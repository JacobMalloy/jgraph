all: image1.jpg image2.jpg image3.jpg image4.jpg image5.jpg random.jpg

spiro: spiro.c
	gcc -O3 -Wall -Wextra -o spiro spiro.c -lm

clean:
	rm -f *.jpg
	rm -f *.pdf
	rm -f spiro


image1.jpg: input1.txt spiro
	./spiro < $< | jgraph | convert -density 600 - $@
image2.jpg: input2.txt spiro
	./spiro < $< | jgraph | convert -density 600 - $@
image3.jpg: input3.txt spiro
	./spiro < $< | jgraph | convert -density 600 - $@
image4.jpg: input4.txt spiro
	./spiro < $< | jgraph | convert -density 600 - $@
image5.jpg: input5.txt spiro
	./spiro < $< | jgraph | convert -density 600 - $@
random.jpg: spiro
	python3 random_gen.py | ./spiro | jgraph | convert -density 600 - $@
