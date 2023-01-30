/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "base/geometry/ng/size_t.h"
#define private public
#define protected public
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/radio/radio_layout_algorithm.h"
#include "core/components_ng/pattern/radio/radio_paint_method.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr bool CHECKED = true;
constexpr float POINT_SCALE = 0.5f;
constexpr float POINT_SCALE_INVALID = 1.0f;
constexpr float POINT_SCALE_INVALID_0 = 0.0f;
constexpr float COMPONENT_WIDTH = 200.0;
constexpr float COMPONENT_HEIGHT = 210.0;
constexpr float COMPONENT_WIDTH_INVALID = -1.0;
constexpr float COMPONENT_HEIGHT_INVALID = -1.0;
constexpr double DEFAULT_WIDTH = 100.0;
constexpr double DEFAULT_HEIGHT = 110.0;
constexpr Dimension DEFAULT_WIDTH_DIMENSION = Dimension(DEFAULT_WIDTH);
constexpr Dimension DEFAULT_HEIGHT_DIMENSION = Dimension(DEFAULT_HEIGHT);
constexpr double SHADOW_WIDTH = 200.0;
constexpr double BORDER_WIDTH = 300.0;
constexpr Dimension SHADOW_WIDTH_DIMENSION = Dimension(SHADOW_WIDTH);
constexpr Dimension BORDER_WIDTH_DIMENSION = Dimension(BORDER_WIDTH);
const Color ACTIVE_COLOR = Color::BLACK;
const Color INACTIVE_COLOR = Color::GREEN;
const Color SHADOW_COLOR = Color::RED;
const Color CLICK_EFFECT_COLOR = Color::WHITE;
const Color HOVER_COLOR = Color::GRAY;
constexpr Dimension HORIZONTAL_PADDING = Dimension(5.0);
constexpr Dimension VERTICAL_PADDING = Dimension(4.0);
} // namespace

class RadioPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}
};

void RadioPaintMethodTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void RadioPaintMethodTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: RadioPaintMethodTest001
 * @tc.desc: Test Radio PaintMethod, verify that PaintMethod can generate correct function.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioPaintMethodTest001, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    EXPECT_TRUE(radioPaintProperty != nullptr);
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    radioTheme->shadowWidth_ = SHADOW_WIDTH_DIMENSION;
    radioTheme->borderWidth_ = BORDER_WIDTH_DIMENSION;
    radioTheme->activeColor_ = ACTIVE_COLOR;
    radioTheme->inactiveColor_ = INACTIVE_COLOR;
    radioTheme->shadowColor_ = SHADOW_COLOR;
    radioTheme->SetClickEffectColor(CLICK_EFFECT_COLOR);
    radioTheme->SetHoverColor(HOVER_COLOR);
    radioTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(radioTheme));
    /**
     * @tc.case: case1. radioPaintProperty has not radioCheck.
     */
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    RadioPaintMethod radioPaintMethod(false, false, false, 0.0, 0.0, UIStatus::PART);
    auto paintMethod = radioPaintMethod.GetContentDrawFunction(&paintWrapper);
    EXPECT_TRUE(paintMethod != nullptr);
    EXPECT_EQ(radioPaintMethod.shadowWidth_, SHADOW_WIDTH);
    EXPECT_EQ(radioPaintMethod.borderWidth_, BORDER_WIDTH);
    EXPECT_EQ(radioPaintMethod.activeColor_, ACTIVE_COLOR);
    EXPECT_EQ(radioPaintMethod.inactiveColor_, INACTIVE_COLOR);
    EXPECT_EQ(radioPaintMethod.shadowColor_, SHADOW_COLOR);
    EXPECT_EQ(radioPaintMethod.clickEffectColor_, CLICK_EFFECT_COLOR);
    EXPECT_EQ(radioPaintMethod.hoverColor_, HOVER_COLOR);
    EXPECT_EQ(radioPaintMethod.hotZoneHorizontalPadding_, HORIZONTAL_PADDING);
    /**
     * @tc.case: case2. radioPaintProperty has radioCheck.
     */
    radioPaintProperty->UpdateRadioCheck(CHECKED);
    PaintWrapper paintWrapper2(nullptr, geometryNode, radioPaintProperty);
    RadioPaintMethod radioPaintMethod2(false, false, false, 0.0, 0.0, UIStatus::PART);
    auto paintMethod2 = radioPaintMethod.GetContentDrawFunction(&paintWrapper);
    EXPECT_TRUE(paintMethod2 != nullptr);
}

/**
 * @tc.name: RadioPaintMethodTest002
 * @tc.desc: Test Radio PaintMethod->DrawTouchBoard.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioPaintMethodTest002, TestSize.Level1)
{
    /**
     * @tc.case: case. When isTouch is true, RadioPaintMethod's PaintRadio will DrawTouchBoard.
     */
    RadioPaintMethod radioPaintMethod(false, true, false, 0.0, 0.0, UIStatus::FOCUS);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    radioPaintMethod.PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
}

/**
 * @tc.name: RadioPaintMethodTest003
 * @tc.desc: Test Radio PaintMethod->DrawHoverBoard.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioPaintMethodTest003, TestSize.Level1)
{
    /**
     * @tc.case: case. When isHover is true, RadioPaintMethod's PaintRadio will DrawHoverBoard.
     */
    RadioPaintMethod radioPaintMethod(false, false, true, 0.0, 0.0, UIStatus::FOCUS);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    radioPaintMethod.PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
}

/**
 * @tc.name: RadioPaintMethodTest004
 * @tc.desc: Test Radio PaintMethod will paintRadio when UIStatus is SELECTED.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioPaintMethodTest004, TestSize.Level1)
{
    /**
     * @tc.case: case1. When enabled is false and pointScale_ is valid, RadioPaintMethod will Paint Radio with shadow.
     *           enabled = false, 0 < pointScale_ < 1
     */
    RadioPaintMethod radioPaintMethod(false, false, false, 0.0, POINT_SCALE, UIStatus::SELECTED);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(2));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    radioPaintMethod.PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    /**
     * @tc.case: case2. When enabled is true and pointScale_ is invalid, RadioPaintMethod will Paint Radio without
     *                  shadow.
     *           enabled = true, pointScale_ == 0 || pointScale_ == 1
     */
    RadioPaintMethod radioPaintMethod2(true, false, false, 0.0, POINT_SCALE_INVALID, UIStatus::SELECTED);
    Testing::MockCanvas canvas2;
    EXPECT_CALL(canvas2, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas2));
    EXPECT_CALL(canvas2, DrawCircle(_, _)).Times(AtLeast(2));
    EXPECT_CALL(canvas2, AttachPen(_)).WillRepeatedly(ReturnRef(canvas2));
    radioPaintMethod2.PaintRadio(canvas2, false, CONTENT_SIZE, CONTENT_OFFSET);
}

/**
 * @tc.name: RadioPaintMethodTest005
 * @tc.desc: Test Radio PaintMethod will paintRadio when UIStatus is UNSELECTED.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioPaintMethodTest005, TestSize.Level1)
{
    /**
     * @tc.case: case1. When enabled is false, RadioPaintMethod will Paint Radio with border.
     */
    RadioPaintMethod radioPaintMethod(false, false, false, 0.0, 0.0, UIStatus::UNSELECTED);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(2);
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    radioPaintMethod.PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    /**
     * @tc.case: case2. When enabled is true, RadioPaintMethod will Paint Radio without border.
     */
    RadioPaintMethod radioPaintMethod2(true, false, false, 0.0, 0.0, UIStatus::UNSELECTED);
    Testing::MockCanvas canvas2;
    EXPECT_CALL(canvas2, AttachBrush(_)).WillOnce(ReturnRef(canvas2));
    EXPECT_CALL(canvas2, DrawCircle(_, _)).Times(2);
    EXPECT_CALL(canvas2, AttachPen(_)).WillOnce(ReturnRef(canvas2));
    radioPaintMethod2.PaintRadio(canvas2, false, CONTENT_SIZE, CONTENT_OFFSET);
}

/**
 * @tc.name: RadioLayoutAlgorithmTest001
 * @tc.desc: Verify that RadioLayoutAlgorithm can correctly InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioLayoutAlgorithmTest001, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    radioTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    radioTheme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    radioTheme->defaultWidth_ = DEFAULT_WIDTH_DIMENSION;
    radioTheme->defaultHeight_ = DEFAULT_HEIGHT_DIMENSION;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(radioTheme));
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    radioLayoutAlgorithm.InitializeParam();
    EXPECT_EQ(radioLayoutAlgorithm.horizontalPadding_, HORIZONTAL_PADDING.ConvertToPx());
    EXPECT_EQ(radioLayoutAlgorithm.verticalPadding_, VERTICAL_PADDING.ConvertToPx());
}

/**
 * @tc.name: RadioLayoutAlgorithmTest002
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when Width and height are set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioLayoutAlgorithmTest002, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    /**
    //     corresponding ets code:
    //         Radio().width(200).height(210)
    //     size = (200, 200)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(COMPONENT_WIDTH, COMPONENT_WIDTH));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest003
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when The front end only sets width.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioLayoutAlgorithmTest003, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    /**
    //     corresponding ets code:
    //         Radio().width(200)
    //     size = (200, 200)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(COMPONENT_WIDTH, COMPONENT_WIDTH));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest004
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when The front end only sets height.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioLayoutAlgorithmTest004, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    /**
    //     corresponding ets code:
    //         Radio().height(210)
    //     size = (210, 210)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(COMPONENT_HEIGHT, COMPONENT_HEIGHT));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest005
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize from the theme,
             when Width and height are not set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioLayoutAlgorithmTest005, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    radioTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    radioTheme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    radioTheme->defaultWidth_ = DEFAULT_WIDTH_DIMENSION;
    radioTheme->defaultHeight_ = DEFAULT_HEIGHT_DIMENSION;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(radioTheme));
    /**
    //     corresponding ets code:
    //         Radio()
    //     length = min(theme.Width(), theme.Height()), size = (length, length)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = SizeF(1000.0, 1000.0);
    layoutConstraintSize.minSize = SizeF(0, 0);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(radioLayoutAlgorithm.horizontalPadding_, HORIZONTAL_PADDING.ConvertToPx());
    EXPECT_EQ(radioLayoutAlgorithm.verticalPadding_, VERTICAL_PADDING.ConvertToPx());
}

/**
 * @tc.name: RadioLayoutAlgorithmTest006
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when Width and height are set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioLayoutAlgorithmTest006, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH_INVALID);
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT_INVALID);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest007
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when The front end only sets width.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioLayoutAlgorithmTest007, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH_INVALID);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: RadioLayoutAlgorithmTest008
 * @tc.desc: Verify that RadioLayoutAlgorithm's MeasureContent can get contentSize
             when The front end only sets height.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioLayoutAlgorithmTest008, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<RadioTheme>()));
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT_INVALID);
    auto size = radioLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: RadioPaintMethodTest009
 * @tc.desc: Test Radio PaintMethod will paintRadio when UIStatus is SELECTED.
 * @tc.type: FUNC
 */
HWTEST_F(RadioPaintMethodTestNg, RadioPaintMethodTest009, TestSize.Level1)
{
    RadioPaintMethod radioPaintMethod(true, false, false, 0.0, POINT_SCALE_INVALID_0, UIStatus::SELECTED);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(2));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    radioPaintMethod.PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
}
} // namespace OHOS::Ace::NG
