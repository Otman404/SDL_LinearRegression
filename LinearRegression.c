#include "LinearRegression.h"


Point* createPoint(double x, double y){
    Point *point = (Point*)malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    return point;
}

Elem* createElem(Point *point){
    Elem *new_elem = (Elem*)malloc(sizeof(Elem));
    new_elem->point = point;
    new_elem->next = NULL;
    return new_elem;
}

List* createList(){
    List *list = (List*)malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    return list;
}

Model* initModel(double a, double b, double lr){
    Model *model = (Model*)malloc(sizeof(Model));
    model->a = a;
    model->b = b;
    model->lr = lr;
    return model;
}

void addPointToList(List **list, Point *point){
    Elem *new_elem = createElem(point);
    if((*list)->first == NULL){
        (*list)->first = new_elem;
        (*list)->last = new_elem;
        return;
    }

    (*list)->last->next = new_elem;
    (*list)->last = new_elem;
}

void update_model(Model*model,List *dataList){

    double a = model->a;
    double b = model->b;
    double lr = model->lr;


    Elem *dataElem; /* element of a linkedList, contains: Point *point, ELem *next */


    for(dataElem=dataList->first;dataElem!=NULL;dataElem=dataElem->next){

            double x = (dataElem->point->x)/win_Width;
            double real_y = (dataElem->point->y)/win_Height;

            double predicted_y = a*x+b;
            double error =  real_y - predicted_y;

            a = a + (error*x)*lr;
            b = b + error*lr;

    }

    model->a = a;
    model->b = b;
    printf("a=%.2lf b=%.2lf lr=%.2lf\n",a,b,lr);
}
