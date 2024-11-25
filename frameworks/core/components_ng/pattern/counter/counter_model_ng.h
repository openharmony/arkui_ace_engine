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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_MODEL_NG_H

#include "core/components_ng/pattern/counter/counter_model.h"
#include "core/components/counter/counter_theme.h"
#include "core/components_ng/pattern/counter/counter_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CounterModelNG : public CounterModel {
public:
    void Create() override;
    void SetOnInc(CounterEventFunc&& onInc) override;
    void SetOnDec(CounterEventFunc&& onDec) override;
    void SetHeight(const Dimension& value) override;
    void SetWidth(const Dimension& value) override;
    void SetControlWidth(const Dimension& value) override;
    void SetStateChange(bool value) override;
    void SetBackgroundColor(const Color& value) override;
    void SetEnableDec(bool enableDec) override;
    void SetEnableInc(bool enableInc) override;
    static void SetEnableDec(FrameNode* frameNode, bool enableDec);
    static void SetEnableInc(FrameNode* frameNode, bool enableInc);
    static void SetHeight(FrameNode* frameNode, const Dimension& value);
    static void SetWidth(FrameNode* frameNode, const Dimension& value);
    static void SetBackgroundColor(FrameNode* frameNode, const Color& value);

private:
    RefPtr<FrameNode> CreateButtonChild(
        int32_t id, const std::u16string& symbol, const RefPtr<CounterTheme>& counterTheme);
    static RefPtr<FrameNode> CreateContentNodeChild(int32_t contentId, const RefPtr<CounterTheme>& counterTheme);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_MODEL_NG_H
