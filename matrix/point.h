struct point{
  double x;
  double y;
};

struct ll_point{
  point data;
  ll_point* next_data;
};

class ll_point_head{
private:
  ll_point* head_data;
  int num_data;

public:
  ll_point_head();
  ~ll_point_head();
  ll_point* get_head_data();
  ll_point* get_last_data();
  int get_num_data();
  void add_to_last(ll_point* src);
  void print_all_data();
};

ll_point_head* input_points();
double** convert_ll(ll_point_head* data); // convert a ll_point_head linked list to a 2D double array, arr[][0] stores x, arr[][1] stores y
