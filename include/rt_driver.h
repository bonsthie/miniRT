/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_driver.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:18:38 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 19:37:17 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file rt_driver.h
 * @brief A driver to give the MacroLibX more options than put pixel.
 */

#ifndef RT_DRIVER_H
# define RT_DRIVER_H

# ifndef RT_WIN_NAME
#  define RT_WIN_NAME "miniRT"
# endif

# ifndef RT_WIDTH
#  define RT_WIDTH 1920
# endif

# ifndef RT_HEIGHT
#  define RT_HEIGHT 1080
# endif

# ifndef RT_UI_TOP_BAR
#  define RT_UI_TOP_BAR 40
# endif

# ifndef RT_UI_SIDE_BAR
#  define RT_UI_SIDE_BAR 300
# endif

# ifndef RT_BACKGROUND_COLOR
#  define RT_BACKGROUND_COLOR 0xFF3F3F3F
# endif

# ifndef RT_UI_TOP_BAR_COLOR
#  define RT_UI_TOP_BAR_COLOR 0xFF181818
# endif

# ifndef RT_UI_SIDE_BAR_COLOR
#  define RT_UI_SIDE_BAR_COLOR 0xFF303030
# endif

typedef struct s_scene t_scene;
typedef struct s_screen t_screen;

// Aligned vector types for optimal hardware utilization by use of AVX.
typedef float	__attribute__((aligned(16), vector_size(16))) t_v4f;

/**
 * @struct s_vec3
 * @brief Structure to hold a 3D vector with alignment
 */
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
	float	w;
} __attribute__((aligned(16))) t_vec3;

/**
 * @union vec
 * @brief Union to hold either a 4D vector of floats or a 3D vector
 */
union vec
{
	t_v4f		v4f;
	t_vec3		vec3;
};

typedef void * t_image;

/**
 * @struct s_img
 * @brief Structure to hold image data, including z-buffer, color data, and object IDs
 */
typedef struct	s_img t_img;

/**
 * @struct s_rt_render_info
 * @brief Structure to hold additional rendering information for objects
 */
typedef struct s_rt_render_info
{
	t_vec3	vector;
	t_vec3	normal;
} t_rt_render_info;

/**
 * @brief Initialize ray tracing structure
 *
 * @return (t_screen*) Pointer to the initialized screen structure
 */
t_screen	*rt_init(void);

/**
 * @brief Destroy ray tracing structure
 *
 * @param screen Pointer to the screen structure to be destroyed
 */
void rt_destroy(t_screen *screen);

/**
 * @brief Print the UI screen
 *
 * @param screen Pointer to the screen structure
 */
void rt_print_ui_screen(t_screen *screen);

/**
 * @brief Main loop function for ray tracing
 *
 * @param scene		Scene to be rendered
 * @param rt		Ray tracing structure
 * @param loop		Function to be executed in each loop iteration
 *
 * @return (int)	Status of the loop execution
 */
int rt_loop(t_scene *scene, t_screen *screen, int loop(t_scene *scene, t_img *img, t_screen *screen));

/**
 * DISPLAY ACTION
 */

/**
 * @brief Rasterize and display a triangle on the image
 *
 * @param info		Array of 3 rendering information structs for the triangle vertices
 * @param img		Image structure where the triangle will be displayed
 * @param color		Color to use for the triangle
 */
void	display_triangle_rast(t_rt_render_info info[3], t_img *img, unsigned int color);

/**
 * @brief Rasterize and display a quadrilateral on the image
 *
 * @param info		Array of 4 rendering information structs for the quadrilateral vertices
 * @param img		Image structure where the quadrilateral will be displayed
 * @param color		Color to use for the quadrilateral
 */
void	display_quad_rast(t_rt_render_info info[4], t_img *img, unsigned int color);

/**
 * @brief Print a triangle mesh on the image
 *
 * @param info		Array of 3 rendering information structs for the triangle vertices
 * @param img		Image structure where the triangle will be displayed
 * @param color		Color to use for the triangle
 */
void	display_triangle_mesh(t_rt_render_info info[3], t_img *img, unsigned int color);

/**
 * @brief Print a quadrilateral mesh on the image
 *
 * @param info		Array of 4 rendering information structs for the quadrilateral vertices
 * @param img		Image structure where the quadrilateral will be displayed
 * @param color		Color to use for the quadrilateral
 */
void	display_quad_mesh(t_rt_render_info info[4], t_img *img, unsigned int color);

/**
 * @brief Print a line on the image
 *
 * @param info		Array of 2 rendering information structs for the line endpoints
 * @param img		Image structure where the line will be displayed
 * @param color		Color to use for the line
 */
void	display_line(t_rt_render_info info[2], t_img *img, unsigned int color);

/**
 * @brief Print the image on the screen
 *
 * @param img	Image structure to be printed
 * @param screen Screen structure where the image will be printed
 * @param x		X coordinate on the screen
 * @param y		Y coordinate on the screen
 */
void rt_print_img_screen(t_img *img, t_screen *screen, unsigned int x, unsigned int y);


/**
 * BUTTON ACTION
 */

void rt_add_text_button_top(t_screen *screen, char *text, void *data, void f(void *));
/* void rt_add_icon_png_top(t_screen *screen, void *icon, char *id); */
/* void rt_add_text_button_side(t_screen *screen, char *text, char *id); */
/* void rt_add_icon_png_side(t_screen *screen, void *icon, char *id); */
/* void rt_add_separator_side(t_screen *screen, char *text, char *id); */
/*  */
/* void rt_add_after_text_button_top(t_screen *screen, char *text, char *id, char *after_id); */
/* void rt_add_after_icon_png_top(t_screen *screen, void *icon, char *id, char *after_id); */
/* void rt_add_after_text_button_side(t_screen *screen, char *text, char *id, char *after_id); */
/* void rt_add_after_icon_png_side(t_screen *screen, void *icon, char *id, char *after_id); */
/* void rt_add_after_text_button_side(t_screen *screen, char *text, char *id, char *after_id); */
/* void rt_add_after_separator_button_top(t_screen *screen, char *id, char *after_id); */

void rt_print_button(t_screen *screen);
/* void rt_remove_button(t_screen *screen, char *id); */

#endif /* RT_DRIVER_H */
