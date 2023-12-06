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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_ACE_AUTO_FILL_TYPE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_ACE_AUTO_FILL_TYPE_H

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
enum class AceAutoFillType {
    ACE_UNSPECIFIED = 0,
    ACE_PASSWORD,
    ACE_USER_NAME,
    ACE_NEW_PASSWORD
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_ACE_AUTO_FILL_TYPE_H