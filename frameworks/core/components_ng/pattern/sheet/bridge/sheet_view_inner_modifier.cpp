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

#include "core/components_ng/pattern/sheet/bridge/sheet_view_inner_modifier.h"

#include "core/components_ng/pattern/sheet/sheet_view.h"

namespace OHOS::Ace::NG::InnerModifier {
namespace {
RefPtr<FrameNode> CreateSheetPage(int32_t targetId, std::string targetTag, RefPtr<UINode> builder,
    RefPtr<FrameNode> titleBuilder, std::function<void(const std::string&)>&& callback, SheetStyle& sheetStyle)
{
    return SheetView::CreateSheetPage(
        targetId, std::move(targetTag), builder, titleBuilder, std::move(callback), sheetStyle);
}

RefPtr<FrameNode> CreateSheetMaskShowInSubwindow(const RefPtr<FrameNode>& sheetPageNode,
    const RefPtr<FrameNode>& sheetWrapperNode, const RefPtr<FrameNode>& targetNode, SheetStyle& sheetStyle)
{
    return SheetView::CreateSheetMaskShowInSubwindow(sheetPageNode, sheetWrapperNode, targetNode, sheetStyle);
}

bool SheetIsSingleDetents(const SheetStyle& sheetStyle)
{
    return SheetView::IsSingleDetents(sheetStyle);
}
} // namespace

const ArkUISheetViewInnerModifier* GetSheetViewInnerModifier()
{
    static const ArkUISheetViewInnerModifier modifier = {
        .createSheetPage = CreateSheetPage,
        .createSheetMaskShowInSubwindow = CreateSheetMaskShowInSubwindow,
        .sheetIsSingleDetents = SheetIsSingleDetents,
    };
    return &modifier;
}
} // namespace OHOS::Ace::NG::InnerModifier
