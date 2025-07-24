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

#include "node_render_node_modifier.h"

#include "render_service_base/include/render/rs_mask.h"
#include "render_service_client/core/modifier_ng/rs_modifier_ng.h"
#include "render_service_client/core/ui/rs_canvas_node.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_modifier.h"
#include "core/pipeline/base/render_node.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/geometry/matrix4.h"
#include "frameworks/core/components_ng/render/adapter/rosen_modifier_property.h"

namespace OHOS::Ace::NG {
using OHOS::Rosen::RSNode;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
constexpr int NUM_9 = 9;
constexpr int NUM_10 = 10;
constexpr int NUM_11 = 11;
constexpr int NUM_12 = 12;
constexpr int NUM_13 = 13;
constexpr int NUM_14 = 14;
constexpr int NUM_15 = 15;
constexpr int32_t INDEX_2 = 2; // Arg Index
constexpr int32_t INDEX_3 = 3; // Arg Index

namespace {

struct RenderNodeStruct {
    std::shared_ptr<RSNode> rsNode;
    int32_t nodeId;
};

struct RenderModifierStruct {
    int32_t modifierId;
    RefPtr<NodeModifier::RenderContentModifier> modifier;
};

struct RenderPropertyStruct {
    int32_t propertyType;
    std::shared_ptr<RSProperty<float>> floatProperty;
    std::shared_ptr<RSProperty<Rosen::Vector2f>> vector2Property;
    std::shared_ptr<RSProperty<Rosen::RSColor>> colorProperty;
    std::shared_ptr<RSAnimatableProperty<float>> floatAnimatableProperty;
    std::shared_ptr<RSAnimatableProperty<Rosen::Vector2f>> vector2AnimatableProperty;
    std::shared_ptr<RSAnimatableProperty<Rosen::RSColor>> colorAnimatableProperty;
};

std::shared_ptr<RSNode> GetRsNodeFromStruct(ArkUIRenderNodeHandle node)
{
    auto* nodeStruct = reinterpret_cast<RenderNodeStruct*>(node);
    CHECK_NULL_RETURN(nodeStruct, nullptr);
    return nodeStruct->rsNode;
}

ArkUI_Int32 AddRenderNode(ArkUINodeHandle node, ArkUIRenderNodeHandle child)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    if (frameNode->TotalChildCount() > 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    CHECK_NULL_RETURN(frameNode->GetRenderContext(), ERROR_CODE_PARAM_INVALID);
    auto rsContext = AceType::DynamicCast<RosenRenderContext>(frameNode->GetRenderContext());
    CHECK_NULL_RETURN(rsContext, ERROR_CODE_PARAM_INVALID);
    auto rsNode = rsContext->GetRSNode();
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    if (rsNode->GetChildren().size() > 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto childNodePtr = GetRsNodeFromStruct(child);
    CHECK_NULL_RETURN(childNodePtr, ERROR_CODE_PARAM_INVALID);
    rsNode->AddChild(childNodePtr, -1);
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, ERROR_CODE_NO_ERROR);
    pipeline->RequestFrame();
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RemoveRenderNode(ArkUINodeHandle node, ArkUIRenderNodeHandle child)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(frameNode->GetRenderContext(), ERROR_CODE_PARAM_INVALID);
    auto rsContext = AceType::DynamicCast<RosenRenderContext>(frameNode->GetRenderContext());
    CHECK_NULL_RETURN(rsContext, ERROR_CODE_PARAM_INVALID);
    auto rsNode = rsContext->GetRSNode();
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto childNodePtr = GetRsNodeFromStruct(child);
    CHECK_NULL_RETURN(childNodePtr, ERROR_CODE_PARAM_INVALID);
    rsNode->RemoveChild(childNodePtr);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 ClearRenderNodeChildren(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(frameNode->GetRenderContext(), ERROR_CODE_PARAM_INVALID);
    auto rsContext = AceType::DynamicCast<RosenRenderContext>(frameNode->GetRenderContext());
    CHECK_NULL_RETURN(rsContext, ERROR_CODE_PARAM_INVALID);
    auto rsNode = rsContext->GetRSNode();
    rsNode->ClearChildren();
    return ERROR_CODE_NO_ERROR;
}

ArkUIRenderNodeHandle CreateNode(int32_t* nodeId)
{
    std::shared_ptr<RSNode> renderNode;
    auto pipelineContext = NG::PipelineContext::GetCurrentContextSafely();
    if (SystemProperties::GetMultiInstanceEnabled() && pipelineContext && pipelineContext->GetRSUIDirector()) {
        auto rsContext = pipelineContext->GetRSUIDirector()->GetRSUIContext();
        renderNode = Rosen::RSCanvasNode::Create(false, false, rsContext);
    } else {
        renderNode = Rosen::RSCanvasNode::Create();
    }
    CHECK_NULL_RETURN(renderNode, nullptr);
    RenderNodeStruct* nodeStruct = new RenderNodeStruct { .rsNode = renderNode, .nodeId = renderNode->GetId() };
    *nodeId = renderNode->GetId();
    return reinterpret_cast<ArkUIRenderNodeHandle>(nodeStruct);
}

ArkUI_Int32 GetId(ArkUIRenderNodeHandle node)
{
    auto nodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(nodePtr, 0);
    return nodePtr->GetId();
}

ArkUI_Int32 AddChild(ArkUIRenderNodeHandle node, ArkUIRenderNodeHandle child)
{
    auto parentNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(parentNodePtr, ERROR_CODE_PARAM_INVALID);
    auto childNodePtr = GetRsNodeFromStruct(child);
    CHECK_NULL_RETURN(childNodePtr, ERROR_CODE_PARAM_INVALID);
    parentNodePtr->AddChild(childNodePtr, -1);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetChildIndex(std::shared_ptr<RSNode> parent, std::shared_ptr<RSNode> child)
{
    CHECK_NULL_RETURN(parent, -1);
    CHECK_NULL_RETURN(child, -1);
    for (size_t i = 0; i < parent->GetChildren().size(); i++) {
        if (parent->GetChildByIndex(i) == child) {
            return i;
        }
    }
    return -1;
}

int32_t GetRSNodeChildCount(std::shared_ptr<RSNode> node)
{
    CHECK_NULL_RETURN(node, -1);
    return node->GetChildren().size();
}

ArkUI_Int32 InsertChildAfter(ArkUIRenderNodeHandle node, ArkUIRenderNodeHandle child, ArkUIRenderNodeHandle sibling)
{
    auto parentNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(parentNodePtr, ERROR_CODE_PARAM_INVALID);
    auto childNodePtr = GetRsNodeFromStruct(child);
    CHECK_NULL_RETURN(childNodePtr, ERROR_CODE_PARAM_INVALID);
    auto siblingPtr = GetRsNodeFromStruct(sibling);
    CHECK_NULL_RETURN(siblingPtr, ERROR_CODE_PARAM_INVALID);
    auto index = GetChildIndex(parentNodePtr, siblingPtr);
    if (index == -1) {
        parentNodePtr->AddChild(childNodePtr, -1);
    } else {
        parentNodePtr->AddChild(childNodePtr, index + 1);
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RemoveChild(ArkUIRenderNodeHandle node, ArkUIRenderNodeHandle child)
{
    auto parentNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(parentNodePtr, ERROR_CODE_PARAM_INVALID);
    auto childNodePtr = GetRsNodeFromStruct(child);
    CHECK_NULL_RETURN(childNodePtr, ERROR_CODE_PARAM_INVALID);
    parentNodePtr->RemoveChild(childNodePtr);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 ClearChildren(ArkUIRenderNodeHandle node)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    rsNodePtr->ClearChildren();
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 GetChild(ArkUIRenderNodeHandle node, int32_t index, ArkUIRenderNodeHandle* child, int32_t* childId)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    auto renderNode = rsNodePtr->GetChildByIndex(index);
    CHECK_NULL_RETURN(renderNode, ERROR_CODE_PARAM_INVALID);
    RenderNodeStruct* nodeStruct = new RenderNodeStruct { .rsNode = renderNode, .nodeId = renderNode->GetId() };
    *child = reinterpret_cast<ArkUIRenderNodeHandle>(nodeStruct);
    *childId = renderNode->GetId();
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 GetChildren(ArkUIRenderNodeHandle node, ArkUIRenderNodeHandle** child, uint32_t** childId, int32_t* count)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    auto childCount = GetRSNodeChildCount(rsNodePtr);
    int32_t index = 0;
    if (childCount <= 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    ArkUIRenderNodeHandle* childList = new ArkUIRenderNodeHandle[childCount];
    uint32_t* childIdList = new uint32_t[childCount];
    while (childCount > 0) {
        auto renderNode = rsNodePtr->GetChildByIndex(index);
        if (renderNode) {
            RenderNodeStruct* nodeStruct = new RenderNodeStruct { .rsNode = renderNode, .nodeId = renderNode->GetId() };
            childList[index] = reinterpret_cast<ArkUIRenderNodeHandle>(nodeStruct);
            childIdList[index] = renderNode->GetId();
        }
        index++;
        childCount--;
    }
    *count = index;
    *child = childList;
    *childId = childIdList;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 GetFirstChild(ArkUIRenderNodeHandle node, ArkUIRenderNodeHandle* child, int32_t* childId)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    auto count = GetRSNodeChildCount(rsNodePtr);
    if (count > 0) {
        auto renderNode = rsNodePtr->GetChildByIndex(0);
        CHECK_NULL_RETURN(renderNode, ERROR_CODE_PARAM_INVALID);
        RenderNodeStruct* nodeStruct = new RenderNodeStruct { .rsNode = renderNode, .nodeId = renderNode->GetId() };
        *child = reinterpret_cast<ArkUIRenderNodeHandle>(nodeStruct);
        *childId = renderNode->GetId();
        return ERROR_CODE_NO_ERROR;
    }
    return ERROR_CODE_PARAM_INVALID;
}

ArkUI_Int32 GetNextSibling(ArkUIRenderNodeHandle node, ArkUIRenderNodeHandle* slibing, int32_t* childId)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    auto parentNodePtr = rsNodePtr->GetParent();
    CHECK_NULL_RETURN(parentNodePtr, ERROR_CODE_PARAM_INVALID);
    int32_t childIndex = GetChildIndex(parentNodePtr, rsNodePtr);
    int32_t childCount = GetRSNodeChildCount(parentNodePtr);
    if (childIndex != -1 && childCount - 1 > childIndex) {
        auto slibingNode = parentNodePtr->GetChildByIndex(childIndex + 1);
        CHECK_NULL_RETURN(slibingNode, ERROR_CODE_PARAM_INVALID);
        RenderNodeStruct* nodeStruct = new RenderNodeStruct { .rsNode = slibingNode, .nodeId = slibingNode->GetId() };
        *slibing = reinterpret_cast<ArkUIRenderNodeHandle>(nodeStruct);
        *childId = slibingNode->GetId();
        return ERROR_CODE_NO_ERROR;
    }
    return ERROR_CODE_PARAM_INVALID;
}

ArkUI_Int32 GetPreviousSibling(ArkUIRenderNodeHandle node, ArkUIRenderNodeHandle* slibing, int32_t* childId)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    auto parentNodePtr = rsNodePtr->GetParent();
    CHECK_NULL_RETURN(parentNodePtr, ERROR_CODE_PARAM_INVALID);
    int32_t childIndex = GetChildIndex(parentNodePtr, rsNodePtr);
    if (childIndex > 0) {
        auto slibingNode = parentNodePtr->GetChildByIndex(childIndex - 1);
        CHECK_NULL_RETURN(slibingNode, ERROR_CODE_PARAM_INVALID);
        RenderNodeStruct* nodeStruct = new RenderNodeStruct { .rsNode = slibingNode, .nodeId = slibingNode->GetId() };
        *slibing = reinterpret_cast<ArkUIRenderNodeHandle>(nodeStruct);
        *childId = slibingNode->GetId();
        return ERROR_CODE_NO_ERROR;
    }
    return ERROR_CODE_PARAM_INVALID;
}

ArkUI_Int32 GetChildrenCount(ArkUIRenderNodeHandle node, int32_t* count)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    *count = GetRSNodeChildCount(rsNodePtr);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetBackgroundColor(ArkUIRenderNodeHandle handle, uint32_t backgroundColor)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetBackgroundColor(backgroundColor);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetBackgroundColor(ArkUIRenderNodeHandle handle, uint32_t* color)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    *color = rsNode->GetStagingProperties().GetBackgroundColor().AsArgbInt();
    return ERROR_CODE_NO_ERROR;
}

int32_t SetOpacity(ArkUIRenderNodeHandle handle, float opacity)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetAlpha(opacity);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetOpacity(ArkUIRenderNodeHandle handle, float* opacity)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    *opacity = rsNode->GetStagingProperties().GetAlpha();
    return ERROR_CODE_NO_ERROR;
}

int32_t SetSize(ArkUIRenderNodeHandle handle, int32_t width, int32_t height)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetBoundsWidth(width);
    rsNode->SetBoundsHeight(height);
    rsNode->SetFrame(0, 0, width, height);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetSize(ArkUIRenderNodeHandle handle, int32_t* width, int32_t* height)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto vector4f = rsNode->GetStagingProperties().GetBounds();
    *width = vector4f.z_;
    *height = vector4f.w_;
    return ERROR_CODE_NO_ERROR;
}

int32_t SetPosition(ArkUIRenderNodeHandle handle, int32_t x, int32_t y)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    OHOS::Rosen::Vector4f vector4f;
    vector4f.x_ = x;
    vector4f.y_ = y;
    rsNode->SetBounds(vector4f);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetPosition(ArkUIRenderNodeHandle handle, int32_t* x, int32_t* y)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto vector4f = rsNode->GetStagingProperties().GetBounds();
    *x = vector4f.x_;
    *y = vector4f.y_;
    return ERROR_CODE_NO_ERROR;
}

int32_t SetPivot(ArkUIRenderNodeHandle handle, float x, float y)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetPivot(x, y);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetPivot(ArkUIRenderNodeHandle handle, float* x, float* y)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto vector2f = rsNode->GetStagingProperties().GetPivot();
    *x = vector2f.x_;
    *y = vector2f.y_;
    return ERROR_CODE_NO_ERROR;
}

int32_t SetScale(ArkUIRenderNodeHandle handle, float x, float y)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetScale(x, y);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetScale(ArkUIRenderNodeHandle handle, float* x, float* y)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto vector2f = rsNode->GetStagingProperties().GetScale();
    *x = vector2f.x_;
    *y = vector2f.y_;
    return ERROR_CODE_NO_ERROR;
}

int32_t SetTranslation(ArkUIRenderNodeHandle handle, float x, float y)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    OHOS::Rosen::Vector2f translate = { x, y };
    rsNode->SetTranslate(translate);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetTranslation(ArkUIRenderNodeHandle handle, float* x, float* y)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto vector2f = rsNode->GetStagingProperties().GetTranslate();
    *x = vector2f.x_;
    *y = vector2f.y_;
    return ERROR_CODE_NO_ERROR;
}

int32_t SetRotation(ArkUIRenderNodeHandle handle, float x, float y, float z)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetRotation(x, y, z);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetRotation(ArkUIRenderNodeHandle handle, float* x, float* y, float* z)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    *z = rsNode->GetStagingProperties().GetRotation();
    *x = rsNode->GetStagingProperties().GetRotationX();
    *y = rsNode->GetStagingProperties().GetRotationY();
    return ERROR_CODE_NO_ERROR;
}

#ifndef MODIFIER_NG
template<typename T>
bool CreateOrSetModifierValue(std::shared_ptr<Rosen::RSAnimatableProperty<T>>& property, const T& value)
{
    if (property == nullptr) {
        property = std::make_shared<Rosen::RSAnimatableProperty<T>>(value);
        return true;
    }
    property->Set(value);
    return false;
}

void AddOrChangePerspectiveModifier(std::shared_ptr<RSNode>& rsNode, std::shared_ptr<Rosen::RSPerspModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector4f>>& property, const Rosen::Vector4f& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSPerspModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeTranslateModifier(std::shared_ptr<RSNode>& rsNode,
    std::shared_ptr<Rosen::RSTranslateModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>>& property, const Rosen::Vector2f& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSTranslateModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeScaleModifier(std::shared_ptr<RSNode>& rsNode, std::shared_ptr<Rosen::RSScaleModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>>& property, const Rosen::Vector2f& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSScaleModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeQuaternionModifier(std::shared_ptr<RSNode>& rsNode,
    std::shared_ptr<Rosen::RSQuaternionModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Quaternion>>& property, const Rosen::Quaternion& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSQuaternionModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeSkewModifier(std::shared_ptr<RSNode>& rsNode, std::shared_ptr<Rosen::RSSkewModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector3f>>& property, const Rosen::Vector3f& value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSSkewModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeScaleZModifier(std::shared_ptr<RSNode>& rsNode, std::shared_ptr<Rosen::RSScaleZModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSScaleZModifier>(property);
        rsNode->AddModifier(modifier);
    }
}

void AddOrChangeTranslateZModifier(std::shared_ptr<RSNode>& rsNode,
    std::shared_ptr<Rosen::RSTranslateZModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float value)
{
    bool isCreate = CreateOrSetModifierValue(property, value);
    if (isCreate) {
        CHECK_NULL_VOID(rsNode);
        modifier = std::make_shared<Rosen::RSTranslateZModifier>(property);
        rsNode->AddModifier(modifier);
    }
}
#else
template<typename ModifierName, auto Setter, typename T>
void AddOrUpdateModifier(std::shared_ptr<RSNode>& rsNode, const T& value)
{
    auto modifier = std::make_shared<ModifierName>();
    (*modifier.*Setter)(value);
    rsNode->AddModifier(modifier);
}
#endif

int32_t SetTransform(ArkUIRenderNodeHandle handle, float* matrix)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);

    auto matrix4 = Matrix4(matrix[NUM_0], matrix[NUM_4], matrix[NUM_8], matrix[NUM_12], matrix[NUM_1], matrix[NUM_5],
        matrix[NUM_9], matrix[NUM_13], matrix[NUM_2], matrix[NUM_6], matrix[NUM_10], matrix[NUM_14], matrix[NUM_3],
        matrix[NUM_7], matrix[NUM_11], matrix[NUM_15]);

    DecomposedTransform transform;
    if (!TransformUtil::DecomposeTransform(transform, matrix4)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    std::shared_ptr<RSNode> rsNodeShared(rsNode);
    Rosen::Vector4f perspectiveValue { transform.perspective[0], transform.perspective[1],
        transform.perspective[INDEX_2], transform.perspective[INDEX_3] };
    Rosen::Vector2f xyTranslateValue { transform.translate[0], transform.translate[1] };
    Rosen::Quaternion quaternion { static_cast<float>(transform.quaternion.GetX()),
        static_cast<float>(transform.quaternion.GetY()), static_cast<float>(transform.quaternion.GetZ()),
        static_cast<float>(transform.quaternion.GetW()) };
    Rosen::Vector2f xyScaleValue { transform.scale[0], transform.scale[1] };
    Rosen::Vector3f skewValue { transform.skew[0], transform.skew[1], transform.skew[INDEX_2] };
#if defined(MODIFIER_NG)
    AddOrUpdateModifier<Rosen::ModifierNG::RSTransformModifier, &Rosen::ModifierNG::RSTransformModifier::SetPersp,
        Rosen::Vector4f>(rsNodeShared, perspectiveValue);
    AddOrUpdateModifier<Rosen::ModifierNG::RSTransformModifier, &Rosen::ModifierNG::RSTransformModifier::SetTranslate,
        Rosen::Vector2f>(rsNodeShared, xyTranslateValue);
    AddOrUpdateModifier<Rosen::ModifierNG::RSTransformModifier, &Rosen::ModifierNG::RSTransformModifier::SetTranslateZ,
        float>(rsNodeShared, transform.translate[INDEX_2]);
    AddOrUpdateModifier<Rosen::ModifierNG::RSTransformModifier, &Rosen::ModifierNG::RSTransformModifier::SetScale,
        Rosen::Vector2f>(rsNodeShared, xyScaleValue);
    AddOrUpdateModifier<Rosen::ModifierNG::RSTransformModifier, &Rosen::ModifierNG::RSTransformModifier::SetScaleZ,
        float>(rsNodeShared, transform.scale[INDEX_2]);
    AddOrUpdateModifier<Rosen::ModifierNG::RSTransformModifier, &Rosen::ModifierNG::RSTransformModifier::SetSkew,
        Rosen::Vector3f>(rsNodeShared, skewValue);
    AddOrUpdateModifier<Rosen::ModifierNG::RSTransformModifier, &Rosen::ModifierNG::RSTransformModifier::SetQuaternion,
        Rosen::Quaternion>(rsNodeShared, quaternion);
#else
    std::shared_ptr<Rosen::RSPerspModifier> perspectivePtr;
    std::shared_ptr<Rosen::RSTranslateModifier> translateXYPtr;
    std::shared_ptr<Rosen::RSTranslateZModifier> translateZPtr;
    std::shared_ptr<Rosen::RSScaleModifier> scaleXYPtr;
    std::shared_ptr<Rosen::RSScaleZModifier> scaleZPtr;
    std::shared_ptr<Rosen::RSSkewModifier> skewPtr;
    std::shared_ptr<Rosen::RSQuaternionModifier> quaternionPtr;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector4f>> perspectiveValuePtr;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>> translateXYValuePtr;
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> translateZValuePtr;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>> scaleXYValuePtr;
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> scaleZValuePtr;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector3f>> skewValuePtr;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Quaternion>> quaternionValuePtr;

    AddOrChangePerspectiveModifier(rsNodeShared, perspectivePtr, perspectiveValuePtr, perspectiveValue);
    AddOrChangeTranslateModifier(rsNodeShared, translateXYPtr, translateXYValuePtr, xyTranslateValue);
    AddOrChangeTranslateZModifier(rsNodeShared, translateZPtr, translateZValuePtr, transform.translate[INDEX_2]);
    AddOrChangeScaleModifier(rsNodeShared, scaleXYPtr, scaleXYValuePtr, xyScaleValue);
    AddOrChangeScaleZModifier(rsNodeShared, scaleZPtr, scaleZValuePtr, transform.scale[INDEX_2]);
    AddOrChangeSkewModifier(rsNodeShared, skewPtr, skewValuePtr, skewValue);
    AddOrChangeQuaternionModifier(rsNodeShared, quaternionPtr, quaternionValuePtr, quaternion);
#endif
    return ERROR_CODE_NO_ERROR;
}

int32_t SetShadowColor(ArkUIRenderNodeHandle handle, uint32_t color)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetShadowColor(color);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetShadowColor(ArkUIRenderNodeHandle handle, uint32_t* color)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    *color = rsNode->GetStagingProperties().GetShadowColor().AsArgbInt();
    return ERROR_CODE_NO_ERROR;
}

int32_t SetShadowOffset(ArkUIRenderNodeHandle handle, int32_t x, int32_t y)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetShadowOffset(static_cast<float>(x), static_cast<float>(y));
    return ERROR_CODE_NO_ERROR;
}

int32_t GetShadowOffset(ArkUIRenderNodeHandle handle, int32_t* x, int32_t* y)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    *x = rsNode->GetStagingProperties().GetShadowOffsetX();
    *y = rsNode->GetStagingProperties().GetShadowOffsetY();
    return ERROR_CODE_NO_ERROR;
}

int32_t SetShadowAlpha(ArkUIRenderNodeHandle handle, float alpha)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetShadowAlpha(alpha);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetShadowAlpha(ArkUIRenderNodeHandle handle, float* alpha)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    *alpha = rsNode->GetStagingProperties().GetShadowAlpha();
    return ERROR_CODE_NO_ERROR;
}

int32_t SetShadowElevation(ArkUIRenderNodeHandle handle, float elevation)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetShadowElevation(elevation);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetShadowElevation(ArkUIRenderNodeHandle handle, float* elevation)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    *elevation = rsNode->GetStagingProperties().GetShadowElevation();
    return ERROR_CODE_NO_ERROR;
}

int32_t SetShadowRadius(ArkUIRenderNodeHandle handle, float radius)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetShadowRadius(radius);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetShadowRadius(ArkUIRenderNodeHandle handle, float* radius)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    *radius = rsNode->GetStagingProperties().GetShadowRadius();
    return ERROR_CODE_NO_ERROR;
}

int32_t SetBorderStyle(ArkUIRenderNodeHandle handle, uint32_t left, uint32_t top, uint32_t right, uint32_t bottom)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetBorderStyle(left, top, right, bottom);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetBorderStyle(ArkUIRenderNodeHandle handle, uint32_t* left, uint32_t* top, uint32_t* right, uint32_t* bottom)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto vector4 = rsNode->GetStagingProperties().GetBorderStyle();
    *left = vector4.x_;
    *top = vector4.y_;
    *right = vector4.z_;
    *bottom = vector4.w_;
    return ERROR_CODE_NO_ERROR;
}

int32_t SetBorderWidth(ArkUIRenderNodeHandle handle, float left, float top, float right, float bottom)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetBorderWidth(left, top, right, bottom);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetBorderWidth(ArkUIRenderNodeHandle handle, float* left, float* top, float* right, float* bottom)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto vector4 = rsNode->GetStagingProperties().GetBorderWidth();
    *left = vector4.x_;
    *top = vector4.y_;
    *right = vector4.z_;
    *bottom = vector4.w_;
    return ERROR_CODE_NO_ERROR;
}

int32_t SetBorderColor(ArkUIRenderNodeHandle handle, uint32_t left, uint32_t top, uint32_t right, uint32_t bottom)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetBorderColor(left, top, right, bottom);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetBorderColor(ArkUIRenderNodeHandle handle, uint32_t* left, uint32_t* top, uint32_t* right, uint32_t* bottom)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto vector4 = rsNode->GetStagingProperties().GetBorderColor();
    *left = vector4.x_.AsArgbInt();
    *top = vector4.y_.AsArgbInt();
    *right = vector4.z_.AsArgbInt();
    *bottom = vector4.w_.AsArgbInt();
    return ERROR_CODE_NO_ERROR;
}

int32_t SetBorderRadius(ArkUIRenderNodeHandle handle, float left, float top, float right, float bottom)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    OHOS::Rosen::Vector4f vector4f;
    vector4f.x_ = left;
    vector4f.y_ = top;
    vector4f.z_ = right;
    vector4f.w_ = bottom;
    rsNode->SetCornerRadius(vector4f);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetBorderRadius(ArkUIRenderNodeHandle handle, float* left, float* top, float* right, float* bottom)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto vector4 = rsNode->GetStagingProperties().GetCornerRadius();
    *left = vector4.x_;
    *top = vector4.y_;
    *right = vector4.z_;
    *bottom = vector4.w_;
    return ERROR_CODE_NO_ERROR;
}

int32_t SetMarkNodeGroup(ArkUIRenderNodeHandle handle, int32_t markNodeGroup)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->MarkNodeGroup(markNodeGroup);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetBounds(ArkUIRenderNodeHandle handle, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetBounds(x, y, width, height);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetBounds(ArkUIRenderNodeHandle handle, uint32_t* x, uint32_t* y, uint32_t* width, uint32_t* height)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    auto vector4 = rsNode->GetStagingProperties().GetBounds();
    *x = vector4.x_;
    *y = vector4.y_;
    *width = vector4.z_;
    *height = vector4.w_;
    return ERROR_CODE_NO_ERROR;
}

int32_t SetDrawRegion(ArkUIRenderNodeHandle handle, float x, float y, float w, float h)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    std::shared_ptr<OHOS::Rosen::RectF> rect = std::make_shared<OHOS::Rosen::RectF>();
    rect->SetAll(x, y, w, h);
    rsNode->SetDrawRegion(rect);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetClipToFrame(ArkUIRenderNodeHandle handle, int32_t* clipToFrame)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    *clipToFrame = static_cast<int32_t>(rsNode->GetStagingProperties().GetClipToFrame());
    return ERROR_CODE_NO_ERROR;
}

int32_t SetClipToFrame(ArkUIRenderNodeHandle handle, int32_t clipToFrame)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetClipToFrame(static_cast<bool>(clipToFrame));
    return ERROR_CODE_NO_ERROR;
}

int32_t GetClipToBounds(ArkUIRenderNodeHandle handle, int32_t* clipToBounds)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    *clipToBounds = static_cast<int32_t>(rsNode->GetStagingProperties().GetClipToBounds());
    return ERROR_CODE_NO_ERROR;
}

int32_t SetClipToBounds(ArkUIRenderNodeHandle handle, int32_t clipToBounds)
{
    auto rsNode = GetRsNodeFromStruct(handle);
    CHECK_NULL_RETURN(rsNode, ERROR_CODE_PARAM_INVALID);
    rsNode->SetClipToBounds(static_cast<bool>(clipToBounds));
    return ERROR_CODE_NO_ERROR;
}

int32_t AttachModifier(ArkUIRenderNodeHandle node, ArkUIRenderModifierHandle modifier)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    auto* modifierStruct = reinterpret_cast<RenderModifierStruct*>(modifier);
    CHECK_NULL_RETURN(modifierStruct, ERROR_CODE_PARAM_INVALID);
    auto modifierAdapter = ConvertContentModifier(modifierStruct->modifier);
    rsNodePtr->AddModifier(modifierAdapter);
    return ERROR_CODE_NO_ERROR;
}

ArkUIRenderModifierHandle CreateModifier()
{
    auto contentModifier = AceType::MakeRefPtr<NodeModifier::RenderContentModifier>([](DrawingContext&) {});
    CHECK_NULL_RETURN(contentModifier, nullptr);
    auto modifierAdapter = std::static_pointer_cast<ContentModifierAdapter>(ConvertContentModifier(contentModifier));
    CHECK_NULL_RETURN(modifierAdapter, nullptr);
    RenderModifierStruct* modifierStruct =
        new RenderModifierStruct { .modifier = contentModifier, .modifierId = modifierAdapter->GetId() };
    return reinterpret_cast<ArkUIRenderModifierHandle>(modifierStruct);
}

int32_t AttachProperty(ArkUIRenderModifierHandle modifier, ArkUIPropertyHandle property)
{
    auto modifierStruct = reinterpret_cast<RenderModifierStruct*>(modifier);
    CHECK_NULL_RETURN(modifier, ERROR_CODE_PARAM_INVALID);
    auto modifierPtr = ConvertContentModifier(modifierStruct->modifier);
    CHECK_NULL_RETURN(modifierPtr, ERROR_CODE_PARAM_INVALID);
    auto propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(property, ERROR_CODE_PARAM_INVALID);
    switch (propertyStruct->propertyType) {
        case ArkUIPropertyType::PROPERTY_FLOAT:
            modifierPtr->AttachProperty(propertyStruct->floatProperty);
            break;
        case ArkUIPropertyType::PROPERTY_VECTOR2:
            modifierPtr->AttachProperty(propertyStruct->vector2Property);
            break;
        case ArkUIPropertyType::PROPERTY_COLOR:
            modifierPtr->AttachProperty(propertyStruct->colorProperty);
            break;
        case ArkUIPropertyType::ANIMATABLE_PROPERTY_FLOAT:
            modifierPtr->AttachProperty(propertyStruct->floatAnimatableProperty);
            break;
        case ArkUIPropertyType::ANIMATABLE_PROPERTY_VECTOR2:
            modifierPtr->AttachProperty(propertyStruct->vector2AnimatableProperty);
            break;
        case ArkUIPropertyType::ANIMATABLE_PROPERTY_COLOR:
            modifierPtr->AttachProperty(propertyStruct->colorAnimatableProperty);
            break;
        default:
            return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetModifierOnDraw(ArkUIRenderModifierHandle modifier, void* userData,
    void (*customRenderDrawFunc)(ArkUIDrawingContext* context, void* userData))
{
    auto modifierStruct = reinterpret_cast<RenderModifierStruct*>(modifier);
    CHECK_NULL_RETURN(modifierStruct, ERROR_CODE_PARAM_INVALID);
    auto renderContentModifier = modifierStruct->modifier;
    CHECK_NULL_RETURN(renderContentModifier, ERROR_CODE_PARAM_INVALID);
    auto onContentDraw = [userData, customRenderDrawFunc](DrawingContext context) {
        ArkUIDrawingContext drawContext;
        drawContext.canvas = reinterpret_cast<ArkUICanvasHandle>(&context.canvas);
        drawContext.width = context.width;
        drawContext.height = context.height;
        customRenderDrawFunc(&drawContext, userData);
    };
    renderContentModifier->setDrawFunction(std::move(onContentDraw));
    return ERROR_CODE_NO_ERROR;
}

void DisposeModifier(ArkUIRenderModifierHandle modifier)
{
    auto* modifierStruct = reinterpret_cast<RenderModifierStruct*>(modifier);
    CHECK_NULL_VOID(modifierStruct);
    delete modifierStruct;
}

ArkUIPropertyHandle CreateFloatProperty(ArkUI_Float32 value)
{
    auto property = std::make_shared<RSProperty<float>>(value);
    RenderPropertyStruct* propertyStruct =
        new RenderPropertyStruct { .floatProperty = property, .propertyType = ArkUIPropertyType::PROPERTY_FLOAT };
    return reinterpret_cast<ArkUIPropertyHandle>(propertyStruct);
}

int32_t SetFloatProperty(ArkUIPropertyHandle property, float value)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::PROPERTY_FLOAT) {
        return ERROR_CODE_PARAM_INVALID;
    }
    propertyStruct->floatProperty->Set(value);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetFloatProperty(ArkUIPropertyHandle property, float* value)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::PROPERTY_FLOAT) {
        return ERROR_CODE_PARAM_INVALID;
    }
    *value = propertyStruct->floatProperty->Get();
    return ERROR_CODE_NO_ERROR;
}

ArkUIPropertyHandle CreateVector2Property(float x, float y)
{
    auto property = std::make_shared<RSProperty<Rosen::Vector2f>>(Rosen::Vector2f(x, y));
    RenderPropertyStruct* propertyStruct =
        new RenderPropertyStruct { .vector2Property = property, .propertyType = ArkUIPropertyType::PROPERTY_VECTOR2 };
    return reinterpret_cast<ArkUIPropertyHandle>(propertyStruct);
}

ArkUI_Int32 SetVector2Property(ArkUIPropertyHandle property, float x, float y)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::PROPERTY_VECTOR2) {
        return ERROR_CODE_PARAM_INVALID;
    }
    propertyStruct->vector2Property->Set(Rosen::Vector2f(x, y));
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 GetVector2Property(ArkUIPropertyHandle property, float* x, float* y)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::PROPERTY_VECTOR2) {
        return ERROR_CODE_PARAM_INVALID;
    }
    Rosen::Vector2f value = propertyStruct->vector2Property->Get();
    *x = value.x_;
    *y = value.y_;
    return ERROR_CODE_NO_ERROR;
}

ArkUIPropertyHandle CreateColorProperty(uint32_t color)
{
    auto property = std::make_shared<RSProperty<Rosen::RSColor>>(Rosen::RSColor(color));
    RenderPropertyStruct* propertyStruct =
        new RenderPropertyStruct { .colorProperty = property, .propertyType = ArkUIPropertyType::PROPERTY_COLOR };
    return reinterpret_cast<ArkUIPropertyHandle>(propertyStruct);
}

ArkUI_Int32 SetColorProperty(ArkUIPropertyHandle property, uint32_t color)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::PROPERTY_COLOR) {
        return ERROR_CODE_PARAM_INVALID;
    }
    propertyStruct->colorProperty->Set(Rosen::RSColor(color));
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 GetColorProperty(ArkUIPropertyHandle property, uint32_t* color)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::PROPERTY_COLOR) {
        return ERROR_CODE_PARAM_INVALID;
    }
    *color = propertyStruct->colorProperty->Get().AsArgbInt();
    return ERROR_CODE_NO_ERROR;
}

ArkUIPropertyHandle CreateFloatAnimatableProperty(ArkUI_Float32 value)
{
    auto property = std::make_shared<RSAnimatableProperty<float>>(value);
    RenderPropertyStruct* propertyStruct = new RenderPropertyStruct { .floatAnimatableProperty = property,
        .propertyType = ArkUIPropertyType::ANIMATABLE_PROPERTY_FLOAT };
    return reinterpret_cast<ArkUIPropertyHandle>(propertyStruct);
}

int32_t SetFloatAnimatableProperty(ArkUIPropertyHandle property, float value)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::ANIMATABLE_PROPERTY_FLOAT) {
        return ERROR_CODE_PARAM_INVALID;
    }
    propertyStruct->floatAnimatableProperty->Set(value);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetFloatAnimatableProperty(ArkUIPropertyHandle property, float* value)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::ANIMATABLE_PROPERTY_FLOAT) {
        return ERROR_CODE_PARAM_INVALID;
    }
    *value = propertyStruct->floatAnimatableProperty->Get();
    return ERROR_CODE_NO_ERROR;
}

ArkUIPropertyHandle CreateVector2AnimatableProperty(float x, float y)
{
    auto property = std::make_shared<RSAnimatableProperty<Rosen::Vector2f>>(Rosen::Vector2f(x, y));
    RenderPropertyStruct* propertyStruct = new RenderPropertyStruct { .vector2AnimatableProperty = property,
        .propertyType = ArkUIPropertyType::ANIMATABLE_PROPERTY_VECTOR2 };
    return reinterpret_cast<ArkUIPropertyHandle>(propertyStruct);
}

ArkUI_Int32 SetVector2AnimatableProperty(ArkUIPropertyHandle property, float x, float y)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::ANIMATABLE_PROPERTY_VECTOR2) {
        return ERROR_CODE_PARAM_INVALID;
    }
    propertyStruct->vector2AnimatableProperty->Set(Rosen::Vector2f(x, y));
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 GetVector2AnimatableProperty(ArkUIPropertyHandle property, float* x, float* y)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::ANIMATABLE_PROPERTY_VECTOR2) {
        return ERROR_CODE_PARAM_INVALID;
    }
    Rosen::Vector2f value = propertyStruct->vector2AnimatableProperty->Get();
    *x = value.x_;
    *y = value.y_;
    return ERROR_CODE_NO_ERROR;
}

ArkUIPropertyHandle CreateColorAnimatableProperty(uint32_t color)
{
    auto property = std::make_shared<RSAnimatableProperty<Rosen::RSColor>>(Rosen::RSColor(color));
    RenderPropertyStruct* propertyStruct = new RenderPropertyStruct { .colorAnimatableProperty = property,
        .propertyType = ArkUIPropertyType::ANIMATABLE_PROPERTY_COLOR };
    return reinterpret_cast<ArkUIPropertyHandle>(propertyStruct);
}

ArkUI_Int32 SetColorAnimatableProperty(ArkUIPropertyHandle property, uint32_t color)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::ANIMATABLE_PROPERTY_COLOR) {
        return ERROR_CODE_PARAM_INVALID;
    }
    propertyStruct->colorAnimatableProperty->Set(Rosen::RSColor(color));
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 GetColorAnimatableProperty(ArkUIPropertyHandle property, uint32_t* color)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_RETURN(propertyStruct, ERROR_CODE_PARAM_INVALID);
    if (propertyStruct->propertyType != ArkUIPropertyType::ANIMATABLE_PROPERTY_COLOR) {
        return ERROR_CODE_PARAM_INVALID;
    }
    *color = propertyStruct->colorAnimatableProperty->Get().AsArgbInt();
    return ERROR_CODE_NO_ERROR;
}

void DisposeProperty(ArkUIPropertyHandle property)
{
    auto* propertyStruct = reinterpret_cast<RenderPropertyStruct*>(property);
    CHECK_NULL_VOID(propertyStruct);
    delete propertyStruct;
}

RSPen GetRsPen(uint32_t strokeColor, float strokeWidth)
{
    RSColor rsStrokeColor;
    rsStrokeColor.SetColorQuad(strokeColor);

    RSPen pen;
    pen.SetColor(rsStrokeColor);
    pen.SetWidth(strokeWidth);

    return pen;
}

RSBrush GetRsBrush(uint32_t fillColor)
{
    RSColor color;
    color.SetColorQuad(fillColor);
    RSBrush brush(color);

    return brush;
}

ArkUI_Int32 SetRectMask(ArkUIRenderNodeHandle node, ArkUIRectShape shape, ArkUIMaskFill fill)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    RSPath path;
    path.AddRect(shape.left, shape.top, shape.right, shape.bottom);

    RSBrush brush = GetRsBrush(fill.fillColor);
    RSPen pen = GetRsPen(fill.strokeColor, fill.strokeWidth);

    std::shared_ptr<Rosen::RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    rsNodePtr->SetMask(mask);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetCircleMask(ArkUIRenderNodeHandle node, ArkUICircleShape shape, ArkUIMaskFill fill)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    RSPath path;
    path.AddCircle(shape.centerX, shape.centerY, shape.radius);

    RSBrush brush = GetRsBrush(fill.fillColor);
    RSPen pen = GetRsPen(fill.strokeColor, fill.strokeWidth);

    std::shared_ptr<Rosen::RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    rsNodePtr->SetMask(mask);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetRoundRectMask(ArkUIRenderNodeHandle node, ArkUIRoundRectShape shape, ArkUIMaskFill fill)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    RSRoundRect rsRoundRect;

    RSRect rsRect(shape.left, shape.top, shape.right, shape.bottom);
    rsRoundRect.SetRect(rsRect);

    rsRoundRect.SetCornerRadius(RSRoundRect::TOP_LEFT_POS, shape.topLeftX, shape.topLeftY);
    rsRoundRect.SetCornerRadius(RSRoundRect::TOP_RIGHT_POS, shape.topRightX, shape.topRightY);
    rsRoundRect.SetCornerRadius(RSRoundRect::BOTTOM_LEFT_POS, shape.bottomLeftX, shape.bottomLeftY);
    rsRoundRect.SetCornerRadius(RSRoundRect::BOTTOM_RIGHT_POS, shape.bottomRightX, shape.bottomRightY);

    RSPath path;
    path.AddRoundRect(rsRoundRect);

    RSBrush brush = GetRsBrush(fill.fillColor);
    RSPen pen = GetRsPen(fill.strokeColor, fill.strokeWidth);

    std::shared_ptr<Rosen::RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    rsNodePtr->SetMask(mask);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetOvalMask(ArkUIRenderNodeHandle node, ArkUIRectShape shape, ArkUIMaskFill fill)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    RSRect rsRect(shape.left, shape.top, shape.right, shape.bottom);
    RSPath path;
    path.AddOval(rsRect);

    RSBrush brush = GetRsBrush(fill.fillColor);
    RSPen pen = GetRsPen(fill.strokeColor, fill.strokeWidth);

    std::shared_ptr<Rosen::RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    rsNodePtr->SetMask(mask);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetCommandPathMask(ArkUIRenderNodeHandle node, ArkUI_CharPtr commands, ArkUIMaskFill fill)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    RSPath path;
    path.BuildFromSVGString(commands);

    RSBrush brush = GetRsBrush(fill.fillColor);
    RSPen pen = GetRsPen(fill.strokeColor, fill.strokeWidth);

    std::shared_ptr<Rosen::RSMask> mask = Rosen::RSMask::CreatePathMask(path, pen, brush);
    rsNodePtr->SetMask(mask);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetRectClip(ArkUIRenderNodeHandle node, ArkUIRectShape shape)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    RectF rectF(shape.left, shape.top, shape.right, shape.bottom);
    RSRecordingPath rsPath;
    rsPath.AddRect({ rectF.GetX(), rectF.GetY(), rectF.GetX() + rectF.Width(), rectF.GetY() + rectF.Height() });
    rsNodePtr->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetCircleClip(ArkUIRenderNodeHandle node, ArkUICircleShape shape)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetRoundRectClip(ArkUIRenderNodeHandle node, ArkUIRoundRectShape shape)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    RSRoundRect rsRoundRect;

    RSRect rsRect(shape.left, shape.top, shape.right, shape.bottom);
    rsRoundRect.SetRect(rsRect);

    rsRoundRect.SetCornerRadius(RSRoundRect::TOP_LEFT_POS, shape.topLeftX, shape.topLeftY);
    rsRoundRect.SetCornerRadius(RSRoundRect::TOP_RIGHT_POS, shape.topRightX, shape.topRightY);
    rsRoundRect.SetCornerRadius(RSRoundRect::BOTTOM_LEFT_POS, shape.bottomLeftX, shape.bottomLeftY);
    rsRoundRect.SetCornerRadius(RSRoundRect::BOTTOM_RIGHT_POS, shape.bottomRightX, shape.bottomRightY);

    RSRecordingPath rsPath;
    rsPath.AddRoundRect(rsRoundRect);
    rsNodePtr->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetOvalClip(ArkUIRenderNodeHandle node, ArkUIRectShape shape)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    RectF rectF(shape.left, shape.top, shape.right, shape.bottom);
    RSRecordingPath rsPath;
    rsPath.AddOval({ rectF.GetX(), rectF.GetY(), rectF.GetX() + rectF.Width(), rectF.GetY() + rectF.Height() });
    rsNodePtr->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetCommandPathClip(ArkUIRenderNodeHandle node, ArkUI_CharPtr commands)
{
    auto rsNodePtr = GetRsNodeFromStruct(node);
    CHECK_NULL_RETURN(rsNodePtr, ERROR_CODE_PARAM_INVALID);
    RSRecordingPath rsPath;
    rsPath.BuildFromSVGString(commands);
    rsNodePtr->SetClipBounds(Rosen::RSPath::CreateRSPath(rsPath));
    return ERROR_CODE_NO_ERROR;
}

} // namespace
namespace NodeModifier {
const ArkUINDKRenderNodeModifier* GetNDKRenderNodeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUINDKRenderNodeModifier modifier = {
        .addRenderNode = AddRenderNode,
        .removeRenderNode = RemoveRenderNode,
        .clearRenderNodeChildren = ClearRenderNodeChildren,
        .createNode = CreateNode,
        .addChild = AddChild,
        .getId = GetId,
        .insertChildAfter = InsertChildAfter,
        .removeChild = RemoveChild,
        .clearChildren = ClearChildren,
        .getChild = GetChild,
        .getChildren = GetChildren,
        .getFirstChild = GetFirstChild,
        .getNextSibling = GetNextSibling,
        .getPreviousSibling = GetPreviousSibling,
        .getChildrenCount = GetChildrenCount,
        .setBackgroundColor = SetBackgroundColor,
        .setOpacity = SetOpacity,
        .setPivot = SetPivot,
        .setScale = SetScale,
        .setRotation = SetRotation,
        .setShadowColor = SetShadowColor,
        .setShadowOffset = SetShadowOffset,
        .setShadowAlpha = SetShadowAlpha,
        .setShadowElevation = SetShadowElevation,
        .getBackgroundColor = GetBackgroundColor,
        .getOpacity = GetOpacity,
        .getPivot = GetPivot,
        .getScale = GetScale,
        .getRotation = GetRotation,
        .getShadowColor = GetShadowColor,
        .getShadowOffset = GetShadowOffset,
        .getShadowAlpha = GetShadowAlpha,
        .setClipToFrame = SetClipToFrame,
        .getClipToFrame = GetClipToFrame,
        .setClipToBounds = SetClipToBounds,
        .getClipToBounds = GetClipToBounds,
        .setTranslation = SetTranslation,
        .getTranslation = GetTranslation,
        .attachModifier = AttachModifier,
        .createModifier = CreateModifier,
        .attachProperty = AttachProperty,
        .setModifierOnDraw = SetModifierOnDraw,
        .disposeModifier = DisposeModifier,
        .createFloatProperty = CreateFloatProperty,
        .setFloatProperty = SetFloatProperty,
        .getFloatProperty = GetFloatProperty,
        .createVector2Property = CreateVector2Property,
        .setVector2Property = SetVector2Property,
        .getVector2Property = GetVector2Property,
        .createColorProperty = CreateColorProperty,
        .setColorProperty = SetColorProperty,
        .getColorProperty = GetColorProperty,
        .createFloatAnimatableProperty = CreateFloatAnimatableProperty,
        .setFloatAnimatableProperty = SetFloatAnimatableProperty,
        .getFloatAnimatableProperty = GetFloatAnimatableProperty,
        .createVector2AnimatableProperty = CreateVector2AnimatableProperty,
        .setVector2AnimatableProperty = SetVector2AnimatableProperty,
        .getVector2AnimatableProperty = GetVector2AnimatableProperty,
        .createColorAnimatableProperty = CreateColorAnimatableProperty,
        .setColorAnimatableProperty = SetColorAnimatableProperty,
        .getColorAnimatableProperty = GetColorAnimatableProperty,
        .disposeProperty = DisposeProperty,
        .getShadowElevation = GetShadowElevation,
        .setShadowRadius = SetShadowRadius,
        .getShadowRadius = GetShadowRadius,
        .setBorderStyle = SetBorderStyle,
        .getBorderStyle = GetBorderStyle,
        .setBorderWidth = SetBorderWidth,
        .getBorderWidth = GetBorderWidth,
        .setBorderColor = SetBorderColor,
        .getBorderColor = GetBorderColor,
        .setBorderRadius = SetBorderRadius,
        .getBorderRadius = GetBorderRadius,
        .setMarkNodeGroup = SetMarkNodeGroup,
        .setBounds = SetBounds,
        .getBounds = GetBounds,
        .setDrawRegion = SetDrawRegion,
        .setSize = SetSize,
        .getSize = GetSize,
        .setPosition = SetPosition,
        .getPosition = GetPosition,
        .setRectMask = SetRectMask,
        .setCircleMask = SetCircleMask,
        .setRoundRectMask = SetRoundRectMask,
        .setOvalMask = SetOvalMask,
        .setCommandPathMask = SetCommandPathMask,
        .setRectClip = SetRectClip,
        .setCircleClip = SetCircleClip,
        .setRoundRectClip = SetRoundRectClip,
        .setOvalClip = SetOvalClip,
        .setCommandPathClip = SetCommandPathClip,
        .setTransform = SetTransform,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
