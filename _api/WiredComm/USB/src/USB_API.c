/*************************************************************************//**

  @file     USB_API.c

  @brief    Driver Library to use USB

  @author   Tomas Pentacolo (based on Pablo Llull (PL))

  @date     23/11/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/


void USB_Init()
{
	Init_USBDriver();
}

#if USBprot=="EMIC_message"

void pUSB(char* format,...)
{
	va_list arg;
    va_start(arg, format);
 	for (; *format > 0; format++)
	{
		if ( *format == '%' )
		{
			char* str;
			streamIn_t* dataIn;
			format++;
			switch (*format)
			{
				//case 't':
				//	UARTX_{puerto}__OUT_push('\t');
				//	break;
				case 's':
					str = va_arg(arg, char*);
					while (*str)
					{
						UARTX_{puerto}__OUT_push( *str++);
					}
					break;
				case 'r':
					dataIn = va_arg(arg, streamIn_t*);
					while (dataIn->count())
					{
						UARTX_{puerto}__OUT_push( dataIn->get(1));
					}
					break;
				default:
					UARTX_{puerto}__OUT_push(*format);
					break;

			}
		}
		else
		{
			UARTX_{puerto}__OUT_push(*format);
		}
	}
	va_end(arg);
}


#else
void pUSB(char* msg)
{
	char *r;
	
	for (r = char* msg;*r > 0; r++) 
	{
		UARTX_{puerto}__OUT_push(*r);
	}
	UARTX_{puerto}__OUT_push(USBFrameLf);
}
#endif

/*
//#if USBprot=="STREAM"
//void gUSB(void)
//{
//	char r;
//
//	if (UARTX_{puerto}__IN_n_frame > 0)
//	{
//		putc_rsp('�');
//
//		while (UARTX_{puerto}__IN_n_frame > 0)
//		{
//			r=UARTX_{puerto}__IN_pop(0);
//			putc_rsp(r);
//		}
//		putc_rsp('�');
//	}
//}
//
//doCMDf(gUSB)
//#endif
*/

void Poll_USB(void)
{

	#ifdef event_eUSB_active 

	if (UARTX_{puerto}__IN_n_frame > 0)
	{
		#if USBprot=="EMIC_message"
		char tag[20];
		char d;
		uint8_t i = 0;
	
		d = UARTX_{puerto}__IN_pop(1);
		while (d != USBFrameLf && d != '\t' && i < 20)
		{
			tag[i++] = d;
			d = UARTX_{puerto}__IN_pop(1);
		}
		
		tag[i] = 0;
		
		eUSB(tag,&getUart_{puerto}_);
		#endif
		
		
		
	}
	#endif

	#ifdef event_eBeUSB_active
		
	if(UARTX_{puerto}__bufferEmpty) 
	{
		UARTX_{puerto}__bufferEmpty=0;
		//puts_f("#eBeUSB;\r"); //se vacio el buffer tx
	}

	#endif
}
