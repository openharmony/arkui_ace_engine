/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_COMMON_COMMON_BACKGROUND_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_COMMON_COMMON_BACKGROUND_STYLE_H

#include "core/components/common/properties/border_image.h"
#include "core/components/common/properties/gradient.h"
#include "core/components/declaration/common/style.h"

namespace OHOS::Ace {

struct CommonBackgroundStyle : Style {
    ~CommonBackgroundStyle() = default;
    Gradient gradient;
    Gradient gradientBorderImage;
    Color backgroundColor;
    std::string backgroundSize;
    RefPtr<BackgroundImage> backgroundImage;
    RefPtr<BorderImage> borderImage;
    ImageRepeat backgroundRepeat;
    std::string backgroundPosition;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_COMMON_COMMON_BACKGROUND_STYLE_H
