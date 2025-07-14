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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_MODEL_NG_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/divider/divider_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DividerModelNG : public DividerModel {
public:
    void Create() override;
    void Vertical(bool value) override;
    void DividerColor(const Color& value) override;
    void DividerColor(const RefPtr<ResourceObject>& resobj) override;
    void StrokeWidth(const Dimension& value) override;
    void LineCap(const enum LineCap& value) override;
    void ResetDividerColor() override;
    void ResetResObj(const std::string& key) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void StrokeWidth(FrameNode* frameNode, std::optional<Dimension> valueOpt);
    static void LineCap(FrameNode* frameNode, std::optional<enum LineCap> valueOpt);
    static void SetDividerColor(FrameNode* frameNode, std::optional<Color> colorOpt, bool isSetByUser);
    static void SetDividerColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, bool isSetByUser);
    static void SetVertical(FrameNode* frameNode, const bool& value);
    static void ResetDividerColor(FrameNode* frameNode);
    static void ResetResObj(FrameNode* frameNode, const std::string& key);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_MODEL_NG_H