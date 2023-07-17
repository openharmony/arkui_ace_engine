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
#include "core/components_ng/test/pattern/app_bar/mock_theme_manager.h"
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
    void ClickBtn(RefPtr<FrameNode> frameNode);
};

void AppBarTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
}

void AppBarTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void AppBarTestNg::SetUp() {}

void AppBarTestNg::TearDown() {}

void AppBarTestNg::ClickBtn(RefPtr<FrameNode> frameNode)
{
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    EXPECT_TRUE(eventHub->clickEventActuator_);
    auto clickEvents = eventHub->clickEventActuator_->clickEvents_;
    GestureEvent info;
    EXPECT_FALSE(clickEvents.empty());
    clickEvents.front()->GetGestureEventFunc()(info);
}

/**
 * @tc.name: Test001
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, Test001, TestSize.Level1)
{
    auto test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AppBarView::Create(test);
    EXPECT_EQ(frameNode->GetChildren().size(), 2);
    auto titleBar = frameNode->GetChildAtIndex(0);
    EXPECT_EQ(titleBar->GetChildren().size(), 3);
}

/**
 * @tc.name: Test002
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, Test002, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("stage", 1, AceType::MakeRefPtr<StagePattern>());
    auto frameNode = AppBarView::Create(stage);
    stage->GetPattern<StagePattern>()->OnRebuildFrame();
    auto titleBar = frameNode->GetChildAtIndex(0);
    auto backbtn = AceType::DynamicCast<FrameNode>(titleBar->GetFirstChild());
    EXPECT_EQ(backbtn->GetLayoutProperty()->GetVisibility(), VisibleType::GONE);

    auto test2 = AceType::MakeRefPtr<FrameNode>("test", 2, AceType::MakeRefPtr<Pattern>());
    auto test3 = AceType::MakeRefPtr<FrameNode>("test", 3, AceType::MakeRefPtr<Pattern>());
    stage->AddChild(test2);
    stage->AddChild(test3);
    frameNode = AppBarView::Create(stage);
    stage->GetPattern<StagePattern>()->OnRebuildFrame();
    titleBar = frameNode->GetChildAtIndex(0);
    backbtn = AceType::DynamicCast<FrameNode>(titleBar->GetFirstChild());
    EXPECT_EQ(backbtn->GetLayoutProperty()->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: Test003
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, Test003, TestSize.Level1)
{
    auto test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    SystemProperties::SetExtSurfaceEnabled(true);
    auto frameNode = AppBarView::Create(test);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetChildren().size(), 2);
    auto titleBar = frameNode->GetChildAtIndex(0);
    EXPECT_TRUE(titleBar);
    EXPECT_EQ(titleBar->GetChildren().size(), 3);
    auto backBtn = AceType::DynamicCast<FrameNode>(titleBar->GetChildAtIndex(0));
    EXPECT_TRUE(backBtn);
    ClickBtn(backBtn);
    auto shareBtn = AceType::DynamicCast<FrameNode>(titleBar->GetChildAtIndex(2));
    EXPECT_TRUE(shareBtn);
    ClickBtn(shareBtn);
    SUCCEED();
}
} // namespace OHOS::Ace::NG
