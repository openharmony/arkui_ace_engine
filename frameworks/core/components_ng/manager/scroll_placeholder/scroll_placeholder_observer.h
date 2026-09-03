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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_OBSERVER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_OBSERVER_H

#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/time_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_manager.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_types.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

// Scoped observation around one scroll container item acquisition, placed at the List/Grid/
// WaterFlow child build call points (their layout child acquisition helpers). When the item is
// not built yet, the scope predicts with the remaining frame budget before the acquisition and
// samples the acquisition duration into the per-pipeline cost model afterwards. Observation
// only: the item is still acquired synchronously with unchanged behavior.
//
// Usage at the component child-build call point:
//   ScrollPlaceholderItemBuildScope buildScope(
//       ScrollPlaceholderComponentType::LIST, layoutWrapper, index, isCache);
//   auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index, addToRenderTree, isCache);
//   buildScope.SetAcquiredWrapper(wrapper);
class ScrollPlaceholderItemBuildScope {
public:
    ScrollPlaceholderItemBuildScope(ScrollPlaceholderComponentType componentType,
        LayoutWrapper* layoutWrapper, int32_t index, bool isCache)
    {
        CHECK_NULL_VOID(layoutWrapper);
        if (index < 0) {
            return;
        }
        const auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        // Cache gate: an acquisition that resolves without running the real item builder must
        // not feed the cost model, so only indexes without a built item open an observation.
        // This lookup never builds; it is a best-effort gate for observation accuracy only.
        if (host->GetChildByIndex(static_cast<uint32_t>(index), isCache)) {
            return;
        }
        auto* context = host->GetContext();
        CHECK_NULL_VOID(context);
        const auto& manager = context->GetOrCreateScrollPlaceholderManager();
        CHECK_NULL_VOID(manager);
        manager_ = manager;
        params_.componentType = componentType;
        params_.hostNodeId = host->GetId();
        params_.index = index;
        params_.cacheBuild = isCache;
        manager_->NotifyRealBuildStart(params_);
        buildStartNs_ = GetSysTimestamp();
        observing_ = true;
        AceTraceBeginWithArgs("ScrollPH.RealBuild[host:%d index:%d]", params_.hostNodeId, index);
    }

    ~ScrollPlaceholderItemBuildScope()
    {
        if (!observing_) {
            return;
        }
        AceTraceEnd();
        manager_->NotifyRealBuildEnd(params_, buildStartNs_);
    }

    // Report the acquisition result. A null wrapper means no real build happened (empty lazy
    // branch / out of range): the observation is closed without feeding a zero-cost sample
    // into the cost model. Sites that forget to report keep the fail-safe sampling behavior.
    void SetAcquiredWrapper(const RefPtr<LayoutWrapper>& wrapper)
    {
        if (!observing_ || acquiredReported_) {
            return;
        }
        acquiredReported_ = true;
        if (wrapper) {
            return;
        }
        AceTraceEnd();
        observing_ = false;
    }

    ScrollPlaceholderItemBuildScope(const ScrollPlaceholderItemBuildScope&) = delete;
    ScrollPlaceholderItemBuildScope& operator=(const ScrollPlaceholderItemBuildScope&) = delete;

private:
    RefPtr<ScrollPlaceholderManager> manager_;
    ScrollPlaceholderPredictParams params_;
    int64_t buildStartNs_ = 0;
    bool observing_ = false;
    bool acquiredReported_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_OBSERVER_H
