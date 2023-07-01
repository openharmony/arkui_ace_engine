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

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SwiperModelNG : public OHOS::Ace::SwiperModel {
public:
    RefPtr<SwiperController> Create() override;
    void SetDirection(Axis axis) override;
    void SetIndex(uint32_t index) override;
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
    void SetShowIndicator(bool showIndicator) override;
    void SetIndicatorType(SwiperIndicatorType indicatorType) override;
    void SetIsIndicatorCustomSize(bool isCustomSize) override;
    void SetItemSpace(const Dimension& itemSpace) override;
    void SetCachedCount(int32_t cachedCount) override;
    void SetOnChange(std::function<void(const BaseEventInfo* info)>&& onChange) override;
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
    void SetDigitIndicatorStyle(const SwiperDigitalParameters& swiperDigitalParameters) override;
    void SetPreviousMargin(const Dimension& prevMargin) override;
    void SetNextMargin(const Dimension& nextMargin) override;
    void SetOnChangeEvent(std::function<void(const BaseEventInfo* info)>&& onChangeEvent) override;
    void SetIndicatorIsBoolean(bool isBoolean) override;
    void SetArrowStyle(const SwiperArrowParameters& swiperArrowParameters) override;
    void SetDisplayArrow(bool displayArrow) override;
    void SetHoverShow(bool hoverShow) override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_MODEL_NG_H
