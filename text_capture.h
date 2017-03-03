#ifndef TEXT_CAPTURE_H
#define TEXT_CAPTURE_H

#include <fstream>

using namespace std;

class TextCapture {
public:
    ifstream fin;
    TextCapture(const char *file_name) {
        fin.open(file_name);
    }

    string next_line() {
        string text;
        getline(fin, text);
        return text;
    }
};

#endif // TEXT_CAPTURE_H