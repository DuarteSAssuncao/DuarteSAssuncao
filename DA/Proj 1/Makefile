all:
	@mkdir -p obj/
	@+$(MAKE) -C src && mv src/main .
	@echo "\nCompilation finished\n"

clean:
	rm -rf .ninja_log build/ doc/html/ doc/latex/ main main.exe obj/
