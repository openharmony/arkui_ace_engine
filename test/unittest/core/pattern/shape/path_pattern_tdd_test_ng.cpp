/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_resource_adapter_v2.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

#include "core/common/container.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/shape/path_model_ng.h"
#include "core/components_ng/pattern/shape/path_paint_property.h"
#include "core/components_ng/pattern/shape/path_pattern.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/render/drawing_mock.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "base/geometry/ng/size_t.h"
#include "include/core/SkCanvas.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const std::string PATH_CMD = "M150 0 L300 300 L0 300 Z";
constexpr float WIDTH = 200.0f;
constexpr float HEIGHT = 300.0f;
constexpr float TEST_SELF_IDEAL_WIDTH = 500.0f;
constexpr float TEST_SELF_IDEAL_HEIGHT = 600.0f;
constexpr float TEST_CONTENT_WIDTH = 100.0f;
constexpr float TEST_CONTENT_HEIGHT = 100.0f;

// Mock TestingPath returns empty bounds from GetBounds(), making size-dependent
// assertions vacuous. This flag probes whether realistic measurements are available.
static bool g_isRSPathMeasurementAvailable = false;
} // namespace

class PathPatternTddTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        RSPath probePath;
        if (probePath.BuildFromSVGString(PATH_CMD.c_str())) {
            auto bounds = probePath.GetBounds();
            g_isRSPathMeasurementAvailable = (bounds.GetRight() > 0.0f && bounds.GetBottom() > 0.0f);
        }
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: MeasureContent002
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with normal path
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent002, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands(PATH_CMD);
    contentConstraint.selfIdealSize.Reset();
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    if (!g_isRSPathMeasurementAvailable) {
        GTEST_SKIP() << "RSPath mock does not provide realistic path measurements";
    }
    EXPECT_GT(size.value().Width(), 0.0f);
    EXPECT_GT(size.value().Height(), 0.0f);
}

/**
 * @tc.name: MeasureContent003
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with empty commands
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent003, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    contentConstraint.selfIdealSize.Reset();
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: MeasureContent004
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with invalid SVG command
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent004, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands("X");
    contentConstraint.selfIdealSize.Reset();
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: MeasureContent005
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with zero width path
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent005, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands("M0 0 L0 100");
    contentConstraint.selfIdealSize.Reset();
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    if (!g_isRSPathMeasurementAvailable) {
        GTEST_SKIP() << "RSPath mock does not provide realistic path measurements";
    }
    auto expectedLineWidth = paintProperty->GetStrokeWidthValue(Dimension(1, DimensionUnit::PX)).ConvertToPx();
    EXPECT_EQ(size.value().Width(), expectedLineWidth);
    EXPECT_EQ(size.value().Height(), 100.0f);
}

/**
 * @tc.name: MeasureContent006
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with zero height path
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent006, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands("M0 0 L100 0");
    contentConstraint.selfIdealSize.Reset();
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    if (!g_isRSPathMeasurementAvailable) {
        GTEST_SKIP() << "RSPath mock does not provide realistic path measurements";
    }
    EXPECT_EQ(size.value().Width(), 100.0f);
    auto expectedLineWidth = paintProperty->GetStrokeWidthValue(Dimension(1, DimensionUnit::PX)).ConvertToPx();
    EXPECT_EQ(size.value().Height(), expectedLineWidth);
}

/**
 * @tc.name: MeasureContent007
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with propertiesFromAncestor_
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent007, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands("M0 0 L0 100");

    auto ancestorPaintProperty = AceType::MakeRefPtr<ShapePaintProperty>();
    ancestorPaintProperty->UpdateStrokeWidth(Dimension(10.0f));
    auto layoutAlgorithm = AceType::MakeRefPtr<PathLayoutAlgorithm>(ancestorPaintProperty);

    contentConstraint.selfIdealSize.Reset();
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    if (!g_isRSPathMeasurementAvailable) {
        GTEST_SKIP() << "RSPath mock does not provide realistic path measurements";
    }
    auto expectedLineWidth = Dimension(10.0f).ConvertToPx();
    EXPECT_EQ(size.value().Width(), expectedLineWidth);
    EXPECT_EQ(size.value().Height(), 100.0f);
}

/**
 * @tc.name: MeasureContent008
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with width MATCH_PARENT
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent008, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands(PATH_CMD);
    contentConstraint.selfIdealSize.Reset();
    contentConstraint.parentIdealSize = OptionalSizeF(300, 400);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    if (!g_isRSPathMeasurementAvailable) {
        GTEST_SKIP() << "RSPath mock does not provide realistic path measurements";
    }
    EXPECT_EQ(size.value().Width(), 300.0f);
    EXPECT_GT(size.value().Height(), 0.0f);
}

/**
 * @tc.name: MeasureContent009
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with height MATCH_PARENT
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent009, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands(PATH_CMD);
    contentConstraint.selfIdealSize.Reset();
    contentConstraint.parentIdealSize = OptionalSizeF(300, 400);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    if (!g_isRSPathMeasurementAvailable) {
        GTEST_SKIP() << "RSPath mock does not provide realistic path measurements";
    }
    EXPECT_GT(size.value().Width(), 0.0f);
    EXPECT_EQ(size.value().Height(), 400.0f);
}

/**
 * @tc.name: MeasureContent010
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with MATCH_PARENT but no parentIdealSize
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent010, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutConstraintF contentConstraint;
    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);

    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands(PATH_CMD);
    contentConstraint.selfIdealSize.Reset();
    contentConstraint.parentIdealSize.Reset();
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    if (!g_isRSPathMeasurementAvailable) {
        GTEST_SKIP() << "RSPath mock does not provide realistic path measurements";
    }
    EXPECT_GT(size.value().Width(), 0.0f);
    EXPECT_GT(size.value().Height(), 0.0f);
}

/**
 * @tc.name: Measure001
 * @tc.desc: PathLayoutAlgorithm::Measure with null layoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, Measure001, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, nullptr);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(0, 0));
}

/**
 * @tc.name: Measure002
 * @tc.desc: PathLayoutAlgorithm::Measure with no layoutPolicy
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, Measure002, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(WIDTH);
    layoutConstraint.percentReference.SetHeight(HEIGHT);

    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    layoutWrapper.ApplyConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(0, 0));
}

/**
 * @tc.name: Measure003
 * @tc.desc: PathLayoutAlgorithm::Measure with null content
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, Measure003, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(WIDTH);
    layoutConstraint.percentReference.SetHeight(HEIGHT);

    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    layoutWrapper.ApplyConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);

    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(0, 0));
}

/**
 * @tc.name: Measure004
 * @tc.desc: PathLayoutAlgorithm::Measure with IsWidthFix true
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, Measure004, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(WIDTH);
    layoutConstraint.percentReference.SetHeight(HEIGHT);
    layoutConstraint.selfIdealSize.SetWidth(TEST_SELF_IDEAL_WIDTH);
    layoutConstraint.selfIdealSize.SetHeight(TEST_SELF_IDEAL_HEIGHT);

    geometryNode->SetContentSize(SizeF(TEST_CONTENT_WIDTH, TEST_CONTENT_HEIGHT));

    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    layoutWrapper.ApplyConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);

    layoutAlgorithm->Measure(&layoutWrapper);

    EXPECT_EQ(geometryNode->GetFrameSize().Width(), TEST_CONTENT_WIDTH);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), TEST_SELF_IDEAL_HEIGHT);
}

/**
 * @tc.name: Measure005
 * @tc.desc: PathLayoutAlgorithm::Measure with IsHeightFix true
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, Measure005, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(WIDTH);
    layoutConstraint.percentReference.SetHeight(HEIGHT);
    layoutConstraint.selfIdealSize.SetWidth(TEST_SELF_IDEAL_WIDTH);
    layoutConstraint.selfIdealSize.SetHeight(TEST_SELF_IDEAL_HEIGHT);

    geometryNode->SetContentSize(SizeF(TEST_CONTENT_WIDTH, TEST_CONTENT_HEIGHT));

    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    layoutWrapper.ApplyConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);

    layoutAlgorithm->Measure(&layoutWrapper);

    EXPECT_EQ(geometryNode->GetFrameSize().Width(), TEST_SELF_IDEAL_WIDTH);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), TEST_CONTENT_HEIGHT);
}

/**
 * @tc.name: Measure006
 * @tc.desc: PathLayoutAlgorithm::Measure with both IsWidthFix and IsHeightFix true
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, Measure006, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(WIDTH);
    layoutConstraint.percentReference.SetHeight(HEIGHT);
    layoutConstraint.selfIdealSize.SetWidth(TEST_SELF_IDEAL_WIDTH);
    layoutConstraint.selfIdealSize.SetHeight(TEST_SELF_IDEAL_HEIGHT);

    geometryNode->SetContentSize(SizeF(TEST_CONTENT_WIDTH, TEST_CONTENT_HEIGHT));

    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    layoutWrapper.ApplyConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);

    layoutAlgorithm->Measure(&layoutWrapper);

    EXPECT_EQ(geometryNode->GetFrameSize().Width(), TEST_CONTENT_WIDTH);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), TEST_CONTENT_HEIGHT);
}

/**
 * @tc.name: Measure007
 * @tc.desc: PathLayoutAlgorithm::Measure with neither IsWidthFix nor IsHeightFix
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, Measure007, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(WIDTH);
    layoutConstraint.percentReference.SetHeight(HEIGHT);
    layoutConstraint.selfIdealSize.SetWidth(TEST_SELF_IDEAL_WIDTH);
    layoutConstraint.selfIdealSize.SetHeight(TEST_SELF_IDEAL_HEIGHT);

    geometryNode->SetContentSize(SizeF(TEST_CONTENT_WIDTH, TEST_CONTENT_HEIGHT));

    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    layoutWrapper.ApplyConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);

    layoutAlgorithm->Measure(&layoutWrapper);

    EXPECT_EQ(geometryNode->GetFrameSize().Width(), TEST_SELF_IDEAL_WIDTH);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), TEST_SELF_IDEAL_HEIGHT);
}

/**
 * @tc.name: MeasureContent011
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with null layoutProperty in wrapper
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent011, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands(PATH_CMD);

    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize.Reset();

    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, nullptr);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    if (!g_isRSPathMeasurementAvailable) {
        GTEST_SKIP() << "RSPath mock does not provide realistic path measurements";
    }
    EXPECT_GT(size.value().Width(), 0.0f);
    EXPECT_GT(size.value().Height(), 0.0f);
}

/**
 * @tc.name: MeasureContent012
 * @tc.desc: PathLayoutAlgorithm::MeasureContent with no layoutPolicy set
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTddTestNg, MeasureContent012, TestSize.Level1)
{
    PathModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_TRUE(pattern);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_TRUE(layoutProperty);
    auto layoutAlgorithm = AceType::DynamicCast<PathLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(layoutAlgorithm);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands(PATH_CMD);

    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize.Reset();

    auto layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, layoutProperty);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    if (!g_isRSPathMeasurementAvailable) {
        GTEST_SKIP() << "RSPath mock does not provide realistic path measurements";
    }
    EXPECT_GT(size.value().Width(), 0.0f);
    EXPECT_GT(size.value().Height(), 0.0f);
}

} // namespace OHOS::Ace::NG
