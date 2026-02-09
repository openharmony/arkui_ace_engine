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

#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

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
constexpr int32_t ID_COMMANDS = 1000;
constexpr float OPACITY = 0.5f;
constexpr float STROKE_WIDTH = 3.0f;
constexpr bool ANTIALIAS = false;
constexpr float DASHOFFSET = 3.0f;
constexpr std::array<float, 2> STROKE_DASH_ARRAY = { 3, 5 };

} // namespace

class PathPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        frameNode_ = CreateFrameNode();
    }

    RefPtr<FrameNode> CreateFrameNode()
    {
        PathModelNG().Create();
        return AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }

    void SetSize(RefPtr<FrameNode> frameNode) const
    {
        auto width = Dimension(WIDTH);
        auto height = Dimension(HEIGHT);
        ShapeAbstractModelNG::SetWidth(AceType::RawPtr(frameNode), width);
        ShapeAbstractModelNG::SetHeight(AceType::RawPtr(frameNode), height);
    }

    void Draw(RefPtr<FrameNode> frameNode)
    {
        EXPECT_EQ(frameNode == nullptr, false);
        auto pattern = frameNode->GetPattern<PathPattern>();
        EXPECT_EQ(pattern == nullptr, false);
        auto layoutProperty = frameNode->GetLayoutProperty();
        EXPECT_EQ(layoutProperty == nullptr, false);
        auto layoutAlgorithm = AceType::DynamicCast<ShapeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
        EXPECT_EQ(layoutAlgorithm == nullptr, false);
        LayoutConstraintF layoutConstraint;
        layoutConstraint.percentReference.SetWidth(WIDTH);
        layoutConstraint.percentReference.SetHeight(HEIGHT);
        layoutConstraint.selfIdealSize.SetWidth(WIDTH);
        layoutConstraint.selfIdealSize.SetHeight(HEIGHT);
        layoutProperty->UpdateLayoutConstraint(layoutConstraint);
        layoutProperty->UpdateContentConstraint();
        auto size = layoutAlgorithm->MeasureContent(layoutProperty->CreateContentConstraint(), nullptr);
        EXPECT_EQ(size.has_value(), true);
        auto paintMethod = pattern->CreateNodePaintMethod();
        EXPECT_EQ(paintMethod == nullptr, false);
        frameNode->GetGeometryNode()->SetContentSize(size.value());
        auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(frameNode->GetRenderContext(),
            frameNode->GetGeometryNode()->Clone(), frameNode->GetPaintProperty<ShapePaintProperty>());
        EXPECT_EQ(paintWrapper == nullptr, false);
        auto contentDraw = paintMethod->GetContentDrawFunction(AceType::RawPtr(paintWrapper));
        EXPECT_EQ(contentDraw == nullptr, false);
        std::shared_ptr<SkCanvas> canvas = std::make_shared<SkCanvas>();
        Testing::MockCanvas rsCavas(&canvas);
        contentDraw(rsCavas);
    }

protected:
    RefPtr<FrameNode> frameNode_;
};

/**
 * @tc.name: COMMONDS001
 * @tc.desc: create path with cmd
 * @tc.type: FUNC
 */

HWTEST_F(PathPatternTestNg, COMMONDS001, TestSize.Level1)
{
    auto pathModelNG = PathModelNG();
    pathModelNG.Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_EQ(frameNode == nullptr, false);
    pathModelNG.SetCommands(PATH_CMD);
    SetSize(frameNode);
    ViewStackProcessor::GetInstance()->Pop();
    auto pathPaintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    EXPECT_EQ(pathPaintProperty->HasCommands(), true);
    EXPECT_STREQ(pathPaintProperty->GetCommandsValue().c_str(), PATH_CMD.c_str());
    Draw(frameNode);
}

/**
 * @tc.name: COMMONDS002
 * @tc.desc: create path with no cmd
 * @tc.type: FUNC
 */

HWTEST_F(PathPatternTestNg, COMMONDS002, TestSize.Level1)
{
    auto pathModelNG = PathModelNG();
    pathModelNG.Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_EQ(frameNode == nullptr, false);
    SetSize(frameNode);
    ViewStackProcessor::GetInstance()->Pop();
    auto pathPaintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    EXPECT_EQ(pathPaintProperty->HasCommands(), false);
    Draw(frameNode);
}

/**
 * @tc.name: MeasureContent001
 * @tc.desc: PathLayoutAlgorithm::MeasureContent
 * @tc.type: FUNC
 */

HWTEST_F(PathPatternTestNg, MeasureContent001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
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

    /**
     * @tc.steps2: contentConstraint.selfIdealSize is (100, 200)
     * @tc.expected: the return value of MeasureContent is (100, 200)
     */
    contentConstraint.selfIdealSize = OptionalSizeF(100, 200);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(100, 200));
    contentConstraint.selfIdealSize.Reset();

    /**
     * @tc.steps3: Width is Zero and Height is Zero
     * @tc.expected: the return value of MeasureContent is (0, 0)
     */
    auto paintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_TRUE(paintProperty);
    paintProperty->UpdateCommands("M0 0 L0 0");
    size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value(), SizeF(0, 0));
}

/**
 * @tc.name: SetCommands001
 * @tc.desc: PathModelNG::SetCommands
 * @tc.type: FUNC
 */

HWTEST_F(PathPatternTestNg, SetCommands001, TestSize.Level1)
{
    auto pathModelNG = PathModelNG();
    pathModelNG.Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto pathPaintProperty = frameNode->GetPaintProperty<PathPaintProperty>();
    ASSERT_NE(pathPaintProperty, nullptr);
    auto pattern = frameNode->GetPattern<PathPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    pathModelNG.SetCommands(invalidResObj);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pathPaintProperty->HasCommands(), false);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(ID_COMMANDS, PATH_CMD);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        ID_COMMANDS, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    pathModelNG.SetCommands(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pathPaintProperty->HasCommands(), true);
    EXPECT_STREQ(pathPaintProperty->GetCommandsValue().c_str(), PATH_CMD.c_str());

    pathModelNG.SetCommands(resObjWithString);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    EXPECT_NE(pattern->resourceMgr_->resMap_.size(), 0);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: PaintFill001
 * @tc.desc: set fill and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintFill001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetFill(AceType::RawPtr(frameNode_), Color::RED);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasFill());
    EXPECT_EQ(shapeProperty->GetFillValue(), Color::RED);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintFill002
 * @tc.desc: set no fill and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintFill002, TestSize.Level1)
{
    SetSize(frameNode_);
    // Default behavior - no explicit fill set
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasFill());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintFillOpacity001
 * @tc.desc: set fill opacity and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintFillOpacity001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetFillOpacity(AceType::RawPtr(frameNode_), OPACITY);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasFillOpacity());
    EXPECT_FLOAT_EQ(shapeProperty->GetFillOpacityValue(), OPACITY);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintFillOpacity002
 * @tc.desc: set no fill opacity and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintFillOpacity002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasFillOpacity());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStroke001
 * @tc.desc: set stroke and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintStroke001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStroke(AceType::RawPtr(frameNode_), Color::RED);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStroke());
    EXPECT_EQ(shapeProperty->GetStrokeValue(), Color::RED);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStroke002
 * @tc.desc: set no stroke and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintStroke002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStroke());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintAntiAlias001
 * @tc.desc: set antialias and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintAntiAlias001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetAntiAlias(AceType::RawPtr(frameNode_), ANTIALIAS);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasAntiAlias());
    EXPECT_EQ(shapeProperty->GetAntiAliasValue(), ANTIALIAS);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintAntiAlias002
 * @tc.desc: set no antialias and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintAntiAlias002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasAntiAlias());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeWidth001
 * @tc.desc: set stroke width and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintStrokeWidth001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStrokeWidth(AceType::RawPtr(frameNode_), Dimension(STROKE_WIDTH));
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeWidth());
    EXPECT_FLOAT_EQ(shapeProperty->GetStrokeWidthValue().ConvertToPx(), STROKE_WIDTH);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeWidth002
 * @tc.desc: set no stroke width and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintStrokeWidth002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeWidth());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeOpacity001
 * @tc.desc: set stroke opacity and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintStrokeOpacity001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStrokeOpacity(AceType::RawPtr(frameNode_), OPACITY);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeOpacity());
    EXPECT_FLOAT_EQ(shapeProperty->GetStrokeOpacityValue(), OPACITY);
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeOpacity002
 * @tc.desc: set no stroke opacity and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintStrokeOpacity002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeOpacity());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeDashArray001
 * @tc.desc: set dash Array and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintStrokeDashArray001, TestSize.Level1)
{
    SetSize(frameNode_);
    auto len = static_cast<int32_t>(STROKE_DASH_ARRAY.size());
    std::vector<Dimension> strokeDashArray(len);
    for (int32_t i = 0; i < len; i++) {
        strokeDashArray[i] = Dimension(STROKE_DASH_ARRAY.at(i));
    }
    ShapeModelNG::SetStrokeDashArray(AceType::RawPtr(frameNode_), strokeDashArray);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeDashArray());
    EXPECT_EQ(shapeProperty->GetStrokeDashArrayValue().size(), STROKE_DASH_ARRAY.size());
    const std::vector<Dimension> propStrokeDashArray = shapeProperty->GetStrokeDashArrayValue();
    auto propLen = static_cast<int32_t>(propStrokeDashArray.size());
    for (int32_t i = 0; i < propLen; i++) {
        EXPECT_FLOAT_EQ(propStrokeDashArray[i].ConvertToPx(), STROKE_DASH_ARRAY.at(i));
    }
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeDashArray002
 * @tc.desc: set no dash Array and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintStrokeDashArray002, TestSize.Level1)
{
    SetSize(frameNode_);
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_FALSE(shapeProperty->HasStrokeDashArray());
    Draw(frameNode_);
}

/**
 * @tc.name: PaintStrokeDashOffset001
 * @tc.desc: set stroke dash offset and check
 * @tc.type: FUNC
 */
HWTEST_F(PathPatternTestNg, PaintStrokeDashOffset001, TestSize.Level1)
{
    SetSize(frameNode_);
    ShapeModelNG::SetStrokeDashOffset(AceType::RawPtr(frameNode_), Dimension(DASHOFFSET));
    ViewStackProcessor::GetInstance()->Pop();

    auto shapeProperty = frameNode_->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapeProperty, nullptr);
    EXPECT_TRUE(shapeProperty->HasStrokeDashOffset());
    EXPECT_FLOAT_EQ(shapeProperty->GetStrokeDashOffset()->ConvertToPx(), DASHOFFSET);
    Draw(frameNode_);
}

} // namespace OHOS::Ace::NG
