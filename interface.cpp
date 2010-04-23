// camera management
static int seed = 0;
int create_camera ()
{
  CameraMgr::getInst().addCamera ( seed );
  return seed++;
}

void delete_camera ( int id )
{
  CameraMgr::getInst().erase ( seed );
}

void camera_props ( int id, float scale, float tx, float ty, float tz )
{
  CameraOrtho* cam = CameraMgr::getInst()[id];
  if ( NULL == cam )
    return;
  cam->zoom  ( scale );
  cam->translate ( tx, ty, tz );
}

int create_viewport ()
{
  ViewportMgr::getInst().addViewport ( seed );
  return seed++;
}

void delete_viewport ( int id )
{
  ViewportMgr::getInst().erase ( id );
}

void viewport_geometry ( int id, int x, int y, int w, int h )
{
  Viewport* p = ViewportMgr::getInst()[id];
  if ( NULL == p )
    return;
  p->position ( x, y );
  p->size ( w, h )
}

void viewport_camera ( int id, int camid )
{
  CameraOrtho* cam = CameraMgr::getInst()[camid];
  Viewport* p = ViewportMgr::getInst()[id];
  if ( NULL == cam || NULL == p )
    return;

  p->attachcamera ( cam );
}

void viewport_name ( int id, const char* nm )
{
  Viewport* p = ViewportMgr::getInst()[id];
  if ( NULL == p )
    return;
  p->name ( name );
}

int load_mesh ()
{
}

void unload_mesh (int id)
{
}
