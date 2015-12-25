#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
static int idx = 0;
/* 先使用16叉树来尝试构建解码表，而后考虑转成自动机的形式 */

typedef struct _huff_node {
	 unsigned char sym;
	 unsigned char ending;
	 struct _huff_node *child[16];
	 int idx;
} huff_node_t;

typedef struct _huff_bitsplit {
	 unsigned char half_byte;
	 unsigned char ending;
} huff_bitsplit_t;

typedef struct _huff_decode_code {
	 unsigned char next;
	 unsigned char sym;
	 unsigned char ending;
} huff_decode_code_t;

huff_node_t *huff_node_create() {
	 huff_node_t *node = (huff_node_t *)malloc(sizeof(huff_node_t));
	 memset(node, 0, sizeof(huff_node_t));
	 return node;
}

void index_tree(huff_node_t *node) {
	 int i;
	 node->idx = idx++;
	 for (i = 0; i < 16; i++) {
		  if (node->child[i] && !node->child[i]->ending) {
				index_tree(node->child[i]);
		  }
	 }
}

void convert_to_table(huff_node_t *node, huff_decode_code_t decode[64][16]) {
	 int i;
	 int idx = node->idx;
	 for (i = 0; i < 16; i++) {
		  if (node->child[i]) {
				decode[idx][i].ending = node->child[i]->ending;
				decode[idx][i].sym = node->child[i]->sym;
				decode[idx][i].next = node->child[i]->idx;
				convert_to_table(node->child[i], decode);
		  }
	 }
}

void expand_bits(huff_decode_code_t code[16], huff_decode_code_t dst[16], int idx) {
	 int bits, i;
	 unsigned int coding;
	 unsigned char sym = code[idx].sym;
	 bits = huff_table[sym].bits;
	 coding = huff_table[sym].code;
	 if (bits % 4 == 0) {
		  dst[idx] = code[idx];
		  return;
	 }
	 coding <<= (32 - bits % 4);
	 coding >>= 28;
	 for (i = coding; i < coding + (1 << (4 - bits % 4)); i++) {
		  dst[i].sym = code[idx].sym;
		  dst[i].ending = code[idx].ending;
		  dst[i].next = 0;
	 }

}

int main(int argc, char **argv) {
	 huff_node_t *root, *parent, **pnode;
	 unsigned int i, j, code, bits;
	 huff_decode_code_t decode[64][16] = {0};
	 huff_decode_code_t dst[64][16] = {0};
	 huff_bitsplit_t decode_table[256][8] = {0};
	 for (i = 0; i < sizeof(huff_table) / sizeof(huff_table[0]); i++) {
		  for (j = 0; j < huff_table[i].bits / 4; j++) {
				code = huff_table[i].code;
				bits = huff_table[i].bits;
				code = code << ((32 - bits) + j * 4);
				code = code >> 28;
				decode_table[i][j].half_byte = code;
		  }
		  code = huff_table[i].code;
		  bits = huff_table[i].bits;
		  switch (huff_table[i].bits % 4) {
				case 0:
					 break;
				case 1:
					 decode_table[i][j++].half_byte = code & 1;
					 break;
				case 2:
					 decode_table[i][j++].half_byte = code & 3;
					 break;
				case 3:
					 decode_table[i][j++].half_byte = code & 7;
					 break;
		  }
		  decode_table[i][j - 1].ending = 1;
	 }

	 root = huff_node_create();
	 for (i = 0; i < 256; i++) {
		  parent = root;
		  for (j = 0; j < 8; j++) {
				pnode = &parent->child[decode_table[i][j].half_byte];
				if (*pnode == NULL) {
					 *pnode = huff_node_create();
					 if (decode_table[i][j].ending) {
						  (*pnode)->ending = 1;
						  (*pnode)->sym = i;
					 }
				}
				parent = *pnode;
				if (decode_table[i][j].ending)
					 break;
		  }
	 }

	 index_tree(root);
	 convert_to_table(root, decode);
	 
	 memcpy(dst, decode, sizeof(dst));
	 for (i = 0; i < 64; i++) {
		  for (j = 0; j < 16; j++) {
				if (decode[i][j].ending)
					 expand_bits(decode[i], dst[i], j);
		  }
	 }

	 for (i = 0; i < 64; i++) {
		  fprintf(stdout, "{\n");
		  for (j = 0; j < 16; j++)
				fprintf(stdout, "\t{ 0x%02X, 0x%02X, 0x%02X },\n", dst[i][j].next, dst[i][j].sym, dst[i][j].ending);
		  fprintf(stdout, "},\n");
	 }
	 return 0;
}