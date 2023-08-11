/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLL_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLL_CONTROLLER_H

#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ScrollableController : public ScrollControllerBase {
    DECLARE_ACE_TYPE(ScrollableController, ScrollControllerBase);

public:
    ScrollableController() = default;

    ~ScrollableController() override = default;

    void SetScrollPattern(const WeakPtr<ScrollablePattern>& scroll)
    {
        scroll_ = scroll;
    }

    const WeakPtr<ScrollablePattern>& GetScrollPattern()
    {
        return scroll_;
    }

    bool AnimateTo(const Dimension& position, float duration, const RefPtr<Curve>& curve, bool smooth) override;
    Offset GetCurrentOffset() const override;
    Axis GetScrollDirection() const override;
protected:
    WeakPtr<ScrollablePattern> scroll_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLL_CONTROLLER_H
