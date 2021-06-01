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


#ifndef UTILS_H
#define UTILS_H

typedef struct {
    unsigned char *data;
    int width;
    int height;
} Image;

/* Loads a BMP file */
Image load_image(char *filename);

/* Prints the image. May be helpful in debugging */
void print_image(const unsigned char *data, int width, int height);

/* Writes a image into a grayscale BMP file */
void save_image(char *filename, const unsigned char *data, int width,
        int height);

/* Writes a image into a color BMP file, highlighting boxes */
void save_image_with_depth(char *filename, const unsigned char *data,
        const unsigned char *depth, int width, int height, int feature_width,
        int feature_height);

/* Should be called if memory allocation fails. */
void allocation_failed();

#endif
