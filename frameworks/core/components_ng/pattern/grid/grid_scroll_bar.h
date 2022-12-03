/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_SCROLL_BAR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_SCROLL_BAR_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GridScrollBar {
public:
    explicit GridScrollBar(const RefPtr<GridPattern>& pattern) : pattern_(pattern) {}
    ~GridScrollBar();

    void CreateInnerBar();
    void CreateBarProxy(const RefPtr<NG::ScrollBarProxy>& scrollBarProxy);
    void UpdateBarOffset(const RefPtr<LayoutWrapper>& layoutWrapper);

    float GetEstimatedHeight()
    {
        return estimatedHeight_;
    }
    float GetOffset()
    {
        return offset_;
    }
    RefPtr<ScrollBar>& GetInnerScrollBar()
    {
        return innerBar_;
    }
    bool OnInnerBarScroll(float offset);

private:
    void OnInnerBarTouch(const TouchEventInfo& info);
    bool SetInnerBarProperties(const RefPtr<GridPattern>& gridPattern);

    WeakPtr<GridPattern> pattern_;
    RefPtr<ScrollBar> innerBar_;
    RefPtr<NG::ScrollBarProxy> scrollBarProxy_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<ScrollableEvent> scrollEvent_;

    float estimatedHeight_ = 0.0f;
    float offset_ = 0.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_SCROLL_BAR_H
