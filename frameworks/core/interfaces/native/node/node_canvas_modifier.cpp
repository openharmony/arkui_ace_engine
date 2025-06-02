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
#include "core/interfaces/native/node/node_canvas_modifier.h"

#include "core/components_ng/pattern/canvas/canvas_model_ng.h"

namespace OHOS::Ace::NG::NodeModifier {

void SetCanvasOnReady(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onReady = reinterpret_cast<std::function<void()>*>(callback);
        CanvasModelNG::SetOnReady(frameNode, std::move(*onReady));
    } else {
        CanvasModelNG::SetOnReady(frameNode, nullptr);
    }
}

void ResetCanvasOnReady(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::SetOnReady(frameNode, nullptr);
}

void SetCanvasEnableAnalyzer(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::EnableAnalyzer(frameNode, static_cast<bool>(value));
}

void ResetCanvasEnableAnalyzer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CanvasModelNG::EnableAnalyzer(frameNode, false);
}

const ArkUICanvasModifier* GetCanvasModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUICanvasModifier modifier = {
        .setCanvasOnReady = SetCanvasOnReady,
        .resetCanvasOnReady = ResetCanvasOnReady,
        .setCanvasEnableAnalyzer = SetCanvasEnableAnalyzer,
        .resetCanvasEnableAnalyzer = ResetCanvasEnableAnalyzer,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace OHOS::Ace::NG::NodeModifier
