T=$(wildcard src/*.cpp)
NAME=$(basename $(notdir $T))
OBJ = $(NAME:%=obj/%.o)
LIBS = $(NAME:%=../libs/lib%.so)

.SECONDARY:  $(OBJ)

.NONINTERMEDIATE: $(LIBS)

plugin: obj __lines_for_space__ $(LIBS)
	@echo "  Tworzenie wtyczek zakonczone."
	@echo


test:
	@echo T: $T
	@echo NAME: $(NAME)
	@echo OBJ: $(OBJ)
	@echo LIBS: $(LIBS)


obj:
	mkdir obj

CPPFLAGS=-Wall -fPIC -pedantic -std=c++17 -Iinc -I../inc
LDFLAGS=-Wall -shared

__lines_for_space__:
	@echo

../libs/lib%.so: obj/%.o
	@g++ ${LDFLAGS} -o $@ $^
	@echo "  Wtyczka $(subst Interp4,,$*) zostala utworzona."
	@echo


obj/%.o: src/%.cpp ../inc/Interp4Command.hh inc/%.hh
	@g++ -c ${CPPFLAGS} -o $@ $<
	@echo Objekt $(subst Interp4,,$*) został utworzony


clean:
	@echo Usuwanie: $(wildcard obj/*)
	@rm -f obj/*
