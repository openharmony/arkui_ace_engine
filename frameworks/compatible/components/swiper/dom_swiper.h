/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SWIPER_DOM_SWIPER_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SWIPER_DOM_SWIPER_H

#include "compatible/components/swiper/swiper_component.h"
#include "frameworks/bridge/common/dom/dom_node.h"

namespace OHOS::Ace::Framework {
// swiper attribute and style constants
ACE_EXPORT extern const char DOM_INDEX[];
ACE_EXPORT extern const char DOM_SWIPER_ANIMATION_OPACITY[];
ACE_EXPORT extern const char DOM_AUTOPLAY[];
ACE_EXPORT extern const char DOM_CACHED_SIZE[];
ACE_EXPORT extern const char DOM_DISPLAY_MODE[];
ACE_EXPORT extern const char DOM_DISPLAY_MODE_AUTO_LINEAR[];
ACE_EXPORT extern const char DOM_INTERVAL[];
ACE_EXPORT extern const char DOM_INDICATOR[];
ACE_EXPORT extern const char DOM_LOOP[];
ACE_EXPORT extern const char DOM_VERTICAL[];
ACE_EXPORT extern const char DOM_ANIMATION_CURVE[];
ACE_EXPORT extern const char DOM_INDICATOR_MASK[];
ACE_EXPORT extern const char DOM_INDICATOR_DISABLED[];
ACE_EXPORT extern const char DOM_INDICATOR_SELECTEDCOLOR[];
ACE_EXPORT extern const char DOM_INDICATOR_SIZE[];
ACE_EXPORT extern const char DOM_INDICATOR_TOP[];
ACE_EXPORT extern const char DOM_INDICATOR_LEFT[];
ACE_EXPORT extern const char DOM_INDICATOR_RIGHT[];
ACE_EXPORT extern const char DOM_INDICATOR_BOTTOM[];
ACE_EXPORT extern const char DOM_METHOD_SWIPE_TO[];
ACE_EXPORT extern const char DOM_METHOD_APPEND[];
ACE_EXPORT extern const char DOM_METHOD_SHOW_PREVIOUS[];
ACE_EXPORT extern const char DOM_METHOD_SHOW_NEXT[];
ACE_EXPORT extern const char DOM_DIGITAL_INDICATOR[];
ACE_EXPORT extern const char DOM_PREVIOUS_MARGIN[];
ACE_EXPORT extern const char DOM_NEXT_MARGIN[];
class DOMSwiper final : public DOMNode {
    DECLARE_ACE_TYPE(DOMSwiper, DOMNode);

public:
    DOMSwiper(NodeId nodeId, const std::string& nodeName);
    ~DOMSwiper() override = default;

    void InitializeStyle() override;

    RefPtr<Component> GetSpecializedComponent() override
    {
        return swiperChild_;
    }
    void AdjustSpecialParamInLiteMode() override;

protected:
    void OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot) override;
    void OnChildNodeRemoved(const RefPtr<DOMNode>& child) override;
    void PrepareSpecializedComponent() override;

private:
    RefPtr<SwiperComponent> swiperChild_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SWIPER_DOM_SWIPER_H
