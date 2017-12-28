#ifndef IMGPGM_H
#define IMGPGM_H

#include "Image.h"

class ImgPGM : public Image {
public:
	ImgPGM (std::string);
	ImgPGM& operator= (const ImgPGM&);
	ImgPGM(const ImgPGM&);
	
	Image* monochrome();
};


#endif