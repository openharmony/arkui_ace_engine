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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FORCE_SPLIT_FORCE_SPLIT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FORCE_SPLIT_FORCE_SPLIT_MANAGER_H

#include <cstdint>
#include <optional>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {

class ForceSplitManager : public virtual AceType {
    DECLARE_ACE_TYPE(ForceSplitManager, AceType);
public:
    ForceSplitManager() = default;
    ~ForceSplitManager() = default;

    void SetForceSplitEnable(bool isForceSplit, bool ignoreOrientation);

    void SetPipelineContext(const WeakPtr<PipelineContext>& pipeline)
    {
        pipeline_ = pipeline;
    }
    bool IsForceSplitSupported() const
    {
        return isForceSplitSupported_;
    }
    bool IsForceSplitEnable() const
    {
        return isForceSplitEnable_;
    }
    bool GetIgnoreOrientation() const;

    void UpdateIsInForceSplitMode(int32_t width);

    void SetFullScreenPages(std::set<std::string>&& pages)
    {
        fullScreenPages_ = std::move(pages);
    }

    bool IsFullScreenPage(const std::string& name) const
    {
        return fullScreenPages_.find(name) != fullScreenPages_.end();
    }

    void NotifyForceFullScreenChange(bool isForceFullScreen);

private:
    WeakPtr<PipelineContext> pipeline_;
    bool isForceSplitSupported_ = false;
    bool isForceSplitEnable_ = false;
    bool ignoreOrientation_ = false;
    std::set<std::string> fullScreenPages_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FORCE_SPLIT_FORCE_SPLIT_MANAGER_H