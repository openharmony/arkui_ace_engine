/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_span_ffi.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/text/span_model.h"
#include "cj_lambda.h"

using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace;

namespace {
const std::vector<FontStyle> FONT_STYLES = {
    FontStyle::NORMAL,
    FontStyle::ITALIC
};
const std::vector<TextCase> TEXT_CASES = {
    TextCase::NORMAL,
    TextCase::LOWERCASE,
    TextCase::UPPERCASE
};
const std::vector<TextDecoration> TEXT_DECRATIONS = {
    TextDecoration::NONE,
    TextDecoration::UNDERLINE,
    TextDecoration::OVERLINE,
    TextDecoration::LINE_THROUGH
};
} // namespace

extern "C" {
void FfiOHOSAceFrameworkSpanCreate(const char* content)
{
    SpanModel::GetInstance()->Create(content);
}

void FfiOHOSAceFrameworkSpanSetDecoration(int32_t type, uint32_t color)
{
    if (!Utils::CheckParamsValid(type, TEXT_DECRATIONS.size())) {
        LOGE("invalid value for scrollDirection");
        return;
    }
    SpanModel::GetInstance()->SetTextDecoration(TEXT_DECRATIONS[type]);
    SpanModel::GetInstance()->SetTextDecorationColor(Color(color));
}

void FfiOHOSAceFrameworkSpanSetTextCase(int32_t textCase)
{
    if (!Utils::CheckParamsValid(textCase, TEXT_CASES.size())) {
        LOGE("invalid value for scrollDirection");
        return;
    }
    SpanModel::GetInstance()->SetTextCase(TEXT_CASES[textCase]);
}

void FfiOHOSAceFrameworkSpanSetFontSize(double fontSize, int32_t unit)
{
    Dimension value(fontSize, static_cast<DimensionUnit>(unit));
    SpanModel::GetInstance()->SetFontSize(value);
}

void FfiOHOSAceFrameworkSpanSetOnClick(void (*callback)(CJClickInfo clickInfo))
{
    auto lambda = [ffiOnClick = CJLambda::Create(callback)](const GestureEvent& event) -> void {
        CJClickInfo cjClickInfo {};
        CJEventTarget cjEventTarget {};
        CJArea cjArea {};
        CJPosition cjPosition {};
        CJPosition cjGlobalPosition {};
        AssambleCJClickInfo(event, cjClickInfo, cjEventTarget, cjArea, cjPosition, cjGlobalPosition);
        ffiOnClick(cjClickInfo);
    };

    auto onClick = [lambda](const BaseEventInfo* info) {
        const auto* clickInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
        auto newInfo = *clickInfo;
        lambda(newInfo);
    };
    SpanModel::GetInstance()->SetOnClick(onClick);
    return;
}

void FfiOHOSAceFrameworkSpanSetFontFamily(const char* fontFamily)
{
    std::vector<std::string> fontFamilies;
    fontFamilies = ConvertStrToFontFamilies(fontFamily);
    SpanModel::GetInstance()->SetFontFamily(fontFamilies);
}

void FfiOHOSAceFrameworkSpanSetFontWeight(const char* fontWeight)
{
    SpanModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(fontWeight));
}

void FfiOHOSAceFrameworkSpanSetFontColor(uint32_t textColor)
{
    SpanModel::GetInstance()->SetTextColor(Color(textColor));
}

void FfiOHOSAceFrameworkSpanSetFontStyle(int32_t fontStyle)
{
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLES.size())) {
        LOGE("invalid value for scrollDirection");
        return;
    }
    SpanModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[fontStyle]);
}

void FfiOHOSAceFrameworkSpanSetLetterSpacing(double space, int32_t unit)
{
    Dimension value(space, static_cast<DimensionUnit>(unit));
    SpanModel::GetInstance()->SetLetterSpacing(value);
}
}
