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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_VIEW_LAZY_LAYOUT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_VIEW_LAZY_LAYOUT_PATTERN_H

#include <memory>
#include <optional>

#include "core/components_ng/pattern/lazy_layout/lazy_layout_offset.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT LazyLayoutPattern : public Pattern {
    DECLARE_ACE_TYPE(LazyLayoutPattern, Pattern);
public:
    virtual AdjustOffset GetAdjustOffset() const = 0;
    virtual AdjustOffset GetAndResetAdjustOffset() = 0;
    virtual bool HasStickyHeader() const
    {
        return false;
    }

    // LazyColumnLayout publishes handoff gaps, defers mid-layout invalidation, and clears the state on detach.
    void PublishNextStickyHeaderGap(const std::optional<float>& gap);

    const std::optional<float>& GetNextStickyHeaderGap() const
    {
        return nextStickyHeaderGap_;
    }

    void NotifyParentOnStickyHeaderChange();

    void OnDetachFromMainTree() override;

protected:
    void DumpStickyHeaderHandoffInfo() const;
    void DumpStickyHeaderHandoffInfo(std::unique_ptr<JsonValue>& json) const;

private:
    bool SetNextStickyHeaderGap(const std::optional<float>& gap);

    std::optional<float> nextStickyHeaderGap_;
    std::optional<bool> lastNotifiedHasStickyHeader_;
};
}
#endif
