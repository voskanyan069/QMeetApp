#ifndef __UI_CAMERAWIDGET_HXX__
#define __UI_CAMERAWIDGET_HXX__

#include <QWidget>
#include <QLabel>
#include <QResizeEvent>
#include <QPaintEvent>

namespace IO
{
    class Camera;
}

class CameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraWidget(QWidget* parent = nullptr, int id = 0);

public:
    int GetID() const;

protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    void initCamera();
    void updateCameraFrame();

private:
    int m_id;
    IO::Camera* m_camDevice;
    QLabel* m_uiCameraView;
};

#endif // !__UI_CAMERAWIDGET_HXX__
