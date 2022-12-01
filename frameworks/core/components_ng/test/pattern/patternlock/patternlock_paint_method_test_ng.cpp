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
#define private public
#define protected public
#include "core/components_ng/pattern/patternlock/patternlock_layout_algorithm.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_method.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_ng/pattern/patternlock/patternlock_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
struct TestProperty {
    std::optional<Dimension> sideLength = std::nullopt;
    std::optional<Dimension> circleRadius = std::nullopt;
    std::optional<Color> regularColor = std::nullopt;
    std::optional<Color> selectedColor = std::nullopt;
    std::optional<Color> activeColor = std::nullopt;
    std::optional<Color> pathColor = std::nullopt;
    std::optional<Dimension> strokeWidth = std::nullopt;
    std::optional<bool> autoReset = std::nullopt;
};

class PatternLockPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}
};

void PatternLockPaintMethodTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void PatternLockPaintMethodTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: PatternLockPaintMethodTest001
 * @tc.desc: Test PatternLockPaintMethod can create correct Draw Function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPaintMethodTestNg, PatternLockPaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create patternLock PaintMethod.
     */
    std::vector<PatternLockCell> vecCell;
    OffsetF offset;
    auto paintMethod = AceType::MakeRefPtr<PatternLockPaintMethod>(vecCell, offset, false);
    /**
     * @tc.step: step2. create Draw Function and call it.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    geometryNode->SetContentSize(SizeF());
    auto patternLockPaintProperty = AceType::MakeRefPtr<PatternLockPaintProperty>();
    PaintWrapper paintWrapper(nullptr, geometryNode, patternLockPaintProperty);
    auto drawFunc = paintMethod->GetContentDrawFunction(&paintWrapper);
    EXPECT_TRUE(drawFunc != nullptr);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    drawFunc(canvas);
}

/**
 * @tc.name: PatternLockPaintMethodTest002
 * @tc.desc: Test PatternLockPaintMethod can initialize Params correctly.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPaintMethodTestNg, PatternLockPaintMethodTest002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create patternLock PaintMethod and PatternLockTheme.
     */
    std::vector<PatternLockCell> vecCell;
    OffsetF offset;
    PatternLockPaintMethod paintMethod(vecCell, offset, false);
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    patternlockTheme->regularColor_ = Color::BLACK;
    patternlockTheme->selectedColor_ = Color::BLUE;
    patternlockTheme->activeColor_ = Color::RED;
    patternlockTheme->pathColor_ = Color::GRAY;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));
    /**
     * @tc.case: case1. call InitializeParam with invalid PatternLockPaintProperty.
     */
    auto patternLockPaintProperty = AceType::MakeRefPtr<PatternLockPaintProperty>();
    paintMethod.InitializeParam(patternLockPaintProperty);
    EXPECT_EQ(paintMethod.sideLength_, 300.0_vp);
    EXPECT_EQ(paintMethod.circleRadius_, 14.0_vp);
    EXPECT_EQ(paintMethod.pathStrokeWidth_, 34.0_vp);
    EXPECT_EQ(paintMethod.autoReset_, true);
    EXPECT_EQ(paintMethod.regularColor_, Color::BLACK);
    EXPECT_EQ(paintMethod.selectedColor_, Color::BLUE);
    EXPECT_EQ(paintMethod.activeColor_, Color::RED);
    EXPECT_EQ(paintMethod.pathColor_, Color::GRAY);
    /**
     * @tc.case: case2. call InitializeParam with valid PatternLockPaintProperty.
     */
    patternLockPaintProperty->UpdateSideLength(Dimension(30.0));
    patternLockPaintProperty->UpdateCircleRadius(Dimension(20.0));
    patternLockPaintProperty->UpdatePathStrokeWidth(Dimension(10.0));
    patternLockPaintProperty->UpdateAutoReset(false);
    patternLockPaintProperty->UpdateRegularColor(Color::RED);
    patternLockPaintProperty->UpdateSelectedColor(Color::GREEN);
    patternLockPaintProperty->UpdateActiveColor(Color::BLACK);
    patternLockPaintProperty->UpdatePathColor(Color::WHITE);
    paintMethod.InitializeParam(patternLockPaintProperty);
    EXPECT_EQ(paintMethod.sideLength_, patternLockPaintProperty->GetSideLengthValue());
    EXPECT_EQ(paintMethod.circleRadius_, patternLockPaintProperty->GetCircleRadiusValue());
    EXPECT_EQ(paintMethod.pathStrokeWidth_, patternLockPaintProperty->GetPathStrokeWidthValue());
    EXPECT_EQ(paintMethod.autoReset_, patternLockPaintProperty->GetAutoResetValue());
    EXPECT_EQ(paintMethod.regularColor_, patternLockPaintProperty->GetRegularColorValue());
    EXPECT_EQ(paintMethod.selectedColor_, patternLockPaintProperty->GetSelectedColorValue());
    EXPECT_EQ(paintMethod.activeColor_, patternLockPaintProperty->GetActiveColorValue());
    EXPECT_EQ(paintMethod.pathColor_, patternLockPaintProperty->GetPathColorValue());
}

/**
 * @tc.name: PatternLockPaintMethodTest003
 * @tc.desc: Test GetCircleCenterByXY function can get correct offset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPaintMethodTestNg, PatternLockPaintMethodTest003, TestSize.Level1)
{
    std::vector<PatternLockCell> vecCell;
    OffsetF offset;
    PatternLockPaintMethod paintMethod(vecCell, offset, false);
    paintMethod.sideLength_ = Dimension(36.0);
    int16_t x = 1;
    int16_t y = 1;
    auto cellCenter = paintMethod.GetCircleCenterByXY(OffsetF(1.0, 1.0), x, y);
    EXPECT_EQ(cellCenter.GetX(), 7.0);
    EXPECT_EQ(cellCenter.GetY(), 7.0);
}

/**
 * @tc.name: PatternLockPaintMethodTest004
 * @tc.desc: Test PaintLockLine function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPaintMethodTestNg, PatternLockPaintMethodTest004, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    /**
     * @tc.case: case1. PatternLock's choosePoint count = 0.
     */
    std::vector<PatternLockCell> vecCell;
    OffsetF offset;
    PatternLockPaintMethod paintMethod(vecCell, offset, false);
    EXPECT_CALL(canvas, Restore()).Times(0);
    paintMethod.PaintLockLine(canvas, OffsetF());
    /**
     * @tc.case: case2. pathStrokeWidth_ <= 0.
     */
    std::vector<PatternLockCell> vecCell2 = { PatternLockCell(0, 1), PatternLockCell(0, 2) };
    PatternLockPaintMethod paintMethod2(vecCell2, offset, false);
    EXPECT_CALL(canvas, Restore()).Times(0);
    paintMethod2.PaintLockLine(canvas, OffsetF());
    /**
     * @tc.case: case3. isMoveEventValid_ is flase.
     */
    std::vector<PatternLockCell> vecCell3 = { PatternLockCell(0, 1), PatternLockCell(0, 2), PatternLockCell(1, 2) };
    PatternLockPaintMethod paintMethod3(vecCell3, offset, false);
    paintMethod3.pathStrokeWidth_ = Dimension(10.0);
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(vecCell3.size() - 1);
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(1);
    paintMethod3.PaintLockLine(canvas, OffsetF());
    /**
     * @tc.case: case4. isMoveEventValid_ is true.
     */
    std::vector<PatternLockCell> vecCell4 = { PatternLockCell(0, 1), PatternLockCell(0, 2), PatternLockCell(1, 2),
        PatternLockCell(2, 2) };
    PatternLockPaintMethod paintMethod4(vecCell4, offset, true);
    paintMethod4.pathStrokeWidth_ = Dimension(10.0);
    EXPECT_CALL(canvas, AttachPen(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(vecCell4.size());
    EXPECT_CALL(canvas, DetachPen()).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).Times(1);
    paintMethod4.PaintLockLine(canvas, OffsetF());
}

/**
 * @tc.name: PatternLockPaintMethodTest005
 * @tc.desc: Test PaintLockCircle function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPaintMethodTestNg, PatternLockPaintMethodTest005, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    /**
     * @tc.case: case1. Current Point (x, y) is not checked.
     */
    std::vector<PatternLockCell> vecCell = { PatternLockCell(0, 1), PatternLockCell(0, 2), PatternLockCell(1, 2) };
    OffsetF offset;
    PatternLockPaintMethod paintMethod(vecCell, offset, true);
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    paintMethod.PaintLockCircle(canvas, OffsetF(), 1, 4);
    /**
     * @tc.case: case2. Current Point (x, y) is checked but the selected Point is not the last Point.
     */
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    paintMethod.PaintLockCircle(canvas, OffsetF(), 0, 1);
    /**
     * @tc.case: case3. last Point (x, y) is checked and isMoveEventValid_ is true.
     */
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    paintMethod.PaintLockCircle(canvas, OffsetF(), 1, 2);
    /**
     * @tc.case: case4. last Point (x, y) is checked but isMoveEventValid_ is false.
     */
    PatternLockPaintMethod paintMethod2(vecCell, offset, false);
    EXPECT_CALL(canvas, AttachBrush(_)).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    paintMethod2.PaintLockCircle(canvas, OffsetF(), 1, 2);
}

/**
 * @tc.name: PatternLockLayoutAlgorithmTest001
 * @tc.desc: Test GetCircleCenterByXY function can get correct offset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockPaintMethodTestNg, PatternLockLayoutAlgorithmTest001, TestSize.Level1)
{
    constexpr Dimension sideLength = Dimension(20.0);
    PatternLockLayoutAlgorithm layoutAlgorithm(sideLength);
    /**
     * @tc.case: case1. selfIdealSize's width is null.
     */
    LayoutConstraintF constraint1;
    auto size1 = layoutAlgorithm.MeasureContent(constraint1, nullptr);
    EXPECT_EQ(size1.value(), SizeF(20.0, 20.0));
    /**
     * @tc.case: case2. selfIdealSize's width is not null but selfIdealSize is invalid.
     */
    LayoutConstraintF constraint2;
    constraint2.selfIdealSize.width_ = 10.0;
    auto size2 = layoutAlgorithm.MeasureContent(constraint2, nullptr);
    EXPECT_EQ(size2.value(), SizeF(20.0, 20.0));
    /**
     * @tc.case: case3. selfIdealSize's width is valid.
     */
    LayoutConstraintF constraint3;
    constraint3.selfIdealSize.width_ = 10.0;
    constraint3.selfIdealSize.height_ = .0;
    auto size3 = layoutAlgorithm.MeasureContent(constraint3, nullptr);
    EXPECT_EQ(size3.value(), SizeF(10.0, 10.0));
}
} // namespace OHOS::Ace::NG
