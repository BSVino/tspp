# clanmod Metamod Plugin sm_cstrike_mm.dll and sm_cstrike_mm_i386.so Makefile for win32 and linux


ifeq ($(OS),Windows_NT)

	COMPILER = mingw32-gcc
	LINKER   = dllwrap
	OFLAGS   = -O2 -fno-exceptions -fno-rtti

# Delete '97 .. moves files to recycle bin .. http://www.easytools.com/Downloads/Freebies/
	DELCMD   = -rm -f
	
	CFLAGS   =
	LFLAGS   = -mdll -mwindows -lstdc++ -k
	VERSION  = version.o
	RC       = tspp_mm.rc
	DLLNAME  = tspp_mm.dll
	
else

	COMPILER = gcc
	LINKER   = gcc
	OFLAGS   = -w -O2 -m386 -ffast-math -funroll-loops \
	-fomit-frame-pointer -fexpensive-optimizations \
	-malign-loops=2 -malign-jumps=2 -malign-functions=2
	
	DELCMD   = -rm -f
	
	CFLAGS   = -fPIC -Dstricmp=strcasecmp -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp -Dstrcmpi=strcasecmp 
	
	LFLAGS   = -shared -ldl
	VERSION  = 
	RC       = 
	DLLNAME  = tspp_mm_i386.so

endif

OFLAGS += 
CFLAGS += -Wall $(OFLAGS) -g0
LFLAGS += -s


METADIR = metamod


INCLUDEDIRS = -I. -I$(METADIR) -Iengine -Icommon -Ipm_shared -Idlls -Ilibini


OBJ =	dllapi.o 		\
	engine_api.o 		\
	meta_api.o 		\
	tspp.o			\
  $(VERSION)


DOCC = $(COMPILER) $(CFLAGS) $(INCLUDEDIRS) -o $@ -c $<
DOO = $(LINKER) -o $@ $(OBJ) $(LFLAGS)


$(DLLNAME) : $(OBJ) 
	$(DOO)
	cp $(DLLNAME) ../lib

clean:
	$(DELCMD) $(OBJ) $(DLLNAME) *.depend


./$(VERSION): ./$(RC)
	windres -o $@ -i $<
	
./$(VERSION): ./$(RC) vers_plugin.h


# pull in dependency info for *existing* .o files
-include $(OBJ:.o=.depend)


./%.o: ./%.cpp
	$(DOCC)
	$(COMPILER) -MM $(INCLUDEDIRS) $< > $*.depend

./%.o: ./%.c
	$(DOCC)
	$(COMPILER) -MM $(INCLUDEDIRS) $< > $*.depend

