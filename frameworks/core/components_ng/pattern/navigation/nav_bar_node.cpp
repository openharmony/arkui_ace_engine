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

#include "core/components_ng/pattern/navigation/nav_bar_node.h"

#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"

namespace OHOS::Ace::NG {
constexpr float TITLE_OFFSET_PERCENT  = 0.02f;

RefPtr<NavBarNode> NavBarNode::GetOrCreateNavBarNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<NavBarNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto navBarNode = AceType::MakeRefPtr<NavBarNode>(tag, nodeId, pattern);
    navBarNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(navBarNode);
    return navBarNode;
}

void NavBarNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    auto contentNode = GetContentNode();
    if (!contentNode) {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        contentNode = FrameNode::GetOrCreateFrameNode(
            V2::NAVBAR_CONTENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        SetContentNode(contentNode);
        AddChild(contentNode);

        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            auto navBarContentNode = AceType::DynamicCast<FrameNode>(contentNode);
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
                .edges = SAFE_AREA_EDGE_ALL };
            navBarContentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
        }
    }
    contentNode->AddChild(child);
}

void NavBarNode::InitSystemTransitionPop()
{
    // navabr do enter pop initialization
    float isRTL = GetLanguageDirection();
    SetTransitionType(PageTransitionType::ENTER_POP);
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    renderContext->RemoveClipWithRRect();
    auto translate = CalcTranslateForTransitionPopStart(frameSize, true);
    renderContext->UpdateTranslateInXY(translate);
    auto curTitleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    CHECK_NULL_VOID(curTitleBarNode);
    curTitleBarNode->GetRenderContext()->UpdateTranslateInXY(
        { frameSize.Width() * TITLE_OFFSET_PERCENT * isRTL, 0.0f });
}

void NavBarNode::SystemTransitionPushAction(bool isStart)
{
    // initialization or finish callBack
    if (isStart) {
        SetTransitionType(PageTransitionType::EXIT_PUSH);
    } else {
        GetRenderContext()->SetActualForegroundColor(Color::TRANSPARENT);
    }
    GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    auto titleNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    titleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
}

void NavBarNode::InitSoftTransitionPop()
{
    SetTransitionType(PageTransitionType::ENTER_POP);
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto translate = CalcTranslateForTransitionPopStart(frameSize, true);
    renderContext->UpdateTranslateInXY(translate);
}

void NavBarNode::SoftTransitionPushAction(bool isStart)
{
    if (isStart) {
        SetTransitionType(PageTransitionType::EXIT_PUSH);
    }
    GetRenderContext()->UpdateTranslateInXY({0.0f, 0.0f});
}

void NavBarNode::StartSoftTransitionPush()
{
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto translate = CalcTranslateForTransitionPushEnd(frameSize, false);
    renderContext->UpdateTranslateInXY(translate);
}

void NavBarNode::StartSoftTransitionPop()
{
    GetRenderContext()->UpdateTranslateInXY({0.0f, 0.0f});
}

void NavBarNode::StartSystemTransitionPush()
{
    // start EXIT_PUSH transition animation
    float isRTL = GetLanguageDirection();
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto translate = CalcTranslateForTransitionPushEnd(frameSize, false);
    renderContext->UpdateTranslateInXY(translate);

    auto titleNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);
    titleNode->GetRenderContext()->UpdateTranslateInXY(
        { frameSize.Width() * TITLE_OFFSET_PERCENT * isRTL, 0.0f });
}

void NavBarNode::StartSystemTransitionPop()
{
    // navabr start to do ENTER_POP animation
    GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    auto titleBarNode = AceType::DynamicCast<FrameNode>(GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    titleBarNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
}

bool NavBarNode::IsNodeInvisible(const RefPtr<FrameNode>& node)
{
    auto navigation = DynamicCast<NavigationGroupNode>(node);
    CHECK_NULL_RETURN(navigation, false);
    auto lastStandardIndex = navigation->GetLastStandardIndex();
    bool isInvisible = navigation->GetNavigationMode() == NavigationMode::STACK && lastStandardIndex >= 0;
    return isInvisible;
}

RefPtr<UINode> NavBarNode::GetNavigationNode()
{
    return GetParentFrameNode();
}
} // namespace OHOS::Ace::NG
