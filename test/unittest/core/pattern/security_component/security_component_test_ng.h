/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SECURITY_COMPONENT_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SECURITY_COMPONENT_TEST_NG_H

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>

#include "gtest/gtest.h"

namespace OHOS::Ace::NG {
    constexpr float DEFAULT_BUTTON_SIZE = 20.0f;
class SecurityComponentModelTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
protected:
    static RefPtr<FrameNode> CreateSecurityComponent(int32_t text, int32_t icon,
        int32_t backgroundType, std::string type);
    static void CreateSecurityComponentNotFinish(int32_t text, int32_t icon,
        int32_t backgroundType, std::string type);
    static RefPtr<LayoutWrapperNode> CreateLayoutWrapper(RefPtr<FrameNode>& node);
    static RefPtr<LayoutWrapperNode> CreateSecurityComponentLayoutWrapper(RefPtr<FrameNode>& node);
    static void CheckSecurityComponentDefaultProp(RefPtr<FrameNode>& node);
    static void InitDefaultTheme(RefPtr<SecurityComponentTheme>& theme);
    static void SetLocationUserDefinedPropty();
    static void SetPasteUserDefinedPropty();
    static void SetSaveUserDefinedPropty();
    static void InitLayoutAlgorithm(RefPtr<SecurityComponentLayoutAlgorithm>& buttonAlgorithm);
};

class MockSecurityComponentButtonLayoutAlgorithm : public BoxLayoutAlgorithm {
public:
    MockSecurityComponentButtonLayoutAlgorithm() = default;

    ~MockSecurityComponentButtonLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override
    {
        SizeF frameSize(DEFAULT_BUTTON_SIZE, DEFAULT_BUTTON_SIZE);
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SECURITY_COMPONENT_TEST_NG_H
