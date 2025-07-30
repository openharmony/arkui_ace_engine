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

#pragma once

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

#include <ace/xcomponent/native_interface_xcomponent.h>

#include <deque>
#include <inttypes.h>

#include "skoala-interop.h"
#include "ark-interop.h"
#include "oh_sk_log.h"

#ifdef KOALA_USE_ARK_VM_WITH_ETS_DEPRECATED
#include <napi.h>
#endif  // KOALA_USE_ARK_VM_WITH_ETS_DEPRECATED

class Engine {
    enum Kind {
        TAP,
        RELEASE,
        MOVE,
        RESIZE
    };
    struct Event {
        Kind kind;
        int count;
        int args1[10] = { 0 };
        int args2[10] = { 0 };

        Event(Kind kind, int arg1, int arg2) : kind(kind), count(1) {
            args1[0] = arg1;
            args2[0] = arg2;
        }

        Event(Kind kind, int count, int* args1, int* args2) : kind(kind), count(count) {
            memcpy(this->args1, args1, sizeof(int) * count);
            memcpy(this->args2, args2, sizeof(int) * count);
        }
    };
    std::deque<Event> _pendingEvents;

private:
    int pointer[2] = { 0, 0 };

public:
    enum class RuntimeKind {
        JS = 0,
        ETS = 1,
    };

    Engine() : peer(nullptr), width(0), height(0), scale(1.0),
    eglWindow(0), eglDisplay(EGL_NO_DISPLAY), eglConfig(EGL_NO_CONFIG_KHR),
    eglSurface(EGL_NO_SURFACE), eglContext(EGL_NO_CONTEXT) {}

    void initEGLContext(void* window, int w, int h);
    void resizeSurface(int w, int h);

    bool updateSize(int w, int h, bool zeroSizeAccepted = false) {
        if (!zeroSizeAccepted && (w <= 0 || h <= 0)) return false;
        if (width == w && height == h) return false;
        width = w;
        height = h;
        return true;
    }

    void resetEGL() {
        updateSize(0, 0);
        eglWindow = EGL_CAST(EGLNativeWindowType, 0);
        eglDisplay = EGL_NO_DISPLAY;
        eglConfig = EGL_NO_CONFIG_KHR;
        eglSurface = EGL_NO_SURFACE;
        eglContext = EGL_NO_CONTEXT;
    }

    bool makeCurrent(bool attach) const;
    void swapBuffers() const;

    template <class T>
    bool checkEvents(T info);

    RedrawerPeerBase* peer;

    int width;
    int height;
    float scale;

#ifdef KOALA_USE_ARK_VM_WITH_ETS_DEPRECATED
    napi_env napiEnv = nullptr;
#endif  // KOALA_USE_ARK_VM_WITH_ETS_DEPRECATED

    float getContentScale() const {
        return scale;
    }

    void setContentScale(float contentScale) {
        bool needResize = this->scale != contentScale;
        this->scale = contentScale;
        if (needResize) {
            _pendingEvents.emplace_back(RESIZE, getFrameWidth(), getFrameHeight());
        }
    }

    static KNativePointer getFrame(KNativePointer peerPtr, int width, int height) {
        return peerPtr;
    }

    int32_t getFrameWidth() const {
        return ceil((float)width / getContentScale());
    }

    int32_t getFrameHeight() const {
        return ceil((float)height / getContentScale());
    }

    int32_t getPhysicalWidth() const {
        return width;
    }

    int32_t getPhysicalHeight() const {
        return height;
    }

    void globalPointer(int32_t &x, int32_t &y);

    // Callbacks from XComponent.
    void onTouchEvent(OH_NativeXComponent_TouchEvent* event);

    EGLNativeWindowType eglWindow;
    EGLDisplay eglDisplay = EGL_NO_DISPLAY;
    EGLConfig eglConfig = EGL_NO_CONFIG_KHR;
    EGLSurface eglSurface = EGL_NO_SURFACE;
    EGLContext eglContext = EGL_NO_CONTEXT;

    static RedrawerPeerBase* peerFactory(void *info, void* ctx, void *platformApi, void *redrawer, RuntimeKind kind);
};
