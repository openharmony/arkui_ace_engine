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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_H

#include "core/components_ng/test/mock/rosen/testing_typography_properties.h"

namespace OHOS::Ace::Testing {
enum class WordBreakType {
    WordBreakTypeNormal = 0,
    WordBreakTypeBreakAll,
    WordBreakTypeBreakWord
};

enum class TextAlign {
    LEFT = 0,
    RIGHT,
    CENTER,
    JUSTIFY,
    START,
    END,
};

class TestingTypography {
public:
    TestingTypography() = default;
    ~TestingTypography() = default;

    double GetMaxWidth();
    double GetHeight();
    double GetLongestLine();
    double GetMinIntrinsicWidth();
    double GetMaxIntrinsicWidth();
    double GetAlphabeticBaseline();
    double GetIdeographicBaseline();
    bool DidExceedMaxLines();
    void Layout(double width);
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_H
