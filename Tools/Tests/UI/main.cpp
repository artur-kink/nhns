#include "EngineCore.hpp"
#include "Utilities/LogManager.hpp"
#include "Utilities/ConsoleLogger.hpp"
#include "Utilities/Logger.hpp"
#include "Graphics/UI/UIManager.hpp"
#include "Graphics/UI/Label.hpp"
#include "Graphics/UI/Panel.hpp"
#include "Graphics/UI/Rectangle.hpp"

class TestEngine:public EngineCore{
public:
    UIManager ui;
    
    Panel testPanel;
    Label testLabel;

    TestEngine(){
        StringHelper::init();
        Log >> new ConsoleLogger();
        Log.setLevelFilter(Logger::ll_Debug);
        
        graphics.setSize(800, 600);
        graphics.setCamera(0);
        ui.setSize(800, 600);
        testLabel.setString(12, Color::White, "UI Test");
        testLabel.setPosition(0, 0);
        ui.addElement(&testLabel);
        testPanel.setPosition(20, 20);
        testPanel.add(new Label(0, 0, 10, Color::White, "Test2"));
        ui.addElement(&testPanel);
        ui.addElement(new Rectangle(100, 100, 50, 50, Color::Red));
    }
    
    virtual void update(unsigned int frameTime){
        ui.update(frameTime, 0, 0, false, false);
    }

    /**
     * Base draw call.
     * @param frameTime Time of draw.
     */
    virtual void draw(unsigned int frameTime){
        ui.draw(&graphics);
    }
};

int main(int argc, char** argv){
    TestEngine engine;
    engine.init();
    engine.start();
}
