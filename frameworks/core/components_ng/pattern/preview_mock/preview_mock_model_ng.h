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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PREVIEW_MOCK_PREVIEW_MOCK_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PREVIEW_MOCK_PREVIEW_MOCK_MODEL_NG_H

#include "frameworks/core/components_ng/pattern/preview_mock/preview_mock_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT PreviewMockModelNG : public PreviewMockModel {
public:
    void Create(const std::string& content) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PREVIEW_MOCK_PREVIEW_MOCK_MODEL_NG_H
