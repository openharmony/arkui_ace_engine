/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#pragma once

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {

struct RawInputEventUnion {
    Ark_Int32 selector;
    union {
        Ark_MouseEvent value0;
        Ark_TouchEventProxy value1;
        Ark_KeyEvent value2;
    };
};

struct RawInputEventWrapperPeer {
    RawInputEventUnion event;
};

Ark_RawInputEventWrapper CreateRawInputEventWrapperPeer(const RawInputEventUnion* event);

} // namespace OHOS::Ace::NG::GeneratedModifier
