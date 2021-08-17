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

#include <vector>

#include "base/json/json_util.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "core/common/container.h"
#include "core/components/common/properties/motion_path_option.h"

#include "bridge/declarative_frontend/jsview/js_grid_container.h"
#include "bridge/declarative_frontend/jsview/js_view_register.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/ace_application_info.h"
#include "core/components/common/layout/align_declaration.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr int32_t MAX_ALIGN_VALUE = 8;

void ParseJsScale(std::unique_ptr<JsonValue>& argsPtrItem, float& scaleX, float& scaleY, float& scaleZ,
    Dimension& centerX, Dimension& centerY)
{
    scaleX = static_cast<float>(argsPtrItem->GetDouble("x", 1.0f));
    scaleY = static_cast<float>(argsPtrItem->GetDouble("y", 1.0f));
    scaleZ = static_cast<float>(argsPtrItem->GetDouble("z", 1.0f));
    // if specify centerX
    std::optional<Dimension> length;
    JSViewAbstract::GetDimension("centerX", argsPtrItem, length);
    if (length) {
        centerX = length.value();
        length.reset();
    }
    // if specify centerY
    JSViewAbstract::GetDimension("centerY", argsPtrItem, length);
    if (length) {
        centerY = length.value();
        length.reset();
    }
}

void ParseJsTranslate(
    std::unique_ptr<JsonValue>& argsPtrItem, Dimension& translateX, Dimension& translateY, Dimension& translateZ)
{
    std::optional<Dimension> length;
    JSViewAbstract::GetDimension("x", argsPtrItem, length);
    if (length) {
        translateX = length.value();
        length.reset();
    }

    JSViewAbstract::GetDimension("y", argsPtrItem, length);
    if (length) {
        translateY = length.value();
        length.reset();
    }

    JSViewAbstract::GetDimension("z", argsPtrItem, length);
    if (length) {
        translateZ = length.value();
        length.reset();
    }
}

void ParseJsRotate(std::unique_ptr<JsonValue>& argsPtrItem, float& dx, float& dy, float& dz, Dimension& centerX,
    Dimension& centerY, std::optional<float>& angle)
{
    // default: dx, dy, dz (0.0, 0.0, 0.0)
    dx = static_cast<float>(argsPtrItem->GetDouble("x", 0.0f));
    dy = static_cast<float>(argsPtrItem->GetDouble("y", 0.0f));
    dz = static_cast<float>(argsPtrItem->GetDouble("z", 0.0f));
    // if specify centerX
    std::optional<Dimension> length;
    JSViewAbstract::GetDimension("centerX", argsPtrItem, length);
    if (length) {
        centerX = length.value();
        length.reset();
    }
    // if specify centerY
    JSViewAbstract::GetDimension("centerY", argsPtrItem, length);
    if (length) {
        centerY = length.value();
    }
    // if specify angle
    JSViewAbstract::GetAngle("angle", argsPtrItem, angle);
}

void ParseAndSetOpacityTransition(const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    if (transitionArgs->Contains("opacity")) {
        double opacity = transitionArgs->GetDouble("opacity", 0.0);
        auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
        if (!display) {
            LOGE("display component is null.");
            return;
        }
        LOGI("JsTransition with type: %{public}d, opacity: %{public}.2f", transitionType, opacity);
        display->SetTransition(transitionType, opacity);
    }
}

void ParseAndSetRotateTransition(const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    if (transitionArgs->Contains("rotate")) {
        auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
        if (!transform) {
            LOGE("transform component is null.");
            return;
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
    }
}

void ParseAndSetScaleTransition(const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    if (transitionArgs->Contains("scale")) {
        auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
        if (!transform) {
            LOGE("transform component is null.");
            return;
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
    }
}

void ParseAndSetTranslateTransition(const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    if (transitionArgs->Contains("translate")) {
        auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
        if (!transform) {
            LOGE("transform component is null.");
            return;
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
    }
}

bool ParseMotionPath(const std::unique_ptr<JsonValue>& argsPtrItem, MotionPathOption& option)
{
    if (argsPtrItem && !argsPtrItem->IsNull()) {
        auto path = argsPtrItem->GetString("path", "");
        if (!path.empty()) {
            option.SetPath(path);
            option.SetBegin(static_cast<float>(argsPtrItem->GetDouble("from", 0.0)));
            option.SetEnd(static_cast<float>(argsPtrItem->GetDouble("to", 1.0)));
            option.SetRotate(argsPtrItem->GetBool("rotatable", false));
            return true;
        }
    }
    return false;
}

void SetBgImgPosition(const BackgroundImagePositionType type, const double valueX, const double valueY,
    BackgroundImagePosition& bgImgPosition)
{
    bgImgPosition.SetSizeTypeX(type);
    bgImgPosition.SetSizeValueX(valueX);
    bgImgPosition.SetSizeTypeY(type);
    bgImgPosition.SetSizeValueY(valueY);
}

} // namespace

uint32_t JSViewAbstract::ColorAlphaAdapt(uint32_t origin)
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
    if (info[0]->IsNumber()) {
        transform->Scale(info[0]->ToNumber<float>(), option);
    } else if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return;
        }
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
    }
}

void JSViewAbstract::JsScaleX(const JSCallbackInfo& info)
{
    LOGD("JsScaleX");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->ScaleX(info[0]->ToNumber<float>(), option);
}

void JSViewAbstract::JsScaleY(const JSCallbackInfo& info)
{
    LOGD("JsScaleY");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->ScaleY(info[0]->ToNumber<float>(), option);
}

void JSViewAbstract::JsOpacity(const JSCallbackInfo& info)
{
    LOGD("js_opacity");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    display->SetOpacity(info[0]->ToNumber<double>(), option);
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
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP);
        transform->Translate(value, value, option);
    } else if (info[0]->IsString()) {
        value = StringUtils::StringToDimension(info[0]->ToString(), true);
        transform->Translate(value, value, option);
    } else if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return;
        }
        // default: x, y, z (0.0, 0.0, 0.0)
        auto translateX = Dimension(0.0);
        auto translateY = Dimension(0.0);
        auto translateZ = Dimension(0.0);
        ParseJsTranslate(argsPtrItem, translateX, translateY, translateZ);
        transform->Translate(translateX, translateY, translateZ, option);
    }
}

void JSViewAbstract::JsTranslateX(const JSCallbackInfo& info)
{
    LOGD("JsTranslateX");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }

    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(info[0]->ToString(), true);
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

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }

    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(info[0]->ToString(), true);
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
    if (info[0]->IsNumber()) {
        transform->RotateZ(info[0]->ToNumber<float>(), option);
    } else if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return;
        }
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
    }
}

void JSViewAbstract::JsRotateX(const JSCallbackInfo& info)
{
    LOGD("JsRotateX");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->RotateX(info[0]->ToNumber<float>(), option);
}

void JSViewAbstract::JsRotateY(const JSCallbackInfo& info)
{
    LOGD("JsRotateX");
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number.");
        return;
    }

    auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->RotateY(info[0]->ToNumber<float>(), option);
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
        matrix[i] = static_cast<float>(array->GetArrayItem(i)->GetDouble());
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
        auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
        if (!display) {
            LOGE("display component is null.");
            return;
        }
        LOGI("JsTransition with default");
        display->SetTransition(TransitionType::ALL, 0.0);
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
    ParseAndSetOpacityTransition(transitionArgs, transitionType);
    ParseAndSetTranslateTransition(transitionArgs, transitionType);
    ParseAndSetScaleTransition(transitionArgs, transitionType);
    ParseAndSetRotateTransition(transitionArgs, transitionType);
}

void JSViewAbstract::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }

    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(info[0]->ToString(), true);
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }

    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    box->SetWidth(value, option);
}

void JSViewAbstract::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }

    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(info[0]->ToString(), true);
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }

    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    box->SetHeight(value, option);
}

void JSViewAbstract::JsSize(const JSCallbackInfo& info)
{
    if (info.Length() < 0) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> widthValue = sizeObj->GetProperty("width");
    if (!widthValue->IsNull() && !widthValue->IsEmpty()) {
        Dimension width;
        if (widthValue->IsNumber()) {
            width = Dimension(widthValue->ToNumber<double>(), DimensionUnit::VP);
        } else if (widthValue->IsString()) {
            width = StringUtils::StringToDimension(widthValue->ToString(), true);
        }

        if (GreatOrEqual(width.Value(), 0.0)) {
            box->SetWidth(width, option);
        }
    }

    JSRef<JSVal> heightValue = sizeObj->GetProperty("height");
    if (!heightValue->IsNull() && !heightValue->IsEmpty()) {
        Dimension height;
        if (heightValue->IsNumber()) {
            height = Dimension(heightValue->ToNumber<double>(), DimensionUnit::VP);
        } else if (heightValue->IsString()) {
            height = StringUtils::StringToDimension(heightValue->ToString(), true);
        }

        if (GreatOrEqual(height.Value(), 0.0)) {
            box->SetHeight(height, option);
        }
    }
}

void JSViewAbstract::JsConstraintSize(const JSCallbackInfo& info)
{
    if (info.Length() < 0) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);

    JSRef<JSVal> minWidthValue = sizeObj->GetProperty("minWidth");
    if (!minWidthValue->IsNull() && !minWidthValue->IsEmpty()) {
        Dimension minWidth;
        if (minWidthValue->IsNumber()) {
            minWidth = Dimension(minWidthValue->ToNumber<double>(), DimensionUnit::VP);
            box->SetMinWidth(minWidth);
        } else if (minWidthValue->IsString()) {
            minWidth = StringUtils::StringToDimension(minWidthValue->ToString(), true);
            box->SetMinWidth(minWidth);
        }
    }

    JSRef<JSVal> maxWidthValue = sizeObj->GetProperty("maxWidth");
    if (!maxWidthValue->IsNull() && !maxWidthValue->IsEmpty()) {
        Dimension maxWidth;
        if (maxWidthValue->IsNumber()) {
            maxWidth = Dimension(maxWidthValue->ToNumber<double>(), DimensionUnit::VP);
            box->SetMaxWidth(maxWidth);
        } else if (maxWidthValue->IsString()) {
            maxWidth = StringUtils::StringToDimension(maxWidthValue->ToString(), true);
            box->SetMaxWidth(maxWidth);
        }
    }

    JSRef<JSVal> minHeightValue = sizeObj->GetProperty("minHeight");
    if (!minHeightValue->IsNull() && !minHeightValue->IsEmpty()) {
        Dimension minHeight;
        if (minHeightValue->IsNumber()) {
            minHeight = Dimension(minHeightValue->ToNumber<double>(), DimensionUnit::VP);
            box->SetMinHeight(minHeight);
        } else if (minHeightValue->IsString()) {
            minHeight = StringUtils::StringToDimension(minHeightValue->ToString(), true);
            box->SetMinHeight(minHeight);
        }
    }

    JSRef<JSVal> maxHeightValue = sizeObj->GetProperty("maxHeight");
    if (!maxHeightValue->IsNull() && !maxHeightValue->IsEmpty()) {
        Dimension maxHeight;
        if (maxHeightValue->IsNumber()) {
            maxHeight = Dimension(maxHeightValue->ToNumber<double>(), DimensionUnit::VP);
            box->SetMaxHeight(maxHeight);
        } else if (maxHeightValue->IsString()) {
            maxHeight = StringUtils::StringToDimension(maxHeightValue->ToString(), true);
            box->SetMaxHeight(maxHeight);
        }
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
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    auto flexItemComponent = ViewStackProcessor::GetInstance()->GetFlexItemComponent();

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);

    JSRef<JSVal> xVal = sizeObj->GetProperty("x");
    if (!xVal->IsNull() && !xVal->IsEmpty()) {
        Dimension x;
        if (xVal->IsNumber()) {
            x = Dimension(xVal->ToNumber<double>(), DimensionUnit::VP);
            flexItemComponent->SetLeft(x);
        } else if (xVal->IsString()) {
            x = StringUtils::StringToDimension(xVal->ToString(), true);
            flexItemComponent->SetLeft(x);
        }
    }

    JSRef<JSVal> yVal = sizeObj->GetProperty("y");
    if (!yVal->IsNull() && !yVal->IsEmpty()) {
        Dimension y;
        if (yVal->IsNumber()) {
            y = Dimension(yVal->ToNumber<double>(), DimensionUnit::VP);
            flexItemComponent->SetTop(y);
        } else if (yVal->IsString()) {
            y = StringUtils::StringToDimension(yVal->ToString(), true);
            flexItemComponent->SetTop(y);
        }
    }
    flexItemComponent->SetPositionType(PositionType::ABSOLUTE);
}

void JSViewAbstract::JsOffset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    auto flexItemComponent = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);

    JSRef<JSVal> xVal = sizeObj->GetProperty("x");
    if (!xVal->IsNull() && !xVal->IsEmpty()) {
        Dimension x;
        if (xVal->IsNumber()) {
            x = Dimension(xVal->ToNumber<double>(), DimensionUnit::VP);
            flexItemComponent->SetLeft(x);
        } else if (xVal->IsString()) {
            x = StringUtils::StringToDimension(xVal->ToString(), true);
            flexItemComponent->SetLeft(x);
        }
    }

    JSRef<JSVal> yVal = sizeObj->GetProperty("y");
    if (!yVal->IsNull() && !yVal->IsEmpty()) {
        Dimension y;
        if (yVal->IsNumber()) {
            y = Dimension(yVal->ToNumber<double>(), DimensionUnit::VP);
            flexItemComponent->SetTop(y);
        } else if (yVal->IsString()) {
            y = StringUtils::StringToDimension(yVal->ToString(), true);
            flexItemComponent->SetTop(y);
        }
    }
    flexItemComponent->SetPositionType(PositionType::OFFSET);
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

    if (!info[0]->IsNumber()) {
        LOGE("arg is not number.");
        return;
    }
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    boxComponent->SetAspectRatio(info[0]->ToNumber<double>());
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
            if (!xVal->IsNull() && !xVal->IsEmpty()) {
                Dimension x;
                if (xVal->IsNumber()) {
                    x = Dimension(xVal->ToNumber<double>(), DimensionUnit::VP);
                } else if (xVal->IsString()) {
                    x = StringUtils::StringToDimension(xVal->ToString(), true);
                }
                coverageComponent->SetX(x);
            }

            JSRef<JSVal> yVal = offsetObj->GetProperty("y");
            if (!yVal->IsNull() && !yVal->IsEmpty()) {
                Dimension y;
                if (yVal->IsNumber()) {
                    y = Dimension(yVal->ToNumber<double>(), DimensionUnit::VP);
                } else if (xVal->IsString()) {
                    y = StringUtils::StringToDimension(yVal->ToString(), true);
                }
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
    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("JsFlexBasis: arg is not Number or String.");
        return;
    }
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    if (info[0]->IsNumber()) {
        flexItem->SetFlexBasis(Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP));
    } else {
        flexItem->SetFlexBasis(StringUtils::StringToDimension(info[0]->ToString(), true));
    }
}

void JSViewAbstract::JsFlexGrow(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsFlexGrow: The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    if (!info[0]->IsNumber()) {
        LOGE("JsFlexGrow: arg is not Number or String.");
        return;
    }
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetFlexGrow(info[0]->ToNumber<double>());
}

void JSViewAbstract::JsFlexShrink(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsFlexShrink: The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    if (!info[0]->IsNumber()) {
        LOGE("JsFlexShrink: arg is not Number or String.");
        return;
    }
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetFlexShrink(info[0]->ToNumber<double>());
}

void JSViewAbstract::JsDisplayPriority(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JsDisplayPriority: The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    if (!info[0]->IsNumber()) {
        LOGE("JsDisplayPriority: arg is not Number or String.");
        return;
    }
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetDisplayIndex(info[0]->ToNumber<double>());
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
        if (info.Length() > 2 && info[2]->IsObject()) {
            auto argsPtrItem = JsonUtil::ParseJsonString(info[2]->ToString());
            MotionPathOption motionPathOption;
            if (ParseMotionPath(argsPtrItem, motionPathOption)) {
                tweenOption.SetMotioPathOption(motionPathOption);
            }
        }
        // effect: exchange
        auto sharedTransitionEffect = SharedTransitionEffect::GetSharedTransitionEffect(
            SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE, sharedTransitionComponent->GetShareId());
        sharedTransitionComponent->SetEffect(sharedTransitionEffect);
        sharedTransitionComponent->SetOption(tweenOption);
    }
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
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("arg is not a string or number.");
        return;
    }

    Color color;
    if (info[0]->IsString()) {
        color = Color::FromString(info[0]->ToString());
    } else if (info[0]->IsNumber()) {
        color = Color(ColorAlphaAdapt(info[0]->ToNumber<uint32_t>()));
    }

    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    SetBorderColor(color, option);
}

void JSViewAbstract::JsBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("arg is not a string or number.");
        return;
    }

    Color color;
    if (info[0]->IsString()) {
        color = Color::FromString(info[0]->ToString());
    } else if (info[0]->IsNumber()) {
        color = Color(ColorAlphaAdapt(info[0]->ToNumber<uint32_t>()));
    }

    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    box->SetColor(color, option);
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
        auto width = imageArgs->GetDouble("width", 0.0);
        auto height = imageArgs->GetDouble("height", 0.0);
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
        auto x = imageArgs->GetDouble("x", 0.0);
        auto y = imageArgs->GetDouble("y", 0.0);
        bgImgPosition.SetSizeTypeX(BackgroundImagePositionType::PX);
        bgImgPosition.SetSizeValueX(x);
        bgImgPosition.SetSizeTypeY(BackgroundImagePositionType::PX);
        bgImgPosition.SetSizeValueY(y);
    }
    image->SetImagePosition(bgImgPosition);
    decoration->SetImage(image);
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
        if (!argsPtrItem) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return;
        }
        if (argsPtrItem->IsNull()) {
            return;
        }
        Dimension topDimen = JSViewAbstract::GetDimension("top", argsPtrItem);
        Dimension bottomDimen = JSViewAbstract::GetDimension("bottom", argsPtrItem);
        Dimension leftDimen = JSViewAbstract::GetDimension("left", argsPtrItem);
        Dimension rightDimen = JSViewAbstract::GetDimension("right", argsPtrItem);

        if (isMargin) {
            SetMargins(topDimen, bottomDimen, leftDimen, rightDimen);
        } else {
            SetPaddings(topDimen, bottomDimen, leftDimen, rightDimen);
        }
    } else if (info[0]->IsString()) {
        Dimension length = StringUtils::StringToDimension(info[0]->ToString(), true);
        if (isMargin) {
            SetMargin(length);
        } else {
            SetPadding(length);
        }
    } else if (info[0]->IsNumber()) {
        Dimension length = Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP);
        if (isMargin) {
            SetMargin(length);
        } else {
            SetPadding(length);
        }
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

    if (argsPtrItem->Contains("width")) {
        Dimension width = JSViewAbstract::GetDimension("width", argsPtrItem);
        SetBorderWidth(width, option);
    }
    if (argsPtrItem->Contains("color")) {
        std::unique_ptr<JsonValue> colorValue = argsPtrItem->GetValue("color");
        Color color;
        if (colorValue->IsString()) {
            color = Color::FromString(colorValue->GetString());
        } else if (colorValue->IsNumber()) {
            color = Color(ColorAlphaAdapt(colorValue->GetUInt()));
        }
        SetBorderColor(color, option);
    }
    if (argsPtrItem->Contains("radius")) {
        Dimension radius = JSViewAbstract::GetDimension("radius", argsPtrItem);
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
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    SetBorderWidth(ParseDimension(info), option);
}

void JSViewAbstract::JsBorderRadius(const JSCallbackInfo& info)
{
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    SetBorderRadius(ParseDimension(info), option);
}

void JSViewAbstract::JsBlur(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number");
        return;
    }
    auto radius = info[0]->ToNumber<float>();
    SetBlur(radius);
    info.SetReturnValue(info.This());
}

void JSViewAbstract::JsBackdropBlur(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not Number");
        return;
    }

    auto radius = info[0]->ToNumber<float>();
    SetBackdropBlur(radius);
    info.SetReturnValue(info.This());
}

void JSViewAbstract::JsWindowBlur(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it it supposed to have at least 1 argument");
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

    auto progress = argsPtrItem->GetDouble("percent", 0.0);
    auto style = argsPtrItem->GetInt("style", static_cast<int32_t>(WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT));

    progress = std::clamp(progress, 0.0, 1.0);
    style = std::clamp(style, static_cast<int32_t>(WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT),
        static_cast<int32_t>(WindowBlurStyle::STYLE_BACKGROUND_XLARGE_DARK));

    SetWindowBlur(static_cast<float>(progress), static_cast<WindowBlurStyle>(style));
    info.SetReturnValue(info.This());
}

Dimension JSViewAbstract::ParseDimension(const JSCallbackInfo& info)
{
    Dimension DEFAULT_DIMENSION = Dimension(0.0, DimensionUnit::VP);
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return DEFAULT_DIMENSION;
    }
    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return DEFAULT_DIMENSION;
    }

    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(info[0]->ToString(), true);
    }
    return value;
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
    Dimension width = JSViewAbstract::GetDimension("width", argsPtrItem);
    Dimension height = JSViewAbstract::GetDimension("height", argsPtrItem);
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
    if (offset->IsNumber()) {
        offsetDimension = Dimension(offset->ToNumber<double>(), DimensionUnit::VP);
    } else {
        offsetDimension = StringUtils::StringToDimension(offset->ToString(), true);
    }
    box->SetUseAlignOffset(offsetDimension);
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
        RefPtr<JsFunction> jsOnDragFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(),
            JSRef<JSFunc>::Cast(info[0]));
        auto onDragId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE(execCtx);
            func->Execute();
        };
        auto drag = ViewStackProcessor::GetInstance()->GetBoxComponent();
        drag->SetOnDragId(onDragId);
    }
}

void JSViewAbstract::JsOnDragEnter(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(),
            JSRef<JSFunc>::Cast(info[0]));
        auto onDragEnterId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE(execCtx);
            func->Execute();
        };
        auto dragEnter = ViewStackProcessor::GetInstance()->GetBoxComponent();
        dragEnter->SetOnDragEnterId(onDragEnterId);
    }
}

void JSViewAbstract::JsOnDragLeave(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(),
            JSRef<JSFunc>::Cast(info[0]));
        auto onDragLeaveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE(execCtx);
            func->Execute();
        };
        auto dragLeave = ViewStackProcessor::GetInstance()->GetBoxComponent();
        dragLeave->SetOnDragLeaveId(onDragLeaveId);
    }
}

void JSViewAbstract::JsOnDrop(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnDropFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(),
            JSRef<JSFunc>::Cast(info[0]));
        auto onDropId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE(execCtx);
            func->Execute();
        };
        auto drop = ViewStackProcessor::GetInstance()->GetBoxComponent();
        drop->SetOnDropId(onDropId);
    }
}

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
    // angle
    std::optional<float> degree;
    GetAngle("angle", argsPtrItem, degree);
    if (degree) {
        lineGradient.GetLinearGradient().angle = degree.value();
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
    // center
    auto center = argsPtrItem->GetValue("center");
    if (center && !center->IsNull() && center->IsArray() && center->GetArraySize() == 2) {
        std::optional<Dimension> value;
        GetDimension(center->GetArrayItem(0), value);
        if (value) {
            radialGradient.GetRadialGradient().radialCenterX = value.value();
            if (value.value().Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                radialGradient.GetRadialGradient().radialCenterX =
                    Dimension(value.value().Value() * 100.0, DimensionUnit::PERCENT);
            }
            value.reset();
        }
        GetDimension(center->GetArrayItem(1), value);
        if (value) {
            radialGradient.GetRadialGradient().radialCenterY = value.value();
            if (value.value().Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                radialGradient.GetRadialGradient().radialCenterY =
                    Dimension(value.value().Value() * 100.0, DimensionUnit::PERCENT);
            }
            value.reset();
        }
    }
    // radius
    auto radius = GetDimension("radius", argsPtrItem);
    radialGradient.GetRadialGradient().radialVerticalSize = radius;
    radialGradient.GetRadialGradient().radialHorizontalSize = radius;
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
    // center
    auto center = argsPtrItem->GetValue("center");
    if (center && !center->IsNull() && center->IsArray() && center->GetArraySize() == 2) {
        std::optional<Dimension> value;
        GetDimension(center->GetArrayItem(0), value);
        if (value) {
            sweepGradient.GetSweepGradient().centerX = value.value();
            if (value.value().Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                sweepGradient.GetSweepGradient().centerX =
                    Dimension(value.value().Value() * 100.0, DimensionUnit::PERCENT);
            }
            value.reset();
        }
        GetDimension(center->GetArrayItem(1), value);
        if (value) {
            sweepGradient.GetSweepGradient().centerY = value.value();
            if (value.value().Unit() == DimensionUnit::PERCENT) {
                // [0,1] -> [0, 100]
                sweepGradient.GetSweepGradient().centerY =
                    Dimension(value.value().Value() * 100.0, DimensionUnit::PERCENT);
            }
            value.reset();
        }
    }
    std::optional<float> degree;
    // start
    GetAngle("start", argsPtrItem, degree);
    if (degree) {
        sweepGradient.GetSweepGradient().startAngle = degree.value();
        degree.reset();
    }
    // end
    GetAngle("end", argsPtrItem, degree);
    if (degree) {
        sweepGradient.GetSweepGradient().endAngle = degree.value();
        degree.reset();
    }
    // rotation
    GetAngle("rotation", argsPtrItem, degree);
    if (degree) {
        sweepGradient.GetSweepGradient().rotation = degree.value();
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
    auto radius = argsPtrItem->GetDouble("radius", 0.0);
    if (LessOrEqual(radius, 0.0)) {
        LOGE("JsShadow Parse radius failed, radius = %{public}lf", radius);
        return;
    }
    auto offsetX = GetDimension("offsetX", argsPtrItem);
    auto offsetY = GetDimension("offsetY", argsPtrItem);
    Color color;
    auto jsonColorValue = argsPtrItem->GetValue("color");
    if (jsonColorValue) {
        if (jsonColorValue->IsString()) {
            color = Color::FromString(jsonColorValue->GetString());
        } else if (jsonColorValue->IsNumber()) {
            color = Color(ColorAlphaAdapt(jsonColorValue->GetUInt()));
        }
    }
    std::vector<Shadow> shadows(1);
    shadows.begin()->SetBlurRadius(radius);
    shadows.begin()->SetOffsetX(offsetX.Value());
    shadows.begin()->SetOffsetY(offsetY.Value());
    shadows.begin()->SetColor(color);
    auto backDecoration = GetBackDecoration();
    backDecoration->SetShadows(shadows);
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
    JSClass<JSViewAbstract>::StaticMethod("offset", &JSViewAbstract::JsOffset);
    JSClass<JSViewAbstract>::StaticMethod("enabled", &JSViewAbstract::JsEnabled);
    JSClass<JSViewAbstract>::StaticMethod("aspectRatio", &JSViewAbstract::JsAspectRatio);
    JSClass<JSViewAbstract>::StaticMethod("overlay", &JSViewAbstract::JsOverlay);

    JSClass<JSViewAbstract>::StaticMethod("blur", &JSViewAbstract::JsBlur);
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

    JSClass<JSViewAbstract>::StaticMethod("onDrag", &JSViewAbstract::JsOnDrag);
    JSClass<JSViewAbstract>::StaticMethod("onDragEnter", &JSViewAbstract::JsOnDragEnter);
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
    JSClass<JSViewAbstract>::StaticMethod("clip", &JSViewAbstract::JsClip);
    JSClass<JSViewAbstract>::StaticMethod("mask", &JSViewAbstract::JsMask);
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

void JSViewAbstract::SetMarginTop(const std::string& value)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetTop(StringUtils::StringToDimension(value, true));
    box->SetMargin(margin);
}

void JSViewAbstract::SetMarginBottom(const std::string& value)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetBottom(StringUtils::StringToDimension(value, true));
    box->SetMargin(margin);
}

void JSViewAbstract::SetMarginLeft(const std::string& value)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetLeft(StringUtils::StringToDimension(value, true));
    box->SetMargin(margin);
}

void JSViewAbstract::SetMarginRight(const std::string& value)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge margin = box->GetMargin();
    margin.SetRight(StringUtils::StringToDimension(value, true));
    box->SetMargin(margin);
}

void JSViewAbstract::SetMargin(const std::string& value)
{
    Dimension dimen = StringUtils::StringToDimension(value, true);
    SetMargins(dimen, dimen, dimen, dimen);
}

void JSViewAbstract::SetMargins(
    const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge margin(left, top, right, bottom);
    box->SetMargin(margin);
}

void JSViewAbstract::SetPaddingTop(const std::string& value)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetTop(StringUtils::StringToDimension(value, true));
    box->SetPadding(padding);
}

void JSViewAbstract::SetPaddingBottom(const std::string& value)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetBottom(StringUtils::StringToDimension(value, true));
    box->SetPadding(padding);
}

void JSViewAbstract::SetPaddingLeft(const std::string& value)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetLeft(StringUtils::StringToDimension(value, true));
    box->SetPadding(padding);
}

void JSViewAbstract::SetPaddingRight(const std::string& value)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    Edge padding = box->GetPadding();
    padding.SetRight(StringUtils::StringToDimension(value, true));
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
    Edge padding(left, top, right, bottom);
    box->SetPadding(padding);
}

void JSViewAbstract::SetMargin(const Dimension& value)
{
    SetMargins(value, value, value, value);
}

void JSViewAbstract::SetBlur(float radius)
{
    auto decoration = GetFrontDecoration();
    if (decoration) {
        decoration->SetBlurRadius(Dimension(radius));
    }
}

void JSViewAbstract::SetBackdropBlur(float radius)
{
    auto decoration = GetBackDecoration();
    if (decoration) {
        decoration->SetBlurRadius(Dimension(radius));
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

Dimension JSViewAbstract::GetDimension(const std::string& key, const std::unique_ptr<JsonValue>& jsonValue)
{
    std::optional<Dimension> dimension;
    GetDimension(key, jsonValue, dimension);
    if (!dimension) {
        dimension = Dimension(0.0, DimensionUnit::VP);
    }
    return dimension.value();
}

void JSViewAbstract::GetDimension(
    const std::string& key, const std::unique_ptr<JsonValue>& jsonValue, std::optional<Dimension>& out)
{
    GetDimension(jsonValue->GetValue(key), out);
}

void JSViewAbstract::GetDimension(const std::unique_ptr<JsonValue>& value, std::optional<Dimension>& out)
{
    if (value && value->IsString()) {
        out = StringUtils::StringToDimension(value->GetString(), true);
    } else if (value && value->IsNumber()) {
        out = Dimension(value->GetDouble(), DimensionUnit::VP);
    } else {
        LOGE("Invalid value type");
    }
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
            if (colorParams->IsString()) {
                color = Color::FromString(colorParams->GetString());
            } else if (colorParams->IsNumber()) {
                color = Color(ColorAlphaAdapt(colorParams->GetInt()));
            } else {
                LOGE("parse colorParams failed, skip this %s ", colorParams->ToString().c_str());
                continue;
            }
            gradientColor.SetColor(color);
            gradientColor.SetHasValue(false);
            // stop value
            if (item->GetArraySize() <= 1) {
                continue;
            }
            auto stopValue = item->GetArrayItem(1);
            if (stopValue && !stopValue->IsNull() && stopValue->IsNumber()) {
                gradientColor.SetHasValue(true);
                auto value = std::clamp(stopValue->GetDouble(), 0.0, 1.0);
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

Dimension JSViewAbstract::ToDimension(const JSRef<JSVal>& jsVal)
{
    Dimension value;
    if (jsVal->IsNumber()) {
        value = Dimension(jsVal->ToNumber<double>(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(jsVal->ToString(), true);
    }
    return value;
}

bool JSViewAbstract::ToDimension(const JSRef<JSVal>& jsVal, Dimension& dim)
{
    if (jsVal->IsNull() || jsVal->IsEmpty()) {
        return false;
    }
    if (!jsVal->IsNumber() && !jsVal->IsString()) {
        return false;
    }
    dim = ToDimension(jsVal);
    return true;
}

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
