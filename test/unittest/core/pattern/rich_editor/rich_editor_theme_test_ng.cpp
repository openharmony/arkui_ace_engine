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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorThemeTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};


void RichEditorThemeTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorThemeTestNg::TearDown()
{
    richEditorNode_.Reset();
    MockParagraph::TearDown();
}

void RichEditorThemeTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: RichEditorThemePadding
 * @tc.desc: test padding about rich editor theme
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorThemeTestNg, RichEditorThemePadding, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    auto resourceAdapter = AceType::MakeRefPtr<MockResourceAdapterV2>();
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(resourceAdapter);
    themeConstants->currentThemeStyle_ = AceType::MakeRefPtr<ThemeStyle>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(RichEditorTheme::Builder().Build(themeConstants)));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(RichEditorTheme::Builder().Build(themeConstants)));
    pipeline->SetThemeManager(theme);
    auto richEditorTheme = richEditorPattern->GetTheme<RichEditorTheme>();
    EXPECT_TRUE(static_cast<bool>(richEditorTheme));
    auto padding = richEditorTheme->GetPadding();
    EXPECT_EQ(padding.Left(), Dimension(16.0f, DimensionUnit::VP));
    EXPECT_EQ(padding.Right(), Dimension(16.0f, DimensionUnit::VP));
    EXPECT_EQ(padding.Top(), Dimension(8.0f, DimensionUnit::VP));
    EXPECT_EQ(padding.Bottom(), Dimension(8.0f, DimensionUnit::VP));
}
} // namespace OHOS::Ace::NG
