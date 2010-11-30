#include "sensors.h"
#include "common.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "touch_qt_config.h"
#include "touch_api.h"


/* This configuration data structure parameters if needs to be changed will be
   changed in the qt_set_parameters function */
extern qt_touch_lib_config_data_t qt_config_data;
/* touch output - measurement data */
extern qt_touch_lib_measure_data_t qt_measure_data;
/* Get sensor delta values */
extern int16_t qt_get_sensor_delta( uint8_t sensor);

#ifdef QTOUCH_STUDIO_MASKS
extern TOUCH_DATA_T SNS_array[2][2];
extern TOUCH_DATA_T SNSK_array[2][2];
#endif

/* Output can be observed in the watch window using this pointer */
qt_touch_lib_measure_data_t *pqt_measure_data = &qt_measure_data;
/* flag set by timer ISR when it's time to measure touch */
static volatile uint8_t time_to_measure_touch = 0u;
/* current time, set by timer ISR */
static volatile uint16_t current_time_ms_touch = 0u;
/* Timer period in msec. */
uint16_t qt_measurement_period_msec = 25u;


void QTouchInit(void) {
    SFIOR |= (1<<PUD);
    #ifdef QTOUCH_STUDIO_MASKS
    SNS_array[0][0]= 0x55;
    SNS_array[0][1]= 0x0;
    SNS_array[1][0]= 0x0;
    SNS_array[1][1]= 0x0;

    SNSK_array[0][0]= 0xaa;
    SNSK_array[0][1]= 0x0;
    SNSK_array[1][0]= 0x0;
    SNSK_array[1][1]= 0x0;
    #endif

    // Configure the Sensors as keys
    qt_enable_key( CHANNEL_0, AKS_GROUP_1, 10u, HYST_6_25 );
    qt_enable_key( CHANNEL_1, AKS_GROUP_1, 10u, HYST_6_25 );
    qt_enable_key( CHANNEL_2, AKS_GROUP_1, 10u, HYST_6_25 );
    qt_enable_key( CHANNEL_3, AKS_GROUP_1, 10u, HYST_6_25 );

    //  Set the parameters like recalibration threshold, Max_On_Duration etc in this function by the user
    /*  This will be modified by the user to different values   */
    qt_config_data.qt_di              = DEF_QT_DI;
    qt_config_data.qt_neg_drift_rate  = DEF_QT_NEG_DRIFT_RATE;
    qt_config_data.qt_pos_drift_rate  = DEF_QT_POS_DRIFT_RATE;
    qt_config_data.qt_max_on_duration = DEF_QT_MAX_ON_DURATION;
    qt_config_data.qt_drift_hold_time = DEF_QT_DRIFT_HOLD_TIME;
    qt_config_data.qt_recal_threshold = DEF_QT_RECAL_THRESHOLD;
    qt_config_data.qt_pos_recal_delay = DEF_QT_POS_RECAL_DELAY;

    qt_init_sensing();  // initialise touch sensing

    // configure timer ISR to fire regularly
    /*  set timer compare value (how often timer ISR will fire) */
    OCR1A = ( TICKS_PER_MS * qt_measurement_period_msec);
    /*  enable timer ISR */
    TIMSK |= (1u << OCIE1A);
    /*  timer prescaler = system clock / 8  */
    TCCR1B |= (1u << CS11);
    /*  timer mode = CTC (count up to compare value, then reset)    */
    TCCR1B |= (1u << WGM12);


    /*  Address to pass address of user functions   */
    /*  This function is called after the library has made capacitive measurements,
    *   but before it has processed them. The user can use this hook to apply filter
    *   functions to the measured signal values.(Possibly to fix sensor layout faults)    */
    qt_filter_callback = 0;

}

void Task_Sensors(void) {
    /*status flags to indicate the re-burst for library*/
    uint16_t status_flag = 0u;
    uint16_t burst_flag = 0u;

    if(time_to_measure_touch) {
        time_to_measure_touch = false;
        do {
            //  one time measure touch sensors
            status_flag = qt_measure_sensors(current_time_ms_touch);
            burst_flag  = status_flag & QTLIB_BURST_AGAIN;
        } while (burst_flag);
    } // if(time_to_measure_touch)
}

FORCE_INLINE bool SensorIsTouched(uint8_t ASensor) {
    return (qt_measure_data.qt_touch_status.sensor_states[0] & (1<<(ASensor)));
}


ISR(TIMER1_COMPA_vect) {
    /*  set flag: it's time to measure touch    */
    time_to_measure_touch = 1u;

    /*  update the current time */
    current_time_ms_touch += qt_measurement_period_msec;
}

