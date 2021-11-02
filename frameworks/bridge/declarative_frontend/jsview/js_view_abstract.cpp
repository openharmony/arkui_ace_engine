/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

#include <algorithm>
#include <regex>
#include <vector>

#include "base/json/json_util.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/functions/js_focus_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"

#ifdef USE_V8_ENGINE
#include "bridge/declarative_frontend/engine/v8/functions/v8_function.h"
#endif

#include "bridge/declarative_frontend/jsview/js_grid_container.h"
#include "bridge/declarative_frontend/jsview/js_view_register.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/ace_application_info.h"
#include "core/components/common/layout/align_declaration.h"
#include "core/components/common/properties/motion_path_option.h"
#include "core/components/menu/menu_component.h"
#include "core/components/option/option_component.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "frameworks/core/components/text/text_component.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr int32_t MAX_ALIGN_VALUE = 8;
constexpr double EPSILON = 0.000002f;
const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);

void ParseJsScale(std::unique_ptr<JsonValue>& argsPtrItem, float& scaleX, float& scaleY, float& scaleZ,
    Dimension& centerX, Dimension& centerY)
{
    double xVal = 1.0;
    double yVal = 1.0;
    double zVal = 1.0;
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("x"), xVal);
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("y"), yVal);
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("z"), zVal);
    scaleX = static_cast<float>(xVal);
    scaleY = static_cast<float>(yVal);
    scaleZ = static_cast<float>(zVal);
    // if specify centerX
    Dimension length;
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("centerX"), length)) {
        centerX = length;
    }
    // if specify centerY
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("centerY"), length)) {
        centerY = length;
    }
}

void ParseJsTranslate(
    std::unique_ptr<JsonValue>& argsPtrItem, Dimension& translateX, Dimension& translateY, Dimension& translateZ)
{
    Dimension length;
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("x"), length)) {
        translateX = length;
    }
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("y"), length)) {
        translateY = length;
    }
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("z"), length)) {
        translateZ = length;
    }
}

void ParseJsRotate(std::unique_ptr<JsonValue>& argsPtrItem, float& dx, float& dy, float& dz, Dimension& centerX,
    Dimension& centerY, std::optional<float>& angle)
{
    // default: dx, dy, dz (0.0, 0.0, 0.0)
    double dxVal = 0.0;
    double dyVal = 0.0;
    double dzVal = 0.0;
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("x"), dxVal);
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("y"), dyVal);
    JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("z"), dzVal);
    dx = static_cast<float>(dxVal);
    dy = static_cast<float>(dyVal);
    dz = static_cast<float>(dzVal);
    // if specify centerX
    Dimension length;
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("centerX"), length)) {
        centerX = length;
    }
    // if specify centerY
    if (JSViewAbstract::ParseJsonDimensionVp(argsPtrItem->GetValue("centerY"), length)) {
        centerY = length;
    }
    // if specify angle
    JSViewAbstract::GetAngle("angle", argsPtrItem, angle);
}

void SetDefaultTransition(TransitionType transitionType)
{
    auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    if (!display) {
        LOGE("display component is null.");
        return;
    }
    LOGI("JsTransition with default");
    display->SetTransition(transitionType, 0.0);
}

bool ParseAndSetOpacityTransition(const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    if (transitionArgs->Contains("opacity")) {
        double opacity = 0.0;
        JSViewAbstract::ParseJsonDouble(transitionArgs->GetValue("opacity"), opacity);
        auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
        if (!display) {
            LOGE("display component is null.");
            return true;
        }
        LOGI("JsTransition with type: %{public}d, opacity: %{public}.2f", transitionType, opacity);
        display->SetTransition(transitionType, opacity);
        return true;
    }
    return false;
}

bool ParseAndSetRotateTransition(const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    if (transitionArgs->Contains("rotate")) {
        auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
        if (!transform) {
            LOGE("transform component is null.");
            return true;
        }
        auto rotateArgs = transitionArgs->GetObject("rotate");
        // default: dx, dy, dz (0.0, 0.0, 0.0)
        float dx = 0.0f;
        float dy = 0.0f;
        float dz = 0.0f;
        // default centerX, centerY 50% 50%;
        Dimension centerX = 0.5_pct;
        Dimension centerY = 0.5_pct;
        std::optional<float> angle;
        ParseJsRotate(rotateArgs, dx, dy, dz, centerX, centerY, angle);
        if (angle) {
            transform->SetRotateTransition(transitionType, dx, dy, dz, angle.value());
            transform->SetOriginDimension(DimensionOffset(centerX, centerY));
            LOGI("JsTransition with type: %{public}d. rotate: [%.2f, %.2f, %.2f] [%.2f, %.2f] %.2f", transitionType, dx,
                dy, dz, centerX.Value(), centerY.Value(), angle.value());
        }
        return true;
    }
    return false;
}

bool ParseAndSetScaleTransition(const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    if (transitionArgs->Contains("scale")) {
        auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
        if (!transform) {
            LOGE("transform component is null.");
            return true;
        }
        auto scaleArgs = transitionArgs->GetObject("scale");
        // default: x, y, z (1.0, 1.0, 1.0)
        auto scaleX = 1.0f;
        auto scaleY = 1.0f;
        auto scaleZ = 1.0f;
        // default centerX, centerY 50% 50%;
        Dimension centerX = 0.5_pct;
        Dimension centerY = 0.5_pct;
        ParseJsScale(scaleArgs, scaleX, scaleY, scaleZ, centerX, centerY);
        transform->SetScaleTransition(transitionType, scaleX, scaleY, scaleZ);
        transform->SetOriginDimension(DimensionOffset(centerX, centerY));
        LOGI("JsTransition with type: %{public}d. scale: [%.2f, %.2f, %.2f] [%.2f, %.2f]", transitionType, scaleX,
            scaleY, scaleZ, centerX.Value(), centerY.Value());
        return true;
    }
    return false;
}

bool ParseAndSetTranslateTransition(const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    if (transitionArgs->Contains("translate")) {
        auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
        if (!transform) {
            LOGE("transform component is null.");
            return true;
        }
        auto translateArgs = transitionArgs->GetObject("translate");
        // default: x, y, z (0.0, 0.0, 0.0)
        auto translateX = Dimension(0.0);
        auto translateY = Dimension(0.0);
        auto translateZ = Dimension(0.0);
        ParseJsTranslate(translateArgs, translateX, translateY, translateZ);
        transform->SetTranslateTransition(transitionType, translateX, translateY, translateZ);
        LOGI("JsTransition with type: %{public}d. translate: [%.2f, %.2f, %.2f]", transitionType, translateX.Value(),
            translateY.Value(), translateZ.Value());
        return true;
    }
    return false;
}

bool ParseMotionPath(const std::unique_ptr<JsonValue>& argsPtrItem, MotionPathOption& option)
{
    if (argsPtrItem && !argsPtrItem->IsNull()) {
        auto path = argsPtrItem->GetString("path", "");
        if (!path.empty()) {
            option.SetPath(path);
            double from = 0.0;
            double to = 1.0;
            JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("from"), from);
            JSViewAbstract::ParseJsonDouble(argsPtrItem->GetValue("to"), to);
            option.SetBegin(static_cast<float>(from));
            option.SetEnd(static_cast<float>(to));
            option.SetRotate(argsPtrItem->GetBool("rotatable", false));
            return true;
        }
    }
    return false;
}

void SetBgImgPosition(const BackgroundImagePositionType type, const double valueX, const double valueY,
    BackgroundImagePosition& bgImgPosition)
{
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    if (type == BackgroundImagePositionType::PERCENT) {
        bgImgPosition.SetSizeX(AnimatableDimension(valueX, DimensionUnit::PERCENT, option));
        bgImgPosition.SetSizeY(AnimatableDimension(valueY, DimensionUnit::PERCENT, option));
    } else {
        bgImgPosition.SetSizeX(AnimatableDimension(valueX, DimensionUnit::PX, option));
        bgImgPosition.SetSizeY(AnimatableDimension(valueY, DimensionUnit::PX, option));
    }
}

std::string GetReplaceContentStr(int pos, const std::string& type, JSRef<JSArray> params, int32_t containCount)
{
    JSRef<JSVal> item = params->GetValueAt(pos + containCount);
    if (type == "d") {
        if (item->IsNumber()) {
            return std::to_string(item->ToNumber<uint32_t>());
        }
    } else if (type == "s") {
        if (item->IsString()) {
            return item->ToString();
        }
    } else if (type == "f") {
        if (item->IsNumber()) {
            return std::to_string(item->ToNumber<float>());
        }
    }
    return std::string();
}

void ReplaceHolder(std::string& originStr, JSRef<JSArray> params, int32_t containCount)
{
    auto size = static_cast<int32_t>(params->Length());
    if (containCount == size) {
        return;
    }
    std::string::const_iterator start = originStr.begin();
    std::string::const_iterator end = originStr.end();
    std::smatch matchs;
    bool shortHolderType = false;
    bool firstMatch = true;
    int searchTime = 0;
    while (std::regex_search(start, end, matchs, RESOURCE_APP_STRING_PLACEHOLDER)) {
        std::string pos = matchs[2];
        std::string type = matchs[4];
        if (firstMatch) {
            firstMatch = false;
            shortHolderType = pos.length() == 0;
        } else {
            if (shortHolderType ^ (pos.length() == 0)) {
                LOGE("wrong place holder,stop parse string");
                return;
            }
        }

        std::string replaceContentStr;
        if (shortHolderType) {
            replaceContentStr = GetReplaceContentStr(searchTime, type, params, containCount);
        } else {
            replaceContentStr = GetReplaceContentStr(StringToInt(pos) - 1, type, params, containCount);
        }

        originStr.replace(matchs[0].first - originStr.begin(), matchs[0].length(), replaceContentStr);
        start = originStr.begin() + matchs.prefix().length() + replaceContentStr.length();
        end = originStr.end();
        searchTime++;
    }
}

bool ParseLocationProps(const JSCallbackInfo& info, AnimatableDimension& x, AnimatableDimension& y)
{
    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return false;
    }
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> xVal = sizeObj->GetProperty("x");
    JSRef<JSVal> yVal = sizeObj->GetProperty("y");
    if (JSViewAbstract::ParseJsAnimatableDimensionVp(xVal, x) &&
        JSViewAbstract::ParseJsAnimatableDimensionVp(yVal, y)) {
        return true;
    }
    return false;
}

} // namespace

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if (origin >> COLOR_ALPHA_OFFSET == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

void JSViewAbstract::JsScale(const JSCallbackInfo& info)
{
    LOGD("JsScale");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGE("arg is not Number or Object.");
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return;
        }
        if (argsPtrItem->Contains("x") || argsPtrItem->Contains("y") || argsPtrItem->Contains("z")) {
            // default: x, y, z (1.0, 1.0, 1.0)
            auto scaleX = 1.0f;
            auto scaleY = 1.0f;
            auto scaleZ = 1.0f;
            // default centerX, centerY 50% 50%;
            Dimension centerX = 0.5_pct;
            Dimension centerY = 0.5_pct;
            ParseJsScale(argsPtrItem, scaleX, scaleY, scaleZ, centerX, centerY);
            transform->Scale(scaleX, scaleY, scaleZ, option);
            transform->SetOriginDimension(DimensionOffset(centerX, centerY));
            return;
        }
    }
    double scale;
    if (ParseJsDouble(info[0], scale)) {
        transform->Scale(scale, option);
    }
}

void JSViewAbstract::JsScaleX(const JSCallbackInfo& info)
{
    LOGD("JsScaleX");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    double scaleVal = 0.0;
    if (!ParseJsDouble(info[0], scaleVal)) {
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->ScaleX(scaleVal, option);
}

void JSViewAbstract::JsScaleY(const JSCallbackInfo& info)
{
    LOGD("JsScaleY");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    double scaleVal = 0.0;
    if (!ParseJsDouble(info[0], scaleVal)) {
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->ScaleY(scaleVal, option);
}

void JSViewAbstract::JsOpacity(const JSCallbackInfo& info)
{
    LOGD("js_opacity");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    double opacity = 0.0;
    if (!ParseJsDouble(info[0], opacity)) {
        return;
    }

    auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    display->SetOpacity(opacity, option);
}

void JSViewAbstract::JsTranslate(const JSCallbackInfo& info)
{
    LOGD("JsTranslate");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString() && !info[0]->IsObject()) {
        LOGE("arg is not [Number|String|Object].");
        return;
    }

    Dimension value;
    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return;
        }
        if (argsPtrItem->Contains("x") || argsPtrItem->Contains("y") || argsPtrItem->Contains("z")) {
            // default: x, y, z (0.0, 0.0, 0.0)
            auto translateX = Dimension(0.0);
            auto translateY = Dimension(0.0);
            auto translateZ = Dimension(0.0);
            ParseJsTranslate(argsPtrItem, translateX, translateY, translateZ);
            transform->Translate(translateX, translateY, translateZ, option);
            return;
        }
    }
    if (ParseJsDimensionVp(info[0], value)) {
        transform->Translate(value, value, option);
    }
}

void JSViewAbstract::JsTranslateX(const JSCallbackInfo& info)
{
    LOGD("JsTranslateX");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->TranslateX(value, option);
}

void JSViewAbstract::JsTranslateY(const JSCallbackInfo& info)
{
    LOGD("JsTranslateY");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->TranslateY(value, option);
}

void JSViewAbstract::JsRotate(const JSCallbackInfo& info)
{
    LOGD("JsRotate");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGE("arg is not Number or Object.");
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return;
        }
        if (argsPtrItem->Contains("x") || argsPtrItem->Contains("y") || argsPtrItem->Contains("z")) {
            // default: dx, dy, dz (0.0, 0.0, 0.0)
            float dx = 0.0f;
            float dy = 0.0f;
            float dz = 0.0f;
            // default centerX, centerY 50% 50%;
            Dimension centerX = 0.5_pct;
            Dimension centerY = 0.5_pct;
            std::optional<float> angle;
            ParseJsRotate(argsPtrItem, dx, dy, dz, centerX, centerY, angle);
            if (angle) {
                transform->Rotate(dx, dy, dz, angle.value(), option);
                transform->SetOriginDimension(DimensionOffset(centerX, centerY));
            } else {
                LOGE("Js JsRotate failed, not specify angle");
            }
            return;
        }
    }
    double rotateZ;
    if (ParseJsDouble(info[0], rotateZ)) {
        transform->RotateZ(rotateZ, option);
    }
}

void JSViewAbstract::JsRotateX(const JSCallbackInfo& info)
{
    LOGD("JsRotateX");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    double rotateVal = 0.0;
    if (!ParseJsDouble(info[0], rotateVal)) {
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->RotateX(rotateVal, option);
}

void JSViewAbstract::JsRotateY(const JSCallbackInfo& info)
{
    LOGD("JsRotateX");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    double rotateVal = 0.0;
    if (!ParseJsDouble(info[0], rotateVal)) {
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->RotateY(rotateVal, option);
}

void JSViewAbstract::JsTransform(const JSCallbackInfo& info)
{
    LOGD("JsTransform");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not object");
        return;
    }
    auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
    if (!argsPtrItem || argsPtrItem->IsNull()) {
        LOGE("Js Parse object failed. argsPtr is null. %{public}s", info[0]->ToString().c_str());
        return;
    }
    auto array = argsPtrItem->GetValue("matrix4x4");
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    if (!array || array->IsNull() || !array->IsArray() || array->GetArraySize() != matrix4Len) {
        LOGE("Js Parse object failed, matrix4x4 is null or not Array");
        return;
    }
    std::vector<float> matrix(matrix4Len);
    for (int32_t i = 0; i < matrix4Len; i++) {
        double value = 0.0;
        ParseJsonDouble(array->GetArrayItem(i), value);
        matrix[i] = static_cast<float>(value);
    }
    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->Matrix3d(matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5], matrix[6], matrix[7],
        matrix[8], matrix[9], matrix[10], matrix[11], matrix[12], matrix[13], matrix[14], matrix[15], option);
}

void JSViewAbstract::JsTransition(const JSCallbackInfo& info)
{
    LOGD("JsTransition");
    if (info.Length() > 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (info.Length() == 0) {
        SetDefaultTransition(TransitionType::ALL);
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not Object.");
        return;
    }
    auto transitionArgs = JsonUtil::ParseJsonString(info[0]->ToString());
    ParseAndSetTransitionOption(transitionArgs);
}

void JSViewAbstract::ParseAndSetTransitionOption(std::unique_ptr<JsonValue>& transitionArgs)
{
    TransitionType transitionType = ParseTransitionType(transitionArgs->GetString("type", "All"));
    bool hasEffect = false;
    hasEffect |= ParseAndSetOpacityTransition(transitionArgs, transitionType);
    hasEffect |= ParseAndSetTranslateTransition(transitionArgs, transitionType);
    hasEffect |= ParseAndSetScaleTransition(transitionArgs, transitionType);
    hasEffect |= ParseAndSetRotateTransition(transitionArgs, transitionType);
    if (!hasEffect) {
        SetDefaultTransition(transitionType);
    }
}

void JSViewAbstract::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    JsWidth(info[0]);
}

bool JSViewAbstract::JsWidth(const JSRef<JSVal>& jsValue)
{
    Dimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
        return false;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    bool isPercentSize = value.Unit() == DimensionUnit::PERCENT ? true : false;
    if (isPercentSize) {
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto renderComponent = AceType::DynamicCast<RenderComponent>(component);
        if (renderComponent) {
            renderComponent->SetIsPercentSize(isPercentSize);
        }
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    box->SetWidth(value, option);
    return true;
}

void JSViewAbstract::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    JsHeight(info[0]);
}

bool JSViewAbstract::JsHeight(const JSRef<JSVal>& jsValue)
{
    Dimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
        return false;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    bool isPercentSize = value.Unit() == DimensionUnit::PERCENT ? true : false;
    if (isPercentSize) {
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto renderComponent = AceType::DynamicCast<RenderComponent>(component);
        if (renderComponent) {
            renderComponent->SetIsPercentSize(isPercentSize);
        }
    }

    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    box->SetHeight(value, option);
    return true;
}

void JSViewAbstract::JsSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JsWidth(sizeObj->GetProperty("width"));
    JsHeight(sizeObj->GetProperty("height"));
}

void JSViewAbstract::JsConstraintSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);

    JSRef<JSVal> minWidthValue = sizeObj->GetProperty("minWidth");
    Dimension minWidth;
    if (ParseJsDimensionVp(minWidthValue, minWidth)) {
        box->SetMinWidth(minWidth);
        flexItem->SetMinWidth(minWidth);
    }

    JSRef<JSVal> maxWidthValue = sizeObj->GetProperty("maxWidth");
    Dimension maxWidth;
    if (ParseJsDimensionVp(maxWidthValue, maxWidth)) {
        box->SetMaxWidth(maxWidth);
        flexItem->SetMaxWidth(maxWidth);
    }

    JSRef<JSVal> minHeightValue = sizeObj->GetProperty("minHeight");
    Dimension minHeight;
    if (ParseJsDimensionVp(minHeightValue, minHeight)) {
        box->SetMinHeight(minHeight);
        flexItem->SetMinHeight(minHeight);
    }

    JSRef<JSVal> maxHeightValue = sizeObj->GetProperty("maxHeight");
    Dimension maxHeight;
    if (ParseJsDimensionVp(maxHeightValue, maxHeight)) {
        box->SetMaxHeight(maxHeight);
        flexItem->SetMaxHeight(maxHeight);
    }
}

void JSViewAbstract::JsLayoutPriority(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }

    int32_t priority;
    if (info[0]->IsNumber()) {
        priority = info[0]->ToNumber<int32_t>();
    } else {
        priority = StringUtils::StringToUint(info[0]->ToString());
    }

    auto flex = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flex->SetDisplayIndex(priority);
}

void JSViewAbstract::JsLayoutWeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }

    int32_t value;
    if (info[0]->IsNumber()) {
        value = info[0]->ToNumber<int32_t>();
    } else {
        value = StringUtils::StringToUint(info[0]->ToString());
    }

    auto flex = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flex->SetFlexWeight(value);
}

void JSViewAbstract::JsAlign(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsAlign: The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    if (!info[0]->IsNumber()) {
        LOGE("JsAlign: arg is not Number or String.");
        return;
    }
    auto value = info[0]->ToNumber<int32_t>();
    Alignment alignment = ParseAlignment(value);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetAlignment(alignment);
}

void JSViewAbstract::JsPosition(const JSCallbackInfo& info)
{
    AnimatableDimension x;
    AnimatableDimension y;
    if (ParseLocationProps(info, x, y)) {
        auto flexItemComponent = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
        flexItemComponent->SetLeft(x);
        flexItemComponent->SetTop(y);
        flexItemComponent->SetPositionType(PositionType::ABSOLUTE);
    }
}

void JSViewAbstract::JsMarkAnchor(const JSCallbackInfo& info)
{
    AnimatableDimension x;
    AnimatableDimension y;
    if (ParseLocationProps(info, x, y)) {
        auto flexItemComponent = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
        flexItemComponent->SetAnchorX(x);
        flexItemComponent->SetAnchorY(y);
    }
}

void JSViewAbstract::JsOffset(const JSCallbackInfo& info)
{
    AnimatableDimension x;
    AnimatableDimension y;
    if (ParseLocationProps(info, x, y)) {
        auto flexItemComponent = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
        flexItemComponent->SetLeft(x);
        flexItemComponent->SetTop(y);
        flexItemComponent->SetPositionType(PositionType::OFFSET);
    }
}

void JSViewAbstract::JsEnabled(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsBoolean()) {
        LOGE("arg is not bool.");
        return;
    }

    auto rootComponent = ViewStackProcessor::GetInstance()->GetRootComponent();
    rootComponent->SetDisabledStatus(!(info[0]->ToBoolean()));
}

void JSViewAbstract::JsAspectRatio(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    double value = 0.0;
    if (!ParseJsDouble(info[0], value)) {
        return;
    }
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    boxComponent->SetAspectRatio(value, option);
}

void JSViewAbstract::JsOverlay(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsString()) {
        LOGE("No overLayer text.");
        return;
    }

    auto coverageComponent = ViewStackProcessor::GetInstance()->GetCoverageComponent();
    std::string text = info[0]->ToString();
    coverageComponent->SetTextVal(text);
    coverageComponent->SetIsOverLay(true);

    if (info.Length() > 1 && !info[1]->IsNull()) {
        JSRef<JSObject> optionObj = JSRef<JSObject>::Cast(info[1]);
        JSRef<JSVal> alignVal = optionObj->GetProperty("align");
        auto value = alignVal->ToNumber<int32_t>();
        Alignment alignment = ParseAlignment(value);
        coverageComponent->SetAlignment(alignment);

        JSRef<JSVal> val = optionObj->GetProperty("offset");
        if (val->IsObject()) {
            JSRef<JSObject> offsetObj = JSRef<JSObject>::Cast(val);
            JSRef<JSVal> xVal = offsetObj->GetProperty("x");
            Dimension x;
            if (ParseJsDimensionVp(xVal, x)) {
                coverageComponent->SetX(x);
            }
            JSRef<JSVal> yVal = offsetObj->GetProperty("y");
            Dimension y;
            if (ParseJsDimensionVp(yVal, y)) {
                coverageComponent->SetY(y);
            }
        }
    }
}

Alignment JSViewAbstract::ParseAlignment(int32_t align)
{
    Alignment alignment = Alignment::CENTER;
    switch (align) {
        case 0:
            alignment = Alignment::TOP_LEFT;
            break;
        case 1:
            alignment = Alignment::TOP_CENTER;
            break;
        case 2:
            alignment = Alignment::TOP_RIGHT;
            break;
        case 3:
            alignment = Alignment::CENTER_LEFT;
            break;
        case 4:
            alignment = Alignment::CENTER;
            break;
        case 5:
            alignment = Alignment::CENTER_RIGHT;
            break;
        case 6:
            alignment = Alignment::BOTTOM_LEFT;
            break;
        case 7:
            alignment = Alignment::BOTTOM_CENTER;
            break;
        case 8:
            alignment = Alignment::BOTTOM_RIGHT;
            break;
        default:
            LOGE("Invaild value for alignment");
    }
    return alignment;
}

void JSViewAbstract::SetVisibility(int value)
{
    auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    display->SetVisible(VisibleType(value));
}

void JSViewAbstract::JsFlexBasis(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsFlexBasis: The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetFlexBasis(value);
}

void JSViewAbstract::JsFlexGrow(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsFlexGrow: The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    double value = 0.0;
    if (!ParseJsDouble(info[0], value)) {
        return;
    }
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetFlexGrow(value);
}

void JSViewAbstract::JsFlexShrink(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsFlexShrink: The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    double value = 0.0;
    if (!ParseJsDouble(info[0], value)) {
        return;
    }
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetFlexShrink(value);
}

void JSViewAbstract::JsDisplayPriority(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsDisplayPriority: The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    double value = 0.0;
    if (!ParseJsDouble(info[0], value)) {
        return;
    }
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetDisplayIndex(value);
}

void JSViewAbstract::JsSharedTransition(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsSharedTransition: The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (!info[0]->IsString()) {
        LOGE("JsSharedTransition: arg[0] is not String.");
        return;
    }
    // id
    auto id = info[0]->ToString();
    if (id.empty()) {
        LOGE("JsSharedTransition: id is empty.");
        return;
    }
    auto sharedTransitionComponent = ViewStackProcessor::GetInstance()->GetSharedTransitionComponent();
    sharedTransitionComponent->SetShareId(id);

    // options
    if (info.Length() > 1 && info[1]->IsObject()) {
        auto optionsArgs = JsonUtil::ParseJsonString(info[1]->ToString());
        // default: duration: 1000; if not specify: duration: 0
        int32_t duration = 0;
        auto durationValue = optionsArgs->GetValue("duration");
        if (durationValue && durationValue->IsNumber()) {
            duration = durationValue->GetInt();
            if (duration < 0) {
                duration = DEFAULT_DURATION;
            }
        }
        // default: delay: 0
        auto delay = optionsArgs->GetInt("delay", 0);
        if (delay < 0) {
            delay = 0;
        }
        // default: LinearCurve
        RefPtr<Curve> curve;
        auto curveArgs = optionsArgs->GetValue("curve");
        if (curveArgs->IsString()) {
            curve = CreateCurve(optionsArgs->GetString("curve", "linear"));
        } else if (curveArgs->IsObject()) {
            auto curveString = curveArgs->GetValue("__curveString");
            if (!curveString) {
                return;
            }
            curve = CreateCurve(curveString->GetString());
        } else {
            curve = AceType::MakeRefPtr<LinearCurve>();
        }
        TweenOption tweenOption;
        tweenOption.SetCurve(curve);
        tweenOption.SetDuration(static_cast<int32_t>(duration));
        tweenOption.SetDelay(static_cast<int32_t>(delay));
        // motionPath

        if (optionsArgs->Contains("motionPath")) {
            MotionPathOption motionPathOption;
            if (ParseMotionPath(optionsArgs->GetValue("motionPath"), motionPathOption)) {
                tweenOption.SetMotioPathOption(motionPathOption);
            }
        }
        // zIndex
        int32_t zIndex = 0;
        if (optionsArgs->Contains("zIndex")) {
            zIndex = optionsArgs->GetInt("zIndex", 0);
        }
        // type
        SharedTransitionEffectType type = SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE;
        if (optionsArgs->Contains("type")) {
            type = static_cast<SharedTransitionEffectType>(
                optionsArgs->GetInt("type", static_cast<int32_t>(SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE)));
        }
        // effect: exchange
        auto sharedTransitionEffect =
            SharedTransitionEffect::GetSharedTransitionEffect(type, sharedTransitionComponent->GetShareId());
        sharedTransitionComponent->SetEffect(sharedTransitionEffect);
        sharedTransitionComponent->SetOption(tweenOption);
        if (zIndex != 0) {
            sharedTransitionComponent->SetZIndex(zIndex);
        }
    }
}

void JSViewAbstract::JsGeometryTransition(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsGeometryTransition: The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (!info[0]->IsString()) {
        LOGE("JsGeometryTransition: arg[0] is not String.");
        return;
    }
    // id
    auto id = info[0]->ToString();
    if (id.empty()) {
        LOGE("JsGeometryTransition: id is empty.");
        return;
    }
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    boxComponent->SetGeometryTransitionId(id);
}

void JSViewAbstract::JsAlignSelf(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsAlignSelf: The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    if (!info[0]->IsNumber()) {
        LOGE("JsAlignSelf: arg is not Number or String.");
        return;
    }
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    auto alignVal = info[0]->ToNumber<int32_t>();

    if (alignVal >= 0 && alignVal <= MAX_ALIGN_VALUE) {
        flexItem->SetAlignSelf((FlexAlign)alignVal);
    }
}

void JSViewAbstract::JsBorderColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color borderColor;
    if (!ParseJsColor(info[0], borderColor)) {
        return;
    }
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    SetBorderColor(borderColor, option);
}

void JSViewAbstract::JsBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor)) {
        return;
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    box->SetColor(backgroundColor, option);
}

void JSViewAbstract::JsBackgroundImage(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsString()) {
        LOGE("info[0] is not a string.");
        return;
    }

    auto decoration = GetBackDecoration();
    if (!decoration) {
        LOGE("The decoration is nullptr.");
        return;
    }
    auto image = decoration->GetImage();
    if (!image) {
        image = AceType::MakeRefPtr<BackgroundImage>();
    }
    image->SetSrc(info[0]->ToString(), GetThemeConstants());
    int32_t repeatIndex = 0;
    if (info.Length() == 2 && info[1]->IsNumber()) {
        repeatIndex = info[1]->ToNumber<int32_t>();
    }
    auto repeat = static_cast<ImageRepeat>(repeatIndex);
    image->SetImageRepeat(repeat);
    decoration->SetImage(image);
}

void JSViewAbstract::JsBackgroundImageSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have 1 object argument.");
        return;
    }
    if (!info[0]->IsObject() && !info[0]->IsNumber()) {
        LOGE("JsBackgroundImageSize: info[0] is not object or number");
        return;
    }
    auto decoration = GetBackDecoration();
    if (!decoration) {
        LOGE("The decoration is nullptr.");
        return;
    }
    auto image = decoration->GetImage();
    if (!image) {
        image = AceType::MakeRefPtr<BackgroundImage>();
    }
    BackgroundImageSize bgImgSize;
    if (info[0]->IsNumber()) {
        auto sizeType = static_cast<BackgroundImageSizeType>(info[0]->ToNumber<int32_t>());
        bgImgSize.SetSizeTypeX(sizeType);
        bgImgSize.SetSizeTypeY(sizeType);
    } else {
        auto imageArgs = JsonUtil::ParseJsonString(info[0]->ToString());
        if (imageArgs->IsNull()) {
            LOGE("Js Parse failed. imageArgs is null.");
            return;
        }
        double width = 0.0;
        double height = 0.0;
        ParseJsonDouble(imageArgs->GetValue("width"), width);
        ParseJsonDouble(imageArgs->GetValue("height"), height);
        bgImgSize.SetSizeTypeX(BackgroundImageSizeType::LENGTH);
        bgImgSize.SetSizeValueX(width);
        bgImgSize.SetSizeTypeY(BackgroundImageSizeType::LENGTH);
        bgImgSize.SetSizeValueY(height);
    }
    image->SetImageSize(bgImgSize);
    decoration->SetImage(image);
}

void JSViewAbstract::JsBackgroundImagePosition(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have 1 object argument.");
        return;
    }
    if (!info[0]->IsObject() && !info[0]->IsNumber()) {
        LOGE("JsBackgroundImageSize: info[0] is not object or number");
        return;
    }
    auto decoration = GetBackDecoration();
    if (!decoration) {
        LOGE("The decoration is nullptr.");
        return;
    }
    auto image = decoration->GetImage();
    if (!image) {
        image = AceType::MakeRefPtr<BackgroundImage>();
    }
    BackgroundImagePosition bgImgPosition;
    if (info[0]->IsNumber()) {
        int32_t align = info[0]->ToNumber<int32_t>();
        switch (align) {
            case 0:
                SetBgImgPosition(BackgroundImagePositionType::PERCENT, 0, 0, bgImgPosition);
                break;
            case 1:
                SetBgImgPosition(BackgroundImagePositionType::PERCENT, 50, 0, bgImgPosition);
                break;
            case 2:
                SetBgImgPosition(BackgroundImagePositionType::PERCENT, 100, 0, bgImgPosition);
                break;
            case 3:
                SetBgImgPosition(BackgroundImagePositionType::PERCENT, 0, 50, bgImgPosition);
                break;
            case 4:
                SetBgImgPosition(BackgroundImagePositionType::PERCENT, 50, 50, bgImgPosition);
                break;
            case 5:
                SetBgImgPosition(BackgroundImagePositionType::PERCENT, 100, 50, bgImgPosition);
                break;
            case 6:
                SetBgImgPosition(BackgroundImagePositionType::PERCENT, 0, 100, bgImgPosition);
                break;
            case 7:
                SetBgImgPosition(BackgroundImagePositionType::PERCENT, 50, 100, bgImgPosition);
                break;
            case 8:
                SetBgImgPosition(BackgroundImagePositionType::PERCENT, 100, 100, bgImgPosition);
                break;
            default:
                break;
        }
    } else {
        auto imageArgs = JsonUtil::ParseJsonString(info[0]->ToString());
        if (imageArgs->IsNull()) {
            LOGE("Js Parse failed. imageArgs is null.");
            return;
        }
        double x = 0.0;
        double y = 0.0;
        ParseJsonDouble(imageArgs->GetValue("x"), x);
        ParseJsonDouble(imageArgs->GetValue("y"), y);
        SetBgImgPosition(BackgroundImagePositionType::PX, x, y, bgImgPosition);
    }
    image->SetImagePosition(bgImgPosition);
    decoration->SetImage(image);
}

void JSViewAbstract::JsBindMenu(const JSCallbackInfo& info)
{
    auto menuComponent = AceType::MakeRefPtr<OHOS::Ace::MenuComponent>("", "menu");
    auto click = ViewStackProcessor::GetInstance()->GetBoxComponent();
    RefPtr<Gesture> tapGesture = AceType::MakeRefPtr<TapGesture>();
    tapGesture->SetOnActionId([weak = WeakPtr<OHOS::Ace::MenuComponent>(menuComponent)](const GestureEvent& info) {
        auto refPtr = weak.Upgrade();
        if (!refPtr) {
            return;
        }
        auto showDialog = refPtr->GetTargetCallback();
        showDialog("", info.GetGlobalLocation());
    });
    click->SetOnClick(tapGesture);
    ViewStackProcessor::GetInstance()->Push(menuComponent);
    auto menuTheme = GetTheme<SelectTheme>();
    menuComponent->SetTheme(menuTheme);
    auto context = info.GetExecutionContext();

    auto paramArray = JSRef<JSArray>::Cast(info[0]);
    size_t size = paramArray->Length();
    for (size_t i = 0; i < size; i++) {
        std::string value;
        auto indexObject = JSRef<JSObject>::Cast(paramArray->GetValueAt(i));
        auto menuValue = indexObject->GetProperty("value");
        auto menuAction = indexObject->GetProperty("action");
        ParseJsString(menuValue, value);
        auto action = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(menuAction));

        auto optionTheme = GetTheme<SelectTheme>();
        auto optionComponent = AceType::MakeRefPtr<OHOS::Ace::OptionComponent>(optionTheme);
        auto textComponent = AceType::MakeRefPtr<OHOS::Ace::TextComponent>(value);

        optionComponent->SetTheme(optionTheme);
        optionComponent->SetText(textComponent);
        optionComponent->SetValue(value);
        optionComponent->SetCustomizedCallback([action, context] {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context);
            action->Execute();
        });
        menuComponent->AppendOption(optionComponent);
    }
    ViewStackProcessor::GetInstance()->Pop();
}

void JSViewAbstract::JsPadding(const JSCallbackInfo& info)
{
    ParseMarginOrPadding(info, false);
}

void JSViewAbstract::JsMargin(const JSCallbackInfo& info)
{
    JSViewAbstract::ParseMarginOrPadding(info, true);
}

void JSViewAbstract::ParseMarginOrPadding(const JSCallbackInfo& info, bool isMargin)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (!info[0]->IsString() && !info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGE("arg is not a string, number or object.");
        return;
    }

    if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return;
        }
        if (argsPtrItem->Contains("top") || argsPtrItem->Contains("bottom") || argsPtrItem->Contains("left") ||
            argsPtrItem->Contains("right")) {
            Dimension topDimen = Dimension(0.0, DimensionUnit::VP);
            Dimension bottomDimen = Dimension(0.0, DimensionUnit::VP);
            Dimension leftDimen = Dimension(0.0, DimensionUnit::VP);
            Dimension rightDimen = Dimension(0.0, DimensionUnit::VP);
            ParseJsonDimensionVp(argsPtrItem->GetValue("top"), topDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("bottom"), bottomDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("left"), leftDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("right"), rightDimen);
            if (isMargin) {
                SetMargins(topDimen, bottomDimen, leftDimen, rightDimen);
            } else {
                SetPaddings(topDimen, bottomDimen, leftDimen, rightDimen);
            }
            return;
        }
    }
    AnimatableDimension length;
    if (!ParseJsAnimatableDimensionVp(info[0], length)) {
        return;
    }
    if (isMargin) {
        SetMargin(length);
    } else {
        SetPadding(length);
    }
}

void JSViewAbstract::JsBorder(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return;
    }
    auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
    if (!argsPtrItem || argsPtrItem->IsNull()) {
        LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
        info.ReturnSelf();
        return;
    }

    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();

    Dimension width;
    if (argsPtrItem->Contains("width") && ParseJsonDimensionVp(argsPtrItem->GetValue("width"), width)) {
        SetBorderWidth(width, option);
    }
    Color color;
    if (argsPtrItem->Contains("color") && ParseJsonColor(argsPtrItem->GetValue("color"), color)) {
        SetBorderColor(color, option);
    }
    Dimension radius;
    if (argsPtrItem->Contains("radius") && ParseJsonDimensionVp(argsPtrItem->GetValue("radius"), radius)) {
        SetBorderRadius(radius, option);
    }
    if (argsPtrItem->Contains("style")) {
        auto borderStyle = argsPtrItem->GetInt("style", static_cast<int32_t>(BorderStyle::SOLID));
        SetBorderStyle(borderStyle);
    }
    info.ReturnSelf();
}

void JSViewAbstract::JsBorderWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension borderWidth;
    if (!ParseJsDimensionVp(info[0], borderWidth)) {
        return;
    }
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    SetBorderWidth(borderWidth, option);
}

void JSViewAbstract::JsBorderRadius(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension borderRadius;
    if (!ParseJsDimensionVp(info[0], borderRadius)) {
        return;
    }
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    SetBorderRadius(borderRadius, option);
}

void JSViewAbstract::JsBlur(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }

    double blur = 0.0;
    if (!ParseJsDouble(info[0], blur)) {
        return;
    }
    SetBlur(blur);
    info.SetReturnValue(info.This());
}

void JSViewAbstract::JsColorBlend(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color colorBlend;
    if (!ParseJsColor(info[0], colorBlend)) {
        return;
    }
    SetColorBlend(colorBlend);
    info.SetReturnValue(info.This());
}

void JSViewAbstract::JsBackdropBlur(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }

    double blur = 0.0;
    if (!ParseJsDouble(info[0], blur)) {
        return;
    }
    SetBackdropBlur(blur);
    info.SetReturnValue(info.This());
}

void JSViewAbstract::JsWindowBlur(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not object");
        return;
    }

    auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
    if (!argsPtrItem || argsPtrItem->IsNull()) {
        LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
        return;
    }
    double progress = 0.0;
    ParseJsonDouble(argsPtrItem->GetValue("percent"), progress);
    auto style = argsPtrItem->GetInt("style", static_cast<int32_t>(WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT));

    progress = std::clamp(progress, 0.0, 1.0);
    style = std::clamp(style, static_cast<int32_t>(WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT),
        static_cast<int32_t>(WindowBlurStyle::STYLE_BACKGROUND_XLARGE_DARK));

    SetWindowBlur(static_cast<float>(progress), static_cast<WindowBlurStyle>(style));
    info.SetReturnValue(info.This());
}

bool JSViewAbstract::ParseJsDimension(const JSRef<JSVal>& jsValue, Dimension& result, DimensionUnit defaultUnit)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        LOGE("arg is not Number, String or Object.");
        return false;
    }

    if (jsValue->IsNumber()) {
        result = Dimension(jsValue->ToNumber<double>(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        result = StringUtils::StringToDimensionWithUnit(jsValue->ToString(), defaultUnit);
        return true;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        LOGW("resId is not number");
        return false;
    }

    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGE("themeConstants is nullptr");
        return false;
    }
    result = themeConstants->GetDimension(resId->ToNumber<uint32_t>());
    return true;
}

bool JSViewAbstract::ParseJsDimensionVp(const JSRef<JSVal>& jsValue, Dimension& result)
{
    // 'vp' -> the value varies with piexl density of device.
    return ParseJsDimension(jsValue, result, DimensionUnit::VP);
}

bool JSViewAbstract::ParseJsAnimatableDimensionVp(const JSRef<JSVal>& jsValue, AnimatableDimension& result)
{
    if (ParseJsDimensionVp(jsValue, result)) {
        AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
        result.SetAnimationOption(option);
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseJsDimensionFp(const JSRef<JSVal>& jsValue, Dimension& result)
{
    // the 'fp' unit is used for text secnes.
    return ParseJsDimension(jsValue, result, DimensionUnit::FP);
}

bool JSViewAbstract::ParseJsDimensionPx(const JSRef<JSVal>& jsValue, Dimension& result)
{
    return ParseJsDimension(jsValue, result, DimensionUnit::PX);
}

bool JSViewAbstract::ParseJsDouble(const JSRef<JSVal>& jsValue, double& result)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        LOGE("arg is not Number, String or Object.");
        return false;
    }
    if (jsValue->IsNumber()) {
        result = jsValue->ToNumber<double>();
        return true;
    }
    if (jsValue->IsString()) {
        result = StringUtils::StringToDouble(jsValue->ToString());
        return true;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        LOGW("resId is not number");
        return false;
    }

    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }
    result = themeConstants->GetDouble(resId->ToNumber<uint32_t>());
    return true;
}

bool JSViewAbstract::ParseJsColor(const JSRef<JSVal>& jsValue, Color& result)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        LOGE("arg is not Number, String or Object.");
        return false;
    }
    if (jsValue->IsNumber()) {
        result = Color(ColorAlphaAdapt(jsValue->ToNumber<uint32_t>()));
        return true;
    }
    if (jsValue->IsString()) {
        result = Color::FromString(jsValue->ToString());
        return true;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        LOGW("resId is not number");
        return false;
    }

    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }
    result = themeConstants->GetColor(resId->ToNumber<uint32_t>());
    return true;
}

bool JSViewAbstract::ParseJsFontFamilies(const JSRef<JSVal>& jsValue, std::vector<std::string>& result)
{
    result.clear();
    if (!jsValue->IsString() && !jsValue->IsObject()) {
        LOGE("arg is not String or Object.");
        return false;
    }
    if (jsValue->IsString()) {
        result = ConvertStrToFontFamilies(jsValue->ToString());
        return true;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        LOGW("resId is not number");
        return false;
    }

    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }
    result.emplace_back(themeConstants->GetString(resId->ToNumber<uint32_t>()));
    return true;
}

bool JSViewAbstract::ParseJsString(const JSRef<JSVal>& jsValue, std::string& result)
{
    if (!jsValue->IsString() && !jsValue->IsObject()) {
        LOGE("arg is not String or Object.");
        return false;
    }

    if (jsValue->IsString()) {
        LOGD("jsValue->IsString()");
        result = jsValue->ToString();
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!type->IsNumber()) {
        LOGW("type is not number");
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        LOGW("resId is not number");
        return false;
    }

    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }

    JSRef<JSVal> args = jsObj->GetProperty("params");
    if (!args->IsArray()) {
        LOGW("args is not array");
        return false;
    }

    JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
    if (type->ToNumber<uint32_t>() == static_cast<int>(ResourceType::STRING)) {
        auto originStr = themeConstants->GetString(resId->ToNumber<uint32_t>());
        ReplaceHolder(originStr, params, 0);
        result = originStr;
    } else if (type->ToNumber<uint32_t>() == static_cast<int>(ResourceType::PLURAL)) {
        auto countJsVal = params->GetValueAt(0);
        int count = 0;
        if (!countJsVal->IsNumber()) {
            LOGW("pluralString, pluralnumber is not number");
            return false;
        }
        count = countJsVal->ToNumber<int>();
        auto pluralStr = themeConstants->GetPluralString(resId->ToNumber<uint32_t>(), count);
        ReplaceHolder(pluralStr, params, 1);
        result = pluralStr;
    } else {
        return false;
    }

    return true;
}

bool JSViewAbstract::ParseJsMedia(const JSRef<JSVal>& jsValue, std::string& result)
{
    if (!jsValue->IsObject() && !jsValue->IsString()) {
        LOGE("arg is not Object and String.");
        return false;
    }

    if (jsValue->IsString()) {
        result = jsValue->ToString();
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNull() && !type->IsNull() && type->IsNumber() && resId->IsNumber()) {
        auto themeConstants = GetThemeConstants();
        if (!themeConstants) {
            LOGW("themeConstants is nullptr");
            return false;
        }
        auto typeInteger = type->ToNumber<int32_t>();
        if (typeInteger == static_cast<int>(ResourceType::MEDIA)) {
            result = themeConstants->GetMediaPath(resId->ToNumber<uint32_t>());
            return true;
        }

        if (typeInteger == static_cast<int>(ResourceType::RAWFILE)) {
            JSRef<JSVal> args = jsObj->GetProperty("params");
            if (!args->IsArray()) {
                LOGW("args is not Array");
                return false;
            }
            JSRef<JSArray> params = JSRef<JSArray>::Cast(args);
            auto fileName = params->GetValueAt(0);
            if (!fileName->IsString()) {
                LOGW("fileName is not String");
                return false;
            }
            result = themeConstants->GetRawfile(fileName->ToString());
            return true;
        }
        
        LOGE("JSImage::Create ParseJsMedia type is wrong");
        return false;
    }

    LOGE("input value is not string or number, using PixelMap");
    return false;
}

bool JSViewAbstract::ParseJsBool(const JSRef<JSVal>& jsValue, bool& result)
{
    if (!jsValue->IsBoolean() && !jsValue->IsObject()) {
        LOGE("arg is not bool or Object.");
        return false;
    }

    if (jsValue->IsBoolean()) {
        LOGD("jsValue->IsBoolean()");
        result = jsValue->ToBoolean();
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!type->IsNumber()) {
        LOGW("type is not number");
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        LOGW("resId is not number");
        return false;
    }

    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }

    if (type->ToNumber<uint32_t>() == static_cast<int>(ResourceType::BOOLEAN)) {
        result = themeConstants->GetBoolean(resId->ToNumber<uint32_t>());
        return true;
    } else {
        return false;
    }
}

bool JSViewAbstract::ParseJsInteger(const JSRef<JSVal>& jsValue, uint32_t& result)
{
    if (!jsValue->IsNumber() && !jsValue->IsObject()) {
        LOGE("arg is not number or Object.");
        return false;
    }

    if (jsValue->IsNumber()) {
        LOGD("jsValue->IsNumber()");
        result = jsValue->ToNumber<uint32_t>();
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!type->IsNumber()) {
        LOGW("type is not number");
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        LOGW("resId is not number");
        return false;
    }

    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }

    if (type->ToNumber<uint32_t>() == static_cast<int>(ResourceType::INTEGER)) {
        result = themeConstants->GetInt(resId->ToNumber<uint32_t>());
        return true;
    } else {
        return false;
    }

}

bool JSViewAbstract::ParseJsIntegerArray(const JSRef<JSVal>& jsValue, std::vector<uint32_t>& result)
{

    if (!jsValue->IsArray() && !jsValue->IsObject()) {
        LOGE("arg is not array or Object.");
        return false;
    }

    if (jsValue->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            if (value->IsNumber()) {
                result.emplace_back(value->ToNumber<uint32_t>());
            } else if (value->IsObject()) {
                uint32_t singleResInt;
                if (ParseJsInteger(value, singleResInt)) {
                    result.emplace_back(singleResInt);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!type->IsNumber()) {
        LOGW("type is not number");
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        LOGW("resId is not number");
        return false;
    }

    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }

    if (type->ToNumber<uint32_t>() == static_cast<int>(ResourceType::INTARRAY)) {
        result = themeConstants->GetIntArray(resId->ToNumber<uint32_t>());
        return true;
    } else {
        return false;
    }
}

bool JSViewAbstract::ParseJsStrArray(const JSRef<JSVal>& jsValue, std::vector<std::string>& result)
{
    if (!jsValue->IsArray() && !jsValue->IsObject()) {
        LOGE("arg is not array or Object.");
        return false;
    }

    if (jsValue->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            if (value->IsString()) {
                result.emplace_back(value->ToString());
            } else if (value->IsObject()) {
                std::string singleResStr;
                if (ParseJsString(value, singleResStr)) {
                    result.emplace_back(singleResStr);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!type->IsNumber()) {
        LOGW("type is not number");
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        LOGW("resId is not number");
        return false;
    }

    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }

    if (type->ToNumber<uint32_t>() == static_cast<int>(ResourceType::STRARRAY)) {
        result = themeConstants->GetStringArray(resId->ToNumber<uint32_t>());
        return true;
    } else {
        return false;
    }
}


std::pair<Dimension, Dimension> JSViewAbstract::ParseSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return std::pair<Dimension, Dimension>();
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return std::pair<Dimension, Dimension>();
    }

    auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
    if (!argsPtrItem || argsPtrItem->IsNull()) {
        LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
        info.SetReturnValue(info.This());
        return std::pair<Dimension, Dimension>();
    }
    Dimension width;
    Dimension height;
    if (!ParseJsonDimensionVp(argsPtrItem->GetValue("width"), width) ||
        !ParseJsonDimensionVp(argsPtrItem->GetValue("height"), height)) {
        return std::pair<Dimension, Dimension>();
    }
    LOGD("JsSize width = %lf unit = %d, height = %lf unit = %d", width.Value(), width.Unit(), height.Value(),
        height.Unit());
    info.SetReturnValue(info.This());
    return std::pair<Dimension, Dimension>(width, height);
}

void JSViewAbstract::JsUseAlign(const JSCallbackInfo& info)
{
    if (info.Length() < 2) {
        LOGE("The arg is wrong, it is supposed to have atleast 2 arguments");
        return;
    }

    if (!info[0]->IsObject() && !info[1]->IsObject()) {
        LOGE("arg is not IsObject.");
        return;
    }

    AlignDeclaration* declaration = JSRef<JSObject>::Cast(info[0])->Unwrap<AlignDeclaration>();
    if (declaration == nullptr) {
        LOGE("declaration is nullptr");
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[1]);
    JSRef<JSVal> side = obj->GetProperty("side");
    JSRef<JSVal> offset = obj->GetProperty("offset");

    if (!side->IsNumber()) {
        LOGE("side is not Number [%s]", side->ToString().c_str());
        return;
    }

    auto sideValue = side->ToNumber<int32_t>();

    if (declaration->GetDeclarationType() == AlignDeclaration::DeclarationType::HORIZONTAL) {
        if (sideValue < static_cast<int32_t>(AlignDeclaration::Edge::START) ||
            sideValue > static_cast<int32_t>(AlignDeclaration::Edge::END)) {
            LOGE("side should be Edge.Start Edge.Middle or Edge.End with HorizontalAlignDeclaration");
            return;
        }
    } else if (declaration->GetDeclarationType() == AlignDeclaration::DeclarationType::VERTICAL) {
        if (sideValue < static_cast<int32_t>(AlignDeclaration::Edge::TOP) ||
            sideValue > static_cast<int32_t>(AlignDeclaration::Edge::BASELINE)) {
            LOGE("side should be Edge.Top Edge.Center Edge.Bottom or Edge.Baseline with VerticalAlignDeclaration");
            return;
        }
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetAlignDeclarationPtr(declaration);
    box->SetUseAlignSide(static_cast<AlignDeclaration::Edge>(sideValue));
    Dimension offsetDimension;
    if (ParseJsDimensionVp(offset, offsetDimension)) {
        box->SetUseAlignOffset(offsetDimension);
    }
}

void JSViewAbstract::JsGridSpan(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number");
        return;
    }
    auto gridContainerInfo = JSGridContainer::GetContainer();
    if (gridContainerInfo != nullptr) {
        auto span = info[0]->ToNumber<uint32_t>();
        auto builder = ViewStackProcessor::GetInstance()->GetBoxComponent()->GetGridColumnInfoBuilder();
        builder->SetParent(gridContainerInfo);
        builder->SetColumns(span);
    }
}

void JSViewAbstract::JsGridOffset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    auto gridContainerInfo = JSGridContainer::GetContainer();
    if (info[0]->IsNumber() && gridContainerInfo != nullptr) {
        auto builder = ViewStackProcessor::GetInstance()->GetBoxComponent()->GetGridColumnInfoBuilder();
        builder->SetParent(gridContainerInfo);
        int32_t offset = info[0]->ToNumber<int32_t>();
        builder->SetOffset(offset);
    }
}

static bool ParseSpanAndOffset(const JSRef<JSVal>& val, uint32_t& span, int32_t& offset)
{
    // {lg: 4}
    if (val->IsNumber()) {
        span = val->ToNumber<uint32_t>();
        return true;
    }

    if (!val->IsObject()) {
        LOGE("The argument is not object or number.");
        return false;
    }

    // {lg: {span: 1, offset: 2}}
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(val);
    span = obj->GetProperty("span")->ToNumber<int32_t>();
    offset = obj->GetProperty("offset")->ToNumber<int32_t>();
    return true;
}

void JSViewAbstract::JsUseSizeType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argument is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("The argument is not object or string.");
        return;
    }
    auto gridContainerInfo = JSGridContainer::GetContainer();
    if (gridContainerInfo == nullptr) {
        LOGE("No valid grid container.");
        return;
    }
    auto builder = ViewStackProcessor::GetInstance()->GetBoxComponent()->GetGridColumnInfoBuilder();
    builder->SetParent(gridContainerInfo);

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    // keys order must be strictly refer to GridSizeType
    const char* keys[] = { "", "xs", "sm", "md", "lg" };
    for (uint32_t i = 1; i < sizeof(keys) / sizeof(const char*); i++) {
        JSRef<JSVal> val = sizeObj->GetProperty(keys[i]);
        if (val->IsNull() || val->IsEmpty()) {
            continue;
        }
        uint32_t span = 0;
        int32_t offset = 0;
        if (ParseSpanAndOffset(val, span, offset)) {
            builder->SetSizeColumn(static_cast<GridSizeType>(i), span);
            builder->SetOffset(offset, static_cast<GridSizeType>(i));
        }
    }
}

void JSViewAbstract::JsZIndex(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    int zIndex = 0;
    if (info[0]->IsNumber()) {
        zIndex = info[0]->ToNumber<int>();
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto renderComponent = AceType::DynamicCast<RenderComponent>(component);
    if (renderComponent) {
        renderComponent->SetZIndex(zIndex);
    }
}

void JSViewAbstract::Pop()
{
    ViewStackProcessor::GetInstance()->Pop();
}

void JSViewAbstract::JsOnDrag(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsDragFunction> jsOnDragFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto onDragId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragFunc)](
                            const RefPtr<DragEvent>& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(info);
        };
        auto drag = ViewStackProcessor::GetInstance()->GetBoxComponent();
        drag->SetOnDragId(onDragId);
    }
}

void JSViewAbstract::JsOnDragEnter(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto onDragEnterId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc)](
                                 const RefPtr<DragEvent>& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(info);
        };
        auto dragEnter = ViewStackProcessor::GetInstance()->GetBoxComponent();
        dragEnter->SetOnDragEnterId(onDragEnterId);
    }
}

void JSViewAbstract::JsOnDragMove(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto onDragMoveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc)](
                                const RefPtr<DragEvent>& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(info);
        };
        auto dragMove = ViewStackProcessor::GetInstance()->GetBoxComponent();
        dragMove->SetOnDragMoveId(onDragMoveId);
    }
}

void JSViewAbstract::JsOnDragLeave(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto onDragLeaveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc)](
                                 const RefPtr<DragEvent>& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(info);
        };
        auto dragLeave = ViewStackProcessor::GetInstance()->GetBoxComponent();
        dragLeave->SetOnDragLeaveId(onDragLeaveId);
    }
}

void JSViewAbstract::JsOnDrop(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto onDropId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc)](
                            const RefPtr<DragEvent>& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(info);
        };
        auto drop = ViewStackProcessor::GetInstance()->GetBoxComponent();
        drop->SetOnDropId(onDropId);
    }
}

#ifndef WEARABLE_PRODUCT
void JSViewAbstract::JsBindPopup(const JSCallbackInfo& info)
{
    if (info.Length() < 2) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsBoolean()) {
        LOGE("No overLayer text.");
        return;
    }

    ViewStackProcessor::GetInstance()->GetCoverageComponent();
    auto popupComponent = ViewStackProcessor::GetInstance()->GetPopupComponent(true);
    auto popupParam = popupComponent->GetPopupParam();
    if (!popupParam) {
        return;
    }

    auto mainComponen = ViewStackProcessor::GetInstance()->GetMainComponent();
    popupParam->SetTargetId(mainComponen->GetInspectorId());
    popupParam->SetIsShow(info[0]->ToBoolean());

    JSRef<JSObject> popupObj = JSRef<JSObject>::Cast(info[1]);
    JSRef<JSVal> messageVal = popupObj->GetProperty("message");
    popupComponent->SetMessage(messageVal->ToString());

    JSRef<JSVal> placementOnTopVal = popupObj->GetProperty("placementOnTop");
    if (placementOnTopVal->IsBoolean()) {
        popupComponent->SetPlacementOnTop(placementOnTopVal->ToBoolean());
    }

    JSRef<JSVal> onStateChangeVal = popupObj->GetProperty("onStateChange");
    if (onStateChangeVal->IsFunction()) {
        std::vector<std::string> keys = { "isVisible" };
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(),
                                    JSRef<JSFunc>::Cast(onStateChangeVal));
        auto eventMarker = EventMarker(
            [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), keys](const std::string& param) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                func->Execute(keys, param);
            });
        popupComponent->SetOnStateChange(eventMarker);
    }

    JSRef<JSVal> primaryButtonVal = popupObj->GetProperty("primaryButton");
    if (primaryButtonVal->IsObject()) {
        ButtonProperties properties;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(primaryButtonVal);
        JSRef<JSVal> value = obj->GetProperty("value");
        if (value->IsString()) {
            properties.value = value->ToString();
        }

        JSRef<JSVal> actionValue = obj->GetProperty("action");
        if (actionValue->IsFunction()) {
            auto actionFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(actionValue));
            EventMarker actionId([execCtx = info.GetExecutionContext(), func = std::move(actionFunc)]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                func->Execute();
            });
            properties.actionId = actionId;
        }
        properties.showButton = true;
        popupComponent->SetPrimaryButtonProperties(properties);
    }

    JSRef<JSVal> secondaryButtonVal = popupObj->GetProperty("secondaryButton");
    if (secondaryButtonVal->IsObject()) {
        ButtonProperties properties;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(secondaryButtonVal);
        JSRef<JSVal> value = obj->GetProperty("value");
        if (value->IsString()) {
            properties.value = value->ToString();
        }

        JSRef<JSVal> actionValue = obj->GetProperty("action");
        if (actionValue->IsFunction()) {
            auto actionFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(actionValue));
            EventMarker actionId([execCtx = info.GetExecutionContext(), func = std::move(actionFunc)]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                func->Execute();
            });
            properties.actionId = actionId;
        }
        properties.showButton = true;
        popupComponent->SetSecondaryButtonProperties(properties);
    }
}
#endif

void JSViewAbstract::JsLinearGradient(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return;
    }

    auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
    if (!argsPtrItem || argsPtrItem->IsNull()) {
        LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
        info.ReturnSelf();
        return;
    }
    Gradient lineGradient;
    lineGradient.SetType(GradientType::LINEAR);
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    // angle
    std::optional<float> degree;
    GetAngle("angle", argsPtrItem, degree);
    if (degree) {
        lineGradient.GetLinearGradient().angle = AnimatableDimension(degree.value(), DimensionUnit::PX, option);
        degree.reset();
    }
    // direction
    auto direction =
        static_cast<GradientDirection>(argsPtrItem->GetInt("direction", static_cast<int32_t>(GradientDirection::NONE)));
    switch (direction) {
        case GradientDirection::LEFT:
            lineGradient.GetLinearGradient().linearX = GradientDirection::LEFT;
            break;
        case GradientDirection::RIGHT:
            lineGradient.GetLinearGradient().linearX = GradientDirection::RIGHT;
            break;
        case GradientDirection::TOP:
            lineGradient.GetLinearGradient().linearY = GradientDirection::TOP;
            break;
        case GradientDirection::BOTTOM:
            lineGradient.GetLinearGradient().linearY = GradientDirection::BOTTOM;
            break;
        case GradientDirection::LEFT_TOP:
            lineGradient.GetLinearGradient().linearX = GradientDirection::LEFT;
            lineGradient.GetLinearGradient().linearY = GradientDirection::TOP;
            break;
        case GradientDirection::LEFT_BOTTOM:
            lineGradient.GetLinearGradient().linearX = GradientDirection::LEFT;
            lineGradient.GetLinearGradient().linearY = GradientDirection::BOTTOM;
            break;
        case GradientDirection::RIGHT_TOP:
            lineGradient.GetLinearGradient().linearX = GradientDirection::RIGHT;
            lineGradient.GetLinearGradient().linearY = GradientDirection::TOP;
            break;
        case GradientDirection::RIGHT_BOTTOM:
            lineGradient.GetLinearGradient().linearX = GradientDirection::RIGHT;
            lineGradient.GetLinearGradient().linearY = GradientDirection::BOTTOM;
            break;
        case GradientDirection::NONE:
        case GradientDirection::START_TO_END:
        case GradientDirection::END_TO_START:
        default:
            break;
    }
    // repeating
    auto repeating = argsPtrItem->GetBool("repeating", false);
    lineGradient.SetRepeat(repeating);
    // color stops
    GetGradientColorStops(lineGradient, argsPtrItem->GetValue("colors"));
    auto decoration = GetBackDecoration();
    if (decoration) {
        decoration->SetGradient(lineGradient);
    }
}

void JSViewAbstract::JsRadialGradient(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return;
    }

    auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
    if (!argsPtrItem || argsPtrItem->IsNull()) {
        LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
        info.ReturnSelf();
        return;
    }

    Gradient radialGradient;
    radialGradient.SetType(GradientType::RADIAL);
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    // center
    auto center = argsPtrItem->GetValue("center");
    if (center && !center->IsNull() && center->IsArray() && center->GetArraySize() == 2) {
        Dimension value;
        if (ParseJsonDimensionVp(center->GetArrayItem(0), value)) {
            radialGradient.GetRadialGradient().radialCenterX = AnimatableDimension(value, option);
            if (value.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                radialGradient.GetRadialGradient().radialCenterX =
                    AnimatableDimension(value.Value() * 100.0, DimensionUnit::PERCENT, option);
            }
        }
        if (ParseJsonDimensionVp(center->GetArrayItem(1), value)) {
            radialGradient.GetRadialGradient().radialCenterY = AnimatableDimension(value, option);
            if (value.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                radialGradient.GetRadialGradient().radialCenterY =
                    AnimatableDimension(value.Value() * 100.0, DimensionUnit::PERCENT, option);
            }
        }
    }
    // radius
    Dimension radius;
    if (ParseJsonDimensionVp(argsPtrItem->GetValue("radius"), radius)) {
        radialGradient.GetRadialGradient().radialVerticalSize = AnimatableDimension(radius, option);
        radialGradient.GetRadialGradient().radialHorizontalSize = AnimatableDimension(radius, option);
    }
    // repeating
    auto repeating = argsPtrItem->GetBool("repeating", false);
    radialGradient.SetRepeat(repeating);
    // color stops
    GetGradientColorStops(radialGradient, argsPtrItem->GetValue("colors"));
    auto decoration = GetBackDecoration();
    if (decoration) {
        decoration->SetGradient(radialGradient);
    }
}

void JSViewAbstract::JsSweepGradient(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return;
    }

    auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
    if (!argsPtrItem || argsPtrItem->IsNull()) {
        LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
        info.ReturnSelf();
        return;
    }

    Gradient sweepGradient;
    sweepGradient.SetType(GradientType::SWEEP);
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    // center
    auto center = argsPtrItem->GetValue("center");
    if (center && !center->IsNull() && center->IsArray() && center->GetArraySize() == 2) {
        Dimension value;
        if (ParseJsonDimensionVp(center->GetArrayItem(0), value)) {
            sweepGradient.GetSweepGradient().centerX = AnimatableDimension(value, option);
            if (value.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                sweepGradient.GetSweepGradient().centerX = AnimatableDimension(
                    value.Value() * 100.0, DimensionUnit::PERCENT, option);
            }
        }
        if (ParseJsonDimensionVp(center->GetArrayItem(1), value)) {
            sweepGradient.GetSweepGradient().centerY = AnimatableDimension(value, option);
            if (value.Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                sweepGradient.GetSweepGradient().centerY = AnimatableDimension(
                    value.Value() * 100.0, DimensionUnit::PERCENT, option);
            }
        }
    }
    std::optional<float> degree;
    // start
    GetAngle("start", argsPtrItem, degree);
    if (degree) {
        sweepGradient.GetSweepGradient().startAngle = AnimatableDimension(degree.value(), DimensionUnit::PX, option);
        degree.reset();
    }
    // end
    GetAngle("end", argsPtrItem, degree);
    if (degree) {
        sweepGradient.GetSweepGradient().endAngle = AnimatableDimension(degree.value(), DimensionUnit::PX, option);
        degree.reset();
    }
    // rotation
    GetAngle("rotation", argsPtrItem, degree);
    if (degree) {
        sweepGradient.GetSweepGradient().rotation = AnimatableDimension(degree.value(), DimensionUnit::PX, option);
        degree.reset();
    }
    // repeating
    auto repeating = argsPtrItem->GetBool("repeating", false);
    sweepGradient.SetRepeat(repeating);
    // color stops
    GetGradientColorStops(sweepGradient, argsPtrItem->GetValue("colors"));
    auto decoration = GetBackDecoration();
    if (decoration) {
        decoration->SetGradient(sweepGradient);
    }
}

void JSViewAbstract::JsMotionPath(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return;
    }
    auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
    MotionPathOption motionPathOption;
    if (ParseMotionPath(argsPtrItem, motionPathOption)) {
        if (motionPathOption.GetRotate()) {
            ViewStackProcessor::GetInstance()->GetTransformComponent();
        }
        auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
        flexItem->SetMotionPathOption(motionPathOption);
    } else {
        LOGE("parse motionPath failed. %{public}s", info[0]->ToString().c_str());
    }
}

void JSViewAbstract::JsShadow(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return;
    }
    auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
    if (!argsPtrItem || argsPtrItem->IsNull()) {
        LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
        info.ReturnSelf();
        return;
    }
    double radius = 0.0;
    ParseJsonDouble(argsPtrItem->GetValue("radius"), radius);
    if (LessOrEqual(radius, 0.0)) {
        LOGE("JsShadow Parse radius failed, radius = %{public}lf", radius);
        return;
    }
    std::vector<Shadow> shadows(1);
    shadows.begin()->SetBlurRadius(radius);
    Dimension offsetX;
    if (ParseJsonDimensionVp(argsPtrItem->GetValue("offsetX"), offsetX)) {
        shadows.begin()->SetOffsetX(offsetX.Value());
    }
    Dimension offsetY;
    if (ParseJsonDimensionVp(argsPtrItem->GetValue("offsetY"), offsetY)) {
        shadows.begin()->SetOffsetY(offsetY.Value());
    }
    Color color;
    if (ParseJsonColor(argsPtrItem->GetValue("color"), color)) {
        shadows.begin()->SetColor(color);
    }
    auto backDecoration = GetBackDecoration();
    backDecoration->SetShadows(shadows);
}

void JSViewAbstract::JsGrayScale(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    if (GreatNotEqual(value.Value(), 1.0)) {
        value.SetValue(1.0);
    }

    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetGrayScale(value);
}

void JSViewAbstract::JsBrightness(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (value.Value() == 0) {
        value.SetValue(EPSILON);
    }
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetBrightness(value);
}

void JSViewAbstract::JsContrast(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (value.Value() == 0) {
        value.SetValue(EPSILON);
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetContrast(value);
}

void JSViewAbstract::JsSaturate(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (value.Value() == 0) {
        value.SetValue(EPSILON);
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetSaturate(value);
}

void JSViewAbstract::JsSepia(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetSepia(value);
}

void JSViewAbstract::JsInvert(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetInvert(value);
}

void JSViewAbstract::JsHueRotate(const JSCallbackInfo& info)
{
    std::optional<float> degree;
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    if (info[0]->IsString()) {
        degree = static_cast<float>(StringUtils::StringToDegree(info[0]->ToString()));
    } else if (info[0]->IsNumber()) {
        degree = static_cast<float>(info[0]->ToNumber<uint32_t>());
    } else {
        LOGE("Invalid value type");
    }
    float deg = 0.0;
    if (degree) {
        deg = degree.value();
        degree.reset();
    }
    auto decoration = GetFrontDecoration();
    if (decoration) {
        decoration->SetHueRotate(deg);
    }
}

void JSViewAbstract::JsClip(const JSCallbackInfo& info)
{
    if (info.Length() > 0) {
        auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
        if (info[0]->IsObject()) {
            JSShapeAbstract* clipShape = JSRef<JSObject>::Cast(info[0])->Unwrap<JSShapeAbstract>();
            if (clipShape == nullptr) {
                LOGE("clipShape is null.");
                return;
            }
            auto clipPath = AceType::MakeRefPtr<ClipPath>();
            clipPath->SetBasicShape(clipShape->GetBasicShape());
            box->SetClipPath(clipPath);
        } else if (info[0]->IsBoolean()) {
            box->SetBoxClipFlag(info[0]->ToBoolean());
        }
    }
}

void JSViewAbstract::JsMask(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSShapeAbstract* maskShape = JSRef<JSObject>::Cast(info[0])->Unwrap<JSShapeAbstract>();
        if (maskShape == nullptr) {
            return;
        }
        auto maskPath = AceType::MakeRefPtr<MaskPath>();
        maskPath->SetBasicShape(maskShape->GetBasicShape());
        auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
        box->SetMask(maskPath);
    }
}

void JSViewAbstract::JsFocusable(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        LOGE("The info is wrong, it is supposed to be an boolean");
        return;
    }

    auto focusComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    if (!focusComponent) {
        LOGE("The focusComponent is null");
        return;
    } else {
        focusComponent->SetFocusable(info[0]->ToBoolean());
    }

}

void JSViewAbstract::JsOnFocusMove(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        RefPtr<JsFocusFunction> jsOnFocusMove = AceType::MakeRefPtr<JsFocusFunction>(JSRef<JSFunc>::Cast(args[0]));
        auto onFocusMove = [execCtx = args.GetExecutionContext(), func = std::move(jsOnFocusMove)](int info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(info);
        };
        auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
        focusableComponent->SetOnFocusMove(onFocusMove);
    }
}

void JSViewAbstract::JsOnFocus(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        RefPtr<JsFocusFunction> jsOnFocus = AceType::MakeRefPtr<JsFocusFunction>(JSRef<JSFunc>::Cast(args[0]));
        auto onFocus = [execCtx = args.GetExecutionContext(), func = std::move(jsOnFocus)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute();
        };
        auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
        focusableComponent->SetOnFocus(onFocus);
    }
}

void JSViewAbstract::JsOnBlur(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        RefPtr<JsFocusFunction> jsOnBlur = AceType::MakeRefPtr<JsFocusFunction>(JSRef<JSFunc>::Cast(args[0]));
        auto onBlur_ = [execCtx = args.GetExecutionContext(), func = std::move(jsOnBlur)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute();
        };
        auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
        focusableComponent->SetOnBlur(onBlur_);
    }
}

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
void JSViewAbstract::JsDebugLine(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsString()) {
        LOGE("info[0] is not a string.");
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    if (component) {
        component->SetDebugLine(info[0]->ToString());
    }
}
#endif

void JSViewAbstract::JsOpacityPassThrough(const JSCallbackInfo& info)
{
    JSViewAbstract::JsOpacity(info);
    if (ViewStackProcessor::GetInstance()->HasDisplayComponent()) {
        auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
        display->DisableLayer(true);
    }
}

void JSViewAbstract::JsTransitionPassThrough(const JSCallbackInfo& info)
{
    JSViewAbstract::JsTransition(info);
    if (ViewStackProcessor::GetInstance()->HasDisplayComponent()) {
        auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
        display->DisableLayer(true);
    }
}

void JSViewAbstract::JsAccessibilityGroup(bool accessible)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    if (!component) {
        return;
    }

    int32_t inspectorId = StringUtils::StringToInt(component->GetInspectorId());
    auto accessibilityNode = GetAccessibilityNodeById(inspectorId);
    if (accessibilityNode) {
        accessibilityNode->SetAccessible(accessible);
    }
}

void JSViewAbstract::JsAccessibilityText(const std::string& text)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    if (!component) {
        return;
    }

    int32_t inspectorId = StringUtils::StringToInt(component->GetInspectorId());
    auto accessibilityNode = GetAccessibilityNodeById(inspectorId);
    if (accessibilityNode) {
        accessibilityNode->SetAccessibilityLabel(text);
    }
}

void JSViewAbstract::JsAccessibilityDescription(const std::string& description)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    if (!component) {
        return;
    }

    int32_t inspectorId = StringUtils::StringToInt(component->GetInspectorId());
    auto accessibilityNode = GetAccessibilityNodeById(inspectorId);
    if (accessibilityNode) {
        accessibilityNode->SetAccessibilityHint(description);
    }
}

void JSViewAbstract::JsAccessibilityImportance(const std::string& importance)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    if (!component) {
        return;
    }

    int32_t inspectorId = StringUtils::StringToInt(component->GetInspectorId());
    auto accessibilityNode = GetAccessibilityNodeById(inspectorId);
    if (accessibilityNode) {
        accessibilityNode->SetImportantForAccessibility(importance);
    }
}

RefPtr<AccessibilityNode> JSViewAbstract::GetAccessibilityNodeById(int32_t nodeId)
{
    auto container = Container::Current();
    if (!container) {
        LOGE("Container is null.");
        return nullptr;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        LOGE("PipelineContext is null.");
        return nullptr;
    }

    auto accessibilityManager = pipelineContext->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("SetAccessibilityNode accessibilityManager is null.");
        return nullptr;
    }

    return accessibilityManager->GetAccessibilityNodeById(nodeId);
}

void JSViewAbstract::JSBind()
{
    JSClass<JSViewAbstract>::Declare("JSViewAbstract");

    // staticmethods
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSViewAbstract>::StaticMethod("pop", &JSViewAbstract::Pop, opt);

    JSClass<JSViewAbstract>::StaticMethod("width", &JSViewAbstract::JsWidth);
    JSClass<JSViewAbstract>::StaticMethod("height", &JSViewAbstract::JsHeight);
    JSClass<JSViewAbstract>::StaticMethod("size", &JSViewAbstract::JsSize);
    JSClass<JSViewAbstract>::StaticMethod("constraintSize", &JSViewAbstract::JsConstraintSize);
    JSClass<JSViewAbstract>::StaticMethod("layoutPriority", &JSViewAbstract::JsLayoutPriority);
    JSClass<JSViewAbstract>::StaticMethod("layoutWeight", &JSViewAbstract::JsLayoutWeight);

    JSClass<JSViewAbstract>::StaticMethod("margin", &JSViewAbstract::JsMargin);
    JSClass<JSViewAbstract>::StaticMethod("marginTop", &JSViewAbstract::SetMarginTop, opt);
    JSClass<JSViewAbstract>::StaticMethod("marginBottom", &JSViewAbstract::SetMarginBottom, opt);
    JSClass<JSViewAbstract>::StaticMethod("marginLeft", &JSViewAbstract::SetMarginLeft, opt);
    JSClass<JSViewAbstract>::StaticMethod("marginRight", &JSViewAbstract::SetMarginRight, opt);

    JSClass<JSViewAbstract>::StaticMethod("padding", &JSViewAbstract::JsPadding);
    JSClass<JSViewAbstract>::StaticMethod("paddingTop", &JSViewAbstract::SetPaddingTop, opt);
    JSClass<JSViewAbstract>::StaticMethod("paddingBottom", &JSViewAbstract::SetPaddingBottom, opt);
    JSClass<JSViewAbstract>::StaticMethod("paddingLeft", &JSViewAbstract::SetPaddingLeft, opt);
    JSClass<JSViewAbstract>::StaticMethod("paddingRight", &JSViewAbstract::SetPaddingRight, opt);

    JSClass<JSViewAbstract>::StaticMethod("backgroundColor", &JSViewAbstract::JsBackgroundColor);
    JSClass<JSViewAbstract>::StaticMethod("backgroundImage", &JSViewAbstract::JsBackgroundImage);
    JSClass<JSViewAbstract>::StaticMethod("backgroundImageSize", &JSViewAbstract::JsBackgroundImageSize);
    JSClass<JSViewAbstract>::StaticMethod("backgroundImagePosition", &JSViewAbstract::JsBackgroundImagePosition);
    JSClass<JSViewAbstract>::StaticMethod("borderStyle", &JSViewAbstract::SetBorderStyle, opt);
    JSClass<JSViewAbstract>::StaticMethod("borderColor", &JSViewAbstract::JsBorderColor);
    JSClass<JSViewAbstract>::StaticMethod("border", &JSViewAbstract::JsBorder);
    JSClass<JSViewAbstract>::StaticMethod("borderWidth", &JSViewAbstract::JsBorderWidth);
    JSClass<JSViewAbstract>::StaticMethod("borderRadius", &JSViewAbstract::JsBorderRadius);

    JSClass<JSViewAbstract>::StaticMethod("scale", &JSViewAbstract::JsScale);
    JSClass<JSViewAbstract>::StaticMethod("scaleX", &JSViewAbstract::JsScaleX);
    JSClass<JSViewAbstract>::StaticMethod("scaleY", &JSViewAbstract::JsScaleY);
    JSClass<JSViewAbstract>::StaticMethod("opacity", &JSViewAbstract::JsOpacity);
    JSClass<JSViewAbstract>::StaticMethod("rotate", &JSViewAbstract::JsRotate);
    JSClass<JSViewAbstract>::StaticMethod("rotateX", &JSViewAbstract::JsRotateX);
    JSClass<JSViewAbstract>::StaticMethod("rotateY", &JSViewAbstract::JsRotateY);
    JSClass<JSViewAbstract>::StaticMethod("translate", &JSViewAbstract::JsTranslate);
    JSClass<JSViewAbstract>::StaticMethod("translateX", &JSViewAbstract::JsTranslateX);
    JSClass<JSViewAbstract>::StaticMethod("translateY", &JSViewAbstract::JsTranslateY);
    JSClass<JSViewAbstract>::StaticMethod("transform", &JSViewAbstract::JsTransform);
    JSClass<JSViewAbstract>::StaticMethod("transition", &JSViewAbstract::JsTransition);

    JSClass<JSViewAbstract>::StaticMethod("align", &JSViewAbstract::JsAlign);
    JSClass<JSViewAbstract>::StaticMethod("position", &JSViewAbstract::JsPosition);
    JSClass<JSViewAbstract>::StaticMethod("markAnchor", &JSViewAbstract::JsMarkAnchor);
    JSClass<JSViewAbstract>::StaticMethod("offset", &JSViewAbstract::JsOffset);
    JSClass<JSViewAbstract>::StaticMethod("enabled", &JSViewAbstract::JsEnabled);
    JSClass<JSViewAbstract>::StaticMethod("aspectRatio", &JSViewAbstract::JsAspectRatio);
    JSClass<JSViewAbstract>::StaticMethod("overlay", &JSViewAbstract::JsOverlay);

    JSClass<JSViewAbstract>::StaticMethod("blur", &JSViewAbstract::JsBlur);
    JSClass<JSViewAbstract>::StaticMethod("colorBlend", &JSViewAbstract::JsColorBlend);
    JSClass<JSViewAbstract>::StaticMethod("backdropBlur", &JSViewAbstract::JsBackdropBlur);
    JSClass<JSViewAbstract>::StaticMethod("windowBlur", &JSViewAbstract::JsWindowBlur);
    JSClass<JSViewAbstract>::StaticMethod("visibility", &JSViewAbstract::SetVisibility);
    JSClass<JSViewAbstract>::StaticMethod("flexBasis", &JSViewAbstract::JsFlexBasis);
    JSClass<JSViewAbstract>::StaticMethod("flexGrow", &JSViewAbstract::JsFlexGrow);
    JSClass<JSViewAbstract>::StaticMethod("flexShrink", &JSViewAbstract::JsFlexShrink);
    JSClass<JSViewAbstract>::StaticMethod("alignSelf", &JSViewAbstract::JsAlignSelf);
    JSClass<JSViewAbstract>::StaticMethod("displayPriority", &JSViewAbstract::JsDisplayPriority);
    JSClass<JSViewAbstract>::StaticMethod("useAlign", &JSViewAbstract::JsUseAlign);
    JSClass<JSViewAbstract>::StaticMethod("zIndex", &JSViewAbstract::JsZIndex);
    JSClass<JSViewAbstract>::StaticMethod("sharedTransition", &JSViewAbstract::JsSharedTransition);
    JSClass<JSViewAbstract>::StaticMethod("navigationTitle", &JSViewAbstract::SetNavigationTitle, opt);
    JSClass<JSViewAbstract>::StaticMethod("navigationSubTitle", &JSViewAbstract::SetNavigationSubTitle, opt);
    JSClass<JSViewAbstract>::StaticMethod("hideNavigationBar", &JSViewAbstract::SetHideNavigationBar, opt);
    JSClass<JSViewAbstract>::StaticMethod(
        "hideNavigationBackButton", &JSViewAbstract::SetHideNavigationBackButton, opt);
    JSClass<JSViewAbstract>::StaticMethod("hideToolBar", &JSViewAbstract::SetHideToolBar, opt);
    JSClass<JSViewAbstract>::StaticMethod("direction", &JSViewAbstract::SetDirection, opt);
    JSClass<JSViewAbstract>::CustomStaticMethod("toolBar", &JSViewAbstract::JsToolBar);
#ifndef WEARABLE_PRODUCT
    JSClass<JSViewAbstract>::StaticMethod("bindPopup", &JSViewAbstract::JsBindPopup);
#endif

    JSClass<JSViewAbstract>::StaticMethod("bindMenu", &JSViewAbstract::JsBindMenu);
    JSClass<JSViewAbstract>::StaticMethod("onDrag", &JSViewAbstract::JsOnDrag);
    JSClass<JSViewAbstract>::StaticMethod("onDragEnter", &JSViewAbstract::JsOnDragEnter);
    JSClass<JSViewAbstract>::StaticMethod("onDragMove", &JSViewAbstract::JsOnDragMove);
    JSClass<JSViewAbstract>::StaticMethod("onDragLeave", &JSViewAbstract::JsOnDragLeave);
    JSClass<JSViewAbstract>::StaticMethod("onDrop", &JSViewAbstract::JsOnDrop);

    JSClass<JSViewAbstract>::StaticMethod("linearGradient", &JSViewAbstract::JsLinearGradient);
    JSClass<JSViewAbstract>::StaticMethod("sweepGradient", &JSViewAbstract::JsSweepGradient);
    JSClass<JSViewAbstract>::StaticMethod("radialGradient", &JSViewAbstract::JsRadialGradient);
    JSClass<JSViewAbstract>::StaticMethod("motionPath", &JSViewAbstract::JsMotionPath);
    JSClass<JSViewAbstract>::StaticMethod("gridSpan", &JSViewAbstract::JsGridSpan);
    JSClass<JSViewAbstract>::StaticMethod("gridOffset", &JSViewAbstract::JsGridOffset);
    JSClass<JSViewAbstract>::StaticMethod("useSizeType", &JSViewAbstract::JsUseSizeType);
    JSClass<JSViewAbstract>::StaticMethod("shadow", &JSViewAbstract::JsShadow);
    JSClass<JSViewAbstract>::StaticMethod("grayscale", &JSViewAbstract::JsGrayScale);
    JSClass<JSViewAbstract>::StaticMethod("focusable", &JSViewAbstract::JsFocusable);
    JSClass<JSViewAbstract>::StaticMethod("onFocusMove", &JSViewAbstract::JsOnFocusMove);
    JSClass<JSViewAbstract>::StaticMethod("onFocus", &JSViewAbstract::JsOnFocus);
    JSClass<JSViewAbstract>::StaticMethod("onBlur", &JSViewAbstract::JsOnBlur);
    JSClass<JSViewAbstract>::StaticMethod("brightness", &JSViewAbstract::JsBrightness);
    JSClass<JSViewAbstract>::StaticMethod("contrast", &JSViewAbstract::JsContrast);
    JSClass<JSViewAbstract>::StaticMethod("saturate", &JSViewAbstract::JsSaturate);
    JSClass<JSViewAbstract>::StaticMethod("sepia", &JSViewAbstract::JsSepia);
    JSClass<JSViewAbstract>::StaticMethod("invert", &JSViewAbstract::JsInvert);
    JSClass<JSViewAbstract>::StaticMethod("hueRotate", &JSViewAbstract::JsHueRotate);
    JSClass<JSViewAbstract>::StaticMethod("clip", &JSViewAbstract::JsClip);
    JSClass<JSViewAbstract>::StaticMethod("mask", &JSViewAbstract::JsMask);
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    JSClass<JSViewAbstract>::StaticMethod("debugLine", &JSViewAbstract::JsDebugLine);
#endif
    JSClass<JSViewAbstract>::StaticMethod("accessibilityGroup", &JSViewAbstract::JsAccessibilityGroup);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityText", &JSViewAbstract::JsAccessibilityText);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityDescription", &JSViewAbstract::JsAccessibilityDescription);
    JSClass<JSViewAbstract>::StaticMethod("accessibilityImportance", &JSViewAbstract::JsAccessibilityImportance);
    JSClass<JSViewAbstract>::StaticMethod("onAccessibility", &JSInteractableView::JsOnAccessibility);
    JSClass<JSViewAbstract>::StaticMethod("geometryTransition", &JSViewAbstract::JsGeometryTransition);
}

RefPtr<Decoration> JSViewAbstract::GetFrontDecoration()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto decoration = box->GetFrontDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
        box->SetFrontDecoration(decoration);
    }

    return decoration;
}

RefPtr<Decoration> JSViewAbstract::GetBackDecoration()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto decoration = box->GetBackDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
        box->SetBackDecoration(decoration);
    }
    return decoration;
}

const Border& JSViewAbstract::GetBorder()
{
    return GetBackDecoration()->GetBorder();
}

RefPtr<NavigationDeclaration> JSViewAbstract::GetNavigationDeclaration()
{
    auto navigationDeclarationCollector = ViewStackProcessor::GetInstance()->GetNavigationDeclarationCollector();
    auto declaration = navigationDeclarationCollector->GetDeclaration();
    if (!declaration) {
        declaration = AceType::MakeRefPtr<NavigationDeclaration>();
        navigationDeclarationCollector->SetDeclaration(declaration);
    }
    return declaration;
}

void JSViewAbstract::SetBorder(const Border& border)
{
    GetBackDecoration()->SetBorder(border);
}

void JSViewAbstract::SetBorderRadius(const Dimension& value, const AnimationOption& option)
{
    Border border = GetBorder();
    border.SetBorderRadius(Radius(AnimatableDimension(value, option)));
    SetBorder(border);
}

void JSViewAbstract::SetBorderStyle(int32_t style)
{
    BorderStyle borderStyle = BorderStyle::SOLID;

    if (static_cast<int32_t>(BorderStyle::SOLID) == style) {
        borderStyle = BorderStyle::SOLID;
    } else if (static_cast<int32_t>(BorderStyle::DASHED) == style) {
        borderStyle = BorderStyle::DASHED;
    } else if (static_cast<int32_t>(BorderStyle::DOTTED) == style) {
        borderStyle = BorderStyle::DOTTED;
    } else {
        borderStyle = BorderStyle::NONE;
    }
    Border border = GetBorder();
    border.SetStyle(borderStyle);
    SetBorder(border);
}

void JSViewAbstract::SetBorderColor(const Color& color, const AnimationOption& option)
{
    auto border = GetBorder();
    border.SetColor(color, option);
    SetBorder(border);
}

void JSViewAbstract::SetBorderWidth(const Dimension& value, const AnimationOption& option)
{
    auto border = GetBorder();
    border.SetWidth(value, option);
    SetBorder(border);
}

void JSViewAbstract::SetMarginTop(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    AnimatableDimension value;
    if (!ParseJsAnimatableDimensionVp(info[0], value)) {
        return;
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetTop(value);
    box->SetMargin(margin);
}

void JSViewAbstract::SetMarginBottom(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    AnimatableDimension value;
    if (!ParseJsAnimatableDimensionVp(info[0], value)) {
        return;
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetBottom(value);
    box->SetMargin(margin);
}

void JSViewAbstract::SetMarginLeft(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    AnimatableDimension value;
    if (!ParseJsAnimatableDimensionVp(info[0], value)) {
        return;
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetLeft(value);
    box->SetMargin(margin);
}

void JSViewAbstract::SetMarginRight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    AnimatableDimension value;
    if (!ParseJsAnimatableDimensionVp(info[0], value)) {
        return;
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetRight(value);
    box->SetMargin(margin);
}

void JSViewAbstract::SetMargins(
    const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    Edge margin(left, top, right, bottom, option);
    box->SetMargin(margin);
}

void JSViewAbstract::SetPaddingTop(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    AnimatableDimension value;
    if (!ParseJsAnimatableDimensionVp(info[0], value)) {
        return;
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetTop(value);
    box->SetPadding(padding);
}

void JSViewAbstract::SetPaddingBottom(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    AnimatableDimension value;
    if (!ParseJsAnimatableDimensionVp(info[0], value)) {
        return;
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetBottom(value);
    box->SetPadding(padding);
}

void JSViewAbstract::SetPaddingLeft(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    AnimatableDimension value;
    if (!ParseJsAnimatableDimensionVp(info[0], value)) {
        return;
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetLeft(value);
    box->SetPadding(padding);
}

void JSViewAbstract::SetPaddingRight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    AnimatableDimension value;
    if (!ParseJsAnimatableDimensionVp(info[0], value)) {
        return;
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetRight(value);
    box->SetPadding(padding);
}

void JSViewAbstract::SetPadding(const Dimension& value)
{
    SetPaddings(value, value, value, value);
}

void JSViewAbstract::SetPaddings(
    const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    Edge padding(left, top, right, bottom, option);
    box->SetPadding(padding);
}

void JSViewAbstract::SetMargin(const Dimension& value)
{
    SetMargins(value, value, value, value);
}

void JSViewAbstract::SetBlur(float radius)
{
    auto decoration = GetFrontDecoration();
    SetBlurRadius(decoration, radius);
}

void JSViewAbstract::SetColorBlend(Color color)
{
    auto decoration = GetFrontDecoration();
    if (decoration) {
        decoration->SetColorBlend(color);
    }
}

void JSViewAbstract::SetBackdropBlur(float radius)
{
    auto decoration = GetBackDecoration();
    SetBlurRadius(decoration, radius);
}

void JSViewAbstract::SetBlurRadius(const RefPtr<Decoration>& decoration, float radius)
{
    if (decoration) {
        AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
        decoration->SetBlurRadius(AnimatableDimension(radius, DimensionUnit::PX, option));
    }
}

void JSViewAbstract::SetWindowBlur(float progress, WindowBlurStyle blurStyle)
{
    auto decoration = GetBackDecoration();
    if (decoration) {
        decoration->SetWindowBlurProgress(progress);
        decoration->SetWindowBlurStyle(blurStyle);
    }
}

void JSViewAbstract::SetNavigationTitle(const std::string& title)
{
    GetNavigationDeclaration()->SetTitle(title);
}

void JSViewAbstract::SetNavigationSubTitle(const std::string& subTitle)
{
    GetNavigationDeclaration()->SetSubTitle(subTitle);
}

void JSViewAbstract::SetHideNavigationBar(bool hide)
{
    GetNavigationDeclaration()->SetHideBar(hide);
}

void JSViewAbstract::SetHideNavigationBackButton(bool hide)
{
    GetNavigationDeclaration()->SetHideBarBackButton(hide);
}

void JSViewAbstract::SetHideToolBar(bool hide)
{
    GetNavigationDeclaration()->SetHideToolBar(hide);
}

bool JSViewAbstract::ParseJsonDimension(const std::unique_ptr<JsonValue>& jsonValue, Dimension& result,
    DimensionUnit defaultUnit)
{
    if (!jsonValue || jsonValue->IsNull()) {
        LOGD("invalid json value");
        return false;
    }
    if (!jsonValue->IsNumber() && !jsonValue->IsString() && !jsonValue->IsObject()) {
        LOGE("json value is not numner, string or object");
        return false;
    }
    if (jsonValue->IsNumber()) {
        result = Dimension(jsonValue->GetDouble(), defaultUnit);
        return true;
    }
    if (jsonValue->IsString()) {
        result = StringUtils::StringToDimensionWithUnit(jsonValue->GetString(), defaultUnit);
        return true;
    }
    auto resVal = JsonUtil::ParseJsonString(jsonValue->ToString());
    auto resId = resVal->GetValue("id");
    if (!resId || !resId->IsNumber()) {
        LOGE("invalid resource id");
        return false;
    }
    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGE("themeConstants is nullptr");
        return false;
    }
    result = themeConstants->GetDimension(resId->GetUInt());
    return true;
}

bool JSViewAbstract::ParseJsonDimensionVp(const std::unique_ptr<JsonValue>& jsonValue, Dimension& result)
{
    return ParseJsonDimension(jsonValue, result, DimensionUnit::VP);
}

bool JSViewAbstract::ParseJsonDouble(const std::unique_ptr<JsonValue>& jsonValue, double& result)
{
    if (!jsonValue || jsonValue->IsNull()) {
        LOGD("invalid json value");
        return false;
    }
    if (!jsonValue->IsNumber() && !jsonValue->IsString() && !jsonValue->IsObject()) {
        LOGE("json value is not numner, string or object");
        return false;
    }
    if (jsonValue->IsNumber()) {
        result = jsonValue->GetDouble();
        return true;
    }
    if (jsonValue->IsString()) {
        result = StringUtils::StringToDouble(jsonValue->GetString());
        return true;
    }
    auto resVal = JsonUtil::ParseJsonString(jsonValue->ToString());
    auto resId = resVal->GetValue("id");
    if (!resId || !resId->IsNumber()) {
        LOGE("invalid resource id");
        return false;
    }
    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }
    result = themeConstants->GetDouble(resId->GetUInt());
    return true;
}

bool JSViewAbstract::ParseJsonColor(const std::unique_ptr<JsonValue>& jsonValue, Color& result)
{
    if (!jsonValue || jsonValue->IsNull()) {
        LOGD("invalid json value");
        return false;
    }
    if (!jsonValue->IsNumber() && !jsonValue->IsString() && !jsonValue->IsObject()) {
        LOGE("json value is not numner, string or object");
        return false;
    }
    if (jsonValue->IsNumber()) {
        result = Color(ColorAlphaAdapt(jsonValue->GetUInt()));
        return true;
    }
    if (jsonValue->IsString()) {
        result = Color::FromString(jsonValue->GetString());
        return true;
    }
    auto resVal = JsonUtil::ParseJsonString(jsonValue->ToString());
    auto resId = resVal->GetValue("id");
    if (!resId || !resId->IsNumber()) {
        LOGE("invalid resource id");
        return false;
    }
    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGW("themeConstants is nullptr");
        return false;
    }
    result = themeConstants->GetColor(resId->GetUInt());
    return true;
}

void JSViewAbstract::GetAngle(
    const std::string& key, const std::unique_ptr<JsonValue>& jsonValue, std::optional<float>& angle)
{
    auto value = jsonValue->GetValue(key);
    if (value && value->IsString()) {
        angle = static_cast<float>(StringUtils::StringToDegree(value->GetString()));
    } else if (value && value->IsNumber()) {
        angle = static_cast<float>(value->GetDouble());
    } else {
        LOGE("Invalid value type");
    }
}

void JSViewAbstract::GetGradientColorStops(Gradient& gradient, const std::unique_ptr<JsonValue>& colorStops)
{
    if (!colorStops || colorStops->IsNull() || !colorStops->IsArray()) {
        return;
    }

    for (int32_t i = 0; i < colorStops->GetArraySize(); i++) {
        GradientColor gradientColor;
        auto item = colorStops->GetArrayItem(i);
        if (item && !item->IsNull() && item->IsArray() && item->GetArraySize() >= 1) {
            auto colorParams = item->GetArrayItem(0);
            // color
            Color color;
            if (!ParseJsonColor(colorParams, color)) {
                LOGE("parse colorParams failed");
                continue;
            }
            gradientColor.SetColor(color);
            gradientColor.SetHasValue(false);
            // stop value
            if (item->GetArraySize() <= 1) {
                continue;
            }
            auto stopValue = item->GetArrayItem(1);
            double value = 0.0;
            if (ParseJsonDouble(stopValue, value)) {
                value = std::clamp(value, 0.0, 1.0);
                gradientColor.SetHasValue(true);
                //  [0, 1] -> [0, 100.0];
                gradientColor.SetDimension(Dimension(value * 100.0, DimensionUnit::PERCENT));
            }

            gradient.AddColor(gradientColor);
        }
    }
}

void JSViewAbstract::SetDirection(const std::string& dir)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    if (!box) {
        return;
    }

    if (dir == "Ltr") {
        box->SetTextDirection(TextDirection::LTR);
    } else if (dir == "Rtl") {
        box->SetTextDirection(TextDirection::RTL);
    } else if (dir == "Auto") {
        box->SetTextDirection(
            AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR);
    }
}

#ifdef USE_QUICKJS_ENGINE
JSValue JSViewAbstract::JsToolBar(JSContext* ctx, JSValueConst thisValue, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc < 1)) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong: less than one parameter");
    }
    if (!JS_IsObject(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong: parameter of type object expected");
    }
    auto argsPtrItem = JsonUtil::ParseJsonString(ScopedString::Stringify(argv[0]));
    if (!argsPtrItem) {
        LOGE("Js Parse Border failed. argsPtr is null. %s", ScopedString::Stringify(argv[0]).c_str());
        return thisValue;
    }
    if (argsPtrItem->IsNull()) {
        LOGE("Js Parse Border failed. argsPtr is null. %s", ScopedString::Stringify(argv[0]).c_str());
        return thisValue;
    }

    return thisValue;
}
#elif USE_V8_ENGINE
void JSViewAbstract::JsToolBar(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    auto context = isolate->GetCurrentContext();
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return;
    }

    auto object = info[0]->ToObject(context).ToLocalChecked();
    auto items = object->Get(context, v8::String::NewFromUtf8(isolate, "items").ToLocalChecked()).ToLocalChecked();
    if (!items->IsObject() || !items->IsArray()) {
        LOGE("arg format error: not find items");
        return;
    }
    auto itemsObject = items->ToObject(context).ToLocalChecked();
    auto length = itemsObject->Get(context, v8::String::NewFromUtf8(isolate, "length").ToLocalChecked())
                      .ToLocalChecked()->Uint32Value(context).ToChecked();
    auto navigationDeclaration = GetNavigationDeclaration();
    for (uint32_t i = 0; i < length; i++) {
        auto item = itemsObject->Get(context, i).ToLocalChecked();
        if (!item->IsObject()) {
            LOGE("tab bar item is not json object");
            continue;
        }

        ToolBarItem toolBarItem;
        auto itemObject = item->ToObject(context).ToLocalChecked();

        auto itemValueObject =
            itemObject->Get(context, v8::String::NewFromUtf8(isolate, "value").ToLocalChecked()).ToLocalChecked();
        if (itemValueObject->IsString()) {
            toolBarItem.value = *v8::String::Utf8Value(isolate, itemValueObject->ToString(context).ToLocalChecked());
        }

        auto itemIconObject =
            itemObject->Get(context, v8::String::NewFromUtf8(isolate, "icon").ToLocalChecked()).ToLocalChecked();
        if (itemIconObject->IsString()) {
            toolBarItem.icon = *v8::String::Utf8Value(isolate, itemIconObject->ToString(context).ToLocalChecked());
        }

        auto itemActionValue =
            itemObject->Get(context, v8::String::NewFromUtf8(isolate, "action").ToLocalChecked()).ToLocalChecked();
        if (itemActionValue->IsFunction()) {
            auto tabBarItemActionFunc = AceType::MakeRefPtr<V8EventFunction<BaseEventInfo, 0>>(
                v8::Local<v8::Function>::Cast(itemActionValue), nullptr);
            toolBarItem.action =
                EventMarker([func = std::move(tabBarItemActionFunc)]() { func->execute(); }, "tabBarItemClick", 0);
        }
        navigationDeclaration->AddToolBarItem(toolBarItem);
    }
    info.GetReturnValue().Set(info.This());
}
#elif USE_ARK_ENGINE
panda::Local<panda::JSValueRef> JSViewAbstract::JsToolBar(panda::EcmaVM* vm, panda::Local<panda::JSValueRef> thisObj,
    const panda::Local<panda::JSValueRef> argv[], int32_t argc, void* data)
{
    return panda::Local<panda::JSValueRef>(panda::JSValueRef::Undefined(vm));
}
#endif // USE_ARK_ENGINE

RefPtr<ThemeConstants> JSViewAbstract::GetThemeConstants()
{
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return nullptr;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        LOGE("pipelineContext is null!");
        return nullptr;
    }
    auto themeManager = pipelineContext->GetThemeManager();
    if (!themeManager) {
        LOGE("themeManager is null!");
        return nullptr;
    }
    return themeManager->GetThemeConstants();
}

} // namespace OHOS::Ace::Framework
