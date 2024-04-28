/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "movingphoto_node.h"

namespace OHOS::Ace::NG {
RefPtr<MovingPhotoNode> MovingPhotoNode::GetOrCreateMovingPhotoNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto movingPhotoNode = ElementRegister::GetInstance()->GetSpecificItemById<MovingPhotoNode>(nodeId);
    if (movingPhotoNode) {
        if (movingPhotoNode->GetTag() == tag) {
            return movingPhotoNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = movingPhotoNode->GetParent();
        if (parent) {
            parent->RemoveChild(movingPhotoNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    movingPhotoNode = AceType::MakeRefPtr<MovingPhotoNode>(tag, nodeId, pattern, false);
    movingPhotoNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(movingPhotoNode);
    return movingPhotoNode;
}
} // namespace OHOS::Ace::NG