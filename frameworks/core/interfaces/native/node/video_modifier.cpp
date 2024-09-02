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
#include "core/interfaces/native/node/video_modifier.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/video/video_model_ng.h"

namespace OHOS::Ace::NG {
constexpr ArkUI_Bool DEFAULT_CONTROLS_VALUE = true;
constexpr ArkUI_Bool DEFAULT_LOOP = false;
constexpr ArkUI_Bool DEFAULT_MUTED = false;
constexpr ImageFit DEFAULT_OBJECT_FIT = ImageFit::COVER;

void SetAutoPlay(ArkUINodeHandle node, ArkUI_Uint32 autoPlay)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetAutoPlay(frameNode, static_cast<ArkUI_Bool>(autoPlay));
}

void ResetAutoPlay(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetAutoPlay(frameNode, false);
}

void SetVideoObjectFit(ArkUINodeHandle node, ArkUI_Int32 objectFit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetObjectFit(frameNode, static_cast<ImageFit>(objectFit));
}

void ResetVideoObjectFit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetObjectFit(frameNode, DEFAULT_OBJECT_FIT);
}

void SetVideoControls(ArkUINodeHandle node, ArkUI_Uint32 controlsValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetControls(frameNode, static_cast<ArkUI_Bool>(controlsValue));
}

void ResetVideoControls(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetControls(frameNode, DEFAULT_CONTROLS_VALUE);
}

void SetVideoLoop(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetLoop(frameNode, static_cast<ArkUI_Bool>(value));
}

void ResetVideoLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetLoop(frameNode, DEFAULT_LOOP);
}

void SetVideoMuted(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetMuted(frameNode, static_cast<ArkUI_Bool>(value));
}

void ResetVideoMuted(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetMuted(frameNode, DEFAULT_MUTED);
}

void SetVideoOpacity(ArkUINodeHandle node, ArkUI_Float32 opacity)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if ((LessNotEqual(opacity, 0.0)) || opacity > 1) {
        opacity = 1.0f;
    }
    ViewAbstract::SetOpacity(frameNode, opacity);
}

void ResetVideoOpacity(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOpacity(frameNode, 1.0f);
}

namespace NodeModifier {
const ArkUIVideoModifier* GetVideoModifier()
{
    static const ArkUIVideoModifier modifier = {
        SetAutoPlay,
        ResetAutoPlay,
        SetVideoObjectFit,
        ResetVideoObjectFit,
        SetVideoControls,
        ResetVideoControls,
        SetVideoLoop,
        ResetVideoLoop,
        SetVideoMuted,
        ResetVideoMuted,
        SetVideoOpacity,
        ResetVideoOpacity
    };

    return &modifier;
}

const CJUIVideoModifier* GetCJUIVideoModifier()
{
    static const CJUIVideoModifier modifier = {
        SetAutoPlay,
        ResetAutoPlay,
        SetVideoObjectFit,
        ResetVideoObjectFit,
        SetVideoControls,
        ResetVideoControls,
        SetVideoLoop,
        ResetVideoLoop,
        SetVideoMuted,
        ResetVideoMuted,
        SetVideoOpacity,
        ResetVideoOpacity
    };

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG