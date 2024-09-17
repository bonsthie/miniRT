/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_driver.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:18:38 by babonnet          #+#    #+#             */
/*   Updated: 2024/09/17 19:52:57 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file rt_driver.h
 * @brief A driver to give the MacroLibX more options than put pixel.
 */

#ifndef RT_DRIVER_H
# define RT_DRIVER_H

# include <stdint.h>


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
#  define RT_UI_SIDE_BAR 250
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

# ifndef RT_ERROR_WINDOW
#  define RT_ERROR_WINDOW 0
# endif

// Forward declaration
typedef struct s_screen t_screen;

// Aligned vector types for optimal hardware utilization by use of AVX.
typedef float __attribute__((aligned(16), vector_size(16))) t_v4f;

/**
 * @struct s_vec3
 * @brief Structure to hold a 3D vector with alignment
 */
typedef struct s_vec3
{
	float x;
	float y;
	float z;
	float w;
} __attribute__((aligned(16))) t_vec3;

/**
 * @union u_vec
 * @brief Union to hold either a 4D vector of floats or a 3D vector
 */
union u_vec
{
	t_v4f v4f;
	t_vec3 vec3;
};

/**
 * @struct s_int_vec4
 * @brief Structure to hold a 4D vector with alignment
 */
typedef struct s_int_vec4
{
	int x;
	int y;
	int z;
	int w;
} __attribute__((aligned(16))) t_int_vec4;

/**
 * @union u_color
 * @brief Union to hold either an integer color value or its components
 */
union u_color
{
	int value;
	struct s_color_components
	{
		uint8_t blue;
		uint8_t green;
		uint8_t red;
		uint8_t alpha;
	} components;
};

typedef void *t_image;

/**
 * @struct s_img
 * @brief Structure to hold image data, including z-buffer, color data, and object IDs
 */
typedef struct s_img
{
	short zbuffer[RT_HEIGHT][RT_WIDTH];
	unsigned int color[RT_HEIGHT][RT_WIDTH];
	short obj_id[RT_HEIGHT][RT_WIDTH];
} t_img;

/**
 * @struct s_rt_render_info
 * @brief Structure to hold additional rendering information for objects
 */
typedef struct s_rt_render_info
{
	union u_vec vertex[4];
	union u_vec normal[4];
	union u_color color;
	uint8_t count;
} t_rt_render_info;

// Function declarations

/**
 * @brief Initialize ray tracing structure
 *
 * @return (t_screen*) Pointer to the initialized screen structure
 */
t_screen *rt_init(void);

/**
 * @brief Destroy ray tracing structure
 *
 * @param screen Pointer to the screen structure to be destroyed
 */
void rt_destroy(t_screen *screen) __attribute__((nonnull(1)));

/**
 * @brief Print the UI screen
 *
 * @param screen Pointer to the screen structure
 */
void rt_print_ui_screen(t_screen *screen) __attribute__((nonnull(1)));

/**
 * @brief Main loop function for ray tracing
 *
 * @param data   Data to be passed to the loop function
 * @param screen Screen structure used for rendering
 * @param loop   Function to be executed in each loop iteration
 *
 * @return (int) Status of the loop execution
 */
int rt_loop(void *data, t_screen *screen,
            int loop(void *data, t_img *img,
                     t_screen *screen) __attribute__((nonnull(1, 2, 3))));

/**
 * DISPLAY ACTION
 */

/**
 * @brief Rasterize and display a triangle on the image
 *
 * @param info Array of 3 rendering information structs for the triangle vertices
 * @param img  Image structure where the triangle will be displayed
 * @param id   ID for the triangle (used for object identification)
 */
void rt_display_triangle_rast(t_rt_render_info *info, t_img *img, int id) __attribute__((nonnull(1, 2)));

/**
 * @brief Rasterize and display a quadrilateral on the image
 *
 * @param info Array of 4 rendering information structs for the quadrilateral vertices
 * @param img  Image structure where the quadrilateral will be displayed
 * @param id   ID for the quadrilateral (used for object identification)
 */
void rt_display_quad_rast(t_rt_render_info *info, t_img *img, int id) __attribute__((nonnull(1, 2)));

/**
 * @brief Print a triangle mesh on the image
 *
 * @param info  Array of 3 rendering information structs for the triangle vertices
 * @param img   Image structure where the triangle will be displayed
 * @param color Color to use for the triangle
 */
void rt_display_triangle_mesh(t_rt_render_info *info, t_img *img, unsigned int color) __attribute__((nonnull(1, 2)));

/**
 * @brief Print a quadrilateral mesh on the image
 *
 * @param info  Array of 4 rendering information structs for the quadrilateral vertices
 * @param img   Image structure where the quadrilateral will be displayed
 * @param color Color to use for the quadrilateral
 */
void rt_display_quad_mesh(t_rt_render_info *info, t_img *img, unsigned int color) __attribute__((nonnull(1, 2)));

/**
 * @brief Print a line on the image
 *
 * @param info  Array of 2 rendering information structs for the line endpoints
 * @param img   Image structure where the line will be displayed
 * @param color Color to use for the line
 */
void rt_display_line(t_rt_render_info *info, t_img *img, unsigned int color) __attribute__((nonnull(1, 2)));

/**
 * @brief Print the image on the screen
 *
 * @param img    Image structure to be printed
 * @param screen Screen structure where the image will be printed
 * @param x      X coordinate on the screen
 * @param y      Y coordinate on the screen
 */
void rt_print_img_screen(t_img *img, t_screen *screen, unsigned int x, unsigned int y) __attribute__((nonnull(1, 2)));

/**
 *  @@brief Update the UI
 *
 * @param screen Pointer to the screen structure
 */
void rt_update_ui(t_screen *screen);

/**
 * @brief Print the buttons on the screen
 *
 * @param screen Pointer to the screen structure
 */
void rt_print_button(t_screen *screen);

/* Optional function for future implementation */
/* void rt_remove_button(t_screen *screen, char *id); */

/**
 * @brief Display an error message in a window
 *
 * @param error_msg The error message to display
 */
void rt_error_window(const char *error_msg);

#define HOOK_COUNT 6

/**
 * @enum rt_event_type
 * @brief Enumeration for different event types
 */
typedef enum
{
	RT_KEYDOWN = 0,
	RT_KEYUP = 1,
	RT_MOUSEDOWN = 2,
	RT_MOUSEUP = 3,
	RT_MOUSEWHEEL = 4,
	RT_WINDOW_EVENT = 5
} rt_event_type;

/**
 * @brief Set event handler functions
 *
 * @param screen Pointer to the screen structure
 * @param type   Event type
 * @param f      Function pointer array for the event handler
 * @param data   Additional data to be passed to the handler
 */
void rt_on_event(t_screen *screen, rt_event_type type, void **f, void *data);

/**
 * MOUSE FUNCTIONS
 */

/**
 * @brief Get the mouse position
 *
 * @param screen Pointer to the screen structure
 * @param x      Pointer to store the X position
 * @param y      Pointer to store the Y position
 *
 * @return (int) Status of the operation
 */
int rt_mouse_get_pos(t_screen *screen, int *x, int *y);

/**
 * @brief Hide the mouse cursor
 *
 * @return (int) Status of the operation
 */
int rt_mouse_hide(void);

/**
 * @brief Show the mouse cursor
 *
 * @return (int) Status of the operation
 */
int rt_mouse_show(void);

/**
 * @brief Move the mouse cursor to a specific position
 *
 * @param screen Pointer to the screen structure
 * @param x      X position to move the cursor to
 * @param y      Y position to move the cursor to
 *
 * @return (int) Status of the operation
 */
int rt_mouse_move(t_screen *screen, int x, int y);

/**
 * COLOR FUNCTIONS
 */

/**
 * @brief Set the color of the image
 *
 * @param img    Pointer to the image structure
 * @param color  The color to set
 */
void rt_set_image_color(t_img *img, unsigned int color);

/**
 * @brief Get the object ID under the cursor
 *
 * @param screen Pointer to the screen structure
 * @param img    Pointer to the image structure
 *
 * @return (short) ID of the object under the cursor
 */
short rt_id_obj_under_curssor(t_screen *screen, t_img *img);

/**
 * @brief Put a pixel on the image
 *
 * @param img   Pointer to the image structure
 * @param x     X coordinate of the pixel
 * @param y     Y coordinate of the pixel
 * @param z     Z coordinate (depth) of the pixel
 * @param color Color of the pixel
 *
 * @return (int) Status of the operation
 */
int rt_put_pixel_img(t_img *img, int x, int y, int z, int color);

/**
 * @brief Put a pixel on the image with bounds checking
 *
 * @param img   Pointer to the image structure
 * @param x     X coordinate of the pixel
 * @param y     Y coordinate of the pixel
 * @param z     Z coordinate (depth) of the pixel
 * @param color Color of the pixel
 *
 * @return (int) Status of the operation
 */
int rt_put_pixel_img_protected(t_img *img, int x, int y, int z, int color);

/**
 * @brief Get the color under the cursor
 *
 * @param screen Pointer to the screen structure
 * @param img    Pointer to the image structure
 *
 * @return (int) Color under the cursor
 */
int rt_get_color_under_cursor(t_screen *screen, t_img *img);

/**
 * @brief Get the average color under the cursor in a given area
 *
 * @param screen Pointer to the screen structure
 * @param img    Pointer to the image structure
 * @param size   Size of the area to average
 *
 * @return (int) Average color under the cursor
 */
int rt_get_color_under_cursor_avrege(t_screen *screen, t_img *img, int size);

#endif /* RT_DRIVER_H */
