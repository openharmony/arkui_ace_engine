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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_MODEL_NG_H

#include <unordered_map>
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_model.h"

namespace OHOS::Ace::NG {
class FrameNode;
using UpdateLayoutPropertyFunc = std::function<void(const RefPtr<NG::FrameNode>&, const RefPtr<AlgorithmParamBase>&)>;

class ACE_EXPORT DynamicLayoutModelNG : public DynamicLayoutModel {
public:
    void Create(const RefPtr<AlgorithmParamBase>& algorithmParams, NG::DynamicLayoutType type) override;

private:
    static void UpdatePropertyFromLinearParam(
        const RefPtr<NG::FrameNode> &frameNode, const RefPtr<AlgorithmParamBase>& params);
    static void UpdatePropertyFromStackParam(
        const RefPtr<NG::FrameNode> &frameNode, const RefPtr<AlgorithmParamBase>& params);
    static void UpdatePropertyFromCustomParam(
        const RefPtr<NG::FrameNode> &frameNode, const RefPtr<AlgorithmParamBase>& params);
    static void UpdatePropertyFromGridParam(
        const RefPtr<NG::FrameNode> &frameNode, const RefPtr<AlgorithmParamBase>& params);
    static void UpdatePropertyFromAlgorithmParams(const RefPtr<FrameNode> &frameNode,
        const RefPtr<AlgorithmParamBase>& algorithmParams, NG::DynamicLayoutType type);
    static std::unordered_map<DynamicLayoutType, UpdateLayoutPropertyFunc> updateLayoutPropertyFuncMap_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_MODEL_NG_H