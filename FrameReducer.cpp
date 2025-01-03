#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    
    if (argc != 4) {
        cout << "Usage: <program> <input video> <output video> <desired fps>" << endl;
        return -1;
    }

   
    string inputPath = argv[1];
    string outputPath = argv[2];
    int desiredFPS = atoi(argv[3]);  

    
    VideoCapture inputVideo(inputPath);
    if (!inputVideo.isOpened()) {
        cout << "Error: Could not open the video file!" << endl;
        return -1;
    }

   
    int inputFPS = static_cast<int>(inputVideo.get(CAP_PROP_FPS));
    Size frameSize = Size((int)inputVideo.get(CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CAP_PROP_FRAME_HEIGHT));

    cout << "Input FPS: " << inputFPS << " -> Desired FPS: " << desiredFPS << endl;

    
    int codec = VideoWriter::fourcc('m', 'p', '4', 'v'); 
   
    VideoWriter outputVideo(outputPath, codec, desiredFPS, frameSize, true);  // true for color video
    if (!outputVideo.isOpened()) {
        cout << "Error: Could not open the output video file!" << endl;
        return -1;
    }

    
    Mat frame;
    int frameCount = 0;
    while (true) {
        inputVideo >> frame;  // Capture a frame
        if (frame.empty()) {
            break;  // End of video
        }

       
        if (frameCount % (inputFPS / desiredFPS) == 0) {
            outputVideo.write(frame);  // Write the frame to the output video
        }

        frameCount++;
    }

   
    inputVideo.release();
    outputVideo.release();

    cout << "Video processing complete!" << endl;
    return 0;
}
