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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/form/resource/form_request_data.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT FormLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(FormLayoutProperty, LayoutProperty);

public:
    FormLayoutProperty() = default;
    ~FormLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<FormLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<FormLayoutProperty>(this));
        value->propRequestFormInfo_ = CloneRequestFormInfo();
        value->propVisibleType_ = CloneVisibleType();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetRequestFormInfo();
        ResetVisibleType();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto formInfo = GetRequestFormInfoValue(RequestFormInfo());
        auto jsonConstructor = JsonUtil::Create(true);
        jsonConstructor->Put("allowUpdate", formInfo.allowUpdate ? "true" : "false");
        jsonConstructor->Put("dimension", std::to_string(formInfo.dimension).c_str());
        auto jsonSize = JsonUtil::Create(true);
        jsonSize->Put("width", formInfo.width.ToString().c_str());
        jsonSize->Put("height", formInfo.height.ToString().c_str());
        jsonConstructor->Put("size", jsonSize);
        jsonConstructor->Put("moduleName", formInfo.moduleName.c_str());
        json->PutExtAttr("constructor", jsonConstructor, filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(VisibleType, VisibleType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RequestFormInfo, RequestFormInfo, PROPERTY_UPDATE_MEASURE);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_LAYOUT_PROPERTY_H
