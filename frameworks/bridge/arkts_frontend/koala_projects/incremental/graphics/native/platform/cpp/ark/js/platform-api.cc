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

#include "common-interop.h"
#include "common-redrawer.h"

#include "ark-interop.h"
#include "oh_sk_log.h"

#include "platform-api.h"

static napi_ref gPlatformApiRef = nullptr;

Napi::Value Node_skoala_setPlatformAPI(const Napi::CallbackInfo& info) {
    if (static_cast<size_t>(0) >= info.Length()) {
        Napi::Error::New(info.Env(), "No such element")
                .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }
    if (info[0].IsNull()) {
        return info.Env().Undefined();
    }

    napi_value platformApi = (napi_value)info[0];
    napi_create_reference(info.Env(), platformApi, 1, &gPlatformApiRef);

    return info.Env().Undefined();
}
MAKE_INTEROP_NODE_EXPORT(skoala_setPlatformAPI)

Napi::Value Node_skoala_createRedrawerPeer(const Napi::CallbackInfo& info) {
    if (static_cast<size_t>(0) >= info.Length()) {
        Napi::Error::New(info.Env(), "No such element")
                .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }
    if (info[0].IsNull()) {
        return info.Env().Undefined();
    }
    napi_value redrawer = (napi_value)info[0];

    napi_value platformApi = nullptr;
    napi_get_reference_value(info.Env(), gPlatformApiRef, &platformApi);

    auto* peer = reinterpret_cast<RedrawerPeer *>(GetPeerFactory()(reinterpret_cast<void*>(&const_cast<Napi::CallbackInfo&>(info)),
        GetEngine(), platformApi, redrawer, Engine::RuntimeKind::JS));
    Napi::Value result = makePointer(info, peer);
    peer->callOnInitEnv(info);
    return result;
}
MAKE_INTEROP_NODE_EXPORT(skoala_createRedrawerPeer)

Napi::Value Node_skoala_checkEvents(const Napi::CallbackInfo& info) {
    if (static_cast<size_t>(0) >= info.Length()) {
        Napi::Error::New(info.Env(), "No such element")
                .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }
    if (info[0].IsNull()) {
        return info.Env().Undefined();
    }
    RedrawerData* data = reinterpret_cast<RedrawerData*>(getPointer(info, 0));
    return makeBoolean(info, data->peer->checkEvents(data->peer->engine, reinterpret_cast<void*>(&const_cast<Napi::CallbackInfo&>(info))));
}
MAKE_INTEROP_NODE_EXPORT(skoala_checkEvents)

Napi::Value Node_skoala_drawPicture(const Napi::CallbackInfo& info) {
    if (static_cast<size_t>(3) >= info.Length()) {
        Napi::Error::New(info.Env(), "No such element")
                .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    SkPicture* picture = reinterpret_cast<SkPicture*>(getPointer(info, 0));
    RedrawerData* data = reinterpret_cast<RedrawerData*>(getPointer(info, 1));
    Napi::Function completer = Napi::Function(info.Env(), (napi_value)info[2]);
    KBoolean sync = getBoolean(info, 3);

    performDrawOperation(completer, data, picture, sync);

    return info.Env().Undefined();
}
MAKE_INTEROP_NODE_EXPORT(skoala_drawPicture)

void doDisposeCallback(KNativePointer cb) {
    NodeCallback* callback = reinterpret_cast<NodeCallback*>(cb);
    delete callback;
}

napi_value callCallback(KNativePointer cb) {
    NodeCallback* callback = reinterpret_cast<NodeCallback*>(cb);
    return callback->callCallback();
}

Napi::Env getEnv(KNativePointer cb) {
    NodeCallback* callback = reinterpret_cast<NodeCallback*>(cb);
    return callback->getEnv();
}

KBoolean doCallBooleanCallback(KNativePointer cb) {
    napi_value value = callCallback(cb);
    Napi::Env env = getEnv(cb);

    return getBoolean(env, Napi::Value(env, value));
}

KInt doCallIntCallback(KNativePointer cb) {
    napi_value value = callCallback(cb);
    Napi::Env env = getEnv(cb);

    return getInt32(env, Napi::Value(env, value));
}

KNativePointer doCallNativePointerCallback(KNativePointer cb) {
    napi_value value = callCallback(cb);
    Napi::Env env = getEnv(cb);

    return getPointer(env, Napi::Value(env, value));
}

void doCallVoidCallback(KNativePointer cb) {
    callCallback(cb);
}

Napi::Value Node_skoala_registerCallback(const Napi::CallbackInfo& info) {
    static std::once_flag flag;
    std::call_once(flag, []() {
        initCallbacks(
            &doCallBooleanCallback,
            &doCallIntCallback,
            &doCallNativePointerCallback,
            &doCallVoidCallback,
            &doDisposeCallback);
    });

    if (static_cast<size_t>(1) >= info.Length()) {
        Napi::Error::New(info.Env(), "No such element").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    Napi::Value arg0 = info[0];

    if (arg0.IsNull() || arg0.IsUndefined() || !arg0.IsFunction()) {
        Napi::Error::New(info.Env(), "Wrong callback").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    Napi::Value arg1 = info[1];
    if (!arg0.IsObject()) {
        Napi::Error::New(info.Env(), "Not an object").ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }
    NodeCallback* callback = new NodeCallback(info, arg1, arg0);

    return makePointer(info, callback);
}
MAKE_INTEROP_NODE_EXPORT(skoala_registerCallback)

static inline void OnAsyncWorkExecute(napi_env env, void* asyncworker) {}
static inline void OnAsyncWorkComplete(napi_env env,
                                       napi_status status,
                                       void* asyncworker) {
    napi_value platformApi = nullptr;
    napi_value runCallback = nullptr;
    napi_get_reference_value(env, gPlatformApiRef, &platformApi);
    napi_get_named_property(env, platformApi, "run", &runCallback);
    Napi::Function cb = Napi::Function(env, runCallback);
    cb.Call(runCallback, {});
}
static napi_async_work gWork = nullptr;
Napi::Value Node_skoala_enqueue_run(const Napi::CallbackInfo& info) {
    const char* resource_name = "generic";
    napi_env env = info.Env();
    const Napi::Object resource = Napi::Object::New(env);
    napi_value resource_id;
    napi_status status = napi_create_string_latin1(
        env, resource_name, NAPI_AUTO_LENGTH, &resource_id);
    NAPI_THROW_IF_FAILED_VOID(env, status);

    // napi_async_work work;
    if (gWork != nullptr) {
        napi_delete_async_work(env, gWork);
        gWork = nullptr;
    }
    status = napi_create_async_work(env, resource, resource_id, OnAsyncWorkExecute,
                                    OnAsyncWorkComplete, nullptr, &gWork);
    NAPI_THROW_IF_FAILED_VOID(env, status);
    status = napi_queue_async_work(env, gWork);
    NAPI_THROW_IF_FAILED_VOID(env, status);

    return info.Env().Undefined();
}
MAKE_INTEROP_NODE_EXPORT(skoala_enqueue_run)
