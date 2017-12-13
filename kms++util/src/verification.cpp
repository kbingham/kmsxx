
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

}
