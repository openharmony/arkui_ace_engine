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

#include <array>

#define private public
#define protected public

#include "gtest/gtest.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_resource_adapter_v2.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/radius.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/pattern/shape/rect_pattern.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ID_RADIUS_WIDTH = 1001;
constexpr int32_t ID_RADIUS_HEIGHT = 1002;
} // namespace

class RectPatternTddTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: SetRadiusWidth002
 * @tc.desc: Test SetRadiusWidth with RefPtr<ResourceObject> when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusWidth002, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = false;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    rectModelNG.SetRadiusWidth(resObj);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), false);
}

/**
 * @tc.name: SetRadiusWidth003
 * @tc.desc: Test static SetRadiusWidth(FrameNode*, ResourceObject) when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusWidth003, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = false;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RectModelNG::SetRadiusWidth(AceType::RawPtr(frameNode), resObj);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), false);
}

/**
 * @tc.name: SetRadiusWidth004
 * @tc.desc: Test static SetRadiusWidth(FrameNode*, ResourceObject) with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusWidth004, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RectModelNG::SetRadiusWidth(nullptr, resObj);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetRadiusHeight002
 * @tc.desc: Test SetRadiusHeight with RefPtr<ResourceObject> when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusHeight002, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = false;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    rectModelNG.SetRadiusHeight(resObj);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), false);
}

/**
 * @tc.name: SetRadiusHeight003
 * @tc.desc: Test static SetRadiusHeight(FrameNode*, ResourceObject) when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusHeight003, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = false;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RectModelNG::SetRadiusHeight(AceType::RawPtr(frameNode), resObj);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), false);
}

/**
 * @tc.name: SetRadiusHeight004
 * @tc.desc: Test static SetRadiusHeight(FrameNode*, ResourceObject) with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusHeight004, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RectModelNG::SetRadiusHeight(nullptr, resObj);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetRadius002
 * @tc.desc: Test SetRadius with RefPtr<ResourceObject> when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadius002, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = false;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    rectModelNG.SetRadius(resObj);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), false);
}

/**
 * @tc.name: SetRadius003
 * @tc.desc: Test static SetRadius(FrameNode*, ResourceObject) when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadius003, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = false;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RectModelNG::SetRadius(AceType::RawPtr(frameNode), resObj);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), false);
}

/**
 * @tc.name: SetRadius004
 * @tc.desc: Test static SetRadius(FrameNode*, ResourceObject) with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadius004, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RectModelNG::SetRadius(nullptr, resObj);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetRadius005
 * @tc.desc: Test SetRadius with ResourceObject when value is negative
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadius005, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<RectPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    ResetMockResourceData();
    Dimension NEGATIVE_RADIUS_DIM = Dimension(-1.0_vp);
    AddMockResourceData(ID_RADIUS_HEIGHT, NEGATIVE_RADIUS_DIM);
    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        ID_RADIUS_HEIGHT, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", Container::CurrentIdSafely());
    rectModelNG.SetRadius(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), 0.0f);

    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetRadiusWidth005
 * @tc.desc: Test static SetRadiusWidth(FrameNode*, Dimension) with negative value
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusWidth005, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    Dimension NEGATIVE_WIDTH_DIM = Dimension(-5.0_vp);
    RectModelNG::SetRadiusWidth(AceType::RawPtr(frameNode), NEGATIVE_WIDTH_DIM);

    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), -1.0f);
}

/**
 * @tc.name: SetRadiusHeight005
 * @tc.desc: Test static SetRadiusHeight(FrameNode*, Dimension) with negative value
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusHeight005, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    Dimension NEGATIVE_HEIGHT_DIM = Dimension(-5.0_vp);
    RectModelNG::SetRadiusHeight(AceType::RawPtr(frameNode), NEGATIVE_HEIGHT_DIM);

    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), -1.0f);
}

/**
 * @tc.name: UpdateRadius001
 * @tc.desc: Test UpdateRadius with valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, UpdateRadius001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    Radius testRadius;
    Dimension TEST_RADIUS_DIM_X = Dimension(15.0_vp);
    Dimension TEST_RADIUS_DIM_Y = Dimension(25.0_vp);
    testRadius.SetX(TEST_RADIUS_DIM_X);
    testRadius.SetY(TEST_RADIUS_DIM_Y);
    RectModelNG::UpdateRadius(testRadius);

    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), TEST_RADIUS_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), TEST_RADIUS_DIM_Y.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetX().ConvertToPx(), TEST_RADIUS_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetY().ConvertToPx(), TEST_RADIUS_DIM_Y.ConvertToPx());
}

/**
 * @tc.name: UpdateRadius002
 * @tc.desc: Test static UpdateRadius(FrameNode*, Radius) with valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, UpdateRadius002, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    Radius testRadius;
    Dimension TEST_RADIUS_DIM_X = Dimension(18.0_vp);
    Dimension TEST_RADIUS_DIM_Y = Dimension(28.0_vp);
    testRadius.SetX(TEST_RADIUS_DIM_X);
    testRadius.SetY(TEST_RADIUS_DIM_Y);
    RectModelNG::UpdateRadius(AceType::RawPtr(frameNode), testRadius);

    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), true);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), TEST_RADIUS_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), TEST_RADIUS_DIM_Y.ConvertToPx());
}

/**
 * @tc.name: UpdateRadius003
 * @tc.desc: Test static UpdateRadius(FrameNode*, Radius) with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, UpdateRadius003, TestSize.Level1)
{
    Radius testRadius;
    testRadius.SetX(Dimension(10.0_vp));
    testRadius.SetY(Dimension(20.0_vp));
    RectModelNG::UpdateRadius(nullptr, testRadius);
}

/**
 * @tc.name: SetTopLeftRadiusStatic001
 * @tc.desc: Test static SetTopLeftRadius(FrameNode*, Radius)
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetTopLeftRadiusStatic001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    Radius testRadius(Dimension(12.0_vp), Dimension(13.0_vp));
    RectModelNG::SetTopLeftRadius(AceType::RawPtr(frameNode), testRadius);

    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), Dimension(12.0_vp).ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), Dimension(13.0_vp).ConvertToPx());
}

/**
 * @tc.name: SetTopRightRadiusStatic001
 * @tc.desc: Test static SetTopRightRadius(FrameNode*, Radius)
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetTopRightRadiusStatic001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    Radius testRadius(Dimension(14.0_vp), Dimension(15.0_vp));
    RectModelNG::SetTopRightRadius(AceType::RawPtr(frameNode), testRadius);

    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetX().ConvertToPx(), Dimension(14.0_vp).ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetY().ConvertToPx(), Dimension(15.0_vp).ConvertToPx());
}

/**
 * @tc.name: SetBottomLeftRadiusStatic001
 * @tc.desc: Test static SetBottomLeftRadius(FrameNode*, Radius)
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetBottomLeftRadiusStatic001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    Radius testRadius(Dimension(16.0_vp), Dimension(17.0_vp));
    RectModelNG::SetBottomLeftRadius(AceType::RawPtr(frameNode), testRadius);

    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetBottomLeftRadiusValue().GetX().ConvertToPx(), Dimension(16.0_vp).ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetBottomLeftRadiusValue().GetY().ConvertToPx(), Dimension(17.0_vp).ConvertToPx());
}

/**
 * @tc.name: SetBottomRightRadiusStatic001
 * @tc.desc: Test static SetBottomRightRadius(FrameNode*, Radius)
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetBottomRightRadiusStatic001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    Radius testRadius(Dimension(18.0_vp), Dimension(19.0_vp));
    RectModelNG::SetBottomRightRadius(AceType::RawPtr(frameNode), testRadius);

    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetBottomRightRadiusValue().GetX().ConvertToPx(), Dimension(18.0_vp).ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetBottomRightRadiusValue().GetY().ConvertToPx(), Dimension(19.0_vp).ConvertToPx());
}

/**
 * @tc.name: SetRadiusValueStatic001
 * @tc.desc: Test static SetRadiusValue(FrameNode*, Dimension, Dimension, int32_t) with each index
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusValueStatic001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    RectModelNG::SetRadiusValue(AceType::RawPtr(frameNode),
                                Dimension(11.0_vp), Dimension(12.0_vp), RectModel::TOP_LEFT_RADIUS);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), Dimension(11.0_vp).ConvertToPx());

    RectModelNG::SetRadiusValue(AceType::RawPtr(frameNode),
                                Dimension(13.0_vp), Dimension(14.0_vp), RectModel::TOP_RIGHT_RADIUS);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetX().ConvertToPx(), Dimension(13.0_vp).ConvertToPx());

    RectModelNG::SetRadiusValue(AceType::RawPtr(frameNode),
                                Dimension(15.0_vp), Dimension(16.0_vp), RectModel::BOTTOM_RIGHT_RADIUS);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetBottomRightRadiusValue().GetX().ConvertToPx(), Dimension(15.0_vp).ConvertToPx());

    RectModelNG::SetRadiusValue(AceType::RawPtr(frameNode),
                                Dimension(17.0_vp), Dimension(18.0_vp), RectModel::BOTTOM_LEFT_RADIUS);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetBottomLeftRadiusValue().GetX().ConvertToPx(), Dimension(17.0_vp).ConvertToPx());
}

/**
 * @tc.name: SetShapeRectRadiusNull001
 * @tc.desc: Test SetShapeRectRadius with null rect
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetShapeRectRadiusNull001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    rectModelNG.SetShapeRectRadius(nullptr, Dimension(10.0_vp), Dimension(20.0_vp), RectModel::TOP_LEFT_RADIUS);
}

/**
 * @tc.name: SetShapeRectRadiusDefault001
 * @tc.desc: Test SetShapeRectRadius with invalid index
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetShapeRectRadiusDefault001, TestSize.Level1)
{
    auto rect = AceType::MakeRefPtr<ShapeRect>();
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();

    auto initialRadius = Ace::Radius(Dimension(100.0_vp), Dimension(100.0_vp));
    rect->SetTopLeftRadius(initialRadius);
    rect->SetTopRightRadius(initialRadius);
    rect->SetBottomRightRadius(initialRadius);
    rect->SetBottomLeftRadius(initialRadius);

    rectModelNG.SetShapeRectRadius(rect, Dimension(1.0_vp), Dimension(2.0_vp), 4);
    EXPECT_EQ(rect->GetTopLeftRadius(), initialRadius);
    EXPECT_EQ(rect->GetTopRightRadius(), initialRadius);
    EXPECT_EQ(rect->GetBottomRightRadius(), initialRadius);
    EXPECT_EQ(rect->GetBottomLeftRadius(), initialRadius);
}

/**
 * @tc.name: SetRadiusValueResObj001
 * @tc.desc: Test SetRadiusValue with ResourceObject when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusValueResObj001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = false;
    RefPtr<ResourceObject> radiusXResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RefPtr<ResourceObject> radiusYResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    rectModelNG.SetRadiusValue(Dimension(10.0_vp), Dimension(20.0_vp),
                               radiusXResObj, radiusYResObj, RectModel::TOP_LEFT_RADIUS);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
}

/**
 * @tc.name: SetRadiusValueResObjStatic001
 * @tc.desc: Test static SetRadiusValue with ResourceObject when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusValueResObjStatic001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = false;
    RefPtr<ResourceObject> radiusXResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RefPtr<ResourceObject> radiusYResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RectModelNG::SetRadiusValue(AceType::RawPtr(frameNode), Dimension(10.0_vp), Dimension(20.0_vp),
        radiusXResObj, radiusYResObj, RectModel::TOP_LEFT_RADIUS);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
}

/**
 * @tc.name: SetRadiusValueResObjStatic002
 * @tc.desc: Test static SetRadiusValue with ResourceObject and null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusValueResObjStatic002, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> radiusXResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RefPtr<ResourceObject> radiusYResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RectModelNG::SetRadiusValue(nullptr, Dimension(10.0_vp), Dimension(20.0_vp),
        radiusXResObj, radiusYResObj, RectModel::TOP_LEFT_RADIUS);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetRadiusValueResObjStatic003
 * @tc.desc: Test static SetRadiusValue with ResourceObject overriding radius
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusValueResObjStatic003, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ResetMockResourceData();
    Dimension TEST_RADIUS_X_DIM = Dimension(30.0_vp);
    Dimension TEST_RADIUS_Y_DIM = Dimension(40.0_vp);
    AddMockResourceData(ID_RADIUS_WIDTH, TEST_RADIUS_X_DIM);
    AddMockResourceData(ID_RADIUS_HEIGHT, TEST_RADIUS_Y_DIM);
    std::vector<ResourceObjectParams> params;
    auto radiusXResObj = AceType::MakeRefPtr<ResourceObject>(
        ID_RADIUS_WIDTH, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", Container::CurrentIdSafely());
    auto radiusYResObj = AceType::MakeRefPtr<ResourceObject>(
        ID_RADIUS_HEIGHT, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", Container::CurrentIdSafely());

    RectModelNG::SetRadiusValue(AceType::RawPtr(frameNode), Dimension(1.0_vp), Dimension(2.0_vp),
        radiusXResObj, radiusYResObj, RectModel::TOP_LEFT_RADIUS);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), TEST_RADIUS_X_DIM.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), TEST_RADIUS_Y_DIM.ConvertToPx());

    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetRadiusValueResObjStatic004
 * @tc.desc: Test static SetRadiusValue with null ResourceObject for TOP_RIGHT_RADIUS
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusValueResObjStatic004, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> radiusXResObj;
    RefPtr<ResourceObject> radiusYResObj;

    RectModelNG::SetRadiusValue(AceType::RawPtr(frameNode), Dimension(35.0_vp), Dimension(45.0_vp),
        radiusXResObj, radiusYResObj, RectModel::TOP_RIGHT_RADIUS);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(paintProperty->HasTopRightRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetX().ConvertToPx(), Dimension(35.0_vp).ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetTopRightRadiusValue().GetY().ConvertToPx(), Dimension(45.0_vp).ConvertToPx());

    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetRadiusValueResObjStatic005
 * @tc.desc: Test static SetRadiusValue with null ResourceObject for BOTTOM_RIGHT_RADIUS and BOTTOM_LEFT_RADIUS
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusValueResObjStatic005, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> radiusXResObj;
    RefPtr<ResourceObject> radiusYResObj;

    RectModelNG::SetRadiusValue(AceType::RawPtr(frameNode), Dimension(55.0_vp), Dimension(65.0_vp),
        radiusXResObj, radiusYResObj, RectModel::BOTTOM_RIGHT_RADIUS);
    pattern->resourceMgr_->ReloadResources();
    // Source maps BOTTOM_RIGHT_RADIUS to BottomLeftRadius property
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetBottomLeftRadiusValue().GetX().ConvertToPx(), Dimension(55.0_vp).ConvertToPx());

    RectModelNG::SetRadiusValue(AceType::RawPtr(frameNode), Dimension(75.0_vp), Dimension(85.0_vp),
        radiusXResObj, radiusYResObj, RectModel::BOTTOM_LEFT_RADIUS);
    pattern->resourceMgr_->ReloadResources();
    // Source maps BOTTOM_LEFT_RADIUS to BottomRightRadius property
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetBottomRightRadiusValue().GetX().ConvertToPx(), Dimension(75.0_vp).ConvertToPx());

    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetRadiusWidthNegative001
 * @tc.desc: Test SetRadiusWidth(Dimension) with negative value
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusWidthNegative001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    Dimension NEGATIVE_WIDTH_DIM = Dimension(-10.0_vp);
    rectModelNG.SetRadiusWidth(NEGATIVE_WIDTH_DIM);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), -1.0f);
}

/**
 * @tc.name: SetRadiusHeightNegative001
 * @tc.desc: Test SetRadiusHeight(Dimension) with negative value
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusHeightNegative001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    Dimension NEGATIVE_HEIGHT_DIM = Dimension(-10.0_vp);
    rectModelNG.SetRadiusHeight(NEGATIVE_HEIGHT_DIM);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), -1.0f);
}

/**
 * @tc.name: SetRadiusValueStaticInvalidIndex001
 * @tc.desc: Test static SetRadiusValue with invalid index does not modify any radius
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusValueStaticInvalidIndex001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    RectModelNG::SetRadiusValue(frameNode, Dimension(99.0_vp), Dimension(88.0_vp), -1);
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), false);
}

/**
 * @tc.name: SetRadiusValueResObjStaticInvalidResObj001
 * @tc.desc: Test static SetRadiusValue with invalid ResourceObject where ConvertFromResObjNG fails for both X and Y
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusValueResObjStaticInvalidResObj001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RectModelNG::SetRadiusValue(frameNode, Dimension(10.0_vp), Dimension(20.0_vp),
        invalidResObj, invalidResObj, RectModel::TOP_LEFT_RADIUS);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), true);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetX().ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(paintProperty->GetTopLeftRadiusValue().GetY().ConvertToPx(), 0.0f);

    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetRadiusValueResObjStaticInvalidIndex001
 * @tc.desc: Test static SetRadiusValue with ResourceObject and invalid index does not modify any radius
 * @tc.type: FUNC
 */
HWTEST_F(RectPatternTddTestNg, SetRadiusValueResObjStaticInvalidIndex001, TestSize.Level1)
{
    auto rectModelNG = RectModelNG();
    rectModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ShapePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RectPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    RectModelNG::SetRadiusValue(frameNode, Dimension(10.0_vp), Dimension(20.0_vp),
        resObj, resObj, -1);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(paintProperty->HasTopLeftRadius(), false);
    EXPECT_EQ(paintProperty->HasTopRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomRightRadius(), false);
    EXPECT_EQ(paintProperty->HasBottomLeftRadius(), false);

    g_isConfigChangePerform = false;
}
} // namespace OHOS::Ace::NG
