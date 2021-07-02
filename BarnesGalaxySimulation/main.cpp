#include "utils.hpp"
#include "planet.hpp"
#include "quadtree.hpp"
#include "rectangle.hpp"
#include "galaxy.hpp"

int main()
{
    srand (time(NULL));
    
    Galaxy galaxy(n_planet, height/4, 0.1, 0.2, true);
    
    galaxy.init();
    
    RenderWindow window(VideoMode(width, height), "GalaxySimulation");
    window.setFramerateLimit(60);
    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        
        galaxy.update();
        
        galaxy.draw(window);
        
        window.display();
    }
    
    return 0;
}
