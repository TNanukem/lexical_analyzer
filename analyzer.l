%{
#include <stdio.h>

    const char *reserved[] = {"program", "begin", "end", "const", "var", "real", "integer",
                      "procedure", "if", "else", "for", "while", "read", "write",
                      "do", "then"};

    int isReserved(char* ident){
        // Recebe o ident e faz uma busca pra ver se é palavra
        // reservada da linguagem ou não.
        return 0;
    }

%}

digit [0-9]
letter [a-zA-Z]
mais_simb "+"
menos_simb "-"
mult_simb "*"
div_simb "/"
igual_simb "="
diff_simb "<>"
maior_simb ">"
menor_simb "<"
maior_igual_simb ">="
menor_igual_simb "<="
ponto_virgula_simb ";"
virgula_simb ","
ponto_simb "."
abre_par_simb "("
fecha_par_simb ")"

ident {letter}({letter}|{digit})*
numero_int -?{digit}+
numero_real -?{digit}+"."{digit}+

%%

{ident} {if(!isReserved(yytext)) printf("%s - ident\n", yytext); else printf("%s - %s\n", yytext, yytext);}
{numero_int} {printf("%s - numero_int\n", yytext);}
{numero_real} {printf("%s - numero_real\n", yytext);}

{mais_simb} {printf("%s - mais_simb\n", yytext);}
{menos_simb} {printf("%s - menos_simb\n", yytext);}
{mult_simb} {printf("%s - mult_simb\n", yytext);}
{div_simb} {printf("%s - div_simb\n", yytext);}

{igual_simb} {printf("%s - igual_simb\n", yytext);}
{diff_simb} {printf("%s - diff_simb\n", yytext);}
{maior_simb} {printf("%s - maior_simb\n", yytext);}
{menor_simb} {printf("%s - menor_simb\n", yytext);}
{maior_igual_simb} {printf("%s - maior_igual_simb\n", yytext);}
{menor_igual_simb} {printf("%s - menor_igual_simb\n", yytext);}

{abre_par_simb} {printf("%s - abre_par_simb\n", yytext);}
{fecha_par_simb} {printf("%s - fecha_par_simb\n", yytext);}

{virgula_simb} {printf("%s - virgula_simb\n", yytext);}
{ponto_simb} {printf("%s - ponto_simb\n", yytext);}
{ponto_virgula_simb} {printf("%s - ponto_virgula_simb\n", yytext);}

%%
int main(){
    yylex();
    return 0;
}
