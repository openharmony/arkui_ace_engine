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

#include "core/components_ng/pattern/menu/preview/menu_preview_layout_algorithm.h"

#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"

namespace OHOS::Ace::NG {
void MenuPreviewLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    UpdateLayoutConstraintForPreview(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }

    LinearLayoutAlgorithm::Measure(layoutWrapper);
}

void MenuPreviewLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto preview = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(preview);
    auto previewPattern = preview->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    auto menuWrapper = previewPattern->GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto menuLayoutAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    CHECK_NULL_VOID(menuLayoutAlgorithmWrapper);
    auto menuLayoutAlgorithm = DynamicCast<MenuLayoutAlgorithm>(menuLayoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(menuLayoutAlgorithm);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    if (!menuPattern->HasLaid()) {
        menuLayoutAlgorithm->Measure(AceType::RawPtr(menuNode));
        menuLayoutAlgorithm->Layout(AceType::RawPtr(menuNode));
        // This is a workaround, because sometimes the dirty will not be marked to the top menu node,
        // the image size of the hoverScale may change. After the change, the image needs to call layout to send
        // the measured paint to the rosen paint.
        LayoutHoverScaleImage(menuWrapperPattern);
    }
    menuPattern->SetHasLaid(false);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout();
    }
    LinearLayoutAlgorithm::Layout(layoutWrapper);
}

void MenuPreviewLayoutAlgorithm::LayoutHoverScaleImage(const RefPtr<MenuWrapperPattern>& wrapperPattern)
{
    CHECK_NULL_VOID(wrapperPattern);
    if (!wrapperPattern->GetIsShowHoverImage()) {
        return;
    }
    auto hoverScaleImage = wrapperPattern->GetHoverImagePreview();
    CHECK_NULL_VOID(hoverScaleImage);
    hoverScaleImage->Layout();
}

void MenuPreviewLayoutAlgorithm::UpdateLayoutConstraintForPreview(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto preview = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(preview);
    auto previewPattern = preview->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    auto menuWrapper = previewPattern->GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuParam = menuWrapperPattern->GetMenuParam();
    if (menuParam.isPreviewContainScale) {
        auto menuWindowRect = menuPattern->GetMenuWindowRect();
        auto maxWidth = menuWindowRect.Width();
        auto maxHeight = menuWindowRect.Height();
        auto targetSize = menuPattern->GetTargetSize();
        auto isOversize = GreatNotEqual(targetSize.Width(), maxWidth) || GreatNotEqual(targetSize.Height(), maxHeight);
        if (!isOversize) {
            return;
        }
        auto widthDelta = targetSize.Width() - maxWidth;
        auto heightDelta = targetSize.Height() - maxHeight;
        if (GreatOrEqual(widthDelta, heightDelta)) {
            maxHeight = targetSize.Height() * (maxWidth / targetSize.Width());
        } else {
            maxWidth = targetSize.Width() * (maxHeight / targetSize.Height());
        }
        auto layoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto layoutConstraint = layoutProperty->CreateChildConstraint();
        layoutConstraint.maxSize.SetWidth(maxWidth);
        layoutConstraint.maxSize.SetHeight(maxHeight);
        layoutConstraint.selfIdealSize.SetWidth(maxWidth);
        layoutConstraint.selfIdealSize.SetHeight(maxHeight);
        layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    } else {
        CheckLayoutConstraint(layoutWrapper, menuParam, menuPattern);
    }
}

void MenuPreviewLayoutAlgorithm::CheckLayoutConstraint(
    LayoutWrapper* layoutWrapper, const MenuParam& menuParam, const RefPtr<MenuPattern>& menuPattern)
{
    CHECK_NULL_VOID(menuPattern);
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->CreateChildConstraint();

    auto isUpdateContentConstraint = false;
    // contentRect = windowSize - safeArea - margin
    if (menuParam.availableLayoutAreaMode.has_value() &&
        menuParam.availableLayoutAreaMode.value() == AvailableLayoutAreaMode::SAFE_AREA) {
        auto layoutParam = menuPattern->GetMenuLayoutParam();
        auto maxWidth = layoutParam.wrapperRect.Width() - layoutParam.leftSecurity - layoutParam.rightSecurity;
        maxWidth = std::max(maxWidth, 0.0);
        auto maxHeight = layoutParam.wrapperRect.Height() - layoutParam.topSecurity - layoutParam.bottomSecurity;
        maxHeight = std::max(maxHeight, 0.0);
        layoutConstraint.maxSize = { maxWidth, maxHeight };
        layoutConstraint.percentReference = { maxWidth, maxHeight };
        isUpdateContentConstraint = true;
    }

    if (menuParam.previewScaleMode.value_or(PreviewScaleMode::AUTO) == PreviewScaleMode::MAINTAIN) {
        layoutConstraint.maxSize = { Infinity<float>(), Infinity<float>() };
        isUpdateContentConstraint = true;
    }

    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    if (isUpdateContentConstraint) {
        layoutProperty->UpdateContentConstraint();
    }
}
} // namespace OHOS::Ace::NG
