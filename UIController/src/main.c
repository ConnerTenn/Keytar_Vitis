
/**
* Hello World program using XUartPs driver in polled mode
*
* The example uses the default setting in the XUartPs driver:
*	. baud rate 115200
*	. 8 bit data
*	. 1 stop bit
*	. no parity
*
* @note
* This example requires an external SchmartModule connected to the pins for
* the device to display the 'Hello World' message onto a hyper-terminal.
*
*/


#include "../../Synth_system/Common.h"

#include "xil_mmu.h"
#include "sleep.h"

#include "USB_Controller.h"
#include "Sil9022.h"
#include "VideoController.h"


#include "lvgl/lvgl.h"



int Init()
{
    //Disable cache on OCM
    /** @todo Change to Macros. xil_mmu.h*/
    Xil_SetTlbAttributes(SHARED_ADDR,0x14de2); //S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0

    InitializeInterrupt();

    InitUSB();

    InitVideoController();

    Sil9022Init();

    lv_init();

    return XST_SUCCESS;
}

void FlushCallback(struct _disp_drv_t *dispDrv, const lv_area_t *area, lv_color_t *color_p)
{
    u8 fb = -1;
    if (VIDEO_FRAME_BUFFER_ADDR(0) <= (u32)color_p && (u32)color_p <= VIDEO_FRAME_BUFFER_ADDR(0)+1920*1080*2) { fb = 0; }
    else if (VIDEO_FRAME_BUFFER_ADDR(1) <= (u32)color_p && (u32)color_p <= VIDEO_FRAME_BUFFER_ADDR(1)+1920*1080*2) { fb = 1; }

    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)-3*16) = 0b0000011111100000;
    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)-4*16) = 0b0000011111100000;
    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)-5*16) = 0b0000011111100000;

    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)) = 0b0000011111100000;
    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)+2*1) = 0b0000011111100000;
    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)+2*2) = 0b0000011111100000;
    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)+2*3) = 0b0000011111100000;
    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)+1920*2) = 0b0000011111100000;
    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)+1920*2*2) = 0b0000011111100000;
    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)+1920*2*3) = 0b0000011111100000;
    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)+1920*2*3+2*3) = 0b0000011111100000;
    REG16(VIDEO_FRAME_BUFFER_ADDR(fb)+1920*2*3+2*4) = 0b0000011111100000;

    for (int i=0; i<64; i++)
    {
        REG16(VIDEO_FRAME_BUFFER_ADDR(fb)+1920*2*(1080-2)+(1920-i*10-1)*2) = 0b0000011111100000;
    }

    if (fb <= 1)
    {
        // PRINT("CPU1: Flush FB:%d\n" TERM_RESET, fb);
        // Xil_DCacheFlushRange(VIDEO_FRAME_BUFFER_ADDR(fb)+1920*2*(area->y1), 1920*2*(area->y2-area->y1));
        VIDEO_CTRL_FBSELECT_REG = fb;
        while (VIDEO_CTRL_FBSELECT_REG != fb) {}
    }
    else
    {
        PRINT("CPU1:" TERM_RED "ERROR: Flush called for invalid address\n" TERM_RESET);
    }

    lv_disp_flush_ready(dispDrv);
}

int main()
{
    if (Init() != XST_SUCCESS)
    {
        PRINT("CPU1: Init Failed\n");
        return XST_FAILURE;
    }

    PRINT("CPU1: Start!\n");

    PRINT("CPU1: Initialized!\n");


    PRINT("CPU1: Setting up display!\n");
    lv_disp_buf_t dispBuf; //Display Buffer descriptor
    lv_disp_buf_init(&dispBuf, (void *)VIDEO_FRAME_BUFFER_ADDR(0), (void *)VIDEO_FRAME_BUFFER_ADDR(1), 1080*1920);

    lv_disp_drv_t dispDrv; //Display Driver descriptor
    lv_disp_drv_init(&dispDrv);
    dispDrv.buffer = &dispBuf;
    dispDrv.flush_cb = FlushCallback; //Attach Flush Callback

    //Register the driver and save pointer to the created display
    lv_disp_t *display = lv_disp_drv_register(&dispDrv);
    (void)display; //Disable unused variable warning

    //Initialize Styles
    lv_style_t roundStyle;
    lv_style_init(&roundStyle);
    lv_style_set_radius(&roundStyle, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
    lv_style_set_bg_color(&roundStyle, LV_STATE_DEFAULT, LV_THEME_DEFAULT_COLOR_PRIMARY);

    lv_style_t textStyle1;
    lv_style_init(&textStyle1);
    lv_style_set_text_font(&textStyle1, LV_STATE_DEFAULT, &lv_font_montserrat_20);

    lv_style_t textStyle2;
    lv_style_init(&textStyle2);
    lv_style_set_text_font(&textStyle2, LV_STATE_DEFAULT, &lv_font_montserrat_28);

    //Initialize Display Objects
    lv_obj_t *screen = lv_scr_act();
    lv_obj_set_style_local_bg_color(screen, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    lv_obj_t *rect = lv_obj_create(screen, NULL);
    lv_obj_set_size(rect, 400, 200);

    lv_obj_t *rect2 = lv_obj_create(screen, NULL);
    lv_obj_set_size(rect2, 400, 200);

    lv_obj_t *dot = lv_obj_create(rect, NULL);
    lv_obj_add_style(dot, LV_OBJ_PART_MAIN, &roundStyle);
    lv_obj_set_size(dot, 50, 50);

    lv_obj_t * label1 = lv_label_create(screen, NULL);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
    lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#ffffff Demo abcdefghijklmnopqrstuvwxyz \\ / '");
    lv_obj_set_width(label1, 1000);
    lv_obj_add_style(label1, LV_OBJ_PART_MAIN, &textStyle1);
    lv_obj_align(label1, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

    lv_obj_t * label2 = lv_label_create(screen, NULL);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
    lv_label_set_recolor(label2, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label2, "#ffffff Demo abcdefghijklmnopqrstuvwxyz \\ / '");
    lv_obj_set_width(label2, 1000);
    lv_obj_add_style(label2, LV_OBJ_PART_MAIN, &textStyle2);
    lv_obj_align(label2, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 40);



    PRINT("CPU1: Begin mainloop\n");
    // uint32_t count = 0;
    lv_coord_t rectx = 0, recty = 0;
    lv_coord_t dotx = 0, doty = 0;
    s8 rectvelx = 1, rectvely = 1;
    s8 dotvelx = 1, dotvely = 1;
    while (1)
    {
        // PRINT("CPU1: %lu\n", count++);
        // Draw();

        rectx+=rectvelx; recty+=rectvely;
        if (rectx>=1920-lv_obj_get_width(rect) || rectx<=0) { rectvelx=-rectvelx; }
        if (recty>=1080-lv_obj_get_height(rect) || recty<=0) { rectvely=-rectvely; }
        lv_obj_set_pos(rect, rectx, recty);
        
        dotx+=dotvelx; doty+=dotvely;
        if (dotx>=400-lv_obj_get_width(dot) || dotx<=0) { dotvelx=-dotvelx; }
        if (doty>=200-lv_obj_get_height(dot) || doty<=0) { dotvely=-dotvely; }
        lv_obj_set_pos(dot, dotx, doty);


        lv_tick_inc(1); //Increment 1 ms

        lv_task_handler();

        usleep(1*1000); //1ms
    }

    return 0;
}


