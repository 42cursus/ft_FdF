#include "fdf_linux.h"

int main(int argc,char **argv)

{
  ulong uVar1;
  int shorest_side;
  int longest_side;
  t_fdf_struct fdf;
  t_arguments *args;
  int arg_num;
  int ret_code;
  
  ret_code = 0;
  args = (t_arguments *)argv;
  arg_num = argc;
  if ((argc != 2) && (argc != 4)) {
    printf("Usage : %s <filename> [ case_size z_size ]\n",*argv);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  fdf.filename = argv[1];
  fdf.map = NULL;
  fdf.custom_colour = 0;
  load_data(&fdf);
  if ((fdf.line_length != 0) && (fdf.line_number != 0)) {
    fdf.case_size = 0x14;
    if (fdf.line_length < fdf.line_number) {
      longest_side = fdf.line_number;
    }
    else {
      longest_side = fdf.line_length;
    }
    fdf.w_width = (longest_side * 0x118) / 10;
    if (1000 < fdf.w_width) {
      fdf.w_width = 1000;
      if (fdf.line_length < fdf.line_number) {
        shorest_side = fdf.line_number;
      }
      else {
        shorest_side = fdf.line_length;
      }
      fdf.case_size = (int)(10000 / (long)(shorest_side * 0xe)) + 1;
    }
    fdf.z_size = fdf.case_size;
    fdf.w_height = fdf.local_30 * fdf.case_size + (fdf.case_size * (fdf.line_length + fdf.line_number) * 7) / 0x14;
    if (800 < fdf.w_height) {
      fdf.w_height = 800;
      fdf.z_size = (800 - (fdf.case_size * (fdf.line_length + fdf.line_number) * 7) / 0x14) / fdf.local_30 + 1;
    }
    if (arg_num == 4) {
      uVar1 = strtoul(args->case_size,NULL,0);
      if (uVar1 != 0) {
        uVar1 = strtoul(args->z_size,NULL,0);
        if (uVar1 != 0) {
          uVar1 = strtoul(args->case_size,NULL,0);
          fdf.case_size = (int)uVar1;
          uVar1 = strtoul(args->z_size,NULL,0);
          fdf.z_size = (int)uVar1;
        }
      }
    }
    fdf.mlx_app = mlx_init();
    if (fdf.mlx_app == NULL) {
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    fdf.main_win = mlx_new_window(fdf.mlx_app,fdf.w_width,fdf.w_height,"fdf");
    on_expose(&fdf);
    mlx_key_hook(fdf.main_win,out,NULL);
    mlx_loop(fdf.mlx_app);
    return ret_code;
  }
  printf("No data found.\n");
                    /* WARNING: Subroutine does not return */
  exit(1);
}



int out(int key)

{
  if (key == 0x35) {
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  return 0;
}



void * on_expose(t_fdf_struct *fdf)

{
  int iVar1;
  int iVar2;
  t_list_node *current_node;
  int local_18;
  int local_14;
  
  current_node = fdf->map;
  iVar1 = fdf->line_number;
  while (local_18 = iVar1 + -1, 0 < local_18) {
    local_14 = fdf->line_length;
    while (iVar2 = local_14, local_14 = iVar2 + -1, 0 < local_14) {
      draw_line_d(fdf,((local_14 * fdf->case_size * 7) / 10 - (local_18 * fdf->case_size * 7) / 10) + fdf->w_width / 2,
                  fdf->w_height - ((int)current_node->coord[local_14] * fdf->z_size + (local_14 * fdf->case_size * 7) / 0x14 + (local_18 * fdf->case_size * 7) / 0x14),
                  (((iVar2 + -2) * fdf->case_size * 7) / 10 - (local_18 * fdf->case_size * 7) / 10) + fdf->w_width / 2,
                  fdf->w_height - ((int)current_node->coord[iVar2 + -2] * fdf->z_size + ((iVar2 + -2) * fdf->case_size * 7) / 0x14 + (local_18 * fdf->case_size * 7) / 0x14),
                  current_node->color[local_14],current_node->color[iVar2 + -2]);
      draw_line_d(fdf,((local_14 * fdf->case_size * 7) / 10 - (local_18 * fdf->case_size * 7) / 10) + fdf->w_width / 2,
                  fdf->w_height - ((int)current_node->coord[local_14] * fdf->z_size + (local_14 * fdf->case_size * 7) / 0x14 + (local_18 * fdf->case_size * 7) / 0x14),
                  ((local_14 * fdf->case_size * 7) / 10 - ((iVar1 + -2) * fdf->case_size * 7) / 10) + fdf->w_width / 2,
                  fdf->w_height - ((int)current_node->next->coord[local_14] * fdf->z_size + (local_14 * fdf->case_size * 7) / 0x14 + ((iVar1 + -2) * fdf->case_size * 7) / 0x14),
                  current_node->color[local_14],current_node->next->color[local_14]);
      if (fdf->custom_colour != 0) {
        draw_line_d(fdf,((local_14 * fdf->case_size * 7) / 10 - (local_18 * fdf->case_size * 7) / 10) + fdf->w_width / 2,
                    fdf->w_height - ((int)current_node->coord[local_14] * fdf->z_size + (local_14 * fdf->case_size * 7) / 0x14 + (local_18 * fdf->case_size * 7) / 0x14),
                    (((iVar2 + -2) * fdf->case_size * 7) / 10 - ((iVar1 + -2) * fdf->case_size * 7) / 10) + fdf->w_width / 2,
                    fdf->w_height -
                    ((int)current_node->next->coord[iVar2 + -2] * fdf->z_size + ((iVar2 + -2) * fdf->case_size * 7) / 0x14 + ((iVar1 + -2) * fdf->case_size * 7) / 0x14),
                    current_node->color[local_14],current_node->next->color[iVar2 + -2]);
      }
    }
    if (local_18 % (fdf->line_number / 10 + 1) == 0) {
      mlx_do_sync(fdf->mlx_app);
    }
    current_node = current_node->next;
    iVar1 = local_18;
  }
  return NULL;
}



void sub_draw_line(long param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7)

{
  int local_2c;
  int local_28;
  
  local_28 = 1;
  local_2c = param_2;
  if (param_4 < param_2) {
    local_28 = -1;
  }
  while (local_2c * local_28 <= param_4 * local_28) {
    if (param_7 == 0) {
      mlx_pixel_put(*(t_xvar **)(param_1 + 8),*(t_win_list **)(param_1 + 0x10),param_3 + ((param_5 - param_3) * (local_2c - param_2)) / (param_4 - param_2),local_2c,param_6);
    }
    else {
      mlx_pixel_put(*(t_xvar **)(param_1 + 8),*(t_win_list **)(param_1 + 0x10),local_2c,param_3 + ((param_5 - param_3) * (local_2c - param_2)) / (param_4 - param_2),param_6);
    }
    local_2c = local_28 + local_2c;
  }
  return;
}



void draw_line(long param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int local_30;
  int local_28;
  
  if (param_4 - param_2 < 0) {
    local_28 = -(param_4 - param_2);
  }
  else {
    local_28 = param_4 - param_2;
  }
  if (param_5 - param_3 < 0) {
    local_30 = -(param_5 - param_3);
  }
  else {
    local_30 = param_5 - param_3;
  }
  if (local_28 < local_30) {
    sub_draw_line(param_1,param_3,param_2,param_5,param_4,param_6,0);
  }
  else {
    if ((param_2 == param_4) && (param_3 == param_5)) {
      mlx_pixel_put(*(t_xvar **)(param_1 + 8),*(t_win_list **)(param_1 + 0x10),param_2,param_5,param_6);
    }
    else {
      sub_draw_line(param_1,param_2,param_3,param_4,param_5,param_6,1);
    }
  }
  return;
}



char * get_next_line(int fd)

{
  ssize_t sVar1;
  char *pcVar2;
  size_t sVar3;
  size_t sVar4;
  char *__dest;
  int local_18;
  char *local_10;
  
  if ((get_next_line_size < 0) || (get_next_line_size <= get_next_line_pos)) {
    sVar1 = read(fd,get_next_line_buffer,0x2a);
    get_next_line_size = (int)sVar1;
    if ((get_next_line_size == 0) || (get_next_line_size == -1)) {
      return NULL;
    }
    get_next_line_pos = 0;
  }
  local_18 = get_next_line_pos;
  while( true ) {
    if (get_next_line_size <= local_18) {
      local_10 = (char *)malloc((long)((local_18 - get_next_line_pos) + 1));
      strncpy(local_10,get_next_line_buffer + get_next_line_pos,(long)(local_18 - get_next_line_pos));
      local_10[local_18 - get_next_line_pos] = '\0';
      get_next_line_size = 0xffffffff;
      pcVar2 = get_next_line(fd);
      if (pcVar2 != NULL) {
        sVar3 = strlen(local_10);
        sVar4 = strlen(pcVar2);
        __dest = (char *)malloc(sVar3 + sVar4 + 1);
        sVar3 = strlen(local_10);
        strncpy(__dest,local_10,sVar3);
        sVar3 = strlen(local_10);
        sVar4 = strlen(pcVar2);
        strncpy(__dest + sVar3,pcVar2,sVar4);
        sVar3 = strlen(local_10);
        sVar4 = strlen(pcVar2);
        __dest[sVar3 + sVar4] = '\0';
        free(local_10);
        free(pcVar2);
        local_10 = __dest;
      }
      return local_10;
    }
    if (get_next_line_buffer[local_18] == '\n') break;
    local_18 = local_18 + 1;
  }
  pcVar2 = (char *)malloc((long)((local_18 - get_next_line_pos) + 1));
  strncpy(pcVar2,get_next_line_buffer + get_next_line_pos,(long)(local_18 - get_next_line_pos));
  pcVar2[local_18 - get_next_line_pos] = '\0';
  get_next_line_pos = local_18 + 1;
  return pcVar2;
}



char ** my_str_to_wordtab(char *str)

{
  size_t length;
  bool is_space;
  int i;
  int j;
  char **str_tab;
  
  length = strlen(str);
  i = 0;
  j = 0;
  while (j < (int)length) {
    while (str[j] == ' ') {
      j = j + 1;
    }
    if (str[j] != '\0') {
      i = i + 1;
    }
    while( true ) {
      is_space = false;
      if (str[j] != '\0') {
        is_space = str[j] != ' ';
      }
      if (!is_space) break;
      j = j + 1;
    }
  }
  str_tab = (char **)malloc((long)(i + 1) << 3);
  if (str_tab == NULL) {
    str_tab = NULL;
  }
  else {
    i = 0;
    j = 0;
    while (j < (int)length) {
      while (str[j] == ' ') {
        str[j] = '\0';
        j = j + 1;
      }
      if (str[j] != '\0') {
        str_tab[i] = str + j;
        i = i + 1;
      }
      while( true ) {
        is_space = false;
        if (str[j] != '\0') {
          is_space = str[j] != ' ';
        }
        if (!is_space) break;
        j = j + 1;
      }
    }
    str_tab[i] = NULL;
  }
  return str_tab;
}



void data_convert(t_fdf_struct *fdf,t_list_node *param_2)

{
  int **coordinates;
  int *color_map;
  ulong uVar1;
  char *local_28;
  int i;
  t_list_node *current_node;
  t_fdf_struct *l_fdf;
  
  current_node = param_2;
  l_fdf = fdf;
  coordinates = (int **)malloc((long)fdf->line_length << 3);
  current_node->coord = coordinates;
  color_map = (int *)malloc((long)l_fdf->line_length << 2);
  current_node->color = color_map;
  i = l_fdf->line_length;
  while (i != 0) {
    current_node->color[i + -1] = 0xffffff;
    i = i + -1;
  }
  i = 0;
  while( true ) {
    if (l_fdf->line_length <= i) {
      return;
    }
    if (current_node->word_tab[i] == NULL) break;
    color_map = (int *)strtol(current_node->word_tab[i],&local_28,0);
    current_node->coord[i] = color_map;
    if ((long)l_fdf->local_30 < (long)current_node->coord[i]) {
      l_fdf->local_30 = (int)current_node->coord[i];
    }
    if (*local_28 == ',') {
      uVar1 = strtoul(local_28 + 1,NULL,0);
      current_node->color[i] = (int)uVar1;
      l_fdf->custom_colour = 1;
    }
    i = i + 1;
  }
  printf("Found wrong line length. Exiting.\n");
                    /* WARNING: Subroutine does not return */
  exit(1);
}



void load_data(t_fdf_struct *fdf)

{
  int fd;
  char *line;
  t_list_node *current_node;
  char **w_tab;
  bool is_last;
  t_list_node *next_node;
  
  fd = open(fdf->filename,0);
  if (fd != -1) {
    while (line = get_next_line(fd), line != NULL) {
      current_node = (t_list_node *)malloc(0x28);
      current_node->line = line;
      w_tab = my_str_to_wordtab(current_node->line);
      current_node->word_tab = w_tab;
      current_node->next = fdf->map;
      fdf->map = current_node;
    }
    close(fd);
    next_node = NULL;
    while (fdf->map != NULL) {
      current_node = fdf->map->next;
      fdf->map->next = next_node;
      next_node = fdf->map;
      fdf->map = current_node;
    }
    fdf->map = next_node;
    fdf->line_length = 0;
    while( true ) {
      is_last = false;
      if (fdf->map != NULL) {
        is_last = fdf->map->word_tab[fdf->line_length] != NULL;
      }
      if (!is_last) break;
      fdf->line_length = fdf->line_length + 1;
    }
    fdf->line_number = 0;
    fdf->local_30 = 0;
    next_node = fdf->map;
    while (next_node != NULL) {
      data_convert(fdf,next_node);
      fdf->line_number = fdf->line_number + 1;
      next_node = next_node->next;
    }
    return;
  }
  printf("No file %s\n",fdf->filename);
                    /* WARNING: Subroutine does not return */
  exit(1);
}



void sub_draw_line_d(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2,int orientation)

{
  uint uVar1;
  uint uVar2;
  int color;
  int local_2c;
  int local_28;
  
  local_28 = 1;
  if (max_x < x) {
    local_28 = -1;
  }
  uVar1 = color1 >> 0x10 & 0xff;
  uVar2 = color1 >> 8 & 0xff;
  local_2c = x;
  while (local_2c * local_28 <= max_x * local_28) {
    color = (uVar1 + (int)((local_2c - x) * ((color2 >> 0x10 & 0xffU) - uVar1)) / (max_x - x) & 0xff) * 0x10000 +
            (uVar2 + (int)((local_2c - x) * ((color2 >> 8 & 0xffU) - uVar2)) / (max_x - x) & 0xff) * 0x100 +
            ((color1 & 0xffU) + (int)((local_2c - x) * ((color2 & 0xffU) - (color1 & 0xffU))) / (max_x - x) & 0xff);
    if (orientation == 0) {
      mlx_pixel_put(fdf->mlx_app,fdf->main_win,y + ((max_y - y) * (local_2c - x)) / (max_x - x),local_2c,color);
    }
    else {
      mlx_pixel_put(fdf->mlx_app,fdf->main_win,local_2c,y + ((max_y - y) * (local_2c - x)) / (max_x - x),color);
    }
    local_2c = local_28 + local_2c;
  }
  return;
}



void draw_line_d(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2)

{
  int local_30;
  int local_28;
  
  if (max_x - x < 0) {
    local_28 = -(max_x - x);
  }
  else {
    local_28 = max_x - x;
  }
  if (max_y - y < 0) {
    local_30 = -(max_y - y);
  }
  else {
    local_30 = max_y - y;
  }
  if (local_28 < local_30) {
    sub_draw_line_d(fdf,y,x,max_y,max_x,color1,color2,0);
  }
  else {
    if ((x == max_x) && (y == max_y)) {
      mlx_pixel_put(fdf->mlx_app,fdf->main_win,x,max_y,color1);
    }
    else {
      sub_draw_line_d(fdf,x,y,max_x,max_y,color1,color2,1);
    }
  }
  return;
}

