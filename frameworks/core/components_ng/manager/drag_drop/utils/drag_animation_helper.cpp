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
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"

#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_controller_func_wrapper.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BEFORE_LIFTING_TIME = 650;
constexpr int32_t IMAGE_SHOW_TIME = 50;
constexpr int32_t PIXELMAP_ANIMATION_DURATION = 300;
constexpr int32_t BADGE_ANIMATION_DURATION = 200;
constexpr int32_t BADGE_ANIMATION_DELAY = 100;
constexpr int32_t NODE_RESET_DURATION = 200;
constexpr float DEFAULT_ANIMATION_SCALE = 0.95f;
constexpr float GATHER_SPRING_RESPONSE = 0.304f;
constexpr float GATHER_SPRING_DAMPING_FRACTION = 0.97f;
constexpr float GRID_MOVE_SCALE = 0.2f;
constexpr float LIST_MOVE_SCALE = 0.2f;
constexpr float EULER_NUMBER = 2.71828f;
constexpr float GATHER_OFFSET_RADIUS = 0.1f;
constexpr float PIXELMAP_DRAG_SCALE_MULTIPLE = 1.05f;
constexpr float BADGE_ANIMATION_SCALE = 1.0f;
constexpr Dimension BADGE_RELATIVE_OFFSET = 8.0_vp;
constexpr Dimension BADGE_DEFAULT_SIZE = 24.0_vp;
constexpr Dimension BADGE_TEXT_FONT_SIZE = 14.0_fp;
const Color BADGE_TEXT_FONT_COLOR = Color::FromString("#ffffffff");
const Color BADGE_BACKGROUND_COLOR = Color::FromString("#ff007dff");
constexpr float DEFAULT_INTERPOLATING_SPRING_VELOCITY = 10.0f;
constexpr float DEFAULT_INTERPOLATING_SPRING_MASS = 1.0f;
constexpr float DEFAULT_INTERPOLATING_SPRING_STIFFNESS = 410.0f;
constexpr float DEFAULT_INTERPOLATING_SPRING_DAMPING = 38.0f;
constexpr float DEFAULT_GRAYED = 0.4f;
constexpr float HALF_DIVIDE = 2.0f;
const RefPtr<InterpolatingSpring> DRAG_START_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 0.0f, 380.0f, 34.0f);
const RefPtr<InterpolatingSpring> DRAG_END_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 0.0f, 228.0f, 29.0f);
const RefPtr<Curve> DRAG_CONTROL_ANIMATION_CURVE =
    AceType::MakeRefPtr<ResponsiveSpringMotion>(0.347f, 0.99f, 0.0f);
}

void DragAnimationHelper::CalcDistanceBeforeLifting(bool isGrid, CalcResult& calcResult, OffsetF gatherNodeCenter,
    const std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo)
{
    for (const auto& child : gatherNodeChildrenInfo) {
        auto imageNode = child.imageNode.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto width = child.width;
        auto height = child.height;
        OffsetF curPos = {child.offset.GetX() + child.halfWidth, child.offset.GetY() + child.halfHeight};
        float dis = sqrt(pow(gatherNodeCenter.GetX() - curPos.GetX(), 2) +
            pow(gatherNodeCenter.GetY() - curPos.GetY(), 2));
        calcResult.maxDistance = std::max(calcResult.maxDistance, dis);
        calcResult.minDistance = calcResult.minDistance < 0 ? dis : std::min(calcResult.minDistance, dis);
        if (isGrid) {
            calcResult.maxTranslation = calcResult.maxTranslation < 0 ? std::min(width, height) :
                std::min(calcResult.maxTranslation, std::min(width, height));
        } else {
            calcResult.maxTranslation = calcResult.maxTranslation < 0 ? height :
                std::min(calcResult.maxTranslation, height);
        }
    }
    calcResult.maxTranslation *= isGrid ? GRID_MOVE_SCALE : LIST_MOVE_SCALE;
}

OffsetF DragAnimationHelper::CalcOffsetToTarget(OffsetF curPos, OffsetF targetPos, CalcResult& calcResult)
{
    if (NearZero(calcResult.maxDistance) || NearZero(calcResult.minDistance) || calcResult.maxTranslation < 0) {
        return { 0.0f, 0.0f };
    }

    float xDis = targetPos.GetX() - curPos.GetX();
    float yDis = targetPos.GetY() - curPos.GetY();
    float dis = sqrt(pow(xDis, 2) + pow(yDis, 2));
    if (NearZero(dis)) {
        return { 0.0f, 0.0f };
    }
    auto trans = calcResult.maxTranslation * pow(EULER_NUMBER, -(dis - calcResult.minDistance) /
        calcResult.maxDistance * GATHER_OFFSET_RADIUS);
    float x = xDis * trans / dis;
    float y = yDis * trans / dis;
    return { x, y };
}

void DragAnimationHelper::PlayGatherNodeTranslateAnimation(const RefPtr<FrameNode>& frameNode,
    const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(overlayManager);
    CHECK_NULL_VOID(frameNode);
    AnimationOption option;
    option.SetDuration(BEFORE_LIFTING_TIME);
    option.SetCurve(Curves::SHARP);
    auto gatherNodeCenter = DragDropFuncWrapper::GetPaintRectCenterToScreen(frameNode);
    auto gatherNodeChildrenInfo = overlayManager->GetGatherNodeChildrenInfo();

    bool isGrid = frameNode->GetTag() == V2::GRID_ITEM_ETS_TAG;
    CalcResult calcResult = { 0.0f, -1.0f, -1.0f };
    CalcDistanceBeforeLifting(isGrid, calcResult, gatherNodeCenter, gatherNodeChildrenInfo);
    AnimationUtils::Animate(
        option,
        [gatherNodeCenter, gatherNodeChildrenInfo, calcResult]() mutable {
            for (const auto& child : gatherNodeChildrenInfo) {
                auto imageNode = child.imageNode.Upgrade();
                auto curPos = child.offset + OffsetF(child.halfWidth, child.halfHeight);
                auto offset = CalcOffsetToTarget(curPos, gatherNodeCenter, calcResult);
                offset += child.offset;
                DragDropFuncWrapper::UpdateNodePositionToScreen(imageNode, offset);
            }
        });
}

void DragAnimationHelper::PlayGatherNodeOpacityAnimation(const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(overlayManager);
    auto gatherNodeChildrenInfo = overlayManager->GetGatherNodeChildrenInfo();

    AnimationOption opacityOption;
    opacityOption.SetDuration(IMAGE_SHOW_TIME);
    opacityOption.SetCurve(AceType::MakeRefPtr<CubicCurve>(0.0f, 0.0f, 1.0f, 1.0f));
    
    for (const auto& child : gatherNodeChildrenInfo) {
        auto imageNode = child.imageNode.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        imageContext->OpacityAnimation(opacityOption, 0.0f, 1.0f);
    }
}

void DragAnimationHelper::PlayGatherAnimationBeforeLifting(const RefPtr<DragEventActuator>& actuator)
{
    TAG_LOGI(AceLogTag::ACE_DRAG, "Play gather animation before lifting");
    CHECK_NULL_VOID(actuator);
    if (!actuator->IsNeedGather()) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto frameNode = actuator->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto gatherNode = actuator->GetGatherNode();
    CHECK_NULL_VOID(gatherNode);
    auto imageContext = gatherNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(0.0f), Dimension(0.0f)));
    auto gatherNodeChildrenInfo = actuator->GetGatherNodeChildrenInfo();
    DragEventActuator::MountGatherNode(manager, frameNode, gatherNode, gatherNodeChildrenInfo);
    actuator->ClearGatherNodeChildrenInfo();
    actuator->InitGatherNodesPosition(gatherNodeChildrenInfo);
    pipeline->FlushSyncGeometryNodeTasks();
    manager->SetIsGatherWithMenu(false);
    PlayGatherNodeOpacityAnimation(manager);
    PlayGatherNodeTranslateAnimation(frameNode, manager);
}

void DragAnimationHelper::PlayNodeAnimationBeforeLifting(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto previewOptions = frameNode->GetDragPreviewOption();
    if (!previewOptions.defaultAnimationBeforeLifting) {
        return;
    }
    AnimationOption option;
    option.SetDuration(BEFORE_LIFTING_TIME);
    auto springCurve = AceType::MakeRefPtr<InterpolatingSpring>(DEFAULT_INTERPOLATING_SPRING_VELOCITY,
        DEFAULT_INTERPOLATING_SPRING_MASS, DEFAULT_INTERPOLATING_SPRING_STIFFNESS,
        DEFAULT_INTERPOLATING_SPRING_DAMPING);
    option.SetCurve(springCurve);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformScale({ 1.0f, 1.0f });

    AnimationUtils::Animate(
        option,
        [renderContext]() mutable {
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformScale({ DEFAULT_ANIMATION_SCALE, DEFAULT_ANIMATION_SCALE });
        });
}

void DragAnimationHelper::PlayNodeResetAnimation(const RefPtr<DragEventActuator>& actuator)
{
    CHECK_NULL_VOID(actuator);
    auto frameNode = actuator->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    bool defaultAnimationBeforeLifting = frameNode->GetDragPreviewOption().defaultAnimationBeforeLifting;
    if (!defaultAnimationBeforeLifting) {
        return;
    }
    auto frameContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(frameContext);
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    const RefPtr<Curve> curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.33f, 0.67f, 1.0f);
    option.SetCurve(curve);
    AnimationUtils::Animate(
        option,
        [frameContext]() mutable {
            frameContext->UpdateTransformScale({ 1.0f, 1.0f });
        },
        option.GetOnFinishEvent());
}

void DragAnimationHelper::PlayGatherAnimation(const RefPtr<FrameNode>& frameNode,
    const RefPtr<OverlayManager>& overlayManager)
{
    TAG_LOGI(AceLogTag::ACE_DRAG, "Play gather animation");
    CHECK_NULL_VOID(frameNode);
    auto gatherNodeCenter = DragDropFuncWrapper::GetPaintRectCenter(frameNode);
    CHECK_NULL_VOID(overlayManager);
    auto gatherNodeChildrenInfo = overlayManager->GetGatherNodeChildrenInfo();
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(0.0_vp);
    borderRadius.multiValued = false;
    for (const auto& child : gatherNodeChildrenInfo) {
        auto imageNode = child.imageNode.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        imageContext->UpdateBorderRadius(borderRadius);
    }

    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    const RefPtr<Curve> curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(GATHER_SPRING_RESPONSE,
        GATHER_SPRING_DAMPING_FRACTION, 0.0f);
    option.SetCurve(curve);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameNodeSize = geometryNode->GetFrameSize();
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    GatherAnimationInfo gatherAnimationInfo = { PIXELMAP_DRAG_SCALE_MULTIPLE, frameNodeSize.Width(),
        frameNodeSize.Height(), gatherNodeCenter, renderContext->GetBorderRadius() };
    AnimationUtils::Animate(
        option,
        [weakOverlayManager = AceType::WeakClaim(AceType::RawPtr(overlayManager)), gatherAnimationInfo,
            weak = AceType::WeakClaim(AceType::RawPtr(frameNode))]() {
            auto overlayManager = weakOverlayManager.Upgrade();
            auto frameNode = weak.Upgrade();
            DragDropManager::UpdateGatherNodeAttr(overlayManager, gatherAnimationInfo);
            DragDropManager::UpdateGatherNodePosition(overlayManager, frameNode);
        },
        option.GetOnFinishEvent());
}

void DragAnimationHelper::ShowBadgeAnimation(const RefPtr<FrameNode>& textNode)
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    CHECK_NULL_VOID(textNode);
    auto textNodeContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textNodeContext);
    textNodeContext->SetVisible(true);
    auto windowScale = dragDropManager->GetWindowScale();
    auto badgeScale = GreatNotEqual(windowScale, 0.0f) ? BADGE_ANIMATION_SCALE / windowScale : BADGE_ANIMATION_SCALE;
    if (!dragDropManager->IsShowBadgeAnimation()) {
        textNodeContext->UpdateTransformScale({ badgeScale, badgeScale });
        return;
    }
    textNodeContext->UpdateTransformScale({ 0.0f, 0.0f });
    RefPtr<Curve> interpolatingSpring = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 628.0f, 40.0f);
    CHECK_NULL_VOID(interpolatingSpring);
    AnimationOption textOption;
    textOption.SetDuration(BADGE_ANIMATION_DURATION);
    textOption.SetCurve(interpolatingSpring);
    textOption.SetDelay(BADGE_ANIMATION_DELAY);
    AnimationUtils::Animate(
        textOption,
        [textNodeContext, badgeScale]() mutable {
            textNodeContext->UpdateTransformScale({ badgeScale, badgeScale });
        },
        textOption.GetOnFinishEvent());

    dragDropManager->SetIsShowBadgeAnimation(false);
}

OffsetF DragAnimationHelper::CalcBadgeTextOffset(const RefPtr<MenuPattern>& menuPattern,
    const RefPtr<FrameNode>& imageNode, const RefPtr<PipelineBase>& context, int32_t badgeLength)
{
    CHECK_NULL_RETURN(imageNode, OffsetF());
    CHECK_NULL_RETURN(menuPattern, OffsetF());
    auto offset = imageNode->GetPaintRectOffset();
    auto width = imageNode->GetGeometryNode()->GetFrameSize().Width();
    auto scaleAfter = menuPattern->GetPreviewAfterAnimationScale();
    auto menuTheme = context->GetTheme<NG::MenuTheme>();
    CHECK_NULL_RETURN(menuTheme, OffsetF());
    auto previewAfterAnimationScale =
        LessNotEqual(scaleAfter, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : scaleAfter;
    double textOffsetX = offset.GetX() + width * previewAfterAnimationScale -
        BADGE_RELATIVE_OFFSET.ConvertToPx() - (BADGE_RELATIVE_OFFSET.ConvertToPx() * badgeLength);
    double textOffsetY = offset.GetY() - BADGE_RELATIVE_OFFSET.ConvertToPx();
    return OffsetF(textOffsetX, textOffsetY);
}

void DragAnimationHelper::CalcBadgeTextPosition(const RefPtr<MenuPattern>& menuPattern,
    const RefPtr<OverlayManager>& manager, const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& textNode)
{
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(textNode);
    CHECK_NULL_VOID(menuPattern);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto frameNode = FrameNode::GetFrameNode(menuPattern->GetTargetTag(), menuPattern->GetTargetId());
    CHECK_NULL_VOID(frameNode);
    auto badgeNumber = frameNode->GetDragPreviewOption().GetCustomerBadgeNumber();
    auto childSize = badgeNumber.has_value() ? static_cast<size_t>(badgeNumber.value()) :
                                        manager->GetGatherNodeChildrenInfo().size() + 1;
    TAG_LOGI(AceLogTag::ACE_DRAG, "Badge node number %{public}d, children count %{public}d",
        badgeNumber.value_or(-1), static_cast<int32_t>(manager->GetGatherNodeChildrenInfo().size()));
    auto badgeLength = std::to_string(childSize).size();
    UpdateBadgeLayoutAndRenderContext(textNode, badgeLength, childSize);
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    auto offset = CalcBadgeTextOffset(menuPattern, imageNode, pipelineContext, badgeLength);
    textRenderContext->UpdatePosition(OffsetT<Dimension>(Dimension(offset.GetX()), Dimension(offset.GetY())));
    textNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
    textNode->MarkModifyDone();
    textNode->SetLayoutDirtyMarked(true);
    textNode->SetActive(true);
    auto context = textNode->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(textNode);
    }
    pipelineContext->FlushSyncGeometryNodeTasks();
}

void DragAnimationHelper::UpdateBadgeLayoutAndRenderContext(
    const RefPtr<FrameNode>& textNode, int32_t badgeLength, int32_t childSize)
{
    if (childSize <= 1) {
        return;
    }
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(std::to_string(childSize));
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    textLayoutProperty->UpdateTextColor(BADGE_TEXT_FONT_COLOR);
    textLayoutProperty->UpdateFontSize(BADGE_TEXT_FONT_SIZE);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    int64_t textWidth = BADGE_DEFAULT_SIZE.ConvertToPx() + (BADGE_RELATIVE_OFFSET.ConvertToPx() * (badgeLength - 1));
    auto textSize = CalcSize(NG::CalcLength(textWidth), NG::CalcLength(BADGE_DEFAULT_SIZE.ConvertToPx()));
    textLayoutProperty->UpdateUserDefinedIdealSize(textSize);

    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->SetVisible(true);
    textRenderContext->UpdateBackgroundColor(BADGE_BACKGROUND_COLOR);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(BADGE_DEFAULT_SIZE);
    textRenderContext->UpdateBorderRadius(borderRadius);
}

void DragAnimationHelper::UpdateGatherNodeToTop()
{
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(mainPipeline);
    auto manager = mainPipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->UpdateGatherNodeToTop();
}

void DragAnimationHelper::ShowGatherAnimationWithMenu(const RefPtr<FrameNode>& menuWrapperNode)
{
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(mainPipeline);
    auto manager = mainPipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->SetIsGatherWithMenu(true);

    mainPipeline->AddAfterRenderTask([weakWrapperNode = AceType::WeakClaim(AceType::RawPtr(menuWrapperNode)),
        weakManager = AceType::WeakClaim(AceType::RawPtr(manager))]() {
        auto menuWrapperNode = weakWrapperNode.Upgrade();
        CHECK_NULL_VOID(menuWrapperNode);
        auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(menuWrapperPattern);
        auto manager = weakManager.Upgrade();
        auto textNode = menuWrapperPattern->GetBadgeNode();
        auto imageNode = menuWrapperPattern->GetPreview();
        auto menuNode = menuWrapperPattern->GetMenu();
        CHECK_NULL_VOID(menuNode);
        auto menuPattern = menuNode->GetPattern<MenuPattern>();
        DragAnimationHelper::PlayGatherAnimation(imageNode, manager);
        DragAnimationHelper::CalcBadgeTextPosition(menuPattern, manager, imageNode, textNode);
        DragAnimationHelper::ShowBadgeAnimation(textNode);
    });
}

void DragAnimationHelper::SetPreOpacity(const RefPtr<FrameNode>& preNode)
{
    auto grayedOpacity = preNode->GetPreGrayedOpacity();
    DoGrayedAnimation(preNode, grayedOpacity, DRAG_END_ANIMATION_CURVE);
}

void DragAnimationHelper::DoDragStartGrayedAnimation(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    float opacity = 1.0f;
    if (renderContext->HasOpacity()) {
        opacity = renderContext->GetOpacityValue();
        frameNode->SetPreGrayedOpacity(opacity);
    }
    DoGrayedAnimation(frameNode, opacity * DEFAULT_GRAYED, DRAG_START_ANIMATION_CURVE);
}

void DragAnimationHelper::DoGrayedAnimation(
    const RefPtr<FrameNode>& frameNode, float opacity, RefPtr<InterpolatingSpring> cure)
{
    CHECK_NULL_VOID(frameNode);
    auto frameTag = frameNode->GetTag();
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (gestureHub->IsTextCategoryComponent(frameTag)) {
        return;
    }
    AnimationOption option;
    option.SetCurve(cure);
    AnimationUtils::Animate(
        option, [frameNode, opacity]() { ACE_UPDATE_NODE_RENDER_CONTEXT(Opacity, opacity, frameNode); },
        option.GetOnFinishEvent());
}

RefPtr<FrameNode> DragAnimationHelper::CreateImageNode(const RefPtr<PixelMap>& pixelMap)
{
    CHECK_NULL_RETURN(pixelMap, nullptr);
    auto width = pixelMap->GetWidth();
    auto height = pixelMap->GetHeight();
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_RETURN(imageNode, nullptr);
    auto renderProps = imageNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(renderProps, nullptr);
    renderProps->UpdateImageInterpolation(ImageInterpolation::HIGH);
    renderProps->UpdateNeedBorderRadius(false);
    auto props = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    props->UpdateAutoResize(false);
    props->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    auto targetSize = CalcSize(NG::CalcLength(width), NG::CalcLength(height));
    props->UpdateUserDefinedIdealSize(targetSize);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_RETURN(imageContext, nullptr);
    Vector5F rotate = Vector5F(0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    imageContext->UpdateTransformRotate(rotate);
    imageContext->UpdateClipEdge(true);
    imageContext->UpdateBorderRadius(BorderRadiusProperty(Dimension()));
    imageContext->UpdateOpacity(1.0f);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    if (imagePattern) {
        imagePattern->SetSyncLoad(true);
    }
    ClickEffectInfo clickEffectInfo;
    clickEffectInfo.level = ClickEffectLevel::LIGHT;
    clickEffectInfo.scaleNumber = DEFAULT_ANIMATION_SCALE;
    imageContext->UpdateClickEffectLevel(clickEffectInfo);
    return imageNode;
}

RefPtr<FrameNode> DragAnimationHelper::CreateGatherNode(const RefPtr<FrameNode>& frameNode,
    std::vector<GatherNodeChildInfo>& gatherNodeInfo)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto parentNode = DragDropFuncWrapper::FindItemParentNode(frameNode);
    CHECK_NULL_RETURN(parentNode, nullptr);
    auto scrollPattern = parentNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(scrollPattern, nullptr);
    auto children = scrollPattern->GetVisibleSelectedItems();
    if (children.empty()) {
        return nullptr;
    }

    auto stackNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto geometryNode = stackNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    geometryNode->SetFrameOffset({0.0f, 0.0f});
    gatherNodeInfo.clear();
    for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
        auto itemFrameNode = (*iter);
        if (itemFrameNode == frameNode) {
            continue;
        }
        GatherNodeChildInfo gatherNodeChildInfo;
        auto imageNode = CreateGatherImageNode(itemFrameNode, gatherNodeChildInfo);
        CHECK_NULL_RETURN(imageNode, nullptr);
        stackNode->AddChild(imageNode);
        gatherNodeInfo.push_back(gatherNodeChildInfo);
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "Create gather node success, count %{public}d",
        static_cast<int32_t>(children.size()));
    return stackNode;
}

RefPtr<FrameNode> DragAnimationHelper::GetOrCreateGatherNode(const RefPtr<NG::OverlayManager>& overlayManager,
    const RefPtr<DragEventActuator>& actuator, std::vector<GatherNodeChildInfo>& info)
{
    CHECK_NULL_RETURN(actuator, nullptr);
    if (!actuator->IsNeedGather()) {
        return nullptr;
    }
    auto frameNode = actuator->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto previewOptions = frameNode->GetDragPreviewOption();
    if (!previewOptions.isMultiSelectionEnabled) {
        return nullptr;
    }
    CHECK_NULL_RETURN(overlayManager, nullptr);
    auto gatherNode = overlayManager->GetGatherNode();
    if (!gatherNode) {
        gatherNode = CreateGatherNode(frameNode, info);
        if (gatherNode) {
            MarkDirtyNode(gatherNode);
        }
        return gatherNode;
    } else {
        info = overlayManager->GetGatherNodeChildrenInfo();
        overlayManager->RemoveGatherNode();
    }
    return gatherNode;
}

RefPtr<FrameNode> DragAnimationHelper::CreateGatherImageNode(const RefPtr<FrameNode>& frameNode,
    GatherNodeChildInfo& gatherNodeChildInfo)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pixelMap = DragDropFuncWrapper::GetGatherNodePreviewPixelMap(frameNode);
    CHECK_NULL_RETURN(pixelMap, nullptr);
    int32_t width = pixelMap->GetWidth();
    int32_t height = pixelMap->GetHeight();
    auto offset = DragDropFuncWrapper::GetPaintRectCenter(frameNode) - OffsetF(width / 2.0f, height / 2.0f);
    auto imageNode = CreateImageNode(pixelMap);
    CHECK_NULL_RETURN(imageNode, nullptr);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_RETURN(imageContext, nullptr);
    imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(offset.GetX()), Dimension(offset.GetY())));

    gatherNodeChildInfo = { imageNode,
        offset + DragDropFuncWrapper::GetCurrentWindowOffset(frameNode->GetContextRefPtr()), width, height,
        width / 2.0f, height / 2.0f, WeakPtr<FrameNode>(frameNode) };
    return imageNode;
}

void DragAnimationHelper::MountGatherNode(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& gatherNode,
    const std::vector<GatherNodeChildInfo>& gatherNodeInfo)
{
    if (!overlayManager || !frameNode || !gatherNode) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "Mount gather node");
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        auto windowScene = overlayManager->FindWindowScene(frameNode);
        overlayManager->MountGatherNodeToWindowScene(gatherNode, gatherNodeInfo, windowScene);
    } else {
        overlayManager->MountGatherNodeToRootNode(gatherNode, gatherNodeInfo);
    }
}

void DragAnimationHelper::MarkDirtyNode(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->MarkModifyDone();
    frameNode->SetLayoutDirtyMarked(true);
    auto context = frameNode->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(frameNode);
    }

    auto children = frameNode->GetChildren();
    for (const auto& child : children) {
        CHECK_NULL_VOID(child);
        auto imageNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(imageNode);
        imageNode->MarkModifyDone();
        imageNode->SetLayoutDirtyMarked(true);
        if (context) {
            context->FlushUITaskWithSingleDirtyNode(imageNode);
        }
    }
}

void DragAnimationHelper::InitGatherNodeAttr(const RefPtr<FrameNode>& gatherNode,
    const std::vector<GatherNodeChildInfo>& gatherNodeInfo)
{
    CHECK_NULL_VOID(gatherNode);
    auto renderContext = gatherNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(0.0f), Dimension(0.0f)));
    }
    for (auto childInfo : gatherNodeInfo) {
        auto imageNode = childInfo.imageNode.Upgrade();
        DragDropFuncWrapper::UpdateNodePositionToScreen(imageNode, childInfo.offset);
    }
}

void DragAnimationHelper::ShowGatherNodeAnimation(const RefPtr<FrameNode>& frameNode)
{
    TAG_LOGI(AceLogTag::ACE_DRAG, "Show gather node animation");
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);

    if (manager->GetHasGatherNode()) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Not need create gather node, already have");
        return;
    }

    //create gather node
    std::vector<GatherNodeChildInfo> gatherNodeInfo;
    auto gatherNode = CreateGatherNode(frameNode, gatherNodeInfo);
    CHECK_NULL_VOID(gatherNode);
    MountGatherNode(manager, frameNode, gatherNode, gatherNodeInfo);
    InitGatherNodeAttr(gatherNode, gatherNodeInfo);
    AddDragNodeCopy(manager, frameNode, gatherNode);
    MarkDirtyNode(gatherNode);
    
    pipeline->FlushSyncGeometryNodeTasks();
    manager->SetIsGatherWithMenu(false);

    //do gather animation before lifting
    PlayGatherNodeOpacityAnimation(manager);
    PlayGatherNodeTranslateAnimation(frameNode, manager);
    ShowDragNodeCopyAnimation(manager, frameNode);
}

void DragAnimationHelper::AddDragNodeCopy(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& gatherNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(gatherNode);
    CHECK_NULL_VOID(overlayManager);
    //create frameNode copy
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pixelMap = renderContext->GetThumbnailPixelMap(true, false);
    CHECK_NULL_VOID(pixelMap);
    auto dragNodeCopy = CreateImageNode(pixelMap);
    CHECK_NULL_VOID(dragNodeCopy);

    //mount to gatherNode
    gatherNode->AddChild(dragNodeCopy);
    overlayManager->SetDragNodeCopy(dragNodeCopy);

    //update position
    int32_t width = pixelMap->GetWidth();
    int32_t height = pixelMap->GetHeight();
    auto offset = DragDropFuncWrapper::GetPaintRectCenter(frameNode) -
        OffsetF(width / HALF_DIVIDE, height / HALF_DIVIDE);
    auto copyNodeRenderContext = dragNodeCopy->GetRenderContext();
    CHECK_NULL_VOID(copyNodeRenderContext);
    copyNodeRenderContext->UpdatePosition(OffsetT<Dimension>(Dimension(offset.GetX()), Dimension(offset.GetY())));
    copyNodeRenderContext->UpdateTransformScale({ 1.0f, 1.0f });
}

void DragAnimationHelper::ShowDragNodeCopyAnimation(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(overlayManager);
    auto dragNodeCopy = overlayManager->GetDragNodeCopy();
    CHECK_NULL_VOID(dragNodeCopy);
    auto previewOptions = frameNode->GetDragPreviewOption();
    if (!previewOptions.defaultAnimationBeforeLifting) {
        return;
    }
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    }
    auto renderContext = dragNodeCopy->GetRenderContext();
    AnimationOption option;
    option.SetDuration(BEFORE_LIFTING_TIME);
    auto springCurve = AceType::MakeRefPtr<InterpolatingSpring>(DEFAULT_INTERPOLATING_SPRING_VELOCITY,
        DEFAULT_INTERPOLATING_SPRING_MASS, DEFAULT_INTERPOLATING_SPRING_STIFFNESS,
        DEFAULT_INTERPOLATING_SPRING_DAMPING);
    option.SetCurve(springCurve);
    AnimationUtils::Animate(
        option,
        [renderContext]() mutable {
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformScale({ DEFAULT_ANIMATION_SCALE, DEFAULT_ANIMATION_SCALE });
        },
        option.GetOnFinishEvent()
    );
}

void DragAnimationHelper::HideDragNodeCopyWithAnimation(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(overlayManager);
    auto dragNodeCopy = overlayManager->GetDragNodeCopy();
    auto defaultAnimation = frameNode->GetDragPreviewOption().defaultAnimationBeforeLifting;
    if (!dragNodeCopy) {
        auto layoutProperty = frameNode->GetLayoutProperty();
        if (layoutProperty && defaultAnimation) {
            layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        }
        return;
    }
    auto renderContext = dragNodeCopy->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(NODE_RESET_DURATION);
    option.SetCurve(Curves::SHARP);
    option.SetOnFinishEvent([renderContext, weak = AceType::WeakClaim(AceType::RawPtr(frameNode)),
        defaultAnimation]() {
        auto frameNode = weak.Upgrade();
        if (frameNode) {
            auto layoutProperty = frameNode->GetLayoutProperty();
            if (layoutProperty && defaultAnimation) {
                layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            }
        }
        if (renderContext) {
            renderContext->UpdateOpacity(0.0f);
        }
    });

    AnimationUtils::Animate(
        option,
        [renderContext]() mutable {
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformScale({ 1.0, 1.0f });
        },
        option.GetOnFinishEvent()
    );
}

void DragAnimationHelper::HideDragNodeCopy(const RefPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(overlayManager);
    auto dragNodeCopy = overlayManager->GetDragNodeCopy();
    CHECK_NULL_VOID(dragNodeCopy);
    auto renderContext = dragNodeCopy->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateOpacity(0.0f);
}

void DragAnimationHelper::UpdateBadgeTextNodePosition(const RefPtr<FrameNode>& frameNode,
    const RefPtr<FrameNode>& textNode, int32_t childSize, float previewScale, OffsetF previewOffset)
{
    if (childSize <= 1) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(textNode);
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    auto pixelMap = frameNode->GetDragPixelMap();
    CHECK_NULL_VOID(pixelMap);
    auto width = pixelMap->GetWidth();
    auto height = pixelMap->GetHeight();
    auto offset = previewOffset.NonOffset()
                      ? DragDropFuncWrapper::GetFrameNodeOffsetToWindow(textNode, frameNode, width, height)
                      : previewOffset;
    auto badgeLength = std::to_string(childSize).size();
    double textOffsetX = offset.GetX() + width * (previewScale + 1) / 2 - BADGE_RELATIVE_OFFSET.ConvertToPx() -
                         (BADGE_RELATIVE_OFFSET.ConvertToPx() * badgeLength);
    double textOffsetY = offset.GetY() - height * (previewScale - 1) / 2 - BADGE_RELATIVE_OFFSET.ConvertToPx();
    textRenderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    textRenderContext->UpdatePosition(OffsetT<Dimension>(Dimension(textOffsetX), Dimension(textOffsetY)));
}

RefPtr<FrameNode> DragAnimationHelper::CreateBadgeTextNode(int32_t childSize)
{
    if (childSize <= 1) {
        return nullptr;
    }
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_RETURN(textNode, nullptr);
    auto badgeLength = std::to_string(childSize).size();
    DragAnimationHelper::UpdateBadgeLayoutAndRenderContext(textNode, badgeLength, childSize);

    textNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
    textNode->MarkModifyDone();
    textNode->SetLayoutDirtyMarked(true);
    textNode->SetActive(true);
    return textNode;
}

void DragAnimationHelper::ShowPreviewBadgeAnimation(
    const RefPtr<GestureEventHub>& gestureHub, const RefPtr<OverlayManager>& manager)
{
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto dragPreviewOptions = frameNode->GetDragPreviewOption();
    auto badgeNumber = dragPreviewOptions.GetCustomerBadgeNumber();
    int32_t childSize = badgeNumber.has_value() ? badgeNumber.value()
                                                : static_cast<int32_t>(manager->GetGatherNodeChildrenInfo().size()) + 1;
    auto textNode = DragAnimationHelper::CreateBadgeTextNode(childSize);
    CHECK_NULL_VOID(textNode);
    auto column = manager->GetPixelMapNode();
    CHECK_NULL_VOID(column);
    column->AddChild(textNode);

    DragAnimationHelper::UpdateBadgeTextNodePosition(frameNode, textNode, childSize, PIXELMAP_DRAG_SCALE_MULTIPLE);
    DragAnimationHelper::ShowBadgeAnimation(textNode);
}

// update ImageNode default attr before floating
void DragAnimationHelper::SetImageNodeInitAttr(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& imageNode)
{
    CHECK_NULL_VOID(imageNode);
    CHECK_NULL_VOID(frameNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();

    // update default scale
    imageContext->UpdateTransformScale({ 1.0f, 1.0f });

    // update shadow
    auto shadow = Shadow::CreateShadow(ShadowStyle::None);
    if (dragPreviewOption.options.shadow.has_value()) {
        shadow = dragPreviewOption.options.shadow.value();
        shadow.SetColor(Color(0x00000000));
    }
    imageContext->UpdateBackShadow(shadow);

    // update radius
    auto borderRadius = DragDropFuncWrapper::GetDragFrameNodeBorderRadius(frameNode);
    imageContext->UpdateBorderRadius(borderRadius);

    // update opacity
    imageContext->UpdateOpacity(1.0f);
}

void DragAnimationHelper::SetImageNodeFinishAttr(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& imageNode)
{
    CHECK_NULL_VOID(imageNode);
    CHECK_NULL_VOID(frameNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    if (dragPreviewOption.options.shadow.has_value() && !dragPreviewOption.options.shadow->GetIsFilled()) {
        imageContext->UpdateBackShadow(dragPreviewOption.options.shadow.value());
    }
}

void DragAnimationHelper::PreLayout(const RefPtr<FrameNode>& imageNode)
{
    CHECK_NULL_VOID(imageNode);
    auto subwindowContext = imageNode->GetContext();
    if (subwindowContext) {
        subwindowContext->FlushSyncGeometryNodeTasks();
        subwindowContext->PreLayout(subwindowContext->GetTimeFromExternalTimer(), 0);
    }
}

void DragAnimationHelper::SetNodeVisible(const RefPtr<FrameNode>& frameNode, bool visible)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetVisible(visible);
}

void DragAnimationHelper::DragStartAnimation(const Offset& newOffset, const RefPtr<OverlayManager>& overlayManager,
    const OffsetF& gatherNodeCenter, Point point, int32_t containerId)
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    AnimationOption option;
    constexpr int32_t animateDuration = 300;
    option.SetCurve(DRAG_CONTROL_ANIMATION_CURVE);
    option.SetDuration(animateDuration);
    option.SetOnFinishEvent([weakManager = AceType::WeakClaim(AceType::RawPtr(dragDropManager)), containerId]() {
       auto dragDropManager = weakManager.Upgrade();
       dragDropManager->SetStartAnimation(true);
       if (dragDropManager && !dragDropManager->IsPullMoveReceivedForCurrentDrag()) {
           DragControllerFuncWrapper::TransDragWindowToDragFwk(containerId);
       }
    });
    auto imageNode = dragDropManager->GetDragPreviewInfo().imageNode;
    CHECK_NULL_VOID(imageNode);
    auto renderContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationUtils::Animate(
        option,
        [renderContext, info = dragDropManager->GetDragPreviewInfo(), newOffset, overlayManager,
            dragDropManager, gatherNodeCenter]() {
                CHECK_NULL_VOID(renderContext);
                renderContext->UpdateTransformScale({ info.scale, info.scale });
                renderContext->UpdateTransformTranslate({ newOffset.GetX(), newOffset.GetY(), 0.0f });
                GatherAnimationInfo gatherAnimationInfo = { info.scale, info.width, info.height,
                    gatherNodeCenter, renderContext->GetBorderRadius() };
                dragDropManager->UpdateGatherNodeAttr(overlayManager, gatherAnimationInfo);
                dragDropManager->UpdateTextNodePosition(info.textNode, newOffset);
        },
        option.GetOnFinishEvent());
}
} // namespace OHOS::Ace::NG
