/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LOADING_PROGRESS_LOADING_PROGRESS_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LOADING_PROGRESS_LOADING_PROGRESS_MODEL_NG_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model.h"

namespace OHOS::Ace::NG {
class LoadingProgressConfiguration : public CommonConfiguration {
public:
    LoadingProgressConfiguration(bool enableloading, bool enabled)
        : CommonConfiguration(enabled), enableloading_(enableloading)
    {}
    bool enableloading_ = true;
};
using LoadingProgressMakeCallback =
    std::function<RefPtr<FrameNode>(const LoadingProgressConfiguration& loadingProgressConfiguration)>;
class  ACE_EXPORT LoadingProgressModelNG : public OHOS::Ace::LoadingProgressModel {
public:
    void Create() override;
    void SetColor(const Color& value) override;
    void SetEnableLoading(bool enable) override;
    void ResetColor() override;
    void SetForegroundColorParseFailed(bool isParseFailed) override;
    
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static uint32_t GetColor(FrameNode* frameNode);
    static void SetColor(FrameNode* frameNode, const Color& value);
    static bool GetEnableLoading(FrameNode* frameNode);
    static void SetEnableLoading(FrameNode* frameNode, bool enable);
    static void SetForegroundColor(FrameNode* frameNode, const Color& value);
    static void SetBuilderFunc(FrameNode* frameNode, NG::LoadingProgressMakeCallback&& jsMake);
    static void ResetColor(FrameNode* frameNode);
    static void ResetForegroundColor(FrameNode* frameNode);
    static void SetForegroundColorParseFailed(FrameNode* frameNode, bool isParseFailed);
    static void SetColorParseFailed(FrameNode* frameNode, bool isParseFailed);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LOADING_PROGRESS_LOADING_PROGRESS_MODEL_NG_H
