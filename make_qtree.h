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

#ifndef MAKE_QTREE_H
#define MAKE_QTREE_H

/* Implement this in make_qtree.c */
int homogenous(unsigned char *depth_map, int map_width, int x, int y, int section_width);

/* Implement this in make_qtree.c */
qNode *depth_to_quad(unsigned char *depth_map, int image_width);

/* Function that frees the quadtree created */
void free_qtree(qNode *qtree_root);

#endif
