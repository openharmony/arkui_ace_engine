/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_NAPI_ACE_COMPONENT_TEST_COMBINATION_ISSCROLLABLE_H
#define OHOS_NAPI_ACE_COMPONENT_TEST_COMBINATION_ISSCROLLABLE_H

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace {
class CombinationIsScrollable {
private:
    RefPtr<NG::FrameNode> frameNode_;
    RefPtr<NG::Pattern> pattern_;
    bool isSwiper_ = false;
    bool isSteper_ = false;
    bool isTabBar_ = false;

public:
    explicit CombinationIsScrollable(const RefPtr<NG::FrameNode> frameNode);
    ~CombinationIsScrollable() = default;
    bool IsComponentExist();
    bool IsComponentScrollable() const;
};
} // namespace OHOS::Ace
#endif // OHOS_NAPI_ACE_COMPONENT_TEST_COMBINATION_ISSCROLLABLE_H