#Project Makefile

all: client server

client:
	@echo ""
	@echo "Compiling client"
	make -C Client/

server:
	@echo ""
	@echo "Compiling server"
	make -C Server/

clean:
	@echo ""
	@echo "Compiling client"
	make -C Client/ clean
	make -C Server/ clean

tools: spriteparser shaderparser audioparser mapcompiler

spriteparser:
	@echo ""
	@echo "Compiling Sprite Parser"
	make -C Tools/SpriteParser/

shaderparser:
	@echo ""
	@echo "Compiling Shader Parser"
	make -C Tools/ShaderParser/

audioparser:
	@echo ""
	@echo "Compiling Audio Parser"
	make -C Tools/AudioParser/

mapcompiler:
	@echo ""
	@echo "Compiling Map Compiler"
	make -C Tools/MapCompiler/

tests:
	make -C Tools/Tests/

ui:
	make -C Tools/Tests/ ui
