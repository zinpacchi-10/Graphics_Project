#include <windows.h>
#include <GL/glut.h>
#include <mmsystem.h>
#include<cmath>
#include <cstdio>




float riverOffset = 0.0f;
float riverSpeed = 0.001f;
// Ship variables
float ship1X = -0.8f, ship1Y = -0.9f;
float ship2X = 0.7f, ship2Y = -0.85f;
float shipSpeed = 0.0003f;

float rayRotationA = 0.0f;
//cloud
float cloud1X = -1.5f, cloud1Y = 0.6f;
float cloud2X = -2.0f, cloud2Y = 0.7f;
float cloud3X = -1.8f, cloud3Y = 0.8f;
float cloud4X = -1.0f, cloud4Y = 0.5f;
float cloud5X = -0.5f, cloud5Y = 0.65f;
float cloud6X = -1.8f, cloud6Y = 0.75f;
float cloud7X = -1.2f, cloud7Y = 0.85f;
float cloudSpeed = 0.00009f;
// Bird variables
float birdX[10] = {-1.0f, -0.8f, -0.6f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 0.6f, 0.8f};
float birdY[10] = {0.6f, 0.7f, 0.65f, 0.72f, 0.68f, 0.66f, 0.7f, 0.63f, 0.69f, 0.71f};
float birdSpeed[10] = {0.0005f, 0.0007f, 0.0004f, 0.0006f, 0.0008f, 0.00055f, 0.00065f, 0.00045f, 0.00075f, 0.0005f};
int birdType[10] = {1,2,3,4,5,1,2,3,4,5};

int countdown = 15;
int lastTime = 0;
bool showCountdown = true;
int frameCount = 0;

// Antena animation
float antennaRotation = 0.0f;
float antennaSpeed = 0.09f;         // How fast it swings
bool antennaForward = true;        // Direction flag

float antenna1Rotation = 0.0f;
float antenna1Speed = 0.1f;
bool antenna1Forward = true;





void drawCircleA(float x, float y, float radius) {
    int numSegments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawEllipseA(float x_center, float y_center, float a, float b) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float x = x_center + a * cosf(angle);
        float y = y_center + b * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}


void drawTriangleA(float x1, float y1, float x2, float y2, float x3, float y3) {

    glBegin(GL_TRIANGLES);

    glVertex2f(x1, y1);

    glVertex2f(x2, y2);

    glVertex2f(x3, y3);

    glEnd();

}


void drawQuadA(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

    glBegin(GL_QUADS);

    glVertex2f(x1, y1);

    glVertex2f(x2, y2);

    glVertex2f(x3, y3);

    glVertex2f(x4, y4);

    glEnd();


}


float rocketYA = 2.6f;
float rocketSpeedA = 0.003f;
float upperFlameOffsetA = 0.0f;
bool flameUpa = true;
float lowerFlameOffsetA = 0.0f;
bool lowerFlameUpA = true;
float rocketflyA = 0.0f;

void drawLowerStageA(float stageY) {

    const GLfloat bodyR = 0.92f, bodyG = 0.94f, bodyB = 0.98f;
    const GLfloat finR  = 0.80f, finG  = 0.15f, finB  = 0.15f;
    const GLfloat rimR  = 0.95f, rimG  = 0.95f, rimB  = 0.98f;
    const GLfloat glassR= 0.30f, glassG= 0.70f, glassB= 0.90f;
    const GLfloat darkR = 0.12f, darkG = 0.12f, darkB = 0.12f;
    const GLfloat accentR = 0.90f, accentG = 0.60f, accentB = 0.10f;

    glPushMatrix();
    glScalef(0.6f, 0.6f, 0.0f);
    glTranslatef(-1.8f, stageY, 0.0f);

    glColor3f(bodyR, bodyG, bodyB);
    glBegin(GL_QUADS);
        glVertex2f(-0.20f, -0.65f);
        glVertex2f( 0.20f, -0.65f);
        glVertex2f( 0.173f,  0.0f);
        glVertex2f(-0.173f,  0.0f);
    glEnd();

    // Lower center
    glColor3f(0.98f, 0.98f, 1.00f);
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, -0.60f);
        glVertex2f( 0.03f, -0.60f);
        glVertex2f( 0.03f,   0.0f);
        glVertex2f(-0.03f,   0.0f);
    glEnd();

    // Lower left side
    glColor3f(0.85f, 0.87f, 0.92f);
    glBegin(GL_QUADS);
        glVertex2f(-0.20f, -0.60f);
        glVertex2f(-0.18f, -0.60f);
        glVertex2f(-0.158f,  0.0f);
        glVertex2f(-0.178f,  0.0f);
    glEnd();

    // Lower right side
    glBegin(GL_QUADS);
        glVertex2f( 0.18f, -0.60f);
        glVertex2f( 0.20f, -0.60f);
        glVertex2f( 0.178f,  0.0f);
        glVertex2f( 0.158f,  0.0f);
    glEnd();

    // Lower decorative orange
    glColor3f(accentR, accentG, accentB);
    glBegin(GL_QUADS);
        glVertex2f(-0.18f, -0.10f);
        glVertex2f( 0.18f, -0.10f);
        glVertex2f( 0.18f, -0.06f);
        glVertex2f(-0.18f, -0.06f);
    glEnd();

    // Lower window
    glColor3f(rimR, rimG, rimB);
    drawCircleA(0.0f, -0.05f, 0.08f);
    glColor3f(glassR, glassG, glassB);
    drawCircleA(0.0f, -0.05f, 0.06f);

    // SIDE FINS
    glColor3f(darkR, darkG, darkB);
    glBegin(GL_POLYGON); // Left shadow fin
        glVertex2f(-0.20f, -0.20f);
        glVertex2f(-0.55f, -0.65f);
        glVertex2f(-0.45f, -0.70f);
        glVertex2f(-0.20f, -0.65f);
    glEnd();
    glBegin(GL_POLYGON); // Right shadow fin
        glVertex2f( 0.20f, -0.20f);
        glVertex2f( 0.55f, -0.65f);
        glVertex2f( 0.45f, -0.70f);
        glVertex2f( 0.20f, -0.65f);
    glEnd();

    glColor3f(finR, finG, finB);
    glBegin(GL_POLYGON); // Left red fin
        glVertex2f(-0.20f, -0.25f);
        glVertex2f(-0.50f, -0.65f);
        glVertex2f(-0.40f, -0.68f);
        glVertex2f(-0.20f, -0.64f);
    glEnd();
    glBegin(GL_POLYGON); // Right red fin
        glVertex2f( 0.20f, -0.25f);
        glVertex2f( 0.50f, -0.65f);
        glVertex2f( 0.40f, -0.68f);
        glVertex2f( 0.20f, -0.64f);
    glEnd();

    // NOZZLE
    glColor3f(darkR, darkG, darkB);
    glBegin(GL_POLYGON);
        glVertex2f(-0.18f, -0.65f);
        glVertex2f( 0.18f, -0.65f);
        glVertex2f( 0.22f, -0.85f);
        glVertex2f(-0.22f, -0.85f);
    glEnd();
    glColor3f(0.25f, 0.25f, 0.25f);
    drawEllipseA(0.0f, -0.85f, 0.22f, 0.05f); // Nozzle rim

    // FLAME
    glColor3f(1.00f, 0.55f, 0.00f); // Orange outer flame
    glBegin(GL_POLYGON);
        glVertex2f(-0.18f, -0.85f);
        glVertex2f( 0.18f, -0.85f);
        glVertex2f( 0.12f, -1.00f + lowerFlameOffsetA);
        glVertex2f( 0.06f, -1.10f + lowerFlameOffsetA);
        glVertex2f( 0.00f, -1.05f + lowerFlameOffsetA);
        glVertex2f(-0.06f, -1.10f + lowerFlameOffsetA);
        glVertex2f(-0.12f, -1.00f + lowerFlameOffsetA);
    glEnd();

    glColor3f(1.00f, 0.90f, 0.20f); // Yellow middle flame
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.10f, -0.85f);
        glVertex2f( 0.10f, -0.85f);
        glVertex2f( 0.00f, -1.05f + lowerFlameOffsetA);
    glEnd();

    glColor3f(1.00f, 0.98f, 0.95f); // White core flame
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, -0.85f);
        glVertex2f( 0.04f, -0.85f);
        glVertex2f( 0.03f, -0.95f + lowerFlameOffsetA);
        glVertex2f( 0.00f, -1.00f + lowerFlameOffsetA);
        glVertex2f(-0.03f, -0.95f + lowerFlameOffsetA);
    glEnd();

    glPopMatrix();
}


void upperRocketFlameA()
{

// Outer flame (orange)
glColor3f(1.00f, 0.55f, 0.00f);
glBegin(GL_POLYGON);
    glVertex2f(-0.12f, -0.14f);
    glVertex2f( 0.12f, -0.14f);
    glVertex2f( 0.08f, -0.29f + upperFlameOffsetA);
    glVertex2f( 0.04f, -0.39f + upperFlameOffsetA);
    glVertex2f( 0.00f, -0.34f + upperFlameOffsetA);
    glVertex2f(-0.04f, -0.39f + upperFlameOffsetA);
    glVertex2f(-0.08f, -0.29f + upperFlameOffsetA);
glEnd();

// Middle flame
glColor3f(1.00f, 0.90f, 0.20f);
glBegin(GL_TRIANGLES);
    glVertex2f(-0.08f, -0.14f);
    glVertex2f( 0.08f, -0.14f);
    glVertex2f( 0.00f, -0.34f + upperFlameOffsetA);
glEnd();

// Core flame
glColor3f(1.00f, 0.98f, 0.95f);
glBegin(GL_POLYGON);
    glVertex2f(-0.03f, -0.14f);
    glVertex2f( 0.03f, -0.14f);
    glVertex2f( 0.02f, -0.24f + upperFlameOffsetA);
    glVertex2f( 0.00f, -0.29f + upperFlameOffsetA);
    glVertex2f(-0.02f, -0.24f + upperFlameOffsetA);
glEnd();


}


void drawUpperStageA(float stageY) {
    const GLfloat bodyR = 0.92f, bodyG = 0.94f, bodyB = 0.98f;
    const GLfloat noseR = 0.88f, noseG = 0.15f, noseB = 0.15f;
    const GLfloat finR  = 0.80f, finG  = 0.15f, finB  = 0.15f;
    const GLfloat rimR  = 0.95f, rimG  = 0.95f, rimB  = 0.98f;
    const GLfloat glassR= 0.30f, glassG= 0.70f, glassB= 0.90f;
    const GLfloat darkR = 0.12f, darkG = 0.12f, darkB = 0.12f;
    const GLfloat accentR = 0.90f, accentG = 0.60f, accentB = 0.10f;

    glPushMatrix();
    glScalef(0.6f, 0.6f, 0.0f);
    glTranslatef(-1.8f, stageY, 0.0f);

    // Main body
    glColor3f(bodyR, bodyG, bodyB);
    drawQuadA(-0.173f, 0.0f, 0.173f, 0.0f, 0.14f, 0.75f, -0.14f, 0.75f);

    // Sheen and shading
    glColor3f(0.98f, 0.98f, 1.00f);
    drawQuadA(-0.03f, 0.0f, 0.03f, 0.0f, 0.03f, 0.70f, -0.03f, 0.70f);

    glColor3f(0.85f, 0.87f, 0.92f);
    drawQuadA(-0.178f, 0.0f, -0.158f, 0.0f, -0.12f, 0.70f, -0.15f, 0.70f);
    drawQuadA(0.158f, 0.0f, 0.178f, 0.0f, 0.15f, 0.70f, 0.12f, 0.70f);

    // Orange bands
    glColor3f(accentR, accentG, accentB);
    drawQuadA(-0.17f, 0.10f, 0.17f, 0.10f, 0.17f, 0.14f, -0.17f, 0.14f);
    drawQuadA(-0.17f, 0.30f, 0.17f, 0.30f, 0.17f, 0.34f, -0.17f, 0.34f);
    drawQuadA(-0.17f, 0.50f, 0.17f, 0.50f, 0.17f, 0.54f, -0.17f, 0.54f);
    drawQuadA(-0.17f, 0.65f, 0.17f, 0.65f, 0.17f, 0.69f, -0.17f, 0.69f);

    // Windows
    glColor3f(rimR, rimG, rimB);
    drawCircleA(0.0f, 0.20f, 0.09f);
    drawCircleA(0.0f, 0.45f, 0.04f);
    drawCircleA(0.0f, 0.60f, 0.06f);
    glColor3f(glassR, glassG, glassB);
    drawCircleA(0.0f, 0.20f, 0.07f);
    drawCircleA(0.0f, 0.45f, 0.02f);
    drawCircleA(0.0f, 0.60f, 0.04f);

    // RCS thrusters
    glColor3f(darkR, darkG, darkB);
    drawCircleA(-0.16f, 0.05f, 0.012f);
    drawCircleA( 0.16f, 0.05f, 0.012f);
    drawCircleA(-0.16f, 0.40f, 0.012f);
    drawCircleA( 0.16f, 0.40f, 0.012f);
    drawCircleA(-0.16f, 0.65f, 0.012f);
    drawCircleA( 0.16f, 0.65f, 0.012f);

// Left shadow fin
glColor3f(darkR, darkG, darkB);
glBegin(GL_TRIANGLES);
    glVertex2f(-0.16f, 0.26f);
    glVertex2f(-0.16f, 0.00f);
    glVertex2f(-0.36f, -0.04f);
glEnd();

// Right shadow fin
glBegin(GL_TRIANGLES);
    glVertex2f( 0.16f, 0.26f);
    glVertex2f( 0.16f, 0.00f);
    glVertex2f( 0.36f, -0.04f);
glEnd();

// Left red fin
glColor3f(finR, finG, finB);
glBegin(GL_TRIANGLES);
    glVertex2f(-0.16f, 0.25f);
    glVertex2f(-0.16f, 0.01f);
    glVertex2f(-0.32f, -0.03f);
glEnd();

// Right red fin
glBegin(GL_TRIANGLES);
    glVertex2f( 0.16f, 0.25f);
    glVertex2f( 0.16f, 0.01f);
    glVertex2f( 0.32f, -0.03f);
glEnd();



//Upper Stage Nozzle
glColor3f(darkR, darkG, darkB);
glBegin(GL_POLYGON);
    glVertex2f(-0.09f, 0.00f);
    glVertex2f( 0.09f, 0.00f);
    glVertex2f( 0.11f, -0.14f);
    glVertex2f(-0.11f, -0.14f);
glEnd();

// Nozzle rim
glColor3f(0.25f, 0.25f, 0.25f);
drawEllipseA(0.0f, -0.14f, 0.11f, 0.03f);


    // Rocket fire
   if (rocketYA > -1.40f)
   {
       upperRocketFlameA();
   }


    // Docking port
    glColor3f(0.3f, 0.3f, 0.3f);
    drawQuadA(-0.03f, 0.75f, 0.03f, 0.75f, 0.03f, 0.85f, -0.03f, 0.85f);
    glColor3f(0.8f, 0.8f, 0.8f);
    drawCircleA(0.0f, 0.87f, 0.008f);

    // Nose cone
    glColor3f(noseR, noseG, noseB);
    drawTriangleA(-0.14f, 0.75f, 0.14f, 0.75f, 0.00f, 1.05f);

    glPopMatrix();
}


void drawRocketA() {
glPushMatrix();
glTranslatef(-0.68f,-0.75f, 0.0f);
glScalef(0.55f, 0.55f , 1.0f);
glTranslatef(0.0f,rocketflyA, 0.0f);
    drawUpperStageA(rocketYA);
    drawLowerStageA(rocketYA);
glPopMatrix();
}


// Car variables
float carX = -1.5f;
float carY = -0.55f;
float carSpeed = 0.0005f;
void drawCar(float x, float y) {
    // Car body
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.10f, y + 0.05f);
        glVertex2f(x + 0.10f, y + 0.05f);
        glVertex2f(x + 0.10f, y);
        glVertex2f(x - 0.10f, y);
    glEnd();

    // Car roof
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.05f, y + 0.10f);
        glVertex2f(x + 0.05f, y + 0.10f);
        glVertex2f(x + 0.07f, y + 0.05f);
        glVertex2f(x - 0.07f, y + 0.05f);
    glEnd();

    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircleA(x - 0.06f, y - 0.01f, 0.02f);
    drawCircleA(x + 0.06f, y - 0.01f, 0.02f);
}


void drawBird(float x, float y) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(x - 0.02f, y);
        glVertex2f(x, y + 0.015f);
        glVertex2f(x + 0.02f, y);
    glEnd();
}

// Update bird positions
void updateBirds() {
    for(int i=0; i<10; i++){
        birdX[i] += birdSpeed[i];
        if(birdX[i] > 1.5f) birdX[i] = -1.5f;
    }
}


void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);


    drawCircleA(x, y, 0.08f);
    drawCircleA(x + 0.05f, y + 0.02f, 0.07f);
    drawCircleA(x - 0.05f, y + 0.02f, 0.06f);
}


void drawCloudVariant(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);

    drawCircleA(x, y, 0.06f);
    drawCircleA(x + 0.06f, y + 0.03f, 0.05f);
    drawCircleA(x - 0.05f, y + 0.02f, 0.04f);
    drawCircleA(x + 0.02f, y - 0.02f, 0.045f);
    drawCircleA(x - 0.03f, y - 0.01f, 0.035f);
}


void drawSunA() {
    float cx = 0.0f, cy = 0.8f;

    float outerGlow = 0.10f;
    float midGlow   = 0.07f;
    float innerGlow = 0.05f;
    float core      = 0.025f;

    // Outer glow (faint orange)
    glColor4f(1.0f, 0.5f, 0.0f, 0.2f);
    drawCircleA(cx, cy, outerGlow);

    // Mid glow
    glColor4f(1.0f, 0.7f, 0.0f, 0.3f);
    drawCircleA(cx, cy, midGlow);

    // Inner glow
    glColor4f(1.0f, 0.85f, 0.0f, 0.6f);
    drawCircleA(cx, cy, innerGlow);

    // Core (bright yellow)
    glColor3f(1.0f, 0.95f, 0.2f);
    drawCircleA(cx, cy, core);

   // Sun Rays using triangles
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glRotatef(rayRotationA, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 0.8f, 0.0f);

    int rays = 16;
    float rayInner = 0.11f;
    float rayOuter = 0.16f;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < rays; i++) {
        float angle = 2.0f * 3.1415926f * i / rays;

        float x1 = rayInner * cos(angle - 0.05f);
        float y1 = rayInner * sin(angle - 0.05f);

        float x2 = rayInner * cos(angle + 0.05f);
        float y2 = rayInner * sin(angle + 0.05f);

        float x3 = rayOuter * cos(angle);
        float y3 = rayOuter * sin(angle);

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    }

    glEnd();
    glPopMatrix();
}




void Grass(){
    glBegin(GL_QUADS);
    glColor3f(0.13f, 0.55f, 0.13f);//Grass
    glVertex3f(-2.0f,-0.62f,0.0f);
    glVertex3f(-2.0f,0.42f,0.0f);
    glVertex3f(2.0f,0.42f,0.0f);
    glVertex3f(2.0f,-0.62f,0.0f);
    glEnd();
}

void RiverSideLean(){
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-2.0f,-0.62f,0.0f);
    glVertex3f(-2.0f,-0.59f,0.0f);
    glVertex3f(2.0f,-0.59f,0.0f);
    glVertex3f(2.0f,-0.62f,0.0f);
    glEnd();
}


void Road(){
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex3f(-2.0f,-0.59f,0.0f);
    glVertex3f(-2.0f,-0.50f,0.0f);
    glVertex3f(2.0f,-0.50f,0.0f);
    glVertex3f(2.0f,-0.59f,0.0f);
    glEnd();
}

void RoadSideLean(){
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-2.0f,-0.50f,0.0f);
    glVertex3f(-2.0f,-0.47f,0.0f);
    glVertex3f(2.0f,-0.47f,0.0f);
    glVertex3f(2.0f,-0.50f,0.0f);
    glEnd();
}

void RoadSideMiddle(){
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-2.0f,-0.55f,0.0f);
    glVertex3f(2.0f,-0.55f,0.0f);
    glVertex3f(2.0f,-0.54f,0.0f);
    glVertex3f(-2.0f,-0.54f,0.0f);


    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.9f,-0.55f,0.0f);
    glVertex3f(1.9f,-0.55f,0.0f);
    glVertex3f(1.9f,-0.54f,0.0f);
    glVertex3f(-1.9f,-0.54f,0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.8f,-0.55f,0.0f);
    glVertex3f(1.8f,-0.55f,0.0f);
    glVertex3f(1.8f,-0.54f,0.0f);
    glVertex3f(-1.8f,-0.54f,0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.7f,-0.55f,0.0f);
    glVertex3f(1.7f,-0.55f,0.0f);
    glVertex3f(1.7f,-0.54f,0.0f);
    glVertex3f(-1.7f,-0.54f,0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.6f,-0.55f,0.0f);
    glVertex3f(1.6f,-0.55f,0.0f);
    glVertex3f(1.6f,-0.54f,0.0f);
    glVertex3f(-1.6f,-0.54f,0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.5f,-0.55f,0.0f);
    glVertex3f(1.5f,-0.55f,0.0f);
    glVertex3f(1.5f,-0.54f,0.0f);
    glVertex3f(-1.5f,-0.54f,0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.4f,-0.55f,0.0f);
    glVertex3f(1.4f,-0.55f,0.0f);
    glVertex3f(1.4f,-0.54f,0.0f);
    glVertex3f(-1.4f,-0.54f,0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.3f,-0.55f,0.0f);
    glVertex3f(1.3f,-0.55f,0.0f);
    glVertex3f(1.3f,-0.54f,0.0f);
    glVertex3f(-1.3f,-0.54f,0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.2f,-0.55f,0.0f);
    glVertex3f(1.2f,-0.55f,0.0f);
    glVertex3f(1.2f,-0.54f,0.0f);
    glVertex3f(-1.2f,-0.54f,0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.1f,-0.55f,0.0f);
    glVertex3f(1.1f,-0.55f,0.0f);
    glVertex3f(1.1f,-0.54f,0.0f);
    glVertex3f(-1.1f,-0.54f,0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f,-0.55f,0.0f);
    glVertex3f(1.0f,-0.55f,0.0f);
    glVertex3f(1.0f,-0.54f,0.0f);
    glVertex3f(-1.0f,-0.54f,0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f,-0.55f,0.0f);
    glVertex3f(1.0f,-0.55f,0.0f);
    glVertex3f(1.0f,-0.54f,0.0f);
    glVertex3f(-1.0f,-0.54f,0.0f);


    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-0.9f,-0.55f,0.0f);
    glVertex3f(0.9f,-0.55f,0.0f);
    glVertex3f(0.9f,-0.54f,0.0f);
    glVertex3f(-0.9f,-0.54f,0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.8f,-0.55f,0.0f);
    glVertex3f(0.8f,-0.55f,0.0f);
    glVertex3f(0.8f,-0.54f,0.0f);
    glVertex3f(-0.8f,-0.54f,0.0f);
//
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-0.7f,-0.55f,0.0f);
    glVertex3f(0.7f,-0.55f,0.0f);
    glVertex3f(0.7f,-0.54f,0.0f);
    glVertex3f(-0.7f,-0.54f,0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.6f,-0.55f,0.0f);
    glVertex3f(0.6f,-0.55f,0.0f);
    glVertex3f(0.6f,-0.54f,0.0f);
    glVertex3f(-0.6f,-0.54f,0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-0.5f,-0.55f,0.0f);
    glVertex3f(0.5f,-0.55f,0.0f);
    glVertex3f(0.5f,-0.54f,0.0f);
    glVertex3f(-0.5f,-0.54f,0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.4f,-0.55f,0.0f);
    glVertex3f(0.4f,-0.55f,0.0f);
    glVertex3f(0.4f,-0.54f,0.0f);
    glVertex3f(-0.4f,-0.54f,0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-0.3f,-0.55f,0.0f);
    glVertex3f(0.3f,-0.55f,0.0f);
    glVertex3f(0.3f,-0.54f,0.0f);
    glVertex3f(-0.3f,-0.54f,0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.2f,-0.55f,0.0f);
    glVertex3f(0.2f,-0.55f,0.0f);
    glVertex3f(0.2f,-0.54f,0.0f);
    glVertex3f(-0.2f,-0.54f,0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-0.1f,-0.55f,0.0f);
    glVertex3f(0.1f,-0.55f,0.0f);
    glVertex3f(0.1f,-0.54f,0.0f);
    glVertex3f(-0.1f,-0.54f,0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.0f,-0.55f,0.0f);
    glVertex3f(0.0f,-0.55f,0.0f);
    glVertex3f(0.0f,-0.54f,0.0f);
    glVertex3f(-0.0f,-0.54f,0.0f);

    glEnd();
}


void drawShip1() {
    glPushMatrix();
    glTranslatef(ship1X, ship1Y, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);//LOWER
    glVertex3f(-0.05f,-0.02f,0.0f);
    glVertex3f( 0.05f,-0.02f,0.0f);
    glVertex3f( 0.03f,-0.05f,0.0f);
    glVertex3f(-0.03f,-0.05f,0.0f);
    glEnd();

    // Upper parts
    glColor3f(0.5f,0.5f,0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-0.03f,-0.02f,0.0f);
    glVertex3f( 0.03f,-0.02f,0.0f);
    glVertex3f( 0.02f, 0.00f,0.0f);
    glVertex3f(-0.02f, 0.00f,0.0f);
    glEnd();

    glPopMatrix();
}


void drawShip2() {
    glPushMatrix();
    glTranslatef(ship2X, ship2Y + 0.05f, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex3f(-0.05f,-0.02f,0.0f);
    glVertex3f( 0.05f,-0.02f,0.0f);
    glVertex3f( 0.03f,-0.05f,0.0f);
    glVertex3f(-0.03f,-0.05f,0.0f);
    glEnd();

    glColor3f(0.1f,0.5f,0.3f);
    glBegin(GL_QUADS);
    glVertex3f(-0.025f,-0.02f,0.0f);
    glVertex3f( 0.025f,-0.02f,0.0f);
    glVertex3f( 0.015f, 0.00f,0.0f);
    glVertex3f(-0.015f, 0.00f,0.0f);
    glEnd();

    glPopMatrix();
}


//variables for fruits
float fruit1X = -0.3f, fruit1Y = 0.25f, fruit1SpeedY = 0.001f;
float fruit2X = -0.25f, fruit2Y = 0.25f, fruit2SpeedY = 0.00075f;
float fruit3X = -0.35f, fruit3Y = 0.25f, fruit3SpeedY = 0.00125f;
float fruit4X = -0.28f, fruit4Y = 0.25f, fruit4SpeedY = 0.0009f;
float fruit5X = -0.32f, fruit5Y = 0.25f, fruit5SpeedY = 0.0011f;


void drawTree() {
    glPushMatrix();
    glTranslatef(0.2f,-0.07f, 0.0f);
    glScalef(0.6f,0.6f, 1.0f);


    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, -0.1f);
        glVertex2f(-0.25f, -0.1f);
        glVertex2f(-0.25f, 0.2f);
        glVertex2f(-0.35f, 0.2f);
    glEnd();


    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.34f, -0.1f); glVertex2f(-0.34f, 0.2f);
        glVertex2f(-0.30f, -0.1f); glVertex2f(-0.30f, 0.2f);
        glVertex2f(-0.26f, -0.1f); glVertex2f(-0.26f, 0.2f);
    glEnd();


    glColor3f(0.6f, 0.4f, 0.2f);
    // Left branch
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.35f, 0.12f);
        glVertex2f(-0.45f, 0.17f);
        glVertex2f(-0.40f, 0.07f);
    glEnd();
    // Right branch
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.25f, 0.15f);
        glVertex2f(-0.15f, 0.20f);
        glVertex2f(-0.20f, 0.10f);
    glEnd();


    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircleA(-0.3f, 0.25f, 0.1f);   // Main canopy
    drawCircleA(-0.38f, 0.20f, 0.07f); // Left outer
    drawCircleA(-0.22f, 0.20f, 0.07f); // Right outer

    glColor3f(0.2f, 0.8f, 0.2f);
    drawCircleA(-0.3f, 0.30f, 0.06f);  // Top inner
    drawCircleA(-0.35f, 0.25f, 0.05f);  // Left inner
    drawCircleA(-0.25f, 0.25f, 0.05f);  // Right inner
glPopMatrix();

}


void drawSingleFruit(float fx, float fy) {
    glPushMatrix();
    glTranslatef(0.2f,-0.07f, 0.0f);
     glScalef(0.6f,0.6f, 1.0f);

    glColor3f(0.3f, 0.3f, 0.3f);  // Gray shadow
    drawEllipseA(fx + 0.005f, fy - 0.015f, 0.018f, 0.008f);  // Elliptical shadow


    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(fx, fy + 0.015f);
        glVertex2f(fx + 0.005f, fy + 0.025f);
    glEnd();

    glColor3f(0.9f, 0.2f, 0.2f);  // Brighter red
    drawCircleA(fx, fy, 0.015f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircleA(fx - 0.005f, fy + 0.005f, 0.003f);
    glPopMatrix();
}


void drawFruits() {
    // Draw each fruit
    drawSingleFruit(fruit1X, fruit1Y);
    drawSingleFruit(fruit2X, fruit2Y);
    drawSingleFruit(fruit3X, fruit3Y);
    drawSingleFruit(fruit4X, fruit4Y);
    drawSingleFruit(fruit5X, fruit5Y);
}

// Update fruits
void updateFruits() {
    static int restFrames[5] = {0, 0, 0, 0, 0};
    const float groundY = -0.12f + 0.015f;
    const int restTime = 2500;

    // Update Fruit 1
    if (fruit1Y > groundY) {
        fruit1Y -= fruit1SpeedY;  // Falling
        restFrames[0] = 0;
    } else {
        restFrames[0]++;
        if (restFrames[0] >= restTime) {
            fruit1Y = 0.25f;
            fruit1SpeedY = 0.001f;
            restFrames[0] = 0;
        }
    }

    // Update Fruit 2
    if (fruit2Y > groundY) {
        fruit2Y -= fruit2SpeedY;
        restFrames[1] = 0;
    } else {
        restFrames[1]++;
        if (restFrames[1] >= restTime) {
            fruit2Y = 0.25f;
            fruit2SpeedY = 0.00075f;
            restFrames[1] = 0;
        }
    }

    // Update Fruit 3
    if (fruit3Y > groundY) {
        fruit3Y -= fruit3SpeedY;
        restFrames[2] = 0;
    } else {
        restFrames[2]++;
        if (restFrames[2] >= restTime) {
            fruit3Y = 0.25f;
            fruit3SpeedY = 0.00125f;
            restFrames[2] = 0;
        }
    }

    // Update Fruit 4
    if (fruit4Y > groundY) {
        fruit4Y -= fruit4SpeedY;
        restFrames[3] = 0;
    } else {
        restFrames[3]++;
        if (restFrames[3] >= restTime) {
            fruit4Y = 0.25f;
            fruit4SpeedY = 0.0009f;
            restFrames[3] = 0;
        }
    }

    // Update Fruit 5
    if (fruit5Y > groundY) {
        fruit5Y -= fruit5SpeedY;
        restFrames[4] = 0;
    } else {
        restFrames[4]++;
        if (restFrames[4] >= restTime) {
            fruit5Y = 0.25f;
            fruit5SpeedY = 0.0011f;
            restFrames[4] = 0;
        }
    }
}


void drawTreeA() {
    glPushMatrix();
    glTranslatef(1.0f,-0.35f, 0.0f);
    glScalef(0.6f,0.6f, 1.0f);


    glColor3f(0.5f, 0.3f, 0.1f);  // Darker brown
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, -0.1f);
        glVertex2f(-0.25f, -0.1f);
        glVertex2f(-0.25f, 0.2f);
        glVertex2f(-0.35f, 0.2f);
    glEnd();


    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.34f, -0.1f); glVertex2f(-0.34f, 0.2f);
        glVertex2f(-0.30f, -0.1f); glVertex2f(-0.30f, 0.2f);
        glVertex2f(-0.26f, -0.1f); glVertex2f(-0.26f, 0.2f);
    glEnd();


    glColor3f(0.6f, 0.4f, 0.2f);  // Lighter brown for branches
    // Left branch
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.35f, 0.12f);  // Slightly lowered
        glVertex2f(-0.45f, 0.17f);
        glVertex2f(-0.40f, 0.07f);
    glEnd();
    // Right branch
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.25f, 0.15f);  // Slightly lowered
        glVertex2f(-0.15f, 0.20f);
        glVertex2f(-0.20f, 0.10f);
    glEnd();


    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircleA(-0.3f, 0.25f, 0.1f);   // Main canopy
    drawCircleA(-0.38f, 0.20f, 0.07f); // Left outer
    drawCircleA(-0.22f, 0.20f, 0.07f); // Right outer

    glColor3f(0.2f, 0.8f, 0.2f);
    drawCircleA(-0.3f, 0.30f, 0.06f);  // Top inner
    drawCircleA(-0.35f, 0.25f, 0.05f);  // Left inner
    drawCircleA(-0.25f, 0.25f, 0.05f);  // Right inner
glPopMatrix();

}


void drawSingleFruitA(float fxi, float fyi) {
    glPushMatrix();
    glTranslatef(1.0f,0.5f, 0.0f);
     glScalef(0.6f,0.6f, 1.0f);

    glColor3f(0.3f, 0.3f, 0.3f);  // Gray shadow
    drawEllipseA(fxi + 0.005f, fyi - 0.015f, 0.018f, 0.008f);

    // Stem (thin green line)
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(fxi, fyi + 0.015f);
        glVertex2f(fxi + 0.005f, fyi + 0.025f);
    glEnd();
    glColor3f(0.9f, 0.2f, 0.2f);  // Brighter red
    drawCircleA(fxi, fyi, 0.015f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircleA(fxi - 0.005f, fyi + 0.005f, 0.003f);
    glPopMatrix();
}


void drawFruitsA() {
    // Draw each fruit
    drawSingleFruit(fruit1X, fruit1Y);
    drawSingleFruit(fruit2X, fruit2Y);
    drawSingleFruit(fruit3X, fruit3Y);
    drawSingleFruit(fruit4X, fruit4Y);
    drawSingleFruit(fruit5X, fruit5Y);
}


void updateFruitsA() {
    static int restFrames[5] = {0, 0, 0, 0, 0};
    const float groundY = -0.12f + 0.015f;
    const int restTime = 2500;

    // Update Fruit 1
    if (fruit1Y > groundY) {
        fruit1Y -= fruit1SpeedY;  // Falling
        restFrames[0] = 0;
    } else {
        restFrames[0]++;
        if (restFrames[0] >= restTime) {
            fruit1Y = 0.25f;  // Reset to tree
            fruit1SpeedY = 0.001f;  // Downward speed
            restFrames[0] = 0;
        }
    }

    // Update Fruit 2
    if (fruit2Y > groundY) {
        fruit2Y -= fruit2SpeedY;
        restFrames[1] = 0;
    } else {
        restFrames[1]++;
        if (restFrames[1] >= restTime) {
            fruit2Y = 0.25f;
            fruit2SpeedY = 0.00075f;
            restFrames[1] = 0;
        }
    }

    // Update Fruit 3
    if (fruit3Y > groundY) {
        fruit3Y -= fruit3SpeedY;
        restFrames[2] = 0;
    } else {
        restFrames[2]++;
        if (restFrames[2] >= restTime) {
            fruit3Y = 0.25f;
            fruit3SpeedY = 0.00125f;
            restFrames[2] = 0;
        }
    }

    // Update Fruit 4
    if (fruit4Y > groundY) {
        fruit4Y -= fruit4SpeedY;
        restFrames[3] = 0;
    } else {
        restFrames[3]++;
        if (restFrames[3] >= restTime) {
            fruit4Y = 0.25f;
            fruit4SpeedY = 0.0009f;
            restFrames[3] = 0;
        }
    }

    // Update Fruit 5
    if (fruit5Y > groundY) {
        fruit5Y -= fruit5SpeedY;
        restFrames[4] = 0;
    } else {
        restFrames[4]++;
        if (restFrames[4] >= restTime) {
            fruit5Y = 0.25f;
            fruit5SpeedY = 0.0011f;
            restFrames[4] = 0;
        }
    }
}


void drawTreeB() {
    glPushMatrix();
    glTranslatef(1.0f,-0.02f, 0.0f);
    glScalef(0.4f,0.4f, 1.0f);


    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, -0.1f);
        glVertex2f(-0.25f, -0.1f);
        glVertex2f(-0.25f, 0.2f);
        glVertex2f(-0.35f, 0.2f);
    glEnd();


    glColor3f(0.4f, 0.2f, 0.0f);  // Darker lines
    glBegin(GL_LINES);
        glVertex2f(-0.34f, -0.1f); glVertex2f(-0.34f, 0.2f);
        glVertex2f(-0.30f, -0.1f); glVertex2f(-0.30f, 0.2f);
        glVertex2f(-0.26f, -0.1f); glVertex2f(-0.26f, 0.2f);
    glEnd();

    // Branches
    glColor3f(0.6f, 0.4f, 0.2f);
    // Left branch
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.35f, 0.12f);
        glVertex2f(-0.45f, 0.17f);
        glVertex2f(-0.40f, 0.07f);
    glEnd();
    // Right branch
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.25f, 0.15f);
        glVertex2f(-0.15f, 0.20f);
        glVertex2f(-0.20f, 0.10f);
    glEnd();



    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircleA(-0.3f, 0.25f, 0.1f);
    drawCircleA(-0.38f, 0.20f, 0.07f);
    drawCircleA(-0.22f, 0.20f, 0.07f);
    // Inner layer-green
    glColor3f(0.2f, 0.8f, 0.2f);
    drawCircleA(-0.3f, 0.30f, 0.06f);
    drawCircleA(-0.35f, 0.25f, 0.05f);
    drawCircleA(-0.25f, 0.25f, 0.05f);
glPopMatrix();

}


void drawSingleFruitB(float fxj, float fyj) {
    glPushMatrix();
   glTranslatef(6.0f,0.2f, 0.0f);
    glScalef(0.4f,0.4f, 1.0f);

    glColor3f(0.3f, 0.3f, 0.3f);
    drawEllipseA(fxj + 0.005f, fyj - 0.015f, 0.018f, 0.008f);


    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(fxj, fyj + 0.015f);
        glVertex2f(fxj + 0.005f, fyj + 0.025f);
    glEnd();


    glColor3f(0.9f, 0.2f, 0.2f);  // Brighter red
    drawCircleA(fxj, fyj, 0.015f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircleA(fxj - 0.005f, fyj + 0.005f, 0.003f);
    glPopMatrix();
}


void drawFruitsB() {
    // Draw each fruit
    drawSingleFruit(fruit1X, fruit1Y);
    drawSingleFruit(fruit2X, fruit2Y);
    drawSingleFruit(fruit3X, fruit3Y);
    drawSingleFruit(fruit4X, fruit4Y);
    drawSingleFruit(fruit5X, fruit5Y);
}


void updateFruitsB() {
    static int restFrames[5] = {0, 0, 0, 0, 0};
    const float groundY = -0.12f + 0.015f;
    const int restTime = 2500;

    // Update Fruit 1
    if (fruit1Y > groundY) {
        fruit1Y -= fruit1SpeedY;  // Falling
        restFrames[0] = 0;
    } else {
        restFrames[0]++;
        if (restFrames[0] >= restTime) {
            fruit1Y = 0.25f;
            fruit1SpeedY = 0.001f;
            restFrames[0] = 0;
        }
    }

    // Update Fruit 2
    if (fruit2Y > groundY) {
        fruit2Y -= fruit2SpeedY;
        restFrames[1] = 0;
    } else {
        restFrames[1]++;
        if (restFrames[1] >= restTime) {
            fruit2Y = 0.25f;
            fruit2SpeedY = 0.00075f;
            restFrames[1] = 0;
        }
    }

    // Update Fruit 3
    if (fruit3Y > groundY) {
        fruit3Y -= fruit3SpeedY;
        restFrames[2] = 0;
    } else {
        restFrames[2]++;
        if (restFrames[2] >= restTime) {
            fruit3Y = 0.25f;
            fruit3SpeedY = 0.00125f;
            restFrames[2] = 0;
        }
    }

    // Update Fruit 4
    if (fruit4Y > groundY) {
        fruit4Y -= fruit4SpeedY;
        restFrames[3] = 0;
    } else {
        restFrames[3]++;
        if (restFrames[3] >= restTime) {
            fruit4Y = 0.25f;
            fruit4SpeedY = 0.0009f;
            restFrames[3] = 0;
        }
    }

    // Update Fruit 5
    if (fruit5Y > groundY) {
        fruit5Y -= fruit5SpeedY;
        restFrames[4] = 0;
    } else {
        restFrames[4]++;
        if (restFrames[4] >= restTime) {
            fruit5Y = 0.25f;
            fruit5SpeedY = 0.0011f;
            restFrames[4] = 0;
        }
    }
}



void drawTreeC() {
    glPushMatrix();
    glTranslatef(1.90f,0.1f, 0.0f);
    glScalef(0.5f,0.5f, 1.0f);


    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, -0.1f);
        glVertex2f(-0.25f, -0.1f);
        glVertex2f(-0.25f, 0.2f);
        glVertex2f(-0.35f, 0.2f);
    glEnd();

    // Bark texture
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.34f, -0.1f);
	glVertex2f(-0.34f, 0.2f);
        glVertex2f(-0.30f, -0.1f);
	glVertex2f(-0.30f, 0.2f);
        glVertex2f(-0.26f, -0.1f);
	glVertex2f(-0.26f, 0.2f);
    glEnd();

    // Branches (adjusted down for shorter trunk)
    glColor3f(0.6f, 0.4f, 0.2f);
    // Left branch
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.35f, 0.12f);
        glVertex2f(-0.45f, 0.17f);
        glVertex2f(-0.40f, 0.07f);
    glEnd();
    // Right branch
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.25f, 0.15f);
        glVertex2f(-0.15f, 0.20f);
        glVertex2f(-0.20f, 0.10f);
    glEnd();

    // Outer layer-green
    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircleA(-0.3f, 0.25f, 0.1f);
    drawCircleA(-0.38f, 0.20f, 0.07f);
    drawCircleA(-0.22f, 0.20f, 0.07f);
    // Inner layer-green
    glColor3f(0.2f, 0.8f, 0.2f);
    drawCircleA(-0.3f, 0.30f, 0.06f);
    drawCircleA(-0.35f, 0.25f, 0.05f);
    drawCircleA(-0.25f, 0.25f, 0.05f);
glPopMatrix();

}


void drawSingleFruitC(float fxk, float fyk) {
    glPushMatrix();
    glTranslatef(1.90f,0.1f, 0.0f);
    glScalef(0.5f,0.5f, 1.0f);
    // Shadow
    glColor3f(0.3f, 0.3f, 0.3f);
    drawEllipseA(fxk + 0.005f, fyk - 0.015f, 0.018f, 0.008f);

    // Stem
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(fxk, fyk + 0.015f);
        glVertex2f(fxk + 0.005f, fyk + 0.025f);
    glEnd();

    // Fruit body
    glColor3f(0.9f, 0.2f, 0.2f);
    drawCircleA(fxk, fyk, 0.015f);
    // Highlight
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircleA(fxk - 0.005f, fyk + 0.005f, 0.003f);
    glPopMatrix();
}


void drawFruitsC() {
    // Draw each fruit
    drawSingleFruit(fruit1X, fruit1Y);
    drawSingleFruit(fruit2X, fruit2Y);
    drawSingleFruit(fruit3X, fruit3Y);
    drawSingleFruit(fruit4X, fruit4Y);
    drawSingleFruit(fruit5X, fruit5Y);
}

// Update fruits
void updateFruitsC() {
    static int restFrames[5] = {0, 0, 0, 0, 0};
    const float groundY = -0.12f + 0.015f;
    const int restTime = 2500;

    // Update Fruit 1
    if (fruit1Y > groundY) {
        fruit1Y -= fruit1SpeedY;  // Falling
        restFrames[0] = 0;
    } else {
        restFrames[0]++;
        if (restFrames[0] >= restTime) {
            fruit1Y = 0.25f;  // Reset to tree
            fruit1SpeedY = 0.001f;  // Downward speed
            restFrames[0] = 0;
        }
    }

    // Update Fruit 2
    if (fruit2Y > groundY) {
        fruit2Y -= fruit2SpeedY;
        restFrames[1] = 0;
    } else {
        restFrames[1]++;
        if (restFrames[1] >= restTime) {
            fruit2Y = 0.25f;
            fruit2SpeedY = 0.00075f;
            restFrames[1] = 0;
        }
    }

    // Update Fruit 3
    if (fruit3Y > groundY) {
        fruit3Y -= fruit3SpeedY;
        restFrames[2] = 0;
    } else {
        restFrames[2]++;
        if (restFrames[2] >= restTime) {
            fruit3Y = 0.25f;
            fruit3SpeedY = 0.00125f;
            restFrames[2] = 0;
        }
    }

    // Update Fruit 4
    if (fruit4Y > groundY) {
        fruit4Y -= fruit4SpeedY;
        restFrames[3] = 0;
    } else {
        restFrames[3]++;
        if (restFrames[3] >= restTime) {
            fruit4Y = 0.25f;
            fruit4SpeedY = 0.0009f;
            restFrames[3] = 0;
        }
    }

    // Update Fruit 5
    if (fruit5Y > groundY) {
        fruit5Y -= fruit5SpeedY;
        restFrames[4] = 0;
    } else {
        restFrames[4]++;
        if (restFrames[4] >= restTime) {
            fruit5Y = 0.25f;
            fruit5SpeedY = 0.0011f;
            restFrames[4] = 0;
        }
    }
}


void drawTreeD() {
    glPushMatrix();
    glTranslatef(0.4f,-0.37f, 0.0f);
    glScalef(0.6f,0.6f, 1.0f);


    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, -0.1f);
        glVertex2f(-0.25f, -0.1f);
        glVertex2f(-0.25f, 0.2f);
        glVertex2f(-0.35f, 0.2f);
    glEnd();

    // Bark texture
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.34f, -0.1f);
	glVertex2f(-0.34f, 0.2f);
        glVertex2f(-0.30f, -0.1f);
	glVertex2f(-0.30f, 0.2f);
        glVertex2f(-0.26f, -0.1f);
	glVertex2f(-0.26f, 0.2f);
    glEnd();

    // Branches
    glColor3f(0.6f, 0.4f, 0.2f);
    // Left branch
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.35f, 0.12f);
        glVertex2f(-0.45f, 0.17f);
        glVertex2f(-0.40f, 0.07f);
    glEnd();
    // Right branch
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.25f, 0.15f);
        glVertex2f(-0.15f, 0.20f);
        glVertex2f(-0.20f, 0.10f);
    glEnd();

    // Foliage (unchanged, already close)
    // Outer layer-green
    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircleA(-0.3f, 0.25f, 0.1f);
    drawCircleA(-0.38f, 0.20f, 0.07f);
    drawCircleA(-0.22f, 0.20f, 0.07f);
    // Inner layer-green
    glColor3f(0.2f, 0.8f, 0.2f);
    drawCircleA(-0.3f, 0.30f, 0.06f);
    drawCircleA(-0.35f, 0.25f, 0.05f);
    drawCircleA(-0.25f, 0.25f, 0.05f);
glPopMatrix();

}


void drawSingleFruitD(float fxl, float fyl) {
    glPushMatrix();
    glTranslatef(0.4f,-0.03f, 0.0f);
     glScalef(0.6f,0.6f, 1.0f);
    // faint gray ellipse below
    glColor3f(0.3f, 0.3f, 0.3f);
    drawEllipseA(fxl + 0.005f, fyl - 0.015f, 0.018f, 0.008f);

    // thin green line
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(fxl, fyl + 0.015f);
        glVertex2f(fxl + 0.005f, fyl + 0.025f);
    glEnd();


    glColor3f(0.9f, 0.2f, 0.2f);
    drawCircleA(fxl, fyl, 0.015f);
    // small white circle on top
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircleA(fxl - 0.005f, fyl + 0.005f, 0.003f);
    glPopMatrix();
}


void drawFruitsD() {
    // Draw each fruit
    drawSingleFruit(fruit1X, fruit1Y);
    drawSingleFruit(fruit2X, fruit2Y);
    drawSingleFruit(fruit3X, fruit3Y);
    drawSingleFruit(fruit4X, fruit4Y);
    drawSingleFruit(fruit5X, fruit5Y);
}

// Update fruits
void updateFruitsD() {
    static int restFrames[5] = {0, 0, 0, 0, 0};
    const float groundY = -0.12f + 0.015f;
    const int restTime = 2500;
    // Update Fruit 1
    if (fruit1Y > groundY) {
        fruit1Y -= fruit1SpeedY;  // Falling
        restFrames[0] = 0;
    } else {
        restFrames[0]++;
        if (restFrames[0] >= restTime) {
            fruit1Y = 0.25f;  // Reset to tree
            fruit1SpeedY = 0.001f;  // Downward speed
            restFrames[0] = 0;
        }
    }

    // Update Fruit 2
    if (fruit2Y > groundY) {
        fruit2Y -= fruit2SpeedY;
        restFrames[1] = 0;
    } else {
        restFrames[1]++;
        if (restFrames[1] >= restTime) {
            fruit2Y = 0.25f;
            fruit2SpeedY = 0.00075f;
            restFrames[1] = 0;
        }
    }

    // Update Fruit 3
    if (fruit3Y > groundY) {
        fruit3Y -= fruit3SpeedY;
        restFrames[2] = 0;
    } else {
        restFrames[2]++;
        if (restFrames[2] >= restTime) {
            fruit3Y = 0.25f;
            fruit3SpeedY = 0.00125f;
            restFrames[2] = 0;
        }
    }

    // Update Fruit 4
    if (fruit4Y > groundY) {
        fruit4Y -= fruit4SpeedY;
        restFrames[3] = 0;
    } else {
        restFrames[3]++;
        if (restFrames[3] >= restTime) {
            fruit4Y = 0.25f;
            fruit4SpeedY = 0.0009f;
            restFrames[3] = 0;
        }
    }

    // Update Fruit 5
    if (fruit5Y > groundY) {
        fruit5Y -= fruit5SpeedY;
        restFrames[4] = 0;
    } else {
        restFrames[4]++;
        if (restFrames[4] >= restTime) {
            fruit5Y = 0.25f;
            fruit5SpeedY = 0.0011f;
            restFrames[4] = 0;
        }
    }
}


void initGL() {
// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}


void RiverView(){
    glColor3f(0.224f, 0.6f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-2.0f,-1.0f,0.0f);
    glVertex3f(2.0f,-1.0f,0.0f);
    glVertex3f(2.0f,-0.62f,0.0f);
    glVertex3f(-2.0f,-0.62f,0.0f);
    glEnd();

    // Flowing sine ripples
    glColor3f(0.9f, 0.95f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for(float x = -2.0f; x <= 2.0f; x += 0.05f){
        float y = -0.8f + 0.02f * sinf(10 * x + riverOffset * 10);
        glVertex2f(x, y);
    }
    glEnd();
}


void drawLaunchPad() {
    glPushMatrix();
    glTranslatef(-0.9f,0.12f, 0.0f);
    glScalef(0.7f,0.7f, 1.0f);
    // Solid Concrete Base
    glColor3f(0.32f, 0.32f, 0.32f);
    glBegin(GL_QUADS);
        glVertex2f(-0.85f, -0.55f);
        glVertex2f(-0.35f, -0.55f);
        glVertex2f(-0.35f, -0.45f);
        glVertex2f(-0.85f, -0.45f);
    glEnd();

    // Top metal plate (where rocket stands)
    glColor3f(0.55f, 0.55f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.80f, -0.45f);
        glVertex2f(-0.40f, -0.45f);
        glVertex2f(-0.40f, -0.42f);
        glVertex2f(-0.80f, -0.42f);
    glEnd();

    // LEFT side
    glColor3f(0.50f, 0.50f, 0.50f);
    glBegin(GL_QUADS);
        glVertex2f(-0.80f, -0.45f);
        glVertex2f(-0.85f, -0.45f);
        glVertex2f(-0.85f, 0.35f);
        glVertex2f(-0.80f, 0.35f);
    glEnd();

    // depth
    glColor3f(0.30f, 0.30f, 0.30f);
    glBegin(GL_QUADS);
        glVertex2f(-0.80f, -0.45f);
        glVertex2f(-0.78f, -0.45f);
        glVertex2f(-0.78f, 0.35f);
        glVertex2f(-0.80f, 0.35f);
    glEnd();

    //Side arms
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(-0.80f, -0.20f);
        glVertex2f(-0.60f, -0.20f);
        glVertex2f(-0.60f, -0.17f);
        glVertex2f(-0.80f, -0.17f);

        glVertex2f(-0.80f, -0.05f);
        glVertex2f(-0.65f, -0.05f);
        glVertex2f(-0.65f, -0.02f);
        glVertex2f(-0.80f, -0.02f);
    glEnd();

    //Reinforcement cross-beams
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINES);
        glVertex2f(-0.85f, -0.40f);
        glVertex2f(-0.80f, -0.35f);
        glVertex2f(-0.85f, -0.35f);
        glVertex2f(-0.80f, -0.30f);
        glVertex2f(-0.85f, -0.30f);
        glVertex2f(-0.80f, -0.25f);
        glVertex2f(-0.85f, -0.25f);
        glVertex2f(-0.80f, -0.20f);
        glVertex2f(-0.85f, -0.20f);
        glVertex2f(-0.80f, -0.15f);
        glVertex2f(-0.85f, -0.15f);
        glVertex2f(-0.80f, -0.10f);
        glVertex2f(-0.85f, -0.10f);
        glVertex2f(-0.80f, -0.05f);
        glVertex2f(-0.85f, -0.05f);
        glVertex2f(-0.80f,  0.00f);
        glVertex2f(-0.85f,  0.00f);
        glVertex2f(-0.80f,  0.05f);
        glVertex2f(-0.85f,  0.05f);
        glVertex2f(-0.80f,  0.10f);
        glVertex2f(-0.85f,  0.10f);
        glVertex2f(-0.80f,  0.15f);
        glVertex2f(-0.85f,  0.15f);
        glVertex2f(-0.80f,  0.20f);
        glVertex2f(-0.85f,  0.20f);
        glVertex2f(-0.80f,  0.25f);
        glVertex2f(-0.85f,  0.25f);
        glVertex2f(-0.80f,  0.30f);
    glEnd();

    //Ladder
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
        glVertex2f(-0.845f, -0.38f);
        glVertex2f(-0.825f, -0.38f);
        glVertex2f(-0.845f, -0.34f);
        glVertex2f(-0.825f, -0.34f);
        glVertex2f(-0.845f, -0.30f);
        glVertex2f(-0.825f, -0.30f);
        glVertex2f(-0.845f, -0.26f);
        glVertex2f(-0.825f, -0.26f);
        glVertex2f(-0.845f, -0.22f);
        glVertex2f(-0.825f, -0.22f);
        glVertex2f(-0.845f, -0.18f);
        glVertex2f(-0.825f, -0.18f);
        glVertex2f(-0.845f, -0.14f);
        glVertex2f(-0.825f, -0.14f);
        glVertex2f(-0.845f, -0.10f);
        glVertex2f(-0.825f, -0.10f);
        glVertex2f(-0.845f, -0.06f);
        glVertex2f(-0.825f, -0.06f);
        glVertex2f(-0.845f, -0.02f);
        glVertex2f(-0.825f, -0.02f);
        glVertex2f(-0.845f,  0.02f);
        glVertex2f(-0.825f,  0.02f);
        glVertex2f(-0.845f,  0.06f);
        glVertex2f(-0.825f,  0.06f);
        glVertex2f(-0.845f,  0.10f);
        glVertex2f(-0.825f,  0.10f);
        glVertex2f(-0.845f,  0.14f);
        glVertex2f(-0.825f,  0.14f);
        glVertex2f(-0.845f,  0.18f);
        glVertex2f(-0.825f,  0.18f);
        glVertex2f(-0.845f,  0.22f);
        glVertex2f(-0.825f,  0.22f);
    glEnd();
    glPopMatrix();
}



void drawMountains() {
    // BACK RANGE
    glColor3f(0.10f, 0.12f, 0.16f);
    glBegin(GL_POLYGON);
        glVertex2f(-2.2f,  0.15f);
        glVertex2f(-1.8f,  0.55f);
        glVertex2f(-1.5f,  0.35f);
        glVertex2f(-1.2f,  0.60f);
        glVertex2f(-0.9f,  0.40f);
        glVertex2f(-0.6f,  0.70f);
        glVertex2f(-0.2f,  0.50f);
        glVertex2f(0.2f,   0.75f);
        glVertex2f(0.6f,   0.55f);
        glVertex2f(0.9f,   0.80f);
        glVertex2f(1.3f,   0.60f);
        glVertex2f(1.6f,   0.85f);
        glVertex2f(1.9f,   0.65f);
        glVertex2f(2.2f,   0.15f);
    glEnd();

    //FRONT RANGE
    glColor3f(0.20f, 0.22f, 0.26f);
    glBegin(GL_POLYGON);
        glVertex2f(-2.2f,  0.10f);
        glVertex2f(-1.9f,  0.50f);
        glVertex2f(-1.5f,  0.35f);
        glVertex2f(-1.1f,  0.55f);
        glVertex2f(-0.8f,  0.38f);
        glVertex2f(-0.5f,  0.62f);
        glVertex2f(-0.2f,  0.45f);
        glVertex2f(0.1f,   0.70f);
        glVertex2f(0.4f,   0.48f);
        glVertex2f(0.8f,   0.68f);
        glVertex2f(1.1f,   0.42f);
        glVertex2f(1.5f,   0.65f);
        glVertex2f(1.9f,   0.40f);
        glVertex2f(2.2f,   0.10f);
    glEnd();

    //MID RIDGE
    glColor3f(0.26f, 0.28f, 0.32f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.6f,  0.35f);
        glVertex2f(-1.3f,  0.48f);
        glVertex2f(-1.0f,  0.36f);
        glVertex2f(-0.7f,  0.52f);
        glVertex2f(-0.4f,  0.38f);
        glVertex2f(-0.1f,  0.55f);
        glVertex2f(0.2f,   0.40f);
        glVertex2f(0.5f,   0.60f);
        glVertex2f(0.8f,   0.45f);
        glVertex2f(1.1f,   0.58f);
        glVertex2f(1.4f,   0.42f);
    glEnd();
}




void drawEnhancedAntenna(float x, float y) {
    // Base mount
    glColor3f(0.2f, 0.2f, 0.2f);
    drawEllipseA(x, y - 0.01f, 0.04f, 0.015f);

    // Vertical pole
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.005f, y);
        glVertex2f(x + 0.005f, y);
        glVertex2f(x + 0.005f, y + 0.25f);
        glVertex2f(x - 0.005f, y + 0.25f);
    glEnd();

    // Horizontal signal bars
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
        glVertex2f(x - 0.04f, y + 0.08f);
        glVertex2f(x + 0.04f, y + 0.08f);
        glVertex2f(x - 0.035f, y + 0.12f);
        glVertex2f(x + 0.035f, y + 0.12f);
        glVertex2f(x - 0.03f, y + 0.16f);
        glVertex2f(x + 0.03f, y + 0.16f);
    glEnd();

    // Side dish
    glColor3f(0.6f, 0.6f, 0.6f);
    drawEllipseA(x + 0.035f, y + 0.18f, 0.045f, 0.025f);

    // Dish arm
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.002f, y + 0.18f);
        glVertex2f(x + 0.004f, y + 0.18f);
        glVertex2f(x + 0.036f, y + 0.19f);
        glVertex2f(x + 0.034f, y + 0.19f);
    glEnd();

    // Top receiver bulb (blinking, larger)
    if ((glutGet(GLUT_ELAPSED_TIME) / 500) % 2 == 0)
        glColor3f(1.0f, 0.0f, 0.0f); // Bright red
    else
        glColor3f(0.3f, 0.0f, 0.0f); // Dim red
    drawCircleA(x, y + 0.26f, 0.012f); // Increased radius

    // Glow ring
    glColor3f(1.0f, 1.0f, 0.0f);
    drawEllipseA(x, y + 0.255f, 0.012f, 0.004f);

    // Small antenna fork
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
        glVertex2f(x, y + 0.25f); glVertex2f(x - 0.02f, y + 0.28f);
        glVertex2f(x, y + 0.25f); glVertex2f(x + 0.02f, y + 0.28f);
    glEnd();
}

void drawEnhancedAntenna1(float x, float y) {
    // Base mount
    glColor3f(0.2f, 0.2f, 0.2f);
    drawEllipseA(x, y - 0.01f, 0.04f, 0.015f);

    // Vertical pole
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.005f, y);
        glVertex2f(x + 0.005f, y);
        glVertex2f(x + 0.005f, y + 0.25f);
        glVertex2f(x - 0.005f, y + 0.25f);
    glEnd();

    // Horizontal signal
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
        glVertex2f(x - 0.04f, y + 0.08f);
        glVertex2f(x + 0.04f, y + 0.08f);
        glVertex2f(x - 0.035f, y + 0.12f);
        glVertex2f(x + 0.035f, y + 0.12f);
        glVertex2f(x - 0.03f, y + 0.16f);
        glVertex2f(x + 0.03f, y + 0.16f);
    glEnd();

    // Side dish
    glColor3f(0.6f, 0.6f, 0.6f);
    drawEllipseA(x + 0.035f, y + 0.18f, 0.045f, 0.025f);

    // Dish arm
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.002f, y + 0.18f);
        glVertex2f(x + 0.004f, y + 0.18f);
        glVertex2f(x + 0.036f, y + 0.19f);
        glVertex2f(x + 0.034f, y + 0.19f);
    glEnd();

    // Top receiver bulb (blinking green, larger)
    if ((glutGet(GLUT_ELAPSED_TIME) / 500) % 2 == 0)
        glColor3f(0.0f, 1.0f, 0.0f); // Bright green
    else
        glColor3f(0.0f, 0.3f, 0.0f); // Dim green
    drawCircleA(x, y + 0.26f, 0.012f); // Increased radius

    // Glow ring
    glColor3f(1.0f, 1.0f, 0.0f);
    drawEllipseA(x, y + 0.255f, 0.012f, 0.004f);

    // Small antenna fork
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
        glVertex2f(x, y + 0.25f); glVertex2f(x - 0.02f, y + 0.28f);
        glVertex2f(x, y + 0.25f); glVertex2f(x + 0.02f, y + 0.28f);
    glEnd();
}



void drawAntenna(float x, float y) {
    float pivot_y = y;
    float base_y = y - 0.15f;

    // 1. Base (Dark Gray)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.08f, base_y - 0.03f);
        glVertex2f(x + 0.08f, base_y - 0.03f);
        glVertex2f(x + 0.08f, base_y);
        glVertex2f(x - 0.08f, base_y);
    glEnd();

    // 2. Support Arm (Thickened)
    glBegin(GL_QUADS);
        glVertex2f(x - 0.04f, base_y);
        glVertex2f(x + 0.04f, base_y);
        glVertex2f(x + 0.02f, pivot_y);
        glVertex2f(x - 0.02f, pivot_y);
    glEnd();

    // 3. Rotating Dish Assembly
    glPushMatrix();
    glTranslatef(x, pivot_y, 0.0f);
    glRotatef(antennaRotation, 0.0f, 0.0f, 1.0f);  // 🔄 Animated rotation
    glTranslatef(-0.015f, 0.0f, 0.0f);             // Slight offset

    // Dish (Orange-Red)
    glColor3f(0.8f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 25; i <= 75; i++) {
        float angle = 2.0f * 3.1415926f * i / 100.0f;
        float radius = 0.12f;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(dx + 0.03f, dy);
    }
    glEnd();

    // Feedhorn Arm (Black line)
    float feedhorn_x = 0.12f;
    float feedhorn_y = 0.05f;
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(feedhorn_x, feedhorn_y);
    glEnd();

    // Feedhorn (White circle)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircleA(feedhorn_x, feedhorn_y, 0.01f);

    // Signal Waves (3 arcs)
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int j = 0; j < 3; j++) {
        glBegin(GL_LINE_STRIP);
        float radius = 0.03f + j * 0.02f;
        for (int i = 0; i <= 30; i++) {
            float angle = 2.0f * 3.1415926f * i / 100.0f;
            float dx = radius * cosf(angle);
            float dy = radius * sinf(angle);
            if (angle < 3.1415926f * 0.5f) {
                glVertex2f(feedhorn_x + dx, feedhorn_y + dy);
            }
        }
        glEnd();
    }

    // Joint (Dark Gray circle)
    glTranslatef(0.015f, 0.0f, 0.0f);
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircleA(0.0f, 0.0f, 0.015f);

    glPopMatrix(); // End dish assembly
}

/*
void drawCountdownText(float x, float y) {
    // Set text color: bright white
    glColor3f(1.0f, 1.0f, 1.0f);

    // Convert countdown number to text
    char text[10];
    sprintf(text, "%d", countdown);

    // Position text
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

*/


void drawAntenna1(float x, float y) {
    glPushMatrix();
    glTranslatef(-0.4f, -0.2f, 0.0f);
    glScalef(0.6f, 0.6f, 1.0f);

    float pivot_y = y;
    float base_y = y - 0.15f;

    // Base
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.08f, base_y - 0.03f);
        glVertex2f(x + 0.08f, base_y - 0.03f);
        glVertex2f(x + 0.08f, base_y);
        glVertex2f(x - 0.08f, base_y);
    glEnd();

    // Support Arm
    glBegin(GL_QUADS);
        glVertex2f(x - 0.04f, base_y);
        glVertex2f(x + 0.04f, base_y);
        glVertex2f(x + 0.02f, pivot_y);
        glVertex2f(x - 0.02f, pivot_y);
    glEnd();

    // Rotating Dish Assembly
    glPushMatrix();
    glTranslatef(x, pivot_y, 0.0f);
    glRotatef(antenna1Rotation, 0.0f, 0.0f, 1.0f);  // 🔄 Oscillating rotation
    glTranslatef(-0.015f, 0.0f, 0.0f);

    // Dish
    glColor3f(0.8f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 25; i <= 75; i++) {
        float angle = 2.0f * 3.1415926f * i / 100.0f;
        float radius = 0.12f;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(dx + 0.03f, dy);
    }
    glEnd();

    // Feedhorn Arm
    float feedhorn_x = 0.12f;
    float feedhorn_y = 0.05f;
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(feedhorn_x, feedhorn_y);
    glEnd();

    // Feedhorn
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircleA(feedhorn_x, feedhorn_y, 0.01f);

    // Signal Waves
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int j = 0; j < 3; j++) {
        glBegin(GL_LINE_STRIP);
        float radius = 0.03f + j * 0.02f;
        for (int i = 0; i <= 30; i++) {
            float angle = 2.0f * 3.1415926f * i / 100.0f;
            float dx = radius * cosf(angle);
            float dy = radius * sinf(angle);
            if (angle < 3.1415926f * 0.5f) {
                glVertex2f(feedhorn_x + dx, feedhorn_y + dy);
            }
        }
        glEnd();
    }

    // Joint
    glTranslatef(0.015f, 0.0f, 0.0f);
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircleA(0.0f, 0.0f, 0.015f);

    glPopMatrix(); // End dish assembly
    glPopMatrix(); // End antenna1
}





void drawBangladeshFlag(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.2f, 0.2f, 1.0f);

    // Flag body
    glColor3f(0.0f, 0.42f, 0.31f); // Dark green
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, 0.2f);
        glVertex2f( 0.3f, 0.2f);
        glVertex2f( 0.3f, -0.2f);
        glVertex2f(-0.3f, -0.2f);
    glEnd();

    // Red circle
    glColor3f(0.86f, 0.08f, 0.24f);
    drawCircleA(-0.05f, 0.0f, 0.09f);

    // Flag pole
    glColor3f(0.4f, 0.3f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-0.32f, -0.25f);
        glVertex2f(-0.28f, -0.25f);
        glVertex2f(-0.28f, 0.25f);
        glVertex2f(-0.32f, 0.25f);
    glEnd();

    glPopMatrix();
}

void r1(){
    glPushMatrix();
         glTranslatef(0.6f,-0.195f, 0.0f);

         glScalef(0.6f,0.6f , 1.0f);

            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.2f, 0.2f, 0.2f);
            glVertex2f(-0.491f, 0.672f);
            glVertex2f(-0.491f, 0.672f);
            glVertex2f(-0.402f, 0.672f);
            glVertex2f(-0.402f, -0.486f);
            glVertex2f(-0.489f, -0.482f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.2f, 0.2f, 0.2f);
            glVertex2f(-0.491f, 0.672f);
            glVertex2f(-0.491f, 0.672f);
            glVertex2f(-0.402f, 0.672f);
            glVertex2f(-0.402f, -0.486f);
            glVertex2f(-0.489f, -0.482f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(246,238,238);
            glVertex2f(-0.460f, 0.601f);
            glVertex2f(-0.471f, 0.617f);
            glVertex2f(-0.466f, 0.51f);
            glVertex2f(-0.449f, 0.522f);
            glVertex2f(-0.451f, 0.601f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(246,238,238);
            glVertex2f(-0.466f, 0.415f);
            glVertex2f(-0.457f, 0.292f);
            glVertex2f(-0.440f, 0.304f);
            glVertex2f(-0.446f, 0.443f);
            glVertex2f(-0.464f, 0.443f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(246,238,238);
            glVertex2f(-0.433f, 0.206f);
            glVertex2f(-0.426f, 0.028f);
            glVertex2f(-0.453f, 0.04f);
            glVertex2f(-0.460f, 0.209f);
            glVertex2f(-0.460f, 0.209f);
            glVertex2f(-0.453f, 0.221f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(246,238,238);
            glVertex2f(-0.437f, -0.047f);
            glVertex2f(-0.435f, -0.213f);
            glVertex2f(-0.455f, -0.221f);
            glVertex2f(-0.460f, -0.043f);
            glVertex2f(-0.462f, -0.04f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(246,238,238);
            glVertex2f(-0.451f, -0.296f);
            glVertex2f(-0.433f, -0.3f);
            glVertex2f(-0.435f, -0.395f);
            glVertex2f(-0.455f, -0.395f);
            glVertex2f(-0.460f, -0.281f);
            glVertex2f(-0.460f, -0.281f);
            glEnd();
            glPopMatrix();
}



void house() {
    glPushMatrix();

     glTranslatef(1.6f,-0.76f, 0.0f);

     glScalef(0.6f,0.6f , 1.0f);

    // left house start
    glBegin(GL_POLYGON); // body
        glColor3ub(224, 228, 231);
        glVertex2f(-1.4f, 0.5f);
        glVertex2f(-1.4f, 1.0f);
        glVertex2f(-0.9f, 1.0f);
        glVertex2f(-0.9f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON); // bottom-window 1
        glColor3ub(179, 230, 255);
        glVertex2f(-1.35f, 0.55f);
        glVertex2f(-1.35f, 0.65f);
        glColor3ub(0, 230, 230);
        glVertex2f(-1.25f, 0.65f);
        glVertex2f(-1.25f, 0.55f);
    glEnd();
    glBegin(GL_POLYGON); // bottom-window 2
        glColor3ub(179, 230, 255);
        glVertex2f(-1.05f, 0.55f);
        glVertex2f(-1.05f, 0.65f);
        glColor3ub(0, 230, 230);
        glVertex2f(-0.95f, 0.65f);
        glVertex2f(-0.95f, 0.55f);
    glEnd();

    glBegin(GL_POLYGON); // top-window 1
        glColor3ub(179, 230, 255);
        glVertex2f(-1.35f, 0.85f);
        glVertex2f(-1.35f, 0.95f);
        glColor3ub(0, 230, 230);
        glVertex2f(-1.25f, 0.95f);
        glVertex2f(-1.25f, 0.85f);
    glEnd();
    glBegin(GL_POLYGON); // top-window 2
        glColor3ub(179, 230, 255);
        glVertex2f(-1.2f, 0.85f);
        glVertex2f(-1.2f, 0.95f);
        glColor3ub(0, 230, 230);
        glVertex2f(-1.1f, 0.95f);
        glVertex2f(-1.1f, 0.85f);
    glEnd();
    glBegin(GL_POLYGON); // top-window 3
        glColor3ub(179, 230, 255);
        glVertex2f(-1.05f, 0.85f);
        glVertex2f(-1.05f, 0.95f);
        glColor3ub(0, 230, 230);
        glVertex2f(-0.95f, 0.95f);
        glVertex2f(-0.95f, 0.85f);
    glEnd();

    glBegin(GL_POLYGON); // door
        glColor3ub(153, 153, 153);
        glVertex2f(-1.2f, 0.5f);
        glVertex2f(-1.2f, 0.65f);
        glVertex2f(-1.1f, 0.65f);
        glVertex2f(-1.1f, 0.5f);
    glEnd();

    glPointSize(5.0); // door handle
    glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-1.17f, 0.58f);
	glEnd();

    glBegin(GL_LINES);
        glColor3ub(77, 195, 255);
        glVertex2f(-1.35f, 0.55f); // bottom-window 1
        glVertex2f(-1.35f, 0.65f);

        glVertex2f(-1.35f, 0.65f);
        glVertex2f(-1.25f, 0.65f);

        glVertex2f(-1.25f, 0.65f);
        glVertex2f(-1.25f, 0.55f);

        glVertex2f(-1.25f, 0.55f);
        glVertex2f(-1.35f, 0.55f);

        glVertex2f(-1.25f, 0.6f);
        glVertex2f(-1.35f, 0.6f);

        glVertex2f(-1.05f, 0.55f); // bottom-window 2
        glVertex2f(-1.05f, 0.65f);

        glVertex2f(-1.05f, 0.65f);
        glVertex2f(-0.95f, 0.65f);

        glVertex2f(-0.95f, 0.65f);
        glVertex2f(-0.95f, 0.55f);

        glVertex2f(-0.95f, 0.55f);
        glVertex2f(-1.05f, 0.55f);

        glVertex2f(-0.95f, 0.6f);
        glVertex2f(-1.05f, 0.6f);

        glVertex2f(-1.35f, 0.85f); // top-window 1
        glVertex2f(-1.35f, 0.95f);

        glVertex2f(-1.35f, 0.95f);
        glVertex2f(-1.25f, 0.95f);

        glVertex2f(-1.25f, 0.95f);
        glVertex2f(-1.25f, 0.85f);

        glVertex2f(-1.25f, 0.85f);
        glVertex2f(-1.35f, 0.85f);

        glVertex2f(-1.25f, 0.9f);
        glVertex2f(-1.35f, 0.9f);

        glVertex2f(-1.2f, 0.85f); // top-window 2
        glVertex2f(-1.2f, 0.95f);

        glVertex2f(-1.2f, 0.95f);
        glVertex2f(-1.1f, 0.95f);

        glVertex2f(-1.1f, 0.95f);
        glVertex2f(-1.1f, 0.85f);

        glVertex2f(-1.1f, 0.85f);
        glVertex2f(-1.2f, 0.85f);

        glVertex2f(-1.1f, 0.9f);
        glVertex2f(-1.2f, 0.9f);

        glVertex2f(-1.05f, 0.85f); // top-window 3
        glVertex2f(-1.05f, 0.95f);

        glVertex2f(-1.05f, 0.95f);
        glVertex2f(-0.95f, 0.95f);

        glVertex2f(-0.95f, 0.95f);
        glVertex2f(-0.95f, 0.85f);

        glVertex2f(-0.95f, 0.85f);
        glVertex2f(-1.05f, 0.85f);

        glVertex2f(-0.95f, 0.9f);
        glVertex2f(-1.05f, 0.9f);

        glVertex2f(-1.2f, 0.5f); // door
        glVertex2f(-1.2f, 0.65f);

        glVertex2f(-1.2f, 0.65f);
        glVertex2f(-1.1f, 0.65f);

        glVertex2f(-1.1f, 0.65f);
        glVertex2f(-1.1f, 0.5f);

        glVertex2f(-1.1f, 0.5f);
        glVertex2f(-1.2f, 0.5f);

        // body
        glColor3ub(128, 128, 128);

        glVertex2f(-1.4f, 0.5f);
        glVertex2f(-1.4f, 1.0f);

        glVertex2f(-1.4f, 1.0f);
        glVertex2f(-0.9f, 1.0f);

        glVertex2f(-0.9f, 1.0f);
        glVertex2f(-0.9f, 0.5f);

        glColor3ub(128, 0, 0);
        glVertex2f(-0.87f, 0.5f);
        glVertex2f(-1.43f, 0.5f);

        glVertex2f(-0.87f, 0.504f);
        glVertex2f(-1.43f, 0.504f);
    glEnd();

    glBegin(GL_POLYGON); // shelter
        glColor3ub(76, 174, 218);
        glVertex2f(-1.4f, 0.8f);
        glVertex2f(-1.45f, 0.75f);
        glVertex2f(-1.45f, 0.7f);
        glVertex2f(-0.85f, 0.7f);
        glVertex2f(-0.85f, 0.75f);
        glVertex2f(-0.9f, 0.8f);
    glEnd();

    glBegin(GL_LINES);
        glColor3ub(128, 128, 128);
        glVertex2f(-1.4f, 0.8f);
        glVertex2f(-1.45f, 0.75f);

        glVertex2f(-1.45f, 0.75f);
        glVertex2f(-1.45f, 0.7f);

        glVertex2f(-1.45f, 0.7f);
        glVertex2f(-0.85f, 0.7f);

        glVertex2f(-0.85f, 0.7f);
        glVertex2f(-0.85f, 0.75f);

        glVertex2f(-0.85f, 0.75f);
        glVertex2f(-0.9f, 0.8f);

        glVertex2f(-0.9f, 0.8f);
        glVertex2f(-1.4f, 0.8f);
    glEnd();
    // left house end

    // right house start
    glBegin(GL_POLYGON); // body
        glColor3ub(153, 51, 0);
        glVertex2f(-0.15f, 0.5f);
        glVertex2f(-0.15f, 0.8f);
        glVertex2f(0.35f, 0.8f);
        glVertex2f(0.35f, 0.5f);
    glEnd();
    glBegin(GL_POLYGON); // store room
        glColor3ub(153, 51, 0);
        glVertex2f(0.05f, 0.8f);
        glVertex2f(0.05f, 0.99f);
        glVertex2f(0.35f, 0.99f);
        glVertex2f(0.35f, 0.8f);
    glEnd();

    glBegin(GL_POLYGON); // window 1
        glColor3ub(77, 184, 255);
        glVertex2f(0.05f, 0.6f);
        glVertex2f(0.05f, 0.7f);
        glColor3ub(26, 140, 255);
        glVertex2f(0.15f, 0.7f);
        glVertex2f(0.15f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON); // window 2
        glColor3ub(77, 184, 255);
        glVertex2f(0.2f, 0.6f);
        glVertex2f(0.2f, 0.7f);
        glColor3ub(26, 140, 255);
        glVertex2f(0.3f, 0.7f);
        glVertex2f(0.3f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON); // store room window
        glColor3ub(77, 184, 255);
        glVertex2f(0.15f, 0.85f);
        glVertex2f(0.15f, 0.95f);
        glColor3ub(26, 140, 255);
        glVertex2f(0.25f, 0.95f);
        glVertex2f(0.25f, 0.85f);
    glEnd();

    glBegin(GL_POLYGON); // door
        glColor3ub(77, 77, 77);
        glVertex2f(-0.1f, 0.5f);
        glVertex2f(-0.1f, 0.65f);
        glVertex2f(0.0f, 0.65f);
        glVertex2f(0.0f, 0.5f);
    glEnd();

    glPointSize(5.0); // door handle
    glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.03f, 0.6f);
	glEnd();

    glBegin(GL_POLYGON); // door shelter
        glColor3ub(230, 115, 0);
        glVertex2f(0.02f, 0.65f);
        glVertex2f(-0.05f, 0.7f);
        glVertex2f(-0.12f, 0.65f);
    glEnd();

    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.15f, 0.85f); // store room window
        glVertex2f(0.15f, 0.95f);

        glVertex2f(0.15f, 0.95f);
        glVertex2f(0.25f, 0.95f);

        glVertex2f(0.25f, 0.95f);
        glVertex2f(0.25f, 0.85f);

        glVertex2f(0.25f, 0.85f);
        glVertex2f(0.15f, 0.85f);

        glVertex2f(0.05f, 0.6f); // window 1
        glVertex2f(0.05f, 0.7f);

        glVertex2f(0.05f, 0.7f);
        glVertex2f(0.15f, 0.7f);

        glVertex2f(0.15f, 0.7f);
        glVertex2f(0.15f, 0.6f);

        glVertex2f(0.15f, 0.6f);
        glVertex2f(0.05f, 0.6f);

        glVertex2f(0.2f, 0.6f); // window 2
        glVertex2f(0.2f, 0.7f);

        glVertex2f(0.2f, 0.7f);
        glVertex2f(0.3f, 0.7f);

        glVertex2f(0.3f, 0.7f);
        glVertex2f(0.3f, 0.6f);

        glVertex2f(0.3f, 0.6f);
        glVertex2f(0.2f, 0.6f);

        glColor3ub(255, 153, 51);
        glVertex2f(-0.1f, 0.5f); // door
        glVertex2f(-0.1f, 0.65f);

        glVertex2f(-0.1f, 0.65f);
        glVertex2f(0.0f, 0.65f);

        glVertex2f(0.0f, 0.65f);
        glVertex2f(0.0f, 0.5f);

        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.1f, 0.5f);

        glVertex2f(0.02f, 0.65f); // door shelter
        glVertex2f(-0.05f, 0.7f);

        glVertex2f(-0.05f, 0.7f);
        glVertex2f(-0.12f, 0.65f);

        glVertex2f(-0.12f, 0.65f);
        glVertex2f(0.02f, 0.65f);

        glVertex2f(0.36f, 0.8f); // roof railing
        glVertex2f(-0.16f, 0.8f);

        glVertex2f(0.36f, 0.84f);
        glVertex2f(-0.16f, 0.84f);

        glVertex2f(-0.14f, 0.8f);
        glVertex2f(-0.14f, 0.84f);

        glVertex2f(-0.1f, 0.8f);
        glVertex2f(-0.1f, 0.84f);

        glVertex2f(-0.05f, 0.8f);
        glVertex2f(-0.05f, 0.84f);

        glVertex2f(-0.0f, 0.8f);
        glVertex2f(-0.0f, 0.84f);

        glVertex2f(0.05f, 0.8f);
        glVertex2f(0.05f, 0.84f);

        glVertex2f(0.1f, 0.8f);
        glVertex2f(0.1f, 0.84f);

        glVertex2f(0.15f, 0.8f);
        glVertex2f(0.15f, 0.84f);

        glVertex2f(0.2f, 0.8f);
        glVertex2f(0.2f, 0.84f);

        glVertex2f(0.25f, 0.8f);
        glVertex2f(0.25f, 0.84f);

        glVertex2f(0.3f, 0.8f);
        glVertex2f(0.3f, 0.84f);

        glVertex2f(0.35f, 0.8f);
        glVertex2f(0.35f, 0.84f);

        glVertex2f(-0.16f, 0.504f); // ground
        glVertex2f(0.36f, 0.504f);

        glVertex2f(-0.16f, 0.5f);
        glVertex2f(0.36f, 0.5f);

        glVertex2f(0.04f, 0.99f); // top roof
        glVertex2f(0.36f, 0.99f);

        glVertex2f(0.04f, 0.985f);
        glVertex2f(0.36f, 0.985f);
    glEnd();

    glPopMatrix();


}


void r2(){
    glPushMatrix();
         glTranslatef(1.53f,-0.31f, 0.0f);

         glScalef(0.68f,0.39f , 1.0f);

            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.2f, 0.2f, 0.2f);
            glVertex2f(-0.491f, 0.672f);
            glVertex2f(-0.491f, 0.672f);
            glVertex2f(-0.402f, 0.672f);
            glVertex2f(-0.402f, -0.486f);
            glVertex2f(-0.489f, -0.482f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.2f, 0.2f, 0.2f);
            glVertex2f(-0.491f, 0.672f);
            glVertex2f(-0.491f, 0.672f);
            glVertex2f(-0.402f, 0.672f);
            glVertex2f(-0.402f, -0.486f);
            glVertex2f(-0.489f, -0.482f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(246,238,238);
            glVertex2f(-0.460f, 0.601f);
            glVertex2f(-0.471f, 0.617f);
            glVertex2f(-0.466f, 0.51f);
            glVertex2f(-0.449f, 0.522f);
            glVertex2f(-0.451f, 0.601f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(246,238,238);
            glVertex2f(-0.466f, 0.415f);
            glVertex2f(-0.457f, 0.292f);
            glVertex2f(-0.440f, 0.304f);
            glVertex2f(-0.446f, 0.443f);
            glVertex2f(-0.464f, 0.443f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(246,238,238);
            glVertex2f(-0.433f, 0.206f);
            glVertex2f(-0.426f, 0.028f);
            glVertex2f(-0.453f, 0.04f);
            glVertex2f(-0.460f, 0.209f);
            glVertex2f(-0.460f, 0.209f);
            glVertex2f(-0.453f, 0.221f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(246,238,238);
            glVertex2f(-0.437f, -0.047f);
            glVertex2f(-0.435f, -0.213f);
            glVertex2f(-0.455f, -0.221f);
            glVertex2f(-0.460f, -0.043f);
            glVertex2f(-0.462f, -0.04f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(246,238,238);
            glVertex2f(-0.451f, -0.296f);
            glVertex2f(-0.433f, -0.3f);
            glVertex2f(-0.435f, -0.395f);
            glVertex2f(-0.455f, -0.395f);
            glVertex2f(-0.460f, -0.281f);
            glVertex2f(-0.460f, -0.281f);
            glEnd();
            glPopMatrix();
            }

void house1() {
    glPushMatrix();

     glTranslatef(1.26f,-0.45f, 0.0f);

     glScalef(0.8f,0.8f , 1.0f);

    // left house start
    glBegin(GL_POLYGON); // body
        glColor3ub(224, 228, 231);
        glVertex2f(-1.4f, 0.5f);
        glVertex2f(-1.4f, 1.0f);
        glVertex2f(-0.9f, 1.0f);
        glVertex2f(-0.9f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON); // bottom-window 1
        glColor3ub(179, 230, 255);
        glVertex2f(-1.35f, 0.55f);
        glVertex2f(-1.35f, 0.65f);
        glColor3ub(0, 230, 230);
        glVertex2f(-1.25f, 0.65f);
        glVertex2f(-1.25f, 0.55f);
    glEnd();
    glBegin(GL_POLYGON); // bottom-window 2
        glColor3ub(179, 230, 255);
        glVertex2f(-1.05f, 0.55f);
        glVertex2f(-1.05f, 0.65f);
        glColor3ub(0, 230, 230);
        glVertex2f(-0.95f, 0.65f);
        glVertex2f(-0.95f, 0.55f);
    glEnd();

    glBegin(GL_POLYGON); // top-window 1
        glColor3ub(179, 230, 255);
        glVertex2f(-1.35f, 0.85f);
        glVertex2f(-1.35f, 0.95f);
        glColor3ub(0, 230, 230);
        glVertex2f(-1.25f, 0.95f);
        glVertex2f(-1.25f, 0.85f);
    glEnd();
    glBegin(GL_POLYGON); // top-window 2
        glColor3ub(179, 230, 255);
        glVertex2f(-1.2f, 0.85f);
        glVertex2f(-1.2f, 0.95f);
        glColor3ub(0, 230, 230);
        glVertex2f(-1.1f, 0.95f);
        glVertex2f(-1.1f, 0.85f);
    glEnd();
    glBegin(GL_POLYGON); // top-window 3
        glColor3ub(179, 230, 255);
        glVertex2f(-1.05f, 0.85f);
        glVertex2f(-1.05f, 0.95f);
        glColor3ub(0, 230, 230);
        glVertex2f(-0.95f, 0.95f);
        glVertex2f(-0.95f, 0.85f);
    glEnd();

    glBegin(GL_POLYGON); // door
        glColor3ub(153, 153, 153);
        glVertex2f(-1.2f, 0.5f);
        glVertex2f(-1.2f, 0.65f);
        glVertex2f(-1.1f, 0.65f);
        glVertex2f(-1.1f, 0.5f);
    glEnd();

    glPointSize(5.0); // door handle
    glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-1.17f, 0.58f);
	glEnd();

    glBegin(GL_LINES);
        glColor3ub(77, 195, 255);
        glVertex2f(-1.35f, 0.55f); // bottom-window 1
        glVertex2f(-1.35f, 0.65f);

        glVertex2f(-1.35f, 0.65f);
        glVertex2f(-1.25f, 0.65f);

        glVertex2f(-1.25f, 0.65f);
        glVertex2f(-1.25f, 0.55f);

        glVertex2f(-1.25f, 0.55f);
        glVertex2f(-1.35f, 0.55f);

        glVertex2f(-1.25f, 0.6f);
        glVertex2f(-1.35f, 0.6f);

        glVertex2f(-1.05f, 0.55f); // bottom-window 2
        glVertex2f(-1.05f, 0.65f);

        glVertex2f(-1.05f, 0.65f);
        glVertex2f(-0.95f, 0.65f);

        glVertex2f(-0.95f, 0.65f);
        glVertex2f(-0.95f, 0.55f);

        glVertex2f(-0.95f, 0.55f);
        glVertex2f(-1.05f, 0.55f);

        glVertex2f(-0.95f, 0.6f);
        glVertex2f(-1.05f, 0.6f);

        glVertex2f(-1.35f, 0.85f); // top-window 1
        glVertex2f(-1.35f, 0.95f);

        glVertex2f(-1.35f, 0.95f);
        glVertex2f(-1.25f, 0.95f);

        glVertex2f(-1.25f, 0.95f);
        glVertex2f(-1.25f, 0.85f);

        glVertex2f(-1.25f, 0.85f);
        glVertex2f(-1.35f, 0.85f);

        glVertex2f(-1.25f, 0.9f);
        glVertex2f(-1.35f, 0.9f);

        glVertex2f(-1.2f, 0.85f); // top-window 2
        glVertex2f(-1.2f, 0.95f);

        glVertex2f(-1.2f, 0.95f);
        glVertex2f(-1.1f, 0.95f);

        glVertex2f(-1.1f, 0.95f);
        glVertex2f(-1.1f, 0.85f);

        glVertex2f(-1.1f, 0.85f);
        glVertex2f(-1.2f, 0.85f);

        glVertex2f(-1.1f, 0.9f);
        glVertex2f(-1.2f, 0.9f);

        glVertex2f(-1.05f, 0.85f); // top-window 3
        glVertex2f(-1.05f, 0.95f);

        glVertex2f(-1.05f, 0.95f);
        glVertex2f(-0.95f, 0.95f);

        glVertex2f(-0.95f, 0.95f);
        glVertex2f(-0.95f, 0.85f);

        glVertex2f(-0.95f, 0.85f);
        glVertex2f(-1.05f, 0.85f);

        glVertex2f(-0.95f, 0.9f);
        glVertex2f(-1.05f, 0.9f);

        glVertex2f(-1.2f, 0.5f); // door
        glVertex2f(-1.2f, 0.65f);

        glVertex2f(-1.2f, 0.65f);
        glVertex2f(-1.1f, 0.65f);

        glVertex2f(-1.1f, 0.65f);
        glVertex2f(-1.1f, 0.5f);

        glVertex2f(-1.1f, 0.5f);
        glVertex2f(-1.2f, 0.5f);

        // body
        glColor3ub(128, 128, 128);

        glVertex2f(-1.4f, 0.5f);
        glVertex2f(-1.4f, 1.0f);

        glVertex2f(-1.4f, 1.0f);
        glVertex2f(-0.9f, 1.0f);

        glVertex2f(-0.9f, 1.0f);
        glVertex2f(-0.9f, 0.5f);

        glColor3ub(128, 0, 0);
        glVertex2f(-0.87f, 0.5f);
        glVertex2f(-1.43f, 0.5f);

        glVertex2f(-0.87f, 0.504f);
        glVertex2f(-1.43f, 0.504f);
    glEnd();

    glBegin(GL_POLYGON); // shelter
        glColor3ub(76, 174, 218);
        glVertex2f(-1.4f, 0.8f);
        glVertex2f(-1.45f, 0.75f);
        glVertex2f(-1.45f, 0.7f);
        glVertex2f(-0.85f, 0.7f);
        glVertex2f(-0.85f, 0.75f);
        glVertex2f(-0.9f, 0.8f);
    glEnd();

    glBegin(GL_LINES);
        glColor3ub(128, 128, 128);
        glVertex2f(-1.4f, 0.8f);
        glVertex2f(-1.45f, 0.75f);

        glVertex2f(-1.45f, 0.75f);
        glVertex2f(-1.45f, 0.7f);

        glVertex2f(-1.45f, 0.7f);
        glVertex2f(-0.85f, 0.7f);

        glVertex2f(-0.85f, 0.7f);
        glVertex2f(-0.85f, 0.75f);

        glVertex2f(-0.85f, 0.75f);
        glVertex2f(-0.9f, 0.8f);

        glVertex2f(-0.9f, 0.8f);
        glVertex2f(-1.4f, 0.8f);
    glEnd();
    // left house end

    // right house start
    glBegin(GL_POLYGON); // body
        glColor3ub(153, 51, 0);
        glVertex2f(-0.15f, 0.5f);
        glVertex2f(-0.15f, 0.8f);
        glVertex2f(0.35f, 0.8f);
        glVertex2f(0.35f, 0.5f);
    glEnd();
    glBegin(GL_POLYGON); // store room
        glColor3ub(153, 51, 0);
        glVertex2f(0.05f, 0.8f);
        glVertex2f(0.05f, 0.99f);
        glVertex2f(0.35f, 0.99f);
        glVertex2f(0.35f, 0.8f);
    glEnd();

    glBegin(GL_POLYGON); // window 1
        glColor3ub(77, 184, 255);
        glVertex2f(0.05f, 0.6f);
        glVertex2f(0.05f, 0.7f);
        glColor3ub(26, 140, 255);
        glVertex2f(0.15f, 0.7f);
        glVertex2f(0.15f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON); // window 2
        glColor3ub(77, 184, 255);
        glVertex2f(0.2f, 0.6f);
        glVertex2f(0.2f, 0.7f);
        glColor3ub(26, 140, 255);
        glVertex2f(0.3f, 0.7f);
        glVertex2f(0.3f, 0.6f);
    glEnd();

    glBegin(GL_POLYGON); // store room window
        glColor3ub(77, 184, 255);
        glVertex2f(0.15f, 0.85f);
        glVertex2f(0.15f, 0.95f);
        glColor3ub(26, 140, 255);
        glVertex2f(0.25f, 0.95f);
        glVertex2f(0.25f, 0.85f);
    glEnd();

    glBegin(GL_POLYGON); // door
        glColor3ub(77, 77, 77);
        glVertex2f(-0.1f, 0.5f);
        glVertex2f(-0.1f, 0.65f);
        glVertex2f(0.0f, 0.65f);
        glVertex2f(0.0f, 0.5f);
    glEnd();

    glPointSize(5.0); // door handle
    glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.03f, 0.6f);
	glEnd();

    glBegin(GL_POLYGON); // door shelter
        glColor3ub(230, 115, 0);
        glVertex2f(0.02f, 0.65f);
        glVertex2f(-0.05f, 0.7f);
        glVertex2f(-0.12f, 0.65f);
    glEnd();

    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(0.15f, 0.85f); // store room window
        glVertex2f(0.15f, 0.95f);

        glVertex2f(0.15f, 0.95f);
        glVertex2f(0.25f, 0.95f);

        glVertex2f(0.25f, 0.95f);
        glVertex2f(0.25f, 0.85f);

        glVertex2f(0.25f, 0.85f);
        glVertex2f(0.15f, 0.85f);

        glVertex2f(0.05f, 0.6f); // window 1
        glVertex2f(0.05f, 0.7f);

        glVertex2f(0.05f, 0.7f);
        glVertex2f(0.15f, 0.7f);

        glVertex2f(0.15f, 0.7f);
        glVertex2f(0.15f, 0.6f);

        glVertex2f(0.15f, 0.6f);
        glVertex2f(0.05f, 0.6f);

        glVertex2f(0.2f, 0.6f); // window 2
        glVertex2f(0.2f, 0.7f);

        glVertex2f(0.2f, 0.7f);
        glVertex2f(0.3f, 0.7f);

        glVertex2f(0.3f, 0.7f);
        glVertex2f(0.3f, 0.6f);

        glVertex2f(0.3f, 0.6f);
        glVertex2f(0.2f, 0.6f);

        glColor3ub(255, 153, 51);
        glVertex2f(-0.1f, 0.5f); // door
        glVertex2f(-0.1f, 0.65f);

        glVertex2f(-0.1f, 0.65f);
        glVertex2f(0.0f, 0.65f);

        glVertex2f(0.0f, 0.65f);
        glVertex2f(0.0f, 0.5f);

        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.1f, 0.5f);

        glVertex2f(0.02f, 0.65f); // door shelter
        glVertex2f(-0.05f, 0.7f);

        glVertex2f(-0.05f, 0.7f);
        glVertex2f(-0.12f, 0.65f);

        glVertex2f(-0.12f, 0.65f);
        glVertex2f(0.02f, 0.65f);

        glVertex2f(0.36f, 0.8f); // roof railing
        glVertex2f(-0.16f, 0.8f);

        glVertex2f(0.36f, 0.84f);
        glVertex2f(-0.16f, 0.84f);

        glVertex2f(-0.14f, 0.8f);
        glVertex2f(-0.14f, 0.84f);

        glVertex2f(-0.1f, 0.8f);
        glVertex2f(-0.1f, 0.84f);

        glVertex2f(-0.05f, 0.8f);
        glVertex2f(-0.05f, 0.84f);

        glVertex2f(-0.0f, 0.8f);
        glVertex2f(-0.0f, 0.84f);

        glVertex2f(0.05f, 0.8f);
        glVertex2f(0.05f, 0.84f);

        glVertex2f(0.1f, 0.8f);
        glVertex2f(0.1f, 0.84f);

        glVertex2f(0.15f, 0.8f);
        glVertex2f(0.15f, 0.84f);

        glVertex2f(0.2f, 0.8f);
        glVertex2f(0.2f, 0.84f);

        glVertex2f(0.25f, 0.8f);
        glVertex2f(0.25f, 0.84f);

        glVertex2f(0.3f, 0.8f);
        glVertex2f(0.3f, 0.84f);

        glVertex2f(0.35f, 0.8f);
        glVertex2f(0.35f, 0.84f);

        glVertex2f(-0.16f, 0.504f); // ground
        glVertex2f(0.36f, 0.504f);

        glVertex2f(-0.16f, 0.5f);
        glVertex2f(0.36f, 0.5f);

        glVertex2f(0.04f, 0.99f); // top roof
        glVertex2f(0.36f, 0.99f);

        glVertex2f(0.04f, 0.985f);
        glVertex2f(0.36f, 0.985f);
    glEnd();

    glPopMatrix();

}


void drawSignalTower(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Sway animation for realistic motion (slightly elastic)
   // float sway = sin(glutGet(GLUT_ELAPSED_TIME) * 0.002f) * 0.03f;
   // glTranslatef(sway, 0.0f, 0.0f);



    //Tower Steel Structure ===
    glLineWidth(3.0f); // make lines bold

    // Dark metallic grey
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_LINES);
        // Vertical pillars
        glVertex2f(-0.08f, 0.0f); glVertex2f(-0.08f, 1.0f);
        glVertex2f( 0.08f, 0.0f); glVertex2f( 0.08f, 1.0f);

        // Cross braces (X patterns)
        for (float h = 0.0f; h <= 0.9f; h += 0.1f) {
            glVertex2f(-0.08f, h);
            glVertex2f( 0.08f, h + 0.1f);

            glVertex2f( 0.08f, h);
            glVertex2f(-0.08f, h + 0.1f);
        }

        // Horizontal beams
        for (float h = 0.0f; h <= 1.0f; h += 0.1f) {
            glVertex2f(-0.08f, h);
            glVertex2f( 0.08f, h);
        }
    glEnd();

    // Metal Plates for Strength
    glColor3f(0.45f, 0.45f, 0.45f);
    for (float h = 0.0f; h <= 1.0f; h += 0.2f) {
        glBegin(GL_QUADS);
            glVertex2f(-0.09f, h);
            glVertex2f( 0.09f, h);
            glVertex2f( 0.09f, h + 0.02f);
            glVertex2f(-0.09f, h + 0.02f);
        glEnd();
    }

    // Tower Head
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, 1.0f);
        glVertex2f( 0.03f, 1.0f);
        glVertex2f( 0.03f, 1.25f);
        glVertex2f(-0.03f, 1.25f);
    glEnd();

    //  Top Red Light (with glow effect)
    if ((glutGet(GLUT_ELAPSED_TIME) / 500) % 2 == 0)
        glColor3f(1.0f, 0.0f, 0.0f);
    else
        glColor3f(0.3f, 0.0f, 0.0f);

    drawCircleA(0.0f, 1.28f, 0.035f);
/*
    // Signal Waves (bold golden arcs)
    glLineWidth(2.0f);
    glColor3f(1.0f, 0.75f, 0.1f);
    for (float r = 0.18f; r <= 0.4f; r += 0.1f) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 50; i++) {
            float a = i * 2 * 3.1416f / 50;
            glVertex2f(r * cos(a), 1.28f + r * sin(a));
        }
        glEnd();
    }
    */

    //Base Foundation (reinforced concrete)
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.0f);
        glVertex2f( 0.15f, 0.0f);
        glVertex2f( 0.15f,-0.08f);
        glVertex2f(-0.15f,-0.08f);
    glEnd();

    // Metallic shadow for realism
    glColor3f(0.1f, 0.1f, 0.1f);
    drawEllipseA(0.0f, -0.09f, 0.18f, 0.03f);

    glPopMatrix();
}

void drawText(float x, float y, const char* string, void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
void drawText1(float x, float y, const char* string, void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
void drawText2(float x, float y, const char* string, void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
void updateCountdown() {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (showCountdown && currentTime - lastTime > 1000) { // 1 second
        lastTime = currentTime;
        countdown--;
        if (countdown <= 0) {
            countdown = 0;
            showCountdown = false; // stop showing countdown when done
        }
    }
}

void BlackScreen(){
glPushMatrix();
glTranslatef(-0.35f,-0.07f, 0.0f);

glScalef(0.5f, 0.3f , 1.0f);


            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(0,0,0);
            glVertex2f(0.431f, 0.103f);
            glVertex2f(0.434f, -0.146f);
            glVertex2f(-0.522f, -0.138f);
            glVertex2f(-0.529f, 0.68f);
            glVertex2f(0.429f, 0.676f);
            glEnd();
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(155,146,151);
            glVertex2f(-0.415f, -0.134f);
            glVertex2f(-0.415f, -0.538f);
            glVertex2f(-0.357f, -0.534f);
            glVertex2f(-0.355f, -0.111f);
            glEnd();
          /*  glBegin(GL_TRIANGLE_FAN);
            glColor3ub(0,0,0);
            glVertex2f(-0.877f, -0.332f);
            glVertex2f(-0.882f, -0.332f);
            glVertex2f(-0.893f, -0.34f);
            glVertex2f(-0.895f, 0.47f);
            glVertex2f(-0.809f, 0.431f);
            glVertex2f(-0.822f, -0.352f);
            glEnd();
            */
            glBegin(GL_TRIANGLE_FAN);
            glColor3ub(155,146,151);
            glVertex2f(0.291f, -0.15f);
            glVertex2f(0.229f, -0.146f);
            glVertex2f(0.220f, -0.502f);
            glVertex2f(0.294f, -0.498f);
            glEnd();

glPopMatrix();
}

void display() {
 glClear(GL_COLOR_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
 glClearColor(0.529f, 0.808f, 0.922f, 1.0f);

 glLoadIdentity();

drawSunA();

drawMountains();


// Draw all birds
for (int i = 0; i < 10; i++) {
    drawBird(birdX[i], birdY[i]);
}


 RiverView();
 Grass();
 RiverSideLean();
 Road();


 drawBangladeshFlag(1.66f, 0.90f, 0.4f); // x, y, size
 drawRocketA();
 drawLaunchPad();

// drawCountdownText(-1.35f, -0.35f);

 drawEnhancedAntenna(-1.0f,0.0f);
 drawEnhancedAntenna1(-1.65f,-0.43f);
 drawAntenna(-1.7f,0.05f);
 drawAntenna1(-0.85f,-0.05f);

 drawTree();
 drawTreeA();
 drawTreeB();
 drawTreeC();
 drawTreeD();
 drawFruits();
 drawFruitsA();
 drawFruitsB();
 drawFruitsC();
 drawFruitsD();
 RoadSideLean();
 drawSignalTower(-0.7f, -0.1f, 0.4f);
 RoadSideMiddle();
 house();
 r1();
 house1();
 r2();

BlackScreen();

glPushMatrix();
glTranslatef(-0.3f,-0.8f, 0.0f);
if (showCountdown) {
    char buffer[10];
    sprintf(buffer, "%d", countdown);

    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow text
    drawText(-0.05f, 0.8f, buffer, GLUT_BITMAP_TIMES_ROMAN_24); // Center-top
}
else {
    glColor3f(0.0f, 1.0f, 0.0f);
    drawText(-0.3f, 0.8f, "            Launch!", GLUT_BITMAP_HELVETICA_18);
}
//glScalef(ufoscale, ufoscale , 1.0f);
updateCountdown();
glPopMatrix();




glPushMatrix();
glTranslatef(0.1f,0.05f, 0.0f);
glScalef(0.1f,0.1f , 1.0f);
drawText1(-0.05f, 0.8f, "Alamin Parmacy", GLUT_BITMAP_TIMES_ROMAN_24);
glPopMatrix();



glPushMatrix();
glTranslatef(0.83f,-0.324f, 0.0f);
glScalef(0.0f,0.0f , 1.0f);
drawText2(-0.05f, 0.8f, "AMK", GLUT_BITMAP_TIMES_ROMAN_24);
glPopMatrix();

glutPostRedisplay();

 drawShip1();
 drawShip2();
 glPushMatrix();
 glPopMatrix();
 drawCloud(cloud1X, cloud1Y);
 drawCloud(cloud2X, cloud2Y);
 drawCloud(cloud3X, cloud3Y);

 drawCloudVariant(cloud4X, cloud4Y);
 drawCloudVariant(cloud5X, cloud5Y);
 drawCloudVariant(cloud6X, cloud6Y);
 drawCloudVariant(cloud7X, cloud7Y);


    // Draw moving car
    drawCar(carX, carY);


 glutSwapBuffers();

}


void alamin_idle()
{
rayRotationA += 0.05f;  // Rotate sun
    if (rayRotationA >= 360.0f) rayRotationA -= 360.0f;
// Move ships with river
ship1X += shipSpeed * 0.5f;
ship2X -= shipSpeed * 0.7f;

// Reset positions when off-screen
if (ship1X > 1.2f) ship1X = -1.2f;
if (ship2X < -1.2f) ship2X = 1.2f;

    // River movement
riverOffset += riverSpeed;
if (riverOffset > 1.0f) riverOffset = 0.0f;

    // Existing clouds
    cloud1X += cloudSpeed;
    cloud2X += cloudSpeed * 0.8f;
    cloud3X += cloudSpeed * 1.2f;

    // New clouds
    cloud4X += cloudSpeed * 1.1f;
    cloud5X += cloudSpeed * 0.9f;
    cloud6X += cloudSpeed * 1.05f;
    cloud7X += cloudSpeed * 0.95f;

    // Reset positions when off-screen
    if(cloud1X > 1.5f) cloud1X = -1.5f;
    if(cloud2X > 1.5f) cloud2X = -1.5f;
    if(cloud3X > 1.5f) cloud3X = -1.5f;
    if(cloud4X > 1.5f) cloud4X = -1.5f;
    if(cloud5X > 1.5f) cloud5X = -1.5f;
    if(cloud6X > 1.5f) cloud6X = -1.5f;
    if(cloud7X > 1.5f) cloud7X = -1.5f;

    // Move birds
for(int i = 0; i < 10; i++){
    birdX[i] += birdSpeed[i];
    if (birdX[i] > 1.5f) birdX[i] = -1.5f; // loop from left
}
    //Move the car
    carX += carSpeed;
    if (carX > 1.8f) carX = -1.8f; // loop when off-screen

    updateFruits();
    updateFruitsA();
    updateFruitsB();
    updateFruitsC();
    updateFruitsD();


    if (antennaForward) {
    antennaRotation += antennaSpeed;
    if (antennaRotation >= 50.0f) antennaForward = false;
} else {
    antennaRotation -= antennaSpeed;
    if (antennaRotation <= 20.0f) antennaForward = true;
}



    if (antenna1Forward) {
    antenna1Rotation += antenna1Speed;
    if (antenna1Rotation >= 80.0f) antenna1Forward = false;
} else {
    antenna1Rotation -= antenna1Speed;
    if (antenna1Rotation <= 20.0f) antenna1Forward = true;
}


}




void update(int value)
{
    rocketflyA += rocketSpeedA;

     //rocket flame
    if (flameUpa) {
    upperFlameOffsetA += 0.0008f;
    if (upperFlameOffsetA > 0.015f) flameUpa = false;
} else {
    upperFlameOffsetA -= 0.0008f;
    if (upperFlameOffsetA < -0.015f) flameUpa = true;
}
    //lower flame
    if (lowerFlameUpA) {
    lowerFlameOffsetA += 0.0008f;
    if (lowerFlameOffsetA > 0.015f) lowerFlameUpA = false;
} else {
    lowerFlameOffsetA -= 0.0008f;
    if (lowerFlameOffsetA < -0.015f) lowerFlameUpA = true;
}
// Countdown time-logic
frameCount++;
if (frameCount >= 60) {  // roughly 1 second (if 60 FPS)
    frameCount = 0;
    if (countdown > 0) {
        countdown--;
    }
}


     glutPostRedisplay();
    glutTimerFunc(16, update, 0);

}




//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA





float moonx =0.1;
float asteroidX=-1.8;  // move right
 float asteroidY=0.08;
  // move up slightly
 float satelliteX1 = -1.8f;
    float satelliteY1 = 0.01f;
    float satelliteX2 = -0.85f;
    float satelliteY2 = -0.9f;
    float satelliteX3 = -0.45f;
    float satelliteY3 = -0.5f;

    float rayRotationM = 0.0f;
    float MoonRotation  = 0.0f;

    float EarthRotation  = 0.0f;

    float sat1speed = 0.0002f;
    float sat2speed = 0.000050f;
    float sat3speed = 0.0001f;

    float ufoXM = -1.9f; // UFO starts at left edge
    float ufoYM = 0.3f;  // UFO base y-position (mid-upper)
    float ufoTime = 0.0f; // For sinusoidal vertical motion


    float ufo2X = 1.0f;   // Start at right edge
    float ufo2Y = 1.5f;  // Start at lower corner
    float ufo2Time = 0.0f; // For sinusoidal vertical motion


    float cometX = 1.1f;  // Start near moon (behind)
    float cometY = 0.9f;  // Start above moon

    float mercuryX = 1.2f;  // Right lower corner
    float mercuryY = -0.6f;  // Right lower corner
    float mercuryRotation = 0.0f;  // Rotation angle for Mercury, matching moon's speed

    float mercury2X = 1.5f;  // Right lower corner
    float mercury2Y = -0.2f;  // Right lower corner
    float mercury2Rotation = 0.0f;  // Rotation angle for Mercury, matching moon's speed


    float rocketYM = 2.6f;       // Starting Y position
    float rocketSpeedM = -0.0009f; // Downward speed
    float upperFlameOffsetM = 0.0f;  //Upper rocket flame
    bool flameUpM = true;
    float lowerFlameOffsetM = 0.0f;
    bool lowerFlameUpM = true;
    float rocketFlx = 0.0f;
    float rocketFly = 0.0f;
    float rocketangle = 0.0f;
     // float rocketanglediff = -0.009f;

    float rocketscale = 1.0f;
    float rocketLowerX = 0.0f;
    float rocketLowerY = 0.0f;
    float rocketlowerangle = 0.0f;
    float rocketlowerscale = 1.0;
    bool lowerflamebool = true;




    float blackHole1X = -1.2f;  // Black hole 1 starting x
    float blackHole1Y = 0.3f;   // Black hole 1 starting y
    float blackHole1Angle = 0.0f;  // Angle for elliptical orbit
    float blackHole2X = 0.8f;   // Black hole 2 starting x
    float blackHole2Y = -0.6f;  // Black hole 2 starting y
    float blackHole2Time = 0.0f;  // Time for sinusoidal motion
    float blackHole3X = 1.5f;   // Black hole 3 starting x
    float blackHole3Y = 0.4f;   // Black hole 3 starting y
    float blackHole3Angle = 0.0f;  // Angle for circular orbit


    float venusAngleM = 0.0f;





void drawEllipseM(float x_center, float y_center, float a, float b) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100; // Angle in radians, 100 segments
        float x = x_center + a * cosf(angle);
        float y = y_center + b * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}


void drawCircleM(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}
void drawStarM(float cx, float cy, float innerRadius, float outerRadius, int numPoints) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 2 * numPoints; i++) {
        float angle = i * 3.1415926f / numPoints;  // Half angle for alternate points
        float r = (i % 2 == 0) ? outerRadius : innerRadius; // alternate radius
        float x = cx + r * cosf(angle);
        float y = cy + r * sinf(angle);
        glVertex2f(x, y);
    }
glEnd();
}
void displaystarM()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    // Close stars (bigger)
    drawStarM(-0.7f, 0.8f, 0.015f, 0.03f, 10);
    drawStarM(1.2f, 0.5f, 0.012f, 0.025f, 10);
    drawStarM(-1.5f, 0.3f, 0.01f, 0.02f, 10);
    drawStarM(0.9f, -0.2f, 0.013f, 0.028f, 10);
    drawStarM(-1.8f, -0.5f, 0.012f, 0.025f, 10);
    drawStarM(1.5f, 0.8f, 0.014f, 0.03f, 10);
    drawStarM(-0.3f, 0.7f, 0.012f, 0.027f, 10);
    drawStarM(0.0f, 0.9f, 0.013f, 0.028f, 10);
    drawStarM(-1.0f, -0.7f, 0.011f, 0.024f, 10);
    drawStarM(1.8f, -0.8f, 0.01f, 0.02f, 10);

    // Medium stars
    drawStarM(-0.5f, 0.2f, 0.007f, 0.018f, 10);
    drawStarM(0.5f, -0.5f, 0.008f, 0.02f, 10);
    drawStarM(-1.2f, 0.6f, 0.009f, 0.022f, 10);
    drawStarM(1.0f, 0.0f, 0.007f, 0.018f, 10);
    drawStarM(-0.9f, -0.3f, 0.006f, 0.015f, 10);
    drawStarM(0.8f, 0.9f, 0.008f, 0.02f, 10);
    drawStarM(-1.6f, 0.1f, 0.007f, 0.018f, 10);
    drawStarM(1.3f, -0.4f, 0.009f, 0.02f, 10);
    drawStarM(-0.2f, -0.8f, 0.006f, 0.015f, 10);
    drawStarM(0.2f, 0.6f, 0.007f, 0.018f, 10);

    // Distant stars (smaller)
    drawStarM(-1.9f, 0.9f, 0.004f, 0.01f, 10);
    drawStarM(1.9f, 0.7f, 0.005f, 0.012f, 10);
    drawStarM(-1.3f, -0.9f, 0.004f, 0.01f, 10);
    drawStarM(1.1f, -0.6f, 0.005f, 0.012f, 10);
    drawStarM(-0.7f, -0.9f, 0.006f, 0.015f, 10);
    drawStarM(0.6f, 0.3f, 0.005f, 0.012f, 10);
    drawStarM(-0.4f, 0.0f, 0.004f, 0.01f, 10);
    drawStarM(0.3f, -0.2f, 0.005f, 0.012f, 10);
    drawStarM(-0.1f, 0.4f, 0.006f, 0.015f, 10);
    drawStarM(0.0f, -0.6f, 0.005f, 0.012f, 10);

    // Extra random stars
    drawStarM(1.7f, 0.1f, 0.005f, 0.012f, 10);
    drawStarM(-1.4f, 0.5f, 0.006f, 0.015f, 10);
    drawStarM(0.9f, -0.9f, 0.004f, 0.01f, 10);
    drawStarM(-1.8f, 0.3f, 0.007f, 0.018f, 10);
    drawStarM(1.5f, -0.2f, 0.005f, 0.012f, 10);
    drawStarM(-0.5f, 0.9f, 0.006f, 0.015f, 10);
    drawStarM(0.4f, -0.1f, 0.005f, 0.012f, 10);
    drawStarM(-1.1f, -0.5f, 0.004f, 0.01f, 10);
    drawStarM(1.2f, 0.2f, 0.007f, 0.018f, 10);
    drawStarM(-0.8f, 0.0f, 0.005f, 0.012f, 10);

    drawStarM(0.0f, 0.1f, 0.006f, 0.015f, 10);
    drawStarM(-1.0f, 0.8f, 0.005f, 0.012f, 10);
    drawStarM(0.8f, -0.7f, 0.004f, 0.01f, 10);
    drawStarM(-0.3f, 0.5f, 0.007f, 0.018f, 10);
    drawStarM(1.4f, 0.6f, 0.005f, 0.012f, 10);
    drawStarM(-1.6f, -0.2f, 0.006f, 0.015f, 10);
    drawStarM(0.3f, -0.4f, 0.005f, 0.012f, 10);
    drawStarM(-0.6f, -0.7f, 0.004f, 0.01f, 10);
    drawStarM(0.5f, 0.8f, 0.007f, 0.018f, 10);
    drawStarM(-0.9f, 0.2f, 0.006f, 0.015f, 10);

    drawStarM(0.0f, -0.9f, 0.005f, 0.012f, 10);
    drawStarM(1.0f, 0.9f, 0.004f, 0.01f, 10);
    drawStarM(-1.2f, -0.1f, 0.007f, 0.018f, 10);
    drawStarM(1.6f, -0.3f, 0.005f, 0.012f, 10);
    drawStarM(-1.7f, 0.7f, 0.006f, 0.015f, 10);
    drawStarM(0.7f, -0.8f, 0.004f, 0.01f, 10);
    drawStarM(-0.2f, 0.9f, 0.007f, 0.018f, 10);
    drawStarM(0.9f, 0.3f, 0.006f, 0.015f, 10);
    drawStarM(-1.5f, -0.6f, 0.005f, 0.012f, 10);
    drawStarM(1.3f, -0.9f, 0.004f, 0.01f, 10);
}
void drawUFOM() {
    glPushMatrix();
    glTranslatef(ufoXM, ufoYM, 0.0f);
    glScalef(0.7f, 0.7f, 0.0f); // Match satellite scale for consistency
    // === Saucer Body (Elliptical) ===
    glColor3f(0.6f, 0.6f, 0.65f); // Metallic gray
    drawEllipseM(0.0f, 0.0f, 0.1f, 0.05f); // Wider horizontally
    // === Glowing Dome (Top) ===
    glColor4f(0.2f, 0.9f, 0.2f, 0.8f); // Green glow with transparency
    drawCircleM(0.0f, 0.03f, 0.04f);
    // === Edge Lights (Red and Blue) ===
    glColor3f(1.0f, 0.2f, 0.2f); // Red
    drawCircleM(-0.08f, 0.0f, 0.01f); // Left
    drawCircleM(0.08f, 0.0f, 0.01f);  // Right
    glColor3f(0.2f, 0.2f, 1.0f); // Blue
    drawCircleM(-0.04f, 0.0f, 0.01f); // Left-middle
    drawCircleM(0.04f, 0.0f, 0.01f);  // Right-middle
    glPopMatrix();
}

void drawMoonCraters() {
    // Larger craters (0.03–0.05, fewer)
    glColor4f(0.75f, 0.75f, 0.78f, 0.95f); drawCircleM(1.5f, 0.65f, 0.04f);  // Upper-left
    glColor4f(0.74f, 0.74f, 0.77f, 0.90f); drawCircleM( 1.7f, 0.68f, 0.035f); // Lower-right
    glColor4f(0.73f, 0.73f, 0.76f, 0.85f); drawCircleM(1.6f, 0.8f, 0.03f);  // Upper-center

    // Medium craters (0.02–0.03)
    glColor4f(0.76f, 0.76f, 0.79f, 0.95f); drawCircleM(1.35f, 0.7f, 0.025f); // Left-lower
    glColor4f(0.75f, 0.75f, 0.78f, 0.90f); drawCircleM( 1.45f, 0.75f, 0.022f); // Right-upper
    glColor4f(0.74f, 0.74f, 0.77f, 0.85f); drawCircleM(1.59f, 0.57f, 0.02f);  // Lower-left

    // Smaller craters (0.01–0.02, more numerous)
    glColor4f(0.77f, 0.77f, 0.80f, 0.95f); drawCircleM(1.69f, 0.7f, 0.015f); // Upper-left
    //glColor4f(0.76f, 0.76f, 0.79f, 0.90f); drawCircleM( 1.3f, 0.87f, 0.012f); // Upper-center
   // glColor4f(0.75f, 0.75f, 0.78f, 0.85f); drawCircleM( 0.15f, 0.40f, 0.01f);  // Right-lower
    glColor4f(0.74f, 0.74f, 0.77f, 0.90f); drawCircleM(1.7f, 0.59f, 0.014f); // Lower-center
}


void drawMoon() {




    //glTranslatef(-0.1f, 0.5f, 0.25f);  // Move to origin relative to Earth
    glPushMatrix();
   // glTranslatef(0.7f,0.8f,0.0f);
   glTranslatef(1.5f, 0.7f,0.0f);
    glRotatef(MoonRotation, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glTranslatef(-1.5f,-0.7f,0.0f); // Move back to original position

    glColor4f(0.8f, 0.8f, 0.8f, 0.95f); // Grayish color for the moon
    drawCircleM(1.5f, 0.7f, 0.25f); // Moon at upper middle with radius 0.25
    drawMoonCraters();
    glPopMatrix();

     // Draw craters on the moon
}

void CreateEarthM() {
    glPushMatrix();

    glTranslatef(-1.7f, -0.8f, 0.0f);
    glRotatef(EarthRotation, 0.0f, 0.0f, 1.0f);
    glTranslatef(1.7f, 0.8f, 0.0f);

    // ===== Earth circle (Ocean - Sky Blue) =====
    glColor4f(0.0f, 0.2f, 0.5f, 0.95f); // Sky blue ocean
    drawCircleM(-1.7f, -0.8f, 0.7f);

    // --- South America (Southwest) ---
    glBegin(GL_POLYGON);
    glColor4f(0.18f, 0.65f, 0.25f, 0.95f); // Tropical Green
    glVertex2f(-1.95f, -0.55f); glVertex2f(-1.88f, -0.48f); glVertex2f(-1.82f, -0.48f);
    glVertex2f(-1.78f, -0.55f); glVertex2f(-1.78f, -0.65f); glVertex2f(-1.85f, -0.72f);
    glVertex2f(-1.92f, -0.68f); glVertex2f(-1.95f, -0.63f); glVertex2f(-1.95f, -0.55f);
    glEnd();

    // --- Africa (Central-East) ---
    glBegin(GL_POLYGON);
    glColor4f(0.60f, 0.80f, 0.20f, 0.95f); // Yellowish Green (Savanna)
    glVertex2f(-1.60f, -0.35f); glVertex2f(-1.55f, -0.30f); glVertex2f(-1.50f, -0.37f);
    glVertex2f(-1.48f, -0.47f); glVertex2f(-1.52f, -0.57f); glVertex2f(-1.58f, -0.58f);
    glVertex2f(-1.63f, -0.50f); glVertex2f(-1.60f, -0.35f);
    glEnd();

    // --- Europe/Asia (Northeast) --- (Adjusted vertices: added -0.2 to x, -0.5 to y)
    glBegin(GL_POLYGON);
    glColor4f(0.34f, 0.65f, 0.32f, 0.95f); // Meadow Green
    glVertex2f(-1.55f, -0.75f); glVertex2f(-1.48f, -0.68f); glVertex2f(-1.42f, -0.70f);
    glVertex2f(-1.38f, -0.77f); glVertex2f(-1.43f, -0.86f); glVertex2f(-1.50f, -0.84f);
    glVertex2f(-1.55f, -0.75f);
    glEnd();

    // --- Australia (Southeast) ---
    glBegin(GL_POLYGON);
    glColor4f(0.85f, 0.65f, 0.40f, 0.95f); // Sandy Brown (desert look)
    glVertex2f(-1.10f, -0.75f); glVertex2f(-1.05f, -0.70f); glVertex2f(-1.03f, -0.73f);
    glVertex2f(-1.05f, -0.78f); glVertex2f(-1.10f, -0.75f);
    glEnd();

    // ===== New Country 1 (Pacific Island, East) ===== (Adjusted vertices: added -0.02 to x, -0.5 to y)
    glBegin(GL_POLYGON);
    glColor4f(0.20f, 0.70f, 0.35f, 0.95f); // Green island
    glVertex2f(-1.42f, -0.60f); glVertex2f(-1.37f, -0.58f); glVertex2f(-1.32f, -0.62f);
    glVertex2f(-1.35f, -0.68f); glVertex2f(-1.40f, -0.65f); glVertex2f(-1.42f, -0.60f);
    glEnd();

    // ===== New Country 2 (Near Africa, Central-West) =====
    glBegin(GL_POLYGON);
    glColor4f(0.50f, 0.75f, 0.25f, 0.95f); // Olive Green
    glVertex2f(-1.75f, -0.25f); glVertex2f(-1.70f, -0.22f); glVertex2f(-1.65f, -0.25f);
    glVertex2f(-1.67f, -0.32f); glVertex2f(-1.73f, -0.30f); glVertex2f(-1.75f, -0.25f);
    glEnd();

    // ===== New Country 3 (South Pole Island, South-Central) =====
    glBegin(GL_POLYGON);
    glColor4f(0.25f, 0.55f, 0.25f, 0.95f); // Dark Green
    glVertex2f(-1.90f, -0.85f); glVertex2f(-1.85f, -0.83f); glVertex2f(-1.80f, -0.87f);
    glVertex2f(-1.83f, -0.92f); glVertex2f(-1.88f, -0.90f); glVertex2f(-1.90f, -0.85f);
    glEnd();

    // ===== New Country 5 (Southeast Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.45f, 0.70f, 0.35f, 0.95f); // Light Green
    glVertex2f(-1.25f, -0.95f); glVertex2f(-1.20f, -0.93f); glVertex2f(-1.15f, -0.97f);
    glVertex2f(-1.18f, -1.02f); glVertex2f(-1.23f, -1.00f); glVertex2f(-1.25f, -0.95f);
    glEnd();

    // ===== New Country 6 (Southwest Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.65f, 0.50f, 0.30f, 0.95f); // Sandy Brown
    glVertex2f(-2.10f, -1.05f); glVertex2f(-2.05f, -1.03f); glVertex2f(-2.00f, -1.07f);
    glVertex2f(-2.03f, -1.12f); glVertex2f(-2.08f, -1.10f); glVertex2f(-2.10f, -1.05f);
    glEnd();

    // ===== New Country 7 (Central-West Landmass) =====
    glBegin(GL_POLYGON);
    glColor4f(0.20f, 0.50f, 0.20f, 0.95f); // Dark Green
    glVertex2f(-2.00f, -0.65f); glVertex2f(-1.95f, -0.63f); glVertex2f(-1.90f, -0.67f);
    glVertex2f(-1.93f, -0.72f); glVertex2f(-1.98f, -0.70f); glVertex2f(-2.00f, -0.65f);
    glEnd();

    // ===== New Country 8 (Central-North Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.55f, 0.65f, 0.25f, 0.95f); // Olive Green
    glVertex2f(-1.65f, -0.20f); glVertex2f(-1.60f, -0.18f); glVertex2f(-1.55f, -0.22f);
    glVertex2f(-1.58f, -0.27f); glVertex2f(-1.63f, -0.25f); glVertex2f(-1.65f, -0.20f);
    glEnd();

    // ===== New Country 9 (Northeast Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.35f, 0.75f, 0.40f, 0.95f); // Bright Green
    glVertex2f(-1.30f, -0.35f); glVertex2f(-1.25f, -0.33f); glVertex2f(-1.20f, -0.37f);
    glVertex2f(-1.23f, -0.42f); glVertex2f(-1.28f, -0.40f); glVertex2f(-1.30f, -0.35f);
    glEnd();

    // ===== New Country 10 (South-Central Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.70f, 0.55f, 0.35f, 0.95f); // Desert Tan
    glVertex2f(-1.65f, -0.95f); glVertex2f(-1.60f, -0.93f); glVertex2f(-1.55f, -0.97f);
    glVertex2f(-1.58f, -1.02f); glVertex2f(-1.63f, -1.00f); glVertex2f(-1.65f, -0.95f);
    glEnd();

    // ===== New Country 11 (North-Central Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.25f, 0.60f, 0.30f, 0.95f); // Moss Green
    glVertex2f(-1.80f, -0.15f); glVertex2f(-1.75f, -0.13f); glVertex2f(-1.70f, -0.17f);
    glVertex2f(-1.73f, -0.22f); glVertex2f(-1.78f, -0.20f); glVertex2f(-1.80f, -0.15f);
    glEnd();

    // ===== New Country 12 (East-Central Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.40f, 0.65f, 0.30f, 0.95f); // Jungle Green
    glVertex2f(-1.35f, -0.65f); glVertex2f(-1.30f, -0.63f); glVertex2f(-1.25f, -0.67f);
    glVertex2f(-1.28f, -0.72f); glVertex2f(-1.33f, -0.70f); glVertex2f(-1.35f, -0.65f);
    glEnd();

    // ===== New Country 13 (West-Central Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.60f, 0.70f, 0.40f, 0.95f); // Light Olive
    glVertex2f(-2.15f, -0.45f); glVertex2f(-2.10f, -0.43f); glVertex2f(-2.05f, -0.47f);
    glVertex2f(-2.08f, -0.52f); glVertex2f(-2.13f, -0.50f); glVertex2f(-2.15f, -0.45f);
    glEnd();

    // ===== New Country 14 (South-Northwest Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.30f, 0.55f, 0.25f, 0.95f); // Deep Green
    glVertex2f(-2.20f, -0.75f); glVertex2f(-2.15f, -0.73f); glVertex2f(-2.10f, -0.77f);
    glVertex2f(-2.13f, -0.82f); glVertex2f(-2.18f, -0.80f); glVertex2f(-2.20f, -0.75f);
    glEnd();

    // ===== New Country 15 (East-North Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.50f, 0.60f, 0.35f, 0.95f); // Earthy Green
    glVertex2f(-1.45f, -0.25f); glVertex2f(-1.40f, -0.23f); glVertex2f(-1.35f, -0.27f);
    glVertex2f(-1.38f, -0.32f); glVertex2f(-1.43f, -0.30f); glVertex2f(-1.45f, -0.25f);
    glEnd();

    // ===== New Country 16 (South-Southwest Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.45f, 0.60f, 0.25f, 0.95f); // Olive Green
    glVertex2f(-2.05f, -0.95f); glVertex2f(-2.00f, -0.93f); glVertex2f(-1.95f, -0.97f);
    glVertex2f(-1.98f, -1.02f); glVertex2f(-2.03f, -1.00f); glVertex2f(-2.05f, -0.95f);
    glEnd();

    // ===== New Country 18 (South-Southeast Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.35f, 0.65f, 0.35f, 0.95f); // Verdant Green
    glVertex2f(-1.40f, -0.85f); glVertex2f(-1.35f, -0.83f); glVertex2f(-1.30f, -0.87f);
    glVertex2f(-1.33f, -0.92f); glVertex2f(-1.38f, -0.90f); glVertex2f(-1.40f, -0.85f);
    glEnd();

    // ===== New Country 19 (Central-South Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.20f, 0.55f, 0.20f, 0.95f); // Dark Green
    glVertex2f(-1.70f, -0.75f); glVertex2f(-1.65f, -0.73f); glVertex2f(-1.60f, -0.77f);
    glVertex2f(-1.63f, -0.82f); glVertex2f(-1.68f, -0.80f); glVertex2f(-1.70f, -0.75f);
    glEnd();

    // ===== New Country 20 (East-South Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.55f, 0.70f, 0.30f, 0.95f); // Light Olive
    glVertex2f(-1.20f, -0.85f); glVertex2f(-1.15f, -0.83f); glVertex2f(-1.10f, -0.87f);
    glVertex2f(-1.13f, -0.92f); glVertex2f(-1.18f, -0.90f); glVertex2f(-1.20f, -0.85f);
    glEnd();

    // ===== New Country 21 (West-South Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.30f, 0.60f, 0.25f, 0.95f); // Moss Green
    glVertex2f(-2.20f, -0.95f); glVertex2f(-2.15f, -0.93f); glVertex2f(-2.10f, -0.97f);
    glVertex2f(-2.13f, -1.02f); glVertex2f(-2.18f, -1.00f); glVertex2f(-2.20f, -0.95f);
    glEnd();

    // ===== New Country 22 (North-Central Island) =====
    glBegin(GL_POLYGON);
    glColor4f(0.65f, 0.50f, 0.30f, 0.95f); // Sandy Brown
    glVertex2f(-1.75f, -0.35f); glVertex2f(-1.70f, -0.33f); glVertex2f(-1.65f, -0.37f);
    glVertex2f(-1.68f, -0.42f); glVertex2f(-1.73f, -0.40f); glVertex2f(-1.75f, -0.35f);
    glEnd();

    glPopMatrix();
}

void drawTriangleM(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}


void drawAsteroid() {
    glColor4f(0.5f, 0.5f, 0.5f, 0.85f); // Grayish color with slight transparency
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); // Global translation if needed

    glBegin(GL_POLYGON);
        glVertex2f(asteroidX + 0.00f, asteroidY + 0.57f);  // Top
        glVertex2f(asteroidX + 0.04f, asteroidY + 0.56f);
        glVertex2f(asteroidX + 0.07f, asteroidY + 0.54f);
        glVertex2f(asteroidX + 0.08f, asteroidY + 0.51f);
        glVertex2f(asteroidX + 0.07f, asteroidY + 0.48f);
        glVertex2f(asteroidX + 0.05f, asteroidY + 0.46f);
        glVertex2f(asteroidX + 0.03f, asteroidY + 0.44f);
        glVertex2f(asteroidX + 0.01f, asteroidY + 0.43f);
        glVertex2f(asteroidX - 0.02f, asteroidY + 0.43f);
        glVertex2f(asteroidX - 0.04f, asteroidY + 0.44f);
        glVertex2f(asteroidX - 0.06f, asteroidY + 0.46f);
        glVertex2f(asteroidX - 0.08f, asteroidY + 0.48f);
        glVertex2f(asteroidX - 0.09f, asteroidY + 0.51f);
        glVertex2f(asteroidX - 0.08f, asteroidY + 0.54f);
        glVertex2f(asteroidX - 0.06f, asteroidY + 0.56f);
        glVertex2f(asteroidX - 0.03f, asteroidY + 0.57f);
        glVertex2f(asteroidX - 0.01f, asteroidY + 0.58f);
        glVertex2f(asteroidX + 0.02f, asteroidY + 0.58f);
        glVertex2f(asteroidX + 0.05f, asteroidY + 0.57f);
        glVertex2f(asteroidX + 0.07f, asteroidY + 0.55f);
        glVertex2f(asteroidX + 0.08f, asteroidY + 0.52f);
        glVertex2f(asteroidX + 0.06f, asteroidY + 0.49f);
        glVertex2f(asteroidX + 0.04f, asteroidY + 0.47f);
        glVertex2f(asteroidX + 0.01f, asteroidY + 0.45f);
    glEnd();

    glPopMatrix();
}

void drawUFOM2() {

    glPushMatrix();
    glTranslatef(ufo2X, ufo2Y, 0.0f);
     glScalef(0.5f, 0.5f, 0.0f);// Slightly larger than first UFO
    // === Triangular Body ===
    glColor3f(0.7f, 0.7f, 0.75f); // Silver, matching satellite aesthetic
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.06f);  // Top point (front of UFO)
    glVertex2f(-0.12f, -0.06f); // Bottom-left (rear)
    glVertex2f(0.12f, -0.06f);  // Bottom-right (rear)
    glEnd();
    // === Cockpit (Glowing Red) ===
    glColor4f(1.0f, 0.2f, 0.2f, 0.7f); // Red with transparency
    drawCircleM(0.0f, 0.0f, 0.03f);
    // === Thrusters (Yellow, Rear) ===
    glColor3f(1.0f, 1.0f, 0.2f); // Bright yellow
    drawCircleM(-0.08f, -0.05f, 0.01f); // Left thruster
    drawCircleM(0.08f, -0.05f, 0.01f);  // Right thruster
    glPopMatrix();
}


void drawComet() {
    glPushMatrix();
    glTranslatef(cometX, cometY, 0.0f);
    glScalef(0.3f, 0.3f, 0.0f); // Smaller scale (reduced from 0.5)
    // === Core (Bright Yellow, Sun-like) ===
    glColor4f(1.0f, 0.2f, 0.2f, 0.7f); // Bright yellow nucleus
    drawCircleM(0.0f, 0.0f, 0.02f);
    // === Coma (Orange-Yellow Glow) ===
    glColor4f(1.0f, 0.8f, 0.0f, 0.7f); // Orange-yellow with transparency
    drawEllipseM(0.0f, 0.0f, 0.06f, 0.03f); // Elliptical, stretched along x
    // === Tail (Orange, Fading, Sun-like) ===
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 0.5f, 0.0f, 0.5f); // Orange at core
    glVertex2f(0.0f, 0.0f); // Center
    for (int i = 0; i <= 20; i++) {
        float t = i / 20.0f;
        float angle = 3.1415926f * (0.0f + 0.5f * t); // 90-degree arc (0° to 90°, rightward)
        float alpha = 0.5f * (1.0f - t); // Fade to transparent
        glColor4f(1.0f, 0.5f, 0.0f, alpha);
        float x = 0.2f * cosf(angle); // Fixed length tail (0.2 units)
        float y = 0.2f * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}

void drawMercury() {
    glPushMatrix();
    glTranslatef(mercuryX, mercuryY, 0.0f);
    glRotatef(mercuryRotation, 0.0f, 0.0f, 1.0f); // Rotate around z-axis like moon
    glScalef(0.7f, 0.7f, 0.0f); // Matches sun size, adjusted for realistic scale
    // === Base Surface (Reddish-Blue) ===
    glColor4f(0.83f, 0.83f, 0.83f, 1.0f); // Reddish-blue surface
    drawCircleM(0.0f, 0.0f, 0.15f);
    // === Large Crater (Polygon, Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    glBegin(GL_POLYGON);
    glVertex2f(0.06f, -0.10f); // Bottom
    glVertex2f(0.08f, -0.08f); // Right
    glVertex2f(0.10f, -0.06f); // Top-right
    glVertex2f(0.08f, -0.04f); // Top
    glVertex2f(0.04f, -0.06f); // Left
    glVertex2f(0.06f, -0.08f); // Bottom-left
    glEnd();
    // === Medium Crater 1 (Triangle, Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.05f, 0.04f);
    glVertex2f(-0.02f, 0.07f);
    glVertex2f(-0.08f, 0.07f);
    glEnd();
    // === Medium Crater 2 (Polygon, Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, -0.03f);
    glVertex2f(0.06f, -0.03f);
    glVertex2f(0.06f, 0.00f);
    glVertex2f(0.03f, 0.00f);
    glEnd();
    // === Ridge 1 (Line, Reddish) ===
    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Reddish
    glBegin(GL_LINES);
    glVertex2f(-0.02f, 0.02f);
    glVertex2f(0.02f, 0.02f);
    glEnd();
    // === Ridge 2 (Line, Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    glBegin(GL_LINES);
    glVertex2f(0.04f, 0.01f);
    glVertex2f(0.08f, 0.03f);
    glEnd();
    // === Patch 1 (Polygon, Light Gray) ===
    glColor4f(0.7f, 0.7f, 0.7f, 1.0f); // Light gray
    glBegin(GL_POLYGON);
    glVertex2f(-0.03f, -0.04f);
    glVertex2f(-0.01f, -0.04f);
    glVertex2f(0.00f, -0.02f);
    glVertex2f(-0.02f, -0.01f);
    glVertex2f(-0.03f, -0.02f);
    glEnd();
    // === Patch 2 (Triangle, Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    glBegin(GL_TRIANGLES);
    glVertex2f(0.05f, 0.03f);
    glVertex2f(0.07f, 0.03f);
    glVertex2f(0.05f, 0.05f);
    glEnd();
    // === Small Ridge (Line, Reddish) ===
    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Reddish
    glBegin(GL_LINES);
    glVertex2f(-0.04f, -0.02f);
    glVertex2f(-0.01f, -0.04f);
    glEnd();
    // === Small Crater (Triangle, Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    glBegin(GL_TRIANGLES);
    glVertex2f(0.01f, -0.01f);
    glVertex2f(0.025f, -0.01f);
    glVertex2f(0.01f, -0.025f);
    glEnd();
    // === Small Crater 3 (Triangle, Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.07f, -0.07f);
    glVertex2f(-0.055f, -0.07f);
    glVertex2f(-0.07f, -0.085f);
    glEnd();
    // === Ridge 3 (Line, Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    glBegin(GL_LINES);
    glVertex2f(0.02f, -0.05f);
    glVertex2f(0.06f, -0.07f);
    glEnd();
    // === Patch 3 (Polygon, Light Gray) ===
    glColor4f(0.7f, 0.7f, 0.7f, 1.0f); // Light gray
    glBegin(GL_POLYGON);
    glVertex2f(0.08f, -0.08f);
    glVertex2f(0.10f, -0.08f);
    glVertex2f(0.10f, -0.06f);
    glVertex2f(0.08f, -0.06f);
    glEnd();
    // === Small Crater 4 (Triangle, Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03f, 0.06f);
    glVertex2f(-0.015f, 0.06f);
    glVertex2f(-0.03f, 0.075f);
    glEnd();
    // === Ridge 4 (Line, Reddish) ===
    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Reddish
    glBegin(GL_LINES);
    glVertex2f(-0.06f, 0.03f);
    glVertex2f(-0.02f, 0.05f);
    glEnd();
    // === Patch 4 (Polygon, Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, 0.07f);
    glVertex2f(0.05f, 0.07f);
    glVertex2f(0.06f, 0.09f);
    glVertex2f(0.04f, 0.09f);
    glVertex2f(0.03f, 0.08f);
    glEnd();
    // === New Circle 1 (Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    drawCircleM(-0.08f, -0.05f, 0.01f);
    // === New Circle 2 (Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    drawCircleM(0.07f, -0.02f, 0.01f);
    // === New Circle 3 (Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    drawCircleM(-0.04f, 0.08f, 0.01f);
    // === New Circle 4 (Reddish) ===
    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Reddish
    drawCircleM(0.09f, 0.04f, 0.01f);
    // === New Circle 5 (Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    drawCircleM(-0.06f, -0.09f, 0.01f);
    // === New Circle 6 (Light Gray) ===
    glColor4f(0.7f, 0.7f, 0.7f, 1.0f); // Light gray
    drawCircleM(0.05f, -0.06f, 0.01f);
    // === New Circle 7 (Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    drawCircleM(-0.01f, 0.09f, 0.01f);
    // === New Circle 8 (Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    drawCircleM(0.02f, -0.08f, 0.01f);
    // === New Circle 9 (Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    drawCircleM(0.08f, 0.06f, 0.01f);
    // === New Circle 10 (Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    drawCircleM(-0.09f, 0.02f, 0.01f);
    // === New Circle 11 (Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    drawCircleM(-0.03f, -0.03f, 0.01f);
    // === New Circle 12 (Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    drawCircleM(0.04f, 0.05f, 0.01f);
    // === New Circle 13 (Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    drawCircleM(-0.07f, 0.03f, 0.01f);
    // === New Circle 14 (Reddish) ===
    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Reddish
    drawCircleM(0.06f, -0.07f, 0.01f);
    // === New Circle 15 (Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    drawCircleM(-0.02f, 0.07f, 0.01f);
    // === New Circle 16 (Light Gray) ===
    glColor4f(0.7f, 0.7f, 0.7f, 1.0f); // Light gray
    drawCircleM(0.03f, -0.09f, 0.01f);
    // === New Circle 17 (Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    drawCircleM(-0.05f, 0.01f, 0.01f);
    // === New Circle 18 (Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    drawCircleM(0.01f, 0.03f, 0.01f);
    // === New Circle 19 (Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    drawCircleM(0.07f, -0.05f, 0.01f);
    // === New Circle 20 (Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    drawCircleM(-0.09f, -0.01f, 0.01f);
    glPopMatrix();
}


void drawMercury2() {
    glPushMatrix();
    glTranslatef(mercury2X, mercury2Y, 0.0f);
    glRotatef(mercury2Rotation, 0.0f, 0.0f, 1.0f); // Rotate around z-axis like moon
    glScalef(0.4f, 0.4f, 0.0f); // Matches sun size, adjusted for realistic scale
    // === Base Surface (Reddish-Blue) ===
    glColor4f(0.75f, 0.60f, 0.35f, 1.0f); // Reddish-blue surface
    drawCircleM(0.0f, 0.0f, 0.15f);
    // === Large Crater (Polygon, Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    glBegin(GL_POLYGON);
    glVertex2f(0.06f, -0.10f); // Bottom
    glVertex2f(0.08f, -0.08f); // Right
    glVertex2f(0.10f, -0.06f); // Top-right
    glVertex2f(0.08f, -0.04f); // Top
    glVertex2f(0.04f, -0.06f); // Left
    glVertex2f(0.06f, -0.08f); // Bottom-left
    glEnd();
    // === Medium Crater 1 (Triangle, Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.05f, 0.04f);
    glVertex2f(-0.02f, 0.07f);
    glVertex2f(-0.08f, 0.07f);
    glEnd();
    // === Medium Crater 2 (Polygon, Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, -0.03f);
    glVertex2f(0.06f, -0.03f);
    glVertex2f(0.06f, 0.00f);
    glVertex2f(0.03f, 0.00f);
    glEnd();
    // === Ridge 1 (Line, Reddish) ===
    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Reddish
    glBegin(GL_LINES);
    glVertex2f(-0.02f, 0.02f);
    glVertex2f(0.02f, 0.02f);
    glEnd();
    // === Ridge 2 (Line, Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    glBegin(GL_LINES);
    glVertex2f(0.04f, 0.01f);
    glVertex2f(0.08f, 0.03f);
    glEnd();
    // === Patch 1 (Polygon, Light Gray) ===
    glColor4f(0.7f, 0.7f, 0.7f, 1.0f); // Light gray
    glBegin(GL_POLYGON);
    glVertex2f(-0.03f, -0.04f);
    glVertex2f(-0.01f, -0.04f);
    glVertex2f(0.00f, -0.02f);
    glVertex2f(-0.02f, -0.01f);
    glVertex2f(-0.03f, -0.02f);
    glEnd();
    // === Patch 2 (Triangle, Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    glBegin(GL_TRIANGLES);
    glVertex2f(0.05f, 0.03f);
    glVertex2f(0.07f, 0.03f);
    glVertex2f(0.05f, 0.05f);
    glEnd();
    // === Small Ridge (Line, Reddish) ===
    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Reddish
    glBegin(GL_LINES);
    glVertex2f(-0.04f, -0.02f);
    glVertex2f(-0.01f, -0.04f);
    glEnd();
    // === Small Crater (Triangle, Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    glBegin(GL_TRIANGLES);
    glVertex2f(0.01f, -0.01f);
    glVertex2f(0.025f, -0.01f);
    glVertex2f(0.01f, -0.025f);
    glEnd();
    // === Small Crater 3 (Triangle, Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.07f, -0.07f);
    glVertex2f(-0.055f, -0.07f);
    glVertex2f(-0.07f, -0.085f);
    glEnd();
    // === Ridge 3 (Line, Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    glBegin(GL_LINES);
    glVertex2f(0.02f, -0.05f);
    glVertex2f(0.06f, -0.07f);
    glEnd();
    // === Patch 3 (Polygon, Light Gray) ===
    glColor4f(0.7f, 0.7f, 0.7f, 1.0f); // Light gray
    glBegin(GL_POLYGON);
    glVertex2f(0.08f, -0.08f);
    glVertex2f(0.10f, -0.08f);
    glVertex2f(0.10f, -0.06f);
    glVertex2f(0.08f, -0.06f);
    glEnd();
    // === Small Crater 4 (Triangle, Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03f, 0.06f);
    glVertex2f(-0.015f, 0.06f);
    glVertex2f(-0.03f, 0.075f);
    glEnd();
    // === Ridge 4 (Line, Reddish) ===
    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Reddish
    glBegin(GL_LINES);
    glVertex2f(-0.06f, 0.03f);
    glVertex2f(-0.02f, 0.05f);
    glEnd();
    // === Patch 4 (Polygon, Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    glBegin(GL_POLYGON);
    glVertex2f(0.03f, 0.07f);
    glVertex2f(0.05f, 0.07f);
    glVertex2f(0.06f, 0.09f);
    glVertex2f(0.04f, 0.09f);
    glVertex2f(0.03f, 0.08f);
    glEnd();
    // === New Circle 1 (Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    drawCircleM(-0.08f, -0.05f, 0.01f);
    // === New Circle 2 (Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    drawCircleM(0.07f, -0.02f, 0.01f);
    // === New Circle 3 (Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    drawCircleM(-0.04f, 0.08f, 0.01f);
    // === New Circle 4 (Reddish) ===
    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Reddish
    drawCircleM(0.09f, 0.04f, 0.01f);
    // === New Circle 5 (Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    drawCircleM(-0.06f, -0.09f, 0.01f);
    // === New Circle 6 (Light Gray) ===
    glColor4f(0.7f, 0.7f, 0.7f, 1.0f); // Light gray
    drawCircleM(0.05f, -0.06f, 0.01f);
    // === New Circle 7 (Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    drawCircleM(-0.01f, 0.09f, 0.01f);
    // === New Circle 8 (Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    drawCircleM(0.02f, -0.08f, 0.01f);
    // === New Circle 9 (Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    drawCircleM(0.08f, 0.06f, 0.01f);
    // === New Circle 10 (Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    drawCircleM(-0.09f, 0.02f, 0.01f);
    // === New Circle 11 (Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    drawCircleM(-0.03f, -0.03f, 0.01f);
    // === New Circle 12 (Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    drawCircleM(0.04f, 0.05f, 0.01f);
    // === New Circle 13 (Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    drawCircleM(-0.07f, 0.03f, 0.01f);
    // === New Circle 14 (Reddish) ===
    glColor4f(1.0f, 0.2f, 0.2f, 1.0f); // Reddish
    drawCircleM(0.06f, -0.07f, 0.01f);
    // === New Circle 15 (Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    drawCircleM(-0.02f, 0.07f, 0.01f);
    // === New Circle 16 (Light Gray) ===
    glColor4f(0.7f, 0.7f, 0.7f, 1.0f); // Light gray
    drawCircleM(0.03f, -0.09f, 0.01f);
    // === New Circle 17 (Blue) ===
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Blue
    drawCircleM(-0.05f, 0.01f, 0.01f);
    // === New Circle 18 (Light Blue) ===
    glColor4f(0.5f, 0.8f, 0.9f, 1.0f); // Light blue
    drawCircleM(0.01f, 0.03f, 0.01f);
    // === New Circle 19 (Dark Blue) ===
    glColor4f(0.1f, 0.4f, 0.6f, 1.0f); // Dark blue
    drawCircleM(0.07f, -0.05f, 0.01f);
    // === New Circle 20 (Cyan) ===
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
    drawCircleM(-0.09f, -0.01f, 0.01f);
    glPopMatrix();
}

void drawVenusM() {
    glPushMatrix();

    // Translation (0.2, 0.65, 0.0) removed; applied directly to coordinates
    //glScalef(0.25f, 0.25f, 0.0f); // Scaling commented out; applied directly to coordinates and radii
    glTranslatef(1.275f * 0.25f + 0.2f, 0.6f * 0.25f + 0.65f, 0.0f);
    glRotatef(venusAngleM, 0.0f, 0.0f, 1.0f);
    glTranslatef(-(1.275f * 0.25f + 0.2f),-( 0.6f * 0.25f + 0.65f), 0.0f);

    // Soft outer glow
    glColor4f(1.0f, 0.6f, 0.2f, 0.05f);
    drawCircleM(1.275f * 0.25f + 0.2f, 0.6f * 0.25f + 0.65f, 0.13f * 0.25f); // Translated: (0.31875+0.2, 0.15+0.65, 0.0325) = (0.51875, 0.8, 0.0325)

    // Core body — slightly darker volcanic tone
    glColor3f(0.75f, 0.55f, 0.28f);
    drawCircleM(1.275f * 0.25f + 0.2f, 0.6f * 0.25f + 0.65f, 0.11f * 0.25f); // Translated: (0.31875+0.2, 0.15+0.65, 0.0275) = (0.51875, 0.8, 0.0275)

    // === Terrain Patches ===

    // 1. Central fracture
    glColor4f(0.8f, 0.5f, 0.3f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(1.25f * 0.25f + 0.2f, 0.615f * 0.25f + 0.65f); // (0.3125+0.2, 0.15375+0.65) = (0.5125, 0.80375)
        glVertex2f(1.275f * 0.25f + 0.2f, 0.625f * 0.25f + 0.65f); // (0.31875+0.2, 0.15625+0.65) = (0.51875, 0.80625)
        glVertex2f(1.3f * 0.25f + 0.2f, 0.62f * 0.25f + 0.65f); // (0.325+0.2, 0.155+0.65) = (0.525, 0.805)
        glVertex2f(1.31f * 0.25f + 0.2f, 0.6f * 0.25f + 0.65f); // (0.3275+0.2, 0.15+0.65) = (0.5275, 0.8)
        glVertex2f(1.3f * 0.25f + 0.2f, 0.58f * 0.25f + 0.65f); // (0.325+0.2, 0.145+0.65) = (0.525, 0.795)
        glVertex2f(1.275f * 0.25f + 0.2f, 0.575f * 0.25f + 0.65f); // (0.31875+0.2, 0.14375+0.65) = (0.51875, 0.79375)
        glVertex2f(1.25f * 0.25f + 0.2f, 0.58f * 0.25f + 0.65f); // (0.3125+0.2, 0.145+0.65) = (0.5125, 0.795)
        glVertex2f(1.24f * 0.25f + 0.2f, 0.6f * 0.25f + 0.65f); // (0.31+0.2, 0.15+0.65) = (0.51, 0.8)
    glEnd();

    // 2. Upper left arc
    glColor4f(0.7f, 0.4f, 0.2f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(1.185f * 0.25f + 0.2f, 0.68f * 0.25f + 0.65f); // (0.29625+0.2, 0.17+0.65) = (0.49625, 0.82)
        glVertex2f(1.205f * 0.25f + 0.2f, 0.69f * 0.25f + 0.65f); // (0.30125+0.2, 0.1725+0.65) = (0.50125, 0.8225)
        glVertex2f(1.225f * 0.25f + 0.2f, 0.685f * 0.25f + 0.65f); // (0.30625+0.2, 0.17125+0.65) = (0.50625, 0.82125)
        glVertex2f(1.245f * 0.25f + 0.2f, 0.68f * 0.25f + 0.65f); // (0.31125+0.2, 0.17+0.65) = (0.51125, 0.82)
        glVertex2f(1.255f * 0.25f + 0.2f, 0.665f * 0.25f + 0.65f); // (0.31375+0.2, 0.16625+0.65) = (0.51375, 0.81625)
        glVertex2f(1.235f * 0.25f + 0.2f, 0.655f * 0.25f + 0.65f); // (0.30875+0.2, 0.16375+0.65) = (0.50875, 0.81375)
        glVertex2f(1.215f * 0.25f + 0.2f, 0.65f * 0.25f + 0.65f); // (0.30375+0.2, 0.1625+0.65) = (0.50375, 0.8125)
        glVertex2f(1.195f * 0.25f + 0.2f, 0.66f * 0.25f + 0.65f); // (0.29875+0.2, 0.165+0.65) = (0.49875, 0.815)
    glEnd();

    // 3. Upper right crater
    glColor4f(0.85f, 0.6f, 0.3f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(1.325f * 0.25f + 0.2f, 0.68f * 0.25f + 0.65f); // (0.33125+0.2, 0.17+0.65) = (0.53125, 0.82)
        glVertex2f(1.345f * 0.25f + 0.2f, 0.69f * 0.25f + 0.65f); // (0.33625+0.2, 0.1725+0.65) = (0.53625, 0.8225)
        glVertex2f(1.365f * 0.25f + 0.2f, 0.68f * 0.25f + 0.65f); // (0.34125+0.2, 0.17+0.65) = (0.54125, 0.82)
        glVertex2f(1.355f * 0.25f + 0.2f, 0.66f * 0.25f + 0.65f); // (0.33875+0.2, 0.165+0.65) = (0.53875, 0.815)
        glVertex2f(1.335f * 0.25f + 0.2f, 0.655f * 0.25f + 0.65f); // (0.33375+0.2, 0.16375+0.65) = (0.53375, 0.81375)
    glEnd();

    // 4. Lower left lava flow
    glColor4f(0.6f, 0.3f, 0.15f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(1.185f * 0.25f + 0.2f, 0.53f * 0.25f + 0.65f); // (0.29625+0.2, 0.1325+0.65) = (0.49625, 0.7825)
        glVertex2f(1.205f * 0.25f + 0.2f, 0.52f * 0.25f + 0.65f); // (0.30125+0.2, 0.13+0.65) = (0.50125, 0.78)
        glVertex2f(1.225f * 0.25f + 0.2f, 0.525f * 0.25f + 0.65f); // (0.30625+0.2, 0.13125+0.65) = (0.50625, 0.78125)
        glVertex2f(1.235f * 0.25f + 0.2f, 0.54f * 0.25f + 0.65f); // (0.30875+0.2, 0.135+0.65) = (0.50875, 0.785)
        glVertex2f(1.215f * 0.25f + 0.2f, 0.55f * 0.25f + 0.65f); // (0.30375+0.2, 0.1375+0.65) = (0.50375, 0.7875)
        glVertex2f(1.195f * 0.25f + 0.2f, 0.545f * 0.25f + 0.65f); // (0.29875+0.2, 0.13625+0.65) = (0.49875, 0.78625)
    glEnd();

    // 5. Lower right arc
    glColor4f(0.65f, 0.4f, 0.2f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(1.305f * 0.25f + 0.2f, 0.55f * 0.25f + 0.65f); // (0.32625+0.2, 0.1375+0.65) = (0.52625, 0.7875)
        glVertex2f(1.325f * 0.25f + 0.2f, 0.56f * 0.25f + 0.65f); // (0.33125+0.2, 0.14+0.65) = (0.53125, 0.79)
        glVertex2f(1.345f * 0.25f + 0.2f, 0.555f * 0.25f + 0.65f); // (0.33625+0.2, 0.13875+0.65) = (0.53625, 0.78875)
        glVertex2f(1.365f * 0.25f + 0.2f, 0.54f * 0.25f + 0.65f); // (0.34125+0.2, 0.135+0.65) = (0.54125, 0.785)
        glVertex2f(1.355f * 0.25f + 0.2f, 0.52f * 0.25f + 0.65f); // (0.33875+0.2, 0.13+0.65) = (0.53875, 0.78)
        glVertex2f(1.335f * 0.25f + 0.2f, 0.515f * 0.25f + 0.65f); // (0.33375+0.2, 0.12875+0.65) = (0.53375, 0.77875)
        glVertex2f(1.315f * 0.25f + 0.2f, 0.525f * 0.25f + 0.65f); // (0.32875+0.2, 0.13125+0.65) = (0.52875, 0.78125)
        glVertex2f(1.295f * 0.25f + 0.2f, 0.535f * 0.25f + 0.65f); // (0.32375+0.2, 0.13375+0.65) = (0.52375, 0.78375)
    glEnd();

    // 6. Bottom ridge
    glColor4f(0.55f, 0.3f, 0.15f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(1.245f * 0.25f + 0.2f, 0.505f * 0.25f + 0.65f); // (0.31125+0.2, 0.12625+0.65) = (0.51125, 0.77625)
        glVertex2f(1.305f * 0.25f + 0.2f, 0.505f * 0.25f + 0.65f); // (0.32625+0.2, 0.12625+0.65) = (0.52625, 0.77625)
        glVertex2f(1.295f * 0.25f + 0.2f, 0.49f * 0.25f + 0.65f); // (0.32375+0.2, 0.1225+0.65) = (0.52375, 0.7725)
        glVertex2f(1.255f * 0.25f + 0.2f, 0.49f * 0.25f + 0.65f); // (0.31375+0.2, 0.1225+0.65) = (0.51375, 0.7725)
        glVertex2f(1.235f * 0.25f + 0.2f, 0.495f * 0.25f + 0.65f); // (0.30875+0.2, 0.12375+0.65) = (0.50875, 0.77375)
    glEnd();

    // 7. Upper center ripple
    glColor4f(0.95f, 0.75f, 0.45f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(1.255f * 0.25f + 0.2f, 0.7f * 0.25f + 0.65f); // (0.31375+0.2, 0.175+0.65) = (0.51375, 0.825)
        glVertex2f(1.275f * 0.25f + 0.2f, 0.71f * 0.25f + 0.65f); // (0.31875+0.2, 0.1775+0.65) = (0.51875, 0.8275)
        glVertex2f(1.295f * 0.25f + 0.2f, 0.7f * 0.25f + 0.65f); // (0.32375+0.2, 0.175+0.65) = (0.52375, 0.825)
        glVertex2f(1.305f * 0.25f + 0.2f, 0.68f * 0.25f + 0.65f); // (0.32625+0.2, 0.17+0.65) = (0.52625, 0.82)
        glVertex2f(1.285f * 0.25f + 0.2f, 0.67f * 0.25f + 0.65f); // (0.32125+0.2, 0.1675+0.65) = (0.52125, 0.8175)
        glVertex2f(1.265f * 0.25f + 0.2f, 0.68f * 0.25f + 0.65f); // (0.31625+0.2, 0.17+0.65) = (0.51625, 0.82)
    glEnd();

    // 8. Left edge streak
    glColor4f(0.6f, 0.4f, 0.2f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(1.165f * 0.25f + 0.2f, 0.63f * 0.25f + 0.65f); // (0.29125+0.2, 0.1575+0.65) = (0.49125, 0.8075)
        glVertex2f(1.185f * 0.25f + 0.2f, 0.64f * 0.25f + 0.65f); // (0.29625+0.2, 0.16+0.65) = (0.49625, 0.81)
        glVertex2f(1.205f * 0.25f + 0.2f, 0.63f * 0.25f + 0.65f); // (0.30125+0.2, 0.1575+0.65) = (0.50125, 0.8075)
        glVertex2f(1.195f * 0.25f + 0.2f, 0.61f * 0.25f + 0.65f); // (0.29875+0.2, 0.1525+0.65) = (0.49875, 0.8025)
        glVertex2f(1.175f * 0.25f + 0.2f, 0.6f * 0.25f + 0.65f); // (0.29375+0.2, 0.15+0.65) = (0.49375, 0.8)
    glEnd();

    // 9. Right edge streak
    glColor4f(0.7f, 0.5f, 0.3f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(1.385f * 0.25f + 0.2f, 0.57f * 0.25f + 0.65f); // (0.34625+0.2, 0.1425+0.65) = (0.54625, 0.7925)
        glVertex2f(1.365f * 0.25f + 0.2f, 0.56f * 0.25f + 0.65f); // (0.34125+0.2, 0.14+0.65) = (0.54125, 0.79)
        glVertex2f(1.345f * 0.25f + 0.2f, 0.57f * 0.25f + 0.65f); // (0.33625+0.2, 0.1425+0.65) = (0.53625, 0.7925)
        glVertex2f(1.355f * 0.25f + 0.2f, 0.59f * 0.25f + 0.65f); // (0.33875+0.2, 0.1475+0.65) = (0.53875, 0.7975)
        glVertex2f(1.375f * 0.25f + 0.2f, 0.6f * 0.25f + 0.65f); // (0.34375+0.2, 0.15+0.65) = (0.54375, 0.8)
    glEnd();

    // 10. Mid-left band
    glColor4f(0.65f, 0.4f, 0.2f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(1.205f * 0.25f + 0.2f, 0.6f * 0.25f + 0.65f); // (0.30125+0.2, 0.15+0.65) = (0.50125, 0.8)
        glVertex2f(1.225f * 0.25f + 0.2f, 0.61f * 0.25f + 0.65f); // (0.30625+0.2, 0.1525+0.65) = (0.50625, 0.8025)
        glVertex2f(1.245f * 0.25f + 0.2f, 0.6f * 0.25f + 0.65f); // (0.31125+0.2, 0.15+0.65) = (0.51125, 0.8)
        glVertex2f(1.235f * 0.25f + 0.2f, 0.585f * 0.25f + 0.65f); // (0.30875+0.2, 0.14625+0.65) = (0.50875, 0.79625)
        glVertex2f(1.215f * 0.25f + 0.2f, 0.58f * 0.25f + 0.65f); // (0.30375+0.2, 0.145+0.65) = (0.50375, 0.795)
    glEnd();

    glPopMatrix();
}


void marium_idle() {
    asteroidX += 0.00031f; // move right
    asteroidY += 0.000009f; // move up slightly
    if(asteroidX > 2.0f) asteroidX = -2.0f; // reset

     MoonRotation+= 0.04f; // Rotate moon slowly
    if (MoonRotation >= 360.0f) MoonRotation-= 360.0f;



     EarthRotation+= 0.01f; // Rotate earth slowly
   if (EarthRotation >= 360.0f) EarthRotation-= 360.0f;


   rayRotationM+= 0.031f; //
   if (rayRotationM >= 360.0f) rayRotationM-= 360.0f;






    satelliteX1 += sat1speed;

if (satelliteX1 > -1.5f || satelliteX1 < -2.0f)
        sat1speed = -sat1speed;


        satelliteX2 += sat2speed;

if (satelliteX2 > -0.70f || satelliteX2 < -0.90f)
        sat2speed = -sat2speed;


        satelliteX3 += sat3speed;

if (satelliteX3 > -0.45f || satelliteX3 < -0.75f)
        sat3speed = -sat3speed;


        ufoXM += 0.000091f; // Same horizontal speed as asteroid
    ufoTime += 0.001f; // Increment time for vertical oscillation
    ufoYM = 0.5f + 0.1f * sin(ufoTime); // Sinusoidal vertical motion
    if (ufoXM > 2.0f) {
        ufoXM = -2.0f; // Reset to left
        ufoTime = 0.0f; // Reset time to keep sine wave consistent
    }

   ufo2X -= 0.00031f; // Move left
    ufo2Y += 0.000031f * 0.35f; // Move up (Δy/Δx = 1.4/4 = 0.35)
    ufo2Time += 0.01f; // Increment time for vertical oscillation
    ufo2Y = ufo2Y + 0.00000099f * sin(ufo2Time); // Add sinusoidal vertical motion
    if (ufo2X < -2.0f) {
        ufo2X = 2.0f; // Reset to right
        ufo2Y = -0.07f; // Reset to lower corner
        ufo2Time = 0.0f; // Reset time to keep sine wave consistent
    }

     cometX -= 0.0002f; // Move left, slower speed
    if (cometX < -2.0f) {
        cometX = 2.0f; // Reset to right edge
        cometY = 0.9f; // Constant y near moon, above Earth
    }

    mercuryRotation += 0.04f; // Same speed as moon
    if (mercuryRotation >= 360.0f) mercuryRotation -= 360.0f;

    mercury2Rotation += 0.04f; // Same speed as moon
    if (mercury2Rotation >= 360.0f) mercury2Rotation -= 360.0f;


    blackHole1Angle += 0.02f;
    blackHole1X = -1.0f + 0.5f * cos(blackHole1Angle);
    blackHole1Y = 0.0f + 0.3f * sin(blackHole1Angle);
    // Black hole 2 sinusoidal vertical motion with leftward drift
    blackHole2Time += 0.01f;
    blackHole2X -= 0.0002f;
    blackHole2Y = -0.6f + 0.4f * sin(blackHole2Time);
    if (blackHole2X < -2.0f) blackHole2X = 2.0f;
    // Black hole 3 circular orbit around (1.0, 0.0)
    blackHole3Angle += 0.015f;
    blackHole3X = 1.0f + 0.4f * cos(blackHole3Angle);
    blackHole3Y = 0.0f + 0.4f * sin(blackHole3Angle);

    venusAngleM += 0.05f; // Adjust speed as needed
    if (venusAngleM > 360.0f) venusAngleM -= 360.0f;

    glutPostRedisplay();
}
void drawQuadM(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}
void drawSatellite1() {


    glPushMatrix();

    glTranslatef(satelliteX1, satelliteY1, 0.0f);
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.7f, 0.7f, 0.0f);

    // === Hexagonal Chassis Body ===
    glColor3f(0.25f, 0.25f, 0.3f); // dark grey-blue body
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, -0.08f);
        glVertex2f( 0.04f, -0.08f);
        glVertex2f( 0.06f, -0.04f);
        glVertex2f( 0.04f,  0.08f);
        glVertex2f(-0.04f,  0.08f);
        glVertex2f(-0.06f, -0.04f);
    glEnd();

    // === Golden Edge Stripes ===
    glColor3f(0.85f, 0.65f, 0.2f);
    drawQuadM(-0.06f, -0.04f, 0.06f, -0.04f,
              0.05f, -0.035f, -0.05f, -0.035f);
    drawQuadM(-0.05f, 0.035f, 0.05f, 0.035f,
              0.06f, 0.04f, -0.06f, 0.04f);

    // === Small Sensor Windows (Blue) ===
    glColor3f(0.2f, 0.6f, 0.9f);
    drawCircleM(0.0f, 0.00f, 0.01f);
    drawCircleM(0.0f, 0.05f, 0.01f);
    drawCircleM(0.0f,-0.05f, 0.01f);

    // === Antenna Dish (Top Right) ===
    glPushMatrix();
    glTranslatef(0.08f, 0.08f, 0.0f);
    glColor3f(0.95f, 0.95f, 0.95f);
    drawCircleM(0.0f, 0.0f, 0.025f);
    glColor3f(0.3f, 0.3f, 0.3f);
    drawTriangleM(0.0f, 0.0f,
                 -0.015f, 0.02f,
                  0.015f, 0.02f);
    glPopMatrix();

    // === Panel Support Arms ===
    glColor3f(0.6f, 0.6f, 0.6f);
    drawQuadM(-0.06f, -0.005f, -0.06f, 0.005f,
             -0.10f, 0.005f, -0.10f, -0.005f);
    drawQuadM( 0.06f, -0.005f,  0.06f, 0.005f,
              0.10f, 0.005f,  0.10f, -0.005f);

    // === Solar Panels (New Colors: Dark Navy) ===
    glColor3f(0.05f, 0.1f, 0.4f);
    drawQuadM(-0.20f, -0.05f, -0.10f, -0.05f,
             -0.10f,  0.05f, -0.20f,  0.05f);
    drawQuadM( 0.10f, -0.05f,  0.20f, -0.05f,
              0.20f,  0.05f,  0.10f,  0.05f);

    // === Solar Panel Tiles (Light Green Stripes) ===
    glColor3f(0.3f, 0.8f, 0.4f);
    drawQuadM(-0.19f, -0.045f, -0.17f, -0.045f, -0.17f, 0.045f, -0.19f, 0.045f);
    drawQuadM(-0.15f, -0.045f, -0.13f, -0.045f, -0.13f, 0.045f, -0.15f, 0.045f);
    drawQuadM( 0.13f, -0.045f,  0.15f, -0.045f,  0.15f, 0.045f,  0.13f, 0.045f);
    drawQuadM( 0.17f, -0.045f,  0.19f, -0.045f,  0.19f, 0.045f,  0.17f, 0.045f);

    glPopMatrix();
}


void drawSatellite2() {

    glPushMatrix();
    glTranslatef(satelliteX2, satelliteY2, 0.0f);

    glRotatef(-150.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.7f, 0.7f, 0.0f);

    // === Main Rectangular Body ===
    glColor3f(0.7f, 0.7f, 0.75f); // silver-grey
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, -0.06f);
        glVertex2f( 0.05f, -0.06f);
        glVertex2f( 0.05f,  0.06f);
        glVertex2f(-0.05f,  0.06f);
    glEnd();

    // === Golden trim on top & bottom ===
    glColor3f(0.85f, 0.65f, 0.2f);
    drawQuadM(-0.05f, 0.055f, 0.05f, 0.055f,
              0.05f, 0.06f, -0.05f, 0.06f);
    drawQuadM(-0.05f,-0.055f, 0.05f,-0.055f,
              0.05f,-0.06f, -0.05f,-0.06f);

    // === Sensor Lens (red, center) ===
    glColor3f(0.9f, 0.2f, 0.2f);
    drawCircleM(0.0f, 0.0f, 0.015f);

    // === Small Windows (cyan) ===
    glColor3f(0.1f, 0.7f, 0.9f);
    drawCircleM(0.0f,  0.035f, 0.01f);
    drawCircleM(0.0f, -0.035f, 0.01f);

    // === Solar Panel Left ===
    glColor3f(0.15f, 0.3f, 0.7f); // dark blue panel
    glBegin(GL_QUADS);
        glVertex2f(-0.18f, -0.04f);
        glVertex2f(-0.05f, -0.04f);
        glVertex2f(-0.05f,  0.04f);
        glVertex2f(-0.18f,  0.04f);
    glEnd();

    // grid lines on left panel
    glColor3f(0.8f, 0.8f, 0.9f);
    glBegin(GL_LINES);
        glVertex2f(-0.165f,-0.04f); glVertex2f(-0.165f,0.04f);
        glVertex2f(-0.14f,-0.04f);  glVertex2f(-0.14f,0.04f);
        glVertex2f(-0.115f,-0.04f); glVertex2f(-0.115f,0.04f);
        glVertex2f(-0.09f,-0.04f);  glVertex2f(-0.09f,0.04f);
    glEnd();

    // === Solar Panel Right ===
    glColor3f(0.15f, 0.3f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(0.05f, -0.04f);
        glVertex2f(0.18f, -0.04f);
        glVertex2f(0.18f,  0.04f);
        glVertex2f(0.05f,  0.04f);
    glEnd();

    // grid lines on right panel
    glColor3f(0.8f, 0.8f, 0.9f);
    glBegin(GL_LINES);
        glVertex2f(0.065f,-0.04f); glVertex2f(0.065f,0.04f);
        glVertex2f(0.09f,-0.04f);  glVertex2f(0.09f,0.04f);
        glVertex2f(0.115f,-0.04f); glVertex2f(0.115f,0.04f);
        glVertex2f(0.14f,-0.04f);  glVertex2f(0.14f,0.04f);
    glEnd();

    // === Antenna Dish (Bottom Center) ===
    glPushMatrix();
    glTranslatef(0.0f, -0.09f, 0.0f);
    glColor3f(0.95f, 0.95f, 0.95f);
    drawCircleM(0.0f, 0.0f, 0.025f);

    // antenna stick
    glColor3f(0.35f, 0.35f, 0.35f);
    drawTriangleM(0.0f, 0.0f,
                 -0.015f, 0.03f,
                  0.015f, 0.03f);
    glPopMatrix();

    glPopMatrix();
}
void drawSatellite3() {

    glPushMatrix();
    glTranslatef(satelliteX3, satelliteY3, 0.0f);
     glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.7f, 0.7f, 0.0f);


    // === Cylindrical Chassis (Vertical) ===
    glColor3f(0.25f, 0.25f, 0.3f); // dark grey
    glBegin(GL_POLYGON);
        for (int i = 0; i <= 50; i++) {
            float angle = 2.0f * 3.1416f * i / 50;
            float x = 0.04f * cos(angle);
            float y = 0.08f * sin(angle);
            glVertex2f(x, y);
        }
    glEnd();

    // === Golden Top Sensor (Circle) ===
    glColor3f(0.85f, 0.65f, 0.2f);
    drawCircleM(0.0f, 0.07f, 0.015f);

    // === Teal Windows (Vertical) ===
    glColor3f(0.1f, 0.8f, 0.7f);
    drawCircleM(0.0f,  0.03f, 0.01f);
    drawCircleM(0.0f, -0.03f, 0.01f);

    // === Left Solar Wing (angled) ===
    glColor3f(0.12f, 0.35f, 0.7f); // teal-blue
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.02f);
        glVertex2f(-0.04f, -0.04f);
        glVertex2f(-0.04f,  0.04f);
        glVertex2f(-0.15f,  0.02f);
    glEnd();

    // grid lines left panel
    glColor3f(0.85f, 0.85f, 0.9f);
    glBegin(GL_LINES);
        glVertex2f(-0.13f, -0.015f); glVertex2f(-0.13f, 0.015f);
        glVertex2f(-0.10f, -0.02f);  glVertex2f(-0.10f, 0.02f);
        glVertex2f(-0.07f, -0.03f);  glVertex2f(-0.07f, 0.03f);
    glEnd();

    // === Right Solar Wing (angled) ===
    glColor3f(0.12f, 0.35f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(0.04f, -0.04f);
        glVertex2f(0.15f, -0.02f);
        glVertex2f(0.15f,  0.02f);
        glVertex2f(0.04f,  0.04f);
    glEnd();

    // grid lines right panel
    glColor3f(0.85f, 0.85f, 0.9f);
    glBegin(GL_LINES);
        glVertex2f(0.07f, -0.03f); glVertex2f(0.07f, 0.03f);
        glVertex2f(0.10f, -0.02f); glVertex2f(0.10f, 0.02f);
        glVertex2f(0.13f, -0.015f); glVertex2f(0.13f, 0.015f);
    glEnd();

    // === Antenna Dish (Top Left) ===
    glPushMatrix();
    glTranslatef(-0.06f, 0.09f, 0.0f);
    glColor3f(0.95f, 0.95f, 0.9f);
    drawCircleM(0.0f, 0.0f, 0.025f);

    // antenna stick
    glColor3f(0.4f, 0.4f, 0.4f);
    drawTriangleM(0.0f, 0.0f,
                 -0.015f, -0.03f,
                  0.015f, -0.03f);
    glPopMatrix();

    glPopMatrix();
}


void drawSunVariant2() {

    float cx = -1.6f, cy = 0.8f;

    float outerGlow = 0.13f;
    float midGlow   = 0.09f;
    float innerGlow = 0.05f;
    float core      = 0.03f;

    // Outer glow (soft orange)
    glColor4f(1.0f, 0.6f, 0.15f, 0.15f);
    drawCircleM(cx, cy, outerGlow);

    // Mid glow
    glColor4f(1.0f, 0.8f, 0.05f, 0.3f);
    drawCircleM(cx, cy, midGlow);

    // Inner glow
    glColor4f(1.0f, 0.9f, 0.2f, 0.5f);
    drawCircleM(cx, cy, innerGlow);

    // Core (bright yellow)
    glColor3f(1.0f, 0.95f, 0.3f);
    drawCircleM(cx, cy, core);

    // 🔆 Dynamic Wavy Rays
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glRotatef(rayRotationM, 0.0f, 0.0f, 1.0f);

    int rays = 24;             // more rays
    float rayInner = 0.12f;
    float rayOuter = 0.20f;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < rays; i++) {
        float angle = 2.0f * 3.1415926f * i / rays;

        // More wavy, varying length
        float wave = 0.015f * sin(7.0f * angle + rayRotationM * 0.2f);

        float x1 = rayInner * cos(angle - 0.02f);
        float y1 = rayInner * sin(angle - 0.02f);

        float x2 = rayInner * cos(angle + 0.02f);
        float y2 = rayInner * sin(angle + 0.02f);

        float x3 = (rayOuter + wave) * cos(angle);
        float y3 = (rayOuter + wave) * sin(angle);

        // alternating gradient color
        if (i % 2 == 0) glColor3f(1.0f, 0.85f, 0.0f);
        else glColor3f(1.0f, 0.75f, 0.0f);

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    }
    glEnd();

    glPopMatrix();
}



void drawLowerStageM(float stageY) {
    // =========================
    // COLORS
    // =========================
    const GLfloat bodyR = 0.92f, bodyG = 0.94f, bodyB = 0.98f;   // Light silver body
    const GLfloat finR  = 0.80f, finG  = 0.15f, finB  = 0.15f;   // Red fins
    const GLfloat rimR  = 0.95f, rimG  = 0.95f, rimB  = 0.98f;   // Silver window rim
    const GLfloat glassR= 0.30f, glassG= 0.70f, glassB= 0.90f;   // Blue window glass
    const GLfloat darkR = 0.12f, darkG = 0.12f, darkB = 0.12f;   // Dark gray nozzle/fins shadow
    const GLfloat accentR = 0.90f, accentG = 0.60f, accentB = 0.10f; // Orange accent

    glTranslatef(rocketLowerX ,rocketLowerY , 0.0f);
    glRotatef(rocketlowerangle, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
     glScalef(rocketlowerscale, rocketlowerscale , 1.0f);

    glPushMatrix();
    glScalef(0.6f, 0.6f, 0.0f);
    glTranslatef(-1.8f, stageY, 0.0f);

    // Lower body (tapered quad)
    glColor3f(bodyR, bodyG, bodyB);
    glBegin(GL_QUADS);
        glVertex2f(-0.20f, -0.65f);
        glVertex2f( 0.20f, -0.65f);
        glVertex2f( 0.173f,  0.0f);
        glVertex2f(-0.173f,  0.0f);
    glEnd();

    // Lower center metallic sheen
    glColor3f(0.98f, 0.98f, 1.00f);
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, -0.60f);
        glVertex2f( 0.03f, -0.60f);
        glVertex2f( 0.03f,   0.0f);
        glVertex2f(-0.03f,   0.0f);
    glEnd();

    // Lower left side shading
    glColor3f(0.85f, 0.87f, 0.92f);
    glBegin(GL_QUADS);
        glVertex2f(-0.20f, -0.60f);
        glVertex2f(-0.18f, -0.60f);
        glVertex2f(-0.158f,  0.0f);
        glVertex2f(-0.178f,  0.0f);
    glEnd();

    // Lower right side shading
    glBegin(GL_QUADS);
        glVertex2f( 0.18f, -0.60f);
        glVertex2f( 0.20f, -0.60f);
        glVertex2f( 0.178f,  0.0f);
        glVertex2f( 0.158f,  0.0f);
    glEnd();

    // Lower decorative orange band
    glColor3f(accentR, accentG, accentB);
    glBegin(GL_QUADS);
        glVertex2f(-0.18f, -0.10f);
        glVertex2f( 0.18f, -0.10f);
        glVertex2f( 0.18f, -0.06f);
        glVertex2f(-0.18f, -0.06f);
    glEnd();

    // Lower window
    glColor3f(rimR, rimG, rimB);
    drawCircleM(0.0f, -0.05f, 0.08f); // Rim
    glColor3f(glassR, glassG, glassB);
    drawCircleM(0.0f, -0.05f, 0.06f); // Glass

    // SIDE FINS (curved + layered)
    glColor3f(darkR, darkG, darkB);
    glBegin(GL_POLYGON); // Left shadow fin
        glVertex2f(-0.20f, -0.20f);
        glVertex2f(-0.55f, -0.65f);
        glVertex2f(-0.45f, -0.70f);
        glVertex2f(-0.20f, -0.65f);
    glEnd();
    glBegin(GL_POLYGON); // Right shadow fin
        glVertex2f( 0.20f, -0.20f);
        glVertex2f( 0.55f, -0.65f);
        glVertex2f( 0.45f, -0.70f);
        glVertex2f( 0.20f, -0.65f);
    glEnd();

    glColor3f(finR, finG, finB);
    glBegin(GL_POLYGON); // Left red fin
        glVertex2f(-0.20f, -0.25f);
        glVertex2f(-0.50f, -0.65f);
        glVertex2f(-0.40f, -0.68f);
        glVertex2f(-0.20f, -0.64f);
    glEnd();
    glBegin(GL_POLYGON); // Right red fin
        glVertex2f( 0.20f, -0.25f);
        glVertex2f( 0.50f, -0.65f);
        glVertex2f( 0.40f, -0.68f);
        glVertex2f( 0.20f, -0.64f);
    glEnd();

    // NOZZLE (flared + detailed)
    glColor3f(darkR, darkG, darkB);
    glBegin(GL_POLYGON);
        glVertex2f(-0.18f, -0.65f);
        glVertex2f( 0.18f, -0.65f);
        glVertex2f( 0.22f, -0.85f);
        glVertex2f(-0.22f, -0.85f);
    glEnd();
    glColor3f(0.25f, 0.25f, 0.25f);
    drawEllipseM(0.0f, -0.85f, 0.22f, 0.05f); // Nozzle rim


    if(lowerflamebool){
    // FLAME (animated three-layer)
    glColor3f(1.00f, 0.55f, 0.00f); // Orange outer flame
    glBegin(GL_POLYGON);
        glVertex2f(-0.18f, -0.85f);                          // base left
        glVertex2f( 0.18f, -0.85f);                          // base right
        glVertex2f( 0.12f, -1.00f + lowerFlameOffsetM);       // tip
        glVertex2f( 0.06f, -1.10f + lowerFlameOffsetM);
        glVertex2f( 0.00f, -1.05f + lowerFlameOffsetM);
        glVertex2f(-0.06f, -1.10f + lowerFlameOffsetM);
        glVertex2f(-0.12f, -1.00f + lowerFlameOffsetM);
    glEnd();

    glColor3f(1.00f, 0.90f, 0.20f); // Yellow middle flame
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.10f, -0.85f);
        glVertex2f( 0.10f, -0.85f);
        glVertex2f( 0.00f, -1.05f + lowerFlameOffsetM);
    glEnd();

    glColor3f(1.00f, 0.98f, 0.95f); // White core flame
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, -0.85f);
        glVertex2f( 0.04f, -0.85f);
        glVertex2f( 0.03f, -0.95f + lowerFlameOffsetM);
        glVertex2f( 0.00f, -1.00f + lowerFlameOffsetM);
        glVertex2f(-0.03f, -0.95f + lowerFlameOffsetM);
    glEnd();
    }


    glPopMatrix();
}


void upperRocketFlameM()
{

// Outer flame (orange)
glColor3f(1.00f, 0.55f, 0.00f);
glBegin(GL_POLYGON);
    glVertex2f(-0.12f, -0.14f);                     // base left (new nozzle height)
    glVertex2f( 0.12f, -0.14f);                     // base right
    glVertex2f( 0.08f, -0.29f + upperFlameOffsetM);  // tip
    glVertex2f( 0.04f, -0.39f + upperFlameOffsetM);
    glVertex2f( 0.00f, -0.34f + upperFlameOffsetM);
    glVertex2f(-0.04f, -0.39f + upperFlameOffsetM);
    glVertex2f(-0.08f, -0.29f + upperFlameOffsetM);
glEnd();

// Middle flame (yellow)
glColor3f(1.00f, 0.90f, 0.20f);
glBegin(GL_TRIANGLES);
    glVertex2f(-0.08f, -0.14f);
    glVertex2f( 0.08f, -0.14f);
    glVertex2f( 0.00f, -0.34f + upperFlameOffsetM);
glEnd();

// Core flame (white)
glColor3f(1.00f, 0.98f, 0.95f);
glBegin(GL_POLYGON);
    glVertex2f(-0.03f, -0.14f);
    glVertex2f( 0.03f, -0.14f);
    glVertex2f( 0.02f, -0.24f + upperFlameOffsetM);
    glVertex2f( 0.00f, -0.29f + upperFlameOffsetM);
    glVertex2f(-0.02f, -0.24f + upperFlameOffsetM);
glEnd();


}


void drawUpperStageM(float stageY) {
    const GLfloat bodyR = 0.92f, bodyG = 0.94f, bodyB = 0.98f;
    const GLfloat noseR = 0.88f, noseG = 0.15f, noseB = 0.15f;
    const GLfloat finR  = 0.80f, finG  = 0.15f, finB  = 0.15f;
    const GLfloat rimR  = 0.95f, rimG  = 0.95f, rimB  = 0.98f;
    const GLfloat glassR= 0.30f, glassG= 0.70f, glassB= 0.90f;
    const GLfloat darkR = 0.12f, darkG = 0.12f, darkB = 0.12f;
    const GLfloat accentR = 0.90f, accentG = 0.60f, accentB = 0.10f;

    glPushMatrix();
    glScalef(0.6f, 0.6f, 0.0f);
    glTranslatef(-1.8f, stageY, 0.0f);

    // Main body
    glColor3f(bodyR, bodyG, bodyB);
    drawQuadM(-0.173f, 0.0f, 0.173f, 0.0f, 0.14f, 0.75f, -0.14f, 0.75f);

    // Sheen and shading
    glColor3f(0.98f, 0.98f, 1.00f);
    drawQuadM(-0.03f, 0.0f, 0.03f, 0.0f, 0.03f, 0.70f, -0.03f, 0.70f);

    glColor3f(0.85f, 0.87f, 0.92f);
    drawQuadM(-0.178f, 0.0f, -0.158f, 0.0f, -0.12f, 0.70f, -0.15f, 0.70f);
    drawQuadM(0.158f, 0.0f, 0.178f, 0.0f, 0.15f, 0.70f, 0.12f, 0.70f);

    // Orange bands
    glColor3f(accentR, accentG, accentB);
    drawQuadM(-0.17f, 0.10f, 0.17f, 0.10f, 0.17f, 0.14f, -0.17f, 0.14f);
    drawQuadM(-0.17f, 0.30f, 0.17f, 0.30f, 0.17f, 0.34f, -0.17f, 0.34f);
    drawQuadM(-0.17f, 0.50f, 0.17f, 0.50f, 0.17f, 0.54f, -0.17f, 0.54f);
    drawQuadM(-0.17f, 0.65f, 0.17f, 0.65f, 0.17f, 0.69f, -0.17f, 0.69f);

    // Windows
    glColor3f(rimR, rimG, rimB);
    drawCircleM(0.0f, 0.20f, 0.09f);
    drawCircleM(0.0f, 0.45f, 0.04f);
    drawCircleM(0.0f, 0.60f, 0.06f);
    glColor3f(glassR, glassG, glassB);
    drawCircleM(0.0f, 0.20f, 0.07f);
    drawCircleM(0.0f, 0.45f, 0.02f);
    drawCircleM(0.0f, 0.60f, 0.04f);

    // RCS thrusters
    glColor3f(darkR, darkG, darkB);
    drawCircleM(-0.16f, 0.05f, 0.012f);
    drawCircleM( 0.16f, 0.05f, 0.012f);
    drawCircleM(-0.16f, 0.40f, 0.012f);
    drawCircleM( 0.16f, 0.40f, 0.012f);
    drawCircleM(-0.16f, 0.65f, 0.012f);
    drawCircleM( 0.16f, 0.65f, 0.012f);


   // === Upper Stage Fins (side-mounted, slightly bigger, properly offset) ===

// Left shadow fin
glColor3f(darkR, darkG, darkB);
glBegin(GL_TRIANGLES);
    glVertex2f(-0.16f, 0.26f);   // top attach (shifted left from -0.14f)
    glVertex2f(-0.16f, 0.00f);   // bottom attach
    glVertex2f(-0.36f, -0.04f);  // outward tip
glEnd();

// Right shadow fin
glBegin(GL_TRIANGLES);
    glVertex2f( 0.16f, 0.26f);   // top attach (shifted right from 0.14f)
    glVertex2f( 0.16f, 0.00f);   // bottom attach
    glVertex2f( 0.36f, -0.04f);  // outward tip
glEnd();

// Left red fin
glColor3f(finR, finG, finB);
glBegin(GL_TRIANGLES);
    glVertex2f(-0.16f, 0.25f);   // top attach
    glVertex2f(-0.16f, 0.01f);   // bottom attach
    glVertex2f(-0.32f, -0.03f);  // outward tip
glEnd();

// Right red fin
glBegin(GL_TRIANGLES);
    glVertex2f( 0.16f, 0.25f);   // top attach
    glVertex2f( 0.16f, 0.01f);   // bottom attach
    glVertex2f( 0.32f, -0.03f);  // outward tip
glEnd();



// === Upper Stage Nozzle (smaller, flared) ===
glColor3f(darkR, darkG, darkB);
glBegin(GL_POLYGON);
    glVertex2f(-0.09f, 0.00f);   // base left (narrower)
    glVertex2f( 0.09f, 0.00f);   // base right
    glVertex2f( 0.11f, -0.14f);  // bottom right (shorter)
    glVertex2f(-0.11f, -0.14f);  // bottom left
glEnd();

// Nozzle rim
glColor3f(0.25f, 0.25f, 0.25f);
drawEllipseM(0.0f, -0.14f, 0.11f, 0.03f); // Smaller rim


    // Rocket fire
   if (rocketYM > -1.40f)
   {
       upperRocketFlameM();
   }

 // Docking port
    glColor3f(0.3f, 0.3f, 0.3f);
    drawQuadM(-0.03f, 0.75f, 0.03f, 0.75f, 0.03f, 0.85f, -0.03f, 0.85f);
    glColor3f(0.8f, 0.8f, 0.8f);
    drawCircleM(0.0f, 0.87f, 0.008f);

    // Nose cone
    glColor3f(noseR, noseG, noseB);
    drawTriangleM(-0.14f, 0.75f, 0.14f, 0.75f, 0.00f, 1.05f);

    glPopMatrix();
}


void drawRocketM() {
    glPushMatrix();
    //glRotatef(-65, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis

    glTranslatef(-2.0f,-1.3f, 0.0f);
  //  glScalef(0.65f, 0.65f, 1.0f);
    glRotatef(-57+rocketangle, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glTranslatef(rocketFlx,rocketFly,0.0f);
    glScalef(0.65f, 0.65f , 1.0f);
   glScalef(rocketscale,rocketscale, 1.0f);





    drawUpperStageM(rocketYM);
    drawLowerStageM(rocketYM);
    glPopMatrix();

}

void drawBlackHole() {
    // Black hole 1 (elliptical orbit)
    glPushMatrix();
    glTranslatef(blackHole1X, blackHole1Y, 0.0f);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // Black
    drawCircleM(0.0f, 0.0f, 0.1f);
    glPopMatrix();
    // Black hole 2 (sinusoidal vertical with drift)
    glPushMatrix();
    glTranslatef(blackHole2X, blackHole2Y, 0.0f);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // Black
    drawCircleM(0.0f, 0.0f, 0.1f);
    glPopMatrix();
    // Black hole 3 (circular orbit)
    glPushMatrix();
    glTranslatef(blackHole3X, blackHole3Y, 0.0f);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // Black
    drawCircleM(0.0f, 0.0f, 0.1f);
    glPopMatrix();
}






void displaymarium() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 0.1f);

     displaystarM();
      drawBlackHole();
     drawSatellite3();


     CreateEarthM();
          drawRocketM();
     drawMoon();
   //displaystarM();
     drawAsteroid();
//   drawCometStatic();
    drawSatellite1();
    drawSatellite2();

    drawSunVariant2() ;
    drawUFOM();
    drawUFOM2();
    drawComet();
    drawMercury();
    drawMercury2();
    drawVenusM();



    glutSwapBuffers();
}



 void updateM(int value)
 {
     rocketFlx += 0.00001;
        rocketFly += 0.006;



        if (flameUpM) {
    upperFlameOffsetM += 0.004f;
    if (upperFlameOffsetM > 0.015f) flameUpM = false;
} else {
    upperFlameOffsetM -= 0.004f;
    if (upperFlameOffsetM < -0.015f) flameUpM = true;
}
    //lower flame
    if (lowerFlameUpM) {
    lowerFlameOffsetM += 0.004f;
    if (lowerFlameOffsetM > 0.015f) lowerFlameUpM = false;
} else {
    lowerFlameOffsetM -= 0.004f;
    if (lowerFlameOffsetM < -0.015f) lowerFlameUpM = true;
}


       // earth to moon angle
        rocketangle += -0.01000;

        if (rocketscale >= 0.00f)  rocketscale -= 0.001431f;




        //Lower part separate
        if(rocketFly>0.5f)
        {
            rocketLowerX -= 0.006f;

            rocketLowerY += 0.00f;

            rocketlowerangle += 0.003f;

           lowerflamebool = false ;


        }

        if(rocketFly>0.8 && rocketlowerscale>0)
        {
            rocketlowerscale -= 0.0035;
        }


          glutPostRedisplay();
    glutTimerFunc(16, updateM, 0);
 }



//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

float ufoX = -4.2f;
float ufoSpeed = 0.0009f;
float ufoscale = 1.4f;



float rayRotation = 0.0f;
float  earthRotation = 0.0f;


// Asteroid 1: from left-bottom
float asteroid1X = -2.8f, asteroid1Y = -1.3f;
float asteroid1SpeedX = 0.003f, asteroid1SpeedY = 0.0015f;

// Asteroid 2: from right-top
float asteroid2X = 2.8f, asteroid2Y = 1.9f;
float asteroid2SpeedX = -0.003f, asteroid2SpeedY = -0.0002f;

// Asteroid 3: from left-top
float asteroid3X = -1.9f, asteroid3Y = 0.7f;
float asteroid3SpeedX = 0.005f, asteroid3SpeedY = -0.001f;

// Asteroid 4: from right-bottom
float asteroid4X = 1.8f, asteroid4Y = -0.6f;
float asteroid4SpeedX = -0.004f, asteroid4SpeedY = 0.003f;



// Sattelite
float satelliteX = -1.40f;
float satelliteY = 0.8f;
float satelliteSpeed = 0.0002f;


float rocketY = 2.6f;       // Starting Y position
float rocketSpeed = -0.0009f; // Downward speed
float upperFlameOffset = 0.0f;  //Upper rocket flame
bool flameUp = true;
float lowerFlameOffset = 0.0f;
bool lowerFlameUp = true;
float stairLength = 0.0f;//stairs
bool stairDeploying = false;



// Scout (robot) translation for animation
float scoutX = 0.0f;
float scoutY = 0.0f;
float scoutSpeedX = 0.0006f; // adjust speed as needed
float scoutSpeedY = 0.0000f; // set nonzero if you want vertical motion
bool  scoutbool= false;
float scoutangle=0.0f;


//flag
float flagX;
float flagY;


//Monster
float monsterX = 0.0f;
float monsterY = 0.0f;
float monsterSpeed = 0.002f;
float mouthOffset = 0.0f;
bool mouthOpening = true;
float scoutmonsX = 0.0f;
float scoutmonsY = 0.0f;



//venus rotation
float venusAngle = 0.0f;







void drawEllipse(float x_center, float y_center, float a, float b) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float x = x_center + a * cosf(angle);
        float y = y_center + b * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

void drawStar(float cx, float cy, float innerRadius, float outerRadius, int numPoints) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 2 * numPoints; i++) {
        float angle = i * 3.1415926f / numPoints;
        float r = (i % 2 == 0) ? outerRadius : innerRadius;
        float x = cx + r * cosf(angle);
        float y = cy + r * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void displaystar()
{
    // Close stars (bigger)
    drawStar(-0.7f, 0.8f, 0.015f, 0.03f, 10);
    drawStar(1.2f, 0.5f, 0.012f, 0.025f, 10);
    drawStar(-1.5f, 0.3f, 0.01f, 0.02f, 10);
    drawStar(0.9f, -0.2f, 0.013f, 0.028f, 10);
    drawStar(-1.8f, -0.5f, 0.012f, 0.025f, 10);
    drawStar(1.5f, 0.8f, 0.014f, 0.03f, 10);
    drawStar(-0.3f, 0.7f, 0.012f, 0.027f, 10);
    drawStar(0.0f, 0.9f, 0.013f, 0.028f, 10);
    drawStar(-1.0f, -0.7f, 0.011f, 0.024f, 10);
    drawStar(1.8f, -0.8f, 0.01f, 0.02f, 10);

    // Medium stars
    drawStar(-0.5f, 0.2f, 0.007f, 0.018f, 10);
    drawStar(0.5f, -0.5f, 0.008f, 0.02f, 10);
    drawStar(-1.2f, 0.6f, 0.009f, 0.022f, 10);
    drawStar(1.0f, 0.0f, 0.007f, 0.018f, 10);
    drawStar(-0.9f, -0.3f, 0.006f, 0.015f, 10);
    drawStar(0.8f, 0.9f, 0.008f, 0.02f, 10);
    drawStar(-1.6f, 0.1f, 0.007f, 0.018f, 10);
    drawStar(1.3f, -0.4f, 0.009f, 0.02f, 10);
    drawStar(-0.2f, -0.8f, 0.006f, 0.015f, 10);
    drawStar(0.2f, 0.6f, 0.007f, 0.018f, 10);

    // Distant stars (smaller)
    drawStar(-1.9f, 0.9f, 0.004f, 0.01f, 10);
    drawStar(1.9f, 0.7f, 0.005f, 0.012f, 10);
    drawStar(-1.3f, -0.9f, 0.004f, 0.01f, 10);
    drawStar(1.1f, -0.6f, 0.005f, 0.012f, 10);
    drawStar(-0.7f, -0.9f, 0.006f, 0.015f, 10);
    drawStar(0.6f, 0.3f, 0.005f, 0.012f, 10);
    drawStar(-0.4f, 0.0f, 0.004f, 0.01f, 10);
    drawStar(0.3f, -0.2f, 0.005f, 0.012f, 10);
    drawStar(-0.1f, 0.4f, 0.006f, 0.015f, 10);
    drawStar(0.0f, -0.6f, 0.005f, 0.012f, 10);

    // Extra random stars
    drawStar(1.7f, 0.1f, 0.005f, 0.012f, 10);
    drawStar(-1.4f, 0.5f, 0.006f, 0.015f, 10);
    drawStar(0.9f, -0.9f, 0.004f, 0.01f, 10);
    drawStar(-1.8f, 0.3f, 0.007f, 0.018f, 10);
    drawStar(1.5f, -0.2f, 0.005f, 0.012f, 10);
    drawStar(-0.5f, 0.9f, 0.006f, 0.015f, 10);
    drawStar(0.4f, -0.1f, 0.005f, 0.012f, 10);
    drawStar(-1.1f, -0.5f, 0.004f, 0.01f, 10);
    drawStar(1.2f, 0.2f, 0.007f, 0.018f, 10);
    drawStar(-0.8f, 0.0f, 0.005f, 0.012f, 10);

    drawStar(0.0f, 0.1f, 0.006f, 0.015f, 10);
    drawStar(-1.0f, 0.8f, 0.005f, 0.012f, 10);
    drawStar(0.8f, -0.7f, 0.004f, 0.01f, 10);
    drawStar(-0.3f, 0.5f, 0.007f, 0.018f, 10);
    drawStar(1.4f, 0.6f, 0.005f, 0.012f, 10);
    drawStar(-1.6f, -0.2f, 0.006f, 0.015f, 10);
    drawStar(0.3f, -0.4f, 0.005f, 0.012f, 10);
    drawStar(-0.6f, -0.7f, 0.004f, 0.01f, 10);
    drawStar(0.5f, 0.8f, 0.007f, 0.018f, 10);
    drawStar(-0.9f, 0.2f, 0.006f, 0.015f, 10);

    drawStar(0.0f, -0.9f, 0.005f, 0.012f, 10);
    drawStar(1.0f, 0.9f, 0.004f, 0.01f, 10);
    drawStar(-1.2f, -0.1f, 0.007f, 0.018f, 10);
    drawStar(1.6f, -0.3f, 0.005f, 0.012f, 10);
    drawStar(-1.7f, 0.7f, 0.006f, 0.015f, 10);
    drawStar(0.7f, -0.8f, 0.004f, 0.01f, 10);
    drawStar(-0.2f, 0.9f, 0.007f, 0.018f, 10);
    drawStar(0.9f, 0.3f, 0.006f, 0.015f, 10);
    drawStar(-1.5f, -0.6f, 0.005f, 0.012f, 10);
    drawStar(1.3f, -0.9f, 0.004f, 0.01f, 10);
}


void drawAsteroidAt(float x, float y) {
    // Main body - smoother, organic shape with softened vertices
    glColor4f(0.5f, 0.5f, 0.5f, 0.85f); // Grayish color
    glBegin(GL_POLYGON);
        glVertex2f(x + 0.00f, y + 0.072f); // Top center, slightly raised
        glVertex2f(x + 0.045f, y + 0.065f); // Smooth right upper curve
        glVertex2f(x + 0.072f, y + 0.045f); // Right side, rounded
        glVertex2f(x + 0.075f, y + 0.015f); // Right lower, gentle slope
        glVertex2f(x + 0.062f, y - 0.025f); // Lower right, smooth transition
        glVertex2f(x + 0.035f, y - 0.062f); // Bottom right, curved
        glVertex2f(x + 0.00f, y - 0.075f); // Bottom center, rounded
        glVertex2f(x - 0.035f, y - 0.068f); // Bottom left, smooth
        glVertex2f(x - 0.065f, y - 0.045f); // Left lower, gentle curve
        glVertex2f(x - 0.075f, y - 0.015f); // Left side, rounded
        glVertex2f(x - 0.062f, y + 0.025f); // Left upper, smooth
        glVertex2f(x - 0.035f, y + 0.055f); // Upper left, curved
        glVertex2f(x - 0.01f, y + 0.068f); // Near top, smooth close
    glEnd();

    // Surface texture - small bumps and irregularities
    glColor4f(0.55f, 0.55f, 0.55f, 0.9f); // Slightly lighter for texture
    drawCircle(x + 0.05f, y + 0.02f, 0.008f); // Bump 1
    drawCircle(x - 0.04f, y - 0.03f, 0.006f); // Bump 2
    drawCircle(x + 0.02f, y - 0.04f, 0.007f); // Bump 3
    drawCircle(x - 0.02f, y + 0.03f, 0.005f); // Bump 4

    // Craters - varying sizes and shades for depth
    glColor4f(0.4f, 0.4f, 0.4f, 0.9f); // Darker gray for craters
    drawCircle(x + 0.03f, y + 0.02f, 0.015f); // Large crater 1
    drawCircle(x - 0.02f, y - 0.03f, 0.012f); // Medium crater 2
    drawCircle(x + 0.04f, y - 0.02f, 0.01f);  // Small crater 3
    drawCircle(x - 0.03f, y + 0.01f, 0.008f); // Small crater 4
    drawCircle(x + 0.01f, y - 0.04f, 0.009f); // Small crater 5

    // Crater rims - lighter to simulate raised edges
    glColor4f(0.6f, 0.6f, 0.6f, 0.7f); // Lighter gray for rims
    drawCircle(x + 0.03f, y + 0.02f, 0.018f); // Rim for large crater
    drawCircle(x - 0.02f, y - 0.03f, 0.014f); // Rim for medium crater
    drawCircle(x + 0.04f, y - 0.02f, 0.012f); // Rim for small crater 3
    drawCircle(x - 0.03f, y + 0.01f, 0.01f);  // Rim for small crater 4
    drawCircle(x + 0.01f, y - 0.04f, 0.011f); // Rim for small crater 5
}


void drawSun() {
    float cx = 1.6f, cy = -0.6f;  // Sun center moved slightly down (south)

    // 🔆 Adjusted smaller radii
    float outerGlow = 0.10f;
    float midGlow   = 0.07f;
    float innerGlow = 0.05f;
    float core      = 0.025f;

    // Outer glow (faint orange)
    glColor4f(1.0f, 0.5f, 0.0f, 0.2f);
    drawCircle(cx, cy, outerGlow);

    // Mid glow
    glColor4f(1.0f, 0.7f, 0.0f, 0.3f);
    drawCircle(cx, cy, midGlow);

    // Inner glow
    glColor4f(1.0f, 0.85f, 0.0f, 0.6f);
    drawCircle(cx, cy, innerGlow);

    // Core (bright yellow)
    glColor3f(1.0f, 0.95f, 0.2f);
    drawCircle(cx, cy, core);

    // 🔆 Sun Rays using triangles
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);              // Move origin to sun center
    glRotatef(rayRotation, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glColor3f(1.0f, 0.8f, 0.0f);

    int rays = 16;             // number of rays
    float rayInner = 0.11f;    // start just outside glow
    float rayOuter = 0.16f;    // how far rays extend

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < rays; i++) {
        float angle = 2.0f * 3.1415926f * i / rays;

        float x1 = rayInner * cos(angle - 0.05f);
        float y1 = rayInner * sin(angle - 0.05f);

        float x2 = rayInner * cos(angle + 0.05f);
        float y2 = rayInner * sin(angle + 0.05f);

        float x3 = rayOuter * cos(angle);
        float y3 = rayOuter * sin(angle);

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    }
    glEnd();
    glPopMatrix();
}



void drawUFO() {
    glPushMatrix(); // Save current transformation state


    glScalef(ufoscale, ufoscale , 1.0f);

    // Main body
    glColor3f(0.6f, 0.6f, 0.6f);
    drawEllipse(ufoX, 0.3f, 0.18f, 0.048f);

    // Dome
    glColor3f(0.8f, 0.8f, 1.0f);
    drawEllipse(ufoX, 0.34f, 0.09f, 0.0525f);

    // Bottom
    glColor3f(0.55f, 0.55f, 0.55f);
    drawEllipse(ufoX, 0.26f, 0.1f, 0.015f);

    // Legs
    glColor3f(0.5f, 0.5f, 0.5f);
    drawTriangle(ufoX - 0.0675f, 0.26f, ufoX - 0.0825f, 0.21f, ufoX - 0.0525f, 0.21f);
    drawTriangle(ufoX + 0.0675f, 0.255f, ufoX + 0.0825f, 0.205f, ufoX + 0.0525f, 0.205f);

    glPopMatrix(); // Restore transformation state
}


void drawCrater() {

    // Larger craters (0.03–0.05, fewer)
    glColor4f(0.80f, 0.80f, 0.83f, 0.95f); drawCircle(-0.50f, -0.92f, 0.05f);  // Left-center, large
    glColor4f(0.79f, 0.79f, 0.82f, 0.90f); drawCircle( 0.60f, -0.90f, 0.04f);  // Right-center, large
    glColor4f(0.78f, 0.78f, 0.81f, 0.85f); drawCircle( 0.00f, -0.88f, 0.045f); // Center, large
    glColor4f(0.77f, 0.77f, 0.80f, 0.85f); drawCircle(-0.80f, -0.89f, 0.035f); // Left-upper, large
    glColor4f(0.76f, 0.76f, 0.79f, 0.90f); drawCircle( 0.85f, -0.93f, 0.03f);  // Right-lower, large

    // Medium craters (0.02–0.03)
    glColor4f(0.75f, 0.75f, 0.78f, 0.95f); drawCircle(-0.90f, -0.87f, 0.025f); // Far-left upper
    glColor4f(0.80f, 0.80f, 0.83f, 0.95f); drawCircle(-0.70f, -0.94f, 0.022f); // Left-lower
    glColor4f(0.79f, 0.79f, 0.82f, 0.90f); drawCircle(-0.30f, -0.90f, 0.028f); // Center
    glColor4f(0.78f, 0.78f, 0.81f, 0.85f); drawCircle( 0.20f, -0.86f, 0.02f);  // Center-right
    glColor4f(0.77f, 0.77f, 0.80f, 0.85f); drawCircle( 0.75f, -0.88f, 0.025f); // Right-upper
    glColor4f(0.76f, 0.76f, 0.79f, 0.90f); drawCircle(-0.20f, -0.93f, 0.023f); // Center-lower
    glColor4f(0.75f, 0.75f, 0.78f, 0.95f); drawCircle( 0.40f, -0.91f, 0.027f); // Right-center
    glColor4f(0.80f, 0.80f, 0.83f, 0.95f); drawCircle(-0.60f, -0.88f, 0.02f);  // Left-upper
    glColor4f(0.79f, 0.79f, 0.82f, 0.90f); drawCircle( 0.90f, -0.87f, 0.026f); // Far-right upper
    glColor4f(0.78f, 0.78f, 0.81f, 0.85f); drawCircle(-0.10f, -0.89f, 0.024f); // Center

    // Smaller craters (0.01–0.02, more numerous)
    glColor4f(0.77f, 0.77f, 0.80f, 0.85f); drawCircle(-0.95f, -0.90f, 0.015f); // Far-left
    glColor4f(0.76f, 0.76f, 0.79f, 0.90f); drawCircle(-0.75f, -0.86f, 0.012f); // Left-upper
    glColor4f(0.75f, 0.75f, 0.78f, 0.95f); drawCircle(-0.55f, -0.93f, 0.018f); // Left-lower
    glColor4f(0.80f, 0.80f, 0.83f, 0.95f); drawCircle(-0.35f, -0.87f, 0.01f);  // Center-left
    glColor4f(0.79f, 0.79f, 0.82f, 0.90f); drawCircle(-0.15f, -0.91f, 0.016f); // Center
    glColor4f(0.78f, 0.78f, 0.81f, 0.85f); drawCircle( 0.05f, -0.88f, 0.014f); // Center-right
    glColor4f(0.77f, 0.77f, 0.80f, 0.85f); drawCircle( 0.25f, -0.92f, 0.017f); // Center-right
    glColor4f(0.76f, 0.76f, 0.79f, 0.90f); drawCircle( 0.45f, -0.86f, 0.013f); // Right-upper
    glColor4f(0.75f, 0.75f, 0.78f, 0.95f); drawCircle( 0.65f, -0.90f, 0.015f); // Right-center
    glColor4f(0.80f, 0.80f, 0.83f, 0.95f); drawCircle( 0.80f, -0.94f, 0.019f); // Right-lower
    glColor4f(0.79f, 0.79f, 0.82f, 0.90f); drawCircle(-0.85f, -0.92f, 0.014f); // Left-lower
    glColor4f(0.78f, 0.78f, 0.81f, 0.85f); drawCircle(-0.65f, -0.89f, 0.016f); // Left-upper
    glColor4f(0.77f, 0.77f, 0.80f, 0.85f); drawCircle(-0.25f, -0.86f, 0.012f); // Center-left
    glColor4f(0.76f, 0.76f, 0.79f, 0.90f); drawCircle( 0.15f, -0.93f, 0.018f); // Center-right
    glColor4f(0.75f, 0.75f, 0.78f, 0.95f); drawCircle( 0.35f, -0.88f, 0.015f); // Right-upper
}




void drawSatellite() {

    glPushMatrix();

   glTranslatef(satelliteX, satelliteY, 0.0f);
     glScalef(0.50f, 0.50f, 0.0f);
    glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);

    // === Tilted Cylindrical Body with Details ===
    glColor3f(0.65f, 0.65f, 0.65f);
    drawQuad(-0.04f, -0.07f, 0.04f, -0.07f,
              0.04f,  0.07f, -0.04f,  0.07f);

    glColor3f(0.7f, 0.7f, 0.7f);
    drawEllipse(0.0f, 0.07f, 0.04f, 0.007f);
    drawEllipse(0.0f, -0.07f, 0.04f, 0.007f);

    glColor3f(0.5f, 0.5f, 0.5f);
    drawQuad(-0.04f, -0.045f, 0.04f, -0.045f,
              0.04f, -0.04f, -0.04f, -0.04f);
    drawQuad(-0.04f, 0.0f, 0.04f, 0.0f,
              0.04f, 0.005f, -0.04f, 0.005f);
    drawQuad(-0.04f, 0.04f, 0.04f, 0.04f,
              0.04f, 0.045f, -0.04f, 0.045f);

    glColor3f(0.4f, 0.4f, 0.4f);
    drawQuad(-0.015f, -0.015f, 0.015f, -0.015f,
              0.015f,  0.015f, -0.015f,  0.015f);

    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle(-0.03f, -0.06f, 0.003f);
    drawCircle( 0.03f, -0.06f, 0.003f);
    drawCircle(-0.03f,  0.06f, 0.003f);
    drawCircle( 0.03f,  0.06f, 0.003f);

    // === Panel Support Arms (Slimmed & Realistic) ===
    glColor3f(0.6f, 0.6f, 0.6f);
    drawQuad(-0.04f, -0.005f, -0.04f, 0.005f,
             -0.09f, 0.005f, -0.09f, -0.005f);
    drawQuad( 0.04f, -0.005f,  0.04f, 0.005f,
              0.09f, 0.005f,  0.09f, -0.005f);

    // === Dish Antenna ===
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0.06f, 0.06f, 0.025f);

    glColor3f(0.2f, 0.2f, 0.2f);
    drawTriangle(0.06f, 0.06f,
                 0.055f, 0.07f,
                 0.065f, 0.07f);

    // === Solar Panel Base (Left & Right) ===
    glColor3f(0.2f, 0.4f, 0.8f);
    drawQuad(-0.18f, -0.04f, -0.09f, -0.04f,
             -0.09f,  0.04f, -0.18f,  0.04f);
    drawQuad( 0.09f, -0.04f,  0.18f, -0.04f,
              0.18f,  0.04f,  0.09f,  0.04f);

    // === Larger Panel Tiles (Left) ===
    glColor3f(0.1f, 0.3f, 0.6f);
    drawQuad(-0.175f, -0.035f, -0.145f, -0.035f,
             -0.145f, -0.005f, -0.175f, -0.005f);
    drawQuad(-0.135f, -0.035f, -0.105f, -0.035f,
             -0.105f, -0.005f, -0.135f, -0.005f);
    drawQuad(-0.175f,  0.005f, -0.145f,  0.005f,
             -0.145f,  0.035f, -0.175f,  0.035f);
    drawQuad(-0.135f,  0.005f, -0.105f,  0.005f,
             -0.105f,  0.035f, -0.135f,  0.035f);

    // === Larger Panel Tiles (Right) ===
    drawQuad( 0.105f, -0.035f,  0.135f, -0.035f,
              0.135f, -0.005f,  0.105f, -0.005f);
    drawQuad( 0.145f, -0.035f,  0.175f, -0.035f,
              0.175f, -0.005f,  0.145f, -0.005f);
    drawQuad( 0.105f,  0.005f,  0.135f,  0.005f,
              0.135f,  0.035f,  0.105f,  0.035f);
    drawQuad( 0.145f,  0.005f,  0.175f,  0.005f,
              0.175f,  0.035f,  0.145f,  0.035f);

    glPopMatrix();
}




void CreateEarth() {


    glPushMatrix();

    // Move the center of rotation to Earth's center
    glTranslatef(-1.50f, 0.42f, 0.0f);  // Move to origin relative to Earth
    glRotatef(earthRotation, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glTranslatef(1.50f, -0.42f, 0.0f); // Move back to original position

    // Earth circle
    glColor4f(0.00f, 0.20f, 0.50f, 0.95f);
    drawCircle(-1.50f, 0.42f, 0.30f);

    // Polygon 1: North America
    glBegin(GL_POLYGON);
    glColor4f(0.32f, 0.72f, 0.32f, 0.92f);
    glVertex2f(-1.68f, 0.60f);
    glVertex2f(-1.66f, 0.62f);
    glVertex2f(-1.63f, 0.65f);
    glVertex2f(-1.61f, 0.64f);
    glVertex2f(-1.58f, 0.62f);
    glVertex2f(-1.56f, 0.66f);
    glVertex2f(-1.53f, 0.68f);
    glVertex2f(-1.51f, 0.66f);
    glVertex2f(-1.50f, 0.63f);
    glVertex2f(-1.47f, 0.57f);
    glVertex2f(-1.46f, 0.55f);
    glVertex2f(-1.47f, 0.52f);
    glVertex2f(-1.48f, 0.50f);
    glVertex2f(-1.51f, 0.49f);
    glVertex2f(-1.53f, 0.48f);
    glVertex2f(-1.55f, 0.46f);
    glVertex2f(-1.58f, 0.45f);
    glVertex2f(-1.61f, 0.46f);
    glVertex2f(-1.63f, 0.48f);
    glVertex2f(-1.66f, 0.52f);
    glVertex2f(-1.70f, 0.58f);
    glEnd();

    // Polygon 2: South America
    glBegin(GL_POLYGON);
    glColor4f(0.27f, 0.67f, 0.27f, 0.87f);
    glVertex2f(-1.58f, 0.33f);
    glVertex2f(-1.56f, 0.34f);
    glVertex2f(-1.52f, 0.36f);
    glVertex2f(-1.50f, 0.34f);
    glVertex2f(-1.47f, 0.32f);
    glVertex2f(-1.45f, 0.30f);
    glVertex2f(-1.43f, 0.28f);
    glVertex2f(-1.42f, 0.26f);
    glVertex2f(-1.44f, 0.24f);
    glVertex2f(-1.46f, 0.22f);
    glVertex2f(-1.48f, 0.20f);
    glVertex2f(-1.50f, 0.18f);
    glVertex2f(-1.52f, 0.16f);
    glVertex2f(-1.54f, 0.17f);
    glVertex2f(-1.56f, 0.18f);
    glVertex2f(-1.58f, 0.18f);
    glVertex2f(-1.60f, 0.20f);
    glVertex2f(-1.62f, 0.23f);
    glVertex2f(-1.61f, 0.25f);
    glVertex2f(-1.60f, 0.28f);
    glVertex2f(-1.58f, 0.30f);
    glVertex2f(-1.56f, 0.31f);
    glEnd();

    // Polygon 3: Africa
    glBegin(GL_POLYGON);
    glColor4f(0.37f, 0.77f, 0.37f, 0.92f);
    glVertex2f(-1.38f, 0.55f);
    glVertex2f(-1.36f, 0.56f);
    glVertex2f(-1.33f, 0.58f);
    glVertex2f(-1.31f, 0.56f);
    glVertex2f(-1.28f, 0.52f);
    glVertex2f(-1.26f, 0.48f);
    glVertex2f(-1.23f, 0.45f);
    glVertex2f(-1.24f, 0.42f);
    glVertex2f(-1.26f, 0.40f);
    glVertex2f(-1.28f, 0.38f);
    glVertex2f(-1.30f, 0.35f);
    glVertex2f(-1.33f, 0.34f);
    glVertex2f(-1.36f, 0.32f);
    glVertex2f(-1.38f, 0.33f);
    glVertex2f(-1.40f, 0.35f);
    glVertex2f(-1.42f, 0.37f);
    glVertex2f(-1.43f, 0.40f);
    glVertex2f(-1.42f, 0.42f);
    glVertex2f(-1.40f, 0.45f);
    glVertex2f(-1.38f, 0.48f);
    glVertex2f(-1.36f, 0.50f);
    glEnd();


    glPopMatrix();
}


void drawLowerStage(float stageY) {
    // =========================
    // COLORS
    // =========================
    const GLfloat bodyR = 0.92f, bodyG = 0.94f, bodyB = 0.98f;   // Light silver body
    const GLfloat finR  = 0.80f, finG  = 0.15f, finB  = 0.15f;   // Red fins
    const GLfloat rimR  = 0.95f, rimG  = 0.95f, rimB  = 0.98f;   // Silver window rim
    const GLfloat glassR= 0.30f, glassG= 0.70f, glassB= 0.90f;   // Blue window glass
    const GLfloat darkR = 0.12f, darkG = 0.12f, darkB = 0.12f;   // Dark gray nozzle/fins shadow
    const GLfloat accentR = 0.90f, accentG = 0.60f, accentB = 0.10f; // Orange accent

    glPushMatrix();
    glScalef(0.6f, 0.6f, 0.0f);
    glTranslatef(-1.8f, stageY, 0.0f);

    // Lower body (tapered quad)
    glColor3f(bodyR, bodyG, bodyB);
    glBegin(GL_QUADS);
        glVertex2f(-0.20f, -0.65f);
        glVertex2f( 0.20f, -0.65f);
        glVertex2f( 0.173f,  0.0f);
        glVertex2f(-0.173f,  0.0f);
    glEnd();

    // Lower center metallic sheen
    glColor3f(0.98f, 0.98f, 1.00f);
    glBegin(GL_QUADS);
        glVertex2f(-0.03f, -0.60f);
        glVertex2f( 0.03f, -0.60f);
        glVertex2f( 0.03f,   0.0f);
        glVertex2f(-0.03f,   0.0f);
    glEnd();

    // Lower left side shading
    glColor3f(0.85f, 0.87f, 0.92f);
    glBegin(GL_QUADS);
        glVertex2f(-0.20f, -0.60f);
        glVertex2f(-0.18f, -0.60f);
        glVertex2f(-0.158f,  0.0f);
        glVertex2f(-0.178f,  0.0f);
    glEnd();

    // Lower right side shading
    glBegin(GL_QUADS);
        glVertex2f( 0.18f, -0.60f);
        glVertex2f( 0.20f, -0.60f);
        glVertex2f( 0.178f,  0.0f);
        glVertex2f( 0.158f,  0.0f);
    glEnd();

    // Lower decorative orange band
    glColor3f(accentR, accentG, accentB);
    glBegin(GL_QUADS);
        glVertex2f(-0.18f, -0.10f);
        glVertex2f( 0.18f, -0.10f);
        glVertex2f( 0.18f, -0.06f);
        glVertex2f(-0.18f, -0.06f);
    glEnd();

    // Lower window
    glColor3f(rimR, rimG, rimB);
    drawCircle(0.0f, -0.05f, 0.08f); // Rim
    glColor3f(glassR, glassG, glassB);
    drawCircle(0.0f, -0.05f, 0.06f); // Glass

    // SIDE FINS (curved + layered)
    glColor3f(darkR, darkG, darkB);
    glBegin(GL_POLYGON); // Left shadow fin
        glVertex2f(-0.20f, -0.20f);
        glVertex2f(-0.55f, -0.65f);
        glVertex2f(-0.45f, -0.70f);
        glVertex2f(-0.20f, -0.65f);
    glEnd();
    glBegin(GL_POLYGON); // Right shadow fin
        glVertex2f( 0.20f, -0.20f);
        glVertex2f( 0.55f, -0.65f);
        glVertex2f( 0.45f, -0.70f);
        glVertex2f( 0.20f, -0.65f);
    glEnd();

    glColor3f(finR, finG, finB);
    glBegin(GL_POLYGON); // Left red fin
        glVertex2f(-0.20f, -0.25f);
        glVertex2f(-0.50f, -0.65f);
        glVertex2f(-0.40f, -0.68f);
        glVertex2f(-0.20f, -0.64f);
    glEnd();
    glBegin(GL_POLYGON); // Right red fin
        glVertex2f( 0.20f, -0.25f);
        glVertex2f( 0.50f, -0.65f);
        glVertex2f( 0.40f, -0.68f);
        glVertex2f( 0.20f, -0.64f);
    glEnd();

    // NOZZLE (flared + detailed)
    glColor3f(darkR, darkG, darkB);
    glBegin(GL_POLYGON);
        glVertex2f(-0.18f, -0.65f);
        glVertex2f( 0.18f, -0.65f);
        glVertex2f( 0.22f, -0.85f);
        glVertex2f(-0.22f, -0.85f);
    glEnd();
    glColor3f(0.25f, 0.25f, 0.25f);
    drawEllipse(0.0f, -0.85f, 0.22f, 0.05f); // Nozzle rim

    // FLAME (animated three-layer)
    glColor3f(1.00f, 0.55f, 0.00f); // Orange outer flame
    glBegin(GL_POLYGON);
        glVertex2f(-0.18f, -0.85f);                          // base left
        glVertex2f( 0.18f, -0.85f);                          // base right
        glVertex2f( 0.12f, -1.00f + lowerFlameOffset);       // tip
        glVertex2f( 0.06f, -1.10f + lowerFlameOffset);
        glVertex2f( 0.00f, -1.05f + lowerFlameOffset);
        glVertex2f(-0.06f, -1.10f + lowerFlameOffset);
        glVertex2f(-0.12f, -1.00f + lowerFlameOffset);
    glEnd();

    glColor3f(1.00f, 0.90f, 0.20f); // Yellow middle flame
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.10f, -0.85f);
        glVertex2f( 0.10f, -0.85f);
        glVertex2f( 0.00f, -1.05f + lowerFlameOffset);
    glEnd();

    glColor3f(1.00f, 0.98f, 0.95f); // White core flame
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, -0.85f);
        glVertex2f( 0.04f, -0.85f);
        glVertex2f( 0.03f, -0.95f + lowerFlameOffset);
        glVertex2f( 0.00f, -1.00f + lowerFlameOffset);
        glVertex2f(-0.03f, -0.95f + lowerFlameOffset);
    glEnd();

    glPopMatrix();
}


void upperRocketFlame()
{

// Outer flame (orange)
glColor3f(1.00f, 0.55f, 0.00f);
glBegin(GL_POLYGON);
    glVertex2f(-0.12f, -0.14f);                     // base left (new nozzle height)
    glVertex2f( 0.12f, -0.14f);                     // base right
    glVertex2f( 0.08f, -0.29f + upperFlameOffset);  // tip
    glVertex2f( 0.04f, -0.39f + upperFlameOffset);
    glVertex2f( 0.00f, -0.34f + upperFlameOffset);
    glVertex2f(-0.04f, -0.39f + upperFlameOffset);
    glVertex2f(-0.08f, -0.29f + upperFlameOffset);
glEnd();

// Middle flame (yellow)
glColor3f(1.00f, 0.90f, 0.20f);
glBegin(GL_TRIANGLES);
    glVertex2f(-0.08f, -0.14f);
    glVertex2f( 0.08f, -0.14f);
    glVertex2f( 0.00f, -0.34f + upperFlameOffset);
glEnd();

// Core flame (white)
glColor3f(1.00f, 0.98f, 0.95f);
glBegin(GL_POLYGON);
    glVertex2f(-0.03f, -0.14f);
    glVertex2f( 0.03f, -0.14f);
    glVertex2f( 0.02f, -0.24f + upperFlameOffset);
    glVertex2f( 0.00f, -0.29f + upperFlameOffset);
    glVertex2f(-0.02f, -0.24f + upperFlameOffset);
glEnd();


}


void drawUpperStage(float stageY) {
    const GLfloat bodyR = 0.92f, bodyG = 0.94f, bodyB = 0.98f;
    const GLfloat noseR = 0.88f, noseG = 0.15f, noseB = 0.15f;
    const GLfloat finR  = 0.80f, finG  = 0.15f, finB  = 0.15f;
    const GLfloat rimR  = 0.95f, rimG  = 0.95f, rimB  = 0.98f;
    const GLfloat glassR= 0.30f, glassG= 0.70f, glassB= 0.90f;
    const GLfloat darkR = 0.12f, darkG = 0.12f, darkB = 0.12f;
    const GLfloat accentR = 0.90f, accentG = 0.60f, accentB = 0.10f;

    glPushMatrix();
    glScalef(0.6f, 0.6f, 0.0f);
    glTranslatef(-1.8f, stageY, 0.0f);

    // Main body
    glColor3f(bodyR, bodyG, bodyB);
    drawQuad(-0.173f, 0.0f, 0.173f, 0.0f, 0.14f, 0.75f, -0.14f, 0.75f);

    // Sheen and shading
    glColor3f(0.98f, 0.98f, 1.00f);
    drawQuad(-0.03f, 0.0f, 0.03f, 0.0f, 0.03f, 0.70f, -0.03f, 0.70f);

    glColor3f(0.85f, 0.87f, 0.92f);
    drawQuad(-0.178f, 0.0f, -0.158f, 0.0f, -0.12f, 0.70f, -0.15f, 0.70f);
    drawQuad(0.158f, 0.0f, 0.178f, 0.0f, 0.15f, 0.70f, 0.12f, 0.70f);

    // Orange bands
    glColor3f(accentR, accentG, accentB);
    drawQuad(-0.17f, 0.10f, 0.17f, 0.10f, 0.17f, 0.14f, -0.17f, 0.14f);
    drawQuad(-0.17f, 0.30f, 0.17f, 0.30f, 0.17f, 0.34f, -0.17f, 0.34f);
    drawQuad(-0.17f, 0.50f, 0.17f, 0.50f, 0.17f, 0.54f, -0.17f, 0.54f);
    drawQuad(-0.17f, 0.65f, 0.17f, 0.65f, 0.17f, 0.69f, -0.17f, 0.69f);

    // Windows
    glColor3f(rimR, rimG, rimB);
    drawCircle(0.0f, 0.20f, 0.09f);
    drawCircle(0.0f, 0.45f, 0.04f);
    drawCircle(0.0f, 0.60f, 0.06f);
    glColor3f(glassR, glassG, glassB);
    drawCircle(0.0f, 0.20f, 0.07f);
    drawCircle(0.0f, 0.45f, 0.02f);
    drawCircle(0.0f, 0.60f, 0.04f);

    // RCS thrusters
    glColor3f(darkR, darkG, darkB);
    drawCircle(-0.16f, 0.05f, 0.012f);
    drawCircle( 0.16f, 0.05f, 0.012f);
    drawCircle(-0.16f, 0.40f, 0.012f);
    drawCircle( 0.16f, 0.40f, 0.012f);
    drawCircle(-0.16f, 0.65f, 0.012f);
    drawCircle( 0.16f, 0.65f, 0.012f);


   // === Upper Stage Fins (side-mounted, slightly bigger, properly offset) ===

// Left shadow fin
glColor3f(darkR, darkG, darkB);
glBegin(GL_TRIANGLES);
    glVertex2f(-0.16f, 0.26f);   // top attach (shifted left from -0.14f)
    glVertex2f(-0.16f, 0.00f);   // bottom attach
    glVertex2f(-0.36f, -0.04f);  // outward tip
glEnd();

// Right shadow fin
glBegin(GL_TRIANGLES);
    glVertex2f( 0.16f, 0.26f);   // top attach (shifted right from 0.14f)
    glVertex2f( 0.16f, 0.00f);   // bottom attach
    glVertex2f( 0.36f, -0.04f);  // outward tip
glEnd();

// Left red fin
glColor3f(finR, finG, finB);
glBegin(GL_TRIANGLES);
    glVertex2f(-0.16f, 0.25f);   // top attach
    glVertex2f(-0.16f, 0.01f);   // bottom attach
    glVertex2f(-0.32f, -0.03f);  // outward tip
glEnd();

// Right red fin
glBegin(GL_TRIANGLES);
    glVertex2f( 0.16f, 0.25f);   // top attach
    glVertex2f( 0.16f, 0.01f);   // bottom attach
    glVertex2f( 0.32f, -0.03f);  // outward tip
glEnd();



// === Upper Stage Nozzle (smaller, flared) ===
glColor3f(darkR, darkG, darkB);
glBegin(GL_POLYGON);
    glVertex2f(-0.09f, 0.00f);   // base left (narrower)
    glVertex2f( 0.09f, 0.00f);   // base right
    glVertex2f( 0.11f, -0.14f);  // bottom right (shorter)
    glVertex2f(-0.11f, -0.14f);  // bottom left
glEnd();

// Nozzle rim
glColor3f(0.25f, 0.25f, 0.25f);
drawEllipse(0.0f, -0.14f, 0.11f, 0.03f); // Smaller rim


    // Rocket fire
   if (rocketY > -1.40f)
   {
       upperRocketFlame();
   }


   // Rocket stairs

    if (stairLength > 0.0f) {
    glColor3f(0.5f, 0.5f, 0.5f); // Gray stair color

    glBegin(GL_QUADS);
        glVertex2f(0.16f, 0.35f);                          // top-right (flush with rocket edge)
        glVertex2f(0.16f, 0.31f);                          // top-left (thickness = 0.08f)
        glVertex2f(0.093f + stairLength, 0.20f - stairLength * 0.31f); // bottom-left
        glVertex2f(0.173f + stairLength, 0.20f - stairLength * 0.31f); // bottom-right
    glEnd();
}



    // Docking port
    glColor3f(0.3f, 0.3f, 0.3f);
    drawQuad(-0.03f, 0.75f, 0.03f, 0.75f, 0.03f, 0.85f, -0.03f, 0.85f);
    glColor3f(0.8f, 0.8f, 0.8f);
    drawCircle(0.0f, 0.87f, 0.008f);

    // Nose cone
    glColor3f(noseR, noseG, noseB);
    drawTriangle(-0.14f, 0.75f, 0.14f, 0.75f, 0.00f, 1.05f);

    glPopMatrix();
}


void drawRocket() {

    drawUpperStage(rocketY);
   // drawLowerStage(rocketY);

}




void FlagOnHand() {

     glPushMatrix();

     glTranslatef(flagX,flagY, 0.0f);
    // Flag pole (shorter and thicker)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.9652f, -0.646f);   // bottom left
        glVertex2f(-0.9557f, -0.646f);   // bottom right
        glVertex2f(-0.9557f, -0.456f);   // top right
        glVertex2f(-0.9652f, -0.456f);   // top left
    glEnd();

    // Flag cloth (green rectangle)
    glColor3f(0.0f, 0.5f, 0.0f); // bottle green
    glBegin(GL_QUADS);
        glVertex2f(-0.9557f, -0.4275f);     // top right
        glVertex2f(-0.9557f, -0.5035f);     // bottom right
        glVertex2f(-1.0887f, -0.5035f);     // bottom left
        glVertex2f(-1.0887f, -0.4275f);     // top left
    glEnd();

    // Red disc (centered in flag)
    glColor3f(1.0f, 0.0f, 0.0f); // red
    drawCircle(-1.0222f, -0.4655f, 0.0202f);


    glPopMatrix();

}


// Robot
void drawScoutE_Mk1() {



     FlagOnHand();
    glPushMatrix();
  //  glRotatef(scoutangle, 1.0f, 0.0f, 0.0f);
     glTranslatef(scoutX,scoutY, 0.0f);
    // === Two main tires (large circles attached directly under body) ===

    glTranslatef(scoutmonsX,scoutmonsY, 0.0f);
    glColor3f(0.12f, 0.12f, 0.12f); // dark tire rubber
    drawCircle(-1.0478f, -0.6504f, 0.0175f); // Rear tire (center raised to touch body at y=0.03)
    drawCircle(-1.0041f, -0.6504f, 0.0175f); // Front tire
    glColor3f(0.08f, 0.08f, 0.08f); // tire tread details (inner rings)
    drawCircle(-1.0478f, -0.6504f, 0.0131f);
    drawCircle(-1.0041f, -0.6504f, 0.0131f);
    glColor3f(0.55f, 0.55f, 0.55f); // wheel hubs
    drawCircle(-1.0478f, -0.6504f, 0.0044f);
    drawCircle(-1.0041f, -0.6504f, 0.0044f);

    // === Simple axle line (under body) ===
    glColor3f(0.35f, 0.35f, 0.35f);
    glBegin(GL_LINES);
        glVertex2f(-1.0478f, -0.6504f); glVertex2f(-1.0041f, -0.6504f);
    glEnd();

    // === Lower torso (main body base, tires touch bottom at y=0.03) ===
    glColor3f(0.52f, 0.54f, 0.57f);
    drawQuad(-1.061f, -0.6329f, -0.991f, -0.6329f, -0.9954f, -0.5979f, -1.0566f, -0.5979f);

    // Body side shade
    glColor3f(0.40f, 0.42f, 0.45f);
    drawQuad(-0.9954f, -0.6329f, -0.991f, -0.6241f, -0.991f, -0.6023f, -0.9954f, -0.5979f);

    // === Chest detail bolts ===
    glColor3f(0.12f, 0.12f, 0.12f);
    drawCircle(-1.0457f, -0.6241f, 0.0022f);
    drawCircle(-1.0063f, -0.6241f, 0.0022f);

    // === Upper torso (plate + vent) ===
    glColor3f(0.62f, 0.62f, 0.67f);
    drawQuad(-1.0566f, -0.5979f, -0.9954f, -0.5979f, -0.9998f, -0.5673f, -1.0522f, -0.5673f);
    glColor3f(0.22f, 0.24f, 0.26f);
    drawQuad(-1.0369f, -0.5892f, -1.0151f, -0.5892f, -1.0151f, -0.5804f, -1.0369f, -0.5804f);

    // === Neck ===
    glColor3f(0.38f, 0.38f, 0.40f);
    drawQuad(-1.0347f, -0.5673f, -1.0173f, -0.5673f, -1.0129f, -0.5411f, -1.0304f, -0.5411f);

    // === Head (visor + lens) ===
    glColor3f(0.12f, 0.16f, 0.30f);
    drawQuad(-1.05f, -0.5411f, -1.002f, -0.5411f, -0.9976f, -0.5062f, -1.0457f, -0.5062f);
    glColor3f(0.9f, 0.92f, 0.95f);
    drawQuad(-1.0391f, -0.5236f, -1.0129f, -0.5236f, -1.0107f, -0.5193f, -1.0369f, -0.5193f);
    glColor3f(0.7f, 0.85f, 1.0f);
    drawCircle(-1.0129f, -0.5215f, 0.0035f);
    glColor3f(0.22f, 0.26f, 0.40f);
    drawQuad(-1.0085f, -0.5193f, -0.9976f, -0.5193f, -0.9976f, -0.5171f, -1.0085f, -0.5171f);
    glColor3f(0.95f, 0.95f, 1.0f);
    drawCircle(-1.0063f, -0.5083f, 0.0017f);

    // === Arm shaft ===
    glColor3f(0.25f, 0.28f, 0.30f); // base arm color
    drawQuad(-1.0216f, -0.5804f, -1.0304f, -0.5804f, -1.0304f, -0.6307f, -1.0216f, -0.6307f);

    // === Arm stripes ===
    glColor3f(0.0f, 0.48f, 0.50f); // stripe color
    drawQuad(-1.0216f, -0.5848f, -1.0304f, -0.5848f, -1.0304f, -0.5857f, -1.0216f, -0.5857f); // top stripe
    drawQuad(-1.0216f, -0.5979f, -1.0304f, -0.5979f, -1.0304f, -0.5988f, -1.0216f, -0.5988f); // middle stripe
    drawQuad(-1.0216f, -0.611f, -1.0304f, -0.611f, -1.0304f, -0.6119f, -1.0216f, -0.6119f); // bottom stripe

    // === Palm circle ===
    glColor3f(0.25f, 0.28f, 0.30f); // palm color
    drawCircle(-1.026f, -0.6307f, 0.0087f);

    glColor3f(0.52f, 0.54f, 0.57f);
    drawCircle(-1.026f, -0.6307f, 0.0052f);

    // other arm

    // === Left-side arm extending forward (to the right) ===
    glColor3f(0.25f, 0.28f, 0.30f); // base arm color
    drawQuad(-0.9981f, -0.5804f, -0.9963f, -0.5892f, -0.9604f, -0.5892f, -0.9604f, -0.5804f); // horizontal shaft

    // === Thin angled stripes spanning full arm length ===
    glColor3f(0.0f, 0.48f, 0.50f); // stripe color

    // Stripe 1 (near base)
    drawQuad(-0.9963f, -0.5826f, -0.9946f, -0.587f, -0.9927f, -0.587f, -0.9946f, -0.5826f);

    // Stripe 2 (mid-arm)
    drawQuad(-0.9858f, -0.5826f, -0.984f, -0.587f, -0.9823f, -0.587f, -0.984f, -0.5826f);

    // Stripe 3 (near tip)
    drawQuad(-0.9753f, -0.5826f, -0.9736f, -0.587f, -0.9718f, -0.587f, -0.9736f, -0.5826f);

        // === Palm circle (at the tip, to the right) ===
    glColor3f(0.25f, 0.28f, 0.30f);
    drawCircle(-0.9604f, -0.5848f, 0.0087f);

    glPopMatrix();



}



void drawMonster() {

     glPushMatrix();
     glTranslatef(monsterX,monsterY, 0.0f);

    glColor3f(0.6f, 0.2f, 0.8f); glBegin(GL_POLYGON);
    glVertex2f(-2.075f, -0.76f);
    glVertex2f(-2.06f, -0.75f);
    glVertex2f(-2.04f, -0.75f);
    glVertex2f(-2.025f, -0.76f);
    glVertex2f(-2.005f, -0.76f);
    glVertex2f(-1.99f, -0.785f);
    glVertex2f(-1.975f, -0.805f);
    glVertex2f(-1.98f, -0.815f);
    glVertex2f(-1.975f, -0.835f);
    glVertex2f(-1.985f, -0.86f);
    glVertex2f(-1.975f, -0.87f);
    glVertex2f(-1.97f, -0.88f);
    glVertex2f(-1.965f, -0.91f);
    glVertex2f(-1.96f, -0.94f);
    glVertex2f(-1.98f, -0.945f);
    glVertex2f(-2.0f, -0.945f);
    glVertex2f(-2.05f, -0.95f);
    glVertex2f(-2.1f, -0.945f);
    glVertex2f(-2.12f, -0.945f);
    glVertex2f(-2.14f, -0.94f);
    glVertex2f(-2.135f, -0.91f);
    glVertex2f(-2.13f, -0.88f);
    glVertex2f(-2.125f, -0.87f);
    glVertex2f(-2.115f, -0.86f);
    glVertex2f(-2.125f, -0.835f);
    glVertex2f(-2.12f, -0.815f);
    glVertex2f(-2.125f, -0.805f);
    glVertex2f(-2.11f, -0.785f);
    glVertex2f(-2.095f, -0.76f);
    glEnd();
    glColor3f(0.8f, 0.2f, 0.2f); drawCircle(-2.05f, -0.815f, 0.03f);
    glColor3f(1.0f, 0.9f, 0.0f); drawCircle(-2.05f, -0.815f, 0.025f);
    glColor3f(0.0f, 0.0f, 0.0f); drawCircle(-2.05f, -0.81f, 0.015f);
    glColor3f(1.0f, 1.0f, 1.0f); drawCircle(-2.0575f, -0.805f, 0.004f);
    glColor3f(0.0f, 0.0f, 0.0f); glLineWidth(2.5f); glBegin(GL_LINE_STRIP);
    glVertex2f(-1.99f, -0.84f);
    glVertex2f(-2.005f, -0.85f);
    glVertex2f(-2.01f, -0.84f);
    glVertex2f(-2.03f, -0.855f);
    glVertex2f(-2.05f, -0.86f);
    glVertex2f(-2.07f, -0.855f);
    glVertex2f(-2.09f, -0.84f);
    glVertex2f(-2.095f, -0.85f);
    glVertex2f(-2.11f, -0.84f);
    glVertex2f(-2.11f, -0.9f);
    glVertex2f(-2.095f, -0.885f);
    glVertex2f(-2.09f, -0.9f);
    glVertex2f(-2.07f, -0.89f);
    glVertex2f(-2.05f, -0.905f);
    glVertex2f(-2.03f, -0.89f);
    glVertex2f(-2.01f, -0.9f);
    glVertex2f(-2.005f, -0.885f);
    glVertex2f(-1.99f, -0.9f);
    glEnd(); glLineWidth(1.0f);
    glColor3f(0.9f, 0.9f, 0.9f); glBegin(GL_TRIANGLES);
    glVertex2f(-1.995f, -0.845f);
    glVertex2f(-1.995f, -0.855f);
    glVertex2f(-2.01f, -0.855f);
    glVertex2f(-2.02f, -0.845f);
    glVertex2f(-2.02f, -0.85f);
    glVertex2f(-2.035f, -0.85f);
    glVertex2f(-2.08f, -0.845f);
    glVertex2f(-2.08f, -0.85f);
    glVertex2f(-2.065f, -0.85f);
    glVertex2f(-2.105f, -0.845f);
    glVertex2f(-2.105f, -0.855f);
    glVertex2f(-2.09f, -0.855f);
    glVertex2f(-1.995f, -0.895f);
    glVertex2f(-1.995f, -0.885f);
    glVertex2f(-2.01f, -0.885f);
    glVertex2f(-2.02f, -0.895f);
    glVertex2f(-2.02f, -0.89f);
    glVertex2f(-2.035f, -0.89f);
    glVertex2f(-2.08f, -0.895f);
    glVertex2f(-2.08f, -0.89f);
    glVertex2f(-2.065f, -0.89f);
    glVertex2f(-2.105f, -0.895f);
    glVertex2f(-2.105f, -0.885f);
    glVertex2f(-2.09f, -0.885f);
    glEnd();
    glColor3f(1.0f, 0.6f, 0.7f); glLineWidth(4.0f); glBegin(GL_LINE_STRIP);
    glVertex2f(-2.01f, -0.855f + mouthOffset);
    glVertex2f(-2.03f, -0.865f + mouthOffset);
    glVertex2f(-2.04f, -0.875f + mouthOffset);
    glVertex2f(-2.05f, -0.87f + mouthOffset);
    glVertex2f(-2.06f, -0.875f + mouthOffset);
    glVertex2f(-2.07f, -0.865f + mouthOffset);
    glVertex2f(-2.09f, -0.855f + mouthOffset);
    glEnd(); glLineWidth(1.0f);
    glColor3f(0.6f, 0.2f, 0.8f); glBegin(GL_POLYGON);
    glVertex2f(-1.99f, -0.85f);
    glVertex2f(-1.95f, -0.825f);
    glVertex2f(-1.955f, -0.81f);
    glVertex2f(-1.96f, -0.80f);
    glVertex2f(-1.98f, -0.80f);
    glVertex2f(-1.985f, -0.81f);
    glEnd(); glBegin(GL_POLYGON);
    glVertex2f(-1.96f, -0.80f);
    glVertex2f(-1.92f, -0.775f);
    glVertex2f(-1.925f, -0.76f);
    glVertex2f(-1.93f, -0.75f);
    glVertex2f(-1.95f, -0.75f);
    glVertex2f(-1.945f, -0.76f);
    glEnd(); glColor3f(0.4f, 0.1f, 0.6f); glBegin(GL_TRIANGLES);
    glVertex2f(-1.93f, -0.75f);
    glVertex2f(-1.90f, -0.735f);
    glVertex2f(-1.95f, -0.735f);
    glEnd(); glBegin(GL_TRIANGLES);
    glVertex2f(-1.92f, -0.74f);
    glVertex2f(-1.89f, -0.72f);
    glVertex2f(-1.93f, -0.72f);
    glEnd(); glBegin(GL_TRIANGLES);
    glVertex2f(-1.91f, -0.74f);
    glVertex2f(-1.88f, -0.725f);
    glVertex2f(-1.92f, -0.725f);
    glEnd(); glBegin(GL_TRIANGLES);
    glVertex2f(-1.90f, -0.74f);
    glVertex2f(-1.875f, -0.73f);
    glVertex2f(-1.91f, -0.73f);
    glEnd();
    glColor3f(0.6f, 0.2f, 0.8f); glBegin(GL_POLYGON);
    glVertex2f(-2.11f, -0.85f);
    glVertex2f(-2.15f, -0.825f);
    glVertex2f(-2.145f, -0.81f);
    glVertex2f(-2.14f, -0.80f);
    glVertex2f(-2.12f, -0.80f);
    glVertex2f(-2.115f, -0.81f);
    glEnd(); glBegin(GL_POLYGON);
    glVertex2f(-2.14f, -0.80f);
    glVertex2f(-2.18f, -0.775f);
    glVertex2f(-2.175f, -0.76f);
    glVertex2f(-2.17f, -0.75f);
    glVertex2f(-2.15f, -0.75f);
    glVertex2f(-2.155f, -0.76f);
    glEnd(); glColor3f(0.4f, 0.1f, 0.6f); glBegin(GL_TRIANGLES);
    glVertex2f(-2.17f, -0.75f);
    glVertex2f(-2.20f, -0.735f);
    glVertex2f(-2.15f, -0.735f);
    glEnd(); glBegin(GL_TRIANGLES);
    glVertex2f(-2.18f, -0.74f);
    glVertex2f(-2.21f, -0.72f);
    glVertex2f(-2.17f, -0.72f);
    glEnd(); glBegin(GL_TRIANGLES);
    glVertex2f(-2.19f, -0.74f);
    glVertex2f(-2.22f, -0.725f);
    glVertex2f(-2.18f, -0.725f);
    glEnd(); glBegin(GL_TRIANGLES);
    glVertex2f(-2.20f, -0.74f);
    glVertex2f(-2.225f, -0.73f);
    glVertex2f(-2.19f, -0.73f);
    glEnd();

    glPopMatrix();
}



void drawVenus() {
    glPushMatrix();
     glTranslatef(1.275f, 0.6f, 0.0f);
    glRotatef(venusAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.275f, -0.6f, 0.0f);



    // Soft outer glow
    glColor4f(1.0f, 0.6f, 0.2f, 0.05f);
    drawCircle(1.275f, 0.6f, 0.13f);

    // Core body — slightly darker volcanic tone
    glColor3f(0.75f, 0.55f, 0.28f);
    drawCircle(1.275f, 0.6f, 0.11f);

    // === Terrain Patches ===

    // 1. Central fracture
    glColor4f(0.8f, 0.5f, 0.3f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(1.25f, 0.615f); glVertex2f(1.275f, 0.625f); glVertex2f(1.3f, 0.62f);
        glVertex2f(1.31f, 0.6f); glVertex2f(1.3f, 0.58f); glVertex2f(1.275f, 0.575f);
        glVertex2f(1.25f, 0.58f); glVertex2f(1.24f, 0.6f);
    glEnd();

    // 2. Upper left arc
    glColor4f(0.7f, 0.4f, 0.2f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(1.185f, 0.68f); glVertex2f(1.205f, 0.69f); glVertex2f(1.225f, 0.685f);
        glVertex2f(1.245f, 0.68f); glVertex2f(1.255f, 0.665f); glVertex2f(1.235f, 0.655f);
        glVertex2f(1.215f, 0.65f); glVertex2f(1.195f, 0.66f);
    glEnd();

    // 3. Upper right crater
    glColor4f(0.85f, 0.6f, 0.3f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(1.325f, 0.68f); glVertex2f(1.345f, 0.69f); glVertex2f(1.365f, 0.68f);
        glVertex2f(1.355f, 0.66f); glVertex2f(1.335f, 0.655f);
    glEnd();

    // 4. Lower left lava flow
    glColor4f(0.6f, 0.3f, 0.15f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(1.185f, 0.53f); glVertex2f(1.205f, 0.52f); glVertex2f(1.225f, 0.525f);
        glVertex2f(1.235f, 0.54f); glVertex2f(1.215f, 0.55f); glVertex2f(1.195f, 0.545f);
    glEnd();

    // 5. Lower right arc
    glColor4f(0.65f, 0.4f, 0.2f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(1.305f, 0.55f); glVertex2f(1.325f, 0.56f); glVertex2f(1.345f, 0.555f);
        glVertex2f(1.365f, 0.54f); glVertex2f(1.355f, 0.52f); glVertex2f(1.335f, 0.515f);
        glVertex2f(1.315f, 0.525f); glVertex2f(1.295f, 0.535f);
    glEnd();

    // 6. Bottom ridge
    glColor4f(0.55f, 0.3f, 0.15f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(1.245f, 0.505f); glVertex2f(1.305f, 0.505f);
        glVertex2f(1.295f, 0.49f); glVertex2f(1.255f, 0.49f);
        glVertex2f(1.235f, 0.495f);
    glEnd();

    // 7. Upper center ripple
    glColor4f(0.95f, 0.75f, 0.45f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(1.255f, 0.7f); glVertex2f(1.275f, 0.71f); glVertex2f(1.295f, 0.7f);
        glVertex2f(1.305f, 0.68f); glVertex2f(1.285f, 0.67f); glVertex2f(1.265f, 0.68f);
    glEnd();

    // 8. Left edge streak
    glColor4f(0.6f, 0.4f, 0.2f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(1.165f, 0.63f); glVertex2f(1.185f, 0.64f); glVertex2f(1.205f, 0.63f);
        glVertex2f(1.195f, 0.61f); glVertex2f(1.175f, 0.6f);
    glEnd();

    // 9. Right edge streak
    glColor4f(0.7f, 0.5f, 0.3f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(1.385f, 0.57f); glVertex2f(1.365f, 0.56f); glVertex2f(1.345f, 0.57f);
        glVertex2f(1.355f, 0.59f); glVertex2f(1.375f, 0.6f);
    glEnd();

    // 10. Mid-left band
    glColor4f(0.65f, 0.4f, 0.2f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(1.205f, 0.6f); glVertex2f(1.225f, 0.61f); glVertex2f(1.245f, 0.6f);
        glVertex2f(1.235f, 0.585f); glVertex2f(1.215f, 0.58f);
    glEnd();

    glPopMatrix();
}


void drawTheEnd() {
    glColor3f(1.0f, 1.0f, 1.0f); // White text
         glTranslatef(0.3f, 0.1f, 0.0f);
           glScalef(1.6, 1.6, 1.0f);

    // === T ===
    glBegin(GL_POLYGON); // Top bar
        glVertex2f(-0.6f, 0.1f); glVertex2f(-0.5f, 0.1f);
        glVertex2f(-0.5f, 0.05f); glVertex2f(-0.6f, 0.05f);
    glEnd();
    glBegin(GL_POLYGON); // Stem
        glVertex2f(-0.55f, 0.05f); glVertex2f(-0.53f, 0.05f);
        glVertex2f(-0.53f, -0.1f); glVertex2f(-0.55f, -0.1f);
    glEnd();

    // === H ===
    glBegin(GL_POLYGON); // Left bar
        glVertex2f(-0.48f, 0.1f); glVertex2f(-0.46f, 0.1f);
        glVertex2f(-0.46f, -0.1f); glVertex2f(-0.48f, -0.1f);
    glEnd();
    glBegin(GL_POLYGON); // Right bar
        glVertex2f(-0.42f, 0.1f); glVertex2f(-0.40f, 0.1f);
        glVertex2f(-0.40f, -0.1f); glVertex2f(-0.42f, -0.1f);
    glEnd();
    glBegin(GL_POLYGON); // Middle bar
        glVertex2f(-0.48f, 0.01f); glVertex2f(-0.40f, 0.01f);
        glVertex2f(-0.40f, -0.01f); glVertex2f(-0.48f, -0.01f);
    glEnd();

    // === E (THE) ===
    glBegin(GL_POLYGON); // Vertical bar
        glVertex2f(-0.36f, 0.1f); glVertex2f(-0.34f, 0.1f);
        glVertex2f(-0.34f, -0.1f); glVertex2f(-0.36f, -0.1f);
    glEnd();
    glBegin(GL_POLYGON); // Top bar
        glVertex2f(-0.34f, 0.1f); glVertex2f(-0.28f, 0.1f);
        glVertex2f(-0.28f, 0.08f); glVertex2f(-0.34f, 0.08f);
    glEnd();
    glBegin(GL_POLYGON); // Middle bar
        glVertex2f(-0.34f, 0.01f); glVertex2f(-0.30f, 0.01f);
        glVertex2f(-0.30f, -0.01f); glVertex2f(-0.34f, -0.01f);
    glEnd();
    glBegin(GL_POLYGON); // Bottom bar
        glVertex2f(-0.34f, -0.08f); glVertex2f(-0.28f, -0.08f);
        glVertex2f(-0.28f, -0.1f); glVertex2f(-0.34f, -0.1f);
    glEnd();

    // === E (END) ===
    glBegin(GL_POLYGON); // Vertical bar
        glVertex2f(-0.22f, 0.1f); glVertex2f(-0.20f, 0.1f);
        glVertex2f(-0.20f, -0.1f); glVertex2f(-0.22f, -0.1f);
    glEnd();
    glBegin(GL_POLYGON); // Top bar
        glVertex2f(-0.20f, 0.1f); glVertex2f(-0.14f, 0.1f);
        glVertex2f(-0.14f, 0.08f); glVertex2f(-0.20f, 0.08f);
    glEnd();
    glBegin(GL_POLYGON); // Middle bar
        glVertex2f(-0.20f, 0.01f); glVertex2f(-0.16f, 0.01f);
        glVertex2f(-0.16f, -0.01f); glVertex2f(-0.20f, -0.01f);
    glEnd();
    glBegin(GL_POLYGON); // Bottom bar
        glVertex2f(-0.20f, -0.08f); glVertex2f(-0.14f, -0.08f);
        glVertex2f(-0.14f, -0.1f); glVertex2f(-0.20f, -0.1f);
    glEnd();

    // === N (relaxed spacing) ===
    glBegin(GL_POLYGON); // Left bar
        glVertex2f(-0.12f, 0.1f); glVertex2f(-0.10f, 0.1f);
        glVertex2f(-0.10f, -0.1f); glVertex2f(-0.12f, -0.1f);
    glEnd();
    glBegin(GL_POLYGON); // Right bar
        glVertex2f(-0.04f, 0.1f); glVertex2f(-0.02f, 0.1f);
        glVertex2f(-0.02f, -0.1f); glVertex2f(-0.04f, -0.1f);
    glEnd();
    glBegin(GL_POLYGON); // Diagonal fill (top-left to bottom-right)
        glVertex2f(-0.10f, 0.1f); glVertex2f(-0.08f, 0.1f);
        glVertex2f(-0.02f, -0.1f); glVertex2f(-0.04f, -0.1f);
    glEnd();

    // === D ===
    glBegin(GL_POLYGON); // Outer vertical bar
        glVertex2f(0.0f, 0.1f); glVertex2f(0.03f, 0.1f);
        glVertex2f(0.03f, -0.1f); glVertex2f(0.0f, -0.1f);
    glEnd();
    glBegin(GL_POLYGON); // Outer curve
        glVertex2f(0.03f, 0.1f); glVertex2f(0.07f, 0.08f);
        glVertex2f(0.09f, 0.04f); glVertex2f(0.10f, 0.0f);
        glVertex2f(0.09f, -0.04f); glVertex2f(0.07f, -0.08f);
        glVertex2f(0.03f, -0.1f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Inner black D
    glBegin(GL_POLYGON); // Inner vertical bar
        glVertex2f(0.01f, 0.07f); glVertex2f(0.035f, 0.07f);
        glVertex2f(0.035f, -0.07f); glVertex2f(0.01f, -0.07f);
    glEnd();
    glBegin(GL_POLYGON); // Inner curve
        glVertex2f(0.035f, 0.07f); glVertex2f(0.055f, 0.055f);
        glVertex2f(0.07f, 0.03f); glVertex2f(0.075f, 0.0f);
        glVertex2f(0.07f, -0.03f); glVertex2f(0.055f, -0.055f);
        glVertex2f(0.035f, -0.07f);
    glEnd();
}




void display1() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 0.1f);




     glColor3f(0.82f, 0.82f, 0.85f);
    drawCircle(0.0f, -9.75f, 9.0f);


    displaystar();


    drawCrater();
    CreateEarth();
    drawSun();

     drawSatellite();




    drawUFO();
     if(scoutbool==true)
   {
     drawScoutE_Mk1();

   }

    // drawAsteroidAt();
    drawVenus();


   drawAsteroidAt(asteroid1X, asteroid1Y);
drawAsteroidAt(asteroid2X, asteroid2Y);
drawAsteroidAt(asteroid3X, asteroid3Y);
drawAsteroidAt(asteroid4X, asteroid4Y);



   drawRocket();
    drawMonster();


     if(monsterX>3.8)
     {
     drawTheEnd();
     }





    glutSwapBuffers();
}




 void robot_animation() {
    scoutX += scoutSpeedX; // Always move in X


    // Update Y only until it reaches the target depth
    if (scoutY > -0.22f) {
        scoutY = (-0.5f) * (scoutX - 0.16f); // Your original equation
         flagY = scoutY;
    }

    if ( scoutSpeedX > 0.0f )
    {
         flagX = scoutX;
         flagY = scoutY;

    }

    if (scoutX > 1.4f)
    {
        scoutSpeedX = 0.0f;
    }


    if ( scoutSpeedX == 0.0f )
    {
       if(scoutX > 1.1f)
        scoutX -= 0.0006f;

    }

}

void ornob_idle()
{
     // Ufo animation
      ufoX += ufoSpeed;
       if (ufoscale >= 0.00f)  ufoscale -= 0.0002f;

     if (ufoX >= 1.00f) ufoX = 1.00f;


     //Sun animation
     rayRotation += 0.05f;  // Rotate sun rays slowly
    if (rayRotation >= 360.0f) rayRotation -= 360.0f;

    earthRotation += 0.02f; // Rotate Earth slowly
    if (earthRotation >= 360.0f) earthRotation -= 360.0f;



    // Sattelite animation
    satelliteX += satelliteSpeed;

     // Bounce back at edges
    if (satelliteX > -1.25f || satelliteX < -1.40f)
        satelliteSpeed = -satelliteSpeed;


    // Rocket + Stairs + Robot animation
     rocketY += rocketSpeed;
    if (rocketY < -1.40f)
    {
        rocketSpeed = 0.0f; // Stops at Y = 2.0
         stairDeploying = true;

    }

if (stairDeploying && stairLength < 0.90f) {
    stairLength += 0.004f; // Controls how far the stair extends
}


   if(stairLength > 0.88f)
   {
       scoutbool= true;
       robot_animation();

   }


    //rocket flame
    if (flameUp) {
    upperFlameOffset += 0.0008f;
    if (upperFlameOffset > 0.015f) flameUp = false;
} else {
    upperFlameOffset -= 0.0008f;
    if (upperFlameOffset < -0.015f) flameUp = true;
}
    //lower flame
    if (lowerFlameUp) {
    lowerFlameOffset += 0.0008f;
    if (lowerFlameOffset > 0.015f) lowerFlameUp = false;
} else {
    lowerFlameOffset -= 0.0008f;
    if (lowerFlameOffset < -0.015f) lowerFlameUp = true;
}


   /*
  // robot animation
      // Scout horizontal movement (bounce between -0.20 and 0.20)
    scoutX += scoutSpeedX;
    if (scoutX > 0.20f || scoutX < -0.20f) scoutSpeedX = -scoutSpeedX;

    // Optional vertical motion
    scoutY += scoutSpeedY;

     */



// venus rotation

   venusAngle += 0.05f; // Adjust speed as needed
    if (venusAngle > 360.0f) venusAngle -= 360.0f;


}


int scene = 0;


void idle() {

     if(scene == 0)
     {
          alamin_idle();
     }
     else if (scene == 1)
     {
          marium_idle();
     }


     else if (scene ==2)
     {
          ornob_idle();
     }

    glutPostRedisplay();
}



void updatemonster(int value) {

    //Monster
     monsterX += monsterSpeed;
      if (mouthOpening) {
        mouthOffset += 0.0008f;
        if (mouthOffset > 0.01f) mouthOpening = false;
    } else {
        mouthOffset -= 0.0008f;
        if (mouthOffset < -0.01f) mouthOpening = true;
    }


    if(monsterX > 1.7f)
    {
      scoutmonsX += 0.002f;
      scoutmonsY -= 0.0002f;

      if(monsterX > 2.0f)
        {
            monsterY -= 0.0001f;
        }


    }
    glutPostRedisplay();
    glutTimerFunc(16,updatemonster , 0);

}



void updateAstroid1(int value) {
    // Asteroid 1
    asteroid1X += asteroid1SpeedX;
    asteroid1Y += asteroid1SpeedY;
    if (asteroid1X > 4.0f || asteroid1X < -4.0f || asteroid1Y > 3.5f || asteroid1Y < -3.5f) {
        asteroid1X = -3.0f;
        asteroid1Y = -1.3f;
    }

   /* /
    // Asteroid 3
    asteroid3X += asteroid3SpeedX;
    asteroid3Y += asteroid3SpeedY;
    if (asteroid3X > 4.0f || asteroid3X < -4.0f || asteroid3Y > 3.5f || asteroid3Y < -3.5f) {
        asteroid3X = -1.9f; // Corrected initial position
        asteroid3Y = 0.7f;
    }

    // Asteroid 4
    asteroid4X += asteroid4SpeedX;
    asteroid4Y += asteroid4SpeedY;
    if (asteroid4X > 4.0f || asteroid4X < -4.0f || asteroid4Y > 3.5f || asteroid4Y < -3.5f) {
        asteroid4X = 1.8f; // Corrected initial position
        asteroid4Y = -0.6f;
    }

    */

    glutPostRedisplay();
    glutTimerFunc(16, updateAstroid1, 0); // Reschedule with any value (e.g., 0)
}


void updateAstroid2(int value)
{

    // Asteroid 2
    asteroid2X += asteroid2SpeedX;
    asteroid2Y += asteroid2SpeedY;
    if (asteroid2X > 4.0f || asteroid2X < -4.0f || asteroid2Y > 3.5f || asteroid2Y < -3.5f) {
        asteroid2X = 3.0f; // Corrected initial position (was 1.2f, 0.9f in your code)
        asteroid2Y = 2.1f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, updateAstroid2, 0);


}



void updateAstroid(int value)

{
     glutTimerFunc(2000, updateAstroid1, 0);
     glutTimerFunc(34000, updateAstroid2, 0);

}

// ------------------- Reshape -------------------

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height)
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    else
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
}




void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            scene = 1;
            glutTimerFunc(0,updateM, 0);
            break;
        case 's':
            scene = 2;
            glutTimerFunc(50000, updatemonster, 0);
            glutTimerFunc(1000, updateAstroid, 0);
            break;


    }
    glutPostRedisplay();
}





void displaymain()
{
   if(scene == 0)
      {
           display();
      }
    else if (scene == 1)
    {
        displaymarium();
    }
    else if (scene == 2)
    {
        display1();
    }

}



//0000000000000000000000000000000000000000000000000000000000000000000000000000


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1300, 700);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Animated UFO");

    glutDisplayFunc(displaymain);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutTimerFunc(15000,update, 0);
sndPlaySound("al.wav",SND_ASYNC);
     glutKeyboardFunc(handleKeypress);
    initGL();
    glutMainLoop();
    return 0;
}


