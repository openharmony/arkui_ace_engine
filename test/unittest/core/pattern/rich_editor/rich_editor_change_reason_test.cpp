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
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorChangeReasonTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorChangeReasonTest::SetUp()
{
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

void RichEditorChangeReasonTest::TearDown()
{
    richEditorNode_ = nullptr;
}

void RichEditorChangeReasonTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: ControllerAddTextSpan
 * @tc.desc: test AddTextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerAddTextSpan001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CONTROLLER);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorController->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_EQ(changeReason, TextChangeReason::CONTROLLER);
}

/**
 * @tc.name: ControllerAddImageSpan
 * @tc.desc: test AddImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerAddImageSpan001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CONTROLLER);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorController->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    EXPECT_EQ(changeReason, TextChangeReason::CONTROLLER);
}

/**
 * @tc.name: ControllerAddSymbolSpan
 * @tc.desc: test AddSymbolSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerAddSymbolSpan001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CONTROLLER);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorController->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    EXPECT_EQ(changeReason, TextChangeReason::CONTROLLER);
}

/**
 * @tc.name: ControllerDeleteSpans
 * @tc.desc: test DeleteSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, ControllerDeleteSpans001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::CONTROLLER);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    RangeOptions options;
    options.start = 0;
    options.end = 1;
    richEditorController->DeleteSpans(options);
    EXPECT_EQ(changeReason, TextChangeReason::CONTROLLER);
}

/**
 * @tc.name: ControllerDeleteSpans
 * @tc.desc: test DeleteSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, DeleteRange001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::INPUT);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorPattern->DeleteRange(0, 1, true);
    EXPECT_EQ(changeReason, TextChangeReason::INPUT);
}

/**
 * @tc.name: DeleteBackwardForward
 * @tc.desc: test DeleteSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorChangeReasonTest, DeleteBackwardForward001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);

    auto changeReason = TextChangeReason::UNKNOWN;
    auto onWillChange = [&changeReason](const RichEditorChangeValue& changeValue) {
        EXPECT_EQ(changeValue.changeReason_, TextChangeReason::INPUT);
        changeReason = changeValue.changeReason_;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    richEditorPattern->HandleOnDelete(true);
    EXPECT_EQ(changeReason, TextChangeReason::INPUT);

    changeReason = TextChangeReason::UNKNOWN;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(changeReason, TextChangeReason::INPUT);

    richEditorPattern->SetCaretPosition(0);

    changeReason = TextChangeReason::UNKNOWN;
    richEditorPattern->HandleOnDelete(false);
    EXPECT_EQ(changeReason, TextChangeReason::INPUT);
    
    changeReason = TextChangeReason::UNKNOWN;
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(changeReason, TextChangeReason::INPUT);
}

}