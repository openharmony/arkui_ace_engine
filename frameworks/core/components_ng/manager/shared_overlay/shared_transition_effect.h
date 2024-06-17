/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SHARED_OVERLAY_SHARED_TRANSITION_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SHARED_OVERLAY_SHARED_TRANSITION_EFFECT_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/animation/animator.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/shared_transition_option.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {

class FrameNode;

class ACE_EXPORT SharedTransitionEffect : public AceType {
    DECLARE_ACE_TYPE(SharedTransitionEffect, AceType);

public:
    SharedTransitionEffect(const ShareId& shareId, const std::shared_ptr<SharedTransitionOption>& sharedOption);
    ~SharedTransitionEffect() override = default;

    virtual SharedTransitionEffectType GetType() const = 0;
    virtual bool Allow() const = 0;
    virtual bool CreateAnimation() = 0;
    virtual const WeakPtr<FrameNode>& GetPassengerNode() const = 0;

    const WeakPtr<FrameNode>& GetDestSharedNode() const
    {
        return dest_;
    }
    const WeakPtr<FrameNode>& GetSrcSharedNode() const
    {
        return src_;
    }
    const RefPtr<Animator>& GetController() const
    {
        return controller_;
    }
    ShareId GetShareId() const
    {
        return shareId_;
    }
    int32_t GetZIndex() const
    {
        return option_ ? option_->zIndex : 0;
    }
    void StopPlayingEffect() const
    {
        if (controller_->IsRunning()) {
            TAG_LOGD(AceLogTag::ACE_ANIMATION, "Stop playing transition effect, shareId:%{public}s", shareId_.c_str());
            controller_->Finish();
        }
    }
    const std::shared_ptr<SharedTransitionOption>& GetOption() const
    {
        return option_;
    }
    const WeakPtr<FrameNode>& GetPassengerHolder() const
    {
        return passengerHolder_;
    }
    const std::optional<OffsetT<Dimension>>& GetPassengerInitPos() const
    {
        return initialPosition_;
    }
    const std::optional<MarginProperty>& GetPassengerInitMargin() const
    {
        return initialMargin_;
    }
    OffsetF GetPassengerInitFrameOffset() const
    {
        return initialFrameOffset_;
    }
    const std::optional<int32_t>& GetPassengerInitZIndex() const
    {
        return initialZIndex_;
    }
    bool GetPassengerCurrentFocused() const
    {
        return isCurrentFocused_;
    }
    void SetSharedNode(const WeakPtr<FrameNode>& src, const WeakPtr<FrameNode>& dest)
    {
        dest_ = dest;
        src_ = src;
    }
    void SetPassengerHolder(const WeakPtr<FrameNode>& holder)
    {
        passengerHolder_ = holder;
    }
    void SetPassengerInitPos(const std::optional<OffsetT<Dimension>>& position)
    {
        initialPosition_ = position;
    }
    void SetPassengerInitMargin(const std::optional<MarginProperty>& margin)
    {
        initialMargin_ = margin;
    }
    void SetPassengerInitFrameOffset(const OffsetF& offset)
    {
        initialFrameOffset_ = offset;
    }
    void SetPassengerInitZIndex(const std::optional<int32_t>& zIndex)
    {
        initialZIndex_ = zIndex;
    }
    void SetPassengerCurrentFocused(bool isFocused)
    {
        isCurrentFocused_ = isFocused;
    }
    void PerformFinishCallback();
    bool ApplyAnimation();
    static RefPtr<SharedTransitionEffect> GetSharedTransitionEffect(
        const ShareId& shareId, const std::shared_ptr<SharedTransitionOption>& sharedOption);

protected:
    bool CreateOpacityAnimation(
        float startOpacity, float endOpacity, float finalOpacity, const WeakPtr<FrameNode>& node);
    WeakPtr<FrameNode> dest_;
    WeakPtr<FrameNode> src_;
    // placeholder used to hold the position after the passenger node is removed from the parent node
    WeakPtr<FrameNode> passengerHolder_;
    RefPtr<Animator> controller_;
    ShareId shareId_;
    std::shared_ptr<SharedTransitionOption> option_;
    std::optional<OffsetT<Dimension>> initialPosition_;
    std::optional<MarginProperty> initialMargin_;
    OffsetF initialFrameOffset_;
    std::optional<int32_t> initialZIndex_;
    std::list<std::function<void()>> finishCallbacks_;
    bool isCurrentFocused_ = false;
};

class SharedTransitionExchange : public SharedTransitionEffect {
    DECLARE_ACE_TYPE(SharedTransitionExchange, SharedTransitionEffect);

public:
    SharedTransitionExchange(const ShareId& shareId, const std::shared_ptr<SharedTransitionOption>& sharedOption);
    ~SharedTransitionExchange() override = default;

    SharedTransitionEffectType GetType() const override
    {
        return SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE;
    }
    const WeakPtr<FrameNode>& GetPassengerNode() const override
    {
        return src_;
    }
    bool Allow() const override;
    bool CreateAnimation() override;
    VisibleType GetInitialDestVisible() const
    {
        return destVisible_;
    }
    void SetInitialDestVisible(VisibleType type)
    {
        destVisible_ = type;
    }
    bool SetVisibleToDest(VisibleType type);
    void DestRequestDefaultFocus();

private:
    bool CreateTranslateAnimation(const RefPtr<FrameNode>& src, const RefPtr<FrameNode>& dest);
    bool CreateSizeAnimation(const RefPtr<FrameNode>& src, const RefPtr<FrameNode>& dest);
    bool CreateOpacityAnimation(const RefPtr<FrameNode>& src, const RefPtr<FrameNode>& dest);
    VisibleType destVisible_ = VisibleType::VISIBLE;
};

class SharedTransitionStatic : public SharedTransitionEffect {
    DECLARE_ACE_TYPE(SharedTransitionStatic, SharedTransitionEffect);

public:
    SharedTransitionStatic(const ShareId& shareId, const std::shared_ptr<SharedTransitionOption>& sharedOption);
    ~SharedTransitionStatic() override = default;

    SharedTransitionEffectType GetType() const override
    {
        return SharedTransitionEffectType::SHARED_EFFECT_STATIC;
    }
    const WeakPtr<FrameNode>& GetPassengerNode() const override;
    bool Allow() const override;
    bool CreateAnimation() override;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SHARED_OVERLAY_SHARED_TRANSITION_EFFECT_H
