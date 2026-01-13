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
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void BindPopupMultiThread(
    const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode, const RefPtr<UINode>& customNode)
{
    CHECK_NULL_VOID(targetNode);
    targetNode->PostAfterAttachMainTreeTask([param, weakTarget = WeakPtr<FrameNode>(targetNode), customNode]() {
        auto targetNode = weakTarget.Upgrade();
        CHECK_NULL_VOID(targetNode);
        ViewAbstract::BindPopup(param, targetNode, customNode);
    });
}

void BindTipsMultiThread(
    const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode, const RefPtr<SpanString>& spanString)
{
    CHECK_NULL_VOID(targetNode);
    targetNode->PostAfterAttachMainTreeTask([param, weakTarget = WeakPtr<FrameNode>(targetNode), spanString]() {
        auto targetNode = weakTarget.Upgrade();
        CHECK_NULL_VOID(targetNode);
        ViewAbstract::BindTips(param, targetNode, spanString);
    });
}

void SetInspectorIdMultiThread(FrameNode* frameNode, const std::string& inspectorId)
{
    CHECK_NULL_VOID(frameNode);
    auto nodeInspectorId = frameNode->GetInspectorId();
    auto nodeId = frameNode->GetId();
    frameNode->PostAfterAttachMainTreeTask([nodeInspectorId, nodeId, inspectorId]() {
        if (nodeInspectorId.has_value() && nodeInspectorId.value() != inspectorId) {
            ElementRegister::GetInstance()->RemoveFrameNodeByInspectorId(nodeInspectorId.value(), nodeId);
        }
    });
    frameNode->UpdateInspectorId(inspectorId);
}

void SetBackgroundBlurStyleMultiThread(FrameNode* frameNode, const BlurStyleOption& bgBlurStyle,
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
    frameNode->CleanVisibleAreaUserCallback(true);
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

void SetBackgroundEffectMultiThread(FrameNode* frameNode, const EffectOption& effectOption,
    const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode), effectOption,
        sysOptions]() mutable {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        if (SystemProperties::ConfigChangePerform()) {
            auto pattern = frameNode->GetPattern();
            CHECK_NULL_VOID(pattern);
            RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
            auto&& updateFunc = [effectOption, sysOptions, weak](const RefPtr<ResourceObject>& resObj) {
                auto frameNode = weak.Upgrade();
                CHECK_NULL_VOID(frameNode);
                EffectOption& effectOptionValue = const_cast<EffectOption&>(effectOption);
                effectOptionValue.ReloadResources();
                ViewAbstract::UpdateBackgroundEffect(AceType::RawPtr(frameNode), effectOptionValue, sysOptions);
            };
            pattern->AddResObj("backgroundEffect", resObj, std::move(updateFunc));
        }
        ViewAbstract::UpdateBackgroundEffect(AceType::RawPtr(frameNode), effectOption, sysOptions);
    });
}

void SetClickEffectLevelMultiThread(FrameNode* frameNode, const ClickEffectLevel& level, float scaleValue)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode), level,
        scaleValue]() mutable {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        ClickEffectInfo clickEffectInfo;
        clickEffectInfo.level = level;
        clickEffectInfo.scaleNumber = scaleValue;
        ACE_UPDATE_NODE_RENDER_CONTEXT(ClickEffectLevel, clickEffectInfo, frameNode);
    });
}

void SetUseEffectMultiThread(FrameNode* frameNode, bool useEffect, EffectType effectType)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(frameNode), useEffect, effectType]() mutable {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto* pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        if (useEffect && effectType == EffectType::WINDOW_EFFECT) {
            pipeline->AddWindowActivateChangedCallback(frameNode->GetId());
        } else {
            pipeline->RemoveWindowActivateChangedCallback(frameNode->GetId());
        }
        const auto& target = frameNode->GetRenderContext();
        if (target) {
            target->UpdateUseEffect(useEffect);
            target->UpdateUseEffectType(effectType);
        }
    });
}
} // namespace OHOS::Ace::NG
