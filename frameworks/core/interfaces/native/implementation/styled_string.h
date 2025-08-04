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

#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
    template<>
    void AssignCast(std::optional<Ace::SpanType>& dst, const Ark_StyledStringKey& src);

    template<>
    RefPtr<SpanBase> Convert(const Ark_StyleOptions& src);

    template<>
    inline RefPtr<SpanBase> Convert(const Ark_SpanStyle& src)
    {
        return Convert<RefPtr<SpanBase>>(Ark_StyleOptions {
            .start = ArkValue<Opt_Number>(src.start),
            .length = ArkValue<Opt_Number>(src.length),
            .styledKey = src.styledKey,
            .styledValue = src.styledValue,
        });
    }
}
