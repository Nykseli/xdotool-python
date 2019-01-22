
import _xdotool

from threading import Thread

THREADING = False

### xdotool key symbols ###

# Symbol for enter key
SYM_ENTER = 'Return'

# Sybol for backspace key
SYM_BACKSPACE = 'BackSpace'

# Symbol for tab key
SYM_TAB = 'Tab'

# Symbol for space key
SYM_SPACE = 'space'

# Symbol for ( character
SYM_PAREN_LEFT = 'parenleft'

# Symbol for ) character
SYM_PAREN_RIGHT = 'parenright'

# Symbol for ! character
SYM_EXCLAMATION = 'exclam'

# Symbol for ? character
SYM_QUESTION_MARK = 'question'

# Symbol for < character
SYM_LESSER_THAN = 'less'

# Symbol for > character
SYM_GREATER_THAN = 'greater'

# Symbol for = character
SYM_EQUAL = 'equal'

# Symbol for @ character
SYM_AT = 'at'

# Symbol for " character
SYM_DOUBLE_QUOTE = 'quotedbl'

# Symbol for # character
SYM_NUMBER_SIGN = 'numbersign'

# Symbol for $ character
SYM_DOLLAR_SIGN = 'dollar'

# Symbol for % character
SYM_PERCENT = 'percent'

# Symbol for & character
SYM_AMBERSAND = 'ampersand'

# Symbol for ' character
SYM_APOSTROPHE = 'apostrophe'

# Symbol for [ character
SYM_SQUARE_BRACKET_LEFT = 'bracketleft'

# Symbol for ] character
SYM_SQUARE_BRACKET_RIGHT = 'bracketright'

# Symbol for { character
SYM_CURLY_BRACKET_LEFT = 'braceleft'

# Symbol for } character
SYM_CURLY_BRACKET_RIGHT = 'braceright'

# Symbol for * character
SYM_ASTERISK = 'asterisk'

# Symbol for ^ character
SYM_CIRCUMFLEX = 'asciicircum'

# Symbol for - character
SYM_MINUS = 'minus'

# Symbol for ` character
SYS_GRAVE_ACCENT = 'grave'

# Symbol for _ character
SYM_UNDERSCORE = 'underscore'

# Symbol for + character
SYM_PLUS = 'plus'

# Symbol for / character
SYM_SLASH = 'slash'

# Symbol for \ character
SYM_BACKSLASH = 'backslash'

# Symbol for . character
SYM_PERIOD = 'period'

# Symbol for , character
SYM_COMMA = 'comma'

# Symbol for : character
SYM_COLON = 'colon'

# Symbol for ; character
SYM_SEMICOLON = 'semicolon'

# Symbol for ~ character
SYM_TILDE = 'asciitilde'

# Symbol for | character
SYM_BAR = 'bar'

# Arrow keys
SYM_ARROW_UP = 'Up'
SYM_ARROW_RIGHT = 'Right'
SYM_ARROW_DOWN = 'Down'
SYM_ARROW_LEFT = 'Left'


def __charToUnicodeCodePoint(c):
    '''
    Return unicode code point in format that xdotool understands.
    E.g. 'Ä' -> "U00C4"
    '''
    #TODO: still slow :(
    return _xdotool.inttoutf8(c)

def __charToXdotoolSymbol(char):
    ''' Change char to a value that xdotool understand'''

    # Get int value of character
    charVal = ord(char)
    # If character is not ascii
    if charVal > 127:
        return __charToUnicodeCodePoint(char)
    # If character is newLine (\n)
    elif charVal == 10:
        return SYM_ENTER
    # If character is a space
    elif charVal == 32:
        return SYM_SPACE
    # If character is !
    elif charVal == 33:
        return SYM_EXCLAMATION
    # If character is "
    elif charVal == 34:
        return SYM_DOUBLE_QUOTE
    # If character is #
    elif charVal == 35:
        return SYM_NUMBER_SIGN
    # If character is $
    elif charVal == 36:
        return SYM_DOLLAR_SIGN
    # If character is %
    elif charVal == 37:
        return SYM_PERCENT
    # If character is &
    elif charVal == 38:
        return SYM_AMBERSAND
    # If charachter if '
    elif charVal == 39:
        return SYM_APOSTROPHE
    # If character is (
    elif charVal == 40:
        return SYM_PAREN_LEFT
    # If character is )
    elif charVal == 41:
        return SYM_PAREN_RIGHT
    # If character is *
    elif charVal == 42:
        return SYM_ASTERISK
    # If character is +
    elif charVal == 43:
        return SYM_PLUS
    # If character is ,
    elif charVal == 44:
        return SYM_COMMA
    # If character is -
    elif charVal == 45:
        return SYM_MINUS
    # If character is .
    elif charVal == 46:
        return SYM_PERIOD
    # If character is /
    elif charVal == 47:
        return SYM_SLASH
    # If character is :
    elif charVal == 58:
        return SYM_COLON
    # If character is ;
    elif charVal == 59:
        return SYM_SEMICOLON
    # If character is <
    elif charVal == 60:
        return SYM_LESSER_THAN
    # If character is =
    elif charVal == 61:
        return SYM_EQUAL
    # If character is >
    elif charVal == 62:
        return SYM_GREATER_THAN
    # If character is ?
    elif charVal == 63:
        return SYM_QUESTION_MARK
    # If character is @
    elif charVal == 64:
        return SYM_AT
    # If character [
    elif charVal == 91:
        return SYM_SQUARE_BRACKET_LEFT
    # If character is \
    elif charVal == 92:
        return SYM_BACKSLASH
    # If character is ]
    elif charVal == 93:
        return SYM_SQUARE_BRACKET_RIGHT
    # If character is ^
    elif charVal == 94:
        return SYM_CIRCUMFLEX
    # If character is _
    elif charVal == 95:
        return SYM_UNDERSCORE
    # IF character is `
    elif charVal == 96:
        return SYS_GRAVE_ACCENT
    # If character is {
    elif charVal == 123:
        return SYM_CURLY_BRACKET_LEFT
    # If character is |
    elif charVal == 124:
        return SYM_BAR
    # If character is }
    elif charVal == 125:
        return SYM_CURLY_BRACKET_RIGHT
    # If character is ~
    elif charVal == 126:
        return SYM_TILDE
    # If character is ascii alphabet
    return char

def inputSingleChar(c):
    '''Change char to a value that xdotool understand and simulate input with it'''
    if THREADING:
        Thread(target=__inputSingleChar, args=(c,)).start()
    else:
        __inputSingleChar(c)

def __inputSingleChar(c):
    symbol = __charToXdotoolSymbol(c)
    _xdotool.keyboardinput("key", symbol)

def inputSingleSymbol(symbol):
    if THREADING:
        Thread(target=__inputSingleSymbol, args=(symbol,)).start()
    else:
        __inputSingleChar(symbol)

def __inputSingleSymbol(symbol):
    _xdotool.keyboardinput("key", symbol)

def inputString(inputString):
    ''' Input string to device with simulating keyboard input'''
    if THREADING:
        Thread(target=__inputString, args=(inputString,)).start()
    else:
        __inputString(inputString)

def __inputString(inputString):
    for c in inputString:
        inputSingleChar(c)

def setMousePosition(x, y):
    if THREADING:
        Thread(target=__setMousePosition, args=(x, y)).start()
    else:
        __setMousePosition(x, y)

def __setMousePosition(x, y):
   #TODO: error if x or y is not type of int and >= 0
    _xdotool.movemouse(x, y)

def moveMouseX(pixel_amount):
    ''' Move cursor on x axis by pixel_amount. Positive is right, negative is left '''
    if THREADING:
        Thread(target=__moveMouseX, args=(pixel_amount,)).start()
    else:
        __moveMouseX(pixel_amount)

def __moveMouseX(pixel_amount):
    ''' Move cursor on x axis by pixel_amount. Positive is right, negative is left '''
    _xdotool.movemouse_relative(pixel_amount, 0)

def moveMouseY(pixel_amount):
    ''' Move cursor on y axis by pixel_amount. Positive amount is down, negative is up '''
    if THREADING:
        Thread(target=__moveMouseY, args=(pixel_amount,)).start()
    else:
        __moveMouseY(pixel_amount)

def __moveMouseY(pixel_amount):
    ''' Move cursor on y axis by pixel_amount. Positive amount is down, negative is up '''
    _xdotool.movemouse_relative(0, pixel_amount)

def leftMouseClick():
    if THREADING:
        Thread(target=__leftMouseClick).start()
    else:
        __leftMouseClick()

def __leftMouseClick():
    _xdotool.mouseclick(1)

