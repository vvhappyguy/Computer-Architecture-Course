all:
	touch shmfile
	clang sh_read.c -Weverything -O0 -lpthread -o read.out
	clang sh_write.c -Weverything -O0 -lpthread -o write.out
	echo "!Please start read.out in another console"
	./write.out
	rm write.out
	rm read.out
	rm shmfile
compile:
	clang sh_read.c -Weverything -O0 -lpthread -o read.out
	clang sh_write.c -Weverything -O0 -lpthread -o write.out
debug:
	echo "Write debug make"