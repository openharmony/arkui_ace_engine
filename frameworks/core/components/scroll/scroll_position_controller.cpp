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

#include "core/components/scroll/scroll_position_controller.h"

#include "core/animation/curves.h"
#include "core/components/scroll/render_scroll.h"

namespace OHOS::Ace {

ScrollEventInfo::ScrollEventInfo(ScrollEvent type, double scrollX, double scrollY, int32_t scrollState)
    : BaseEventInfo("scroll"), type_(type), scrollX_(scrollX), scrollY_(scrollY), scrollState_(scrollState)
{}

std::string ScrollEventInfo::ToJSONString() const
{
    switch (type_) {
        case ScrollEvent::SCROLL_TOP:
            return std::string("\"scrolltop\",null");
        case ScrollEvent::SCROLL_BOTTOM:
            return std::string("\"scrollbottom\",null");
        case ScrollEvent::SCROLL_END:
            return std::string("\"scrollend\",null");
        case ScrollEvent::SCROLL_TOUCHUP:
            return std::string("\"scrolltouchup\",null");
        case ScrollEvent::SCROLL_POSITION:
            return std::string("\"scroll\",{\"scrollX\":")
                        .append(std::to_string(scrollX_))
                        .append(",\"scrollY\":")
                        .append(std::to_string(scrollY_))
                        .append(",\"scrollState\":")
                        .append(std::to_string(scrollState_))
                        .append("},null");
        default:
            return "";
    }
}

void ScrollPositionController::JumpTo(int32_t index, int32_t source)
{
    RefPtr<RenderNode> node = scroll_.Upgrade();
    if (node) {
        auto scroll = AceType::DynamicCast<RenderScroll>(node);
        if (scroll) {
            scroll->JumpToIndex(index, source);
        }
    }
}

void ScrollPositionController::JumpTo(double position)
{
    RefPtr<RenderNode> node = scroll_.Upgrade();
    if (node) {
        auto scroll = AceType::DynamicCast<RenderScroll>(node);
        if (scroll) {
            scroll->JumpToPosition(position);
        }
    }
}

void ScrollPositionController::AnimateTo(double position, float duration, const RefPtr<Curve>& curve)
{
    RefPtr<RenderNode> node = scroll_.Upgrade();
    if (node) {
        auto scroll = AceType::DynamicCast<RenderScroll>(node);
        if (scroll) {
            scroll->AnimateTo(position, duration, curve);
        }
    }
}

void ScrollPositionController::ScrollBy(double pixelX, double pixelY, bool smooth)
{
    RefPtr<RenderNode> node = scroll_.Upgrade();
    if (node) {
        auto scroll = AceType::DynamicCast<RenderScroll>(node);
        if (scroll) {
            scroll->ScrollBy(pixelX, pixelY, smooth);
        }
    }
}

void ScrollPositionController::ScrollArrow(double scrollDistance, bool reverse, bool smooth)
{
    if (scrollDistance > 0.0) {
        RefPtr<RenderNode> node = scroll_.Upgrade();
        if (node) {
            auto scroll = AceType::DynamicCast<RenderScroll>(node);
            if (scroll) {
                if (reverse) {
                    ScrollBy(-scrollDistance, -scrollDistance, smooth);
                } else {
                    ScrollBy(scrollDistance, scrollDistance, smooth);
                }
            }
        }
    }
}

double ScrollPositionController::GetCurrentPosition() const
{
    RefPtr<RenderNode> node = scroll_.Upgrade();
    if (!node) {
        return 0.0;
    }
    auto scroll = AceType::DynamicCast<RenderScroll>(node);
    if (!scroll) {
        return 0.0;
    }

    return scroll->GetCurrentPosition();
}

void ScrollPositionController::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    RefPtr<RenderNode> node = scroll_.Upgrade();
    if (node) {
        auto scroll = AceType::DynamicCast<RenderScroll>(node);
        if (scroll) {
            scroll->ScrollToEdge(scrollEdgeType, smooth);
        }
    }
}

void ScrollPositionController::ScrollPage(bool reverse, bool smooth)
{
    RefPtr<RenderNode> node = scroll_.Upgrade();
    if (node) {
        auto scroll = AceType::DynamicCast<RenderScroll>(node);
        if (scroll) {
            scroll->ScrollPage(reverse, smooth);
        }
    }
}

Offset ScrollPositionController::GetCurrentOffset() const
{
    RefPtr<RenderNode> node = scroll_.Upgrade();
    auto scroll = AceType::DynamicCast<RenderScroll>(node);
    if (!scroll) {
        return Offset::Zero();
    }

    return scroll->GetCurrentOffset();
}

} // namespace OHOS::Ace
