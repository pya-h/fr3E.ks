from ast import literal_eval as numberify
import os
from termcolor import cprint, colored
from pympler.asizeof import asizeof
import colorama
from memory import Memory
import methods_ky as myfy
from calculus import *

# import keyboard # i think its needed, but if not feel free to remove:)

Memory.CreateMainScope()

# import keywords
from words_ky import *

previous_check_results = [True]  # this fuck controls the conditions and running statements
current_flow = FLOW_MAIN  # for now i had to define it globally, because 'check' algorithm in do_cmd
# i need to separate check code ( like i seperated loops ) and then define current_flow locally
# loop_conditions = [] # all loop conditions

def freekey_ide():
    global current_flow
    # change CHECK algorithm entirely to work with the loops
    colorama.init()
    os.system("color")

    # error : s :: 10   .   s = 10 => true !
    # maybe its better
    statements = []
    # s = :: test ?   error ; cause of string sign
    # do some exception handling
    # s :: test .   s = test => true        good or not?
    # s :: test ? => error; because it reads '?' and think its condition
    print('everything & everyone needs space')
    current_flow = FLOW_MAIN
    str_input = ''
    loop_block = []
    num_nested_loops = 0
    while True:
        try:
            # prompt is used to indention
            prompt = ''
            for c in range(num_nested_loops + len(previous_check_results) - 1):
                prompt += '\t'
            prompt += '> '

            statements = []
            str_input = input(prompt)

            statements.extend(str_input.split(SIGN_COMMANDS_SEPARATOR))
            # using retrievable function to implement nested loops and 1 dimensional 'statements' list ( Memory probem )
            # using other methods to implement nested loops and multi dimensional 'statements' list
            # ( also memory problem and complexity )
            for cmd in statements:
                cmd = cmd.replace(' ' + METHOD_BLAHBLAH, ' ' + myfy.blahblah())  # **********************
                # serious fuckin attention
                # do to using blahblah as method and allow it to be used inb the middle of everything
                # the user can not use the text blahblah to be printed exactlt
                # what do you suggest to do huh?

                terms = cmd.split()
                if not str_input:
                    if current_flow == FLOW_CHECK:
                        previous_check_results.pop()
                        if num_nested_loops > 0:
                            current_flow = FLOW_LOOP
                        elif not len(previous_check_results):
                            # better to construct 'flows' list to check everything precisely
                            current_flow = FLOW_MAIN

                        # current_flow = previous flow in list of flows
                    elif current_flow == FLOW_LOOP:
                        current_flow = FLOW_MAIN  # completely temporary /// need to construct a list for flows
                        # e.g. what if its a nested loop? or what if there was an "check" block before?
                        execute_loop(loop_block)
                        # for now, its just for simple loops, for nested loops u need to improvise these statements
                        loop_block = []  # just for simple loops, nested loops?
                        num_nested_loops -= 1
                elif terms[0] == KEY_LOOP:
                    current_flow = FLOW_LOOP
                    loop_block.append(cmd)
                    num_nested_loops += 1
                elif current_flow == FLOW_LOOP:
                    # if commands may encounter with errors because of not getting empty lines!
                    loop_block.append(cmd)
                    # .extend() will add the list char by char in this case ( why?)
                    # its better to remove each cmd in statements to improve ram usage
                else:
                    # for check and main flows:
                    execute_command(terms)

        except SystemExit:
            print(colored('bye bye bitch', "cyan"))
            break
        except Exception as exc:  # for infinite loop def a LoopException : Exception
            # ( write its class ) and then handle error completely
            cprint(str(exc), "grey", "on_red")


def check_condition(condition):
    # find a way to solve :: x = 2 = :: x = 2
    # modify leftpart & rightpart
    # try to add & | ...

    # CHECK CONDITION HAS MANY BUGS
    i = -1
    logic_sign_found = False
    lencondition = len(condition)
    while i < lencondition and not logic_sign_found:
        i += 1
        for ch in LOGIC_OPERATORS:
            if ch == condition[i]:
                logic_sign_found = True
                break
    if logic_sign_found:
        sign = condition[i]
        # ************modify, notice memory **********
        leftpart = stringify([SIGN_STRING] + condition[: i])
        rightpart = stringify([SIGN_STRING] + condition[i + 1:])

        if leftpart.isnumeric():
            leftpart = numberify(leftpart)
        if rightpart.isnumeric():
            rightpart = numberify(rightpart)

        if sign == LOGIC_EQUAL:
            if leftpart == rightpart:
                return True
            return False
        elif sign == LOGIC_SMALLER:
            if leftpart < rightpart:
                return True
            return False
        elif sign == LOGIC_GREATER:
            if leftpart > rightpart:
                return True
            return False
        elif sign == LOGIC_EQUAL_SMALLER:
            if leftpart <= rightpart:
                return True
            return False
        elif sign == LOGIC_EQUAL_GREATER:
            if leftpart >= rightpart:
                return True
            return False
        elif sign == LOGIC_NOT_EQUALS:
            if leftpart != rightpart:
                return True
            return False
        elif sign == LOGIC_2NEAR:
            # whatever
            # if leftpart < rightpart:
            # return True
            return False

    return False


def execute_command(terms):
    global current_flow
    main = Memory.MainScope()

    if terms[-1] == KEY_CHECK:
        del terms[-1]
        current_flow = FLOW_CHECK
        run_permission = True
        for check_result in previous_check_results:
            if not check_result:
                run_permission = False
                break

        if run_permission and check_condition(terms):
            previous_check_results.append(True)
        else:
            previous_check_results.append(False)

    elif previous_check_results[-1]:
        if terms[-1] == KEY_UNDRAFT:
            main.Variables.update({terms[0]: Memory.undraft()})
        elif terms[0] == METHOD_TYPE:
            # error in typing strings
            cprint(colored('\t:= ' + myfy.process_type_params(terms) + '  ', "green"))
        elif terms[0] == METHOD_MEMORY:
            memory_analysis()
            # enable parameters like: #mm x
        elif len(terms) > 1 and terms[1] == METHOD_ASK:
            main.Variables.update({terms[0]: myfy.ask_value(terms[2:])})
        elif len(terms) == 1 and terms[0] == KEY_BYEBYE:
            raise SystemExit
        elif KEY_MATH_FUNCTION_DEFINER in terms:
            del terms[terms.index(KEY_MATH_FUNCTION_DEFINER)]  # delete the '=' item
            inspector = ExpressionInspector(terms[0])
            if inspector.is_math_function_callback():
                math_func = inspector.get_math_function_callback()
                main.newMathFunction(math_func['name'], math_func['variables'], terms[1:])  # f(x,y) = x + 3*y
        else:
            mustDraft = terms[-1] == KEY_DRAFT
            if mustDraft:
                del terms[-1]
                if len(terms) < 1:
                    Memory.draft(None)
                elif len(terms) == 1:
                    terms[0] = numberify(terms[0]) \
                        if terms[0].isnumeric() else (terms[0] \
                        if terms[0] != METHOD_BLAHBLAH else myfy.blahblah())
                    Memory.draft((terms[0] if terms[0] not in main.Variables.keys() else main.Variables[terms[0]]))
                    return
            varName = terms[0] # variable name
            result = None
            if terms[0].isnumeric() or ExpressionInspector(terms[0]).is_common_math_operator():
                result = quantify(terms=terms, run_independent=False)
                if not mustDraft:
                    cprint(colored('\t:= ' + str(result) + '  ', "green"))
            elif terms[1] == SIGN_STRING:
                    main.Variables.update({varName: stringify(terms[1:])})
                    result = main.Variables[varName]
            else:
                result = quantify(terms=terms)
            # if drafting requested
            if mustDraft:
                Memory.draft(result)


def convert_loop_condition(counter, init, block):
    main = Memory.MainScope()
    cond = []
    # conditioner_index = 0
    # while not init[conditioner_index] in KEY_LOOP_CONDITIONER:
    # conditioner_index += 1

    # if init[conditioner_index] == KEY_LOOP_TO:  # dont forget other loop states
    if init[0] in main.Variables.keys() or init[0].isnumeric():  # if init[0] is numeric then it's the LOOP_TO mode:
        # e.g. @ i 1 + 2 - 5 * 2 2 - 1 + 3 4 - x + 6
        # start = part1 = 1 + 2 - 5 * 2
        # step = part2 = 2 - 1 + 3
        # end = part3 = 4 - x + 6

        # IMPORTANT ERROR: using % in loop init will cause error
        # because of x % y "r"
        step = 1
        part1 = 0
        while init[part1] in MATH_OPERATORS or init[part1 + 1] in MATH_OPERATORS:  # for now, calculations only contain
            # math ops in future i add logic operators as well
            part1 += 1
        part1 += 1  # part1 is fixed on " :    -5 * 2 "2" - 1

        part3 = 2
        while init[-part3] in MATH_OPERATORS or init[-part3 + 1] in MATH_OPERATORS:
            part3 += 1  # part3 is fixed on " :    - 1 + "3" 4 - x

        main.Variables.update({counter: quantify(terms=init[: part1], run_independent=False)})

        if part1 <= len(init) - part3:
            step = quantify(terms=init[part1: -part3 + 1], run_independent=False)
        if not step:
            raise Exception("ERROR: loop with infinite iterates detected")
        stop = quantify(terms=init[-part3 + 1:], run_independent=False)
        cond = [counter, (LOGIC_EQUAL_SMALLER if step > 0 else LOGIC_EQUAL_GREATER), str(stop)]
        block.append(counter + ' ++ ' + str(step))  # adds the loop step code ( block param is passed by reference )
    return cond


def execute_loop(block):
    # its better to remove each cmd in block to improve ram usage
    # always first cmd is loop conditions:
    loop_init = block[0].split()
    del block[0]
    counter = loop_init[1]
    condition = convert_loop_condition(counter, loop_init[2:], block)
    # IMPORTANT ERROR: using % in loop init will cause error
    del loop_init
    while check_condition(condition):
        for command in block:
            execute_command(command.split())
    del Memory.MainScope().Variables[counter]
    # delete counter


def memory_analysis():
    main = Memory.MainScope()
    print(colored("\t\tvariables\n------------------------------------------------\n", "cyan"),end='\t')
    for var in main.Variables.keys():
        print(colored(var, "cyan"),end='\t')
        print(colored(str(main.Variables[var]), "green"), end='\t')
        # print(colored(sys.getsizeof(str(main.Variables[var])), "red"))
        print(colored(asizeof(str(main.Variables[var])), "red"), end=" Byte(s)\n")
    print(colored("\n\t\tbatches:\n------------------------------------------------\n", "cyan"),end='\t')
    for bch in main.Batches.keys():
        print(colored(bch, "cyan"),end='\t')
        print(colored(str(main.Batches[bch]), "green"), end='\t')
        # print(colored(sys.getsizeof(str(main.Batches[bch])), "red"))
        print(colored(asizeof(str(main.Batches[bch])), "red"), end=" Byte(s)\n")


if __name__ == "__main__":
    freekey_ide()
    # change CHECK algorithm entirely to work with the loops


# NEW IDEAS:
# Save Calculation expressions for each variable: maybe its needed to know how its value created!.
