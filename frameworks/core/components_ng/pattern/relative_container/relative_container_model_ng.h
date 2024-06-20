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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_MODEL_NG_H
#include "base/utils/macros.h"
#include "core/components_ng/pattern/relative_container/relative_container_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RelativeContainerModelNG : public OHOS::Ace::RelativeContainerModel {
public:
    void Create() override;
    void SetBarrier(const std::vector<BarrierInfo>& barrierInfo) override;
    void SetGuideline(const std::vector<GuidelineInfo>& guidelineInfo) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetBarrier(FrameNode* frameNode, const std::vector<BarrierInfo>& barrierInfo);
    static void SetGuideline(FrameNode* frameNode, const std::vector<GuidelineInfo>& guidelineInfo);

    static std::vector<BarrierInfo> GetBarrier(FrameNode* frameNode);
    static std::vector<GuidelineInfo> GetGuideline(FrameNode* frameNode);

    static void ResetBarrier(FrameNode* frameNode);
    static void ResetGuideline(FrameNode* frameNode);

};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RELATIVE_CONTAINER_RELATIVE_CONTAINER_MODEL_NG_H