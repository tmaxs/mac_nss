### Конфигурация. ###################################
CC = gcc 
SOURCES = main.c mac_nss_int.c mac_nss_load_lib.c mac_nss_parser.c
MODULES = mac_lib_local.so 
	
### Правила. ########################################
# Служебный целевой модуль
.PHONY:		all clean
# Стандартный целевой модуль: компиляция всех файлов.
all:	$(MODULES) main 
	
# Удаление всего чего насобирали.
clean:
	rm -f	$(MODULES) main 

# Собираем основные файлы.
main:		$(SOURCES) 
	$(CC)	$(CFLAGS)	-Wl,-export-dynamic -o $@ $^ -ldl
					
# Собираем библиотеки.
$(MODULES): %.so:		%.c
	$(CC)	$(CFLAGS)	-fPIC -shared -o $@ mac_lib_local.c
####################################################
