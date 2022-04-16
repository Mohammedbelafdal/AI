AI_v2.exe: AI_v2.o loadImg.o
	$(CC) AI_v2.o	-o AI_v2.exe
loadImg.o: loadImg.h loadImg.c 
	$(CC) -c loadImg.c -o loadImg.o
AI_v2.o: AI_v2.c
	$(CC) -c AI_v2.c -o AI_v2.o
clean:
	rm *.o *.h.gch images/*.bmp 
