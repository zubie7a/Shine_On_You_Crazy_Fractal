#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <complex>
#define imageWidth 800
#define imageHeight 800

struct Complex{
// Custom defined structure for holding a complex number.
    double real;
    double imag; 
    Complex(double re, double im) {
        real = re;
        imag = im;
    } 
};


double MinIm = -3;
double MaxIm =  3;
// Bounds for the imaginary axis. I set them to go from -3 to 3, but
// since the screen has many more pixels, we scale the position on the
// screen to a number in this range.
double MinRe = -3;
double MaxRe =  3;
// Bounds for the real axis. I set them to go from -3 to 3, but
// since the screen has many more pixels, we scale the position on the
// screen to a number in this range.

double Re_factor = (MaxRe - MinRe)/(imageWidth);
// Scaling factor for the real axis. 
double Im_factor = (MaxIm - MinIm)/(imageHeight);
// Scaling factor for the imaginary axis.

double kradius;
// Radius of the circle that gets bigger when scanning radially.
int cx[3];
// To hold the palette shifting values of RGB for the image hue.

Complex k(0,0);
Complex c(0,0);
Complex z(0,0);

sf::Image imagen;
sf::Texture mandtex;
sf::Sprite mandelb;
sf::Color col; 
// SFML variables for rendering.

bool dir;
// Direction of scanning.
bool mandel;
// To check whether we are drawing Mandelbrot Set or Julia Set.
bool draw;
// To check whether the application is running or paused.

bool comp(double a, double b) {
    return fabs(a - b) < 1e-5;
}


int fractal() {
    z.real = c.real;
    z.imag = c.imag;
    // c will be the initial seed value. For the Mandelbrot Set, it will be
    // every point on the plane, for the Julia Set, it will be a fixed K
    // for every point in the plane.
    if(mandel == false) {
    // If we are not really going to draw the Mandelbrot Set, use Julia Set's
    // fixed k value.
        c.real = k.real;
        c.imag = k.imag;
    }
    double re, im;
    // Helper variables for calculating the power of a complex number.
    int iters = 0;
    for(int n = 0; n < 64; ++n) {
    // 64 will be our limit of iterations.
        if(abs(z.real*z.real - z.imag*z.imag) > 4) {
        // It its outside the circle of radius 2, it means it has escaped, so
        // lets set the value of iterations it took for escaping and exit.
            iters = n;
            break;
        }
        re = z.real*z.real - z.imag*z.imag;
        // When powering a complex number to the 2, imag*imag will become real
        // and yield a -1.
        im = 2*z.real*z.imag;
        // whereas real*imag will become imag.
        z.real = re + c.real;
        z.imag = im + c.imag;
        // Because the iterative formula is Z_n+1 = Z_n^2 + C
    }
    return iters*2;
}

int* shifter(int cx[]) {
// Function to shift colors across a rainbow palette.
    int r,g,b;
    r = cx[0]; g = cx[1]; b = cx[2];
    if(r == 255 && g != 255 && b == 0  ) { cx[1] += 5; return cx; }
    // Increase green to go from red to yellow.
    if(r != 0   && g == 255 && b == 0  ) { cx[0] -= 5; return cx; }
    // Reduce red to go from yellow to green.
    if(r == 0   && g == 255 && b != 255) { cx[2] += 5; return cx; }
    // Increase blue to go from green to cyan.
    if(r == 0   && g != 0   && b == 255) { cx[1] -= 5; return cx; }
    // Reduce green to go from cyan to blue.
    if(r != 255 && g == 0   && b == 255) { cx[0] += 5; return cx; }
    // Increase red to go from blue to purple.
    if(r == 255 && g == 0   && b != 0  ) { cx[2] -= 5; return cx; }
    // Reduce blue to go from purple to red.
    return NULL;
}


void resolve() {
    shifter(cx);
    // Shift the palette for this iteration.
    for(int y = 0; y < imageHeight; ++y) {
    // In the imaginary axis...
        double c_im = MaxIm - (y * Im_factor);
        // The current imaginary is the max value minus the scaled vertical iterator.
        for(int x=0; x<imageWidth; ++x) {
        // In the real axis...
            double c_re = MinRe + (x * Re_factor);
            // The current real is the min value plus the scaled horizontal iterator.
            c.real = c_re;
            c.imag = c_im;
            // Change the real and imaginary components of the global complex variable c.
            int iters = fractal();
            // The returned value is the escape iterations for the current coordinate
            col = sf::Color(iters * 4, iters * 4, iters * 4, 255);
            // Create a color based on the current scape iterations.
            imagen.setPixel(x, y, col);
            // Set the image pixel at this current location to that color.
        }
    }
    mandtex.update(imagen);
    // Update the texture.
    mandelb.setTexture(mandtex);
    // Set the texture to the window.
}


void radialScan() {
// Scan the complex plane in a radial fashion, starting at the center and
// 'spiraling' out from there.
    if(dir == false) {
        if(!comp(k.real, -kradius)) {
        // Start reducing the real value until reaching the left bound of the
        // circle's radius.
            k.real -= kradius/10;
            // Reduce the real value by a bit of the radius value.
            k.imag = sqrt(kradius*kradius - k.real*k.real);
            // Find the imaginary value based on the real value and the circle's
            // radius (using Pythagoras Theorem).
            if(k.imag != k.imag) {
            // This happens when the result of the previous operation is a NaN.
            // NaN has this odd property of k != k being true.
                k.imag = 0;
            }
        }
        else{
        // We've finally reached the left boundary of the circle, where the real
        // value will be the negative radius, and imaginary value will be 0. We
        // have traversed so far only half circle (the upper half), we need to
        // generate the lower half.
            dir = true;
            k.real = -kradius;
            k.imag = 0;
        }
    }
    else{
        if(!comp(k.real, kradius)) {
        // Now the opposite, start increasing the real value until reaching the
        // right bound of the circle's radius.
            k.real += kradius/10;
           	// Increase the real value by a bit of the radius value.
            k.imag = -sqrt(kradius*kradius-k.real*k.real);
            // Find the imaginary value based on the real value and the circle's
            // radius (using Pythagoras Theorem) BUT make the result negative so
            // that it represents a point in the lower half of the circle.
            if(k.imag != k.imag) {
            // This happens when the result of the previous operation is a NaN.
            // NaN has this odd property of k != k being true.
                k.imag = 0;
            }                
        }
        else{
        // We've finally reached the left boundary of the circle, where the real
        // value will be the positive radius, and imaginary value will be 0. We
        // have traversed the complete circle, so lets increase the radius a bit
        // and then repeat the whole process!
            dir = false;
            kradius += 0.01;
            k.real = kradius;
            k.imag = 0;
        }
    }    
}

void horizontalScan() {
// Scan the complex plane in a horizontal fashion, from left to right, then go down
// a row, then from right to left, then go down another row, and so on, starting at
// the uppermost-left corner and finishing at the lowermost-right corner.
    if(!comp(k.real, 3) && dir == true) {
    // Increase the horizontal value until reaching 3.
        k.real += 0.02;
    }
    else{
    // Upon reaching 3, change the direction, and start reducing horizontal value.
    // Also reduce one position of the vertical value, like a line break.
        if(comp(k.real, 3)) {
            dir = false;
            k.imag -= 0.02;
        }
    }
    if(!comp(k.real, -3) && dir == false) {
    // Reduce the horizontal value until reaching -3.
        k.real -= 0.02;
    }
    else{
    // Upon reaching -3, change the direction, and start increasing horizontal value.
    // Also reduce the position of the vertical value, like a line break.
        if(comp(k.real, -3)) {
            dir = true;
            k.imag -= 0.02;
        }
    }
}

int main() {
    sf::RenderWindow App(sf::VideoMode(imageWidth, imageHeight), 
        "SFML Graphics",sf::Style::Fullscreen);
    // This is the SFML application initialization with the app's parameters
    cx[0] = 255; cx[1] = 0; cx[2] = 0;
    // The initial colors for the shifting
    kradius = 0.1;
    imagen.create(imageWidth,imageHeight);
    mandtex.create(imageWidth,imageHeight);
    // The scaling factor, defined by the ranges in Real and Imaginary axis,
    // divided by the respective axis real length.
    mandelb.setOrigin(imageWidth/2,imageHeight/2);
    mandelb.setPosition(640,400);
    mandelb.scale(1.5,1.5);
    // Set the image positioning, centering and scaling.
    k.real = 0;
    k.imag = 0;
    // Original K seed values.
    dir = false;
    // Direction of scan over the complex plane
    mandel = false;
    // false if painting Julia Set, true if Mandelbrot Set.
    draw = true;
    // To tell the application to pause or continue drawing, its switched by
    // pressing the right click.
    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
           // SFML works with an event loop
            if (Event.type == sf::Event::Closed){
            // If the window is closed, close the application
                App.close();
            }
            if( Event.type == Event.MouseButtonReleased
                && Event.mouseButton.button == sf::Mouse::Left){
            // If the left mouse is pressed and released, close the application
                App.close();
            }
            if( Event.type == Event.MouseButtonReleased
                && Event.mouseButton.button == sf::Mouse::Right){
            // If the right mouse is pressed and released, toggle randomness.
                draw = !draw;
            }
        }
        App.clear();
        if(!draw) continue;
        // If false, then stop animating and freeze in the last generated frame.
        resolve();
        //radialScan();
        horizontalScan();
        mandelb.setColor(sf::Color(cx[0], cx[1], cx[2]));
        // Shift the image hue.
        App.draw(mandelb);
        App.display();
    }
    return EXIT_SUCCESS;
}
