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

#include "core/components_ng/pattern/dialog/dialog_inner_manager.h"

#include <utility>

#include "base/error/error_code.h"
#include "base/hiviewdfx/histogram_wrapper.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/interfaces/native/node/calendar_picker_modifier.h"
#include "core/interfaces/native/node/node_date_picker_modifier.h"
#include "core/interfaces/native/node/node_textpicker_modifier.h"
#include "core/interfaces/native/node/node_timepicker_modifier.h"
#include "core/interfaces/native/node/sheet_modifier.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DUMP_LOG_DEPTH_1 = 1;
constexpr int32_t DUMP_LOG_DEPTH_2 = 2;
constexpr int32_t TRANSITION_NODE_2 = 2;
constexpr char SHEET_PAGE_TAG[] = "SheetPage";
const RefPtr<Curve> SHOW_SCALE_ANIMATION_CURVE =
    AceType::MakeRefPtr<CubicCurve>(0.38f, 1.33f, 0.6f, 1.0f); // dialog animation params
} // namespace

DialogInnerManager::DialogInnerManager(const RefPtr<UINode>& rootNode) : rootNodeWeak_(rootNode)
{
    if (rootNode) {
        context_ = rootNode->GetContext();
    }
}

DialogInnerManager::~DialogInnerManager()
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "DialogInnerManager destroyed");
    dialogMap_.clear();
}

RefPtr<PipelineContext> DialogInnerManager::GetPipelineContext() const
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, PipelineContext::GetCurrentContextSafelyWithCheck());
    return context;
}

std::unordered_map<int32_t, RefPtr<FrameNode>> DialogInnerManager::GetDialogMap()
{
    return dialogMap_;
};

RefPtr<FrameNode> DialogInnerManager::GetDialogNodeWithExistContent(const RefPtr<UINode>& node)
{
    auto iter = dialogMap_.begin();
    while (iter != dialogMap_.end()) {
        auto dialogNode = (*iter).second;
        CHECK_NULL_RETURN(dialogNode, nullptr);
        ACE_UINODE_TRACE(dialogNode);
        auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
        CHECK_NULL_RETURN(dialogPattern, nullptr);
        if (dialogPattern->GetCustomNode() == node) {
            return dialogNode;
        }
        iter++;
    }
    return nullptr;
}

void DialogInnerManager::RemoveDialogFromMap(const RefPtr<FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove dialog from map enter");
    CHECK_NULL_VOID(node);
    if (dialogMap_.find(node->GetId()) == dialogMap_.end()) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "not find dialog %{public}d in dialog map", node->GetId());
        return;
    }
    dialogMap_.erase(node->GetId());
}

void DialogInnerManager::ReloadBuilderNodeConfig()
{
    if (dialogMap_.empty()) {
        return;
    }
    auto iter = dialogMap_.begin();
    while (iter != dialogMap_.end()) {
        auto dialogNode = (*iter).second;
        ACE_UINODE_TRACE(dialogNode);
        if (dialogNode) {
            auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(dialogPattern);
            auto customNode = dialogPattern->GetCustomNode();
            if (customNode && customNode->GetUpdateNodeConfig()) {
                customNode->GetUpdateNodeConfig()();
            }
        }
        iter++;
    }
}

void DialogInnerManager::RemoveDialogFromMapForcefully(const RefPtr<FrameNode>& node)
{
    dialogMap_.erase(node->GetId());
}

RefPtr<FrameNode> DialogInnerManager::GetDialog(int32_t dialogId)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "get dialog enter");
    for (auto it = dialogMap_.begin(); it != dialogMap_.end(); it++) {
        if (dialogId == it->second->GetId()) {
            return it->second;
        }
    }
    return nullptr;
}

void DialogInnerManager::OnUIExtensionWindowSizeChange()
{
    for (auto iter = dialogMap_.begin(); iter != dialogMap_.end(); iter++) {
        auto dialogNode = (*iter).second;
        CHECK_NULL_VOID(dialogNode);
        auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(dialogPattern);
        dialogPattern->UpdateHostWindowRect();
    }
}

void DialogInnerManager::SetMaskNodeId(int32_t dialogId, int32_t maskId)
{
    maskNodeIdMap_[dialogId] = maskId;
}

bool DialogInnerManager::IsMaskNode(int32_t maskId)
{
    for (const auto& [key, value] : maskNodeIdMap_) {
        if (value == maskId) {
            return true;
        }
    }
    return false;
}

void DialogInnerManager::PopModalDialog(int32_t maskId, int32_t subWindowId)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "pop modal dialog enter");
    int32_t dialogId = -1;
    for (auto it = maskNodeIdMap_.begin(); it != maskNodeIdMap_.end(); it++) {
        if (maskId == it->second) {
            dialogId = it->first;
            break;
        }
    }
    auto subWindow = SubwindowManager::GetInstance()->GetSubwindowByType(subWindowId, SubwindowType::TYPE_DIALOG);
    CHECK_NULL_VOID(subWindow);
    auto subOverlayManager = subWindow->GetOverlayManager();
    CHECK_NULL_VOID(subOverlayManager);
    std::map<int32_t, RefPtr<FrameNode>> DialogMap(
        subOverlayManager->GetDialogMap().begin(), subOverlayManager->GetDialogMap().end());
    for (auto it = DialogMap.begin(); it != DialogMap.end(); it++) {
        auto dialogProp = DynamicCast<DialogLayoutProperty>(it->second->GetLayoutProperty());
        if (dialogId == it->first) {
            auto hub = it->second->GetEventHub<DialogEventHub>();
            if (hub) {
                hub->FireCancelEvent();
            }
            subOverlayManager->CloseDialog(it->second);
        }
    }
}

int32_t DialogInnerManager::GetMaskNodeIdWithDialogId(int32_t dialogId)
{
    auto iter = maskNodeIdMap_.find(dialogId);
    return (iter == maskNodeIdMap_.end()) ? -1 : iter->second;
}

void DialogInnerManager::RemoveMaskFromMap(const RefPtr<FrameNode>& dialogNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove mask from map enter");
    CHECK_NULL_VOID(dialogNode);
    if (maskNodeIdMap_.find(dialogNode->GetId()) == maskNodeIdMap_.end()) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "not find mask dialog %{public}d in maskNodeIdMap", dialogNode->GetId());
        return;
    }
    maskNodeIdMap_.erase(dialogNode->GetId());
}

void DialogInnerManager::DumpMaskNodeIdMapInfo() const
{
    DumpLog::GetInstance().Print("MaskNodeIdMap: ");
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Size: " + std::to_string(maskNodeIdMap_.size()));
    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "Entries: [");

    for (const auto& entry : maskNodeIdMap_) {
        auto targetId = entry.first;
        auto targetNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(targetId);
        auto nodeId = entry.second;
        auto node = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(nodeId);
        std::string entryLog = "DialogId: " + std::to_string(targetId);
        entryLog += ", DialogTag: " + (targetNode ? targetNode->GetTag() : "NULL");
        entryLog += ", NodeId: " + std::to_string(nodeId);
        entryLog += ", NodeTag: " + (node ? node->GetTag() : "NULL");
        DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_2, entryLog);
    }

    DumpLog::GetInstance().Print(DUMP_LOG_DEPTH_1, "]");
}

void DialogInnerManager::RegisterOnHideDialog(std::function<void()> callback)
{
    onHideDialogCallback_ = std::move(callback);
}

void DialogInnerManager::CallOnHideDialogCallback()
{
    if (onHideDialogCallback_) {
        onHideDialogCallback_();
    }
}

bool DialogInnerManager::FireBackPressEvent() const
{
    if (backPressEvent_) {
        return backPressEvent_();
    }
    return false;
}

void DialogInnerManager::SetBackPressEvent(std::function<bool()> event)
{
    backPressEvent_ = std::move(event);
}

void DialogInnerManager::FireNavigationLifecycle(
    const RefPtr<UINode>& node, int32_t lifecycle, bool isLowerOnly, int32_t reason)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = node->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto navigationManager = pipelineContext->GetNavigationManager();
    CHECK_NULL_VOID(navigationManager);
    auto pattern = frameNode->GetPattern();
    if (InstanceOf<DialogPattern>(pattern)) {
        auto dialogPattern = AceType::DynamicCast<DialogPattern>(pattern);
        CHECK_NULL_VOID(dialogPattern);
        auto dialogProperties = dialogPattern->GetDialogProperties();
        if (!dialogProperties.isUserCreatedDialog || dialogProperties.dialogLevelMode == LevelMode::EMBEDDED) {
            return;
        }
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "fire dialog change to cause navdestination lifecycle: %{public}d",
            static_cast<int32_t>(lifecycle));
        if (dialogProperties.isShowInSubWindow) {
            navigationManager->FireSubWindowLifecycle(node, lifecycle, reason);
            return;
        }
    } else if (node->GetTag() == SHEET_PAGE_TAG) {
        auto* sheetModifier = NG::NodeModifier::GetSheetPatternInnerModifier();
        CHECK_NULL_VOID(sheetModifier);
        if (sheetModifier->sheetIsShowInPage(frameNode)) {
            return;
        }
    }
    if (isLowerOnly) {
        navigationManager->FireLowerLayerLifecycle(node, lifecycle, reason);
        return;
    }
    navigationManager->FireOverlayLifecycle(node, lifecycle, reason);
}

void DialogInnerManager::RegisterDialogLifeCycleCallback(
    const RefPtr<FrameNode>& dialog, const DialogProperties& dialogProps)
{
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    auto onDidAppearEvent = dialogProps.onDidAppear;
    dialogPattern->RegisterDialogDidAppearCallback(std::move(onDidAppearEvent));
    auto onDidDisappearEvent = dialogProps.onDidDisappear;
    dialogPattern->RegisterDialogDidDisappearCallback(std::move(onDidDisappearEvent));
    auto onWillAppearEvent = dialogProps.onWillAppear;
    dialogPattern->RegisterDialogWillAppearCallback(std::move(onWillAppearEvent));
    auto onWillDisappearEvent = dialogProps.onWillDisappear;
    dialogPattern->RegisterDialogWillDisappearCallback(std::move(onWillDisappearEvent));
    auto onWillDismissRelease = dialogProps.onWillDismissRelease;
    dialogPattern->SetOnWillDismissRelease(std::move(onWillDismissRelease));
}

void DialogInnerManager::UpdateChildVisible(
    const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& childNode)
{
    ACE_UINODE_TRACE(node);
    auto layoutProperty = childNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
    auto ctx = childNode->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    ctx->SetTransitionInCallback(
        [overlayManagerWeak = WeakClaim(RawPtr(overlayManager)), nodeWK = WeakPtr<FrameNode>(node)] {
            auto overlayManager = overlayManagerWeak.Upgrade();
            auto node = nodeWK.Upgrade();
            CHECK_NULL_VOID(overlayManager && node);
            auto dialogPattern = node->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(dialogPattern);
            dialogPattern->addTransitionNodeCount();
            if (dialogPattern->getTransitionNodeCount() == TRANSITION_NODE_2) {
                dialogPattern->CallDialogDidAppearCallback();
            } else if (dialogPattern->getTransitionNodeCount() > TRANSITION_NODE_2) {
                TAG_LOGE(AceLogTag::ACE_OVERLAY, "transition node over two");
            }
        });
}

void DialogInnerManager::SetTransitionCallbacks(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& contentNode, const RefPtr<FrameNode>& maskNode,
    const DialogProperties& dialogProps)
{
    if (!maskNode) {
        auto layoutProperty = contentNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
        auto ctx = contentNode->GetRenderContext();
        CHECK_NULL_VOID(ctx);
        if (dialogProps.dialogTransitionEffect != nullptr) {
            ctx->SetTransitionInCallback(
                [overlayManagerWeak = WeakClaim(RawPtr(overlayManager)), nodeWK = WeakPtr<FrameNode>(node)] {
                    auto overlayManager = overlayManagerWeak.Upgrade();
                    auto node = nodeWK.Upgrade();
                    CHECK_NULL_VOID(overlayManager && node);
                    auto dialogPattern = node->GetPattern<DialogPattern>();
                    CHECK_NULL_VOID(dialogPattern);
                    dialogPattern->CallDialogDidAppearCallback();
                });
        } else {
            auto dialogPattern = node->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(dialogPattern);
            dialogPattern->CallDialogDidAppearCallback();
        }
    } else {
        bool defaultAnimation = true;
        if (dialogProps.dialogTransitionEffect != nullptr) {
            defaultAnimation = false;
            UpdateChildVisible(overlayManager, node, contentNode);
        } else {
            auto dialogPattern = node->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(dialogPattern);
            dialogPattern->addTransitionNodeCount();
        }

        if (dialogProps.maskTransitionEffect != nullptr) {
            defaultAnimation = false;
            UpdateChildVisible(overlayManager, node, maskNode);
        } else {
            auto dialogPattern = node->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(dialogPattern);
            dialogPattern->addTransitionNodeCount();
        }

        if (defaultAnimation) {
            auto dialogPattern = node->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(dialogPattern);
            dialogPattern->CallDialogDidAppearCallback();
        }
    }
}

void DialogInnerManager::SendDialogAccessibilityEvent(const RefPtr<FrameNode>& node, AccessibilityEventType eventType)
{
    auto dialogPattern = node->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    DialogProperties props = dialogPattern->GetDialogProperties();
    if (!props.isMask) {
        node->OnAccessibilityEvent(eventType, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
    }
}

void DialogInnerManager::SetDialogTransitionEffect(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& node, const DialogProperties& dialogProps, std::function<void(int32_t)> mountCallback)
{
    CHECK_NULL_VOID(node);
    ACE_UINODE_TRACE(node);
    auto root = rootNodeWeak_.Upgrade();
    auto dialogPattern = node->GetPattern<DialogPattern>();
    dialogPattern->CallDialogWillAppearCallback();

    auto layoutProperty = node->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);

    if (dialogProps.dialogTransitionEffect != nullptr || dialogProps.maskTransitionEffect != nullptr) {
        auto contentNode = AceType::DynamicCast<FrameNode>(node->GetChildByIndex(0));
        auto maskNode = AceType::DynamicCast<FrameNode>(node->GetChildByIndex(1));
        if (contentNode) {
            SetTransitionCallbacks(overlayManager, node, contentNode, maskNode, dialogProps);
        }
    }

    auto ctx = node->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    auto levelOrder = overlayManager->GetLevelOrder(node, dialogProps.levelOrder);
    auto isTopOrder = overlayManager->IsTopOrder(levelOrder);
    bool isNeedFocus = isTopOrder && dialogProps.focusable;
    ctx->SetTransitionInCallback(
        [overlayManagerWeak = WeakClaim(RawPtr(overlayManager)), nodeWK = WeakPtr<FrameNode>(node), isNeedFocus] {
            auto overlayManager = overlayManagerWeak.Upgrade();
            auto node = nodeWK.Upgrade();
            CHECK_NULL_VOID(overlayManager && node);
            if (isNeedFocus) {
                overlayManager->FocusOverlayNode(node);
            }
            auto dialogPattern = node->GetPattern<DialogPattern>();
            dialogPattern->CallDialogDidAppearCallback();
            overlayManager->ContentChangeReport(node, true);
        });

    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        root = dialogPattern->GetDialogProperties().windowScene.Upgrade();
    }

    CHECK_NULL_VOID(root);
    overlayManager->MountToParentWithService(root, node, levelOrder);
    if (!node->GetParent()) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "dialog node mount failed in SetDialogTransitionEffect, parent is null.");
        if (mountCallback) {
            mountCallback(ERROR_CODE_DIALOG_CANNOT_OPEN);
            return;
        }
    }
    if (!node->IsOnMainTree()) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "dialog node is not on main tree after mount.");
        if (mountCallback) {
            mountCallback(ERROR_CODE_DIALOG_CANNOT_OPEN);
            return;
        }
    }
    if (mountCallback) {
        mountCallback(ERROR_CODE_NO_ERROR);
    }
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    if (isTopOrder) {
        SendDialogAccessibilityEvent(node, AccessibilityEventType::PAGE_OPEN);
    }
}

void DialogInnerManager::BeforeShowDialog(const RefPtr<FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "before show dialog");
    CHECK_NULL_VOID(node);
    FireNavigationLifecycle(node, static_cast<int32_t>(NavDestinationLifecycle::ON_INACTIVE), true,
        static_cast<int32_t>(NavDestinationActiveReason::DIALOG));
    if (dialogMap_.find(node->GetId()) != dialogMap_.end()) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "dialog %{public}d already in dialog map", node->GetId());
        return;
    }
    dialogMap_[node->GetId()] = node;
}

void DialogInnerManager::OpenDialogAnimationInner(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& node, const DialogProperties& dialogProps, bool isReadFirstNode)
{
    CHECK_NULL_VOID(node);
    auto dialogPattern = node->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    auto levelOrder = overlayManager->GetLevelOrder(node, dialogProps.levelOrder);
    auto isTopOrder = overlayManager->IsTopOrder(levelOrder);
    bool isNeedFocus = isTopOrder && dialogProps.focusable;

    if (dialogPattern->NeedDistortion()) {
        auto onFinishEvent = [overlayManagerWeak = WeakClaim(RawPtr(overlayManager)), nodeWK = WeakPtr<FrameNode>(node),
                                 isNeedFocus] {
            auto overlayManager = overlayManagerWeak.Upgrade();
            auto node = nodeWK.Upgrade();
            CHECK_NULL_VOID(overlayManager && node);
            if (isNeedFocus) {
                overlayManager->FocusOverlayNode(node);
            }
            auto dialogPattern = node->GetPattern<DialogPattern>();
            dialogPattern->CallDialogDidAppearCallback();
            overlayManager->ContentChangeReport(node, true);
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::DIALOG_LIGHT_SENSE_ANIMATION, true);
        };
        dialogPattern->RegisterOnFinishEvent(onFinishEvent);
        if (isTopOrder && isReadFirstNode) {
            SendDialogAccessibilityEvent(node, AccessibilityEventType::PAGE_OPEN);
        }
        return;
    }
    auto pipeline = GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);

    AnimationOption option;
    // default opacity animation params
    option.SetCurve(Curves::SHARP);
    option.SetDuration(theme->GetOpacityAnimationDurIn());
    option.SetFillMode(FillMode::FORWARDS);
    option = dialogPattern->GetOpenAnimation().value_or(option);
    option.SetIteration(1);
    option.SetAnimationDirection(AnimationDirection::NORMAL);
    auto onFinish = option.GetOnFinishEvent();
    option.SetOnFinishEvent([overlayManagerWeak = WeakClaim(RawPtr(overlayManager)), nodeWK = WeakPtr<FrameNode>(node),
                                onFinish, isNeedFocus] {
        if (onFinish) {
            onFinish();
        }
        auto overlayManager = overlayManagerWeak.Upgrade();
        auto node = nodeWK.Upgrade();
        CHECK_NULL_VOID(overlayManager && node);
        if (isNeedFocus) {
            overlayManager->FocusOverlayNode(node);
        }
        auto dialogPattern = node->GetPattern<DialogPattern>();
        dialogPattern->CallDialogDidAppearCallback();
        overlayManager->ContentChangeReport(node, true);
    });
    auto ctx = node->GetRenderContext();
    option.SetFinishCallbackType(dialogPattern->GetOpenAnimation().has_value()
                                     ? dialogPattern->GetOpenAnimation().value().GetFinishCallbackType()
                                     : FinishCallbackType::REMOVED);
    CHECK_NULL_VOID(ctx);
    ctx->OpacityAnimation(option, theme->GetOpacityStart(), theme->GetOpacityEnd());
    // scale animation on dialog content
    auto contentNode = DynamicCast<FrameNode>(node->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    ctx = contentNode->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    option.SetOnFinishEvent(nullptr);
    option.SetCurve(SHOW_SCALE_ANIMATION_CURVE);
    option.SetDuration(dialogPattern->GetOpenAnimation().has_value()
                           ? dialogPattern->GetOpenAnimation().value().GetDuration()
                           : theme->GetAnimationDurationIn());
    ctx->ScaleAnimation(option, theme->GetScaleStart(), theme->GetScaleEnd());
    if (isTopOrder && isReadFirstNode) {
        SendDialogAccessibilityEvent(node, AccessibilityEventType::PAGE_OPEN);
    }
}

void DialogInnerManager::OpenDialogAnimation(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& node, const DialogProperties& dialogProps, bool isReadFirstNode,
    std::function<void(int32_t)> mountCallback)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "open dialog animation");
    CHECK_NULL_VOID(node);
    ACE_UINODE_TRACE(node);
    auto root = rootNodeWeak_.Upgrade();
    auto dialogPattern = node->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    dialogPattern->CallDialogWillAppearCallback();
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        root = dialogPattern->GetDialogProperties().windowScene.Upgrade();
    }
    CHECK_NULL_VOID(root);
    auto levelOrder = overlayManager->GetLevelOrder(node, dialogProps.levelOrder);
    overlayManager->MountToParentWithService(root, node, levelOrder);
    if (!node->GetParent()) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "dialog node mount failed, parent is null.");
        if (mountCallback) {
            mountCallback(ERROR_CODE_DIALOG_CANNOT_OPEN);
            return;
        }
    }
    if (!node->IsOnMainTree()) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "dialog node is not on main tree after mount.");
        if (mountCallback) {
            mountCallback(ERROR_CODE_DIALOG_CANNOT_OPEN);
            return;
        }
    }
    if (mountCallback) {
        mountCallback(ERROR_CODE_NO_ERROR);
    }
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    OpenDialogAnimationInner(overlayManager, node, dialogProps, isReadFirstNode);
}

void DialogInnerManager::SetContainerButtonEnable(bool isEnabled)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetCloseButtonStatus(isEnabled);
}

RefPtr<UINode> DialogInnerManager::RebuildCustomBuilder(RefPtr<UINode>& contentNode)
{
    auto currentId = Container::CurrentId();
    if (!(currentId >= MIN_SUBCONTAINER_ID && currentId < MIN_PLUGIN_SUBCONTAINER_ID)) {
        return contentNode;
    }

    RefPtr<UINode> customNode;
    auto lazyBuilderFunc = contentNode->GetBuilderFunc();
    if (lazyBuilderFunc) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        lazyBuilderFunc();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    } else {
        customNode = contentNode;
    }

    auto updateNodeFunc = contentNode->GetUpdateNodeFunc();
    if (updateNodeFunc) {
        updateNodeFunc(currentId, customNode);
    }
    auto updateNodeConfig = contentNode->GetUpdateNodeConfig();
    if (customNode && updateNodeConfig) {
        customNode->SetUpdateNodeConfig(std::move(updateNodeConfig));
    }
    return customNode;
}

void DialogInnerManager::CustomDialogRecordEvent(const DialogProperties& dialogProps)
{
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder.SetType("Dialog")
            .SetEventType(Recorder::EventType::DIALOG_SHOW)
            .SetExtra(Recorder::KEY_TITLE, dialogProps.title)
            .SetExtra(Recorder::KEY_SUB_TITLE, dialogProps.subtitle);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
}

void DialogInnerManager::OpenCustomDialogInner(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback, const RefPtr<FrameNode>& dialog,
    bool showComponentContent)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN("PromptAction.OpenCustomDialog", 1);
    if (!dialog) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to create dialog node.");
        callback(showComponentContent ? ERROR_CODE_DIALOG_CONTENT_ERROR : -1);
        return;
    }

    RegisterDialogLifeCycleCallback(dialog, dialogProps);
    BeforeShowDialog(dialog);
    if (dialogProps.dialogCallback) {
        dialogProps.dialogCallback(dialog);
    }

    callback(showComponentContent ? ERROR_CODE_NO_ERROR : dialog->GetId());

    if (dialogProps.transitionEffect != nullptr || dialogProps.dialogTransitionEffect != nullptr ||
        dialogProps.maskTransitionEffect != nullptr) {
        SetDialogTransitionEffect(overlayManager, dialog, dialogProps);
    } else {
        OpenDialogAnimation(overlayManager, dialog, dialogProps);
    }

    dialogCount_++;
    CustomDialogRecordEvent(dialogProps);
}

void DialogInnerManager::OpenCustomDialogInner(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, std::function<void(int32_t errorCode, int32_t dialogId)>&& callback,
    const RefPtr<FrameNode> dialog, bool showComponentContent)
{
    if (!dialog) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to create dialog node.");
        callback(showComponentContent ? ERROR_CODE_DIALOG_CONTENT_ERROR : ERROR_CODE_INTERNAL_ERROR, -1);
        return;
    }

    RegisterDialogLifeCycleCallback(dialog, dialogProps);
    BeforeShowDialog(dialog);
    if (dialogProps.dialogCallback) {
        dialogProps.dialogCallback(dialog);
    }

    int32_t dialogId = dialog->GetId();
    auto mountCallback = std::function<void(int32_t)>(
        [cb = std::move(callback), dialogId, dialog, overlayWeak = WeakClaim(this)](int32_t errorCode) {
            auto overlayManager = overlayWeak.Upgrade();
            if (errorCode != ERROR_CODE_NO_ERROR && overlayManager) {
                overlayManager->RemoveDialogFromMap(dialog);
            }
            cb(errorCode, dialogId);
        });
    if (dialogProps.transitionEffect != nullptr || dialogProps.dialogTransitionEffect != nullptr ||
        dialogProps.maskTransitionEffect != nullptr) {
        SetDialogTransitionEffect(overlayManager, dialog, dialogProps, std::move(mountCallback));
    } else {
        OpenDialogAnimation(overlayManager, dialog, dialogProps, true, std::move(mountCallback));
    }

    dialogCount_++;
    CustomDialogRecordEvent(dialogProps);
}

void DialogInnerManager::DeleteDialogHotAreas(const RefPtr<FrameNode>& dialogNode)
{
    CHECK_NULL_VOID(dialogNode);
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    CHECK_NULL_VOID(dialogLayoutProp);
    if (dialogLayoutProp->GetShowInSubWindowValue(false)) {
        auto pipeline = dialogNode->GetContextRefPtr();
        auto currentId = pipeline ? pipeline->GetInstanceId() : Container::CurrentId();
        SubwindowManager::GetInstance()->DeleteHotAreas(currentId, dialogNode->GetId(), SubwindowType::TYPE_DIALOG);
        SubwindowManager::GetInstance()->HideDialogSubWindow(currentId);
    }
}

void DialogInnerManager::OnDialogCloseEvent(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(overlayManager && node);
    ACE_UINODE_TRACE(node);
    TAG_LOGI(AceLogTag::ACE_DIALOG, "on dialog/%{public}d close event enter", node->GetId());

    overlayManager->FireAutoSave(node);

    auto dialogPattern = node->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    auto option = dialogPattern->GetCloseAnimation().value_or(AnimationOption());
    auto onFinish = option.GetOnFinishEvent();

    auto dialogLayoutProp = dialogPattern->GetLayoutProperty<DialogLayoutProperty>();
    bool isShowInSubWindow = false;
    if (dialogLayoutProp) {
        isShowInSubWindow = dialogLayoutProp->GetShowInSubWindowValue(false);
    }
    if (onFinish != nullptr) {
        onFinish();
    }

    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    CHECK_NULL_VOID(container);
    if (isShowInSubWindow && !container->IsSubContainer()) {
        auto pipeline = node->GetContextRefPtr();
        currentId = pipeline ? pipeline->GetInstanceId() : currentId;
    }

    auto topOrderNode = overlayManager->GetTopOrderNode();
    auto topFocusableNode = overlayManager->GetTopFocusableNode();
    overlayManager->PopLevelOrder(node->GetId());
    ContainerScope scope(currentId);
    auto root = node->GetParent();
    CHECK_NULL_VOID(root);
    SendDialogAccessibilityEvent(node, AccessibilityEventType::PAGE_CLOSE);
    TAG_LOGD(
        AceLogTag::ACE_OVERLAY, "remove DialogNode/%{public}d from RootNode/%{public}d", node->GetId(), root->GetId());
    root->RemoveChild(node, node->GetIsUseTransitionAnimator());
    root->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    overlayManager->FocusNextOrderNode(topFocusableNode);
    overlayManager->SendAccessibilityEventToNextOrderNode(topOrderNode);

    if (container->IsDialogContainer() || isShowInSubWindow) {
        auto dialogProps = AceType::DynamicCast<DialogLayoutProperty>(node->GetLayoutProperty());
        CHECK_NULL_VOID(dialogProps);
        if (dialogPattern->IsUIExtensionSubWindow() && dialogProps->GetIsModal().value_or(true)) {
            SubwindowManager::GetInstance()->RemoveSubwindowByNodeId(node->GetId());
        } else {
            SubwindowManager::GetInstance()->HideDialogSubWindow(currentId);
        }
    }
    DeleteDialogHotAreas(node);
}

void DialogInnerManager::PostDialogFinishEvent(
    const RefPtr<OverlayManager>& overlayManager, const WeakPtr<FrameNode>& nodeWk)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "post dialog finish event enter");
    auto context = GetPipelineContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    // animation finish event should be posted to UI thread.
    taskExecutor->PostTask(
        [DialogInnerManagerWeak = WeakClaim(this), overlayManagerWeak = WeakClaim(RawPtr(overlayManager)), nodeWk,
            id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto DialogInnerManager = DialogInnerManagerWeak.Upgrade();
            auto overlayManager = overlayManagerWeak.Upgrade();
            auto node = nodeWk.Upgrade();
            CHECK_NULL_VOID(DialogInnerManager && overlayManager && node);
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_NONE };
            node->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
            DialogInnerManager->OnDialogCloseEvent(overlayManager, node);
        },
        TaskExecutor::TaskType::UI, "ArkUIOverlayDialogCloseEvent");
}

void DialogInnerManager::UpdateChildInvisible(
    const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& child)
{
    CHECK_NULL_VOID(node);
    ACE_UINODE_TRACE(node);
    auto layoutProperty = child->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);
    auto ctx = child->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    if (ctx->HasDisappearTransition()) {
        ctx->SetTransitionOutCallback(
            [DialogInnerManagerWeak = WeakClaim(this), overlayManagerWeak = WeakClaim(RawPtr(overlayManager)),
                nodeWk = WeakPtr<FrameNode>(node), id = Container::CurrentId(), childWK = WeakPtr<FrameNode>(child)] {
                ContainerScope scope(id);
                auto DialogInnerManager = DialogInnerManagerWeak.Upgrade();
                auto overlayManager = overlayManagerWeak.Upgrade();
                auto node = nodeWk.Upgrade();
                CHECK_NULL_VOID(DialogInnerManager && overlayManager && node);
                node->RemoveChild(childWK.Upgrade());
                if (node->GetChildren().empty()) {
                    DialogInnerManager->PostDialogFinishEvent(overlayManager, nodeWk);
                    auto dialogPattern = node->GetPattern<DialogPattern>();
                    CHECK_NULL_VOID(dialogPattern);
                    dialogPattern->CallDialogDidDisappearCallback();
                }
            });
    } else {
        node->RemoveChild(child);
    }
}

void DialogInnerManager::CloseMaskAndContentMatchTransition(
    const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    ACE_UINODE_TRACE(node);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_KEYBOARD };
    node->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    auto dialogPattern = node->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    dialogPattern->CallDialogWillDisappearCallback();

    auto contentNode = AceType::DynamicCast<FrameNode>(node->GetChildByIndex(0));
    auto maskNode = AceType::DynamicCast<FrameNode>(node->GetChildByIndex(1));
    bool hasDisappearTransition = false;
    if (maskNode) {
        auto ctx = maskNode->GetRenderContext();
        if (ctx) {
            hasDisappearTransition = hasDisappearTransition || ctx->HasDisappearTransition();
        }
        UpdateChildInvisible(overlayManager, node, maskNode);
    }
    if (contentNode) {
        auto ctx = contentNode->GetRenderContext();
        if (ctx) {
            hasDisappearTransition = hasDisappearTransition || ctx->HasDisappearTransition();
        }
        UpdateChildInvisible(overlayManager, node, contentNode);
    }
    if (!hasDisappearTransition) {
        auto id = Container::CurrentId();
        ContainerScope scope(id);
        auto nodeWk = WeakPtr<FrameNode>(node);
        PostDialogFinishEvent(overlayManager, nodeWk);
        dialogPattern->CallDialogDidDisappearCallback();
    }
}

void DialogInnerManager::CloseDialogMatchTransition(
    const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "close dialog match transition");
    CHECK_NULL_VOID(node);
    ACE_UINODE_TRACE(node);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_KEYBOARD };
    node->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    auto dialogPattern = node->GetPattern<DialogPattern>();
    dialogPattern->CallDialogWillDisappearCallback();

    auto ctx = node->GetRenderContext();
    if (!ctx) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "not find render context when closing dialog");
        return;
    }
    auto layoutProperty = node->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);
    if (ctx->HasDisappearTransition()) {
        ctx->SetTransitionOutCallback(
            [DialogInnerManagerWeak = WeakClaim(this), overlayManagerWeak = WeakClaim(RawPtr(overlayManager)),
                nodeWk = WeakPtr<FrameNode>(node), id = Container::CurrentId()] {
                ContainerScope scope(id);
                auto DialogInnerManager = DialogInnerManagerWeak.Upgrade();
                auto overlayManager = overlayManagerWeak.Upgrade();
                CHECK_NULL_VOID(DialogInnerManager && overlayManager);
                DialogInnerManager->PostDialogFinishEvent(overlayManager, nodeWk);
                auto node = nodeWk.Upgrade();
                CHECK_NULL_VOID(node);
                auto dialogPattern = node->GetPattern<DialogPattern>();
                dialogPattern->CallDialogDidDisappearCallback();
                overlayManager->ContentChangeReport(node, false);
            });
    } else {
        auto id = Container::CurrentId();
        ContainerScope scope(id);
        auto nodeWk = WeakPtr<FrameNode>(node);
        PostDialogFinishEvent(overlayManager, nodeWk);
        dialogPattern->CallDialogDidDisappearCallback();
    }
}

void DialogInnerManager::CloseDialogAnimation(
    const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto pipeline = GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_KEYBOARD };
    node->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);

    // default opacity animation params
    AnimationOption option;
    option.SetFillMode(FillMode::FORWARDS);
    option.SetCurve(Curves::SHARP);
    option.SetDuration(theme->GetAnimationDurationOut());
    // get customized animation params
    auto dialogPattern = node->GetPattern<DialogPattern>();
    dialogPattern->CallDialogWillDisappearCallback();
    option = dialogPattern->GetCloseAnimation().value_or(option);
    option.SetIteration(1);
    option.SetAnimationDirection(AnimationDirection::NORMAL);
    option.SetOnFinishEvent(
        [DialogInnerManagerWeak = WeakClaim(this), overlayManagerWeak = WeakClaim(RawPtr(overlayManager)),
            nodeWk = WeakPtr<FrameNode>(node), id = Container::CurrentId()] {
            ContainerScope scope(id);

            auto DialogInnerManager = DialogInnerManagerWeak.Upgrade();
            auto overlayManager = overlayManagerWeak.Upgrade();
            CHECK_NULL_VOID(DialogInnerManager && overlayManager);
            DialogInnerManager->PostDialogFinishEvent(overlayManager, nodeWk);
            auto node = nodeWk.Upgrade();
            CHECK_NULL_VOID(node);
            auto dialogPattern = node->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(dialogPattern);
            dialogPattern->CallDialogDidDisappearCallback();
            overlayManager->ContentChangeReport(node, false);
        });
    auto ctx = node->GetRenderContext();
    if (!ctx) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "not find render context when closing dialog");
        return;
    }
    option.SetFinishCallbackType(dialogPattern->GetOpenAnimation().has_value()
                                     ? dialogPattern->GetOpenAnimation().value().GetFinishCallbackType()
                                     : FinishCallbackType::REMOVED);
    ctx->OpacityAnimation(option, theme->GetOpacityEnd(), theme->GetOpacityStart());

    // scale animation
    auto contentNode = DynamicCast<FrameNode>(node->GetFirstChild());
    CHECK_NULL_VOID(contentNode);
    ctx = contentNode->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    option.SetOnFinishEvent(nullptr);
    option.SetCurve(Curves::FRICTION);
    ctx->ScaleAnimation(option, theme->GetScaleEnd(), theme->GetScaleStart());
    // start animation immediately
    pipeline->RequestFrame();
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "close dialog animation");
}

void DialogInnerManager::CloseDialogInner(
    const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& dialogNode)
{
    CHECK_NULL_VOID(dialogNode);
    RemoveDialogFromMap(dialogNode);
    if (dialogNode->IsRemoving()) {
        // already in close animation
        TAG_LOGW(AceLogTag::ACE_DIALOG, "dialogNode/%{public}d is removing", dialogNode->GetId());
        return;
    }

    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    CHECK_NULL_VOID(container);
    if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_VOID(container);
    }
    ContainerScope scope(currentId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto contextOverlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(contextOverlayManager);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    auto transitionEffect = dialogPattern->GetDialogProperties().transitionEffect;
    auto dialogTransitionEffect = dialogPattern->GetDialogProperties().dialogTransitionEffect;
    auto maskTransitionEffect = dialogPattern->GetDialogProperties().maskTransitionEffect;
    dialogNode->MarkRemoving();
    if (dialogTransitionEffect != nullptr || maskTransitionEffect != nullptr) {
        CloseMaskAndContentMatchTransition(overlayManager, dialogNode);
    } else if (transitionEffect != nullptr) {
        CloseDialogMatchTransition(overlayManager, dialogNode);
    } else {
        CloseDialogAnimation(overlayManager, dialogNode);
    }
    dialogCount_--;
    dialogPattern->setMaskNodeId(contextOverlayManager->GetMaskNodeIdWithDialogId(dialogNode->GetId()));
    contextOverlayManager->RemoveMaskFromMap(dialogNode);
    // set close button enable
    if (dialogCount_ == 0) {
        SetContainerButtonEnable(true);
    }
    FireNavigationLifecycle(dialogNode, static_cast<int32_t>(NavDestinationLifecycle::ON_ACTIVE), true,
        static_cast<int32_t>(NavDestinationActiveReason::DIALOG));
    CallOnHideDialogCallback();
}

RefPtr<FrameNode> DialogInnerManager::UpdateCustomDialogInner(
    const WeakPtr<NG::UINode>& node, const DialogProperties& dialogProps, const std::function<void(int32_t)>& callback)
{
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Parameters of UpdateCustomDialog are incomplete because of no callback.");
        return nullptr;
    }
    auto contentNode = node.Upgrade();
    if (!contentNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of custom dialog is null");
        callback(ERROR_CODE_DIALOG_CONTENT_ERROR);
        return nullptr;
    }
    TAG_LOGD(AceLogTag::ACE_DIALOG, "UpdateCustomDialog ComponentContent id: %{public}d", contentNode->GetId());
    auto dialogNode = GetDialogNodeWithExistContent(contentNode);
    ACE_UINODE_TRACE(dialogNode);
    if (!dialogNode) {
        dialogNode = SubwindowManager::GetInstance()->GetSubwindowDialogNodeWithExistContent(contentNode);
    }
    if (!dialogNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "UpdateCustomDialog failed because cannot find dialog.");
        callback(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
        return nullptr;
    }
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    CHECK_NULL_RETURN(dialogLayoutProp, nullptr);
    dialogLayoutProp->UpdateDialogAlignment(dialogProps.alignment);
    dialogLayoutProp->UpdateDialogOffset(dialogProps.offset);
    dialogLayoutProp->UpdateAutoCancel(dialogProps.autoCancel);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, nullptr);
    auto maskNode = dialogPattern->GetMaskNode();
    if (maskNode) {
        auto pipelineContext = dialogNode->GetContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
        CHECK_NULL_RETURN(dialogTheme, nullptr);
        auto maskContext = maskNode->GetRenderContext();
        CHECK_NULL_RETURN(maskContext, nullptr);
        maskContext->UpdateBackgroundColor(dialogProps.maskColor.value_or(dialogTheme->GetMaskColorEnd()));
    }
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return dialogNode;
}

void DialogInnerManager::RegisterDialogCallback(
    const RefPtr<FrameNode>& node, std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent)
{
    CHECK_NULL_VOID(node);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    auto dialogPattern = node->GetPattern<DialogPattern>();
    if (!dialogLifeCycleEvent.empty()) {
        auto didAppearEvent = dialogLifeCycleEvent["didAppearId"];
        auto didDisappearEvent = dialogLifeCycleEvent["didDisappearId"];
        auto willAppearEvent = dialogLifeCycleEvent["willAppearId"];
        auto willDisappearEvent = dialogLifeCycleEvent["willDisappearId"];
        dialogPattern->RegisterDialogDidAppearCallback(std::move(didAppearEvent));
        dialogPattern->RegisterDialogDidDisappearCallback(std::move(didDisappearEvent));
        dialogPattern->RegisterDialogWillAppearCallback(std::move(willAppearEvent));
        dialogPattern->RegisterDialogWillDisappearCallback(std::move(willDisappearEvent));
    }
}

RefPtr<FrameNode> DialogInnerManager::ShowDialog(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, std::function<void()>&& buildFunc, bool isRightToLeft)
{
    if (dialogProps.isAlertDialog) {
        ACE_ENGINE_HISTOGRAM_BOOLEAN("UIContext.ShowAlertDialog", 1);
    } else {
        ACE_ENGINE_HISTOGRAM_BOOLEAN("PromptAction.ShowDialog", 1);
    }
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter");
    RefPtr<UINode> customNode;
    // create custom builder content
    if (buildFunc) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        buildFunc();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        if (!customNode) {
            TAG_LOGE(AceLogTag::ACE_OVERLAY, "fail to build customNode");
            return nullptr;
        }
    }

    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    if (!dialog) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "fail to create dialog node");
        return nullptr;
    }
    ACE_UINODE_TRACE(dialog);
    RegisterDialogLifeCycleCallback(dialog, dialogProps);
    BeforeShowDialog(dialog);
    if (dialogProps.transitionEffect != nullptr) {
        SetDialogTransitionEffect(overlayManager, dialog, dialogProps);
    } else {
        OpenDialogAnimation(overlayManager, dialog, dialogProps);
    }
    dialogCount_++;
    // set close button disable
    SetContainerButtonEnable(false);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder.SetType("Dialog")
            .SetEventType(Recorder::EventType::DIALOG_SHOW)
            .SetExtra(Recorder::KEY_TITLE, dialogProps.title)
            .SetExtra(Recorder::KEY_SUB_TITLE, dialogProps.subtitle);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
    return dialog;
}

RefPtr<FrameNode> DialogInnerManager::ShowDialogWithErrorCallback(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, std::function<void()>&& buildFunc, bool isRightToLeft,
    std::function<void(int32_t, int32_t)> callback)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter");
    RefPtr<UINode> customNode;
    if (buildFunc) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        buildFunc();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        if (!customNode) {
            TAG_LOGE(AceLogTag::ACE_OVERLAY, "fail to build customNode");
            return nullptr;
        }
    }

    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    if (!dialog) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "fail to create dialog node");
        return nullptr;
    }
    ACE_UINODE_TRACE(dialog);
    RegisterDialogLifeCycleCallback(dialog, dialogProps);
    BeforeShowDialog(dialog);

    int32_t dialogId = dialog->GetId();
    auto mountCallback = std::function<void(int32_t)>(
        [cb = std::move(callback), dialogId](int32_t errorCode) { cb(errorCode, dialogId); });
    if (dialogProps.transitionEffect != nullptr || dialogProps.dialogTransitionEffect != nullptr ||
        dialogProps.maskTransitionEffect != nullptr) {
        SetDialogTransitionEffect(overlayManager, dialog, dialogProps, std::move(mountCallback));
    } else {
        OpenDialogAnimation(overlayManager, dialog, dialogProps, true, std::move(mountCallback));
    }

    dialogCount_++;
    SetContainerButtonEnable(false);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder.SetType("Dialog")
            .SetEventType(Recorder::EventType::DIALOG_SHOW)
            .SetExtra(Recorder::KEY_TITLE, dialogProps.title)
            .SetExtra(Recorder::KEY_SUB_TITLE, dialogProps.subtitle);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
    return dialog;
}

RefPtr<FrameNode> DialogInnerManager::ShowDialogWithNode(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, const RefPtr<UINode>& customNode, bool isRightToLeft)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter");
    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    CHECK_NULL_RETURN(dialog, nullptr);
    ACE_UINODE_TRACE(dialog);
    BeforeShowDialog(dialog);
    RegisterDialogLifeCycleCallback(dialog, dialogProps);
    if (dialogProps.transitionEffect != nullptr) {
        SetDialogTransitionEffect(overlayManager, dialog, dialogProps);
    } else {
        OpenDialogAnimation(overlayManager, dialog, dialogProps);
    }
    dialogCount_++;
    // set close button disable
    SetContainerButtonEnable(false);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder.SetType("Dialog")
            .SetEventType(Recorder::EventType::DIALOG_SHOW)
            .SetExtra(Recorder::KEY_TITLE, dialogProps.title)
            .SetExtra(Recorder::KEY_SUB_TITLE, dialogProps.subtitle);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
    return dialog;
}

RefPtr<FrameNode> DialogInnerManager::ShowDialogWithNodeAndErrorCallback(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, const RefPtr<UINode>& customNode, bool isRightToLeft,
    std::function<void(int32_t, int32_t)> callback)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter");
    auto dialog = DialogView::CreateDialogNode(dialogProps, customNode);
    CHECK_NULL_RETURN(dialog, nullptr);
    ACE_UINODE_TRACE(dialog);
    BeforeShowDialog(dialog);
    RegisterDialogLifeCycleCallback(dialog, dialogProps);

    int32_t dialogId = dialog->GetId();
    auto mountCallback = std::function<void(int32_t)>(
        [cb = std::move(callback), dialogId](int32_t errorCode) { cb(errorCode, dialogId); });
    if (dialogProps.transitionEffect != nullptr || dialogProps.dialogTransitionEffect != nullptr ||
        dialogProps.maskTransitionEffect != nullptr) {
        SetDialogTransitionEffect(overlayManager, dialog, dialogProps, std::move(mountCallback));
    } else {
        OpenDialogAnimation(overlayManager, dialog, dialogProps, true, std::move(mountCallback));
    }

    dialogCount_++;
    SetContainerButtonEnable(false);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder.SetType("Dialog")
            .SetEventType(Recorder::EventType::DIALOG_SHOW)
            .SetExtra(Recorder::KEY_TITLE, dialogProps.title)
            .SetExtra(Recorder::KEY_SUB_TITLE, dialogProps.subtitle);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
    return dialog;
}

RefPtr<FrameNode> DialogInnerManager::OpenCustomDialog(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback)
{
    RefPtr<UINode> customNode;
    bool showComponentContent = false;
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Parameters of OpenCustomDialog are incomplete because of no callback.");
        return nullptr;
    }

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    if (dialogProps.customBuilderWithId) {
        TAG_LOGD(AceLogTag::ACE_DIALOG, "open custom dialog with custom builder with id.");
        NG::ScopedViewStackProcessor builderViewStackProcessor(Container::CurrentId());
        dialogProps.customBuilderWithId(nodeId);
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        if (!customNode) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to build custom node.");
            callback(-1);
            return nullptr;
        }
    } else if (dialogProps.customBuilder) {
        TAG_LOGD(AceLogTag::ACE_DIALOG, "open custom dialog with custom builder.");
        NG::ScopedViewStackProcessor builderViewStackProcessor(Container::CurrentId());
        dialogProps.customBuilder();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        if (!customNode) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to build custom node.");
            callback(-1);
            return nullptr;
        }
    } else if (dialogProps.customCNode.Upgrade()) {
        auto contentNode = dialogProps.customCNode.Upgrade();
        customNode = RebuildCustomBuilder(contentNode);
        if (!customNode) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to build custom cnode.");
            callback(-1);
            return nullptr;
        }
    } else {
        auto contentNode = dialogProps.contentNode.Upgrade();
        if (!contentNode) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of custom dialog is null");
            callback(ERROR_CODE_DIALOG_CONTENT_ERROR);
            return nullptr;
        }
        if (GetDialogNodeWithExistContent(contentNode)) {
            TAG_LOGW(AceLogTag::ACE_DIALOG, "Content of custom dialog already existed.");
            callback(ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
            return nullptr;
        }
        TAG_LOGD(AceLogTag::ACE_DIALOG, "OpenCustomDialog ComponentContent id: %{public}d", contentNode->GetId());
        customNode = RebuildCustomBuilder(contentNode);
        showComponentContent = true;
    }
    auto dialog = DialogView::CreateDialogNode(nodeId, dialogProps, customNode);
    ACE_UINODE_TRACE(dialog);
    OpenCustomDialogInner(overlayManager, dialogProps, std::move(callback), dialog, showComponentContent);
    return dialog;
}

RefPtr<FrameNode> DialogInnerManager::OpenCustomDialogWithErrorCallback(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, std::function<void(int32_t errorCode, int32_t dialogId)>&& callback)
{
    RefPtr<UINode> customNode;
    bool showComponentContent = false;
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Parameters of OpenCustomDialog are incomplete because of no callback.");
        return nullptr;
    }

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    if (dialogProps.customBuilderWithId) {
        TAG_LOGD(AceLogTag::ACE_DIALOG, "open custom dialog with custom builder with id.");
        NG::ScopedViewStackProcessor builderViewStackProcessor(Container::CurrentId());
        dialogProps.customBuilderWithId(nodeId);
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        if (!customNode) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to build custom node.");
            callback(ERROR_CODE_DIALOG_CONTENT_ERROR, -1);
            return nullptr;
        }
    } else if (dialogProps.customBuilder) {
        TAG_LOGD(AceLogTag::ACE_DIALOG, "open custom dialog with custom builder.");
        NG::ScopedViewStackProcessor builderViewStackProcessor(Container::CurrentId());
        dialogProps.customBuilder();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        if (!customNode) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to build custom node.");
            callback(ERROR_CODE_DIALOG_CONTENT_ERROR, -1);
            return nullptr;
        }
    } else if (dialogProps.customCNode.Upgrade()) {
        auto contentNode = dialogProps.customCNode.Upgrade();
        customNode = RebuildCustomBuilder(contentNode);
        if (!customNode) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Fail to build custom cnode.");
            callback(ERROR_CODE_DIALOG_CONTENT_ERROR, -1);
            return nullptr;
        }
    } else {
        auto contentNode = dialogProps.contentNode.Upgrade();
        if (!contentNode) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of custom dialog is null");
            callback(ERROR_CODE_DIALOG_CONTENT_ERROR, -1);
            return nullptr;
        }
        if (GetDialogNodeWithExistContent(contentNode)) {
            TAG_LOGW(AceLogTag::ACE_DIALOG, "Content of custom dialog already existed.");
            callback(ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST, -1);
            return nullptr;
        }
        TAG_LOGD(AceLogTag::ACE_DIALOG, "OpenCustomDialog ComponentContent id: %{public}d", contentNode->GetId());
        customNode = RebuildCustomBuilder(contentNode);
        showComponentContent = true;
    }
    auto dialog = DialogView::CreateDialogNode(nodeId, dialogProps, customNode);
    ACE_UINODE_TRACE(dialog);
    OpenCustomDialogInner(overlayManager, dialogProps, std::move(callback), dialog, showComponentContent);
    return dialog;
}

void DialogInnerManager::CloseCustomDialogWithId(
    const RefPtr<OverlayManager>& overlayManager, const int32_t dialogId, std::function<void(int32_t)>&& callback)
{
    auto iter = dialogMap_.end();
    if (dialogId == -1) {
        int32_t tmpNodeId = -1;
        RefPtr<FrameNode> tmpNode;
        iter = dialogMap_.begin();
        while (iter != dialogMap_.end()) {
            auto dialogNode = (*iter).second;
            ACE_UINODE_TRACE(dialogNode);
            if (dialogNode && dialogNode->GetId() > tmpNodeId) {
                tmpNodeId = dialogNode->GetId();
                tmpNode = dialogNode;
            }
            iter++;
        }
        if (tmpNode) {
            DeleteDialogHotAreas(tmpNode);
            CloseDialogInner(overlayManager, tmpNode);
            if (callback) {
                callback(ERROR_CODE_NO_ERROR);
            }
        } else {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "not find dialog when no dialog id");
            if (callback) {
                callback(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
            }
        }
    } else {
        iter = dialogMap_.find(dialogId);
        if (iter == dialogMap_.end()) {
            TAG_LOGE(AceLogTag::ACE_DIALOG, "not find dialog by id %{public}d", dialogId);
            if (callback) {
                callback(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
            }
            return;
        }
        RefPtr<FrameNode> tmpDialog = (*iter).second;
        DeleteDialogHotAreas(tmpDialog);
        CloseDialogInner(overlayManager, tmpDialog);
        if (callback) {
            callback(ERROR_CODE_NO_ERROR);
        }
    }
}

void DialogInnerManager::CloseCustomDialogWithNode(const RefPtr<OverlayManager>& overlayManager,
    const WeakPtr<NG::UINode>& node, std::function<void(int32_t)>&& callback)
{
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Parameters of CloseCustomDialog are incomplete because of no callback.");
        return;
    }
    auto contentNode = node.Upgrade();
    if (!contentNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of custom dialog is null");
        callback(ERROR_CODE_DIALOG_CONTENT_ERROR);
        return;
    }
    TAG_LOGD(AceLogTag::ACE_DIALOG, "CloseCustomDialog ComponentContent id: %{public}d", contentNode->GetId());
    auto dialogNode = GetDialogNodeWithExistContent(contentNode);
    ACE_UINODE_TRACE(dialogNode);
    if (!dialogNode) {
        dialogNode = SubwindowManager::GetInstance()->GetSubwindowDialogNodeWithExistContent(contentNode);
    }
    if (dialogNode) {
        DeleteDialogHotAreas(dialogNode);
        CloseDialogInner(overlayManager, dialogNode);
        callback(ERROR_CODE_NO_ERROR);
        return;
    }
    TAG_LOGE(AceLogTag::ACE_DIALOG, "CloseCustomDialog failed because cannot find dialog.");
    callback(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
}

void DialogInnerManager::UpdateCustomDialog(
    const WeakPtr<NG::UINode>& node, const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback)
{
    auto dialogNode = UpdateCustomDialogInner(node, dialogProps, callback);
    ACE_UINODE_TRACE(dialogNode);
    if (dialogNode) {
        callback(ERROR_CODE_NO_ERROR);
    }
}

void DialogInnerManager::UpdateCustomDialogWithNode(
    const WeakPtr<NG::UINode>& node, const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback)
{
    auto dialogNode = UpdateCustomDialogInner(node, dialogProps, callback);
    ACE_UINODE_TRACE(dialogNode);
    if (dialogNode) {
        callback(dialogNode->GetId());
        dialogMap_[dialogNode->GetId()] = dialogNode;
    }
}

void DialogInnerManager::ShowDateDialog(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show date dialog enter");
#ifndef ARKUI_WEARABLE
    auto* modifier = NodeModifier::GetDatepickerCustomModifier();
    CHECK_NULL_VOID(modifier);
    DatePickerUtil::DatePickerDialogInfo dialogInfo = { .dialogProperties = dialogProps,
        .settingData = settingData,
        .buttonInfos = buttonInfos,
        .datePickerNode = nullptr };
    modifier->setDatePickerDialogViewShow(dialogInfo, std::move(dialogEvent), std::move(dialogCancelEvent));
    RefPtr<FrameNode> dialogNode = dialogInfo.datePickerNode;
    CHECK_NULL_VOID(dialogNode);
    ACE_UINODE_TRACE(dialogNode);
    RegisterDialogCallback(dialogNode, std::move(dialogLifeCycleEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(overlayManager, dialogNode, dialogProps);
#endif
}

void DialogInnerManager::ShowTimeDialog(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, const TimePickerSettingData& settingData,
    std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show time dialog enter");
#ifndef ARKUI_WEARABLE
    auto* modifier = NodeModifier::GetTimepickerCustomModifier();
    CHECK_NULL_VOID(modifier);
    TimePickerUtil::TimePickerDialogInfo dialogInfo = { .dialogProperties = dialogProps,
        .settingData = settingData,
        .buttonInfos = buttonInfos,
        .timePickerNode = nullptr };
    modifier->setTimePickerDialogViewShow(
        dialogInfo, std::move(timePickerProperty), std::move(dialogEvent), std::move(dialogCancelEvent));
    RefPtr<FrameNode> dialogNode = dialogInfo.timePickerNode;
    ACE_UINODE_TRACE(dialogNode);
    RegisterDialogCallback(dialogNode, std::move(dialogLifeCycleEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(overlayManager, dialogNode, dialogProps);
#endif
}

void DialogInnerManager::ShowTextDialog(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, const TextPickerSettingData& settingData,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show text dialog enter");
#ifndef ARKUI_WEARABLE
    auto* modifier = NodeModifier::GetTextPickerCustomModifier();
    CHECK_NULL_VOID(modifier);
    auto dialogNode = modifier->setTextPickerDialogViewShow(
        dialogProps, settingData, buttonInfos, std::move(dialogEvent), std::move(dialogCancelEvent));
    ACE_UINODE_TRACE(dialogNode);
    RegisterDialogCallback(dialogNode, std::move(dialogLifeCycleEvent));
    BeforeShowDialog(dialogNode);
    OpenDialogAnimation(overlayManager, dialogNode, dialogProps);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder.SetType("TextPickerDialog").SetEventType(Recorder::EventType::DIALOG_SHOW);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
#endif
}

void DialogInnerManager::ShowCalendarDialog(const RefPtr<OverlayManager>& overlayManager,
    const DialogProperties& dialogProps, const CalendarSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show calendar dialog enter");
#ifndef ARKUI_WEARABLE
    auto modifier = NodeModifier::GetCalendarPickerModifier();
    CHECK_NULL_VOID(modifier);
    ArkUINodeHandle node =
        modifier->jsShowCalendarPicker(reinterpret_cast<void*>(const_cast<DialogProperties*>(&dialogProps)),
            reinterpret_cast<void*>(const_cast<CalendarSettingData*>(&settingData)),
            reinterpret_cast<void*>(const_cast<std::vector<ButtonInfo>*>(&buttonInfos)),
            reinterpret_cast<void*>(&dialogEvent), reinterpret_cast<void*>(&dialogCancelEvent));
    CHECK_NULL_VOID(node);
    FrameNode* dialogNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(dialogNode);
    ACE_UINODE_TRACE(dialogNode);
    auto dialogRefNode = AceType::Claim<FrameNode>(dialogNode);
    CHECK_NULL_VOID(dialogRefNode);
    RegisterDialogCallback(dialogRefNode, std::move(dialogLifeCycleEvent));
    BeforeShowDialog(dialogRefNode);
    OpenDialogAnimation(overlayManager, dialogRefNode, dialogProps, false);
#endif
}

void DialogInnerManager::CloseDialog(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& dialogNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "close dialog enter");
    DeleteDialogHotAreas(dialogNode);
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialogNode->GetLayoutProperty());
    CHECK_NULL_VOID(dialogLayoutProp);
    if (dialogLayoutProp && dialogLayoutProp->GetShowInSubWindowValue(false) &&
        dialogLayoutProp->GetIsModal().value_or(true)) {
        RefPtr<OverlayManager> parentOverlayManager = nullptr;
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
        auto container = Container::Current();
        auto currentId = Container::CurrentId();
        CHECK_NULL_VOID(container);
        if (container->IsSubContainer()) {
            currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
            container = AceEngine::Get().GetContainer(currentId);
            CHECK_NULL_VOID(container);
        }
        ContainerScope scope(currentId);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
        CHECK_NULL_VOID(context);
        parentOverlayManager = context->GetOverlayManager();
#else
        auto parentPipelineContext = PipelineContext::GetMainPipelineContext();
        CHECK_NULL_VOID(parentPipelineContext);
        parentOverlayManager = parentPipelineContext->GetOverlayManager();
#endif
        CHECK_NULL_VOID(parentOverlayManager);
        RefPtr<FrameNode> maskNode =
            parentOverlayManager->GetDialog(parentOverlayManager->GetMaskNodeIdWithDialogId(dialogNode->GetId()));
        if (maskNode) {
            parentOverlayManager->CloseDialog(maskNode);
        } else {
            TAG_LOGD(AceLogTag::ACE_OVERLAY, "no maskNode in currentDialog/%{public}d", dialogNode->GetId());
        }
    }
    CloseDialogInner(overlayManager, dialogNode);
}

bool DialogInnerManager::RemoveDialog(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& overlay,
    bool isBackPressed, bool isPageRouter)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove dialog enter");
    if (overlay->IsRemoving()) {
        return false;
    }
    if (FireBackPressEvent()) {
        return true;
    }
    auto hub = overlay->GetEventHub<DialogEventHub>();
    if (!isPageRouter && hub) {
        hub->FireCancelEvent();
    }
    CloseDialog(overlayManager, overlay);
    if (isBackPressed) {
        SetBackPressEvent(nullptr);
    }
    return true;
}

bool DialogInnerManager::RemoveDialogWithContent(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& overlay, const DialogProperties& props, bool isBackPressed, bool isPageRouter,
    int32_t subWindowId)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "remove dialog enter");
    CHECK_NULL_RETURN(overlay, false);
    if (overlay->IsRemoving()) {
        return false;
    }
    if (FireBackPressEvent()) {
        return true;
    }
    auto hub = overlay->GetEventHub<DialogEventHub>();
    if (!isPageRouter && hub) {
        hub->FireCancelEvent();
    }
    if (props.isMask) {
        PopModalDialog(overlay->GetId(), subWindowId);
    }
    CloseDialog(overlayManager, overlay);
    if (isBackPressed) {
        SetBackPressEvent(nullptr);
    }
    return true;
}
} // namespace OHOS::Ace::NG
