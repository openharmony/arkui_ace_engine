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
#include "core/common/autofill/auto_fill_trigger_state_holder.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/manager/avoid_info/avoid_info_manager.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

enum class BindSheetDismissReason {
    BACK_PRESSED = 0,
    TOUCH_OUTSIDE,
    CLOSE_BUTTON,
    SLIDE_DOWN,
};
class ACE_EXPORT SheetPresentationPattern : public LinearLayoutPattern,
                                            public PopupBasePattern,
                                            public FocusView,
                                            public NestableScrollContainer,
                                            public AutoFillTriggerStateHolder,
                                            public IAvoidInfoListener {
    DECLARE_ACE_TYPE(SheetPresentationPattern, LinearLayoutPattern, PopupBasePattern, FocusView,
        NestableScrollContainer, AutoFillTriggerStateHolder, IAvoidInfoListener);

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

    void SetOverlay(const WeakPtr<OverlayManager>& overlayManager)
    {
        overlayManager_ = overlayManager;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SheetPresentationLayoutAlgorithm>(GetSheetType(), sheetPopupInfo_);
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SheetPresentationProperty>();
    }

    int32_t GetTargetId() const override
    {
        return targetId_;
    }

    const std::string& GetTargetTag() const
    {
        return targetTag_;
    }

    void FireCallback(const std::string& value)
    {
        if (callback_) {
            callback_(value);
        }
    }

    void UpdateShouldDismiss(std::function<void()>&& shouldDismiss)
    {
        shouldDismiss_ = std::move(shouldDismiss);
    }

    bool HasShouldDismiss()
    {
        if (shouldDismiss_) {
            return true;
        }
        return false;
    }

    void CallShouldDismiss()
    {
        if (shouldDismiss_) {
            shouldDismiss_();
        }
    }

    void UpdateOnDisappear(std::function<void()>&& onDisappear)
    {
        onDisappear_ = std::move(onDisappear);
        isExecuteOnDisappear_ = false;
    }

    void OnDisappear()
    {
        if (onDisappear_) {
            TAG_LOGI(AceLogTag::ACE_SHEET, "bindsheet lifecycle change to onDisappear state.");
            isExecuteOnDisappear_ = true;
            onDisappear_();
        }
        isDismissProcess_ = false;
    }

    void UpdateOnWillDisappear(std::function<void()>&& onWillDisappear)
    {
        onWillDisappear_ = std::move(onWillDisappear);
    }

    void OnWillDisappear();

    void UpdateOnAppear(std::function<void()>&& onAppear)
    {
        onAppear_ = std::move(onAppear);
    }

    void OnAppear()
    {
        if (onAppear_) {
            TAG_LOGI(AceLogTag::ACE_SHEET, "bindsheet lifecycle change to onAppear state.");
            onAppear_();
        }
    }

    void UpdateOnHeightDidChange(std::function<void(const float)>&& onHeightDidChange)
    {
        onHeightDidChange_ = std::move(onHeightDidChange);
    }

    void OnHeightDidChange(float currentHeight) const
    {
        if (onHeightDidChange_) {
            onHeightDidChange_(currentHeight);
        }
    }

    void FireOnHeightDidChange();

    bool HasOnHeightDidChange()
    {
        if (onHeightDidChange_) {
            return true;
        }
        return false;
    }

    void UpdateOnDetentsDidChange(std::function<void(const float)>&& onDetentsDidChange)
    {
        onDetentsDidChange_ = std::move(onDetentsDidChange);
    }

    void OnDetentsDidChange(float currentHeight) const
    {
        if (onDetentsDidChange_) {
            onDetentsDidChange_(currentHeight);
        }
    }

    void FireOnDetentsDidChange(float height);

    void UpdateOnWidthDidChange(std::function<void(const float)>&& onWidthDidChange)
    {
        onWidthDidChange_ = std::move(onWidthDidChange);
    }

    void onWidthDidChange(float currentWidth) const
    {
        if (onWidthDidChange_) {
            onWidthDidChange_(currentWidth);
        }
    }

    void FireOnWidthDidChange(RefPtr<FrameNode> sheetNode);

    void UpdateOnTypeDidChange(std::function<void(const float)>&& onTypeDidChange)
    {
        onTypeDidChange_ = std::move(onTypeDidChange);
    }

    void onTypeDidChange(float currentType) const
    {
        if (onTypeDidChange_) {
            onTypeDidChange_(currentType);
        }
    }

    void FireOnTypeDidChange();

    void UpdateOnWillDismiss(std::function<void(const int32_t)>&& onWillDismiss)
    {
        onWillDismiss_ = std::move(onWillDismiss);
    }

    bool HasOnWillDismiss() const
    {
        if (onWillDismiss_) {
            return true;
        }
        return false;
    }

    void CallOnWillDismiss(const int32_t reason)
    {
        if (onWillDismiss_) {
            onWillDismiss_(reason);
        }
    }

    void UpdateSheetSpringBack(std::function<void()>&& sheetSpringBack)
    {
        sheetSpringBack_ = std::move(sheetSpringBack);
    }

    bool HasSheetSpringBack() const
    {
        if (sheetSpringBack_) {
            return true;
        }
        return false;
    }

    void CallSheetSpringBack()
    {
        if (sheetSpringBack_) {
            sheetSpringBack_();
        }
    }

    void OverlaySheetSpringBack();
    void OverlayDismissSheet();
    void DismissSheet()
    {
        DismissTransition(false);
    }

    void SheetSpringBack()
    {
        isDismissProcess_ = false;
        SheetTransition(true);
    }

    void InitialLayoutProps();

    bool IsScrollable() const;
    void AvoidAiBar();

    void AvoidSafeArea(bool forceAvoid = false);
    void CheckBuilderChange();
    float GetSheetHeightChange();
    void ScrollTo(float height);
    bool AdditionalScrollTo(const RefPtr<FrameNode>& scroll, float height);
    float InitialSingleGearHeight(NG::SheetStyle& sheetStyle);
    float GetSheetTopSafeArea();
    float UpdateSheetTransitionOffset();

    // initial drag gesture event
    void InitPanEvent();
    void InitOnkeyEvent(const RefPtr<FocusHub>& focusHub);
    void HandleFocusEvent();
    void HandleBlurEvent();

    void HandleDragStart();

    void HandleDragUpdate(const GestureEvent& info);

    void HandleDragEnd(float dragVelocity);

    void OnCoordScrollStart();

    bool OnCoordScrollUpdate(float scrollOffset);

    void OnCoordScrollEnd(float dragVelocity);

    void SheetTransition(bool isTransitionIn, float dragVelocity = 0.0f);

    void ModifyFireSheetTransition(float dragVelocity = 0.0f);

    void SheetInteractiveDismiss(BindSheetDismissReason dismissReason, float dragVelocity = 0.0f);

    void SetSheetAnimationOption(AnimationOption& option) const;

    void SetSheetBorderWidth(bool isPartialUpdate = false);

    void SetCurrentOffset(float currentOffset)
    {
        currentOffset_ = currentOffset;
    }

    void SetCurrentHeight(float currentHeight)
    {
        if (height_ != currentHeight) {
            height_ = currentHeight;
            ChangeScrollHeight(height_);
        }
    }

    bool GetWindowButtonRect(NG::RectF& floatButtons);

    void SetBottomOffset(const SheetStyle &sheetStyle)
    {
        DeviceType deviceType = SystemProperties::GetDeviceType();
        if (deviceType != DeviceType::TWO_IN_ONE) {
            TAG_LOGI(AceLogTag::ACE_SHEET, "Bottom offset invalid");
            return;
        }
        if (sheetStyle.bottomOffset.has_value() &&
            sheetStyle.sheetType.value_or(SheetType::SHEET_BOTTOM) == SheetType::SHEET_BOTTOM) {
            bottomOffsetX_ = sheetStyle.bottomOffset->GetX();
            bottomOffsetY_ = sheetStyle.bottomOffset->GetY();
        } else {
            bottomOffsetX_ = 0;
            bottomOffsetY_ = 0;
        }
    }

    void SetCurrentHeightToOverlay(float height)
    {
        auto overlayManager = GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->SetSheetHeight(height);
    }

    void ChangeScrollHeight(float height);

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    std::list<int32_t> GetRouteOfFirstScope() override
    {
        return { 1, 0 };
    }

    bool IsExecuteOnDisappear() const
    {
        return isExecuteOnDisappear_;
    }

    bool AvoidKeyboard() const override
    {
        return false;
    }

    bool IsWindowSizeChangedWithUndefinedReason(int32_t width, int32_t height, WindowSizeChangeReason type);

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

    static float CalculateFriction(float gamma, float ratio)
    {
        if (GreatOrEqual(gamma, 1.0)) {
            gamma = 1.0f;
        }
        return exp(-ratio * gamma);
    }

    SheetType GetSheetType();
    bool IsPhoneInLandScape();
    bool IsShowCloseIcon();
    ScrollSizeMode GetScrollSizeMode();
    void InitSheetMode();
    void GetSheetTypeWithAuto(SheetType& sheetType);
    void GetSheetTypeWithPopup(SheetType& sheetType);

    void SetUIFirstSwitch(bool isFirstTransition, bool isNone);

    void BubbleStyleSheetTransition(bool isTransitionIn);

    void StartOffsetEnteringAnimation();

    void StartAlphaEnteringAnimation(std::function<void()> finish);

    void StartOffsetExitingAnimation();

    void StartAlphaExitingAnimation(std::function<void()> finish);

    void ResetToInvisible();

    bool IsFoldExpand();

    void SetSheetKey(const SheetKey& sheetKey)
    {
        sheetKey_ = sheetKey;
    }

    SheetKey GetSheetKey() const
    {
        return sheetKey_;
    }

    bool GetAnimationBreak() const
    {
        return isAnimationBreak_;
    }

    void SetAnimationProcess(bool isProcess)
    {
        isAnimationProcess_ = isProcess;
    }

    bool GetAnimationProcess()
    {
        return isAnimationProcess_;
    }

    void SetDismissProcess(bool isProcess)
    {
        isDismissProcess_ = isProcess;
    }

    bool GetDismissProcess()
    {
        return isDismissProcess_;
    }

    float GetPageHeightWithoutOffset() const
    {
        return pageHeight_;
    }

    float GetPageHeight()
    {
        // OnTransformTranslateUpdate's offset is the relative to the upper left corner of the father
        // Therefore, if the father is a PageNode, need to obtain the offsetY of the Page relative to the window
        // On the basis of the normally calculated offset, move parentOffsetY up,
        // It can be considered as the offset relative to the window
        auto parentOffsetY = GetRootOffsetYToWindow();
        return pageHeight_ - parentOffsetY;
    }

    float GetSheetMaxHeight()
    {
        // pageHeight - sheetTopSafeArea
        return sheetMaxHeight_;
    }

    float GetSheetMaxWidth()
    {
        return sheetMaxWidth_;
    }

    float GetSheetOffset()
    {
        return sheetOffsetY_;
    }

    bool IsShowInSubWindowTwoInOne();
    bool IsShowInSubWindow();
    SheetType ComputeSheetTypeInSubWindow();
    void SheetTransitionAction(float offset, bool isStart, bool isTransitionIn);
    float ComputeTransitionOffset(float sheetHeight);
    void InitSheetTransitionAction(float offset);
    int32_t GetSubWindowId();

    OffsetF GetSheetArrowOffset() const
    {
        return arrowOffset_;
    }

    float GetFitContentHeight();

    bool WillSpringBack() const
    {
        return isSpringBack_;
    }

    void SetShowState(bool show)
    {
        show_ = show;
    }

    bool GetShowState() const
    {
        return show_;
    }

    void SetIsDragging(bool isDrag)
    {
        isDrag_ = isDrag;
    }

    bool IsDragging() const
    {
        return isDrag_;
    }

    void UpdateMaskBackgroundColor();

    void UpdateMaskBackgroundColorRender();

    Color GetMaskBackgroundColor() const
    {
        return sheetMaskColor_;
    }

    void InitFoldState()
    {
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        container->InitIsFoldable();
        if (container->IsFoldable()) {
            currentFoldStatus_ = container->GetCurrentFoldStatus();
        }
    }

    bool IsFoldStatusChanged()
    {
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, false);
        if (!container->IsFoldable()) {
            return false;
        }
        auto foldStatus = container->GetCurrentFoldStatus();
        TAG_LOGI(AceLogTag::ACE_SHEET, "newFoldStatus: %{public}d, currentFoldStatus: %{public}d.",
            static_cast<int32_t>(foldStatus), static_cast<int32_t>(currentFoldStatus_));
        if (foldStatus != currentFoldStatus_) {
            currentFoldStatus_ = foldStatus;
            return true;
        }
        return false;
    }

    void UpdateHoverModeChangedCallbackId(const std::optional<int32_t>& id)
    {
        hoverModeChangedCallbackId_ = id;
    }

    bool HasHoverModeChangedCallbackId()
    {
        return hoverModeChangedCallbackId_.has_value();
    }

    // Get ScrollHeight before avoid keyboard
    float GetScrollHeight() const
    {
        auto titleHeight = GetFirstChildHeight();
        if (sheetType_ == SheetType::SHEET_CENTER) {
            return centerHeight_ - titleHeight;
        }
        return height_ - titleHeight;
    }

    float GetFirstChildHeight() const;

    RefPtr<OverlayManager> GetOverlayManager();
    RefPtr<FrameNode> GetOverlayRoot();
    float GetRootOffsetYToWindow();

    bool IsAvoidingKeyboard() const
    {
        return Positive(keyboardHeight_);
    }

    bool IsTypeNeedAvoidAiBar();
    void IsNeedPlayTransition(const SheetStyle& sheetStyle);

    RefPtr<FrameNode> GetFirstFrameNodeOfBuilder() const;
    void GetBuilderInitHeight();
    void ChangeSheetPage(float height);
    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;

    uint32_t GetDetentsIndex() const
    {
        return detentsFinalIndex_;
    }
    bool IsScrollOutOfBoundary();
    RefPtr<FrameNode> GetScrollNode();

    void UpdateSheetType()
    {
        sheetType_ = GetSheetType();
    }

    // Used for isolation of SHEET_BOTTOMLANDSPACE after version 12, such as support for height setting callback,
    // support for detents setting and callback for SHEET_BOTTOMLANDSPACE
    bool IsSheetBottomStyle()
    {
        // sheetType_ is invalid before onModifyDone
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            return sheetType_ == SheetType::SHEET_BOTTOM || sheetType_ == SheetType::SHEET_BOTTOM_FREE_WINDOW ||
                   sheetType_ == SheetType::SHEET_BOTTOMLANDSPACE;
        }
        return sheetType_ == SheetType::SHEET_BOTTOM || sheetType_ == SheetType::SHEET_BOTTOM_FREE_WINDOW;
    }

    // If has dispute about version isolation, suggest use the following. And it does not support SHEET_BOTTOM_OFFSET
    bool IsSheetBottom()
    {
        auto sheetType = GetSheetType();
        return !(sheetType == SheetType::SHEET_CENTER || sheetType == SheetType::SHEET_POPUP ||
                 sheetType == SheetType::SHEET_BOTTOM_OFFSET);
    }

    // Nestable Scroll
    Axis GetAxis() const override
    {
        return Axis::VERTICAL;
    }
    ScrollResult HandleScroll(float scrollOffset, int32_t source,
        NestedState state = NestedState::GESTURE, float velocity = 0.f) override;
    void OnScrollStartRecursive(
        WeakPtr<NestableScrollContainer> child, float position, float dragVelocity = 0.0f) override;
    void OnScrollEndRecursive (const std::optional<float>& velocity) override;
    bool HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child = nullptr) override;
    ScrollResult HandleScrollWithSheet(float scrollOffset);
    Shadow GetShadowFromTheme(ShadowStyle shadowStyle);
    void SetShadowStyle(bool isFocused);
    bool IsCurSheetNeedHalfFoldHover();
    float GetMaxSheetHeightBeforeDragUpdate();
    float GetSheetHeightBeforeDragUpdate();
    void FireHoverModeChangeCallback();
    void InitFoldCreaseRegion();
    Rect GetFoldScreenRect() const;
    void RecoverHalfFoldOrAvoidStatus();
    bool UpdateAccessibilityDetents(float height);
    void CalculateSheetRadius(BorderRadiusProperty& sheetRadius);

    void UpdateSheetPopupInfo(const SheetPopupInfo& sheetPopupInfo)
    {
        sheetPopupInfo_ = sheetPopupInfo;
    }

    SheetPopupInfo GetSheetPopupInfo() const
    {
        return sheetPopupInfo_;
    }

    bool UpdateIndexByDetentSelection(const SheetStyle& sheetStyle, bool isFirstTransition);

    bool GetIsPlayTransition() const
    {
        return isPlayTransition_;
    }
    void OnFontScaleConfigurationUpdate() override;

    void FireCommonCallback();

protected:
    void OnDetachFromFrameNode(FrameNode* sheetNode) override;

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    void OnColorConfigurationUpdate() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAvoidInfoChange(const ContainerModalAvoidInfo& info) override;
    void RegisterAvoidInfoChangeListener(const RefPtr<FrameNode>& hostNode);
    void UnRegisterAvoidInfoChangeListener(FrameNode* hostNode);

    void RegisterHoverModeChangeCallback();
    void InitScrollProps();
    void InitPageHeight();
    void TranslateTo(float height);
    void SetColumnMinSize(bool reset = false);
    void UpdateDragBarStatus();
    void UpdateCloseIconStatus();
    void UpdateTitlePadding();
    RefPtr<FrameNode> GetTitleNode();
    float GetCloseIconPosX(const SizeF& sheetSize, const RefPtr<SheetTheme>& sheetTheme);
    void UpdateSheetTitle();
    void UpdateFontScaleStatus();
    RefPtr<RenderContext> GetRenderContext();
    bool PostTask(const TaskExecutor::Task& task, const std::string& name);
    void CheckSheetHeightChange();
    float GetWrapperHeight();
    bool SheetHeightNeedChanged();
    void InitSheetDetents();
    void InitDetents(SheetStyle sheetStyle, float height, double mediumSize, float largeHeightOfTheme,
        double largeHeight);
    void HandleFitContontChange(float height);
    void ChangeSheetHeight(float height);
    void StartSheetTransitionAnimation(const AnimationOption& option, bool isTransitionIn, float offset);
    void DismissSheetShadow(const RefPtr<RenderContext>& context);
    void ClipSheetNode();
    void CreatePropertyCallback();
    void ComputeDetentsPos(float currentSheetHeight, float& upHeight, float& downHeight, uint32_t& detentsLowerPos,
        uint32_t& detentsUpperPos);
    void IsCustomDetentsChanged(SheetStyle sheetStyle);
    void CalculateAloneSheetRadius(
        std::optional<Dimension>& sheetRadius, const std::optional<Dimension>& sheetStyleRadius);
    std::string GetPopupStyleSheetClipPath(const SizeF& sheetSize, const BorderRadiusProperty& sheetRadius);
    std::string GetPopupStyleSheetClipPathNew(const SizeF& sheetSize, const BorderRadiusProperty& sheetRadius);
    std::string GetCenterStyleSheetClipPath(SizeF sheetSize, Dimension sheetRadius);
    std::string GetBottomStyleSheetClipPath(SizeF sheetSize, Dimension sheetRadius);
    std::string MoveTo(double x, double y);
    std::string LineTo(double x, double y);
    std::string ArcTo(double rx, double ry, double rotation, int32_t arc_flag, double x, double y);
    void DismissTransition(bool isTransitionIn, float dragVelocity = 0.0f);
    float GetTopAreaInWindow() const;
    void MarkSheetPageNeedRender();
    void SetSheetOuterBorderWidth(const RefPtr<SheetTheme>& sheetTheme, const NG::SheetStyle& sheetStyle);
    PipelineContext* GetSheetMainPipeline() const;
    float GetBottomSafeArea();
    void AvoidKeyboardBySheetMode(bool forceAvoid = false);
    bool AvoidKeyboardBeforeTranslate();
    void AvoidKeyboardAfterTranslate(float height);
    void DecreaseScrollHeightInSheet(float decreaseHeight);
    bool IsResizeWhenAvoidKeyboard();
    float GetRadio() const
    {
        return sheetType_ == SheetType::SHEET_BOTTOM_OFFSET ? 5.0f : 1.848f;
    }
    void ResetClipShape();
    void UpdateSheetWhenSheetTypeChanged();
    void GetCurrentScrollHeight();
    void RecoverAvoidKeyboardStatus();
    void RecoverScrollOrResizeAvoidStatus();

    // broadcast
    void SendTextUpdateEvent();
    void SendSelectedEvent();
    void HandleFollowAccessibilityEvent(float currHeight);
    void HandleDragEndAccessibilityEvent();
    void RegisterElementInfoCallBack();
    uint32_t GetCurrentBroadcastDetentsIndex();

    void GetArrowOffsetByPlacement(const RefPtr<SheetPresentationLayoutAlgorithm>& layoutAlgorithm);
    std::string DrawClipPathBottom(const SizeF&, const BorderRadiusProperty&);
    std::string DrawClipPathTop(const SizeF&, const BorderRadiusProperty&);
    std::string DrawClipPathLeft(const SizeF&, const BorderRadiusProperty&);
    std::string DrawClipPathRight(const SizeF&, const BorderRadiusProperty&);
    
    uint32_t broadcastPreDetentsIndex_ = 0;
    SheetAccessibilityDetents sheetDetents_ = SheetAccessibilityDetents::HIGH;

    uint32_t keyboardHeight_ = 0;
    int32_t targetId_ = -1;
    SheetKey sheetKey_;
    std::optional<int32_t> titleId_;
    std::optional<int32_t> subtitleId_;
    std::string targetTag_;
    std::function<void(const std::string&)> callback_;
    std::function<void()> onDisappear_;
    std::function<void()> onWillDisappear_;
    std::function<void()> shouldDismiss_;
    std::function<void(const int32_t info)> onWillDismiss_;
    std::function<void()> sheetSpringBack_;
    std::function<void(const float)> onHeightDidChange_;
    std::function<void(const float)> onDetentsDidChange_;
    std::function<void(const float)> onWidthDidChange_;
    std::function<void(const float)> onTypeDidChange_;
    std::function<void()> onAppear_;
    RefPtr<PanEvent> panEvent_;
    OffsetF arrowOffset_;
    float currentOffset_ = 0.0f;

    float preDidHeight_ = 0.0f;
    float sheetHeightUp_ = 0.0f; // sheet offset to move up when avoiding keyboard
    float height_ = 0.0f; // sheet height, start from the bottom, before avoiding keyboard
    float sheetHeight_ = 0.0f; // sheet frameSize Height
    float wrapperHeight_ = 0.0f; // sheetWrapper frameSize Height
    float pageHeight_ = 0.0f; // root Height, = maxSize.Height()
    float scrollHeight_ = 0.0f;
    float preWidth_ = 0.0f;
    int32_t preType_ = -1;
    float sheetTopSafeArea_ = .0f;
    bool isExecuteOnDisappear_ = false;
    bool windowRotate_ = false;
    bool isScrolling_ = false;
    float builderHeight_ = 0.0f;
    float sheetMaxHeight_ = 0.0f; // start from the bottom, pageHeight - sheetTopSafeArea
    float sheetMaxWidth_ = 0.0f;
    float centerHeight_ = 0.0f; // node height, not translate height
    float sheetFitContentHeight_ = 0.0f;
    float sheetOffsetX_ = 0.0f;
    float sheetOffsetY_ = 0.0f;
    float bottomOffsetX_ = 0.0f; // offset x with SHEET_BOTTOM_OFFSET
    float bottomOffsetY_ = 0.0f; // offset y with SHEET_BOTTOM_OFFSET, <= 0
    bool isFirstInit_ = true;
    bool isAnimationBreak_ = false;
    bool isAnimationProcess_ = false;
    bool isDismissProcess_ = false;
    SheetType sheetType_ = SheetType::SHEET_BOTTOM;
    bool windowChanged_ = false;
    bool isDirectionUp_ = true;
    bool topSafeAreaChanged_ = false;
    ScrollSizeMode scrollSizeMode_ = ScrollSizeMode::FOLLOW_DETENT;
    SheetEffectEdge sheetEffectEdge_ = SheetEffectEdge::ALL;

    //record sheet sored detent index
    uint32_t detentsIndex_ = 0;

    //record sheet unsoreddetent index
    uint32_t detentsFinalIndex_ = 0;
    std::string sheetThemeType_ = "auto";

    WeakPtr<OverlayManager> overlayManager_ = nullptr;

    std::vector<SheetHeight> preDetents_;
    std::vector<float> sheetDetentHeight_;
    std::vector<float> unSortedSheetDentents_;
    std::vector<Rect> currentFoldCreaseRegion_;

    std::shared_ptr<AnimationUtils::Animation> animation_;
    std::optional<int32_t> foldDisplayModeChangedCallbackId_;
    std::optional<int32_t> hoverModeChangedCallbackId_;

    bool show_ = true;
    bool isDrag_ = false;
    FoldStatus currentFoldStatus_ = FoldStatus::UNKNOWN;
    bool isNeedProcessHeight_ = false;
    bool isSheetNeedScroll_ = false; // true if Sheet is ready to receive scroll offset.
    bool isSheetPosChanged_ = false; // UpdateTransformTranslate end
    bool isSpringBack_ = false; // sheet rebound

    double start_ = 0.0; // start position of detents changed
    RefPtr<NodeAnimatablePropertyFloat> property_;

    ACE_DISALLOW_COPY_AND_MOVE(SheetPresentationPattern);

    float preDetentsHeight_ = 0.0f;
    std::optional<SizeT<int32_t>> windowSize_;
    float scale_ = 1.0;

    Color sheetMaskColor_ = Color::TRANSPARENT;
    SheetKeyboardAvoidMode keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    float resizeDecreasedHeight_ = 0.f;
    bool isPlayTransition_ = false;
    Placement finalPlacement_ = Placement::BOTTOM;
    bool showArrow_ = true;
    SheetArrowPosition arrowPosition_ = SheetArrowPosition::NONE;
    SheetPopupInfo sheetPopupInfo_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_PRESENTATION_PATTERN_H
