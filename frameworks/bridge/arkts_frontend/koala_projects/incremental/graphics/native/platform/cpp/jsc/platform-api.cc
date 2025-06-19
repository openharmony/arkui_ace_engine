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

#include <iostream>

#include "skoala.h"
#include "common-redrawer.h"
#include "common-interop.h"
#include "jsc-interop.h"

static peerFactory_t peerFactory = nullptr;
static void* peerFactoryArg = nullptr;


std::string JSStringToStdString(JSStringRef jsString) {
    size_t maxBufferSize = JSStringGetMaximumUTF8CStringSize(jsString);
    char* utf8Buffer = new char[maxBufferSize];
    size_t bytesWritten = JSStringGetUTF8CString(jsString, utf8Buffer, maxBufferSize);
    std::string utf_string = std::string(utf8Buffer, bytesWritten - 1);
    delete[] utf8Buffer;
    return utf_string;
}

JSValueRef Jsc_require(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    for(size_t i = 0; i < argumentCount; i++) {
        JSStringRef pathString = JSValueToStringCopy(ctx, arguments[i], nullptr);
        std::cout << JSStringToStdString(pathString);
    }
    std::cout << std::endl;
    return JSContextGetGlobalObject(ctx);
}
MAKE_JSC_EXPORT_V1(require)

JSValueRef Jsc_isMainThread(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef argument[], JSValueRef* exception) {
    return JSValueMakeNumber(ctx, 1);
}
MAKE_JSC_EXPORT_V1(isMainThread)

/* skoala export*/
JSValueRef Jsc_skoala_setPlatformAPI(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    auto* apiHolder = new JSValueHolder(context, arguments[0]);

    auto* jscState = new JscScopedState(context, thisObject);
    jscState->initPlatform(apiHolder);

    extern peerFactory_t getIosPeerFactory(JscScopedState* jscState);
    extern void* getIosPeerFactoryArg();

    peerFactory = getIosPeerFactory(jscState);
    peerFactoryArg = getIosPeerFactoryArg();

    return JSValueMakeUndefined(context);
}
MAKE_JSC_EXPORT(skoala_setPlatformAPI)

JSValueRef Jsc_skoala_jsc_gc(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef argument[], JSValueRef* exception) {
    JSGarbageCollect(context);
    return JSValueMakeUndefined(context);
}
MAKE_JSC_EXPORT(skoala_jsc_gc)

JSValueRef Jsc_skoala_createRedrawerPeer(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    JSValueHolder redrawerHolder(context, arguments[0]);
    RedrawerPeer* peer = nullptr;

    peer = peerFactory(peerFactoryArg, redrawerHolder.obj());
    peer->callOnInit();

    return makePointer(context, peer);
}
MAKE_JSC_EXPORT(skoala_createRedrawerPeer)

JSValueRef Jsc_skoala_providePeerFactory(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    peerFactory = reinterpret_cast<RedrawerPeer* (*)(void*, JSObjectRef)>(getPointer(context, arguments[0]));
    peerFactoryArg = getPointer(context, arguments[1]);

    return JSValueMakeUndefined(context);
}
MAKE_JSC_EXPORT(skoala_providePeerFactory)

KNativePointer impl_skoala_initRedrawer(KFloat scale, KNativePointer peerPtr, KNativePointer framePtr) {
    auto peer = ptr<RedrawerPeer>(peerPtr);
    auto data = sk_sp<RedrawerData>(new RedrawerData(scale, peer, framePtr));
    return data.release();
}
KOALA_INTEROP_3(skoala_initRedrawer, KNativePointer, KFloat, KNativePointer, KNativePointer)

KBoolean impl_skoala_checkEvents(KNativePointer dataPtr) {
    RedrawerData* data = reinterpret_cast<RedrawerData*>(dataPtr);
    return data->peer->checkEvents(data->peer->engine, data->frame);
}
KOALA_INTEROP_1(skoala_checkEvents, KBoolean, KNativePointer)

JSValueRef Jsc_skoala_drawPicture(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {

    SkPicture* picture = reinterpret_cast<SkPicture*>(getPointer(context, arguments[0]));
    RedrawerData* data = reinterpret_cast<RedrawerData*>(getPointer(context, arguments[1]));
    JSObjectRef completer = JSValueToObject(context, arguments[2], nullptr);
    KBoolean sync = JSValueToBoolean(context, arguments[3]);

    CompleterType* completerArg = new CompleterType(context, completer, thisObject);

    performDrawOperation(completerArg, data, picture, sync);

    return makeVoid(context);
}
MAKE_JSC_EXPORT(skoala_drawPicture)

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