import ply.lex as lex

tokens = (
    # Keywords
    'VAL', 'VAR', 'FUN', 'IF', 'ELSE', 'WHEN', 'RETURN',
    # Types
    'INT_TYPE', 'STRING_TYPE', 'BOOLEAN_TYPE', 'DOUBLE_TYPE', 'FLOAT_TYPE',
    # Literals
    'NUMBER', 'STRING_LIT', 'TRUE', 'FALSE',
    # Identifiers
    'ID',
    # Operators
    'ASSIGN', 'PLUS', 'MINUS', 'TIMES', 'DIVIDE',
    'EQ', 'NE', 'LT', 'GT', 'LE', 'GE',
    'AND', 'OR', 'NOT',
    # Delimiters
    'LPAREN', 'RPAREN', 'LBRACE', 'RBRACE',
    'COLON', 'COMMA', 'ARROW', 'SEMICOLON'
)

reserved = {
    'val': 'VAL',
    'var': 'VAR',
    'fun': 'FUN',
    'if': 'IF',
    'else': 'ELSE',
    'when': 'WHEN',
    'return': 'RETURN',
    'Int': 'INT_TYPE',
    'String': 'STRING_TYPE',
    'Boolean': 'BOOLEAN_TYPE',
    'Double': 'DOUBLE_TYPE',
    'Float': 'FLOAT_TYPE',
    'true': 'TRUE',
    'false': 'FALSE'
}

t_ASSIGN = r'='
t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_DIVIDE = r'/'
t_EQ = r'=='
t_NE = r'!='
t_LE = r'<='
t_GE = r'>='
t_LT = r'<'
t_GT = r'>'
t_AND = r'&&'
t_OR = r'\|\|'
t_NOT = r'!'
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_LBRACE = r'\{'
t_RBRACE = r'\}'
t_COLON = r':'
t_COMMA = r','
t_ARROW = r'->'
t_SEMICOLON = r';'

def t_ID(t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    t.type = reserved.get(t.value, 'ID')  
    return t

def t_NUMBER(t):
    r'\d+(\.\d+)?'
    t.value = float(t.value) if '.' in t.value else int(t.value)
    return t

def t_STRING_LIT(t):
    r'\"([^\\\n]|(\\.))*?\"'
    return t

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

t_ignore = ' \t'

def t_COMMENT(t):
    r'//.*'
    pass  

def t_error(t):
    print(f"Illegal character '{t.value[0]}'")
    t.lexer.skip(1)

lexer = lex.lex()