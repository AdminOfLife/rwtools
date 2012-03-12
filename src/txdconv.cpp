#include "renderware.h"
using namespace std;

using namespace rw;

int main(int argc, char *argv[])
{
	if (sizeof(uint32) != 4 || sizeof(int32) != 4 ||
	    sizeof(uint16) != 2 || sizeof(int16) != 2 ||
	    sizeof(uint8)  != 1 || sizeof(int8)  != 1 ||
	    sizeof(float32) != 4) {
		cerr << "type size not correct\n";
	}
	if (argc < 3) {
		cerr << "Usage: " << argv[0] << " txd_in txd_out\n";
		return 1;
	}
	filename = argv[1];
	ifstream rw(argv[1], ios::binary);
	TextureDictionary txd;
	txd.read(rw);
	rw.close();
	for (uint32 i = 0; i < txd.texList.size(); i++) {
		if (txd.texList[i].platform == PLATFORM_PS2)
			txd.texList[i].convertFromPS2();
		if (txd.texList[i].platform == PLATFORM_XBOX)
			txd.texList[i].convertFromXbox();
		if (txd.texList[i].dxtCompression)
			txd.texList[i].decompressDxt();
		txd.texList[i].convertTo32Bit();
	}

	ofstream out(argv[2], ios::binary);
	version = VCPS2;
	txd.write(out);
	out.close();
}
