#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Uint64 lastFrameTime = 0;
int windowWidth = 1280;
int windowHeight = 720;

struct Ball
{
  double x;
  double y;
  double width;
  double height;
  double vX;
  double vY;
} ball;

SDL_Rect ballRect;

int initialize_sdl(void)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    return false;
  }

  window = SDL_CreateWindow("Hello, SDL2!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0);

  if (window == NULL)
  {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (renderer == NULL)
  {
    SDL_DestroyWindow(window);
    printf("Error creating renderer: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  return true;
}

void update(void)
{

  Uint64 delta = SDL_GetTicks64() - lastFrameTime;
  lastFrameTime = SDL_GetTicks64();

  printf("delta: %f\n", 1000.0f / delta);

  ball.x += ball.vX * delta;
  ball.y += ball.vY * delta;

  if (ball.x < 0)
  {
    ball.x = 0;
    ball.vX *= -1;
  }
  else if (ball.x + ball.width > windowWidth)
  {
    ball.x = windowWidth - ball.width;
    ball.vX *= -1;
  }

  if (ball.y < 0)
  {
    ball.y = 0;
    ball.vY *= -1;
  }
  else if (ball.y + ball.height > windowHeight)
  {
    ball.y = windowHeight - ball.height;
    ball.vY *= -1;
  }

  ballRect.x = ball.x;
  ballRect.y = ball.y;
  ballRect.w = ball.width;
  ballRect.h = ball.height;

  // SDL_Delay(timeToWait);
}

void render(void)
{
  SDL_SetRenderDrawColor(renderer, 255, 160, 160, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
  SDL_RenderFillRect(renderer, &ballRect);

  SDL_RenderPresent(renderer);
}

int main(void)
{

  bool runGame = initialize_sdl();

  if (!runGame)
  {
    printf("Error initializing SDL\n");
    return 1;
  }

  ball = (struct Ball){100, 100, 50, 50, 0.4, 0.1};

  while (runGame)
  {
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        runGame = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          runGame = false;
        }
        break;
      }
    }

    update();

    render();
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
