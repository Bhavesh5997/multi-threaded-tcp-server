all:
	make -C ./server/build
	make -C ./client/build
clean:
	make -C ./server/build clean
	make -C ./client/build clean
	@rm -f output.txt
