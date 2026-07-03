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

#include "core/components_ng/pattern/bubble/bridge/inner_modifier/bubble_inner_modifier.h"

#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {

namespace {
bool IsOnShow(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsOnShow();
}

bool GetHasTransition(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetHasTransition();
}

bool GetShowInSubWindow(const RefPtr<BubbleLayoutProperty>& layoutProp)
{
    CHECK_NULL_RETURN(layoutProp, false);
    return layoutProp->GetShowInSubWindow().value_or(false);
}

bool GetPrimaryButtonShow(const RefPtr<BubbleRenderProperty>& paintProperty)
{
    CHECK_NULL_RETURN(paintProperty, false);
    return paintProperty->GetPrimaryButtonShow().value_or(false);
}

bool GetAutoCancel(const RefPtr<BubbleRenderProperty>& bubbleRenderProp)
{
    CHECK_NULL_RETURN(bubbleRenderProp, true);
    return bubbleRenderProp->GetAutoCancel().value_or(true);
}

void ResetFocusState(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->ResetFocusState();
}

void StartEnteringAnimationOrTransition(const RefPtr<BubblePattern>& pattern,
    const RefPtr<FrameNode>& popupNode, const std::function<void()>& finish)
{
    CHECK_NULL_VOID(pattern);
    if (pattern->GetHasTransition()) {
        pattern->StartEnteringTransitionEffects(popupNode, finish);
    } else {
        pattern->StartEnteringAnimation(finish);
    }
}

RefPtr<PopupParam> GetPopupParam(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetPopupParam();
}

void SetPopupParam(const RefPtr<BubblePattern>& pattern, const RefPtr<PopupParam>& param)
{
    CHECK_NULL_VOID(pattern);
    pattern->SetPopupParam(param);
}

void RegisterDoubleBindCallback(const RefPtr<BubblePattern>& pattern,
    const std::function<void(const std::string&)>& callback)
{
    CHECK_NULL_VOID(pattern);
    pattern->RegisterDoubleBindCallback(callback);
}

void SetIsTipsAppearing(const RefPtr<BubblePattern>& pattern, bool isTipsAppearing)
{
    CHECK_NULL_VOID(pattern);
    pattern->SetIsTipsAppearing(isTipsAppearing);
}

void AddPipelineCallBack(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->AddPipelineCallBack();
}

void SetInteractiveDismiss(const RefPtr<BubblePattern>& pattern, bool interactiveDismiss)
{
    CHECK_NULL_VOID(pattern);
    pattern->SetInteractiveDismiss(interactiveDismiss);
}

void UpdateOnWillDismiss(const RefPtr<BubblePattern>& pattern, std::function<void(int32_t)> onWillDismiss)
{
    CHECK_NULL_VOID(pattern);
    pattern->UpdateOnWillDismiss(std::move(onWillDismiss));
}

void FireChangeEvent(const RefPtr<BubbleEventHub>& popupEventHub, bool isShow)
{
    CHECK_NULL_VOID(popupEventHub);
    popupEventHub->FireChangeEvent(isShow);
}

bool IsContentUpdatePopupBridge(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, false);
    auto param = pattern->GetPopupParam();
    if (param && param->GetIsPartialUpdate().has_value()) {
        return true;
    }
    return false;
}

void SetPopupHotAreasImpl(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto popupId = host->GetId();
    auto layoutProp = host->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto isBlock = layoutProp->GetBlockEventValue(true);
    auto isShowInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
    if (isShowInSubWindow && pattern->IsOnShow()) {
        std::vector<Rect> rects;
        if (!isBlock) {
            auto rect = Rect(pattern->GetChildOffset().GetX(), pattern->GetChildOffset().GetY(),
                pattern->GetChildSize().Width(), pattern->GetChildSize().Height());
            rects.emplace_back(rect);
        } else {
            auto parentWindowRect = pattern->GetHostWindowRect();
            auto rect = Rect(pattern->GetChildOffset().GetX(), pattern->GetChildOffset().GetY(),
                pattern->GetChildSize().Width(), pattern->GetChildSize().Height());
            rects.emplace_back(parentWindowRect);
            rects.emplace_back(rect);
        }
        auto subWindowMgr = SubwindowManager::GetInstance();
        subWindowMgr->SetHotAreas(rects, SubwindowType::TYPE_POPUP, popupId, pattern->GetContainerId());
    }
}

bool ErasePopupSetupBridge(const RefPtr<BubbleLayoutProperty>& layoutProp)
{
    CHECK_NULL_RETURN(layoutProp, false);
    return layoutProp->GetShowInSubWindow().value_or(false);
}

bool IsCustomNodeMatchBridge(const RefPtr<BubblePattern>& pattern, const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(pattern, false);
    CHECK_NULL_RETURN(node, false);
    return pattern->GetCustomNode() == AceType::Claim(Referenced::RawPtr(node));
}

bool HandleOnWillDismissCleanupBridge(const RefPtr<BubblePattern>& pattern, bool isForceClear)
{
    CHECK_NULL_RETURN(pattern, false);
    return pattern->HasOnWillDismiss() && !isForceClear;
}

RefPtr<FrameNode> GetPopupCustomNodeBridge(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, nullptr);
    return AceType::DynamicCast<FrameNode>(pattern->GetCustomNode());
}

void CallOnWillDismissWithCheckBridge(const RefPtr<BubblePattern>& pattern, int32_t dismissReason)
{
    CHECK_NULL_VOID(pattern);
    pattern->CallOnWillDismiss(dismissReason);
}

bool CheckAndSetExitingStatusBridge(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, false);
    if (pattern->GetTransitionStatus() == TransitionStatus::EXITING) {
        return true;
    }
    pattern->SetTransitionStatus(TransitionStatus::EXITING);
    return false;
}

std::function<void()> CreateHidePopupOnFinish(const RefPtr<BubblePattern>& popupPattern,
    OverlayManager* overlayManager, const BubbleHidePopupParams& params,
    const RefPtr<FrameNode>& popupNode, const RefPtr<UINode>& rootNode)
{
    // Fire onWillDisappear callback
    auto popupParam = popupPattern->GetPopupParam();
    if (popupParam) {
        popupParam->FireOnWillDisappear();
    }

    auto overlayRef = AceType::Claim(overlayManager);
    return [params, popupNodeWk = WeakPtr<FrameNode>(popupNode),
        rootNodeWk = WeakPtr<UINode>(rootNode), overlayManagerWk = WeakPtr<OverlayManager>(overlayRef)]() {
        auto rootNode = rootNodeWk.Upgrade();
        auto popupNode = popupNodeWk.Upgrade();
        auto overlayManager = overlayManagerWk.Upgrade();
        CHECK_NULL_VOID(rootNode && popupNode && overlayManager);
        ACE_UINODE_TRACE(popupNode);

        // Fire onDidDisappear callback
        auto popupPattern = popupNode->GetPattern<BubblePattern>();
        if (popupPattern) {
            auto popupParam = popupPattern->GetPopupParam();
            if (popupParam) {
                popupParam->FireOnDidDisappear();
            }
        }

        auto popupMap = overlayManager->GetPopupMap();
        auto popupInfoInMap = popupMap.find(params.targetId);
        auto targetIsInMap = popupInfoInMap != popupMap.end();
        bool popupNodeIsInMap = false;
        if (targetIsInMap) {
            popupNodeIsInMap = popupMap[params.targetId].popupNode == popupNode;
            if (popupNodeIsInMap && popupMap[params.targetId].isCurrentOnShow) {
                return;
            }
        }
        CHECK_NULL_VOID(popupPattern);
        popupPattern->SetTransitionStatus(TransitionStatus::INVISIABLE);
        auto popupEventHub = popupNode->GetEventHub<BubbleEventHub>();
        CHECK_NULL_VOID(popupEventHub);
        popupEventHub->FireChangeEvent(false);
        auto popupRenderContext = popupNode->GetRenderContext();
        CHECK_NULL_VOID(popupRenderContext);
        popupRenderContext->UpdateChainedTransition(nullptr);
        auto accessibilityProperty = popupNode->GetAccessibilityProperty<BubbleAccessibilityProperty>();
        CHECK_NULL_VOID(accessibilityProperty);
        accessibilityProperty->SetShowedState(0);
        popupNode->OnAccessibilityEvent(
            AccessibilityEventType::PAGE_CLOSE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
        overlayManager->RemoveChildWithService(rootNode, popupNode);
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        if (popupNodeIsInMap) {
            overlayManager->ErasePopupInfo(params.targetId);
        }
        if (params.isShowInSubWindow) {
            auto subwindow = SubwindowManager::GetInstance();
            subwindow->DeleteHotAreas(Container::CurrentId(), popupNode->GetId(), SubwindowType::TYPE_POPUP);
            subwindow->HideSubWindowNG();
        }
        popupPattern->CallDoubleBindCallback("false");
    };
}

bool FireChangeEventOnOverlayBridge(const RefPtr<BubbleEventHub>& popupEventHub)
{
    CHECK_NULL_RETURN(popupEventHub, false);
    popupEventHub->FireChangeEvent(false);
    return true;
}

void StartExitAnimation(const RefPtr<BubblePattern>& popupPattern, const RefPtr<FrameNode>& popupNode,
    const std::function<void()>& finish)
{
    if (popupPattern->GetHasTransition()) {
        auto popupRenderContext = popupNode->GetRenderContext();
        if (popupRenderContext && !popupRenderContext->HasDisappearTransition()) {
            if (finish) {
                finish();
            }
        } else {
            popupPattern->StartExitingTransitionEffects(popupNode, finish);
        }
    } else {
        popupPattern->StartExitingAnimation(finish);
    }
}

void UpdateColor(const RefPtr<BubblePattern>& pattern, int32_t typeAsInt, const Color& color)
{
    CHECK_NULL_VOID(pattern);
    auto type = static_cast<PopupType>(typeAsInt);
    switch (type) {
        case POPUPTYPE_TEXTCOLOR:
            pattern->UpdateBubbleText(color);
            break;
        case POPUPTYPE_POPUPCOLOR:
            pattern->UpdateBubbleBackGroundColor(color);
            break;
        case POPUPTYPE_MASKCOLOR:
            pattern->UpdateMaskColor(color);
            break;
        default:
            break;
    }
}

void ParseOptionsDimension(const RefPtr<BubblePattern>& pattern,
    const RefPtr<ResourceObject>& dimensionResObj, int32_t typeAsInt)
{
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(dimensionResObj);
    auto type = static_cast<PopupOptionsType>(typeAsInt);
    CalcDimension dimension;
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    switch (type) {
        case POPUP_OPTIONTYPE_ARROWWIDTH:
            if (ResourceParseUtils::ParseResDimensionVp(dimensionResObj, dimension)) {
                pattern->UpdateArrowWidth(dimension);
            }
            return;
        case POPUP_OPTIONTYPE_ARROWHEIGHT:
            if (ResourceParseUtils::ParseResDimensionVp(dimensionResObj, dimension)) {
                pattern->UpdateArrowHeight(dimension);
            }
            return;
        case POPUP_OPTIONTYPE_OUTLINEWIDTH:
            if (ResourceParseUtils::ParseResDimensionVp(dimensionResObj, dimension)) {
                pattern->SetOutlineWidth(dimension);
                host->MarkModifyDone();
                host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
            }
            return;
        case POPUP_OPTIONTYPE_BORDERWIDTH:
            if (ResourceParseUtils::ParseResDimensionVp(dimensionResObj, dimension)) {
                pattern->SetInnerBorderWidth(dimension);
                host->MarkModifyDone();
                host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
            }
            return;
        case POPUP_OPTIONTYPE_WIDTH:
            if (ResourceParseUtils::ParseResDimensionVpNG(dimensionResObj, dimension)) {
                pattern->UpdateWidth(dimension);
            }
            return;
        case POPUP_OPTIONTYPE_RADIUS:
            if (ResourceParseUtils::ParseResDimensionVpNG(dimensionResObj, dimension)) {
                pattern->UpdateRadius(dimension);
            }
            return;
        default:
            return;
    }
}

void AddBubbleGradientResObj(const RefPtr<BubblePattern>& pattern, const std::string& key,
    const RefPtr<ResourceObject>& resObj, uint32_t index, bool isOutlineGradient)
{
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [index, key, isOutlineGradient, weak = AceType::WeakClaim(AceType::RawPtr(pattern))](
                            const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(resObj);
        std::string color = pattern->GetResCacheMapByKey(key);
        Color result;
        if (color.empty()) {
            ResourceParseUtils::ParseResColor(resObj, result);
            pattern->AddResCache(key, result.ColorToString());
        } else {
            result = Color::FromString(color);
        }
        pattern->UpdateBubbleGradient(index, result, isOutlineGradient);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void AddBubbleMaskResObj(const RefPtr<BubblePattern>& pattern, const std::string& key,
    const RefPtr<ResourceObject>& maskResObj)
{
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(maskResObj);
    auto&& updateFunc = [pattern, key](const RefPtr<ResourceObject>& maskResObj) {
        std::string mask = pattern->GetResCacheMapByKey(key);
        bool result;
        if (mask.empty()) {
            ResourceParseUtils::ParseResBool(maskResObj, result);
            std::string maskValue = result ? "true" : "false";
            pattern->AddResCache(key, maskValue);
        } else {
            result = mask == "true";
        }
        pattern->UpdateMask(result);
    };
    updateFunc(maskResObj);
    pattern->AddResObj(key, maskResObj, std::move(updateFunc));
}

void HideCustomPopupsIteration(OverlayManager* overlayManager,
    const std::unordered_map<int32_t, PopupInfo>& popupMap)
{
    CHECK_NULL_VOID(overlayManager);
    for (const auto& popup : popupMap) {
        auto popupInfoCopy = popup.second;
        if (popupInfoCopy.isCurrentOnShow && popupInfoCopy.target.Upgrade()) {
            auto targetNodeId = popupInfoCopy.target.Upgrade()->GetId();
            auto popupNode = popupInfoCopy.popupNode;
            CHECK_NULL_VOID(popupNode);
            ACE_UINODE_TRACE(popupNode);
            auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
            CHECK_NULL_VOID(layoutProp);
            auto paintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
            CHECK_NULL_VOID(paintProperty);
            auto isTypeWithOption = paintProperty->GetPrimaryButtonShow().value_or(false);
            
            auto popupEventHub = popupNode->GetEventHub<BubbleEventHub>();
            CHECK_NULL_VOID(popupEventHub);
            popupEventHub->FireChangeEvent(false);
            // if use popup with option, skip
            if (isTypeWithOption) {
                continue;
            }
            popupInfoCopy.markNeedUpdate = true;
            auto isShowInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
            if (isShowInSubWindow) {
                auto pipelineContext = popupNode->GetContextRefPtr();
                CHECK_NULL_VOID(pipelineContext);
                auto containerId = pipelineContext->GetInstanceId();
                SubwindowManager::GetInstance()->HidePopupNG(targetNodeId, containerId);
            } else {
                overlayManager->HidePopup(targetNodeId, popupInfoCopy);
            }
        }
    }
}

void HideAllPopupsIteration(OverlayManager* overlayManager,
    const std::unordered_map<int32_t, PopupInfo>& popupMap)
{
    CHECK_NULL_VOID(overlayManager);
    for (const auto& popup : popupMap) {
        auto popupInfoCopy = popup.second;
        if (popupInfoCopy.isCurrentOnShow && popupInfoCopy.target.Upgrade()) {
            auto targetNodeId = popupInfoCopy.target.Upgrade()->GetId();
            auto popupNode = popupInfoCopy.popupNode;
            CHECK_NULL_VOID(popupNode);
            ACE_UINODE_TRACE(popupNode);
            auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
            CHECK_NULL_VOID(layoutProp);
            popupInfoCopy.markNeedUpdate = true;
            auto showInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
            if (showInSubWindow) {
                auto pipelineContext = popupNode->GetContextRefPtr();
                CHECK_NULL_VOID(pipelineContext);
                auto containerId = pipelineContext->GetInstanceId();
                SubwindowManager::GetInstance()->HidePopupNG(targetNodeId, containerId);
            } else {
                overlayManager->HidePopup(targetNodeId, popupInfoCopy);
            }
        }
    }
}

void HideAllPopupsWithoutAnimationIteration(OverlayManager* overlayManager,
    const std::unordered_map<int32_t, PopupInfo>& popupMap)
{
    CHECK_NULL_VOID(overlayManager);
    for (const auto& popup : popupMap) {
        auto targetId = popup.first;
        auto popupNode = popup.second.popupNode;
        CHECK_NULL_CONTINUE(popupNode);
        ACE_UINODE_TRACE(popupNode);
        auto popupPattern = popupNode->GetPattern<BubblePattern>();
        CHECK_NULL_CONTINUE(popupPattern);
        popupPattern->SetTransitionStatus(TransitionStatus::INVISIABLE);
        popupPattern->CallDoubleBindCallback("false");
        auto popupEventHub = popupNode->GetEventHub<BubbleEventHub>();
        CHECK_NULL_CONTINUE(popupEventHub);
        popupEventHub->FireChangeEvent(false);
        auto popupRenderContext = popupNode->GetRenderContext();
        CHECK_NULL_CONTINUE(popupRenderContext);
        popupRenderContext->UpdateChainedTransition(nullptr);
        overlayManager->ErasePopup(targetId);
    }
}

RefPtr<FrameNode> CreateBubbleNode(const std::string& tag, int32_t targetId,
    const RefPtr<PopupParam>& param, const RefPtr<SpanString>& spanString)
{
    CHECK_NULL_RETURN(param, nullptr);
    return BubbleView::CreateBubbleNode(tag, targetId, param, spanString);
}

RefPtr<FrameNode> CreatePopupNode(const std::string& targetTag, int32_t targetId,
    const RefPtr<UINode>& customNode, const RefPtr<PopupParam>& param, bool isUseCustom)
{
    if (!isUseCustom) {
        return BubbleView::CreateBubbleNode(targetTag, targetId, param);
    }
    CHECK_NULL_RETURN(customNode, nullptr);
    return BubbleView::CreateCustomBubbleNode(targetTag, targetId, customNode, param);
}

void UpdatePopupParam(int32_t popupId, const RefPtr<PopupParam>& param,
    const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_VOID(param);
    BubbleView::UpdatePopupParam(popupId, param, targetNode);
}

void UpdatePopupNode(int32_t popupId, const RefPtr<PopupParam>& param,
    const RefPtr<FrameNode>& targetNode, bool isUseCustom)
{
    if (!isUseCustom) {
        BubbleView::UpdatePopupParam(popupId, param, targetNode);
    } else {
        BubbleView::UpdateCustomPopupParam(popupId, param);
    }
}

void ResetBubbleProperty(int32_t popupId)
{
    BubbleView::ResetBubbleProperty(popupId);
}

PopupInfo GetPopupInfoWithCustomNode(const RefPtr<UINode>& customNode)
{
    return BubbleView::GetPopupInfoWithCustomNode(customNode);
}

PopupInfo GetPopupInfoWithTargetId(const RefPtr<UINode>& customNode, const int32_t targetId)
{
    return BubbleView::GetPopupInfoWithTargetId(customNode, targetId);
}

RefPtr<OverlayManager> GetPopupOverlayManager(const RefPtr<UINode>& customNode, const int32_t targetId)
{
    return BubbleView::GetPopupOverlayManager(customNode, targetId);
}

bool PopupInteractiveDismiss(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, false);
    return !pattern->GetInteractiveDismiss();
}

void SetCustomNode(const RefPtr<BubblePattern>& pattern, const WeakPtr<UINode>& customNode)
{
    CHECK_NULL_VOID(pattern);
    pattern->SetCustomNode(customNode);
}

void SetMouseOffset(const RefPtr<BubblePattern>& pattern, const Offset& offset)
{
    CHECK_NULL_VOID(pattern);
    pattern->SetMouseOffset(offset);
}

int32_t FinishOpenPopup(const RefPtr<UINode>& customNode, const int32_t targetId)
{
    auto popupInfo = GetPopupInfoWithTargetId(customNode, targetId);
    if (!popupInfo.popupNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The popupNode of popup is null.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    auto popupPattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    if (!popupPattern) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The popupPattern does not exist.");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    SetCustomNode(popupPattern, AceType::WeakClaim(AceType::RawPtr(customNode)));
    return ERROR_CODE_NO_ERROR;
}

void CleanupPopupInSubWindowElseBridge(const RefPtr<BubblePattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    pattern->SetTransitionStatus(TransitionStatus::INVISIABLE);
    pattern->CallDoubleBindCallback("false");
}
} // namespace

namespace InnerModifier {
const ArkUIBubbleInnerModifier* GetBubbleInnerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIBubbleInnerModifier modifier = {
        .isOnShow = IsOnShow,
        .getHasTransition = GetHasTransition,
        .getShowInSubWindow = GetShowInSubWindow,
        .getPrimaryButtonShow = GetPrimaryButtonShow,
        .getAutoCancel = GetAutoCancel,
        .resetFocusState = ResetFocusState,
        .startEnteringAnimationOrTransition = StartEnteringAnimationOrTransition,
        .getPopupParam = GetPopupParam,
        .setPopupParam = SetPopupParam,
        .registerDoubleBindCallback = RegisterDoubleBindCallback,
        .setIsTipsAppearing = SetIsTipsAppearing,
        .addPipelineCallBack = AddPipelineCallBack,
        .setInteractiveDismiss = SetInteractiveDismiss,
        .updateOnWillDismiss = UpdateOnWillDismiss,
        .fireChangeEvent = FireChangeEvent,
        .isContentUpdatePopup = IsContentUpdatePopupBridge,
        .setPopupHotAreas = SetPopupHotAreasImpl,
        .erasePopupSetup = ErasePopupSetupBridge,
        .isCustomNodeMatch = IsCustomNodeMatchBridge,
        .handleOnWillDismissCleanup = HandleOnWillDismissCleanupBridge,
        .getPopupCustomNode = GetPopupCustomNodeBridge,
        .callOnWillDismissWithCheck = CallOnWillDismissWithCheckBridge,
        .checkAndSetExitingStatus = CheckAndSetExitingStatusBridge,
        .createHidePopupOnFinish = CreateHidePopupOnFinish,
        .fireChangeEventOnOverlay = FireChangeEventOnOverlayBridge,
        .startExitAnimation = StartExitAnimation,
        .hideCustomPopupsIteration = HideCustomPopupsIteration,
        .hideAllPopupsIteration = HideAllPopupsIteration,
        .hideAllPopupsWithoutAnimationIteration = HideAllPopupsWithoutAnimationIteration,
        .popupInteractiveDismiss = PopupInteractiveDismiss,
        .createBubbleNode = CreateBubbleNode,
        .createPopupNode = CreatePopupNode,
        .updatePopupParam = UpdatePopupParam,
        .updatePopupNode = UpdatePopupNode,
        .getPopupInfoWithCustomNode = GetPopupInfoWithCustomNode,
        .getPopupInfoWithTargetId = GetPopupInfoWithTargetId,
        .getPopupOverlayManager = GetPopupOverlayManager,
        .resetBubbleProperty = ResetBubbleProperty,
        .setCustomNode = SetCustomNode,
        .setMouseOffset = SetMouseOffset,
        .updateColor = UpdateColor,
        .parseOptionsDimension = ParseOptionsDimension,
        .finishOpenPopup = FinishOpenPopup,
        .addBubbleGradientResObj = AddBubbleGradientResObj,
        .addBubbleMaskResObj = AddBubbleMaskResObj,
        .cleanupPopupInSubWindowElse = CleanupPopupInSubWindowElseBridge,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace InnerModifier
} // namespace OHOS::Ace::NG