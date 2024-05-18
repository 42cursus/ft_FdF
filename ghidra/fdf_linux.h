typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned char    dwfenc;
typedef unsigned int    dword;
typedef unsigned long    qword;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned char    undefined1;
typedef unsigned int    undefined4;
typedef unsigned long    undefined8;
typedef unsigned short    ushort;
typedef int    wchar_t;
typedef unsigned short    word;
#define unkbyte9   unsigned long long
#define unkbyte10   unsigned long long
#define unkbyte11   unsigned long long
#define unkbyte12   unsigned long long
#define unkbyte13   unsigned long long
#define unkbyte14   unsigned long long
#define unkbyte15   unsigned long long
#define unkbyte16   unsigned long long

#define unkuint9   unsigned long long
#define unkuint10   unsigned long long
#define unkuint11   unsigned long long
#define unkuint12   unsigned long long
#define unkuint13   unsigned long long
#define unkuint14   unsigned long long
#define unkuint15   unsigned long long
#define unkuint16   unsigned long long

#define unkint9   long long
#define unkint10   long long
#define unkint11   long long
#define unkint12   long long
#define unkint13   long long
#define unkint14   long long
#define unkint15   long long
#define unkint16   long long

#define unkfloat1   float
#define unkfloat2   float
#define unkfloat3   float
#define unkfloat5   double
#define unkfloat6   double
#define unkfloat7   double
#define unkfloat9   long double
#define unkfloat11   long double
#define unkfloat12   long double
#define unkfloat13   long double
#define unkfloat14   long double
#define unkfloat15   long double
#define unkfloat16   long double

#define BADSPACEBASE   void
#define code   void


typedef struct _struct_125 _struct_125, *P_struct_125;

struct _struct_125 {
    int x;
    int y;
};

typedef struct s_fdf_struct s_fdf_struct, *Ps_fdf_struct;

typedef struct s_fdf_struct t_fdf_struct;

typedef struct s_xvar s_xvar, *Ps_xvar;

typedef struct s_xvar t_xvar;

typedef struct s_win_list s_win_list, *Ps_win_list;

typedef struct s_win_list t_win_list;

typedef struct s_list_node s_list_node, *Ps_list_node;

typedef struct s_list_node t_list_node;

typedef struct _XGC _XGC, *P_XGC;

typedef struct _XGC * GC;

typedef struct s_event_list s_event_list, *Ps_event_list;

typedef struct s_event_list t_event_list;

struct s_event_list {
    int mask;
    int (* hook)(void);
    void * param;
};

struct s_win_list {
    Window window;
    GC gc;
    t_win_list * next;
    int (* mouse_hook)(void);
    int (* key_hook)(void);
    int (* expose_hook)(void);
    void * mouse_param;
    void * key_param;
    void * expose_param;
    t_event_list hooks[36];
};

struct s_list_node {
    char * line;
    char * * word_tab;
    int * * coord;
    int * color;
    t_list_node * next;
};

struct s_xvar {
    Display * display;
    Window root;
    int screen;
    int depth;
    struct Visual * visual;
    Colormap cmap;
    int private_cmap;
    t_win_list * win_list;
    int (* loop_hook)(void);
    void * loop_param;
    int use_xshm;
    int pshm_format;
    int do_flush;
    int decrgb[6];
    Atom wm_delete_window;
    Atom wm_protocols;
    int end_loop;
};

struct s_fdf_struct {
    int w_width;
    int w_height;
    t_xvar * mlx_app;
    t_win_list * main_win;
    t_list_node * map;
    int line_length;
    int line_number;
    int case_size;
    int z_size;
    int local_30;
    char * filename;
    int custom_colour;
};

typedef struct s_args s_args, *Ps_args;

struct s_args {
    char * prog_name;
    char * filename;
    char * case_size;
    char * z_size;
};

typedef struct s_xpm_col s_xpm_col, *Ps_xpm_col;

typedef struct s_xpm_col t_xpm_col;

struct s_xpm_col {
    int name;
    int col;
};

typedef struct s_args t_arguments;

typedef struct s_col_name s_col_name, *Ps_col_name;

struct s_col_name {
    char * name;
    int color;
};

typedef struct s_img s_img, *Ps_img;

typedef struct s_img t_img;

int _init(EVP_PKEY_CTX *ctx);
void FUN_00401020(void);
int main(int argc,char **argv);
int out(int key);
void * on_expose(t_fdf_struct *fdf);
void sub_draw_line(long param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7);
void draw_line(long param_1,int param_2,int param_3,int param_4,int param_5,int param_6);
char * get_next_line(int fd);
char ** my_str_to_wordtab(char *str);
void data_convert(t_fdf_struct *fdf,t_list_node *param_2);
void load_data(t_fdf_struct *fdf);
void sub_draw_line_d(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2,int orientation);
void draw_line_d(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2);


