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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_WRAPPER_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_WRAPPER_INNER_MODIFIER_H

#include <cstdint>

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/sheet/sheet_style.h"

namespace OHOS::Ace::NG {
class FrameNode;
class Pattern;

struct ArkUISheetWrapperInnerModifier {
    bool (*sheetIsWrapperPattern)(const RefPtr<Pattern>& pattern);
    RefPtr<FrameNode> (*sheetWrapperGetSheetPageNode)(const RefPtr<FrameNode>& sheetWrapperNode);
    RefPtr<FrameNode> (*sheetWrapperGetSheetMaskNode)(const RefPtr<FrameNode>& sheetWrapperNode);
    int32_t (*sheetWrapperGetSubWindowId)(const RefPtr<FrameNode>& sheetWrapperNode);
    void (*sheetWrapperInitMainWindowRect)(const RefPtr<FrameNode>& sheetWrapperNode, int32_t subWindowId);
    bool (*sheetWrapperShowInUEC)(const RefPtr<FrameNode>& sheetWrapperNode);
    void (*sheetWrapperSetSheetECNode)(const RefPtr<FrameNode>& sheetWrapperNode,
        const RefPtr<FrameNode>& sheetECNode);
    RefPtr<Pattern> (*sheetWrapperCreatePattern)(int32_t targetId, const std::string& targetTag);
    void (*sheetWrapperUpdateSheetMaskResource)(const RefPtr<FrameNode>& sheetWrapperNode,
        const RefPtr<FrameNode>& sheetPageNode, SheetStyle& sheetStyle);
    void (*sheetWrapperSetSheetPageNode)(const RefPtr<FrameNode>& sheetWrapperNode,
        const RefPtr<FrameNode>& sheetPageNode);
};

namespace InnerModifier {
constexpr const char* SHEET_WRAPPER_INNER_MODIFIER = "sheetWrapperInnerModifier";
const ArkUISheetWrapperInnerModifier* GetSheetWrapperInnerModifier();
} // namespace InnerModifier
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_WRAPPER_INNER_MODIFIER_H
