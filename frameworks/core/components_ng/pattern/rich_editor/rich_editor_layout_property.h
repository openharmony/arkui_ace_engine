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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_PROPERTY_H

#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RichEditorLayoutProperty : public TextLayoutProperty {
    DECLARE_ACE_TYPE(RichEditorLayoutProperty, TextLayoutProperty);

public:
    RichEditorLayoutProperty();
    ~RichEditorLayoutProperty() override;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorLayoutProperty);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PreviewTextStyle, std::string, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayMode, DisplayMode, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_PROPERTY_H
