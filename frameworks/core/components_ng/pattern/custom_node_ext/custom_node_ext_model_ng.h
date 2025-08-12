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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_MODEL_NG_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_pattern.h"

namespace OHOS::Ace::NG {

class CustomNodeExtModelNG {
public:
    static RefPtr<FrameNode> GetOrCreateFrameNode(const std::string& tag);
    static RefPtr<FrameNode> CreateFrameNode(const std::string& tag);
    static RefPtr<FrameNode> CreateFrameNode(const std::string& tag, int32_t nodeId);

    static void SetMeasureCallback(
        FrameNode* frameNode, std::function<void(LayoutConstraintF constraints)>&& onMeasure);
    static void SetLayoutCallback(FrameNode* frameNode, std::function<void(RectF rect)>&& onLayout);
    static void SetContentDrawCallback(FrameNode* frameNode, DrawFunction&& onDraw);
    static void SetForegroundDrawCallback(FrameNode* frameNode, DrawFunction&& onDraw);
    static void SetOverlayDrawCallback(FrameNode* frameNode, DrawFunction&& onDraw);

    static void SetOnConfigUpdateCallback(
        FrameNode* frameNode, std::function<void(ConfigurationType configType)>&& onConfigUpdate);
    static void SetOnModifyDoneCallback(FrameNode* frameNode, std::function<void()>&& onModifyDone);
    static void SetOnWindowFocusedCallback(FrameNode* frameNode, std::function<void()>&& onWindowFocused);
    static void SetOnWindowUnfocusedCallback(FrameNode* frameNode, std::function<void()>&& onWindowUnfocused);
    static void SetOnWindowActivatedCallback(FrameNode* frameNode, std::function<void()>&& onWindowActivated);
    static void SetOnWindowDeactivatedCallback(FrameNode* frameNode, std::function<void()>&& onWindowDeactivated);
    static void SetOnAttachToMainTreeCallback(FrameNode* frameNode, std::function<void()>&& onAttachToMainTree);
    static void SetOnDetachFromMainTreeCallback(FrameNode* frameNode, std::function<void()>&& onDetachFromMainTree);
    static void SetOnAvoidInfoChangeCallback(FrameNode* frameNode, std::function<void()>&& onAvoidInfoChange);
    static void SetIsNeedRegisterAvoidInfoChangeListener(FrameNode* frameNode, bool isRegister);
    static void SetOnDirtyLayoutWrapperSwap(
        FrameNode* frameNode, std::function<void(const DirtySwapConfig& config)>&& onDirtySwap);

    static void SetIsAtomic(FrameNode* frameNode, bool isAtomic);
    static void SetBeforeCreateLayoutWrapperCallback(
        FrameNode* frameNode, std::function<void()>&& beforeCreateLayoutWrapper);
};
}
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_MODEL_NG_H