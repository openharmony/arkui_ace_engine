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

#include "core/components_ng/pattern/toast/toast_layout_algorithm.h"

#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr Dimension LIMIT_SPACING = 8.0_vp;
} // namespace
        
void UpdateToastAlign(int32_t& alignment)
{
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (alignment == static_cast<int32_t>(ToastAlignment::TOP_START)) {
        if (isRtl) {
            alignment = static_cast<int32_t>(ToastAlignment::TOP_END);
        }
    } else if (alignment == static_cast<int32_t>(ToastAlignment::TOP_END)) {
        if (isRtl) {
            alignment = static_cast<int32_t>(ToastAlignment::TOP_START);
        }
    } else if (alignment == static_cast<int32_t>(ToastAlignment::CENTER_START)) {
        if (isRtl) {
            alignment = static_cast<int32_t>(ToastAlignment::CENTER_END);
        }
    } else if (alignment == static_cast<int32_t>(ToastAlignment::CENTER_END)) {
        if (isRtl) {
            alignment = static_cast<int32_t>(ToastAlignment::CENTER_START);
        }
    } else if (alignment == static_cast<int32_t>(ToastAlignment::BOTTOM_START)) {
        if (isRtl) {
            alignment = static_cast<int32_t>(ToastAlignment::BOTTOM_END);
        }
    } else if (alignment == static_cast<int32_t>(ToastAlignment::BOTTOM_END)) {
        if (isRtl) {
            alignment = static_cast<int32_t>(ToastAlignment::BOTTOM_START);
        }
    }
}

void ToastLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto toastPattern = frameNode->GetPattern<ToastPattern>();
    CHECK_NULL_VOID(toastPattern);
    auto toastProperty = frameNode->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_VOID(toastProperty);
    auto alignment = toastPattern->GetToastInfo().alignment;
    UpdateToastAlign(alignment);
    auto align = Alignment::ParseAlignment(alignment);
    if (align.has_value()) {
        toastProperty->UpdateToastAlignment(align.value());
    } else {
        toastProperty->ResetToastAlignment();
    }
    auto offset = toastPattern->GetToastInfo().offset;
    if (offset.has_value()) {
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        Dimension offsetX = isRtl ? offset->GetX() * (-1) : offset->GetX();
        offset->SetX(offsetX);
        toastProperty->UpdateToastOffset(offset.value());
    } else {
        toastProperty->ResetToastOffset();
    }
    auto text = layoutWrapper->GetOrCreateChildByIndex(0);
    text->Layout();
}

size_t GetLineCount(const RefPtr<LayoutWrapper>& textWrapper, LayoutConstraintF& layoutConstraint)
{
    textWrapper->Measure(layoutConstraint);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(textWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, 0);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textLayoutAlgorithm, 0);
    auto paragraph = textLayoutAlgorithm->GetSingleParagraph();
    CHECK_NULL_RETURN(paragraph, 0);
    auto paragLineCount = paragraph->GetLineCount();
    return paragLineCount;
}

void ToastLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto toastProps = DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(toastProps);
    auto toastNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(toastNode);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    CHECK_NULL_VOID(toastPattern);
    toastPattern->InitWrapperRect(layoutWrapper, toastProps);
    auto text = layoutWrapper->GetOrCreateChildByIndex(0);
    auto layoutConstraint = GetTextLayoutConstraint(layoutWrapper);
    // TextAlign should be START when lines of text are greater than 1
    if (GetLineCount(text, layoutConstraint) > 1) {
        auto textLayoutProp = DynamicCast<TextLayoutProperty>(text->GetLayoutProperty());
        CHECK_NULL_VOID(textLayoutProp);
        auto context = toastNode->GetContext();
        CHECK_NULL_VOID(context);
        auto toastTheme = context->GetTheme<ToastTheme>();
        CHECK_NULL_VOID(toastTheme);
        textLayoutProp->UpdateTextAlign(toastTheme->GetMultiLineTextAlign());
    }
    text->Measure(layoutConstraint);
    PerformMeasureSelf(layoutWrapper);
}

LayoutConstraintF ToastLayoutAlgorithm::GetTextLayoutConstraint(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, layoutConstraint);
    auto toastPattern = frameNode->GetPattern<ToastPattern>();
    CHECK_NULL_RETURN(toastPattern, layoutConstraint);
    auto toastProperty = frameNode->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_RETURN(toastProperty, layoutConstraint);
    auto context = toastPattern->GetToastContext();
    CHECK_NULL_RETURN(context, layoutConstraint);
    auto safeAreaManager = context->GetSafeAreaManager();
    auto keyboardInset = 0;
    if (safeAreaManager) {
        auto inset = safeAreaManager->GetKeyboardInset().Length();
        keyboardInset = NearEqual(inset, 0.0f) ? safeAreaManager->GetRawKeyboardHeight() : inset;
    }
    auto deviceHeight = context->GetRootHeight();
    auto keyboardOffset = deviceHeight - keyboardInset;
    if (toastPattern->IsAlignedWithHostWindow() && GreatNotEqual(keyboardInset, 0)) {
        deviceHeight = toastPattern->GetUiExtensionHostWindowRect().Height();

        auto currentId = Container::CurrentId();
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, layoutConstraint);
        if (container->IsSubContainer()) {
            auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(currentId);
            auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);
            CHECK_NULL_RETURN(parentContainer, layoutConstraint);
            CHECK_NULL_RETURN(parentContainer->IsUIExtensionWindow(), layoutConstraint);
            auto toastSubwindow = SubwindowManager::GetInstance()->GetToastSubwindow(parentContainer);
            if (toastSubwindow) {
                auto parentWindowRect = toastSubwindow->GetParentWindowRect();
                keyboardOffset = deviceHeight - keyboardInset - toastPattern->GetUiExtensionHostWindowRect().Bottom() +
                                 parentWindowRect.Bottom();
            }
        }
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN) && GreatNotEqual(keyboardInset, 0) &&
        (toastPattern->IsDefaultToast() || toastPattern->IsTopMostToast())) {
        auto maxHeight = keyboardOffset - toastPattern->GetLimitPos().Value() - LIMIT_SPACING.ConvertToPx();
        layoutConstraint.maxSize.SetHeight(maxHeight);
    }
    return layoutConstraint;
}
} // namespace OHOS::Ace::NG
