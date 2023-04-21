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

#include "gtest/gtest.h"

#include "core/components_ng/base/frame_node.h"
#define protected public
#define private public
#include "core/components/badge/badge_theme.h"
#undef protected
#undef private
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/badge/badge_pattern.h"
#include "core/components_ng/pattern/badge/badge_view.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string VALUE = "badge value";
const int COUNT = 10;
} // namespace

class BadgeAccessibilityPropertyTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};
void BadgeAccessibilityPropertyTestNg::SetUp()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<BadgeTheme>()));
}
void BadgeAccessibilityPropertyTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: BadgeAccessibilityPropertyTestNg001
 * @tc.desc: Test Text property for BadgeValue of Badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeAccessibilityPropertyTestNg, BadgeAccessibilityPropertyTestNg001, TestSize.Level1)
{
    BadgeView badge;
    NG::BadgeView::BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badge.Create(badgeParameters);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto badgeAccessibilityProperty = frameNode->GetAccessibilityProperty<BadgeAccessibilityProperty>();
    EXPECT_EQ(badgeAccessibilityProperty->GetText(), VALUE);
}

/**
 * @tc.name: BadgeAccessibilityPropertyTestNg002
 * @tc.desc: Test Text property for BadgeCount of Badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeAccessibilityPropertyTestNg, BadgeAccessibilityPropertyTestNg002, TestSize.Level1)
{
    BadgeView badge;
    NG::BadgeView::BadgeParameters badgeParameters;
    badgeParameters.badgeValue = VALUE;
    badgeParameters.badgeCount = COUNT;
    badge.Create(badgeParameters);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto badgeAccessibilityProperty = frameNode->GetAccessibilityProperty<BadgeAccessibilityProperty>();
    EXPECT_EQ(badgeAccessibilityProperty->GetText(), std::to_string(COUNT));
}

/**
 * @tc.name: BadgeAccessibilityPropertyTestNg003
 * @tc.desc: Test Text property of Badge if BadgeValue is empty.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgeAccessibilityPropertyTestNg, BadgeAccessibilityPropertyTestNg003, TestSize.Level1)
{
    BadgeView badge;
    NG::BadgeView::BadgeParameters badgeParameters;
    badge.Create(badgeParameters);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto badgeAccessibilityProperty = frameNode->GetAccessibilityProperty<BadgeAccessibilityProperty>();
    EXPECT_EQ(badgeAccessibilityProperty->GetText(), "");
}
} // namespace OHOS::Ace::NG
