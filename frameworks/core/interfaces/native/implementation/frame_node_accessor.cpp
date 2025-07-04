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
#include "ui/base/geometry/dimension.h"
#include "ui/base/utils/utils.h"

#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/view_model_bridge.h"
#include "core/interfaces/native/implementation/ui_common_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {
enum class ExpandMode : uint32_t {
    NOT_EXPAND = 0,
    EXPAND,
    LAZY_EXPAND,
};
// same as inner defines in property.h
typedef enum {
    ARKUI_DIRTY_FLAG_MEASURE = 0b1,
    ARKUI_DIRTY_FLAG_LAYOUT = 0b10,
    /** mark the node need to do attribute diff to drive update. */
    ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF = 0b100,
    ARKUI_DIRTY_FLAG_MEASURE_SELF = 0b1000,
    ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_PARENT = 0b10000,
    ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST = 0b100000,
    ARKUI_DIRTY_FLAG_RENDER = 0b1000000,
    ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_CHILD = 0b1000000000,
} ArkUIDirtyFlag;
}
std::map<int32_t, FrameNodePeer> FrameNodePeer::peerMap_;
namespace OHOS::Ace::NG::GeneratedModifier {
namespace FrameNodeAccessor {
void DestroyPeerImpl(Ark_FrameNode peer)
{
}
Ark_FrameNode ConstructImpl(Ark_UIContext uiContext)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsModifiableImpl(Ark_FrameNode peer)
{
    return {};
}
void AppendChildImpl(Ark_FrameNode peer,
                     Ark_FrameNode node)
{
}
void InsertChildAfterImpl(Ark_FrameNode peer,
                          Ark_FrameNode child,
                          Ark_FrameNode sibling)
{
}
void RemoveChildImpl(Ark_FrameNode peer,
                     Ark_FrameNode node)
{
}
void ClearChildrenImpl(Ark_FrameNode peer)
{
}
Ark_FrameNode GetChildImpl(Ark_FrameNode peer,
                           const Ark_Number* index,
                           const Ark_Number* expandMode)
{
    return {};
}
Ark_FrameNode GetFirstChildImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_FrameNode GetNextSiblingImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_FrameNode GetPreviousSiblingImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_FrameNode GetParentImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Int32 GetChildrenCountImpl(Ark_FrameNode peer)
{
    return {};
}
void DisposeImpl(Ark_FrameNode peer)
{
}
Ark_String GetIdImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Number GetUniqueIdImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_String GetNodeTypeImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Number GetOpacityImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Boolean IsVisibleImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Boolean IsClipToFrameImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Boolean IsAttachedImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Object GetInspectorInfoImpl(Ark_FrameNode peer)
{
    return {};
}
void InvalidateImpl(Ark_FrameNode peer)
{
}
void DisposeTreeImpl(Ark_FrameNode peer)
{
}
void SetCrossLanguageOptionsImpl(Ark_FrameNode peer,
                                 const Ark_CrossLanguageOptions* options)
{
}
Ark_CrossLanguageOptions GetCrossLanguageOptionsImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode->isCrossLanguageAttributeSetting();
}

Ark_Number GetIdByFrameNodeImpl(Ark_FrameNode peer, Ark_FrameNode node)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(-1);
    auto currentNode = FrameNodePeer::GetFrameNodeByPeer(node);
    CHECK_NULL_RETURN(currentNode, errValue);
    auto nodeId = currentNode->GetId();
    return Converter::ArkValue<Ark_Number>(nodeId);
}

static GENERATED_Ark_NodeType ParseNodeType(std::string& type)
{
    static const std::unordered_map<std::string, GENERATED_Ark_NodeType> typeMap = {
        { "List", GENERATED_ARKUI_LIST },
        { "Search", GENERATED_ARKUI_SEARCH },
        { "TextArea", GENERATED_ARKUI_TEXT_AREA },
        { "TextInput", GENERATED_ARKUI_TEXT_INPUT },
        { "Text", GENERATED_ARKUI_TEXT },
    };
    GENERATED_Ark_NodeType nodeType = GENERATED_ARKUI_CUSTOM_NODE;
    auto iter = typeMap.find(type);
    if (iter != typeMap.end()) {
        nodeType = iter->second;
    }
    return nodeType;
}

Ark_FrameNode CreateTypedFrameNodeImpl(const Ark_String* type)
{
    auto valueType = Converter::Convert<std::string>(*type);
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    GENERATED_Ark_NodeType nodeType = ParseNodeType(valueType);
    if (nodeType == GENERATED_ARKUI_CUSTOM_NODE) {
        return nullptr;
    }
    auto node =  OHOS::Ace::NG::GeneratedBridge::CreateNode(nodeType, nodeId, 0);
    CHECK_NULL_RETURN(node, nullptr);
    auto newNode = AceType::Claim(reinterpret_cast<FrameNode*>(node));
    newNode->SetIsArkTsFrameNode(true);
    newNode->DecRefCount();
    return FrameNodePeer::Create(newNode);
}

Ark_Position GetPositionToParentImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToParentImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto currFrameRect = frameNode->GetRectWithRender();
    auto offset = currFrameRect.GetOffset();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}

Ark_Position GetPositionToScreenImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToScreenImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetPositionToScreen();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}

Ark_Position GetPositionToWindowImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToWindowImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetOffsetRelativeToWindow();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}

Ark_Position GetPositionToParentWithTransformImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToParentWithTransformImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetPositionToParentWithTransform();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}

Ark_Position GetPositionToScreenWithTransformImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToScreenWithTransformImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetPositionToScreenWithTransform();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}

Ark_Position GetPositionToWindowWithTransform1Impl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToWindowWithTransform1Impl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetPositionToWindowWithTransform();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}

Ark_Size GetMeasuredSizeImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetMeasuredSizeImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, {});
    auto size = geometryNode->GetFrameSize();
    return Converter::ArkValue<Ark_Size>(size);
}

Ark_Position GetLayoutPositionImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetLayoutPositionImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, {});
    auto offset = geometryNode->GetMarginFrameOffset();
    return Converter::ArkValue<Ark_Position>(offset);
}

Ark_EdgesLengthMetrics GetUserConfigBorderWidthImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetUserConfigBorderWidthImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto borderWidth = ViewAbstract::GetLayoutBorderWidth(AceType::RawPtr(frameNode));
    Ark_EdgesLengthMetrics retValue = {
        .top = GetOptNumberFromDimension(borderWidth.topDimen),
        .topUnit = GetOptLengthUnitFromDimension(borderWidth.topDimen),
        .left = GetOptNumberFromDimension(borderWidth.leftDimen),
        .leftUnit = GetOptLengthUnitFromDimension(borderWidth.leftDimen),
        .bottom = GetOptNumberFromDimension(borderWidth.bottomDimen),
        .bottomUnit = GetOptLengthUnitFromDimension(borderWidth.bottomDimen),
        .right = GetOptNumberFromDimension(borderWidth.rightDimen),
        .rightUnit = GetOptLengthUnitFromDimension(borderWidth.rightDimen),
    };
    return retValue;
}

Ark_EdgesLengthMetrics GetUserConfigPaddingImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetUserConfigPaddingImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto padding = ViewAbstract::GetPadding(AceType::RawPtr(frameNode));
    Ark_EdgesLengthMetrics retValue = {
        .top = GetOptNumberFromCalcLength(padding.top),
        .topUnit = GetOptLengthUnitFromCalcLength(padding.top),
        .left = GetOptNumberFromCalcLength(padding.left),
        .leftUnit = GetOptLengthUnitFromCalcLength(padding.left),
        .bottom = GetOptNumberFromCalcLength(padding.bottom),
        .bottomUnit = GetOptLengthUnitFromCalcLength(padding.bottom),
        .right = GetOptNumberFromCalcLength(padding.right),
        .rightUnit = GetOptLengthUnitFromCalcLength(padding.right),
    };
    return retValue;
}

Ark_EdgesLengthMetrics GetUserConfigMarginImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetUserConfigMarginImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto margin = ViewAbstract::GetMargin(AceType::RawPtr(frameNode));
    Ark_EdgesLengthMetrics retValue = {
        .top = GetOptNumberFromCalcLength(margin.top),
        .topUnit = GetOptLengthUnitFromCalcLength(margin.top),
        .left = GetOptNumberFromCalcLength(margin.left),
        .leftUnit = GetOptLengthUnitFromCalcLength(margin.left),
        .bottom = GetOptNumberFromCalcLength(margin.bottom),
        .bottomUnit = GetOptLengthUnitFromCalcLength(margin.bottom),
        .right = GetOptNumberFromCalcLength(margin.right),
        .rightUnit = GetOptLengthUnitFromCalcLength(margin.right),
    };
    return retValue;
}

Ark_SizeLengthMetrics GetUserConfigSizeImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetUserConfigSizeImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto size = ViewAbstract::GetConfigSize(AceType::RawPtr(frameNode));
    if (!size.has_value()) {
        LOGW("This frameNode do not have config size, return default.");
        auto width = std::make_optional<CalcLength>();
        auto height = std::make_optional<CalcLength>();
        auto calcSize = std::make_optional<CalcSize>(width, height);
        Ark_SizeLengthMetrics retValue = { .width = GetOptNumberFromCalcLength(calcSize->Width()),
            .widthUnit = GetOptLengthUnitFromCalcLength(calcSize->Width()),
            .height = GetOptNumberFromCalcLength(calcSize->Height()),
            .heightUnit = GetOptLengthUnitFromCalcLength(calcSize->Height()) };
        return retValue;
    }
    Ark_SizeLengthMetrics retValue = {
        .width = GetOptNumberFromCalcLength(size->Width()),
        .widthUnit = GetOptLengthUnitFromCalcLength(size->Width()),
        .height = GetOptNumberFromCalcLength(size->Height()),
        .heightUnit = GetOptLengthUnitFromCalcLength(size->Height())
    };
    return retValue;
}
void SetMeasuredSizeImpl(Ark_FrameNode peer, const Ark_Size* size)
{
    CHECK_NULL_VOID(size);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto widthValue = Converter::Convert<int32_t>(size->width);
    auto heightValue = Converter::Convert<int32_t>(size->height);
    peerNode->GetGeometryNode()->SetFrameWidth(widthValue);
    peerNode->GetGeometryNode()->SetFrameHeight(heightValue);
}
void SetLayoutPositionImpl(Ark_FrameNode peer, const Ark_Position* position)
{
    CHECK_NULL_VOID(position);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto xValue = Converter::Convert<Dimension>(position->x.value);
    auto yValue = Converter::Convert<Dimension>(position->y.value);
    peerNode->GetGeometryNode()->SetMarginFrameOffsetX(xValue.Value());
    peerNode->GetGeometryNode()->SetMarginFrameOffsetY(yValue.Value());
}
void MeasureImpl(Ark_FrameNode peer, const Ark_LayoutConstraint* constraint)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    CHECK_NULL_VOID(constraint);
    Ark_Size maxSize = constraint->maxSize;
    Ark_Size minSize = constraint->minSize;
    Ark_Size percentReference = constraint->percentReference;
    auto minWidth = Converter::Convert<float>(constraint->minSize.width);
    auto minHeight = Converter::Convert<float>(constraint->minSize.height);
    auto maxWidth = Converter::Convert<float>(constraint->maxSize.width);
    auto maxHeight = Converter::Convert<float>(constraint->maxSize.height);
    auto percentReferenceWidth = Converter::Convert<float>(constraint->percentReference.width);
    auto percentReferenceHeight = Converter::Convert<float>(constraint->percentReference.height);
    std::optional<LayoutConstraintF> constraintF = std::make_optional<LayoutConstraintF>();
    // minWidth
    constraintF->minSize.SetWidth(minWidth);
    // minHeight
    constraintF->minSize.SetHeight(minHeight);
    // maxWidth
    constraintF->maxSize.SetWidth(maxWidth);
    // maxHeight
    constraintF->maxSize.SetHeight(maxHeight);
    // minWidth == maxWidth
    if (minWidth == maxWidth) {
        constraintF->selfIdealSize.SetWidth(minWidth);
    }
    // minHeight == maxHeight
    if (minHeight == maxHeight) {
        constraintF->selfIdealSize.SetHeight(minHeight);
    }
    // percentReferenceWidth
    constraintF->percentReference.SetWidth(percentReferenceWidth);
    // percentReferenceHeight
    constraintF->percentReference.SetHeight(percentReferenceHeight);
    peerNode->SetActive(true);
    peerNode->Measure(constraintF);
}
void LayoutImpl(Ark_FrameNode peer, const Ark_Position* position)
{
    CHECK_NULL_VOID(position);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto xValue = Converter::Convert<Dimension>(position->x.value);
    auto yValue = Converter::Convert<Dimension>(position->y.value);
    peerNode->SetActive(true);
    peerNode->GetGeometryNode()->SetMarginFrameOffsetX(xValue.Value());
    peerNode->GetGeometryNode()->SetMarginFrameOffsetY(yValue.Value());
    peerNode->Layout();
}
void SetNeedsLayoutImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    peerNode->MarkDirtyNode(ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_PARENT);
}
} // FrameNodeAccessor
const GENERATED_ArkUIFrameNodeAccessor* GetFrameNodeAccessor()
{
    static const GENERATED_ArkUIFrameNodeAccessor FrameNodeAccessorImpl {
        FrameNodeAccessor::DestroyPeerImpl, FrameNodeAccessor::CtorImpl,
        FrameNodeAccessor::GetFinalizerImpl, FrameNodeAccessor::IsModifiableImpl,
        FrameNodeAccessor::AppendChildImpl, FrameNodeAccessor::InsertChildAfterImpl,
        FrameNodeAccessor::RemoveChildImpl, FrameNodeAccessor::ClearChildrenImpl,
        FrameNodeAccessor::GetChildImpl, FrameNodeAccessor::GetFirstChildImpl,
        FrameNodeAccessor::GetNextSiblingImpl, FrameNodeAccessor::GetPreviousSiblingImpl,
        FrameNodeAccessor::GetParentImpl, FrameNodeAccessor::GetChildrenCountImpl,
        FrameNodeAccessor::DisposeImpl, FrameNodeAccessor::GetOpacityImpl,
        FrameNodeAccessor::SetMeasuredSizeImpl,
        FrameNodeAccessor::SetLayoutPositionImpl,
        FrameNodeAccessor::MeasureImpl,
        FrameNodeAccessor::LayoutImpl,
        FrameNodeAccessor::SetNeedsLayoutImpl,
        FrameNodeAccessor::GetPositionToWindowWithTransformImpl, FrameNodeAccessor::GetFrameNodeByKeyImpl,
        FrameNodeAccessor::GetIdByFrameNodeImpl, FrameNodeAccessor::MoveToImpl,
        FrameNodeAccessor::GetFirstChildIndexWithoutExpandImpl, FrameNodeAccessor::GetLastChildIndexWithoutExpandImpl,
        FrameNodeAccessor::GetAttachedFrameNodeByIdImpl, FrameNodeAccessor::GetFrameNodeByIdImpl,
        FrameNodeAccessor::GetFrameNodeByUniqueIdImpl, FrameNodeAccessor::GetCommonEventImpl,
        FrameNodeAccessor::ReuseImpl,
        FrameNodeAccessor::RecycleImpl,
        FrameNodeAccessor::GetFrameNodePtrImpl,
        FrameNodeAccessor::CreateTypedFrameNodeImpl,
    };
    return &FrameNodeAccessorImpl;
}

}
