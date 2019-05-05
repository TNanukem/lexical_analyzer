#include "entry.h"

const char* symbolToStr(Symbol sym){
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
	return (sym != error_simb) && (sym != reserved_simb) && (sym != no_simb) && (sym != eof_simb);
}

Entry* initEntry(char* str, int str_len, int line, Symbol sym, int code){
	Entry* local_entry = (Entry*) malloc(sizeof(Entry));
	if(local_entry == NULL){
		fprintf(stderr, "Entry allocation Error");
		exit(-1);
	}
	local_entry->str = (char*) malloc(str_len+1);
	if(local_entry == NULL){
		fprintf(stderr, "String allocation Error");
		exit(-1);
	}
	snprintf(local_entry->str, str_len+1, "%s", str);
	local_entry->line = line;
	local_entry->column = -1;
	local_entry->sym = sym;
	if(sym == error_simb){
		local_entry->code = code;
	}else{
		local_entry->code = -1;
	}
	return local_entry;
}

Entry* initEntry2(char* str, int str_len, int line, int column, Symbol sym, int code){
	Entry* local_entry = initEntry(str, str_len, line, sym, code);
	local_entry->column = column;
	return local_entry;
}

void handleEntry(Entry local_entry){
	if(isValidSymbol(local_entry.sym)){
		printf("%s - %s\n", local_entry.str, symbolToStr(local_entry.sym));
	}else if(local_entry.sym == reserved_simb){
		printf("%s - %s\n", local_entry.str, local_entry.str);
	}else if(local_entry.sym == error_simb){
		printf("ERRO: %s, linha: %d\n", error_messages[local_entry.code], local_entry.line);
	}
}

