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

#include "base/utils/multi_thread.h"
#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"

#include "core/components/marquee/marquee_theme.h"
#include "core/components_ng/pattern/text/text_layout_adapter.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DEFAULT_MARQUEE_SCROLL_DELAY = 85.0; // Delay time between each jump.
constexpr float HALF = 0.5f;
inline constexpr int32_t DEFAULT_MARQUEE_LOOP = -1;
} // namespace

void MarqueePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    THREAD_SAFE_NODE_CHECK(host, OnAttachToFrameNode);  // call OnAttachToFrameNodeMultiThread() by multi thread
    host->GetRenderContext()->SetUsingContentRectForRenderFrame(true);
    host->GetRenderContext()->SetClipToFrame(true);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowSizeChangeCallback(host->GetId());
    pipeline->AddWindowStateChangedCallback(host->GetId());
    ProcessVisibleAreaCallback();
}

void MarqueePattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    THREAD_SAFE_NODE_CHECK(frameNode, OnDetachFromFrameNode,
        frameNode);  // call OnDetachFromFrameNodeMultiThread() by multi thread
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowSizeChangeCallback(frameNode->GetId());
    pipeline->RemoveWindowStateChangedCallback(frameNode->GetId());
    pipeline->RemoveVisibleAreaChangeNode(frameNode->GetId());
}

void MarqueePattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // call OnAttachToMainTreeMultiThread() by multi thread Pattern::OnAttachToMainTree()
    THREAD_SAFE_NODE_CHECK(host, OnAttachToMainTree);
}

void MarqueePattern::OnDetachFromMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // call OnDetachFromMainTreeMultiThread() by multi thread Pattern::OnDetachFromMainTree()
    THREAD_SAFE_NODE_CHECK(host, OnDetachFromMainTree);
}

MarqueePattern::~MarqueePattern()
{
    CHECK_NULL_VOID(animation_);
    AnimationUtils::StopAnimation(animation_);
}

void MarqueePattern::OnWindowHide()
{
    if (!playStatus_) {
        return;
    }
    PauseAnimation();
}

void MarqueePattern::OnWindowShow()
{
    if (playStatus_) {
        return;
    }
    ResumeAnimation();
}

bool MarqueePattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& /* dirty */, const DirtySwapConfig& /* config */)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geoNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geoNode, false);
    auto marqueeWidth = geoNode->GetFrameSize().Width();
    if (measureChanged_ || marqueeWidth_ != marqueeWidth) {
        measureChanged_ = false;
        auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
        CHECK_NULL_RETURN(paintProperty, false);
        auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
        StopMarqueeAnimation(playStatus);
    }
    marqueeWidth_ = marqueeWidth;
    return false;
}

void MarqueePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto textChild = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textChild);
    auto childRenderContext = textChild->GetRenderContext();
    CHECK_NULL_VOID(childRenderContext);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    UpdateTextDirection(layoutProperty, textLayoutProperty);
    auto gestureHub = textChild->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetHitTestMode(HitTestMode::HTMNONE);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    auto fontSize = layoutProperty->GetFontSize().value_or(theme->GetTextStyle().GetFontSize());
    textLayoutProperty->UpdateFontSize(fontSize);
    textLayoutProperty->UpdateFontWeight(layoutProperty->GetFontWeight().value_or(FontWeight::NORMAL));
    if (layoutProperty->GetFontFamily().has_value()) {
        textLayoutProperty->UpdateFontFamily(layoutProperty->GetFontFamily().value());
    } else {
        textLayoutProperty->ResetFontFamily();
    }
    textLayoutProperty->UpdateTextColor(layoutProperty->GetFontColor().value_or(theme->GetTextStyle().GetTextColor()));
    textChild->MarkModifyDone();
    childRenderContext->UpdateClipEdge(true);
    childRenderContext->SetClipToFrame(true);
    if (CheckMeasureFlag(layoutProperty->GetPropertyChangeFlag()) ||
        CheckLayoutFlag(layoutProperty->GetPropertyChangeFlag())) {
        measureChanged_ = true;
    } else if (OnlyPlayStatusChange()) {
        ChangeAnimationPlayStatus();
    } else {
        auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
        StopMarqueeAnimation(playStatus);
    }
    StoreProperties();
}

void MarqueePattern::StartMarqueeAnimation()
{
    TAG_LOGD(AceLogTag::ACE_MARQUEE, "Start Marquee Animation.");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!IsRunMarquee()) {
        UpdateTextTranslateXY(0.0f);
        StopAndResetAnimation();
        return;
    }
    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto repeatCount = paintProperty->GetLoop().value_or(DEFAULT_MARQUEE_LOOP);
    if (pipeline->IsFormRenderExceptDynamicComponent()) {
        repeatCount = 1;
    }
    FireStartEvent();
    bool needSecondPlay = repeatCount != 1;
    auto startPosition = GetTextOffset();
    PlayMarqueeAnimation(startPosition, repeatCount, needSecondPlay);
}

void MarqueePattern::PlayMarqueeAnimation(float start, int32_t playCount, bool needSecondPlay, bool isFirst)
{
    TAG_LOGD(AceLogTag::ACE_MARQUEE,
        "Play Marquee Animation, startPosition is %{public}f, playCount is %{public}d, needSecondPlay is true ? "
        "%{public}d.",
        start, playCount, needSecondPlay);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto textWidth = GetTextNodeWidth();
    auto step = GetScrollAmount();
    if (GreatNotEqual(step, textWidth)) {
        step = DEFAULT_MARQUEE_SCROLL_AMOUNT.ConvertToPx();
    }
    float calculateEnd = CalculateEnd();
    float calculateStart = CalculateStart();
    auto direction = GetCurrentTextDirection();
    bool isRtl = direction == TextDirection::RTL ? true : false;
    if (isRtl) {
        std::swap(calculateEnd, calculateStart);
    }

    calculateStart = isFirst ? start : calculateStart;
    auto duration = static_cast<int32_t>(std::abs(calculateEnd - calculateStart) * DEFAULT_MARQUEE_SCROLL_DELAY);
    if (GreatNotEqual(step, 0.0)) {
        duration = static_cast<int32_t>(duration / step);
    }
    AnimationOption option;
    auto iter = frameRateRange_.find(MarqueeDynamicSyncSceneType::ANIMATE);
    if (iter != frameRateRange_.end()) {
        option.SetFrameRateRange(iter->second);
    }
    option.SetCurve(Curves::LINEAR);
    option.SetDuration(duration);
    needSecondPlay ? option.SetIteration(1) : option.SetIteration(playCount);
    TAG_LOGD(AceLogTag::ACE_MARQUEE,
        "Play Marquee Animation, marqueeNodeId is %{public}d, textNodeId is %{public}d, textWidth is %{public}f, "
        "duration is %{public}d.",
        host->GetId(), textNode->GetId(), textWidth, duration);
    UpdateTextTranslateXY(calculateStart);
    ActionAnimation(option, calculateEnd, playCount, needSecondPlay);
}

void MarqueePattern::ActionAnimation(AnimationOption& option, float end, int32_t playCount, bool needSecondPlay)
{
    animationId_++;
    animation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), end]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateTextTranslateXY(end);
        },
        [weak = AceType::WeakClaim(this), animationId = animationId_, needSecondPlay, playCount,
            id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto taskExecutor = Container::CurrentTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            auto onFinish = [weak, needSecondPlay, playCount, animationId]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (animationId != pattern->animationId_) {
                    return;
                }
                if (!needSecondPlay) {
                    pattern->OnAnimationFinish();
                    return;
                }
                auto newPlayCount = playCount > 0 ? playCount - 1 : playCount;
                if (newPlayCount == 0) {
                    return;
                }

                auto direction = pattern->GetCurrentTextDirection();
                auto newStart = direction == TextDirection::RTL ? pattern->CalculateEnd() : pattern->CalculateStart();
                pattern->PlayMarqueeAnimation(newStart, newPlayCount, false, false);
            };
            if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
                onFinish();
                return;
            }
            taskExecutor->PostTask(
                [onFinish]() { onFinish(); }, TaskExecutor::TaskType::UI, "ArkUIMarqueePlayAnimation");
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireBounceEvent();
        });
}

void MarqueePattern::OnAnimationFinish()
{
    FireFinishEvent();
    UpdateTextTranslateXY(0.0f);
}

void MarqueePattern::StopMarqueeAnimation(bool stopAndStart)
{
    TAG_LOGD(AceLogTag::ACE_MARQUEE, "Stop Marquee Animation.");
    animationId_++;
    if (animation_) {
        AnimationOption option;
        option.SetDuration(0);
        option.SetCurve(Curves::LINEAR);
        auto cancelAnimationCallbacl = [weak = WeakClaim(this)]() {
            auto marquee = weak.Upgrade();
            CHECK_NULL_VOID(marquee);
            // cancel translate for marquee.
            marquee->UpdateTextTranslateXY(0.0f, true);
        };
        AnimationUtils::OpenImplicitAnimation(option, Curves::LINEAR, nullptr);
        cancelAnimationCallbacl();
        bool isSyncSuc = AnimationUtils::CloseImplicitCancelAnimation();
        if (!isSyncSuc) {
            ACE_SCOPED_TRACE("Marquee stop property sync failed");
            //sync cancel animation filed, stop animation.
            StopAndResetAnimation();
        } else {
            PropertyCancelAnimationFinish();
            animation_.reset();
        }
    }
    if (stopAndStart) {
        StartMarqueeAnimation();
    }
}

void MarqueePattern::StopAndResetAnimation()
{
    lastAnimationOffset_ = std::nullopt;
    CHECK_NULL_VOID(animation_);
    AnimationUtils::StopAnimation(animation_);
    animation_.reset();
}

void MarqueePattern::PropertyCancelAnimationFinish()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto renderContext = textNode->GetRenderContext();
    lastAnimationOffset_ = renderContext->GetTranslateXYProperty();
}

void MarqueePattern::FireStartEvent() const
{
    auto marqueeEventHub = GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(marqueeEventHub);
    marqueeEventHub->FireStartEvent();
}

void MarqueePattern::FireBounceEvent() const
{
    auto marqueeEventHub = GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(marqueeEventHub);
    marqueeEventHub->FireBounceEvent();
}

void MarqueePattern::FireFinishEvent() const
{
    auto marqueeEventHub = GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(marqueeEventHub);
    marqueeEventHub->FireFinishEvent();
}

void MarqueePattern::UpdateTextTranslateXY(float offsetX, bool cancel)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    auto renderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    TAG_LOGD(AceLogTag::ACE_MARQUEE,
        "Marquee nodeId %{public}d, textNodeId %{public}d is setted text offsetX is %{public}f cancel: %{public}d.",
        host->GetId(), textNode->GetId(), offsetX, cancel);
    if (!cancel) {
        renderContext->UpdateTranslateInXY(OffsetF { offsetX, 0.0f });
    } else {
        renderContext->CancelTranslateXYAnimation();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

float MarqueePattern::GetTextOffset()
{
    float offsetX = 0.0f;
    if (!IsRunMarquee()) {
        return offsetX;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, offsetX);
    auto layoutProperty = host->GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, offsetX);
    auto marqueeUpdateStrategy = layoutProperty->GetMarqueeUpdateStrategy().value_or(MarqueeUpdateStrategy::DEFAULT);
    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, offsetX);
    auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
    if (playStatus && (marqueeUpdateStrategy == MarqueeUpdateStrategy::PRESERVE_POSITION) &&
        lastAnimationOffset_.has_value()) {
        offsetX = lastAnimationOffset_.value().GetX();
        lastAnimationOffset_ = std::nullopt;
    }
    return offsetX;
}

void MarqueePattern::OnVisibleChange(bool isVisible)
{
    if (isVisible) {
        CHECK_NULL_VOID(!playStatus_);
        ResumeAnimation();
    } else {
        CHECK_NULL_VOID(playStatus_);
        PauseAnimation();
    }
}

bool MarqueePattern::OnlyPlayStatusChange()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
    auto scrollAmount = paintProperty->GetScrollAmount().value_or(DEFAULT_MARQUEE_SCROLL_AMOUNT.ConvertToPx());
    auto loop = paintProperty->GetLoop().value_or(DEFAULT_MARQUEE_LOOP);
    auto direction = paintProperty->GetDirection().value_or(MarqueeDirection::LEFT);
    if (!NearEqual(scrollAmount_, scrollAmount) || loop_ != loop || direction_ != direction) {
        return false;
    }
    if (playStatus_ != playStatus) {
        return true;
    }
    return false;
}

void MarqueePattern::ChangeAnimationPlayStatus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
    if (playStatus) {
        if (!animation_) {
            StartMarqueeAnimation();
            return;
        }
        ResumeAnimation();
    } else {
        PauseAnimation();
    }
}

void MarqueePattern::StoreProperties()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    playStatus_ = paintProperty->GetPlayerStatus().value_or(false);
    scrollAmount_ = paintProperty->GetScrollAmount().value_or(DEFAULT_MARQUEE_SCROLL_AMOUNT.ConvertToPx());
    loop_ = paintProperty->GetLoop().value_or(DEFAULT_MARQUEE_LOOP);
    direction_ = paintProperty->GetDirection().value_or(MarqueeDirection::LEFT);
}

float MarqueePattern::CalculateStart()
{
    float start = 0.0f;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, start);
    auto geoNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geoNode, start);
    auto marqueeSize = geoNode->GetFrameSize();
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(textNode, start);
    auto textGeoNode = textNode->GetGeometryNode();
    CHECK_NULL_RETURN(textGeoNode, start);
    auto textWidth = textGeoNode->GetFrameSize().Width();
    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, start);
    auto direction = paintProperty->GetDirection().value_or(MarqueeDirection::LEFT);
    auto layoutProperty = host->GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, start);
    auto textDirection = GetCurrentTextDirection();
    Alignment align = (textDirection == TextDirection::RTL ? Alignment::CENTER_RIGHT : Alignment::CENTER_LEFT);

    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    if (direction == MarqueeDirection::LEFT) {
        if (NearEqual(align.GetHorizontal(), -1.0)) {
            start = marqueeSize.Width() - padding.left.value_or(0);
        } else if (NearEqual(align.GetHorizontal(), 0.0)) {
            start = (marqueeSize.Width() + textWidth) * HALF;
        } else {
            start = textWidth + padding.right.value_or(0);
        }
    } else {
        if (NearEqual(align.GetHorizontal(), -1.0)) {
            start = -1 * textWidth - padding.left.value_or(0);
        } else if (NearEqual(align.GetHorizontal(), 0.0)) {
            start = -1 * (marqueeSize.Width() + textWidth) * HALF;
        } else {
            start = -1 * marqueeSize.Width() + padding.right.value_or(0);
        }
    }
    return start;
}

float MarqueePattern::CalculateEnd()
{
    float end = 0.0f;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, end);
    auto geoNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geoNode, end);
    auto marqueeSize = geoNode->GetFrameSize();
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(textNode, end);
    auto textGeoNode = textNode->GetGeometryNode();
    CHECK_NULL_RETURN(textGeoNode, end);
    auto textWidth = textGeoNode->GetFrameSize().Width();
    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, end);
    auto layoutProperty = host->GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, end);
    auto direction = paintProperty->GetDirection().value_or(MarqueeDirection::LEFT);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    auto textDirection = GetCurrentTextDirection();
    Alignment align = (textDirection == TextDirection::RTL ? Alignment::CENTER_RIGHT : Alignment::CENTER_LEFT);

    if (direction == MarqueeDirection::LEFT) {
        if (NearEqual(align.GetHorizontal(), -1.0)) {
            end = -1 * textWidth - padding.left.value_or(0);
        } else if (NearEqual(align.GetHorizontal(), 0.0)) {
            end = -1 * (marqueeSize.Width() + textWidth) * HALF;
        } else {
            end = -1 * marqueeSize.Width() + padding.right.value_or(0);
        }
    } else {
        if (NearEqual(align.GetHorizontal(), -1.0)) {
            end = marqueeSize.Width() - padding.left.value_or(0);
        } else if (NearEqual(align.GetHorizontal(), 0.0)) {
            end = (marqueeSize.Width() + textWidth) * HALF;
        } else {
            end = textWidth + padding.right.value_or(0);
        }
    }
    return end;
}

void MarqueePattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    if (width != lastWindowWidth_ || height != lastWindowHeight_) {
        measureChanged_ = true;
    }
    lastWindowHeight_ = height;
    lastWindowWidth_ = width;
}

void MarqueePattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetNeedCallChildrenUpdate(false);
    auto textChild = host->GetChildren().front();
    CHECK_NULL_VOID(textChild);
    auto textChildNode = DynamicCast<FrameNode>(textChild);
    CHECK_NULL_VOID(textChildNode);
    auto textLayoutProperty = textChildNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<MarqueeTheme>();
    CHECK_NULL_VOID(theme);
    textLayoutProperty->UpdateTextColor(theme->GetTextColor());
    textChildNode->MarkModifyDone();
    textChildNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void MarqueePattern::DumpInfo()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textChild = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    DumpLog::GetInstance().AddDesc(std::string("Marquee text content: ").append(
        UtfUtils::Str16ToStr8(textLayoutProperty->GetContent().value_or(u""))));
    DumpLog::GetInstance().AddDesc(std::string("Play status: ").append(std::to_string(playStatus_)));
    DumpLog::GetInstance().AddDesc(std::string("loop: ").append(std::to_string(loop_)));
    DumpLog::GetInstance().AddDesc(std::string("step: ").append(std::to_string(scrollAmount_)));
}

float MarqueePattern::GetTextNodeWidth()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto geoNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geoNode, 0.0f);
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(textNode, 0.0f);
    auto textGeoNode = textNode->GetGeometryNode();
    CHECK_NULL_RETURN(textGeoNode, 0.0f);
    return textGeoNode->GetFrameSize().Width();
}

double MarqueePattern::GetScrollAmount()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, 0.0f);
    return paintProperty->GetScrollAmount().value_or(DEFAULT_MARQUEE_SCROLL_AMOUNT.ConvertToPx());
}

bool MarqueePattern::IsRunMarquee()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geoNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geoNode, false);
    auto marqueeSize = geoNode->GetFrameSize();
    auto textNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(textNode, false);
    auto textGeoNode = textNode->GetGeometryNode();
    CHECK_NULL_RETURN(textGeoNode, false);
    auto textWidth = textGeoNode->GetFrameSize().Width();
    auto layoutProperty = host->GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    float padding = 0.0f;
    if (layoutProperty->GetPaddingProperty()) {
        const auto& paddingProperty = layoutProperty->GetPaddingProperty();
        padding = paddingProperty->left.value_or(CalcLength(0.0)).GetDimension().ConvertToPx() +
            paddingProperty->right.value_or(CalcLength(0.0)).GetDimension().ConvertToPx();
    }
    return GreatOrEqual(textWidth + padding, marqueeSize.Width());
}

void MarqueePattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textChild = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    json->Put("Marquee text content", UtfUtils::Str16ToStr8(textLayoutProperty->GetContent().value_or(u"")).c_str());
    json->Put("Play status", playStatus_);
    json->Put("loop", loop_);
    json->Put("step", scrollAmount_);
}

TextDirection MarqueePattern::GetTextDirection(const std::string& content, TextDirection direction)
{
    if (direction == TextDirection::LTR || direction == TextDirection::RTL) {
        return direction;
    }

    bool isRTL = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto textDirection = isRTL ? TextDirection::RTL : TextDirection::LTR;
    auto showingTextForWString = StringUtils::ToWstring(content);
    for (const auto& charOfShowingText : showingTextForWString) {
        if (TextLayoutadapter::IsLeftToRight(charOfShowingText)) {
            return TextDirection::LTR;
        }
        if (TextLayoutadapter::IsRightToLeft(charOfShowingText) ||
            TextLayoutadapter::IsRightTOLeftArabic(charOfShowingText)) {
            return TextDirection::RTL;
        }
    }
    return textDirection;
}

TextDirection MarqueePattern::GetCurrentTextDirection()
{
    return currentTextDirection_;
}

void MarqueePattern::CheckTextDirectionChange(TextDirection direction)
{
    if (direction != currentTextDirection_) {
        lastAnimationOffset_ = std::nullopt;
    }
    currentTextDirection_ = direction;
}

void MarqueePattern::UpdateTextDirection(
    const RefPtr<MarqueeLayoutProperty>& layoutProperty, const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    auto src = layoutProperty->GetSrc().value_or(" ");
    std::replace(src.begin(), src.end(), '\n', ' ');
    textLayoutProperty->UpdateContent(src);
    auto direction = layoutProperty->GetLayoutDirection();
    auto textDirection = GetTextDirection(src, direction);
    textLayoutProperty->UpdateLayoutDirection(textDirection);
    CheckTextDirectionChange(textDirection);
}

void MarqueePattern::ProcessVisibleAreaCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnVisibleChange(visible);
    };
    std::vector<double> ratioList = { 0.0 };
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false, true);
}

void MarqueePattern::PauseAnimation()
{
    CHECK_NULL_VOID(animation_);
    playStatus_ = false;
    AnimationUtils::PauseAnimation(animation_);
}

void MarqueePattern::ResumeAnimation()
{
    CHECK_NULL_VOID(animation_);
    playStatus_ = true;
    AnimationUtils::ResumeAnimation(animation_);
}

void MarqueePattern::OnFontScaleConfigurationUpdate()
{
    if (!AnimationUtils::IsImplicitAnimationOpen()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterReloadAnimationTask([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
        pattern->StopMarqueeAnimation(playStatus);
    });
}

void MarqueePattern::UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> value)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutPropertyPtr<MarqueeLayoutProperty>();
    CHECK_NULL_VOID(property);
    CHECK_NULL_VOID(value);
    using Handler = std::function<void(MarqueeLayoutProperty*, RefPtr<PropertyValueBase>)>;
    const std::unordered_map<std::string, Handler> handlers = {
        { "FontSize",
            [](MarqueeLayoutProperty* prop, RefPtr<PropertyValueBase> value) {
                if (auto realValue = std::get_if<CalcDimension>(&(value->GetValue()))) {
                    prop->UpdateFontSize(*realValue);
                }
            }
        },
        { "TextColor",
            [node = WeakClaim(RawPtr((frameNode))), weak = WeakClaim(this)](
                MarqueeLayoutProperty* prop, RefPtr<PropertyValueBase> value) {
                auto frameNode = node.Upgrade();
                CHECK_NULL_VOID(frameNode);
                if (auto realValue = std::get_if<Color>(&(value->GetValue()))) {
                    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, *realValue, frameNode);
                    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
                    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
                    prop->UpdateFontColor(*realValue);
                }
            }
        },
        { "FontFamily",
            [](MarqueeLayoutProperty* prop, RefPtr<PropertyValueBase> value) {
                if (auto realValue = std::get_if<std::vector<std::string>>(&(value->GetValue()))) {
                    prop->UpdateFontFamily(*realValue);
                }
            }
        },
    };
    auto it = handlers.find(key);
    if (it != handlers.end()) {
        it->second(property, value);
    }
    if (frameNode->GetRerenderable()) {
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void MarqueePattern::OnColorModeChange(uint32_t colorMode)
{
    Pattern::OnColorModeChange(colorMode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkModifyDone();
}
} // namespace OHOS::Ace::NG
