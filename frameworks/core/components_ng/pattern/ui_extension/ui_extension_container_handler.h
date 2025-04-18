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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_UIEXTENSION_CONTAINER_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_UIEXTENSION_CONTAINER_HANDLER_H

#include "base/memory/ace_type.h"
#include "frameworks/core/common/container_handler.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "interfaces/inner_api/ace/constants.h"
#include "want.h"

namespace OHOS::Ace::NG {

class UIExtensionContainerHandler : public ContainerHandler {
    DECLARE_ACE_TYPE(UIExtensionContainerHandler, ContainerHandler);

public:
    UIExtensionContainerHandler() = default;
    ~UIExtensionContainerHandler() override = default;

    static UIContentType FromStrToUIContentType(const std::string& str);
    static std::string FromUIContentTypeToStr(UIContentType uIContentType);

    UIContentType GetHostUIContentType() const
    {
        return hostUIContentType_;
    }

    void SetHostUIContentType(UIContentType hostUIContentType)
    {
        hostUIContentType_ = hostUIContentType;
    }

    void SetHostParams(const std::shared_ptr<OHOS::AAFwk::Want>& params);

private:
    void SetHostUIContentType(const std::shared_ptr<OHOS::AAFwk::Want>& params);

    UIContentType hostUIContentType_ = UIContentType::UNDEFINED;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_UIEXTENSION_CONTAINER_HANDLER_H
