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
    ohosPath = "OhosRawFile://" + ohosPath;
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

void JSSceneView::Create(const JSCallbackInfo& info)
{
    const auto& length = info.Length();
    std::string srcPath("");

    int surfaceData = 0;
    if (length >= 2) { // 2: info size
        surfaceData = info[1]->ToNumber<int32_t>();
    }
    auto surfaceType =
        (surfaceData == 0) ? OHOS::Render3D::SurfaceType::SURFACE_TEXTURE : OHOS::Render3D::SurfaceType::SURFACE_WINDOW;

    if (length >= 1) {
        ParseJsMedia(info[0], srcPath);
    }

    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(info[0], bundleName, moduleName);
    std::string ohosPath("");
    SetOhosPath(srcPath, ohosPath);
    ModelView::GetInstance()->Create(ohosPath, bundleName, moduleName, surfaceType);
}

void JSSceneView::JsCamera(const JSCallbackInfo& info)
{
    // Parse the info object.
    if (info.Length() <= 0 || !info[0]->IsObject()) {
        return;
    }

    AnimationOption animOption = ViewStackModel::GetInstance()->GetImplicitAnimationOption();
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    std::unordered_map<std::string, float> perspect { { "zNear", 0.5f }, { "zFar", 50.0f }, { "yFov", 60.0f } };
    GetModelProperty(jsObj, "perspective", perspect);
    ModelView::GetInstance()->SetCameraFrustum(perspect["zNear"], perspect["zFar"], perspect["yFov"]);
    // cameraSpace
    std::unordered_map<std::string, float> positionAng { { "theta", 0.0f }, { "phi", 0.0f }, { "radius", 4.0f } };
    std::unordered_map<std::string, float> position { { "x", 0.0f }, { "y", 0.0f }, { "z", 4.0f } };
    std::unordered_map<std::string, float> front { { "x", 0.0f }, { "y", 0.0f }, { "z", 0.0f } };
    std::unordered_map<std::string, float> up { { "x", 0.0f }, { "y", 0.0f }, { "z", 0.0f } };
    if (GetModelProperty(jsObj, "cameraSpace", positionAng)) {
        ModelView::GetInstance()->SetCameraPosition(AnimatableFloat(positionAng["theta"], animOption),
            AnimatableFloat(0, animOption), AnimatableFloat(positionAng["phi"], animOption),
            AnimatableFloat(positionAng["radius"], animOption), true);
        return;
    }
    auto itemCameraSpace = jsObj->GetProperty("cameraSpace");
    if (itemCameraSpace->IsObject()) {
        JSRef<JSObject> spaceObj = JSRef<JSObject>::Cast(itemCameraSpace);
        // position
        GetModelProperty(spaceObj, "position", position);
        // front
        GetModelProperty(spaceObj, "front", front);
        // up
        GetModelProperty(spaceObj, "up", up);
    }
    ModelView::GetInstance()->SetCameraPosition(AnimatableFloat(position["x"], animOption),
        AnimatableFloat(position["y"], animOption), AnimatableFloat(position["z"], animOption),
        AnimatableFloat(0.0f, animOption), false);
    Vec3 lookVec(front["x"], front["y"], front["z"]);
    ModelView::GetInstance()->SetCameraLookAt(lookVec);
    Vec3 upVec(up["x"], up["y"], up["z"]);
    ModelView::GetInstance()->SetCameraUp(upVec);
}

void JSSceneView::JsSetTransparent(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsBoolean()) {
        return;
    }

    bool value = info[0]->ToBoolean();
    ModelView::GetInstance()->SetTransparent(value);
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

void JSSceneView::JsLight(const JSCallbackInfo& info)
{
    // Parse the info object.
    if (info.Length() <= 0 || !info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> itemType = jsObj->GetProperty("type");
    JSRef<JSVal> itemIntensity = jsObj->GetProperty("intensity");
    JSRef<JSVal> itemShadow = jsObj->GetProperty("shadow");
    auto type = static_cast<NG::ModelLightType>((itemType->IsNumber()) ? itemType->ToNumber<int32_t>() : 1);
    int intensity = (itemIntensity->IsNumber()) ? itemIntensity->ToNumber<int32_t>() : 10;
    bool shadow = (itemShadow->IsBoolean()) ? itemShadow->ToBoolean() : false;
    JSRef<JSVal> lightColor = jsObj->GetProperty("color");
    Color color(0xffffffff); // red:255, green:255, blue:255
    ParseJsColor(lightColor, color);
    AnimationOption animOption = ViewStackModel::GetInstance()->GetImplicitAnimationOption();
    Vec3 inputColor = Vec3(color.GetRed() / 255.0f, color.GetGreen() / 255.0f, color.GetBlue() / 255.0f, animOption);
    OHOS::Ace::NG::ModelPosition position;
    double maxInvalid = std::numeric_limits<double>::max();
    Quaternion rotation = Quaternion(maxInvalid, maxInvalid, maxInvalid, maxInvalid);
    std::unordered_map<std::string, float> positionAng { { "theta", 0.0f }, { "phi", 0.0f }, { "radius", 4.0f } };
    std::unordered_map<std::string, float> pos { { "x", 0.0f }, { "y", 1.0f }, { "z", 0.0f } };
    std::unordered_map<std::string, float> quat { { "x", 0.0f }, { "y", 1.0f }, { "z", 0.0f }, { "w", 1.0f } };
    if (GetModelProperty(jsObj, "lightSpace", positionAng)) {
        position.Set({ AnimatableFloat(positionAng["theta"], animOption), AnimatableFloat(0.0f, animOption),
                         AnimatableFloat(positionAng["phi"], animOption) },
            AnimatableFloat(positionAng["radius"], animOption), true);
        ModelView::GetInstance()->AddLight(AceType::MakeRefPtr<NG::ModelLight>(
            type, inputColor, AnimatableFloat(intensity, animOption), shadow, position, rotation));
        return;
    }
    auto itemLightSpace = jsObj->GetProperty("lightSpace");
    if (itemLightSpace->IsObject()) {
        JSRef<JSObject> spaceObj = JSRef<JSObject>::Cast(itemLightSpace);
        GetModelProperty(spaceObj, "position", pos);
        position.Set({ AnimatableFloat(pos["x"], animOption), AnimatableFloat(pos["y"], animOption),
                         AnimatableFloat(pos["z"], animOption) },
            AnimatableFloat(0.0f, animOption), false);
        GetModelProperty(spaceObj, "rotation", quat);
        rotation = Quaternion(quat["x"], quat["y"], quat["z"], quat["w"]);
    }
    ModelView::GetInstance()->AddLight(AceType::MakeRefPtr<NG::ModelLight>(
        type, inputColor, AnimatableFloat(intensity, animOption), shadow, position, rotation));
}

void JSSceneView::JsAddCube(const JSCallbackInfo& info)
{
    // Parse the info object.
    if (info.Length() <= 0 || !info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    auto name = jsObj->GetPropertyValue<std::string>("name", "");
    auto width = jsObj->GetPropertyValue<double>("width", 0.0);
    auto height = jsObj->GetPropertyValue<double>("height", 0.0);
    auto depth = jsObj->GetPropertyValue<double>("depth", 0.0);

    OHOS::Render3D::Vec3 position(0.0f, 0.0f, 0.0f);
    if (jsObj->HasProperty("position")) {
        JSRef<JSVal> positionArgs = jsObj->GetProperty("position");
        if (positionArgs->IsObject()) {
            JSRef<JSObject> posObj = JSRef<JSObject>::Cast(positionArgs);
            position.SetX(posObj->GetPropertyValue<double>("x", 0.0));
            position.SetY(posObj->GetPropertyValue<double>("y", 0.0));
            position.SetZ(posObj->GetPropertyValue<double>("z", 0.0));
        }
    }

    ModelView::GetInstance()->AddGeometry(
        std::make_shared<OHOS::Render3D::Cube>(name.c_str(), width, height, depth, position));
}

void JSSceneView::JsAddSphere(const JSCallbackInfo& info)
{
    // Parse the info object.
    if (info.Length() <= 0 || !info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    auto name = jsObj->GetPropertyValue<std::string>("name", "");
    auto radius = jsObj->GetPropertyValue<double>("radius", 0.0);
    auto rings = jsObj->GetPropertyValue<int32_t>("rings", 0);
    auto sectors = jsObj->GetPropertyValue<int32_t>("sectors", 0);

    OHOS::Render3D::Vec3 position(0.0f, 0.0f, 0.0f);
    if (jsObj->HasProperty("position")) {
        JSRef<JSVal> positionArgs = jsObj->GetProperty("position");
        if (positionArgs->IsObject()) {
            JSRef<JSObject> posObj = JSRef<JSObject>::Cast(positionArgs);
            position.SetX(posObj->GetPropertyValue<double>("x", 0.0));
            position.SetY(posObj->GetPropertyValue<double>("y", 0.0));
            position.SetZ(posObj->GetPropertyValue<double>("z", 0.0));
        }
    }

    ModelView::GetInstance()->AddGeometry(
        std::make_shared<OHOS::Render3D::Sphere>(name.c_str(), radius, rings, sectors, position));
}

void JSSceneView::JsAddCone(const JSCallbackInfo& info)
{
    // Parse the info object.
    if (info.Length() <= 0 || !info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    auto name = jsObj->GetPropertyValue<std::string>("name", "");
    auto radius = jsObj->GetPropertyValue<double>("radius", 0.0);
    auto length = jsObj->GetPropertyValue<int32_t>("length", 0);
    auto sectors = jsObj->GetPropertyValue<int32_t>("sectors", 0);

    OHOS::Render3D::Vec3 position(0.0f, 0.0f, 0.0f);
    if (jsObj->HasProperty("position")) {
        JSRef<JSVal> positionArgs = jsObj->GetProperty("position");
        if (positionArgs->IsObject()) {
            JSRef<JSObject> posObj = JSRef<JSObject>::Cast(positionArgs);
            position.SetX(posObj->GetPropertyValue<double>("x", 0.0));
            position.SetY(posObj->GetPropertyValue<double>("y", 0.0));
            position.SetZ(posObj->GetPropertyValue<double>("z", 0.0));
        }
    }

    ModelView::GetInstance()->AddGeometry(
        std::make_shared<OHOS::Render3D::Cone>(name.c_str(), radius, length, sectors, position));
}

void JSSceneView::JsGLTFAnimation(const JSCallbackInfo& info)
{
    // Parse the info object.
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> itemName = jsObj->GetProperty("name");
    std::string name = (itemName->IsString()) ? itemName->ToString() : "";
    JSRef<JSVal> itemState = jsObj->GetProperty("state");
    auto state = (itemState->IsNumber()) ? itemState->ToNumber<int32_t>() : 0;
    JSRef<JSVal> itemRepeat = jsObj->GetProperty("repeatCount");
    auto repeatCount = (itemRepeat->IsNumber()) ? itemRepeat->ToNumber<int32_t>() : -1;
    JSRef<JSVal> itemSpeed = jsObj->GetProperty("speed");
    auto speed = (itemSpeed->IsNumber()) ? itemSpeed->ToNumber<float>() : 1.0f;
    JSRef<JSVal> itemDuration = jsObj->GetProperty("duration");
    auto duration = (itemDuration->IsNumber()) ? itemDuration->ToNumber<float>() : -1.0f;
    JSRef<JSVal> itemReverse = jsObj->GetProperty("reverse");
    auto reverse = (itemReverse->IsBoolean()) ? itemReverse->ToBoolean() : false;

    ModelView::GetInstance()->AddGLTFAnimation(std::make_shared<Render3D::GLTFAnimation>(
        name, static_cast<Render3D::AnimationState>(state), repeatCount, speed, duration, reverse));
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

void JSSceneView::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ModelView::GetInstance()->SetWidth(value);
}

void JSSceneView::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ModelView::GetInstance()->SetHeight(value);
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
    auto bufferOpt = modelView->GetShaderInputBuffer();
    std::shared_ptr<OHOS::Render3D::ShaderInputBuffer> buffer = nullptr;
    if (bufferOpt.has_value() && !bufferOpt.value()) {
        buffer = bufferOpt.value();
    } else {
        buffer = std::make_shared<OHOS::Render3D::ShaderInputBuffer>();
    }

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
    JSClass<JSSceneView>::StaticMethod("camera", &JSSceneView::JsCamera);
    JSClass<JSSceneView>::StaticMethod("transparent", &JSSceneView::JsSetTransparent);
    JSClass<JSSceneView>::StaticMethod("environment", &JSSceneView::JsSetBackground);
    JSClass<JSSceneView>::StaticMethod("light", &JSSceneView::JsLight);
    JSClass<JSSceneView>::StaticMethod("cube", &JSSceneView::JsAddCube);
    JSClass<JSSceneView>::StaticMethod("sphere", &JSSceneView::JsAddSphere);
    JSClass<JSSceneView>::StaticMethod("cone", &JSSceneView::JsAddCone);
    JSClass<JSSceneView>::StaticMethod("modelAnimation", &JSSceneView::JsGLTFAnimation);
    JSClass<JSSceneView>::StaticMethod("customRender", &JSSceneView::JsAddCustomRender);
    JSClass<JSSceneView>::StaticMethod("width", &JSSceneView::JsWidth);
    JSClass<JSSceneView>::StaticMethod("height", &JSSceneView::JsHeight);
    JSClass<JSSceneView>::StaticMethod("shader", &JSSceneView::JsShader);
    JSClass<JSSceneView>::StaticMethod("renderWidth", &JSSceneView::JsRenderWidth);
    JSClass<JSSceneView>::StaticMethod("renderHeight", &JSSceneView::JsRenderHeight);
    JSClass<JSSceneView>::StaticMethod("renderFrameRateHint", &JSSceneView::JsRenderFrameRate);
    JSClass<JSSceneView>::StaticMethod("shaderImageTexture", &JSSceneView::JsShaderImageTexture);
    JSClass<JSSceneView>::StaticMethod("shaderInputBuffer", &JSSceneView::JsShaderInputBuffer);
    JSClass<JSSceneView>::StaticMethod("OnError", &JSSceneView::JsOnError);
    JSClass<JSSceneView>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSceneView>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSceneView>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSceneView>::InheritAndBind<JSViewAbstract>(globalObj);
}

} // namespace OHOS::Ace::Framework
