/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     int rows = theSource.getRows();
 	   int columns = theSource.getColumns();
 	   MosaicCanvas* mosaicImage = new MosaicCanvas(rows, columns);
 	   vector <Point<3> > pixelVector;
 	   vector <TileImage*> image;

     if(rows == 0 || columns == 0){
       return NULL;
     }

 	   for(size_t i = 0; i < theTiles.size(); i++){
       image.push_back(new TileImage());
       *image[i] = theTiles[i];
 		   HSLAPixel temp = theTiles[i].getAverageColor();
 		   Point <3> p = convertToLAB(temp);
 	     pixelVector.push_back(p);
 	   }

 	   KDTree <3> kd(pixelVector);
 	   for(int i = 0; i < rows; i++){
 		   for(int j = 0; j < columns; j++){
 			   HSLAPixel originalPixel = theSource.getRegionColor(i, j);
 			   Point <3> p = convertToLAB(originalPixel);
 			   Point <3> source = kd.findNearestNeighbor(p);
         for(size_t k = 0; k < pixelVector.size(); k++){
           if(pixelVector[k] == source){
             mosaicImage->setTile(i, j, image[k]);
           }
         }
       }
 	   }
     return mosaicImage;
  }

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
