//============================================================================
// Name        : cafe.cpp
// Author      : Serafeim Papadias
// Description : comp2017 2017S
//============================================================================

// TODO 7: Include appropriate header
#include "cafe.h"




float calc_avg_rating(const Cafe& c)
{
	// Calculate average rating
	float sum_ratings = 0.0;
	for (int i = 0 ; i < c.num_of_ratings ; i++ )
		sum_ratings += c.ratings[i];

	float avg_rating;

	if (c.num_of_ratings > 0)
		avg_rating = sum_ratings / (float)c.num_of_ratings;
	else
		avg_rating = 0;
	// Return the average
	return avg_rating;
}

void print_cafe(const Cafe& c)
{
	cout << "< " << c.name << ", Coordinates: (" << c.location.x << "," << c.location.y <<"), AVG_rating: " << calc_avg_rating(c) << " >" << endl;
}


// Write the extra functions needed here

void add_cafe(Cafe cafes[], int& cafe_num, const char cafe_name[],  const Point& location)
{
	Cafe new_cafe;
	strcpy(new_cafe.name, cafe_name);
	new_cafe.num_of_ratings = 0;
	new_cafe.location = location;
	cafes[cafe_num] = new_cafe;
	cafe_num++;
}

void add_rating(Cafe cafes[], int cafe_index,  float rating)
{
	cafes[cafe_index].ratings[cafes[cafe_index].num_of_ratings] = rating;
	cafes[cafe_index].num_of_ratings++;
}

void recommend_based_on_rating(const Cafe cafes[], int cafe_num)
{
	// TODO 3: According to Part 4 in the lab description. Recommend the cafe with the highest average rating.
	int highest_rating_cafe_index = 0;
	int corr_avg_rating;
	for(int i = 1; i < cafe_num; i++){
		if(calc_avg_rating(cafes[i]) > calc_avg_rating(cafes[highest_rating_cafe_index])){
			highest_rating_cafe_index = i;
		}
	}
	print_cafe(cafes[highest_rating_cafe_index]);
}

void recommend_based_on_distance(const Cafe cafes[], const Point& my_location, int cafe_num, int N)
{
	// TODO 4: According to Part 5 in the lab description. Return the N nearest cafes (no need to sort).

	float distance_to_my_location[MAX_CAFE_NUM] = {}; // create array to store distance from my_location to each destination
	for(int i = 0; i < cafe_num; i++){
		float distance = euclidean_distance(my_location, cafes[i].location);
		distance_to_my_location[i] = distance;
	}
	float shortest_distance;

	for(int i = 0; i < N; i++){ 									//TODO: find N shortest distance from "distance_to_my_location" array
		int shortest_distance_cafe_index = 0;
		for(int j = 0, x = 0; j < cafe_num; j++){
			if(distance_to_my_location[j] == -1){ //if the index is printed already, then just skip this iteration
				continue;
			}
			if(!x){
				shortest_distance_cafe_index = j;
				shortest_distance = distance_to_my_location[j];
				x++;
			}
			if(distance_to_my_location[j] < shortest_distance){
				shortest_distance = distance_to_my_location[j];
				shortest_distance_cafe_index = j;
			}
		}
		print_cafe(cafes[shortest_distance_cafe_index]);
		distance_to_my_location[shortest_distance_cafe_index] = -1; // whenever the shortest_distance_cafe_index is printed, its corresponding distance saved in array "distance_to_my_location" is assigned -1
	}
}
