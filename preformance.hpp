#ifndef preformance_HPP
#define preformance_HPP
#include <stdio.h>
#include <iostream>
#include<tuple>
#include <vector>
#include "particle.hpp"
using namespace std;
#include <cstdlib>  // for rand and srand
#include <ctime>    // for time
#include <printf.h>
#include <stdio.h>

int random_in_range(int lower_bound, int upper_bound) {
    // Seed the random number generator with the current time
    srand(rand());

    // Generate a random number between lower_bound and upper_bound, inclusive
    int random_number = lower_bound + rand() % (upper_bound - lower_bound + 1);

    return random_number;
}

float randomFloat()
{
    srand(rand());
    return (float)(rand()) / (float)(rand());
}


pair<double, double> addgravvelocityfeild(double x, double y, double ox, double oy, double attraction, int chunk_size)
{
    if (attraction == 0)
    {
        //cout << '-' << endl;
        //printf("%s \n", "____________________1");;
        return make_pair(0, 0);
        
    }
    double ix = x - ox;
    double iy = y - oy;
    double dist = sqrt(ix*ix + iy*iy);

    if (dist == 0)
    {
        return make_pair(0, 0);   
    }
            
    double div = attraction / dist;
    double vx = ((x - ox) * div);
    double vy = ((y - oy) * div);

    return make_pair(vx, vy);
}

vector<vector<vector<double> > > velocityfeild(vector<vector<double> > gmap, int worldsize[2], int chunk_size, vector<vector<vector<double> > > Default)
{
    vector<vector<vector<double> > > out = Default;
    pair<double, double> temp;
    double half = chunk_size * .5;
    
    for (int x = 0; x < gmap.size(); x++)
    {
        for (int y = 0; y < gmap[0].size(); y++)
        {
                
            for (int i = 0; i < gmap.size(); i++)
            {
                for (int a = 0; a < gmap[0].size(); a++)
                {
                    pair<double, double> temp = addgravvelocityfeild(x, y, i, a, gmap[i][a], chunk_size);
                    out[x][y][0] += temp.first * -.0000001;
                    out[x][y][1] += temp.second * -.0000001;
                }
            }
        }
    }
    return out;
}

vector<vector<vector<int> > > change_map(vector<vector<vector<int> > > map)
{
    vector<vector<vector<int> > > out = map;
    
    for (int x = 0; x < map.size(); x++)
    {

        for (int y = 0; y < map[0].size(); y++)
        {
            
            if (x-1 >= 0)
            {

                for (int i = 0; i < map[x-1][y].size(); i++)
                {
                    
                    out[x][y].push_back(map[x-1][y][i]);
                }
            }
            if (y-1 >= 0)
            {

                for (int i = 0; i < map[x][y-1].size(); i++)
                {
                    out[x][y].push_back(map[x][y-1][i]);
                }
            }
            
            if (x+1 < map.size())
            {
                
                for (int i = 0; i < map[x+1][y].size(); i++)
                {

                    out[x][y].push_back(map[x+1][y][i]);
                    //cout << out[x][y].size() << endl;
                }
            }

            if (y+1 < map[0].size())
            {

                for (int i = 0; i < map[x][y+1].size(); i++)
                {
                    out[x][y].push_back(map[x][y+1][i]);
                }
            }
            
            if (x-1 >= 0 && y-1 >= 0)
            {

                for (int i = 0; i < map[x-1][y-1].size(); i++)
                {
                    out[x][y].push_back(map[x-1][y-1][i]);
                }
            }
            
            if (x-1 >= 0 && y+1 < map[0].size())
            {

                for (int i = 0; i < map[x-1][y+1].size(); i++)
                {
                    out[x][y].push_back(map[x-1][y+1][i]);
                }
            }
            
            if (x+1 < map.size() && y+1 < map[0].size())
            {

                for (int i = 0; i < map[x+1][y+1].size(); i++)
                {
                    out[x][y].push_back(map[x+1][y+1][i]);
                }
            }
            
            if (x+1 < map.size() && y-1 >= 0)
            {

                for (int i = 0; i < map[x+1][y-1].size(); i++)
                {
                    out[x][y].push_back(map[x+1][y-1][i]);
                }
            }
        }
    }
    return(out);
}

#endif
