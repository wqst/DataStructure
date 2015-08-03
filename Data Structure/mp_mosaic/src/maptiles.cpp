/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

mosaic_canvas map_tiles(const source_image& source,
                        const std::vector<tile_image>& tiles)
{
    /**
     * @todo Implement this function!
     */
       vector< point<3> > colors;
    vector< tile_image >::iterator it;
    
    //Build a map between average color and the tile that would generate the average color
    std::map<point<3>, tile_image> theMap;
    
    //Loop through the tiles
    //for (it = theTiles.begin(); it != theTiles.end(); it++)
    for (int i = 0; i < tiles.size(); i++)
    {
        //get average color
        epng::rgba_pixel pi = tiles.at(i).average_color();
        point<3> po(pi.red, pi.green, pi.blue);
        
        //map it
        theMap[po] = tiles.at(i);
        
        //put in vector
        colors.push_back(po);
    }

    //Call kdtree constructor
    kd_tree<3>::kd_tree tree(colors);

    //Start building the canvas
    //Declare a new canvas
    int r = source.rows();
    int c = source.columns();
    mosaic_canvas::mosaic_canvas canvas(r, c);

    //loop through each tile
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            //for each tile: 
            //grab the pixel from source
            epng::rgba_pixel regionColor = source.region_color(i, j); 
            //find the closest average color from kdtree using NNS
            point<3> regionPoint(regionColor.red, regionColor.green, regionColor.blue);
            point<3> closestPoint = tree.find_nearest_neighbor(regionPoint);
            //use the map to find the tile 
            tile_image theTile = theMap[closestPoint];

            //put the tile onto canvas
            canvas.set_tile(i,j,theTile);
        }
    }

    //return canvas
    return canvas;


}
