#include "adc.h"

/**
 * @brief inicializa o ADC, configurado para conversão engatilhada com o timer0.
 */
void adc_init(void)
{
    adc.ready = 0;
    adc.select = ADC0;

    // configuracao do ADC
    clr_bit(PORTC,ADC0);
    DDRC    =   0b00000000;                         // all adcs as inputs
    set_bit(DIDR0,ADC0);

    ADMUX   =   (0 << REFS1)                        // AVcc with external capacitor at AREF pin
            | (1 << REFS0)
#ifdef ADC_8BITS
            | (1 << ADLAR);                         // ADC left adjusted -> using 8bits ADCH only
#else
            | (0 << ADLAR);                         // ADC left adjusted -> using all 10 bits
#endif
    ADMUX = (ADMUX & 0xF8) | ADC0;                  // Choose ADMUX

    ADCSRB  =   (0 << ADTS2)                        // free-running mode
            | (0 << ADTS1)
            | (0 << ADTS0);

    ADCSRA  =   (1 << ADATE)                        // ADC Auto Trigger Enable
            | (1 << ADIE)                           // ADC Interrupt Enable
            | (1 << ADEN)                           // ADC Enable
            | (1 << ADSC)                           // Do the first Start of Conversion
            | (1 << ADPS2)                          // ADC Prescaller = 128;
            | (1 << ADPS1)
            | (1 << ADPS0);
}

/**
 * @brief MUX do ADC
 */
ISR(ADC_vect)
{

#ifdef FAKE_ADC_ON
    adc.channel[adc.select].sum += FAKE_ADC;
#else // FAKE_ADC_ON
    #ifdef ADC_8BITS
    adc.channel[adc.select].sum += ADCH;
    #else // ADC_8BITS
    adc.channel[adc.select].sum += ADC;
    #endif // ADC_8BITS
#endif // FAKE_ADC_ON

    if(++adc.channel[adc.select].samples >= ADC_AVG_SIZE_10){
        adc.channel[adc.select].avg = adc.channel[adc.select].sum >> ADC_AVG_SIZE_2;

        adc.channel[adc.select].samples = adc.channel[adc.select].sum = 0;
        adc.ready = 1;

        #ifdef VERBOSE_ON_ADC
        VERBOSE_MSG_ADC( usart_send_string("adc:") );
        VERBOSE_MSG_ADC( usart_send_char(adc.select + '0') );
        VERBOSE_MSG_ADC( usart_send_char(':') );
        VERBOSE_MSG_ADC( usart_send_uint16(adc.channel[adc.select].avg) );
        VERBOSE_MSG_ADC( usart_send_char('\n') );
        #endif
    }

    ADCSRA = ADCSRA;                  // rearm for next conversion if TIMER0
    
}
 
