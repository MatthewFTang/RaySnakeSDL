#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <vector>
int randBetweenPoints(int min,int max)
{
    double t = rand() /(RAND_MAX+1.0);
    t = min +t *max;
    return t;
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_WindowFlags flags ;
    SDL_Window* window = SDL_CreateWindow("SDL Test",0,0,500,500,SDL_WINDOW_METAL);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1, 0);


    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }


    struct point {
        int x;
        int y;
        int size = 1;
        float direction ;
    };
    std::vector<point> Circle;
    int n =100;

    for (int i =0; i <n ; i++)
    {
        point temp;
        int x =  randBetweenPoints(0,600);
        int y =  randBetweenPoints(0,600);
        temp.x=x;
        temp.y =y;
        float direction = (rand()/(RAND_MAX+1.0)) *M_PI;
        temp.direction=direction;
        Circle.push_back(temp);
    }
    bool running = true;
    SDL_Event e;
    float VEL = 2;
    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);


        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255,155,155,255);

        // Add your rendering code here
        for (auto  &c:Circle)
        {
            SDL_Rect rect ;

            rect.x=c.x;
            rect.y= c.y;
            rect.h=10;
            rect.w=40;
            c.x += (int)(VEL*std::cos(c.direction ));
            c.y += (int)(VEL*std::sin(c.direction));
            if (c.x > 600 || c.x <0 || c.y <0 ||c.y>600)
            {
                if (c.x >600)
                    c.x = c.x-600;
                else if (c.x <0)
                    c.x +=600;
                else if (c.y<0)
                    c.y+=600;
                else if (c.y >600)
                    c.y -=600;
            }
            SDL_RenderDrawRect(renderer,&rect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

