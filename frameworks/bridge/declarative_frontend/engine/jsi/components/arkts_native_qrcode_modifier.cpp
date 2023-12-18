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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_qrcode_modifier.h"

#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"

namespace OHOS::Ace::NG {
constexpr uint32_t DEFAULT_COLOR = 0xff182431;
constexpr uint32_t DEFAULT_BG_COLOR = 0xffffffff;
constexpr double DEFAULT_OPACITY = 1.0;

void SetQRColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRCodeColor(frameNode, Color(color));
}

void ResetQRColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRCodeColor(frameNode, Color(DEFAULT_COLOR));
}

void SetQRBackgroundColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRBackgroundColor(frameNode, Color(color));
}

void ResetQRBackgroundColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRBackgroundColor(frameNode, Color(DEFAULT_BG_COLOR));
}

void SetContentOpacity(NodeHandle node, double opacity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // The minimum value of opacity is 0 and the maximum value is 1.
    if (LessNotEqual(opacity, 0.0) || GreatNotEqual(opacity, 1.0)) {
        QRCodeModelNG::SetContentOpacity(frameNode, DEFAULT_OPACITY);
    } else {
        QRCodeModelNG::SetContentOpacity(frameNode, opacity);
    }
}

void ResetContentOpacity(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetContentOpacity(frameNode, DEFAULT_OPACITY);
}


ArkUIQRCodeModifierAPI GetQRCodeModifier()
{
    static const ArkUIQRCodeModifierAPI modifier = { SetQRColor, ResetQRColor, SetQRBackgroundColor,
        ResetQRBackgroundColor, SetContentOpacity, ResetContentOpacity };

    return modifier;
}
}