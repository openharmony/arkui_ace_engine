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

/**
 * @tc.name: ParticleToJsonValue001
 * @tc.desc: Test GetEmitterJson parse.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create particle option for ParticleType::POINT.
     */
    ParticleOption particleOption;
    EmitterOption emitterOption;
    Particle particle;
    particle.SetLifeTime(0.0f);
    particle.SetLifeTimeRange(1.0f);
    particle.SetParticleType(ParticleType::POINT);
    NG::ParticleConfig particleConfig;
    NG::PointParticleParameter pointParameter;
    pointParameter.SetRadius(6);
    particleConfig.SetPointParticleParameter(pointParameter);
    particle.SetConfig(particleConfig);
    emitterOption.SetParticle(particle);
    particleOption.SetEmitterOption(emitterOption);
    std::list<ParticleOption> particleArray;
    particleArray.emplace_back(particleOption);
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    frameNode->renderContext_->UpdateParticleOptionArray(particleArray);
    /**
     * @tc.steps: step3. run GetEmitterJson.
     */
    auto objectParticlesJson = JsonUtil::Create(true);
    pattern->GetEmitterJson(objectParticlesJson, particleOption);
    /**
     * @tc.steps: step4. expect emitter properties can be matched.
     */
    auto emitterJson = objectParticlesJson->GetObject("emitter");
    auto particleJson = emitterJson->GetObject("particle");
    auto lifetime = particleJson->GetString("lifetime");
    auto lifeTimeRange = particleJson->GetString("lifetimeRange");
    auto type = particleJson->GetString("type");
    auto count = particleJson->GetString("count");
    auto radius = particleJson->GetObject("config")->GetString("radius");
    EXPECT_EQ(lifetime, "0");
    EXPECT_EQ(lifeTimeRange, "1");
    EXPECT_EQ(type, "ParticleType.POINT");
    EXPECT_EQ(count, "5");
    EXPECT_EQ(radius, "6.000000");
}

/**
 * @tc.name: ParticleToJsonValue002
 * @tc.desc: Test GetEmitterJson parse.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleToJsonValue002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create particle option for ParticleType::IMAGE.
     */
    ParticleOption particleOption;
    EmitterOption emitterOption;
    Particle particle;
    particle.SetLifeTime(0.0f);
    particle.SetLifeTimeRange(1.0f);
    particle.SetParticleType(ParticleType::IMAGE);
    NG::ParticleConfig particleConfig;
    NG::ImageParticleParameter imageParameter;
    std::string src = "imageSource";
    imageParameter.SetImageSource(src);
    auto fit = ImageFit::COVER;
    imageParameter.SetImageFit(fit);
    auto width = Dimension(10.0);
    auto height = Dimension(20.0);
    auto sizeValue = std::pair<Dimension, Dimension>(width, height);
    imageParameter.SetSize(sizeValue);
    particleConfig.SetImageParticleParameter(imageParameter);
    particle.SetConfig(particleConfig);
    emitterOption.SetParticle(particle);
    particleOption.SetEmitterOption(emitterOption);
    std::list<ParticleOption> particleArray;
    particleArray.emplace_back(particleOption);
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    frameNode->renderContext_->UpdateParticleOptionArray(particleArray);
    /**
     * @tc.steps: step3. run GetEmitterJson.
     */
    auto objectParticlesJson = JsonUtil::Create(true);
    pattern->GetEmitterJson(objectParticlesJson, particleOption);
    /**
     * @tc.steps: step4. expect emitter properties can be matched.
     */
    auto emitterJson = objectParticlesJson->GetObject("emitter");
    auto particleJson = emitterJson->GetObject("particle");
    auto lifetime = particleJson->GetString("lifetime");
    auto lifeTimeRange = particleJson->GetString("lifetimeRange");
    auto config = particleJson->GetObject("config");
    auto type = particleJson->GetString("type");
    auto imgSrc = config->GetString("src");
    auto size = config->GetString("size");
    auto imgFit = config->GetString("objectFit");
    EXPECT_EQ(lifetime, "0");
    EXPECT_EQ(lifeTimeRange, "1");
    EXPECT_EQ(type, "ParticleType.IMAGE");
    EXPECT_EQ(imgSrc, "imageSource");
    EXPECT_EQ(size, "[10.00px,20.00px]");
    EXPECT_EQ(imgFit, "ImageFit.Cover");
}

/**
 * @tc.name: ParticleToJsonValue003
 * @tc.desc: Test GetEmitterJson parse.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleToJsonValue003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create particle option for ParticleEmitterShape::CIRCLE.
     */
    ParticleOption particleOption;
    EmitterOption emitterOption;
    Particle particle;
    emitterOption.SetParticle(particle);
    emitterOption.SetEmitterRate(10);
    auto particleEmitterShape = ParticleEmitterShape::CIRCLE;
    emitterOption.SetShape(particleEmitterShape);
    CalcDimension xValue(10.0);
    CalcDimension yValue(20.0);
    auto positionValue = std::pair<Dimension, Dimension>(xValue, yValue);
    emitterOption.SetPosition(positionValue);
    particleOption.SetEmitterOption(emitterOption);
    std::list<ParticleOption> particleArray;
    particleArray.emplace_back(particleOption);
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    frameNode->renderContext_->UpdateParticleOptionArray(particleArray);
    /**
     * @tc.steps: step3. run GetEmitterJson.
     */
    auto objectParticlesJson = JsonUtil::Create(true);
    pattern->GetEmitterJson(objectParticlesJson, particleOption);
    /**
     * @tc.steps: step4. expect emitter properties can be matched.
     */
    auto emitterJson = objectParticlesJson->GetObject("emitter");
    auto emitRate = emitterJson->GetString("emitRate");
    auto shape = emitterJson->GetString("shape");
    auto position = emitterJson->GetString("position");
    EXPECT_EQ(emitRate, "10");
    EXPECT_EQ(shape, "ParticleEmitterShape.CIRCLE");
    EXPECT_EQ(position, "[10.00px,20.00px]");
}

/**
 * @tc.name: ParticleToJsonValue004
 * @tc.desc: Test GetEmitterJson parse.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleToJsonValue004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create particle option for default value.
     */
    ParticleOption particleOption;
    EmitterOption emitterOption;
    Particle particle;
    particleOption.SetEmitterOption(emitterOption);
    std::list<ParticleOption> particleArray;
    particleArray.emplace_back(particleOption);
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    frameNode->renderContext_->UpdateParticleOptionArray(particleArray);
    /**
     * @tc.steps: step3. run GetEmitterJson.
     */
    auto objectParticlesJson = JsonUtil::Create(true);
    pattern->GetEmitterJson(objectParticlesJson, particleOption);
    /**
     * @tc.steps: step4. expect emitterJson can be matched.
     */
    auto emitterJson = objectParticlesJson->GetObject("emitter");
    EXPECT_EQ(emitterJson->ToString(), "{\"particle\":{\"type\":\"ParticleType.POINT\","
                                       "\"config\":{\"radius\":\"0.000000\"},\"count\":\"5\"}}");
}

/**
 * @tc.name: ParticleToJsonValue005
 * @tc.desc: Test GetColorJson parse.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleToJsonValue005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create particle option for DistributionType::GAUSSIAN and UpdaterType::RANDOM.
     */
    std::list<ParticleOption> particleArray;
    ParticleOption particleOption;
    ParticleColorPropertyOption colorOption;
    auto range = std::pair<Color, Color>(Color::BLACK, Color::RED);
    colorOption.SetRange(range);
    auto type = DistributionType::GAUSSIAN;
    colorOption.SetDistribution(type);
    ParticleColorPropertyUpdater updater;
    updater.SetUpdateType(UpdaterType::RANDOM);
    ParticleColorPropertyUpdaterConfig config;
    ColorParticleRandomUpdateConfig randomConfig;
    auto random = std::pair<float, float>(0, 1000);
    randomConfig.SetRedRandom(random);
    config.SetRandomConfig(randomConfig);
    updater.SetConfig(config);
    colorOption.SetUpdater(updater);
    particleOption.SetParticleColorOption(colorOption);
    particleArray.emplace_back(particleOption);
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    frameNode->renderContext_->UpdateParticleOptionArray(particleArray);
    /**
     * @tc.steps: step3. run GetColorJson.
     */
    auto objectParticlesJson = JsonUtil::Create(true);
    pattern->GetColorJson(objectParticlesJson, particleOption);
    /**
     * @tc.steps: step4. expect color properties can be matched.
     */
    auto colorJson = objectParticlesJson->GetObject("color");
    auto distributionType = colorJson->GetString("distributionType");
    EXPECT_EQ(colorJson->GetString("range"), "[#FF000000,#FFFF0000]");
    EXPECT_EQ(distributionType, "DistributionType::GAUSSIAN");
    auto colorConfig = colorJson->GetObject("updater");
    EXPECT_EQ(colorConfig->ToString(),
        "{\"type\":\"ParticleUpdater.RANDOM\",\"config\":{\"r\":"
        "\"[0.000000,1000.000000]\",\"g\":\"[0.000000,0.000000]\",\"b\":\"[0.000000,0.000000]\",\"a\":"
        "\"[0.000000,0.000000]\"}}");
}

/**
 * @tc.name: ParticleToJsonValue006
 * @tc.desc: Test GetColorJson parse.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleToJsonValue006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create particle option for default value.
     */
    std::list<ParticleOption> particleArray;
    ParticleOption particleOption;
    ParticleColorPropertyOption colorOption;
    ParticleColorPropertyUpdater updater;
    colorOption.SetUpdater(updater);
    particleOption.SetParticleColorOption(colorOption);
    particleArray.emplace_back(particleOption);
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    frameNode->renderContext_->UpdateParticleOptionArray(particleArray);
    /**
     * @tc.steps: step3. run GetColorJson.
     */
    auto objectParticlesJson = JsonUtil::Create(true);
    pattern->GetColorJson(objectParticlesJson, particleOption);
    /**
     * @tc.steps: step4. expect color properties can be matched.
     */
    auto colorJson = objectParticlesJson->GetObject("color");
    EXPECT_EQ(colorJson->ToString(), "{\"range\":\"[#FF000000,#FF000000]\","
                                     "\"distributionType\":\"DistributionType::UNIFORM\",\"updater\":"
                                     "{\"type\":\"ParticleUpdater.NONE\",\"config\":\"\"}}");
}

/**
 * @tc.name: ParticleToJsonValue007
 * @tc.desc: Test GetOpacityJson parse.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleToJsonValue007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create opacity option for UpdaterType::CURVE.
     */
    std::list<ParticleOption> particleArray;
    ParticleOption particleOption;
    ParticleFloatPropertyOption opacityOption;
    auto range = pair<float, float>(0.0, 1.0);
    opacityOption.SetRange(range);
    auto updaterType = UpdaterType::CURVE;
    ParticleFloatPropertyUpdater updater;
    std::list<NG::ParticlePropertyAnimation<float>> particleAnimationFloatArray;
    ParticlePropertyAnimation<float> animationConfig;
    float from = 0.0;
    float to = 10000.0;
    animationConfig.SetFrom(from);
    animationConfig.SetTo(to);
    animationConfig.SetStartMills(-500.0);
    animationConfig.SetEndMills(500.0);
    animationConfig.SetCurve(Curves::FRICTION);
    particleAnimationFloatArray.emplace_back(animationConfig);
    NG::ParticleFloatPropertyUpdaterConfig updateConfig;
    updateConfig.SetAnimations(particleAnimationFloatArray);
    updater.SetConfig(updateConfig);
    updater.SetUpdaterType(updaterType);
    opacityOption.SetUpdater(updater);
    particleOption.SetParticleOpacityOption(opacityOption);
    particleArray.emplace_back(particleOption);
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    frameNode->renderContext_->UpdateParticleOptionArray(particleArray);
    /**
     * @tc.steps: step3. run GetOpacityJson.
     */
    auto objectParticlesJson = JsonUtil::Create(true);
    pattern->GetOpacityJson(objectParticlesJson, particleOption);
    /**
     * @tc.steps: step4. expect opacity properties can be matched.
     */
    auto opacityJson = objectParticlesJson->GetObject("opacity");
    EXPECT_EQ(opacityJson->ToString(),
        "{\"range\":\"[0.000000,1.000000]\",\"updater\":{\"type\":"
        "\"ParticleUpdater.CURVE\",\"config\":[{\"from\":\"0.000000\",\"to\":\"10000.000000\",\"startMillis\":"
        "\"-500\",\"endMillis\":\"500\",\"curve\":\"cubic-bezier(0.200000,0.000000,0.200000,1.000000)\"}]}}");
}

/**
 * @tc.name: ParticleToJsonValue008
 * @tc.desc: Test GetOpacityJson parse.
 * @tc.type: FUNC
 */
HWTEST_F(ParticleTestNg, ParticleToJsonValue008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create particle option for default value.
     */
    std::list<ParticleOption> particleArray;
    ParticleOption particleOption;
    VelocityProperty velocityOption;
    particleOption.SetParticleVelocityOption(velocityOption);
    particleArray.emplace_back(particleOption);
    /**
     * @tc.steps: step2. create frameNode and get pattern.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PARTICLE_ETS_TAG, 1, [count = 1]() { return AceType::MakeRefPtr<ParticlePattern>(count); });
    auto pattern = AceType::DynamicCast<ParticlePattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    frameNode->renderContext_->UpdateParticleOptionArray(particleArray);
    /**
     * @tc.steps: step3. run GetVelocityJson and expect velocity properties can be matched.
     */
    auto objectParticlesJson = JsonUtil::Create(true);
    pattern->GetVelocityJson(objectParticlesJson, particleOption);
    auto velocityJson = objectParticlesJson->GetObject("velocity");
    EXPECT_EQ(velocityJson->ToString(), "{\"speed\":\"[0.000000,0.000000]\","
                                        "\"angle\":\"[0.000000,0.000000]\"}");
}
} // namespace OHOS::Ace::NG
