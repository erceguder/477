#ifndef ECLIPSEMAP_H
#define ECLIPSEMAP_H

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <jpeglib.h>
#include <math.h>

#include "glm/glm/ext.hpp"
#include "Shader.h"
#include "glm/glm/glm.hpp"

#define PI 3.14159265359

#define MOON_INITIAL_Y 2600

using namespace std;

struct vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;

    vertex() {}

    vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texture) : position(position),
                                                                                           normal(normal),
                                                                                           texture(texture) {}
};

struct triangle {
    int vertex1;
    int vertex2;
    int vertex3;

    triangle() {}

    triangle(const int &vertex1, const int &vertex2, const int &vertex3) : vertex1(vertex1), vertex2(vertex2),
                                                                           vertex3(vertex3) {}
};

class EclipseMap {
private:
    float heightFactor = 80;
    float textureOffset = 0;
    float orbitDegree = 0;
    glm::vec3 lightPos = glm::vec3(0, 4000, 0);
    bool pKeyPressed = false;
    
    // DISPLAY SETTINGS
    enum displayFormatOptions {
        windowed = 1, fullScreen = 0
    };

    const char *windowName = "Ceng477 - HW3";
    int defaultScreenWidth = 700;
    int defaultScreenHeight = 700;
    int screenWidth = defaultScreenWidth;
    int screenHeight = defaultScreenHeight;
    int displayFormat = displayFormatOptions::windowed;

    float moonX = 0;
    float moonY = MOON_INITIAL_Y;
    
    // CAMERA SETTINGS
    float projectionAngle = 45;
    float aspectRatio = 1;
    float near = 0.1;
    float far = 10000;
    float startPitch = -45;
    float startYaw = 270;
    float startSpeed = 0;
    float pitch = startPitch;
    float yaw = startYaw;
    float speed = startSpeed;
    glm::vec3 cameraStartPosition = glm::vec3(0, 4000, 4000);
    glm::vec3 cameraStartDirection = glm::vec3(0, -1, -1);
    glm::vec3 cameraStartUp = glm::vec3(0, 0, 1);
    glm::vec3 cameraUp = cameraStartUp;
    glm::vec3 cameraPosition = cameraStartPosition;
    glm::vec3 cameraDirection = cameraStartDirection;
public:
    unsigned int textureColor;
    unsigned int textureGrey;
    unsigned int VAO;
    unsigned int VBO, EBO;
    float imageHeight;
    float imageWidth;
    float radius = 600;
    int horizontalSplitCount = 250;
    int verticalSplitCount = 125;

    unsigned int moonTextureColor;
    unsigned int moonVAO;
    unsigned int moonVBO, moonEBO;
    float moonImageHeight;
    float moonImageWidth;
    float moonRadius = 162;

    vector<float> worldVertices;
    vector<float> moonVertices;
    vector<unsigned int> indices;

    GLFWwindow *openWindow(const char *windowName, int width, int height);

    void Render(const char *coloredTexturePath, const char *greyTexturePath, const char *moonTexturePath);

    void handleKeyPress(GLFWwindow *window);

    void initColoredTexture(const char *filename, GLuint shader);

    void initGreyTexture(const char *filename, GLuint shader);

    void initMoonColoredTexture(const char *filename, GLuint shader);

    void initMoonBuffers();
    void initEarthBuffers();

    void initIndices();
    void initVertices();

    void updateCamera();
};

#endif
