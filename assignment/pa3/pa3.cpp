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
  if(frame_index < 0 || frame_index >= video.num_frames){
    return nullptr;
  }

  Frame* temp_frame = video.first_frame;

  for(; temp_frame->index != frame_index; temp_frame = temp_frame->next_frame){
    if(temp_frame == nullptr){
      return nullptr;
    }
  }
  return temp_frame;
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

  if(vehicle_index < 0 || vehicle_index > video.num_vehicles){
    return nullptr;
  }

  return video.vehicles[vehicle_index];
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
  VehicleFrameInfo* temp_info = vehicle->first_frame_info;
  if(temp_info == nullptr){
    return nullptr;
  }

  while(temp_info->frame_index != frame_index){
    if(temp_info->next_frame_info == nullptr){ // this is not the wanted frame and next is nullptr
      return nullptr;
    }
    temp_info = temp_info->next_frame_info;
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
  if(video.num_processed_frames >= video.num_frames){ // if all frames are processed
    return false;
  }

  int new_frame_index = video.num_processed_frames;

  Frame* new_frame = new Frame;
  new_frame->index = new_frame_index;
  // new_frame->image = new char*[ROWS];
  // for(int i = 0; i < ROWS; i++){
  //   new_frame->image[i] = new char[COLS];
  //   for(int j = 0; j < COLS; j++){
  //     new_frame->image[i][j] = video.raw_data[new_frame_index][i][j];
  //   }
  // }
  new_frame->image = video.raw_data[new_frame->index];
  new_frame->num_vehicles = 0;
  for(int i = 0; i < MAX_VEHICLE_NUM; i++){
    new_frame->vehicles[i] = nullptr;
  }
  new_frame->next_frame = nullptr;

  if(new_frame_index == 0){
    video.first_frame = new_frame;
  }
  else{ // if there are other frame before this frame (frame index not 0)
    Frame* last_frame = GetFrame(video, new_frame_index-1);
    last_frame->next_frame = new_frame;
  }
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
  if(vehicle_frame_info->frame_index > video.num_processed_frames){ // if frame index does not exist in the video
    return false;
  }
  if(vehicle_frame_info->vehicle_index < 0 || vehicle_frame_info->vehicle_index > video.num_vehicles){ // if vehicle index does not exist in the video
    return false;
  }
  VehicleFrameInfo* temp_info = GetVFInfo(GetVehicle(video, vehicle_frame_info->vehicle_index), vehicle_frame_info->frame_index);
  if(temp_info != nullptr){
    return false;
  }

  // handle adding case
  Vehicle* corr_vehicle = GetVehicle(video, vehicle_frame_info->vehicle_index);
  corr_vehicle->num_visible_frames++;
  GetFrame(video, vehicle_frame_info->frame_index)->vehicles[vehicle_frame_info->vehicle_index] = corr_vehicle;
  VehicleFrameInfo* last_info = GetVFInfo(corr_vehicle, vehicle_frame_info->frame_index - 1);
  last_info->next_frame_info = vehicle_frame_info;
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
  if(current_frame == nullptr || prev_frame == nullptr){ // if frames does not exist
    return nullptr;
  }
  if(prev_frame->vehicles[vehicle->index] == nullptr){ // if the vehicle was not in prev frame
    return nullptr;
  }
  VehicleFrameInfo* last_info = GetVFInfo(vehicle, prev_frame->index);
  if(last_info == nullptr){ // if there is no last_info
    return nullptr; // if this is returned, then something's REALLY WRONG!!!!!!!
  }
  int pos_col_old = last_info->position[1];
  bool found_vehicle = false; // check if vehicle is found
  int speed = 1;
  for(; speed <= 8 && pos_col_old + speed < COLS; speed++){
    if(current_frame->image[last_info->position[0]][pos_col_old + speed] == '*'){
      found_vehicle = true;
      break;
    }
  }
  if(!found_vehicle){ // cannot find the vehicle, out of scope
    return nullptr;
  }
  VehicleFrameInfo* new_info = new VehicleFrameInfo;
  // vehicle->num_visible_frames++;
  // current_frame->vehicles[vehicle->index] = vehicle;

  new_info->vehicle_index = last_info->vehicle_index;
  new_info->frame_index = current_frame->index;
  new_info->position[0] = last_info->position[0];
  new_info->position[1] = pos_col_old + speed;
  new_info->speed = speed;
  new_info->next_frame_info = nullptr;
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
	// your implementation
  // detect new vehicles lane by lane
	// check if there is a new vehicle in the lane
	// construct and add a new vehicle
	// construct and add a new vf_info
  if(video.num_processed_frames <= 0){ // if there is no processed frame, then return false
    return false;
  }
  if(video.num_processed_frames > video.num_frames){ // all frames checked
    return false;
  }

  int check_frame_index = video.num_processed_frames - 1;
  Frame* check_frame = GetFrame(video, check_frame_index);
  for(int i = 0; i < ROWS; i++){
    if(check_frame->image[i][0] == '*'){ // if located a vehicle
      Vehicle* new_vehicle = new Vehicle; // create a new vehicle object
      new_vehicle->index = video.num_vehicles;
      new_vehicle->num_visible_frames = 1;

      VehicleFrameInfo* new_info = new VehicleFrameInfo; // create a new info object
      new_info->vehicle_index = new_vehicle->index;
      new_info->frame_index = check_frame_index;
      new_info->position[0] = i;
      new_info->position[1] = 0;
      new_info->speed = 1;
      new_info->next_frame_info = nullptr;

      new_vehicle->first_frame_info = new_info;

      video.vehicles[new_vehicle->index] = new_vehicle;
      video.num_vehicles++;
      check_frame->vehicles[new_vehicle->index] = new_vehicle; // add the new vehicle pointer to frames vehicles index
      check_frame->num_vehicles++;
    }
  }
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
  if(video.num_vehicles == 0){
    return 0.0;
  }
  double total_speed = 0;
  int total_visible_vehicles = 0;
  for(int i = 0; video.vehicles[i] != nullptr; i++){ // loop through every vehicles in video
    for(VehicleFrameInfo* temp_info = video.vehicles[i]->first_frame_info; temp_info != nullptr; temp_info = temp_info->next_frame_info){ // loop through every info for the vehicle
      total_speed += temp_info->speed;
      total_visible_vehicles++;
    }
  }
  return total_speed/total_visible_vehicles;
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
  //TODO delete all raw data
 for(int i = 0; i < video.num_frames; i++){
    for(int j = 0; j < ROWS; j++){
      delete[] video.raw_data[i][j];
      video.raw_data[i][j] = nullptr;
    }
    delete[] video.raw_data[i];
    video.raw_data[i] = nullptr;
  }
  delete[] video.raw_data;
  video.raw_data = nullptr;

  //TODO delete video.vehicles[]->every_info, then every_vehicle
  for(int i = 0; i < MAX_VEHICLE_NUM; i++){
    Vehicle* temp_vehicle = video.vehicles[i]; // get every vehicles
    if(temp_vehicle == nullptr){
      continue;
    }
    VehicleFrameInfo* temp_info = temp_vehicle->first_frame_info; // get info
    while(temp_info != nullptr){ // delete every info for a vehicle
      VehicleFrameInfo* to_be_deleted_info = temp_info;
      temp_info = temp_info->next_frame_info;
      delete to_be_deleted_info;
      // to_be_deleted_info = temp_info;
    }
    delete temp_vehicle; // delete the vehicle after all info for the vehicle are deallocated
    temp_vehicle = nullptr;
  }

  //TODO delete image for every frames
  // for(int i = 0; i < video.num_frames; i++){
  //     Frame* temp_frame = GetFrame(video, i);
  //     if(temp_frame == nullptr){
  //       continue;
  //     }
  //     for(int j = 0; j < ROWS; j++){
  //       delete[] temp_frame->image[j];
  //       temp_frame->image[j] = nullptr;
  //     }
  //     delete[] temp_frame->image;
  //     temp_frame->image = nullptr;
  // }

  // TODO FINALLY, delete all frames in the video
  Frame* temp_frame = video.first_frame; // get first frame in video
  while(temp_frame != nullptr){
    Frame* to_be_deleted_frame = temp_frame;
    temp_frame = temp_frame->next_frame;
    delete to_be_deleted_frame;
    to_be_deleted_frame = temp_frame;
  }
}
