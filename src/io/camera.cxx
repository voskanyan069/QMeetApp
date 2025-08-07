#include "io/camera.hxx"
#include "sys/exception.hxx"
#include "sys/macro.hxx"

#include <opencv2/opencv.hpp>

IO::Camera::Camera(int idx, int w, int h)
    : m_pCap(new cv::VideoCapture(idx, cv::CAP_V4L2))
    , m_width(w)
    , m_height(h)
    , m_cameraIdx(idx)
{
}

IO::Camera::~Camera()
{
    SAFE_DELETE(m_pCap);
}

void IO::Camera::Init()
{
    m_pCap->set(cv::CAP_PROP_FRAME_WIDTH, m_width);
    m_pCap->set(cv::CAP_PROP_FRAME_HEIGHT, m_height);
    if ( ! m_pCap->isOpened() )
    {
        throw Sys::Exception("Could not open camera");
    }
}

void IO::Camera::ReadFrame(cv::Mat& frame) const
{
    (*m_pCap) >> frame;
}

void IO::Camera::ReverseFrame(cv::Mat& frame) const
{
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
}

int IO::Camera::GetCameraIndex() const
{
    return m_cameraIdx;
}
