/** @file assembler.c
*  @brief You will modify this file and implement the assembler.h interface
*  @details This is a implementation of the interface that you will write
*  for the assignment. Although there are only four functions defined
*  by the interface, it is likely that you will add many helper functions
*  to perform specific tasks.
*  <p>
*  @author <b>Brent Grundman ~ I worked alone</b>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <assert.h>

#include "assembler.h"
#include "lc3.h"
#include "symbol.h"
#include "tokens.h"
#include "util.h"

/** Global variable containing the current line number in the source file*/
static int srcLineNum;

/** Global variable containing the current LC3 address */
static int currAddr;

// do not modify
line_info_t* asm_init_line_info(line_info_t* info) {
	if (!info)
		info = malloc(sizeof(line_info_t));

	info->next = NULL;
	info->lineNum = srcLineNum;
	info->address = currAddr;
	info->opcode = OP_INVALID;
	info->format = NULL;
	info->DR = -1;
	info->SR1 = -1;
	info->SR2 = -1;
	info->immediate = 0;
	info->reference = NULL;

	return info;
}

// do not modify
void asm_print_line_info(line_info_t* info) {
	if (info) {
		fprintf(stderr, "%3d: addr: x%04x op: %s DR:%3d, SR1:%3d SR2:%3d imm: %d ref: %s\n",
			info->lineNum, info->address, lc3_get_opcode_name(info->opcode), info->DR,
			info->SR1, info->SR2, info->immediate, info->reference);
	}
}

// do not modify
/* based on code from http://www.eskimo.com/~scs/cclass/int/sx11c.html */

void asm_error(const char* msg, ...) {
	numErrors++;
	va_list argp;
	fprintf(stderr, "ERROR %3d: ", srcLineNum);
	va_start(argp, msg);
	vfprintf(stderr, msg, argp);
	va_end(argp);
	fprintf(stderr, "\n");
}

/** @todo implement this function */
void asm_init(void) {
	srcLineNum = 1;
	currAddr = 0;
	tokens_init();
	lc3_sym_tab = symbol_init(256, 0);
}

line_info_t* asm_pass_one(const char* asm_file_name,
	const char* sym_file_name) {
	FILE *fp;
	FILE *st;
	line_info_t* linklist = NULL;
	char str[255];
	fp = fopen(asm_file_name, "r");
	st = fopen(sym_file_name, "w");
	if (fp != NULL) {
		while (fgets(str, 255, fp) != NULL) {
			//convert line to tokens
			const char* tokens[10];
			const char* tok;
			int i = 0;
			//Put tokens into array max 10
			for (tok = tokenize_lc3_line(str); tok != NULL; tok = next_token()) {
				tokens[i] = tok;
				//printf("token[%d]: = '%s'\n", i++, tok);
				i++;
			}
			//Null out other tokens (useful later)
			for (; i < 10; i++) {
				tokens[i] = NULL;
			}
			//if there is a label, add it to symbol table
			i = 0;
			opcode_t opcode = util_get_opcode(tokens[i]);
			line_info_t* info = asm_init_line_info(NULL);
			//asm_init_line_info(info);
			if (opcode == OP_ORIG) {
				i++;
				int value = 0;
				info->opcode = opcode;
				lc3_get_int(tokens[i], &value);
				info->immediate = value;
				currAddr = value;
				i++;
			}
			if (opcode == OP_INVALID) {
				//currAddr++;
				int goodAdd = 0;
				if (util_is_valid_label(tokens[i])) {
					goodAdd = symbol_add(lc3_sym_tab, tokens[i], currAddr);
					if (goodAdd == 0) {
						asm_error(ERR_DUPLICATE_LABEL, tokens[i]);
						exit(0);
					}
					i++;
				}
				//else error not a valid label
			}

			if (tokens[i] != NULL) {
				//printf("%s \n", tokens[i]);
				opcode = util_get_opcode(tokens[i]);
				int reg = 0;

				if (lc3_get_format_name(opcode)) {
					//i++;
					currAddr++;
					info->opcode = opcode;
					switch (opcode) {

					case OP_LD: {
						i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->DR = reg;
						//PCOFFSET
						i++; i++;
						//lc3_get_int(tokens[i], &reg);
						//info->immediate = reg;
						info->reference = strdup(tokens[i]);
						break;
					}
					case OP_ST: {
						i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->DR = reg;
						//PCOFFSET
						i++; i++;
						lc3_get_int(tokens[i], &reg);
						info->reference = strdup(tokens[i]);
						break;
					}
					case OP_JSR_JSRR: {

						//JSR 
						if (strcmp(tokens[i], "JSR") == 0) {
							i++;
							//lc3_get_int(tokens[i],reg);
							//info->immediate = reg;
							info->reference = strdup(tokens[i]);
						}
						else {
							//JSRR 
							i++;
							reg = util_get_reg(tokens[i]);
							if (reg<0 || reg > 7) {
								asm_error(ERR_EXPECTED_REG, tokens[i]);
								exit(0);
							}
							info->SR1 = reg;
						}
						break;
					}
					case OP_AND: {
						i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->DR = reg;
						i++; i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->SR1 = reg;
						i++; i++;
						if ((util_get_reg(tokens[i])) >= 0) {
							reg = util_get_reg(tokens[i]);
							if (reg<0 || reg > 7) {
								asm_error(ERR_EXPECTED_REG, tokens[i]);
								exit(0);
							}
							info->SR2 = reg;
						}
						else {
							lc3_get_int(tokens[i], &reg);
							info->immediate = reg;
						}
						break;
					}
					case OP_LDR: {
						i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->DR = reg;
						i++; i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->SR1 = reg;
						//OFFSET
						i++; i++;
						lc3_get_int(tokens[i], &reg);
						info->immediate = reg;
						break;
					}
					case OP_STR: {
						i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->DR = reg;
						i++; i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->SR1 = reg;
						//OFFSET
						i++; i++;
						lc3_get_int(tokens[i], &reg);
						info->immediate = reg;
						break;
					}
					case OP_RTI: {
						break;
					}
					case OP_NOT: {
						i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->DR = reg;
						i++; i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->SR1 = reg;
						break;
					}

					case OP_LDI: {
						i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->DR = reg;
						//PCOFFSET
						i++; i++;
						//lc3_get_int(tokens[i], &reg);
						//info->immediate = reg;
						info->reference = strdup(tokens[i]);
						break;
					}
					case OP_STI: {
						i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->DR = reg;
						//PCOFFSET
						i++; i++;
						//lc3_get_int(tokens[i], &reg);
						//info->immediate = reg;
						info->reference = strdup(tokens[i]);
						break;
					}
					case OP_JMP_RET: {
						
						i++;
						//JMP 
						reg = util_get_reg(tokens[i]);
						i--;
						if (strcmp(tokens[i], "JMP") == 0) {
							if (reg < 0 || reg > 7) {
								asm_error(ERR_EXPECTED_REG, tokens[i]);
								exit(0);
							}
						}
						info->SR1 = reg;
						//RET ???        
						break;
					}
					case OP_LEA: {
						i++;
						//printf("%s \n", tokens[i]);
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->DR = reg;

						//PCOFFSET
						i++; i++;
						//lc3_get_int(tokens[i], &reg);
						//info->immediate = reg;
						info->reference = strdup(tokens[i]);
						break;
					}
					case OP_TRAP: {
						i++;
						lc3_get_int(tokens[i], &reg);
						info->immediate = reg;
						break;
					}
					case OP_END: {
						break;
					}
					case OP_BLKW: {
						i++;
						lc3_get_int(tokens[i], &reg);
						info->immediate = reg;
						currAddr--;
						currAddr = currAddr + reg;
						break;
					}
					case OP_FILL: {
						i++;
						if (lc3_get_int(tokens[i], &reg)) {
							info->immediate = reg;
						}
						else
							info->reference = strdup(tokens[i]);
						//currAddr = currAddr + reg;
						break;
					}
					case OP_GETC: {
						break;
					}

					case OP_OUT: {
						break;
					}

					case OP_PUTS: {
						break;
					}

					case OP_IN: {
						break;
					}

					case OP_PUTSP: {
						break;
					}

					case OP_HALT: {
						break;
					}

					case OP_GETS: {
						break;
					}

					case OP_BR: {
						//check for nzp
						const char* afterBRp = (tokens[i] + 2);
						//printf("%s \n", afterBRp);

						int cond = util_parse_cond(afterBRp);
						//PCOFFSET or label
						info->DR = cond;
						//printf("%s \n", tokens[i]);
						//printf("%d \n", cond);
						i++;
						//printf("%s \n", tokens[i]);
						//printf("GOOD \n");
						//reg = util_get_reg(tokens[i]);
						//lc3_get_int(tokens[i], &reg);
						//info->immediate = reg;
						//printf("%s \n", tokens[i]);
						info->reference = strdup(tokens[i]);
						break;
					}
					case OP_ADD: {
						i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->DR = reg;
						i++; i++;
						reg = util_get_reg(tokens[i]);
						if (reg<0 || reg > 7) {
							asm_error(ERR_EXPECTED_REG, tokens[i]);
							exit(0);
						}
						info->SR1 = reg;
						i++; i++;
						if ((util_get_reg(tokens[i])) >= 0) {
							reg = util_get_reg(tokens[i]);
							if (reg<0 || reg > 7) {
								asm_error(ERR_EXPECTED_REG, tokens[i]);
								exit(0);
							}
							info->SR2 = reg;
						}
						else {
							lc3_get_int(tokens[i], &reg);
							info->immediate = reg;
						}
						break;
					}
					case OP_INVALID:break;
					case OP_RESERVED:break;
					case OP_ORIG:break;
					case OP_STRINGZ:break;
					case OP_NEWLN:break;
					case OP_ZERO:break;
					case OP_COPY:break;
					case OP_SETCC:break;
					case OP_SUB:break;
					case NUM_OPCODES:break;
					}
				}
				srcLineNum++;
			}
			else {
				srcLineNum++;
			}
			i = 0;
			if (tokens[i] != NULL) {
				if (linklist == NULL) {
					if (opcode == OP_ORIG) {
						linklist = info;
						//asm_print_line_info(info);
						//asm_print_line_info(linklist);
					}
					else {
						asm_error(ERR_NO_ORIG);
						exit(0);
					}
				}
				else if(opcode!=OP_INVALID) {
					//asm_print_line_info(info);
					line_info_t* lastnode = linklist;
					while (lastnode->next) {
						lastnode = lastnode->next;
					}
					lastnode->next = info;
				}
				else {
					free(info);
				}
			}
			else {
				free(info);
			}
		}
		
	}
	//else return could not open file
	else {
		asm_error(ERR_OPEN_READ,asm_file_name);
		exit(0);
	}
	if (st != NULL) {
		lc3_write_sym_table(st);
	}
	else {
		asm_error(ERR_OPEN_WRITE,sym_file_name);
		exit(0);
	}
	//else return could not write file
	fclose(fp);
	fclose(st);
	return linklist;
}

/** @todo implement this function */
void asm_pass_two(const char* obj_file_name, line_info_t* list) {
	lc3_set_obj_file_mode(obj_file_name);
	FILE* fp = fopen(obj_file_name, "w");
	//int line = 0;
	if (fp == NULL) {
		asm_error(ERR_OPEN_WRITE, obj_file_name);
		exit(0);
	}
	for (; list; list = list->next) {
		//line++;
		int setdr = 0;
		int setr1 = 0;
		int setr2 = 0;
		int setref = 0;
		int setimm = 0;
		int ADDR = 0;
		const char* token = list->reference;
		//printf("Line: %d\n", line);
		asm_print_line_info(list);
		//get hex opcode, <<12
		int toHex = (list->opcode)<<12;
		if (list->DR != -1) {
			toHex = toHex + ((list->DR) << 9);
			setdr++;
		}
		if (list->SR1 != -1) {
			toHex = toHex + ((list->SR1) << 6);
			setr1++;
		}
		if (list->SR2 != -1) {
			toHex = toHex + ((list->SR2));
			setr2++;
		}
		else if (list->reference != NULL) {
			//address/PCOffset
			//printf("reference\n");
			if (lc3_get_address(token, &ADDR)) {
				lc3_get_address(token,&ADDR);
			}
			else {
				asm_error(ERR_MISSING_LABEL, token);//error: symbol not in table
				exit(0);
			}
			if (ADDR < 0 || ADDR >0x7fff) {
				asm_error(ERR_BAD_PCOFFSET, token);
				exit(0);
			}
			setref++;
		}
		else {
			//immediate masked by 5?
			//printf("immediate\n");
			toHex = toHex + ((list->immediate));
			setimm++;
		}
		switch (list->opcode) {
		case OP_ADD: {
			if (setimm) {
				if (list->immediate < 0)
					toHex = toHex + (1 << 6);
				else
					toHex = toHex + (1 << 5);
			}
			break;
		}
		case OP_AND: {
			if (setimm) {
				if (list->immediate < 0)
					toHex = toHex + (1 << 6);
				else
					toHex = toHex + (1 << 5);
			}
			break;
		}
		case OP_NOT: {
			toHex = toHex + 0x3F;
			break;
		}
		case OP_BR: {
			//toHex = toHex && 0x0FFF;
			ADDR = ADDR - list->address - 1;
			if (ADDR >0xffffffff) {
				asm_error(ERR_BAD_PCOFFSET, token);
				exit(0);
			}
			//ADDR = ADDR && 0x01FF;
			toHex = toHex + ADDR;
			if(ADDR<0)
				toHex = toHex + (1 << 9);
			break;
		}
		case OP_JMP_RET: {
			if(!setr1)
				toHex = toHex + (7 << 6);
			break;
		}
		case OP_JSR_JSRR: {
			if (!setr1) {
				ADDR = ADDR - list->address - 1;
				if (ADDR >0xfffffffffff) {
					asm_error(ERR_BAD_PCOFFSET, token);
					exit(0);
				}
				toHex = toHex + ADDR;
				if(ADDR>0)
					toHex = toHex + (1 << 11);
			}
			break;
		}
		case OP_LD: {
			ADDR = ADDR - list->address - 1;
			if (ADDR >0xfffffffff) {
				asm_error(ERR_BAD_PCOFFSET, token);
				exit(0);
			}
			toHex = toHex + ADDR;
			if(ADDR<0)
				toHex = toHex + (1 << 9);
			break;
		}
		case OP_LDI: {
			ADDR = ADDR - list->address - 1;
			if (ADDR >0xfffffffff) {
				asm_error(ERR_BAD_PCOFFSET, token);
				exit(0);
			}
			toHex = toHex + ADDR;
			if(ADDR<0)
				toHex = toHex + (1 << 9);
			break;
		}
		case OP_LEA: {
			ADDR = ADDR - list->address - 1;
			if (ADDR >0xfffffffff) {
				asm_error(ERR_BAD_PCOFFSET, token);
				exit(0);
			}
			toHex = toHex + ADDR;
			break;
		}
		case OP_ST: {
			ADDR = ADDR - list->address - 1;
			if (ADDR >0xfffffffff) {
				asm_error(ERR_BAD_PCOFFSET, token);
				exit(0);
			}
			toHex = toHex + ADDR;
			break;
		}
		case OP_STI: {
			ADDR = ADDR - list->address - 1;
			if (ADDR >0xfffffffff) {
				asm_error(ERR_BAD_PCOFFSET, token);
				exit(0);
			}
			toHex = toHex + ADDR;
			break;
		}
		case OP_STR: {
			if(list->immediate<0)
			toHex = toHex + (1 << 6);
			break;
		}
		case OP_BLKW: {
			toHex = 0;
			int block = list->immediate;			
			for (int i = 0; i < block - 1;i++) {
				lc3_write_LC3_word(fp, toHex);
			}
			break;
		}
		case OP_FILL: {
			if (setref) {
				toHex = ADDR;
			}
			else {
				toHex = list->immediate;
			}
			break;
		}
		case OP_IN: {
			toHex = 0xf023;
			break;
		}
		case OP_OUT: {
			toHex = 0xf021;
			break;
		}
		case OP_GETC: {
			toHex = 0xf020;
			break;
		}
		case OP_GETS: {
			toHex = 0xf026;
			break;
		}
		case OP_PUTS: {
			toHex = 0xf022;
			break;
		}
		case OP_PUTSP: {
			toHex = 0xf024;
			break;
		}
		case OP_HALT: {
			toHex = 0xf025;
			break;
		}
		default:break;
		}

		if(list->opcode!=OP_END)
			lc3_write_LC3_word(fp, toHex);
	}
	fclose(fp);
}

/** @todo implement this function */
void asm_term(line_info_t* list) {
	symbol_term(lc3_sym_tab);
	tokens_term();
	line_info_t* getNext = list;
	while (list != NULL) {
		list = list->next;
		free(getNext->reference);
		free(getNext);
		getNext = list;
	}
}