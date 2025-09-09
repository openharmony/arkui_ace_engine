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

#include <cmath>

#include "skoala.h"
#include "skoala-interop.h"

#include "NativeRenderer.h"

#ifdef SK_BUILD_FOR_WIN
#include <windows.h>
void* openLibrary(const char* name) {
    return LoadLibrary(name);
}
void closeLibrary(void* library) {
    FreeLibrary(reinterpret_cast<HMODULE>(library));
}
void* findFunction(void* library, const char* name) {
    return GetProcAddress(reinterpret_cast<HMODULE>(library), name);
}
#else
#include <dlfcn.h>
void* openLibrary(const char* name) {
    return dlopen(name, RTLD_LAZY);
}
void closeLibrary(void* library) {
    dlclose(library);
}
void* findFunction(void* library, const char* name) {
    return dlsym(library, name);
}
#endif

#ifndef SKOALA_USE_METAL
#include <GL/gl.h>
#endif

static double timestamp() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return static_cast<int64_t>(ts.tv_sec + (double) ts.tv_nsec / 1e9);
}

enum RenderMode {
    UnknownMode,
    SoftMode,
    OpenGLMode
};

struct DefaultNativeRendererState {
    uint32_t* softPixels;
    int phase;
    double lastTs;
    RenderMode mode;
    int width;
    int height;
    DefaultNativeRendererState(int phase, int width, int height):
        softPixels(nullptr), phase(phase), lastTs(0), mode(UnknownMode), width(width), height(height) {}
};

static void defaultRendererOnInit(SkoalaNativeRenderer* renderer, void* window, int width, int height) {
    static int count = 0;
    renderer->context = new DefaultNativeRendererState(count++, width, height);
}

static void defaultRendererOnDeinit(SkoalaNativeRenderer* renderer) {
    delete reinterpret_cast<DefaultNativeRendererState*>(renderer->context);
    delete renderer;
}

static void defaultRendererOnDraw(SkoalaNativeRenderer* renderer, int width, int height) {
    auto* state = reinterpret_cast<DefaultNativeRendererState*>(renderer->context);
#ifndef SKOALA_USE_METAL
    if (state->mode == OpenGLMode) {
        const auto pi = 3.14159265358;
        float time = fmod(timestamp(), 2 * pi) + state->phase * pi / 2.0;
        float r = sin(time) * 0.5 + 0.5;
        float g = sin(time) * 0.5 + 0.5;
        float b = cos(time) * 0.5 + 0.5;
        float a = 1.0;
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
#endif
     if (state->mode == SoftMode && state->softPixels && state->height > 2) {
        int from = ((unsigned int)(timestamp() * 1000) % (state->height - 2)) * state->width;
        for (int i = from; i < from + state->width * 2; i++) {
            state->softPixels[i] = 0xff0000ff;
        }
     }
}

static int defaultRendererCheckRedraw(SkoalaNativeRenderer* renderer) {
    double time = timestamp();
    auto* state = reinterpret_cast<DefaultNativeRendererState*>(renderer->context);
    if (state && ((time - state->lastTs) > (0.5 - (state->phase % 4) * 0.1))) {
        state->lastTs = time;
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
T* asPointer(unsigned int p1, unsigned int p2) {
    return reinterpret_cast<T*>(
        static_cast<uintptr_t>(p1) | (static_cast<uintptr_t>(p2) << 32));
}


static int defaultRendererSendMessage(SkoalaNativeRenderer* renderer, int id, int data1, int data2, int data3, int data4, int data5, int data6) {
    auto* state = reinterpret_cast<DefaultNativeRendererState*>(renderer->context);
    if (id == SkoalaNativeRendererIdFBO) {
        state->mode = OpenGLMode;
    }
    if (id == SkoalaNativeRendererIdPixels) {
        state->mode = SoftMode;
        state->softPixels = asPointer<uint32_t>(data1, data2);
        memset_s(state->softPixels, state->width * state->height * 4, 0, state->width * state->height * 4);
    }
    return 0;
}

KNativePointer impl_skoala_SkoalaNativeRenderer__1nDefaultNativeRenderer() {
    SkoalaNativeRenderer* result = new SkoalaNativeRenderer();
    result->context = nullptr;
    result->onInit = defaultRendererOnInit;
    result->onDeinit = defaultRendererOnDeinit;
    result->onDraw = defaultRendererOnDraw;
    result->checkRedraw = defaultRendererCheckRedraw;
    result->sendMessage = defaultRendererSendMessage;

    return result;
}
KOALA_INTEROP_0(skoala_SkoalaNativeRenderer__1nDefaultNativeRenderer, KNativePointer)

struct LibraryRendererState {
    void* module;
    void (*onDeinit)(SkoalaNativeRenderer*);
    LibraryRendererState(void* module, void (*onDeinit)(SkoalaNativeRenderer*))
        : module(module), onDeinit(onDeinit) {}
};

static void libraryRendererOnDeinit(SkoalaNativeRenderer* renderer) {
    LibraryRendererState* state = reinterpret_cast<LibraryRendererState*>(renderer->context);
    auto module = state->module;
    delete state;
    state->onDeinit(renderer);
    closeLibrary(module);
}

#ifdef KOALA_NAPI
class LoadJob : public Napi::AsyncWorker {
    public:
        LoadJob(Napi::Function& callback, const SkString& path)
            : AsyncWorker(callback), path(path), result(nullptr) {}

        ~LoadJob() {}

    void Execute() override {
        void* library = openLibrary(path.c_str());
        if (!library) return;;

        auto* onInit = reinterpret_cast<void (*)(SkoalaNativeRenderer*, void*, int, int)>(
            findFunction(library, "SkoalaRenderer_onInit"));
        auto* onDeinit = reinterpret_cast<void (*)(SkoalaNativeRenderer*)>(
            findFunction(library, "SkoalaRenderer_onDeinit"));
        auto* onDraw = reinterpret_cast<void (*)(SkoalaNativeRenderer*, int, int)>(
            findFunction(library, "SkoalaRenderer_onDraw"));
        auto* checkRedraw = reinterpret_cast<int (*)(SkoalaNativeRenderer*)>(
            findFunction(library, "SkoalaRenderer_checkRedraw"));
        auto* sendMessage = reinterpret_cast<int (*)(SkoalaNativeRenderer*, int, int, int, int, int, int, int)>(
            findFunction(library, "SkoalaRenderer_sendMessage"));
        auto* onLoad = reinterpret_cast<void (*)(SkoalaNativeRenderer*)>(
            findFunction(library, "SkoalaRenderer_onLoad"));

        if (!onInit || !onDeinit || !onDraw || !checkRedraw || !sendMessage)
            return;

        this->result = new SkoalaNativeRenderer();
        result->context = new LibraryRendererState(library, onDeinit);
        result->onInit = onInit;
        result->onDeinit = libraryRendererOnDeinit;
        result->onDraw = onDraw;
        result->checkRedraw = checkRedraw;
        result->sendMessage = sendMessage;

        if (onLoad) onLoad(result);
    }

    void OnOK() override {
        Napi::HandleScope scope(Env());
        Callback().Call({makePointer(Env(), result)});
    }
private:
    SkString path;
    SkoalaNativeRenderer* result;
};

Napi::Value Node_skoala_SkoalaNativeRenderer__1nLibraryNativeRenderer(const Napi::CallbackInfo& info) {
    if (2 != info.Length()) {
        Napi::Error::New(info.Env(), "Wrong arg count")
            .ThrowAsJavaScriptException();
        return makeVoid(info);
    }
    auto pathPtr = getArgument<KStringPtr>(info, 0);
    Napi::Function completer = info[1].As<Napi::Function>();
    SkString path(pathPtr.c_str());
    LoadJob* job = new LoadJob(completer, path);
    job->Queue();
    return makeVoid(info);
}
MAKE_INTEROP_NODE_EXPORT(skoala_SkoalaNativeRenderer__1nLibraryNativeRenderer)

struct NativeModuleState {
    void* module;
    void (*onDeinit)(SkoalaNativeModule*);
    NativeModuleState(void* module, void (*onDeinit)(SkoalaNativeModule*))
        : module(module), onDeinit(onDeinit) {}
};

class LoadModuleJob : public Napi::AsyncWorker {
    public:
        LoadModuleJob(Napi::Function& callback, const SkString& path, void* osHandle)
            : AsyncWorker(callback), path(path), result(nullptr), osHandle(osHandle) {}

        ~LoadModuleJob() {}

    void Execute() override {
        void* library = openLibrary(path.c_str());
        if (!library) return;;

        auto* onInit = reinterpret_cast<void (*)(SkoalaNativeModule*, void*)>(
            findFunction(library, "SkoalaModule_onInit"));
        auto* onDeinit = reinterpret_cast<void (*)(SkoalaNativeModule*)>(
            findFunction(library, "SkoalaModule_onDeinit"));
        auto* sendMessage = reinterpret_cast<int (*)(SkoalaNativeModule*, int, int, int, int, int, int, int)>(
            findFunction(library, "SkoalaModule_sendMessage"));

        if (!onInit || !onDeinit || !sendMessage)
            return;

        result = new SkoalaNativeModule();
        result->context = new NativeModuleState(library, onDeinit);
        result->onInit = onInit;
        result->onDeinit = onDeinit;
        result->sendMessage = sendMessage;

        onInit(result, osHandle);
    }

    void OnOK() override {
        Napi::HandleScope scope(Env());
        Callback().Call({makePointer(Env(), result)});
    }
private:
    SkString path;
    SkoalaNativeModule* result;
    void* osHandle;
};

Napi::Value Node_skoala_SkoalaNativeModule__1nCreate(const Napi::CallbackInfo& info) {
    if (3 != info.Length()) {
        Napi::Error::New(info.Env(), "Wrong arg count")
            .ThrowAsJavaScriptException();
        return makeVoid(info);
    }
    auto pathPtr = getArgument<KStringPtr>(info, 0);
    Napi::Function completer = info[1].As<Napi::Function>();
    void* osHandle = getArgument<KNativePointer>(info, 2);
    SkString path(pathPtr.c_str());
    LoadModuleJob* job = new LoadModuleJob(completer, path, osHandle);
    job->Queue();
    return makeVoid(info);
}
MAKE_INTEROP_NODE_EXPORT(skoala_SkoalaNativeModule__1nCreate)

#endif // KOALA_NAPI