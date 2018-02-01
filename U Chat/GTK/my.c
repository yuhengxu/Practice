#include <gtk/gtk.h>

/*********************应用图图标*****************************/
GdkPixbuf *create_pixbuf(const gchar * filename)
{
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf) 
    {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }
    return pixbuf;
}

/*********************树装列表*****************************/
enum
{
    COLUMN = 0,
    NUM_COLS
} ;
void on_changed(GtkWidget *widget, gpointer statusbar) 
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    char *value;
    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)) 
    {
        gtk_tree_model_get(model, &iter, COLUMN, &value,-1);
        gtk_statusbar_push(GTK_STATUSBAR(statusbar),
        gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar),value), value);
        g_free(value);
    }
}
static GtkTreeModel *create_and_fill_model (void)
{
    GtkTreeStore *treestore;    
    GtkTreeIter toplevel, child;
    treestore = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING);
    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel,COLUMN, "我的好友", -1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, COLUMN, "Python", -1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, COLUMN, "Perl",-1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, COLUMN, "PHP",-1);
    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel, COLUMN, "家人",-1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, COLUMN, "C",-1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, COLUMN, "C++",-1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, COLUMN, "Java",-1);
    return GTK_TREE_MODEL(treestore);
}
static GtkWidget *create_view_and_model (void)
{
    GtkTreeViewColumn *col;
    GtkCellRenderer *renderer;
    GtkWidget *view;
    GtkTreeModel *model;view = gtk_tree_view_new();
    col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(col, "好友列表");
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(col, renderer, "text", COLUMN);
    model = create_and_fill_model();
    gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
    g_object_unref(model);
    return view;
}



int main( int argc, char *argv[])
{
GtkWidget *window;
GtkWidget *username_entry, *password_entry;	

gtk_init(&argc, &argv);

/**********************window绘制主窗口***************************/
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);/*生成主窗口*/
g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);/*连接信号，关闭窗口*/
gtk_window_set_title(GTK_WINDOW(window),"Save Text");/*设置主窗口标题*/
gtk_container_set_border_width(GTK_CONTAINER(window),10);/*设置主窗口边框*/
gtk_widget_set_size_request(window,750,750);/*设置主窗口初始化大小*/
gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);/*设置主窗口初始位置*/

/**********************应用图标**********************/
//tk_window_set_default_size(GTK_WINDOW(window), 230, 150);
//gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("web.png"));

/**********************盒子设计**********************/
GtkWidget *usr_msg, *friends_num, *ect;
GtkWidget *hbox1, *hbox2, *hbox3, *hbox4;	//横向盒子
GtkWidget *vbox1, *vbox2, *vbox3, *vbox4;   //纵向盒子
GtkWidget *usr_msg_vbox, *friends_num_vbox, *ect_vbox;	//纵向盒子
hbox1 = gtk_hbox_new(FALSE, 5);	//横向盒子，每个框具有相同大小，对象之间距离为5
hbox2 = gtk_hbox_new(FALSE, 5);
hbox3 = gtk_hbox_new(FALSE, 5);
hbox4 = gtk_hbox_new(FALSE, 5);
vbox1 = gtk_vbox_new(FALSE, 5);	//纵向盒子，每个框具有相同大小，对象之间距离为5
vbox2 = gtk_vbox_new(FALSE, 5);
vbox3 = gtk_vbox_new(FALSE, 5);
vbox4 = gtk_vbox_new(FALSE, 5);



/**********************联系人信息盒子usr_vbox,好友数目盒子friends_num_vbox，待补充盒子ect_vbox，
********************************************将三个盒子装入vbox1中******************************/
usr_msg_vbox = gtk_vbox_new(FALSE, 10);//纵向盒子
friends_num_vbox = gtk_vbox_new(FALSE, 10);
ect_vbox = gtk_vbox_new(FALSE, 10);
vbox1 = gtk_vbox_new(FALSE, 10);
usr_msg = gtk_label_new("联系人信息");
friends_num = gtk_label_new("好友数目");
ect = gtk_label_new("其他信息");
gtk_box_pack_start(GTK_BOX(usr_msg_vbox), usr_msg, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(friends_num_vbox), friends_num, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(ect_vbox), ect, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(vbox1), usr_msg_vbox, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(vbox1), friends_num_vbox, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(vbox1), ect_vbox, TRUE, TRUE, 5);


/***************************************头像盒子**********************************************/
GtkWidget *image;
GtkWidget *head_show_vbox;//头像盒子
//GtkWidget *hbox1;//头像盒子与vbox1盒子横向排列
head_show_vbox = gtk_vbox_new(FALSE, 10);
gtk_container_set_border_width(GTK_CONTAINER(head_show_vbox), 2);
image = gtk_image_new_from_file("web.png");
gtk_container_add(GTK_CONTAINER(head_show_vbox), image);
gtk_box_pack_start(GTK_BOX(hbox1), head_show_vbox, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(hbox1), vbox1, TRUE, TRUE, 5);


/***************************************搜索好友**********************************************/
GtkWidget *table;
GtkWidget *label1;
GtkWidget *entry1;
table = gtk_table_new(3, 2, FALSE);
label1 = gtk_label_new("SearchName");
gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 0, 1,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
entry1 = gtk_entry_new();
gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 0, 1,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

gtk_box_pack_start(GTK_BOX(vbox2), hbox1, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(vbox2), table, TRUE, TRUE, 5);


/***************************************好友，群组，备用**********************************************/
GtkWidget *friends, *group, *sth;//都是button
friends = gtk_button_new_with_label("好友");//纵向盒子
group = gtk_button_new_with_label("群组");
sth = gtk_button_new_with_label("其他");
gtk_box_pack_start(GTK_BOX(hbox2), friends, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(hbox2), group, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(hbox2), sth, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(vbox3), vbox2, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(vbox3), hbox2, TRUE, TRUE, 5);//



/***************************************调用树装列表（好友列表，群组列表）**********************************************/
GtkTreeSelection *selection;
GtkWidget *tree_vbox;
GtkWidget *statusbar;
GtkWidget *view;
GtkWidget *friends_list_vbox;
friends_list_vbox = gtk_vbox_new(FALSE, 2);
tree_vbox = gtk_vbox_new(FALSE, 2);
view = create_view_and_model();
selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
gtk_box_pack_start(GTK_BOX(tree_vbox), view, TRUE, TRUE, 1);
statusbar = gtk_statusbar_new();
gtk_box_pack_start(GTK_BOX(tree_vbox), statusbar, FALSE, TRUE, 1);
g_signal_connect(selection, "changed", G_CALLBACK(on_changed),statusbar);
// gtk_box_pack_start(GTK_BOX(friends_list_vbox), friends, TRUE, TRUE, 5);
// gtk_box_pack_start(GTK_BOX(friends_list_vbox), tree_vbox, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(vbox3), tree_vbox, TRUE, TRUE, 5);//






/***************************************功能框**********************************************/
GtkWidget *fun_vbox;
GtkWidget *toolbar;
GtkToolItem *new;
GtkToolItem *open;
GtkToolItem *save;
GtkToolItem *sep;
GtkToolItem *exit;
fun_vbox = gtk_vbox_new(FALSE, 0);
toolbar = gtk_toolbar_new();
gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);
new = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new, -1);
open = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
gtk_toolbar_insert(GTK_TOOLBAR(toolbar), open, -1);
save = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
gtk_toolbar_insert(GTK_TOOLBAR(toolbar), save, -1);
sep = gtk_separator_tool_item_new();
gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);
exit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exit, -1);
gtk_box_pack_start(GTK_BOX(fun_vbox), toolbar, FALSE, FALSE, 5);
g_signal_connect(G_OBJECT(exit), "clicked",G_CALLBACK(gtk_main_quit), NULL);
gtk_box_pack_start(GTK_BOX(vbox3), fun_vbox, TRUE, TRUE, 5);//把功能框放入猪盒子

/***************************************装进window并show_all**********************************************/
gtk_container_add(GTK_CONTAINER(window), vbox3);	//盒子装入window
gtk_widget_show_all(window);
gtk_main();
return 0;
}