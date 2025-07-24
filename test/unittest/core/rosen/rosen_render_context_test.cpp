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
#include <memory>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define private public
#define protected public

#include "test/unittest/core/rosen/rosen_render_context_test.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const char* SRC_JPG = "file://data/data/com.example.test/res/exampleAlt.jpg";

template <typename T>
bool CompareVector(const std::vector<T>& vec1, const std::vector<T>& vec2)
{
    if (vec1.size() != vec2.size()) {
        return false;
    }
    for (size_t i = 0; i != vec1.size(); ++i) {
        if (!NearEqual(vec1[i], vec2[i])) {
            return false;
        }
    }
    return true;
}
} // namespace

void RosenRenderContextTest::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void RosenRenderContextTest::TearDown()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<RosenRenderContext> RosenRenderContextTest::InitRosenRenderContext(const RefPtr<FrameNode>& frameNode)
{
    return InitRosenRenderContext(frameNode, RenderContext::ContextType::CANVAS);
}

RefPtr<RosenRenderContext> RosenRenderContextTest::InitRosenRenderContext(const RefPtr<FrameNode>& frameNode,
    const RenderContext::ContextType& type)
{
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = type;
    contextParam.surfaceName.emplace("test");
    std::optional<RenderContext::ContextParam> contextParamValue = std::make_optional(contextParam);
    rosenRenderContext->InitContext(false, contextParamValue);
    rosenRenderContext->SetHostNode(frameNode);
    return rosenRenderContext;
}

/**
 * @tc.name: RosenRenderContextTest001
 * @tc.desc: SetPivot().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    float xPivot = 10.0;
    float yPivot = 10.0;
    float zPivot = 10.0;
    rosenRenderContext->SetPivot(xPivot, yPivot, zPivot);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().x_, 10.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().y_, 10.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivotZ(), 10.0);
    xPivot = 5.0;
    rosenRenderContext->SetPivot(xPivot, yPivot, zPivot);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().x_, 5.0);
}

/**
 * @tc.name: RosenRenderContextTest002
 * @tc.desc: SetTransitionPivot().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->SetTransitionPivot(SizeF(100.0, 100.0), true);
    ScaleOptions scaleOptions;
    scaleOptions.centerX = CalcDimension(50.0, DimensionUnit::PX);
    scaleOptions.centerY = CalcDimension(50.0, DimensionUnit::PX);
    rosenRenderContext->GetOrCreateTransitionAppearing()->UpdateScale(scaleOptions);
    rosenRenderContext->SetTransitionPivot(SizeF(100.0, 100.0), true);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().x_, 0.5);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().y_, 0.5);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivotZ(), 0);
    RotateOptions rotateOptions;
    rotateOptions.centerX = CalcDimension(50.0, DimensionUnit::PX);
    rotateOptions.centerY = CalcDimension(50.0, DimensionUnit::PX);
    rotateOptions.centerZ = CalcDimension(50.0, DimensionUnit::PX);
    rosenRenderContext->GetOrCreateTransitionAppearing()->UpdateRotate(rotateOptions);
    rosenRenderContext->SetTransitionPivot(SizeF(100.0, 100.0), true);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().x_, 0.5);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().y_, 0.5);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivotZ(), 50.0);
}

/**
 * @tc.name: RosenRenderContextTest003
 * @tc.desc: SetSandBox().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest003, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    std::optional<OffsetF> parentPosition = std::make_optional(OffsetF(100.0, 100.0));
    rosenRenderContext->SetSandBox(parentPosition, false);
    EXPECT_EQ(rosenRenderContext->sandBoxCount_, 1);
    rosenRenderContext->SetSandBox(parentPosition, true);
    EXPECT_EQ(rosenRenderContext->sandBoxCount_, 1);
    rosenRenderContext->SetSandBox(std::nullopt, true);
    EXPECT_EQ(rosenRenderContext->sandBoxCount_, 0);
    rosenRenderContext->sandBoxCount_ = 2;
    rosenRenderContext->SetSandBox(std::nullopt, true);
    EXPECT_EQ(rosenRenderContext->sandBoxCount_, 0);
}

/**
 * @tc.name: RosenRenderContextTest004
 * @tc.desc: SetFrameWithoutAnimation().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest004, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    RectF paintRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    rosenRenderContext->SetFrameWithoutAnimation(paintRect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[0], paintRect.GetX());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[1], paintRect.GetY());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[2], paintRect.Width());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[3], paintRect.Height());
}

/**
 * @tc.name: RosenRenderContextTest005
 * @tc.desc: SyncGeometryFrame().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest005, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    RectF paintRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    rosenRenderContext->SyncGeometryFrame(paintRect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[0], paintRect.GetX());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[1], paintRect.GetY());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[2], paintRect.Width());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[3], paintRect.Height());
    rosenRenderContext->SyncGeometryFrame(paintRect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBounds()[0], paintRect.GetX());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBounds()[1], paintRect.GetY());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBounds()[2], paintRect.Width());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBounds()[3], paintRect.Height());
}

/**
 * @tc.name: RosenRenderContextTest006
 * @tc.desc: SetChildBounds().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest006, TestSize.Level1)
{
    auto hostNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(hostNode);
    RectF paintRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    rosenRenderContext->SetChildBounds(paintRect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetChildren().size(), 0);
    auto rosenRenderContextChild = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::CANVAS;
    contextParam.surfaceName.emplace("test1");
    std::optional<RenderContext::ContextParam> contextParamValue = std::make_optional(contextParam);
    rosenRenderContextChild->InitContext(false, contextParamValue);
    auto frameNode = FrameNode::GetOrCreateFrameNode("child", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    rosenRenderContextChild->SetHostNode(frameNode);
    rosenRenderContext->AddChild(rosenRenderContextChild, 10);
    rosenRenderContext->SetChildBounds(paintRect);
    EXPECT_EQ(rosenRenderContextChild->GetRSNode()->GetStagingProperties().GetBounds()[0], 0.0);
    EXPECT_EQ(rosenRenderContextChild->GetRSNode()->GetStagingProperties().GetBounds()[1], 0.0);
    EXPECT_EQ(rosenRenderContextChild->GetRSNode()->GetStagingProperties().GetBounds()[2], paintRect.Width());
    EXPECT_EQ(rosenRenderContextChild->GetRSNode()->GetStagingProperties().GetBounds()[3], paintRect.Height());
}

/**
 * @tc.name: RosenRenderContextTest008
 * @tc.desc: OnForegroundEffectUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest008, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->OnForegroundEffectUpdate(1.0f);
    EXPECT_TRUE(rosenRenderContext->GetRSNode()->GetStagingProperties().GetForegroundEffectRadius() - 1.0 < 1);
}

/**
 * @tc.name: RosenRenderContextTest011
 * @tc.desc: SyncGeometryFrame().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest011, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->OnOpacityUpdate(10.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetAlpha(), 10.0);
}

/**
 * @tc.name: RosenRenderContextTest012
 * @tc.desc: ConvertDimensionToScaleBySize().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest012, TestSize.Level1)
{
    Dimension dimension;
    dimension.SetUnit(DimensionUnit::FP);
    float size = 100.0;
    float ret = RosenRenderContext::ConvertDimensionToScaleBySize(dimension, size);
    EXPECT_EQ(ret == 0.5f, false);
    dimension.SetUnit(DimensionUnit::PERCENT);
    float ret2 = RosenRenderContext::ConvertDimensionToScaleBySize(dimension, size);
    EXPECT_EQ(ret2 == 0.0f, true);
}

/**
 * @tc.name: RosenRenderContextTest013
 * @tc.desc: OnNodeAppear().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest013, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // recursive is false
    rosenRenderContext->OnNodeAppear(false);
    EXPECT_TRUE(rosenRenderContext->firstTransitionIn_);
    // OnNodeAppear() recursive is true
    rosenRenderContext->OnNodeAppear(true);
    EXPECT_FALSE(rosenRenderContext->isDisappearing_);
}

/**
 * @tc.name: RosenRenderContextTest014
 * @tc.desc: CreateHardwareSurface().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest014, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    std::optional<RenderContext::ContextParam> param = std::make_optional(RenderContext::ContextParam());
    bool isTextureExportNode = true;
    std::shared_ptr<Rosen::RSUIContext> rsUIContext;
    std::shared_ptr<Rosen::RSNode> ret = rosenRenderContext->CreateHardwareSurface(
        param, isTextureExportNode, rsUIContext);
    EXPECT_FALSE(ret == nullptr);
}

/**
 * @tc.name: RosenRenderContextTest015
 * @tc.desc: SyncGeometryProperties().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest015, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    RectF paintRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    rosenRenderContext->SyncGeometryProperties(paintRect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[0], paintRect.GetX());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[1], paintRect.GetY());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[2], paintRect.Width());
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame()[3], paintRect.Height());
}

/**
 * @tc.name: RosenRenderContextTest017
 * @tc.desc: OnBackgroundImageUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest017, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // Src null,pixmap null
    ImageSourceInfo src;
    rosenRenderContext->OnBackgroundImageUpdate(src);
    EXPECT_EQ(rosenRenderContext->bgImage_, nullptr);
    EXPECT_EQ(rosenRenderContext->bgLoadingCtx_, nullptr);
    // Src null,pixmap not null
    RefPtr<PixelMap> pixmap;
    std::optional<Color> fillColor = std::make_optional(Color::BLACK);
    src.SetPixMap(pixmap, fillColor);
    rosenRenderContext->OnBackgroundImageUpdate(src);
    EXPECT_TRUE(rosenRenderContext->bgImage_ == nullptr);
    EXPECT_TRUE(rosenRenderContext->bgLoadingCtx_ == nullptr);
    // Src not null,pixmap null
    src.SetSrc("test");
    rosenRenderContext->OnBackgroundImageUpdate(src);
    EXPECT_TRUE(rosenRenderContext->bgImage_ == nullptr);
    EXPECT_TRUE(rosenRenderContext->bgLoadingCtx_ != nullptr);
}

/**
 * @tc.name: RosenRenderContextTest019
 * @tc.desc: OnParticleOptionArrayUpdate()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest019, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    std::list<ParticleOption> optionList;
    rosenRenderContext->OnParticleOptionArrayUpdate(optionList);
    EXPECT_FALSE(rosenRenderContext->particleAnimationPlaying_);
    rosenRenderContext->paintRect_ = RectT<float>(1.0f, 1.0f, 1.0f, 1.0f);
    rosenRenderContext->OnParticleOptionArrayUpdate(optionList);
    EXPECT_TRUE(rosenRenderContext->particleAnimationPlaying_);
    auto frameNode2 = FrameNode::GetOrCreateFrameNode("parent", -1, []() {
        auto pattern = AceType::MakeRefPtr<ParticlePattern>(1);
        pattern->SetHaveUnVisibleParent(true);
        return pattern;
    });
    auto rosenRenderContext2 = InitRosenRenderContext(frameNode2);
    rosenRenderContext2->paintRect_ = RectT<float>(1.0f, 1.0f, 1.0f, 1.0f);
    rosenRenderContext2->OnParticleOptionArrayUpdate(optionList);
    EXPECT_FALSE(rosenRenderContext2->particleAnimationPlaying_);
}

/**
 * @tc.name: RosenRenderContextTest020
 * @tc.desc: OnParticleOptionArrayUpdate()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest020, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params,default value,expect SetLifeTime 0.0f,SetLifeTimeRange 1.0f
    ParticleOption particleOption;
    RectF rectF;
    EmitterOption emitter;
    Particle particle;
    particle.SetLifeTime(0.0f);
    particle.SetLifeTimeRange(1.0f);
    emitter.SetParticle(particle);
    particleOption.SetEmitterOption(emitter);
    OHOS::Rosen::ParticleParams ret = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret.velocity_.velocityAngle_.start_, 0.0f);
    EXPECT_EQ(ret.velocity_.velocityAngle_.end_, 0.0f);
    // SetLifeTime 0.0f,SetLifeTimeRange 1.0f
    Particle particle2;
    particle2.SetLifeTime(-1.0f);
    particle2.SetLifeTimeRange(1.0f);
    emitter.SetParticle(particle2);
    particleOption.SetEmitterOption(emitter);
    OHOS::Rosen::ParticleParams ret2 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret2.velocity_.velocityAngle_.start_, 0.0f);
    EXPECT_EQ(ret2.velocity_.velocityAngle_.end_, 0.0f);
    // SetLifeTime 1.0f,SetLifeTimeRange 0.5f
    Particle particle3;
    particle3.SetLifeTime(1);
    particle3.SetLifeTimeRange(0);
    particle3.SetParticleType(ParticleType::IMAGE);
    ParticleConfig config;
    ImageParticleParameter imageParam;
    ImageFit imageFit = ImageFit::FILL;
    imageParam.SetImageFit(imageFit);
    config.SetImageParticleParameter(imageParam);
    particle3.SetConfig(config);
    emitter.SetParticle(particle3);
    particleOption.SetEmitterOption(emitter);
    OHOS::Rosen::ParticleParams ret3 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret3.velocity_.velocityAngle_.start_, 0.0f);
    EXPECT_EQ(ret3.velocity_.velocityAngle_.end_, 0.0f);
}

/**
 * @tc.name: RosenRenderContextTest021
 * @tc.desc: OnParticleOptionArrayUpdate()-2
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest021, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params,default value,expect SetLifeTime 0.0f,SetLifeTimeRange 1.0f
    ParticleOption particleOption;
    RectF rectF;
    EmitterOption emitter;
    Particle particle;
    particle.SetLifeTime(0.0f);
    particle.SetLifeTimeRange(1.0f);
    emitter.SetParticle(particle);
    particleOption.SetEmitterOption(emitter);
    // particleColorPropertyOption assign value
    ParticleColorPropertyOption particleColorPropertyOption;
    particleOption.SetParticleColorOption(particleColorPropertyOption);
    OHOS::Rosen::ParticleParams ret4 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret4.color_.updator_, OHOS::Rosen::ParticleUpdator::NONE);
    ParticleColorPropertyUpdater colorUpdater;
    colorUpdater.SetUpdateType(UpdaterType::RANDOM);
    particleColorPropertyOption.SetUpdater(colorUpdater);
    particleOption.SetParticleColorOption(particleColorPropertyOption);
    OHOS::Rosen::ParticleParams ret5 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret5.color_.updator_, OHOS::Rosen::ParticleUpdator::RANDOM);
    colorUpdater.SetUpdateType(UpdaterType::CURVE);
    particleColorPropertyOption.SetUpdater(colorUpdater);
    particleOption.SetParticleColorOption(particleColorPropertyOption);
    OHOS::Rosen::ParticleParams ret6 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret6.color_.updator_, OHOS::Rosen::ParticleUpdator::CURVE);
    // ParticleFloatPropertyOption assign value
    ParticleFloatPropertyOption particleFloatPropertyOption;
    particleOption.SetParticleOpacityOption(particleFloatPropertyOption);
    OHOS::Rosen::ParticleParams ret7 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret7.opacity_.updator_, OHOS::Rosen::ParticleUpdator::NONE);
    ParticleFloatPropertyUpdater particleFloatPropertyUpdater;
    particleFloatPropertyUpdater.SetUpdaterType(UpdaterType::RANDOM);
    particleFloatPropertyOption.SetUpdater(particleFloatPropertyUpdater);
    particleOption.SetParticleOpacityOption(particleFloatPropertyOption);
    OHOS::Rosen::ParticleParams ret8 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret8.opacity_.updator_, OHOS::Rosen::ParticleUpdator::RANDOM);
    particleFloatPropertyUpdater.SetUpdaterType(UpdaterType::CURVE);
    particleFloatPropertyOption.SetUpdater(particleFloatPropertyUpdater);
    particleOption.SetParticleOpacityOption(particleFloatPropertyOption);
    OHOS::Rosen::ParticleParams ret9 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret9.opacity_.updator_, OHOS::Rosen::ParticleUpdator::CURVE);
    // scaleOptionOpt assing value,same as rsOpacityOpt
    particleOption.SetParticleScaleOption(particleFloatPropertyOption);
    OHOS::Rosen::ParticleParams ret10 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret10.scale_.updator_, OHOS::Rosen::ParticleUpdator::CURVE);
}

/**
 * @tc.name: RosenRenderContextTest022
 * @tc.desc: OnParticleOptionArrayUpdate()-3
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest022, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params,default value,expect SetLifeTime 0.0f,SetLifeTimeRange 1.0f
    ParticleOption particleOption;
    RectF rectF;
    EmitterOption emitter;
    Particle particle;
    particle.SetLifeTime(0.0f);
    particle.SetLifeTimeRange(1.0f);
    emitter.SetParticle(particle);
    particleOption.SetEmitterOption(emitter);
    // velocityOptionOpt assing value
    VelocityProperty velocityProperty;
    std::pair<float, float> range = std::make_pair(1.0f, 2.0f);
    velocityProperty.SetSpeedRange(range);
    velocityProperty.SetAngleRange(range);
    particleOption.SetParticleVelocityOption(velocityProperty);
    OHOS::Rosen::ParticleParams ret11 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret11.velocity_.velocityAngle_.end_, 2.0f);
    //  accelerationProperty assing value
    AccelerationProperty accelerationProperty;
    particleOption.SetParticleAccelerationOption(accelerationProperty);
    OHOS::Rosen::ParticleParams ret12 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret12.acceleration_.accelerationAngle_.val_.end_, 0.0f);
    EXPECT_EQ(ret12.acceleration_.accelerationValue_.val_.end_, 0.0f);
    ParticleFloatPropertyOption particleFloatPropertyOption1;
    particleFloatPropertyOption1.SetRange(range);
    accelerationProperty.SetSpeed(particleFloatPropertyOption1);
    accelerationProperty.SetAngle(particleFloatPropertyOption1);
    particleOption.SetParticleAccelerationOption(accelerationProperty);
    OHOS::Rosen::ParticleParams ret13 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret13.acceleration_.accelerationAngle_.val_.end_, 2.0f);
    EXPECT_EQ(ret13.acceleration_.accelerationValue_.val_.end_, 2.0f);
    // spinOption assing value
    particleOption.SetParticleSpinOption(particleFloatPropertyOption1);
    OHOS::Rosen::ParticleParams ret14 = rosenRenderContext->ConvertParticleOptionToParams(particleOption, rectF);
    EXPECT_EQ(ret14.spin_.updator_, OHOS::Rosen::ParticleUpdator::NONE);
}

/**
 * @tc.name: RosenRenderContextTest023
 * @tc.desc: OnDynamicRangeModeUpdate()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest023, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params
    DynamicRangeMode dynamicRangeMode = DynamicRangeMode::STANDARD;
    rosenRenderContext->OnDynamicRangeModeUpdate(dynamicRangeMode);
    EXPECT_EQ(rosenRenderContext->isHdr_, false);
    dynamicRangeMode = DynamicRangeMode::HIGH;
    rosenRenderContext->OnDynamicRangeModeUpdate(dynamicRangeMode);
    EXPECT_EQ(rosenRenderContext->isHdr_, true);
    rosenRenderContext->OnDynamicRangeModeUpdate(dynamicRangeMode);
    EXPECT_EQ(rosenRenderContext->isHdr_, false);
}

/**
 * @tc.name: RosenRenderContextTest024
 * @tc.desc: GetThumbnailPixelMap()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest024, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params
    RefPtr<PixelMap> ret = rosenRenderContext->GetThumbnailPixelMap(false);
    EXPECT_EQ(Referenced::RawPtr(ret) == nullptr, true);
    RefPtr<PixelMap> ret2 = rosenRenderContext->GetThumbnailPixelMap(true);
    EXPECT_EQ(Referenced::RawPtr(ret) == nullptr, true);
}

/**
 * @tc.name: RosenRenderContextTest025
 * @tc.desc: MarshallTranslate()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest025, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params
    TranslateOptions translate;
    Vector3F ret = rosenRenderContext->MarshallTranslate(translate);
    EXPECT_EQ(ret.x, 0.0f);
    EXPECT_EQ(ret.y, 0.0f);
    EXPECT_EQ(ret.z, 0.0f);
    CalcDimension x(1.0, DimensionUnit::PX);
    CalcDimension y(1.0, DimensionUnit::PERCENT);
    CalcDimension z(1.0, DimensionUnit::PX);
    TranslateOptions translate1(x, y, z);
    Vector3F ret2 = rosenRenderContext->MarshallTranslate(translate1);
    EXPECT_EQ(ret2.x, 0.0f);
    CalcDimension x2(1.0, DimensionUnit::PERCENT);
    TranslateOptions translate2(x2, y, z);
    Vector3F ret3 = rosenRenderContext->MarshallTranslate(translate2);
    EXPECT_EQ(ret3.x, 0.0f);
}

/**
 * @tc.name: RosenRenderContextTest026
 * @tc.desc: GetPaintRectWithTransform()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest026, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params
    RectF ret = rosenRenderContext->GetPaintRectWithTransform();
    EXPECT_EQ(ret.x_, 0.0f);
    rosenRenderContext->GetRSNode()->SetRotation(2.0f);
    RectF ret2 = rosenRenderContext->GetPaintRectWithTransform();
    EXPECT_EQ(ret2.x_, 0.0f);
    rosenRenderContext->GetRSNode()->SetRotation(90.0f);
    RectF ret3 = rosenRenderContext->GetPaintRectWithTransform();
    EXPECT_EQ(ret3.x_, 0.0f);
    rosenRenderContext->GetRSNode()->SetRotation(180.0f);
    RectF ret4 = rosenRenderContext->GetPaintRectWithTransform();
    EXPECT_EQ(ret4.x_, 0.0f);
    rosenRenderContext->GetRSNode()->SetRotation(270.0f);
    RectF ret5 = rosenRenderContext->GetPaintRectWithTransform();
    EXPECT_EQ(ret5.x_, 0.0f);
}

/**
 * @tc.name: RosenRenderContextTest027
 * @tc.desc: GetPaintRectWithTranslate()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest027, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params
    std::pair<RectF, bool> ret = rosenRenderContext->GetPaintRectWithTranslate();
    EXPECT_EQ(ret.first.x_, 0.0f);
    rosenRenderContext->GetRSNode()->SetRotation(90.0f);
    std::pair<RectF, bool> ret2 = rosenRenderContext->GetPaintRectWithTranslate();
    EXPECT_EQ(ret2.first.width_, -1.0f);
}

/**
 * @tc.name: RosenRenderContextTest028
 * @tc.desc: GetRevertMatrix()/GetMatrix()/GetMatrixWithTransformRotate()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest028, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params
    Matrix4 ret = rosenRenderContext->GetRevertMatrix();
    EXPECT_EQ(ret(0, 0), 1.0f);
    Matrix4 ret2 = rosenRenderContext->GetMatrix();
    EXPECT_EQ(ret2(0, 0), 1.0f);
    Matrix4 ret3 = rosenRenderContext->GetMatrixWithTransformRotate();
    EXPECT_EQ(ret3(0, 0), 1.0f);
}

/**
 * @tc.name: RosenRenderContextTest029
 * @tc.desc: GetPointWithTransform()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest029, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params
    PointF pointf;
    rosenRenderContext->GetPointWithTransform(pointf);
    EXPECT_EQ(pointf.x_, 0.0f);
    rosenRenderContext->GetRSNode()->SetRotation(90.0f);
    rosenRenderContext->GetPointWithTransform(pointf);
    EXPECT_EQ(pointf.x_, 0.0f);
}

/**
 * @tc.name: RosenRenderContextTest030
 * @tc.desc: NeedPreloadImage()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest030, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params
    std::list<ParticleOption> optionList;
    RectF rect;
    bool ret = rosenRenderContext->NeedPreloadImage(optionList, rect);
    EXPECT_FALSE(ret);
    ParticleOption particleOption1;
    EmitterOption emitter1;
    Particle particle1;
    particle1.SetLifeTime(1);
    particle1.SetLifeTimeRange(0);
    particle1.SetParticleType(ParticleType::POINT);
    emitter1.SetParticle(particle1);
    particleOption1.SetEmitterOption(emitter1);
    optionList.push_back(particleOption1);
    bool ret2 = rosenRenderContext->NeedPreloadImage(optionList, rect);
    EXPECT_FALSE(ret2);
    ParticleOption particleOption;
    EmitterOption emitter;
    Particle particle;
    particle.SetLifeTime(1);
    particle.SetLifeTimeRange(0);
    particle.SetParticleType(ParticleType::IMAGE);
    emitter.SetParticle(particle);
    particleOption.SetEmitterOption(emitter);
    optionList.push_back(particleOption);
    bool ret3 = rosenRenderContext->NeedPreloadImage(optionList, rect);
    EXPECT_TRUE(ret3);
}

/**
 * @tc.name: RosenRenderContextTest031
 * @tc.desc: OnParticleImageLoaded()/ConvertDimensionToPx
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest031, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    // constrcuct params
    std::string src = "";
    RefPtr<CanvasImage> canvasImage;
    int size = rosenRenderContext->particleImageMap_.size();
    rosenRenderContext->OnParticleImageLoaded(src, canvasImage);
    EXPECT_EQ(rosenRenderContext->particleImageMap_.size(), size + 1);

    OHOS::Ace::Dimension dimension(1.0, DimensionUnit::PX);
    float ret = rosenRenderContext->ConvertDimensionToPx(dimension, 5);
    EXPECT_EQ(ret, 1.0f);
    OHOS::Ace::Dimension dimension2(1.0, DimensionUnit::PERCENT);
    float ret2 = rosenRenderContext->ConvertDimensionToPx(dimension2, 5);
    EXPECT_EQ(ret2, 5.0f);
}

/**
 * @tc.name: RosenRenderContextTest032
 * @tc.desc: InitContext()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest032, TestSize.Level1)
{
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::CANVAS;
    contextParam.surfaceName.emplace("test");
    std::optional<RenderContext::ContextParam> contextParamValue = std::make_optional(contextParam);
    // is root is true
    rosenRenderContext->InitContext(true, contextParamValue);
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);
    rosenRenderContext->rsNode_ = nullptr;
    // contextParamValue does not has value
    std::optional<RenderContext::ContextParam> contextParamValue2 = std::make_optional(contextParam);
    rosenRenderContext->InitContext(false, contextParamValue2);
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);
    rosenRenderContext->rsNode_ = nullptr;
    contextParam.type = RenderContext::ContextType::ROOT;
    std::optional<RenderContext::ContextParam> contextParamValue3 = std::make_optional(contextParam);
    rosenRenderContext->InitContext(false, contextParamValue3);
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);
    rosenRenderContext->rsNode_ = nullptr;
    contextParam.type = RenderContext::ContextType::SURFACE;
    std::optional<RenderContext::ContextParam> contextParamValue4 = std::make_optional(contextParam);
    rosenRenderContext->InitContext(false, contextParamValue4);
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);
    rosenRenderContext->rsNode_ = nullptr;
    contextParam.type = RenderContext::ContextType::HARDWARE_SURFACE;
    std::optional<RenderContext::ContextParam> contextParamValue5 = std::make_optional(contextParam);
    rosenRenderContext->InitContext(false, contextParamValue5);
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);
    rosenRenderContext->rsNode_ = nullptr;
    contextParam.type = RenderContext::ContextType::EFFECT;
    std::optional<RenderContext::ContextParam> contextParamValue7 = std::make_optional(contextParam);
    rosenRenderContext->InitContext(false, contextParamValue7);
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);
    rosenRenderContext->rsNode_ = nullptr;
    contextParam.type = RenderContext::ContextType::INCREMENTAL_CANVAS;
    std::optional<RenderContext::ContextParam> contextParamValue8 = std::make_optional(contextParam);
    rosenRenderContext->InitContext(false, contextParamValue8);
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);
    rosenRenderContext->rsNode_ = nullptr;
    contextParam.type = RenderContext::ContextType::EXTERNAL;
    std::optional<RenderContext::ContextParam> contextParamValue9 = std::make_optional(contextParam);
    rosenRenderContext->InitContext(false, contextParamValue9);
    EXPECT_EQ(rosenRenderContext->rsNode_ == nullptr, true);
}

/**
 * @tc.name: RosenRenderContextTest033
 * @tc.desc: PaintDebugBoundary()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest033, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->PaintDebugBoundary(false);
    EXPECT_EQ(rosenRenderContext->debugBoundaryModifier_ == nullptr, true);
    auto rosenRenderContext2 = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::SURFACE;
    contextParam.surfaceName.emplace("test");
    std::optional<RenderContext::ContextParam> contextParamValue = std::make_optional(contextParam);
    rosenRenderContext2->InitContext(false, contextParamValue);
    rosenRenderContext2->SetHostNode(frameNode);
    rosenRenderContext2->PaintDebugBoundary(true);
    EXPECT_EQ(rosenRenderContext->debugBoundaryModifier_ == nullptr, true);
}

/**
 * @tc.name: RosenRenderContextTest034
 * @tc.desc: UpdateBlurBackgroundColor()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest034, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<ParticlePattern>(1); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    std::optional<BlurStyleOption> bgBlurStyle;
    EXPECT_FALSE(rosenRenderContext->UpdateBlurBackgroundColor(bgBlurStyle));
    std::optional<BlurStyleOption> bgBlurStyle2 = std::make_optional(BlurStyleOption());
    EXPECT_TRUE(rosenRenderContext->UpdateBlurBackgroundColor(bgBlurStyle2));
    bgBlurStyle2->isValidColor = true;
    EXPECT_TRUE(rosenRenderContext->UpdateBlurBackgroundColor(bgBlurStyle2));
    bgBlurStyle2->isWindowFocused = false;
    EXPECT_TRUE(rosenRenderContext->UpdateBlurBackgroundColor(bgBlurStyle2));

    std::optional<EffectOption> efffectOption = std::make_optional(EffectOption());
    EXPECT_TRUE(rosenRenderContext->UpdateBlurBackgroundColor(efffectOption));
    efffectOption->isValidColor = true;
    EXPECT_TRUE(rosenRenderContext->UpdateBlurBackgroundColor(efffectOption));
    efffectOption->isWindowFocused = false;
    EXPECT_TRUE(rosenRenderContext->UpdateBlurBackgroundColor(efffectOption));
}

/**
 * @tc.name: RosenRenderContextTest035
 * @tc.desc: UpdateAccessibilityRoundRect().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest035, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    if (!rosenRenderContext) {
        return;
    }

    rosenRenderContext->accessibilityFocusStateModifier_ = std::make_shared<FocusStateModifier>();
    if (!rosenRenderContext->accessibilityFocusStateModifier_) {
        return;
    }

    RoundRect frameRect;
    frameRect.SetRect(RectF(6, 6, 6, 6));
    const constexpr double accessibilityFocusWidth = 4.0;
    double lineWidth = accessibilityFocusWidth * PipelineBase::GetCurrentDensity();
    Dimension paintWidth(lineWidth, DimensionUnit::PX);
    auto paintWidthPx = static_cast<float>(paintWidth.ConvertToPx());
    (void)paintWidthPx;
    rosenRenderContext->accessibilityFocusStateModifier_->SetRoundRect(frameRect, paintWidthPx);
    if (!rosenRenderContext->accessibilityFocusStateModifier_->animationRect_) {
        return;
    }
    frameNode->geometryNode_->SetFrameSize(SizeF(10.0f, 10.0f));
    rosenRenderContext->UpdateAccessibilityRoundRect();
    auto rectBeforeUpdate = rosenRenderContext->accessibilityFocusStateModifier_->roundRect_.GetRect();
    EXPECT_EQ(rectBeforeUpdate.GetLeft(), 2.0f);
    EXPECT_EQ(rectBeforeUpdate.GetTop(), 2.0f);
    EXPECT_EQ(rectBeforeUpdate.GetRight(), 8.0f);
    EXPECT_EQ(rectBeforeUpdate.GetBottom(), 8.0f);

    frameNode->geometryNode_->SetFrameSize(SizeF(20.0f, 20.0f));
    rosenRenderContext->UpdateAccessibilityRoundRect();
    auto rectAfterUpdate = rosenRenderContext->accessibilityFocusStateModifier_->roundRect_.GetRect();

    EXPECT_EQ(rectAfterUpdate.GetLeft(), 2.0f);
    EXPECT_EQ(rectAfterUpdate.GetTop(), 2.0f);
    EXPECT_EQ(rectAfterUpdate.GetRight(), 18.0f);
    EXPECT_EQ(rectAfterUpdate.GetBottom(), 18.0f);

    Dimension focusPaddingVp = Dimension(0.0, DimensionUnit::VP);
    auto borderPaddingPx = static_cast<float>(focusPaddingVp.ConvertToPx());
    auto diffRadiusValueX = borderPaddingPx + paintWidthPx / 2;
    auto diffRadiusValueY = borderPaddingPx + paintWidthPx / 2;

    auto roundRectAfterUpdate = rosenRenderContext->accessibilityFocusStateModifier_->roundRect_;
    auto focusPaintCornerTopLeftAfter = roundRectAfterUpdate.GetCornerRadius(RSRoundRect::RoundRect::CornerPos::TOP_LEFT_POS);
    auto focusPaintCornerTopRightAfter = roundRectAfterUpdate.GetCornerRadius(RSRoundRect::RoundRect::CornerPos::TOP_RIGHT_POS);
    auto focusPaintCornerBottomLeftAfter = roundRectAfterUpdate.GetCornerRadius(RSRoundRect::RoundRect::CornerPos::BOTTOM_LEFT_POS);
    auto focusPaintCornerBottomRightAfter = roundRectAfterUpdate.GetCornerRadius(RSRoundRect::RoundRect::CornerPos::BOTTOM_RIGHT_POS);

    EXPECT_EQ(focusPaintCornerTopLeftAfter.GetX(), diffRadiusValueX);
    EXPECT_EQ(focusPaintCornerTopLeftAfter.GetY(), diffRadiusValueY);
    EXPECT_EQ(focusPaintCornerTopRightAfter.GetX(), diffRadiusValueX);
    EXPECT_EQ(focusPaintCornerTopRightAfter.GetY(), diffRadiusValueY);
    EXPECT_EQ(focusPaintCornerBottomLeftAfter.GetX(), diffRadiusValueX);
    EXPECT_EQ(focusPaintCornerBottomLeftAfter.GetY(), diffRadiusValueY);
    EXPECT_EQ(focusPaintCornerBottomRightAfter.GetX(), diffRadiusValueX);
    EXPECT_EQ(focusPaintCornerBottomRightAfter.GetY(), diffRadiusValueY);
}

/**
 * @tc.name: RosenRenderContextTest037
 * @tc.desc: UpdateShadow.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest037, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    if (!rosenRenderContext) {
        return;
    }
    Shadow shadow;
    shadow.SetBlurRadius(1.0);
    shadow.SetOffsetX(1.0);
    shadow.SetOffsetY(1.0);
    shadow.SetIsFilled(true);
    rosenRenderContext->OnBackShadowUpdate(shadow);
    auto color = rosenRenderContext->rsNode_->GetStagingProperties().GetShadowColor();
    ASSERT_TRUE(color.AsArgbInt() == Color::BLACK.GetValue());
    auto offsetX =  rosenRenderContext->rsNode_->GetStagingProperties().GetShadowOffsetY();
    auto offsetY =  rosenRenderContext->rsNode_->GetStagingProperties().GetShadowOffsetY();
    ASSERT_TRUE(NearEqual(1.0, offsetX));
    ASSERT_TRUE(NearEqual(1.0, offsetY));
    auto isFilled =  rosenRenderContext->rsNode_->GetStagingProperties().GetShadowIsFilled();
    ASSERT_TRUE(isFilled);
}

/**
 * @tc.name: RosenRenderContextTest38
 * @tc.desc: UpdateClipEdge
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest038, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    if (!rosenRenderContext) {
        return;
    }
    rosenRenderContext->OnClipEdgeUpdate(true);
    auto clip = rosenRenderContext->rsNode_->GetStagingProperties().GetClipToBounds();
    ASSERT_TRUE(clip);
}

/**
 * @tc.name: RosenRenderContextTest039
 * @tc.desc: GetStatusByEffectTypeAndWindow.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest039, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    auto pipeline = MockPipelineContext::GetCurrentContext();

    auto windowEffect = EffectType::WINDOW_EFFECT;
    rosenRenderContext->UpdateUseEffectType(windowEffect);
    pipeline->WindowFocus(false);
    EXPECT_TRUE(rosenRenderContext->GetStatusByEffectTypeAndWindow());

    pipeline->WindowFocus(true);
    auto useEffectTypeVal = rosenRenderContext->GetUseEffectType();
    EXPECT_EQ(useEffectTypeVal, windowEffect);
    EXPECT_TRUE(pipeline->IsWindowFocused());
    EXPECT_TRUE(rosenRenderContext->GetStatusByEffectTypeAndWindow());

    rosenRenderContext->UpdateUseEffectType(EffectType::DEFAULT);
    EXPECT_FALSE(rosenRenderContext->GetStatusByEffectTypeAndWindow());
}

/**
 * @tc.name: RosenRenderContextTest040
 * @tc.desc: OnUseEffectUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest040, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    auto pipeline = rosenRenderContext->GetPipelineContext();
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);

    rosenRenderContext->UpdateUseEffectType(EffectType::WINDOW_EFFECT);
    bool value = true;
    // GetStatusByEffectTypeAndWindow() is true
    pipeline->WindowFocus(false);
    rosenRenderContext->OnUseEffectUpdate(value);
    bool willSetVal = false;
    rosenRenderContext->rsNode_->SetUseEffect(willSetVal);
    EXPECT_NE(willSetVal, value);

    // GetStatusByEffectTypeAndWindow() is false
    pipeline->WindowFocus(true);
    rosenRenderContext->OnUseEffectUpdate(value);
    willSetVal = true;
    rosenRenderContext->rsNode_->SetUseEffect(willSetVal);
    EXPECT_EQ(willSetVal, value);

    value = false;
    // value is false, GetStatusByEffectTypeAndWindow() is true
    pipeline->WindowFocus(false);
    rosenRenderContext->OnUseEffectUpdate(value);
    willSetVal = false;
    rosenRenderContext->rsNode_->SetUseEffect(value);
    EXPECT_EQ(willSetVal, value);

    // value is false,  GetStatusByEffectTypeAndWindow() is false
    pipeline->WindowFocus(true);
    rosenRenderContext->OnUseEffectUpdate(value);
    willSetVal = false;
    rosenRenderContext->rsNode_->SetUseEffect(willSetVal);
    EXPECT_EQ(willSetVal, value);
}

/**
 * @tc.name: RosenRenderContextTest041
 * @tc.desc: OnUseEffectTypeUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest041, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    EffectType effectType = EffectType::WINDOW_EFFECT;
    rosenRenderContext->OnUseEffectTypeUpdate(effectType);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);

    auto effectTypeParam = static_cast<Rosen::UseEffectType>(effectType);
    rosenRenderContext->rsNode_->SetUseEffectType(effectTypeParam);
    
    bool useEffect = true;
    rosenRenderContext->UpdateUseEffect(useEffect);
    rosenRenderContext->OnUseEffectUpdate(useEffect);

    useEffect = false;
    rosenRenderContext->UpdateUseEffect(useEffect);
    rosenRenderContext->OnUseEffectUpdate(useEffect);

    effectType = EffectType::DEFAULT;
    rosenRenderContext->OnUseEffectTypeUpdate(effectType);
    auto useEffectTypeVal = rosenRenderContext->GetUseEffectType().value_or(EffectType::DEFAULT);
    EXPECT_EQ(useEffectTypeVal, effectType);
}

/**
 * @tc.name: RosenRenderContextTest042
 * @tc.desc: UpdateWindowFocusState().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest042, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
   
    bool isFocused = true;
    rosenRenderContext->UpdateWindowFocusState(isFocused);

    auto useEffect = rosenRenderContext->GetUseEffect().value_or(false);
    rosenRenderContext->UpdateUseEffectType(EffectType::WINDOW_EFFECT);
    rosenRenderContext->OnUseEffectUpdate(useEffect);

    BlurStyleOption blurStyleObj;
    blurStyleObj.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    blurStyleObj.isWindowFocused = isFocused;
    rosenRenderContext->UpdateBackBlurStyle(blurStyleObj);

    EffectOption effectObj;
    effectObj.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    rosenRenderContext->UpdateBackgroundEffect(effectObj);
    EXPECT_EQ(effectObj.isWindowFocused, isFocused);
}

/**
 * @tc.name: RosenRenderContextTest043
 * @tc.desc: OnBackgroundColorUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node and check basic information.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    const Color value = Color::RED;
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    OHOS::Rosen::RSColor rsColor;
    /**
     * @tc.steps: step2. Call OnBackgroundColorUpdate function with value (RED), and convert it to rsColor.
     * @tc.expected: step2. The backgroundColorVal value on node should match rsColor value.
     */
    rosenRenderContext->OnBackgroundColorUpdate(value);
    rosenRenderContext->ColorToRSColor(value, rsColor);
    rosenRenderContext->rsNode_->SetBackgroundColor(rsColor);
    rosenRenderContext->PaintBackground();
    auto backgroundColorVal = rosenRenderContext->rsNode_->GetStagingProperties().GetBackgroundColor();
    rsColor.ConvertToP3ColorSpace();
    EXPECT_EQ(backgroundColorVal.GetRed(), rsColor.GetRed());
    EXPECT_EQ(backgroundColorVal.GetGreen(), rsColor.GetGreen());
    EXPECT_EQ(backgroundColorVal.GetBlue(), rsColor.GetBlue());
    EXPECT_EQ(backgroundColorVal.GetAlpha(), rsColor.GetAlpha());
    EXPECT_EQ(backgroundColorVal.GetColorSpace(), rsColor.GetColorSpace());
    /**
     * @tc.steps: step3. Call OnBackgroundColorUpdate function with p3Color (RED with DISPLAY_P3 color space),
     * and convert it to rsColor.
     * @tc.expected: step3. The colorSpace of p3BackgroundColorVal on node should match colorSpace of rsColor.
     */
    Color p3Color = Color::RED;
    p3Color.SetColorSpace(ColorSpace::DISPLAY_P3);
    rosenRenderContext->OnBackgroundColorUpdate(p3Color);
    rosenRenderContext->ColorToRSColor(p3Color, rsColor);
    rosenRenderContext->rsNode_->SetBackgroundColor(rsColor);
    rosenRenderContext->PaintBackground();
    auto p3BackgroundColorVal = rosenRenderContext->rsNode_->GetStagingProperties().GetBackgroundColor();
    EXPECT_EQ(p3BackgroundColorVal.GetColorSpace(), rsColor.GetColorSpace());
}

/**
 * @tc.name: RosenRenderContextTest044
 * @tc.desc: HasValidBgImageResizable().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest044, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);

    rosenRenderContext->bgLoadingCtx_ = nullptr;
    EXPECT_EQ(rosenRenderContext->HasValidBgImageResizable(), false);
    auto str = ImageSourceInfo(SRC_JPG);
    auto ctx = AceType::MakeRefPtr<ImageLoadingContext>(str, LoadNotifier(nullptr, nullptr, nullptr), true);
   
    rosenRenderContext->bgLoadingCtx_ = ctx;
    auto srcSize = rosenRenderContext->bgLoadingCtx_->GetImageSize();
    auto slice = rosenRenderContext->GetBackgroundImageResizableSliceValue(ImageResizableSlice());
    auto left = slice.left.ConvertToPxWithSize(srcSize.Width());
    auto right = slice.right.ConvertToPxWithSize(srcSize.Width());
    auto top = slice.top.ConvertToPxWithSize(srcSize.Width());
    auto bottom = slice.bottom.ConvertToPxWithSize(srcSize.Width());
    bool firstRes = srcSize.Width() > left + right;
    bool secondRes = srcSize.Height() > top + bottom;
    bool thirdRes = right > 0;
    bool fourthRes = bottom > 0;
    bool res = firstRes && secondRes && thirdRes && fourthRes;

    EXPECT_EQ(rosenRenderContext->HasValidBgImageResizable(), res);
}

/**
 * @tc.name: RosenRenderContextTest045
 * @tc.desc: SetAlphaOffscreen().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest045, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    bool isOffScreen = true;
    bool isOffScreenVal = true;
    rosenRenderContext->SetAlphaOffscreen(isOffScreen);
    rosenRenderContext->rsNode_->SetAlphaOffscreen(isOffScreenVal);
    EXPECT_EQ(isOffScreen, isOffScreenVal);

    isOffScreen = false;
    isOffScreenVal = false;
    rosenRenderContext->SetAlphaOffscreen(isOffScreen);
    rosenRenderContext->rsNode_->SetAlphaOffscreen(isOffScreenVal);
    EXPECT_EQ(isOffScreen, isOffScreenVal);
}

/**
 * @tc.name: RosenRenderContextTest046
 * @tc.desc: Test SetRenderFit Func and GetRenderFit Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest046, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    rosenRenderContext->SetRenderFit(RenderFit::CENTER);
    auto renderFit = rosenRenderContext->GetRenderFit();
    ASSERT_NE(renderFit, std::nullopt);
    EXPECT_EQ(renderFit.value(), RenderFit::CENTER);
}

/**
 * @tc.name: RosenRenderContextTest047
 * @tc.desc: Test OnTransformRotateAngleUpdate Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest047, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    auto rotateX = 40.0f;
    auto rotateY = -40.0f;
    auto rotateZ = 0.0f;
    auto perspective = 120.0f;
    auto rotate = 0.0f;
    auto rotationXUserModifier = std::make_shared<Rosen::RSAnimatableProperty<float>>(rotate);
    auto rotationYUserModifier = std::make_shared<Rosen::RSAnimatableProperty<float>>(rotate);
    auto rotationZUserModifier = std::make_shared<Rosen::RSAnimatableProperty<float>>(rotate);
    auto cameraDistanceUserModifier = std::make_shared<Rosen::RSAnimatableProperty<float>>(rotate);
    rosenRenderContext->rotationXUserModifier_ = std::make_shared<Rosen::ModifierNG::RSTransformModifier>();
    rosenRenderContext->rotationXUserModifier_->AttachProperty(
        Rosen::ModifierNG::RSPropertyType::ROTATION_X, rotationXUserModifier);
    rosenRenderContext->rotationYUserModifier_ = std::make_shared<Rosen::ModifierNG::RSTransformModifier>();
    rosenRenderContext->rotationYUserModifier_->AttachProperty(
        Rosen::ModifierNG::RSPropertyType::ROTATION_Y, rotationYUserModifier);
    rosenRenderContext->rotationZUserModifier_ = std::make_shared<Rosen::ModifierNG::RSTransformModifier>();
    rosenRenderContext->rotationZUserModifier_->AttachProperty(
        Rosen::ModifierNG::RSPropertyType::ROTATION, rotationZUserModifier);
    rosenRenderContext->cameraDistanceUserModifier_ = std::make_shared<Rosen::ModifierNG::RSTransformModifier>();
    rosenRenderContext->cameraDistanceUserModifier_->AttachProperty(
        Rosen::ModifierNG::RSPropertyType::CAMERA_DISTANCE, cameraDistanceUserModifier);
    rosenRenderContext->OnTransformRotateAngleUpdate({ rotateX, rotateY, rotateZ, perspective });
    auto rotationXValue = rosenRenderContext->rotationXUserModifier_->GetRotationX();
    auto rotationYValue = rosenRenderContext->rotationYUserModifier_->GetRotationY();
    auto rotationZValue = rosenRenderContext->rotationZUserModifier_->GetRotation();
    auto cameraDistanceValue = rosenRenderContext->cameraDistanceUserModifier_->GetCameraDistance();
    EXPECT_EQ(rotationXValue, -rotateX);
    EXPECT_EQ(rotationYValue, -rotateY);
    EXPECT_EQ(rotationZValue, rotateZ);
    EXPECT_EQ(cameraDistanceValue, perspective);
}

/**
 * @tc.name: RosenRenderContextTest048
 * @tc.desc: Test BlendBgColor Func and ResetBlendBgColor Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node and check basic information.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    /**
     * @tc.steps: step2. Call the BlendBgColor function and ResetBlendBgColor function.
     * @tc.expected: step2. The current colorSpace value on the node should match the original colorSpace value.
     */
    Color bgColor = Color::RED;
    OHOS::Rosen::RSColor rsColor;
    rosenRenderContext->OnBackgroundColorUpdate(bgColor);
    rosenRenderContext->ColorToRSColor(bgColor, rsColor);
    rosenRenderContext->rsNode_->SetBackgroundColor(rsColor);
    rosenRenderContext->PaintBackground();
    Color blendColor = Color::FromRGB(6, 7, 8);
    auto originBackgroundColorVal = rosenRenderContext->rsNode_->GetStagingProperties().GetBackgroundColor();
    rosenRenderContext->BlendBgColor(blendColor);
    auto backgroundColorVal = rosenRenderContext->rsNode_->GetStagingProperties().GetBackgroundColor();
    EXPECT_EQ(backgroundColorVal.GetColorSpace(), originBackgroundColorVal.GetColorSpace());
    rosenRenderContext->ResetBlendBgColor();
    backgroundColorVal = rosenRenderContext->rsNode_->GetStagingProperties().GetBackgroundColor();
    EXPECT_EQ(backgroundColorVal.GetColorSpace(), originBackgroundColorVal.GetColorSpace());
}

/**
 * @tc.name: AnimationPropertyTest001
 * @tc.desc: Test GetRenderNodePropertyValue func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, AnimationPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node and check basic infomation.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    auto rsNode = rosenRenderContext->rsNode_;
    ASSERT_NE(rsNode, nullptr);
    /**
     * @tc.steps: step2. Test GetRenderNodePropertyValue function without setting value.
     * @tc.expected: step2. property value on node is default value.
     */
    auto rotationValue = rosenRenderContext->GetRenderNodePropertyValue(AnimationPropertyType::ROTATION);
    std::vector<float> expectedRotationValue = { 0.0f, 0.0f, 0.0f };
    EXPECT_TRUE(CompareVector(rotationValue, expectedRotationValue));
    auto scaleValue = rosenRenderContext->GetRenderNodePropertyValue(AnimationPropertyType::SCALE);
    std::vector<float> expectedScaleValue = { 1.0f, 1.0f };
    EXPECT_TRUE(CompareVector(scaleValue, expectedScaleValue));
    auto translateValue = rosenRenderContext->GetRenderNodePropertyValue(AnimationPropertyType::TRANSLATION);
    std::vector<float> expectedTranslateValue = { 0.0f, 0.0f };
    EXPECT_TRUE(CompareVector(translateValue, expectedTranslateValue));
    auto opacityValue = rosenRenderContext->GetRenderNodePropertyValue(AnimationPropertyType::OPACITY);
    std::vector<float> expectedOpacityValue = { 1.0f };
    EXPECT_TRUE(CompareVector(opacityValue, expectedOpacityValue));
}

/**
 * @tc.name: AnimationPropertyTest002
 * @tc.desc: Test SetAnimationPropertyValue and GetRenderNodePropertyValue func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, AnimationPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node and check basic infomation.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    auto rsNode = rosenRenderContext->rsNode_;
    ASSERT_NE(rsNode, nullptr);
    /**
     * @tc.steps: step2. call SetAnimationPropertyValue function.
     * @tc.expected: step2. The value on rsNode is same with set value.
     */
    std::vector<float> rotationValue { 45.0f, -30.0f, 180.0f };
    rosenRenderContext->SetAnimationPropertyValue(AnimationPropertyType::ROTATION, rotationValue);
    std::vector<float> scaleValue { 2.0f, 1.2f };
    rosenRenderContext->SetAnimationPropertyValue(AnimationPropertyType::SCALE, scaleValue);
    std::vector<float> translateValue { 100.0f, -20.0f };
    rosenRenderContext->SetAnimationPropertyValue(AnimationPropertyType::TRANSLATION, translateValue);
    std::vector<float> opacityValue { 0.5f };
    rosenRenderContext->SetAnimationPropertyValue(AnimationPropertyType::OPACITY, opacityValue);
    auto nodeRotateValue = rosenRenderContext->GetRenderNodePropertyValue(AnimationPropertyType::ROTATION);
    auto nodeScaleValue = rosenRenderContext->GetRenderNodePropertyValue(AnimationPropertyType::SCALE);
    auto nodeTranslateValue = rosenRenderContext->GetRenderNodePropertyValue(AnimationPropertyType::TRANSLATION);
    auto nodeOpacityValue = rosenRenderContext->GetRenderNodePropertyValue(AnimationPropertyType::OPACITY);
    EXPECT_TRUE(CompareVector(nodeRotateValue, rotationValue));
    EXPECT_TRUE(CompareVector(nodeScaleValue, scaleValue));
    EXPECT_TRUE(CompareVector(nodeTranslateValue, translateValue));
    EXPECT_TRUE(CompareVector(nodeOpacityValue, opacityValue));
    /**
     * @tc.steps: step3. call SyncRSPropertyToRenderContext function.
     * @tc.expected: step3. The value on renderContext is same with set value.
     */
    rosenRenderContext->SyncRSPropertyToRenderContext(AnimationPropertyType::ROTATION);
    rosenRenderContext->SyncRSPropertyToRenderContext(AnimationPropertyType::SCALE);
    rosenRenderContext->SyncRSPropertyToRenderContext(AnimationPropertyType::TRANSLATION);
    rosenRenderContext->SyncRSPropertyToRenderContext(AnimationPropertyType::OPACITY);
    ASSERT_TRUE(rosenRenderContext->GetTransformRotateAngle().has_value());
    EXPECT_TRUE(NearEqual(rotationValue[2], rosenRenderContext->GetTransformRotateAngle()->z));
    ASSERT_TRUE(rosenRenderContext->GetTransformScale().has_value());
    EXPECT_TRUE(NearEqual(scaleValue[0], rosenRenderContext->GetTransformScale()->x));
    ASSERT_TRUE(rosenRenderContext->GetTransformTranslate().has_value());
    ASSERT_TRUE(rosenRenderContext->GetOpacity().has_value());
    EXPECT_TRUE(NearEqual(opacityValue[0], rosenRenderContext->GetOpacity().value()));
}

/**
 * @tc.name: UpdateTransformTranslate001
 * @tc.desc: Test UpdateTransformTranslate Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, UpdateTransformTranslate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node and check basic infomation.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    auto rsNode = rosenRenderContext->rsNode_;
    ASSERT_NE(rsNode, nullptr);
    /**
     * @tc.steps: step2. Set a TranslateOptions value whose unit is px.
     * @tc.expected: step2. Translate value in RSNode is correct.
     */
    constexpr float translateX = 30.0f;
    constexpr float translateY = -10.0f;
    constexpr float translateZ = 3.0f;
    Rosen::Vector2f translateRS;
    float translateZRS = 0.0f;
    TranslateOptions options { Dimension(translateX), Dimension(translateY), Dimension(translateZ) };
    rosenRenderContext->UpdateTransformTranslate(options);
    translateRS = rsNode->GetStagingProperties().GetTranslate();
    translateZRS = rsNode->GetStagingProperties().GetTranslateZ();
    EXPECT_TRUE(NearEqual(translateRS[0], translateX));
    EXPECT_TRUE(NearEqual(translateRS[1], translateY));
    EXPECT_TRUE(NearEqual(translateRS[2], translateZ));
    /**
     * @tc.steps: step3. Set a TranslateOptions value whose unit is percent. The node need have size.
     * @tc.expected: step3. Translate value in RSNode is correct.
     */
    constexpr float width = 200.0f;
    constexpr float height = 100.0f;
    constexpr float translateXPercent1 = 0.1f;
    constexpr float translateYPercent1 = 0.0f;
    RectF frame { 0, 0, width, height };
    rosenRenderContext->UpdatePaintRect(frame);
    rosenRenderContext->SyncGeometryProperties(frame);
    TranslateOptions options1 { Dimension(translateXPercent1, DimensionUnit::PERCENT),
        Dimension(translateYPercent1, DimensionUnit::PERCENT), Dimension(translateZ) };
    rosenRenderContext->UpdateTransformTranslate(options1);
    translateRS = rsNode->GetStagingProperties().GetTranslate();
    EXPECT_TRUE(NearEqual(translateRS[0], translateXPercent1 * width));
    EXPECT_TRUE(NearEqual(translateRS[1], translateYPercent1 * height));
}

/**
 * @tc.name: UpdateTransformRotate001
 * @tc.desc: Test UpdateTransformRotate Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, UpdateTransformRotate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node and check basic infomation.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    auto rsNode = rosenRenderContext->rsNode_;
    ASSERT_NE(rsNode, nullptr);
    constexpr float angle = 90.0f;
    constexpr float angleZero = 0.0f;
    /**
     * @tc.steps: step2. Set rotationX.
     * @tc.expected: step2. RotationX value in RSNode is correct.
     */
    Vector5F vecX { 1.0f, 0.0f, 0.0f, angle, 0.0f };
    rosenRenderContext->UpdateTransformRotate(vecX);
    // ignore the sign
    EXPECT_TRUE(NearEqual(std::abs(rsNode->GetStagingProperties().GetRotationX()), angle));
    EXPECT_TRUE(NearEqual(rsNode->GetStagingProperties().GetRotationY(), angleZero));
    EXPECT_TRUE(NearEqual(rsNode->GetStagingProperties().GetRotation(), angleZero));
    /**
     * @tc.steps: step3. Set rotationY.
     * @tc.expected: step3. RotationY value in RSNode is correct.
     */
    Vector5F vecY { 0.0f, 1.0f, 0.0f, angle, 0.0f };
    rosenRenderContext->UpdateTransformRotate(vecY);
    EXPECT_TRUE(NearEqual(rsNode->GetStagingProperties().GetRotationX(), angleZero));
    EXPECT_TRUE(NearEqual(std::abs(rsNode->GetStagingProperties().GetRotationY()), angle));
    EXPECT_TRUE(NearEqual(rsNode->GetStagingProperties().GetRotation(), angleZero));
    /**
     * @tc.steps: step4. Set rotationZ.
     * @tc.expected: step4. RotationZ value in RSNode is correct.
     */
    Vector5F vecZ { 0.0f, 0.0f, 1.0f, angle, 0.0f };
    rosenRenderContext->UpdateTransformRotate(vecZ);
    EXPECT_TRUE(NearEqual(rsNode->GetStagingProperties().GetRotationX(), angleZero));
    EXPECT_TRUE(NearEqual(rsNode->GetStagingProperties().GetRotationY(), angleZero));
    EXPECT_TRUE(NearEqual(std::abs(rsNode->GetStagingProperties().GetRotation()), angle));
}

/**
 * @tc.name: UpdateTransformScale001
 * @tc.desc: Test UpdateTransformScale Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, UpdateTransformScale001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node and check basic infomation.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    auto rsNode = rosenRenderContext->rsNode_;
    ASSERT_NE(rsNode, nullptr);
    constexpr float scale1 = 2.0f;
    constexpr float scale2 = -2.0f;
    Rosen::Vector2f rsScale;
    /**
     * @tc.steps: step2. Set positive scale.
     * @tc.expected: step2. Scale value in RSNode is correct.
     */
    VectorF vecScale1 { scale1, scale1 };
    rosenRenderContext->UpdateTransformScale(vecScale1);
    rsScale = rsNode->GetStagingProperties().GetScale();
    EXPECT_TRUE(NearEqual(rsScale[0], scale1));
    EXPECT_TRUE(NearEqual(rsScale[1], scale1));
    /**
     * @tc.steps: step3. Set negative scale.
     * @tc.expected: step3. Scale value in RSNode is correct.
     */
    VectorF vecScale2 { scale2, scale2 };
    rosenRenderContext->UpdateTransformScale(vecScale2);
    rsScale = rsNode->GetStagingProperties().GetScale();
    EXPECT_TRUE(NearEqual(rsScale[0], scale2));
    EXPECT_TRUE(NearEqual(rsScale[1], scale2));
}

/**
 * @tc.name: SetAlwaysSnapshot001
 * @tc.desc: Test SetAlwaysSnapshot Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, SetAlwaysSnapshot001, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext =
        InitRosenRenderContext(frameNode, RenderContext::ContextType::EFFECT);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);

    /**
     * @tc.steps: step1. Get default value.
     * @tc.expected: step1. Default value is false.
     */
    EXPECT_EQ(rosenRenderContext->rsNode_->GetStagingProperties().GetAlwaysSnapshot(), false);

    /**
     * @tc.steps: step2. Set value to rsNode_ which context type is EFFECT.
     * @tc.expected: step2. Value can be set correctly.
     */
    rosenRenderContext->SetAlwaysSnapshot(true);
    EXPECT_EQ(rosenRenderContext->rsNode_->GetStagingProperties().GetAlwaysSnapshot(), true);

    /**
     * @tc.steps: step3. Set value to rsNode_ which context type is not EFFECT.
     * @tc.expected: step3. Value is always false.
     */
    rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    rosenRenderContext->SetAlwaysSnapshot(true);
    EXPECT_EQ(rosenRenderContext->rsNode_->GetStagingProperties().GetAlwaysSnapshot(), false);
}

/**
 * @tc.name: GetWithRange001
 * @tc.desc: Test GetWithRange Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetWithRange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    NodeIdentity startID;
    NodeIdentity endID;
    startID.first = "test1";
    endID.first = "test2";
    bool isStartRect = true;
    int32_t errorCode = 0;
    ComponentSnapshot::JsCallback callback = [&](std::shared_ptr<Media::PixelMap> pixmap, int32_t errCode,
        std::function<void()> finishCallback) {
        errorCode = errCode;
    };
    SnapshotOptions options{};

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetWithRange.
     * @tc.expected: Check error code.
     */
    ComponentSnapshot snapshot;
    snapshot.GetWithRange(startID, endID, isStartRect, std::move(callback), options);
    ASSERT_NE(callback, nullptr);
    EXPECT_EQ(errorCode, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: GetWithRange002
 * @tc.desc: Test GetWithRange Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetWithRange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    NodeIdentity startID;
    NodeIdentity endID;
    startID.second = 0;
    endID.second = 0;
    bool isStartRect = true;
    int32_t errorCode = 0;
    ComponentSnapshot::JsCallback callback = [&](std::shared_ptr<Media::PixelMap> pixmap, int32_t errCode,
        std::function<void()> finishCallback) {
        errorCode = errCode;
    };
    SnapshotOptions options{};

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetWithRange.
     * @tc.expected: Check error code.
     */
    ComponentSnapshot snapshot;
    snapshot.GetWithRange(startID, endID, isStartRect, std::move(callback), options);
    ASSERT_NE(callback, nullptr);
    EXPECT_EQ(errorCode, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: GetWithRange003
 * @tc.desc: Test GetWithRange Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetWithRange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    NodeIdentity startID;
    NodeIdentity endID;
    startID.first = "test";
    endID.second = 0;
    bool isStartRect = true;
    int32_t errorCode = 0;
    ComponentSnapshot::JsCallback callback = [&](std::shared_ptr<Media::PixelMap> pixmap, int32_t errCode,
        std::function<void()> finishCallback) {
        errorCode = errCode;
    };
    SnapshotOptions options{};

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetWithRange.
     * @tc.expected: Check error code.
     */
    ComponentSnapshot snapshot;
    snapshot.GetWithRange(startID, endID, isStartRect, std::move(callback), options);
    ASSERT_NE(callback, nullptr);
    EXPECT_EQ(errorCode, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: GetWithRange004
 * @tc.desc: Test GetWithRange Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetWithRange004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    NodeIdentity startID;
    NodeIdentity endID;
    startID.second = 0;
    endID.first = "test";
    bool isStartRect = true;
    int32_t errorCode = 0;
    ComponentSnapshot::JsCallback callback = [&](std::shared_ptr<Media::PixelMap> pixmap, int32_t errCode,
        std::function<void()> finishCallback) {
        errorCode = errCode;
    };
    SnapshotOptions options{};

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetWithRange.
     * @tc.expected: Check error code.
     */
    ComponentSnapshot snapshot;
    snapshot.GetWithRange(startID, endID, isStartRect, std::move(callback), options);
    ASSERT_NE(callback, nullptr);
    EXPECT_EQ(errorCode, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: GetWithRange005
 * @tc.desc: Test GetWithRange Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetWithRange005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    NodeIdentity startID;
    NodeIdentity endID;
    startID.first = "test1";
    startID.second = 0;
    endID.first = "test2";
    endID.second = 0;
    bool isStartRect = true;
    int32_t errorCode = 0;
    ComponentSnapshot::JsCallback callback = [&](std::shared_ptr<Media::PixelMap> pixmap, int32_t errCode,
        std::function<void()> finishCallback) {
        errorCode = errCode;
    };
    SnapshotOptions options{};

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetWithRange.
     * @tc.expected: Check error code.
     */
    ComponentSnapshot snapshot;
    snapshot.GetWithRange(startID, endID, isStartRect, std::move(callback), options);
    ASSERT_NE(callback, nullptr);
    EXPECT_EQ(errorCode, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: GetWithRange006
 * @tc.desc: Test GetWithRange Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetWithRange006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    auto startNode = FrameNode::CreateFrameNode("startNode", -1, AceType::MakeRefPtr<Pattern>());
    auto endNode = FrameNode::CreateFrameNode("endNode", -1, AceType::MakeRefPtr<Pattern>());
    NodeIdentity startID;
    NodeIdentity endID;
    bool isStartRect = true;
    int32_t errorCode = -1;
    ComponentSnapshot::JsCallback callback = [&errorCode](std::shared_ptr<Media::PixelMap> pixmap, int32_t errCode,
        std::function<void()> finishCallback) {
        errorCode = errCode;
    };
    SnapshotOptions options{};

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetWithRange.
     * @tc.expected: Check error code.
     */
    startID.first = "0";
    endID.first = "endNode";
    ComponentSnapshot snapshot;
    snapshot.GetWithRange(startID, endID, isStartRect, std::move(callback), options);
    EXPECT_EQ(errorCode, ERROR_CODE_INTERNAL_ERROR);

    errorCode = -1;
    startID.first = "startNode";
    endID.first = "0";
    snapshot.GetWithRange(startID, endID, isStartRect, std::move(callback), options);
    EXPECT_EQ(errorCode, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: GetRangeIDNode001
 * @tc.desc: Test GetRangeIDNode Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetRangeIDNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    NodeIdentity startID;
    startID.first = "test1";
    startID.second = 0;

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetRangeIDNode.
     * @tc.expected: Check result.
     */
    ComponentSnapshot snapshot;
    auto startNode = snapshot.GetRangeIDNode(startID);
    EXPECT_EQ(startNode, nullptr);
}

/**
 * @tc.name: GetRangeIDNode002
 * @tc.desc: Test GetRangeIDNode Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetRangeIDNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    NodeIdentity startID;
    startID.first = "";
    startID.second = 1;

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetRangeIDNode.
     * @tc.expected: Check result.
     */
    ComponentSnapshot snapshot;
    auto startNode = snapshot.GetRangeIDNode(startID);
    EXPECT_EQ(startNode, nullptr);
}

/**
 * @tc.name: GetRangeIDStr001
 * @tc.desc: Test GetRangeIDStr Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetRangeIDStr001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    NodeIdentity startID;
    startID.first = "test1";
    startID.second = 0;

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetRangeIDStr.
     * @tc.expected: Check result.
     */
    ComponentSnapshot snapshot;
    auto startNode = snapshot.GetRangeIDStr(startID);
    EXPECT_EQ(startNode, "test1");
}

/**
 * @tc.name: GetRangeIDStr002
 * @tc.desc: Test GetRangeIDStr Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetRangeIDStr002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    NodeIdentity startID;
    startID.first = "";
    startID.second = 1;

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetRangeIDStr.
     * @tc.expected: Check result.
     */
    ComponentSnapshot snapshot;
    auto startNode = snapshot.GetRangeIDStr(startID);
    EXPECT_EQ(startNode, "1");
}

/**
 * @tc.name: GetRangeIDStr003
 * @tc.desc: Test GetRangeIDStr Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, GetRangeIDStr003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    NodeIdentity startID;
    startID.first = "";
    startID.second = 0;

    /**
     * @tc.steps: step2. Call ComponentSnapshot::GetRangeIDStr.
     * @tc.expected: Check result.
     */
    ComponentSnapshot snapshot;
    auto startNode = snapshot.GetRangeIDStr(startID);
    EXPECT_EQ(startNode, "0");
}

/**
 * @tc.name: OnCustomBackgroundColorUpdate001
 * @tc.desc: Test OnCustomBackgroundColorUpdate Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, OnCustomBackgroundColorUpdate001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    auto transitionModifier = rosenRenderContext->GetOrCreateTransitionModifier();
    ASSERT_NE(transitionModifier, nullptr);

    /**
     * @tc.steps: step1. Set custom background color.
     * @tc.expected: step1. Custom background color can be set correctly.
     */
    Color color = Color::BLUE;
    rosenRenderContext->OnCustomBackgroundColorUpdate(color);
    EXPECT_EQ(transitionModifier->backgroundColor_.GetValue(), color.GetValue());

    /**
     * @tc.steps: step2. Set custom background color while rsNode_ is null.
     * @tc.expected: step2. Custom background color set failed.
     */
    rosenRenderContext->rsNode_ = nullptr;
    rosenRenderContext->OnCustomBackgroundColorUpdate(Color::GREEN);
    EXPECT_EQ(transitionModifier->backgroundColor_.GetValue(), color.GetValue());
}

/**
 * @tc.name: OnBuilderBackgroundFlagUpdate001
 * @tc.desc: Test OnBuilderBackgroundFlagUpdate Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, OnBuilderBackgroundFlagUpdate001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    auto transitionModifier = rosenRenderContext->GetOrCreateTransitionModifier();
    ASSERT_NE(transitionModifier, nullptr);

    /**
     * @tc.steps: step1. Set BuilderBackgroundFlag.
     * @tc.expected: step1. BuilderBackgroundFlag can be set correctly.
     */
    rosenRenderContext->OnBuilderBackgroundFlagUpdate(true);
    EXPECT_TRUE(transitionModifier->isBuilderBackground_);

    /**
     * @tc.steps: step2. Set BuilderBackgroundFlag while rsNode_ is null.
     * @tc.expected: step2. BuilderBackgroundFlag set failed.
     */
    rosenRenderContext->rsNode_ = nullptr;
    rosenRenderContext->OnBuilderBackgroundFlagUpdate(false);
    EXPECT_TRUE(transitionModifier->isBuilderBackground_);
}

/**
 * @tc.name: OnBackgroundAlignUpdate001
 * @tc.desc: Test OnBackgroundAlignUpdate Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, OnBackgroundAlignUpdate001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    auto transitionModifier = rosenRenderContext->GetOrCreateTransitionModifier();
    ASSERT_NE(transitionModifier, nullptr);
    auto backgroundModifier = rosenRenderContext->GetOrCreateBackgroundModifier();
    ASSERT_NE(backgroundModifier, nullptr);

    /**
     * @tc.steps: step1. Set alignment.
     * @tc.expected: step1. alignment can be set correctly.
     */
    Alignment align = Alignment::TOP_CENTER;
    rosenRenderContext->OnBackgroundAlignUpdate(align);
    EXPECT_EQ(transitionModifier->align_.ToString(), align.ToString());
    EXPECT_EQ(backgroundModifier->align_.ToString(), align.ToString());

    /**
     * @tc.steps: step2. Set alignment while rsNode_ is null.
     * @tc.expected: step2. alignment set failed.
     */
    rosenRenderContext->rsNode_ = nullptr;
    rosenRenderContext->OnBackgroundAlignUpdate(Alignment::BOTTOM_RIGHT);
    EXPECT_EQ(transitionModifier->align_.ToString(), align.ToString());
    EXPECT_EQ(backgroundModifier->align_.ToString(), align.ToString());
}

/**
 * @tc.name: OnBackgroundPixelMapUpdate001
 * @tc.desc: Test OnBackgroundPixelMapUpdate Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, OnBackgroundPixelMapUpdate001, TestSize.Level1)
{
    const float EXPECT_WIDTH = 100.0f;
    const float EXPECT_HEIGHT = 150.0f;
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    auto transitionModifier = rosenRenderContext->GetOrCreateTransitionModifier();
    ASSERT_NE(transitionModifier, nullptr);
    auto backgroundModifier = rosenRenderContext->GetOrCreateBackgroundModifier();
    ASSERT_NE(backgroundModifier, nullptr);

    /**
     * @tc.steps: step1. Set alignment.
     * @tc.expected: step1. alignment can be set correctly.
     */
    RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(EXPECT_WIDTH, EXPECT_HEIGHT));
    rosenRenderContext->OnBackgroundPixelMapUpdate(pixelMap);
    RectF backgroundRegion = frameNode->GetBackGroundAccumulatedSafeAreaExpand();
    EXPECT_EQ(transitionModifier->initialBackgroundRegion_.ToString(), backgroundRegion.ToString());
    EXPECT_EQ(backgroundModifier->initialNodeWidth_, EXPECT_WIDTH);
    EXPECT_EQ(backgroundModifier->initialNodeHeight_, EXPECT_HEIGHT);

    /**
     * @tc.steps: step2. Set PixelMap while rsNode_ is null.
     * @tc.expected: step2. PixelMap set failed.
     */
    rosenRenderContext->rsNode_ = nullptr;
    transitionModifier->pixelMap_ = nullptr;
    backgroundModifier->pixelMap_ = nullptr;
    rosenRenderContext->OnBackgroundPixelMapUpdate(pixelMap);
    EXPECT_EQ(transitionModifier->pixelMap_, nullptr);
    EXPECT_EQ(backgroundModifier->pixelMap_, nullptr);
}

/**
 * @tc.name: UpdateCustomBackground001
 * @tc.desc: Test UpdateCustomBackground Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, UpdateCustomBackground001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);

    /**
     * @tc.steps: step1. Create transition modifier and get the modifier flag.
     * @tc.expected: step1. Creation successful.
     */
    rosenRenderContext->UpdateIsTransitionBackground(true);
    auto transitionModifier = rosenRenderContext->GetOrCreateTransitionModifier();
    ASSERT_NE(transitionModifier, nullptr);
    transitionModifier->Modify();
    ASSERT_NE(transitionModifier->flag_, nullptr);
    bool flag = transitionModifier->flag_->Get();

    /**
     * @tc.steps: step2. Call UpdateCustomBackground function.
     * @tc.expected: step2. The modifier flag is changed.
     */
    rosenRenderContext->UpdateCustomBackground();
    EXPECT_NE(transitionModifier->flag_->Get(), flag);
}

/**
 * @tc.name: OnTransform3DMatrixUpdate001
 * @tc.desc: Test OnTransform3DMatrixUpdate Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, OnTransform3DMatrixUpdate001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    float INDEX_0 = 0.0f;
    float INDEX_1 = 1.0f;
    float INDEX_100 = 100.0f;
    Matrix4 matrix4(INDEX_1, INDEX_0, INDEX_0, INDEX_0, INDEX_0, INDEX_1, INDEX_0, INDEX_0, INDEX_0, INDEX_0, INDEX_1,
        INDEX_0, INDEX_100, INDEX_0, INDEX_0, INDEX_1);
    rosenRenderContext->OnTransform3DMatrixUpdate(matrix4);
    auto perspectiveValue = rosenRenderContext->transformModifier_->GetPersp();
    auto xyTranslateValue = rosenRenderContext->transformModifier_->GetTranslate();
    auto translateZValue = rosenRenderContext->transformModifier_->GetTranslateZ();
    auto scaleXYValue = rosenRenderContext->transformModifier_->GetScale();
    auto scaleZValue = rosenRenderContext->transformModifier_->GetScaleZ();
    auto skewValue = rosenRenderContext->transformModifier_->GetSkew();
    auto quaternionValue = rosenRenderContext->transformModifier_->GetQuaternion();
    EXPECT_NE(perspectiveValue[0], 0);
    EXPECT_EQ(perspectiveValue[1], 0);
    EXPECT_EQ(perspectiveValue[2], 0);
    EXPECT_NE(perspectiveValue[3], 0);
    EXPECT_EQ(xyTranslateValue[0], 0);
    EXPECT_EQ(perspectiveValue[1], 0);
    EXPECT_EQ(translateZValue, 0);
    EXPECT_NE(scaleXYValue[0], 0);
    EXPECT_NE(scaleXYValue[1], 0);
    EXPECT_NE(scaleZValue, 0);
    EXPECT_EQ(skewValue[0], 0);
    EXPECT_EQ(skewValue[1], 0);
    EXPECT_EQ(skewValue[2], 0);
    EXPECT_EQ(quaternionValue[0], 0);
    EXPECT_EQ(quaternionValue[1], 0);
    EXPECT_EQ(quaternionValue[2], 0);
    EXPECT_NE(quaternionValue[3], 0);
}

/**
 * @tc.name: ClearModifiers001
 * @tc.desc: Test cast to RosenRenderContextTest
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, ClearModifiers001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object renderContext.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    auto rsNode = rosenRenderContext->rsNode_;
    ASSERT_NE(rsNode, nullptr);

    /**
     * @tc.steps: step2. set rotateZ is 90.
     * @tc.expected: GetRotation is 90.
     */
    auto angle = 90;
    rosenRenderContext->SetRotation(0, 0, angle);
    auto rotateZ = rsNode->GetStagingProperties().GetRotation();
    EXPECT_EQ(rotateZ, angle);

    /**
     * @tc.steps: step3. ClearModifiers.
     * @tc.expected: GetRotation is default value.
     */
    rosenRenderContext->ClearModifiers();
    rotateZ = rsNode->GetStagingProperties().GetRotation();
    EXPECT_EQ(rotateZ, 0);
}

/**
 * @tc.name: GetBitmapTest001
 * @tc.desc: Test RosenRenderContext GetBitmap with rsNode_ is nullptr
 * @tc.type: FUNC
 * @tc.require: issueICK0X0
 */
HWTEST_F(RosenRenderContextTest, GetBitmapTest001, TestSize.Level1)
{
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::CANVAS;
    contextParam.surfaceName.emplace("test");

    rosenRenderContext->rsNode_ = nullptr;
    RSBitmap bitmap;
    bool ret = rosenRenderContext->GetBitmap(bitmap, nullptr);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: GetBitmapTest002
 * @tc.desc: Test RosenRenderContext GetBitmap with rsNode_ is not nullptr
 * @tc.type: FUNC
 * @tc.require: issueICK0X0
 */
HWTEST_F(RosenRenderContextTest, GetBitmapTest002, TestSize.Level1)
{
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::CANVAS;
    contextParam.surfaceName.emplace("test");
    std::optional<RenderContext::ContextParam> contextParamValue = std::make_optional(contextParam);
    rosenRenderContext->InitContext(true, contextParamValue);
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);

    RSBitmap bitmap;
    bool ret = rosenRenderContext->GetBitmap(bitmap, nullptr);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: GetPixelMapTest001
 * @tc.desc: Test RosenRenderContext GetPixelMap with rsNode_ is nullptr
 * @tc.type: FUNC
 * @tc.require: issueICK0X0
 */
HWTEST_F(RosenRenderContextTest, GetPixelMapTest001, TestSize.Level1)
{
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::CANVAS;
    contextParam.surfaceName.emplace("test");

    rosenRenderContext->rsNode_ = nullptr;
    RSBitmap bitmap;
    bool ret = rosenRenderContext->GetPixelMap(nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: GetPixelMapTest002
 * @tc.desc: Test RosenRenderContext GetPixelMap with rsNode_ is not nullptr
 * @tc.type: FUNC
 * @tc.require: issueICK0X0
 */
HWTEST_F(RosenRenderContextTest, GetPixelMapTest002, TestSize.Level1)
{
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::CANVAS;
    contextParam.surfaceName.emplace("test");
    std::optional<RenderContext::ContextParam> contextParamValue = std::make_optional(contextParam);
    rosenRenderContext->InitContext(true, contextParamValue);
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);

    RSBitmap bitmap;
    bool ret = rosenRenderContext->GetPixelMap(nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: RemoveFromTreeTest001
 * @tc.desc: Test RosenRenderContext RemoveFromTree
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RemoveFromTreeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a rosenRenderContext
     */
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_EQ(rosenRenderContext->rsNode_, nullptr);

     /**
     * @tc.steps: step2. test RemoveFromTree function
     */
    rosenRenderContext->RemoveFromTree();
    ASSERT_EQ(rosenRenderContext->rsNode_, nullptr);
}

/**
 * @tc.name: RemoveFromTreeTest002
 * @tc.desc: Test RosenRenderContext RemoveFromTree
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RemoveFromTreeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a RemoveFromTree
     */
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::CANVAS;
    contextParam.surfaceName.emplace("test");
    std::optional<RenderContext::ContextParam> contextParamValue = std::make_optional(contextParam);
    rosenRenderContext->InitContext(true, contextParamValue);
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);

    /**
     * @tc.steps: step2. test RemoveFromTree function
     */
    rosenRenderContext->RemoveFromTree();
    EXPECT_EQ(rosenRenderContext->rsNode_ != nullptr, true);
    EXPECT_EQ(rosenRenderContext->rsNode_->isOnTheTreeInit_, true);
    EXPECT_EQ(rosenRenderContext->rsNode_->isOnTheTree_, false);
}

class MockRosenRenderContext : public RosenRenderContext {
public:
    MOCK_METHOD1(SetNeedUseCmdlistDrawRegion, void(bool needUseCmdlistDrawRegion));
};

/**
 * @tc.name: SetNeedUseCmdlistDrawRegion001
 * @tc.desc: Test RosenRenderContext SetNeedUseCmdlistDrawRegion
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, SetNeedUseCmdlistDrawRegion001, TestSize.Level1)
{
    auto mockRosenRenderContext = AceType::MakeRefPtr<MockRosenRenderContext>();
    EXPECT_CALL(*mockRosenRenderContext, SetNeedUseCmdlistDrawRegion(_)).Times(2);
    mockRosenRenderContext->SetNeedUseCmdlistDrawRegion(true);
    mockRosenRenderContext->SetNeedUseCmdlistDrawRegion(false);
}

/**
 * @tc.name: ShouldSkipAffineTransformation001
 * @tc.desc: Test ShouldSkipAffineTransformation Func.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, ShouldSkipAffineTransformation001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    RefPtr rosenRenderContext = InitRosenRenderContext(frameNode);
    ASSERT_NE(rosenRenderContext, nullptr);
    ASSERT_NE(rosenRenderContext->rsNode_, nullptr);
    rosenRenderContext->rsNode_->SetDrawNodeType(Rosen::DrawNodeType::DrawPropertyType);
    bool res = rosenRenderContext->ShouldSkipAffineTransformation(rosenRenderContext->rsNode_);
    rosenRenderContext->rsNode_->SetDrawNodeType(Rosen::DrawNodeType::GeometryPropertyType);
    res = rosenRenderContext->ShouldSkipAffineTransformation(rosenRenderContext->rsNode_);
    ASSERT_EQ(res, false);
    rosenRenderContext->rsNode_ = nullptr;
    ASSERT_EQ(rosenRenderContext->rsNode_, nullptr);
}
} // namespace OHOS::Ace::NG
