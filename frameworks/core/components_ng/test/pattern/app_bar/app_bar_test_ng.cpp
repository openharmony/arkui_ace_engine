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

#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
} // namespace

class AppBarTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void AppBarTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<AppBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void AppBarTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void AppBarTestNg::SetUp() {}

void AppBarTestNg::TearDown() {}

/**
 * @tc.name: Test001
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, Test001, TestSize.Level1)
{
    auto test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    AppBarView::Create(test);

    auto frameNode_1 = AppBarView::Create(test);
    EXPECT_EQ(frameNode_1->GetChildren().size(), 2);
    auto titleBar_1 = AceType::DynamicCast<FrameNode>(frameNode_1->GetChildAtIndex(0));
    EXPECT_EQ(titleBar_1->GetChildren().size(), 2);

    SystemProperties::SetExtSurfaceEnabled(true);
    auto frameNode_2 = AppBarView::Create(test);
    EXPECT_EQ(frameNode_2->GetChildren().size(), 2);
    auto titleBar_2 = AceType::DynamicCast<FrameNode>(frameNode_2->GetChildAtIndex(0));
    EXPECT_EQ(titleBar_2->GetChildren().size(), 3);
}
} // namespace OHOS::Ace::NG
