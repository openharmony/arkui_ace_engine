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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_MODEL_H

#include <functional>
#include <string>

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_ng/pattern/text_field/text_selector.h"

namespace OHOS::Ace {

class Color;

namespace NG {
enum class SelectionContainerTextJoinStyle {
    NEWLINE = 0,
    DIRECT = 1,
};
}

class ACE_EXPORT SelectionContainerModel {
public:
    virtual ~SelectionContainerModel() = default;
    virtual void SetCopyOption(CopyOptions copyOption) = 0;
    virtual void SetEnableHapticFeedback(bool isEnabled) = 0;
    virtual void SetTextJoinStyle(NG::SelectionContainerTextJoinStyle style) = 0;
    virtual void SetCaretColor(const Color& caretColor) = 0;
    virtual void SetSelectedBackgroundColor(const Color& selectedBackgroundColor) = 0;
    virtual void ResetCopyOption() = 0;
    virtual void ResetEnableHapticFeedback() = 0;
    virtual void ResetTextJoinStyle() = 0;
    virtual void ResetCaretColor() = 0;
    virtual void ResetSelectedBackgroundColor() = 0;
    virtual void SetOnWillCopy(std::function<bool(const std::u16string&)>&& func) = 0;
    virtual void SetOnCopy(std::function<void(const std::u16string&)>&& func) = 0;
    virtual void SetOnTextSelectionChange(
        std::function<void(const std::vector<std::u16string>&)>&& func) = 0;
    virtual void SetSelectionMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick,
        const NG::OnPrepareMenuCallback&& onPrepareMenuCallback) = 0;
    virtual void SetSelectionMenuItemClickWithTextCallback(
        std::function<bool(const NG::MenuItemParam&, const std::u16string&)>&& func) = 0;
    virtual void BindSelectionMenu(NG::TextSpanType spanType, NG::TextResponseType responseType,
        std::function<void()>& menuBuilder, const NG::SelectMenuParam& menuParam) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_MODEL_H
