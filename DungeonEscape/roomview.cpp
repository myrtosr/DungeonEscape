#include "roomview.h"
#include "tile.h"


void RoomView::applyToTileMap(TileMap& map) {
	for (int row = topLeft.x; row <= bottomRight.x; ++row) {
		for (int col = topLeft.y; col <= bottomRight.y; ++col) {

			Tile& tile = map.at(row, col);

			bool isTop = (row == topLeft.x);
			bool isBottom = (row == bottomRight.x);
			bool isLeft = (col == topLeft.y);
			bool isRight = (col == bottomRight.y);

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
	}
}
