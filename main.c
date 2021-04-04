#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LinearRegression.h"
#include <SDL2/SDL.h>




typedef struct RectElem{
    SDL_Rect *rect;
    struct RectElem *next;
}RectElem;

RectElem* createRectElem(SDL_Rect *rect){
    RectElem *newRect = (RectElem*)malloc(sizeof(RectElem));
    newRect->rect = rect;
    newRect->next = NULL;
    return newRect;
}

void insertRect(RectElem **rectangles, SDL_Rect *rect){
    RectElem *newRectElem;
    newRectElem = createRectElem(rect);

    RectElem *curr = (*rectangles);

    if(curr == NULL){
        (*rectangles) = newRectElem;
        return ;
    }
    while(curr->next != NULL)
        curr = curr->next;
    curr->next = newRectElem;
}

void drawRectangles(RectElem *rectangles, SDL_Renderer *renderer){

    RectElem *pt;
    for(pt=rectangles;pt!=NULL;pt=pt->next)
        SDL_RenderFillRect(renderer,pt->rect);

}





void drawLine(Model*model,SDL_Renderer*renderer){

    double x1,y1,x2,y2;


    x1 = 0;
    y1 = model->a*x1 + model->b;
    x2 = 1;
    y2 = model->a*x2 + model->b;

    x1*=win_Width;
    y1*=win_Height;
    x2*=win_Width;
    y2*=win_Height;

    y1 = win_Height - y1;
    y2 = win_Height - y2;

    SDL_SetRenderDrawColor(renderer,255,0,0,255);

    SDL_RenderDrawLine(renderer, x1,y1,x2,y2);

}



int main(int c, char *T[]){


    List *dataList = createList();
    Model *model = initModel(1,0,0.01);
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!= 0)
    {
        SDL_Log("failed: ",SDL_GetError());
        exit(-1);
    }
    RectElem *rectangles = NULL;;

    SDL_Window *window;
    window = SDL_CreateWindow("Linear Regression",win_X,win_Y,win_Width,win_Height,SDL_WINDOW_OPENGL);
    if(window==NULL)
    {
        printf("%s\n",SDL_GetError());
        exit(-1);
    }
    SDL_Event windowEvent;

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    while(1)
    {
        update_model(model,dataList);
        if(SDL_PollEvent(&windowEvent))
        {
            if(windowEvent.type == SDL_QUIT)
                break;

            if(windowEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                Point *p = (Point*)malloc(sizeof(Point));
                p->x = windowEvent.button.x;
                p->y = win_Height - windowEvent.button.y;
                addPointToList(&dataList,p);

                SDL_Rect *rect;
                rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
                rect->x = windowEvent.button.x;
                rect->y = windowEvent.button.y;
                rect->h = 10;
                rect->w = 10;
                insertRect(&rectangles,rect);

                drawLine(model,renderer);

            }
        }
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);
        drawLine(model,renderer);
        SDL_SetRenderDrawColor(renderer,0,0,255,255);


        drawRectangles(rectangles,renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
