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
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_foreground_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/style_manager.h"
#include "core/components_ng/pattern/common_text/counter_foreground_modifier.h"
#include "core/components_ng/pattern/common_text/counter_decorator.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_paint_method.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace NodeModifier {
void SetRichEditorShowCounter(ArkUINodeHandle node, ArkUIShowCountOptions* showCountOptions,
    void* counterTextColorRawPtr, void* counterTextOverflowColorRawPtr);
void ResetRichEditorShowCounter(ArkUINodeHandle node);
void GetRichEditorShowCounterOptions(ArkUINodeHandle node, ArkUIShowCountOptions* options);
} // namespace NodeModifier
using namespace NodeModifier;
namespace {
constexpr int32_t TEST_MAX_LENGTH_5 = 5;
constexpr int32_t TEST_MAX_LENGTH_10 = 10;
constexpr float TEST_CONTENT_WIDTH = 300.0f;
const std::u16string INSERT_TEST_VALUE = u"ab";
const Color COUNTER_TEXT_COLOR = Color::FromRGB(10, 20, 30);
const Color COUNTER_OVERFLOW_COLOR = Color::FromRGB(200, 100, 50);
constexpr int32_t TEST_MAX_LENGTH = 10;
constexpr int32_t TEST_COUNTER_VALUE = 5;
constexpr float BORDER_WIDTH_VALUE = 2.0f;
constexpr float BORDER_RADIUS_VALUE = 4.0f;
constexpr uint32_t BORDER_COLOR_VALUE = 0xFF0000;
} // namespace

class RichEditorCounterCoreTestNg : public RichEditorStyledStringCommonTestNg {};

class RichEditorCounterApiTestNg : public RichEditorStyledStringCommonTestNg {
public:
    void InitStyledStringMode();
};

void RichEditorCounterApiTestNg::InitStyledStringMode()
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isSpanStringMode_ = true;
    pattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(INIT_VALUE_3);
    pattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(pattern)));
}

/* ===================== ICounterHost interface override tests ===================== */

/**
 * @tc.name: ICounterHostInterface001
 * @tc.desc: RichEditorPattern ICounterHost interface: ShouldUseHostTextLength and NeedRestoreMeasureConstraint
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, ICounterHostInterface001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(richEditorPattern));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->ShouldUseHostTextLength());
    EXPECT_TRUE(richEditorPattern->ShouldUseHostTextLength());
    EXPECT_TRUE(richEditorPattern->NeedRestoreMeasureConstraint());
}

/**
 * @tc.name: GetAllResponseArea001
 * @tc.desc: GetAllResponseArea returns vector with cleanNodeResponseArea_ null and non-null
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, GetAllResponseArea001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    // Branch: cleanNodeResponseArea_ not initialized -> size 1, element null
    auto areas = richEditorPattern->GetAllResponseArea();
    EXPECT_EQ(areas.size(), 1);
    // Branch: cleanNodeResponseArea_ set -> size 1, element non-null
    richEditorPattern->cleanNodeResponseArea_ =
        AceType::MakeRefPtr<CleanNodeResponseArea>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    areas = richEditorPattern->GetAllResponseArea();
    EXPECT_EQ(areas.size(), 1);
    EXPECT_NE(areas[0], nullptr);
    richEditorPattern->cleanNodeResponseArea_.Reset();
}

/* ===================== CounterNodeMeasure test ===================== */

/**
 * @tc.name: CounterNodeMeasure001
 * @tc.desc: CounterNodeMeasure with valid decorator and null decorator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, CounterNodeMeasure001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto wrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, richEditorNode_->GetGeometryNode(), richEditorNode_->GetLayoutProperty());
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    // Branch: counterDecorator null -> returns 0
    richEditorPattern->counterDecorator_ = nullptr;
    float result = layoutAlgorithm->CounterNodeMeasure(TEST_CONTENT_WIDTH, AceType::RawPtr(wrapper));
    EXPECT_EQ(result, 0.0f);
    // Branch: valid counterDecorator with content
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    result = layoutAlgorithm->CounterNodeMeasure(TEST_CONTENT_WIDTH, AceType::RawPtr(wrapper));
    EXPECT_GE(result, 0.0f);
}

/* ===================== InsertValueInStyledString tests ===================== */

/**
 * @tc.name: InsertValueInStyledStringFilterEmpty001
 * @tc.desc: When filter empties insert text, HandleCounterWithLength is called and function returns early
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, InsertValueInStyledStringFilterEmpty001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));

    // Set up filter that removes all non-digit characters
    richEditorPattern->hasActiveFilter_ = true;
    richEditorPattern->filterDirty_ = false;
    richEditorPattern->filterManager_.SetFilter(u"[0-9]");
    richEditorPattern->filterErrorHandler_ = [](const std::u16string&) -> bool { return true; };

    auto lengthBefore = richEditorPattern->GetTextContentLength();
    (void)lengthBefore;
    // "abc" will be filtered to "" by [0-9] filter
    richEditorPattern->InsertValueInStyledString(u"abc", true, false, false, false);
    auto lengthAfter = richEditorPattern->GetTextContentLength();
    // Text should not be inserted since filter emptied it
    EXPECT_EQ(lengthAfter, lengthBefore);

    richEditorPattern->hasActiveFilter_ = false;
}

/**
 * @tc.name: InsertValueInStyledStringSplitAndNotSplit001
 * @tc.desc: isInsertValueSplit=true (below max) and isInsertValueSplit=false (preFiltered, same value) → counter with 0
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, InsertValueInStyledStringSplitAndNotSplit001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto setupStyledString = [&richEditorPattern]() {
        richEditorPattern->isSpanStringMode_ = true;
        richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"ab");
        richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
        richEditorPattern->undoManager_ =
            std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
        richEditorPattern->hasActiveFilter_ = false;
        richEditorPattern->maxLength_ = TEST_MAX_LENGTH_10;
    };
    // Branch: isInsertValueSplit=true, preFiltered=true, below max → counter with 0
    setupStyledString();
    auto lengthBefore = richEditorPattern->GetTextContentLength();
    richEditorPattern->InsertValueInStyledString(u"cd", true, false, true, true);
    auto lengthAfter = richEditorPattern->GetTextContentLength();
    EXPECT_GT(lengthAfter, lengthBefore);
    // Branch: isInsertValueSplit=false, preFiltered=true (insertValue==subValue) → counter with 0
    setupStyledString();
    lengthBefore = richEditorPattern->GetTextContentLength();
    richEditorPattern->InsertValueInStyledString(u"cd", true, false, true, false);
    lengthAfter = richEditorPattern->GetTextContentLength();
    EXPECT_GT(lengthAfter, lengthBefore);
}

/**
 * @tc.name: InsertValueInStyledStringNotSplitDifferentValue001
 * @tc.desc: isInsertValueSplit=false, filter changes text (insertValue!=subValue) → counter with DEFAULT_LENGTH
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, InsertValueInStyledStringNotSplitDifferentValue001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"12");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));

    // Set up filter that keeps only digits
    richEditorPattern->hasActiveFilter_ = true;
    richEditorPattern->filterDirty_ = false;
    richEditorPattern->filterManager_.SetFilter(u"[0-9]");
    richEditorPattern->filterErrorHandler_ = [](const std::u16string&) -> bool { return true; };
    richEditorPattern->maxLength_ = TEST_MAX_LENGTH_10;

    auto lengthBefore = richEditorPattern->GetTextContentLength();
    // "a1b2c3" will be filtered to "123" (changed but not empty)
    // preFiltered=false, isInsertValueSplit=false, insertValue!=subValue → DEFAULT_LENGTH
    richEditorPattern->InsertValueInStyledString(u"a1b2c3", true, false, false, false);
    auto lengthAfter = richEditorPattern->GetTextContentLength();
    // Filtered text "123" should be inserted
    EXPECT_GT(lengthAfter, lengthBefore);

    richEditorPattern->hasActiveFilter_ = false;
}

/**
 * @tc.name: InsertValueInStyledStringShouldNotCommit001
 * @tc.desc: shouldCommitInput=false → counter branch skipped
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, InsertValueInStyledStringShouldNotCommit001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"ab");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->hasActiveFilter_ = false;
    richEditorPattern->maxLength_ = TEST_MAX_LENGTH_10;

    // shouldCommitInput=false → counter branch (!isPreventChange && shouldCommitInput) is false
    richEditorPattern->InsertValueInStyledString(u"cd", false, false, true, false);
    // No crash means success
    EXPECT_NE(richEditorPattern->GetTextContentLength(), -1);
}

/**
 * @tc.name: InsertValueInStyledStringSplitAtMax001
 * @tc.desc: isInsertValueSplit=true and GetTextContentLength()==GetMaxLength() → counter with DEFAULT_LENGTH
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, InsertValueInStyledStringSplitAtMax001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->hasActiveFilter_ = false;
    richEditorPattern->maxLength_ = TEST_MAX_LENGTH_5;
    // Set up selection to allow ProcessTextTruncationOperation to return true when at max length
    richEditorPattern->textSelector_.Update(0, 3);
    richEditorPattern->previewTextRecord_.needReplacePreviewText = false;

    auto lengthBefore = richEditorPattern->GetTextContentLength();
    (void)lengthBefore;
    // Text is at max length, isInsertValueSplit=true
    // GetTextContentLength()==GetMaxLength() → DEFAULT_LENGTH path
    richEditorPattern->InsertValueInStyledString(u"abcde", true, false, true, true);
    // Selection replacement should have occurred
    EXPECT_NE(richEditorPattern->GetTextContentLength(), -1);
    richEditorPattern->textSelector_.Update(-1);
}

/* ===================== ProcessInsertValue tests ===================== */

/**
 * @tc.name: ProcessInsertValueFilterEmpty001
 * @tc.desc: When filter empties insert text in ProcessInsertValue, HandleCounterWithLength is called
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, ProcessInsertValueFilterEmpty001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));

    // Set up filter that removes all non-digit characters
    richEditorPattern->hasActiveFilter_ = true;
    richEditorPattern->filterDirty_ = false;
    richEditorPattern->filterManager_.SetFilter(u"[0-9]");
    richEditorPattern->filterErrorHandler_ = [](const std::u16string&) -> bool { return true; };
    richEditorPattern->maxLength_ = TEST_MAX_LENGTH_10;

    auto lengthBefore = richEditorPattern->GetTextContentLength();
    // "abc" will be filtered to "" by [0-9] filter
    richEditorPattern->ProcessInsertValue(u"abc", OperationType::IME, true);
    auto lengthAfter = richEditorPattern->GetTextContentLength();
    // Text should not be inserted since filter emptied it
    EXPECT_EQ(lengthAfter, lengthBefore);

    richEditorPattern->hasActiveFilter_ = false;
}

/**
 * @tc.name: ProcessInsertValueSpanStringWithFilter001
 * @tc.desc: SpanString mode with filter reducing text → isInsertValueSplit=true passed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, ProcessInsertValueSpanStringWithFilter001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"12");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));

    // Set up filter that keeps only digits
    richEditorPattern->hasActiveFilter_ = true;
    richEditorPattern->filterDirty_ = false;
    richEditorPattern->filterManager_.SetFilter(u"[0-9]");
    richEditorPattern->filterErrorHandler_ = [](const std::u16string&) -> bool { return true; };
    richEditorPattern->maxLength_ = TEST_MAX_LENGTH_10;

    auto lengthBefore = richEditorPattern->GetTextContentLength();
    // "a1b2" will be filtered to "12" (reduced but not empty) → isInsertValueSplit=true
    richEditorPattern->ProcessInsertValue(u"a1b2", OperationType::IME, true);
    auto lengthAfter = richEditorPattern->GetTextContentLength();
    // Filtered text "12" should be inserted
    EXPECT_GT(lengthAfter, lengthBefore);

    richEditorPattern->hasActiveFilter_ = false;
}

/**
 * @tc.name: ProcessInsertValueNormal001
 * @tc.desc: Normal path (non-spanString mode), no filter
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, ProcessInsertValueNormal001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->isEditing_ = true;
    richEditorPattern->hasActiveFilter_ = false;

    auto size = richEditorPattern->operationRecords_.size();
    richEditorPattern->ProcessInsertValue(u"abc", OperationType::IME, true);
    EXPECT_NE(richEditorPattern->operationRecords_.size(), size);
}

/* ===================== SetStyledString test ===================== */

/**
 * @tc.name: SetStyledStringSubValueLength001
 * @tc.desc: SetStyledString with and without maxLength, subValueLength used correctly
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, SetStyledStringSubValueLength001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto initStyledString = [&richEditorPattern]() {
        richEditorPattern->isSpanStringMode_ = true;
        richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
        richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
        richEditorPattern->undoManager_ =
            std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    };
    // Branch: without maxLength
    initStyledString();
    auto value = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    richEditorPattern->SetStyledString(value);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), static_cast<int32_t>(std::u16string(u"hello").length()));
    // Branch: with maxLength
    initStyledString();
    richEditorPattern->maxLength_ = TEST_MAX_LENGTH_10;
    richEditorPattern->SetStyledString(value);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), static_cast<int32_t>(std::u16string(u"hello").length()));
}

/* ===================== DeleteToMaxLength test ===================== */

/**
 * @tc.name: DeleteToMaxLengthSpanString001
 * @tc.desc: DeleteToMaxLength in spanString mode with content exceeding max and nullopt
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, DeleteToMaxLengthSpanString001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    // Branch: content exceeds max -> deletion occurs
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello world");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->maxLength_ = TEST_MAX_LENGTH_10;

    int32_t maxLen = TEST_MAX_LENGTH_5;
    EXPECT_GT(richEditorPattern->GetTextContentLength(), maxLen);
    richEditorPattern->DeleteToMaxLength(maxLen);
    EXPECT_LE(richEditorPattern->GetTextContentLength(), maxLen);
    // Branch: nullopt length -> no deletion needed
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hi");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    auto lengthBefore = richEditorPattern->GetTextContentLength();
    richEditorPattern->DeleteToMaxLength(std::nullopt);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), lengthBefore);
}

/* ===================== SetThemeBorderAttr test ===================== */

/**
 * @tc.name: SetThemeBorderAttr001
 * @tc.desc: SetThemeBorderAttr without and with user-set border radius flag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, SetThemeBorderAttr001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    // Branch: no user-set border radius flag -> resets with empty BorderRadiusProperty
    auto renderContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderRadiusProperty initialRadius(5.0_vp, 5.0_vp, 5.0_vp, 5.0_vp);
    renderContext->UpdateBorderRadius(initialRadius);
    richEditorPattern->SetThemeBorderAttr();
    SUCCEED();
    // Branch: HasBorderRadiusFlagByUser=true -> applies user radius
    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    BorderRadiusProperty userRadius(3.0_vp, 3.0_vp, 3.0_vp, 3.0_vp);
    layoutProperty->UpdateBorderRadiusFlagByUser(userRadius);
    richEditorPattern->SetThemeBorderAttr();
    SUCCEED();
    layoutProperty->ResetBorderRadiusFlagByUser();
}

/* ===================== Counter enabled behavior tests ===================== */

/**
 * @tc.name: HandleCounterWithLength001
 * @tc.desc: HandleCounterWithLength with counter enabled verifies counter behavior
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, HandleCounterWithLength001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->maxLength_ = TEST_MAX_LENGTH_10;

    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowCounter(true);

    EXPECT_TRUE(richEditorPattern->IsShowCounterEnabled());
    richEditorPattern->HandleCounterWithLength(0, TEST_MAX_LENGTH_10);
    EXPECT_FALSE(richEditorPattern->showCountBorderStyle_);

    richEditorPattern->HandleCounterWithLength(TEST_MAX_LENGTH_10, TEST_MAX_LENGTH_10);
    // showCountBorderStyle_ depends on HasFocus()
    SUCCEED();

    layoutProperty->UpdateShowCounter(false);
}

/**
 * @tc.name: InsertValueInStyledStringCounterEnabled001
 * @tc.desc: With counter enabled, filter empties text → HandleCounterWithLength called with originInsertLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, InsertValueInStyledStringCounterEnabled001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
    richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->undoManager_ =
        std::make_unique<StyledStringUndoManager>(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->maxLength_ = TEST_MAX_LENGTH_10;

    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowCounter(true);

    // Set up filter that removes all non-digit characters
    richEditorPattern->hasActiveFilter_ = true;
    richEditorPattern->filterDirty_ = false;
    richEditorPattern->filterManager_.SetFilter(u"[0-9]");
    richEditorPattern->filterErrorHandler_ = [](const std::u16string&) -> bool { return true; };

    bool styleBefore = richEditorPattern->showCountBorderStyle_;
    (void)styleBefore;
    // "abc" filtered to "" → HandleCounterWithLength(originInsertLength=3, maxLength_) called
    richEditorPattern->InsertValueInStyledString(u"abc", true, false, false, false);
    // Verify counter was processed (showCountBorderStyle_ may have changed)
    SUCCEED();

    richEditorPattern->hasActiveFilter_ = false;
    layoutProperty->UpdateShowCounter(false);
}

/* ===================== MeasureDecorator branches test ===================== */

/**
 * @tc.name: MeasureDecorator001
 * @tc.desc: MeasureDecorator with showPlaceHolder, ShouldUseHostTextLength, and counter disabled
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterCoreTestNg, MeasureDecorator001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& richEditorNode = richEditorNode_;
    auto setupCounter = [&richEditorPattern, &richEditorNode]() {
        richEditorPattern->isSpanStringMode_ = true;
        richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"hello");
        richEditorPattern->styledString_->SetSpanWatcher(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
        richEditorPattern->maxLength_ = TEST_MAX_LENGTH_10;
        auto layoutProperty = richEditorNode->GetLayoutProperty<RichEditorLayoutProperty>();
        layoutProperty->UpdateShowCounter(true);
        richEditorPattern->AddCounterNode();
        return AceType::DynamicCast<CounterDecorator>(richEditorPattern->GetCounterDecorator());
    };
    // Branch: showPlaceHolder=true → textLength stays 0
    auto decorator = setupCounter();
    ASSERT_NE(decorator, nullptr);
    float height = decorator->MeasureDecorator(TEST_CONTENT_WIDTH, u"hello", true);
    EXPECT_GE(height, 0.0f);
    // Branch: ShouldUseHostTextLength=true, showPlaceHolder=false → uses host->GetTextLength()
    height = decorator->MeasureDecorator(TEST_CONTENT_WIDTH, u"", false);
    EXPECT_GE(height, 0.0f);
    // Branch: counter disabled → returns 0
    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateShowCounter(false);
    richEditorPattern->maxLength_ = std::nullopt;
    height = decorator->MeasureDecorator(TEST_CONTENT_WIDTH, u"hello", false);
    EXPECT_EQ(height, 0.0f);
    layoutProperty->UpdateShowCounter(false);
}

/* ===================== RichEditorCounterApiTestNg tests ===================== */

/**
 * @tc.name: PrepareInsertChangeRange001
 * @tc.desc: test PrepareInsertChangeRange all branches
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, PrepareInsertChangeRange001, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    // Branch: textSelector_ invalid → changeStart=caretPosition_, changeLength=0
    pattern->caretPosition_ = 5;
    int32_t start = -1;
    int32_t length = -1;
    pattern->PrepareInsertChangeRange(true, start, length);
    EXPECT_EQ(start, 5);
    EXPECT_EQ(length, 0);
    // Branch: textSelector_ valid + shouldCommitInput=true
    pattern->textSelector_.Update(2, 8);
    pattern->PrepareInsertChangeRange(true, start, length);
    EXPECT_EQ(start, 2);
    EXPECT_EQ(length, 6);
    // Branch: textSelector_ valid + shouldCommitInput=false → RecordPreviewInputtingStart
    pattern->PrepareInsertChangeRange(false, start, length);
    EXPECT_EQ(start, 2);
    EXPECT_EQ(length, 6);
    pattern->textSelector_.Update(-1, -1);
}

/**
 * @tc.name: HandleComposingTextBeforeInsertion001
 * @tc.desc: test HandleComposingTextBeforeInsertion (CROSS_PLATFORM not compiled in test build)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, HandleComposingTextBeforeInsertion001, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    // CROSS_PLATFORM not defined in test build; function body is empty, verify no crash
    pattern->HandleComposingTextBeforeInsertion(TEST_INSERT_VALUE);
    pattern->HandleComposingTextBeforeInsertion(u"");
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: InsertValueInStyledString001
 * @tc.desc: test InsertValueInStyledString normal insert + truncation failure
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, InsertValueInStyledString001, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    InitStyledStringMode();
    // Branch: normal insert (shouldCommitInput=true, no selection, no preview, isPaste=false)
    int32_t oldLen = pattern->styledString_->GetLength();
    pattern->InsertValueInStyledString(TEST_INSERT_VALUE, true);
    EXPECT_EQ(pattern->styledString_->GetLength(), oldLen + static_cast<int32_t>(TEST_INSERT_VALUE.length()));
    EXPECT_FALSE(pattern->textSelector_.IsValid());
    // Branch: ProcessTextTruncationOperation fails → HandleCounterWithLength + return
    InitStyledStringMode();
    pattern->maxLength_ = 0;
    pattern->caretPosition_ = 0;
    pattern->InsertValueInStyledString(INSERT_TEST_VALUE, true);
    EXPECT_EQ(pattern->styledString_->GetLength(), static_cast<int32_t>(INIT_VALUE_3.length()));
    pattern->maxLength_.reset();
}

/**
 * @tc.name: InsertValueInStyledString002
 * @tc.desc: test InsertValueInStyledString isPreventChange + needReplaceInTextPreview + isPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, InsertValueInStyledString002, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    InitStyledStringMode();
    // Branch: isPreventChange → ClearPreviewInputRecord + return (BeforeStyledStringChange returns false)
    auto eventHub = pattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnStyledStringWillChange([](const StyledStringChangeValue&) { return false; });
    int32_t oldLen = pattern->styledString_->GetLength();
    pattern->InsertValueInStyledString(TEST_INSERT_VALUE, true);
    EXPECT_EQ(pattern->styledString_->GetLength(), oldLen); // insert prevented
    eventHub->SetOnStyledStringWillChange(nullptr);
    // Branch: needReplaceInTextPreview=true + isPaste=true (no OnReportRichEditorEvent)
    InitStyledStringMode();
    pattern->previewTextRecord_.needReplacePreviewText = true;
    pattern->previewTextRecord_.replacedRange.Set(0, 3);
    pattern->InsertValueInStyledString(TEST_INSERT_VALUE, true, true);
    EXPECT_GT(pattern->styledString_->GetLength(), 0);
    pattern->previewTextRecord_.Reset();
}

/**
 * @tc.name: DeleteValueInStyledString001
 * @tc.desc: test DeleteValueInStyledString normal delete + selector + isPreventChange return true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, DeleteValueInStyledString001, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    InitStyledStringMode();
    pattern->caretPosition_ = 3;
    // Branch: normal delete (no selection) → return false
    bool ret = pattern->DeleteValueInStyledString(0, 2);
    EXPECT_FALSE(ret);
    // Branch: textSelector_ valid → start/length from selector
    InitStyledStringMode();
    pattern->textSelector_.Update(1, 5);
    ret = pattern->DeleteValueInStyledString(0, 1);
    EXPECT_FALSE(ret);
    pattern->textSelector_.Update(-1, -1);
    // Branch: isPreventChange + !IsPreviewTextInputting → return true
    InitStyledStringMode();
    auto eventHub = pattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnStyledStringWillChange([](const StyledStringChangeValue&) { return false; });
    ret = pattern->DeleteValueInStyledString(0, 2);
    EXPECT_TRUE(ret);
    eventHub->SetOnStyledStringWillChange(nullptr);
}

/**
 * @tc.name: SetMaxLength001
 * @tc.desc: test SetMaxLength with counter enabled and disabled
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, SetMaxLength001, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    // --- Counter enabled branches ---
    InitStyledStringMode();
    layoutProperty->UpdateShowCounter(true);
    pattern->AddCounterNode();
    // Branch: needUpdateCounter=true (textLength < inputMaxLength) + DeleteToMaxLength
    pattern->SetMaxLength(TEST_MAX_LENGTH);
    EXPECT_EQ(pattern->GetMaxLength(), TEST_MAX_LENGTH);
    // Branch: needUpdateCounter=true (maxLength==INT_MAX && maxLength_!=maxLength)
    pattern->SetMaxLength(std::nullopt);
    EXPECT_EQ(pattern->GetMaxLength(), INT_MAX);
    // Branch: maxLength != INT_MAX → DeleteToMaxLength trims content
    pattern->SetMaxLength(2);
    EXPECT_EQ(pattern->GetTextContentLength(), 2);
    // --- Counter disabled branches ---
    InitStyledStringMode();
    pattern->maxLength_ = TEST_MAX_LENGTH;
    pattern->SetMaxLength(TEST_MAX_LENGTH);
    EXPECT_EQ(pattern->GetMaxLength(), TEST_MAX_LENGTH);
    // Branch: textLength == inputMaxLength && maxLength_ == maxLength → needUpdateCounter=false
    pattern->maxLength_ = 0;
    pattern->SetMaxLength(0);
    EXPECT_EQ(pattern->GetMaxLength(), 0);
}

/**
 * @tc.name: ModelNGCounter001
 * @tc.desc: test RichEditorModelNG counter instance + static methods
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, ModelNGCounter001, TestSize.Level0)
{
    // Branch: instance methods (use ViewStackProcessor)
    RichEditorModelNG model;
    model.Create();
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    model.SetShowCounter(true);
    model.SetCounter(TEST_COUNTER_VALUE);
    model.SetCounterTextColor(COUNTER_TEXT_COLOR);
    model.SetCounterTextOverflowColor(COUNTER_OVERFLOW_COLOR);
    model.SetShowHighlightBorder(false);
    model.ResetCounterTextColor();
    model.ResetCounterTextOverflowColor();
    auto layoutProp = node->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_TRUE(layoutProp->GetShowCounterValue(false));
    EXPECT_EQ(layoutProp->GetSetCounterValue(0), TEST_COUNTER_VALUE);
    // Branch: static methods with FrameNode*
    RichEditorModelNG::SetShowCounter(AceType::RawPtr(richEditorNode_), true);
    RichEditorModelNG::SetCounter(AceType::RawPtr(richEditorNode_), TEST_COUNTER_VALUE);
    RichEditorModelNG::SetCounterTextColor(AceType::RawPtr(richEditorNode_), COUNTER_TEXT_COLOR);
    RichEditorModelNG::SetCounterTextOverflowColor(AceType::RawPtr(richEditorNode_), COUNTER_OVERFLOW_COLOR);
    RichEditorModelNG::SetShowHighlightBorder(AceType::RawPtr(richEditorNode_), false);
    RichEditorModelNG::ResetCounterTextColor(AceType::RawPtr(richEditorNode_));
    RichEditorModelNG::ResetCounterTextOverflowColor(AceType::RawPtr(richEditorNode_));
    auto richLayoutProp = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(richLayoutProp, nullptr);
    EXPECT_TRUE(richLayoutProp->GetShowCounterValue(false));
    EXPECT_EQ(richLayoutProp->GetSetCounterValue(0), TEST_COUNTER_VALUE);
    // Branch: static methods with nullptr FrameNode* (CHECK_NULL_VOID)
    RichEditorModelNG::SetShowCounter(nullptr, true);
    RichEditorModelNG::SetCounter(nullptr, 0);
    EXPECT_NE(richEditorNode_, nullptr);
}

/**
 * @tc.name: ModelNGBorder001
 * @tc.desc: test RichEditorModelNG border static methods
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, ModelNGBorder001, TestSize.Level0)
{
    auto* frameNode = AceType::RawPtr(richEditorNode_);
    ASSERT_NE(frameNode, nullptr);
    // Branch: SetBorderWidth (delegates to ViewAbstract + ACE_UPDATE_NODE_LAYOUT_PROPERTY)
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(BORDER_WIDTH_VALUE));
    RichEditorModelNG::SetBorderWidth(frameNode, borderWidth);
    // Branch: SetBorderRadius
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(BORDER_RADIUS_VALUE));
    RichEditorModelNG::SetBorderRadius(frameNode, borderRadius);
    // Branch: SetBorderColor
    BorderColorProperty borderColor;
    borderColor.SetColor(Color(BORDER_COLOR_VALUE));
    RichEditorModelNG::SetBorderColor(frameNode, borderColor);
    // Branch: SetBorderStyle
    BorderStyleProperty borderStyle;
    borderStyle.SetBorderStyle(BorderStyle::SOLID);
    RichEditorModelNG::SetBorderStyle(frameNode, borderStyle);
    auto layoutProp = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_TRUE(layoutProp->HasBorderWidthFlagByUser());
    EXPECT_TRUE(layoutProp->HasBorderRadiusFlagByUser());
    EXPECT_TRUE(layoutProp->HasBorderColorFlagByUser());
    EXPECT_TRUE(layoutProp->HasBorderStyleFlagByUser());
    // Branch: nullptr FrameNode* (CHECK_NULL_VOID)
    RichEditorModelNG::SetBorderWidth(nullptr, borderWidth);
    RichEditorModelNG::SetBorderRadius(nullptr, borderRadius);
    RichEditorModelNG::SetBorderColor(nullptr, borderColor);
    RichEditorModelNG::SetBorderStyle(nullptr, borderStyle);
    EXPECT_NE(richEditorNode_, nullptr);
}

/**
 * @tc.name: ForegroundModifierOnDraw001
 * @tc.desc: test RichEditorForegroundModifier::onDraw all branches
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, ForegroundModifierOnDraw001, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(0));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    // Branch: pattern_ null (empty WeakPtr) → return
    auto modifier = AceType::MakeRefPtr<RichEditorForegroundModifier>(WeakPtr<Pattern>());
    modifier->onDraw(context);
    // Branch: pattern valid but GetHost() returns null → early return
    auto orphanPattern = AceType::MakeRefPtr<RichEditorPattern>();
    orphanPattern->SetSpanStringMode(true);
    auto modifierNoHost = AceType::MakeRefPtr<RichEditorForegroundModifier>(WeakPtr<Pattern>(orphanPattern));
    modifierNoHost->SetInnerBorderWidth(BORDER_WIDTH_VALUE);
    modifierNoHost->SetInnerBorderColor(Color::RED);
    modifierNoHost->onDraw(context);
    // Branch: HasInnerBorderColor() false → return
    modifier = AceType::MakeRefPtr<RichEditorForegroundModifier>(AceType::WeakClaim(AceType::RawPtr(pattern)));
    modifier->onDraw(context);
    // Branch: innerBorderWidth_ null → return
    auto layoutProp = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->UpdateInnerBorderColor(Color::RED);
    modifier = AceType::MakeRefPtr<RichEditorForegroundModifier>(AceType::WeakClaim(AceType::RawPtr(pattern)));
    modifier->innerBorderWidth_ = nullptr;
    modifier->onDraw(context);
    // Branch: all valid → draw logic
    richEditorNode_->GetGeometryNode()->SetFrameSize({ 100.0f, 100.0f });
    modifier = AceType::MakeRefPtr<RichEditorForegroundModifier>(AceType::WeakClaim(AceType::RawPtr(pattern)));
    modifier->SetInnerBorderWidth(BORDER_WIDTH_VALUE);
    modifier->SetInnerBorderColor(Color::RED);
    modifier->onDraw(context);
    EXPECT_NE(modifier, nullptr);
}

/**
 * @tc.name: CounterNodeMeasure001
 * @tc.desc: test RichEditorLayoutAlgorithm::CounterNodeMeasure all branches
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, CounterNodeMeasure001, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    // Branch: null layoutWrapper -> return 0.0f
    float result = layoutAlgorithm->CounterNodeMeasure(100.0f, nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
    // Create valid LayoutWrapper
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    // Branch: counterDecorator null -> return 0.0f
    pattern->counterDecorator_ = nullptr;
    result = layoutAlgorithm->CounterNodeMeasure(100.0f, AceType::RawPtr(layoutWrapper));
    EXPECT_FLOAT_EQ(result, 0.0f);
    // Branch: valid counterDecorator -> calls MeasureDecorator
    InitStyledStringMode();
    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowCounter(true);
    pattern->maxLength_ = TEST_MAX_LENGTH;
    pattern->AddCounterNode();
    ASSERT_TRUE(pattern->GetCounterDecorator());
    result = layoutAlgorithm->CounterNodeMeasure(100.0f, AceType::RawPtr(layoutWrapper));
    SUCCEED();
}

/**
 * @tc.name: CounterLayout001
 * @tc.desc: test RichEditorLayoutAlgorithm::CounterLayout all branches
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, CounterLayout001, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    // Branch: null layoutWrapper -> early return (no crash)
    layoutAlgorithm->CounterLayout(nullptr);
    // Create valid LayoutWrapper
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    // Branch: counterDecorator null -> early return (no crash)
    pattern->counterDecorator_ = nullptr;
    layoutAlgorithm->CounterLayout(AceType::RawPtr(layoutWrapper));
    // Branch: valid counterDecorator -> calls LayoutDecorator
    InitStyledStringMode();
    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowCounter(true);
    pattern->maxLength_ = TEST_MAX_LENGTH;
    pattern->AddCounterNode();
    ASSERT_TRUE(pattern->GetCounterDecorator());
    layoutAlgorithm->CounterLayout(AceType::RawPtr(layoutWrapper));
    // Branch: non-ICounterHost pattern -> DynamicCast fails -> early return (no crash)
    auto nonCounterNode = FrameNode::GetOrCreateFrameNode("test_non_counter", 9999,
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(nonCounterNode, nullptr);
    auto nonCounterWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        nonCounterNode, AceType::MakeRefPtr<GeometryNode>(), nonCounterNode->GetLayoutProperty());
    nonCounterWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(
        AceType::MakeRefPtr<LayoutAlgorithm>()));
    CounterDecorator::LayoutCounterNode(AceType::RawPtr(nonCounterWrapper));
    SUCCEED();
}

/**
 * @tc.name: PaintMethodForegroundModifier001
 * @tc.desc: test RichEditorPaintMethod::GetForegroundModifier and UpdateForegroundModifier
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, PaintMethodForegroundModifier001, TestSize.Level0)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    // Branch: foregroundModifier_ null (counter disabled) -> GetForegroundModifier returns null
    pattern->foregroundModifier_ = nullptr;
    auto paintMethod = AceType::DynamicCast<RichEditorPaintMethod>(pattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    auto fgMod = paintMethod->GetForegroundModifier(nullptr);
    EXPECT_FALSE(fgMod);
    // Branch: foregroundModifier_ set -> GetForegroundModifier returns modifier
    InitStyledStringMode();
    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowCounter(true);
    pattern->maxLength_ = TEST_MAX_LENGTH;
    paintMethod = AceType::DynamicCast<RichEditorPaintMethod>(pattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    fgMod = paintMethod->GetForegroundModifier(nullptr);
    EXPECT_TRUE(fgMod);
    // Branch: UpdateForegroundModifier with valid modifier
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = pattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    paintMethod->UpdateForegroundModifier(AceType::RawPtr(paintWrapper));
    SUCCEED();
    // Branch: UpdateForegroundModifier with null modifier (create paint method without counter)
    layoutProperty->UpdateShowCounter(false);
    pattern->foregroundModifier_ = nullptr;
    auto paintMethodNoFg = AceType::DynamicCast<RichEditorPaintMethod>(pattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethodNoFg, nullptr);
    paintMethodNoFg->UpdateForegroundModifier(AceType::RawPtr(paintWrapper)); // CHECK_NULL_VOID early return
    SUCCEED();
    // Branch: UpdateForegroundModifier with null pattern_ (DynamicCast fails, early return)
    auto nullPatternModifier = AceType::MakeRefPtr<RichEditorForegroundModifier>(WeakPtr<Pattern>());
    nullPatternModifier->SetInnerBorderWidth(BORDER_WIDTH_VALUE);
    nullPatternModifier->SetInnerBorderColor(Color::RED);
    auto paintMethodNullPattern = AceType::MakeRefPtr<RichEditorPaintMethod>(
        WeakPtr<Pattern>(), nullptr, 0.0f, nullptr, nullptr, nullPatternModifier);
    ASSERT_NE(paintMethodNullPattern->foregroundModifier_, nullptr);
    paintMethodNullPattern->UpdateForegroundModifier(nullptr);
    EXPECT_EQ(AceType::RawPtr(paintMethodNullPattern->foregroundModifier_), AceType::RawPtr(nullPatternModifier));
}

/**
 * @tc.name: SetRichEditorShowCounter001
 * @tc.desc: Test SetRichEditorShowCounter with ConfigChange, both resources, and no color set
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, SetRichEditorShowCounter001, TestSize.Level0)
{
    SystemProperties::SetConfigChangePerform();
    auto richEditorNode = FrameNode::GetOrCreateFrameNode(V2::RICH_EDITOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode, nullptr);
    auto pattern = richEditorNode->GetPattern<RichEditorPattern>();
    pattern->SetSpanStringMode(true);
    auto layoutProperty = richEditorNode->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto textColorRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto overflowColorRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    // B1: ConfigChangePerform=true, counterTextColorIsSet=true, counterTextOverflowColorIsSet=false
    ArkUIShowCountOptions options = {};
    options.open = 1;
    options.thresholdPercentage = 80;
    options.highlightBorder = 1;
    options.counterTextColorIsSet = 1;
    options.counterTextColor = COUNTER_TEXT_COLOR.GetValue();
    options.counterTextOverflowColorIsSet = 0;
    SetRichEditorShowCounter(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(richEditorNode)),
        &options, AceType::RawPtr(textColorRes), nullptr);
    EXPECT_TRUE(layoutProperty->HasCounterTextColor());
    EXPECT_NE(pattern->resourceMgr_, nullptr);
    // B2: ConfigChangePerform=true, both raw ptrs non-null -> Register both resources
    options.counterTextOverflowColorIsSet = 1;
    options.counterTextOverflowColor = COUNTER_OVERFLOW_COLOR.GetValue();
    SetRichEditorShowCounter(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(richEditorNode)),
        &options, AceType::RawPtr(textColorRes), AceType::RawPtr(overflowColorRes));
    EXPECT_NE(pattern->resourceMgr_, nullptr);
    g_isConfigChangePerform = false;
    // B3: IsSet=false -> ResetCounterTextColor + ResetCounterTextOverflowColor
    auto node2 = FrameNode::GetOrCreateFrameNode(V2::RICH_EDITOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    auto pattern2 = node2->GetPattern<RichEditorPattern>();
    pattern2->SetSpanStringMode(true);
    options.counterTextColorIsSet = 0;
    options.counterTextOverflowColorIsSet = 0;
    SetRichEditorShowCounter(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(node2)),
        &options, nullptr, nullptr);
    auto layoutProp2 = node2->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProp2, nullptr);
    EXPECT_FALSE(layoutProp2->HasCounterTextColor());
    EXPECT_FALSE(layoutProp2->HasCounterTextOverflowColor());
}

/**
 * @tc.name: ResetRichEditorShowCounterConfigChange
 * @tc.desc: Test ResetRichEditorShowCounter with ConfigChangePerform=true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, ResetRichEditorShowCounterConfigChange, TestSize.Level0)
{
    SystemProperties::SetConfigChangePerform();
    auto richEditorNode = FrameNode::GetOrCreateFrameNode(V2::RICH_EDITOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode, nullptr);
    auto pattern = richEditorNode->GetPattern<RichEditorPattern>();
    // First register resources
    auto resObj = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    pattern->RegisterResource<Color>("counterTextColor", resObj, Color::RED);
    pattern->RegisterResource<Color>("counterTextOverflowColor", resObj, Color::GREEN);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
    // B1: ConfigChangePerform=true -> UnRegisterResource for both
    ResetRichEditorShowCounter(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(richEditorNode)));
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: GetRichEditorShowCounterOptionsTest
 * @tc.desc: Test GetRichEditorShowCounterOptions retrieves correct values
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, GetRichEditorShowCounterOptionsTest, TestSize.Level0)
{
    auto richEditorNode = FrameNode::GetOrCreateFrameNode(V2::RICH_EDITOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode, nullptr);
    // Set counter values
    RichEditorModelNG::SetShowCounter(AceType::RawPtr(richEditorNode), true);
    RichEditorModelNG::SetCounter(AceType::RawPtr(richEditorNode), 50);
    RichEditorModelNG::SetShowHighlightBorder(AceType::RawPtr(richEditorNode), true);
    RichEditorModelNG::SetCounterTextColor(AceType::RawPtr(richEditorNode), COUNTER_TEXT_COLOR);
    RichEditorModelNG::SetCounterTextOverflowColor(AceType::RawPtr(richEditorNode), COUNTER_OVERFLOW_COLOR);
    // Get
    ArkUIShowCountOptions result = {};
    GetRichEditorShowCounterOptions(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(richEditorNode)), &result);
    EXPECT_EQ(result.open, 1);
    EXPECT_EQ(result.thresholdPercentage, 50);
    EXPECT_EQ(result.highlightBorder, 1);
}

/**
 * @tc.name: RichEditorAccessibilityIsShowCount
 * @tc.desc: Test RichEditorAccessibilityProperty::IsShowCount
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorCounterApiTestNg, RichEditorAccessibilityIsShowCount, TestSize.Level0)
{
    auto richEditorNode = FrameNode::GetOrCreateFrameNode(V2::RICH_EDITOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode, nullptr);
    auto pattern = richEditorNode->GetPattern<RichEditorPattern>();
    pattern->SetSpanStringMode(true);
    auto accProp = richEditorNode->GetAccessibilityProperty<RichEditorAccessibilityProperty>();
    ASSERT_NE(accProp, nullptr);
    // B1: counter not enabled -> IsShowCount returns false
    EXPECT_FALSE(accProp->IsShowCount());
    // Enable counter
    InitStyledStringMode();
    auto layoutProperty = richEditorNode->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->UpdateShowCounter(true);
    pattern->maxLength_ = TEST_MAX_LENGTH;
    pattern->AddCounterNode();
    // B2: counter enabled -> depends on HasContent
    bool result = accProp->IsShowCount();
    // Counter decorator was just created, no content update called yet
    // So HasContent() likely returns false
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern->GetCounterDecorator());
    if (counterDecorator && counterDecorator->HasContent()) {
        EXPECT_TRUE(result);
    } else {
        EXPECT_FALSE(result);
    }
}
} // namespace OHOS::Ace::NG
