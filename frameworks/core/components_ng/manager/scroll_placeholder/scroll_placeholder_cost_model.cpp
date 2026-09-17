/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_cost_model.h"

#include <algorithm>
#include <cmath>

namespace OHOS::Ace::NG {
namespace {
// Smoothing factor of the exponentially weighted moving average.
constexpr double EWMA_ALPHA = 0.3;
// Conservative cold start estimate for a bucket without any sample yet.
constexpr int64_t COLD_START_ESTIMATE_NS = 5000000; // 5ms
} // namespace

void ScrollPlaceholderCostModel::RecordRealBuildDuration(
    ScrollPlaceholderComponentType componentType, const std::string& templateId, int64_t durationNs)
{
    if (durationNs < 0) {
        return;
    }
    UpdateBucket(GetOrCreateTemplateBucket(componentType, templateId), durationNs);
    UpdateBucket(GetOrCreateTemplateBucket(componentType, std::string()), durationNs);
}

int64_t ScrollPlaceholderCostModel::EstimateRealBuildDuration(
    ScrollPlaceholderComponentType componentType, const std::string& templateId) const
{
    const CostBucket* bucket = FindTemplateBucket(componentType, templateId);
    if (bucket != nullptr && bucket->sampleCount > 0) {
        return ComposeEstimate(*bucket);
    }
    bucket = FindComponentBucket(componentType);
    if (bucket != nullptr && bucket->sampleCount > 0) {
        return ComposeEstimate(*bucket);
    }
    return COLD_START_ESTIMATE_NS;
}

uint32_t ScrollPlaceholderCostModel::GetTemplateBucketSampleCount(
    ScrollPlaceholderComponentType componentType, const std::string& templateId) const
{
    const CostBucket* bucket = FindTemplateBucket(componentType, templateId);
    return bucket == nullptr ? 0 : bucket->sampleCount;
}

uint32_t ScrollPlaceholderCostModel::GetComponentSampleCount(ScrollPlaceholderComponentType componentType) const
{
    const CostBucket* bucket = FindComponentBucket(componentType);
    return bucket == nullptr ? 0 : bucket->sampleCount;
}

void ScrollPlaceholderCostModel::UpdateBucket(CostBucket& bucket, int64_t durationNs)
{
    if (bucket.sampleCount == 0) {
        bucket.ewmaMeanNs = static_cast<double>(durationNs);
        bucket.ewmaMeanAbsoluteDeviationNs = 0.0;
    } else {
        double delta = static_cast<double>(durationNs) - bucket.ewmaMeanNs;
        bucket.ewmaMeanNs += EWMA_ALPHA * delta;
        bucket.ewmaMeanAbsoluteDeviationNs +=
            EWMA_ALPHA * (std::fabs(delta) - bucket.ewmaMeanAbsoluteDeviationNs);
    }
    bucket.sampleCount++;
}

int64_t ScrollPlaceholderCostModel::ComposeEstimate(const CostBucket& bucket)
{
    double estimate = bucket.ewmaMeanNs + bucket.ewmaMeanAbsoluteDeviationNs;
    return static_cast<int64_t>(std::max(estimate, 1.0));
}

ScrollPlaceholderCostModel::CostBucket& ScrollPlaceholderCostModel::GetOrCreateTemplateBucket(
    ScrollPlaceholderComponentType componentType, const std::string& templateId)
{
    ScrollPlaceholderCostBucketKey key { componentType, templateId };
    auto it = buckets_.find(key);
    if (it == buckets_.end()) {
        it = buckets_.emplace(std::move(key), CostBucket {}).first;
    }
    return it->second;
}

const ScrollPlaceholderCostModel::CostBucket* ScrollPlaceholderCostModel::FindTemplateBucket(
    ScrollPlaceholderComponentType componentType, const std::string& templateId) const
{
    ScrollPlaceholderCostBucketKey key { componentType, templateId };
    auto it = buckets_.find(key);
    return it == buckets_.end() ? nullptr : &(it->second);
}

const ScrollPlaceholderCostModel::CostBucket* ScrollPlaceholderCostModel::FindComponentBucket(
    ScrollPlaceholderComponentType componentType) const
{
    // The component aggregate bucket is the template bucket with an empty template id.
    return FindTemplateBucket(componentType, std::string());
}

} // namespace OHOS::Ace::NG
