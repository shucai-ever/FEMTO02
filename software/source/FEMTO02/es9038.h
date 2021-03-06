#ifndef _AVR_ES9038_H_
#define _AVR_ES9038_H_

#define ES9038_XI_CLK 100000000L

#define ES9038_ADDR0  0x90      // Left channel
#define ES9038_ADDR1  0x92      // Right channel
#define ES9038_REG_SYSTEM 0x00
#define ES9038_REG_INPUT_SEL 0x01
#define ES9038_REG_SERIALDATA_AUTOMUTE 0x02
#define ES9038_REG_AUTOMUTE_TIME 0x04
#define ES9038_REG_AUTOMUTE_LEVEL 0x05
#define ES9038_REG_VOLUME_RAMP_RATE   0x06
#define ES9038_REG_FILTERBW_MUTE 0x07
#define ES9038_REG_JITTER_ELIMINATOR_DPLL_BW 0x0B
#define ES9038_REG_GPIO_INPUT_SEL_VOLUME_CONFIG 0x0F
#define ES9038_REG_VOLUME 0x10        // 0x10~0x17
#define ES9038_REG_JITTER_DPLLBW 0x0C
#define ES9038_REG_SOFT_START_CFG 0x0D

#define ES9038_MAX_REG_NUM 115
#define ES9038_MAX_VOLUME 0x00
#define ES9038_MIN_VOLUME 199

#define ES9038_REG_CHIP_ID_STATUS  0x40
#define ES9038_CHIP_ID(x) (((x)&0x3F)<<2)
#define ES9038_AUTOMUTE_STATUS 0x01<<1
#define ES9038_LOCK_STATUS 0x01<<0
#define ES9038PRO_CHIP_ID 0x2A

#define ES9038_REG_VOLUME1_CONTROL 0x10
#define ES9038_REG_VOLUME2_CONTROL 0x11
#define ES9038_REG_VOLUME3_CONTROL 0x12
#define ES9038_REG_VOLUME4_CONTROL 0x13
#define ES9038_REG_VOLUME5_CONTROL 0x14
#define ES9038_REG_VOLUME6_CONTROL 0x15
#define ES9038_REG_VOLUME7_CONTROL 0x16
#define ES9038_REG_VOLUME8_CONTROL 0x17
#define ES9038_REG_MASTER_TRIM 0x18 //32bit
#define ES9038_REG_DPLL_NUM    0x42 //32bit
#define ES9038_REG_DAC_CH_MAPPING_DAC12 0x26
#define ES9038_REG_DAC_CH_MAPPING_DAC34 0x27
#define ES9038_REG_DAC_CH_MAPPING_DAC56 0x28
#define ES9038_REG_DAC_CH_MAPPING_DAC78 0x29

#define ES9038_REG_GPIO12_CFG 0x08
#define ES9038_REG_GPIO34_CFG 0x09
#define ES9038_GPIO1_CFG(x)             (((x)&0x0F)<<0)
#define ES9038_GPIO2_CFG(x)             (((x)&0x0F)<<4)
#define ES9038_GPIO3_CFG(x)             (((x)&0x0F)<<0)
#define ES9038_GPIO4_CFG(x)             (((x)&0x0F)<<4)
enum gpio_table {GPIO_AUTOMUTE_STATUS=0, GPIO_LOCK_STATUS, GPIO_VOLUME_MIN, GPIO_CLK, GPIO_AMLI, GPIO_ADC_CLK, GPIO_RESERVED, GPIO_OUTPUT0, GPIO_STANDARD_INPUT, GPIO_INPUT_SELECT, GPIO_MUTE_ALL };

#define ES9038_REG_18DB_CHANNEL_GAIN 0x3E       //Register 62

#define ES9038_SYSTEM_SOFT_RESET        0x01<<0
#define ES9038_GPIO_INPUT_SEL(x)        (((x)&0x03)<<6)
#define ES9038_INPUT_AUTO_SEL(x)        (((x)&0x03)<<2)
enum auto_select {AUTO_SEL_DISABLE, AUTO_SEL_DSD_I2S, AUTO_SEL_SPDIF_I2S, AUTO_SEL_DSD_SPDIF_I2S};
#define ES9038_INPUT_SEL(x)             (((x)&0x03)<<0)
enum input_select {INPUT_I2S, INPUT_SPDIF, INPUT_DSD=4};

#define ES9038_VOLUME_CFG_STEREO_MODE   0x01<<2
#define ES9038_VOLUME_CFG_CH1_VOL       0x01<<1
#define ES9038_VOLUME_CFG_LATCH_VOL     0x01<<0
#define ES9038_VOLUME_RATE(x)           (((x)&0x07)<<0)
#define ES9038_FILTER_SHAPE(x)          (((x)&0x07)<<5)
enum filter_shape { FAST_ROLL_OFF_LINEAR_PHASE_FILTER,\
                    SLOW_ROLL_OFF_LINEAR_PHASE_FILTER,\
                    FAST_ROLL_OFF_MIN_PHASE_FILTER,\
                    SLOW_ROLL_OFF_MIN_PHASE_FILTER,\
                    RESERVED_FILTER,\
                    APODIZING_FAST_ROLL_OFF_LINEAR_PHASE_FILTER,\
                    HYBRID_FAST_ROLL_OFF_MIN_PHASE_FILTER,\
                    BRICKWALL_FILTER };
#define ES9038_FILTER_IIR_BW(x)         (((x)&0x03)<<1)
#define ES9038_DPLL_BW_SERIAL(x)        (((x)&0x0F)<<4)
#define ES9038_DPLL_BW_DSD(x)           (((x)&0x0F)<<0)
enum dpdd_bw { DPLL_OFF, DPLL_LOWEST, DPLL_2, DPLL_3, DPLL_4, DPLL_5, DPLL_6, DPLL_7, DPLL_8, DPLL_9, DPLL_10, DPLL_11, DPLL_12, DPLL_13, DPLL_14, DPLL_HIGHEST };

#define ES9038_SYSTEM_MUTE              0x01<<0
#define ES9038_AUTOMUTE_TIME(x)         (x)
#define ES9038_AUTOMUTE_LEVEL(x)        (((x)&0x3F)<<0)   

#define ES9038_DAC_CH1_MAP(x)           (((x)&0x0F)<<0)
#define ES9038_DAC_CH2_MAP(x)           (((x)&0x0F)<<4)
#define ES9038_DAC_CH3_MAP(x)           (((x)&0x0F)<<0)
#define ES9038_DAC_CH4_MAP(x)           (((x)&0x0F)<<4)
#define ES9038_DAC_CH5_MAP(x)           (((x)&0x0F)<<0)
#define ES9038_DAC_CH6_MAP(x)           (((x)&0x0F)<<4)
#define ES9038_DAC_CH7_MAP(x)           (((x)&0x0F)<<0)
#define ES9038_DAC_CH8_MAP(x)           (((x)&0x0F)<<4)

#define ES9038_AUTOMUTE_STATUS          0x01<<1
#define ES9038_LOCK_STATUS              0x01<<0

#define ES9038_SOFT_START_TIME(x)       (((x)&0x0F)<<0)



enum ch_input {INPUT_CH1, INPUT_CH2, INPUT_CH3, INPUT_CH4, INPUT_CH5, INPUT_CH6, INPUT_CH7, INPUT_CH8};




enum automute_cfg { AUTOMUTE_NORMAL, AUTOMUTE_ONLYMUTE, AUTOMUTE_ALLGND, AUTOMUTE_RAMPNGND };
enum serial_mode { I2S_MODE, LEFTJUST_MODE, RIGHTJUST_MODE };
#define REG_AUTOMUTE_LEVEL 0x05
#define REG_SOFT_START_TIME 11

#define ES9038_ADDR0_MUTE es9038_write_register(ES9038_ADDR0,ES9038_REG_FILTERBW_MUTE,0x41)
#define ES9038_ADDR1_MUTE es9038_write_register(ES9038_ADDR1,ES9038_REG_FILTERBW_MUTE,0x41)

unsigned char es9038_is_dsd_mode(unsigned char devaddr);
void es9038_system_mute(unsigned char devaddr, unsigned char onoff);
#endif
