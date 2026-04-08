/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"

#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "test/mock/frameworks/core/animation/mock_animation_proxy.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::NG {
RefPtr<RenderContext> RenderContext::Create()
{
    return MakeRefPtr<::testing::NiceMock<MockRenderContext>>();
}

void RenderContext::SetNeedCallbackNodeChange(bool needCallback) {}

void RenderContext::SetRequestFrame(const std::function<void(bool)>& requestFrame)
{
    requestFrame_ = requestFrame;
}

void RenderContext::SetHostNode(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

RefPtr<FrameNode> RenderContext::GetHost() const
{
    return host_.Upgrade();
}

void RenderContext::SetSharedTransitionOptions(const std::shared_ptr<SharedTransitionOption>& option)
{
    sharedTransitionOption_ = option;
}

const std::shared_ptr<SharedTransitionOption>& RenderContext::GetSharedTransitionOption() const
{
    return sharedTransitionOption_;
}

void RenderContext::SetShareId(const ShareId& shareId)
{
    shareId_ = shareId;
}

const ShareId& RenderContext::GetShareId() const
{
    return shareId_;
}

bool RenderContext::HasSharedTransition() const
{
    return !shareId_.empty();
}

bool RenderContext::HasSharedTransitionOption() const
{
    return sharedTransitionOption_ != nullptr;
}

void RenderContext::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}

void RenderContext::FromJson(const std::unique_ptr<JsonValue>& json) {}

void RenderContext::RequestNextFrame(bool isOffScreenNode) const
{
    (void)isOffScreenNode;
}

void RenderContext::SetSystemMaterial(const RefPtr<UiMaterial>& material)
{
    uiMaterial_ = material;
}

RefPtr<UiMaterial> RenderContext::GetSystemMaterial() const
{
    return uiMaterial_;
}

#ifdef ENHANCED_ANIMATION
namespace {
void InitProp(const RefPtr<PropertyBase>& propBase)
{
    if (auto prop = AceType::DynamicCast<AnimatablePropertyFloat>(propBase); prop) {
        MockAnimationProxy<float>::GetInstance().RegisterProperty(prop, prop->Get());
        // setup proxy for Set, Get, GetStageValue
        prop->SetUpCallbacks(
            [weak = WeakPtr(prop)]() { return MockAnimationProxy<float>::GetInstance().GetValue(weak.Upgrade()); },
            [weak = WeakPtr(prop)](
                float value) { MockAnimationProxy<float>::GetInstance().RecordPropChange(weak, value); },
            [weak = WeakPtr(prop)]() { return MockAnimationProxy<float>::GetInstance().GetEndValue(weak.Upgrade()); });
    }

    if (auto prop = AceType::DynamicCast<AnimatablePropertyOffsetF>(propBase); prop) {
        MockAnimationProxy<OffsetF>::GetInstance().RegisterProperty(prop, prop->Get());
        prop->SetUpCallbacks(
            [weak = WeakPtr(prop)]() { return MockAnimationProxy<OffsetF>::GetInstance().GetValue(weak.Upgrade()); },
            [weak = WeakPtr(prop)](
                OffsetF value) { MockAnimationProxy<OffsetF>::GetInstance().RecordPropChange(weak, value); },
            [weak = WeakPtr(prop)]() {
                return MockAnimationProxy<OffsetF>::GetInstance().GetEndValue(weak.Upgrade());
            });
    }
    /* add code for other types */
}
} // namespace
void MockRenderContext::AttachNodeAnimatableProperty(RefPtr<NodeAnimatablePropertyBase> modifier)
{
    if (!MockAnimationManager::Enabled()) {
        return;
    }
    InitProp(modifier->GetProperty());
}

void MockRenderContext::CancelTranslateXYAnimation()
{
}
OffsetF MockRenderContext::GetTranslateXYProperty()
{
    return {};
}
void MockRenderContext::UpdateTranslateInXY(const OffsetF& offset)
{
}
#endif
} // namespace OHOS::Ace::NG
