/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock-actions.h"
#include "gmock/gmock-spec-builders.h"

#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"
#include "core/components_ng/pattern/qrcode/qrcode_paint_method.h"
#include "core/components_ng/pattern/qrcode/qrcode_paint_property.h"
#include "core/components_ng/pattern/qrcode/qrcode_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/rosen/testing_bitmap.h"
#include "core/components_ng/test/mock/rosen/testing_canvas.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string CREATE_VALUE = "Hello World";
const Alignment ALIGNMENT = Alignment::BOTTOM_RIGHT;
constexpr bool SKIP_MEASURE = true;
constexpr bool NO_SKIP_MEASURE = false;
constexpr float ZERO = 0.0f;
constexpr float TEN = 10.0f;
constexpr float CONTAINER_WIDTH = 300.0f;
constexpr float CONTAINER_HEIGHT = 600.0f;
constexpr float QR_CODE_WIDTH = 200.0f;
constexpr float QR_CODE_HEIGHT = 100.0f;
constexpr Color QR_CODE_COLOR_VALUE = Color(0XFFFF0000);
constexpr Color QR_CODE_BACKGROUND_COLOR_VALUE = Color(0XFF0000);
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const OptionalSize<float> PARENT_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const OptionalSize<float> SELF_IDEAL_SIZE_1(QR_CODE_WIDTH, QR_CODE_HEIGHT);
const OptionalSize<float> SELF_IDEAL_SIZE_2(QR_CODE_HEIGHT, QR_CODE_WIDTH);
const uint32_t QR_CODE_VALUE_MAX_LENGTH = 256;
} // namespace

class QRCodePropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: QRCodePaintPropertyTest001
 * @tc.desc: Test qrcode paintProperty.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePaintPropertyTest001, TestSize.Level1)
{
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    qrCodeModelNG.SetQRCodeColor(QR_CODE_COLOR_VALUE);
    qrCodeModelNG.SetQRBackgroundColor(QR_CODE_BACKGROUND_COLOR_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    EXPECT_FALSE(qrcodePaintProperty == nullptr);
    EXPECT_EQ(qrcodePaintProperty->GetValue(), CREATE_VALUE);
    EXPECT_EQ(qrcodePaintProperty->GetColorValue(), QR_CODE_COLOR_VALUE);
    EXPECT_EQ(qrcodePaintProperty->GetBackgroundColorValue(), QR_CODE_BACKGROUND_COLOR_VALUE);
}

/**
 * @tc.name: QRCodePatternTest002
 * @tc.desc:Test pattern of qrcode.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest002, TestSize.Level1)
{
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    qrCodeModelNG.SetQRCodeColor(QR_CODE_COLOR_VALUE);
    qrCodeModelNG.SetQRBackgroundColor(QR_CODE_BACKGROUND_COLOR_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    auto qrcodePattern = frameNode->GetPattern<QRCodePattern>();
    EXPECT_FALSE(qrcodePattern == nullptr);
    auto paintProperty = qrcodePattern->CreatePaintProperty();
    EXPECT_FALSE(paintProperty == nullptr);
    auto layoutAlgorithm = qrcodePattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto paintMethod = qrcodePattern->CreateNodePaintMethod();
    EXPECT_FALSE(paintMethod == nullptr);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    EXPECT_FALSE(qrcodePaintProperty == nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithmWrapper == nullptr);
    auto qrcodeLayoutAlgorithm =
        AceType::DynamicCast<QRCodeLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_FALSE(qrcodeLayoutAlgorithm == nullptr);
}

/**
 * @tc.name: QRCodePatternTest003
 * @tc.desc: Test layout of qrcode wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest003, TestSize.Level1)
{
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    geometryNode->SetMarginFrameOffset(OffsetF(ZERO, ZERO));
    geometryNode->SetContentOffset(OffsetF(ZERO, ZERO));
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_FALSE(frameNode == nullptr);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    EXPECT_FALSE(qrcodePaintProperty == nullptr);
    // update qrcodePaintProperty
    qrcodePaintProperty->UpdateColor(QR_CODE_COLOR_VALUE);
    qrcodePaintProperty->UpdateBackgroundColor(QR_CODE_BACKGROUND_COLOR_VALUE);
    auto qrcodePattern = frameNode->GetPattern<QRCodePattern>();
    EXPECT_FALSE(qrcodePattern == nullptr);
    auto qrcodeLayoutAlgorithm = AceType::DynamicCast<QRCodeLayoutAlgorithm>(qrcodePattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(qrcodeLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(qrcodeLayoutAlgorithm));

    // set contentConstraint
    LayoutConstraintF contentConstraint = LayoutConstraintF();
    contentConstraint.parentIdealSize = PARENT_SIZE;
    contentConstraint.maxSize = CONTAINER_SIZE;
    contentConstraint.minSize = SizeF(ZERO, ZERO);
    contentConstraint.selfIdealSize = (SELF_IDEAL_SIZE_1);
    auto idealSizeFirst = qrcodeLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    geometryNode->SetFrameSize(SizeF(idealSizeFirst->Width(), idealSizeFirst->Width()));
    EXPECT_TRUE(idealSizeFirst->Width() == fmin(QR_CODE_WIDTH, QR_CODE_HEIGHT));

    // update layoutWrapper and contentConstraint
    geometryNode->SetContentOffset(OffsetF(TEN, TEN));
    contentConstraint.UpdateIllegalSelfIdealSizeWithCheck(SELF_IDEAL_SIZE_2);
    auto idealSizeSecond = qrcodeLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_TRUE(idealSizeSecond->Width() == fmin(QR_CODE_WIDTH, QR_CODE_HEIGHT));
}

/**
 * @tc.name: QRCodePatternTest004
 * @tc.desc: Test qrcode pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create qrcode and get frameNode.
     */
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get layoutWrapper and setLayoutAlgorithm.
     * @tc.expected: step2. check qrcodeLayoutAlgorithm is not null.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto qrcodePattern = frameNode->GetPattern<QRCodePattern>();
    EXPECT_FALSE(qrcodePattern == nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. call qrcodePattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    auto qrcodeLayoutAlgorithm = AceType::DynamicCast<QRCodeLayoutAlgorithm>(qrcodePattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(qrcodeLayoutAlgorithm == nullptr);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(qrcodeLayoutAlgorithm, SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(qrcodeLayoutAlgorithm));

    /**
     * @tc.steps: step4. call qrcodePattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step4. OnDirtyLayoutWrapperSwap success and result correct.
     */

    /**
     *     case 1: LayoutWrapper::SkipMeasure = true , skipLayout = true;
     */
    bool first_case = qrcodePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_FALSE(first_case);

    /**
     *     case 2: LayoutWrapper::SkipMeasure = false , skipLayout = false;
     */
    bool second_case = qrcodePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(second_case);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(qrcodeLayoutAlgorithm, NO_SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     *     case 3: LayoutWrapper::SkipMeasure = true , skipLayout = false;
     */
    bool third_case = qrcodePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_TRUE(third_case);

    /**
     *     case 4: LayoutWrapper::SkipMeasure = false , skipLayout = false;
     */
    bool forth_case = qrcodePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(forth_case);
}

/**
 * @tc.name: QRCodePatternTest005
 * @tc.desc: Test qrcode  MeasureContent function.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create qrcode and get frameNode.
     */
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get layoutWrapper and setLayoutAlgorithm.
     * @tc.expected: step2. check qrcodeLayoutAlgorithm is not null.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto qrcodePattern = frameNode->GetPattern<QRCodePattern>();
    EXPECT_FALSE(qrcodePattern == nullptr);
    auto qrcodeLayoutAlgorithm = AceType::DynamicCast<QRCodeLayoutAlgorithm>(qrcodePattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(qrcodeLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(qrcodeLayoutAlgorithm));

    /**
     * @tc.steps: step3. compare qrcodeSize with expected value.
     * @tc.expected: step3. qrcodeSize is the same with expected value.
     */
    LayoutConstraintF layoutConstraintSizeOne;
    layoutConstraintSizeOne.maxSize = CONTAINER_SIZE;
    layoutConstraintSizeOne.selfIdealSize.SetSize(SizeF(QR_CODE_WIDTH, QR_CODE_HEIGHT));
    auto qrcodeSize_One = qrcodeLayoutAlgorithm->MeasureContent(layoutConstraintSizeOne, &layoutWrapper);
    EXPECT_EQ(qrcodeSize_One->Width(), fmin(QR_CODE_WIDTH, QR_CODE_HEIGHT));

    LayoutConstraintF layoutConstraintSizeSecond;
    layoutConstraintSizeSecond.maxSize = CONTAINER_SIZE;
    layoutConstraintSizeSecond.selfIdealSize.SetSize(SizeF(QR_CODE_HEIGHT, QR_CODE_WIDTH));
    auto qrcodeSize_Second = qrcodeLayoutAlgorithm->MeasureContent(layoutConstraintSizeSecond, &layoutWrapper);
    EXPECT_EQ(qrcodeSize_Second->Width(), fmin(QR_CODE_WIDTH, QR_CODE_HEIGHT));
}

/**
 * @tc.name: QRCodePatternTest006
 * @tc.desc: Test qrcode OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create qrcode and get frameNode.
     */
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. create qrcode frameNode, get qrcodePattern.
     * @tc.expected: step2. get qrcodePattern success.
     */
    auto qrcodePattern = AceType::DynamicCast<QRCodePattern>(frameNode->GetPattern());
    EXPECT_FALSE(qrcodePattern == nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    qrcodePattern->OnModifyDone();
    layoutProperty->UpdateAlignment(ALIGNMENT);
    qrcodePattern->OnModifyDone();
    EXPECT_EQ(ALIGNMENT, layoutProperty->GetPositionProperty()->GetAlignmentValue());
}

/**
 * @tc.name: QRCodePatternTest007
 * @tc.desc: Test qrcode PaintMethod GetContentDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create qrcode and get frameNode.
     */
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    // create qrcodePaintMethod
    QRCodePaintMethod qrcodePaintMethod = QRCodePaintMethod(QR_CODE_WIDTH);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    RefPtr<RenderContext> rendercontext;
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(rendercontext, geometryNode, qrcodePaintProperty);
    EXPECT_NE(paintWrapper, nullptr);
    qrcodePaintMethod.GetContentDrawFunction(paintWrapper);
}

/**
 * @tc.name: QRCodePatternTest008
 * @tc.desc: Test qrcode PaintMethod Paint.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create qrcode and get frameNode.
     */
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    qrCodeModelNG.SetQRCodeColor(QR_CODE_COLOR_VALUE);
    qrCodeModelNG.SetQRBackgroundColor(QR_CODE_BACKGROUND_COLOR_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    // create qrcodePaintMethod
    QRCodePaintMethod qrcodePaintMethod = QRCodePaintMethod(QR_CODE_WIDTH);

    /**
     * @tc.steps: step2. get paintWrapper and execute paint method
     * @tc.expected: paintWrapper is not null
     */
    RefPtr<MockRenderContext> renderContext = AceType::DynamicCast<MockRenderContext>(frameNode->renderContext_);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, qrcodePaintProperty);
    EXPECT_NE(paintWrapper, nullptr);
    qrcodePaintMethod.GetContentDrawFunction(paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DrawBitmap(_, _, _)).Times(1);
    qrcodePaintMethod.Paint(rsCanvas, paintWrapper);
}

/**
 * @tc.name: QRCodePaintMethodTest009
 * @tc.desc: Test qrcode PaintMethod Paint while QRCode value is empty.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create qrcode paintMethod.
     */
    RefPtr<RenderContext> renderContext;
    auto qrcodePaintProperty = AceType::MakeRefPtr<QRCodePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, qrcodePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    QRCodePaintMethod qrcodePaintMethod(QR_CODE_WIDTH);

    /**
     * @tc.steps: step2. Call paint method
     * @tc.expected: QRCode value is empty, can't paint
     */
    Testing::MockCanvas rsCanvas;
    qrcodePaintMethod.Paint(rsCanvas, paintWrapper);
    EXPECT_FALSE(qrcodePaintProperty->GetValue().has_value());
}

/**
 * @tc.name: QRCodePaintMethodTest010
 * @tc.desc: Test qrcode PaintMethod Paint ForegroundColor change.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize renderContext and qrcodePaintProperty.
     */
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    renderContext->propForegroundColor_ = Color::BLACK;
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    qrcodePaintProperty->UpdateColor(Color::BLUE);
    std::string value = CREATE_VALUE;
    for (uint32_t i = 0; i <= QR_CODE_VALUE_MAX_LENGTH; i++) {
        value.push_back('a');
    }
    qrcodePaintProperty->UpdateValue(value);

    /**
     * @tc.steps: step2. create qrcode paintMethod.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, qrcodePaintProperty);
    EXPECT_NE(paintWrapper, nullptr);
    QRCodePaintMethod qrcodePaintMethod = QRCodePaintMethod(QR_CODE_WIDTH);

    /**
     * @tc.steps: step3. Call paint method
     * @tc.expected: QrcodePaintProperty's color property set correctly.
     */
    qrcodePaintMethod.qrCodeSize_ = -1;
    Testing::MockCanvas rsCanvas;
    qrcodePaintMethod.Paint(rsCanvas, paintWrapper);
    EXPECT_EQ(qrcodePaintProperty->GetColorValue(), Color::FOREGROUND);

    std::optional<Color> nullColor;
    renderContext->propForegroundColor_ = nullColor;
    renderContext->propForegroundColorStrategy_ =
        std::make_optional<ForegroundColorStrategy>(ForegroundColorStrategy::INVERT);
    paintWrapper->renderContext_ = renderContext;
    qrcodePaintMethod.Paint(rsCanvas, paintWrapper);
    EXPECT_EQ(qrcodePaintProperty->GetColorValue(), Color::FOREGROUND);
}

/**
 * @tc.name: QRCodePaintMethodTest011
 * @tc.desc: Test qrcode PaintMethod Paint ForegroundColor change.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePaintMethodTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create qrcode paintMethod.
     */
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    qrcodePaintProperty->UpdateColor(Color::BLUE);
    qrcodePaintProperty->UpdateValue("");
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    renderContext->propForegroundColor_ = Color::BLACK;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, qrcodePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    QRCodePaintMethod qrcodePaintMethod(QR_CODE_WIDTH);

    /**
     * @tc.steps: step2. Call paint method
     * @tc.expected: RsCanvas method is called.
     */
    Testing::MockCanvas rsCanvas;
    paintWrapper->paintProperty_ = qrcodePaintProperty;
    qrcodePaintMethod.qrCodeSize_ = -1;
    qrcodePaintMethod.Paint(rsCanvas, paintWrapper);
    qrcodePaintMethod.qrCodeSize_ = 2;
    qrcodePaintMethod.Paint(rsCanvas, paintWrapper);
    EXPECT_CALL(rsCanvas, Save()).Times(1).WillOnce(Return());
    EXPECT_CALL(rsCanvas, DrawBitmap(_, _, _)).Times(1).WillOnce(Return());
    EXPECT_CALL(rsCanvas, Restore()).Times(1).WillOnce(Return());
    qrcodePaintMethod.qrCodeSize_ = 50;
    qrcodePaintMethod.Paint(rsCanvas, paintWrapper);
}
} // namespace OHOS::Ace::NG
