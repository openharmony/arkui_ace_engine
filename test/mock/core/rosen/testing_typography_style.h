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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_STYLE_H

#include <limits>
#include <string>
#include <vector>

#include "testing_typography.h"
#include "testing_typography_properties.h"

namespace OHOS::Ace::Testing {
class TestingTypographyStyle {
public:
    static const std::u16string ELLIPSIS;
    TextDirection textDirection;
    std::string locale;
    WordBreakType wordBreakType = WordBreakType::WordBreakTypeBreakWord;
    double fontSize = 14;
    std::u16string ellipsis;
    TextAlign textAlign = TextAlign::START;
    size_t maxLines = std::numeric_limits<size_t>::max();
    std::string fontFamily;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_STYLE_H
