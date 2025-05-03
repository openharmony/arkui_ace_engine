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
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/animation/animation_util.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t API_VERSION_9 = 9;
constexpr Dimension ADAPT_TOAST_MIN_FONT_SIZE = 12.0_fp;
constexpr Dimension LIMIT_SPACING = 8.0_vp;

// get main window's pipeline
RefPtr<PipelineContext> GetMainPipelineContext()
{
    auto containerId = Container::CurrentId();
    RefPtr<PipelineContext> context;
    if (containerId >= MIN_SUBCONTAINER_ID) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
        auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);
        CHECK_NULL_RETURN(parentContainer, nullptr);
        context = AceType::DynamicCast<PipelineContext>(parentContainer->GetPipelineContext());
    } else {
        context = PipelineContext::GetCurrentContextSafelyWithCheck();
    }
    return context;
}
} // namespace

void ToastPattern::InitWrapperRect(LayoutWrapper* layoutWrapper, const RefPtr<ToastLayoutProperty>& toastProps)
{
    InitUIExtensionHostWindowRect();

    // init toast wrapper rect with different settings.
    auto pipelineContext =
        IsDefaultToast() ? PipelineContext::GetCurrentContextSafelyWithCheck() : GetMainPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    CHECK_NULL_VOID(layoutWrapper);
    auto safeAreaInsets = OverlayManager::GetSafeAreaInsets(layoutWrapper->GetHostNode());
    float safeAreaTop = safeAreaInsets.top_.Length();
    auto toastProp = DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(toastProp);
    Alignment alignment = toastProp->GetToastAlignmentValue(Alignment::BOTTOM_CENTER);
    if (alignment == Alignment::TOP_LEFT || alignment == Alignment::TOP_CENTER || alignment == Alignment::TOP_RIGHT) {
        auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
        CHECK_NULL_VOID(toastTheme);
        safeAreaTop += toastTheme->GetTop().ConvertToPx();
    }
    const auto& safeArea = toastProps->GetSafeAreaInsets();
    limitPos_ = Dimension(GreatNotEqual(safeAreaTop, 0) ? safeAreaTop : LIMIT_SPACING.ConvertToPx());
    // Default Toast need to avoid keyboard, but the Top mode doesn't need.
    auto useOldSafeArea = safeArea && Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN);
    float safeAreaBottom = useOldSafeArea ? safeArea->bottom_.Length() : safeAreaInsets.bottom_.Length();

    if (IsSystemTopMost()) {
        wrapperRect_ = pipelineContext->GetDisplayWindowRectInfo();
        auto windowSize = GetSystemTopMostSubwindowSize();
        wrapperRect_.SetRect(0, safeAreaTop, static_cast<double>(windowSize.Width()),
            static_cast<double>(windowSize.Height()) - safeAreaTop - safeAreaBottom);
    } else if (IsAlignedWithHostWindow()) {
        wrapperRect_ = uiExtensionHostWindowRect_;
        wrapperRect_.SetRect(wrapperRect_.Left(), safeAreaTop,
            uiExtensionHostWindowRect_.Width(), uiExtensionHostWindowRect_.Height() - safeAreaTop - safeAreaBottom);
    } else {
        wrapperRect_ = pipelineContext->GetDisplayWindowRectInfo();
        wrapperRect_.SetRect(wrapperRect_.Left(), safeAreaTop,
            pipelineContext->GetRootWidth(), pipelineContext->GetRootHeight() - safeAreaTop - safeAreaBottom);
    }
    
    isHoverMode_ = pipelineContext->IsHalfFoldHoverStatus();
    if (isHoverMode_ && toastInfo_.enableHoverMode) {
        auto safeAreaManager = pipelineContext->GetSafeAreaManager();
        CHECK_NULL_VOID(safeAreaManager);
        UpdateHoverModeRect(toastProps, safeAreaManager, safeAreaTop, safeAreaBottom);
    }
}

void ToastPattern::InitUIExtensionHostWindowRect()
{
    if (!IsAlignedWithHostWindow()) {
        uiExtensionHostWindowRect_ = Rect();
        return;
    }

    auto currentId = Container::CurrentId();
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
        container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_VOID(container);
    }

    if (container->IsUIExtensionWindow()) {
        auto toastSubwindow = SubwindowManager::GetInstance()->GetToastSubwindow(currentId);
        CHECK_NULL_VOID(toastSubwindow);
        uiExtensionHostWindowRect_ = toastSubwindow->GetUIExtensionHostWindowRect();
    }
}

void ToastPattern::UpdateHoverModeRect(const RefPtr<ToastLayoutProperty>& toastProps,
    const RefPtr<SafeAreaManager>& safeAreaManager, float safeAreaTop, float safeAreaBottom)
{
    auto hoverModeArea = toastProps->GetHoverModeAreaValue(HoverModeAreaType::TOP_SCREEN);
    auto container = Container::CurrentSafelyWithCheck();
    auto displayInfo = container->GetDisplayInfo();
    auto foldCreaseRects = displayInfo->GetCurrentFoldCreaseRegion();
    float foldCreaseTop = 0.0f;
    float foldCreaseBottom = 0.0f;
    if (!foldCreaseRects.empty()) {
        auto foldCrease = foldCreaseRects.front();
        foldCreaseTop = foldCrease.Top();
        foldCreaseBottom = foldCrease.Bottom();
    }
    bool isKeyboardShow = false;
    auto showMode = ToastShowMode::DEFAULT;
    switch (hoverModeArea) {
        case HoverModeAreaType::TOP_SCREEN:
            wrapperRect_.SetRect(wrapperRect_.Left(), safeAreaTop, wrapperRect_.Width(), foldCreaseTop - safeAreaTop);
            break;
        case HoverModeAreaType::BOTTOM_SCREEN:
            isKeyboardShow = safeAreaManager->GetKeyboardInset().IsValid();
            showMode = toastProps->GetShowModeValue(ToastShowMode::DEFAULT);
            // if keyboard is show, wrapper rect change to the up half screen.
            if (isKeyboardShow && showMode != ToastShowMode::SYSTEM_TOP_MOST) {
                wrapperRect_.SetRect(wrapperRect_.Left(), safeAreaTop,
                    wrapperRect_.Width(), foldCreaseTop - safeAreaTop);
            } else {
                wrapperRect_.SetRect(wrapperRect_.Left(), foldCreaseBottom,
                    wrapperRect_.Width(), wrapperRect_.Height() - foldCreaseBottom + safeAreaTop);
            }
            break;
        default:
            break;
    }
}

void ToastPattern::FoldStatusChangedAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.35f, 1.0f, 0.0f);
    option.SetCurve(curve);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    AnimationUtils::Animate(option, [host, context]() {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        context->FlushUITasks();
    });
}

bool ToastPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& changeConfig)
{
    CHECK_NULL_RETURN(dirty, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = IsDefaultToast() ? host->GetContextRefPtr() : GetMainPipelineContext();
    CHECK_NULL_RETURN(context, false);
    auto toastNode = dirty->GetHostNode();
    CHECK_NULL_RETURN(toastNode, false);
    auto toastContext = toastNode->GetRenderContext();
    CHECK_NULL_RETURN(toastContext, false);
    auto dialogTheme = context->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, false);
    expandDisplay_ = dialogTheme->GetExpandDisplay() || IsShowInFreeMultiWindow();
    OffsetT<Dimension> offset { GetOffsetX(dirty), GetOffsetY(dirty) };
    // show in the float subwindow
    if (IsAlignedWithHostWindow() && expandDisplay_) {
        OffsetT<Dimension> hostWindowOffset = { Dimension(uiExtensionHostWindowRect_.GetOffset().GetX()),
            Dimension(uiExtensionHostWindowRect_.GetOffset().GetY()) };
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast hostWindowOffset, x: %{public}.2f vp, y: %{public}.2f vp",
            hostWindowOffset.GetX().ConvertToVp(), hostWindowOffset.GetY().ConvertToVp());
        offset += hostWindowOffset;
    } else if (!IsSystemTopMost() && (!IsDefaultToast() && expandDisplay_)) {
        OffsetT<Dimension> displayWindowOffset = { Dimension(context->GetDisplayWindowRectInfo().GetOffset().GetX()),
            Dimension(context->GetDisplayWindowRectInfo().GetOffset().GetY()) };
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast displayWindowOffset, x: %{public}.2f vp, y: %{public}.2f vp",
            displayWindowOffset.GetX().ConvertToVp(), displayWindowOffset.GetY().ConvertToVp());
        offset += displayWindowOffset;
    }
    auto func = [toastContext, offset]() { toastContext->UpdateOffset(offset); };
    auto toastProp = DynamicCast<ToastLayoutProperty>(dirty->GetLayoutProperty());
    CHECK_NULL_RETURN(toastProp, false);
    auto showMode = toastProp->GetShowModeValue(ToastShowMode::DEFAULT);
    if (showMode == ToastShowMode::TOP_MOST) {
        auto keyboardAnimationConfig = context->GetKeyboardAnimationConfig();
        auto safeAreaManager = context->GetSafeAreaManager();
        auto keyboardHeight = safeAreaManager ? safeAreaManager->GetKeyboardInset().Length() : 0;
        if (safeAreaManager && NearEqual(keyboardHeight, 0.0f)) {
            keyboardHeight = safeAreaManager->GetRawKeyboardHeight();
        }
        AnimationOption option = AnimationUtil::CreateKeyboardAnimationOption(keyboardAnimationConfig, keyboardHeight);
        auto subContext = host->GetContextRefPtr();
        CHECK_NULL_RETURN(subContext, false);
        subContext->Animate(option, option.GetCurve(), func);
    } else {
        func();
    }
    return true;
}

Dimension ToastPattern::GetOffsetX(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, Dimension(0.0));
    auto context = IsDefaultToast() ? host->GetContextRefPtr() : GetMainPipelineContext();
    CHECK_NULL_RETURN(context, Dimension(0.0));
    auto text = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(text, Dimension(0.0));
    auto rootWidth = wrapperRect_.Width();
    auto toastProp = DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(toastProp, Dimension(0.0));
    auto textWidth = text->GetGeometryNode()->GetMarginFrameSize().Width();
    Alignment alignment = toastProp->GetToastAlignmentValue(Alignment::BOTTOM_CENTER);
    Dimension offsetX;
    if (alignment == Alignment::TOP_LEFT || alignment == Alignment::CENTER_LEFT ||
        alignment == Alignment::BOTTOM_LEFT) {
        offsetX = Dimension(0.0);
    } else if (alignment == Alignment::TOP_RIGHT || alignment == Alignment::CENTER_RIGHT ||
               alignment == Alignment::BOTTOM_RIGHT) {
        offsetX = Dimension(rootWidth - textWidth);
    } else {
        offsetX = Dimension((rootWidth - textWidth) / 2.0f);
    }
    return offsetX + toastProp->GetToastOffsetValue(DimensionOffset()).GetX();
}

Dimension ToastPattern::GetOffsetY(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto context = GetToastContext();
    CHECK_NULL_RETURN(context, Dimension(0.0));
    auto text = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(text, Dimension(0.0));
    auto rootHeight = wrapperRect_.Height();
    auto toastProp = DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(toastProp, Dimension(0.0));
    auto textHeight = text->GetGeometryNode()->GetMarginFrameSize().Height();
    Dimension offsetY;
    // Get toastBottom and update defaultBottom_
    auto toastBottom = GetBottomValue(layoutWrapper);
    if (!toastProp->HasToastAlignment()) {
        if (context->GetMinPlatformVersion() > API_VERSION_9) {
            offsetY = Dimension(rootHeight - toastBottom - textHeight);
        } else {
            offsetY = Dimension(rootHeight - toastBottom);
        }
    } else {
        Alignment alignment = toastProp->GetToastAlignmentValue(Alignment::BOTTOM_CENTER);
        if (alignment == Alignment::TOP_LEFT || alignment == Alignment::TOP_CENTER ||
            alignment == Alignment::TOP_RIGHT) {
            offsetY = Dimension(0.0f);
        } else if (alignment == Alignment::CENTER_LEFT || alignment == Alignment::CENTER ||
                   alignment == Alignment::CENTER_RIGHT) {
            offsetY = Dimension((rootHeight - textHeight) / 2.0f);
        } else {
            offsetY = Dimension(rootHeight - textHeight);
        }
    }
    // add toast wrapper rect's offsetY.
    offsetY += Dimension(wrapperRect_.Top());
    bool needResizeBottom = false;
    AdjustOffsetForKeyboard(offsetY, defaultBottom_.ConvertToPx(), textHeight, needResizeBottom);
    needResizeBottom = needResizeBottom || (!toastProp->HasToastAlignment() && toastInfo_.bottom.empty());
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) && needResizeBottom &&
        !GreatNotEqual(offsetY.Value(), 0)) {
        return limitPos_ + toastProp->GetToastOffsetValue(DimensionOffset()).GetY();
    }
    return offsetY + toastProp->GetToastOffsetValue(DimensionOffset()).GetY();
}

void ToastPattern::AdjustOffsetForKeyboard(
    Dimension& offsetY, double toastBottom, float textHeight, bool& needResizeBottom)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = IsDefaultToast() ? host->GetContextRefPtr() : GetMainPipelineContext();
    CHECK_NULL_VOID(context);
    auto safeAreaManager = context->GetSafeAreaManager();
    auto keyboardInset = safeAreaManager ? safeAreaManager->GetKeyboardInset().Length() : 0;
    if (safeAreaManager && NearEqual(keyboardInset, 0.0f)) {
        keyboardInset = safeAreaManager->GetRawKeyboardHeight();
    }
    auto deviceHeight = context->GetRootHeight();
    auto keyboardOffset = deviceHeight - keyboardInset;
    if (IsAlignedWithHostWindow() && GreatNotEqual(keyboardInset, 0)) {
        deviceHeight = uiExtensionHostWindowRect_.Height();

        auto currentId = Container::CurrentId();
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        if (container->IsSubContainer()) {
            currentId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
            container = AceEngine::Get().GetContainer(currentId);
            CHECK_NULL_VOID(container);
        }
        if (container->IsUIExtensionWindow()) {
            auto toastSubwindow = SubwindowManager::GetInstance()->GetToastSubwindow(currentId);
            if (toastSubwindow) {
                auto parentWindowRect = toastSubwindow->GetParentWindowRect();
                keyboardOffset =
                    deviceHeight - keyboardInset - uiExtensionHostWindowRect_.Bottom() + parentWindowRect.Bottom();
            }
        }
    }
    if (((IsDefaultToast() && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) ||
            IsTopMostToast()) &&
        GreatNotEqual(keyboardInset, 0) && (offsetY.Value() + textHeight > keyboardOffset)) {
        needResizeBottom = true;
        offsetY = Dimension(keyboardOffset - toastBottom - textHeight);
    }
    TAG_LOGD(AceLogTag::ACE_OVERLAY,
        "toast device height: %{public}.2f, keyboardOffset: %{public}d, "
        "textHeight: %{public}.2f, offsetY: %{public}.2f",
        deviceHeight, (uint32_t)keyboardOffset, textHeight, offsetY.Value());
}

double ToastPattern::GetBottomValue(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    // Obtain the height relative to the main window
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto pipeline = IsDefaultToast() ? host->GetContextRefPtr() : GetMainPipelineContext();
    CHECK_NULL_RETURN(pipeline, 0.0);
    auto rootHeight = Dimension(wrapperRect_.Height());
    auto toastTheme = pipeline->GetTheme<ToastTheme>();
    CHECK_NULL_RETURN(toastTheme, 0.0);

    auto toastProp = DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(toastProp, 0.0);
    defaultBottom_ = toastTheme->GetBottom();
    auto toastBottom = toastProp->GetBottomValue(defaultBottom_);
    if (toastBottom.Unit() == DimensionUnit::PERCENT) {
        toastBottom = rootHeight * toastBottom.Value();
    }
    return GreatOrEqual(toastBottom.ConvertToPx(), 0.0) ? toastBottom.ConvertToPx()
                                                        : toastTheme->GetBottom().ConvertToPx();
}

void ToastPattern::BeforeCreateLayoutWrapper()
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        PopupBasePattern::BeforeCreateLayoutWrapper();
    }

    auto toastNode = GetHost();
    CHECK_NULL_VOID(toastNode);
    auto pipelineContext = IsDefaultToast() ? toastNode->GetContextRefPtr() : GetMainPipelineContext();
    if (!pipelineContext) {
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast get pipelineContext failed");
        return;
    }

    auto textNode = DynamicCast<FrameNode>(toastNode->GetFirstChild());
    CHECK_NULL_VOID(textNode);
    UpdateTextSizeConstraint(textNode);
}

void ToastPattern::UpdateToastSize(const RefPtr<FrameNode>& toast)
{
    CHECK_NULL_VOID(toast);
    auto toastProperty = toast->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_VOID(toastProperty);
    auto rootWidth = Dimension(wrapperRect_.Width());
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto limitWidth = Dimension(GetTextMaxWidth());
        toastProperty->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(limitWidth), std::nullopt));
    } else {
        toastProperty->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(rootWidth), std::nullopt));
    }
}

void ToastPattern::UpdateTextSizeConstraint(const RefPtr<FrameNode>& text)
{
    CHECK_NULL_VOID(text);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto gridColumnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::TOAST);
    auto parent = gridColumnInfo->GetParent();
    if (parent) {
        parent->BuildColumnWidth(context->GetRootWidth());
    }
    auto maxWidth = Dimension(gridColumnInfo->GetMaxWidth());
    auto textLayoutProperty = text->GetLayoutProperty();
    CHECK_NULL_VOID(textLayoutProperty);

    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    auto minWidth = Dimension(toastTheme->GetMinWidth().ConvertToPx());
    auto minHeight = Dimension(toastTheme->GetMinHeight().ConvertToPx());
    textLayoutProperty->UpdateCalcMinSize(CalcSize(NG::CalcLength(minWidth), NG::CalcLength(minHeight)));

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto limitWidth = Dimension(GetTextMaxWidth());
        auto limitHeight = GetTextMaxHeight();
        textLayoutProperty->UpdateCalcMaxSize(
            CalcSize(NG::CalcLength(limitWidth), NG::CalcLength(Dimension(limitHeight))));
        CHECK_NULL_VOID(textNode_);
        auto textProperty = textNode_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textProperty);
        auto toastMaxFontSize = toastTheme->GetTextStyle().GetFontSize();
        textProperty->UpdateAdaptMaxFontSize(toastMaxFontSize);
        textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_MIN_FONT_SIZE);
        textProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);

        auto textLineHeight = GetTextLineHeight(text);
        if (textLineHeight > 0) {
            auto maxLines = static_cast<int32_t>(limitHeight / textLineHeight);
            textProperty->UpdateMaxLines(maxLines);
        }
    } else {
        textLayoutProperty->UpdateCalcMaxSize(CalcSize(NG::CalcLength(maxWidth), std::nullopt));
    }
}

void ToastPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textContext = host->GetRenderContext();
    CHECK_NULL_VOID(textContext);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    auto textColor = toastTheme->GetTextStyle().GetTextColor();
    CHECK_NULL_VOID(textNode_);
    auto textLayoutProperty = textNode_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto toastInfo = GetToastInfo();
    textLayoutProperty->UpdateTextColor(toastInfo.textColor.value_or(textColor));
    host->SetNeedCallChildrenUpdate(false);
    ToastView::UpdateToastNodeStyle(host);
}

void ToastPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto containerId = Container::CurrentId();
    auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
    auto pipeline = parentContainerId < 0 ? host->GetContextRefPtr() : PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto callbackId =
        pipeline->RegisterFoldDisplayModeChangedCallback([parentContainerId](FoldDisplayMode foldDisplayMode) {
            if (foldDisplayMode == FoldDisplayMode::FULL || foldDisplayMode == FoldDisplayMode::MAIN) {
                TAG_LOGI(AceLogTag::ACE_OVERLAY, "Window status changes, displayMode is %{public}d", foldDisplayMode);
                SubwindowManager::GetInstance()->ResizeWindowForFoldStatus(parentContainerId);
            }
        });
    UpdateFoldDisplayModeChangedCallbackId(callbackId);
    auto halfFoldHoverCallbackId =
        pipeline->RegisterHalfFoldHoverChangedCallback([weak = WeakClaim(this)](bool isHoverMode) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (isHoverMode != pattern->isHoverMode_) {
                pattern->FoldStatusChangedAnimation();
            }
        });
    UpdateHalfFoldHoverChangedCallbackId(halfFoldHoverCallbackId);
}

void ToastPattern::OnDetachFromFrameNode(FrameNode* node)
{
    auto containerId = Container::CurrentId();
    auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
    auto current_context = PipelineContext::GetCurrentContextSafelyWithCheck();
    auto pipeline = parentContainerId < 0 ? current_context : PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    if (HasFoldDisplayModeChangedCallbackId()) {
        pipeline->UnRegisterFoldDisplayModeChangedCallback(foldDisplayModeChangedCallbackId_.value_or(-1));
    }
    if (HasHalfFoldHoverChangedCallbackId()) {
        pipeline->UnRegisterHalfFoldHoverChangedCallback(halfFoldHoverChangedCallbackId_.value_or(-1));
    }
}

double ToastPattern::GetTextMaxHeight()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto pipelineContext = IsDefaultToast() ? host->GetContextRefPtr() : GetMainPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0);
    double deviceHeight = 0.0;
    if (IsSystemTopMost()) {
        auto windowSize = GetSystemTopMostSubwindowSize();
        deviceHeight = static_cast<double>(windowSize.Height());
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "SystemTopMost toast get device height: %{public}f.", deviceHeight);
    } else if (IsAlignedWithHostWindow()) {
        deviceHeight = uiExtensionHostWindowRect_.Height();
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast in UIExtension subwindow, device height: %{public}f.", deviceHeight);
    } else {
        deviceHeight = pipelineContext->GetRootHeight();
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast get device height: %{public}f.", deviceHeight);
    }
    if (LessOrEqual(deviceHeight, 0.0)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Device height is invalid when show toast.");
        deviceHeight = static_cast<double>(SystemProperties::GetDeviceHeight());
    }
    auto safeAreaInsets = OverlayManager::GetSafeAreaInsets(host);
    auto bottom = safeAreaInsets.bottom_.Length();
    auto top = safeAreaInsets.top_.Length();
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    CHECK_NULL_RETURN(toastTheme, 0.0);
    auto toastLimitHeightRatio = toastTheme->GetToastLimitHeightRatio();
    auto maxHeight = (deviceHeight - bottom - top) * toastLimitHeightRatio;

    maxHeight = GreatOrEqual(maxHeight, 0.0) ? maxHeight : 0.0;
    return maxHeight;
}

double ToastPattern::GetTextMaxWidth()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto pipelineContext = IsDefaultToast() ? host->GetContextRefPtr() : GetMainPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0);
    double deviceWidth = 0.0;
    if (IsSystemTopMost()) {
        auto windowSize = GetSystemTopMostSubwindowSize();
        deviceWidth = static_cast<double>(windowSize.Width());
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "SystemTopMost toast get device width: %{public}f.", deviceWidth);
    } else if (IsAlignedWithHostWindow()) {
        deviceWidth = uiExtensionHostWindowRect_.Width();
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast in UIExtension subwindow, device width: %{public}f.", deviceWidth);
    } else {
        deviceWidth = pipelineContext->GetRootWidth();
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast get device width: %{public}f.", deviceWidth);
    }
    if (LessOrEqual(deviceWidth, 0.0)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Device width is invalid when show toast.");
        deviceWidth = static_cast<double>(SystemProperties::GetDeviceWidth());
    }
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    CHECK_NULL_RETURN(toastTheme, 0.0);
    auto marging = toastTheme->GetMarging();
    auto maxWidth = deviceWidth - marging.Left().ConvertToPx() - marging.Right().ConvertToPx();
    auto maxLimitWidth = toastTheme->GetMaxWidth();
    if (GreatNotEqual(maxWidth, maxLimitWidth.ConvertToPx())) {
        maxWidth = maxLimitWidth.ConvertToPx();
    }
    return maxWidth;
}

int32_t ToastPattern::GetTextLineHeight(const RefPtr<FrameNode>& textNode)
{
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, 0);
    auto layoutConstraint = textLayoutProperty->GetLayoutConstraint();
    auto textLayoutWrapper = textNode->CreateLayoutWrapper();
    CHECK_NULL_RETURN(textLayoutWrapper, 0);
    textLayoutWrapper->Measure(layoutConstraint);
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(textLayoutWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, 0);
    auto textLayoutAlgorithm = DynamicCast<TextLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textLayoutAlgorithm, 0);
    auto paragraph = textLayoutAlgorithm->GetSingleParagraph();
    CHECK_NULL_RETURN(paragraph, 0);
    auto paragHeight = paragraph->GetHeight();
    auto paragLineCount = paragraph->GetLineCount();
    int32_t paragLineHeight = 0;
    if (paragLineCount > 0) {
        paragLineHeight = static_cast<int32_t>(paragHeight / paragLineCount);
    }
    return paragLineHeight;
}

bool ToastPattern::IsShowInFreeMultiWindow() const
{
    auto currentId = Container::CurrentId();
    auto container = Container::Current();
    if (!container) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "container is null");
        return false;
    }
    if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
        container = AceEngine::Get().GetContainer(currentId);
        if (!container) {
            TAG_LOGW(AceLogTag::ACE_OVERLAY, "parent container is null");
            return false;
        }
    }
    return container->IsFreeMultiWindow();
}

bool ToastPattern::IsUIExtensionSubWindow() const
{
    if (IsDefaultToast()) {
        return false;
    }

    auto currentId = Container::CurrentId();
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
        container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_RETURN(container, false);
    }
    return container->IsUIExtensionWindow();
}

void ToastPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc("Message: " + toastInfo_.message);
    DumpLog::GetInstance().AddDesc("Duration: " + std::to_string(toastInfo_.duration));
    DumpLog::GetInstance().AddDesc("Bottom: " + toastInfo_.bottom);
    std::string isRightToLeft = toastInfo_.isRightToLeft ? "true" : "false";
    DumpLog::GetInstance().AddDesc("IsRightToLeft: " + isRightToLeft);
    std::string showMode = toastInfo_.showMode == ToastShowMode::DEFAULT ? "DEFAULT" : "TOP_MOST";
    DumpLog::GetInstance().AddDesc("ShowMode: " + showMode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto toastProp = DynamicCast<ToastLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(toastProp);
    if (!toastProp->HasToastAlignment()) {
        DumpLog::GetInstance().AddDesc("Alignment: NONE");
    } else {
        DumpLog::GetInstance().AddDesc(
            "Alignment: " + toastProp->GetToastAlignmentValue().GetAlignmentStr(toastProp->GetLayoutDirection()));
    }
    auto offset = toastProp->GetToastOffsetValue(DimensionOffset());
    DumpLog::GetInstance().AddDesc(
        "Offset: { dx: " + offset.GetX().ToString() + " dy: " + offset.GetY().ToString() + " }");
    std::string enableHoverMode = toastInfo_.enableHoverMode ? "true" : "false";
    DumpLog::GetInstance().AddDesc("EnableHoverMode: " + enableHoverMode);
    std::string hoverModeAreaType =
        toastInfo_.hoverModeArea == HoverModeAreaType::TOP_SCREEN ? "TOP_SCREEN" : "BOTTOM_SCREEN";
    DumpLog::GetInstance().AddDesc("HoverModeArea: " + hoverModeAreaType);
}

void ToastPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("Message", toastInfo_.message.c_str());
    json->Put("Duration", toastInfo_.duration);
    json->Put("Bottom", toastInfo_.bottom.c_str());
    json->Put("IsRightToLeft", toastInfo_.isRightToLeft ? "true" : "false");
    json->Put("ShowMode", toastInfo_.showMode == ToastShowMode::DEFAULT ? "DEFAULT" : "TOP_MOST");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto toastProp = DynamicCast<ToastLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(toastProp);
    if (!toastProp->HasToastAlignment()) {
        json->Put("Alignment", "NONE");
    } else {
        json->Put(
            "Alignment", toastProp->GetToastAlignmentValue().GetAlignmentStr(toastProp->GetLayoutDirection()).c_str());
    }
    auto offset = toastProp->GetToastOffsetValue(DimensionOffset());
    std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
    children->Put("dx", offset.GetX().ToString().c_str());
    children->Put("dy", offset.GetY().ToString().c_str());
    json->Put("Offset", children);
}

NG::SizeF ToastPattern::GetSystemTopMostSubwindowSize() const
{
    SizeF windowSize = {
        static_cast<float>(SystemProperties::GetDeviceWidth()),
        static_cast<float>(SystemProperties::GetDeviceHeight())
    };
    auto containerId = Container::CurrentId();
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    auto parentContainerId = containerId >= MIN_SUBCONTAINER_ID ?
        SubwindowManager::GetInstance()->GetParentContainerId(containerId) : containerId;
    auto subwindow = SubwindowManager::GetInstance()->GetSystemToastWindow(parentContainerId);
    if (subwindow) {
        auto rect = subwindow->GetWindowRect();
        if (GreatNotEqual(rect.Width(), 0.0f) && GreatNotEqual(rect.Height(), 0.0f)) {
            windowSize.SetWidth(rect.Width());
            windowSize.SetHeight(rect.Height());
        }
    }
    return windowSize;
}
RefPtr<PipelineContext> ToastPattern::GetToastContext()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto context = IsDefaultToast() ? host->GetContextRefPtr() : GetMainPipelineContext();
    return context;
}
} // namespace OHOS::Ace::NG
