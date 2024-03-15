make:
	gcc main.c game.c story.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o a.out -g
clean:
	rm -f a.out