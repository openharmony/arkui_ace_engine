/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/common/graphic/environment_gl.h"

#include <EGL/egl.h>
#include "third_party/skia/include/gpu/GrContext.h"
#include "third_party/skia/tools/gpu/GrContextFactory.h"

#include "base/log/ace_trace.h"
#include "base/log/log.h"

namespace OHOS::Ace {

thread_local WeakPtr<EnvironmentGL> EnvironmentGL::glEnvironment_;

RefPtr<EnvironmentGL> EnvironmentGL::GetCurrent()
{
    return glEnvironment_.Upgrade();
}

RefPtr<EnvironmentGL> EnvironmentGL::MakeSharedGLContext()
{
    ACE_SCOPED_TRACE("create egl ");
    EGLContext context = eglGetCurrentContext();
    if (context == EGL_NO_CONTEXT) {
        LOGE("eglGetCurrentContext failed errorCode = [%{public}d]", eglGetError());
        return nullptr;
    }
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay failed errorCode = [%{public}d]", eglGetError());
        return nullptr;
    }
    EGLint attributes[] = {
        // clang-format off
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
        EGL_RED_SIZE,        8,
        EGL_GREEN_SIZE,      8,
        EGL_BLUE_SIZE,       8,
        EGL_ALPHA_SIZE,      8,
        EGL_DEPTH_SIZE,      0,
        EGL_STENCIL_SIZE,    0,
        EGL_NONE,            // termination sentinel
        // clang-format on
    };
    EGLint config_count = 0;
    EGLConfig egl_config = nullptr;
    if (eglChooseConfig(display, attributes, &egl_config, 1, &config_count) != EGL_TRUE) {
        LOGE("Get EGLConfig failed errorCode = [%{public}d]", eglGetError());
        return nullptr;
    }
    EGLint contextAttr[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext shareContext = eglCreateContext(display, egl_config, context, contextAttr);
    if (shareContext == EGL_NO_CONTEXT) {
        LOGE("eglCreateContext failed errorCode = [%{public}d]", eglGetError());
        return nullptr;
    }
    const EGLint attribs[] = { EGL_WIDTH, 1, EGL_HEIGHT, 1, EGL_NONE };
    EGLSurface surface = eglCreatePbufferSurface(display, egl_config, attribs);
    if (surface == EGL_NO_SURFACE) {
        LOGE("eglCreatePbufferSurface failed errorCode = [%{public}d]", eglGetError());
        eglDestroyContext(display, context);
        return nullptr;
    }
    LOGI("create egl success");
    return MakeRefPtr<EnvironmentGL>(display, shareContext, surface);
}

EnvironmentGL::~EnvironmentGL()
{
    if (surface_ != EGL_NO_SURFACE) {
        eglDestroySurface(display_, surface_);
    }

    if (context_ != EGL_NO_CONTEXT) {
        eglDestroyContext(display_, context_);
    }
}

void EnvironmentGL::MakeCurrent()
{
    if (eglMakeCurrent(display_, surface_, surface_, context_) != EGL_TRUE) {
        LOGE("eglMakeCurrent failed");
    }
    glEnvironment_ = WeakClaim(this);
}

void EnvironmentGL::MakeGrContext()
{
    if (!grContext_) {
        grContext_ = GrContext::MakeGL(GrGLMakeNativeInterface());
    }
}

sk_sp<GrContext> EnvironmentGL::GetGrContext() const
{
    return grContext_;
}

} // namespace OHOS::Ace