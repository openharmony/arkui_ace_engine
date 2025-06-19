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
    ArkUIAPINodeFlags::CUSTOM_DRAW, ArkUIAPINodeFlags::CUSTOM_FOREGROUND_DRAW, ArkUIAPINodeFlags::CUSTOM_OVERLAY_DRAW,
    ArkUIAPINodeFlags::CUSTOM_DRAW_FRONT, ArkUIAPINodeFlags::CUSTOM_DRAW_BEHIND };

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
        if (static_cast<uint32_t>(type) & flag) {
            auto it = extraParamMap_.find(flag);
            if (it != extraParamMap_.end()) {
                it->second = extraParam;
            } else {
                extraParamMap_.emplace(flag, extraParam);
            }
        }
    }
}

ArkUI_Int64 ExtensionCompanionNode::GetExtraParam(ArkUI_Int32 type)
{
    auto it = extraParamMap_.find(type);
    if (it != extraParamMap_.end()) {
        return reinterpret_cast<ArkUI_Int64>(it->second);
    }
    return reinterpret_cast<ArkUI_Int64>(nullptr);
}

void ExtensionCompanionNode::EraseExtraParam(ArkUI_Int32 type)
{
    for (const auto& flag : NODE_FLAGS) {
        if (static_cast<uint32_t>(type) & flag) {
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
        event.data[NUM_0] = layoutConstraint.minWidth;
        event.data[NUM_1] = layoutConstraint.minHeight;
        event.data[NUM_2] = layoutConstraint.maxWidth;
        event.data[NUM_3] = layoutConstraint.maxHeight;
        event.data[NUM_4] = layoutConstraint.parentIdealWidth;
        event.data[NUM_5] = layoutConstraint.parentIdealHeight;
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
        event.data[NUM_0] = positionX;
        event.data[NUM_1] = positionY;
        event.data[NUM_2] = width;
        event.data[NUM_3] = height;
        SendArkUIAsyncCustomEvent(&event);
    } else {
        InnerLayout(width, height, positionX, positionY);
    }
}

void ExtensionCompanionNode::OnDraw(DrawingContext& context)
{
    if (flags_ & ArkUIAPINodeFlags::CUSTOM_DRAW_BEHIND) {
        auto canvas = reinterpret_cast<uintptr_t>(&context.canvas);
        ArkUICustomNodeEvent eventDrawBehind;
        eventDrawBehind.kind = ArkUIAPINodeFlags::CUSTOM_DRAW_BEHIND;
        eventDrawBehind.extraParam = GetExtraParam(static_cast<ArkUI_Int32>(ArkUIAPINodeFlags::CUSTOM_DRAW_BEHIND));
        eventDrawBehind.data[NUM_0] = (ArkUI_Int32)(canvas & 0xffffffff);
        eventDrawBehind.data[NUM_1] = (ArkUI_Int32)((static_cast<uint64_t>(canvas) >> NUM_32) & 0xffffffff);
        eventDrawBehind.data[NUM_2] = context.width;
        eventDrawBehind.data[NUM_3] = context.height;
        eventDrawBehind.canvas = reinterpret_cast<intptr_t>(&context.canvas);
        SendArkUIAsyncCustomEvent(&eventDrawBehind);
    }

    if (flags_ & ArkUIAPINodeFlags::CUSTOM_DRAW) {
        // call extension logic to manager side.
        auto canvas = reinterpret_cast<uintptr_t>(&context.canvas);
        ArkUICustomNodeEvent event;
        event.kind = ArkUIAPINodeFlags::CUSTOM_DRAW;
        event.extraParam = GetExtraParam(static_cast<ArkUI_Int32>(ArkUIAPINodeFlags::CUSTOM_DRAW));
        event.data[NUM_0] = (ArkUI_Int32)(canvas & 0xffffffff);
        event.data[NUM_1] =
            (ArkUI_Int32)((static_cast<uint64_t>(canvas) >> NUM_32) & 0xffffffff);
        event.data[NUM_2] = context.width;
        event.data[NUM_3] = context.height;
        event.canvas = reinterpret_cast<intptr_t>(&context.canvas);
        SendArkUIAsyncCustomEvent(&event);
    } else {
        InnerDraw(context);
    }

    if (flags_ & ArkUIAPINodeFlags::CUSTOM_DRAW_FRONT) {
        auto canvas = reinterpret_cast<uintptr_t>(&context.canvas);
        ArkUICustomNodeEvent eventDrawFront;
        eventDrawFront.kind = ArkUIAPINodeFlags::CUSTOM_DRAW_FRONT;
        eventDrawFront.extraParam = GetExtraParam(static_cast<ArkUI_Int32>(ArkUIAPINodeFlags::CUSTOM_DRAW_FRONT));
        eventDrawFront.data[NUM_0] = (ArkUI_Int32)(canvas & 0xffffffff);
        eventDrawFront.data[NUM_1] = (ArkUI_Int32)((static_cast<uint64_t>(canvas) >> NUM_32) & 0xffffffff);
        eventDrawFront.data[NUM_2] = context.width;
        eventDrawFront.data[NUM_3] = context.height;
        eventDrawFront.canvas = reinterpret_cast<intptr_t>(&context.canvas);
        SendArkUIAsyncCustomEvent(&eventDrawFront);
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
        event.data[NUM_0] = (ArkUI_Int32)(canvas & 0xffffffff);
        event.data[NUM_1] =
            (ArkUI_Int32)((static_cast<uint64_t>(canvas) >> NUM_32) & 0xffffffff);
        event.data[NUM_2] = context.width;
        event.data[NUM_3] = context.height;
        event.canvas = reinterpret_cast<intptr_t>(&context.canvas);
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
        event.data[NUM_0] = (ArkUI_Int32)(canvas & 0xffffffff);
        event.data[NUM_1] =
            (ArkUI_Int32)((static_cast<uint64_t>(canvas) >> NUM_32) & 0xffffffff);
        event.data[NUM_2] = context.width;
        event.data[NUM_3] = context.height;
        event.canvas = reinterpret_cast<intptr_t>(&context.canvas);
        SendArkUIAsyncCustomEvent(&event);
    } else {
        InnerOverlayDraw(context);
    }
}

bool ExtensionCompanionNode::HasCustomerMeasure() const
{
    return (flags_ & ArkUIAPINodeFlags::CUSTOM_MEASURE) != 0;
}

bool ExtensionCompanionNode::HasCustomerLayout() const
{
    return (flags_ & ArkUIAPINodeFlags::CUSTOM_LAYOUT) != 0;
}

bool ExtensionCompanionNode::NeedRender() const
{
    ArkUI_Uint32 mask = ArkUIAPINodeFlags::CUSTOM_OVERLAY_DRAW | ArkUIAPINodeFlags::CUSTOM_FOREGROUND_DRAW |
                        ArkUIAPINodeFlags::CUSTOM_DRAW | ArkUIAPINodeFlags::CUSTOM_DRAW_FRONT |
                        ArkUIAPINodeFlags::CUSTOM_DRAW_BEHIND;
    return (flags_ & mask) != 0;
}
} // namespace OHOS::Ace::NG