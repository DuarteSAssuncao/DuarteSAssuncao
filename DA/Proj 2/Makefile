all:
	@mkdir -p obj/
	@+$(MAKE) -C src && mv src/main .
	@echo "\n\033[32mCompilation Finished\033[37m\n"

clean:
	rm -rf .ninja_log build/ doc/html/ doc/latex/ main main.exe obj/
