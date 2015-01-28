#Engine Makefile

#Core engine source files
CORE_SOURCES= EngineCore.cpp

AUDIO_SOURCES = Audio/AudioObject.cpp \
    Audio/AudioManager.cpp

UI_SOURCES = Graphics/UI/InterfaceElement.cpp \
    Graphics/UI/InterfaceEvent.cpp \
    Graphics/UI/InterfaceEventHandler.cpp \
    Graphics/UI/UIManager.cpp \
    Graphics/UI/Rectangle.cpp \
    Graphics/UI/Panel.cpp \
    Graphics/UI/Label.cpp \
    Graphics/UI/TextBox.cpp \
    Graphics/UI/Window.cpp

#Graphics engine source files.
GRAPHIC_SOURCES= Graphics/BaseSprite.cpp \
    Graphics/StaticSprite.cpp \
    Graphics/AnimatedSprite.cpp \
    Graphics/LayeredSprite.cpp \
    Graphics/SpriteSet.cpp \
    Graphics/SpriteManager.cpp \
    Graphics/BaseTransformation.cpp \
    Graphics/MatrixTransformation.cpp \
    Graphics/ShaderTransformation.cpp \
    Graphics/ShaderManager.cpp \
    Graphics/Color.cpp \
    Graphics/FontHandler.cpp \
    Graphics/RenderTarget.cpp \
    Graphics/GraphicsHandler.cpp \
    Graphics/Camera.cpp \
    $(UI_SOURCES)

#Networking source files.
NETWORKING_SOURCES= Networking/Message.cpp \
    Networking/MessageIterator.cpp \
    Networking/MessageQueue.cpp \
    Networking/NetworkHandler.cpp

#Utilities source files.
#Alot of utilities are used by other modules.
UTILITY_SOURCES= Utilities/StringHelper.cpp \
    Utilities/MemoryPool.cpp \
    Utilities/Time.cpp \
    Utilities/CalendarTime.cpp \
    Utilities/Timer.cpp \
    Utilities/TandemTimer.cpp \
    Utilities/AccumulativeTimer.cpp \
    Utilities/IntervalCounter.cpp \
    Utilities/Logger.cpp \
    Utilities/LogManager.cpp \
    Utilities/ConsoleLogger.cpp\
    Utilities/FileLogger.cpp \
    Utilities/FileHandler.cpp \
    Utilities/InputHandler.cpp \
    Utilities/CollisionHelper.cpp \
    Utilities/MathHelper.cpp

CONTENT_SOURCES= Content/Tile.cpp \
    Content/Map.cpp \
    Content/MapLoader.cpp

OBJECT_SOURCES= Objects/BaseObject.cpp \
    Objects/ObjectManager.cpp \
	Objects/Region.cpp \
    Objects/RegionManager.cpp

ENGINE_SOURCES= $(CORE_SOURCES) $(UTILITY_SOURCES) $(AUDIO_SOURCES) $(GRAPHIC_SOURCES) $(NETWORKING_SOURCES) $(CONTENT_SOURCES) $(OBJECT_SOURCES)


DIRECTORIES= Utilities Audio Graphics Content Objects

ENGINE_OBJECTS=$(ENGINE_SOURCES:.cpp=.o)

CORE_OBJECTS=$(CORE_SOURCES:.cpp=.o)
UTILITY_OBJECTS=$(UTILITY_SOURCES:.cpp=.o)
AUDIO_OBJECTS=$(AUDIO_SOURCES:.cpp=.o)
GRAPHICS_OBJECTS=$(GRAPHIC_SOURCES:.cpp=.o)
CONTENT_OBJECTS=$(CONTENT_SOURCES:.cpp=.o)
OBJECT_OBJECTS=$(OBJECT_SOURCES:.cpp=.o)

