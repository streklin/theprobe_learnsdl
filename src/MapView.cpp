#include <algorithm>
#include "MapView.h"
#include "SharedConstants.h"

MapView::MapView() {
    map_offset_x_ = 0;
    map_offset_y_ = 0;
    zoom_level_ = 1.0f;
}

void MapView::SetMapOffset(const int offset_x, const int offset_y) {
    map_offset_x_ = std::clamp(offset_x, g_min_map_offset, g_max_map_offset);
    map_offset_y_ = std::clamp(offset_y, g_min_map_offset, g_max_map_offset);
}

void MapView::SetZoomLevel(const float zoom_level) {
    zoom_level_ = std::clamp(zoom_level, g_min_zoom, g_max_zoom);
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