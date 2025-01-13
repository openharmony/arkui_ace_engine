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
#include "base/memory/referenced.h"
#include "core/common/container.h"
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
#include "base/memory/memory_monitor_def.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
std::vector<std::string> CREATE_ARRAY = { "AAAAAAAA", "BBBB", "C", "D", "E", "FFFFF", "G", "H", "I", "J", "K", "L",
    "MMMMMMMM", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
std::vector<std::string> CREATE_ARRAY_1 = { "A", "B", "C", "D", "E", "F", "G", "H", "I" };
std::vector<std::string> CREATE_ARRAY_2 = { "#", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
} // namespace

class ArcindexerPatternTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(const std::function<void(IndexerModelNG)>& callback = nullptr,
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
};

void ArcindexerPatternTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
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
}

void ArcindexerPatternTestNg::Create(
    const std::function<void(IndexerModelNG)>& callback, std::vector<std::string> arrayValue, int32_t selected)
{
    IndexerModelNG model;
    model.Create(arrayValue, selected, true);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
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
    int32_t index = 1;
    /**
     * @tc.steps: step1. isInputEventRegisted_ is true and call InitInputEvent.
    */
    auto renderContext = AceType::MakeRefPtr<RenderContext>();
    pattern_->UpdateIndexerNodeOpacityByIdx(renderContext, index);
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
    EXPECT_EQ(pattern_->selected_, 19);
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
    auto value = pattern_->lastSelected_ = 1;
    pattern_->OnSelect();
    EXPECT_TRUE(value != pattern_->animateSelected_);
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
} // namespace OHOS::Ace::NG
