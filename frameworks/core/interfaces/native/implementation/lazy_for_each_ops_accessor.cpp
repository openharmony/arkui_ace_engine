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

#include <cstdint>

#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/syntax/arkoala_lazy_node.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LazyForEachOpsAccessor {
void SyncItemDragEvent(
    ArkoalaLazyNode* lazyNode, const Opt_ItemDragEventHandler* onMoveDragEventOps)
{
    std::function<void(int32_t)> onLongPressCallback;
    std::function<void(int32_t)> onDragStartCallback;
    std::function<void(int32_t, int32_t)> onMoveThroughCallback;
    std::function<void(int32_t)> onDropCallback;
    auto onMoveDragEventOpt = Converter::GetOptPtr(onMoveDragEventOps);
    if (!onMoveDragEventOpt) {
        lazyNode->SetItemDragEvent(nullptr, nullptr, nullptr, nullptr);
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
    lazyNode->SetItemDragEvent(std::move(onLongPressCallback), std::move(onDragStartCallback),
        std::move(onMoveThroughCallback), std::move(onDropCallback));
}
void NotifyChangeImpl(Ark_NativePointer node, int32_t startIdx, int32_t endIdx, int32_t changeCnt)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    auto lazyNode = AceType::DynamicCast<ArkoalaLazyNode>(uiNode);
    CHECK_NULL_VOID(lazyNode);
    lazyNode->OnDataChange(startIdx, changeCnt, UINode::NotificationType::START_CHANGE_POSITION);
}
void SyncImpl(Ark_NativePointer node,
              Ark_Int32 totalCount,
              const Callback_CreateItem* creator,
              const Callback_RangeUpdate* updater)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode && creator && updater);
    auto lazyNode = AceType::DynamicCast<ArkoalaLazyNode>(uiNode);
    CHECK_NULL_VOID(lazyNode);

    lazyNode->SetTotalCount(totalCount);
    lazyNode->SetCallbacks(
        [callback = CallbackHelper(*creator)](int32_t index) {
            return AceType::DynamicCast<UINode>(callback.BuildSync(index));
        },
        [cb = CallbackHelper(*updater)](
            int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool isLoop) {
            cb.InvokeSync(start, end, cacheStart, cacheEnd, isLoop);
        });
}
void SyncOnMoveOpsImpl(Ark_NativePointer node,
                       const Callback_OnMoveFromTo* onMoveFromToOps,
                       const Opt_OnMoveHandler* onMoveOps,
                       const Opt_ItemDragEventHandler* onMoveDragEventOps)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode && onMoveFromToOps);
    ArkoalaLazyNode* lazyNode = AceType::DynamicCast<ArkoalaLazyNode>(uiNode);
    CHECK_NULL_VOID(lazyNode);
    auto onMoveOpt = Converter::OptConvert<OnMoveHandler>(*onMoveOps);
    if (!onMoveOpt) {
        // enable user to disable onMove callback.
        lazyNode->SetOnMove(nullptr);
        lazyNode->SetOnMoveFromTo(nullptr);
        lazyNode->SetItemDragEvent(nullptr, nullptr, nullptr, nullptr);
        return;
    }
    lazyNode->SetOnMove([callback = CallbackHelper(*onMoveOpt)](int32_t from, int32_t to) {
        auto arkFrom = Converter::ArkValue<Ark_Int32>(from);
        auto arkTo = Converter::ArkValue<Ark_Int32>(to);
        callback.InvokeSync(arkFrom, arkTo);
    });
    lazyNode->SetOnMoveFromTo([callback = CallbackHelper(*onMoveFromToOps)](int32_t from, int32_t to) {
        callback.InvokeSync(from, to);
    });
    // set drag event callback
    SyncItemDragEvent(lazyNode, onMoveDragEventOps);
}
} // LazyForEachOpsAccessor
const GENERATED_ArkUILazyForEachOpsAccessor* GetLazyForEachOpsAccessor()
{
    static const GENERATED_ArkUILazyForEachOpsAccessor LazyForEachOpsAccessorImpl {
        LazyForEachOpsAccessor::NotifyChangeImpl,
        LazyForEachOpsAccessor::SyncImpl,
        LazyForEachOpsAccessor::SyncOnMoveOpsImpl,
    };
    return &LazyForEachOpsAccessorImpl;
}

}
