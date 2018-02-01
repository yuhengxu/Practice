#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
// GdkPixbuf *create_pixbuf(const gchar * filename)
// {
//     GdkPixbuf *pixbuf;
//     GError *error = NULL;
//     pixbuf = gdk_pixbuf_new_from_file(filename, &error);
//     if(!pixbuf) 
//     {
//         fprintf(stderr, "%s\n", error->message);
//         g_error_free(error);
//     }
//     return pixbuf;
// }



char * online_or()
{
    printf("调取数据库看对方是否在线\n");
    char *text = "在线";
    return text;
}

void change_word(GtkWidget* button,gpointer data)
{
    char *text;
    printf("输入文本\n");
    text = "这里是签名";
    gtk_label_set(GTK_LABEL(data),text);    
}


char* search_username(GtkWidget* button,gpointer data)
{
    const char * name;
    name = gtk_entry_get_text(GTK_ENTRY(data));
    printf("查找名字是%s的用户，弹出加好友界面\n", name);

    return name;
}


void change_key(GtkWidget* button,gpointer data)
{
    printf("调取登入者名字，弹出密码修改界面，修改其密码\n");
}



enum
{
    COLUMN = 0,
    NUM_COLS
} ;
GtkTreeStore *treestore;    
GtkTreeIter toplevel, child;
treestore = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING);
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
    // GtkTreeStore *treestore;    
    // GtkTreeIter toplevel, child;
    // treestore = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING);
    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel,COLUMN, "Scriptinglanguages", -1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, COLUMN, "Python", -1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, COLUMN, "Perl",-1);
    gtk_tree_store_append(treestore, &child, &toplevel);
    gtk_tree_store_set(treestore, &child, COLUMN, "PHP",-1);
    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel, COLUMN, "Compiledlanguages",-1);
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
    GtkTreeModel *model;
    view = gtk_tree_view_new();
    col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(col, "Programming languages");
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(col, renderer, "text", COLUMN);
    model = create_and_fill_model();
    gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
    g_object_unref(model);
    return view;
}

/*动态添加好友*/
void add_friends(char* name)
{
    gtk_tree_store_insert_with_values(&treestore, NULL, &toplevel, -1, name);//树装列表，哪个分支，选择有效分支，放在该列表的位置，名称
    gtk_widget_show_all(&treestore);
}




int main(int argc, char *argv[])
{

    GtkWidget *window;
    GtkWidget *search_entry;
    GtkWidget *search;
    GtkWidget *hbox0, *hbox1, *hbox2, *hbox3;
    GtkWidget *vbox0, *vbox;
    GtkWidget *portrait;	//头像
    GtkWidget *online;	//在线状态
    GtkWidget *qianming;
    GtkWidget *smile, *word;
    GtkWidget *image = gtk_image_new_from_file("./2.png");
    GtkWidget *SaveButton,
              *CloseButton;
    GtkTreeSelection *selection;
    GtkWidget *tree_vbox;
    GtkWidget *statusbar;
    GtkWidget *view;
    GtkWidget *friends_list_vbox;
//    GtkWidget *hseparator1, *hseparator2/*定义水平分割线*/;

    gtk_init(&argc,&argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"STAY REAL");
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    gtk_widget_set_size_request(window,370,600);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    //gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("web.png"));


    search_entry = gtk_entry_new();
    qianming = gtk_label_new("空");

    friends_list_vbox = gtk_vbox_new(FALSE, 2);
    tree_vbox = gtk_vbox_new(FALSE, 2);
    view = create_view_and_model();
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
    gtk_box_pack_start(GTK_BOX(tree_vbox), view, TRUE, TRUE, 1);
    statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(tree_vbox), statusbar, FALSE, TRUE, 1);
    g_signal_connect(selection, "changed", G_CALLBACK(on_changed),statusbar);

    SaveButton = gtk_button_new_with_label("密码修改");
    g_signal_connect(G_OBJECT(SaveButton),"clicked",G_CALLBACK(change_key),NULL);

    CloseButton = gtk_button_new_with_label("编辑签名");
    g_signal_connect(G_OBJECT(CloseButton),"clicked",G_CALLBACK(change_word),qianming);
   
    search = gtk_button_new_with_label("搜索");
    g_signal_connect(G_OBJECT(search),"clicked",G_CALLBACK(search_username),search_entry);
    //g_signal_connect(G_OBJECT(search),"clicked",G_CALLBACK(add_friends),search_entry);
    char * name = "jshcsv";
    add_friends(name);
    
    portrait = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(portrait), image);
    
    online=gtk_label_new(NULL);
    gtk_label_set(GTK_LABEL(online),online_or());    
    
    smile = gtk_button_new();
    word =  gtk_button_new();
    smile = gtk_button_new_with_label("好友");
    word = gtk_button_new_with_label("群组");
    
    hbox0 = gtk_hbox_new(FALSE, 0);
    hbox1 = gtk_hbox_new(FALSE, 5);	//横向盒子，每个框具有相同大小，对象之间距离为5
    hbox2 = gtk_hbox_new(FALSE, 0);
    hbox3 = gtk_hbox_new(FALSE, 5);
    vbox0 = gtk_vbox_new(FALSE, 5);
    vbox = gtk_vbox_new(FALSE, 5);
//    hseparator1 = gtk_hseparator_new();
//    hseparator2 = gtk_hseparator_new();

    gtk_widget_set_size_request(tree_vbox, 350, 400);
    gtk_widget_set_size_request(portrait, 50, 50);
    gtk_widget_set_size_request(search_entry, 280, 20);
    gtk_widget_set_size_request(search, 40, 20);
    gtk_widget_set_size_request(online, 40, 20);
    gtk_widget_set_size_request(smile, 160, 20);
    gtk_widget_set_size_request(word, 160, 20);
    gtk_widget_set_size_request(SaveButton, 80, 20);
    gtk_widget_set_size_request(CloseButton, 80, 20);
    
    gtk_box_pack_start(GTK_BOX(vbox0), online, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox0), qianming, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(hbox0), search_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox0), search, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(hbox1), portrait, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), vbox0, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(hbox2), smile, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), word, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(hbox3), SaveButton, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox3), CloseButton, FALSE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(vbox),hbox1);
//    gtk_container_add(GTK_CONTAINER(vbox),hseparator1);
    gtk_container_add(GTK_CONTAINER(vbox),hbox0);
//    gtk_container_add(GTK_CONTAINER(vbox),hseparator2);
    gtk_container_add(GTK_CONTAINER(vbox),hbox2);
    gtk_container_add(GTK_CONTAINER(vbox),tree_vbox);
    gtk_container_add(GTK_CONTAINER(vbox),hbox3);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
