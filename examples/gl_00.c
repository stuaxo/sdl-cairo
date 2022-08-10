/*
 *
 */

#include <SDL2/SDL.h>
#include <cairo/cairo.h>

int main ()
{
   int width      = 720;
   int height     = 450;
   int videoFlags = SDL_WINDOW_RESIZABLE;
   int quit = 0;

   const char * text = "https://github.com/rjopek/sdl-cairo";

   if( ( SDL_Init( SDL_INIT_VIDEO ) != 0 ) )
   {
      SDL_Log( "Unable to initialize SDL: %s.\n", SDL_GetError() );
      exit( EXIT_FAILURE );
   }

   SDL_Window * window = SDL_CreateWindow( "SDL .AND. Cairo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, videoFlags );
   if( window == NULL )
   {
      SDL_Log( "Could not create window: %s.\n", SDL_GetError() );
      exit( EXIT_FAILURE );
   }

   SDL_Renderer * renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
   if( renderer == NULL )
   {
      SDL_Log( "Could not create Renderer: %s.\n", SDL_GetError() );
      exit( EXIT_FAILURE );
   }

   SDL_Surface * sdl_surface = SDL_CreateRGBSurface( videoFlags, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0 );
   if( sdl_surface == NULL )
   {
      SDL_Log( "SDL_CreateRGBSurface() failed: %s\n", SDL_GetError() );
      exit( EXIT_FAILURE );
   }

   while( ! quit )
   {
      SDL_FillRect( sdl_surface, NULL, 0 );

      cairo_surface_t * cr_surface = cairo_image_surface_create_for_data( (unsigned char *) sdl_surface->pixels, CAIRO_FORMAT_RGB24, sdl_surface->w, sdl_surface->h, sdl_surface->pitch );
      cairo_t * cr = cairo_create( cr_surface );

      cairo_set_source_rgb( cr, 1.0, 1.0, 1.0 );
      cairo_set_operator( cr, CAIRO_OPERATOR_SOURCE );
      cairo_paint( cr );

      //---
      cairo_select_font_face( cr, "FreeMono", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD );
      cairo_set_font_size( cr, 34 );
      cairo_set_source_rgba( cr, 0.5, 0.5, 0.5, 1.0 );

      cairo_text_extents_t te;
      cairo_text_extents( cr, text, &te );

      double xc = ( width  - te.width ) / 2;
      double yc = ( height + te.height ) / 2;

      cairo_move_to( cr, xc, yc );
      cairo_show_text( cr, text );
      //---

      SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
      SDL_RenderClear( renderer );
      SDL_Texture * texture = SDL_CreateTextureFromSurface( renderer,sdl_surface );
      SDL_RenderCopy( renderer, texture, NULL, NULL ) ;
      SDL_RenderPresent( renderer );
      SDL_DestroyTexture( texture );

      cairo_surface_destroy( cr_surface );
      cairo_destroy( cr );

      SDL_Event event;
      if( SDL_WaitEvent( &event ) )
      {
         do
         {
            switch( event.type )
            {
               case SDL_KEYDOWN:
                  if( event.key.keysym.sym == SDLK_ESCAPE )
                  {
                     quit = 1;
                  }
                  break;

               case SDL_QUIT:
                  quit = 1;
                  break;

               case SDL_WINDOWEVENT:
                  switch( event.window.event )
                  {
                     case SDL_WINDOWEVENT_SIZE_CHANGED:
                        width = event.window.data1;
                        height = event.window.data2;
                        break;
                     case SDL_WINDOWEVENT_CLOSE:
                        event.type = SDL_QUIT;
                        SDL_PushEvent( &event );
                        break;
                  }

               SDL_FreeSurface( sdl_surface );
               sdl_surface = SDL_CreateRGBSurface( videoFlags, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0 );
               break;
            }
         } while( SDL_PollEvent( &event ) );
         printf( "window width=%d\n" "window height=%d\n", width, height );
      }
   }

   SDL_DestroyRenderer( renderer );
   SDL_DestroyWindow( window );
   SDL_Quit();

   return 0;
}
