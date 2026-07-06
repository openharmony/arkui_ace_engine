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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_VIEW_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_VIEW_INNER_MODIFIER_H

#include <functional>
#include <string>

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/sheet/sheet_style.h"

namespace OHOS::Ace::NG {
class FrameNode;
class UINode;

struct ArkUISheetViewInnerModifier {
    RefPtr<FrameNode> (*createSheetPage)(int32_t targetId, std::string targetTag, RefPtr<UINode> builder,
        RefPtr<FrameNode> titleBuilder, std::function<void(const std::string&)>&& callback, SheetStyle& sheetStyle);
    RefPtr<FrameNode> (*createSheetMaskShowInSubwindow)(const RefPtr<FrameNode>& sheetPageNode,
        const RefPtr<FrameNode>& sheetWrapperNode, const RefPtr<FrameNode>& targetNode, SheetStyle& sheetStyle);
    bool (*sheetIsSingleDetents)(const SheetStyle& sheetStyle);
};

namespace InnerModifier {
constexpr const char* SHEET_VIEW_INNER_MODIFIER = "sheetViewInnerModifier";
const ArkUISheetViewInnerModifier* GetSheetViewInnerModifier();
} // namespace InnerModifier
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_VIEW_INNER_MODIFIER_H
