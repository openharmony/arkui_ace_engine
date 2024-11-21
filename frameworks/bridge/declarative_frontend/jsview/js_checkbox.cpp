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
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_checkbox_theme.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace {
namespace {
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;
}

CheckBoxModel* CheckBoxModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::CheckBoxModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::CheckBoxModelNG instance;
        return &instance;
    } else {
        static Framework::CheckBoxModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSCheckbox::Create(const JSCallbackInfo& info)
{
    auto checkboxName = std::optional<std::string>("");
    auto checkboxGroup = std::optional<std::string>("");
    std::optional<std::function<void()>> customBuilderFunc;
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
        auto builderObject = paramObject->GetProperty("indicatorBuilder");
        if (builderObject->IsFunction()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(info.This(), JSRef<JSFunc>::Cast(builderObject));
            CHECK_NULL_VOID(builderFunc);
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto callbackFunc = [execCtx = info.GetExecutionContext(),
                func = std::move(builderFunc), node = targetNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("CheckBox.builder");
                PipelineContext::SetCallBackNode(node);
                func->Execute();
            };
            customBuilderFunc = std::move(callbackFunc);
        }
    }
    CheckBoxModel::GetInstance()->Create(checkboxName, checkboxGroup, V2::CHECK_BOX_ETS_TAG);
    CheckBoxModel::GetInstance()->SetBuilder(customBuilderFunc);

    JSCheckBoxTheme::ApplyTheme();
}

void JSCheckbox::JSBind(BindingTarget globalObj)
{
    JSClass<JSCheckbox>::Declare("Checkbox");

    JSClass<JSCheckbox>::StaticMethod("create", &JSCheckbox::Create);
    JSClass<JSCheckbox>::StaticMethod("select", &JSCheckbox::SetSelect);
    JSClass<JSCheckbox>::StaticMethod("shape", &JSCheckbox::SetCheckboxStyle);
    JSClass<JSCheckbox>::StaticMethod("onChange", &JSCheckbox::SetOnChange);
    JSClass<JSCheckbox>::StaticMethod("selectedColor", &JSCheckbox::SelectedColor);
    JSClass<JSCheckbox>::StaticMethod("unselectedColor", &JSCheckbox::UnSelectedColor);
    JSClass<JSCheckbox>::StaticMethod("mark", &JSCheckbox::Mark);
    JSClass<JSCheckbox>::StaticMethod("responseRegion", &JSCheckbox::JsResponseRegion);
    JSClass<JSCheckbox>::StaticMethod("padding", &JSCheckbox::JsPadding);
    JSClass<JSCheckbox>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSCheckbox>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCheckbox>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCheckbox>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCheckbox>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSCheckbox>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCheckbox>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSCheckbox>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSCheckbox>::InheritAndBind<JSViewAbstract>(globalObj);
}

void ParseSelectObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto changeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](bool param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("CheckBox.ChangeEvent");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(param));
        func->ExecuteJS(1, &newJSVal);
    };
    CheckBoxModel::GetInstance()->SetChangeEvent(std::move(changeEvent));
}

void JSCheckbox::SetSelect(const JSCallbackInfo& info)
{
    auto length = info.Length();
    if (length < 1 || length > 2) {
        return;
    }
    bool select = false;
    auto jsSelect = info[0];
    if (length > 0 && jsSelect->IsBoolean()) {
        select = jsSelect->ToBoolean();
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkbox set select %{public}d", select);
    CheckBoxModel::GetInstance()->SetSelect(select);
    if (length > 1 && info[1]->IsFunction()) {
        ParseSelectObject(info, info[1]);
    }
}

void JSCheckbox::SetOnChange(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](bool select) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("CheckBox.onChange");
        PipelineContext::SetCallBackNode(node);
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
    CalcDimension value;
    ParseJsDimensionVp(jsValue, value);
    if (value.IsNegative()) {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
        return;
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
    CalcDimension value;
    ParseJsDimensionVp(jsValue, value);
    if (value.IsNegative()) {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(false);
        return;
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

void JSCheckbox::SetCheckboxStyle(int32_t checkBoxStyle)
{
    CheckBoxStyle curCheckBoxStyle = static_cast<CheckBoxStyle>(checkBoxStyle);
    CheckBoxModel::GetInstance()->SetCheckboxStyle(curCheckBoxStyle);
}
void JSCheckbox::Mark(const JSCallbackInfo& info)
{
    auto theme = GetTheme<CheckboxTheme>();
    if (!info[0]->IsObject()) {
        CheckBoxModel::GetInstance()->SetCheckMarkColor(theme->GetPointColor());
        CheckBoxModel::GetInstance()->SetCheckMarkSize(Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE));
        CheckBoxModel::GetInstance()->SetCheckMarkWidth(theme->GetCheckStroke());
        return;
    }

    auto markObj = JSRef<JSObject>::Cast(info[0]);
    auto strokeColorValue = markObj->GetProperty("strokeColor");
    Color strokeColor = theme->GetPointColor();
    if (!ParseJsColor(strokeColorValue, strokeColor)) {
        JSCheckBoxTheme::ObtainCheckMarkColor(strokeColor);
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
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        if (jsObj->HasProperty("top") || jsObj->HasProperty("bottom")
            || jsObj->HasProperty("left") || jsObj->HasProperty("right")) {
            CalcDimension topDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension leftDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension rightDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension bottomDimen = CalcDimension(0.0, DimensionUnit::VP);
            ParseJsDimensionVp(jsObj->GetProperty("top"), topDimen);
            ParseJsDimensionVp(jsObj->GetProperty("left"), leftDimen);
            ParseJsDimensionVp(jsObj->GetProperty("right"), rightDimen);
            ParseJsDimensionVp(jsObj->GetProperty("bottom"), bottomDimen);
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
    NG::PaddingProperty padding({
        NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp)
    });
    if (info[0]->IsObject()) {
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);
        CommonCalcDimension commonCalcDimension;
        ParseCommonMarginOrPaddingCorner(paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            padding = GetPadding(commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left,
                commonCalcDimension.right);
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
    NG::PaddingProperty padding({
        NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp)
    });
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
