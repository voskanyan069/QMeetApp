#ifndef __IO_CAMERA_HXX__
#define __IO_CAMERA_HXX__

namespace cv
{
    class Mat;
    class VideoCapture;
}

namespace IO
{
    class Camera;
}

class IO::Camera
{
public:
    Camera(int id = 0, int w = 640, int h = 480);
    ~Camera();

public:
    void Init();
    void ReadFrame(cv::Mat& frame) const;

private:
    cv::VideoCapture* m_pCap;
    int m_width;
    int m_height;
};

#endif // !__IO_CAMERA_HXX__
