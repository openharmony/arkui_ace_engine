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

#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void ScrollablePaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    PaintProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("scrollBar", GetBarStateString().c_str(), filter);
    json->PutExtAttr("scrollBarColor", GetBarColor().ColorToString().c_str(), filter);
    json->PutExtAttr("scrollBarWidth", GetBarWidth().ToString().c_str(), filter);
    json->PutExtAttr("fadingEdge",
        propFadingEdgeProperty_ ? propFadingEdgeProperty_->propFadingEdge.value_or(false) : false, filter);
    auto fadingEdgeOption = JsonUtil::Create(true);
    fadingEdgeOption->Put("fadingEdgeLength",
        propFadingEdgeProperty_
            ? propFadingEdgeProperty_->propFadingEdgeLength
                  .value_or(Dimension(32.0, DimensionUnit::VP)) // 32.0: default fading edge length
                  .ToString()
                  .c_str()
            : Dimension(32.0, DimensionUnit::VP).ToString().c_str()); // 32.0: default fading edge length
    json->PutExtAttr("fadingEdgeOption", fadingEdgeOption, filter);
}

Color ScrollablePaintProperty::GetBarColor() const
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    auto mode = propScrollBarProperty_ ? propScrollBarProperty_->propScrollBarMode.value_or(DisplayMode::AUTO)
                                       : DisplayMode::AUTO;
    switch (mode) {
        case DisplayMode::AUTO:
            return "BarState.Auto";
        case DisplayMode::ON:
            return "BarState.On";
        case DisplayMode::OFF:
            return "BarState.Off";
        default:
            break;
    }
    return "BarState.Off";
}
} // namespace OHOS::Ace::NG
