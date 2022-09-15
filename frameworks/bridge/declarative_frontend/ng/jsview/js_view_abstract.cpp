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

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

#include <algorithm>
#include <regex>
#include <vector>

#include "base/json/json_util.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr double EPSILON = 0.000002f;

bool CheckJSCallbackInfo(
    const std::string& callerName, const JSCallbackInfo& info, std::vector<JSCallbackInfoType>& infoTypes)
{
    if (info.Length() < 1) {
        LOGE("%{public}s: The arg is supposed to have at least one argument", callerName.c_str());
        return false;
    }
    bool typeVerified = false;
    std::string unrecognizedType;
    for (const auto& infoType : infoTypes) {
        switch (infoType) {
            case JSCallbackInfoType::STRING:
                if (info[0]->IsString()) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "string|";
                }
                break;
            case JSCallbackInfoType::NUMBER:
                if (info[0]->IsNumber()) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "number|";
                }
                break;
            case JSCallbackInfoType::OBJECT:
                if (info[0]->IsObject()) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "object|";
                }
                break;
            case JSCallbackInfoType::FUNCTION:
                if (info[0]->IsFunction()) {
                    typeVerified = true;
                } else {
                    unrecognizedType += "Function|";
                }
                break;
            default:
                break;
        }
    }
    if (!typeVerified) {
        LOGE("%{public}s: info[0] is not a [%{public}s]", callerName.c_str(),
            unrecognizedType.substr(0, unrecognizedType.size() - 1).c_str());
    }
    return typeVerified || infoTypes.size() == 0;
}

} // namespace

void JSViewAbstract::SetDefaultTransition(TransitionType transitionType) {}

bool JSViewAbstract::ParseAndSetOpacityTransition(
    const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    return false;
}

bool JSViewAbstract::ParseAndSetRotateTransition(
    const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    return false;
}

bool JSViewAbstract::ParseAndSetScaleTransition(
    const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    return false;
}

bool JSViewAbstract::ParseAndSetTranslateTransition(
    const std::unique_ptr<JsonValue>& transitionArgs, TransitionType transitionType)
{
    return false;
}

void JSViewAbstract::JsScale(const JSCallbackInfo& info) {}

void JSViewAbstract::JsScaleX(const JSCallbackInfo& info) {}

void JSViewAbstract::JsScaleY(const JSCallbackInfo& info) {}

void JSViewAbstract::JsOpacity(const JSCallbackInfo& info) {}

void JSViewAbstract::JsTranslate(const JSCallbackInfo& info) {}

void JSViewAbstract::JsTranslateX(const JSCallbackInfo& info) {}

void JSViewAbstract::JsTranslateY(const JSCallbackInfo& info) {}

void JSViewAbstract::JsRotate(const JSCallbackInfo& info) {}

void JSViewAbstract::JsRotateX(const JSCallbackInfo& info) {}

void JSViewAbstract::JsRotateY(const JSCallbackInfo& info) {}

void JSViewAbstract::JsTransform(const JSCallbackInfo& info) {}

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

    NG::ViewAbstract::SetWidth(NG::CalcLength(value));
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

    NG::ViewAbstract::SetHeight(NG::CalcLength(value));
    return true;
}

void JSViewAbstract::JsResponseRegion(const JSCallbackInfo& info) {}

void JSViewAbstract::JsConstraintSize(const JSCallbackInfo& info) {}

void JSViewAbstract::JsLayoutPriority(const JSCallbackInfo& info) {}

void JSViewAbstract::JsLayoutWeight(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER };
    if (!CheckJSCallbackInfo("JsLayoutWeight", info, checkList)) {
        return;
    }

    int32_t value;
    if (info[0]->IsNumber()) {
        value = info[0]->ToNumber<int32_t>();
    } else {
        value = static_cast<int32_t>(StringUtils::StringToUint(info[0]->ToString()));
    }

    NG::ViewAbstract::SetLayoutWeight(value);
}

void JSViewAbstract::JsAlign(const JSCallbackInfo& info) {}

void JSViewAbstract::JsPosition(const JSCallbackInfo& info) {}

void JSViewAbstract::JsMarkAnchor(const JSCallbackInfo& info) {}

void JSViewAbstract::JsOffset(const JSCallbackInfo& info) {}

void JSViewAbstract::JsEnabled(const JSCallbackInfo& info) {}

void JSViewAbstract::JsAspectRatio(const JSCallbackInfo& info) {}

void JSViewAbstract::JsOverlay(const JSCallbackInfo& info) {}

void JSViewAbstract::SetVisibility(const JSCallbackInfo& info) {}

void JSViewAbstract::JsFlexBasis(const JSCallbackInfo& info) {}

void JSViewAbstract::JsFlexGrow(const JSCallbackInfo& info) {}

void JSViewAbstract::JsFlexShrink(const JSCallbackInfo& info) {}

void JSViewAbstract::JsDisplayPriority(const JSCallbackInfo& info) {}

void JSViewAbstract::JsSharedTransition(const JSCallbackInfo& info) {}

void JSViewAbstract::JsGeometryTransition(const JSCallbackInfo& info) {}

void JSViewAbstract::JsAlignSelf(const JSCallbackInfo& info) {}

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
    NG::ViewAbstract::SetBackgroundColor(backgroundColor);
}

void JSViewAbstract::JsBackgroundImage(const JSCallbackInfo& info) {}

void JSViewAbstract::JsBackgroundBlurStyle(const JSCallbackInfo& info) {}

void JSViewAbstract::JsBackgroundImageSize(const JSCallbackInfo& info) {}

void JSViewAbstract::JsBackgroundImagePosition(const JSCallbackInfo& info) {}

void JSViewAbstract::JsBindMenu(const JSCallbackInfo& info) {}

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
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("ParseMarginOrPadding", info, checkList)) {
        return;
    }

    if (info[0]->IsObject()) {
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);
        NG::PaddingProperty padding;
        Dimension leftDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("left"), leftDimen)) {
            padding.left = NG::CalcLength(leftDimen);
        }
        Dimension rightDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("right"), rightDimen)) {
            padding.right = NG::CalcLength(rightDimen);
        }
        Dimension topDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("top"), topDimen)) {
            padding.top = NG::CalcLength(topDimen);
        }
        Dimension bottomDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("bottom"), bottomDimen)) {
            padding.bottom = NG::CalcLength(bottomDimen);
        }
        NG::ViewAbstract::SetPadding(padding);
        return;
    }

    Dimension length;
    if (ParseJsDimensionVp(info[0], length)) {
        NG::ViewAbstract::SetPadding(NG::CalcLength(length));
    }
}

void JSViewAbstract::ParseBorderWidth(const JSRef<JSVal>& args, RefPtr<Decoration> decoration) {}

void JSViewAbstract::JsBorderImage(const JSCallbackInfo& info) {}

void JSViewAbstract::ParseBorderColor(const JSRef<JSVal>& args, RefPtr<Decoration> decoration) {}

void JSViewAbstract::ParseBorderRadius(const JSRef<JSVal>& args, RefPtr<Decoration> decoration) {}

void JSViewAbstract::ParseBorderStyle(const JSRef<JSVal>& args, RefPtr<Decoration> decoration) {}

bool JSViewAbstract::ParseJsAnimatableDimensionVp(const JSRef<JSVal>& jsValue, AnimatableDimension& result)
{
    return false;
}

bool JSViewAbstract::ParseAndUpdateDragItemInfo(const JSRef<JSVal>& info, DragItemInfo& dragInfo)
{
    return false;
}

void JSViewAbstract::JsUseAlign(const JSCallbackInfo& info) {}

void JSViewAbstract::JsGridSpan(const JSCallbackInfo& info) {}

void JSViewAbstract::JsGridOffset(const JSCallbackInfo& info) {}

void JSViewAbstract::JsUseSizeType(const JSCallbackInfo& info) {}

void JSViewAbstract::JsZIndex(const JSCallbackInfo& info) {}

void JSViewAbstract::Pop()
{
    NG::ViewStackProcessor::GetInstance()->Pop();
}

void JSViewAbstract::JsOnDragStart(const JSCallbackInfo& info) {}

void JSViewAbstract::JsOnDragEnter(const JSCallbackInfo& info) {}

void JSViewAbstract::JsOnDragMove(const JSCallbackInfo& info) {}

void JSViewAbstract::JsOnDragLeave(const JSCallbackInfo& info) {}

void JSViewAbstract::JsOnDrop(const JSCallbackInfo& info) {}

void JSViewAbstract::JsOnAreaChange(const JSCallbackInfo& info) {}

#ifndef WEARABLE_PRODUCT
void JSViewAbstract::JsBindPopup(const JSCallbackInfo& info) {}
#endif

void JSViewAbstract::JsLinearGradient(const JSCallbackInfo& info) {}

void JSViewAbstract::JsRadialGradient(const JSCallbackInfo& info) {}

void JSViewAbstract::JsSweepGradient(const JSCallbackInfo& info) {}

void JSViewAbstract::JsMotionPath(const JSCallbackInfo& info) {}

void JSViewAbstract::JsShadow(const JSCallbackInfo& info) {}

void JSViewAbstract::JsGrayScale(const JSCallbackInfo& info) {}

void JSViewAbstract::JsBrightness(const JSCallbackInfo& info) {}

void JSViewAbstract::JsContrast(const JSCallbackInfo& info) {}

void JSViewAbstract::JsSaturate(const JSCallbackInfo& info) {}

void JSViewAbstract::JsSepia(const JSCallbackInfo& info) {}

void JSViewAbstract::JsInvert(const JSCallbackInfo& info) {}

void JSViewAbstract::JsHueRotate(const JSCallbackInfo& info) {}

void JSViewAbstract::JsClip(const JSCallbackInfo& info) {}

void JSViewAbstract::JsMask(const JSCallbackInfo& info) {}

void JSViewAbstract::JsFocusable(const JSCallbackInfo& info) {}

void JSViewAbstract::JsOnFocusMove(const JSCallbackInfo& args) {}

void JSViewAbstract::JsOnFocus(const JSCallbackInfo& args) {}

void JSViewAbstract::JsOnBlur(const JSCallbackInfo& args) {}

void JSViewAbstract::JsTabIndex(const JSCallbackInfo& info) {}

void JSViewAbstract::JsKey(const std::string& key) {}

void JSViewAbstract::JsId(const std::string& id)
{
    JsKey(id);
}

void JSViewAbstract::JsRestoreId(int32_t restoreId) {}

#if defined(PREVIEW)
void JSViewAbstract::JsDebugLine(const JSCallbackInfo& info) {}
#endif

void JSViewAbstract::JsOpacityPassThrough(const JSCallbackInfo& info)
{
    JSViewAbstract::JsOpacity(info);
}

void JSViewAbstract::JsTransitionPassThrough(const JSCallbackInfo& info)
{
    JSViewAbstract::JsTransition(info);
}

void JSViewAbstract::JsAccessibilityGroup(bool accessible) {}

void JSViewAbstract::JsAccessibilityText(const std::string& text) {}

void JSViewAbstract::JsAccessibilityDescription(const std::string& description) {}

void JSViewAbstract::JsAccessibilityImportance(const std::string& importance) {}

void JSViewAbstract::JsBindContextMenu(const JSCallbackInfo& info) {}

void JSViewAbstract::JsAlignRules(const JSCallbackInfo& info) {}

RefPtr<Decoration> JSViewAbstract::GetFrontDecoration()
{
    return nullptr;
}

RefPtr<Decoration> JSViewAbstract::GetBackDecoration()
{
    return nullptr;
}

void JSViewAbstract::SetBorderRadius(const Dimension& value, const AnimationOption& option) {}

void JSViewAbstract::SetMarginTop(const JSCallbackInfo& info) {}

void JSViewAbstract::SetMarginBottom(const JSCallbackInfo& info) {}

void JSViewAbstract::SetMarginLeft(const JSCallbackInfo& info) {}

void JSViewAbstract::SetMarginRight(const JSCallbackInfo& info) {}

void JSViewAbstract::SetMargins(
    const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right)
{}

void JSViewAbstract::SetPaddingTop(const JSCallbackInfo& info) {}

void JSViewAbstract::SetPaddingBottom(const JSCallbackInfo& info) {}

void JSViewAbstract::SetPaddingLeft(const JSCallbackInfo& info) {}

void JSViewAbstract::SetPaddingRight(const JSCallbackInfo& info) {}

void JSViewAbstract::SetPadding(const Dimension& value)
{
    SetPaddings(value, value, value, value);
}

void JSViewAbstract::SetPaddings(
    const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right)
{}

void JSViewAbstract::SetMargin(const Dimension& value)
{
    SetMargins(value, value, value, value);
}

void JSViewAbstract::SetBlur(float radius) {}

void JSViewAbstract::SetColorBlend(Color color) {}

void JSViewAbstract::SetBackdropBlur(float radius) {}

void JSViewAbstract::SetBlurRadius(const RefPtr<Decoration>& decoration, float radius) {}

void JSViewAbstract::SetWindowBlur(float progress, WindowBlurStyle blurStyle) {}

void JSViewAbstract::SetDirection(const std::string& dir) {}

void JSViewAbstract::JsHoverEffect(const JSCallbackInfo& info) {}

RefPtr<Gesture> JSViewAbstract::GetTapGesture(const JSCallbackInfo& info, int32_t countNum, int32_t fingerNum)
{
    return nullptr;
}

void JSViewAbstract::JsOnMouse(const JSCallbackInfo& args) {}

void JSViewAbstract::JsOnVisibleAreaChange(const JSCallbackInfo& info) {}

} // namespace OHOS::Ace::Framework
