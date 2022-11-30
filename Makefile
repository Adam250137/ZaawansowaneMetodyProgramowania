T=$(wildcard src/*.cpp)
MAIN_D=$(basename $(notdir $T))
# MAIN_D = main LibInterface command
MAIN_O = $(MAIN_D:%=obj/%.o)

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall

.SECONDARY: $(MAIN_O)


interp: _plugin_ obj __lines_for_space__ $(MAIN_O)
	g++ ${LDFLAGS} -o $@  $(MAIN_O) -ldl -lxerces-c
	@echo Skompilowano $@
	@echo Uruchamianie...
	@echo ---------------
	@export LD_LIBRARY_PATH="./libs"; ./interp

test:
	@echo MAIN_D $(MAIN_D)
	@echo MAIN_O $(MAIN_O)

obj:
	mkdir obj


__lines_for_space__:
	@echo


_plugin_:
	@cd plugin; make


obj/%.o: src/%.cpp inc/Interp4Command.hh
	@g++ -c ${CPPFLAGS} -o $@ $<
	@echo Utworzono obiekt $*

clean:
	@echo Usuwanie: $(wildcard obj/* interp libs/*)
	@rm -f obj/* interp libs/*

clean_plugin:
	@cd plugin; make clean;

cleanall: clean clean_plugin