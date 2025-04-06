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

#include "bridge/declarative_frontend/jsview/js_select.h"

#include <cstdint>
#include <string>
#include <vector>
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_popups.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/js_symbol_modifier.h"
#include "bridge/declarative_frontend/jsview/models/select_model_impl.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/select/select_model.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_properties.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
std::unique_ptr<SelectModel> SelectModel::instance_ = nullptr;
std::mutex SelectModel::mutex_;

SelectModel* SelectModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::SelectModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::SelectModelNG());
            } else {
                instance_.reset(new Framework::SelectModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSSelect::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 0) {
        return;
    }
    if (info[0]->IsArray()) {
        auto paramArray = JSRef<JSArray>::Cast(info[0]);
        size_t size = paramArray->Length();
        std::vector<SelectParam> params(size);
        for (size_t i = 0; i < size; i++) {
            std::string value;
            std::string icon;
            JSRef<JSVal> indexVal = paramArray->GetValueAt(i);
            if (!indexVal->IsObject()) {
                return;
            }
            auto indexObject = JSRef<JSObject>::Cast(indexVal);
            auto selectValue = indexObject->GetProperty("value");
            auto selectIcon = indexObject->GetProperty("icon");
            auto selectSymbolIcon = indexObject->GetProperty("symbolIcon");
            RefPtr<JSSymbolGlyphModifier> selectSymbol = AceType::MakeRefPtr<JSSymbolGlyphModifier>();
            selectSymbol->symbol_ = selectSymbolIcon;
            params[i].symbolModifier = selectSymbol;
            ParseJsString(selectValue, value);
            params[i].text = value;
            if (selectSymbolIcon->IsObject()) {
                std::function<void(WeakPtr<NG::FrameNode>)> symbolApply = nullptr;
                JSViewAbstract::SetSymbolOptionApply(info, symbolApply, selectSymbolIcon);
                params[i].symbolIcon = symbolApply;
            } else {
                ParseJsMedia(selectIcon, icon);
                params[i].icon = icon;
            }
        }
        SelectModel::GetInstance()->Create(params);
    }
}

void JSSelect::JSBind(BindingTarget globalObj)
{
    JSClass<JSSelect>::Declare("Select");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSelect>::StaticMethod("create", &JSSelect::Create, opt);

    JSClass<JSSelect>::StaticMethod("selected", &JSSelect::Selected, opt);
    JSClass<JSSelect>::StaticMethod("value", &JSSelect::Value, opt);
    JSClass<JSSelect>::StaticMethod("font", &JSSelect::Font, opt);
    JSClass<JSSelect>::StaticMethod("fontColor", &JSSelect::FontColor, opt);
    JSClass<JSSelect>::StaticMethod("backgroundColor", &JSSelect::BackgroundColor, opt);
    JSClass<JSSelect>::StaticMethod("selectedOptionBgColor", &JSSelect::SelectedOptionBgColor, opt);
    JSClass<JSSelect>::StaticMethod("selectedOptionFont", &JSSelect::SelectedOptionFont, opt);
    JSClass<JSSelect>::StaticMethod("selectedOptionFontColor", &JSSelect::SelectedOptionFontColor, opt);
    JSClass<JSSelect>::StaticMethod("optionBgColor", &JSSelect::OptionBgColor, opt);
    JSClass<JSSelect>::StaticMethod("optionFont", &JSSelect::OptionFont, opt);
    JSClass<JSSelect>::StaticMethod("optionFontColor", &JSSelect::OptionFontColor, opt);
    JSClass<JSSelect>::StaticMethod("onSelect", &JSSelect::OnSelected, opt);
    JSClass<JSSelect>::StaticMethod("space", &JSSelect::SetSpace, opt);
    JSClass<JSSelect>::StaticMethod("arrowPosition", &JSSelect::SetArrowPosition, opt);
    JSClass<JSSelect>::StaticMethod("menuAlign", &JSSelect::SetMenuAlign, opt);
    JSClass<JSSelect>::StaticMethod("avoidance", &JSSelect::SetAvoidance, opt);

    // API7 onSelected deprecated
    JSClass<JSSelect>::StaticMethod("onSelected", &JSSelect::OnSelected, opt);
    JSClass<JSSelect>::StaticMethod("size", &JSSelect::JsSize);
    JSClass<JSSelect>::StaticMethod("padding", &JSSelect::JsPadding);
    JSClass<JSSelect>::StaticMethod("paddingTop", &JSSelect::SetPaddingTop, opt);
    JSClass<JSSelect>::StaticMethod("paddingBottom", &JSSelect::SetPaddingBottom, opt);
    JSClass<JSSelect>::StaticMethod("paddingLeft", &JSSelect::SetPaddingLeft, opt);
    JSClass<JSSelect>::StaticMethod("paddingRight", &JSSelect::SetPaddingRight, opt);
    JSClass<JSSelect>::StaticMethod("optionWidth", &JSSelect::SetOptionWidth, opt);
    JSClass<JSSelect>::StaticMethod("optionHeight", &JSSelect::SetOptionHeight, opt);
    JSClass<JSSelect>::StaticMethod("optionWidthFitTrigger", &JSSelect::SetOptionWidthFitTrigger, opt);
    JSClass<JSSelect>::StaticMethod("menuBackgroundColor", &JSSelect::SetMenuBackgroundColor, opt);
    JSClass<JSSelect>::StaticMethod("menuBackgroundBlurStyle", &JSSelect::SetMenuBackgroundBlurStyle, opt);
    JSClass<JSSelect>::StaticMethod("divider", &JSSelect::SetDivider);
    JSClass<JSSelect>::StaticMethod("controlSize", &JSSelect::SetControlSize);
    JSClass<JSSelect>::StaticMethod("direction", &JSSelect::SetDirection, opt);
    JSClass<JSSelect>::StaticMethod("dividerStyle", &JSSelect::SetDividerStyle);
    JSClass<JSSelect>::StaticMethod("menuOutline", &JSSelect::SetMenuOutline, opt);
    JSClass<JSSelect>::StaticMethod("arrowModifier", &JSSelect::SetArrowModifier, opt);
    JSClass<JSSelect>::StaticMethod("textModifier", &JSSelect::SetTextModifier, opt);
    JSClass<JSSelect>::StaticMethod("optionTextModifier", &JSSelect::SetOptionTextModifier, opt);
    JSClass<JSSelect>::StaticMethod("selectedOptionTextModifier", &JSSelect::SetSelectedOptionTextModifier, opt);

    JSClass<JSSelect>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSelect>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSelect>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSelect>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSelect>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSSelect>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSelect>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSSelect>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSelect>::InheritAndBind<JSViewAbstract>(globalObj);
}

void ParseSelectedObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onSelect = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](int32_t index) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Select.SelectChangeEvent");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(index));
        func->ExecuteJS(1, &newJSVal);
    };
    SelectModel::GetInstance()->SetSelectChangeEvent(onSelect);
}

void JSSelect::Selected(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        return;
    }

    int32_t value = 0;

    bool result = ParseJsInteger<int32_t>(info[0], value);

    if (value < -1) {
        value = -1;
    }
    JSRef<JSVal> changeEventVal;
    auto selectedVal = info[0];
    if (!result && selectedVal->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(selectedVal);
        selectedVal = obj->GetProperty("value");
        changeEventVal = obj->GetProperty("$value");
        ParseJsInteger<int32_t>(selectedVal, value);
    } else if (info.Length() > 1) {
        changeEventVal = info[1];
    }

    if (changeEventVal->IsFunction()) {
        ParseSelectedObject(info, changeEventVal);
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set selected index %{public}d", value);
    SelectModel::GetInstance()->SetSelected(value);
}

void ParseValueObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onSelect = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        const std::string& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Select.ValueChangeEvent");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(value));
        func->ExecuteJS(1, &newJSVal);
    };
    SelectModel::GetInstance()->SetValueChangeEvent(onSelect);
}

void JSSelect::Value(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        return;
    }

    std::string value;
    
    bool result = ParseJsString(info[0], value);

    JSRef<JSVal> changeEventVal;
    auto selectedVal = info[0];
    if (!result && selectedVal->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(selectedVal);
        selectedVal = obj->GetProperty("value");
        changeEventVal = obj->GetProperty("$value");
        ParseJsString(selectedVal, value);
    } else if (info.Length() > 1) {
        changeEventVal = info[1];
    }

    if (changeEventVal->IsFunction()) {
        ParseValueObject(info, changeEventVal);
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "value set by user");
    SelectModel::GetInstance()->SetValue(value);
}

void JSSelect::Font(const JSCallbackInfo& info)
{
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        ResetFont(SelectFontType::SELECT);
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    ParseFontSize(param->GetProperty("size"), SelectFontType::SELECT);
    ParseFontWeight(param->GetProperty("weight"), SelectFontType::SELECT);
    ParseFontFamily(param->GetProperty("family"), SelectFontType::SELECT);
    ParseFontStyle(param->GetProperty("style"), SelectFontType::SELECT);
}

void JSSelect::ParseFontSize(const JSRef<JSVal>& jsValue, SelectFontType type)
{
    CalcDimension fontSize;
    if (!ParseJsDimensionFp(jsValue, fontSize)) {
        ResetFontSize(type);
        return;
    }
    if (type == SelectFontType::SELECT) {
        SelectModel::GetInstance()->SetFontSize(fontSize);
    } else if (type == SelectFontType::OPTION) {
        SelectModel::GetInstance()->SetOptionFontSize(fontSize);
    } else if (type == SelectFontType::SELECTED_OPTION) {
        SelectModel::GetInstance()->SetSelectedOptionFontSize(fontSize);
    }
}

void JSSelect::ParseFontWeight(const JSRef<JSVal>& jsValue, SelectFontType type)
{
    std::string weight;
    if (jsValue->IsNumber()) {
        weight = std::to_string(jsValue->ToNumber<int32_t>());
    } else {
        ParseJsString(jsValue, weight);
    }
    if (type == SelectFontType::SELECT) {
        SelectModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(weight, FontWeight::MEDIUM));
    } else if (type == SelectFontType::OPTION) {
        SelectModel::GetInstance()->SetOptionFontWeight(ConvertStrToFontWeight(weight, FontWeight::REGULAR));
    } else if (type == SelectFontType::SELECTED_OPTION) {
        SelectModel::GetInstance()->SetSelectedOptionFontWeight(ConvertStrToFontWeight(weight, FontWeight::REGULAR));
    }
}

void JSSelect::ParseFontFamily(const JSRef<JSVal>& jsValue, SelectFontType type)
{
    if (!jsValue->IsString()) {
        ResetFontFamily(type);
        return;
    }
    auto family = ConvertStrToFontFamilies(jsValue->ToString());
    if (type == SelectFontType::SELECT) {
        SelectModel::GetInstance()->SetFontFamily(family);
    } else if (type == SelectFontType::OPTION) {
        SelectModel::GetInstance()->SetOptionFontFamily(family);
    } else if (type == SelectFontType::SELECTED_OPTION) {
        SelectModel::GetInstance()->SetSelectedOptionFontFamily(family);
    }
}

void JSSelect::ParseFontStyle(const JSRef<JSVal>& jsValue, SelectFontType type)
{
    if (!jsValue->IsNumber()) {
        ResetFontStyle(type);
        return;
    }
    auto styleVal = static_cast<FontStyle>(jsValue->ToNumber<int32_t>());
    if (type == SelectFontType::SELECT) {
        SelectModel::GetInstance()->SetItalicFontStyle(styleVal);
    } else if (type == SelectFontType::OPTION) {
        SelectModel::GetInstance()->SetOptionItalicFontStyle(styleVal);
    } else if (type == SelectFontType::SELECTED_OPTION) {
        SelectModel::GetInstance()->SetSelectedOptionItalicFontStyle(styleVal);
    }
}

void JSSelect::ResetFontSize(SelectFontType type)
{
    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    if (type == SelectFontType::OPTION) {
        SelectModel::GetInstance()->SetOptionFontSize(selectTheme->GetMenuFontSize());
        return;
    } else if (type == SelectFontType::SELECTED_OPTION) {
        SelectModel::GetInstance()->SetSelectedOptionFontSize(selectTheme->GetMenuFontSize());
        return;
    }
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        SelectModel::GetInstance()->SetFontSize(selectTheme->GetFontSize());
    } else {
        auto controlSize = SelectModel::GetInstance()->GetControlSize();
        SelectModel::GetInstance()->SetFontSize(selectTheme->GetFontSize(controlSize));
    }
}

void JSSelect::ResetFontWeight(SelectFontType type)
{
    if (type == SelectFontType::SELECT) {
        SelectModel::GetInstance()->SetFontWeight(FontWeight::MEDIUM);
    } else if (type == SelectFontType::OPTION) {
        SelectModel::GetInstance()->SetOptionFontWeight(FontWeight::REGULAR);
    } else if (type == SelectFontType::SELECTED_OPTION) {
        SelectModel::GetInstance()->SetSelectedOptionFontWeight(FontWeight::REGULAR);
    }
}

void JSSelect::ResetFontFamily(SelectFontType type)
{
    auto textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    if (type == SelectFontType::SELECT) {
        SelectModel::GetInstance()->SetFontFamily(textTheme->GetTextStyle().GetFontFamilies());
    } else if (type == SelectFontType::OPTION) {
        SelectModel::GetInstance()->SetOptionFontFamily(textTheme->GetTextStyle().GetFontFamilies());
    } else if (type == SelectFontType::SELECTED_OPTION) {
        SelectModel::GetInstance()->SetSelectedOptionFontFamily(textTheme->GetTextStyle().GetFontFamilies());
    }
}

void JSSelect::ResetFontStyle(SelectFontType type)
{
    auto textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    if (type == SelectFontType::SELECT) {
        SelectModel::GetInstance()->SetItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
    } else if (type == SelectFontType::OPTION) {
        SelectModel::GetInstance()->SetOptionItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
    } else if (type == SelectFontType::SELECTED_OPTION) {
        SelectModel::GetInstance()->SetSelectedOptionItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
    }
}

void JSSelect::ResetFont(SelectFontType type)
{
    ResetFontSize(type);
    ResetFontWeight(type);
    ResetFontFamily(type);
    ResetFontStyle(type);
}

void JSSelect::FontColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        SelectModel::GetInstance()->ResetFontColor();
        return;
    }

    SelectModel::GetInstance()->SetFontColor(textColor);
}

void JSSelect::BackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor)) {
        backgroundColor = Color::TRANSPARENT;
    }

    SelectModel::GetInstance()->BackgroundColor(backgroundColor);
}

void JSSelect::SelectedOptionBgColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color bgColor;
    if (!ParseJsColor(info[0], bgColor)) {
        if (info[0]->IsUndefined() || info[0]->IsNull()) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<SelectTheme>();
            CHECK_NULL_VOID(theme);
            bgColor = theme->GetSelectedColor();
        } else {
            return;
        }
    }
    SelectModel::GetInstance()->SetSelectedOptionBgColor(bgColor);
}

void JSSelect::SelectedOptionFont(const JSCallbackInfo& info)
{
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        ResetFont(SelectFontType::SELECTED_OPTION);
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    ParseFontSize(param->GetProperty("size"), SelectFontType::SELECTED_OPTION);
    ParseFontWeight(param->GetProperty("weight"), SelectFontType::SELECTED_OPTION);
    ParseFontFamily(param->GetProperty("family"), SelectFontType::SELECTED_OPTION);
    ParseFontStyle(param->GetProperty("style"), SelectFontType::SELECTED_OPTION);
}

void JSSelect::SelectedOptionFontColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        if (info[0]->IsNull() || info[0]->IsUndefined()) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<SelectTheme>();
            CHECK_NULL_VOID(theme);
            textColor = theme->GetSelectedColorText();
        } else {
            return;
        }
    }
    SelectModel::GetInstance()->SetSelectedOptionFontColor(textColor);
}

void JSSelect::OptionBgColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color bgColor;
    if (!ParseJsColor(info[0], bgColor)) {
        if (info[0]->IsUndefined() || info[0]->IsNull()) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<SelectTheme>();
            CHECK_NULL_VOID(theme);
            bgColor = theme->GetBackgroundColor();
        } else {
            return;
        }
    }

    SelectModel::GetInstance()->SetOptionBgColor(bgColor);
}

void JSSelect::OptionFont(const JSCallbackInfo& info)
{
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        ResetFont(SelectFontType::OPTION);
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    ParseFontSize(param->GetProperty("size"), SelectFontType::OPTION);
    ParseFontWeight(param->GetProperty("weight"), SelectFontType::OPTION);
    ParseFontFamily(param->GetProperty("family"), SelectFontType::OPTION);
    ParseFontStyle(param->GetProperty("style"), SelectFontType::OPTION);
}

void JSSelect::OptionFontColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        if (info[0]->IsUndefined() || info[0]->IsNull()) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<SelectTheme>();
            CHECK_NULL_VOID(theme);
            textColor = theme->GetMenuFontColor();
        } else {
            return;
        }
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set option font color %{public}s", textColor.ColorToString().c_str());
    SelectModel::GetInstance()->SetOptionFontColor(textColor);
}

void JSSelect::OnSelected(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onSelect = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        int32_t index, const std::string& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Select.onSelect");
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "fire change event %{public}d %{public}s", index, value.c_str());
        PipelineContext::SetCallBackNode(node);
        JSRef<JSVal> params[2];
        params[0] = JSRef<JSVal>::Make(ToJSValue(index));
        params[1] = JSRef<JSVal>::Make(ToJSValue(value));
        func->ExecuteJS(2, params);
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Select.onSelect");
    };
    SelectModel::GetInstance()->SetOnSelect(std::move(onSelect));
    info.ReturnSelf();
}

void JSSelect::JsSize(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        JSViewAbstract::JsWidth(JSVal::Undefined());
        JSViewAbstract::JsHeight(JSVal::Undefined());
        return;
    }
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSViewAbstract::JsWidth(sizeObj->GetProperty("width"));
    JSViewAbstract::JsHeight(sizeObj->GetProperty("height"));
}

void JSSelect::JsPadding(const JSCallbackInfo& info)
{
    if (!info[0]->IsString() && !info[0]->IsNumber() && !info[0]->IsObject()) {
        return;
    }

    if (info[0]->IsObject()) {
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);
        CommonCalcDimension commonCalcDimension;
        JSViewAbstract::ParseCommonMarginOrPaddingCorner(paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            ViewAbstractModel::GetInstance()->SetPaddings(commonCalcDimension.top, commonCalcDimension.bottom,
                commonCalcDimension.left, commonCalcDimension.right);
            return;
        }
    }

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value.Reset();
    }
    SelectModel::GetInstance()->SetPadding(value);
}

void JSSelect::SetPaddingLeft(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    SelectModel::GetInstance()->SetPaddingLeft(value);
}

void JSSelect::SetPaddingTop(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    SelectModel::GetInstance()->SetPaddingTop(value);
}

void JSSelect::SetPaddingRight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    SelectModel::GetInstance()->SetPaddingRight(value);
}

void JSSelect::SetPaddingBottom(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    SelectModel::GetInstance()->SetPaddingBottom(value);
}

void JSSelect::SetSpace(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    auto selectTheme = GetTheme<SelectTheme>();

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value = selectTheme->GetContentSpinnerPadding();
    }
    if (LessNotEqual(value.Value(), 0.0) || value.Unit() == DimensionUnit::PERCENT) {
        value = selectTheme->GetContentSpinnerPadding();
    }

    SelectModel::GetInstance()->SetSpace(value);
}

void JSSelect::SetArrowPosition(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    int32_t direction = 0;
    if (!ParseJsInt32(info[0], direction)) {
        direction = 0;
    }

    if (static_cast<ArrowPosition>(direction) != ArrowPosition::START &&
        static_cast<ArrowPosition>(direction) != ArrowPosition::END) {
        direction = 0;
    }

    SelectModel::GetInstance()->SetArrowPosition(static_cast<ArrowPosition>(direction));
}

void JSSelect::SetMenuAlign(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    MenuAlign menuAlignObj;

    if (!info[0]->IsNumber()) {
        if (!(info[0]->IsUndefined() || info[0]->IsNull())) {
            return;
        }
    } else {
        menuAlignObj.alignType = static_cast<MenuAlignType>(info[0]->ToNumber<int32_t>());
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set alignType %{public}d", menuAlignObj.alignType);
    }

    if (info.Length() > 1) {
        if (info[1]->IsUndefined() || info[1]->IsNull()) {
            SelectModel::GetInstance()->SetMenuAlign(menuAlignObj);
            return;
        }
        if (!info[1]->IsObject()) {
            return;
        }
        auto offsetObj = JSRef<JSObject>::Cast(info[1]);
        CalcDimension dx;
        auto dxValue = offsetObj->GetProperty("dx");
        ParseJsDimensionVp(dxValue, dx);
        CalcDimension dy;
        auto dyValue = offsetObj->GetProperty("dy");
        ParseJsDimensionVp(dyValue, dy);
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set offset dx %{public}f dy %{public}f", dx.Value(), dy.Value());
        menuAlignObj.offset = DimensionOffset(dx, dy);
    }

    SelectModel::GetInstance()->SetMenuAlign(menuAlignObj);
}

void JSSelect::SetAvoidance(const JSCallbackInfo& info)
{
    AvoidanceMode mode = AvoidanceMode::COVER_TARGET;
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsNumber()) {
        SelectModel::GetInstance()->SetAvoidance(mode);
        return;
    }

    int32_t value = info[0]->ToNumber<int32_t>();
    switch (value) {
        case static_cast<int32_t>(AvoidanceMode::COVER_TARGET):
            mode = AvoidanceMode::COVER_TARGET;
            break;
        case static_cast<int32_t>(AvoidanceMode::AVOID_AROUND_TARGET):
            mode = AvoidanceMode::AVOID_AROUND_TARGET;
            break;
        default:
            break;
    }
    SelectModel::GetInstance()->SetAvoidance(mode);
}

bool JSSelect::IsPercentStr(std::string& percent)
{
    if (percent.find("%") != std::string::npos) {
        size_t index = percent.find("%");
        percent = percent.substr(0, index);
        return true;
    }
    return false;
}

void JSSelect::SetOptionWidth(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (info[0]->IsUndefined() || info[0]->IsNull()) {
        SelectModel::GetInstance()->SetHasOptionWidth(false);
        SelectModel::GetInstance()->SetOptionWidth(value);
        return;
    } else if (info[0]->IsString()) {
        SelectModel::GetInstance()->SetHasOptionWidth(true);
        std::string modeFlag = info[0]->ToString();
        if (modeFlag.compare("fit_content") == 0) {
            SelectModel::GetInstance()->SetOptionWidthFitTrigger(false);
        } else if (modeFlag.compare("fit_trigger") == 0) {
            SelectModel::GetInstance()->SetOptionWidthFitTrigger(true);
        } else if (IsPercentStr(modeFlag)) {
            return;
        } else {
            ParseJsDimensionVpNG(info[0], value);
            if (value.IsNegative()) {
                value.Reset();
            }
            SelectModel::GetInstance()->SetOptionWidth(value);
        }
    } else {
        SelectModel::GetInstance()->SetHasOptionWidth(true);
        ParseJsDimensionVpNG(info[0], value);
        if (value.IsNegative()) {
            value.Reset();
        }
        SelectModel::GetInstance()->SetOptionWidth(value);
    }
}

void JSSelect::SetOptionHeight(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (info[0]->IsUndefined() || info[0]->IsNull()) {
        return;
    } else if (info[0]->IsString()) {
        std::string modeFlag = info[0]->ToString();
        if (IsPercentStr(modeFlag)) {
            return;
        } else {
            ParseJsDimensionVpNG(info[0], value);
            if (value.IsNonPositive()) {
                return;
            }
            SelectModel::GetInstance()->SetOptionHeight(value);
        }
    } else {
        ParseJsDimensionVpNG(info[0], value);
        if (value.IsNonPositive()) {
            return;
        }
        SelectModel::GetInstance()->SetOptionHeight(value);
    }
}

void JSSelect::SetOptionWidthFitTrigger(const JSCallbackInfo& info)
{
    bool isFitTrigger = false;
    if (info[0]->IsBoolean()) {
        isFitTrigger = info[0]->ToBoolean();
    }

    SelectModel::GetInstance()->SetOptionWidthFitTrigger(isFitTrigger);
}

void JSSelect::SetMenuBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color menuBackgroundColor;
    if (!ParseJsColor(info[0], menuBackgroundColor)) {
        if (info[0]->IsNull() || info[0]->IsUndefined()) {
            menuBackgroundColor = Color::TRANSPARENT;
        } else {
            return;
        }
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set menu background color %{public}s",
        menuBackgroundColor.ColorToString().c_str());
    SelectModel::GetInstance()->SetMenuBackgroundColor(menuBackgroundColor);
}

void JSSelect::SetMenuBackgroundBlurStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    BlurStyleOption styleOption;
    if (info[0]->IsNumber()) {
        auto blurStyle = info[0]->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
            TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "set menu blurStyle %{public}d", blurStyle);
            SelectModel::GetInstance()->SetMenuBackgroundBlurStyle(styleOption);
        }
    }
}

void JSSelect::SetControlSize(const JSCallbackInfo& info)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsNumber()) {
        auto controlSize = static_cast<ControlSize>(info[0]->ToNumber<int32_t>());
        SelectModel::GetInstance()->SetControlSize(controlSize);
    } else {
        LOGE("JSSelect::SetControlSize Is not Number.");
    }
}

void JSSelect::SetDivider(const JSCallbackInfo& info)
{
    NG::SelectDivider divider;
    auto selectTheme = GetTheme<SelectTheme>();
    Dimension defaultStrokeWidth = 0.0_vp;
    Dimension defaultMargin = -1.0_vp;
    Color defaultColor = Color::TRANSPARENT;
    // Set default strokeWidth and color
    if (selectTheme) {
        defaultStrokeWidth = selectTheme->GetDefaultDividerWidth();
        defaultColor = selectTheme->GetLineColor();
        divider.strokeWidth = defaultStrokeWidth;
        divider.color = defaultColor;
        divider.startMargin = defaultMargin;
        divider.endMargin = defaultMargin;
    }

    if (info.Length() >= 1 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
       
        Dimension strokeWidth = defaultStrokeWidth;
        if (ConvertFromJSValueNG(obj->GetProperty("strokeWidth"), strokeWidth) && CheckDividerValue(strokeWidth)) {
            divider.strokeWidth = strokeWidth;
        }
        
        Color color = defaultColor;
        if (ConvertFromJSValue(obj->GetProperty("color"), color)) {
            divider.color = color;
        }

        Dimension startMargin = defaultMargin;
        if (ConvertFromJSValueNG(obj->GetProperty("startMargin"), startMargin) && CheckDividerValue(startMargin)) {
            divider.startMargin = startMargin;
        }

        Dimension endMargin = defaultMargin;
        if (ConvertFromJSValueNG(obj->GetProperty("endMargin"), endMargin) &&  CheckDividerValue(endMargin)) {
            divider.endMargin = endMargin;
        }
    } else if (info.Length() >= 1 && info[0]->IsNull()) {
        divider.strokeWidth = 0.0_vp;
    }
    SelectModel::GetInstance()->SetDivider(divider);
}

void JSSelect::SetDividerStyle(const JSCallbackInfo& info)
{
    NG::SelectDivider divider;
    Dimension defaultStrokeWidth = 0.0_vp;
    Dimension defaultMargin = -1.0_vp;
    Color defaultColor = Color::TRANSPARENT;
    auto selectTheme = GetTheme<SelectTheme>();
    if (selectTheme) {
        defaultStrokeWidth = selectTheme->GetDefaultDividerWidth();
        defaultColor = selectTheme->GetLineColor();
        divider.strokeWidth = defaultStrokeWidth;
        divider.color = defaultColor;
        divider.startMargin = defaultMargin;
        divider.endMargin = defaultMargin;
    }
    if (info.Length() >= 1 && info[0]->IsObject()) {
        auto mode = DividerMode::FLOATING_ABOVE_MENU;
        divider.isDividerStyle = true;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        CalcDimension value;
        if (ParseLengthMetricsToPositiveDimension(obj->GetProperty("strokeWidth"), value) && value.IsNonNegative()) {
            divider.strokeWidth = value;
        }
        if (ParseLengthMetricsToPositiveDimension(obj->GetProperty("startMargin"), value) && value.IsNonNegative()) {
            divider.startMargin = value;
        }
        if (ParseLengthMetricsToPositiveDimension(obj->GetProperty("endMargin"), value) && value.IsNonNegative()) {
            divider.endMargin = value;
        }
        if (!ConvertFromJSValue(obj->GetProperty("color"), divider.color)) {
            divider.color = defaultColor;
        }
        auto modeVal = obj->GetProperty("mode");
        if (modeVal->IsNumber() && modeVal->ToNumber<int32_t>() == 1) {
            mode = DividerMode::EMBEDDED_IN_MENU;
        }
        SelectModel::GetInstance()->SetDividerStyle(divider, mode);
    } else {
        divider.isDividerStyle = false;
        SelectModel::GetInstance()->SetDivider(divider);
    }
}

bool JSSelect::CheckDividerValue(const Dimension &dimension)
{
    if (dimension.Value() >= 0.0f && dimension.Unit() != DimensionUnit::PERCENT) {
        return true;
    }
    return false;
}

void JSSelect::SetDirection(const std::string& dir)
{
    TextDirection direction = TextDirection::AUTO;
    if (dir == "Ltr") {
        direction = TextDirection::LTR;
    } else if (dir == "Rtl") {
        direction = TextDirection::RTL;
    } else if (dir == "Auto") {
        direction = TextDirection::AUTO;
    } else if (dir == "undefined" && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        direction = TextDirection::AUTO;
    }
    SelectModel::GetInstance()->SetLayoutDirection(direction);
}

void JSSelect::SetMenuOutline(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto menuTheme = GetTheme<NG::MenuTheme>();
    NG::MenuParam menuParam;
    MenuDefaultParam(menuParam);
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        NG::BorderWidthProperty outlineWidth;
        outlineWidth.SetBorderWidth(Dimension(menuTheme->GetOuterBorderWidth()));
        menuParam.outlineWidth = outlineWidth;
        NG::BorderColorProperty outlineColor;
        outlineColor.SetColor(menuTheme->GetOuterBorderColor());
        menuParam.outlineColor = outlineColor;
    } else {
        auto menuOptions = JSRef<JSObject>::Cast(info[0]);
        auto outlineWidthValue = menuOptions->GetProperty("width");
        JSViewPopups::ParseMenuOutlineWidth(outlineWidthValue, menuParam);
        auto outlineColorValue = menuOptions->GetProperty("color");
        JSViewPopups::ParseMenuOutlineColor(outlineColorValue, menuParam);
    }
    SelectModel::GetInstance()->SetMenuOutline(menuParam);
}

void JSSelect::SetArrowModifier(const JSCallbackInfo& info)
{
    std::function<void(WeakPtr<NG::FrameNode>)> applyFunc = nullptr;
    if (info.Length() < 1 || info[0]->IsNull() || info[0]->IsUndefined() || !info[0]->IsObject() ||
        !SystemProperties::IsNeedSymbol()) {
        SelectModel::GetInstance()->SetArrowModifierApply(applyFunc);
        return;
    }
    JSViewAbstract::SetSymbolOptionApply(info, applyFunc, info[0]);
    SelectModel::GetInstance()->SetArrowModifierApply(applyFunc);
}

void JSSelect::SetTextModifier(const JSCallbackInfo& info)
{
    std::function<void(WeakPtr<NG::FrameNode>)> applyFunc = nullptr;
    if (info.Length() < 1 || info[0]->IsNull() || info[0]->IsUndefined() || !info[0]->IsObject()) {
        SelectModel::GetInstance()->SetTextModifierApply(applyFunc);
        return;
    }
    JSViewAbstract::SetTextStyleApply(info, applyFunc, info[0]);
    SelectModel::GetInstance()->SetTextModifierApply(applyFunc);
}

void JSSelect::SetOptionTextModifier(const JSCallbackInfo& info)
{
    std::function<void(WeakPtr<NG::FrameNode>)> applyFunc = nullptr;
    if (info.Length() < 1 || info[0]->IsNull() || info[0]->IsUndefined() || !info[0]->IsObject()) {
        SelectModel::GetInstance()->SetOptionTextModifier(applyFunc);
        return;
    }
    JSViewAbstract::SetTextStyleApply(info, applyFunc, info[0]);
    SelectModel::GetInstance()->SetOptionTextModifier(applyFunc);
}

void JSSelect::SetSelectedOptionTextModifier(const JSCallbackInfo& info)
{
    std::function<void(WeakPtr<NG::FrameNode>)> applyFunc = nullptr;
    if (info.Length() < 1 || info[0]->IsNull() || info[0]->IsUndefined() || !info[0]->IsObject()) {
        SelectModel::GetInstance()->SetSelectedOptionTextModifier(applyFunc);
        return;
    }
    JSViewAbstract::SetTextStyleApply(info, applyFunc, info[0]);
    SelectModel::GetInstance()->SetSelectedOptionTextModifier(applyFunc);
}
} // namespace OHOS::Ace::Framework
