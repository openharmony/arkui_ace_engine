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

#include "interfaces/inner_api/ace_kit/src/view/extend_pattern.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::Kit {

ExtendPattern::ExtendPattern(const RefPtr<Kit::Pattern>& kitPattern) : kitPattern_(kitPattern) {}

bool ExtendPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<NG::LayoutWrapper>& dirty, const NG::DirtySwapConfig& changeConfig)
{
    if (kitPattern_) {
        return kitPattern_->OnDirtyLayoutrSwap(changeConfig);
    }
    return false;
}

void ExtendPattern::OnModifyDone()
{
    NG::Pattern::OnModifyDone();
    if (kitPattern_) {
        kitPattern_->OnModifyDone();
    }
}

} // namespace OHOS::Ace::Kit
