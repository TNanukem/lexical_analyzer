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

            node->childRoot = rtnode;
            node->numOfChilds = 1;
            return 0;
        } else {
            RadixTreeNode *rtcurr = node->childRoot;
            RadixTreeNode *rtprev = NULL;

            int charConsumed = 0;
            while((rtcurr != NULL) && (charConsumed == 0)) {
                int strLen = str.size - strIdx;
                if(strLen > rtcurr->prefix.size) {
                  strLen = rtcurr->prefix.size;
                }

                while(charConsumed < strLen && rtcurr->prefix.str[charConsumed] == str.str[strIdx + charConsumed]) {
                    charConsumed++;
                }

                if(charConsumed == 0) {
                    rtprev = rtcurr;
                    rtcurr = rtcurr->nextSiblingNode;
                }
            }

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
                if(charConsumed + strIdx < str.size) {
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
                rtcurr->isAWord = 1;
                return 0;
            } else {
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
            return 0;
        } else {
            RadixTreeNode *rtchild = node->childRoot;

            int charConsumed = 0;
            while(rtchild != NULL && charConsumed == 0) {
                int len = str.size - strIdx;
                if(len > rtchild->prefix.size) {
                  len = rtchild->prefix.size;
                }

                while(charConsumed < len && rtchild->prefix.str[charConsumed] == str.str[strIdx + charConsumed]) {
                    charConsumed++;
                }

                if(charConsumed == 0) {
                    rtchild = rtchild->nextSiblingNode;
                }
            }

            if(rtchild == NULL) {
              return 0;
            }

            if(charConsumed == rtchild->prefix.size) {
                strIdx += charConsumed;

                if(strIdx == str.size) {
                    return rtchild->isAWord;
                }
                node = rtchild;
            } else {
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
