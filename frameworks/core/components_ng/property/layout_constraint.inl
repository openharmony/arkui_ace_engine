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

namespace OHOS::Ace::NG {
template<typename T>
void LayoutConstraintT<T>::ApplyAspectRatio(
    float ratio, const std::optional<CalcSize>& calcSize, bool greaterThanApiTen)
{
    if (!Positive(ratio)) {
        // just in case ratio is illegal value
        return;
    }
    std::optional<bool> useDefinedWidth;
    if (calcSize) {
        if (calcSize.value().Width()) {
            useDefinedWidth = true;
        } else if (calcSize.value().Height()) {
            useDefinedWidth = false;
        }
    }
    if (useDefinedWidth) {
        if (useDefinedWidth.value_or(false)) {
            if (selfIdealSize.Width()) {
                selfIdealSize.SetHeight(selfIdealSize.Width().value() / ratio);
            }
            minSize.SetHeight(minSize.Width() / ratio);
            maxSize.SetHeight(maxSize.Width() / ratio);
            ApplyAspectRatioToParentIdealSize(true, ratio);
            return;
        }
        if (selfIdealSize.Height()) {
            selfIdealSize.SetWidth(selfIdealSize.Height().value() * ratio);
        }
        minSize.SetWidth(minSize.Height() * ratio);
        maxSize.SetWidth(maxSize.Height() * ratio);
        ApplyAspectRatioToParentIdealSize(false, ratio);
        return;
    } else {
        if (selfIdealSize.Width()) {
            selfIdealSize.SetHeight(selfIdealSize.Width().value() / ratio);
            minSize.SetHeight(minSize.Width() / ratio);
            maxSize.SetHeight(maxSize.Width() / ratio);
            ApplyAspectRatioToParentIdealSize(true, ratio);
            return;
        }
        if (selfIdealSize.Height()) {
            selfIdealSize.SetWidth(selfIdealSize.Height().value() * ratio);
            minSize.SetWidth(minSize.Height() * ratio);
            maxSize.SetWidth(maxSize.Height() * ratio);
            ApplyAspectRatioToParentIdealSize(false, ratio);
            return;
        }
    }
    // after previous conditions, ideal size does not exist, we use max size to rule aspect ratio
    // but nothing can be done if both width and height are inf
    if (NearEqual(maxSize.Width(), Infinity<T>()) && NearEqual(maxSize.Height(), Infinity<T>())) {
        return;
    }
    ApplyAspectRatioByMaxSize(ratio, useDefinedWidth, greaterThanApiTen);
}

template<typename T>
void LayoutConstraintT<T>::ApplyAspectRatioToParentIdealSize(bool useWidth, float ratio)
{
    if (!Positive(ratio)) {
        return;
    }
    if (useWidth && parentIdealSize.Width()) {
        parentIdealSize.SetHeight(parentIdealSize.Width().value() / ratio);
        return;
    }
    if (!parentIdealSize.Height()) {
        return;
    }
    parentIdealSize.SetWidth(parentIdealSize.Height().value() * ratio);
}

template<typename T>
void LayoutConstraintT<T>::ApplyAspectRatioByMaxSize(
    float ratio, std::optional<bool> useDefinedWidth, bool greaterThanApiTen)
{
    if (!Positive(ratio)) {
        return;
    }
    if (useDefinedWidth) {
        ApplyAspectRatioWithCalcSize(ratio, useDefinedWidth.value());
        return;
    }
    ApplyAspectRatioWithoutCalcSize(ratio, greaterThanApiTen);
}

template<typename T>
void LayoutConstraintT<T>::ApplyAspectRatioWithCalcSize(float ratio, bool useDefinedWidth)
{
    if (!Positive(ratio)) {
        return;
    }
    if (useDefinedWidth) {
        minSize.SetHeight(minSize.Width() / ratio);
        maxSize.SetHeight(maxSize.Width() / ratio);
        percentReference.SetHeight(percentReference.Width() / ratio);
        ApplyAspectRatioToParentIdealSize(true, ratio);
        return;
    }
    minSize.SetWidth(minSize.Height() * ratio);
    maxSize.SetWidth(maxSize.Height() * ratio);
    percentReference.SetWidth(percentReference.Height() / ratio);
    ApplyAspectRatioToParentIdealSize(false, ratio);
}

template<typename T>
void LayoutConstraintT<T>::ApplyAspectRatioWithoutCalcSize(float ratio, bool greaterThanApiTen)
{
    if (!Positive(ratio)) {
        return;
    }
    if (greaterThanApiTen) {
        if (percentReference.Height() * ratio > maxSize.Width()) {
            minSize.SetHeight(minSize.Width() / ratio);
            maxSize.SetHeight(maxSize.Width() / ratio);
            percentReference.SetHeight(percentReference.Width() / ratio);
            ApplyAspectRatioToParentIdealSize(true, ratio);
            return;
        }
        if (percentReference.Width() / ratio > maxSize.Height()) {
            minSize.SetWidth(minSize.Height() * ratio);
            maxSize.SetWidth(maxSize.Height() * ratio);
            percentReference.SetWidth(percentReference.Height() * ratio);
            ApplyAspectRatioToParentIdealSize(false, ratio);
        }
        return;
    } else {
        if (maxSize.Width() < maxSize.Height()) {
            minSize.SetHeight(minSize.Width() / ratio);
            maxSize.SetHeight(maxSize.Width() / ratio);
            percentReference.SetHeight(percentReference.Width() / ratio);
            ApplyAspectRatioToParentIdealSize(true, ratio);
            return;
        }
    }
    minSize.SetWidth(minSize.Height() * ratio);
    maxSize.SetWidth(maxSize.Height() * ratio);
    percentReference.SetWidth(percentReference.Height() / ratio);
    ApplyAspectRatioToParentIdealSize(false, ratio);
}

template<typename T>
void LayoutConstraintT<T>::Reset()
{
    scaleProperty.Reset();
    minSize = { 0, 0 };
    maxSize = { Infinity<T>(), Infinity<T>() };
    percentReference = { 0, 0 };
    parentIdealSize.Reset();
    selfIdealSize.Reset();
}

template<typename T>
void LayoutConstraintT<T>::MinusPadding(const std::optional<T>& left, const std::optional<T>& right,
    const std::optional<T>& top, const std::optional<T>& bottom)
{
    minSize.MinusPadding(left, right, top, bottom);
    maxSize.MinusPadding(left, right, top, bottom);
    parentIdealSize.MinusPadding(left, right, top, bottom);
    selfIdealSize.MinusPadding(left, right, top, bottom);
    percentReference.MinusPadding(left, right, top, bottom);
}

template<typename T>
void LayoutConstraintT<T>::MinusPaddingToNonNegativeSize(const std::optional<T>& left, const std::optional<T>& right,
    const std::optional<T>& top, const std::optional<T>& bottom)
{
    minSize.MinusPaddingToNonNegative(left, right, top, bottom);
    maxSize.MinusPaddingToNonNegative(left, right, top, bottom);
    parentIdealSize.MinusPadding(left, right, top, bottom);
    selfIdealSize.MinusPadding(left, right, top, bottom);
    percentReference.MinusPaddingToNonNegative(left, right, top, bottom);
}

template<typename T>
std::string LayoutConstraintT<T>::ToString() const
{
    std::string str;
    str.append("minSize: [").append(minSize.ToString()).append("]");
    str.append("maxSize: [").append(maxSize.ToString()).append("]");
    str.append("percentReference: [").append(percentReference.ToString()).append("]");
    str.append("parentIdealSize: [").append(parentIdealSize.ToString()).append("]");
    str.append("selfIdealSize: [").append(selfIdealSize.ToString()).append("]");
    return str;
}

template<typename T>
SizeF LayoutConstraintT<T>::Constrain(const SizeF& size) const
{
    SizeF constrainSize;
    constrainSize.SetWidth(std::clamp(size.Width(), minSize.Width(), maxSize.Width()));
    constrainSize.SetHeight(std::clamp(size.Height(), minSize.Height(), maxSize.Height()));
    return constrainSize;
}
} // namespace OHOS::Ace::NG