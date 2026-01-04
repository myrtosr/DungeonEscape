#include "graphobject.h"
#include "roomnode.h"
#include "door.h"


RoomNode::RoomNode(int id_, int x_, int y_, int w_, int h_)
	: id(id_), x(x_), y(y_), w(w_), h(h_) {}

void RoomNode::addDoor(int doorId, TileCoord pos) {
	doors.push_back(Door(doorId, pos));
}