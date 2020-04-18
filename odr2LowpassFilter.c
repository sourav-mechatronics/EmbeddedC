  
/*!---------------------------------------------------------------------------------------
 * @brief      moving avarage Filter structure.
 * @author     Sourav Sahoo
 * @date       14 April 2020
 *
 *transfer function H(z):

        H(z)=Y(z)X(z)=b0+b1z−1+b2z−21+a1z−1+a2z−2(1)
        Which has finite difference equation:

        y[n]=b0x[n]+b1x[n−1]+b2x[n−2]−a1y[n−1]−a2y[n−2](2)
        You can boil this down to very simple C code by processing one sample at a time.
        Then you can write a simple structure like this:
 *//*-----------------------------------------------------------------------------------*/


struct difference_equation
{
   // coefficients
   double b0;
   double b1;
   double b2;
   double a1;
   double a2;
   // input history
   double x1;
   double x2;
   // output history
   double y1;
   double y2;

   double process(double x0)
   {
      double y0 = b0 * x0 + b1 * x1 + b2 * x2
                - a1 * y1 - a2 * y2;

      x2 = x1;
      x1 = x0;

      y2 = y1;
      y1 = y0;

      return y0;
   }
}

difference_equation de;

//assign coefficients (I'm assuming you know how to calculate your own values):
de.b0 = 1;
de.b1 = 0;
de.b2 = 0;
de.a1 = 0;
de.a2 = 0;

// reset input/output history
de.x1 = 0;
de.x2 = 0;
de.y1 = 0;
de.y2 = 0;

double input_samples[3];
double output_samples[3];

for (int i = 0; i < 3; i++)
{
   output_samples[i] = de.process(input_samples[i]);
}
