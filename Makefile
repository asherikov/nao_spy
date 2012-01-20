include ./common.mk


cmake: igm
	-mkdir build;
ifdef TOOLCHAIN
	cd build; cmake -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN} ${CMAKEFLAGS} ..;
else
	cd build; cmake ${CMAKEFLAGS} ..;
endif
	cd build; ${MAKE}


igm:
	cd ${IGM_DIR}; ${MAKE} cmake ${DEBUGFLAGS} TOOLCHAIN=${TOOLCHAIN};


clean: igm-clean
	rm -f src/*.o
	rm -rf build
	rm -rf docs

igm-clean:
	cd ${IGM_DIR}; ${MAKE} clean;


# dummy targets
.PHONY: clean

