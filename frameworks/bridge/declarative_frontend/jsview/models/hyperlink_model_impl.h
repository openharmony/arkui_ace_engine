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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_HYPERLINK_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_HYPERLINK_MODEL_IMPL_H

#include "core/components_ng/pattern/hyperlink/hyperlink_model.h"
#include "core/components/hyperlink/hyperlink_component.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT HyperlinkModelImpl : public HyperlinkModel {
public:
    void Create(const std::string& address, const std::string& summary) override;
    void SetColor(const Color& value) override;
    void Pop() override;
    void SetDraggable(bool draggable) override {}

private:
    RefPtr<HyperlinkComponent> GetComponent();
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_HYPERLINK_MODEL_IMPL_H