#Server Makefile

include ../Engine/Makefile
include ../MakefileShared

LOCAL_INCLUDE_DIRS= $(LIB_INCLUDES) . ../Engine/

LOCAL_LFLAGS=$(LFLAGS) $(LOCAL_INCLUDE_DIRS:%=-I%)

LOCAL_LIBS= $(LIB_LIBS:%=-L%) -Wl,-rpath,. -L/lib/ -lrt -lpthread -L$(EXEC_PATH) -lsfml-network -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lpugixml

LOCAL_FLAGS=$(CFLAGS) $(LOCAL_INCLUDE_DIRS:%=-I%) -MMD -MP -MF

SOURCES= Server.cpp \
    Client.cpp \
    main.cpp \
    Entities/Entity.cpp \
    $(ENGINE_SOURCES:%=../Engine/%)

OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: all server clean
all: cleanexec compile

compile: $(OBJECTS)
	@echo ""
	@echo "Creating server executable"
	$(CC) -o $(EXEC_PATH)/server $(OBJECTS) $(LOCAL_LIBS)

server: $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	@echo ""
	@echo "Compiling $@"
	$(RM) $@.d
	$(CC) $(LOCAL_FLAGS) -MMD -MP -MF $@.d  -o $@ $<	

cleanexec:
	@echo ""
	@echo "Cleaning Server"
	$(RM) $(EXEC_PATH)/server

clean: cleanexec
	$(RM) $(OBJECTS)
	$(RM) $(OBJECTS:.o=.o.d)
