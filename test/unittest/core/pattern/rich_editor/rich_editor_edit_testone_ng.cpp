/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "test/unittest/core/pattern/rich_editor/rich_editor_styled_string_common_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    constexpr int32_t CALCLINEEND_POSITION = 0;
    const std::u16string TEST_INSERT_LINE_SPACE = u" ";
}

class RichEditorEditTestOneNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorEditTestOneNg::SetUp()
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

void RichEditorEditTestOneNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorEditTestOneNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: GetChildByIndex002
 * @tc.desc: test get child by index
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetChildByIndex002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    richEditorPattern->GetChildByIndex(-1);
    AddSpan(INIT_VALUE_1);
    auto ret = richEditorPattern->GetChildByIndex(0);
    EXPECT_EQ(*(contentNode->GetChildren().begin()), ret);
}

/**
 * @tc.name: GetChildByIndex001
 * @tc.desc: test GetChildByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetChildByIndex001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    AddSpan(INIT_VALUE_1);
    auto ret1 = richEditorPattern->GetChildByIndex(1);
    EXPECT_EQ(ret1, nullptr);
    auto ret2 = richEditorPattern->GetChildByIndex(-1);
    EXPECT_EQ(ret2, nullptr);
    auto ret3 = richEditorPattern->GetChildByIndex(0);
    EXPECT_NE(ret3, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, CreateNodePaintMethod001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: GetSpanItemByIndex001
 * @tc.desc: test GetSpanItemByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetSpanItemByIndex001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto ret = richEditorPattern->GetSpanItemByIndex(-1);
    EXPECT_EQ(ret, nullptr);
    ret = richEditorPattern->GetSpanItemByIndex(1);
    EXPECT_EQ(ret, nullptr);
    ret = richEditorPattern->GetSpanItemByIndex(0);
    EXPECT_EQ(ret, richEditorPattern->spans_.front());
}

/**
 * @tc.name: GetSelectedBackgroundColor001
 * @tc.desc: test GetSelectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetSelectedBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
    */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    richEditorPattern->selectedBackgroundColor_.reset();
    auto ret = richEditorPattern->GetSelectedBackgroundColor();
    EXPECT_NE(ret.GetValue(), 0);
}

/**
 * @tc.name: RichEditorHalfLeading001
 * @tc.desc: test RichEditor HalfLeading
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, RichEditorHalfLeading001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    TextStyle textStyle;
    textStyle.SetHalfLeading(true);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateHalfLeading = true;

    richEditorPattern->UpdateTextStyle(newSpan1, updateSpanStyle, textStyle);
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetHalfLeading(), true);
    ClearSpan();
}

/**
 * @tc.name: BeforeAddImage001
 * @tc.desc: test BeforeAddImage
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, BeforeAddImage001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorChangeValue changeValue;
    ImageSpanOptions options;
    auto eventHub = richEditorNode_->GetOrCreateEventHub<RichEditorEventHub>();
    eventHub->SetOnDidChange([](const RichEditorChangeValue& value) -> bool { return false; });
    auto ret = richEditorPattern->BeforeAddImage(changeValue, options, 100);
    EXPECT_TRUE(ret);
}

class MockTextInputConnection : public TextInputConnection {
public:
    MockTextInputConnection(const WeakPtr<TextInputClient>& client, const RefPtr<TaskExecutor>& taskExecutor)
        : TextInputConnection(client, taskExecutor)
    {}

    MOCK_METHOD(void, Show, (bool isFocusViewChanged, int32_t instanceId), (override));
    MOCK_METHOD(void, SetEditingState, (const TextEditingValue& value, int32_t instanceId, bool needFireChangeEvent),
        (override));
    MOCK_METHOD(void, Close, (int32_t instanceId), (override));
};

class MockTextInputClient : public TextInputClient {
public:
    MOCK_METHOD(void, UpdateEditingValue, (const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent),
        (override));
    MOCK_METHOD(void, PerformAction, (TextInputAction action, bool forceCloseKeyboard), (override));
};

class MockTaskExecutor : public TaskExecutor {
public:
    MOCK_METHOD(void, AddTaskObserver, (Task && callback), (override));
    MOCK_METHOD(void, RemoveTaskObserver, (), (override));
    MOCK_METHOD(bool, WillRunOnCurrentThread, (TaskType type), (const, override));
    MOCK_METHOD(void, RemoveTask, (TaskType type, const std::string& name), (override));

    MOCK_METHOD(bool, OnPostTask,
        (Task && task, TaskType type, uint32_t delayTime, const std::string& name, PriorityType priorityType),
        (const, override));
    MOCK_METHOD(Task, WrapTaskWithTraceId, (Task && task, int32_t id), (const, override));
    MOCK_METHOD(bool, OnPostTaskWithoutTraceId,
        (Task && task, TaskType type, uint32_t delayTime, const std::string& name, PriorityType priorityType),
        (const, override));
};

/**
 * @tc.name: UnableStandardInput001
 * @tc.desc: test RichEditorPattern UnableStandardInput
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, UnableStandardInput001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->UnableStandardInput(true);
    bool res = richEditorPattern->UnableStandardInput(false);
    ASSERT_EQ(res, false);
}

/**
 * @tc.name: UnableStandardInput002
 * @tc.desc: test RichEditorPattern UnableStandardInput
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, UnableStandardInput002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto client = AceType::MakeRefPtr<MockTextInputClient>();
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->connection_ = AceType::MakeRefPtr<MockTextInputConnection>(client, taskExecutor);
    richEditorPattern->imeAttached_ = true;
    bool res = richEditorPattern->UnableStandardInput(false);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: ProvideabilityNameText001
 * @tc.desc: test provide abilityName information to inputmethod function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, ProvideabilityNameText, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = richEditorPattern->GetMiscTextConfig();
    auto textconfig = miscTextConfig.value();
    auto abilityName = UtfUtils::Str16ToStr8(textconfig.inputAttribute.abilityName).c_str();
    size_t count = 0;
    size_t i = 0;
    while (i < abilityName.size()) {
        count++;
        i += (abilityName[i] >= 0xD800 && abilityName[i] <= 0xDBFF) ? 2 : 1;
    }
    EXPECT_NE(count, 0);
#endif
}

/**
 * @tc.name: GetTextContentLength001
 * @tc.desc: test GetTextContentLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetTextContentLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->styledString_ = nullptr;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->GetTextContentLength();

    richEditorPattern->styledString_ = nullptr;
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->GetTextContentLength();

    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"abc");
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->GetTextContentLength();

    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"abc");
    richEditorPattern->isSpanStringMode_ = false;
    int32_t res = richEditorPattern->GetTextContentLength();
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: CalcLineBeginPosition001
 * @tc.desc: test CalcLineBeginPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, CalcLineBeginPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t result = 1;
    result = richEditorPattern->CalcLineBeginPosition();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CalcLineEndPosition
 * @tc.desc: test CalcLineEndPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, CalcLineEndPosition, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->richTextRect_.y_ = 10.0f;
    richEditorPattern->contentRect_.y_ = 20.0f;
    EXPECT_EQ(richEditorPattern->CalcLineEndPosition(10), CALCLINEEND_POSITION);
}

/**
 * @tc.name: MoveTextRect001
 * @tc.desc: test MoveTextRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, MoveTextRect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->richTextRect_ = RectF(0, 5, 100, 160);
    richEditorPattern->contentRect_ = RectF(0, 10, 100, 140);
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_EQ(richEditorPattern->MoveTextRect(0.0f), 0.0f);
}

/**
 * @tc.name: AdjustIndexSkipLineSeparator001
 * @tc.desc: test AdjustIndexSkipLineSeparator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, AdjustIndexSkipLineSeparator001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t currentPosition = 1;
    bool ret = richEditorPattern->AdjustIndexSkipLineSeparator(currentPosition);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AdjustIndexSkipLineSeparator002
 * @tc.desc: test AdjustIndexSkipLineSeparator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, AdjustIndexSkipLineSeparator002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t currentPosition = 0;
    bool ret = richEditorPattern->AdjustIndexSkipLineSeparator(currentPosition);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AdjustIndexSkipLineSeparator003
 * @tc.desc: test AdjustIndexSkipLineSeparator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, AdjustIndexSkipLineSeparator003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t currentPosition = 10;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = u"AdjustInd\nxSkipLineSeparator";
    richEditorPattern->spans_.push_back(spanItem);
    EXPECT_TRUE(richEditorPattern->AdjustIndexSkipLineSeparator(currentPosition));
}

/**
 * @tc.name: IsTextEditableForStylus001
 * @tc.desc: test IsTextEditableForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, IsTextEditableForStylus001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool tag = richEditorPattern->IsTextEditableForStylus();
    EXPECT_TRUE(tag);
}

/**
 * @tc.name: IsTextEditableForStylus002
 * @tc.desc: test IsTextEditableForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, IsTextEditableForStylus002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(richEditorPattern->GetFocusHub()->IsFocusable());
    bool tag = richEditorPattern->IsTextEditableForStylus();
    EXPECT_FALSE(tag);
}

/**
 * @tc.name: IsTextEditableForStylus003
 * @tc.desc: test IsTextEditableForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, IsTextEditableForStylus003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(richEditorPattern->GetFocusHub()->IsFocusable());
    EXPECT_TRUE(richEditorNode_->IsVisible());
    richEditorNode_->layoutProperty_->OnVisibilityUpdate(VisibleType::INVISIBLE);
    EXPECT_FALSE(richEditorNode_->IsVisible());
    bool tag = richEditorPattern->IsTextEditableForStylus();
    EXPECT_FALSE(tag);
}

/**
 * @tc.name: GetRightWordPosition001
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetRightWordPosition001, TestSize.Level2)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->caretPosition_), 0);
    AddSpan(INIT_VALUE_1 + TEST_INSERT_LINE_SPACE);
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(richEditorPattern->GetTextContentLength()),
        richEditorPattern->GetTextContentLength());
}

/**
 * @tc.name: GetRightWordPosition002
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetRightWordPosition002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::u16string firstText = u"text";
    AddSpan(firstText);
    std::u16string space = u" ";
    std::u16string secondText = u"content";
    AddSpan(space + secondText);
    auto initCaretPosition = firstText.size();
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(initCaretPosition), initCaretPosition + space.size());
}

/**
 * @tc.name: GetRightWordPosition003
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetRightWordPosition003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::u16string firstText = u"Text ";
    AddSpan(firstText);
    std::u16string secondText = u"Content\n";
    AddSpan(secondText);
    AddSpan(INIT_VALUE_3);

    auto initCaretPosition = firstText.size() + secondText.size() - 1;
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(initCaretPosition), initCaretPosition + 1);
}

/**
 * @tc.name: GetRightWordPosition004
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetRightWordPosition004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    std::string firstText = "text";
    AddSpan(firstText);
    std::string space = " ";
    std::string secondText = "content";
    AddSpan(space + secondText);
    for (auto iter = richEditorPattern->spans_.cbegin(); iter != richEditorPattern->spans_.cend(); iter++) {
        auto span = *iter;
        span->placeholderIndex = 0;
    }
    int32_t initCaretPosition = firstText.size();
    auto position =
        std::clamp(initCaretPosition + 1, 0, static_cast<int32_t>(richEditorPattern->GetTextContentLength()));
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(initCaretPosition), position);
}

/**
 * @tc.name: GetRightWordPosition005
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetRightWordPosition005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    std::string firstText = "text ";
    AddSpan(firstText);
    std::string secondText = "content";
    AddSpan(secondText);
    for (auto iter = richEditorPattern->spans_.cbegin(); iter != richEditorPattern->spans_.cend(); iter++) {
        auto span = *iter;
        span->placeholderIndex = 0;
    }
    int32_t initCaretPosition = firstText.size() + secondText.size() - 1;
    auto position =
        std::clamp(initCaretPosition + 1, 0, static_cast<int32_t>(richEditorPattern->GetTextContentLength()));
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(initCaretPosition), position);
}

/**
 * @tc.name: GetParagraphEndPosition001
 * @tc.desc: test GetParagraphEndPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetParagraphEndPosition001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t caretPosition = 10;
    AddSpan(EXCEPT_VALUE);
    auto iter = richEditorPattern->spans_.cbegin();
    auto span = *iter;
    ASSERT_NE(span, nullptr);
    int32_t position = span->position - static_cast<int32_t>(span->content.length());
    richEditorPattern->GetParagraphEndPosition(caretPosition);
    EXPECT_EQ(position, span->position - static_cast<int32_t>(span->content.length()));
    caretPosition = 1;
    richEditorPattern->GetParagraphEndPosition(caretPosition);
    EXPECT_EQ(position, span->position - static_cast<int32_t>(span->content.length()));
}

/**
 * @tc.name: GetLeftWordPosition001
 * @tc.desc: test GetLeftWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetLeftWordPosition001, TestSize.Level2)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->caretPosition_), 0);
    AddSpan(INIT_VALUE_1 + TEST_INSERT_LINE_SPACE);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->GetTextContentLength()), 0);
}

/**
 * @tc.name: GetLeftWordPosition002
 * @tc.desc: test GetLeftWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, GetLeftWordPosition002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan("hello1");
    int32_t res = richEditorPattern->GetLeftWordPosition(-9999);

    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: HandleOnEscape001
 * @tc.desc: test HandleOnEscape
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, HandleOnEscape001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->HandleOnEscape());
}

/**
 * @tc.name: ClearContent001
 * @tc.desc: test ClearContent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, ClearContent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    auto placeholderSpanItem = placeholderSpanNode->GetSpanItem();
    ASSERT_NE(placeholderSpanItem, nullptr);
    placeholderSpanItem->content = u" ";
    placeholderSpanNode->MountToParent(richEditorNode_);
    richEditorPattern->ClearContent(placeholderSpanNode);
    EXPECT_TRUE(placeholderSpanItem->content.empty());
}

/**
 * @tc.name: ConvertGlobalToTextOffset001
 * @tc.desc: test ConvertGlobalToTextOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, ConvertGlobalToTextOffset001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->richTextRect_ = RectF(50, 50, 100, 140);
    auto globalOffset = Offset(100, 100);
    auto textOffset = richEditorPattern->ConvertGlobalToTextOffset(globalOffset);
    ASSERT_EQ(textOffset, Offset(50, 50));
}

/**
 * @tc.name: AfterContentChange001
 * @tc.desc: test AfterContentChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, AfterContentChange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorNode_.Reset();
    RichEditorChangeValue changeValue;
    richEditorPattern->AfterContentChange(changeValue);
    EXPECT_EQ(richEditorNode_, nullptr);
}

/**
 * @tc.name: ReportAfterContentChangeEvent001
 * @tc.desc: Test ReportAfterContentChangeEvent non-span string mode with content added
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, ReportAfterContentChangeEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    std::string firstText = "abcd";
    AddSpan(firstText);
    std::string space = " ";
    std::string secondText = "content";
    AddSpan(space + secondText);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->textCache_ = "abcd";
    richEditorPattern->ReportAfterContentChangeEvent();
    EXPECT_EQ(richEditorPattern->textCache_, "abcd content");
}

/**
 * @tc.name: ReportAfterContentChangeEvent002
 * @tc.desc: Test ReportAfterContentChangeEvent in span mode with content removed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, ReportAfterContentChangeEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textCache_ = "nihaodajia";
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(PREVIEW_TEXT_VALUE1);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->ReportAfterContentChangeEvent();
    EXPECT_EQ(richEditorPattern->textCache_, "nihao");
}

/**
 * @tc.name: ReportAfterContentChangeEvent003
 * @tc.desc: Test ReportAfterContentChangeEvent non-span string mode with content modified
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, ReportAfterContentChangeEvent003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    std::string firstText = "abcd";
    AddSpan(firstText);
    std::string space = " ";
    std::string secondText = "content";
    AddSpan(space + secondText);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->textCache_ = "abcdefg";
    richEditorPattern->ReportAfterContentChangeEvent();
    EXPECT_EQ(richEditorPattern->textCache_, "abcd content");
}

/**
 * @tc.name: ClearContent002
 * @tc.desc: test ClearContent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, ClearContent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto child = SpanNode::GetOrCreateSpanNode(V2::SPAN_ETS_TAG, nodeId);
    richEditorPattern->ClearContent(child);
    EXPECT_EQ(child->spanItem_->content, u"");
}

/**
 * @tc.name: SetInputMethodStatus001
 * @tc.desc: test SetInputMethodStatus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, SetInputMethodStatus001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    richEditorPattern->SetInputMethodStatus(true);
    EXPECT_TRUE(richEditorPattern->imeShown_);
    richEditorPattern->SetInputMethodStatus(false);
    EXPECT_FALSE(richEditorPattern->imeShown_);
#endif
}

/**
 * @tc.name: RichEditorToJsonValue001
 * @tc.desc: test ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, RichEditorToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);

    auto jsonObject = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 0;
    filter.filterExt.clear();
    EXPECT_FALSE(filter.IsFastFilter());
    richEditorPattern->SetRequestKeyboardOnFocus(true);
    richEditorPattern->SetSupportStyledUndo(true);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    richEditorPattern->SetSupportPreviewText(false);
    richEditorPattern->SetEnableAutoSpacing(true);
    richEditorPattern->ToJsonValue(jsonObject, filter);
    EXPECT_EQ(jsonObject->GetString("enableKeyboardOnFocus"), "true");
    EXPECT_EQ(jsonObject->GetInt("undoStyle"), 1);
    EXPECT_EQ(jsonObject->GetInt("copyOptions"), 2);
    EXPECT_EQ(jsonObject->GetString("enablePreviewText"), "false");
    EXPECT_EQ(jsonObject->GetString("enableAutoSpacing"), "true");

    filter.filterFixed = 10;
    EXPECT_TRUE(filter.IsFastFilter());
    richEditorPattern->ToJsonValue(jsonObject, filter);
    EXPECT_FALSE(jsonObject->IsNull());
}

/**
 * @tc.name: FixMoveDownChange001
 * @tc.desc: test FixMoveDownChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, FixMoveDownChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. declare and init variables and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    span1.SetValue(u"test123");
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    span2.SetValue(u"test");
    changeValue.replacedSpans_.emplace_back(span2);
    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    int32_t firstLength = static_cast<int32_t>(firstInfo.GetValue().length());
    firstInfo.SetEraseLength(firstLength);
    auto spanIndex = firstInfo.GetSpanIndex();
    richEditorPattern->FixMoveDownChange(changeValue, 0);
    EXPECT_EQ(spanIndex, firstInfo.GetSpanIndex());
}

/**
 * @tc.name: IsLineSeparatorInLast001
 * @tc.desc: test IsLineSeparatorInLast
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorEditTestOneNg, IsLineSeparatorInLast001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanNode = AceType::MakeRefPtr<SpanNode>(1);
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanNode, nullptr);

    spanItem->content = u"ni\nhao";
    EXPECT_FALSE(richEditorPattern->IsLineSeparatorInLast(spanNode));

    spanItem->content = u"nihao\n";
    EXPECT_TRUE(richEditorPattern->IsLineSeparatorInLast(spanNode));
}

} // namespace OHOS::Ace::NG