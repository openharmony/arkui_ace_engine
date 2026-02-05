/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/custom_frame_node/custom_pattern.h"
#include "core/components_ng/pattern/custom_frame_node/custom_accessibility_child_tree_callback.h"
#include "core/components_ng/pattern/custom_frame_node/custom_accessibility_provider.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/accessibility/accessibility_session_adapter.h"
#include "core/accessibility/native_interface_accessibility_provider.h"
#include "core/common/ace_application_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

CustomPattern::CustomPattern() = default;

CustomPattern::~CustomPattern() = default;

bool CustomPattern::ReusedNodeSkipMeasure()
{
    return AceApplicationInfo::GetInstance().IsReusedNodeSkipMeasure();
}

RefPtr<AccessibilitySessionAdapter> CustomPattern::GetAccessibilitySessionAdapter()
{
    return accessibilitySessionAdapter_;
}

void CustomPattern::OnAttachContext(PipelineContext *context)
{
    InitializeAccessibility(context);
}

void CustomPattern::OnDetachContext(PipelineContext* context)
{
    CHECK_NULL_VOID(context);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UninitializeAccessibility(host.GetRawPtr(), context);
}

ArkUI_AccessibilityProvider* CustomPattern::GetNativeAccessibilityProvider()
{
    if (arkuiAccessibilityProvider_ == nullptr) {
        arkuiAccessibilityProvider_ = std::make_shared<ArkUI_AccessibilityProvider>();
    }
    return arkuiAccessibilityProvider_.get();
}

void CustomPattern::InitializeAccessibility(PipelineContext* context)
{
    if (accessibilityChildTreeCallback_) {
        return;
    }
    InitializeAccessibilityCallback();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int64_t accessibilityId = host->GetAccessibilityId();
    CHECK_NULL_VOID(context);
    auto accessibilityManager = context->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);

    accessibilityChildTreeCallback_ =
        std::make_shared<CustomAccessibilityChildTreeCallback>(WeakClaim(this), accessibilityId);
    accessibilityManager->RegisterAccessibilityChildTreeCallback(
        accessibilityId, accessibilityChildTreeCallback_);

    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(
            context->GetWindowId(), accessibilityManager->GetTreeId());
    }
}

void CustomPattern::UninitializeAccessibility(FrameNode* frameNode, PipelineContext* context)
{
    CHECK_NULL_VOID(frameNode);
    auto accessibilityManager = context->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    int64_t accessibilityId = frameNode->GetAccessibilityId();

    if (accessibilityManager->IsRegister() && accessibilityChildTreeCallback_) {
        OnAccessibilityChildTreeDeregister(frameNode);
    }
    accessibilityManager->DeregisterAccessibilityChildTreeCallback(accessibilityId);
    accessibilityChildTreeCallback_ = nullptr;
}

bool CustomPattern::OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, false);
    if (pipeline->IsSubPipeline()) {
        windowId = pipeline->GetRealHostWindowId();
    }

    if (accessibilityProvider_ == nullptr) {
        accessibilityProvider_ = AceType::MakeRefPtr<CustomAccessibilityProvider>(WeakClaim(this));
    }

    auto nativeProvider = GetNativeAccessibilityProvider();
    CHECK_NULL_RETURN(nativeProvider, false);
    if (!nativeProvider->IsRegister()) {
        return false;
    }

    nativeProvider->SetInnerAccessibilityProvider(accessibilityProvider_);

    Registration registration;
    registration.windowId = windowId;
    registration.parentWindowId = windowId;
    registration.parentTreeId = treeId;
    registration.elementId = host->GetAccessibilityId();
    registration.operatorType = OperatorType::JS_THIRD_PROVIDER;
    registration.hostNode = WeakClaim(RawPtr(host));
    registration.accessibilityProvider = WeakClaim(RawPtr(accessibilityProvider_));
    return accessibilityManager->RegisterInteractionOperationAsChildTree(registration);
}

bool CustomPattern::OnAccessibilityChildTreeDeregister(FrameNode* frameNode)
{
    RefPtr<PipelineContext> pipeline;
    if (frameNode) {
        pipeline = frameNode->GetContext();
    } else {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        pipeline = host->GetContext();
    }
    CHECK_NULL_RETURN(pipeline, false);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, false);

    auto nativeProvider = GetNativeAccessibilityProvider();
    CHECK_NULL_RETURN(nativeProvider, false);
    nativeProvider->SetInnerAccessibilityProvider(nullptr);

    accessibilitySessionAdapter_ = nullptr;
    accessibilityProvider_ = nullptr;

    return accessibilityManager->DeregisterInteractionOperationAsChildTree(windowId_, treeId_);
}

void CustomPattern::OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId)
{
    windowId_ = static_cast<uint32_t>(childWindowId);
    treeId_ = childTreeId;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetChildWindowId(childWindowId);
    accessibilityProperty->SetChildTreeId(childTreeId);
}

void CustomPattern::InitializeAccessibilityCallback()
{
    auto nativeProvider = GetNativeAccessibilityProvider();
    CHECK_NULL_VOID(nativeProvider);
    nativeProvider->SetRegisterCallback(
        [weak = WeakClaim(this)](bool isRegister) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleRegisterAccessibilityEvent(isRegister);
        });
}

void CustomPattern::HandleRegisterAccessibilityEvent(bool isRegister)
{
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);

    if (!isRegister) {
        accessibilityChildTreeCallback_->OnDeregister();
        return;
    }

    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(
            pipeline->GetWindowId(), accessibilityManager->GetTreeId());
    }
}

RefPtr<EventHub> CustomPattern::CreateEventHub()
{
    return MakeRefPtr<OverflowScrollEventHub>();
}

RefPtr<VerticalOverflowHandler> CustomPattern::GetOrCreateVerticalOverflowHandler(const WeakPtr<FrameNode>& host)
{
    if (!vOverflowHandler_) {
        vOverflowHandler_ = MakeRefPtr<VerticalOverflowHandler>(host);
    }
    return vOverflowHandler_;
}

void CustomPattern::DumpInfo()
{
    if (vOverflowHandler_) {
        DumpLog::GetInstance().AddDesc(std::string("OverflowInfo: ").append(vOverflowHandler_->ToString().c_str()));
    }
}
} // namespace OHOS::Ace::NG
