#ifndef IMGPPM_H
#define IMGPPM_H

#include "Image.h"
class ImgPPM : public Image {
public:
	ImgPPM (std::string);
	ImgPPM& operator= (const ImgPPM&);
	ImgPPM(const ImgPPM&);
	
	Image* grayscale();
	Image* monochrome();
	Image* histogram(int channel);
};


#endif