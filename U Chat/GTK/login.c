#include "login.h"
#include "main.h"

/*功能函数*/
//const char * password = "secret"

void closesoft(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}

void login_clicked (GtkWidget *button, gpointer data)
{
/*    const char *password_text = gtk_entry_get_text(GTK_ENTRY((GtkWidget *) data));

    if(strcmp(password_text, password) == 0)
    printf("Access granted!\n");
    else
    printf("Access denied!\n");*/
    printf("数据库接口，检测账号密码是否正确！\n");
    gtk_main_quit();
}

void regist_clicked(GtkWidget* button,gpointer data)
{
    printf("注册接口\n");
    gtk_main_quit();
    gtk_widget_hide_all(data); 
    gtk_widget_show_all(registUI_window);
    gtk_main();
}

void forget_clicked(GtkWidget* button,gpointer data)
{
    printf("找回密码接口\n");
    gtk_main_quit();
 /*   gtk_widget_hide_all(data);
    gtk_widget_show_all(regist_window);*/
}

GtkWidget * loginUI()
{
/*定义*/
    GtkWidget *window;
    GtkWidget *logo;
    GtkWidget *portrait;
    GtkWidget *regist, *forget;	//注册账号和找回密码按钮
    GtkWidget *username_entry, *password_entry;	//填充entry
    GtkWidget *ok_button;	//登录button
    GtkWidget *hbox1, *hbox2, *hbox3, *hbox4;	//横向盒子
    GtkWidget *vbox1, *vbox2;	//纵向盒子
    //给portrait设置一张图片
    GtkWidget *image = gtk_image_new_from_file("./2.png");
    
//    gtk_init(&argc, &argv);

/*window设计*/    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//创建窗口，窗口为最上层的主窗口
    gtk_window_set_title(GTK_WINDOW(window), "SUNNY");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
/*确定是否退出*/
    gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(closesoft), NULL);
/*button设计*/ 
    logo = gtk_label_new("logo");
    regist = gtk_button_new();
    forget = gtk_button_new();
    portrait = gtk_button_new();
    username_entry = gtk_entry_new();
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);	//设置密码不可视
    ok_button = gtk_button_new_with_label("登录");
    regist = gtk_button_new_with_label("注册账号");
    forget = gtk_button_new_with_label("找回密码");

    gtk_container_add(GTK_CONTAINER(portrait), image);

/*功能函数调用*/
    g_signal_connect(GTK_OBJECT(ok_button), "clicked", GTK_SIGNAL_FUNC(login_clicked), password_entry);
    g_signal_connect(GTK_OBJECT(regist), "clicked", GTK_SIGNAL_FUNC(regist_clicked), window);
    g_signal_connect(GTK_OBJECT(regist), "clicked", GTK_SIGNAL_FUNC(forget_clicked), NULL);
/*盒子设计*/
    hbox1 = gtk_hbox_new(FALSE, 5);	//横向盒子，每个框具有相同大小，对象之间距离为5
    hbox2 = gtk_hbox_new(FALSE, 5);
    hbox3 = gtk_hbox_new(FALSE, 5);
    hbox4 = gtk_hbox_new(FALSE, 5);
    vbox1 = gtk_vbox_new(FALSE, 10);
    vbox2 = gtk_vbox_new(FALSE, 10);
    gtk_widget_set_size_request(username_entry, 200, 35);
    gtk_widget_set_size_request(password_entry, 200, 35);
    gtk_widget_set_size_request(portrait, 100, 100);
    /*从左向右，对象扩展，多余空间分配给对象，两边距离为5*/
    gtk_box_pack_start(GTK_BOX(hbox1), username_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), regist, TRUE, FALSE, 5);
    
    gtk_box_pack_start(GTK_BOX(hbox2), password_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox2), forget, TRUE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(vbox1), hbox1, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox1), hbox2, TRUE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(hbox3), portrait, TRUE, FALSE, 30);
    gtk_box_pack_start(GTK_BOX(hbox3), vbox1, TRUE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(hbox4), ok_button, TRUE, TRUE, 100);

    gtk_box_pack_end(GTK_BOX(vbox2), hbox4, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(vbox2), hbox3, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(vbox2), logo, TRUE, TRUE, 5);

    gtk_container_add(GTK_CONTAINER(window), vbox2);	//盒子装入window
/*显示*/
    return window;
//    gtk_main();
    return 0;
}