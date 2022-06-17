#pragma once

#define DIR_EXCEPT( hr ) Window::HrException( __LINE__,__FILE__,(hr) )
#define DIR_LAST_EXCEPT() Window::HrException( __LINE__,__FILE__,GetLastError() )
#define DIR_NOGFX_EXCEPT() Window::NoGfxException( __LINE__,__FILE__ )