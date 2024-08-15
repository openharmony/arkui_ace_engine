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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_MODAL_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_MODAL_STYLE_H

#include <optional>

#include "core/components/common/properties/color.h"

namespace OHOS::Ace::NG {
enum ModalTransition {
    DEFAULT,
    NONE,
    ALPHA,
};

struct ModalStyle {
    std::optional<ModalTransition> modalTransition;
    std::optional<Color> backgroundColor;
    bool isUIExtension = false;
    bool prohibitedRemoveByRouter = false;

    bool operator==(const ModalStyle& modelStyle) const
    {
        return !(modalTransition != modelStyle.modalTransition || backgroundColor != modelStyle.backgroundColor ||
            isUIExtension != modelStyle.isUIExtension ||
            prohibitedRemoveByRouter != modelStyle.prohibitedRemoveByRouter);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_STYLE_H
