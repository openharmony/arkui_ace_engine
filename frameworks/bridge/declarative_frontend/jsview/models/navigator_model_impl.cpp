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

#include "bridge/declarative_frontend/jsview/models/navigator_model_impl.h"

#include "core/components/box/box_component.h"
#include "core/components/navigator/navigator_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void NavigatorModelImpl::Create()
{
    RefPtr<OHOS::Ace::Component> child;
    auto navigatorComponent = AceType::MakeRefPtr<OHOS::Ace::NavigatorComponent>(child);
    ViewStackProcessor::GetInstance()->Push(navigatorComponent);
}

void NavigatorModelImpl::SetType(NavigatorType value)
{
    auto navigator = AceType::DynamicCast<NavigatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    navigator->SetType(value);
}

void NavigatorModelImpl::SetActive(bool active)
{
    auto navigator = AceType::DynamicCast<NavigatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (navigator) {
        navigator->SetActive(active);
    }
}

void NavigatorModelImpl::SetUri(const std::string& uri)
{
    auto navigator = AceType::DynamicCast<NavigatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (navigator) {
        navigator->SetUri(uri);
    }
}

void NavigatorModelImpl::SetParams(const std::string& params)
{
    auto navigator = AceType::DynamicCast<NavigatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (navigator) {
        navigator->SetParams(params);
    }
}

void NavigatorModelImpl::SetIsDefWidth(bool isDefWidth)
{
    auto navigator = AceType::DynamicCast<NavigatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (navigator) {
        navigator->SetIsDefWidth(true);
    }
}

void NavigatorModelImpl::SetIsDefHeight(bool isDefHeight)
{
    auto navigator = AceType::DynamicCast<NavigatorComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (navigator) {
        navigator->SetIsDefHeight(true);
    }
}

} // namespace OHOS::Ace::Framework
