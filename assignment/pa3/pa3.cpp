/*
 *       File: pa3.cpp
 * Created on: Nov 1, 2017
 *     Author: Yao Yao (yyaoag@cse.ust.hk)
 *       Note: Implement all functions without changing any function prototype.
 *             This is the only file you should modify and submit.
 */

#include <iostream>
#include "structure.h"
using namespace std;

/*
 * Description: get the pointer to the frame through frame index.
 *
 *       video: input video structure.
 * frame_index: the index of the frame to be extracted.
 *      return: the pointer to the frame or nullptr if the frame does not exsist.
 */
Frame * GetFrame(const Video & video, const int frame_index)
{
	// your implementation
  if(frame_index > video.num_frames || frame_index < 0) // if frame_index is out of number of total frames, then return nullptr
    return nullptr;
  // return video.raw_data[frame_index];
  Frame* frame = video.first_frame;
  for(int i = 0; i < frame_index; i++){ // a counter to point to the wanted frame pointer
    frame = frame->next_frame;
  }
  return frame;
}

/*
 * Description: get the pointer to the vehicle through vehicle index.
 *
 *         video: input video structure.
 * vehicle_index: the index of the vehicle to be extracted.
 *        return: the pointer to the vehicle or nullptr if the vehicle does not exsist.
 */
Vehicle * GetVehicle(const Video & video, const int vehicle_index)
{
	// your implementation
  if(vehicle_index > MAX_VEHICLE_NUM || vehicle_index < 0) // if vehicle_index is out of bound, then return nullptr
    return nullptr;
  return video.vehicles[vehicle_index]; // get the pointer from video.vehicles[] array
}
/*
 * Description: get the pointer to vf_info of a vehicle in one frame.
 *
 *     vehicle: input vehicle structure.
 * frame_index: the frame index of the vf_info to be extracted from this vehicle.
 *      return: the pointer to the vf_info or nullptr if the vehicle does not visible in
 *              this frame.
 */
VehicleFrameInfo * GetVFInfo(const Vehicle * vehicle, const int frame_index)
{
	// your implementation
  if(vehicle == nullptr) // if no such vehicle, then return nullptr
    return nullptr;

  VehicleFrameInfo* temp_info = vehicle->first_frame_info; // obtain vehicle's first info
  if(temp_info == nullptr){ // if no info, then return nullptr
    return nullptr;
  }
	// for(; temp_info->frame_index != frame_index && temp_info != nullptr; temp_info = temp_info->next_frame_info)// loop until reach temp->frame_index reaches required frame_index
  // ;
  int i = frame_index;
  while(frame_index){
    if(temp_info == nullptr){
      return nullptr;
    }
    else{
      cout<<"not nullptr";
      temp_info = temp_info->next_frame_info;
      i--;
    }
  }
  return temp_info;
}

/*
 * Description: initialize a new frame in the video during frame processing. You need to
 *              create a new frame, and initialize this new frame and add it to the link
 *              list. In this function, you don't need to use hard copy to initialize
 *              Frame.image. Also, you don't need to analyze the vehicles in this frame
 *              (set num_vehicles of this new frame as 0 and all pointers to vehicles as
 *              nullptr).
 *
 *  video: input video structure.
 * return: true if finish and false if all frames has been processed.
 */
bool InitializeNewFrame(Video & video)
{
	// your implementation
  // handle all frame processed case
  if(video.num_processed_frames >= video.num_frames) return false;

  // handle a new frame, num_processed_frames = 0
  if(video.num_processed_frames == 0){
    Frame* current_frame = new Frame();
    current_frame->index = video.num_processed_frames;
    current_frame->image = new char*[ROWS];
    for(int i = 0; i < ROWS; i++){
      current_frame->image[i] = new char[COLS];
      for(int j = 0; j < COLS; j++){
        current_frame->image[i][j] = video.raw_data[current_frame->index][i][j];
      }
    }
    current_frame->num_vehicles = 0;
    current_frame->next_frame = nullptr;
    video.num_processed_frames++;
    video.first_frame = current_frame;
    return true;
  }

  // handle a new_frame, num_processed_frames != 0
  // current_frame is now changed to last frame's pointer

  Frame* current_frame = video.first_frame;
  for(; current_frame->next_frame != nullptr; current_frame = current_frame->next_frame)
  ;

  Frame* new_frame = new Frame(); // initialize a new frame
  new_frame->index = video.num_processed_frames; // index of frame set to num_processed_frames + 1
  new_frame->image = new char*[ROWS];
  for(int i = 0; i < ROWS; i++){ // assign values to new_frame->image
    new_frame->image[i] = new char[COLS];
    for(int j = 0; j < COLS; j++){
      new_frame->image[i][j] = video.raw_data[new_frame->index][i][j];
    }
  }
  new_frame->num_vehicles = 0;
  for(int i = 0; i < MAX_VEHICLE_NUM; i++){
    new_frame->vehicles[i] = nullptr;
  }
  new_frame->next_frame = nullptr;

  current_frame->next_frame = new_frame;
  video.num_processed_frames++;
  return true;
}

/*
 * Description: add one vf_info to the video. You need to check if the vf_info, the
 *              corresponding video and the corresponding the vehicle has been in the
 *              video before you add the VFInfo.
 *
 *              video: input video structure.
 * vehicle_frame_info: pointer to the new info to be added. (vf_info)
 *             return: return true if finish and false if
 *                     1. the frame or the vehicle of this vf_info is not in this video or
 *                     2. vf_info has already been in the list of the vehicle.
 */
bool AddVFInfo(Video & video, VehicleFrameInfo * vehicle_frame_info)
{
	// your implementation
  // handle frame number not ok
  if(vehicle_frame_info->frame_index >= video.num_processed_frames|| vehicle_frame_info->frame_index < 0){ return false;}
  if(video.vehicles[vehicle_frame_info->vehicle_index] == nullptr){
    return false;
  }
//  if(video.vehicles[vehicle_frame_info->vehicle_index]){}
//  // info already added
//  Vehicle * vehicle = GetVehicle(video, vehicle_frame_info->vehicle_index);
//
//  VehicleFrameInfo* current_info = vehicle->first_frame_info;
//  for(; current_info->next_frame_info; current_info = current_info->next_frame_info){
//    if(current_info == vehicle_frame_info){
//      return false;
//    } // current_info is updated to the last node of info ll for the vehicle
//  }
//
//  current_info->next_frame_info = vehicle_frame_info;

  // handle info already added
  int vehicle_index = vehicle_frame_info->vehicle_index;
  VehicleFrameInfo* current_info = video.vehicles[vehicle_index]->first_frame_info;
  for(; current_info->next_frame_info != nullptr; current_info = current_info->next_frame_info){
	  if(current_info == vehicle_frame_info || current_info->frame_index == vehicle_frame_info->frame_index){ // if same copy of info already exist or if info for the frame already exist
		  return false;
	  }
  }

  // handle add case
  current_info->next_frame_info = vehicle_frame_info;

  return true;
}

/*
 * Description: track the vehicle in the new frame and return the new info. The speed
 *              is the distance between positions of the vehicle in two frames and note
 *              that 1. the maximum speed of one vehicle is MAX_SPEED and 2. the minimum
 *              distance between vehicles in the same lane is MAX_SPEED and 3. the vehicle
 *              is assumed always to stay in the same lane.
 *       vehicle: pointer to the vehicle to be tracked.
 * current_frame: pointer to the frame the vehicle to be tracked in.
 *    prev_frame: pointer to the previous frame the vehicle was in.
 *        return: the pointer to the new info or nullptr if 1. the vehicle is not in
 *                prev_frame or 2. the vehicle left scope of current frame.
 */
VehicleFrameInfo * TrackVehicle(const Vehicle * vehicle, const Frame * current_frame, const Frame * prev_frame)
{
	// your implementation
//  VehicleFrameInfo* current_info;
  VehicleFrameInfo* prev_info = vehicle->first_frame_info;
  for(; prev_info->next_frame_info != nullptr; prev_info = prev_info->next_frame_info)
	  ; // current_info is now getting the last info of vehicle
  if(prev_frame->vehicles[prev_info->vehicle_index] == nullptr){ return nullptr;} // vehicle does not exist in prev_frame

  int pos_col = prev_info->position[1]; // getting previous position from previous vehicle frame info object
  int i = 1; // counting speed index
  bool flag = false; // check if vehicle is found
  for(; i <= 8 && pos_col+i < COLS; i++){
    if(current_frame->image[prev_info->position[0]][pos_col+i] == '*'){ // if there is a star in the current frame
      flag = true;
      break;
    }
  }
  if(!flag) return nullptr; // vehicle out of scope

  VehicleFrameInfo* new_info = new VehicleFrameInfo(); // create a new vehicle frame info object
  new_info->vehicle_index = prev_info->vehicle_index;
  new_info->frame_index = current_frame->index;
  new_info->position[0] = prev_info->position[0];
  new_info->position[1] = pos_col+i; // the location of vehicle in previous frame + speed of this frame
  new_info->speed = i;
  new_info->next_frame_info = nullptr;

  // current_info->next_frame_info = new_info;
  return new_info;
}

/*
 * Description: find and add new vehicles in the last frame of the frame list. You need to 1. find the
 *              new vehicles in the first colume of each lane, and 2. create and initialize a new vehicle
 *              is a new vehicle is found and, 3. add the new vehicle to the video and, 4. create a
 *              vf_info for the new vehicle in this frame and, 5. add the vf_info to the video.
 *
 *  video: input video structure.
 * return: true is finish or false if the frame index is invalid.
 */
bool FindAndAddNewVehicles(Video & video)
{
  // cout<<"entered FindAndAddNewVehicles"<<endl;
	// your implementation
  // TODO: haven't implemented output false case
  if(video.num_processed_frames > video.num_frames){ //
    return false;
  }

  if(video.num_processed_frames == 1){ // frame 0
    for(int i = 0; i < ROWS; i++){
      if(video.raw_data[0][i][0] == '*'){
        Vehicle* new_vehicle = new Vehicle();
        new_vehicle->index = video.num_vehicles;
        new_vehicle->num_visible_frames = 1;

        VehicleFrameInfo* new_info = new VehicleFrameInfo();
        new_info->vehicle_index = new_vehicle->index;
        new_info->frame_index = 0;
        new_info->position[0] = i;
        new_info->position[1] = 0;
        new_info->speed = 1;
        new_info->next_frame_info = nullptr;

        new_vehicle->first_frame_info = new_info;

        video.vehicles[video.num_vehicles] = new_vehicle;
        video.first_frame->vehicles[video.first_frame->num_vehicles] = new_vehicle;
        video.first_frame->num_vehicles++;
        video.num_vehicles++;
      }
    }
    return true;
  }

  // for frame != 0
  Frame* last_frame = video.first_frame;
  for(; last_frame->next_frame != nullptr; last_frame = last_frame->next_frame) // finding the last frame
  ;
  for(int i = 0; i < ROWS; i++){ // TODO: buggy loop
    if(last_frame->image[i][0] == '*'){ // has a vehicle at image[i][0]
      Vehicle* new_vehicle = new Vehicle();
      new_vehicle->index = video.num_vehicles; // set index to be 1 larger than current number of vehicles
      new_vehicle->num_visible_frames = 1; // set visible frame to 1

      VehicleFrameInfo* frame_info = new VehicleFrameInfo(); // initialize a new info object
      frame_info->vehicle_index = new_vehicle->index;
      frame_info->frame_index = last_frame->index;
      frame_info->position[0] = i; // row
      frame_info->position[1] = 0; // col
      frame_info->speed = 1; // speed
      frame_info->next_frame_info = nullptr; // set ll length = 1, so next is nullptr

      video.vehicles[video.num_vehicles] = new_vehicle;
      video.num_vehicles++;
      last_frame->vehicles[last_frame->num_vehicles] = new_vehicle;
      last_frame->num_vehicles++;
    }
    // cout<<"ok until now in loop "<<i<<endl;
  }

    // detect new vehicles lane by lane

		// check if there is a new vehicle in the lane

		// construct and add a new vehicle

		// construct and add a new vf_info
    return true;
}

/*
 * Description: calcute the average speed of all vehicles in all their visible frames (the average of all speeds).
 *
 *  video: input video structure.
 * return: the average speed or 0 if no vehicle is in the video.
 */
double AverageRoadSpeed(Video & video)
{
	// your implementation
  double total_speed = 0;
  // for(int i = 0; i < video.num_frames; i++){
  //   double total_speed_in_frame = 0;
  //   for(Frame* frame = video.first_frame; frame != nullptr; frame = frame->next_frame){
  //     for(int k = 0; k < num_vehicles; k++){
  //       total_speed_in_frame += frame->vehicles[k]->
  //     }
  //   }
  // }
  for(int i = 0; i < video.num_vehicles; i++){
    for(VehicleFrameInfo* info = video.vehicles[i]->first_frame_info; info->next_frame_info != nullptr; info = info->next_frame_info){
      total_speed += info->speed;
    }
  }
  return total_speed/video.num_vehicles;
}

/*
 * Description: clean all memories of the video, including raw_data, all frames, vehicles and vf_infos.
 *
 *  video: input video to be clean.
 * return: no return.
 */
void CleanVideo(Video & video)
{
	// your implementation

  // delete every VehicleFrameInfo
  for(int i = 0; i < video.num_vehicles; i++){ // accessing each elememnt in vehicles[]
    for(int j = 0; j < video.vehicles[i]->num_visible_frames; j++){ // accessing each info object
      VehicleFrameInfo * I_temp;
      VehicleFrameInfo * I_delete = video.vehicles[i]->first_frame_info;
      while(I_delete != nullptr){
        I_temp = I_delete->next_frame_info;
        delete I_delete;
        I_delete = I_temp;
      }
    }
  }

  Frame* f_temp;
  Frame* f_delete = video.first_frame;
  while(f_delete != nullptr){
    f_temp = f_delete->next_frame;
    delete f_delete;
    f_delete = f_temp;
  }

  delete[] *(video.vehicles);
  *(video.vehicles) = nullptr;
}
