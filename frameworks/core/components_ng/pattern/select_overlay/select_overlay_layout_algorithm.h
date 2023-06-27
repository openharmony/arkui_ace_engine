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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_OVERLAY_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_OVERLAY_LAYOUT_ALGORITHM_H

#include <optional>
#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SelectOverlayLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(SelectOverlayLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    explicit SelectOverlayLayoutAlgorithm(std::shared_ptr<SelectOverlayInfo> info, const OffsetF& defaultMenuEndOffset)
        : info_(std::move(info)), defaultMenuEndOffset_(defaultMenuEndOffset)
    {}
    ~SelectOverlayLayoutAlgorithm() override = default;

    void Layout(LayoutWrapper* layoutWrapper) override;

    static bool CheckInShowArea(const SelectOverlayInfo& info);

    const OffsetF& GetDefaultMenuEndOffset() const
    {
        return defaultMenuEndOffset_;
    }

    const std::optional<float>& GetMenuWidth() const
    {
        return menuWidth_;
    }

    bool GetHasExtensionMenu() const
    {
        return hasExtensionMenu_;
    }

private:
    OffsetF ComputeSelectMenuPosition(LayoutWrapper* layoutWrapper);
    OffsetF ComputeExtensionMenuPosition(LayoutWrapper* layoutWrapper, const OffsetF& offset);
    bool IsTextAreaSelectAll();

    std::shared_ptr<SelectOverlayInfo> info_;

    OffsetF defaultMenuEndOffset_;
    std::optional<float> menuWidth_;
    bool hasExtensionMenu_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_OVERLAY_LAYOUT_ALGORITHM_H