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

#include "napi.h"
#include "oh_sk_log.h"
#include "convertors-napi.h"
#include "common-interop.h"

#define GET_AND_THROW_LAST_ERROR(env)                                        \
    do {                                                                     \
        const napi_extended_error_info *error_info;                          \
        napi_get_last_error_info((env), &error_info);                        \
        bool is_pending;                                                     \
        napi_is_exception_pending((env), &is_pending);                       \
        /* If an exception is already pending, don't rethrow it */           \
        if (!is_pending) {                                                   \
            const char* error_message = error_info->error_message != NULL ?  \
            error_info->error_message :                                      \
            "empty error message";                                           \
            OH_SK_LOG_ERROR_A("error: %s", error_message);                   \
            napi_throw_error((env), NULL, error_message);                    \
        }                                                                    \
    } while (0)

#define NAPI_CALL(env, the_call, ret_val)                                    \
    do {                                                                     \
        if ((the_call) != napi_ok) {                                         \
            GET_AND_THROW_LAST_ERROR((env));                                 \
            return ret_val;                                                  \
        }                                                                    \
    } while (0)

#define NAPI_CALL_VOID(env, the_call)                                        \
    do {                                                                     \
        if ((the_call) != napi_ok) {                                         \
            GET_AND_THROW_LAST_ERROR((env));                                 \
            return;                                                          \
        }                                                                    \
    } while (0)

#define REF_CALLBACK(name)                                                                      \
    do {                                                                                        \
        napi_env env = info.Env();                                                              \
        napi_value name##Callback = nullptr;                                                    \
        NAPI_CALL_VOID(env, napi_get_named_property(env, platformApi, #name, &name##Callback)); \
        NAPI_CALL_VOID(env, napi_create_reference(env, name##Callback, 1, &name##CallbackRef)); \
    } while (0)

#define INVOKE_CALLBACK(callbackRef, argc, ... /* args */)                                  \
    do {                                                                                    \
        napi_env env = info.Env();                                                          \
        napi_value func = nullptr;                                                          \
        NAPI_CALL_VOID(env, napi_get_reference_value(env, callbackRef, &func));             \
        assert(func != nullptr);                                                            \
        napi_value redrawer = nullptr;                                                      \
        NAPI_CALL_VOID(env, napi_get_reference_value(env, redrawerRef, &redrawer));         \
        assert(redrawer != nullptr);                                                        \
        napi_value args[] = { __VA_ARGS__ };                                                \
        napi_value result = nullptr;                                                        \
        NAPI_CALL_VOID(env, napi_call_function(env, redrawer, func, argc, args, &result));  \
    } while (0)

struct RedrawerPeer : public RedrawerPeerBase {
    napi_ref onInitCallbackRef;
    napi_ref onTapCallbackRef;
    napi_ref onMultiTouchTapCallbackRef;
    napi_ref onMoveCallbackRef;
    napi_ref onMultiTouchMoveCallbackRef;
    napi_ref onKeyCallbackRef;
    napi_ref onTextInputCallbackRef;
    napi_ref onScrollCallbackRef;
    napi_ref onResizeCallbackRef;

    napi_ref redrawerRef;

    RedrawerPeer(const Napi::CallbackInfo& info, napi_value platformApi, napi_value redrawer) {
        REF_CALLBACK(onInit);
        REF_CALLBACK(onTap);
        REF_CALLBACK(onMultiTouchTap);
        REF_CALLBACK(onMove);
        REF_CALLBACK(onMultiTouchMove);
        REF_CALLBACK(onKey);
        REF_CALLBACK(onTextInput);
        REF_CALLBACK(onScroll);
        REF_CALLBACK(onResize);

        napi_create_reference(info.Env(), redrawer, 1, &redrawerRef);
    }

    void release(const Napi::CallbackInfo& info) {
        napi_env env = info.Env();
        napi_delete_reference(env, redrawerRef);
        napi_delete_reference(env, onInitCallbackRef);
        napi_delete_reference(env, onTapCallbackRef);
        napi_delete_reference(env, onMultiTouchTapCallbackRef);
        napi_delete_reference(env, onMoveCallbackRef);
        napi_delete_reference(env, onMultiTouchMoveCallbackRef);
        napi_delete_reference(env, onKeyCallbackRef);
        napi_delete_reference(env, onTextInputCallbackRef);
        napi_delete_reference(env, onScrollCallbackRef);
        napi_delete_reference(env, onResizeCallbackRef);
    }

    void callOnInitEnv(const Napi::CallbackInfo& info) {
        INVOKE_CALLBACK(onInitCallbackRef, 1,
                        makePointer(info, this));
    }

    void callOnTapEnv(const Napi::CallbackInfo& info, int count, int* xs, int* ys, int tap, int button) {
        if (count == 1) {
            INVOKE_CALLBACK(onTapCallbackRef, 4,
                            makeInt32(info, xs[0]),
                            makeInt32(info, ys[0]),
                            makeInt32(info, tap),
                            makeInt32(info, button)
            );
        } else {
            auto xArray = Napi::Array::New(info.Env(), count);
            auto yArray = Napi::Array::New(info.Env(), count);
            for (int i = 0; i < count; i++) {
                xArray[i] = makeInt32(info, xs[i]);
                yArray[i] = makeInt32(info, ys[i]);
            }
            INVOKE_CALLBACK(onMultiTouchTapCallbackRef, 4,
                            xArray,
                            yArray,
                            makeInt32(info, tap),
                            makeInt32(info, button));
        }
    }

    void callOnMoveEnv(const Napi::CallbackInfo& info, int count, int* xs, int* ys) {
        if (count == 1) {
            INVOKE_CALLBACK(onMoveCallbackRef, 2,
                            makeInt32(info, xs[0]),
                            makeInt32(info, ys[0]));
        } else {
            auto xArray = Napi::Array::New(info.Env(), count);
            auto yArray = Napi::Array::New(info.Env(), count);
            for (int i = 0; i < count; i++) {
                xArray[i] = makeInt32(info, xs[i]);
                yArray[i] = makeInt32(info, ys[i]);
            }
            INVOKE_CALLBACK(onMultiTouchMoveCallbackRef, 2,
                            xArray,
                            yArray);
        }
    }

    void callOnKeyEnv(const Napi::CallbackInfo& info, int key, int modifiers, int isPressed) {
        INVOKE_CALLBACK(onKeyCallbackRef, 3,
                        makeInt32(info, key),
                        makeInt32(info, modifiers),
                        makeInt32(info, isPressed));
    }

    void callOnTextInputEnv(const Napi::CallbackInfo& info, int type, int cursorPosition, std::string characters) {
        INVOKE_CALLBACK(onTextInputCallbackRef, 3,
                        makeInt32(info, type),
                        makeInt32(info, cursorPosition),
                        makeString(info, characters));
    }

    void callOnScrollEnv(const Napi::CallbackInfo& info, int xpos, int ypos, int xoffset, int yoffset) {
        INVOKE_CALLBACK(onScrollCallbackRef, 4,
                        makeInt32(info, xpos),
                        makeInt32(info, ypos),
                        makeInt32(info, xoffset),
                        makeInt32(info, yoffset));
    }

    void callOnResizeEnv(const Napi::CallbackInfo& info, int width, int height) {
        INVOKE_CALLBACK(onResizeCallbackRef, 2,
                        makeInt32(info, width),
                        makeInt32(info, height));
    }
};

struct NodeCallback {
    napi_ref receiverRef;
    napi_ref callbackRef;
    const Napi::CallbackInfo& info;

    NodeCallback(const Napi::CallbackInfo& info, napi_value receiver, napi_value callback):
        info(info)
    {
        napi_env env = info.Env();
        NAPI_CALL_VOID(env, napi_create_reference(env, receiver, 1, &receiverRef));
        NAPI_CALL_VOID(env, napi_create_reference(env, callback, 1, &callbackRef));
    }

    ~NodeCallback() {
        napi_env env = info.Env();
        if (!receiverRef) napi_delete_reference(env, receiverRef);
        if (!callbackRef) napi_delete_reference(env, callbackRef);
    }

    napi_value callCallback() {
        if (!callbackRef) {
            return info.Env().Undefined();
        }

        napi_env env = info.Env();
        napi_value callback = nullptr;
        NAPI_CALL(env, napi_get_reference_value(env, callbackRef, &callback), nullptr);
        assert(callback != nullptr);

        napi_value receiver = nullptr;
        NAPI_CALL(env, napi_get_reference_value(env, receiverRef, &receiver), nullptr);
        assert(receiver != nullptr);

        napi_value args[] = {};
        napi_value result = nullptr;
        NAPI_CALL(env, napi_call_function(env, receiver, callback, 0, args, &result), nullptr);
        if (!result) {
            return info.Env().Undefined();
        }
        return result;
    }

    Napi::Env getEnv() {
        return info.Env();
    }
};

#undef REF_CALLBACK
#undef INVOKE_CALLBACK
