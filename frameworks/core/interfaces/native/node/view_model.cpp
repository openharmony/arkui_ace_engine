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

#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text/image_span_view.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/node/node_types.h"


namespace OHOS::Ace::NG::ViewModel {
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

void* createColumnNode(ArkUI_Int32 nodeId)
{
    auto frameNode = ColumnModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createRowNode(ArkUI_Int32 nodeId)
{
    auto frameNode = RowModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* createListItemNode(ArkUI_Int32 nodeId)
{
    auto frameNode = ListItemModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

using createArkUIFrameNode = void*(ArkUI_Int32 nodeId);
void* CreateNode(ArkUINodeType tag, ArkUI_Int32 nodeId)
{
    static createArkUIFrameNode* createArkUIFrameNodes[] = {
        nullptr, createTextNode, createSpanNode, createImageSpanNode, createImageNode, createToggleNode,
        createLoadingProgress, createTextInputNode, createStackNode, createScrollNode, createListNode,
        createSwiperNode, nullptr, nullptr, nullptr, nullptr, createColumnNode, createRowNode,
        nullptr, createListItemNode
    };
    if (tag >= sizeof(createArkUIFrameNodes) / sizeof(createArkUIFrameNode*)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to create %{public}d type of node", tag);
        return nullptr;
    }
    CHECK_NULL_RETURN(createArkUIFrameNodes[tag], nullptr);
    return createArkUIFrameNodes[tag](nodeId);
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
    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

} // namespace OHOS::Ace::NG::ViewModel
