OBJS = menu.o submenu.o func.o
HEAD = Header1.h Header2.h
PM = menu.c
SM = submenu.c
FUN = func.c
CL = *.o
G = gcc -o
C = gcc -c
T = test

test: $(OBJS) $(HEAD) 
	$(G) $(T) $(OBJS) -lpthread
menu.o: $(PM) $(HEAD)
	$(C) $(PM)
	
submenu.o: $(SM) $(HEAD)
	$(C) $(SM)

func.o: $(FUN) Header2.h
	$(C) $(FUN)

clean: 
	rm $(CL)
	rm $(T)
