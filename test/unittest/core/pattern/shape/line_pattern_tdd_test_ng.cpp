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

#define private public
#define protected public

#include <memory>
#include "core/accessibility/accessibility_manager.h"

#include "gtest/gtest.h"
#include "include/core/SkCanvas.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_resource_adapter_v2.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/common/resource/pattern_resource_manager.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"
#include "core/components_ng/pattern/shape/line_paint_property.h"
#include "core/components_ng/pattern/shape/line_pattern.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_layout_algorithm.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/render/paint_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t ID_START_X = 2001;
constexpr int32_t ID_START_Y = 2002;
constexpr int32_t ID_END_X = 2003;
constexpr int32_t ID_END_Y = 2004;
constexpr Dimension MOCK_DIM_X = Dimension(10.0f);
constexpr Dimension MOCK_DIM_Y = Dimension(20.0f);
constexpr float ORIGINAL_POINT_X = 5.0f;
constexpr float ORIGINAL_POINT_Y = 15.0f;

RefPtr<FrameNode> CreateLineFrameNode()
{
    LineModelNG().Create();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

RefPtr<ResourceObject> CreateInvalidResObj()
{
    return AceType::MakeRefPtr<ResourceObject>("", "", 0);
}

RefPtr<ResourceObject> CreateValidResObj(int32_t resId)
{
    std::vector<ResourceObjectParams> params;
    return AceType::MakeRefPtr<ResourceObject>(
        resId, static_cast<int32_t>(ResourceType::FLOAT), params, "", "", Container::CurrentIdSafely());
}
} // namespace

class LinePatternTddTestNg : public testing::Test {
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
        frameNode_ = CreateLineFrameNode();
    }

protected:
    RefPtr<FrameNode> frameNode_;
};

/**
 * @tc.name: LineModelNG_StartPointWithFrameNode
 * @tc.desc: Test static StartPoint(FrameNode*, ShapePoint) updates paint property
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointWithFrameNode, TestSize.Level1)
{
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    LineModelNG::StartPoint(AceType::RawPtr(frameNode), point);

    EXPECT_TRUE(paintProperty->HasStartPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().first.ConvertToPx(), ORIGINAL_POINT_X);
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().second.ConvertToPx(), ORIGINAL_POINT_Y);
}

/**
 * @tc.name: LineModelNG_EndPointWithFrameNode
 * @tc.desc: Test static EndPoint(FrameNode*, ShapePoint) updates paint property
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointWithFrameNode, TestSize.Level1)
{
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    LineModelNG::EndPoint(AceType::RawPtr(frameNode), point);

    EXPECT_TRUE(paintProperty->HasEndPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().first.ConvertToPx(), ORIGINAL_POINT_X);
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().second.ConvertToPx(), ORIGINAL_POINT_Y);
}

/**
 * @tc.name: LineModelNG_StartPointResObj_NonStatic_ConfigChangePerformFalse
 * @tc.desc: StartPoint with resObj returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_NonStatic_ConfigChangePerformFalse, TestSize.Level1)
{
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    if (pattern->resourceMgr_ == nullptr) {
        pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    }
    auto initialSize = pattern->resourceMgr_->resMap_.size();

    g_isConfigChangePerform = false;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray;
    LineModelNG().StartPoint(point, resObjArray);

    EXPECT_EQ(pattern->resourceMgr_->resMap_.size(), initialSize);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_NonStatic_ConfigChangePerformFalse
 * @tc.desc: EndPoint with resObj returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_NonStatic_ConfigChangePerformFalse, TestSize.Level1)
{
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    if (pattern->resourceMgr_ == nullptr) {
        pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    }
    auto initialSize = pattern->resourceMgr_->resMap_.size();

    g_isConfigChangePerform = false;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray;
    LineModelNG().EndPoint(point, resObjArray);

    EXPECT_EQ(pattern->resourceMgr_->resMap_.size(), initialSize);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_Static_ConfigChangePerformFalse
 * @tc.desc: Static StartPoint with resObj returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    if (pattern->resourceMgr_ == nullptr) {
        pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    }
    auto initialSize = pattern->resourceMgr_->resMap_.size();

    g_isConfigChangePerform = false;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray;
    LineModelNG::StartPoint(AceType::RawPtr(frameNode), point, resObjArray);

    EXPECT_EQ(pattern->resourceMgr_->resMap_.size(), initialSize);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_Static_NullFrameNode
 * @tc.desc: Static StartPoint with resObj returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateLineFrameNode();
    ASSERT_NE(observerNode, nullptr);
    auto paintProperty = observerNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray;
    LineModelNG::StartPoint(nullptr, point, resObjArray);

    EXPECT_FALSE(paintProperty->HasStartPoint());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_Static_ConfigChangePerformFalse
 * @tc.desc: Static EndPoint with resObj returns early when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_Static_ConfigChangePerformFalse, TestSize.Level1)
{
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    if (pattern->resourceMgr_ == nullptr) {
        pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    }
    auto initialSize = pattern->resourceMgr_->resMap_.size();

    g_isConfigChangePerform = false;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray;
    LineModelNG::EndPoint(AceType::RawPtr(frameNode), point, resObjArray);

    EXPECT_EQ(pattern->resourceMgr_->resMap_.size(), initialSize);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_Static_NullFrameNode
 * @tc.desc: Static EndPoint with resObj returns early when frameNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_Static_NullFrameNode, TestSize.Level1)
{
    auto observerNode = CreateLineFrameNode();
    ASSERT_NE(observerNode, nullptr);
    auto paintProperty = observerNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray;
    LineModelNG::EndPoint(nullptr, point, resObjArray);

    EXPECT_FALSE(paintProperty->HasEndPoint());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_WrongSize
 * @tc.desc: StartPoint resObj lambda returns early when array size is not 2
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_WrongSize, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateInvalidResObj() };
    LineModelNG::StartPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_FALSE(paintProperty->HasStartPoint());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_BothInvalid
 * @tc.desc: StartPoint resObj with both invalid resObj sets dimensions to 0.0_vp
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_BothInvalid, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateInvalidResObj(), CreateInvalidResObj() };
    LineModelNG::StartPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasStartPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().first.ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().second.ConvertToPx(), 0.0f);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_FirstNullSecondInvalid
 * @tc.desc: StartPoint resObj first is null, second is invalid -> first keeps original, second becomes 0.0_vp
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_FirstNullSecondInvalid, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { nullptr, CreateInvalidResObj() };
    LineModelNG::StartPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasStartPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().first.ConvertToPx(), ORIGINAL_POINT_X);
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().second.ConvertToPx(), 0.0f);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_SecondNullFirstInvalid
 * @tc.desc: StartPoint resObj second is null, first is invalid -> first becomes 0.0_vp, second keeps original
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_SecondNullFirstInvalid, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateInvalidResObj(), nullptr };
    LineModelNG::StartPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasStartPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().first.ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().second.ConvertToPx(), ORIGINAL_POINT_Y);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_FirstNullSecondValid
 * @tc.desc: StartPoint resObj first is null, second is valid -> first keeps original, second updates
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_FirstNullSecondValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_START_Y, MOCK_DIM_Y);
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { nullptr, CreateValidResObj(ID_START_Y) };
    LineModelNG::StartPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasStartPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().first.ConvertToPx(), ORIGINAL_POINT_X);
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().second.ConvertToPx(), MOCK_DIM_Y.ConvertToPx());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_SecondNullFirstValid
 * @tc.desc: StartPoint resObj second is null, first is valid -> first updates, second keeps original
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_SecondNullFirstValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_START_X, MOCK_DIM_X);
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateValidResObj(ID_START_X), nullptr };
    LineModelNG::StartPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasStartPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().first.ConvertToPx(), MOCK_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().second.ConvertToPx(), ORIGINAL_POINT_Y);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_BothValid
 * @tc.desc: StartPoint resObj both valid -> both dimensions update from mock data
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_BothValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_START_X, MOCK_DIM_X);
    AddMockResourceData(ID_START_Y, MOCK_DIM_Y);
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateValidResObj(ID_START_X), CreateValidResObj(ID_START_Y) };
    LineModelNG::StartPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasStartPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().first.ConvertToPx(), MOCK_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().second.ConvertToPx(), MOCK_DIM_Y.ConvertToPx());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_RerenderableFalse
 * @tc.desc: StartPoint resObj updates property when frameNode is not rerenderable
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_RerenderableFalse, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_START_X, MOCK_DIM_X);
    AddMockResourceData(ID_START_Y, MOCK_DIM_Y);
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->SetRerenderable(false);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateValidResObj(ID_START_X), CreateValidResObj(ID_START_Y) };
    LineModelNG::StartPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasStartPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().first.ConvertToPx(), MOCK_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().second.ConvertToPx(), MOCK_DIM_Y.ConvertToPx());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_WrongSize
 * @tc.desc: EndPoint resObj lambda returns early when array size is not 2
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_WrongSize, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateInvalidResObj() };
    LineModelNG::EndPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_FALSE(paintProperty->HasEndPoint());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_BothInvalid
 * @tc.desc: EndPoint resObj with both invalid resObj sets dimensions to 0.0_vp
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_BothInvalid, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateInvalidResObj(), CreateInvalidResObj() };
    LineModelNG::EndPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasEndPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().first.ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().second.ConvertToPx(), 0.0f);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_FirstNullSecondInvalid
 * @tc.desc: EndPoint resObj first is null, second is invalid -> first keeps original, second becomes 0.0_vp
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_FirstNullSecondInvalid, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { nullptr, CreateInvalidResObj() };
    LineModelNG::EndPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasEndPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().first.ConvertToPx(), ORIGINAL_POINT_X);
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().second.ConvertToPx(), 0.0f);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_SecondNullFirstInvalid
 * @tc.desc: EndPoint resObj second is null, first is invalid -> first becomes 0.0_vp, second keeps original
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_SecondNullFirstInvalid, TestSize.Level1)
{
    ResetMockResourceData();
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateInvalidResObj(), nullptr };
    LineModelNG::EndPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasEndPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().first.ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().second.ConvertToPx(), ORIGINAL_POINT_Y);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_FirstNullSecondValid
 * @tc.desc: EndPoint resObj first is null, second is valid -> first keeps original, second updates
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_FirstNullSecondValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_END_Y, MOCK_DIM_Y);
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { nullptr, CreateValidResObj(ID_END_Y) };
    LineModelNG::EndPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasEndPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().first.ConvertToPx(), ORIGINAL_POINT_X);
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().second.ConvertToPx(), MOCK_DIM_Y.ConvertToPx());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_SecondNullFirstValid
 * @tc.desc: EndPoint resObj second is null, first is valid -> first updates, second keeps original
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_SecondNullFirstValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_END_X, MOCK_DIM_X);
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateValidResObj(ID_END_X), nullptr };
    LineModelNG::EndPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasEndPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().first.ConvertToPx(), MOCK_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().second.ConvertToPx(), ORIGINAL_POINT_Y);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_BothValid
 * @tc.desc: EndPoint resObj both valid -> both dimensions update from mock data
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_BothValid, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_END_X, MOCK_DIM_X);
    AddMockResourceData(ID_END_Y, MOCK_DIM_Y);
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateValidResObj(ID_END_X), CreateValidResObj(ID_END_Y) };
    LineModelNG::EndPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasEndPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().first.ConvertToPx(), MOCK_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().second.ConvertToPx(), MOCK_DIM_Y.ConvertToPx());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_RerenderableFalse
 * @tc.desc: EndPoint resObj updates property when frameNode is not rerenderable
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_RerenderableFalse, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_END_X, MOCK_DIM_X);
    AddMockResourceData(ID_END_Y, MOCK_DIM_Y);
    auto frameNode = CreateLineFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->SetRerenderable(false);
    auto pattern = frameNode->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateValidResObj(ID_END_X), CreateValidResObj(ID_END_Y) };
    LineModelNG::EndPoint(AceType::RawPtr(frameNode), point, resObjArray);
    pattern->resourceMgr_->ReloadResources();

    EXPECT_TRUE(paintProperty->HasEndPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().first.ConvertToPx(), MOCK_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().second.ConvertToPx(), MOCK_DIM_Y.ConvertToPx());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_NonStatic_ConfigChangePerformTrue
 * @tc.desc: Non-static StartPoint delegates to static version when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_NonStatic_ConfigChangePerformTrue, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_START_X, MOCK_DIM_X);
    AddMockResourceData(ID_START_Y, MOCK_DIM_Y);

    auto pattern = frameNode_->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    if (pattern->resourceMgr_ == nullptr) {
        pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    }
    auto initialSize = pattern->resourceMgr_->resMap_.size();

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateValidResObj(ID_START_X), CreateValidResObj(ID_START_Y) };
    LineModelNG().StartPoint(point, resObjArray);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);

    pattern->resourceMgr_->ReloadResources();
    auto paintProperty = frameNode_->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasStartPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().first.ConvertToPx(), MOCK_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetStartPointValue().second.ConvertToPx(), MOCK_DIM_Y.ConvertToPx());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_NonStatic_ConfigChangePerformTrue
 * @tc.desc: Non-static EndPoint delegates to static version when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_NonStatic_ConfigChangePerformTrue, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_END_X, MOCK_DIM_X);
    AddMockResourceData(ID_END_Y, MOCK_DIM_Y);

    auto pattern = frameNode_->GetPattern<LinePattern>();
    ASSERT_NE(pattern, nullptr);
    if (pattern->resourceMgr_ == nullptr) {
        pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    }
    auto initialSize = pattern->resourceMgr_->resMap_.size();

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateValidResObj(ID_END_X), CreateValidResObj(ID_END_Y) };
    LineModelNG().EndPoint(point, resObjArray);

    EXPECT_GT(pattern->resourceMgr_->resMap_.size(), initialSize);

    pattern->resourceMgr_->ReloadResources();
    auto paintProperty = frameNode_->GetPaintProperty<LinePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasEndPoint());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().first.ConvertToPx(), MOCK_DIM_X.ConvertToPx());
    EXPECT_FLOAT_EQ(paintProperty->GetEndPointValue().second.ConvertToPx(), MOCK_DIM_Y.ConvertToPx());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_Static_NullPattern
 * @tc.desc: Static StartPoint returns early when frameNode has no ShapePattern
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_Static_NullPattern, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    RefPtr<FrameNode> nonShapeNode = FrameNode::GetOrCreateFrameNode(
        "DummyTag", nodeId, []() { return AceType::MakeRefPtr<ShapeContainerPattern>(); });
    ASSERT_NE(nonShapeNode, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateInvalidResObj(), CreateInvalidResObj() };

    LineModelNG::StartPoint(AceType::RawPtr(nonShapeNode), point, resObjArray);

    auto paintProperty = nonShapeNode->GetPaintProperty<LinePaintProperty>();
    EXPECT_EQ(paintProperty, nullptr);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_EndPointResObj_Static_NullPattern
 * @tc.desc: Static EndPoint returns early when frameNode has no ShapePattern
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_Static_NullPattern, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    RefPtr<FrameNode> nonShapeNode = FrameNode::GetOrCreateFrameNode(
        "DummyTag2", nodeId, []() { return AceType::MakeRefPtr<ShapeContainerPattern>(); });
    ASSERT_NE(nonShapeNode, nullptr);

    g_isConfigChangePerform = true;
    ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
    std::vector<RefPtr<ResourceObject>> resObjArray = { CreateInvalidResObj(), CreateInvalidResObj() };

    LineModelNG::EndPoint(AceType::RawPtr(nonShapeNode), point, resObjArray);

    auto paintProperty = nonShapeNode->GetPaintProperty<LinePaintProperty>();
    EXPECT_EQ(paintProperty, nullptr);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: LineModelNG_StartPointResObj_WeakExpired
 * @tc.desc: StartPoint lambda returns early when frameNode weak reference has expired
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_StartPointResObj_WeakExpired, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_START_X, MOCK_DIM_X);
    AddMockResourceData(ID_START_Y, MOCK_DIM_Y);

    RefPtr<PatternResourceManager> savedResourceMgr;
    size_t initialResMapSize = 0;
    {
        auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
        RefPtr<FrameNode> scopedNode = FrameNode::GetOrCreateFrameNode(
            V2::LINE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinePattern>(); });
        ASSERT_NE(scopedNode, nullptr);

        auto pattern = scopedNode->GetPattern<LinePattern>();
        ASSERT_NE(pattern, nullptr);

        g_isConfigChangePerform = true;
        ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
        std::vector<RefPtr<ResourceObject>> resObjArray = {
            CreateValidResObj(ID_START_X), CreateValidResObj(ID_START_Y) };
        LineModelNG::StartPoint(AceType::RawPtr(scopedNode), point, resObjArray);

        savedResourceMgr = pattern->resourceMgr_;
        ASSERT_NE(savedResourceMgr, nullptr);
        initialResMapSize = savedResourceMgr->resMap_.size();
        EXPECT_GT(initialResMapSize, static_cast<size_t>(0));

        g_isConfigChangePerform = false;
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
    }

    // ReloadResources completes without crash when weak reference has expired
    savedResourceMgr->ReloadResources();
    // resMap still contains registered entry (lambda cannot execute but entry remains)
    EXPECT_EQ(savedResourceMgr->resMap_.size(), initialResMapSize);
}

/**
 * @tc.name: LineModelNG_EndPointResObj_WeakExpired
 * @tc.desc: EndPoint lambda returns early when frameNode weak reference has expired
 * @tc.type: FUNC
 */
HWTEST_F(LinePatternTddTestNg, LineModelNG_EndPointResObj_WeakExpired, TestSize.Level1)
{
    ResetMockResourceData();
    AddMockResourceData(ID_END_X, MOCK_DIM_X);
    AddMockResourceData(ID_END_Y, MOCK_DIM_Y);

    RefPtr<PatternResourceManager> savedResourceMgr;
    size_t initialResMapSize = 0;
    {
        auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
        RefPtr<FrameNode> scopedNode = FrameNode::GetOrCreateFrameNode(
            V2::LINE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinePattern>(); });
        ASSERT_NE(scopedNode, nullptr);

        auto pattern = scopedNode->GetPattern<LinePattern>();
        ASSERT_NE(pattern, nullptr);

        g_isConfigChangePerform = true;
        ShapePoint point{Dimension(ORIGINAL_POINT_X), Dimension(ORIGINAL_POINT_Y)};
        std::vector<RefPtr<ResourceObject>> resObjArray = {
            CreateValidResObj(ID_END_X), CreateValidResObj(ID_END_Y) };
        LineModelNG::EndPoint(AceType::RawPtr(scopedNode), point, resObjArray);

        savedResourceMgr = pattern->resourceMgr_;
        ASSERT_NE(savedResourceMgr, nullptr);
        initialResMapSize = savedResourceMgr->resMap_.size();
        EXPECT_GT(initialResMapSize, static_cast<size_t>(0));

        g_isConfigChangePerform = false;
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
    }

    // ReloadResources completes without crash when weak reference has expired
    savedResourceMgr->ReloadResources();
    EXPECT_EQ(savedResourceMgr->resMap_.size(), initialResMapSize);
}

} // namespace OHOS::Ace::NG
