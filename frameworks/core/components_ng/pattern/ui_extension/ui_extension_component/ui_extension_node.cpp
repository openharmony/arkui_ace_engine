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

#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_node.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_touch_delegate.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
UIExtensionNode::UIExtensionNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
    : FrameNode(tag, nodeId, pattern, isRoot)
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Create UIExtensionNode");
}

UIExtensionNode::~UIExtensionNode()
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Destory UIExtensionNode");
}

RefPtr<UIExtensionNode> UIExtensionNode::GetOrCreateUIExtensionNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto uiExtensionNode = ElementRegister::GetInstance()->GetSpecificItemById<UIExtensionNode>(nodeId);
    if (uiExtensionNode) {
        if (uiExtensionNode->GetTag() == tag) {
            return uiExtensionNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = uiExtensionNode->GetParent();
        if (parent) {
            parent->RemoveChild(uiExtensionNode);
        }
    }
    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    uiExtensionNode = AceType::MakeRefPtr<UIExtensionNode>(tag, nodeId, pattern, false);
    uiExtensionNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(uiExtensionNode);
    return uiExtensionNode;
}

HitTestResult UIExtensionNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId,
    ResponseLinkResult& responseLinkResult, bool isDispatch)
{
    auto testResult = FrameNode::TouchTest(
        globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, result, touchId, responseLinkResult);
    if (testResult == HitTestResult::OUT_OF_REGION) {
        return HitTestResult::OUT_OF_REGION;
    }
    if (touchRestrict.touchEvent.type == TouchType::HOVER_ENTER) {
        return testResult;
    }
    auto pattern = GetPattern<UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, testResult);
    auto context = GetContext();
    CHECK_NULL_RETURN(context, testResult);
    auto eventManager = context->GetEventManager();
    CHECK_NULL_RETURN(eventManager, testResult);
    auto delegate = AceType::MakeRefPtr<UIExtensionTouchDelegate>(pattern);
    eventManager->RegisterTouchDelegate(touchRestrict.touchEvent.id, delegate);
    return testResult;
}
} // namespace OHOS::Ace::NG
