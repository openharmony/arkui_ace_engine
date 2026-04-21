/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_PROPERTIES_H

#include <functional>
#include <optional>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"

namespace OHOS::Ace {
class BaseEventInfo;
class ItemDragInfo;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class UINode;

using ScrollToIndexFunc = std::function<void(const BaseEventInfo*)>;
using ScrollBarUpdateFunc = std::function<std::pair<std::optional<float>, std::optional<float>>(int32_t, Dimension)>;
using ItemDragStartFunc = std::function<RefPtr<UINode>(const ItemDragInfo&, int32_t)>;
using ItemDragEnterFunc = std::function<void(const ItemDragInfo&)>;
using ItemDragMoveFunc = std::function<void(const ItemDragInfo&, int32_t, int32_t)>;
using ItemDragLeaveFunc = std::function<void(const ItemDragInfo&, int32_t)>;
using ItemDropFunc = std::function<void(const ItemDragInfo&, int32_t, int32_t, bool)>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_PROPERTIES_H
