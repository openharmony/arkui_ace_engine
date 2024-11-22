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

#define private public
#define protected public

#include "test/unittest/core/rosen/rosen_render_context_test.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

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
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    RenderContext::ContextParam contextParam;
    contextParam.type = RenderContext::ContextType::CANVAS;
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
    rosenRenderContext->DoTextureExport(1);
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
 * @tc.desc: SyncGeometryFrame().
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
    std::shared_ptr<Rosen::RSNode> ret = rosenRenderContext->CreateHardwareSurface(param, isTextureExportNode);
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
 * @tc.name: RosenRenderContextTest016
 * @tc.desc: SyncGeometryProperties().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest016, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    ForegroundColorStrategy value = ForegroundColorStrategy::NONE;
    rosenRenderContext->OnForegroundColorStrategyUpdate(value);
    value = ForegroundColorStrategy::INVERT;
    rosenRenderContext->OnForegroundColorStrategyUpdate(value);
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
 * @tc.name: RosenRenderContextTest018
 * @tc.desc: OnBackgroundImageUpdate()/OnPixelStretchEffectUpdate()
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest018, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    BlurStyleOption bgBlurStyleObj;
    std::optional<BlurStyleOption> bgBlurStyle = std::make_optional(bgBlurStyleObj);
    rosenRenderContext->UpdateBackBlurStyle(bgBlurStyle);

    // option.IsPercentOption() false
    PixStretchEffectOption pixStretchEffectOption;
    pixStretchEffectOption.left = Dimension(1.0);
    pixStretchEffectOption.right = Dimension(1.0);
    pixStretchEffectOption.top = Dimension(1.0);
    pixStretchEffectOption.bottom = Dimension(1.0);
    rosenRenderContext->OnPixelStretchEffectUpdate(pixStretchEffectOption);

    // option.IsPercentOption() true
    pixStretchEffectOption.left = Dimension(1.0, DimensionUnit::PERCENT);
    pixStretchEffectOption.right = Dimension(1.0, DimensionUnit::PERCENT);
    pixStretchEffectOption.top = Dimension(1.0, DimensionUnit::PERCENT);
    pixStretchEffectOption.bottom = Dimension(1.0, DimensionUnit::PERCENT);
    rosenRenderContext->OnPixelStretchEffectUpdate(pixStretchEffectOption);
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
    EXPECT_EQ(ret.GetRawPtr() == nullptr, true);
    RefPtr<PixelMap> ret2 = rosenRenderContext->GetThumbnailPixelMap(true);
    EXPECT_EQ(ret.GetRawPtr() == nullptr, true);
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
    EXPECT_FALSE(rosenRenderContext->UpdateBlurBackgroundColor(bgBlurStyle2));

    std::optional<EffectOption> efffectOption = std::make_optional(EffectOption());
    EXPECT_TRUE(rosenRenderContext->UpdateBlurBackgroundColor(efffectOption));
    efffectOption->isValidColor = true;
    EXPECT_TRUE(rosenRenderContext->UpdateBlurBackgroundColor(efffectOption));
    efffectOption->isWindowFocused = false;
    EXPECT_FALSE(rosenRenderContext->UpdateBlurBackgroundColor(efffectOption));
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
}

/**
 * @tc.name: RosenRenderContextTest036
 * @tc.desc: UpdateWindowBlur.
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest036, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    if (!rosenRenderContext) {
        return;
    }
    rosenRenderContext->UpdateWindowBlur();
}
} // namespace OHOS::Ace::NG