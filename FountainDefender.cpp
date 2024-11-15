#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

const float kRadius = 1.5f;
const int kTeethCount = 10;
#define M_PI 3.14159265358979323846
float gRotationAngle = 0.0f; // Current rotation angle
float gTranslationX = 0.0f; // Current translation in X-axis
float gTranslationY = 0.0f; // Current translation in Y-axis

float ballRadius = 0.5;
float ballX = 10.0, ballY = 10.0;
float ballSpeed = 0.09;
float t = 0;
int flag = 0;
float count=0;

void DrawGear ()
{
 const float kAngleStep = 2.0f * M_PI / kTeethCount;
 glBegin (GL_QUADS);
 for (int i = 0; i <= kTeethCount; ++i)
 {
 float angle = i * kAngleStep;
 float x = kRadius * cos(angle);
 float y = kRadius * sin(angle);
 glColor3f (1.0 * i, i * 1.0, i * 0.0);
 glVertex2f (x, y);
 glVertex2f ((0.7f * kRadius) * cos (angle + kAngleStep /
2.0f), (0.7f * kRadius) * sin (angle + kAngleStep / 2.0f));
 }
 glEnd ();
}
void spin()
{
 t += 0.01;
 glutPostRedisplay ();
}
void Display ()
{
 bool visible = true;
 float a = rand () % 9, b = rand () % 11;
 glClear (GL_COLOR_BUFFER_BIT |
GL_DEPTH_BUFFER_BIT);

 glPushMatrix ();
 glPointSize (3);
 glColor3f (1.0, 1.0, 1.0);
 glBegin (GL_POINTS);
 glVertex2f (a, b);
 glEnd ();
 glPopMatrix ();
 glPushMatrix ();
 glTranslatef (gTranslationX, gTranslationY, -0.2f); // Apply translation
 glRotatef (gRotationAngle, 0.0f, 0.0f, 1.0f); // Applyrotation
 glColor3f (1.0f, 1.0f, 0.0f); // Red color
 glutWireSphere (0.9f, 10, 10);
 DrawGear();
 glPopMatrix ();
 glPushMatrix ();
 glTranslatef (ballX, ballY, 0.0);
 glColor3f (0.9, 0.2, 0.0);
 glBegin(GL_TRIANGLE_FAN);
 glVertex2f (0.0, 0.0);
 for (int i = 0; i <= 360; i++)
 {
 float angle = i * 3.14159 / 180.0;
 float x = ballRadius * cos(angle);
 float y = ballRadius * sin(angle);
 glVertex2f(x, y);
 }
 glEnd ();
 glPopMatrix ();
 glPushMatrix ();
 glLoadIdentity ();
 glTranslatef (5.0, -10.0, 0.0);
 glRotatef (t, 0.0, -1, 0.0);
 glColor3f (0.0, 0.0, 1);
 glutSolidSphere (6, 50, 50);
 glColor3f (1.0, 1.0, 1);
 glRotatef (90, 1, 0, 0);
 glutWireSphere (6.1, 17, 18);
 glPopMatrix ();
 glutSwapBuffers();
}
void Reshape (int width, int height)
{
 glViewport (0, 0, width, height);
 glMatrixMode (GL_PROJECTION);
 glLoadIdentity ();
 glOrtho (-1.0f, 11.0f, -10.0f, 10.0f, -30.0f, 20.0f);
 glMatrixMode (GL_MODELVIEW);
 glLoadIdentity ();
}
void Timer (int value)
{
 gRotationAngle += 20.0f;
 if (gRotationAngle >= 360.0f)
 gRotationAngle -= 360.0f;
 glutPostRedisplay ();
 glutTimerFunc (16, Timer, 0);
}
void updateBall (int value)
{
 ballY -= ballSpeed;
 if (ballY < -10.0 + ballRadius || ((int)ballY ==
(int)gTranslationY & (int)ballX == (int)gTranslationX))
 {
 // Reset the ball position
 if (ballY < -10.0)
 {
 count += 1;
 }
 ballY = 10.0;
 ballX = rand () % 10;
 }

 glutPostRedisplay ();
 glutTimerFunc (10, updateBall, 0);
}
void Keyboard (unsigned char key, int x, int y)
{
 switch (key)
 {
 case '8': // Move gear wheel up
 gTranslationY += 1.0f;
 break;
 case '2': // Move gear wheel down
 gTranslationY -= 1.0f;
 break;
 case '4': // Move gear wheel left
 gTranslationX -= 1.0f;
 break;
 case '6': // Move gear wheel right
 gTranslationX += 1.0f;
 break;
 }
 glutPostRedisplay ();
}
int main (int argc, char **argv)
{
 glutInit (&argc, argv);
 glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
 glutInitWindowSize (2000, 2000);
 glutCreateWindow ("The Defender");
 glutDisplayFunc (Display);
 glutReshapeFunc (Reshape);
 glutTimerFunc(0, Timer, 0);
 glutTimerFunc(10, updateBall, 0);
 glutKeyboardFunc (Keyboard);
 glutIdleFunc(spin);
 glClearColor (0.0f, 0.0f, 0.08f, 0.0f);
 glutMainLoop ();
 return 0;
}
