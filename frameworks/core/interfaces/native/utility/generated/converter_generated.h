/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!
 */

#ifndef CONVERTER_GENERATED_H
#define CONVERTER_GENERATED_H

#include <optional>
#include <cstdlib>
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "base/log/log_wrapper.h"

#define SELECTOR_ID_0 0
#define SELECTOR_ID_1 1
#define SELECTOR_ID_2 2
#define SELECTOR_ID_3 3
#define SELECTOR_ID_4 4
#define SELECTOR_ID_5 5
#define SELECTOR_ID_6 6
#define SELECTOR_ID_7 7
#define SELECTOR_ID_8 8
#define SELECTOR_ID_9 9
#define SELECTOR_ID_10 10
#define SELECTOR_ID_11 11
#define SELECTOR_ID_12 12
#define SELECTOR_ID_13 13
#define SELECTOR_ID_14 14
#define SELECTOR_ID_15 15

namespace OHOS::Ace::NG::Converter {

template<typename T, typename P>
void AssignTo(std::optional<T>& dst, const P& src);

template<typename T, typename P>
void AssignUnionTo(std::optional<T>& dst, const P& src);

template<typename T, typename P>
void AssignOptionalTo(std::optional<T>& dst, const P& src);

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Boolean_EditMode& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Boolean_Number& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Color_Number& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Color_Number_String& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ColorFilter_DrawingColorFilter& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ContentClipMode_RectShape& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Curve_ICurve& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Curve_String_ICurve& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_OptionWidthMode& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_PanelHeight& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_FontWeight_Number_String& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_FrameNode_Undefined& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_I64_String& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Length_LayoutPolicy& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Length_Number& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_FontStyle& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_FontWeight_String& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_LengthConstrain& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_String& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_String_FontWeight& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_String_PlaybackSpeed& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_TextAlign& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_TextCase& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_TextOverflow& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResponseType_RichEditorResponseType& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_SheetSize_Length& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_FunctionKey& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Number& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Number_CanvasGradient_CanvasPattern& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Undefined& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_SwiperAnimationMode_Boolean& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_TextInputStyle_TextContentStyle& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_TitleHeight_Length& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_VP& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_ColorFilterType& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_GestureType& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        case SELECTOR_ID_4: AssignTo(dst, src.value4); break;
        case SELECTOR_ID_5: AssignTo(dst, src.value5); break;
        case SELECTOR_ID_6: AssignTo(dst, src.value6); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_ResourceColor& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_ResourceStr& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_TipsMessageType& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Type_GaugeAttribute_colors_colors& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Type_PanGestureInterface_callable0_value& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Type_TextPickerOptions_range& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        case SELECTOR_ID_4: AssignTo(dst, src.value4); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Array_MenuElement_CustomBuilder& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Array_NavigationMenuItem_CustomBuilder& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Array_Rectangle_Rectangle& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Array_ToolbarItem_CustomBuilder& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_BadgePosition_Position& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_BlendMode_Blender& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Boolean_Callback_DismissPopupAction_Void& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Boolean_Resource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Boolean_ResourceStr_SymbolGlyphModifier& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_BorderStyle_EdgeStyles& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Color_Number_String_Resource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Color_String_Resource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Color_String_Resource_ColoringStrategy& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Color_String_Resource_Number& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ColumnOptions_ColumnOptionsV2& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Context_Undefined& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_CustomBuilder_DragItemInfo& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_CustomBuilder_DragItemInfo_String& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_CustomBuilder_SwipeActionItem& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_Array_Dimension& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_BorderRadiuses& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_EdgeOutlineWidths& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_EdgeWidths& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_LeadingMarginPlaceholder& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_Margin& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_OutlineRadiuses& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_DragPreviewMode_Array_DragPreviewMode& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_EdgeOutlineStyles_OutlineStyle& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_EdgeOutlineWidths_Dimension& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_EdgeStyles_BorderStyle& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ImageBitmap_PixelMap& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Length_BorderRadiuses& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Length_GridRowSizeOption& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_LengthMetrics_BorderRadiuses& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_LengthMetrics_LeadingMarginPlaceholder& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_LengthMetrics_Margin& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_LengthMetrics_Padding& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_LengthMetrics_String& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Margin_Dimension& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_MenuPreviewMode_CustomBuilder& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_NestedScrollOptions_NestedScrollOptionsExt& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_Array_Number& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_GridColColumnOption& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_GridRowColumnOption& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_InvertOptions& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_LeadingMarginPlaceholder& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_Literal_Number_offset_span& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_Resource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_ResourceStr& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_String_Array_Union_Number_String& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_String_Resource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Number_String_SwiperAutoFill& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_OutlineRadiuses_Dimension& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_OutlineStyle_EdgeOutlineStyles& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Padding_Dimension& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_PixelMap_ResourceStr& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ASTCResource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Position_Alignment& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_PX_VP_LPX_Resource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_RenderNode_Undefined& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Resource_String& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceColor_ColorContent& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceColor_ColoringStrategy& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceColor_LinearGradient& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceStr_ComponentContent& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceStr_CustomBuilder& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceStr_PixelMap& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceStr_PixelMap_SymbolGlyphModifier& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceStr_Scene& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceStr_TabBarSymbol& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceStr_Union_ResourceStr_ComponentContent& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_RowOptions_RowOptionsV2& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ScrollAnimationOptions_Boolean& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_SizeOptions_ImageSize& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Array_String& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_CustomBuilder_ComponentContent& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Number_Buffer_Resource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Number_Resource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Number_Resource_Buffer& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_PixelMap_Resource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Resource& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Resource_ComponentContent& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Resource_LinearGradient_common& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Resource_PixelMap& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_WebResourceRequest& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_WebController_WebviewController& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Type_NavDestinationAttribute_title_value& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        case SELECTOR_ID_4: AssignTo(dst, src.value4); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Type_NavigationAttribute_title_value& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ArrowStyle_Boolean& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Boolean_Literal_ResourceColor_color& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Boolean_PopupMaskType& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_BorderRadiuses_Length_LocalizedBorderRadiuses& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_CanvasRenderingContext2D_DrawingRenderingContext& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_BorderRadiuses_LocalizedBorderRadiuses& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Dimension_EdgeWidths_LocalizedEdgeWidths& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_EdgeColors_ResourceColor_LocalizedEdgeColors& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_EdgeWidths_Length_LocalizedEdgeWidths& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_EdgeWidths_LengthMetrics_LocalizedEdgeWidths& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_IconOptions_SymbolGlyphModifier& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Length_EdgeWidths_LocalizedEdgeWidths& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Length_GutterOption& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_LengthMetrics_BorderRadiuses_LocalizedBorderRadiuses& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Margin_Length_LocalizedMargin& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_MenuItemOptions_CustomBuilder& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_NavDestinationContext_NavBar& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Padding_Dimension_LocalizedPadding& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Padding_Length_LocalizedPadding& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Padding_LengthMetrics_LocalizedPadding& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Position_Edges_LocalizedEdges& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Position_LocalizedPosition& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_RectOptions_RoundedRectOptions& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_RectShapeOptions_RoundRectShapeOptions& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceColor_EdgeColors& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ResourceColor_UnderlineColor& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ShadowOptions_Array_ShadowOptions& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_ShadowOptions_ShadowStyle& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_SheetTitleOptions_CustomBuilder& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_Resource_CustomBuilder_TabBarOptions& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_TransitionOptions_TransitionEffect& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_Union_Padding_Dimension_LocalizedPadding& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_BorderRadiusType& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_StyledStringValue& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        case SELECTOR_ID_4: AssignTo(dst, src.value4); break;
        case SELECTOR_ID_5: AssignTo(dst, src.value5); break;
        case SELECTOR_ID_6: AssignTo(dst, src.value6); break;
        case SELECTOR_ID_7: AssignTo(dst, src.value7); break;
        case SELECTOR_ID_8: AssignTo(dst, src.value8); break;
        case SELECTOR_ID_9: AssignTo(dst, src.value9); break;
        case SELECTOR_ID_10: AssignTo(dst, src.value10); break;
        case SELECTOR_ID_11: AssignTo(dst, src.value11); break;
        case SELECTOR_ID_12: AssignTo(dst, src.value12); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Type_AlertDialog_show_value& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Type_RichEditorController_updateSpanStyle_value& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Type_SwiperAttribute_indicator_indicator& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_CancelButtonOptions_CancelButtonSymbolOptions& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_DotIndicator_DigitIndicator& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_DotIndicator_DigitIndicator_Boolean& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_String_ImageAttachment_CustomSpan& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_AttachmentType& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Type_TabContentAttribute_tabBar_content& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        case SELECTOR_ID_4: AssignTo(dst, src.value4); break;
        case SELECTOR_ID_5: AssignTo(dst, src.value5); break;
        case SELECTOR_ID_6: AssignTo(dst, src.value6); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_PopupOptions_CustomPopupOptions& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_RichEditorImageSpanResult_RichEditorTextSpanResult& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_RichEditorTextSpanResult_RichEditorImageSpanResult& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_Union_SubTabBarStyle_BottomTabBarStyle& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_RichEditorSpan& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T, typename P>
void AssignLiteralTo(std::optional<T>& dst, const P& src);

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Boolean_isVisible& src)
{
    AssignTo(dst, src.isVisible);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Function_callback__Object_fileSelector& src)
{
    AssignTo(dst, src.callback_);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Function_handler_Object_error& src)
{
    AssignTo(dst, src.handler);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Object_detail& src)
{
    AssignTo(dst, src.detail);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Type_ImageAttribute_onComplete_callback_event& src)
{
    AssignTo(dst, src.width);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Alignment_align& src)
{
    AssignTo(dst, src.align);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Boolean_next_Axis_direction& src)
{
    AssignTo(dst, src.next);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_angle_fingers& src)
{
    AssignTo(dst, src.fingers);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_day_month_year& src)
{
    AssignTo(dst, src.year);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_distance_fingers& src)
{
    AssignTo(dst, src.fingers);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_distance_fingers_PanDirection_direction& src)
{
    AssignTo(dst, src.fingers);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_duration_fingers_Boolean_repeat& src)
{
    AssignTo(dst, src.fingers);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_errcode_String_msg& src)
{
    AssignTo(dst, src.errcode);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_fingers_speed_SwipeDirection_direction& src)
{
    AssignTo(dst, src.fingers);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_index& src)
{
    AssignTo(dst, src.index);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_offset_span& src)
{
    AssignTo(dst, src.span);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_offsetRemain& src)
{
    AssignTo(dst, src.offsetRemain);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_surfaceHeight_surfaceWidth& src)
{
    AssignTo(dst, src.surfaceWidth);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Object_object__String_name_Array_String_methodList& src)
{
    AssignTo(dst, src.object_);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_HorizontalAlignParam& src)
{
    AssignTo(dst, src.anchor);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_VerticalAlignParam& src)
{
    AssignTo(dst, src.anchor);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_String_baseUrl_data_encoding_historyUrl_mimeType& src)
{
    AssignTo(dst, src.data);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_String_plainText& src)
{
    AssignTo(dst, src.plainText);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_String_script_Callback_String_Void_callback_& src)
{
    AssignTo(dst, src.script);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_String_target_NavigationType_type& src)
{
    AssignTo(dst, src.target);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_String_value_Callback_Void_action& src)
{
    AssignTo(dst, src.value);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_TransitionEffect_appear_disappear& src)
{
    AssignTo(dst, src.appear);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Type_CalendarInterface_callable0_value& src)
{
    AssignTo(dst, src.date);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Type_XComponentInterface_callable0_value& src)
{
    AssignTo(dst, src.id);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Type_XComponentInterface_callable1_value& src)
{
    AssignTo(dst, src.id);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal__want& src)
{
    AssignTo(dst, src.want);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Number_code__want& src)
{
    AssignTo(dst, src.code);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_ResourceColor_color& src)
{
    AssignTo(dst, src.color);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs& src)
{
    AssignTo(dst, src.xs);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Union_String_Resource_url_Array_Header_headers& src)
{
    AssignTo(dst, src.url);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_Literal_Union_String_WebResourceRequest_data& src)
{
    AssignTo(dst, src.data);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_TransitionEffects& src)
{
    AssignTo(dst, src.identity);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Ark_PopupButton& src)
{
    AssignTo(dst, src.value);
}

#define ASSIGN_OPT(name) \
template<typename T> \
void AssignOptionalTo(std::optional<T>& dst, const name& src) { \
    if (src.tag != INTEROP_TAG_UNDEFINED) { \
        AssignUnionTo(dst, src.value); \
    } \
} \
template<typename T> \
void WithOptional(const name& src, T call) { \
    if (src.tag != INTEROP_TAG_UNDEFINED) { \
        call(src.value); \
    } \
}
ASSIGN_OPT(Opt_Int32)
ASSIGN_OPT(Opt_AccessibilityCallback)
ASSIGN_OPT(Opt_AccessibilityFocusCallback)
ASSIGN_OPT(Opt_AccessibilityHoverType)
ASSIGN_OPT(Opt_AccessibilityRoleType)
ASSIGN_OPT(Opt_AccessibilitySamePageMode)
ASSIGN_OPT(Opt_AdaptiveColor)
ASSIGN_OPT(Opt_Affinity)
ASSIGN_OPT(Opt_Alignment)
ASSIGN_OPT(Opt_AlphabetIndexerAttribute)
ASSIGN_OPT(Opt_AnimatedDrawableDescriptor)
ASSIGN_OPT(Opt_AnimationMode)
ASSIGN_OPT(Opt_AnimationStatus)
ASSIGN_OPT(Opt_AppRotation)
ASSIGN_OPT(Opt_ArrowPointPosition)
ASSIGN_OPT(Opt_ArrowPosition)
ASSIGN_OPT(Opt_AutoCapitalizationMode)
ASSIGN_OPT(Opt_AvoidanceMode)
ASSIGN_OPT(Opt_Axis)
ASSIGN_OPT(Opt_AxisAction)
ASSIGN_OPT(Opt_AxisModel)
ASSIGN_OPT(Opt_BadgePosition)
ASSIGN_OPT(Opt_BarMode)
ASSIGN_OPT(Opt_BarPosition)
ASSIGN_OPT(Opt_BarrierDirection)
ASSIGN_OPT(Opt_BarState)
ASSIGN_OPT(Opt_BarStyle)
ASSIGN_OPT(Opt_BaseShape)
ASSIGN_OPT(Opt_BlendApplyType)
ASSIGN_OPT(Opt_BlendMode)
ASSIGN_OPT(Opt_BlurOnKeyboardHideMode)
ASSIGN_OPT(Opt_BlurStyle)
ASSIGN_OPT(Opt_BlurStyleActivePolicy)
ASSIGN_OPT(Opt_Boolean)
ASSIGN_OPT(Opt_BorderStyle)
ASSIGN_OPT(Opt_BreakpointsReference)
ASSIGN_OPT(Opt_Buffer)
ASSIGN_OPT(Opt_ButtonRole)
ASSIGN_OPT(Opt_ButtonStyleMode)
ASSIGN_OPT(Opt_ButtonType)
ASSIGN_OPT(Opt_CacheMode)
ASSIGN_OPT(Opt_CalendarAlign)
ASSIGN_OPT(Opt_CalendarController)
ASSIGN_OPT(Opt_CalendarPickerAttribute)
ASSIGN_OPT(Opt_CancelButtonStyle)
ASSIGN_OPT(Opt_CanvasGradient)
ASSIGN_OPT(Opt_CanvasPath)
ASSIGN_OPT(Opt_CanvasPattern)
ASSIGN_OPT(Opt_ChainEdgeEffect)
ASSIGN_OPT(Opt_ChainStyle)
ASSIGN_OPT(Opt_CheckBoxShape)
ASSIGN_OPT(Opt_CircleShape)
ASSIGN_OPT(Opt_ClickEffectLevel)
ASSIGN_OPT(Opt_ClientAuthenticationHandler)
ASSIGN_OPT(Opt_Color)
ASSIGN_OPT(Opt_ColorContent)
ASSIGN_OPT(Opt_ColorFilter)
ASSIGN_OPT(Opt_ColoringStrategy)
ASSIGN_OPT(Opt_ColorMode)
ASSIGN_OPT(Opt_CommonShape)
ASSIGN_OPT(Opt_Component3DAttribute)
ASSIGN_OPT(Opt_ComponentContent)
ASSIGN_OPT(Opt_ConsoleMessage)
ASSIGN_OPT(Opt_ContentClipMode)
ASSIGN_OPT(Opt_ContentType)
ASSIGN_OPT(Opt_ContextMenuEditStateFlags)
ASSIGN_OPT(Opt_ContextMenuInputFieldType)
ASSIGN_OPT(Opt_ContextMenuMediaType)
ASSIGN_OPT(Opt_ContextMenuSourceType)
ASSIGN_OPT(Opt_ControllerHandler)
ASSIGN_OPT(Opt_ControlSize)
ASSIGN_OPT(Opt_CopyOptions)
ASSIGN_OPT(Opt_CrownAction)
ASSIGN_OPT(Opt_CrownSensitivity)
ASSIGN_OPT(Opt_Curve)
ASSIGN_OPT(Opt_CustomDialogController)
ASSIGN_OPT(Opt_CustomObject)
ASSIGN_OPT(Opt_CustomSpan)
ASSIGN_OPT(Opt_DataOperationType)
ASSIGN_OPT(Opt_DataPanelType)
ASSIGN_OPT(Opt_DataResubmissionHandler)
ASSIGN_OPT(Opt_Date)
ASSIGN_OPT(Opt_DatePickerMode)
ASSIGN_OPT(Opt_DialogAlignment)
ASSIGN_OPT(Opt_DialogButtonDirection)
ASSIGN_OPT(Opt_DialogButtonStyle)
ASSIGN_OPT(Opt_Direction)
ASSIGN_OPT(Opt_DismissReason)
ASSIGN_OPT(Opt_DistributionType)
ASSIGN_OPT(Opt_DisturbanceFieldShape)
ASSIGN_OPT(Opt_DividerMode)
ASSIGN_OPT(Opt_DpiFollowStrategy)
ASSIGN_OPT(Opt_DragBehavior)
ASSIGN_OPT(Opt_DragEvent)
ASSIGN_OPT(Opt_DraggingSizeChangeEffect)
ASSIGN_OPT(Opt_DragPreviewMode)
ASSIGN_OPT(Opt_DragResult)
ASSIGN_OPT(Opt_DrawableDescriptor)
ASSIGN_OPT(Opt_DrawingCanvas)
ASSIGN_OPT(Opt_DrawingColorFilter)
ASSIGN_OPT(Opt_DrawingLattice)
ASSIGN_OPT(Opt_DrawModifier)
ASSIGN_OPT(Opt_DynamicRangeMode)
ASSIGN_OPT(Opt_Edge)
ASSIGN_OPT(Opt_EdgeEffect)
ASSIGN_OPT(Opt_EditMode)
ASSIGN_OPT(Opt_EffectDirection)
ASSIGN_OPT(Opt_EffectEdge)
ASSIGN_OPT(Opt_EffectFillStyle)
ASSIGN_OPT(Opt_EffectScope)
ASSIGN_OPT(Opt_EffectType)
ASSIGN_OPT(Opt_EllipseShape)
ASSIGN_OPT(Opt_EllipsisMode)
ASSIGN_OPT(Opt_EmbeddedType)
ASSIGN_OPT(Opt_EnterKeyType)
ASSIGN_OPT(Opt_EventResult)
ASSIGN_OPT(Opt_EventTargetInfo)
ASSIGN_OPT(Opt_FileSelectorMode)
ASSIGN_OPT(Opt_FileSelectorParam)
ASSIGN_OPT(Opt_FileSelectorResult)
ASSIGN_OPT(Opt_FillMode)
ASSIGN_OPT(Opt_Filter)
ASSIGN_OPT(Opt_FinishCallbackType)
ASSIGN_OPT(Opt_FlexAlign)
ASSIGN_OPT(Opt_FlexDirection)
ASSIGN_OPT(Opt_FlexWrap)
ASSIGN_OPT(Opt_Float32)
ASSIGN_OPT(Opt_FlyMode)
ASSIGN_OPT(Opt_FocusDrawLevel)
ASSIGN_OPT(Opt_FocusPriority)
ASSIGN_OPT(Opt_FoldStatus)
ASSIGN_OPT(Opt_FontStyle)
ASSIGN_OPT(Opt_FontWeight)
ASSIGN_OPT(Opt_FormDimension)
ASSIGN_OPT(Opt_FormRenderingMode)
ASSIGN_OPT(Opt_FormShape)
ASSIGN_OPT(Opt_FrameNode)
ASSIGN_OPT(Opt_FrictionMotion)
ASSIGN_OPT(Opt_FullScreenExitHandler)
ASSIGN_OPT(Opt_FullscreenInfo)
ASSIGN_OPT(Opt_Function)
ASSIGN_OPT(Opt_FunctionKey)
ASSIGN_OPT(Opt_GestureControl_GestureType)
ASSIGN_OPT(Opt_GestureGroupInterface)
ASSIGN_OPT(Opt_GestureJudgeResult)
ASSIGN_OPT(Opt_GestureMask)
ASSIGN_OPT(Opt_GestureMode)
ASSIGN_OPT(Opt_GestureModifier)
ASSIGN_OPT(Opt_GesturePriority)
ASSIGN_OPT(Opt_GestureRecognizer)
ASSIGN_OPT(Opt_GestureRecognizerState)
ASSIGN_OPT(Opt_GestureStyle)
ASSIGN_OPT(Opt_GradientDirection)
ASSIGN_OPT(Opt_GridAttribute)
ASSIGN_OPT(Opt_GridDirection)
ASSIGN_OPT(Opt_GridItemAlignment)
ASSIGN_OPT(Opt_GridItemStyle)
ASSIGN_OPT(Opt_GridRowDirection)
ASSIGN_OPT(Opt_HapticFeedbackMode)
ASSIGN_OPT(Opt_HeightBreakpoint)
ASSIGN_OPT(Opt_HitTestMode)
ASSIGN_OPT(Opt_HitTestType)
ASSIGN_OPT(Opt_HorizontalAlign)
ASSIGN_OPT(Opt_HoverEffect)
ASSIGN_OPT(Opt_HoverModeAreaType)
ASSIGN_OPT(Opt_HttpAuthHandler)
ASSIGN_OPT(Opt_ICurve)
ASSIGN_OPT(Opt_IlluminatedType)
ASSIGN_OPT(Opt_ImageAnalyzerController)
ASSIGN_OPT(Opt_ImageAnalyzerType)
ASSIGN_OPT(Opt_ImageContent)
ASSIGN_OPT(Opt_ImageFit)
ASSIGN_OPT(Opt_ImageInterpolation)
ASSIGN_OPT(Opt_ImageModifier)
ASSIGN_OPT(Opt_ImageRenderMode)
ASSIGN_OPT(Opt_ImageRepeat)
ASSIGN_OPT(Opt_ImageRotateOrientation)
ASSIGN_OPT(Opt_ImageSize)
ASSIGN_OPT(Opt_ImageSpanAlignment)
ASSIGN_OPT(Opt_IndexerAlign)
ASSIGN_OPT(Opt_IndicatorComponentController)
ASSIGN_OPT(Opt_InputType)
ASSIGN_OPT(Opt_Int64)
ASSIGN_OPT(Opt_IntentionCode)
ASSIGN_OPT(Opt_InteractionHand)
ASSIGN_OPT(Opt_ItemAlign)
ASSIGN_OPT(Opt_ItemState)
ASSIGN_OPT(Opt_JsGeolocation)
ASSIGN_OPT(Opt_JsResult)
ASSIGN_OPT(Opt_KeyboardAppearance)
ASSIGN_OPT(Opt_KeyboardAvoidMode)
ASSIGN_OPT(Opt_KeyProcessingMode)
ASSIGN_OPT(Opt_KeySource)
ASSIGN_OPT(Opt_KeyType)
ASSIGN_OPT(Opt_LaunchMode)
ASSIGN_OPT(Opt_LayeredDrawableDescriptor)
ASSIGN_OPT(Opt_LayoutDirection)
ASSIGN_OPT(Opt_LayoutManager)
ASSIGN_OPT(Opt_LayoutMode)
ASSIGN_OPT(Opt_LayoutPolicy)
ASSIGN_OPT(Opt_LayoutSafeAreaEdge)
ASSIGN_OPT(Opt_LayoutSafeAreaType)
ASSIGN_OPT(Opt_LayoutStyle)
ASSIGN_OPT(Opt_Length)
ASSIGN_OPT(Opt_LengthConstrain)
ASSIGN_OPT(Opt_LengthMetricsUnit)
ASSIGN_OPT(Opt_LengthUnit)
ASSIGN_OPT(Opt_LinearGradient)
ASSIGN_OPT(Opt_LinearIndicatorController)
ASSIGN_OPT(Opt_LineBreakStrategy)
ASSIGN_OPT(Opt_LineCapStyle)
ASSIGN_OPT(Opt_LineJoinStyle)
ASSIGN_OPT(Opt_ListAttribute)
ASSIGN_OPT(Opt_ListItemAlign)
ASSIGN_OPT(Opt_ListItemGroupArea)
ASSIGN_OPT(Opt_ListItemGroupStyle)
ASSIGN_OPT(Opt_ListItemStyle)
ASSIGN_OPT(Opt_ListScroller)
ASSIGN_OPT(Opt_Literal_Boolean_isVisible)
ASSIGN_OPT(Opt_Literal_Function_callback__Object_fileSelector)
ASSIGN_OPT(Opt_Literal_Function_handler_Object_error)
ASSIGN_OPT(Opt_Literal_Object_detail)
ASSIGN_OPT(Opt_LoadingProgressStyle)
ASSIGN_OPT(Opt_LocalizedBarrierDirection)
ASSIGN_OPT(Opt_LocationButtonOnClickResult)
ASSIGN_OPT(Opt_LocationDescription)
ASSIGN_OPT(Opt_LocationIconStyle)
ASSIGN_OPT(Opt_LongPressGestureInterface)
ASSIGN_OPT(Opt_LongPressRecognizer)
ASSIGN_OPT(Opt_MarqueeStartPolicy)
ASSIGN_OPT(Opt_MarqueeState)
ASSIGN_OPT(Opt_MarqueeUpdateStrategy)
ASSIGN_OPT(Opt_Matrix4Transit)
ASSIGN_OPT(Opt_MenuAlignType)
ASSIGN_OPT(Opt_MenuPolicy)
ASSIGN_OPT(Opt_MenuPreviewMode)
ASSIGN_OPT(Opt_MenuType)
ASSIGN_OPT(Opt_MessageLevel)
ASSIGN_OPT(Opt_MixedMode)
ASSIGN_OPT(Opt_ModalTransition)
ASSIGN_OPT(Opt_ModelType)
ASSIGN_OPT(Opt_ModifierKey)
ASSIGN_OPT(Opt_MouseAction)
ASSIGN_OPT(Opt_MouseButton)
ASSIGN_OPT(Opt_NativeEmbedStatus)
ASSIGN_OPT(Opt_NativeMediaPlayerConfig)
ASSIGN_OPT(Opt_NativePointer)
ASSIGN_OPT(Opt_NavBarPosition)
ASSIGN_OPT(Opt_NavDestinationActiveReason)
ASSIGN_OPT(Opt_NavDestinationAttribute)
ASSIGN_OPT(Opt_NavDestinationMode)
ASSIGN_OPT(Opt_NavigationAttribute)
ASSIGN_OPT(Opt_NavigationMode)
ASSIGN_OPT(Opt_NavigationOperation)
ASSIGN_OPT(Opt_NavigationSystemTransitionType)
ASSIGN_OPT(Opt_NavigationTitleMode)
ASSIGN_OPT(Opt_NavigationType)
ASSIGN_OPT(Opt_NavPathStack)
ASSIGN_OPT(Opt_NavRouteMode)
ASSIGN_OPT(Opt_NestedScrollMode)
ASSIGN_OPT(Opt_NestedScrollOptions)
ASSIGN_OPT(Opt_NodeContent)
ASSIGN_OPT(Opt_NodeController)
ASSIGN_OPT(Opt_Number)
ASSIGN_OPT(Opt_Object)
ASSIGN_OPT(Opt_ObscuredReasons)
ASSIGN_OPT(Opt_OffscreenCanvas)
ASSIGN_OPT(Opt_Offset)
ASSIGN_OPT(Opt_Offset_componentutils)
ASSIGN_OPT(Opt_OffsetResult)
ASSIGN_OPT(Opt_ScrollResult)
ASSIGN_OPT(Opt_OnAudioStateChangedEvent)
ASSIGN_OPT(Opt_OnConsoleEvent)
ASSIGN_OPT(Opt_OnDataResubmittedEvent)
ASSIGN_OPT(Opt_OnFirstContentfulPaintEvent)
ASSIGN_OPT(Opt_OnFoldStatusChangeInfo)
ASSIGN_OPT(Opt_OnOverScrollEvent)
ASSIGN_OPT(Opt_OnProgressChangeEvent)
ASSIGN_OPT(Opt_OnScaleChangeEvent)
ASSIGN_OPT(Opt_OnScrollEvent)
ASSIGN_OPT(Opt_OnScrollFrameBeginHandlerResult)
ASSIGN_OPT(Opt_OnSearchResultReceiveEvent)
ASSIGN_OPT(Opt_OnShowFileSelectorEvent)
ASSIGN_OPT(Opt_OptionWidthMode)
ASSIGN_OPT(Opt_OutlineStyle)
ASSIGN_OPT(Opt_OverScrollMode)
ASSIGN_OPT(Opt_PageFlipMode)
ASSIGN_OPT(Opt_PanDirection)
ASSIGN_OPT(Opt_PanelHeight)
ASSIGN_OPT(Opt_PanelMode)
ASSIGN_OPT(Opt_PanelType)
ASSIGN_OPT(Opt_PanGestureInterface)
ASSIGN_OPT(Opt_PanGestureOptions)
ASSIGN_OPT(Opt_PanRecognizer)
ASSIGN_OPT(Opt_ParticleEmitterShape)
ASSIGN_OPT(Opt_ParticleType)
ASSIGN_OPT(Opt_ParticleUpdater)
ASSIGN_OPT(Opt_PasteButtonOnClickResult)
ASSIGN_OPT(Opt_PasteDescription)
ASSIGN_OPT(Opt_PasteIconStyle)
ASSIGN_OPT(Opt_Path2D)
ASSIGN_OPT(Opt_PathShape)
ASSIGN_OPT(Opt_PatternLockChallengeResult)
ASSIGN_OPT(Opt_PatternLockController)
ASSIGN_OPT(Opt_PerfMonitorActionType)
ASSIGN_OPT(Opt_PerfMonitorSourceType)
ASSIGN_OPT(Opt_PermissionRequest)
ASSIGN_OPT(Opt_PinchGestureInterface)
ASSIGN_OPT(Opt_PinchRecognizer)
ASSIGN_OPT(Opt_PixelMap)
ASSIGN_OPT(Opt_PixelMapDrawableDescriptor)
ASSIGN_OPT(Opt_PixelMapMock)
ASSIGN_OPT(Opt_PixelRoundCalcPolicy)
ASSIGN_OPT(Opt_PixelRoundMode)
ASSIGN_OPT(Opt_Placement)
ASSIGN_OPT(Opt_PlaybackInfo)
ASSIGN_OPT(Opt_PlaybackSpeed)
ASSIGN_OPT(Opt_PlayMode)
ASSIGN_OPT(Opt_Point)
ASSIGN_OPT(Opt_PointerStyle)
ASSIGN_OPT(Opt_PopupStateChangeParam)
ASSIGN_OPT(Opt_PositionWithAffinity)
ASSIGN_OPT(Opt_PreDragStatus)
ASSIGN_OPT(Opt_PreparedInfo)
ASSIGN_OPT(Opt_ProgressMask)
ASSIGN_OPT(Opt_ProgressStatus)
ASSIGN_OPT(Opt_ProgressStyle)
ASSIGN_OPT(Opt_ProgressType)
ASSIGN_OPT(Opt_ProtectedResourceType)
ASSIGN_OPT(Opt_PulseSymbolEffect)
ASSIGN_OPT(Opt_RadioIndicatorType)
ASSIGN_OPT(Opt_Rect)
ASSIGN_OPT(Opt_RectHeightStyle)
ASSIGN_OPT(Opt_RectResult)
ASSIGN_OPT(Opt_RectShape)
ASSIGN_OPT(Opt_RectType)
ASSIGN_OPT(Opt_RectWidthStyle)
ASSIGN_OPT(Opt_RefreshStatus)
ASSIGN_OPT(Opt_RelateType)
ASSIGN_OPT(Opt_RenderExitReason)
ASSIGN_OPT(Opt_RenderFit)
ASSIGN_OPT(Opt_RenderMode)
ASSIGN_OPT(Opt_RenderProcessNotRespondingReason)
ASSIGN_OPT(Opt_RepeatMode)
ASSIGN_OPT(Opt_ResolutionQuality)
ASSIGN_OPT(Opt_ResponseType)
ASSIGN_OPT(Opt_RichEditorAttribute)
ASSIGN_OPT(Opt_RichEditorBaseController)
ASSIGN_OPT(Opt_RichEditorController)
ASSIGN_OPT(Opt_RichEditorDeleteDirection)
ASSIGN_OPT(Opt_RichEditorOptions)
ASSIGN_OPT(Opt_RichEditorResponseType)
ASSIGN_OPT(Opt_RichEditorSpanType)
ASSIGN_OPT(Opt_RichEditorStyledStringController)
ASSIGN_OPT(Opt_RichEditorStyledStringOptions)
ASSIGN_OPT(Opt_RootSceneSession)
ASSIGN_OPT(Opt_RotateResult)
ASSIGN_OPT(Opt_RotationGestureInterface)
ASSIGN_OPT(Opt_RotationRecognizer)
ASSIGN_OPT(Opt_RouteType)
ASSIGN_OPT(Opt_RRect)
ASSIGN_OPT(Opt_RunMetrics)
ASSIGN_OPT(Opt_SafeAreaEdge)
ASSIGN_OPT(Opt_SafeAreaType)
ASSIGN_OPT(Opt_SaveButtonOnClickResult)
ASSIGN_OPT(Opt_SaveDescription)
ASSIGN_OPT(Opt_SaveIconStyle)
ASSIGN_OPT(Opt_ScaleResult)
ASSIGN_OPT(Opt_Scene)
ASSIGN_OPT(Opt_ScreenCaptureHandler)
ASSIGN_OPT(Opt_ScrollableTargetInfo)
ASSIGN_OPT(Opt_ScrollAlign)
ASSIGN_OPT(Opt_ScrollAttribute)
ASSIGN_OPT(Opt_ScrollBarDirection)
ASSIGN_OPT(Opt_ScrollDirection)
ASSIGN_OPT(Opt_Scroller)
ASSIGN_OPT(Opt_ScrollMotion)
ASSIGN_OPT(Opt_ScrollSizeMode)
ASSIGN_OPT(Opt_ScrollSnapAlign)
ASSIGN_OPT(Opt_ScrollSource)
ASSIGN_OPT(Opt_ScrollState)
ASSIGN_OPT(Opt_SearchAttribute)
ASSIGN_OPT(Opt_SearchController)
ASSIGN_OPT(Opt_SearchType)
ASSIGN_OPT(Opt_SecurityComponentLayoutDirection)
ASSIGN_OPT(Opt_SeekMode)
ASSIGN_OPT(Opt_SelectAttribute)
ASSIGN_OPT(Opt_SelectedMode)
ASSIGN_OPT(Opt_SelectStatus)
ASSIGN_OPT(Opt_ShadowStyle)
ASSIGN_OPT(Opt_ShadowType)
ASSIGN_OPT(Opt_ShapeAttribute)
ASSIGN_OPT(Opt_ShapeClip)
ASSIGN_OPT(Opt_ShapeMask)
ASSIGN_OPT(Opt_SharedTransitionEffectType)
ASSIGN_OPT(Opt_SheetKeyboardAvoidMode)
ASSIGN_OPT(Opt_SheetMode)
ASSIGN_OPT(Opt_SheetSize)
ASSIGN_OPT(Opt_SheetType)
ASSIGN_OPT(Opt_SideBarContainerType)
ASSIGN_OPT(Opt_SideBarPosition)
ASSIGN_OPT(Opt_Size)
ASSIGN_OPT(Opt_SizeType)
ASSIGN_OPT(Opt_SlideEffect)
ASSIGN_OPT(Opt_SliderAttribute)
ASSIGN_OPT(Opt_SliderBlockType)
ASSIGN_OPT(Opt_SliderChangeMode)
ASSIGN_OPT(Opt_SliderInteraction)
ASSIGN_OPT(Opt_SliderStyle)
ASSIGN_OPT(Opt_SourceTool)
ASSIGN_OPT(Opt_SourceType)
ASSIGN_OPT(Opt_SpringMotion)
ASSIGN_OPT(Opt_SpringProp)
ASSIGN_OPT(Opt_SslError)
ASSIGN_OPT(Opt_SslErrorHandler)
ASSIGN_OPT(Opt_Sticky)
ASSIGN_OPT(Opt_StickyStyle)
ASSIGN_OPT(Opt_String)
ASSIGN_OPT(Opt_StyledString)
ASSIGN_OPT(Opt_StyledStringController)
ASSIGN_OPT(Opt_StyledStringKey)
ASSIGN_OPT(Opt_SubMenuExpandingMode)
ASSIGN_OPT(Opt_SubmitEvent)
ASSIGN_OPT(Opt_SwipeActionState)
ASSIGN_OPT(Opt_SwipeDirection)
ASSIGN_OPT(Opt_SwipeEdgeEffect)
ASSIGN_OPT(Opt_SwipeGestureInterface)
ASSIGN_OPT(Opt_SwiperAnimationEvent)
ASSIGN_OPT(Opt_SwiperAnimationMode)
ASSIGN_OPT(Opt_SwiperAttribute)
ASSIGN_OPT(Opt_SwiperContentTransitionProxy)
ASSIGN_OPT(Opt_SwiperContentWillScrollResult)
ASSIGN_OPT(Opt_SwiperController)
ASSIGN_OPT(Opt_SwiperDisplayMode)
ASSIGN_OPT(Opt_SwipeRecognizer)
ASSIGN_OPT(Opt_SwiperNestedScrollMode)
ASSIGN_OPT(Opt_SymbolEffect)
ASSIGN_OPT(Opt_SymbolEffectStrategy)
ASSIGN_OPT(Opt_SymbolGlyphAttribute)
ASSIGN_OPT(Opt_SymbolGlyphModifier)
ASSIGN_OPT(Opt_SymbolRenderingStrategy)
ASSIGN_OPT(Opt_TabContentTransitionProxy)
ASSIGN_OPT(Opt_TabsAnimationEvent)
ASSIGN_OPT(Opt_TabsAttribute)
ASSIGN_OPT(Opt_TabsCacheMode)
ASSIGN_OPT(Opt_TabsController)
ASSIGN_OPT(Opt_TapGestureInterface)
ASSIGN_OPT(Opt_TapRecognizer)
ASSIGN_OPT(Opt_TextAlign)
ASSIGN_OPT(Opt_TextAreaAttribute)
ASSIGN_OPT(Opt_TextAreaController)
ASSIGN_OPT(Opt_TextAreaType)
ASSIGN_OPT(Opt_TextAttribute)
ASSIGN_OPT(Opt_TextBaseController)
ASSIGN_OPT(Opt_TextCase)
ASSIGN_OPT(Opt_TextClockController)
ASSIGN_OPT(Opt_TextContentControllerBase)
ASSIGN_OPT(Opt_TextContentStyle)
ASSIGN_OPT(Opt_TextController)
ASSIGN_OPT(Opt_TextDataDetectorType)
ASSIGN_OPT(Opt_TextDecorationStyle)
ASSIGN_OPT(Opt_TextDecorationType)
ASSIGN_OPT(Opt_TextDeleteDirection)
ASSIGN_OPT(Opt_TextDirection)
ASSIGN_OPT(Opt_TextEditControllerEx)
ASSIGN_OPT(Opt_TextHeightAdaptivePolicy)
ASSIGN_OPT(Opt_TextInputAttribute)
ASSIGN_OPT(Opt_TextInputController)
ASSIGN_OPT(Opt_TextInputStyle)
ASSIGN_OPT(Opt_TextMenuItemId)
ASSIGN_OPT(Opt_TextMenuShowMode)
ASSIGN_OPT(Opt_TextMetrics)
ASSIGN_OPT(Opt_TextModifier)
ASSIGN_OPT(Opt_TextOptions)
ASSIGN_OPT(Opt_TextOverflow)
ASSIGN_OPT(Opt_TextOverflowOptions)
ASSIGN_OPT(Opt_TextResponseType)
ASSIGN_OPT(Opt_TextSelectableMode)
ASSIGN_OPT(Opt_TextSpanType)
ASSIGN_OPT(Opt_TextTimerController)
ASSIGN_OPT(Opt_ThemeColorMode)
ASSIGN_OPT(Opt_ThreatType)
ASSIGN_OPT(Opt_TileMode)
ASSIGN_OPT(Opt_TimePickerFormat)
ASSIGN_OPT(Opt_TimePickerResult)
ASSIGN_OPT(Opt_TitleHeight)
ASSIGN_OPT(Opt_ToggleType)
ASSIGN_OPT(Opt_ToolbarItemStatus)
ASSIGN_OPT(Opt_TouchTestInfo)
ASSIGN_OPT(Opt_TouchTestStrategy)
ASSIGN_OPT(Opt_TouchType)
ASSIGN_OPT(Opt_TransitionEdge)
ASSIGN_OPT(Opt_TransitionEffect)
ASSIGN_OPT(Opt_TransitionHierarchyStrategy)
ASSIGN_OPT(Opt_TransitionType)
ASSIGN_OPT(Opt_TranslateResult)
ASSIGN_OPT(Opt_Tuple_Dimension_Dimension)
ASSIGN_OPT(Opt_Tuple_Length_Length)
ASSIGN_OPT(Opt_Tuple_Number_Number)
ASSIGN_OPT(Opt_Tuple_Number_Number_Number)
ASSIGN_OPT(Opt_Tuple_Number_Number_Number_Number)
ASSIGN_OPT(Opt_Type_ImageAttribute_onComplete_callback_event)
ASSIGN_OPT(Opt_UICommonEvent)
ASSIGN_OPT(Opt_UIContext)
ASSIGN_OPT(Opt_UIExtensionProxy)
ASSIGN_OPT(Opt_UIGestureEvent)
ASSIGN_OPT(Opt_Undefined)
ASSIGN_OPT(Opt_UnifiedData)
ASSIGN_OPT(Opt_UniformDataType)
ASSIGN_OPT(Opt_Union_Boolean_EditMode)
ASSIGN_OPT(Opt_Union_Boolean_Number)
ASSIGN_OPT(Opt_Union_CircleShape_EllipseShape_PathShape_RectShape)
ASSIGN_OPT(Opt_Union_Color_Number)
ASSIGN_OPT(Opt_Union_Color_Number_String)
ASSIGN_OPT(Opt_Union_ColorFilter_DrawingColorFilter)
ASSIGN_OPT(Opt_Union_ContentClipMode_RectShape)
ASSIGN_OPT(Opt_Union_Curve_ICurve)
ASSIGN_OPT(Opt_Union_Curve_String_ICurve)
ASSIGN_OPT(Opt_Union_Dimension_OptionWidthMode)
ASSIGN_OPT(Opt_Union_Dimension_PanelHeight)
ASSIGN_OPT(Opt_Union_FontWeight_Number_String)
ASSIGN_OPT(Opt_Union_FrameNode_Undefined)
ASSIGN_OPT(Opt_Union_I64_String)
ASSIGN_OPT(Opt_Union_Length_LayoutPolicy)
ASSIGN_OPT(Opt_Union_Length_Number)
ASSIGN_OPT(Opt_Union_Number_FontStyle)
ASSIGN_OPT(Opt_Union_Number_FontWeight_String)
ASSIGN_OPT(Opt_Union_Number_LengthConstrain)
ASSIGN_OPT(Opt_Union_Number_String)
ASSIGN_OPT(Opt_Union_Number_String_FontWeight)
ASSIGN_OPT(Opt_Union_Number_String_PlaybackSpeed)
ASSIGN_OPT(Opt_Union_Number_TextAlign)
ASSIGN_OPT(Opt_Union_Number_TextCase)
ASSIGN_OPT(Opt_Union_Number_TextOverflow)
ASSIGN_OPT(Opt_Union_ResponseType_RichEditorResponseType)
ASSIGN_OPT(Opt_Union_SheetSize_Length)
ASSIGN_OPT(Opt_Union_String_FunctionKey)
ASSIGN_OPT(Opt_Union_String_Number)
ASSIGN_OPT(Opt_Union_String_Number_CanvasGradient_CanvasPattern)
ASSIGN_OPT(Opt_Union_String_Undefined)
ASSIGN_OPT(Opt_Union_SwiperAnimationMode_Boolean)
ASSIGN_OPT(Opt_Union_TextInputStyle_TextContentStyle)
ASSIGN_OPT(Opt_Union_TitleHeight_Length)
ASSIGN_OPT(Opt_UrlStyle)
ASSIGN_OPT(Opt_UserDataSpan)
ASSIGN_OPT(Opt_Vector2)
ASSIGN_OPT(Opt_Vector3)
ASSIGN_OPT(Opt_VerticalAlign)
ASSIGN_OPT(Opt_VideoController)
ASSIGN_OPT(Opt_View)
ASSIGN_OPT(Opt_ViewportFit)
ASSIGN_OPT(Opt_Visibility)
ASSIGN_OPT(Opt_VisualEffect)
ASSIGN_OPT(Opt_VP)
ASSIGN_OPT(Opt_WaterFlowAttribute)
ASSIGN_OPT(Opt_WaterFlowLayoutMode)
ASSIGN_OPT(Opt_WaterFlowSections)
ASSIGN_OPT(Opt_WaterRippleMode)
ASSIGN_OPT(Opt_WebAttribute)
ASSIGN_OPT(Opt_WebCaptureMode)
ASSIGN_OPT(Opt_WebContextMenuParam)
ASSIGN_OPT(Opt_WebContextMenuResult)
ASSIGN_OPT(Opt_WebController)
ASSIGN_OPT(Opt_WebCookie)
ASSIGN_OPT(Opt_WebDarkMode)
ASSIGN_OPT(Opt_WebElementType)
ASSIGN_OPT(Opt_WebHeader)
ASSIGN_OPT(Opt_WebKeyboardAvoidMode)
ASSIGN_OPT(Opt_WebKeyboardController)
ASSIGN_OPT(Opt_WebLayoutMode)
ASSIGN_OPT(Opt_WebNavigationType)
ASSIGN_OPT(Opt_WebResourceError)
ASSIGN_OPT(Opt_WebResourceRequest)
ASSIGN_OPT(Opt_WebResourceResponse)
ASSIGN_OPT(Opt_WebResponseType)
ASSIGN_OPT(Opt_WebviewController)
ASSIGN_OPT(Opt_Week)
ASSIGN_OPT(Opt_WidthBreakpoint)
ASSIGN_OPT(Opt_WindowAnimationTarget)
ASSIGN_OPT(Opt_WindowModeFollowStrategy)
ASSIGN_OPT(Opt_WindowSceneAttribute)
ASSIGN_OPT(Opt_WindowStatusType)
ASSIGN_OPT(Opt_WithThemeAttribute)
ASSIGN_OPT(Opt_WordBreak)
ASSIGN_OPT(Opt_WorkerEventListener)
ASSIGN_OPT(Opt_XComponentController)
ASSIGN_OPT(Opt_XComponentType)
ASSIGN_OPT(Opt_Array_AlertDialogButtonOptions)
ASSIGN_OPT(Opt_Array_Array_String)
ASSIGN_OPT(Opt_Array_BarrierStyle)
ASSIGN_OPT(Opt_Array_Buffer)
ASSIGN_OPT(Opt_Array_CalendarDay)
ASSIGN_OPT(Opt_Array_ColorStop)
ASSIGN_OPT(Opt_Array_DateRange)
ASSIGN_OPT(Opt_Array_DragPreviewMode)
ASSIGN_OPT(Opt_Array_ExpandedMenuItemOptions)
ASSIGN_OPT(Opt_Array_FingerInfo)
ASSIGN_OPT(Opt_Array_FractionStop)
ASSIGN_OPT(Opt_Array_GestureRecognizer)
ASSIGN_OPT(Opt_Array_GestureType)
ASSIGN_OPT(Opt_Array_GuideLineStyle)
ASSIGN_OPT(Opt_Array_Header)
ASSIGN_OPT(Opt_Array_HistoricalPoint)
ASSIGN_OPT(Opt_Array_ImageAnalyzerType)
ASSIGN_OPT(Opt_Array_ImageFrameInfo)
ASSIGN_OPT(Opt_Array_LayoutSafeAreaEdge)
ASSIGN_OPT(Opt_Array_LayoutSafeAreaType)
ASSIGN_OPT(Opt_Array_Length)
ASSIGN_OPT(Opt_Array_LengthMetrics)
ASSIGN_OPT(Opt_Array_LocalizedBarrierStyle)
ASSIGN_OPT(Opt_Array_MenuElement)
ASSIGN_OPT(Opt_Array_ModifierKey)
ASSIGN_OPT(Opt_Array_MouseButton)
ASSIGN_OPT(Opt_Array_NavDestinationTransition)
ASSIGN_OPT(Opt_Array_NavigationMenuItem)
ASSIGN_OPT(Opt_Array_NavPathInfo)
ASSIGN_OPT(Opt_Array_NestedScrollInfo)
ASSIGN_OPT(Opt_Array_Number)
ASSIGN_OPT(Opt_Array_Object)
ASSIGN_OPT(Opt_Array_ObscuredReasons)
ASSIGN_OPT(Opt_Array_Opt_Object)
ASSIGN_OPT(Opt_Array_PixelMap)
ASSIGN_OPT(Opt_Array_Point)
ASSIGN_OPT(Opt_Array_Rectangle)
ASSIGN_OPT(Opt_Array_RectType)
ASSIGN_OPT(Opt_Array_ResourceColor)
ASSIGN_OPT(Opt_Array_RichEditorImageSpanResult)
ASSIGN_OPT(Opt_Array_RichEditorParagraphResult)
ASSIGN_OPT(Opt_Array_RichEditorSpan)
ASSIGN_OPT(Opt_Array_RichEditorTextSpanResult)
ASSIGN_OPT(Opt_Array_SafeAreaEdge)
ASSIGN_OPT(Opt_Array_SafeAreaType)
ASSIGN_OPT(Opt_Array_ScriptItem)
ASSIGN_OPT(Opt_Array_Scroller)
ASSIGN_OPT(Opt_Array_SectionOptions)
ASSIGN_OPT(Opt_Array_SelectOption)
ASSIGN_OPT(Opt_Array_ShadowOptions)
ASSIGN_OPT(Opt_Array_SheetInfo)
ASSIGN_OPT(Opt_Array_SpanStyle)
ASSIGN_OPT(Opt_Array_String)
ASSIGN_OPT(Opt_Array_StyleOptions)
ASSIGN_OPT(Opt_Array_TextBox)
ASSIGN_OPT(Opt_Array_TextCascadePickerRangeContent)
ASSIGN_OPT(Opt_Array_TextDataDetectorType)
ASSIGN_OPT(Opt_Array_TextMenuItem)
ASSIGN_OPT(Opt_Array_TextPickerRangeContent)
ASSIGN_OPT(Opt_Array_ToolbarItem)
ASSIGN_OPT(Opt_Array_TouchObject)
ASSIGN_OPT(Opt_Array_TouchTestInfo)
ASSIGN_OPT(Opt_Array_Tuple_ResourceColor_Number)
ASSIGN_OPT(Opt_Array_Tuple_Union_ResourceColor_LinearGradient_Number)
ASSIGN_OPT(Opt_Array_UniformDataType)
ASSIGN_OPT(Opt_Array_Union_Color_Number)
ASSIGN_OPT(Opt_Array_Union_Number_String)
ASSIGN_OPT(Opt_Array_Union_ResourceColor_LinearGradient)
ASSIGN_OPT(Opt_Array_Union_RichEditorImageSpanResult_RichEditorTextSpanResult)
ASSIGN_OPT(Opt_Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult)
ASSIGN_OPT(Opt_Array_WebHeader)
ASSIGN_OPT(Opt_AsyncCallback_Array_TextMenuItem_Array_TextMenuItem)
ASSIGN_OPT(Opt_AsyncCallback_image_PixelMap_Void)
ASSIGN_OPT(Opt_AsyncCallback_TextMenuItem_TextRange_Boolean)
ASSIGN_OPT(Opt_ButtonTriggerClickCallback)
ASSIGN_OPT(Opt_Callback_Any_Void)
ASSIGN_OPT(Opt_Callback_Area_Area_Void)
ASSIGN_OPT(Opt_Callback_Array_Number_Void)
ASSIGN_OPT(Opt_Callback_Array_String_Void)
ASSIGN_OPT(Opt_Callback_Array_TextMenuItem_Void)
ASSIGN_OPT(Opt_Callback_Array_TouchTestInfo_TouchResult)
ASSIGN_OPT(Opt_Callback_AxisEvent_Void)
ASSIGN_OPT(Opt_Callback_Boolean)
ASSIGN_OPT(Opt_Callback_Boolean_HoverEvent_Void)
ASSIGN_OPT(Opt_Callback_Boolean_Void)
ASSIGN_OPT(Opt_Callback_Buffer_Void)
ASSIGN_OPT(Opt_Callback_CalendarRequestedData_Void)
ASSIGN_OPT(Opt_Callback_CalendarSelectedDate_Void)
ASSIGN_OPT(Opt_Callback_ClickEvent_Void)
ASSIGN_OPT(Opt_Callback_ComputedBarAttribute_Void)
ASSIGN_OPT(Opt_Callback_CopyEvent_Void)
ASSIGN_OPT(Opt_Callback_CrownEvent_Void)
ASSIGN_OPT(Opt_Callback_CustomBuilder_Void)
ASSIGN_OPT(Opt_Callback_CutEvent_Void)
ASSIGN_OPT(Opt_Callback_Date_Void)
ASSIGN_OPT(Opt_Callback_DatePickerResult_Void)
ASSIGN_OPT(Opt_Callback_DeleteValue_Boolean)
ASSIGN_OPT(Opt_Callback_DeleteValue_Void)
ASSIGN_OPT(Opt_Callback_DismissContentCoverAction_Void)
ASSIGN_OPT(Opt_Callback_DismissDialogAction_Void)
ASSIGN_OPT(Opt_Callback_DismissPopupAction_Void)
ASSIGN_OPT(Opt_Callback_DismissSheetAction_Void)
ASSIGN_OPT(Opt_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo)
ASSIGN_OPT(Opt_Callback_DragEvent_String_Void)
ASSIGN_OPT(Opt_Callback_EditableTextChangeValue_Boolean)
ASSIGN_OPT(Opt_Callback_EnterKeyType_Void)
ASSIGN_OPT(Opt_Callback_Extender_OnFinish)
ASSIGN_OPT(Opt_Callback_Extender_OnProgress)
ASSIGN_OPT(Opt_Callback_FocusAxisEvent_Void)
ASSIGN_OPT(Opt_Callback_FormCallbackInfo_Void)
ASSIGN_OPT(Opt_Callback_FullscreenInfo_Void)
ASSIGN_OPT(Opt_Callback_GestureEvent_Void)
ASSIGN_OPT(Opt_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult)
ASSIGN_OPT(Opt_Callback_GestureJudgeResult_Void)
ASSIGN_OPT(Opt_Callback_GestureRecognizer_Void)
ASSIGN_OPT(Opt_Callback_HitTestMode_Void)
ASSIGN_OPT(Opt_Callback_HoverEvent_Void)
ASSIGN_OPT(Opt_Callback_InsertValue_Boolean)
ASSIGN_OPT(Opt_Callback_InsertValue_Void)
ASSIGN_OPT(Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void)
ASSIGN_OPT(Opt_Callback_ItemDragInfo_Number_Number_Void)
ASSIGN_OPT(Opt_Callback_ItemDragInfo_Number_Void)
ASSIGN_OPT(Opt_Callback_ItemDragInfo_Void)
ASSIGN_OPT(Opt_Callback_KeyEvent_Boolean)
ASSIGN_OPT(Opt_Callback_KeyEvent_Void)
ASSIGN_OPT(Opt_Callback_Literal_Boolean_isVisible_Void)
ASSIGN_OPT(Opt_Callback_Literal_Function_handler_Object_error_Void)
ASSIGN_OPT(Opt_Callback_Literal_Number_code__want_Void)
ASSIGN_OPT(Opt_Callback_Literal_Number_errcode_String_msg_Void)
ASSIGN_OPT(Opt_Callback_Literal_Number_offsetRemain_Void)
ASSIGN_OPT(Opt_Callback_Literal_Object_detail_Boolean)
ASSIGN_OPT(Opt_Callback_Literal_String_plainText_Void)
ASSIGN_OPT(Opt_Callback_Map_String_Object_Void)
ASSIGN_OPT(Opt_Callback_MarqueeState_Void)
ASSIGN_OPT(Opt_Callback_MouseEvent_Void)
ASSIGN_OPT(Opt_Callback_NativeEmbedDataInfo_Void)
ASSIGN_OPT(Opt_Callback_NativeEmbedTouchInfo_Void)
ASSIGN_OPT(Opt_Callback_NavDestinationActiveReason_Void)
ASSIGN_OPT(Opt_Callback_NavDestinationContext_Void)
ASSIGN_OPT(Opt_Callback_NavigationMode_Void)
ASSIGN_OPT(Opt_Callback_NavigationTitleMode_Void)
ASSIGN_OPT(Opt_Callback_NavigationTransitionProxy_Void)
ASSIGN_OPT(Opt_Callback_Number_Boolean)
ASSIGN_OPT(Opt_Callback_Number_Number_Boolean)
ASSIGN_OPT(Opt_Callback_Number_Number_ComputedBarAttribute)
ASSIGN_OPT(Opt_Callback_Number_Number_Number_Void)
ASSIGN_OPT(Opt_Callback_Number_Number_PanelMode_Void)
ASSIGN_OPT(Opt_Callback_Number_Number_Void)
ASSIGN_OPT(Opt_Callback_Number_ScrollState_Literal_Number_offsetRemain)
ASSIGN_OPT(Opt_Callback_Number_SliderChangeMode_Void)
ASSIGN_OPT(Opt_Callback_Number_String_Void)
ASSIGN_OPT(Opt_Callback_Number_Tuple_Number_Number)
ASSIGN_OPT(Opt_Callback_Number_Tuple_Number_Number_Number_Number)
ASSIGN_OPT(Opt_Callback_Number_Void)
ASSIGN_OPT(Opt_Callback_Object_Void)
ASSIGN_OPT(Opt_Callback_OffsetResult_Void)
ASSIGN_OPT(Opt_Callback_ScrollResult_Void)
ASSIGN_OPT(Opt_Callback_OnAlertEvent_Boolean)
ASSIGN_OPT(Opt_Callback_OnAudioStateChangedEvent_Void)
ASSIGN_OPT(Opt_Callback_OnBeforeUnloadEvent_Boolean)
ASSIGN_OPT(Opt_Callback_OnClientAuthenticationEvent_Void)
ASSIGN_OPT(Opt_Callback_OnConfirmEvent_Boolean)
ASSIGN_OPT(Opt_Callback_OnConsoleEvent_Boolean)
ASSIGN_OPT(Opt_Callback_OnContextMenuShowEvent_Boolean)
ASSIGN_OPT(Opt_Callback_OnDataResubmittedEvent_Void)
ASSIGN_OPT(Opt_Callback_OnDownloadStartEvent_Void)
ASSIGN_OPT(Opt_Callback_OnErrorReceiveEvent_Void)
ASSIGN_OPT(Opt_Callback_OnFaviconReceivedEvent_Void)
ASSIGN_OPT(Opt_Callback_OnFirstContentfulPaintEvent_Void)
ASSIGN_OPT(Opt_Callback_OnGeolocationShowEvent_Void)
ASSIGN_OPT(Opt_Callback_OnHttpAuthRequestEvent_Boolean)
ASSIGN_OPT(Opt_Callback_OnHttpErrorReceiveEvent_Void)
ASSIGN_OPT(Opt_Callback_OnInterceptRequestEvent_WebResourceResponse)
ASSIGN_OPT(Opt_Callback_OnLoadInterceptEvent_Boolean)
ASSIGN_OPT(Opt_Callback_OnOverScrollEvent_Void)
ASSIGN_OPT(Opt_Callback_OnPageBeginEvent_Void)
ASSIGN_OPT(Opt_Callback_OnPageEndEvent_Void)
ASSIGN_OPT(Opt_Callback_OnPageVisibleEvent_Void)
ASSIGN_OPT(Opt_Callback_OnPermissionRequestEvent_Void)
ASSIGN_OPT(Opt_Callback_OnProgressChangeEvent_Void)
ASSIGN_OPT(Opt_Callback_OnPromptEvent_Boolean)
ASSIGN_OPT(Opt_Callback_OnRefreshAccessedHistoryEvent_Void)
ASSIGN_OPT(Opt_Callback_OnRenderExitedEvent_Void)
ASSIGN_OPT(Opt_Callback_OnResourceLoadEvent_Void)
ASSIGN_OPT(Opt_Callback_OnScaleChangeEvent_Void)
ASSIGN_OPT(Opt_Callback_OnScreenCaptureRequestEvent_Void)
ASSIGN_OPT(Opt_Callback_OnScrollEvent_Void)
ASSIGN_OPT(Opt_Callback_OnScrollFrameBeginHandlerResult_Void)
ASSIGN_OPT(Opt_Callback_OnSearchResultReceiveEvent_Void)
ASSIGN_OPT(Opt_Callback_OnShowFileSelectorEvent_Boolean)
ASSIGN_OPT(Opt_Callback_OnSslErrorEventReceiveEvent_Void)
ASSIGN_OPT(Opt_Callback_OnTitleReceiveEvent_Void)
ASSIGN_OPT(Opt_Callback_OnTouchIconUrlReceivedEvent_Void)
ASSIGN_OPT(Opt_Callback_OnWindowNewEvent_Void)
ASSIGN_OPT(Opt_Callback_Opt_Array_NavDestinationTransition_Void)
ASSIGN_OPT(Opt_Callback_Opt_Array_String_Void)
ASSIGN_OPT(Opt_Callback_Opt_Boolean_Void)
ASSIGN_OPT(Opt_Callback_Opt_NavigationAnimatedTransition_Void)
ASSIGN_OPT(Opt_Callback_Opt_Number_Void)
ASSIGN_OPT(Opt_Callback_Opt_PanelMode_Void)
ASSIGN_OPT(Opt_Callback_Opt_ResourceStr_Void)
ASSIGN_OPT(Opt_Callback_Opt_StyledString_Opt_Array_String_Void)
ASSIGN_OPT(Opt_Callback_Opt_TabContentAnimatedTransition_Void)
ASSIGN_OPT(Opt_Callback_Opt_Union_Number_Resource_Void)
ASSIGN_OPT(Opt_Callback_PlaybackInfo_Void)
ASSIGN_OPT(Opt_Callback_Pointer_Void)
ASSIGN_OPT(Opt_Callback_PopInfo_Void)
ASSIGN_OPT(Opt_Callback_PreDragStatus_Void)
ASSIGN_OPT(Opt_Callback_PreparedInfo_Void)
ASSIGN_OPT(Opt_Callback_RangeUpdate)
ASSIGN_OPT(Opt_Callback_RefreshStatus_Void)
ASSIGN_OPT(Opt_Callback_ResourceStr_Void)
ASSIGN_OPT(Opt_Callback_RichEditorChangeValue_Boolean)
ASSIGN_OPT(Opt_Callback_RichEditorDeleteValue_Boolean)
ASSIGN_OPT(Opt_Callback_RichEditorInsertValue_Boolean)
ASSIGN_OPT(Opt_Callback_RichEditorRange_Void)
ASSIGN_OPT(Opt_Callback_RichEditorSelection_Void)
ASSIGN_OPT(Opt_Callback_RichEditorTextSpanResult_Void)
ASSIGN_OPT(Opt_Callback_SheetDismiss_Void)
ASSIGN_OPT(Opt_Callback_SheetType_Void)
ASSIGN_OPT(Opt_Callback_SpringBackAction_Void)
ASSIGN_OPT(Opt_Callback_String_Number_Void)
ASSIGN_OPT(Opt_Callback_String_Opt_Object_Void)
ASSIGN_OPT(Opt_Callback_String_PasteEvent_Void)
ASSIGN_OPT(Opt_Callback_String_Void)
ASSIGN_OPT(Opt_Callback_StyledStringChangeValue_Boolean)
ASSIGN_OPT(Opt_Callback_StyledStringMarshallingValue_Void)
ASSIGN_OPT(Opt_Callback_SwipeActionState_Void)
ASSIGN_OPT(Opt_Callback_SwiperContentTransitionProxy_Void)
ASSIGN_OPT(Opt_Callback_TabContentTransitionProxy_Void)
ASSIGN_OPT(Opt_Callback_TerminationInfo_Void)
ASSIGN_OPT(Opt_Callback_TextPickerResult_Void)
ASSIGN_OPT(Opt_Callback_TextRange_Void)
ASSIGN_OPT(Opt_Callback_TimePickerResult_Void)
ASSIGN_OPT(Opt_Callback_TouchEvent_HitTestMode)
ASSIGN_OPT(Opt_Callback_TouchEvent_Void)
ASSIGN_OPT(Opt_Callback_TouchResult_Void)
ASSIGN_OPT(Opt_Callback_Tuple_Number_Number_Number_Number_Void)
ASSIGN_OPT(Opt_Callback_Tuple_Number_Number_Void)
ASSIGN_OPT(Opt_Callback_Type_ImageAttribute_onComplete_callback_event_Void)
ASSIGN_OPT(Opt_Callback_UIExtensionProxy_Void)
ASSIGN_OPT(Opt_Callback_Union_CustomBuilder_DragItemInfo_Void)
ASSIGN_OPT(Opt_Callback_Union_Number_Array_Number_Void)
ASSIGN_OPT(Opt_Callback_Union_String_Array_String_Void)
ASSIGN_OPT(Opt_Callback_Void)
ASSIGN_OPT(Opt_Callback_WebKeyboardOptions_Void)
ASSIGN_OPT(Opt_Callback_WebResourceResponse_Void)
ASSIGN_OPT(Opt_Callback_WithThemeAttribute_Void)
ASSIGN_OPT(Opt_Callback_WrappedBuilder_Args_Void)
ASSIGN_OPT(Opt_ContentDidScrollCallback)
ASSIGN_OPT(Opt_ContentWillScrollCallback)
ASSIGN_OPT(Opt_Context_getGroupDir_Callback)
ASSIGN_OPT(Opt_CustomNodeBuilder)
ASSIGN_OPT(Opt_EditableTextOnChangeCallback)
ASSIGN_OPT(Opt_ErrorCallback)
ASSIGN_OPT(Opt_GestureRecognizerJudgeBeginCallback)
ASSIGN_OPT(Opt_GetItemMainSizeByIndex)
ASSIGN_OPT(Opt_GridAttribute_onItemDragStart_event_type)
ASSIGN_OPT(Opt_HoverCallback)
ASSIGN_OPT(Opt_ImageCompleteCallback)
ASSIGN_OPT(Opt_ImageErrorCallback)
ASSIGN_OPT(Opt_InterceptionModeCallback)
ASSIGN_OPT(Opt_InterceptionShowCallback)
ASSIGN_OPT(Opt_ListAttribute_onItemDragStart_event_type)
ASSIGN_OPT(Opt_LocationButtonCallback)
ASSIGN_OPT(Opt_Map_AxisModel_Number)
ASSIGN_OPT(Opt_Map_Number_RunMetrics)
ASSIGN_OPT(Opt_Map_String_ComponentContent)
ASSIGN_OPT(Opt_Map_String_Int64)
ASSIGN_OPT(Opt_Map_String_Object)
ASSIGN_OPT(Opt_Map_String_String)
ASSIGN_OPT(Opt_MenuCallback)
ASSIGN_OPT(Opt_MenuOnAppearCallback)
ASSIGN_OPT(Opt_NavDestinationTransitionDelegate)
ASSIGN_OPT(Opt_NavExtender_OnUpdateStack)
ASSIGN_OPT(Opt_OnAdsBlockedCallback)
ASSIGN_OPT(Opt_OnAlphabetIndexerPopupSelectCallback)
ASSIGN_OPT(Opt_OnAlphabetIndexerRequestPopupDataCallback)
ASSIGN_OPT(Opt_OnAlphabetIndexerSelectCallback)
ASSIGN_OPT(Opt_OnCheckboxChangeCallback)
ASSIGN_OPT(Opt_OnCheckboxGroupChangeCallback)
ASSIGN_OPT(Opt_OnContentScrollCallback)
ASSIGN_OPT(Opt_OnContextMenuHideCallback)
ASSIGN_OPT(Opt_OnDidChangeCallback)
ASSIGN_OPT(Opt_OnDragEventCallback)
ASSIGN_OPT(Opt_OnFirstMeaningfulPaintCallback)
ASSIGN_OPT(Opt_OnFoldStatusChangeCallback)
ASSIGN_OPT(Opt_OnFullScreenEnterCallback)
ASSIGN_OPT(Opt_OnHoverCallback)
ASSIGN_OPT(Opt_OnHoverStatusChangeCallback)
ASSIGN_OPT(Opt_OnIntelligentTrackingPreventionCallback)
ASSIGN_OPT(Opt_OnLargestContentfulPaintCallback)
ASSIGN_OPT(Opt_OnLinearIndicatorChangeCallback)
ASSIGN_OPT(Opt_OnMoveHandler)
ASSIGN_OPT(Opt_OnNativeEmbedVisibilityChangeCallback)
ASSIGN_OPT(Opt_OnNativeLoadCallback)
ASSIGN_OPT(Opt_OnNavigationEntryCommittedCallback)
ASSIGN_OPT(Opt_OnOverrideUrlLoadingCallback)
ASSIGN_OPT(Opt_OnPasteCallback)
ASSIGN_OPT(Opt_OnRadioChangeCallback)
ASSIGN_OPT(Opt_OnRatingChangeCallback)
ASSIGN_OPT(Opt_OnRenderProcessNotRespondingCallback)
ASSIGN_OPT(Opt_OnRenderProcessRespondingCallback)
ASSIGN_OPT(Opt_OnSafeBrowsingCheckResultCallback)
ASSIGN_OPT(Opt_OnScrollCallback)
ASSIGN_OPT(Opt_OnScrollEdgeCallback)
ASSIGN_OPT(Opt_OnScrollFrameBeginCallback)
ASSIGN_OPT(Opt_OnScrollVisibleContentChangeCallback)
ASSIGN_OPT(Opt_OnSelectCallback)
ASSIGN_OPT(Opt_OnSslErrorEventCallback)
ASSIGN_OPT(Opt_OnSubmitCallback)
ASSIGN_OPT(Opt_OnSwiperAnimationEndCallback)
ASSIGN_OPT(Opt_OnSwiperAnimationStartCallback)
ASSIGN_OPT(Opt_OnSwiperGestureSwipeCallback)
ASSIGN_OPT(Opt_OnTabsAnimationEndCallback)
ASSIGN_OPT(Opt_OnTabsAnimationStartCallback)
ASSIGN_OPT(Opt_OnTabsContentWillChangeCallback)
ASSIGN_OPT(Opt_OnTabsGestureSwipeCallback)
ASSIGN_OPT(Opt_OnTextPickerChangeCallback)
ASSIGN_OPT(Opt_OnTextSelectionChangeCallback)
ASSIGN_OPT(Opt_OnTimePickerChangeCallback)
ASSIGN_OPT(Opt_OnViewportFitChangedCallback)
ASSIGN_OPT(Opt_PageTransitionCallback)
ASSIGN_OPT(Opt_PasteButtonCallback)
ASSIGN_OPT(Opt_PasteEventCallback)
ASSIGN_OPT(Opt_PluginErrorCallback)
ASSIGN_OPT(Opt_PopupStateChangeCallback)
ASSIGN_OPT(Opt_Profiler_Callback_String_Void)
ASSIGN_OPT(Opt_ReceiveCallback)
ASSIGN_OPT(Opt_RestrictedWorker_onerror_Callback)
ASSIGN_OPT(Opt_RestrictedWorker_onexit_Callback)
ASSIGN_OPT(Opt_RestrictedWorker_onmessage_Callback)
ASSIGN_OPT(Opt_ReuseIdCallback)
ASSIGN_OPT(Opt_SaveButtonCallback)
ASSIGN_OPT(Opt_ScrollOnScrollCallback)
ASSIGN_OPT(Opt_ScrollOnWillScrollCallback)
ASSIGN_OPT(Opt_OnWillScrollCallback)
ASSIGN_OPT(Opt_SearchSubmitCallback)
ASSIGN_OPT(Opt_SearchValueCallback)
ASSIGN_OPT(Opt_ShouldBuiltInRecognizerParallelWithCallback)
ASSIGN_OPT(Opt_SizeChangeCallback)
ASSIGN_OPT(Opt_SliderTriggerChangeCallback)
ASSIGN_OPT(Opt_StyledStringMarshallCallback)
ASSIGN_OPT(Opt_StyledStringUnmarshallCallback)
ASSIGN_OPT(Opt_SubmitCallback)
ASSIGN_OPT(Opt_TabsCustomContentTransitionCallback)
ASSIGN_OPT(Opt_TextAreaSubmitCallback)
ASSIGN_OPT(Opt_TextFieldValueCallback)
ASSIGN_OPT(Opt_TextPickerEnterSelectedAreaCallback)
ASSIGN_OPT(Opt_TextPickerScrollStopCallback)
ASSIGN_OPT(Opt_TextTimerAttribute_onTimer_event_type)
ASSIGN_OPT(Opt_TransitionFinishCallback)
ASSIGN_OPT(Opt_Type_NavigationAttribute_customNavContentTransition_delegate)
ASSIGN_OPT(Opt_Type_TextPickerAttribute_onChange_callback)
ASSIGN_OPT(Opt_Type_WebAttribute_onFileSelectorShow_callback)
ASSIGN_OPT(Opt_Type_WebAttribute_onUrlLoadIntercept_callback)
ASSIGN_OPT(Opt_VisibleAreaChangeCallback)
ASSIGN_OPT(Opt_VoidCallback)
ASSIGN_OPT(Opt_WebKeyboardCallback)
ASSIGN_OPT(Opt_WithThemeInterface)
ASSIGN_OPT(Opt_AccessibilityOptions)
ASSIGN_OPT(Opt_AdsBlockedDetails)
ASSIGN_OPT(Opt_AlphabetIndexerOptions)
ASSIGN_OPT(Opt_AnimationOptions)
ASSIGN_OPT(Opt_AnimationRange_Number)
ASSIGN_OPT(Opt_AppearSymbolEffect)
ASSIGN_OPT(Opt_ASTCResource)
ASSIGN_OPT(Opt_AutoPlayOptions)
ASSIGN_OPT(Opt_BackgroundBrightnessOptions)
ASSIGN_OPT(Opt_BackgroundImageOptions)
ASSIGN_OPT(Opt_BarGridColumnOptions)
ASSIGN_OPT(Opt_BarrierStyle)
ASSIGN_OPT(Opt_BaseContext)
ASSIGN_OPT(Opt_BaselineOffsetStyle)
ASSIGN_OPT(Opt_Bias)
ASSIGN_OPT(Opt_BlurOptions)
ASSIGN_OPT(Opt_BoardStyle)
ASSIGN_OPT(Opt_BorderRadiuses)
ASSIGN_OPT(Opt_BorderRadiuses_graphics)
ASSIGN_OPT(Opt_BounceSymbolEffect)
ASSIGN_OPT(Opt_BreakPoints)
ASSIGN_OPT(Opt_BrightnessBlender)
ASSIGN_OPT(Opt_BusinessError)
ASSIGN_OPT(Opt_ButtonOptions)
ASSIGN_OPT(Opt_CalendarDay)
ASSIGN_OPT(Opt_CalendarRequestedData)
ASSIGN_OPT(Opt_CalendarSelectedDate)
ASSIGN_OPT(Opt_CancelButtonSymbolOptions)
ASSIGN_OPT(Opt_CaretOffset)
ASSIGN_OPT(Opt_ChainAnimationOptions)
ASSIGN_OPT(Opt_ChainWeightOptions)
ASSIGN_OPT(Opt_CheckboxGroupOptions)
ASSIGN_OPT(Opt_CheckboxGroupResult)
ASSIGN_OPT(Opt_CheckboxOptions)
ASSIGN_OPT(Opt_ChildrenMainSize)
ASSIGN_OPT(Opt_Circle)
ASSIGN_OPT(Opt_CircleOptions)
ASSIGN_OPT(Opt_ClickEffect)
ASSIGN_OPT(Opt_CloseSwipeActionOptions)
ASSIGN_OPT(Opt_ColorFilterType)
ASSIGN_OPT(Opt_ColorMetrics)
ASSIGN_OPT(Opt_ColumnOptions)
ASSIGN_OPT(Opt_ColumnOptionsV2)
ASSIGN_OPT(Opt_ColumnSplitDividerStyle)
ASSIGN_OPT(Opt_CommandPath)
ASSIGN_OPT(Opt_CommonConfiguration)
ASSIGN_OPT(Opt_CommonModifier)
ASSIGN_OPT(Opt_ComputedBarAttribute)
ASSIGN_OPT(Opt_ConstraintSizeOptions)
ASSIGN_OPT(Opt_Context)
ASSIGN_OPT(Opt_CopyEvent)
ASSIGN_OPT(Opt_CornerRadius)
ASSIGN_OPT(Opt_CrownEvent)
ASSIGN_OPT(Opt_CustomSpanDrawInfo)
ASSIGN_OPT(Opt_CustomSpanMeasureInfo)
ASSIGN_OPT(Opt_CustomSpanMetrics)
ASSIGN_OPT(Opt_CutEvent)
ASSIGN_OPT(Opt_DataPanelOptions)
ASSIGN_OPT(Opt_DataSyncOptions)
ASSIGN_OPT(Opt_DatePickerOptions)
ASSIGN_OPT(Opt_DatePickerResult)
ASSIGN_OPT(Opt_DateRange)
ASSIGN_OPT(Opt_DateTimeOptions)
ASSIGN_OPT(Opt_DeleteValue)
ASSIGN_OPT(Opt_DirectionalEdgesT)
ASSIGN_OPT(Opt_DisappearSymbolEffect)
ASSIGN_OPT(Opt_DismissContentCoverAction)
ASSIGN_OPT(Opt_DismissDialogAction)
ASSIGN_OPT(Opt_DismissPopupAction)
ASSIGN_OPT(Opt_DismissSheetAction)
ASSIGN_OPT(Opt_DoubleAnimationParam)
ASSIGN_OPT(Opt_DragInteractionOptions)
ASSIGN_OPT(Opt_DragItemInfo)
ASSIGN_OPT(Opt_DrawContext)
ASSIGN_OPT(Opt_DrawingRenderingContext)
ASSIGN_OPT(Opt_DropOptions)
ASSIGN_OPT(Opt_EdgeEffectOptions)
ASSIGN_OPT(Opt_EdgeOutlineStyles)
ASSIGN_OPT(Opt_EdgeOutlineWidths)
ASSIGN_OPT(Opt_Edges)
ASSIGN_OPT(Opt_EdgeStyles)
ASSIGN_OPT(Opt_EdgeWidths)
ASSIGN_OPT(Opt_EditMenuOptions)
ASSIGN_OPT(Opt_EllipseOptions)
ASSIGN_OPT(Opt_EmbedOptions)
ASSIGN_OPT(Opt_ErrorEvent)
ASSIGN_OPT(Opt_Event)
ASSIGN_OPT(Opt_ExpectedFrameRateRange)
ASSIGN_OPT(Opt_FingerInfo)
ASSIGN_OPT(Opt_FirstMeaningfulPaint)
ASSIGN_OPT(Opt_FocusMovement)
ASSIGN_OPT(Opt_FolderStackOptions)
ASSIGN_OPT(Opt_FontInfo)
ASSIGN_OPT(Opt_FontSettingOptions)
ASSIGN_OPT(Opt_ForegroundEffectOptions)
ASSIGN_OPT(Opt_FormCallbackInfo)
ASSIGN_OPT(Opt_FormLinkOptions)
ASSIGN_OPT(Opt_FractionStop)
ASSIGN_OPT(Opt_Frame)
ASSIGN_OPT(Opt_FullScreenEnterEvent)
ASSIGN_OPT(Opt_GaugeOptions)
ASSIGN_OPT(Opt_GeometryTransitionOptions)
ASSIGN_OPT(Opt_GestureInfo)
ASSIGN_OPT(Opt_GestureStyleInterface)
ASSIGN_OPT(Opt_GestureType)
ASSIGN_OPT(Opt_GridColColumnOption)
ASSIGN_OPT(Opt_GridContainerOptions)
ASSIGN_OPT(Opt_GridItemOptions)
ASSIGN_OPT(Opt_GridLayoutOptions)
ASSIGN_OPT(Opt_GridRowColumnOption)
ASSIGN_OPT(Opt_GridRowSizeOption)
ASSIGN_OPT(Opt_GuideLinePosition)
ASSIGN_OPT(Opt_GuideLineStyle)
ASSIGN_OPT(Opt_Header)
ASSIGN_OPT(Opt_HierarchicalSymbolEffect)
ASSIGN_OPT(Opt_HoverEventParam)
ASSIGN_OPT(Opt_ImageAIOptions)
ASSIGN_OPT(Opt_ImageAnalyzerConfig)
ASSIGN_OPT(Opt_ImageBitmap)
ASSIGN_OPT(Opt_ImageData)
ASSIGN_OPT(Opt_ImageError)
ASSIGN_OPT(Opt_ImageLoadResult)
ASSIGN_OPT(Opt_ImageSourceSize)
ASSIGN_OPT(Opt_ImmersiveMode)
ASSIGN_OPT(Opt_InputCounterOptions)
ASSIGN_OPT(Opt_InsertValue)
ASSIGN_OPT(Opt_IntelligentTrackingPreventionDetails)
ASSIGN_OPT(Opt_InvertOptions)
ASSIGN_OPT(Opt_ItemDragInfo)
ASSIGN_OPT(Opt_KeyboardOptions)
ASSIGN_OPT(Opt_KeyEvent)
ASSIGN_OPT(Opt_LargestContentfulPaint)
ASSIGN_OPT(Opt_LeadingMarginPlaceholder)
ASSIGN_OPT(Opt_LengthMetrics)
ASSIGN_OPT(Opt_LetterSpacingStyle)
ASSIGN_OPT(Opt_LevelMode)
ASSIGN_OPT(Opt_LevelOrder)
ASSIGN_OPT(Opt_LinearGradient_common)
ASSIGN_OPT(Opt_LinearGradientBlurOptions)
ASSIGN_OPT(Opt_LinearGradientOptions)
ASSIGN_OPT(Opt_LinearIndicatorStartOptions)
ASSIGN_OPT(Opt_LineHeightStyle)
ASSIGN_OPT(Opt_LineMetrics)
ASSIGN_OPT(Opt_LineOptions)
ASSIGN_OPT(Opt_ListItemGroupOptions)
ASSIGN_OPT(Opt_ListItemOptions)
ASSIGN_OPT(Opt_ListOptions)
ASSIGN_OPT(Opt_Literal_Alignment_align)
ASSIGN_OPT(Opt_Literal_Boolean_next_Axis_direction)
ASSIGN_OPT(Opt_Literal_Number_angle_fingers)
ASSIGN_OPT(Opt_Literal_Number_day_month_year)
ASSIGN_OPT(Opt_Literal_Number_distance_fingers)
ASSIGN_OPT(Opt_Literal_Number_distance_fingers_PanDirection_direction)
ASSIGN_OPT(Opt_Literal_Number_duration_fingers_Boolean_repeat)
ASSIGN_OPT(Opt_Literal_Number_errcode_String_msg)
ASSIGN_OPT(Opt_Literal_Number_fingers_speed_SwipeDirection_direction)
ASSIGN_OPT(Opt_Literal_Number_index)
ASSIGN_OPT(Opt_Literal_Number_offset_span)
ASSIGN_OPT(Opt_Literal_Number_offsetRemain)
ASSIGN_OPT(Opt_Literal_Number_surfaceHeight_surfaceWidth)
ASSIGN_OPT(Opt_Literal_Object_object__String_name_Array_String_methodList)
ASSIGN_OPT(Opt_HorizontalAlignParam)
ASSIGN_OPT(Opt_VerticalAlignParam)
ASSIGN_OPT(Opt_Literal_String_baseUrl_data_encoding_historyUrl_mimeType)
ASSIGN_OPT(Opt_Literal_String_plainText)
ASSIGN_OPT(Opt_Literal_String_script_Callback_String_Void_callback_)
ASSIGN_OPT(Opt_Literal_String_target_NavigationType_type)
ASSIGN_OPT(Opt_Literal_String_value_Callback_Void_action)
ASSIGN_OPT(Opt_Literal_TransitionEffect_appear_disappear)
ASSIGN_OPT(Opt_LoadCommittedDetails)
ASSIGN_OPT(Opt_LocalizedBarrierStyle)
ASSIGN_OPT(Opt_LocalizedHorizontalAlignParam)
ASSIGN_OPT(Opt_LocalizedVerticalAlignParam)
ASSIGN_OPT(Opt_LocationButtonOptions)
ASSIGN_OPT(Opt_LongPressGestureHandlerOptions)
ASSIGN_OPT(Opt_MarqueeOptions)
ASSIGN_OPT(Opt_Matrix2D)
ASSIGN_OPT(Opt_Matrix4)
ASSIGN_OPT(Opt_Matrix4Result)
ASSIGN_OPT(Opt_Measurable)
ASSIGN_OPT(Opt_MeasureResult)
ASSIGN_OPT(Opt_MessageEvents)
ASSIGN_OPT(Opt_MonthData)
ASSIGN_OPT(Opt_MotionBlurAnchor)
ASSIGN_OPT(Opt_MotionBlurOptions)
ASSIGN_OPT(Opt_MotionPathOptions)
ASSIGN_OPT(Opt_MutableStyledString)
ASSIGN_OPT(Opt_NativeEmbedVisibilityInfo)
ASSIGN_OPT(Opt_NavContentInfo)
ASSIGN_OPT(Opt_NavDestinationCustomTitle)
ASSIGN_OPT(Opt_NavDestinationTransition)
ASSIGN_OPT(Opt_NavigationCustomTitle)
ASSIGN_OPT(Opt_NavigationInterception)
ASSIGN_OPT(Opt_NavigationOptions)
ASSIGN_OPT(Opt_NavigationTransitionProxy)
ASSIGN_OPT(Opt_NavPathInfo)
ASSIGN_OPT(Opt_NestedScrollInfo)
ASSIGN_OPT(Opt_NestedScrollOptionsExt)
ASSIGN_OPT(Opt_OffsetOptions)
ASSIGN_OPT(Opt_OnAlertEvent)
ASSIGN_OPT(Opt_OnBeforeUnloadEvent)
ASSIGN_OPT(Opt_OnClientAuthenticationEvent)
ASSIGN_OPT(Opt_OnConfirmEvent)
ASSIGN_OPT(Opt_OnContextMenuShowEvent)
ASSIGN_OPT(Opt_OnDownloadStartEvent)
ASSIGN_OPT(Opt_OnErrorReceiveEvent)
ASSIGN_OPT(Opt_OnFaviconReceivedEvent)
ASSIGN_OPT(Opt_OnGeolocationShowEvent)
ASSIGN_OPT(Opt_OnHttpAuthRequestEvent)
ASSIGN_OPT(Opt_OnHttpErrorReceiveEvent)
ASSIGN_OPT(Opt_OnInterceptRequestEvent)
ASSIGN_OPT(Opt_OnLoadInterceptEvent)
ASSIGN_OPT(Opt_OnPageBeginEvent)
ASSIGN_OPT(Opt_OnPageEndEvent)
ASSIGN_OPT(Opt_OnPageVisibleEvent)
ASSIGN_OPT(Opt_OnPermissionRequestEvent)
ASSIGN_OPT(Opt_OnPromptEvent)
ASSIGN_OPT(Opt_OnRefreshAccessedHistoryEvent)
ASSIGN_OPT(Opt_OnRenderExitedEvent)
ASSIGN_OPT(Opt_OnResourceLoadEvent)
ASSIGN_OPT(Opt_OnScreenCaptureRequestEvent)
ASSIGN_OPT(Opt_OnSslErrorEventReceiveEvent)
ASSIGN_OPT(Opt_OnTitleReceiveEvent)
ASSIGN_OPT(Opt_OnTouchIconUrlReceivedEvent)
ASSIGN_OPT(Opt_OnWindowNewEvent)
ASSIGN_OPT(Opt_Orientation)
ASSIGN_OPT(Opt_OutlineRadiuses)
ASSIGN_OPT(Opt_OverlayOffset)
ASSIGN_OPT(Opt_Padding)
ASSIGN_OPT(Opt_PanGestureHandlerOptions)
ASSIGN_OPT(Opt_PasteButtonOptions)
ASSIGN_OPT(Opt_PasteEvent)
ASSIGN_OPT(Opt_PathOptions)
ASSIGN_OPT(Opt_PathShapeOptions)
ASSIGN_OPT(Opt_PinchGestureHandlerOptions)
ASSIGN_OPT(Opt_PixelRoundPolicy)
ASSIGN_OPT(Opt_PixelStretchEffectOptions)
ASSIGN_OPT(Opt_PluginComponentTemplate)
ASSIGN_OPT(Opt_PluginErrorData)
ASSIGN_OPT(Opt_PolygonOptions)
ASSIGN_OPT(Opt_PolylineOptions)
ASSIGN_OPT(Opt_PolyToPolyOptions)
ASSIGN_OPT(Opt_PopInfo)
ASSIGN_OPT(Opt_Position)
ASSIGN_OPT(Opt_PosterOptions)
ASSIGN_OPT(Opt_PostMessageOptions)
ASSIGN_OPT(Opt_PreviewConfiguration)
ASSIGN_OPT(Opt_PreviewMenuOptions)
ASSIGN_OPT(Opt_PreviewText)
ASSIGN_OPT(Opt_ProgressOptions)
ASSIGN_OPT(Opt_ProgressStyleOptions)
ASSIGN_OPT(Opt_RadialGradientOptions)
ASSIGN_OPT(Opt_RadioOptions)
ASSIGN_OPT(Opt_RatingOptions)
ASSIGN_OPT(Opt_Rectangle)
ASSIGN_OPT(Opt_RenderingContextSettings)
ASSIGN_OPT(Opt_RenderNode)
ASSIGN_OPT(Opt_RenderProcessNotRespondingData)
ASSIGN_OPT(Opt_ReplaceSymbolEffect)
ASSIGN_OPT(Opt_Resource)
ASSIGN_OPT(Opt_ResourceColor)
ASSIGN_OPT(Opt_ResourceStr)
ASSIGN_OPT(Opt_RichEditorDeleteValue)
ASSIGN_OPT(Opt_RichEditorGesture)
ASSIGN_OPT(Opt_RichEditorInsertValue)
ASSIGN_OPT(Opt_RichEditorRange)
ASSIGN_OPT(Opt_RichEditorSelection)
ASSIGN_OPT(Opt_RichEditorSpanPosition)
ASSIGN_OPT(Opt_RingStyleOptions)
ASSIGN_OPT(Opt_RotateOption)
ASSIGN_OPT(Opt_RotateOptions)
ASSIGN_OPT(Opt_RotationGestureHandlerOptions)
ASSIGN_OPT(Opt_RoundedRectOptions)
ASSIGN_OPT(Opt_RoundRect)
ASSIGN_OPT(Opt_RoundRectShapeOptions)
ASSIGN_OPT(Opt_RouteInfo)
ASSIGN_OPT(Opt_RouteMapConfig)
ASSIGN_OPT(Opt_RowOptions)
ASSIGN_OPT(Opt_RowOptionsV2)
ASSIGN_OPT(Opt_SaveButtonOptions)
ASSIGN_OPT(Opt_ScaleOption)
ASSIGN_OPT(Opt_ScaleOptions)
ASSIGN_OPT(Opt_ScaleSymbolEffect)
ASSIGN_OPT(Opt_ScreenCaptureConfig)
ASSIGN_OPT(Opt_ScriptItem)
ASSIGN_OPT(Opt_ScrollableBarModeOptions)
ASSIGN_OPT(Opt_ScrollAnimationOptions)
ASSIGN_OPT(Opt_ScrollBarOptions)
ASSIGN_OPT(Opt_ScrollEdgeOptions)
ASSIGN_OPT(Opt_ScrollPageOptions)
ASSIGN_OPT(Opt_SelectionOptions)
ASSIGN_OPT(Opt_ShapeSize)
ASSIGN_OPT(Opt_SheetDismiss)
ASSIGN_OPT(Opt_SizeOptions)
ASSIGN_OPT(Opt_SlideRange)
ASSIGN_OPT(Opt_SliderOptions)
ASSIGN_OPT(Opt_SnapshotOptions)
ASSIGN_OPT(Opt_SpringBackAction)
ASSIGN_OPT(Opt_SslErrorEvent)
ASSIGN_OPT(Opt_StackOptions)
ASSIGN_OPT(Opt_StarStyleOptions)
ASSIGN_OPT(Opt_StateStyles)
ASSIGN_OPT(Opt_StyledStringChangedListener)
ASSIGN_OPT(Opt_Summary)
ASSIGN_OPT(Opt_SurfaceRect)
ASSIGN_OPT(Opt_SurfaceRotationOptions)
ASSIGN_OPT(Opt_SweepGradientOptions)
ASSIGN_OPT(Opt_SwipeActionItem)
ASSIGN_OPT(Opt_SwipeGestureHandlerOptions)
ASSIGN_OPT(Opt_SwiperAutoFill)
ASSIGN_OPT(Opt_SwiperContentAnimatedTransition)
ASSIGN_OPT(Opt_SystemAdaptiveOptions)
ASSIGN_OPT(Opt_SystemBarStyle)
ASSIGN_OPT(Opt_TabBarSymbol)
ASSIGN_OPT(Opt_TabContentAnimatedTransition)
ASSIGN_OPT(Opt_TapGestureParameters)
ASSIGN_OPT(Opt_TextBox)
ASSIGN_OPT(Opt_TextClockOptions)
ASSIGN_OPT(Opt_TextContentControllerOptions)
ASSIGN_OPT(Opt_TextMarqueeOptions)
ASSIGN_OPT(Opt_TextRange)
ASSIGN_OPT(Opt_TextShadowStyle)
ASSIGN_OPT(Opt_TextStyle_alert_dialog)
ASSIGN_OPT(Opt_TextTimerOptions)
ASSIGN_OPT(Opt_TimePickerOptions)
ASSIGN_OPT(Opt_TipsMessageType)
ASSIGN_OPT(Opt_TipsOptions)
ASSIGN_OPT(Opt_ToggleOptions)
ASSIGN_OPT(Opt_TouchObject)
ASSIGN_OPT(Opt_TouchResult)
ASSIGN_OPT(Opt_TransformationMatrix)
ASSIGN_OPT(Opt_TranslateOption)
ASSIGN_OPT(Opt_TranslateOptions)
ASSIGN_OPT(Opt_Tuple_ResourceColor_Number)
ASSIGN_OPT(Opt_Type_CalendarInterface_callable0_value)
ASSIGN_OPT(Opt_Type_GaugeAttribute_colors_colors)
ASSIGN_OPT(Opt_Type_PanGestureInterface_callable0_value)
ASSIGN_OPT(Opt_Union_SingleLengthDetent_DoubleLengthDetents_TripleLengthDetents)
ASSIGN_OPT(Opt_Type_SheetOptions_detents)
ASSIGN_OPT(Opt_Type_TextPickerOptions_range)
ASSIGN_OPT(Opt_Type_XComponentInterface_callable0_value)
ASSIGN_OPT(Opt_Type_XComponentInterface_callable1_value)
ASSIGN_OPT(Opt_UIExtensionOptions)
ASSIGN_OPT(Opt_Union_Array_MenuElement_CustomBuilder)
ASSIGN_OPT(Opt_Union_Array_NavigationMenuItem_CustomBuilder)
ASSIGN_OPT(Opt_Union_Array_Rectangle_Rectangle)
ASSIGN_OPT(Opt_Union_Array_ToolbarItem_CustomBuilder)
ASSIGN_OPT(Opt_Union_BadgePosition_Position)
ASSIGN_OPT(Opt_Union_BlendMode_Blender)
ASSIGN_OPT(Opt_Union_Boolean_Callback_DismissPopupAction_Void)
ASSIGN_OPT(Opt_Union_Boolean_Resource)
ASSIGN_OPT(Opt_Union_Boolean_ResourceStr_SymbolGlyphModifier)
ASSIGN_OPT(Opt_Union_BorderStyle_EdgeStyles)
ASSIGN_OPT(Opt_Union_Color_Number_String_Resource)
ASSIGN_OPT(Opt_Union_Color_String_Resource)
ASSIGN_OPT(Opt_Union_Color_String_Resource_ColoringStrategy)
ASSIGN_OPT(Opt_Union_Color_String_Resource_Number)
ASSIGN_OPT(Opt_Union_ColumnOptions_ColumnOptionsV2)
ASSIGN_OPT(Opt_Union_Context_Undefined)
ASSIGN_OPT(Opt_Union_CustomBuilder_DragItemInfo)
ASSIGN_OPT(Opt_Union_CustomBuilder_DragItemInfo_String)
ASSIGN_OPT(Opt_Union_CustomBuilder_SwipeActionItem)
ASSIGN_OPT(Opt_Union_Dimension_Array_Dimension)
ASSIGN_OPT(Opt_Union_Dimension_BorderRadiuses)
ASSIGN_OPT(Opt_Union_Dimension_EdgeOutlineWidths)
ASSIGN_OPT(Opt_Union_Dimension_EdgeWidths)
ASSIGN_OPT(Opt_Union_Dimension_LeadingMarginPlaceholder)
ASSIGN_OPT(Opt_Union_Dimension_Margin)
ASSIGN_OPT(Opt_Union_Dimension_OutlineRadiuses)
ASSIGN_OPT(Opt_Union_DragPreviewMode_Array_DragPreviewMode)
ASSIGN_OPT(Opt_Union_EdgeOutlineStyles_OutlineStyle)
ASSIGN_OPT(Opt_Union_EdgeOutlineWidths_Dimension)
ASSIGN_OPT(Opt_Union_EdgeStyles_BorderStyle)
ASSIGN_OPT(Opt_Union_ImageBitmap_PixelMap)
ASSIGN_OPT(Opt_Union_Length_BorderRadiuses)
ASSIGN_OPT(Opt_Union_Length_GridRowSizeOption)
ASSIGN_OPT(Opt_Union_LengthMetrics_BorderRadiuses)
ASSIGN_OPT(Opt_Union_LengthMetrics_LeadingMarginPlaceholder)
ASSIGN_OPT(Opt_Union_LengthMetrics_Margin)
ASSIGN_OPT(Opt_Union_LengthMetrics_Padding)
ASSIGN_OPT(Opt_Union_LengthMetrics_String)
ASSIGN_OPT(Opt_Union_Margin_Dimension)
ASSIGN_OPT(Opt_Union_MenuPreviewMode_CustomBuilder)
ASSIGN_OPT(Opt_Union_NestedScrollOptions_NestedScrollOptionsExt)
ASSIGN_OPT(Opt_Union_Number_Array_Number)
ASSIGN_OPT(Opt_Union_Number_GridColColumnOption)
ASSIGN_OPT(Opt_Union_Number_GridRowColumnOption)
ASSIGN_OPT(Opt_Union_Number_InvertOptions)
ASSIGN_OPT(Opt_Union_Number_LeadingMarginPlaceholder)
ASSIGN_OPT(Opt_Union_Number_Literal_Number_offset_span)
ASSIGN_OPT(Opt_Union_Number_Resource)
ASSIGN_OPT(Opt_Union_Number_ResourceStr)
ASSIGN_OPT(Opt_Union_Number_String_Array_Union_Number_String)
ASSIGN_OPT(Opt_Union_Number_String_Resource)
ASSIGN_OPT(Opt_Union_Number_String_SwiperAutoFill)
ASSIGN_OPT(Opt_Union_OutlineRadiuses_Dimension)
ASSIGN_OPT(Opt_Union_OutlineStyle_EdgeOutlineStyles)
ASSIGN_OPT(Opt_Union_Padding_Dimension)
ASSIGN_OPT(Opt_Union_PixelMap_ResourceStr)
ASSIGN_OPT(Opt_Union_PixelMap_ResourceStr_DrawableDescriptor)
ASSIGN_OPT(Opt_Union_PixelMap_ResourceStr_DrawableDescriptor_ASTCResource)
ASSIGN_OPT(Opt_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent)
ASSIGN_OPT(Opt_Union_Position_Alignment)
ASSIGN_OPT(Opt_Union_PX_VP_LPX_Resource)
ASSIGN_OPT(Opt_Union_RenderNode_Undefined)
ASSIGN_OPT(Opt_Union_Resource_String)
ASSIGN_OPT(Opt_Union_ResourceColor_ColorContent)
ASSIGN_OPT(Opt_Union_ResourceColor_ColoringStrategy)
ASSIGN_OPT(Opt_Union_ResourceColor_LinearGradient)
ASSIGN_OPT(Opt_Union_ResourceStr_ComponentContent)
ASSIGN_OPT(Opt_Union_ResourceStr_CustomBuilder)
ASSIGN_OPT(Opt_Union_ResourceStr_PixelMap)
ASSIGN_OPT(Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier)
ASSIGN_OPT(Opt_Union_ResourceStr_Scene)
ASSIGN_OPT(Opt_Union_ResourceStr_TabBarSymbol)
ASSIGN_OPT(Opt_Union_ResourceStr_Union_ResourceStr_ComponentContent)
ASSIGN_OPT(Opt_Union_RowOptions_RowOptionsV2)
ASSIGN_OPT(Opt_Union_ScrollAnimationOptions_Boolean)
ASSIGN_OPT(Opt_Union_SizeOptions_ImageSize)
ASSIGN_OPT(Opt_Union_String_Array_String)
ASSIGN_OPT(Opt_Union_String_CustomBuilder_ComponentContent)
ASSIGN_OPT(Opt_Union_String_Number_Buffer_Resource)
ASSIGN_OPT(Opt_Union_String_Number_Resource)
ASSIGN_OPT(Opt_Union_String_Number_Resource_Buffer)
ASSIGN_OPT(Opt_Union_String_PixelMap_Resource)
ASSIGN_OPT(Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier)
ASSIGN_OPT(Opt_Union_String_Resource)
ASSIGN_OPT(Opt_Union_String_Resource_ComponentContent)
ASSIGN_OPT(Opt_Union_String_Resource_LinearGradient_common)
ASSIGN_OPT(Opt_Union_String_Resource_PixelMap)
ASSIGN_OPT(Opt_Union_String_WebResourceRequest)
ASSIGN_OPT(Opt_Union_WebController_WebviewController)
ASSIGN_OPT(Opt_ViewportRect)
ASSIGN_OPT(Opt_VirtualScrollOptions)
ASSIGN_OPT(Opt_VisibleAreaEventOptions)
ASSIGN_OPT(Opt_VisibleListContentInfo)
ASSIGN_OPT(Opt_Want)
ASSIGN_OPT(Opt_WaterFlowOptions)
ASSIGN_OPT(Opt_WebKeyboardCallbackInfo)
ASSIGN_OPT(Opt_WebKeyboardOptions)
ASSIGN_OPT(Opt_WebMediaOptions)
ASSIGN_OPT(Opt_WebOptions)
ASSIGN_OPT(Opt_WorkerOptions)
ASSIGN_OPT(Opt_WrappedBuilder)
ASSIGN_OPT(Opt_ActionSheetButtonOptions)
ASSIGN_OPT(Opt_ActionSheetOffset)
ASSIGN_OPT(Opt_AlertDialogButtonBaseOptions)
ASSIGN_OPT(Opt_AlertDialogButtonOptions)
ASSIGN_OPT(Opt_AlignRuleOption)
ASSIGN_OPT(Opt_AnimateParam)
ASSIGN_OPT(Opt_Area)
ASSIGN_OPT(Opt_ArrowStyle)
ASSIGN_OPT(Opt_BackgroundBlurStyleOptions)
ASSIGN_OPT(Opt_BackgroundEffectOptions)
ASSIGN_OPT(Opt_BadgeStyle)
ASSIGN_OPT(Opt_ButtonIconOptions)
ASSIGN_OPT(Opt_CalendarOptions)
ASSIGN_OPT(Opt_CanvasRenderer)
ASSIGN_OPT(Opt_CanvasRenderingContext2D)
ASSIGN_OPT(Opt_CaretStyle)
ASSIGN_OPT(Opt_CircleStyleOptions)
ASSIGN_OPT(Opt_ColorStop)
ASSIGN_OPT(Opt_ComponentInfo)
ASSIGN_OPT(Opt_ContentCoverOptions)
ASSIGN_OPT(Opt_ContextMenuAnimationOptions)
ASSIGN_OPT(Opt_CurrentDayStyle)
ASSIGN_OPT(Opt_CustomColors)
ASSIGN_OPT(Opt_DataPanelShadowOptions)
ASSIGN_OPT(Opt_DecorationStyle)
ASSIGN_OPT(Opt_DecorationStyleInterface)
ASSIGN_OPT(Opt_DecorationStyleResult)
ASSIGN_OPT(Opt_DividerOptions)
ASSIGN_OPT(Opt_DividerStyle)
ASSIGN_OPT(Opt_DividerStyleOptions)
ASSIGN_OPT(Opt_DotIndicator)
ASSIGN_OPT(Opt_DragPreviewOptions)
ASSIGN_OPT(Opt_EdgeColors)
ASSIGN_OPT(Opt_EventTarget)
ASSIGN_OPT(Opt_ExpandedMenuItemOptions)
ASSIGN_OPT(Opt_FadingEdgeOptions)
ASSIGN_OPT(Opt_FlexSpaceOptions)
ASSIGN_OPT(Opt_FocusAxisEvent)
ASSIGN_OPT(Opt_FocusBoxStyle)
ASSIGN_OPT(Opt_Font)
ASSIGN_OPT(Opt_FontOptions)
ASSIGN_OPT(Opt_ForegroundBlurStyleOptions)
ASSIGN_OPT(Opt_FormInfo)
ASSIGN_OPT(Opt_GaugeIndicatorOptions)
ASSIGN_OPT(Opt_GaugeShadowOptions)
ASSIGN_OPT(Opt_GestureEvent)
ASSIGN_OPT(Opt_GridColOptions)
ASSIGN_OPT(Opt_GutterOption)
ASSIGN_OPT(Opt_HistoricalPoint)
ASSIGN_OPT(Opt_HoverEvent)
ASSIGN_OPT(Opt_IconOptions)
ASSIGN_OPT(Opt_ImageAttachmentLayoutStyle)
ASSIGN_OPT(Opt_ImageFrameInfo)
ASSIGN_OPT(Opt_IndicatorStyle)
ASSIGN_OPT(Opt_SubTabBarIndicatorStyle)
ASSIGN_OPT(Opt_JavaScriptProxy)
ASSIGN_OPT(Opt_LightSource)
ASSIGN_OPT(Opt_LinearIndicatorStyle)
ASSIGN_OPT(Opt_LinearStyleOptions)
ASSIGN_OPT(Opt_ListDividerOptions)
ASSIGN_OPT(Opt_Literal__want)
ASSIGN_OPT(Opt_Literal_Number_code__want)
ASSIGN_OPT(Opt_Literal_ResourceColor_color)
ASSIGN_OPT(Opt_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs)
ASSIGN_OPT(Opt_Literal_Union_String_Resource_url_Array_Header_headers)
ASSIGN_OPT(Opt_Literal_Union_String_WebResourceRequest_data)
ASSIGN_OPT(Opt_LocalizedAlignRuleOptions)
ASSIGN_OPT(Opt_LocalizedBorderRadiuses)
ASSIGN_OPT(Opt_LocalizedEdgeColors)
ASSIGN_OPT(Opt_LocalizedEdges)
ASSIGN_OPT(Opt_LocalizedEdgeWidths)
ASSIGN_OPT(Opt_LocalizedPadding)
ASSIGN_OPT(Opt_LocalizedPosition)
ASSIGN_OPT(Opt_LongPressGestureEvent)
ASSIGN_OPT(Opt_LunarSwitchStyle)
ASSIGN_OPT(Opt_MarkStyle)
ASSIGN_OPT(Opt_MeasureOptions)
ASSIGN_OPT(Opt_MenuElement)
ASSIGN_OPT(Opt_MenuItemConfiguration)
ASSIGN_OPT(Opt_MenuItemGroupOptions)
ASSIGN_OPT(Opt_MenuItemOptions)
ASSIGN_OPT(Opt_MouseEvent)
ASSIGN_OPT(Opt_NativeEmbedInfo)
ASSIGN_OPT(Opt_NativeXComponentParameters)
ASSIGN_OPT(Opt_NavDestinationCommonTitle)
ASSIGN_OPT(Opt_NavDestinationContext)
ASSIGN_OPT(Opt_NavigationCommonTitle)
ASSIGN_OPT(Opt_NavigationMenuItem)
ASSIGN_OPT(Opt_NonCurrentDayStyle)
ASSIGN_OPT(Opt_OffscreenCanvasRenderingContext2D)
ASSIGN_OPT(Opt_OverlayOptions)
ASSIGN_OPT(Opt_PanGestureEvent)
ASSIGN_OPT(Opt_ParagraphStyle)
ASSIGN_OPT(Opt_ParagraphStyleInterface)
ASSIGN_OPT(Opt_PasswordIcon)
ASSIGN_OPT(Opt_PickerDialogButtonStyle)
ASSIGN_OPT(Opt_PinchGestureEvent)
ASSIGN_OPT(Opt_PluginComponentOptions)
ASSIGN_OPT(Opt_RadioStyle)
ASSIGN_OPT(Opt_RectOptions)
ASSIGN_OPT(Opt_RectShapeOptions)
ASSIGN_OPT(Opt_RefreshOptions)
ASSIGN_OPT(Opt_ResizableOptions)
ASSIGN_OPT(Opt_RestrictedWorker)
ASSIGN_OPT(Opt_ReuseOptions)
ASSIGN_OPT(Opt_RichEditorBuilderSpanOptions)
ASSIGN_OPT(Opt_RichEditorChangeValue)
ASSIGN_OPT(Opt_RichEditorLayoutStyle)
ASSIGN_OPT(Opt_RichEditorParagraphStyle)
ASSIGN_OPT(Opt_RichEditorParagraphStyleOptions)
ASSIGN_OPT(Opt_RichEditorSymbolSpanStyle)
ASSIGN_OPT(Opt_RichEditorUpdateSymbolSpanStyleOptions)
ASSIGN_OPT(Opt_RichEditorUrlStyle)
ASSIGN_OPT(Opt_RotationGestureEvent)
ASSIGN_OPT(Opt_SceneOptions)
ASSIGN_OPT(Opt_ScrollOptions)
ASSIGN_OPT(Opt_ScrollSnapOptions)
ASSIGN_OPT(Opt_ScrollToIndexOptions)
ASSIGN_OPT(Opt_SearchButtonOptions)
ASSIGN_OPT(Opt_SearchOptions)
ASSIGN_OPT(Opt_SectionOptions)
ASSIGN_OPT(Opt_SelectionMenuOptions)
ASSIGN_OPT(Opt_SelectionMenuOptionsExt)
ASSIGN_OPT(Opt_SelectOption)
ASSIGN_OPT(Opt_ShadowOptions)
ASSIGN_OPT(Opt_sharedTransitionOptions)
ASSIGN_OPT(Opt_SheetInfo)
ASSIGN_OPT(Opt_SheetTitleOptions)
ASSIGN_OPT(Opt_SliderBlockStyle)
ASSIGN_OPT(Opt_StyledStringChangeValue)
ASSIGN_OPT(Opt_SwipeActionOptions)
ASSIGN_OPT(Opt_SwipeGestureEvent)
ASSIGN_OPT(Opt_SwitchStyle)
ASSIGN_OPT(Opt_TabBarIconStyle)
ASSIGN_OPT(Opt_TabBarOptions)
ASSIGN_OPT(Opt_TabsOptions)
ASSIGN_OPT(Opt_TapGestureEvent)
ASSIGN_OPT(Opt_TerminationInfo)
ASSIGN_OPT(Opt_TextAreaOptions)
ASSIGN_OPT(Opt_TextBackgroundStyle)
ASSIGN_OPT(Opt_TextCascadePickerRangeContent)
ASSIGN_OPT(Opt_TextChangeOptions)
ASSIGN_OPT(Opt_TextDecorationOptions)
ASSIGN_OPT(Opt_TextInputOptions)
ASSIGN_OPT(Opt_TextMenuItem)
ASSIGN_OPT(Opt_TextPickerOptions)
ASSIGN_OPT(Opt_TextPickerRangeContent)
ASSIGN_OPT(Opt_TextPickerResult)
ASSIGN_OPT(Opt_TextStyle_styled_string)
ASSIGN_OPT(Opt_TextStyleInterface)
ASSIGN_OPT(Opt_TodayStyle)
ASSIGN_OPT(Opt_ToolbarItem)
ASSIGN_OPT(Opt_TouchEvent)
ASSIGN_OPT(Opt_TransitionEffects)
ASSIGN_OPT(Opt_TransitionOptions)
ASSIGN_OPT(Opt_Tuple_Union_ResourceColor_LinearGradient_Number)
ASSIGN_OPT(Opt_Type_NavDestinationAttribute_title_value)
ASSIGN_OPT(Opt_Type_NavigationAttribute_title_value)
ASSIGN_OPT(Opt_UnderlineColor)
ASSIGN_OPT(Opt_Union_ArrowStyle_Boolean)
ASSIGN_OPT(Opt_Union_Boolean_Literal_ResourceColor_color)
ASSIGN_OPT(Opt_Union_Boolean_PopupMaskType)
ASSIGN_OPT(Opt_Union_BorderRadiuses_Length_LocalizedBorderRadiuses)
ASSIGN_OPT(Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext)
ASSIGN_OPT(Opt_Union_Dimension_BorderRadiuses_LocalizedBorderRadiuses)
ASSIGN_OPT(Opt_Union_Dimension_EdgeWidths_LocalizedEdgeWidths)
ASSIGN_OPT(Opt_Union_EdgeColors_ResourceColor_LocalizedEdgeColors)
ASSIGN_OPT(Opt_Union_EdgeWidths_Length_LocalizedEdgeWidths)
ASSIGN_OPT(Opt_Union_EdgeWidths_LengthMetrics_LocalizedEdgeWidths)
ASSIGN_OPT(Opt_Union_IconOptions_SymbolGlyphModifier)
ASSIGN_OPT(Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses)
ASSIGN_OPT(Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths)
ASSIGN_OPT(Opt_Union_Length_GutterOption)
ASSIGN_OPT(Opt_Union_LengthMetrics_BorderRadiuses_LocalizedBorderRadiuses)
ASSIGN_OPT(Opt_Union_Margin_Length_LocalizedMargin)
ASSIGN_OPT(Opt_Union_MenuItemOptions_CustomBuilder)
ASSIGN_OPT(Opt_Union_NavDestinationContext_NavBar)
ASSIGN_OPT(Opt_Union_Padding_Dimension_LocalizedPadding)
ASSIGN_OPT(Opt_Union_Padding_Length_LocalizedPadding)
ASSIGN_OPT(Opt_Union_Padding_LengthMetrics_LocalizedPadding)
ASSIGN_OPT(Opt_Union_Position_Edges_LocalizedEdges)
ASSIGN_OPT(Opt_Union_Position_LocalizedPosition)
ASSIGN_OPT(Opt_Union_RectOptions_RoundedRectOptions)
ASSIGN_OPT(Opt_Union_RectShapeOptions_RoundRectShapeOptions)
ASSIGN_OPT(Opt_Union_ResourceColor_EdgeColors)
ASSIGN_OPT(Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors)
ASSIGN_OPT(Opt_Union_ResourceColor_UnderlineColor)
ASSIGN_OPT(Opt_Union_ShadowOptions_Array_ShadowOptions)
ASSIGN_OPT(Opt_Union_ShadowOptions_ShadowStyle)
ASSIGN_OPT(Opt_Union_SheetTitleOptions_CustomBuilder)
ASSIGN_OPT(Opt_Union_String_Resource_CustomBuilder_TabBarOptions)
ASSIGN_OPT(Opt_Union_TransitionOptions_TransitionEffect)
ASSIGN_OPT(Opt_Union_Union_Padding_Dimension_LocalizedPadding)
ASSIGN_OPT(Opt_VideoOptions)
ASSIGN_OPT(Opt_WeekStyle)
ASSIGN_OPT(Opt_WorkStateStyle)
ASSIGN_OPT(Opt_XComponentOptions)
ASSIGN_OPT(Opt_AccessibilityHoverEvent)
ASSIGN_OPT(Opt_ActionSheetOptions)
ASSIGN_OPT(Opt_AlertDialogParamWithButtons)
ASSIGN_OPT(Opt_AlertDialogParamWithConfirm)
ASSIGN_OPT(Opt_AlertDialogParamWithOptions)
ASSIGN_OPT(Opt_AxisEvent)
ASSIGN_OPT(Opt_BackgroundColorStyle)
ASSIGN_OPT(Opt_BadgeParamWithNumber)
ASSIGN_OPT(Opt_BadgeParamWithString)
ASSIGN_OPT(Opt_BaseEvent)
ASSIGN_OPT(Opt_BaseGestureEvent)
ASSIGN_OPT(Opt_BorderImageOption)
ASSIGN_OPT(Opt_BorderOptions)
ASSIGN_OPT(Opt_BorderRadiusType)
ASSIGN_OPT(Opt_ButtonStyle)
ASSIGN_OPT(Opt_CalendarDialogOptions)
ASSIGN_OPT(Opt_CancelButtonOptions)
ASSIGN_OPT(Opt_CapsuleStyleOptions)
ASSIGN_OPT(Opt_ClickEvent)
ASSIGN_OPT(Opt_CustomDialogControllerOptions)
ASSIGN_OPT(Opt_CustomPopupOptions)
ASSIGN_OPT(Opt_CustomTheme)
ASSIGN_OPT(Opt_DigitIndicator)
ASSIGN_OPT(Opt_EditableTextChangeValue)
ASSIGN_OPT(Opt_FlexOptions)
ASSIGN_OPT(Opt_GridRowOptions)
ASSIGN_OPT(Opt_ImageAttachment)
ASSIGN_OPT(Opt_ImageAttachmentInterface)
ASSIGN_OPT(Opt_LabelStyle)
ASSIGN_OPT(Opt_TabBarLabelStyle)
ASSIGN_OPT(Opt_MenuOutlineOptions)
ASSIGN_OPT(Opt_MoreButtonOptions)
ASSIGN_OPT(Opt_NativeEmbedDataInfo)
ASSIGN_OPT(Opt_NativeEmbedTouchInfo)
ASSIGN_OPT(Opt_NavigationTitleOptions)
ASSIGN_OPT(Opt_OutlineOptions)
ASSIGN_OPT(Opt_PickerTextStyle)
ASSIGN_OPT(Opt_PlaceholderStyle)
ASSIGN_OPT(Opt_PointLightStyle)
ASSIGN_OPT(Opt_PopupMessageOptions)
ASSIGN_OPT(Opt_ResourceImageAttachmentOptions)
ASSIGN_OPT(Opt_RichEditorImageSpanStyle)
ASSIGN_OPT(Opt_RichEditorImageSpanStyleResult)
ASSIGN_OPT(Opt_RichEditorParagraphResult)
ASSIGN_OPT(Opt_RichEditorSymbolSpanOptions)
ASSIGN_OPT(Opt_RichEditorTextStyle)
ASSIGN_OPT(Opt_RichEditorTextStyleResult)
ASSIGN_OPT(Opt_RichEditorUpdateImageSpanStyleOptions)
ASSIGN_OPT(Opt_RichEditorUpdateTextSpanStyleOptions)
ASSIGN_OPT(Opt_SheetOptions)
ASSIGN_OPT(Opt_StyledStringValue)
ASSIGN_OPT(Opt_StyleOptions)
ASSIGN_OPT(Opt_TextDataDetectorConfig)
ASSIGN_OPT(Opt_TextPickerTextStyle)
ASSIGN_OPT(Opt_Type_AlertDialog_show_value)
ASSIGN_OPT(Opt_Type_RichEditorController_updateSpanStyle_value)
ASSIGN_OPT(Opt_Type_SwiperAttribute_indicator_indicator)
ASSIGN_OPT(Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions)
ASSIGN_OPT(Opt_Union_DotIndicator_DigitIndicator)
ASSIGN_OPT(Opt_Union_DotIndicator_DigitIndicator_Boolean)
ASSIGN_OPT(Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions)
ASSIGN_OPT(Opt_Union_String_ImageAttachment_CustomSpan)
ASSIGN_OPT(Opt_AttachmentType)
ASSIGN_OPT(Opt_BottomTabBarStyle)
ASSIGN_OPT(Opt_ContextMenuOptions)
ASSIGN_OPT(Opt_DatePickerDialogOptions)
ASSIGN_OPT(Opt_MenuOptions)
ASSIGN_OPT(Opt_NavigationMenuOptions)
ASSIGN_OPT(Opt_NavigationToolbarOptions)
ASSIGN_OPT(Opt_RichEditorImageSpanOptions)
ASSIGN_OPT(Opt_RichEditorImageSpanResult)
ASSIGN_OPT(Opt_RichEditorTextSpanOptions)
ASSIGN_OPT(Opt_RichEditorTextSpanResult)
ASSIGN_OPT(Opt_SpanStyle)
ASSIGN_OPT(Opt_SubTabBarStyle)
ASSIGN_OPT(Opt_TextPickerDialogOptions)
ASSIGN_OPT(Opt_TimePickerDialogOptions)
ASSIGN_OPT(Opt_Type_TabContentAttribute_tabBar_content)
ASSIGN_OPT(Opt_Union_PopupOptions_CustomPopupOptions)
ASSIGN_OPT(Opt_Union_RichEditorImageSpanResult_RichEditorTextSpanResult)
ASSIGN_OPT(Opt_Union_RichEditorTextSpanResult_RichEditorImageSpanResult)
ASSIGN_OPT(Opt_Union_SubTabBarStyle_BottomTabBarStyle)
ASSIGN_OPT(Opt_WithThemeOptions)
ASSIGN_OPT(Opt_RichEditorSpan)
ASSIGN_OPT(Opt_PopupButton)
ASSIGN_OPT(Opt_PopupOptions)
#undef ASSIGN_OPT
}

#endif // CONVERTER_GENERATED_H
