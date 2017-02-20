//1.
int  rf_init(char *filename,unsigned long baud);
//2.
int rf_exit(int icdev);
//3.
int rf_config(int icdev,unsigned char _Mode,unsigned char _Baud);
//4.
int rf_request(int icdev,unsigned char _Mode,unsigned int *TagType);
//5.
int  rf_anticoll(int icdev,unsigned char _Bcnt,unsigned long *_Snr);
//6.
int rf_select(int icdev,unsigned long _Snr,unsigned char *_Size);
//7.
int rf_authentication(int icdev,unsigned char _Mode,unsigned char _SecNr);
//8.
int rf_halt(int icdev);
//9
int rf_read(int icdev,unsigned char _Adr,unsigned char *_Data);
//10.
int rf_read_hex(int icdev,unsigned char _Adr,char *_Data);
//11.
int rf_write(int icdev,unsigned char _Adr,unsigned char *_Data);
//12.
int rf_write_hex(int icdev,unsigned char _Adr,char *_Data);
//13.
int rf_load_key(int icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
//14.
int rf_load_key_hex(int icdev,unsigned char _Mode,unsigned char _SecNr,char *_NKey);
//15.
int rf_increment(int icdev,unsigned char _Adr,unsigned long _Value);
//16.
int rf_decrement(int icdev,unsigned char _Adr,unsigned long _Value);
//17
int rf_decrement_ml(int icdev,unsigned int _Value);
//18.
int rf_restore(int icdev,unsigned char _Adr);
//19
int rf_transfer(int icdev,unsigned char _Adr);
//20.
int rf_card(int icdev,unsigned char _Mode,unsigned long *_Snr);
//21.
int rf_initval(int icdev,unsigned char _Adr,unsigned long _Value);
//22
int rf_initval_ml(int icdev,unsigned int _Value);
//23.
int rf_readval(int icdev,unsigned char _Adr,unsigned long *_Value);
//24
int rf_readval_ml(int icdev,unsigned int *_Value);
//25.
int rf_changeb3(int icdev,unsigned char _SecNr,unsigned char *_KeyA,unsigned char _B0,unsigned char _B1,unsigned char _B2,unsigned char _B3,unsigned char _Bk,unsigned char *_KeyB);
//26.
int rf_get_status(int icdev,unsigned char *_Status);
//27.
int rf_clr_control_bit(int icdev,unsigned char _b);
//28.
int rf_set_control_bit(int icdev,unsigned char _b);
//29.
int rf_reset(int icdev,unsigned int _Msec);
//30.
int rf_HL_decrement(int icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long _Snr,unsigned long *_NValue,unsigned long *_NSnr);
//31.
int rf_HL_increment(int icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long _Snr,unsigned long *_NValue,unsigned long *_NSnr);
//32.
int rf_HL_write(int icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
//33
int rf_HL_writehex(int icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
//34.
int rf_HL_read(int icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
//35
int rf_HL_readhex(int icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
//36.
int rf_HL_initval(int icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long *_Snr);
//37.
int rf_beep(int icdev,unsigned short _Msec);
//38.
int rf_disp8(int icdev,int pt_mode,unsigned char* disp_str);
//39
int rf_disp(int icdev,unsigned char pt_mode,unsigned short digit);
//40.
int rf_encrypt( char *key,char *ptrSource, unsigned long msgLen, char *ptrDest);
//41.
int rf_decrypt( char *key,char *ptrSource, unsigned long msgLen, char *ptrDest);
//42
int rf_HL_authentication(int icdev,unsigned char reqmode,unsigned long snr,unsigned char authmode,unsigned char secnr);
//43
int rf_srd_eeprom(int icdev,int offset,int lenth,unsigned char *rec_buffer);
//44
int rf_swr_eeprom(int icdev,int offset,int lenth,unsigned char* send_buffer);
//45
int rf_srd_snr(int icdev,int lenth,unsigned char *rec_buffer);
//46
int rf_check_write(int icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data);
//47
int rf_check_writehex(int icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data);
//48
int rf_authentication_2(int icdev,unsigned char _Mode,unsigned char KeyNr,unsigned char Adr);
//49
int rf_decrement_transfer(int icdev,unsigned char Adr,unsigned long _Value);
//50
int rf_setport(int icdev,unsigned char _Byte);
//51
int rf_getport(int icdev,unsigned char *receive_data);
//52
int rf_gettime(int icdev,unsigned char *time);
//53
int rf_gettimehex(int icdev,char *time);
//54
int rf_settime(int icdev,unsigned char *time);
//55
int rf_settimehex(int icdev,char *time);
//56
int rf_setbright(int icdev,unsigned char bright);
//57
int rf_ctl_mode(int icdev,unsigned char mode);
//58
int rf_disp_mode(int icdev,unsigned char mode);
//59
int lib_ver(unsigned char *str_ver);
//60
int rf_comm_check(int icdev,unsigned char _Mode);
//61
int set_host_check(unsigned char _Mode);
//62
int set_host_485(unsigned char _Mode);

int rf_sam_rst(int icdev, unsigned char baud, unsigned char *samack);
//63
int rf_sam_trn(int icdev, unsigned char *samblock,unsigned char *recv);
//64
int rf_sam_off(int icdev);
//65
int rf_cpu_rst(int icdev, unsigned char baud, unsigned char *cpuack);
//66
int rf_cpu_trn(int icdev, unsigned char *cpublock,unsigned char *recv);
//67
int rf_pro_rst(int icdev,unsigned char *_Data);
//68
int rf_pro_trn(int icdev,unsigned char *problock,unsigned char *recv);
//69
int rf_pro_halt(int icdev);
//70
void Set_Reader_Mode(unsigned char _Mode);
int rf_get_snr(int icdev,unsigned char *_Snr);
int turn_hex(int icdev);
int turn_asc(int icdev);

