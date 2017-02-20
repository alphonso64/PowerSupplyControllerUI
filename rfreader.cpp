#include "rfreader.h"
#include <QDebug>

extern "C"
{
     #include "mwrf.h"
     extern int rf_init(char *filename,unsigned long baud);
     extern int rf_request(int icdev,unsigned char _Mode,unsigned int *TagType);
     extern int rf_anticoll(int icdev,unsigned char _Bcnt,unsigned long *_Snr);
     extern int rf_beep(int icdev,unsigned short _Msec);
}

void RFReader::run()
{
    int icdev;
    unsigned long _Snr;
    unsigned int state;
    if((icdev=rf_init("/root/star500x",9600))<0)
    {
        qDebug()<<"ic_init ERR ";
        return;
    }else
    {
        qDebug()<<"ic_init OK ";
    }

    while(1)
    {
        unsigned long _Snr_temp;
        if(rf_request(icdev,0x01,&state)==0)
        {
            if(rf_anticoll(icdev,0,&_Snr_temp)==0)
            {
                if(_Snr != _Snr_temp)
                {
                    rf_beep(icdev,10);
                    _Snr = _Snr_temp;
                    qDebug()<<"card number:"<<_Snr;
                }
            }else{
                _Snr = 0;
            }
        }else{
            _Snr = 0;
        }
        usleep(500000);
    }
}
