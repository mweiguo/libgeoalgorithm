#include <QApplication>
#include <QPushButton>
#include "qviewport.h"
#include "interface.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QViewport vp( "viewport 1" );
    vp.resize(400, 300);
    vp.show();

    // create shape
    int layerid = layer_create ( "layerOne" );
    int lodid = lod_create();
    add_child ( layerid, lodid );
    int rectid = rectangle_create ();
    rectangle_size ( rectid, 10, 6 );
    add_child ( lodid, rectid );

    rectid = rectangle_create ();
    rectangle_size ( rectid, 8, 3 );
    add_child ( lodid, rectid );

    return app.exec();
}
