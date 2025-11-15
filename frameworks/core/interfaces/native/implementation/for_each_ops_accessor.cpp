/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <cstdint>

#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/syntax/arkoala_for_each_node.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ForEachOpsAccessor {
void SyncItemDragEvent(
    ArkoalaForEachNode* forEachNode, const Opt_ItemDragEventHandler* onMoveDragEventOps)
{
    std::function<void(int32_t)> onLongPressCallback;
    std::function<void(int32_t)> onDragStartCallback;
    std::function<void(int32_t, int32_t)> onMoveThroughCallback;
    std::function<void(int32_t)> onDropCallback;
    auto onMoveDragEventOpt = Converter::GetOptPtr(onMoveDragEventOps);
    if (!onMoveDragEventOpt) {
        forEachNode->SetItemDragEvent(nullptr, nullptr, nullptr, nullptr);
        return;
    }
    auto onLongPressOpt = Converter::OptConvert<Callback_I32_Void>(onMoveDragEventOpt->onLongPress);
    auto onDragStartOpt = Converter::OptConvert<Callback_I32_Void>(onMoveDragEventOpt->onDragStart);
    auto onMoveThroughOpt = Converter::OptConvert<OnMoveHandler>(onMoveDragEventOpt->onMoveThrough);
    auto onDropOpt = Converter::OptConvert<Callback_I32_Void>(onMoveDragEventOpt->onDrop);
    if (onLongPressOpt) {
        onLongPressCallback = [arkCallback = CallbackHelper(*onLongPressOpt)](int32_t index) {
            auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
            arkCallback.Invoke(arkIndex);
        };
    }
    if (onDragStartOpt) {
        onDragStartCallback = [arkCallback = CallbackHelper(*onDragStartOpt)](int32_t index) {
            auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
            arkCallback.Invoke(arkIndex);
        };
    }
    if (onMoveThroughOpt) {
        onMoveThroughCallback = [arkCallback = CallbackHelper(*onMoveThroughOpt)](int32_t from, int32_t to) {
            auto arkFrom = Converter::ArkValue<Ark_Int32>(from);
            auto arkTo = Converter::ArkValue<Ark_Int32>(to);
            arkCallback.Invoke(arkFrom, arkTo);
        };
    }
    if (onDropOpt) {
        onDropCallback = [arkCallback = CallbackHelper(*onDropOpt)](int32_t index) {
            auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
            arkCallback.Invoke(arkIndex);
        };
    }
    forEachNode->SetItemDragEvent(std::move(onLongPressCallback), std::move(onDragStartCallback),
        std::move(onMoveThroughCallback), std::move(onDropCallback));
}
void SyncOnMoveOpsImpl(Ark_NativePointer node,
                       const Array_NativePointer* additionalChild,
                       const Opt_OnMoveHandler* onMoveOps,
                       const Opt_ItemDragEventHandler* onMoveDragEventOps)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    ArkoalaForEachNode* forEachNode = AceType::DynamicCast<ArkoalaForEachNode>(uiNode);
    CHECK_NULL_VOID(forEachNode);
    CHECK_NULL_VOID(additionalChild);
    auto onMoveOpt = Converter::OptConvert<OnMoveHandler>(*onMoveOps);
    if (!onMoveOpt) {
        // enable user to disable onMove callback.
        forEachNode->SetOnMove(nullptr);
        forEachNode->SetItemDragEvent(nullptr, nullptr, nullptr, nullptr);
        return;
    }
    forEachNode->SetOnMove([callback = CallbackHelper(*onMoveOpt)](int32_t from, int32_t to) {
        auto arkFrom = Converter::ArkValue<Ark_Int32>(from);
        auto arkTo = Converter::ArkValue<Ark_Int32>(to);
        callback.InvokeSync(arkFrom, arkTo);
    });
    for (int32_t i = 0; i < additionalChild->length; ++i) {
        auto* childNode = reinterpret_cast<UINode*>(additionalChild->array[i]);
        if (childNode) {
            forEachNode->InitDragManager(AceType::DynamicCast<FrameNode>(childNode->GetFrameChildByIndex(0, true)));
        }
    }
    // set drag event callback
    SyncItemDragEvent(forEachNode, onMoveDragEventOps);
}
} // ForEachOpsAccessor
const GENERATED_ArkUIForEachOpsAccessor* GetForEachOpsAccessor()
{
    static const GENERATED_ArkUIForEachOpsAccessor ForEachOpsAccessorImpl {
        ForEachOpsAccessor::SyncOnMoveOpsImpl,
    };
    return &ForEachOpsAccessorImpl;
}

}
