#ShaderParser Makefile

include ../../Engine/Makefile
include ../../MakefileShared

LOCAL_INCLUDE_DIRS= $(LIB_INCLUDES) . ../../Engine/

LOCAL_LIBS= $(LIB_LIBS:%=-L %) -Wl,-rpath,. -L$(EXEC_PATH) -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -ldl -lpugixml -L$(PROJECT_PATH)/glew-1.7.0/lib -lGLEW

LOCAL_FLAGS=$(CFLAGS) $(LOCAL_INCLUDE_DIRS:%=-I%) -MMD -MP -MF

SOURCES= main.cpp \
    $(ENGINE_SOURCES:%=../../Engine/%)

OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: all shaderparser cleanexec clean

all: cleanexec shaderparser

shaderparser: $(OBJECTS)
	@echo ""
	@echo "Creating shaderparser executable"
	$(CC) -o $(EXEC_PATH)/shaderparser $(OBJECTS) $(LOCAL_LIBS)

$(OBJECTS): %.o: %.cpp
	$(RM) $@.d
	$(CC) $(LOCAL_FLAGS) -MMD -MP -MF $@.d  -o $@ $<

cleanexec:
	$(RM) $(EXEC_PATH)/shaderparser

clean: cleanexec
	$(RM) $(OBJECTS)
	$(RM) $(OBJECTS:.o=.o.d)
