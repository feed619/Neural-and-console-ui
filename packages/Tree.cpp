#include <vector>

struct vector_2d
{
    int x;
    float y;
    vector_2d(int x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

struct Tree
{
    /* data */
    int X;
    std::vector<vector_2d> data;
};
