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

#include <cstdint>

#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
constexpr bool DEFAULT_CONTROLS_VALUE = true;
constexpr bool DEFAULT_LOOP = false;
constexpr bool DEFAULT_MUTED = false;
constexpr ImageFit DEFAULT_OBJECT_FIT = ImageFit::COVER;

void SetAutoPlay(NodeHandle node, uint32_t autoPlay)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetAutoPlay(frameNode, static_cast<bool>(autoPlay));
}

void ResetAutoPlay(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetAutoPlay(frameNode, false);
}

void SetVideoObjectFit(NodeHandle node, int32_t objectFit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetObjectFit(frameNode, static_cast<ImageFit>(objectFit));
}

void ResetVideoObjectFit(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetObjectFit(frameNode, DEFAULT_OBJECT_FIT);
}

void SetVideoControls(NodeHandle node, uint32_t controlsValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetControls(frameNode, static_cast<bool>(controlsValue));
}

void ResetVideoControls(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetControls(frameNode, DEFAULT_CONTROLS_VALUE);
}

void SetVideoLoop(NodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetLoop(frameNode, static_cast<bool>(value));
}

void ResetVideoLoop(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetLoop(frameNode, DEFAULT_LOOP);
}

void SetVideoMuted(NodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetMuted(frameNode, static_cast<bool>(value));
}

void ResetVideoMuted(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetMuted(frameNode, DEFAULT_MUTED);
}

ArkUIVideoModifierAPI GetVideoModifier()
{
    static const ArkUIVideoModifierAPI modifier = { SetAutoPlay, ResetAutoPlay, SetVideoObjectFit, ResetVideoObjectFit,
        SetVideoControls, ResetVideoControls, SetVideoLoop, ResetVideoLoop, SetVideoMuted, ResetVideoMuted };

    return modifier;
}
} // namespace OHOS::Ace::NG