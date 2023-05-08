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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ROOT_SCENE_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ROOT_SCENE_NODE_H

#include "core/components_ng/base/ui_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
class RootSceneNode : public UINode {
    DECLARE_ACE_TYPE(RootSceneNode, UINode);

public:
    static RefPtr<RootSceneNode> GetOrCreateRootSceneNode(int32_t nodeId)
    {
        auto node = ElementRegister::GetInstance()->GetSpecificItemById<RootSceneNode>(nodeId);
        if (node) {
            return node;
        }
        node = MakeRefPtr<RootSceneNode>(nodeId);
        ElementRegister::GetInstance()->AddUINode(node);
        return node;
    }

    explicit RootSceneNode(int32_t nodeId) : UINode(V2::ROOT_SCENE_ETS_TAG, nodeId) {}
    ~RootSceneNode() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    ACE_DISALLOW_COPY_AND_MOVE(RootSceneNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ROOT_SCENE_NODE_H
