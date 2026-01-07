#include "roomview.h"



/*
void RoomView::applyToTileMap(TileMap& map) {
	for (int ty = y; ty < y + h; ++ty) {
		for (int tx = x; tx < x + w; ++tx) {

			Tile& tile = map.at(tx, ty);

			bool isTop = (ty == y);
			bool isBottom = (ty == y + h - 1);
			bool isLeft = (tx == x);
			bool isRight = (tx == x + w - 1);

			// ΓΩΝΙΕΣ
			if (isTop && isLeft) {
				tile.type = TileType::WALL_TL;
			}
			else if (isTop && isRight) {
				tile.type = TileType::WALL_TR;
			}
			else if (isBottom && isLeft) {
				tile.type = TileType::WALL_BL;
			}
			else if (isBottom && isRight) {
				tile.type == TileType::WALL_BR;
			}

			// ΟΡΙΖΟΝΤΙΟΙ ΤΟΙΧΟΙ
			else if (isTop || isBottom) {
				tile.type = TileType::WALL_HOR;
			}
			// ΚΑΘΕΤΟΙ ΤΟΙΧΟΙ
			else if (isLeft || isRight) {
				tile.type = TileType::WALL_VER;
			}
			// ΕΣΩΤΕΡΙΚΟ ΔΩΜΑΤΙΟΥ
			else {
				tile.type = TileType::FLOOR;
				tile.clickable = node->isAvailable();
			}
		}
	};
*/


	// if ((isTop || isBottom) && (isLeft || isRight)) {
//    tile.type = TileType::WallCorner;
//}
