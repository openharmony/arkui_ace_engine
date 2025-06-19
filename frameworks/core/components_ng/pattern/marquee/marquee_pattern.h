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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_PATTERN_H

#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/marquee/marquee_accessibility_property.h"
#include "core/components_ng/pattern/marquee/marquee_event_hub.h"
#include "core/components_ng/pattern/marquee/marquee_layout_algorithm.h"
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/pattern/marquee/marquee_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace {
    class AnimationOption;
}

namespace OHOS::Ace::NG {
using TimeCallback = std::function<void()>;
struct LastAnimationParam {
    uint64_t lastStartMilliseconds = 0;
    float lastAnimationPosition = 0.0f;
    float lastStep = 1.0f;
    float lastDistance = 0.0f;
    float lastDuration = 0.0f;
    float lastStart = 0.0f;
    float lastEnd = 0.0f;
    MarqueeDirection lastDirection = MarqueeDirection::LEFT;
};

class MarqueePattern : public Pattern {
    DECLARE_ACE_TYPE(MarqueePattern, Pattern);

public:
    MarqueePattern() = default;
    ~MarqueePattern() override;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<MarqueeLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<MarqueePaintProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<MarqueeEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<MarqueeLayoutAlgorithm>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<MarqueeAccessibilityProperty>();
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void OnColorConfigurationUpdate() override;
    void DumpInfo() override;
    
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void OnVisibleChange(bool isVisible) override;
    void OnWindowHide() override;
    void OnWindowShow() override;
    void SetMarqueeFrameRateRange(const RefPtr<FrameRateRange>& rateRange, MarqueeDynamicSyncSceneType type)
    {
        frameRateRange_[type] = rateRange;
    }
    TextDirection GetTextDirection(const std::string& content, TextDirection direction);
    void OnFontScaleConfigurationUpdate() override;

protected:
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> value) override;

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;

    void FireStartEvent() const;
    void FireBounceEvent() const;
    void FireFinishEvent() const;

    void StartMarqueeAnimation();
    void StopMarqueeAnimation(bool stopAndStart);
    void UpdateTextTranslateXY(float offsetX, bool cancel = false);
    void PropertyCancelAnimationFinish();
    bool OnlyPlayStatusChange();
    void ChangeAnimationPlayStatus();
    void StoreProperties();
    void PlayMarqueeAnimation(float start, int32_t playCount, bool needSecondPlay, bool isFirst = true);
    void StopAndResetAnimation();
    void OnAnimationFinish();
    float CalculateStart();
    float CalculateEnd();
    float GetTextOffset();
    float GetTextNodeWidth();
    double GetScrollAmount();
    void CheckTextDirectionChange(TextDirection direction);
    TextDirection GetCurrentTextDirection();
    void UpdateTextDirection(
        const RefPtr<MarqueeLayoutProperty>& layoutProperty, const RefPtr<TextLayoutProperty>& textLayoutProperty);
    void ActionAnimation(AnimationOption& option, float end, int32_t playCount, bool needSecondPlay);
    bool IsRunMarquee();
    void ProcessVisibleAreaCallback();
    void PauseAnimation();
    void ResumeAnimation();

    bool measureChanged_ = false;
    int32_t animationId_ = 0;
    std::shared_ptr<AnimationUtils::Animation> animation_;
    bool playStatus_ = false;
    double scrollAmount_ = DEFAULT_MARQUEE_SCROLL_AMOUNT.ConvertToPx();
    int32_t loop_ = -1;
    MarqueeDirection direction_ = MarqueeDirection::LEFT;
    TextDirection currentTextDirection_ = TextDirection::LTR;
    ACE_DISALLOW_COPY_AND_MOVE(MarqueePattern);
    int32_t lastWindowHeight_ = 0.0;
    int32_t lastWindowWidth_ = 0.0;
    float marqueeWidth_ = 0.0f;
    std::optional<OffsetF> lastAnimationOffset_;
    std::unordered_map<MarqueeDynamicSyncSceneType, RefPtr<FrameRateRange>> frameRateRange_ ;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_PATTERN_H
