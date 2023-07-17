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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_PROPERTIES_H

#include <cstddef>

#include "testing_rect.h"

namespace OHOS::Ace::Testing {
enum class TextDirection {
    RTL,
    LTR,
};

class TestingTypographyProperties {
public:
    enum class RectWidthStyle {
        TIGHT,
        MAX,
    };

    enum class Affinity {
        UPSTREAM,
        DOWNSTREAM,
    };

    enum class RectHeightStyle {
        TIGHT,
        MAX,
        INCLUDELINESPACEMIDDLE,
        INCLUDELINESPACETOP,
        INCLUDELINESPACEBOTTOM,
        STRUCT,
    };

    struct TextBox {
        TextDirection direction_;
        TestingRect rect_;
        TextBox() = default;
        TextBox(TestingRect rect, TextDirection direction) : direction_(direction), rect_(rect) {}
    };

    struct PositionAndAffinity {
        const size_t pos_;
        const Affinity affinity_;
        PositionAndAffinity(size_t pos, Affinity affinity) : pos_(pos), affinity_(affinity) {}
    };

    template<typename T>
    struct Range {
        T start_, end_;
        Range() : start_(), end_() {}
        Range(T a, T b) : start_(a), end_(b) {}
        bool operator==(const Range<T>& rhs) const
        {
            return start_ == rhs.start_ && end_ == rhs.end_;
        }

        T Width() const
        {
            return end_ - start_;
        }

        void Shift(T offset)
        {
            start_ += offset;
            end_ += offset;
        }
    };
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_PROPERTIES_H
