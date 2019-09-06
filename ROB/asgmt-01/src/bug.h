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


struct terrrain
{
    RGB8b color;
    int weight;
    bool walkable;

};

class Bug
{
    public:
    Bug(const std::string& name,cv::Mat& map, RGB8b start_tile_color, RGB8b goal_tile_color):
    m_goal_tile_color{goal_tile_color},
    m_start_tile_color{start_tile_color},
    m_name{name},
    m_map{map.clone()}
    {}
    
    int get_walked_distance(){ return m_walked_distance;}
    const cv::Mat& get_map()const {return m_map;}
    const std::string& get_name() const {return m_name;}
    void insert_tile(coords coordinate);


    private:
    virtual void _path_planning();
    virtual void _reconstruct_closest_route();
    int m_walked_distance;
    int m_mline;
    int m_current_distance_from_goal;
    RGB8b m_start_tile_color;
    RGB8b m_goal_tile_color;
    RGB8b m_draw_col;
    const std::string& m_name;
    coords m_coordinate;
    std::map<RGB8b, std::pair<int,bool>> m_terrain_colors;
    cv::Mat m_map;


};