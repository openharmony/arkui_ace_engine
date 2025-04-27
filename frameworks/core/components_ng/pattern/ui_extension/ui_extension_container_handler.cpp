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
#include "core/components_ng/pattern/ui_extension/ui_extension_container_handler.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/dump_log.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr char UIEXTENSION_HOST_UICONTENT_TYPE[] = "ohos.ace.uiextension.hostUicontentType";
constexpr char UI_CONTENT_TYPE_FORM[] = "FORM";
constexpr char UI_CONTENT_TYPE_UI_EXTENSION[] = "UI_EXTENSION";
constexpr char UI_CONTENT_TYPE_SECURITY_UI_EXTENSION[] = "SECURITY_UI_EXTENSION";
constexpr char UI_CONTENT_TYPE_ISOLATED_COMPONENT[] = "ISOLATED_COMPONENT";
constexpr char UI_CONTENT_TYPE_DYNAMIC_COMPONENT[] = "DYNAMIC_COMPONENT";
constexpr char UI_CONTENT_TYPE_MODAL_UI_EXTENSION[] = "MODAL_UI_EXTENSION";

const std::unordered_map<std::string, UIContentType> UI_CONTENT_TYPE_FROM_STR_TO_TYPE_MAP = {
    { UI_CONTENT_TYPE_FORM, UIContentType::FORM },
    { UI_CONTENT_TYPE_UI_EXTENSION, UIContentType::UI_EXTENSION },
    { UI_CONTENT_TYPE_SECURITY_UI_EXTENSION, UIContentType::SECURITY_UI_EXTENSION },
    { UI_CONTENT_TYPE_ISOLATED_COMPONENT, UIContentType::ISOLATED_COMPONENT },
    { UI_CONTENT_TYPE_DYNAMIC_COMPONENT, UIContentType::DYNAMIC_COMPONENT },
    { UI_CONTENT_TYPE_MODAL_UI_EXTENSION, UIContentType::MODAL_UI_EXTENSION },
};

const std::unordered_map<UIContentType, std::string> UI_CONTENT_TYPE_FROM_TYPE_TO_STR_MAP = {
    { UIContentType::FORM, UI_CONTENT_TYPE_FORM },
    { UIContentType::UI_EXTENSION, UI_CONTENT_TYPE_UI_EXTENSION },
    { UIContentType::SECURITY_UI_EXTENSION, UI_CONTENT_TYPE_SECURITY_UI_EXTENSION },
    { UIContentType::ISOLATED_COMPONENT, UI_CONTENT_TYPE_ISOLATED_COMPONENT },
    { UIContentType::DYNAMIC_COMPONENT, UI_CONTENT_TYPE_DYNAMIC_COMPONENT },
    { UIContentType::MODAL_UI_EXTENSION, UI_CONTENT_TYPE_MODAL_UI_EXTENSION },
};
}

UIContentType UIExtensionContainerHandler::FromStrToUIContentType(const std::string& str)
{
    auto iter = UI_CONTENT_TYPE_FROM_STR_TO_TYPE_MAP.find(str);
    if (iter == UI_CONTENT_TYPE_FROM_STR_TO_TYPE_MAP.end()) {
        return UIContentType::UNDEFINED;
    }

    return iter->second;
}

std::string UIExtensionContainerHandler::FromUIContentTypeToStr(UIContentType uIContentType)
{
    auto iter = UI_CONTENT_TYPE_FROM_TYPE_TO_STR_MAP.find(uIContentType);
    if (iter == UI_CONTENT_TYPE_FROM_TYPE_TO_STR_MAP.end()) {
        return "";
    }

    return iter->second;
}

void UIExtensionContainerHandler::SetHostParams(const std::shared_ptr<OHOS::AAFwk::Want>& params)
{
    CHECK_NULL_VOID(params);
    SetHostUIContentType(params);
}

void UIExtensionContainerHandler::SetHostUIContentType(
    const std::shared_ptr<OHOS::AAFwk::Want>& params)
{
    CHECK_NULL_VOID(params);
    auto str = params->GetStringParam(UIEXTENSION_HOST_UICONTENT_TYPE);
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "SetHostUIContentType: %{public}s.", str.c_str());
    hostUIContentType_ = FromStrToUIContentType(str);
}
} // namespace OHOS::Ace::NG
