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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_MODEL_NG_H

#include <cstdint>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT SwiperModelNG : public OHOS::Ace::SwiperModel {
public:
    RefPtr<SwiperController> Create(bool isCreateArc = false) override;
    void SetDirection(Axis axis) override;
    void SetIndex(uint32_t index) override;
    void SetIndicatorInteractive(bool interactive) override;
    void SetAutoPlay(bool autoPlay) override;
    void SetAutoPlayInterval(uint32_t interval) override;
    void SetDuration(uint32_t duration) override;
    void SetCurve(const RefPtr<Curve>& curve) override;
    void SetLoop(bool loop) override;
    void SetEnabled(bool enabled) override;
    void SetDisableSwipe(bool disableSwipe) override;
    void SetEdgeEffect(EdgeEffect EdgeEffect) override;
    void SetDisplayMode(SwiperDisplayMode displayMode) override;
    void SetDisplayCount(int32_t displayCount) override;
    void ResetDisplayCount() override;
    void SetMinSize(const Dimension& minSize) override;
    void SetShowIndicator(bool showIndicator) override;
    void SetIndicatorType(SwiperIndicatorType indicatorType) override;
    void SetIsIndicatorCustomSize(bool isCustomSize) override;
    void SetItemSpace(const Dimension& itemSpace) override;
    void SetCachedCount(int32_t cachedCount) override;
    void SetCachedIsShown(bool isShown) override;
    void SetOnChange(std::function<void(const BaseEventInfo* info)>&& onChange) override;
    void SetOnUnselected(std::function<void(const BaseEventInfo* info)>&& onUnselected) override;
    void SetOnAnimationStart(AnimationStartEvent&& onAnimationStart) override;
    void SetOnAnimationEnd(AnimationEndEvent&& onAnimationEnd) override;
    void SetOnGestureSwipe(GestureSwipeEvent&& gestureSwipe) override;

    void SetRemoteMessageEventId(RemoteCallback&& remoteCallback) override;
    void SetOnClick(
        std::function<void(const BaseEventInfo* info, const RefPtr<V2::InspectorFunctionImpl>& impl)>&& value) override;
    void SetMainSwiperSizeWidth() override;
    void SetMainSwiperSizeHeight() override;
    void SetIndicatorStyle(const SwiperParameters& swiperParameters) override;
    void SetDotIndicatorStyle(const SwiperParameters& swiperParameters) override;
    void SetArcDotIndicatorStyle(const SwiperArcDotParameters& swiperArcDotParameters) override;
    void SetDigitIndicatorStyle(const SwiperDigitalParameters& swiperDigitalParameters) override;
    void SetPreviousMargin(const Dimension& prevMargin, bool ignoreBlank) override;
    void SetNextMargin(const Dimension& nextMargi, bool ignoreBlankn) override;
    void SetOnChangeEvent(std::function<void(const BaseEventInfo* info)>&& onChangeEvent) override;
    void SetIndicatorIsBoolean(bool isBoolean) override;
    void SetAutoPlayOptions(const SwiperAutoPlayOptions& swiperAutoPlayOptions) override;
    void SetArrowStyle(const SwiperArrowParameters& swiperArrowParameters) override;
    void SetDisplayArrow(bool displayArrow) override;
    void SetHoverShow(bool hoverShow) override;
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override;
    void SetSwipeByGroup(bool swipeByGroup) override;
    void SetCustomContentTransition(SwiperContentAnimatedTransition& transition) override;
    void SetDisableTransitionAnimation(bool isDisable) override;
    void SetOnContentDidScroll(ContentDidScrollEvent&& onContentDidScroll) override;
    void SetOnContentWillScroll(ContentWillScrollEvent&& onContentWillScroll) override;
    void SetBindIndicator(bool bind) override;
    void SetPageFlipMode(int32_t pageFlipMode) override;
    void SetDigitalCrownSensitivity(int32_t sensitivity) override;
    void SetOnSelected(std::function<void(const BaseEventInfo* info)>&& onSelected) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetIndicatorInteractive(FrameNode* frameNode, bool interactive);
    static void SetNextMargin(FrameNode* frameNode, const Dimension& nextMargin, bool ignoreBlankn = false);
    static void SetPreviousMargin(FrameNode* frameNode, const Dimension& prevMargin, bool ignoreBlankn = false);
    static void SetIndex(FrameNode* frameNode, uint32_t index);
    static void SetAutoPlayInterval(FrameNode* frameNode, uint32_t interval);
    static void SetDuration(FrameNode* frameNode, uint32_t duration);
    static void SetCachedCount(FrameNode* frameNode, int32_t cachedCount);
    static int32_t GetCachedCount(FrameNode* frameNode);
    static void SetCachedIsShown(FrameNode* frameNode, bool isShown);
    static bool GetCachedIsShown(FrameNode* frameNode);
    static void SetAutoPlay(FrameNode* frameNode, bool autoPlay);
    static void SetLoop(FrameNode* frameNode, bool loop);
    static void SetDirection(FrameNode* frameNode, Axis axis);
    static void SetDisableSwipe(FrameNode* frameNode, bool disableSwipe);
    static void SetItemSpace(FrameNode* frameNode, const Dimension& itemSpace);
    static void SetDisplayMode(FrameNode* frameNode, SwiperDisplayMode displayMode);
    static void SetEdgeEffect(FrameNode* frameNode, EdgeEffect EdgeEffect);
    static void SetMinSize(FrameNode* frameNode, const Dimension& minSize);
    static void SetDisplayCount(FrameNode* frameNode, int32_t displayCount);
    static void ResetDisplayCount(FrameNode* frameNode);
    static void SetCurve(FrameNode* frameNode, const RefPtr<Curve>& curve);
    static void SetAutoPlayOptions(FrameNode* frameNode, const SwiperAutoPlayOptions& swiperAutoPlayOptions);
    static void SetArrowStyle(FrameNode* frameNode, const SwiperArrowParameters& swiperArrowParameters);
    static void SetDisplayArrow(FrameNode* frameNode, bool displayArrow);
    static void SetHoverShow(FrameNode* frameNode, bool hoverShow);
    static void SetShowIndicator(FrameNode* frameNode, bool showIndicator);
    static void SetIndicatorIsBoolean(FrameNode* frameNode, bool isBoolean);
    static void SetDigitIndicatorStyle(FrameNode* frameNode, const SwiperDigitalParameters& swiperDigitalParameters);
    static void SetDotIndicatorStyle(FrameNode* frameNode, const SwiperParameters& swiperParameters);
    static void SetArcDotIndicatorStyle(FrameNode* frameNode, const SwiperArcDotParameters& swiperArcDotParameters);
    static void SetIndicatorType(FrameNode* frameNode, SwiperIndicatorType indicatorType);
    static void SetIsIndicatorCustomSize(FrameNode* frameNode, bool isCustomSize);
    static void SetEnabled(FrameNode* frameNode, bool enabled);
    static void SetOnChange(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& onChange);
    static void SetOnUnselected(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& onUnselected);
    static void SetOnAnimationStart(FrameNode* frameNode, AnimationStartEvent&& onAnimationStart);
    static void SetOnAnimationEnd(FrameNode* frameNode, AnimationEndEvent&& onAnimationEnd);
    static void SetOnGestureSwipe(FrameNode* frameNode, GestureSwipeEvent&& onGestureSwipe);
    static void SetNestedScroll(FrameNode* frameNode, const int32_t nestedOpt);
    static void SetSwipeByGroup(FrameNode* frameNode, bool swipeByGroup);
    static void SetBindIndicator(FrameNode* frameNode, bool bind);
    static bool GetLoop(FrameNode* frameNode);
    static bool GetAutoPlay(FrameNode* frameNode);
    static int GetIndex(FrameNode* frameNode);
    static Axis GetDirection(FrameNode* frameNode);
    static uint32_t GetDuration(FrameNode* frameNode);
    static int GetDisplayCount(FrameNode* frameNode);
    static SwiperAutoPlayOptions GetAutoPlayOptions(FrameNode* frameNode);
    static int GetAutoPlayInterval(FrameNode* frameNode);
    static RefPtr<Curve> GetCurve(FrameNode* frameNode);
    static bool GetDisableSwipe(FrameNode* frameNode);
    static float GetItemSpace(FrameNode* frameNode);
    static bool GetShowIndicator(FrameNode* frameNode);
    static int GetShowDisplayArrow(FrameNode* frameNode);
    static EdgeEffect GetEffectMode(FrameNode* frameNode);
    static int32_t GetNestedScroll(FrameNode* frameNode);

    static int32_t RealTotalCount(FrameNode* frameNode);
    static void SetSwiperToIndex(FrameNode* frameNode, int32_t index, bool useAnimation);
    static void SetSwiperToIndex(FrameNode* frameNode, int32_t index, SwiperAnimationMode animationMode);
    static void GetPreviousMargin(FrameNode* frameNode, int32_t unit, SwiperMarginOptions* options);
    static void GetNextMargin(FrameNode* frameNode, int32_t unit, SwiperMarginOptions* options);
    static std::shared_ptr<SwiperParameters> GetDotIndicator(FrameNode* frameNode);
    static int32_t GetIndicatorType(FrameNode* frameNode);
    static RefPtr<SwiperController> GetSwiperController(FrameNode* frameNode);
    static void SetOnContentDidScroll(FrameNode* frameNode, ContentDidScrollEvent&& onContentDidScroll);
    static void SetOnContentWillScroll(FrameNode* frameNode, ContentWillScrollEvent&& onContentWillScroll);
    static void SetCustomContentTransition(FrameNode* frameNode, SwiperContentAnimatedTransition& transition);
    static void SetOnSelected(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& onSelected);
    static RefPtr<SwiperController> GetOrCreateSwiperController(FrameNode* frameNode);
    static bool GetIndicatorInteractive(FrameNode* frameNode);
    static void SetPageFlipMode(FrameNode* frameNode, int32_t options);
    static int32_t GetPageFlipMode(FrameNode* frameNode);
    static int GetSwipeByGroup(FrameNode* frameNode);
    static SwiperDisplayMode GetDisplayMode(FrameNode* frameNode);
    static float GetMinSize(FrameNode* frameNode);
    static void ResetArrowStyle(FrameNode* frameNode);
    static void ResetIndicatorStyle(FrameNode* frameNode);
    static SwiperArrowParameters GetArrowStyle(FrameNode* frameNode);
    static std::shared_ptr<SwiperDigitalParameters> GetDigitIndicator(FrameNode* frameNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_MODEL_NG_H
