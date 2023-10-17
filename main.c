#include <SDL2/SDL.h> 
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 720;

int printError(char *errorString)
{
  printf("%s error: %s", errorString, SDL_GetError());
  return 1;
}

SDL_Window* windowCreation(SDL_Window *win, const char *Title)
{
  win = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if(win == NULL)
  {
    printError("Window creation");
  }
    return win;
}

SDL_Renderer* createRenderer(SDL_Renderer *ren, SDL_Window *win)
{
  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(ren == NULL)
  {
    printError("Renderer creation");
  }
  return ren;
}

SDL_Surface* loadImage(SDL_Surface *bmp, const char *imagePath)
{
  bmp = SDL_LoadBMP(imagePath);
  if(bmp == NULL)
  {
    printError("Load image");
  }
  return bmp;
}

SDL_Texture* createTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Surface *bmp)
{
  tex = SDL_CreateTextureFromSurface(ren, bmp);
  if(tex == NULL)
  {
    printError("Create texture");
  }
  return tex;
}
int main(int argc, char *argv[])
{
  const char *Title = "Hello nootshell!!";
  const char *imagePath = "./noot.bmp";

  SDL_Window *win = NULL;
  SDL_Renderer *ren = NULL;
  SDL_Surface *bmp = NULL;
  SDL_Texture *tex = NULL;

  win = windowCreation(win, Title); 
  ren = createRenderer(ren, win);
  bmp = loadImage(bmp, imagePath);
  tex = createTexture(tex, ren, bmp);
  SDL_FreeSurface(bmp);

  for(int i = 0; i < 3; ++i)
  {
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
    SDL_Delay(2000);
  }

  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

