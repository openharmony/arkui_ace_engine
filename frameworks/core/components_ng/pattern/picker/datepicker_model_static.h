/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_MODEL_STATIC_H

#include "core/components_ng/pattern/picker/picker_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DatePickerModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetOnChange(FrameNode* frameNode, DateChangeEvent&& onChange);
    static void SetChangeEvent(FrameNode* frameNode, DateChangeEvent&& onChange);
    static void SetSelectedDate(FrameNode* frameNode, const int64_t& value);
private:
    static RefPtr<FrameNode> CreateStackNode();
    static RefPtr<FrameNode> CreateColumnNode();
    static RefPtr<FrameNode> CreateButtonNode();
    static void CreateDateColumn(const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& dateNode);
    static void SetupDateOrder(const RefPtr<FrameNode>& dateNode, const std::string& dateOrder,
        const RefPtr<FrameNode>& yearColumnNode, const RefPtr<FrameNode>& monthColumnNode,
        const RefPtr<FrameNode>& dayColumnNode, bool hasYearNode, bool hasMonthNode, bool hasDayNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_MODEL_STATIC_H
 