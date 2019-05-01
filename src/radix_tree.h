#ifndef RADIX_TREE_H
#define RADIX_TREE_H

typedef struct _string_p {
    const char *str;
    int size;
} String;

typedef struct _radix_tree_node_p {
    int isAWord;
    String prefix;
    struct _radix_tree_node_p *nextSiblingNode;
    struct _radix_tree_node_p *childRoot;
    int numOfChilds;
} RadixTreeNode;

typedef struct _radix_tree_p {
    struct _radix_tree_node_p root;
} RadixTree;

String strsize(const char *s);
String str(const char *s, int size);
int RTSearch(RadixTree *rt, String str);
int RTAddString(RadixTree *rt, String str);
void RTInit(RadixTree *rt);

#endif
