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

#include "core/components_ng/manager/shared_overlay/shared_transition_effect.h"

#include "core/components/common/properties/motion_path_evaluator.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {
SharedTransitionEffect::SharedTransitionEffect(
    const ShareId& shareId, const std::shared_ptr<SharedTransitionOption>& sharedOption)
    : shareId_(shareId), option_(sharedOption)
{
    std::string animatorName = "SharedTransition(" + shareId + ")";
    controller_ = CREATE_ANIMATOR(animatorName.c_str());
}

RefPtr<SharedTransitionEffect> SharedTransitionEffect::GetSharedTransitionEffect(
    const ShareId& shareId, const std::shared_ptr<SharedTransitionOption>& option)
{
    CHECK_NULL_RETURN(option, nullptr);
    RefPtr<SharedTransitionEffect> effect;
    if (option->type == SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE) {
        effect = AceType::MakeRefPtr<SharedTransitionExchange>(shareId, option);
    } else {
        effect = AceType::MakeRefPtr<SharedTransitionStatic>(shareId, option);
    }
    return effect;
}

void SharedTransitionEffect::PerformFinishCallback()
{
    for (const auto& callback : finishCallbacks_) {
        if (callback) {
            callback();
        }
    }
    finishCallbacks_.clear();
}

bool SharedTransitionEffect::CreateOpacityAnimation(
    float startOpacity, float endOpacity, float finalOpacity, const WeakPtr<FrameNode>& node)
{
    if (NearEqual(startOpacity, endOpacity)) {
        // no need to perform opacity animation
        return true;
    }
    auto opacityAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(startOpacity, endOpacity, option_->curve);
    auto opacityListener = [weakFrame = node](const float& opacity) {
        auto node = weakFrame.Upgrade();
        CHECK_NULL_VOID(node);
        node->GetRenderContext()->UpdateOpacity(opacity);
    };
    opacityAnimation->AddListener(opacityListener);
    controller_->AddInterpolator(opacityAnimation);
    controller_->AddStopListener([weakFrame = node, finalOpacity]() {
        auto node = weakFrame.Upgrade();
        CHECK_NULL_VOID(node);
        node->GetRenderContext()->UpdateOpacity(finalOpacity);
    });
    return true;
}

bool SharedTransitionEffect::ApplyAnimation()
{
    CHECK_NULL_RETURN(option_, false);
    controller_->SetDuration(option_->duration);
    controller_->SetStartDelay(option_->delay);
    return true;
}

SharedTransitionExchange::SharedTransitionExchange(
    const ShareId& shareId, const std::shared_ptr<SharedTransitionOption>& sharedOption)
    : SharedTransitionEffect(shareId, sharedOption)
{}

bool SharedTransitionExchange::Allow() const
{
    auto dest = dest_.Upgrade();
    auto src = src_.Upgrade();
    if (!dest || !src) {
        return false;
    }
    return !GetShareId().empty();
}

bool SharedTransitionExchange::CreateAnimation()
{
    auto src = src_.Upgrade();
    auto dest = dest_.Upgrade();
    if (!dest || !src) {
        return false;
    }
    CHECK_NULL_RETURN(option_, false);
    CHECK_NULL_RETURN(option_->curve, false);
    if (!CreateTranslateAnimation(src, dest)) {
        return false;
    }
    if (!CreateSizeAnimation(src, dest)) {
        return false;
    }
    if (!CreateOpacityAnimation(src, dest)) {
        return false;
    }
    return true;
}

bool SharedTransitionExchange::CreateTranslateAnimation(const RefPtr<FrameNode>& src, const RefPtr<FrameNode>& dest)
{
    auto destOffset = dest->GetPaintRectOffsetToStage();
    auto srcOffset = src->GetPaintRectOffsetToStage();
    TAG_LOGD(AceLogTag::ACE_ANIMATION,
        "Translate animation get Offset, share id: %{public}s. src: %{public}s, dest: %{public}s", GetShareId().c_str(),
        srcOffset.ToString().c_str(), destOffset.ToString().c_str());
    if (NearEqual(destOffset, srcOffset)) {
        return true;
    }
    Offset diff { destOffset.GetX() - srcOffset.GetX(), destOffset.GetY() - srcOffset.GetY() };
    auto translateAnimation = AceType::MakeRefPtr<CurveAnimation<DimensionOffset>>(Offset(0, 0), diff, option_->curve);
    auto srcRenderContext = src->GetRenderContext();
    std::optional<Vector5F> srcRotate;
    if (option_->motionPathOption.IsValid()) {
        auto motionPathEvaluator =
            AceType::MakeRefPtr<MotionPathEvaluator>(option_->motionPathOption, Offset(0, 0), diff);
        translateAnimation->SetEvaluator(motionPathEvaluator->CreateDimensionOffsetEvaluator());
        if (option_->motionPathOption.GetRotate()) {
            // Just need to add a rotation animation, the specific rotation Angle is calculated through the path
            auto rotateAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 0.0f, option_->curve);
            rotateAnimation->SetEvaluator(motionPathEvaluator->CreateRotateEvaluator());
            auto rotateListener = [weakSrc = WeakPtr<RenderContext>(srcRenderContext)](float value) {
                auto srcNode = weakSrc.Upgrade();
                CHECK_NULL_VOID(srcNode);
                // Rotate around the Z axis
                srcNode->UpdateTransformRotate({ 0, 0, 1, value, 0 });
            };
            rotateAnimation->AddListener(rotateListener);
            controller_->AddInterpolator(rotateAnimation);
            srcRotate = srcRenderContext->GetTransformRotateValue({ 0, 0, 1, 0, 0 });
        }
    }
    auto translateListener = [weakSrc = WeakPtr<RenderContext>(srcRenderContext)](const DimensionOffset& value) {
        auto srcNode = weakSrc.Upgrade();
        CHECK_NULL_VOID(srcNode);
        srcNode->SetSharedTranslate(static_cast<float>(value.GetX().Value()), static_cast<float>(value.GetY().Value()));
    };
    translateAnimation->AddListener(translateListener);
    controller_->AddInterpolator(translateAnimation);
    finishCallbacks_.emplace_back([weakSrc = WeakPtr<RenderContext>(srcRenderContext), srcRotate]() {
        auto srcNode = weakSrc.Upgrade();
        CHECK_NULL_VOID(srcNode);
        srcNode->ResetSharedTranslate();
        if (srcRotate) {
            srcNode->UpdateTransformRotate(srcRotate.value());
        }
    });
    return true;
}

bool SharedTransitionExchange::CreateSizeAnimation(const RefPtr<FrameNode>& src, const RefPtr<FrameNode>& dest)
{
    auto destSize = dest->GetRenderContext()->GetPaintRectWithoutTransform().GetSize();
    auto srcSize = src->GetRenderContext()->GetPaintRectWithoutTransform().GetSize();
    if (!destSize.IsPositive()) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION,
            "DestSize is %{public}s, means we don't get the size correctly, so create sharedTransition failed"
            ", sharedId:%{public}s",
            destSize.ToString().c_str(), GetShareId().c_str());
        return false;
    }
    TAG_LOGD(AceLogTag::ACE_ANIMATION,
        "Size animation get size,  share id: %{public}s. src: %{public}s, dest: %{public}s", GetShareId().c_str(),
        srcSize.ToString().c_str(), destSize.ToString().c_str());
    if (NearEqual(srcSize, destSize)) {
        return true;
    }
    const auto& magicProperty = src->GetLayoutProperty()->GetMagicItemProperty();
    auto initAspectRatio = magicProperty.GetAspectRatio();
    auto initSize = src->GetLayoutProperty()->GetCalcLayoutConstraint()
                        ? src->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize
                        : std::nullopt;
    auto sizeAnimation = AceType::MakeRefPtr<CurveAnimation<SizeF>>(srcSize, destSize, option_->curve);
    auto sizeListener = [weakFrame = WeakPtr<FrameNode>(src), setAspect = initAspectRatio.has_value()](
                            const SizeF& size) {
        auto src = weakFrame.Upgrade();
        CHECK_NULL_VOID(src);
        src->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(size.Width()), CalcLength(size.Height())));
        if (setAspect) {
            src->GetLayoutProperty()->UpdateAspectRatio(size.Width() / size.Height());
        }
        // When call listener callback, the passenger has mounted to overlay, only need to measure passenger
        // for better performance. Notice that the parent has been changed, layoutConstraint is not correct if we
        // don't measure from parent, otherwise the result may be wrong if passenger has aspectRatio.
        src->GetGeometryNode()->ResetParentLayoutConstraint();
        src->GetLayoutProperty()->CleanDirty();
        src->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    };
    sizeAnimation->AddListener(sizeListener);
    controller_->AddInterpolator(sizeAnimation);
    finishCallbacks_.emplace_back([weakFrame = WeakPtr<FrameNode>(src), initSize, initAspectRatio]() {
        auto src = weakFrame.Upgrade();
        CHECK_NULL_VOID(src);
        if (src->GetLayoutProperty()->GetCalcLayoutConstraint()) {
            src->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize = initSize;
        }
        if (initAspectRatio.has_value()) {
            src->GetLayoutProperty()->UpdateAspectRatio(initAspectRatio.value());
        }
        src->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    });
    return true;
}

bool SharedTransitionExchange::CreateOpacityAnimation(const RefPtr<FrameNode>& src, const RefPtr<FrameNode>& dest)
{
    auto startOpacity = static_cast<float>(src->GetRenderContext()->GetOpacityValue(1.0));
    auto endOpacity = static_cast<float>(dest->GetRenderContext()->GetOpacityValue(1.0));
    return SharedTransitionEffect::CreateOpacityAnimation(startOpacity, endOpacity, startOpacity, src_);
}

bool SharedTransitionExchange::SetVisibleToDest(VisibleType type)
{
    auto dest = dest_.Upgrade();
    CHECK_NULL_RETURN(dest, false);
    dest->GetLayoutProperty()->UpdateVisibility(type);
    return true;
}

void SharedTransitionExchange::DestRequestDefaultFocus()
{
    if (destVisible_ != VisibleType::VISIBLE) {
        return;
    }
    auto dest = dest_.Upgrade();
    CHECK_NULL_VOID(dest);
    auto page = dest->GetPageNode();
    CHECK_NULL_VOID(page);
    auto pagePattern = page->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->FocusViewShow();
}

SharedTransitionStatic::SharedTransitionStatic(
    const ShareId& shareId, const std::shared_ptr<SharedTransitionOption>& sharedOption)
    : SharedTransitionEffect(shareId, sharedOption)
{}

bool SharedTransitionStatic::Allow() const
{
    auto shared = GetPassengerNode().Upgrade();
    CHECK_NULL_RETURN(shared, false);
    return !(GetShareId().empty());
}

bool SharedTransitionStatic::CreateAnimation()
{
    auto node = GetPassengerNode().Upgrade();
    if (!node) {
        return false;
    }
    // static transition only need opacity animation
    auto initialOpacity = static_cast<float>(node->GetRenderContext()->GetOpacityValue(1.0));
    if (dest_ == node) {
        // anchor appearing, passenger is dest_, opacity 0 to initial opacity
        return SharedTransitionEffect::CreateOpacityAnimation(0.0f, initialOpacity, initialOpacity, dest_);
    }
    // anchor disappearing, passenger is src_, opacity initial opacity to 0
    return SharedTransitionEffect::CreateOpacityAnimation(initialOpacity, 0.0f, initialOpacity, src_);
}

const WeakPtr<FrameNode>& SharedTransitionStatic::GetPassengerNode() const
{
    return src_.Invalid() ? dest_ : src_;
}

} // namespace OHOS::Ace::NG
