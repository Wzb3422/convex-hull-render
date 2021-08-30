#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GLFW/glfw3.h>
struct MyPoint
{
    float x, y;
};

struct MyPoint points[] = {
    {300.0,310.0},
    {300.0,230.0},
    {220.0,220.0},
    {230.0,330.0},
    {210.0, 290.0},
    {240.0, 270.0},
    {130.0,250.0},
    {170.0,260.0},
    {140.0,310.0}
};

int orientation(struct MyPoint p, struct MyPoint q, struct MyPoint r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
 
void convexHull(struct MyPoint points[], int n)
{
    // There must be at least 3 points
    if (n < 3) return;
 
    // Initialize Result
//    vector<Point> hull;
 
    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
    
    int p = l, q;
    do
    {
        // Add current point to result
//        hull.push_back(points[p]);
        
        glVertex2f(points[p].x, points[p].y);

        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {

           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }
 
        // Now q is the most counterclockwise with respect to p
        // Set p as q for next iteration, so that q is added to
        // result 'hull'
        glVertex2f(points[q].x, points[q].y);
        p = q;
 
    } while (p != l);  // While we don't come to first point
 
    // Print Result
//    for (int i = 0; i < hull.size(); i++)
//        cout << "(" << hull[i].x << ", "
//              << hull[i].y << ")\n";
}

void render_loop()
{
    int n = sizeof(points) / sizeof(points[0]);
    
    glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(10);
    glLineWidth(2.5);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glPointSize(1.0);
    
    for (int i = 0; i < n; i++) {
        glVertex2f(points[i].x, points[i].y);
    }
    glEnd();
    // Draw Hull Line
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    convexHull(points, n);
    glEnd();
}

/* program entry */
int main(int argc, char *argv[])
{
    GLFWwindow* window;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow( 400, 400, "LearnOpenGL", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }


    glfwMakeContextCurrent(window);
    glfwSwapInterval( 1 );

    // set up view
    glViewport( 0, 0, 800, 800 );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    // see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
    glOrtho(0.0,400.0,0.0,400.0,0.0,1.0); // this creates a canvas you can do 2D drawing on

    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
        // Draw gears
        render_loop();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    // Exit program
    exit( EXIT_SUCCESS );
}
