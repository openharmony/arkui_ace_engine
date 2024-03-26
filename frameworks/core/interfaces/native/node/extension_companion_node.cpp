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

#include "core/interfaces/native/node/extension_companion_node.h"

#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/node/view_model.h"

namespace {

constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_32 = 32;

} // namespace

namespace OHOS::Ace::NG {

const std::vector<ArkUIAPINodeFlags> NODE_FLAGS = { ArkUIAPINodeFlags::CUSTOM_MEASURE, ArkUIAPINodeFlags::CUSTOM_LAYOUT,
    ArkUIAPINodeFlags::CUSTOM_DRAW, ArkUIAPINodeFlags::CUSTOM_FOREGROUND_DRAW, ArkUIAPINodeFlags::CUSTOM_OVERLAY_DRAW };

ArkUICanvasHandle ExtensionCompanionNode::GetCanvas()
{
    return reinterpret_cast<ArkUICanvasHandle>(0x123456789aLL);
}

ArkUIEventCallbackArg ExtensionCompanionNode::Arg(ArkUI_Float32 f32)
{
    ArkUIEventCallbackArg result;
    result.f32 = f32;
    return result;
}

ArkUIEventCallbackArg ExtensionCompanionNode::Arg(ArkUI_Int32 i32)
{
    ArkUIEventCallbackArg result;
    result.i32 = i32;
    return result;
}

ArkUI_Int32 ExtensionCompanionNode::GetPeerId() const
{
    return peerId_;
}

ArkUI_Int32 ExtensionCompanionNode::GetCallbackId() const
{
    return customCallbackId_;
}

void ExtensionCompanionNode::SetCallbackId(ArkUIVMContext context, int id)
{
    context_ = context;
    customCallbackId_ = id;
}

void ExtensionCompanionNode::SetExtraParam(ArkUI_Int32 type, void* extraParam)
{
    for (const auto& flag : NODE_FLAGS) {
        if (type & flag) {
            auto it = extraParamMap_.find(flag);
            if (it != extraParamMap_.end()) {
                it->second = extraParam;
            } else {
                extraParamMap_.emplace(flag, extraParam);
            }
        }
    }
}

void* ExtensionCompanionNode::GetExtraParam(ArkUI_Int32 type)
{
    auto it = extraParamMap_.find(type);
    if (it != extraParamMap_.end()) {
        return it->second;
    }
    return nullptr;
}

void ExtensionCompanionNode::EraseExtraParam(ArkUI_Int32 type)
{
    for (const auto& flag : NODE_FLAGS) {
        if (type & flag) {
            auto it = extraParamMap_.find(type);
            if (it != extraParamMap_.end()) {
                extraParamMap_.erase(it);
            }
        }
    }
}

void ExtensionCompanionNode::OnMeasure(const ExtensionLayoutConstraint& layoutConstraint)
{
    if (flags_ & ArkUIAPINodeFlags::CUSTOM_MEASURE) {
        // call extension logic to manager side.
        ArkUICustomNodeEvent event;
        event.kind = ArkUIAPINodeFlags::CUSTOM_MEASURE;
        event.extraParam = GetExtraParam(static_cast<ArkUI_Int32>(ArkUIAPINodeFlags::CUSTOM_MEASURE));
        event.componentAsyncEvent.data[NUM_0].i32 = layoutConstraint.minWidth;
        event.componentAsyncEvent.data[NUM_1].i32 = layoutConstraint.maxWidth;
        event.componentAsyncEvent.data[NUM_2].i32 = layoutConstraint.minHeight;
        event.componentAsyncEvent.data[NUM_3].i32 = layoutConstraint.maxHeight;
        event.componentAsyncEvent.data[NUM_4].i32 = layoutConstraint.parentIdealWidth;
        event.componentAsyncEvent.data[NUM_5].i32 = layoutConstraint.parentIdealHeight;
        SendArkUIAsyncCustomEvent(&event);
    } else {
        // call origin measure.
        InnerMeasure(layoutConstraint);
    }
}

void ExtensionCompanionNode::OnLayout(int32_t width, int32_t height, int32_t positionX, int32_t positionY)
{
    if (flags_ & ArkUIAPINodeFlags::CUSTOM_LAYOUT) {
        ArkUICustomNodeEvent event;
        event.kind = ArkUIAPINodeFlags::CUSTOM_LAYOUT;
        event.extraParam = GetExtraParam(static_cast<ArkUI_Int32>(ArkUIAPINodeFlags::CUSTOM_LAYOUT));
        event.componentAsyncEvent.data[NUM_0].i32 = positionX;
        event.componentAsyncEvent.data[NUM_1].i32 = positionY;
        event.componentAsyncEvent.data[NUM_2].i32 = width;
        event.componentAsyncEvent.data[NUM_3].i32 = height;
        SendArkUIAsyncCustomEvent(&event);
    } else {
        InnerLayout(width, height, positionX, positionY);
    }
}

void ExtensionCompanionNode::OnDraw(DrawingContext& context)
{
    if (flags_ & ArkUIAPINodeFlags::CUSTOM_DRAW) {
        // call extension logic to manager side.
        auto canvas = reinterpret_cast<uintptr_t>(&context.canvas);
        ArkUICustomNodeEvent event;
        event.kind = ArkUIAPINodeFlags::CUSTOM_DRAW;
        event.extraParam = GetExtraParam(static_cast<ArkUI_Int32>(ArkUIAPINodeFlags::CUSTOM_DRAW));
        event.componentAsyncEvent.data[NUM_0].i32 = (ArkUI_Int32)(canvas & 0xffffffff);
        event.componentAsyncEvent.data[NUM_1].i32 =
            (ArkUI_Int32)((static_cast<uint64_t>(canvas) >> NUM_32) & 0xffffffff);
        event.componentAsyncEvent.data[NUM_2].i32 = context.width;
        event.componentAsyncEvent.data[NUM_3].i32 = context.height;
        event.canvas = &context.canvas;
        SendArkUIAsyncCustomEvent(&event);
    } else {
        InnerDraw(context);
    }
}

void ExtensionCompanionNode::OnForegroundDraw(DrawingContext& context)
{
    if (flags_ & ArkUIAPINodeFlags::CUSTOM_FOREGROUND_DRAW) {
        // call extension logic to manager side.
        auto canvas = reinterpret_cast<uintptr_t>(&context.canvas);
        ArkUICustomNodeEvent event;
        event.kind = ArkUIAPINodeFlags::CUSTOM_FOREGROUND_DRAW;
        event.extraParam = GetExtraParam(static_cast<ArkUI_Int32>(ArkUIAPINodeFlags::CUSTOM_FOREGROUND_DRAW));
        event.componentAsyncEvent.data[NUM_0].i32 = (ArkUI_Int32)(canvas & 0xffffffff);
        event.componentAsyncEvent.data[NUM_1].i32 =
            (ArkUI_Int32)((static_cast<uint64_t>(canvas) >> NUM_32) & 0xffffffff);
        event.componentAsyncEvent.data[NUM_2].i32 = context.width;
        event.componentAsyncEvent.data[NUM_3].i32 = context.height;
        event.canvas = &context.canvas;
        SendArkUIAsyncCustomEvent(&event);
    } else {
        InnerForegroundDraw(context);
    }
}

void ExtensionCompanionNode::OnOverlayDraw(DrawingContext& context)
{
    if (flags_ & ArkUIAPINodeFlags::CUSTOM_OVERLAY_DRAW) {
        // call extension logic to manager side.
        auto canvas = reinterpret_cast<uintptr_t>(&context.canvas);
        ArkUICustomNodeEvent event;
        event.kind = ArkUIAPINodeFlags::CUSTOM_OVERLAY_DRAW;
        event.extraParam = GetExtraParam(static_cast<ArkUI_Int32>(ArkUIAPINodeFlags::CUSTOM_OVERLAY_DRAW));
        event.componentAsyncEvent.data[NUM_0].i32 = (ArkUI_Int32)(canvas & 0xffffffff);
        event.componentAsyncEvent.data[NUM_1].i32 =
            (ArkUI_Int32)((static_cast<uint64_t>(canvas) >> NUM_32) & 0xffffffff);
        event.componentAsyncEvent.data[NUM_2].i32 = context.width;
        event.componentAsyncEvent.data[NUM_3].i32 = context.height;
        event.canvas = &context.canvas;
        SendArkUIAsyncCustomEvent(&event);
    } else {
        InnerOverlayDraw(context);
    }
}
} // namespace OHOS::Ace::NG