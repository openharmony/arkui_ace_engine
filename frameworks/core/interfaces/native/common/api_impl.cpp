/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <sstream>
#include <vector>

// SORTED_SECTION
#include "arkoala-macros.h"
#include "arkoala_api_generated.h"
#include "extension_companion_node.h"

#include "base/error/error_code.h"
#include "core/common/card_scope.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace OHOS::Ace::NG {
namespace GeneratedApiImpl {
void ShowCrash(Ark_CharPtr message)
{
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Arkoala crash: %{public}s", message);
}

ExtensionCompanionNode* GetCompanion(Ark_NodeHandle nodePtr)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(nodePtr));
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto ret = AceType::DynamicCast<ExtensionCompanionNode>(frameNode->GetExtensionHandler());
    if (ret == nullptr) {
        auto pipeline = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_RETURN(pipeline, nullptr);
        auto rootNode = pipeline->GetRootElement();
        CHECK_NULL_RETURN(rootNode, nullptr);
        ret = AceType::DynamicCast<ExtensionCompanionNode>(rootNode->GetExtensionHandler());
        if (ret == nullptr) {
            auto companion = AceType::MakeRefPtr<ExtensionCompanionNode>(0, 0, nullptr);
            rootNode->SetExtensionHandler(companion);
            ret = AceType::RawPtr(companion);
        }
    }
    return ret;
}

Ark_Float32 GetDensity(int deviceId)
{
    return SystemProperties::GetResolution();
}

Ark_Float32 GetFontScale(int deviceId)
{
    auto scale = 0.0;
    auto density = SystemProperties::GetResolution();
    auto container = Container::Current();
    if (container && container->GetPipelineContext()) {
        scale = container->GetPipelineContext()->GetFontScale() * density;
    }
    return scale;
}

Ark_Float32 GetDesignWidthScale(int deviceId)
{
    auto scale = 0.0;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, scale);
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, scale);
    auto windowConfig = frontend->GetWindowConfig();
    return windowConfig.GetDesignWidthScale(SystemProperties::GetDeviceWidth());
}

void SetCustomCallback(Ark_VMContext context, Ark_NodeHandle nodePtr, Ark_Int32 callback) {}

void SetCustomNodeDestroyCallback(void (*destroy)(Ark_NodeHandle nodeId)) {}

Ark_NodeHandle GetNodeByViewStack()
{
    auto node = ViewStackProcessor::GetInstance()->Finish();
    node->IncRefCount();
    return reinterpret_cast<Ark_NodeHandle>(AceType::RawPtr(node));
}

void DisposeNode(Ark_NodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto* uiNode = reinterpret_cast<UINode*>(node);
    auto* frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    if (frameNode) {
        frameNode->SetExtensionHandler(nullptr);
    }
    uiNode->DecRefCount();
}

static void DumpTree(Ark_NodeHandle node, int indent) {}

void DumpTreeNode(Ark_NodeHandle node)
{
    DumpTree(node, 0);
}

Ark_Int32 AddChild(Ark_NodeHandle parentNode, Ark_NodeHandle childNode)
{
    Ark_Int32 result = ERROR_CODE_NO_ERROR;
    CHECK_NULL_RETURN(parentNode, result);
    CHECK_NULL_RETURN(childNode, result);
    auto* parent = reinterpret_cast<UINode*>(parentNode);
    auto* child = reinterpret_cast<UINode*>(childNode);
    parent->AddChild(AceType::Claim(child));
    auto* frameNode = AceType::DynamicCast<FrameNode>(child);
    if (frameNode) {
        frameNode->OnMountToParentDone();
    }
    return result;
}

Ark_Int32 InsertChildAt(Ark_NodeHandle parentNode, Ark_NodeHandle childNode, int32_t position)
{
    Ark_Int32 result = ERROR_CODE_NO_ERROR;
    CHECK_NULL_RETURN(parentNode, result);
    CHECK_NULL_RETURN(childNode, result);
    auto* parent = reinterpret_cast<UINode*>(parentNode);
    auto* child = reinterpret_cast<UINode*>(childNode);
    parent->AddChild(AceType::Claim(child), position);
    auto* frameNode = AceType::DynamicCast<FrameNode>(child);
    if (frameNode) {
        frameNode->OnMountToParentDone();
    }
    return result;
}

void RemoveChild(Ark_NodeHandle parentNode, Ark_NodeHandle childNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    auto* parent = reinterpret_cast<UINode*>(parentNode);
    auto* child = reinterpret_cast<UINode*>(childNode);
    child->MarkRemoving();
    parent->RemoveChild(AceType::Claim(child), true);
}

Ark_Int32 InsertChildAfter(Ark_NodeHandle parentNode, Ark_NodeHandle childNode, Ark_NodeHandle siblingNode)
{
    Ark_Int32 result = ERROR_CODE_NO_ERROR;
    CHECK_NULL_RETURN(parentNode, result);
    CHECK_NULL_RETURN(childNode, result);
    auto* parent = reinterpret_cast<UINode*>(parentNode);
    auto* child = reinterpret_cast<UINode*>(childNode);
    if (auto* groupNode = AceType::DynamicCast<GroupNode>(parent); groupNode) {
        groupNode->AddChildToGroup(AceType::Claim(child));
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return result;
    }
    if (siblingNode == nullptr ||
        siblingNode == reinterpret_cast<Ark_NodeHandle>(0x01) /*lazyForEach markItem case.*/) {
        parent->AddChild(AceType::Claim(child));
    } else {
        auto* sibling = reinterpret_cast<UINode*>(siblingNode);
        parent->AddChildAfter(AceType::Claim(child), AceType::Claim(sibling));
    }
    auto* frameNode = AceType::DynamicCast<FrameNode>(child);
    if (frameNode) {
        frameNode->OnMountToParentDone();
    }
    return result;
}

Ark_Boolean IsBuilderNode(Ark_NodeHandle nodePtr)
{
    CHECK_NULL_RETURN(nodePtr, false);
    auto* node = reinterpret_cast<UINode*>(nodePtr);
    return static_cast<Ark_Int32>(node->GetNodeStatus()) != 0;
}

Ark_Float32 ConvertLengthMetricsUnit(Ark_Float32 value, Ark_Int32 originUnit, Ark_Int32 targetUnit)
{
    Dimension lengthMetric(value, static_cast<DimensionUnit>(originUnit));
    return static_cast<Ark_Float32>(lengthMetric.GetNativeValue(static_cast<DimensionUnit>(targetUnit)));
}

Ark_Int32 InsertChildBefore(Ark_NodeHandle parentNode, Ark_NodeHandle childNode, Ark_NodeHandle siblingNode)
{
    Ark_Int32 result = ERROR_CODE_NO_ERROR;
    CHECK_NULL_RETURN(parentNode, result);
    CHECK_NULL_RETURN(childNode, result);
    auto* parent = reinterpret_cast<UINode*>(parentNode);
    auto* child = reinterpret_cast<UINode*>(childNode);
    if (auto* groupNode = AceType::DynamicCast<GroupNode>(parent); groupNode) {
        groupNode->AddChildToGroup(AceType::Claim(child));
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return result;
    }
    if (siblingNode == nullptr) {
        parent->AddChild(AceType::Claim(child));
    } else {
        auto* sibling = reinterpret_cast<UINode*>(siblingNode);
        parent->AddChildBefore(AceType::Claim(child), AceType::Claim(sibling));
    }
    auto* frameNode = AceType::DynamicCast<FrameNode>(child);
    if (frameNode) {
        frameNode->OnMountToParentDone();
    }
    return result;
}

void ApplyModifierFinish(Ark_NodeHandle nodePtr)
{
    auto* uiNode = reinterpret_cast<UINode*>(nodePtr);
    auto* frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    if (frameNode) {
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    }
}

void MarkDirty(Ark_NodeHandle nodePtr, Ark_UInt32 flag)
{
    auto* uiNode = reinterpret_cast<UINode*>(nodePtr);
    if (uiNode) {
        uiNode->MarkDirtyNode(flag);
    }
}

GENERATED_Ark_APICallbackMethod* callbacks = nullptr;

void SetCallbackMethod(GENERATED_Ark_APICallbackMethod* method)
{
    callbacks = method;
}

GENERATED_Ark_APICallbackMethod* GetCallbackMethod()
{
    return callbacks;
}

Ark_PipelineContext GetPipelineContext(Ark_NodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    return reinterpret_cast<Ark_PipelineContext>(frameNode->GetContext());
}

void SetVsyncCallback(Ark_PipelineContext pipelineContext, Ark_VsyncCallback callback)
{
    auto vsync = [pipelineContext, callback]() { callback(pipelineContext); };
    reinterpret_cast<PipelineContext*>(pipelineContext)->SetVsyncListener(vsync);
}

Ark_Int32 MeasureNode(Ark_VMContext context, Ark_NodeHandle nodePtr, Ark_Float32* data)
{
    // call frameNode measure.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(nodePtr));
    if (frameNode) {
        std::optional<LayoutConstraintF> constraint = std::make_optional<LayoutConstraintF>();
        constraint->minSize.SetWidth(data[0]);  // minWidth
        constraint->minSize.SetHeight(data[1]); // minHeight
        constraint->maxSize.SetWidth(data[2]);  // maxWidth
        constraint->maxSize.SetHeight(data[3]); // maxHeight
        bool idealWidth = data[0] == data[2];   // minWidth == maxWidth
        if (idealWidth) {
            constraint->selfIdealSize.SetWidth(data[0]);
        }
        bool idealHeight = data[1] == data[3]; // minHeight == maxHeight
        if (idealHeight) {
            constraint->selfIdealSize.SetHeight(data[1]);
        }
        constraint->percentReference.SetWidth(data[4]);  // percentReferenceWidth
        constraint->percentReference.SetHeight(data[5]); // percentReferenceHeight
        frameNode->SetActive(true);
        frameNode->Measure(constraint);
    }
    return 0;
}

Ark_Int32 LayoutNode(Ark_VMContext vmContext, Ark_NodeHandle node, Ark_Float32 (*data)[2])
{
    // call frameNode layout.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (frameNode) {
        frameNode->SetActive(true);
        frameNode->GetGeometryNode()->SetMarginFrameOffsetX((*data)[0]);
        frameNode->GetGeometryNode()->SetMarginFrameOffsetY((*data)[1]);
        frameNode->Layout();
    }
    return 0;
}

Ark_Int32 DrawNode(Ark_VMContext vmContext, Ark_NodeHandle node, Ark_Float32* data)
{
    // rsnode draw by data, no need to directly call.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (frameNode) {
        frameNode->SetActive(true);
        auto task = frameNode->CreateRenderTask();
        if (task) {
            (*task)();
        }
    }
    return 0;
}

void SetAttachNodePtr(Ark_NodeHandle nodePtr, void* value)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(nodePtr));
    if (frameNode) {
        frameNode->SetExternalData(value);
    }
}

void* GetAttachNodePtr(Ark_NodeHandle nodePtr)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(nodePtr));
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetExternalData();
}

Ark_Int32 MeasureLayoutAndDraw(Ark_VMContext vmContext, Ark_NodeHandle rootPtr)
{
    auto* root = reinterpret_cast<FrameNode*>(rootPtr);
    CHECK_NULL_RETURN(root, 0);
    while (root->GetTag() != V2::STAGE_ETS_TAG) {
        auto parentNode = AceType::DynamicCast<FrameNode>(root->GetParent());
        CHECK_NULL_RETURN(parentNode, 0);
        root = AceType::RawPtr(parentNode);
    }
    float width = root->GetGeometryNode()->GetFrameSize().Width();
    float height = root->GetGeometryNode()->GetFrameSize().Height();
    auto stagePtr = reinterpret_cast<Ark_NodeHandle>(root);
    // measure
    Ark_Float32 measureData[] = { width, height, width, height, width, height };
    MeasureNode(vmContext, stagePtr, &measureData[0]);
    // layout
    Ark_Float32 layoutData[] = { 0, 0 };
    LayoutNode(vmContext, stagePtr, &layoutData);
    // draw
    Ark_Float32 drawData[] = { 0, 0, 0, 0 };
    DrawNode(vmContext, stagePtr, &drawData[0]);

    if (auto companionNode = GetCompanion(stagePtr); companionNode) {
        companionNode->SetVMContext(vmContext);
    }
    return 0;
}

void SetMeasureWidth(Ark_NodeHandle node, Ark_Int32 value)
{
    // directly set frameNode measure width.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(frameNode);
    frameNode->GetGeometryNode()->SetFrameWidth(value);
}

Ark_Int32 GetMeasureWidth(Ark_NodeHandle node)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetGeometryNode()->GetFrameSize().Width();
}

void SetMeasureHeight(Ark_NodeHandle node, Ark_Int32 value)
{
    // directly set frameNode measure height.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(frameNode);
    frameNode->GetGeometryNode()->SetFrameHeight(value);
}

Ark_Int32 GetMeasureHeight(Ark_NodeHandle node)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetGeometryNode()->GetFrameSize().Height();
}

void SetX(Ark_NodeHandle node, Ark_Int32 value)
{
    // directly set frameNode measure positionX.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(frameNode);
    frameNode->GetGeometryNode()->SetMarginFrameOffsetX(value);
}

void SetY(Ark_NodeHandle node, Ark_Int32 value)
{
    // directly set frameNode measure positionY.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(frameNode);
    frameNode->GetGeometryNode()->SetMarginFrameOffsetY(value);
}

Ark_Int32 GetX(Ark_NodeHandle node)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetGeometryNode()->GetMarginFrameOffset().GetX();
}

Ark_Int32 GetY(Ark_NodeHandle node)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetGeometryNode()->GetMarginFrameOffset().GetY();
}

void SetCustomMethodFlag(Ark_NodeHandle node, Ark_Int32 flag)
{
    auto* companion = GetCompanion(node);
    CHECK_NULL_VOID(companion);
    companion->SetFlags(flag);
}

Ark_Int32 GetCustomMethodFlag(Ark_NodeHandle node)
{
    auto* companion = GetCompanion(node);
    CHECK_NULL_RETURN(companion, 0);
    return companion->GetFlags();
}

void SetAlignment(Ark_NodeHandle node, Ark_Int32 value)
{
    auto* companion = GetCompanion(node);
    CHECK_NULL_VOID(companion);
    companion->SetAlignmentValue(value);
}

Ark_Int32 GetAlignment(Ark_NodeHandle node)
{
    auto* companion = GetCompanion(node);
    CHECK_NULL_RETURN(companion, 0);
    return companion->GetAlignmentValue();
}

void GetLayoutConstraint(Ark_NodeHandle node, Ark_Int32* value)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(frameNode);
    auto layoutConstraint = frameNode->GetLayoutProperty()->GetContentLayoutConstraint();
    if (layoutConstraint.has_value()) {
        // min
        *value++ = static_cast<Ark_Int32>(layoutConstraint.value().minSize.Width());
        // min
        *value++ = static_cast<Ark_Int32>(layoutConstraint.value().minSize.Height());
        //.max
        *value++ = static_cast<Ark_Int32>(layoutConstraint.value().maxSize.Width());
        //.max
        *value++ = static_cast<Ark_Int32>(layoutConstraint.value().maxSize.Height());
        // percentReference
        *value++ = static_cast<Ark_Int32>(layoutConstraint.value().percentReference.Width());
        // percentReference
        *value++ = static_cast<Ark_Int32>(layoutConstraint.value().percentReference.Height());
    }
}

void SetChildTotalCount(Ark_NodeHandle node, int totalCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == OHOS::Ace::V2::LIST_ETS_TAG) {
        // ListModelNG::SetListItemTotalCount(frameNode, totalCount);
        return;
    }
    if (frameNode->GetTag() == OHOS::Ace::V2::GRID_ETS_TAG) {
        // GridModelNG::SetGridItemTotalCount(frameNode, totalCount);
        return;
    }
}

int IndexerChecker(Ark_VMContext vmContext, Ark_NodeHandle nodePtr)
{
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NOT IMPLEMENTED! Arkoala IndexerChecker");
    return 1;
}

void SetRangeUpdater(Ark_NodeHandle nodePtr, int updaterId)
{
#ifdef LAZY_CALLBACK_IMPL
    auto* frameNode = reinterpret_cast<FrameNode*>(nodePtr);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == OHOS::Ace::V2::LIST_ETS_TAG) {
        auto continuation = new ListItemAdapterContinuation(nodePtr);
        continuations.emplace(continuation->Id(), continuation);
        auto requestFunc = [updaterId, id = continuation->Id()](int start, int end) {
            ArkUINodeEvent event;
            event.kind = ArkUIEventCategory::CALLBACK_EVENT;
            event.callback.id = updaterId;
            event.callback.continuationId = id;
            event.callback.numArgs = 2;
            event.callback.args[0] = { start };
            event.callback.args[1] = { end };
            SendArkUIAsyncEvent(&event);
        };
        ListModelNG::SetListItemAdapterFunc(frameNode, std::move(requestFunc));
        return;
    }
    if (frameNode->GetTag() == OHOS::Ace::V2::GRID_ETS_TAG) {
        auto continuation = new GridItrmAdapterContinuation(nodePtr);
        continuations.emplace(continuation->Id(), continuation);
        auto requestFunc = [updaterId, id = continuation->Id()](int start, int end) {
            ArkUINodeEvent event;
            event.kind = ArkUIEventCategory::CALLBACK_EVENT;
            event.callback.id = updaterId;
            event.callback.continuationId = id;
            event.callback.numArgs = 2;
            event.callback.args[0] = { start };
            event.callback.args[1] = { end };
            SendArkUIAsyncEvent(&event);
        };
        GridModelNG::SetGridItemAdapterFunc(frameNode, std::move(requestFunc));
        return;
    }
#endif
}

template<typename T>
inline T* fromBits(GENERATED_Ark_EventCallbackArg* args)
{
    uint64_t raw = static_cast<uint64_t>(args[0].u32) | (static_cast<uint64_t>(args[1].u32) << 32);
    return reinterpret_cast<T*>(static_cast<uintptr_t>(raw));
}

void SetLazyItemIndexer(Ark_VMContext vmContext, Ark_NodeHandle nodePtr, int indexerId)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(nodePtr);
    CHECK_NULL_VOID(frameNode);
    auto getNodeByIndex = [vmContext, indexerId](int32_t index) -> OHOS::Ace::RefPtr<FrameNode> {
        GENERATED_Ark_EventCallbackArg args[] = { { index }, { 0 }, { 0 } };
        int found = GetCallbackMethod()->CallInt(vmContext, indexerId, 3, &args[0]);
        if (found == 0) {
            return nullptr;
        }
        return OHOS::Ace::AceType::Claim(fromBits<FrameNode>(&args[1]));
    };
    if (frameNode->GetTag() == OHOS::Ace::V2::LIST_ETS_TAG) {
        // ListModelNG::SetListItemGetFunc(frameNode, std::move(getNodeByIndex));
        return;
    }
    if (frameNode->GetTag() == OHOS::Ace::V2::GRID_ETS_TAG) {
        // GridModelNG::SetGridItemGetFunc(frameNode, std::move(getNodeByIndex));
        return;
    }
}

void EmitOnClick(Ark_NativePointer node, Ark_ClickEvent event) {}
} // namespace GeneratedApiImpl
} // namespace OHOS::Ace::NG

extern "C" {
IDLIZE_API_EXPORT const GENERATED_ArkUIAnyAPI* GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind kind, int version);

__attribute__((constructor)) static void ProvideEntryPoint(void)
{
    std::stringstream entryPointString;
    auto addr = static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(&GENERATED_GetArkAnyAPI));
#ifdef WINDOWS_PLATFORM
    entryPointString << "__LIBACE_ENTRY_POINT=" << std::hex << addr;
    putenv(entryPointString.str().c_str());
#else
    entryPointString << std::hex << addr;
    setenv("__LIBACE_ENTRY_POINT", entryPointString.str().c_str(), 1);
#endif
}
}
