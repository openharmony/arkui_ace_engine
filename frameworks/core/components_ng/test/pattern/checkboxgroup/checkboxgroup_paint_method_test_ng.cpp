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
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_layout_algorithm.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_method.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
constexpr float SHAPE_SCALE_HALF = 0.5f;
constexpr float SHAPE_SCALE = 1.0f;
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

class CheckBoxGroupPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}
};

void CheckBoxGroupPaintMethodTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void CheckBoxGroupPaintMethodTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest001
 * @tc.desc: Test CheckBoxGroup PaintMethod, verify that PaintMethod can generate correct function.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupPaintMethodTest001, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    EXPECT_TRUE(checkBoxPaintProperty != nullptr);
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    checkBoxTheme->shadowWidth_ = SHADOW_WIDTH_DIMENSION;
    checkBoxTheme->borderWidth_ = BORDER_WIDTH_DIMENSION;
    checkBoxTheme->activeColor_ = ACTIVE_COLOR;
    checkBoxTheme->inactiveColor_ = INACTIVE_COLOR;
    checkBoxTheme->shadowColor_ = SHADOW_COLOR;
    checkBoxTheme->SetClickEffectColor(CLICK_EFFECT_COLOR);
    checkBoxTheme->SetHoverColor(HOVER_COLOR);
    checkBoxTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkBoxTheme));

    /**
     * @tc.case: case1. uiStatus_ == UIStatus::OFF_TO_ON.
     */
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(false, false, false, 0.0, UIStatus::OFF_TO_ON);
    auto paintMethod = checkBoxPaintMethod.GetContentDrawFunction(&paintWrapper);
    auto paintProperty = AccessibilityManager::DynamicCast<CheckBoxGroupPaintProperty>(paintWrapper.GetPaintProperty());
    paintProperty->UpdateCheckBoxGroupSelectedColor(ACTIVE_COLOR);
    EXPECT_TRUE(paintMethod != nullptr);
    EXPECT_EQ(checkBoxPaintMethod.borderWidth_, BORDER_WIDTH);
    EXPECT_EQ(checkBoxPaintMethod.activeColor_, ACTIVE_COLOR);
    EXPECT_EQ(checkBoxPaintMethod.inactiveColor_, INACTIVE_COLOR);
    EXPECT_EQ(checkBoxPaintMethod.shadowColor_, SHADOW_COLOR);
    EXPECT_EQ(checkBoxPaintMethod.clickEffectColor_, CLICK_EFFECT_COLOR);
    EXPECT_EQ(checkBoxPaintMethod.hoverColor_, HOVER_COLOR);
    EXPECT_EQ(checkBoxPaintMethod.hotZoneHorizontalPadding_, HORIZONTAL_PADDING);

    /**
     * @tc.case: case2. uiStatus_ == UIStatus::ON_TO_OFF.
     */
    PaintWrapper paintWrapper2(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupPaintMethod checkBoxPaintMethod2(false, false, false, 0.0, UIStatus::ON_TO_OFF);
    auto paintMethod2 = checkBoxPaintMethod.GetContentDrawFunction(&paintWrapper);
    EXPECT_TRUE(paintMethod2 != nullptr);

    /**
     * @tc.case: case3. uiStatus_ == UIStatus::UNSELECTED.
     */
    PaintWrapper paintWrapper3(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupPaintMethod checkBoxPaintMethod3(false, false, false, 0.0, UIStatus::UNSELECTED);
    auto paintMethod3 = checkBoxPaintMethod.GetContentDrawFunction(&paintWrapper);
    EXPECT_TRUE(paintMethod3 != nullptr);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest002
 * @tc.desc: Test CheckBoxGroup PaintMethod DrawTouchBoard.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupPaintMethodTest002, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    EXPECT_TRUE(checkBoxPaintProperty != nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     * @tc.case: case. When isTouch is true, CheckBoxPaintMethod's PaintCheckBox will call DrawTouchBoard.
     */
    CheckBoxGroupPaintMethod checkBoxPaintMethod(false, true, false, 0.0, UIStatus::FOCUS);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest003
 * @tc.desc: Test CheckBoxGroup PaintMethod DrawHoverBoard.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupPaintMethodTest003, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    EXPECT_TRUE(checkBoxPaintProperty != nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     * @tc.case: case. When isHover is true, CheckBoxPaintMethod's PaintCheckBox will call DrawHoverBoard.
     */
    CheckBoxGroupPaintMethod checkBoxPaintMethod(false, false, true, 0.0, UIStatus::FOCUS);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest004
 * @tc.desc: Test CheckBoxGroup PaintMethod DrawAnimationOffToOn.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupPaintMethodTest004, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    EXPECT_TRUE(checkBoxPaintProperty != nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    /**
     * @tc.case: case. When uiStatus_ == UIStatus::OFF_TO_ON, CheckBoxPaintMethod's PaintCheckBox will call
     * DrawAnimationOffToOn.
     */
    CheckBoxGroupPaintMethod checkBoxPaintMethod(false, false, false, 0.0, UIStatus::FOCUS);
    Testing::MockCanvas canvas;
    OffsetF offset;
    RSPen pen;
    SizeF size;
    /**
     * @tc.case: case1. shapeScale_ < CHECK_MARK_LEFT_ANIMATION_PERCENT.
     */
    checkBoxPaintMethod.shapeScale_ = 0.0;
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(2);
    checkBoxPaintMethod.DrawAnimationOffToOn(canvas, offset, pen, size);
    /**
     * @tc.case: case2. shapeScale_ == DEFAULT_MAX_CHECKBOX_SHAPE_SCALE.
     */
    checkBoxPaintMethod.shapeScale_ = SHAPE_SCALE;
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(4);
    checkBoxPaintMethod.DrawAnimationOffToOn(canvas, offset, pen, size);
    /**
     * @tc.case: case3. shapeScale_ > DEFAULT_MAX_CHECKBOX_SHAPE_SCALE and shapeScale_ !=
     * DEFAULT_MAX_CHECKBOX_SHAPE_SCALE.
     */
    checkBoxPaintMethod.shapeScale_ = SHAPE_SCALE_HALF;
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(4);
    checkBoxPaintMethod.DrawAnimationOffToOn(canvas, offset, pen, size);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest005
 * @tc.desc: Test CheckBoxGroup PaintMethod will paintCheckBox when UIStatus is OFF_TO_ON.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupPaintMethodTest005, TestSize.Level1)
{
    /**
     * @tc.case: case1. When uiStatus_ == UIStatus::OFF_TO_ON and enabled_ == true.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    EXPECT_TRUE(checkBoxPaintProperty != nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(false, false, false, 0.0, UIStatus::OFF_TO_ON);
    auto paintMethod = checkBoxPaintMethod.GetContentDrawFunction(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    EXPECT_CALL(canvas, DrawPath(_)).Times(2);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
    /**
     * @tc.case: case2. When uiStatus_ == UIStatus::OFF_TO_ON and enabled_ == false.
     */
    checkBoxPaintMethod.enabled_ = false;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    EXPECT_CALL(canvas, DrawPath(_)).Times(2);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest006
 * @tc.desc: Test CheckBoxGroup PaintMethod will paintCheckBox when UIStatus is ON_TO_OFF.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupPaintMethodTest006, TestSize.Level1)
{
    /**
     * @tc.case: case1. When uiStatus_ == UIStatus::ON_TO_OFF and enabled_ == true.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    EXPECT_TRUE(checkBoxPaintProperty != nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(false, false, false, 0.0, UIStatus::ON_TO_OFF);
    auto paintMethod2 = checkBoxPaintMethod.GetContentDrawFunction(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
    /**
     * @tc.case: case1. When uiStatus_ == UIStatus::ON_TO_OFF and enabled_ == false.
     */
    checkBoxPaintMethod.enabled_ = false;
    checkBoxPaintMethod.shapeScale_ = 1.0;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    EXPECT_CALL(canvas, DrawPath(_)).Times(4);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest007
 * @tc.desc: Test CheckBoxGroup PaintMethod will paintCheckBox when UIStatus is ON_TO_OFF.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupPaintMethodTest007, TestSize.Level1)
{
    /**
     * @tc.case: case1. When uiStatus_ == UIStatus::UNSELECTED and enabled_ == true.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    EXPECT_TRUE(checkBoxPaintProperty != nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(false, false, false, 0.0, UIStatus::UNSELECTED);
    auto paintMethod3 = checkBoxPaintMethod.GetContentDrawFunction(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
    /**
     * @tc.case: case1. When uiStatus_ == UIStatus::UNSELECTED and enabled_ == false.
     */
    checkBoxPaintMethod.enabled_ = false;
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest011
 * @tc.desc: Test CheckBoxGroup PaintMethod DrawPart.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupPaintMethodTest011, TestSize.Level1)
{
    /**
     * @tc.case: case1. When status == CheckBoxGroupPaintProperty::SelectStatus::PART and enabled_ == true.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    EXPECT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus::PART);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);
    CheckBoxGroupPaintMethod checkBoxPaintMethod(false, false, false, 0.0, UIStatus::UNSELECTED);
    auto paintMethod4 = checkBoxPaintMethod.GetContentDrawFunction(&paintWrapper);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    EXPECT_CALL(canvas, DrawPath(_)).Times(2);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
    /**
     * @tc.case: case1. When status == CheckBoxGroupPaintProperty::SelectStatus::PART and enabled_ == false.
     */
    checkBoxPaintMethod.enabled_ = false;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    EXPECT_CALL(canvas, DrawPath(_)).Times(2);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest001
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm can correctly InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupLayoutAlgorithmTest001, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    checkBoxTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    checkBoxTheme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    checkBoxTheme->defaultWidth_ = DEFAULT_WIDTH_DIMENSION;
    checkBoxTheme->defaultHeight_ = DEFAULT_HEIGHT_DIMENSION;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(checkBoxTheme));
    CheckBoxGroupLayoutAlgorithm checkBoxLayoutAlgorithm;
    checkBoxLayoutAlgorithm.InitializeParam();
    EXPECT_EQ(checkBoxLayoutAlgorithm.defaultWidth_, DEFAULT_WIDTH);
    EXPECT_EQ(checkBoxLayoutAlgorithm.defaultHeight_, DEFAULT_HEIGHT);
    EXPECT_EQ(checkBoxLayoutAlgorithm.horizontalPadding_, HORIZONTAL_PADDING.ConvertToPx());
    EXPECT_EQ(checkBoxLayoutAlgorithm.verticalPadding_, VERTICAL_PADDING.ConvertToPx());
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest002
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's MeasureContent can get contentSize
             when Width and height are set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupLayoutAlgorithmTest002, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    /**
    //     corresponding ets code:
    //         CheckBoxGroup().width(200).height(210)
    //     size = (200, 200)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    CheckBoxGroupLayoutAlgorithm checkBoxLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT);
    auto size = checkBoxLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(COMPONENT_WIDTH, COMPONENT_WIDTH));
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest003
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's MeasureContent can get contentSize
             when The front end only sets width.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxLayoutAlgorithmTest003, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    /**
    //     corresponding ets code:
    //         CheckBoxGroup().width(200)
    //     size = (200, 200)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    CheckBoxGroupLayoutAlgorithm checkBoxLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH);
    auto size = checkBoxLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(COMPONENT_WIDTH, COMPONENT_WIDTH));
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest004
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's MeasureContent can get contentSize
             when The front end only sets height.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxLayoutAlgorithmTest004, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    /**
    //     corresponding ets code:
    //         CheckBoxGroup().height(210)
    //     size = (210, 210)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    CheckBoxGroupLayoutAlgorithm checkBoxLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT);
    auto size = checkBoxLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(COMPONENT_HEIGHT, COMPONENT_HEIGHT));
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest005
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's MeasureContent can get contentSize from the theme,
             when Width and height are not set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupLayoutAlgorithmTest005, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto checkBoxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    checkBoxTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    checkBoxTheme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    checkBoxTheme->defaultWidth_ = DEFAULT_WIDTH_DIMENSION;
    checkBoxTheme->defaultHeight_ = DEFAULT_HEIGHT_DIMENSION;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(checkBoxTheme));
    /**
    //     corresponding ets code:
    //         CheckBoxGroup()
    //     length = min(theme.Width(), theme.Height()), size = (length, length)
    */
    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    CheckBoxGroupLayoutAlgorithm checkBoxLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = SizeF(1000.0, 1000.0);
    layoutConstraintSize.minSize = SizeF(0, 0);
    auto size = checkBoxLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(checkBoxLayoutAlgorithm.defaultWidth_, DEFAULT_WIDTH);
    EXPECT_EQ(checkBoxLayoutAlgorithm.defaultHeight_, DEFAULT_HEIGHT);
    EXPECT_EQ(checkBoxLayoutAlgorithm.horizontalPadding_, HORIZONTAL_PADDING.ConvertToPx());
    EXPECT_EQ(checkBoxLayoutAlgorithm.verticalPadding_, VERTICAL_PADDING.ConvertToPx());
    auto length = std::min(checkBoxLayoutAlgorithm.defaultWidth_ - 2 * checkBoxLayoutAlgorithm.horizontalPadding_,
        checkBoxLayoutAlgorithm.defaultHeight_ - 2 * checkBoxLayoutAlgorithm.verticalPadding_);
    EXPECT_EQ(size.value(), SizeF(length, length));
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest006
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's MeasureContent can get contentSize
             when Width and height are set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupLayoutAlgorithmTest006, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<CheckboxTheme>()));

    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    CheckBoxGroupLayoutAlgorithm checkBoxLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH_INVALID);
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT_INVALID);
    auto size = checkBoxLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest007
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's MeasureContent can get contentSize
             when Width and height are set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupLayoutAlgorithmTest007, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<CheckboxTheme>()));

    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    CheckBoxGroupLayoutAlgorithm checkBoxLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetWidth(COMPONENT_WIDTH_INVALID);
    auto size = checkBoxLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest008
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's MeasureContent can get contentSize
             when Width and height are set in the front end.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupLayoutAlgorithmTest008, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<CheckboxTheme>()));

    LayoutWrapper layoutWrapper(nullptr, nullptr, nullptr);
    CheckBoxGroupLayoutAlgorithm checkBoxLayoutAlgorithm;
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetHeight(COMPONENT_HEIGHT_INVALID);
    auto size = checkBoxLayoutAlgorithm.MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest009
 * @tc.desc: Test CheckBoxGroup PaintMethod DrawTouchBoard.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxGroupPaintMethodTest009, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    EXPECT_TRUE(checkBoxPaintProperty != nullptr);
    checkBoxPaintProperty->UpdateCheckBoxGroupSelectedColor(ACTIVE_COLOR);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);

    CheckBoxGroupPaintMethod checkBoxPaintMethod(false, true, false, 0.0, UIStatus::FOCUS);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
}

/**
 * @tc.name: CheckBoxGroupPaintMethodTest010
 * @tc.desc: Test CheckBoxGroup PaintMethod DrawTouchBoard.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupPaintMethodTestNg, CheckBoxPaintMethodTest010, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    EXPECT_TRUE(checkBoxPaintProperty != nullptr);
    checkBoxPaintProperty->UpdateCheckBoxGroupSelectedColor(ACTIVE_COLOR);
    PaintWrapper paintWrapper(nullptr, geometryNode, checkBoxPaintProperty);

    CheckBoxGroupPaintMethod checkBoxPaintMethod(true, true, false, 0.0, UIStatus::FOCUS);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    checkBoxPaintMethod.enabled_ = true;
    checkBoxPaintMethod.PaintCheckBox(canvas, &paintWrapper);
}
} // namespace OHOS::Ace::NG
