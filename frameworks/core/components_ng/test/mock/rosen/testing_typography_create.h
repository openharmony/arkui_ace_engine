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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_CREATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_CREATE_H

#include <memory>
#include <vector>

#include "testing_font_collection.h"
#include "testing_typography.h"
#include "testing_typography_properties.h"
#include "testing_typography_style.h"

namespace OHOS::Ace::Testing {
class TestingTypographyCreate {
public:
    TestingTypographyCreate() = default;
    virtual ~TestingTypographyCreate() = default;

    static std::unique_ptr<TestingTypographyCreate> CreateRosenBuilder(
        const TestingTypographyStyle& style, std::shared_ptr<TestingFontCollection> font_collection)
    {
        return std::make_unique<TestingTypographyCreate>();
    }

#ifdef USE_GRAPHIC_TEXT_GINE
    static std::unique_ptr<TestingTypographyCreate> Create(
        const TestingTypographyStyle &style, std::shared_ptr<TestingFontCollection> collection)
    {
        return std::make_unique<TestingTypographyCreate>();
    }

    std::unique_ptr<TestingTypography> CreateTypography()
    {
        return std::make_unique<TestingTypography>();
    }
#endif

    virtual void PushStyle(const TestingTextStyle& style) {}

#ifndef USE_GRAPHIC_TEXT_GINE
    virtual void Pop() {}

    virtual void AddText(const std::u16string& text) {}
#else
    virtual void PopStyle() {}

    virtual void AppendText(const std::u16string& text) {}
#endif

    virtual std::unique_ptr<TestingTypography> Build()
    {
        return std::make_unique<TestingTypography>();
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_CREATE_H
