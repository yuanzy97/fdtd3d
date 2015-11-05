#include <iostream>

#include "BMPLoader.h"

void
BMPLoader::LoadGrid (Grid& grid) const
{
  #if defined (GRID_1D)
    load1D (grid);
  #else
  #if defined (GRID_2D)
    load2D (grid);
  #else
  #if defined (GRID_3D)
    load3D (grid);
  #endif
  #endif
  #endif
}

/*
 * Return value according to colors of pixel.
 * Blue-Green-Red scheme.
 */
FieldValue
BMPLoader::getValueFromPixel (const RGBApixel& pixel, const FieldValue& maxNeg,
                              const FieldValue& max) const
{
  FieldValue retval = 0;

  return retval;
}

void
BMPLoader::loadFlat (Grid& grid, const grid_iter& sx, const grid_iter& sy) const
{
  // Create image for current values and max/min values
  BMP imageCur;
  imageCur.SetSize (sx, sy);
  imageCur.SetBitDepth (24);

  // Create image for previous values and max/min values
#if defined (ONE_TIME_STEP) || defined (TWO_TIME_STEPS)
  BMP imagePrev;
  imagePrev.SetSize (sx, sy);
  imagePrev.SetBitDepth (24);

  // Create image for previous previous values and max/min values
#if defined (TWO_TIME_STEPS)
  BMP imagePrevPrev;
  imagePrevPrev.SetSize (sx, sy);
  imagePrevPrev.SetBitDepth (24);
#endif
#endif


  // Set max
  const FieldValue maxCur = maxValuePos.getCurValue () - maxValueNeg.getCurValue ();
#if defined (ONE_TIME_STEP) || defined (TWO_TIME_STEPS)
  const FieldValue maxPrev = maxValuePos.getPrevValue () - maxValueNeg.getPrevValue ();
#if defined (TWO_TIME_STEPS)
  const FieldValue maxPrevPrev = maxValuePos.getPrevPrevValue () - maxValueNeg.getPrevPrevValue ();
#endif
#endif


  // Load images from files
  imageCur.ReadFromFile (cur.c_str());
#if defined (ONE_TIME_STEP) || defined (TWO_TIME_STEPS)
  if (type == ALL)
  {
    imagePrev.ReadFromFile (prev.c_str());
  }
#if defined (TWO_TIME_STEPS)
  if (type == ALL)
  {
    imagePrevPrev.ReadFromFile (prevPrev.c_str());
  }
#endif
#endif


  // Go through all values and set them
  VectorFieldPointValues& values = grid.getValues ();
  grid_iter end = values.size ();
  for (grid_iter iter = 0; iter < end; ++iter)
  {
    // Get current point value
    FieldPointValue& current = values[iter];
    // Calculate its position from index in array
    GridCoordinate coord = grid.calculatePositionFromIndex (iter);

    // Pixel coordinate
#if defined (GRID_1D)
    grid_iter px = coord.getX ();
    grid_iter py = 0;
#else
#if defined (GRID_2D)
    grid_iter px = coord.getX ();
    grid_iter py = coord.getY ();
#endif
#endif

  // Get pixel for current image
  RGBApixel pixelCur = imageCur.GetPixel(px, py);
#if defined (ONE_TIME_STEP) || defined (TWO_TIME_STEPS)
  // Get pixel for previous image
  RGBApixel pixelPrev;
  if (type == ALL)
  {
    pixelPrev = imagePrev.GetPixel(px, py);
  }
#if defined (TWO_TIME_STEPS)
  // Get pixel for previous previous image
  RGBApixel pixelPrevPrev;
  if (type == ALL)
  {
    pixelPrevPrev = imagePrevPrev.GetPixel(px, py);
  }
#endif
#endif

    // Set value for current image
    FieldValue currentVal = getValueFromPixel (pixelCur, maxValueNeg.getCurValue (), maxCur);
    current.setCurValue (currentVal);
#if defined (ONE_TIME_STEP) || defined (TWO_TIME_STEPS)
    // Set value for previous image
    FieldValue prevVal = getValueFromPixel (pixelPrev, maxValueNeg.getPrevValue (), maxPrev);
    current.setPrevValue (prevVal);
#if defined (TWO_TIME_STEPS)
    // Set value for previous previous image
    FieldValue prevPrevVal = getValueFromPixel (pixelPrevPrev, maxValueNeg.getPrevPrevValue (), maxPrevPrev);
    current.setPrevPrevValue (prevPrevVal);
#endif
#endif
  }
}

#if defined (GRID_1D)
void
BMPLoader::load1D (Grid& grid) const
{

}
#endif

#if defined (GRID_2D)
void
BMPLoader::load2D (Grid& grid) const
{

}
#endif

#if defined (GRID_3D)
void
BMPLoader::load3D (Grid& grid) const
{

}
#endif
