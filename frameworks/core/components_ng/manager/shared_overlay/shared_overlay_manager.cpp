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

#include "core/components_ng/manager/shared_overlay/shared_overlay_manager.h"

#include <sstream>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

namespace {
RefPtr<SharedTransitionEffect> GetSharedEffect(
    const ShareId& shareId, const WeakPtr<FrameNode>& destWeak, const WeakPtr<FrameNode>& srcWeak)
{
    auto dest = destWeak.Upgrade();
    auto src = srcWeak.Upgrade();
    if ((!src) && (!dest)) {
        LOGW("No Shared element found. share id: %{public}s", shareId.c_str());
        return nullptr;
    }
    std::shared_ptr<SharedTransitionOption> options;
    if (dest && dest->GetRenderContext()->HasSharedTransitionOption()) {
        options = dest->GetRenderContext()->GetSharedTransitionOption();
    } else if (src && src->GetRenderContext()->HasSharedTransitionOption()) {
        options = src->GetRenderContext()->GetSharedTransitionOption();
    }
    if (!options) {
        // use default transition params
        const int32_t defaultDuration = 1000;
        options = std::make_shared<SharedTransitionOption>();
        options->curve = Curves::LINEAR;
        options->duration = defaultDuration;
    }
    if (options->type == SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE && (!src || !dest)) {
        return nullptr;
    }
    return SharedTransitionEffect::GetSharedTransitionEffect(shareId, options);
}

RefPtr<FrameNode> CreateBlankFrameNode(const RefPtr<FrameNode>& node)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto newNode = FrameNode::CreateFrameNode(node->GetTag(), nodeId, pattern);
    newNode->SetGeometryNode(node->GetGeometryNode()->Clone());
    auto frameSize = node->GetGeometryNode()->GetFrameSize();
    // set size so the node will keep its size
    newNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(frameSize.Width()), CalcLength(frameSize.Height())));
    LOGD("create new node, tag:%{public}s, id:%{public}d, frameSize:%{public}s, pre node globalOffset:%{public}s",
        node->GetTag().c_str(), nodeId, newNode->GetGeometryNode()->GetFrameSize().ToString().c_str(),
        node->GetOffsetRelativeToWindow().ToString().c_str());
    return newNode;
}

bool ReplaceFrameNode(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& newNode)
{
    auto parent = node->GetParent();
    CHECK_NULL_RETURN(parent, false);
    parent->ReplaceChild(node, newNode);
    parent->RebuildRenderContextTree();
    return true;
}

} // namespace

void SharedOverlayManager::StartSharedTransition(const RefPtr<FrameNode>& pageSrc, const RefPtr<FrameNode>& pageDest)
{
    CHECK_NULL_VOID(pageSrc);
    CHECK_NULL_VOID(pageDest);
    auto patternSrc = pageSrc->GetPattern<PagePattern>();
    CHECK_NULL_VOID(patternSrc);
    auto patternDest = pageDest->GetPattern<PagePattern>();
    CHECK_NULL_VOID(patternDest);
    patternSrc->BuildSharedTransitionMap();
    patternDest->BuildSharedTransitionMap();
    PrepareSharedTransition(pageSrc, pageDest);
    auto pipeline = PipelineBase::GetCurrentContext();
    for (const auto& effect : effects_) {
        auto controller = effect->GetController();
        if (controller) {
            LOGI("effect start, shareId = %{public}s, id = %{public}d", effect->GetShareId().c_str(),
                effect->GetController()->GetId());
            controller->SetFillMode(FillMode::FORWARDS);
            controller->SetAllowRunningAsynchronously(true);
            controller->AttachScheduler(pipeline);
            controller->Forward();
        }
    }
}

void SharedOverlayManager::PrepareSharedTransition(const RefPtr<FrameNode>& pageSrc, const RefPtr<FrameNode>& pageDest)
{
    ClearAllEffects();
    auto patternDest = pageDest->GetPattern<PagePattern>();
    CHECK_NULL_VOID(patternDest);
    auto patternSrc = pageSrc->GetPattern<PagePattern>();
    CHECK_NULL_VOID(patternSrc);
    pageOffset_ = pageDest->GetRenderContext()->GetPaintRectWithoutTransform().GetOffset();
    const auto& srcMap = patternSrc->GetSharedTransitionMap();
    const auto& destMap = patternDest->GetSharedTransitionMap();
    std::list<RefPtr<SharedTransitionEffect>> effects;
    std::list<RefPtr<SharedTransitionEffect>> anchorEffects;

    // find out all exchange effect or static effect in dest page
    for (const auto& item : destMap) {
        const auto& shareId = item.first;
        const auto& destWeak = item.second;
        auto srcSharedIter = srcMap.find(shareId);
        WeakPtr<FrameNode> srcWeak;
        if (srcSharedIter != srcMap.end()) {
            srcWeak = srcSharedIter->second;
        }
        RefPtr<SharedTransitionEffect> effect = GetSharedEffect(shareId, destWeak, srcWeak);
        if (!effect) {
            continue;
        }
        effect->SetSharedNode(srcWeak, destWeak);
        if (effect->GetType() == SharedTransitionEffectType::SHARED_EFFECT_STATIC) {
            anchorEffects.emplace_back(effect);
        } else {
            effects.emplace_back(effect);
        }
    }
    // find out all static effect in source page
    for (const auto& item : srcMap) {
        const auto& sharedId = item.first;
        const auto& sourceWeak = item.second;
        RefPtr<SharedTransitionEffect> effect = GetSharedEffect(sharedId, nullptr, sourceWeak);
        if (!effect || effect->GetType() != SharedTransitionEffectType::SHARED_EFFECT_STATIC) {
            continue;
        }
        auto destSharedIter = destMap.find(sharedId);
        if (destSharedIter != destMap.end()) {
            // src is static, it has been added to effects in previous for loop
            continue;
        }
        effect->SetSharedNode(sourceWeak, nullptr);
        anchorEffects.emplace_back(effect);
    }

    LOGD("effectSize:%{public}zu, anchorEffectSize:%{public}zu, srcMap size:%{public}zu, destMap size:%{public}zu",
        effects.size(), anchorEffects.size(), srcMap.size(), destMap.size());
    // prepare each sharedTransition effect
    CheckAndPrepareTransition(effects, effects_);
    CheckAndPrepareTransition(anchorEffects, effects_);
    if (!effects_.empty()) {
        sharedManager_->RebuildRenderContextTree();
    }
    LOGD("effective effects size:%{public}zu", effects_.size());
}

void SharedOverlayManager::CheckAndPrepareTransition(
    std::list<RefPtr<SharedTransitionEffect>>& effects, std::list<RefPtr<SharedTransitionEffect>>& effectiveEffects)
{
    for (auto& effect : effects) {
        const auto& shareId = effect->GetShareId();
        if (!effect->Allow()) {
            LOGW("Shared transition not allowed, share id: %{public}s", shareId.c_str());
            continue;
        }
        if (!PrepareEachTransition(effect)) {
            LOGW("Prepare shared transition failed. share id: %{public}s", shareId.c_str());
            continue;
        }
        if (!CheckIn(effect)) {
            LOGW("CheckIn shared transition failed. share id: %{public}s", shareId.c_str());
            continue;
        }
        effectiveEffects.emplace_back(effect);
    }
}

bool SharedOverlayManager::PrepareEachTransition(const RefPtr<SharedTransitionEffect>& effect)
{
    if (!effect->CreateAnimation()) {
        LOGW("Create animation failed. share id: %{public}s", effect->GetShareId().c_str());
        return false;
    }
    if (!effect->ApplyAnimation()) {
        LOGW("Apply animation failed. share id: %{public}s", effect->GetShareId().c_str());
        return false;
    }
    LOGD("Prepare Shared Transition. share id: %{public}s", effect->GetShareId().c_str());
    return true;
}

void SharedOverlayManager::ClearAllEffects()
{
    while (!effects_.empty()) {
        auto& effect = effects_.front();
        effect->StopPlayingEffect();
        effects_.pop_front();
    }
}

bool SharedOverlayManager::CheckIn(const RefPtr<SharedTransitionEffect>& effect)
{
    // Check-in
    if (!AboardShuttle(effect)) {
        LOGW("Check In failed. aboard shuttle failed. share id: %{public}s.", effect->GetShareId().c_str());
        return false;
    }
    const auto& controller = effect->GetController();
    CHECK_NULL_RETURN(controller, false);
    // Arrange Return Shuttle
    controller->AddStopListener([weak = WeakClaim(this), effectWeak = WeakPtr<SharedTransitionEffect>(effect)]() {
        auto shared = weak.Upgrade();
        CHECK_NULL_VOID(shared);
        auto effect = effectWeak.Upgrade();
        shared->GetOffShuttle(effect);
    });
    return true;
}

void SharedOverlayManager::PassengerAboard(
    const RefPtr<SharedTransitionEffect>& effect, const RefPtr<FrameNode>& passenger)
{
    auto ticket = passenger->GetPaintRectOffsetToPage();
    // Get offset relative to stage(or overlay), for safeArea
    ticket += pageOffset_;
    LOGI("passenger offset is %{public}s, id = %{public}s", ticket.ToString().c_str(), effect->GetShareId().c_str());
    auto initialPosition = passenger->GetRenderContext()->GetPosition();
    // save initialFrameOffset for static type sharedTransition
    auto initialFrameOffset = passenger->GetGeometryNode()->GetFrameOffset();
    const auto& initialMarginPtr = passenger->GetLayoutProperty()->GetMarginProperty();
    auto initialMargin = initialMarginPtr ? std::make_optional<MarginProperty>(*initialMarginPtr) : std::nullopt;
    auto zIndex = passenger->GetRenderContext()->GetZIndex();
    effect->SetPassengerInitZIndex(zIndex);
    effect->SetPassengerInitPos(initialPosition);
    effect->SetPassengerInitFrameOffset(initialFrameOffset);
    effect->SetPassengerInitMargin(initialMargin);
    bool isPassengerCurrentFocused = false;
    auto passengerFocusHub = passenger->GetFocusHub();
    if (passengerFocusHub) {
        isPassengerCurrentFocused = passengerFocusHub->IsCurrentFocus();
    }
    effect->SetPassengerCurrentFocused(isPassengerCurrentFocused);
    auto passengerHolder = CreateBlankFrameNode(passenger);
    passengerHolder->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    ReplaceFrameNode(passenger, passengerHolder);
    effect->SetPassengerHolder(passengerHolder);
    sharedManager_->AddChild(passenger);
    auto offset = OffsetT<Dimension>(Dimension(ticket.GetX()), Dimension(ticket.GetY()));
    if (initialMargin) {
        passenger->GetLayoutProperty()->UpdateMargin(MarginProperty());
        passenger->GetLayoutProperty()->CleanDirty();
    }
    passenger->GetRenderContext()->UpdateZIndex(effect->GetZIndex());
    passenger->GetRenderContext()->UpdatePosition(offset);
    passenger->GetRenderContext()->OnModifyDone();
    passenger->GetEventHub<EventHub>()->SetEnabledInternal(false);
}

bool SharedOverlayManager::AboardShuttle(const RefPtr<SharedTransitionEffect>& effect)
{
    auto passenger = effect->GetPassengerNode().Upgrade();
    if (!passenger) {
        LOGW("passenger is null, shareId = %{public}s", effect->GetShareId().c_str());
        return false;
    }
    if (effect->GetType() == SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE) {
        // passenger is src
        auto dest = effect->GetDestSharedNode().Upgrade();
        if (!dest) {
            LOGW("dest is null, shareId = %{public}s", effect->GetShareId().c_str());
            return false;
        }
        PassengerAboard(effect, passenger);
        auto exchangeEffect = AceType::DynamicCast<SharedTransitionExchange>(effect);
        auto destVisible = dest->GetLayoutProperty()->GetVisibilityValue(VisibleType::VISIBLE);
        exchangeEffect->SetInitialDestVisible(destVisible);
        exchangeEffect->SetVisibleToDest(VisibleType::INVISIBLE);
    } else {
        PassengerAboard(effect, passenger);
    }
    return true;
}

void SharedOverlayManager::GetOffShuttle(const RefPtr<SharedTransitionEffect>& effect)
{
    CHECK_NULL_VOID(effect);
    LOGI("get off shuttle. id: %{public}s", effect->GetShareId().c_str());
    auto passenger = effect->GetPassengerNode().Upgrade();
    CHECK_NULL_VOID(passenger);
    sharedManager_->RemoveChild(passenger);
    sharedManager_->RebuildRenderContextTree();
    auto passengerHolder = effect->GetPassengerHolder().Upgrade();
    if (!passengerHolder) {
        LOGD("passenger holder is null, maybe not need to place passenger back");
    } else {
        // restore the position and zIndex of passenger frameNode
        if (effect->GetPassengerInitPos().has_value()) {
            passenger->GetRenderContext()->UpdatePosition(effect->GetPassengerInitPos().value());
        } else {
            passenger->GetRenderContext()->ResetPositionProperty();
            passenger->GetRenderContext()->OnPositionUpdate(OffsetT<Dimension>());
        }
        if (effect->GetPassengerInitZIndex().has_value()) {
            passenger->GetRenderContext()->UpdateZIndex(effect->GetPassengerInitZIndex().value());
        } else {
            passenger->GetRenderContext()->ResetZIndex();
            passenger->GetRenderContext()->OnZIndexUpdate(0);
        }
        if (effect->GetPassengerInitMargin().has_value()) {
            passenger->GetLayoutProperty()->UpdateMargin(effect->GetPassengerInitMargin().value());
            passenger->MarkDirtyNode();
        }
        // restore initialFrameOffset for static type sharedTransition, because it may not layout again
        passenger->GetGeometryNode()->SetFrameOffset(effect->GetPassengerInitFrameOffset());
        ReplaceFrameNode(passengerHolder, passenger);
        passenger->GetEventHub<EventHub>()->RestoreEnabled();
        auto isPassengerCurrentFocused = effect->GetPassengerCurrentFocused();
        if (isPassengerCurrentFocused) {
            auto passengerFocusHub = passenger->GetFocusHub();
            if (passengerFocusHub) {
                passengerFocusHub->RequestFocusImmediately();
            }
        }
        // The callback is to restore the parameters used by passenger in the animation
        effect->PerformFinishCallback();
        passenger->GetRenderContext()->OnModifyDone();
    }
    if (effect->GetType() == SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE) {
        // restore the visibility of dest frameNode
        auto exchangeEffect = AceType::DynamicCast<SharedTransitionExchange>(effect);
        auto destVisible = exchangeEffect->GetInitialDestVisible();
        exchangeEffect->SetVisibleToDest(destVisible);
    }
}

bool SharedOverlayManager::OnBackPressed()
{
    bool inSharedTransition = false;
    for (const auto& effect : effects_) {
        if (effect->GetController()->IsRunning()) {
            inSharedTransition = true;
            break;
        }
    }
    return inSharedTransition;
}

void SharedOverlayManager::StopSharedTransition()
{
    for (const auto& effect : effects_) {
        auto controller = effect->GetController();
        if (controller->IsRunning()) {
            // When two new pages switch, let controller finishes, so passenger can go back to the original page.
            controller->Finish();
        }
    }
    effects_.clear();
}

} // namespace OHOS::Ace::NG
