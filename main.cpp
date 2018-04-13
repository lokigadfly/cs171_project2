#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "/Users/gadflyloki/Desktop/桌面潜逃/学习总览/正在学习/计算机图形学/linux/assignment/inc/shader_m.h"
//#include "/Users/gadflyloki/chengxu/test/test/camera.h"

#include "/Users/gadflyloki/chengxu/test的副本/test/bezier/mlbezier.h"
#include "/Users/gadflyloki/chengxu/test的副本/test/stb_image.h"


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

float xoffset,yoffset;
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void jisuan();
// camera
glm::vec3 cameraPos =glm::vec3(0.0f,0.0f,-7.5f);
glm::vec3 Position=glm::vec3(0.0f,0.0f,-7.5f);
glm::vec3 Front = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 Up=glm::vec3(0.0f,1.0f,0.0f);
//Camera camera(glm::vec3(0.0f, 0.0f, -7.5f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

bool dragFlag = false;
float deltaTime = 0.0f; // µ±Ç°Ö¡ÓëÉÏÒ»Ö¡µÄÊ±¼ä²î
float lastFrame = 0.0f; // ÉÏÒ»Ö¡µÄÊ±¼ä
mlBezier mlbezier;


void jisuan(GLfloat xx1,GLfloat yy1,GLfloat zz1,GLfloat xx2,GLfloat yy2,GLfloat zz2,GLfloat xx3,GLfloat yy3,GLfloat zz3,GLfloat centerpoint[3]){
    
    GLfloat a1, b1, c1, d1;
    GLfloat a2, b2, c2, d2;
    GLfloat a3, b3, c3, d3;
    
    GLfloat x1 = xx1, y1 = yy1, z1 = zz1;
    GLfloat x2 = xx2, y2 = yy2, z2 = zz2;
    GLfloat x3 = xx3, y3 = yy3, z3 = zz3;
    
    a1 = (y1*z2 - y2*z1 - y1*z3 + y3*z1 + y2*z3 - y3*z2);
    b1 = -(x1*z2 - x2*z1 - x1*z3 + x3*z1 + x2*z3 - x3*z2);
    c1 = (x1*y2 - x2*y1 - x1*y3 + x3*y1 + x2*y3 - x3*y2);
    d1 = -(x1*y2*z3 - x1*y3*z2 - x2*y1*z3 + x2*y3*z1 + x3*y1*z2 - x3*y2*z1);
    
    a2 = 2 * (x2 - x1);
    b2 = 2 * (y2 - y1);
    c2 = 2 * (z2 - z1);
    d2 = x1 * x1 + y1 * y1 + z1 * z1 - x2 * x2 - y2 * y2 - z2 * z2;
    
    a3 = 2 * (x3 - x1);
    b3 = 2 * (y3 - y1);
    c3 = 2 * (z3 - z1);
    d3 = x1 * x1 + y1 * y1 + z1 * z1 - x3 * x3 - y3 * y3 - z3 * z3;
    
    centerpoint[0] = -(b1*c2*d3 - b1*c3*d2 - b2*c1*d3 + b2*c3*d1 + b3*c1*d2 - b3*c2*d1)
    /(a1*b2*c3 - a1*b3*c2 - a2*b1*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1);
    centerpoint[1] =  (a1*c2*d3 - a1*c3*d2 - a2*c1*d3 + a2*c3*d1 + a3*c1*d2 - a3*c2*d1)
    /(a1*b2*c3 - a1*b3*c2 - a2*b1*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1);
    centerpoint[2] = -(a1*b2*d3 - a1*b3*d2 - a2*b1*d3 + a2*b3*d1 + a3*b1*d2 - a3*b2*d1)
    /(a1*b2*c3 - a1*b3*c2 - a2*b1*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1);
    
}
GLfloat distance3d(GLfloat a1,GLfloat b1,GLfloat c1,GLfloat a2,GLfloat b2,GLfloat c2){
    GLfloat distance;
    distance=sqrt((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2)+(c1-c2)*(c1-c2));
    return distance;
}


void drawControlPoint(mlBezier &mlbezier)
{
    glBegin(GL_QUADS);
    
    for (int i = 0; i < (int)mlbezier.indicesofControlpoints.size() / 4; i++)
    {
        glColor3f(0, 1, 0);
        glVertex3f
        (
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i]].x,
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i]].y,
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i]].z
         );
        glVertex3f
        (
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i + 1]].x,
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i + 1]].y,
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i + 1]].z
         );
        glVertex3f
        (
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i + 2]].x,
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i + 2]].y,
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i + 2]].z
         );
        glVertex3f
        (
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i + 3]].x,
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i + 3]].y,
         mlbezier.controlPoints[mlbezier.indicesofControlpoints[4 * i + 3]].z
         );
    }
    glEnd();
}
void drawBezierSurface(mlBezier &mlbezier)
{
    int n = 5;//number
    float xarray[4];
    float yarray[4];
    float zarray[4];
    GLfloat ps[11][5][3];
    for (int v=0;v<5;v++){
        int u=0;
        for (double t=0.0;t<=1;t+=0.1){
            for (int i=1;i<n;++i){
                for (int j=0;j<n-i;++j){
                    if (i==1){
                        xarray[j]=mlbezier.controlPoints[j*5+v].x* (1 - t)+mlbezier.controlPoints[(j+1)*5+v].x* t;
                        yarray[j]=mlbezier.controlPoints[j*5+v].y* (1 - t)+mlbezier.controlPoints[(j+1)*5+v].y* t;
                        zarray[j]=mlbezier.controlPoints[j*5+v].z* (1 - t)+mlbezier.controlPoints[(j+1)*5+v].z* t;
                        continue;
                    }
                    xarray[j]=xarray[j]*(1-t)+xarray[j+1]*t;
                    yarray[j]=yarray[j]*(1-t)+yarray[j+1]*t;
                    zarray[j]=zarray[j]*(1-t)+zarray[j+1]*t;
                }
            }
            ps[u][v][0] = xarray[0];
            ps[u][v][1] = yarray[0];
            ps[u][v][2] = zarray[0];
            u++;
        }
    }
    GLfloat ps1[11][11][3];
    GLfloat normalx[11][11];
    GLfloat normaly[11][11];
    GLfloat normalz[11][11];
    glm::vec3 normal[11][11];
    for (int v=0;v<11;v++){
        int u =0;
        for (double t=0.0;t<=1;t+=0.1){
            for (int i=1;i<n;++i){
                for (int j=0;j<n-i;++j){
                    if (i==1){
                    xarray[j] = ps[v][j][0] * (1 - t) + ps[v][j + 1][0] * t;
                    yarray[j] = ps[v][j][1] * (1 - t) + ps[v][j + 1][1] * t;
                    zarray[j] = ps[v][j][2] * (1 - t) + ps[v][j + 1][2] * t;
                    continue;
                    }
                    xarray[j] = xarray[j] * (1 - t) + xarray[j + 1] * t;
                    yarray[j] = yarray[j] * (1 - t) + yarray[j + 1] * t;
                    zarray[j] = zarray[j] * (1 - t) + zarray[j + 1] * t;
//                    normalx[]
                }
            }
            normalx[v][u]=xarray[0]-xarray[1];
            normaly[v][u]=yarray[0]-yarray[1];
            normalz[v][u]=zarray[0]-zarray[1];
            normal[v][u]=glm::vec3(normalx[v][u],normaly[v][u],normalz[v][u]);
            ps1[v][u][0] = xarray[0];
            ps1[v][u][1] = yarray[0];
            ps1[v][u][2] = zarray[0];
            u++;
        }
    }
    glm::vec3 newcontrolpoints[25];
    for (int i=0;i<5;i++)
    {
        for (int j=0;j<4;j++){
            newcontrolpoints[5*j+i]=mlbezier.controlPoints[5*i+j];
        }
    }
    
    for (int v=0;v<4;v++){
        int u=0;
        for (double t=0.0;t<=1;t+=0.1){
            for (int i=1;i<n;++i){
                for (int j=0;j<n-i;++j){
                    if (i==1){
                        xarray[j]=newcontrolpoints[j*5+v].x* (1 - t)+newcontrolpoints[(j+1)*5+v].x* t;
                        yarray[j]=newcontrolpoints[j*5+v].y* (1 - t)+newcontrolpoints[(j+1)*5+v].y* t;
                        zarray[j]=newcontrolpoints[j*5+v].z* (1 - t)+newcontrolpoints[(j+1)*5+v].z* t;
                        continue;
                    }
                    xarray[j]=xarray[j]*(1-t)+xarray[j+1]*t;
                    yarray[j]=yarray[j]*(1-t)+yarray[j+1]*t;
                    zarray[j]=zarray[j]*(1-t)+zarray[j+1]*t;
                }
            }
            ps[u][v][0] = xarray[0];
            ps[u][v][1] = yarray[0];
            ps[u][v][2] = zarray[0];
            u++;
        }
    }

    GLfloat normal2x[11][11];
    GLfloat normal2y[11][11];
    GLfloat normal2z[11][11];
    glm::vec3 normal2[11][11];
    for (int v=0;v<11;v++){
        int u =0;
        for (double t=0.0;t<=1;t+=0.1){
            for (int i=1;i<n;++i){
                for (int j=0;j<n-i;++j){
                    if (i==1){
                        xarray[j] = ps[v][j][0] * (1 - t) + ps[v][j + 1][0] * t;
                        yarray[j] = ps[v][j][1] * (1 - t) + ps[v][j + 1][1] * t;
                        zarray[j] = ps[v][j][2] * (1 - t) + ps[v][j + 1][2] * t;
                        continue;
                    }
                    xarray[j] = xarray[j] * (1 - t) + xarray[j + 1] * t;
                    yarray[j] = yarray[j] * (1 - t) + yarray[j + 1] * t;
                    zarray[j] = zarray[j] * (1 - t) + zarray[j + 1] * t;
                    //                    normalx[]
                }
            }
            normal2x[v][u]=xarray[0]-xarray[1];
            normal2y[v][u]=yarray[0]-yarray[1];
            normal2z[v][u]=zarray[0]-zarray[1];
            normal2[v][u]=glm::vec3(normal2x[v][u],normal2y[v][u],normal2z[v][u]);
            u++;
        }
    }
    glm::vec3 finalnormal[11][11];
    for (int i=0;i<11;i++){
        for (int j=0;j<11;j++){
            finalnormal[i][j]=glm::normalize(glm::cross(normal[i][j],normal2[j][i]));
        }
    }
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glEnable( GL_LINE_SMOOTH );
//    float rotate = glfwGetTime()*30;
//    glRotatef(rotate, 0.0, 1.0, 0.0);
    
    for (int y=0;y<10;y++){
        for (int x=0;x<10;x++){
            
            GLfloat *centerpoint = new GLfloat[3];
            jisuan(ps1[y][x][0],ps1[y][x][1],ps1[y][x][2],ps1[y][x+1][0],ps1[y][x+1][1],ps1[y][x+1][2],ps1[y+1][x+1][0],ps1[y+1][x+1][1],ps1[y+1][x+1][2],centerpoint);
            
            // 先算出外心
            // 点到点距离函数调用
            GLfloat distance;
            distance=distance3d(centerpoint[0],centerpoint[1],centerpoint[2],ps1[y][x][0],ps1[y][x][1],ps1[y][x][2]);
            
            GLfloat diffe;
            diffe=(ps1[y+1][x][0]-centerpoint[0])*(ps1[y+1][x][0]-centerpoint[0])+(ps1[y+1][x][1]-centerpoint[1])*(ps1[y+1][x][1]-centerpoint[1])+(ps1[y+1][x][2]-centerpoint[2])*(ps1[y+1][x][2]-centerpoint[2])-(distance*distance);
//            std::cout<<diffe<<std::endl;
            
            if (diffe<=0){
                glBegin(GL_TRIANGLES);
                glNormal3f(finalnormal[y][x].x,finalnormal[y][x].y,finalnormal[y][x].z);
                glTexCoord2f(1-(x)/10.0,1-(y)/10.0);
                glVertex3fv(&ps1[y][x][0]);
                
                glNormal3f(finalnormal[y][x+1].x,finalnormal[y][x+1].y,finalnormal[y][x+1].z);
                glTexCoord2f( 1-(x+1)/10.0, 1-y/10.0 );
                glVertex3fv(&ps1[y][x+1][0]);
                
                glNormal3f(finalnormal[y+1][x].x,finalnormal[y+1][x].y,finalnormal[y+1][x].z);
                glTexCoord2f( 1-x/10.0, 1-(y+1)/10.0);
                glVertex3fv(&ps1[y+1][x][0]);
                
                glEnd();
                glBegin(GL_TRIANGLES);
                glNormal3f(finalnormal[y][x+1].x,finalnormal[y][x+1].y,finalnormal[y][x+1].z);
                glTexCoord2f( 1-(x+1)/10.0, 1-y/10.0 );
                glVertex3fv(&ps1[y][x+1][0]);
                glNormal3f(finalnormal[y+1][x+1].x,finalnormal[y+1][x+1].y,finalnormal[y+1][x+1].z);
                glTexCoord2f( 1-(x+1)/10.0, 1-(y+1)/10.0 );
                glVertex3fv(&ps1[y+1][x+1][0]);
                
                
                glNormal3f(finalnormal[y+1][x].x,finalnormal[y+1][x].y,finalnormal[y+1][x].z);
                glTexCoord2f( 1-x/10.0, 1-(y+1)/10.0);
                glVertex3fv(&ps1[y+1][x][0]);
                glEnd();
                
            }else{
                glBegin(GL_TRIANGLES);
                glNormal3f(finalnormal[y][x].x,finalnormal[y][x].y,finalnormal[y][x].z);
                glTexCoord2f(1-(x)/10.0,1-(y)/10.0);
                glVertex3fv(&ps1[y][x][0]);
                
                glNormal3f(finalnormal[y][x+1].x,finalnormal[y][x+1].y,finalnormal[y][x+1].z);
                glTexCoord2f( 1-(x+1)/10.0, 1-y/10.0 );
                glVertex3fv(&ps1[y][x+1][0]);
                
                glNormal3f(finalnormal[y+1][x+1].x,finalnormal[y+1][x+1].y,finalnormal[y+1][x+1].z);
                glTexCoord2f( 1-(x+1)/10.0, 1-(y+1)/10.0 );
                glVertex3fv(&ps1[y+1][x+1][0]);
                
                glEnd();
                glBegin(GL_TRIANGLES);
                glNormal3f(finalnormal[y+1][x+1].x,finalnormal[y+1][x+1].y,finalnormal[y+1][x+1].z);
                glTexCoord2f( 1-(x+1)/10.0, 1-(y+1)/10.0 );
                glVertex3fv(&ps1[y+1][x+1][0]);
                
                
                glNormal3f(finalnormal[y+1][x].x,finalnormal[y+1][x].y,finalnormal[y+1][x].z);
                glTexCoord2f( 1-x/10.0, 1-(y+1)/10.0);
                glVertex3fv(&ps1[y+1][x][0]);
                glNormal3f(finalnormal[y][x].x,finalnormal[y][x].y,finalnormal[y][x].z);
                glTexCoord2f(1-(x)/10.0,1-(y)/10.0);
                glVertex3fv(&ps1[y][x][0]);
                   glEnd();
                
            }
//            glBegin(GL_QUADS);
//
//            glNormal3f(finalnormal[y][x].x,finalnormal[y][x].y,finalnormal[y][x].z);
//            glTexCoord2f(1-(x)/10.0,1-(y)/10.0);
//            glVertex3fv(&ps1[y][x][0]);
//
//            glNormal3f(finalnormal[y][x+1].x,finalnormal[y][x+1].y,finalnormal[y][x+1].z);
//            glTexCoord2f( 1-(x+1)/10.0, 1-y/10.0 );
//            glVertex3fv(&ps1[y][x+1][0]);
//
//            glNormal3f(finalnormal[y+1][x+1].x,finalnormal[y+1][x+1].y,finalnormal[y+1][x+1].z);
//            glTexCoord2f( 1-(x+1)/10.0, 1-(y+1)/10.0 );
//            glVertex3fv(&ps1[y+1][x+1][0]);
//
//
//            glNormal3f(finalnormal[y+1][x].x,finalnormal[y+1][x].y,finalnormal[y+1][x].z);
//            glTexCoord2f( 1-x/10.0, 1-(y+1)/10.0);
//            glVertex3fv(&ps1[y+1][x][0]);
//
//            glEnd();
        }
    }
    glPopMatrix();
    glFlush();
}


void initPMV()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60, SCR_WIDTH / SCR_HEIGHT, 0.1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt
    (
     cameraPos[0],cameraPos[1],cameraPos[2],
     0, 0, 0,
     0, 1, 0
     );
}


void AddLight(mlBezier &mlbezier)
{
    
}
void initTexture(unsigned int &texture)
{
    //glLoadIdentity();
    int width, height, nrChannels;
    unsigned char *data = stbi_load("/Users/gadflyloki/chengxu/test的副本/test/img.jpg", &width, &height, &nrChannels, 0);
    glEnable(GL_TEXTURE_2D);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //bind it to texture
    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
    
    

int main()
{
    glfwInit();
    
    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "hello", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glewExperimental = GL_TRUE;
    glewInit();
    glfwSetCursorPosCallback(window, mouse_callback);
    
    
    //mlBezier mlbezier;
    mlbezier.divs = 25;
    mlbezier.mlCreateBeizermesh();
    mlbezier.mlTriangularization();
    
    initPMV();
     glEnable(GL_DEPTH_TEST);
    glm::vec3 record;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        
        GLfloat sun_light_position[] = { 0.0f, 0.0f, -10.0f, 0.0f };
        GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat sun_light_specular[] = { 1.0f, 1.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f };
        GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
        GLfloat earth_mat_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat earth_mat_shininess = 30.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
        glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
        glPointSize(5);
        
        //texture start
        unsigned int texture = 0;
//        initTexture(texture);
//        int width, heigh;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        drawControlPoint(mlbezier);
        GLint   viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];
        glGetIntegerv(GL_VIEWPORT, viewport);
        viewport[2]=800;
        viewport[3]=600;
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        double winX = 800-lastX;
        double winY = 600-lastY;
        GLdouble posX, posY, posZ,posX1,posY1,posZ1;

        bool bResult = gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);
        GLfloat nearPoint[3];
        nearPoint[0] = posX; nearPoint[1] = posY; nearPoint[2] = posZ;

        bResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ);
        GLfloat farPoint[3];
        farPoint[0] = posX; farPoint[1] = posY; farPoint[2] = posZ;
        glm::vec3 direPoint,sdirePoint;
        
        direPoint=glm::vec3(nearPoint[0],nearPoint[1],nearPoint[2]+7.5);
        
//        for (int i=0;i<16;i++){
//        sdirePoint=glm::vec3(mlbezier.controlPoints[i].x,mlbezier.controlPoints[i].y,mlbezier.controlPoints[i].z+7.5);
//            GLfloat answer;
//
//            answer=(glm::length(glm::cross(sdirePoint,direPoint)))/(glm::length(direPoint));
//
//            std::cout<<xoffset+lastX<<","<<lastY-yoffset<<std::endl;
//            bool cResult = gluUnProject(xoffset+lastX, lastY-yoffset, 1.0, modelview, projection, viewport, &posX, &posY, &posZ);
//            bool dResult = gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX1, &posY1, &posZ1);
//            std::cout<<posX-posX1<<","<<posY-posY1<<","<<posZ-posZ1<<std::endl;
//            int choice;
//            if (1){
//                choice=i;
//                mlbezier.controlPoints[0].x+=(posX-posX1)*0.0001;
//                mlbezier.controlPoints[0].y+=(posY-posY1)*0.0001;
//                mlbezier.controlPoints[0].z+=(posZ-posZ1)*0.0001;
//                if (answer<0.4)
//                std::cout<<i<<"laile:"<<answer<<std::endl;
//            }
////            mlbezier.controlPoints[i].x+=posX*0.01;
////            mlbezier.controlPoints[i].y+=posY*0.01;
////            mlbezier.controlPoints[i].z+=posZ*0.01;
////            } std::cout<<"laile:"<<(glm::length(glm::cross(sdirePoint,direPoint)))<<" ,"<<answer<<","<<(glm::length(direPoint))<<std::endl;
//        }
//        std::cout<<nearPoint[0]<<","<<nearPoint[1]<<","<<nearPoint[2]<<std::endl;
//         std::cout<<farPoint[0]<<","<<farPoint[1]<<","<<farPoint[2]<<std::endl;
//      for ()
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindTexture(GL_TEXTURE_2D, texture);
        drawBezierSurface(mlbezier);
        processInput(window);
        glDeleteTextures(1,&texture);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{

    
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;

    float velocity = 2.5f * deltaTime;

    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        Position += Front * velocity;
        glLoadIdentity();
        gluLookAt
        (
         Position[0],Position[1],Position[2],
        0, 0,0,
         0, 1, 0
         );
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        Position-= glm::normalize(glm::cross(Front,Up))*velocity;  // circle rotate
        Front = -Position ;
        glLoadIdentity();
        gluLookAt
        (
         Position[0],Position[1],Position[2],
         0, 0, 0,
         0, 1, 0
         );
        
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        Position -= Front * velocity;
        glLoadIdentity();
        gluLookAt
        (
         Position[0],Position[1],Position[2],
         0, 0,0,
         0, 1, 0
         );
    }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    Position+= glm::normalize(glm::cross(Front,Up))*velocity;  // circle rotate
    Front = -Position ;
    glLoadIdentity();
    gluLookAt
    (
     Position[0],Position[1],Position[2],
     0, 0, 0,
     0, 1, 0
     );
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT )){
        xoffset = xpos - lastX;
        yoffset =
    lastY - ypos;  // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    }
    
//    camera.ProcessMouseMovement(xoffset, yoffset);
}

