//Jacob Malloy - jmalloy1
//jgraph lab
//code to generate jgraph spirograph
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h> //get DBL_MIN


//some macros. These use the gnu extensions, but I believe that will probably be fine
#define SAFE_DIV(x,y) ({  \
    __typeof__(x) _x = x; \
    __typeof__(y) _y = y; \
    _y==0?_x/DBL_MIN :_x/_y; \
})

#define MAX(x,y) ({  \
    __typeof__(x) _x = x; \
    __typeof__(y) _y = y; \
    _x>_y?_x:_y; \
})

#define BOUND(val,bottom,top) ({  \
    __typeof__(val) _val = val; \
    __typeof__(bottom) _bottom = bottom; \
    __typeof__(top) _top = top; \
    _val<_bottom?_bottom:_val>_top?_top:_val; \
})


//the point structure so it can be passed back easily
struct point{
    double x;
    double y;
};
//simple structure to store the info
struct figure_data{
    long steps,total_steps;
    long R,r,d;
    double red,green,blue;
    double offset_angle;
};

//define constants
const char *header="newgraph \n \
xaxis min %d max %d nodraw \n \
yaxis min %d max %d nodraw \n \
";


const char *new_curve="newcurve marktype none linetype solid color %lf %lf %lf\n    pts\n";


//implement the equations simply
void calc_spiro(double R, double r, double theta, double d,double offset_angle,struct point *return_value){
    double x,y;
    x=(R-r)*cos(theta)+d*cos(SAFE_DIV((R-r)*theta,r));
    y=(R-r)*sin(theta)-d*sin(SAFE_DIV((R-r)*theta,r));
    return_value->x=x*cos(offset_angle)-y*sin(offset_angle);
    return_value->y=x*sin(offset_angle)+y*cos(offset_angle);
}


//eulers algorithm used for gcd to get lcm to find what angle to turn through
int gcd(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}


//function to print all the points for a configurationl
void print_points(long R, long r, long d, double offset_angle, long steps, long total_steps){
    struct point tmp_point;
    double increment_angle;

    increment_angle = (R*r)/gcd(R,r)/R*2.0*M_PI/total_steps;
    for(int i =0;i<=steps;i++){
        calc_spiro(R,r,increment_angle*i,d,offset_angle,&tmp_point);
        printf("%lf %lf ",tmp_point.x,tmp_point.y);
    }
}

int main(){
    struct figure_data *figures;
    int count;
    int max;
    int max_width;

    long red,green,blue;


    figures = malloc(sizeof(struct figure_data)*10);
    count =0;
    max = 10;
    max_width=0;


    //scan in all the info and find the size of the graph needed
    while(scanf("%ld %ld %ld %ld %ld %lf %ld %ld %ld",&figures[count].R,&figures[count].r,&figures[count].d,&figures[count].total_steps,&figures[count].steps,&figures[count].offset_angle,&red,&green,&blue)==9){
        figures[count].offset_angle*=M_PI/180;
        figures[count].red = (double)BOUND(red,0,255)/255;
        figures[count].green = (double)BOUND(green,0,255)/255;
        figures[count].blue = (double)BOUND(blue,0,255)/255;
        max_width = MAX((figures[count].R-figures[count].r)+figures[count].d,max_width);
        count+=1;
        if(count==max){
            max*=2;
            figures=realloc(figures,sizeof(struct figure_data)*max);
        }
    }


    //print the formatted points
    printf(header,-max_width,max_width,-max_width,max_width);
    for(int i =0;i<count;i++){
        printf(new_curve,figures[i].red,figures[i].green,figures[i].blue);
        print_points(figures[i].R,figures[i].r,figures[i].d,figures[i].offset_angle,figures[i].steps,figures[i].total_steps);
        printf("\n");
    }
    free(figures);
}
