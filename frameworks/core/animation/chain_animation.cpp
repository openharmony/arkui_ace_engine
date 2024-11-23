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

#include "chain_animation.h"

#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
namespace {
constexpr int64_t NANOS_TO_MILLS = 1000000;
constexpr int32_t CHAIN_NODE_NUMBER = 15;
constexpr double DEFAULT_CHAIN_VALUE_ACCURACY = 0.5;
constexpr double DEFAULT_CHAIN_VALUE_VELOCITY_ACCURACY = 1000.0;
} // namespace

ChainAnimationNode::ChainAnimationNode(
    int32_t index, float space, float maxSpace, float minSpace, RefPtr<SpringProperty> springProperty)
    : springProperty_(std::move(springProperty)), index_(index), space_(space), maxSpace_(maxSpace),
      minSpace_(minSpace), curPosition_(space)
{
    spring_ = AceType::MakeRefPtr<SpringMotion>(space, space, 0.0, springProperty_);
    spring_->SetAccuracy(DEFAULT_CHAIN_VALUE_ACCURACY);
    spring_->SetVelocityAccuracy(DEFAULT_CHAIN_VALUE_VELOCITY_ACCURACY);
}

bool ChainAnimationNode::TickAnimation(float duration)
{
    spring_->OnTimestampChanged(duration, 0.0f, false);
    curPosition_ = spring_->GetCurrentPosition();
    curVelocity_ = spring_->GetCurrentVelocity();
    return spring_->IsCompleted();
}

void ChainAnimationNode::SetDelta(float delta, float spaceDelta, float duration)
{
    spaceDelta = std::clamp(spaceDelta, minSpace_ - space_, maxSpace_ - space_);
    spring_->OnTimestampChanged(duration, 0.0f, false);
    curPosition_ = spring_->GetCurrentPosition();
    curPosition_ = std::clamp(curPosition_ + delta, minSpace_ - spaceDelta, maxSpace_ - spaceDelta);
    spring_->Reset(curPosition_, space_, curVelocity_, springProperty_);
    spaceDelta_ = spaceDelta;
}

float ChainAnimationNode::GetDeltaPredict(float delta, float duration)
{
    spring_->OnTimestampChanged(duration, 0.0f, false);
    float curPosition = spring_->GetCurrentPosition();
    curPosition = std::clamp(curPosition + delta, minSpace_, maxSpace_);
    return curPosition - space_;
}

float ChainAnimationNode::GetDelta() const
{
    return curPosition_ - space_ + spaceDelta_;
}

ChainAnimation::ChainAnimation(float space, float maxSpace, float minSpace, RefPtr<SpringProperty> springProperty)
    : springProperty_(springProperty), space_(space), maxSpace_(maxSpace), minSpace_(minSpace)
{
    for (int32_t i = 1; i < CHAIN_NODE_NUMBER; i++) {
        nodes_.emplace(i, AceType::MakeRefPtr<ChainAnimationNode>(i, space, maxSpace, minSpace, springProperty));
        nodes_.emplace(-i, AceType::MakeRefPtr<ChainAnimationNode>(-i, space, maxSpace, minSpace, springProperty));
    }
    auto&& callback = [weak = AceType::WeakClaim(this)](uint64_t duration) {
        ACE_SCOPED_TRACE("ChainAnimation");
        auto chain = weak.Upgrade();
        CHECK_NULL_VOID(chain);
        chain->TickAnimation();
    };
    scheduler_ = AceType::MakeRefPtr<Scheduler>(callback, PipelineBase::GetCurrentContext());
}

void ChainAnimation::SetDelta(float delta, float overOffset)
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto timestamp = context->GetVsyncTime();
    double duration = static_cast<double>(timestamp - timestamp_) / static_cast<double>(NANOS_TO_MILLS);
    float factor = (1 - conductivity_) * intensity_;
    if (edgeEffect_ == ChainEdgeEffect::STRETCH) {
        float spaceDelta = std::abs(overOffset) * edgeEffectIntensity_;
        for (int32_t i = 1; i < CHAIN_NODE_NUMBER; i++) {
            nodes_[i]->SetDelta(delta * factor, spaceDelta, static_cast<float>(duration));
            nodes_[-i]->SetDelta(-delta * factor, spaceDelta, static_cast<float>(duration));
            factor *= conductivity_;
        }
    } else {
        float spaceDelta = overOffset * edgeEffectIntensity_;
        for (int32_t i = 1; i < CHAIN_NODE_NUMBER; i++) {
            nodes_[i]->SetDelta(delta * factor, -spaceDelta, static_cast<float>(duration));
            nodes_[-i]->SetDelta(-delta * factor, spaceDelta, static_cast<float>(duration));
            factor *= conductivity_;
            spaceDelta *= conductivity_;
        }
    }
    if (!scheduler_->IsActive() && !NearZero(delta)) {
        scheduler_->Start();
    }
    timestamp_ = timestamp;
}

void ChainAnimation::TickAnimation()
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto timestamp = context->GetVsyncTime();
    auto duration = static_cast<double>(timestamp - timestamp_) / static_cast<double>(NANOS_TO_MILLS);
    auto finish = true;
    for (int32_t i = 1; i < CHAIN_NODE_NUMBER; i++) {
        finish = nodes_[i]->TickAnimation(duration) && finish;
        finish = nodes_[-i]->TickAnimation(duration) && finish;
    }
    if (finish) {
        scheduler_->Stop();
    }
    if (animationCallback_) {
        animationCallback_();
    }
}

float ChainAnimation::GetValue(int32_t index)
{
    float value = 0.0f;
    if (index > controlIndex_) {
        for (int32_t i = 1; i <= index - controlIndex_ && i < CHAIN_NODE_NUMBER; i++) {
            value += nodes_[i]->GetDelta();
        }
    } else if (index < controlIndex_) {
        for (int32_t i = 1; i <= controlIndex_ - index && i < CHAIN_NODE_NUMBER; i++) {
            value -= nodes_[-i]->GetDelta();
        }
    }
    return value;
}

float ChainAnimation::GetValuePredict(int32_t index, float delta)
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0);
    auto timestamp = context->GetVsyncTime();
    double duration = static_cast<double>(timestamp - timestamp_) / static_cast<double>(NANOS_TO_MILLS);
    float value = 0.0f;
    float factor = (1 - conductivity_) * intensity_;
    if (index > controlIndex_) {
        for (int32_t i = 1; i <= index - controlIndex_ && i < CHAIN_NODE_NUMBER; i++) {
            value += nodes_[i]->GetDeltaPredict(delta * factor, duration);
            factor *= conductivity_;
        }
    } else if (index < controlIndex_) {
        for (int32_t i = 1; i <= controlIndex_ - index && i < CHAIN_NODE_NUMBER; i++) {
            value -= nodes_[-i]->GetDeltaPredict(-delta * factor, duration);
            factor *= conductivity_;
        }
    }
    return value;
}

float ChainAnimation::SetControlIndex(int32_t index)
{
    if (index == controlIndex_) {
        return 0.0f;
    }
    float delta = GetValue(index);
    if (scheduler_->IsActive()) {
        std::map<int32_t, RefPtr<ChainAnimationNode>> tmpNodes;
        int32_t dt = index - controlIndex_;
        for (int32_t i = 1; i < CHAIN_NODE_NUMBER; i++) {
            auto next = i + dt <= 0 ? i + dt - 1 : i + dt;
            if (next > -CHAIN_NODE_NUMBER && next < CHAIN_NODE_NUMBER) {
                tmpNodes[i] = nodes_[next];
                tmpNodes[i]->SetIndex(i);
            } else {
                tmpNodes.emplace(
                    i, AceType::MakeRefPtr<ChainAnimationNode>(i, space_, maxSpace_, minSpace_, springProperty_));
            }
            auto prev = dt - i >= 0 ? dt - i + 1 : dt - i;
            if (prev > -CHAIN_NODE_NUMBER && prev < CHAIN_NODE_NUMBER) {
                tmpNodes[-i] = nodes_[prev];
                tmpNodes[-i]->SetIndex(-i);
            } else {
                tmpNodes.emplace(
                    -i, AceType::MakeRefPtr<ChainAnimationNode>(-i, space_, maxSpace_, minSpace_, springProperty_));
            }
        }
        nodes_.swap(tmpNodes);
    }
    controlIndex_ = index;
    return delta;
}

void ChainAnimation::SetSpace(float space, float maxSpace, float minSpace)
{
    space_ = space;
    maxSpace_ = maxSpace;
    minSpace_ = minSpace;
    for (int32_t i = 1; i < CHAIN_NODE_NUMBER; i++) {
        nodes_[i]->SetSpace(space, maxSpace, minSpace);
        nodes_[-i]->SetSpace(space, maxSpace, minSpace);
    }
}
} // namespace OHOS::Ace
