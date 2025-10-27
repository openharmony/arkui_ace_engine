/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CAPIDEMO_SWIPER_COMPONENT_H
#define CAPIDEMO_SWIPER_COMPONENT_H

#include <arkui/native_node.h>

#include "components/component.h"
#include "components/node_adapter.h"

namespace ArkUICApiDemo {
class SwiperComponent : public Component {
public:
    SwiperComponent() : Component(ARKUI_NODE_SWIPER) {}
    explicit SwiperComponent(ArkUI_NodeHandle handle) : Component(handle) {}
    void SetSwiperLoop(int32_t loop);
    void SetSwiperAutoPlay(int32_t status);
    void SetSwiperPrevMigration(float migration, int32_t ignoreBlank = false);
    void SetSwiperNextMigration(float migration, int32_t ignoreBlank = false);
    void SetSwiperDisplayCount(int32_t count);
    void SetSwiperIndex(int32_t index);
    void SetSwiperVertical(int32_t vertical);
    void SetSwiperNestedScroll(int32_t nestedScroll);
    void SetSwiperEffectMode(int32_t effect);
    void SetSwiperInterval(float interval);
    void SetSwiperDirection(int32_t direction);
    void SetSwiperIndicator(ArkUI_SwiperIndicator* indicator);
    void SetSwiperToIndex(int32_t index, int32_t useAnimation = false);
    void SetSwiperDuration(float duration);
    void RegisterOnGesture(const std::function<void(ArkUI_NodeEvent* event)>& onGesture);
    void RegisterOnChange(const std::function<void(ArkUI_NodeEvent* event)>& onChange);
    void RegisterOnDidScrollContext(const std::function<void(ArkUI_NodeEvent* event)>& onDid);
    void RegisterOnAnimationStart(const std::function<void(ArkUI_NodeEvent* event)>& onStart);
    void RegisterOnAnimationEnd(const std::function<void(ArkUI_NodeEvent* event)>& onEnd);
    void OnNodeEvent(ArkUI_NodeEvent* event) override;

    std::function<void(ArkUI_NodeEvent* event)> onGesture_;
    std::function<void(ArkUI_NodeEvent* event)> onDid_;
    std::function<void(ArkUI_NodeEvent* event)> onChange_;
    std::function<void(ArkUI_NodeEvent* event)> onStart_;
    std::function<void(ArkUI_NodeEvent* event)> onEnd_;
};
} // namespace ArkUICApiDemo
#endif // CAPIDEMO_SWIPER_COMPONENT_H
