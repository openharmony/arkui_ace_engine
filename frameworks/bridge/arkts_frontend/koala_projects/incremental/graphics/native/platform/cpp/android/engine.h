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

#include <android_native_app_glue.h>
#include <cpu-features.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cerrno>
#include <unistd.h>
#include <dlfcn.h>
#include <deque>
#include <memory>
#include <string>
#include <vector>

#include <GLES/gl.h>
#include <EGL/egl.h>

#include <uv.h>
#include <node.h>

#include "skoala-interop.h"
#include "node-interop.h"
#include "jni-bridge.h"

struct SavedState {
    int index;
};

struct InputTextEventState {
    int type;
    std::string characters;
    int cursorPosition;
    InputTextEventState(int type, int cursorPosition, std::string characters) {
        this->type = type;
        this->cursorPosition = cursorPosition;
        this->characters = characters;
    }
};

struct InputKeyEventState {
    int key;
    int modifiers;
    int action;
    InputKeyEventState(int key, int modifiers, int action) {
        this->key = key;
        this->modifiers = modifiers;
        this->action = action;
    }
};

struct PermissionGrantedEventState {
    int requestCode;
    std::vector<std::string> permissions;
    std::vector<int> grantResults;
    PermissionGrantedEventState(
        int requestCode,
        std::vector<std::string>& permissions,
        std::vector<int>& grantResults) {
        this->requestCode = requestCode;
        this->permissions = permissions;
        this->grantResults = grantResults;
    }
};

class Engine {
    enum Kind {
        INIT,
        DEINIT,
        RESIZE,
        REDRAW,
        FOCUS,
        UNFOCUS,
        PAUSE,
        RESUME,
        TAP,
        MOVE,
        KEY
    };
    struct Event {
        Kind kind;
        int count;
        int args1[10];
        int args2[10];
        int arg3;
        int target;
        Event(Kind kind, int arg1, int arg2, int arg3) : kind(kind), count(1), arg3(arg3), target(0) {
            args1[0] = arg1;
            args2[0] = arg2;
        }
        Event(Kind kind, int arg1, int arg2) : kind(kind), count(1), arg3(0), target(0) {
            args1[0] = arg1;
            args2[0] = arg2;
        }
        Event(Kind kind, int count) : kind(kind), count(count), arg3(0), target(0) {
            args1[0] = 0;
            args2[0] = 0;
        }
        Event(Kind kind) : Event(kind, 1) {}
    };
    std::deque<std::unique_ptr<Event>> _pendingEvents;

    typedef void (*engine_callback_t)(Engine*, void* ctx);
    android_app *app;

    // Node runtime state.
    std::unique_ptr<NodeRuntime> nodeRuntime;
    std::unique_ptr<NodeScopedState> nodeScopedState;

    // Graphics state.
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    float density;

    int canDraw;

    AndroidCpuFamily androidCpuFamily;

    // Saved state.
    SavedState savedState;

    int initDisplay();
    void deinitDisplay();
    void resizeDisplay();

    std::shared_ptr<JNIBridge> jniBridge;
    bool checkJniBridge() {
        if (!jniBridge) {
            jniBridge = std::make_shared<JNIBridge>(this->app->activity->vm);
            if (!jniBridge->init()) {
                jniBridge.reset();
                return false;
            }
        }
        return true;
    }

    // We may need  to scale to display coordinates on some platforms.
    void maybeScale(int* xpos, int* ypos) {
        float density = getContentScale();
        *xpos = (int)(*xpos / density);
        *ypos = (int)(*ypos / density);
    }

    void maybeScaleVector(Event* pointerEvent) {
        float density = getContentScale();
        for (int i = 0; i < pointerEvent->count; i++) {
            pointerEvent->args1[i] = (int)(pointerEvent->args1[i] / density);
            pointerEvent->args2[i] = (int)(pointerEvent->args2[i] / density);
        }
    }

    int getPointersCount(const AInputEvent* event) {
        return AMotionEvent_getPointerCount(event);
    }

    int getCurrentAction(const AInputEvent* event) {
        return AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
    }

    int getCurrentPointerIndex(const AInputEvent* event) {
        int pointerMask = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK;
        return pointerMask >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
    }

    jclass vibrationEffectClass;

    jobject vibratorInstance;

    jmethodID vibrateWithDurationMethod;
    jmethodID vibrateWithEffectMethod;
    jmethodID createPredefinedEffectMethod;

    static RedrawerPeer* peer_factory(void* ctx, v8::Local<v8::Object> redrawer);

    std::mutex locker;
    std::deque<std::pair<engine_callback_t, void*>> cb_queue;
    void processQueue();

    int physicalWidth;
    int physicalHeight;

 public:
    Engine(android_app *app);
    RedrawerPeer* peer;

    int prepareNode(std::vector<std::string> &errors, const std::string& startScript);

    bool initNode();
    void runNode();
    void deinitNode();

    void drawFrame();

    void deinit() {
        deinitNode();
        deinitDisplay();
    }

    int handleInput(AInputEvent* event);
    void handleCommand(int command);

    bool makeCurrent(bool attach);
    void swapBuffers();
    bool checkEvents();

    float getContentScale();
    KNativePointer getFrame(KNativePointer peerPtr, int width, int height);
    int32_t getFrameWidth();
    int32_t getFrameHeight();
    int32_t getPhysicalWidth();
    int32_t getPhysicalHeight();
    void requestHaptic(int32_t p1, int32_t p2);
    int32_t getOrientation();
    void softKeyboard(bool show);
    void commitInput();
    SkString* getClipboard();
    void setClipboard(const SkString&);
    int getUnicodeChar(AInputEvent *event);
    void globalPointer(int32_t &x, int32_t &y);

    jstring androidPermissionName(const char* perm_name);
    bool androidHasPermission(const char* perm_name);
    bool androidExistPermission(const char* perm_name);
    void askPermissions(std::vector<std::string> &perms);

    void callOnUIThread(engine_callback_t cb, void* state);
};
