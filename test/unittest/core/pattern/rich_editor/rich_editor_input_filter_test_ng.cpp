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

#include "test/unittest/core/pattern/rich_editor/rich_editor_styled_string_common_test_ng.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"
#include "core/common/ime/text_input_filter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string DIGIT_FILTER = "[0-9]";
const std::string LETTER_FILTER = "[a-z]";
const std::string ALL_FILTER = "[\\s\\S]";
const std::string ANCHORED_DIGIT_FILTER = "^[0-9]+$";
const std::u16string TEST_TEXT_MIXED = u"abc123";
const std::u16string TEST_TEXT_DIGITS = u"123";
const std::u16string TEST_TEXT_LETTERS = u"abc";
const std::u16string TEST_TEXT_EMPTY = u"";
// Grinning face emoji (U+1F600) as UTF-16 surrogate pair
constexpr char16_t EMOJI_GRINNING_HIGH = 0xD83D;
constexpr char16_t EMOJI_GRINNING_LOW = 0xDE00;
} // namespace

class RichEditorInputFilterTestNg : public RichEditorStyledStringCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<RichEditorPattern> GetPattern();
    RefPtr<RichEditorEventHub> GetEventHub();
    void SetInputFilter(const std::string& filter);
};

void RichEditorInputFilterTestNg::SetUp()
{
    RichEditorStyledStringCommonTestNg::SetUp();
}

void RichEditorInputFilterTestNg::TearDown()
{
    if (richEditorNode_) {
        auto eventHub = richEditorNode_->GetEventHub<RichEditorEventHub>();
        if (eventHub) {
            eventHub->SetOnInputFilterError(nullptr);
        }
    }
    RichEditorStyledStringCommonTestNg::TearDown();
}

RefPtr<RichEditorPattern> RichEditorInputFilterTestNg::GetPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

RefPtr<RichEditorEventHub> RichEditorInputFilterTestNg::GetEventHub()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetEventHub<RichEditorEventHub>();
}

void RichEditorInputFilterTestNg::SetInputFilter(const std::string& filter)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    RichEditorModelNG::SetInputFilter(AceType::RawPtr(richEditorNode_), filter);
}

// =============================================================================
// Minimal Test Suite — 18 tests covering all target function branches + key ACs
// =============================================================================

/**
 * @tc.name: InputFilterEventHub001
 * @tc.desc: Test SetOnInputFilterError and FireOnInputFilterError callback.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterEventHub001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto eventHub = GetEventHub();
    ASSERT_NE(eventHub, nullptr);
    std::u16string capturedError;
    bool callbackCalled = false;
    eventHub->SetOnInputFilterError(
        [&capturedError, &callbackCalled](const std::u16string& value) {
            capturedError = value;
            callbackCalled = true;
        });
    eventHub->FireOnInputFilterError(u"abc");
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedError, u"abc");
}

/**
 * @tc.name: InputFilterEventHub002
 * @tc.desc: Test FireOnInputFilterError returns early when callback is null.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterEventHub002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto eventHub = GetEventHub();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnInputFilterError(nullptr);
    eventHub->FireOnInputFilterError(u"test");
    // no crash — null callback path covered
}

/**
 * @tc.name: InputFilterEventHub004
 * @tc.desc: Test FireOnInputFilterError copy-before-call safety.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterEventHub004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto eventHub = GetEventHub();
    ASSERT_NE(eventHub, nullptr);
    bool callbackCalled = false;
    eventHub->SetOnInputFilterError(
        [&callbackCalled, &eventHub](const std::u16string&) {
            callbackCalled = true;
            eventHub->SetOnInputFilterError(nullptr);
        });
    eventHub->FireOnInputFilterError(u"test");
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: InputFilterModelNG001
 * @tc.desc: Test SetInputFilter + SetInputFilterError set property and callback.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterModelNG001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    bool callbackCalled = false;
    std::u16string capturedError;
    auto onError = [&callbackCalled, &capturedError](const std::u16string& value) {
        callbackCalled = true;
        capturedError = value;
    };
    RichEditorModelNG::SetInputFilter(AceType::RawPtr(richEditorNode_), DIGIT_FILTER);
    RichEditorModelNG::SetInputFilterError(AceType::RawPtr(richEditorNode_), onError);
    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetInputFilter().value_or(""), DIGIT_FILTER);
    auto eventHub = GetEventHub();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnInputFilterError(u"abc");
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedError, u"abc");
}

/**
 * @tc.name: InputFilterPattern001
 * @tc.desc: Test FilterWithInputFilter filters non-matching chars and fires error.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern001, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    auto eventHub = GetEventHub();
    ASSERT_NE(eventHub, nullptr);
    bool callbackCalled = false;
    std::u16string capturedError;
    eventHub->SetOnInputFilterError([&callbackCalled, &capturedError](const std::u16string& value) {
        callbackCalled = true;
        capturedError = value;
    });
    std::u16string text = TEST_TEXT_MIXED;
    pattern->FilterWithInputFilter(text);
    EXPECT_EQ(text, TEST_TEXT_DIGITS);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedError, TEST_TEXT_LETTERS);
}

/**
 * @tc.name: InputFilterPattern012
 * @tc.desc: Test FilterNonCharContent returns true when no filter is set.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern012, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    bool result = pattern->FilterNonCharContent();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: InputFilterPattern013
 * @tc.desc: Test FilterNonCharContent fires error callback when rejected.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern013, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    auto eventHub = GetEventHub();
    ASSERT_NE(eventHub, nullptr);
    bool callbackCalled = false;
    std::u16string capturedError;
    eventHub->SetOnInputFilterError([&callbackCalled, &capturedError](const std::u16string& value) {
        callbackCalled = true;
        capturedError = value;
    });
    bool result = pattern->FilterNonCharContent();
    EXPECT_FALSE(result);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedError, u"\uFFFC");
}

/**
 * @tc.name: InputFilterPattern014
 * @tc.desc: Test FilterStyledStringBeforeInsert filters content from MutableSpanString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern014, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<MutableSpanString>(TEST_TEXT_MIXED);
    pattern->FilterStyledStringBeforeInsert(spanString);
    ASSERT_NE(spanString, nullptr);
    EXPECT_EQ(spanString->GetU16string(), TEST_TEXT_DIGITS);
}

/**
 * @tc.name: InputFilterPattern016
 * @tc.desc: Test FilterStyledStringBeforeInsert creates mutable copy for immutable SpanString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern016, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(TEST_TEXT_MIXED);
    ASSERT_NE(spanString, nullptr);
    auto beforeMutable = AceType::DynamicCast<MutableSpanString>(spanString);
    EXPECT_EQ(beforeMutable, nullptr);
    pattern->FilterStyledStringBeforeInsert(spanString);
    ASSERT_NE(spanString, nullptr);
    auto afterMutable = AceType::DynamicCast<MutableSpanString>(spanString);
    EXPECT_NE(afterMutable, nullptr);
    EXPECT_EQ(spanString->GetU16string(), TEST_TEXT_DIGITS);
}

/**
 * @tc.name: InputFilterPattern017
 * @tc.desc: Test FilterStyledStringBeforeInsert does not crash with null spanString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern017, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    RefPtr<SpanString> spanString = nullptr;
    pattern->FilterStyledStringBeforeInsert(spanString);
    EXPECT_EQ(spanString, nullptr);
}

/**
 * @tc.name: InputFilterPattern018
 * @tc.desc: Test FilterStyledStringBeforeInsert does not crash with empty content.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern018, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<MutableSpanString>(TEST_TEXT_EMPTY);
    pattern->FilterStyledStringBeforeInsert(spanString);
    ASSERT_NE(spanString, nullptr);
    EXPECT_EQ(spanString->GetU16string(), TEST_TEXT_EMPTY);
}

/**
 * @tc.name: InputFilterPattern026
 * @tc.desc: Test FilterInitializeText does not crash with null styledString.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern026, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    pattern->styledString_ = nullptr;
    pattern->FilterInitializeText();
    EXPECT_EQ(pattern->styledString_, nullptr);
}

/**
 * @tc.name: InputFilterPattern027
 * @tc.desc: Test FilterInitializeText returns false when content is empty.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern027, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    pattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(TEST_TEXT_EMPTY);
    pattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(pattern)));
    bool result = pattern->FilterInitializeText();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: InputFilterPattern028
 * @tc.desc: Test FilterInitializeText returns false when content unchanged (all matches).
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern028, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(ALL_FILTER);
    pattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(TEST_TEXT_DIGITS);
    pattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(pattern)));
    bool result = pattern->FilterInitializeText();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern->styledString_->GetU16string(), TEST_TEXT_DIGITS);
}

/**
 * @tc.name: InputFilterPattern029
 * @tc.desc: Test FilterInitializeText returns true when content changed (partial filter).
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern029, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    auto eventHub = GetEventHub();
    ASSERT_NE(eventHub, nullptr);
    bool callbackCalled = false;
    eventHub->SetOnInputFilterError([&callbackCalled](const std::u16string&) {
        callbackCalled = true;
    });
    pattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(TEST_TEXT_MIXED);
    pattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(pattern)));
    bool result = pattern->FilterInitializeText();
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern->styledString_->GetU16string(), TEST_TEXT_DIGITS);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: InputFilterPattern030
 * @tc.desc: Test FilterInitializeText restore path: inserted text doesn't match anchored regex.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern030, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(ANCHORED_DIGIT_FILTER);
    auto eventHub = GetEventHub();
    ASSERT_NE(eventHub, nullptr);
    bool callbackCalled = false;
    std::u16string capturedError;
    eventHub->SetOnInputFilterError([&callbackCalled, &capturedError](const std::u16string& value) {
        callbackCalled = true;
        capturedError = value;
    });
    pattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"123abc");
    pattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(pattern)));
    bool result = pattern->FilterInitializeText(u"123");
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern->styledString_->GetU16string(), u"123");
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(capturedError, u"abc");
}

/**
 * @tc.name: InputFilterPattern031
 * @tc.desc: Test FilterStyledStringBeforeInsert returns early when no filter set.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern031, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<MutableSpanString>(TEST_TEXT_MIXED);
    pattern->FilterStyledStringBeforeInsert(spanString);
    EXPECT_EQ(spanString->GetU16string(), TEST_TEXT_MIXED);
}

/**
 * @tc.name: InputFilterPattern032
 * @tc.desc: Test PrepareFilter uses cached filter on second call (filterDirty_ = false).
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPattern032, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    std::u16string text1 = u"abc123";
    pattern->FilterWithInputFilter(text1);
    EXPECT_EQ(text1, u"123");
    // Second call: filterDirty_ is now false — PrepareFilter returns true without re-reading
    std::u16string text2 = u"xyz456";
    pattern->FilterWithInputFilter(text2);
    EXPECT_EQ(text2, u"456");
}

/**
 * @tc.name: InputFilterPriority001
 * @tc.desc: AC-9/R-8: Filter removes letters first, then maxLength truncates remaining digits.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterPriority001, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    pattern->maxLength_ = 3;
    pattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    pattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(pattern)));
    std::u16string value = u"abc123456";
    pattern->FilterWithInputFilter(value);
    EXPECT_EQ(value, u"123456");
    auto length = pattern->CalculateTruncationLength(value, 3);
    EXPECT_EQ(length, 3);
    EXPECT_EQ(value.substr(0, length), u"123");
}

/**
 * @tc.name: InputFilterNewline001
 * @tc.desc: AC-11/R-9: FilterWithInputFilter removes \n when regex doesn't match it.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterNewline001, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    std::u16string value = u"1\n2\n3";
    pattern->FilterWithInputFilter(value);
    EXPECT_EQ(value, u"123");
}

/**
 * @tc.name: InputFilterEmojiMerge001
 * @tc.desc: AC-16/R-26: FilterSpanString merges adjacent rejected surrogate pair.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterEmojiMerge001, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(LETTER_FILTER);
    auto eventHub = GetEventHub();
    ASSERT_NE(eventHub, nullptr);
    bool callbackCalled = false;
    std::u16string capturedError;
    eventHub->SetOnInputFilterError([&callbackCalled, &capturedError](const std::u16string& value) {
        callbackCalled = true;
        capturedError = value;
    });
    std::u16string content = u"a";
    content.push_back(EMOJI_GRINNING_HIGH);
    content.push_back(EMOJI_GRINNING_LOW);
    content.append(u"b");
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(content);
    auto onError = pattern->MakeFilterErrorHandler();
    ASSERT_NE(onError, nullptr);
    pattern->filterManager_.SetFilter(u"[a-z]");
    pattern->filterManager_.FilterSpanString(spanString, content, onError);
    EXPECT_EQ(spanString->GetU16string(), u"ab");
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: InputFilterSerial001
 * @tc.desc: AC-17/R-27: Filter removes emoji first, then maxLength truncates remaining text.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterSerial001, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(LETTER_FILTER);
    pattern->maxLength_ = 2;
    std::u16string content = u"a";
    content.push_back(EMOJI_GRINNING_HIGH);
    content.push_back(EMOJI_GRINNING_LOW);
    content.append(u"bcd");
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(content);
    auto onError = pattern->MakeFilterErrorHandler();
    ASSERT_NE(onError, nullptr);
    pattern->filterManager_.SetFilter(u"[a-z]");
    pattern->filterManager_.FilterSpanString(spanString, content, onError);
    EXPECT_EQ(spanString->GetU16string(), u"abcd");
    auto filtered = spanString->GetU16string();
    auto length = pattern->CalculateTruncationLength(filtered, 2);
    EXPECT_EQ(filtered.substr(0, length), u"ab");
}

/**
 * @tc.name: InputFilterIntegration016
 * @tc.desc: After ResetInputFilter, filtering functions become no-op (filterDirty_ invalidated).
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorInputFilterTestNg, InputFilterIntegration016, TestSize.Level0)
{
    auto pattern = GetPattern();
    ASSERT_NE(pattern, nullptr);
    SetInputFilter(DIGIT_FILTER);
    std::u16string text = u"abc123";
    pattern->FilterWithInputFilter(text);
    EXPECT_EQ(text, u"123");
    RichEditorModelNG::ResetInputFilter(AceType::RawPtr(richEditorNode_));
    std::u16string text2 = u"abc123";
    pattern->FilterWithInputFilter(text2);
    EXPECT_EQ(text2, u"abc123");
    EXPECT_TRUE(pattern->FilterNonCharContent());
    EXPECT_FALSE(pattern->FilterInitializeText());
}

} // namespace OHOS::Ace::NG
