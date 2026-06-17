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

#define private public
#define protected public

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/image/mock_pixel_map.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
using OHOS::Ace::g_isConfigChangePerform;

namespace OHOS::Ace::NG {
namespace {
constexpr double TEST_VIEWPORT_LEFT = 10.0;
constexpr double TEST_VIEWPORT_TOP = 20.0;
constexpr double TEST_VIEWPORT_WIDTH = 100.0;
constexpr double TEST_VIEWPORT_HEIGHT = 80.0;
const Color TEST_STROKE_COLOR = Color::BLUE;
const Color TEST_FILL_COLOR = Color::GREEN;
const Color TEST_FOREGROUND_COLOR = Color::RED;
constexpr double TEST_DASH_OFFSET_VP_VALUE = 5.0;
constexpr int32_t TEST_LINE_CAP_ROUND = 1;
constexpr int32_t TEST_LINE_JOIN_ROUND = 1;
constexpr double TEST_MITER_LIMIT = 2.5;
constexpr double TEST_FILL_OPACITY = 0.7;
constexpr double TEST_STROKE_OPACITY = 0.6;
constexpr Dimension TEST_STROKE_WIDTH_VALUE = 3.0_vp;
constexpr bool TEST_ANTIALIAS_TRUE = true;
constexpr bool TEST_ANTIALIAS_FALSE = false;

inline void TriggerResourceReload(const RefPtr<FrameNode>& frameNode)
{
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    if (pattern) {
        pattern->OnColorModeChange(0);
    }
}

RefPtr<ShapeContainerPaintProperty> GetPaintProp(const RefPtr<FrameNode>& node)
{
    EXPECT_NE(node, nullptr);
    return node->GetPaintProperty<ShapeContainerPaintProperty>();
}

std::vector<Dimension> MakeTestViewBoxArray()
{
    return {
        Dimension(TEST_VIEWPORT_LEFT),
        Dimension(TEST_VIEWPORT_TOP),
        Dimension(TEST_VIEWPORT_WIDTH),
        Dimension(TEST_VIEWPORT_HEIGHT),
    };
}

std::vector<RefPtr<ResourceObject>> MakeTestResObjArray(size_t count)
{
    std::vector<RefPtr<ResourceObject>> resObjArray(count);
    for (size_t i = 0; i < count; ++i) {
        resObjArray[i] = AceType::MakeRefPtr<ResourceObject>();
    }
    return resObjArray;
}

std::vector<Ace::Dimension> MakeTestDashArraySeg()
{
    return { Dimension(TEST_DASH_OFFSET_VP_VALUE), Dimension(TEST_DASH_OFFSET_VP_VALUE * 2) };
}
} // namespace

class ShapeModelNGTest : public testing::Test {
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
        g_isConfigChangePerform = false;
        ViewStackProcessor::GetInstance()->ClearVisualState();
        auto* stack = ViewStackProcessor::GetInstance();
        if (stack->GetMainFrameNode()) {
            stack->Pop();
        }
    }

    RefPtr<FrameNode> CreateShapeContainerNode()
    {
        ShapeModelNG().Create();
        return AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
};

// ====== SetViewPort (Dimensions) ======
/**
 * @tc.name: SetViewPortDimensions_ValidNode
 * @tc.desc: SetViewPort with Dimensions sets ShapeViewBox on the paint property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetViewPortDimensions_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetViewPort(AceType::RawPtr(frameNode),
        Dimension(TEST_VIEWPORT_LEFT),
        Dimension(TEST_VIEWPORT_TOP),
        Dimension(TEST_VIEWPORT_WIDTH),
        Dimension(TEST_VIEWPORT_HEIGHT));
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasShapeViewBox());
    EXPECT_EQ(prop->GetShapeViewBoxValue().Left().Value(), TEST_VIEWPORT_LEFT);
    EXPECT_EQ(prop->GetShapeViewBoxValue().Top().Value(), TEST_VIEWPORT_TOP);
    EXPECT_EQ(prop->GetShapeViewBoxValue().Width().Value(), TEST_VIEWPORT_WIDTH);
    EXPECT_EQ(prop->GetShapeViewBoxValue().Height().Value(), TEST_VIEWPORT_HEIGHT);
}

/**
 * @tc.name: SetViewPortDimensions_NullFrameNode
 * @tc.desc: SetViewPort with Dimensions and null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetViewPortDimensions_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetViewPort(nullptr,
        Dimension(TEST_VIEWPORT_LEFT),
        Dimension(TEST_VIEWPORT_TOP),
        Dimension(TEST_VIEWPORT_WIDTH),
        Dimension(TEST_VIEWPORT_HEIGHT));
    EXPECT_FALSE(GetPaintProp(observerNode)->HasShapeViewBox());
}

// ====== SetViewPort (Vector) ======
/**
 * @tc.name: SetViewPortVector_ResObj_ValidNode
 * @tc.desc: SetViewPort with vector of Dimensions/ResObj sets ShapeViewBox
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetViewPortVector_ResObj_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto dimArray = MakeTestViewBoxArray();
    auto resObjArray = MakeTestResObjArray(4);
    ShapeModelNG::SetViewPort(AceType::RawPtr(frameNode), dimArray, resObjArray);
    TriggerResourceReload(frameNode);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasShapeViewBox());
}

/**
 * @tc.name: SetViewPortVector_ResObj_NullFrameNode
 * @tc.desc: SetViewPort with vector of Dimensions/ResObj and null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetViewPortVector_ResObj_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto dimArray = MakeTestViewBoxArray();
    auto resObjArray = MakeTestResObjArray(4);
    ShapeModelNG::SetViewPort(nullptr, dimArray, resObjArray);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasShapeViewBox());
}

// ====== SetStroke (Color) ======
/**
 * @tc.name: SetStrokeColor_Static_ValidNode
 * @tc.desc: SetStroke with Color sets stroke color on the paint property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeColor_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetStroke(AceType::RawPtr(frameNode), TEST_STROKE_COLOR);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStroke());
    EXPECT_EQ(prop->GetStrokeValue(), TEST_STROKE_COLOR);
}

/**
 * @tc.name: SetStrokeColor_Static_NullFrameNode
 * @tc.desc: SetStroke with Color and null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeColor_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetStroke(nullptr, TEST_STROKE_COLOR);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStroke());
}

// ====== SetFill (Color) ======
/**
 * @tc.name: SetFillColor_Static_ValidNode
 * @tc.desc: SetFill with Color sets fill color on the paint property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillColor_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetFill(AceType::RawPtr(frameNode), TEST_FILL_COLOR);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasFill());
    EXPECT_EQ(prop->GetFillValue(), TEST_FILL_COLOR);
}

/**
 * @tc.name: SetFillColor_Static_NullFrameNode
 * @tc.desc: SetFill with Color and null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillColor_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetFill(nullptr, TEST_FILL_COLOR);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasFill());
}

// ====== SetForegroundColor (Color) ======
/**
 * @tc.name: SetForegroundColorColor_ValidNode
 * @tc.desc: SetForegroundColor with Color updates the fill property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetForegroundColorColor_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetViewPort(AceType::RawPtr(frameNode),
        Dimension(TEST_VIEWPORT_LEFT),
        Dimension(TEST_VIEWPORT_TOP),
        Dimension(TEST_VIEWPORT_WIDTH),
        Dimension(TEST_VIEWPORT_HEIGHT));
    auto pattern = frameNode->GetPattern<ShapeContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    ShapeModelNG().SetForegroundColor(TEST_FOREGROUND_COLOR);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasFill());
}

/**
 * @tc.name: SetForegroundColorColor_NullFrameNode
 * @tc.desc: SetForegroundColor with Color and null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetForegroundColorColor_MemberValidNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG().SetForegroundColor(TEST_FOREGROUND_COLOR);
    EXPECT_TRUE(GetPaintProp(observerNode)->HasFill());
}

// ====== SetStrokeDashArray ======
/**
 * @tc.name: SetStrokeDashArray_Static_ValidNode
 * @tc.desc: SetStrokeDashArray sets the stroke dash array segments
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashArray_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto segments = MakeTestDashArraySeg();
    ShapeModelNG::SetStrokeDashArray(AceType::RawPtr(frameNode), segments);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeDashArray());
}

/**
 * @tc.name: SetStrokeDashArray_Static_NullFrameNode
 * @tc.desc: SetStrokeDashArray with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashArray_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto segments = MakeTestDashArraySeg();
    ShapeModelNG::SetStrokeDashArray(nullptr, segments);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeDashArray());
}

/**
 * @tc.name: SetStrokeDashArray_ResObj_ValidNode
 * @tc.desc: SetStrokeDashArray with ResObj sets the stroke dash array
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashArray_ResObj_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto segments = MakeTestDashArraySeg();
    auto resObjArray = MakeTestResObjArray(segments.size());
    ShapeModelNG::SetStrokeDashArray(AceType::RawPtr(frameNode), segments, resObjArray);
    TriggerResourceReload(frameNode);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeDashArray());
}

/**
 * @tc.name: SetStrokeDashArray_ResObj_NullFrameNode
 * @tc.desc: SetStrokeDashArray with ResObj and null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashArray_ResObj_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto segments = MakeTestDashArraySeg();
    auto resObjArray = MakeTestResObjArray(segments.size());
    ShapeModelNG::SetStrokeDashArray(nullptr, segments, resObjArray);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeDashArray());
}

// ====== SetAntiAlias ======
/**
 * @tc.name: SetAntiAlias_Static_ValidNode
 * @tc.desc: SetAntiAlias updates anti-alias property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetAntiAlias_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetAntiAlias(AceType::RawPtr(frameNode), TEST_ANTIALIAS_TRUE);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasAntiAlias());
    EXPECT_TRUE(prop->GetAntiAliasValue());
}

/**
 * @tc.name: SetAntiAlias_Static_NullFrameNode
 * @tc.desc: SetAntiAlias with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetAntiAlias_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetAntiAlias(nullptr, TEST_ANTIALIAS_FALSE);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasAntiAlias());
}

// ====== SetStrokeDashOffset ======
/**
 * @tc.name: SetStrokeDashOffset_Static_ValidNode
 * @tc.desc: SetStrokeDashOffset updates the stroke dash offset property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashOffset_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetStrokeDashOffset(AceType::RawPtr(frameNode), Dimension(TEST_DASH_OFFSET_VP_VALUE));
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeDashOffset());
    EXPECT_EQ(prop->GetStrokeDashOffsetValue().Value(), TEST_DASH_OFFSET_VP_VALUE);
}

/**
 * @tc.name: SetStrokeDashOffset_Static_NullFrameNode
 * @tc.desc: SetStrokeDashOffset with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashOffset_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetStrokeDashOffset(nullptr, Dimension(TEST_DASH_OFFSET_VP_VALUE));
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeDashOffset());
}

// ====== SetStrokeLineCap ======
/**
 * @tc.name: SetStrokeLineCap_Static_ValidNode
 * @tc.desc: SetStrokeLineCap updates the stroke line cap property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeLineCap_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetStrokeLineCap(AceType::RawPtr(frameNode), TEST_LINE_CAP_ROUND);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeLineCap());
    EXPECT_EQ(prop->GetStrokeLineCapValue(), TEST_LINE_CAP_ROUND);
}

/**
 * @tc.name: SetStrokeLineCap_Static_NullFrameNode
 * @tc.desc: SetStrokeLineCap with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeLineCap_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetStrokeLineCap(nullptr, TEST_LINE_CAP_ROUND);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeLineCap());
}

// ====== SetStrokeLineJoin ======
/**
 * @tc.name: SetStrokeLineJoin_Static_ValidNode
 * @tc.desc: SetStrokeLineJoin updates the stroke line join property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeLineJoin_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetStrokeLineJoin(AceType::RawPtr(frameNode), TEST_LINE_JOIN_ROUND);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeLineJoin());
    EXPECT_EQ(prop->GetStrokeLineJoinValue(), TEST_LINE_JOIN_ROUND);
}

/**
 * @tc.name: SetStrokeLineJoin_Static_NullFrameNode
 * @tc.desc: SetStrokeLineJoin with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeLineJoin_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetStrokeLineJoin(nullptr, TEST_LINE_JOIN_ROUND);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeLineJoin());
}

// ====== SetStrokeMiterLimit ======
/**
 * @tc.name: SetStrokeMiterLimit_Static_ValidNode
 * @tc.desc: SetStrokeMiterLimit updates the stroke miter limit property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeMiterLimit_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetStrokeMiterLimit(AceType::RawPtr(frameNode), TEST_MITER_LIMIT);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeMiterLimit());
    EXPECT_NEAR(prop->GetStrokeMiterLimitValue(), TEST_MITER_LIMIT, 0.001);
}

/**
 * @tc.name: SetStrokeMiterLimit_Static_NullFrameNode
 * @tc.desc: SetStrokeMiterLimit with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeMiterLimit_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetStrokeMiterLimit(nullptr, TEST_MITER_LIMIT);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeMiterLimit());
}

// ====== SetFillOpacity ======
/**
 * @tc.name: SetFillOpacity_Static_ValidNode
 * @tc.desc: SetFillOpacity updates the fill opacity property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillOpacity_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetFillOpacity(AceType::RawPtr(frameNode), TEST_FILL_OPACITY);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasFillOpacity());
    EXPECT_NEAR(prop->GetFillOpacityValue(), TEST_FILL_OPACITY, 0.001);
}

/**
 * @tc.name: SetFillOpacity_Static_ClampNegative
 * @tc.desc: SetFillOpacity clamps negative values to zero
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillOpacity_Static_ClampNegative, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetFillOpacity(AceType::RawPtr(frameNode), -1.0);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasFillOpacity());
    EXPECT_NEAR(prop->GetFillOpacityValue(), 0.0, 0.001);
}

/**
 * @tc.name: SetFillOpacity_Static_NullFrameNode
 * @tc.desc: SetFillOpacity with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillOpacity_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetFillOpacity(nullptr, TEST_FILL_OPACITY);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasFillOpacity());
}

// ====== SetStrokeOpacity ======
/**
 * @tc.name: SetStrokeOpacity_Static_ValidNode
 * @tc.desc: SetStrokeOpacity updates the stroke opacity property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeOpacity_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetStrokeOpacity(AceType::RawPtr(frameNode), TEST_STROKE_OPACITY);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeOpacity());
    EXPECT_NEAR(prop->GetStrokeOpacityValue(), TEST_STROKE_OPACITY, 0.001);
}

/**
 * @tc.name: SetStrokeOpacity_Static_NullFrameNode
 * @tc.desc: SetStrokeOpacity with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeOpacity_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetStrokeOpacity(nullptr, TEST_STROKE_OPACITY);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeOpacity());
}

// ====== SetStrokeWidth ======
/**
 * @tc.name: SetStrokeWidth_Static_ValidNode
 * @tc.desc: SetStrokeWidth updates the stroke width property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeWidth_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG::SetStrokeWidth(AceType::RawPtr(frameNode), TEST_STROKE_WIDTH_VALUE);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeWidth());
    EXPECT_EQ(prop->GetStrokeWidthValue().Value(), TEST_STROKE_WIDTH_VALUE.Value());
}

/**
 * @tc.name: SetStrokeWidth_Static_NullFrameNode
 * @tc.desc: SetStrokeWidth with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeWidth_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    ShapeModelNG::SetStrokeWidth(nullptr, TEST_STROKE_WIDTH_VALUE);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeWidth());
}

// ====== SetBitmapMesh ======
/**
 * @tc.name: SetBitmapMesh_Static_ValidNode
 * @tc.desc: SetBitmapMesh updates the ImageMesh property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetBitmapMesh_Static_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    std::vector<float> mesh(12, 1.0f);
    constexpr int32_t TEST_COLUMN = 2;
    constexpr int32_t TEST_ROW = 1;
    ShapeModelNG::SetBitmapMesh(AceType::RawPtr(frameNode), mesh, TEST_COLUMN, TEST_ROW);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasImageMesh());
}

/**
 * @tc.name: SetBitmapMesh_Static_NullFrameNode
 * @tc.desc: SetBitmapMesh with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetBitmapMesh_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    std::vector<float> mesh(12, 1.0f);
    constexpr int32_t TEST_COLUMN = 2;
    constexpr int32_t TEST_ROW = 1;
    ShapeModelNG::SetBitmapMesh(nullptr, mesh, TEST_COLUMN, TEST_ROW);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasImageMesh());
}

// ====== SetInitBox ======
/**
 * @tc.name: SetInitBox_Static_ValidPixMap
 * @tc.desc: SetInitBox with valid PixelMap updates the PixelMapInfo property
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetInitBox_Static_ValidPixMap, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    ShapeModelNG::InitBox(AceType::RawPtr(frameNode), pixmap);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasPixelMapInfo());
}

/**
 * @tc.name: SetInitBox_Static_NullFrameNode
 * @tc.desc: SetInitBox with null FrameNode is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetInitBox_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    ShapeModelNG::InitBox(nullptr, pixmap);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasPixelMapInfo());
}

// ====== ResourceObject overloads (ConfigChangePerform = false) ======
/**
 * @tc.name: SetStrokeResObj_ConfigChangePerformFalse
 * @tc.desc: SetStroke with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetStroke(resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasStroke());
}

/**
 * @tc.name: SetFillResObj_ConfigChangePerformFalse
 * @tc.desc: SetFill with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetFill(resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasFill());
}

/**
 * @tc.name: SetForegroundColorResObj_ConfigChangePerformFalse
 * @tc.desc: SetForegroundColor with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetForegroundColorResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetForegroundColor(resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasFill());
}

/**
 * @tc.name: SetStrokeDashOffsetResObj_ConfigChangePerformFalse
 * @tc.desc: SetStrokeDashOffset with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashOffsetResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetStrokeDashOffset(resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasStrokeDashOffset());
}

/**
 * @tc.name: SetStrokeMiterLimitResObj_ConfigChangePerformFalse
 * @tc.desc: SetStrokeMiterLimit with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeMiterLimitResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetStrokeMiterLimit(resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasStrokeMiterLimit());
}

/**
 * @tc.name: SetStrokeOpacityResObj_ConfigChangePerformFalse
 * @tc.desc: SetStrokeOpacity with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeOpacityResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetStrokeOpacity(resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasStrokeOpacity());
}

/**
 * @tc.name: SetFillOpacityResObj_ConfigChangePerformFalse
 * @tc.desc: SetFillOpacity with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillOpacityResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetFillOpacity(resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasFillOpacity());
}

/**
 * @tc.name: SetStrokeWidthResObj_ConfigChangePerformFalse
 * @tc.desc: SetStrokeWidth with ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeWidthResObj_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetStrokeWidth(resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasStrokeWidth());
}

// ====== ResourceObject overloads (Valid FrameNode) ======
/**
 * @tc.name: SetStrokeResObj_ValidNode
 * @tc.desc: SetStroke with ResourceObject updates stroke when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeResObj_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetStroke(resObj);
    TriggerResourceReload(frameNode);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStroke());
}

/**
 * @tc.name: SetFillResObj_ValidNode
 * @tc.desc: SetFill with ResourceObject updates fill when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillResObj_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetFill(resObj);
    TriggerResourceReload(frameNode);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasFill());
}

/**
 * @tc.name: SetForegroundColorResObj_ValidNode
 * @tc.desc: SetForegroundColor with ResourceObject updates fill when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetForegroundColorResObj_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetForegroundColor(resObj);
    TriggerResourceReload(frameNode);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasFill());
}

/**
 * @tc.name: SetStrokeDashOffsetResObj_ValidNode
 * @tc.desc: SetStrokeDashOffset with ResourceObject updates dash offset when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashOffsetResObj_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetStrokeDashOffset(resObj);
    TriggerResourceReload(frameNode);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeDashOffset());
}

/**
 * @tc.name: SetStrokeMiterLimitResObj_ValidNode
 * @tc.desc: SetStrokeMiterLimit with ResourceObject updates miter limit when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeMiterLimitResObj_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetStrokeMiterLimit(resObj);
    TriggerResourceReload(frameNode);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeMiterLimit());
}

/**
 * @tc.name: SetStrokeOpacityResObj_ValidNode
 * @tc.desc: SetStrokeOpacity with ResourceObject updates stroke opacity when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeOpacityResObj_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetStrokeOpacity(resObj);
    TriggerResourceReload(frameNode);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeOpacity());
}

/**
 * @tc.name: SetFillOpacityResObj_ValidNode
 * @tc.desc: SetFillOpacity with ResourceObject updates fill opacity when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillOpacityResObj_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetFillOpacity(resObj);
    TriggerResourceReload(frameNode);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasFillOpacity());
}

/**
 * @tc.name: SetStrokeWidthResObj_ValidNode
 * @tc.desc: SetStrokeWidth with ResourceObject updates stroke width when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeWidthResObj_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG().SetStrokeWidth(resObj);
    TriggerResourceReload(frameNode);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeWidth());
}

// ====== SetAntiAlias member overloads ======
/**
 * @tc.name: SetAntiAlias_Member_ValidNode
 * @tc.desc: SetAntiAlias member updates anti-alias on ShapeContainer node
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetAntiAlias_Member_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG().SetAntiAlias(TEST_ANTIALIAS_TRUE);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasAntiAlias());
    EXPECT_TRUE(prop->GetAntiAliasValue());
}

/**
 * @tc.name: SetStrokeDashArray_Member_ValidNode
 * @tc.desc: SetStrokeDashArray member sets stroke dash array on ShapeContainer node
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashArray_Member_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto segments = MakeTestDashArraySeg();
    ShapeModelNG().SetStrokeDashArray(segments);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasStrokeDashArray());
}

/**
 * @tc.name: SetViewPort_Member_Dimensions_ValidNode
 * @tc.desc: SetViewPort member with Dimensions updates ShapeViewBox
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetViewPort_Member_Dimensions_ValidNode, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    ShapeModelNG().SetViewPort(
        Dimension(TEST_VIEWPORT_LEFT),
        Dimension(TEST_VIEWPORT_TOP),
        Dimension(TEST_VIEWPORT_WIDTH),
        Dimension(TEST_VIEWPORT_HEIGHT));
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasShapeViewBox());
}

/**
 * @tc.name: SetInitBox_Member_ValidPixMap
 * @tc.desc: SetInitBox member with PixelMap updates PixelMapInfo
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetInitBox_Member_ValidPixMap, TestSize.Level1)
{
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pixmap = AceType::MakeRefPtr<MockPixelMap>();
    auto savedApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(14);
    ShapeModelNG().InitBox(pixmap);
    auto prop = GetPaintProp(frameNode);
    EXPECT_TRUE(prop->HasPixelMapInfo());
    AceApplicationInfo::GetInstance().SetApiTargetVersion(savedApiVersion);
}

// ====== Static FrameNode* + ResourceObject overloads: ConfigChangePerform=false early return ======
/**
 * @tc.name: SetStroke_ResObj_Static_ConfigChangePerformFalse
 * @tc.desc: SetStroke with FrameNode and ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStroke_ResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStroke(AceType::RawPtr(frameNode), resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasStroke());
}

/**
 * @tc.name: SetStroke_ResObj_Static_NullFrameNode
 * @tc.desc: SetStroke with null FrameNode and ResourceObject returns early
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStroke_ResObj_Static_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStroke(nullptr, resObj);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStroke());
}

/**
 * @tc.name: SetStroke_ResObj_Static_ValidNode
 * @tc.desc: SetStroke with FrameNode and ResourceObject sets stroke when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStroke_ResObj_Static_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStroke(AceType::RawPtr(frameNode), resObj);
    TriggerResourceReload(frameNode);
    EXPECT_TRUE(GetPaintProp(frameNode)->HasStroke());
}

/**
 * @tc.name: SetFill_ResObj_Static_ConfigChangePerformFalse
 * @tc.desc: SetFill with FrameNode and ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFill_ResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetFill(AceType::RawPtr(frameNode), resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasFill());
}

/**
 * @tc.name: SetFill_ResObj_Static_NullFrameNode
 * @tc.desc: SetFill with null FrameNode and ResourceObject returns early
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFill_ResObj_Static_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetFill(nullptr, resObj);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasFill());
}

/**
 * @tc.name: SetFill_ResObj_Static_ValidNode
 * @tc.desc: SetFill with FrameNode and ResourceObject sets fill when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFill_ResObj_Static_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetFill(AceType::RawPtr(frameNode), resObj);
    TriggerResourceReload(frameNode);
    EXPECT_TRUE(GetPaintProp(frameNode)->HasFill());
}

/**
 * @tc.name: SetForegroundColor_ResObj_Static_ConfigChangePerformFalse
 * @tc.desc: SetForegroundColor with FrameNode and ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetForegroundColor_ResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetForegroundColor(AceType::RawPtr(frameNode), resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasFill());
}

/**
 * @tc.name: SetForegroundColor_ResObj_Static_NullFrameNode
 * @tc.desc: SetForegroundColor with null FrameNode and ResourceObject returns early
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetForegroundColor_ResObj_Static_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetForegroundColor(nullptr, resObj);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasFill());
}

/**
 * @tc.name: SetForegroundColor_ResObj_Static_ValidNode
 * @tc.desc: SetForegroundColor with FrameNode and ResourceObject sets fill when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetForegroundColor_ResObj_Static_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetForegroundColor(AceType::RawPtr(frameNode), resObj);
    TriggerResourceReload(frameNode);
    EXPECT_TRUE(GetPaintProp(frameNode)->HasFill());
}

/**
 * @tc.name: SetStrokeDashOffset_ResObj_Static_ConfigChangePerformFalse
 * @tc.desc: SetStrokeDashOffset with FrameNode and ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashOffset_ResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeDashOffset(AceType::RawPtr(frameNode), resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasStrokeDashOffset());
}

/**
 * @tc.name: SetStrokeDashOffset_ResObj_Static_NullFrameNode
 * @tc.desc: SetStrokeDashOffset with null FrameNode and ResourceObject returns early
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashOffset_ResObj_Static_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeDashOffset(nullptr, resObj);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeDashOffset());
}

/**
 * @tc.name: SetStrokeDashOffset_ResObj_Static_ValidNode
 * @tc.desc: SetStrokeDashOffset with FrameNode and ResourceObject sets dash offset when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeDashOffset_ResObj_Static_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeDashOffset(AceType::RawPtr(frameNode), resObj);
    TriggerResourceReload(frameNode);
    EXPECT_TRUE(GetPaintProp(frameNode)->HasStrokeDashOffset());
}

/**
 * @tc.name: SetStrokeMiterLimit_ResObj_Static_ConfigChangePerformFalse
 * @tc.desc: SetStrokeMiterLimit with FrameNode and ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeMiterLimit_ResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeMiterLimit(AceType::RawPtr(frameNode), resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasStrokeMiterLimit());
}

/**
 * @tc.name: SetStrokeMiterLimit_ResObj_Static_NullFrameNode
 * @tc.desc: SetStrokeMiterLimit with null FrameNode and ResourceObject returns early
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeMiterLimit_ResObj_Static_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeMiterLimit(nullptr, resObj);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeMiterLimit());
}

/**
 * @tc.name: SetStrokeMiterLimit_ResObj_Static_ValidNode
 * @tc.desc: SetStrokeMiterLimit with FrameNode and ResourceObject sets miter limit when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeMiterLimit_ResObj_Static_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeMiterLimit(AceType::RawPtr(frameNode), resObj);
    TriggerResourceReload(frameNode);
    EXPECT_TRUE(GetPaintProp(frameNode)->HasStrokeMiterLimit());
}

/**
 * @tc.name: SetStrokeOpacity_ResObj_Static_ConfigChangePerformFalse
 * @tc.desc: SetStrokeOpacity with FrameNode and ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeOpacity_ResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeOpacity(AceType::RawPtr(frameNode), resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasStrokeOpacity());
}

/**
 * @tc.name: SetStrokeOpacity_ResObj_Static_NullFrameNode
 * @tc.desc: SetStrokeOpacity with null FrameNode and ResourceObject returns early
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeOpacity_ResObj_Static_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeOpacity(nullptr, resObj);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeOpacity());
}

/**
 * @tc.name: SetStrokeOpacity_ResObj_Static_ValidNode
 * @tc.desc: SetStrokeOpacity with FrameNode and ResourceObject sets stroke opacity when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeOpacity_ResObj_Static_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeOpacity(AceType::RawPtr(frameNode), resObj);
    TriggerResourceReload(frameNode);
    EXPECT_TRUE(GetPaintProp(frameNode)->HasStrokeOpacity());
}

/**
 * @tc.name: SetFillOpacity_ResObj_Static_ConfigChangePerformFalse
 * @tc.desc: SetFillOpacity with FrameNode and ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillOpacity_ResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetFillOpacity(AceType::RawPtr(frameNode), resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasFillOpacity());
}

/**
 * @tc.name: SetFillOpacity_ResObj_Static_NullFrameNode
 * @tc.desc: SetFillOpacity with null FrameNode and ResourceObject returns early
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillOpacity_ResObj_Static_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetFillOpacity(nullptr, resObj);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasFillOpacity());
}

/**
 * @tc.name: SetFillOpacity_ResObj_Static_ValidNode
 * @tc.desc: SetFillOpacity with FrameNode and ResourceObject sets fill opacity when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetFillOpacity_ResObj_Static_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetFillOpacity(AceType::RawPtr(frameNode), resObj);
    TriggerResourceReload(frameNode);
    EXPECT_TRUE(GetPaintProp(frameNode)->HasFillOpacity());
}

/**
 * @tc.name: SetStrokeWidth_ResObj_Static_ConfigChangePerformFalse
 * @tc.desc: SetStrokeWidth with FrameNode and ResourceObject returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeWidth_ResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeWidth(AceType::RawPtr(frameNode), resObj);
    EXPECT_FALSE(GetPaintProp(frameNode)->HasStrokeWidth());
}

/**
 * @tc.name: SetStrokeWidth_ResObj_Static_NullFrameNode
 * @tc.desc: SetStrokeWidth with null FrameNode and ResourceObject returns early
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeWidth_ResObj_Static_NullFrameNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto observerNode = CreateShapeContainerNode();
    ASSERT_NE(observerNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeWidth(nullptr, resObj);
    EXPECT_FALSE(GetPaintProp(observerNode)->HasStrokeWidth());
}

/**
 * @tc.name: SetStrokeWidth_ResObj_Static_ValidNode
 * @tc.desc: SetStrokeWidth with FrameNode and ResourceObject sets stroke width when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModelNGTest, SetStrokeWidth_ResObj_Static_ValidNode, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    auto frameNode = CreateShapeContainerNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ShapeModelNG::SetStrokeWidth(AceType::RawPtr(frameNode), resObj);
    TriggerResourceReload(frameNode);
    EXPECT_TRUE(GetPaintProp(frameNode)->HasStrokeWidth());
}

} // namespace OHOS::Ace::NG
