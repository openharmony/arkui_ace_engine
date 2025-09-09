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

#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"

#define protected public
#define private public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "base/memory/memory_monitor_def.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/indexer/arc_indexer_pattern.h"
#include "core/components_ng/pattern/indexer/arc_indexer_content_modifier.h"
#include "core/components_ng/pattern/indexer/arc_indexer_layout_algorithm.h"
#include "core/components_ng/pattern/indexer/arc_indexer_paint_method.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "indexer_test_ng.h"
#include "arcindexer_pattern_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
std::vector<std::string> CREATE_ARRAY = { "AAAAAAAA", "BBBB", "C", "D", "E", "FFFFF", "G", "H", "I", "J", "K", "L",
    "MMMMMMMM", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
std::vector<std::string> CREATE_ARRAY_1 = { "A", "B", "C", "D", "E", "F", "G", "H", "I" };
std::vector<std::string> CREATE_ARRAY_2 = { "#", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
std::vector<std::string> LONG_ARRAY = { "AAAAAAAA", "BBBB", "C", "D", "E", "FFFFF", "G", "H", "I", "J", "K", "L",
    "MMMMMMMM", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "ED", "FJ", "OMD", "MDL", "PCL" };

} // namespace

class ArcindexerPatternTestTwoNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    IndexerModelNG Create(const std::function<void(IndexerModelNG)>& callback = nullptr,
        std::vector<std::string> arrayValue = CREATE_ARRAY, int32_t selected = 0);
    AssertionResult Selected(int32_t expectSelected);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ArcIndexerPattern> pattern_;
    RefPtr<IndexerEventHub> eventHub_;
    RefPtr<IndexerLayoutProperty> layoutProperty_;
    RefPtr<IndexerPaintProperty> paintProperty_;
    RefPtr<IndexerAccessibilityProperty> accessibilityProperty_;
    RefPtr<ArcIndexerContentModifier> contentModifier_;
};

void ArcindexerPatternTestTwoNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));
}

void ArcindexerPatternTestTwoNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ArcindexerPatternTestTwoNg::SetUp() {}

void ArcindexerPatternTestTwoNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    contentModifier_ = nullptr;
}

void ArcindexerPatternTestTwoNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ArcIndexerPattern>();
    eventHub_ = frameNode_->GetEventHub<IndexerEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<IndexerLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<IndexerPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<IndexerAccessibilityProperty>();
    contentModifier_ = AceType::MakeRefPtr<ArcIndexerContentModifier>();
}

IndexerModelNG ArcindexerPatternTestTwoNg::Create(
    const std::function<void(IndexerModelNG)>& callback, std::vector<std::string> arrayValue, int32_t selected)
{
    IndexerModelNG model;
    model.Create(arrayValue, selected, true);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushUITasks(frameNode_);
    return model;
}

AssertionResult ArcindexerPatternTestTwoNg::Selected(int32_t expectSelected)
{
    return IsEqual(pattern_->GetSelected(), expectSelected);
}

/**
 * @tc.name: UpdateIndexerRender001
 * @tc.desc: Test arc indexer pattern UpdateIndexerRender function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, UpdateIndexerRender001, TestSize.Level1)
{
    Create(nullptr, CREATE_ARRAY, 0);
    auto indexerRenderContext = frameNode_->GetRenderContext();

    /**
     * @tc.steps: step1. Test with arcRadius_ 15.
     * @tc.expected: UpdateIndexerRender correct.
     */
    pattern_->arcRadius_ = 15.f;
    auto indexerRadius = Dimension(pattern_->arcRadius_, DimensionUnit::VP);
    pattern_->UpdateIndexerRender();
    EXPECT_EQ(indexerRenderContext->GetBorderRadius()->radiusTopLeft.value(), indexerRadius);
    EXPECT_EQ(indexerRenderContext->GetBorderRadius()->radiusTopRight.value(), indexerRadius);
    EXPECT_EQ(indexerRenderContext->GetBorderRadius()->radiusBottomLeft.value(), indexerRadius);
    EXPECT_EQ(indexerRenderContext->GetBorderRadius()->radiusBottomRight.value(), indexerRadius);
    EXPECT_EQ(indexerRenderContext->GetBackgroundColor().value(), Color::TRANSPARENT);

    /**
     * @tc.steps: step2. Test with arcRadius_ 180.
     * @tc.expected: UpdateIndexerRender correct.
     */
    pattern_->arcRadius_ = 180.f;
    indexerRadius = Dimension(pattern_->arcRadius_, DimensionUnit::VP);
    pattern_->UpdateIndexerRender();
    EXPECT_EQ(indexerRenderContext->GetBorderRadius()->radiusTopLeft.value(), indexerRadius);
    EXPECT_EQ(indexerRenderContext->GetBorderRadius()->radiusTopRight.value(), indexerRadius);
    EXPECT_EQ(indexerRenderContext->GetBorderRadius()->radiusBottomLeft.value(), indexerRadius);
    EXPECT_EQ(indexerRenderContext->GetBorderRadius()->radiusBottomRight.value(), indexerRadius);
    EXPECT_EQ(indexerRenderContext->GetBackgroundColor().value(), Color::TRANSPARENT);
}

/**
 * @tc.name: UpdateIndexerNodeOpacityByIdx001
 * @tc.desc: Test arc indexer pattern UpdateIndexerNodeOpacityByIdx function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, UpdateIndexerNodeOpacityByIdx001, TestSize.Level1)
{
    Create(nullptr, CREATE_ARRAY, 0);
    auto renderContext = frameNode_->GetRenderContext();

    /**
     * @tc.steps: step1. Test with currectCollapsingMode_ == lastCollapsingMode_.
     * @tc.expected: Opacity not changed.
     */
    renderContext->UpdateOpacity(2.0f);
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->lastCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->UpdateIndexerNodeOpacityByIdx(renderContext, 2);
    EXPECT_EQ(renderContext->GetOpacity(), 2.0f);

    /**
     * @tc.steps: step2. Test with currectCollapsingMode_ != lastCollapsingMode_.
     * @tc.expected: Opacity changed.
     */
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    pattern_->lastCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->UpdateIndexerNodeOpacityByIdx(renderContext, 5);
    EXPECT_EQ(renderContext->GetOpacity(), 0.0f);

    /**
     * @tc.steps: step3. Test with currectCollapsingMode_ != lastCollapsingMode_.
     * @tc.expected: Opacity not changed.
     */
    renderContext->UpdateOpacity(2.0f);
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->lastCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    pattern_->UpdateIndexerNodeOpacityByIdx(renderContext, 5);
    EXPECT_EQ(renderContext->GetOpacity(), 2.0f);
}

/**
 * @tc.name: UpdateBubbleView001
 * @tc.desc: Test arc indexer pattern UpdateBubbleView function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, UpdateBubbleView001, TestSize.Level1)
{
    Create(nullptr, CREATE_ARRAY, 0);
    pattern_->popupNode_ = pattern_->CreatePopupNode();

    /**
     * @tc.steps: step1. Test with func UpdateBubbleView.
     * @tc.expected: renderContext set correct.
     */
    pattern_->UpdateBubbleView();
    auto borderRadius = Dimension(ARC_BUBBLE_BOX_RADIUS, DimensionUnit::VP);
    auto textRenderContext = pattern_->popupNode_->GetRenderContext();
    EXPECT_EQ(textRenderContext->GetBorderRadius()->radiusBottomRight, borderRadius);
    EXPECT_EQ(textRenderContext->GetBorderRadius()->radiusBottomLeft, borderRadius);
    EXPECT_EQ(textRenderContext->GetBorderRadius()->radiusTopLeft, borderRadius);
    EXPECT_EQ(textRenderContext->GetBorderRadius()->radiusTopRight, borderRadius);
    EXPECT_EQ(textRenderContext->GetBackShadow()->GetBlurRadius(), 0);
    EXPECT_EQ(textRenderContext->GetBackShadow()->GetOffset().GetX(), 0);
    EXPECT_EQ(textRenderContext->GetBackShadow()->GetOffset().GetY(), 10);
    EXPECT_EQ(textRenderContext->GetBackShadow()->GetColor(), Color(0x26000000));
    EXPECT_EQ(textRenderContext->GetBackShadow()->GetShadowType(), ShadowType::COLOR);
}

/**
 * @tc.name: FireOnSelect002
 * @tc.desc: Test arc indexer pattern FireOnSelect function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, FireOnSelect002, TestSize.Level1)
{
    int32_t selected = -1;
    int32_t changeSelected = -1;
    int32_t creatChangeSelected = -1;
    OnSelectedEvent onSelected = [&selected](int32_t selectedIndex) { selected = selectedIndex; };
    OnSelectedEvent changeEvent = [&changeSelected](int32_t selectedIndex) { changeSelected = selectedIndex; };
    OnSelectedEvent creatChangeEvent = [&creatChangeSelected](
                                           int32_t selectedIndex) { creatChangeSelected = selectedIndex; };
    IndexerModelNG model = Create(nullptr, CREATE_ARRAY, 0);
    model.SetOnSelected(std::move(onSelected));
    model.SetChangeEvent(std::move(changeEvent));
    model.SetCreatChangeEvent(std::move(creatChangeEvent));

    /**
     * @tc.steps: step1. Test with func FireOnSelect.
     * @tc.expected: lastFireSelectIndex_ 2.
     */
    pattern_->selected_ = 1;
    pattern_->FireOnSelect(2, false);
    EXPECT_EQ(selected, -1);
    EXPECT_EQ(changeSelected, -1);
    EXPECT_EQ(creatChangeSelected, -1);
    EXPECT_EQ(pattern_->lastFireSelectIndex_, 2);
    EXPECT_FALSE(pattern_->lastIndexFromPress_);
}

/**
 * @tc.name: BuildFullArrayValue001
 * @tc.desc: Test arc indexer pattern BuildFullArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, BuildFullArrayValue001, TestSize.Level1)
{
    Create(nullptr, std::vector<std::string>(), 0);

    /**
     * @tc.steps: step1. Test with CREATE_ARRAY_2.
     * @tc.expected: arcArrayValue_ correct.
     */
    pattern_->fullArrayValue_ = CREATE_ARRAY_2;
    pattern_->fullCount_ = CREATE_ARRAY_2.size();
    pattern_->autoCollapse_ = true;
    pattern_->BuildFullArrayValue();
    std::vector<std::string> expectValue = CREATE_ARRAY_2;
    std::vector<std::string> arrayValue;
    expectValue.push_back("<");
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    EXPECT_EQ(arrayValue, expectValue);

    /**
     * @tc.steps: step2. Test with fullCount_ < ARC_INDEXER_COLLAPSE_ITEM_COUNT and autoCollapse_ false.
     * @tc.expected: arcArrayValue_ correct.
     */
    std::vector<std::string> array = { "A", "B" };
    pattern_->fullArrayValue_ = array;
    pattern_->fullCount_ = array.size();
    pattern_->autoCollapse_ = false;
    pattern_->BuildFullArrayValue();
    arrayValue.clear();
    expectValue = array;
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    EXPECT_EQ(arrayValue, expectValue);

    /**
     * @tc.steps: step3. Test with fullCount_ < ARC_INDEXER_COLLAPSE_ITEM_COUNT and autoCollapse_ true.
     * @tc.expected: arcArrayValue_ correct.
     */
    pattern_->autoCollapse_ = true;
    pattern_->BuildFullArrayValue();
    arrayValue.clear();
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    EXPECT_EQ(arrayValue, expectValue);
}

/**
 * @tc.name: ApplyFourPlusOneMode001
 * @tc.desc: Test arc indexer pattern ApplyFourPlusOneMode function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, ApplyFourPlusOneMode001, TestSize.Level1)
{
    Create(nullptr, CREATE_ARRAY_2, 0);
    pattern_->autoCollapse_ = true;
    std::vector<std::string> arrayvalue;
    std::vector<std::string> expectValue = CREATE_ARRAY_2;

    /**
     * @tc.steps: step1. Test with CREATE_ARRAY_2.
     * @tc.expected: arcArrayValue_ correct.
     */
    expectValue.push_back(">");
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = CREATE_ARRAY_2.size();
    pattern_->selected_ = 2;
    pattern_->ApplyFourPlusOneMode();
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 13);

    /**
     * @tc.steps: step2. Test with startIndex_ and endIndex_ changed.
     * @tc.expected: arcArrayValue_ correct.
     */
    arrayvalue.clear();
    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = 15;
    pattern_->selected_ = CREATE_ARRAY_2.size();
    pattern_->ApplyFourPlusOneMode();
    expectValue = { "I", "J", "K", "L", ">" };
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_EQ(pattern_->startIndex_, 9);
    EXPECT_EQ(pattern_->endIndex_, 13);
}

/**
 * @tc.name: ApplyFourPlusOneMode002
 * @tc.desc: Test arc indexer pattern ApplyFourPlusOneMode function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, ApplyFourPlusOneMode002, TestSize.Level1)
{
    Create(nullptr, CREATE_ARRAY_2, 0);
    pattern_->autoCollapse_ = true;
    std::vector<std::string> arrayvalue;
    std::vector<std::string> expectValue;

    /**
     * @tc.steps: step1. Test with startIndex_ and endIndex_ changed.
     * @tc.expected: arcArrayValue_ correct.
     */
    arrayvalue.clear();
    pattern_->startIndex_ = 3;
    pattern_->endIndex_ = 10;
    pattern_->selected_ = 0;
    pattern_->ApplyFourPlusOneMode();
    expectValue = { "#", "A", "B", "C", ">" };
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 4);

    /**
     * @tc.steps: step2. Test with startIndex_ and endIndex_ changed.
     * @tc.expected: arcArrayValue_ correct.
     */
    arrayvalue.clear();
    pattern_->startIndex_ = 2;
    pattern_->endIndex_ = 8;
    pattern_->selected_ = 9;
    pattern_->ApplyFourPlusOneMode();
    expectValue = { "F", "G", "H", "I", ">" };
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_EQ(pattern_->startIndex_, 6);
    EXPECT_EQ(pattern_->endIndex_, 10);
}

/**
 * @tc.name: ApplyFourPlusOneMode003
 * @tc.desc: Test arc indexer pattern ApplyFourPlusOneMode function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, ApplyFourPlusOneMode003, TestSize.Level1)
{
    Create(nullptr, LONG_ARRAY, 0);
    pattern_->autoCollapse_ = true;
    std::vector<std::string> arrayvalue;
    std::vector<std::string> expectValue = LONG_ARRAY;

    /**
     * @tc.steps: step1. Test with LONG_ARRAY.
     * @tc.expected: arcArrayValue_ correct.
     */
    for (int32_t i = 0; i < LONG_ARRAY.size() - ARC_INDEXER_ITEM_MAX_COUNT; ++i) {
        expectValue.pop_back();
    }
    expectValue.push_back(">");
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = LONG_ARRAY.size() + 1;
    pattern_->selected_ = 4;
    pattern_->ApplyFourPlusOneMode();
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 29);

    /**
     * @tc.steps: step2. Test with startIndex_ and endIndex_ changed.
     * @tc.expected: arcArrayValue_ correct.
     */
    arrayvalue.clear();
    pattern_->startIndex_ = 3;
    pattern_->endIndex_ = 17;
    pattern_->selected_ = CREATE_ARRAY_2.size() + 1;
    pattern_->ApplyFourPlusOneMode();
    expectValue = { "D", "E", "FFFFF", "G", "H", "I", "J", "K", "L", "MMMMMMMM", "N", "O", "P", "Q", ">" };
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->endIndex_, 17);
}

/**
 * @tc.name: ApplyFourPlusOneMode004
 * @tc.desc: Test arc indexer pattern ApplyFourPlusOneMode function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, ApplyFourPlusOneMode004, TestSize.Level1)
{
    Create(nullptr, LONG_ARRAY, 0);
    pattern_->autoCollapse_ = true;
    std::vector<std::string> arrayvalue;
    std::vector<std::string> expectValue;

    /**
     * @tc.steps: step1. Test with startIndex_ and endIndex_ changed.
     * @tc.expected: arcArrayValue_ correct.
     */
    arrayvalue.clear();
    pattern_->startIndex_ = 6;
    pattern_->endIndex_ = 7;
    pattern_->selected_ = 1;
    pattern_->ApplyFourPlusOneMode();
    expectValue = { "BBBB", "C", "D", "E", ">" };
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 5);

    /**
     * @tc.steps: step2. Test with startIndex_ and endIndex_ changed.
     * @tc.expected: arcArrayValue_ correct.
     */
    arrayvalue.clear();
    pattern_->startIndex_ = 8;
    pattern_->endIndex_ = 17;
    pattern_->selected_ = 19;
    pattern_->ApplyFourPlusOneMode();
    expectValue = { "Q", "R", "S", "T", ">" };
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_EQ(pattern_->startIndex_, 16);
    EXPECT_EQ(pattern_->endIndex_, 20);
}

/**
 * @tc.name: ResetArrayValue001
 * @tc.desc: Test arc indexer pattern ResetArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, ResetArrayValue001, TestSize.Level1)
{
    Create(nullptr, std::vector<std::string>(), 7);
    bool isModeChanged = false;
    std::vector<std::string> arrayValue;
    std::vector<std::string> expectValue;

    /**
     * @tc.steps: step2. Test with LONG_ARRAY and autoCollapse_ true.
     * @tc.expected: arcArrayValue_ correct.
     */
    isModeChanged = true;
    pattern_->autoCollapse_ = true;
    pattern_->fullArrayValue_ = LONG_ARRAY;
    layoutProperty_->UpdateUsingPopup(true);
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->startIndex_ = 8;
    pattern_->endIndex_ = 17;
    pattern_->ResetArrayValue(isModeChanged);
    EXPECT_EQ(pattern_->fullCount_, LONG_ARRAY.size());
    EXPECT_EQ(pattern_->sharpItemCount_, 0);
    EXPECT_EQ(pattern_->itemCount_, 5);
    EXPECT_TRUE(pattern_->isPopup_);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 4);
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    expectValue = { "AAAAAAAA", "BBBB", "C", "D", ">" };
    EXPECT_EQ(arrayValue, expectValue);

    /**
     * @tc.steps: step2. Test with LONG_ARRAY and autoCollapse_ false.
     * @tc.expected: arcArrayValue_ correct.
     */
    pattern_->autoCollapse_ = true;
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    pattern_->ResetArrayValue(isModeChanged);
    EXPECT_EQ(pattern_->fullCount_, LONG_ARRAY.size());
    EXPECT_EQ(pattern_->sharpItemCount_, 0);
    EXPECT_EQ(pattern_->itemCount_, LONG_ARRAY.size() - 1);
    EXPECT_EQ(pattern_->endIndex_, 4);
    expectValue = LONG_ARRAY;
    for (int32_t i = 0; i < LONG_ARRAY.size() - ARC_INDEXER_ITEM_MAX_COUNT; ++i) {
        expectValue.pop_back();
    }
    expectValue.push_back("<");
    arrayValue.clear();
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    EXPECT_EQ(arrayValue, expectValue);
}

/**
 * @tc.name: FireAccessbilityExpanded001
 * @tc.desc: Test arc indexer pattern FireAccessbilityExpanded function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, FireAccessbilityExpanded001, TestSize.Level1)
{
    Create(nullptr, LONG_ARRAY, 0);

    /**
     * @tc.steps: step1. Test with func FireAccessbilityExpanded.
     * @tc.expected: currectCollapsingMode_ correct.
     */
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->FireAccessbilityExpanded();
    EXPECT_FALSE(pattern_->isNewHeightCalculated_);
    EXPECT_EQ(pattern_->lastCollapsingMode_, ArcIndexerCollapsingMode::NONE);
    EXPECT_EQ(pattern_->currectCollapsingMode_, ArcIndexerCollapsingMode::NONE);
}

/**
 * @tc.name: FireAccessbilityCollapsed001
 * @tc.desc: Test arc indexer pattern FireAccessbilityCollapsed function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, FireAccessbilityCollapsed001, TestSize.Level1)
{
    Create(nullptr, LONG_ARRAY, 0);

    /**
     * @tc.steps: step1. Test with func FireAccessbilityCollapsed.
     * @tc.expected: currectCollapsingMode_ correct.
     */
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    pattern_->FireAccessbilityCollapsed();
    EXPECT_FALSE(pattern_->isNewHeightCalculated_);
    EXPECT_EQ(pattern_->lastCollapsingMode_, ArcIndexerCollapsingMode::FOUR);
    EXPECT_EQ(pattern_->currectCollapsingMode_, ArcIndexerCollapsingMode::FOUR);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test arc indexer pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    Create(nullptr, LONG_ARRAY, 0);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipLayout = false;
    dirtySwapConfig.skipMeasure = false;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    auto algorithm = AceType::MakeRefPtr<ArcIndexerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;

    /**
     * @tc.steps: step1. Test with autoCollapse_ true.
     * @tc.expected: currectCollapsingMode_ correct.
     */
    algorithm->arcCenter_ = OffsetF(10.f, 10.f);
    algorithm->sweepAngle_ = 10;
    algorithm->arcRadius_ = 20;
    algorithm->itemRadius_ = 10;
    algorithm->actualSize_ = 5;
    algorithm->stepAngle_ = 20;
    algorithm->startAngle_ = 20;
    pattern_->autoCollapse_ = true;
    pattern_->arcIndexerSize_ = 2;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(pattern_->strokeWidth_, pattern_->lastItemSize_);
    EXPECT_EQ(pattern_->arcRadius_, 20);
    EXPECT_EQ(pattern_->arcCenter_, OffsetF(10.f, 10.f));
    EXPECT_EQ(pattern_->sweepAngle_, 10);
    EXPECT_EQ(pattern_->arcIndexerSize_, 5);
    EXPECT_EQ(pattern_->stepAngle_, 20);
    EXPECT_EQ(pattern_->startAngle_, 20);
    EXPECT_TRUE(pattern_->isNewHeightCalculated_);

    /**
     * @tc.steps: step1. Test with autoCollapse_ false.
     * @tc.expected: currectCollapsingMode_ correct.
     */
    algorithm->stepAngle_ = 10;
    algorithm->startAngle_ = 10;
    pattern_->autoCollapse_ = false;
    pattern_->stepAngle_ = 10;
    pattern_->startAngle_ = 10;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_TRUE(pattern_->initialized_);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test arc indexer pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    Create(nullptr, LONG_ARRAY, 0);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipLayout = false;
    dirtySwapConfig.skipMeasure = false;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    auto algorithm = AceType::MakeRefPtr<ArcIndexerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;

    /**
     * @tc.steps: step1. Test with stepAngle_ changed.
     * @tc.expected: stepAngle_ correct.
     */
    algorithm->actualSize_ = 5;
    algorithm->stepAngle_ = 10;
    algorithm->startAngle_ = 10;
    pattern_->stepAngle_ = 20;
    pattern_->autoCollapse_ = false;
    pattern_->arcIndexerSize_ = 5;
    pattern_->startAngle_ = 10;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(pattern_->arcIndexerSize_, 5);
    EXPECT_EQ(pattern_->stepAngle_, 10);
    EXPECT_EQ(pattern_->startAngle_, 10);

    /**
     * @tc.steps: step2. Test with startAngle_ changed.
     * @tc.expected: startAngle_ correct.
     */
    algorithm->actualSize_ = 4;
    algorithm->stepAngle_ = 10;
    algorithm->startAngle_ = 20;
    pattern_->stepAngle_ = 10;
    pattern_->autoCollapse_ = false;
    pattern_->arcIndexerSize_ = 4;
    pattern_->startAngle_ = 10;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(pattern_->arcIndexerSize_, 4);
    EXPECT_EQ(pattern_->stepAngle_, 10);
    EXPECT_EQ(pattern_->startAngle_, 20);
}

/**
 * @tc.name: OnTouchDown001
 * @tc.desc: Test arc indexer pattern OnTouchDown function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, OnTouchDown001, TestSize.Level1)
{
    Create(nullptr, LONG_ARRAY, 0);
    TouchEventInfo info = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(50.f, 50.f));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchLocationInfo));

    /**
     * @tc.steps: step1. Test with nextSelectIndex < itemCount_.
     * @tc.expected: selected correct.
     */
    pattern_->stepAngle_ = 20;
    pattern_->autoCollapse_ = true;
    pattern_->arcCenter_ = OffsetF(20.f, 20.f);
    pattern_->selected_ = 5;
    pattern_->startAngle_ = 0;
    pattern_->OnTouchDown(info);
    EXPECT_EQ(pattern_->selected_, 2);

    /**
     * @tc.steps: step2. Test with nextSelectIndex == itemCount_.
     * @tc.expected: selected not changed.
     */
    touchLocationInfo.SetLocalLocation(Offset(15.f, 25.f));
    info.AddTouchLocationInfo(std::move(touchLocationInfo));
    pattern_->selected_ = 5;
    pattern_->OnTouchDown(info);
    EXPECT_EQ(pattern_->selected_, 5);
}

/**
 * @tc.name: OnTouchUp002
 * @tc.desc: Test arc indexer pattern OnTouchUp function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, OnTouchUp002, TestSize.Level1)
{
    Create(nullptr, LONG_ARRAY, 0);
    TouchEventInfo info = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(50.f, 50.f));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchLocationInfo));

    /**
     * @tc.steps: step1. Test with func OnTouchUp.
     * @tc.expected: selected correct.
     */
    pattern_->OnTouchUp(info);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
    EXPECT_EQ(pattern_->childFocusIndex_, -1);
}

/**
 * @tc.name: ItemSelectedChangedAnimation001
 * @tc.desc: Test arc indexer pattern ItemSelectedChangedAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, ItemSelectedChangedAnimation001, TestSize.Level1)
{
    Create(nullptr, LONG_ARRAY, 0);

    /**
     * @tc.steps: step1. Test with selected 2.
     * @tc.expected: animateSelected_ and lastSelected_ correct.
     */
    auto selectedFrameNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(2));
    auto renderContext = selectedFrameNode->GetRenderContext();
    auto pipelineContext = frameNode_->GetContext();
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    pattern_->selected_ = 2;
    pattern_->lastSelected_ = 0;
    pattern_->ItemSelectedChangedAnimation();
    EXPECT_EQ(pattern_->animateSelected_, 2);
    EXPECT_EQ(pattern_->lastSelected_, 2);

    /**
     * @tc.steps: step2. Test with selected 5.
     * @tc.expected: animateSelected_ and lastSelected_ correct.
     */
    selectedFrameNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(4));
    renderContext = selectedFrameNode->GetRenderContext();
    pattern_->selected_ = 5;
    pattern_->lastSelected_ = 2;
    pattern_->ItemSelectedChangedAnimation();
    EXPECT_EQ(pattern_->animateSelected_, 5);
    EXPECT_EQ(pattern_->lastSelected_, 2);
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: ShowBubble001
 * @tc.desc: Test arc indexer pattern ShowBubble function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, ShowBubble001, TestSize.Level1)
{
    Create(nullptr, LONG_ARRAY, 2);
    auto layoutProperty = frameNode_->GetLayoutProperty<ArcIndexerLayoutProperty>();
    layoutProperty->UpdateUsingPopup(true);

    /**
     * @tc.steps: step1. Test with ShowBubble true.
     * @tc.expected: popupnode_ correct.
     */
    pattern_->ShowBubble(true);
    EXPECT_NE(pattern_->popupNode_, nullptr);
    auto renderContext = pattern_->popupNode_->GetRenderContext();
    EXPECT_EQ(renderContext->GetOpacity(), 1);
}

/**
 * @tc.name: BuildArrayValueItems001
 * @tc.desc: Test arc indexer pattern BuildArrayValueItems function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, BuildArrayValueItems001, TestSize.Level1)
{
    IndexerModelNG model = Create(nullptr, std::vector<std::string>(), 0);
    auto layoutProperty = frameNode_->GetLayoutProperty<ArcIndexerLayoutProperty>();
    layoutProperty->UpdateAutoCollapse(true);
    std::vector<std::string> arrayValueStrs;

    /**
     * @tc.steps: step1. Test with CREATE_ARRAY.
     * @tc.expected: arrayValueItems correct.
     */
    pattern_->fullArrayValue_ = CREATE_ARRAY;
    pattern_->autoCollapse_ = true;
    pattern_->fullCount_ = CREATE_ARRAY.size();
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->selected_ = 2;
    pattern_->startIndex_ = 3;
    pattern_->ApplyFourPlusOneMode();
    pattern_->BuildArrayValueItems();
    for (auto item : pattern_->arcArrayValue_) {
        arrayValueStrs.push_back(item.first);
    }
    arrayValueStrs.pop_back();
    EXPECT_EQ(layoutProperty->GetActualArrayValue(), arrayValueStrs);
    auto children = frameNode_->GetChildren();
    auto childCount = static_cast<int32_t>(children.size());
    EXPECT_EQ(childCount, pattern_->arcArrayValue_.size());
    EXPECT_TRUE(layoutProperty->GetIsPopup());
}

/**
 * @tc.name: BuildArrayValueItems002
 * @tc.desc: Test arc indexer pattern BuildArrayValueItems function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, BuildArrayValueItems002, TestSize.Level1)
{
    IndexerModelNG model = Create(nullptr, std::vector<std::string>(), 0);
    auto layoutProperty = frameNode_->GetLayoutProperty<ArcIndexerLayoutProperty>();
    layoutProperty->UpdateAutoCollapse(true);
    std::vector<std::string> arrayValueStrs;

    /**
     * @tc.steps: step1. Test with LONG_ARRAY.
     * @tc.expected: arrayValueItems correct.
     */
    pattern_->fullArrayValue_ = LONG_ARRAY;
    pattern_->autoCollapse_ = true;
    pattern_->fullCount_ = LONG_ARRAY.size();
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->selected_ = 7;
    pattern_->endIndex_ = 5;
    pattern_->ApplyFourPlusOneMode();
    pattern_->BuildArrayValueItems();
    for (auto item : pattern_->arcArrayValue_) {
        arrayValueStrs.push_back(item.first);
    }
    arrayValueStrs.pop_back();
    EXPECT_EQ(layoutProperty->GetActualArrayValue(), arrayValueStrs);
    auto children = frameNode_->GetChildren();
    auto childCount = static_cast<int32_t>(children.size());
    EXPECT_EQ(childCount, pattern_->arcArrayValue_.size());
    EXPECT_TRUE(layoutProperty->GetIsPopup());
}

/**
 * @tc.name: BuildArrayValueItems003
 * @tc.desc: Test arc indexer pattern BuildArrayValueItems function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestTwoNg, BuildArrayValueItems003, TestSize.Level1)
{
    IndexerModelNG model = Create(nullptr, std::vector<std::string>(), 0);
    auto layoutProperty = frameNode_->GetLayoutProperty<ArcIndexerLayoutProperty>();
    layoutProperty->UpdateAutoCollapse(true);
    std::vector<std::string> arrayValueStrs;

    /**
     * @tc.steps: step1. Test with LONG_ARRAY and autoCollapse_ false.
     * @tc.expected: arrayValueItems correct.
     */
    pattern_->fullArrayValue_ = LONG_ARRAY;
    pattern_->autoCollapse_ = false;
    pattern_->fullCount_ = LONG_ARRAY.size();
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    pattern_->selected_ = 7;
    pattern_->endIndex_ = 5;
    pattern_->BuildFullArrayValue();
    pattern_->BuildArrayValueItems();
    for (auto item : pattern_->arcArrayValue_) {
        arrayValueStrs.push_back(item.first);
    }
    arrayValueStrs.pop_back();
    EXPECT_EQ(layoutProperty->GetActualArrayValue(), arrayValueStrs);
    auto children = frameNode_->GetChildren();
    auto childCount = static_cast<int32_t>(children.size());
    EXPECT_EQ(childCount, pattern_->arcArrayValue_.size());
    EXPECT_TRUE(layoutProperty->GetIsPopup());
}
} // namespace OHOS::Ace::NG
