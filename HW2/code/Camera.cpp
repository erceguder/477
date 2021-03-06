#include "Camera.h"


using namespace std;


Camera::Camera() {}


Camera::Camera(int cameraId,
               int projectionType,
               Vec3 pos, Vec3 gaze,
               Vec3 u, Vec3 v, Vec3 w,
               double left, double right, double bottom, double top,
               double near, double far,
               int horRes, int verRes,
               string outputFileName)
{

    this->cameraId = cameraId;
    this->projectionType = projectionType;
    this->pos = pos;
    this->gaze = gaze;
    this->u = u;
    this->v = v;
    this->w = w;
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;
    this->horRes = horRes;
    this->verRes = verRes;
    this->outputFileName = outputFileName;
}


Camera::Camera(const Camera &other)
{
    this->cameraId = other.cameraId;
    this->projectionType = other.projectionType;
    this->pos = other.pos;
    this->gaze = other.gaze;
    this->u = other.u;
    this->v = other.v;
    this->w = other.w;
    this->left = other.left;
    this->right = other.right;
    this->bottom = other.bottom;
    this->top = other.top;
    this->near = other.near;
    this->far = other.far;
    this->horRes = other.horRes;
    this->verRes = other.verRes;
    this->outputFileName = other.outputFileName;
}


// void Camera::correctUpVector(){
//     this->u = this->gaze * v;
//     this->v = this->gaze * u;
// }


Matrix4 Camera::getCamTrsMatrix(){

    double m_03 = -(u.x*pos.x + u.y*pos.y + u.z*pos.z);
    double m_13 = -(v.x*pos.x + v.y*pos.y + v.z*pos.z);
    double m_23 = -(w.x*pos.x + w.y*pos.y + w.z*pos.z);
    double m_33 = 1;

    double val[4][4] = {
        {u.x, u.y, u.z, m_03},
        {v.x, v.y, v.z, m_13},
        {w.x, w.y, w.z, m_23},
        {0, 0, 0, m_33}
    };

    return Matrix4(val);
}


Matrix4 Camera::getOrthoPrjMatrix(){

    double val[4][4] = {
        {2/(right-left), 0, 0, -(right+left)/(right-left)},
        {0, 2/(top-bottom), 0, -(top+bottom)/(top-bottom)},
        {0, 0, -2/(far-near), -(far+near)/(far-near)},
        {0, 0, 0, 1}
    };

    return Matrix4(val);
}


Matrix4 Camera::getPersPrjMatrix(){

    double val[4][4] = {
        {near, 0, 0, 0},
        {0, near, 0, 0},
        {0, 0, far+near, far*near},
        {0, 0, -1, 0}
    };

    Matrix4 m_p2o = Matrix4(val);
    Matrix4 m_orth = this->getOrthoPrjMatrix();

    return m_orth * m_p2o;
}

Matrix4 Camera::getViewportMatrix(){
    double val[4][4] = {
        {horRes/2., 0, 0, (horRes-1)/2.},
        {0, verRes/2., 0, (verRes-1)/2.},
        {0, 0, 0.5, 0.5},
        {0, 0, 0, 1}
    };
    return Matrix4(val);
}

ostream &operator<<(ostream &os, const Camera &c)
{
    const char *camType = c.projectionType ? "perspective" : "orthographic";

    os << fixed << setprecision(6) << "Camera " << c.cameraId << " (" << camType << ") => pos: " << c.pos << " gaze: " << c.gaze << endl
       << "\tu: " << c.u << " v: " << c.v << " w: " << c.w << endl
       << fixed << setprecision(3) << "\tleft: " << c.left << " right: " << c.right << " bottom: " << c.bottom << " top: " << c.top << endl
       << "\tnear: " << c.near << " far: " << c.far << " resolutions: " << c.horRes << "x" << c.verRes << " fileName: " << c.outputFileName;

    return os;
}