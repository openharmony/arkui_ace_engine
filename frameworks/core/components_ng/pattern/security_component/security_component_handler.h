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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_HANDLER_H
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_probe.h"
#include "location_button.h"
#include "paste_button.h"
#include "save_button.h"
#include "sec_comp_err.h"
#include "sec_comp_kit.h"
#include "ui/base/geometry/dimension.h"

namespace OHOS::Ace::NG {
struct NodeMaps {
    std::unordered_map<int32_t, std::pair<std::string, NG::RectF>> nodeId2Rect;
    std::unordered_map<int32_t, int32_t> nodeId2Zindex;
};
class SecurityComponentHandler {
public:
    static int32_t RegisterSecurityComponent(RefPtr<FrameNode>& node, int32_t& scId);
    static int32_t UpdateSecurityComponent(RefPtr<FrameNode>& node, int32_t& scId);
    static int32_t UnregisterSecurityComponent(int32_t& scId);
    static int32_t ReportSecurityComponentClickEvent(int32_t& scId,
        RefPtr<FrameNode>& node, GestureEvent& event,
        Security::SecurityComponent::OnFirstUseDialogCloseFunc&& callback,
        std::string& message);
    static int32_t ReportSecurityComponentClickEvent(int32_t& scId,
        RefPtr<FrameNode>& node, const KeyEvent& event,
        Security::SecurityComponent::OnFirstUseDialogCloseFunc&& callback);
    static bool InitButtonInfoValue(RefPtr<FrameNode>& node, OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
        const Security::SecurityComponent::SecCompType& scType, std::string& message);
    static bool InitButtonInfo(std::string& componentInfo,
        RefPtr<FrameNode>& node, Security::SecurityComponent::SecCompType& scType, std::string& message);
    static bool GetDisplayOffset(RefPtr<FrameNode>& node, double& offsetX, double& offsetY);
    static bool GetWindowRect(RefPtr<FrameNode>& node, OHOS::Security::SecurityComponent::SecCompRect& winRect);
    static OHOS::Security::SecurityComponent::SecCompUiRegister uiRegister;
    static SecurityComponentProbe probe;
    static int32_t ReportSecurityComponentClickEventInner(int32_t& scId,
        RefPtr<FrameNode>& node, Security::SecurityComponent::SecCompClickEvent& event,
        Security::SecurityComponent::OnFirstUseDialogCloseFunc&& callback, std::string& message);
    static bool IsSecurityComponentServiceExist();
    static bool LoadSecurityComponentService();
    static bool IsSystemAppCalling();
    static bool HasCustomPermissionForSecComp();

private:
    static bool CheckOpacity(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckBrightness(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckVisibility(const RefPtr<FrameNode>& node, RefPtr<LayoutProperty>& layoutProperty,
        std::string& message);
    static bool CheckBlur(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckForegroundBlurStyle(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckBlendMode(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckParentBorder(const RefPtr<FrameNode>& parentNode, const RectF& scRect, std::string& message);
    static bool GetBorderRect(const RefPtr<FrameNode>& parentNode, std::vector<RectF>& borderRects);
    static float GetLinearGradientBlurRatio(std::vector<std::pair<float, float>>& fractionStops);
    static bool CheckDistance(const float& deltaY, const float& radius, const float& distance,
        const int32_t& multiplier);
    static bool CheckDiagonalLinearGradientBlur(const RectF& parentRect, const RectF& rect,
        const NG::GradientDirection direction, const float& ratio, const float& radius);
    static float GetBorderRadius(RefPtr<FrameNode>& node, const NG::GradientDirection direction);
    static bool CheckLinearGradientBlur(const RefPtr<FrameNode>& parentNode, RefPtr<FrameNode>& node,
        bool& isBlured, double& blurRadius);
    static bool CheckGrayScale(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckSaturate(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckContrast(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckInvert(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckSepia(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckHueRotate(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckColorBlend(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckClipMask(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckForegroundColor(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckSphericalEffect(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckLightUpEffect(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckPixelStretchEffect(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext,
        std::string& message);
    static bool CheckForegroundEffect(const RefPtr<FrameNode>& node, std::string& message,
        const RefPtr<RenderContext>& renderContext, OHOS::Security::SecurityComponent::SecCompBase& buttonInfo);
    static bool CheckOverlayText(const RefPtr<FrameNode>& node, std::string& message,
        const RefPtr<RenderContext>& renderContext, OHOS::Security::SecurityComponent::SecCompBase& buttonInfo);
    static bool CheckRenderEffect(RefPtr<FrameNode>& node, std::string& message,
        OHOS::Security::SecurityComponent::SecCompBase& buttonInfo);
    static bool CheckOverlayNode(RefPtr<FrameNode>& parentNode, RefPtr<FrameNode>& node,
        std::string& message, OHOS::Security::SecurityComponent::SecCompBase& buttonInfo);
    static bool CheckParentNodesEffect(RefPtr<FrameNode>& node,
        OHOS::Security::SecurityComponent::SecCompBase& buttonInfo,
        std::string& message);
    static void GetVisibleRect(RefPtr<FrameNode>& node, RectF& visibleRect);
    static bool IsOutOfParentWithRound(const RectF& visibleRect, const RectF& renderRect,
        OHOS::Security::SecurityComponent::SecCompBase& buttonInfo);
    static bool GetWindowSceneWindowId(RefPtr<FrameNode>& node, uint32_t& windId);
    static bool InitBaseInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo, RefPtr<FrameNode>& node);
    static bool GetPaddingInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo, RefPtr<FrameNode>& node);
    static bool InitChildInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo, RefPtr<FrameNode>& node);
    static NG::RectF UpdateClipRect(NG::RectF& clipRect, NG::RectF& paintRect);
    static NG::RectF UpdatePaintRect(NG::RectF& paintRect, NG::RectF& clipRect);
    static bool CheckSecurityComponentStatus(const RefPtr<UINode>& root, NodeMaps& maps,
        int32_t secNodeId, std::string& message, NG::RectF& clipRect);
    static bool CheckRectIntersect(const RectF& dest, int32_t secNodeId,
        const std::unordered_map<int32_t, std::pair<std::string, NG::RectF>>& nodeId2Rect,
        std::unordered_map<int32_t, int32_t>& nodeId2Zindex, std::string& message);
    static bool IsSecurityComponent(RefPtr<FrameNode>& node);
    static bool CheckComponentCoveredStatus(int32_t secNodeId, std::string& message);
    static bool IsContextTransparent(const RefPtr<FrameNode>& frameNode);
    static bool CheckContainerTags(const RefPtr<FrameNode>& frameNode);
    static bool IsInModalPage(const RefPtr<UINode>& node);
    static int32_t GetNodeZIndex(const RefPtr<UINode>& root);
    static void UpdateAllZindex(const RefPtr<UINode>& root, std::unordered_map<int32_t, int32_t>& nodeId2Zindex);
    static void WriteButtonInfo(const RefPtr<OHOS::Ace::NG::SecurityComponentLayoutProperty>& layoutProperty,
        RefPtr<FrameNode>& node, OHOS::Security::SecurityComponent::SecCompBase& buttonInfo, std::string& message);
    static bool IsSecComponentClipped(RefPtr<FrameNode>& parentNode, RectF& visibleRect, const RectF& frameRect,
        OHOS::Security::SecurityComponent::SecCompBase& buttonInfo);
    static void CheckSecurityComponentClickEvent(const RefPtr<FrameNode>& node, std::string& message);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_HANDLER_H
