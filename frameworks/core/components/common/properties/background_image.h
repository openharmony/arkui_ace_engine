/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BACKGROUND_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BACKGROUND_IMAGE_H

#include <string>

#include "base/memory/ace_type.h"
#include "base/geometry/animatable_dimension.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

constexpr double FULL_IMG_SIZE = 100.0;

class PipelineContext;
class ThemeConstants;

enum class ACE_EXPORT BackgroundImageSizeType {
    CONTAIN = 0,
    COVER,
    AUTO,
    FILL,
    LENGTH,
    PERCENT,
};

class ACE_FORCE_EXPORT BackgroundImageSize final {
public:
    BackgroundImageSize() = default;
    BackgroundImageSize(BackgroundImageSizeType type, double value) : typeX_(type), valueX_(value) {}
    BackgroundImageSize(BackgroundImageSizeType typeX, double valueX, BackgroundImageSizeType typeY, double valueY)
        : typeX_(typeX), valueX_(valueX), typeY_(typeY), valueY_(valueY)
    {}
    ~BackgroundImageSize() = default;

    void SetSizeTypeX(BackgroundImageSizeType type);
    void SetSizeTypeY(BackgroundImageSizeType type);
    void SetSizeValueX(double value);
    void SetSizeValueY(double value);
    bool IsValid() const;
    BackgroundImageSizeType GetSizeTypeX() const;
    BackgroundImageSizeType GetSizeTypeY() const;
    double GetSizeValueX() const;
    double GetSizeValueY() const;

    BackgroundImageSize operator+(const BackgroundImageSize& size) const;
    BackgroundImageSize operator-(const BackgroundImageSize& size) const;
    BackgroundImageSize operator*(double value) const;

    bool operator==(const BackgroundImageSize& size) const;
    bool operator!=(const BackgroundImageSize& size) const;

    std::string ToString() const;

private:
    BackgroundImageSizeType typeX_ { BackgroundImageSizeType::AUTO };
    double valueX_ = 0.0;
    BackgroundImageSizeType typeY_ { BackgroundImageSizeType::AUTO };
    double valueY_ = 0.0;
};

enum class ACE_EXPORT BackgroundImagePositionType {
    PERCENT = 0,
    PX,
};

class ACE_EXPORT BackgroundImagePosition {
public:
    BackgroundImagePosition() = default;
    ~BackgroundImagePosition() = default;
    BackgroundImagePosition(
        BackgroundImagePositionType typeX, double valueX, BackgroundImagePositionType typeY, double valueY)
        : typeX_(typeX), typeY_(typeY), valueX_(AnimatableDimension(valueX)), valueY_(AnimatableDimension(valueY))
    {}

    void SetContextAndCallback(const WeakPtr<PipelineContext>& context, const RenderNodeAnimationCallback& callback);

    void SetSizeTypeX(BackgroundImagePositionType type)
    {
        typeX_ = type;
    }

    void SetSizeX(const AnimatableDimension& sizeX)
    {
        if (sizeX.Unit() == DimensionUnit::PERCENT) {
            typeX_ = BackgroundImagePositionType::PERCENT;
        } else {
            typeX_ = BackgroundImagePositionType::PX;
        }
        valueX_ = sizeX;
    }

    void SetSizeTypeY(BackgroundImagePositionType type)
    {
        typeY_ = type;
    }

    void SetSizeY(const AnimatableDimension& sizeY)
    {
        if (sizeY.Unit() == DimensionUnit::PERCENT) {
            typeY_ = BackgroundImagePositionType::PERCENT;
        } else {
            typeY_ = BackgroundImagePositionType::PX;
        }
        valueY_ = sizeY;
    }

    void SetSizeValueX(double value)
    {
        valueX_ = AnimatableDimension(value);
    }

    void SetSizeValueY(double value)
    {
        valueY_ = AnimatableDimension(value);
    }

    void SetIsAlign(bool isAlign)
    {
        isAlign_ = isAlign;
    }

    BackgroundImagePositionType GetSizeTypeX() const
    {
        return typeX_;
    }

    BackgroundImagePositionType GetSizeTypeY() const
    {
        return typeY_;
    }

    const AnimatableDimension& GetSizeX() const
    {
        return valueX_;
    }

    const AnimatableDimension& GetSizeY() const
    {
        return valueY_;
    }

    double GetSizeValueX() const
    {
        return valueX_.Value();
    }

    double GetSizeValueY() const
    {
        return valueY_.Value();
    }

    bool IsAlign() const
    {
        return isAlign_;
    }

    BackgroundImagePosition operator+(const BackgroundImagePosition& position) const;

    BackgroundImagePosition operator-(const BackgroundImagePosition& position) const;

    BackgroundImagePosition operator*(double value) const;

    bool operator==(const BackgroundImagePosition& backgroundImagePosition) const;

    bool operator!=(const BackgroundImagePosition& backgroundImagePosition) const;

    std::string ToString() const;

private:
    BackgroundImagePositionType typeX_ { BackgroundImagePositionType::PX };
    BackgroundImagePositionType typeY_ { BackgroundImagePositionType::PX };
    AnimatableDimension valueX_ = AnimatableDimension(-1.0);
    AnimatableDimension valueY_ = AnimatableDimension(0.0);
    bool isAlign_ = false;
};

class ImageObjectPosition final : public BackgroundImagePosition {};

class BackgroundImage final : public AceType {
    DECLARE_ACE_TYPE(BackgroundImage, AceType);

public:
    BackgroundImage() = default;
    ~BackgroundImage() override = default;

    const BackgroundImageSize& GetImageSize() const
    {
        return imageSize_;
    }

    const BackgroundImagePosition& GetImagePosition() const
    {
        return imagePosition_;
    }

    ImageRepeat GetImageRepeat() const
    {
        return imageRepeat_;
    }

    const std::string& GetSrc() const
    {
        return src_;
    }

    void SetImageSize(BackgroundImageSize imageSize)
    {
        imageSize_ = imageSize;
    }

    void SetImageSize(BackgroundImageSizeType type, double value = FULL_IMG_SIZE)
    {
        imageSize_ = BackgroundImageSize(type, value);
    }

    void SetImageSize(BackgroundImageSizeType typeX, double valueX, BackgroundImageSizeType typeY, double valueY)
    {
        imageSize_ = BackgroundImageSize(typeX, valueX, typeY, valueY);
    }

    void SetImagePosition(const BackgroundImagePosition& imagePosition)
    {
        imagePosition_ = imagePosition;
    }

    void SetImagePosition(
        BackgroundImagePositionType typeX, double valueX, BackgroundImagePositionType typeY, double valueY)
    {
        imagePosition_ = BackgroundImagePosition(typeX, valueX, typeY, valueY);
    }

    void SetImageRepeat(const ImageRepeat& imageRepeat)
    {
        imageRepeat_ = imageRepeat;
    }

    void SetSrc(const std::string& src, const RefPtr<ThemeConstants>& themeConstants);

    void SetParsedSrc(const std::string& src)
    {
        // src is processed by ParseJsMedia function
        src_ = src;
    }

    bool operator==(const BackgroundImage& image) const
    {
        bool fileName = src_ == image.GetSrc();
        bool size = imageSize_ == image.GetImageSize();
        bool position = imagePosition_ == image.GetImagePosition();
        bool repeat = imageRepeat_ == image.GetImageRepeat();
        return fileName && size && position && repeat;
    }

    bool operator!=(const BackgroundImage& image) const
    {
        return !operator==(image);
    }

private:
    std::string src_;
    BackgroundImageSize imageSize_;
    BackgroundImagePosition imagePosition_;
    ImageRepeat imageRepeat_ { ImageRepeat::REPEAT };
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BACKGROUND_IMAGE_H
