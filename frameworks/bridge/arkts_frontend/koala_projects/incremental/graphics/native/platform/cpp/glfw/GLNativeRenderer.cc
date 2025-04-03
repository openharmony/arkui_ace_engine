/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "GrBackendSurface.h"
#include "common-interop.h"
#include "ganesh/SkSurfaceGanesh.h"
#include "skoala.h"

#include "SkCanvas.h"
#include "SkPicture.h"
#include "GrDirectContext.h"
#include "ganesh/gl/GrGLBackendSurface.h"
#include "SkColorSpace.h"
#include "SkSurface.h"
#include "NativeRenderer.h"

#ifdef SK_BUILD_FOR_WIN
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#define GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_FRAMEBUFFER_EXT                0x8D40
#define GL_COLOR_ATTACHMENT0_EXT          0x8CE0


#ifndef SK_BUILD_FOR_WIN
extern "C" GLAPI void APIENTRY glBindFramebuffer(GLenum target, GLuint framebuffer);
extern "C" GLAPI void APIENTRY glGenFramebuffers(GLsizei n, GLuint *framebuffers);
extern "C" GLAPI void APIENTRY glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers);
extern "C" GLAPI void APIENTRY glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
#endif

typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSEXTPROC) (GLsizei n, GLuint *framebuffers);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFEREXTPROC) (GLenum target, GLuint framebuffer);
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSEXTPROC) (GLsizei n, const GLuint *framebuffers);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREEXTPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);

PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersProc = nullptr;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferProc = nullptr;
PFNGLDELETEFRAMEBUFFERSEXTPROC glDeleteFramebuffersProc = nullptr;
PFNGLFRAMEBUFFERTEXTUREEXTPROC glFramebufferTextureProc = nullptr;

struct GLState {
    GLfloat color[4];
    GLint viewport[4];
    GLint framebuffer;
    GLFWwindow* window;
};

class NativeGLRenderer : public NativeRenderer {
  private:
    GrBackendTexture* backend;
    GrDirectContext* context;
    GLFWwindow* window;

    bool initGLProc() {
        if (glBindFramebufferProc == nullptr)
        {
#ifdef SK_BUILD_FOR_WIN
            glBindFramebufferProc = (PFNGLBINDFRAMEBUFFEREXTPROC)wglGetProcAddress("glBindFramebufferEXT");
            if (glBindFramebufferProc == nullptr)
                return false;
#else
            glBindFramebufferProc = &glBindFramebuffer;
#endif
        }
        if (glGenFramebuffersProc == nullptr)
        {
#ifdef SK_BUILD_FOR_WIN
            glGenFramebuffersProc = (PFNGLGENFRAMEBUFFERSEXTPROC)wglGetProcAddress("glGenFramebuffersEXT");
            if (glGenFramebuffersProc == nullptr) {
                return false;
            }
#else
            glGenFramebuffersProc = &glGenFramebuffers;
#endif

        }
        if (glDeleteFramebuffersProc == nullptr)
        {
#ifdef SK_BUILD_FOR_WIN
            glDeleteFramebuffersProc = (PFNGLDELETEFRAMEBUFFERSEXTPROC)wglGetProcAddress("glDeleteFramebuffers");
            if (glDeleteFramebuffersProc == nullptr)
                return false;
#else
            glDeleteFramebuffersProc = &glDeleteFramebuffers;
#endif
        }
        if (glFramebufferTextureProc == nullptr)
        {
#ifdef SK_BUILD_FOR_WIN
            glFramebufferTextureProc = (PFNGLFRAMEBUFFERTEXTUREEXTPROC)wglGetProcAddress("glFramebufferTextureEXT");
            if (glFramebufferTextureProc == nullptr)
                return false;
#else
        glFramebufferTextureProc = &glFramebufferTexture;
#endif
        }
        return true;
    }

    bool makeTexturedSurface() {
        if (!initGLProc()) return false;
        glGenFramebuffersProc(1, &framebuffer);
        glBindFramebufferProc(GL_FRAMEBUFFER_EXT, framebuffer);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTextureProc(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, texture, 0);
        GrGLTextureInfo glInfo;
        glInfo.fTarget = GL_TEXTURE_2D;
        glInfo.fID = texture;
        glInfo.fFormat = GL_RGBA8;
        backend = new GrBackendTexture;
        *backend = GrBackendTextures::MakeGL(width, height, GrMipmapped::kNo, glInfo);
        auto colorSpace = SkColorSpace::MakeSRGBLinear();
        SkSurfaceProps surfaceProperties;
        drawSurface = SkSurfaces::WrapBackendTexture(
            context,
            *backend,
            GrSurfaceOrigin::kBottomLeft_GrSurfaceOrigin,
            0 /* sampleCnt */,
            SkColorType::kRGBA_8888_SkColorType,
            colorSpace,
            &surfaceProperties
        );
        return true;
    }

    void save(GLState* state) {
        state->window = glfwGetCurrentContext();
        glfwMakeContextCurrent(window);
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &state->framebuffer);
        glGetIntegerv(GL_VIEWPORT, state->viewport);
        glGetFloatv(GL_COLOR_CLEAR_VALUE, state->color);
    }

    void restore(GLState* state) {
        glBindFramebufferProc(GL_FRAMEBUFFER_EXT, state->framebuffer);
        glViewport(state->viewport[0], state->viewport[1], state->viewport[2], state->viewport[3]);
        glClearColor(state->color[0], state->color[1], state->color[2], state->color[3]);
        glfwMakeContextCurrent(state->window);
    }

  public:
    GLuint texture = 0;
    GLuint framebuffer = 0;
    NativeGLRenderer(int width, int height, GrDirectContext* context, GLFWwindow* window, SkoalaNativeRenderer* renderer)
    : NativeRenderer(width, height, renderer) {
        this->context = context;
        this->window = window;
        this->renderer = renderer;

        GLState state;
        save(&state);
        if (makeTexturedSurface()) {
            if (renderer) renderer->onInit(renderer, window, width, height);
        }
        restore(&state);
    }

    ~NativeGLRenderer() override {
        if (framebuffer == 0) return;

        GLState state;
        save(&state);
        glDeleteTextures(1, &texture);
        texture = 0;
        glDeleteFramebuffersProc(1, &framebuffer);
        framebuffer = 0;
        if (backend) {
            delete backend;
            backend = nullptr;
        }
        window = nullptr;
        context = nullptr;
        renderer = nullptr;
        restore(&state);
        drawSurface.reset();
    }

    void draw() override {
        if (renderer) {
            GLState state;
            save(&state);
            glBindFramebufferProc(GL_FRAMEBUFFER_EXT, framebuffer);
            glViewport(0, 0, width, height);
            renderer->onDraw(renderer, width, height);
            restore(&state);
        }
    }
};

KNativePointer impl_skoala_TexturedImage__1nMakeNativeGLRenderer(KInt width, KInt height, KNativePointer contextPtr, KNativePointer windowPtr, KNativePointer nativeRendererPtr) {
    GrDirectContext* context = reinterpret_cast<GrDirectContext*>(contextPtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(windowPtr);
    SkoalaNativeRenderer* nativeRenderer = reinterpret_cast<SkoalaNativeRenderer*>(nativeRendererPtr);
    NativeGLRenderer* renderer = new NativeGLRenderer(width, height, context, window, nativeRenderer);
    nativeRenderer->sendMessage(nativeRenderer, SkoalaNativeRendererIdFBO, renderer->framebuffer, 0, 0, 0, 0, 0);
    return renderer;
}
KOALA_INTEROP_5(skoala_TexturedImage__1nMakeNativeGLRenderer, KNativePointer, KInt, KInt, KNativePointer, KNativePointer, KNativePointer)