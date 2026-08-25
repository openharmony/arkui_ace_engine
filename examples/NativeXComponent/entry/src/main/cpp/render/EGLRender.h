/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NATIVEXCOMPONENT_EGLRENDER_H
#define NATIVEXCOMPONENT_EGLRENDER_H

#include "EGLConst.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <GLES3/gl3.h>
#include <string>

class EGLRender {
public:
    bool SetUpEGLContext(void *window);
    void SetEGLWindowSize(int width, int height);
    void DrawStar(bool drawColor);
    void DestroySurface();
    void Clear();
    void Background();

    std::string xcomponentId;
    EGLNativeWindowType eglWindow_;

    EGLDisplay eglDisplay_ = EGL_NO_DISPLAY;
    EGLConfig eglConfig_ = EGL_NO_CONFIG_KHR;
    EGLSurface eglSurface_ = EGL_NO_SURFACE;
    EGLContext eglContext_ = EGL_NO_CONTEXT;
    GLuint program_;
    int width_ = 0;
    int height_ = 0;
    int hasDraw_ = 0;
    int hasChangeColor_ = 0;

private:
    GLint PrepareDraw();
    bool ExecuteDraw(GLint position, const GLfloat *color, const GLfloat shapeVertices[]);
    bool ExecuteDrawStar(GLint position, const GLfloat *color, const GLfloat shapeVertices[], unsigned long vertSize);
};
#endif // NATIVEXCOMPONENT_EGLRENDER_H
