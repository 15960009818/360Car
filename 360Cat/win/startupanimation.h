#ifndef STARTUPANIMATION_H
#define STARTUPANIMATION_H

#include <QObject>

class StartupAnimation
{
public:
    StartupAnimation();
    void playStartupAnimation(const std::string &videoPath);
private:
    void settings_page();
};

#endif // STARTUPANIMATION_H
