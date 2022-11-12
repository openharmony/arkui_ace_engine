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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/test/unittest/image/image_test_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/flex/wrap_layout_algorithm.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"
#include "core/components_ng/pattern/qrcode/qrcode_paint_property.h"
#include "core/components_ng/pattern/qrcode/qrcode_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string CREATE_VALUE = "Hello World";
constexpr Color QR_CODE_COLOR_VALUE = Color(0XFFFF0000);
constexpr Color QR_CODE_BACKGROUND_COLOR_VALUE = Color(0XFF0000);
const float ZERO = 0.0f;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 600.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const float QR_CODE_WIDTH = 200.0f;
const float QR_CODE_HEIGHT = 100.0f;
const OptionalSize<float> PARENT_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const OptionalSize<float> SELF_IDEAL_SIZE_1(QR_CODE_WIDTH, QR_CODE_HEIGHT);
const OptionalSize<float> SELF_IDEAL_SIZE_2(QR_CODE_HEIGHT, QR_CODE_WIDTH);
} // namespace

class QRCodePropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: QRCodePaintPropertyTest001
 * @tc.desc: Set QRCode value into QRCodePaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePaintPropertyTest001, TestSize.Level1)
{
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    EXPECT_FALSE(qrcodePaintProperty == nullptr);
    EXPECT_EQ(qrcodePaintProperty->GetValue(), CREATE_VALUE);
}

/**
 * @tc.name: QRCodePaintPropertyTest002
 * @tc.desc: Set QRCodeColor value into QRCodePaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePaintPropertyTest002, TestSize.Level1)
{
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    qrCodeModelNG.SetQRCodeColor(QR_CODE_COLOR_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    EXPECT_FALSE(qrcodePaintProperty == nullptr);
    EXPECT_EQ(qrcodePaintProperty->GetColorValue(), QR_CODE_COLOR_VALUE);
}

/**
 * @tc.name: QRCodePaintPropertyTest003
 * @tc.desc: Set QRCode bgColor value into QRCodePaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePaintPropertyTest003, TestSize.Level1)
{
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    qrCodeModelNG.SetQRBackgroundColor(QR_CODE_BACKGROUND_COLOR_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    EXPECT_FALSE(qrcodePaintProperty == nullptr);
    EXPECT_EQ(qrcodePaintProperty->GetBackgroundColorValue(), QR_CODE_BACKGROUND_COLOR_VALUE);
}

/**
 * @tc.name: QRCodePatternTest004
 * @tc.desc:Test pattern of qrcode.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest004, TestSize.Level1)
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
 * @tc.name: QRCodePatternTest005
 * @tc.desc: Test layout of qrcode wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest005, TestSize.Level1)
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
    contentConstraint.UpdateIllegalSelfIdealSizeWithCheck(SELF_IDEAL_SIZE_2);
    auto idealSizeSecond = qrcodeLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_TRUE(idealSizeSecond->Width() == fmin(QR_CODE_WIDTH, QR_CODE_HEIGHT));
}

/**
 * @tc.name: QRCodePatternTest006
 * @tc.desc: Test paint of qrcode wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodePropertyTestNg, QRCodePatternTest006, TestSize.Level1)
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
    auto paintMethod = qrcodePattern->CreateNodePaintMethod();
    EXPECT_FALSE(paintMethod == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(qrcodeLayoutAlgorithm));

    // set contentConstraint
    LayoutConstraintF contentConstraint = LayoutConstraintF();
    contentConstraint.parentIdealSize = PARENT_SIZE;
    contentConstraint.maxSize = CONTAINER_SIZE;
    contentConstraint.minSize = SizeF(ZERO, ZERO);
    contentConstraint.selfIdealSize = SELF_IDEAL_SIZE_1;

    auto idealSize = qrcodeLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    geometryNode->SetFrameSize(SizeF(idealSize->Width(), idealSize->Width()));
    geometryNode->SetContentSize(SizeF(idealSize->Width(), idealSize->Width()));
    EXPECT_TRUE(idealSize->Width() == fmin(QR_CODE_WIDTH, QR_CODE_HEIGHT));

    auto renderContext = frameNode->GetRenderContext();
    EXPECT_FALSE(renderContext == nullptr);
    auto paintWrapper = PaintWrapper(renderContext, geometryNode, qrcodePaintProperty);
    paintMethod->GetContentDrawFunction(&paintWrapper);
    EXPECT_TRUE(paintWrapper.GetContentSize().Width() == fmin(QR_CODE_WIDTH, QR_CODE_HEIGHT));
    EXPECT_TRUE(paintWrapper.GetContentOffset() == OffsetF(ZERO, ZERO));
}

} // namespace OHOS::Ace::NG