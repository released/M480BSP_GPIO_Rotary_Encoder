# M480BSP_GPIO_Rotary_Encoder
 M480BSP_GPIO_Rotary_Encoder

update @ 2023/07/25

1. use PA.4 , PA.3 to driver rotary / encoder ( PIN A , PIN B)

2. initial GPIO interrupt and debounce , refer to GPIO_Rotary_Encoder_Init

3. under GPIO IRQ , to calculate direction and counting , refer to 

Rotary_Encoder_pinAcalculate , Rotary_Encoder_pinBcalculate , Rotary_Encoder_IRQSensing

4. under super loop , to display current direction and counting , refer to Rotary_Encoder_polling

5. refer link : 

    https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/

6. below is log message when change rotary / encoder

![image](https://github.com/released/M480BSP_GPIO_Rotary_Encoder/blob/main/log.jpg)	

7. below is clockwise waveform (up : PINA , down : PINB)

![image](https://github.com/released/M480BSP_GPIO_Rotary_Encoder/blob/main/clockwise.jpg)	

8. below is counter_clockwise waveform (up : PINA , down : PINB)

![image](https://github.com/released/M480BSP_GPIO_Rotary_Encoder/blob/main/counter_clockwise.jpg)	


