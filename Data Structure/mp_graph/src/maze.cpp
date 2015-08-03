/**
 * @file maze.cpp
 * Definition of a maze class.
 *
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <random>

#include "tools.h"
#include "maze.h"

namespace cs225
{

std::ostream& operator<<(std::ostream& os, direction dir)
{
    switch (dir)
    {
        case direction::RIGHT:
            return os << "RIGHT";
        case direction::DOWN:
            return os << "DOWN";
        case direction::LEFT:
            return os << "LEFT";
        case direction::UP:
            return os << "UP";

            
    }
}

maze::maze(uint64_t width, uint64_t height) : width_{width}, height_{height}
{
    size = width * height;
    cellset.add_elements(size);

    rw = vector<bool> (size, true);
    bw = vector<bool> (size, true);
    

    for (uint64_t i = 0; i < width_; i++)
    {
        for (uint64_t j = 0; j < height_; j++)
        {
            pair< uint64_t, uint64_t > block (i, j);
            pair< pair< uint64_t, uint64_t > , direction> wallRight ( block, direction::RIGHT);
            pair< pair< uint64_t, uint64_t > , direction> wallDOWN ( block, direction::DOWN);

            walls.push_back(wallRight);
            walls.push_back(wallDOWN);
        }
    }


    while (walls.size() != 1)
    {

        uint64_t temp = rand() % walls.size();
        pair < pair< uint64_t, uint64_t > , direction > wall = walls[temp];
        walls[temp] = walls[walls.size()-1];
        walls.pop_back();
        pair < uint64_t, uint64_t > block = wall.first;
        direction dir = wall.second;
        uint64_t x = block.first;
        uint64_t y = block.second;
        uint64_t location = idx(x, y);

        if (dir==direction::DOWN)
        {
     
            if ( location + width >= size) 
                 continue;
            if (cellset.find( location ) == cellset.find( location + width ))
                 continue;
            cellset.merge( location, location + width );
            bw[location] = false;
        }
        else
        {
            
            if ( ( (location + 1)  % width) == 0) 
               continue;

            if ( cellset.find(location) == cellset.find( location + 1 ))
                continue;
        
           cellset.merge( location, location +1);

            rw[location] = false;
        }
    }

    // use rng for your random numbers: it's a functor that returns you
    // random numbers

    /// @todo your code here
}

bool maze::can_travel(uint64_t x, uint64_t y, direction dir) const
{
  if ( x > width_ || y > height_ )
        return false;

    if ( ( y == height_ -1 && dir == direction::DOWN ) ||
            ( x == width_ -1 && dir == direction::RIGHT) ||( x == 0 && dir == direction::LEFT ) ||( y == 0 && dir == direction::UP )  )
        return false;
        
        if(dir == direction::RIGHT)
		return !rw[idx(x, y)];
	if(dir == direction::DOWN)
		return !bw[idx(x, y)];
	if(dir == direction::LEFT) 
		return !rw[idx(x-1, y)];
        if(dir == direction::UP) 
		return !bw[idx(x, y-1)];
	
	return false;

    /// @todo your code here
    
}

void maze::set_wall(uint64_t x, uint64_t y, direction dir, bool exists)
{
       uint64_t location = idx(x, y);

    if (dir == direction::DOWN)
        bw[location] = exists;
    else
        rw[location] = exists;

    /// @todo your code here
    /// DON'T THROW EXCEPTIONS FROM THIS FUNCTION
}



std::vector<direction> maze::solve () {

	 
   
    map <uint64_t, uint64_t> path;
    bool checkpath [width_][height_];
    
  for (uint64_t i = 0; i < width_; i++ )
    {
        for (uint64_t j = 0; j < height_; j++ )
        {
            checkpath[i][j] = false;
        }
    }

   
    queue<int> q;
    q.push(0);
    checkpath[0][0] = true;

    
    while (!q.empty())
    {
  
        auto curCell = q.front();
        auto curX = xcoord( curCell );
        auto curY = ycoord( curCell );
        q.pop();
        direction dire;


        for (uint64_t i = 0; i < 4; i++)
        {
           
            if (i==0)
               dire=direction::RIGHT;
            if (i==1)
               dire=direction::DOWN;
            if (i==2)
               dire=direction::LEFT;
            if (i==3)
               dire=direction::UP;

            auto nc = next( curX, curY, dire );
            auto nx = xcoord( nc );
            auto ny = ycoord( nc );

            if (!checkpath[ nx ][ ny ]&&can_travel( curX, curY, dire) )
            {    
                 checkpath[ nx ][ ny ] = true;
                 path[nc] = curCell;
                 q.push( nc );
            } 
        }
    }
 
    uint64_t ml = 0;
    uint64_t mi = 0;
    
    for (uint64_t i = 0; i < width_; i++)
    {
        uint64_t count = 0;
        uint64_t start = 0;
        uint64_t end = idx(i, height_ -1);
        while (end != start)
        {
            end = path[end];
            count++;
        }
     if (count > ml)
        {
            ml = count;
            mi = i;
        }
    }

    ec = idx( mi, height_ -1);

    auto last = ec;
    uint64_t begin = 0;
    stack<uint64_t> savestack;
    while (last != begin)
    {
        auto diff = last - path[last];
        
        if (diff == 1)          
            savestack.push(0);
        else if (diff == -1)    
            savestack.push(2);
        else if (diff == width_)     
            savestack.push(1);
        else if (diff == (-1) * width_)     
            savestack.push(3);
        else                  
            savestack.push(-1);

        last = path[last];
    }
    

    direction dire;
    while (!savestack.empty() )
    {
     
        auto temp=savestack.top();
        
        if (temp==0)
        dire=direction::RIGHT;
     else if (temp==1)
        dire=direction::DOWN;
     else if (temp==2)
        dire=direction::LEFT;
     else if (temp==3)
        dire=direction::UP;
        solution.push_back(dire);
        
        savestack.pop();
    }
    return solution; 

 
}

epng::png maze::draw() const
{
 epng::png result( 10 * width_ + 1, 10 * height_ +1);

    

    for (uint64_t i = 10; i < 1 + 10 * width_; i++)
    {
        result( i, 0 )->red = 0;
        result( i, 0 )->green = 0;
        result( i, 0 )->blue = 0;
    }


    for (uint64_t i = 0; i < 1 + 10 * height_ ; i++ )
    {
       result( 0, i )->red = 0;
       result( 0, i )->green = 0;
       result( 0, i )->blue = 0;
    }

   uint64_t curX;
    uint64_t curY;

    for ( uint64_t x = 0; x < width_; x++ )
    {
        for (uint64_t y = 0; y < height_; y++ )
        {
            if (bw[ idx(x, y) ] )
            {
                for (uint64_t i = 0; i <= 10; i++ )
                {
                    curX = i + x * 10 ;
                    curY = ( y + 1 ) * 10;
                     result( curX, curY )->red = 0;
                     result( curX, curY )->green = 0;
                     result( curX, curY )->blue = 0;    
                  

            
                }
            }

            if ( rw[ idx(x, y) ] )
            {
                for (uint64_t i = 0; i <= 10; i++)
                {
                    curX = (x + 1) * 10;
                    curY = i + y * 10;
                     result( curX, curY )->red = 0;
                     result( curX, curY )->green = 0;
                     result( curX, curY )->blue = 0;
                   

                }
            }
        }
    }

    return result;    

   /// @todo your code here
}

epng::png maze::draw_with_solution()
{
 auto pic = draw();

    uint64_t xc=0;
    uint64_t yc=0;
    uint64_t curX = 5;
    uint64_t curY = 5;

    for ( uint64_t i= 0; i < solution.size(); i++)
    {
        if ( solution[i] == direction::RIGHT )
        {
            for (uint64_t j = 0; j < 11; j++ )
            {
                
                pic( curX + j, curY )->blue = 0;
                pic( curX + j, curY )->green = 0;
            }
            curX += 10;
            xc++;
        } 
           else if ( solution [i] == direction::DOWN)
        {
            for (uint64_t j = 0; j < 11; j++)
            {
                
                pic( curX, curY + j)->blue = 0;
                pic( curX, curY + j)->green = 0;
            }
            curY += 10;
            yc++;
        }
        else if ( solution [i] == direction::LEFT)
        {
            for (uint64_t j = 0; j < 11; j++)
            {
               
                pic( curX - j, curY )->blue = 0;
                pic( curX - j, curY )->green = 0;
            }
            curX -= 10;
            xc--;
        }
        else if ( solution [i] == direction::UP)
        {
            for (uint64_t j = 0; j < 11; j++)
            {
               
                pic( curX, curY - j)->blue = 0;
                pic( curX, curY - j)->green = 0;
            }
            curY -= 10;
            yc--;
        }
      
    }



    for (uint64_t i = 1; i < 10; i++)
    {
        auto tx=xc * 10 + i;
        auto ty=(yc + 1) * 10;
       pic( tx, ty )->red = 255;
       pic( tx, ty )->green = 255;
       pic( tx, ty )->blue = 255;
  
    }

    return pic; 

	
    /// @todo your code here

    
}

/*void maze::makecolor (uint64_t xc, uint64_t yc, epng::png& retval)
{
       retval( xc, yc )->red = 255;
       retval( xc, yc )->green = 255;
       retval( xc, yc )->blue = 255;
}
*/

uint64_t maze::idx(uint64_t x, uint64_t y) const {
	return  y * width_ + x;
}

uint64_t maze::xcoord(uint64_t location) const{
	return location % width_;
}



uint64_t maze::ycoord(uint64_t location) const{
	return (location-xcoord(location)) / height_;
}


uint64_t maze::next( uint64_t x, uint64_t y, direction dir )
{
    switch(dir)
    {
        case direction::RIGHT:
            return idx(x, y) + 1;
        case direction::DOWN:
            return idx(x, y) + width_;
        case direction::UP:
            return idx(x, y) - width_;
        case direction::LEFT:
            return idx(x, y) - 1;
          
    }
}

}
