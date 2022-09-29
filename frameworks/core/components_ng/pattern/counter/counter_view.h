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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_VIEW_H

#include <functional>

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/counter/counter_theme.h"
#include "core/components_ng/pattern/counter/counter_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CounterView {
public:
    using CounterEventFunc = std::function<void()>;

    static void Create();
    static void SetOnInc(CounterEventFunc&& onInc);
    static void SetOnDec(CounterEventFunc&& onDec);

private:
    static RefPtr<FrameNode> CreateButtonChild(
        int32_t id, const std::string& symbol, const RefPtr<CounterTheme>& counterTheme);
    static RefPtr<FrameNode> CreateContentNodeChild(int32_t contentId, const RefPtr<CounterTheme>& counterTheme);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_VIEW_H