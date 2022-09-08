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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_REMOTE_WINDOW_REMOTE_WINDOW_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_REMOTE_WINDOW_REMOTE_WINDOW_COMPONENT_H

#include "core/pipeline/base/render_component.h"

namespace OHOS {
namespace Rosen {
class RSNode;
}

namespace Ace {
class ACE_EXPORT RemoteWindowComponent : public RenderComponent {
    DECLARE_ACE_TYPE(RemoteWindowComponent, RenderComponent);

public:
    RemoteWindowComponent() = default;
    ~RemoteWindowComponent() override = default;
    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    void SetExternalRSNode(const std::shared_ptr<Rosen::RSNode>& rsNode)
    {
        rsNode_ = rsNode;
    }

    const std::shared_ptr<Rosen::RSNode>& GetExternalRSNode() const
    {
        return rsNode_;
    }

private:
    std::shared_ptr<Rosen::RSNode> rsNode_;
};
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_REMOTE_WINDOW_REMOTE_WINDOW_COMPONENT_H
