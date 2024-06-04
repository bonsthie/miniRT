/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_driver.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:18:38 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/04 17:46:36 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_DATA_H
# define MLX_DATA_H

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

struct s_scene;
typedef struct s_scene t_scene;

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

/**
 * @struct s_img
 * @brief Structure to hold image data, including z-buffer, color data, and object IDs
 */
typedef struct				s_img
{
	int				zbuffer[HEIGHT][WIDTH];    /**< Z-buffer array for depth information */
	unsigned int	color[HEIGHT][WIDTH];      /**< Color buffer array */
	int				obj_id[HEIGHT][WIDTH];     /**< Object ID buffer array */
} t_img;

/**
 * @struct s_rt_render_info
 * @brief Structure to hold additional rendering information for objects
 */
typedef struct s_rt_render_info
{
	t_vec3	vector; /**< Vector information for rendering */
	t_vec3	normal; /**< Normal vector information for rendering */
} t_rt_render_info;

/**
 * @brief Main loop function for ray tracing
 *
 * @param scene		Scene to be rendered
 * @param loop		Function to be executed in each loop iteration
 *
 * @return (int)	Status of the loop execution
 */
int rt_loop(t_scene *scene, int loop(t_scene *scene, t_img *img));

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

#endif /* MLX_DATA_H */
