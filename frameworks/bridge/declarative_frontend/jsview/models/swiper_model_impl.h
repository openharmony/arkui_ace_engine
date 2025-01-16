/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SWIPER_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SWIPER_MODEL_IMPL_H

#include "core/components_ng/pattern/swiper/swiper_model.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT SwiperModelImpl : public OHOS::Ace::SwiperModel {
public:
    RefPtr<SwiperController> Create(bool isCreateArc = false) override;
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
    void SetMinSize(const Dimension& minSize) override {};
    void SetShowIndicator(bool showIndicator) override;
    void SetItemSpace(const Dimension& itemSpace) override;
    void SetCachedCount(int32_t cachedCount) override;
    void SetOnChange(std::function<void(const BaseEventInfo* info)>&& onChange) override;
    void SetOnAnimationStart(std::function<void(const BaseEventInfo* info)>&& onAnimationStart) override;
    void SetOnAnimationEnd(std::function<void(const BaseEventInfo* info)>&& onAnimationEnd) override;

    void SetRemoteMessageEventId(RemoteCallback&& remoteCallback) override;
    void SetOnClick(
        std::function<void(const BaseEventInfo* info, const RefPtr<V2::InspectorFunctionImpl>& impl)>&& value) override;
    void SetMainSwiperSizeWidth() override;
    void SetMainSwiperSizeHeight() override;
    void SetIndicatorStyle(const SwiperParameters& swiperParameters) override;
    void SetOnChangeEvent(std::function<void(const BaseEventInfo* info)>&& onChangeEvent) override {};
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SWIPER_MODEL_IMPL_H
