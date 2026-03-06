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

#ifndef ACCESSIBILITY_CAPI_FAKE_CHECKBOX_H
#define ACCESSIBILITY_CAPI_FAKE_CHECKBOX_H

#include "fake_node.h"

namespace NativeXComponentSample {

/**
 * @brief 复选框节点
 *
 * 演示Checkbox相关的Native接口：
 * - SetCheckable
 * - SetChecked
 */
class FakeCheckbox : public AccessibleObject {
public:
    explicit FakeCheckbox(const std::string& name);
    ~FakeCheckbox() = default;

    void SetLabel(const std::string& label)
    {
        label_ = label;
        SetName(label);
    }

    const char* ObjectType() const override
    {
        return "FakeCheckbox";
    }

    const char* Hint() const override
    {
        return label_.c_str();
    }

    std::string Name() const
    {
        return label_;
    }

    void OnClick() override
    {
        // 切换选中状态
        isChecked_ = !isChecked_;
        SetChecked(isChecked_);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FakeCheckbox",
            "Checkbox %{public}s checked: %{public}d",
            Name().c_str(), isChecked_);
    }

    bool IsChecked() const
    {
        return isChecked_;
    }

private:
    std::string label_;
    bool isChecked_ = false;
};

} // namespace NativeXComponentSample

#endif // ACCESSIBILITY_CAPI_FAKE_CHECKBOX_H
