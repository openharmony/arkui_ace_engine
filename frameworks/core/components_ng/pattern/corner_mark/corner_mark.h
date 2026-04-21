/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CORNER_MARK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CORNER_MARK_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class CornerMark : public virtual AceType {
    DECLARE_ACE_TYPE(CornerMark, AceType);

public:
    CornerMark() = default;
    ~CornerMark() override = default;
    int32_t ResponseShowCornerMarkEvent(const RefPtr<NG::FrameNode>& node, const std::string& command);
    static void UpdateCornerMarkNodeLanguage(const RefPtr<NG::FrameNode>& node);
    static void UpdateCornerMarkNodeColorMode(const RefPtr<NG::FrameNode>& node);
    static void UpdateCornerMarkNodePosition(const RefPtr<NG::FrameNode>& node);

private:
    int32_t AddCornerMarkNode(const RefPtr<NG::FrameNode>& node, const std::string& index);
    int32_t UpdateCornerMarkNode(const RefPtr<NG::FrameNode>& node, const std::string& index);
    int32_t RemoveCornerMarkNode(const RefPtr<NG::FrameNode>& node);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CORNER_MARK_H