/*
 *
 * QuadTree-based Image Compression
 *
 * Copyright (c) 2021 Robert Clayton and/or The Regents of the University of California.
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED AS IS AND WITHOUT ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include "quadtree.h"
#include "make_qtree.h"
#include "utils.h"

#define ABS(x) (((x) < 0) ? (-(x)) : (x))

int homogenous(unsigned char *depth_map, int map_width, int x, int y, int section_width) {
	int grayscale_val = depth_map[x + map_width * y], w, h, temp; //value is set to starting pixel
	for (h = 0; h < section_width; h++) { //while there is still more pixels in the section
		for (w = 0; w < section_width; w++) {
			temp = (x + w) + map_width * (y + h);
			if (depth_map[temp] != grayscale_val) { // value of following pixels != first pixel
				return 256; //nonhomogenous 
			}
		}
	}
	return grayscale_val;
}

qNode *makeNode(unsigned char *depth_map, int map_width, int x, int y, int section_width) {
	int color;
	qNode* node;
	node = (qNode *)malloc(sizeof(qNode));
	color = homogenous(depth_map, map_width, x, y, section_width);
	if (color == 256) {
		node->leaf = 0;
		node->size = section_width;
		node->x = x;
		node->y = y;
		node->gray_value = 256;
		section_width = section_width / 2; // section_width is only half of before
		node->child_NW = makeNode(depth_map, map_width, x, y, section_width);
		node->child_NE = makeNode(depth_map, map_width, x + section_width, y, section_width);
		node->child_SE = makeNode(depth_map, map_width, x + section_width, y + section_width, section_width);
		node->child_SW = makeNode(depth_map, map_width, x, y + section_width, section_width);
	}
	else {
		node->leaf = 1;
		node->size = section_width;
		node->x = x;
		node->y = y;
		node->gray_value = color;
		node->child_NW = NULL;
		node->child_NE = NULL;
		node->child_SE = NULL;
		node->child_SW = NULL;
	}
	return node;
}

qNode *depth_to_quad(unsigned char *depth_map, int map_width) {
	int color, x = 0, y = 0, section = map_width;
	qNode* root;
	root = (qNode *)malloc(sizeof(qNode));
	color = homogenous(depth_map, map_width, x, y, section); // the very first one has a section_width of the entire map
	if (color == 256) {
		root->leaf = 0;
		root->size = section;
		root->x = x;
		root->y = y;
		root->gray_value = 256;
		section = section / 2;
		root->child_NW = makeNode(depth_map, map_width, x, y, section);
		root->child_NE = makeNode(depth_map, map_width, x + section, y, section);
		root->child_SE = makeNode(depth_map, map_width, x + section, y + section, section);
		root->child_SW = makeNode(depth_map, map_width, x, y + section, section);
	}
	else {
		root->leaf = 1;
		root->size = section;
		root->x = x;
		root->y = y;
		root->gray_value = color;
		root->child_NW = NULL;
		root->child_NE = NULL;
		root->child_SE = NULL;
		root->child_SW = NULL;
	}
	return root;
}

void free_qtree(qNode *qtree_node) {
	if (qtree_node) {
		if (!qtree_node->leaf) {
			free_qtree(qtree_node->child_NW);
			free_qtree(qtree_node->child_NE);
			free_qtree(qtree_node->child_SE);
			free_qtree(qtree_node->child_SW);
		}
		free(qtree_node);
	}
}
