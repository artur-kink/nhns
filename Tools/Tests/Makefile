#Test Projects Makefile

include ../../Engine/Makefile
include ../../MakefileShared

LOCAL_INCLUDE_DIRS= $(LIB_INCLUDES) . ../../Engine/

LOCAL_LIBS= $(LIB_LIBS:%=-L %) -Wl,-rpath,. -L$(EXEC_PATH) -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -ldl -lpugixml -L$(PROJECT_PATH)/glew-1.7.0/lib -lGLEW

LOCAL_FLAGS=$(CFLAGS) $(LOCAL_INCLUDE_DIRS:%=-I%) -MMD -MP -MF

TEST_UI_SOURCES= UI/main.cpp \
    $(ENGINE_SOURCES:%=../../Engine/%)

TEST_UI_OBJECTS=$(TEST_UI_SOURCES:.cpp=.o)

TEST_CLIENT_SOURCES=ClientServer/client.cpp \
    $(ENGINE_SOURCES:%=../../Engine/%)

TEST_CLIENT_OBJECTS=$(TEST_CLIENT_SOURCES:.cpp=.o)

TEST_SERVER_SOURCES=ClientServer/server.cpp \
    $(ENGINE_SOURCES:%=../../Engine/%)

TEST_SERVER_OBJECTS=$(TEST_SERVER_SOURCES:.cpp=.o)

OBJECTS= $(TEST_UI_OBJECTS) \
    $(TEST_CLIENT_OBJECTS) \
    $(TEST_SERVER_OBJECTS)

.PHONY: all ui clientserver cleanexec clean

all: cleanexec ui clientserver

ui: $(TEST_UI_OBJECTS)
	@echo ""
	@echo "Creating ui test executable"
	$(CC) -o $(EXEC_PATH)/ui $(TEST_UI_OBJECTS) $(LOCAL_LIBS)

clientserver: $(TEST_CLIENT_OBJECTS) $(TEST_SERVER_OBJECTS)
	@echo ""
	@echo "Creating client-server test executables"
	$(CC) -o $(EXEC_PATH)/testclient $(TEST_CLIENT_OBJECTS) $(LOCAL_LIBS)
	$(CC) -o $(EXEC_PATH)/testserver $(TEST_SERVER_OBJECTS) $(LOCAL_LIBS)

$(OBJECTS): %.o: %.cpp
	$(RM) $@.d
	$(CC) $(LOCAL_FLAGS) -MMD -MP -MF $@.d  -o $@ $<

cleanexec:
	$(RM) $(EXEC_PATH)/ui

clean: cleanexec
	$(RM) $(OBJECTS)
	$(RM) $(OBJECTS:.o=.o.d)
