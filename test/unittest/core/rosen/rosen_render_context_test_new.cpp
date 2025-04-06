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

#define private public
#define protected public

#include "test/unittest/core/rosen/rosen_render_context_test.h"
#include "core/components_ng/render/drawing.h"

#include "core/components_ng/pattern/stage/page_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

/**
 * @tc.name: RosenRenderContextTestNew001
 * @tc.desc: OnAttractionEffectUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    auto pipelineContext = rosenRenderContext->GetPipelineContext();
    EXPECT_NE(pipelineContext, nullptr);
    rosenRenderContext->SuggestOpIncNode(false, true);
    AttractionEffect effect;
    effect.fraction = 1.0f;
    effect.destinationX = Dimension(1.0, DimensionUnit::PX);
    effect.destinationY = Dimension(1.0, DimensionUnit::PX);
    rosenRenderContext->OnAttractionEffectUpdate(effect);
    Rosen::Vector2f dstPoint = { 1.0, 1.0 };
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetAttractionFractionValue(), 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetAttractionDstPointValue(), dstPoint);
}

/**
 * @tc.name: RosenRenderContextTestNew002
 * @tc.desc: NotifyHostTransformUpdated().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew002, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->SyncPartialRsProperties();
    std::shared_ptr<Rosen::RectF> drawRect = std::make_shared<Rosen::RectF>(1.0, 1.0, 1.0, 1.0);
    rosenRenderContext->UpdateDrawRegion(5, drawRect); // 5 is the index of drawRegionRects_
    rosenRenderContext->NotifyHostTransformUpdated(false);
    EXPECT_FALSE(frameNode->isTransformNotChanged_);
}

/**
 * @tc.name: RosenRenderContextTestNew003
 * @tc.desc: SavePaintRect().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew003, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->ResetSurface(1, 0);
    rosenRenderContext->SetMarkNodeGroup(false);
    rosenRenderContext->SavePaintRect(true, 0);
    EXPECT_EQ(rosenRenderContext->paintRect_, RectF(0.0, 0.0, 0.0, 0.0));
    rosenRenderContext->SavePaintRect(false, 0);
    EXPECT_EQ(rosenRenderContext->paintRect_, RectF(0.0, 0.0, 0.0, 0.0));
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    rosenRenderContext->SavePaintRect(true, 0);
    EXPECT_EQ(rosenRenderContext->paintRect_, RectF(0.0, 0.0, 0.0, 0.0));
    rosenRenderContext->SavePaintRect(false, 0);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
    EXPECT_EQ(rosenRenderContext->paintRect_, RectF(0.0, 0.0, 0.0, 0.0));
}

/**
 * @tc.name: RosenRenderContextTestNew004
 * @tc.desc: UpdatePaintRect().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew004, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->UpdatePaintRect(RectF(1.0, 1.0, 1.0, 1.0));
    EXPECT_EQ(rosenRenderContext->paintRect_, RectF(1.0, 1.0, 1.0, 1.0));
}

/**
 * @tc.name: RosenRenderContextTestNew005
 * @tc.desc: SetCommandPathMask().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew005, TestSize.Level1)
{
    std::string commands = "abcd";
    RSPath path;
    path.BuildFromSVGString(commands);
    ShapeMaskProperty property;
    property.fillColor = SHAPE_MASK_DEFAULT_COLOR;
    property.strokeColor = SHAPE_MASK_DEFAULT_COLOR;
    property.strokeWidth = 0.0f;
    RSColor color;
    color.SetColorQuad(property.fillColor);
    RSBrush brush(color);
    RSColor rsStrokeColor;
    rsStrokeColor.SetColorQuad(property.strokeColor);
    RSPen pen;
    pen.SetColor(rsStrokeColor);
    pen.SetWidth(property.strokeWidth);
    std::shared_ptr<Rosen::RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->SetCommandPathMask(commands, property);
    rosenRenderContext->SetClipBoundsWithCommands(commands);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetMask()->GetMaskPen().GetColor(),
        mask->GetMaskPen().GetColor());
}

/**
 * @tc.name: RosenRenderContextTestNew006
 * @tc.desc: SetOvalMask().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew006, TestSize.Level1)
{
    auto rect = RectF(1.0, 1.0, 1.0, 1.0);
    RSRect rsRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    RSPath path;
    path.AddOval(rsRect);
    ShapeMaskProperty property;
    property.fillColor = SHAPE_MASK_DEFAULT_COLOR;
    property.strokeColor = SHAPE_MASK_DEFAULT_COLOR;
    property.strokeWidth = 0.0f;
    RSColor color;
    color.SetColorQuad(property.fillColor);
    RSBrush brush(color);
    RSColor rsStrokeColor;
    rsStrokeColor.SetColorQuad(property.strokeColor);
    RSPen pen;
    pen.SetColor(rsStrokeColor);
    pen.SetWidth(property.strokeWidth);
    std::shared_ptr<Rosen::RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->SetOvalMask(rect, property);
    rosenRenderContext->ClipWithRect(rect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetMask()->GetMaskPen().GetColor(),
        mask->GetMaskPen().GetColor());
}

/**
 * @tc.name: RosenRenderContextTestNew007
 * @tc.desc: SetRoundRectMask().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew007, TestSize.Level1)
{
    auto rect = RectF(1.0, 1.0, 1.0, 1.0);
    RSRoundRect rsRoundRect;
    RoundRect roundRect;
    roundRect.SetRect(rect);
    roundRect.SetCornerRadius(1.0);
    RSRect rsRect(roundRect.GetRect().Left(), roundRect.GetRect().Top(), roundRect.GetRect().Right(),
        roundRect.GetRect().Bottom());
    rsRoundRect.SetRect(rsRect);
    EdgeF edge = roundRect.GetCornerRadius(RoundRect::TOP_LEFT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::TOP_LEFT_POS, edge.x, edge.y);
    edge = roundRect.GetCornerRadius(RoundRect::TOP_RIGHT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::TOP_RIGHT_POS, edge.x, edge.y);
    edge = roundRect.GetCornerRadius(RoundRect::BOTTOM_LEFT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::BOTTOM_LEFT_POS, edge.x, edge.y);
    edge = roundRect.GetCornerRadius(RoundRect::BOTTOM_RIGHT_POS);
    rsRoundRect.SetCornerRadius(RSRoundRect::BOTTOM_RIGHT_POS, edge.x, edge.y);
    RSPath path;
    path.AddRoundRect(rsRoundRect);
    ShapeMaskProperty property;
    property.fillColor = SHAPE_MASK_DEFAULT_COLOR;
    property.strokeColor = SHAPE_MASK_DEFAULT_COLOR;
    property.strokeWidth = 0.0f;
    RSColor color;
    color.SetColorQuad(property.fillColor);
    RSBrush brush(color);
    RSColor rsStrokeColor;
    rsStrokeColor.SetColorQuad(property.strokeColor);
    RSPen pen;
    pen.SetColor(rsStrokeColor);
    pen.SetWidth(property.strokeWidth);
    std::shared_ptr<Rosen::RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->SetRoundRectMask(roundRect, property);
    rosenRenderContext->ClipWithRoundRect(roundRect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetMask()->GetMaskPen().GetColor(),
        mask->GetMaskPen().GetColor());
}

/**
 * @tc.name: RosenRenderContextTestNew008
 * @tc.desc: SetCircleMask().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew008, TestSize.Level1)
{
    Circle circle;
    circle.SetAxisX(Dimension(1.0));
    circle.SetAxisY(Dimension(0.0));
    circle.SetRadius(Dimension(1.0));
    RSPath path;
    path.AddCircle(circle.GetAxisX().Value(), circle.GetAxisY().Value(), circle.GetRadius().Value());
    ShapeMaskProperty property;
    property.fillColor = SHAPE_MASK_DEFAULT_COLOR;
    property.strokeColor = SHAPE_MASK_DEFAULT_COLOR;
    property.strokeWidth = 0.0f;
    RSColor color;
    color.SetColorQuad(property.fillColor);
    RSBrush brush(color);
    RSColor rsStrokeColor;
    rsStrokeColor.SetColorQuad(property.strokeColor);
    RSPen pen;
    pen.SetColor(rsStrokeColor);
    pen.SetWidth(property.strokeWidth);
    std::shared_ptr<Rosen::RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->SetCircleMask(circle, property);
    rosenRenderContext->SetOpacityMultiplier(1.0);
    rosenRenderContext->ClipWithCircle(circle);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetMask()->GetMaskPen().GetColor(),
        mask->GetMaskPen().GetColor());
}

/**
 * @tc.name: RosenRenderContextTestNew009
 * @tc.desc: SetRectMask().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew009, TestSize.Level1)
{
    auto rect = RectF(1.0, 1.0, 1.0, 1.0);
    RSPath path;
    path.AddRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    ShapeMaskProperty property;
    property.fillColor = SHAPE_MASK_DEFAULT_COLOR;
    property.strokeColor = SHAPE_MASK_DEFAULT_COLOR;
    property.strokeWidth = 0.0f;
    RSColor color;
    color.SetColorQuad(property.fillColor);
    RSBrush brush(color);
    RSColor rsStrokeColor;
    rsStrokeColor.SetColorQuad(property.strokeColor);
    RSPen pen;
    pen.SetColor(rsStrokeColor);
    pen.SetWidth(property.strokeWidth);
    std::shared_ptr<Rosen::RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->SetRectMask(rect, property);
    rosenRenderContext->SetTranslate(0.0, 1.0, 0.0);
    rosenRenderContext->ClipWithOval(rect);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetMask()->GetMaskPen().GetColor(),
        mask->GetMaskPen().GetColor());
}

/**
 * @tc.name: RosenRenderContextTestNew010
 * @tc.desc: SetTransitionUserCallback().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew010, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    auto parentNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    parentNode->AddChild(frameNode);

    bool userFlag = false;
    TransitionFinishCallback userCallback = [&userFlag](bool ret) { userFlag = !userFlag; };
    rosenRenderContext->SetTransitionUserCallback(std::move(userCallback));
    rosenRenderContext->FireTransitionUserCallback(true);
    rosenRenderContext->InitEventClickEffect();
    EXPECT_TRUE(userFlag);

    bool outFlag = false;
    auto outCallback = [&outFlag]() { outFlag = !outFlag; };
    rosenRenderContext->SetTransitionOutCallback(std::move(outCallback));
    auto property = AceType::MakeRefPtr<NodeAnimatablePropertyBase>();
    rosenRenderContext->AttachNodeAnimatableProperty(property);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->propVisibility_ = VisibleType::INVISIBLE;
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->isDisappearing_ = false;
    frameNode->onMainTree_ = true;
    rosenRenderContext->DetachNodeAnimatableProperty(property);
    rosenRenderContext->OnTransitionOutFinish();
    EXPECT_TRUE(outFlag);

    bool inFlag = false;
    auto inCallback = [&inFlag]() { inFlag = !inFlag; };
    rosenRenderContext->SetTransitionInCallback(std::move(inCallback));
    rosenRenderContext->PostTransitionUserOutCallback();
    frameNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    rosenRenderContext->OnTransitionInFinish();
    EXPECT_TRUE(inFlag);
}

/**
 * @tc.name: RosenRenderContextTestNew011
 * @tc.desc: SetOpacity().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew011, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    EXPECT_FALSE(rosenRenderContext->IsUniRenderEnabled());
    rosenRenderContext->SetOpacity(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetAlpha(), 1.0);
    rosenRenderContext->SetFrame(0.0, 1.0, 0.0, 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame().data_[1], 1.0);
    rosenRenderContext->SetRenderPivot(1.0, 0.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().x_, 1.0);
    rosenRenderContext->SetBackgroundColor(SHAPE_MASK_DEFAULT_COLOR);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBackgroundColor(),
        OHOS::Rosen::RSColor::FromArgbInt(SHAPE_MASK_DEFAULT_COLOR));
    rosenRenderContext->SetScale(1.0, 0.0);
    rosenRenderContext->PaintPixmapBgImage();
    rosenRenderContext->PaintRSBgImage();
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetScale().data_[0], 1.0);
    rosenRenderContext->SetRenderFrameOffset(OffsetF(1.0, 0.0));
    EXPECT_EQ(rosenRenderContext->frameOffset_, OffsetF(1.0, 0.0));
    rosenRenderContext->SetShadowRadius(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowRadius(), 1.0);
    rosenRenderContext->SetShadowElevation(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowElevation(), 1.0);
    rosenRenderContext->SetShadowAlpha(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowAlpha(), 1.0);
    rosenRenderContext->SetShadowOffset(1.0, 0.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowOffsetX(), 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowOffsetY(), 0.0);
    rosenRenderContext->SetShadowColor(SHAPE_MASK_DEFAULT_COLOR);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowColor(),
        OHOS::Rosen::RSColor::FromArgbInt(SHAPE_MASK_DEFAULT_COLOR));
    rosenRenderContext->SetRotation(1.0, 0.0, 1.0);
    rosenRenderContext->DumpInfo();
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetRotationX(), 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetRotationY(), 0.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetRotation(), 1.0);
}

/**
 * @tc.name: RosenRenderContextTestNew012
 * @tc.desc: SetContentRectToFrame().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew012, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->OnRenderGroupUpdate(true);
    rosenRenderContext->OnSuggestedRenderGroupUpdate(true);
    rosenRenderContext->UpdateRenderGroup(true, false, true);
    auto updateCallback = [](std::vector<float>& param) {};
    rosenRenderContext->AddUpdateCallBack(std::move(updateCallback));
    auto attachCallback = [](int64_t param, bool ret) {};
    rosenRenderContext->AddAttachCallBack(std::move(attachCallback));
    rosenRenderContext->MarkNewFrameAvailable(nullptr);
    rosenRenderContext->OnRenderFitUpdate(RenderFit::BOTTOM_LEFT);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrameGravity(), Rosen::Gravity::BOTTOM_LEFT);
    std::string id = "id";
    rosenRenderContext->OnNodeNameUpdate(id);
    rosenRenderContext->SetContentRectToFrame(RectF(0.0, 1.0, 0.0, 1.0));
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame().data_[1], 1.0);
}

/**
 * @tc.name: RosenRenderContextTestNew013
 * @tc.desc: UpdatePlayAnimationValue().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew013, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    auto context = AceType::MakeRefPtr<RenderContext>();
    rosenRenderContext->RegisterSharedTransition(context, true);
    float scaleValue = 1.0; // 4.0 is the value of scaleValue
    rosenRenderContext->UpdatePlayAnimationValue(ClickEffectLevel::LIGHT, scaleValue);
    EXPECT_EQ(scaleValue, 1.0);
    ClickEffectInfo effectInfo;
    effectInfo.level = ClickEffectLevel::LIGHT;
    rosenRenderContext->UpdateClickEffectLevel(effectInfo);
    rosenRenderContext->ClickEffectPlayAnimation(TouchType::DOWN);
    EXPECT_FALSE(rosenRenderContext->isTouchUpFinished_);
    rosenRenderContext->UnregisterSharedTransition(context);
    BorderRadiusProperty property;
    property.SetRadius(Dimension(1.0_px));
    rosenRenderContext->UpdateBorderRadius(property);
    rosenRenderContext->SetActualForegroundColor(Color(SHAPE_MASK_DEFAULT_COLOR));
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetForegroundColor(),
        OHOS::Rosen::RSColor::FromArgbInt(SHAPE_MASK_DEFAULT_COLOR));
}

/**
 * @tc.name: RosenRenderContextTestNew014
 * @tc.desc: UpdateChainedTransition().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew014, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->transitionEffect_ = AceType::MakeRefPtr<RosenTransitionEffect>();
    rosenRenderContext->NotifyTransition(true);
    rosenRenderContext->OnMouseSelectUpdate(true, Color(SHAPE_MASK_DEFAULT_COLOR), Color(SHAPE_MASK_DEFAULT_COLOR));
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetModifierIds().size(), 1);
    rosenRenderContext->MarkDrivenRenderFramePaintState(true);
    rosenRenderContext->MarkDrivenRenderItemIndex(1);
    rosenRenderContext->MarkDrivenRender(true);
    rosenRenderContext->MarkContentChanged(true);
    RefPtr<NG::ChainedTransitionEffect> effect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(1.0);
    rosenRenderContext->UpdateChainedTransition(effect);
    EXPECT_FALSE(rosenRenderContext->hasDefaultTransition_);
}

/**
 * @tc.name: RosenRenderContextTestNew015
 * @tc.desc: SetFrameGravity().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew015, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->UpdateBackgroundAlign(Alignment::BOTTOM_LEFT);
    rosenRenderContext->UpdateLightUpEffect(1);
    rosenRenderContext->DumpAdvanceInfo();
    std::shared_ptr<RSNode> externalNode = rosenRenderContext->GetRSNode();
    rosenRenderContext->SetRSNode(externalNode);
    ASSERT_NE(rosenRenderContext->GetRSNode(), nullptr);
    rosenRenderContext->ClearDrawCommands();
    rosenRenderContext->SetSurfaceRotation(false);
    rosenRenderContext->rsTextureExport_ = std::make_shared<Rosen::RSTextureExport>(externalNode, 1);
    EXPECT_TRUE(rosenRenderContext->StopTextureExport());
    EXPECT_FALSE(rosenRenderContext->DoTextureExport(1));
    std::string scene = "scene";
    EXPECT_EQ(rosenRenderContext->CalcExpectedFrameRate(scene, 1.0), 0);
    rosenRenderContext->SetFrameGravity(OHOS::Rosen::Gravity::BOTTOM_LEFT);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrameGravity(), Rosen::Gravity::BOTTOM_LEFT);
}

/**
 * @tc.name: RosenRenderContextTestNew016
 * @tc.desc: SetBounds().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew016, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->SetUsingContentRectForRenderFrame(false, true);
    EXPECT_TRUE(rosenRenderContext->adjustRSFrameByContentRect_);
    EXPECT_FALSE(rosenRenderContext->useContentRectForRSFrame_);
    rosenRenderContext->SetSharedTranslate(1.0, 1.0);
    rosenRenderContext->ResetSharedTranslate();
    auto childContextOne = AceType::MakeRefPtr<RosenRenderContext>();
    auto childContextTwo = AceType::MakeRefPtr<RosenRenderContext>();
    rosenRenderContext->AddChild(childContextOne, 0);
    rosenRenderContext->AddChild(childContextTwo, 1);
    rosenRenderContext->RemoveChild(childContextOne);
    rosenRenderContext->ClearChildren();
    EXPECT_EQ(rosenRenderContext->GetRSNode()->children_.size(), 0);
    rosenRenderContext->SetBounds(1.0, 0.0, 1.0, 0.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBounds().data_[0], 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBounds().data_[1], 0.0);
}

/**
 * @tc.name: RosenRenderContextTestNew017
 * @tc.desc: OnBloomUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew017, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<PagePattern>(nullptr); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    SafeAreaInsets::Inset left { 0, 1 };
    SafeAreaInsets::Inset top { 0, 1 };
    SafeAreaInsets::Inset right { 0, 1 };
    SafeAreaInsets::Inset bottom { 0, 1 };
    SafeAreaInsets safeAreaInsets(left, top, right, bottom);
    auto context = PipelineContext::GetCurrentContext();
    context->UpdateSystemSafeArea(safeAreaInsets);
    rosenRenderContext->paintRect_ = RectF(1.0, 1.0, 1.0, 1.0);
    OverlayOptions overlay;
    overlay.x = Dimension(1.0_px);
    rosenRenderContext->OnOverlayTextUpdate(overlay);
    rosenRenderContext->OnBloomUpdate(false);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBloom(), false);
    rosenRenderContext->OnIlluminatedBorderWidthUpdate(Dimension(1.0_px));
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetIlluminatedBorderWidth(), 1.0);
    rosenRenderContext->OnLightIlluminatedUpdate(1);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetIlluminatedType(), 1);
    rosenRenderContext->OnLightColorUpdate(Color(SHAPE_MASK_DEFAULT_COLOR));
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetLightColor(),
        OHOS::Rosen::RSColor::FromArgbInt(SHAPE_MASK_DEFAULT_COLOR));
    MotionPathOption motionPathOption("test");
    rosenRenderContext->OnMotionPathUpdate(motionPathOption);
    rosenRenderContext->OnLightIntensityUpdate(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetLightIntensity(), 1.0);
    TranslateOptions translate { Dimension(1.0_px), Dimension(0.0_px), Dimension(1.0_px) };
    rosenRenderContext->OnLightPositionUpdate(translate);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetLightPosition().data_[0], 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetLightPosition().data_[1], 0.0);
}

/**
 * @tc.name: RosenRenderContextTestNew018
 * @tc.desc: OnClipEdgeUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew018, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<PagePattern>(nullptr); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    auto pattern = frameNode->GetPattern<PagePattern>();
    PageTransitionOption option;
    option.routeType = RouteType::PUSH;
    auto effect = AceType::MakeRefPtr<PageTransitionEffect>(PageTransitionType::EXIT, option);
    pattern->AddPageTransition(effect);
    rosenRenderContext->paintRect_ = RectF(1.0, 1.0, 1.0, 1.0);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    rosenRenderContext->UpdateClipShape(basicShape);
    rosenRenderContext->UpdateClipMask(basicShape);
    rosenRenderContext->OnClipMaskUpdate(basicShape);
    rosenRenderContext->OnClipShapeUpdate(basicShape);
    rosenRenderContext->PaintClip(SizeF(1.0, 1.0));
    rosenRenderContext->RemoveClipWithRRect();
    RefPtr<NG::ProgressMaskProperty> progress = AceType::MakeRefPtr<NG::ProgressMaskProperty>();
    progress->SetColor(Color::BLUE);
    rosenRenderContext->UpdateProgressMask(progress);
    rosenRenderContext->OnProgressMaskUpdate(progress);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetClipToBounds(), true);
    rosenRenderContext->OnClipEdgeUpdate(false);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetClipToBounds(), false);
}

/**
 * @tc.name: RosenRenderContextTestNew019
 * @tc.desc: PaintGradient().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew019, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<PagePattern>(nullptr); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    rosenRenderContext->paintRect_ = RectF(1.0, 1.0, 1.0, 1.0);
    NG::Gradient gradient;
    GradientColor color(Color::BLACK);
    gradient.AddColor(color);
    rosenRenderContext->UpdateLinearGradient(gradient);
    rosenRenderContext->UpdateSweepGradient(gradient);
    rosenRenderContext->UpdateRadialGradient(gradient);
    rosenRenderContext->SetOpacity(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetAlpha(), 1.0);
    rosenRenderContext->OnLinearGradientUpdate(gradient);
    rosenRenderContext->OnSweepGradientUpdate(gradient);
    rosenRenderContext->OnRadialGradientUpdate(gradient);
    rosenRenderContext->PaintGradient(SizeF(1.0, 0.0));
    auto shader = std::make_shared<Rosen::RSShader>();
    rosenRenderContext->SetBackgroundShader(shader);
    TransitionOptions options;
    options.Type = TransitionType::APPEARING;
    auto optionsPtr = std::make_unique<TransitionOptions>(options);
    rosenRenderContext->UpdateTransition(options);
    EXPECT_NE(rosenRenderContext->GetRSTransitionWithoutType(optionsPtr, SizeF(0.0, 1.0)), nullptr);
    rosenRenderContext->CleanTransition();
    rosenRenderContext->SetShadowAlpha(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowAlpha(), 1.0);
    rosenRenderContext->SetShadowOffset(1.0, 0.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowOffsetX(), 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowOffsetY(), 0.0);
}

/**
 * @tc.name: RosenRenderContextTestNew020
 * @tc.desc: OnClipEdgeUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew020, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<PagePattern>(nullptr); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    auto property = std::make_shared<Rosen::RSPropertyBase>();
    std::shared_ptr<Rosen::RSModifier> modifier = std::make_shared<Rosen::RSBackgroundShaderModifier>(property);
    rosenRenderContext->AddModifier(modifier);
    rosenRenderContext->paintRect_ = RectF(1.0, 1.0, 1.0, 1.0);
    BrightnessOption option;
    std::optional<BrightnessOption> brightnessOption = std::make_optional(option);
    rosenRenderContext->OnFgDynamicBrightnessOptionUpdate(brightnessOption);
    rosenRenderContext->OnBgDynamicBrightnessOptionUpdate(brightnessOption);
    rosenRenderContext->OnDynamicLightUpDegreeUpdate(0.0);
    rosenRenderContext->OnDynamicLightUpRateUpdate(1.0);
    rosenRenderContext->OnDynamicDimDegreeUpdate(0.0);
    rosenRenderContext->SetRenderFrameOffset(OffsetF(1.0, 0.0));
    EXPECT_EQ(rosenRenderContext->frameOffset_, OffsetF(1.0, 0.0));
    std::vector<std::pair<float, float>> fractionStops;
    fractionStops.push_back(std::pair<float, float>(0.0f, 1.0f));
    CalcDimension dimensionRadius(0.0);
    NG::LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, NG::GradientDirection::LEFT);
    rosenRenderContext->OnLinearGradientBlurUpdate(blurPara);
    rosenRenderContext->SetShadowRadius(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowRadius(), 1.0);
    rosenRenderContext->OnSystemBarEffectUpdate(false);
    rosenRenderContext->RemoveModifier(modifier);
    rosenRenderContext->UpdateFrontGrayScale(1.0_vp);
    rosenRenderContext->UpdateFrontBrightness(1.0_vp);
    rosenRenderContext->UpdateFrontContrast(1.0_vp);
    rosenRenderContext->UpdateFrontSaturate(1.0_vp);
    rosenRenderContext->UpdateFrontSepia(1.0_vp);
    InvertVariant invert = 0.0f;
    rosenRenderContext->UpdateFrontInvert(invert);
    rosenRenderContext->UpdateFrontHueRotate(0.0);
    rosenRenderContext->UpdateFrontColorBlend(Color::GRAY);
    rosenRenderContext->PaintGraphics();
    rosenRenderContext->SetRotation(1.0, 0.0, 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetRotationX(), 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetRotationY(), 0.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetRotation(), 1.0);
}

/**
 * @tc.name: RosenRenderContextTestNew021
 * @tc.desc: OnBackBlendApplyTypeUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew021, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<PagePattern>(nullptr); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    auto property = std::make_shared<Rosen::RSPropertyBase>();
    std::shared_ptr<Rosen::RSModifier> modifier = std::make_shared<Rosen::RSBackgroundShaderModifier>(property);
    rosenRenderContext->AddModifier(modifier);
    rosenRenderContext->paintRect_ = RectF(1.0, 1.0, 1.0, 1.0);
    rosenRenderContext->OnBackBlendApplyTypeUpdate(BlendApplyType::OFFSCREEN);
    rosenRenderContext->OnBackBlendModeUpdate(BlendMode::SATURATION);
    rosenRenderContext->AnimateHoverEffectScale(true);
    EXPECT_FALSE(rosenRenderContext->isHoveredScale_);
    MotionBlurOption motionBlurOption;
    motionBlurOption.radius = 5;
    rosenRenderContext->UpdateMotionBlur(motionBlurOption);
    rosenRenderContext->AnimateHoverEffectBoard(true);
    EXPECT_FALSE(rosenRenderContext->isHoveredBoard_);
    rosenRenderContext->UpdateFrontBlurRadius(0.0_px);
    EXPECT_EQ(rosenRenderContext->GetFrontBlurRadius().value(), 0.0_px);
    BlurOption blurOption;
    blurOption.grayscale.emplace_back(0.0);
    blurOption.grayscale.emplace_back(1.0);
    rosenRenderContext->UpdateFrontBlur(1.0_px, blurOption);
    EXPECT_EQ(rosenRenderContext->GetFrontBlurRadius().value(), 1.0_px);
    rosenRenderContext->UpdateBackBlurRadius(0.0_px);
    EXPECT_EQ(rosenRenderContext->GetBackBlurRadius().value(), 0.0_px);
    rosenRenderContext->UpdateBackBlur(1.0_px, blurOption);
    EXPECT_EQ(rosenRenderContext->GetBackBlurRadius().value(), 1.0_px);
}

/**
 * @tc.name: RosenRenderContextTestNew022
 * @tc.desc: OnBackShadowUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew022, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<PagePattern>(nullptr); });
    auto rosenRenderContext = InitRosenRenderContext(frameNode);
    auto childNode =
        FrameNode::GetOrCreateFrameNode("child", -1, []() { return AceType::MakeRefPtr<PagePattern>(nullptr); });
    auto childRenderContext = InitRosenRenderContext(childNode);
    auto nodeOne = FrameNode::GetOrCreateFrameNode("nodeOne", 0, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto nodeTwo = FrameNode::GetOrCreateFrameNode("nodeTwo", 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto nodeThree = FrameNode::GetOrCreateFrameNode("nodeThree", 0, []() { return AceType::MakeRefPtr<Pattern>(); });
    std::list<RefPtr<FrameNode>> childrenOne;
    childrenOne.emplace_back(nodeOne);
    childrenOne.emplace_back(nodeTwo);
    std::list<RefPtr<FrameNode>> childrenTwo;
    childrenTwo.emplace_back(nodeTwo);
    childrenTwo.emplace_back(nodeThree);
    rosenRenderContext->AddFrameChildren(nullptr, childrenOne);
    rosenRenderContext->RebuildFrame(nullptr, childrenTwo);
    rosenRenderContext->RemoveFrameChildren(nullptr, childrenTwo);
    EXPECT_NE(childRenderContext, nullptr);
    rosenRenderContext->MoveFrame(nullptr, childNode, 0);
    Shadow shadow(1.0, Offset(1.0, 0.0), Color(SHAPE_MASK_DEFAULT_COLOR), ShadowStyle::None);
    shadow.SetIsFilled(true);
    shadow.SetShadowType(ShadowType::COLOR);
    shadow.SetShadowColorStrategy(ShadowColorStrategy::NONE);
    rosenRenderContext->OnBackShadowUpdate(shadow);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowOffsetX(), 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowOffsetY(), 0.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowColor(),
        OHOS::Rosen::RSColor::FromArgbInt(SHAPE_MASK_DEFAULT_COLOR));
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowMask(), false);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowIsFilled(), true);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowColorStrategy(),
        Rosen::SHADOW_COLOR_STRATEGY::COLOR_STRATEGY_NONE);
}

/**
 * @tc.name: RosenRenderContextTestNew023
 * @tc.desc: OnBackBlendApplyTypeUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew023, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<PagePattern>(nullptr); });
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    auto fgModifier = AceType::MakeRefPtr<Modifier>();
    rosenRenderContext->FlushForegroundModifier(fgModifier);
    auto overlayModifier = AceType::MakeRefPtr<Modifier>();
    rosenRenderContext->FlushOverlayModifier(overlayModifier);
    std::function<void(RSCanvas & canvas)> func = [](RSCanvas& canvas) {};
    rosenRenderContext->FlushOverlayDrawFunction(std::move(func));
    auto rect = RectF(1.0, 1.0, 1.0, 1.0);
    RoundRect roundRect;
    roundRect.SetRect(rect);
    roundRect.SetCornerRadius(1.0);
    rosenRenderContext->PaintFocusState(roundRect, Color::BLUE, 1.0_vp, true, true);
    rosenRenderContext->SetShadowRadius(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowRadius(), 1.0);
    rosenRenderContext->SetShadowElevation(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetShadowElevation(), 1.0);
    rosenRenderContext->FlushForegroundDrawFunction(std::move(func));
    auto contentModifier = AceType::MakeRefPtr<Modifier>();
    rosenRenderContext->FlushContentModifier(contentModifier);
    rosenRenderContext->FlushContentDrawFunction(std::move(func));
    rosenRenderContext->ClearFocusState();
    rosenRenderContext->PaintFocusState(1.0_vp, Color::BLACK, 0.0_vp, false);
    EXPECT_FALSE(rosenRenderContext->IsUniRenderEnabled());
    rosenRenderContext->SetOpacity(1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetAlpha(), 1.0);
    rosenRenderContext->PaintAccessibilityFocus();
    rosenRenderContext->PaintFocusState(1.0_vp, Color::BLACK, 0.0_vp, true);
    rosenRenderContext->SetFrame(0.0, 1.0, 0.0, 1.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetFrame().data_[1], 1.0);
    rosenRenderContext->SetRenderPivot(1.0, 0.0);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetPivot().x_, 1.0);
}

/**
 * @tc.name: RosenRenderContextTestNew024
 * @tc.desc: AdjustPaintRect().
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTestNew024, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode("frame", -1, []() { return AceType::MakeRefPtr<PagePattern>(nullptr); });
    RefPtr<RosenRenderContext> rosenRenderContext = InitRosenRenderContext(frameNode);
    auto parentNode =
        FrameNode::GetOrCreateFrameNode("parent", -1, []() { return AceType::MakeRefPtr<PagePattern>(nullptr); });
    parentNode->AddChild(frameNode);
    rosenRenderContext->OnZIndexUpdate(1);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    layoutProperty->SetUsingPosition(true);
    frameNode->SetLayoutProperty(layoutProperty);
    rosenRenderContext->RecalculatePosition();
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->frame_.rect_ = RectF(1.0, 1.0, 1.0, 1.0);
    auto offset = OffsetT<Dimension>(Dimension(1), Dimension(1));
    EdgesParam edges;
    CalcDimension top(1.0, DimensionUnit::VP);
    edges.SetTop(top);
    rosenRenderContext->UpdateOffsetEdges(edges);
    rosenRenderContext->OnPositionEdgesUpdate(edges);
    rosenRenderContext->UpdateOffset(offset);
    rosenRenderContext->RecalculatePosition();
    rosenRenderContext->ResetBlendBorderColor();
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBorderColor().data_[0],
        OHOS::Rosen::RSColor::FromArgbInt((Color::TRANSPARENT).GetValue()));
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBorderColor().data_[1],
        OHOS::Rosen::RSColor::FromArgbInt((Color::TRANSPARENT).GetValue()));
    rosenRenderContext->UpdatePositionEdges(edges);
    rosenRenderContext->OnOffsetEdgesUpdate(edges);
    rosenRenderContext->UpdatePosition(offset);
    rosenRenderContext->OnAnchorUpdate(offset);
    rosenRenderContext->BlendBorderColor(Color::BLUE);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBorderColor().data_[0],
        OHOS::Rosen::RSColor::FromArgbInt((Color::BLUE).GetValue()));
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBorderColor().data_[1],
        OHOS::Rosen::RSColor::FromArgbInt((Color::BLUE).GetValue()));
    rosenRenderContext->OnOffsetUpdate(offset);
    rosenRenderContext->OnPositionUpdate(offset);
    rosenRenderContext->ResetBlendBgColor();
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBackgroundColor(),
        OHOS::Rosen::RSColor::FromArgbInt((Color::TRANSPARENT).GetValue()));
    rosenRenderContext->BlendBgColor(Color::BLACK);
    EXPECT_EQ(rosenRenderContext->GetRSNode()->GetStagingProperties().GetBackgroundColor(),
        OHOS::Rosen::RSColor::FromArgbInt((Color::BLACK).GetValue()));
}
} // namespace OHOS::Ace::NG