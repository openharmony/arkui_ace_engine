/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CAMERA_CAMERA_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CAMERA_CAMERA_THEME_H

#include "base/geometry/size.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/*
 * CameraTheme defines color and styles of Camera. CameraTheme should be built
 * using CameraTheme::Builder.
 */
class CameraTheme : public virtual Theme {
    DECLARE_ACE_TYPE(CameraTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;
        const Dimension themeCameraBufferWidth = Dimension(1080.0, DimensionUnit::PX);
        const Dimension themeCameraBufferHeight = Dimension(1920.0, DimensionUnit::PX);
        const Dimension themeVideoTextFontsize = Dimension(15.0, DimensionUnit::VP);
        const Color themeVideoErrorTextColor = Color(0xffc0c0c0);

        RefPtr<CameraTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<CameraTheme> theme = AceType::MakeRefPtr<CameraTheme>();
            if (!themeConstants) {
                return theme;
            }
            theme->bufferSize_ = Size(themeCameraBufferWidth.Value(), themeCameraBufferHeight.Value());
#if defined(PREVIEW)
            theme->errorTextStyle_.SetFontSize(themeVideoTextFontsize);
            theme->errorTextStyle_.SetTextColor(themeVideoErrorTextColor);
#endif
            return theme;
        }
    };

    ~CameraTheme() override = default;

    const Size& GetBufferSize() const
    {
        return bufferSize_;
    }

#if defined(PREVIEW)
    const TextStyle& GetErrorTextStyle() const
    {
        return errorTextStyle_;
    }
#endif

protected:
    CameraTheme() = default;

private:
    Size bufferSize_;

#if defined(PREVIEW)
    TextStyle errorTextStyle_;
#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CAMERA_CAMERA_THEME_H
