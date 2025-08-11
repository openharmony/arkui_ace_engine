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
#include "core/interfaces/native/implementation/decoration_style_peer.h"
#include "core/interfaces/native/implementation/image_attachment_peer.h"
#include "core/interfaces/native/implementation/gesture_style_peer.h"
#include "core/interfaces/native/implementation/length_metrics_peer.h"
#include "core/interfaces/native/implementation/letter_spacing_style_peer.h"
#include "core/interfaces/native/implementation/line_height_style_peer.h"
#include "core/interfaces/native/implementation/paragraph_style_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/implementation/text_menu_item_id_peer.h"
#include "core/interfaces/native/implementation/text_shadow_style_peer.h"
#include "core/interfaces/native/implementation/text_style_styled_string_peer.h"
#include "core/interfaces/native/implementation/url_style_peer.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "converter.h"
#include "validators.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr int32_t NUM_4 = 4;
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

void AssignArkValue(Ark_String& dst, const FONT_FEATURES_LIST& src, ConvContext *ctx)
{
    CHECK_NULL_VOID(src.empty());
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

void AssignArkValue(Ark_BaseGestureEvent& dst, const std::shared_ptr<OHOS::Ace::BaseGestureEvent>& src)
{
    const auto peer = reinterpret_cast<GeneratedModifier::BaseGestureEventPeerImpl*>(
        GeneratedModifier::GetFullAPI()->getAccessors()->getBaseGestureEventAccessor()->ctor());
    peer->SetEventInfo(src);
    dst = peer;
}

void AssignArkValue(Ark_CaretOffset& dst, const NG::OffsetF& src)
{
    dst.index = Converter::ArkValue<Ark_Number>(0);
    dst.x = Converter::ArkValue<Ark_Number>(src.GetX());
    dst.y = Converter::ArkValue<Ark_Number>(src.GetY());
}

void AssignArkValue(Ark_DragEvent& dragEvent, const RefPtr<OHOS::Ace::DragEvent>& info)
{
    const auto peer = GeneratedModifier::GetFullAPI()->getAccessors()->getDragEventAccessor()->ctor();
    peer->dragInfo = info;
    dragEvent = peer;
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
    dst.actualBoundingBoxAscent = Converter::ArkValue<Ark_Number>(src.actualBoundingBoxAscent);
    dst.actualBoundingBoxDescent = Converter::ArkValue<Ark_Number>(src.actualBoundingBoxDescent);
    dst.actualBoundingBoxLeft = Converter::ArkValue<Ark_Number>(src.actualBoundingBoxLeft);
    dst.actualBoundingBoxRight = Converter::ArkValue<Ark_Number>(src.actualBoundingBoxRight);
    dst.alphabeticBaseline = Converter::ArkValue<Ark_Number>(src.alphabeticBaseline);
    dst.emHeightAscent = Converter::ArkValue<Ark_Number>(src.emHeightAscent);
    dst.emHeightDescent = Converter::ArkValue<Ark_Number>(src.emHeightDescent);
    dst.fontBoundingBoxAscent = Converter::ArkValue<Ark_Number>(src.fontBoundingBoxAscent);
    dst.fontBoundingBoxDescent = Converter::ArkValue<Ark_Number>(src.fontBoundingBoxDescent);
    dst.hangingBaseline = Converter::ArkValue<Ark_Number>(src.hangingBaseline);
    dst.ideographicBaseline = Converter::ArkValue<Ark_Number>(src.ideographicBaseline);
    dst.width = Converter::ArkValue<Ark_Number>(src.width);
    dst.height = Converter::ArkValue<Ark_Number>(src.height);
}

void AssignArkValue(Ark_LengthMetrics& dst, const Dimension& src)
{
    dst = LengthMetricsPeer::Create(src);
}

void AssignArkValue(Ark_VisibleListContentInfo& dst, const ListItemIndex& src)
{
    dst.index = ArkValue<Ark_Number>(src.index);
    dst.itemGroupArea = src.area < 0 ?
        ArkValue<Opt_ListItemGroupArea>(Ark_Empty{}) : ArkValue<Opt_ListItemGroupArea>(src.area);
    dst.itemIndexInGroup = src.indexInGroup < 0 ?
        ArkValue<Opt_Number>(Ark_Empty{}) : ArkValue<Opt_Number>(src.indexInGroup);
}

void AssignArkValue(Ark_VisibleListContentInfo& dst, const ListItemGroupIndex& src)
{
    dst.index = ArkValue<Ark_Number>(src.index);
    dst.itemGroupArea = src.area < 0 ?
        ArkValue<Opt_ListItemGroupArea>(Ark_Empty{}) : ArkValue<Opt_ListItemGroupArea>(src.area);
    dst.itemIndexInGroup = src.indexInGroup < 0 ?
        ArkValue<Opt_Number>(Ark_Empty{}) : ArkValue<Opt_Number>(src.indexInGroup);
}

void AssignArkValue(Ark_RectResult& dst, const OHOS::Ace::Rect& src)
{
    dst.x = ArkValue<Ark_Number>(src.Left());
    dst.y = ArkValue<Ark_Number>(src.Top());
    dst.width = ArkValue<Ark_Number>(src.Width());
    dst.height = ArkValue<Ark_Number>(src.Height());
}

void AssignArkValue(Ark_Tuple_Dimension_Dimension& dst, const std::pair<const Dimension, const Dimension>& src)
{
    dst.value0 = ArkValue<Ark_Length>(src.first);
    dst.value1 = ArkValue<Ark_Length>(src.second);
}

void AssignArkValue(Ark_Tuple_Number_Number& dst, const Point& src)
{
    dst.value0 = ArkValue<Ark_Number>(src.GetX());
    dst.value1 = ArkValue<Ark_Number>(src.GetY());
}

void AssignArkValue(Ark_ShadowOptions& dst, const Shadow& src, ConvContext* ctx)
{
    dst.radius = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(src.GetBlurRadius());
    dst.type = Converter::ArkValue<Opt_ShadowType>(src.GetShadowType());
    dst.color = Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(
        src.GetColor().ColorToString(), ctx);
    auto offset = src.GetOffset();
    dst.offsetX = Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(offset.GetX());
    dst.offsetY = Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(offset.GetY());
    dst.fill = Converter::ArkValue<Opt_Boolean>(src.GetIsFilled());
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

void AssignArkValue(Ark_LeadingMarginPlaceholder& dst, const LeadingMargin& src)
{
    std::pair<const Dimension, const Dimension> pair = {src.size.Width(), src.size.Height()};
    dst.size = Converter::ArkValue<Ark_Tuple_Dimension_Dimension>(pair);
    if (src.pixmap) {
        dst.pixelMap = PixelMapPeer::Create(src.pixmap);
    }
}

void AssignArkValue(Ark_Length& dst, const double& src)
{
    dst.type = INTEROP_RUNTIME_NUMBER;
    dst.value = src;
    dst.unit = static_cast<int32_t>(OHOS::Ace::DimensionUnit::VP);
}

void AssignArkValue(Ark_Length& dst, const Dimension& src)
{
    dst.type = INTEROP_RUNTIME_NUMBER;
    dst.value = src.Unit() == DimensionUnit::PERCENT ? src.Value() * 100.f : src.Value();
    dst.unit = static_cast<int32_t>(src.Unit());
}

void AssignArkValue(Ark_Length& dst, const float& src)
{
    dst.type = INTEROP_RUNTIME_NUMBER;
    dst.value = src;
    dst.unit = static_cast<int32_t>(OHOS::Ace::DimensionUnit::VP);
}

void AssignArkValue(Ark_Length& dst, const CalcLength& src)
{
    dst = ArkValue<Ark_Length>(src.GetDimension());
}

void AssignArkValue(Ark_Number& dst, const int32_t& src)
{
    dst.tag = INTEROP_TAG_INT32;
    dst.i32 = src;
}

void AssignArkValue(Ark_Number& dst, const long& src)
{
    LOGE("Ark_Number doesn`t support long");
    dst.tag = INTEROP_TAG_INT32;
    dst.i32 = static_cast<int32_t>(src);
}

void AssignArkValue(Ark_Number& dst, const long long& src)
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

void AssignArkValue(Ark_Padding& dst, const PaddingProperty& src)
{
    Ark_Padding arkPadding = {
        .top = ArkValue<Opt_Length>(src.top),
        .right = ArkValue<Opt_Length>(src.right),
        .bottom = ArkValue<Opt_Length>(src.bottom),
        .left = ArkValue<Opt_Length>(src.left),
    };
    dst = arkPadding;
}

void AssignArkValue(Ark_PreviewText& dst, const PreviewText& src, ConvContext *ctx)
{
    dst.offset = ArkValue<Ark_Number>(src.offset);
    dst.value = ArkValue<Ark_String>(src.value, ctx);
}

void AssignArkValue(Ark_Length& dst, const int& id)
{
    dst.type = INTEROP_TAG_RESOURCE;
    dst.resource = id;
}

void AssignArkValue(Ark_Number& dst, const Dimension& src)
{
    auto value = static_cast<float>(src.ConvertToVp());
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

void AssignArkValue(Ark_DatePickerResult& dst, const std::string& src)
{
    auto json = JsonUtil::ParseJsonString(src);
    PickerDate date(
        json->GetValue(YEAR)->GetInt(),
        json->GetValue(MONTH)->GetInt(),
        json->GetValue(DAY)->GetInt());
    Validator::ValidatePickerDate(date);
    dst = {
        .year = Converter::ArkValue<Opt_Number>(date.GetYear()),
        .month = Converter::ArkValue<Opt_Number>(date.GetMonth()),
        .day = Converter::ArkValue<Opt_Number>(date.GetDay())
    };
}

void AssignArkValue(Ark_EventTarget& dst, const EventTarget& src)
{
    Ark_Area area;
    area.width = Converter::ArkValue<Ark_Length>(src.area.GetWidth());
    area.height = Converter::ArkValue<Ark_Length>(src.area.GetHeight());
    Ark_Position position;
    position.x = Converter::ArkValue<Opt_Length>(src.area.GetOffset().GetX());
    position.y = Converter::ArkValue<Opt_Length>(src.area.GetOffset().GetY());
    area.position = Converter::ArkValue<Ark_Position>(position);
    Ark_Position globPosition;
    globPosition.x = Converter::ArkValue<Opt_Length>(src.origin.GetX());
    globPosition.y = Converter::ArkValue<Opt_Length>(src.origin.GetY());
    area.globalPosition = Converter::ArkValue<Ark_Position>(globPosition);
    dst.area = area;
    dst.id = Converter::ArkValue<Opt_String>(src.id);
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
    return LengthMetricsPeer::Create(Dimension(value, du));
}

void AssignArkValue(Ark_Position& dst, const OffsetF& src)
{
    dst.x = Converter::ArkValue<Opt_Length>(src.GetX());
    dst.y = Converter::ArkValue<Opt_Length>(src.GetY());
}

void AssignArkValue(Ark_OffsetResult& dst, const Offset& src)
{
    dst.xOffset = ArkValue<Ark_Number>(src.GetX());
    dst.yOffset = ArkValue<Ark_Number>(src.GetY());
}

void AssignArkValue(Ark_RectResult& dst, const RectF& src)
{
    dst.x = ArkValue<Ark_Number>(src.GetX());
    dst.y = ArkValue<Ark_Number>(src.GetY());
    dst.width = ArkValue<Ark_Number>(src.Width());
    dst.height = ArkValue<Ark_Number>(src.Height());
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
    dst.start = Converter::ArkValue<Ark_Number>(src->GetStartIndex());
    dst.length = Converter::ArkValue<Ark_Number>(src->GetEndIndex() - src->GetStartIndex());
    dst.styledKey = Converter::ArkValue<Ark_StyledStringKey>(src->GetSpanType());
    switch (src->GetSpanType()) {
        case Ace::SpanType::Font:
            CreateStylePeer<TextStyle_styled_stringPeer, OHOS::Ace::FontSpan>(dst, src);
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
        case Ace::SpanType::CustomSpan: {
            LOGE("Converter::AssignArkValue(Ark_SpanStyle) the Ark_CustomSpan is not implemented.");
            break;
        }
        case Ace::SpanType::ExtSpan: {
            LOGE("Converter::AssignArkValue(Ark_SpanStyle) the Ark_UserDataSpan is not implemented.");
            break;
        }
        default: LOGE("Unexpected enum value in SpanType: %{public}d", src->GetSpanType());
    }
}

void AssignArkValue(Ark_Resource& dst, const std::variant<int32_t, std::string>& src, ConvContext *ctx)
{
    dst.id = ArkValue<Ark_Number>(-1);
    dst.params = ArkValue<Opt_Array_String>();
    if (auto name = std::get_if<std::string>(&src); name) {
        CHECK_NULL_VOID(ctx);
        std::vector<std::string> vecName { *name };
        auto arkName = Converter::ArkValue<Array_String>(vecName, ctx);
        dst.params = Converter::ArkValue<Opt_Array_String>(arkName, ctx);
    } else if (auto id = std::get_if<int32_t>(&src); id) {
        dst.id = ArkValue<Ark_Number>(*id);
    }
    dst.type = ArkValue<Opt_Number>(static_cast<Ark_Int32>(ResourceType::FLOAT));
}

void AssignArkValue(Ark_FontInfo& dst, const FontInfo& src, ConvContext *ctx)
{
    dst.path = ArkValue<Ark_String>(src.path, ctx);
    dst.postScriptName = ArkValue<Ark_String>(src.postScriptName, ctx);
    dst.fullName = ArkValue<Ark_String>(src.fullName, ctx);
    dst.family = ArkValue<Ark_String>(src.family, ctx);
    dst.subfamily = ArkValue<Ark_String>(src.subfamily, ctx);
    dst.weight = ArkValue<Ark_Number>(src.weight);
    dst.width = ArkValue<Ark_Number>(src.width);
    dst.italic = ArkValue<Ark_Boolean>(src.italic);
    dst.monoSpace = ArkValue<Ark_Boolean>(src.monoSpace);
    dst.symbolic = ArkValue<Ark_Boolean>(src.symbolic);
}

void AssignArkValue(Ark_Size& dst, const SizeF& src)
{
    dst.width = ArkValue<Ark_Number>(src.Width());
    dst.height = ArkValue<Ark_Number>(src.Height());
}

void AssignArkValue(Ark_String& dst, const Color& src, ConvContext *ctx)
{
    dst = ArkValue<Ark_String>(src.ToString(), ctx);
}

void AssignArkValue(Ark_BorderRadiuses& dst, const BorderRadiusProperty& src)
{
    Ark_BorderRadiuses arkBorder = {
        .topLeft = ArkValue<Opt_Length>(src.radiusTopLeft),
        .topRight = ArkValue<Opt_Length>(src.radiusTopRight),
        .bottomLeft = ArkValue<Opt_Length>(src.radiusBottomLeft),
        .bottomRight = ArkValue<Opt_Length>(src.radiusBottomRight),
    };
    dst = arkBorder;
}

void AssignArkValue(Ark_TextBackgroundStyle& dst, const TextBackgroundStyle& src, ConvContext *ctx)
{
    dst.radius = ArkUnion<Opt_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(src.backgroundRadius);
    dst.color = ArkUnion<Opt_ResourceColor, Ark_String>(src.backgroundColor, ctx);
}

void AssignArkValue(Ark_TextRange& dst, const SelectionInfo& src)
{
    dst.start = ArkValue<Opt_Number>(src.GetSelection().selection[0]);
    dst.end = ArkValue<Opt_Number>(src.GetSelection().selection[1]);
}

void AssignArkValue(Ark_Length& dst, const std::string& src)
{
    char *suffixPtr = nullptr;
    dst.type = INTEROP_TAG_FLOAT32;
    dst.value = std::strtof(src.c_str(), &suffixPtr);
    dst.unit = -NUM_1;
    if (!suffixPtr || suffixPtr == src.c_str()) { return; }
    if (suffixPtr[NUM_0] == '\0' || (suffixPtr[NUM_0] == 'v' && suffixPtr[NUM_1] == 'p')) {
        dst.unit = NUM_1;
    } else if (suffixPtr[NUM_0] == '%') {
        dst.unit = NUM_3;
    } else if (suffixPtr[NUM_0] == 'p' && suffixPtr[NUM_1] == 'x') {
        dst.unit = NUM_0;
    } else if (suffixPtr[NUM_0] == 'l' && suffixPtr[NUM_1] == 'p' && suffixPtr[NUM_2] == 'x') {
        dst.unit = NUM_4;
    } else if (suffixPtr[NUM_0] == 'f' && suffixPtr[NUM_1] == 'p') {
        dst.unit = NUM_2;
    }
}

void AssignArkValue(Ark_Resource& dst, const Ark_Length& src)
{
    dst.id = ArkValue<Ark_Number>(src.resource);
    dst.type = ArkValue<Opt_Number>(static_cast<Ark_Int32>(ResourceType::FLOAT));
    dst.params = ArkValue<Opt_Array_String>();
}

void AssignArkValue(Ark_TouchObject& dst, const OHOS::Ace::TouchLocationInfo& src)
{
    Offset globalOffset = src.GetGlobalLocation();
    Offset localOffset = src.GetLocalLocation();
    Offset screenOffset = src.GetScreenLocation();

    dst.displayX.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.displayX.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    dst.displayY.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.displayY.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));

    dst.id.tag = Ark_Tag::INTEROP_TAG_INT32;
    dst.id.i32 = static_cast<int32_t>(src.GetTouchDeviceId());

    dst.screenX.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.screenX.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    dst.screenY.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.screenY.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

    dst.type = static_cast<Ark_TouchType>(src.GetTouchType());

    dst.windowX.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.windowX.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    dst.windowY.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.windowY.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

    dst.x.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.x.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    dst.y.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.y.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    
    dst.pressedTime.tag = Ark_Tag::INTEROP_TAG_OBJECT;
    dst.pressedTime.value.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.pressedTime.value.f32 = static_cast<float>(
        src.GetPressedTime().time_since_epoch().count());

    dst.pressure.tag = Ark_Tag::INTEROP_TAG_OBJECT;
    dst.pressure.value.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.pressure.value.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(src.GetForce()));

    dst.width.tag = Ark_Tag::INTEROP_TAG_OBJECT;
    dst.width.value.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.width.value.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(src.GetWidth()));

    dst.height.tag = Ark_Tag::INTEROP_TAG_OBJECT;
    dst.height.value.tag = Ark_Tag::INTEROP_TAG_FLOAT32;
    dst.height.value.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(src.GetHeight()));
}

void AssignArkValue(Ark_HistoricalPoint& dst, const OHOS::Ace::TouchLocationInfo& src)
{
    AssignArkValue(dst.touchObject, src);
    dst.size = ArkValue<Ark_Number>(src.GetSize());
    dst.force = ArkValue<Ark_Number>(src.GetForce());
    dst.timestamp = src.GetTimeStamp().time_since_epoch().count();
}

void AssignArkValue(Ark_ImageError& dst, const LoadImageFailEvent& src)
{
    dst.componentWidth = Converter::ArkValue<Ark_Number>(src.GetComponentWidth());
    dst.componentHeight = Converter::ArkValue<Ark_Number>(src.GetComponentHeight());
    dst.message = Converter::ArkValue<Ark_String>(src.GetErrorMessage());
}

void AssignArkValue(Ark_ImageLoadResult& dst, const LoadImageSuccessEvent& src)
{
    dst.width = Converter::ArkValue<Ark_Number>(src.GetWidth());
    dst.height = Converter::ArkValue<Ark_Number>(src.GetHeight());
    dst.componentWidth = Converter::ArkValue<Ark_Number>(src.GetComponentWidth());
    dst.componentHeight = Converter::ArkValue<Ark_Number>(src.GetComponentHeight());
    dst.loadingStatus = Converter::ArkValue<Ark_Number>(src.GetLoadingStatus());
    dst.contentWidth = Converter::ArkValue<Ark_Number>(src.GetContentWidth());
    dst.contentHeight = Converter::ArkValue<Ark_Number>(src.GetContentHeight());
    dst.contentOffsetX = Converter::ArkValue<Ark_Number>(src.GetContentOffsetX());
    dst.contentOffsetY = Converter::ArkValue<Ark_Number>(src.GetContentOffsetY());
}

void AssignArkValue(Ark_RichEditorSymbolSpanStyle& dst, const SymbolSpanStyle& src)
{
    dst.fontSize = Converter::ArkUnion<Opt_Union_Number_String_Resource, Ark_Number>(src.fontSize);
    dst.fontWeight = Converter::ArkUnion<Opt_Union_Number_FontWeight_String, Ark_Number>(src.fontWeight);
    dst.effectStrategy.value = static_cast<Ark_SymbolEffectStrategy>(src.effectStrategy);
    dst.renderingStrategy.value = static_cast<Ark_SymbolRenderingStrategy>(src.renderingStrategy);
}

void AssignArkValue(Ark_Resource& dst, const ResourceObject& src, ConvContext *ctx)
{
    dst.bundleName = Converter::ArkValue<Ark_String>(src.GetBundleName(), ctx);
    dst.moduleName = Converter::ArkValue<Ark_String>(src.GetModuleName(), ctx);
    dst.id = Converter::ArkValue<Ark_Number>(src.GetId());

    std::vector<std::string> paramsArray;
    auto params = src.GetParams();
    for (const ResourceObjectParams& param : params) {
        if (param.value) {
            paramsArray.push_back(*param.value);
        }
    }
    auto arkArray = Converter::ArkValue<Array_String>(paramsArray, ctx);
    dst.params = Converter::ArkValue<Opt_Array_String>(arkArray, ctx);
    dst.type = Converter::ArkValue<Opt_Number>(src.GetType());
}

void AssignArkValue(Ark_RichEditorLayoutStyle& dst, const ImageStyleResult& src)
{
    dst.margin = ArkUnion<Opt_Union_Dimension_Margin, Ark_Length>(src.margin);
    dst.borderRadius = ArkUnion<Opt_Union_Dimension_BorderRadiuses, Ark_Length>(src.borderRadius);
}

void AssignArkValue(Ark_RichEditorImageSpanStyleResult& dst, const ImageStyleResult& src)
{
    dst.size.value0 = ArkValue<Ark_Number>(src.size[0]);
    dst.size.value1 = ArkValue<Ark_Number>(src.size[1]);
    dst.verticalAlign = ArkValue<Ark_ImageSpanAlignment>(
        static_cast<OHOS::Ace::VerticalAlign>(src.verticalAlign));
    dst.objectFit = ArkValue<Ark_ImageFit>(
        static_cast<OHOS::Ace::ImageFit>(src.objectFit));
    dst.layoutStyle = ArkValue<Opt_RichEditorLayoutStyle>(src);
}

void AssignArkValue(Ark_NavDestinationContext& dst, const RefPtr<NG::NavDestinationContext>& src)
{
    auto peer = GeneratedModifier::GetFullAPI()->getAccessors()->getNavDestinationContextAccessor()->ctor();
    peer->SetHandler(src);
    dst = peer;
}

void AssignArkValue(Ark_NavigationTransitionProxy& dst, const RefPtr<NavigationTransitionProxy>& src)
{
    auto peer = GeneratedModifier::GetFullAPI()->getAccessors()->getNavigationTransitionProxyAccessor()->ctor();
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
        dst.index = Converter::ArkValue<Ark_Number>(-1);
        return;
    }
    auto navPathInfo = src->GetNavPathInfo();
    if (navPathInfo) {
        auto name = navPathInfo->GetName();
        dst.name.tag = InteropTag::INTEROP_TAG_STRING;
        dst.name.value = Converter::ArkValue<Ark_String>(name, Converter::FC);
        dst.param.tag = InteropTag::INTEROP_TAG_UNDEFINED;
        // tbd: param info
    } else {
        dst.name.tag = InteropTag::INTEROP_TAG_UNDEFINED;
        dst.param.tag = InteropTag::INTEROP_TAG_UNDEFINED;
    }
    auto index = src->GetIndex();
    dst.index = Converter::ArkValue<Ark_Number>(index);
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
} // namespace OHOS::Ace::NG::Converter
