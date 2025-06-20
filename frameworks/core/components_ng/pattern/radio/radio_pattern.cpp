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

#include "core/components_ng/pattern/radio/radio_pattern.h"

#include "base/log/dump_log.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int FOR_HOTZONESIZE_CALCULATE_MULTIPLY_TWO = 2;
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;

constexpr int32_t DEFAULT_RADIO_ANIMATION_DURATION = 200;
constexpr int32_t DEFAULT_RADIO_ANIMATION_DURATION_CIRCLE = 150;
constexpr float DEFAULT_CUSTOM_SCALE = 0.7F;
constexpr float INDICATOR_MIN_SCALE = 0.8F;
constexpr float INDICATOR_MAX_SCALE = 1.0F;
constexpr float INDICATOR_MIN_OPACITY = 0.0F;
constexpr float INDICATOR_MAX_OPACITY = 1.0F;
constexpr int32_t RADIO_PADDING_COUNT = 2;

constexpr float DEFAULT_INTERPOLATINGSPRING_VELOCITY = 0.0f;
constexpr float DEFAULT_INTERPOLATINGSPRING_MASS = 1.0f;
constexpr float DEFAULT_INTERPOLATINGSPRING_STIFFNESS = 728.0f;
constexpr float DEFAULT_INTERPOLATINGSPRING_DAMPING = 46.0f;

} // namespace

void RadioPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
}

void RadioPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    auto radioEventHub = frameNode->GetOrCreateEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(radioEventHub);
    groupManager->RemoveRadioFromGroup(radioEventHub->GetGroup(), frameNode->GetId());
}

void RadioPattern::SetBuilderState()
{
    CHECK_NULL_VOID(builderChildNode_);
    auto renderContext = builderChildNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateOpacity(0);
    auto layoutProperty = builderChildNode_->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::GONE);
}

void RadioPattern::UpdateIndicatorType()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto radioPaintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(radioPaintProperty);
    auto radioIndicatorType = radioPaintProperty->GetRadioIndicator().value_or(0);
    if (radioIndicatorType == static_cast<int32_t>(RadioIndicatorType::CUSTOM)) {
        LoadBuilder();
    } else {
        ImageNodeCreate();
    }
    CHECK_NULL_VOID(builderChildNode_);
    auto renderContext = builderChildNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformScale({ INDICATOR_MAX_SCALE, INDICATOR_MAX_SCALE });
    renderContext->UpdateOpacity(1);
    if (!radioModifier_) {
        radioModifier_ = AceType::MakeRefPtr<RadioModifier>();
    }
    if (!radioPaintProperty->HasRadioCheck()) {
        radioPaintProperty->UpdateRadioCheck(false);
    }
    if (!radioPaintProperty->GetRadioCheckValue()) {
        radioModifier_->InitOpacityScale(false);
        SetBuilderState();
    }
}

void RadioPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    FireBuilder();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!makeFunc_.has_value() && host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        UpdateIndicatorType();
    }
    UpdateState();
    auto* pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    hotZoneHorizontalPadding_ = radioTheme->GetHotZoneHorizontalPadding();
    hotZoneVerticalPadding_ = radioTheme->GetHotZoneVerticalPadding();
    InitDefaultMargin();
    HandleEnabled();
    InitClickEvent();
    InitTouchEvent();
    InitMouseEvent();
    InitFocusEvent();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
    SetAccessibilityAction();
}

void RadioPattern::InitDefaultMargin()
{
    if (makeFunc_.has_value()) {
        ResetDefaultMargin();
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    MarginProperty margin;
    margin.left = CalcLength(hotZoneHorizontalPadding_.Value());
    margin.right = CalcLength(hotZoneHorizontalPadding_.Value());
    margin.top = CalcLength(hotZoneVerticalPadding_.Value());
    margin.bottom = CalcLength(hotZoneVerticalPadding_.Value());
    auto& setMargin = layoutProperty->GetMarginProperty();
    if (setMargin) {
        if (setMargin->left.has_value()) {
            margin.left = setMargin->left;
        }
        if (setMargin->right.has_value()) {
            margin.right = setMargin->right;
        }
        if (setMargin->top.has_value()) {
            margin.top = setMargin->top;
        }
        if (setMargin->bottom.has_value()) {
            margin.bottom = setMargin->bottom;
        }
    }
    layoutProperty->UpdateMargin(margin);
}

void RadioPattern::ResetDefaultMargin()
{
    if (isUserSetMargin_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    MarginProperty margin;
    layoutProperty->UpdateMargin(margin);
}

void RadioPattern::InitFocusEvent()
{
    if (focusEventInitialized_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto focusTask = [weak = WeakClaim(this)](FocusReason reason) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
    focusEventInitialized_ = true;
}

void RadioPattern::HandleFocusEvent()
{
    CHECK_NULL_VOID(radioModifier_);
    AddIsFocusActiveUpdateEvent();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetIsFocusActive()) {
        OnIsFocusActiveUpdate(true);
    }
}

void RadioPattern::HandleBlurEvent()
{
    CHECK_NULL_VOID(radioModifier_);
    RemoveIsFocusActiveUpdateEvent();
    OnIsFocusActiveUpdate(false);
}

void RadioPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusAcitve) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnIsFocusActiveUpdate(isFocusAcitve);
        };
    }

    auto pipline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipline);
    pipline->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void RadioPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto pipline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipline);
    pipline->RemoveIsFocusActiveUpdateEvent(GetHost());
}

void RadioPattern::OnIsFocusActiveUpdate(bool isFocusAcitve)
{
    CHECK_NULL_VOID(radioModifier_);
    radioModifier_->SetIsFocused(isFocusAcitve);
}

void RadioPattern::ImageNodeCreate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childNode = DynamicCast<FrameNode>(host->GetFirstChild());
    if (preTypeIsBuilder_) {
        host->RemoveChild(childNode);
    }
    if (!childNode || preTypeIsBuilder_) {
        auto node = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        CHECK_NULL_VOID(node);
        builderChildNode_ = AceType::DynamicCast<FrameNode>(node);
        CHECK_NULL_VOID(builderChildNode_);
        auto gesturehub = builderChildNode_->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gesturehub);
        gesturehub->SetHitTestMode(HitTestMode::HTMNONE);
    }
    CHECK_NULL_VOID(builderChildNode_);
    auto radioPaintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(radioPaintProperty);
    auto imageProperty = builderChildNode_->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageProperty);
    imageProperty->UpdateUserDefinedIdealSize(GetChildContentSize());
    auto imageSourceInfo = GetImageSourceInfoFromTheme(radioPaintProperty->GetRadioIndicator().value_or(0));
    UpdateInternalResource(imageSourceInfo);
    auto* pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    auto indicatorColor = radioPaintProperty->GetRadioIndicatorColor().value_or(Color(radioTheme->GetPointColor()));
    auto imageRenderProperty = builderChildNode_->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    imageRenderProperty->UpdateSvgFillColor(indicatorColor);
    imageProperty->UpdateImageSourceInfo(imageSourceInfo);
    preTypeIsBuilder_ = false;
    builderChildNode_->MountToParent(host);
    builderChildNode_->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void RadioPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSelect([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateSelectStatus(true);
    });

    accessibilityProperty->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateSelectStatus(false);
    });
}

void RadioPattern::UpdateSelectStatus(bool isSelected)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "radio node %{public}d update status %d", host->GetId(), isSelected);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    MarkIsSelected(isSelected);
    context->OnMouseSelectUpdate(isSelected, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
}

void RadioPattern::MarkIsSelected(bool isSelected)
{
    if (preCheck_ == isSelected) {
        return;
    }
    preCheck_ = isSelected;
    auto eventHub = GetOrCreateEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateChangeEvent(isSelected);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "radio node %{public}d fire change event %{public}d", host->GetId(),
        isSelected);
    if (isSelected) {
        eventHub->UpdateCurrentUIState(UI_STATE_SELECTED);
        host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);
    } else {
        eventHub->ResetCurrentUIState(UI_STATE_SELECTED);
        host->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
    }
}

void RadioPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (inspectorId.empty()) {
        return;
    }
    auto eventHub = host->GetOrCreateEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    Recorder::NodeDataCache::Get().PutMultiple(host, inspectorId, eventHub->GetValue(), preCheck_);
}

void RadioPattern::InitClickEvent()
{
    if (clickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto radioPattern = weak.Upgrade();
        CHECK_NULL_VOID(radioPattern);
        radioPattern->OnClick();
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void RadioPattern::InitTouchEvent()
{
    if (UseContentModifier()) {
        return;
    }
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto radioPattern = weak.Upgrade();
        CHECK_NULL_VOID(radioPattern);
        if (info.GetTouches().empty()) {
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            radioPattern->OnTouchDown();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            radioPattern->OnTouchUp();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void RadioPattern::InitMouseEvent()
{
    if (UseContentModifier()) {
        return;
    }
    if (mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto eventHub = host->GetOrCreateEventHub<RadioEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(isHover);
        }
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent_);
}

void RadioPattern::HandleMouseEvent(bool isHover)
{
    if (UseContentModifier()) {
        return;
    }
    isHover_ = isHover;
    if (isHover) {
        touchHoverType_ = TouchHoverAnimationType::HOVER;
    } else {
        touchHoverType_ = TouchHoverAnimationType::NONE;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGD(
        AceLogTag::ACE_SELECT_COMPONENT, "radio node %{public}d handle mouse hover %{public}d", host->GetId(), isHover);
    host->MarkNeedRenderOnly();
}

void RadioPattern::OnClick()
{
    if (UseContentModifier()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "radio node %{public}d handle click event", host->GetId());
    auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool check = false;
    if (paintProperty->HasRadioCheck()) {
        check = paintProperty->GetRadioCheckValue();
    } else {
        paintProperty->UpdateRadioCheck(false);
    }
    if (!preCheck_ && !check) {
        paintProperty->UpdateRadioCheck(true);
        UpdateState();
    }
}

void RadioPattern::OnTouchDown()
{
    if (UseContentModifier()) {
        return;
    }
    if (isHover_) {
        touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    } else {
        touchHoverType_ = TouchHoverAnimationType::PRESS;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "radio node %{public}d onTouch Down", host->GetId());
    isTouch_ = true;
    host->MarkNeedRenderOnly();
}

void RadioPattern::OnTouchUp()
{
    if (UseContentModifier()) {
        return;
    }
    if (isHover_) {
        touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    } else {
        touchHoverType_ = TouchHoverAnimationType::NONE;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "radio node %{public}d onTouch Up", host->GetId());
    isTouch_ = false;
    host->MarkNeedRenderOnly();
}

void RadioPattern::CheckPageNode()
{
    if (Container::IsInSubContainer()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto prePageId = GetPrePageId();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetPageById(host->GetPageId());
    CHECK_NULL_VOID(pageNode);
    if (pageNode->GetId() != prePageId) {
        auto eventHub = host->GetOrCreateEventHub<RadioEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto groupManager = GetGroupManager();
        CHECK_NULL_VOID(groupManager);
        auto group = eventHub->GetGroup();
        groupManager->AddRadioToGroup(group, host->GetId());
        auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        bool check = false;
        if (paintProperty->HasRadioCheck()) {
            check = paintProperty->GetRadioCheckValue();
        }
        UpdateGroupCheckStatus(host, groupManager, check);
    }
}

void RadioPattern::UpdateState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto groupManager = GetGroupManager();
    CHECK_NULL_VOID(groupManager);
    auto preGroup = GetPreGroup();
    auto group = eventHub->GetGroup();
    if (!preGroup.has_value()) {
        groupManager->AddRadioToGroup(group, host->GetId());
        SetPrePageIdToLastPageId();
        auto callback = [weak = WeakClaim(this)]() {
            auto radio = weak.Upgrade();
            if (radio) {
                radio->CheckPageNode();
            }
        };
        pipelineContext->AddBuildFinishCallBack(callback);
    }
    if (preGroup.has_value() && preGroup.value() != group) {
        groupManager->RemoveRadioFromGroup(preGroup.value(), host->GetId());
        groupManager->AddRadioToGroup(group, host->GetId());
        SetPrePageIdToLastPageId();
        isGroupChanged_ = true;
    }
    SetPreGroup(group);

    auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    bool check = false;
    if (paintProperty->HasRadioCheck()) {
        check = paintProperty->GetRadioCheckValue();
        /*
         * Do not set isFirstCreated_ to false if the radio is set to true at creation time. The isFirstCreated_ is set
         * to false in UpdateGroupCheckStatus because isFirstCreated_ is also required to determine if an onChange event
         * needs to be triggered.
         */
        if (check) {
            UpdateUIStatus(true);
            isOnAnimationFlag_ = true;
        } else {
            // If the radio is set to false, set isFirstCreated_ to false.
            isFirstCreated_ = false;
        }
    } else {
        paintProperty->UpdateRadioCheck(false);
        // If the radio check is not set, set isFirstCreated_ to false.
        isFirstCreated_ = false;
    }
    if (preCheck_ != check || isGroupChanged_) {
        UpdateGroupCheckStatus(host, groupManager, check);
    }
    preCheck_ = check;
    isGroupChanged_ = false;
}

void RadioPattern::UpdateUncheckStatus(const RefPtr<FrameNode>& frameNode)
{
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(radioPaintProperty);
    if (radioPaintProperty->GetRadioCheckValue(false)) {
        radioPaintProperty->UpdateRadioCheck(false);
        FireBuilder();
    }
    frameNode->MarkNeedRenderOnly();
    if (frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        startExitAnimation();
    }
    if (preCheck_) {
        auto radioEventHub = GetOrCreateEventHub<RadioEventHub>();
        CHECK_NULL_VOID(radioEventHub);
        TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "radio node %{public}d fire unselect event", frameNode->GetId());
        radioEventHub->UpdateChangeEvent(false);
        isOnAnimationFlag_ = false;
    }
    preCheck_ = false;
}

void RadioPattern::startEnterAnimation()
{
    auto springCurve = AceType::MakeRefPtr<InterpolatingSpring>(DEFAULT_INTERPOLATINGSPRING_VELOCITY,
        DEFAULT_INTERPOLATINGSPRING_MASS, DEFAULT_INTERPOLATINGSPRING_STIFFNESS, DEFAULT_INTERPOLATINGSPRING_DAMPING);
    AnimationOption delayOption;

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    if (radioTheme->IsCircleDial()) {
        delayOption.SetCurve(Curves::FAST_OUT_SLOW_IN);
        delayOption.SetDelay(DEFAULT_RADIO_ANIMATION_DURATION_CIRCLE);
    } else {
        delayOption.SetCurve(springCurve);
        delayOption.SetDelay(DEFAULT_RADIO_ANIMATION_DURATION);
    }

    CHECK_NULL_VOID(builderChildNode_);
    auto renderContext = builderChildNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateOpacity(INDICATOR_MIN_OPACITY);
    renderContext->UpdateTransformScale({ INDICATOR_MIN_SCALE, INDICATOR_MIN_SCALE });
    auto layoutProperty = builderChildNode_->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    auto eventHub = builderChildNode_->GetOrCreateEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(true);
    }
    AnimationUtils::Animate(
        delayOption,
        [&]() {
            renderContext->UpdateTransformScale({ INDICATOR_MAX_SCALE, INDICATOR_MAX_SCALE });
            renderContext->UpdateOpacity(INDICATOR_MAX_OPACITY);
        },
        nullptr);
}

void RadioPattern::startExitAnimation()
{
    auto springCurve = AceType::MakeRefPtr<InterpolatingSpring>(DEFAULT_INTERPOLATINGSPRING_VELOCITY,
        DEFAULT_INTERPOLATINGSPRING_MASS, DEFAULT_INTERPOLATINGSPRING_STIFFNESS, DEFAULT_INTERPOLATINGSPRING_DAMPING);
    AnimationOption delayOption;

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    if (radioTheme->IsCircleDial()) {
        delayOption.SetCurve(Curves::FAST_OUT_SLOW_IN);
        delayOption.SetDelay(DEFAULT_RADIO_ANIMATION_DURATION_CIRCLE);
    } else {
        delayOption.SetCurve(springCurve);
    }

    CHECK_NULL_VOID(builderChildNode_);
    auto renderContext = builderChildNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationUtils::Animate(
        delayOption,
        [&]() {
            renderContext->UpdateTransformScale({ INDICATOR_MIN_SCALE, INDICATOR_MIN_SCALE });
            renderContext->UpdateOpacity(INDICATOR_MIN_OPACITY);
        },
        nullptr);
    auto eventHub = builderChildNode_->GetOrCreateEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(false);
    }
}

ImageSourceInfo RadioPattern::GetImageSourceInfoFromTheme(int32_t RadioIndicator)
{
    ImageSourceInfo imageSourceInfo;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, imageSourceInfo);
    auto* pipeline = host->GetContextWithCheck();
    CHECK_NULL_RETURN(pipeline, imageSourceInfo);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_RETURN(radioTheme, imageSourceInfo);
    switch (RadioIndicator) {
        case static_cast<int32_t>(RadioIndicatorType::TICK):
            imageSourceInfo.SetResourceId(radioTheme->GetTickResourceId());
            break;
        case static_cast<int32_t>(RadioIndicatorType::DOT):
            imageSourceInfo.SetResourceId(radioTheme->GetDotResourceId());
            break;
        default:
            imageSourceInfo.SetResourceId(radioTheme->GetTickResourceId());
            break;
    }
    return imageSourceInfo;
}

void RadioPattern::UpdateInternalResource(ImageSourceInfo& sourceInfo)
{
    CHECK_NULL_VOID(sourceInfo.IsInternalResource());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto* pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    auto iconPath = iconTheme->GetIconPath(sourceInfo.GetResourceId());
    if (iconPath.empty()) {
        return;
    }
    sourceInfo.SetSrc(iconPath);
}

void RadioPattern::LoadBuilder()
{
    RefPtr<UINode> customNode;
    if (builder_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto childNode = DynamicCast<FrameNode>(host->GetFirstChild());
        if (preTypeIsBuilder_) {
            return;
        } else {
            if (childNode) {
                host->RemoveChild(childNode);
            }
        }
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        builder_();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_VOID(customNode);
        builderChildNode_ = AceType::DynamicCast<FrameNode>(customNode);
        CHECK_NULL_VOID(builderChildNode_);
        preTypeIsBuilder_ = true;
        builderChildNode_->MountToParent(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void RadioPattern::InitializeParam(
    Dimension& defaultWidth, Dimension& defaultHeight, Dimension& horizontalPadding, Dimension& verticalPadding)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto* pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    defaultWidth = radioTheme->GetWidth();
    defaultHeight = radioTheme->GetHeight();
    horizontalPadding = radioTheme->GetDefaultPaddingSize();
    verticalPadding = radioTheme->GetDefaultPaddingSize();
}

CalcSize RadioPattern::GetChildContentSize()
{
    auto host = GetHost();
    auto layoutProperty = host->GetLayoutProperty<LayoutProperty>();
    auto &&layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (layoutConstraint && layoutConstraint->selfIdealSize) {
        auto selfIdealSize = layoutConstraint->selfIdealSize;
        if (selfIdealSize->IsValid()) {
            auto height = selfIdealSize->Height()->GetDimension() * DEFAULT_CUSTOM_SCALE;
            auto width = selfIdealSize->Width()->GetDimension() * DEFAULT_CUSTOM_SCALE;
            auto length = std::min(width, height);
            return CalcSize(NG::CalcLength(length), NG::CalcLength(length));
        }
        if (selfIdealSize->Width().has_value()) {
            auto width = selfIdealSize->Width()->GetDimension() * DEFAULT_CUSTOM_SCALE;
            return CalcSize(NG::CalcLength(width), NG::CalcLength(width));
        }
        if (selfIdealSize->Height().has_value()) {
            auto height = selfIdealSize->Height()->GetDimension() * DEFAULT_CUSTOM_SCALE;
            return CalcSize(NG::CalcLength(height), NG::CalcLength(height));
        }
    }
    Dimension defaultWidth;
    Dimension defaultHeight;
    Dimension horizontalPadding;
    Dimension verticalPadding;
    InitializeParam(defaultWidth, defaultHeight, horizontalPadding, verticalPadding);
    auto width = (defaultWidth - horizontalPadding * RADIO_PADDING_COUNT) * DEFAULT_CUSTOM_SCALE;
    auto height = (defaultHeight - verticalPadding * RADIO_PADDING_COUNT) * DEFAULT_CUSTOM_SCALE;
    return CalcSize(NG::CalcLength(width), NG::CalcLength(height));
}

void RadioPattern::UpdateGroupCheckStatus(
    const RefPtr<FrameNode>& frameNode, const RefPtr<GroupManager>& groupManager, bool check)
{
    frameNode->MarkNeedRenderOnly();
    if (frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        if (!isFirstCreated_ && check) {
            startEnterAnimation();
        }
    }

    auto radioEventHub = GetOrCreateEventHub<RadioEventHub>();
    CHECK_NULL_VOID(radioEventHub);
    if (check) {
        groupManager->UpdateRadioGroupValue(radioEventHub->GetGroup(), frameNode->GetId());
    } else {
        auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
        CHECK_NULL_VOID(radioPaintProperty);
        radioPaintProperty->UpdateRadioCheck(check);
        if (!isGroupChanged_) {
            isOnAnimationFlag_ = false;
        }
    }

    if (!isFirstCreated_) {
        TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "radio node %{public}d fire group change event %{public}d",
            frameNode->GetId(), check);
        radioEventHub->UpdateChangeEvent(check);
    }
}

void RadioPattern::UpdateUIStatus(bool check)
{
    uiStatus_ = check ? UIStatus::SELECTED : UIStatus::UNSELECTED;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkNeedRenderOnly();
}

bool RadioPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action == KeyAction::DOWN && event.code == KeyCode::KEY_FUNCTION) {
        OnClick();
        return true;
    }
    return false;
}

void RadioPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);

    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
        } else {
            return false;
        }
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

void RadioPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto* pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    auto focusPaintPadding = radioTheme->GetFocusPaintPadding().ConvertToPx();
    float outCircleRadius = size_.Width() / 2 + focusPaintPadding;
    float originX = offset_.GetX() - focusPaintPadding;
    float originY = offset_.GetY() - focusPaintPadding;
    float width = size_.Width() + 2 * focusPaintPadding;
    float height = size_.Height() + 2 * focusPaintPadding;
    paintRect.SetRect({ originX, originY, width, height });
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, outCircleRadius, outCircleRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, outCircleRadius, outCircleRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, outCircleRadius, outCircleRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, outCircleRadius, outCircleRadius);
}

FocusPattern RadioPattern::GetFocusPattern() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, FocusPattern());
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, FocusPattern());
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_RETURN(radioTheme, FocusPattern());
    FocusPaintParam focusPaintParam;
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto focusColor = radioTheme->GetFocusColor();
        focusPaintParam.SetPaintColor(focusColor);
    } else {
        auto activeColor = radioTheme->GetActiveColor();
        focusPaintParam.SetPaintColor(activeColor);
    }
    return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION, focusPaintParam };
}

bool RadioPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& /*config*/)
{
    auto geometryNode = dirty->GetGeometryNode();
    offset_ = geometryNode->GetContentOffset();
    size_ = geometryNode->GetContentSize();
    if (!isUserSetResponseRegion_) {
        AddHotZoneRect();
    }
    return true;
}

// Set the default hot zone for the component.
void RadioPattern::AddHotZoneRect()
{
    hotZoneOffset_.SetX(offset_.GetX() - hotZoneHorizontalPadding_.ConvertToPx());
    hotZoneOffset_.SetY(offset_.GetY() - hotZoneVerticalPadding_.ConvertToPx());
    hotZoneSize_.SetWidth(
        size_.Width() + FOR_HOTZONESIZE_CALCULATE_MULTIPLY_TWO * hotZoneHorizontalPadding_.ConvertToPx());
    hotZoneSize_.SetHeight(
        size_.Height() + FOR_HOTZONESIZE_CALCULATE_MULTIPLY_TWO * hotZoneVerticalPadding_.ConvertToPx());
    DimensionRect hotZoneRegion;
    hotZoneRegion.SetSize(DimensionSize(Dimension(hotZoneSize_.Width()), Dimension(hotZoneSize_.Height())));
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(hotZoneOffset_.GetX()), Dimension(hotZoneOffset_.GetY())));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetResponseRegion(std::vector<DimensionRect>({ hotZoneRegion }));
}

void RadioPattern::RemoveLastHotZoneRect() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveLastHotZoneRect();
}

std::string RadioPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    auto radioPaintProperty = GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_RETURN(radioPaintProperty, "");
    jsonObj->Put("checked", radioPaintProperty->GetRadioCheck().value_or(false));
    return jsonObj->ToString();
}

void RadioPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto radioPaintProperty = GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(radioPaintProperty);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonChecked = info->GetValue("checked");
    radioPaintProperty->UpdateRadioCheck(jsonChecked->GetBool());
    OnModifyDone();
}

void RadioPattern::HandleEnabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto radioPaintProperty = GetHost()->GetPaintProperty<RadioPaintProperty>();
    if (enabled_ != enabled) {
        enabled_ = enabled;
        if (!enabled_ && host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            if (!radioModifier_) {
                radioModifier_ = AceType::MakeRefPtr<RadioModifier>();
            }
            if (!radioPaintProperty->HasRadioCheck() || !radioPaintProperty->GetRadioCheckValue()) {
                radioModifier_->SetUIStatus(UIStatus::UNSELECTED);
            }
        }
        auto paintProperty = GetPaintProperty<RadioPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        paintProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
    }
}

void RadioPattern::SetRadioChecked(bool check)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    if (!enabled) {
        return;
    }
    auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateRadioCheck(check);
    UpdateState();
    OnModifyDone();
}

void RadioPattern::DumpInfo ()
{
    auto eventHub = GetOrCreateEventHub<RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    DumpLog::GetInstance().AddDesc("Value: " + eventHub->GetValue());
    DumpLog::GetInstance().AddDesc("Group: " + eventHub->GetGroup());

    auto paintProperty = GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->HasRadioIndicator()) {
        DumpLog::GetInstance().AddDesc("IndicatorType: " + std::to_string(paintProperty->GetRadioIndicatorValue()));
    }
    if (paintProperty->HasRadioCheck()) {
        DumpLog::GetInstance().AddDesc(
            "IsChecked: " + std::string(paintProperty->GetRadioCheckValue() ? "true" : "false"));
    }
    if (paintProperty->HasRadioCheckedBackgroundColor()) {
        DumpLog::GetInstance().AddDesc(
            "CheckedBackgroundColor: " + paintProperty->GetRadioCheckedBackgroundColorValue().ToString());
    }
    if (paintProperty->HasRadioUncheckedBorderColor()) {
        DumpLog::GetInstance().AddDesc(
            "UncheckedBorderColor: " + paintProperty->GetRadioUncheckedBorderColorValue().ToString());
    }
    if (paintProperty->HasRadioIndicatorColor()) {
        DumpLog::GetInstance().AddDesc("IndicatorColor: " + paintProperty->GetRadioIndicatorColorValue().ToString());
    }
}

void RadioPattern::UpdateRadioComponentColor(const Color& color, const RadioColorType radioColorType)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto paintProperty = GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    switch (radioColorType) {
        case RadioColorType::CHECKED_BACKGROUND_COLOR:
            paintProperty->UpdateRadioCheckedBackgroundColor(color);
            break;
        case RadioColorType::UNCHECKED_BORDER_COLOR:
            paintProperty->UpdateRadioUncheckedBorderColor(color);
            break;
        case RadioColorType::INDICATOR_COLOR:
            paintProperty->UpdateRadioIndicatorColor(color);
            ImageNodeCreate();
            break;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RadioPattern::FireBuilder()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!makeFunc_.has_value()) {
        host->RemoveChildAndReturnIndex(customNode_);
        customNode_ = nullptr;
        host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto node = BuildContentModifierNode();
    if (customNode_ == node) {
        return;
    }
    host->RemoveChildAndReturnIndex(customNode_);
    customNode_ = node;
    CHECK_NULL_VOID(customNode_);
    host->AddChild(customNode_, 0);
    host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> RadioPattern::BuildContentModifierNode()
{
    CHECK_NULL_RETURN(makeFunc_, nullptr);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto eventHub = host->GetOrCreateEventHub<RadioEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto value = eventHub->GetValue();
    auto enabled = eventHub->IsEnabled();
    auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    bool isChecked = false;
    if (paintProperty->HasRadioCheck()) {
        isChecked = paintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    RadioConfiguration radioConfiguration(value, isChecked, enabled);
    return (makeFunc_.value())(radioConfiguration);
}

RefPtr<GroupManager> RadioPattern::GetGroupManager()
{
    auto manager = groupManager_.Upgrade();
    if (manager) {
        return manager;
    }
    groupManager_ = GroupManager::GetGroupManager();
    return groupManager_.Upgrade();
}

void RadioPattern::SetPrePageIdToLastPageId()
{
    if (!Container::IsInSubContainer()) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto stageManager = pipelineContext->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto pageNode = stageManager->GetLastPage();
        CHECK_NULL_VOID(pageNode);
        SetPrePageId(pageNode->GetId());
    }
}

void RadioPattern::OnColorConfigurationUpdate()
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<RadioPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_VOID(radioTheme);
    if (!paintProperty->GetRadioCheckedBackgroundColorSetByUser().value_or(false)) {
        auto activeColor = radioTheme->GetActiveColor();
        paintProperty->UpdateRadioCheckedBackgroundColor(activeColor);
    }
    if (!paintProperty->GetRadioUncheckedBorderColorSetByUser().value_or(false)) {
        auto inActiveColor = radioTheme->GetInactiveColor();
        paintProperty->UpdateRadioUncheckedBorderColor(inActiveColor);
    }
    if (!paintProperty->GetRadioIndicatorColorSetByUser().value_or(false)) {
        auto pointColor = radioTheme->GetPointColor();
        paintProperty->UpdateRadioIndicatorColor(pointColor);
        ImageNodeCreate();
    }
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}
} // namespace OHOS::Ace::NG
