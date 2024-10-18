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

#include "component_test/core/component_test_matcher_impl.h"

#include "core/common/ace_engine.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::ComponentTest {

bool ComponentTestMatcherImpl::Match(const RefPtr<NG::UINode>& uiNode) const
{
    ComponentTestComponentImpl componentImpl;
    componentImpl.SetUiNode(uiNode);
    for (auto&& matchFunc : matchFuncs) {
        if (!matchFunc(componentImpl)) {
            return false;
        }
    }
    return true;
}

void ComponentTestMatcherImpl::SetText(const std::string& text, MatchType matchType)
{
    matchFuncs.emplace_back([text, matchType](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        std::string componentText = componentImpl.GetTextImpl(errInfo);
        if (errInfo.errCode != ErrCode::RET_OK) {
            return false;
        }
        switch (matchType) {
            case MatchType::EQUALS:
                if (text != componentText) {
                    return false;
                }
                break;
            case MatchType::CONTAINS:
                return componentText.find(text) != std::string::npos;
            case MatchType::STARTS_WITH:
                if (componentText.length() < text.length()) {
                    return false;
                } else {
                    return 0 == componentText.compare(0, text.length(), text);
                }
            case MatchType::ENDS_WITH:
                if (componentText.length() < text.length()) {
                    return false;
                } else {
                    return 0 == componentText.compare(componentText.length() - text.length(), text.length(), text);
                }
        }
        return true;
    });
}

void ComponentTestMatcherImpl::SetId(const std::string& id)
{
    matchFuncs.emplace_back([id](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        return componentImpl.GetIdImpl(errInfo) == id && errInfo.errCode == ErrCode::RET_OK;
    });
}

void ComponentTestMatcherImpl::SetType(const std::string& type)
{
    matchFuncs.emplace_back([type](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        return componentImpl.GetTypeImpl(errInfo) == type && errInfo.errCode == ErrCode::RET_OK;
    });
}

void ComponentTestMatcherImpl::SetClickable(bool clickabled)
{
    matchFuncs.emplace_back([clickabled](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        return componentImpl.IsClickableImpl(errInfo) == clickabled && errInfo.errCode == ErrCode::RET_OK;
    });
}

void ComponentTestMatcherImpl::SetLongPressable(bool longPressable)
{
    matchFuncs.emplace_back([longPressable](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        return componentImpl.IsLongPressableImpl(errInfo) == longPressable && errInfo.errCode == ErrCode::RET_OK;
    });
}

void ComponentTestMatcherImpl::SetScrollable(bool scrollable)
{
    matchFuncs.emplace_back([scrollable](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        return componentImpl.IsScrollableImpl(errInfo) == scrollable && errInfo.errCode == ErrCode::RET_OK;
    });
}

void ComponentTestMatcherImpl::SetEnabled(bool enabled)
{
    matchFuncs.emplace_back([enabled](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        return componentImpl.IsEnabledImpl(errInfo) == enabled && errInfo.errCode == ErrCode::RET_OK;
    });
}

void ComponentTestMatcherImpl::SetFocused(bool focused)
{
    matchFuncs.emplace_back([focused](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        return componentImpl.IsFocusedImpl(errInfo) == focused && errInfo.errCode == ErrCode::RET_OK;
    });
}

void ComponentTestMatcherImpl::SetSelected(bool selected)
{
    matchFuncs.emplace_back([selected](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        return componentImpl.IsSelectedImpl(errInfo) == selected && errInfo.errCode == ErrCode::RET_OK;
    });
}

void ComponentTestMatcherImpl::SetChecked(bool checked)
{
    matchFuncs.emplace_back([checked](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        return componentImpl.IsCheckedImpl(errInfo) == checked && errInfo.errCode == ErrCode::RET_OK;
    });
}

void ComponentTestMatcherImpl::SetCheckable(bool checkable)
{
    matchFuncs.emplace_back([checkable](ComponentTestComponentImpl& componentImpl) -> bool {
        ErrInfo errInfo { ErrCode::RET_OK, "" };
        return componentImpl.IsCheckableImpl(errInfo) == checkable && errInfo.errCode == ErrCode::RET_OK;
    });
}

} // namespace OHOS::Ace::ComponentTest
