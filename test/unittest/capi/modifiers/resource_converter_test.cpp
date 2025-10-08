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

#include "common_method_modifier_test.h"
#include "test/unittest/core/base/view_abstract_test_ng.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace Converter {
    template<>
    void AssignArkValue(Ark_Resource& dst, const std::string& src, ConvContext *ctx);
}

class ResourceConvertorTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        themeManager_ = AceType::MakeRefPtr<::testing::NiceMock<MockThemeManager>>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager_);

        // assume using of test/mock/core/common/mock_theme_constants.cpp in build
        themeConstants_ = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        EXPECT_CALL(*themeManager_, GetThemeConstants(testing::_, testing::_))
            .WillRepeatedly(testing::Return(themeConstants_));
        ON_CALL(*themeManager_, GetTheme(testing::_)).WillByDefault(CatchEmptyTheme1);
        ON_CALL(*themeManager_, GetTheme(testing::_, testing::_)).WillByDefault(CatchEmptyTheme2);

        themeConstants_->LoadTheme(0);
        MockThemeStyle::GetInstance()->SetAttributes({});

        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

        auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(true);
        MockPipelineContext::GetCurrent()->SetTaskExecutor(taskExecutor);
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetTaskExecutor(nullptr);
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
        themeManager_ = nullptr;
        themeConstants_ = nullptr;
    }

    static void AddResource(std::string key, const ResRawValue& value)
    {
        ThemeConstantsType type = ThemeConstantsType::ERROR;
        if (std::holds_alternative<std::string>(value)) {
            type = ThemeConstantsType::STRING;
        }
        ASSERT_NE(type, ThemeConstantsType::ERROR);
        MockThemeStyle::GetInstance()->SetAttr(key, { .type = type, .value = value });
    }

    inline static RefPtr<::testing::NiceMock<MockThemeManager>> themeManager_;
    inline static RefPtr<ThemeConstants> themeConstants_;
};

/**
 * @tc.name: ResourceConverterTest001
 * @tc.desc: ResourceConverter test
 * @tc.type: FUNC
 */
HWTEST_F(ResourceConvertorTest, ResourceConverterTest001, TestSize.Level1)
{
    auto registerResource = [](const std::string& id, const std::string& value) -> Ark_Resource {
        // Register a resource
        AddResource(id, value);
        // Create Ark resource
        return Converter::ArkCreate<Ark_Resource>(id, ResourceType::STRING, Converter::FC);
    };

    using OneTestStep = std::tuple<Ark_Resource, std::string>;
    const std::vector<OneTestStep> testPlan = {
        { registerResource("1", "100.00vp"), "100.00vp" },
        { registerResource("2", "200.00px"), "200.00px" },
    };

    for (auto [inputValue, expectedValue]: testPlan) {
        Converter::ResourceConverter converter(inputValue);
        auto dimension = converter.ToDimension();
        EXPECT_EQ(dimension->ToString(), expectedValue);
    }
}
} // namespace OHOS::Ace::NG
