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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_pattern.h"
#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_property.h"
#include "ui/base/geometry/ng/offset_t.h"
#include "ui/base/geometry/ng/size_t.h"
#include "ui/properties/dirty_flag.h"
#include "ui/view/frame_node.h"
#include "ui/view_factory/abstract_view_factory.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;
namespace OHOS::Ace {
class FrameNodeTest : public testing::Test {};

class TestAICaller : public AICallerHelper {
public:
    TestAICaller() = default;
    ~TestAICaller() override = default;
    bool onAIFunctionCaller(const std::string& funcName, const std::string& params) override
    {
        if (funcName.compare("Success") == 0) {
            return true;
        }
        return false;
    }
};

/**
 * @tc.name: FrameNodeTestTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest001, TestSize.Level1)
{
    constexpr char tag[] = "TEST1";
    const int32_t id = 1;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    EXPECT_EQ(frameNode->GetId(), id);
    auto nodeTag = frameNode->GetTag();
    EXPECT_EQ(tag, nodeTag);
}

/**
 * @tc.name: FrameNodeTestTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest002, TestSize.Level1)
{
    constexpr char tag[] = "TEST2";
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, 2, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    auto property = frameNode->GetProperty();
    EXPECT_TRUE(property);

    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    auto* aceNodePtr = frameNodeImpl->GetAceNodePtr();
    EXPECT_TRUE(aceNodePtr);
    auto aceNode = frameNodeImpl->GetAceNode();
    EXPECT_TRUE(aceNode);
    auto pattern = frameNodeImpl->GetPattern();
    EXPECT_TRUE(pattern);

    frameNode->Reset();
    EXPECT_FALSE(frameNodeImpl->GetAceNodePtr());
    EXPECT_FALSE(frameNodeImpl->GetAceNode());
    EXPECT_FALSE(frameNodeImpl->GetPattern());
}

/**
 * @tc.name: FrameNodeTestTest003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest003, TestSize.Level1)
{
    constexpr char tag[] = "TEST3";
    const int32_t id = 3;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    auto aceNode =
        NG::FrameNode::GetOrCreateFrameNode("TEST_ACE_NODE", 3, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_TRUE(aceNode);

    auto popAceNode = frameNodeImpl->MoveOwnershipAndGetAceNode();
    EXPECT_EQ(popAceNode->GetTag(), tag);
    EXPECT_EQ(popAceNode->GetId(), id);
    EXPECT_NE(frameNodeImpl->GetAceNodePtr(), nullptr);
}

/**
 * @tc.name: FrameNodeTestTest004
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest004, TestSize.Level1)
{
    constexpr char tag[] = "TEST4";
    const int32_t id = 4;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    frameNode->AddChild(nullptr);
    EXPECT_EQ(frameNode->GetChildren().size(), 0);

    const std::string childTag = "TEST4_CHILD";
    const int32_t childId = 4;
    auto mockPatternChild = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNodeChild = AbstractViewFactory::CreateFrameNode(childTag, childId, mockPatternChild);
    EXPECT_NE(frameNode, nullptr);
    frameNode->AddChild(frameNodeChild);
    EXPECT_EQ(frameNode->GetChildren().size(), 1);

    frameNode->RemoveChild(frameNodeChild);
    EXPECT_EQ(frameNode->GetChildren().size(), 0);
}

/**
 * @tc.name: FrameNodeTestTest005
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest005, TestSize.Level1)
{
    constexpr char tag[] = "TEST5";
    const int32_t id = 5;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    LayoutConstraintInfo constraint { .maxWidth = 100.0f, .maxHeight = 100.0f };
    frameNode->Measure(constraint);
    auto* aceNode = frameNodeImpl->GetAceNodePtr();
    ASSERT_TRUE(aceNode);
    EXPECT_TRUE(aceNode->IsActive());
    auto geometryNode = aceNode->GetGeometryNode();
    auto parentConstraint = geometryNode->GetParentLayoutConstraint();
    EXPECT_TRUE(NearEqual(parentConstraint.value().maxSize.Width(), constraint.maxWidth));
    EXPECT_TRUE(NearEqual(parentConstraint.value().maxSize.Height(), constraint.maxHeight));

    frameNode->Layout();
    auto layoutProperty = aceNode->GetLayoutProperty();
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    EXPECT_TRUE(NearEqual(layoutConstraint.value().maxSize.Width(), constraint.maxWidth));
    EXPECT_TRUE(NearEqual(layoutConstraint.value().maxSize.Height(), constraint.maxHeight));

    auto propertyChangeFlag = layoutProperty->GetPropertyChangeFlag();
    EXPECT_EQ(propertyChangeFlag, NG::PROPERTY_UPDATE_MEASURE | NG::PROPERTY_UPDATE_LAYOUT);
    frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(),
        NG::PROPERTY_UPDATE_MEASURE | NG::PROPERTY_UPDATE_LAYOUT | NG::PROPERTY_UPDATE_MEASURE_SELF);
}

/**
 * @tc.name: FrameNodeTestTest005
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest006, TestSize.Level1)
{
    constexpr char tag[] = "TEST6";
    const int32_t id = 5;

    auto aceFrameNode =
        NG::FrameNode::GetOrCreateFrameNode(tag, id, []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    auto frameNode = Kit::FrameNode::GetFrameNode(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(aceFrameNode)));
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FrameNodeTestTest007
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest007, TestSize.Level1)
{
    constexpr char tag[] = "TEST7";
    const int32_t id = 7;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    const std::string parentTag = "TEST7_PARENT";
    const int32_t parentId = 8;
    auto mockPatternParent = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNodeParent = AbstractViewFactory::CreateFrameNode(parentTag, parentId, mockPatternParent);
    EXPECT_NE(frameNodeParent, nullptr);

    EXPECT_EQ(frameNode->GetParentHandle(), nullptr);
    frameNodeParent->AddChild(frameNode);
    EXPECT_NE(frameNode->GetParentHandle(), nullptr);
}

/**
 * @tc.name: FrameNodeTestTest008
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest008, TestSize.Level1)
{
    constexpr char tag[] = "TEST8";
    const int32_t id = 8;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    frameNode->ResetCompositingFilter();
    SUCCEED();
}

/**
 * @tc.name: FrameNodeTestTest009
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest009, TestSize.Level1)
{
    constexpr char tag[] = "TEST9";
    const int32_t id = 9;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    frameNode->NeedAvoidContainerModal();
    SUCCEED();
}

/**
 * @tc.name: FrameNodeTestTest100
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest100, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST100";
    const int32_t id = 100;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: set property value, validate result.
     */
    char value[7] = "value1";
    frameNodeImpl->AddExtraCustomProperty("key", value);
    bool result = frameNodeImpl->GetExtraCustomProperty("key");
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: FrameNodeTestTest101
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest101, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST101";
    const int32_t id = 101;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: set property value, verify error result.
     */
    char value[7] = "value1";
    frameNodeImpl->AddExtraCustomProperty("key", value);
    bool result = frameNodeImpl->GetExtraCustomProperty("key1");
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameNodeTestTest102
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest102, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST102";
    const int32_t id = 102;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: set function callback, validate result.
     */
    frameNodeImpl->SetMeasureCallback([](RefPtr<FrameNode> node) -> void {});
    auto node = frameNodeImpl->PopAceNode();
    EXPECT_NE(node->measureCallback_, nullptr);
}

/**
 * @tc.name: FrameNodeTestTest103
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest103, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST103";
    const int32_t id = 103;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: set function callback, validate result.
     */
    frameNodeImpl->SetOnNodeDestroyCallback([](RefPtr<FrameNode> node) -> void {});
    auto node = frameNodeImpl->PopAceNode();
    EXPECT_NE(node->destroyCallback_, nullptr);
}

/**
 * @tc.name: FrameNodeTestTest104
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest104, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST104";
    const int32_t id = 104;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: set function callback, validate result.
     */
    frameNodeImpl->SetConfigurationUpdateCallback([](const ConfigurationChange& configurationChange) -> void {});
    auto node = frameNodeImpl->PopAceNode();
    EXPECT_NE(node->configurationUpdateCallback_, nullptr);
}

/**
 * @tc.name: FrameNodeTestTest105
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest105, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST105";
    const int32_t id = 105;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: test attach to tree.
     */
    auto node = frameNodeImpl->PopAceNode();
    node->AttachToMainTree();
    node->GetRenderContext()->RequestNextFrame();
    EXPECT_TRUE(node->IsOnMainTree());
}

/**
 * @tc.name: FrameNodeTestTest106
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest106, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST106";
    const int32_t id = 106;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: test node states.
     */
    auto node = frameNodeImpl->PopAceNode();
    node->OnWindowShow();
    node->OnWindowHide();
    node->OnWindowFocused();
    node->OnWindowUnfocused();

    NG::OnAreaChangedFunc callback = [](const NG::RectF& oldRect, const NG::OffsetF& oldOrigin, const NG::RectF& rect,
                                         const NG::OffsetF& origin) {};
    node->SetOnAreaChangeCallback(std::move(callback));
    EXPECT_NE(node->lastFrameRect_, nullptr);
    EXPECT_NE(node->lastParentOffsetToWindow_, nullptr);
}

/**
 * @tc.name: FrameNodeTestTest107
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest107, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST107";
    const int32_t id = 107;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: build a object to SetOnAreaChangeCallback.
     */
    auto node = frameNodeImpl->PopAceNode();
    NG::OnAreaChangedFunc callback = [](const NG::RectF& oldRect, const NG::OffsetF& oldOrigin, const NG::RectF& rect,
                                         const NG::OffsetF& origin) {};
    node->lastFrameRect_ = std::make_unique<NG::RectF>();
    node->SetOnAreaChangeCallback(std::move(callback));
    EXPECT_NE(node->lastFrameRect_, nullptr);
}

/**
 * @tc.name: FrameNodeTestTest108
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest108, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST108";
    const int32_t id = 108;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: test while SetOnAreaChangeCallback is nullptr.
     */
    auto node = frameNodeImpl->PopAceNode();
    node->lastParentOffsetToWindow_ = std::make_unique<NG::OffsetF>();
    node->SetOnAreaChangeCallback(nullptr);
    EXPECT_NE(node->lastParentOffsetToWindow_, nullptr);
}

/**
 * @tc.name: FrameNodeTestTest109
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest109, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST109";
    const int32_t id = 109;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: build a object to MarkModifyDone.
     */
    auto node = frameNodeImpl->PopAceNode();
    node->MarkModifyDone();
    EXPECT_TRUE(node->isRestoreInfoUsed_);
    node->isRestoreInfoUsed_ = true;
    node->MarkModifyDone();
    EXPECT_TRUE(node->isRestoreInfoUsed_);
}

/**
 * @tc.name: FrameNodeTestTest110
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest110, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST110";
    const int32_t id = 110;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: callback MarkNeedRenderOnly.
     */
    auto node = frameNodeImpl->PopAceNode();
    node->MarkNeedRenderOnly();
    auto test = node->isRenderDirtyMarked_ = false;
    auto test1 = node->isLayoutDirtyMarked_ = false;
    node->MarkNeedRender(false);
    node->MarkNeedRender(true);
    EXPECT_FALSE(test);
    EXPECT_FALSE(test1);
}

/**
 * @tc.name: FrameNodeTestTest111
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest111, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST111";
    const int32_t id = 111;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: callback IsNeedRequestParentMeasure.
     */
    auto node = frameNodeImpl->PopAceNode();
    auto test = node->IsNeedRequestParentMeasure();
    EXPECT_TRUE(test);

    node->layoutProperty_->propertyChangeFlag_ = NG::PROPERTY_UPDATE_BY_CHILD_REQUEST;
    node->IsNeedRequestParentMeasure();

    node->layoutProperty_->propertyChangeFlag_ = NG::PROPERTY_UPDATE_BY_CHILD_REQUEST;
    node->layoutProperty_->calcLayoutConstraint_ = std::make_unique<NG::MeasureProperty>();
    auto test1 = node->IsNeedRequestParentMeasure();
    EXPECT_TRUE(test1);
}

/**
 * @tc.name: FrameNodeTestTest112
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest112, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST112";
    const int32_t id = 112;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: callback IsOutOfTouchTestRegion.
     */
    auto node = frameNodeImpl->PopAceNode();
    NG::PointF pointF;
    std::vector<NG::RectF> rectF;
    TouchEvent touchEvent;
    auto test = node->IsOutOfTouchTestRegion(std::move(pointF), touchEvent);
    EXPECT_TRUE(test);

    auto test1 = node->InResponseRegionList(pointF, rectF);
    auto test2 = node->IsOutOfTouchTestRegion(std::move(pointF), touchEvent);
    EXPECT_FALSE(test1);
    EXPECT_TRUE(test2);
}

/**
 * @tc.name: FrameNodeTestTest113
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest113, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST113";
    const int32_t id = 113;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: test CalculateCurrentVisibleRatio.
     */
    auto node = frameNodeImpl->PopAceNode();
    NG::RectF visibleRect;
    NG::RectF renderRect;
    node->CalculateCurrentVisibleRatio(visibleRect, renderRect);
    EXPECT_EQ(visibleRect.Width(), 0);
    EXPECT_EQ(renderRect.Width(), 0);

    /**
     * @tc.steps3: set wrong value.
     */
    renderRect.SetWidth(-1);
    EXPECT_EQ(node->CalculateCurrentVisibleRatio(visibleRect, renderRect), 0);
    visibleRect.SetWidth(-1);
    EXPECT_EQ(node->CalculateCurrentVisibleRatio(visibleRect, renderRect), 0);
}

/**
 * @tc.name: FrameNodeTestTest114
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest114, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST114";
    const int32_t id = 114;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: init a vector for preparing for args, then set a flag.
     */
    auto node = frameNodeImpl->PopAceNode();
    std::vector<double> visibleAreaRatios { 0.2, 0.8, 0.21, 0.79, 0.5 };
    int flag = 0;
    auto defaultCallback = [&flag](bool input1, double input2) { flag += 1; };
    VisibleCallbackInfo callbackInfo { defaultCallback, 1.0, false };

    /**
     * @tc.steps2: call ProcessAllVisibleCallback with 0.5 from 0.
     */
    node->ProcessAllVisibleCallback(visibleAreaRatios, callbackInfo, 0.5, 0);
    EXPECT_EQ(flag, 1);

    /**
     * @tc.steps2: call ProcessAllVisibleCallback with 0 from 0.5.
     */
    node->ProcessAllVisibleCallback(visibleAreaRatios, callbackInfo, 0, 0.5);
    EXPECT_EQ(flag, 2);

    /**
     * @tc.steps2: call ProcessAllVisibleCallback with 0 from 0.
     */
    node->ProcessAllVisibleCallback(visibleAreaRatios, callbackInfo, 0, 0);
    EXPECT_EQ(flag, 2);

    /**
     * @tc.steps2: call ProcessAllVisibleCallback with 1 from 0.
     */
    node->ProcessAllVisibleCallback(visibleAreaRatios, callbackInfo, 1, 0);
    EXPECT_EQ(flag, 3);

    /**
     * @tc.steps2: call ProcessAllVisibleCallback with 1 from 1.
     */
    node->ProcessAllVisibleCallback(visibleAreaRatios, callbackInfo, 1, 1);
    EXPECT_EQ(flag, 3);
}

/**
 * @tc.name: FrameNodeTestTest114
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest115, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST115";
    const int32_t id = 115;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    ASSERT_TRUE(frameNodeImpl);

    /**
     * @tc.steps2: create AI helper
     */
    auto myAICaller = std::make_shared<TestAICaller>();
    /**
     * @tc.steps3: call ai function without set
     * @tc.excepted: step3 return 1 means AI helper not setted.
     */
    EXPECT_EQ(frameNodeImpl->frameNode_->CallAIFunction("Success", ""), 1);
    /**
     * @tc.steps4: set ai helper instance.
     * @tc.excepted: step4 AI helper not null and setted success.
     */
    frameNodeImpl->SetAICallerHelper(myAICaller);
    EXPECT_EQ(frameNodeImpl->frameNode_->aiCallerHelper_, myAICaller);
    /**
     * @tc.steps5: call ai function success after set.
     * @tc.excepted: step5 ai function called success.
     */
    EXPECT_EQ(frameNodeImpl->frameNode_->CallAIFunction("Success", "params1: 1"), 0);
    /**
     * @tc.steps6: call invalid function after set.
     * @tc.excepted: step6 ai function not found and return 2.
     */
    EXPECT_EQ(frameNodeImpl->frameNode_->CallAIFunction("OTHERFunction", "params1: 1"), 2);
}

/**
 * @tc.name: FrameNodeTestTest116
 * @tc.desc: test GetParentGlobalOffsetDuringLayout
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest116, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST116";
    const int32_t id = 116;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps2: test GetParentGlobalOffsetDuringLayout.
     */
    auto offset = frameNode->GetParentGlobalOffsetDuringLayout();
    EXPECT_TRUE(NearEqual(offset.GetX(), 0.0f));
    EXPECT_TRUE(NearEqual(offset.GetY(), 0.0f));
}

/**
 * @tc.name: FrameNodeTestTest117
 * @tc.desc: test ContainerModalTitleHeight
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest117, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST117";
    const int32_t id = 117;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps2: test GetContainerModalTitleHeight.
     */
    auto titleHeight = frameNode->GetContainerModalTitleHeight();
    EXPECT_EQ(titleHeight, 0);
}

/**
 * @tc.name: FrameNodeTestTest118
 * @tc.desc: test ContainerModalButtonsOffset
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest118, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST118";
    const int32_t id = 118;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps2: test ContainerModalButtonsOffset.
     */
    auto buttonsOffset = frameNode->GetContainerModalButtonsOffset();
    EXPECT_TRUE(NearEqual(buttonsOffset.GetX(), 0.0f));
    EXPECT_TRUE(NearEqual(buttonsOffset.GetY(), 0.0f));
}

/**
 * @tc.name: FrameNodeTestTest119
 * @tc.desc: test ContainerModalButtonsSize
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTest, FrameNodeTestTest119, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    constexpr char tag[] = "TEST119";
    const int32_t id = 119;
    auto mockPattern = AceType::MakeRefPtr<MockAceKitPattern>();
    auto frameNode = AbstractViewFactory::CreateFrameNode(tag, id, mockPattern);
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps2: test ContainerModalButtonsSize.
     */
    auto buttonsSize = frameNode->GetContainerModalButtonsSize();
    EXPECT_TRUE(NearEqual(buttonsSize.Width(), 0.0f));
    EXPECT_TRUE(NearEqual(buttonsSize.Height(), 0.0f));
}
} // namespace OHOS::Ace
