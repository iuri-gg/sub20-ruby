require File.expand_path(File.dirname(__FILE__) + '/../ext/sub20/sub20.so')

class Sub20
  # Single ended ADC inputs
 	ADC_S0, ADC_S1, ADC_S2, ADC_S3 = 0, 1, 2, 3
 	ADC_S4, ADC_S5, ADC_S6, ADC_S7 = 4, 5, 6, 7
 
 	ADC_D10_10X = 9   # Differential ADC1(+) ADC0(-) Gain 10x  */
  ADC_D10_200X= 11  # Differential ADC1(+) ADC0(-) Gain 200x */
 	ADC_D32_10X = 13  # Differential ADC3(+) ADC2(-) Gain 10x  */
 	ADC_D32_200X= 15  # Differential ADC3(+) ADC2(-) Gain 200x */
 	ADC_D01 	  = 16  # Differential ADC0(+) ADC1(-) Gain 1x   */
 	ADC_D21     = 18  # Differential ADC2(+) ADC1(-) Gain 1x   */
 	ADC_D31     = 19  # Differential ADC3(+) ADC1(-) Gain 1x   */
 	ADC_D41     = 20  # Differential ADC4(+) ADC1(-) Gain 1x   */
 	ADC_D51     = 21  # Differential ADC5(+) ADC1(-) Gain 1x   */
 	ADC_D61     = 22  # Differential ADC6(+) ADC1(-) Gain 1x   */
 	ADC_D71     = 23  # Differential ADC7(+) ADC1(-) Gain 1x   */
 	ADC_D02     = 24  # Differential ADC0(+) ADC2(-) Gain 1x   */
 	ADC_D12     = 25  # Differential ADC1(+) ADC2(-) Gain 1x   */
 	ADC_D32     = 27  # Differential ADC3(+) ADC2(-) Gain 1x   */
 	ADC_D42     = 28  # Differential ADC4(+) ADC2(-) Gain 1x   */
 	ADC_D52     = 29  # Differential ADC5(+) ADC2(-) Gain 1x   */
 	ADC_1_1V  	= 30  # Single Ended internally connected to 1.1V */
 	ADC_GND	  	= 31  # Single Ended internally connected to GND  */
end