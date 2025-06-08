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

#include "engine.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <GLES3/gl3.h>

#include "napi.h"
#include "oh_sk_log.h"
#include "xcomponent.h"

void Engine::initEGLContext(void* window, int w, int h) {
    if (!updateSize(w, h) || w == 0 || h == 0) return;
    OH_SK_LOG_INFO_A("Engine::initEGLContext: window = %p, w = %d, h = %d", window, w, h);
    this->width = w;
    this->height = h;
    this->eglWindow = reinterpret_cast<EGLNativeWindowType>(window);

    EGLint majorVersion = 0;
    EGLint minorVersion = 0;
    this->eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (this->eglDisplay == EGL_NO_DISPLAY) {
        OH_SK_LOG_ERROR("Engine::initEGLContext: unable to get EGL display");
        return;
    }
    if (!eglInitialize(this->eglDisplay, &majorVersion, &minorVersion)) {
        OH_SK_LOG_ERROR("Engine::initEGLContext: unable to get initialize EGL display");
        return;
    }
    OH_SK_LOG_INFO_A("EGL version %d.%d", majorVersion, minorVersion);

    EGLint attribList[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_CONFORMANT, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    const EGLint maxConfigs = 1;
    EGLint numConfigs;
    if (!eglChooseConfig(this->eglDisplay, attribList, &this->eglConfig, maxConfigs, &numConfigs)) {
        OH_SK_LOG_ERROR("Engine::initEGLContext: unable to choose configs");
        return;
    }

    EGLint verList[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    this->eglContext = eglCreateContext(this->eglDisplay, this->eglConfig, EGL_NO_CONTEXT, verList);

    EGLint winAttrs[] = {
        EGL_GL_COLORSPACE_KHR, EGL_GL_COLORSPACE_SRGB_KHR,
        EGL_NONE
    };
    if (this->eglWindow) {
        this->eglSurface = eglCreateWindowSurface(this->eglDisplay, this->eglConfig, this->eglWindow, winAttrs);
        if (this->eglSurface == nullptr) {
            OH_SK_LOG_ERROR("Engine::initEGLContext: unable to create surface");
            return;
        }
    }

    if (!eglMakeCurrent(this->eglDisplay, this->eglSurface, this->eglSurface, this->eglContext)) {
        OH_SK_LOG_ERROR_A("Engine::initEGLContext: error = %d", eglGetError());
        auto opengl_info = { GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS };
        for (auto name : opengl_info) {
            auto info = glGetString(name);
            OH_SK_LOG_INFO_A("OpenGL Info: %s", info);
        }
    }
    // TS side must see logical size.
    _pendingEvents.emplace_back(RESIZE, getFrameWidth(), getFrameHeight());
}

void Engine::resizeSurface(int w, int h) {
    if (!updateSize(w, h) || w == 0 || h == 0) return;
    this->width = w;
    this->height = h;
    _pendingEvents.emplace_back(RESIZE, getFrameWidth(), getFrameHeight());
}

bool Engine::makeCurrent(bool attach) const {
    if (attach) {
        if (eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext) == EGL_FALSE) {
            return false;
        }
    } else {
        eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }
    return true;
}

void Engine::swapBuffers() const {
    if (eglDisplay && eglSurface != EGL_NO_SURFACE) {
        eglSwapBuffers(eglDisplay, eglSurface);
    }
}

void Engine::globalPointer(int32_t &x, int32_t &y) {
    x = 0;
    y = 0;
}

template <class T>
static auto CastPeer(RedrawerPeerBase *peer);

template <Engine::RuntimeKind kind>
static RedrawerPeerBase* CreatePeer(void *info, void *platformApi, void *redrawer);

#ifdef KOALA_USE_HZ_VM
template <>
auto CastPeer<const Napi::CallbackInfo&>(RedrawerPeerBase *peer) {
    return reinterpret_cast<RedrawerPeer *>(peer);
}

static bool check_events(void* enginePtr, void* context) {
    auto engine = (Engine *)enginePtr;
    return engine->checkEvents<const Napi::CallbackInfo &>(*reinterpret_cast<const Napi::CallbackInfo*>(context));
}

template <>
RedrawerPeerBase* CreatePeer<Engine::RuntimeKind::JS>(void *info, void *platformApi, void *redrawer) {
    auto *peer = new RedrawerPeer(*reinterpret_cast<const Napi::CallbackInfo *>(info), reinterpret_cast<napi_value>(platformApi),
        reinterpret_cast<napi_value>(redrawer));
    peer->checkEvents = ::check_events;
    peer->getNapiEnv = nullptr;
    return peer;
}

#endif  // KOALA_USE_HZ_VM

#ifdef KOALA_USE_ARK_VM_WITH_ETS_DEPRECATED
template <>
auto CastPeer<EtsEnv *>(RedrawerPeerBase *peer) {
    return reinterpret_cast<EtsRedrawerPeer *>(peer);
}

static bool check_events_ets(void* enginePtr, void* context) {
    Engine* engine = (Engine *)enginePtr;
    return engine->checkEvents(reinterpret_cast<EtsEnv*>(context));
}

static void* get_napi_env(void* enginePtr) {
    Engine* engine = (Engine*)enginePtr;
    return engine->napiEnv;
}

template <>
RedrawerPeerBase* CreatePeer<Engine::RuntimeKind::ETS>(void *info, void *platformApi, void *redrawer) {
    auto *peer = new EtsRedrawerPeer(reinterpret_cast<EtsEnv *>(info), reinterpret_cast<ets_object>(platformApi),
        reinterpret_cast<ets_object>(redrawer));
    peer->checkEvents = ::check_events_ets;
    peer->getNapiEnv = ::get_napi_env;
    return peer;
}

#endif  // KOALA_USE_ARK_VM_WITH_ETS_DEPRECATED

template <class T>
bool Engine::checkEvents(T info) {
    while (!_pendingEvents.empty()) {
        Event next = _pendingEvents.front();
        _pendingEvents.pop_front();
        switch (next.kind) {
            case TAP:
            case RELEASE:
                CastPeer<T>(peer)->callOnTapEnv(info, next.count, next.args1, next.args2, next.kind == TAP ? 1 : 0, 0);
                break;
            case MOVE:
                CastPeer<T>(peer)->callOnMoveEnv(info, next.count, next.args1, next.args2);
                pointer[0] = next.args1[0];
                pointer[1] = next.args2[0];
                break;
            case RESIZE:
                CastPeer<T>(peer)->callOnResizeEnv(info, next.args1[0], next.args2[0]);
                break;
        }
    }
    return true;
}

void Engine::onTouchEvent(OH_NativeXComponent_TouchEvent* event) {
    Kind kind = TAP;
    int xs[10];
    int ys[10];
    float contentScale = getContentScale();

    if (event->numPoints == 1) {
        xs[0] = (int)(event->x / contentScale);
        ys[0] = (int)(event->y / contentScale);
    } else {
        for (int i = 0; i < event->numPoints; i++) {
            xs[i] = (int)(event->touchPoints[i].x / contentScale);
            ys[i] = (int)(event->touchPoints[i].y / contentScale);
        }
    }

    switch (event->type) {
        case OH_NATIVEXCOMPONENT_DOWN: kind = TAP; break;
        case OH_NATIVEXCOMPONENT_UP: kind = RELEASE; break;
        case OH_NATIVEXCOMPONENT_MOVE: kind = MOVE; break;
        default: assert("unknown event type");
    }
    _pendingEvents.emplace_back(kind, event->numPoints, xs, ys);
}

static bool make_current(void* enginePtr, void* context) {
    auto engine = (Engine*)enginePtr;
    return engine->makeCurrent(context != nullptr);
}

static void swap_buffers(void* enginePtr, void* context) {
    auto engine = (Engine *)enginePtr;
    engine->swapBuffers();
}

static float get_content_scale(void* enginePtr, void* window) {
    auto engine = (Engine *)enginePtr;
    return engine->getContentScale();
}

static KNativePointer get_frame(void* enginePtr, void* peerPtr, int width, int height, int flags, int placement, int x, int y) {
    auto engine = reinterpret_cast<Engine*>(enginePtr);
    return engine->getFrame(peerPtr, width, height);
}

static int32_t get_frame_width(void* enginePtr, void* window) {
    auto engine = (Engine *)enginePtr;
    return engine->getFrameWidth();
}

static int32_t get_frame_height(void* enginePtr, void* window) {
    auto engine = (Engine*)enginePtr;
    return engine->getFrameHeight();
}

static int32_t get_physical_width(void* enginePtr, void* window) {
    auto engine = (Engine *)enginePtr;
    return engine->getPhysicalWidth();
}

static int32_t get_physical_height(void* enginePtr, void* window) {
    auto engine = (Engine*)enginePtr;
    return engine->getPhysicalHeight();
}

static void get_global_pointer(void* enginePtr, KInt* pointer) {
    auto engine = (Engine*)enginePtr;
    return engine->globalPointer(pointer[0], pointer[1]);
}

RedrawerPeerBase* Engine::peerFactory(void *info, void* ctx, void *platformApi, void *redrawer, RuntimeKind kind) {
    OH_SK_LOG_ERROR("Engine::peerFactory");

    auto engine = (Engine*)ctx;

    if (engine->peer != nullptr) {
        OH_SK_LOG_FATAL("engine->peer != nullptr");
        return nullptr;
    }

    RedrawerPeerBase* peer = nullptr;
    switch (kind) {
#ifdef KOALA_USE_HZ_VM
    case RuntimeKind::JS:
        peer = CreatePeer<RuntimeKind::JS>(info, platformApi, redrawer);
        break;
#endif  // KOALA_USE_HZ_VM
#ifdef KOALA_USE_ARK_VM_WITH_ETS_DEPRECATED
    case RuntimeKind::ETS:
        peer = CreatePeer<RuntimeKind::ETS>(info, platformApi, redrawer);
        break;
#endif  // KOALA_USE_ARK_VM_WITH_ETS_DEPRECATED
    default:
        OH_SK_LOG_FATAL_A("Engine::peerFactory: Unsupported runtime kind: %d", kind);
        break;
    };

    engine->peer = peer;
    peer->engine = engine;
    peer->makeCurrent = ::make_current;
    peer->swapBuffers = ::swap_buffers;
    peer->getContentScale = ::get_content_scale;
    peer->getFrame = ::get_frame;
    peer->getFrameWidth = ::get_frame_width;
    peer->getFrameHeight = ::get_frame_height;
    peer->getPhysicalWidth = ::get_physical_width;
    peer->getPhysicalHeight = ::get_physical_height;
    peer->getGlobalPointer = ::get_global_pointer;
    peer->requestHaptic = nullptr;
    peer->getOrientation = nullptr;
    peer->softKeyboard = nullptr;
    peer->commitInput = nullptr;
    return peer;
}

KNativePointer impl_getEngine() {
    OH_SK_LOG_INFO("getEngine");
    return &XComponent::engine;
}
KOALA_INTEROP_0(getEngine, KNativePointer)

KNativePointer impl_getPeerFactory() {
    OH_SK_LOG_INFO("getPeerFactory");
    return reinterpret_cast<KNativePointer>(Engine::peerFactory);
}
KOALA_INTEROP_0(getPeerFactory, KNativePointer)

void impl_setContentScale(KFloat scale) {
    OH_SK_LOG_INFO_A("setContentScale: %.2f", scale);
    XComponent::engine.setContentScale(static_cast<float>(scale));
}
KOALA_INTEROP_V1(setContentScale, KFloat)
