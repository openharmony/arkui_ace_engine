/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "ashmem.h"

#include "core/components/form/sub_container.h"

namespace OHOS::Ace {
SubContainer::~SubContainer() {}

void SubContainer::Initialize() {}

void SubContainer::Destroy() {}

void SubContainer::UpdateRootElementSize() {}

void SubContainer::UpdateSurfaceSize() {}

void SubContainer::UpdateSurfaceSizeWithAnimathion() {}

void SubContainer::RunCard(int64_t formId, const std::string& path, const std::string& module, const std::string& data,
    const std::map<std::string, sptr<AppExecFwk::FormAshmem>>& imageDataMap, const std::string& formSrc,
    const FrontendType& cardType, const FrontendType& uiSyntax)
{}
void SubContainer::RunSameCard() {}

void SubContainer::UpdateConfiguration() {}

void SubContainer::UpdateCard(
    const std::string& content, const std::map<std::string, sptr<AppExecFwk::FormAshmem>>& imageDataMap)
{}
} // namespace OHOS::Ace
