.PHONEY: ALL
ALL:
	@make 1_print_char
	@make 2_change_format
	@make 3_keyboard_mouse

%: %.c
	@mkdir -p bin
	gcc -o bin/$@ -lncurses $<
