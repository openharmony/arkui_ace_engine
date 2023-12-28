/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/container_modal/container_modal_view.h"

#include "base/geometry/ng/offset_t.h"
#include "base/image/pixel_map.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/gestures/gesture_group.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_utils.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "frameworks/bridge/common/utils/utils.h"


namespace OHOS::Ace::NG {
namespace {
constexpr char SPLIT_LEFT_KEY[] = "container_modal_split_left_button";
constexpr char MAXIMIZE_KEY[] = "container_modal_maximize_button";
constexpr char MINIMIZE_KEY[] = "container_modal_minimize_button";
constexpr char CLOSE_KEY[] = "container_modal_close_button";
constexpr float SPRINGMOTION_RESPONSE = 0.55f;
constexpr float CURRENT_RATIO = 0.86f;
constexpr float CURRENT_DURATION = 0.25f;
} // namespace
float ContainerModalView::imageMaxTranslate = 0.0f;
float ContainerModalView::baseScale = 1.0f;
/**
 * The structure of container_modal is designed as follows :
 * |--container_modal(stack)
 *   |--column
 *      |--container_modal_custom_title(row)
 *          |--custom_node(js)
 *      |--stack
 *          |--container_modal_content(stage)
 *              |--page
 *          |--dialog(when show)
 *   |--container_modal_custom_floating_title(row)
 *          |--custom_node(js)
 *   |--container_modal_control_buttons(row)
 *          |--[leftSplit, maxRecover, minimize, close](button)
 */

RefPtr<FrameNode> ContainerModalView::Create(RefPtr<FrameNode>& content)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[ContainerModal][self:%d]", nodeId);
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal", nodeId, MakeRefPtr<ContainerModalPattern>());
    containerModalNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto stack = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<StackPattern>());
    auto column = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(true));
    auto controlButtonsRow = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(false));

    column->AddChild(BuildTitle(containerModalNode));
    stack->AddChild(content);
    column->AddChild(stack);
    content->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    content->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(1.0, DimensionUnit::PERCENT)));
    containerModalNode->AddChild(column);
    containerModalNode->AddChild(BuildTitle(containerModalNode, true));
    containerModalNode->AddChild(AddControlButtons(controlButtonsRow));

    CHECK_NULL_RETURN(stack->GetLayoutProperty(), nullptr);
    stack->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    CHECK_NULL_RETURN(column->GetLayoutProperty(), nullptr);
    column->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    CHECK_NULL_RETURN(controlButtonsRow->GetLayoutProperty(), nullptr);
    controlButtonsRow->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_RETURN(containerPattern, nullptr);
    containerModalNode->MarkModifyDone();
    containerPattern->Init();

    return containerModalNode;
}

RefPtr<FrameNode> ContainerModalView::BuildTitle(RefPtr<FrameNode>& containerNode, bool isFloatingTitle)
{
    LOGI("ContainerModalView BuildTitle called");
    auto customTitleContainer = BuildTitleContainer(containerNode, isFloatingTitle);
    CHECK_NULL_RETURN(customTitleContainer, nullptr);
    return customTitleContainer;
}

RefPtr<FrameNode> ContainerModalView::BuildTitleContainer(RefPtr<FrameNode>& containerNode, bool isFloatingTitle)
{
    auto containerTitleRow = BuildTitleRow(isFloatingTitle);
    CHECK_NULL_RETURN(containerTitleRow, nullptr);

    auto isSucc = ExecuteCustomTitleAbc();
    if (!isSucc) {
        return nullptr;
    }

    // get custom node
    auto customTitleBarNode = NG::ViewStackProcessor::GetInstance()->GetCustomTitleNode();
    CHECK_NULL_RETURN(customTitleBarNode, nullptr);
    containerTitleRow->AddChild(customTitleBarNode);
    return containerTitleRow;
}

RefPtr<FrameNode> ContainerModalView::BuildTitleRow(bool isFloatingTitle)
{
    auto containerTitleRow = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(false));
    containerTitleRow->UpdateInspectorId("ContainerModalTitleRow");
    auto layoutProperty = containerTitleRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(CONTAINER_TITLE_HEIGHT)));
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    if (isFloatingTitle) {
        auto renderContext = containerTitleRow->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, nullptr);
        renderContext->UpdateBackgroundColor(CONTAINER_BACKGROUND_COLOR);
    }
    return containerTitleRow;
}

RefPtr<FrameNode> ContainerModalView::AddControlButtons(RefPtr<FrameNode>& controlButtonsRow)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto layoutProperty = controlButtonsRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(CONTAINER_TITLE_HEIGHT)));
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);

    // add leftSplit / maxRecover / minimize / close button
    controlButtonsRow->AddChild(BuildControlButton(InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT,
        [wk = WeakClaim(RawPtr(windowManager))](GestureEvent& info) {
            auto windowManager = wk.Upgrade();
            CHECK_NULL_VOID(windowManager);
            LOGI("left split button clicked");
            windowManager->FireWindowSplitCallBack();
        }));
    controlButtonsRow->AddChild(BuildControlButton(InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE,
        [wk = WeakClaim(RawPtr(windowManager))](GestureEvent& info) {
            auto windowManager = wk.Upgrade();
            CHECK_NULL_VOID(windowManager);
            auto mode = windowManager->GetWindowMode();
            if (mode == WindowMode::WINDOW_MODE_FULLSCREEN) {
                LOGI("recover button clicked");
                windowManager->WindowRecover();
            } else {
                LOGI("maximize button clicked");
                windowManager->WindowMaximize();
            }
        }));
    controlButtonsRow->AddChild(BuildControlButton(InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE,
        [wk = WeakClaim(RawPtr(windowManager))](GestureEvent& info) {
            auto windowManager = wk.Upgrade();
            CHECK_NULL_VOID(windowManager);
            LOGI("minimize button clicked");
            windowManager->WindowMinimize();
        }));
    controlButtonsRow->AddChild(BuildControlButton(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE,
        [wk = WeakClaim(RawPtr(windowManager))](GestureEvent& info) {
            auto windowManager = wk.Upgrade();
            CHECK_NULL_VOID(windowManager);
            LOGI("close button clicked");
            windowManager->WindowClose();
        },
        true));

    return controlButtonsRow;
}

RefPtr<FrameNode> ContainerModalView::BuildControlButton(
    InternalResource::ResourceId icon, GestureEventFunc&& clickCallback, bool isCloseButton, bool canDrag)
{
    static std::unordered_map<InternalResource::ResourceId, std::string> controlButtonKeyMap = {
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT, SPLIT_LEFT_KEY },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_SPLIT_LEFT, SPLIT_LEFT_KEY },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER, MAXIMIZE_KEY },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE, MAXIMIZE_KEY },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_RECOVER, MAXIMIZE_KEY },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MAXIMIZE, MAXIMIZE_KEY },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE, MINIMIZE_KEY },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MINIMIZE, MINIMIZE_KEY },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE, CLOSE_KEY },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_CLOSE, CLOSE_KEY },
    };
    // button image icon
    ImageSourceInfo imageSourceInfo;
    auto imageIcon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<ImagePattern>());
    auto imageEventHub = imageIcon->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(imageEventHub, nullptr);
    imageEventHub->RemoveDragEvent();
    imageIcon->SetDraggable(false);
    auto imageFocus = imageIcon->GetFocusHub();
    if (imageFocus) {
        imageFocus->SetFocusable(false);
    }
    imageSourceInfo.SetResourceId(icon);
    auto imageLayoutProperty = imageIcon->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(TITLE_ICON_SIZE), CalcLength(TITLE_ICON_SIZE)));
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    auto imageRenderProperty = imageIcon->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(imageRenderProperty, nullptr);
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::HIGH);
    imageIcon->MarkModifyDone();

    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<ButtonPattern>());
    auto buttonFocus = buttonNode->GetFocusHub();
    if (buttonFocus) {
        buttonFocus->SetFocusable(false);
    }
    std::string buttonKey = "";
    auto iter = controlButtonKeyMap.find(icon);
    if (iter != controlButtonKeyMap.end()) {
        buttonKey = iter->second;
    }
    buttonNode->UpdateInspectorId(buttonKey);

    AddButtonHover(buttonNode, imageIcon);
    AddButtonMouse(buttonNode, imageIcon);

    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(TITLE_BUTTON_BACKGROUND_COLOR);

    auto buttonPattern = DynamicCast<ButtonPattern>(buttonNode->GetPattern());
    CHECK_NULL_RETURN(buttonPattern, nullptr);
    buttonPattern->SetClickedColor(TITLE_BUTTON_CLICKED_COLOR);

    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    auto clickGesture = MakeRefPtr<TapGesture>();
    clickGesture->SetOnActionId(clickCallback);
    auto gestureGroup = MakeRefPtr<NG::GestureGroup>(GestureMode::Parallel);
    gestureGroup->AddGesture(clickGesture);
    if (!canDrag) {
        // if can not be drag, cover father panEvent
        PanDirection panDirection;
        auto panGesture = MakeRefPtr<PanGesture>(DEFAULT_PAN_FINGER, panDirection, 0.0);
        gestureGroup->AddGesture(panGesture);
    }
    buttonEventHub->AddGesture(gestureGroup);

    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateType(ButtonType::CIRCLE);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TITLE_BUTTON_SIZE), CalcLength(TITLE_BUTTON_SIZE)));

    MarginProperty margin;
    margin.right = CalcLength(isCloseButton ? TITLE_PADDING_END : TITLE_ELEMENT_MARGIN_HORIZONTAL);
    buttonLayoutProperty->UpdateMargin(margin);
    buttonNode->MarkModifyDone();

    buttonNode->AddChild(imageIcon);
    return buttonNode;
}

void ContainerModalView::AddButtonHover(RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode)
{
    auto inputHub = buttonNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto hoverTask = [buttonWk = WeakClaim(RawPtr(buttonNode)), imageWk = WeakClaim(RawPtr(imageNode))](bool isHover) {
        auto buttonNode = buttonWk.Upgrade();
        auto imageNode = imageWk.Upgrade();
        CHECK_NULL_VOID(buttonNode && imageNode);
        auto buttonPattern = DynamicCast<ButtonPattern>(buttonNode->GetPattern());
        CHECK_NULL_VOID(buttonPattern);
        buttonPattern->SetInHover(isHover);
        float halfSize = TITLE_ICON_SIZE.Value() / 2.0f;
        auto icurve = MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.2f, 1.0f);
        float maxDis = sqrt(pow(halfSize, 2.0) + pow(halfSize, 2.0));
        float curDis = sqrt(pow(buttonPattern->GetLocalLocation().GetX() - halfSize, 2.0) +
                            pow(buttonPattern->GetLocalLocation().GetY() - halfSize, 2.0));
        float currentScale = 1 + 0.1 * icurve->Move((maxDis - curDis) / (maxDis));
        baseScale = currentScale > baseScale ? currentScale : baseScale;
        float imageTranslate = 2 * icurve->Move((maxDis - curDis) / (maxDis));
        imageMaxTranslate = imageTranslate > imageMaxTranslate ? imageTranslate : imageMaxTranslate;
        float translateX = (buttonPattern->GetLocalLocation().GetX() - halfSize) / halfSize * imageMaxTranslate;
        float translateY = (buttonPattern->GetLocalLocation().GetY() - halfSize) / halfSize * imageMaxTranslate;
        auto buttonNodeRenderContext = buttonNode->GetRenderContext();
        auto imageIconRenderContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(buttonNodeRenderContext);
        CHECK_NULL_VOID(imageIconRenderContext);
        float imageScale = isHover ? baseScale : 1.0f;
        AnimationOption option = AnimationOption();
        auto motion = MakeRefPtr<ResponsiveSpringMotion>(SPRINGMOTION_RESPONSE, CURRENT_RATIO, CURRENT_DURATION);
        option.SetCurve(motion);
        TranslateOptions translate;
        translate.x = isHover ? translateX : 0.0f;
        translate.y = isHover ? translateY : 0.0f;
        if (isHover) {
            AnimationUtils::Animate(option, [buttonNodeRenderContext, imageIconRenderContext, imageScale, translate]() {
                buttonNodeRenderContext->UpdateTransformScale(VectorF(imageScale, imageScale));
                imageIconRenderContext->UpdateTransformScale(VectorF(1 / imageScale, 1 / imageScale));
                imageIconRenderContext->UpdateTransformTranslate(translate);
            });
        } else {
            baseScale = 1.0f;
            imageMaxTranslate = 0.0f;
            AnimationUtils::Animate(option, [buttonNodeRenderContext, imageIconRenderContext, imageScale, translate]() {
                buttonNodeRenderContext->UpdateTransformScale(VectorF(imageScale, imageScale));
                imageIconRenderContext->UpdateTransformScale(VectorF(imageScale, imageScale));
                imageIconRenderContext->UpdateTransformTranslate(translate);
            });
        }
    };
    auto hoverEvent = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent);
}

void ContainerModalView::AddButtonMouse(RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode)
{
    auto inputHub = buttonNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseTask = [buttonWk = WeakClaim(RawPtr(buttonNode)), imageWk = WeakClaim(RawPtr(imageNode))](
                         MouseInfo& info) {
        auto buttonNode = buttonWk.Upgrade();
        auto imageNode = imageWk.Upgrade();
        CHECK_NULL_VOID(buttonNode && imageNode);
        auto buttonPattern = DynamicCast<ButtonPattern>(buttonNode->GetPattern());
        CHECK_NULL_VOID(buttonPattern);
        if (info.GetAction() != MouseAction::MOVE || !buttonPattern->GetIsInHover()) {
            buttonPattern->SetLocalLocation(info.GetLocalLocation());
            return;
        }
        auto buttonNodeRenderContext = buttonNode->GetRenderContext();
        auto imageIconRenderContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageIconRenderContext);
        float halfSize = TITLE_ICON_SIZE.Value() / 2.0f;
        auto icurve = MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.2f, 1.0f);
        float maxDis = sqrt(pow(halfSize, 2.0) + pow(halfSize, 2.0));
        float curDis = sqrt(
            pow(info.GetLocalLocation().GetX() - halfSize, 2.0) + pow(info.GetLocalLocation().GetY() - halfSize, 2.0));
        float currentScale = 1 + 0.1 * icurve->Move((maxDis - curDis) / (maxDis));
        baseScale = currentScale > baseScale ? currentScale : baseScale;
        float imageScale = baseScale;
        float imageTranslate = 2 * icurve->Move((maxDis - curDis) / (maxDis));
        imageMaxTranslate = imageTranslate > imageMaxTranslate ? imageTranslate : imageMaxTranslate;
        float translateX = (info.GetLocalLocation().GetX() - halfSize) / halfSize * imageMaxTranslate;
        float translateY = (info.GetLocalLocation().GetY() - halfSize) / halfSize * imageMaxTranslate;
        float response = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_RESPONSE;
        float dampingRatio = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_DAMPING_RATIO;
        float blendDuration = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_BLEND_DURATION;
        auto motion = MakeRefPtr<ResponsiveSpringMotion>(response, dampingRatio, blendDuration);
        AnimationOption option = AnimationOption();
        option.SetCurve(motion);
        TranslateOptions translate;
        translate.x = translateX;
        translate.y = translateY;
        AnimationUtils::Animate(option, [buttonNodeRenderContext, imageIconRenderContext, imageScale, translate]() {
            buttonNodeRenderContext->UpdateTransformScale(VectorF(imageScale, imageScale));
            imageIconRenderContext->UpdateTransformScale(VectorF(imageScale, imageScale));
            imageIconRenderContext->UpdateTransformTranslate(translate);
        });
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent);
}

} // namespace OHOS::Ace::NG
