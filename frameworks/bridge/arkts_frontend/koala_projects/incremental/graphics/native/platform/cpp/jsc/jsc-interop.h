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

#include "skoala-interop.h"

#include <iostream>
#include <vector>
#include <deque>

#include "Event.h"

struct RedrawerPeer;

typedef RedrawerPeer* (*peerFactory_t)(void* arg, JSObjectRef redrawer);

struct JSValueHolder {
    JSContextRef ctx;
    JSValueRef value;
    JSValueHolder()  : ctx(nullptr), value(nullptr) {}
    JSValueHolder(JSContextRef ctx, JSValueRef value) {
        init(ctx, value);
    }
    ~JSValueHolder() {
        if (ctx && JSValueIsObject(ctx, value))
            JSValueUnprotect(ctx, JSValueToObject(ctx, value, nullptr));
    }
    void init(JSContextRef ctx, JSValueRef value) {
        this->ctx = ctx;
        this->value = value;
        if (ctx && JSValueIsObject(ctx, value))
            JSValueProtect(ctx, JSValueToObject(ctx, value, nullptr));
    }

    JSObjectRef obj() {
        assert(JSValueIsObject(ctx, value));
        return JSValueToObject(ctx, value, nullptr);
    }
};


struct JscScopedState {
    JSContextRef context;
    JSObjectRef thisObject;
    JSValueHolder* api = nullptr;

    JSObjectRef onProvidePlatformData;
    JSObjectRef onInit;
    JSObjectRef onDeinit;
    JSObjectRef onFrameEvent;
    JSObjectRef onRequestRedraw;
    JSObjectRef onTap;
    JSObjectRef onMove;
    JSObjectRef onMultiTouchTap;
    JSObjectRef onMultiTouchMove;
    JSObjectRef onFrameMove;
    JSObjectRef onKey;
    JSObjectRef onTextInput;
    JSObjectRef onScroll;
    JSObjectRef onResize;
    JSObjectRef permissionGranted;

    bool callbacksStopped;

    JscScopedState(JSContextRef context, JSObjectRef thisObject)
            : context(context), thisObject(thisObject), callbacksStopped(true) {}

    ~JscScopedState() {
        if(this->api) delete this->api;
    }

    std::string JSStringToStdString(JSStringRef jsString) {
        size_t maxBufferSize = JSStringGetMaximumUTF8CStringSize(jsString);
        char* utf8Buffer = new char[maxBufferSize];
        size_t bytesWritten = JSStringGetUTF8CString(jsString, utf8Buffer, maxBufferSize);
        std::string utf_string = std::string(utf8Buffer, bytesWritten - 1);
        delete[] utf8Buffer;
        return utf_string;
    }

    void initPlatform(JSValueHolder* api) {
        this->api = api;
        // providePlatformData
        JSValueRef providePlatformData = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("providePlatformData"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, providePlatformData, nullptr))) {
            this->onProvidePlatformData = JSValueToObject(context, providePlatformData, nullptr);
        }
        // onInit
        JSValueRef onInit = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onInit"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onInit, nullptr))) {
            this->onInit = JSValueToObject(context, onInit, nullptr);
        }
        // onMove
        JSValueRef onMove = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onMove"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onMove, nullptr))) {
            this->onMove = JSValueToObject(context, onMove, nullptr);
        }
        // onTap
        JSValueRef onTap = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onTap"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onTap, nullptr))) {
            this->onTap = JSValueToObject(context, onTap, nullptr);
        }
        // onMultiTouchTap
        JSValueRef onMultiTouchTap = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onMultiTouchTap"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onMultiTouchTap, nullptr))) {
            this->onMultiTouchTap = JSValueToObject(context, onMultiTouchTap, nullptr);
        }
        // onMultiTouchMove
        JSValueRef onMultiTouchMove = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onMultiTouchMove"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onMultiTouchMove, nullptr))) {
            this->onMultiTouchMove = JSValueToObject(context, onMultiTouchMove, nullptr);
        }
        // onKey
        JSValueRef onKey = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onKey"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onKey, nullptr))) {
            this->onKey = JSValueToObject(context, onKey, nullptr);
        }
        // permissionGranted
        JSValueRef permissionGranted = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("permissionGranted"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, permissionGranted, nullptr))) {
            this->permissionGranted = JSValueToObject(context, permissionGranted, nullptr);
        }
        // onTextInput
        JSValueRef onTextInput = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onTextInput"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onTextInput, nullptr))) {
            this->onTextInput = JSValueToObject(context, onTextInput, nullptr);
        }
        // onScroll
        JSValueRef onScroll = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onScroll"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onScroll, nullptr))) {
            this->onScroll = JSValueToObject(context, onScroll, nullptr);
        }
        // onResize
        JSValueRef onResize = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onResize"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onResize, nullptr))) {
            this->onResize = JSValueToObject(context, onResize, nullptr);
        }
        // onFrameMove
        JSValueRef onFrameMove = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onFrameMove"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onFrameMove, nullptr))) {
            this->onFrameMove = JSValueToObject(context, onFrameMove, nullptr);
        }
        // onDeinit
        JSValueRef onDeinit = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onDeinit"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onDeinit, nullptr))) {
            this->onDeinit = JSValueToObject(context, onDeinit, nullptr);
        }
        // onFrameEvent
        JSValueRef onFrameEvent = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onFrameEvent"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onFrameEvent, nullptr))) {
            this->onFrameEvent = JSValueToObject(context, onFrameEvent, nullptr);
        }
        // onRequestRedraw
        JSValueRef onRequestRedraw = JSObjectGetProperty(context, api->obj(), JSStringCreateWithUTF8CString("onRequestRedraw"), nullptr);
        if (JSObjectIsFunction(context, JSValueToObject(context, onRequestRedraw, nullptr))) {
            this->onRequestRedraw = JSValueToObject(context, onRequestRedraw, nullptr);
        }
    }

    void providePlatformData(peerFactory_t factory, void* ctx) {
        JSObjectRef providePlatformData = this->onProvidePlatformData;
        std::vector<JSValueRef> args = {makePointer(context, reinterpret_cast<void*>(factory)), makePointer(context, reinterpret_cast<void*>(ctx))};
        auto result = JSObjectCallAsFunction(context, providePlatformData, this->thisObject, 2, &args[0], nullptr);
        (void)result;
    }

    void callOnInit(JSObjectRef redrawer, void* peer) {
        JSObjectRef onInit = this->onInit;

        std::vector<JSValueRef> args;
        args.emplace_back(makePointer(context, (KNativePointer)peer));

        JSValueRef exc {};
        auto result = JSObjectCallAsFunction(context, onInit, redrawer, args.size(), &args[0], &exc);
        if (exc) {
            std::cout << JSStringToStdString(JSValueToStringCopy(context, exc, nullptr)) << std::endl;
        }
        (void)result;
    }

    void callOnDeinit(JSObjectRef redrawer) {
        JSObjectRef onDeinit = this->onDeinit;

        JSValueRef exc {};
        auto result = JSObjectCallAsFunction(context, onDeinit, redrawer, 0, nullptr, &exc);
        if (exc) {
            std::cout << JSStringToStdString(JSValueToStringCopy(context, exc, nullptr)) << std::endl;
        }
        (void)result;
    }

    void callOnFrameEvent(JSObjectRef redrawer, FrameEventType type) {
        JSObjectRef onFrameEvent = this->onFrameEvent;
        JSValueRef args[1];
        args[0] = JSValueMakeNumber(context, (int)type);
        JSValueRef exc {};
        auto result = JSObjectCallAsFunction(context, onFrameEvent, redrawer, 1, &args[0], &exc);
        if (exc) {
            std::cout << JSStringToStdString(JSValueToStringCopy(context, exc, nullptr)) << std::endl;
        }
        (void)result;
    }

    void callOnRequestRedraw(JSObjectRef redrawer) {
        JSObjectRef onRequestRedraw = this->onRequestRedraw;

        JSValueRef exc {};
        auto result = JSObjectCallAsFunction(context, onRequestRedraw, redrawer, 0, nullptr, &exc);
        if (exc) {
            std::cout << JSStringToStdString(JSValueToStringCopy(context, exc, nullptr)) << std::endl;
        }
        (void)result;
    }

    void callOnMove(JSObjectRef redrawer, int count, int* xValues, int* yValues) {
        JSValueRef args[2];
        JSValueRef exc {};

        if (count == 1) {
            args[0] = JSValueMakeNumber(context, xValues[0]);
            args[1] = JSValueMakeNumber(context, yValues[0]);
            auto result = JSObjectCallAsFunction(context, onMove, redrawer, 2, &args[0], &exc);
            (void)result;
        } else {
            JSObjectRef xs = JSObjectMakeTypedArray(context, kJSTypedArrayTypeInt32Array, count, &exc);
            JSObjectRef ys = JSObjectMakeTypedArray(context, kJSTypedArrayTypeInt32Array, count, &exc);
            int32_t* xsRaw = reinterpret_cast<int32_t*>(JSObjectGetTypedArrayBytesPtr(context, xs, &exc));
            int32_t* ysRaw = reinterpret_cast<int32_t*>(JSObjectGetTypedArrayBytesPtr(context, ys, &exc));
            memcpy(xsRaw, xValues, 4 * count);
            memcpy(ysRaw, yValues, 4 * count);
            args[0] = xs;
            args[1] = ys;
            auto result = JSObjectCallAsFunction(context, onMultiTouchMove, redrawer, 2, &args[0], &exc);
            (void)result;
        }
    }

    void callOnTap(JSObjectRef redrawer, int count, int* xValues, int* yValues, int tap, int target, int button) {
        JSValueRef args[4];
        JSValueRef exc {};

        if (count == 1) {
            args[0] = JSValueMakeNumber(context, xValues[0]);
            args[1] = JSValueMakeNumber(context, yValues[0]);
            args[2] = JSValueMakeNumber(context, tap);
            args[3] = JSValueMakeNumber(context, button);
            auto result = JSObjectCallAsFunction(context, onTap, redrawer, 4, &args[0], &exc);
            (void)result;
        } else {
            JSObjectRef xs = JSObjectMakeTypedArray(context, kJSTypedArrayTypeInt32Array, count, &exc);
            JSObjectRef ys = JSObjectMakeTypedArray(context, kJSTypedArrayTypeInt32Array, count, &exc);
            int32_t* xsRaw = reinterpret_cast<int32_t*>(JSObjectGetTypedArrayBytesPtr(context, xs, &exc));
            int32_t* ysRaw = reinterpret_cast<int32_t*>(JSObjectGetTypedArrayBytesPtr(context, ys, &exc));
            memcpy(xsRaw, xValues, 4 * count);
            memcpy(ysRaw, yValues, 4 * count);
            args[0] = xs;
            args[1] = ys;
            args[2] = JSValueMakeNumber(context, tap);
            args[3] = JSValueMakeNumber(context, button);
            JSValueRef exc {};
            auto result = JSObjectCallAsFunction(context, onMultiTouchTap, redrawer, 4, &args[0], &exc);
            (void)result;
        }
    }

    void callOnKey(JSObjectRef redrawer, int key, int modifiers, int isPressed) {
        JSObjectRef onKey = this->onKey;

        std::vector<JSValueRef> args;
        args.emplace_back(JSValueMakeNumber(context, key));
        args.emplace_back(JSValueMakeNumber(context, modifiers));
        args.emplace_back(JSValueMakeNumber(context, isPressed));

        JSValueRef exc {};
        auto result = JSObjectCallAsFunction(context, onKey, redrawer, args.size(), &args[0], &exc);
        if (exc) {
            std::cout << JSStringToStdString(JSValueToStringCopy(context, exc, nullptr)) << std::endl;
        }
        (void)result;
    }

    void callOnTextInput(JSObjectRef redrawer, int type, int cursorPosition, std::string characters) {
        JSObjectRef onTextInput = this->onTextInput;

        std::vector<JSValueRef> args;
        args.emplace_back(JSValueMakeNumber(context, type));
        args.emplace_back(JSValueMakeNumber(context, cursorPosition));
        args.emplace_back(JSValueMakeString(context, JSStringCreateWithUTF8CString(characters.c_str())));

        JSValueRef exc {};
        auto result = JSObjectCallAsFunction(context, onTextInput, redrawer, args.size(), &args[0], &exc);
        if (exc) {
            std::cout << JSStringToStdString(JSValueToStringCopy(context, exc, nullptr)) << std::endl;
        }
        (void)result;
    }

    void callOnScroll(JSObjectRef redrawer, int xpos, int ypos, int xoffset, int yoffset) {
        JSObjectRef onScroll = this->onScroll;

        std::vector<JSValueRef> args;
        args.emplace_back(JSValueMakeNumber(context, xpos));
        args.emplace_back(JSValueMakeNumber(context, ypos));
        args.emplace_back(JSValueMakeNumber(context, xoffset));
        args.emplace_back(JSValueMakeNumber(context, yoffset));

        JSValueRef exc {};
        auto result = JSObjectCallAsFunction(context, onScroll, redrawer, args.size(), &args[0], &exc);
        if (exc) {
            std::cout << JSStringToStdString(JSValueToStringCopy(context, exc, nullptr)) << std::endl;
        }
        (void)result;
    }

    void callOnResize(JSObjectRef redrawer, int width, int height) {
        JSObjectRef onResize = this->onResize;

        std::vector<JSValueRef> args;
        args.emplace_back(JSValueMakeNumber(context, width));
        args.emplace_back(JSValueMakeNumber(context, height));

        JSValueRef exc {};
        auto result = JSObjectCallAsFunction(context, onResize, redrawer, args.size(), &args[0], &exc);
        if (exc) {
            std::cout << JSStringToStdString(JSValueToStringCopy(context, exc, nullptr)) << std::endl;
        }
        (void)result;
    }

    void callOnFrameMove(JSObjectRef redrawer, int x, int y) {
        JSObjectRef onFrameMove = this->onFrameMove;

        std::vector<JSValueRef> args;
        args.emplace_back(JSValueMakeNumber(context, x));
        args.emplace_back(JSValueMakeNumber(context, y));

        JSValueRef exc {};
        auto result = JSObjectCallAsFunction(context, onFrameMove, redrawer, args.size(), &args[0], &exc);
        if (exc) {
            std::cout << JSStringToStdString(JSValueToStringCopy(context, exc, nullptr)) << std::endl;
        }
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
    JscScopedState* state;
    JSObjectRef redrawer;
    std::deque<std::unique_ptr<Event>> _pendingEvents;

    RedrawerPeer(JscScopedState* state, JSObjectRef redrawer)
        : state(state), redrawer(redrawer)
        {}

    void callRequestRedraw() {
        state->callOnRequestRedraw(this->redrawer);
    }

    void callOnInit() {
        state->callOnInit(this->redrawer, this);
    }

    void callOnDeinit() {
        state->callOnDeinit(this->redrawer);
    }

    void callOnFrameEvent(FrameEventType type) {
        state->callOnFrameEvent(this->redrawer, type);
    }

    void callOnMove(int count, int* xValues, int* yValues) {
        state->callOnMove(this->redrawer, count, xValues, yValues);
    }

    void callOnTap(int count, int* xValues, int* yValues, int tap, int target, int button) {
        state->callOnTap(this->redrawer, count, xValues, yValues, tap, target, button);
    }

    void callOnKey(int key, int modifiers, int isPressed) {
        state->callOnKey(this->redrawer, key, modifiers, isPressed);
    }

    void callOnTextInput(int type, int cursorPosition, std::string characters) {
        state->callOnTextInput(this->redrawer, type, cursorPosition, characters);
    }

    void callOnScroll(int xpos, int ypos, int xoffset, int yoffset) {
        state->callOnScroll(this->redrawer, xpos, ypos, xoffset, yoffset);
    }

    void callOnResize(int width, int height) {
        state->callOnResize(this->redrawer, width, height);
    }

    void callOnFrameMove(int x, int y) {
        state->callOnFrameMove(this->redrawer, x, y);
    }

};

struct JscCallback {
    JSContextRef context;
    JSObjectRef object;
    JSObjectRef receiver;
    JSObjectRef callback;

    JscCallback(JSContextRef context, JSObjectRef object, JSObjectRef receiver, JSObjectRef callback): context(context), object(object), receiver(receiver), callback(callback) {}

    JSValueRef callCallback() {
        JSObjectRef callback = this->callback;
        JSObjectRef receiver = this->receiver;
        //JSObjectRef object = this->object;
        JSValueRef result = JSObjectCallAsFunction(context, callback, receiver, 0, nullptr, nullptr);

        return result;
    }

};