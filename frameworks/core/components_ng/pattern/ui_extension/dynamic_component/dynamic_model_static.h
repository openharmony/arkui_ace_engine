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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_MODEL_STATIC_H

#include <memory>
#include <string>

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_param.h"

namespace OHOS::Ace::NG {
// For Arkts Static
class ACE_FORCE_EXPORT DynamicModelStatic : public AceType {
    DECLARE_ACE_TYPE(DynamicModelStatic, AceType);
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void* CreateFrameNodeByIncRefCount(int32_t nodeId);
    static void SetDynamicParam(FrameNode* frameNode, const DynamicParam& param);
    static void SetOnError(FrameNode* frameNode,
        std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError);
    static void SetIsReportFrameEvent(FrameNode* frameNode, bool isReportFrameEvent);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_MODEL_STATIC_H
