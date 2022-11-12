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

#include <optional>
#include "gtest/gtest.h"

#include "core/components/badge/badge_component.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/badge/badge_layout_algorithm.h"
#include "core/components_ng/pattern/badge/badge_layout_property.h"
#include "core/components_ng/pattern/badge/badge_pattern.h"
#include "core/components_ng/pattern/badge/badge_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

} // namespace

class BadgePatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
protected:
};

/**
 * @tc.name: BadgeFrameNodeCreator001
 * @tc.desc: Test empty property of Badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgePatternTestNg, BadgeFrameNodeCreator001, TestSize.Level1)
{
    BadgeView badge;
    NG::BadgeView::BadgeParameters badgeParameters;
    badge.Create(badgeParameters);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto badgeLayoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_FALSE(badgeLayoutProperty == nullptr);
}

/**
 * @tc.name: BadgeFrameNodeCreator002
 * @tc.desc: Test all the properties of Badge.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BadgePatternTestNg, BadgeFrameNodeCreator002, TestSize.Level1)
{
    BadgeView badge;
    Dimension fontSize;
    Dimension badgeSize;
    NG::BadgeView::BadgeParameters badgeParameters;
    badgeParameters.badgeValue = "test";
    badgeParameters.badgeCount = 1;
    badgeParameters.badgeMaxCount = 99;
    badgeParameters.badgePosition = 1;
    badgeParameters.badgeColor = Color::BLACK;
    badgeParameters.badgeTextColor = Color::GREEN;
    badgeParameters.badgeFontSize = fontSize;
    badgeParameters.badgeCircleSize = badgeSize;
    badge.Create(badgeParameters);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto badgeLayoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    EXPECT_FALSE(badgeLayoutProperty == nullptr);
}
} // namespace OHOS::Ace::NG
