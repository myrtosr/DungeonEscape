#include "passageview.h"


void PassageView::applyToTileMap(TileMap& map) {

	int dx = (first.x > last.x) ? 1 : (first.x < last.x ? -1 : 0);
	int dy = (first.y > last.y) ? 1 : (first.y < first.y ? -1 : 0);

	int x = first.x;
	int y = first.y;

	while (x != last.x || y != last.y) {
		Tile& tile = map.at(x, y);
		tile.setType(TileType::PASSAGE);
		tile.setClickable(false);

		x += dx;
		y += dy;
	}

	map.at(last.x, last.y).setType(TileType::PASSAGE);
}