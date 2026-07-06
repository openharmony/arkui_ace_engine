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

#include "core/components_ng/pattern/sheet/bridge/sheet_wrapper_inner_modifier.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/sheet/sheet_wrapper_pattern.h"

namespace OHOS::Ace::NG::InnerModifier {
namespace {
bool SheetIsWrapperPattern(const RefPtr<Pattern>& pattern)
{
    return AceType::InstanceOf<SheetWrapperPattern>(pattern);
}

RefPtr<FrameNode> SheetWrapperGetSheetPageNode(const RefPtr<FrameNode>& sheetWrapperNode)
{
    auto pattern = sheetWrapperNode->GetPattern();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto sheetWrapperPattern = AceType::DynamicCast<SheetWrapperPattern>(pattern);
    CHECK_NULL_RETURN(sheetWrapperPattern, nullptr);
    return sheetWrapperPattern->GetSheetPageNode();
}

RefPtr<FrameNode> SheetWrapperGetSheetMaskNode(const RefPtr<FrameNode>& sheetWrapperNode)
{
    CHECK_NULL_RETURN(sheetWrapperNode, nullptr);
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_RETURN(sheetWrapperPattern, nullptr);
    return sheetWrapperPattern->GetSheetMaskNode();
}

int32_t SheetWrapperGetSubWindowId(const RefPtr<FrameNode>& sheetWrapperNode)
{
    CHECK_NULL_RETURN(sheetWrapperNode, -1);
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_RETURN(sheetWrapperPattern, -1);
    return sheetWrapperPattern->GetSubWindowId();
}

void SheetWrapperInitMainWindowRect(const RefPtr<FrameNode>& sheetWrapperNode, int32_t subWindowId)
{
    CHECK_NULL_VOID(sheetWrapperNode);
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    sheetWrapperPattern->InitMainWindowRect(subWindowId);
}

bool SheetWrapperShowInUEC(const RefPtr<FrameNode>& sheetWrapperNode)
{
    CHECK_NULL_RETURN(sheetWrapperNode, false);
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_RETURN(sheetWrapperPattern, false);
    return sheetWrapperPattern->ShowInUEC();
}

void SheetWrapperSetSheetECNode(
    const RefPtr<FrameNode>& sheetWrapperNode, const RefPtr<FrameNode>& sheetECNode)
{
    CHECK_NULL_VOID(sheetWrapperNode);
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    sheetWrapperPattern->SetSheetECNode(sheetECNode);
}

RefPtr<Pattern> SheetWrapperCreatePattern(int32_t targetId, const std::string& targetTag)
{
    return AceType::MakeRefPtr<SheetWrapperPattern>(targetId, targetTag);
}

void SheetWrapperUpdateSheetMaskResource(const RefPtr<FrameNode>& sheetWrapperNode,
    const RefPtr<FrameNode>& sheetPageNode, SheetStyle& sheetStyle)
{
    CHECK_NULL_VOID(sheetWrapperNode);
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    sheetWrapperPattern->UpdateSheetMaskResource(sheetWrapperNode, sheetPageNode, sheetStyle);
}

void SheetWrapperSetSheetPageNode(const RefPtr<FrameNode>& sheetWrapperNode,
    const RefPtr<FrameNode>& sheetPageNode)
{
    CHECK_NULL_VOID(sheetWrapperNode);
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    sheetWrapperPattern->SetSheetPageNode(sheetPageNode);
}
} // namespace

const ArkUISheetWrapperInnerModifier* GetSheetWrapperInnerModifier()
{
    static const ArkUISheetWrapperInnerModifier modifier = {
        .sheetIsWrapperPattern = SheetIsWrapperPattern,
        .sheetWrapperGetSheetPageNode = SheetWrapperGetSheetPageNode,
        .sheetWrapperGetSheetMaskNode = SheetWrapperGetSheetMaskNode,
        .sheetWrapperGetSubWindowId = SheetWrapperGetSubWindowId,
        .sheetWrapperInitMainWindowRect = SheetWrapperInitMainWindowRect,
        .sheetWrapperShowInUEC = SheetWrapperShowInUEC,
        .sheetWrapperSetSheetECNode = SheetWrapperSetSheetECNode,
        .sheetWrapperCreatePattern = SheetWrapperCreatePattern,
        .sheetWrapperUpdateSheetMaskResource = SheetWrapperUpdateSheetMaskResource,
        .sheetWrapperSetSheetPageNode = SheetWrapperSetSheetPageNode,
    };
    return &modifier;
}
} // namespace OHOS::Ace::NG::InnerModifier
