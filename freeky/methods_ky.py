from random import randint
from termcolor import cprint, colored
from calculus import *

def process_type_params(expression):
    del expression[0]
    if expression[0] != SIGN_STRING:
        expression.insert(0, SIGN_STRING)
    return stringify(expression)

def blahblah():

    chars = 'abcdefghi jklmnopqrstuvwxyz'
    (MIN_LENGTH, MAX_LENGTH, LEN_CHARS) = (5, 30, len(chars))
    text_length = randint(MIN_LENGTH, MAX_LENGTH)
    text = ''
    for i in range(text_length):
        charpos = randint(0, LEN_CHARS - 1)
        text += chars[charpos]
    return text


def ask_value(params):
    default_value = None
    i = 0
    
    if params:
        while i < len(params) and params[i] != SIGN_PARAM_SEPARATOR:
            i += 1
        cprint(stringify(params[: i]), "grey", "on_green", end=' ')

    temp = str(input()).split()
    if not temp:  # if input is empty
        if i < len(params):
            if params[i + 1] == SIGN_STRING:
                return stringify(params[i + 1:])
            else:
                return quantify(params[i:], False)  # first param is deleted in calculate_equation
        else:
            return None

    value = stringify([SIGN_STRING] + temp)
    if value.isnumeric():
        return numberify(value)
    return value