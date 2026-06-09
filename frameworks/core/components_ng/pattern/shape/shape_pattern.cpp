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

#include "core/components_ng/pattern/shape/shape_pattern.h"

#include "base/log/ace_trace.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_ng/pattern/shape/shape_layout_algorithm.h"
#include "core/components_ng/pattern/shape/shape_overlay_modifier.h"

namespace OHOS::Ace::NG {
ShapePattern::~ShapePattern() = default;

RefPtr<LayoutAlgorithm> ShapePattern::CreateLayoutAlgorithm()
{
    ACE_UINODE_TRACE(GetHost());
    return MakeRefPtr<ShapeLayoutAlgorithm>();
}

RefPtr<PaintProperty> ShapePattern::CreatePaintProperty()
{
    ACE_UINODE_TRACE(GetHost());
    return MakeRefPtr<ShapePaintProperty>();
}

void ShapePattern::OnModifyDone()
{
    Pattern::CheckLocalized();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ShapePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->HasStrokeMiterLimit()) {
        auto miterLimit = paintProperty->GetStrokeMiterLimitValue();
        if (Negative(miterLimit)) {
            paintProperty->UpdateStrokeMiterLimit(ShapePaintProperty::STROKE_MITERLIMIT_DEFAULT);
        } else if (NonNegative(miterLimit) &&
            LessNotEqual(miterLimit, ShapePaintProperty::STROKE_MITERLIMIT_MIN)) {
            paintProperty->UpdateStrokeMiterLimit(ShapePaintProperty::STROKE_MITERLIMIT_MIN);
        }
    }
}

RefPtr<ShapePaintProperty> ShapePattern::GetAncestorPaintProperty()
{
    auto curFrameNode = GetHost();
    CHECK_NULL_RETURN(curFrameNode, nullptr);
    auto childNode = curFrameNode;
    ShapePaintProperty propertiesFromAncestor;
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(curFrameNode->GetAncestorNodeOfFrame(false));
    while (parentFrameNode) {
        auto parentPaintProperty = parentFrameNode->GetPaintProperty<ShapePaintProperty>();
        if (parentPaintProperty) {
            propertiesFromAncestor.UpdateShapeProperty(parentPaintProperty);
            UpdateForeground(parentFrameNode, childNode);
            auto pattern = AceType::DynamicCast<ShapeContainerPattern>(parentFrameNode->GetPattern());
            if (pattern) {
                pattern->AddChildShapeNode(WeakPtr<FrameNode>(childNode));
            }
        }
        curFrameNode = parentFrameNode;
        parentFrameNode = AceType::DynamicCast<FrameNode>(curFrameNode->GetAncestorNodeOfFrame(false));
    }
    return DynamicCast<ShapePaintProperty>(propertiesFromAncestor.Clone());
}

void ShapePattern::OnForegroundColorUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ShapePattern::UpdateForeground(RefPtr<FrameNode> parentFrameNode, RefPtr<FrameNode> childFrameNode)
{
    auto renderContext = parentFrameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto childRenderContext = childFrameNode->GetRenderContext();
    CHECK_NULL_VOID(childRenderContext);
    if (!childRenderContext->HasForegroundColor() && !childRenderContext->HasForegroundColorStrategy()) {
        if (renderContext->HasForegroundColor()) {
            childRenderContext->UpdateForegroundColor(renderContext->GetForegroundColorValue());
            childRenderContext->ResetForegroundColorStrategy();
            childRenderContext->UpdateForegroundColorFlag(false);
        } else if (renderContext->HasForegroundColorStrategy()) {
            childRenderContext->UpdateForegroundColorStrategy(renderContext->GetForegroundColorStrategyValue());
            childRenderContext->ResetForegroundColor();
            childRenderContext->UpdateForegroundColorFlag(false);
        }
    } else {
        if (!childRenderContext->GetForegroundColorFlag().value_or(false)) {
            if (renderContext->HasForegroundColor()) {
                childRenderContext->UpdateForegroundColor(renderContext->GetForegroundColorValue());
                childRenderContext->ResetForegroundColorStrategy();
                childRenderContext->UpdateForegroundColorFlag(false);
            } else if (renderContext->HasForegroundColorStrategy()) {
                childRenderContext->UpdateForegroundColorStrategy(renderContext->GetForegroundColorStrategyValue());
                childRenderContext->ResetForegroundColor();
                childRenderContext->UpdateForegroundColorFlag(false);
            }
        }
    }
}

bool ShapePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    return !(skipMeasure || dirty->SkipMeasureContent());
}
} // namespace OHOS::Ace::NG
