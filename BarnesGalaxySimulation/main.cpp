#include "utils.hpp"
#include "planet.hpp"
#include "quadtree.hpp"
#include "rectangle/rectangle.hpp"
#include "galaxy.hpp"

int main()
{
    srand (time(NULL));
    
    Galaxy galaxy(n_planet, height/4, 1e12, 1e12, false);
    
    galaxy.init();
    
    RenderWindow window(VideoMode(width, height), "GalaxySimulation");
    window.setFramerateLimit(60);
    
    Clock clock;
    
    float angle = 0;
    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        
        float fps = 1.f / clock.getElapsedTime().asSeconds();
        clock.restart();
        
        cout << fps << endl;
        
        Vector2i position = sf::Mouse::getPosition();
        
        window.clear();
        
        galaxy.update(0,n_planet);
        galaxy.draw(window, angle);
        
        window.display();
        
        angle = map_value(position.y, 0, height, 0, 2*PI);
    }
    
    return 0;
}
