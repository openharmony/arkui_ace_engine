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

constexpr double DEFAULT_POSIITON_X = -23.0;
constexpr double DEFAULT_POSIITON_Y = 44.0;
} // namespace

class ArcindexerPatternTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    IndexerModelNG Create(const std::function<void(IndexerModelNG)>& callback = nullptr,
        std::vector<std::string> arrayValue = CREATE_ARRAY, int32_t selected = 0);
    float GetFirstChildOffsetY();
    AssertionResult Selected(int32_t expectSelected);
    void MoveIndex(GestureEvent gestureEvent);
    AssertionResult Touch(TouchType touchType, float locationY, int32_t expectSelected);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ArcIndexerPattern> pattern_;
    RefPtr<IndexerEventHub> eventHub_;
    RefPtr<IndexerLayoutProperty> layoutProperty_;
    RefPtr<IndexerPaintProperty> paintProperty_;
    RefPtr<IndexerAccessibilityProperty> accessibilityProperty_;
    RefPtr<ArcIndexerContentModifier> contentModifier_;
};

void ArcindexerPatternTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));
}

void ArcindexerPatternTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ArcindexerPatternTestNg::SetUp() {}

void ArcindexerPatternTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    contentModifier_ = nullptr;
}

void ArcindexerPatternTestNg::GetInstance()
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

IndexerModelNG ArcindexerPatternTestNg::Create(
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

float ArcindexerPatternTestNg::GetFirstChildOffsetY()
{
    if (pattern_->itemCount_ > 0) {
        return GetChildRect(frameNode_, 0).GetY();
    }
    return 0.f;
}

AssertionResult ArcindexerPatternTestNg::Selected(int32_t expectSelected)
{
    return IsEqual(pattern_->GetSelected(), expectSelected);
}

void ArcindexerPatternTestNg::MoveIndex(GestureEvent gestureEvent)
{
    auto start = pattern_->panEvent_->GetActionStartEventFunc();
    auto update = pattern_->panEvent_->GetActionUpdateEventFunc();
    start(gestureEvent);
    update(gestureEvent);
}

AssertionResult ArcindexerPatternTestNg::Touch(TouchType touchType, float locationY, int32_t expectSelected)
{
    float firstOffsetY = GetFirstChildOffsetY();
    TouchEventInfo touchEventInfo = CreateTouchEventInfo(touchType, Offset(0.f, locationY + firstOffsetY));
    auto touchFuc = pattern_->touchListener_->GetTouchEventCallback();
    touchFuc(touchEventInfo);
    return Selected(expectSelected);
}

/**
 * @tc.name: ArcindexerPatternTestNg001
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer and get frameNode.
     */
    Create(
        [](IndexerModelNG model) {
            model.SetSelectedColor(Color(0x00000000));
            model.SetColor(Color(0x00000000));
            model.SetPopupColor(Color(0x00000000));
            model.SetSelectedBackgroundColor(Color(0x00000000));
            model.SetPopupBackground(Color(0x00000000));
            model.SetUsingPopup(true);
            model.SetAlignStyle(0);
            model.SetPopupHorizontalSpace(Dimension(50)); //50 is the horizontal space of popupNode
            model.SetSelected(0);
            model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP)); //-96.f is the left space of popupNode
            model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));  //48.f is the top space of popupNode
            model.SetPopupItemBackground(Color(0x00000000));
            model.SetPopupSelectedColor(Color(0x00000000));
            model.SetPopupUnselectedColor(Color(0x00000000));
            model.SetFontSize(Dimension(24)); //24 is the fontSize of item
            model.SetFontWeight(FontWeight::MEDIUM);
            model.SetAdaptiveWidth(true);
            model.SetItemSize(20.0_vp); //20.0_vp is the width of item
        },
        CREATE_ARRAY, 0);

    /**
     * @tc.steps: step2.  get layoutWrapper and indexerLayoutAlgorithm.
     * @tc.expected: step2. get layoutWrapper success.
     */
    pattern_->OnModifyDone();
    pattern_->isNewHeightCalculated_ = true;
    pattern_->autoCollapse_ = true;
    pattern_->OnModifyDone();

    pattern_->fullCount_ = -1;
    pattern_->OnModifyDone();


    pattern_->ApplyIndexChanged(true, true);
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    EXPECT_NE(layoutWrapper, nullptr);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(arcindexerLayoutAlgorithm);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<IndexerAccessibilityProperty>();
    EXPECT_EQ(arcindexerLayoutAlgorithm->GetstepAngle(), 13.5f);

    pattern_->selected_ = 5; // 5 is the index of item
    EXPECT_EQ(arcindexerLayoutAlgorithm->GetstepAngle(), 13.5f);
}

/**
 * @tc.name: ArcindexerPatternTestNg002
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer and get frameNode.
     */
    Create(
        [](IndexerModelNG model) {
            model.SetSelectedColor(Color(0x00000000));
            model.SetColor(Color(0x00000000));
            model.SetPopupColor(Color(0x00000000));
            model.SetSelectedBackgroundColor(Color(0x00000000));
            model.SetPopupBackground(Color(0x00000000));
            model.SetUsingPopup(true);
            model.SetSelected(-1);
            model.SetFontSize(Dimension(24)); //24 is the fontSize of item
            model.SetFontWeight(FontWeight::MEDIUM);
            model.SetAdaptiveWidth(true);
            model.SetItemSize(20.0_vp); //20.0_vp is the width of item
        },
        CREATE_ARRAY, 0);

    /**
     * @tc.steps: step2.  get layoutWrapper and indexerLayoutAlgorithm.
     * @tc.expected: step2. get layoutWrapper success.
     */
    layoutProperty_->Clone();
    pattern_->OnModifyDone();
    pattern_->selected_ = 10;
    pattern_->OnModifyDone();
    pattern_->ApplyIndexChanged(true, true);
    auto layoutWrapper = frameNode_->CreateLayoutWrapper();
    EXPECT_NE(layoutWrapper, nullptr);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(arcindexerLayoutAlgorithm);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<IndexerAccessibilityProperty>();
    EXPECT_EQ(arcindexerLayoutAlgorithm->GetstepAngle(), 13.5f);

    pattern_->selected_ = 5; // 5 is the index of item
    EXPECT_EQ(arcindexerLayoutAlgorithm->GetstepAngle(), 13.5f);
}

/**
 * @tc.name: ArcindexerPatternTestNg003
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg003, TestSize.Level1)
{
    Create();
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    DirtySwapConfig config;
    /**
     * @tc.steps: step1. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: step1. func return true.
     */
    pattern_->actualIndexerHeight_ = 10.0f;
    pattern_->autoCollapse_ = true;
    auto result1 = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result1);
    
    /**
     * @tc.steps: step1. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: step1. func return false.
     */
    config.skipMeasure = true;
    config.skipLayout = true;
    auto result = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ArcindexerPatternTestNg004
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg004, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. fullCount_ is equal 10 and call CollapseArrayValue.
    */
    pattern_->lastCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    EXPECT_NE(pattern_->fullCount_, INDEXER_NINE_CHARACTERS_CHECK);
    pattern_->CollapseArrayValue();

    /**
     * @tc.steps: step2. fullCount_ is equal 0 and call CollapseArrayValue.
     */
    pattern_->fullCount_ = 4;
    pattern_->CollapseArrayValue();
    EXPECT_EQ(pattern_->fullCount_, 4);
}

/**
 * @tc.name: ArcindexerPatternTestNg005
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg005, TestSize.Level1)
{
    Create();
    
    /**
     * @tc.steps: step1. isHover is false and call IndexNodeCollapsedAnimation.
     */
    pattern_->atomicAnimateOp_ = false;
    pattern_->IndexNodeCollapsedAnimation();
    EXPECT_FALSE(pattern_->collapsedProperty_);

    pattern_->atomicAnimateOp_ = true;
    pattern_->IndexNodeCollapsedAnimation();
    EXPECT_EQ(pattern_->collapsedProperty_->Get(), pattern_->stepAngle_ * 5);

    pattern_->InitCollapsedProperty();
    EXPECT_EQ(pattern_->collapsedProperty_->Get(), pattern_->stepAngle_ * 5);
}

/**
 * @tc.name: ArcindexerPatternTestNg006
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg006, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. isHover is true and call OnHover.
    */
    pattern_->IndexNodeExpandedAnimation();
    auto total = frameNode_->GetTotalChildCount();
    EXPECT_EQ(pattern_->expandedProperty_->Get(), pattern_->stepAngle_ * total);
}

/**
 * @tc.name: ArcindexerPatternTestNg007
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg007, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. isInputEventRegisted_ is true and call InitInputEvent.
    */
    auto renderContext = AceType::MakeRefPtr<RenderContext>();
    pattern_->UpdateIndexerNodeOpacityByIdx(renderContext, 1);
    EXPECT_FALSE(renderContext->GetOpacity().has_value());

    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::INVALID;
    pattern_->lastCollapsingMode_ = ArcIndexerCollapsingMode::INVALID;
    pattern_->UpdateIndexerNodeOpacityByIdx(renderContext, 5);
    EXPECT_FALSE(renderContext->GetOpacity().has_value());

    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->lastCollapsingMode_ = ArcIndexerCollapsingMode::INVALID;
    pattern_->UpdateIndexerNodeOpacityByIdx(renderContext, 5);
    EXPECT_FALSE(renderContext->GetOpacity().has_value());

    pattern_->UpdateIndexerNodeOpacityByIdx(renderContext, 5);
    EXPECT_FALSE(renderContext->GetOpacity().has_value());
}

/**
 * @tc.name: ArcindexerPatternTestNg008
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg008, TestSize.Level1)
{
    Create();
    
    /**
     * @tc.steps: step1. isHover is false and call OnHover.
     */
    pattern_->StartIndexerNodeDisappearAnimation(1);
    auto itemNode = GetChildFrameNode(frameNode_, 1);
    auto renderContext = itemNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetOpacityValue(), 0);
    pattern_->StartIndexerNodeDisappearAnimation(100);
}

/**
 * @tc.name: ArcindexerPatternTestNg009
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg009, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. isHover is true and call InitCurrentInputEvent.
    */
    int32_t nodeIndex  = 1;
    pattern_->StartIndexerNodeAppearAnimation(nodeIndex);
    auto itemNode = GetChildFrameNode(frameNode_, nodeIndex);
    auto renderContext = itemNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetOpacityValue(), 1);
}

/**
 * @tc.name: ArcindexerPatternTestNg0010
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0010, TestSize.Level1)
{
    Create(
        [](IndexerModelNG model) {
            model.SetSelectedColor(Color(0x00000000));
            model.SetColor(Color(0x00000000));
            model.SetPopupColor(Color(0x00000000));
            model.SetSelectedBackgroundColor(Color(0x00000000));
            model.SetPopupBackground(Color(0x00000000));
            model.SetUsingPopup(true);
            model.SetSelected(-1);
            model.SetAutoCollapse(false);
            model.SetFontSize(Dimension(24)); //24 is the fontSize of item
            model.SetFontWeight(FontWeight::MEDIUM);
            model.SetAdaptiveWidth(true);
            model.SetItemSize(20.0_vp); //20.0_vp is the width of item
        },
        CREATE_ARRAY, 0);
    /**
     * @tc.steps: step1. itemCount_ is -1 and call OnTouchDown.
    */
    TouchEventInfo touchEventInfo("1");
    TouchLocationInfo locationInfo(0);
    locationInfo.SetScreenLocation(Offset(200, 200));
    touchEventInfo.AddTouchLocationInfo(std::move(locationInfo));
    pattern_->OnTouchDown(touchEventInfo);
    EXPECT_EQ(pattern_->selected_, 23);
    pattern_->itemCount_ = -1;
    pattern_->OnTouchDown(touchEventInfo);
    EXPECT_EQ(pattern_->selected_, 23);
}

/**
 * @tc.name: ArcindexerPatternTestNg0011
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0011, TestSize.Level1)
{
    Create(
        [](IndexerModelNG model) {
            model.SetSelectedColor(Color(0x00000000));
            model.SetColor(Color(0x00000000));
            model.SetPopupColor(Color(0x00000000));
            model.SetSelectedBackgroundColor(Color(0x00000000));
            model.SetPopupBackground(Color(0x00000000));
            model.SetUsingPopup(true);
            model.SetSelected(-1);
            model.SetFontSize(Dimension(24)); //24 is the fontSize of item
            model.SetFontWeight(FontWeight::MEDIUM);
            model.SetAdaptiveWidth(true);
            model.SetItemSize(20.0_vp); //20.0_vp is the width of item
        },
        CREATE_ARRAY, 0);
    /**
     * @tc.steps: step1. isHover is true itemCount_is -1 and call OnTouchUp.
    */
    TouchEventInfo touchEventInfo("1");
    TouchLocationInfo locationInfo(0);
    locationInfo.SetScreenLocation(Offset(200, 200));
    touchEventInfo.AddTouchLocationInfo(std::move(locationInfo));
    pattern_->OnTouchUp(touchEventInfo);
    pattern_->isHover_ = true;
    pattern_->OnTouchUp(touchEventInfo);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
    pattern_->itemCount_ = -1;
    pattern_->OnTouchUp(touchEventInfo);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
}

/**
 * @tc.name: ArcindexerPatternTestNg0012
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0012, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call MoveIndexByOffset.
    */
    pattern_->childPressIndex_ = 1;
    pattern_->MoveIndexByOffset(Offset(0, 0));
    pattern_->isHover_ = true;
    pattern_->childPressIndex_ = -1;
    pattern_->MoveIndexByOffset(Offset(0, 0));
    pattern_->isHover_ = true;
    pattern_->childPressIndex_ = 1;
    pattern_->MoveIndexByOffset(Offset(0, 0));
     /**
     * @tc.steps: step1. itemCount_  is -1 and call MoveIndexByOffset.
    */
    pattern_->childPressIndex_ = 0;
    pattern_->MoveIndexByOffset(Offset(0, 0));
    pattern_->itemCount_ = -1;
    pattern_->MoveIndexByOffset(Offset(0, 0));
    pattern_->itemSizeRender_  = -1.0f;
    pattern_->MoveIndexByOffset(Offset(0, 0));
    EXPECT_EQ(pattern_->selected_, 0);
}

/**
 * @tc.name: ArcindexerPatternTestNg0013
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0013, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call GetSelectChildIndex.
     *  @tc.expected: step1. expect index is 0
    */
    pattern_->stepAngle_ = 720;
    int32_t index = pattern_->GetSelectChildIndex(Offset(1, 1));
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: ArcindexerPatternTestNg0014
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0014, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call KeyIndexByStep.
     * * @tc.expected: step1. expect status is true
    */
    int32_t nextIndex = 1;
    pattern_->ArcExpandedAnimation(nextIndex);
    EXPECT_GT(pattern_->contentModifier_->sweepAngle_->Get(), 0);
}

/**
 * @tc.name: ArcindexerPatternTestNg0015
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0015, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call MoveIndexByStep.
     * @tc.expected: step1. expect status1 is true
    */
    int32_t nextIndex = 1;
    pattern_->ArcCollapedAnimation(nextIndex);
    EXPECT_GT(pattern_->contentModifier_->sweepAngle_->Get(), 0);
}

/**
 * @tc.name: ArcindexerPatternTestNg0016
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0016, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call MoveIndexBySearch.
     * @tc.expected: step1. expect Search is true
    */
    pattern_->StartBubbleDisappearAnimation();
    EXPECT_FALSE(pattern_->popupNode_);
}

/**
 * @tc.name: ArcindexerPatternTestNg0017
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0017, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call OnSelect.
     * @tc.expected: step1. expect resuit is true
    */
    auto value1 = pattern_->lastSelected_ = 1;
    pattern_->OnSelect();
    EXPECT_TRUE(value1 != pattern_->animateSelected_);
    auto value2 = pattern_->selected_ = 3;
    pattern_->ItemSelectedChangedAnimation();
    EXPECT_EQ(pattern_->lastSelected_, value2);
}

/**
 * @tc.name: ArcindexerPatternTestNg0018
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0018, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call ApplyIndexChanged set arcindex theme.
    */
    pattern_->ApplyIndexChanged(false, false, false, false);
    EXPECT_TRUE(pattern_->initialized_);
}

/**
 * @tc.name: ArcindexerPatternTestNg0019
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0019, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call ShowBubble.
    */
    bool isShow = true;
    pattern_->ShowBubble(isShow);
    EXPECT_FALSE(pattern_->popupNode_);
    pattern_->itemCount_ = 2;
    pattern_->ShowBubble(isShow);
    EXPECT_FALSE(pattern_->popupNode_);
}

/**
 * @tc.name: ArcindexerPatternTestNg0020
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0020, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call ArcIndexerPressOutAnimation.
    */
    pattern_->ArcIndexerPressOutAnimation();
    pattern_->DumpInfo();
     /**
     * @tc.steps: step1. call GetPositionAngle.
     * * @tc.expected: step1.expect result is same with 0.0f
    */
    pattern_->startAngle_ = 360.0F;
    auto result = pattern_->GetPositionAngle(Offset(0, 0));
    EXPECT_EQ(result, 585);
}

/**
 * @tc.name: ArcindexerPatternTestNg0021
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0021, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call AtArcHotArea.
     * @tc.expected: step1.expect status is false
    */
    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
    bool status1 = pattern_->AtArcHotArea(Offset(-360, -360));
    EXPECT_FALSE(status1);
}

/**
 * @tc.name: ArcindexerPatternTestNg0022
 * @tc.desc: Test indexer GetPositionOfPopupNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer and get frameNode.
     */
    Create(
        [](IndexerModelNG model) {
            model.SetSelectedColor(Color(0x00000000));
            model.SetColor(Color(0x00000000));
            model.SetPopupColor(Color(0x00000000));
            model.SetSelectedBackgroundColor(Color(0x00000000));
            model.SetPopupBackground(Color(0x00000000));
            model.SetUsingPopup(true);
            model.SetAlignStyle(0);
            model.SetPopupHorizontalSpace(Dimension(50));
            model.SetSelected(0);
            model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
            model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
            model.SetPopupItemBackground(Color(0x00000000));
            model.SetPopupSelectedColor(Color(0x00000000));
            model.SetPopupUnselectedColor(Color(0x00000000));
            model.SetFontSize(Dimension(24));
            model.SetFontWeight(FontWeight::MEDIUM);
            model.SetAdaptiveWidth(true);
            model.SetItemSize(Dimension(20));
        },
        CREATE_ARRAY, 0);

    /**
    * @tc.steps: step2. Show popup
    */
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(arcindexerLayoutAlgorithm, nullptr);
    auto childCount = layoutWrapper->GetTotalChildCount();
    arcindexerLayoutAlgorithm->MeasurePopup(layoutWrapper, childCount);
    auto offset = arcindexerLayoutAlgorithm->GetPositionOfPopupNode(layoutWrapper);
    EXPECT_EQ(offset, OffsetT<Dimension>(Dimension(DEFAULT_POSIITON_X), Dimension(DEFAULT_POSIITON_Y)));
}

/**
 * @tc.name: ArcindexerPatternTestNg0023
 * @tc.desc: Test indexer FireAccessbilityExpanded function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0023, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call FireAccessbilityExpanded.
     * @tc.expected: step1.expect status is false
    */
    pattern_->FireAccessbilityExpanded();
    EXPECT_FALSE(pattern_->isClickActionFire_);
}

/**
 * @tc.name: ArcindexerPatternTestNg0024
 * @tc.desc: Test indexer FireAccessbilityCollapsed function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0024, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call FireAccessbilityExpanded.
     * @tc.expected: step1.expect currectCollapsingMode_ equal to lastCollapsingMode_.
    */
    pattern_->lastCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->FireAccessbilityCollapsed();
    EXPECT_EQ(pattern_->currectCollapsingMode_, pattern_->lastCollapsingMode_);
}

/**
 * @tc.name: ArcindexerPatternTestNg0025
 * @tc.desc: Test Arcindexer layoutProperty ToJsonValue function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer.
     */
    Create();
    auto arcLayoutProperty = AceType::MakeRefPtr<ArcIndexerLayoutProperty>();
    ASSERT_NE(arcLayoutProperty, nullptr);
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    arcLayoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("selected"), "0");
    EXPECT_EQ(json->GetString("color"), "#FFFFFFFF");
    EXPECT_EQ(json->GetString("selectedColor"), "#FFFFFFFF");
    EXPECT_EQ(json->GetString("popupColor"), "#FFFFFFFF");
    EXPECT_EQ(json->GetString("popupPosition"), "");
    EXPECT_EQ(json->GetString("arrayValue"), "");
    EXPECT_EQ(json->GetString("font"), "");
    EXPECT_EQ(json->GetString("selectedFont"), "");
    EXPECT_EQ(json->GetString("popupFont"), "");
    EXPECT_EQ(json->GetString("autoCollapse"), "false");
}

/**
 * @tc.name: ArcindexerPatternTestNg0026
 * @tc.desc: Test Arcindexer layoutProperty ToJsonValue function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer and get frameNode.
     */
    Create(
        [](IndexerModelNG model) {
            model.SetSelectedColor(Color(0x00000000));
            model.SetColor(Color(0x00000000));
            model.SetPopupColor(Color(0x00000000));
            model.SetSelectedBackgroundColor(Color(0x00000000));
            model.SetPopupBackground(Color(0x00000000));
            model.SetUsingPopup(true);
            model.SetAlignStyle(0);
            model.SetPopupHorizontalSpace(Dimension(50));
            model.SetSelected(0);
            model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
            model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
            model.SetPopupItemBackground(Color(0x00000000));
            model.SetPopupSelectedColor(Color(0x00000000));
            model.SetPopupUnselectedColor(Color(0x00000000));
            model.SetFontSize(Dimension(24));
            model.SetFontWeight(FontWeight::MEDIUM);
            model.SetAdaptiveWidth(true);
            model.SetItemSize(Dimension(20));
        },
        CREATE_ARRAY, 0);

    auto layoutProperty  = AceType::DynamicCast<ArcIndexerLayoutProperty>(layoutProperty_);

    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("selected"), "0");
    EXPECT_EQ(json->GetString("color"), "#00000000");
    EXPECT_EQ(json->GetString("selectedColor"), "#00000000");
    EXPECT_EQ(json->GetString("popupColor"), "#00000000");
    EXPECT_EQ(json->GetString("itemSize"), "20.00px");
    EXPECT_EQ(json->GetString("popupPosition"), "");
    EXPECT_EQ(json->GetString("arrayValue"), "");
    EXPECT_EQ(json->GetString("font"), "");
    EXPECT_EQ(json->GetString("selectedFont"), "");
    EXPECT_EQ(json->GetString("popupFont"), "");
    EXPECT_EQ(json->GetString("autoCollapse"), "false");
}

/**
 * @tc.name: ArcindexerPatternTestNg0027
 * @tc.desc: Test indexer onDraw DrawArc function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0027, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. call MoveIndexByStep.
     * @tc.expected: step1. expect status1 is true
    */
    RSCanvas canvas;
    DrawingContext context { canvas, 0.0, 0.0 };
    ArcIndexerContentModifier modifier;
    modifier.sweepAngle_->Set(180);
    modifier.stepAngle_->Set(180);
    modifier.onDraw(context);
    modifier.DrawArc(context);
    EXPECT_FALSE(modifier.startAngle_->Get() > 0);
    modifier.sweepAngle_->Set(-1.0f);
    EXPECT_TRUE(modifier.sweepAngle_ > 0);
    modifier.onDraw(context);
    EXPECT_TRUE(modifier.sweepAngle_->Get() < 0);
}

/**
 * @tc.name: ArcindexerPatternTestNg0028
 * @tc.desc: Test indexer onDraw DrawArc function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0028, TestSize.Level1)
{
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
    RSCanvas canvas;
    DrawingContext context { canvas, 0.0, 0.0 };
    ArcIndexerContentModifier modifier;
    modifier.sweepAngle_->Set(180);
    modifier.stepAngle_->Set(180);
    modifier.onDraw(context);
    modifier.DrawArc(context);
    EXPECT_FALSE(modifier.startAngle_->Get() > 0);
    modifier.sweepAngle_->Set(-1.0f);
    EXPECT_TRUE(modifier.sweepAngle_ > 0);
    modifier.onDraw(context);
    EXPECT_TRUE(modifier.sweepAngle_->Get() < 0);
}

/**
 * @tc.name: ArcindexerPatternTestNg0029
 * @tc.desc: Test indexer UpdateStartAndEndIndexByTouch function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0029, TestSize.Level1)
{
    Create();
    pattern_->UpdateStartAndEndIndexByTouch();
    EXPECT_EQ(pattern_->focusIndex_, (pattern_->selected_ - pattern_->startIndex_));
    pattern_->autoCollapse_ = true;
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->UpdateStartAndEndIndexByTouch();
    EXPECT_EQ(pattern_->focusIndex_, (pattern_->selected_ - pattern_->startIndex_));
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    pattern_->UpdateStartAndEndIndexByTouch();
    EXPECT_EQ(pattern_->focusIndex_, (pattern_->selected_ - pattern_->startIndex_));
    pattern_->fullCount_ = 1;
    pattern_->UpdateStartAndEndIndexByTouch();
    EXPECT_EQ(pattern_->startIndex_, 0);
    pattern_->fullCount_ = 34;
    pattern_->selected_ = 50;
    pattern_->startIndex_ = 100;
    pattern_->UpdateStartAndEndIndexByTouch();
    EXPECT_EQ(pattern_->focusIndex_, (pattern_->selected_ - pattern_->startIndex_));
}

/**
 * @tc.name: ArcindexerPatternTestNg0030
 * @tc.desc: Test indexer RemoveAccessibilityClickEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0030, TestSize.Level1)
{
    Create();
    pattern_->collapsedNode_ = frameNode_;
    pattern_->expandedNode_ = frameNode_;
    pattern_->RemoveAccessibilityClickEvent();
    EXPECT_EQ(pattern_->collapsedClickListener_, nullptr);

    EXPECT_EQ(pattern_->expandedClickListener_, nullptr);
    GestureEventFunc collCallback = [](GestureEvent& info) {};
    pattern_->collapsedClickListener_ = AceType::MakeRefPtr<ClickEvent>(std::move(collCallback));
    GestureEventFunc expandCallback = [](GestureEvent& info) {};
    pattern_->expandedClickListener_ = AceType::MakeRefPtr<ClickEvent>(std::move(expandCallback));
    pattern_->RemoveAccessibilityClickEvent();
    EXPECT_EQ(pattern_->collapsedClickListener_, nullptr);

    EXPECT_EQ(pattern_->expandedClickListener_, nullptr);
}

/**
 * @tc.name: ArcindexerPatternTestNg0031
 * @tc.desc: Test indexer OnState function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcindexerPatternTestNg0031, TestSize.Level1)
{
    Create();
    WeakPtr<ArcIndexerPattern> weakparent = AceType::WeakClaim(AceType::RawPtr(pattern_));
    pattern_->accessibilitySAObserverCallback_ = std::make_shared<ArcIndexerAccessibilitySAObserverCallback>(
        weakparent, frameNode_->GetAccessibilityId());
    pattern_->accessibilitySAObserverCallback_->OnState(false);
    EXPECT_FALSE(pattern_->isScreenReaderOn_);

    pattern_->accessibilitySAObserverCallback_->OnState(true);
    EXPECT_TRUE(pattern_->isScreenReaderOn_);
}

/**
 * @tc.name: InitExpandedProperty001
 * @tc.desc: Test arc indexer pattern InitExpandedProperty function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitExpandedProperty001, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. expandedProperty_ is nullptr.
    */
    pattern_->InitExpandedProperty();
    EXPECT_TRUE(pattern_->expandedProperty_);

    /**
     * @tc.steps: step2. expandedProperty_ is not nullptr.
    */
    pattern_->InitExpandedProperty();
    EXPECT_TRUE(pattern_->expandedProperty_);
}

/**
 * @tc.name: InitExpandedProperty002
 * @tc.desc: Test arc indexer pattern InitExpandedProperty function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitExpandedProperty002, TestSize.Level1)
{
    Create();
    /**
     * @tc.steps: step1. expandedProperty_ is nullptr.
    */
    pattern_->InitExpandedProperty();
    EXPECT_TRUE(pattern_->expandedProperty_);

    /**
     * @tc.steps: step2. expandedProperty_ is not nullptr.
    */
    pattern_->atomicAnimateOp_ = true;
    pattern_->IndexNodeExpandedAnimation();
    EXPECT_TRUE(pattern_->expandedProperty_);
}

/**
 * @tc.name: AtArcHotArea001
 * @tc.desc: Test arc indexer pattern AtArcHotArea function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, AtArcHotArea001, TestSize.Level1)
{
    Create();
    pattern_->sweepAngle_ = 500.0;
    pattern_->startAngle_ = 500.0;
    pattern_->stepAngle_ = 500.0;
    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
}

/**
 * @tc.name: AtArcHotArea002
 * @tc.desc: Test arc indexer pattern AtArcHotArea function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, AtArcHotArea002, TestSize.Level1)
{
    Create();
    pattern_->isScreenReaderOn_ = true;
    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
}

/**
 * @tc.name: AtArcHotArea003
 * @tc.desc: Test arc indexer pattern AtArcHotArea function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, AtArcHotArea003, TestSize.Level1)
{
    Create();
    pattern_->sweepAngle_ = 500.0;
    pattern_->startAngle_ = 500.0;
    pattern_->stepAngle_ = 500.0;
    pattern_->arcRadius_ = 0.0;
    pattern_->itemRadius_ = 0.0;
    pattern_->arcCenter_ = OffsetF(0, 0);
    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_TRUE(status);
}

/**
 * @tc.name: InitAccessibilityClickEvent001
 * @tc.desc: Test arc indexer pattern InitAccessibilityClickEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitAccessibilityClickEvent001, TestSize.Level1)
{
    Create();
    pattern_->arcArrayValue_.push_back(
        std::pair(StringUtils::Str16ToStr8(ARC_INDEXER_STR_EXPANDED), ArcIndexerBarState::EXPANDED));
    pattern_->arcArrayValue_.push_back(
        std::pair(StringUtils::Str16ToStr8(ARC_INDEXER_STR_COLLAPSED), ArcIndexerBarState::COLLAPSED));

    pattern_->isScreenReaderOn_ = true;
    /**
     * @tc.steps: step1. expandedNode
    */
    auto nodeStr0 = pattern_->GetChildNodeContent(0);
    pattern_->SetChildNodeStyle(0, nodeStr0, true);
    auto child0 = pattern_->GetHost()->GetChildByIndex(0);
    EXPECT_TRUE(child0);
    auto childNode0 = child0->GetHostNode();
    EXPECT_TRUE(childNode0);
    pattern_->expandedNode_ = childNode0;
    pattern_->SetChildNodeAccessibility(childNode0, nodeStr0);
    pattern_->InitAccessibilityClickEvent();
    EXPECT_EQ(pattern_->focusIndex_, 0);

    /**
     * @tc.steps: step2. collapsedNode
    */
    auto nodeStr1 = pattern_->GetChildNodeContent(1);
    pattern_->SetChildNodeStyle(1, nodeStr1, true);
    auto child1 = pattern_->GetHost()->GetChildByIndex(1);
    EXPECT_TRUE(child1);
    auto childNode1 = child1->GetHostNode();
    EXPECT_TRUE(childNode1);
    pattern_->SetChildNodeAccessibility(childNode1, nodeStr1);
    pattern_->InitAccessibilityClickEvent();
    EXPECT_EQ(pattern_->focusIndex_, 0);
}

/**
 * @tc.name: UpdateStartAndEndIndexbySelected001
 * @tc.desc: Test indexer UpdateStartAndEndIndexbySelected function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, UpdateStartAndEndIndexbySelected001, TestSize.Level1)
{
    Create();

    pattern_->autoCollapse_ = false;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, (pattern_->selected_ - pattern_->startIndex_));
    pattern_->autoCollapse_ = true;
    pattern_->fullCount_ = 20;
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->endIndex_  = 21;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, (pattern_->selected_ - pattern_->startIndex_));

    pattern_->selected_ = 9;
    pattern_->startIndex_ = 1;
    pattern_->endIndex_  = 15;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, pattern_->selected_);

    pattern_->selected_ = 30;
    pattern_->endIndex_  = 30;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, ARC_INDEXER_COLLAPSE_ITEM_COUNT - 1);

    pattern_->selected_ = 5;
    pattern_->startIndex_  = 8;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, 0);

    pattern_->selected_ = -3;
    pattern_->startIndex_  = -1;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, 0);

    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, pattern_->selected_);
}

/**
 * @tc.name: InitPanEvent001
 * @tc.desc: Test ArcIndexerPattern::InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitPanEvent001, TestSize.Level1)
{
    Create();
    auto gesture = pattern_->GetHost()->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    pattern_->InitPanEvent(gesture);
    auto actionStart = pattern_->panEvent_->GetActionStartEventFunc();
    ASSERT_NE(actionStart, nullptr);
    GestureEvent info = GestureEvent();
    actionStart(info);

    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
}

/**
 * @tc.name: InitPanEvent002
 * @tc.desc: Test ArcIndexerPattern::InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitPanEvent002, TestSize.Level1)
{
    Create();
    auto gesture = pattern_->GetHost()->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    pattern_->InitPanEvent(gesture);
    auto actionUpdate = pattern_->panEvent_->GetActionUpdateEventFunc();
    ASSERT_NE(actionUpdate, nullptr);
    GestureEvent info = GestureEvent();
    actionUpdate(info);

    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
}

/**
 * @tc.name: InitPanEvent003
 * @tc.desc: Test ArcIndexerPattern::InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitPanEvent003, TestSize.Level1)
{
    Create();
    auto gesture = pattern_->GetHost()->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    pattern_->InitPanEvent(gesture);
    auto actionEnd = pattern_->panEvent_->GetActionEndEventFunc();
    ASSERT_NE(actionEnd, nullptr);
    GestureEvent info = GestureEvent();
    actionEnd(info);

    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
}

/**
 * @tc.name: InitPanEvent004
 * @tc.desc: Test ArcIndexerPattern::InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitPanEvent004, TestSize.Level1)
{
    Create();
    auto gesture = pattern_->GetHost()->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    pattern_->InitPanEvent(gesture);
    pattern_->atomicAnimateOp_ = false;
    auto actionStart = pattern_->panEvent_->GetActionStartEventFunc();
    ASSERT_NE(actionStart, nullptr);
    GestureEvent info = GestureEvent();
    actionStart(info);

    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
}

/**
 * @tc.name: InitPanEvent005
 * @tc.desc: Test ArcIndexerPattern::InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitPanEvent005, TestSize.Level1)
{
    Create();
    auto gesture = pattern_->GetHost()->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    pattern_->InitPanEvent(gesture);
    auto actionStart = pattern_->panEvent_->GetActionStartEventFunc();
    ASSERT_NE(actionStart, nullptr);
    GestureEvent info = GestureEvent();
    info.SetInputEventType(InputEventType::AXIS);
    actionStart(info);

    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
}

/**
 * @tc.name: InitPanEvent006
 * @tc.desc: Test ArcIndexerPattern::InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitPanEvent006, TestSize.Level1)
{
    Create();
    auto gesture = pattern_->GetHost()->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    pattern_->InitPanEvent(gesture);
    pattern_->atomicAnimateOp_ = false;
    auto actionUpdate = pattern_->panEvent_->GetActionUpdateEventFunc();
    ASSERT_NE(actionUpdate, nullptr);
    GestureEvent info = GestureEvent();
    actionUpdate(info);

    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
}

/**
 * @tc.name: InitPanEvent007
 * @tc.desc: Test ArcIndexerPattern::InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitPanEvent007, TestSize.Level1)
{
    Create();
    auto gesture = pattern_->GetHost()->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    pattern_->InitPanEvent(gesture);
    auto actionUpdate = pattern_->panEvent_->GetActionUpdateEventFunc();
    ASSERT_NE(actionUpdate, nullptr);
    GestureEvent info = GestureEvent();
    info.SetInputEventType(InputEventType::AXIS);
    actionUpdate(info);

    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
}

/**
 * @tc.name: InitPanEvent008
 * @tc.desc: Test ArcIndexerPattern::InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitPanEvent008, TestSize.Level1)
{
    Create();
    auto gesture = pattern_->GetHost()->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    pattern_->InitPanEvent(gesture);
    auto gestureJudgeNativeFunc = gesture->GetOnGestureJudgeNativeBeginCallback();
    ASSERT_NE(gestureJudgeNativeFunc, nullptr);
    RefPtr<GestureInfo> gestureInfo = AccessibilityManagerNG::MakeRefPtr<GestureInfo>();
    auto info = std::make_shared<PanGestureEvent>();
    FingerInfo fingerInfo;
    std::list<FingerInfo> fingerList;
    fingerList.emplace_back(fingerInfo);
    info->SetFingerList(fingerList);
    gestureJudgeNativeFunc(gestureInfo, info);

    bool status = pattern_->AtArcHotArea(Offset(0, 0));
    EXPECT_FALSE(status);
}

/**
 * @tc.name: GetActualIndex001
 * @tc.desc: Test ArcIndexerPattern::GetActualIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, GetActualIndex001, TestSize.Level1)
{
    Create();
    pattern_->autoCollapse_ = true;
    pattern_->selected_ = 0;
    int32_t result = pattern_->GetActualIndex(0);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: GetActualIndex002
 * @tc.desc: Test ArcIndexerPattern::GetActualIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, GetActualIndex002, TestSize.Level1)
{
    Create();
    pattern_->autoCollapse_ = true;
    pattern_->selected_ = 1;
    int32_t result = pattern_->GetActualIndex(0);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: FireOnSelect001
 * @tc.desc: Test ArcIndexerPattern::FireOnSelect
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, FireOnSelect001, TestSize.Level1)
{
    Create();
    pattern_->selected_ = 0;

    OnSelectedEvent onSelected = [](int32_t value) {};
    OnSelectedEvent changeEvent = [](int32_t value) {};
    OnSelectedEvent creatChangeEvent = [](int32_t value) {};
    eventHub_->SetChangeEvent(std::move(changeEvent));
    eventHub_->SetCreatChangeEvent(std::move(creatChangeEvent));
    eventHub_->SetOnSelected(std::move(onSelected));

    pattern_->FireOnSelect(0, true);
    EXPECT_EQ(pattern_->selected_, 0);
}

/**
 * @tc.name: InitArrayValue001
 * @tc.desc: Test ArcIndexerPattern::InitArrayValue
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitArrayValue001, TestSize.Level1)
{
    Create();
    bool autoCollapseModeChanged = true;
    auto layoutProperty = pattern_->GetHost()->GetLayoutProperty<ArcIndexerLayoutProperty>();
    auto propSelect = layoutProperty->GetSelected().value();

    layoutProperty->UpdateSelected(-10);
    pattern_->InitArrayValue(autoCollapseModeChanged);
    propSelect = layoutProperty->GetSelected().value();
    ASSERT_EQ(propSelect, 0);

    for (int32_t i = 0; i < CREATE_ARRAY_1.size(); ++i) {
        if (i >= 0 && i < CREATE_ARRAY_1.size()) {
            pattern_->arcArrayValue_.push_back(std::pair(CREATE_ARRAY_1.at(i), ArcIndexerBarState::INVALID));
        }
    }
    layoutProperty->UpdateSelected(10);
    pattern_->InitArrayValue(autoCollapseModeChanged);
    propSelect = layoutProperty->GetSelected().value();
    ASSERT_EQ(propSelect, 10);

    layoutProperty->UpdateSelected(10);
    pattern_->startIndex_ = 2;
    pattern_->selected_ = 8;
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_FALSE(pattern_->selectChanged_);
}

/**
 * @tc.name: StartBubbleDisappearAnimation001
 * @tc.desc: Test ArcIndexerPattern::StartBubbleDisappearAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, StartBubbleDisappearAnimation001, TestSize.Level1)
{
    Create();
    auto frameNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    pattern_->selected_ = 0;
    pattern_->popupNode_ = Referenced::RawPtr(frameNode);
    pattern_->StartBubbleDisappearAnimation();
    EXPECT_EQ(pattern_->selected_, 0);
}

/**
 * @tc.name: MoveIndexByOffset001
 * @tc.desc: Test ArcIndexerPattern::MoveIndexByOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, MoveIndexByOffset001, TestSize.Level1)
{
    Create();
    auto frameNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    pattern_->itemCount_ = 3;
    pattern_->arcCenter_ = OffsetF(3.0, 3.0);
    pattern_->startAngle_ = 60.0F;
    pattern_->stepAngle_ = 90.f;
    pattern_->arcArrayValue_.push_back(std::pair("COLLAPSED", ArcIndexerBarState::COLLAPSED));
    Offset offset(10.0, 10.0);
    pattern_->MoveIndexByOffset(offset);
    EXPECT_TRUE(pattern_->isNewHeightCalculated_);
}

/**
 * @tc.name: MoveIndexByOffset002
 * @tc.desc: Test ArcIndexerPattern::MoveIndexByOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, MoveIndexByOffset002, TestSize.Level1)
{
    auto arcIndexerPattern = AceType::MakeRefPtr<ArcIndexerPattern>();
    auto frameNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    arcIndexerPattern->itemCount_ = 3;
    arcIndexerPattern->arcCenter_ = OffsetF(3.0, 3.0);
    arcIndexerPattern->startAngle_ = 60.0F;
    arcIndexerPattern->stepAngle_ = 90.f;
    arcIndexerPattern->childPressIndex_ = 0;
    arcIndexerPattern->atomicAnimateOp_ = false;
    arcIndexerPattern->contentModifier_ = AceType::MakeRefPtr<ArcIndexerContentModifier>();
    arcIndexerPattern->arcArrayValue_.push_back(std::pair("COLLAPSED", ArcIndexerBarState::COLLAPSED));
    arcIndexerPattern->arcArrayValue_.push_back(std::pair("COLLAPSED", ArcIndexerBarState::COLLAPSED));
    Offset offset(10.0, 10.0);
    arcIndexerPattern->MoveIndexByOffset(offset);
    EXPECT_TRUE(arcIndexerPattern->isNewHeightCalculated_);
    EXPECT_EQ(arcIndexerPattern->currectCollapsingMode_, ArcIndexerCollapsingMode::FOUR);
}

/**
 * @tc.name: MoveIndexByOffset003
 * @tc.desc: Test ArcIndexerPattern::MoveIndexByOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, MoveIndexByOffset003, TestSize.Level1)
{
    auto arcIndexerPattern = AceType::MakeRefPtr<ArcIndexerPattern>();
    auto frameNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    arcIndexerPattern->itemCount_ = 3;
    arcIndexerPattern->arcCenter_ = OffsetF(3.0, 3.0);
    arcIndexerPattern->startAngle_ = 60.0F;
    arcIndexerPattern->stepAngle_ = 90.f;
    arcIndexerPattern->childPressIndex_ = 0;
    arcIndexerPattern->atomicAnimateOp_ = false;
    arcIndexerPattern->contentModifier_ = AceType::MakeRefPtr<ArcIndexerContentModifier>();
    arcIndexerPattern->currectCollapsingMode_ = ArcIndexerCollapsingMode::INVALID;
    arcIndexerPattern->arcArrayValue_.push_back(std::pair("EXPANDED", ArcIndexerBarState::EXPANDED));
    arcIndexerPattern->arcArrayValue_.push_back(std::pair("COLLAPSED", ArcIndexerBarState::COLLAPSED));
    Offset offset(10.0, 10.0);
    arcIndexerPattern->MoveIndexByOffset(offset);
    EXPECT_TRUE(arcIndexerPattern->isNewHeightCalculated_);
    EXPECT_EQ(arcIndexerPattern->currectCollapsingMode_, ArcIndexerCollapsingMode::NONE);
}

/**
 * @tc.name: MoveIndexByOffset004
 * @tc.desc: Test ArcIndexerPattern::MoveIndexByOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, MoveIndexByOffset004, TestSize.Level1)
{
    auto arcIndexerPattern = AceType::MakeRefPtr<ArcIndexerPattern>();
    auto frameNode = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    arcIndexerPattern->itemCount_ = 3;
    arcIndexerPattern->arcCenter_ = OffsetF(3.0, 3.0);
    arcIndexerPattern->startAngle_ = 60.0F;
    arcIndexerPattern->stepAngle_ = 90.f;
    arcIndexerPattern->atomicAnimateOp_ = false;
    arcIndexerPattern->autoCollapse_ = false;
    arcIndexerPattern->contentModifier_ = AceType::MakeRefPtr<ArcIndexerContentModifier>();
    arcIndexerPattern->currectCollapsingMode_ = ArcIndexerCollapsingMode::INVALID;
    arcIndexerPattern->arcArrayValue_.push_back(std::pair("COLLAPSED", ArcIndexerBarState::COLLAPSED));
    arcIndexerPattern->arcArrayValue_.push_back(std::pair("COLLAPSED", ArcIndexerBarState::COLLAPSED));
    Offset offset(10.0, 10.0);
    arcIndexerPattern->MoveIndexByOffset(offset);
    EXPECT_TRUE(arcIndexerPattern->isNewHeightCalculated_);
    EXPECT_EQ(arcIndexerPattern->currectCollapsingMode_, ArcIndexerCollapsingMode::NONE);
}

/**
 * @tc.name: MoveIndexByOffset005
 * @tc.desc: Test ArcIndexerPattern::MoveIndexByOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, MoveIndexByOffset005, TestSize.Level1)
{
    auto arcIndexerPattern = AceType::MakeRefPtr<ArcIndexerPattern>();
    arcIndexerPattern->itemCount_ = 3;
    arcIndexerPattern->arcCenter_ = OffsetF(3.0, 3.0);
    arcIndexerPattern->startAngle_ = 60.0F;
    arcIndexerPattern->stepAngle_ = 90.f;
    arcIndexerPattern->atomicAnimateOp_ = false;
    arcIndexerPattern->autoCollapse_ = false;
    arcIndexerPattern->childPressIndex_ = 0;
    arcIndexerPattern->contentModifier_ = AceType::MakeRefPtr<ArcIndexerContentModifier>();
    arcIndexerPattern->currectCollapsingMode_ = ArcIndexerCollapsingMode::INVALID;
    arcIndexerPattern->arcArrayValue_.push_back(std::pair("INVALID", ArcIndexerBarState::INVALID));
    Offset offset(10.0, 10.0);
    arcIndexerPattern->MoveIndexByOffset(offset);
    EXPECT_FALSE(arcIndexerPattern->isNewHeightCalculated_);
}

/**
 * @tc.name: OnTouchUp001
 * @tc.desc: Test ArcIndexerPattern::OnTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, OnTouchUp001, TestSize.Level1)
{
    auto arcIndexerPattern = AceType::MakeRefPtr<ArcIndexerPattern>();
    arcIndexerPattern->itemCount_ = 3;
    arcIndexerPattern->childPressIndex_ = 1;
    TouchEventInfo info("touch");
    arcIndexerPattern->OnTouchUp(info);
    EXPECT_EQ(arcIndexerPattern->childPressIndex_, -1);
}

/**
 * @tc.name: ArcExpandedAnimation001
 * @tc.desc: Test ArcIndexerPattern::ArcExpandedAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ArcExpandedAnimation001, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode("childNode", 1, AceType::MakeRefPtr<ArcIndexerPattern>(), true);
    auto arcIndexerPattern = node->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(arcIndexerPattern, nullptr);
    arcIndexerPattern->itemCount_ = 3;
    arcIndexerPattern->childPressIndex_ = 1;
    arcIndexerPattern->startAngle_ = 10.0F;
    arcIndexerPattern->stepAngle_ = 100.f;
    RefPtr<AnimatablePropertyFloat> sweepAngle = AceType::MakeRefPtr<AnimatablePropertyFloat>(180.0f);
    arcIndexerPattern->contentModifier_ = AceType::MakeRefPtr<ArcIndexerContentModifier>();
    arcIndexerPattern->contentModifier_->sweepAngle_ = sweepAngle;
    arcIndexerPattern->ArcExpandedAnimation(0);
    EXPECT_EQ(arcIndexerPattern->contentModifier_->sweepAngle_->Get(), 360.0f);
}

/**
 * @tc.name: InitArrayValueTestNg001
 * @tc.desc: Test arc indexer pattern InitArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitArrayValueTestNg001, TestSize.Level1)
{
    IndexerModelNG model = Create(nullptr, std::vector<std::string>(), 0);
    model.SetAutoCollapse(true);
    bool autoCollapseModeChanged = false;

    /**
     * @tc.steps: step1. Test with CREATE_ARRAY_1.
     * @tc.expected: InitArrayValue correct.
     */
    model.SetArrayValue(AceType::RawPtr(frameNode_), CREATE_ARRAY_1);
    pattern_->isNewHeightCalculated_ = false;
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->lastCollapsingMode_, ArcIndexerCollapsingMode::NONE);
    EXPECT_EQ(pattern_->currectCollapsingMode_, ArcIndexerCollapsingMode::FOUR);
    EXPECT_EQ(pattern_->fullArrayValue_, CREATE_ARRAY_1);
    EXPECT_EQ(pattern_->fullCount_, CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_FALSE(autoCollapseModeChanged);

    /**
     * @tc.steps: step2. Test with voidArray.
     * @tc.expected: InitArrayValue correct.
     */
    model.SetArrayValue(AceType::RawPtr(frameNode_), std::vector<std::string>());
    pattern_->isNewHeightCalculated_ = false;
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->lastCollapsingMode_, ArcIndexerCollapsingMode::FOUR);
    EXPECT_EQ(pattern_->currectCollapsingMode_, ArcIndexerCollapsingMode::NONE);
    EXPECT_EQ(pattern_->fullArrayValue_, std::vector<std::string>());
    EXPECT_EQ(pattern_->fullCount_, 0);
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_FALSE(autoCollapseModeChanged);
}

/**
 * @tc.name: InitArrayValueTestNg002
 * @tc.desc: Test arc indexer pattern InitArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitArrayValueTestNg002, TestSize.Level1)
{
    IndexerModelNG model = Create(nullptr, std::vector<std::string>(), 0);
    model.SetAutoCollapse(true);
    bool autoCollapseModeChanged = false;

    /**
     * @tc.steps: step1. Test with CREATE_ARRAY_2.
     * @tc.expected: InitArrayValue correct.
     */
    model.SetArrayValue(AceType::RawPtr(frameNode_), CREATE_ARRAY_2);
    pattern_->isNewHeightCalculated_ = false;
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->lastCollapsingMode_, ArcIndexerCollapsingMode::NONE);
    EXPECT_EQ(pattern_->currectCollapsingMode_, ArcIndexerCollapsingMode::FOUR);
    EXPECT_EQ(pattern_->fullArrayValue_, CREATE_ARRAY_2);
    EXPECT_EQ(pattern_->fullCount_, CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_FALSE(autoCollapseModeChanged);

    /**
     * @tc.steps: step2. Test with autoCollapseMode changed.
     * @tc.expected: InitArrayValue correct.
     */
    layoutProperty_->UpdateAutoCollapse(false);
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->lastCollapsingMode_, ArcIndexerCollapsingMode::FOUR);
    EXPECT_EQ(pattern_->currectCollapsingMode_, ArcIndexerCollapsingMode::NONE);
    EXPECT_EQ(pattern_->fullArrayValue_, CREATE_ARRAY_2);
    EXPECT_EQ(pattern_->fullCount_, CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_FALSE(pattern_->autoCollapse_);
    EXPECT_TRUE(autoCollapseModeChanged);

    /**
     * @tc.steps: step3. Test with selected_ changed.
     * @tc.expected: selected_ correct.
     */
    layoutProperty_->UpdateSelected(-1);
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_TRUE(pattern_->selectChanged_);
    layoutProperty_->UpdateSelected(CREATE_ARRAY_2.size());
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->selected_, CREATE_ARRAY_2.size() - 1);
    EXPECT_TRUE(pattern_->selectChanged_);
    layoutProperty_->UpdateSelected(5);
    pattern_->startIndex_ = 2;
    pattern_->selected_ = 3;
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->selected_, 5);
    EXPECT_FALSE(pattern_->selectChanged_);
}

/**
 * @tc.name: InitArrayValueTestNg003
 * @tc.desc: Test arc indexer pattern InitArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, InitArrayValueTestNg003, TestSize.Level1)
{
    IndexerModelNG model = Create(nullptr, std::vector<std::string>(), 0);
    bool autoCollapseModeChanged = false;

    /**
     * @tc.steps: step1. Test with CREATE_ARRAY and autoCollapse_ false.
     * @tc.expected: fullArrayValue_ correct.
     */
    pattern_->isNewHeightCalculated_ = false;
    layoutProperty_->UpdateArrayValue(CREATE_ARRAY);
    pattern_->autoCollapse_ = false;
    layoutProperty_->UpdateAutoCollapse(false);
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->fullArrayValue_, CREATE_ARRAY);
    EXPECT_EQ(pattern_->fullCount_, CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->currectCollapsingMode_, ArcIndexerCollapsingMode::NONE);
    EXPECT_EQ(pattern_->lastCollapsingMode_, ArcIndexerCollapsingMode::NONE);
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_FALSE(autoCollapseModeChanged);

    /**
     * @tc.steps: step2. Test with CREATE_ARRAY and autoCollapse_ true.
     * @tc.expected: fullArrayValue_ correct.
     */
    pattern_->autoCollapse_ = false;
    pattern_->isNewHeightCalculated_ = false;
    layoutProperty_->UpdateAutoCollapse(true);
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->fullArrayValue_, CREATE_ARRAY);
    EXPECT_EQ(pattern_->fullCount_, CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->currectCollapsingMode_, ArcIndexerCollapsingMode::FOUR);
    EXPECT_EQ(pattern_->lastCollapsingMode_, ArcIndexerCollapsingMode::NONE);
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_TRUE(autoCollapseModeChanged);

    /**
     * @tc.steps: step3. Test with selected_ changed.
     * @tc.expected: selected_ correct.
     */
    layoutProperty_->UpdateSelected(-1);
    pattern_->selected_ = 1;
    pattern_->isNewHeightCalculated_ = false;
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_TRUE(pattern_->selectChanged_);
    layoutProperty_->UpdateSelected(CREATE_ARRAY.size());
    pattern_->isNewHeightCalculated_ = false;
    pattern_->InitArrayValue(autoCollapseModeChanged);
    EXPECT_EQ(pattern_->selected_, 3);
    EXPECT_TRUE(pattern_->selectChanged_);
}

/**
 * @tc.name: UpdateStartAndEndIndexbySelectedTestNg001
 * @tc.desc: Test arc indexer pattern UpdateStartAndEndIndexbySelected function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, UpdateStartAndEndIndexbySelectedTestNg001, TestSize.Level1)
{
    IndexerModelNG model = Create(nullptr, CREATE_ARRAY_2, 0);

    /**
     * @tc.steps: step1. Test with autoCollapse_ false.
     * @tc.expected: focusIndex_ 5.
     */
    pattern_->autoCollapse_ = false;
    pattern_->selected_ = 5;
    pattern_->focusIndex_ = 0;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, 5);

    /**
     * @tc.steps: step2. Test with autoCollapse_ true and currectCollapsingMode_ NONE.
     * @tc.expected: focusIndex_ 5.
     */
    pattern_->autoCollapse_ = true;
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    pattern_->focusIndex_ = 0;
    pattern_->selected_ = 5;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, 5);
}

/**
 * @tc.name: UpdateStartAndEndIndexbySelectedTestNg002
 * @tc.desc: Test arc indexer pattern UpdateStartAndEndIndexbySelected function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, UpdateStartAndEndIndexbySelectedTestNg002, TestSize.Level1)
{
    Create(nullptr, std::vector<std::string>(), 0);
    pattern_->autoCollapse_ = true;

    /**
     * @tc.steps: step1. Test with selected_ >= startIndex_ && selected_ < endIndex_.
     * @tc.expected: focusIndex_ 2.
     */
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->fullCount_ = 30;
    pattern_->endIndex_ = 31;
    pattern_->startIndex_ = 1;
    pattern_->selected_ = 3;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, 2);
    EXPECT_EQ(pattern_->selected_, 2);
    EXPECT_EQ(pattern_->endIndex_, 29);

    /**
     * @tc.steps: step2. Test with selected_ >= endIndex_ - 1.
     * @tc.expected: focusIndex_ 3.
     */
    pattern_->selected_ = 30;
    pattern_->endIndex_ = 26;
    pattern_->startIndex_ = 5;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, 3);
    EXPECT_EQ(pattern_->selected_, 3);
    EXPECT_EQ(pattern_->startIndex_, 25);
    EXPECT_EQ(pattern_->endIndex_, 29);

    /**
     * @tc.steps: step3. Test with selected_ < startIndex_.
     * @tc.expected: focusIndex_ correct.
     */
    pattern_->selected_ = -1;
    pattern_->startIndex_ = 2;
    pattern_->endIndex_ = 10;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, 0);
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 4);
    pattern_->selected_ = 2;
    pattern_->startIndex_ = 5;
    pattern_->endIndex_ = 10;
    pattern_->UpdateStartAndEndIndexbySelected();
    EXPECT_EQ(pattern_->focusIndex_, 0);
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_EQ(pattern_->startIndex_, 2);
    EXPECT_EQ(pattern_->endIndex_, 6);
}

/**
 * @tc.name: ApplyFourPlusOneModeTestNg001
 * @tc.desc: Test arc indexer pattern ApplyFourPlusOneMode function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ApplyFourPlusOneModeTestNg001, TestSize.Level1)
{
    Create(nullptr, CREATE_ARRAY, 0);
    pattern_->autoCollapse_ = true;
    std::vector<std::string> arrayvalue;
    std::vector<std::string> expectValue = CREATE_ARRAY;


    /**
     * @tc.steps: step1. Test with CREATE_ARRAY.
     * @tc.expected: arcArrayValue_ correct.
     */
    expectValue.push_back(">");
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = 29;
    pattern_->ApplyFourPlusOneMode();
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);

    /**
     * @tc.steps: step2. Test with startIndex_ and endIndex_ changed.
     * @tc.expected: arcArrayValue_ correct.
     */
    arrayvalue.clear();
    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = 29;
    pattern_->selected_ = 30;
    pattern_->ApplyFourPlusOneMode();
    expectValue = { "W", "X", "Y", "Z", ">" };
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);

    /**
     * @tc.steps: step3. Test with startIndex_ and endIndex_ changed.
     * @tc.expected: arcArrayValue_ correct.
     */
    arrayvalue.clear();
    pattern_->startIndex_ = 1;
    pattern_->endIndex_ = 10;
    pattern_->selected_ = 0;
    pattern_->ApplyFourPlusOneMode();
    expectValue = { "AAAAAAAA", "BBBB", "C", "D", ">" };
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);

    /**
     * @tc.steps: step4. Test with startIndex_ and endIndex_ changed.
     * @tc.expected: arcArrayValue_ correct.
     */
    arrayvalue.clear();
    pattern_->startIndex_ = 6;
    pattern_->endIndex_ = 10;
    pattern_->selected_ = 15;
    pattern_->ApplyFourPlusOneMode();
    expectValue = { "MMMMMMMM", "N", "O", "P", ">" };
    for (auto item : pattern_->arcArrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, expectValue);
}

/**
 * @tc.name: UpdateStartAndEndIndexByTouchTestNg001
 * @tc.desc: Test arc indexer pattern UpdateStartAndEndIndexByTouch function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, UpdateStartAndEndIndexByTouchTestNg001, TestSize.Level1)
{
    Create(nullptr, std::vector<std::string>(), 0);

    /**
     * @tc.steps: step1. Test with autoCollapse_ false.
     * @tc.expected: focusIndex_ 5.
     */
    pattern_->autoCollapse_ = false;
    pattern_->selected_ = 5;
    pattern_->UpdateStartAndEndIndexByTouch();
    EXPECT_EQ(pattern_->focusIndex_, 5);

    /**
     * @tc.steps: step2. Test with autoCollapse_ true and currectCollapsingMode_ FOUR.
     * @tc.expected: focusIndex_ 6.
     */
    pattern_->autoCollapse_ = true;
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->selected_ = 6;
    pattern_->UpdateStartAndEndIndexByTouch();
    EXPECT_EQ(pattern_->focusIndex_, 6);

    /**
     * @tc.steps: step3. Test with currectCollapsingMode_ NONE and fullCount_ <= ARC_INDEXER_COLLAPSE_ITEM_COUNT.
     * @tc.expected: focusIndex_ 2.
     */
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    pattern_->fullCount_ = 3;
    pattern_->selected_ = 2;
    pattern_->UpdateStartAndEndIndexByTouch();
    EXPECT_EQ(pattern_->focusIndex_, 2);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);

    /**
     * @tc.steps: step4. Test with currectCollapsingMode_ NONE and fullCount_ > ARC_INDEXER_COLLAPSE_ITEM_COUNT.
     * @tc.expected: focusIndex_ 2.
     */
    pattern_->fullCount_ = 10;
    pattern_->selected_ = 8;
    pattern_->UpdateStartAndEndIndexByTouch();
    EXPECT_EQ(pattern_->focusIndex_, 2);
    EXPECT_EQ(pattern_->startIndex_, 6);
    EXPECT_EQ(pattern_->endIndex_, 10);

    /**
     * @tc.steps: step5. Test with currectCollapsingMode_ NONE and fullCount_ > ARC_INDEXER_COLLAPSE_ITEM_COUNT.
     * @tc.expected: focusIndex_ 0.
     */
    pattern_->fullCount_ = 35;
    pattern_->selected_ = 26;
    pattern_->UpdateStartAndEndIndexByTouch();
    EXPECT_EQ(pattern_->focusIndex_, 1);
    EXPECT_EQ(pattern_->startIndex_, 25);
    EXPECT_EQ(pattern_->endIndex_, 29);
}

/**
 * @tc.name: BuildFullArrayValueTestNg001
 * @tc.desc: Test arc indexer pattern BuildFullArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, BuildFullArrayValueTestNg001, TestSize.Level1)
{
    Create(nullptr, CREATE_ARRAY, 0);

    /**
     * @tc.steps: step1. Test with fullCount_ <= ARC_INDEXER_COLLAPSE_ITEM_COUNT.
     * @tc.expected: arcArrayValue_ correct.
     */
    pattern_->fullCount_ = CREATE_ARRAY.size();
    pattern_->autoCollapse_ = true;
    pattern_->BuildFullArrayValue();
    std::vector<std::string> expectValue = CREATE_ARRAY;
    std::vector<std::string> arrayValue;
    expectValue.push_back("<");
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    EXPECT_EQ(arrayValue, expectValue);

    /**
     * @tc.steps: step2. Test with fullCount_ > ARC_INDEXER_COLLAPSE_ITEM_COUNT and autoCollapse_ false.
     * @tc.expected: arcArrayValue_ correct.
     */
    pattern_->fullArrayValue_ = LONG_ARRAY;
    pattern_->fullCount_ = LONG_ARRAY.size();
    pattern_->autoCollapse_ = false;
    pattern_->BuildFullArrayValue();
    arrayValue.clear();
    expectValue = LONG_ARRAY;
    for (int32_t i = 0; i < LONG_ARRAY.size() - ARC_INDEXER_ITEM_MAX_COUNT - 1; ++i) {
        expectValue.pop_back();
    }
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    EXPECT_EQ(arrayValue, expectValue);

    /**
     * @tc.steps: step3. Test with fullCount_ > ARC_INDEXER_COLLAPSE_ITEM_COUNT and autoCollapse_ true.
     * @tc.expected: arcArrayValue_ correct.
     */
    pattern_->autoCollapse_ = true;
    pattern_->BuildFullArrayValue();
    arrayValue.clear();
    expectValue.pop_back();
    expectValue.push_back("<");
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    EXPECT_EQ(arrayValue, expectValue);
}

/**
 * @tc.name: ResetArrayValueTestNg001
 * @tc.desc: Test arc indexer pattern ResetArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ResetArrayValueTestNg001, TestSize.Level1)
{
    IndexerModelNG model = Create(nullptr, std::vector<std::string>(), 0);
    bool isModeChanged = true;
    std::vector<std::string> arrayValue;
    std::vector<std::string> expectValue;

    /**
     * @tc.steps: step1. Test with CREATE_ARRAY_2 and autoCollapse_ true.
     * @tc.expected: arcArrayValue_ correct.
     */
    model.SetArrayValue(AceType::RawPtr(frameNode_), CREATE_ARRAY_2);
    pattern_->fullArrayValue_ = CREATE_ARRAY_2;
    layoutProperty_->UpdateUsingPopup(true);
    pattern_->autoCollapse_ = true;
    pattern_->ResetArrayValue(isModeChanged);
    EXPECT_EQ(pattern_->fullCount_, CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->sharpItemCount_, 1);
    EXPECT_EQ(pattern_->itemCount_, 14);
    EXPECT_TRUE(pattern_->isPopup_);
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    expectValue = { "#", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "<" };
    EXPECT_EQ(arrayValue, expectValue);

    /**
     * @tc.steps: step2. Test with CREATE_ARRAY_2 and autoCollapse_ false.
     * @tc.expected: arcArrayValue_ correct.
     */
    pattern_->autoCollapse_ = false;
    pattern_->ResetArrayValue(isModeChanged);
    EXPECT_EQ(pattern_->fullCount_, CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->sharpItemCount_, 0);
    EXPECT_EQ(pattern_->itemCount_, CREATE_ARRAY_2.size());
    arrayValue.clear();
    expectValue = CREATE_ARRAY_2;
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    EXPECT_EQ(arrayValue, expectValue);
}

/**
 * @tc.name: ResetArrayValueTestNg002
 * @tc.desc: Test arc indexer pattern ResetArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, ResetArrayValueTestNg002, TestSize.Level1)
{
    Create(nullptr, std::vector<std::string>(), 0);
    bool isModeChanged = false;
    std::vector<std::string> arrayValue;
    std::vector<std::string> expectValue;

    /**
     * @tc.steps: step1. Test with voidArray.
     * @tc.expected: arcArrayValue_ empty.
     */
    pattern_->ResetArrayValue(isModeChanged);
    EXPECT_EQ(pattern_->fullCount_, 0);
    EXPECT_EQ(pattern_->sharpItemCount_, 0);
    EXPECT_EQ(pattern_->itemCount_, 0);
    EXPECT_EQ(pattern_->arcArrayValue_.size(), 0);

    /**
     * @tc.steps: step2. Test with CREATE_ARRAY and autoCollapse_ true.
     * @tc.expected: arcArrayValue_ correct.
     */
    isModeChanged = true;
    pattern_->autoCollapse_ = true;
    pattern_->fullArrayValue_ = CREATE_ARRAY;
    layoutProperty_->UpdateUsingPopup(true);
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->ResetArrayValue(isModeChanged);
    EXPECT_EQ(pattern_->fullCount_, CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->sharpItemCount_, 0);
    EXPECT_EQ(pattern_->itemCount_, 5);
    EXPECT_TRUE(pattern_->isPopup_);
    for (auto item : pattern_->arcArrayValue_) {
        arrayValue.push_back(item.first);
    }
    expectValue = { "AAAAAAAA", "BBBB", "C", "D", ">" };
    EXPECT_EQ(arrayValue, expectValue);
}

/**
 * @tc.name: GetPositionAngleTestNg001
 * @tc.desc: Test arc indexer pattern GetPositionAngle function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, GetPositionAngleTestNg001, TestSize.Level1)
{
    Create(nullptr, std::vector<std::string>(), 0);

    /**
     * @tc.steps: step1. Test with deltaY < 0.
     * @tc.expected: GetPositionAngle return correct.
     */
    pattern_->arcCenter_ = OffsetF(20.f, 20.f);
    float angle = pattern_->GetPositionAngle(Offset(25.f, 15.f));
    EXPECT_EQ(angle, 315.f);

    /**
     * @tc.steps: step2. Test with posAngle < startAngle_.
     * @tc.expected: angle correct.
     */
    pattern_->startAngle_ = 50.f;
    pattern_->arcCenter_ = OffsetF(10.f, 10.f);
    angle = pattern_->GetPositionAngle(Offset(100.f, 100.f));
    EXPECT_EQ(angle, 45.f);

    /**
     * @tc.steps: step3. Test with posAngle out of range.
     * @tc.expected: angle correct.
     */
    pattern_->arcCenter_ = OffsetF(5.f, 5.f);
    pattern_->stepAngle_ = 40.f;
    angle = pattern_->GetPositionAngle(Offset(100.f, 100.f));
    EXPECT_EQ(angle, 45.f);
}

/**
 * @tc.name: GetSelectChildIndexTestNg001
 * @tc.desc: Test arc indexer pattern GetSelectChildIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, GetSelectChildIndexTestNg001, TestSize.Level1)
{
    Create(nullptr, std::vector<std::string>(), 0);

    /**
     * @tc.steps: step1. Test with index < itemCount_.
     * @tc.expected: GetSelectChildIndex return correct.
     */
    pattern_->itemCount_ = 10;
    pattern_->stepAngle_ = 10;
    int32_t index = pattern_->GetSelectChildIndex(Offset(10.f, 10.f));
    EXPECT_EQ(index, 10);

    /**
     * @tc.steps: step2. Test with index > itemCount_.
     * @tc.expected: GetSelectChildIndex return correct.
     */

    pattern_->stepAngle_ = 5;
    index = pattern_->GetSelectChildIndex(Offset(10.f, 10.f));
    EXPECT_EQ(index, pattern_->itemCount_);

    /**
     * @tc.steps: step3. Test with arcCenter_ changed.
     * @tc.expected: GetSelectChildIndex return correct.
     */
    pattern_->arcCenter_ = OffsetF(5.f, 5.f);
    pattern_->stepAngle_ = 10;
    index = pattern_->GetSelectChildIndex(Offset(10.f, 10.f));
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: MoveIndexByOffsetTestNg001
 * @tc.desc: Test arc indexer pattern MoveIndexByOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, MoveIndexByOffsetTestNg001, TestSize.Level1)
{
    IndexerModelNG model = Create(nullptr, std::vector<std::string>(), 0);
    model.SetAutoCollapse(true);
    pattern_->stepAngle_ = 20;

    /**
     * @tc.steps: step1. Test with VoidArray.
     * @tc.expected: selected_ 0.
     */
    pattern_->arcCenter_ = OffsetF(20.f, 20.f);
    pattern_->MoveIndexByOffset(Offset(30.f, 50.f));
    EXPECT_EQ(pattern_->selected_, 0);

    /**
     * @tc.steps: step2. Test with LongArray and nextSelectIndex == itemCount_.
     * @tc.expected: selected_ not changed.
     */
    pattern_->fullArrayValue_ = CREATE_ARRAY;
    pattern_->autoCollapse_ = true;
    pattern_->fullCount_ = CREATE_ARRAY.size();
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->CollapseArrayValue();
    pattern_->itemCount_ = pattern_->arcArrayValue_.size();
    pattern_->selected_ = 5;
    pattern_->MoveIndexByOffset(Offset(15.f, 25.f));
    EXPECT_EQ(pattern_->selected_, 5);

    /**
     * @tc.steps: step3. Test with LongArray and nextSelectIndex < itemCount_.
     * @tc.expected: selected_ changed.
     */
    pattern_->selected_ = 5;
    pattern_->startAngle_ = 0;
    pattern_->MoveIndexByOffset(Offset(50.f, 50.f));
    EXPECT_EQ(pattern_->selected_, 2);
    EXPECT_EQ(pattern_->childPressIndex_, 2);
    EXPECT_EQ(pattern_->lastSelected_, 2);
}

/**
 * @tc.name: MoveIndexByOffsetTestNg002
 * @tc.desc: Test arc indexer pattern MoveIndexByOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, MoveIndexByOffsetTestNg002, TestSize.Level1)
{
    IndexerModelNG model = Create(nullptr, std::vector<std::string>(), 0);
    pattern_->stepAngle_ = 20;
    pattern_->arcCenter_ = OffsetF(20.f, 20.f);

    /**
     * @tc.steps: step1. Test with ArcIndexerBarState::COLLAPSED.
     * @tc.expected: selected_ not change.
     */
    pattern_->fullArrayValue_ = CREATE_ARRAY;
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->fullCount_ = CREATE_ARRAY.size();
    pattern_->CollapseArrayValue();
    pattern_->itemCount_ = pattern_->arcArrayValue_.size();
    pattern_->startAngle_ = 0;
    pattern_->childPressIndex_ = 0;
    pattern_->autoCollapse_ = true;
    pattern_->MoveIndexByOffset(Offset(25.f, 50.f));
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_EQ(pattern_->currectCollapsingMode_, ArcIndexerCollapsingMode::NONE);
    EXPECT_EQ(pattern_->lastSelected_, -1);
    EXPECT_EQ(pattern_->childPressIndex_, 0);
    EXPECT_EQ(pattern_->lastCollapsingMode_, ArcIndexerCollapsingMode::NONE);
    EXPECT_FALSE(pattern_->isNewHeightCalculated_);
    EXPECT_FALSE(pattern_->selectChanged_);

    /**
     * @tc.steps: step2. Test with ArcIndexerBarState::EXPANDED.
     * @tc.expected: selected_ not change.
     */
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->autoCollapse_ = true;
    pattern_->startAngle_ = 0;
    pattern_->stepAngle_ = 3;
    pattern_->MoveIndexByOffset(Offset(25.f, 41.f));
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_EQ(pattern_->currectCollapsingMode_, ArcIndexerCollapsingMode::FOUR);
    EXPECT_EQ(pattern_->lastSelected_, -1);
    EXPECT_EQ(pattern_->childPressIndex_, 0);
    EXPECT_EQ(pattern_->lastCollapsingMode_, ArcIndexerCollapsingMode::FOUR);
    EXPECT_FALSE(pattern_->isNewHeightCalculated_);
    EXPECT_FALSE(pattern_->selectChanged_);
}

/**
 * @tc.name: GetChildNodeContentTestNg001
 * @tc.desc: Test arc indexer pattern GetChildNodeContent function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, GetChildNodeContentTestNg001, TestSize.Level1)
{
    Create(nullptr, CREATE_ARRAY, 0);
    std::string content;

    /**
     * @tc.steps: step1. Test with index < 0.
     * @tc.expected: GetChildNodeContent return correct.
     */
    std::string childContent = pattern_->GetChildNodeContent(-1);
    content = "AAAAAAAA";
    EXPECT_EQ(childContent, content);

    /**
     * @tc.steps: step2. Test with index >= arcArrayValue_.
     * @tc.expected: GetChildNodeContent return correct.
     */
    childContent = pattern_->GetChildNodeContent(100);
    content = ">";
    EXPECT_EQ(childContent, content);

    /**
     * @tc.steps: step3. Test with index in arcArrayValue_ range.
     * @tc.expected: GetChildNodeContent return correct.
     */
    childContent = pattern_->GetChildNodeContent(2);
    content = "C";
    EXPECT_EQ(childContent, content);

    /**
     * @tc.steps: step4. Test with autoCollapse_ true.
     * @tc.expected: GetChildNodeContent return correct.
     */
    pattern_->autoCollapse_ = true;
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->CollapseArrayValue();
    childContent = pattern_->GetChildNodeContent(100);
    content = ">";
    EXPECT_EQ(childContent, content);
}

/**
 * @tc.name: GetActualIndexTestNg001
 * @tc.desc: Test arc indexer pattern GetActualIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcindexerPatternTestNg, GetActualIndexTestNg001, TestSize.Level1)
{
    Create(nullptr, CREATE_ARRAY, 0);

    /**
     * @tc.steps: step1. Test with autoCollapse_ false.
     * @tc.expected: GetActualIndex return correct.
     */
    pattern_->autoCollapse_ = false;
    int32_t index = pattern_->GetActualIndex(5);
    EXPECT_EQ(index, 5);

    /**
     * @tc.steps: step2. Test with autoCollapse_ true and currectCollapsingMode_ FOUR.
     * @tc.expected: GetActualIndex return correct.
     */
    pattern_->autoCollapse_ = true;
    pattern_->selected_ = 2;
    pattern_->currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    pattern_->CollapseArrayValue();
    index = pattern_->GetActualIndex(2);
    EXPECT_EQ(index, 2);
    pattern_->selected_ = 22;
    pattern_->startIndex_ = 5;
    pattern_->CollapseArrayValue();
    index = pattern_->GetActualIndex(22);
    EXPECT_EQ(index, 22);

    /**
     * @tc.steps: step3. Test with arcIndex == 0.
     * @tc.expected: GetActualIndex return correct.
     */
    pattern_->selected_ = 0;
    pattern_->startIndex_ = 5;
    index = pattern_->GetActualIndex(0);
    EXPECT_EQ(index, 5);
}
} // namespace OHOS::Ace::NG
