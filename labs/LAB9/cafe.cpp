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
	//TODO 2 Add Your Code Here
	Cafe* new_cafe = new Cafe;
	strcpy(new_cafe->name, cafe_name);
	new_cafe->location = *location;
	new_cafe->num_of_ratings = 0;
	(*cafe_num)++;
	delete new_cafe;
	new_cafe = nullptr;
}

// Add a Rating object to the Cafe c.
// You may call the search_user_by_id() function for finding the address of the corresponding User object.
void add_rating(Cafe *c, User *user, float rating)
{
	//TODO 2 Add Your Code Here
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
	cout << "< " << c->name << ", Coordinates: (" << c->location.x << "," << c->location.y <<")"<<endl;
	for(int i = 0; i < c->num_of_ratings; i++){
		cout<<c->ratings[i].user_ptr->name<<" Rating: "<<c->ratings[i].rating<<endl;
	}
	cout<<"AVG_rating: "<<calc_avg_rating(c)<<endl;

}

// Recommend best options of cafe w.r.t rating and distance
void recommend_best_options(const Cafe cafes[], const Point* my_location, int cafe_num)
{
	//TODO 2 Add Your Code Here
}
