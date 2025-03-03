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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SURFACE_PROXY_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SURFACE_PROXY_NODE_H

#include "core/components_ng/pattern/pattern.h"
#include "transaction/rs_interfaces.h"

namespace OHOS::Ace::NG {
class SurfaceProxyNode : public AceType {
    DECLARE_ACE_TYPE(SurfaceProxyNode, AceType);

public:
    virtual ~SurfaceProxyNode() = default;

    void SetHostNode(const WeakPtr<FrameNode>& host);
    bool AddSurfaceNode(const std::shared_ptr<Rosen::RSSurfaceNode>& rsSurfaceNode);
    void CreateSurfaceProxyNode();
    virtual void OnAddSurfaceNode();
    RefPtr<FrameNode> GetSurfaceProxyNode();

private:
    RefPtr<FrameNode> surfaceProxyNode_;
    WeakPtr<FrameNode> host_;
    AceLogTag aceLogTag_ = AceLogTag::ACE_DEFAULT_DOMAIN;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SURFACE_PROXY_NODE_H
