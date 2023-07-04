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

#define private public
#include "gtest/gtest.h"

#include "test/mock/window_ng/mock_window_extension_connection_adapter_ng.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/ability_component/ability_component_event_hub.h"
#include "core/components_ng/pattern/ability_component/ability_component_model_ng.h"
#include "core/components_ng/pattern/ability_component/ability_component_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string BUNDLE_NAME = "com.test.windowextension";
const std::string ABILITY_NAME = "WindowExtAbility";
const std::string WANT = R"({bundleName: "com.test.windowextension", abilityName: "WindowExtAbility"})";
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const float IDEAL_WIDTH = 300.0f;
const float IDEAL_HEIGHT = 300.0f;
const SizeF IDEAL_SIZE(IDEAL_WIDTH, IDEAL_HEIGHT);
const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
} // namespace

class AbilityComponentPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: AbilityComponentTest001
 * @tc.desc: Test Create Object Interface.
 * @tc.type: FUNC
 */
HWTEST_F(AbilityComponentPatternTestNg, AbilityComponentTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode of abilityComponent.
     */
    AbilityComponentModelNG modelNG;
    modelNG.Create(BUNDLE_NAME, ABILITY_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get and test object of abilityComponent.
     */
    RefPtr<AbilityComponentRenderProperty> paintProperty =
        frameNode->GetPaintProperty<AbilityComponentRenderProperty>();
    EXPECT_NE(paintProperty, nullptr);
    RefPtr<AbilityComponentEventHub> eventHub = frameNode->GetEventHub<AbilityComponentEventHub>();
    EXPECT_NE(eventHub, nullptr);
    RefPtr<AbilityComponentPattern> pattern = frameNode->GetPattern<AbilityComponentPattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(layoutAlgorithm, nullptr);
}

/**
 * @tc.name: AbilityComponentTest002
 * @tc.desc: Test model setting interface of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(AbilityComponentPatternTestNg, AbilityComponentTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build event callback function.
     */
    bool flagConnect = false;
    auto onConnect = [&flagConnect]() { flagConnect = true; };
    bool flagDisConnect = false;
    auto onDisConnect = [&flagDisConnect]() { flagDisConnect = true; };
    /**
     * @tc.steps: step2. create and get frameNode of abilityComponent.
     */
    AbilityComponentModelNG modelNG;
    modelNG.Create(BUNDLE_NAME, ABILITY_NAME);
    /**
     * @tc.steps: step3. set event callback by model object.
     */
    modelNG.SetWant(WANT);
    modelNG.SetOnConnect(std::move(onConnect));
    modelNG.SetOnDisConnect(std::move(onDisConnect));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<AbilityComponentRenderProperty> paintProperty =
        frameNode->GetPaintProperty<AbilityComponentRenderProperty>();
    EXPECT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetWantValue(), WANT);
    /**
     * @tc.steps: step4. test event callback by pattern object.
     */
    RefPtr<AbilityComponentPattern> pattern = frameNode->GetPattern<AbilityComponentPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->FireConnect();
    EXPECT_EQ(flagConnect, true);
    pattern->FireDisConnect();
    EXPECT_EQ(flagDisConnect, true);
}

/**
 * @tc.name: AbilityComponentTest003
 * @tc.desc: Test event of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(AbilityComponentPatternTestNg, AbilityComponentTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build event callback function.
     */
    bool flagConnect = false;
    auto onConnect = [&flagConnect]() { flagConnect = true; };
    bool flagDisConnect = false;
    auto onDisConnect = [&flagDisConnect]() { flagDisConnect = true; };
    /**
     * @tc.steps: step2. create and get frameNode of abilityComponent.
     */
    AbilityComponentModelNG modelNG;
    modelNG.Create(BUNDLE_NAME, ABILITY_NAME);
    modelNG.SetWant(WANT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step3. put callback function by eventHub.
     */
    RefPtr<AbilityComponentEventHub> eventHub = frameNode->GetEventHub<AbilityComponentEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->SetOnConnect(std::move(onConnect));
    eventHub->SetOnDisConnect(std::move(onDisConnect));
    /**
     * @tc.steps: step4. test callback function by eventHub.
     */
    eventHub->FireOnConnect();
    EXPECT_EQ(flagConnect, true);
    eventHub->FireOnDisConnect();
    EXPECT_EQ(flagDisConnect, true);
}

/**
 * @tc.name: AbilityComponentTest004
 * @tc.desc: Test event of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(AbilityComponentPatternTestNg, AbilityComponentTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build event callback function.
     */
    bool flagConnect = false;
    auto onConnect = [&flagConnect]() { flagConnect = true; };
    bool flagDisConnect = false;
    auto onDisConnect = [&flagDisConnect]() { flagDisConnect = true; };
    /**
     * @tc.steps: step2. create and get frameNode of abilityComponent.
     */
    AbilityComponentModelNG modelNG;
    modelNG.Create(BUNDLE_NAME, ABILITY_NAME);
    modelNG.SetWant(WANT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step3. put callback function by eventHub.
     */
    RefPtr<AbilityComponentEventHub> eventHub = frameNode->GetEventHub<AbilityComponentEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->SetOnConnect(std::move(onConnect));
    eventHub->SetOnDisConnect(std::move(onDisConnect));
    /**
     * @tc.steps: step4. test callback function by pattern.
     */
    RefPtr<AbilityComponentPattern> pattern = frameNode->GetPattern<AbilityComponentPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    pattern->OnActive();
    pattern->OnInActive();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    EXPECT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.frameOffsetChange = true;
    config.frameSizeChange = true;
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    config.frameSizeChange = false;
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    config.frameOffsetChange = false;
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    config.frameSizeChange = true;
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    pattern->FireConnect();
    EXPECT_EQ(flagConnect, true);
    pattern->FireDisConnect();
    EXPECT_EQ(flagDisConnect, true);
}

/**
 * @tc.name: AbilityComponentTest005
 * @tc.desc: Test algorithm interface of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(AbilityComponentPatternTestNg, AbilityComponentTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode of abilityComponent.
     */
    AbilityComponentModelNG modelNG;
    modelNG.Create(BUNDLE_NAME, ABILITY_NAME);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::ABILITY_COMPONENT_ETS_TAG);
    /**
     * @tc.steps: step2. get and test layout object of abilityComponent.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto abilityComponentPattern = frameNode->GetPattern<AbilityComponentPattern>();
    EXPECT_NE(abilityComponentPattern, nullptr);
    auto refreshLayoutAlgorithm = abilityComponentPattern->CreateLayoutAlgorithm();
    EXPECT_NE(refreshLayoutAlgorithm, nullptr);
    auto layoutAlgorithm = abilityComponentPattern->CreateLayoutAlgorithm();
    EXPECT_NE(layoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    EXPECT_NE(layoutWrapper.GetLayoutProperty(), nullptr);
    /**
     * @tc.steps: step3. get and test layout param of abilityComponent.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    auto refreshSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(refreshSize.value_or(SizeF(0.0f, 0.0f)), MAX_SIZE);

    layoutConstraint.selfIdealSize.SetSize(IDEAL_SIZE);
    refreshSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(refreshSize.value_or(SizeF(0.0f, 0.0f)), IDEAL_SIZE);
}

/**
 * @tc.name: AbilityComponentTest006
 * @tc.desc: Test algorithm interface of refresh.
 * @tc.type: FUNC
 */
HWTEST_F(AbilityComponentPatternTestNg, AbilityComponentTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set pipeline and create and get frameNode of abilityComponent.
     */
    MockPipelineBase::SetUp();
    AbilityComponentModelNG modelNG;
    modelNG.Create(BUNDLE_NAME, ABILITY_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<AbilityComponentPattern> pattern = frameNode->GetPattern<AbilityComponentPattern>();
    EXPECT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. get rect witch will be set into pattern->lastRect_
     */
    auto host = pattern->GetHost();
    auto size = host->GetGeometryNode()->GetFrameSize();
    auto offset = host->GetTransformRelativeOffset();
    auto pipeline = PipelineContext::GetCurrentContext();
    Rect rect = pipeline->GetDisplayWindowRectInfo();
    rect = Rect(offset.GetX() + rect.Left(), offset.GetY() + rect.Top(), size.Width(), size.Height());

    /**
     * @tc.steps: step3. set hasConnectionToAbility_ with true and call UpdateWindowRect
     * @tc.expected: expect rect is not set
     */
    pattern->hasConnectionToAbility_ = true;
    pattern->UpdateWindowRect();
    EXPECT_EQ(pattern->lastRect_, rect);

    /**
     * @tc.steps: step3. set adapter_ and call OnModifyDone
     * @tc.expected: expect rect is set
     */
    pattern->adapter_ = AceType::MakeRefPtr<MockWindowExtensionConnectionAdapterNG>();
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->lastRect_, rect);

    /**
     * @tc.steps: step3. set lastRect_ and call OnModifyDone
     * @tc.expected: expect rect is reset
     */
    pattern->lastRect_.SetRect(1, 1, 1, 1);
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->lastRect_, rect);

    /**
     * @tc.steps: step3. set lastRect_ with rect and call OnModifyDone
     * @tc.expected: expect rect is set
     */
    pattern->lastRect_ = rect;
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->lastRect_, rect);

    MockPipelineBase::TearDown();
}
} // namespace OHOS::Ace::NG
