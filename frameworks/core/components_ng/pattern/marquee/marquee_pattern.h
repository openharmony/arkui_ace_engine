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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_PATTERN_H

#include "base/geometry/ng/offset_t.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/marquee/marquee_accessibility_property.h"
#include "core/components_ng/pattern/marquee/marquee_event_hub.h"
#include "core/components_ng/pattern/marquee/marquee_layout_algorithm.h"
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
inline constexpr double DEFAULT_MARQUEE_SCROLL_AMOUNT = 6.0;
inline constexpr int32_t DEFAULT_MARQUEE_LOOP = -1;
using TimeCallback = std::function<void()>;

class MarqueePattern : public Pattern {
    DECLARE_ACE_TYPE(MarqueePattern, Pattern);

public:
    MarqueePattern() = default;
    ~MarqueePattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<MarqueeLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<MarqueeEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<MarqueeLayoutAlgorithm>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<MarqueeAccessibilityProperty>();
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;

    void FireStartEvent() const;
    void FireBounceEvent() const;
    void FireFinishEvent() const;

    void StartMarqueeAnimation();
    void StopMarqueeAnimation(bool stopAndStart, bool statusChanged);
    void SetTextOffset(float offsetX);
    bool lastStartStatus_ = false;
    bool statusChanged_ = false;
    bool forceStropAnimation_ = false;
    int32_t repeatCount_ = 0;
    int32_t animationId_ = 0;
    ACE_DISALLOW_COPY_AND_MOVE(MarqueePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_PATTERN_H
