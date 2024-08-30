/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <optional>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"

#include "reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
// Reverse-convert Ark_TextDeleteDirection
void AssignArkValue(Ark_TextDeleteDirection& dst, const TextDeleteDirection& src)
{
    switch (src) {
        case TextDeleteDirection::BACKWARD: dst = ARK_TEXT_DELETE_DIRECTION_BACKWARD; break;
        case TextDeleteDirection::FORWARD: dst = ARK_TEXT_DELETE_DIRECTION_FORWARD; break;
        default: dst = static_cast<Ark_TextDeleteDirection>(-1);
    }
}

void AssignArkValue(Ark_EnterKeyType& dst, const TextInputAction& src)
{
    switch (src) {
        case TextInputAction::GO: dst = ARK_ENTER_KEY_TYPE_GO; break;
        case TextInputAction::SEARCH: dst = ARK_ENTER_KEY_TYPE_SEARCH; break;
        case TextInputAction::SEND: dst = ARK_ENTER_KEY_TYPE_SEND; break;
        case TextInputAction::NEXT: dst = ARK_ENTER_KEY_TYPE_NEXT; break;
        case TextInputAction::DONE: dst = ARK_ENTER_KEY_TYPE_DONE; break;
        case TextInputAction::PREVIOUS: dst = ARK_ENTER_KEY_TYPE_PREVIOUS; break;
        case TextInputAction::NEW_LINE: dst = ARK_ENTER_KEY_TYPE_NEW_LINE; break;
        default:
            LOGE("Unexpected enum value in TextInputAction: %{public}d", src);
            dst = static_cast<Ark_EnterKeyType>(-1);
    }
}
} // namespace OHOS::Ace::NG::Converter