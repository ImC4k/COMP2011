#include "lab10.h"
#include "frame.h"

using namespace std;

// TODO 1
//
// Create frame linked list containing all frames and copy image from imageData to every frame.
//
// imageData:	3D char array where images of each frame are stored
// numOfFrames:	Number of frames in total
//
// return:		Pointer to the head of linked list
//
Frame *createFrameLinkedList(char imageData[][ROWS][COLS], int numOfFrames)
{
	Frame *result = nullptr;
	for(int frame_index = 0; frame_index < numOfFrames; frame_index++){
		Frame* new_frame = new Frame;
		// return nullptr if out of bound
		if(numOfFrames < 0 || numOfFrames > 16){
			return nullptr;
		}
		// copy image of the frame
		int num_vehicles_this_frame = 0;
		for(int i = 0; i < ROWS; i++){
			for(int j = 0; j < COLS; j++){
				new_frame->image[i][j] = imageData[frame_index][i][j];
			}
		}
		new_frame->num_vehicles = num_vehicles_this_frame;
		new_frame->next_frame = nullptr;
		// assign first frame pointer to result for returning
		if(frame_index == 0){
			result = new_frame;
		}
		if(frame_index != 0){
			Frame* last_frame = result;
			for(; last_frame->next_frame != nullptr; last_frame = last_frame->next_frame)
			;
			last_frame->next_frame = new_frame;
		}
	}
	return result;
}

// TODO 2
//
// Set the num_vehicles field in each frame to be the number of vehicles in its image.
//
// head:	Pointer to the head of linked list
//
void setNumOfVehicles(Frame *head)
{
	if(head == nullptr){
		return;
	}
	Frame* temp_frame = head;
	for(; temp_frame->next_frame != nullptr; temp_frame = temp_frame->next_frame){
		int num_vehicles_this_frame = 0;
		for(int i = 0; i < ROWS; i++){
			for(int j = 0; j < COLS; j++){
				if(temp_frame->image[i][j] == '*'){
					num_vehicles_this_frame++;
				}
			}
		}
		temp_frame->num_vehicles = num_vehicles_this_frame;
	}
}

// TODO 3
//
// Remove the frames that contain no vehicles.
//
// head:	Pointer to the head of linked list
//
void removeFramesWithNoVehicles(Frame *&head)
{
	Frame* temp_frame = head;
	while(temp_frame != nullptr){
		if(temp_frame->num_vehicles == 0){
			if(temp_frame == head){
				head = temp_frame->next_frame;
				delete temp_frame;
				temp_frame = head;
				continue;
			}
			else{
				//TODO set previous frame's next_frame to this frame's next_frame point
				// get previous frame, guaranteed prev_frame has something
				Frame* prev_frame = head;
				for(; prev_frame->next_frame != temp_frame; prev_frame = prev_frame->next_frame){
				}
				// get next frame to search
				Frame* next_frame = temp_frame->next_frame;
				prev_frame->next_frame = next_frame;
				delete temp_frame;
				temp_frame = next_frame;
				continue;
			}
		}
		temp_frame = temp_frame->next_frame;
	}
}

// Given function
//
// Prints out the frame linked list, specified by head.
//
// head:	Pointer to the head of linked list to be printed
//
void printFrameLinkedList(const Frame *head)
{
	for (const Frame *curr = head; curr != nullptr; curr = curr->next_frame) {
		cout << "Number of vehicles: " << curr->num_vehicles << endl;

		for (int r = 0; r < ROWS; ++r) {
			for (int c = 0; c < COLS; ++c) {
				cout << curr->image[r][c];
			}
			cout << endl;
		}
	}

	cout << endl;
}
