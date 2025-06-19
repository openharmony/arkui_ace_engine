/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODEL_H

#include <mutex>

#include "core/common/resource/resource_object.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_event_hub.h"
#include "core/components_ng/pattern/checkbox/checkbox_model.h"

namespace OHOS::Ace {
enum class CheckBoxGroupColorType {
    SELECTED_COLOR,
    UN_SELECTED_COLOR
};
class ACE_FORCE_EXPORT CheckBoxGroupModel {
public:
    static CheckBoxGroupModel* GetInstance();
    virtual ~CheckBoxGroupModel() = default;

    virtual void Create(const std::optional<std::string>& groupName);
    virtual void SetSelectAll(bool isSelected);
    virtual void SetSelectedColor(const Color& color);
    virtual void SetUnSelectedColor(const Color& color) {}
    virtual void SetCheckMarkColor(const Color& color) {}
    virtual void SetCheckMarkSize(const Dimension& size) {}
    virtual void SetCheckMarkWidth(const Dimension& width) {}
    virtual void SetOnChange(NG::GroupChangeEvent&& onChange);
    virtual void SetWidth(const Dimension& width);
    virtual void SetHeight(const Dimension& height);
    virtual void SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs, bool flag);
    virtual void SetChangeEvent(NG::GroupChangeEvent&& changeEvent) {};
    virtual void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) {};
    virtual void SetCheckboxGroupStyle(CheckBoxStyle checkboxGroupStyle) {};
    virtual void ResetSelectedColor() {};
    virtual void ResetUnSelectedColor() {};
    virtual void ResetCheckMarkColor() {};
    virtual void CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj,
        const CheckBoxGroupColorType checkBoxGroupColorType) {};

private:
    static std::unique_ptr<CheckBoxGroupModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODEL_H
