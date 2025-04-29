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

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>

#include "gtest/gtest.h"
#include "mock_canvas_paint.h"

#define protected public
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/canvas/canvas_event_hub.h"
#include "core/components_ng/pattern/canvas/canvas_layout_algorithm.h"
#include "core/components_ng/pattern/canvas/canvas_model.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_modifier.h"
#include "core/components_ng/pattern/canvas/canvas_paint_mem.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/components_ng/pattern/canvas/custom_paint_paint_method.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CanvasCustomPaintMethodTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void CanvasCustomPaintMethodTestTwoNg::SetUpTestCase()
{
    MockContainer::SetUp();
}

void CanvasCustomPaintMethodTestTwoNg::TearDownTestCase()
{
    MockContainer::TearDown();
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo001
 * @tc.desc: Test the function 'CheckFilterProperty' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo001, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    EXPECT_FALSE(paintMethod->CheckFilterProperty(static_cast<FilterType>(-1), "10"));
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo002
 * @tc.desc: Test the function 'ParseFilter' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo002, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    std::vector<FilterProperty> filters;
    std::string filter = "blur(10aa)";
    EXPECT_FALSE(paintMethod->ParseFilter(filter, filters));
    EXPECT_EQ(filters.size(), 0);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo003
 * @tc.desc: Test the function 'UpdateFontFamilies' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo003, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    MockPipelineContext::SetUp();
    MockPipelineContext::GetCurrent()->fontManager_ = AceType::MakeRefPtr<MockFontManager>();
    EXPECT_TRUE(MockPipelineContext::GetCurrent()->fontManager_);

    paintMethod->UpdateFontFamilies();
    EXPECT_FALSE(MockPipelineContext::GetCurrent()->fontManager_->IsUseAppCustomFont());
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo004
 * @tc.desc: Test the function 'MakeConicGradient' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo004, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    Ace::Gradient gradient;
    gradient.SetType(Ace::GradientType::LINEAR);
    EXPECT_EQ(paintMethod->MakeConicGradient(gradient), nullptr);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo005
 * @tc.desc: Test the function 'UpdatePaintShader' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo005, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Ace::Gradient gradient;
    gradient.type_ = Ace::GradientType::SWEEP;
    gradient.SetInnerRadius(0.0f);
    gradient.SetBeginOffset(Offset(1.0f, 1.0f));
    gradient.SetEndOffset(Offset(1.0f, 1.0f));
    gradient.colors_.emplace_back(Color::BLACK);
    gradient.colors_.emplace_back(Color::BLUE);
    paintMethod->UpdatePaintShader(nullptr, nullptr, gradient);
    RSPoint beginPoint = RSPoint(static_cast<RSScalar>(gradient.GetBeginOffset().GetX()),
        static_cast<RSScalar>(gradient.GetBeginOffset().GetY()));
    RSPoint endPoint = RSPoint(
        static_cast<RSScalar>(gradient.GetEndOffset().GetX()), static_cast<RSScalar>(gradient.GetEndOffset().GetY()));
    EXPECT_FALSE(gradient.GetInnerRadius() <= 0.0 && beginPoint == endPoint);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo006
 * @tc.desc: Test the function 'DrawImageInternal' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo006, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Testing::MockCanvas canvas;
    Ace::CanvasImage canvasImage;
    std::shared_ptr<RSImage> image;
    Testing::MockBrush brush;

    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->state_.shadow.SetOffset(Offset(1.0f, 1.0f));
    EXPECT_FALSE(paintMethod->state_.globalState.HasGlobalAlpha());
    canvasImage.flag = static_cast<CustomPaintPaintMethod::DrawImageType>(-1);
    EXPECT_CALL(canvas, SaveLayer(_)).WillRepeatedly(Return());
    EXPECT_CALL(brush, SetAlphaF(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawImage(_, _, _, _)).WillRepeatedly(Return());
    paintMethod->DrawImageInternal(canvasImage, image);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo007
 * @tc.desc: Test the function 'FillRect' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo007, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Testing::MockCanvas canvas;
    Testing::MockBrush brush;
    Testing::MockPath path;
    Rect rect;
    Offset offset(0.0f, 0.0f);

    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    paintMethod->state_.globalState.SetAlpha(1.0f);
    EXPECT_TRUE(paintMethod->state_.globalState.HasGlobalAlpha());
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor1(Color::BLACK);
    OHOS::Ace::GradientColor gradientColor2(Color::RED);
    gradient.AddColor(gradientColor1);
    gradient.AddColor(gradientColor2);
    paintMethod->state_.fillState.SetGradient(gradient);
    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->state_.shadow.SetOffset(offset);
    paintMethod->state_.shadow.SetLightRadius(0.5f);
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(brush, SetColor(_)).WillRepeatedly(Return());
    EXPECT_CALL(brush, SetAlphaF(_)).WillRepeatedly(Return());
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    paintMethod->FillRect(rect);

    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_ATOP);
    paintMethod->state_.fillState.paintStyle_ = PaintStyle::Color;
    paintMethod->state_.globalState.SetAlpha(-1.0f);
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, SaveLayer(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    paintMethod->FillRect(rect);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo008
 * @tc.desc: Test the function 'StrokeRect' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo008, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Rect rect;
    Testing::MockPath path;
    Testing::MockCanvas canvas;
    Offset offset(0.0, 0.0);

    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor1(Color::BLACK);
    OHOS::Ace::GradientColor gradientColor2(Color::RED);
    paintMethod->state_.fillState.gradient_ = gradient;
    paintMethod->state_.fillState.gradient_.AddColor(gradientColor1);
    paintMethod->state_.fillState.gradient_.AddColor(gradientColor2);
    paintMethod->state_.fillState.paintStyle_ = PaintStyle::Gradient;
    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->state_.shadow.SetOffset(offset);
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    paintMethod->StrokeRect(rect);

    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_ATOP);
    paintMethod->state_.fillState.paintStyle_ = PaintStyle::Color;
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    paintMethod->StrokeRect(rect);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo009
 * @tc.desc: Test the function 'SetOpacityFilter' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo009, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    float percentNum = 1.0f;
    string percentFalse = "A";
    string percentTrue = "0.5";
    paintMethod->SetOpacityFilter(percentFalse);
    EXPECT_FALSE(paintMethod->CheckNumberAndPercentage(percentFalse, true, percentNum));
    paintMethod->SetOpacityFilter(percentTrue);
    EXPECT_TRUE(paintMethod->CheckNumberAndPercentage(percentTrue, true, percentNum));
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo010
 * @tc.desc: Test the function 'UpdateFontFamilies' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo010, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    MockPipelineContext::SetUp();
    auto pipeContext = MockPipelineContext::GetCurrent();
    paintMethod->context_ = AceType::WeakClaim(AceType::RawPtr(pipeContext));
    paintMethod->UpdateFontFamilies();
    EXPECT_TRUE(paintMethod->context_.Upgrade());
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo011
 * @tc.desc: Test the function 'FillRect' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo011, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Testing::MockCanvas canvas;
    Testing::MockBrush brush;
    Testing::MockPath path;
    Rect rect;
    Offset offset(0.0f, 0.0f);

    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    paintMethod->state_.globalState.SetAlpha(1.0f);
    EXPECT_TRUE(paintMethod->state_.globalState.HasGlobalAlpha());
    OHOS::Ace::Pattern pattern;
    void* voidPtr = static_cast<void*>(new char[10]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    pattern.SetPixelMap(pixelMap);
    string src = "ImgSrc";
    pattern.SetImgSrc(src);
    paintMethod->state_.fillState.SetPattern(pattern);
    auto sharedPattern = std::make_shared<OHOS::Ace::Pattern>();
    sharedPattern->SetPixelMap(pixelMap);
    sharedPattern->SetImgSrc(src);
    std::weak_ptr<Ace::Pattern> patternWeak = sharedPattern;
    paintMethod->state_.fillState.SetPatternNG(patternWeak);
    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->state_.shadow.SetOffset(offset);
    paintMethod->state_.shadow.SetLightRadius(0.5f);
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(brush, SetColor(_)).WillRepeatedly(Return());
    EXPECT_CALL(brush, SetAlphaF(_)).WillRepeatedly(Return());
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    paintMethod->FillRect(rect);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo012
 * @tc.desc: Test the function 'StrokeRect', 'Stroke', 'Path2DStroke' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo012, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Rect rect;
    Testing::MockPath path;
    Testing::MockCanvas canvas;
    Offset offset(0.0, 0.0);

    OHOS::Ace::Pattern pattern;
    void* voidPtr = static_cast<void*>(new char[10]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    pattern.SetPixelMap(pixelMap);
    string src = "ImgSrc";
    pattern.SetImgSrc(src);
    paintMethod->state_.strokeState.SetPattern(pattern);
    auto sharedPattern = std::make_shared<OHOS::Ace::Pattern>();
    sharedPattern->SetPixelMap(pixelMap);
    sharedPattern->SetImgSrc(src);
    std::weak_ptr<Ace::Pattern> patternWeak = sharedPattern;
    paintMethod->state_.strokeState.SetPatternNG(patternWeak);
    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->state_.shadow.SetOffset(offset);
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    paintMethod->StrokeRect(rect);
    paintMethod->Stroke();
    paintMethod->Path2DStroke();
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo013
 * @tc.desc: Test the function 'Stroke' and 'Path2DStroke' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo013, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Testing::MockCanvas canvas;
    Testing::MockBrush brush;
    Testing::MockPath path;
    Offset offset(0.0f, 0.0f);

    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    paintMethod->state_.globalState.SetAlpha(1.0f);
    EXPECT_TRUE(paintMethod->state_.globalState.HasGlobalAlpha());
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor1(Color::BLACK);
    OHOS::Ace::GradientColor gradientColor2(Color::RED);
    gradient.AddColor(gradientColor1);
    gradient.AddColor(gradientColor2);
    paintMethod->state_.strokeState.SetGradient(gradient);
    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->state_.shadow.SetOffset(offset);
    paintMethod->state_.shadow.SetLightRadius(0.5f);
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(brush, SetColor(_)).WillRepeatedly(Return());
    EXPECT_CALL(brush, SetAlphaF(_)).WillRepeatedly(Return());
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    paintMethod->Stroke();
    paintMethod->Path2DStroke();

    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_ATOP);
    paintMethod->state_.strokeState.paintStyle_ = PaintStyle::Color;
    paintMethod->state_.globalState.SetAlpha(-1.0f);
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, SaveLayer(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    paintMethod->Stroke();
    paintMethod->Path2DStroke();
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo014
 * @tc.desc: Test the function 'Fill' and 'Path2DFill' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo014, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Testing::MockCanvas canvas;
    Testing::MockBrush brush;
    Testing::MockPath path;
    Offset offset(0.0f, 0.0f);

    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    paintMethod->state_.globalState.SetAlpha(1.0f);
    EXPECT_TRUE(paintMethod->state_.globalState.HasGlobalAlpha());
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor1(Color::BLACK);
    OHOS::Ace::GradientColor gradientColor2(Color::RED);
    gradient.AddColor(gradientColor1);
    gradient.AddColor(gradientColor2);
    paintMethod->state_.fillState.SetGradient(gradient);
    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->state_.shadow.SetOffset(offset);
    paintMethod->state_.shadow.SetLightRadius(0.5f);
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(brush, SetColor(_)).WillRepeatedly(Return());
    EXPECT_CALL(brush, SetAlphaF(_)).WillRepeatedly(Return());
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    paintMethod->Fill();
    paintMethod->Path2DFill();

    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_ATOP);
    paintMethod->state_.fillState.paintStyle_ = PaintStyle::Color;
    paintMethod->state_.globalState.SetAlpha(-1.0f);
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, SaveLayer(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    paintMethod->Fill();
    paintMethod->Path2DFill();
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo015
 * @tc.desc: Test the function 'Fill' and 'Path2DFill' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo015, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Testing::MockCanvas canvas;
    Testing::MockBrush brush;
    Testing::MockPath path;
    Offset offset(0.0f, 0.0f);

    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    paintMethod->state_.globalState.SetAlpha(1.0f);
    EXPECT_TRUE(paintMethod->state_.globalState.HasGlobalAlpha());
    OHOS::Ace::Pattern pattern;
    void* voidPtr = static_cast<void*>(new char[10]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    pattern.SetPixelMap(pixelMap);
    string src = "ImgSrc";
    pattern.SetImgSrc(src);
    paintMethod->state_.fillState.SetPattern(pattern);
    auto sharedPattern = std::make_shared<OHOS::Ace::Pattern>();
    sharedPattern->SetPixelMap(pixelMap);
    sharedPattern->SetImgSrc(src);
    std::weak_ptr<Ace::Pattern> patternWeak = sharedPattern;
    paintMethod->state_.fillState.SetPatternNG(patternWeak);
    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->state_.shadow.SetOffset(offset);
    paintMethod->state_.shadow.SetLightRadius(0.5f);
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(brush, SetColor(_)).WillRepeatedly(Return());
    EXPECT_CALL(brush, SetAlphaF(_)).WillRepeatedly(Return());
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    paintMethod->Fill();
    paintMethod->Path2DFill();
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo016
 * @tc.desc: Test the function 'StrokeRect', 'Stroke', 'Path2DStroke' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo016, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Rect rect;
    Testing::MockPath path;
    Testing::MockCanvas canvas;
    Offset offset(0.0, 0.0);

    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor1(Color::BLACK);
    OHOS::Ace::GradientColor gradientColor2(Color::RED);
    paintMethod->state_.strokeState.gradient_ = gradient;
    paintMethod->state_.strokeState.gradient_.AddColor(gradientColor1);
    paintMethod->state_.strokeState.gradient_.AddColor(gradientColor2);
    paintMethod->state_.strokeState.paintStyle_ = PaintStyle::Gradient;
    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_OVER);
    paintMethod->state_.shadow.SetOffset(offset);
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    paintMethod->StrokeRect(rect);
    paintMethod->Stroke();
    paintMethod->Path2DStroke();

    paintMethod->state_.globalState.SetType(CompositeOperation::SOURCE_ATOP);
    paintMethod->state_.strokeState.paintStyle_ = PaintStyle::Color;
    EXPECT_CALL(path, AddRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    paintMethod->StrokeRect(rect);
    paintMethod->Stroke();
    paintMethod->Path2DStroke();
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo017
 * @tc.desc: Test the function 'Arc' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo017, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    ArcParam arcParam;
    Testing::MockPath path;

    arcParam.x = 1.0;
    arcParam.y = 1.0;
    arcParam.radius = 1.0;
    arcParam.startAngle = 1.0;
    arcParam.endAngle = 1.0;
    arcParam.anticlockwise = true;
    EXPECT_CALL(path, ArcTo(_, _, _, _)).WillRepeatedly(Return());
    paintMethod->Arc(arcParam);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo018
 * @tc.desc: Test the function 'Ellipse' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo018, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    EllipseParam param;
    Testing::MockPath path;
    Testing::MockMatrix matrix;

    param.x = 1.0;
    param.y = 1.0;
    param.startAngle = 0.0;
    param.endAngle = 1.0;
    param.rotation = 0.0;
    param.anticlockwise = true;
    EXPECT_CALL(matrix, Rotate(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(path, Transform(_)).WillRepeatedly(Return());
    paintMethod->Ellipse(param);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo019
 * @tc.desc: Test the function 'ParsePath2D' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo019, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    PathArgs args;
    Testing::MockPath path;
    RefPtr<CanvasPath2D> path2D = AceType::MakeRefPtr<CanvasPath2D>();

    path2D->caches_.emplace_back(static_cast<PathCmd>(-1), args);
    EXPECT_CALL(path, AddPath(_)).WillRepeatedly(Return());
    paintMethod->ParsePath2D(path2D);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo020
 * @tc.desc: Test the function 'Path2DArc' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo020, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    PathArgs args;
    Testing::MockPath path;

    args.para4 = 0.0;
    args.para5 = 1.0;
    args.para6 = 1.0;
    EXPECT_CALL(path, ArcTo(_, _, _, _)).WillRepeatedly(Return());
    paintMethod->Path2DArc(args);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo021
 * @tc.desc: Test the function 'Path2DEllipse' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo021, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    PathArgs args;
    Testing::MockPath path;
    Testing::MockMatrix matrix;

    args.para5 = 0.0;
    args.para6 = 0.0;
    args.para7 = 1.0;
    EXPECT_CALL(matrix, Rotate(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(path, Transform(_)).WillRepeatedly(Return());
    EXPECT_CALL(path, ArcTo(_, _, _, _)).WillRepeatedly(Return());
    paintMethod->Path2DEllipse(args);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo022
 * @tc.desc: Test the function 'Restore' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo022, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    Testing::MockPath path;

    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    EXPECT_CALL(path, ArcTo(_, _, _, _)).WillRepeatedly(Return());
    paintMethod->Restore();

    paintMethod->rsCanvas_->RestoreToCount(10);
    EXPECT_CALL(path, ArcTo(_, _, _, _)).WillRepeatedly(Return());
    paintMethod->Restore();
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo023
 * @tc.desc: Test the function 'PaintText' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo023, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->paragraph_ = std::make_unique<RSParagraph>();
    paintMethod->rsCanvas_ = std::make_shared<RSCanvas>();
    Testing::MockTypography typography;
    Testing::MockCanvas canvas;

    float width = 0.0f;
    std::optional<double> maxWidth = 0.0;
    EXPECT_CALL(typography, Layout(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Scale(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(typography, Paint(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    paintMethod->PaintText(width, 1.0, 1.0, maxWidth, true);

    EXPECT_CALL(typography, Layout(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Scale(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(typography, Paint(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    paintMethod->PaintText(width, 1.0, 1.0, maxWidth, true);

    maxWidth = 10.0;
    EXPECT_CALL(typography, Layout(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Scale(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(typography, Paint(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    paintMethod->PaintText(width, 1.0, 1.0, maxWidth, true);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo024
 * @tc.desc: Test the function 'GetBaselineOffset' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo024, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    auto paragraph = std::make_unique<RSParagraph>();
    TextBaseline baseLine = static_cast<TextBaseline>(-1);
    auto result = paintMethod->GetBaselineOffset(baseLine, paragraph);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo025
 * @tc.desc: Test the function 'SetFilterParam' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo025, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    paintMethod->SetFilterParam("brightness");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);

    paintMethod->SetBlurFilter("-1px");
    paintMethod->SetFilterParam("blur(10px)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);

    paintMethod->SetBrightnessFilter("A");
    paintMethod->SetFilterParam("brightness(10)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);

    paintMethod->SetContrastFilter(".");
    paintMethod->SetFilterParam("contrast(90)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);
}

/**
 * @tc.name: CanvasCustomPaintMethodTestTwo026
 * @tc.desc: Test the function 'SetFilterParam' of the class 'CustomPaintPaintMethod'.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasCustomPaintMethodTestTwoNg, CanvasCustomPaintMethodTestTwo026, TestSize.Level1)
{
    auto paintMethod = AceType::MakeRefPtr<OffscreenCanvasPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    paintMethod->SetFilterParam("drop-shadow(90)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);

    paintMethod->SetGrayFilter("-1");
    paintMethod->SetFilterParam("grayscale(90)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);

    paintMethod->SetInvertFilter("A");
    paintMethod->SetFilterParam("invert(90)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);

    paintMethod->SetFilterParam("opacity(90)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);

    paintMethod->SetSaturateFilter("A");
    paintMethod->SetFilterParam("saturate(90)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);

    paintMethod->SetSepiaFilter("A");
    paintMethod->SetFilterParam("sepia(90)");
    EXPECT_NE(paintMethod->colorFilter_, nullptr);
}
} // namespace OHOS::Ace::NG
