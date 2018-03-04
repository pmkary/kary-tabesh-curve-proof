
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
    const struct Point topPosition =
        { 400, 100 };
    const struct Point bottomLeftPosition =
        { 300, 400 };
    const struct Point bottomRightPosition =
        { 600, 350 };

    // trangle edges
    const struct Line edge1 =
        { topPosition, bottomLeftPosition };
    const struct Line edge2 =
        { bottomLeftPosition, bottomRightPosition };
    const struct Line edge3 =
        { bottomRightPosition, topPosition };

    const std::vector<Line> edges =
        { edge1, edge2, edge3 };

    // origin
    const struct Point origin =
        { 0, 0 };

//
// ─── DO LINES INTERSECT ─────────────────────────────────────────────────────────
//

    bool lines_are_intesecting( Line a, Line b ) {
        const auto first_condition =
            ( ( ( b.start.x - a.start.x ) * ( a.end.y - a.start.y )
                - ( b.start.y - a.start.y ) * ( a.end.x-a.start.x ) )
              * ( ( b.end.x - a.start.x ) * ( a.end.y - a.start.y )
                - ( b.end.y - a.start.y ) * ( a.end.x - a.start.x ) ) < 0 );

        const auto second_condition =
            ( ( ( a.start.x - b.start.x ) * ( b.end.y-b.start.y )
                - ( a.start.y - b.start.y ) * ( b.end.x-b.start.x ) )
              * ( ( a.end.x - b.start.x ) * ( b.end.y - b.start.y )
                - ( a.end.y - b.start.y ) * ( b.end.x - b.start.x ) ) < 0 );

        return first_condition && second_condition;
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
// ─── DISPLAY VIEW ───────────────────────────────────────────────────────────────
//

    void display ( ) {
        glColor4f( 1.0f , 0.0f , 0.0f, 0.3f );
        glBegin( GL_POINTS );
            for ( float x = 0; x < screen_width; x++ ) {
                for ( float y = 0; y < screen_height; y++ ) {
                    const struct Point point =
                        { x, y };

                    if ( test_interpolation_using_kary_tabesh_curve( point ) )
                        glVertex2f( point.x, point.y );
                }
            }
        glEnd( );
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
