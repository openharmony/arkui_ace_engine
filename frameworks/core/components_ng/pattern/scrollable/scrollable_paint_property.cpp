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

#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

#include "core/components/scroll/scroll_bar_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void ScrollablePaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    PaintProperty::ToJsonValue(json);
    json->Put("scrollBar", GetBarStateString().c_str());
    json->Put("scrollBarColor", GetBarColor().ColorToString().c_str());
    json->Put("scrollBarWidth", GetBarWidth().ToString().c_str());
}

Color ScrollablePaintProperty::GetBarColor() const
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, Color::TRANSPARENT);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, Color::TRANSPARENT);
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    CHECK_NULL_RETURN(scrollBarTheme, Color::TRANSPARENT);
    auto defaultScrollBarColor = scrollBarTheme->GetForegroundColor();
    return propScrollBarProperty_ ? propScrollBarProperty_->propScrollBarColor.value_or(defaultScrollBarColor)
                                  : defaultScrollBarColor;
}

Dimension ScrollablePaintProperty::GetBarWidth() const
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, Dimension());
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, Dimension());
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    CHECK_NULL_RETURN(scrollBarTheme, Dimension());
    auto defaultScrollBarWidth = scrollBarTheme->GetNormalWidth();
    return propScrollBarProperty_ ? propScrollBarProperty_->propScrollBarWidth.value_or(defaultScrollBarWidth)
                                  : defaultScrollBarWidth;
}

std::string ScrollablePaintProperty::GetBarStateString() const
{
    auto mode = propScrollBarProperty_ ? propScrollBarProperty_->propScrollBarMode.value_or(NG::DisplayMode::AUTO)
                                       : NG::DisplayMode::AUTO;
    switch (mode) {
        case NG::DisplayMode::AUTO:
            return "BarState.Auto";
        case NG::DisplayMode::ON:
            return "BarState.On";
        case NG::DisplayMode::OFF:
            return "BarState.Off";
        default:
            break;
    }
    return "BarState.Off";
}
} // namespace OHOS::Ace::NG
