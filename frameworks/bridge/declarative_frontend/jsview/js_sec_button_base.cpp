/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_sec_button_base.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/common/container.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"

using OHOS::Ace::NG::SecurityComponentModelNG;
using OHOS::Ace::NG::SecurityComponentTheme;

namespace OHOS::Ace::Framework {
namespace {
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
}

void JSSecButtonBase::SetIconSize(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);

    if (info[0]->IsObject()) {
        JSRef<JSObject> iconSizeObj = JSRef<JSObject>::Cast(info[0]);

        CalcDimension widthDimen;
        std::optional<NG::CalcLength> width;
        if (ParseJsDimensionVp(iconSizeObj->GetProperty("width"), widthDimen)) {
            width.emplace(widthDimen);
        }
        CalcDimension heightDimen;
        std::optional<NG::CalcLength> height;
        if (ParseJsDimensionVp(iconSizeObj->GetProperty("height"), heightDimen)) {
            height.emplace(heightDimen);
        }
        if ((!width.has_value()) && (!height.has_value())) {
            return;
        }
        SecurityComponentModelNG::SetIconSize(NG::CalcSize(width, height));
        return;
    }

    CalcDimension value;
    if (!ParseJsDimensionVpNG(info[0], value, false) || value.IsNegative()) {
        SecurityComponentModelNG::SetIconSize(theme->GetIconSize());
    } else {
        SecurityComponentModelNG::SetIconSize(value);
    }
}

void JSSecButtonBase::SetIconColor(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);

    Color color;
    if (!ParseJsColor(info[0], color)) {
        color = theme->GetIconColor();
    }
    SecurityComponentModelNG::SetIconColor(color);
}

void JSSecButtonBase::SetFontSize(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);

    CalcDimension value;
    if (!ParseJsDimensionFpNG(info[0], value, false) || value.IsNegative()) {
        SecurityComponentModelNG::SetFontSize(theme->GetFontSize());
    } else {
        SecurityComponentModelNG::SetFontSize(value);
    }
}

void JSSecButtonBase::SetFontStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        SecurityComponentModelNG::SetFontStyle(Ace::FontStyle::NORMAL);
        return;
    }
    uint32_t value = info[0]->ToNumber<uint32_t>();
    if (value < static_cast<uint32_t>(Ace::FontStyle::NORMAL) ||
        value > static_cast<uint32_t>(Ace::FontStyle::ITALIC)) {
        SecurityComponentModelNG::SetFontStyle(Ace::FontStyle::NORMAL);
        return;
    }
    SecurityComponentModelNG::SetFontStyle(static_cast<Ace::FontStyle>(value));
}

void JSSecButtonBase::SetFontWeight(const JSCallbackInfo& info)
{
    if (!(info[0]->IsString() || info[0]->IsNumber())) {
        return;
    }
    std::string value = info[0]->ToString();
    SecurityComponentModelNG::SetFontWeight(ConvertStrToFontWeight(value));
}

void JSSecButtonBase::SetFontFamily(const JSCallbackInfo& info)
{
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        fontFamilies.emplace_back("HarmonyOS Sans");
    }
    SecurityComponentModelNG::SetFontFamily(fontFamilies);
}

void JSSecButtonBase::SetFontColor(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);

    Color color;
    if (!ParseJsColor(info[0], color)) {
        color = theme->GetFontColor();
    }
    SecurityComponentModelNG::SetFontColor(color);
}

void JSSecButtonBase::SetLayoutDirection(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        SecurityComponentModelNG::SetTextIconLayoutDirection(
            SecurityComponentLayoutDirection::HORIZONTAL);
        return;
    }
    int32_t value = info[0]->ToNumber<int32_t>();
    if ((value < static_cast<int32_t>(SecurityComponentLayoutDirection::HORIZONTAL)) ||
        (value > static_cast<int32_t>(SecurityComponentLayoutDirection::VERTICAL))) {
        SecurityComponentModelNG::SetTextIconLayoutDirection(
            SecurityComponentLayoutDirection::HORIZONTAL);
        return;
    }
    SecurityComponentModelNG::SetTextIconLayoutDirection(
        static_cast<SecurityComponentLayoutDirection>(value));
}

void JSSecButtonBase::SetBackgroundColor(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);

    Color color;
    if (!ParseJsColor(info[0], color)) {
        color = theme->GetBackgroundColor();
    }
    SecurityComponentModelNG::SetBackgroundColor(color);
}

void JSSecButtonBase::SetBackgroundBorderStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        SecurityComponentModelNG::SetBackgroundBorderStyle(BorderStyle::NONE);
        return;
    }
    int32_t value = info[0]->ToNumber<int32_t>();
    if ((value < static_cast<int32_t>(BorderStyle::SOLID)) ||
        (value > static_cast<int32_t>(BorderStyle::NONE))) {
        SecurityComponentModelNG::SetBackgroundBorderStyle(BorderStyle::NONE);
        return;
    }
    SecurityComponentModelNG::SetBackgroundBorderStyle(static_cast<BorderStyle>(value));
}

void JSSecButtonBase::SetBackgroundBorderWidth(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        SecurityComponentModelNG::SetBackgroundBorderWidth(theme->GetBorderWidth());
    } else {
        SecurityComponentModelNG::SetBackgroundBorderWidth(value);
    }
}

void JSSecButtonBase::SetBackgroundBorderColor(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);

    Color borderColor;
    if (!ParseJsColor(info[0], borderColor)) {
        borderColor = theme->GetBorderColor();
    }
    SecurityComponentModelNG::SetBackgroundBorderColor(borderColor);
}

void JSSecButtonBase::SetBackgroundBorderRadius(const JSCallbackInfo& info)
{
    if (info[0]->IsObject()) {
        std::optional<CalcDimension> topLeft;
        std::optional<CalcDimension> topRight;
        std::optional<CalcDimension> bottomLeft;
        std::optional<CalcDimension> bottomRight;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);

        CalcDimension topLeftDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("topLeft"), topLeftDimen)) {
            topLeft = topLeftDimen;
        }
        CalcDimension topRightDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("topRight"), topRightDimen)) {
            topRight = topRightDimen;
        }
        CalcDimension bottomLeftDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("bottomLeft"), bottomLeftDimen)) {
            bottomLeft = bottomLeftDimen;
        }
        CalcDimension bottomRightDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("bottomRight"), bottomRightDimen)) {
            bottomRight = bottomRightDimen;
        }
        
        if (topLeft.has_value() || topRight.has_value() || bottomLeft.has_value() || bottomRight.has_value()) {
            SecurityComponentModelNG::SetBackgroundBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
            return;
        }
    }
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        SecurityComponentModelNG::SetBackgroundBorderRadius(theme->GetBorderRadius());
    } else {
        SecurityComponentModelNG::SetBackgroundBorderRadius(value);
    }
}

void JSSecButtonBase::SetBackgroundPadding(const JSCallbackInfo& info)
{
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
            SecurityComponentModelNG::SetBackgroundPadding(left, right, top, bottom);
            return;
        }
    }

    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        SecurityComponentModelNG::SetBackgroundPadding(std::nullopt);
    } else {
        SecurityComponentModelNG::SetBackgroundPadding(length);
    }
}

void JSSecButtonBase::SetTextIconSpace(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID(theme);

    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length) || LessNotEqual(length.ConvertToPx(), 0.0)) {
        SecurityComponentModelNG::SetTextIconSpace(theme->GetTextIconSpace());
    } else {
        SecurityComponentModelNG::SetTextIconSpace(length);
    }
}

void JSSecButtonBase::SetAlign(const JSCallbackInfo& info)
{
    Alignment alignment;
    if (!info[0]->IsNumber()) {
        alignment = Alignment::CENTER;
    } else {
        auto value = info[0]->ToNumber<int32_t>();
        alignment = ParseAlignment(value);
    }
    SecurityComponentModelNG::SetAlign(alignment);
}

void JSSecButtonBase::SetMaxFontScale(const JSCallbackInfo& info)
{
    double maxFontScale;
    if (info.Length() < 1 || !ParseJsDouble(info[0], maxFontScale)) {
        return;
    }
    if (LessOrEqual(maxFontScale, 1.0f)) {
        SecurityComponentModelNG::SetMaxFontScale(1.0f);
        return;
    }
    SecurityComponentModelNG::SetMaxFontScale(static_cast<float>(maxFontScale));
}

void JSSecButtonBase::SetMinFontScale(const JSCallbackInfo& info)
{
    double minFontScale;
    if (info.Length() < 1 || !ParseJsDouble(info[0], minFontScale)) {
        return;
    }
    if (LessOrEqual(minFontScale, 0.0f)) {
        SecurityComponentModelNG::SetMinFontScale(0.0f);
        return;
    }
    if (GreatOrEqual(minFontScale, 1.0f)) {
        SecurityComponentModelNG::SetMinFontScale(1.0f);
        return;
    }
    SecurityComponentModelNG::SetMinFontScale(static_cast<float>(minFontScale));
}

void JSSecButtonBase::SetMaxLines(const JSCallbackInfo& info)
{
    JSRef<JSVal> args = info[0];
    auto value = Infinity<int32_t>();
    if (args->ToString() != "Infinity") {
        ParseJsInt32(args, value);
    }
    if (value <= 0) {
        return;
    }
    SecurityComponentModelNG::SetMaxLines(value);
}

void JSSecButtonBase::SetMaxFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension maxFontSize;
    JSRef<JSVal> args = info[0];
    if (!ParseJsDimensionFpNG(args, maxFontSize, false)) {
        return;
    }
    if (maxFontSize.IsNegative()) {
        return;
    }
    SecurityComponentModelNG::SetAdaptMaxFontSize(maxFontSize);
}

void JSSecButtonBase::SetMinFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension minFontSize;
    JSRef<JSVal> args = info[0];
    if (!ParseJsDimensionFpNG(args, minFontSize, false)) {
        return;
    }
    if (minFontSize.IsNegative()) {
        return;
    }
    SecurityComponentModelNG::SetAdaptMinFontSize(minFontSize);
}

void JSSecButtonBase::SetHeightAdaptivePolicy(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICY.size())) {
        value = 0;
    }
    SecurityComponentModelNG::SetHeightAdaptivePolicy(HEIGHT_ADAPTIVE_POLICY[value]);
}
}
