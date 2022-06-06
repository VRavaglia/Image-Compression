//
// Created by Victor on 03/06/2022.
//

#ifndef WAVELETS_ENCODERWRAPPER_H
#define WAVELETS_ENCODERWRAPPER_H

#include <string>
#include "VQ.h"
extern "C"
{
#include "subdefs2.h"
}

using namespace std;

struct codebookInfo
{
    unsigned cbSize = 0;
    unsigned blockH = 0;
    unsigned blockW = 0;
    unsigned blocks = 0;
};

class EncoderWrapper {
private:
    static void write_header(FILE *fout, const vector<vector<performance>> &performances, unsigned bestCodebooks[NBANDS], const unsigned *dims);
    static codebookInfo get_cb_info(int codebook_index, const unsigned *dims, int subband);
public:
    static void encode(const string& in, const string& out);
    static void decode(const string& filename);
};


#endif //WAVELETS_ENCODERWRAPPER_H
