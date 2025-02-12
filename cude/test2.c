#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PI 3.14159265358979323846
#define WIDTH 160         // 增大终端宽度
#define HEIGHT 80         // 增大终端高度
#define CUBE_SIZE 12.0f   // 增大立方体的大小
#define SPHERE_POINTS 300 // 点数，增大分辨率

// 旋转矩阵函数
void rotate(float *x, float *y, float *z, float angleX, float angleY) {
  // 绕 X 轴旋转
  float tempY = *y;
  *y = *y * cos(angleX) - *z * sin(angleX);
  *z = tempY * sin(angleX) + *z * cos(angleX);

  // 绕 Y 轴旋转
  float tempX = *x;
  *x = *x * cos(angleY) + *z * sin(angleY);
  *z = -tempX * sin(angleY) + *z * cos(angleY);
}

// 投影函数：将 3D 坐标投影到 2D 屏幕
void project(float x, float y, float z, int *px, int *py) {
  // 确保水平和垂直投影比例一致
  float scale = 45.0f / (45.0f + z); // 增加投影比例以适应更大的屏幕
  *px = (int)(x * scale + WIDTH / 2);
  *py = (int)(y * scale + HEIGHT / 2);
}

// 设置彩色输出的函数（使用 256 色）
void setColor(float z) {
  // 使用黄色设置颜色（ANSI 256色）
  printf("\033[38;5;226m"); // 设置前景色为黄色
}

// 清空屏幕并设置背景色
void clearScreen() {
  // 使用 ANSI 转义序列清空屏幕并设置背景色为蓝色
  printf("\033[H\033[J");  // 清空屏幕
  printf("\033[48;5;32m"); // 设置背景色为蓝色
}

// Bresenham 算法绘制直线
void drawLine(int x1, int y1, int x2, int y2, char screen[HEIGHT][WIDTH]) {
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;
  int err = dx - dy;

  while (1) {
    if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT) {
      screen[y1][x1] = '#'; // 绘制直线
    }
    if (x1 == x2 && y1 == y2)
      break;
    int e2 = err * 2;
    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  }
}

// 绘制立方体
void drawCube(float angleX, float angleY) {
  char screen[HEIGHT][WIDTH];

  // 初始化屏幕为 ' '（空格）
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      screen[y][x] = ' ';
    }
  }

  // 定义立方体的 8 个顶点（每个顶点是 (x, y, z)）
  float vertices[8][3] = {
      {-CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE}, {CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
      {CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE},   {-CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE},
      {-CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE},  {CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE},
      {CUBE_SIZE, CUBE_SIZE, CUBE_SIZE},    {-CUBE_SIZE, CUBE_SIZE, CUBE_SIZE}};

  // 旋转并投影每个顶点
  int projectedVertices[8][2];
  for (int i = 0; i < 8; i++) {
    float x = vertices[i][0];
    float y = vertices[i][1];
    float z = vertices[i][2];

    // 旋转顶点
    rotate(&x, &y, &z, angleX, angleY);

    // 投影到屏幕
    int px, py;
    project(x, y, z, &px, &py);
    projectedVertices[i][0] = px;
    projectedVertices[i][1] = py;
  }

  // 连接顶点，绘制立方体的边
  int edges[12][2] = {
      {0, 1}, {1, 2}, {2, 3}, {3, 0}, // 前面
      {4, 5}, {5, 6}, {6, 7}, {7, 4}, // 后面
      {0, 4}, {1, 5}, {2, 6}, {3, 7}  // 连接前后面
  };

  // 绘制每一条边
  for (int i = 0; i < 12; i++) {
    int start = edges[i][0];
    int end = edges[i][1];

    int x1 = projectedVertices[start][0];
    int y1 = projectedVertices[start][1];
    int x2 = projectedVertices[end][0];
    int y2 = projectedVertices[end][1];

    // 根据深度设置颜色
    float z1 = vertices[start][2];
    float z2 = vertices[end][2];
    setColor((z1 + z2) / 2);

    // 使用 Bresenham 算法绘制每条边
    drawLine(x1, y1, x2, y2, screen);
  }

  // 打印屏幕
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (screen[y][x] == '#') {
        putchar('#'); // 绘制立方体的边
      } else {
        putchar(' '); // 空白区域
      }
    }
    putchar('\n');
  }

  // 重置颜色为默认
  printf("\033[0m");
}

int main() {
  float angleX = 0.0f, angleY = 0.0f;

  while (1) {
    clearScreen(); // 清空屏幕并设置背景色为蓝色

    drawCube(angleX, angleY); // 绘制旋转立方体

    // 更新旋转角度
    angleX += 0.01f;
    angleY += 0.01f;

    // 延时，模拟动画效果
    usleep(5000); // 30ms 延时，增加延迟减慢旋转速度
  }

  return 0;
}
