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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_CUSTOM_NODE_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_CUSTOM_NODE_STATIC_H

#include <functional>
#include <string>

#include "core/components_ng/pattern/custom/custom_node_base.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
namespace OHOS::Ace::NG {

struct NodeKoalaInfo {
    std::function<void()> onPageShowFunc;
    std::function<void()> onPageHideFunc;
    std::function<bool()> onBackPressedFunc;
    std::function<void()> pageTransitionFunc;
    std::function<void()> onCleanupFunc;
    std::function<std::string()> onDumpInspectorFunc;
    std::string jsViewName;
};

class ACE_FORCE_EXPORT CustomNodeStatic : public AceType {
    DECLARE_ACE_TYPE(CustomNodeStatic, AceType);
public:
    static CustomNode* ConstructCustomNode(int32_t id, NodeKoalaInfo&& info);
    static CustomMeasureLayoutNode* ConstructCustomNode(int32_t id,
        std::function<void(NG::LayoutWrapper* layoutWrapper)>&& onMeasureSize,
        std::function<void(NG::LayoutWrapper* layoutWrapper)>&& onPlaceChildren);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_CUSTOM_NODE_STATIC_H
