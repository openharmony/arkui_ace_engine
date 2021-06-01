/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEXT_FIELD_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEXT_FIELD_MANAGER_H

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components/stack/stack_element.h"

namespace OHOS::Ace {

class ACE_EXPORT PageScroller : public AceType {
    DECLARE_ACE_TYPE(PageScroller, AceType);

public:
    PageScroller() = default;
    ~PageScroller() override = default;

    void SetClickPosition(const Offset& position);
    void MovePage(const RefPtr<StackElement>& stackElement, const Offset& rootRect, double offsetHeight);

private:
    bool hasMove_ = false;
    Offset position_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEXT_FIELD_MANAGER_H
