/* varac-table.c
 * Quick and messy code to create the Arduino
 * lookup tables.
 *
 * Version: 0.0.1
 * Author:  Matthew J Wolf, N4MTT
 * Date:    I have no idea. Header added on 15-SEP-2019
 *
 * The N4MTT Variable Voltage and Current Arduino Sketch is 
 * free software: you can  redistribute it and/or modify it 
 * under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 
 * 2 of the License, or (at your option) any later version.
 * 
 * The N4MTT Variable Voltage and Current Arduino Sketch is 
 * distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public 
 * License along with the N4MTT Variable Voltage and Current 
 * Arduino Sketch.  
 * If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <math.h>

/*
  voltageValue = analogRead(voltage); 
  current1Value = analogRead(current1);
  float vol = (voltageValue * (5.00/1023.0))*120;
  float cur1 = current1Value * (5.00/1023.0);

  analogRead(voltage) returns
  int (0 to 1023) 
  5/1023 = 0.004887586

  ATMega int is  -32,768 to 32,767
  unsigned int is 0 to 65,535
*/

float out_value = -1;
float out_value1 = -1;

//float ratio[1024];

int x = -1;

main() {

  printf ("/*\n ADC V(Rounded) V\n");  

  //use table, aka lookup table is final code
  for (x=0;x<=1023;x++) {
     out_value = (x * (5.00 / 1023.0) ) *120;
     out_value1 = roundf( ((x * (5.00 / 1023.0) ) *120 ) *100  )/100;

     printf (" %-4d %-3.2f    %-3.6f\n",x,out_value1,out_value);	
  }

  printf ("\n ADC  Current(Rounded) Current\n");

  for (x=0;x<=1023;x++) {
     out_value = (x * (5.00 / 1023.0) );
     out_value1 = roundf( (x * (5.00 / 1023.0) ) *100 )/100;
     printf (" %-4d %-3.2f    %-3.6f\n",x,out_value1,out_value);
  }
 
  printf ("*/\n");

  printf ("\nconst int vol_table[] PROGMEM = { \n");

    for (x=0;x<=1023;x++) {
     out_value = roundf( ((x * (5.00 / 1023.0) ) *120 ) *100  )/100;

     //no comma on last one and need a close blacket
     if ( x== 1023) {
        printf (" %-.2f };\n",out_value); 
     } else { 
        printf (" %-.2f,",out_value);
     }

     //new line every 10 lines
     if ( x%10 == 0 && x != 0 )  { printf("\n"); }	
  }

  printf ("\nconst int cur_table[] PROGMEM = { \n");

  for (x=0;x<=1023;x++) {
     out_value = roundf( (x * (5.00 / 1023.0) ) *100 )/100;

     //no comma on last one and need a close blacket
     if ( x== 1023) {
        printf (" %-.2f };\n",out_value); 
     } else { 
        printf (" %-.2f,",out_value);
     }

     //new line every 10 lines
     if ( x%10 == 0 )  { printf("\n"); }

  }


}

