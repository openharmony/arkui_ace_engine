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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_OVERLAY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_OVERLAY_PROPERTY_H

#include <memory>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

struct OverlayOptions {
    OverlayOptions() = default;
    ~OverlayOptions() = default;
    std::string content;
    Alignment align;
    Dimension x;
    Dimension y;
    TextDirection direction = TextDirection::LTR;

    bool operator==(const OverlayOptions& value) const
    {
        return (content.compare(value.content) == 0) && (align == value.align) &&
               (x == value.x) && (y == value.y) && (direction == value.direction);
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto jsonOverlay = JsonUtil::Create(true);
        jsonOverlay->Put("title", content.c_str());
        auto jsonOptions = JsonUtil::Create(true);
        // should get TextDirection
        jsonOptions->Put("align", align.GetAlignmentStr(TextDirection::LTR).c_str());
        auto jsonOffset = JsonUtil::Create(true);
        jsonOffset->Put("x", x.ToString().c_str());
        jsonOffset->Put("y", y.ToString().c_str());
        jsonOptions->Put("offset", jsonOffset);
        jsonOverlay->Put("options", jsonOptions);
        json->PutExtAttr("overlay", jsonOverlay, filter);
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_OVERLAY_PROPERTY_H
