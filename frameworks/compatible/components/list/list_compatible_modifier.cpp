/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "compatible/components/list/list_compatible_modifier.h"

#include "compatible/components/list/dom_list.h"
#include "compatible/components/list/render_list.h"
#include "compatible/components/list_v2/list_component.h"
#include "compatible/components/list_v2/render_list.h"
#include "core/components/scroll/render_scroll.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace::ListCompatibleModifier {
namespace {
OHOS::Ace::Offset GetCurrentOffset(OHOS::Ace::RefPtr<OHOS::Ace::Framework::DOMList> list)
{
    return list->GetCurrentOffset();
}
void ScrollToMethod(OHOS::Ace::RefPtr<OHOS::Ace::Framework::DOMList> list, int32_t index)
{
    list->ScrollToMethod(index);
}
double CalculateItemPositionReturn(
    OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, int32_t index, OHOS::Ace::ScrollType type)
{
    return renderList->CalculateItemPosition(index, type);
}
void CalculateItemPosition(OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double targetPos)
{
    renderList->CalculateItemPosition(targetPos);
}
void BuildNextItem(OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double start, double end,
    OHOS::Ace::Offset position, OHOS::Ace::Size viewPort)
{
    renderList->BuildNextItem(start, end, position, viewPort);
}
void ResetLayoutRange(OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double head, double tail,
    OHOS::Ace::Offset position, OHOS::Ace::Size viewport)
{
    renderList->ResetLayoutRange(head, tail, position, viewport);
}
OHOS::Ace::RefPtr<OHOS::Ace::RenderNode> GetChildByIndex(
    OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, int32_t index)
{
    return renderList->GetChildByIndex(index);
}
void NotifyDragStart(OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double startPosition)
{
    renderList->NotifyDragStart(startPosition);
}
void NotifyDragUpdate(OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double dragOffset)
{
    renderList->NotifyDragUpdate(dragOffset);
}
void NotifyScrollOver(
    OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double velocity, bool isCrashTop, bool isCrashBottom)
{
    renderList->NotifyScrollOver(velocity, isCrashTop, isCrashBottom);
}
int32_t CalculateInsertIndex(OHOS::Ace::RefPtr<OHOS::Ace::V2::RenderList> renderList,
    const OHOS::Ace::GestureEvent& info, OHOS::Ace::Size selectedItemSize)
{
    return renderList->CalculateInsertIndex(renderList, info, selectedItemSize);
}
size_t CalculateSelectedIndex(OHOS::Ace::RefPtr<OHOS::Ace::V2::RenderList> renderList,
    const OHOS::Ace::GestureEvent& info, OHOS::Ace::Size& selectedItemSize)
{
    return renderList->CalculateSelectedIndex(renderList, info, selectedItemSize);
}
OHOS::Ace::RefPtr<OHOS::Ace::V2::ListComponent> MakeV2ListComponent()
{
    return AceType::MakeRefPtr<OHOS::Ace::V2::ListComponent>();
}
}
const ArkUIListCompatibleModifier* GetListCompatibleModifier()
{
    static const ArkUIListCompatibleModifier instance = {
        .getCurrentOffset = GetCurrentOffset,
        .scrollToMethod = ScrollToMethod,
        .calculateItemPositionReturn = CalculateItemPositionReturn,
        .calculateItemPosition = CalculateItemPosition,
        .buildNextItem = BuildNextItem,
        .resetLayoutRange = ResetLayoutRange,
        .getChildByIndex = GetChildByIndex,
        .notifyDragStart = NotifyDragStart,
        .notifyDragUpdate = NotifyDragUpdate,
        .notifyScrollOver = NotifyScrollOver,
        .calculateInsertIndex = CalculateInsertIndex,
        .calculateSelectedIndex = CalculateSelectedIndex,
        .makeV2ListComponent = MakeV2ListComponent,
    };
    return &instance;
}
} // OHOS::Ace::ListCompatibleModifier