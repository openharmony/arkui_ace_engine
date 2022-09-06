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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_NAVIGATOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATOR_NAVIGATOR_PATTERN_H

#include "navigator_event_hub.h"
#include "navigator_layout_algorithm.h"
#include "navigator_layout_property.h"

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class NavigatorPattern : public Pattern {
    DECLARE_ACE_TYPE(NavigatorPattern, Pattern);

public:
    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<NavigatorEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<NavigatorLayoutAlgorithm>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<NavigatorLayoutProperty>();
    }

    void OnModifyDone() override;

private:
    // in target container
    // bool useSubStage_ = false;

    EventMarker clickEventId_;
    RefPtr<TouchEventImpl> touchListener_;

    // child onClick events
    std::function<void(const ClickInfo&)> onClickWithInfo_;
    std::function<void()> onClick_;

    void SetAccessibilityClickImpl();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATOR_PATTERN_H
