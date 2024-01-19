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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TITLE_BAR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TITLE_BAR_PATTERN_H

#include "core/common/container.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/title_bar_accessibility_property.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class TitleBarPattern : public Pattern {
    DECLARE_ACE_TYPE(TitleBarPattern, Pattern);

public:
    TitleBarPattern() = default;
    ~TitleBarPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TitleBarLayoutProperty>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<TitleBarAccessibilityProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto titleBarLayoutAlgorithm = MakeRefPtr<TitleBarLayoutAlgorithm>();
        titleBarLayoutAlgorithm->SetInitialTitleOffsetY(initialTitleOffsetY_);
        titleBarLayoutAlgorithm->MarkIsInitialTitle(isInitialTitle_);
        titleBarLayoutAlgorithm->SetInitialSubtitleOffsetY(initialSubtitleOffsetY_);
        titleBarLayoutAlgorithm->MarkIsInitialSubtitle(isInitialSubtitle_);
        titleBarLayoutAlgorithm->SetMinTitleHeight(minTitleHeight_);
        return titleBarLayoutAlgorithm;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    void OnModifyDone() override;

    float GetTempTitleBarHeight() const
    {
        return tempTitleBarHeight_;
    }

    float GetDefaultTitleBarHeight() const
    {
        return defaultTitleBarHeight_;
    }

    float GetTempTitleOffsetY() const
    {
        return tempTitleOffsetY_;
    }

    float GetTempSubTitleOffsetY() const
    {
        return tempSubTitleOffsetY_;
    }

    float GetMaxTitleBarHeight() const
    {
        return maxTitleBarHeight_;
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void InitTitleParam();

    bool IsHidden();

    bool IsInitialTitle() const
    {
        return isInitialTitle_;
    }

    void MarkIsInitialTitle(bool isInitialTitle)
    {
        isInitialTitle_ = isInitialTitle;
    }

    bool IsInitialSubtitle() const
    {
        return isInitialSubtitle_;
    }

    void MarkIsInitialSubtitle(bool isInitialSubtitle)
    {
        isInitialSubtitle_ = isInitialSubtitle;
    }
    void ProcessTitleDragStart(float offset);
    void ProcessTitleDragUpdate(float offset);

    void ProcessTitleDragEnd();
    
    void OnColorConfigurationUpdate() override;

    float GetCurrentOffset()
    {
        return tempTitleBarHeight_ - defaultTitleBarHeight_;
    }

    void SetOverDragOffset(float overDragOffset)
    {
        overDragOffset_ = overDragOffset;
    }

    float GetOverDragOffset() const
    {
        return overDragOffset_;
    }
    
    bool IsTitleDraggedDown() const
    {
        if (NearZero(tempTitleBarHeight_)) {
            return true;
        }
        return GreatNotEqual(tempTitleBarHeight_, static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    }

    bool IsTitleFullStatus() const
    {
        if (NearZero(tempTitleBarHeight_)) {
            return true;
        }
        GetMaxTitleBarHeight();
        return GreatOrEqual(tempTitleBarHeight_, maxTitleBarHeight_);
    }

    bool IsMinTitle() const
    {
        if (NearZero(tempTitleBarHeight_)) {
            return true;
        }
        GetMaxTitleBarHeight();
        return LessOrEqual(tempTitleBarHeight_, maxTitleBarHeight_);
    }

    bool IsCurrentMinTitle() const
    {
        if (NearZero(tempTitleBarHeight_)) {
            return true;
        }
        return LessOrEqual(tempTitleBarHeight_, static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    }

    bool IsCurrentMaxTitle() const
    {
        if (NearZero(tempTitleBarHeight_)) {
            return false;
        }
        GetMaxTitleBarHeight();
        return GreatOrEqual(tempTitleBarHeight_, maxTitleBarHeight_);
    }

    bool IsFreeTitleUpdated() const
    {
        return isFreeTitleUpdated_;
    }

    NavigationTitleMode GetNavigationTitleMode() const
    {
        return titleMode_;
    }

    void SetCanOverDrag(bool CanOverDrag)
    {
        CanOverDrag_ = CanOverDrag;
    }

    void SetTitleScaleChange(bool isTitleScaleChange)
    {
        isTitleScaleChange_ = isTitleScaleChange;
    }

    void OnCoordScrollStart();
    float OnCoordScrollUpdate(float offset);
    void OnCoordScrollEnd();

private:
    void TransformScale(float overDragOffset, const RefPtr<FrameNode>& frameNode);

    void ClearDragState();
    float GetSubtitleOpacity();
    float GetFontSize(float offset);
    float GetMappedOffset(float offset);
    void SpringAnimation(float startPos, float endPos);
    void UpdateScaleByDragOverDragOffset(float overDragOffset);
    void AnimateTo(float offset);

    void OnAttachToFrameNode() override;

    void HandleDragStart(const GestureEvent& info);
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(double dragVelocity);

    void SetMaxTitleBarHeight();
    void SetTempTitleBarHeight(float offsetY);
    void SetTempTitleOffsetY();
    void SetTempSubTitleOffsetY();
    void SetDefaultTitleFontSize();
    void SetDefaultSubtitleOpacity();

    float GetTitleHeight();
    float GetSubTitleOffsetY();
    void UpdateTitleFontSize(const Dimension& tempTitleFontSize);
    void UpdateSubTitleOpacity(const double &value);
    void UpdateTitleModeChange();
    void MountTitle(const RefPtr<TitleBarNode>& hostNode);

    void UpdateTitleBarByCoordScroll(float offset);
    void SetTitleStyleByCoordScrollOffset(float offset);
    float CalculateHandledOffsetMinTitle(float offset, float lastCordScrollOffset);
    float CalculateHandledOffsetMaxTitle(float offset, float lastCordScrollOffset);
    float CalculateHandledOffsetBetweenMinAndMaxTitle(float offset, float lastCordScrollOffset);

    void SetBackgroundAndBlur();

    RefPtr<PanEvent> panEvent_;
    RefPtr<SpringMotion> springMotion_;
    RefPtr<Animator> springController_;
    RefPtr<Animator> animator_;
    std::optional<float> fontSize_;
    std::optional<float> opacity_;

    float overDragOffset_ = 0.0f;
    float maxTitleBarHeight_ = 0.0f;
    float defaultTitleBarHeight_ = 0.0f;
    float tempTitleBarHeight_ = 0.0f;
    float minTitleOffsetY_ = 0.0f;
    float maxTitleOffsetY_ = 0.0f;
    // ratio of titleOffsetY difference and titleBarHeight difference
    float moveRatio_ = 0.0f;
    float titleMoveDistance_ = 0.0f;
    float defaultTitleOffsetY_ = 0.0f;
    float defaultSubtitleOffsetY_ = 0.0f;
    float tempTitleOffsetY_ = 0.0f;
    float tempSubTitleOffsetY_ = 0.0f;

    Dimension defaultTitleFontSize_;
    // ratio of fontSize difference and titleBarHeight difference
    double fontSizeRatio_ = 0.0f;

    float defaultSubtitleOpacity_;
    // ratio of opacity difference and titleBarHeight difference
    double opacityRatio_ = 0.0f;

    float initialTitleOffsetY_ = 0.0f;
    bool isInitialTitle_ = true;
    float initialSubtitleOffsetY_ = 0.0f;
    bool isInitialSubtitle_ = true;
    float minTitleHeight_ = 0.0f;
    bool CanOverDrag_ = true;
    bool isTitleScaleChange_ = true;
    NavigationTitleMode titleMode_ = NavigationTitleMode::FREE;

    bool isFreeTitleUpdated_ = false;

    float coordScrollOffset_ = 0.0f;
    float coordScrollFinalOffset_ = 0.0f;

    // the value before title bar expand safe area
    float currentTitleOffsetY_ = 0.0f;
    float currentTitleBarHeight_ = 0.0f;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TITLE_BAR_PATTERN_H
