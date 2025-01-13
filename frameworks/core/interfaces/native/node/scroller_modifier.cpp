/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/scroller_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"

namespace OHOS::Ace::NG {

ArkUINodeHandle GetScroller(ArkUINodeHandle node, ArkUINodeHandle proxy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = ScrollModelNG::GetOrCreateController(frameNode);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(controller));
}

ArkUINodeHandle GetScrollerProxy(ArkUINodeHandle node)
{
    TAG_LOGE(AceLogTag::ACE_SCROLL, "GetScrollerProxy not implemented");
    return node;
}

void SetScrollToIndex(ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Bool smooth,
    ArkUIScrollAlign align)
{
    auto* scrollController = reinterpret_cast<NG::ScrollableController*>(node);
    CHECK_NULL_VOID(scrollController);
    scrollController->ScrollToIndex(index, smooth, static_cast<ScrollAlign>(align), std::nullopt);
}

void ScrollBy(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32* units)
{
    auto* scrollController = reinterpret_cast<NG::ScrollableController*>(node);
    CHECK_NULL_VOID(scrollController);
    Dimension deltaX(values[0], static_cast<OHOS::Ace::DimensionUnit>(units[0]));
    Dimension deltaY(values[1], static_cast<OHOS::Ace::DimensionUnit>(units[1]));
    scrollController->ScrollBy(deltaX.Value(), deltaY.Value(), false);
}

void GetCurrentOffset(ArkUINodeHandle node, ArkUI_Float32* out)
{
    auto* scrollController = reinterpret_cast<NG::ScrollableController*>(node);
    CHECK_NULL_VOID(scrollController);
    auto offset = scrollController->GetCurrentOffset();
    out[0] = offset.GetX();
    out[1] = offset.GetY();
}

void ScrollTo(ArkUINodeHandle node, ArkUI_Float32* xOffsetArray, ArkUI_Float32* yOffsetArray,
    ArkUI_Bool animation, const struct ArkUIScrollerAnimationType* animationType)
{
    auto* controller = reinterpret_cast<NG::ScrollableController*>(node);
    CHECK_NULL_VOID(controller);
    Dimension xOffset(xOffsetArray[0], static_cast<OHOS::Ace::DimensionUnit>(xOffsetArray[1]));
    Dimension yOffset(yOffsetArray[0], static_cast<OHOS::Ace::DimensionUnit>(yOffsetArray[1]));
    float duration = animationType->duration;
    RefPtr<Curve> curve = Framework::CreateCurve(Framework::CurveIntToString(animationType->curve), false);
    auto direction = controller->GetScrollDirection();
    auto position = direction == Axis::VERTICAL ? yOffset : xOffset;
    controller->AnimateTo(position, duration, curve, animation);
}

namespace NodeModifier {
const ArkUIScrollerModifier* GetScrollerModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIScrollerModifier modifier = {
        .getScroller = GetScroller,
        .getScrollerProxy = GetScrollerProxy,
        .scrollToIndex = SetScrollToIndex,
        .scrollBy = ScrollBy,
        .getCurrentOffset = GetCurrentOffset,
        .scrollTo = ScrollTo,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}

const CJUIScrollerModifier* GetCJUIScrollerModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIScrollerModifier modifier = {
        .getScroller = GetScroller,
        .getScrollerProxy = GetScrollerProxy,
        .scrollToIndex = SetScrollToIndex,
        .scrollBy = ScrollBy,
        .getCurrentOffset = GetCurrentOffset,
        .scrollTo = ScrollTo,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}
}
}
