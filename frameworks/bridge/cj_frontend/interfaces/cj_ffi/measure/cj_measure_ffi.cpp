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

#include "cj_measure_ffi.h"


#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
std::vector<FontStyle> FONTSTYLE_TYPES = {
    FontStyle::NORMAL, FontStyle::ITALIC
};

std::vector<TextAlign> TEXT_ALIGNS = {
    TextAlign::START,
    TextAlign::CENTER,
    TextAlign::END,
    TextAlign::LEFT,
    TextAlign::RIGHT,
    TextAlign::JUSTIFY
};
std::vector<TextOverflow> TEXTOVERFLOW = {
    TextOverflow::NONE,
    TextOverflow::CLIP,
    TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE
};
std::vector<TextCase> TEXTCASE = {
    TextCase::NORMAL,
    TextCase::LOWERCASE,
    TextCase::UPPERCASE
};
std::vector<WordBreak> WORDBREAK = {
    WordBreak::NORMAL,
    WordBreak::BREAK_ALL,
    WordBreak::BREAK_WORD
};

MeasureContext FromCJCreateMeasureContext(CJMeasureContextToC context)
{
    MeasureContext measureContext;

    measureContext.textContent = std::string(context.textContent);
    measureContext.fontWeight = std::string(context.fontWeight);
    measureContext.fontFamily = std::string(context.fontFamily);
    measureContext.maxlines = static_cast<int32_t>(context.maxLines);
    measureContext.textAlign = TEXT_ALIGNS[context.textAlign];
    measureContext.fontStyle = FONTSTYLE_TYPES[context.fontStyle];
    measureContext.textOverlayFlow = TEXTOVERFLOW[context.overflow];
    measureContext.textCase = TEXTCASE[context.textCase];
    measureContext.wordBreak = WORDBREAK[context.wordBreak];

    if (context.constraintWidth.hasValue) {
        measureContext.constraintWidth = Dimension(
            context.constraintWidth.value.value,
            DimensionUnit(context.constraintWidth.value.unitType)
        );
    }

    if (context.fontSize.hasValue) {
        measureContext.fontSize = Dimension(
            context.fontSize.value.value,
            DimensionUnit(context.fontSize.value.unitType)
        );
    }

    if (context.lineHeight.hasValue) {
        measureContext.lineHeight = Dimension(
            context.lineHeight.value.value,
            DimensionUnit(context.lineHeight.value.unitType)
        );
    }

    if (context.baselineOffset.hasValue) {
        measureContext.baselineOffset = Dimension(
            context.baselineOffset.value.value,
            DimensionUnit(context.baselineOffset.value.unitType)
        );
    }

    if (context.letterSpacing.hasValue) {
        measureContext.letterSpacing = Dimension(
            context.letterSpacing.value.value,
            DimensionUnit(context.letterSpacing.value.unitType)
        );
    }

    if (context.textIndent.hasValue) {
        measureContext.textIndent = Dimension(
            context.textIndent.value.value,
            DimensionUnit(context.textIndent.value.unitType)
        );
    }

    return measureContext;
}
} // namespace


extern "C" {
double FfiMeasureText(const CJMeasureContextToC cjcontext)
{
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("Can not get frontend.");
        return 0.0;
    }
    MeasureContext context = FromCJCreateMeasureContext(cjcontext);

    return frontend->MeasureText(context);
}

CJSize FfiMeasureTextSize(const CJMeasureContextToC cjcontext)
{
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    CJSize thisSize;
    thisSize.height = 0.0;
    thisSize.width = 0.0;
    if (!frontend) {
        LOGE("Can not get frontend.");
        return thisSize;
    }

    MeasureContext measureContext = FromCJCreateMeasureContext(cjcontext);
    auto size = frontend->MeasureTextSize(measureContext);
    thisSize.height = size.Height();
    thisSize.width = size.Width();
    return thisSize;
}
}