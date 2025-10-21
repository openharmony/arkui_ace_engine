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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_MODEL_STATIC_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_MODEL_STATIC_NG_H

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/form/resource/form_request_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/form/form_event_hub.h"
#include "core/components_ng/pattern/form/form_model.h"
#include "core/components_ng/pattern/form/form_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT FormModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void UpdateProperty(const RequestFormInfo& formInfo);
    static void SetVisibility(FrameNode* frameNode, VisibleType visible);
    static void AllowUpdate(FrameNode* frameNode, bool value);
    static void SetDimension(FrameNode* frameNode, int32_t value);
    static void SetModuleName(FrameNode* frameNode, const std::string& value);
    static void SetSize(FrameNode* frameNode, const Dimension& width, const Dimension& height);
    static void SetOnAcquired(FrameNode* frameNode, std::function<void(const std::string&)>&& onAcquired);
    static void SetOnError(FrameNode* frameNode, std::function<void(const std::string&)>&& onError);
    static void SetOnUninstall(FrameNode* frameNode, std::function<void(const std::string&)>&& onUninstall);
    static void SetOnLoad(FrameNode* frameNode, std::function<void(const std::string&)>&& onLoad);
    static void SetOnRouter(FrameNode* frameNode, std::function<void(const std::string&)>&& onRouter);
    static void SetOnUpdate(FrameNode* frameNode, std::function<void(const std::string&)>&& onUpdate);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_MODEL_STATIC_NG_H
