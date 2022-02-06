#define EPD_WIDTH   128
#define EPD_HEIGHT  250

#define ALLSCREEN_GRAGHBYTES  4000
//EPD
void EPD_HW_init(void);
void EPD_init(void);
void EPD_init_GUI(void); //EPD init GUI
void PIC_display(const unsigned char *BW_datas,const unsigned char *R_datas);
void EPD_sleep(void);
void Epaper_READBUSY(void);
void PIC_display_Clear(void);
//Display canvas function
void EPD_Display(unsigned char *BW_Image,unsigned char *R_Image);
/***********************************************************
						end file
***********************************************************/


