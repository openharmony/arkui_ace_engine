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

#include "core/components_ng/pattern/option/option_pattern.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void OptionPattern::OnModifyDone()
{
    RegisterOnClick();
    RegisterOnTouch();
    RegisterOnHover();
    textTheme_ = PipelineContext::GetCurrentContext()->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme_);
}

void OptionPattern::RegisterOnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<OptionEventHub>();

    auto event = [JsAction = hub->GetJsCallback(), onSelect = hub->GetOnSelect(), index = index_](
                     GestureEvent& /*info*/) {
        if (JsAction) {
            LOGI("Option's callback executing");
            JsAction();
        }
        if (onSelect) {
            LOGI("selecting option %d", index);
            onSelect(index);
        }
    };
    auto clickEvent = MakeRefPtr<ClickEvent>(std::move(event));

    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->AddClickEvent(clickEvent);
}

void OptionPattern::RegisterOnTouch()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnPress(info);
    };
    auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureHub->AddTouchEvent(touchEvent);
}

void OptionPattern::RegisterOnHover()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inputHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHover(isHover);
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent);
}

void OptionPattern::OnPress(const TouchEventInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto props = GetPaintProperty<OptionPaintProperty>();
    CHECK_NULL_VOID(props);
    auto touchType = info.GetTouches().front().GetTouchType();
    // enter press status
    if (touchType == TouchType::DOWN) {
        LOGD("triggers option press");
        // change background color, update press status
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        auto clickedColor = theme->GetClickedColor();
        renderContext->UpdateBackgroundColor(clickedColor);
        props->UpdatePress(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        // disable next option node's divider
        UpdateNextNodeDivider(false);
    }
    // leave press status
    else if (touchType == TouchType::UP) {
        renderContext->UpdateBackgroundColor(GetBgColor());
        props->UpdatePress(false);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        UpdateNextNodeDivider(true);
    }
}

void OptionPattern::OnHover(bool isHover)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto props = GetPaintProperty<OptionPaintProperty>();
    CHECK_NULL_VOID(props);
    if (isHover) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SelectTheme>();
        auto hoverColor = theme->GetHoverColor();
        renderContext->UpdateBackgroundColor(hoverColor);
        props->UpdateHover(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        UpdateNextNodeDivider(false);
    } else {
        renderContext->UpdateBackgroundColor(GetBgColor());
        props->UpdateHover(false);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        UpdateNextNodeDivider(true);
    }
}

void OptionPattern::UpdateNextNodeDivider(bool needDivider)
{
    auto host = GetHost();
    // find next option node from parent menuNode
    auto nextNode = host->GetParent()->GetChildAtIndex(index_ + 1);
    if (nextNode) {
        if (!InstanceOf<FrameNode>(nextNode)) {
            LOGW("next optionNode is not a frameNode! type = %{public}s", nextNode->GetTag().c_str());
            return;
        }
        auto props = DynamicCast<FrameNode>(nextNode)->GetPaintProperty<OptionPaintProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateNeedDivider(needDivider);
        nextNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void OptionPattern::SetBgColor(const Color& color)
{
    auto renderContext = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(color);
    bgColor_ = color;
}

void OptionPattern::SetFontSize(const Dimension& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateFontSize(value);
}

void OptionPattern::SetItalicFontStyle(const Ace::FontStyle& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateItalicFontStyle(value);
}

void OptionPattern::SetFontWeight(const FontWeight& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateFontWeight(value);
}

void OptionPattern::SetFontFamily(const std::vector<std::string>& value)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateFontFamily(value);
}

void OptionPattern::SetFontColor(const Color& color)
{
    CHECK_NULL_VOID(text_);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(props);
    text_->MarkModifyDone();
    props->UpdateTextColor(color);
}

std::string OptionPattern::InspectorGetFont()
{
    CHECK_NULL_RETURN(text_, "");
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, "");
    return props->InspectorGetTextFont();
}

Color OptionPattern::GetBgColor()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, Color());
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, Color());
    auto bgColor = theme->GetBackgroundColor();
    return bgColor_.value_or(bgColor);
}

Dimension OptionPattern::GetFontSize()
{
    CHECK_NULL_RETURN(text_, Dimension());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, Dimension());
    auto defaultSize = textTheme_->GetTextStyle().GetFontSize();
    return props->GetFontSizeValue(defaultSize);
}

Ace::FontStyle OptionPattern::GetItalicFontStyle()
{
    CHECK_NULL_RETURN(text_, Ace::FontStyle());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, Ace::FontStyle());
    auto defaultStyle = textTheme_->GetTextStyle().GetFontStyle();
    return props->GetItalicFontStyleValue(defaultStyle);
}

FontWeight OptionPattern::GetFontWeight()
{
    CHECK_NULL_RETURN(text_, FontWeight());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, FontWeight());
    auto defaultWeight = textTheme_->GetTextStyle().GetFontWeight();
    return props->GetFontWeightValue(defaultWeight);
}

std::vector<std::string> OptionPattern::GetFontFamily()
{
    CHECK_NULL_RETURN(text_, std::vector<std::string>());
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, std::vector<std::string>());
    auto defaultFamily = textTheme_->GetTextStyle().GetFontFamilies();
    return props->GetFontFamilyValue(defaultFamily);
}

Color OptionPattern::GetFontColor()
{
    CHECK_NULL_RETURN(text_, Color::TRANSPARENT);
    auto props = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(props, Color::TRANSPARENT);
    auto defaultColor = textTheme_->GetTextStyle().GetTextColor();
    return props->GetTextColorValue(defaultColor);
}

const std::string& OptionPattern::GetText()
{
    CHECK_NULL_RETURN(text_, std::string());
    auto textProps = text_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textProps, std::string());
    return textProps->GetContentValue();
}

} // namespace OHOS::Ace::NG