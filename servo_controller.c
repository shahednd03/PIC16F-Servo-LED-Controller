// Function to set servo motor to 0 degrees
void S_0() {
    unsigned int i;
    for (i = 0; i < 50; i++) {
        PORTB.F0 = 1;
        Delay_us(800);
        PORTB.F0 = 0;
        Delay_us(19200);
    }
}

// Function to set servo motor to 90 degrees
void S_90() {
    unsigned int i;
    for (i = 0; i < 50; i++) {
        PORTB.F0 = 1;
        Delay_us(1500);
        PORTB.F0 = 0;
        Delay_us(18500);
    }
}

// Function to set servo motor to 180 degrees
void S_180() {
    unsigned int i;
    for (i = 0; i < 50; i++) {
        PORTB.F0 = 1;
        Delay_us(2200);
        PORTB.F0 = 0;
        Delay_us(17800);
    }
}

// Function to control LED with fading effect
void LED() {
    unsigned int i;

    PWM1_Start();
    for (i = 0; i < 255; i++) {
        PWM1_Set_Duty(i);
        Delay_ms(15);
    }
    for (i = 255; i > 0; i--) {
        PWM1_Set_Duty(i);
        Delay_ms(15);
    }
    PWM1_Stop();
}

float volt;

void main() {
    // Port and ADC initialization
    TRISA = 0xFF;
    PORTA = 0x00;
    TRISB = 0x00;
    PORTB = 0x00;
    TRISC = 0x00;
    PORTC = 0x00;

    ADC_Init();
    PWM1_Init(500);

    while (1) {
        // LED fading effect
        LED();

        // Read voltage from ADC channel 0
        volt = ADC_Read(0);
        volt = volt * 0.0048875855; // Convert ADC value to voltage

        // Servo control based on voltage level
        if (volt > 1 && volt < 4) {
            S_90();
        } else if (volt >= 4) {
            S_180();
        } else {
            S_0();
        }
    }
}
