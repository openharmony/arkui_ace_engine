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

#include <stdio.h>
#include <assert.h>

#include "skoala.h"
#include "common-redrawer.h"

#include "skoala-interop.h"
#include "node-interop.h"

#ifdef SK_BUILD_FOR_WIN
#include <windows.h>
#endif

static peerFactory_t peerFactory = nullptr;
static void* peerFactoryArg = nullptr;
static bool isPlatformApiSet = false;

// void impl_skoala_setPlatformAPI(Napi::Object apiObject) {
napi_value Node_skoala_setPlatformAPI(napi_env env, napi_callback_info cbinfo) {
    napi_value result = makeVoid(env);
    if (isPlatformApiSet) return result;
    isPlatformApiSet = true;
#ifndef SK_BUILD_FOR_ANDROID
    CallbackInfo info(env, cbinfo);
    Napi::Object apiObject(env, info[0]);
    if (apiObject.IsNull()) {
        return result;
    }
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    auto nodeState = new NodeScopedState(isolate, isolate->GetCurrentContext());
    // TODO: move to NAPI types!
    v8::Local<v8::Value> api = V8LocalValueFromJsValue((napi_value)apiObject);
    nodeState->initPlatform(api.As<v8::Object>());

    extern peerFactory_t getSystemPeerFactory(NodeScopedState * nodeState);
    extern void* getSystemPeerFactoryArg();

    peerFactory = getSystemPeerFactory(nodeState);
    peerFactoryArg = getSystemPeerFactoryArg();
#endif
    return result;
}
MAKE_INTEROP_NODE_EXPORT(skoala_setPlatformAPI)

// KNativePointer impl_skoala_createRedrawerPeer(Napi::Object redrawerObject) {
napi_value Node_skoala_createRedrawerPeer(napi_env env, napi_callback_info cbinfo) {
    CallbackInfo info(env, cbinfo);
    Napi::Object redrawerObject(env, info[0]);
    // TODO: implement release of peer.
    RedrawerPeer* peer = nullptr;
    assert(peerFactory != nullptr);
    // TODO: move to NAPI types!
    v8::Local<v8::Value> redrawer = V8LocalValueFromJsValue((napi_value)redrawerObject);
    peer = peerFactory(peerFactoryArg, redrawer.As<v8::Object>());
    if (peer->version != KOALA_CURRENT_VERSION) {
        fprintf(stderr, "version mismatch: %d=%d\n", KOALA_CURRENT_VERSION, peer->version);
        assert(false);
    }
    peer->callOnInit();

    return makePointer(env, peer);
}
MAKE_INTEROP_NODE_EXPORT(skoala_createRedrawerPeer)

void impl_skoala_providePeerFactory(KNativePointer peerFactoryPtr, KNativePointer peerFactoryArgPtr) {
    peerFactory = reinterpret_cast<RedrawerPeer* (*)(void*, v8::Local<v8::Object>)>(peerFactoryPtr);
    peerFactoryArg = peerFactoryArgPtr;
}
KOALA_INTEROP_V2(skoala_providePeerFactory, KNativePointer, KNativePointer)

void doDisposeCallback(KNativePointer cb) {
    NodeCallback* callback = reinterpret_cast<NodeCallback*>(cb);
    delete callback;
}

v8::Local<v8::Value> callCallback(KNativePointer cb) {
    NodeCallback* callback = reinterpret_cast<NodeCallback*>(cb);
    return callback->callCallback();
}

KBoolean doCallBooleanCallback(KNativePointer cb) {
    v8::Local<v8::Value> result = callCallback(cb);
    assert(result->IsBoolean());
    return result.As<v8::Boolean>()->Value();
}

KInt doCallIntCallback(KNativePointer cb) {
    v8::Local<v8::Value> result = callCallback(cb);
    assert(result->IsInt32());
    return result.As<v8::Int32>()->Value();
}

KNativePointer doCallNativePointerCallback(KNativePointer cb) {
    v8::Local<v8::Value> result = callCallback(cb);
    assert(result->IsBigInt());
    // Keep in sync with NAPI version.
    uint64_t raw = result.As<v8::BigInt>()->Uint64Value();
    return reinterpret_cast<void*>(static_cast<uintptr_t>(raw));
}

void doCallVoidCallback(KNativePointer cb) {
    callCallback(cb);
}

napi_value Node_skoala_registerCallback(napi_env env, napi_callback_info cbinfo) {
    Napi::CallbackInfo info(env, cbinfo);
    static std::once_flag flag;
    std::call_once(flag, []() {
        initCallbacks(
            &doCallBooleanCallback,
            &doCallIntCallback,
            &doCallNativePointerCallback,
            &doCallVoidCallback,
            &doDisposeCallback);
    });

    if (2 != info.Length()) {
        Napi::Error::New(info.Env(), "No such element")
            .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }
    Napi::Value arg0 = info[0];
    if (arg0.IsNull()) {
        return info.Env().Undefined();
    }
    if (arg0.IsUndefined()) {
        Napi::Error::New(info.Env(), "`undefined` passed as callback")
            .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    if (!arg0.IsFunction()) {
        Napi::Error::New(info.Env(), "`not a function` passed as callback")
            .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    Napi::Value arg1 = info[1];
    if (!arg1.IsNull() && !arg1.IsObject()) {
        Napi::Error::New(info.Env(), "`not an object or null` passed as callback receiver")
            .ThrowAsJavaScriptException();
        return info.Env().Undefined();
    }

    v8::Local<v8::Value> cb = V8LocalValueFromJsValue((napi_value)arg0);
    v8::Local<v8::Value> receiver = V8LocalValueFromJsValue((napi_value)arg1);

    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    NodeCallback* callback = new NodeCallback(isolate, isolate->GetCurrentContext(),
                                              receiver.As<v8::Object>(), cb.As<v8::Function>());

    return makePointer(env, callback);
}
MAKE_INTEROP_NODE_EXPORT(skoala_registerCallback)

KNativePointer impl_skoala_initRedrawer(KFloat scale, KNativePointer peerPtr, KNativePointer framePtr) {
    auto peer = ptr<RedrawerPeer>(peerPtr);
    auto data = sk_sp<RedrawerData>(new RedrawerData(scale, peer, framePtr));
    return data.release();
}
KOALA_INTEROP_3(skoala_initRedrawer, KNativePointer, KFloat, KNativePointer, KNativePointer)

KBoolean impl_skoala_checkEvents(KNativePointer dataPtr) {
    auto data = ptr<RedrawerData>(dataPtr);
    return data->peer->checkEvents(data->peer->engine, data->frame);
}
KOALA_INTEROP_1(skoala_checkEvents, KBoolean, KNativePointer)

napi_value Node_skoala_drawPicture(napi_env env, napi_callback_info cbinfo) {
    CallbackInfo info(env, cbinfo);
    KNativePointer picturePtr = getArgument<KNativePointer>(info, 0);
    KNativePointer dataPtr = getArgument<KNativePointer>(info, 1);
    Napi::Object completerObject(env, info[0]);
    KBoolean sync = getArgument<KBoolean>(info, 3);

    SkPicture* picture = ptr<SkPicture>(picturePtr);
    RedrawerData* data = ptr<RedrawerData>(dataPtr);
    Napi::Function completer = completerObject.As<Napi::Function>();

    performDrawOperation(completer, data, picture, sync);
    return makeVoid(env);
}
MAKE_INTEROP_NODE_EXPORT(skoala_drawPicture)

void impl_skoala_abandonRedrawer(KNativePointer dataPtr) {
    auto data = ptr<RedrawerData>(dataPtr);
    if (data) {
        data->abandon();
        data->unref();
    }
}
KOALA_INTEROP_V1(skoala_abandonRedrawer, KNativePointer)

KNativePointer impl_skoala_getDirectContext(KNativePointer dataPtr) {
    // TODO: fix for Metal!
    auto data = ptr<RedrawerData>(dataPtr);
    return data ? data->hwContext.get() : nullptr;
}
KOALA_INTEROP_1(skoala_getDirectContext, KNativePointer, KNativePointer)

KNativePointer impl_skoala_getNativeWindow(KNativePointer dataPtr) {
    return ptr<RedrawerData>(dataPtr)->frame;
}
KOALA_INTEROP_1(skoala_getNativeWindow, KNativePointer, KNativePointer)

KNativePointer impl_skoala_GetContentRoots() {
    auto* res = new std::vector<KNativePointer>();
#ifdef SK_BUILD_FOR_WIN
    int bufferSize = 256;
    char* drives = new char[bufferSize];
    DWORD ret = ::GetLogicalDriveStringsA(bufferSize, drives);
    while (ret > bufferSize) {
        delete[] drives;
        drives = new char[ret];
        bufferSize = ret;
        ret = ::GetLogicalDriveStringsA(bufferSize, drives);
    }

    char* drivePtr = drives;
    for (int i = 0; i < ret;) {
        res->push_back(nativePtr(new SkString(drivePtr)));

        int sectionSize = strlen(drivePtr) + 1;
        i += sectionSize;
        drivePtr += sectionSize;
    }
    delete[] drives;
#else
    res->push_back(new SkString("/"));
#endif
    return nativePtr(res);
}
KOALA_INTEROP_0(skoala_GetContentRoots, KNativePointer)
