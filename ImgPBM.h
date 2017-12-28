#ifndef IMGPBM_H
#define IMGPBM_H

#include "Image.h"

class ImgPBM : public Image {
	public:
	ImgPBM (std::string);
	ImgPBM& operator= (const ImgPBM&);
	ImgPBM(const ImgPBM&);
	
	Image* monochrome();
};


#endif