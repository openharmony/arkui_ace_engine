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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_COST_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_COST_MODEL_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_types.h"

namespace OHOS::Ace::NG {

// Cost bucket identity: a placeholder template used inside one scroll container type.
struct ScrollPlaceholderCostBucketKey {
    ScrollPlaceholderComponentType componentType = ScrollPlaceholderComponentType::LIST;
    std::string templateId;

    bool operator==(const ScrollPlaceholderCostBucketKey& other) const
    {
        return componentType == other.componentType && templateId == other.templateId;
    }
};

struct ScrollPlaceholderCostBucketKeyHash {
    size_t operator()(const ScrollPlaceholderCostBucketKey& key) const
    {
        return std::hash<std::string>()(key.templateId) ^
               (static_cast<size_t>(key.componentType) << 1);
    }
};

// EWMA based real item build cost model (design ADR-4):
// - buckets are keyed by componentType + templateId, plus one aggregate bucket per component;
// - estimate = EWMA mean + EWMA mean-absolute-deviation safety margin;
// - fallback chain: template bucket -> component aggregate -> cold start constant.
// All state is owned and mutated on the UI thread only, no locking is required.
class ScrollPlaceholderCostModel {
public:
    ScrollPlaceholderCostModel() = default;
    ~ScrollPlaceholderCostModel() = default;

    void RecordRealBuildDuration(
        ScrollPlaceholderComponentType componentType, const std::string& templateId, int64_t durationNs);
    int64_t EstimateRealBuildDuration(
        ScrollPlaceholderComponentType componentType, const std::string& templateId) const;

    uint32_t GetTemplateBucketSampleCount(
        ScrollPlaceholderComponentType componentType, const std::string& templateId) const;
    uint32_t GetComponentSampleCount(ScrollPlaceholderComponentType componentType) const;

private:
    struct CostBucket {
        uint32_t sampleCount = 0;
        double ewmaMeanNs = 0.0;
        double ewmaMeanAbsoluteDeviationNs = 0.0;
    };

    void UpdateBucket(CostBucket& bucket, int64_t durationNs);
    static int64_t ComposeEstimate(const CostBucket& bucket);

    CostBucket& GetOrCreateTemplateBucket(
        ScrollPlaceholderComponentType componentType, const std::string& templateId);
    const CostBucket* FindTemplateBucket(
        ScrollPlaceholderComponentType componentType, const std::string& templateId) const;
    const CostBucket* FindComponentBucket(ScrollPlaceholderComponentType componentType) const;

    std::unordered_map<ScrollPlaceholderCostBucketKey, CostBucket, ScrollPlaceholderCostBucketKeyHash> buckets_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_COST_MODEL_H
