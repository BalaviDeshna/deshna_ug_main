import ply.yacc as yacc
from lexer import tokens

def p_program(p):
    '''program : statement
               | program statement'''
    pass

def p_statement(p):
    '''statement : variable_declaration
                 | function_declaration
                 | selection_statement'''
    pass

def p_variable_declaration(p):
    '''variable_declaration : VAL ID COLON type ASSIGN expression
                           | VAR ID COLON type ASSIGN expression
                           | VAL ID ASSIGN expression
                           | VAR ID ASSIGN expression'''
    pass

def p_function_declaration(p):
    '''function_declaration : FUN ID LPAREN RPAREN COLON type LBRACE statements RBRACE
                           | FUN ID LPAREN RPAREN LBRACE statements RBRACE
                           | FUN ID LPAREN parameter_list RPAREN COLON type LBRACE statements RBRACE
                           | FUN ID LPAREN parameter_list RPAREN LBRACE statements RBRACE'''
    pass

def p_parameter_list(p):
    '''parameter_list : parameter
                     | parameter_list COMMA parameter'''
    pass

def p_parameter(p):
    '''parameter : ID COLON type'''
    pass

def p_statements(p):
    '''statements : statement
                 | statements statement
                 | empty'''
    pass

def p_selection_statement(p):
    '''selection_statement : if_statement
                          | when_statement'''
    pass

def p_if_statement(p):
    '''if_statement : IF LPAREN expression RPAREN LBRACE statements RBRACE
                   | IF LPAREN expression RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE
                   | IF LPAREN expression RPAREN LBRACE statements RBRACE ELSE if_statement'''
    pass

def p_when_statement(p):
    '''when_statement : WHEN LPAREN expression RPAREN LBRACE when_entries RBRACE'''
    pass

def p_when_entries(p):
    '''when_entries : when_entry
                   | when_entries when_entry'''
    pass

def p_when_entry(p):
    '''when_entry : expression ARROW LBRACE statements RBRACE
                 | ELSE ARROW LBRACE statements RBRACE'''
    pass

def p_type(p):
    '''type : INT_TYPE
           | STRING_TYPE
           | BOOLEAN_TYPE
           | DOUBLE_TYPE
           | FLOAT_TYPE'''
    pass

def p_expression_binop(p):
    '''expression : expression PLUS expression
                 | expression MINUS expression
                 | expression TIMES expression
                 | expression DIVIDE expression
                 | expression EQ expression
                 | expression NE expression
                 | expression LT expression
                 | expression GT expression
                 | expression LE expression
                 | expression GE expression
                 | expression AND expression
                 | expression OR expression'''
    pass

def p_expression_unop(p):
    '''expression : NOT expression
                 | MINUS expression'''
    pass

def p_expression_group(p):
    '''expression : LPAREN expression RPAREN'''
    pass

def p_expression_value(p):
    '''expression : NUMBER
                 | STRING_LIT
                 | TRUE
                 | FALSE
                 | ID'''
    pass

def p_empty(p):
    '''empty :'''
    pass

def p_error(p):
    if p:
        print(f"Syntax error at '{p.value}'")
    else:
        print("Syntax error at EOF")
    exit(1)

parser = yacc.yacc()