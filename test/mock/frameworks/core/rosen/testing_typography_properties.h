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
    enum class TextRectWidthStyle {
        TIGHT,
        MAX,
    };

    enum class Affinity {
        PREV,
        NEXT,
    };

    enum class TextRectHeightStyle {
        TIGHT,
        COVER_TOP_AND_BOTTOM,
        COVER_HALF_TOP_AND_BOTTOM,
        COVER_TOP,
        COVER_BOTTOM,
        FOLLOW_BY_STRUT,
    };

    struct TextRect {
        TextDirection direction;
        TestingRect rect;
        TextRect() = default;
        TextRect(TestingRect testRect, TextDirection testDirection) : direction(testDirection), rect(testRect) {}
    };

    struct IndexAndAffinity {
        const size_t index;
        const Affinity affinity;
        IndexAndAffinity(size_t pos, Affinity affinity) : index(pos), affinity(affinity) {}
    };

    template<typename T>
    struct Boundary {
        T leftIndex, rightIndex;
        Boundary() : leftIndex(), rightIndex() {}
        Boundary(T a, T b) : leftIndex(a), rightIndex(b) {}
        bool operator==(const Boundary<T>& rhs) const
        {
            return leftIndex == rhs.leftIndex && rightIndex == rhs.rightIndex;
        }

        T Width() const
        {
            return rightIndex - leftIndex;
        }

        void Shift(T offset)
        {
            leftIndex += offset;
            rightIndex += offset;
        }
    };
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_PROPERTIES_H
