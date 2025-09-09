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

#include "core/common/resource/resource_parse_utils.h"
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
        NG::CalcLength safeAreaPaddingTop(inset.top_.Length());
        NG::CalcLength safeAreaPaddingBottom(inset.bottom_.Length());
        NG::CalcLength safeAreaPaddingLeft(inset.left_.Length());
        NG::CalcLength safeAreaPaddingRight(inset.right_.Length());
        PaddingProperty safeAreaPadding;
        safeAreaPadding.top = safeAreaPaddingTop;
        safeAreaPadding.bottom = safeAreaPaddingBottom;
        safeAreaPadding.left = safeAreaPaddingLeft;
        safeAreaPadding.right = safeAreaPaddingRight;
        modalNodeLayoutProperty->UpdateSafeAreaPadding(safeAreaPadding);
        inset.top_ = { 0, 0 };
        inset.bottom_ = { 0, 0 };
        inset.left_ = { 0, 0 };
        inset.right_ = { 0, 0 };
        modalNodeLayoutProperty->UpdateSafeAreaInsets(inset);
        return;
    }
    modalNodeLayoutProperty->ResetSafeAreaPadding();
    ContentRootPattern::BeforeCreateLayoutWrapper();
}

void ModalPresentationPattern::RegisterModalBgColorResFunc(
    const RefPtr<NG::FrameNode>& modalNode, NG::ModalStyle& modalStyle)
{
    CHECK_NULL_VOID(modalNode);
    auto pattern = modalNode->GetPattern<ModalPresentationPattern>();
    CHECK_NULL_VOID(pattern);
    auto resObj = modalStyle.GetBackgroundColorResObj();
    if (resObj) {
        auto modalWK = AceType::WeakClaim(AceType::RawPtr(modalNode));
        auto&& updateFunc = [modalWK](const RefPtr<ResourceObject>& resObj) {
            auto modalNode = modalWK.Upgrade();
            CHECK_NULL_VOID(modalNode);
            Color backgroundColor;

            // Reparse modal background color and update it.
            bool result = ResourceParseUtils::ParseResColor(resObj, backgroundColor);
            CHECK_NULL_VOID(result);
            auto renderContext = modalNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateBackgroundColor(backgroundColor);
        };
        pattern->AddResObj("modalPage.backgroundColor", resObj, std::move(updateFunc));
    } else {
        pattern->RemoveResObj("modalPage.backgroundColor");
    }
}
} // namespace OHOS::Ace::NG
