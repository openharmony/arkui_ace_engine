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

#include "core/components_ng/pattern/button/button_pattern.h"

#include "base/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
void ButtonPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    SetDefaultAttributes(host, pipeline);
    host->GetRenderContext()->SetClipToFrame(true);
    clickedColor_ = pipeline->GetTheme<ButtonTheme>()->GetClickedColor();
}

void ButtonPattern::SetDefaultAttributes(const RefPtr<FrameNode>& buttonNode, const RefPtr<PipelineBase>& pipeline)
{
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);

    // Init button default style
    buttonLayoutProperty->UpdateType(ButtonType::CAPSULE);
    renderContext->UpdateBackgroundColor(buttonTheme->GetBgColor());
    buttonLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(buttonTheme->GetHeight())));
}

void ButtonPattern::InitButtonLabel()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto label = layoutProperty->GetLabelValue("");
    if (label.empty()) {
        LOGI("No label or label is empty, no need to initialize label.");
        return;
    }
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    if (layoutProperty->GetFontSize().has_value()) {
        textLayoutProperty->UpdateFontSize(layoutProperty->GetFontSize().value());
    }
    if (layoutProperty->GetFontWeight().has_value()) {
        textLayoutProperty->UpdateFontWeight(layoutProperty->GetFontWeight().value());
    }
    if (layoutProperty->GetFontColor().has_value()) {
        textLayoutProperty->UpdateTextColor(layoutProperty->GetFontColor().value());
    }
    if (layoutProperty->GetFontStyle().has_value()) {
        textLayoutProperty->UpdateItalicFontStyle(layoutProperty->GetFontStyle().value());
    }
    if (layoutProperty->GetFontFamily().has_value()) {
        textLayoutProperty->UpdateFontFamily(layoutProperty->GetFontFamily().value());
    }
    textNode->MarkModifyDone();
}

void ButtonPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    InitButtonLabel();

    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);

    if (touchListener_) {
        return;
    }
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto buttonPattern = weak.Upgrade();
        CHECK_NULL_VOID(buttonPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            buttonPattern->OnTouchDown();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            buttonPattern->OnTouchUp();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void ButtonPattern::OnTouchDown()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonEventHub = GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);

    if (buttonEventHub->GetStateEffect()) {
        const auto& renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        backgroundColor_ = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT);
        if (isSetClickedColor_) {
            // for user self-defined
            renderContext->UpdateBackgroundColor(clickedColor_);
            return;
        }
        // for system default
        renderContext->BlendBgColor(clickedColor_);
    }
}

void ButtonPattern::OnTouchUp()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonEventHub = GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    if (buttonEventHub->GetStateEffect()) {
        const auto& renderContext = host->GetRenderContext();
        if (isSetClickedColor_) {
            renderContext->UpdateBackgroundColor(backgroundColor_);
            return;
        }
        renderContext->ResetBlendBgColor();
    }
}

} // namespace OHOS::Ace::NG
