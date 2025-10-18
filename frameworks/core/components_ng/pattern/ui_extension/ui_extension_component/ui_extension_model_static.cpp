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

#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_model_static.h"

#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_node.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::NG {
const CalcDimension EMBEDDED_COMPONENT_MIN_WIDTH(10.0f, DimensionUnit::VP);
const CalcDimension EMBEDDED_COMPONENT_MIN_HEIGHT(10.0f, DimensionUnit::VP);

static RefPtr<FrameNode> CreateEmbeddedComponent(int32_t nodeId, NG::SessionType sessionType)
{
    auto frameNode = UIExtensionNode::GetOrCreateUIExtensionNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId, [sessionType] () {
            return AceType::MakeRefPtr<UIExtensionPattern>(false, false, false, sessionType);
        });
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, frameNode);
    ViewAbstract::SetWidth(static_cast<FrameNode*>(
        Referenced::RawPtr(frameNode)), CalcLength(EMBEDDED_COMPONENT_MIN_WIDTH));
    ViewAbstract::SetHeight(static_cast<FrameNode*>(
        Referenced::RawPtr(frameNode)), CalcLength(EMBEDDED_COMPONENT_MIN_HEIGHT));
    ViewAbstract::SetMinWidth(static_cast<FrameNode*>(
        Referenced::RawPtr(frameNode)), CalcLength(EMBEDDED_COMPONENT_MIN_WIDTH));
    ViewAbstract::SetMinHeight(static_cast<FrameNode*>(
        Referenced::RawPtr(frameNode)), CalcLength(EMBEDDED_COMPONENT_MIN_HEIGHT));
    return frameNode;
}

static RefPtr<FrameNode> CreateUIExtensionComponent(int32_t nodeId, NG::SessionType sessionType)
{
    auto frameNode = UIExtensionNode::GetOrCreateUIExtensionNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId, [sessionType] () {
            return AceType::MakeRefPtr<UIExtensionPattern>(false, false, false, sessionType);
        });
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, frameNode);
    return frameNode;
}

RefPtr<FrameNode> UIExtensionStatic::CreateFrameNode(
    int32_t nodeId, NG::SessionType sessionType)
{
    switch (sessionType) {
        case NG::SessionType::UI_EXTENSION_ABILITY:
            return CreateUIExtensionComponent(nodeId, sessionType);
        case NG::SessionType::EMBEDDED_UI_EXTENSION:
            return CreateEmbeddedComponent(nodeId, sessionType);
        default:
            break;
    }

    LOGW("No sessionType support, sessionType is %{public}d", static_cast<int32_t>(sessionType));
    return nullptr;
}

void UIExtensionStatic::UpdateUecConfig(FrameNode* frameNode, bool isTransferringCaller, bool densityDpi,
    bool isWindowModeFollowHost, const std::map<PlaceholderType, RefPtr<NG::FrameNode>>& placeholderMap)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetPattern());
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetIsTransferringCaller() != isTransferringCaller) {
        pattern->SetIsTransferringCaller(isTransferringCaller);
    }
    pattern->SetDensityDpi(densityDpi);
    pattern->SetIsWindowModeFollowHost(isWindowModeFollowHost);
    pattern->SetPlaceholderMap(placeholderMap);
}

void UIExtensionStatic::UpdateWant(FrameNode* frameNode, const AAFwk::Want& want)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetPattern());
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetWantWrap(AceType::MakeRefPtr<OHOS::Ace::WantWrapOhos>(want));
}

void UIExtensionStatic::SetOnError(FrameNode* frameNode,
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnErrorCallback(std::move(onError));
}

void UIExtensionStatic::SetOnReceive(FrameNode* frameNode,
    std::function<void(const AAFwk::WantParams&)>&& onReceive)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnReceiveCallback(std::move(onReceive));
}

void UIExtensionStatic::SetOnRelease(
    FrameNode* frameNode, std::function<void(int32_t)>&& onRelease)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnReleaseCallback(std::move(onRelease));
}

void UIExtensionStatic::SetOnRemoteReady(FrameNode* frameNode,
    std::function<void(const RefPtr<UIExtensionProxy>&)>&& onRemoteReady)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnRemoteReadyCallback(std::move(onRemoteReady));
}

void UIExtensionStatic::SetOnResult(
    FrameNode* frameNode, std::function<void(int32_t, const AAFwk::Want&)>&& onResult)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnResultCallback(std::move(onResult));
}

void UIExtensionStatic::SetOnTerminated(FrameNode* frameNode,
    std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnTerminatedCallback(std::move(onTerminated));
}

void UIExtensionStatic::SetOnDrawReady(FrameNode* frameNode, std::function<void()>&& OnDrawReady)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnDrawReadyCallback(std::move(OnDrawReady));
}
} // namespace OHOS::Ace::NG