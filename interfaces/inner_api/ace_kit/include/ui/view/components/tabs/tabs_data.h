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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_COMPONENTS_TABS_TABS_DATA_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_COMPONENTS_TABS_TABS_DATA_H

namespace OHOS::Ace {

enum class LayoutStyle {
    ALWAYS_CENTER,
    ALWAYS_AVERAGE_SPLIT,
    SPACE_BETWEEN_OR_CENTER,
};

struct ScrollableBarModeOptions final {
    Dimension margin = 0.0_vp;
    std::optional<LayoutStyle> nonScrollableLayoutStyle = std::nullopt;
    bool operator==(const ScrollableBarModeOptions& option) const
    {
        return (margin == option.margin) &&
               (nonScrollableLayoutStyle.has_value() == option.nonScrollableLayoutStyle.has_value()) &&
               (nonScrollableLayoutStyle.value_or(LayoutStyle::ALWAYS_CENTER) ==
                   option.nonScrollableLayoutStyle.value_or(LayoutStyle::ALWAYS_CENTER));
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_COMPONENTS_TABS_TABS_DATA_H
