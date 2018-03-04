
//
// This is a testing proof of concept software that selects every pixel within
// a triangle using the Kary-Tabesh Curve to show that the system is working.
//
// This demo
//      Copyright 2018 - Pouya Kary, All Rights Reserved.
// Kary-Tabesh Curve
//      Copyright 2011 - Pouya Kary and Armin Tabesh. All Rights Resverd.
//

//
// ─── IMPORTS ────────────────────────────────────────────────────────────────────
//

    #ifdef __APPLE__
        #include <GLUT/glut.h>
        #include <stdlib.h>
    #else
        #include <GL/glut.h>
    #endif

    #include <math.h>
    #include <time.h>
    #include <iostream>
    #include <vector>

//
// ─── TYPES ──────────────────────────────────────────────────────────────────────
//

    struct Point {
        float x;
        float y;
    };

    struct Line {
        Point start;
        Point end;
    };

//
// ─── SETTING CONSTANTS ──────────────────────────────────────────────────────────
//

    // window
    const int screen_width =
        800;
    const int screen_height =
        500;

    // triangle
    struct Point topPosition =
        { 400, 100 };
    struct Point bottomLeftPosition =
        { 300, 400 };
    struct Point bottomRightPosition =
        { 600, 350 };

    // trangle edges
    struct Line edge1 =
        { topPosition, bottomLeftPosition };
    struct Line edge2 =
        { bottomLeftPosition, bottomRightPosition };
    struct Line edge3 =
        { bottomRightPosition, topPosition };

    const std::vector<Line> edges =
        { edge1, edge2, edge3 };

    // origin
    struct Point origin =
        { 0, 0 };

//
// ─── DO LINES INTERSECT ─────────────────────────────────────────────────────────
//

    bool lines_are_intesecting( Line a, Line b ) {
        const auto p1 =
            a.start;
        const auto p2 =
            a.end;
        const auto q1 =
            b.start;
        const auto q2 =
            b.end;

        return (((q1.x-p1.x)*(p2.y-p1.y) - (q1.y-p1.y)*(p2.x-p1.x))
                * ((q2.x-p1.x)*(p2.y-p1.y) - (q2.y-p1.y)*(p2.x-p1.x)) < 0)
                &&
            (((p1.x-q1.x)*(q2.y-q1.y) - (p1.y-q1.y)*(q2.x-q1.x))
                * ((p2.x-q1.x)*(q2.y-q1.y) - (p2.y-q1.y)*(q2.x-q1.x)) < 0);
    }


//
// ─── KARY TABESH CURVE TEST ─────────────────────────────────────────────────────
//

    bool test_interpolation_using_kary_tabesh_curve ( Point point ) {
        const Line test_line =
            { origin, point };

        int sign = 1;
        for ( auto edge : edges )
            if ( lines_are_intesecting( test_line, edge ) )
                sign = sign * -1;

        return sign == -1;
    }

//
// ─── CREATE TRIANGLE BASED ON THE FORMULA ───────────────────────────────────────
//

    void test_pixels_with_the_formula ( ) {
        glColor4f( 1.0f , 0.0f , 0.0f, 0.3f );
        for ( float x = 0; x < screen_width; x++ ) {
            glBegin( GL_POINTS );
                for ( float y = 0; y < screen_height; y++ ) {
                    struct Point point =
                        { x, y };

                    if ( test_interpolation_using_kary_tabesh_curve( point ) ) {
                        glVertex2f( point.x, point.y );
                    }
                }
            glEnd( );
            glFlush( );
        }
    }

//
// ─── DISPLAY VIEW ───────────────────────────────────────────────────────────────
//

    void display ( ) {
        test_pixels_with_the_formula( );
        glFlush( );
    }

//
// ─── INIT ───────────────────────────────────────────────────────────────────────
//

    void init ( ) {
        glClearColor( 0.0, 0.0, 0.0, 1.0 );
             glClear( GL_COLOR_BUFFER_BIT );
           glColor4f( 1.0, 1.0, 1.0, 1.0 );
             glOrtho( 0.f, screen_width, screen_height, 0.f, 0.f, 1.f );
    }

//
// ─── MAIN ───────────────────────────────────────────────────────────────────────
//

    int main ( int argc, char ** argv ) {
                      glutInit( &argc, argv );
           glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
            glutInitWindowSize( screen_width, screen_height );
        glutInitWindowPosition( 100, 100);
              glutCreateWindow( "Kary-Tabesh Curve - Triangle Selector" );
                          init( );
               glutDisplayFunc( display );
                  glutMainLoop( );

        return 0;
    }

// ────────────────────────────────────────────────────────────────────────────────
