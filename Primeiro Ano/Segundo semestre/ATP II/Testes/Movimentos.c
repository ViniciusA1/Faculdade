#include <stdio.h>
#include <math.h>

double op_1(double v, double t)
{
    return (v * t);
}

double op_2_3(double d, double t_v)
{
    return (d / t_v);
}

double op_4(double v, double a, double t)
{
    return ((v * t) + ((a / 2) * (t*t)));
}

double op_5(double v, double a, double t)
{
    return (v + (a*t));
}

double op_6(double d, double a, double t)
{
    return ((d / t) - ((a * t) / 2));
}

double op_7(double d, double v, double a)
{
    double torri = sqrt((v*v) + (2*a*d));
    return ((torri - v) / a);
}

double verifica(int resp)
{
    double velo, tempo, dist, aclr, result;

    switch(resp) {
        case 1:
            scanf("%lf%lf", &velo, &tempo);
            result = op_1(velo, tempo);
            break;
        case 2:
            scanf("%lf%lf", &dist, &tempo);
            result = op_2_3(dist, tempo);
            break;
        case 3:
            scanf("%lf%lf", &dist, &velo);
            result = op_2_3(dist, velo);
            break;
        case 4:
            scanf("%lf%lf%lf", &velo, &aclr, &tempo);
            result = op_4(velo, aclr, tempo);
            break;
        case 5:
            scanf("%lf%lf%lf", &velo, &aclr, &tempo);
            result = op_5(velo, aclr, tempo);
            break;
        case 6:
            scanf("%lf%lf%lf", &dist, &aclr, &tempo);
            result = op_6(dist, aclr, tempo);
            break;
        default:
            scanf("%lf%lf%lf", &dist, &velo, &aclr);
            result = op_7(dist, velo, aclr);
    }

    return result;
}

int main()
{
    int op, max, i;

    scanf("%d", &max);

    for(i = 0; i < max; i++) {
        scanf("%d", &op);
        printf("%.2lf\n", verifica(op));
    }

    return 0;
}