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
#ifndef USE_GRAPHIC_TEXT_GINE
    enum class RectWidthStyle {
#else
    enum class TextRectWidthStyle {
#endif
        TIGHT,
        MAX,
    };

    enum class Affinity {
#ifndef USE_GRAPHIC_TEXT_GINE
        UPSTREAM,
        DOWNSTREAM,
#else
        PREV,
        NEXT,
#endif
    };

#ifndef USE_GRAPHIC_TEXT_GINE
    enum class RectHeightStyle {
#else
    enum class TextRectHeightStyle {
#endif
        TIGHT,
#ifndef USE_GRAPHIC_TEXT_GINE
        MAX,
        INCLUDELINESPACEMIDDLE,
        INCLUDELINESPACETOP,
        INCLUDELINESPACEBOTTOM,
        STRUCT,
#else
        COVER_TOP_AND_BOTTOM,
        COVER_HALF_TOP_AND_BOTTOM,
        COVER_TOP,
        COVER_BOTTOM,
        FOLLOW_BY_STRUT,
#endif
    };

#ifndef USE_GRAPHIC_TEXT_GINE
    struct TextBox {
        TextDirection direction_;
        TestingRect rect_;
        TextBox() = default;
        TextBox(TestingRect rect, TextDirection direction) : direction_(direction), rect_(rect) {}
    };
#else
    struct TextRect {
        TextDirection direction;
        TestingRect rect;
        TextRect() = default;
        TextRect(TestingRect testRect, TextDirection testDirection) : direction(testDirection), rect(testRect) {}
    };
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
    struct PositionAndAffinity {
        const size_t pos_;
        const Affinity affinity_;
        PositionAndAffinity(size_t pos, Affinity affinity) : pos_(pos), affinity_(affinity) {}
    };
#else
    struct IndexAndAffinity {
        const size_t index;
        const Affinity affinity;
        IndexAndAffinity(size_t pos, Affinity affinity) : index(pos), affinity(affinity) {}
    };
#endif

    template<typename T>
#ifndef USE_GRAPHIC_TEXT_GINE
    struct Range {
        T start_, end_;
        Range() : start_(), end_() {}
        Range(T a, T b) : start_(a), end_(b) {}
        bool operator==(const Range<T>& rhs) const
        {
            return start_ == rhs.start_ && end_ == rhs.end_;
        }
#else
    struct Boundary {
        T leftIndex, rightIndex;
        Boundary() : leftIndex(), rightIndex() {}
        Boundary(T a, T b) : leftIndex(a), rightIndex(b) {}
        bool operator==(const Boundary<T>& rhs) const
        {
            return leftIndex == rhs.leftIndex && rightIndex == rhs.rightIndex;
        }
#endif

        T Width() const
        {
#ifndef USE_GRAPHIC_TEXT_GINE
            return end_ - start_;
#else
            return rightIndex - leftIndex;
#endif
        }

        void Shift(T offset)
        {
#ifndef USE_GRAPHIC_TEXT_GINE
            start_ += offset;
            end_ += offset;
#else
            leftIndex += offset;
            rightIndex += offset;
#endif
        }
    };
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_PROPERTIES_H
