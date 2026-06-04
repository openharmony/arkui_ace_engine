/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_pattern.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_property.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"

namespace OHOS::Ace::NG {

void LazyColumnLayoutModel::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", "LazyColumnLayout", nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode("LazyColumnLayout", nodeId, []() {
        return AceType::MakeRefPtr<LazyColumnLayoutPattern>();
    });
    stack->Push(frameNode);
}

void LazyColumnLayoutModel::SetSpace(const Dimension& space)
{
    ACE_CHECK_LPX_ATTRIBUTE(space, LpxAttribute::LPX_SPACE);
    ACE_UPDATE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, Space, space);
}

void LazyColumnLayoutModel::SetAlignItems(HorizontalAlign align)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, HorizontalAlign, align);
}

void LazyColumnLayoutModel::SetOnVisibleIndexesChange(VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetOnVisibleIndexesChange(frameNode, std::move(onVisibleIndexesChange));
}

void LazyColumnLayoutModel::SetSpace(FrameNode* frameNode, const Dimension& space)
{
    ACE_CHECK_NODE_LPX_ATTRIBUTE(space, LpxAttribute::LPX_SPACE, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, Space, space, frameNode);
}

void LazyColumnLayoutModel::SetAlignItems(FrameNode* frameNode, HorizontalAlign align)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, HorizontalAlign, align, frameNode);
}

void LazyColumnLayoutModel::SetOnVisibleIndexesChange(
    FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyColumnLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

void LazyColumnLayoutModel::SetSticky(StickyStyle stickyStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, StickyStyle, stickyStyle);
}

void LazyColumnLayoutModel::SetSticky(FrameNode* frameNode, StickyStyle stickyStyle)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyColumnLayoutProperty, StickyStyle, stickyStyle, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<LazyColumnLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
}

void LazyColumnLayoutModel::SetHeader(std::function<void()>&& header)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    RefPtr<UINode> headerNode;
    if (header) {
        auto isBuilderNode = stack->IsBuilderNode();
        auto isExportTexture = stack->IsExportTexture();
        ScopedViewStackProcessor builderViewStackProcessor;
        stack = ViewStackProcessor::GetInstance();
        CHECK_NULL_VOID(stack);
        stack->SetIsBuilderNode(isBuilderNode);
        stack->SetIsExportTexture(isExportTexture);
        header();
        headerNode = stack->Finish();
        if (!headerNode) {
            TAG_LOGW(AceLogTag::ACE_LAZY_COLUMN, "LazyColumnLayout header builder produced no node");
        }
    }
    SetHeader(frameNode, headerNode);
}

void LazyColumnLayoutModel::SetFooter(std::function<void()>&& footer)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    RefPtr<UINode> footerNode;
    if (footer) {
        auto isBuilderNode = stack->IsBuilderNode();
        auto isExportTexture = stack->IsExportTexture();
        ScopedViewStackProcessor builderViewStackProcessor;
        stack = ViewStackProcessor::GetInstance();
        CHECK_NULL_VOID(stack);
        stack->SetIsBuilderNode(isBuilderNode);
        stack->SetIsExportTexture(isExportTexture);
        footer();
        footerNode = stack->Finish();
        if (!footerNode) {
            TAG_LOGW(AceLogTag::ACE_LAZY_COLUMN, "LazyColumnLayout footer builder produced no node");
        }
    }
    SetFooter(frameNode, footerNode);
}

void LazyColumnLayoutModel::SetHeader(FrameNode* frameNode, const RefPtr<UINode>& headerNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyColumnLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    if (!headerNode) {
        pattern->RemoveHeader();
        return;
    }
    pattern->AddHeader(headerNode);
}

void LazyColumnLayoutModel::SetFooter(FrameNode* frameNode, const RefPtr<UINode>& footerNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyColumnLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    if (!footerNode) {
        pattern->RemoveFooter();
        return;
    }
    pattern->AddFooter(footerNode);
}

void LazyColumnLayoutModel::RemoveHeader()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    RemoveHeader(frameNode);
}

void LazyColumnLayoutModel::RemoveFooter()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    RemoveFooter(frameNode);
}

void LazyColumnLayoutModel::RemoveHeader(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyColumnLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveHeader();
}

void LazyColumnLayoutModel::RemoveFooter(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyColumnLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveFooter();
}

} // namespace OHOS::Ace::NG
