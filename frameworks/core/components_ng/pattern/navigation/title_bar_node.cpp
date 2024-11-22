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

#include "core/components_ng/pattern/navigation/title_bar_node.h"

#include "core/components_ng/pattern/navigation/title_bar_pattern.h"

namespace OHOS::Ace::NG {

TitleBarNode::TitleBarNode(const std::string& tag, int32_t nodeId)
    : FrameNode(tag, nodeId, MakeRefPtr<TitleBarPattern>())
{}

TitleBarNode::~TitleBarNode()
{
    auto pipeline = GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto titleBarPattern = GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    auto backButtonDialog = titleBarPattern->GetBackButtonDialogNode();
    if (backButtonDialog) {
        overlayManager->CloseDialog(backButtonDialog);
    }
    auto menuItemDialog = titleBarPattern->GetLargeFontPopUpDialogNode();
    if (menuItemDialog) {
        overlayManager->CloseDialog(menuItemDialog);
    }
}

RefPtr<TitleBarNode> TitleBarNode::GetOrCreateTitleBarNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<TitleBarNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>(tag, nodeId, pattern);
    titleBarNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(titleBarNode);
    return titleBarNode;
}

// The function is only used for fast preview.
void TitleBarNode::FastPreviewUpdateChild(int32_t slot, const RefPtr<UINode>& newChild)
{
    auto oldChild = GetChildAtIndex(slot);
    if (title_ == oldChild) {
        title_ = newChild;
    } else if (menu_ == oldChild) {
        menu_ = newChild;
    }
    UINode::FastPreviewUpdateChild(slot, newChild);
}

void TitleBarNode::MarkIsInitialTitle(bool isInitialTitle)
{
    auto pattern = GetPattern<TitleBarPattern>();
    pattern->MarkIsInitialTitle(isInitialTitle);
}

void TitleBarNode::OnAttachToMainTree(bool recursive)
{
    FrameNode::OnAttachToMainTree(recursive);
    auto layoutProperty = GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_THIRTEEN) &&
        layoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) == TitleBarParentType::NAVBAR) {
        auto pattern = GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(pattern);
        // register sideBar button info update callback
        pattern->InitSideBarButtonUpdateCallbackIfNeeded();
    }
}
} // namespace OHOS::Ace::NG
