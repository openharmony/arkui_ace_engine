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

#include "gtest/gtest.h"
#define protected public
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/particle/particle_model_ng.h"
#include "core/components_ng/pattern/particle/particle_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class ParticleTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ParticleTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void ParticleTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ParticleTest001
 * @tc.desc: Test Particle Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and get pattern.
     */
    ParticleOption particleOption;
    EmitterOption emitterOption;
    particleOption.SetEmitterOption(emitterOption);
    std::list<ParticleOption> particleArray;
    particleArray.emplace_back(particleOption);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::PARTICLE_ETS_TAG, 1,
        [count = particleArray.size()]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    frameNode->renderContext_->UpdateParticleOptionArray(particleArray);

    /**
     * @tc.steps: step2. call the function OnVisibleChange.
     */
    pattern->OnAttachToMainTree();
    pattern->OnVisibleChange(false);
    EXPECT_TRUE(pattern->HaveUnVisibleParent());
    pattern->OnVisibleChange(false);
    EXPECT_TRUE(pattern->HaveUnVisibleParent());
    pattern->OnVisibleChange(true);
    EXPECT_FALSE(pattern->HaveUnVisibleParent());
}

/**
 * @tc.name: ParticleTest002
 * @tc.desc: Test Particle Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and get pattern.
     */
    ParticleOption particleOption;
    EmitterOption emitterOption;
    particleOption.SetEmitterOption(emitterOption);
    std::list<ParticleOption> particleArray;
    particleArray.emplace_back(particleOption);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::PARTICLE_ETS_TAG, 1,
        [count = particleArray.size()]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto parentNode = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    auto grandNode = FrameNode::CreateFrameNode("grand", 1, AceType::MakeRefPtr<Pattern>());
    parentNode->AddChild(frameNode);
    grandNode->AddChild(parentNode);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::VISIBLE;
    parentNode->SetLayoutProperty(layoutProperty);
    auto grandProperty = AceType::MakeRefPtr<LayoutProperty>();
    grandProperty->propVisibility_ = VisibleType::INVISIBLE;
    grandNode->SetLayoutProperty(grandProperty);
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. call the function OnAttachToMainTree.
     */
    pattern->OnAttachToMainTree();
    EXPECT_TRUE(pattern->HaveUnVisibleParent());
}

/**
 * @tc.name: ParticleTest003
 * @tc.desc: Test Particle Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and get pattern.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. create emitterProperty and disturbance.
     */
    EmitterProperty emitterOne;
    emitterOne.index = 0;
    emitterOne.position = { 1.0, 0.0 };
    emitterOne.size = { 1.0, 0.0 };
    emitterOne.emitRate = 1;
    EmitterProperty emitterTwo;
    emitterTwo.index = 1;
    emitterTwo.position = std::nullopt;
    emitterTwo.size = std::nullopt;
    emitterTwo.emitRate = std::nullopt;
    std::vector<EmitterProperty> emitterVector;
    pattern->updateEmitterPosition(emitterVector);
    emitterVector.push_back(emitterOne);
    emitterVector.push_back(emitterTwo);
    ParticleDisturbance disOne;
    ParticleDisturbance disTwo;
    ParticleDisturbance disThree;
    disTwo.shape = static_cast<ParticleDisturbanceShapeType>(3); // 3 is not a valid ParticleDisturbanceShapeType.
    disThree.shape = ParticleDisturbanceShapeType::ELLIPSE;
    std::vector<ParticleDisturbance> disturbanceVector;
    pattern->UpdateDisturbance(disturbanceVector);
    disturbanceVector.push_back(disOne);
    disturbanceVector.push_back(disTwo);
    std::vector<ParticleDisturbance> newDisturbanceVector;
    newDisturbanceVector.push_back(disOne);
    newDisturbanceVector.push_back(disThree);

    /**
     * @tc.steps: step2. call the function.
     */
    InspectorFilter testFilter;
    auto jsonValue = std::make_unique<JsonValue>();
    testFilter.AddFilterAttr("focusable");
    pattern->ToJsonValue(jsonValue, testFilter);
    pattern->UpdateDisturbance(disturbanceVector);
    pattern->updateEmitterPosition(emitterVector);
    EXPECT_EQ(pattern->GetDisturbance().size(), 2); // 2 is the size of disturbance_
    EXPECT_EQ(pattern->GetEmitterProperty().size(), 2); // 2 is the size of emitterProperty_
    pattern->ToJsonValue(jsonValue, testFilter);
    pattern->UpdateDisturbance(disturbanceVector);
    pattern->updateEmitterPosition(emitterVector);
    pattern->UpdateDisturbance(newDisturbanceVector);
    EXPECT_EQ(pattern->GetDisturbance().size(), 2); // 2 is the size of disturbance_
    EXPECT_EQ(pattern->GetEmitterProperty().size(), 2); // 2 is the size of emitterProperty_
}

/**
 * @tc.name: ParticleTest004
 * @tc.desc: Test Particle color option.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleTest004, TestSize.Level1)
{
    std::list<ParticleOption> arrayValue;
    ParticleOption option;
    /**
     * @tc.steps: step1. set color option.
     */
    ParticleColorPropertyOption colorOption;
    auto range = std::pair<Color, Color>(Color::BLACK, Color::RED);
    colorOption.SetRange(range);
    auto distributionType = DistributionType::UNIFORM;
    colorOption.SetDistribution(distributionType);
    ParticleColorPropertyUpdater updater;
    updater.SetUpdateType(UpdaterType::RANDOM);
    ParticleColorPropertyUpdaterConfig config;
    ColorParticleRandomUpdateConfig randomConfig;
    auto random = std::pair<float, float>(0, 1);
    randomConfig.SetRedRandom(random);
    config.SetRandomConfig(randomConfig);
    updater.SetConfig(config);
    colorOption.SetUpdater(updater);
    option.SetParticleColorOption(colorOption);
    ParticleFloatPropertyOption opacityOption;
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    arrayValue.push_back(option);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    ACE_UPDATE_RENDER_CONTEXT(ParticleOptionArray, arrayValue);
    auto context = frameNode->GetRenderContext();
    auto particleArray = context->GetParticleOptionArray();
    EXPECT_EQ(particleArray->size(), 1);
    auto colorOptionCache = particleArray->front();
    EXPECT_TRUE(option == colorOptionCache);
}

/**
 * @tc.name: ParticleTest005
 * @tc.desc: Test Particle color option.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleTest005, TestSize.Level1)
{
    std::list<ParticleOption> arrayValue;
    ParticleOption option;
    /**
     * @tc.steps: step1. set opacity option.
     */
    ParticleFloatPropertyOption opacityOption;
    auto range = pair<float, float>(0.0, 1.0);
    opacityOption.SetRange(range);
    auto updaterType = UpdaterType::RANDOM;
    ParticleFloatPropertyUpdater updater;
    updater.SetUpdaterType(updaterType);
    ParticleFloatPropertyUpdaterConfig config;
    auto randomConfig = pair<float, float>(0.0, 1.0);
    config.SetRandomConfig(randomConfig);
    updater.SetConfig(config);
    opacityOption.SetUpdater(updater);
    option.SetParticleOpacityOption(opacityOption);
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    arrayValue.push_back(option);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    ACE_UPDATE_RENDER_CONTEXT(ParticleOptionArray, arrayValue);
    auto context = frameNode->GetRenderContext();
    auto particleArray = context->GetParticleOptionArray();
    EXPECT_EQ(particleArray->size(), 1);
    auto opacityOptionCache = particleArray->front();
    EXPECT_TRUE(option == opacityOptionCache);
}

/**
 * @tc.name: ParticleTest006
 * @tc.desc: Test Particle accelerate option.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleTest006, TestSize.Level1)
{
    std::list<ParticleOption> arrayValue;
    ParticleOption option;
    /**
     * @tc.steps: step1. set accelerate option.
     */
    AccelerationProperty accelerationOption;
    ParticleFloatPropertyOption speed;
    auto range = pair<float, float>(0.0, 10.0);
    speed.SetRange(range);
    accelerationOption.SetSpeed(speed);
    ParticleFloatPropertyOption angle;
    angle.SetRange(range);
    accelerationOption.SetAngle(angle);
    option.SetParticleAccelerationOption(accelerationOption);
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    arrayValue.push_back(option);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    ACE_UPDATE_RENDER_CONTEXT(ParticleOptionArray, arrayValue);
    auto context = frameNode->GetRenderContext();
    auto particleArray = context->GetParticleOptionArray();
    EXPECT_EQ(particleArray->size(), 1);
    auto opacityOptionCache = particleArray->front();
    EXPECT_TRUE(option == opacityOptionCache);
}
} // namespace OHOS::Ace::NG
