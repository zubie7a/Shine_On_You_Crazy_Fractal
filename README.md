##Santiago Zubieta
####2012

#Shine On You Crazy Fractal

###Description
This app was developed at first just to paint the **Julia Set** (a subset of the Mandelbrot Set) of Fractals. A Julia Set is generated using a fixed point in the Complex Plane as a seed when evaluating all the points of the plane in a quadratic polynomial. The Mandelbrot Set uses each point where its evaluating the polynomial as the seed. This was done using **SFML 2.0 in C++** and for educational purposes, and is licensed for use under the **MIT License.**

What I thought then was, what if I draw several Julia Sets per frame, varying slightly the 'fixed seed' parameter? This results in an animation of 'evolving' Julia Sets, since the proximity of the seed values yields similar Julia Sets. When people think of fractals, they first think of zooming them up infinitely which has nice psychedelic patterns showing up. But what about fractals that don't zoom, but mutate? That leads to nice psychedelic patterns forming too!

The variation in seed points can be done in two ways, first, as a traversal of the complex plane in 'zigzag', like a scan, going from a left X limit to a right X limit, and upon reaching the right X limit, carrying on to a lower Y value from the starting X point. The second way is a spiral, starting at a fixed radius, and traversing all the points that go along the circle describing that radius. Then increasing the radius a bit, and traversing all the new points. This could be thought of a kinda spiralish way to traverse the plane, up to reaching a certain radius limit.

**Julia Set** 
[Wikipedia Link](https://en.wikipedia.org/wiki/Julia_set)

###Showcasing Video
[![](https://raw2.github.com/Zubieta/Shine_On_You_Crazy_Fractal/master/Screenshots/Screen_Shine.png)](https://www.youtube.com/watch?v=-Lhw-qdXUis)

###Some Poetry
*For all those fractal hearts  
Convoluted, and complex  
No matter how deep, full of detail  
The intrinsic logic of the universe*  

And when I watch this video, I can't help but notice how it continously cycles from two separate main bodies into a single one and viceversa. It looks as if two galaxies were dancing around each other, merging, and separating, and merging, and separating. The dynamics of galaxy collissions shows that when they collide, they sort of dance around each other, then separate, then go across each other again, until their cores merge. **Luckily for fractals, their dance can go on forever.**