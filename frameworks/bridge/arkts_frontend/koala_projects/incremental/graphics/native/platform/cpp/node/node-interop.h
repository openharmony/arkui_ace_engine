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

#include <node.h>
#include <napi.h>
#include <assert.h>

#include "common-interop.h"

#ifdef SK_BUILD_FOR_WIN
#include <windows.h>
#else
#include <time.h>
#endif

static inline v8::Local<v8::Value> V8LocalValueFromJsValue(napi_value v) {
  v8::Local<v8::Value> local;
  memcpy(static_cast<void*>(&local), &v, sizeof(v));
  return local;
}

struct RedrawerPeer;

typedef RedrawerPeer* (*peerFactory_t)(void* arg, v8::Local<v8::Object> redrawer);

struct NodeScopedState {
    v8::Isolate* isolate;

    std::unique_ptr<v8::Locker> locker;
    std::unique_ptr<v8::Isolate::Scope> isolate_scope;
    std::unique_ptr<v8::Context::Scope> context_scope;

    v8::Global<v8::Context> context;

    v8::Global<v8::Function> onProvidePlatformData;
    v8::Global<v8::Function> onInit;
    v8::Global<v8::Function> onDeinit;
    v8::Global<v8::Function> onFrameEvent;
    v8::Global<v8::Function> onRequestRedraw;
    v8::Global<v8::Function> onTap;
    v8::Global<v8::Function> onMove;
    v8::Global<v8::Function> onMultiTouchTap;
    v8::Global<v8::Function> onMultiTouchMove;
    v8::Global<v8::Function> onFrameMove;
    v8::Global<v8::Function> onKey;
    v8::Global<v8::Function> onTextInput;
    v8::Global<v8::Function> onScroll;
    v8::Global<v8::Function> onResize;
    v8::Global<v8::Function> onDrop;
    v8::Global<v8::Function> permissionGranted;

    bool callbacksStopped;

    NodeScopedState(v8::Isolate* isolate, v8::Local<v8::Context> context)
            : isolate(isolate), callbacksStopped(true) {
        this->context = v8::Global<v8::Context>(isolate, context);
    }

    NodeScopedState(node::CommonEnvironmentSetup* setup)
        : isolate(setup->isolate()), callbacksStopped(true) {
        locker = std::make_unique<v8::Locker>(isolate);
        v8::HandleScope handleScope(isolate);
        isolate_scope = std::make_unique<v8::Isolate::Scope>(isolate);
        v8::Local<v8::Context> context = setup->context();
        this->context = v8::Global<v8::Context>(isolate, context);
        context_scope = std::make_unique<v8::Context::Scope>(context);
    }

    ~NodeScopedState() {
        // TODO: fix me properly.
        context_scope.release();
        isolate_scope.release();
    }

    void initPlatform(v8::Local<v8::Object> api) {
        v8::Local<v8::Context> context = this->context.Get(isolate);
        v8::Local<v8::Value> providePlatformData = api->Get(context, makeString("providePlatformData")).ToLocalChecked();
        if (providePlatformData->IsFunction()) {
            this->onProvidePlatformData = v8::Global<v8::Function>(isolate, providePlatformData.As<v8::Function>());
        }
        v8::Local<v8::Value> onTap = api->Get(context, makeString("onTap")).ToLocalChecked();
        if (onTap->IsFunction()) {
            this->onTap = v8::Global<v8::Function>(isolate, onTap.As<v8::Function>());
        }
        v8::Local<v8::Value> onMove = api->Get(context, makeString("onMove")).ToLocalChecked();
        if (onMove->IsFunction()) {
            this->onMove = v8::Global<v8::Function>(isolate, onMove.As<v8::Function>());
        }
        v8::Local<v8::Value> onMultiTouchTap = api->Get(context, makeString("onMultiTouchTap")).ToLocalChecked();
        if (onMultiTouchTap->IsFunction()) {
            this->onMultiTouchTap = v8::Global<v8::Function>(isolate, onMultiTouchTap.As<v8::Function>());
        }
        v8::Local<v8::Value> onMultiTouchMove = api->Get(context, makeString("onMultiTouchMove")).ToLocalChecked();
        if (onMultiTouchMove->IsFunction()) {
            this->onMultiTouchMove = v8::Global<v8::Function>(isolate, onMultiTouchMove.As<v8::Function>());
        }
        v8::Local<v8::Value> onKey = api->Get(context, makeString("onKey")).ToLocalChecked();
        if (onKey->IsFunction()) {
            this->onKey = v8::Global<v8::Function>(isolate, onKey.As<v8::Function>());
        }
        v8::Local<v8::Value> permissionGranted = api->Get(context, makeString("permissionGranted")).ToLocalChecked();
        if (permissionGranted->IsFunction()) {
            this->permissionGranted = v8::Global<v8::Function>(isolate, permissionGranted.As<v8::Function>());
        }
        v8::Local<v8::Value> onTextInput = api->Get(context, makeString("onTextInput")).ToLocalChecked();
        if (onTextInput->IsFunction()) {
            this->onTextInput = v8::Global<v8::Function>(isolate, onTextInput.As<v8::Function>());
        }
        v8::Local<v8::Value> onScroll = api->Get(context, makeString("onScroll")).ToLocalChecked();
        if (onScroll->IsFunction()) {
            this->onScroll = v8::Global<v8::Function>(isolate, onScroll.As<v8::Function>());
        }
        v8::Local<v8::Value> onResize = api->Get(context, makeString("onResize")).ToLocalChecked();
        if (onResize->IsFunction()) {
            this->onResize = v8::Global<v8::Function>(isolate, onResize.As<v8::Function>());
        }
        v8::Local<v8::Value> onDrop = api->Get(context, makeString("onDrop")).ToLocalChecked();
        if (onDrop->IsFunction()) {
            this->onDrop = v8::Global<v8::Function>(isolate, onDrop.As<v8::Function>());
        }
        v8::Local<v8::Value> onFrameMove = api->Get(context, makeString("onFrameMove")).ToLocalChecked();
        if (onFrameMove->IsFunction()) {
            this->onFrameMove = v8::Global<v8::Function>(isolate, onFrameMove.As<v8::Function>());
        }
        v8::Local<v8::Value> onInit = api->Get(context, makeString("onInit")).ToLocalChecked();
        if (onInit->IsFunction()) {
            this->onInit = v8::Global<v8::Function>(isolate, onInit.As<v8::Function>());
        }
        v8::Local<v8::Value> onDeinit = api->Get(context, makeString("onDeinit")).ToLocalChecked();
        if (onDeinit->IsFunction()) {
            this->onDeinit = v8::Global<v8::Function>(isolate, onDeinit.As<v8::Function>());
        }
        v8::Local<v8::Value> onFrameEvent = api->Get(context, makeString("onFrameEvent")).ToLocalChecked();
        if (onFrameEvent->IsFunction()) {
            this->onFrameEvent = v8::Global<v8::Function>(isolate, onFrameEvent.As<v8::Function>());
        }
        v8::Local<v8::Value> onRequestRedraw = api->Get(context, makeString("onRequestRedraw")).ToLocalChecked();
        if (onRequestRedraw->IsFunction()) {
            this->onRequestRedraw = v8::Global<v8::Function>(isolate, onRequestRedraw.As<v8::Function>());
        }
    }

    v8::Local<v8::Value> makePointerAsLocal(void* ptr) {
        // Keep in sync with NAPI version.
        v8::Local<v8::BigInt> result = v8::BigInt::NewFromUnsigned(isolate, (uint64_t) ptr);
        return result;
    }

    void providePlatformData(peerFactory_t factory, void* ctx) {
        if (onProvidePlatformData.IsEmpty()) return;
        v8::Local<v8::Value> argv[2] = {
            makePointerAsLocal(reinterpret_cast<void*>(factory)),
            makePointerAsLocal(reinterpret_cast<void*>(ctx))
        };
        v8::Local<v8::Function> providePlatformData = this->onProvidePlatformData.Get(isolate);
        auto result = providePlatformData->Call(isolate->GetCurrentContext(), v8::Object::New(isolate), 2, argv);
        (void)result;
    }

    void callPermissionGranted(
        v8::Local<v8::Object> redrawer,
        int requestCode,
        std::vector<std::string>& permissions,
        std::vector<int>& grantResults) {
        if (permissionGranted.IsEmpty() || callbacksStopped) return;

        v8::Local<v8::Function> permissionGranted = this->permissionGranted.Get(isolate);

        int permissionsNumber = permissions.size();
        v8::Local<v8::Value>* permissionNames = new v8::Local<v8::Value>[permissionsNumber];
        v8::Local<v8::Value>* permissionGrants = new v8::Local<v8::Value>[permissionsNumber];

        for (int i=0; i<permissionsNumber; i++) {
            permissionNames[i] = v8::String::NewFromUtf8(isolate, permissions[i].c_str()).ToLocalChecked();
            permissionGrants[i] = v8::Number::New(isolate, grantResults[i]);
        }

        v8::Local<v8::Array> grantsValue = v8::Array::New(isolate, permissionGrants, permissionsNumber);
        v8::Local<v8::Array> namesValue = v8::Array::New(isolate, permissionNames, permissionsNumber);

        v8::Local<v8::Value> argv[3] = {
            v8::Number::New(isolate, requestCode),
            namesValue,
            grantsValue
        };

        auto result = permissionGranted->Call(isolate->GetCurrentContext(), redrawer, 3, argv);
        (void)result;
    }

    void callOnInit(v8::Local<v8::Object> redrawer, void* peer) {
        if (onInit.IsEmpty()) return;
        v8::Local<v8::Function> onInit = this->onInit.Get(isolate);
        v8::Local<v8::Value> argv[1] = {
            makePointerAsLocal(peer)
        };
        auto result = onInit->Call(isolate->GetCurrentContext(), redrawer, 1, argv);
        (void)result;
    }

    void callOnDeinit(v8::Local<v8::Object> redrawer) {
        if (onDeinit.IsEmpty()) return;
        v8::Local<v8::Function> onDeinit = this->onDeinit.Get(isolate);
        auto result = onDeinit->Call(isolate->GetCurrentContext(), redrawer, 0, nullptr);
        (void)result;
    }

    void callOnFrameEvent(v8::Local<v8::Object> redrawer, FrameEventType type) {
        if (onFrameEvent.IsEmpty()) return;
        v8::Local<v8::Function> onFrameEvent = this->onFrameEvent.Get(isolate);
        v8::Local<v8::Value> argv[1] = {
                v8::Number::New(isolate, (int)type)
        };
        auto result = onFrameEvent->Call(isolate->GetCurrentContext(), redrawer, 1, argv);
        (void)result;
    }

    void callOnRequestRedraw(v8::Local<v8::Object> redrawer) {
        if (onRequestRedraw.IsEmpty()) return;
        v8::Local<v8::Function> onRequestRedraw = this->onRequestRedraw.Get(isolate);
        auto result = onRequestRedraw->Call(isolate->GetCurrentContext(), redrawer, 0, nullptr);
        (void)result;
    }

    v8::Local<v8::Value> makeString(const char* str) {
        return v8::String::NewFromOneByte(isolate, reinterpret_cast<const uint8_t*>(str)).ToLocalChecked();
    }

    void callOnTap(v8::Local<v8::Object> redrawer, int count, int* xValues, int* yValues, int tap, int target, int button) {
        if (count > 1) {
            if (onMultiTouchTap.IsEmpty() || callbacksStopped) return;
            v8::Local<v8::Value>* xV8Values = new v8::Local<v8::Value>[count];
            v8::Local<v8::Value>* yV8Values = new v8::Local<v8::Value>[count];

            for (int i = 0; i < count; i++) {
                xV8Values[i] = v8::Number::New(isolate, xValues[i]);
                yV8Values[i] = v8::Number::New(isolate, yValues[i]);
            }

            v8::Local<v8::Function> onMultiTouchTap = this->onMultiTouchTap.Get(isolate);
            v8::Local<v8::Value> argv[4] = {
                    v8::Array::New(isolate, xV8Values, count),
                    v8::Array::New(isolate, yV8Values, count),
                    v8::Number::New(isolate, tap),
                    v8::Number::New(isolate, target)
            };
            auto result = onMultiTouchTap->Call(isolate->GetCurrentContext(), redrawer, 4, argv);
            (void)result;
        } else {
            if (onMove.IsEmpty() || callbacksStopped) return;
            v8::Local<v8::Function> onTap = this->onTap.Get(isolate);
            v8::Local<v8::Value> argv[4] = {
                    v8::Number::New(isolate, xValues[0]),
                    v8::Number::New(isolate, yValues[0]),
                    v8::Number::New(isolate, tap),
                    v8::Number::New(isolate, button)
            };
            auto result = onTap->Call(isolate->GetCurrentContext(), redrawer, 4, argv);
            (void)result;
        }
    }

    void callOnMove(v8::Local<v8::Object> redrawer, int count, int* xValues, int* yValues) {
        if (count > 1) {
            if (onMultiTouchMove.IsEmpty() || callbacksStopped) return;
            v8::Local<v8::Value>* xV8Values = new v8::Local<v8::Value>[count];
            v8::Local<v8::Value>* yV8Values = new v8::Local<v8::Value>[count];

            for (int i = 0; i < count; i++) {
                xV8Values[i] = v8::Number::New(isolate, xValues[i]);
                yV8Values[i] = v8::Number::New(isolate, yValues[i]);
            }

            v8::Local<v8::Function> onMultiTouchMove = this->onMultiTouchMove.Get(isolate);
            v8::Local<v8::Value> argv[2] = {
                    v8::Array::New(isolate, xV8Values, count),
                    v8::Array::New(isolate, yV8Values, count)
            };
            auto result = onMultiTouchMove->Call(isolate->GetCurrentContext(), redrawer, 2, argv);
            (void)result;
        } else {
            if (onMove.IsEmpty() || callbacksStopped) return;
            v8::Local<v8::Function> onMove = this->onMove.Get(isolate);
            v8::Local<v8::Value> argv[2] = {
                    v8::Number::New(isolate, xValues[0]),
                    v8::Number::New(isolate, yValues[0])
            };
            auto result = onMove->Call(isolate->GetCurrentContext(), redrawer, 2, argv);
            (void)result;
        }
    }

    void callOnKey(v8::Local<v8::Object> redrawer, int key, int modifiers, int isPressed) {
        if (onKey.IsEmpty() || callbacksStopped) return;

        v8::Local<v8::Function> onKey = this->onKey.Get(isolate);
        v8::Local<v8::Value> argv[3] = {
                v8::Number::New(isolate, key),
                v8::Number::New(isolate, modifiers),
                v8::Number::New(isolate, isPressed)
        };
        auto result = onKey->Call(isolate->GetCurrentContext(), redrawer, 3, argv);
        (void)result;
    }

    void callOnTextInput(v8::Local<v8::Object> redrawer, int type, int cursorPosition, std::string characters) {
        if (onTextInput.IsEmpty() || callbacksStopped) return;

        v8::Local<v8::Function> onTextInput = this->onTextInput.Get(isolate);
        v8::Local<v8::Value> argv[3] = {
                v8::Number::New(isolate, type),
                v8::Number::New(isolate, cursorPosition),
                v8::String::NewFromUtf8(isolate, characters.c_str(), v8::NewStringType::kNormal, characters.size()).ToLocalChecked()
        };
        auto result = onTextInput->Call(isolate->GetCurrentContext(), redrawer, 3, argv);
        (void)result;
    }

    void callOnScroll(v8::Local<v8::Object> redrawer, int xpos, int ypos, int xoffset, int yoffset) {
        if (onScroll.IsEmpty() || callbacksStopped) return;
        v8::Local<v8::Function> onScroll = this->onScroll.Get(isolate);
        v8::Local<v8::Value> argv[4] = {
                v8::Number::New(isolate, xpos),
                v8::Number::New(isolate, ypos),
                v8::Number::New(isolate, xoffset),
                v8::Number::New(isolate, yoffset)
        };
        auto result = onScroll->Call(isolate->GetCurrentContext(), redrawer, 4, argv);
        (void)result;
    }

    void callOnResize(v8::Local<v8::Object> redrawer, int width, int height) {
        if (onResize.IsEmpty() || callbacksStopped) return;
        v8::Local<v8::Function> onResize = this->onResize.Get(isolate);
        v8::Local<v8::Value> argv[2] = {
                v8::Number::New(isolate, width),
                v8::Number::New(isolate, height)
        };
        auto result = onResize->Call(isolate->GetCurrentContext(), redrawer, 2, argv);
        (void)result;
    }

    void callOnDrop(v8::Local<v8::Object> redrawer, int count, const char** paths, int x, int y) {
        if (onDrop.IsEmpty() || callbacksStopped) return;
        v8::Local<v8::Function> onDrop = this->onDrop.Get(isolate);
        v8::Local<v8::Value>* pathsV8 = new v8::Local<v8::Value>[count];

        for (int i = 0; i < count; i++) {
            pathsV8[i] = v8::String::NewFromUtf8(isolate, paths[i]).ToLocalChecked();
        }
        v8::Local<v8::Value> argv[3] = {
            v8::Array::New(isolate, pathsV8, count),
            v8::Number::New(isolate, x),
            v8::Number::New(isolate, y),
        };

        auto result = onDrop->Call(isolate->GetCurrentContext(), redrawer, 3, argv);
        (void)result;
    }

    void callOnFrameMove(v8::Local<v8::Object> redrawer, int x, int y) {
        if (onFrameMove.IsEmpty() || callbacksStopped) return;
        v8::Local<v8::Function> onFrameMove = this->onFrameMove.Get(isolate);
        v8::Local<v8::Value> argv[2] = {
                v8::Number::New(isolate, x),
                v8::Number::New(isolate, y)
        };
        auto result = onFrameMove->Call(isolate->GetCurrentContext(), redrawer, 2, argv);
        (void)result;
    }

    void startCallbacks() {
        callbacksStopped = false;
    }

    void stopCallbacks() {
        callbacksStopped = true;
    }
};

struct RedrawerPeer : public RedrawerPeerBase {
    NodeScopedState* node;
    v8::Global<v8::Object> redrawer;
    RedrawerPeer(NodeScopedState* node, v8::Local<v8::Object> redrawer)
        : node(node), redrawer(v8::Global<v8::Object>(node->isolate, redrawer))
        {}

    void callRequestRedraw() {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnRequestRedraw(this->redrawer.Get(node->isolate));
    }

    void callOnInit() {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnInit(this->redrawer.Get(node->isolate), this);
    }

    void callOnDeinit() {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnDeinit(this->redrawer.Get(node->isolate));
    }

    void callOnFrameEvent(FrameEventType type) {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnFrameEvent(this->redrawer.Get(node->isolate), type);
    }

    void callOnTap(int count, int* xValues, int* yValues, int tap, int target, int button) {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnTap(this->redrawer.Get(node->isolate), count, xValues, yValues, tap, target, button);
    }

    void callOnMove(int count, int* xValues, int* yValues) {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnMove(this->redrawer.Get(node->isolate), count, xValues, yValues);
    }

    void callOnKey(int key, int modifiers, int isPressed) {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnKey(this->redrawer.Get(node->isolate), key, modifiers, isPressed);
    }

    void callPermissionGranted(int requestCode,
        std::vector<std::string>& permissions,
        std::vector<int>& grantResults) {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;

        node->callPermissionGranted(
            this->redrawer.Get(node->isolate),
            requestCode,
            permissions,
            grantResults);
    }

    void callOnTextInput(int type, int cursorPosition, std::string characters) {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnTextInput(this->redrawer.Get(node->isolate), type, cursorPosition, characters);
    }

    void callOnScroll(int xpos, int ypos, int xoffset, int yoffset) {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnScroll(this->redrawer.Get(node->isolate), xpos, ypos, xoffset, yoffset);
    }

    void callOnResize(int width, int height) {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnResize(this->redrawer.Get(node->isolate), width, height);
    }

    void callOnDrop(int count, const char** paths, int x, int y) {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnDrop(this->redrawer.Get(node->isolate), count, paths, x, y);
    }

    void callOnFrameMove(int x, int y) {
        v8::HandleScope scope(node->isolate);
        if (redrawer.IsEmpty()) return;
        node->callOnFrameMove(this->redrawer.Get(node->isolate), x, y);
    }
};

struct NodeCallback {
    v8::Isolate* isolate;
    v8::Global<v8::Context> context;
    v8::Global<v8::Object> receiver;
    v8::Global<v8::Function> callback;

    NodeCallback(v8::Isolate* isolate, v8::Local<v8::Context> context,
        v8::Local<v8::Object> receiver, v8::Local<v8::Function> callback)
        : isolate(isolate),
          context(v8::Global<v8::Context>(isolate, context)),
          receiver(v8::Global<v8::Object>(isolate, receiver)),
          callback(v8::Global<v8::Function>(isolate, callback))
        {}

    v8::Local<v8::Value> callCallback() {
        if (callback.IsEmpty()) {
            return v8::Undefined(isolate);
        }
        v8::Local<v8::Function> callback = this->callback.Get(isolate);
        v8::Local<v8::Object> receiver = this->receiver.Get(isolate);
        v8::Local<v8::Context> context = this->context.Get(isolate);
        v8::MaybeLocal<v8::Value> maybeResult = callback->Call(context, receiver, 0, {});
        if (maybeResult.IsEmpty()) {
            return v8::Undefined(isolate);
        }
        v8::Local<v8::Value> result;
        if (!maybeResult.ToLocal(&result)) {
            return v8::Undefined(isolate);
        }
        return result;
    }
};

struct NodeRuntime {
    node::MultiIsolatePlatform* platform;
    node::CommonEnvironmentSetup* setup;

    NodeRuntime() : platform(nullptr), setup(nullptr) {}

    bool init(bool inspect) {
        std::vector<std::string> args{"--expose-gc"};
        if (inspect) args.push_back("--inspect");
        std::vector<std::string> exec_args;
        std::vector<std::string> errors;
        int exit_code = node::InitializeNodeWithArgs(&args, &exec_args, &errors);
        assert(exit_code == 0);
        platform = node::MultiIsolatePlatform::Create(4).release();
        v8::V8::InitializePlatform(platform);
        v8::V8::Initialize();
        this->setup = node::CommonEnvironmentSetup::Create(
            platform, &errors, args, exec_args
        ).release();
        if (setup == nullptr) return false;
        node::SetProcessExitHandler(setup->env(), [](node::Environment* env, int errorCode) {
            fprintf(stderr, "Trying to exit with code = %d", errorCode);
        });
        return true;
    }

    void deinit() {
        node::Stop(setup->env());
        delete setup;
        delete platform;
        v8::V8::Dispose();
        v8::V8::DisposePlatform();
    }
};