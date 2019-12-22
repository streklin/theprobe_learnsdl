#include <iostream>
#include "MapView.h"

MapView::MapView() {
    map_offset_x_ = 0;
    map_offset_y_ = 0;
    zoom_level_ = 1.0f;
}

void MapView::SetMapOffset(const int offset_x, const int offset_y) {
    map_offset_x_ = offset_x;
    map_offset_y_ = offset_y;
}

void MapView::SetZoomLevel(const float zoom_level) {
    zoom_level_ = zoom_level;
}

int MapView::MapOffsetX() {
    return map_offset_x_;
}

int MapView::MapOffsetY() {
    return map_offset_y_;
}

float MapView::GetZoomLevel() {
    return zoom_level_;
}