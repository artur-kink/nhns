#Client Makefile

include ../Engine/Makefile
include ../MakefileShared

LOCAL_INCLUDE_DIRS= $(LIB_INCLUDES) . ../Engine/

LOCAL_LFLAGS=$(LFLAGS) $(LOCAL_INCLUDE_DIRS:%=-I%)

LOCAL_LIBS= $(LIB_LIBS:%=-L%) -Wl,-rpath,. -L$(EXEC_PATH) -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -ldl -lpugixml -L$(PROJECT_PATH)/glew-1.7.0/lib -lGLEW

LOCAL_FLAGS=$(CFLAGS) $(LOCAL_INCLUDE_DIRS:%=-I%) -MMD -MP -MF

SOURCES= main.cpp \
	GameResources.cpp \
	Client.cpp \
	$(ENGINE_SOURCES:%=../Engine/%)

OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: all client clean
all: cleanexec client

client: $(OBJECTS)
	@echo ""
	@echo "Creating client executable"
	$(CC) -o $(EXEC_PATH)/client $(OBJECTS) $(LOCAL_LIBS)

$(OBJECTS): %.o: %.cpp
	@echo ""
	@echo "Compiling $@"
	$(RM) $@.d
	$(CC) $(LOCAL_FLAGS) -MMD -MP -MF $@.d  -o $@ $<	

cleanexec: 
	@echo ""
	@echo "Cleaning Client"
	$(RM) $(EXEC_PATH)/client

clean: cleanexec
	$(RM) $(OBJECTS)
	$(RM) $(OBJECTS:.o=.o.d)
