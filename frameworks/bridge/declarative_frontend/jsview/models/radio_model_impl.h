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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RADIO_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RADIO_MODEL_IMPL_H

#include "core/components_ng/pattern/radio/radio_model.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT RadioModelImpl : public OHOS::Ace::RadioModel {
public:
    void Create(const std::optional<std::string>& value, const std::optional<std::string>& group,
        const std::optional<int32_t>& indicator) override;
    void SetChecked(bool isChecked) override;
    void SetOnChange(NG::ChangeEvent&& onChange) override;
    void SetWidth(const Dimension& width) override;
    void SetHeight(const Dimension& height) override;
    void SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs) override;
    void SetOnClickEvent(std::function<void()>&& onClick) override;
    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override;
    void CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj,
        const RadioColorType radioColorType) override {};
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RADIO_MODEL_IMPL_H
