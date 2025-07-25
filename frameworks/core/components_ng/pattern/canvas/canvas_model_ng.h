/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_MODEL_NG_H

#include "core/components_ng/pattern/canvas/canvas_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CanvasModelNG : public OHOS::Ace::CanvasModel {
public:
    RefPtr<AceType> Create() override;
    RefPtr<AceType> GetTaskPool(RefPtr<AceType>& pattern) override;
    void SetOnReady(std::function<void()>&& onReady) override;
    void EnableAnalyzer(bool enable) override;
    void SetImageAIOptions(void* options) override;
    void DetachRenderContext() override;
    static void SetOnReady(FrameNode* frameNode, std::function<void()>&& onReady);
    static void EnableAnalyzer(FrameNode* frameNode, bool enable);
    static RefPtr<AceType> GetCanvasPattern(FrameNode* frameNode);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void DetachRenderContext(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_MODEL_NG_H
