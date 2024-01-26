/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MANAGER_H

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/common/manager_interface.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/safe_area_insets.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextFieldManagerNG : public ManagerInterface {
    DECLARE_ACE_TYPE(TextFieldManagerNG, ManagerInterface);

public:
    TextFieldManagerNG() = default;
    ~TextFieldManagerNG() override = default;

    void SetClickPosition(const Offset& position) override
    {
        position_ = position;
    }
    const Offset& GetClickPosition() override
    {
        return position_;
    }
    void MovePage(int32_t pageId, const Offset& rootRect, double offsetHeight) override {}
    void RemovePageId(int32_t pageId) override {}

    WeakPtr<Pattern>& GetOnFocusTextField()
    {
        return onFocusTextField_;
    }

    void SetOnFocusTextField(const WeakPtr<Pattern>& onFocusTextField)
    {
        onFocusTextField_ = onFocusTextField;
    }

    void ScrollTextFieldToSafeArea();

    void ClearOnFocusTextField();

    bool ResetSlidingPanelParentHeight();

    bool UpdatePanelForVirtualKeyboard(double offsetY, double fullHeight);
    void SetHeight(float height);

    float GetHeight() const
    {
        return height_;
    }

    bool OnBackPressed();

    void UpdateScrollableParentViewPort(const RefPtr<FrameNode>& node);

    bool GetImeShow() const
    {
        return imeShow_;
    }

    void SetImeShow(bool imeShow)
    {
        imeShow_ = imeShow;
    }

private:
    void ScrollToSafeAreaHelper(const SafeAreaInsets::Inset& bottomInset, bool isShowKeyboard);
    RefPtr<FrameNode> FindScrollableOfFocusedTextField(const RefPtr<FrameNode>& textField);

    bool hasMove_ = false;
    bool imeShow_ = false;
    Offset position_;
    float height_ = 0.0f;
    WeakPtr<Pattern> onFocusTextField_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MANAGER_H
