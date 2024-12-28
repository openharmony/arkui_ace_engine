/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER2_H
#define GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER2_H

#pragma once

// SORTED_SECTION
#include <optional>

#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/pattern/text_field/text_selector.h"

namespace OHOS::Ace::NG {
namespace Converter {
    template<> void AssignCast(std::optional<DragRet>& dst, const Ark_DragResult& src);
    template<> void AssignCast(std::optional<ToggleType>& dst, const Ark_ToggleType& src);
    template<> void AssignCast(std::optional<TextSpanType>& dst, const Ark_RichEditorSpanType& src);
    template<> void AssignCast(std::optional<TextResponseType>& dst, const Ark_ResponseType& src);
    template<> void AssignCast(std::optional<TextResponseType>& dst, const Ark_RichEditorResponseType& src);
    template<> SelectMenuParam Convert(const Ark_SelectionMenuOptions& src);
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG

#endif  // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_H
