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

#include "core/components_ng/pattern/marquee/marquee_pattern.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/color.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/transition_property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DEFAULT_MARQUEE_SCROLL_DELAY = 85.0; // Delay time between each jump.
} // namespace

void MarqueePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool MarqueePattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& /* dirty */, const DirtySwapConfig& /* config */)
{
    if (forceStropAnimation_) {
        forceStropAnimation_ = false;
        auto statusChanged = statusChanged_;
        statusChanged_ = false;
        StopMarqueeAnimation(lastStartStatus_, statusChanged);
    }
    return false;
}

void MarqueePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto textChild = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto src = layoutProperty->GetSrc().value_or("");
    textLayoutProperty->UpdateContent(src);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID_NOLOG(theme);
    auto fontSize = layoutProperty->GetFontSize().value_or(theme->GetTextStyle().GetFontSize());
    textLayoutProperty->UpdateFontSize(fontSize);
    textLayoutProperty->UpdateFontWeight(layoutProperty->GetFontWeight().value_or(FontWeight::NORMAL));
    textLayoutProperty->UpdateFontFamily(
        layoutProperty->GetFontFamily().value_or(std::vector<std::string>({ "" })));
    textLayoutProperty->UpdateTextColor(layoutProperty->GetFontColor().value_or(Color()));
    textChild->MarkModifyDone();
    textChild->MarkDirtyNode();
    if (CheckMeasureFlag(layoutProperty->GetPropertyChangeFlag())) {
        forceStropAnimation_ = true;
        host->MarkDirtyNode();
    }
    auto startPlay = layoutProperty->GetPlayerStatus().value_or(false);
    if (startPlay != lastStartStatus_) {
        lastStartStatus_ = startPlay;
        statusChanged_ = true;
    }
    RegistVisibleAreaChangeCallback();
}

void MarqueePattern::StartMarqueeAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    repeatCount_ = layoutProperty->GetLoop().value_or(DEFAULT_MARQUEE_LOOP);
    if (repeatCount_ == 0) {
        lastStartStatus_ = false;
        return;
    }
    auto geoNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geoNode);
    auto marqueeSize = geoNode->GetFrameSize();
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textGeoNode = textNode->GetGeometryNode();
    CHECK_NULL_VOID(textGeoNode);
    auto textWidth = textGeoNode->GetFrameSize().Width();
    if (GreatOrEqual(marqueeSize.Width(), textWidth)) {
        lastStartStatus_ = false;
        return;
    }
    FireStartEvent();
    auto step = layoutProperty->GetScrollAmount().value_or(DEFAULT_MARQUEE_SCROLL_AMOUNT);
    auto direction = layoutProperty->GetDirection().value_or(MarqueeDirection::LEFT);
    auto end = -1 * textWidth;
    if (direction == MarqueeDirection::RIGHT) {
        const auto& padding = layoutProperty->CreatePaddingAndBorder();
        MinusPaddingToSize(padding, marqueeSize);
        end = marqueeSize.Width() >= textWidth ? marqueeSize.Width() : textWidth;
    }
    auto duration = static_cast<int32_t>(std::abs(end) * DEFAULT_MARQUEE_SCROLL_DELAY);
    if (GreatNotEqual(step, 0.0)) {
        duration = static_cast<int32_t>(duration / step);
    }
    AnimationOption option;
    option.SetCurve(Curves::LINEAR);
    option.SetDuration(duration);
    option.SetIteration(repeatCount_);
    SetTextOffset(0.0f);
    animationId_++;
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this), end]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SetTextOffset(end);
        },
        [weak = AceType::WeakClaim(this), animationId = animationId_]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (animationId == pattern->animationId_) {
                pattern->FireFinishEvent();
                pattern->SetTextOffset(0.0f);
                pattern->lastStartStatus_ = false;
            }
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireBounceEvent();
        });
}

void MarqueePattern::StopMarqueeAnimation(bool stopAndStart, bool statusChanged)
{
    if (!statusChanged & !lastStartStatus_) {
        return;
    }
    AnimationOption option;
    option.SetCurve(Curves::LINEAR);
    option.SetDuration(0);
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SetTextOffset(0.0f);
        },
        [weak = AceType::WeakClaim(this), restart = stopAndStart]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireFinishEvent();
            if (restart) {
                pattern->StartMarqueeAnimation();
            } else {
                pattern->lastStartStatus_ = false;
            }
        });
}

void MarqueePattern::FireStartEvent() const
{
    auto marqueeEventHub = GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(marqueeEventHub);
    marqueeEventHub->FireStartEvent();
}

void MarqueePattern::FireBounceEvent() const
{
    auto marqueeEventHub = GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(marqueeEventHub);
    marqueeEventHub->FireBounceEvent();
}

void MarqueePattern::FireFinishEvent() const
{
    auto marqueeEventHub = GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(marqueeEventHub);
    marqueeEventHub->FireFinishEvent();
}

void MarqueePattern::SetTextOffset(float offsetX)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto renderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformTranslate({ offsetX, 0.0f, 0.0f });
}

void MarqueePattern::RegistVisibleAreaChangeCallback()
{
    if (isRegistedAreaCallback_) {
        return;
    }
    isRegistedAreaCallback_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnVisibleAreaChange(visible);
    };
    pipeline->AddVisibleAreaChangeNode(host, 0.0f, callback, false);
}

void MarqueePattern::OnVisibleAreaChange(bool visible)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (visible) {
        CHECK_NULL_VOID(textNode_);
        auto childNode = DynamicCast<FrameNode>(host->GetFirstChild());
        if (!childNode) {
            host->AddChild(textNode_);
            host->RebuildRenderContextTree();
        }
    } else {
        auto layoutProperty = host->GetLayoutProperty<MarqueeLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto repeatCount = layoutProperty->GetLoop().value_or(DEFAULT_MARQUEE_LOOP);
        if (repeatCount >= 0) {
            return;
        }
        auto childNode = DynamicCast<FrameNode>(host->GetFirstChild());
        CHECK_NULL_VOID(childNode);
        bool isTextNode = AceType::InstanceOf<TextPattern>(childNode->GetPattern());
        if (!isTextNode) {
            return;
        }
        textNode_ = childNode;
        host->RemoveChild(childNode);
        host->RebuildRenderContextTree();
    }
}
} // namespace OHOS::Ace::NG