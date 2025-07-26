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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_RS_NODE_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_RS_NODE_ADAPTER_H

#include <memory>
#include <string>

#include "base/memory/referenced.h"
#include "render_service_client/core/ui/rs_surface_node.h"

namespace OHOS::Rosen {
class RSUIContext;
class RSNode;
}

namespace OHOS::Ace {
class RsNodeAdapter {
public:
    RsNodeAdapter() = default;
    ~RsNodeAdapter() = default;
    static std::shared_ptr<Rosen::RSNode> CreateRootNode();
    static std::shared_ptr<Rosen::RSNode> CreateCanvasNode();
    static std::shared_ptr<Rosen::RSNode> CreateSurfaceNode(
        const Rosen::RSSurfaceNodeConfig& surfaceNodeConfig);
private:
    static std::shared_ptr<Rosen::RSUIContext> GetRSUIContext();
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_RS_NODE_ADAPTER_H