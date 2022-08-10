/*
 *
 */

#include <math.h>

#include <cairo/cairo.h>
#include <cairo/cairo-svg.h>

int main( void )
{
   int width = 512, height = 512;
   double xc, yc;
   cairo_text_extents_t te;
   const char * text = "SDL-Cairo";

   cairo_surface_t * surface = cairo_svg_surface_create( "sdl-cairo.svg", width, height );
   cairo_t * cr = cairo_create( surface );

   cairo_set_source_rgb( cr, 0.2734, 0.7578, 0.6875 );
   cairo_arc( cr, width / 2, height / 2, 256.0, 0, 2 * M_PI );
   cairo_fill( cr );

   cairo_set_source_rgb( cr, 0.1961, 0.1961, 0.1961 );
   cairo_arc( cr, width / 2, height / 2, 256, 0, 2 * M_PI );
   cairo_clip( cr );
   cairo_set_source_rgb( cr, 1, 1, 1 );
   cairo_rectangle( cr, 0, ( height - 220 ) / 2, width, 180 );
   cairo_fill( cr );

   cairo_set_source_rgb( cr, 0.1961, 0.1961, 0.1961 );
   cairo_rectangle( cr, 0, ( height - 280 ) / 2, width, 30 );
   cairo_rectangle( cr, 0, ( height + 140 ) / 2, width, 30 );
   cairo_fill( cr );

   cairo_set_source_rgb( cr, 0.1961, 0.1961, 0.1961 );
   cairo_set_line_width( cr, 60 );
   cairo_arc( cr, width / 2, height / 2, 256, 0, 2 * M_PI );
   cairo_stroke( cr );

   cairo_select_font_face( cr, "FreeMono", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD );
   cairo_set_font_size( cr, 80 );
   cairo_set_source_rgb( cr, 0.1961, 0.1961, 0.1961 );

   cairo_text_extents( cr, text, &te );

   xc = ( width  - te.width ) / 2;
   yc = ( height + te.height / 2 ) / 2;

   cairo_move_to( cr, xc, yc );
   cairo_show_text( cr, text );

   cairo_surface_destroy( surface );
   cairo_destroy( cr );
}
