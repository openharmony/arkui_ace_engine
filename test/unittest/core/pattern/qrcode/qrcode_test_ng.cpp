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

#include "gmock/gmock-actions.h"
#include "gmock/gmock-spec-builders.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_bitmap.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"
#include "core/components_ng/pattern/qrcode/qrcode_paint_method.h"
#include "core/components_ng/pattern/qrcode/qrcode_paint_property.h"
#include "core/components_ng/pattern/qrcode/qrcode_pattern.h"
#include "core/components/theme/app_theme.h"

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
const uint32_t QR_CODE_VALUE_MAX_LENGTH_NEW = 512;
constexpr int32_t PLATFORM_VERSION_10 = 10;
constexpr int32_t PLATFORM_VERSION_11 = 11;
const Dimension DEFAULT_SIZE(240.0, DimensionUnit::VP);
} // namespace

class QRCodeTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void QRCodeTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_QRCODE);
    auto qrcodeTheme = QrcodeTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(qrcodeTheme));
    EXPECT_CALL(*themeManager, GetTheme(AppTheme::TypeId())).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
}

void QRCodeTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: QRCodePaintPropertyTest001
 * @tc.desc: Test qrcode paintProperty.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodePaintPropertyTest001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);

    /**
     * @tc.cases: case. cover more than APIVersion 10.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
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
 * @tc.name: QRCodePaintPropertyTest002
 * @tc.desc: Test qrcode paintProperty.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodePaintPropertyTest002, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);

    /**
     * @tc.cases: case. cover more than APIVersion 10.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    qrCodeModelNG.SetQRCodeColor(AceType::RawPtr(frameNode), QR_CODE_COLOR_VALUE);
    qrCodeModelNG.SetQRBackgroundColor(AceType::RawPtr(frameNode), QR_CODE_BACKGROUND_COLOR_VALUE);
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
HWTEST_F(QRCodeTestNg, QRCodePatternTest002, TestSize.Level1)
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
HWTEST_F(QRCodeTestNg, QRCodePatternTest003, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_10);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    geometryNode->SetMarginFrameOffset(OffsetF(ZERO, ZERO));
    geometryNode->SetContentOffset(OffsetF(ZERO, ZERO));
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
HWTEST_F(QRCodeTestNg, QRCodePatternTest004, TestSize.Level1)
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
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
     *     case 1: LayoutWrapperNode::SkipMeasure = true , skipLayout = true;
     */
    bool first_case = qrcodePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true);
    EXPECT_FALSE(first_case);

    /**
     *     case 2: LayoutWrapperNode::SkipMeasure = false , skipLayout = false;
     */
    bool second_case = qrcodePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(second_case);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(qrcodeLayoutAlgorithm, NO_SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     *     case 3: LayoutWrapperNode::SkipMeasure = true , skipLayout = false;
     */
    bool third_case = qrcodePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_TRUE(third_case);

    /**
     *     case 4: LayoutWrapperNode::SkipMeasure = false , skipLayout = false;
     */
    bool forth_case = qrcodePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(forth_case);
}

/**
 * @tc.name: QRCodePatternTest005
 * @tc.desc: Test qrcode  MeasureContent function.
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodePatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create qrcode and get frameNode.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_10);
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
HWTEST_F(QRCodeTestNg, QRCodePatternTest006, TestSize.Level1)
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
 * @tc.desc: Test qrcode OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodePatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    RefPtr<QrcodeTheme> qrCodeTheme = pipeline->GetTheme<QrcodeTheme>();
    ASSERT_NE(qrCodeTheme, nullptr);
    qrCodeModelNG.SetQRCodeColor(QR_CODE_COLOR_VALUE);
    qrCodeModelNG.SetContentOpacity(0.1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    ASSERT_NE(qrcodePaintProperty, nullptr);
    EXPECT_EQ(qrcodePaintProperty->GetOpacityValue(), 0.1);
    auto qrcodePattern = AceType::DynamicCast<QRCodePattern>(frameNode->GetPattern());
    EXPECT_FALSE(qrcodePattern == nullptr);

    /**
     * @tc.steps: steps2. GetDumpInfo
     * @tc.expected: steps2. Check the result of DumpInfo
     */
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    qrcodePattern->DumpInfo();
    qrcodePattern->DumpInfo(json);
    EXPECT_EQ(qrcodePaintProperty->GetColorValue(Color::TRANSPARENT).ColorToString(), "#FFFF0000");
    EXPECT_EQ(std::to_string(qrcodePaintProperty->GetOpacityValue(1.0f)), "0.100000");
    EXPECT_EQ(qrcodePaintProperty->GetValueValue(" "), CREATE_VALUE);
}

/**
 * @tc.name: QRCodeModelSetContentOpacity001
 * @tc.desc: test SetContentOpacity
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodeModelSetContentOpacity001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    RefPtr<QrcodeTheme> qrCodeTheme = pipeline->GetTheme<QrcodeTheme>();
    ASSERT_NE(qrCodeTheme, nullptr);

    /**
     * @tc.steps: steps2. SetContentOpacity
     * @tc.expected: steps2. Check the result of SetContentOpacity
     */
    qrCodeModelNG.SetContentOpacity(0.1);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode1, nullptr);
    auto qrcodePaintProperty1 = frameNode1->GetPaintProperty<QRCodePaintProperty>();
    ASSERT_NE(qrcodePaintProperty1, nullptr);
    EXPECT_EQ(qrcodePaintProperty1->GetOpacityValue(), 0.1);

    qrCodeModelNG.Create(CREATE_VALUE);
    qrCodeModelNG.SetQRCodeColor(qrCodeTheme->GetQrcodeColor());
    qrCodeModelNG.SetContentOpacity(1);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto qrcodePaintProperty2 = frameNode2->GetPaintProperty<QRCodePaintProperty>();
    ASSERT_NE(qrcodePaintProperty2, nullptr);
    EXPECT_EQ(qrcodePaintProperty2->GetColorValue().GetValue(), qrCodeTheme->GetQrcodeColor().GetValue());
}

/**
 * @tc.name: QRCodePatternGetFocusPattern001
 * @tc.desc: test GetFocusPattern
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodePatternGetFocusPattern001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto qrCodePattern = frameNode->GetPattern<QRCodePattern>();
    ASSERT_NE(qrCodePattern, nullptr);

    /**
     * @tc.steps: steps2. GetFocusPattern
     * @tc.expected: steps2. Check the result of GetFocusPattern
     */
    auto focusPattern = qrCodePattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.focusType_, FocusType::NODE);
    EXPECT_EQ(focusPattern.focusable_, true);
    EXPECT_EQ(focusPattern.styleType_, FocusStyleType::INNER_BORDER);
}

/**
 * @tc.name: QRCodeLayoutAlgorithmMeasureContent001
 * @tc.desc: test MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodeLayoutAlgorithmMeasureContent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    PaddingProperty padding;
    padding.left = CalcLength(200.0_vp);
    padding.right = CalcLength(200.0_vp);
    padding.top = CalcLength(200.0_vp);
    padding.bottom = CalcLength(200.0_vp);
    layoutProperty->UpdatePadding(padding);
    LayoutWrapperNode layoutWrapper(frameNode, nullptr, layoutProperty);
    auto qrCodePattern = frameNode->GetPattern<QRCodePattern>();
    ASSERT_NE(qrCodePattern, nullptr);
    auto qrCodeLayoutAlgorithm = AceType::DynamicCast<QRCodeLayoutAlgorithm>(qrCodePattern->CreateLayoutAlgorithm());
    ASSERT_NE(qrCodeLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(qrCodeLayoutAlgorithm));

    /**
     * @tc.steps: steps2. MeasureContent
     * @tc.expected: steps2. Check the result of MeasureContent
     */
    LayoutConstraintF contentConstraint;
    auto size = qrCodeLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size->Width(), 0.0f);
    contentConstraint.selfIdealSize.SetWidth(20.0f);
    contentConstraint.selfIdealSize.SetHeight(20.0f);
    auto size1 = qrCodeLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1->Width(), 20.0f);
    contentConstraint.parentIdealSize = PARENT_SIZE;
    contentConstraint.maxSize = CONTAINER_SIZE;
    contentConstraint.minSize = SizeF(ZERO, ZERO);
    OptionalSize<float> selfIdealSize1(200.0f, 200.0f);
    contentConstraint.selfIdealSize = (selfIdealSize1);
    auto size2 = qrCodeLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size2, std::nullopt);
    EXPECT_EQ(size2->Height(), 200.0f);
}

/**
 * @tc.name: QRCodeLayoutAlgorithmMeasureContent002
 * @tc.desc: test MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodeLayoutAlgorithmMeasureContent002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    LayoutWrapperNode layoutWrapper(frameNode, nullptr, layoutProperty);
    auto qrCodePattern = frameNode->GetPattern<QRCodePattern>();
    ASSERT_NE(qrCodePattern, nullptr);
    auto qrCodeLayoutAlgorithm = AceType::DynamicCast<QRCodeLayoutAlgorithm>(qrCodePattern->CreateLayoutAlgorithm());
    ASSERT_NE(qrCodeLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(qrCodeLayoutAlgorithm));

    /**
     * @tc.steps: steps2. construct arguments and call MeasureContent().
     * @tc.expected: cover branch not padding and Negative is false. Check the result of MeasureContent.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize.SetWidth(-20.0f);
    contentConstraint.selfIdealSize.SetHeight(-20.0f);
    auto size1 = qrCodeLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1->Width(), -20.0f);
}

/**
 * @tc.name: QRCodeModifierOnDraw001
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodeModifierOnDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto qrCodePattern = frameNode->GetPattern<QRCodePattern>();
    ASSERT_NE(qrCodePattern, nullptr);
    auto qrCodePaintMethod = AceType::DynamicCast<QRCodePaintMethod>(qrCodePattern->CreateNodePaintMethod());
    ASSERT_NE(qrCodePaintMethod, nullptr);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    qrcodePaintProperty->UpdateColor(Color::BLUE);
    qrcodePaintProperty->UpdateValue(CREATE_VALUE);
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    renderContext->propForegroundColor_ = Color::BLUE;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, qrcodePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).Times(1).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).Times(1).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(1).WillOnce(Return());
    EXPECT_CALL(rsCanvas, Scale(_, _)).Times(1).WillOnce(Return());
    EXPECT_CALL(rsCanvas, DrawImage(_, _, _, _)).Times(1).WillOnce(Return());
    EXPECT_CALL(rsCanvas, Restore()).Times(1).WillOnce(Return());
    DrawingContext context = { rsCanvas, 10.0f, 10.0f };
    qrCodePaintMethod->qrCodeSize_ = 100.0f;

    /**
     * @tc.steps: steps2. onDraw
     * @tc.expected: steps2. Check the result of onDraw
     */
    qrCodePaintMethod->UpdateContentModifier(paintWrapper);
    auto qrCodeModifier = AceType::DynamicCast<QRCodeModifier>(qrCodePaintMethod->GetContentModifier(paintWrapper));
    qrCodeModifier->onDraw(context);
    EXPECT_EQ(qrCodeModifier->color_->Get(), Color::BLUE);
}

/**
 * @tc.name: QRCodeModifierOnDraw002
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodeModifierOnDraw002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto qrCodePattern = frameNode->GetPattern<QRCodePattern>();
    ASSERT_NE(qrCodePattern, nullptr);
    auto qrCodePaintMethod = AceType::DynamicCast<QRCodePaintMethod>(qrCodePattern->CreateNodePaintMethod());
    ASSERT_NE(qrCodePaintMethod, nullptr);
    std::string value = CREATE_VALUE;
    for (uint32_t i = 0; i <= QR_CODE_VALUE_MAX_LENGTH; i++) {
        value.push_back('a');
    }
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    qrcodePaintProperty->UpdateColor(Color::BLUE);
    qrcodePaintProperty->UpdateValue(value);
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    renderContext->propForegroundColor_ = Color::RED;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, qrcodePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    Testing::MockCanvas rsCanvas;
    DrawingContext context = { rsCanvas, 10.0f, 10.0f };

    /**
     * @tc.steps: steps2. onDraw
     * @tc.expected: steps2. Check the result of onDraw
     */
    qrCodePaintMethod->UpdateContentModifier(paintWrapper);
    auto qrCodeModifier = AceType::DynamicCast<QRCodeModifier>(qrCodePaintMethod->GetContentModifier(paintWrapper));
    qrCodeModifier->onDraw(context);
    EXPECT_EQ(qrCodeModifier->color_->Get(), Color::FOREGROUND);
}

/**
 * @tc.name: UpdateContentModifier001
 * @tc.desc: test qrcodePaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, UpdateContentModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto qrCodePattern = frameNode->GetPattern<QRCodePattern>();
    ASSERT_NE(qrCodePattern, nullptr);

    /**
     * @tc.steps: steps2. Create qrCodePaintMethod and paintWrapper
     */
    auto qrCodePaintMethod = AceType::DynamicCast<QRCodePaintMethod>(qrCodePattern->CreateNodePaintMethod());
    ASSERT_NE(qrCodePaintMethod, nullptr);
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy::INVERT);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, qrcodePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: steps3. Call UpdateContentModifier
     * @tc.expected: Call UpdateContentModifier and cover branch HasForegroundColorStrategy is true
     */
    qrCodePaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_TRUE(renderContext->HasForegroundColorStrategy());

    /**
     * @tc.steps: steps4. Call UpdateContentModifier
     * @tc.expected: Call UpdateContentModifier and cover branch HasForegroundColorStrategy、HasForegroundColor is false
     */
    auto renderContext2 = AceType::MakeRefPtr<MockRenderContext>();
    auto* paintWrapper2 = new PaintWrapper(renderContext2, geometryNode, qrcodePaintProperty);
    ASSERT_NE(paintWrapper2, nullptr);
    qrCodePaintMethod->UpdateContentModifier(paintWrapper2);
    EXPECT_FALSE(renderContext2->HasForegroundColor());
}

/**
 * @tc.name: QRCodeModelNG001
 * @tc.desc: test QRCodeModelNG static Method
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodeModelNG001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto frameNode = QRCodeModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode, nullptr);

    QRCodeModelNG::SetQRCodeValue(AceType::RawPtr(frameNode), CREATE_VALUE);
    auto property = frameNode->GetPaintProperty<QRCodePaintProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetValueValue(), CREATE_VALUE);
}
/**
 * @tc.name: QRCodeModifierTest001
 * @tc.desc: test modifier
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodeModifierTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create LoadingProgressModifier pointer.
     */
    auto qrcodeModifier = AceType::MakeRefPtr<QRCodeModifier>();
    /**
     * @tc.step: step2. reset opacity_.
     * @tc.expected: opacity_ is nullptr.
     */
    qrcodeModifier->SetQRCodeOpacity(ZERO);
    qrcodeModifier->opacity_.Reset();
    EXPECT_EQ(qrcodeModifier->opacity_, nullptr);
    qrcodeModifier->SetQRCodeOpacity(ZERO);
    EXPECT_EQ(qrcodeModifier->opacity_, nullptr);
    /**
     * @tc.step: step3. reset qrCodeSize_.
     * @tc.expected: qrCodeSize_ is nullptr.
     */
    qrcodeModifier->SetQRCodeSize(ZERO);
    qrcodeModifier->qrCodeSize_.Reset();
    EXPECT_EQ(qrcodeModifier->qrCodeSize_, nullptr);
    qrcodeModifier->SetQRCodeSize(ZERO);
    EXPECT_EQ(qrcodeModifier->qrCodeSize_, nullptr);
    /**
     * @tc.step: step4. reset value_.
     * @tc.expected: value_ is nullptr.
     */
    qrcodeModifier->SetQRCodeValue(CREATE_VALUE);
    qrcodeModifier->value_.Reset();
    EXPECT_EQ(qrcodeModifier->value_, nullptr);
    qrcodeModifier->SetQRCodeValue(CREATE_VALUE);
    EXPECT_EQ(qrcodeModifier->value_, nullptr);
    /**
     * @tc.step: step5. reset paintOffset_.
     * @tc.expected: paintOffset_ is nullptr.
     */
    qrcodeModifier->SetPaintOffset(OffsetF(ZERO, ZERO));
    qrcodeModifier->paintOffset_.Reset();
    EXPECT_EQ(qrcodeModifier->paintOffset_, nullptr);
    qrcodeModifier->SetPaintOffset(OffsetF(ZERO, ZERO));
    EXPECT_EQ(qrcodeModifier->paintOffset_, nullptr);
    /**
     * @tc.step: step6. reset color_.
     * @tc.expected: color_ is nullptr.
     */
    qrcodeModifier->SetQRCodeColor(QR_CODE_COLOR_VALUE);
    qrcodeModifier->color_.Reset();
    EXPECT_EQ(qrcodeModifier->color_, nullptr);
    qrcodeModifier->SetQRCodeColor(QR_CODE_COLOR_VALUE);
    EXPECT_EQ(qrcodeModifier->color_, nullptr);
    /**
     * @tc.step: step7. reset backgroundColor_.
     * @tc.expected: backgroundColor_ is nullptr.
     */
    qrcodeModifier->SetQRCodeBackgroundColor(QR_CODE_BACKGROUND_COLOR_VALUE);
    qrcodeModifier->backgroundColor_.Reset();
    EXPECT_EQ(qrcodeModifier->backgroundColor_, nullptr);
    qrcodeModifier->SetQRCodeBackgroundColor(QR_CODE_BACKGROUND_COLOR_VALUE);
    EXPECT_EQ(qrcodeModifier->backgroundColor_, nullptr);
}

/*
 * @tc.name: QRCodeLayoutAlgorithmMeasureContent003
 * @tc.desc: test MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodeLayoutAlgorithmMeasureContent003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    RefPtr<QrcodeTheme> qrCodeTheme = pipeline->GetTheme<QrcodeTheme>();
    ASSERT_NE(qrCodeTheme, nullptr);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    LayoutWrapperNode layoutWrapper(frameNode, nullptr, layoutProperty);
    auto qrCodePattern = frameNode->GetPattern<QRCodePattern>();
    ASSERT_NE(qrCodePattern, nullptr);
    auto qrCodeLayoutAlgorithm = AceType::DynamicCast<QRCodeLayoutAlgorithm>(qrCodePattern->CreateLayoutAlgorithm());
    ASSERT_NE(qrCodeLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(qrCodeLayoutAlgorithm));

    /**
     * @tc.steps: steps2. construct arguments and call MeasureContent().
     * @tc.expected: cover branch not padding and Negative is false. Check the result of MeasureContent.
     */
    LayoutConstraintF contentConstraint;
    qrCodeTheme->qrcodeDefaultSize_ = DEFAULT_SIZE;
    auto size1 = qrCodeLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1->Width(), 240.0f);
}

/**
 * @tc.name: QRCodeMaxLengthTest1
 * @tc.desc: test modifier
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodeMaxLengthTest1, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto qrCodePattern = frameNode->GetPattern<QRCodePattern>();
    ASSERT_NE(qrCodePattern, nullptr);
    auto qrCodePaintMethod = AceType::DynamicCast<QRCodePaintMethod>(qrCodePattern->CreateNodePaintMethod());
    ASSERT_NE(qrCodePaintMethod, nullptr);
    std::string value = CREATE_VALUE;
    for (uint32_t i = 0; i <= 600; i++) {
        value.push_back('a');
    }
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    qrcodePaintProperty->UpdateValue(value);
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, qrcodePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: steps2. check the length of qrCodeValue
     * @tc.expected: steps2. the the length of qrCodeValue is 512
     */
    qrCodePaintMethod->UpdateContentModifier(paintWrapper);
    auto qrCodeModifier = AceType::DynamicCast<QRCodeModifier>(qrCodePaintMethod->GetContentModifier(paintWrapper));
    auto qrcodeLength = qrCodeModifier->value_->Get().length();
    EXPECT_EQ(qrcodeLength, QR_CODE_VALUE_MAX_LENGTH_NEW);
}

/**
 * @tc.name: QRCodeMaxLengthTest2
 * @tc.desc: test modifier
 * @tc.type: FUNC
 */
HWTEST_F(QRCodeTestNg, QRCodeMaxLengthTest2, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create qrCodeModel
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    QRCodeModelNG qrCodeModelNG;
    qrCodeModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto qrCodePattern = frameNode->GetPattern<QRCodePattern>();
    ASSERT_NE(qrCodePattern, nullptr);
    auto qrCodePaintMethod = AceType::DynamicCast<QRCodePaintMethod>(qrCodePattern->CreateNodePaintMethod());
    ASSERT_NE(qrCodePaintMethod, nullptr);
    std::string value = CREATE_VALUE;
    for (uint32_t i = 0; i < 300; i++) {
        value.push_back('a');
    }
    auto qrcodePaintProperty = frameNode->GetPaintProperty<QRCodePaintProperty>();
    qrcodePaintProperty->UpdateValue(value);
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, qrcodePaintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: steps2. check the length of qrCodeValue
     * @tc.expected: steps2. the the length of qrCodeValue can over 256
     */
    qrCodePaintMethod->UpdateContentModifier(paintWrapper);
    auto qrCodeModifier = AceType::DynamicCast<QRCodeModifier>(qrCodePaintMethod->GetContentModifier(paintWrapper));
    auto qrcodeLength = qrCodeModifier->value_->Get().length();
    EXPECT_EQ(qrcodeLength, 311);
}
} // namespace OHOS::Ace::NG
