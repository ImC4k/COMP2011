#include "utils.h"
#include "cafe.h"

// calculate average rating of a cafe
float calc_avg_rating(const Cafe* c)
{
	float sum_ratings = 0.0;
	for (int i = 0 ; i < c->num_of_ratings ; i++ )
		sum_ratings += c->ratings[i].rating;

	float avg_rating;

	if (c->num_of_ratings > 0)
		avg_rating = sum_ratings / static_cast<float>(c->num_of_ratings);
	else
		avg_rating = 0;

	return avg_rating;
}

// load cafes from a given file
void load_cafe(Cafe cafes[], int *cafe_num, string filename)
{
	void add_cafe(Cafe[], int*, const char[], const Point*);
	*cafe_num = 0;
	Point p;
	char cafe_name[MAX_NAME_LENGTH];
	ifstream ifs(filename);
	while (!ifs.eof()){
		ifs >> cafe_name >> p.x >> p.y;
		add_cafe(cafes, cafe_num, cafe_name, &p); // added & sign to cafe_num
	}
	ifs.close();
}

// load cafe ratings from a given file
void load_rating(Cafe cafes[], int cafe_num, User users[], int num_users, string filename)
{
	void add_rating(Cafe*, User*, float);
	ifstream ifs(filename);
	int num_rating, id;
	float rating;
	for (int i = 0 ; i < cafe_num ; i++)
	{
		ifs >> num_rating;
		for (int j = 0 ; j < num_rating ; j++)
		{
			ifs >> id >> rating;
			User *user = search_user_by_id(users, num_users, id);
			if (user != nullptr)
				add_rating(&cafes[i], user, rating);
			else
				cout << "User ID: " << id << " NOT FOUND!" << endl;
		}
	}
	ifs.close();
}

// Implement the following functions
// add a Cafe object to the Cafe array, cafes.
void add_cafe(Cafe cafes[], int* cafe_num, const char cafe_name[],  const Point* location)
{
	cout<<*cafe_num<<endl;
	//TODO 2 Add Your Code Here
	if(*cafe_num >= MAX_CAFE_NUM){
		cout<<"Too many cafe"<<endl;
		return;
	}
	Cafe new_cafe;
	strcpy(new_cafe.name, cafe_name);
	new_cafe.location = *location;
	new_cafe.num_of_ratings = 0;
	cafes[*cafe_num] = new_cafe;
	(*cafe_num)++;
}

// Add a Rating object to the Cafe c.
// You may call the search_user_by_id() function for finding the address of the corresponding User object.
void add_rating(Cafe *c, User *user, float rating)
{
	//TODO 2 Add Your Code Here
	if(c->num_of_ratings >= MAX_RATINGS_NUM){
		cout<<"Too many ratings"<<endl;
		return;
	}
	Rating new_rating; // Create a new Rating structure
	new_rating.user_ptr = user; // assign user_ptr
	new_rating.rating = rating; // assign corresponding rating
	c->ratings[c->num_of_ratings] = new_rating; // put new_rating to ratings array
	(c->num_of_ratings)++; // update num_of_ratings

}


// Similar to lab 8, implement this function to  show the cafe's name, location and its average rating.
void print_cafe(const Cafe* c)
{
	//TODO 2 Add Your Code Here
	cout << "< " << c->name << ", Coordinates: (" << c->location.x << "," << c->location.y <<"), AVG_rating: " << calc_avg_rating(c) << " >" << endl;
}

// This function show the cafe ratings by each user and the average rating
void print_cafe_rating_by_user(const Cafe* c)
{
	//TODO 2 Add Your Code Here
	cout << c->name << ", Coordinates: (" << c->location.x << "," << c->location.y <<")"<<endl;
	for(int i = 0; i < c->num_of_ratings; i++){
		cout<<c->ratings[i].user_ptr->name<<" Rating: "<<c->ratings[i].rating<<endl;
	}
	cout<<"AVG_rating: "<<calc_avg_rating(c)<<endl<<endl;

}

// Recommend best options of cafe w.r.t rating and distance
void recommend_best_options(const Cafe cafes[], const Point* my_location, int cafe_num)
{
	//TODO 2 Add Your Code Here
	// float cafe_distances[MAX_CAFE_NUM] = {}; // for comparing distance
	// for(int i = 0; i < cafe_num; i++){ // create distance array
	// 	cafe_distances[i] = euclidean_distance(*my_location, cafes[i].location);
	// }
	// float shortest_distance = cafe_distances[0];
	// int shortest_distance_index = 0; // second attempt
	// for(int i = 1; i < cafe_num; i++){
	// 	if(cafe_distances[i] < shortest_distance){
	// 		shortest_distance = cafe_distances[i];
	// 		shortest_distance_index = i; // second attempt
	// 	}
	// }
	//
	// bool will_print_cafes[MAX_CAFE_NUM] = {};
	// for(int i = 0; i < MAX_CAFE_NUM; i++){
	// 	will_print_cafes[i] = true;
	// }
	// // will_print_cafes[shortest_distance_index] = true;
	// // will_print_cafes[highest_rating_index] = true;
	// // for(int i = 0; i < cafe_num; i++){
	// // 	if(cafe_distances[i] == shortest_distance || cafe_ratings[i] == highest_rating){ // must print shortest_distance and highest rating
	// // 		print_cafe(&cafes[i]);
	// // 		will_print_cafes[i] = true;
	// // 	}
	// // 	// else{
	// // 	// 	if(cafe_ratings[i] > cafe_ratings[shortest_distance_index] || cafe_distances[i] < cafe_distances[highest_rating_index]){
	// // 	// 		print_cafe(&cafes[i]);
	// // 	// 	}
	// // 	// }
	// // 	// if(cafe_distances[i] == shortest_distance || cafe_ratings[i] >= cafe_ratings[shortest_distance_index]){ // second attempt
	// // 	// 	print_cafe(&cafes[i]);
	// // 	// }
	// // }
	//
	// // for(int i = 0; i < cafe_num; i++){ // version 2 trial
	// // 	for(int j = 0; j < cafe_num; j++){
	// // 		// if(j == shortest_distance_index || j == highest_rating_index) continue;
	// // 		// if(will_print_cafes[j] == false) continue;
	// // 		if()
	// // 		if(cafe_distances[i] > cafe_distances[j] && cafe_ratings[i] < cafe_ratings[j]){
	// // 			will_print_cafes[i] = false;
	// // 			break;
	// // 		}
	// // 	}
	// // }
	// // for(int i = 0; i < cafe_num; i++){
	// // 	if(will_print_cafes[i]){
	// // 		print_cafe(&cafes[i]);
	// // 	}
	// // }
	//
	// if(shortest_distance_index == highest_rating_index), then return that cafe object
	// else

	float* cafe_distances = new float[cafe_num];
	for(int i = 0; i < cafe_num; i++){
		cafe_distances[i] = euclidean_distance(*my_location, cafes[i].location);
	}

	float* cafe_ratings = new float[cafe_num];
	for(int i = 0; i < cafe_num; i++){
		cafe_ratings[i] = calc_avg_rating(&cafes[i]);
	}

	if(cafe_num == 0){
		cout<<"There is no cafe!"<<endl;
	}
	else if(cafe_num == 1){
		print_cafe(&cafes[0]);
		return;
	}

	int* wont_print_cafes = new int[cafe_num];
	for(int i = 0; i < cafe_num; i++){
		wont_print_cafes[i] = -1;
	}
	// int wont_print_cafes_index = 0;

	for(int i = 0; i < cafe_num; i++){
		for(int j = 0; j < cafe_num; j++){
			if(i==j){
				continue;
			}
			if(cafe_distances[i] > cafe_distances[j] && cafe_ratings[i] < cafe_ratings[j]){
				wont_print_cafes[i] = i;
				// wont_print_cafes_index++;
				break;
			}
		}
	}

	cout<<"---------------debug---------------"<<endl;
	for(int i = 0; i < cafe_num; i++){
		cout<<cafes[i].name<<"\t"<<cafe_distances[i]<<"\t"<<cafe_ratings[i]<<endl;
	}
	cout<<"wont_print_cafes: "<<endl;
	for(int i = 0; i < cafe_num; i++){
		cout<<wont_print_cafes[i]<<"  ";
	}
	// float highest_rating = cafe_ratings[0];
	// int highest_rating_index = 0;
	// for(int i = 1; i < cafe_num; i++){
	// 	if(cafe_ratings[i] > highest_rating){
	// 		highest_rating = cafe_ratings[i];
	// 		highest_rating_index = i;
	// 	}
	// }
	// cout<<"\nshortest distance (corresponding rating): "<<shortest_distance<< " ("<<cafe_ratings[shortest_distance_index]<<") "<<endl<<"highest rating: "<<highest_rating<<endl;
	cout<<"\n---------------debug---------------"<<endl;

	for(int i = 0; i < cafe_num; i++){
		if(wont_print_cafes[i] == -1){
			print_cafe(&cafes[i]);
		}
	}
	delete[] wont_print_cafes;
	wont_print_cafes = nullptr;

	delete[] cafe_distances;
	cafe_distances = nullptr;
	delete[] cafe_ratings;
	cafe_ratings = nullptr;

	// cout<<"---------Ben's attempt---------"<<endl;
	// 	if (cafe_num == 0)
	// 	return;
	// else if (cafe_num == 1) {
	// 	print_cafe(&cafes[0]);
	// 	return;
	// }
	//
	// 		// use an array to save the cafe index which it is both 2 condition are not as good
	// 		// as some other cafe.
	// 		// when printing, skip those cafe in the index array
	//
	// int *index = new int[cafe_num];
	// int cafeIgnore = 0;
	// for (int i = 0; i < cafe_num; i++) { // initialized index array to all -1
	// 	index[i] = -1;
	// }
	// for (int i = 0; i < cafe_num; i++) { // select one cafe item
	// 	for (int j = 0; j < cafe_num; j++) { // compare with all other cafe items
	// 		if (i == j) // if comparing itself
	// 			continue; // then skip
	// 		if (calc_avg_rating(&cafes[i]) < calc_avg_rating(&cafes[j]) &&
	// 			euclidean_distance(cafes[i].location, *my_location) > euclidean_distance(cafes[j].location, *my_location)) { // if rating is smaller and distance is longer than one cafe
	//
	// 			index[cafeIgnore] = i; // then add its index to index array
	// 			cafeIgnore++; // num of cafe to ignore increment
	// 			break;
	// 		}
	// 	}
	// }
	// for (int i = 0, count = 0; i < cafe_num; i++) {
	// 	if (i == index[count]) { // if cafe
	// 		count++;
	// 		continue;
	// 	}
	// 	print_cafe(&cafes[i]);
	// }
	// delete[] index;
	// return;

}
