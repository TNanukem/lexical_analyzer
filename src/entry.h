#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum symbol Symbol;

enum symbol {mais_simb, menos_simb, mult_simb, div_simb, igual_simb, diff_simb,
			 maior_simb, menor_simb, maior_igual_simb, menor_igual_simb,
			 ponto_virgula_simb, virgula_simb, ponto_simb, dois_pontos_simb,
			 abre_par_simb, fecha_par_simb, abre_chave_simb, fecha_chave_simb,
			 ident, numero_int, numero_real, error_simb, reserved_simb, no_simb, eof_simb};


typedef struct entry Entry;

struct entry{
	char* str;
	int line, column;
	int code;
	Symbol sym;
};

static const char *error_messages[] = {"Limite de identificador excedido",					 // 0
								"Limite de caracteres excedido para numero inteiro", // 1
								"Limite de caracteres excedido para numero real", 	 // 2
								"Simbolo nao pertence a linguagem",					 // 3
								"Comentario mal formado", "Numero real mal formado", // 4, 5
								"Identificador mal formado"};						 // 6

			 
const char* symbolToStr(Symbol sym);
int isValidSymbol(Symbol sym);

Entry* initEntry(char* str, int str_len, int line, Symbol sym, int code);
Entry* initEntry2(char* str, int str_len, int line, int column, Symbol sym, int code);

void handleEntry(Entry local_entry);
