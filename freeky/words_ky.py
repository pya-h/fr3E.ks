(METHOD_TYPE, METHOD_ASK, METHOD_MEMORY, METHOD_PRECEDE, METHOD_BLAHBLAH) = ('#', '$', '#mm', '()', 'blahblah')

(SIGN_STRING, SIGN_PLUS2, SIGN_MINUS2, SIGN_MULTIPLY2, SIGN_DIVIDE, SIGN_DIVIDE2) = (':', '++', '--', '**', '%', '%%')
(SIGN_POWER, SIGN_POWER2, SIGN_PARAM_SEPARATOR, SIGN_COMMANDS_SEPARATOR, SIGN_ROOT, SIGN_FRACTION) = ('^', '^^', ',', ' . ', '-/', '/')

# flows
(FLOW_MAIN, FLOW_CHECK, FLOW_LOOP) = (0, 1, 2)

# main keywords
(KEY_CHECK, KEY_LOOP, KEY_BYEBYE, KEY_ITEM_AT, KEY_BATCH_INDEX_SEPARATOR, KEY_DRAFT, KEY_UNDRAFT) = ('?', '@', '<3', '@', '.', '==>', '<==')
(KEY_MATH_FUNCTION_DEFINER, KEY_MATH_FUNCTION_VARIABLE_SEPERATOR) = ('=', ',')

# loop keywords
KEY_LOOP_CONDITIONER = (KEY_LOOP_TILL, KEY_LOOP_WHILE, KEY_LOOP_DONT_DELETE_COUNTER) = ('!', '~~', '~dl')

MATH_OPERATORS = ('+', '-', '*', SIGN_DIVIDE, SIGN_POWER, SIGN_PLUS2, SIGN_MINUS2,
                  SIGN_MULTIPLY2, SIGN_DIVIDE2, SIGN_POWER2, SIGN_ROOT, SIGN_FRACTION)

LOGIC_OPERATORS =\
   (LOGIC_EQUAL, LOGIC_SMALLER, LOGIC_GREATER, LOGIC_EQUAL_SMALLER,
    LOGIC_EQUAL_GREATER, LOGIC_NOT_EQUALS, LOGIC_2SMALLER, LOGIC_2GREATER,
    LOGIC_2NEAR) =\
   ('=', '<', '>', '\\<', '>/', '<>', '<<', '>>', '~')  # def some new ops : like "is one more than "


LOGIC_COMBINERS =\
   (LOGIC_AND, LOGIC_OR, LOGIC_NAND,
    LOGIC_NOR, LOGIC_XOR, LOGIC_NOT) = ('&', ',', '`&', '`,', 'x,', '`')

# log:
print('keywords loaded successfully ...')



class ExpressionInspector:
    def __init__(self, expression):
        self.expression = expression

    def is_common_math_operator(self):
        return self.expression in MATH_OPERATORS or SIGN_ROOT in self.expression or \
            (self.expression != KEY_LOOP and KEY_ITEM_AT in self.expression)  or self.is_math_function_callback() # last one === x@i

    def is_math_function_callback(self):
        return '(' in self.expression and ')' in self.expression

    def get_math_function_callback(self):
        # gets the function name and dedicated variables;
        # is_math_funtion_callback must be called before for making sure
        by_paranthesis_splitted = self.expression.split('(')
        function_name = by_paranthesis_splitted[0]
        between_paranthesis = by_paranthesis_splitted[1].split(')')[0]  # text between (x,y)
        if between_paranthesis and between_paranthesis != '':
            math_function_variables = between_paranthesis.split(KEY_MATH_FUNCTION_VARIABLE_SEPERATOR)
            return {
                'name': function_name,
                'variables': math_function_variables
            }
        return None  # in case of error happening
