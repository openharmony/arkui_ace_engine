/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_radio.h"
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/jsview/models/radio_model_impl.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_radio_theme.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"

namespace OHOS::Ace {

enum class RadioIndicatorType {
    TICK = 0,
    DOT,
    CUSTOM,
};

RadioModel* RadioModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::RadioModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::RadioModelNG instance;
        return &instance;
    } else {
        static Framework::RadioModelImpl instance;
        return &instance;
    }
#endif
}

} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
void JSRadio::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    std::optional<std::string> value;
    std::optional<std::string> group;
    std::optional<int32_t> indicator;
    std::function<void()> customBuilderFunc = nullptr;
    if ((info.Length() >= 1) && info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto valueTemp = paramObject->GetProperty("value");
        auto groupTemp = paramObject->GetProperty("group");
        auto indicatorTemp = paramObject->GetProperty("indicatorType");
        auto builderObject = paramObject->GetProperty("indicatorBuilder");
        if (valueTemp->IsString()) {
            value = valueTemp->ToString();
        } else {
            value = "";
        }
        if (groupTemp->IsString()) {
            group = groupTemp->ToString();
        } else {
            group = "";
        }
        indicator = indicatorTemp->ToNumber<int32_t>();
        ParseIndicator(info, indicator, customBuilderFunc, builderObject);
    }
    RadioModel::GetInstance()->Create(value, group, indicator);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        RadioModel::GetInstance()->SetBuilder(std::move(customBuilderFunc));
    }
    JSRadioTheme::ApplyTheme();
}

void JSRadio::ParseIndicator(const JSCallbackInfo& info, std::optional<int32_t>& indicator,
    std::function<void()>& customBuilderFunc, JSRef<JSVal>& builderObject)
{
    if (indicator.value() == static_cast<int32_t>(RadioIndicatorType::CUSTOM)) {
        if (builderObject->IsFunction()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(info.This(), JSRef<JSFunc>::Cast(builderObject));
            CHECK_NULL_VOID(builderFunc);
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            customBuilderFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc),
                                    node = targetNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("Radio.builder");
                PipelineContext::SetCallBackNode(node);
                func->Execute();
            };
        } else {
            indicator = static_cast<int32_t>(RadioIndicatorType::TICK);
        }
    }
}

void JSRadio::JSBind(BindingTarget globalObj)
{
    JSClass<JSRadio>::Declare("Radio");

    JSClass<JSRadio>::StaticMethod("create", &JSRadio::Create);
    JSClass<JSRadio>::StaticMethod("checked", &JSRadio::Checked);
    JSClass<JSRadio>::StaticMethod("size", &JSRadio::JsSize);
    JSClass<JSRadio>::StaticMethod("padding", &JSRadio::JsPadding);
    JSClass<JSRadio>::StaticMethod("radioStyle", &JSRadio::JsRadioStyle);
    JSClass<JSRadio>::StaticMethod("responseRegion", &JSRadio::JsResponseRegion);
    JSClass<JSRadio>::StaticMethod("hoverEffect", &JSRadio::JsHoverEffect);
    JSClass<JSRadio>::StaticMethod("onChange", &JSRadio::OnChange);
    JSClass<JSRadio>::StaticMethod("onClick", &JSRadio::JsOnClick);
    JSClass<JSRadio>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRadio>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRadio>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRadio>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSRadio>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRadio>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSRadio>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRadio>::InheritAndBind<JSViewAbstract>(globalObj);
}

void ParseCheckedObject(const JSCallbackInfo& args, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChecked = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](bool check) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Radio.onChangeEvent");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(check));
        func->ExecuteJS(1, &newJSVal);
    };
    RadioModel::GetInstance()->SetOnChangeEvent(std::move(onChecked));
}

void JSRadio::Checked(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        return;
    }
    bool checked = false;
    JSRef<JSVal> changeEventVal;
    auto checkedVal = info[0];
    if (checkedVal->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(checkedVal);
        checkedVal = obj->GetProperty("value");
        changeEventVal = obj->GetProperty("$value");
    } else if (info.Length() > 1) {
        changeEventVal = info[1];
    }

    if (checkedVal->IsBoolean()) {
        checked = checkedVal->ToBoolean();
    }

    RadioModel::GetInstance()->SetChecked(checked);

    if (changeEventVal->IsFunction()) {
        ParseCheckedObject(info, changeEventVal);
    }
}

void JSRadio::JsSize(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        JSViewAbstract::JsWidth(JSVal::Undefined());
        JSViewAbstract::JsHeight(JSVal::Undefined());
        return;
    }
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSViewAbstract::JsWidth(sizeObj->GetProperty(static_cast<int32_t>(ArkUIIndex::WIDTH)));
    JSViewAbstract::JsHeight(sizeObj->GetProperty(static_cast<int32_t>(ArkUIIndex::HEIGHT)));
}

void JSRadio::JsPadding(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    NG::PaddingPropertyF oldPadding = GetOldPadding(info);
    NG::PaddingProperty newPadding = GetNewPadding(info);
    RadioModel::GetInstance()->SetPadding(oldPadding, newPadding);
}

NG::PaddingPropertyF JSRadio::GetOldPadding(const JSCallbackInfo& info)
{
    NG::PaddingPropertyF padding({ 0.0f, 0.0f, 0.0f, 0.0f });
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        if (jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::TOP)) ||
            jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)) ||
            jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::LEFT)) ||
            jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::RIGHT))) {
            CalcDimension topDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension leftDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension rightDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension bottomDimen = CalcDimension(0.0, DimensionUnit::VP);
            ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), topDimen);
            ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT)), leftDimen);
            ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT)), rightDimen);
            ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottomDimen);
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
            return padding;
        }
    }

    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        return padding;
    }

    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    return padding;
}

NG::PaddingProperty JSRadio::GetNewPadding(const JSCallbackInfo& info)
{
    NG::PaddingProperty padding({ NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp),
        NG::CalcLength(0.0_vp), std::nullopt, std::nullopt });
    if (info[0]->IsObject()) {
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);
        CommonCalcDimension commonCalcDimension;
        JSViewAbstract::ParseCommonMarginOrPaddingCorner(paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            return GetPadding(commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left,
                commonCalcDimension.right);
        }
    }
    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        length.Reset();
    }

    padding.SetEdges(NG::CalcLength(length.IsNonNegative() ? length : CalcDimension()));
    return padding;
}

NG::PaddingProperty JSRadio::GetPadding(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
    const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty padding({ NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp),
        NG::CalcLength(0.0_vp), std::nullopt, std::nullopt });
    if (left.has_value() && left.value().IsNonNegative()) {
        padding.left = NG::CalcLength(left.value());
    }
    if (right.has_value() && right.value().IsNonNegative()) {
        padding.right = NG::CalcLength(right.value());
    }
    if (top.has_value() && top.value().IsNonNegative()) {
        padding.top = NG::CalcLength(top.value());
    }
    if (bottom.has_value() && bottom.value().IsNonNegative()) {
        padding.bottom = NG::CalcLength(bottom.value());
    }
    return padding;
}

void JSRadio::JsRadioStyle(const JSCallbackInfo& info)
{
    auto theme = GetTheme<RadioTheme>();
    if (!info[0]->IsObject()) {
        RadioModel::GetInstance()->SetCheckedBackgroundColor(theme->GetActiveColor());
        RadioModel::GetInstance()->SetUncheckedBorderColor(theme->GetInactiveColor());
        RadioModel::GetInstance()->SetIndicatorColor(theme->GetPointColor());
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> checkedBackgroundColor = obj->GetProperty("checkedBackgroundColor");
    JSRef<JSVal> uncheckedBorderColor = obj->GetProperty("uncheckedBorderColor");
    JSRef<JSVal> indicatorColor = obj->GetProperty("indicatorColor");
    Color checkedBackgroundColorVal;
    if (!ParseJsColor(checkedBackgroundColor, checkedBackgroundColorVal)) {
        if (!JSRadioTheme::ObtainCheckedBackgroundColor(checkedBackgroundColorVal)) {
            checkedBackgroundColorVal = theme->GetActiveColor();
        }
    }
    RadioModel::GetInstance()->SetCheckedBackgroundColor(checkedBackgroundColorVal);
    Color uncheckedBorderColorVal;
    if (!ParseJsColor(uncheckedBorderColor, uncheckedBorderColorVal)) {
        if (!JSRadioTheme::ObtainUncheckedBorderColor(uncheckedBorderColorVal)) {
            uncheckedBorderColorVal = theme->GetInactiveColor();
        }
    } else {
        auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<NG::RadioPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsUserSetUncheckBorderColor(true);
    }
    RadioModel::GetInstance()->SetUncheckedBorderColor(uncheckedBorderColorVal);
    Color indicatorColorVal;
    if (!ParseJsColor(indicatorColor, indicatorColorVal)) {
        if (!JSRadioTheme::ObtainIndicatorColor(indicatorColorVal)) {
            indicatorColorVal = theme->GetPointColor();
        }
    }
    RadioModel::GetInstance()->SetIndicatorColor(indicatorColorVal);
}

void JSRadio::JsResponseRegion(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    std::vector<DimensionRect> result;
    if (!JSViewAbstract::ParseJsResponseRegionArray(info[0], result)) {
        return;
    }

    RadioModel::GetInstance()->SetResponseRegion(result);
}

void JSRadio::OnChange(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](bool check) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Radio.onChange");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(check));
        func->ExecuteJS(1, &newJSVal);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        UiSessionManager::GetInstance().ReportComponentChangeEvent("event", "Radio.onChange");
#endif
    };
    RadioModel::GetInstance()->SetOnChange(std::move(onChange));
    args.ReturnSelf();
}

void JSRadio::JsOnClick(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsOnClick(args);
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }
    RadioModel::GetInstance()->SetOnClickEvent(
        JsEventCallback<void()>(args.GetExecutionContext(), JSRef<JSFunc>::Cast(args[0])));

    args.ReturnSelf();
}

void JSRadio::JsHoverEffect(const JSCallbackInfo& info)
{
    if (info[0]->IsNumber()) {
        RadioModel::GetInstance()->SetHoverEffect(static_cast<HoverEffectType>(info[0]->ToNumber<int32_t>()));
    }
}
} // namespace OHOS::Ace::Framework
