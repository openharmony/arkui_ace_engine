/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/common/ace_application_info.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class NavigationTitleUtilTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    }
    static void TearDownTestSuite()
    {
        MockContainer::Current()->pipelineContext_ = nullptr;
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: InitTextPropertyNullTextProperty001
 * @tc.desc: InitTextProperty with null textLayoutProperty should not crash due to early CHECK_NULL_VOID
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTitleUtilTestNg, InitTextPropertyNullTextProperty001, TestSize.Level1)
{
    ASSERT_NO_FATAL_FAILURE(NavigationTitleUtil::InitTextProperty(nullptr));
}

/**
 * @tc.name: InitTextPropertyPunctuationOverflowLowApiVersion001
 * @tc.desc: InitTextProperty with low API version should set PunctuationOverflow to true and return early
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTitleUtilTestNg, InitTextPropertyPunctuationOverflowLowApiVersion001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    NavigationTitleUtil::InitTextProperty(textLayoutProperty);

    EXPECT_TRUE(textLayoutProperty->GetPunctuationOverflowValue(false));
}

/**
 * @tc.name: InitTextPropertyPunctuationOverflowHighApiVersion001
 * @tc.desc: InitTextProperty with high API version should set PunctuationOverflow and OrphanCharOptimization
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTitleUtilTestNg, InitTextPropertyPunctuationOverflowHighApiVersion001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    NavigationTitleUtil::InitTextProperty(textLayoutProperty);

    EXPECT_TRUE(textLayoutProperty->GetPunctuationOverflowValue(false));
}

/**
 * @tc.name: InitTextPropertyCheckNullVoidMovedBeforePunctuationOverflow001
 * @tc.desc: Verify CHECK_NULL_VOID is executed before UpdatePunctuationOverflow so null input does not crash
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTitleUtilTestNg, InitTextPropertyCheckNullVoidMovedBeforePunctuationOverflow001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    ASSERT_NO_FATAL_FAILURE(NavigationTitleUtil::InitTextProperty(nullptr));
}

/**
 * @tc.name: InitTextPropertyPunctuationOverflowDefaultNotSet001
 * @tc.desc: Verify PunctuationOverflow is not set before calling InitTextProperty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTitleUtilTestNg, InitTextPropertyPunctuationOverflowDefaultNotSet001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    EXPECT_FALSE(textLayoutProperty->HasPunctuationOverflow());

    NavigationTitleUtil::InitTextProperty(textLayoutProperty);

    EXPECT_TRUE(textLayoutProperty->HasPunctuationOverflow());
    EXPECT_TRUE(textLayoutProperty->GetPunctuationOverflowValue(false));
}

} // namespace OHOS::Ace::NG
