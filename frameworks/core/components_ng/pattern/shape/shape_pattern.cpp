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
namespace OHOS::Ace::NG {
bool ShapePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }

                LOGE("wch  shapepattern  CreateNodePaintMethod-------------------------------------");
    auto curFrameNode = GetHost();
    LOGE("wch  shapepattern  curFrameNode isnull %{public}d-------------------------------------",!!curFrameNode);
    //CHECK_NULL_RETURN(curFrameNode, nullptr);
    auto renderContext = DynamicCast<RosenRenderContext>(curFrameNode->GetRenderContext());
    LOGE("wch  shapepattern renderContext isnull %{public}d-------------------------------------",!!renderContext);

    auto rsNode = renderContext->GetRSNode();
    LOGE("wch  shapepattern rsNode isnull  %{public}d-------------------------------------",!!rsNode);
    if(!rsNode){
        return true;
    }
   
    auto geoNode = curFrameNode->GetGeometryNode();
    if(!geoNode){
        return true;
    }

    SizeF sizeF = geoNode->GetContentSize();
    LOGE("wch  shapepattern sizeF.IsPositive  %{public}d-------------------------------------",sizeF.IsPositive());
    LOGE("wch  shapepattern width  %{public}lf-------------------------------------",sizeF.Width());
    LOGE("wch  shapepattern height   %{public}lf-------------------------------------",sizeF.Height());
    auto containerPaintProperty = curFrameNode->GetPaintProperty<ContainerPaintProperty>();
    if(containerPaintProperty->HasShapeViewBox()){
        LOGE("wch  shapepattern shapeViewBoxOpt->IsValid()  %{public}d-------------------------------------",containerPaintProperty->GetShapeViewBoxValue().IsValid());
        LOGE("wch  shapepattern shapeViewBoxOpt->Left()  %{public}lf-------------------------------------",containerPaintProperty->GetShapeViewBoxValue().Left().Value());
        LOGE("wch  shapepattern shapeViewBoxOpt->Top() %{public}lf-------------------------------------",containerPaintProperty->GetShapeViewBoxValue().Top().Value());
        if(containerPaintProperty->GetShapeViewBoxValue().IsValid()){
            double portWidth= containerPaintProperty->GetShapeViewBoxValue().Width().ConvertToPx();
            double portHeight = containerPaintProperty->GetShapeViewBoxValue().Height().ConvertToPx();
            double portLeft = containerPaintProperty->GetShapeViewBoxValue().Left().ConvertToPx();
            double protTop = containerPaintProperty->GetShapeViewBoxValue().Top().ConvertToPx();
            double scale = std::min(sizeF.Width()/portWidth,sizeF.Height()/portHeight);
            double tx = sizeF.Width() * 0.5 - (portWidth * 0.5 + portLeft) * scale;
            double ty = sizeF.Height() * 0.5 - (portHeight * 0.5 + protTop) * scale;

            LOGE("wch  shapepattern tx   %{public}lf-------------------------------------",tx);
            LOGE("wch  shapepattern ty   %{public}lf-------------------------------------",ty);
            rsNode->SetClipToFrame(true);
           /* rsNode->SetPivot(0.0f, 0.0f);
            rsNode->SetScale(static_cast<float>(scale));
            rsNode->SetTranslate({ static_cast<float>(tx), static_cast<float>(ty) });*/
            
           for(const auto child : curFrameNode->GetChildren()){
                auto childFrameNode = DynamicCast<FrameNode>(child);
                LOGE("wch  shapepattern childFrameNode   %{public}d-------------------------------------",!!childFrameNode);

                if(!childFrameNode){
                    continue;
                }
                auto childRenderContext = DynamicCast<RosenRenderContext>(curFrameNode->GetRenderContext());
                auto childRsNode = childRenderContext->GetRSNode();
                LOGE("wch  shapepattern childRsNode   %{public}d-------------------------------------",!!childRsNode);
                if(!childRsNode){
                    continue;
                }
                 LOGE("wch  shapepattern scale  %{public}lf-------------------------------------",scale);
                childRsNode->SetPivot(0.0f, 0.0f);
                childRsNode->SetScale(static_cast<float>(scale));
                childRsNode->SetTranslate({ static_cast<float>(tx), static_cast<float>(ty) });
            }
           
        }
    }
    return true;
}
} // namespace OHOS::Ace::NG