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

#include "symbol_source_info.h"

namespace OHOS::Ace::NG {

SymbolSourceInfo::SymbolSourceInfo(std::uint32_t codeId)
{
    unicode = codeId;
}

bool SymbolSourceInfo::operator==(const SymbolSourceInfo& info) const
{
    return unicode == info.GetUnicode();
}

bool SymbolSourceInfo::operator!=(const SymbolSourceInfo& info) const
{
    return !(operator==(info));
}

} // namespace OHOS::Ace::NG
