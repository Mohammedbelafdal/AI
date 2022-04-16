AI_v2.exe: AI_v2.o loadImg.o error.o
	$(CC) AI_v2.o -Wall -Wextra -fanalyzer	-o AI_v2.exe
loadImg.o: loadImg.h loadImg.c 
	$(CC) -c loadImg.c -Wall -Wextra -fanalyzer -o loadImg.o
AI_v2.o: AI_v2.c
	$(CC) -c AI_v2.c -Wall -Wextra -fanalyzer -o AI_v2.o
error.o:	error.c error.h
	$(CC) -c error.c -Wall -Wextra -fanalyzer  -o error.o
clean:
	rm *.o *.h.gch images/*.bmp 
