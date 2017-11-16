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
  if(vehicle_index < 0 || vehicle_index > num_vehicles){
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
    if(temp_info->next_frame_info == nullptr && temp_info->frame_index != frame_index){
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
  if(video.num_processed_frames >= video.num_frames){
    return false;
  }

  int new_frame_index = video.num_processed_frames;

  Frame* new_frame = new Frame;
  new_frame->index = new_frame_index;
  new_frame->image = new char*[ROWS];
  for(int i = 0; i < ROWS; i++){
    new_frame->image[i] = new char[COLS];
    for(int j = 0; j < COLS; j++){
      new_frame->image[i][j] = video.raw_data[new_frame_index][i][j];
    }
  }
  new_frame->num_vehicles = 0;
  new_frame->vehicles = nullptr;
  new_frame->next_frame = nullptr;

  if(new_frame_index != 0){ // if there are other frame before this frame (frame index not 0)
    Frame* last_frame = GetFrame(video, new_frame_index-1);
    last_frame->next_frame = new_frame;
  }
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
  VehicleFrameInfo temp_info = GetVFInfo(GetVehicle(video, vehicle_frame_info->vehicle_index), vehicle_frame_info->frame_index);
  if(temp_info != nullptr){
    return false;
  }

  // handle adding case
  Vehicle* corr_vehicle = GetVehicle(video, vehicle_frame_info->vehicle_index);
  VehicleFrameInfo* last_info = GetVFInfo(corr_vehicle, vehicle_frame_info->frame_index);
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
    cout<<"something's wrong"<<endl;
    return nullptr;
  }
  int pos_col_old = last_info->position[1];
  bool flag = false;
  int i = 1;
  for(; i <= 8 && pos_col_old + i < COLS; i++){
    if(current_frame->image[last_info->position[0]][pos_col_old + i] == '*'){
      flag = true;
      break;
    }
  }
  if(!flag){ // cannot find the vehicle, out of scope
    return nullptr;
  }
  VehicleFrameInfo* new_info = new VehicleFrameInfo;
  vehicle->num_visible_frames++;
  current_frame->vehicles[vehicle->index] = vehicle;

  new_info->vehicle_index = last_info->vehicle_index;
  new_info->frame_index = last_info->frame_index;
  new_info->position[0] = last_info->position[0];
  new_info->position[1] = pos_col_old + i;
  new_info->speed = i;
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
  int check_frame_index = video.num_processed_frames - 1;
  
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
