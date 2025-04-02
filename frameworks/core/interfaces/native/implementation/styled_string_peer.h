/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_string.h"

struct StyledStringPeer {
    virtual ~StyledStringPeer() = default;

    static StyledStringPeer *Create(const OHOS::Ace::RefPtr<OHOS::Ace::SpanStringBase>& src = nullptr)
    {
        auto ret = new StyledStringPeer;
        ret->spanString = OHOS::Ace::AceType::DynamicCast<OHOS::Ace::SpanString>(src);
        return ret;
    }

    static void Destroy(StyledStringPeer *peer)
    {
        delete peer;
    }

    OHOS::Ace::RefPtr<OHOS::Ace::MutableSpanString> GetMutableString()
    {
        return OHOS::Ace::AceType::DynamicCast<OHOS::Ace::MutableSpanString>(spanString);
    }

    OHOS::Ace::RefPtr<OHOS::Ace::SpanString> spanString;
};
