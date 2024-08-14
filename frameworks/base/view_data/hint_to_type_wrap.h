/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_HINT_TO_TYPE_WRAP_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_HINT_TO_TYPE_WRAP_H

#include "base/view_data/ace_auto_fill_type.h"

namespace OHOS::Ace {
struct HintToTypeWrap {
    AceAutoFillType autoFillType = AceAutoFillType::ACE_UNSPECIFIED;
    std::string metadata = "";
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_HINT_TO_TYPE_WRAP_H
