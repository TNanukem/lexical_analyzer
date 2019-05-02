#include "radix_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RTInit(RadixTree *rt) {
  rt->root.isAWord = 0;
  rt->root.prefix.str = "";
  rt->root.prefix.size = 0;
  rt->root.childRoot = NULL;
  rt->root.numOfChilds = 0;
}

int RTAddString(RadixTree *rt, String str) {
    RadixTreeNode *node = &(rt->root);

    int strIdx = 0;
    while (strIdx < str.size) {
        if(node->numOfChilds == 0) {
            /* Não há continuação para o prefixo achado. O restante da string
            *  será adicionado como um sufixo do nó atual.
            */
            RadixTreeNode *rtnode = (RadixTreeNode *)malloc(sizeof(RadixTreeNode));
            if(rtnode == NULL) {
              return -1;
            }

            /* Tornar o caminho até esse nó uma palavra válida */
            rtnode->isAWord = 1;
            rtnode->prefix.str = &(str.str[strIdx]);
            rtnode->prefix.size = str.size - strIdx;
            rtnode->childRoot = NULL;
            rtnode->nextSiblingNode = NULL;
            rtnode->numOfChilds = 0;

            node->childRoot = rtnode;
            node->numOfChilds = 1;

            return 0;
        } else {
            /* Há sufixos para o caminho encontrado, procura um sufixo que continue
             * a string str
             */
            RadixTreeNode *rtcurr = node->childRoot;
            RadixTreeNode *rtprev = NULL;

            /* Procurar um sufixo até que algum caractere seja consumido
             * (sufixos não apresentam início igual)
             */
            int charConsumed = 0;
            while((rtcurr != NULL) && (charConsumed == 0)) {
                /* Calcula o máximo que pode ser comparado */
                int strLen = str.size - strIdx;
                if(strLen > rtcurr->prefix.size) {
                  strLen = rtcurr->prefix.size;
                }

                /* Se encontrar um sufixo que continue a string, a string é
                 * consumida até chegar um ponto de divergência
                 */
                while(charConsumed < strLen && rtcurr->prefix.str[charConsumed] == str.str[strIdx + charConsumed]) {
                    charConsumed++;
                }

                /* continua a busca em outro sufixo se não há nenhum caractere igual */
                if(charConsumed == 0) {
                    rtprev = rtcurr;
                    rtcurr = rtcurr->nextSiblingNode;
                }
            }

            /* Se não houve caracter consumido temos que rtcurr == NULL,
             * logo deve-se adicionar um novo sufixo para esse prefixo
             */
            if(charConsumed == 0) {
                RadixTreeNode *rtnode = (RadixTreeNode *)malloc(sizeof(RadixTreeNode));
                if(rtnode == NULL) {
                  return -1;
                }

                rtnode->isAWord = 1;
                rtnode->prefix.str = &(str.str[strIdx]);
                rtnode->prefix.size = str.size - strIdx;
                rtnode->childRoot = NULL;
                rtnode->nextSiblingNode = NULL;
                rtnode->numOfChilds = 0;

                rtprev->nextSiblingNode = rtnode;
                (node->numOfChilds)++;

                return 0;
            } else if(charConsumed < rtcurr->prefix.size) {
                /* Se o sufixo não foi uma igualdade completa, deve-se quebrar
                 * esse sufixo até o ponto de equivalência total, adicionando o
                 * resto do sufixo e da str como sufixo filho */
                if(charConsumed + strIdx < str.size) {
                    /* Se ainda há um str não consumida, ela deve ser adicionada
                     * também a lista de sufios filhos */
                    RadixTreeNode *rtnodebranch = (RadixTreeNode *)malloc(sizeof(RadixTreeNode));
                    if(rtnodebranch == NULL) {
                        return -1;
                    }

                    RadixTreeNode *rtnode = (RadixTreeNode *)malloc(sizeof(RadixTreeNode));
                    if(rtnode == NULL) {
                        free(rtnodebranch);
                        return -1;
                    }

                    rtnodebranch->isAWord = rtcurr->isAWord;
                    rtcurr->isAWord = 0;

                    rtnodebranch->prefix.str = &(rtcurr->prefix.str[charConsumed]);

                    rtnodebranch->prefix.size = rtcurr->prefix.size - charConsumed;
                    rtcurr->prefix.size = charConsumed;

                    rtnodebranch->childRoot = rtcurr->childRoot;
                    rtcurr->childRoot = rtnodebranch;

                    rtnodebranch->nextSiblingNode = rtnode;

                    rtnodebranch->numOfChilds = rtcurr->numOfChilds;
                    rtcurr->numOfChilds = 2;

                    rtnode->isAWord = 1;
                    rtnode->prefix.str = &(str.str[strIdx + charConsumed]);
                    rtnode->prefix.size = str.size - strIdx - charConsumed;
                    rtnode->childRoot = NULL;
                    rtnode->nextSiblingNode = NULL;
                    rtnode->numOfChilds = 0;
                } else {
                  /* Se a str foi consumida completamente, deve-se setar o caminho a
                   * esse sufixo como sendo uma palabra válida e adicionar apenas o restante
                   * do sufixo a lista de sufixos filhos */
                  RadixTreeNode *rtnodebranch = (RadixTreeNode *)malloc(sizeof(RadixTreeNode));
                  if(rtnodebranch == NULL) {
                      return -1;
                  }

                  rtnodebranch->isAWord = rtcurr->isAWord;
                  rtcurr->isAWord = 1;

                  rtnodebranch->prefix.str = &(rtcurr->prefix.str[charConsumed]);

                  rtnodebranch->prefix.size = rtcurr->prefix.size - charConsumed;
                  rtcurr->prefix.size = charConsumed;

                  rtnodebranch->childRoot = rtcurr->childRoot;
                  rtcurr->childRoot = rtnodebranch;

                  rtnodebranch->nextSiblingNode = NULL;

                  rtnodebranch->numOfChilds = rtcurr->numOfChilds;
                  rtcurr->numOfChilds = 1;
                }

                return 0;
            } else if(charConsumed + strIdx == str.size) {
                /* Se o sufixo e a str foram consumidas completamente, o caminho
                 * até esse sufixo se torna uma palavra válida */
                rtcurr->isAWord = 1;
                return 0;
            } else {
                /* Se ainda há str para ser consumida, porém o sufixo foi consumido
                 * completamente, procuramos consumir a str com os sufixos filhos
                 */
                node = rtcurr;
                strIdx += charConsumed;
            }
        }
    }

    return -2;
}


int RTSearch(RadixTree *rt, String str) {
    RadixTreeNode *node = &(rt->root);

    int strIdx = 0;
    while(strIdx < str.size) {
        if(node->numOfChilds == 0) {
            /* Se não há nenhum sufixo para consumir a str, ela não é uma palavra válida */
            return 0;
        } else {
            RadixTreeNode *rtchild = node->childRoot;

            /* Procura um sufixo para consumir a str */
            int charConsumed = 0;
            while(rtchild != NULL && charConsumed == 0) {
                int len = str.size - strIdx;
                if(len > rtchild->prefix.size) {
                  len = rtchild->prefix.size;
                }

                /* A str é consumida encontrando sufixos com caracteres iguais */
                while(charConsumed < len && rtchild->prefix.str[charConsumed] == str.str[strIdx + charConsumed]) {
                    charConsumed++;
                }

                /* Se não foi encontrado um caractere igual, o próximo sufixo é testado */
                if(charConsumed == 0) {
                    rtchild = rtchild->nextSiblingNode;
                }
            }

            /* Se não foram encontrados sufixos para consumir a str, ela não
             * é uma palavra válida */
            if(rtchild == NULL) {
              return 0;
            }

            /* Se a str consumiu completamente o sufixo, é possível que ela seja válida */
            if(charConsumed == rtchild->prefix.size) {
                strIdx += charConsumed;

                /* se a palavra foi consumida completamente, e o caminho até o sufixo
                 * é uma palavra, então str é uma palavra */
                if(strIdx == str.size) {
                    return rtchild->isAWord;
                }

                /* Se a str não foi consumida completamente, continua a busca */
                node = rtchild;
            } else {
              /* Se o sufixo não foi consumido completamente, str não é uma palavra */
                return 0;
            }
        }
    }
    return 0;
}

void RTCleanNode(RadixTreeNode *node) {
    if(node == NULL) {
      return;
    }

    RTCleanNode(node->nextSiblingNode);
    RTCleanNode(node->childRoot);

    free(node);
}

void RTClean(RadixTree *rt) {
    RTCleanNode(rt->root.childRoot);

    RTInit(rt);
}

String str(const char *s, int size) {
    String tmp;
    tmp.str = s;
    tmp.size = size;

    return tmp;
}

String strsize(const char *s) {
    return str(s, strlen(s));
}
