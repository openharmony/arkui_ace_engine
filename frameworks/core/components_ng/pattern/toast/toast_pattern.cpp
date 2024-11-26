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
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "base/log/dump_log.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t API_VERSION_9 = 9;
constexpr Dimension ADAPT_TOAST_MIN_FONT_SIZE = 12.0_fp;

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
        context = PipelineContext::GetCurrentContext();
    }
    return context;
}
} // namespace

bool ToastPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& changeConfig)
{
    CHECK_NULL_RETURN(dirty, false);
    auto context = IsDefaultToast() ? PipelineContext::GetCurrentContext() : GetMainPipelineContext();
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
    if (!IsSystemTopMost() && (IsUIExtensionSubWindow() || (!IsDefaultToast() && expandDisplay_))) {
        auto nodeContext = toastNode->GetContextWithCheck();
        CHECK_NULL_RETURN(nodeContext, false);
        auto subwindowOffset = nodeContext->GetDisplayWindowRectInfo().GetOffset();
        if (!IsUIExtensionSubWindow() && (!NearEqual(subwindowOffset.GetX(), 0) ||
            !NearEqual(subwindowOffset.GetY(), 0))) {
            TAG_LOGW(AceLogTag::ACE_OVERLAY, "toast subwindow offset, x: %{public}f, y: %{public}f",
                subwindowOffset.GetX(), subwindowOffset.GetY());
        }
        OffsetT<Dimension> displayWindowOffset = { Dimension(context->GetDisplayWindowRectInfo().GetOffset().GetX() -
            subwindowOffset.GetX()), Dimension(context->GetDisplayWindowRectInfo().GetOffset().GetY() -
            subwindowOffset.GetY()) };
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
        context->Animate(option, option.GetCurve(), func);
    } else {
        func();
    }
    return true;
}

Dimension ToastPattern::GetOffsetX(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto context = IsDefaultToast() ? PipelineContext::GetCurrentContext() : GetMainPipelineContext();
    CHECK_NULL_RETURN(context, Dimension(0.0));
    auto text = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(text, Dimension(0.0));
    auto rootWidth = context->GetRootWidth();
    if (IsSystemTopMost()) {
        auto windowSize = GetSystemTopMostSubwindowSize();
        rootWidth = static_cast<double>(windowSize.Height());
    }
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
    auto context = IsDefaultToast() ? PipelineContext::GetCurrentContext() : GetMainPipelineContext();
    CHECK_NULL_RETURN(context, Dimension(0.0));
    auto text = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(text, Dimension(0.0));
    auto windowSize = GetSystemTopMostSubwindowSize();
    auto rootHeight = IsSystemTopMost() ? static_cast<double>(windowSize.Height())
                                        : context->GetRootHeight();
    auto toastProp = DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(toastProp, Dimension(0.0));
    auto textHeight = text->GetGeometryNode()->GetMarginFrameSize().Height();
    Dimension offsetY;
    auto safeAreaManager = context->GetSafeAreaManager();
    auto safeAreaOffset = safeAreaManager ? safeAreaManager->GetSafeAreaWithoutProcess().bottom_.Length() : 0;
    auto showMode = toastProp->GetShowModeValue(ToastShowMode::DEFAULT);
    auto keyboardInset = safeAreaManager ? safeAreaManager->GetKeyboardInset().Length() : 0;
    if (safeAreaManager && NearEqual(keyboardInset, 0.0f)) {
        keyboardInset = safeAreaManager->GetRawKeyboardHeight();
    }
    auto keyboardOffset = GreatNotEqual(keyboardInset, 0) ? keyboardInset : 0;
    if (showMode == ToastShowMode::DEFAULT) {
        safeAreaOffset = std::max(keyboardOffset, safeAreaOffset);
    }
    // Get toastBottom and update defaultBottom_
    auto toastBottom = GetBottomValue(layoutWrapper);
    if (!toastProp->HasToastAlignment()) {
        toastBottom_ = toastBottom;
        if (context->GetMinPlatformVersion() > API_VERSION_9) {
            offsetY = Dimension(rootHeight - toastBottom - textHeight - safeAreaOffset);
        } else {
            offsetY = Dimension(rootHeight - toastBottom);
        }
    } else {
        Alignment alignment = toastProp->GetToastAlignmentValue(Alignment::BOTTOM_CENTER);
        if (alignment == Alignment::TOP_LEFT || alignment == Alignment::TOP_CENTER ||
            alignment == Alignment::TOP_RIGHT) {
            // Top Needs Avoid System Navigation Bar
            auto safeAreaManager = context->GetSafeAreaManager();
            auto sysTop = safeAreaManager ? safeAreaManager->GetSystemSafeArea().top_.Length() : 0.0f;
            offsetY = Dimension(sysTop);
        } else if (alignment == Alignment::CENTER_LEFT || alignment == Alignment::CENTER ||
                   alignment == Alignment::CENTER_RIGHT) {
            offsetY = Dimension((rootHeight - textHeight - safeAreaOffset) / 2.0f);
        } else {
            offsetY = Dimension(rootHeight - textHeight - safeAreaOffset);
        }
    }
    //TOP_MOST Toast need to avoid keyboard
    auto deviceHeight = context->GetRootHeight();
    if (showMode == ToastShowMode::TOP_MOST && (offsetY.Value() + textHeight > deviceHeight - keyboardOffset)) {
        offsetY = Dimension(deviceHeight - keyboardOffset - defaultBottom_.ConvertToPx() -textHeight);
    }
    TAG_LOGD(AceLogTag::ACE_OVERLAY,
        "toast device height: %{public}.2f, keyboardOffset: %{public}d, "
        "textHeight: %{public}.2f, offsetY: %{public}.2f",
        deviceHeight, (uint32_t)keyboardOffset, textHeight, offsetY.Value());
    return offsetY + toastProp->GetToastOffsetValue(DimensionOffset()).GetY();
}

double ToastPattern::GetBottomValue(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    // Obtain the height relative to the main window
    auto pipeline = IsDefaultToast() ? PipelineContext::GetCurrentContext() : GetMainPipelineContext();
    CHECK_NULL_RETURN(pipeline, 0.0);
    auto rootHeight = Dimension(pipeline->GetRootHeight());
    if (IsSystemTopMost()) {
        rootHeight = Dimension(static_cast<double>(SystemProperties::GetDeviceHeight()));
    }
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
    PopupBasePattern::BeforeCreateLayoutWrapper();

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
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto rootWidth = Dimension(context->GetRootWidth());
    if (IsSystemTopMost()) {
        rootWidth = Dimension(static_cast<double>(SystemProperties::GetDeviceWidth()));
    }
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
        auto limitHeight = GetTextMaxHeight();
        textLayoutProperty->UpdateCalcMaxSize(
            CalcSize(NG::CalcLength(maxWidth), NG::CalcLength(Dimension(limitHeight))));

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
    auto textLayoutProperty = textNode_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto toastInfo = GetToastInfo();
    textLayoutProperty->UpdateTextColor(toastInfo.textColor.value_or(textColor));
    host->SetNeedCallChildrenUpdate(false);
    ToastView::UpdateToastNodeStyle(host);
}

void ToastPattern::OnAttachToFrameNode()
{
    auto containerId = Container::CurrentId();
    auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
    auto pipeline =
        parentContainerId < 0 ? PipelineContext::GetCurrentContext() : PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto callbackId =
        pipeline->RegisterFoldDisplayModeChangedCallback([parentContainerId](FoldDisplayMode foldDisplayMode) {
            if (foldDisplayMode == FoldDisplayMode::FULL || foldDisplayMode == FoldDisplayMode::MAIN) {
                TAG_LOGI(AceLogTag::ACE_OVERLAY, "Window status changes, displayMode is %{public}d", foldDisplayMode);
                SubwindowManager::GetInstance()->ResizeWindowForFoldStatus(parentContainerId);
            }
        });
    UpdateFoldDisplayModeChangedCallbackId(callbackId);
}

void ToastPattern::OnDetachFromFrameNode(FrameNode* node)
{
    auto containerId = Container::CurrentId();
    auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
    auto pipeline =
        parentContainerId < 0 ? PipelineContext::GetCurrentContext() : PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    if (HasFoldDisplayModeChangedCallbackId()) {
        pipeline->UnRegisterFoldDisplayModeChangedCallback(foldDisplayModeChangedCallbackId_.value_or(-1));
    }
}

bool ToastPattern::IsShowInFreeMultiWindow()
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

bool ToastPattern::IsUIExtensionSubWindow()
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
}

double ToastPattern::GetTextMaxHeight()
{
    auto pipelineContext = IsDefaultToast() ? PipelineContext::GetCurrentContext() : GetMainPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0);
    double deviceHeight = 0.0;
    if (IsSystemTopMost()) {
        auto windowSize = GetSystemTopMostSubwindowSize();
        deviceHeight = static_cast<double>(windowSize.Height());
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "SystemTopMost toast get device height: %{public}f.", deviceHeight);
    } else if (IsUIExtensionSubWindow()) {
        auto toastNode = GetHost();
        CHECK_NULL_RETURN(toastNode, 0.0);
        auto nodeContext = toastNode->GetContextWithCheck();
        CHECK_NULL_RETURN(nodeContext, 0.0);
        deviceHeight = nodeContext->GetDisplayWindowRectInfo().Height();
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast in UIExtension subwindow, device height: %{public}f.", deviceHeight);
    } else {
        deviceHeight = pipelineContext->GetRootHeight();
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast get device height: %{public}f.", deviceHeight);
    }
    if (LessOrEqual(deviceHeight, 0.0)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "toast get device height is invalid.");
        deviceHeight = static_cast<double>(SystemProperties::GetDeviceHeight());
    }
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    auto bottom = safeAreaManager ? safeAreaManager->GetSafeAreaWithoutProcess().bottom_.Length() : 0;
    auto top = safeAreaManager ? safeAreaManager->GetSafeAreaWithoutProcess().top_.Length() : 0;
    auto maxHeight = deviceHeight - bottom - top - toastBottom_;
    auto limitHeight = (deviceHeight - bottom - top) * 0.65;
    if (GreatNotEqual(maxHeight, limitHeight)) {
        maxHeight = limitHeight;
    }

    maxHeight = GreatOrEqual(maxHeight, 0.0) ? maxHeight : 0.0;
    return maxHeight;
}

double ToastPattern::GetTextMaxWidth()
{
    auto pipelineContext = IsDefaultToast() ? PipelineContext::GetCurrentContext() : GetMainPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0);
    double deviceWidth = 0.0;
    if (IsSystemTopMost()) {
        auto windowSize = GetSystemTopMostSubwindowSize();
        deviceWidth = static_cast<double>(windowSize.Width());
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "SystemTopMost toast get device width: %{public}f.", deviceWidth);
    } else if (IsUIExtensionSubWindow()) {
        auto toastNode = GetHost();
        CHECK_NULL_RETURN(toastNode, 0.0);
        auto nodeContext = toastNode->GetContextWithCheck();
        CHECK_NULL_RETURN(nodeContext, 0.0);
        deviceWidth = nodeContext->GetDisplayWindowRectInfo().Width();
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast in UIExtension subwindow, device width: %{public}f.", deviceWidth);
    } else {
        deviceWidth = pipelineContext->GetRootWidth();
        TAG_LOGD(AceLogTag::ACE_OVERLAY, "toast get device width: %{public}f.", deviceWidth);
    }
    if (LessOrEqual(deviceWidth, 0.0)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "toast get device width is invalid.");
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
        auto rect = subwindow->GetRect();
        if (GreatNotEqual(rect.Width(), 0.0f) && GreatNotEqual(rect.Height(), 0.0f)) {
            windowSize.SetWidth(rect.Width());
            windowSize.SetHeight(rect.Height());
        }
    }
    return windowSize;
}
} // namespace OHOS::Ace::NG
