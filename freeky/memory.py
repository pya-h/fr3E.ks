
from ast import literal_eval as numberify
from words_ky import *

class Memory:

    def __init__(self):
        self.Variables = {}
        self.Batches = {}
        self.MathFunctions = {}

    def dissect(self, term):
        components = term.split(KEY_ITEM_AT)
        inspector = ExpressionInspector(term)
        if len(components) > 1 : # if its a batch item call => means there was @ there
            batch_name = components[0]
            indices = components[1].split(KEY_BATCH_INDEX_SEPARATOR)
            n = len(indices)
            for i in range(n):
                indices[i] = self.dissect(indices[i])
            item = self.batchItemAt(batch_name, indices)
            return item
        elif inspector.is_math_function_callback():
            math_func = inspector.get_math_function_callback()
            sent_parameters = math_func.keys()
            if math_func and 'name' in sent_parameters and 'variables' in sent_parameters:
                return self.evaluateMathFunction(math_func['name'], math_func['variables'])
        # check if its complex

        return self.get(term)


    def evaluateMathFunction(self, name, variable_values):
        if name in self.MathFunctions.keys():
            math_func = self.MathFunctions[name].copy()
            math_expression = math_func['formula']
            for i in range(len(math_func['variables'])):
                var_value = self.dissect(variable_values[i])
                math_expression = math_expression.replace(math_func['variables'][i], str(var_value))
            return eval(math_expression)

        return None  # in case of error

    def batchItemAt(self, name, indices):
        if name in self.Batches:
            item = self.Batches[name].copy()
            while indices:
                index = indices.pop(0)
                item = item[index]
            return item

        raise NotImplemented("No batch found")

    def newBatch(self, name, items):
        self.Batches.update({name: items})

    def newMathFunction(self, name, variables, formula_terms):
        if name and variables and formula_terms:
            formula = ' '.join(str(t) for t in formula_terms)
            # formula check
            # name and variables check
            self.MathFunctions.update({ name: {'variables': variables, 'formula': formula} })

    def get(self, name):
        return self.Variables[name] \
            if name in self.Variables \
            else self.Batches[name] if name in self.Batches \
            else numberify(name)

    @staticmethod
    def CreateMainScope():
        Memory.__mainScope = Memory()
        Memory.__drafts = []

    @staticmethod
    def MainScope():
        return Memory.__mainScope

    @staticmethod
    def draft(value):
        Memory.__drafts.append(value)

    @staticmethod
    def undraft():
        temp = Memory.__drafts.copy()
        Memory.__drafts.clear()
        return temp
