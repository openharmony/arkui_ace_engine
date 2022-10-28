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

#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"

namespace OHOS::Ace::NG {

namespace {

const Color DEFAULT_SELECTED_COLOR = Color(0xFF007DFF);

} // namespace

void CheckBoxPaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    PaintProperty::ToJsonValue(json);
    json->Put("select", GetCheckBoxSelect().value_or(false) ? "true" : "false");
    json->Put("selectedColor", GetCheckBoxSelectedColor().value_or(DEFAULT_SELECTED_COLOR).ColorToString().c_str());
}

} // namespace OHOS::Ace::NG
