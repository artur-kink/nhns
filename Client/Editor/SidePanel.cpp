#include "SidePanel.hpp"

SidePanel::SidePanel(){
    setFormat(Panel::BindRight | Panel::VerticalStretch);
    bg.color = Color::Red;
    bg.color.a = 0.5f;
    
    add(&bg);
    setSize(150, 1);
    
    headerLabel.setString(8, Color::White, "Editor Panel");
    headerLabel.x = 1;
    headerLabel.y = 1;
    add(&headerLabel);

    mapName.setPosition(1, 34);
    mapName.setSize(150, 8);
    mapName.setString(8, Color::White, "unnamed");
    add(&mapName);
}

void SidePanel::onResize(int w, int h){
    Panel::onResize(w, h);
    bg.setSize(width, height);
}