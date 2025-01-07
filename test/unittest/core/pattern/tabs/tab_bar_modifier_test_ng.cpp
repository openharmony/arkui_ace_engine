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

#include "tabs_test_ng.h"
#include "test/mock/core/rosen/mock_canvas.h"

namespace OHOS::Ace::NG {
class TabBarModifierTestNg : public TabsTestNg {
public:
};

/**
 * @tc.name: TabBarModifierSetIndicator001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarModifierSetIndicator001, TestSize.Level1)
{
    OffsetF indicatorOffset = { 0.0f, 0.0f };
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorOffset(indicatorOffset);
    EXPECT_EQ(tabBarModifier->indicatorLeft_->Get(), 0.0f);
    EXPECT_EQ(tabBarModifier->indicatorTop_->Get(), 0.0f);
    tabBarModifier->indicatorLeft_ = nullptr;
    tabBarModifier->indicatorTop_ = nullptr;
    tabBarModifier->SetIndicatorOffset(indicatorOffset);
    EXPECT_EQ(tabBarModifier->indicatorLeft_, nullptr);
    EXPECT_EQ(tabBarModifier->indicatorTop_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorColor001
 * @tc.desc: test SetIndicatorColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarModifierSetIndicatorColor001, TestSize.Level1)
{
    LinearColor indicatorColor(Color::BLACK);
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorColor(indicatorColor);
    EXPECT_TRUE(tabBarModifier->indicatorColor_->Get() == indicatorColor);
    tabBarModifier->indicatorColor_ = nullptr;
    tabBarModifier->SetIndicatorColor(indicatorColor);
    EXPECT_EQ(tabBarModifier->indicatorColor_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorWidth001
 * @tc.desc: test SetIndicatorWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarModifierSetIndicatorWidth001, TestSize.Level1)
{
    float indicatorWidth = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorWidth_->Get(), indicatorWidth);
    tabBarModifier->indicatorWidth_ = nullptr;
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorWidth_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorHeight001
 * @tc.desc: test SetIndicatorHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarModifierSetIndicatorHeight001, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    float indicatorHeight = 1.0f;
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorHeight_->Get(), indicatorHeight);
    tabBarModifier->indicatorHeight_ = nullptr;
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorHeight_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorBorderRadius001
 * @tc.desc: test SetIndicatorBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarModifierSetIndicatorBorderRadius001, TestSize.Level1)
{
    float indicatorBorderRadius = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_->Get(), indicatorBorderRadius);
    tabBarModifier->indicatorBorderRadius_ = nullptr;
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorMarginTop001
 * @tc.desc: test SetIndicatorMarginTop
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarModifierSetIndicatorMarginTop001, TestSize.Level1)
{
    float indicatorMarginTop = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_->Get(), indicatorMarginTop);
    tabBarModifier->indicatorMarginTop_ = nullptr;
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetHasIndicator001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarModifierSetHasIndicator001, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    ASSERT_NE(tabBarModifier->hasIndicator_, nullptr);
    EXPECT_TRUE(tabBarModifier->hasIndicator_->Get());
    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->SetHasIndicator(true);
    EXPECT_EQ(tabBarModifier->hasIndicator_, nullptr);
}

/**
 * @tc.name: TabBarModifierOnDraw001
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarModifierOnDraw001, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());

    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    float indicatorHeight = 1.0f;
    float indicatorWidth = 1.0f;
    float indicatorMarginTop = 1.0f;
    float indicatorBorderRadius = 1.0f;

    tabBarModifier->SetHasIndicator(true);
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    tabBarModifier->onDraw(context);

    EXPECT_TRUE(tabBarModifier->hasIndicator_->Get());
    EXPECT_EQ(tabBarModifier->indicatorHeight_->Get(), indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorWidth_->Get(), indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_->Get(), indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_->Get(), indicatorBorderRadius);

    indicatorHeight = -1.0f;
    indicatorWidth = -1.0f;
    indicatorMarginTop = -1.0f;
    indicatorBorderRadius = -1.0f;

    tabBarModifier->SetHasIndicator(true);
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    tabBarModifier->onDraw(context);

    EXPECT_TRUE(tabBarModifier->hasIndicator_->Get());
    EXPECT_EQ(tabBarModifier->indicatorHeight_->Get(), indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorWidth_->Get(), indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_->Get(), indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_->Get(), indicatorBorderRadius);

    tabBarModifier->SetHasIndicator(false);
    tabBarModifier->onDraw(context);
    EXPECT_FALSE(tabBarModifier->hasIndicator_->Get());

    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->onDraw(context);
    EXPECT_EQ(tabBarModifier->hasIndicator_, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodGetForegroundDrawFunction001
 * @tc.desc: test GetForegroundDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarPaintMethodGetForegroundDrawFunction001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);

    auto paintMethod = tabBarPattern_->CreateNodePaintMethod();
    PaintWrapper paintWrapper(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);

    tabBarPaintProperty_->UpdateFadingEdge(false);
    EXPECT_FALSE(tabBarPaintProperty_->GetFadingEdgeValue());
    PaintWrapper paintWrapper2(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_EQ(drawFunction, nullptr);
    auto clone = tabBarPaintProperty_->Clone();
    EXPECT_NE(clone, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodGetContentModifier001
 * @tc.desc: test GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarPaintMethodGetContentModifier001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);
    auto paintMethod = tabBarPattern_->CreateNodePaintMethod();

    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->CreateNodePaintMethod();

    IndicatorStyle style;
    tabBarPattern_->SetIndicatorStyle(style, 1);
    tabBarPattern_->CreateNodePaintMethod();

    PaintWrapper paintWrapper(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    auto contentModifier = paintMethod->GetContentModifier(&paintWrapper);
    EXPECT_NE(contentModifier, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodUpdateContentModifier001
 * @tc.desc: test UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarPaintMethodUpdateContentModifier001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);

    auto paintMethod = tabBarPattern_->CreateNodePaintMethod();
    PaintWrapper paintWrapper(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    paintMethod->UpdateContentModifier(&paintWrapper);
    auto tabBarPaintMethod = Ace::AceType::DynamicCast<TabBarPaintMethod>(paintMethod);
    EXPECT_NE(tabBarPaintMethod->tabBarModifier_, nullptr);

    PaintWrapper paintWrapper2(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), nullptr);
    paintMethod->UpdateContentModifier(&paintWrapper2);
    EXPECT_NE(tabBarPaintMethod->tabBarModifier_, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodPaintGradient001
 * @tc.desc: test PaintGradient
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarPaintMethodPaintGradient001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);
    std::vector<bool> gradientRegions = { true, true, true, true, true };
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    auto paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(
        tabBarModifier, RectF(), gradientRegions, Color::BLACK, indicator, OffsetF(), true);

    PaintWrapper paintWrapper(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    drawFunction(rsCanvas);
    EXPECT_TRUE(paintMethod->gradientRegions_[0]);

    gradientRegions[0] = false;
    paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(
        tabBarModifier, RectF(), gradientRegions, Color::BLACK, indicator, OffsetF(), true);
    PaintWrapper paintWrapper2(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    drawFunction(rsCanvas);
    EXPECT_FALSE(paintMethod->gradientRegions_[0]);
}

/**
 * @tc.name: TabBarmodifieronDraw002
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarmodifieronDraw002, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());

    /**
     * @tc.steps: step2. Test function onDraw.
     * @tc.expected: Related function runs ok.
     */
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->onDraw(context);
}

/**
 * @tc.name: TabBarmodifierPaintIndicator001
 * @tc.desc: test PaintIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarmodifierPaintIndicator001, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());

    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    tabBarModifier->indicatorHeight_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});
    tabBarModifier->indicatorWidth_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});
    tabBarModifier->indicatorMarginTop_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});
    tabBarModifier->indicatorBorderRadius_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});

    /**
     * @tc.steps: step2. Test function PaintIndicator.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarModifier->PaintIndicator(context);
        tabBarModifier->indicatorHeight_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
        tabBarModifier->indicatorWidth_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
        tabBarModifier->indicatorMarginTop_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
        tabBarModifier->indicatorBorderRadius_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
    }
}

/**
 * @tc.name: TabBarPatternOnModifyDone001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarPatternOnModifyDone001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->OnModifyDone();
        tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);
    }
}

/**
 * @tc.name: TabBarPatternOnModifyDone002
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarPatternOnModifyDone002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->OnModifyDone();
    auto layoutProperty = tabBarLayoutProperty_;
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->OnModifyDone();
    tabBarNode_->eventHub_ = AceType::MakeRefPtr<EventHub>();
    tabBarNode_->eventHub_->focusHub_ = AceType::MakeRefPtr<FocusHub>(tabBarNode_->eventHub_);
    ASSERT_NE(tabBarNode_->eventHub_->focusHub_, nullptr);
    tabBarPattern_->OnModifyDone();
    tabBarPattern_->swiperController_->removeTabBarEventCallback_();
    tabBarPattern_->swiperController_->addTabBarEventCallback_();
    EXPECT_NE(tabBarPattern_->swiperController_, nullptr);
}

/**
 * @tc.name: TabBarModifierHasIndicator002
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarModifierHasIndicator002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Select mode as BOARD
     */
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    ASSERT_NE(tabBarModifier->hasIndicator_, nullptr);
    tabBarModifier->SetHasIndicator(false);
    EXPECT_FALSE(tabBarModifier->hasIndicator_->Get());

    /**
     * @tc.steps: steps2.Calling the SetSelectedMode interface to pass in SelectedMode:: BOARD
     * @tc.expected: steps2. TabBarModifier -> has Indicator_ nullptr
     */
    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->SetHasIndicator(false);
    EXPECT_EQ(tabBarModifier->hasIndicator_, nullptr);
}

/**
 * @tc.name: TabBarPatternCreateNodePaintMethod001
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarPatternCreateNodePaintMethod001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);

    /**
     * @tc.steps: steps2. CreateNodePaintMethod
     * @tc.expected: steps2. Check the result of CreateNodePaintMethod
     */
    auto tabBarRenderContext = tabBarNode_->GetRenderContext();
    tabBarRenderContext->UpdateBackgroundColor(Color::RED);
    auto paintMethod = tabBarPattern_->CreateNodePaintMethod();
    EXPECT_EQ(tabBarRenderContext->GetBackgroundColor().value(), Color::RED);
}

/**
 * @tc.name: TabBarPaintMethodGetForegroundDrawFunction002
 * @tc.desc: Test the GetForegroundDrawFunction function in the TabBarPaintMethod class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarPaintMethodGetForegroundDrawFunction002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);
    auto paintMethod = tabBarPattern_->CreateNodePaintMethod();
    auto paintMethod2 = tabBarPattern_->CreateNodePaintMethod();
    auto geometryNode = tabBarNode_->GetGeometryNode();

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    MarginPropertyF padding;
    padding.left = 20.0f;
    padding.right = 20.0f;
    padding.top = 20.0f;
    padding.bottom = 20.0f;
    geometryNode->UpdatePaddingWithBorder(padding);
    PaintWrapper paintWrapper(tabBarNode_->GetRenderContext(), geometryNode, tabBarPaintProperty_);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    tabBarPaintProperty_->UpdateFadingEdge(false);

    /**
     * @tc.steps: steps3. GetForegroundDrawFunction.
     * @tc.expected: steps3. expect The function is run ok.
     */
    EXPECT_FALSE(tabBarPaintProperty_->GetFadingEdgeValue());
    PaintWrapper paintWrapper2(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_EQ(drawFunction, nullptr);
    auto clone = tabBarPaintProperty_->Clone();
    EXPECT_NE(clone, nullptr);
}

/**
 * @tc.name: TabBarPatternGetInnerFocusPaintRect001
 * @tc.desc: test GetInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarModifierTestNg, TabBarPatternGetInnerFocusPaintRect001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Test function InitOnKeyEvent.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    tabBarPattern_->isFirstFocus_ = true;
    auto event = KeyEvent();
    auto paintRect = RoundRect();
    tabBarPattern_->GetInnerFocusPaintRect(paintRect);
    EXPECT_TRUE(tabBarPattern_->isFirstFocus_);
}
} // namespace OHOS::Ace::NG
