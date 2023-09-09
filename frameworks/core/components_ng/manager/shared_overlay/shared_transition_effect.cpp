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

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/motion_path_evaluator.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

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
        LOGW("Create exchange animation failed. %{public}s is null. share id: %{public}s", !src ? "src" : "dest",
            GetShareId().c_str());
        return false;
    }
    return !GetShareId().empty();
}

bool SharedTransitionExchange::CreateAnimation()
{
    auto src = src_.Upgrade();
    auto dest = dest_.Upgrade();
    if (!dest || !src) {
        LOGW("Create exchange animation failed. %{public}s is null. share id: %{public}s", !src ? "src" : "dest",
            GetShareId().c_str());
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
    auto destOffset = dest->GetPaintRectOffsetToPage();
    auto srcOffset = src->GetPaintRectOffsetToPage();
    LOGI("Get Offset, share id: %{public}s. src: %{public}s, dest: %{public}s", GetShareId().c_str(),
        srcOffset.ToString().c_str(), destOffset.ToString().c_str());
    if (NearEqual(destOffset, srcOffset)) {
        return true;
    }
    Offset diff { destOffset.GetX() - srcOffset.GetX(), destOffset.GetY() - srcOffset.GetY() };
    auto translateAnimation = AceType::MakeRefPtr<CurveAnimation<DimensionOffset>>(Offset(0, 0), diff, option_->curve);
    if (option_->motionPathOption.IsValid()) {
        auto motionPathEvaluator =
            AceType::MakeRefPtr<MotionPathEvaluator>(option_->motionPathOption, Offset(0, 0), diff);
        translateAnimation->SetEvaluator(motionPathEvaluator->CreateDimensionOffsetEvaluator());
        // ignore motion rotate
    }
    auto translateListener =
        [weakSrc = WeakPtr<RenderContext>(src->GetRenderContext())](const DimensionOffset& value) {
        auto srcNode = weakSrc.Upgrade();
        if (srcNode) {
            auto host = srcNode->GetHost();
            srcNode->SetSharedTranslate(
                static_cast<float>(value.GetX().Value()), static_cast<float>(value.GetY().Value()));
        }
    };
    translateAnimation->AddListener(translateListener);
    controller_->AddInterpolator(translateAnimation);
    finishCallbacks_.emplace_back([weakSrc = WeakPtr<RenderContext>(src->GetRenderContext())]() {
        auto srcNode = weakSrc.Upgrade();
        if (srcNode) {
            LOGD("reset shared translate");
            srcNode->ResetSharedTranslate();
        }
    });
    return true;
}

bool SharedTransitionExchange::CreateSizeAnimation(const RefPtr<FrameNode>& src, const RefPtr<FrameNode>& dest)
{
    auto destSize = dest->GetGeometryNode()->GetFrameSize();
    auto srcSize = src->GetGeometryNode()->GetFrameSize();
    if (!destSize.IsPositive()) {
        LOGW("destSize is %{public}s, means we don't get the size correctly, so create sharedTransition failed"
             ", sharedId:%{public}s",
            destSize.ToString().c_str(), GetShareId().c_str());
        return false;
    }
    LOGI("Get Size, share id: %{public}s. src: %{public}s, dest: %{public}s", GetShareId().c_str(),
        srcSize.ToString().c_str(), destSize.ToString().c_str());
    if (NearEqual(srcSize, destSize)) {
        return true;
    }
    const auto& magicProperty = src->GetLayoutProperty()->GetMagicItemProperty();
    auto initAspectRatio = magicProperty ? magicProperty->GetAspectRatio() : std::nullopt;
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
        LOGW("Create static animation failed. current is null. share id: %{public}s", GetShareId().c_str());
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
