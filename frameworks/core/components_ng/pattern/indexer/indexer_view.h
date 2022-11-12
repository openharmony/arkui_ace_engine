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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_VIEW_H

#include "core/components_v2/indexer/indexer_component.h"
#include "core/components_ng/pattern/indexer/indexer_event_hub.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT IndexerView {
public:
    static void Create(const std::vector<std::string>& arrayValue, int32_t selected);
    static void SetColor(const Color& color);
    static void SetSelectedColor(const Color& selectedColor);
    static void SetPopupColor(const Color& popupColor);
    static void SetSelectedBackgroundColor(const Color& selectedBackgroundColor);
    static void SetPopupBackground(const Color& popupBackground);
    static void SetUsingPopup(bool usingPopup);
    static void SetSelectedFont(const TextStyle& selectedFont);
    static void SetPopupFont(const TextStyle& popupFont);
    static void SetFont(const TextStyle& font);
    static void SetItemSize(const Dimension& itemSize);
    static void SetAlignStyle(NG::AlignStyle alignStyle);
    static void SetSelected(int32_t selected);
    static void SetPopupPositionX(float popupPositionX);
    static void SetPopupPositionY(float popupPositionY);
    static void SetOnSelected(OnSelectedEvent&& onSelected);
    static void SetOnRequestPopupData(OnRequestPopupDataEvent&& onRequestPopupData);
    static void SetOnPopupSelected(OnPopupSelectedEvent&& onPopupSelectedEvent);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_VIEW_H
