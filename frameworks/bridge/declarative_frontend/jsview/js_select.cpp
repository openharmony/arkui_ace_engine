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

#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/select_model_impl.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/select/select_model.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
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
namespace {
constexpr int32_t PLATFORM_VERSION_TEN = 10;
} // namespace

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
            ParseJsString(selectValue, value);
            ParseJsMedia(selectIcon, icon);

            params[i] = { value, icon };
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

    // API7 onSelected deprecated
    JSClass<JSSelect>::StaticMethod("onSelected", &JSSelect::OnSelected, opt);
    JSClass<JSSelect>::StaticMethod("width", &JSSelect::JsWidth);
    JSClass<JSSelect>::StaticMethod("height", &JSSelect::JsHeight);
    JSClass<JSSelect>::StaticMethod("size", &JSSelect::JsSize);
    JSClass<JSSelect>::StaticMethod("padding", &JSSelect::JsPadding);
    JSClass<JSSelect>::StaticMethod("paddingTop", &JSSelect::SetPaddingTop, opt);
    JSClass<JSSelect>::StaticMethod("paddingBottom", &JSSelect::SetPaddingBottom, opt);
    JSClass<JSSelect>::StaticMethod("paddingLeft", &JSSelect::SetPaddingLeft, opt);
    JSClass<JSSelect>::StaticMethod("paddingRight", &JSSelect::SetPaddingRight, opt);

    JSClass<JSSelect>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSelect>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSelect>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSelect>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSelect>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSelect>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSelect>::InheritAndBind<JSViewAbstract>(globalObj);
}

void ParseSelectedObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    auto onSelect = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](int32_t index) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Select.SelectChangeEvent");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(index));
        func->ExecuteJS(1, &newJSVal);
    };
    SelectModel::GetInstance()->SetSelectChangeEvent(onSelect);
}

void JSSelect::Selected(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        LOGE("The arg is wrong, it is supposed to have 1 or 2 arguments");
        return;
    }

    int32_t value = 0;
    if (PipelineBase::GetCurrentContext() &&
        PipelineBase::GetCurrentContext()->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        // default value is -1
        value = -1;
    }
    if (info.Length() > 0 && info[0]->IsNumber()) {
        value = info[0]->ToNumber<int32_t>();
    }

    if (value < -1) {
        value = -1;
    }
    if (info.Length() > 1 && info[1]->IsFunction()) {
        ParseSelectedObject(info, info[1]);
    }
    SelectModel::GetInstance()->SetSelected(value);
}

void ParseValueObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    auto onSelect = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Select.ValueChangeEvent");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(value));
        func->ExecuteJS(1, &newJSVal);
    };
    SelectModel::GetInstance()->SetValueChangeEvent(onSelect);
}

void JSSelect::Value(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        LOGE("The arg is wrong, it is supposed to have 1 or 2 arguments");
        return;
    }

    std::string value;
    if (info.Length() > 0 && info[0]->IsString()) {
        value = info[0]->ToString();
    }

    if (info.Length() > 1 && info[1]->IsFunction()) {
        ParseValueObject(info, info[1]);
    }
    SelectModel::GetInstance()->SetValue(value);
}

void JSSelect::Font(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID_NOLOG(theme);
    auto param = JSRef<JSObject>::Cast(info[0]);
    // set select value font size
    auto size = param->GetProperty("size");
    if (!size->IsNull()) {
        CalcDimension fontSize = theme->GetFontSize();
        if (ParseJsDimensionFp(size, fontSize) || pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            SelectModel::GetInstance()->SetFontSize(fontSize);
        }
    }
    // set select value font weight
    auto fontWeight = param->GetProperty("weight");
    std::string weightStr;
    if (!fontWeight->IsNull()) {
        FontWeight weight = theme->GetFontWeight();
        if (fontWeight->IsNumber()) {
            weight = ConvertStrToFontWeight(std::to_string(fontWeight->ToNumber<int32_t>()));
        } else if (ParseJsString(fontWeight, weightStr)) {
            weight = ConvertStrToFontWeight(weightStr);
        }
        SelectModel::GetInstance()->SetFontWeight(weight);
    }
    // set select value font family
    auto family = param->GetProperty("family");
    if (!family->IsNull()) {
        std::vector<std::string> fontFamily;
        if (family->IsString()) {
            fontFamily = ConvertStrToFontFamilies(family->ToString());
            SelectModel::GetInstance()->SetFontFamily(fontFamily);
        } else if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            SelectModel::GetInstance()->SetFontFamily(fontFamily);
        }
    }
    // set select value font style
    auto style = param->GetProperty("style");
    if (!style->IsNull()) {
        FontStyle fontStyle = FontStyle::NORMAL;
        if (style->IsNumber()) {
            fontStyle = static_cast<FontStyle>(style->ToNumber<int32_t>());
            SelectModel::GetInstance()->SetItalicFontStyle(fontStyle);
        } else if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            SelectModel::GetInstance()->SetItalicFontStyle(fontStyle);
        }
    }
}

void JSSelect::FontColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    Color textColor = theme->GetFontColor();
    ParseJsColor(info[0], textColor);
    SelectModel::GetInstance()->SetFontColor(textColor);
}

void JSSelect::SelectedOptionBgColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color bgColor;
    if (!ParseJsColor(info[0], bgColor)) {
        if (info[0]->IsUndefined() || info[0]->IsNull()) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(pipeline);
            auto theme = pipeline->GetTheme<SelectTheme>();
            CHECK_NULL_VOID_NOLOG(theme);
            bgColor = theme->GetSelectedColor();
        } else {
            return;
        }
    }
    SelectModel::GetInstance()->SetSelectedOptionBgColor(bgColor);
}

void JSSelect::SelectedOptionFont(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID_NOLOG(theme);
    auto param = JSRef<JSObject>::Cast(info[0]);
    // set selected option font size
    auto size = param->GetProperty("size");
    if (!size->IsNull()) {
        CalcDimension fontSize = theme->GetFontSize();
        if (ParseJsDimensionFp(size, fontSize) || pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            SelectModel::GetInstance()->SetSelectedOptionFontSize(fontSize);
        }
    }
    // set selected option font weight
    auto fontWeight = param->GetProperty("weight");
    std::string weightStr;
    if (!fontWeight->IsNull()) {
        FontWeight weight = theme->GetFontWeight();
        if (fontWeight->IsNumber()) {
            weight = ConvertStrToFontWeight(std::to_string(fontWeight->ToNumber<int32_t>()));
        } else if (ParseJsString(fontWeight, weightStr)) {
            weight = ConvertStrToFontWeight(weightStr);
        }
        SelectModel::GetInstance()->SetSelectedOptionFontWeight(weight);
    }
    // set selected option font family
    auto family = param->GetProperty("family");
    if (!family->IsNull()) {
        std::vector<std::string> fontFamily;
        if (family->IsString()) {
            fontFamily = ConvertStrToFontFamilies(family->ToString());
            SelectModel::GetInstance()->SetSelectedOptionFontFamily(fontFamily);
        } else if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            // set theme default value
            SelectModel::GetInstance()->SetSelectedOptionFontFamily(fontFamily);
        }
    }
    // set selected option font style
    auto style = param->GetProperty("style");
    if (!style->IsNull()) {
        FontStyle fontStyle = FontStyle::NORMAL;
        if (style->IsNumber()) {
            fontStyle = static_cast<FontStyle>(style->ToNumber<int32_t>());
            SelectModel::GetInstance()->SetSelectedOptionItalicFontStyle(fontStyle);
        } else if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            // set theme default value
            SelectModel::GetInstance()->SetSelectedOptionItalicFontStyle(fontStyle);
        }
    }
}

void JSSelect::SelectedOptionFontColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    Color textColor = theme->GetSelectedColorText();
    ParseJsColor(info[0], textColor);
    SelectModel::GetInstance()->SetSelectedOptionFontColor(textColor);
}

void JSSelect::OptionBgColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID_NOLOG(theme);
    Color bgColor = theme->GetBackgroundColor();
    if (!ParseJsColor(info[0], bgColor) && pipeline->GetMinPlatformVersion() < PLATFORM_VERSION_TEN) {
        return;
    }
    SelectModel::GetInstance()->SetOptionBgColor(bgColor);
}

void JSSelect::OptionFont(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID_NOLOG(theme);
    auto param = JSRef<JSObject>::Cast(info[0]);
    // set option font size
    auto size = param->GetProperty("size");
    if (!size->IsNull()) {
        CalcDimension fontSize = theme->GetFontSize();
        if (ParseJsDimensionFp(size, fontSize) || pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            SelectModel::GetInstance()->SetOptionFontSize(fontSize);
        }
    }
    // set option font weight
    std::string weightStr;
    auto fontWeight = param->GetProperty("weight");
    if (!fontWeight->IsNull()) {
        FontWeight weight = theme->GetFontWeight();
        if (fontWeight->IsNumber()) {
            weight = ConvertStrToFontWeight(std::to_string(fontWeight->ToNumber<int32_t>()));
        } else if (ParseJsString(fontWeight, weightStr)) {
            weight = ConvertStrToFontWeight(weightStr);
        }
        SelectModel::GetInstance()->SetOptionFontWeight(weight);
    }
    // set option font family
    auto family = param->GetProperty("family");
    if (!family->IsNull()) {
        std::vector<std::string> fontFamily;
        if (family->IsString()) {
            fontFamily = ConvertStrToFontFamilies(family->ToString());
            SelectModel::GetInstance()->SetOptionFontFamily(fontFamily);
        } else if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            // set theme default value
            SelectModel::GetInstance()->SetOptionFontFamily(fontFamily);
        }
    }
    // set option font style
    auto style = param->GetProperty("style");
    if (!style->IsNull()) {
        FontStyle fontStyle = FontStyle::NORMAL;
        if (style->IsNumber()) {
            fontStyle = static_cast<FontStyle>(style->ToNumber<int32_t>());
            SelectModel::GetInstance()->SetOptionItalicFontStyle(fontStyle);
        } else if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
            // set theme default value
            SelectModel::GetInstance()->SetOptionItalicFontStyle(fontStyle);
        }
    }
}

void JSSelect::OptionFontColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    Color textColor = theme->GetFontColor();
    if (!ParseJsColor(info[0], textColor) && pipeline->GetMinPlatformVersion() < PLATFORM_VERSION_TEN) {
        return;
    }
    SelectModel::GetInstance()->SetOptionFontColor(textColor);
}

void JSSelect::OnSelected(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("info[0] is not a function.");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onSelect = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](
                        int32_t index, const std::string& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Select.onSelect");
        JSRef<JSVal> params[2];
        params[0] = JSRef<JSVal>::Make(ToJSValue(index));
        params[1] = JSRef<JSVal>::Make(ToJSValue(value));
        func->ExecuteJS(2, params);
    };
    SelectModel::GetInstance()->SetOnSelect(std::move(onSelect));
    info.ReturnSelf();
}

void JSSelect::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    SelectModel::GetInstance()->SetWidth(value);
}

void JSSelect::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    SelectModel::GetInstance()->SetHeight(value);
}

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

void JSSelect::JsSize(const JSCallbackInfo& info)
{
    std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsSize", info, checkList)) {
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);

    CalcDimension width;
    if (!ParseJsDimensionVp(sizeObj->GetProperty("width"), width)) {
        return;
    }

    CalcDimension height;
    if (!ParseJsDimensionVp(sizeObj->GetProperty("height"), height)) {
        return;
    }

    SelectModel::GetInstance()->SetSize(width, height);
}

void JSSelect::JsPadding(const JSCallbackInfo& info)
{
    if (!info[0]->IsString() && !info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGE("arg is not a string, number or object.");
        return;
    }

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
            ViewAbstractModel::GetInstance()->SetPaddings(top, bottom, left, right);
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
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
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
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
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
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
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
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
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
        LOGI("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    auto selectTheme = GetTheme<SelectTheme>();

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        LOGI("JSSelect set space value is mull");
        value = selectTheme->GetContentSpinnerPadding();
    }
    if (LessNotEqual(value.Value(), 0.0) || value.Unit() == DimensionUnit::PERCENT) {
        LOGI("JSSelect set space value is to small");
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

    if (!info[0]->IsNumber()) {
        return;
    }

    MenuAlign menuAlignObj;
    menuAlignObj.alignType = static_cast<MenuAlignType>(info[0]->ToNumber<int32_t>());

    if (info.Length() > 1) {
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
        menuAlignObj.offset = DimensionOffset(dx, dy);
    }

    SelectModel::GetInstance()->SetMenuAlign(menuAlignObj);
}
} // namespace OHOS::Ace::Framework
