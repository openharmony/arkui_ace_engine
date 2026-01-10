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
#include "core/components_ng/pattern/container_modal/static/container_modal_static_view.h"

#include "core/components/theme/advanced_pattern_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/xbar_proxy_wrapper.h"
#include "core/components_ng/pattern/container_modal/container_modal_utils.h"
#include "core/components_ng/pattern/container_modal/static/container_modal_static_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> ContainerModalStaticView::Create(RefPtr<FrameNode>& content)
{
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalStaticPattern>());
    ACE_UINODE_TRACE(containerModalNode);
    auto stack = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto controlButtonsRow = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(false));

    column->AddChild(BuildTitle(containerModalNode));
    stack->AddChild(content);
    column->AddChild(stack);
    column->AddChild(BuildGestureRow(containerModalNode));
    auto containerPattern = containerModalNode->GetPattern<ContainerModalStaticPattern>();
    CHECK_NULL_RETURN(containerPattern, nullptr);
    containerModalNode->AddChild(column);
    containerModalNode->AddChild(BuildTitle(containerModalNode, true));

    // Confirm that if it is a pure Cangjie application, the node construction is completed on the C side
    if (customControlButtonBuilder_) {
        WeakPtr<ContainerModalStaticPattern> weakPattern = controlButtonsRow->GetPattern<ContainerModalStaticPattern>();
        containerModalNode->AddChild(customControlButtonBuilder_(weakPattern, controlButtonsRow));
    } else {
        containerModalNode->AddChild(BuildCustomButtonRow(containerModalNode, controlButtonsRow));
    }
    containerPattern->Init();
    return containerModalNode;
}

RefPtr<FrameNode> ContainerModalStaticView::BuildTitle(RefPtr<FrameNode>& containerNode, bool isFloatingTitle)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalStaticView BuildTitle called");
    auto titleRow = BuildTitleContainer(containerNode, isFloatingTitle);
    CHECK_NULL_RETURN(titleRow, nullptr);
    return titleRow;
}

RefPtr<FrameNode> ContainerModalStaticView::BuildTitleContainer(RefPtr<FrameNode>& containerNode, bool isFloatingTitle)
{
    CHECK_NULL_RETURN(containerNode, nullptr);
    auto containerPattern = containerNode->GetPattern<ContainerModalStaticPattern>();
    CHECK_NULL_RETURN(containerPattern, nullptr);
    auto containerTitleRow = BuildTitleRow(isFloatingTitle);
    CHECK_NULL_RETURN(containerTitleRow, nullptr);

    RefPtr<UINode> customTitleBarNode;
    if (customTitileBuilder_) {
        customTitleBarNode = customTitileBuilder_();
    } else {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_RETURN(containerTitleRow, nullptr);
        RefPtr<XbarComponent> xbarComponent = nullptr;
        if (isFloatingTitle) {
            TAG_LOGI(AceLogTag::ACE_APPBAR, "BuildTitleContainer isFloatingTitle");
            xbarComponent = XbarProxyWrapper::GetInstance()->CreateXBarComponent(0, pipeline->GetInstanceId());
            containerPattern->SetCustomFloatingTitle(xbarComponent);
        } else {
            TAG_LOGI(AceLogTag::ACE_APPBAR, "BuildTitleContainer fixed");
            xbarComponent = XbarProxyWrapper::GetInstance()->CreateXBarComponent(0, pipeline->GetInstanceId());
            containerPattern->SetCustomTitle(xbarComponent);
        }
        CHECK_NULL_RETURN(xbarComponent, nullptr);
        auto customNode = reinterpret_cast<UINode*>(xbarComponent->GetUINodePointFromXbar());
        customTitleBarNode = AceType::Claim(customNode);
    }
    CHECK_NULL_RETURN(customTitleBarNode, nullptr);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "BuildTitleContainer xbarComponent is not null");
    auto customTitleBarRow = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(false));
    customTitleBarRow->AddChild(customTitleBarNode);
    containerTitleRow->AddChild(customTitleBarRow);
    return containerTitleRow;
}

RefPtr<FrameNode> ContainerModalStaticView::BuildCustomButtonRow(
    RefPtr<FrameNode>& containerNode, RefPtr<FrameNode>& containerRow)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalStaticView BuildCustomButtonRow called");
    CHECK_NULL_RETURN(containerNode, nullptr);
    auto containerPattern = containerNode->GetPattern<ContainerModalStaticPattern>();
    CHECK_NULL_RETURN(containerPattern, nullptr);
    CHECK_NULL_RETURN(containerRow, nullptr);
    auto pipeline = containerNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto xbarComponent = XbarProxyWrapper::GetInstance()->CreateXBarComponent(1, pipeline->GetInstanceId());
    CHECK_NULL_RETURN(xbarComponent, nullptr);
    containerPattern->SetCustomButton(xbarComponent);
    auto customButtonNode = reinterpret_cast<UINode*>(xbarComponent->GetUINodePointFromXbar());
    CHECK_NULL_RETURN(customButtonNode, nullptr);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalStaticView add customButtonNode");
    containerRow->AddChild(AceType::Claim(customButtonNode));
    return containerRow;
}

} // namespace OHOS::Ace::NG
