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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_MODEL_STATIC_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SwiperModelStatic {
public:
    static void ParseAndSetArrowStyle(FrameNode* frameNode, const SwiperArrowParameters& swiperArrowParameters);
    static void SetDefaultArrowStyle(FrameNode* frameNode);
    static void SetArrowStyle(FrameNode* frameNode, const SwiperArrowParameters& swiperArrowParameters);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static RefPtr<SwiperController> GetSwiperController(FrameNode* frameNode);
    static void SetIndex(FrameNode* frameNode, uint32_t index);
    static void SetAutoPlay(FrameNode* frameNode, bool autoPlay);
    static void SetAutoPlayOptions(FrameNode* frameNode, const SwiperAutoPlayOptions& swiperAutoPlayOptions);
    static void SetAutoPlayInterval(FrameNode* frameNode, uint32_t interval);
    static void SetIndicatorIsBoolean(FrameNode* frameNode, bool isBoolean);
    static void SetDigitIndicatorStyle(FrameNode* frameNode, const SwiperDigitalParameters& swiperDigitalParameters);
    static void SetIndicatorType(FrameNode* frameNode, SwiperIndicatorType indicatorType);
    static void SetDotIndicatorStyle(FrameNode* frameNode, const SwiperParameters& swiperParameters);
    static void SetIsIndicatorCustomSize(FrameNode* frameNode, bool isCustomSize);
    static void SetShowIndicator(FrameNode* frameNode, bool showIndicator);
    static void SetLoop(FrameNode* frameNode, bool loop);
    static void SetDuration(FrameNode* frameNode, uint32_t duration);
    static void SetDirection(FrameNode* frameNode, Axis axis);
    static void SetItemSpace(FrameNode* frameNode, const Dimension& itemSpace);
    static void SetDisplayMode(FrameNode* frameNode, SwiperDisplayMode displayMode);
    static void SetCachedCount(FrameNode* frameNode, int32_t cachedCount);
    static void SetCachedIsShown(FrameNode* frameNode, bool isShown);
    static void SetEdgeEffect(FrameNode* frameNode, EdgeEffect EdgeEffect);
    static void SetDisableSwipe(FrameNode* frameNode, bool disableSwipe);
    static void SetCurve(FrameNode* frameNode, const RefPtr<Curve>& curve);
    static void SetOnChange(FrameNode* frameNode, std::function<void(int32_t index)>&& onChange);
    static void SetOnAnimationStart(FrameNode* frameNode, AnimationStartEvent&& onAnimationStart);
    static void SetOnAnimationEnd(FrameNode* frameNode, AnimationEndEvent&& onAnimationEnd);
    static void SetOnGestureSwipe(FrameNode* frameNode, GestureSwipeEvent&& onGestureSwipe);
    static void SetNestedScroll(FrameNode* frameNode, const int32_t nestedOpt);
    static void SetCustomContentTransition(FrameNode* frameNode, SwiperContentAnimatedTransition& transition);
    static void SetOnContentDidScroll(FrameNode* frameNode, ContentDidScrollEvent&& onContentDidScroll);
    static void SetIndicatorInteractive(FrameNode* frameNode, bool interactive);
    static void SetPageFlipMode(FrameNode* frameNode, int32_t options);
    static void SetHoverShow(FrameNode* frameNode, bool hoverShow);
    static void SetDisplayArrow(FrameNode* frameNode, bool displayArrow);
    static void SetSwipeByGroup(FrameNode* frameNode, bool swipeByGroup);
    static void SetDisplayCount(FrameNode* frameNode, int32_t displayCount);
    static void ResetDisplayCount(FrameNode* frameNode);
    static void SetMinSize(FrameNode* frameNode, const Dimension& minSize);
    static void SetPreviousMargin(FrameNode* frameNode, const Dimension& prevMargin,
        const std::optional<bool> &ignoreBlank = false);
    static void SetNextMargin(FrameNode* frameNode, const Dimension& nextMargin,
        const std::optional<bool> &ignoreBlank = false);
    static void SetOnChangeEvent(FrameNode* frameNode,
        std::function<void(const BaseEventInfo* info)>&& onChangeEvent);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_MODEL_STATIC_H