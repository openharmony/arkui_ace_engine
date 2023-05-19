/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"

#include "base/geometry/ng/point_t.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_node.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_paint_property.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string BUNDLE_NAME = "com.example.hello";
const std::string ABILITY_NAME = "MainAbility";
const std::string WANT = R"({bundleName: "com.example.hello", abilityName: "MainAbility"})";
const int32_t NODE_ID = 1000;
} // namespace

class UIExtensionPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: UIExtensionCreator001
 * @tc.desc: create UIExtension
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(UIExtensionPatternTestNg, UIExtensionCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create UIExtension Component.
     */
    auto model = UIExtensionModelNG();
    model.Create(BUNDLE_NAME, ABILITY_NAME);
    model.SetWant(WANT);

    /**
     * @tc.steps: step1. Create UIExtension component.
     * @tc.expected: expect paintProperty want
     */
    auto uiExtensionNode =
        AceType::DynamicCast<UIExtensionNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto paintProperty = uiExtensionNode->GetPaintProperty<UIExtensionPaintProperty>();
    EXPECT_EQ(paintProperty->GetWantValue(), WANT);
}

/**
 * @tc.name: UIExtensionCreator002
 * @tc.desc: create UIExtension and get uiExtensionNode to dispatch event
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(UIExtensionPatternTestNg, UIExtensionCreator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create or create UIExtension component.
     */
    auto model = UIExtensionModelNG();
    model.Create(BUNDLE_NAME, ABILITY_NAME);

    auto uiExtensionNode =
        AceType::DynamicCast<UIExtensionNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    TouchRestrict touchRestrict;
    TouchTestResult testResult;
    auto result = uiExtensionNode->TouchTest(PointF(), PointF(), touchRestrict, testResult, 1);
    EXPECT_EQ(static_cast<int>(HitTestResult::BUBBLING), static_cast<int>(result));
    auto result2 = uiExtensionNode->TouchTest(PointF(), PointF(10, 10), touchRestrict, testResult, 1);
    EXPECT_EQ(static_cast<int>(HitTestResult::OUT_OF_REGION), static_cast<int>(result2));
}

/**
 * @tc.name: UIExtensionCreator003
 * @tc.desc: create UIExtension and run GetOrCreateUIExtensionNode success
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(UIExtensionPatternTestNg, UIExtensionCreator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create or create UIExtension component.
     * @tc.expect: Create or create UIExtension component success.
     */
    auto uiExtensionNode = UIExtensionNode::GetOrCreateUIExtensionNode(
        "UIExtensionNodeTag", NODE_ID, []() { return AceType::MakeRefPtr<Pattern>(); });
    EXPECT_NE(uiExtensionNode, nullptr);

    /**
     * @tc.steps: step2. Create or create UIExtension component.
     * @tc.expect: component equal
     */
    auto uiExtensionNodeTemp1 = UIExtensionNode::GetOrCreateUIExtensionNode(
        "UIExtensionNodeTag", NODE_ID, []() { return AceType::MakeRefPtr<Pattern>(); });
    EXPECT_EQ(uiExtensionNode, uiExtensionNodeTemp1);

    /**
     * @tc.steps: step3. Create or create UIExtension component.
     * @tc.expect: component not equal
     */
    auto uiExtensionNodeTemp2 = UIExtensionNode::GetOrCreateUIExtensionNode(
        "UIExtensionNodeTag1", NODE_ID, []() { return AceType::MakeRefPtr<Pattern>(); });
    EXPECT_NE(uiExtensionNode, uiExtensionNodeTemp2);

    /**
     * @tc.steps: step4. Create or create UIExtension component.
     * @tc.expect: Create or create UIExtension component success.
     */
    auto parent = UIExtensionNode::GetOrCreateUIExtensionNode(
        "UIExtensionNodeTagParent", NODE_ID + 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    EXPECT_NE(parent, nullptr);

    /**
     * @tc.steps: step4. Create or create UIExtension component and set parent.
     * @tc.expect: Create or create UIExtension component and set parent success.
     */
    uiExtensionNodeTemp2->SetParent(parent);
    uiExtensionNodeTemp2 = UIExtensionNode::GetOrCreateUIExtensionNode(
        "UIExtensionNodeTag1", NODE_ID, []() { return AceType::MakeRefPtr<Pattern>(); });
    EXPECT_NE(uiExtensionNodeTemp2->GetParent(), nullptr);
}

/**
 * @tc.name: UIExtensionCreator004
 * @tc.desc: create UIExtension and run TouchTest success
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(UIExtensionPatternTestNg, UIExtensionCreator004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pipeline and container
     * @tc.steps: step1. Create or create UIExtension component.
     * @tc.expect: Create or create UIExtension component success.
     */
    MockPipelineBase::SetUp();
    MockContainer::SetUp();
    MockContainer::container_->pipelineContext_ = MockPipelineBase::pipeline_;
    auto container = Container::Current();
    EXPECT_NE(container, nullptr);
    auto context = container->GetPipelineContext();
    EXPECT_NE(context, nullptr);
    auto model = UIExtensionModelNG();
    model.Create(BUNDLE_NAME, ABILITY_NAME);

    auto uiExtensionNode =
        AceType::DynamicCast<UIExtensionNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    TouchRestrict touchRestrict;
    TouchTestResult testResult;

    /**
     * @tc.expect: result equals with BUBBLING
     */
    auto result = uiExtensionNode->TouchTest(PointF(), PointF(), touchRestrict, testResult, 1);
    EXPECT_EQ(static_cast<int>(HitTestResult::BUBBLING), static_cast<int>(result));
    MockPipelineBase::TearDown();
    MockContainer::TearDown();
}
} // namespace OHOS::Ace::NG
