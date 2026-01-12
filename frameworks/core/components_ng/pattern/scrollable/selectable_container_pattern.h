/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_CONTAINER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_CONTAINER_EVENT_HUB_H

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {

enum class PreviewBadgeMode {
    NO_BADGE = 0,
    AUTO,
    USER_SET
};

struct PreviewBadge {
    PreviewBadgeMode mode = PreviewBadgeMode::AUTO;
    int32_t count;
};
using GetPreviewBadge = std::function<PreviewBadge()>;
struct EditModeOptions {
    bool enableGatherSelectedItemsAnimation = false;
    GetPreviewBadge getPreviewBadge;
};

class SelectableContainerPattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(SelectableContainerPattern, ScrollablePattern);

public:
    SelectableContainerPattern() = default;
    ~SelectableContainerPattern() override = default;
    virtual std::vector<RefPtr<FrameNode>> GetVisibleSelectedItems() = 0;
    void SetEditModeOptions(const EditModeOptions& editModeOptions)
    {
        editModeOptions_ = editModeOptions;
    }

    EditModeOptions GetEditModeOptions() const
    {
        return editModeOptions_;
    }

private:
    EditModeOptions editModeOptions_;
};
} // namespace OHOS::Ace::NG

#endif