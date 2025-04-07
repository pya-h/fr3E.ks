from words_ky import *
from ast import literal_eval as numberify
from memory import Memory
from fractions import Fraction

def is_operator(character):
    for ch in MATH_OPERATORS:
        if ch == character:
            return True
    return False

def quantify(terms, run_independent=True):
    memain = Memory.MainScope() #memor=y main scope
    if len(terms) > 1:
        new_var = None
        if run_independent:
            new_var = terms[0]
            # double operators:
            if terms[1] == SIGN_PLUS2:
                terms[1] = '+'
                # check for string concat
                if new_var in memain.Variables.keys() and type(memain.Variables[new_var]) == str:
                    memain.Variables.update({new_var: memain.Variables[new_var] + ' ' + stringify([SIGN_STRING] + terms[2:])})
            elif terms[1] == SIGN_MINUS2:
                terms[1] = '-'
            elif terms[1] == SIGN_MULTIPLY2:
                terms[1] = '*'
            elif terms[1] == SIGN_DIVIDE2:
                terms[1] = SIGN_DIVIDE
            elif terms[1] == SIGN_POWER2:
                terms[1] = SIGN_POWER
            elif not ExpressionInspector(new_var).is_common_math_operator():  # if first item is an alphabetic(or whatever) variable name => then the var name is saved in new_var
                del terms[0]

        if SIGN_ROOT in terms[0]:   # start the calculations while considering the modification of wrong operator use: n-/ x   ==> 1 n-/ x
            terms.insert(0, '1')

        batch = []
        terms[0] = memain.dissect(terms[0])
        while len(terms) > 1:
            seperated = False
            if terms[1] == '+':
                terms[0] += memain.dissect(terms[2])
            elif terms[1] == '-':
                terms[0] -= memain.dissect(terms[2])
            elif terms[1] == '*':
                terms[0] *= memain.dissect(terms[2])
            elif terms[1] == SIGN_DIVIDE:
                denominator = memain.dissect(terms[2])
                if len(terms) > 2 and not is_operator(terms[3]):
                    mod_var = terms[3]
                    del terms[3]
                    memain.Variables.update({mod_var: terms[0] % denominator})
                terms[0] /= denominator
                del mod_var, denominator
            elif terms[1] == SIGN_POWER:
                terms[0] **= memain.dissect(terms[2])
            elif terms[1] == SIGN_ROOT:
                terms[0] *= (memain.dissect(terms[2])) ** 0.5
            elif SIGN_ROOT in terms[1]:
                root_degree = terms[1].split(SIGN_ROOT)
                n_inv = 1 / memain.dissect(root_degree[0])  # n_inv = (1/n)
                terms[0] *= (memain.dissect(terms[2])) ** n_inv
            elif terms[1] == SIGN_FRACTION:
                terms[0] = Fraction(terms[0], memain.dissect(terms[2]))
            else:
                seperated = True
                if terms[1].isnumeric() or terms[1] in memain.Variables.keys():
                    batch.append(terms[0])
                    del terms[0]
                    terms[0] = memain.dissect(terms[0])

            if not seperated:
                del terms[2], terms[1]


        if run_independent:
            if batch:
                batch.append(terms[0])
                memain.newBatch(new_var, batch)
                return batch
            else:
                memain.Variables.update({new_var: terms[0]})
                return terms[0]
        else:
            if batch:
                batch.append(terms[0])
                return batch
            return terms[0]
    return memain.dissect(terms[0])  # if len(terms) == 1


def stringify(data):
    memain = Memory.MainScope()
    if data[-1] == SIGN_STRING:
        del data[-1]
    result = ''

    i = 0
    j = 1
    hasoperator = False
    while i < len(data):
        if data[i] == SIGN_STRING:
            j = i + 1
            hasoperator = False
            while j < len(data) and data[j] != SIGN_STRING:
                # error here: is_operator takes a str as param not character
                if not data[j].isnumeric() and not is_operator(data[j]) and not data[j] in memain.Variables:
                    hasunknown = True
                elif is_operator(data[j]):
                    hasoperator = True
                j += 1
        else:
            if data[i] == METHOD_TYPE:
                result += str(data[i+1])
                i += 1
            elif not hasoperator:
                found = False
                # **********
                # NOT GOOD AT ALL
                # FUCKED PERFORMANCE
                if data[i] in memain.Variables or data[i].split(KEY_ITEM_AT)[0] in memain.Batches:
                    #result += str(memain.Variables[data[i]])
                    data[i] = str(memain.dissect(data[i]))
                    result += data[i]
                    found = True
                # if(data[i] in memain.Batches.keys()):
                #     if found:
                #         result += " & "
                #     result += str(memain.Batches[data[i]])
                #     found = True
                # else
                if not found:
                    result += data[i]
            elif hasoperator:
                result += str(quantify(data[i: j], False))  # calculate_equation fucks the first parameter
                i = j - 1
            if i < len(data) - 1:
                result += ' '
        i += 1
    return result
