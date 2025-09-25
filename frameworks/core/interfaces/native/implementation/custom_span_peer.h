/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#pragma once

#include "custom_span_impl.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct CustomSpanPeer final {
    OHOS::Ace::RefPtr<OHOS::Ace::NG::CustomSpanImpl> span;

protected:
    explicit CustomSpanPeer(OHOS::Ace::RefPtr<OHOS::Ace::NG::CustomSpanImpl> spn = nullptr): span(spn) {};
    ~CustomSpanPeer()
    {
        span = nullptr;
    }
    friend OHOS::Ace::NG::PeerUtils;
};