.DEFAULT_GOAL:=all
clean:
	cd app && find -name "*.o" -type f -delete
	cd core && find -name "*.o" -type f -delete
	cd package && find -name "*.o" -type f -delete
	cd test && find -name "*.o" -type f -delete