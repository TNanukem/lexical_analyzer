%{
#include <stdio.h>
#include <string.h>
#include "src/radix_tree.h"
#include "src/entry.h"

    const char *reserved[] = {"program", "begin", "end", "const", "var", "real", "integer",
							  "procedure", "if", "else", "for", "while", "read", "write",
							  "do", "then", "to", NULL};							 

    RadixTree rt;
    
    Entry* currentEntry;

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

{ident} { 	if(yyleng > 100){
				currentEntry = initEntry(yytext, yyleng, n_linhas, error_simb, 0);
				return -1;
			}else if(!isReserved(yytext, yyleng)){
				currentEntry = initEntry(yytext, yyleng, n_linhas, ident, -1);
				return 0;
			}else {
				currentEntry = initEntry(yytext, yyleng, n_linhas, reserved_simb, -1);
				return 0;
			}
		}
		
{numero_int} {	if(yyleng < 12){
					currentEntry = initEntry(yytext, yyleng, n_linhas, numero_int, -1);
					return 0;
				}else {
					currentEntry = initEntry(yytext, yyleng, n_linhas, error_simb, 1);
					return -1;
				}
			 }
			 
{numero_real} {	if(yyleng < 309){
					currentEntry = initEntry(yytext, yyleng, n_linhas, numero_real, -1);
					return 0;
				}else {
					currentEntry = initEntry(yytext, yyleng, n_linhas, error_simb, 2);
					return -1;
				}
			  }

{mais_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, mais_simb, -1);return 0;}
{menos_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, menos_simb, -1);return 0;}
{mult_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, mult_simb, -1);return 0;}
{div_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, div_simb, -1);return 0;}

{igual_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, igual_simb, -1);return 0;}
{diff_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, diff_simb, -1);return 0;}
{maior_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, maior_simb, -1);return 0;}
{menor_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, menor_simb, -1);return 0;}
{maior_igual_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, maior_igual_simb, -1);return 0;}
{menor_igual_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, menor_igual_simb, -1);return 0;}

{abre_par_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, abre_par_simb, -1);return 0;}
{fecha_par_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, fecha_par_simb, -1);return 0;}

{virgula_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, virgula_simb, -1);return 0;}
{ponto_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, ponto_simb, -1);return 0;}
{ponto_virgula_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, ponto_virgula_simb, -1);return 0;}
{dois_pontos_simb} {currentEntry = initEntry(yytext, yyleng, n_linhas, dois_pontos_simb, -1);return 0;}

{comentario} {currentEntry = initEntry(yytext, yyleng, n_linhas, no_simb, -1);return 0;}
{espaco} {currentEntry = initEntry(yytext, yyleng, n_linhas, no_simb, -1);return 0;}
{tab} {currentEntry = initEntry(yytext, yyleng, n_linhas, no_simb, -1);return 0;}
{quebra_linha} {n_linhas++;
				currentEntry = initEntry(yytext, yyleng, n_linhas, no_simb, -1);
				return 0;
				}

. {currentEntry = initEntry(yytext, yyleng, n_linhas, error_simb, 3);return -1;}
{comentario_mal_formado} {currentEntry = initEntry(yytext, yyleng, n_linhas, error_simb, 4);n_linhas++;return -1;}
{numero_real_mal_formado_1} {currentEntry = initEntry(yytext, yyleng, n_linhas, error_simb, 5);return -1;}
{numero_real_mal_formado_2} {currentEntry = initEntry(yytext, yyleng, n_linhas, error_simb, 5);return -1;}
{numero_real_mal_formado_3} {currentEntry = initEntry(yytext, yyleng, n_linhas, error_simb, 5);return -1;}
{identificador_mal_formado} {currentEntry = initEntry(yytext, yyleng, n_linhas, error_simb, 6);return -1;}

<<EOF>> {currentEntry = initEntry(yytext, yyleng, n_linhas, eof_simb, -1);return 1;}

%%
int main(){
    RTInit(&rt);

    int i = 0;
    while(reserved[i] != NULL) {
        RTAddString(&rt, strsize(reserved[i]));
        i++;
    }
	
	Entry** fileEntries;
	
	i = 0;
	do{
		yylex();
		if(i!=0){
			fileEntries = (Entry**) realloc(fileEntries, (i+1)*sizeof(Entry*));
		}else{
			fileEntries = (Entry**) malloc(sizeof(Entry*));
		}
		fileEntries[i] = currentEntry;
		handleEntry(*fileEntries[i]);
		i++;
	}while(fileEntries[i-1]->sym != eof_simb);

	i--;
	while(i>=0){
		free(fileEntries[i]->str);
		free(fileEntries[i]);
		i--;
	}
	free(fileEntries);

    RTClean(&rt);
    return 0;
}
