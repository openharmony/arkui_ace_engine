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

#include "core/components_ng/pattern/indexer/indexer_layout_property.h"

namespace OHOS::Ace::NG {

void IndexerLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("Selected", std::to_string(propSelected_.value_or(0)).c_str());
    json->Put("Color", propColor_.value_or(Color::WHITE).ColorToString().c_str());
    json->Put("SelectedColor", propSelectedColor_.value_or(Color::WHITE).ColorToString().c_str());
    json->Put("PopupColor", propPopupColor_.value_or(Color::WHITE).ColorToString().c_str());
    json->Put("SelectedBackgroundColor", propSelectedBackgroundColor_.value_or(Color::WHITE)
                                             .ColorToString().c_str());
    json->Put("PopupBackground", propPopupBackground_.value_or(Color::WHITE).ColorToString().c_str());
    json->Put("UsingPopup", propUsingPopup_.value_or(false) ? "true" : "false");
    json->Put("ItemSize", propItemSize_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    json->Put("AlignStyle", propAlignStyle_.value_or(AlignStyle::LEFT) == AlignStyle::LEFT
                                ? "AlignStyle::LEFT"
                                : "AlignStyle::RIGHT");
    json->Put("PopupPositionX", std::to_string(propPopupPositionX_.value_or(0)).c_str());
    json->Put("PopupPositionY", std::to_string(propPopupPositionY_.value_or(0)).c_str());
}
}
