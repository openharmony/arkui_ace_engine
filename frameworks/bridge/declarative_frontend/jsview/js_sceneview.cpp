/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_sceneview.h"

#include <regex>

#include "custom/custom_render_descriptor.h"
#include "custom/shader_input_buffer.h"
#include "data_type/constants.h"
#include "data_type/geometry/cone.h"
#include "data_type/geometry/cube.h"
#include "data_type/geometry/sphere.h"
#include "data_type/light.h"

#include "base/geometry/quaternion.h"
#include "base/geometry/vec3.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/model/model_view_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

#if defined(KIT_3D_ENABLE)
#include "scene_adapter/scene_bridge.h"
#endif

namespace OHOS::Ace {

std::unique_ptr<ModelView> ModelView::instance_ = nullptr;
std::mutex ModelView::mutex_;

ModelView* ModelView::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ModelViewNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ModelViewNG());
            } else {
                LOGW("ModelView::GetInstance() NOT NG Pipeline not support");
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
static const std::regex MODEL_RES_ID_REGEX(R"(^resource://\w+/([0-9]+)\.\w+$)", std::regex::icase);
static const std::regex MODEL_APP_RES_PATH_REGEX(R"(^resource://RAWFILE/(.*)$)");
static const std::regex MODEL_APP_RES_ID_REGEX(R"(^resource://.*/([0-9]+)\.\w+$)", std::regex::icase);
static const std::regex MODEL_RES_NAME_REGEX(R"(^resource://.*/(\w+)\.\w+$)", std::regex::icase);
static constexpr uint32_t MODEL_RESOURCE_MATCH_SIZE = 2;

bool GetResourceId(const std::string& uri, uint32_t& resId)
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MODEL_RES_ID_REGEX) && matches.size() == MODEL_RESOURCE_MATCH_SIZE) {
        resId = static_cast<uint32_t>(std::stoul(matches[1].str()));
        return true;
    }

    std::smatch appMatches;
    if (std::regex_match(uri, appMatches, MODEL_APP_RES_ID_REGEX) && appMatches.size() == MODEL_RESOURCE_MATCH_SIZE) {
        resId = static_cast<uint32_t>(std::stoul(appMatches[1].str()));
        return true;
    }
    return false;
}

bool GetResourceId(const std::string& uri, std::string& path)
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MODEL_APP_RES_PATH_REGEX) && matches.size() == MODEL_RESOURCE_MATCH_SIZE) {
        path = matches[1].str();
        return true;
    }
    return false;
}

bool GetResourceName(const std::string& uri, std::string& resName)
{
    std::smatch matches;
    if (std::regex_match(uri, matches, MODEL_RES_NAME_REGEX) && matches.size() == MODEL_RESOURCE_MATCH_SIZE) {
        resName = matches[1].str();
        return true;
    }
    return false;
}

bool SetOhosPath(const std::string& uri, std::string& ohosPath)
{
    if (GetResourceId(uri, ohosPath)) {
        ohosPath = "OhosRawFile://" + ohosPath;
        return true;
    }

    uint32_t resId = 0;
    if (GetResourceId(uri, resId)) {
        ohosPath = "OhosRawFile://" + std::to_string(resId);
        return true;
    }

    if (GetResourceName(uri, ohosPath)) {
        ohosPath = "OhosRawFile://" + ohosPath;
        return true;
    }
    // set default format as system resource
    ohosPath = "file://" + uri;
    return false;
}

// get Number data
template<typename T>
bool GetModelProperty(
    const JSRef<JSObject>& jsValue, const std::string& propertyName, std::unordered_map<std::string, T>& propertyData)
{
    auto item = jsValue->GetProperty(propertyName.c_str());
    if (item->IsObject()) {
        JSRef<JSObject> itemObj = JSRef<JSObject>::Cast(item);
        for (auto iter = propertyData.begin(); iter != propertyData.end(); ++iter) {
            JSRef<JSVal> itemData = itemObj->GetProperty((iter->first).c_str());
            if (itemData->IsNumber()) {
                iter->second = itemData->ToNumber<T>();
                continue;
            }
            if (itemData->IsBoolean()) {
                iter->second = itemData->ToBoolean();
                continue;
            }
            return false;
        }
        return true;
    }
    return false;
}

void JSSceneView::JsSetHandleCameraMove(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsBoolean()) {
        return;
    }

    bool value = info[0]->ToBoolean();
    ModelView::GetInstance()->SetHandleCameraMove(value);
}

#if defined(KIT_3D_ENABLE)
std::shared_ptr<Render3D::ISceneAdapter> UnwrapScene(JSRef<JSVal> obj)
{
#if defined(USE_ARK_ENGINE) && !defined(PREVIEW)
    if (!obj->IsObject()) {
        return nullptr;
    }

    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!runtime) {
        return nullptr;
    }

    auto nativeEngine = runtime->GetNativeEngine();
    if (nativeEngine == nullptr) {
        return nullptr;
    }

    panda::Local<JsiValue> value = obj.Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;

    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    napi_value napiValue = nativeEngine->ValueToNapiValue(valueWrapper);

    auto ret = Render3D::SceneBridge::UnwrapSceneFromJs(env, napiValue);
    napi_close_handle_scope(env, scope);
    return ret;
#else
    return nullptr;
#endif
}

bool ParseSceneOpt(const JSCallbackInfo& info, std::string& srcPath, std::shared_ptr<Render3D::ISceneAdapter>& scene,
    int& surfaceData, std::string& bundleName, std::string& moduleName)
{
    if (JSViewAbstract::ParseJsMedia(info[0], srcPath)) {
        return false;
    }

    if (!info[0]->IsObject()) {
        return false;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    auto type = jsObj->GetProperty("modelType");
    if (!type->IsNull()) {
        surfaceData = type->ToNumber<int32_t>();
    }

    // SceneOptings
    auto sceneOpt = jsObj->GetProperty("scene");
    if (!sceneOpt->IsObject()) {
        return false;
    }

    JSRef<JSObject> jsObjScene = JSRef<JSObject>::Cast(sceneOpt);
    scene = UnwrapScene(jsObjScene);
    if (scene == nullptr) {
        JSViewAbstract::ParseJsMedia(sceneOpt, srcPath);
        JSViewAbstract::GetJsMediaBundleInfo(sceneOpt, bundleName, moduleName);
        return false;
    }

    // Scene new api
    auto prop = jsObjScene->GetProperty("uri");
    if (!prop->IsNull()) {
        scene = UnwrapScene(jsObjScene);
    }
    return true;
}
#endif

void JSSceneView::Create(const JSCallbackInfo& info)
{
    const auto& length = info.Length();
    std::string srcPath("");
    int surfaceData = 0;
    std::string bundleName;
    std::string moduleName;

    Render3D::SurfaceType surfaceType = OHOS::Render3D::SurfaceType::SURFACE_TEXTURE;
#if defined(KIT_3D_ENABLE)
    std::shared_ptr<Render3D::ISceneAdapter> scene = nullptr;
    bool isSceneApi = false;
#endif
    if (length == 2) { // 2: info size
        if (info[1]->IsNumber()) {
            surfaceData = info[1]->ToNumber<int32_t>();
        }
        ParseJsMedia(info[0], srcPath);
        GetJsMediaBundleInfo(info[0], bundleName, moduleName);
    } else if (length == 1) {
#if defined(KIT_3D_ENABLE)
        isSceneApi = ParseSceneOpt(info, srcPath, scene, surfaceData, bundleName, moduleName);
#else
        if (!ParseJsMedia(info[0], srcPath)) {
            // SceneOptions
            JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
            auto scene = jsObj->GetProperty("scene");
            if (!scene->IsNull()) {
                ParseJsMedia(scene, srcPath);
                GetJsMediaBundleInfo(scene, bundleName, moduleName);
            }
            auto type = jsObj->GetProperty("modelType");
            if (!type->IsNull()) {
                surfaceData = type->ToNumber<int32_t>();
            }
        }
#endif
    }

    surfaceType = (surfaceData == 0) ? OHOS::Render3D::SurfaceType::SURFACE_TEXTURE :
        OHOS::Render3D::SurfaceType::SURFACE_WINDOW;

    std::string ohosPath("");
    SetOhosPath(srcPath, ohosPath);
    LOGD("srcPath after ParseJsMedia(): %s bundleName: %s, moduleName %s", ohosPath.c_str(),
        bundleName.c_str(), moduleName.c_str());
#if defined(KIT_3D_ENABLE)
    ModelView::GetInstance()->Create({ bundleName, moduleName, surfaceType, scene });
#else
    ModelView::GetInstance()->Create({ bundleName, moduleName, surfaceType });
#endif
    ModelView::GetInstance()->SetModelSource(ohosPath);
}

void JSSceneView::JsSetBackground(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    std::string srcPath;
    auto parseOk = ParseJsMedia(info[0], srcPath);
    if (!parseOk) {
        return;
    }
    std::string ohosPath("");
    SetOhosPath(srcPath, ohosPath);
    ModelView::GetInstance()->SetBackground(ohosPath);
}

void JSSceneView::JsAddCustomRender(const JSCallbackInfo& info)
{
    if (info.Length() != 2) {
        return;
    }

    if (info[1]->IsNull() || !info[1]->IsBoolean()) {
        return;
    }

    std::string uri;
    auto parseOk = ParseJsMedia(info[0], uri);
    if (!parseOk) {
        return;
    }

    std::string ohosPath("");
    SetOhosPath(uri, ohosPath);
    auto desc = std::make_shared<Render3D::CustomRenderDescriptor>(ohosPath, info[1]->ToBoolean());
    ModelView::GetInstance()->AddCustomRender(desc);
}

void JSSceneView::JsRenderWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value.SetValue(1.0f);
        return;
    }

    if (info[0]->IsNumber() || info[0]->IsObject()) {
        value.SetValue(1.0f);
    }

    if (LessNotEqual(value.Value(), 0.0f)) {
        value.SetValue(0.0f);
    }
    ModelView::GetInstance()->SetRenderWidth(value);
}

void JSSceneView::JsRenderHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        LOGE("invalid args for render height");
        value.SetValue(1.0f);
        return;
    }

    if (info[0]->IsNumber() || info[0]->IsObject()) {
        value.SetValue(1.0f);
    }

    if (LessNotEqual(value.Value(), 0.0f)) {
        value.SetValue(0.0f);
    }
    ModelView::GetInstance()->SetRenderHeight(value);
}

void JSSceneView::JsRenderFrameRate(const JSCallbackInfo& info) {}

void JSSceneView::JsShader(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        return;
    }

    std::string shaderPath;
    auto parseOk = ParseJsMedia(info[0], shaderPath);
    if (!parseOk) {
        return;
    }

    std::string ohosPath("");
    SetOhosPath(shaderPath, ohosPath);
    ModelView::GetInstance()->SetShader(ohosPath);
}

void JSSceneView::JsShaderImageTexture(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        return;
    }

    std::string texturePath;
    auto parseOk = ParseJsMedia(info[0], texturePath);
    if (!parseOk) {
        return;
    }

    std::string ohosPath("");
    SetOhosPath(texturePath, ohosPath);
    ModelView::GetInstance()->AddShaderImageTexture(ohosPath);
}

void JSSceneView::JsShaderInputBuffer(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsArray()) {
        return;
    }

    JSRef<JSArray> array = JSRef<JSArray>::Cast(info[0]);
    int32_t length = static_cast<int32_t>(array->Length());
    if (length <= 0) {
        return;
    }

    auto modelView = ModelView::GetInstance();
    std::shared_ptr<OHOS::Render3D::ShaderInputBuffer> buffer = nullptr;

    // same shader input buffer would be rejected to update for nearEqual check
    buffer = std::make_shared<OHOS::Render3D::ShaderInputBuffer>();
    if (!buffer->Alloc(length)) {
        return;
    }

    for (uint32_t i = 0; i < static_cast<uint32_t>(length); i++) {
        JSRef<JSVal> jsValue = array->GetValueAt(i);
        if (jsValue->IsNumber()) {
            buffer->Update(jsValue->ToNumber<float>(), i);
        } else {
            return;
        }
    }

    modelView->AddShaderInputBuffer(buffer);
}

void JSSceneView::JsOnError(const JSCallbackInfo& info) {}

void JSSceneView::JSBind(BindingTarget globalObj)
{
    JSClass<JSSceneView>::Declare("Component3D");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSceneView>::StaticMethod("create", &JSSceneView::Create, opt);
    JSClass<JSSceneView>::StaticMethod("gestureAccess", &JSSceneView::JsSetHandleCameraMove);
    JSClass<JSSceneView>::StaticMethod("environment", &JSSceneView::JsSetBackground);
    JSClass<JSSceneView>::StaticMethod("customRender", &JSSceneView::JsAddCustomRender);
    JSClass<JSSceneView>::StaticMethod("shader", &JSSceneView::JsShader);
    JSClass<JSSceneView>::StaticMethod("renderWidth", &JSSceneView::JsRenderWidth);
    JSClass<JSSceneView>::StaticMethod("renderHeight", &JSSceneView::JsRenderHeight);
    JSClass<JSSceneView>::StaticMethod("renderFrameRateHint", &JSSceneView::JsRenderFrameRate);
    JSClass<JSSceneView>::StaticMethod("shaderImageTexture", &JSSceneView::JsShaderImageTexture);
    JSClass<JSSceneView>::StaticMethod("shaderInputBuffer", &JSSceneView::JsShaderInputBuffer);
    JSClass<JSSceneView>::StaticMethod("OnError", &JSSceneView::JsOnError);
    JSClass<JSSceneView>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSSceneView>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSceneView>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSSceneView>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSceneView>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSceneView>::InheritAndBind<JSViewAbstract>(globalObj);
}

} // namespace OHOS::Ace::Framework
