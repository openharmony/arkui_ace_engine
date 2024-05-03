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

#include "core/interfaces/native/node/view_model.h"

#include <optional>

#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/components_ng/pattern/common_view/common_view_model_ng.h"
#include "core/components_ng/pattern/custom_paint/canvas_model_ng.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text/image_span_view.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/flex/flex_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG::ViewModel {

ArkUIAPICallbackMethod* callbacks = nullptr;

void* createTextNode(ArkUI_Int32 nodeId)
{
    auto frameNode = TextModelNG::CreateFrameNode(nodeId, "");
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createSpanNode(ArkUI_Int32 nodeId)
{
    auto spanNode = SpanModelNG::CreateSpanNode(nodeId, "");
    spanNode->IncRefCount();
    return AceType::RawPtr(spanNode);
}

void* createImageSpanNode(ArkUI_Int32 nodeId)
{
    auto imageSpanNode = ImageSpanView::CreateFrameNode(nodeId);
    imageSpanNode->IncRefCount();
    return AceType::RawPtr(imageSpanNode);
}
void* createImageNode(ArkUI_Int32 nodeId)
{
    RefPtr<PixelMap> pixmap = nullptr;
    auto frameNode = ImageModelNG::CreateFrameNode(nodeId, "", pixmap, "", "", false);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createToggleNode(ArkUI_Int32 nodeId)
{
    auto frameNode = ToggleModelNG::CreateFrameNode(nodeId, NG::ToggleType::SWITCH, false);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createLoadingProgress(ArkUI_Int32 nodeId)
{
    auto frameNode = LoadingProgressModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createTextInputNode(ArkUI_Int32 nodeId)
{
    auto frameNode = TextFieldModelNG::CreateFrameNode(nodeId, "", "", false);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createStackNode(ArkUI_Int32 nodeId)
{
    auto frameNode = StackModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createScrollNode(ArkUI_Int32 nodeId)
{
    auto frameNode = ScrollModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createListNode(ArkUI_Int32 nodeId)
{
    auto frameNode = ListModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createSwiperNode(ArkUI_Int32 nodeId)
{
    auto frameNode = SwiperModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createTextAreaNode(ArkUI_Int32 nodeId)
{
    auto frameNode = TextFieldModelNG::CreateFrameNode(nodeId, "", "", true);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createButtonNode(ArkUI_Int32 nodeId)
{
    auto frameNode = ButtonModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createProgressNode(ArkUI_Int32 nodeId)
{
    auto frameNode = ProgressModelNG::CreateFrameNode(nodeId, 0, 100, NG::ProgressType::LINEAR);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createCheckBoxNode(ArkUI_Int32 nodeId)
{
    auto frameNode = CheckBoxModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createColumnNode(ArkUI_Int32 nodeId)
{
    auto frameNode = ColumnModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    TAG_LOGD(AceLogTag::ACE_NATIVE_NODE, "createColumnNode: frameNode %{public}p", AceType::RawPtr(frameNode));
    return AceType::RawPtr(frameNode);
}

void* createRowNode(ArkUI_Int32 nodeId)
{
    auto frameNode = RowModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createFlexNode(ArkUI_Int32 nodeId)
{
    auto frameNode = FlexModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createListItemNode(ArkUI_Int32 nodeId)
{
    auto frameNode = ListItemModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createRefreshNode(ArkUI_Int32 nodeId)
{
    auto frameNode = RefreshModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createRootNode(ArkUI_Int32 nodeId)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    RefPtr<PipelineBase> pipeline;
    pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(context, nullptr);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_RETURN(stageManager, nullptr);
    auto stageNode = stageManager->GetStageNode();
    TAG_LOGD(AceLogTag::ACE_NATIVE_NODE, "createRootNode: stageNode %{public}p", AceType::RawPtr(stageNode));
    return AceType::RawPtr(stageNode);
}

void* createComponentRootNode(ArkUI_Int32 nodeId)
{
    auto frameNode = CommonViewModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    TAG_LOGD(AceLogTag::ACE_NATIVE_NODE, "createComponentRootNode: frameNode %{public}p", AceType::RawPtr(frameNode));
    return AceType::RawPtr(frameNode);
}

#ifdef XCOMPONENT_SUPPORTED
void* createXComponentNode(ArkUI_Int32 nodeId)
{
    auto frameNode = XComponentModelNG::CreateFrameNode(nodeId, "", XComponentType::SURFACE, "");
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
#endif

void* createListItemGroupNode(ArkUI_Int32 nodeId)
{
    auto frameNode = ListItemGroupModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createSliderNode(ArkUI_Int32 nodeId)
{
    auto frameNode = SliderModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createCanvasNode(ArkUI_Int32 nodeId)
{
    auto frameNode = CanvasModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createDatePickerNode(ArkUI_Int32 nodeId)
{
    auto frameNode = DatePickerModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createTimePickerNode(ArkUI_Int32 nodeId)
{
    auto frameNode = TimePickerModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createTextPickerNode(ArkUI_Int32 nodeId)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createCalendarPickerNode(ArkUI_Int32 nodeId)
{
    auto frameNode = CalendarPickerModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createCustomNode(ArkUI_Int32 nodeId)
{
    auto frameNode = StackModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createWaterFlowNode(ArkUI_Int32 nodeId)
{
    auto frameNode = WaterFlowModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createFlowItemNode(ArkUI_Int32 nodeId)
{
    auto frameNode = WaterFlowItemModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createCircleNode(ArkUI_Int32 nodeId)
{
    auto frameNode = CircleModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createGridNode(ArkUI_Int32 nodeId)
{
    auto frameNode = GridModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createGridItemNode(ArkUI_Int32 nodeId)
{
    auto frameNode = GridItemModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createBlankNode(ArkUI_Int32 nodeId)
{
    auto frameNode = BlankModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createDividerNode(ArkUI_Int32 nodeId)
{
    auto frameNode = DividerModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createAlphabetIndexerNode(ArkUI_Int32 nodeId)
{
    auto frameNode = IndexerModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createSearchNode(ArkUI_Int32 nodeId)
{
    auto frameNode = SearchModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createGridRowNode(ArkUI_Int32 nodeId)
{
    auto frameNode = GridRowModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createGridColNode(ArkUI_Int32 nodeId)
{
    auto frameNode = GridColModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

using createArkUIFrameNode = void*(ArkUI_Int32 nodeId);
void* CreateNode(ArkUINodeType tag, ArkUI_Int32 nodeId)
{
    static createArkUIFrameNode* createArkUIFrameNodes[] = {
        nullptr,
        createTextNode,
        createSpanNode,
        createImageSpanNode,
        createImageNode,
        createToggleNode,
        createLoadingProgress,
        createTextInputNode,
        createStackNode,
        createScrollNode,
        createListNode,
        createSwiperNode,
        createTextAreaNode,
        createButtonNode,
        createProgressNode,
        createCheckBoxNode,
        createColumnNode,
        createRowNode,
        createFlexNode,
        createListItemNode,
        nullptr, // Tabs
        nullptr, // Navigator
        nullptr, // Web
        createSliderNode,
        createCanvasNode,
        nullptr, // Radio
        createGridNode,
#ifdef XCOMPONENT_SUPPORTED
        createXComponentNode,
#else
        nullptr,
#endif
        nullptr, // SideBar
        createRefreshNode,
        createRootNode,
        createComponentRootNode,
        createListItemGroupNode,
        createDatePickerNode,
        createTimePickerNode,
        createTextPickerNode,
        createCalendarPickerNode,
        createGridItemNode,
        createCustomNode,
        createWaterFlowNode,
        createFlowItemNode,
        createBlankNode,
        createDividerNode,
        createAlphabetIndexerNode,
        createSearchNode,
        createGridRowNode,
        createGridColNode,
        createCircleNode,
    };
    if (tag >= sizeof(createArkUIFrameNodes) / sizeof(createArkUIFrameNode*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to create %{public}d type of node", tag);
        return nullptr;
    }
    CHECK_NULL_RETURN(createArkUIFrameNodes[tag], nullptr);
    if (nodeId == ARKUI_AUTO_GENERATE_NODE_ID) {
        nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    }
    return createArkUIFrameNodes[tag](nodeId);
}

ArkUI_CharPtr GetName(void* nativePtr)
{
    CHECK_NULL_RETURN(nativePtr, nullptr);
    auto* frameNode = reinterpret_cast<UINode*>(nativePtr);
    return frameNode->GetTag().c_str();
}

void DisposeNode(void* nativePtr)
{
    CHECK_NULL_VOID(nativePtr);
    auto* frameNode = reinterpret_cast<UINode*>(nativePtr);
    frameNode->DecRefCount();
}

void AddChild(void* parentNode, void* childNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    auto* parent = reinterpret_cast<UINode*>(parentNode);
    auto* child = reinterpret_cast<UINode*>(childNode);
    parent->AddChild(AceType::Claim(child));
    auto* frameNode = AceType::DynamicCast<FrameNode>(child);
    if (frameNode) {
        frameNode->OnMountToParentDone();
    }
}

void RemoveChild(void* parentNode, void* childNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    auto* parent = reinterpret_cast<UINode*>(parentNode);
    auto* child = reinterpret_cast<UINode*>(childNode);
    parent->RemoveChild(AceType::Claim(child));
}

void InsertChildAt(void* parentNode, void* childNode, int32_t position)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    auto* parent = reinterpret_cast<UINode*>(parentNode);
    auto* child = reinterpret_cast<UINode*>(childNode);
    parent->AddChild(AceType::Claim(child), position);
    auto* frameNode = AceType::DynamicCast<FrameNode>(child);
    if (frameNode) {
        frameNode->OnMountToParentDone();
    }
}

void InsertChildAfter(void* parentNode, void* childNode, void* siblingNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    auto* parent = reinterpret_cast<UINode*>(parentNode);
    auto* child = reinterpret_cast<UINode*>(childNode);
    
    if (AceType::InstanceOf<GroupNode>(parent)) {
        auto* groupNode = AceType::DynamicCast<GroupNode>(parent);
        groupNode->AddChildToGroup(AceType::Claim(child));
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto* sibling = reinterpret_cast<UINode*>(siblingNode);
    if (sibling) {
        parent->AddChildAfter(AceType::Claim(child), AceType::Claim(sibling));
    } else {
        parent->AddChild(AceType::Claim(child));
    }
    auto* frameNode = AceType::DynamicCast<FrameNode>(child);
    if (frameNode) {
        frameNode->OnMountToParentDone();
    }
}

void InsertChildBefore(void* parentNode, void* childNode, void* siblingNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    auto* parent = reinterpret_cast<UINode*>(parentNode);
    auto* child = reinterpret_cast<UINode*>(childNode);

    if (AceType::InstanceOf<GroupNode>(parent)) {
        auto* groupNode = AceType::DynamicCast<GroupNode>(parent);
        groupNode->AddChildToGroup(AceType::Claim(child));
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto* sibling = reinterpret_cast<UINode*>(siblingNode);
    if (sibling) {
        parent->AddChildBefore(AceType::Claim(child), AceType::Claim(sibling));
    } else {
        parent->AddChild(AceType::Claim(child));
    }
    auto* frameNode = AceType::DynamicCast<FrameNode>(child);
    if (frameNode) {
        frameNode->OnMountToParentDone();
    }
}

void RegisterCompanion(void* node, int peerId, ArkUI_Int32 flags)
{
    if (flags == ArkUIAPINodeFlags::NONE) {
        return;
    }
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (frameNode) {
        // create extension and set to frameNode extension holder.
        auto companion = AceType::MakeRefPtr<ExtensionCompanionNode>(peerId, flags, node);
        frameNode->SetExtensionHandler(companion);
    }
}

ExtensionCompanionNode* GetCompanion(void* nodePtr)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(nodePtr));
    if (frameNode) {
        return AceType::DynamicCast<ExtensionCompanionNode>(frameNode->GetExtensionHandler());
    }
    return nullptr;
}

void SetCustomCallback(ArkUIVMContext context, void* nodePtr, ArkUI_Int32 callback)
{
    auto* node = GetCompanion(nodePtr);
    CHECK_NULL_VOID(node);
    node->SetCallbackId(context, callback);
}

void SetCallbackMethod(ArkUIAPICallbackMethod* method)
{
    callbacks = method;
}

ArkUIAPICallbackMethod* GetCallbackMethod()
{
    return callbacks;
}

ArkUI_Int32 MeasureNode(ArkUIVMContext context, ArkUINodeHandle nodePtr, ArkUI_Float32* data)
{
    // call frameNode measure.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(nodePtr));
    if (frameNode) {
        std::optional<LayoutConstraintF> constraint = std::make_optional<LayoutConstraintF>();
        //minWidth
        constraint->minSize.SetWidth(data[0]);
        //minHeight
        constraint->minSize.SetHeight(data[1]);
        //maxWidth
        constraint->maxSize.SetWidth(data[2]);
        //maxHeight
        constraint->maxSize.SetHeight(data[3]);
        //minWidth == maxWidth
        if (data[0] == data[2]) {
            constraint->selfIdealSize.SetWidth(data[0]);
        }
        //minHeight == maxHeight
        if (data[1] == data[3]) {
            constraint->selfIdealSize.SetHeight(data[0]);
        }
        //percentReferenceWidth
        constraint->percentReference.SetWidth(data[4]);
        //percentReferenceHeight
        constraint->percentReference.SetHeight(data[5]);
        frameNode->SetActive(true);
        frameNode->Measure(constraint);
    }
    return 0;
}

ArkUI_Int32 LayoutNode(ArkUIVMContext context, ArkUINodeHandle nodePtr, ArkUI_Float32* data)
{
    // call frameNode layout.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(nodePtr));
    if (frameNode) {
        frameNode->SetActive(true);
        frameNode->GetGeometryNode()->SetMarginFrameOffsetX(data[0]);
        frameNode->GetGeometryNode()->SetMarginFrameOffsetY(data[1]);
        frameNode->Layout();
    }
    return 0;
}

ArkUI_Int32 DrawNode(ArkUIVMContext context, ArkUINodeHandle nodePtr, ArkUI_Float32* data)
{
    // rsnode draw by data, no need to directly call.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(nodePtr));
    if (frameNode) {
        frameNode->SetActive(true);
        auto task = frameNode->CreateRenderTask();
        if (task) {
            (*task)();
        }
    }
    return 0;
}

void SetAttachNodePtr(ArkUINodeHandle nodePtr, void* attachNode)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(nodePtr));
    if (frameNode) {
        frameNode->SetExternalData(attachNode);
    }
}

void* GetAttachNodePtr(ArkUINodeHandle nodePtr)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(nodePtr));
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetExternalData();
}

ArkUI_Bool IsBuilderNode(void* nodePtr)
{
    CHECK_NULL_RETURN(nodePtr, false);
    auto* node = reinterpret_cast<UINode*>(nodePtr);
    return static_cast<ArkUI_Int32>(node->GetNodeStatus()) != 0 ;
}
} // namespace OHOS::Ace::NG::ViewModel
