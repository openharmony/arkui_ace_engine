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

#include "core/components_ng/pattern/view_context/view_context_model_ng.h"

#include "base/error/error_code.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<FrameNode> FindDeepestNavDestinationNode(const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    const auto& children = node->GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        if (childNode && childNode->GetLayoutProperty()) {
            auto property = childNode->GetLayoutProperty();
            if (property->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE ||
                !childNode->IsActive()) {
                continue;
            }
        }
        auto target = FindDeepestNavDestinationNode(child);
        if (target) {
            return target;
        }
    }
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(node);
    if (navDestinationGroupNode) {
        return navDestinationGroupNode;
    }
    return nullptr;
}

RefPtr<OverlayManager> FindOverlayManagerFromRoot()
{
    RefPtr<OverlayManager> overlayManager = nullptr;
    auto stageManager = NG::PipelineContext::GetCurrentContext()->GetStageManager();
    CHECK_NULL_RETURN(stageManager, nullptr);
    auto lastPageNode = stageManager->GetLastPage();
    CHECK_NULL_RETURN(lastPageNode, nullptr);
    auto lastNavDesNode =
        AceType::DynamicCast<NavDestinationGroupNode>(FindDeepestNavDestinationNode(lastPageNode));
    if (lastNavDesNode) {
        auto pattern = lastNavDesNode->GetPattern<NavDestinationPattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        pattern->CreateOverlayManager(true);
        overlayManager = pattern->GetOverlayManager();
        lastPageNode->SetRootNodeId(lastNavDesNode->GetId());
        lastPageNode->SetRootNodeType(RootNodeType::NAVDESTINATION_VIEW_ETS_TAG);
    } else {
        auto pattern = lastPageNode->GetPattern<PagePattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        pattern->CreateOverlayManager(true);
        overlayManager = pattern->GetOverlayManager();
        lastPageNode->SetRootNodeId(0);
        lastPageNode->SetRootNodeType(RootNodeType::PAGE_ETS_TAG);
    }
    return overlayManager;
}

int32_t GetOverlayAndTargetNode(int32_t targetId, const SheetStyle& sheetStyle, int32_t sheetContentNodeId,
    RefPtr<OverlayManager>& overlayManager, RefPtr<FrameNode>& targetNode)
{
    bool showInPage = sheetStyle.showInPage.value_or(false);
    if (targetId >= 0) {
        targetNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(targetId);
        if (targetNode == nullptr) {
            TAG_LOGE(AceLogTag::ACE_SHEET, "TargetId does not exist");
            return ERROR_CODE_TARGET_ID_INVALID;
        }
        if (showInPage) {
            overlayManager = ViewAbstractModelNG::FindPageNodeOverlay(targetNode, true, true);
            CHECK_NULL_RETURN(overlayManager, ERROR_CODE_TARGET_ID_INVALID);
        }
        // delete Sheet when target node destroy
        auto destructor =
            [id = targetNode->GetId(), rootNodeId = targetNode->GetRootNodeId(),
                rootNodeType = targetNode->GetRootNodeType(), showInPage = sheetStyle.showInPage.value_or(false),
                instanceId = sheetStyle.instanceId.value_or(Container::CurrentId()), sheetContentNodeId]() {
                ContainerScope scope(instanceId);
                ViewContextModelNG::GetInstance()->CleanBindSheetMap(instanceId, sheetContentNodeId);
                auto overlayManager = NG::PipelineContext::GetCurrentContext()->GetOverlayManager();
                if (showInPage) {
                    TAG_LOGD(AceLogTag::ACE_SHEET, "To showInPage, get overlayManager from GetOverlayFromPage");
                    overlayManager = ViewAbstractModelNG::GetOverlayFromPage(rootNodeId, rootNodeType);
                }
                CHECK_NULL_VOID(overlayManager);
                overlayManager->DeleteModal(id);
            };
        targetNode->PushDestroyCallback(destructor);
    } else if (showInPage) {
        overlayManager = FindOverlayManagerFromRoot();
        CHECK_NULL_RETURN(overlayManager, ERROR_CODE_INTERNAL_ERROR);
        targetNode = AceType::DynamicCast<FrameNode>(overlayManager->GetRootNode().Upgrade());
        CHECK_NULL_RETURN(targetNode, ERROR_CODE_INTERNAL_ERROR);
    }
    return ERROR_CODE_NO_ERROR;
}
}
void ViewContextModelNG::closeAnimation(const AnimationOption& option, bool needFlush)
{
    NG::ViewStackProcessor::GetInstance()->SetImplicitAnimationOption(option);
    if (needFlush) {
        NG::ViewStackProcessor::GetInstance()->FlushImplicitAnimation();
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->CloseFrontendAnimation();
}

void ViewContextModelNG::openAnimation(const AnimationOption& option)
{
    NG::ViewStackProcessor::GetInstance()->SetImplicitAnimationOption(option);
    NG::ViewStackProcessor::GetInstance()->FlushImplicitAnimation();

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->OpenFrontendAnimation(option, option.GetCurve(), option.GetOnFinishEvent());
}

int32_t ViewContextModelNG::OpenBindSheet(
    const RefPtr<NG::FrameNode>& sheetContentNode, std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle,
    std::function<void()>&& onAppear, std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
    std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
    std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
    std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
    std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack,
    int32_t currentInstanceId, int32_t targetId)
{
    CHECK_NULL_RETURN(sheetContentNode, ERROR_CODE_BIND_SHEET_CONTENT_ERROR);
    SheetContentKey sheetContentKey(currentInstanceId, sheetContentNode->GetId());
    if (overlayManagerMap_.find(sheetContentKey) != overlayManagerMap_.end()) {
        return ERROR_CODE_BIND_SHEET_CONTENT_ALREADY_EXIST;
    }
    auto buildTitleNodeFunc = [titleBuildFunc]() -> RefPtr<UINode> {
        CHECK_NULL_RETURN(titleBuildFunc, nullptr);
        NG::ScopedViewStackProcessor builderViewStackProcess;
        titleBuildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        return customNode;
    };

    auto context = AceType::Claim(sheetContentNode->GetContext());
    CHECK_NULL_RETURN(context, ERROR_CODE_INTERNAL_ERROR);
    auto overlayManager = sheetContentNode->GetContext()->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, ERROR_CODE_INTERNAL_ERROR);

    RefPtr<FrameNode> targetNode = AceType::DynamicCast<FrameNode>(overlayManager->GetRootNode().Upgrade());
    auto retErrorCode =
        GetOverlayAndTargetNode(targetId, sheetStyle, sheetContentNode->GetId(), overlayManager, targetNode);
    if (retErrorCode) {
        return retErrorCode;
    }
    overlayManagerMap_.emplace(sheetContentKey, overlayManager);
    targetIdMap_.emplace(sheetContentKey, targetId);

    auto cleanMapFunc = [](const int32_t instanceId, const int32_t sheetContentNodeId) {
        ViewContextModel::GetInstance()->CleanBindSheetMap(instanceId, sheetContentNodeId);
    };

    overlayManager->OpenBindSheetByUIContext(sheetContentNode, std::move(buildTitleNodeFunc),
        sheetStyle, std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
        std::move(sheetSpringBack), std::move(cleanMapFunc), targetNode);
    return ERROR_CODE_NO_ERROR;
}

int32_t ViewContextModelNG::UpdateBindSheet(const RefPtr<NG::FrameNode>& sheetContentNode,
    NG::SheetStyle& sheetStyle, bool isPartialUpdate, int32_t currentInstanceId)
{
    CHECK_NULL_RETURN(sheetContentNode, ERROR_CODE_BIND_SHEET_CONTENT_ERROR);
    SheetContentKey sheetContentKey(currentInstanceId, sheetContentNode->GetId());
    auto iter = overlayManagerMap_.find(sheetContentKey);
    if (iter != overlayManagerMap_.end() && targetIdMap_.find(sheetContentKey) != targetIdMap_.end()) {
        auto overlayManager = iter->second;
        overlayManager->UpdateBindSheetByUIContext(
            sheetContentNode, sheetStyle, targetIdMap_[sheetContentKey], isPartialUpdate);
        return ERROR_CODE_NO_ERROR;
    }
    return ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND;
}

int32_t ViewContextModelNG::CloseBindSheet(const RefPtr<NG::FrameNode>& sheetContentNode, int32_t currentInstanceId)
{
    CHECK_NULL_RETURN(sheetContentNode, ERROR_CODE_BIND_SHEET_CONTENT_ERROR);
    SheetContentKey sheetContentKey(currentInstanceId, sheetContentNode->GetId());
    auto iter = overlayManagerMap_.find(sheetContentKey);
    if (iter != overlayManagerMap_.end() && targetIdMap_.find(sheetContentKey) != targetIdMap_.end()) {
        auto overlayManager = iter->second;
        overlayManager->CloseBindSheetByUIContext(sheetContentNode, targetIdMap_[sheetContentKey]);
        return ERROR_CODE_NO_ERROR;
    }
    return ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND;
}
} // namespace OHOS::Ace::NG
