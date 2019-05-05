#include "entry.h"

const char* symbolToStr(Symbol sym){
	// Simples switch
	switch(sym){
		case mais_simb:
			return "mais_simb";
		case menos_simb:
			return "menos_simb";
		case mult_simb:
			return "mult_simb";
		case div_simb:
			return "div_simb";
		case igual_simb:
			return "igual_simb";
		case diff_simb:
			return "diff_simb";
		case maior_simb:
			return "maior_simb";
		case menor_simb:
			return "menor_simb";
		case maior_igual_simb:
			return "maior_igual_simb";
		case menor_igual_simb:
			return "menor_igual_simb";
		case ponto_virgula_simb:
			return "ponto_virgula_simb";
		case virgula_simb:
			return "virgula_simb";
		case ponto_simb:
			return "ponto_simb";
		case dois_pontos_simb:
			return "dois_pontos_simb";
		case abre_par_simb:
			return "abre_par_simb";
		case fecha_par_simb:
			return "fecha_par_simb";
		case abre_chave_simb:
			return "abre_chav_simb";
		case fecha_chave_simb:
			return "fecha_chave_simb";
		case ident:
			return "ident";
		case numero_int:
			return "numero_int";
		case numero_real:
			return "numero_real";
		case error_simb:
			return "error_simb";
		case reserved_simb:
			return "reserved_simb";
		case no_simb:
			return "no_simb";
		case eof_simb:
			return "eof_simb";
	}
}

int isValidSymbol(Symbol sym){
	/* Para fins da funcao handleEntry, simbolos validos nao sao erros, 
	 * nao sao palavras reservadas, sao simbolos ou numeros e nao sao o 
	 * fim do arquivo.
	 */
	return (sym != error_simb) && (sym != reserved_simb) && (sym != no_simb) && (sym != eof_simb);
}

Entry* initEntry(char* str, int str_len, int line, Symbol sym, int code){
	// Alocacao
	Entry* local_entry = (Entry*) malloc(sizeof(Entry));
	// Checagem de erro
	if(local_entry == NULL){
		fprintf(stderr, "Entry allocation Error");
		exit(-1);
	}
	// Alocacao
	local_entry->str = (char*) malloc(str_len+1);
	// Checagem de erro
	if(local_entry == NULL){
		fprintf(stderr, "String allocation Error");
		exit(-1);
	}
	// Copia do texto recebido
	snprintf(local_entry->str, str_len+1, "%s", str);
	// Copia da linha no arquivo
	local_entry->line = line;
	// Nao recebe-se coluna ainda
	local_entry->column = -1;
	// Copia da enumeracao do simbolo
	local_entry->sym = sym;
	if(sym == error_simb){
	// Se for erro, copia o codigo
		local_entry->code = code;
	}else{
	// Se nao, coloca valor padrao
		local_entry->code = -1;
	}
	return local_entry;
}

Entry* initEntry2(char* str, int str_len, int line, int column, Symbol sym, int code){
	// Chamada de funcao sem numero de coluna
	Entry* local_entry = initEntry(str, str_len, line, sym, code);
	// Copia do numero da coluna
	local_entry->column = column;
	return local_entry;
}

void handleEntry(Entry local_entry){
	if(isValidSymbol(local_entry.sym)){
		// Impressao padrao, "texto - simbolo"
		printf("%s - %s\n", local_entry.str, symbolToStr(local_entry.sym));
	}else if(local_entry.sym == reserved_simb){
		// Impressao de palavra reservada, "texto - palavra"
		printf("%s - %s\n", local_entry.str, local_entry.str);
	}else if(local_entry.sym == error_simb){
		// Impressao de erro, "ERRO: mensagem, linha: numero da linha"
		printf("ERRO: %s, linha: %d\n", error_messages[local_entry.code], local_entry.line);
	}
}

