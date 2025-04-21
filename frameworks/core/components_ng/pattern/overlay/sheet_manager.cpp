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

#include "core/components_ng/pattern/overlay/sheet_manager.h"

#include "base/error/error_code.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_mask_pattern.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#endif

namespace OHOS::Ace::NG {
namespace {
std::string GetTagFromRootNodeType(RootNodeType rootNodeType)
{
    switch (rootNodeType) {
        case RootNodeType::PAGE_ETS_TAG:
            return V2::PAGE_ETS_TAG;
        case RootNodeType::NAVDESTINATION_VIEW_ETS_TAG:
            return V2::NAVDESTINATION_VIEW_ETS_TAG;
        case RootNodeType::WINDOW_SCENE_ETS_TAG:
            return V2::WINDOW_SCENE_ETS_TAG;
        default:
            return V2::PAGE_ETS_TAG;
    }
}

#ifdef WINDOW_SCENE_SUPPORTED
RefPtr<OverlayManager> FindTargetNodeOverlay(RefPtr<UINode>& parent,
    const RefPtr<FrameNode>& targetNode, bool isShow)
{
    auto node = AceType::DynamicCast<FrameNode>(parent);
    CHECK_NULL_RETURN(node, nullptr);
    auto pattern = node->GetPattern<SystemWindowScene>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->CreateOverlayManager(isShow, targetNode);
    auto overlay = pattern->GetOverlayManager();
    CHECK_NULL_RETURN(overlay, nullptr);
    targetNode->SetRootNodeId(node->GetId());
    targetNode->SetRootNodeType(RootNodeType::WINDOW_SCENE_ETS_TAG);
    return overlay;
}
#endif

int32_t GetOverlayAndTargetNode(int32_t targetId, const SheetStyle& sheetStyle, int32_t sheetContentNodeId,
    RefPtr<OverlayManager>& overlayManager, RefPtr<FrameNode>& targetNode)
{
    bool showInPage = sheetStyle.showInPage.value_or(false);
    if (targetId < 0) {
        return ERROR_CODE_NO_ERROR;
    }
    targetNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(targetId);
    if (targetNode == nullptr) {
        TAG_LOGE(AceLogTag::ACE_SHEET, "TargetId does not exist.");
        return ERROR_CODE_TARGET_ID_NOT_EXIST;
    }
    if (showInPage) {
        if (!targetNode->IsOnMainTree()) {
            TAG_LOGE(AceLogTag::ACE_SHEET, "TargetNode does not on main tree.");
            return ERROR_CODE_TARGET_NOT_ON_MAIN_TREE;
        }
        overlayManager = SheetManager::FindPageNodeOverlay(targetNode, true, true);
        CHECK_NULL_RETURN(overlayManager, ERROR_CODE_TARGET_NOT_PAGE_CHILD);
    }
    // delete Sheet when target node destroy
    auto destructor =
        [id = targetNode->GetId(), rootNodeId = targetNode->GetRootNodeId(),
            rootNodeType = targetNode->GetRootNodeType(), showInPage = sheetStyle.showInPage.value_or(false),
            instanceId = sheetStyle.instanceId.value_or(Container::CurrentId()), sheetContentNodeId]() {
            ContainerScope scope(instanceId);
            SheetManager::GetInstance().CleanBindSheetMap(instanceId, sheetContentNodeId);
            auto pipelineContext = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto overlayManager = pipelineContext->GetOverlayManager();
            if (showInPage) {
                TAG_LOGD(AceLogTag::ACE_SHEET, "To showInPage, get overlayManager from GetOverlayFromPage");
                overlayManager = SheetManager::GetOverlayFromPage(rootNodeId, rootNodeType);
            }
            CHECK_NULL_VOID(overlayManager);
            overlayManager->DeleteModal(id);
        };
    targetNode->PushDestroyCallbackWithTag(destructor, V2::SHEET_WRAPPER_TAG);
    return ERROR_CODE_NO_ERROR;
}
} // namespace

SheetManager::SheetManager() = default;

SheetManager::~SheetManager() = default;

int32_t SheetManager::OpenBindSheetByUIContext(
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
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, ERROR_CODE_INTERNAL_ERROR);

    if (targetId < 0) {
        sheetStyle.showInPage = false;
    }

    RefPtr<FrameNode> targetNode = AceType::DynamicCast<FrameNode>(overlayManager->GetRootNode().Upgrade());
    auto retErrorCode =
        GetOverlayAndTargetNode(targetId, sheetStyle, sheetContentNode->GetId(), overlayManager, targetNode);
    if (retErrorCode) {
        TAG_LOGE(AceLogTag::ACE_SHEET, "GetOverlayAndTargetNode failed errCode: %{public}d", retErrorCode);
        return retErrorCode;
    }
    overlayManagerMap_.emplace(sheetContentKey, overlayManager);
    targetIdMap_.emplace(sheetContentKey, targetId);

    auto cleanMapFunc = [](const int32_t instanceId, const int32_t sheetContentNodeId) {
        SheetManager::GetInstance().CleanBindSheetMap(instanceId, sheetContentNodeId);
    };

    overlayManager->OpenBindSheetByUIContext(sheetContentNode, std::move(buildTitleNodeFunc),
        sheetStyle, std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
        std::move(sheetSpringBack), std::move(cleanMapFunc), targetNode);
    return ERROR_CODE_NO_ERROR;
}

int32_t SheetManager::UpdateBindSheetByUIContext(const RefPtr<NG::FrameNode>& sheetContentNode,
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

int32_t SheetManager::CloseBindSheetByUIContext(
    const RefPtr<NG::FrameNode>& sheetContentNode, int32_t currentInstanceId)
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

void SheetManager::DeleteOverlayForWindowScene(int32_t rootNodeId, RootNodeType rootNodeType)
{
#ifdef WINDOW_SCENE_SUPPORTED
    if (rootNodeType == RootNodeType::WINDOW_SCENE_ETS_TAG) {
        auto windowSceneNode = FrameNode::GetFrameNode(V2::WINDOW_SCENE_ETS_TAG, rootNodeId);
        CHECK_NULL_VOID(windowSceneNode);
        auto pattern = windowSceneNode->GetPattern<SystemWindowScene>();
        CHECK_NULL_VOID(pattern);
        pattern->DeleteOverlayManager();
    }
#endif
}

RefPtr<OverlayManager> SheetManager::FindPageNodeOverlay(
    const RefPtr<FrameNode>& targetNode, bool isShow, bool isStartByUIContext)
{
    CHECK_NULL_RETURN(targetNode, nullptr);
    if (targetNode->GetRootNodeId() > 0 && !isStartByUIContext) {
        return SheetManager::GetOverlayFromPage(targetNode->GetRootNodeId(), targetNode->GetRootNodeType());
    }
    auto isNav = false;
    RefPtr<OverlayManager> overlay;
    RefPtr<UINode> parent = targetNode;
    while (parent) {
        if (parent->GetTag() == V2::PAGE_ETS_TAG) {
            auto node = AceType::DynamicCast<FrameNode>(parent);
            CHECK_NULL_RETURN(node, nullptr);
            auto pattern = node->GetPattern<PagePattern>();
            CHECK_NULL_RETURN(pattern, nullptr);
            if (!isNav) {
                pattern->CreateOverlayManager(isShow);
                overlay = pattern->GetOverlayManager();
                CHECK_NULL_RETURN(overlay, nullptr);
                targetNode->SetRootNodeId(node->GetId());
                targetNode->SetRootNodeType(RootNodeType::PAGE_ETS_TAG);
            } else {
                node->SetRootNodeType(RootNodeType::NAVDESTINATION_VIEW_ETS_TAG);
                node->SetRootNodeId(targetNode->GetRootNodeId());
            }
            break;
        }
        if (parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG && !isNav) {
            auto node = AceType::DynamicCast<FrameNode>(parent);
            CHECK_NULL_RETURN(node, nullptr);
            auto pattern = node->GetPattern<NavDestinationPattern>();
            CHECK_NULL_RETURN(pattern, nullptr);
            pattern->CreateOverlayManager(isShow);
            overlay = pattern->GetOverlayManager();
            CHECK_NULL_RETURN(overlay, nullptr);
            targetNode->SetRootNodeId(node->GetId());
            targetNode->SetRootNodeType(RootNodeType::NAVDESTINATION_VIEW_ETS_TAG);
            isNav = true;
        }
#ifdef WINDOW_SCENE_SUPPORTED
        if (parent->GetTag() == V2::WINDOW_SCENE_ETS_TAG) {
            overlay = FindTargetNodeOverlay(parent, targetNode, isShow);
            break;
        }
#endif
        parent = parent->GetParent();
    }
    return overlay;
}

RefPtr<OverlayManager> SheetManager::GetOverlayFromPage(int32_t rootNodeId, RootNodeType rootNodeType)
{
    if (rootNodeId <= 0) {
        return nullptr;
    }
    std::string tag  = GetTagFromRootNodeType(rootNodeType);
    auto frameNode = FrameNode::GetFrameNode(tag, rootNodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (tag == V2::PAGE_ETS_TAG) {
        auto node = AceType::DynamicCast<FrameNode>(frameNode);
        CHECK_NULL_RETURN(node, nullptr);
        auto pattern = node->GetPattern<PagePattern>();
        return pattern->GetOverlayManager();
    }
    if (tag == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto node = AceType::DynamicCast<FrameNode>(frameNode);
        CHECK_NULL_RETURN(node, nullptr);
        auto pattern = node->GetPattern<NavDestinationPattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        return pattern->GetOverlayManager();
    }
#ifdef WINDOW_SCENE_SUPPORTED
    if (tag == V2::WINDOW_SCENE_ETS_TAG) {
        auto node = AceType::DynamicCast<FrameNode>(frameNode);
        CHECK_NULL_RETURN(node, nullptr);
        auto pattern = node->GetPattern<SystemWindowScene>();
        CHECK_NULL_RETURN(pattern, nullptr);
        return pattern->GetOverlayManager();
    }
#endif
    return nullptr;
}

bool SheetManager::RemoveSheetByESC()
{
    if (!sheetFocusId_.has_value()) {
        TAG_LOGE(AceLogTag::ACE_SHEET, "focus sheet id is null, can't respond to esc");
        return false;
    }
    auto sheetNode = FrameNode::GetFrameNode(V2::SHEET_PAGE_TAG, sheetFocusId_.value());
    CHECK_NULL_RETURN(sheetNode, false);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, false);
    if (sheetPattern->GetAnimationProcess()) {
        TAG_LOGW(AceLogTag::ACE_SHEET, "sheet is closing by esc");
        return false;
    }
    auto overlayManager = sheetPattern->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    TAG_LOGI(AceLogTag::ACE_SHEET, "sheet will colse by esc, id is : %{public}d", sheetFocusId_.value());
    return overlayManager->RemoveModalInOverlay();
}

void SheetManager::CloseSheetInSubWindow(const SheetKey& sheetKey)
{
    auto instanceId = Container::CurrentId();
    TAG_LOGD(AceLogTag::ACE_SHEET, "close sheet in subwindow by user defined");
    auto manager = SubwindowManager::GetInstance();
    CHECK_NULL_VOID(manager);
    auto parentId = manager->GetParentContainerId(instanceId);
#ifdef OHOS_STANDARD_SYSTEM
    auto subwindow = manager->GetSubwindowByType(instanceId >= MIN_SUBCONTAINER_ID ?
        parentId : instanceId, SubwindowType::TYPE_SHEET);
#else
    auto subwindow = manager->GetSubwindowByType(parentId != INVALID_SUBWINDOW_ID ?
        parentId : instanceId, SubwindowType::TYPE_SHEET);
#endif
    CHECK_NULL_VOID(subwindow);
    auto overlay = subwindow->GetOverlayManager();
    CHECK_NULL_VOID(overlay);
    overlay->CloseSheet(sheetKey);
}

void SheetManager::SetMaskInteractive(const RefPtr<FrameNode>& maskNode, bool isInteractive)
{
    auto maskPattern = maskNode->GetPattern<SheetMaskPattern>();
    if (maskPattern) {
        maskPattern->SetIsMaskInteractive(isInteractive);
    }
}

void SheetManager::RegisterDestroyCallback(const RefPtr<FrameNode>& targetNode, NG::SheetStyle& sheetStyle,
    const int32_t containerId)
{
    auto destructor = [id = targetNode->GetId(), rootNodeId = targetNode->GetRootNodeId(),
        rootNodeType = targetNode->GetRootNodeType(),
        showInPage = sheetStyle.showInPage.value_or(false), containerId]() {
        ContainerScope scope(containerId);
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        if (showInPage) {
            TAG_LOGD(AceLogTag::ACE_SHEET, "To showInPage, get overlayManager from GetOverlayFromPage");
            overlayManager = SheetManager::GetOverlayFromPage(rootNodeId, rootNodeType);
        }
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteModal(id);
        SheetManager::GetInstance().DeleteOverlayForWindowScene(rootNodeId, rootNodeType);
        SheetManager::GetInstance().CloseSheetInSubWindow(SheetKey(id));
    };
    targetNode->PushDestroyCallbackWithTag(destructor, V2::SHEET_WRAPPER_TAG);
}
} // namespace OHOS::Ace::NG
