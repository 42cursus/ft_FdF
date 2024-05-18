
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <sys/syslog.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include <X11/extensions/XKBstr.h>
typedef struct _XDisplay Display;
//#include <X11/XKBlib.h>
#include <X11/xpm.h>


# define MLX_TYPE_SHM_PIXMAP 3
# define MLX_TYPE_SHM 2
# define MLX_TYPE_XIMAGE 1

# define MLX_MAX_EVENT LASTEvent


# define ENV_DISPLAY "DISPLAY"
# define LOCALHOST "localhost"
# define ERR_NO_TRUECOLOR "MinilibX Error : No TrueColor Visual available.\n"
# define WARN_SHM_ATTACH "MinilibX Warning : X server can't attach shared memory.\n"


typedef struct s_xpm_col {
	int name;
	int col;
} t_xpm_col;


struct s_col_name {
	char *name;
	int color;
};

typedef struct s_event_list {
	int mask;

	int (*hook)();

	void *param;
} t_event_list;

typedef struct s_win_list t_win_list;

struct s_win_list {
	Window window;
	GC gc;
	t_win_list *next;

	int (*mouse_hook)();

	int (*key_hook)();

	int (*expose_hook)();

	void *mouse_param;
	void *key_param;
	void *expose_param;
	t_event_list hooks[MLX_MAX_EVENT];
};

typedef struct s_img t_img;

typedef struct s_xvar {
	Display *display;
	Window root;
	int screen;
	int depth;
	Visual *visual;
	Colormap cmap;
	int private_cmap;
	t_win_list *win_list;

	int (*loop_hook)();

	void *loop_param;
	int use_xshm;
	int pshm_format;
	int do_flush;
	int decrgb[6];
	Atom wm_delete_window;
	Atom wm_protocols;
	int end_loop;
} t_xvar;



int	mlx_int_do_nothing(void *param);
int mlx_get_color_value(t_xvar *xvar, int color);
int mlx_int_get_good_color(t_xvar *xvar, int color);
int mlx_int_find_in_pcm();
int	mlx_int_anti_resize_win(t_xvar *xvar,Window win,int w,int h);
int	mlx_int_wait_first_expose(t_xvar *xvar,Window win);
int mlx_int_rgb_conversion(t_xvar *xvar);
int mlx_int_deal_shm(t_xvar *xvar);
void *mlx_int_new_xshm_image(t_xvar *xvar, int width, int height, int format);
char **mlx_int_str_to_wordtab(char *str);
void *mlx_new_image(t_xvar *xvar, int width, int height);
int shm_att_pb(Display *d, XErrorEvent *ev);
int mlx_int_get_visual(t_xvar *xvar);
int mlx_int_set_win_event_mask(t_xvar *xvar);
int mlx_int_str_str_cote(char *str, char *find, int len);
int mlx_int_str_str(char *str, char *find, int len);

t_xvar *mlx_init();
t_win_list *mlx_new_window(t_xvar *xvar, int size_x, int size_y, char *title);
int mlx_clear_window(t_xvar *xvar, t_win_list *win);
int mlx_pixel_put(t_xvar *xvar, t_win_list *win, int x, int y, int color);
char *mlx_get_data_addr(t_img *img, int *bits_per_pixel,
						int *size_line, int *endian);
int mlx_put_image_to_window(t_xvar *xvar, t_win_list *win, t_img *img,
							int x, int y);
int mlx_mouse_hook(t_win_list *win, int (*funct)(), void *param);
int mlx_key_hook(t_win_list *win, int (*funct)(), void *param);
int mlx_expose_hook(t_win_list *win, int (*funct)(), void *param);
int mlx_loop_hook(t_xvar *xvar, int (*funct)(), void *param);
int mlx_loop(t_xvar *xvar);
int mlx_loop_end(t_xvar *xvar);
int mlx_string_put(t_xvar *xvar, t_win_list *win,
				   int x, int y, int color, char *string);
void mlx_set_font(t_xvar *xvar, t_win_list *win, char *name);
t_img *mlx_xpm_to_image(t_xvar *xvar, char **xpm_data, int *width, int *height);
t_img *mlx_xpm_file_to_image(t_xvar *xvar, char *file, int *width, int *height);
int mlx_destroy_window(t_xvar *xvar, t_win_list *win);
int mlx_destroy_image(t_xvar *xvar, t_img *img);
int mlx_destroy_display(t_xvar *xvar);
int mlx_hook(t_win_list *win, int x_event, int x_mask,
			 int (*funct)(), void *param);
int mlx_do_key_autorepeatoff(t_xvar *xvar);
int mlx_do_key_autorepeaton(t_xvar *xvar);
int mlx_do_sync(t_xvar *xvar);
int mlx_mouse_get_pos(t_xvar *xvar, t_win_list *win,
					  int *win_x_return, int *win_y_return);
int mlx_mouse_move(t_xvar *xvar, t_win_list *win, int x, int y);
int mlx_mouse_hide(t_xvar *xvar, t_win_list *win);
int mlx_mouse_show(t_xvar *xvar, t_win_list *win);
int mlx_get_screen_size(t_xvar *mlx_ptr, int *sizex, int *sizey);

#define DEFAULT_CASE_SIZE 20

typedef struct s_args {
	char *prog_name;
	char *filename;
	char *case_size;
	char *z_size;
} t_arguments;

typedef struct s_list_node t_list_node;
struct s_list_node {
	char * line;
	char ** word_tab;
	int **heights;
	int *colors;
	t_list_node * next;
};

typedef struct s_fdf_struct {
	int w_width;
	int w_height;
	t_xvar *mlx_app;
	t_win_list *main_win;
	t_list_node *map;
	int cols;
	int rows; //current position
	int case_size;
	int z_size;
	int max_height;
	char *filename;
	int custom_colour;
} t_fdf_struct;

int out(int key);
int	main(int argc, char **argv);
void *on_expose (t_fdf_struct * fdf);
void load_data(t_fdf_struct * fdf);
char *get_next_line(int fd);
char **my_str_to_wordtab(char *str);
void data_convert(t_fdf_struct *fdf,t_list_node *param_2);
void draw_line(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2);

void sub_draw_line(t_fdf_struct *fdf,
				   int x,int y,int max_x,int max_y,int color1,int color2,int orientation);
void draw_line_d(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2);
void sub_draw_line_d(t_fdf_struct *fdf,
					 int x,int y,int max_x,int max_y,int color1,int color2,int orientation);