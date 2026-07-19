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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BRIDGE_INNER_MODIFIER_BUBBLE_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BRIDGE_INNER_MODIFIER_BUBBLE_INNER_MODIFIER_H

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/geometry/ng/offset_t.h"

namespace OHOS::Ace {
class Color;
class CalcDimension;
class ResourceObject;
class Offset;
class PopupParam;
class SpanString;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class BubbleEventHub;
class BubbleLayoutProperty;
class BubbleRenderProperty;
class BubblePattern;
class FrameNode;
class OverlayManager;
class UINode;
struct PopupInfo;

struct BubbleHidePopupParams {
    bool isShowInSubWindow = false;
    bool isTypeWithOption = false;
    bool isUseCustom = false;
    bool focusable = false;
    int32_t targetId = -1;
};

struct ArkUIBubbleInnerModifier {
    bool (*isOnShow)(const RefPtr<BubblePattern>& pattern);
    bool (*getHasTransition)(const RefPtr<BubblePattern>& pattern);
    bool (*getShowInSubWindow)(const RefPtr<BubbleLayoutProperty>& layoutProp);
    bool (*getPrimaryButtonShow)(const RefPtr<BubbleRenderProperty>& paintProperty);
    bool (*getAutoCancel)(const RefPtr<BubbleRenderProperty>& bubbleRenderProp);
    void (*resetFocusState)(const RefPtr<BubblePattern>& pattern);
    void (*startEnteringAnimationOrTransition)(const RefPtr<BubblePattern>& pattern,
        const RefPtr<FrameNode>& popupNode, const std::function<void()>& finish);
    RefPtr<PopupParam> (*getPopupParam)(const RefPtr<BubblePattern>& pattern);
    void (*setPopupParam)(const RefPtr<BubblePattern>& pattern, const RefPtr<PopupParam>& param);
    void (*registerDoubleBindCallback)(const RefPtr<BubblePattern>& pattern,
        const std::function<void(const std::string&)>& callback);
    void (*setIsTipsAppearing)(const RefPtr<BubblePattern>& pattern, bool isTipsAppearing);
    void (*addPipelineCallBack)(const RefPtr<BubblePattern>& pattern);
    void (*setInteractiveDismiss)(const RefPtr<BubblePattern>& pattern, bool interactiveDismiss);
    void (*updateOnWillDismiss)(const RefPtr<BubblePattern>& pattern, std::function<void(int32_t)> onWillDismiss);
    void (*fireChangeEvent)(const RefPtr<BubbleEventHub>& popupEventHub, bool isShow);
    bool (*isContentUpdatePopup)(const RefPtr<BubblePattern>& pattern);
    void (*setPopupHotAreas)(const RefPtr<BubblePattern>& pattern);
    bool (*erasePopupSetup)(const RefPtr<BubbleLayoutProperty>& layoutProp);
    bool (*isCustomNodeMatch)(const RefPtr<BubblePattern>& pattern, const RefPtr<UINode>& node);
    bool (*handleOnWillDismissCleanup)(const RefPtr<BubblePattern>& pattern, bool isForceClear);
    RefPtr<FrameNode> (*getPopupCustomNode)(const RefPtr<BubblePattern>& pattern);
    void (*callOnWillDismissWithCheck)(const RefPtr<BubblePattern>& pattern, int32_t dismissReason);
    bool (*checkAndSetExitingStatus)(const RefPtr<BubblePattern>& pattern);
    std::function<void()> (*createHidePopupOnFinish)(const RefPtr<BubblePattern>& popupPattern,
        OverlayManager* overlayManager, const BubbleHidePopupParams& params,
        const RefPtr<FrameNode>& popupNode, const RefPtr<UINode>& rootNode);
    bool (*fireChangeEventOnOverlay)(const RefPtr<BubbleEventHub>& popupEventHub);
    void (*startExitAnimation)(const RefPtr<BubblePattern>& popupPattern, const RefPtr<FrameNode>& popupNode,
        const std::function<void()>& finish);
    void (*hideCustomPopupsIteration)(OverlayManager* overlayManager,
        const std::unordered_map<int32_t, PopupInfo>& popupMap);
    void (*hideAllPopupsIteration)(OverlayManager* overlayManager,
        const std::unordered_map<int32_t, PopupInfo>& popupMap);
    void (*hideAllPopupsWithoutAnimationIteration)(OverlayManager* overlayManager,
        const std::unordered_map<int32_t, PopupInfo>& popupMap);
    bool (*popupInteractiveDismiss)(const RefPtr<BubblePattern>& pattern);
    RefPtr<FrameNode> (*createBubbleNode)(const std::string& tag, int32_t targetId,
        const RefPtr<PopupParam>& param, const RefPtr<SpanString>& spanString);
    RefPtr<FrameNode> (*createPopupNode)(const std::string& targetTag, int32_t targetId,
        const RefPtr<UINode>& customNode, const RefPtr<PopupParam>& param, bool isUseCustom);
    void (*updatePopupParam)(int32_t popupId, const RefPtr<PopupParam>& param,
        const RefPtr<FrameNode>& targetNode);
    void (*updatePopupNode)(int32_t popupId, const RefPtr<PopupParam>& param,
        const RefPtr<FrameNode>& targetNode, bool isUseCustom);
    PopupInfo (*getPopupInfoWithCustomNode)(const RefPtr<UINode>& customNode);
    PopupInfo (*getPopupInfoWithTargetId)(const RefPtr<UINode>& customNode, const int32_t targetId);
    RefPtr<OverlayManager> (*getPopupOverlayManager)(const RefPtr<UINode>& customNode, const int32_t targetId);
    void (*resetBubbleProperty)(int32_t popupId);
    void (*setCustomNode)(const RefPtr<BubblePattern>& pattern, const WeakPtr<UINode>& customNode);
    void (*setMouseOffset)(const RefPtr<BubblePattern>& pattern, const Offset& offset);
    void (*updateColor)(const RefPtr<BubblePattern>& pattern, int32_t type, const Color& color);
    void (*parseOptionsDimension)(const RefPtr<BubblePattern>& pattern,
        const RefPtr<ResourceObject>& dimensionResObj, int32_t type);
    int32_t (*finishOpenPopup)(const RefPtr<UINode>& customNode, const int32_t targetId);
    void (*addBubbleGradientResObj)(const RefPtr<BubblePattern>& pattern, const std::string& key,
        const RefPtr<ResourceObject>& resObj, uint32_t index, bool isOutlineGradient);
    void (*addBubbleMaskResObj)(const RefPtr<BubblePattern>& pattern, const std::string& key,
        const RefPtr<ResourceObject>& maskResObj);
    void (*cleanupPopupInSubWindowElse)(const RefPtr<BubblePattern>& pattern);
};

namespace InnerModifier {
const ArkUIBubbleInnerModifier* GetBubbleInnerModifier();
} // namespace InnerModifier
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BRIDGE_INNER_MODIFIER_BUBBLE_INNER_MODIFIER_H