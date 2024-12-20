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

#include "reverse_converter.h"

namespace {
    constexpr int32_t STD_TM_START_YEAR = 1900;
} // namespace

namespace OHOS::Ace::NG::Converter {
void *ConvContext::Allocate(std::size_t size)
{
    storage_.push_back(std::make_unique<std::byte[]>(size));
    return storage_.back().get();
}

Ark_String ConvContext::Store(const std::string_view& src)
{
    auto ptr = static_cast<char *>(Allocate(src.length() + 1));
    std::copy(src.begin(), src.end(), ptr);
    ptr[src.length()] = 0;
    Ark_String result;
    result.chars = ptr;
    result.length = src.length();
    return result;
}

void AssignArkValue(Ark_Area& dst, const BaseEventInfo& src)
{
    const auto& localOffset = src.GetTarget().area.GetOffset();
    const auto& origin = src.GetTarget().origin;
    dst.position.x = Converter::ArkValue<Opt_Length>(localOffset.GetX().ConvertToVp());
    dst.position.y = Converter::ArkValue<Opt_Length>(localOffset.GetY().ConvertToVp());
    dst.globalPosition.x = Converter::ArkValue<Opt_Length>(
        origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp());
    dst.globalPosition.y = Converter::ArkValue<Opt_Length>(
        origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp());
    dst.width = Converter::ArkValue<Ark_Length>(src.GetTarget().area.GetWidth().ConvertToVp());
    dst.height = Converter::ArkValue<Ark_Length>(src.GetTarget().area.GetHeight().ConvertToVp());
}

void AssignArkValue(Ark_TimePickerResult& dst, const std::string& src)
{
    auto data = JsonUtil::ParseJsonString(src);
    auto hour = data->GetValue("hour")->GetInt();
    auto minute = data->GetValue("minute")->GetInt();
    auto second = data->GetValue("second")->GetInt();
    dst = {
        .hour = ArkValue<Ark_Number>(hour),
        .minute = ArkValue<Ark_Number>(minute),
        .second = ArkValue<Ark_Number>(second),
    };
}

void AssignArkValue(Ark_LengthMetrics& dst, const Dimension& src)
{
    AssignArkValue(dst.value, src.Value());
    switch (src.Unit()) {
        case DimensionUnit::PX: dst.unit = ARK_LENGTH_UNIT_PX; break;
        case DimensionUnit::VP: dst.unit = ARK_LENGTH_UNIT_VP; break;
        case DimensionUnit::FP: dst.unit = ARK_LENGTH_UNIT_FP; break;
        case DimensionUnit::PERCENT: dst.unit = ARK_LENGTH_UNIT_PERCENT; break;
        case DimensionUnit::LPX: dst.unit = ARK_LENGTH_UNIT_LPX; break;
        default:
            AssignArkValue(dst.value, 0.0);
            dst.unit = ARK_LENGTH_UNIT_VP;
    }
}

void AssignArkValue(Ark_VisibleListContentInfo& dst, const ListItemIndex& src)
{
    dst.index = ArkValue<Ark_Number>(src.index);
    dst.itemGroupArea = src.area < 0 ?
        ArkValue<Opt_ListItemGroupArea>(Ark_Empty{}) : ArkValue<Opt_ListItemGroupArea>(src.area);
    dst.itemIndexInGroup = src.indexInGroup < 0 ?
        ArkValue<Opt_Number>(Ark_Empty{}) : ArkValue<Opt_Number>(src.indexInGroup);
}

void AssignArkValue(Ark_Tuple_Dimension_Dimension& dst, const std::pair<const Dimension, const Dimension>& src)
{
    dst.value0 = ArkValue<Ark_Length>(src.first);
    dst.value1 = ArkValue<Ark_Length>(src.second);
}

void AssignArkValue(Ark_ItemDragInfo& dst, const ItemDragInfo& src)
{
    dst.x = ArkValue<Ark_Number>(static_cast<float>(src.GetX()));
    dst.y = ArkValue<Ark_Number>(static_cast<float>(src.GetY()));
}

void AssignArkValue(Ark_EdgeEffectOptions& dst, const bool& src)
{
    dst.alwaysEnabled = src;
}

void AssignArkValue(Ark_StyledString& dst, const StyledStringPeer& src)
{
    dst.ptr = reinterpret_cast<Ark_NativePointer>(&const_cast<StyledStringPeer&>(src));
}

void AssignArkValue(Ark_Length& dst, const double& src)
{
    dst.type = ARK_RUNTIME_NUMBER;
    dst.value = src;
    dst.unit = static_cast<int32_t>(OHOS::Ace::DimensionUnit::VP);
}

void AssignArkValue(Ark_Length& dst, const Dimension& src)
{
    dst.type = ARK_RUNTIME_NUMBER;
    dst.value = src.Unit() == DimensionUnit::PERCENT ? src.Value() * 100.f : src.Value();
    dst.unit = static_cast<int32_t>(src.Unit());
}

void AssignArkValue(Ark_Length& dst, const float& src)
{
    dst.type = ARK_RUNTIME_NUMBER;
    dst.value = src;
    dst.unit = static_cast<int32_t>(OHOS::Ace::DimensionUnit::VP);
}

void AssignArkValue(Ark_Number& dst, const int32_t& src)
{
    dst.tag = ARK_TAG_INT32;
    dst.i32 = src;
}

void AssignArkValue(Ark_Number& dst, const long& src)
{
    LOGE("Ark_Number doesn`t support long");
    dst.tag = ARK_TAG_INT32;
    dst.i32 = static_cast<int32_t>(src);
}

void AssignArkValue(Ark_Number& dst, const long long& src)
{
    LOGE("Ark_Number doesn`t support long long");
    dst.tag = ARK_TAG_INT32;
    dst.i32 = static_cast<int32_t>(src);
}

void AssignArkValue(Ark_Number& dst, const uint32_t& src)
{
    dst.tag = ARK_TAG_INT32;
    dst.i32 = src;
}

void AssignArkValue(Ark_Number& dst, const float& src)
{
    dst.tag = ARK_TAG_FLOAT32;
    dst.f32 = src;
}

void AssignArkValue(Ark_Number& dst, const double& src)
{
    dst.tag = ARK_TAG_FLOAT32;
    dst.f32 = static_cast<float>(src);
}

void AssignArkValue(Ark_PreviewText& dst, const PreviewText& src)
{
    dst.offset = ArkValue<Ark_Number>(src.offset);
    dst.value = ArkValue<Ark_String>(src.value);
}

void AssignArkValue(Ark_Length& dst, const int& src)
{
    dst.type = ARK_RUNTIME_NUMBER;
    dst.value = src;
    dst.unit = static_cast<int32_t>(OHOS::Ace::DimensionUnit::PX);
}

void AssignArkValue(Ark_Number& dst, const Dimension& src)
{
    auto value = static_cast<float>(src.ConvertToVp());
    AssignArkValue(dst, value);
}

void AssignArkValue(Ark_Date& dst, const PickerDate& src)
{
    const auto start = PickerDate(1970, 1, 1);
    const auto end = PickerDate(2100, 12, 31);
    const int64_t secToMillisec = 1000;
    auto date = src;
    if (src.GetYear() < start.GetYear() || src.GetYear() > end.GetYear()) {
        date = start;
    } else if (src.GetMonth() < start.GetMonth() || src.GetMonth() > end.GetMonth()) {
        date = start;
    } else if (src.GetDay() < start.GetDay() || src.GetDay() > PickerDate::GetMaxDay(src.GetYear(), src.GetMonth())) {
        date = start;
    }
    std::tm tm {};
    tm.tm_year = date.GetYear() - STD_TM_START_YEAR; // tm_year is years since 1900
    tm.tm_mon = date.GetMonth() - 1; // tm_mon from 0 to 11
    tm.tm_mday = date.GetDay();
    time_t time = std::mktime(&tm);
    dst = reinterpret_cast<Ark_Date>(time * secToMillisec);
}

void AssignArkValue(Ark_Date& dst, const std::string& src)
{
    auto json = JsonUtil::ParseJsonString(src);
    if (json && !json->IsNull()) {
        uint32_t year = 0;
        auto yearJson = json->GetValue("year");
        if (yearJson && yearJson->IsNumber()) {
            year = yearJson->GetUInt();
        }
        uint32_t month = 0;
        auto monthJson = json->GetValue("month");
        if (monthJson && monthJson->IsNumber()) {
            month = monthJson->GetUInt();
        }
        uint32_t day = 0;
        auto dayJson = json->GetValue("day");
        if (dayJson && dayJson->IsNumber()) {
            day = dayJson->GetUInt();
        }
        auto pickerDate = PickerDate(year, month, day);
        dst = ArkValue<Ark_Date>(pickerDate);
    }
}
} // namespace OHOS::Ace::NG::Converter
