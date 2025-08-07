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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BLANK_BLANK_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BLANK_BLANK_MODEL_NG_H

#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/blank/blank_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT BlankModelNG : public OHOS::Ace::BlankModel {
public:
    void Create() override;
    void SetBlankMin(const Dimension& blankMin) override;
    void SetHeight(const Dimension& height) override;
    void SetColor(const Color& color) override;
    void SetColor(const RefPtr<ResourceObject>& resobj) override;
    void ResetResObj(const std::string& key) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetColor(FrameNode* frameNode, const Color& color);
    static void SetColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resobj);
    static void SetHeight(FrameNode* frameNode, const Dimension& height);
    static void SetBlankMin(FrameNode* frameNode, const Dimension& blankMin);
    static void ResetResObj(FrameNode* frameNode, const std::string& key);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BLANK_BLANK_MODEL_NG_H
