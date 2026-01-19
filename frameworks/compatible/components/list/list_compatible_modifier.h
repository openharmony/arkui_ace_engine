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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_LIST_LIST_COMPATIBLE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_LIST_LIST_COMPATIBLE_MODIFIER_H

#include <cstddef>
#include <cstdint>

namespace OHOS::Ace {

namespace Framework {
class DOMList;
}
class RenderList;
class RenderNode;
class Offset;
class Size;
class GestureEvent;
enum class ScrollType;
template<class T>
class RefPtr;
namespace V2 {
class ListComponent;
class RenderList;
} // namespace V2

} // namespace OHOS::Ace

struct ArkUIListCompatibleModifier {
    OHOS::Ace::Offset (*getCurrentOffset)(OHOS::Ace::RefPtr<OHOS::Ace::Framework::DOMList> domList);
    void (*scrollToMethod)(OHOS::Ace::RefPtr<OHOS::Ace::Framework::DOMList> domList, int32_t index);
    double (*calculateItemPositionReturn)(
        OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, int32_t index, OHOS::Ace::ScrollType type);
    void (*calculateItemPosition)(OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double targetPos);
    void (*buildNextItem)(OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double start, double end,
        OHOS::Ace::Offset position, OHOS::Ace::Size viewPort);
    void (*resetLayoutRange)(OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double head, double tail,
        OHOS::Ace::Offset position, OHOS::Ace::Size viewport);
    OHOS::Ace::RefPtr<OHOS::Ace::RenderNode> (*getChildByIndex)(
        OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, int32_t index);
    void (*notifyDragStart)(OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double startPosition);
    void (*notifyDragUpdate)(OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double dragOffset);
    void (*notifyScrollOver)(
        OHOS::Ace::RefPtr<OHOS::Ace::RenderList> renderList, double velocity, bool isCrashTop, bool isCrashBottom);
    int32_t (*calculateInsertIndex)(OHOS::Ace::RefPtr<OHOS::Ace::V2::RenderList> renderList,
        const OHOS::Ace::GestureEvent& info, OHOS::Ace::Size selectedItemSize);
    size_t (*calculateSelectedIndex)(OHOS::Ace::RefPtr<OHOS::Ace::V2::RenderList> renderList,
        const OHOS::Ace::GestureEvent& info, OHOS::Ace::Size& selectedItemSize);
    OHOS::Ace::RefPtr<OHOS::Ace::V2::ListComponent> (*makeV2ListComponent)();
};

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_LIST_LIST_COMPATIBLE_MODIFIER_H