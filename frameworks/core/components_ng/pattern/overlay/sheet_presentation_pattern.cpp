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

#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"

#include "base/geometry/dimension.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/animation/animation_pub.h"
#include "core/animation/curve.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/property/accessibility_property_helper.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#endif
#include "core/components_ng/property/property.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "core/components_ng/render/adapter/rosen_render_context.h"
#endif
#include "core/components/theme/shadow_theme.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SHEET_VISIABLE_ALPHA = 1.0f;
constexpr float SHEET_INVISIABLE_ALPHA = 0.0f;
constexpr int32_t SHEET_ENTRY_ANIMATION_DURATION = 250;
constexpr int32_t SHEET_EXIT_ANIMATION_DURATION = 100;
constexpr float SHEET_INVISIABLE_OFFSET = 8.0;
constexpr int32_t SHEET_HALF_HEIGHT = 2;
constexpr Dimension ARROW_VERTICAL_P1_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_VERTICAL_P2_OFFSET_X = 1.5_vp;
constexpr Dimension ARROW_VERTICAL_P2_OFFSET_Y = 7.32_vp;
constexpr Dimension ARROW_VERTICAL_P4_OFFSET_X = 1.5_vp;
constexpr Dimension ARROW_VERTICAL_P4_OFFSET_Y = 7.32_vp;
constexpr Dimension ARROW_VERTICAL_P5_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_CORNER_P2_OFFSET_X = 12.8_vp;
constexpr Dimension ARROW_CORNER_P2_OFFSET_Y = 7.6_vp;
constexpr Dimension ARROW_CORNER_P4_OFFSET_Y = 6.0_vp;
constexpr Dimension ARROW_RADIUS = 2.0_vp;
constexpr Dimension SUBWINDOW_SHEET_TRANSLATION = 80.0_vp;
} // namespace
void SheetPresentationPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    if (renderContext) {
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto sheetTheme = pipeline->GetTheme<SheetTheme>();
        CHECK_NULL_VOID(sheetTheme);
        auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto sheetStyle = layoutProperty->GetSheetStyleValue();
        BlurStyle blurStyle = static_cast<BlurStyle>(sheetTheme->GetSheetBackgroundBlurStyle());
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
            && blurStyle != BlurStyle::NO_MATERIAL) {
            BlurStyleOption options;
            options.blurStyle = blurStyle;
            renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
            renderContext->UpdateBackBlurStyle(sheetStyle.backgroundBlurStyle.value_or(options));
        } else {
            renderContext->UpdateBackgroundColor(
                sheetStyle.backgroundColor.value_or(sheetTheme->GetSheetBackgoundColor()));
        }
    }
    InitPanEvent();
    InitPageHeight();
    InitScrollProps();
    UpdateSheetType();
    InitFoldCreaseRegion();
}

// check device is phone, fold status, and device in landscape
bool SheetPresentationPattern::IsPhoneInLandScape()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto containerId = Container::CurrentId();
    auto foldWindow = FoldableWindow::CreateFoldableWindow(containerId);
    CHECK_NULL_RETURN(foldWindow, false);
    auto sheetTheme = pipelineContext->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, false);
    auto sheetThemeType = sheetTheme->GetSheetType();
    if (sheetThemeType == "auto" && !foldWindow->IsFoldExpand() &&
        SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        return true;
    }
    return false;
}

float SheetPresentationPattern::GetSheetTopSafeArea()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0f);
    auto safeAreaInsets = pipelineContext->GetSafeAreaWithoutProcess();
    auto sheetTopSafeArea = safeAreaInsets.top_.Length();
    auto windowManager = pipelineContext->GetWindowManager();
    auto sheetType = GetSheetType();
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    double deviceHeight = static_cast<double>(SystemProperties::GetDeviceHeight());

    // full screen subwindow sheet is also WINDOW_MODE_FLOATING, can not enter
    if (windowManager && windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING &&
        !NearEqual(windowGlobalRect.Height(), deviceHeight)) {
        sheetTopSafeArea = SHEET_BLANK_FLOATING_STATUS_BAR.ConvertToPx();
    } else if ((sheetType == SheetType::SHEET_BOTTOMLANDSPACE || sheetType == SheetType::SHEET_BOTTOM ||
                sheetType == SheetType::SHEET_BOTTOM_OFFSET) &&
               Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        sheetTopSafeArea = GetBottomSafeArea();
    } else if (sheetType == SheetType::SHEET_BOTTOMLANDSPACE &&
               AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        sheetTopSafeArea = 0.0f;
    }
    // before API14，ignore safeArea height when in landscape
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        auto layoutProperty = DynamicCast<SheetPresentationProperty>(host->GetLayoutProperty());
        CHECK_NULL_RETURN(layoutProperty, 0.0f);
        auto sheetStyle = layoutProperty->GetSheetStyleValue();
        if (sheetStyle.sheetType.has_value() && sheetStyle.sheetType.value() == SheetType::SHEET_BOTTOM &&
            IsPhoneInLandScape()) {
            sheetTopSafeArea = 0.0f;
        }
    }
    // if window titleBar hidden, avoid button area.
    NG::RectF floatButtons;
    if (GetWindowButtonRect(floatButtons)) {
        sheetTopSafeArea = floatButtons.Height();
    }
    return sheetTopSafeArea;
}

void SheetPresentationPattern::InitPageHeight()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto safeAreaInsets = pipelineContext->GetSafeAreaWithoutProcess();
    auto currentTopSafeArea = sheetTopSafeArea_;
    TAG_LOGD(AceLogTag::ACE_SHEET, "statusBarHeight of sheet by GetSafeAreaWithoutProcess : %{public}u",
        safeAreaInsets.top_.Length());
    sheetTopSafeArea_ =
        GetSheetType() != SheetType::SHEET_BOTTOMLANDSPACE ? safeAreaInsets.top_.Length() : .0f;
    auto showInPage =
        GetLayoutProperty<SheetPresentationProperty>()->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false);
    auto overlay = GetOverlayManager();
    if (overlay && overlay->IsRootExpansive() && showInPage) {
        sheetTopSafeArea_ = .0f;
    }
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetStyle.sheetType.has_value() && sheetStyle.sheetType.value() == SheetType::SHEET_BOTTOM &&
        IsPhoneInLandScape()) {
        sheetTopSafeArea_ = 0.0f;
    }
    sheetTopSafeArea_ = GetSheetTopSafeArea();
    TAG_LOGD(AceLogTag::ACE_SHEET, "sheetTopSafeArea of sheet is : %{public}f", sheetTopSafeArea_);
    if (!NearEqual(currentTopSafeArea, sheetTopSafeArea_)) {
        topSafeAreaChanged_ = true;
    }
    auto sheetTheme = pipelineContext->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    sheetThemeType_ = sheetTheme->GetSheetType();
    InitSheetMode();
}

void SheetPresentationPattern::InitScrollProps()
{
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);

    // When sheet content height is larger than sheet height,
    // the sheet height should set scroll always enabled.
    auto edgeEffectAlwaysEnabled = scrollSizeMode_ == ScrollSizeMode::CONTINUOUS && IsScrollable();
    if (sheetEffectEdge_ == SheetEffectEdge::NONE) {
        scrollPattern->SetEdgeEffect(EdgeEffect::NONE, edgeEffectAlwaysEnabled);
    } else {
        scrollPattern->SetEdgeEffect(EdgeEffect::SPRING,
            edgeEffectAlwaysEnabled, static_cast<EffectEdge>(sheetEffectEdge_));
    }
}

bool SheetPresentationPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto sheetLayoutAlgorithm =
        DynamicCast<SheetPresentationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(sheetLayoutAlgorithm, false);
    InitPageHeight();
    if (sheetLayoutAlgorithm->GetSheetMaxHeight() > 0) {
        pageHeight_ = sheetLayoutAlgorithm->GetSheetMaxHeight();
        sheetMaxHeight_ = sheetLayoutAlgorithm->GetSheetMaxHeight() - sheetTopSafeArea_;
        sheetMaxWidth_ = sheetLayoutAlgorithm->GetSheetMaxWidth();
        centerHeight_ = sheetLayoutAlgorithm->GetCenterHeight();
        if (!NearEqual(sheetOffsetX_, sheetLayoutAlgorithm->GetSheetOffsetX()) ||
            !NearEqual(sheetOffsetY_, sheetLayoutAlgorithm->GetSheetOffsetY())) {
            sheetOffsetX_ = sheetLayoutAlgorithm->GetSheetOffsetX();
            sheetOffsetY_ = sheetLayoutAlgorithm->GetSheetOffsetY();
            arrowOffset_ = OffsetF(sheetPopupInfo_.arrowOffsetX, .0f);
            windowChanged_ = true;
        }
    }
    GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    InitialLayoutProps();
    UpdateFontScaleStatus();
    UpdateDragBarStatus();
    UpdateCloseIconStatus();
    UpdateTitlePadding();
    UpdateSheetTitle();
    ClipSheetNode();
    CheckBuilderChange();
    if (GetSheetType() != SheetType::SHEET_POPUP) {
        if (windowRotate_) {
            // When rotating the screen,
            // first switch the sheet to the position corresponding to the proportion before rotation
            TranslateTo(pageHeight_ - height_);
            windowRotate_ = false;
        } else {
            // After rotation, if need to avoid the keyboard, trigger the avoidance behavior
            AvoidSafeArea();
        }
    }
    if (GetSheetType() == SheetType::SHEET_POPUP) {
        MarkSheetPageNeedRender();
    }
    return true;
}

void SheetPresentationPattern::CheckBuilderChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto builderNode = GetFirstFrameNodeOfBuilder();
    CHECK_NULL_VOID(builderNode);
    auto eventHub = builderNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    OnAreaChangedFunc onBuilderAreaChangedFunc = [sheetNodeWk = WeakPtr<FrameNode>(host)](const RectF& /* oldRect */,
                                                     const OffsetF& /* oldOrigin */, const RectF& /* rect */,
                                                     const OffsetF& /* origin */) {
        auto sheetNode = sheetNodeWk.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto sheetStyle = layoutProperty->GetSheetStyleValue();
        if (sheetStyle.sheetHeight.sheetMode == SheetMode::AUTO) {
            auto sheetWrapper = sheetNode->GetParent();
            CHECK_NULL_VOID(sheetWrapper);
            sheetWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    };
    eventHub->AddInnerOnAreaChangedCallback(builderNode->GetId(), std::move(onBuilderAreaChangedFunc));
}

void SheetPresentationPattern::AvoidAiBar()
{
    CHECK_NULL_VOID(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    if (!IsTypeNeedAvoidAiBar()) {
        TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet need not avoid AiBar.");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    if (NonPositive(scrollPattern->GetScrollableDistance()) || isScrolling_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto inset = pipeline->GetSafeArea();
    auto layoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollContentEndOffset(inset.bottom_.Length());
    TAG_LOGD(AceLogTag::ACE_SHEET, "AvoidAiBar function execution completed");
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

bool SheetPresentationPattern::IsScrollable() const
{
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_RETURN(scrollNode, false);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(scrollPattern, false);
    return Positive(scrollPattern->GetScrollableDistance());
}

void SheetPresentationPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    scale_ = pipelineContext->GetFontScale();
    InitFoldState();
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetId_);
    CHECK_NULL_VOID(targetNode);
    pipelineContext->AddOnAreaChangeNode(targetNode->GetId());
    OnAreaChangedFunc onAreaChangedFunc = [sheetNodeWk = WeakPtr<FrameNode>(host)](const RectF& /* oldRect */,
                                              const OffsetF& /* oldOrigin */, const RectF& /* rect */,
                                              const OffsetF& /* origin */) {
        auto sheetNode = sheetNodeWk.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        if (sheetPattern->GetSheetType() == SheetType::SHEET_POPUP) {
            auto sheetWrapper = sheetNode->GetParent();
            CHECK_NULL_VOID(sheetWrapper);
            sheetWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    };
    auto eventHub = targetNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->AddInnerOnAreaChangedCallback(host->GetId(), std::move(onAreaChangedFunc));

    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchTask = [](TouchEventInfo& info) {
        info.SetStopPropagation(true);
        TAG_LOGD(AceLogTag::ACE_SHEET, "The sheet hits the touch event.");
    };
    gesture->AddTouchEvent(MakeRefPtr<TouchEventImpl>(std::move(touchTask)));
    RegisterHoverModeChangeCallback();
    RegisterAvoidInfoChangeListener(host);
}

void SheetPresentationPattern::OnDetachFromFrameNode(FrameNode* sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto pipeline = sheetNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowSizeChangeCallback(sheetNode->GetId());
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetId_);
    CHECK_NULL_VOID(targetNode);
    auto eventHub = targetNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->RemoveInnerOnAreaChangedCallback(sheetNode->GetId());
    if (HasHoverModeChangedCallbackId()) {
        pipeline->UnRegisterHalfFoldHoverChangedCallback(hoverModeChangedCallbackId_.value_or(-1));
    }
    UnRegisterAvoidInfoChangeListener(sheetNode);
}

void SheetPresentationPattern::RegisterHoverModeChangeCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto hoverModeChangeCallback = [weak = WeakClaim(this)](bool isHalfFoldHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto sheetType = pattern->GetSheetType();
        if (sheetType != SheetType::SHEET_CENTER) {
            return;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        AnimationOption optionPosition;
        auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.35f, 1.0f, 0.0f);
        optionPosition.SetCurve(motion);
        context->FlushUITasks();
        context->Animate(
            optionPosition, motion,
            [host, context]() {
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                context->FlushUITasks();
            },
            [weak]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->FireHoverModeChangeCallback();
            });
    };
    auto hoverModeCallId = context->RegisterHalfFoldHoverChangedCallback(std::move(hoverModeChangeCallback));
    UpdateHoverModeChangedCallbackId(hoverModeCallId);
}

void SheetPresentationPattern::SetSheetBorderWidth(bool isPartialUpdate)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto sheetType = GetSheetType();
    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToBounds(true);
    if (sheetStyle.borderWidth.has_value()) {
        auto borderWidth = sheetStyle.borderWidth.value();
        bool bottomDimenInvalid = !(sheetType == SheetType::SHEET_CENTER || sheetType == SheetType::SHEET_POPUP ||
            sheetType == SheetType::SHEET_BOTTOM_OFFSET);
        if (bottomDimenInvalid) {
            borderWidth.bottomDimen = 0.0_vp;
        }
        layoutProperty->UpdateBorderWidth(borderWidth);
        renderContext->UpdateBorderWidth(borderWidth);
    } else if (renderContext->GetBorderWidth().has_value() && !isPartialUpdate) {
        BorderWidthProperty borderWidth;
        borderWidth.SetBorderWidth(0.0_vp);
        layoutProperty->UpdateBorderWidth(borderWidth);
        renderContext->UpdateBorderWidth(borderWidth);
    }

    SetSheetOuterBorderWidth(sheetTheme, sheetStyle);
}

// initial drag gesture event
void SheetPresentationPattern::InitPanEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnkeyEvent(focusHub);
    if (IsShowInSubWindowTwoInOne()) {
        return;
    }

    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (panEvent_) {
        return;
    }

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragStart();
        }
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragUpdate(info);
        }
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd(info.GetMainVelocity());
        }
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd({});
        }
    };
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
}

void SheetPresentationPattern::InitOnkeyEvent(const RefPtr<FocusHub>& focusHub)
{
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnFocusInternal([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusEvent();
        }
    });

    focusHub->SetOnBlurInternal([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleBlurEvent();
        }
    });
}

void SheetPresentationPattern::SetShadowStyle(bool isFocused)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetStyle.shadow.has_value()) {
        return;
    }
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto style = static_cast<ShadowStyle>(sheetTheme->GetSheetShadowConfig());
    if (!isFocused) {
        style = static_cast<ShadowStyle>(sheetTheme->GetSheetShadowConfigS());
    }
    auto shadow = GetShadowFromTheme(style);
    renderContext->UpdateBackShadow(shadow);
}

void SheetPresentationPattern::HandleFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sheetId = host->GetId();
    TAG_LOGI(AceLogTag::ACE_SHEET, "Sheet get focus, and id is : %{public}d", sheetId);
    SheetManager::GetInstance().SetFocusSheetId(sheetId);
    SetShadowStyle(true);
}

void SheetPresentationPattern::HandleBlurEvent()
{
    TAG_LOGI(AceLogTag::ACE_SHEET, "Sheet lost focus");
    SheetManager::GetInstance().SetFocusSheetId(std::nullopt);
    SetShadowStyle(false);
}

void SheetPresentationPattern::HandleDragStart()
{
    InitScrollProps();
    SetIsDragging(true);
    if (animation_ && isAnimationProcess_) {
        AnimationUtils::StopAnimation(animation_);
        isAnimationBreak_ = true;
    }
    currentOffset_ = 0.0f;
    isDirectionUp_ = true;
    GetCurrentBroadcastDetentsIndex();
}

void SheetPresentationPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto sheetType = GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        return;
    }
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tempOffset = currentOffset_;
    auto detentSize = sheetDetentHeight_.size();
    if (detentSize <= 0) {
        return;
    }
    auto height = GetSheetHeightBeforeDragUpdate();
    auto maxDetentSize = GetMaxSheetHeightBeforeDragUpdate();
    if (GreatOrEqual((height - currentOffset_), maxDetentSize)) {
        if (LessNotEqual(mainDelta, 0) && GreatNotEqual(sheetMaxHeight_, 0.0f)) {
            auto friction = CalculateFriction((height - currentOffset_) / sheetMaxHeight_, GetRadio());
            mainDelta = mainDelta * friction;
        }
    }
    currentOffset_ = currentOffset_ + mainDelta;
    if (NearEqual(currentOffset_, tempOffset)) {
        return;
    }
    auto pageHeight = GetPageHeightWithoutOffset();
    auto offset = pageHeight - height + currentOffset_;
    if (LessOrEqual(offset, (pageHeight - sheetMaxHeight_))) {
        offset = pageHeight - sheetMaxHeight_;
        currentOffset_ = height - sheetMaxHeight_;
    }
    bool isNeedChangeScrollHeight = scrollSizeMode_ == ScrollSizeMode::CONTINUOUS && currentOffset_ < 0;
    if (isNeedChangeScrollHeight) {
        ChangeScrollHeight(height - currentOffset_);
    }
    HandleFollowAccessibilityEvent(height - currentOffset_);
    auto renderContext = host->GetRenderContext();
    renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
    if (IsSheetBottomStyle()) {
        OnHeightDidChange(height_ - currentOffset_ + sheetHeightUp_);
    }
}

void SheetPresentationPattern::SendTextUpdateEvent()
{
    auto sheetNode = GetHost();
    CHECK_NULL_VOID(sheetNode);
    // Use TEXT_CHANGE to send events.
    TAG_LOGI(AceLogTag::ACE_SHEET, "bindsheet sent TEXT_CHANGE event, when follow up.");
    sheetNode->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, "", "");
}

void SheetPresentationPattern::SendSelectedEvent()
{
    auto sheetNode = GetHost();
    CHECK_NULL_VOID(sheetNode);
    // Use SELECTED to send events.
    TAG_LOGI(AceLogTag::ACE_SHEET, "bindsheet sent SELECTED event, when get out of your hands.");
    sheetNode->OnAccessibilityEvent(AccessibilityEventType::SELECTED, "", "");
}

void SheetPresentationPattern::RegisterElementInfoCallBack()
{
    auto sheetNode = GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto accessibilityProperty = sheetNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto callBack = [sheetDetents = std::to_string(static_cast<int32_t>(sheetDetents_))]
        (Accessibility::ExtraElementInfo& extraElementInfo) {
        extraElementInfo.SetExtraElementInfo("BindSheet", sheetDetents);
    };
    accessibilityProperty->SetRelatedElementInfoCallback(callBack);
}

bool SheetPresentationPattern::UpdateAccessibilityDetents(float height)
{
    auto sheetDetentsSize = sheetDetentHeight_.size();
    bool invalid = sheetDetentsSize < 2 || !IsSheetBottomStyle();
    if (invalid) {
        return false;
    }
    for (uint32_t i = 0; i < sheetDetentsSize; i++) {
        if (NearEqual(height, sheetDetentHeight_[i])) {
            // size is 2, corresponds to high and low.
            // size is 3, corresponds to high、medium and low.
            // The lower of the two detents, corresponds to "LOW".
            bool lowOfTwoDetents = sheetDetentsSize == 2 && i == 0;
            sheetDetents_ = lowOfTwoDetents
                ? static_cast<SheetAccessibilityDetents>(sheetDetentsSize - i)
                : static_cast<SheetAccessibilityDetents>(sheetDetentsSize -1 - i);
            TAG_LOGI(AceLogTag::ACE_SHEET, "bindsheet detents enum value: %{public}d", sheetDetents_);
            RegisterElementInfoCallBack();
            return true;
        }
    }
    return false;
}

uint32_t SheetPresentationPattern::GetCurrentBroadcastDetentsIndex()
{
    bool invalid = sheetDetentHeight_.size() < 2 || !IsSheetBottomStyle();
    if (invalid) {
        return broadcastPreDetentsIndex_;
    }
    // get currrent detents index.
    auto it = std::find(sheetDetentHeight_.begin(), sheetDetentHeight_.end(), height_);
    if (it != sheetDetentHeight_.end()) {
        broadcastPreDetentsIndex_ = static_cast<uint32_t>(std::distance(sheetDetentHeight_.begin(), it));
    }
    return broadcastPreDetentsIndex_;
}

void SheetPresentationPattern::HandleFollowAccessibilityEvent(float currHeight)
{
    auto sheetDetentsSize = sheetDetentHeight_.size();
    bool invalid = sheetDetentsSize < 2 || !IsSheetBottomStyle();
    if (invalid) {
        return;
    }
    if (currHeight < sheetDetentHeight_[0] || currHeight > sheetDetentHeight_[sheetDetentsSize - 1]) {
        return;
    }
    float upHeight = 0.0f;
    float downHeight = 0.0f;
    float finalHeight = 0.0f;

    // record current position info.
    uint32_t detentsLowerPos = 0;
    uint32_t detentsUpperPos = 0;
    uint32_t broadcastCurrDetentsIndex = 0;
    ComputeDetentsPos(currHeight, upHeight, downHeight, detentsLowerPos, detentsUpperPos);

    if (GreatNotEqual(std::abs(currHeight - upHeight), std::abs(currHeight - downHeight))) {
        finalHeight = downHeight;
        broadcastCurrDetentsIndex = detentsLowerPos;
    } else if (LessNotEqual(std::abs(currHeight - upHeight), std::abs(currHeight - downHeight))) {
        finalHeight = upHeight;
        broadcastCurrDetentsIndex = detentsUpperPos;
    }

    // Broadcast once when enter other effect area.
    if (broadcastCurrDetentsIndex != broadcastPreDetentsIndex_) {
        UpdateAccessibilityDetents(finalHeight);
        SendTextUpdateEvent();
        broadcastPreDetentsIndex_ = broadcastCurrDetentsIndex;
    }
}

void SheetPresentationPattern::HandleDragEndAccessibilityEvent()
{
    if (UpdateAccessibilityDetents(GetSheetHeightBeforeDragUpdate())) {
        SendSelectedEvent();
    }
}
void SheetPresentationPattern::HandleDragEnd(float dragVelocity)
{
    isNeedProcessHeight_ = true;
    SetIsDragging(false);
    auto sheetDetentsSize = sheetDetentHeight_.size();
    if ((sheetDetentsSize == 0) || (GetSheetType() == SheetType::SHEET_POPUP) || IsShowInSubWindowTwoInOne()) {
        return;
    }
    float upHeight = 0.0f;
    float downHeight = 0.0f;
    auto height = GetSheetHeightBeforeDragUpdate();
    auto currentSheetHeight =
        GreatNotEqual((height - currentOffset_), sheetMaxHeight_) ? sheetMaxHeight_ : (height - currentOffset_);
    start_ = currentSheetHeight;
    TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet HandleDragEnd, current height is: %{public}f", currentSheetHeight);

    // record the drag position
    uint32_t detentsLowerPos = 0;
    uint32_t detentsUpperPos = 0;
    ComputeDetentsPos(currentSheetHeight, upHeight, downHeight, detentsLowerPos, detentsUpperPos);

    // when drag velocity is under the threshold and the sheet height is not in the middle of lower and upper bound.
    if ((LessNotEqual(std::abs(dragVelocity), SHEET_VELOCITY_THRESHOLD)) &&
        (!NearEqual(std::abs(currentSheetHeight - upHeight), std::abs(currentSheetHeight - downHeight)))) {
        // check whether the lower or upper index is closer to the current height of the sheet page
        if (GreatNotEqual(std::abs(currentSheetHeight - upHeight), std::abs(currentSheetHeight - downHeight))) {
            if (NearZero(downHeight)) {
                SheetInteractiveDismiss(BindSheetDismissReason::SLIDE_DOWN, std::abs(dragVelocity));
            } else {
                detentsIndex_ = detentsLowerPos;
                ChangeSheetHeight(downHeight);
                ChangeSheetPage(height);
                SheetTransition(true, std::abs(dragVelocity));
            }
        } else if (LessNotEqual(std::abs(currentSheetHeight - upHeight), std::abs(currentSheetHeight - downHeight))) {
            detentsIndex_ = detentsUpperPos;
            ChangeSheetHeight(upHeight);
            ChangeSheetPage(height);
            SheetTransition(true, std::abs(dragVelocity));
        }
    } else {
        // when drag velocity is over the threshold
        if (GreatOrEqual(dragVelocity, 0.0f)) {
            if (NearZero(downHeight)) {
                SheetInteractiveDismiss(BindSheetDismissReason::SLIDE_DOWN, std::abs(dragVelocity));
            } else {
                detentsIndex_ = detentsLowerPos;
                ChangeSheetHeight(downHeight);
                ChangeSheetPage(height);
                SheetTransition(true, std::abs(dragVelocity));
            }
        } else {
            detentsIndex_ = detentsUpperPos;
            ChangeSheetHeight(upHeight);
            ChangeSheetPage(height);
            SheetTransition(true, std::abs(dragVelocity));
        }
    }

    // match the sorted detents index to the unsorted one
    auto detentHeight = sheetDetentHeight_[detentsIndex_];
    auto pos = std::find(unSortedSheetDentents_.begin(), unSortedSheetDentents_.end(), detentHeight);
    if (pos != std::end(unSortedSheetDentents_)) {
        auto idx = static_cast<uint32_t>(std::distance(unSortedSheetDentents_.begin(), pos));
        detentsFinalIndex_ = idx;
    }
}

void SheetPresentationPattern::ComputeDetentsPos(
    float currentSheetHeight, float& upHeight, float& downHeight, uint32_t& detentsLowerPos, uint32_t& detentsUpperPos)
{
    // when drag the sheet page, find the lower and upper index range
    auto lowerIter = std::lower_bound(sheetDetentHeight_.begin(), sheetDetentHeight_.end(), currentSheetHeight);
    auto upperIter = std::upper_bound(sheetDetentHeight_.begin(), sheetDetentHeight_.end(), currentSheetHeight);
    auto sheetDetentsSize = sheetDetentHeight_.size();
    if (lowerIter == sheetDetentHeight_.end() || upperIter == sheetDetentHeight_.end()) {
        // when drag over the highest sheet page
        upHeight = sheetDetentHeight_[sheetDetentsSize - 1];
        downHeight = sheetDetentHeight_[sheetDetentsSize - 1];
        detentsLowerPos = sheetDetentsSize - 1;
        detentsUpperPos = sheetDetentsSize - 1;
    } else {
        auto lowerPosition = static_cast<uint32_t>(std::distance(sheetDetentHeight_.begin(), lowerIter));
        auto upperPosition = static_cast<uint32_t>(std::distance(sheetDetentHeight_.begin(), upperIter));
        if (lowerPosition == 0) {
            upHeight = sheetDetentHeight_[lowerPosition];
            downHeight = 0;
        } else {
            // the first largest height greater than the currentsheet height
            upHeight = sheetDetentHeight_[upperPosition];

            // the largest height lower than the currentsheet height
            downHeight = sheetDetentHeight_[lowerPosition - 1];
            detentsLowerPos = lowerPosition - 1;
            detentsUpperPos = upperPosition;
        }
    }
}

void SheetPresentationPattern::ChangeSheetPage(float height)
{
    if (IsAvoidingKeyboard() && keyboardAvoidMode_ == SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL) {
        return;
    }
    ChangeScrollHeight(height);
}

void SheetPresentationPattern::OnCoordScrollStart()
{
    if (animation_ && isAnimationProcess_) {
        AnimationUtils::StopAnimation(animation_);
        isAnimationBreak_ = true;
    }
    currentOffset_ = 0.0f;
    GetCurrentBroadcastDetentsIndex();
}

bool SheetPresentationPattern::OnCoordScrollUpdate(float scrollOffset)
{
    if (!GetShowState() || !IsScrollable()) {
        return false;
    }

    auto sheetType = GetSheetType();
    auto sheetDetentsSize = sheetDetentHeight_.size();
    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) {
        return false;
    }
    auto height = GetSheetHeightBeforeDragUpdate();
    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
        (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate()))) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    currentOffset_ = currentOffset_ + scrollOffset;
    auto pageHeight = GetPageHeightWithoutOffset();
    auto offset = pageHeight - height + currentOffset_;
    if (LessOrEqual(offset, pageHeight - sheetMaxHeight_)) {
        offset = pageHeight - sheetMaxHeight_;
        currentOffset_ = height - sheetMaxHeight_;
    }
    HandleFollowAccessibilityEvent(height - currentOffset_);
    auto renderContext = host->GetRenderContext();
    renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
    return true;
}

void SheetPresentationPattern::OnCoordScrollEnd(float dragVelocity)
{
    HandleDragEnd(dragVelocity);
}

void SheetPresentationPattern::InitialLayoutProps()
{
    CheckSheetHeightChange();
    InitSheetDetents();
}

bool SheetPresentationPattern::GetWindowButtonRect(NG::RectF& floatButtons)
{
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto avoidInfoMgr = pipelineContext->GetAvoidInfoManager();
    CHECK_NULL_RETURN(avoidInfoMgr, false);
    NG::RectF floatContainerModal;
    if (avoidInfoMgr->NeedAvoidContainerModal() &&
        avoidInfoMgr->GetContainerModalButtonsRect(floatContainerModal, floatButtons)) {
        TAG_LOGD(AceLogTag::ACE_SHEET, "When hidden, floatButtons rect is %{public}s", floatButtons.ToString().c_str());
        return true;
    };
    TAG_LOGD(AceLogTag::ACE_SHEET, "Window title builder shown");
    return false;
}

float SheetPresentationPattern::InitialSingleGearHeight(NG::SheetStyle& sheetStyle)
{
    auto largeHeight = sheetMaxHeight_ - SHEET_BLANK_MINI_HEIGHT.ConvertToPx();
    float sheetHeight = largeHeight;
    auto sheetNode = GetHost();
    CHECK_NULL_RETURN(sheetNode, sheetHeight);
    if (sheetStyle.sheetHeight.sheetMode.has_value()) {
        auto pipelineContext = sheetNode->GetContext();
        CHECK_NULL_RETURN(pipelineContext, sheetHeight);
        auto sheetTheme = pipelineContext->GetTheme<SheetTheme>();
        CHECK_NULL_RETURN(sheetTheme, sheetHeight);
        if (sheetStyle.sheetHeight.sheetMode == SheetMode::MEDIUM) {
            sheetHeight = pageHeight_ * sheetTheme->GetMediumPercent();
            if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                sheetHeight = pageHeight_ * MEDIUM_SIZE_PRE;
            }
        } else if (sheetStyle.sheetHeight.sheetMode == SheetMode::LARGE) {
            sheetHeight = sheetTheme->GetHeightApplyFullScreen() ? pageHeight_ : largeHeight;
            sheetHeight *= sheetTheme->GetLargePercent();
        } else if (sheetStyle.sheetHeight.sheetMode == SheetMode::AUTO) {
            sheetHeight = GetFitContentHeight();
            if (sheetHeight > largeHeight) {
                sheetHeight = largeHeight;
            }
            HandleFitContontChange(sheetHeight);
        }
    } else {
        float height = 0.0f;
        if (sheetStyle.sheetHeight.height->Unit() == DimensionUnit::PERCENT) {
            height = sheetStyle.sheetHeight.height->ConvertToPxWithSize(sheetMaxHeight_);
        } else {
            height = sheetStyle.sheetHeight.height->ConvertToPx();
        }
        if (GreatNotEqual(height, largeHeight)) {
            sheetHeight = largeHeight;
        } else if (LessNotEqual(height, 0)) {
            sheetHeight = largeHeight;
        } else {
            sheetHeight = height;
        }
    }
    return sheetHeight;
}

void SheetPresentationPattern::AvoidSafeArea(bool forceAvoid)
{
    auto sheetType = GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP || IsCurSheetNeedHalfFoldHover() ||
        sheetType == SheetType::SHEET_BOTTOM_OFFSET) {
        return;
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_THIRTEEN)) {
        AvoidKeyboardBySheetMode(forceAvoid);
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetSafeAreaManager();
    if (!forceAvoid && keyboardHeight_ == manager->GetKeyboardInset().Length()) {
        return;
    }
    keyboardHeight_ = manager->GetKeyboardInset().Length();
    CHECK_NULL_VOID(host->GetFocusHub());
    auto heightUp = host->GetFocusHub()->IsCurrentFocus() ? GetSheetHeightChange() : 0.0f;
    sheetHeightUp_ = heightUp;
    if (isDismissProcess_) {
        TAG_LOGD(AceLogTag::ACE_SHEET,
            "The sheet will disappear, so there's no need to handle canceling keyboard avoidance here.");
        return;
    }
    TAG_LOGD(AceLogTag::ACE_SHEET, "To avoid Keyboard, sheet height increase %{public}f.", heightUp);
    auto offset = pageHeight_ - height_ - heightUp;
    auto renderContext = host->GetRenderContext();
    if (isScrolling_) {
        // if scrolling and keyboard will down, scroll needs to reset.
        if (NearZero(heightUp)) {
            ScrollTo(.0f);
            renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
        } else {
            sheetHeightUp_ = pageHeight_ - (SHEET_BLANK_MINI_HEIGHT.ConvertToPx() + sheetTopSafeArea_) - height_;
            // Otherwise, sheet is necessary to raise and trigger scroll scrolling
            // sheet is raised to the top first
            renderContext->UpdateTransformTranslate(
                { 0.0f, SHEET_BLANK_MINI_HEIGHT.ConvertToPx() + sheetTopSafeArea_, 0.0f });
            // Then adjust the remaining height(heightUp = h - maxH) difference by scrolling
            ScrollTo(heightUp);
        }
    } else {
        // offset: translate endpoint, calculated from top
        renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
    }
    if (IsSheetBottomStyle()) {
        OnHeightDidChange(height_ + sheetHeightUp_);
    }
}

float SheetPresentationPattern::GetSheetHeightChange()
{
    // TextFieldManagerNG::GetClickPosition: The upper left corner offset of the cursor position relative to rootNode
    // TextFieldManagerNG::GetHeight: the cursor Height + 24vp
    auto host = GetHost();
    CHECK_NULL_RETURN(host, .0f);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, .0f);
    auto manager = pipelineContext->GetSafeAreaManager();
    auto keyboardInsert = manager->GetKeyboardInset();
    if (keyboardInsert.Length() == 0) {
        return 0.f;
    }
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipelineContext->GetTextFieldManager());
    // inputH : Distance from input component's Caret to bottom of screen
    // = caret's offset + caret's height + 24vp
    if (textFieldManager && !textFieldManager->GetOptionalClickPosition().has_value() &&
        !pipelineContext->UsingCaretAvoidMode()) {
        TAG_LOGD(AceLogTag::ACE_SHEET, "illegal caret position, don't calc height this time");
        return .0f;
    }
    float inputH = 0.f;
    if (pipelineContext->UsingCaretAvoidMode()) {
        // when user scroll after avoiding keyboard, we need to update scroll offset before avoid keyboard twice.
        GetCurrentScrollHeight();
        // when avoiding keyboard twice, recover input height before avoiding is needed.
        inputH = textFieldManager ? pipelineContext->GetRootHeight() -
            textFieldManager->GetFocusedNodeCaretRect().Top() - textFieldManager->GetHeight() - sheetHeightUp_ -
            scrollHeight_ : 0.f;
    } else {
        inputH = textFieldManager ? (pipelineContext->GetRootHeight() -
            textFieldManager->GetFocusedNodeCaretRect().Top() - textFieldManager->GetHeight()) : 0.f;
    }
    // keyboardH : keyboard height + height of the bottom navigation bar
    auto keyboardH = keyboardInsert.Length() + manager->GetSystemSafeArea().bottom_.Length();
    // The minimum height of the input component from the bottom of the screen after popping up the soft keyboard
    auto inputMinH = keyboardH;
    // the LARGE sheet is 15vp from the status bar, and SHEET_CENTER's Node height not equal to screen height.
    auto largeHeight = pipelineContext->GetRootHeight() - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - sheetTopSafeArea_;
    // maxH : height that the sheet can reach the stage = the LARGE sheet - Current sheet height
    auto maxH = largeHeight - height_;
    if (inputH >= inputMinH) {
        // sheet needs not up
        TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet needs not up");
        return .0f;
    }
    // The expected height of the sheet to be lifted
    auto h = inputMinH - inputH;
    if (h <= maxH) {
        RecoverScrollOrResizeAvoidStatus();
        // sheet is lifted up with h
        TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet is lifted up with h = %{public}f", h);
        return h;
    }
    // h > maxH, sheet goes up to the LARGE, then adjust the remaining height(h - maxH) difference by scrolling
    if (IsResizeWhenAvoidKeyboard()) {
        // remaing height need to update to (keyboardH - bottomDistance) when in resize mode after translate
        inputH = sheetType_ == SheetType::SHEET_CENTER ? height_ - centerHeight_ : 0.0f;
        h = inputMinH - inputH;
    }
    TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet is LARGE, and there is [%{public}f] height left to be processed.", h - maxH);
    isScrolling_ = true;
    return h - maxH;
}

void SheetPresentationPattern::CreatePropertyCallback()
{
    if (property_) {
        return;
    }
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float position) {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        ref->OnHeightDidChange(static_cast<int>(position));
    };
    property_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
}

void SheetPresentationPattern::ModifyFireSheetTransition(float dragVelocity)
{
    TAG_LOGD(AceLogTag::ACE_SHEET, "ModifyFireSheetTransition function enter");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(
        dragVelocity / SHEET_VELOCITY_THRESHOLD, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto offset = UpdateSheetTransitionOffset();
    CreatePropertyCallback();
    CHECK_NULL_VOID(property_);
    renderContext->AttachNodeAnimatableProperty(property_);
    property_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);

    auto finishCallback = [weak = AceType::WeakClaim(this)]() {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        if (!ref->GetAnimationBreak()) {
            ref->SetAnimationProcess(false);
            ref->ChangeSheetPage(ref->height_);
        } else {
            ref->isAnimationBreak_ = false;
        }
        ref->AvoidAiBar();
        ref->isNeedProcessHeight_ = false;
        ref->FireOnDetentsDidChange(ref->height_);
        ref->preDidHeight_ = ref->height_;
        ref->isSpringBack_ = false;
    };

    isAnimationProcess_ = true;
    HandleDragEndAccessibilityEvent();
    property_->Set(start_);
    animation_ = AnimationUtils::StartAnimation(option,
        [weak = AceType::WeakClaim(this), renderContext, offset]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            if (renderContext) {
                renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
                ref->property_->Set(ref->height_ + ref->sheetHeightUp_);
                bool isNeedChangeScrollHeight =
                    ref->scrollSizeMode_ == ScrollSizeMode::CONTINUOUS && ref->isDirectionUp_;
                if (isNeedChangeScrollHeight) {
                    ref->ChangeScrollHeight(ref->height_);
                }
            }
        },
        finishCallback);
}

/**
 * @brief Get the max height before drag or nestedScroll.
 * the height is relative to the bottom of screen.
 */
float SheetPresentationPattern::GetMaxSheetHeightBeforeDragUpdate()
{
    if (IsCurSheetNeedHalfFoldHover() || sheetType_ == SheetType::SHEET_BOTTOM_OFFSET || IsShowInSubWindow()) {
        return GetPageHeightWithoutOffset() - sheetOffsetY_;
    }
    auto sheetDetentsSize = sheetDetentHeight_.size();
    if (sheetDetentsSize <= 0) {
        TAG_LOGW(AceLogTag::ACE_SHEET, "sheetDetentsSize is nonPositive");
        return 0.0f;
    }
    // The value can be returned in other scenarios as follows:
    // 1. bottom sheet tyle : maxHeight is maxDetent.
    // 2. center and other sheet tyle, except for popup tyle :
    // maxHeight is the height of the top left corner of sheet from the bottom of screen
    // 3. scene in setting offsetY : add offsetY to the following value
    return sheetDetentHeight_[sheetDetentsSize - 1];
}

/**
 * @brief Get the height before drag or nestedScroll.
 * the height is relative to the bottom of screen.
 */
float SheetPresentationPattern::GetSheetHeightBeforeDragUpdate()
{
    if (IsCurSheetNeedHalfFoldHover() || sheetType_ == SheetType::SHEET_BOTTOM_OFFSET || IsShowInSubWindow()) {
        return GetPageHeightWithoutOffset() - sheetOffsetY_;
    }
    // height_ : from the bottom of screen, after the sheet entry action has ended.
    // sheetHeightUp_ : increased height to avoid soft keyboard.
    // -bottomOffsetY_ : increased height by setting offsetY. bottomOffsetY_ is a negative number.
    return height_ + sheetHeightUp_;
}

float SheetPresentationPattern::UpdateSheetTransitionOffset()
{
    // dentets greater than 1 and no rebound
    if (!WillSpringBack() && sheetDetentHeight_.size() > 1) {
        // When avoiding keyboards
        // don't consider the height difference introduced by avoidance after switching detents
        sheetHeightUp_ = 0.0f;
    }
    // apply to springBack scene
    // return the offset before drag
    auto offset = GetPageHeightWithoutOffset() - GetSheetHeightBeforeDragUpdate();
    return offset;
}

void SheetPresentationPattern::SetSheetAnimationOption(AnimationOption& option) const
{
    option.SetFillMode(FillMode::FORWARDS);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        option.SetDuration(SHEET_ANIMATION_DURATION);
    }
}

void SheetPresentationPattern::SheetTransition(bool isTransitionIn, float dragVelocity)
{
    bool isNeedChangeScrollHeight = scrollSizeMode_ == ScrollSizeMode::CONTINUOUS && isDirectionUp_;
    if ((HasOnHeightDidChange() && IsSheetBottomStyle() && isTransitionIn && isNeedProcessHeight_)
        || isNeedChangeScrollHeight) {
        ModifyFireSheetTransition(dragVelocity);
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(
        dragVelocity / SHEET_VELOCITY_THRESHOLD, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    SetSheetAnimationOption(option);
    auto offset = UpdateSheetTransitionOffset();
    if (!isTransitionIn) {
        const auto& overlayManager = GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto maskNode = overlayManager->GetSheetMask(host);
        if (maskNode) {
            overlayManager->PlaySheetMaskTransition(maskNode, host, false);
        }
    }
    option.SetOnFinishEvent([weak = AceType::WeakClaim(this), isTransitionIn]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (isTransitionIn) {
            if (!pattern->GetAnimationBreak()) {
                pattern->SetAnimationProcess(false);
                pattern->ChangeSheetPage(pattern->height_);
            } else {
                pattern->isAnimationBreak_ = false;
            }
            pattern->AvoidAiBar();
            pattern->FireOnDetentsDidChange(pattern->height_);
            pattern->isSpringBack_ = false;
        } else {
            pattern->SetAnimationProcess(false);
            const auto& overlayManager = pattern->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            overlayManager->FireAutoSave(host);
            pattern->OnDisappear();
            overlayManager->RemoveSheet(host);
            pattern->FireCallback("false");
        }
    });
    StartSheetTransitionAnimation(option, isTransitionIn, offset);
}

void SheetPresentationPattern::SheetInteractiveDismiss(BindSheetDismissReason dismissReason, float dragVelocity)
{
    isDirectionUp_ = false;
    if (HasShouldDismiss() || HasOnWillDismiss()) {
        const auto& overlayManager = GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->SetDismissTarget(DismissTarget(sheetKey_));
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        SheetManager::GetInstance().SetDismissSheet(host->GetId());
        if (dismissReason == BindSheetDismissReason::SLIDE_DOWN) {
            isSpringBack_ = true;
            if (HasSheetSpringBack()) {
                CallSheetSpringBack();
            } else {
                isDismissProcess_ = false;
                SheetTransition(true);
            }
        }
        CallShouldDismiss();
        CallOnWillDismiss(static_cast<int32_t>(dismissReason));
    } else {
        DismissTransition(false, dragVelocity);
    }
}

void SheetPresentationPattern::DismissTransition(bool isTransitionIn, float dragVelocity)
{
    isDismissProcess_ = true;
    const auto& overlayManager = GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->ModalPageLostFocus(GetHost());
    if (!isTransitionIn) {
        OnWillDisappear();
    }
    auto sheetType = GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        BubbleStyleSheetTransition(isTransitionIn);
    } else {
        SheetTransition(isTransitionIn, dragVelocity);
    }
}

void SheetPresentationPattern::ChangeScrollHeight(float height)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto operationNode = GetTitleBuilderNode();
    CHECK_NULL_VOID(operationNode);
    auto perationGeometryNode = operationNode->GetGeometryNode();
    CHECK_NULL_VOID(perationGeometryNode);
    auto operationHeight = perationGeometryNode->GetFrameSize().Height();
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollProps = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(scrollProps);
    auto scrollHeight = height - operationHeight - resizeDecreasedHeight_;
    auto sheetType = GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP || sheetType == SheetType::SHEET_CENTER ||
        sheetType == SheetType::SHEET_BOTTOM_OFFSET) {
        auto sheetHeight = geometryNode->GetFrameSize().Height();
        scrollHeight = sheetHeight - operationHeight - resizeDecreasedHeight_;
    }
    scrollProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(scrollHeight)));
    scrollNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SheetPresentationPattern::UpdateDragBarStatus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    auto showDragIndicator = sheetStyle.showDragBar.value_or(true);

    auto titleColumn = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(titleColumn);
    auto sheetDragBar = DynamicCast<FrameNode>(titleColumn->GetFirstChild());
    CHECK_NULL_VOID(sheetDragBar);
    auto dragBarLayoutProperty = sheetDragBar->GetLayoutProperty();
    CHECK_NULL_VOID(dragBarLayoutProperty);
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        dragBarLayoutProperty->UpdateVisibility(showDragIndicator ? VisibleType::VISIBLE : VisibleType::GONE);
        sheetDragBar->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        return;
    }
    if (IsSheetBottomStyle() && (sheetDetentHeight_.size() > 1)) {
        if (sheetStyle.isTitleBuilder.has_value()) {
            dragBarLayoutProperty->UpdateVisibility(showDragIndicator ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
        } else {
            dragBarLayoutProperty->UpdateVisibility(showDragIndicator ? VisibleType::VISIBLE : VisibleType::GONE);
        }
    } else {
        if (sheetStyle.isTitleBuilder.has_value()) {
            dragBarLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        } else {
            dragBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
        }
    }
    sheetDragBar->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

float SheetPresentationPattern::GetCloseIconPosX(const SizeF& sheetSize, const RefPtr<SheetTheme>& sheetTheme)
{
    auto closeIconX = sheetSize.Width() - static_cast<float>(SHEET_CLOSE_ICON_WIDTH.ConvertToPx()) -
                      static_cast<float>(sheetTheme->GetTitleTextMargin().ConvertToPx());
    if (AceApplicationInfo::GetInstance().IsRightToLeft() &&
        AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        closeIconX = static_cast<float>(sheetTheme->GetTitleTextMargin().ConvertToPx());
    }
    return closeIconX;
}

bool SheetPresentationPattern::IsShowCloseIcon()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(host->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetSheetStyleValue().showCloseIcon.value_or(true);
}

RefPtr<FrameNode> SheetPresentationPattern::GetTitleNode()
{
    auto operationNode = GetTitleBuilderNode();
    CHECK_NULL_RETURN(operationNode, nullptr);
    return DynamicCast<FrameNode>(operationNode->GetChildAtIndex(1));
}

void SheetPresentationPattern::UpdateTitleTextColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto firstChild = host->GetChildAtIndex(0);
    CHECK_NULL_VOID(firstChild);
    auto sheetTitleColumn = firstChild->GetChildAtIndex(1);
    CHECK_NULL_VOID(sheetTitleColumn);
    auto mainRow = sheetTitleColumn->GetChildAtIndex(0);
    CHECK_NULL_VOID(mainRow);
    auto mainTitleText = DynamicCast<FrameNode>(mainRow->GetChildAtIndex(0));
    CHECK_NULL_VOID(mainTitleText);
    auto mainTitleProp = mainTitleText->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(mainTitleProp);
    mainTitleProp->UpdateTextColor(sheetTheme->GetTitleTextFontColor());

    auto layoutProperty = DynamicCast<SheetPresentationProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetStyle.sheetSubtitle.has_value()) {
        auto subRow = sheetTitleColumn->GetChildAtIndex(1);
        CHECK_NULL_VOID(subRow);
        auto subTitleText = DynamicCast<FrameNode>(subRow->GetChildAtIndex(0));
        CHECK_NULL_VOID(subTitleText);
        auto subTitleProp = subTitleText->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(subTitleProp);
        subTitleProp->UpdateTextColor(sheetTheme->GetSubtitleTextFontColor());
    }
}

void SheetPresentationPattern::UpdateTitlePadding()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->GetSheetStyleValue().isTitleBuilder.has_value()) {
        return;
    }

    auto titleNode = GetTitleNode();
    CHECK_NULL_VOID(titleNode);
    auto titleLayoutProperty = DynamicCast<LinearLayoutProperty>(titleNode->GetLayoutProperty());
    CHECK_NULL_VOID(titleLayoutProperty);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto showCloseIcon = true;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN)) {
        showCloseIcon = IsShowCloseIcon();
    }
    PaddingProperty padding;

    // The title bar area is reserved for the close button area size by default.
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        auto sheetCloseIconTitleSpace = sheetTheme->IsOuterBorderEnable() ? 0.0_vp : SHEET_CLOSE_ICON_TITLE_SPACE_NEW;
        padding.end = CalcLength(showCloseIcon ? sheetCloseIconTitleSpace + SHEET_CLOSE_ICON_WIDTH : 0.0_vp);
    } else {
        padding.right = CalcLength(SHEET_CLOSE_ICON_TITLE_SPACE + SHEET_CLOSE_ICON_WIDTH);
    }
    titleLayoutProperty->UpdatePadding(padding);
    auto titleColumnPattern = titleNode->GetPattern<LinearLayoutPattern>();
    CHECK_NULL_VOID(titleColumnPattern);
    titleColumnPattern->CheckLocalized();
    titleNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SheetPresentationPattern::UpdateCloseIconStatus()
{
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        TAG_LOGI(AceLogTag::ACE_SHEET, "PlatformVersion less or equal to version 10");
        return;
    }
    auto showCloseIcon = IsShowCloseIcon();
    auto sheetCloseIcon = GetSheetCloseIcon();
    CHECK_NULL_VOID(sheetCloseIcon);
    auto iconLayoutProperty = sheetCloseIcon->GetLayoutProperty();
    CHECK_NULL_VOID(iconLayoutProperty);
    iconLayoutProperty->UpdateVisibility(showCloseIcon ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
    sheetCloseIcon->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SheetPresentationPattern::UpdateSheetTitle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetStyle.sheetTitle.has_value()) {
        auto titleId = GetTitleId();
        auto titleNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetNodeById(titleId));
        CHECK_NULL_VOID(titleNode);
        auto titleProp = titleNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(titleProp);
        titleProp->UpdateContent(sheetStyle.sheetTitle.value());
        if (pipeline->GetFontScale() != scale_) {
            titleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        titleNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        if (sheetStyle.sheetSubtitle.has_value()) {
            auto subtitleId = GetSubtitleId();
            auto subtitleNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetNodeById(subtitleId));
            CHECK_NULL_VOID(subtitleNode);
            auto subtitleProp = subtitleNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(subtitleProp);
            subtitleProp->UpdateContent(sheetStyle.sheetSubtitle.value());
            subtitleNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }
}

void SheetPresentationPattern::UpdateFontScaleStatus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (pipeline->GetFontScale() != scale_) {
        auto operationNode = GetTitleBuilderNode();
        CHECK_NULL_VOID(operationNode);
        auto titleColumnNode = DynamicCast<FrameNode>(operationNode->GetChildAtIndex(1));
        CHECK_NULL_VOID(titleColumnNode);
        auto layoutProps = operationNode->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(layoutProps);
        auto titleLayoutProps = titleColumnNode->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(titleLayoutProps);
        auto sheetTheme = pipeline->GetTheme<SheetTheme>();
        CHECK_NULL_VOID(sheetTheme);
        bool isSheetHasNoTitle = !sheetStyle.isTitleBuilder.has_value();
        bool isFontScaledInSystemTitle = sheetStyle.isTitleBuilder.has_value() && !sheetStyle.isTitleBuilder.value() &&
                                         GreatNotEqual(pipeline->GetFontScale(), sheetTheme->GetSheetNormalScale());
        if (isSheetHasNoTitle || isFontScaledInSystemTitle) {
            layoutProps->ClearUserDefinedIdealSize(false, true);
            titleLayoutProps->ClearUserDefinedIdealSize(false, true);
        } else if (sheetStyle.isTitleBuilder.has_value()) {
            auto sheetTheme = pipeline->GetTheme<SheetTheme>();
            CHECK_NULL_VOID(sheetTheme);
            auto operationAreaHeight = sheetTheme->GetOperationAreaHeight();
            layoutProps->UpdateUserDefinedIdealSize(
                CalcSize(std::nullopt, CalcLength(operationAreaHeight - sheetTheme->GetSheetTitleAreaMargin())));
            titleLayoutProps->UpdateUserDefinedIdealSize(
                CalcSize(std::nullopt, CalcLength(operationAreaHeight)));
            if (sheetStyle.sheetSubtitle.has_value()) {
                layoutProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt,
                    CalcLength(SHEET_OPERATION_AREA_HEIGHT_DOUBLE - sheetTheme->GetSheetTitleAreaMargin())));
                titleLayoutProps->UpdateUserDefinedIdealSize(
                    CalcSize(std::nullopt,
                        CalcLength(SHEET_OPERATION_AREA_HEIGHT_DOUBLE - SHEET_DOUBLE_TITLE_BOTTON_MARGIN)));
            }
        }
        UpdateSheetTitle();
        scale_ = pipeline->GetFontScale();
        auto sheetWrapper = host->GetParent();
        CHECK_NULL_VOID(sheetWrapper);
        sheetWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void SheetPresentationPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);

    UpdateTitleTextColor();
    auto sheetCloseIcon = DynamicCast<FrameNode>(host->GetChildAtIndex(2));
    CHECK_NULL_VOID(sheetCloseIcon);
    auto renderContext = sheetCloseIcon->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(sheetTheme->GetCloseIconColor());
    sheetCloseIcon->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto iconNode = DynamicCast<FrameNode>(sheetCloseIcon->GetChildAtIndex(0));
    CHECK_NULL_VOID(iconNode);

    // when api >= 12, use symbol format image, else use image format.
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        SystemProperties::IsNeedSymbol()) {
        auto symbolLayoutProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolLayoutProperty);
        symbolLayoutProperty->UpdateSymbolColorList({sheetTheme->GetCloseIconSymbolColor()});
    } else {
        auto imagePaintProperty = iconNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(imagePaintProperty);
        imagePaintProperty->UpdateSvgFillColor(sheetTheme->GetCloseIconImageColor());
    }
    iconNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

float SheetPresentationPattern::GetWrapperHeight()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto sheetWrapper = host->GetParent();
    CHECK_NULL_RETURN(sheetWrapper, 0.0f);
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetWrapper->GetParent());
    CHECK_NULL_RETURN(sheetWrapperNode, 0.0f);
    auto sheetWrapperGeometryNode = sheetWrapperNode->GetGeometryNode();
    CHECK_NULL_RETURN(sheetWrapperGeometryNode, 0.0f);
    return sheetWrapperGeometryNode->GetFrameSize().Height();
}

bool SheetPresentationPattern::SheetHeightNeedChanged()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto sheetGeometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(sheetGeometryNode, false);
    if (!NearEqual(sheetGeometryNode->GetFrameSize().Height(), sheetHeight_) ||
        !NearEqual(GetWrapperHeight(), wrapperHeight_)) {
        return true;
    }
    return false;
}

void SheetPresentationPattern::UpdateMaskBackgroundColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    sheetMaskColor_ = sheetStyle.maskColor.value_or(sheetTheme->GetMaskColor());
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (sheetStyle.maskColor.has_value()) {
            sheetMaskColor_ = sheetStyle.maskColor.value();
        } else {
            sheetMaskColor_ = Color::TRANSPARENT;
        }
    } else {
        if ((!sheetStyle.interactive.has_value() && GetSheetType() == SheetType::SHEET_POPUP) ||
            sheetStyle.interactive.value_or(false)) {
            sheetMaskColor_ = Color::TRANSPARENT;
        }
    }
}

void SheetPresentationPattern::UpdateMaskBackgroundColorRender()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateMaskBackgroundColor();
    const auto& overlayManager = GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto maskNode = overlayManager->GetSheetMask(host);
    CHECK_NULL_VOID(maskNode);
    auto maskRenderContext = maskNode->GetRenderContext();
    CHECK_NULL_VOID(maskRenderContext);
    maskRenderContext->UpdateBackgroundColor(sheetMaskColor_);
}

void SheetPresentationPattern::FireCommonCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    FireOnTypeDidChange();
    FireOnWidthDidChange(host);
    FireOnHeightDidChange();
}

void SheetPresentationPattern::CheckSheetHeightChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sheetGeometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(sheetGeometryNode);
    if (isFirstInit_) {
        sheetHeight_ = sheetGeometryNode->GetFrameSize().Height();
        wrapperHeight_ = GetWrapperHeight();
        isFirstInit_ = false;
    } else {
        if (sheetType_ != GetSheetType()) {
            if (sheetType_ == SheetType::SHEET_POPUP) {
                MarkSheetPageNeedRender();
            }
            SetSheetBorderWidth();
        }
        if (SheetHeightNeedChanged() || (sheetType_ != GetSheetType()) || windowChanged_ || topSafeAreaChanged_) {
            sheetHeight_ = sheetGeometryNode->GetFrameSize().Height();
            wrapperHeight_ = GetWrapperHeight();
            const auto& overlayManager = GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
            CHECK_NULL_VOID(layoutProperty);
            auto sheetStyle = layoutProperty->GetSheetStyleValue();
            overlayManager->ComputeSheetOffset(sheetStyle, host);
            if (sheetType_ == SheetType::SHEET_POPUP) {
                auto renderContext = GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                renderContext->UpdateTransformTranslate({ 0.0f, Dimension(sheetOffsetY_), 0.0f });
                renderContext->UpdateOpacity(SHEET_VISIABLE_ALPHA);
                FireCommonCallback();
            } else {
                overlayManager->PlaySheetTransition(host, true, false);
            }
            auto maskNode = overlayManager->GetSheetMask(host);
            if (maskNode) {
                UpdateMaskBackgroundColorRender();
            }
            windowChanged_ = false;
            topSafeAreaChanged_ = false;
        }
    }
    GetBuilderInitHeight();
}

void SheetPresentationPattern::IsCustomDetentsChanged(SheetStyle sheetStyle)
{
    unsigned int preDetentsSize = preDetents_.size();
    unsigned int userSetDetentsSize = sheetStyle.detents.size();
    // if preview detents size is not equal to the new one, set detents index to zero
    if (preDetentsSize != userSetDetentsSize) {
        detentsFinalIndex_ = 0;
        return;
    }

    // check whether the new coming one's content is equal to the last time input
    unsigned int length = std::min(preDetentsSize, userSetDetentsSize);
    for (unsigned int index = 0; index < length; index++) {
        if (sheetStyle.detents[index] != preDetents_[index]) {
            // if detents has been changed, set detents index to zero
            detentsFinalIndex_ = 0;
            break;
        }
    }
}

void SheetPresentationPattern::InitSheetDetents()
{
    // record input detents
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    IsCustomDetentsChanged(sheetStyle);
    preDetents_.clear();
    sheetDetentHeight_.clear();
    unSortedSheetDentents_.clear();
    float height = 0.0f;
    auto sheetNode = GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto geometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto pipelineContext = sheetNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto sheetTheme = pipelineContext->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto largeHeight = sheetMaxHeight_ - SHEET_BLANK_MINI_HEIGHT.ConvertToPx();
    auto sheetType = GetSheetType();
    auto sheetFrameHeight = geometryNode->GetFrameSize().Height();
    auto mediumSize = sheetTheme->GetMediumPercent();
    float largeHeightOfTheme = sheetTheme->GetHeightApplyFullScreen() ? pageHeight_ : largeHeight;
    largeHeightOfTheme *= sheetTheme->GetLargePercent();
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        mediumSize = MEDIUM_SIZE_PRE;
    }
    switch (sheetType) {
        case SheetType::SHEET_BOTTOMLANDSPACE:
            if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                height = sheetFrameHeight - SHEET_BLANK_MINI_HEIGHT.ConvertToPx();
                sheetDetentHeight_.emplace_back(height);
                break;
            }
            [[fallthrough]];
        case SheetType::SHEET_BOTTOM:
            [[fallthrough]];
        case SheetType::SHEET_BOTTOM_FREE_WINDOW:
            if (sheetStyle.detents.size() <= 0) {
                height = InitialSingleGearHeight(sheetStyle);
                sheetDetentHeight_.emplace_back(height);
                break;
            }
            InitDetents(sheetStyle, height, mediumSize, largeHeightOfTheme, largeHeight);
            std::sort(sheetDetentHeight_.begin(), sheetDetentHeight_.end(), std::less<float>());
            sheetDetentHeight_.erase(
                std::unique(sheetDetentHeight_.begin(), sheetDetentHeight_.end()), sheetDetentHeight_.end());
            break;
        case SheetType::SHEET_CENTER:
            height = (centerHeight_ + pageHeight_) / SHEET_HALF_HEIGHT;
            sheetDetentHeight_.emplace_back(height);
            break;
        case SheetType::SHEET_BOTTOM_OFFSET:
            height = InitialSingleGearHeight(sheetStyle);
            sheetDetentHeight_.emplace_back(height);
            break;
        default:
            break;
    }
}

void SheetPresentationPattern::InitDetents(
    SheetStyle sheetStyle, float height, double mediumSize, float largeHeightOfTheme, double largeHeight)
{
    for (auto iter : sheetStyle.detents) {
        preDetents_.emplace_back(iter);
        if (iter.sheetMode.has_value()) {
            if (iter.sheetMode == SheetMode::MEDIUM) {
                height = pageHeight_ * mediumSize;
            } else if (iter.sheetMode == SheetMode::LARGE) {
                height = largeHeightOfTheme;
            } else if (iter.sheetMode == SheetMode::AUTO) {
                height = GetFitContentHeight();
                height = GreatNotEqual(height, largeHeight) ? largeHeight : height;
                HandleFitContontChange(height);
            }
        } else {
            if (iter.height->Unit() == DimensionUnit::PERCENT) {
                height = iter.height->ConvertToPxWithSize(sheetMaxHeight_);
            } else {
                height = iter.height->ConvertToPx();
            }
            if (GreatNotEqual(height, largeHeight)) {
                height = largeHeight;
            } else if (LessNotEqual(height, 0)) {
                height = largeHeight;
            }
        }
        sheetDetentHeight_.emplace_back(height);
        unSortedSheetDentents_.emplace_back(height);
    }
}

void SheetPresentationPattern::HandleFitContontChange(float height)
{
    if ((NearEqual(height_, sheetFitContentHeight_)) && (!NearEqual(height, sheetFitContentHeight_))) {
        ChangeSheetHeight(height);
        ChangeSheetPage(height_);
        SheetTransition(true);
    }
    sheetFitContentHeight_ = height;
}

float SheetPresentationPattern::ComputeTransitionOffset(float sheetHeight)
{
    float offset = 0.0f;
    auto sheetType = GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP ||
        sheetType == SheetType::SHEET_BOTTOM_OFFSET || IsCurSheetNeedHalfFoldHover()
        || IsShowInSubWindow()) {
        offset = GetSheetOffset();
    } else {
        offset = GetPageHeightWithoutOffset() - sheetHeight;
    }
    return offset;
}

int32_t SheetPresentationPattern::GetSubWindowId()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, INVALID_SUBWINDOW_ID);
    auto sheetWrapper = host->GetParent();
    CHECK_NULL_RETURN(sheetWrapper, INVALID_SUBWINDOW_ID);
    auto wrapperNode = AceType::DynamicCast<FrameNode>(sheetWrapper);
    auto sheetWrapperPattern = wrapperNode->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_RETURN(sheetWrapperPattern, INVALID_SUBWINDOW_ID);
    return sheetWrapperPattern->GetSubWindowId();
}

SheetType SheetPresentationPattern::ComputeSheetTypeInSubWindow()
{
    SheetType sheetType = SheetType::SHEET_CENTER;
    auto instanceId = SubwindowManager::GetInstance()->GetParentContainerId(GetSubWindowId());
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, sheetType);
    auto mainWindowContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(mainWindowContext, sheetType);
    auto windowWidth = mainWindowContext->GetDisplayWindowRectInfo().Width();
    if (container->IsUIExtensionWindow()) {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(GetSubWindowId(),
            SubwindowType::TYPE_SHEET);
        CHECK_NULL_RETURN(subwindow, sheetType);
        windowWidth = subwindow->GetUIExtensionHostWindowRect().Width();
    }
    if (GreatOrEqual(windowWidth, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx())
        && sheetKey_.hasValidTargetNode) {
        sheetType =  SheetType::SHEET_POPUP;
    }
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, sheetType);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetStyle.sheetType.has_value()) {
        sheetType = sheetStyle.sheetType.value();
    }
    if (sheetType == SheetType::SHEET_POPUP && !sheetKey_.hasValidTargetNode) {
        sheetType =  SheetType::SHEET_CENTER;
    }
    return sheetType;
}

void SheetPresentationPattern::InitSheetTransitionAction(float offset)
{
    auto sheetNode = GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (IsShowInSubWindowTwoInOne()) {
        context->UpdateOpacity(0.0);
        context->UpdateTransformTranslate({ 0.0f, SUBWINDOW_SHEET_TRANSLATION.ConvertToPx() + offset, 0.0f });
    } else {
        context->UpdateTransformTranslate({ 0.0f, pageHeight_, 0.0f });
    }
}

void SheetPresentationPattern::SheetTransitionAction(float offset, bool isStart, bool isTransitionIn)
{
    auto sheetNode = GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (!isTransitionIn) {
        // play sheet dismiss transition and move sheet down to out of screen
        InitSheetTransitionAction(offset);
        return;
    }
    // play sheet enter transition
    if (isStart) {
        // move sheet down to out of screen
        InitSheetTransitionAction(offset);
    } else {
        // move sheet up
        if (IsShowInSubWindowTwoInOne()) {
            context->UpdateOpacity(1.0);
        }
        context->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
    }
}

SheetType SheetPresentationPattern::GetSheetType()
{
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        return SHEET_BOTTOM;
    }
    SheetType sheetType = SheetType::SHEET_BOTTOM;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, sheetType);
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, sheetType);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetStyle.showInSubWindow.value_or(false)) {
        return ComputeSheetTypeInSubWindow();
    }
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    TAG_LOGD(AceLogTag::ACE_SHEET, "GetSheetType displayWindowRect info is : %{public}s",
        windowGlobalRect.ToString().c_str());
    DeviceType deviceType = SystemProperties::GetDeviceType();
    // only bottom when width is less than 600vp
    if ((windowGlobalRect.Width() < SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) ||
        (sheetStyle.sheetType.has_value() && sheetStyle.sheetType.value() == SheetType::SHEET_BOTTOM)) {
        return sheetStyle.bottomOffset.has_value() && deviceType == DeviceType::TWO_IN_ONE ?
            SheetType::SHEET_BOTTOM_OFFSET : SheetType::SHEET_BOTTOM;
    }
    if (sheetThemeType_ == "auto") {
        GetSheetTypeWithAuto(sheetType);
    } else if (sheetThemeType_ == "popup") {
        GetSheetTypeWithPopup(sheetType);
    }
    return sheetType;
}

void SheetPresentationPattern::InitSheetMode()
{
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    scrollSizeMode_ = sheetStyle.scrollSizeMode.value_or(ScrollSizeMode::FOLLOW_DETENT);
    keyboardAvoidMode_ = sheetStyle.sheetKeyboardAvoidMode.value_or(SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL);
    sheetEffectEdge_ = sheetStyle.sheetEffectEdge.value_or(SheetEffectEdge::ALL);
}

void SheetPresentationPattern::GetSheetTypeWithAuto(SheetType& sheetType)
{
    auto rootHeight = PipelineContext::GetCurrentRootHeight();
    auto rootWidth = PipelineContext::GetCurrentRootWidth();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
#ifdef PREVIEW
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (container->IsFoldable() && container->GetCurrentFoldStatus() == FoldStatus::EXPAND) {
#else
    // when big fold expand
    if (IsFoldExpand() && !sheetTheme->IsOnlyBottom()) {
#endif
        sheetType = SheetType::SHEET_CENTER;
        auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto sheetStyle = layoutProperty->GetSheetStyleValue();
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN) &&
            sheetStyle.sheetType.has_value() && sheetStyle.sheetType.value() == SheetType::SHEET_POPUP) {
            sheetType = SheetType::SHEET_POPUP;
        }
    } else {
        if (LessNotEqual(rootHeight, rootWidth)) {
            sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
        } else {
            sheetType = SheetType::SHEET_BOTTOM;
        }
    }
}

void SheetPresentationPattern::GetSheetTypeWithPopup(SheetType& sheetType)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    double rootWidth = 0.0;
    if (windowSize_.has_value()) {
        rootWidth = windowSize_.value().Width();
    } else {
        rootWidth = PipelineContext::GetCurrentRootWidth();
    }
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
#ifdef PREVIEW
    rootWidth = pipelineContext->GetDisplayWindowRectInfo().Width();
#endif
    if (GreatOrEqual(rootWidth, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx())) {
        if (sheetStyle.sheetType.has_value()) {
            sheetType = sheetStyle.sheetType.value();
        } else {
            sheetType = SheetType::SHEET_POPUP;
        }
    } else if (GreatOrEqual(rootWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) &&
               LessNotEqual(rootWidth, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx())) {
        if (sheetStyle.sheetType.has_value()) {
            sheetType = sheetStyle.sheetType.value();
        } else {
            sheetType = SheetType::SHEET_CENTER;
        }
    } else {
        sheetType = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    }
    if (sheetType == SheetType::SHEET_POPUP && !sheetKey_.hasValidTargetNode) {
        sheetType = SheetType::SHEET_CENTER;
    }
}

void SheetPresentationPattern::SetUIFirstSwitch(bool isFirstTransition, bool isNone)
{
#ifdef ENABLE_ROSEN_BACKEND
    if (!isFirstTransition) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rosenContext = DynamicCast<RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(rosenContext);
    rosenContext->SetUIFirstSwitch(
        isNone ? OHOS::Rosen::RSUIFirstSwitch::NONE : OHOS::Rosen::RSUIFirstSwitch::MODAL_WINDOW_CLOSE);
#endif
}

void SheetPresentationPattern::BubbleStyleSheetTransition(bool isTransitionIn)
{
    auto host = this->GetHost();
    CHECK_NULL_VOID(host);
    if (!isTransitionIn) {
        const auto& overlayManager = GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto maskNode = overlayManager->GetSheetMask(host);
        if (maskNode) {
            overlayManager->PlaySheetMaskTransition(maskNode, host, false);
        }
        StartOffsetExitingAnimation();
        StartAlphaExitingAnimation(
            [weakNode = AceType::WeakClaim(AceType::RawPtr(host)), weakPattern = AceType::WeakClaim(this)]() {
                auto node = weakNode.Upgrade();
                CHECK_NULL_VOID(node);
                auto pattern = weakPattern.Upgrade();
                CHECK_NULL_VOID(pattern);
                const auto& overlayManager = pattern->GetOverlayManager();
                CHECK_NULL_VOID(overlayManager);
                overlayManager->FireAutoSave(node);
                pattern->OnDisappear();
                overlayManager->RemoveSheet(node);;
                pattern->FireCallback("false");
            });
        overlayManager->CleanSheet(host, GetSheetKey());
    }
}

void SheetPresentationPattern::StartOffsetEnteringAnimation()
{
    AnimationOption optionPosition;
    optionPosition.SetDuration(SHEET_ENTRY_ANIMATION_DURATION);
    optionPosition.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        optionPosition,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformTranslate({ 0.0f, Dimension(pattern->sheetOffsetY_), 0.0f });
        },
        nullptr);
}

void SheetPresentationPattern::StartAlphaEnteringAnimation(std::function<void()> finish)
{
    AnimationOption optionAlpha;
    optionAlpha.SetDuration(SHEET_ENTRY_ANIMATION_DURATION);
    optionAlpha.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(
        optionAlpha,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOpacity(SHEET_VISIABLE_ALPHA);
        },
        finish);
}

void SheetPresentationPattern::StartOffsetExitingAnimation()
{
    AnimationOption optionPosition;
    optionPosition.SetDuration(SHEET_EXIT_ANIMATION_DURATION);
    optionPosition.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        optionPosition,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformTranslate(
                { 0.0f, Dimension(pattern->sheetOffsetY_ - SHEET_INVISIABLE_OFFSET), 0.0f });
        },
        nullptr);
}

void SheetPresentationPattern::StartAlphaExitingAnimation(std::function<void()> finish)
{
    AnimationOption optionAlpha;
    optionAlpha.SetDuration(SHEET_EXIT_ANIMATION_DURATION);
    optionAlpha.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(
        optionAlpha,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOpacity(SHEET_INVISIABLE_ALPHA);
        },
        finish);
}

RefPtr<RenderContext> SheetPresentationPattern::GetRenderContext()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetRenderContext();
}

bool SheetPresentationPattern::PostTask(const TaskExecutor::Task& task, const std::string& name)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, name);
}

void SheetPresentationPattern::ResetToInvisible()
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateOpacity(SHEET_INVISIABLE_ALPHA);
    renderContext->UpdateTransformTranslate({ 0.0f, Dimension(sheetOffsetY_ - SHEET_INVISIABLE_OFFSET), 0.0f });
}

bool SheetPresentationPattern::IsFoldExpand()
{
    bool isExpand = false;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto foldStatus = container->GetCurrentFoldStatus();
    isExpand = foldStatus != FoldStatus::FOLDED && foldStatus != FoldStatus::UNKNOWN;
    if (isExpand) {
        TAG_LOGD(AceLogTag::ACE_SHEET, "Get Fold status IsFoldExpand is true");
        return true;
    } else {
        return false;
    }
}

void SheetPresentationPattern::ChangeSheetHeight(float height)
{
    if (!NearEqual(height_, height)) {
        isDirectionUp_ = GreatNotEqual(height, height_);
        height_ = height;
        SetCurrentHeightToOverlay(height_);
    }
}

void SheetPresentationPattern::StartSheetTransitionAnimation(
    const AnimationOption& option, bool isTransitionIn, float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    isAnimationProcess_ = true;
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetParent = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(sheetParent);
    if (isTransitionIn) {
        HandleDragEndAccessibilityEvent();
        animation_ = AnimationUtils::StartAnimation(
            option,
            [context, offset]() {
                if (context) {
                    context->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
                }
            },
            option.GetOnFinishEvent());
    } else {
        host->OnAccessibilityEvent(
            AccessibilityEventType::PAGE_CLOSE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
        sheetParent->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(
            HitTestMode::HTMTRANSPARENT);
        animation_ = AnimationUtils::StartAnimation(
            option,
            [context, weak = WeakClaim(this), offset, isTransitionIn]() {
                if (context) {
                    auto pattern = weak.Upgrade();
                    pattern->SheetTransitionAction(offset, false, isTransitionIn);
                    pattern->DismissSheetShadow(context);
                }
            },
            option.GetOnFinishEvent());
        const auto& overlayManager = GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->CleanSheet(host, GetSheetKey());
    }
}

void SheetPresentationPattern::DismissSheetShadow(const RefPtr<RenderContext>& context)
{
    auto shadow = context->GetBackShadow();
    if (!shadow.has_value()) {
        shadow = Shadow::CreateShadow(ShadowStyle::None);
    }
    auto color = shadow->GetColor();
    auto newColor = color.ChangeAlpha(0);
    shadow->SetColor(newColor);
    context->UpdateBackShadow(shadow.value());
}

void SheetPresentationPattern::ClipSheetNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto sheetSize = geometryNode->GetFrameSize();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    ResetClipShape();
    auto sheetType = GetSheetType();
    BorderRadiusProperty borderRadius(sheetTheme->GetSheetRadius());
    CalculateSheetRadius(borderRadius);
    if (IsSheetBottom()) {
        // set 1px for avoiding doudble radius black lines.
        borderRadius.radiusBottomLeft = 1.0_px;
        borderRadius.radiusBottomRight = 1.0_px;
    }
    renderContext->UpdateBorderRadius(borderRadius);
    if (sheetTheme->IsOuterBorderEnable() && !sheetStyle.borderWidth.has_value()) {
        renderContext->UpdateOuterBorderRadius(borderRadius);
    }
    if (sheetType == SheetType::SHEET_POPUP && sheetPopupInfo_.showArrow) {
        std::string clipPath;
        clipPath = GetPopupStyleSheetClipPath(sheetSize, borderRadius);
        auto path = AceType::MakeRefPtr<Path>();
        path->SetValue(clipPath);
        path->SetBasicShapeType(BasicShapeType::PATH);
        renderContext->UpdateClipShape(path);
    }
}

bool SheetPresentationPattern::IsWindowSizeChangedWithUndefinedReason(
    int32_t width, int32_t height, WindowSizeChangeReason type)
{
    bool isWindowChanged = false;
    if (windowSize_.has_value()) {
        isWindowChanged = (type == WindowSizeChangeReason::UNDEFINED &&
                           (windowSize_->Width() != width || windowSize_->Height() != height));
    }
    return isWindowChanged;
}

void SheetPresentationPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet WindowSizeChangeReason type is: %{public}d", type);
    auto sheetType = GetSheetType();
    if ((type == WindowSizeChangeReason::ROTATION) &&
        ((sheetType == SheetType::SHEET_BOTTOM) || (sheetType == SheetType::SHEET_BOTTOMLANDSPACE) ||
         (sheetType == SheetType::SHEET_BOTTOM_OFFSET))) {
        windowRotate_ = true;
        SetColumnMinSize(true);
        // Before rotation, reset to the initial mode sheet ratio of the current vertical or horizontal screen
        // It's actually a state where the soft keyboard is not pulled up
        if (isScrolling_) {
            ScrollTo(.0f);
        }
    }
    if (IsWindowSizeChangedWithUndefinedReason(width, height, type)) {
        windowChanged_ = true;
    }
    windowSize_ = SizeT<int32_t>(width, height);
    if (type == WindowSizeChangeReason::ROTATION || type == WindowSizeChangeReason::DRAG ||
        type == WindowSizeChangeReason::RESIZE) {
        windowChanged_ = true;
    }

    if (type == WindowSizeChangeReason::ROTATION && sheetType == SheetType::SHEET_CENTER) {
        auto recoverTask = [weak = WeakClaim(this), id = Container::CurrentId()] () {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->RecoverHalfFoldOrAvoidStatus();
        };
        PostTask(recoverTask, "ArkUISheetHalfFoldStatusSwitch");
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    UpdateSheetWhenSheetTypeChanged();
    auto windowManager = pipelineContext->GetWindowManager();
    if (windowManager && windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING) {
        host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    }
}

void SheetPresentationPattern::TranslateTo(float height)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateTransformTranslate({ 0.0f, height, 0.0f });
}

void SheetPresentationPattern::ScrollTo(float height)
{
    // height = 0 or height > 0
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scroll = GetSheetScrollNode();
    CHECK_NULL_VOID(scroll);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    auto layoutProp = scrollPattern->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto geometryNode = scroll->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    // height > 0, Scroll will reduce height, and become scrolling.
    isScrolling_ = height > 0;
    SetColumnMinSize(!isScrolling_);
    if (!AdditionalScrollTo(scroll, height)) {
        scrollHeight_ = height;
        float maxScrollDecreaseHeight = scrollHeight_;
        float maxAvoidSize = keyboardHeight_ - (sheetType_ == SheetType::SHEET_CENTER ? height_ - centerHeight_ : 0.f);
        auto pipelineContext = host->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto useCaretAvoidMode = pipelineContext->UsingCaretAvoidMode();
        /*
         * when the screen rotates from portrait to landscape, and the sheet needs to avoid caret twice,
         * there is a condition that, the caret position that does not exceed the height of sheet in portrait mode,
         * may be exceed the height of sheet in landscape mode. In that case,
         * the distance to avoid caret may exceed as well. To keep bindSheet display normally,
         * we need to obtain the minimum content height and then the avoidance is made.
         */
        if (useCaretAvoidMode && NonNegative(maxAvoidSize) && NonNegative(maxAvoidSize - sheetHeightUp_) &&
            maxScrollDecreaseHeight > maxAvoidSize - sheetHeightUp_) {
            maxScrollDecreaseHeight = maxAvoidSize - sheetHeightUp_;
        }
        layoutProp->UpdateUserDefinedIdealSize(CalcSize(std::nullopt,
            CalcLength(GetScrollHeight() - maxScrollDecreaseHeight)));
        auto curScrollOffset = (useCaretAvoidMode && Positive(height)) ? scrollPattern->GetTotalOffset() : 0.f;
        scrollPattern->UpdateCurrentOffset(-height + curScrollOffset, SCROLL_FROM_JUMP);
    }
    scroll->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

bool SheetPresentationPattern::AdditionalScrollTo(const RefPtr<FrameNode>& scroll, float height)
{
    if (NonPositive(height)) {
        return false;
    }
    // If ScrollHeight is larger than childHeight
    // there will be a scene that is still larger than childHeight after reducing Scrollheight to moving sheet up
    // At this point, even if JumpToPosition is negative, the Scroll will still not to scroll
    auto buildContent = GetFirstFrameNodeOfBuilder();
    CHECK_NULL_RETURN(buildContent, false);
    auto scrollHeight = scroll->GetGeometryNode() ? scroll->GetGeometryNode()->GetFrameSize().Height() : .0f;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto useCaretAvoidMode = pipelineContext->UsingCaretAvoidMode();
    if (useCaretAvoidMode) {
        scrollHeight = GetScrollHeight();
    }
    auto childHeight = buildContent->GetGeometryNode() ? buildContent->GetGeometryNode()->GetFrameSize().Height() : .0f;
    if (scrollHeight <= childHeight) {
        return false;
    }
    auto layoutProp = scroll->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_RETURN(layoutProp, false);
    auto geometryNode = scroll->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(scrollPattern, false);
    // Scroll first shrinks to the same size as childHeight, then reduces the height to allow it to scroll
    scrollHeight_ = scrollHeight - childHeight + height;
    layoutProp->UpdateUserDefinedIdealSize(
        CalcSize(std::nullopt, CalcLength(GetScrollHeight() - (scrollHeight - childHeight + height))));
    // And then scroll move the content with '-height' offset
    auto curScrollOffset = (useCaretAvoidMode && Positive(height)) ? scrollPattern->GetTotalOffset() : 0.f;
    scrollPattern->UpdateCurrentOffset(-height + curScrollOffset, SCROLL_FROM_JUMP);
    return true;
}

float SheetPresentationPattern::GetFirstChildHeight() const
{
    auto firstChildNode = GetTitleBuilderNode();
    CHECK_NULL_RETURN(firstChildNode, 0.0f);
    auto firstChildGeometryNode = firstChildNode->GetGeometryNode();
    CHECK_NULL_RETURN(firstChildGeometryNode, 0.0f);
    auto titleHeight = firstChildGeometryNode->GetFrameSize().Height();
    return titleHeight;
}

void SheetPresentationPattern::SetColumnMinSize(bool reset)
{
    auto buildContent = GetFirstFrameNodeOfBuilder();
    CHECK_NULL_VOID(buildContent);
    auto geometryNode = buildContent->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto props = buildContent->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(props);
    if (reset) {
        props->ResetCalcMinSize();
        return;
    }
    props->UpdateCalcMinSize(CalcSize(std::nullopt, CalcLength(builderHeight_)));
}

void SheetPresentationPattern::CalculateSheetRadius(BorderRadiusProperty& sheetRadius)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto sheetSize = geometryNode->GetFrameSize();
    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetSize.IsPositive()) {
        CalculateAloneSheetRadius(sheetRadius.radiusTopLeft, sheetStyle.radius->radiusTopLeft);
        CalculateAloneSheetRadius(sheetRadius.radiusTopRight, sheetStyle.radius->radiusTopRight);
        CalculateAloneSheetRadius(sheetRadius.radiusBottomLeft, sheetStyle.radius->radiusBottomLeft);
        CalculateAloneSheetRadius(sheetRadius.radiusBottomRight, sheetStyle.radius->radiusBottomRight);
    }
}

void SheetPresentationPattern::CalculateAloneSheetRadius(
    std::optional<Dimension>& sheetRadius, const std::optional<Dimension>& sheetStyleRadius)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto sheetSize = geometryNode->GetFrameSize();
    float half = 0.5f;
    if (sheetStyleRadius.has_value() && GreatOrEqual(sheetStyleRadius->Value(), 0.0f)) {
        if (sheetStyleRadius->Unit() == DimensionUnit::PERCENT) {
            sheetRadius = Dimension(sheetStyleRadius->Value() * sheetSize.Width());
        } else {
            sheetRadius = sheetStyleRadius;
        }
    }
    // The maximum value of radius is half the width of the page.
    if (sheetSize.Width() * half < sheetRadius->ConvertToPx()) {
        sheetRadius = Dimension(sheetSize.Width() * half);
    }
}

std::string SheetPresentationPattern::GetPopupStyleSheetClipPath(
    const SizeF& sheetSize, const BorderRadiusProperty& sheetRadius)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    }
    auto radiusTopLeft = sheetRadius.radiusTopLeft->ConvertToPx();
    auto radiusTopRight = sheetRadius.radiusTopRight->ConvertToPx();
    auto radiusBottomRight = sheetRadius.radiusBottomRight->ConvertToPx();
    auto radiusBottomLeft = sheetRadius.radiusBottomLeft->ConvertToPx();
    std::string path = MoveTo(0.0f, SHEET_ARROW_HEIGHT.ConvertToPx() + radiusTopLeft);
    path += ArcTo(radiusTopLeft, radiusTopLeft, 0.0f, 0, radiusTopLeft, SHEET_ARROW_HEIGHT.ConvertToPx());
    path +=
        LineTo(arrowOffset_.GetX() - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(), SHEET_ARROW_HEIGHT.ConvertToPx()); // P1
    path += LineTo(arrowOffset_.GetX() - ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx() - ARROW_VERTICAL_P2_OFFSET_Y.ConvertToPx()); // P2
    path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
        arrowOffset_.GetX() + ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx() - ARROW_VERTICAL_P4_OFFSET_Y.ConvertToPx()); // P4
    path +=
        LineTo(arrowOffset_.GetX() + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(), SHEET_ARROW_HEIGHT.ConvertToPx()); // P5
    path += LineTo(sheetSize.Width() - radiusTopRight, SHEET_ARROW_HEIGHT.ConvertToPx());
    path += ArcTo(
        radiusTopRight, radiusTopRight, 0.0f, 0, sheetSize.Width(), SHEET_ARROW_HEIGHT.ConvertToPx() + radiusTopRight);
    path += LineTo(sheetSize.Width(), sheetSize.Height() - radiusBottomRight);
    path +=
        ArcTo(radiusBottomRight, radiusBottomRight, 0.0f, 0, sheetSize.Width() - radiusBottomRight, sheetSize.Height());
    path += LineTo(radiusBottomLeft, sheetSize.Height());
    path += ArcTo(radiusBottomLeft, radiusBottomLeft, 0.0f, 0, 0.0f, sheetSize.Height() - radiusBottomLeft);
    return path + "Z";
}

std::string SheetPresentationPattern::GetCenterStyleSheetClipPath(SizeF sheetSize, Dimension sheetRadius)
{
    std::string path = MoveTo(0.0f, sheetRadius.ConvertToPx());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, sheetRadius.ConvertToPx(), 0.0f);
    path += LineTo(sheetSize.Width() - sheetRadius.ConvertToPx(), 0.0f);
    path += ArcTo(
        sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, sheetSize.Width(), sheetRadius.ConvertToPx());
    path += LineTo(sheetSize.Width(), sheetSize.Height() - sheetRadius.ConvertToPx());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0,
        sheetSize.Width() - sheetRadius.ConvertToPx(), sheetSize.Height());
    path += LineTo(sheetRadius.ConvertToPx(), sheetSize.Height());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, 0.0f,
        sheetSize.Height() - sheetRadius.ConvertToPx());
    return path + "Z";
}

std::string SheetPresentationPattern::GetBottomStyleSheetClipPath(SizeF sheetSize, Dimension sheetRadius)
{
    std::string path = MoveTo(0.0f, sheetRadius.ConvertToPx());
    path += ArcTo(sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, sheetRadius.ConvertToPx(), 0.0f);
    path += LineTo(sheetSize.Width() - sheetRadius.ConvertToPx(), 0.0f);
    path += ArcTo(
        sheetRadius.ConvertToPx(), sheetRadius.ConvertToPx(), 0.0f, 0, sheetSize.Width(), sheetRadius.ConvertToPx());
    path += LineTo(sheetSize.Width(), sheetSize.Height());
    path += LineTo(0.0f, sheetSize.Height());
    return path + "Z";
}

std::string SheetPresentationPattern::MoveTo(double x, double y)
{
    return "M" + std::to_string(x) + " " + std::to_string(y) + " ";
}

std::string SheetPresentationPattern::LineTo(double x, double y)
{
    return "L" + std::to_string(x) + " " + std::to_string(y) + " ";
}

std::string SheetPresentationPattern::ArcTo(double rx, double ry, double rotation, int32_t arc_flag, double x, double y)
{
    int32_t sweep_flag = 1;
    return "A" + std::to_string(rx) + " " + std::to_string(ry) + " " + std::to_string(rotation) + " " +
           std::to_string(arc_flag) + " " + std::to_string(sweep_flag) + " " + std::to_string(x) + " " +
           std::to_string(y) + " ";
}

float SheetPresentationPattern::GetFitContentHeight()
{
    auto sheetNode = GetHost();
    CHECK_NULL_RETURN(sheetNode, 0.0f);
    auto titleColumn = DynamicCast<FrameNode>(sheetNode->GetFirstChild());
    CHECK_NULL_RETURN(titleColumn, 0.0f);
    auto titleGeometryNode = titleColumn->GetGeometryNode();
    auto builderNode = GetFirstFrameNodeOfBuilder();
    CHECK_NULL_RETURN(builderNode, 0.0f);
    auto builderGeometryNode = builderNode->GetGeometryNode();
    return builderGeometryNode->GetMarginFrameSize().Height() + titleGeometryNode->GetFrameSize().Height();
}

RefPtr<OverlayManager> SheetPresentationPattern::GetOverlayManager()
{
    const auto& layoutProp = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProp, nullptr);
    auto showInPage = layoutProp->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false);

    if (layoutProp->GetSheetStyleValue(SheetStyle()).showInSubWindow.value_or(false)) {
        auto aceContainer = AceEngine::Get().GetContainer(GetSubWindowId());
        CHECK_NULL_RETURN(aceContainer, nullptr);
        auto context = DynamicCast<NG::PipelineContext>(aceContainer->GetPipelineContext());
        CHECK_NULL_RETURN(context, nullptr);
        auto overlayManager = context->GetOverlayManager();
        return overlayManager;
    }
    if (!showInPage) {
        return PipelineContext::GetCurrentContext()->GetOverlayManager();
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto sheetWrapper = host->GetParent();
    CHECK_NULL_RETURN(sheetWrapper, nullptr);
    auto node = AceType::DynamicCast<FrameNode>(sheetWrapper->GetParent());
    CHECK_NULL_RETURN(node, nullptr);
    RefPtr<OverlayManager> overlay;
    if (node->GetTag() == V2::PAGE_ETS_TAG) {
        auto pattern = node->GetPattern<PagePattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        overlay = pattern->GetOverlayManager();
    } else if (node->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto pattern = node->GetPattern<NavDestinationPattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        overlay = pattern->GetOverlayManager();
    }
    if (!overlay) {
        auto overlayManager = overlayManager_.Upgrade();
        overlay = overlayManager;
    }
    return overlay;
}

RefPtr<FrameNode> SheetPresentationPattern::GetFirstFrameNodeOfBuilder() const
{
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_RETURN(scrollNode, nullptr);
    auto buildNode = scrollNode->GetChildAtIndex(0);
    CHECK_NULL_RETURN(buildNode, nullptr);
    return AceType::DynamicCast<FrameNode>(buildNode->GetFrameChildByIndex(0, true));
}

void SheetPresentationPattern::GetBuilderInitHeight()
{
    auto buildContent = GetFirstFrameNodeOfBuilder();
    CHECK_NULL_VOID(buildContent);
    auto geometryNode = buildContent->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    builderHeight_ = geometryNode->GetFrameSize().Height();
}

RefPtr<FrameNode> SheetPresentationPattern::GetOverlayRoot()
{
    const auto& layoutProp = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProp, nullptr);
    auto showInPage = layoutProp->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false);
    if (!showInPage) {
        auto overlay = PipelineContext::GetCurrentContext()->GetOverlayManager();
        CHECK_NULL_RETURN(overlay, nullptr);
        return AceType::DynamicCast<FrameNode>(overlay->GetRootNode().Upgrade());
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto sheetWrapper = host->GetParent();
    CHECK_NULL_RETURN(sheetWrapper, nullptr);
    return AceType::DynamicCast<FrameNode>(sheetWrapper->GetParent());
}

float SheetPresentationPattern::GetRootOffsetYToWindow()
{
    const auto& layoutProp = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProp, .0f);
    const auto& showInPage = layoutProp->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false);
    CHECK_NULL_RETURN(showInPage, .0f);
    const auto& overlayNode = GetOverlayRoot();
    CHECK_NULL_RETURN(overlayNode, .0f);
    auto parertOffset = overlayNode->GetOffsetRelativeToWindow();
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "PageLevel Node's offset to window: %{public}s", parertOffset.ToString().c_str());
    return parertOffset.GetY();
}

void SheetPresentationPattern::DumpAdvanceInfo()
{
    DumpLog::GetInstance().AddDesc("------------------------------------------");
    DumpLog::GetInstance().AddDesc(
        "TargetId: " + std::to_string(static_cast<int32_t>(targetId_)) + " , TargetTag : " + targetTag_);
    DumpLog::GetInstance().AddDesc("------------ SheetPage Pattern : ");
    DumpLog::GetInstance().AddDesc(
        std::string("SheetType: ").append(std::to_string(static_cast<int32_t>(GetSheetType()))));
    DumpLog::GetInstance().AddDesc(std::string("SheetPage Node Height: ").append(std::to_string(centerHeight_)));
    DumpLog::GetInstance().AddDesc(
        std::string("Sheet Height [start from the bottom, KeyboardHeight = 0]: ").append(std::to_string(height_)));
    DumpLog::GetInstance().AddDesc(
        std::string("SheetMaxHeight [start from the bottom, pageHeight - sheetTopSafeArea]: ")
            .append(std::to_string(sheetMaxHeight_)));
    DumpLog::GetInstance().AddDesc(std::string("Page Height: ").append(std::to_string(pageHeight_)));
    DumpLog::GetInstance().AddDesc(
        std::string("StatusBar Height [current sheetType needed]: ").append(std::to_string(sheetTopSafeArea_)));
    DumpLog::GetInstance().AddDesc(std::string("PopupSheet OffsetX: ").append(std::to_string(sheetOffsetX_)));
    DumpLog::GetInstance().AddDesc(std::string("PopupSheet OffsetY: ").append(std::to_string(sheetOffsetY_)));
    DumpLog::GetInstance().AddDesc(std::string("SheetMaxWidth: ").append(std::to_string(sheetMaxWidth_)));
    DumpLog::GetInstance().AddDesc(std::string("FitContent Height: ").append(std::to_string(sheetFitContentHeight_)));
    DumpLog::GetInstance().AddDesc("SheetThemeType: " + sheetThemeType_);
    DumpLog::GetInstance().AddDesc(std::string("currentOffset: ").append(std::to_string(currentOffset_)));
    DumpLog::GetInstance().AddDesc("------------");
    DumpLog::GetInstance().AddDesc(
        std::string("Height ScrollTo [KeyboardHeight > 0, and is scrolling]: ").append(std::to_string(-scrollHeight_)));
    DumpLog::GetInstance().AddDesc(std::string("KeyboardHeight: ").append(std::to_string(keyboardHeight_)));
    DumpLog::GetInstance().AddDesc(std::string("is scrolling: ").append(isScrolling_ ? "true" : "false"));
    DumpLog::GetInstance().AddDesc(std::string("SheetHeightUp[sheet offset to move up when avoiding keyboard]: ")
                                       .append(std::to_string(sheetHeightUp_)));
    DumpLog::GetInstance().AddDesc("------------");
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    DumpLog::GetInstance().AddDesc(
        std::string("height: ").append(sheetStyle.sheetHeight.height.has_value() ?
        sheetStyle.sheetHeight.height->ToString() : "None"));
    DumpLog::GetInstance().AddDesc(
        ("sheetMode: ") + (sheetStyle.sheetHeight.sheetMode.has_value()
                                  ? std::to_string(static_cast<int32_t>(sheetStyle.sheetHeight.sheetMode.value()))
                                  : "None"));
    DumpLog::GetInstance().AddDesc(std::string("detents' Size: ").append(std::to_string(sheetStyle.detents.size())));
    DumpLog::GetInstance().AddDesc(std::string("IsShouldDismiss: ").append(shouldDismiss_ ? "true" : "false"));
}

void SheetPresentationPattern::FireOnHeightDidChange()
{
    auto height = 0.0f;
    if (!IsSheetBottomStyle()) {
        height = centerHeight_;
    } else {
        height = height_;
    }
    if (NearEqual(preDidHeight_, height)) {
        return;
    }
    OnHeightDidChange(height);
    preDidHeight_ = height;
}

void SheetPresentationPattern::FireOnDetentsDidChange(float height)
{
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (!IsSheetBottomStyle() || NearEqual(preDetentsHeight_, height) ||
        LessOrEqual(sheetStyle.detents.size(), 0)) {
        return;
    }
    OnDetentsDidChange(height);
    preDetentsHeight_ = height;
}

void SheetPresentationPattern::FireOnWidthDidChange(RefPtr<FrameNode> sheetNode)
{
    auto sheetGeo = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(sheetGeo);
    auto width = sheetGeo->GetFrameSize().Width();
    if (NearEqual(preWidth_, width)) {
        return;
    }
    onWidthDidChange(width);
    preWidth_ = width;
}

void SheetPresentationPattern::FireOnTypeDidChange()
{
    auto sheetType = sheetType_;
    if (IsSheetBottomStyle() || sheetType == SheetType::SHEET_BOTTOM_OFFSET) {
        sheetType = SheetType::SHEET_BOTTOM;
    }
    if (preType_ == sheetType) {
        return;
    }
    onTypeDidChange(sheetType);
    preType_ = sheetType;
}

bool SheetPresentationPattern::IsScrollOutOfBoundary()
{
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_RETURN(scrollNode, false);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(scrollPattern, false);
    return scrollPattern->OutBoundaryCallback();
}

void SheetPresentationPattern::OnScrollStartRecursive(
    WeakPtr<NestableScrollContainer> child, float position, float velocity)
{
    InitScrollProps();
    if (animation_ && isAnimationProcess_) {
        AnimationUtils::StopAnimation(animation_);
        isAnimationBreak_ = true;
    }
    currentOffset_ = 0.0f;
    isSheetNeedScroll_ = false;
    isDirectionUp_ = true;
    GetCurrentBroadcastDetentsIndex();
}

ScrollResult SheetPresentationPattern::HandleScroll(float scrollOffset, int32_t source, NestedState state,
    float velocity)
{
    if (state == NestedState::CHILD_CHECK_OVER_SCROLL) {
        return {scrollOffset, true};
    }
    ScrollResult result = {0, true};
    if (GreatOrEqual(currentOffset_, 0.0) && (source == SCROLL_FROM_UPDATE) && !isSheetNeedScroll_) {
        isSheetNeedScroll_ = true;
    }
    if (!isSheetNeedScroll_ || IsScrollOutOfBoundary()) {
        return {scrollOffset, true};
    }
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_SCROLL) {
        if (scrollState == ScrollState::SCROLL) {
            return HandleScrollWithSheet(scrollOffset);
        }
        if (isSheetPosChanged_) {
            HandleDragEnd(scrollOffset > 0 ? SHEET_VELOCITY_THRESHOLD : -SHEET_VELOCITY_THRESHOLD);
            isSheetPosChanged_ = false;
        }
    } else if (state == NestedState::CHILD_OVER_SCROLL) {
        isSheetNeedScroll_ = false;
        return {scrollOffset, true};
    }
    return result;
}

ScrollResult SheetPresentationPattern::HandleScrollWithSheet(float scrollOffset)
{
    ScrollResult result = {0, true};
    auto sheetType = GetSheetType();
    auto sheetDetentsSize = sheetDetentHeight_.size();
    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0) || IsShowInSubWindowTwoInOne()) {
        isSheetNeedScroll_ = false;
        return {scrollOffset, true};
    }

    auto currentHeightPos = GetSheetHeightBeforeDragUpdate();
    bool isDraggingUp = LessNotEqual(scrollOffset, 0.0f);
    bool isReachMaxSheetHeight = GreatOrEqual(currentHeightPos, GetMaxSheetHeightBeforeDragUpdate());

    // When dragging up the sheet, and sheet height is larger than sheet content height,
    // the sheet height should be updated.
    // When dragging up the sheet, and sheet height is less than or equal to sheet content height,
    // the sheet content should scrolling.
    if ((NearZero(currentOffset_)) && isDraggingUp && isReachMaxSheetHeight) {
        isSheetNeedScroll_ = false;
        return {scrollOffset, true};
    }

    // When dragging up the sheet, and sheet height is larger than max height,
    // should set the coefficient of friction.
    bool isExceedMaxSheetHeight =
        GreatNotEqual((currentHeightPos - currentOffset_), GetMaxSheetHeightBeforeDragUpdate());
    bool isNeedCalculateFriction = isExceedMaxSheetHeight && isDraggingUp;
    if (isNeedCalculateFriction && GreatNotEqual(sheetMaxHeight_, 0.0f)) {
        auto friction = CalculateFriction((currentHeightPos - currentOffset_) / sheetMaxHeight_, GetRadio());
        scrollOffset = scrollOffset * friction;
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);
    currentOffset_ = currentOffset_ + scrollOffset;
    auto pageHeight = GetPageHeightWithoutOffset();
    auto sheetOffsetInPage = pageHeight - currentHeightPos + currentOffset_;
    if (LessOrEqual(sheetOffsetInPage, pageHeight - sheetMaxHeight_)) {
        sheetOffsetInPage = pageHeight - sheetMaxHeight_;
        currentOffset_ = currentHeightPos - sheetMaxHeight_;
    }
    bool isNeedChangeScrollHeight = scrollSizeMode_ == ScrollSizeMode::CONTINUOUS && isDraggingUp;
    if (isNeedChangeScrollHeight) {
        ChangeScrollHeight(currentHeightPos - currentOffset_);
    }
    HandleFollowAccessibilityEvent(currentHeightPos - currentOffset_);
    auto renderContext = host->GetRenderContext();
    renderContext->UpdateTransformTranslate({ 0.0f, sheetOffsetInPage, 0.0f });
    isSheetPosChanged_ = NearZero(scrollOffset) ? false : true;
    if (IsSheetBottomStyle()) {
        OnHeightDidChange(height_ - currentOffset_ + sheetHeightUp_);
    }
    isSheetPosChanged_ = true;
    return result;
}

void SheetPresentationPattern::OnScrollEndRecursive(const std::optional<float>& velocity)
{
    if (isSheetPosChanged_) {
        HandleDragEnd(velocity.value_or(0.f));
        isSheetPosChanged_ = false;
    }
}

bool SheetPresentationPattern::HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child)
{
    if (isSheetPosChanged_) {
        HandleDragEnd(velocity);
        isSheetPosChanged_ = false;
    }
    // Use child edge effect
    if (!isSheetNeedScroll_) {
        return false;
    }
    return true;
}

bool SheetPresentationPattern::IsTypeNeedAvoidAiBar()
{
    auto overlay = GetOverlayManager();
    auto layoutProp = GetLayoutProperty<SheetPresentationProperty>();
    if (overlay && overlay->IsRootExpansive() &&
        layoutProp->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false)) {
        return false;
    }
    return sheetType_ == SheetType::SHEET_BOTTOM || sheetType_ == SheetType::SHEET_BOTTOMLANDSPACE ||
           sheetType_ == SheetType::SHEET_BOTTOM_OFFSET;
}

void SheetPresentationPattern::IsNeedPlayTransition(const SheetStyle& inputStyle)
{
    isPlayTransition_ = false;
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto preStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    if (preStyle.sheetHeight.height != inputStyle.sheetHeight.height) {
        isPlayTransition_ = true;
        return;
    }
    if (preStyle.detents != inputStyle.detents) {
        isPlayTransition_ = true;
        return;
    }
    if (preStyle.sheetHeight.sheetMode != inputStyle.sheetHeight.sheetMode) {
        isPlayTransition_ = true;
        return;
    }
    isPlayTransition_ = UpdateIndexByDetentSelection(inputStyle, false) || isPlayTransition_;
}

bool SheetPresentationPattern::UpdateIndexByDetentSelection(const SheetStyle& inputStyle, bool isFirstTransition)
{
    if (!inputStyle.detentSelection.has_value() || inputStyle.detents.size() == 0) {
        // when input detentSelection or detent selection is invalid
        return false;
    }
    auto selection = inputStyle.detentSelection.value();
    if ((selection.sheetMode.has_value() && selection.sheetMode.value() == NG::SheetMode::AUTO) ||
        (selection.height.has_value() && selection.height.value().IsNegative())) {
        return false;
    }
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto preStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    if (!isFirstTransition && preStyle.detentSelection == inputStyle.detentSelection) {
        // only when sheet is first pulled up or pre-detents equal to current detents, otherwise false
        return false;
    }
    for (uint32_t index = 0; index < inputStyle.detents.size(); index++) {
        if (inputStyle.detents[index] == inputStyle.detentSelection.value()) {
            detentsFinalIndex_ = index;
            TAG_LOGI(AceLogTag::ACE_SHEET, "find detent selection is %u", index);
            return true;
        }
    }
    return false;
}

void SheetPresentationPattern::OverlayDismissSheet()
{
    auto overlayManager = GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->DismissSheet();
}

void SheetPresentationPattern::OverlaySheetSpringBack()
{
    auto overlayManager = GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->SheetSpringBack();
}

PipelineContext* SheetPresentationPattern::GetSheetMainPipeline() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto pipelineContext = host->GetContext();
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());

    if (sheetStyle.instanceId.has_value()) {
        // need to get mainWindow's pipeline, and get mainWindow's cutoutSafeArea
        auto container = Container::GetContainer(sheetStyle.instanceId.value());
        CHECK_NULL_RETURN(container, nullptr);
        auto parentId = container->GetParentId();
        TAG_LOGI(AceLogTag::ACE_SHEET, "mainWindow id : %{public}d", parentId);
        auto parentContainer = Container::GetContainer(parentId);
        CHECK_NULL_RETURN(parentContainer, nullptr);
        auto parentPipelineBase = parentContainer->GetPipelineContext();
        CHECK_NULL_RETURN(parentPipelineBase, nullptr);
        auto parentPipelineContext = AceType::DynamicCast<PipelineContext>(parentPipelineBase);
        pipelineContext = RawPtr(parentPipelineContext);
    }
    return pipelineContext;
}

float SheetPresentationPattern::GetBottomSafeArea()
{
    auto pipelineContext = GetSheetMainPipeline();
    CHECK_NULL_RETURN(pipelineContext, .0f);
    auto safeAreaInsets = pipelineContext->GetSafeAreaWithoutProcess();
    auto manager = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_RETURN(manager, .0f);
    auto cutoutSafeArea = manager->GetCutoutSafeAreaWithoutProcess();
    if (cutoutSafeArea.top_.IsValid()) {
        auto topAreaInWindow = GetTopAreaInWindow();
        TAG_LOGD(AceLogTag::ACE_SHEET, "rosen window sheetTopSafeArea of sheet is : %{public}f", topAreaInWindow);
        return topAreaInWindow;
    } else {
        return safeAreaInsets.top_.Length();
    }
}

// Height of status bar
float SheetPresentationPattern::GetTopAreaInWindow() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0f);
    auto window = pipelineContext->GetWindow();
    CHECK_NULL_RETURN(window, 0.0f);
    return window->GetStatusBarHeight();
}

void SheetPresentationPattern::MarkSheetPageNeedRender()
{
    auto parentHost = GetHost()->GetParent();
    CHECK_NULL_VOID(parentHost);
    auto frameNode = AceType::DynamicCast<FrameNode>(parentHost);
    CHECK_NULL_VOID(frameNode);
    frameNode->MarkNeedRenderOnly();
}

void SheetPresentationPattern::SetSheetOuterBorderWidth(
    const RefPtr<SheetTheme>& sheetTheme, const NG::SheetStyle& sheetStyle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetType = GetSheetType();
    if (sheetTheme->IsOuterBorderEnable() && !sheetStyle.borderWidth.has_value()) {
        BorderWidthProperty borderWidth;
        BorderWidthProperty outBorderWidth;
        BorderColorProperty borderColor;
        BorderColorProperty outBorderColor;
        borderWidth.SetBorderWidth(0.0_vp);
        outBorderWidth.SetBorderWidth(0.0_vp);
        if (sheetType != SheetType::SHEET_POPUP) {
            borderColor.SetColor(sheetTheme->GetSheetInnerBorderColor());
            outBorderColor.SetColor(sheetTheme->GetSheetOuterBorderColor());
            renderContext->UpdateOuterBorderColor(outBorderColor);
            renderContext->UpdateBorderColor(borderColor);
            if (sheetType == SheetType::SHEET_CENTER || sheetType == SheetType::SHEET_BOTTOM_OFFSET) {
                borderWidth.SetBorderWidth(sheetTheme->GetSheetInnerBorderWidth());
                outBorderWidth.SetBorderWidth(sheetTheme->GetSheetOuterBorderWidth());
            } else {
                borderWidth.leftDimen = sheetTheme->GetSheetInnerBorderWidth();
                borderWidth.topDimen = sheetTheme->GetSheetInnerBorderWidth();
                borderWidth.rightDimen = sheetTheme->GetSheetInnerBorderWidth();
                outBorderWidth.leftDimen = sheetTheme->GetSheetOuterBorderWidth();
                outBorderWidth.topDimen = sheetTheme->GetSheetOuterBorderWidth();
                outBorderWidth.rightDimen = sheetTheme->GetSheetOuterBorderWidth();
            }
        }
        layoutProperty->UpdateBorderWidth(borderWidth);
        renderContext->UpdateBorderWidth(borderWidth);
        layoutProperty->UpdateOuterBorderWidth(outBorderWidth);
        renderContext->UpdateOuterBorderWidth(outBorderWidth);
    }
}

void SheetPresentationPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("TargetId", static_cast<int32_t>(targetId_));
    json->Put("TargetTag", targetTag_.c_str());
    std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
    children->Put("SheetType", static_cast<int32_t>(GetSheetType()));
    children->Put("SheetPage Node Height", centerHeight_);
    children->Put("Sheet Height [start from the bottom, KeyboardHeight = 0]", height_);
    children->Put("SheetMaxHeight [start from the bottom, pageHeight - sheetTopSafeArea]", sheetMaxHeight_);
    children->Put("Page Height", pageHeight_);
    children->Put("StatusBar Height [current sheetType needed]", sheetTopSafeArea_);
    children->Put("PopupSheet OffsetX", sheetOffsetX_);
    children->Put("PopupSheet OffsetX", sheetOffsetY_);
    children->Put("SheetMaxWidth", sheetMaxWidth_);
    children->Put("FitContent Height", sheetFitContentHeight_);
    children->Put("SheetThemeType", sheetThemeType_.c_str());
    children->Put("currentOffset", currentOffset_);
    json->Put("SheetPage Pattern", children);

    json->Put("Height ScrollTo [KeyboardHeight > 0, and is scrolling]", -scrollHeight_);
    json->Put("KeyboardHeight", static_cast<int32_t>(keyboardHeight_));
    json->Put("is scrolling", isScrolling_);
    json->Put("SheetHeightUp[sheet offset to move up when avoiding keyboard]", sheetHeightUp_);

    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    json->Put("height", sheetStyle.sheetHeight.height.has_value() ?
        sheetStyle.sheetHeight.height->ToString().c_str() : "None");
    json->Put("sheetMode", sheetStyle.sheetHeight.sheetMode.has_value()
                               ? std::to_string(static_cast<int32_t>(sheetStyle.sheetHeight.sheetMode.value())).c_str()
                               : "None");
    json->Put("detents Size", static_cast<int32_t>(sheetStyle.detents.size()));
    json->Put("IsShouldDismiss", shouldDismiss_ ? "true" : "false");
}

void SheetPresentationPattern::AvoidKeyboardBySheetMode(bool forceAvoid)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    bool isCurrentFocus = host->GetFocusHub()->IsCurrentFocus();
    if (keyboardAvoidMode_ == SheetKeyboardAvoidMode::NONE || !isCurrentFocus) {
        TAG_LOGD(AceLogTag::ACE_SHEET,
            "Sheet will not avoid keyboard.keyboardAvoidMode:%{public}d, isCurrentFocus:%{public}d.",
            keyboardAvoidMode_, isCurrentFocus);
        return;
    }
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetSafeAreaManager();
    if (keyboardHeight_ == manager->GetKeyboardInset().Length() && !forceAvoid) {
        return;
    }
    keyboardHeight_ = manager->GetKeyboardInset().Length();

    if (isDismissProcess_) {
        TAG_LOGD(AceLogTag::ACE_SHEET,
            "The sheet will disappear, so there's no need to handle canceling keyboard avoidance here.");
        return;
    }

    // 1.handle non upward logic: avoidKeyboardMode::RESIZE_ONLY
    if (AvoidKeyboardBeforeTranslate()) {
        return;
    }

    // 2.handle upward logic
    CHECK_NULL_VOID(host->GetFocusHub());
    // When bindSheet lift height exceed the max height, hightUp = the remaining height that needs to scroll,
    // otherwise, hightUp = the height to be lifted up
    auto heightUp = isCurrentFocus ? GetSheetHeightChange() : 0.0f;
    sheetHeightUp_ = heightUp;
    TAG_LOGD(AceLogTag::ACE_SHEET, "To avoid Keyboard, sheet needs to deal with %{public}f height.", heightUp);
    auto offset = pageHeight_ - height_ - heightUp;
    auto renderContext = host->GetRenderContext();

    // when bindSheet height exceed the max height, lift it up to the maxHeight,
    // otherwise, lift it up to show input area
    if (isScrolling_) {
        if (NearZero(heightUp)) {
            // scroll needs to reset first when keyboard is down.
            renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
        } else {
            sheetHeightUp_ = pageHeight_ - (SHEET_BLANK_MINI_HEIGHT.ConvertToPx() + sheetTopSafeArea_) - height_;
            // sheet is raised to the top first
            renderContext->UpdateTransformTranslate(
                { 0.0f, SHEET_BLANK_MINI_HEIGHT.ConvertToPx() + sheetTopSafeArea_, 0.0f });
        }
    } else {
        // offset: translate endpoint, calculated from top
        renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
    }

    // 3.deal with left height, scroll or resize
    if (isScrolling_) {
        AvoidKeyboardAfterTranslate(heightUp);
    }

    if (IsSheetBottomStyle()) {
        OnHeightDidChange(height_ + sheetHeightUp_);
    }
}

bool SheetPresentationPattern::AvoidKeyboardBeforeTranslate()
{
    if (keyboardAvoidMode_ == SheetKeyboardAvoidMode::RESIZE_ONLY) {
        // resize bindSheet need to keep safe distance from keyboard
        auto distanceFromBottom = sheetType_ == SheetType::SHEET_CENTER ? height_ - centerHeight_ : 0.0f;
        DecreaseScrollHeightInSheet(keyboardHeight_ == 0 ? 0.0f : keyboardHeight_ - distanceFromBottom);
        return true;
    }
    return false;
}

void SheetPresentationPattern::AvoidKeyboardAfterTranslate(float height)
{
    switch (keyboardAvoidMode_) {
    case SheetKeyboardAvoidMode::NONE:
    case SheetKeyboardAvoidMode::RESIZE_ONLY:
        break;
    case SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE:
        // resize bindSheet need to keep safe distance from keyboard
        DecreaseScrollHeightInSheet(keyboardHeight_ == 0 ? 0.0f : height);
        break;
    case SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL:
        ScrollTo(height);
        break;
    default:
        TAG_LOGW(AceLogTag::ACE_SHEET, "Invalid keyboard avoid mode %{public}d", keyboardAvoidMode_);
        break;
    }
}

void SheetPresentationPattern::DecreaseScrollHeightInSheet(float decreaseHeight)
{
    auto scroll = GetSheetScrollNode();
    CHECK_NULL_VOID(scroll);
    auto layoutProp = scroll->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);

    // height > 0, Scroll will reduce height, and need to set isScrolling true
    isScrolling_ = (decreaseHeight > 0);

    TAG_LOGD(AceLogTag::ACE_SHEET, "To avoid Keyboard, Scroll Height reduces by height %{public}f.", decreaseHeight);
    layoutProp->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(GetScrollHeight() - decreaseHeight)));
    resizeDecreasedHeight_ = decreaseHeight;
    scroll->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

bool SheetPresentationPattern::IsResizeWhenAvoidKeyboard()
{
    return keyboardAvoidMode_ == SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE ||
        keyboardAvoidMode_ == SheetKeyboardAvoidMode::RESIZE_ONLY;
}

void SheetPresentationPattern::ResetClipShape()
{
    // need reset clip path，when system clip path change to user defined
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateClipShape(nullptr);
    renderContext->ResetClipShape();
}

void SheetPresentationPattern::GetCurrentScrollHeight()
{
    if (!isScrolling_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    auto curOffset = scrollPattern->GetTotalOffset();
    if (NearEqual(scrollHeight_, curOffset)) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_SHEET, "scroll height changed because of user scrolling, %{public}f", curOffset);
    scrollHeight_ = curOffset;
}

void SheetPresentationPattern::UpdateSheetWhenSheetTypeChanged()
{
    auto sheetType = GetSheetType();
    if (sheetType_ != sheetType) {
        // It can only be MarkOuterBorder When the SheetType switches and the sheetType_ was SHEET_POPUP
        if (sheetType_ == SheetType::SHEET_POPUP) {
            MarkSheetPageNeedRender();
        }
        sheetType_ = sheetType;
        SetSheetBorderWidth();
    }
}

bool SheetPresentationPattern::IsCurSheetNeedHalfFoldHover()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, false);
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    auto enableHoverMode = sheetStyle.enableHoverMode.value_or(sheetTheme->IsOuterBorderEnable() ? true : false);
    bool isHoverMode = enableHoverMode ? pipeline->IsHalfFoldHoverStatus() : false;
    return isHoverMode && GetSheetType() == SheetType::SHEET_CENTER;
}

bool SheetPresentationPattern::IsShowInSubWindowTwoInOne()
{
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    if (!sheetStyle.showInSubWindow.value_or(false)) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, false);
    return sheetTheme->IsOuterBorderEnable();
}

bool SheetPresentationPattern::IsShowInSubWindow()
{
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    return sheetStyle.showInSubWindow.value_or(false);
}

void SheetPresentationPattern::InitFoldCreaseRegion()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    auto enableHoverMode = sheetStyle.enableHoverMode.value_or(sheetTheme->IsOuterBorderEnable() ? true : false);
    if (!enableHoverMode || !currentFoldCreaseRegion_.empty()) {
        return;
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_VOID(displayInfo);
    currentFoldCreaseRegion_ = displayInfo->GetCurrentFoldCreaseRegion();
}

Rect SheetPresentationPattern::GetFoldScreenRect() const
{
    if (currentFoldCreaseRegion_.empty()) {
        TAG_LOGW(AceLogTag::ACE_SHEET, "FoldCreaseRegion is invalid.");
        return Rect();
    }
    return currentFoldCreaseRegion_.front();
}

Shadow SheetPresentationPattern::GetShadowFromTheme(ShadowStyle shadowStyle)
{
    if (shadowStyle == ShadowStyle::None) {
        return Shadow();
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, Shadow());
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, Shadow());
    auto colorMode = pipelineContext->GetColorMode();
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, Shadow());
    auto shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return shadow;
}

void SheetPresentationPattern::FireHoverModeChangeCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (!IsCurSheetNeedHalfFoldHover()) {
        TAG_LOGD(AceLogTag::ACE_SHEET, "halfFoldHoverStatus: %{public}d, Sheet is not half folded.",
            pipeline->IsHalfFoldHoverStatus());
        return;
    }
    OnHeightDidChange(centerHeight_);
}

void SheetPresentationPattern::GetArrowOffsetByPlacement(
    const RefPtr<SheetPresentationLayoutAlgorithm>& layoutAlgorithm)
{
    CHECK_NULL_VOID(layoutAlgorithm);
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }
    finalPlacement_ = sheetPopupInfo_.finalPlacement;
    showArrow_ = sheetPopupInfo_.showArrow;
    arrowPosition_ = sheetPopupInfo_.arrowPosition;
    if (!showArrow_ || finalPlacement_ == Placement::NONE) {
        arrowOffset_ = OffsetF(0.f, 0.f);
        return;
    }

    switch (finalPlacement_) {
        case Placement::BOTTOM_LEFT:
            [[fallthrough]];
        case Placement::BOTTOM_RIGHT:
            [[fallthrough]];
        case Placement::BOTTOM:
            [[fallthrough]];
        case Placement::TOP_LEFT:
            [[fallthrough]];
        case Placement::TOP_RIGHT:
            [[fallthrough]];
        case Placement::TOP: {
            arrowOffset_ = OffsetF(sheetPopupInfo_.arrowOffsetX, 0.f);
            break;
        }
        case Placement::RIGHT_TOP:
            [[fallthrough]];
        case Placement::RIGHT_BOTTOM:
            [[fallthrough]];
        case Placement::RIGHT:
            [[fallthrough]];
        case Placement::LEFT_TOP:
            [[fallthrough]];
        case Placement::LEFT_BOTTOM:
            [[fallthrough]];
        case Placement::LEFT: {
            arrowOffset_ = OffsetF(0.f, sheetPopupInfo_.arrowOffsetY);
            break;
        }
        default:
            break;
    }
}

std::string SheetPresentationPattern::GetPopupStyleSheetClipPathNew(
    const SizeF& sheetSize, const BorderRadiusProperty& sheetRadius)
{
    std::string drawPath;
    switch (finalPlacement_) {
        case Placement::BOTTOM_LEFT:
            [[fallthrough]];
        case Placement::BOTTOM_RIGHT:
            [[fallthrough]];
        case Placement::BOTTOM: {
            drawPath = DrawClipPathBottom(sheetSize, sheetRadius);
            break;
        }
        case Placement::TOP_LEFT:
            [[fallthrough]];
        case Placement::TOP_RIGHT:
            [[fallthrough]];
        case Placement::TOP: {
            drawPath = DrawClipPathTop(sheetSize, sheetRadius);
            break;
        }
        case Placement::RIGHT_TOP:
            [[fallthrough]];
        case Placement::RIGHT_BOTTOM:
            [[fallthrough]];
        case Placement::RIGHT: {
            drawPath = DrawClipPathRight(sheetSize, sheetRadius);
            break;
        }
        case Placement::LEFT_TOP:
            [[fallthrough]];
        case Placement::LEFT_BOTTOM:
            [[fallthrough]];
        case Placement::LEFT: {
            drawPath = DrawClipPathLeft(sheetSize, sheetRadius);
            break;
        }
        default:
            break;
    }
    return drawPath;
}

std::string SheetPresentationPattern::DrawClipPathBottom(const SizeF& sheetSize,
    const BorderRadiusProperty& sheetRadius)
{
    auto radiusTopLeft = sheetRadius.radiusTopLeft->ConvertToPx();
    auto radiusTopRight = sheetRadius.radiusTopRight->ConvertToPx();
    auto radiusBottomRight = sheetRadius.radiusBottomRight->ConvertToPx();
    auto radiusBottomLeft = sheetRadius.radiusBottomLeft->ConvertToPx();
    // clip path start from TopLeft, and draw Right-angled arrow first if needed
    std::string path;
    if (arrowPosition_ == SheetArrowPosition::BOTTOM_LEFT) {
        path += MoveTo(0.f, SHEET_ARROW_HEIGHT.ConvertToPx());  // P5
        path += LineTo(0.f, (SHEET_ARROW_HEIGHT - ARROW_CORNER_P4_OFFSET_Y).ConvertToPx()); // P4
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
            (SHEET_ARROW_WIDTH - ARROW_CORNER_P2_OFFSET_X).ConvertToPx(),
            (SHEET_ARROW_HEIGHT - ARROW_CORNER_P2_OFFSET_Y).ConvertToPx()); // P2
        path += LineTo(SHEET_ARROW_WIDTH.ConvertToPx(), SHEET_ARROW_HEIGHT.ConvertToPx());  // P1
    } else {
        path += MoveTo(0.0f, SHEET_ARROW_HEIGHT.ConvertToPx() + radiusTopLeft);
        path += ArcTo(radiusTopLeft, radiusTopLeft, 0.0f, 0, radiusTopLeft,
            SHEET_ARROW_HEIGHT.ConvertToPx());
    }
    if (arrowPosition_ == SheetArrowPosition::NONE) {
        path += LineTo(arrowOffset_.GetX() - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
            SHEET_ARROW_HEIGHT.ConvertToPx());  // P1
        path += LineTo(arrowOffset_.GetX() - ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx(),
            (SHEET_ARROW_HEIGHT - ARROW_VERTICAL_P2_OFFSET_Y).ConvertToPx());   // P2
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
            arrowOffset_.GetX() + ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx(),
            (SHEET_ARROW_HEIGHT - ARROW_VERTICAL_P4_OFFSET_Y).ConvertToPx());   // P4
        path += LineTo(arrowOffset_.GetX() + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
            SHEET_ARROW_HEIGHT.ConvertToPx());  // P5
    }
    if (arrowPosition_ == SheetArrowPosition::BOTTOM_RIGHT) {
        path += LineTo(sheetSize.Width() -
            SHEET_ARROW_WIDTH.ConvertToPx(), SHEET_ARROW_HEIGHT.ConvertToPx());  // P1
        path += LineTo(sheetSize.Width() - (SHEET_ARROW_WIDTH - ARROW_CORNER_P2_OFFSET_X).ConvertToPx(),
            (SHEET_ARROW_HEIGHT - ARROW_CORNER_P2_OFFSET_Y).ConvertToPx()); // P2
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
            sheetSize.Width(), (SHEET_ARROW_HEIGHT - ARROW_CORNER_P4_OFFSET_Y).ConvertToPx());  // P4
        path += LineTo(sheetSize.Width(), SHEET_ARROW_HEIGHT.ConvertToPx());    // P5
    } else {
        path += LineTo(sheetSize.Width() - radiusTopRight, SHEET_ARROW_HEIGHT.ConvertToPx());
        path += ArcTo(radiusTopRight, radiusTopRight, 0.0f, 0, sheetSize.Width(),
            SHEET_ARROW_HEIGHT.ConvertToPx() + radiusTopRight);
    }
    path += LineTo(sheetSize.Width(), sheetSize.Height() - radiusBottomRight);
    path += ArcTo(radiusBottomRight, radiusBottomRight, 0.0f, 0,
        sheetSize.Width() - radiusBottomRight, sheetSize.Height());
    path += LineTo(radiusBottomLeft, sheetSize.Height());
    path += ArcTo(radiusBottomLeft, radiusBottomLeft, 0.0f, 0, 0.0f,
        sheetSize.Height() - radiusBottomLeft);
    return path + "Z";
}

std::string SheetPresentationPattern::DrawClipPathTop(const SizeF& sheetSize,
    const BorderRadiusProperty& sheetRadius)
{
    auto radiusTopLeft = sheetRadius.radiusTopLeft->ConvertToPx();
    auto radiusTopRight = sheetRadius.radiusTopRight->ConvertToPx();
    auto radiusBottomRight = sheetRadius.radiusBottomRight->ConvertToPx();
    auto radiusBottomLeft = sheetRadius.radiusBottomLeft->ConvertToPx();
    // clip path start from TopLeft, and draw sheet radius first
    std::string path;
    path += MoveTo(0.f, radiusTopLeft);
    path += ArcTo(radiusTopLeft, radiusTopLeft, 0.0f, 0, radiusTopLeft, 0.f);
    path += LineTo(sheetSize.Width() - radiusTopRight, 0.f);
    path += ArcTo(radiusTopRight, radiusTopRight, 0.0f, 0,
        sheetSize.Width(), radiusTopRight);
    if (arrowPosition_ == SheetArrowPosition::TOP_RIGHT) {
        path += LineTo(sheetSize.Width(),
            sheetSize.Height() - (SHEET_ARROW_HEIGHT - ARROW_CORNER_P4_OFFSET_Y).ConvertToPx());    // P4
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
            sheetSize.Width() - (SHEET_ARROW_WIDTH - ARROW_CORNER_P2_OFFSET_X).ConvertToPx(),
            sheetSize.Height() - (SHEET_ARROW_HEIGHT - ARROW_CORNER_P2_OFFSET_Y).ConvertToPx());    // P2
        path += LineTo(sheetSize.Width() - SHEET_ARROW_WIDTH.ConvertToPx(),
            sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx()); // P1
    } else {
        path += LineTo(sheetSize.Width(), sheetSize.Height() - radiusBottomRight - SHEET_ARROW_HEIGHT.ConvertToPx());
        path += ArcTo(radiusBottomRight, radiusBottomRight, 0.0f, 0,
            sheetSize.Width() - radiusBottomRight, sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx());
    }
    if (arrowPosition_ == SheetArrowPosition::NONE) {
        path += LineTo(arrowOffset_.GetX() + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
            sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx()); // P1
        path += LineTo(arrowOffset_.GetX() + ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx(),
            sheetSize.Height() - (SHEET_ARROW_HEIGHT - ARROW_VERTICAL_P2_OFFSET_Y).ConvertToPx());  // P2
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
            arrowOffset_.GetX() - ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx(),
            sheetSize.Height() - (SHEET_ARROW_HEIGHT - ARROW_VERTICAL_P4_OFFSET_Y).ConvertToPx());  // P4
        path += LineTo(arrowOffset_.GetX() - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
            sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx()); // P5
    }
    if (arrowPosition_ == SheetArrowPosition::TOP_LEFT) {
        path += LineTo(SHEET_ARROW_WIDTH.ConvertToPx(),
            sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx()); // P1
        path += LineTo((SHEET_ARROW_WIDTH - ARROW_CORNER_P2_OFFSET_X).ConvertToPx(),
            sheetSize.Height() - (SHEET_ARROW_HEIGHT - ARROW_CORNER_P2_OFFSET_Y).ConvertToPx());    // P2
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0, 0.f,
            sheetSize.Height() - (SHEET_ARROW_HEIGHT - ARROW_CORNER_P4_OFFSET_Y).ConvertToPx());    // P4
        path += LineTo(0.f, sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx()); // P5
    } else {
        path += LineTo(radiusBottomLeft, sheetSize.Height() - SHEET_ARROW_HEIGHT.ConvertToPx());
        path += ArcTo(radiusBottomLeft, radiusBottomLeft, 0.0f, 0,
            0.f, sheetSize.Height() - radiusBottomLeft - SHEET_ARROW_HEIGHT.ConvertToPx());
    }
    return path + "Z";
}

std::string SheetPresentationPattern::DrawClipPathLeft(const SizeF& sheetSize,
    const BorderRadiusProperty& sheetRadius)
{
    auto radiusTopLeft = sheetRadius.radiusTopLeft->ConvertToPx();
    auto radiusTopRight = sheetRadius.radiusTopRight->ConvertToPx();
    auto radiusBottomRight = sheetRadius.radiusBottomRight->ConvertToPx();
    auto radiusBottomLeft = sheetRadius.radiusBottomLeft->ConvertToPx();
    // clip path start from TopLeft, and draw sheet radius first
    std::string path;
    path += MoveTo(0.f, radiusTopLeft);
    path += ArcTo(radiusTopLeft, radiusTopLeft, 0.0f, 0, radiusTopLeft, 0.f);
    if (arrowPosition_ == SheetArrowPosition::LEFT_TOP) {
        path += LineTo(sheetSize.Width() - (SHEET_ARROW_HEIGHT - ARROW_CORNER_P4_OFFSET_Y).ConvertToPx(), 0.f); // P4
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
            sheetSize.Width() - (SHEET_ARROW_HEIGHT - ARROW_CORNER_P2_OFFSET_Y).ConvertToPx(),
            (SHEET_ARROW_WIDTH - ARROW_CORNER_P2_OFFSET_X).ConvertToPx());  // P2
        path += LineTo(sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx(),
            SHEET_ARROW_WIDTH.ConvertToPx());  // P1
    } else {
        path += LineTo(sheetSize.Width() - radiusTopRight - SHEET_ARROW_HEIGHT.ConvertToPx(), 0.f);
        path += ArcTo(radiusTopRight, radiusTopRight, 0.0f, 0,
            sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx(), radiusTopRight);
    }
    if (arrowPosition_ == SheetArrowPosition::NONE) {
        path += LineTo(sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx(),
            arrowOffset_.GetY() - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx());    // P1
        path += LineTo(sheetSize.Width() - (SHEET_ARROW_HEIGHT - ARROW_VERTICAL_P2_OFFSET_Y).ConvertToPx(),
            arrowOffset_.GetY() - ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx());    // P2
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
            sheetSize.Width() - (SHEET_ARROW_HEIGHT - ARROW_VERTICAL_P4_OFFSET_Y).ConvertToPx(),
            arrowOffset_.GetY() + ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx());    // P4
        path += LineTo(sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx(),
            arrowOffset_.GetY() + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx());    // P5
    }
    if (arrowPosition_ == SheetArrowPosition::LEFT_BOTTOM) {
        path += LineTo(sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx(),
            sheetSize.Height() - SHEET_ARROW_WIDTH.ConvertToPx());  // P1
        path += LineTo(sheetSize.Width() - (SHEET_ARROW_HEIGHT - ARROW_CORNER_P2_OFFSET_Y).ConvertToPx(),
            sheetSize.Height() - (SHEET_ARROW_WIDTH - ARROW_CORNER_P2_OFFSET_X).ConvertToPx()); // P2
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0, sheetSize.Width() -
            (SHEET_ARROW_HEIGHT - ARROW_CORNER_P4_OFFSET_Y).ConvertToPx(), sheetSize.Height()); // P4
        path += LineTo(sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx(), sheetSize.Height());   // P5
    } else {
        path += LineTo(sheetSize.Width() - SHEET_ARROW_HEIGHT.ConvertToPx(),
            sheetSize.Height() - radiusBottomRight);
        path += ArcTo(radiusBottomRight, radiusBottomRight, 0.0f, 0,
            sheetSize.Width() - radiusBottomRight - SHEET_ARROW_HEIGHT.ConvertToPx(), sheetSize.Height());
    }
    path += LineTo(radiusBottomLeft, sheetSize.Height());
    path += ArcTo(radiusBottomLeft, radiusBottomLeft, 0.0f, 0,
        0.f, sheetSize.Height() - radiusBottomLeft);
    return path + "Z";
}

std::string SheetPresentationPattern::DrawClipPathRight(const SizeF& sheetSize,
    const BorderRadiusProperty& sheetRadius)
{
    auto radiusTopLeft = sheetRadius.radiusTopLeft->ConvertToPx();
    auto radiusTopRight = sheetRadius.radiusTopRight->ConvertToPx();
    auto radiusBottomRight = sheetRadius.radiusBottomRight->ConvertToPx();
    auto radiusBottomLeft = sheetRadius.radiusBottomLeft->ConvertToPx();
    // clip path start from TopLeft, and if left side need draw left top Right-angled arrow, draw it first
    std::string path;
    if (arrowPosition_ == SheetArrowPosition::RIGHT_TOP) {
        path += MoveTo(SHEET_ARROW_HEIGHT.ConvertToPx(), SHEET_ARROW_WIDTH.ConvertToPx());  // P1
        path += LineTo((SHEET_ARROW_HEIGHT - ARROW_CORNER_P2_OFFSET_Y).ConvertToPx(),
            (SHEET_ARROW_WIDTH - ARROW_CORNER_P2_OFFSET_X).ConvertToPx());  // P2
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
            (SHEET_ARROW_HEIGHT - ARROW_CORNER_P4_OFFSET_Y).ConvertToPx(), 0.f);    // P4
        path += LineTo(SHEET_ARROW_HEIGHT.ConvertToPx(), 0.f);  // P5
    } else {
        path += MoveTo(SHEET_ARROW_HEIGHT.ConvertToPx(), radiusTopLeft);
        path += ArcTo(radiusTopLeft, radiusTopLeft, 0.0f, 0,
            radiusTopLeft + SHEET_ARROW_HEIGHT.ConvertToPx(), 0.f);
    }
    path += LineTo(sheetSize.Width() - radiusTopRight, 0.f);
    path += ArcTo(radiusTopRight, radiusTopRight, 0.0f, 0,
        sheetSize.Width(), radiusTopRight);
    path += LineTo(sheetSize.Width(), sheetSize.Height() - radiusBottomRight);
    path += ArcTo(radiusBottomRight, radiusBottomRight, 0.0f, 0,
        sheetSize.Width() - radiusBottomRight, sheetSize.Height());
    if (arrowPosition_ == SheetArrowPosition::RIGHT_BOTTOM) {
        path += LineTo(SHEET_ARROW_HEIGHT.ConvertToPx(), sheetSize.Height());   // P5
        path += LineTo((SHEET_ARROW_HEIGHT - ARROW_CORNER_P4_OFFSET_Y).ConvertToPx(), sheetSize.Height());  // P4
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
            (SHEET_ARROW_HEIGHT - ARROW_CORNER_P2_OFFSET_Y).ConvertToPx(),
            sheetSize.Height() - (SHEET_ARROW_WIDTH - ARROW_CORNER_P2_OFFSET_X).ConvertToPx()); // P2
        path += LineTo(SHEET_ARROW_HEIGHT.ConvertToPx(),
            sheetSize.Height() - SHEET_ARROW_WIDTH.ConvertToPx()); // P1
    } else {
        path += LineTo(radiusBottomLeft + SHEET_ARROW_HEIGHT.ConvertToPx(), sheetSize.Height());
        path += ArcTo(radiusBottomLeft, radiusBottomLeft, 0.0f, 0,
            SHEET_ARROW_HEIGHT.ConvertToPx(), sheetSize.Height() - radiusBottomLeft);
    }
    if (arrowPosition_ == SheetArrowPosition::NONE) {
        path += LineTo(SHEET_ARROW_HEIGHT.ConvertToPx(),
            arrowOffset_.GetY() + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx());    // P1
        path += LineTo((SHEET_ARROW_HEIGHT - ARROW_VERTICAL_P2_OFFSET_Y).ConvertToPx(),
            arrowOffset_.GetY() + ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx());    // P2
        path += ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, 0,
            (SHEET_ARROW_HEIGHT - ARROW_VERTICAL_P4_OFFSET_Y).ConvertToPx(),
            arrowOffset_.GetY() - ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx());    // P4
        path += LineTo(SHEET_ARROW_HEIGHT.ConvertToPx(),
            arrowOffset_.GetY() - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx());    // P5
    }
    return path + "Z";
}

void SheetPresentationPattern::RecoverHalfFoldOrAvoidStatus()
{
    TAG_LOGD(AceLogTag::ACE_SHEET, "recover half fold status because of window rotate");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (IsCurSheetNeedHalfFoldHover()) {
        RecoverAvoidKeyboardStatus();
    } else {
        AvoidSafeArea(true);
    }
}

void SheetPresentationPattern::RecoverAvoidKeyboardStatus()
{
    RecoverScrollOrResizeAvoidStatus();
    sheetHeightUp_ = 0.f;
    OnHeightDidChange(centerHeight_);
}

void SheetPresentationPattern::RecoverScrollOrResizeAvoidStatus()
{
    auto scroll = GetSheetScrollNode();
    CHECK_NULL_VOID(scroll);
    auto layoutProp = scroll->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    layoutProp->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(GetScrollHeight())));
    resizeDecreasedHeight_ = 0.f;
    scrollHeight_ = 0.f;
    ScrollTo(0.f);
    isScrolling_ = false;
}

void SheetPresentationPattern::OnWillDisappear()
{
    if (onWillDisappear_) {
        TAG_LOGI(AceLogTag::ACE_SHEET, "bindsheet lifecycle change to onWillDisappear state.");
        onWillDisappear_();
    }
    auto hostNode = GetHost();
    CHECK_NULL_VOID(hostNode);
    auto pipelineContext = hostNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto navigationManager = pipelineContext->GetNavigationManager();
    CHECK_NULL_VOID(navigationManager);
    navigationManager->FireOverlayLifecycle(hostNode, static_cast<int32_t>(NavDestinationLifecycle::ON_INACTIVE),
        static_cast<int32_t>(NavDestinationActiveReason::SHEET));
}

void SheetPresentationPattern::OnFontScaleConfigurationUpdate()
{
    auto hostNode = GetHost();
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterReloadAnimationTask([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->AvoidSafeArea(true);
    });
}

void SheetPresentationPattern::OnAvoidInfoChange(const ContainerModalAvoidInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SheetPresentationPattern::RegisterAvoidInfoChangeListener(const RefPtr<FrameNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto mgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_VOID(mgr);
    mgr->AddAvoidInfoListener(WeakClaim(this));
}

void SheetPresentationPattern::UnRegisterAvoidInfoChangeListener(FrameNode* hostNode)
{
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto mgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_VOID(mgr);
    mgr->RemoveAvoidInfoListener(WeakClaim(this));
}
} // namespace OHOS::Ace::NG
