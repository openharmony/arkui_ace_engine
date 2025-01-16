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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_QRCODE_QRCODE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_QRCODE_QRCODE_THEME_H

#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components/theme/theme_manager.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
namespace {
constexpr double QRCODE_SIZE = 200.0;
constexpr Color QRCODE_DEFAULT_COLOR = Color(0xff000000);
constexpr Color QRCODE_DEFAULT_BACKGROUND_COLOR = Color(0xffffffff);
} // namespace

class QrcodeTheme : public virtual Theme {
    DECLARE_ACE_TYPE(QrcodeTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<QrcodeTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<QrcodeTheme> theme = AceType::Claim(new QrcodeTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<QrcodeTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_QRCODE);
            if (!pattern) {
                return;
            }
            theme->qrcodeDefaultSize_ = pattern->GetAttr<Dimension>("default_size", 240.0_vp);
            theme->backgroundColor_ = QRCODE_DEFAULT_BACKGROUND_COLOR;
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                theme->qrcodeColor_ = Color(0xff000000);
                theme->qrcodeType_ = QrcodeType::RECT;
                theme->qrcodeWidth_ = Dimension(QRCODE_SIZE, DimensionUnit::PX);
                theme->qrcodeHeight_ = Dimension(QRCODE_SIZE, DimensionUnit::PX);
                return;
            }
            theme->qrcodeColor_ = QRCODE_DEFAULT_COLOR;
            theme->focusedColor_ = pattern->GetAttr<Color>("qrcode_focused_color", Color::RED);
            theme->qrcodeType_ = QrcodeType(pattern->GetAttr<int>("qrcode_type", 0));
            theme->qrcodeWidth_ = pattern->GetAttr<Dimension>("qrcode_size", 200.0_px);
            theme->qrcodeHeight_ = pattern->GetAttr<Dimension>("qrcode_size", 200.0_px);
            theme->focusStyleType_ = pattern->GetAttr<double>("qrcode_focus_style_type", 0.0);
        }
    };

    ~QrcodeTheme() override = default;

    const Color& GetQrcodeColor() const
    {
        return qrcodeColor_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetFocusedColor() const
    {
        return focusedColor_;
    }

    QrcodeType GetQrcodeType() const
    {
        return qrcodeType_;
    }

    const Dimension& GetQrcodeWidth() const
    {
        return qrcodeWidth_;
    }

    const Dimension& GetQrcodeHeight() const
    {
        return qrcodeHeight_;
    }

    const Dimension& GetQrcodeDefaultSize() const
    {
        return qrcodeDefaultSize_;
    }

    double GetFocusStyleType() const
    {
        return focusStyleType_;
    }

protected:
    QrcodeTheme() = default;

private:
    Color qrcodeColor_;
    Color backgroundColor_;
    Color focusedColor_;
    QrcodeType qrcodeType_ { QrcodeType::RECT };
    Dimension qrcodeWidth_;
    Dimension qrcodeHeight_;
    Dimension qrcodeDefaultSize_;
    double focusStyleType_ = 0.0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_QRCODE_QRCODE_THEME_H
