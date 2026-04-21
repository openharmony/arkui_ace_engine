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

#ifndef ACCESSIBILITY_CAPI_FAKE_TEXTFIELD_H
#define ACCESSIBILITY_CAPI_FAKE_TEXTFIELD_H

#include "fake_node.h"

namespace NativeXComponentSample {

/**
 * @brief 文本输入框节点
 *
 * 演示TextField相关的Native接口：
 * - SetEditable
 * - SetIsPassword
 * - SetSelectedTextStart
 * - SetSelectedTextEnd
 * - SetHintText
 */
class FakeTextField : public AccessibleObject {
public:
    explicit FakeTextField(const std::string& name);
    ~FakeTextField() = default;

    // TextField特有方法
    void SetHintText(const std::string& hint)
    {
        hintText_ = hint;
    }

    void SetTextContent(const std::string& text)
    {
        textContent_ = text;
        SetName(text);
    }

    void SetPassword(bool isPassword)
    {
        isPassword_ = isPassword;
    }

    void SetTextSelection(int32_t start, int32_t end)
    {
        if (start <= end) {
            selectedTextStart_ = start;
            selectedTextEnd_ = end;
        }
    }

    int32_t GetSelectedTextStart() const
    {
        return selectedTextStart_;
    }

    int32_t GetSelectedTextEnd() const
    {
        return selectedTextEnd_;
    }

    // 重写基类方法
    const char* ObjectType() const override
    {
        return "FakeTextField";
    }

    const char* Hint() const override
    {
        return hintText_.c_str();
    }

    std::string Name() const
    {
        return textContent_.empty() ? OriginName() : textContent_;
    }

private:
    std::string hintText_;
    std::string textContent_;
    bool isPassword_ = false;
    int32_t selectedTextStart_ = 0;
    int32_t selectedTextEnd_ = 0;
};

} // namespace NativeXComponentSample

#endif // ACCESSIBILITY_CAPI_FAKE_TEXTFIELD_H
