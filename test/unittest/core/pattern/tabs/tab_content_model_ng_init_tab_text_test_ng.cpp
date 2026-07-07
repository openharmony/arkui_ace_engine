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
#include "tabs_test_ng.h"

#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/common/ace_application_info.h"

namespace OHOS::Ace::NG {

class TabContentModelNGInitTabTextTestNg : public TabsTestNg {
public:
    static void SetUpTestSuite()
    {
        TabsTestNg::SetUpTestSuite();
    }
    static void TearDownTestSuite()
    {
        TabsTestNg::TearDownTestSuite();
    }
    void SetUp() override {}
    void TearDown() override
    {
        TabsTestNg::TearDown();
    }
};

/**
 * @tc.name: InitTabTextNullTextProperty001
 * @tc.desc: InitTabText with null textLayoutProperty should not crash due to early CHECK_NULL_VOID
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelNGInitTabTextTestNg, InitTabTextNullTextProperty001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    TabContentModelNG::InitTabText(nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: InitTabTextEnablePunctuationOverflowOptimizeLowApiVersion001
 * @tc.desc: InitTabText with low API version should set EnablePunctuationOverflowOptimize to true and return early
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelNGInitTabTextTestNg, InitTabTextEnablePunctuationOverflowOptimizeLowApiVersion001,
    TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    EXPECT_FALSE(textLayoutProperty->HasEnablePunctuationOverflowOptimize());

    TabContentModelNG::InitTabText(textLayoutProperty);

    EXPECT_TRUE(textLayoutProperty->HasEnablePunctuationOverflowOptimize());
    EXPECT_TRUE(textLayoutProperty->GetEnablePunctuationOverflowOptimizeValue(false));
}

/**
 * @tc.name: InitTabTextEnablePunctuationOverflowOptimizeSetBeforeApiCheck001
 * @tc.desc: EnablePunctuationOverflowOptimize is set before API version check so it is true regardless of API version
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelNGInitTabTextTestNg, InitTabTextEnablePunctuationOverflowOptimizeSetBeforeApiCheck001,
    TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    TabContentModelNG::InitTabText(textLayoutProperty);
    EXPECT_TRUE(textLayoutProperty->GetEnablePunctuationOverflowOptimizeValue(false));
}

/**
 * @tc.name: InitTabTextCheckNullVoidBeforeEnablePunctuationOverflowOptimize001
 * @tc.desc: Verify CHECK_NULL_VOID is before UpdateEnablePunctuationOverflowOptimize so null input safely returns
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelNGInitTabTextTestNg, InitTabTextCheckNullVoidBeforeEnablePunctuationOverflowOptimize001,
    TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    TabContentModelNG::InitTabText(nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: InitTabTextHighApiVersionEnablePunctuationOverflowOptimize001
 * @tc.desc: InitTabText with high API version sets EnablePunctuationOverflowOptimize to true
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelNGInitTabTextTestNg, InitTabTextHighApiVersionEnablePunctuationOverflowOptimize001,
    TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    TabContentModelNG::InitTabText(textLayoutProperty);
    EXPECT_TRUE(textLayoutProperty->GetEnablePunctuationOverflowOptimizeValue(false));
}

} // namespace OHOS::Ace::NG
