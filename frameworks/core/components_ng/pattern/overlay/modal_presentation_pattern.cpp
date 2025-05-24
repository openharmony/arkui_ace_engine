/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"

#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void ModalPresentationPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
}

void ModalPresentationPattern::ModalInteractiveDismiss()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->SetDismissTarget(DismissTarget(targetId_));
    CallOnWillDismiss(static_cast<int32_t>(ContentCoverDismissReason::BACK_PRESSED));
}

void ModalPresentationPattern::OnWillDisappear()
{
    if (onWillDisappear_) {
        onWillDisappear_();
    }
    auto hostNode = GetHost();
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto navigationManager = context->GetNavigationManager();
    CHECK_NULL_VOID(navigationManager);
    navigationManager->FireOverlayLifecycle(hostNode, static_cast<int32_t>(NavDestinationLifecycle::ON_INACTIVE),
        static_cast<int32_t>(NavDestinationActiveReason::CONTENT_COVER));
}

void ModalPresentationPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto builder = AceType::DynamicCast<FrameNode>(host->GetChildByIndex(0));
    CHECK_NULL_VOID(builder);
    auto modalNodeLayoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(modalNodeLayoutProperty);
    auto builderLayoutProperty = builder->GetLayoutProperty();
    CHECK_NULL_VOID(builderLayoutProperty);
    if (GetEnableSafeArea()) {
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto inset = context->GetSafeAreaWithoutProcess();
        builderLayoutProperty->UpdateSafeAreaInsets(inset);
        inset.top_ = { 0, 0 };
        inset.bottom_ = { 0, 0 };
        modalNodeLayoutProperty->UpdateSafeAreaInsets(inset);
    } else {
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto inset = context->GetSafeAreaWithoutProcess();
        inset.top_ = { 0, 0 };
        modalNodeLayoutProperty->UpdateSafeAreaInsets(inset);
        inset.bottom_ = { 0, 0 };
        builderLayoutProperty->UpdateSafeAreaInsets(inset);
    }
}
} // namespace OHOS::Ace::NG
