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

#include "bridge/cj_frontend/frontend/container_modal_cj_utils.h"

#include "base/geometry/ng/offset_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/advanced_pattern_theme.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_utils.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr char SPLIT_LEFT_KEY[] = "container_modal_split_left_button";
constexpr char MAXIMIZE_KEY[] = "container_modal_maximize_button";
constexpr char MINIMIZE_KEY[] = "container_modal_minimize_button";
constexpr char CLOSE_KEY[] = "container_modal_close_button";
constexpr float SPRINGMOTION_RESPONSE = 0.55f;
constexpr float CURRENT_RATIO = 0.86f;
constexpr float CURRENT_DURATION = 0.25f;
float g_baseScale = 1.0f;

RefPtr<FrameNode> BuildCjTextNode(const std::string label)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textProps = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textNode, nullptr);

    // Modifying the onFocuse event is currently not supported
    textNode->GetOrCreateFocusHub()->SetFocusable(true);

    // The magic number in the following style refer to the native arkts application titile_node style
    Dimension DEFAULT_TEXT_FONTSIZE = 16.0_fp;
    textProps->UpdateFontSize(DEFAULT_TEXT_FONTSIZE);
    textProps->UpdateFontWeight(Ace::FontWeight::W500);
    textProps->UpdateMaxLines(1);
    textProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textProps->UpdateTextAlign(TextAlign::START);
    textProps->UpdateContent(label);
    return textNode;
}

#ifdef PIXEL_MAP_SUPPORTED
RefPtr<FrameNode> BuildCjImageNode(std::shared_ptr<Media::PixelMap> pixelMap)
{
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    RefPtr<PixelMap> icon = PixelMap::CreatePixelMap(&pixelMap);
    CHECK_NULL_RETURN(icon, nullptr);
    ImageSourceInfo info(icon);
    imageLayoutProperty->UpdateImageSourceInfo(info);

    // The magic number in the following style refer to the native arkts application titile_node style
    Dimension size = 20.0_vp;
    Dimension marginSize = 12.0_vp;
    auto targetSize = CalcSize(NG::CalcLength(size), NG::CalcLength(size));
    MarginProperty imageMargin;
    imageMargin.left = CalcLength(marginSize);
    imageMargin.left = CalcLength(marginSize);
    imageLayoutProperty->UpdateMargin(imageMargin);
    imageLayoutProperty->UpdateUserDefinedIdealSize(targetSize);
    auto imageRenderProperty = imageNode->GetPaintProperty<ImageRenderProperty>();
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::MEDIUM);
    return imageNode;
}
#endif

void AddButtonOnEvent(
    RefPtr<InputEventHub>& inputHub, RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode, bool isCloseBtn)
{
    auto wkTask = [buttonWk = AceType::WeakClaim(AceType::RawPtr(buttonNode)),
                      imageWk = AceType::WeakClaim(AceType::RawPtr(imageNode)), isCloseBtn](MouseInfo& info) {
        auto buttonNode = buttonWk.Upgrade();
        CHECK_NULL_VOID(buttonNode);
        auto imageNode = imageWk.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto theme = PipelineContext::GetCurrentContext()->GetTheme<ContainerModalTheme>();
        if (info.GetAction() == MouseAction::PRESS || info.GetAction() == MouseAction::RELEASE) {
            auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
            CHECK_NULL_VOID(imageLayoutProperty);
            auto sourceInfo = imageLayoutProperty->GetImageSourceInfo();
            CHECK_NULL_VOID(sourceInfo);
            auto isHoverFillType = info.GetAction() == MouseAction::PRESS ? ControlBtnColorType::PRESS_FILL
                                                                          : ControlBtnColorType::NORMAL_FILL;
            sourceInfo->SetFillColor(theme->GetControlBtnColor(isCloseBtn, isHoverFillType));
            auto renderContext = buttonNode->GetRenderContext();
            auto isHoverType =
                info.GetAction() == MouseAction::PRESS ? ControlBtnColorType::PRESS : ControlBtnColorType::NORMAL;
            renderContext->UpdateBackgroundColor(theme->GetControlBtnColor(isCloseBtn, isHoverType));
            buttonNode->MarkModifyDone();
            imageNode->MarkModifyDone();
        }
    };
    auto onclickCallback = AceType::MakeRefPtr<InputEvent>(std::move(wkTask));
    inputHub->AddOnMouseEvent(onclickCallback);
}

void AddButtonHoverEvent(
    RefPtr<InputEventHub>& inputHub, RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode, bool isCloseBtn)
{
    auto task = [buttonWk = AceType::WeakClaim(AceType::RawPtr(buttonNode)),
                    imageWk = AceType::WeakClaim(AceType::RawPtr(imageNode)), isCloseBtn](bool isHover) {
        auto buttonNode = buttonWk.Upgrade();
        CHECK_NULL_VOID(buttonNode);
        auto imageNode = imageWk.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto pipeline = buttonNode->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        auto containerNode = AceType::DynamicCast<FrameNode>(pipeline->GetRootElement()->GetChildAtIndex(0));
        auto containerModalPattern = containerNode->GetPattern<ContainerModalPattern>();
        CHECK_NULL_VOID(containerModalPattern);
        bool isFocus = containerModalPattern->GetIsFocus() || containerModalPattern->GetIsHoveredMenu();

        auto theme = PipelineContext::GetCurrentContext()->GetTheme<ContainerModalTheme>();
        auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
        auto sourceInfo = imageLayoutProperty->GetImageSourceInfo();
        ControlBtnColorType isHoverFillType = ControlBtnColorType::HOVER_FILL;
        ControlBtnColorType isHoverType = ControlBtnColorType::HOVER;
        if (!isHover) {
            isHoverFillType = isFocus ? ControlBtnColorType::NORMAL_FILL : ControlBtnColorType::UNFOCUS_FILL;
            isHoverType = isFocus ? ControlBtnColorType::NORMAL : ControlBtnColorType::UNFOCUS;
        }
        sourceInfo->SetFillColor(theme->GetControlBtnColor(isCloseBtn, isHoverFillType));
        if (isCloseBtn) {
            auto renderContext = buttonNode->GetRenderContext();
            renderContext->UpdateBackgroundColor(theme->GetControlBtnColor(isCloseBtn, isHoverType));
        }
        imageLayoutProperty->UpdateImageSourceInfo(sourceInfo.value());
        buttonNode->MarkModifyDone();
        imageNode->MarkModifyDone();
    };
    auto hoverCallBack = AceType::MakeRefPtr<InputEvent>(std::move(task));
    inputHub->AddOnHoverEvent(hoverCallBack);
}

void AddButtonStyleMouseEvent(RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode, bool isCloseBtn)
{
    auto inputHub = buttonNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    AddButtonHoverEvent(inputHub, buttonNode, imageNode, isCloseBtn);
    AddButtonOnEvent(inputHub, buttonNode, imageNode, isCloseBtn);
}

void AddButtonMouse(RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode)
{
    auto inputHub = buttonNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseTask = [buttonWk = AceType::WeakClaim(AceType::RawPtr(buttonNode)),
                         imageWk = AceType::WeakClaim(AceType::RawPtr(imageNode))](MouseInfo& info) {
        auto buttonNode = buttonWk.Upgrade();
        auto imageNode = imageWk.Upgrade();
        CHECK_NULL_VOID(buttonNode && imageNode);
        auto buttonPattern = AceType::DynamicCast<ButtonPattern>(buttonNode->GetPattern());
        CHECK_NULL_VOID(buttonPattern);
        if (info.GetAction() != MouseAction::MOVE || !buttonPattern->GetIsInHover()) {
            buttonPattern->SetLocalLocation(info.GetLocalLocation());
            return;
        }
        auto buttonNodeRenderContext = buttonNode->GetRenderContext();
        auto imageIconRenderContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageIconRenderContext);
        float halfSize = TITLE_ICON_SIZE.Value() / 2.0f;
        auto icurve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.2f, 1.0f);
        float maxDis = sqrt(pow(halfSize, 2.0) + pow(halfSize, 2.0));
        float curDis = sqrt(
            pow(info.GetLocalLocation().GetX() - halfSize, 2.0) + pow(info.GetLocalLocation().GetY() - halfSize, 2.0));
        float currentScale = 1 + 0.1 * icurve->Move((maxDis - curDis) / (maxDis));
        g_baseScale = currentScale > g_baseScale ? currentScale : g_baseScale;
        float imageScale = g_baseScale;
        float btnScale = 1.0f;
        float response = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_RESPONSE;
        float dampingRatio = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_DAMPING_RATIO;
        float blendDuration = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_BLEND_DURATION;
        auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(response, dampingRatio, blendDuration);
        AnimationOption option = AnimationOption();
        option.SetCurve(motion);
        AnimationUtils::Animate(option, [buttonNodeRenderContext, imageIconRenderContext, imageScale, btnScale]() {
            buttonNodeRenderContext->UpdateTransformScale(VectorF(btnScale, btnScale));
            imageIconRenderContext->UpdateTransformScale(VectorF(imageScale, imageScale));
        });
    };
    auto mouseEvent = AceType::MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent);
}

void AddButtonHover(RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode)
{
    auto inputHub = buttonNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto hoverTask = [buttonWk = AceType::WeakClaim(AceType::RawPtr(buttonNode)),
                         imageWk = AceType::WeakClaim(AceType::RawPtr(imageNode))](bool isHover) {
        auto buttonNode = buttonWk.Upgrade();
        auto imageNode = imageWk.Upgrade();
        CHECK_NULL_VOID(buttonNode && imageNode);
        auto buttonPattern = AceType::DynamicCast<ButtonPattern>(buttonNode->GetPattern());
        CHECK_NULL_VOID(buttonPattern);
        buttonPattern->SetInHover(isHover);
        float halfSize = TITLE_ICON_SIZE.Value() / 2.0f;
        auto icurve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.2f, 1.0f);
        float maxDis = sqrt(pow(halfSize, 2.0) + pow(halfSize, 2.0));
        float curDis = sqrt(pow(buttonPattern->GetLocalLocation().GetX() - halfSize, 2.0) +
                            pow(buttonPattern->GetLocalLocation().GetY() - halfSize, 2.0));
        float currentScale = 1 + 0.1 * icurve->Move((maxDis - curDis) / (maxDis));
        g_baseScale = currentScale > g_baseScale ? currentScale : g_baseScale;
        auto buttonNodeRenderContext = buttonNode->GetRenderContext();
        auto imageIconRenderContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(buttonNodeRenderContext);
        CHECK_NULL_VOID(imageIconRenderContext);
        float imageScale = isHover ? g_baseScale : 1.0f;
        float btnScale = 1.0f;
        AnimationOption option = AnimationOption();
        auto motion =
            AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRINGMOTION_RESPONSE, CURRENT_RATIO, CURRENT_DURATION);
        option.SetCurve(motion);
        if (isHover) {
            AnimationUtils::Animate(option, [buttonNodeRenderContext, imageIconRenderContext, imageScale, btnScale]() {
                buttonNodeRenderContext->UpdateTransformScale(VectorF(btnScale, btnScale));
                imageIconRenderContext->UpdateTransformScale(VectorF(1 / imageScale, 1 / imageScale));
            });
        } else {
            g_baseScale = 1.0f;
            AnimationUtils::Animate(option, [buttonNodeRenderContext, imageIconRenderContext, imageScale, btnScale]() {
                buttonNodeRenderContext->UpdateTransformScale(VectorF(btnScale, btnScale));
                imageIconRenderContext->UpdateTransformScale(VectorF(imageScale, imageScale));
            });
        }
    };
    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent);
}
} // namespace

RefPtr<FrameNode> BuildControlButtonForCj(
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
    auto theme = PipelineContext::GetCurrentContext()->GetTheme<ContainerModalTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    // button image icon
    ImageSourceInfo imageSourceInfo;
    auto imageIcon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageEventHub = imageIcon->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(imageEventHub, nullptr);
    imageEventHub->RemoveDragEvent();
    imageIcon->SetDraggable(false);
    auto imageFocus = imageIcon->GetFocusHub();
    if (imageFocus) {
        imageFocus->SetFocusable(false);
    }
    imageSourceInfo.SetResourceId(icon);
    imageSourceInfo.SetFillColor(theme->GetControlBtnColor(isCloseButton, ControlBtnColorType::NORMAL_FILL));
    auto imageLayoutProperty = imageIcon->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(TITLE_ICON_SIZE), CalcLength(TITLE_ICON_SIZE)));
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    auto imageRenderProperty = imageIcon->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(imageRenderProperty, nullptr);
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::HIGH);
    imageIcon->MarkModifyDone();

    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
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
    AddButtonStyleMouseEvent(buttonNode, imageIcon, isCloseButton);

    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(theme->GetControlBtnColor(isCloseButton, ControlBtnColorType::NORMAL));

    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    auto clickGesture = AceType::MakeRefPtr<TapGesture>();
    clickGesture->SetOnActionId(clickCallback);
    buttonEventHub->AddGesture(clickGesture);
    buttonNode->SetDraggable(canDrag);

    DimensionOffset offsetDimen(TITLE_BUTTON_RESPONSE_REGIOIN_OFFSET_X, TITLE_BUTTON_RESPONSE_REGIOIN_OFFSET_Y);
    DimensionRect dimenRect(TITLE_BUTTON_RESPONSE_REGIOIN_WIDTH, TITLE_BUTTON_RESPONSE_REGIOIN_HEIGHT, offsetDimen);
    std::vector<DimensionRect> result;
    result.emplace_back(dimenRect);
    auto gestureHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    gestureHub->SetResponseRegion(result);

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

RefPtr<FrameNode> AddControlButtonsForCj(
    const WeakPtr<ContainerModalPatternEnhance>& weakPattern, const RefPtr<FrameNode>& containerTitleRow)
{
    RefPtr<FrameNode> maximizeBtn = BuildControlButtonForCj(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE, [weakPattern](GestureEvent& info) {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnMaxButtonClick(info);
        });
    maximizeBtn->UpdateInspectorId("EnhanceMaximizeBtn");

    // add long press event
    WeakPtr<FrameNode> weakMaximizeBtn = maximizeBtn;
    auto longPressCallback = [weakPattern, weakMaximizeBtn](GestureEvent& info) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto maximizeBtn = weakMaximizeBtn.Upgrade();
        CHECK_NULL_VOID(maximizeBtn);
        pattern->ShowMaxMenu(maximizeBtn);
    };
    // diable mouse left!
    auto hub = maximizeBtn->GetOrCreateGestureEventHub();
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    hub->SetLongPressEvent(longPressEvent, false, true);

    auto eventHub = maximizeBtn->GetOrCreateInputEventHub();
    auto hoverMoveFuc = [weakPattern](MouseInfo& info) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnMaxBtnInputEvent(info);
    };
    eventHub->AddOnMouseEvent(AceType::MakeRefPtr<InputEvent>(std::move(hoverMoveFuc)));

    // add hover in out event
    auto hoverEventFuc = [weakPattern, weakMaximizeBtn](bool hover) mutable {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnMaxBtnHoverEvent(hover, weakMaximizeBtn);
    };
    eventHub->AddOnHoverEvent(AceType::MakeRefPtr<InputEvent>(std::move(hoverEventFuc)));
    containerTitleRow->AddChild(maximizeBtn);

    RefPtr<FrameNode> minimizeBtn = BuildControlButtonForCj(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE, [weakPattern](GestureEvent& info) {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnMinButtonClick(info);
        });
    // minimizeBtn add empty panEvent to over fater container event
    minimizeBtn->UpdateInspectorId("EnhanceMinimizeBtn");
    containerTitleRow->AddChild(minimizeBtn);

    RefPtr<FrameNode> closeBtn = BuildControlButtonForCj(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE,
        [weakPattern](GestureEvent& info) {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnCloseButtonClick(info);
        },
        true);
    // closeBtn add empty panEvent to over fater container event
    closeBtn->UpdateInspectorId("EnhanceCloseBtn");
    containerTitleRow->AddChild(closeBtn);

    return containerTitleRow;
}

RefPtr<FrameNode> BuildTitleNodeForCj()
{
    auto titleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(titleRow, nullptr);
    auto rowLayoutProperty = titleRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(rowLayoutProperty, nullptr);

    // The magic number in the following style refer to the native arkts application titile_node style
    PaddingProperty padding = { CalcLength(6), CalcLength(6), CalcLength(8), CalcLength(8) };
    rowLayoutProperty->UpdatePadding(padding);
    // Set the width to 100%
    Dimension width(1.0, DimensionUnit::PERCENT);
    // Set the height to 37.0vp
    Dimension height = 37.0_vp;
    rowLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(width), NG::CalcLength(height)));
    rowLayoutProperty->UpdateAlignment(WrapAlignment::CENTER);
    rowLayoutProperty->UpdateAlignSelf(FlexAlign::FLEX_START);

    // read the configuration in the application and set the naiconme of window title node
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto themeContants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeContants, nullptr);

#ifdef PIXEL_MAP_SUPPORTED
    auto iconId = pipeline->GetWindowManager()->GetAppIconId();
    auto pixelMap = themeContants->GetPixelMap(iconId);
    if (pixelMap != nullptr) {
        titleRow->AddChild(BuildCjImageNode(pixelMap));
    }
#endif
    auto labelId = pipeline->GetWindowManager()->GetAppLabelId();
    auto label = themeContants->GetString(labelId);
    titleRow->AddChild(BuildCjTextNode(label));
    return titleRow;
}
} // namespace OHOS::Ace::NG
