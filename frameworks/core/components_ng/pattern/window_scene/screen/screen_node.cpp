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

#include "core/components_ng/pattern/window_scene/screen/screen_node.h"
#include "core/components_ng/pattern/window_scene/screen/screen_pattern.h"

namespace OHOS::Ace::NG {
HitTestResult ScreenNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId,
    ResponseLinkResult& responseLinkResult, bool isDispatch)
{
    auto testResult = HitTestResult::OUT_OF_REGION;
    auto pattern = GetPattern<ScreenPattern>();
    CHECK_NULL_RETURN(pattern, testResult);
    auto screenSession = pattern->GetScreenSession();
    CHECK_NULL_RETURN(screenSession, testResult);
    uint64_t targetDisplayId = static_cast<uint64_t>(touchRestrict.touchEvent.targetDisplayId);
    if (screenSession->GetScreenId() != targetDisplayId) {
        return testResult;
    }
    testResult = FrameNode::TouchTest(
        globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, result, touchId, responseLinkResult);
    return testResult;
}

RefPtr<ScreenNode> ScreenNode::GetOrCreateScreenNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto screenNode = ElementRegister::GetInstance()->GetSpecificItemById<ScreenNode>(nodeId);
    if (screenNode) {
        if (screenNode->GetTag() == tag) {
            return screenNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = screenNode->GetParent();
        if (parent) {
            parent->RemoveChild(screenNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    screenNode = AceType::MakeRefPtr<ScreenNode>(tag, nodeId, pattern, false);
    screenNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(screenNode);
    return screenNode;
}
} // namespace OHOS::Ace::NG
