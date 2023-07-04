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

#include <optional>

#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "test/mock/core/common/mock_container.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/custom_paint/canvas_model_ng.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_event_hub.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_layout_algorithm.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_pattern.h"
#include "core/components_ng/test/pattern/custom_paint/common_constants.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_interface.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class CustomPaintPatternTestNg : public testing::Test {
public:
    // Create the pointer of the class CustomPaintPattern
    static RefPtr<CustomPaintPattern> CreateCustomPaintPattern();
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

RefPtr<CustomPaintPattern> CustomPaintPatternTestNg::CreateCustomPaintPattern()
{
    ContainerScope scope(DEFAULT_INSTANCE_ID);
    RefPtr<PipelineBase> pipelineContext = AceType::MakeRefPtr<MockPipelineBase>();
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(pipelineContext);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    CanvasModelNG CanvasModelNG;
    return AceType::DynamicCast<CustomPaintPattern>(CanvasModelNG.Create());
}

void CustomPaintPatternTestNg::SetUpTestCase()
{
    GTEST_LOG_(INFO) << "CustomPaintPatternTestNg SetUpTestCase";
}

void CustomPaintPatternTestNg::TearDownTestCase()
{
    GTEST_LOG_(INFO) << "CustomPaintPatternTestNg TearDownTestCase";
}

void CustomPaintPatternTestNg::SetUp()
{
    GTEST_LOG_(INFO) << "CustomPaintPatternTestNg SetUp";
}

void CustomPaintPatternTestNg::TearDown()
{
    GTEST_LOG_(INFO) << "CustomPaintPatternTestNg TearDown";
}

/**
 * @tc.name: CustomPaintPatternTestNg001
 * @tc.desc: Test onReady event.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<CustomPaintEventHub>();
    ASSERT_NE(eventHub, nullptr);
    // The flag used to determine whether the event callback function executed successfully.
    bool flagEventCbk = false;

    /**
     * @tc.steps2: Set the onReadEvent as null and call the function FireReadyEvent.
     * @tc.expected: The value of flagEventCbk is false.
     */
    // Set the onReadEvent as nullptr, the value of flagEventCbk keep false always.
    CanvasModelNG CanvasModelNG;
    CanvasModelNG.SetOnReady([](uint32_t) {});
    eventHub->FireReadyEvent();
    EXPECT_FALSE(flagEventCbk);

    /**
     * @tc.steps3: Set the onReadEvent as the function which changes the value of flagEventCbk.
     * @tc.expected: The value of flagEventCbk will be modified to false.
     */
    CanvasModelNG.SetOnReady([&flagEventCbk](uint32_t) { flagEventCbk = true; });
    eventHub->FireReadyEvent();
    EXPECT_TRUE(flagEventCbk);
}

/**
 * @tc.name: CustomPaintPatternTestNg002
 * @tc.desc: Test the MeasureContent function with different layoutWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutAlgorithm = customPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps2: Call the function MeasureContent without the ideal size.
     * @tc.expected: The return value is equal to MAX_SIZE.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    auto canvasSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(canvasSize.value_or(SizeF(0.0f, 0.0f)), MAX_SIZE);

    /**
     * @tc.steps3: Call the function MeasureContent with the ideal size.
     * @tc.expected: The return value is equal to IDEAL_SIZE.
     */
    layoutConstraint.selfIdealSize.SetSize(IDEAL_SIZE);
    canvasSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(canvasSize.value_or(SizeF(0.0f, 0.0f)), IDEAL_SIZE);
}

/**
 * @tc.name: CustomPaintPatternTestNg003
 * @tc.desc: Test attributes of the object customPattern.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = customPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
}

/**
 * @tc.name: CustomPaintPatternTestNg004
 * @tc.desc: Test functions about MeasureText of the class CustomPaintPattern.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Call the function SetLineDash and SetLineDashOffset.
     * @tc.expected: The value of GetLineDash().dashOffset is equal to DEFAULT_DOUBLE10.
     *               The value of GetLineDash().lineDash is equal to CANDIDATE_DOUBLES.
     */
    paintMethod->SetLineDash(CANDIDATE_DOUBLES);
    paintMethod->SetLineDashOffset(DEFAULT_DOUBLE10);
    EXPECT_DOUBLE_EQ(customPattern->GetLineDash().dashOffset, DEFAULT_DOUBLE10);
    for (uint32_t i = 1; i < CANDIDATE_DOUBLES.size(); ++i) {
        auto lineDash = paintMethod->strokeState_.GetLineDash();
        EXPECT_DOUBLE_EQ(lineDash.lineDash[i], CANDIDATE_DOUBLES[i]);
    }

    /**
     * @tc.steps3: Call the function ToDataURL.
     * @tc.expected: The return value is beginning with the corresponding type obtained from the input string.
     */
    std::string result = customPattern->ToDataURL(IMAGE_PNG);
    EXPECT_EQ(result.substr(URL_PREFIX.size(), IMAGE_PNG.size()), IMAGE_PNG);
    // Make sure entering the first if-branch
    customPattern->Save();
    result = customPattern->ToDataURL(IMAGE_PNG);
    EXPECT_EQ(result.substr(URL_PREFIX.size(), IMAGE_PNG.size()), IMAGE_PNG);

    /**
     * @tc.steps4: Call the function SetCanvasSize with IDEAL_SIZE.
     * @tc.expected: The return value of GetWidth and GetHeight are equal to the corresponding value of IDEAL_SIZE.
     */
    customPattern->SetCanvasSize(IDEAL_SIZE);
    EXPECT_DOUBLE_EQ(customPattern->GetWidth(), IDEAL_WIDTH);
    EXPECT_DOUBLE_EQ(customPattern->GetHeight(), IDEAL_HEIGHT);
}

/**
 * @tc.name: CustomPaintPatternTestNg005
 * @tc.desc: Test functions about GetImageData of the class CustomPaintPattern.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: Make sure entering the first if-branch.
     */
    CanvasModelNG CanvasModelNG;
    auto customPattern = AceType::DynamicCast<CustomPaintPattern>(CanvasModelNG.Create());
    ASSERT_NE(customPattern, nullptr);

    /**
     * @tc.steps2: Call the function GetImageData.
     * @tc.expected: The dirtyWidth and dirtyHeight of the return value are equal to the input value.
     */
    auto imageData = customPattern->GetImageData(DEFAULT_DOUBLE1, DEFAULT_DOUBLE1, DEFAULT_DOUBLE1, DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(imageData->dirtyWidth, DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(imageData->dirtyHeight, DEFAULT_DOUBLE1);

    /**
     * @tc.steps3: initialize parameters.
     * @tc.expected: Make sure ignore the first if-branch.
     */
    auto customPattern1 = CreateCustomPaintPattern();
    ASSERT_NE(customPattern1, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern1->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps4: Call the function GetImageData.
     * @tc.expected: The dirtyWidth and dirtyHeight of the return value are equal to the input value.
     */
    customPattern1->Save(); // Make sure entering the second if-branch
    auto imageData1 = customPattern1->GetImageData(DEFAULT_DOUBLE1, DEFAULT_DOUBLE1, DEFAULT_DOUBLE1, DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(imageData1->dirtyWidth, DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(imageData1->dirtyHeight, DEFAULT_DOUBLE1);
}

/**
 * @tc.name: CustomPaintPatternTestNg006
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about text.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    customPattern->FillText(DEFAULT_STR, DEFAULT_DOUBLE0, DEFAULT_DOUBLE0, std::optional<double>(0));
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->StrokeText(DEFAULT_STR, DEFAULT_DOUBLE0, DEFAULT_DOUBLE0, std::optional<double>(0));
    EXPECT_TRUE(paintMethod->HasTask());

    TextAlign textAlign = TextAlign::CENTER;
    paintMethod->tasks_.clear();
    customPattern->UpdateTextAlign(textAlign);
    EXPECT_TRUE(paintMethod->HasTask());

    TextBaseline textBaseline = TextBaseline::ALPHABETIC;
    paintMethod->tasks_.clear();
    customPattern->UpdateTextBaseline(textBaseline);
    EXPECT_TRUE(paintMethod->HasTask());

    FontWeight weight = FontWeight::BOLD;
    paintMethod->tasks_.clear();
    customPattern->UpdateFontWeight(weight);
    EXPECT_TRUE(paintMethod->HasTask());

    FontStyle style = FontStyle::ITALIC;
    paintMethod->tasks_.clear();
    customPattern->UpdateFontStyle(style);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->UpdateFontFamilies(FONT_FAMILY);
    EXPECT_TRUE(paintMethod->HasTask());

    Dimension size;
    paintMethod->tasks_.clear();
    customPattern->UpdateFontSize(size);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg007
 * @tc.desc: Test functions about TransformParam.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about TransformParam.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    TransformParam param;
    customPattern->SetTransform(param);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->ResetTransform();
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->Transform(param);
    EXPECT_TRUE(paintMethod->HasTask());

    customPattern->Scale(DEFAULT_DOUBLE0, DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->Translate(DEFAULT_DOUBLE0, DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->Rotate(DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg008
 * @tc.desc: Test functions about Rect.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about Rect.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    Rect rect;
    customPattern->FillRect(rect);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->StrokeRect(rect);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->ClearRect(rect);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->AddRect(rect);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg09
 * @tc.desc: Test functions about Shadow.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg09, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about Shadow.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    Color color = Color::BLACK;
    customPattern->UpdateShadowColor(color);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->UpdateShadowBlur(DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->UpdateShadowOffsetX(DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->UpdateShadowOffsetY(DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg010
 * @tc.desc: Test functions about Stroke.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about Stroke.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    RefPtr<CanvasPath2D> path = AceType::MakeRefPtr<CanvasPath2D>();
    customPattern->Stroke(path);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->Stroke();
    EXPECT_TRUE(paintMethod->HasTask());

    std::shared_ptr<Ace::Pattern> pattern = std::make_shared<Ace::Pattern>();
    paintMethod->tasks_.clear();
    customPattern->UpdateStrokePattern(pattern);
    EXPECT_TRUE(paintMethod->HasTask());

    Color color = Color::BLACK;
    paintMethod->tasks_.clear();
    customPattern->UpdateStrokeColor(color);
    EXPECT_TRUE(paintMethod->HasTask());

    Ace::Gradient gradient;
    paintMethod->tasks_.clear();
    customPattern->UpdateStrokeGradient(gradient);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg011
 * @tc.desc: Test functions about path.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about path.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    RefPtr<CanvasPath2D> path = AceType::MakeRefPtr<CanvasPath2D>();
    customPattern->Stroke(path);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->Stroke();
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->Fill();
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->Fill(path);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->Clip();
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->Clip(path);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->BeginPath();
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->ClosePath();
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg012
 * @tc.desc: Test functions about line.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about path.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    customPattern->LineTo(DEFAULT_DOUBLE1, DEFAULT_DOUBLE10);
    EXPECT_TRUE(paintMethod->HasTask());

    LineCapStyle lineCapStyle = LineCapStyle::BUTT;
    paintMethod->tasks_.clear();
    customPattern->UpdateLineCap(lineCapStyle);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->UpdateLineDashOffset(DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->UpdateLineDash(CANDIDATE_DOUBLES);
    EXPECT_TRUE(paintMethod->HasTask());

    LineJoinStyle LineJoinStyle = LineJoinStyle::BEVEL;
    paintMethod->tasks_.clear();
    customPattern->UpdateLineJoin(LineJoinStyle);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->UpdateLineWidth(DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg013
 * @tc.desc: Test functions about updating parameters.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about updating parameters.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    CompositeOperation compositeOperation = CompositeOperation::SOURCE_OVER;
    customPattern->UpdateCompositeOperation(compositeOperation);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->UpdateGlobalAlpha(DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->UpdateMiterLimit(DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    Color color;
    paintMethod->tasks_.clear();
    customPattern->UpdateFillColor(color);
    EXPECT_TRUE(paintMethod->HasTask());

    Ace::Gradient gradient;
    paintMethod->tasks_.clear();
    customPattern->UpdateFillGradient(gradient);
    EXPECT_TRUE(paintMethod->HasTask());

    std::shared_ptr<Ace::Pattern> pattern = std::make_shared<Ace::Pattern>();
    paintMethod->tasks_.clear();
    customPattern->UpdateFillPattern(pattern);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg014
 * @tc.desc: Test functions about image.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about image.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    Ace::CanvasImage canvasImage;
    customPattern->DrawImage(canvasImage, DEFAULT_DOUBLE0, DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    RefPtr<PixelMap> pixelMap(nullptr);
    paintMethod->tasks_.clear();
    customPattern->DrawPixelMap(pixelMap, canvasImage);
    EXPECT_TRUE(paintMethod->HasTask());

    Ace::ImageData imageData;
    paintMethod->tasks_.clear();
    customPattern->PutImageData(imageData);
    EXPECT_TRUE(paintMethod->HasTask());

    RefPtr<OffscreenCanvasPattern> offscreenCanvasPattern;
    paintMethod->tasks_.clear();
    customPattern->TransferFromImageBitmap(offscreenCanvasPattern);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg015
 * @tc.desc: Test functions about curve.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about curve.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    ArcParam arcParam;
    customPattern->Arc(arcParam);
    EXPECT_TRUE(paintMethod->HasTask());

    ArcToParam arcToParam;
    paintMethod->tasks_.clear();
    customPattern->ArcTo(arcToParam);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->MoveTo(DEFAULT_DOUBLE1, DEFAULT_DOUBLE1);
    EXPECT_TRUE(paintMethod->HasTask());

    EllipseParam ellipseParam;
    paintMethod->tasks_.clear();
    customPattern->Ellipse(ellipseParam);
    EXPECT_TRUE(paintMethod->HasTask());

    BezierCurveParam bezierCurveParam;
    paintMethod->tasks_.clear();
    customPattern->BezierCurveTo(bezierCurveParam);
    EXPECT_TRUE(paintMethod->HasTask());

    QuadraticCurveParam quadraticCurveParam;
    paintMethod->tasks_.clear();
    customPattern->QuadraticCurveTo(quadraticCurveParam);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg016
 * @tc.desc: Test functions about CanvasFillRule.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(customPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about CanvasFillRule.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    CanvasFillRule rule = CanvasFillRule::NONZERO;
    customPattern->UpdateFillRuleForPath(rule);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    customPattern->UpdateFillRuleForPath2D(rule);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CustomPaintPatternTestNg017
 * @tc.desc: Test functions about canvas lifecycle OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(CustomPaintPatternTestNg, CustomPaintPatternTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customPattern = CreateCustomPaintPattern();
    ASSERT_NE(customPattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutAlgorithm = customPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto dirty = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    dirty->skipMeasureContent_ = false;
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm);

    /**
     * @tc.steps2: Test functions about canvas lifecycle (onReady and onAreaChange) with OnDirtyLayoutWrapperSwap.
     * @tc.expected: The result.
     */
    DirtySwapConfig config;
    EXPECT_TRUE(customPattern->OnDirtyLayoutWrapperSwap(dirty, config));

    config.frameOffsetChange = true;
    EXPECT_FALSE(customPattern->OnDirtyLayoutWrapperSwap(dirty, config));

    config.contentOffsetChange = true;
    EXPECT_FALSE(customPattern->OnDirtyLayoutWrapperSwap(dirty, config));

    config.frameOffsetChange = false;
    EXPECT_FALSE(customPattern->OnDirtyLayoutWrapperSwap(dirty, config));
}

} // namespace OHOS::Ace::NG
