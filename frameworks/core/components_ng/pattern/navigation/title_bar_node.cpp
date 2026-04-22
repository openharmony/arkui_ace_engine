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

#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/button/button_layout_property.h"

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
    ACE_UINODE_TRACE(nodeId);
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
    menuBarChangeListenerId_ =
        AppBarView::AddRectChangeListener(GetContextRefPtr(), [weakTitleBar = WeakClaim(this)](const RectF& rect) {
            auto titleBarNode = weakTitleBar.Upgrade();
            CHECK_NULL_VOID(titleBarNode);
            auto context = titleBarNode->GetContext();
            CHECK_NULL_VOID(context);
            titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            context->RequestFrame();
        });
    auto parent = GetParent();
    while (parent) {
        auto tag = parent->GetTag();
        if (tag == V2::SHEET_PAGE_TAG || tag == V2::MODAL_PAGE_TAG) {
            isParentModalOrSheet_ = true;
        }
        parent = parent->GetParent();
    }
}

void TitleBarNode::OnDetachFromMainTree(bool recursive, PipelineContext* context)
{
    FrameNode::OnDetachFromMainTree(recursive, context);
    if (menuBarChangeListenerId_ != -1) {
        AppBarView::RemoveRectChangeListener(Claim(context), menuBarChangeListenerId_);
    }
    isParentModalOrSheet_ = false;
}

void TitleBarNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    FrameNode::ToJsonValue(json, filter);
    auto titleBarPattern = GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    auto titleBarOptions = titleBarPattern->GetTitleBarOptions();
    titleBarOptions.ToJsonValue(json, filter);
}

bool TitleBarNode::IsChildEmpty() const
{
    bool isMenuEmpty = menu_ ? menu_->GetChildren().empty() : true;
    return !title_ && !subtitle_ && !backButton_ && isMenuEmpty;
}

void TitleBarNode::UpdateJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    SetTitleJsonValue(json, filter);
    SetMenuJsonValue(json, filter);
    auto backButton = AceType::DynamicCast<FrameNode>(backButton_);
    CHECK_NULL_VOID(backButton);
    auto layoutProperty = backButton->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
        return;
    }
    auto& borderWidth = layoutProperty->GetBorderWidthProperty();
    CHECK_NULL_VOID(borderWidth);
    auto info = JsonUtil::Create(true);
    info->Put("iconWidth", borderWidth->ToString().c_str());
    auto renderContext = backButton->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto iconColor = renderContext->GetBorderColor();
    info->Put("iconColor", iconColor->ToString().c_str());
    json->PutExtAttr("backButton", info, filter);
}

void TitleBarNode::SetTitleJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto mainTitleNode = AceType::DynamicCast<FrameNode>(title_);
    CHECK_NULL_VOID(mainTitleNode);
    auto titleBarLayoutProperty = GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto textLayoutProperty = mainTitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (titleBarLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
        return;
    }
    auto titleVal = JsonUtil::Create(true);
    titleVal->Put("titlePrimaryColor",
        textLayoutProperty->GetTextColorValue(Color()).ColorToString().c_str());
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    titleVal->Put("miniMinFontSize", theme->GetTitleFontSizeMin().ToString().c_str());
    titleVal->Put("fullMinFontSize", theme->GetTitleFontSize().ToString().c_str());
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    titleVal->Put("titleBarHeight", frameSize.Height());
    json->PutExtAttr("titleFont", titleVal, filter);
}

void TitleBarNode::SetMenuJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    CHECK_NULL_VOID(menu_);
    auto parent = AceType::DynamicCast<NavDestinationNodeBase>(GetParent());

    CHECK_NULL_VOID(parent);
    if (parent->GetPrevMenuIsCustomValue(false)) {
        return;
    }
    auto info = JsonUtil::Create(true);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    info->Put("iconBorderWidth", theme->GetIconBorderWidth().ToString().c_str());
    info->Put("iconBorderColor", theme->GetIconBorderColor().ColorToString().c_str());
    info->Put("focusPadding", theme->GetMenuItemFocusPadding().ToString().c_str());
    info->Put("focusBlendBgColor",
        theme->GetNavigationFocusBlendBgColor().ColorToString().c_str());
    json->PutExtAttr("menuIcon", info, filter);
}
} // namespace OHOS::Ace::NG
