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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PREVIEW_MOCK_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PREVIEW_MOCK_MODEL_IMPL_H

#include <functional>
#include <string>

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/preview_mock/preview_mock_model.h"

namespace OHOS::Ace {
class CanvasTaskPool;
}
namespace OHOS::Ace::Framework {

class ACE_EXPORT PreviewMockModelImpl : public PreviewMockModel {
public:
    void Create(const std::string& content) override;

    ACE_FORCE_EXPORT static void CreateJSRenderingContext(bool anti, const RefPtr<CanvasTaskPool>& pool);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_PREVIEW_MOCK_MODEL_IMPL_H
