/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <functional>

#include "core/components_ng/base/view_abstract.h"

#include "core/common/container_scope.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void SetInspectorIdMultiThread(FrameNode* frameNode, const std::string& inspectorId)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode), inspectorId]() {
        auto frameNode = weak.Upgrade();
        if (frameNode) {
            if (frameNode->GetInspectorId().has_value() && frameNode->GetInspectorIdValue() != inspectorId) {
                ElementRegister::GetInstance()->RemoveFrameNodeByInspectorId(
                    frameNode->GetInspectorIdValue(), frameNode->GetId());
            }
            frameNode->UpdateInspectorId(inspectorId);
        }
    });
}

void UpdateBackgroundBlurStyleMultiThread(FrameNode* frameNode, const BlurStyleOption& bgBlurStyle,
    const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode), bgBlurStyle, sysOptions]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        if (bgBlurStyle.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
            pipeline->AddWindowFocusChangedCallback(frameNode->GetId());
        } else {
            pipeline->RemoveWindowFocusChangedCallback(frameNode->GetId());
        }
        auto target = frameNode->GetRenderContext();
        if (target) {
            if (target->GetBackgroundEffect().has_value()) {
                target->UpdateBackgroundEffect(std::nullopt);
            }
            target->UpdateBackBlurStyle(bgBlurStyle, sysOptions);
            if (target->GetBackBlurRadius().has_value()) {
                target->UpdateBackBlurRadius(Dimension());
            }
        }
    });
}

void SetOnAreaChangedMultiThread(FrameNode* frameNode, std::function<void(const RectF& oldRect,
    const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>&& onAreaChanged)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetOnAreaChangeCallback(std::move(onAreaChanged));
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode)]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddOnAreaChangeNode(frameNode->GetId());
    });
}

void SetOnVisibleChangeMultiThread(FrameNode* frameNode, std::function<void(bool, double)> &&onVisibleChange,
    const std::vector<double> &ratioList)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode),
        callback = std::move(onVisibleChange), ratioList]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        frameNode->CleanVisibleAreaUserCallback();
        pipeline->AddVisibleAreaChangeNode(frameNode, ratioList, callback);
    });
}

void SetOnVisibleAreaApproximateChangeMultiThread(FrameNode* frameNode,
    const std::function<void(bool, double)>&& onVisibleChange, const std::vector<double>& ratioList,
    int32_t expectedUpdateInterval)
{
    CHECK_NULL_VOID(frameNode);
    constexpr uint32_t minInterval = 100; // 100ms
    if (expectedUpdateInterval < 0 || static_cast<uint32_t>(expectedUpdateInterval) < minInterval) {
        expectedUpdateInterval = minInterval;
    }
    VisibleCallbackInfo callback;
    callback.callback = std::move(onVisibleChange);
    callback.isCurrentVisible = false;
    callback.period = static_cast<uint32_t>(expectedUpdateInterval);

    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode),
        callback, ratioList]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        frameNode->CleanVisibleAreaUserCallback(true);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddVisibleAreaChangeNode(frameNode->GetId());
        frameNode->SetVisibleAreaUserCallback(ratioList, callback);
    });
}

void ResetAreaChangedMultiThread(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode)]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        frameNode->ClearUserOnAreaChange();
        pipeline->RemoveOnAreaChangeNode(frameNode->GetId());
    });
}

void ResetVisibleChangeMultiThread(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode)]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        frameNode->CleanVisibleAreaUserCallback();
        pipeline->RemoveVisibleAreaChangeNode(frameNode->GetId());
    });
}

void SetNeedFocusMultiThread(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode), value]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto focusHub = frameNode->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        if (value) {
            auto context = frameNode->GetContext();
            CHECK_NULL_VOID(context);
            auto instanceId = context->GetInstanceId();
            ContainerScope scope(instanceId);
            focusHub->RequestFocus();
        } else {
            auto context = frameNode->GetAttachedContext();
            if (!context) {
                TAG_LOGW(AceLogTag::ACE_FOCUS,
                    "Can't find Node %{public}s/%{public}d attachedContext.",
                    frameNode->GetTag().c_str(), frameNode->GetId());
                return;
            }
            auto instanceId = context->GetInstanceId();
            ContainerScope scope(instanceId);
            focusHub->LostFocusToViewRoot();
        }
    });
}
} // namespace OHOS::Ace::NG
