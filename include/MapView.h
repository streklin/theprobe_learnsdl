#ifndef MAPVIEW
#define MAPVIEW

class MapView final {
public:
    MapView();

    void SetMapOffset(const int offset_x, const int offset_y);
    void SetZoomLevel(const float zoom_level);

    int MapOffsetX();
    int MapOffsetY();
    float GetZoomLevel();

private:
    int map_offset_x_;
    int map_offset_y_;
    float zoom_level_;
};

#endif