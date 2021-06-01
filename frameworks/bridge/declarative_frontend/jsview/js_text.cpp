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

#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"

#include <map>
#include <sstream>
#include <string>

#include "base/geometry/dimension.h"
#include "base/log/ace_trace.h"

namespace OHOS::Ace::Framework {

const std::map<int, TextOverflow> textOverflowEnumMapping = {
    { 0, TextOverflow::CLIP },
    { 1, TextOverflow::ELLIPSIS },
    { 2, TextOverflow::NONE },
};

const std::map<int, TextAlign> textAlignEnumMapping = {
    { 0, TextAlign::LEFT },
    { 1, TextAlign::RIGHT },
    { 2, TextAlign::CENTER },
    { 3, TextAlign::JUSTIFY },
    { 4, TextAlign::START },
    { 5, TextAlign::END },
};

const std::map<int, FontStyle> fontStyleEnumMapping = {
    { 0, FontStyle::NORMAL },
    { 1, FontStyle::ITALIC },
};

JSText::JSText(const std::string& text)
{
    textComponent_ = AceType::MakeRefPtr<OHOS::Ace::TextComponent>(text);
}

RefPtr<OHOS::Ace::Component> JSText::CreateSpecializedComponent()
{
    LOGD("Create component: Text");
    return textComponent_;
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSText::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

#ifdef USE_QUICKJS_ENGINE
void JSText::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSText => MarkGC: Mark value for GC start");
    JSInteractableView::MarkGC(rt, markFunc);
    LOGD("JSText => MarkGC: Mark value for GC end");
}

void JSText::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSText => release start");
    JSInteractableView::ReleaseRT(rt);
    LOGD("JSText => release text: %s", textComponent_->GetData().c_str());
    LOGD("JSText => release end");
}
#endif

void JSText::SetFontSize(const std::string& value)
{
    Dimension dimension = TextAttr2Dimension(value, true);
    if (GreatNotEqual(dimension.Value(), 0.0)) {
        auto textStyle = GetTextStyle();
        textStyle.SetFontSize(dimension);
        SetTextStyle(std::move(textStyle));
    } else {
        LOGE("value %s is not positive", value.c_str());
    }
}

void JSText::SetFontWeight(const std::string& value)
{
    auto textStyle = GetTextStyle();
    textStyle.SetFontWeight(ConvertStrToFontWeight(value));
    SetTextStyle(std::move(textStyle));
}

void JSText::SetTextColor(const std::string& value)
{
    auto textStyle = GetTextStyle();
    textStyle.SetTextColor(Color::FromString(value));
    SetTextStyle(std::move(textStyle));
}

void JSText::SetTextOverflow(int value)
{
    auto iter = textOverflowEnumMapping.find(value);
    if (iter != textOverflowEnumMapping.end()) {
        auto textStyle = GetTextStyle();
        textStyle.SetTextOverflow(iter->second);
        SetTextStyle(std::move(textStyle));
    } else {
        LOGE("Text: textOverflow(%d) illegal value", value);
    }
}

void JSText::SetMaxLines(int value)
{
    if (value > 0) {
        auto textStyle = GetTextStyle();
        textStyle.SetMaxLines(value);
        SetTextStyle(std::move(textStyle));
    } else {
        LOGE("Text: maxLines(%d) expected positive number", value);
    }
}

void JSText::SetFontStyle(int value)
{
    auto iter = fontStyleEnumMapping.find(value);
    if (iter != fontStyleEnumMapping.end()) {
        auto textStyle = GetTextStyle();
        textStyle.SetFontStyle(FontStyle(value));
        SetTextStyle(std::move(textStyle));
    } else {
        LOGE("Text fontStyle(%d) illega value", value);
    }
}

void JSText::SetTextAlign(int value)
{
    auto iter = textAlignEnumMapping.find(value);
    if (iter != textAlignEnumMapping.end()) {
        auto textStyle = GetTextStyle();
        textStyle.SetTextAlign(iter->second);
        SetTextStyle(std::move(textStyle));
    } else {
        LOGE("Text: TextAlign(%d) expected positive number", value);
    }
}

void JSText::SetLineHeight(const std::string& value)
{
    Dimension dimension = TextAttr2Dimension(value, true);
    if (GreatNotEqual(dimension.Value(), 0.0)) {
        auto textStyle = GetTextStyle();
        textStyle.SetLineHeight(dimension);
        SetTextStyle(std::move(textStyle));
    } else {
        LOGE("value %s is not positive", value.c_str());
    }
}

void JSText::SetFontFamily(const std::string& fontFamiliy)
{
    std::vector<std::string> fontFamilies = ParseFontFamilies(fontFamiliy);
    auto textStyle = GetTextStyle();
    textStyle.SetFontFamilies(fontFamilies);
    SetTextStyle(std::move(textStyle));
}

void JSText::SetMinFontSize(const std::string& value)
{
    Dimension dimension = TextAttr2Dimension(value, true);
    if (GreatNotEqual(dimension.Value(), 0.0)) {
        auto textStyle = GetTextStyle();
        textStyle.SetAdaptMinFontSize(dimension);
        SetTextStyle(std::move(textStyle));
    } else {
        LOGE("value %s is not positive", value.c_str());
    }
}

void JSText::SetMaxFontSize(const std::string& value)
{
    Dimension dimension = TextAttr2Dimension(value, true);
    if (GreatNotEqual(dimension.Value(), 0.0)) {
        auto textStyle = GetTextStyle();
        textStyle.SetAdaptMaxFontSize(dimension);
        SetTextStyle(std::move(textStyle));
    } else {
        LOGE("value %s is not positive", value.c_str());
    }
}

std::vector<std::string> JSText::ParseFontFamilies(const std::string& value) const
{
    std::vector<std::string> fontFamilies;
    std::stringstream stream(value);
    std::string fontFamily;
    while (getline(stream, fontFamily, ',')) {
        fontFamilies.push_back(fontFamily);
    }
    return fontFamilies;
}

Dimension JSText::TextAttr2Dimension(const std::string& value, bool usefp)
{
    errno = 0;
    char* pEnd = nullptr;
    double result = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        return Dimension(0.0, DimensionUnit::PX);
    } else {
        if ((pEnd) && (std::strcmp(pEnd, "%") == 0)) {
            // Parse percent, transfer from [0, 100] to [0`, 1]
            return Dimension(result / 100.0, DimensionUnit::PERCENT);
        } else if ((pEnd) && (std::strcmp(pEnd, "px") == 0)) {
            return Dimension(result, DimensionUnit::PX);
        } else if ((pEnd) && (std::strcmp(pEnd, "vp") == 0)) {
            return Dimension(result, DimensionUnit::VP);
        } else if ((pEnd) && (std::strcmp(pEnd, "fp") == 0)) {
            return Dimension(result, DimensionUnit::FP);
        }
        return Dimension(result, usefp ? DimensionUnit::FP : DimensionUnit::PX);
    }
}

#ifdef USE_QUICKJS_ENGINE

void JSText::QjsDestructor(JSRuntime* rt, JSText* view)
{
    LOGD("JSText(QjsDestructor) start");
    if (!view)
        return;

    view->ReleaseRT(rt);
    delete view;
    LOGD("JSText(QjsDestructor) end");
}

void JSText::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSText(QjsGcMark) start");

    JSText* view = Unwrap<JSText>(val);
    if (!view)
        return;

    view->MarkGC(rt, markFunc);
    LOGD("JSText(QjsGcMark) end");
}
#endif

void JSText::JSBind(BindingTarget globalObj)
{
    JSClass<JSText>::Declare("Text");
    JSClass<JSText>::Inherit<JSViewAbstract>();

    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSText>::Method("color", &JSText::SetTextColor, opt);
    JSClass<JSText>::Method("fontSize", &JSText::SetFontSize, opt);
    JSClass<JSText>::Method("fontWeight", &JSText::SetFontWeight, opt);
    JSClass<JSText>::Method("maxLines", &JSText::SetMaxLines, opt);
    JSClass<JSText>::Method("textOverflow", &JSText::SetTextOverflow, opt);
    JSClass<JSText>::Method("fontStyle", &JSText::SetFontStyle, opt);
    JSClass<JSText>::Method("textAlign", &JSText::SetTextAlign, opt);
    JSClass<JSText>::Method("lineHeight", &JSText::SetLineHeight, opt);
    JSClass<JSText>::Method("fontFamily", &JSText::SetFontFamily, opt);
    JSClass<JSText>::Method("minFontSize", &JSText::SetMinFontSize, opt);
    JSClass<JSText>::Method("maxFontSize", &JSText::SetMaxFontSize, opt);
    JSClass<JSText>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSText>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSText>::Bind<std::string>(globalObj);
}

TextStyle JSText::GetTextStyle() const
{
    return textComponent_->GetTextStyle();
}

void JSText::SetTextStyle(TextStyle style)
{
    textComponent_->SetTextStyle(std::move(style));
}

} // namespace OHOS::Ace::Framework
