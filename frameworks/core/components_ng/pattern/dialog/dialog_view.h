/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_VIEW_H

#include <string>

#include "base/memory/referenced.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DialogView {
public:
    static RefPtr<FrameNode> CreateDialogNode(const DialogProperties& param, const RefPtr<UINode>& customNode);
    static RefPtr<FrameNode> CreateDialogNode(
        const int32_t nodeId, const DialogProperties& param, const RefPtr<UINode>& customNode);
private:
    static void SetDialogAccessibilityHoverConsume(const RefPtr<FrameNode>& dialog);
    static std::string GetDialogTag(const DialogProperties& param);
    static void CreateWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param);
    static void SetBackgroundColorWithResourceObj(const RefPtr<FrameNode>& node, const RefPtr<ResourceObject>& resObj);
    static void SetMaskColorWithResourceObj(const RefPtr<FrameNode>& frameNode, const RefPtr<ResourceObject>& resObj);
    static void SetWidthWithResourceObj(
        const RefPtr<FrameNode>& node, const RefPtr<ResourceObject>& resObj);
    static void SetHeightWithResourceObj(const RefPtr<FrameNode>& node, const RefPtr<ResourceObject>& resObj);
    static void SetOffsetWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param);
    static void SetShadowWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param);
    static void SetEffectWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param);
    static void SetBlurStyleWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param);
    static void SetMaskRectWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param);
    static void SetBorderWidthWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param);
    static void SetBorderColorWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param);
    static void SetCornerRadiusWithResourceObj(const RefPtr<FrameNode>& node, const DialogProperties& param);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_VIEW_H
