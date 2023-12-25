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
#include "core/interfaces/native/node/render_node_modifier.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {

RefPtr<RenderContext> GetRenderContext(UINode* UiNode)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(UiNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto context = frameNode->GetRenderContext();
    return context;
}

void AppendChild(NodeHandle node, NodeHandle child)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    auto* childNode = reinterpret_cast<UINode*>(child);
    auto childRef = Referenced::Claim<UINode>(childNode);
    auto childNumber = uiNode->GetChildren().size();
    uiNode->AddChild(childRef, childNumber);
}

void InsertChildAfter(NodeHandle node, NodeHandle child, NodeHandle sibling)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* childNode = reinterpret_cast<UINode*>(child);
    if (sibling == nullptr) {
        currentNode->AddChild(Referenced::Claim<UINode>(childNode));
    } else {
        auto* siblingNode = reinterpret_cast<UINode*>(sibling);
        auto index = currentNode->GetChildIndex(Referenced::Claim<UINode>(siblingNode));
        currentNode->AddChild(Referenced::Claim<UINode>(childNode), index + 1);
    }
}

void RemoveChild(NodeHandle node, NodeHandle child)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto* childNode = reinterpret_cast<UINode*>(child);
    currentNode->RemoveChild(Referenced::Claim<UINode>(childNode));
}

void ClearChildren(NodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    currentNode->Clean();
}

void SetClipToFrame(NodeHandle node, bool useClip)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(useClip);
}

void SetRotation(NodeHandle node, double rotationX, double rotationY, double rotationZ)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    Dimension first = Dimension(rotationX, DimensionUnit::VP);
    Dimension second = Dimension(rotationY, DimensionUnit::VP);
    Dimension third = Dimension(rotationZ, DimensionUnit::VP);
    renderContext->SetRotation(first.ConvertToPx(), second.ConvertToPx(), third.ConvertToPx());
}

void SetShadowColor(NodeHandle node, uint32_t color)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowColor(color);
}

void SetShadowOffset(NodeHandle node, double offsetX, double offsetY)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    Dimension first = Dimension(offsetX, DimensionUnit::VP);
    Dimension second = Dimension(offsetY, DimensionUnit::VP);
    renderContext->SetShadowOffset(first.ConvertToPx(), second.ConvertToPx());
}

void SetShadowAlpha(NodeHandle node, float alpha)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowAlpha(alpha);
}

void SetShadowElevation(NodeHandle node, float elevation)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowElevation(elevation);
}

void SetShadowRadius(NodeHandle node, float radius)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    auto renderContext = GetRenderContext(currentNode);
    CHECK_NULL_VOID(renderContext);
    renderContext->SetShadowRadius(radius);
}

void Invalidate(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RenderNodePattern>();
    pattern->Invalidate();
}

ArkUIRenderNodeModifierAPI GetRenderNodeModifier()
{
    static const ArkUIRenderNodeModifierAPI modifier = { AppendChild, InsertChildAfter, RemoveChild, ClearChildren,
        SetClipToFrame, SetRotation, SetShadowColor, SetShadowOffset, SetShadowAlpha, SetShadowElevation,
        SetShadowRadius, Invalidate };

    return modifier;
}
} // namespace OHOS::Ace::NG
