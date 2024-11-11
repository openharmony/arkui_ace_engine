/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PATTERN_TEST_STUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PATTERN_TEST_STUB_H

#include "interfaces/inner_api/ace/ai/image_analyzer.h"
#include "core/components/common/properties/paint_state.h"

namespace OHOS::Ace::NG {
class TestHolder {
public:
    TestHolder() = default;
    ~TestHolder() = default;

    static TestHolder* GetInstance()
    {
        static TestHolder instance;
        return &instance;
    }

    void SetUp()
    {
        config = nullptr;
        onAnalyzed = nullptr;
        x = -1;
        y = -1;
        width = -1;
        height = -1;
        counter = 0;
        isCalled = false;
        request = true;
        rect = Rect(-1, -1, -1, -1);
        value = -1;
        segments.clear();
        text = "";
        maxWidth = std::make_optional<double>();
        scaleX = -1;
        scaleY = -1;
        skewX = -1;
        skewY = -1;
        transX = -1;
        transY = -1;
        composite = static_cast<CompositeOperation>(-1);
    }

    void TearDown()
    {
        request = false;
    }

    void* config = nullptr;
    OnAnalyzedCallback onAnalyzed = nullptr;
    double x = -1;
    double y = -1;
    double width = -1;
    double height = -1;
    int counter = 0;
    bool isCalled = false;
    bool request = false;
    Rect rect = Rect(-1, -1, -1, 1);
    double value = -1;
    std::vector<double> segments;
    std::string text = "";
    std::optional<double> maxWidth = std::make_optional<double>();
    double scaleX = -1;
    double scaleY = -1;
    double skewX = -1;
    double skewY = -1;
    double transX = -1;
    double transY = -1;
    CompositeOperation composite = static_cast<CompositeOperation>(-1);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PATTERN_H
