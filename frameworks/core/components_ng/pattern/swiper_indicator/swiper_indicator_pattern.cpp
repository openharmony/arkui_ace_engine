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

#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_pattern.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
constexpr Dimension INDICATOR_PADDING_DEFAULT = 13.0_vp;
} // namespace

void SwiperIndicatorPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void SwiperIndicatorPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();

    swiperEventHub->SetIndicatorOnChange([weak = AceType::WeakClaim(RawPtr(host))]() {
        auto indicator = weak.Upgrade();
        CHECK_NULL_VOID(indicator);
        indicator->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    });

    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitClickEvent(gestureHub);
}

bool SwiperIndicatorPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!config.frameSizeChange) {
        return false;
    }
    return true;
}

void SwiperIndicatorPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (clickEvent_) {
        return;
    }
    auto clickTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleClick(info);
        }
    };
    clickEvent_ = MakeRefPtr<ClickEvent>(std::move(clickTask));
    gestureHub->AddClickEvent(clickEvent_);
}

void SwiperIndicatorPattern::HandleClick(const GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<SwiperIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    auto userSize = paintProperty->GetSizeValue(theme->GetSize()).ConvertToPx();
    if (Negative(userSize)) {
        userSize = theme->GetSize().ConvertToPx();
    }

    auto swiperPattern = GetSwiperNode()->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);

    auto currentIndex = swiperPattern->GetCurrentIndex();
    auto lengthBeforeCurrentIndex =
        INDICATOR_PADDING_DEFAULT.ConvertToPx() + (INDICATOR_ITEM_SPACE.ConvertToPx() + userSize) * currentIndex;
    auto lengthWithCurrentIndex = lengthBeforeCurrentIndex + userSize * 2.0f;
    auto axis = swiperPattern->GetDirection();
    auto mainClickOffset = axis == Axis::HORIZONTAL ? info.GetLocalLocation().GetX() : info.GetLocalLocation().GetY();
    if (mainClickOffset < lengthBeforeCurrentIndex) {
        swiperPattern->ShowPrevious();
    } else if (mainClickOffset > lengthWithCurrentIndex) {
        swiperPattern->ShowNext();
    }
}

} // namespace OHOS::Ace::NG
