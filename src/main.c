/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
 *  GThumb
 *
 *  Copyright (C) 2010 Free Software Foundation, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// #include <config.h>
#include <gtk/gtk.h>
#include <gthumb/gthumb.h>
#include <glib.h>
#include <stdio.h>

extern unsigned char* load_exr(void* buffer, int size, const char *filename, int *width, int *height);

GthImage *
_cairo_image_surface_create_from_exr(GInputStream *istream,
                                     GthFileData *file_data,
                                     int requested_size,
                                     int *original_width,
                                     int *original_height,
                                     gboolean *loaded_original,
                                     gpointer user_data,
                                     GCancellable *cancellable,
                                     GError **error) {

    GthImage *image = NULL;
    void *in_buffer = NULL;
    gsize in_buffer_size = 0;

    const char* filename = g_file_info_get_attribute_string(file_data->info,
                                                            G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME);

    if (!_g_input_stream_read_all(istream,
                                  &in_buffer,
                                  &in_buffer_size,
                                  cancellable,
                                  error)) {
	*original_height = 0;
	*original_width = 0;
        return image;
    }

    int width, height;

    unsigned char *pixels = load_exr(in_buffer, in_buffer_size, filename, &width, &height);

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, width, height);
    unsigned char* surface_px = cairo_image_surface_get_data(surface);
    int stride = cairo_image_surface_get_stride(surface);

    for (int y = 0; y < height; y++) {
        guint32* scanline = (guint32*)(surface_px + y * stride);
        for (int x = 0; x < width; x++) {
            scanline[x] = CAIRO_RGBA_TO_UINT32(pixels[3 * (y * width + x) + 0],
                                               pixels[3 * (y * width + x) + 1],
                                               pixels[3 * (y * width + x) + 2],
                                               0xff);
        }
    }

    cairo_surface_mark_dirty (surface);
    image = gth_image_new_for_surface(surface);

    *original_width = width;
    *original_height = height;
    free(pixels);

    return image;
}

G_MODULE_EXPORT void
gthumb_extension_activate(void)
{
    gth_main_register_image_loader_func(_cairo_image_surface_create_from_exr,
                                        GTH_IMAGE_FORMAT_CAIRO_SURFACE,
                                        "image/x-exr",
                                        NULL);
}

G_MODULE_EXPORT void
gthumb_extension_deactivate(void)
{
}

G_MODULE_EXPORT gboolean
gthumb_extension_is_configurable(void)
{
    return FALSE;
}

G_MODULE_EXPORT void
gthumb_extension_configure(GtkWindow *parent)
{
}
