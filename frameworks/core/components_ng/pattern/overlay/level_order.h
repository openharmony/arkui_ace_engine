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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_LEVEL_ORDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_LEVEL_ORDER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LevelOrder {
public:
    LevelOrder() = default;
    ~LevelOrder() = default;

    static constexpr double ORDER_DEFAULT = 0.0;

    void SetOrder(const double order)
    {
        order_ = order < ORDER_MIN ? ORDER_MIN : (order > ORDER_MAX ? ORDER_MAX : order);
    }

    double GetOrder() const
    {
        return order_;
    }

private:
    double order_ = ORDER_DEFAULT;

    static constexpr double ORDER_MIN = -100000.0;
    static constexpr double ORDER_MAX = 100000.0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_LEVEL_ORDER_H
