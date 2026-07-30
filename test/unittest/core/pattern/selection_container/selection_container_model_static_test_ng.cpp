/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/selection_container/selection_container_event_hub.h"
#include "core/components_ng/pattern/selection_container/selection_container_layout_property.h"
#include "core/components_ng/pattern/selection_container/selection_container_model_ng.h"
#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID = 100;
const std::string TAG = "SelectionContainer";
} // namespace

class SelectionContainerModelStaticTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        testing::Test::SetUpTestSuite();
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        testing::Test::TearDownTestSuite();
        MockPipelineContext::TearDown();
    }
    void SetUp() override
    {
        auto pattern = AceType::MakeRefPtr<SelectionContainerPattern>();
        frameNode_ = FrameNode::CreateFrameNode(TAG, NODE_ID, pattern, true);
        ASSERT_NE(frameNode_, nullptr);
        frameNode_->AttachToMainTree();
    }
    void TearDown() override
    {
        frameNode_ = nullptr;
    }

    RefPtr<FrameNode> frameNode_;
};

// ==================== SetCopyOption ====================

HWTEST_F(SelectionContainerModelStaticTestNg, SetCopyOption001, TestSize.Level1)
{
    SelectionContainerModelNG::SetCopyOption(frameNode_.GetRawPtr(), CopyOptions::Distributed);
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetCopyOptionValue(CopyOptions::InApp), CopyOptions::Distributed);
}

HWTEST_F(SelectionContainerModelStaticTestNg, SetCopyOption002, TestSize.Level1)
{
    SelectionContainerModelNG::SetCopyOption(frameNode_.GetRawPtr(), CopyOptions::None);
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetCopyOptionValue(CopyOptions::InApp), CopyOptions::None);
}

// ==================== SetCaretColor ====================

HWTEST_F(SelectionContainerModelStaticTestNg, SetCaretColor001, TestSize.Level1)
{
    SelectionContainerModelNG::SetCaretColor(frameNode_.GetRawPtr(), Color::RED);
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetCaretColorValue(Color::BLACK), Color::RED);
}

// ==================== SetSelectedBackgroundColor ====================

HWTEST_F(SelectionContainerModelStaticTestNg, SetSelectedBackgroundColor001, TestSize.Level1)
{
    SelectionContainerModelNG::SetSelectedBackgroundColor(frameNode_.GetRawPtr(), Color::BLUE);
    auto layoutProperty = frameNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSelectedBackgroundColorValue(Color::BLACK), Color::BLUE);
}

// ==================== SetEnableHapticFeedback ====================

HWTEST_F(SelectionContainerModelStaticTestNg, SetEnableHapticFeedback001, TestSize.Level1)
{
    SelectionContainerModelNG::SetEnableHapticFeedback(frameNode_.GetRawPtr(), false);
    auto pattern = frameNode_->GetPattern<SelectionContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->GetEnableHapticFeedback());
}

HWTEST_F(SelectionContainerModelStaticTestNg, SetEnableHapticFeedback002, TestSize.Level1)
{
    SelectionContainerModelNG::SetEnableHapticFeedback(frameNode_.GetRawPtr(), true);
    auto pattern = frameNode_->GetPattern<SelectionContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetEnableHapticFeedback());
}

// ==================== SetTextJoinStyle ====================

HWTEST_F(SelectionContainerModelStaticTestNg, SetTextJoinStyle001, TestSize.Level1)
{
    SelectionContainerModelNG::SetTextJoinStyle(
        frameNode_.GetRawPtr(), SelectionContainerTextJoinStyle::DIRECT);
    auto pattern = frameNode_->GetPattern<SelectionContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    // DIRECT => separator is empty string
    EXPECT_EQ(pattern->GetTextJoinSeparator(), std::u16string());
}

HWTEST_F(SelectionContainerModelStaticTestNg, SetTextJoinStyle002, TestSize.Level1)
{
    SelectionContainerModelNG::SetTextJoinStyle(
        frameNode_.GetRawPtr(), SelectionContainerTextJoinStyle::NEWLINE);
    auto pattern = frameNode_->GetPattern<SelectionContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    // NEWLINE => separator is u"\n"
    EXPECT_EQ(pattern->GetTextJoinSeparator(), std::u16string(u"\n"));
}

// ==================== SetOnCopy ====================

HWTEST_F(SelectionContainerModelStaticTestNg, SetOnCopy001, TestSize.Level1)
{
    bool called = false;
    std::u16string captured;
    SelectionContainerModelNG::SetOnCopy(frameNode_.GetRawPtr(),
        [&called, &captured](const std::u16string& value) {
            called = true;
            captured = value;
        });
    auto eventHub = frameNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnCopy(u"hello");
    EXPECT_TRUE(called);
    EXPECT_EQ(captured, std::u16string(u"hello"));
}

// ==================== SetOnWillCopy ====================

HWTEST_F(SelectionContainerModelStaticTestNg, SetOnWillCopy001, TestSize.Level1)
{
    bool allowCopy = false;
    SelectionContainerModelNG::SetOnWillCopy(frameNode_.GetRawPtr(),
        [&allowCopy](const std::u16string& value) -> bool {
            allowCopy = true;
            return true;
        });
    auto eventHub = frameNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->FireOnWillCopy(u"copy"));
    EXPECT_TRUE(allowCopy);
}

// ==================== SetOnTextSelectionChange ====================

HWTEST_F(SelectionContainerModelStaticTestNg, SetOnTextSelectionChange001, TestSize.Level1)
{
    bool called = false;
    size_t count = 0;
    SelectionContainerModelNG::SetOnTextSelectionChange(frameNode_.GetRawPtr(),
        [&called, &count](const std::vector<std::u16string>& selectedTexts) {
            called = true;
            count = selectedTexts.size();
        });
    auto eventHub = frameNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnTextSelectionChange({u"a", u"b", u"c"});
    EXPECT_TRUE(called);
    EXPECT_EQ(count, 3u);
}

} // namespace OHOS::Ace::NG
