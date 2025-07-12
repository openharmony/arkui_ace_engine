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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_MODEL_STATIC_H

#include "core/components_ng/pattern/counter/counter_model.h"
#include "core/components/counter/counter_theme.h"
#include "core/components_ng/pattern/counter/counter_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CounterModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetHeight(FrameNode* frameNode, const CalcLength& height);
    static void SetWidth(FrameNode* frameNode, const CalcLength& width);
    static void SetBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetOnInc(FrameNode* frameNode, CounterModel::CounterEventFunc&& onInc);
    static void SetOnDec(FrameNode* frameNode, CounterModel::CounterEventFunc&& onDec);

private:
    static RefPtr<FrameNode> CreateButtonChild(
        int32_t id, const std::u16string& symbol, const RefPtr<CounterTheme>& counterTheme);
    static RefPtr<FrameNode> CreateContentNodeChild(int32_t contentId, const RefPtr<CounterTheme>& counterTheme);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_MODEL_STATIC_H
