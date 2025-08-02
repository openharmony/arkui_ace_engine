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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_PATTERN_H

#include <cstdint>

#include "core/components/rating/rating_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rating/rating_accessibility_property.h"
#include "core/components_ng/pattern/rating/rating_event_hub.h"
#include "core/components_ng/pattern/rating/rating_layout_algorithm.h"
#include "core/components_ng/pattern/rating/rating_layout_property.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_modifier.h"
#include "core/components_ng/pattern/rating/rating_render_property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components/theme/app_theme.h"

namespace OHOS::Ace::NG {
class InspectorFilter;


class RatingPattern : public Pattern {
    DECLARE_ACE_TYPE(RatingPattern, Pattern);

public:
    RatingPattern() = default;
    ~RatingPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<RatingLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<RatingLayoutAlgorithm>(foregroundImageLoadingCtx_,
            secondaryImageLoadingCtx_, backgroundImageLoadingCtx_, backgroundImageFocusLoadingCtx_);
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<RatingRenderProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<RatingEventHub>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<RatingAccessibilityProperty>();
    }

    // Called on main thread to check if need rerender of the content.
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    FocusPattern GetFocusPattern() const override
    {
        FocusPaintParam focusPaintParams;
        focusPaintParams.SetPaintWidth(themeBorderWidth_);
        return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION, focusPaintParams };
    }

    void SetBuilderFunc(RatingMakeCallback&& makeFunc)
    {
        if (makeFunc == nullptr) {
            makeFunc_ = std::nullopt;
            OnModifyDone();
            return;
        }
        makeFunc_ = std::move(makeFunc);
    }

    bool UseContentModifier()
    {
        return contentModifierNode_ != nullptr;
    }

    void SetRatingScore(double value);

    RatingModifier::RatingAnimationType GetRatingState() const
    {
        return state_;
    }

    bool IsNeedFocusStyle()
    {
        return isNeedFocusStyle_;
    }

    void DumpInfo() override;

    bool IsEnableMatchParent() override
    {
        return true;
    }

    void LoadForeground(const RefPtr<RatingLayoutProperty>& layoutProperty, const RefPtr<RatingTheme>& ratingTheme,
        const RefPtr<IconTheme>& iconTheme);
    void LoadSecondary(const RefPtr<RatingLayoutProperty>& layoutProperty, const RefPtr<RatingTheme>& ratingTheme,
        const RefPtr<IconTheme>& iconTheme);
    void LoadBackground(const RefPtr<RatingLayoutProperty>& layoutProperty, const RefPtr<RatingTheme>& ratingTheme,
        const RefPtr<IconTheme>& iconTheme);

private:
    void OnAttachToFrameNode() override;
    void UpdateRatingScore(double ratingScore);
    void MarkDirtyNode(const PropertyChangeFlag& flag);
    void OnModifyDone() override;
    void ConstrainsRatingScore(const RefPtr<RatingLayoutProperty>& layoutProperty);
    void LoadFocusBackground(const RefPtr<RatingLayoutProperty>& layoutProperty, const RefPtr<RatingTheme>& ratingTheme,
        const RefPtr<IconTheme>& iconTheme);
    void UpdatePaintConfig();
    void PrepareAnimation(const RefPtr<CanvasImage>& image);
    void SetRedrawCallback(const RefPtr<CanvasImage>& image);
    void OnImageDataReady(int32_t imageFlag);
    void OnImageLoadSuccess(int32_t imageFlag);
    void CheckImageInfoHasChangedOrNot(
        int32_t imageFlag, const ImageSourceInfo& sourceInfo, const std::string& lifeCycleTag);
    float GetFocusRectRadius(const RefPtr<RatingLayoutProperty>& property, float& focusSpace);
    void OnColorModeChange(uint32_t colorMode) override;

    // Init pan recognizer to update render when drag updates, fire change event when drag ends.
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleEnabled();

    // Init touch event, show press effect when touch down, update render when touch up.
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);

    // Init touch event, update render when click.
    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();

    // Init key event
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    void OnFocusEvent();
    void OnBlurEvent();
    void SetModifierFocus(bool isFocus);
    bool OnKeyEvent(const KeyEvent& event);
    void PaintFocusState(double ratingScore);
    void GetInnerFocusPaintRect(RoundRect& paintRect);

    // Init mouse event
    void InitMouseEvent();
    void HandleMouseEvent(MouseInfo& info);
    void HandleHoverEvent(bool isHover);

    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd();
    void HandleTouchDown(const Offset& localPosition);
    void HandleTouchUp();
    void HandleClick(const GestureEvent& info);
    void FireChangeEvent();
    void RecalculatedRatingScoreBasedOnEventPoint(double eventPointX, bool isDrag);
    bool IsIndicator();
    void FireBuilder();
    RefPtr<FrameNode> BuildContentModifierNode();
    bool IsRatingImageReady(uint32_t imageStateCode);

    std::optional<RatingMakeCallback> makeFunc_;
    RefPtr<FrameNode> contentModifierNode_;
    RefPtr<PanEvent> panEvent_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<ClickEvent> clickEvent_;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<PipelineContext> pipelineContext_;
    std::function<void(bool)> isFocusActiveUpdateEvent_;

    DataReadyNotifyTask CreateDataReadyCallback(int32_t imageFlag);
    LoadSuccessNotifyTask CreateLoadSuccessCallback(int32_t imageFlag);
    LoadFailNotifyTask CreateLoadFailCallback(int32_t imageFlag);

    RefPtr<ImageLoadingContext> foregroundImageLoadingCtx_;
    RefPtr<ImageLoadingContext> secondaryImageLoadingCtx_;
    RefPtr<ImageLoadingContext> backgroundImageLoadingCtx_;
    RefPtr<ImageLoadingContext> backgroundImageFocusLoadingCtx_;

    RefPtr<RatingModifier> ratingModifier_;
    RefPtr<CanvasImage> foregroundImageCanvas_;
    RefPtr<CanvasImage> secondaryImageCanvas_;
    RefPtr<CanvasImage> backgroundImageCanvas_;
    RefPtr<CanvasImage> backgroundImageFocusCanvas_;
    ImagePaintConfig foregroundConfig_;
    ImagePaintConfig secondaryConfig_;
    ImagePaintConfig backgroundConfig_;
    ImagePaintConfig backgroundFocusConfig_;
    uint32_t imageReadyStateCode_ = 0;
    uint32_t imageSuccessStateCode_ = 0;
    bool hasInit_ = false;
    bool isHover_ = false;
    bool isfocus_ = false;
    bool isNeedFocusStyle_ = false;
    double focusRatingScore_ = 0.0;
    double lastRatingScore_ = 0.0;
    RatingModifier::RatingAnimationType state_;
    float singleStarWidth_ = .0f;
    int32_t themeStarNum_ = OHOS::Ace::DEFAULT_RATING_STAR_NUM;
    double themeStepSize_ = OHOS::Ace::DEFAULT_RATING_STEP_SIZE;
    double themeRatingScore_ = OHOS::Ace::DEFAULT_RATING_SCORE;
    Dimension themeBorderWidth_ = 0.0_vp;

    bool isForegroundImageInfoFromTheme_ = false;
    bool isSecondaryImageInfoFromTheme_ = false;
    bool isBackgroundImageInfoFromTheme_ = false;
    std::optional<ImageSourceInfo> foregroundImageSourceInfo_ = std::nullopt;
    std::optional<ImageSourceInfo> secondaryImageSourceInfo_ = std::nullopt;
    std::optional<ImageSourceInfo> backgroundImageSourceInfo_ = std::nullopt;
    std::optional<ImageSourceInfo> focusBackgroundImageSourceInfo_ = std::nullopt;
    // get XTS inspector value
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    ACE_DISALLOW_COPY_AND_MOVE(RatingPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_PATTERN_H
