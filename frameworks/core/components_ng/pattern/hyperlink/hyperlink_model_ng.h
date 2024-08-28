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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HYPERLINK_HYPERLINK_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HYPERLINK_HYPERLINK_MODEL_NG_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT HyperlinkModelNG : public HyperlinkModel {
public:
    void Create(const std::string& address, const std::string& content) override;
    void Pop() override {};
    void SetColor(const Color& value) override;
    void SetDraggable(bool draggable) override;
    void SetResponseRegion(bool isUserSetResponseRegion) override;
    static void SetColor(FrameNode* frameNode, const Color& value);
    static void SetDraggable(FrameNode* frameNode, bool draggable);
    static void SetResponseRegion(
        FrameNode* frameNode, const std::vector<DimensionRect>& regions, bool isUserSetResponseRegion);

private:
    void SetTextStyle(const RefPtr<FrameNode>& textNode, const std::string& content, const std::string& address);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HYPERLINK_HYPERLINK_MODEL_NG_H
