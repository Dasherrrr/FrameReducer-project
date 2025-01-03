#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments are passed
    if (argc != 4) {
        cout << "Usage: <program> <input video> <output video> <desired fps>" << endl;
        return -1;
    }

    // Parse the input arguments
    string inputPath = argv[1];
    string outputPath = argv[2];
    int desiredFPS = atoi(argv[3]);  // Convert the desired FPS argument to an integer

    // Open the input video
    VideoCapture inputVideo(inputPath);
    if (!inputVideo.isOpened()) {
        cout << "Error: Could not open the video file!" << endl;
        return -1;
    }

    // Get the input video properties
    int inputFPS = static_cast<int>(inputVideo.get(CAP_PROP_FPS));
    Size frameSize = Size((int)inputVideo.get(CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CAP_PROP_FRAME_HEIGHT));

    cout << "Input FPS: " << inputFPS << " -> Desired FPS: " << desiredFPS << endl;

    // Specify the codec for output video (use 'mp4v' for MP4 format or 'H264' for H.264 codec)
    int codec = VideoWriter::fourcc('m', 'p', '4', 'v'); // MPEG-4 codec (works well with MP4)
    // If you want H.264, use: int codec = VideoWriter::fourcc('H', '2', '6', '4'); if FFmpeg supports it

    // Create the VideoWriter to write the output video
    VideoWriter outputVideo(outputPath, codec, desiredFPS, frameSize, true);  // true for color video
    if (!outputVideo.isOpened()) {
        cout << "Error: Could not open the output video file!" << endl;
        return -1;
    }

    // Read and process the video frames
    Mat frame;
    int frameCount = 0;
    while (true) {
        inputVideo >> frame;  // Capture a frame
        if (frame.empty()) {
            break;  // End of video
        }

        // Only write one frame every (inputFPS / desiredFPS) frames
        if (frameCount % (inputFPS / desiredFPS) == 0) {
            outputVideo.write(frame);  // Write the frame to the output video
        }

        frameCount++;
    }

    // Release resources
    inputVideo.release();
    outputVideo.release();

    cout << "Video processing complete!" << endl;
    return 0;
}
