#pragma once
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <map>

typedef unsigned char uchar;

struct coords
{
    int x, y;
};

struct RGB8b
{   
    uchar B,G,R;
};

union RGBWrap
{
    RGB8b rgb;  
    int value;      
};


struct terrrain
{
    RGBWrap color;
    int weight;
    bool walkable;
    bool operator<(const terrrain& obj1)
    {
        int* tmp = (int*)(&(this->color));
        //return(static_cast<int>(this->color) )
    }
    int ret_val(){return(this->color.value);}
    int ret_rgb(){RGB8b tmp = {2,1,1};
    return *((int*)(&(tmp)));}

};


class Bug
{
    public:
    Bug(const std::string& name,cv::Mat& map, RGB8b start_tile_color, RGB8b goal_tile_color);
    
    
    int get_walked_distance(){ return m_walked_distance;}
    const cv::Mat& get_map()const {return m_map;}
    const std::string& get_name() const {return m_name;}
    void insert_tile(terrrain tile,coords coordinate);


    private:
    virtual void _path_planning();
    virtual void _reconstruct_closest_route();
    virtual int _get_slope_to_goal();
    virtual void _inspect_adjacent_tiles();

    int m_walked_distance;
    terrrain adjacent_tiles[4];
    int m_mline;
    int m_current_distance_from_goal;
    RGB8b m_start_tile_color;
    RGB8b m_goal_tile_color;
    RGB8b m_draw_col;
    const std::string& m_name;
    coords m_coordinate;
    std::map<RGB8b, std::pair<int,bool>> m_terrain_tiles;
    cv::Mat m_map;


};