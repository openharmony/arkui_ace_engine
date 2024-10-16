
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

#ifndef FOUNDATION_ACE_TEST_CORE_PATTERN_SCROLLABLE_SCROLLABLE_TEST_UTILS_H
#define FOUNDATION_ACE_TEST_CORE_PATTERN_SCROLLABLE_SCROLLABLE_TEST_UTILS_H

#include "gmock/gmock-matchers.h"

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/shape.h"
namespace OHOS::Ace::NG {
using ClipRect = std::variant<RectF, RefPtr<ShapeRect>>;
inline bool CmpClipRect(const ClipRect& lhs, const ClipRect& rhs)
{
    if (std::holds_alternative<RectF>(lhs) && std::holds_alternative<RectF>(rhs)) {
        return std::get<RectF>(lhs) == std::get<RectF>(rhs);
    }
    if (std::holds_alternative<RefPtr<ShapeRect>>(lhs) && std::holds_alternative<RefPtr<ShapeRect>>(rhs)) {
        auto&& shape1 = std::get<RefPtr<ShapeRect>>(lhs);
        auto&& shape2 = std::get<RefPtr<ShapeRect>>(rhs);
        return *shape1 == *shape2;
    }
    return false;
}

MATCHER_P(ClipRectEq, expected, "clip rect variant")
{
    return CmpClipRect(arg, expected);
}
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_CORE_PATTERN_SCROLLABLE_SCROLLABLE_TEST_UTILS_H
