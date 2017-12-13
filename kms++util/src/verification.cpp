
#include <kms++/kms++.h>
#include <kms++util/kms++util.h>

#include <fstream>

using namespace std;

namespace kms
{

void save_raw_frame(IFramebuffer& fb, const char *filename)
{
	unique_ptr<ofstream> os;
	os = unique_ptr<ofstream>(new ofstream(filename, ofstream::binary));

	for (unsigned i = 0; i < fb.num_planes(); ++i)
		os->write((char*)fb.map(i), fb.size(i));
}

float compare_framebuffers(IFramebuffer& a, IFramebuffer& b)
{
	unsigned int i;
	unsigned int pixels = a.width() * a.height();
	uint8_t *pa = a.map(0);
	uint8_t *pb = b.map(0);

	float diff = 0;

	if (a.format() != b.format())
		throw std::invalid_argument("Pixel formats differ...");

	if ((a.width() != b.width() ||
	    (a.height() != b.height())))
		throw std::invalid_argument("Frame sizes differ...");

	// Formats are identical, so num_planes are already identical
	for (i = 0; i < a.num_planes(); i++) {
		if ((a.offset(i) != b.offset(i)) ||
		    (a.stride(i) != b.stride(i)))
			throw std::invalid_argument("Planes differ...");
	}

	// Simple byte comparisons to start.
	// This expects a frame to be identical, including non-visible data.
	for (i = 0; i < a.size(0) && i < b.size(0); i++)
		diff += abs(pa[i] - pb[i]);

	return diff / pixels;
}

}
