/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/bridge/waterflow/water_flow_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_v2/water_flow/water_flow_component.h"

namespace OHOS::Ace::Framework {
namespace {
template<class C, class V, class T>
void JSViewSetProperty(void (C::*setMethod)(V), T&& param)
{
#ifndef NG_BUILD
    auto component = AceType::DynamicCast<C>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<C>());
        return;
    }
    ((*component).*setMethod)(std::forward<T>(param));
#else
    LOGE("do not support JSViewSetProperty in new pipeline");
#endif
}
}

void WaterFlowModelImpl::Create()
{
    std::list<RefPtr<Component>> componentChildren;
    auto waterflowComponent = AceType::MakeRefPtr<V2::WaterFlowComponent>(componentChildren);
    CHECK_NULL_VOID(waterflowComponent);
    ViewStackProcessor::GetInstance()->Push(waterflowComponent);
}

void WaterFlowModelImpl::SetFooter(std::function<void()>&& footer)
{
    if (footer) {
        auto waterflowComponent =
            AceType::DynamicCast<V2::WaterFlowComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        CHECK_NULL_VOID(waterflowComponent);
        ScopedViewStackProcessor builderViewStackProcessor;
        footer();
        RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
        waterflowComponent->SetFooterComponent(customComponent);
    }
}

RefPtr<ScrollControllerBase> WaterFlowModelImpl::CreateScrollController()
{
    return AceType::MakeRefPtr<V2::WaterFlowPositionController>();
}

RefPtr<ScrollProxy> WaterFlowModelImpl::CreateScrollBarProxy()
{
    return AceType::MakeRefPtr<ScrollBarProxy>();
}

void WaterFlowModelImpl::SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy)
{
    auto waterflowScroller = AceType::DynamicCast<V2::WaterFlowPositionController>(scroller);
    JSViewSetProperty(&V2::WaterFlowComponent::SetController, waterflowScroller);
    auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(proxy);
    JSViewSetProperty(&V2::WaterFlowComponent::SetScrollBarProxy, scrollBarProxy);
}

void WaterFlowModelImpl::SetColumnsTemplate(const std::string& value)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetColumnsArgs, value);
}

void WaterFlowModelImpl::SetRowsTemplate(const std::string& value)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetRowsArgs, value);
}

void WaterFlowModelImpl::SetItemMinWidth(const Dimension& minWidth)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetMinWidth, minWidth);
}

void WaterFlowModelImpl::SetItemMinHeight(const Dimension& minHeight)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetMinHeight, minHeight);
}

void WaterFlowModelImpl::SetItemMaxWidth(const Dimension& maxWidth)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetMaxWidth, maxWidth);
}

void WaterFlowModelImpl::SetItemMaxHeight(const Dimension& maxHeight)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetMaxHeight, maxHeight);
}

void WaterFlowModelImpl::SetColumnsGap(const Dimension& value)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetColumnsGap, value);
}

void WaterFlowModelImpl::SetRowsGap(const Dimension& value)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetRowsGap, value);
}

void WaterFlowModelImpl::SetLayoutDirection(FlexDirection value)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetLayoutDirection, value);
}

void WaterFlowModelImpl::SetOnReachStart(OnReachEvent&& onReachStart)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetOnReachStart, std::move(onReachStart));
}

void WaterFlowModelImpl::SetOnReachEnd(OnReachEvent&& onReachEnd)
{
    JSViewSetProperty(&V2::WaterFlowComponent::SetOnReachEnd, std::move(onReachEnd));
}
} // namespace OHOS::Ace::Framework