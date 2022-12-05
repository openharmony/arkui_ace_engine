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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_LAYOUT_PROPERTY_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ModelPattern;

class ACE_EXPORT ModelLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ModelLayoutProperty, LayoutProperty);

public:
    ModelLayoutProperty() = default;

    ~ModelLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ModelLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propModelSource_ = CloneModelSource();
        value->propModelBackground_ = CloneModelBackground();
        value->propModelCameraMove_ = CloneModelCameraMove();
        value->propModelTransparent_ = CloneModelTransparent();

        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetModelSource();
        ResetModelBackground();
        ResetModelCameraMove();
        ResetModelTransparent();
    }

    void OnModelSourceUpdate(const std::string& value)
    {
        UpdateNeedsSceneSetup(true);
    }

    void OnModelBackgroundUpdate(const std::string& value)
    {
        UpdateNeedsSceneSetup(true);
    }

    bool NeedsSceneSetup()
    {
        return needsSceneSetup_;
    }

    void UpdateNeedsSceneSetup(const bool value)
    {
        needsSceneSetup_ = value;
        if (value) {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(ModelSource, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(ModelBackground, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ModelCameraMove, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ModelTransparent, bool, PROPERTY_UPDATE_MEASURE);

private:
    bool needsSceneSetup_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ModelLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_LAYOUT_PROPERTY_H
