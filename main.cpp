#include <iostream>
#include <cassert>
using namespace std;

#include <opencv/cv.hpp>
using namespace cv;

#include "text_capture.h"
#include "non_blocking_input.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "Usage: {executable_name} {video_file_name} {text_file_name}" << endl;
        return 1;
    }

    char *video_file_name = argv[1];
    char *text_file_name = argv[2];

    VideoCapture video_reader(video_file_name);
    TextCapture text_reader(text_file_name);

    int output_count = 0;
    bool recording = false;
    VideoWriter video_writer;
    ofstream text_writer;

    while (true) {
        static Mat frame;
        static string text;

        video_reader >> frame;
        text = text_reader.next_line();

        if (frame.empty() || text.empty()) {
            cerr << "EOF" << endl;
            break;
        }

        int key = getkey();
        if (key != -1) {
            cerr << "User Input: " << key << endl;
            if (key == 10) { //ENTER
                recording ^= 1; //toggle state
                if (recording) {
                    ++output_count;
                    video_writer.open(to_string(output_count) + ".avi", CV_FOURCC('X', 'V', 'I', 'D'), 10, Size(frame.cols, frame.rows));
                    text_writer.open((to_string(output_count) + ".txt").c_str());
                } else {
                    video_writer.release();
                    text_writer.close();
                }
            }
        }

        imshow("video", frame);
        if (recording) {
            video_writer << frame;
            text_writer << text << endl;

            cerr << "Saved: " << text << endl;
        } else {
            cerr << "Skipped: " << text << endl;
        }
        waitKey(50);
    }
    return 0;
}
