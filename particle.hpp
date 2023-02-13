#ifndef particle_HPP
#define particle_HPP
#include <cmath>
//#include "jsoncpp-master/include/json/json.h"

#include <iostream>
using namespace std;
#include <vector>
// extern struct particle_details;
// extern vector<particle_details> particle_detail;
extern int worldsize[2];
extern int chunk_size;

//this is the class for a defalt particle
class particles
{
    public:
        //position
        double x;
        double y;

        //velocities
        double vx = 0;
        double vy = 0;

        //damp is the loss of velocity due to friction
        double damp;

        //connections is equal to connections from main [id]
        //connections{id, distance, atraction}
        int id;
        

        particles() {

            void move(double ox, double oy, int attraction);

        }
        
        double roughdistance(double ix, double iy)
        {
            double dx = abs(x - ix);
            double dy = abs(x - ix);

            double dist = .5 * (dx + dy + max(dx, dy));
            return(dist);
        }
        
        void update(int dt, int check, vector<particles> *particlesi, vector<int> neerby, double damper)
        {

            

            x += vx;
            y += vy;

            vx *= damper;
            vy *= damper;


            int cx = x / chunk_size;
            int cy = y / chunk_size;
            int a;
            particles p;
            double dist;
            double dx;
            double dy;
            double attractiontemp;
            double power;
            for (int i = 0; i < neerby.size(); i++)
            
            {
                a = neerby[i];
                //a = i;  
                //cout << a << endl;
                p = particlesi->at(a);
                

                
                

                //dist = roughdistance(p.x, p.y);
                dist = sqrt( (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) );
                //neeraddvelocity(p.x, p.y, -.001 * dt, 60, dist);
                /*
                for (int z = 0; z < particle_detailid.connection.size(); z++)
                {
                    neeraddvelocity(p.x, p.y, particle_detail[p.id].connections[z].attraction * dt, 10, dist);
                }*/
                dx = x - p.x;
                dy = y - p.y;
                dist = sqrt(dx*dx + dy*dy);

                //neeraddvelocity(p.x, p.y, .004 * dt, 20, dist);
                //neeraddvelocity(p.x, p.y, .002 * dt, 15, dist);
                if (dist <= 10)
                {
                attractiontemp = (10 - dist) * .5;
                power = sqrt(vx*vx + vy*vy) * .5;
                //neeraddvelocity(p.x, p.y, power, 10, dist);
                
                move(p.x, p.y, dist, 10);
                p.move(x, y, dist, 10);
                
                // vx *= -1 * p.vx;
                // vy *= -1 * p.vy;
                
                }
                // for (int a = 0; i < 4; a++)
                // {
                //     if (dist <= 10)
                //     {
                //     attractiontemp = (10 - dist) * .5;
                //     move(p.x, p.y, dist, attractiontemp);
                //     //p.move(x, y, dist, attractiontemp);
                //     }
                // }
                
                //addgravvelocity(p.x, p.y, -.00001 * dt);
            
            }

            for (int j = 0; j < 4; j++){
            for (int i = 0; i < neerby.size(); i++)
                {
                a = neerby[i];
                //a = i;  
                //cout << a << endl;
                p = particlesi->at(a);
                if (dist <= 10)
                {
                    dist = sqrt(dx*dx + dy*dy);
                    attractiontemp = (10 - dist) * .005;
                    power = sqrt(vx*vx + vy*vy);
                    //cout << vx << ',' << vy << endl;
                    addvelocity(p.x, p.y, power);
                    
                    move(p.x, p.y, dist, attractiontemp);
                    p.move(x, y, dist, attractiontemp);
                    
                    // vx *= -1 * p.vx;
                    // vy *= -1 * p.vy;
                    
                    }
            }}

                        if (x < 0) {
                x = 1;
                vx *= -1;
                //x += vx * 2;
                //vx *= 0;
            }
            if (x > (chunk_size * worldsize[0]) - 1) {
                x = chunk_size*worldsize[0] - 1;
                vx *= -1;
                //x += vx * 2;
                //vx *= 0;
            }
            if (y <= 0) {
                y = 1;
                vy *= -1;
               // vy *= 0;
                
            }
            if (y >= (chunk_size * worldsize[1]) - 1) {
                y = chunk_size * worldsize[1] -1;
                vy *= -1;
                //vy *= 0;
                
                  
            }

            //x += vx;
            //y += vy;      
            //cout << 'd';
            //cout << x << ',' << y << endl;
        }
        
        void addgravvelocity(double ox, double oy, double attraction)
        {

            double dist = sqrt((x - ox)*(x - ox) + (y - oy)*(y - oy));

            //cout << dist << endl;
            if (!(dist == 0))
            {
            double div = attraction / dist;

            vx += ((x - ox) * div);
            vy += ((y - oy) * div);
            }
            
        }

        //changes velocity
        void addvelocity(double ox, double oy, double attraction)
        {
            double dist = sqrt((x - ox)*(x - ox) + (y - oy)*(y - oy));

            
            if (!(dist == 0))
            {
            double div = dist / attraction;

            vx += ((x - ox) / div);
            vy += ((y - oy) / div);
            }
        }
        void neeraddvelocity(double ox, double oy, double attraction, double distance, double distl)
        {
            
            if (distl <= distance)
            {
                addvelocity(ox, oy, attraction);
                //vx += ovx * .001;
                //vy += ovy * .001;
                //addvelocity(ox, oy, -(1.5/(distl+.5))-(attraction/(distl-distance-.5)));
                
            }
        }

        //this function moves the particle to a location in one step depending on the attraction value
        void move(double ox, double oy, double dist, double attraction)
        {

            if (!(dist == 0))
            {
            x += ((x - ox) / ((dist / attraction)));
            y += ((y - oy) / ((dist / attraction)));
            }
        }
        #include <cmath>




};






#endif