/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/property/measure_property.h"

#include "core/common/ace_application_info.h"
#include "core/pipeline/pipeline_base.h"
#include "json/json_util.h"
#include "ui/base/geometry/dimension.h"
#include "ui/base/geometry/ng/offset_t.h"
#include "ui/base/geometry/ng/size_t.h"
#include "ui/base/inspector_filter.h"
#include "ui/base/utils/utils.h"
#include "ui/properties/ng/calc_length.h"
#include "ui/resource/resource_object.h"
#include "ui/view/ui_context.h"

namespace OHOS::Ace::NG {

void CalcSize::Reset()
{
    width_.reset();
    height_.reset();
}

bool CalcSize::IsValid() const
{
    return (width_ && height_) && (width_->GetDimension().Unit() != DimensionUnit::AUTO &&
                                      height_->GetDimension().Unit() != DimensionUnit::AUTO);
}

void CalcSize::SetSizeT(const CalcSize& Size)
{
    width_ = Size.Width();
    height_ = Size.Height();
}

bool CalcSize::UpdateSizeWithCheck(const CalcSize& size)
{
    if ((width_ == size.width_) && ((height_ == size.height_))) {
        return false;
    }
    if (size.width_) {
        width_ = size.width_;
    }
    if (size.height_) {
        height_ = size.height_;
    }
    return true;
}

bool CalcSize::ClearSize(bool clearWidth, bool clearHeight)
{
    bool changed = false;
    if (clearWidth && width_.has_value()) {
        width_.reset();
        changed = true;
    }
    if (clearHeight && height_.has_value()) {
        height_.reset();
        changed = true;
    }
    return changed;
}

bool CalcSize::WidthFixed(bool checkPercent) const
{
    return width_ && (!checkPercent || width_->GetDimension().Unit() != DimensionUnit::PERCENT);
}

bool CalcSize::HeightFixed(bool checkPercent) const
{
    return height_ && (!checkPercent || height_->GetDimension().Unit() != DimensionUnit::PERCENT);
}

bool CalcSize::PercentWidth() const
{
    return width_ && (width_->GetDimension().Unit() == DimensionUnit::PERCENT ||
                         (width_->GetDimension().Unit() == DimensionUnit::CALC &&
                             width_->CalcValue().find("%") != std::string::npos));
}

bool CalcSize::PercentHeight() const
{
    return height_ && (height_->GetDimension().Unit() == DimensionUnit::PERCENT ||
                          (height_->GetDimension().Unit() == DimensionUnit::CALC &&
                              height_->CalcValue().find("%") != std::string::npos));
}

std::string CalcSize::ToString() const
{
    static const int32_t precision = 2;
    std::stringstream ss;
    ss << "[" << std::fixed << std::setprecision(precision);
    ss << (width_ ? width_->ToString() : "NA");
    ss << " x ";
    ss << (height_ ? height_->ToString() : "NA");
    ss << "]";
    std::string output = ss.str();
    return output;
}

bool CalcSize::IsDimensionUnitAuto() const
{
    return IsWidthDimensionUnitAuto() || IsHeightDimensionUnitAuto();
}

bool CalcSize::IsWidthDimensionUnitAuto() const
{
    return width_ && width_->GetDimension().Unit() == DimensionUnit::AUTO;
}

bool CalcSize::IsHeightDimensionUnitAuto() const
{
    return height_ && height_->GetDimension().Unit() == DimensionUnit::AUTO;
}

void MeasureProperty::Reset()
{
    minSize.reset();
    maxSize.reset();
    selfIdealSize.reset();
    preMinSize.reset();
    preMaxSize.reset();
    preSelfIdealSize.reset();
}

bool MeasureProperty::UpdateSelfIdealSizeWithCheck(const CalcSize& size)
{
    if (selfIdealSize == size) {
        return false;
    }
    if (selfIdealSize.has_value()) {
        return selfIdealSize->UpdateSizeWithCheck(size);
    }
    selfIdealSize = size;
    return true;
}

bool MeasureProperty::ClearSelfIdealSize(bool clearWidth, bool clearHeight)
{
    if (selfIdealSize.has_value()) {
        return selfIdealSize->ClearSize(clearWidth, clearHeight);
    }
    return false;
}

bool MeasureProperty::UpdateMaxSizeWithCheck(const CalcSize& size)
{
    if (maxSize == size) {
        return false;
    }
    if (maxSize.has_value()) {
        return maxSize->UpdateSizeWithCheck(size);
    }
    maxSize = size;
    return true;
}

bool MeasureProperty::UpdateMinSizeWithCheck(const CalcSize& size)
{
    if (minSize == size) {
        return false;
    }
    if (minSize.has_value()) {
        return minSize->UpdateSizeWithCheck(size);
    }
    minSize = size;
    return true;
}

bool MeasureProperty::PercentWidth() const
{
    if (selfIdealSize.has_value()) {
        return selfIdealSize->PercentWidth();
    }
    if (maxSize.has_value()) {
        return maxSize->PercentWidth();
    }
    if (minSize.has_value()) {
        return minSize->PercentWidth();
    }
    return false;
}

bool MeasureProperty::PercentHeight() const
{
    if (selfIdealSize.has_value()) {
        return selfIdealSize->PercentHeight();
    }
    if (maxSize.has_value()) {
        return maxSize->PercentHeight();
    }
    if (minSize.has_value()) {
        return minSize->PercentHeight();
    }
    return false;
}

std::string MeasureProperty::ToString() const
{
    std::string str;
    str.append("minSize: [").append(minSize.has_value() ? minSize->ToString() : "NA").append("]");
    str.append("maxSize: [").append(maxSize.has_value() ? maxSize->ToString() : "NA").append("]");
    str.append("selfIdealSize: [").append(selfIdealSize.has_value() ? selfIdealSize->ToString() : "NA").append("]");
    return str;
}

void MeasureProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    // this may affect XTS, check later.
    auto context = PipelineBase::GetCurrentContext();
    if (context && context->GetMinPlatformVersion() < static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN)) {
#if !defined(PREVIEW)
        /* no fixed attr below */
        if (!filter.IsFastFilter()) {
            std::string width = selfIdealSize.has_value() ?
                (selfIdealSize.value().Width().has_value() ?
                selfIdealSize.value().Width().value().ToString() : "-") : "-";
            std::string height = selfIdealSize.has_value() ?
                (selfIdealSize.value().Height().has_value() ?
                selfIdealSize.value().Height().value().ToString() : "-") : "-";
            json->PutExtAttr("width", width.c_str(), filter);
            json->PutExtAttr("height", height.c_str(), filter);

            auto jsonSize = JsonUtil::Create(true);
            jsonSize->Put("width", width.c_str());
            jsonSize->Put("height", height.c_str());
            json->PutExtAttr("size", jsonSize, filter);
        }
#else
        ToJsonValue_GetJsonSize(json, filter);
#endif
    } else {
        ToJsonValue_GetJsonSize(json, filter);
    }

    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto jsonConstraintSize = JsonUtil::Create(true);
    jsonConstraintSize->Put("minWidth",
        minSize.value_or(CalcSize()).Width().value_or(CalcLength(0, DimensionUnit::VP)).ToString().c_str());
    jsonConstraintSize->Put("minHeight",
        minSize.value_or(CalcSize()).Height().value_or(CalcLength(0, DimensionUnit::VP)).ToString().c_str());
    jsonConstraintSize->Put("maxWidth", maxSize.value_or(CalcSize())
                                            .Width()
                                            .value_or(CalcLength(Infinity<double>(), DimensionUnit::VP))
                                            .ToString()
                                            .c_str());
    jsonConstraintSize->Put("maxHeight", maxSize.value_or(CalcSize())
                                                .Height()
                                                .value_or(CalcLength(Infinity<double>(), DimensionUnit::VP))
                                                .ToString()
                                                .c_str());
    json->PutExtAttr("constraintSize", jsonConstraintSize->ToString().c_str(), filter);
}

void MeasureProperty::ToJsonValue_GetJsonSize(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto jsonSize = JsonUtil::Create(true);
    if (selfIdealSize.has_value()) {
        if (selfIdealSize.value().Width().has_value()) {
            auto widthStr = selfIdealSize.value().Width().value().ToString();
            json->PutExtAttr("width", widthStr.c_str(), filter);
            jsonSize->Put("width", widthStr.c_str());
        }
        if (selfIdealSize.value().Height().has_value()) {
            auto heightStr = selfIdealSize.value().Height().value().ToString();
            json->PutExtAttr("height", heightStr.c_str(), filter);
            jsonSize->Put("height", heightStr.c_str());
        }
    }
    json->PutExtAttr("size", jsonSize, filter);
}

MeasureProperty MeasureProperty::FromJson(const std::unique_ptr<JsonValue>& json)
{
    MeasureProperty ans;
    auto width = json->GetString("width");
    auto height = json->GetString("height");
    if (width != "-" || height != "-") {
        ans.selfIdealSize =
            CalcSize(width != "-" ? std::optional<CalcLength>(Dimension::FromString(width)) : std::nullopt,
                height != "-" ? std::optional<CalcLength>(Dimension::FromString(height)) : std::nullopt);
    }
    return ans;
}

// ============================================================================
// PaddingPropertyT<T> template method implementations
// ============================================================================

template<typename T>
ACE_FORCE_EXPORT
void PaddingPropertyT<T>::SetEdges(const T& padding)
{
    left = padding;
    right = padding;
    top = padding;
    bottom = padding;
}

template<typename T>
ACE_FORCE_EXPORT
void PaddingPropertyT<T>::SetEdges(const T& leftValue, const T& rightValue, const T& topValue, const T& bottomValue)
{
    left = leftValue;
    right = rightValue;
    top = topValue;
    bottom = bottomValue;
}

template<typename T>
ACE_FORCE_EXPORT
bool PaddingPropertyT<T>::operator==(const PaddingPropertyT& value) const
{
    return (left == value.left) && (right == value.right) && (top == value.top) && (bottom == value.bottom);
}

template<typename T>
ACE_FORCE_EXPORT
bool PaddingPropertyT<T>::operator!=(const PaddingPropertyT& value) const
{
    return !(*this == value);
}

template<typename T>
ACE_FORCE_EXPORT
bool PaddingPropertyT<T>::UpdateWithCheck(const PaddingPropertyT& value)
{
    if (value.start.has_value() || value.end.has_value()) {
        return UpdateLocalizedPadding(value);
    }
    start.reset();
    end.reset();
    if (*this != value) {
        left = value.left;
        right = value.right;
        top = value.top;
        bottom = value.bottom;
        return true;
    }
    return false;
}

template<typename T>
ACE_FORCE_EXPORT
bool PaddingPropertyT<T>::UpdateLocalizedPadding(const PaddingPropertyT& value)
{
    bool needUpdate = false;
    if (value.start.has_value() && start != value.start) {
        start = value.start;
        needUpdate = true;
    }
    if (value.end.has_value() && end != value.end) {
        end = value.end;
        needUpdate = true;
    }
    if (value.top.has_value() && top != value.top && (value.start.has_value() || value.end.has_value())) {
        top = value.top;
        needUpdate = true;
    }
    if (value.bottom.has_value() && bottom != value.bottom && (value.start.has_value() || value.end.has_value())) {
        bottom = value.bottom;
        needUpdate = true;
    }
    if (value.left.has_value() && left != value.left) {
        left = value.left;
        needUpdate = true;
    }
    if (value.right.has_value() && right != value.right) {
        right = value.right;
        needUpdate = true;
    }
    checkNeedReset(value);
    return needUpdate;
}

template<typename T>
ACE_FORCE_EXPORT
void PaddingPropertyT<T>::checkNeedReset(const PaddingPropertyT& value)
{
    RefPtr<OHOS::Ace::Kit::UIContext> uiContext = OHOS::Ace::Kit::UIContext::Current();
    bool isGreatThanSixteen = false;
    if (uiContext) {
        isGreatThanSixteen = uiContext->GreatOrEqualTargetAPIVersion(API_VERSION_SIXTEEN);
    }

    if (!value.start.has_value() && start.has_value() && isGreatThanSixteen) {
        start.reset();
    }
    if (!value.end.has_value() && end.has_value() && isGreatThanSixteen) {
        end.reset();
    }
    if (!value.top.has_value() && top.has_value() && isGreatThanSixteen) {
        top.reset();
    }
    if (!value.bottom.has_value() && bottom.has_value() && isGreatThanSixteen) {
        bottom.reset();
    }
}

template<typename T>
ACE_FORCE_EXPORT
std::string PaddingPropertyT<T>::ToString() const
{
    std::string str;
    str.append("[").append(left.has_value() ? left->ToString() : "NA");
    str.append(",").append(right.has_value() ? right->ToString() : "NA");
    str.append(",").append(top.has_value() ? top->ToString() : "NA");
    str.append(",").append(bottom.has_value() ? bottom->ToString() : "NA").append("]");
    return str;
}

template<typename T>
ACE_FORCE_EXPORT
std::string PaddingPropertyT<T>::ToJsonString() const
{
    if (top == right && right == bottom && bottom == left) {
        if (top.has_value()) {
            return top->ToString();
        }
        return "0.0";
    }
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("top", top.has_value() ? top->ToString().c_str() : T{}.ToString().c_str());
    jsonValue->Put("right", right.has_value() ? right->ToString().c_str() : T{}.ToString().c_str());
    jsonValue->Put("bottom", bottom.has_value() ? bottom->ToString().c_str() : T{}.ToString().c_str());
    jsonValue->Put("left", left.has_value() ? left->ToString().c_str() : T{}.ToString().c_str());
    return jsonValue->ToString();
}

template<typename T>
PaddingPropertyT<T> PaddingPropertyT<T>::FromJsonString(const std::string& str)
{
    PaddingPropertyT property;

    if (str.empty()) {
        return property;
    }

    if (str[0] >= '0' && str[0] <= '9') {
        property.top = property.right = property.bottom = property.left = T::FromString(str);
    } else if (str[0] == '{') {
        auto json = JsonUtil::ParseJsonString(str);
        if (!json->IsValid()) {
            return property;
        }
        property.top = T::FromString(json->GetString("top"));
        property.right = T::FromString(json->GetString("right"));
        property.bottom = T::FromString(json->GetString("bottom"));
        property.left = T::FromString(json->GetString("left"));
    }

    return property;
}

template<typename T>
void PaddingPropertyT<T>::AddResource(
    const std::string& key,
    const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&, PaddingPropertyT&)>&& updateFunc)
{
    if (resObj == nullptr || !updateFunc) {
        return;
    }
    resMap_[key] = {resObj, std::move(updateFunc)};
}

template<typename T>
void PaddingPropertyT<T>::ReloadResources()
{
    for (const auto& [key, resourceUpdater] : resMap_) {
        resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
    }
}

// Explicit template instantiation
template struct PaddingPropertyT<CalcLength>;
template struct PaddingPropertyT<Dimension>;

// ============================================================================
// PaddingPropertyF class method implementations
// ============================================================================

bool PaddingPropertyF::operator==(const PaddingPropertyF& value) const
{
    if (left.has_value() ^ value.left.has_value()) {
        return false;
    }
    if (!NearEqual(left.value_or(0), value.left.value_or(0))) {
        return false;
    }
    if (right.has_value() ^ value.right.has_value()) {
        return false;
    }
    if (!NearEqual(right.value_or(0), value.right.value_or(0))) {
        return false;
    }
    if (top.has_value() ^ value.top.has_value()) {
        return false;
    }
    if (!NearEqual(top.value_or(0), value.top.value_or(0))) {
        return false;
    }
    if (bottom.has_value() ^ value.bottom.has_value()) {
        return false;
    }
    if (!NearEqual(bottom.value_or(0), value.bottom.value_or(0))) {
        return false;
    }
    return true;
}

std::string PaddingPropertyF::ToString() const
{
    std::string str;
    str.append("[").append(left.has_value() ? std::to_string(left.value()) : "NA");
    str.append(",").append(right.has_value() ? std::to_string(right.value()) : "NA");
    str.append(",").append(top.has_value() ? std::to_string(top.value()) : "NA");
    str.append(",").append(bottom.has_value() ? std::to_string(bottom.value()) : "NA").append("]");
    return str;
}

std::string PaddingPropertyF::ToJsonString() const
{
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("top", top.has_value() ? std::to_string(top.value()).c_str() : BORDERZERO.c_str());
    jsonValue->Put("right", right.has_value() ? std::to_string(right.value()).c_str() : BORDERZERO.c_str());
    jsonValue->Put("bottom", bottom.has_value() ? std::to_string(bottom.value()).c_str() : BORDERZERO.c_str());
    jsonValue->Put("left", left.has_value() ? std::to_string(left.value()).c_str() : BORDERZERO.c_str());
    return jsonValue->ToString();
}

ACE_FORCE_EXPORT
float PaddingPropertyF::Width() const
{
    return left.value_or(0.0f) + right.value_or(0.0f);
}

ACE_FORCE_EXPORT
float PaddingPropertyF::Height() const
{
    return top.value_or(0.0f) + bottom.value_or(0.0f);
}

SizeF PaddingPropertyF::Size() const
{
    return SizeF(Width(), Height());
}

OffsetF PaddingPropertyF::Offset() const
{
    return OffsetF(left.value_or(0.0f), top.value_or(0.0f));
}

OffsetF PaddingPropertyF::MirrorOffset() const
{
    return OffsetF(-right.value_or(0.0f), top.value_or(0.0f));
}

bool PaddingPropertyF::Empty()
{
    return !left.has_value() && !right.has_value() && !top.has_value() && !bottom.has_value();
}

bool PaddingPropertyF::HasValue() const
{
    return (left && !NearZero(left.value())) || (right && !NearZero(right.value())) ||
        (top && !NearZero(top.value())) || (bottom && !NearZero(bottom.value()));
}

PaddingPropertyF PaddingPropertyF::Plus(const PaddingPropertyF& another, bool skipNullOpt)
{
    return Calculate(another, skipNullOpt, true);
}

PaddingPropertyF PaddingPropertyF::Minus(const PaddingPropertyF& another, bool skipNullOpt) const
{
    return Calculate(another, skipNullOpt, false);
}

bool PaddingPropertyF::AllSidesFilled(bool checkZero)
{
    // checking all sides has values and not zero
    if (checkZero) {
        return !NearZero(left.value_or(0.0f)) && !NearZero(right.value_or(0.0f)) && !NearZero(top.value_or(0.0f)) &&
               !NearZero(bottom.value_or(0.0f));
    }
    return left.has_value() && right.has_value() && top.has_value() && bottom.has_value();
}

bool PaddingPropertyF::OptionalValueCover(const PaddingPropertyF& another)
{
    if (another.left.has_value() && !left.has_value()) {
        return false;
    }
    if (another.right.has_value() && !right.has_value()) {
        return false;
    }
    if (another.top.has_value() && !top.has_value()) {
        return false;
    }
    if (another.bottom.has_value() && !bottom.has_value()) {
        return false;
    }
    return true;
}

void PaddingPropertyF::Reset()
{
    left.reset();
    right.reset();
    top.reset();
    bottom.reset();
}

PaddingPropertyF PaddingPropertyF::Calculate(const PaddingPropertyF& another, bool skipNullOpt, bool isAdd) const
{
    PaddingPropertyF result;
    // skipNullOpt needs at least one padding has value to keep nullopt if two sides both null,
    // !skipNullOpt needs both sides has value
    int32_t factor = isAdd ? 1.0f : -1.0f;
    // to resolve cyclomatic complexity
    bool calculateCondition = (!skipNullOpt && left.has_value() && another.left.has_value()) ||
                              (skipNullOpt && (left.has_value() || another.left.has_value()));
    if (calculateCondition) {
        result.left = left.value_or(0.0f) + factor * another.left.value_or(0.0f);
    }
    calculateCondition = (!skipNullOpt && right.has_value() && another.right.has_value()) ||
                         (skipNullOpt && (right.has_value() || another.right.has_value()));
    if (calculateCondition) {
        result.right = right.value_or(0.0f) + factor * another.right.value_or(0.0f);
    }
    calculateCondition = (!skipNullOpt && top.has_value() && another.top.has_value()) ||
                         (skipNullOpt && (top.has_value() || another.top.has_value()));
    if (calculateCondition) {
        result.top = top.value_or(0.0f) + factor * another.top.value_or(0.0f);
    }
    calculateCondition = (!skipNullOpt && bottom.has_value() && another.bottom.has_value()) ||
                         (skipNullOpt && (bottom.has_value() || another.bottom.has_value()));
    if (calculateCondition) {
        result.bottom = bottom.value_or(0.0f) + factor * another.bottom.value_or(0.0f);
    }
    return result;
}

} // namespace OHOS::Ace::NG
