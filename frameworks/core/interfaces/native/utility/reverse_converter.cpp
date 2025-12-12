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

#include "base/utils/string_utils.h"
#include "core/interfaces/native/implementation/background_color_style_peer.h"
#include "core/interfaces/native/implementation/base_gesture_event_peer.h"
#include "core/interfaces/native/implementation/baseline_offset_style_peer.h"
#include "core/interfaces/native/implementation/custom_span_peer.h"
#include "core/interfaces/native/implementation/decoration_style_peer.h"
#include "core/interfaces/native/implementation/image_attachment_peer.h"
#include "core/interfaces/native/implementation/gesture_style_peer.h"
#include "core/interfaces/native/implementation/length_metrics_peer.h"
#include "core/interfaces/native/implementation/letter_spacing_style_peer.h"
#include "core/interfaces/native/implementation/line_height_style_peer.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/implementation/paragraph_style_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/implementation/text_menu_item_id_peer.h"
#include "core/interfaces/native/implementation/text_shadow_style_peer.h"
#include "core/interfaces/native/implementation/text_style_peer.h"
#include "core/interfaces/native/implementation/url_style_peer.h"
#include "core/interfaces/native/implementation/user_data_span_holder.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "converter.h"
#include "validators.h"

namespace OHOS::Ace {
namespace {
const std::string YEAR = "year";
const std::string MONTH = "month";
const std::string DAY = "day";
const std::string HOUR = "hour";
const std::string MINUTE = "minute";
const std::string SECOND = "second";
const int32_t STD_TM_START_YEAR = 1900;
const int32_t SEC_TO_MILLISEC = 1000;
} // namespace
} // namespace OHOS::Ace

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

void ConvContext::Clear()
{
    storage_.clear();
}

void AssignArkValue(Ark_Int32& dst, const uint32_t& src)
{
    dst = static_cast<Ark_Int32>(src);
}

void AssignArkValue(Ark_Int32& dst, const Dimension& src)
{
    auto value = static_cast<uint32_t>(src.ConvertToVp());
    AssignArkValue(dst, value);
}

void AssignArkValue(Ark_String& dst, const FONT_FEATURES_LIST& src, ConvContext *ctx)
{
    CHECK_NULL_VOID(src.size());
    JsonValue jsonValue;
    for (const auto& it : src) {
        jsonValue.Put((it.first.c_str()), it.second);
    }
    std::string list = jsonValue.ToString();
    dst = Converter::ArkValue<Ark_String>(list, ctx);
}

void AssignArkValue(Ark_String& dst, const std::u16string& src, ConvContext *ctx)
{
    AssignArkValue(dst, StringUtils::Str16ToStr8(src), ctx);
}

void AssignArkValue(Ark_Area& dst, const BaseEventInfo& src, ConvContext *ctx)
{
    const auto& localOffset = src.GetTarget().area.GetOffset();
    const auto& origin = src.GetTarget().origin;
    dst.position.x = Converter::ArkValue<Opt_Length>(localOffset.GetX().ConvertToVp(), ctx);
    dst.position.y = Converter::ArkValue<Opt_Length>(localOffset.GetY().ConvertToVp(), ctx);
    dst.globalPosition.x = Converter::ArkValue<Opt_Length>(
        origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp(), ctx);
    dst.globalPosition.y = Converter::ArkValue<Opt_Length>(
        origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp(), ctx);
    dst.width = Converter::ArkValue<Ark_Length>(src.GetTarget().area.GetWidth().ConvertToVp(), ctx);
    dst.height = Converter::ArkValue<Ark_Length>(src.GetTarget().area.GetHeight().ConvertToVp(), ctx);
}

void AssignArkValue(Ark_DragEvent& dragEvent, const RefPtr<OHOS::Ace::DragEvent>& info)
{
    const auto peer = PeerUtils::CreatePeer<DragEventPeer>();
    peer->dragInfo = info;
    dragEvent = peer;
}

void AssignArkValue(Ark_TimePickerResult& dst, const std::string& src)
{
    auto data = JsonUtil::ParseJsonString(src);
    auto hour = data->GetValue(HOUR)->GetInt();
    auto minute = data->GetValue(MINUTE)->GetInt();
    auto second = data->GetValue(SECOND)->GetInt();
    dst = {
        .hour = ArkValue<Ark_Int32>(hour),
        .minute = ArkValue<Ark_Int32>(minute),
        .second = ArkValue<Ark_Int32>(second),
    };
}

void AssignArkValue(Ark_font_UIFontFallbackInfo& dst, const FallbackInfo& src, ConvContext* ctx)
{
    dst.family = Converter::ArkValue<Ark_String>(src.familyName, ctx);
    dst.language = Converter::ArkValue<Ark_String>(src.font, ctx);
}

void AssignArkValue(Ark_font_UIFontFallbackGroupInfo& dst, const FallbackGroup& src, ConvContext* ctx)
{
    dst.fontSetName = Converter::ArkValue<Ark_String>(src.groupName, ctx);
    dst.fallback = Converter::ArkValue<Array_font_UIFontFallbackInfo>(src.fallbackInfoSet, ctx);
}

void AssignArkValue(Ark_font_UIFontAdjustInfo& dst, const AdjustInfo& src)
{
    dst.weight = Converter::ArkValue<Ark_Float64>(src.origValue);
    dst.to = Converter::ArkValue<Ark_Int32>(src.newValue);
}

void AssignArkValue(Ark_font_UIFontAliasInfo& dst, const AliasInfo& src, ConvContext* ctx)
{
    dst.name = Converter::ArkValue<Ark_String>(src.familyName, ctx);
    dst.weight = Converter::ArkValue<Ark_Float64>(src.weight);
}

void AssignArkValue(Ark_font_UIFontGenericInfo& dst, const FontGenericInfo& src, ConvContext* ctx)
{
    dst.family = Converter::ArkValue<Ark_String>(src.familyName, ctx);
    dst.alias = Converter::ArkValue<Array_font_UIFontAliasInfo>(src.aliasSet, ctx);
    dst.adjust = Converter::ArkValue<Array_font_UIFontAdjustInfo>(src.adjustSet, ctx);
}

void AssignArkValue(Ark_font_UIFontConfig& dst, const FontConfigJsonInfo& src, ConvContext* ctx)
{
    dst.fontDir = Converter::ArkValue<Array_String>(src.fontDirSet, ctx);
    dst.generic = Converter::ArkValue<Array_font_UIFontGenericInfo>(src.genericSet, ctx);
    dst.fallbackGroups = Converter::ArkValue<Array_font_UIFontFallbackGroupInfo>(src.fallbackGroupSet, ctx);
}

void AssignArkValue(Ark_TextMenuItem& dst, const NG::MenuItemParam& src, ConvContext* ctx)
{
    if (src.menuOptionsParam.content.has_value()) {
        dst.content = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(src.menuOptionsParam.content.value(), ctx);
    } else {
        dst.content = Converter::ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr);
    }
    dst.icon = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(src.menuOptionsParam.icon, ctx);
    dst.id = PeerUtils::CreatePeer<TextMenuItemIdPeer>(src.menuOptionsParam.id);
    dst.labelInfo = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(src.menuOptionsParam.labelInfo, ctx);
}

void AssignArkValue(Ark_TextMetrics& dst, const OHOS::Ace::TextMetrics& src)
{
    dst.actualBoundingBoxAscent = Converter::ArkValue<Ark_Float64>(src.actualBoundingBoxAscent);
    dst.actualBoundingBoxDescent = Converter::ArkValue<Ark_Float64>(src.actualBoundingBoxDescent);
    dst.actualBoundingBoxLeft = Converter::ArkValue<Ark_Float64>(src.actualBoundingBoxLeft);
    dst.actualBoundingBoxRight = Converter::ArkValue<Ark_Float64>(src.actualBoundingBoxRight);
    dst.alphabeticBaseline = Converter::ArkValue<Ark_Float64>(src.alphabeticBaseline);
    dst.emHeightAscent = Converter::ArkValue<Ark_Float64>(src.emHeightAscent);
    dst.emHeightDescent = Converter::ArkValue<Ark_Float64>(src.emHeightDescent);
    dst.fontBoundingBoxAscent = Converter::ArkValue<Ark_Float64>(src.fontBoundingBoxAscent);
    dst.fontBoundingBoxDescent = Converter::ArkValue<Ark_Float64>(src.fontBoundingBoxDescent);
    dst.hangingBaseline = Converter::ArkValue<Ark_Float64>(src.hangingBaseline);
    dst.ideographicBaseline = Converter::ArkValue<Ark_Float64>(src.ideographicBaseline);
    dst.width = Converter::ArkValue<Ark_Float64>(src.width);
    dst.height = Converter::ArkValue<Ark_Float64>(src.height);
}

void AssignArkValue(Ark_LengthMetrics& dst, const Dimension& src)
{
    auto value = static_cast<float>(src.Value());
    auto unit = static_cast<int32_t>(src.Unit());
    
    dst.unit = static_cast<Ark_LengthUnit>(unit);
    dst.value = Converter::ArkValue<Ark_Float64>(value);
}

void AssignArkValue(Ark_VisibleListContentInfo& dst, const ListItemIndex& src)
{
    dst.index = ArkValue<Ark_Int32>(src.index);
    dst.itemGroupArea = src.area < 0 ?
        ArkValue<Opt_ListItemGroupArea>(Ark_Empty{}) : ArkValue<Opt_ListItemGroupArea>(src.area);
    dst.itemIndexInGroup = src.indexInGroup < 0 ?
        ArkValue<Opt_Int32>(Ark_Empty{}) : ArkValue<Opt_Int32>(src.indexInGroup);
}

void AssignArkValue(Ark_VisibleListContentInfo& dst, const ListItemGroupIndex& src)
{
    dst.index = ArkValue<Ark_Int32>(src.index);
    dst.itemGroupArea = src.area < 0 ?
        ArkValue<Opt_ListItemGroupArea>(Ark_Empty{}) : ArkValue<Opt_ListItemGroupArea>(src.area);
    dst.itemIndexInGroup = src.indexInGroup < 0 ?
        ArkValue<Opt_Int32>(Ark_Empty{}) : ArkValue<Opt_Int32>(src.indexInGroup);
}

void AssignArkValue(Ark_RectResult& dst, const OHOS::Ace::Rect& src)
{
    dst.x = ArkValue<Ark_Float64>(src.Left());
    dst.y = ArkValue<Ark_Float64>(src.Top());
    dst.width = ArkValue<Ark_Float64>(src.Width());
    dst.height = ArkValue<Ark_Float64>(src.Height());
}

void AssignArkValue(Ark_Tuple_Dimension_Dimension& dst, const std::pair<const Dimension, const Dimension>& src,
    ConvContext *ctx)
{
    dst.value0 = ArkValue<Ark_Dimension>(src.first, ctx);
    dst.value1 = ArkValue<Ark_Dimension>(src.second, ctx);
}

void AssignArkValue(Ark_Vector2& dst, const OffsetF& src)
{
    dst.x = Converter::ArkValue<Ark_Float64>(src.GetX());
    dst.y = Converter::ArkValue<Ark_Float64>(src.GetY());
}

void AssignArkValue(Ark_uiObserver_NavigationInfo& dst, const std::shared_ptr<OHOS::Ace::NG::NavigationInfo>& src)
{
    CHECK_NULL_VOID(src);
    dst.navigationId = ArkValue<Ark_String>(src->navigationId);
    dst.pathStack = new NavPathStackPeer(src->pathStack.Upgrade());
    dst.uniqueId = ArkValue<Opt_Int32>(src->uniqueId);
}

void AssignArkValue(Ark_ShadowOptions& dst, const Shadow& src, ConvContext* ctx)
{
    dst.radius = Converter::ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(src.GetBlurRadius());
    dst.type = Converter::ArkValue<Opt_ShadowType>(src.GetShadowType());
    dst.color = Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(
        src.GetColor().ColorToString(), ctx);
    auto offset = src.GetOffset();
    dst.offsetX = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(offset.GetX());
    dst.offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(offset.GetY());
    dst.fill = Converter::ArkValue<Opt_Boolean>(src.GetIsFilled());
}

void AssignArkValue(Ark_ItemDragInfo& dst, const ItemDragInfo& src)
{
    dst.x = ArkValue<Ark_Float64>(static_cast<float>(src.GetX()));
    dst.y = ArkValue<Ark_Float64>(static_cast<float>(src.GetY()));
}

void AssignArkValue(Ark_EdgeEffectOptions& dst, const bool& src)
{
    dst.alwaysEnabled = src;
}

void AssignArkValue(Ark_LeadingMarginPlaceholder& dst, const LeadingMargin& src, ConvContext *ctx)
{
    std::pair<const Dimension, const Dimension> pair = {src.size.Width(), src.size.Height()};
    dst.size = Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(pair, ctx);
    dst.pixelMap = image_PixelMapPeer::Create(src.pixmap);
}

void AssignArkValue(Ark_Float64& dst, const LeadingMargin& src)
{
    auto leadingMargin = Dimension(src.size.Width()).ConvertToVp();
    dst = ArkValue<Ark_Float64>(leadingMargin);
}

void AssignArkValue(Ark_String& dst, const Dimension& src, ConvContext *ctx)
{
    dst = ArkValue<Ark_String>(src.ToString(), ctx);
}

void AssignArkValue(Ark_String& dst, const CalcDimension& src, ConvContext *ctx)
{
    dst = ArkValue<Ark_String>(src.ToString(), ctx);
}

void AssignArkValue(Ark_Length& dst, const double& src)
{
    dst = ArkUnion<Ark_Length, Ark_Float64>(src);
}

void AssignArkValue(Ark_Length& dst, const Dimension& src, ConvContext *ctx)
{
    dst = ArkUnion<Ark_Length, Ark_String>(src.ToString(), ctx);
}

void AssignArkValue(Ark_Dimension& dst, const Dimension& src, ConvContext *ctx)
{
    dst = ArkUnion<Ark_Dimension, Ark_String>(src.ToString(), ctx);
}

void AssignArkValue(Ark_Length& dst, const CalcDimension& src, ConvContext *ctx)
{
    dst = ArkUnion<Ark_Length, Ark_String>(src.ToString(), ctx);
}

void AssignArkValue(Ark_Length& dst, const CalcLength& src, ConvContext *ctx)
{
    dst = ArkUnion<Ark_Length, Ark_String>(src.ToString(), ctx);
}

void AssignArkValue(Ark_Length& dst, const float& src)
{
    dst = ArkUnion<Ark_Length, Ark_Float64>(src);
}

void AssignArkValue(Ark_Dimension& dst, const float& src)
{
    dst = ArkUnion<Ark_Dimension, Ark_Number>(src);
}

void AssignArkValue(Ark_Length& dst, const std::string& src, ConvContext *ctx)
{
    dst = ArkUnion<Ark_Length, Ark_String>(src, ctx);
}

void AssignArkValue(Ark_Dimension& dst, const std::string& src, ConvContext *ctx)
{
    dst = ArkUnion<Ark_Dimension, Ark_String>(src, ctx);
}

void AssignArkValue(Ark_Length& dst, const char* src)
{
    dst = ArkUnion<Ark_Length, Ark_String>(src);
}

void AssignArkValue(Ark_Dimension& dst, const char* src)
{
    dst = ArkUnion<Ark_Dimension, Ark_String>(src);
}

void AssignArkValue(Ark_Length& dst, const int64_t& id)
{
    auto res = ArkCreate<Ark_Resource>(id, ResourceType::FLOAT);
    dst = ArkUnion<Ark_Length, Ark_Resource>(res);
}

void AssignArkValue(Ark_Dimension& dst, const int64_t& id)
{
    auto res = ArkCreate<Ark_Resource>(id, ResourceType::FLOAT);
    dst = ArkUnion<Ark_Dimension, Ark_Resource>(res);
}

void AssignArkValue(Ark_Number& dst, const int32_t& src)
{
    dst.tag = INTEROP_TAG_INT32;
    dst.i32 = src;
}

void AssignArkValue(Ark_Number& dst, const int64_t& src)
{
    LOGE("Ark_Number doesn`t support int64_t");
    dst.tag = INTEROP_TAG_INT32;
    dst.i32 = static_cast<int32_t>(src);
}

void AssignArkValue(Ark_Number& dst, const uint64_t& src)
{
    LOGE("Ark_Number doesn`t support long long");
    dst.tag = INTEROP_TAG_INT32;
    dst.i32 = static_cast<int32_t>(src);
}

void AssignArkValue(Ark_Number& dst, const uint32_t& src)
{
    dst.tag = INTEROP_TAG_INT32;
    dst.i32 = src;
}

void AssignArkValue(Ark_Number& dst, const float& src)
{
    dst.tag = INTEROP_TAG_FLOAT32;
    dst.f32 = src;
}

void AssignArkValue(Ark_Number& dst, const double& src)
{
    dst.tag = INTEROP_TAG_FLOAT32;
    dst.f32 = static_cast<float>(src);
}

void AssignArkValue(Ark_Float64& dst, const double& src)
{
    dst = src;
}

void AssignArkValue(Ark_Padding& dst, const PaddingProperty& src, ConvContext *ctx)
{
    Ark_Padding arkPadding = {
        .top = ArkValue<Opt_Length>(src.top, ctx),
        .right = ArkValue<Opt_Length>(src.right, ctx),
        .bottom = ArkValue<Opt_Length>(src.bottom, ctx),
        .left = ArkValue<Opt_Length>(src.left, ctx),
    };
    dst = arkPadding;
}

void AssignArkValue(Ark_PreviewText& dst, const PreviewText& src, ConvContext *ctx)
{
    dst.offset = ArkValue<Ark_Int32>(src.offset);
    dst.value = ArkValue<Ark_String>(src.value, ctx);
}

void AssignArkValue(Ark_Number& dst, const Dimension& src)
{
    auto value = static_cast<float>(src.ConvertToVp());
    AssignArkValue(dst, value);
}

void AssignArkValue(Ark_Float64& dst, const Dimension& src)
{
    auto value = static_cast<double>(src.ConvertToVp());
    AssignArkValue(dst, value);
}

void AssignArkValue(Ark_Buffer& dst, const std::string& src)
{
    dst.data = const_cast<char*>(src.data());
    dst.length = src.size();
}

void AssignArkValue(Ark_Date& dst, const PickerDate& src)
{
    auto date = src;
    Validator::ValidatePickerDate(date);
    std::tm tm {};
    tm.tm_year = date.GetYear() - STD_TM_START_YEAR; // tm_year is years since 1900
    tm.tm_mon = date.GetMonth() - 1; // tm_mon from 0 to 11
    tm.tm_mday = date.GetDay();
    time_t time = std::mktime(&tm);
    dst = time * SEC_TO_MILLISEC;
}

void AssignArkValue(Ark_Date& dst, const std::string& src)
{
    auto json = JsonUtil::ParseJsonString(src);
    PickerDate date(
        json->GetValue(YEAR)->GetInt(),
        json->GetValue(MONTH)->GetInt(),
        json->GetValue(DAY)->GetInt());
    Validator::ValidatePickerDate(date);

    PickerTime time(
        json->GetValue(HOUR)->GetInt(),
        json->GetValue(MINUTE)->GetInt(),
        json->GetValue(SECOND)->GetInt());

    std::tm tm {};
    tm.tm_year = date.GetYear() - STD_TM_START_YEAR; // tm_year is years since 1900
    tm.tm_mon = date.GetMonth() - 1; // tm_mon from 0 to 11
    tm.tm_mday = date.GetDay();
    tm.tm_hour = time.GetHour();
    tm.tm_min = time.GetMinute();
    tm.tm_sec = time.GetSecond();
    auto timestamp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto duration = timestamp.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    dst = static_cast<Ark_Date>(milliseconds);
}

void AssignArkValue(Ark_EventTarget& dst, const EventTarget& src, ConvContext *ctx)
{
    Ark_Area area;
    area.width = Converter::ArkValue<Ark_Length>(src.area.GetWidth().ConvertToVp(), ctx);
    area.height = Converter::ArkValue<Ark_Length>(src.area.GetHeight().ConvertToVp(), ctx);
    Ark_Position position;
    position.x = Converter::ArkValue<Opt_Length>(src.area.GetOffset().GetX().ConvertToVp(), ctx);
    position.y = Converter::ArkValue<Opt_Length>(src.area.GetOffset().GetY().ConvertToVp(), ctx);
    area.position = Converter::ArkValue<Ark_Position>(position);
    Ark_Position globPosition;
    globPosition.x = Converter::ArkValue<Opt_Length>(
        src.origin.GetX().ConvertToVp() + src.area.GetOffset().GetX().ConvertToVp(), ctx);
    globPosition.y = Converter::ArkValue<Opt_Length>(
        src.origin.GetY().ConvertToVp() + src.area.GetOffset().GetY().ConvertToVp(), ctx);
    area.globalPosition = Converter::ArkValue<Ark_Position>(globPosition);
    dst.area = area;
    if (!src.id.empty()) {
        dst.id = Converter::ArkValue<Opt_String>(src.id, ctx);
    } else {
        dst.id = Converter::ArkValue<Opt_String>(Ark_Empty());
    }
}

void AssignArkValue(Ark_Header& dst, const Header& src, ConvContext *ctx)
{
    dst.headerKey = Converter::ArkValue<Ark_String>(src.headerKey, ctx);
    dst.headerValue = Converter::ArkValue<Ark_String>(src.headerValue, ctx);
}

void AssignArkValue(Ark_KeyboardOptions& dst, const KeyboardOptions& src, ConvContext *ctx)
{
    dst.supportAvoidance = Converter::ArkValue<Opt_Boolean>(src.supportAvoidance);
}

template<>
Ark_LengthMetrics ArkCreate(Ark_LengthUnit unit, float value)
{
    DimensionUnit du = OptConvert<DimensionUnit>(unit).value_or(DimensionUnit::INVALID);
    auto duUnit = static_cast<int32_t>(du);
    return {
        .unit = static_cast<Ark_LengthUnit>(duUnit),
        .value = ArkValue<Ark_Float64>(value),
    };
}

void AssignArkValue(Ark_Position& dst, const OffsetF& src, ConvContext *ctx)
{
    dst.x = Converter::ArkValue<Opt_Length>(src.GetX(), ctx);
    dst.y = Converter::ArkValue<Opt_Length>(src.GetY(), ctx);
}

void AssignArkValue(Ark_OffsetResult& dst, const Offset& src, ConvContext *ctx)
{
    dst.xOffset = ArkValue<Ark_Float64>(src.GetX(), ctx);
    dst.yOffset = ArkValue<Ark_Float64>(src.GetY(), ctx);
}

void AssignArkValue(Ark_RectResult& dst, const RectF& src)
{
    dst.x = ArkValue<Ark_Float64>(src.GetX());
    dst.y = ArkValue<Ark_Float64>(src.GetY());
    dst.width = ArkValue<Ark_Float64>(src.Width());
    dst.height = ArkValue<Ark_Float64>(src.Height());
}

void AssignArkValue(Ark_Frame& dst, const RectF& src)
{
    dst.x = ArkValue<Ark_Float64>(src.GetX());
    dst.y = ArkValue<Ark_Float64>(src.GetY());
    dst.width = ArkValue<Ark_Float64>(src.Width());
    dst.height = ArkValue<Ark_Float64>(src.Height());
}

template<typename PeerType, typename AceSpan>
void CreateStylePeer(Ark_SpanStyle& dst, const RefPtr<OHOS::Ace::SpanBase>& src)
{
    PeerType* peer = PeerUtils::CreatePeer<PeerType>();
    peer->span = AceType::DynamicCast<AceSpan>(src);
    dst.styledValue = Converter::ArkUnion<Ark_StyledStringValue, PeerType*>(peer);
}

void AssignArkValue(Ark_SpanStyle& dst, const RefPtr<OHOS::Ace::SpanBase>& src)
{
    dst.start = Converter::ArkValue<Ark_Int32>(src->GetStartIndex());
    dst.length = Converter::ArkValue<Ark_Int32>(src->GetEndIndex() - src->GetStartIndex());
    dst.styledKey = Converter::ArkValue<Ark_StyledStringKey>(src->GetSpanType());
    switch (src->GetSpanType()) {
        case Ace::SpanType::Font:
            CreateStylePeer<TextStylePeer, OHOS::Ace::FontSpan>(dst, src);
            break;
        case Ace::SpanType::Decoration:
            CreateStylePeer<DecorationStylePeer, OHOS::Ace::DecorationSpan>(dst, src);
            break;
        case Ace::SpanType::BaselineOffset:
            CreateStylePeer<BaselineOffsetStylePeer, OHOS::Ace::BaselineOffsetSpan>(dst, src);
            break;
        case Ace::SpanType::LetterSpacing:
            CreateStylePeer<LetterSpacingStylePeer, OHOS::Ace::LetterSpacingSpan>(dst, src);
            break;
        case Ace::SpanType::TextShadow:
            CreateStylePeer<TextShadowStylePeer, OHOS::Ace::TextShadowSpan>(dst, src);
            break;
        case Ace::SpanType::LineHeight:
            CreateStylePeer<LineHeightStylePeer, OHOS::Ace::LineHeightSpan>(dst, src);
            break;
        case Ace::SpanType::BackgroundColor:
            CreateStylePeer<BackgroundColorStylePeer, OHOS::Ace::BackgroundColorSpan>(dst, src);
            break;
        case Ace::SpanType::Url:
            CreateStylePeer<UrlStylePeer, OHOS::Ace::UrlSpan>(dst, src);
            break;
        case Ace::SpanType::Gesture:
            CreateStylePeer<GestureStylePeer, OHOS::Ace::GestureSpan>(dst, src);
            break;
        case Ace::SpanType::ParagraphStyle:
            CreateStylePeer<ParagraphStylePeer, OHOS::Ace::ParagraphStyleSpan>(dst, src);
            break;
        case Ace::SpanType::Image:
            CreateStylePeer<ImageAttachmentPeer, OHOS::Ace::ImageSpan>(dst, src);
            break;
        case Ace::SpanType::CustomSpan:
            CreateStylePeer<CustomSpanPeer, OHOS::Ace::NG::CustomSpanImpl>(dst, src);
            break;
        case Ace::SpanType::ExtSpan: {
            auto userDataSpanHolder = AceType::DynamicCast<UserDataSpanHolder>(src);
            CHECK_NULL_VOID(userDataSpanHolder);
            dst.styledValue = Converter::ArkUnion<Ark_StyledStringValue, Ark_UserDataSpan>(userDataSpanHolder->span_);
            break;
        }
        default: LOGE("Unexpected enum value in SpanType: %{public}d", src->GetSpanType());
    }
}

void AssignArkValue(Ark_Size& dst, const SizeF& src)
{
    dst.width = ArkValue<Ark_Float64>(src.Width());
    dst.height = ArkValue<Ark_Float64>(src.Height());
}

void AssignArkValue(Ark_String& dst, const Color& src, ConvContext *ctx)
{
    dst = ArkValue<Ark_String>(src.ToString(), ctx);
}

void AssignArkValue(Ark_BorderRadiuses& dst, const BorderRadiusProperty& src, ConvContext *ctx)
{
    Ark_BorderRadiuses arkBorder = {
        .topLeft = ArkValue<Opt_Length>(src.radiusTopLeft, ctx),
        .topRight = ArkValue<Opt_Length>(src.radiusTopRight, ctx),
        .bottomLeft = ArkValue<Opt_Length>(src.radiusBottomLeft, ctx),
        .bottomRight = ArkValue<Opt_Length>(src.radiusBottomRight, ctx),
    };
    dst = arkBorder;
}

void AssignArkValue(Ark_TextBackgroundStyle& dst, const TextBackgroundStyle& src, ConvContext *ctx)
{
    dst.radius = ArkUnion<Opt_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(src.backgroundRadius, ctx);
    dst.color = ArkUnion<Opt_ResourceColor, Ark_String>(src.backgroundColor, ctx);
}

void AssignArkValue(Ark_TextRange& dst, const SelectionInfo& src)
{
    dst.start = ArkValue<Opt_Int32>(src.GetSelection().selection[0]);
    dst.end = ArkValue<Opt_Int32>(src.GetSelection().selection[1]);
}

void AssignArkValue(Ark_TouchObject& dst, const OHOS::Ace::TouchLocationInfo& src)
{
    Offset globalOffset = src.GetGlobalLocation();
    Offset localOffset = src.GetLocalLocation();
    Offset screenOffset = src.GetScreenLocation();

    dst.displayX = ArkValue<Ark_Float64>(
        PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    dst.displayY = ArkValue<Ark_Float64>(
        PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));

    dst.id = ArkValue<Ark_Int32>(src.GetFingerId());

    dst.type = ArkValue<Ark_TouchType>(src.GetTouchType());

    dst.windowX = ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    dst.windowY = ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

    dst.x = ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    dst.y = ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));

    dst.pressedTime = ArkValue<Opt_Int64>(static_cast<int64_t>(src.GetPressedTime().time_since_epoch().count()));
    dst.pressure = ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(src.GetForce()));

    dst.width = ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(src.GetWidth()));
    dst.height = ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(src.GetHeight()));

    dst.hand = ArkValue<Opt_InteractionHand>(static_cast<ArkUI_InteractionHand>(src.GetOperatingHand()));
}

void AssignArkValue(Ark_HistoricalPoint& dst, const OHOS::Ace::TouchLocationInfo& src)
{
    AssignArkValue(dst.touchObject, src);
    dst.size = ArkValue<Ark_Int32>(src.GetSize());
    dst.force = ArkValue<Ark_Float64>(src.GetForce());
    dst.timestamp = ArkValue<Ark_Int64>(static_cast<int64_t>(src.GetTimeStamp().time_since_epoch().count()));
}

void AssignArkValue(Ark_ImageError& dst, const LoadImageFailEvent& src)
{
    dst.componentWidth = Converter::ArkValue<Ark_Int32>(src.GetComponentWidth());
    dst.componentHeight = Converter::ArkValue<Ark_Int32>(src.GetComponentHeight());
    dst.message = Converter::ArkValue<Ark_String>(src.GetErrorMessage());
    dst.error = ArkValue<Opt_BusinessError>(std::nullopt);
}

void AssignArkValue(Ark_ImageLoadResult& dst, const LoadImageSuccessEvent& src)
{
    dst.width = Converter::ArkValue<Ark_Float64>(src.GetWidth());
    dst.height = Converter::ArkValue<Ark_Float64>(src.GetHeight());
    dst.componentWidth = Converter::ArkValue<Ark_Float64>(src.GetComponentWidth());
    dst.componentHeight = Converter::ArkValue<Ark_Float64>(src.GetComponentHeight());
    dst.loadingStatus = Converter::ArkValue<Ark_Float64>(src.GetLoadingStatus());
    dst.contentWidth = Converter::ArkValue<Ark_Float64>(src.GetContentWidth());
    dst.contentHeight = Converter::ArkValue<Ark_Float64>(src.GetContentHeight());
    dst.contentOffsetX = Converter::ArkValue<Ark_Float64>(src.GetContentOffsetX());
    dst.contentOffsetY = Converter::ArkValue<Ark_Float64>(src.GetContentOffsetY());
}

void AssignArkValue(Ark_RichEditorSymbolSpanStyle& dst, const SymbolSpanStyle& src, ConvContext *ctx)
{
    dst.fontSize = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(src.fontSize);
    dst.fontWeight = Converter::ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Int32>(src.fontWeight);
    auto arkEffectStrategy = static_cast<Ark_SymbolEffectStrategy>(src.effectStrategy);
    dst.effectStrategy = Converter::ArkValue<Opt_SymbolEffectStrategy>(arkEffectStrategy);
    auto arkRenderingStrategy = static_cast<Ark_SymbolRenderingStrategy>(src.renderingStrategy);
    dst.renderingStrategy = Converter::ArkValue<Opt_SymbolRenderingStrategy>(arkRenderingStrategy);
    if (src.symbolColor.size()) {
        std::vector<Ark_ResourceColor> colors;
        std::stringstream symbolColors(src.symbolColor);
        std::string color;
        while (std::getline(symbolColors, color, ',')) {
            colors.push_back(ArkUnion<Ark_ResourceColor, Ark_String>(Color::FromString(color), ctx));
        }
        auto fontColor = Converter::ArkValue<Array_ResourceColor>(colors, ctx);
        dst.fontColor = Converter::ArkValue<Opt_Array_ResourceColor>(fontColor, ctx);
    } else {
        dst.fontColor = Converter::ArkValue<Opt_Array_ResourceColor>(Ark_Empty(), ctx);
    }
}

void AssignArkValue(Ark_Resource& dst, const ResourceObject& src, ConvContext *ctx)
{
    dst.bundleName = Converter::ArkValue<Ark_String>(src.GetBundleName(), ctx);
    dst.moduleName = Converter::ArkValue<Ark_String>(src.GetModuleName(), ctx);
    dst.id = Converter::ArkValue<Ark_Int64>(static_cast<int64_t>(src.GetId()));

    std::vector<Ark_Union_String_I32_I64_F64_Resource> paramsArray;
    auto params = src.GetParams();
    for (const ResourceObjectParams& param : params) {
        if (param.value) {
            paramsArray.push_back(ArkUnion<Ark_Union_String_I32_I64_F64_Resource, Ark_String>(*param.value, ctx));
        }
    }
    dst.params = Converter::ArkValue<Opt_Array_Union_String_I32_I64_F64_Resource>(paramsArray, ctx);
    dst.type = Converter::ArkValue<Opt_Int32>(src.GetType());
}
void AssignArkValue(Ark_text_Affinity& dst, const TextAffinity& src)
{
    switch (src) {
        case TextAffinity::UPSTREAM:
            dst = Ark_text_Affinity::ARK_TEXT_AFFINITY_UPSTREAM;
            break;
        case TextAffinity::DOWNSTREAM:
            dst = Ark_text_Affinity::ARK_TEXT_AFFINITY_DOWNSTREAM;
            break;
        default:
            LOGE("Unexpected enum value in TextAffinity: %{public}d", src);
            dst = Ark_text_Affinity::ARK_TEXT_AFFINITY_UPSTREAM;
            break;
    }
}
void AssignArkValue(Ark_common2D_Rect& dst, const OHOS::Ace::NG::RectT<float>& src)
{
    dst.left = Converter::ArkValue<Ark_Float64>(src.Left());
    dst.top = Converter::ArkValue<Ark_Float64>(src.Top());
    dst.right = Converter::ArkValue<Ark_Float64>(src.Right());
    dst.bottom = Converter::ArkValue<Ark_Float64>(src.Bottom());
}
void AssignArkValue(Ark_text_TextDirection& dst, const OHOS::Ace::TextDirection& src)
{
    switch (src) {
        case OHOS::Ace::TextDirection::LTR:
            dst = Ark_text_TextDirection::ARK_TEXT_TEXT_DIRECTION_LTR;
            break;
        case OHOS::Ace::TextDirection::RTL:
            dst = Ark_text_TextDirection::ARK_TEXT_TEXT_DIRECTION_RTL;
            break;
        default:
            LOGE("Unexpected enum value in TextDirection: %{public}d", src);
            dst = Ark_text_TextDirection::ARK_TEXT_TEXT_DIRECTION_LTR;
            break;
    }
}
void AssignArkValue(Ark_text_TextBox& dst, const ParagraphManager::TextBox& src)
{
    AssignArkValue(dst.direction, src.direction_);
    dst.rect = Converter::ArkValue<Ark_common2D_Rect>(src.rect_);
}
void AssignArkValue(Ark_text_LineMetrics& dst, const OHOS::Ace::TextLineMetrics& src, ConvContext *ctx)
{
    dst.startIndex = Converter::ArkValue<Ark_Int32>(src.startIndex);
    dst.endIndex = Converter::ArkValue<Ark_Int32>(src.endIndex);
    dst.ascent = Converter::ArkValue<Ark_Float64>(src.ascender);
    dst.descent = Converter::ArkValue<Ark_Float64>(src.descender);
    dst.height = Converter::ArkValue<Ark_Float64>(src.height);
    dst.width = Converter::ArkValue<Ark_Float64>(src.width);
    dst.left = Converter::ArkValue<Ark_Float64>(src.x);
    dst.baseline = Converter::ArkValue<Ark_Float64>(src.baseline);
    dst.lineNumber = Converter::ArkValue<Ark_Int32>(src.lineNumber);
    dst.topHeight = Converter::ArkValue<Ark_Float64>(src.y);
    dst.runMetrics = Converter::ArkValue<Map_Int32_text_RunMetrics>(src.runMetrics, ctx);
}
void AssignArkValue(Map_Int32_text_RunMetrics& dst, const std::map<size_t, RunMetrics>& src, ConvContext *ctx)
{
    dst = {};
    CHECK_NULL_VOID(ctx);
    CHECK_NULL_VOID(src.size());
    dst = ctx->AllocateMap<Map_Int32_text_RunMetrics>(src.size());
    Ark_Int32* keys = dst.keys;
    Ark_text_RunMetrics* values = dst.values;
    CHECK_NULL_VOID(keys && values);
    for (const auto& item : src) {
        *keys++ = Converter::ArkValue<Ark_Int32>(item.first, ctx);
        *values++ = Converter::ArkValue<Ark_text_RunMetrics>(item.second, ctx);
    }
    dst.size = src.size();
}
void AssignArkValue(Ark_text_RunMetrics& dst, const RunMetrics& src, ConvContext *ctx)
{
    dst.textStyle = Converter::ArkValue<Ark_text_TextStyle>(src.textStyle, ctx);
    dst.fontMetrics = Converter::ArkValue<Ark_drawing_FontMetrics>(src.fontMetrics, ctx);
}
void AssignArkValue(Ark_text_TextStyle& dst, const TextStyle& src, ConvContext *ctx)
{
    Opt_text_Decoration decoration = {};
    decoration.tag = INTEROP_TAG_OBJECT;
    decoration.value = Converter::ArkValue<Ark_text_Decoration>(src.GetTextDecorationFirst());
    dst.decoration = decoration;
    Opt_common2D_Color color = {};
    color.tag = INTEROP_TAG_OBJECT;
    color.value = Converter::ArkValue<Ark_common2D_Color>(src.GetTextColor());
    dst.color = color;
    Opt_text_FontWeight fontWeight = {};
    fontWeight.tag = INTEROP_TAG_OBJECT;
    fontWeight.value = Converter::ArkValue<Ark_text_FontWeight>(src.GetFontWeight());
    dst.fontWeight = fontWeight;
    Opt_text_FontStyle fontStyle = {};
    fontStyle.tag = INTEROP_TAG_OBJECT;
    fontStyle.value = Converter::ArkValue<Ark_text_FontStyle>(src.GetFontStyle());
    dst.fontStyle = fontStyle;
    Opt_text_TextBaseline textBaseline = {};
    textBaseline.tag = INTEROP_TAG_OBJECT;
    textBaseline.value = Converter::ArkValue<Ark_text_TextBaseline>(src.GetTextBaseline());
    dst.baseline = textBaseline;
    dst.fontFamilies = Converter::ArkValue<Opt_Array_String>(src.GetFontFamilies(), ctx);
    dst.fontSize = Converter::ArkValue<Opt_Float64>(src.GetFontSize().Value());
    dst.letterSpacing = Converter::ArkValue<Opt_Float64>(src.GetLetterSpacing().Value());
    dst.wordSpacing = Converter::ArkValue<Opt_Float64>(src.GetWordSpacing().Value());
    dst.heightScale = Converter::ArkValue<Opt_Float64>(src.GetHeightScale());
    dst.halfLeading = Converter::ArkValue<Opt_Boolean>(src.GetHalfLeading());
    dst.heightOnly = Converter::ArkValue<Opt_Boolean>(src.GetHeightOnly());
    dst.ellipsis = Converter::ArkValue<Opt_String>(StringUtils::Str16ToStr8(src.GetEllipsis()), ctx);
    Opt_text_EllipsisMode ellipsisMode = {};
    ellipsisMode.tag = INTEROP_TAG_OBJECT;
    ellipsisMode.value = Converter::ArkValue<Ark_text_EllipsisMode>(src.GetEllipsisMode());
    dst.ellipsisMode = ellipsisMode;
    dst.locale = Converter::ArkValue<Opt_String>(src.GetLocale(), ctx);
    dst.baselineShift = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    Opt_Array_text_FontFeature fontFeatures = {};
    fontFeatures.tag = INTEROP_TAG_UNDEFINED;
    dst.fontFeatures = fontFeatures;
    Opt_Array_text_TextShadow textShadows = {};
    textShadows.tag = INTEROP_TAG_UNDEFINED;
    dst.textShadows = textShadows;
    Opt_text_RectStyle backgroundRect = {};
    backgroundRect.tag = INTEROP_TAG_UNDEFINED;
    dst.backgroundRect = backgroundRect;
    Opt_Array_text_FontVariation fontVariations = {};
    fontVariations.tag = INTEROP_TAG_UNDEFINED;
    dst.fontVariations = fontVariations;
}
void AssignArkValue(Ark_text_Decoration& dst, const TextDecoration& src, ConvContext *ctx)
{
    Opt_text_TextDecorationType textDecoration = {};
    textDecoration.tag = INTEROP_TAG_OBJECT;
    textDecoration.value = Converter::ArkValue<Ark_text_TextDecorationType>(src);
    dst.textDecoration = textDecoration;
    Opt_common2D_Color color = {};
    color.tag = INTEROP_TAG_UNDEFINED;
    dst.color = color;
    Opt_text_TextDecorationStyle decorationStyle = {};
    decorationStyle.tag = INTEROP_TAG_UNDEFINED;
    dst.decorationStyle = decorationStyle;
    Opt_Float64 decorationThicknessScale = Converter::ArkValue<Opt_Float64>(Ark_Empty());
    dst.decorationThicknessScale = decorationThicknessScale;
}
void AssignArkValue(Ark_text_TextDecorationType& dst, const TextDecoration& src, ConvContext *ctx)
{
    switch (src) {
        case TextDecoration::NONE:
            dst = Ark_text_TextDecorationType::ARK_TEXT_TEXT_DECORATION_TYPE_NONE;
            break;
        case TextDecoration::UNDERLINE:
            dst = Ark_text_TextDecorationType::ARK_TEXT_TEXT_DECORATION_TYPE_UNDERLINE;
            break;
        case TextDecoration::OVERLINE:
            dst = Ark_text_TextDecorationType::ARK_TEXT_TEXT_DECORATION_TYPE_OVERLINE;
            break;
        case TextDecoration::LINE_THROUGH:
            dst = Ark_text_TextDecorationType::ARK_TEXT_TEXT_DECORATION_TYPE_LINE_THROUGH;
            break;        
        case TextDecoration::INHERIT:
        default:
            LOGE("Unexpected enum value in TextDecoration: %{public}d", src);
            dst = Ark_text_TextDecorationType::ARK_TEXT_TEXT_DECORATION_TYPE_NONE;
            break;
    }
}
void AssignArkValue(Ark_common2D_Color& dst, const Color& src, ConvContext *ctx)
{
    dst.alpha = Converter::ArkValue<Ark_Int32>(src.GetAlpha());
    dst.red = Converter::ArkValue<Ark_Int32>(src.GetRed());
    dst.green = Converter::ArkValue<Ark_Int32>(src.GetGreen());
    dst.blue = Converter::ArkValue<Ark_Int32>(src.GetBlue());
}
void AssignArkValue(Ark_text_FontWeight& dst, const FontWeight& src, ConvContext *ctx)
{
    switch (src) {
        case FontWeight::W100:
            dst = Ark_text_FontWeight::ARK_TEXT_FONT_WEIGHT_W100;
            break;
        case FontWeight::W200:
            dst = Ark_text_FontWeight::ARK_TEXT_FONT_WEIGHT_W200;
            break;
        case FontWeight::W300:
            dst = Ark_text_FontWeight::ARK_TEXT_FONT_WEIGHT_W300;
            break;
        case FontWeight::W400:
            dst = Ark_text_FontWeight::ARK_TEXT_FONT_WEIGHT_W400;
            break;    
        case FontWeight::W500:
            dst = Ark_text_FontWeight::ARK_TEXT_FONT_WEIGHT_W500;
            break;
        case FontWeight::W600:
            dst = Ark_text_FontWeight::ARK_TEXT_FONT_WEIGHT_W600;
            break;
        case FontWeight::W700:
            dst = Ark_text_FontWeight::ARK_TEXT_FONT_WEIGHT_W700;
            break;
        case FontWeight::W800:
            dst = Ark_text_FontWeight::ARK_TEXT_FONT_WEIGHT_W800;
            break;
        case FontWeight::W900:
            dst = Ark_text_FontWeight::ARK_TEXT_FONT_WEIGHT_W900;
            break;
        default:
            LOGE("Unexpected enum value in FontWeight: %{public}d", src);
            dst = Ark_text_FontWeight::ARK_TEXT_FONT_WEIGHT_W400;
            break;
    }
}
void AssignArkValue(Ark_text_FontStyle& dst, const OHOS::Ace::FontStyle& src, ConvContext *ctx)
{
    switch (src) {
        case OHOS::Ace::FontStyle::NORMAL:
            dst = Ark_text_FontStyle::ARK_TEXT_FONT_STYLE_NORMAL;
            break;
        case OHOS::Ace::FontStyle::ITALIC:
            dst = Ark_text_FontStyle::ARK_TEXT_FONT_STYLE_ITALIC;
            break;
        case OHOS::Ace::FontStyle::NONE:
            dst = Ark_text_FontStyle::ARK_TEXT_FONT_STYLE_OBLIQUE;
            break;
        default:
            LOGE("Unexpected enum value in FontStyle: %{public}d", src);
            dst = Ark_text_FontStyle::ARK_TEXT_FONT_STYLE_NORMAL;
            break;
    }
}
void AssignArkValue(Ark_text_TextBaseline& dst, const TextBaseline& src, ConvContext *ctx)
{
    switch (src) {
        case TextBaseline::ALPHABETIC:
            dst = Ark_text_TextBaseline::ARK_TEXT_TEXT_BASELINE_ALPHABETIC;
            break;
        case TextBaseline::IDEOGRAPHIC:
            dst = Ark_text_TextBaseline::ARK_TEXT_TEXT_BASELINE_IDEOGRAPHIC;
            break;
        default:
            LOGE("Unexpected enum value in TextBaseline: %{public}d", src);
            dst = Ark_text_TextBaseline::ARK_TEXT_TEXT_BASELINE_ALPHABETIC;
            break;
    }
}
void AssignArkValue(Ark_text_EllipsisMode& dst, const EllipsisMode& src, ConvContext *ctx)
{
    switch (src) {
        case EllipsisMode::HEAD:
            dst = Ark_text_EllipsisMode::ARK_TEXT_ELLIPSIS_MODE_START;
            break;
        case EllipsisMode::MIDDLE:
            dst = Ark_text_EllipsisMode::ARK_TEXT_ELLIPSIS_MODE_MIDDLE;
            break;
        case EllipsisMode::TAIL:
            dst = Ark_text_EllipsisMode::ARK_TEXT_ELLIPSIS_MODE_END;
            break;
        default:
            LOGE("Unexpected enum value in FontStyle: %{public}d", src);
            dst = Ark_text_EllipsisMode::ARK_TEXT_ELLIPSIS_MODE_END;
            break;
    }
}
void AssignArkValue(Ark_drawing_FontMetrics& dst, const FontMetrics& src, ConvContext *ctx)
{
    dst.flags = Converter::ArkValue<Opt_Int32>(src.fFlags);
    dst.top = Converter::ArkValue<Ark_Float64>(src.fTop);
    dst.ascent = Converter::ArkValue<Ark_Float64>(src.fAscent);
    dst.descent = Converter::ArkValue<Ark_Float64>(src.fDescent);
    dst.bottom = Converter::ArkValue<Ark_Float64>(src.fBottom);
    dst.leading = Converter::ArkValue<Ark_Float64>(src.fLeading);
    dst.avgCharWidth = Converter::ArkValue<Opt_Float64>(src.fAvgCharWidth);
    dst.maxCharWidth = Converter::ArkValue<Opt_Float64>(src.fMaxCharWidth);
    dst.xMin = Converter::ArkValue<Opt_Float64>(src.fXMin);
    dst.xMax = Converter::ArkValue<Opt_Float64>(src.fXMax);
    dst.xHeight = Converter::ArkValue<Opt_Float64>(src.fXHeight);
    dst.capHeight = Converter::ArkValue<Opt_Float64>(src.fCapHeight);
    dst.underlineThickness = Converter::ArkValue<Opt_Float64>(src.fUnderlineThickness);
    dst.underlinePosition = Converter::ArkValue<Opt_Float64>(src.fUnderlinePosition);
    dst.strikethroughThickness = Converter::ArkValue<Opt_Float64>(src.fStrikeoutThickness);
    dst.strikethroughPosition = Converter::ArkValue<Opt_Float64>(src.fStrikeoutPosition);
}

std::optional<OHOS::Ace::NG::MarginProperty> ParseMarginString(const std::string& ss)
{
    constexpr int32_t MARGIN_MIN_LENGTH = 2;
    constexpr int32_t EXPECTED_MARGIN_VALUES = 4;
    if (ss.size() < MARGIN_MIN_LENGTH || ss[0] != '[' || ss.back() != ']') {
        LOGE("Unexpected MarginString:%{public}s", ss.c_str());
        return std::nullopt;
    }
    std::string content = ss.substr(1, ss.size() - 2);
    std::vector<std::string> values;
    StringUtils::SplitStr(content, ",", values);
    std::vector<std::optional<CalcLength>> lengths;
    for (const auto& value : values) {
        if (value == "NA") {
            lengths.push_back(std::nullopt);
        } else {
            lengths.push_back(CalcLength::FromString(value));
        }
    }
    if (lengths.size() != EXPECTED_MARGIN_VALUES) {
        LOGE("Unexpected MarginString:%{public}s", ss.c_str());
        return std::nullopt;
    }
    OHOS::Ace::NG::MarginProperty marginProp  = {
        .left = lengths[0],
        .right = lengths[1],
        .top = lengths[2],
        .bottom = lengths[3]
    };
    return marginProp;
}

std::optional<OHOS::Ace::NG::BorderRadiusProperty> ParseBorderRadiusString(const std::string& ss)
{
    CHECK_NULL_RETURN(!ss.empty(), std::nullopt);
    OHOS::Ace::NG::BorderRadiusProperty borderRadius;
    if (ss[0] >= '0' && ss[0] <= '9') {
        borderRadius.SetRadius(Dimension::FromString(ss));
        borderRadius.multiValued = false;
    } else if (ss[0] == '{') {
        auto json = JsonUtil::ParseJsonString(ss);
        CHECK_NULL_RETURN(json && json->IsValid(), std::nullopt);
        borderRadius.radiusTopLeft = Dimension::FromString(json->GetString("topLeft"));
        borderRadius.radiusTopRight = Dimension::FromString(json->GetString("topRight"));
        borderRadius.radiusBottomLeft = Dimension::FromString(json->GetString("bottomLeft"));
        borderRadius.radiusBottomRight = Dimension::FromString(json->GetString("bottomRight"));
    } else {
        LOGE("Unexpected Border Radius String:%{public}s", ss.c_str());
        return std::nullopt;
    }
    return borderRadius;
}

void AssignArkValue(Ark_RichEditorLayoutStyle& dst, const ImageStyleResult& src)
{
    dst.margin = ArkUnion<Opt_Union_Dimension_Margin>(Ark_Empty());
    if (auto marginProp = ParseMarginString(src.margin)) {
        auto arkMargin = ArkValue<Ark_Padding>(marginProp.value(), Converter::FC);
        dst.margin = ArkUnion<Opt_Union_Dimension_Margin, Ark_Padding>(arkMargin, Converter::FC);
    }
    dst.borderRadius = ArkUnion<Opt_Union_Dimension_BorderRadiuses>(Ark_Empty());
    auto borderRadius = ParseBorderRadiusString(src.borderRadius);
    CHECK_NULL_VOID(borderRadius.has_value());
    if (borderRadius->multiValued) {
        auto arkBorder = ArkValue<Ark_BorderRadiuses>(borderRadius.value());
        dst.borderRadius = ArkUnion<Opt_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(arkBorder);
    } else {
        dst.borderRadius = ArkUnion<Opt_Union_Dimension_BorderRadiuses, Ark_Dimension>(borderRadius->radiusTopLeft);
    }
}

void AssignArkValue(Ark_RichEditorImageSpanStyleResult& dst, const ImageStyleResult& src)
{
    dst.size.value0 = ArkValue<Ark_Int32>(src.size[0]);
    dst.size.value1 = ArkValue<Ark_Int32>(src.size[1]);
    dst.verticalAlign = ArkValue<Ark_ImageSpanAlignment>(
        static_cast<OHOS::Ace::VerticalAlign>(src.verticalAlign));
    dst.objectFit = ArkValue<Ark_ImageFit>(
        static_cast<OHOS::Ace::ImageFit>(src.objectFit));
    dst.layoutStyle = ArkValue<Opt_RichEditorLayoutStyle>(src);
}

void AssignArkValue(Ark_NavDestinationContext& dst, const RefPtr<NG::NavDestinationContext>& src)
{
    const auto peer = PeerUtils::CreatePeer<NavDestinationContextPeer>();
    peer->SetHandler(src);
    dst = peer;
}

void AssignArkValue(Ark_NavigationTransitionProxy& dst, const RefPtr<NavigationTransitionProxy>& src)
{
    const auto peer = PeerUtils::CreatePeer<NavigationTransitionProxyPeer>();
    peer->SetHandler(src);
    dst = peer;
}

void AssignArkValue(Ark_NavContentInfo& dst, const RefPtr<NG::NavDestinationContext>& src)
{
    if (!src) {
        dst.name.tag = InteropTag::INTEROP_TAG_UNDEFINED;
        dst.param.tag = InteropTag::INTEROP_TAG_UNDEFINED;
        dst.mode.tag = InteropTag::INTEROP_TAG_UNDEFINED;
        dst.navDestinationId.tag = InteropTag::INTEROP_TAG_UNDEFINED;
        dst.index = Converter::ArkValue<Ark_Int32>(-1);
        return;
    }
    auto navPathInfo =
        AceType::DynamicCast<GeneratedModifier::NavigationContext::JSNavPathInfoStatic>(src->GetNavPathInfo());
    if (navPathInfo) {
        auto name = navPathInfo->GetName();
        dst.name.tag = InteropTag::INTEROP_TAG_STRING;
        dst.name.value = Converter::ArkValue<Ark_String>(name, Converter::FC);
        if (navPathInfo->GetParam()) {
            dst.param = navPathInfo->GetParam()->data_;
        } else {
            dst.param.tag = InteropTag::INTEROP_TAG_UNDEFINED;
        }
    } else {
        dst.name.tag = InteropTag::INTEROP_TAG_UNDEFINED;
        dst.param.tag = InteropTag::INTEROP_TAG_UNDEFINED;
    }
    auto index = src->GetIndex();
    dst.index = Converter::ArkValue<Ark_Int32>(index);
    auto mode = src->GetMode();
    dst.mode.tag = InteropTag::INTEROP_TAG_INT32;
    dst.mode.value = static_cast<Ark_NavDestinationMode>(mode);
    auto navDestinationId = src->GetNavDestinationId();
    dst.navDestinationId.tag = InteropTag::INTEROP_TAG_STRING;
    dst.navDestinationId.value = Converter::ArkValue<Ark_String>(std::to_string(navDestinationId), Converter::FC);
}

void AssignArkValue(Ark_NavigationMode& dst, NG::NavigationMode& src)
{
    dst = static_cast<Ark_NavigationMode>(src);
}

void AssignArkValue(Ark_NavigationOperation& dst, const NG::NavigationOperation& src)
{
    dst = static_cast<Ark_NavigationOperation>(src);
}

template<>
Ark_Resource ArkCreate(int64_t id, ResourceType type)
{
    return {
        .bundleName = ArkValue<Ark_String>(""),
        .moduleName = ArkValue<Ark_String>(""),
        .id = ArkValue<Ark_Int64>(id),
        .params = ArkValue<Opt_Array_Union_String_I32_I64_F64_Resource>(),
        .type = ArkValue<Opt_Int32>(static_cast<int32_t>(type)),
    };
}

template<>
Ark_Resource ArkCreate(std::string name, ResourceType type, ConvContext *ctx)
{
    std::vector params = { ArkUnion<Ark_Union_String_I32_I64_F64_Resource, Ark_String>(name, ctx) };
    return {
        .bundleName = ArkValue<Ark_String>(""),
        .moduleName = ArkValue<Ark_String>(""),
        .id = ArkValue<Ark_Int64>(static_cast<int64_t>(-1)),
        .params = ArkValue<Opt_Array_Union_String_I32_I64_F64_Resource>(params, ctx),
        .type = ArkValue<Opt_Int32>(static_cast<int32_t>(type)),
    };
}

void AssignArkValue(Ark_TextRange& dst, const TextRange& src)
{
    dst.start = Converter::ArkValue<Opt_Int32>(src.start);
    dst.end = Converter::ArkValue<Opt_Int32>(src.end);
}

void AssignArkValue(Ark_RichEditorRange& dst, const BaseEventInfo& src)
{
    std::optional<int32_t> start;
    std::optional<int32_t> end;
    if (src.GetType() == "SelectionInfo") {
        auto selectionInfo = static_cast<const SelectionInfo*>(&src);
        if (selectionInfo) {
            auto selection = selectionInfo->GetSelection();
            start = selection.selection[0];
            end = selection.selection[1];
        }
    } else if (src.GetType() == "SelectionRangeInfo") {
        auto selectionRangeInfo = static_cast<const SelectionRangeInfo*>(&src);
        if (selectionRangeInfo) {
            start = selectionRangeInfo->start_;
            end = selectionRangeInfo->end_;
        }
    }
    dst.start = Converter::ArkValue<Opt_Int32>(start);
    dst.end = Converter::ArkValue<Opt_Int32>(end);
}

void AssignArkValue(Ark_TextChangeOptions& dst, const ChangeValueInfo& value, ConvContext *ctx)
{
    dst.rangeBefore = Converter::ArkValue<Ark_TextRange>(value.rangeBefore);
    dst.rangeAfter = Converter::ArkValue<Ark_TextRange>(value.rangeAfter);
    dst.oldContent = Converter::ArkValue<Ark_String>(value.oldContent, ctx);
    dst.oldPreviewText = Converter::ArkValue<Ark_PreviewText>(value.oldPreviewText, ctx);
}

void AssignArkValue(
    Ark_NavPathStack& dst, const RefPtr<NG::GeneratedModifier::NavigationContext::NavigationStack>& src)
{
    const auto peer = PeerUtils::CreatePeer<NavPathStackPeer>();
    peer->SetNavigationStack(src);
    dst = peer;
}

void AssignArkValue(Ark_LengthMetricsCustom& dst, const CalcDimension& src)
{
    dst.value = Converter::ArkValue<Ark_Number>(static_cast<float>(src.Value()));
    dst.unit = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(src.Unit()));
}

void AssignArkValue(Ark_NavPathInfo& dst, const OHOS::Ace::NG::GeneratedModifier::NavigationContext::PathInfo& src)
{
    const auto peer = PeerUtils::CreatePeer<NavPathInfoPeer>();
    peer->data = src;
    dst = peer;
}

void AssignArkValue(Ark_NativeEmbedParamItem& dst, const NativeEmbedParamItem& src)
{
    dst.status = Converter::ArkValue<Ark_NativeEmbedParamStatus>(src.status);
    dst.id = ArkValue<Ark_String>(src.id);
    dst.name = ArkValue<Opt_String>(src.name);
    dst.value = ArkValue<Opt_String>(src.value);
}

void AssignArkValue(Ark_EventLocationInfo& dst, const EventLocationInfo& src)
{
    dst.x = ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(src.localLocation_.GetX()));
    dst.y =  ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(src.localLocation_.GetY()));
    dst.windowX = ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(src.windowLocation_.GetX()));
    dst.windowY = ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(src.windowLocation_.GetY()));
    dst.displayX = ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(src.globalDisplayLocation_.GetX()));
    dst.displayY = ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(src.globalDisplayLocation_.GetY()));
}
} // namespace OHOS::Ace::NG::Converter
