/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_COMPONENT_TEST_MATCHER_IMPL_H
#define OHOS_ACE_COMPONENT_TEST_MATCHER_IMPL_H

#include "component_test/core/component_test_component_impl.h"

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::ComponentTest {
enum class MatchType : uint8_t {
    EQUALS,
    CONTAINS,
    STARTS_WITH,
    ENDS_WITH,
};

using MatchFunc = std::function<bool(ComponentTestComponentImpl&)>;

struct MatchText {
    MatchText() : text_(""), matchType(MatchType::EQUALS), isCheck(false) {};
    explicit MatchText(const std::string& text) : text_(text), matchType(MatchType::EQUALS), isCheck(true) {};
    MatchText(const std::string& text, MatchType matchType) : text_(text), matchType(matchType), isCheck(true) {};
    std::string text_;
    MatchType matchType;
    bool isCheck;
};

struct MatchString {
    MatchString() : value(""), isCheck(false) {};
    explicit MatchString(const std::string& value) : value(value), isCheck(true) {};
    std::string value;
    bool isCheck;
};

struct MatchBool {
    MatchBool() : value(false), isCheck(false) {};
    explicit MatchBool(bool value) : value(value), isCheck(true) {};
    bool value;
    bool isCheck;
};

class ACE_FORCE_EXPORT ComponentTestMatcherImpl final {
public:
    ComponentTestMatcherImpl() = default;
    ~ComponentTestMatcherImpl() = default;

    bool Match(const RefPtr<NG::UINode>& uiNode) const;
    void SetText(const std::string& text, MatchType matchType = MatchType::EQUALS);
    void SetId(const std::string& id);
    void SetType(const std::string& type);
    void SetClickable(bool clickabled);
    void SetLongPressable(bool longPressable);
    void SetScrollable(bool scrollable);
    void SetEnabled(bool enabled);
    void SetFocused(bool focused);
    void SetSelected(bool selected);
    void SetChecked(bool checked);
    void SetCheckable(bool checkable);

private:
    std::vector<MatchFunc> matchFuncs;
};

} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_NAPI_ACE_COMPONENT_TEST_MATCHER_IMPL_H
