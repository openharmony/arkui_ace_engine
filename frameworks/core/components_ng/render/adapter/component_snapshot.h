/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_COMPONENT_SNAPSHOT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_COMPONENT_SNAPSHOT_H

#include <string>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class ComponentSnapshot {
public:
    using JsCallback = std::function<void(std::shared_ptr<Media::PixelMap>, int32_t, std::function<void()>)>;

    static void Get(const std::string& componentId, JsCallback&& callback);
    // add delay to ensure Rosen has finished rendering
    static void Create(
        const RefPtr<AceType>& customNode, JsCallback&& callback, bool enableInspector, const int32_t delayTime = 300);

private:
    static std::shared_ptr<Rosen::RSNode> GetRsNode(const RefPtr<FrameNode>& node);

    WeakPtr<FrameNode> node_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_COMPONENT_SNAPSHOT_H