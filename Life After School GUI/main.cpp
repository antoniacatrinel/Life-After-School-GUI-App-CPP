#include "UserRepoSelect.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QGuiApplication::setApplicationDisplayName("Life After School :)");
    UserRepoSelect userRepo;
    userRepo.show();
    return a.exec();
}
