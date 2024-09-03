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

#include "bridge/declarative_frontend/jsview/models/scroll_model_impl.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
namespace {
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
} // namespace

void ScrollModelImpl::Create()
{
    RefPtr<Component> child;
    auto scrollComponent = AceType::MakeRefPtr<OHOS::Ace::ScrollComponent>(child);
    ViewStackProcessor::GetInstance()->ClaimElementId(scrollComponent);
    auto positionController = AceType::MakeRefPtr<ScrollPositionController>();
    scrollComponent->SetScrollPositionController(positionController);
    ViewStackProcessor::GetInstance()->Push(scrollComponent);
}

RefPtr<ScrollControllerBase> ScrollModelImpl::GetOrCreateController()
{
    auto component = AceType::DynamicCast<ScrollComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_RETURN(component, nullptr);
    if (!component->GetScrollPositionController()) {
        component->SetScrollPositionController(AceType::MakeRefPtr<ScrollPositionController>());
    }
    return component->GetScrollPositionController();
}

RefPtr<ScrollProxy> ScrollModelImpl::CreateScrollBarProxy()
{
    return AceType::MakeRefPtr<ScrollBarProxy>();
}

void ScrollModelImpl::SetAxis(Axis axis)
{
    JSViewSetProperty(&ScrollComponent::SetAxisDirection, axis);
}

void ScrollModelImpl::SetOnScrollBegin(OnScrollBeginEvent&& event)
{
    JSViewSetProperty(&ScrollComponent::SetOnScrollBegin, std::move(event));
}

void ScrollModelImpl::SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& event)
{
}

void ScrollModelImpl::SetOnScroll(NG::ScrollEvent&& event)
{
    auto onScroll = EventMarker([scrollEvent = std::move(event)](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<ScrollEventInfo>(info);
        if (!eventInfo || !scrollEvent) {
            return;
        }
        Dimension x(eventInfo->GetScrollX(), DimensionUnit::VP);
        Dimension y(eventInfo->GetScrollY(), DimensionUnit::VP);
        scrollEvent(x, y);
    });
    JSViewSetProperty(&ScrollComponent::SetOnScroll, std::move(onScroll));
}

void ScrollModelImpl::SetOnScrollEdge(NG::ScrollEdgeEvent&& event)
{
    auto onScrollEdge = EventMarker([scrollEvent = std::move(event)](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<ScrollEventInfo>(info);
        if (!eventInfo || !scrollEvent) {
            return;
        }
        if (eventInfo->GetType() == ScrollEvent::SCROLL_TOP) {
            scrollEvent(NG::ScrollEdge::TOP);
        } else if (eventInfo->GetType() == ScrollEvent::SCROLL_BOTTOM) {
            scrollEvent(NG::ScrollEdge::BOTTOM);
        } else {
            LOGW("EventType is not support: %{public}d", static_cast<int32_t>(eventInfo->GetType()));
        }
    });
    JSViewSetProperty(&ScrollComponent::SetOnScrollEdge, std::move(onScrollEdge));
}

void ScrollModelImpl::SetOnScrollEnd(NG::ScrollEndEvent&& event)
{
    auto onScrollEnd = EventMarker([scrollEvent = std::move(event)](const BaseEventInfo* info) {
        if (scrollEvent) {
            scrollEvent();
        }
    });
    JSViewSetProperty(&ScrollComponent::SetOnScrollEnd, std::move(onScrollEnd));
}

void ScrollModelImpl::SetScrollBarProxy(const RefPtr<ScrollProxy>& proxy)
{
    auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(proxy);
    JSViewSetProperty(&ScrollComponent::SetScrollBarProxy, scrollBarProxy);
}

void ScrollModelImpl::InitScrollBar(const RefPtr<ScrollBarTheme>& theme, const std::pair<bool, Color>& color,
    const std::pair<bool, Dimension>& width, EdgeEffect effect)
{
    auto component = AceType::DynamicCast<ScrollComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(component);
    component->InitScrollBar(theme, color, width, effect);
}

void ScrollModelImpl::SetDisplayMode(int displayMode)
{
    if (displayMode >= 0 && displayMode < static_cast<int32_t>(DISPLAY_MODE.size())) {
        JSViewSetProperty(&ScrollComponent::SetDisplayMode, DISPLAY_MODE[displayMode]);
    }
}

void ScrollModelImpl::SetScrollBarWidth(const Dimension& dimension)
{
    JSViewSetProperty(&ScrollComponent::SetScrollBarWidth, dimension);
}

void ScrollModelImpl::SetScrollBarColor(const Color& color)
{
    JSViewSetProperty(&ScrollComponent::SetScrollBarColor, color);
}

void ScrollModelImpl::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled)
{
    auto scrollComponent = AceType::DynamicCast<ScrollComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(scrollComponent);
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect;
    if (edgeEffect == EdgeEffect::SPRING) {
        scrollEdgeEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
    } else if (edgeEffect == EdgeEffect::FADE) {
        scrollEdgeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::GRAY);
    } else {
        scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    }
    scrollComponent->SetScrollEffect(scrollEdgeEffect);
}

void ScrollModelImpl::SetHasWidth(bool hasWidth)
{
    JSViewSetProperty(&ScrollComponent::SetHasWidth, hasWidth);
}

void ScrollModelImpl::SetHasHeight(bool hasHeight)
{
    JSViewSetProperty(&ScrollComponent::SetHasHeight, hasHeight);
}

} // namespace OHOS::Ace::Framework
