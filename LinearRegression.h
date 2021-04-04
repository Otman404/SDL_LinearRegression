#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define win_Width  600
#define win_Height 400
#define win_X 500
#define win_Y 100



typedef struct Point{
    double x;
    double y;
}Point;

typedef struct Elem{
    Point *point;
    struct Elem *next;
}Elem;

typedef struct List{
    Elem *first;
    Elem *last;
}List;

typedef struct Model{
    // y = ax + b
    double a; //slope
    double b; //intercept
    double lr; //learning_rate
}Model;


Point* createPoint(double,double);
Elem* createElem(Point *);
List* createList();
Model* initModel(double, double, double);
void addPointToList(List **, Point *);
void update_model(Model*,List*);


