/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/sheet/content_cover/sheet_content_cover_object.h"

#include "base/geometry/dimension.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "ui/base/ace_type.h"
#include "ui/base/referenced.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {
constexpr int32_t FULL_MODAL_ALPHA_ANIMATION_DURATION = 200;

NG::BorderWidthProperty SheetContentCoverObject::PostProcessBorderWidth(const NG::BorderWidthProperty& borderWidth)
{
    // not support border width
    NG::BorderWidthProperty result = borderWidth;
    result.topDimen = 0.0_vp;
    result.bottomDimen = 0.0_vp;
    result.leftDimen = 0.0_vp;
    result.rightDimen = 0.0_vp;
    return result;
}

void SheetContentCoverObject::DirtyLayoutProcess(const RefPtr<LayoutAlgorithmWrapper>& layoutAlgorithmWrapper)
{
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto sheetNode = pattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);

    // update sheetHeight_ for FireHeightDidChange
    auto contentCoverSheetLayoutAlgorithm =
        AceType::DynamicCast<SheetContentCoverLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(contentCoverSheetLayoutAlgorithm);
    if (GreatNotEqual(contentCoverSheetLayoutAlgorithm->GetSheetHeight(), 0.0f)) {
        SetSheetHeight(contentCoverSheetLayoutAlgorithm->GetSheetHeight());
    }

    // update position
    if (!pattern->IsOnAppearing() && !pattern->IsOnDisappearing()) {
        pattern->FireOnWidthDidChange();
        FireHeightDidChange();
        context->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    }
}

void SheetContentCoverObject::InitScrollProps()
{
    // not support scroll
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto scrollNode = pattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->SetEdgeEffect(EdgeEffect::NONE, false);
    scrollPattern->SetScrollEnabled(false);
}

void SheetContentCoverObject::ClipSheetNode()
{
    // not support border radius, clip shape and shadow
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = 0.0_vp;
    borderRadius.radiusTopRight = 0.0_vp;
    borderRadius.radiusBottomLeft = 0.0_vp;
    borderRadius.radiusBottomRight = 0.0_vp;
    renderContext->UpdateBorderRadius(borderRadius);
    renderContext->UpdateOuterBorderRadius(borderRadius);
    renderContext->UpdateClipShape(nullptr);
    renderContext->UpdateBackShadow(Shadow());
}

void SheetContentCoverObject::SetFinishEventForAnimationOption(
    AnimationOption& option, bool isTransitionIn, bool isFirstTransition)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    if (isTransitionIn) {
        option.SetOnFinishEvent(
            [sheetWK = WeakClaim(RawPtr(sheetNode)), isFirst = isFirstTransition] {
                auto sheetNode = sheetWK.Upgrade();
                CHECK_NULL_VOID(sheetNode);
                auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
                CHECK_NULL_VOID(pattern);
                pattern->OnAppear();
                pattern->AvoidAiBar();
                pattern->FireOnTypeDidChange();
                pattern->FireOnWidthDidChange();
                auto sheetObject = pattern->GetSheetObject();
                CHECK_NULL_VOID(sheetObject);
                sheetObject->FireHeightDidChange();
            });
    } else {
        option.SetOnFinishEvent(
            [sheetWK = WeakClaim(RawPtr(sheetNode))] {
            auto sheet = sheetWK.Upgrade();
            CHECK_NULL_VOID(sheet);
            auto pattern = sheet->GetPattern<SheetPresentationPattern>();
            CHECK_NULL_VOID(pattern);
            auto overlayManager = pattern->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            pattern->OnDisappear();
            overlayManager->FireAutoSave(sheet);
            overlayManager->RemoveSheet(sheet);
        });
    }
}

AnimationOption SheetContentCoverObject::GetAnimationOptionForOverlay(bool isTransitionIn, bool isFirstTransition)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, AnimationOption());
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, AnimationOption());
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());

    AnimationOption option;
    auto transition = sheetStyle.modalTransition.value_or(ModalTransition::DEFAULT);
    switch (transition) {
        case ModalTransition::ALPHA:
            option.SetCurve(Curves::FRICTION);
            option.SetDuration(FULL_MODAL_ALPHA_ANIMATION_DURATION);
            option.SetFillMode(FillMode::FORWARDS);
            break;
        case ModalTransition::NONE:
            option.SetDuration(0);
            break;
        case ModalTransition::DEFAULT:
        default:
            const RefPtr<InterpolatingSpring> curve =
                AceType::MakeRefPtr<InterpolatingSpring>(0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
            option.SetCurve(curve);
            option.SetFillMode(FillMode::FORWARDS);
            break;
    }
    SetFinishEventForAnimationOption(option, isTransitionIn, isFirstTransition);
    return option;
}

void SheetContentCoverObject::InitAnimationForOverlay(bool isTransitionIn, bool isFirstTransition)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    auto transition = sheetStyle.modalTransition.value_or(ModalTransition::DEFAULT);
    auto renderContext = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    switch (transition) {
        case ModalTransition::ALPHA:
            renderContext->UpdateOpacity(isTransitionIn ? 0.0 : 1.0);
            break;
        case ModalTransition::NONE:
            renderContext->UpdateOpacity(isTransitionIn ? 1.0 : 0.0);
            break;
        case ModalTransition::DEFAULT:
        default: {
            auto geometryNode = sheetNode->GetGeometryNode();
            CHECK_NULL_VOID(geometryNode);
            auto height = geometryNode->GetFrameSize().Height();
            if (isTransitionIn) {
                renderContext->UpdateTransformTranslate({ 0.0f, height, 0.0f });
            } else {
                renderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
            }
            break;
        }
    }
}

std::function<void()> SheetContentCoverObject::GetAnimationPropertyCallForOverlay(bool isTransitionIn)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    auto transition = sheetStyle.modalTransition.value_or(ModalTransition::DEFAULT);

    switch (transition) {
        case ModalTransition::ALPHA:
            return [sheetWK = WeakClaim(RawPtr(sheetNode)), isTransitionIn]() {
                auto node = sheetWK.Upgrade();
                CHECK_NULL_VOID(node);
                auto renderContext = node->GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                renderContext->UpdateOpacity(isTransitionIn ? 1.0 : 0.0);
            };
        case ModalTransition::NONE:
            return [sheetWK = WeakClaim(RawPtr(sheetNode)), isTransitionIn]() {
                auto node = sheetWK.Upgrade();
                CHECK_NULL_VOID(node);
                auto renderContext = node->GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                renderContext->UpdateOpacity(isTransitionIn ? 1.0 : 0.0);
            };
        case ModalTransition::DEFAULT:
        default:
            return [sheetWK = WeakClaim(RawPtr(sheetNode)), isTransitionIn]() {
                auto node = sheetWK.Upgrade();
                CHECK_NULL_VOID(node);
                auto geometryNode = node->GetGeometryNode();
                CHECK_NULL_VOID(geometryNode);
                auto height = geometryNode->GetFrameSize().Height();
                auto renderContext = node->GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                if (isTransitionIn) {
                    renderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
                } else {
                    renderContext->UpdateTransformTranslate({ 0.0f, height, 0.0f });
                }
            };
    }
}

void SheetContentCoverObject::FireHeightDidChange()
{
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto preDidHeight = pattern->GetPreDidHeight();
    if (NearEqual(preDidHeight, sheetHeight_)) {
        return;
    }
    pattern->OnHeightDidChange(sheetHeight_);
    pattern->SetPreDidHeight(sheetHeight_);
}
} // namespace OHOS::Ace::NG