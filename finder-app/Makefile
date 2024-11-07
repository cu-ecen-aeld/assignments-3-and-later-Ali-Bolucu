CC = aarch64-none-linux-gnu-gcc

native_build: writer.c
	@echo  "Native building"
	gcc writer.c -o writer -Wno-implicit-function-declaration

CROSS_COMPILE: writer.c
	@echo  "Cross compiling"
	${CC} writer.c -o writer -Wno-implicit-function-declaration

clean:
	@echo  "clean up..."
	rm -f writer
