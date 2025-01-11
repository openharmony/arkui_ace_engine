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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_EXTEND_PATTERN_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_EXTEND_PATTERN_H

#include "ui/view/pattern.h"

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::Kit {

class ExtendPattern : public NG::Pattern {
    DECLARE_ACE_TYPE(ExtendPattern, NG::Pattern);

public:
    ExtendPattern(const RefPtr<Kit::Pattern>& kitPattern);
    ~ExtendPattern() override = default;

    virtual bool OnDirtyLayoutWrapperSwap(
        const RefPtr<NG::LayoutWrapper>& dirty, const NG::DirtySwapConfig& changeConfig) override;

private:
    RefPtr<Kit::Pattern> kitPattern_;
};
} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_EXTEND_PATTERN_H
