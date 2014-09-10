#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <complex>

struct Complex{
	double real;
	double imag; 
	Complex(double re, double im){
		real = re;
		imag = im;
	} 
};

double ImageHeight;
double ImageWidth;
double Re_factor;
double Im_factor;
double kside;
double MinIm;
double MaxIm;
double MinRe;
double MaxRe;
int cx[3];

std::complex <double> zz(0,0);
std::complex <double> cc(0,0);
sf::Sprite mandelb;
sf::Color col; 
Complex k(0,0);
Complex c(0,0);
Complex z(0,0);
sf::Image imagen;
sf::Texture mandtex;
bool dir;
bool mande;
bool split;
double i;
bool comp(double a, double b){
    return fabs(a - b) < 1e-5;
}


int mandelbrot(){
	z.real = c.real;
	z.imag = c.imag;
	if(mande==false){
		c.real = k.real;
		c.imag = k.imag;
	}
	double am,bm;
	int isInside = 0;
	for(int n=0; n<64; ++n){
		if(abs(z.real*z.real - z.imag*z.imag) > 4){
			isInside = n;
			break;
		}
		if(split == true){
			zz.real() = z.real;
			zz.imag() = z.imag;
			cc.real() = c.real;
			cc.imag() = c.imag;
			zz = pow(zz,i) + cc;
			z.real = zz.real();
			z.imag = zz.imag();
		}
		else{
			am = z.real*z.real - z.imag*z.imag + c.real;
			bm = 2*z.real*z.imag + c.imag;
			z.real = am;
			z.imag = bm;			
		}
	}
	return isInside*2;
}

int* swapper(int cx[]){
	int r,g,b;
	r = cx[0]; g = cx[1]; b = cx[2];
	if(r==255 && g!=255 && b==0){
		cx[1]+=5;
		return cx;
	}
	if(g==255 && b==0 && r!=0){
		cx[0]-=5;
		return cx;
	}
	if(r==0 && g==255 && b!=255){
		cx[2]+=5;
		return cx;
	}
	if(b==255 && r==0 && g!=0){
		cx[1]-=5;
		return cx;
	}
	if(b==255 && g==0 && r!=255){
		cx[0]+=5;
		return cx;
	}
	if(r==255 && g==0 && b!=0){
		cx[2]-=5;
		return cx;
	}
	return NULL;
}


void mankel(){
	swapper(cx);
	for(int y=0; y<ImageHeight; ++y){
		double c_im = MaxIm - y*Im_factor;
		for(int x=0; x<ImageWidth; ++x){
			double c_re = MinRe + x*Re_factor;
			c.real = c_re;
			c.imag = c_im;
			int zz = mandelbrot();
			col = sf::Color(zz*4,zz*4,zz*4,255);
			imagen.setPixel(x, y, col);
		}
	}
	mandtex.update(imagen);
	mandelb.setTexture(mandtex);
}


void radialScan(){
	if(dir==false){
		if(!comp(k.real,-kside)){
			k.real -= kside/10;
			k.imag = sqrt(kside*kside-k.real*k.real);
			if(k.imag != k.imag){
				k.imag = 0;
			}
		}
		else{
			dir = true;
			k.real = -kside;
			k.imag = 0;
		}
	}
	else{
		if(!comp(k.real,kside)){
			k.real += kside/10;
			k.imag = -sqrt(kside*kside-k.real*k.real);
			if(k.imag != k.imag){
				k.imag = 0;
			}				
		}
		else{
			dir = false;
			kside += 0.01;
			k.real = kside;
			k.imag = 0;
		}
	}	
}

void horizontalScan(){
	if(!comp(k.real,3) && dir==true){
		k.real += 0.02;
	}
	else{
		if(comp(k.real,3)){
			dir = false;
			k.imag -= 0.02;
		}
	}
	if(!comp(k.real,-3) && dir==false){
		k.real -= 0.02;
	}
	else{
		if(comp(k.real,-3)){
			dir = true;
			k.imag -= 0.02;
		}
	}
}

int main(){
	sf::RenderWindow App(sf::VideoMode(700,700), "SFML Graphics",sf::Style::Fullscreen);
	cx[0] = 255;
	cx[1] = 0;
	cx[2] = 0;
	i = 1;
	kside = 0.1;
	MinIm = MinRe = -3;
	MaxIm = MaxRe = 3;
	ImageWidth = ImageHeight = 700;
	imagen.create(ImageWidth,ImageHeight);
	mandtex.create(ImageWidth,ImageHeight);
	Re_factor = (MaxRe-MinRe)/(ImageWidth);
	Im_factor = (MaxIm-MinIm)/(ImageHeight);
	mandelb.setOrigin(350,350);
	mandelb.setPosition(640,400);
	mandelb.scale(1.5,1.5);
	k.real = kside;
	k.imag = 0;
	//k.real = -3;
	//k.imag = 1.2;
	dir = false;
	mande = false;
	split = false;
	while (App.isOpen()){
        sf::Event Event;
        while (App.pollEvent(Event)){
            if (Event.type == sf::Event::Closed)
                App.close();
        }
        App.clear();
		mankel();
		radialScan();
		//horizontalScan();
		//i+=0.1;
		mandelb.setColor(sf::Color(cx[0],cx[1],cx[2]));
		if(mande==true){
			//mandelb.SetRotation(i);
		}
		App.draw(mandelb);
		App.display();
	}
    return EXIT_SUCCESS;
}
