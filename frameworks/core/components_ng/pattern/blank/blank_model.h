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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BLANK_BLANK_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BLANK_BLANK_MODEL_H

#include <mutex>

#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT BlankModel {
public:
    static BlankModel* GetInstance();
    virtual ~BlankModel() = default;

    virtual void Create() = 0;
    virtual void SetBlankMin(const Dimension& blankMin) = 0;
    virtual void SetHeight(const Dimension& height) = 0;
    virtual void SetColor(const Color& color) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BLANK_BLANK_MODEL_H
