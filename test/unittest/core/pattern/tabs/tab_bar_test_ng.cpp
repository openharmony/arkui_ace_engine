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

namespace OHOS::Ace::NG {

namespace {} // namespace

class TabBarTestNg : public TabsTestNg {
public:
};

/**
 * @tc.name: TabBarPatternUpdateSubTabBoard001
 * @tc.desc: test UpdateSubTabBoard
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateSubTabBoard001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(swiperNode_->GetTag(), V2::SWIPER_ETS_TAG);
    tabBarPattern_->UpdateSubTabBoard();

    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    IndicatorStyle style;
    tabBarPattern_->SetIndicatorStyle(style, 1);
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->tabBarStyles_[0] = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->selectedModes_[0] = SelectedMode::BOARD;
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternUpdateGradientRegions001
 * @tc.desc: test UpdateGradientRegions
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateGradientRegions001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetTabBarMode(TabBarMode::SCROLLABLE);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::VERTICAL);

    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern_->gradientRegions_[2]);

    tabBarPattern_->tabItemOffsets_ = { { 1.0f, 1.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[2]);

    tabBarPattern_->tabItemOffsets_ = { { 10.0f, 10.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[3]);

    tabBarPattern_->tabItemOffsets_ = { { -10.0f, -10.0f } };
    tabBarPattern_->childrenMainSize_ = 5.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[3]);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::HORIZONTAL);

    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern_->gradientRegions_[0]);

    tabBarPattern_->tabItemOffsets_ = { { 1.0f, 1.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[0]);

    tabBarPattern_->tabItemOffsets_ = { { 10.0f, 10.0f } };
    tabBarPattern_->childrenMainSize_ = 10.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[1]);

    tabBarPattern_->tabItemOffsets_ = { { -10.0f, -10.0f } };
    tabBarPattern_->childrenMainSize_ = 5.0f;
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[1]);
}

/**
 * @tc.name: TabBarPatternSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetSelectedMode001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });
    EXPECT_EQ(tabBarPattern_->GetSelectedMode(), SelectedMode::INDICATOR);

    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern_->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);

    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    tabBarPattern_->SetIndicatorStyle(indicator, 1);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator);
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternUpdateIndicator001
 * @tc.desc: test UpdateIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateIndicator001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::NOSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::NOSTYLE);
    tabBarPattern_->UpdateIndicator(0);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern_->tabBarType_[0] = true;
    tabBarPattern_->UpdateIndicator(0);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::HORIZONTAL);
    tabBarPattern_->tabBarType_[0] = false;
    tabBarPattern_->UpdateIndicator(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->UpdateIndicator(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation001
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayPressAnimation001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });

    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    IndicatorStyle indicatorStyle;
    tabBarPattern_->SetIndicatorStyle(indicatorStyle, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);

    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternGetIndicatorRect001
 * @tc.desc: test GetIndicatorRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternGetIndicatorRect001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto rect = tabBarLayoutProperty_->GetIndicatorRect(0);
    EXPECT_EQ(rect.GetX(), 85.f);
}

/**
 * @tc.name: TabBarPatternGetSelectedMode001
 * @tc.desc: test GetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternGetSelectedMode001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->indicator_ = 1;
    auto mode = tabBarPattern_->GetSelectedMode();
    EXPECT_EQ(mode, SelectedMode::INDICATOR);
}

/**
 * @tc.name: TabBarModifierSetIndicator001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarModifierSetIndicator001, TestSize.Level1)
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
HWTEST_F(TabBarTestNg, TabBarModifierSetIndicatorColor001, TestSize.Level1)
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
HWTEST_F(TabBarTestNg, TabBarModifierSetIndicatorWidth001, TestSize.Level1)
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
HWTEST_F(TabBarTestNg, TabBarModifierSetIndicatorHeight001, TestSize.Level1)
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
HWTEST_F(TabBarTestNg, TabBarModifierSetIndicatorBorderRadius001, TestSize.Level1)
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
HWTEST_F(TabBarTestNg, TabBarModifierSetIndicatorMarginTop001, TestSize.Level1)
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
HWTEST_F(TabBarTestNg, TabBarModifierSetHasIndicator001, TestSize.Level1)
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
HWTEST_F(TabBarTestNg, TabBarModifierOnDraw001, TestSize.Level1)
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
HWTEST_F(TabBarTestNg, TabBarPaintMethodGetForegroundDrawFunction001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
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
HWTEST_F(TabBarTestNg, TabBarPaintMethodGetContentModifier001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
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
HWTEST_F(TabBarTestNg, TabBarPaintMethodUpdateContentModifier001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
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
HWTEST_F(TabBarTestNg, TabBarPaintMethodPaintGradient001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    tabBarPattern_->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], selectedMode);
    std::vector<bool> gradientRegions = { true, true, true, true, true };
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    auto paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(
        tabBarModifier, gradientRegions, Color::BLACK, indicator, OffsetF(), true);

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
        tabBarModifier, gradientRegions, Color::BLACK, indicator, OffsetF(), true);
    PaintWrapper paintWrapper2(tabBarNode_->GetRenderContext(), tabBarNode_->GetGeometryNode(), tabBarPaintProperty_);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    drawFunction(rsCanvas);
    EXPECT_FALSE(paintMethod->gradientRegions_[0]);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish001
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternMaskAnimationFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call MaskAnimationFinish function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 0, true);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 1, false);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish002
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternMaskAnimationFinish002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call MaskAnimationFinish function.
     * @tc.expected: step2. expect The function is run ok.
     */
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 0, false);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 1, true);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternChangeMask001
 * @tc.desc: test ChangeMask
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternChangeMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call ChangeMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    auto tabBarGeometryNode = tabBarNode_->GetGeometryNode();
    auto tabBarOffset = tabBarGeometryNode->GetMarginFrameOffset();

    auto maskNode1 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT));
    auto imageNode1 = AceType::DynamicCast<FrameNode>(maskNode1->GetChildren().front());

    auto maskNode2 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT + 1));
    auto imageNode2 = AceType::DynamicCast<FrameNode>(maskNode2->GetChildren().front());

    tabBarPattern_->ChangeMask(TEST_TAB_BAR_INDEX, 1.0f, tabBarOffset, 1.0f, TEST_MASK_MIDDLE_RADIUS_RATIO, true);
    tabBarPattern_->ChangeMask(TEST_TAB_BAR_INDEX, 1.0f, tabBarOffset, 0.99f, TEST_MASK_MIDDLE_RADIUS_RATIO, false);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
    auto selectedImageNode = AceType::DynamicCast<FrameNode>(selectedMaskNode->GetChildren().front());
    auto selectedImageRenderContext = selectedImageNode->GetRenderContext();
    EXPECT_DOUBLE_EQ(selectedImageRenderContext->GetOpacity().value(), 1.0f);
    auto unselectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(unselectedmaskPosition));
    auto unSelectedImageNode = AceType::DynamicCast<FrameNode>(unselectedMaskNode->GetChildren().front());
    auto unSelectedImageRenderContext = unSelectedImageNode->GetRenderContext();
    EXPECT_DOUBLE_EQ(unSelectedImageRenderContext->GetOpacity().value(), 0.99f);
}

/**
 * @tc.name: TabBarPatternUpdateImageColor001
 * @tc.desc: test UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateImageColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call UpdateImageColor function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->UpdateImageColor(0);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->UpdateImageColor(1);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    tabBarPattern_->SetMaskAnimationByCreate(false);
    EXPECT_EQ(tabBarPattern_->IsMaskAnimationByCreate(), false);
}

/**
 * @tc.name: TabsModelSetTabBarWidth001
 * @tc.desc: test SetTabBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabsModelSetTabBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function SetTabBarWidth and SetTabBarHeight When tabBarWidth and tabBarHeight change.
     * @tc.expected: Related functions run ok.
     */
    CreateWithItem([](TabsModelNG model) {
        Dimension tabBarWidth = 10.0_vp;
        Dimension tabBarHeight = 3.0_vp;
        for (int i = 0; i <= 1; i++) {
            model.SetTabBarWidth(tabBarWidth);
            model.SetTabBarHeight(tabBarHeight);
            tabBarWidth = -1.0_vp;
            tabBarHeight = -1.0_vp;
        }
    });
}

/**
 * @tc.name: TabBarPatternInitClick001
 * @tc.desc: test InitClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitClick001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->clickEvent_ = nullptr;

    /**
     * @tc.steps: step2. Test function InitClick.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->InitClick(gestureHub);
        tabBarPattern_->clickEvent_ = AceType::MakeRefPtr<ClickEvent>([](GestureEvent&) {});
    }
}

/**
 * @tc.name: TabBarPatternInitScrollable001
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitScrollable001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->InitScrollable(gestureHub);
            tabBarPattern_->axis_ = Axis::VERTICAL;
        }
        tabBarPattern_->scrollableEvent_ = nullptr;
    }
}

/**
 * @tc.name: TabBarPatternInitTouche001
 * @tc.desc: test InitTouch, InitHoverEvent and InitMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitTouche001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>([](TouchEventInfo&) {});
    tabBarPattern_->hoverEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo&) {});
    tabBarPattern_->mouseEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo&) {});

    /**
     * @tc.steps: step2. Test function InitTouch, InitHoverEvent and InitMouseEvent.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->InitTouch(gestureHub);
    tabBarPattern_->InitHoverEvent();
    tabBarPattern_->InitMouseEvent();
}

/**
 * @tc.name: TabBarmodifieronDraw002
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarmodifieronDraw002, TestSize.Level1)
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
 * @tc.name: TabBarPatternGetBottomTabBarImageSizeAndOffset001
 * @tc.desc: test GetBottomTabBarImageSizeAndOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternGetBottomTabBarImageSizeAndOffset001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    std::vector<int32_t> selectedIndexes(1, 1);
    float selectedImageSize = 1.0f;
    float unselectedImageSize = 1.1f;
    OffsetF originalSelectedMaskOffset(1.0f, 1.1f);
    OffsetF originalUnselectedMaskOffset(0.0f, 1.0f);

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    int32_t maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
                unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
            maskIndex = 1;
        }
        tabBarNode_->Clean(false, false);
    }
}

/**
 * @tc.name: TabBarmodifierPaintIndicator001
 * @tc.desc: test PaintIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarmodifierPaintIndicator001, TestSize.Level1)
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
 * @tc.name: TabBarPatternFocusIndexChange001
 * @tc.desc: test FocusIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternFocusIndexChange001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    int32_t index = 1;
    std::optional<int32_t> animation_test = 1;

    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->FocusIndexChange(index);
        tabBarPattern_->animationDuration_ = animation_test;
    }
}

/**
 * @tc.name: TabBarPatternOnModifyDone001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternOnModifyDone001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
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
 * @tc.name: TabBarPatternMaskAnimationFinish003
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternMaskAnimationFinish003, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function MaskAnimationFinish.
     * @tc.expected: Related functions run ok.
     */
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    int32_t selectedIndex = -1;
    bool isSelected = true;
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, selectedIndex, isSelected);
}

/**
 * @tc.name: TabBarDistributedTest001
 * @tc.desc: Test the distributed capability of TabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarDistributedTest001, TestSize.Level1)
{
    TabsItemDivider divider;
    CreateWithItem([divider](TabsModelNG model) {
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: step2. Set Indicator.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    tabBarPattern_->UpdateIndicator(0);
    std::string ret = tabBarPattern_->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":0})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":0})";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    restoreInfo_ = R"({"Index":1})";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 1);
    restoreInfo_ = "invalid_json_string";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 1);
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation002
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayPressAnimation002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    int32_t index = 1;
    auto pressColor = Color();
    pressColor.SetValue(1);
    auto animationType = AnimationType::HOVERTOPRESS;
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern_->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function PlayPressAnimation.
     * @tc.expected: Related functions run ok.
     */
    for (int32_t i = 0; i <= 1; i++) {
        tabBarPattern_->PlayPressAnimation(index, pressColor, animationType);
        animationType = AnimationType::HOVER;
    }
}

/**
 * @tc.name: TabBarPatternStopTabBarTranslateAnimation001
 * @tc.desc: test StopTabBarTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternStopTabBarTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function StopTabBarTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->StopTabBarTranslateAnimation();
    }
    EXPECT_FALSE(tabBarPattern_->tabBarTranslateAnimation_);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect001
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetEdgeEffect001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight001
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateTextColorAndFontWeight001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));
    ASSERT_TRUE(pr.second);
    /**
     * @tc.steps: step2. Test function UpdateTextColorAndFontWeight and UpdateImageColor.
     * @tc.expected: Related functions run ok.
     */
    int32_t index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);

    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight002
 * @tc.desc: test UpdateTextColorAndFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateTextColorAndFontWeight002, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    for (int i = 0; i <= 1; i++) {
        AceType::DynamicCast<FrameNode>(
            AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(i))->GetChildren().back())
            ->layoutProperty_ = AceType::MakeRefPtr<TextLayoutProperty>();
        ASSERT_NE(AceType::DynamicCast<FrameNode>(
                      AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(i))->GetChildren().back())
                      ->layoutProperty_,
            nullptr);
    }

    /**
     * @tc.steps: step2. Test function UpdateTextColorAndFontWeight.
     * @tc.expected: Related function runs ok.
     */
    int32_t index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
}

/**
 * @tc.name: TabBarPatternInitClick002
 * @tc.desc: test InitClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitClick002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->clickEvent_ = nullptr;

    /**
     * @tc.steps: step2. Test function InitClick.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->InitClick(gestureHub);
    auto info = GestureEvent();
    tabBarPattern_->clickEvent_->callback_(info);
}

/**
 * @tc.name: TabBarPatternInitScrollable002
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitScrollable002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->SetAxis(Axis::HORIZONTAL);
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollableEvent->SetAxis(Axis::VERTICAL);
    scrollableEvent->SetScrollable(scrollable);
    tabBarPattern_->scrollableEvent_ = scrollableEvent;

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->InitScrollable(gestureHub);
        tabBarPattern_->swiperController_->tabBarFinishCallback_();
        scrollableEvent->SetScrollable(nullptr);
        tabBarPattern_->scrollableEvent_ = scrollableEvent;
    }
}

/**
 * @tc.name: TabBarPatternInitScrollable003
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitScrollable003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->InitScrollable(gestureHub);
                ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
                auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
                scrollable->callback_(0.1, SCROLL_FROM_NONE);
                tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarPattern_->axis_ = Axis::HORIZONTAL;
            }
            tabBarPattern_->axis_ = Axis::VERTICAL;
            tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
            tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f } };
    }
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_START);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    int32_t source = SCROLL_FROM_UPDATE;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->InitScrollable(gestureHub);
        scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
        scrollable->callback_(0.1, source);
        tabBarPattern_->axis_ = Axis::VERTICAL;
        tabBarPattern_->tabItemOffsets_.clear();
        tabBarPattern_->tabItemOffsets_ = { { 1.0f, -1.0f } };
        tabBarNode_->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 2.0f));
    }
}

/**
 * @tc.name: TabBarPatternPlayMaskAnimation001
 * @tc.desc: test PlayMaskAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayMaskAnimation001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Test function PlayMaskAnimation.
     * @tc.expected: Related function runs ok.
     */
    float selectedImageSize = 0.1f;
    OffsetF originalSelectedMaskOffset(0.1f, 0.2f);
    int32_t selectedIndex = 1;
    float unselectedImageSize = 0.2f;
    OffsetF originalUnselectedMaskOffset(0.1f, 0.2f);
    int32_t unselectedIndex = 1;

    auto maskNode1 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT));
    auto imageNode1 = AceType::DynamicCast<FrameNode>(maskNode1->GetChildren().front());

    auto maskNode2 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT + 1));
    auto imageNode2 = AceType::DynamicCast<FrameNode>(maskNode2->GetChildren().front());

    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternPlayTranslateAnimation001
 * @tc.desc: test PlayTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function PlayTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    CreateWithItem([](TabsModelNG model) {});
    float startPos = 0.1f;
    float endPos = 0.2f;
    float targetCurrentOffset = 0.3f;
    auto offset = 0.1f;
    tabBarPattern_->currentOffset_ = offset;
    tabBarPattern_->PlayTranslateAnimation(startPos, endPos, targetCurrentOffset);
    EXPECT_FALSE(tabBarPattern_->indicatorAnimationIsRunning_);
    EXPECT_FALSE(tabBarPattern_->translateAnimationIsRunning_);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect002
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetEdgeEffect002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: TabBarPatternPlayTabBarTranslateAnimation001
 * @tc.desc: test PlayTabBarTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayTabBarTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    int32_t targetIndex = 1;
    tabBarPattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();
    tabBarNode_->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    tabBarPattern_->childrenMainSize_ = 0.1f;
    AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(targetIndex))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(targetIndex - 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(targetIndex + 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));

    /**
     * @tc.steps: step2. Test function PlayTabBarTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */

    tabBarPattern_->PlayTabBarTranslateAnimation(targetIndex);
    EXPECT_FALSE(tabBarPattern_->tabBarTranslateAnimationIsRunning_);
}

/**
 * @tc.name: TabBarPatternAdjustFocusPosition001
 * @tc.desc: test AdjustFocusPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternAdjustFocusPosition001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    tabBarPattern_->AdjustFocusPosition();
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->tabItemOffsets_.clear();
    OffsetF c1(-1.0f, -1.0f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternAdjustFocusPosition002
 * @tc.desc: test AdjustFocusPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternAdjustFocusPosition002, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->tabItemOffsets_.clear();
    OffsetF c1(1.0f, 1.0f);
    OffsetF c2(100.0f, 100.0f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternCreateNodePaintMethod001
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternCreateNodePaintMethod001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
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
 * @tc.name: TabsModelSetOnTabBarClick001
 * @tc.desc: Tabs SetOnTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabsModelSetOnTabBarClick001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetOnTabBarClick
     * @tc.expected: steps2. Check the result of SetOnTabBarClick
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetOnTabBarClick([](const BaseEventInfo* info) {});
        model.SetOnTabBarClick([](const BaseEventInfo* info) {});
    });
    EXPECT_NE(pattern_->onTabBarClickEvent_, nullptr);
    EXPECT_NE(pattern_->onTabBarClickEvent_, nullptr);
}

/**
 * @tc.name: TabBarPatternInitScrollable004
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitScrollable004, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->InitScrollable(gestureHub);
                ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
                auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
                scrollable->callback_(0.1, SCROLL_FROM_NONE);
                tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarPattern_->axis_ = Axis::HORIZONTAL;
            }
            tabBarPattern_->axis_ = Axis::VERTICAL;
            tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
            tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f } };
    }
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->currentOffset_ = DEFAULT_OFFSET;
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_AXIS);
    scrollable->callback_(1.1, SCROLL_FROM_AXIS);
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::BOTTOMTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternGetIndicatorStyle001
 * @tc.desc: test GetIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternGetIndicatorStyle001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

    /**
     * @tc.steps: steps2. GetIndicatorStyle
     * @tc.expected: steps2. Check the result of GetIndicatorStyle
     */
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern_->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->swiperStartIndex_ = 0;
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    IndicatorStyle indicator1;
    indicator1.width = -1.0_vp;
    tabBarPattern_->SetIndicatorStyle(indicator1, 1);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator1);
    auto firstRect = tabBarLayoutProperty_->GetIndicatorRect(0);
    EXPECT_EQ(firstRect.GetY(), 33.f);
    auto secondRect = tabBarLayoutProperty_->GetIndicatorRect(1);
    EXPECT_EQ(secondRect.GetY(), 33.f);

    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->turnPageRate_ = -0.9f;
    IndicatorStyle indicator2;
    OffsetF indicatorOffset;
    tabBarPattern_->GetIndicatorStyle(indicator2, indicatorOffset);
    EXPECT_EQ(indicatorOffset.GetY(), 33.f);
    indicator1.width = 1.0_vp;
    tabBarPattern_->SetIndicatorStyle(indicator1, 1);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator1);
    tabBarPattern_->GetIndicatorStyle(indicator2, indicatorOffset);
    tabBarPattern_->turnPageRate_ = 0.9f;
    IndicatorStyle indicator3;
    tabBarPattern_->GetIndicatorStyle(indicator3, indicatorOffset);
    tabBarPattern_->SetIndicatorStyle(indicator3, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator3);
}

/**
 * @tc.name: TabBarPatternCheckSwiperDisable001
 * @tc.desc: test CheckSwiperDisable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternCheckSwiperDisable001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

    /**
     * @tc.steps: steps2. CheckSwiperDisable
     * @tc.expected: steps2. Check the result of CheckSwiperDisable
     */
    EXPECT_EQ(tabBarPattern_->CheckSwiperDisable(), false);
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator001
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternApplyTurnPageRateToIndicator001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

    /**
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern_->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->ApplyTurnPageRateToIndicator(2.0f);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-2.0f);
    EXPECT_EQ(tabBarPattern_->turnPageRate_, 0.0f);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.9f);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.9f);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.9f);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPaintMethodGetForegroundDrawFunction002
 * @tc.desc: Test the GetForegroundDrawFunction function in the TabBarPaintMethod class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPaintMethodGetForegroundDrawFunction002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
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
 * @tc.name: TabBarPatternAdjustFocusPosition003
 * @tc.desc: Test the AdjustFocusPosition function in the TabBarPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternAdjustFocusPosition003, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->tabItemOffsets_.clear();
    OffsetF c1(0.0f, 0.0f);
    OffsetF c2(10.0f, 10.0f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto geometryNode = tabBarNode_->GetGeometryNode();

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    MarginPropertyF padding;
    padding.left = 10000.0f;
    padding.right = 10000.0f;
    padding.top = 10000.0f;
    padding.bottom = 10000.0f;
    geometryNode->UpdatePaddingWithBorder(padding);

    /**
     * @tc.steps: steps3. AdjustFocusPosition.
     * @tc.expected: steps3. Check the value of TabBarStyle under the AdjustFocusPosition function.
     */
    tabBarPattern_->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern_->currentOffset_, padding.left);
}

/**
 * @tc.name: TabBarOnAttachToMainTree001.
 * @tc.desc: Test the OnAttachToMainTree function in the TabContentNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarOnAttachToMainTree001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            LabelStyle labelStyle;
            tabContentModel.SetLabelStyle(labelStyle);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
     * @tc.steps: step2. Invoke OnAttachToMainTree.
     */
    tabContentFrameNode->OnAttachToMainTree(true);
    EXPECT_FALSE(tabContentFrameNode->useOffscreenProcess_);
}

/**
 * @tc.name: TabBarPatternGetInnerFocusPaintRect001
 * @tc.desc: test GetInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternGetInnerFocusPaintRect001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

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

/**
 * @tc.name: TabBarPatternInitScrollable005
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitScrollable005, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable in different conditons.
     * @tc.expected: Related function is called.
     */

    tabBarPattern_->InitScrollable(gestureHub);
    ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    tabBarPattern_->scrollableEvent_->scrollable_ = nullptr;
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    EXPECT_EQ(tabBarPattern_->scrollableEvent_->scrollable_, nullptr);
}

/*
 * @tc.name: TabBarPatternCalculateSelectedIndex001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternCalculateSelectedIndex001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    auto info = MouseInfo();
    Offset s1(0.1, 0.1);
    Offset s2(0.4, 0.4);
    OffsetF c0(0.0f, 0.0f);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    OffsetF c4(0.4f, 0.4f);
    info.SetLocalLocation(s1);
    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */

    tabBarPattern_->hoverIndex_.emplace(1);
    tabBarPattern_->tabItemOffsets_ = { c1, c2, c3, c4 };
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->isRTL_ = true;
    tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation());
    EXPECT_TRUE(tabBarPattern_->isRTL_);
    tabBarPattern_->tabItemOffsets_ = { c0, c2, c3, c4 };
    tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation());
    EXPECT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), -1);
}

/**
 * @tc.name: TabBarPatternGetIndicatorStyle002
 * @tc.desc: test GetIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternGetIndicatorStyle002, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

    /**
     * @tc.steps: steps2. GetIndicatorStyle
     * @tc.expected: steps2. Check the result of GetIndicatorStyle
     */
    tabBarPattern_->indicatorStyles_.clear();
    IndicatorStyle indicator;
    IndicatorStyle indicator2;
    tabBarPattern_->indicator_ = -1;
    OffsetF indicatorOffset;
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    EXPECT_EQ(tabBarPattern_->indicator_, -1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    tabBarPattern_->indicatorStyles_.push_back(indicator2);
    tabBarPattern_->indicatorStyles_.push_back(indicator);
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    indicator.width.SetValue(1.0);
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    EXPECT_EQ(indicator.width.Value(), 10);
    tabBarPattern_->isTouchingSwiper_ = false;
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    tabBarPattern_->axis_ = Axis::FREE;
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    EXPECT_EQ(tabBarPattern_->axis_, Axis::FREE);
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    EXPECT_TRUE(tabBarPattern_->isTouchingSwiper_);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    EXPECT_EQ(tabBarPattern_->axis_, Axis::HORIZONTAL);
    tabBarPattern_->turnPageRate_ = 2.0f;
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    EXPECT_EQ(tabBarPattern_->turnPageRate_, 1.0f);
    tabBarPattern_->swiperStartIndex_ = 1;
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, 1);
    tabBarPattern_->swiperStartIndex_ = 1;
    auto tabBarStyles1 = TabBarStyle::NOSTYLE;
    auto tabBarStyles2 = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->tabBarStyles_ = { tabBarStyles1, tabBarStyles2 };
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, 1);
    tabBarPattern_->swiperStartIndex_ = -1;
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    EXPECT_EQ(indicatorOffset.GetY(), 0.f);
}

/**
 * @tc.name: TabBarPatternOnModifyDone002
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternOnModifyDone002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
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
 * @tc.name: TabBarPatternIsAtBottom001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternIsAtBottom001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function IsAtBottom001.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->tabItemOffsets_.clear();
    tabBarPattern_->IsAtBottom();
    EXPECT_FALSE(tabBarPattern_->IsAtBottom());
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator002
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternApplyTurnPageRateToIndicator002, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

    /**
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern_->swiperStartIndex_ = 0;
    auto tabBarStyles1 = TabBarStyle::NOSTYLE;
    auto tabBarStyles2 = TabBarStyle::SUBTABBATSTYLE;
    auto selectedMode1 = SelectedMode::INDICATOR;
    auto selectedMode2 = SelectedMode::BOARD;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles2);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode2);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = 1;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = 2;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = -1;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator003
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternApplyTurnPageRateToIndicator003, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

    /**
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern_->swiperStartIndex_ = 0;
    auto tabBarStyles1 = TabBarStyle::SUBTABBATSTYLE;
    auto tabBarStyles2 = TabBarStyle::NOSTYLE;
    auto selectedMode1 = SelectedMode::INDICATOR;
    auto selectedMode2 = SelectedMode::BOARD;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles1);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles2);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->selectedModes_.push_back(selectedMode2);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, 0);

    /**
     * @tc.steps: steps3. ApplyTurnPageRateToIndicator
     * @tc.expected: steps3. Check the result of ApplyTurnPageRateToIndicator
     */

    tabBarPattern_->swiperStartIndex_ = 0;
    auto tabBarStyles3 = TabBarStyle::SUBTABBATSTYLE;
    auto selectedMode3 = SelectedMode::INDICATOR;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles3);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode3);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.5f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.7f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->turnPageRate_ = 0.5f;
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.7f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->turnPageRate_ = 0.5f;
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.5f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
}

/**
 * @tc.name: TabBarPatternUpdateIndicator002
 * @tc.desc: test UpdateIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateIndicator002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });
    EXPECT_TRUE(tabBarPaintProperty_->GetFadingEdgeValue());

    /**
     * @tc.steps: steps2. UpdateIndicator
     * @tc.expected: steps2. Check the result of UpdateIndicator
     */
    tabBarPattern_->indicator_ = 0;
    auto tabBarStyle1 = TabBarStyle::NOSTYLE;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyle1);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->isTouchingSwiper_ = false;
    tabBarPattern_->UpdateIndicator(0);
}

/**
 * @tc.name: TabBarPatternOnRestoreInfo001
 * @tc.desc: Test the TabBarPatternOnRestoreInfo
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternOnRestoreInfo001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Set Indicator.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    tabBarPattern_->UpdateIndicator(0);
    std::string ret = tabBarPattern_->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":0})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":0})";
    auto info = JsonUtil::ParseJsonString(restoreInfo_);
    auto jsonIsOn = info->GetValue("Index");
    tabBarPattern_->SetTabBarStyle(TabBarStyle::NOSTYLE, 0);
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    tabBarPattern_->SetAnimationDuration(1);
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    tabBarPattern_->swiperController_ = nullptr;
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    columnNode1->MountToParent(tabBarNode_);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    columnNode2->MountToParent(tabBarNode_);
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect003
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetEdgeEffect003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: TabBarBlurStyle001
 * @tc.desc: test TabBarBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarBlurStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);

    /**
     * @tc.steps: step2. update blurstyle
     * @tc.expected: step2. expect The blurstyle is COMPONENT_THICK.
     */
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    auto tabBarRenderContext = tabBarNode_->GetRenderContext();
    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        tabBarRenderContext->UpdateBackBlurStyle(styleOption);
    }
    EXPECT_EQ(tabBarRenderContext->GetBackBlurStyle()->blurStyle, BlurStyle::COMPONENT_THICK);
}

/**
* @tc.name: SetTabBarStyle001
* @tc.desc: test AddTabBarItem
* @tc.type: FUNC
*/
HWTEST_F(TabBarTestNg, SetTabBarStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
    * @tc.steps: step1. step1.SetTabBarStyle Set TabBarStyle to TabBarStyle: SUBTABBATSTYLE
    * @tc.steps: sCall the GetTabBarStyle interface under the TabContentModelNG
    * @tc.expected: Equal to TabBarStyle: SUBTABBATSTYLE.
    */
    const std::string text_test = "text_test";
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
* @tc.name: TabBarPatternProvideRestoreInfo003
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabBarTestNg, TabBarPatternProvideRestoreInfo003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: step1.1. Constructing TabBarPattern class pointers
     * @tc.expected:tabBarPattern_->ProvideRestoreInfo() not null.
     */
    EXPECT_TRUE(tabBarPattern_->ProvideRestoreInfo() != "");
}

/**
 * @tc.name: TabBarModifierHasIndicator002
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarModifierHasIndicator002, TestSize.Level1)
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
 * @tc.name: TabBarPatternAdjustFocusPosition003
 * @tc.desc: test AdjustFocusPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternAdjustFocusPosition004, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    tabBarPattern_->AdjustFocusPosition();
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->tabItemOffsets_.clear();
    OffsetF c1(-1.0f, -1.0f);

    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->focusIndicator_ = 0;
    tabBarPattern_->AdjustFocusPosition();
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps3. Set TabBarStyle: NOSTYLE
     * @tc.expected: Expected value is TabBarStyle: NOSTYLE
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::NOSTYLE);
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::NOSTYLE);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::BOTTOMTABBATSTYLE);
}

/**
 * @tc.name: TabContentModelAddTabBarItem001
 * @tc.desc: test AddTabBarItem
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabContentModelAddTabBarItem001, TestSize.Level1)
{
    const std::string text_test = "text_test";
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabContentFrameNode->GetTabBarItemId();
    tabContentFrameNode->MountToParent(swiperNode_);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    auto tabContentPattern2 = tabContentFrameNode2->GetPattern<TabContentPattern>();
    tabContentFrameNode2->MountToParent(swiperNode_);
    tabContentPattern2->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern2->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode2, DEFAULT_NODE_SLOT, true);
}
} // namespace OHOS::Ace::NG
