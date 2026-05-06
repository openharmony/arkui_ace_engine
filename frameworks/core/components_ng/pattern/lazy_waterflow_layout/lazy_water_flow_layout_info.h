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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_INFO_H

#include <cstdint>
#include <memory>
#include <optional>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_pattern.h"

namespace OHOS::Ace {

class JsonValue;

namespace NG {

class LazyWaterFlowLayoutAlgorithm;
class LazyWaterFlowLayoutPattern;

class ACE_EXPORT LazyWaterFlowLayoutInfo : public AceType {
    DECLARE_ACE_TYPE(LazyWaterFlowLayoutInfo, AceType);

public:
    void NotifyDataChange(int32_t index, int32_t count);
    bool NeedPredict() const;
    void DumpAdvanceInfo();
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json);

private:
    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    int32_t totalItemCount_ = 0;
    AdjustOffset adjustOffset_ {};
    std::optional<int64_t> deadline_;

    friend class LazyWaterFlowLayoutAlgorithm;
    friend class LazyWaterFlowLayoutPattern;
};

} // namespace NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_INFO_H
