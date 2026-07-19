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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_MANAGER_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_MANAGER_INNER_MODIFIER_H

#include <cstdint>
#include <functional>

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/sheet/sheet_style.h"

namespace OHOS::Ace::NG {
class FrameNode;
class OverlayManager;
class UINode;

struct ArkUISheetManagerInnerModifier {
    RefPtr<OverlayManager> (*findPageNodeOverlay)(
        const RefPtr<FrameNode>& targetNode, bool isShow, bool isStartByUIContext);
    void (*registerDestroyCallback)(
        const RefPtr<FrameNode>& targetNode, SheetStyle& sheetStyle, int32_t containerId);
    void (*closeSheetInSubWindow)(int32_t targetId);
    bool (*removeSheetByESC)();
    int32_t (*openBindSheetByUIContext)(const RefPtr<FrameNode>& sheetContentNode,
        std::function<void()>&& titleBuildFunc, SheetStyle& sheetStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack,
        int32_t currentInstanceId, int32_t targetId);
    int32_t (*updateBindSheetByUIContext)(const RefPtr<FrameNode>& sheetContentNode, const SheetStyle& sheetStyle,
        bool isPartialUpdate, int32_t currentInstanceId);
    int32_t (*closeBindSheetByUIContext)(const RefPtr<FrameNode>& sheetContentNode, int32_t currentInstanceId);
    void (*setMaskInteractive)(const RefPtr<FrameNode>& maskNode, bool isInteractive);
    int32_t (*getDismissSheetId)();
};

namespace InnerModifier {
constexpr const char* SHEET_MANAGER_INNER_MODIFIER = "sheetManagerInnerModifier";
const ArkUISheetManagerInnerModifier* GetSheetManagerInnerModifier();
} // namespace InnerModifier
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_MANAGER_INNER_MODIFIER_H
