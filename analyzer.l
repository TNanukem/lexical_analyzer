%{
#include <stdio.h>
#include <string.h>
#include "src/radix_tree.h"

    const char *reserved[] = {"program", "begin", "end", "const", "var", "real", "integer",
                      "procedure", "if", "else", "for", "while", "read", "write",
                      "do", "then", "to", NULL};

    RadixTree rt;

    int isReserved(char* ident, int size){
        // Recebe o ident e faz uma busca pra ver se é palavra
        // reservada da linguagem ou não.
        return RTSearch(&rt, str(ident, size));
    }

    int n_linhas = 1;

%}

digito [0-9]
letra [a-zA-Z]
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
dois_pontos_simb ":"
abre_par_simb "("
fecha_par_simb ")"
abre_chave_simb "{"
fecha_chave_simb "}"

espaco " "
quebra_linha "\r"?"\n"
tab "\t"

comentario_mal_formado "{"[^}\n]*"\n"
comentario "{"[^}\n]*"}"

ident ({letra}|"_")+({letra}|{digito})*
identificador_mal_formado {digito}+({letra}|"-"|"_")+

numero_int ("+"|"-")?{digito}+
numero_real ("+"|"-")?{digito}+"."{digito}+

numero_real_mal_formado_1 ("+"|"-")?"."{digito}+
numero_real_mal_formado_2 ("+"|"-")?{digito}+"."[^digito]
numero_real_mal_formado_3 ("+"|"-")?{digito}+"."{digito}+"."
%%

{ident} {if(yyleng > 100) printf("%s - erro: Limite de identificador excedido, linha %d\n", yytext, n_linhas); else if(!isReserved(yytext, yyleng)) printf("%s - ident\n", yytext); else printf("%s - %s\n", yytext, yytext);}
{numero_int} {if(yyleng < 12) printf("%s - numero_int\n", yytext); else printf("%s - erro: Limite de caracteres excedido para numero inteiro, linha %d\n", yytext, n_linhas);}
{numero_real} {if(yyleng < 309) printf("%s - numero_real\n", yytext); else printf("%s - erro: Limite de caracteres excedido para numero real, linha %d\n", yytext, n_linhas);}

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
{dois_pontos_simb} {printf("%s - dois_pontos_simb\n", yytext);}

{comentario} ;
{espaco} ;
{tab} ;
{quebra_linha} {n_linhas++;}

. {printf("%s - erro: simbolo nao pertence a linguagem, linha %d\n", yytext, n_linhas);}
{comentario_mal_formado} {printf("erro: comentario mal formado, linha %d\n", n_linhas);}
{numero_real_mal_formado_1} {printf("%s - erro: Numero real mal formado, linha %d\n", yytext, n_linhas);}
{numero_real_mal_formado_2} {printf("%s - erro: Numero real mal formado, linha %d\n", yytext, n_linhas);}
{numero_real_mal_formado_3} {printf("%s - erro: Numero real mal formado, linha %d\n", yytext, n_linhas);}
{identificador_mal_formado} {printf("%s - erro: Identificador mal formado, linha %d\n", yytext, n_linhas);}

%%
int main(){
    RTInit(&rt);

    int i = 0;
    while(reserved[i] != NULL) {
        RTAddString(&rt, strsize(reserved[i]));
        i++;
    }

    yylex();

    RTClean(&rt);
    return 0;
}
