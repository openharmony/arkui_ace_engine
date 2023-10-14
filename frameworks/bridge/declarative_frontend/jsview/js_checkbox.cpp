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

#include "bridge/declarative_frontend/jsview/js_checkbox.h"

#include <optional>
#include <string>

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/checkbox_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace {
namespace {
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;
}
std::unique_ptr<CheckBoxModel> CheckBoxModel::instance_ = nullptr;
std::mutex CheckBoxModel::mutex_;

CheckBoxModel* CheckBoxModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::CheckBoxModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::CheckBoxModelNG());
            } else {
                instance_.reset(new Framework::CheckBoxModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSCheckbox::Create(const JSCallbackInfo& info)
{
    auto checkboxName = std::optional<std::string>("");
    auto checkboxGroup = std::optional<std::string>("");
    if ((info.Length() >= 1) && info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto name = paramObject->GetProperty("name");
        auto group = paramObject->GetProperty("group");
        if (name->IsString()) {
            checkboxName = name->ToString();
        }
        if (group->IsString()) {
            checkboxGroup = group->ToString();
        }
    }
    CheckBoxModel::GetInstance()->Create(checkboxName, checkboxGroup, V2::CHECK_BOX_ETS_TAG);
}

void JSCheckbox::JSBind(BindingTarget globalObj)
{
    JSClass<JSCheckbox>::Declare("Checkbox");

    JSClass<JSCheckbox>::StaticMethod("create", &JSCheckbox::Create);
    JSClass<JSCheckbox>::StaticMethod("select", &JSCheckbox::SetSelect);
    JSClass<JSCheckbox>::StaticMethod("onChange", &JSCheckbox::SetOnChange);
    JSClass<JSCheckbox>::StaticMethod("selectedColor", &JSCheckbox::SelectedColor);
    JSClass<JSCheckbox>::StaticMethod("unselectedColor", &JSCheckbox::UnSelectedColor);
    JSClass<JSCheckbox>::StaticMethod("mark", &JSCheckbox::Mark);
    JSClass<JSCheckbox>::StaticMethod("responseRegion", &JSCheckbox::JsResponseRegion);
    JSClass<JSCheckbox>::StaticMethod("width", &JSCheckbox::JsWidth);
    JSClass<JSCheckbox>::StaticMethod("height", &JSCheckbox::JsHeight);
    JSClass<JSCheckbox>::StaticMethod("size", &JSCheckbox::JsSize);
    JSClass<JSCheckbox>::StaticMethod("padding", &JSCheckbox::JsPadding);
    JSClass<JSCheckbox>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSCheckbox>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCheckbox>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCheckbox>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCheckbox>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCheckbox>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSCheckbox>::InheritAndBind<JSViewAbstract>(globalObj);
}

void ParseSelectObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    auto changeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](bool param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("CheckBox.ChangeEvent");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(param));
        func->ExecuteJS(1, &newJSVal);
    };
    CheckBoxModel::GetInstance()->SetChangeEvent(std::move(changeEvent));
}

void JSCheckbox::SetSelect(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        return;
    }
    bool select = false;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        select = info[0]->ToBoolean();
    }
    CheckBoxModel::GetInstance()->SetSelect(select);
    if (info.Length() > 1 && info[1]->IsFunction()) {
        ParseSelectObject(info, info[1]);
    }
}

void JSCheckbox::SetOnChange(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onChange = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](bool select) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("CheckBox.onChange");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(select));
        func->ExecuteJS(1, &newJSVal);
    };
    CheckBoxModel::GetInstance()->SetOnChange(onChange);
    args.ReturnSelf();
}

void JSCheckbox::JsResponseRegion(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsResponseRegion(info);
        return;
    }
    if (info.Length() < 1) {
        return;
    }
    std::vector<DimensionRect> result;
    if (!JSViewAbstract::ParseJsResponseRegionArray(info[0], result)) {
        return;
    }
    CheckBoxModel::GetInstance()->SetResponseRegion(result);
}

void JSCheckbox::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    JsWidth(info[0]);
}

void JSCheckbox::JsWidth(const JSRef<JSVal>& jsValue)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto defaultWidth = checkBoxTheme->GetDefaultWidth();
    auto horizontalPadding = checkBoxTheme->GetHotZoneHorizontalPadding();
    auto width = defaultWidth - horizontalPadding * 2;
    CalcDimension value(width);
    ParseJsDimensionVp(jsValue, value);
    if (value.IsNegative()) {
        value = width;
    }
    CheckBoxModel::GetInstance()->SetWidth(value);
}

void JSCheckbox::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    JsHeight(info[0]);
}

void JSCheckbox::JsHeight(const JSRef<JSVal>& jsValue)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto defaultHeight = checkBoxTheme->GetDefaultHeight();
    auto verticalPadding = checkBoxTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2;
    CalcDimension value(height);
    ParseJsDimensionVp(jsValue, value);
    if (value.IsNegative()) {
        value = height;
    }
    CheckBoxModel::GetInstance()->SetHeight(value);
}

void JSCheckbox::JsSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JsWidth(sizeObj->GetProperty("width"));
    JsHeight(sizeObj->GetProperty("height"));
}

void JSCheckbox::SelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color selectedColor;
    auto theme = GetTheme<CheckboxTheme>();
    if (!ParseJsColor(info[0], selectedColor)) {
        selectedColor = theme->GetActiveColor();
    }
    CheckBoxModel::GetInstance()->SetSelectedColor(selectedColor);
}

void JSCheckbox::UnSelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color unSelectedColor;
    auto theme = GetTheme<CheckboxTheme>();
    if (!ParseJsColor(info[0], unSelectedColor)) {
        unSelectedColor = theme->GetInactiveColor();
    }

    CheckBoxModel::GetInstance()->SetUnSelectedColor(unSelectedColor);
}

void JSCheckbox::Mark(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsObject()) {
        return;
    }

    auto markObj = JSRef<JSObject>::Cast(info[0]);
    auto strokeColorValue = markObj->GetProperty("strokeColor");
    Color strokeColor;
    auto theme = GetTheme<CheckboxTheme>();
    if (!ParseJsColor(strokeColorValue, strokeColor)) {
        strokeColor = theme->GetPointColor();
    }
    CheckBoxModel::GetInstance()->SetCheckMarkColor(strokeColor);

    auto sizeValue = markObj->GetProperty("size");
    CalcDimension size;
    if ((ParseJsDimensionVp(sizeValue, size)) && (size.Unit() != DimensionUnit::PERCENT) && (size.ConvertToVp() >= 0)) {
        CheckBoxModel::GetInstance()->SetCheckMarkSize(size);
    } else {
        CheckBoxModel::GetInstance()->SetCheckMarkSize(Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE));
    }

    auto strokeWidthValue = markObj->GetProperty("strokeWidth");
    CalcDimension strokeWidth;
    if ((ParseJsDimensionVp(strokeWidthValue, strokeWidth)) && (strokeWidth.Unit() != DimensionUnit::PERCENT) &&
        (strokeWidth.ConvertToVp() >= 0)) {
        CheckBoxModel::GetInstance()->SetCheckMarkWidth(strokeWidth);
    } else {
        CheckBoxModel::GetInstance()->SetCheckMarkWidth(theme->GetCheckStroke());
    }
}

void JSCheckbox::JsPadding(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    NG::PaddingPropertyF oldPadding({ 0.0f, 0.0f, 0.0f, 0.0f });
    bool flag = GetOldPadding(info, oldPadding);
    NG::PaddingProperty newPadding = GetNewPadding(info);
    CheckBoxModel::GetInstance()->SetPadding(oldPadding, newPadding, flag);
}

bool JSCheckbox::GetOldPadding(const JSCallbackInfo& info, NG::PaddingPropertyF& padding)
{
    if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            return false;
        }
        if (argsPtrItem->Contains("top") || argsPtrItem->Contains("bottom") || argsPtrItem->Contains("left") ||
            argsPtrItem->Contains("right")) {
            CalcDimension topDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension leftDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension rightDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension bottomDimen = CalcDimension(0.0, DimensionUnit::VP);
            ParseJsonDimensionVp(argsPtrItem->GetValue("top"), topDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("left"), leftDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("right"), rightDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("bottom"), bottomDimen);
            if (leftDimen == 0.0_vp) {
                leftDimen = rightDimen;
            }
            if (topDimen == 0.0_vp) {
                topDimen = bottomDimen;
            }
            if (leftDimen == 0.0_vp) {
                leftDimen = topDimen;
            }

            padding.left = leftDimen.ConvertToPx();
            padding.right = rightDimen.ConvertToPx();
            padding.top = topDimen.ConvertToPx();
            padding.bottom = bottomDimen.ConvertToPx();
            return true;
        }
    }

    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        return false;
    }

    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    return true;
}

NG::PaddingProperty JSCheckbox::GetNewPadding(const JSCallbackInfo& info)
{
    NG::PaddingProperty padding(
        { NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp) });
    if (info[0]->IsObject()) {
        std::optional<CalcDimension> left;
        std::optional<CalcDimension> right;
        std::optional<CalcDimension> top;
        std::optional<CalcDimension> bottom;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);

        CalcDimension leftDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("left"), leftDimen)) {
            left = leftDimen;
        }
        CalcDimension rightDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("right"), rightDimen)) {
            right = rightDimen;
        }
        CalcDimension topDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("top"), topDimen)) {
            top = topDimen;
        }
        CalcDimension bottomDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("bottom"), bottomDimen)) {
            bottom = bottomDimen;
        }
        if (left.has_value() || right.has_value() || top.has_value() || bottom.has_value()) {
            padding = GetPadding(top, bottom, left, right);
            return padding;
        }
    }
    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        length.Reset();
    }

    padding.SetEdges(NG::CalcLength(length.IsNonNegative() ? length : CalcDimension()));
    return padding;
}

NG::PaddingProperty JSCheckbox::GetPadding(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
    const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty padding(
        { NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp) });
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            padding.left =
                NG::CalcLength(left.value().IsNonNegative() ? left.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            padding.left = NG::CalcLength(left.value().IsNonNegative() ? left.value() : CalcDimension());
        }
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            padding.right =
                NG::CalcLength(right.value().IsNonNegative() ? right.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            padding.right = NG::CalcLength(right.value().IsNonNegative() ? right.value() : CalcDimension());
        }
    }
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            padding.top =
                NG::CalcLength(top.value().IsNonNegative() ? top.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            padding.top = NG::CalcLength(top.value().IsNonNegative() ? top.value() : CalcDimension());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            padding.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            padding.bottom = NG::CalcLength(bottom.value().IsNonNegative() ? bottom.value() : CalcDimension());
        }
    }
    return padding;
}
} // namespace OHOS::Ace::Framework
