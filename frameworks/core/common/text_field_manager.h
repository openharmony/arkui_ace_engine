/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEXT_FIELD_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEXT_FIELD_MANAGER_H

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/common/manager_interface.h"
#include "core/components/stack/stack_element.h"
#include "core/components/text_field/render_text_field.h"

namespace OHOS::Ace {

class ACE_EXPORT TextFieldManager : public ManagerInterface {
    DECLARE_ACE_TYPE(TextFieldManager, ManagerInterface);

public:
    TextFieldManager() = default;
    ~TextFieldManager() override = default;

    void SetClickPosition(const Offset& position) override;
    const Offset& GetClickPosition() override;
    void MovePage(int32_t pageId, const Offset& rootRect, double offsetHeight) override;
    void SetScrollElement(int32_t pageId, const WeakPtr<ScrollElement>& scrollElement) override;
    void RemovePageId(int32_t pageId) override;

    WeakPtr<RenderTextField>& GetOnFocusTextField()
    {
        return onFocusTextField_;
    }

    void SetOnFocusTextField(const WeakPtr<RenderTextField>& onFocusTextField)
    {
        onFocusTextField_ = onFocusTextField;
    }

    void ClearOnFocusTextField();

    bool ResetSlidingPanelParentHeight();

    bool UpdatePanelForVirtualKeyboard(double offsetY, double fullHeight);
    void SetHeight(float height);

    float GetHeight() const;

private:
    bool hasMove_ = false;
    Offset position_;
    float height_ = 0.0f;
    std::unordered_map<int32_t, WeakPtr<ScrollElement>> scrollMap_;
    WeakPtr<RenderTextField> onFocusTextField_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_TEXT_FIELD_MANAGER_H
