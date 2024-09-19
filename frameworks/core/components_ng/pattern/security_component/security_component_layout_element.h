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
#ifndef SECUIRTY_COMPONENT_LAYOUT_ELEMENT_H
#define SECUIRTY_COMPONENT_LAYOUT_ELEMENT_H

#include "base/geometry/ng/size_t.h"
#include "base/log/ace_scoring_log.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/security_component/security_component_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
class SecurityComponentLayoutElement {
public:
    SecurityComponentLayoutElement() = default;
    virtual ~SecurityComponentLayoutElement() = default;
    virtual double EnlargeWidth(double addSize)
    {
        return addSize;
    };

    virtual double EnlargeHeight(double addSize)
    {
        return addSize;
    };

    virtual double ShrinkWidth(double reduceSize)
    {
        return reduceSize;
    };

    virtual double ShrinkHeight(double reduceSize)
    {
        return reduceSize;
    };

    double width_ = 0.0;
    double height_ = 0.0;
    bool isSetSize_ = false;
};

class IconLayoutElement : public SecurityComponentLayoutElement {
public:
    IconLayoutElement() {};
    void Init(RefPtr<SecurityComponentLayoutProperty>& property, RefPtr<LayoutWrapper>& textWrap);
    ~IconLayoutElement() = default;

    double ShrinkWidth(double reduceSize) override;
    double ShrinkHeight(double reduceSize) override;
    void DoMeasure();

private:
    bool isExist_ = false;
    double minIconSize_;
    RefPtr<SecurityComponentLayoutProperty> secCompProperty_;
    RefPtr<LayoutWrapper> iconWrap_;
};

class PaddingLayoutElement : public SecurityComponentLayoutElement {
public:
    PaddingLayoutElement() {};
    void Init(bool isVertical, bool isSetSize, double size, double minSize)
    {
        isVertical_ = isVertical;
        isSetSize_ = isSetSize;
        minPadddingSize_ = minSize;
        if (isVertical) {
            height_ = size;
        } else {
            width_ = size;
        }
    };

    ~PaddingLayoutElement() = default;
    double EnlargeWidth(double addSize) override
    {
        if (isVertical_ || isSetSize_) {
            return addSize;
        }
        width_ += addSize;
        return 0.0;
    };

    double EnlargeHeight(double addSize) override
    {
        if (!isVertical_ || isSetSize_) {
            return addSize;
        }
        height_ += addSize;
        return 0.0;
    };

    double ShrinkWidth(double reduceSize) override
    {
        if (isVertical_ || isSetSize_) {
            return reduceSize;
        }
        if (GreatNotEqual(minPadddingSize_, width_ - reduceSize)) {
            double remain = reduceSize - (width_ - minPadddingSize_);
            width_ = minPadddingSize_;
            return remain;
        }
        width_ -= reduceSize;
        return 0.0;
    };

    double ShrinkHeight(double reduceSize) override
    {
        if (!isVertical_ || isSetSize_) {
            return reduceSize;
        }
        if (GreatNotEqual(minPadddingSize_, height_ - reduceSize)) {
            double remain = reduceSize - (height_ - minPadddingSize_);
            height_ = minPadddingSize_;
            return remain;
        }
        height_ -= reduceSize;
        return 0.0;
    };

private:
    bool isVertical_ = false;
    bool isSetSize_ = false;
    double minPadddingSize_;
};

class TextLayoutElement : public SecurityComponentLayoutElement {
public:
    TextLayoutElement() {};
    void Init(RefPtr<SecurityComponentLayoutProperty>& property,
        RefPtr<LayoutWrapper>& textWrap);
    ~TextLayoutElement() = default;

    double ShrinkWidth(double reduceSize) override;

    double ShrinkHeight(double reduceSize) override;

    bool GetCurrentTextSize(std::optional<SizeF>& currentTextSize, Dimension& currentFontSize);

    void DoMeasure(bool isVertical, float minWidth, float leftSpace);

    bool TryShrinkTextWidth(SizeF& point, SizeF& circlePoint, bool maxSpaceToShrink, float maxDistance,
        float threshold);

    float pow(float value)
    {
        return value * value;
    }

private:
    void UpdateSize(bool isWidth);
    void MeasureMinTextSize();
    void ChooseExactFontSize(RefPtr<TextLayoutProperty>& property, bool isWidth);
    std::optional<SizeF> GetMeasureTextSize(const std::string& data,
        const Dimension& fontSize, FontWeight fontWeight, float constraintWidth);
    void MeasureForWidth(float width);

    bool isExist_ = false;
    Dimension minFontSize_;
    Dimension defaultFontSize_;
    RefPtr<SecurityComponentLayoutProperty> secCompProperty_;
    RefPtr<LayoutWrapper> textWrap_;
    std::optional<SizeF> minTextSize_;
};
} // namespace OHOS::Ace::NG
#endif
