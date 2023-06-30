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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#ifdef SECURITY_COMPONENT_ENABLE
#include "location_button.h"
#include "paste_button.h"
#include "save_button.h"
#include "sec_comp_err.h"
#include "sec_comp_kit.h"
#endif

namespace OHOS::Ace::NG {
class SecurityComponentHandler {
public:
    static int32_t RegisterSecurityComponent(RefPtr<FrameNode>& node, int32_t& scId);
    static int32_t UpdateSecurityComponent(RefPtr<FrameNode>& node, int32_t scId);
    static int32_t UnregisterSecurityComponent(int32_t scId);
    static int32_t ReportSecurityComponentClickEvent(int32_t scId, RefPtr<FrameNode>& node, GestureEvent& event);
#ifdef SECURITY_COMPONENT_ENABLE
    static OHOS::Security::SecurityComponent::SecCompUiRegister uiRegister;

private:
    static bool GetDisplayOffset(RefPtr<FrameNode>& node, double& offsetX, double& offsetY);
    static bool GetWindowRect(RefPtr<FrameNode>& node, OHOS::Security::SecurityComponent::SecCompRect& winRect);
    static bool CheckOpacity(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckBrightness(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckVisibility(const RefPtr<FrameNode>& node, RefPtr<LayoutProperty>& layoutProperty);
    static bool CheckBlur(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckGrayScale(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckSaturate(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckContrast(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckInvert(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckSepia(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckHueRotate(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckColorBlend(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckClipEdge(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckClipMask(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckForegroundColor(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckSphericalEffect(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckLightUpEffect(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckPixelStretchEffect(const RefPtr<FrameNode>& node, const RefPtr<RenderContext>& renderContext);
    static bool CheckRenderEffect(RefPtr<FrameNode>& node);
    static bool CheckParentNodesEffect(RefPtr<FrameNode>& node);
    static bool InitBaseInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo, RefPtr<FrameNode>& node);
    static bool InitChildInfo(OHOS::Security::SecurityComponent::SecCompBase& buttonInfo, RefPtr<FrameNode>& node);
    static bool InitButtonInfo(std::string& componentInfo, RefPtr<FrameNode>& node);
#endif
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_HANDLER_H
