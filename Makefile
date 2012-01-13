include ./common.mk


cmake:
	-mkdir build;
ifdef TOOLCHAIN
	cd build; cmake -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN} ${CMAKEFLAGS} ..;
else
	cd build; cmake ${CMAKEFLAGS} ..;
endif
	cd build; ${MAKE}


clean:
	rm -f src/*.o
	rm -rf build
	rm -rf docs


# dummy targets
.PHONY: clean

