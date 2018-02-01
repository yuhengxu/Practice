#include<gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
/*全局变量声明区-----------------------------------------------------------------*/
    GtkWidget *Send_textview/*定义发送文本区*/,
          *Rcv_textview/*定义接收文本区*/;
    GtkTextBuffer *Send_buffer/*定义发送文本缓冲区*/,
              *Rcv_buffer/*定义接收文本缓冲区*/;

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
void Clear_Local_message()
{
    GtkTextIter start,end;
        gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(Send_buffer),&start,&end);/*获得缓冲区开始和结束位置的Iter*/
        gtk_text_buffer_delete(GTK_TEXT_BUFFER(Send_buffer),&start,&end);/*插入到缓冲区*/
}
/*----------------------------------------------------------------------------*/
void Put_Local_message(const gchar *text)
{
    GtkTextIter start,end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(Rcv_buffer),&start,&end);/*获得缓冲区开始和结束位置的Iter*/
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,"我说:\n",8);/*插入文本到缓冲区*/
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,text,strlen(text));/*插入文本到缓冲区*/
        gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,"\n",1);/*插入文本到缓冲区*/
}
/*----------------------------------------------------------------------------*/
void Show_Err(char *err)
{
    GtkTextIter start,end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(Rcv_buffer),&start,&end);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(Rcv_buffer),&end,err,strlen(err));
}
/*----------------------------------------------------------------------------*/
/*发送函数----------------------------------------------------------------------*/
void on_send(GtkButton *SaveButton, GtkWidget *Send_textview)/*保存按钮的回调函数，每当‘保存’按钮被按下的时候，都会触发这个函数*/
{
    //GtkTextBuffer *S_buffer/*定义发送文本区缓冲区*/,*R_buffer/*定义接收文本缓冲区*/;
    GtkTextIter start,end;/*定义迭代器起点终点*/
    gchar *S_text,*R_text;/*定义文字存储变量*/

    //S_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Send_textview));/*获取文本区*/
    //gtk_text_buffer_get_start_iter(Send_buffer,&start);/*得到当前文本区域的起始位置*/
    //gtk_text_buffer_get_end_iter(Send_buffer,&end);/*得到当前文本区域的结束位置*/
    //S_text = gtk_text_buffer_get_text(Send_buffer,&start,&end,TRUE/*FALSE*/);/*返回start end之间的所有文本，最后一个参数是TRUE的话那么可见的文本都将被返回*/
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(Send_buffer),&start,&end);
    S_text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(Send_buffer),&start,&end,FALSE);

    //g_print("%s\n",S_text);/*2种方式都可以输出文本区域的内容*/
    //g_print(S_text);
    
    //R_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Rcv_textview));/*获取接收文本缓冲区*/
    R_text = S_text;/*把发送文本交换到接收文本*/
    //gtk_text_buffer_set_text(R_buffer,R_text,-1);/*在接收文本区显示发送的内容*/
    //gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(R_buffer),&start,&end);/*获得缓冲区开始和结束位置的Iter*/
        //gtk_text_buffer_insert(GTK_TEXT_BUFFER(R_buffer),&end,"我说: ",8);/*插入文本到缓冲区*/
        //gtk_text_buffer_insert(GTK_TEXT_BUFFER(R_buffer),&end,R_text,strlen(R_text));/*插入文本到缓冲区*/
        //gtk_text_buffer_insert(GTK_TEXT_BUFFER(R_buffer),&end,"\n",1);/*插入文本到缓冲区*/
    if(strcmp(R_text,"")!=0)
    {
        //Get_Local_message();
        Clear_Local_message();
        Put_Local_message(R_text);    
    }
    else
        {
            Show_Err("消息不能为空...\n");
        }
    free(R_text);
    //free(S_text);
}
/*----------------------------------------------------------------------------*/
/*关闭函数---------------------------------------------------------------------*/
void on_close(GtkButton *CloseButton,GtkWidget *Send_textview)
{
gtk_main_quit();
}
/*----------------------------------------------------------------------------*/


/*主函数-----------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
/*主函数变量声明区*/
    GtkWidget *window/*定义主窗口*/,
          *Send_scrolled_win/*定义发送滚动窗口*/,
          *Rcv_scrolled_win/*定义接收滚动窗口*/;
    GtkWidget *talk_vbox/*定义垂直盒子*/,
          *list_vbox;
    GtkWidget *big_hbox;
    GtkWidget *Button_Box/*定义按钮盒*/,
          *SaveButton/*定义保存按钮*/,
          *CloseButton/*定义关闭按钮*/;
    GtkWidget *hseparator/*定义水平分割线*/;
          //*panel_v/*定义垂直分割面板*/, 
          //*panel_h/*定义水平分割面板*/;



          /*tianjia gdnfgksdblhsdfnhlkdsjophskogijseogdr*/
          GtkWidget *view;
          GtkWidget *statusbar;
          GtkTreeSelection *selection; 



    gtk_init(&argc,&argv);/*GTK初始化*/
/*函数实现区*/

    /*------------------------------绘制主窗口----------------------------*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);/*生成主窗口*/
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);/*连接信号，关闭窗口*/
    gtk_window_set_title(GTK_WINDOW(window),"Save Text");/*设置主窗口标题*/
    gtk_container_set_border_width(GTK_CONTAINER(window),10);/*设置主窗口边框*/
    gtk_widget_set_size_request(window,750,750);/*设置主窗口初始化大小*/
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);/*设置主窗口初始位置*/
        /*------------------------------设置Send_text view-------------------------*/
    Send_textview = gtk_text_view_new();/*生成text view*/
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(Send_textview),GTK_WRAP_WORD);/*处理多行显示的模式*/
    gtk_text_view_set_justification(GTK_TEXT_VIEW(Send_textview),GTK_JUSTIFY_LEFT);/*控制文字显示方向的,对齐方式*/
    gtk_text_view_set_editable(GTK_TEXT_VIEW(Send_textview),TRUE);/*允许text view内容修改*/
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(Send_textview),TRUE);/*设置光标可见*/
        gtk_text_view_set_pixels_above_lines(GTK_TEXT_VIEW(Send_textview),5);/*设置上行距*/
    gtk_text_view_set_pixels_below_lines(GTK_TEXT_VIEW(Send_textview),5);/*设置下行距*/
    gtk_text_view_set_pixels_inside_wrap(GTK_TEXT_VIEW(Send_textview),5);/*设置词距*/
        gtk_text_view_set_left_margin(GTK_TEXT_VIEW(Send_textview),1);/*设置左边距*/
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(Send_textview),1);/*设置右边距*/
    Send_buffer =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(Send_textview));/*返回text view被显示的buffer*/
        /*------------------------------设置Rcv_text view-------------------------*/
    Rcv_textview = gtk_text_view_new();/*生成text view*/
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(Rcv_textview),GTK_WRAP_WORD);/*处理多行显示的模式*/
    gtk_text_view_set_justification(GTK_TEXT_VIEW(Rcv_textview),GTK_JUSTIFY_LEFT);/*控制文字显示方向的,对齐方式*/
    gtk_text_view_set_editable(GTK_TEXT_VIEW(Rcv_textview),TRUE);/*允许text view内容修改*/
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(Rcv_textview),TRUE);/*设置光标可见*/
        gtk_text_view_set_pixels_above_lines(GTK_TEXT_VIEW(Rcv_textview),5);/*设置上行距*/
    gtk_text_view_set_pixels_below_lines(GTK_TEXT_VIEW(Rcv_textview),5);/*设置下行距*/
    gtk_text_view_set_pixels_inside_wrap(GTK_TEXT_VIEW(Rcv_textview),5);/*设置词距*/
        gtk_text_view_set_left_margin(GTK_TEXT_VIEW(Rcv_textview),10);/*设置左边距*/
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(Rcv_textview),10);/*设置右边距*/
    gtk_text_view_set_editable(GTK_TEXT_VIEW(Rcv_textview),FALSE);/*设置接收文字区不可被编辑*/
    Rcv_buffer =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(Rcv_textview));/*返回text view被显示的buffer*/   

    /*------------------------------设置发送窗口滚动条-------------------------------*/
    Send_scrolled_win = gtk_scrolled_window_new(NULL,NULL);/*生成滚动条的窗口*/
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(Send_scrolled_win),Send_textview);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(Send_scrolled_win),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);/*滚动条属性*/
    /*------------------------------设置接收窗口滚动条-------------------------------*/
    Rcv_scrolled_win = gtk_scrolled_window_new(NULL,NULL);/*生成滚动条的窗口*/
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(Rcv_scrolled_win),Rcv_textview);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(Rcv_scrolled_win),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);/*滚动条属性*/
    /*------------------------------设置垂直盒子------------------------------*/
    talk_vbox = gtk_vbox_new(FALSE,0);/*生成一个垂直排布的盒子*/
    list_vbox = gtk_vbox_new(FALSE,0);/*生成一个水平排布的盒子*/
    big_hbox = gtk_hbox_new(FALSE,0);/*最大的盒子*/
    /*------------------------------设置发送按钮------------------------------*/
    SaveButton = gtk_button_new_with_label("发送");/*生成发送按钮*/
    g_signal_connect(G_OBJECT(SaveButton),"clicked",G_CALLBACK(on_send),(gpointer)Send_textview);/*给按钮加上回调函数*/
    /*------------------------------设置关闭按钮------------------------------*/
    CloseButton = gtk_button_new_with_label("关闭");/*生成关闭按钮*/
    g_signal_connect(G_OBJECT(CloseButton),"clicked",G_CALLBACK(on_close),(gpointer)Send_textview);
    /*------------------------------设置按钮盒子------------------------------*/     
    Button_Box = gtk_hbutton_box_new();/*生成按钮盒*/
    gtk_box_set_spacing(GTK_BOX(Button_Box),1);/*按钮之间的间隔*/
    gtk_button_box_set_layout(GTK_BUTTON_BOX(Button_Box),GTK_BUTTONBOX_END);/*按钮盒内部布局，风格是尾对齐*/
    gtk_container_set_border_width(GTK_CONTAINER(Button_Box),5);/*边框宽*/
    /*------------------------------设置分割线--------------------------------*/
    hseparator = gtk_hseparator_new();
    /*------------------------------设置分割面板------------------------------*/
    //panel_v = gtk_hpaned_new();
    //panel_h = gtk_vpaned_new();
    //gtk_paned_add1(GTK_PANED(panel_v),button1);
    //gtk_paned_add2(GTK_PANED(panel_h),Rcv_scrolled_win);
    //gtk_paned_add2(GTK_PANED(panel_h),Send_scrolled_win);
    /*------------------------------包装所有容器------------------------------*/
    //gtk_container_add(GTK_CONTAINER(Send_scrolled_win),Send_textview);/*包装textview到滚动条窗口*/
    //gtk_container_add(GTK_CONTAINER(Rcv_scrolled_win),Rcv_textview);/*包装textview到滚动条窗口*/
    gtk_container_add(GTK_CONTAINER(talk_vbox),Rcv_scrolled_win);/*包装滚动条窗口到主窗口*/
    gtk_container_add(GTK_CONTAINER(talk_vbox),hseparator);/*加入一条分割线*/
    gtk_container_add(GTK_CONTAINER(talk_vbox),Send_scrolled_win);/*包装滚动条窗口到主窗口*/    
    gtk_container_add(GTK_CONTAINER(talk_vbox),Button_Box);/*把按钮盒包装到vbox中*/
    gtk_box_pack_start(GTK_BOX(Button_Box),CloseButton,TRUE,TRUE,5);/*把关闭按钮包装到按钮盒里面去*/
    gtk_box_pack_start(GTK_BOX(Button_Box),SaveButton,TRUE,TRUE,5);/*把发送按钮包装到按钮盒里面去*/
    //gtk_container_add(GTK_CONTAINER(window),talk_vbox);/*将盒子封装到主窗口中去*/    
    /*------------------------------好友列表------------------------------*/


    










    //gtk_container_add(GTK_CONTAINER(big_hbox),list_vbox);
    //gtk_container_add(GTK_CONTAINER(big_hbox),talk_vbox);
    //gtk_container_add(GTK_CONTAINER(window),big_hbox);
    gtk_container_add(GTK_CONTAINER(window),talk_vbox);
    /*------------------------------显示所有东西------------------------------*/
    gtk_widget_show_all(window);/*显示所有东西*/
    gtk_main();/*主循环*/
    return 0;/*退出程序*/
    }
/*----------------------------------------------------------------------------*/

/*
客户端程序说明：
客户端需要完成的事情：
                     有一个输入文本区：用来输入本地消息
        有一个输出文本区：用来输出本地消息和远程消息
        有一个发送按钮  ：用来发送本地消息
        有一个关闭按钮  ：用来关闭客户端
客户端需要的函数：
        Get_Local_message();
        Put_Local_message();
        Clear_Local_message();
        Get_Remote_message();
        Put_Remote_message();
        Send_Button;
        Close_Button;
*/
