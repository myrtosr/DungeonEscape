#include "roomview.h"
#include "tile.h"


void RoomView::applyToTileMap(TileMap& map) {
	for (int ty = topLeft.y; ty < topLeft.y + bottomRight.y; ++ty) {
		for (int tx = topLeft.x; tx < topLeft.x + bottomRight.x; ++tx) {

			Tile& tile = map.at(tx, ty);

			bool isTop = (ty == topLeft.y);
			bool isBottom = (ty == topLeft.y + bottomRight.y - 1);
			bool isLeft = (tx == topLeft.x);
			bool isRight = (tx == topLeft.x + bottomRight.x - 1);

			// WALL CORNERS
			if (isTop && isLeft) {
				tile.setType(TileType::WALL_TL);
			}
			else if (isTop && isRight) {
				tile.setType(TileType::WALL_TR);
			}
			else if (isBottom && isLeft) {
				tile.setType(TileType::WALL_BL);
			}
			else if (isBottom && isRight) {
				tile.setType(TileType::WALL_BR);
			}

			// HORIZONTAL WALLS
			else if (isTop || isBottom) {
				tile.setType(TileType::WALL_HOR);
			}
			// VERTICAL WALLS
			else if (isLeft || isRight) {
				tile.setType(TileType::WALL_VER);
			}
			// ROOM FLOOR
			else {
				tile.setType(TileType::FLOOR);
				tile.setClickable(roomNode->isAvailable());
			}
		}
	};
