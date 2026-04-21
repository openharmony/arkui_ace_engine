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

#include <algorithm>
#include <string>

#include "base/json/json_util.h"
#include "base/utils/utils.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/manager/content_change_manager/content_change_manager.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/inner_api/ui_session/param_config.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

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
    ACE_SCOPED_TRACE("Modal lifecycle OnWillDisappear");
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
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto overlay = context->GetOverlayManager();
    CHECK_NULL_VOID(overlay);
    auto builder = overlay->GetFirstFrameNodeOfModalBuilder(host);
    CHECK_NULL_VOID(builder);
    auto modalNodeLayoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(modalNodeLayoutProperty);
    auto builderLayoutProperty = builder->GetLayoutProperty();
    CHECK_NULL_VOID(builderLayoutProperty);
    if (GetEnableSafeArea()) {
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

void ModalPresentationPattern::OnAppear()
{
    ACE_SCOPED_TRACE("Modal lifecycle OnAppear");
    if (onAppear_) {
        onAppear_();
    }
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "ModalPresentation.onAppear",
        ComponentEventType::COMPONENT_EVENT_MODAL_PRESENTATION);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto mgr = pipeline->GetContentChangeManager();
    CHECK_NULL_VOID(mgr);
    mgr->OnDialogChangeEnd(GetHost(), true);
}

void ModalPresentationPattern::OnDisappear()
{
    ACE_SCOPED_TRACE("Modal lifecycle OnDisappear");
    if (onDisappear_) {
        isExecuteOnDisappear_ = true;
        onDisappear_();
    }
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "ModalPresentation.onDisappear",
        ComponentEventType::COMPONENT_EVENT_MODAL_PRESENTATION);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto mgr = pipeline->GetContentChangeManager();
    CHECK_NULL_VOID(mgr);
    mgr->OnDialogChangeEnd(GetHost(), false);
}

int32_t ModalPresentationPattern::ParseCommand(const std::string& command, std::string& comValue)
{
    if (command.empty()) {
        return RET_FAILED;
    }
    std::unique_ptr<JsonValue> json = JsonUtil::ParseJsonString(command);
    CHECK_NULL_RETURN(json, RET_FAILED);
    if (json->IsNull()) {
        return RET_FAILED;
    }
    if (!json->Contains("cmd") || !json->GetValue("cmd")->IsString()) {
        return RET_FAILED;
    }
    std::string cmdTmpValue = json->GetString("cmd");
    if (cmdTmpValue != "CloseContentCover") {
        TAG_LOGE(AceLogTag::ACE_SHEET, "command is not CloseContentCover, current: %s", cmdTmpValue.c_str());
        return RET_FAILED;
    }
    comValue = cmdTmpValue;
    return RET_SUCCESS;
}

int32_t ModalPresentationPattern::OnInjectionEvent(const std::string& command)
{
    std::string cmdValue;
    if (command.empty()) {
        TAG_LOGE(AceLogTag::ACE_SHEET, "command is empty");
        return RET_FAILED;
    }
    if (RET_FAILED == ParseCommand(command, cmdValue)) {
        TAG_LOGE(AceLogTag::ACE_SHEET, "command json is error!");
        return RET_FAILED;
    }

    if (cmdValue == "CloseContentCover") {
        // Handle modal sheet close event
        HandleModalSheetEvent(cmdValue);
        ReportCloseContentCoverResult("success", "", "CloseContentCover");
    } else {
        ReportCloseContentCoverResult("failed", "command is error!", "CloseContentCover");
    }
    return RET_SUCCESS;
}

void ModalPresentationPattern::HandleModalSheetEvent(const std::string cmd)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->RemoveModalInOverlay();
}

void ModalPresentationPattern::ReportCloseContentCoverResult(std::string result, std::string reason, std::string event)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto id = host->GetId();
    auto params = JsonUtil::Create();
    CHECK_NULL_VOID(params);
    params->Put("nodeId", id);
    params->Put("event", event.c_str());
    params->Put("result", result.c_str());
    params->Put("reason", reason.c_str());
    auto json = JsonUtil::Create();
    CHECK_NULL_VOID(json);
    std::string eventResult = event + "Result";
    json->Put(eventResult.c_str(), params);
    UiSessionManager::GetInstance()->ReportComponentChangeEvent(
        "result", json->ToString(), ComponentEventType::COMPONENT_EVENT_MODAL_PRESENTATION);
}
} // namespace OHOS::Ace::NG
