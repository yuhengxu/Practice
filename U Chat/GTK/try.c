#include <gtk/gtk.h>

enum
{
  COLUMN = 0,
  NUM_COLS
} ;

void  on_changed(GtkWidget *widget, gpointer statusbar) 
{
  GtkTreeIter iter;
  GtkTreeModel *model;
  char *value;


  if (gtk_tree_selection_get_selected(
      GTK_TREE_SELECTION(widget), &model, &iter)) {

    gtk_tree_model_get(model, &iter, COLUMN, &value,  -1);
    gtk_statusbar_push(GTK_STATUSBAR(statusbar),
        gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), 
            value), value);
    g_free(value);
  }
}


static GtkTreeModel *
create_and_fill_model (void)
{
  GtkTreeStore *treestore;
  GtkTreeIter toplevel, child;

  treestore = gtk_tree_store_new(NUM_COLS,
                  G_TYPE_STRING);

  gtk_tree_store_append(treestore, &toplevel, NULL);
  gtk_tree_store_set(treestore, &toplevel,
                     COLUMN, "Scripting languages",
                     -1);

  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,
                     COLUMN, "Python",
                     -1);
  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,
                     COLUMN, "Perl",
                     -1);
  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,
                     COLUMN, "PHP",
                     -1);

  gtk_tree_store_append(treestore, &toplevel, NULL);
  gtk_tree_store_set(treestore, &toplevel,
                     COLUMN, "Compiled languages",
                     -1);

  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,
                     COLUMN, "C",
                     -1);

  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,
                     COLUMN, "C++",
                     -1);

  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,
                     COLUMN, "Java",
                     -1);

  return GTK_TREE_MODEL(treestore);
}



static GtkWidget *
create_view_and_model (void)
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
  gtk_tree_view_column_add_attribute(col, renderer, 
      "text", COLUMN);

  model = create_and_fill_model();
  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
  g_object_unref(model); 

  return view;
}


/**************************桌面图标************************/
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
  return pixbuf; } 




int
main (int argc, char **argv)
{
  GtkWidget *window;//定义主窗口
  GtkWidget *view;
  GtkTreeSelection *selection; 
  GtkWidget *list_vbox;//定义垂直盒子
  GtkWidget *statusbar;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//生成主窗口
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);//窗口位置
  gtk_window_set_title(GTK_WINDOW(window), "Tree View");//设置窗口标题
  gtk_widget_set_size_request (window, 350, 300);//设置窗口大小

  /*********************桌面图标************************/
  gtk_window_set_title(GTK_WINDOW(window), "icon"); 
  gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("web.png")); //窗口设置图标用的
  gtk_widget_show(window); 
  g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL); 
  /*********************菜单************************/
  GtkWidget *menubar;
  GtkWidget *filemenu;
  GtkWidget *file;
  GtkWidget *quit;
  GtkWidget *head_vbox;
  head_vbox = gtk_vbox_new(FALSE, 0);



  list_vbox = gtk_vbox_new(FALSE, 2);//初始化盒子
  gtk_container_add(GTK_CONTAINER(window), list_vbox);//覆盖
  

  view = create_view_and_model();
  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));

  gtk_box_pack_start(GTK_BOX(list_vbox), view, TRUE, TRUE, 1);

  statusbar = gtk_statusbar_new();
  gtk_box_pack_start(GTK_BOX(list_vbox), statusbar, FALSE, TRUE, 1);

  g_signal_connect(selection, "changed", 
      G_CALLBACK(on_changed), statusbar);

  g_signal_connect (G_OBJECT (window), "destroy",
          G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}