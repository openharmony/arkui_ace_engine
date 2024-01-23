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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_PRESENTATION_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_PRESENTATION_PATTERN_H

#include <functional>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SheetPresentationPattern : public LinearLayoutPattern, public PopupBasePattern {
    DECLARE_ACE_TYPE(SheetPresentationPattern, LinearLayoutPattern, PopupBasePattern);

public:
    SheetPresentationPattern(
        int32_t targetId, const std::string& targetTag, std::function<void(const std::string&)>&& callback)
        : LinearLayoutPattern(true)
    {
        targetId_ = targetId;
        targetTag_ = targetTag;
        callback_ = std::move(callback);
    }

    ~SheetPresentationPattern() override = default;

    bool IsMeasureBoundary() const override
    {
        return true;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SheetPresentationLayoutAlgorithm>(targetId_, targetTag_, GetSheetType());
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SheetPresentationProperty>();
    }

    int32_t GetTargetId() const override
    {
        return targetId_;
    }

    void FireCallback(const std::string& value)
    {
        if (callback_) {
            callback_(value);
        }
    }

    bool HasCallback() const
    {
        return static_cast<bool>(callback_);
    }

    void UpdateShouldDismiss(std::function<void()>&& shouldDismiss)
    {
        shouldDismiss_ = std::move(shouldDismiss);
    }

    bool hasShouldDismiss()
    {
        if (shouldDismiss_) {
            return true;
        }
        return false;
    }

    void UpdateOnDisappear(std::function<void()>&& onDisappear)
    {
        onDisappear_ = std::move(onDisappear);
        isExecuteOnDisappear_ = false;
    }

    void OnDisappear()
    {
        if (onDisappear_) {
            isExecuteOnDisappear_ = true;
            onDisappear_();
        }
    }

    void CallShouldDismiss()
    {
        if (shouldDismiss_) {
            shouldDismiss_();
        }
    }

    void DismissSheet()
    {
        DismissTransition(false);
    }

    void InitialLayoutProps();

    void AvoidAiBar();
    void AvoidSafeArea();
    float GetSheetHeightChange();
    void ScrollTo(float height);
    float InitialSingleGearHeight(NG::SheetStyle& sheetStyle);

    // initial drag gesture event
    void InitPanEvent();

    void HandleDragStart();

    void HandleDragUpdate(const GestureEvent& info);

    void HandleDragEnd(float dragVelocity);

    void OnCoordScrollStart();

    bool OnCoordScrollUpdate(float scrollOffset);

    void OnCoordScrollEnd(float dragVelocity);

    void SheetTransition(bool isTransitionIn, float dragVelocity = 0.0f);

    void SheetInteractiveDismiss(bool isDragClose, float dragVelocity = 0.0f);

    void SetCurrentOffset(float currentOffset)
    {
        currentOffset_ = currentOffset;
    }

    void SetCurrentHeight(float currentHeight)
    {
        height_ = currentHeight;
        ProcessColumnRect(height_);
        ChangeScrollHeight(height_);
    }

    void SetCurrentHeightToOverlay(float height)
    {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->SetSheetHeight(height);
    }

    void ChangeScrollHeight(float height);

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    bool IsExecuteOnDisappear() const
    {
        return isExecuteOnDisappear_;
    }

    bool AvoidKeyboard() const override
    {
        return false;
    }

    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;

    bool HasTitleNode() const
    {
        return titleId_.has_value();
    }

    bool SetTitleId(const int32_t id)
    {
        if (HasTitleNode()) {
            return false;
        }
        titleId_ = id;
        return true;
    }

    int32_t GetTitleId()
    {
        if (!titleId_.has_value()) {
            titleId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return titleId_.value();
    }

    bool HasSubtitleNode() const
    {
        return titleId_.has_value();
    }

    bool SetSubtitleId(const int32_t id)
    {
        if (HasSubtitleNode()) {
            return false;
        }
        subtitleId_ = id;
        return true;
    }

    int32_t GetSubtitleId()
    {
        if (!subtitleId_.has_value()) {
            subtitleId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return subtitleId_.value();
    }

    static float CalculateFriction(float gamma)
    {
        constexpr float RATIO = 1.848f;
        if (GreatOrEqual(gamma, 1.0)) {
            gamma = 1.0f;
        }
        return exp(-RATIO * gamma);
    }

    SheetType GetSheetType();

    void BubbleStyleSheetTransition(bool isTransitionIn);

    void StartOffsetEnteringAnimation();

    void StartAlphaEnteringAnimation(std::function<void()> finish);

    void StartOffsetExitingAnimation();

    void StartAlphaExitingAnimation(std::function<void()> finish);

    void ResetToInvisible();

    bool IsFold();

    bool GetAnimationBreak() const
    {
        return isAnimationBreak_;
    }

    void SetAnimationProcess(bool isProcess)
    {
        isAnimationProcess_ = isProcess;
    }

    float GetSheetMaxHeight()
    {
        return pageHeight_;
    }

    float GetSheetMaxWidth()
    {
        return sheetMaxWidth_;
    }

    float GetSheetOffset()
    {
        return sheetOffsetY_;
    }

    float GetFitContentHeight();

    void ProcessColumnRect(float height = 0.0f);

protected:
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void InitPageHeight();
    void TranslateTo(float height);
    void SetColumnMinSize(bool reset = false);
    void UpdateDragBarStatus();
    void UpdateCloseIconStatus();
    void UpdateSheetTitle();
    void UpdateInteractive();
    RefPtr<RenderContext> GetRenderContext();
    bool PostTask(const TaskExecutor::Task& task);
    void CheckSheetHeightChange();
    void InitSheetDetents();
    void HandleFitContontChange(float height);
    void ChangeSheetHeight(float height);
    void StartSheetTransitionAnimation(const AnimationOption& option, bool isTransitionIn, float offset);
    void ClipSheetNode();
    std::string GetPopupStyleSheetClipPath(SizeF sheetSize, Dimension sheetRadius);
    std::string GetCenterStyleSheetClipPath(SizeF sheetSize, Dimension sheetRadius);
    std::string GetBottomStyleSheetClipPath(SizeF sheetSize, Dimension sheetRadius);
    std::string MoveTo(double x, double y);
    std::string LineTo(double x, double y);
    std::string ArcTo(double rx, double ry, double rotation, int32_t arc_flag, double x, double y);
    void DismissTransition(bool isTransitionIn, float dragVelocity = 0.0f);
    uint32_t keyboardHeight_ = 0;
    int32_t targetId_ = -1;
    std::optional<int32_t> titleId_;
    std::optional<int32_t> subtitleId_;
    std::string targetTag_;
    std::function<void(const std::string&)> callback_;
    std::function<void()> onDisappear_;
    std::function<void()> shouldDismiss_;
    RefPtr<PanEvent> panEvent_;
    float currentOffset_ = 0.0f;

    float height_ = 0.0f; // sheet height, start from the bottom
    float sheetHeight_ = 0.0f;
    float pageHeight_ = 0.0f;
    float scrollHeight_ = 0.0f;
    float statusBarHeight_ = .0f;
    bool isExecuteOnDisappear_ = false;
    bool windowRotate_ = false;
    bool firstMeasure_ = true;
    bool isScrolling_ = false;

    float sheetMaxHeight_ = 0.0f;
    float sheetMaxWidth_ = 0.0f;
    float centerHeight_ = 0.0f;
    float sheetFitContentHeight_ = 0.0f;
    float sheetOffsetX_ = 0.0f;
    float sheetOffsetY_ = 0.0f;
    bool isFirstInit_ = true;
    bool isAnimationBreak_ = false;
    bool isAnimationProcess_ = false;
    SheetType sheetType_ = SheetType::SHEET_BOTTOM;
    bool windowChanged_ = false;

    std::string sheetThemeType_ = "auto";

    std::vector<float> sheetDetentHeight_;

    std::shared_ptr<AnimationUtils::Animation> animation_;

    ACE_DISALLOW_COPY_AND_MOVE(SheetPresentationPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_PRESENTATION_PATTERN_H
