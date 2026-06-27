/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/geometry/dimension.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_static.h"
#include "core/components_ng/pattern/shape/shape_model_static.h"
#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/common/container.h"
#include "test/mock/frameworks/base/image/mock_pixel_map.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float TEST_WIDTH_VALUE = 200.0f;
constexpr float TEST_HEIGHT_VALUE = 300.0f;
constexpr double TEST_DASH_OFFSET_LPX_VALUE = 10.0;
constexpr double TEST_DASH_OFFSET_VP_VALUE = 5.0;
constexpr double TEST_OPACITY_VALUE = 0.5;
constexpr float ZERO_DIMENSION_VALUE = 0.0f;
constexpr float NEGATIVE_DIMENSION_VALUE = -10.0f;
constexpr int32_t TEST_LINE_CAP_ROUND = 1;
constexpr int32_t TEST_LINE_JOIN_ROUND = 1;
constexpr double TEST_MITER_LIMIT_VALUE = 5.0;
constexpr double TEST_FILL_OPACITY_VALUE = 0.8;
constexpr bool TEST_ANTIALIAS_TRUE = true;
constexpr bool TEST_ANTIALIAS_FALSE = false;
constexpr int32_t TEST_NODE_ID_A = 200;
constexpr int32_t TEST_NODE_ID_B = 201;
constexpr int32_t TEST_API_VERSION_14 = static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN);
constexpr int32_t TEST_API_VERSION_13 = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);

RefPtr<ShapePaintProperty> GetShapePaintProp(const RefPtr<FrameNode>& frameNode)
{
    EXPECT_NE(frameNode, nullptr);
    return frameNode->GetPaintProperty<ShapePaintProperty>();
}

void VerifyLayoutWidthSet(const RefPtr<FrameNode>& frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto&& constraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(constraint, nullptr);
    ASSERT_TRUE(constraint->selfIdealSize.has_value());
    EXPECT_TRUE(constraint->selfIdealSize->Width().has_value());
}

void VerifyLayoutHeightSet(const RefPtr<FrameNode>& frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto&& constraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(constraint, nullptr);
    ASSERT_TRUE(constraint->selfIdealSize.has_value());
    EXPECT_TRUE(constraint->selfIdealSize->Height().has_value());
}

void VerifyLayoutWidthCleared(const RefPtr<FrameNode>& frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto&& constraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_TRUE(constraint && constraint->selfIdealSize.has_value());
    EXPECT_FALSE(constraint->selfIdealSize->Width().has_value());
}

void VerifyLayoutHeightCleared(const RefPtr<FrameNode>& frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto&& constraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_TRUE(constraint && constraint->selfIdealSize.has_value());
    EXPECT_FALSE(constraint->selfIdealSize->Height().has_value());
}

void VerifyLayoutWidthNonZero(const RefPtr<FrameNode>& frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto&& constraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(constraint, nullptr);
    ASSERT_TRUE(constraint->selfIdealSize.has_value());
    ASSERT_TRUE(constraint->selfIdealSize->Width().has_value());
    EXPECT_GT(constraint->selfIdealSize->Width().value().GetDimension().Value(), ZERO_DIMENSION_VALUE);
}

void VerifyLayoutHeightNonZero(const RefPtr<FrameNode>& frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto&& constraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(constraint, nullptr);
    ASSERT_TRUE(constraint->selfIdealSize.has_value());
    ASSERT_TRUE(constraint->selfIdealSize->Height().has_value());
    EXPECT_GT(constraint->selfIdealSize->Height().value().GetDimension().Value(), ZERO_DIMENSION_VALUE);
}
} // namespace

class ShapeAbstractModelStaticTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    void TearDown() override
    {
        auto* stack = ViewStackProcessor::GetInstance();
        if (stack->GetMainFrameNode()) {
            stack->Pop();
        }
    }

    RefPtr<FrameNode> CreateNode(int32_t nodeId)
    {
        return CircleModelNG::CreateFrameNode(nodeId);
    }

    RefPtr<FrameNode> CreateContainerNode()
    {
        auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
        auto frameNode = FrameNode::GetOrCreateFrameNode(
            V2::SHAPE_CONTAINER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ShapeContainerPattern>(); });
        return frameNode;
    }
};

// ==================== SetWidth ====================

/**
 * @tc.name: SetWidth_PositiveDimension
 * @tc.desc: SetWidth with positive optional dimension sets width without clamping
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetWidth_PositiveDimension, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetWidth(AceType::RawPtr(frameNode), Dimension(TEST_WIDTH_VALUE));
    VerifyLayoutWidthSet(frameNode);
}

/**
 * @tc.name: SetWidth_ZeroDimension
 * @tc.desc: SetWidth with zero optional dimension clamps value to zero via LessNotEqual branch
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetWidth_ZeroDimension, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetWidth(AceType::RawPtr(frameNode), Dimension(ZERO_DIMENSION_VALUE));
    VerifyLayoutWidthSet(frameNode);
}

/**
 * @tc.name: SetWidth_NegativeDimension
 * @tc.desc: SetWidth with negative optional dimension clamps value to zero via LessNotEqual branch
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetWidth_NegativeDimension, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetWidth(AceType::RawPtr(frameNode), Dimension(NEGATIVE_DIMENSION_VALUE));
    VerifyLayoutWidthSet(frameNode);
}

/**
 * @tc.name: SetWidth_Nullopt
 * @tc.desc: SetWidth with nullopt calls ClearWidthOrHeight to reset width
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetWidth_Nullopt, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetWidth(AceType::RawPtr(frameNode), Dimension(TEST_WIDTH_VALUE));
    ShapeAbstractModelStatic::SetWidth(AceType::RawPtr(frameNode), std::nullopt);
    VerifyLayoutWidthCleared(frameNode);
}

/**
 * @tc.name: SetWidth_NullFrameNode
 * @tc.desc: SetWidth with null FrameNode triggers CHECK_NULL_VOID early return in ViewAbstract
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetWidth_NullFrameNode, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_B);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetWidth(nullptr, Dimension(TEST_WIDTH_VALUE));
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr ||
                !layoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
}

/**
 * @tc.name: SetWidth_NulloptThenPositive
 * @tc.desc: SetWidth clears then re-sets width, verifying both branches in sequence
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetWidth_NulloptThenPositive, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetWidth(AceType::RawPtr(frameNode), Dimension(TEST_WIDTH_VALUE));
    ShapeAbstractModelStatic::SetWidth(AceType::RawPtr(frameNode), std::nullopt);
    VerifyLayoutWidthCleared(frameNode);
    ShapeAbstractModelStatic::SetWidth(AceType::RawPtr(frameNode), Dimension(TEST_WIDTH_VALUE));
    VerifyLayoutWidthNonZero(frameNode);
}

// ==================== SetHeight ====================

/**
 * @tc.name: SetHeight_PositiveDimension
 * @tc.desc: SetHeight with positive optional dimension sets height without clamping
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetHeight_PositiveDimension, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetHeight(AceType::RawPtr(frameNode), Dimension(TEST_HEIGHT_VALUE));
    VerifyLayoutHeightSet(frameNode);
}

/**
 * @tc.name: SetHeight_ZeroDimension
 * @tc.desc: SetHeight with zero optional dimension clamps value to zero via LessNotEqual branch
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetHeight_ZeroDimension, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetHeight(AceType::RawPtr(frameNode), Dimension(ZERO_DIMENSION_VALUE));
    VerifyLayoutHeightSet(frameNode);
}

/**
 * @tc.name: SetHeight_NegativeDimension
 * @tc.desc: SetHeight with negative optional dimension clamps value to zero via LessNotEqual branch
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetHeight_NegativeDimension, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetHeight(AceType::RawPtr(frameNode), Dimension(NEGATIVE_DIMENSION_VALUE));
    VerifyLayoutHeightSet(frameNode);
}

/**
 * @tc.name: SetHeight_Nullopt
 * @tc.desc: SetHeight with nullopt calls ClearWidthOrHeight to reset height
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetHeight_Nullopt, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetHeight(AceType::RawPtr(frameNode), Dimension(TEST_HEIGHT_VALUE));
    ShapeAbstractModelStatic::SetHeight(AceType::RawPtr(frameNode), std::nullopt);
    VerifyLayoutHeightCleared(frameNode);
}

/**
 * @tc.name: SetHeight_NullFrameNode
 * @tc.desc: SetHeight with null FrameNode triggers CHECK_NULL_VOID early return in ViewAbstract
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetHeight_NullFrameNode, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_B);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetHeight(nullptr, Dimension(TEST_HEIGHT_VALUE));
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_TRUE(layoutProperty->GetCalcLayoutConstraint() == nullptr ||
                !layoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
}

/**
 * @tc.name: SetHeight_NulloptThenPositive
 * @tc.desc: SetHeight clears then re-sets height, verifying both branches in sequence
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetHeight_NulloptThenPositive, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetHeight(AceType::RawPtr(frameNode), Dimension(TEST_HEIGHT_VALUE));
    ShapeAbstractModelStatic::SetHeight(AceType::RawPtr(frameNode), std::nullopt);
    VerifyLayoutHeightCleared(frameNode);
    ShapeAbstractModelStatic::SetHeight(AceType::RawPtr(frameNode), Dimension(TEST_HEIGHT_VALUE));
    VerifyLayoutHeightNonZero(frameNode);
}

// ==================== SetStrokeDashOffset ====================

/**
 * @tc.name: SetStrokeDashOffset_LpxUnit
 * @tc.desc: SetStrokeDashOffset with LPX unit registers the LPX attribute on the frame node
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeDashOffset_LpxUnit, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeDashOffset(
        AceType::RawPtr(frameNode), Dimension(TEST_DASH_OFFSET_LPX_VALUE, DimensionUnit::LPX));
    auto paintProperty = GetShapePaintProp(frameNode);
    EXPECT_TRUE(paintProperty->HasStrokeDashOffset());
    EXPECT_EQ(paintProperty->GetStrokeDashOffsetValue().Value(), TEST_DASH_OFFSET_LPX_VALUE);
    EXPECT_EQ(paintProperty->GetStrokeDashOffsetValue().Unit(), DimensionUnit::LPX);
}

/**
 * @tc.name: SetStrokeDashOffset_VpUnit
 * @tc.desc: SetStrokeDashOffset with VP unit unregisters the LPX attribute on the frame node
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeDashOffset_VpUnit, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeDashOffset(
        AceType::RawPtr(frameNode), Dimension(TEST_DASH_OFFSET_VP_VALUE, DimensionUnit::VP));
    auto paintProperty = GetShapePaintProp(frameNode);
    EXPECT_TRUE(paintProperty->HasStrokeDashOffset());
    EXPECT_EQ(paintProperty->GetStrokeDashOffsetValue().Value(), TEST_DASH_OFFSET_VP_VALUE);
    EXPECT_EQ(paintProperty->GetStrokeDashOffsetValue().Unit(), DimensionUnit::VP);
}

/**
 * @tc.name: SetStrokeDashOffset_NullFrameNode
 * @tc.desc: SetStrokeDashOffset with null FrameNode triggers CHECK_NULL_VOID early return and no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeDashOffset_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateNode(TEST_NODE_ID_B);
    ASSERT_NE(observerNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeDashOffset(
        nullptr, Dimension(TEST_DASH_OFFSET_VP_VALUE));
    auto paintProperty = GetShapePaintProp(observerNode);
    EXPECT_FALSE(paintProperty->HasStrokeDashOffset());
}

// ==================== SetStrokeLineCap ====================

/**
 * @tc.name: SetStrokeLineCap_ValidNode
 * @tc.desc: SetStrokeLineCap updates stroke line cap on the frame node's paint property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeLineCap_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeLineCap(AceType::RawPtr(frameNode), TEST_LINE_CAP_ROUND);
    auto paintProperty = GetShapePaintProp(frameNode);
    EXPECT_TRUE(paintProperty->HasStrokeLineCap());
    EXPECT_EQ(paintProperty->GetStrokeLineCapValue(), TEST_LINE_CAP_ROUND);
}

/**
 * @tc.name: SetStrokeLineCap_NullFrameNode
 * @tc.desc: SetStrokeLineCap with null FrameNode triggers early return, no property change
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeLineCap_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateNode(TEST_NODE_ID_B);
    ASSERT_NE(observerNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeLineCap(nullptr, TEST_LINE_CAP_ROUND);
    auto paintProperty = GetShapePaintProp(observerNode);
    EXPECT_FALSE(paintProperty->HasStrokeLineCap());
}

// ==================== SetStrokeLineJoin ====================

/**
 * @tc.name: SetStrokeLineJoin_ValidNode
 * @tc.desc: SetStrokeLineJoin updates stroke line join on the frame node's paint property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeLineJoin_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeLineJoin(AceType::RawPtr(frameNode), TEST_LINE_JOIN_ROUND);
    auto paintProperty = GetShapePaintProp(frameNode);
    EXPECT_TRUE(paintProperty->HasStrokeLineJoin());
    EXPECT_EQ(paintProperty->GetStrokeLineJoinValue(), TEST_LINE_JOIN_ROUND);
}

/**
 * @tc.name: SetStrokeLineJoin_NullFrameNode
 * @tc.desc: SetStrokeLineJoin with null FrameNode triggers early return, no property change
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeLineJoin_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateNode(TEST_NODE_ID_B);
    ASSERT_NE(observerNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeLineJoin(nullptr, TEST_LINE_JOIN_ROUND);
    auto paintProperty = GetShapePaintProp(observerNode);
    EXPECT_FALSE(paintProperty->HasStrokeLineJoin());
}

// ==================== SetStrokeMiterLimit ====================

/**
 * @tc.name: SetStrokeMiterLimit_ValidNode
 * @tc.desc: SetStrokeMiterLimit updates stroke miter limit on the frame node's paint property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeMiterLimit_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeMiterLimit(AceType::RawPtr(frameNode), TEST_MITER_LIMIT_VALUE);
    auto paintProperty = GetShapePaintProp(frameNode);
    EXPECT_TRUE(paintProperty->HasStrokeMiterLimit());
    EXPECT_NEAR(paintProperty->GetStrokeMiterLimitValue(), TEST_MITER_LIMIT_VALUE, 0.001);
}

/**
 * @tc.name: SetStrokeMiterLimit_NullFrameNode
 * @tc.desc: SetStrokeMiterLimit with null FrameNode triggers early return, no property change
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeMiterLimit_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateNode(TEST_NODE_ID_B);
    ASSERT_NE(observerNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeMiterLimit(nullptr, TEST_MITER_LIMIT_VALUE);
    auto paintProperty = GetShapePaintProp(observerNode);
    EXPECT_FALSE(paintProperty->HasStrokeMiterLimit());
}

// ==================== SetStrokeOpacity ====================

/**
 * @tc.name: SetStrokeOpacity_ValidNode
 * @tc.desc: SetStrokeOpacity updates stroke opacity on the frame node's paint property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeOpacity_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeOpacity(AceType::RawPtr(frameNode), TEST_OPACITY_VALUE);
    auto paintProperty = GetShapePaintProp(frameNode);
    EXPECT_TRUE(paintProperty->HasStrokeOpacity());
    EXPECT_NEAR(paintProperty->GetStrokeOpacityValue(), TEST_OPACITY_VALUE, 0.001);
}

/**
 * @tc.name: SetStrokeOpacity_NullFrameNode
 * @tc.desc: SetStrokeOpacity with null FrameNode triggers early return, no property change
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetStrokeOpacity_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateNode(TEST_NODE_ID_B);
    ASSERT_NE(observerNode, nullptr);
    ShapeAbstractModelStatic::SetStrokeOpacity(nullptr, TEST_OPACITY_VALUE);
    auto paintProperty = GetShapePaintProp(observerNode);
    EXPECT_FALSE(paintProperty->HasStrokeOpacity());
}

// ==================== SetFillOpacity ====================

/**
 * @tc.name: SetFillOpacity_ValidNode
 * @tc.desc: SetFillOpacity updates fill opacity on the frame node's paint property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetFillOpacity_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetFillOpacity(AceType::RawPtr(frameNode), TEST_FILL_OPACITY_VALUE);
    auto paintProperty = GetShapePaintProp(frameNode);
    EXPECT_TRUE(paintProperty->HasFillOpacity());
    EXPECT_NEAR(paintProperty->GetFillOpacityValue(), TEST_FILL_OPACITY_VALUE, 0.001);
}

/**
 * @tc.name: SetFillOpacity_NullFrameNode
 * @tc.desc: SetFillOpacity with null FrameNode triggers early return, no property change
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetFillOpacity_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateNode(TEST_NODE_ID_B);
    ASSERT_NE(observerNode, nullptr);
    ShapeAbstractModelStatic::SetFillOpacity(nullptr, TEST_FILL_OPACITY_VALUE);
    auto paintProperty = GetShapePaintProp(observerNode);
    EXPECT_FALSE(paintProperty->HasFillOpacity());
}

// ==================== SetAntiAlias ====================

/**
 * @tc.name: SetAntiAlias_ValidNode
 * @tc.desc: SetAntiAlias updates anti-alias on the frame node's paint property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetAntiAlias_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetAntiAlias(AceType::RawPtr(frameNode), TEST_ANTIALIAS_FALSE);
    auto paintProperty = GetShapePaintProp(frameNode);
    EXPECT_TRUE(paintProperty->HasAntiAlias());
    EXPECT_EQ(paintProperty->GetAntiAliasValue(), TEST_ANTIALIAS_FALSE);
}

/**
 * @tc.name: SetAntiAlias_NullFrameNode
 * @tc.desc: SetAntiAlias with null FrameNode triggers early return, no property change
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetAntiAlias_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateNode(TEST_NODE_ID_B);
    ASSERT_NE(observerNode, nullptr);
    ShapeAbstractModelStatic::SetAntiAlias(nullptr, TEST_ANTIALIAS_TRUE);
    auto paintProperty = GetShapePaintProp(observerNode);
    EXPECT_FALSE(paintProperty->HasAntiAlias());
}

/**
 * @tc.name: SetAntiAlias_ToggleValue
 * @tc.desc: SetAntiAlias toggles between true and false, verifying the property updates correctly
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, SetAntiAlias_ToggleValue, TestSize.Level1)
{
    auto frameNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(frameNode, nullptr);
    ShapeAbstractModelStatic::SetAntiAlias(AceType::RawPtr(frameNode), TEST_ANTIALIAS_TRUE);
    auto paintProperty = GetShapePaintProp(frameNode);
    EXPECT_TRUE(paintProperty->GetAntiAliasValue());
    ShapeAbstractModelStatic::SetAntiAlias(AceType::RawPtr(frameNode), TEST_ANTIALIAS_FALSE);
    EXPECT_FALSE(paintProperty->GetAntiAliasValue());
}

// ==================== InitBox ====================

/**
 * @tc.name: InitBox_API14Plus_UpdatesPixelMapInfo
 * @tc.desc: InitBox with API >= 14 and valid ShapeContainer node updates PixelMapInfo from pixMap
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, InitBox_API14Plus_UpdatesPixelMapInfo, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(14);
    auto containerNode = CreateContainerNode();
    ASSERT_NE(containerNode, nullptr);
    auto paintProperty = containerNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_FALSE(paintProperty->HasPixelMapInfo());

    ShapeModelStatic::InitBox(AceType::RawPtr(containerNode), mockPixelMap);

    EXPECT_TRUE(paintProperty->HasPixelMapInfo());
    AceApplicationInfo::GetInstance().SetApiTargetVersion(0);
}

/**
 * @tc.name: InitBox_BelowAPI14_NoPixelMapInfoUpdate
 * @tc.desc: InitBox with API < 14 returns early, PixelMapInfo is not set on the paint property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, InitBox_BelowAPI14_NoPixelMapInfoUpdate, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(TEST_API_VERSION_13);
    auto containerNode = CreateContainerNode();
    ASSERT_NE(containerNode, nullptr);
    auto paintProperty = containerNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_FALSE(paintProperty->HasPixelMapInfo());

    ShapeModelStatic::InitBox(AceType::RawPtr(containerNode), mockPixelMap);

    EXPECT_FALSE(paintProperty->HasPixelMapInfo());
}

/**
 * @tc.name: InitBox_API14Plus_NullFrameNode
 * @tc.desc: InitBox with API >= 14 and null frameNode triggers CHECK_NULL_VOID early return in the macro
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, InitBox_API14Plus_NullFrameNode, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(TEST_API_VERSION_14);

    auto observerNode = CreateContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto observerProperty = observerNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(observerProperty, nullptr);
    ASSERT_FALSE(observerProperty->HasPixelMapInfo());

    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ShapeModelStatic::InitBox(nullptr, mockPixelMap);

    EXPECT_FALSE(observerProperty->HasPixelMapInfo());
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(TEST_API_VERSION_13);
}

/**
 * @tc.name: InitBox_API14Plus_WrongPaintPropertyType
 * @tc.desc: InitBox with API >= 14 on a non-ShapeContainer node (Circle) causes
 *           GetPaintPropertyPtr<ShapeContainerPaintProperty> to return null, skipping the update
 * @tc.type: FUNC
 */
HWTEST_F(ShapeAbstractModelStaticTest, InitBox_API14Plus_WrongPaintPropertyType, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(TEST_API_VERSION_14);
    auto circleNode = CreateNode(TEST_NODE_ID_A);
    ASSERT_NE(circleNode, nullptr);
    auto paintProperty = GetShapePaintProp(circleNode);
    ASSERT_NE(paintProperty, nullptr);

    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ShapeModelStatic::InitBox(AceType::RawPtr(circleNode), mockPixelMap);

    auto containerProp = circleNode->GetPaintProperty<ShapeContainerPaintProperty>();
    EXPECT_EQ(containerProp, nullptr);
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(TEST_API_VERSION_13);
}

} // namespace OHOS::Ace::NG
