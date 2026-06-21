
/* FILE NAME: rndbase.C
 * PURPOSE: 3D math implementation module.
 * PROGRAMMER: MI6
 * DATE: 09.06.2026
 */

#include "rnd.h"
#include <wglew.h>
#include <gl/wglext.h>
#include <gl/glu.h>

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

VOID MI6_RndInit( HWND hWnd )
{
  INT i, i1[10];
  HGLRC MI6_hRndGLRC, hRC;
  PIXELFORMATDESCRIPTOR pfd = {0};
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };

  MI6_hRndWnd = hWnd;
 
  /* Prepare frame compatible device contesxt */
  MI6_hRndDC = GetDC(hWnd);
 
  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(MI6_hRndDC, &pfd);
  
  DescribePixelFormat(MI6_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(MI6_hRndDC, i, &pfd);
 
  /* OpenGL init: rendering context setup */
  MI6_hRndGLRC = wglCreateContext(MI6_hRndDC);
  wglMakeCurrent(MI6_hRndDC, MI6_hRndGLRC);

  if (glewInit() != GLEW_OK)
    exit(0);

  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(MI6_hRndDC, PixelAttribs, NULL, 1, i1, &i);
  hRC = wglCreateContextAttribsARB(MI6_hRndDC, NULL, ContextAttribs);
 
  if (hRC != NULL)
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(MI6_hRndGLRC);
    MI6_hRndGLRC = hRC;
    wglMakeCurrent(MI6_hRndDC, MI6_hRndGLRC);
  }

  glEnable(GL_DEPTH_TEST);
  wglSwapIntervalEXT(0);

  #ifndef NDEBUG
    OutputDebugString(glGetString(GL_VERSION));
    OutputDebugString("\n");
    OutputDebugString(glGetString(GL_VENDOR));
    OutputDebugString("\n");
    OutputDebugString(glGetString(GL_RENDERER));
    OutputDebugString("\n");
  #endif /* NDEBUG */

  /* Render parameters setup */
  glEnable(GL_DEPTH_TEST);
  wglSwapIntervalEXT(0);

  MI6_RndProjSize = 0.1;
  MI6_RndProjDist = MI6_RndProjSize;
  MI6_RndProjFarClip = 5000;
  MI6_RndFrameW = 47;
  MI6_RndFrameH = 47;
  MI6_RndCamSet(VecSet(5, 5, 5), VecSet(0, 0, 0), VecSet(0, 1, 0));

  MI6_RndResInit();
}

VOID MI6_RndClose( VOID )
{
  MI6_RndResClose();

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(MI6_hRndGLRC);
  ReleaseDC(MI6_hRndWnd, MI6_hRndDC);
}
VOID MI6_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);

  /* Setup projection */
  MI6_RndFrameW = W;
  MI6_RndFrameH = H;

  MI6_RndProjSet();
}

VOID MI6_RndCopyFrame( VOID )
{
  SwapBuffers(MI6_hRndDC);
}


VOID MI6_RndStart( VOID )
{
  VEC4 ClearColor = {0.30, 0.47, 0.8, 1};
  FLT DepthClearValue = 1;
 
  MI6_RndShdUpdate();

  /* Clear frame */
  glClearBufferfv(GL_COLOR, 0, &ClearColor.X);
  glClearBufferfv(GL_DEPTH, 0, &DepthClearValue);
}

VOID MI6_RndEnd( VOID )
{
  glFinish();
}

VOID MI6_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = MI6_RndProjSize;
  /* Correct aspect ratio */
  if (MI6_RndFrameW > MI6_RndFrameH)
    rx *= (DBL)MI6_RndFrameW / MI6_RndFrameH;
  else
    ry *= (DBL)MI6_RndFrameH / MI6_RndFrameW;
  MI6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      MI6_RndProjDist, MI6_RndProjFarClip);
  MI6_RndMatrVP = MatrMulMatr(MI6_RndMatrView, MI6_RndMatrProj);
}
  
VOID MI6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  MI6_RndMatrView = MatrView(Loc, At, Up);
  MI6_RndMatrVP = MatrMulMatr(MI6_RndMatrView, MI6_RndMatrProj);
}