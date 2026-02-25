/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "divider_base_test_ng.h"

#include "core/components_ng/property/layout_constraint.h"
#include "core/common/resource/resource_parse_utils.h"
#include "frameworks/base/memory/ace_type.h"
#include "interfaces/inner_api/ace_kit/include/ui/resource/resource_object.h"
#include "test/mock/base/mock_system_properties.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {} // namespace
class DividerNewTestNG : public DividerBaseTestNG {};

/**
 * @tc.name: DividerLengthTests
 * @tc.desc: percentRef > maxSize, horizontal.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, DividerLengthTest01, TestSize.Level0)
{
    // step: make percentRef > maxSize
    OHOS::Ace::NG::LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = SizeF(200, 200);
    parentConstraint.percentReference = SizeF(300, 300);

    auto frameNode = CreateDivider([this](DividerModelNG model) {});
    frameNode->GetGeometryNode()->SetParentLayoutConstraint(parentConstraint);
    CreateLayoutTask(frameNode);

    auto pattern = OHOS::Ace::AceType::DynamicCast<DividerPattern>(frameNode->GetPattern());

    // expect: divider length = 200
    EXPECT_EQ(pattern->dividerLength_, 200.0f);
}

/**
 * @tc.name: DividerLengthTests
 * @tc.desc: percentRef > maxSize, vertical
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, DividerLengthTest02, TestSize.Level0)
{
    // step: make percentRef > maxSize
    OHOS::Ace::NG::LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = SizeF(200, 100);
    parentConstraint.percentReference = SizeF(300, 300);

    auto frameNode = CreateDivider([this](DividerModelNG model) { model.Vertical(true); });
    frameNode->GetGeometryNode()->SetParentLayoutConstraint(parentConstraint);
    CreateLayoutTask(frameNode);

    auto pattern = OHOS::Ace::AceType::DynamicCast<DividerPattern>(frameNode->GetPattern());
    EXPECT_EQ(pattern->dividerLength_, 100.0f);
}

/**
 * @tc.name: LayoutPolicyTest001
 * @tc.desc: test the measure result when setting matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LayoutPolicyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        divider = CreateDivider([this](DividerModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Divider()
            .width(LayoutPolicy.matchParent)
            .height(LayoutPolicy.matchParent)
        }
        .width("500px")
        .height("300px")
    */

    // Expect stack's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect divider's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = divider->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest002
 * @tc.desc: test the measure result when setting matchParent and parent has padding.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LayoutPolicyTest002, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        ViewAbstract::SetPadding(CalcLength(20));
        divider = CreateDivider([this](DividerModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Divider()
            .width(LayoutPolicy.matchParent)
            .height(LayoutPolicy.matchParent)
        }
        .width("500px")
        .height("300px")
        .padding("20px")
    */

    // Expect stack's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect divider's width is 460, height is 260 and offset is [20.0, 20.0].
    auto geometryNode1 = divider->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(460.0f, 260.0f));
    EXPECT_EQ(offset1, OffsetF(20.0f, 20.0f));
}

/**
 * @tc.name: LayoutPolicyTest003
 * @tc.desc: test the measure result when setting wrapContent.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LayoutPolicyTest003, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(200));
        divider = CreateDivider([this](DividerModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            model.StrokeWidth(Dimension(20));
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Divider()
            .strokeWidth("20px")
            .width(LayoutPolicy.wrapContent)
            .height(LayoutPolicy.wrapContent)
        }
        .width("200px")
        .height("200px")
    */

    // Expect stack's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect divider's width is 0, height is 20 and offset is [100.0, 90.0].
    auto geometryNode1 = divider->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(0.0f, 20.0f));
    EXPECT_EQ(offset1, OffsetF(100.0f, 90.0f));
}

/**
 * @tc.name: LayoutPolicyTest004
 * @tc.desc: test the measure result when setting wrapContent.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LayoutPolicyTest004, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(200));
        divider = CreateDivider([this](DividerModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            model.Vertical(true);
            model.StrokeWidth(Dimension(20));
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Divider()
            .strokeWidth("20px")
            .width(LayoutPolicy.wrapContent)
            .height(LayoutPolicy.wrapContent)
            .vertical(true)
        }
        .width("200px")
        .height("200px")
    */

    // Expect stack's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect divider's width is 20, height is 0 and offset is [90.0, 100.0].
    auto geometryNode1 = divider->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(20.0f, 0.0f));
    EXPECT_EQ(offset1, OffsetF(90.0f, 100.0f));
}

/**
 * @tc.name: LayoutPolicyTest005
 * @tc.desc: test the measure result when setting fixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LayoutPolicyTest005, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(200));
        divider = CreateDivider([this](DividerModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
            model.StrokeWidth(Dimension(20));
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Divider()
            .strokeWidth("20px")
            .width(LayoutPolicy.fixAtIdealSize)
            .height(LayoutPolicy.fixAtIdealSize)
        }
        .width("200px")
        .height("200px")
    */

    // Expect stack's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect divider's width is 0, height is 20 and offset is [100.0, 90.0].
    auto geometryNode1 = divider->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(0.0f, 20.0f));
    EXPECT_EQ(offset1, OffsetF(100.0f, 90.0f));
}

/**
 * @tc.name: LayoutPolicyTest006
 * @tc.desc: test the measure result when setting fixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LayoutPolicyTest006, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(200));
        divider = CreateDivider([this](DividerModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
            model.Vertical(true);
            model.StrokeWidth(Dimension(20));
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Divider()
            .strokeWidth("20px")
            .width(LayoutPolicy.fixAtIdealSize)
            .height(LayoutPolicy.fixAtIdealSize)
            .vertical(true)
        }
        .width("200px")
        .height("200px")
    */

    // Expect stack's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect divider's width is 20, height is 0 and offset is [90.0, 100.0].
    auto geometryNode1 = divider->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(20.0f, 0.0f));
    EXPECT_EQ(offset1, OffsetF(90.0f, 100.0f));
}

/**
 * @tc.name: CreateFrameNodeTest001
 * @tc.desc: test CreateFrameNode static method
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, CreateFrameNodeTest001, TestSize.Level0)
{
    int32_t nodeId = 100;
    auto frameNode = DividerModelNG::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetId(), nodeId);
}

/**
 * @tc.name: DividerColorSetByUserTest001
 * @tc.desc: test DividerColor set DividerColorSetByUser when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, DividerColorSetByUserTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::RED);
    });
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    OHOS::Ace::g_isConfigChangePerform = true;
    // Push frameNode to ViewStack to make it the current main frame node
    auto* viewStack = ViewStackProcessor::GetInstance();
    viewStack->Push(frameNode);
    DividerModelNG model;
    model.DividerColor(Color::RED);
    EXPECT_EQ(paintProperty->GetDividerColorSetByUser().value_or(false), true);
    OHOS::Ace::g_isConfigChangePerform = false;
    // Clean up view stack
    viewStack->Pop();
}

/**
 * @tc.name: ResetResObjTest001
 * @tc.desc: test ResetResObj when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, ResetResObjTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    // Add a res cache first
    pattern->AddResCache("test.key", "test.value");

    OHOS::Ace::g_isConfigChangePerform = true;
    // Push frameNode to ViewStack to make it the current main frame node
    auto* viewStack = ViewStackProcessor::GetInstance();
    viewStack->Push(frameNode);
    DividerModelNG model;
    model.ResetResObj("test.key");
    EXPECT_TRUE(pattern->GetResCacheMapByKey("test.key").empty());
    OHOS::Ace::g_isConfigChangePerform = false;
    // Clean up view stack
    viewStack->Pop();
}

/**
 * @tc.name: ResetResObjTest002
 * @tc.desc: test ResetResObj when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, ResetResObjTest002, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    // Add a res cache first
    pattern->AddResCache("test.key", "test.value");

    OHOS::Ace::g_isConfigChangePerform = false;
    DividerModelNG model;
    model.ResetResObj("test.key");
    // When ConfigChangePerform is false, ResetResObj should not clear the cache
    EXPECT_FALSE(pattern->GetResCacheMapByKey("test.key").empty());
}

/**
 * @tc.name: StrokeWidthTest001
 * @tc.desc: test StrokeWidth method
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, StrokeWidthTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(10));
    });
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetStrokeWidthValue(), Dimension(10));
}

/**
 * @tc.name: LineCapTest001
 * @tc.desc: test LineCap method
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LineCapTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.LineCap(LineCap::ROUND);
    });
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetLineCapValue(), LineCap::ROUND);
}

/**
 * @tc.name: SetDividerColorWithColorOptTest001
 * @tc.desc: test SetDividerColor with colorOpt and isSetByTheme=true
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, SetDividerColorWithColorOptTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    std::optional<Color> colorOpt = Color::BLUE;
    OHOS::Ace::g_isConfigChangePerform = true;
    DividerModelNG::SetDividerColor(frameNode.GetRawPtr(), colorOpt, true);
    EXPECT_EQ(paintProperty->GetDividerColorValue(), Color::BLUE);
    EXPECT_EQ(paintProperty->GetDividerColorSetByUser().value_or(false), true);
    OHOS::Ace::g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetDividerColorWithColorOptTest002
 * @tc.desc: test SetDividerColor with colorOpt and isSetByTheme=false
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, SetDividerColorWithColorOptTest002, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    std::optional<Color> colorOpt = Color::RED;
    OHOS::Ace::g_isConfigChangePerform = true;
    DividerModelNG::SetDividerColor(frameNode.GetRawPtr(), colorOpt, false);
    EXPECT_EQ(paintProperty->GetDividerColorValue(), Color::RED);
    EXPECT_EQ(paintProperty->GetDividerColorSetByUser().value_or(false), false);
    OHOS::Ace::g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetDividerColorWithResourceObjTest001
 * @tc.desc: test SetDividerColor with ResourceObject
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, SetDividerColorWithResourceObjTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    DividerModelNG::SetDividerColor(frameNode.GetRawPtr(), resObj, true);
    EXPECT_TRUE(paintProperty->GetDividerColorSetByUser().value_or(false));
}

/**
 * @tc.name: DividerColorWithResourceObjCacheHitTest001
 * @tc.desc: test DividerColor with ResourceObject when cache hit
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, DividerColorWithResourceObjCacheHitTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    // Pre-populate the cache with a known color
    std::string cachedColor = "#FF0000FF";
    pattern->AddResCache("divider.color", cachedColor);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    // Call DividerColor with ResourceObject - should use cached value
    DividerModelNG model;
    model.DividerColor(resObj);

    // Verify the cached color is used
    std::string actualCache = pattern->GetResCacheMapByKey("divider.color");
    EXPECT_EQ(actualCache, cachedColor);
}

/**
 * @tc.name: ResetResObjWithFrameNodeTest001
 * @tc.desc: test ResetResObj static method with FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, ResetResObjWithFrameNodeTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->AddResCache("test.key", "test.value");

    OHOS::Ace::g_isConfigChangePerform = true;
    DividerModelNG::ResetResObj(frameNode.GetRawPtr(), "test.key");
    EXPECT_TRUE(pattern->GetResCacheMapByKey("test.key").empty());
    OHOS::Ace::g_isConfigChangePerform = false;
}

/**
 * @tc.name: ResetResObjWithFrameNodeTest002
 * @tc.desc: test ResetResObj static method when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, ResetResObjWithFrameNodeTest002, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->AddResCache("test.key", "test.value");

    OHOS::Ace::g_isConfigChangePerform = false;
    DividerModelNG::ResetResObj(frameNode.GetRawPtr(), "test.key");
    EXPECT_FALSE(pattern->GetResCacheMapByKey("test.key").empty());
}

/**
 * @tc.name: ResetDividerColorTest001
 * @tc.desc: test ResetDividerColor sets DividerColorSetByUser to false
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, ResetDividerColorTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::GREEN);
    });
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    OHOS::Ace::g_isConfigChangePerform = true;
    DividerModelNG model;
    model.ResetDividerColor();
    EXPECT_EQ(paintProperty->GetDividerColorSetByUser().value_or(false), false);
    OHOS::Ace::g_isConfigChangePerform = false;
}

/**
 * @tc.name: ResetDividerColorWithFrameNodeTest001
 * @tc.desc: test ResetDividerColor(FrameNode*) sets DividerColorSetByUser to false
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, ResetDividerColorWithFrameNodeTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::GRAY);
    });
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    OHOS::Ace::g_isConfigChangePerform = true;
    DividerModelNG::ResetDividerColor(frameNode.GetRawPtr());
    EXPECT_EQ(paintProperty->GetDividerColorSetByUser().value_or(false), false);
    OHOS::Ace::g_isConfigChangePerform = false;
}
} // namespace OHOS::Ace::NG