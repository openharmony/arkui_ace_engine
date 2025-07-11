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

#include <MacTypes.h>
#include <_types/_uint32_t.h>
#include <_types/_uint8_t.h>
#include <assert.h>
#include <cstdint>

#include "convertors-jsc.h"

// See https://github.com/BabylonJS/BabylonNative/blob/master/Dependencies/napi/napi-direct/source/js_native_api_javascriptcore.cc
// for convertors logic.


KInt* getInt32Elements(JSContextRef context, const JSValueRef arguments) {
    return getTypedElements<KInt>(context, arguments);
}

uint32_t* getUInt32Elements(JSContextRef context, const JSValueRef arguments) {
    return getTypedElements<uint32_t>(context, arguments);
}

float* getFloat32Elements(JSContextRef context, const JSValueRef arguments) {
    return getTypedElements<float>(context, arguments);
}

KByte* getByteElements(JSContextRef context, const JSValueRef arguments) {
    return getTypedElements<KByte>(context, arguments);
}

KStringArray getKStringArray(JSContextRef context, const JSValueRef arguments) {
    return getTypedElements<uint8_t>(context, arguments);
}

KUShort* getUShortElements(JSContextRef context, const JSValueRef arguments) {
    return getTypedElements<KUShort>(context, arguments);
}

KShort* getShortElements(JSContextRef context, const JSValueRef arguments) {
    return getTypedElements<KShort>(context, arguments);
}

int32_t getInt32(JSContextRef context, JSValueRef value) {
    JSValueRef exception {};
    if (JSValueIsNull(context, value)) {
        return 0;
    }
    if (JSValueIsUndefined(context, value)) {
        assert(false);
        return 0;
    }
    double result = JSValueToNumber(context, value, &exception);
    return static_cast<int32_t>(result);
}

uint32_t getUInt32(JSContextRef context, JSValueRef value) {
    JSValueRef exception {};
    if (JSValueIsNull(context, value)) {
        return 0;
    }
    if (JSValueIsUndefined(context, value)) {
        assert(false);
        return 0;
    }
    double result = JSValueToNumber(context, value, &exception);
    return static_cast<uint32_t>(result);
}

uint8_t getUInt8(JSContextRef context, JSValueRef value) {
    JSValueRef exception {};
    if (JSValueIsNull(context, value)) {
        return 0;
    }
    if (JSValueIsUndefined(context, value)) {
        assert(false);
        return 0;
    }
    double result = JSValueToNumber(context, value, &exception);
    return static_cast<uint8_t>(result);
}

/*
static JSStringRef bigintToArrayCastFuncName = JSStringCreateWithUTF8CString("__JSC__castFromBigInt");
static JSStringRef bigintToArrayCastFuncParams[] = { JSStringCreateWithUTF8CString("ptr") };
static JSStringRef bigintToArrayCastFuncBody = JSStringCreateWithUTF8CString(
    "return new Uint32Array([ptr & 0xFFFFFFFFn, (ptr >> 32n) & 0xFFFFFFFFn]);"
);

static JSStringRef arrayToBigintCastFuncName = JSStringCreateWithUTF8CString("__JSC__castToBigInt");
static JSStringRef arrayToBigintCastFuncParams[] = { JSStringCreateWithUTF8CString("ptr") };
static JSStringRef arrayToBigintCastFuncBody = JSStringCreateWithUTF8CString(
    "return BigInt(ptr[1]) << 32n | BigInt(ptr[0])"
);
*/

#ifdef KOALA_JSC_USE_CALLBACK_CAST

static JSStringRef bigIntFromPartsFuncName = JSStringCreateWithUTF8CString("__JSC__bigIntFromParts");
static JSStringRef bigIntFromPartsFuncParams[] = { JSStringCreateWithUTF8CString("hi"), JSStringCreateWithUTF8CString("lo") };
static JSStringRef bigIntFromPartsFuncBody = JSStringCreateWithUTF8CString(
    "return BigInt(hi) << 32n | BigInt(lo);"
);

static JSObjectRef getGlobalCallback(JSContextRef context, JSStringRef name, JSStringRef params[], JSStringRef body) {
    JSObjectRef globalThis = JSContextGetGlobalObject(context);
    JSValueRef propname = JSValueMakeString(context, name);
    JSValueRef castFunc = JSObjectGetPropertyForKey(context, globalThis, propname, nullptr);
    if (JSValueIsUndefined(context, castFunc)) {
        JSObjectRef castFuncObj = JSObjectMakeFunction(context, name, 1, params, body, nullptr, 0, nullptr);
        JSPropertyAttributes attributes = kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontEnum;
        JSObjectSetPropertyForKey(context, globalThis, propname, castFuncObj, attributes, nullptr);
        return castFuncObj;
    }
    return JSValueToObject(context, castFunc, nullptr);
}

static JSObjectRef getBigIntFromParts(JSContextRef context) {
    return getGlobalCallback(context, bigIntFromPartsFuncName, bigIntFromPartsFuncParams, bigIntFromPartsFuncBody);
}

#endif

static JSValueRef u64ToBigInt(JSContextRef context, uint64_t value) {
    JSValueRef bigint;
#ifdef KOALA_JSC_USE_CALLBACK_CAST
    // TODO benchmark this
    JSObjectRef bigIntFromParts = getBigIntFromParts(context);
    JSValueRef parts[2] = {
        JSValueMakeNumber(context, (double) (value >> 32)),
        JSValueMakeNumber(context, (double) (value & 0xFFFFFFFF)),
    };
    bigint = JSObjectCallAsFunction(context, bigIntFromParts, nullptr, 2, parts, nullptr);
#else
    char buffer[128] = {0};
    std::snprintf(buffer, sizeof(buffer) - 1, "%zun", (size_t) value);
    JSStringRef script = JSStringCreateWithUTF8CString(buffer);
    bigint = JSEvaluateScript(context, script, nullptr, nullptr, 0, nullptr);
    JSStringRelease(script);
#endif
    return bigint;
}

static uint64_t bigIntToU64(JSContextRef ctx, JSValueRef value) {
    char buf[128];
    JSStringRef strRef = JSValueToStringCopy(ctx, value, nullptr);
    size_t len = JSStringGetUTF8CString(strRef, buf, sizeof(buf));
    JSStringRelease(strRef);
    assert(len < sizeof(buf));
    char* suf;
    uint64_t numValue = std::strtoull(buf, &suf, 10);
    assert(*suf == '\0');
    return numValue;
}

KNativePointer getPointer(JSContextRef context, JSValueRef value) {
    uint64_t raw = bigIntToU64(context, value);
    return reinterpret_cast<void*>(static_cast<uintptr_t>(raw));
}

KNativePointerArray getPointerElements(JSContextRef context, JSValueRef value) {
    if (JSValueIsNull(context, value) || JSValueIsUndefined(context, value)) {
        return nullptr;
    }

    assert(JSValueIsObject(context, value));
    assert(JSValueGetTypedArrayType(context, value, nullptr) == kJSTypedArrayTypeBigUint64Array);

    JSObjectRef typedArray = JSValueToObject(context, value, nullptr);
    return reinterpret_cast<KNativePointerArray>(JSObjectGetTypedArrayBytesPtr(context, typedArray, nullptr));
}

KFloat getFloat(JSContextRef context, JSValueRef value) {
    JSValueRef exception {};
    if (JSValueIsNull(context, value)) {
        return 0;
    }
    if (JSValueIsUndefined(context, value)) {
        assert(false);
        return 0;
    }
    double result = JSValueToNumber(context, value, &exception);
    return static_cast<KFloat>(result);
}

KShort getShort(JSContextRef context, JSValueRef value) {
    JSValueRef exception {};
    if (JSValueIsNull(context, value)) {
        return 0;
    }
    if (JSValueIsUndefined(context, value)) {
        assert(false);
        return 0;
    }
    double result = JSValueToNumber(context, value, &exception);
    return static_cast<KShort>(result);
}

KUShort getUShort(JSContextRef context, JSValueRef value) {
    JSValueRef exception {};
    if (JSValueIsNull(context, value)) {
        return 0;
    }
    if (JSValueIsUndefined(context, value)) {
        assert(false);
        return 0;
    }
    double result = JSValueToNumber(context, value, &exception);
    return static_cast<KUShort>(result);
}

KStringPtr getString(JSContextRef context, JSValueRef value) {
    if (JSValueIsNull(context, value)) {
        return KStringPtr();
    }
    if (JSValueIsUndefined(context, value)) {
        return KStringPtr();
    }
    KStringPtr result;
    JSStringRef valueString = JSValueToStringCopy(context, value, NULL);
    size_t size = JSStringGetMaximumUTF8CStringSize(valueString);
    result.resize(size);
    JSStringGetUTF8CString(valueString, result.data(), size);
    JSStringRelease(valueString);
    return result;
}

KBoolean getBoolean(JSContextRef context, JSValueRef value) {
    bool result = JSValueToBoolean(context, value);
    return static_cast<KBoolean>(result);
}

JSValueRef makeInt32(JSContextRef context, int32_t value) {
    return JSValueMakeNumber(context, value);
}

JSValueRef makeUInt32(JSContextRef context, uint32_t value) {
    return JSValueMakeNumber(context, value);
}

JSValueRef makePointer(JSContextRef context, KNativePointer value) {
    return u64ToBigInt(context, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(value)));
}

JSValueRef makeFloat(JSContextRef context, KFloat value) {
    return JSValueMakeNumber(context, value);
}

JSValueRef makeBoolean(JSContextRef context, KBoolean value) {
    return JSValueMakeBoolean(context, value);
}

JSValueRef makeVoid(JSContextRef context) {
    return JSValueMakeUndefined(context);
}

Exports* Exports::getInstance() {
  static Exports *instance = nullptr;
  if (instance == nullptr) {
      instance = new Exports();
  }
  return instance;
}

void InitExports(JSGlobalContextRef globalContext) {
    JSObjectRef globalObject = JSContextGetGlobalObject(globalContext);
    for (auto impl: Exports::getInstance()->getImpls()) {
        JSStringRef functionName = JSStringCreateWithUTF8CString(impl.first.c_str());
        JSObjectRef functionObject = JSObjectMakeFunctionWithCallback(globalContext, functionName, impl.second);
        JSObjectSetProperty(globalContext, globalObject, functionName, functionObject, kJSPropertyAttributeNone, nullptr);
        JSStringRelease(functionName);
    }
}
