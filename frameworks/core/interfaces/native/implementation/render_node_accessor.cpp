/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RenderNodeAccessor {
void DestroyPeerImpl(Ark_RenderNode peer)
{
}
Ark_RenderNode CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void AppendChildImpl(Ark_RenderNode peer,
                     Ark_RenderNode node)
{
}
void InsertChildAfterImpl(Ark_RenderNode peer,
                          Ark_RenderNode child,
                          const Ark_Union_RenderNode_Undefined* sibling)
{
}
void RemoveChildImpl(Ark_RenderNode peer,
                     Ark_RenderNode node)
{
}
void ClearChildrenImpl(Ark_RenderNode peer)
{
}
Ark_Union_RenderNode_Undefined GetChildImpl(Ark_RenderNode peer,
                                            const Ark_Number* index)
{
    return {};
}
Ark_Union_RenderNode_Undefined GetFirstChildImpl(Ark_RenderNode peer)
{
    return {};
}
Ark_Union_RenderNode_Undefined GetNextSiblingImpl(Ark_RenderNode peer)
{
    return {};
}
Ark_Union_RenderNode_Undefined GetPreviousSiblingImpl(Ark_RenderNode peer)
{
    return {};
}
void DrawImpl(Ark_RenderNode peer,
              const Ark_DrawContext* context)
{
}
void InvalidateImpl(Ark_RenderNode peer)
{
}
void DisposeImpl(Ark_RenderNode peer)
{
}
Ark_Number GetBackgroundColorImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBackgroundColorImpl(Ark_RenderNode peer,
                            const Ark_Number* backgroundColor)
{
}
Ark_Boolean GetClipToFrameImpl(Ark_RenderNode peer)
{
    return {};
}
void SetClipToFrameImpl(Ark_RenderNode peer,
                        Ark_Boolean clipToFrame)
{
}
Ark_Number GetOpacityImpl(Ark_RenderNode peer)
{
    return {};
}
void SetOpacityImpl(Ark_RenderNode peer,
                    const Ark_Number* opacity)
{
}
Ark_Size GetSizeImpl(Ark_RenderNode peer)
{
    return {};
}
void SetSizeImpl(Ark_RenderNode peer,
                 const Ark_Size* size)
{
}
Ark_Position GetPositionImpl(Ark_RenderNode peer)
{
    return {};
}
void SetPositionImpl(Ark_RenderNode peer,
                     const Ark_Position* position)
{
}
Ark_Frame GetFrameImpl(Ark_RenderNode peer)
{
    return {};
}
void SetFrameImpl(Ark_RenderNode peer,
                  const Ark_Frame* frame)
{
}
Ark_Vector2 GetPivotImpl(Ark_RenderNode peer)
{
    return {};
}
void SetPivotImpl(Ark_RenderNode peer,
                  const Ark_Vector2* pivot)
{
}
Ark_Vector2 GetScaleImpl(Ark_RenderNode peer)
{
    return {};
}
void SetScaleImpl(Ark_RenderNode peer,
                  const Ark_Vector2* scale)
{
}
Ark_Vector2 GetTranslationImpl(Ark_RenderNode peer)
{
    return {};
}
void SetTranslationImpl(Ark_RenderNode peer,
                        const Ark_Vector2* translation)
{
}
Ark_Vector3 GetRotationImpl(Ark_RenderNode peer)
{
    return {};
}
void SetRotationImpl(Ark_RenderNode peer,
                     const Ark_Vector3* rotation)
{
}
Ark_Matrix4 GetTransformImpl(Ark_RenderNode peer)
{
    return {};
}
void SetTransformImpl(Ark_RenderNode peer,
                      const Ark_Matrix4* transform)
{
}
Ark_Number GetShadowColorImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowColorImpl(Ark_RenderNode peer,
                        const Ark_Number* shadowColor)
{
}
Ark_Vector2 GetShadowOffsetImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowOffsetImpl(Ark_RenderNode peer,
                         const Ark_Vector2* shadowOffset)
{
}
Ark_String GetLabelImpl(Ark_RenderNode peer)
{
    return {};
}
void SetLabelImpl(Ark_RenderNode peer,
                  const Ark_String* label)
{
}
Ark_Number GetShadowAlphaImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowAlphaImpl(Ark_RenderNode peer,
                        const Ark_Number* shadowAlpha)
{
}
Ark_Number GetShadowElevationImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowElevationImpl(Ark_RenderNode peer,
                            const Ark_Number* shadowElevation)
{
}
Ark_Number GetShadowRadiusImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShadowRadiusImpl(Ark_RenderNode peer,
                         const Ark_Number* shadowRadius)
{
}
Ark_EdgeStyles GetBorderStyleImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderStyleImpl(Ark_RenderNode peer,
                        const Ark_EdgeStyles* borderStyle)
{
}
Ark_Edges GetBorderWidthImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderWidthImpl(Ark_RenderNode peer,
                        const Ark_Edges* borderWidth)
{
}
Ark_Edges GetBorderColorImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderColorImpl(Ark_RenderNode peer,
                        const Ark_Edges* borderColor)
{
}
Ark_BorderRadiuses_graphics GetBorderRadiusImpl(Ark_RenderNode peer)
{
    return {};
}
void SetBorderRadiusImpl(Ark_RenderNode peer,
                         const Ark_BorderRadiuses_graphics* borderRadius)
{
}
Ark_ShapeMask GetShapeMaskImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShapeMaskImpl(Ark_RenderNode peer,
                      Ark_ShapeMask shapeMask)
{
}
Ark_ShapeClip GetShapeClipImpl(Ark_RenderNode peer)
{
    return {};
}
void SetShapeClipImpl(Ark_RenderNode peer,
                      Ark_ShapeClip shapeClip)
{
}
Ark_Boolean GetMarkNodeGroupImpl(Ark_RenderNode peer)
{
    return {};
}
void SetMarkNodeGroupImpl(Ark_RenderNode peer,
                          Ark_Boolean markNodeGroup)
{
}
Ark_LengthMetricsUnit GetLengthMetricsUnitImpl(Ark_RenderNode peer)
{
    return {};
}
void SetLengthMetricsUnitImpl(Ark_RenderNode peer,
                              Ark_LengthMetricsUnit lengthMetricsUnit)
{
}
} // RenderNodeAccessor
const GENERATED_ArkUIRenderNodeAccessor* GetRenderNodeAccessor()
{
    static const GENERATED_ArkUIRenderNodeAccessor RenderNodeAccessorImpl {
        RenderNodeAccessor::DestroyPeerImpl,
        RenderNodeAccessor::CtorImpl,
        RenderNodeAccessor::GetFinalizerImpl,
        RenderNodeAccessor::AppendChildImpl,
        RenderNodeAccessor::InsertChildAfterImpl,
        RenderNodeAccessor::RemoveChildImpl,
        RenderNodeAccessor::ClearChildrenImpl,
        RenderNodeAccessor::GetChildImpl,
        RenderNodeAccessor::GetFirstChildImpl,
        RenderNodeAccessor::GetNextSiblingImpl,
        RenderNodeAccessor::GetPreviousSiblingImpl,
        RenderNodeAccessor::DrawImpl,
        RenderNodeAccessor::InvalidateImpl,
        RenderNodeAccessor::DisposeImpl,
        RenderNodeAccessor::GetBackgroundColorImpl,
        RenderNodeAccessor::SetBackgroundColorImpl,
        RenderNodeAccessor::GetClipToFrameImpl,
        RenderNodeAccessor::SetClipToFrameImpl,
        RenderNodeAccessor::GetOpacityImpl,
        RenderNodeAccessor::SetOpacityImpl,
        RenderNodeAccessor::GetSizeImpl,
        RenderNodeAccessor::SetSizeImpl,
        RenderNodeAccessor::GetPositionImpl,
        RenderNodeAccessor::SetPositionImpl,
        RenderNodeAccessor::GetFrameImpl,
        RenderNodeAccessor::SetFrameImpl,
        RenderNodeAccessor::GetPivotImpl,
        RenderNodeAccessor::SetPivotImpl,
        RenderNodeAccessor::GetScaleImpl,
        RenderNodeAccessor::SetScaleImpl,
        RenderNodeAccessor::GetTranslationImpl,
        RenderNodeAccessor::SetTranslationImpl,
        RenderNodeAccessor::GetRotationImpl,
        RenderNodeAccessor::SetRotationImpl,
        RenderNodeAccessor::GetTransformImpl,
        RenderNodeAccessor::SetTransformImpl,
        RenderNodeAccessor::GetShadowColorImpl,
        RenderNodeAccessor::SetShadowColorImpl,
        RenderNodeAccessor::GetShadowOffsetImpl,
        RenderNodeAccessor::SetShadowOffsetImpl,
        RenderNodeAccessor::GetLabelImpl,
        RenderNodeAccessor::SetLabelImpl,
        RenderNodeAccessor::GetShadowAlphaImpl,
        RenderNodeAccessor::SetShadowAlphaImpl,
        RenderNodeAccessor::GetShadowElevationImpl,
        RenderNodeAccessor::SetShadowElevationImpl,
        RenderNodeAccessor::GetShadowRadiusImpl,
        RenderNodeAccessor::SetShadowRadiusImpl,
        RenderNodeAccessor::GetBorderStyleImpl,
        RenderNodeAccessor::SetBorderStyleImpl,
        RenderNodeAccessor::GetBorderWidthImpl,
        RenderNodeAccessor::SetBorderWidthImpl,
        RenderNodeAccessor::GetBorderColorImpl,
        RenderNodeAccessor::SetBorderColorImpl,
        RenderNodeAccessor::GetBorderRadiusImpl,
        RenderNodeAccessor::SetBorderRadiusImpl,
        RenderNodeAccessor::GetShapeMaskImpl,
        RenderNodeAccessor::SetShapeMaskImpl,
        RenderNodeAccessor::GetShapeClipImpl,
        RenderNodeAccessor::SetShapeClipImpl,
        RenderNodeAccessor::GetMarkNodeGroupImpl,
        RenderNodeAccessor::SetMarkNodeGroupImpl,
        RenderNodeAccessor::GetLengthMetricsUnitImpl,
        RenderNodeAccessor::SetLengthMetricsUnitImpl,
    };
    return &RenderNodeAccessorImpl;
}

struct RenderNodePeer {
    virtual ~RenderNodePeer() = default;
};
}
