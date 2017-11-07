//============================================================================
// Name        : cafe.h
// Author      : Serafeim Papadias
// Description : comp2017 2017S
//============================================================================

#ifndef LAB8_CAFE_H_
#define LAB8_CAFE_H_

// TODO 7: Include appropriate header
#include "point.h"


// TODO 5: Definite all the appropriate global variables here
const int MAX_NAME_LENGTH = 10;
const int MAX_CAFE_NUM = 10;
const int MAX_RATING_NUM = 10;


// TODO 1: Create the necessary Cafe struct here
struct Cafe{
  char name[MAX_NAME_LENGTH+1];
  int num_of_ratings;
  float ratings[MAX_RATING_NUM];
  Point location;
};


// TODO 6: Fill in the appropriate function declarations here.

float calc_avg_rating(const Cafe&);

void print_cafe(const Cafe&);

void add_cafe(Cafe[MAX_CAFE_NUM], int&, const char[MAX_NAME_LENGTH], const Point&);

void add_rating(Cafe[MAX_CAFE_NUM], int, float);

void recommend_based_on_rating(const Cafe[MAX_CAFE_NUM], int);

void recommend_based_on_distance(const Cafe[MAX_CAFE_NUM], const Point&, int, int);


#endif /* LAB8_CAFE_H_ */
