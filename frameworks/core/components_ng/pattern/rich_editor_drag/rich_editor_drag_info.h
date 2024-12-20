/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_INFO_H

#include <cstdint>
#include <optional>
#include <functional>

#include "base/geometry/ng/rect_t.h"

namespace OHOS::Ace::NG {
struct TextDragInfo {
    std::optional<Color> handleColor;
    std::optional<Color> selectedBackgroundColor;
    RectF firstHandle;
    RectF secondHandle;
    float maxSelectedWidth = 0.0f;
    bool isInline = true;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_INFO_H
