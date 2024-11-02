#include "startupanimation.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <opencv2/opencv.hpp>
#include "registerwin.h"
#include <QDebug>
StartupAnimation::StartupAnimation()
{

}

void StartupAnimation::playStartupAnimation(const std::string &videoPath) {
    cv::VideoCapture cap(videoPath);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return;
    }

    cv::Mat frame;
    while (true) {
        cap >> frame; \
        if (frame.empty()) break; \

        cv::imshow("Startup Animation", frame);\

        // 以 30ms 的延迟显示每一帧
        if (cv::waitKey(30) >= 0) break;
    }

    cap.release();
    cv::destroyAllWindows();
    qDebug()<<"[INFO] 先用register代替";
    RegisterWin *reg = new RegisterWin;
    reg->show();


}
