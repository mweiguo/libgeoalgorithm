#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QViewport vp( "viewport 1" );
    vp.resize(100, 30);

    vp.show();
    return app.exec();
}
