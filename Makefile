quadtree: quadtree.c make_qtree.c utils.c
	gcc -o quadtree quadtree.c make_qtree.c utils.c

clean:
	rm -rf quadtree

