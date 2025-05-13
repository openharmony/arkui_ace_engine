/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_AGINGADAPATION_AGING_ADAPATION_DIALOG_UTIL_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_AGINGADAPATION_AGING_ADAPATION_DIALOG_UTIL_H

#include <cstdint>
#include <string>

#include "ui/base/ace_type.h"
#include "ui/view/frame_node.h"

namespace OHOS::Ace::Kit {

enum class IconNodeType {
    SYMBOL = 0,
    IMAGE,
    TEXT
};

class ACE_FORCE_EXPORT AgingAdapationDialogUtil {
public:
    static RefPtr<FrameNode> ShowLongPressDialog(
        const std::string& message, const int32_t iconNodeId, const IconNodeType type);
    static float GetDialogBigFontSizeScale();
    static float GetDialogLargeFontSizeScale();
    static float GetDialogMaxFontSizeScale();
};
} // OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_AGINGADAPATION_AGING_ADAPATION_DIALOG_UTIL_H
