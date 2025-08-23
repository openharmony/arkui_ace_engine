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

#include <utility>
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
enum class SpanType {
    TEXT,
    SYMBOL,
    IMAGE,
    BUILDER
};
namespace {
const std::vector<std::u16string> INSERT_VALUE_LIST = {
    u"哈哈哈haha123",
    u"\n哈哈哈haha123",
    u"哈哈哈\nhaha123",
    u"哈哈哈haha123\n",
    u"\n哈哈哈\nhaha123",
    u"\n哈哈哈haha123\n",
    u"哈哈哈\nhaha123\n",
    u"\n哈哈哈\nhaha123\n",
};
const auto BUILDER_NODE_1 = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(),
    []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
const std::unordered_map<SpanType, std::function<void(RefPtr<RichEditorPattern>)>> SPAN_CONSTRUCTOR_MAP = {
    { SpanType::TEXT, [](RefPtr<RichEditorPattern> pattern) { pattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);} },
    { SpanType::IMAGE, [](RefPtr<RichEditorPattern> pattern) { pattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);} },
    { SpanType::SYMBOL, [](RefPtr<RichEditorPattern> pattern) { pattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);} },
    { SpanType::BUILDER, [](RefPtr<RichEditorPattern> pattern) { pattern->AddPlaceholderSpan(BUILDER_NODE_1, {});} }
};
int32_t testSpanNodeId = 1;
int32_t testNumber5 = 5;
} // namespace

class RichEditorSpanTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    template<typename... Args>
    void InitSpans(Args... args);
    template<typename T, typename... Args>
    void ConstructSpans(RefPtr<RichEditorPattern> pattern, T value, Args... args);
    void ConstructSpans(RefPtr<RichEditorPattern> pattern) {}
    static void TearDownTestSuite();
};

void RichEditorSpanTest::SetUp()
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

void RichEditorSpanTest::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorSpanTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

template<typename... Args>
void RichEditorSpanTest::InitSpans(Args... args)
{
    RichEditorCommonTestNg::ClearSpan();
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ConstructSpans(pattern, args...);
}

template<typename T, typename... Args>
void RichEditorSpanTest::ConstructSpans(RefPtr<RichEditorPattern> pattern, T value, Args... args)
{
    if constexpr (std::is_same_v<T, std::string>) {
        pattern->AddTextSpan({ .value = value });
    } else if constexpr (std::is_same_v<T, SpanType>) {
        auto it = SPAN_CONSTRUCTOR_MAP.find(value);
        (it->second)(pattern);
    }
    ConstructSpans(pattern, args...);
}

/**
 * @tc.name: RichEditorSpanTestTextText001
 * @tc.desc: test span num [text-text]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestTextText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 6;
        InitSpans(SpanType::TEXT, SpanType::TEXT); // [hello1][hello1]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);
}

/**
 * @tc.name: RichEditorSpanTestTextImage001
 * @tc.desc: test span num [text-image]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestTextImage001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 6;
        InitSpans(SpanType::TEXT, SpanType::IMAGE); // hello1[image]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);
}

/**
 * @tc.name: RichEditorSpanTestTextBuilder001
 * @tc.desc: test span num [text-builder]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestTextBuilder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    
    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 6;
        InitSpans(SpanType::TEXT, SpanType::BUILDER); // hello1[builder]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);
}

/**
 * @tc.name: RichEditorSpanTestTextSymbol001
 * @tc.desc: test span num [text-symbol]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestTextSymbol001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 6;
        InitSpans(SpanType::TEXT, SpanType::SYMBOL); // hello1[symbol]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);
}

/**
 * @tc.name: RichEditorSpanTestImageText001
 * @tc.desc: test span num [image-text]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestImageText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::IMAGE, SpanType::TEXT); // [image]hello1
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3); // fail
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestImageImage001
 * @tc.desc: test span num [image-image]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestImageImage001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::IMAGE, SpanType::IMAGE); // [image][image]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestImageBuilder001
 * @tc.desc: test span num [image-builder]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestImageBuilder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::IMAGE, SpanType::BUILDER); // [image][builder]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestImageSymbol001
 * @tc.desc: test span num [image-symbol]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestImageSymbol001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::IMAGE, SpanType::SYMBOL); // [image][symbol]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestBuilderText001
 * @tc.desc: test span num [builder-text]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestBuilderText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::BUILDER, SpanType::TEXT); // [builder]hello1
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3); // fail
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestBuilderImage001
 * @tc.desc: test span num [builder-image]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestBuilderImage001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::BUILDER, SpanType::IMAGE); // [builder][image]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestBuilderBuilder001
 * @tc.desc: test span num [builder-builder]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestBuilderBuilder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::BUILDER, SpanType::BUILDER); // [builder][builder]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestBuilderSymbol001
 * @tc.desc: test span num [builder-symbol]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestBuilderSymbol001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::BUILDER, SpanType::SYMBOL); // [builder][symbol]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestSymbolText001
 * @tc.desc: test span num [symbol-text]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestSymbolText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 2;
        InitSpans(SpanType::SYMBOL, SpanType::TEXT); // [symbol]hello1
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3); // fail
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestSymbolImage001
 * @tc.desc: test span num [symbol-image]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestSymbolImage001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 2;
        InitSpans(SpanType::SYMBOL, SpanType::IMAGE); // [symbol][image]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestSymbolBuilder001
 * @tc.desc: test span num [symbol-builder]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestSymbolBuilder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 2;
        InitSpans(SpanType::SYMBOL, SpanType::BUILDER); // [symbol][builder]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestSymbolSymbol001
 * @tc.desc: test span num [symbol-symbol]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestSymbolSymbol001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 2;
        InitSpans(SpanType::SYMBOL, SpanType::SYMBOL); // [symbol][symbol]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: IsSelectAll001
 * @tc.desc: test IsSelectAll001
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, IsSelectAll001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitSpans(SpanType::TEXT, SpanType::IMAGE,
        SpanType::TEXT, SpanType::SYMBOL,
        SpanType::TEXT, SpanType::BUILDER,
        SpanType::TEXT);
    auto contentLength = richEditorPattern->GetTextContentLength();
    richEditorPattern->UpdateSelector(0, contentLength);
    EXPECT_EQ(richEditorPattern->IsSelectAll(), true);
}

/**
 * @tc.name: GetDelPartiallySpanItem001
 * @tc.desc: test GetDelPartiallySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, GetDelPartiallySpanItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.clear();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem1 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem1);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem2);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem> spanItem3 = AceType::MakeRefPtr<ImageSpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem3);
    RichEditorChangeValue changeValue;
    RichEditorAbstractSpanResult span1;
    changeValue.originalSpans_.emplace_back(span1);
    RichEditorAbstractSpanResult span2;
    changeValue.originalSpans_.emplace_back(span2);
    RichEditorAbstractSpanResult& firstInfo = changeValue.originalSpans_.front();
    firstInfo.SetValue(u"");
    RichEditorAbstractSpanResult& lastInfo = changeValue.originalSpans_.back();
    lastInfo.SetValue(u"test123\n");
    int32_t lastLength = static_cast<int32_t>(lastInfo.GetValue().length());
    lastInfo.SetEraseLength(lastLength - 1);
    std::u16string originalStr;
    int32_t originalPos = 0;
    auto ret = richEditorPattern->GetDelPartiallySpanItem(changeValue, originalStr, originalPos);
    auto it = richEditorPattern->spans_.front();
    EXPECT_NE(ret.first, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    int32_t firstLength = static_cast<int32_t>(firstInfo.GetValue().length());
    firstInfo.SetEraseLength(firstLength);
    lastLength = static_cast<int32_t>(lastInfo.GetValue().length());
    lastInfo.SetEraseLength(lastLength);
    ret = richEditorPattern->GetDelPartiallySpanItem(changeValue, originalStr, originalPos);
    EXPECT_EQ(ret.first, nullptr);
}

/**
 * @tc.name: GetSameSpanItem001
 * @tc.desc: test GetSameSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, GetSameSpanItem001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    spanItem->spanItemType = SpanItemType::IMAGE;
    auto childNode = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 2);
    childNode->imageSpanItem_ = spanItem;
    contentNode->children_.emplace_back(childNode);
    auto image = AceType::MakeRefPtr<MockCanvasImage>();
    auto imageNode = richEditorPattern->GetImageSpanNodeBySpanItem(spanItem);
    auto pattern = imageNode->GetPattern<ImagePattern>();
    pattern->image_ = image;
    auto pixelMap = image->GetPixelMap();
    richEditorPattern->GetSameSpanItem(spanItem);
    EXPECT_FALSE(pixelMap);
}

/**
 * @tc.name: GetSameSpanItem002
 * @tc.desc: test GetSameSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, GetSameSpanItem002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    spanItem->spanItemType = SpanItemType::IMAGE;
    auto childNode = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, 2);
    childNode->imageSpanItem_ = spanItem;
    contentNode->children_.emplace_back(childNode);
    auto image = AceType::MakeRefPtr<MockCanvasImage>();
    image->needPixelMap = true;
    auto imageNode = richEditorPattern->GetImageSpanNodeBySpanItem(spanItem);
    auto pattern = imageNode->GetPattern<ImagePattern>();
    pattern->image_ = image;
    auto pixelMap = image->GetPixelMap();
    richEditorPattern->GetSameSpanItem(spanItem);
    EXPECT_TRUE(pixelMap);
}

/**
 * @tc.name: RichEditorPatternTestInsertDiffStyleValueInSpan001
 * @tc.desc: test InsertDiffStyleValueInSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorPatternTestInsertDiffStyleValueInSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanNode = AceType::MakeRefPtr<SpanNode>(testSpanNodeId);
    ASSERT_NE(spanNode, nullptr);

    TextInsertValueInfo info;
    std::u16string insertValue;
    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);

    richEditorPattern->InsertDiffStyleValueInSpan(spanNode, info, insertValue);
    ASSERT_EQ(richEditorPattern->moveLength_, 0);
}

/**
 * @tc.name: GetReplacedSpan001
 * @tc.desc: test GetReplacedSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, GetReplacedSpan001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);

    richEditorPattern->spans_.clear();
    host->children_.clear();
    auto textframeNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textframeNode, nullptr);
    host->AddChild(textframeNode);
    textframeNode->SetParent(host);
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(imageSpanNode, nullptr);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);

    RichEditorChangeValue changeValue;
    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;
    int32_t innerPosition = 0;
    std::u16string insertValue = u"test123\n123";
    int32_t textIndex = 1;
    std::optional<TextStyle> textStyle = std::optional<TextStyle>(TextStyle());
    richEditorPattern->GetReplacedSpan(
        changeValue, innerPosition, insertValue, textIndex, textStyle, spanParaStyle, std::nullopt, false, false);
    auto uiNode = host->GetChildAtIndex(0);
    EXPECT_NE(uiNode, nullptr);
    EXPECT_EQ(uiNode->GetTag(), V2::TEXT_ETS_TAG);
}

/**
 * @tc.name: GetReplacedSpanFission001
 * @tc.desc: test GetReplacedSpanFission
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, GetReplacedSpanFission001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorChangeValue changeValue;
    int32_t innerPosition = 0;
    std::u16string content = u"test123\n";
    int32_t startSpanIndex = 0;
    int32_t offsetInSpan = 0;
    std::optional<TextStyle> textStyle = std::optional<TextStyle>(TextStyle());
    struct UpdateParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = TextAlign::END;
    paragraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
    paragraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, paragraphStyle);
    std::optional<struct UpdateParagraphStyle> spanParaStyle = paragraphStyle;
    std::optional<std::u16string> urlAddress = std::nullopt;
    richEditorPattern->GetReplacedSpanFission(
        changeValue, innerPosition, content, startSpanIndex, offsetInSpan, textStyle, spanParaStyle, urlAddress);
    EXPECT_NE(innerPosition, 0);
}

/**
 * @tc.name: ToGestureSpan001
 * @tc.desc: test ToGestureSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, ToGestureSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();

    spanItem->onClick = [](GestureEvent& info) {};
    spanItem->onLongPress = [](GestureEvent& info) {};

    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);
    auto start = spanItem->position - spanItem->content.length();
    auto end = spanItem->position;
    EXPECT_NE(spanString->ToGestureSpan(spanItem, start, end), nullptr);
}

/**
 * @tc.name: ToBaselineOffsetSpan001
 * @tc.desc: test ToBaselineOffsetSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, ToBaselineOffsetSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->textLineStyle->UpdateBaselineOffset(Dimension(testNumber5, DimensionUnit::PX));
    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);
    auto start = spanItem->position - spanItem->content.length();
    auto end = spanItem->position;
    EXPECT_NE(spanString->ToBaselineOffsetSpan(spanItem, start, end), nullptr);
}

/**
 * @tc.name: ToTextShadowSpan001
 * @tc.desc: test ToTextShadowSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, ToTextShadowSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    Shadow textShadow1 = Shadow();
    Shadow textShadow2 = Shadow();
    textShadow1.SetColor(Color::RED);
    textShadow2.SetColor(Color::WHITE);
    std::vector<Shadow> shadows { textShadow1, textShadow2 };
    spanItem->fontStyle->UpdateTextShadow(shadows);
    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);
    auto start = spanItem->position - spanItem->content.length();
    auto end = spanItem->position;
    EXPECT_NE(spanString->ToTextShadowSpan(spanItem, start, end), nullptr);
}

/**
 * @tc.name: CreateImageSourceInfo001
 * @tc.desc: test CreateImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, CreateImageSourceInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateEventHub();
    ImageSpanOptions options;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    options.imagePixelMap = pixelMap;
    richEditorPattern->CreateImageSourceInfo(options);
    EXPECT_EQ(options.imagePixelMap.has_value(), true);
}

/**
 * @tc.name: InsertSpanByBackData001
 * @tc.desc: test InsertSpanByBackData
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, InsertSpanByBackData001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto spanString = AceType::MakeRefPtr<SpanString>(u"");
    richEditorPattern->textSelector_ = TextSelector(0, 6);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
    richEditorPattern->InsertSpanByBackData(spanString);
    EXPECT_FALSE(richEditorPattern->textSelector_.IsValid());
    richEditorPattern->ClearOperationRecords();

    richEditorPattern->placeholderSpansMap_[u"![id1]"] = AceType::MakeRefPtr<SpanItem>();
    spanString = AceType::MakeRefPtr<SpanString>(u"test![id1]");
    auto start = richEditorPattern->operationRecords_.size();
    richEditorPattern->InsertSpanByBackData(spanString);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 2);
    richEditorPattern->ClearOperationRecords();
}

/**
 * @tc.name: AddTextSpan001
 * @tc.desc: test AddTextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, AddTextSpan001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextSpanOptions options;
    richEditorPattern->previewTextRecord_.previewContent = u"123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    EXPECT_EQ(richEditorPattern->previewTextRecord_.IsValid(), true);
    int32_t res = richEditorPattern->AddTextSpan(options, TextChangeReason::UNKNOWN, true, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: AddTextSpan001
 * @tc.desc: test AddTextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, PlaceholderSpanNodeTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    ASSERT_NE(placeholderSpanNode, nullptr);
    auto placeholderSpanItem = placeholderSpanNode->GetSpanItem();
    ASSERT_NE(placeholderSpanItem, nullptr);
    auto placeholderSpanPattern = placeholderSpanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderSpanPattern, nullptr);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    DirtySwapConfig config = { .frameSizeChange = true };

    placeholderSpanItem->needReLayout = false;
    placeholderSpanPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(placeholderSpanItem->needReLayout, true);
}

} // namespace OHOS::Ace::NG