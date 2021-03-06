///////////////////////////////////////////////////////////////////////////////
// This represent remocon status.
char _flg_on_remocon=0;
char _code_remocon=0; // represent remocon present status.
    //1 : Lead Code
    //2 : Custom Code I
    //3 : Custom Code II
    //4 : Data I
    //5 : Data II
U16 _counter_remocon;
int _remocon_custom=0;
int _remocon_custom_2=0;
int _remocon_data=0,Remoc_data_save=0;
int _remocon_data_2=0;
char _remocon_counter=0;
char _flgOrKey;
char _flg_enter;
U16 _remocon_buffer;
char _flg_repeat; // This represent the staus fo remocon repeat mode.
U16 _remocon_repeat_count;
char _flg_run_repeat;
char _flg_allow_remocon_repeat;


char bit_input;

#define	remocon_signal		PINE_Bit5

U8 _repeat_remocon=0;
U8 _repeat_data=0x30;

U8 low_bit_time=0;
U8 low_start_flag=0;
U8 high_bit_0=0;
U8 high_bit_1=0;
U8 high_start_flag=0;
U8 high_repeat_flag0=0;
U8 high_repeat_flag1=0;
U8 ir_error_check=0;

///////////////////////////////////////////////////////////////////////////////
//
// This is the interrupt routine.
// TIMER0
//
///////////////////////////////////////////////////////////////////////////////
#pragma vector = TIMER2_OVF_vect
__interrupt void TIMER2_OVF_Handler(void)
{
    TCNT2 = 0xff - 200;
  // 16MHz / 8precaling = 2000kHz
  // T= 1 / 2000kHz = 0.5usec
  // 0.5usec X 200 = 100usec
  
    //TIFR = 0 << TOV1;
    //pf = ~pf;
    //_outport(PPCF,pf);
    _counter_remocon++;
    
    //if ( _counter_remocon > 1100 )	high_repeat_flag1=0;		//110msec
    if ( _counter_remocon > 1100 ){								//120msec
     _flg_on_remocon = IDLE;
     _code_remocon= 0;
     _remocon_custom_2 = 0;
     _remocon_custom = 0;
     _remocon_data = 0;
     _remocon_data_2 = 0;
     _remocon_counter = 0;
            
     low_start_flag=0;
     high_start_flag=0;
     low_bit_time=0;
     high_bit_0=0;
     high_bit_1=0;
     high_repeat_flag0=0;
     high_repeat_flag1=0;
     _repeat_remocon=0;
     _counter_remocon=0;
     ir_error_check=0;
     rom_save_flag=1;
     if(  rom_save_flag==0 ) {
      rom_save_flag=1;
      rom_tmr=0;
     }
    }
    
}
/*
//0v1
void IR_error(){
  _flg_on_remocon = IDLE;
    _code_remocon= 0;
    _remocon_custom_2 = 0;
    _remocon_custom = 0;
    _remocon_data = 0;
    _remocon_data_2 = 0;
    _remocon_counter = 0;
    
    low_start_flag=0;
    high_start_flag=0;
    low_bit_time=0;
    high_bit_0=0;
    high_bit_1=0;
    high_repeat_flag0=0;
    high_repeat_flag1=0;
    _repeat_remocon=0;
    ir_error_check=0;        
  }
*/
void remocon_data(){

  switch(_code_remocon){
  case 1:
      _remocon_custom <<= 1;
      _remocon_custom |= bit_input;
      break;
  case 2:
      _remocon_custom_2 <<=1;
      _remocon_custom_2 |= bit_input;
      break;
  case 3:
      _remocon_data <<= 1;
      _remocon_data |= bit_input;
      break;
  case 4:
      _remocon_data_2 <<= 1;
      _remocon_data_2 |= bit_input;
      break;
  }
   
  _remocon_counter++;
   
  if(_remocon_counter >= 8) {
    _code_remocon++;
    _remocon_counter =0;
  }
     //bit check    
  // receiving finished.
  if(_code_remocon >= 5){
    _remocon_custom&=0xf;
    _remocon_custom_2&=0xf;
 
  if(_remocon_custom==0x7 && _remocon_custom_2==0xa){
    if(_remocon_data_2==(_remocon_data^0xff)){         			
      _repeat_data=_remocon_data;
        if(init_setting_check){
//MUTE            : 0xB0;
//VOL-UP          : 0x80;
//VOL-DOWN     : 0xA8;
//CH-UP           : 0x90;
//CH-DOWN       : 0x88;
//PHASE           : 0xA0;
//FILTER           : 0X98;         
          rom_save_flag=0;
          
          if(_remocon_data==0xB0) ess_mute();                                           //Mute
          else if(_remocon_data==0x80) audio_level_up();                            //Master Volume Up
          else if(_remocon_data==0xA8) audio_level_down();                        //Master Volume Down
          else if(_remocon_data==0x90) channel_up();                                //Channel Change
          else if(_remocon_data==0x88) channel_down();                           //Channel Change
          else if(_remocon_data==0xA0) {                                                //inverse Change
            if(!key_condition) key_func=1;
            else key_func=3;      
            femto_function(); 
          }//phase_write();  phase_ess(); }     
          else if(_remocon_data==0x98) { 
            if(!key_condition) key_func=2;
            else key_func=4;     
            femto_function();
            //filter_led<<=1;    
            //if(filter_led>0x04)  filter_led=1;	//filter1
            //ess_filter(filter_led);                                    //filter Change
          }
        }
      }
      //0v1
      //else IR_error();
    }
    //0v1
    //else IR_error();
            	
            
    _flg_on_remocon = IDLE;
    _code_remocon= 0;
    _remocon_custom_2 = 0;
    _remocon_custom = 0;
    _remocon_data = 0;
    _remocon_data_2 = 0;
    _remocon_counter = 0;
    
    low_start_flag=0;
    high_start_flag=0;
    low_bit_time=0;
    high_bit_0=0;
    high_bit_1=0;
    high_repeat_flag0=0;
    high_repeat_flag1=0;
    _repeat_remocon=0;
    ir_error_check=0;        
  }
   
}


U16 sp_en_cnt=0;
void _remocon_processing()
{
  //Lead code
  if ( low_start_flag && high_start_flag ) {
    if(_flg_on_remocon == IDLE){       		 	
      _flg_on_remocon = BUSY;
      _code_remocon = 1;
      _flg_repeat = IDLE;
      _flg_run_repeat = IDLE;
      _remocon_repeat_count =0;
      
      low_start_flag=0;
      high_start_flag=0;
      low_bit_time=0;
      high_bit_0=0;
      high_bit_1=0;
      //high_repeat_flag=0;
      high_repeat_flag0=0;
      high_repeat_flag1=0;
      _repeat_remocon=0;
      sp_en_cnt=0;
      ir_error_check=0;
    }
  }
   
    else if ( _flg_on_remocon && low_bit_time && high_bit_0 ) { bit_input=0;	low_bit_time=0;		high_bit_0=0; 	remocon_data();}
    else if ( _flg_on_remocon && low_bit_time && high_bit_1 ) { bit_input=1;	low_bit_time=0;		high_bit_1=0; 	remocon_data();}
    	
    //repeat check
    else if ( !_flg_on_remocon && high_repeat_flag0  )  { _repeat_remocon=1;  high_repeat_flag0=0; ir_error_check++;}
    else if ( _repeat_remocon &&  high_repeat_flag1  && init_setting_check ) { 	
      if(ir_error_check==1){
        high_repeat_flag1=0;
        rom_save_flag=0;
        
        //if(_repeat_data==0xB0) audio_level_up();                 //Master Volume Up
        //else if(_repeat_data==0x88) audio_level_down();      //Master Volume Down
        
        sp_en_cnt++;
        if(sp_en_cnt>2){
          if(_repeat_data==0x80) audio_level_sp_up();                 //Master Volume Up
          else if(_repeat_data==0xA8) audio_level_sp_down();      //Master Volume Down
        }
        else{
          if(_repeat_data==0x80) audio_level_up();                 //Master Volume Up
          else if(_repeat_data==0xA8) audio_level_down();      //Master Volume Down
        }
      }
      else{
        ir_error_check=0;
        _repeat_data=0;
      }
        
    }
    

}
U8 ir_error=0;
#pragma vector = INT5_vect
__interrupt void INT5_Handler(void)
{    
	//low time
	if(remocon_signal){
		if ( (_counter_remocon>=4 ) && ( _counter_remocon<=8 ) ) 	low_bit_time=1;	//bit check
		else if ( (_counter_remocon>=85 ) && ( _counter_remocon<=95 ) ) 	low_start_flag=1;	//Lead code
		else ir_error=1;
	}	
	
	//high time
	else if(!remocon_signal){
		if ( (_counter_remocon>=4 ) && ( _counter_remocon<=8 )  )	    high_bit_0=1;		//bit check
    	              else if ( (_counter_remocon>=9 ) && ( _counter_remocon<=22 ) )	    high_bit_1=1;		//bit check
		else if ( (_counter_remocon>=40 ) && ( _counter_remocon<=55 ) ) 	    high_start_flag=1;	//Lead code
		else if ( (_counter_remocon>=200 ) && ( _counter_remocon<=400 ) ) 	    high_repeat_flag0=1;	//repeat check , 38msec
		else if ( (_counter_remocon>=800 ) && ( _counter_remocon<=1000 ) )     high_repeat_flag1=1;	//repeat check , 100msec
		else ir_error=1;
	}
	
	//test IR 	
	//test_IR_tmr[test_IR_flag]=!remocon_signal;
              //test_IR_flag++;
              //test_IR_tmr[test_IR_flag]=_counter_remocon;
              //test_IR_flag++;
              //////
              
	_counter_remocon = 0;
	
	//0V0
	if(ir_error) { 
	  ir_error = 0;  
	  high_repeat_flag1=0;
	  //0v1
	  //IR_error();
	  }
	else _remocon_processing(); 
}



