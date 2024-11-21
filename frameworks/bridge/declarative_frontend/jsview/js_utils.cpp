/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bridge/declarative_frontend/jsview/js_utils.h"

#include "scope_manager/native_scope_manager.h"
#include "base/image/drawing_lattice.h"

#if !defined(PREVIEW)
#include <dlfcn.h>
#endif
#if !defined(WINDOWS_PLATFORM)
#include <regex.h>
#endif

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#include "pixel_map_napi.h"
#endif
#include "napi/native_node_api.h"

#include "base/image/pixel_map.h"
#include "base/log/ace_trace.h"
#include "base/want/want_wrap.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Framework {
namespace {
#if defined(WINDOWS_PLATFORM)
constexpr char CHECK_REGEX_VALID[] = "__checkRegexValid__";
#endif
} // namespace

namespace {
void* UnwrapNapiValue(const JSRef<JSVal>& obj)
{
#ifdef ENABLE_ROSEN_BACKEND
    if (!obj->IsObject()) {
        LOGE("info[0] is not an object when try CreateFromNapiValue");
        return nullptr;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    auto nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);
#ifdef USE_ARK_ENGINE
    panda::Local<JsiValue> value = obj.Get().GetLocalHandle();
#endif
    JSValueWrapper valueWrapper = value;

    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value napiValue = nativeEngine->ValueToNapiValue(valueWrapper);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, napiValue, &valueType);
    if (valueType != napi_object) {
        LOGE("napiValue is not napi_object");
        return nullptr;
    }
    void* objectNapi = nullptr;
    napi_unwrap(env, napiValue, &objectNapi);
    return objectNapi;
#else
    return nullptr;
#endif
}
} // namespace

#if !defined(PREVIEW)
RefPtr<PixelMap> CreatePixelMapFromNapiValue(const JSRef<JSVal>& obj, NativeEngine* localNativeEngine)
{
    if (!obj->IsObject()) {
        return nullptr;
    }
    NativeEngine* nativeEngine = nullptr;
    if (localNativeEngine != nullptr) {
        nativeEngine = localNativeEngine;
    } else {
        auto engine = EngineHelper::GetCurrentEngineSafely();
        if (!engine) {
            return nullptr;
        }
        nativeEngine = engine->GetNativeEngine();
    }
    if (nativeEngine == nullptr) {
        return nullptr;
    }
#ifdef USE_ARK_ENGINE
    panda::Local<JsiValue> value = obj.Get().GetLocalHandle();
#endif
    JSValueWrapper valueWrapper = value;

    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value napiValue = nativeEngine->ValueToNapiValue(valueWrapper);

    PixelMapNapiEntry pixelMapNapiEntry = JsEngine::GetPixelMapNapiEntry();
    if (!pixelMapNapiEntry) {
        return nullptr;
    }

    void* pixmapPtrAddr = pixelMapNapiEntry(reinterpret_cast<napi_env>(nativeEngine), napiValue);
    if (pixmapPtrAddr == nullptr) {
        return nullptr;
    }
    return PixelMap::CreatePixelMap(pixmapPtrAddr);
}

bool GetPixelMapListFromAnimatedDrawable(JSRef<JSVal> obj, std::vector<RefPtr<PixelMap>>& pixelMaps,
    int32_t& duration, int32_t& iterations)
{
    return PixelMap::GetPxielMapListFromAnimatedDrawable(UnwrapNapiValue(obj), pixelMaps, duration, iterations);
}

RefPtr<PixelMap> GetDrawablePixmap(JSRef<JSVal> obj)
{
    return PixelMap::GetFromDrawable(UnwrapNapiValue(obj));
}

const std::shared_ptr<Rosen::RSNode> CreateRSNodeFromNapiValue(JSRef<JSVal> obj)
{
    auto nodePtr = static_cast<std::shared_ptr<Rosen::RSNode>*>(UnwrapNapiValue(obj));
    if (nodePtr == nullptr) {
        return nullptr;
    }
    return *nodePtr;
}

RefPtr<OHOS::Ace::WantWrap> CreateWantWrapFromNapiValue(JSRef<JSVal> obj)
{
    if (!obj->IsObject()) {
        LOGE("invalid object when try CreateWantWrapFromNapiValue");
        return nullptr;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);

    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);

#ifdef USE_ARK_ENGINE
    panda::Local<JsiValue> value = obj.Get().GetLocalHandle();
#endif
    JSValueWrapper valueWrapper = value;
    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);
    return WantWrap::CreateWantWrap(reinterpret_cast<napi_env>(nativeEngine), nativeValue);
}
#endif

const Rosen::VisualEffect* CreateRSEffectFromNapiValue(JSRef<JSVal> obj)
{
    auto visualEffectPtr = static_cast<Rosen::VisualEffect*>(UnwrapNapiValue(obj));
    return visualEffectPtr;
}

const Rosen::Filter* CreateRSFilterFromNapiValue(JSRef<JSVal> obj)
{
    auto filterPtr = static_cast<Rosen::Filter*>(UnwrapNapiValue(obj));
    return filterPtr;
}

const Rosen::BrightnessBlender* CreateRSBrightnessBlenderFromNapiValue(JSRef<JSVal> obj)
{
    auto blenderPtr = static_cast<Rosen::BrightnessBlender*>(UnwrapNapiValue(obj));
    return blenderPtr;
}

RefPtr<DrawingColorFilter> CreateDrawingColorFilter(JSRef<JSVal> obj)
{
    return DrawingColorFilter::CreateDrawingColorFilter(UnwrapNapiValue(obj));
}

RefPtr<DrawingLattice> CreateDrawingLattice(JSRef<JSVal> obj)
{
    return DrawingLattice::CreateDrawingLattice(UnwrapNapiValue(obj));
}

std::optional<NG::BorderRadiusProperty> HandleDifferentRadius(JsiRef<JSVal> args)
{
    std::optional<NG::BorderRadiusProperty> prop = std::nullopt;
    if (!args->IsObject()) {
        return prop;
    }

    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;
    JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
    CalcDimension topLeft;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("topLeft"), topLeft)) {
        radiusTopLeft = topLeft;
    }
    CalcDimension topRight;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("topRight"), topRight)) {
        radiusTopRight = topRight;
    }
    CalcDimension bottomLeft;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("bottomLeft"), bottomLeft)) {
        radiusBottomLeft = bottomLeft;
    }
    CalcDimension bottomRight;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("bottomRight"), bottomRight)) {
        radiusBottomRight = bottomRight;
    }
    if (!radiusTopLeft.has_value() && !radiusTopRight.has_value() && !radiusBottomLeft.has_value() &&
        !radiusBottomRight.has_value()) {
        return prop;
    }
    NG::BorderRadiusProperty borderRadius;
    if (radiusTopLeft.has_value()) {
        borderRadius.radiusTopLeft = radiusTopLeft;
    }
    if (radiusTopRight.has_value()) {
        borderRadius.radiusTopRight = radiusTopRight;
    }
    if (radiusBottomLeft.has_value()) {
        borderRadius.radiusBottomLeft = radiusBottomLeft;
    }
    if (radiusBottomRight.has_value()) {
        borderRadius.radiusBottomRight = radiusBottomRight;
    }
    borderRadius.multiValued = true;
    prop = borderRadius;

    return prop;
}

std::optional<NG::BorderRadiusProperty> ParseBorderRadiusAttr(JsiRef<JSVal> args)
{
    std::optional<NG::BorderRadiusProperty> prop = std::nullopt;
    CalcDimension radiusDim;
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return prop;
    }
    if (JSViewAbstract::ParseJsDimensionVpNG(args, radiusDim)) {
        NG::BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(radiusDim);
        borderRadius.multiValued = false;
        prop = borderRadius;
    } else if (args->IsObject()) {
        prop = HandleDifferentRadius(args);
    }
    return prop;
}

// When the api version >= 11, it is disable event version.
bool IsDisableEventVersion()
{
    return Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN);
}

void ParseTextShadowFromShadowObject(const JSRef<JSVal>& shadowObject, std::vector<Shadow>& shadows)
{
    if (!shadowObject->IsNumber() && !shadowObject->IsObject() && !shadowObject->IsArray()) {
        return;
    }
    if (!shadowObject->IsArray()) {
        Shadow shadow;
        if (!JSViewAbstract::ParseShadowProps(shadowObject, shadow)) {
            return;
        }
        shadows.push_back(shadow);
        return;
    }
    JSRef<JSArray> params = JSRef<JSArray>::Cast(shadowObject);
    auto shadowLength = params->Length();
    for (size_t i = 0; i < shadowLength; ++i) {
        auto shadowJsVal = params->GetValueAt(i);
        Shadow shadow;
        if (!JSViewAbstract::ParseShadowProps(shadowJsVal, shadow)) {
            continue;
        }
        shadows.push_back(shadow);
    }
}

#ifdef PIXEL_MAP_SUPPORTED
JSRef<JSVal> ConvertPixmap(const RefPtr<PixelMap>& pixelMap)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, {});
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto* env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelMap->GetPixelMapSharedPtr());
    return JsConverter::ConvertNapiValueToJsVal(napiValue);
}
#endif

#ifdef PIXEL_MAP_SUPPORTED
napi_value ConvertPixmapNapi(const RefPtr<PixelMap>& pixelMap)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, {});
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto* env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelMap->GetPixelMapSharedPtr());
    return napiValue;
}
#endif

bool IsDrawable(const JSRef<JSVal>& jsValue)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    if (jsObj->IsUndefined()) {
        return false;
    }

    // if jsObject has function getPixelMap, it's a DrawableDescriptor object
    JSRef<JSVal> func = jsObj->GetProperty("getPixelMap");
    return (!func->IsNull() && func->IsFunction());
}

bool CheckRegexValid(const std::string& pattern)
{
#if !defined(WINDOWS_PLATFORM)
    regex_t regex;
    // compile regex
    const char* patternPtr = pattern.c_str();
    int32_t ret = regcomp(&regex, patternPtr, REG_EXTENDED);
    if (ret != 0) {
        regfree(&regex);
        return false;
    }
    regfree(&regex);
    return true;
#else
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, false);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, false);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value global;
    napi_status ret = napi_get_global(env, &global);
    if (ret != napi_ok) {
        return false;
    }
    napi_value checkRegexValid;
    ret = napi_get_named_property(env, global, CHECK_REGEX_VALID, &checkRegexValid);
    if (ret != napi_ok) {
        return false;
    }
    // create napi string
    napi_value argv[1];
    napi_create_string_utf8(env, pattern.c_str(), pattern.length(), &argv[0]);
    napi_value result;
    napi_call_function(env, nullptr, checkRegexValid, 1, argv, &result);
    bool isValid = false;
    napi_get_value_bool(env, result, &isValid);
    return isValid;
#endif
}

napi_env GetCurrentEnv()
{
    auto engine = EngineHelper::GetCurrentEngine();
    if (!engine) {
        return nullptr;
    }
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    if (!nativeEngine) {
        return nullptr;
    }
    return reinterpret_cast<napi_env>(nativeEngine);
}
} // namespace OHOS::Ace::Framework
