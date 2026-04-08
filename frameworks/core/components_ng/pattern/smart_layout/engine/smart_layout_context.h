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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_CONTEXT_H

#include "smart_layout_types.h"
#include "base/utils/macros.h"

namespace OHOS::Ace::NG {

// Forward declaration
class SmartLayoutNode;

/**
 * @brief Context for smart layout algorithm, containing layout configuration
 *
 * This class is embedded as a member of SmartLayoutNode.
 * Contains global layout settings (type, alignment, container size).
 */
class ACE_EXPORT LayoutContext {
public:
    LayoutContext() = default;
    ~LayoutContext() = default;

    SmartLayoutType layoutType = SmartLayoutType::UNKNOWN;
    SmartLayoutAlign mainAxisAlign = SmartLayoutAlign::FLEX_START;
    SmartLayoutAlign crossAxisAlign = SmartLayoutAlign::CENTER;
    SmartLayoutSize size = SmartLayoutSize(0.0, 0.0);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_CONTEXT_H