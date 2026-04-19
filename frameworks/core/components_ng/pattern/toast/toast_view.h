/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOAST_TOAST_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOAST_TOAST_VIEW_H

#include <string>

#include "base/memory/referenced.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"

namespace OHOS::Ace {
class ThemeConstants;
class ToastTheme;
}

namespace OHOS::Ace::NG {

class ACE_EXPORT ToastView {
public:
    static RefPtr<FrameNode> CreateToastNode(const ToastInfo& toastInfo);
    static void UpdateToastNodeStyle(const RefPtr<FrameNode>& toastNode);

private:
    static void UpdateTextLayoutProperty(
        const RefPtr<FrameNode>& textNode, const std::string& message, bool isRightToLeft,
        const std::optional<Color>& textColor);
    static void UpdateToastContext(const RefPtr<FrameNode>& toastNode);
    static bool SetToastSystemMaterial(const RefPtr<FrameNode>& toastNode, const ToastInfo& toastInfo);
    static bool HandleLowEndImmersiveMaterial(
        const RefPtr<FrameNode>& toastNode,
        const ToastInfo& toastInfo,
        const RefPtr<RenderContext>& renderContext);
    static void SetLowEndImmersiveBackground(
        const RefPtr<RenderContext>& renderContext,
        const RefPtr<ThemeConstants>& themeConstants);
    static void SetLowEndImmersiveShadow(
        const RefPtr<FrameNode>& toastNode,
        const ToastInfo& toastInfo,
        const RefPtr<RenderContext>& renderContext,
        const RefPtr<PipelineContext>& pipelineContext);
    static bool HandleUserSetMaterial(
        const RefPtr<FrameNode>& toastNode,
        const ToastInfo& toastInfo,
        const RefPtr<RenderContext>& renderContext);
    static bool ApplyDefaultMaterial(
        const RefPtr<FrameNode>& toastNode,
        const ToastInfo& toastInfo,
        const RefPtr<RenderContext>& renderContext);
    static void UpdateToastBackgroundAndBlur(
        const RefPtr<RenderContext>& renderContext,
        const ToastInfo& toastInfo,
        const RefPtr<ToastTheme>& toastTheme,
        bool isUserSetMaterial);
    static bool ShouldSkipShadowUpdate(const ToastInfo& toastInfo, bool isUserSetMaterial);
    static Shadow GetToastShadow(
        const ToastInfo& toastInfo,
        const RefPtr<ToastTheme>& toastTheme,
        const RefPtr<PipelineContext>& pipelineContext);
    static void UpdateToastShadow(
        const RefPtr<RenderContext>& renderContext,
        const ToastInfo& toastInfo,
        const RefPtr<ToastTheme>& toastTheme,
        const RefPtr<PipelineContext>& pipelineContext,
        bool isUserSetMaterial);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOAST_TOAST_VIEW_H
