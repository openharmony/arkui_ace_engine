/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "arkoala_api_generated.h"
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
                   const Union_Number_Resource& src)
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
                   const Union_Color_String_Resource_ColoringStrategy& src)
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
                   const Union_Length_Ark_BorderRadiuses& src)
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
                   const Union_Length_Ark_Padding& src)
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
                   const Union_CustomObject_Ark_BorderRadiuses& src)
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
                   const Union_CustomObject_Ark_Padding& src)
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
                   const Union_String_Resource& src)
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
                   const Union_FontWeight_Number_String& src)
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
                   const Union_Length_LeadingMarginPlaceholder& src)
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
                   const Union_Number_FontWeight_String& src)
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
                   const Union_Number_String_Resource& src)
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
                   const Union_Number_LeadingMarginPlaceholder& src)
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
                   const Union_Number_String& src)
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
                   const Union_ShadowOptions_Array_ShadowOptions& src)
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
                   const Union_Length_Number& src)
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
                   const Union_Curve_ICurve& src)
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
                   const Union_Number_Ark_ResourceStr& src)
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
                   const Ark_CustomBuilder& src)
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
                   const Union_Length_GridRowSizeOption& src)
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
                   const Ark_CanvasTextBaseline& src)
{
    switch (src.selector) {
        case SELECTOR_ID_0: AssignTo(dst, src.value0); break;
        case SELECTOR_ID_1: AssignTo(dst, src.value1); break;
        case SELECTOR_ID_2: AssignTo(dst, src.value2); break;
        case SELECTOR_ID_3: AssignTo(dst, src.value3); break;
        case SELECTOR_ID_4: AssignTo(dst, src.value4); break;
        case SELECTOR_ID_5: AssignTo(dst, src.value5); break;
        default:
        {
            LOGE("Unexpected src->selector: %{public}d\n", src.selector);
            return;
        }
    }
}

template<typename T>
void AssignUnionTo(std::optional<T>& dst,
                   const Ark_CanvasTextAlign& src)
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
                   const Ark_CanvasDirection& src)
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
                   const Ark_CanvasLineJoin& src)
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
                   const Ark_CanvasLineCap& src)
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
                   const Ark_ImageSmoothingQuality& src)
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
                   const Union_String_Number_CanvasGradient_CanvasPattern& src)
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
                   const Union_SheetSize_Length& src)
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
                   const Union_String_CustomObject_Resource& src)
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
                   const Union_Ark_ResourceColor_Undefined& src)
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
                   const Union_Ark_Padding_Length_LocalizedPadding& src)
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
                   const Union_Ark_Padding_Length& src)
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
                   const Union_Number_String_Array_CustomObject& src)
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
                   const Union_TitleHeight_Length& src)
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
                   const Union_BadgePosition_Position& src)
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
                   const Union_Length_Ark_BorderRadiuses_LocalizedBorderRadiuses& src)
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
                   const Union_MenuPreviewMode_Ark_CustomBuilder& src)
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
                   const Union_Boolean_Ark_Function& src)
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
                   const Union_ShadowOptions_ShadowStyle& src)
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
                   const Union_Boolean_Literal_Ark_ResourceColor_color& src)
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
                   const Union_Color_String_Resource_Number& src)
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
                   const Union_String_WebResourceRequest& src)
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
                   const Union_ScrollAnimationOptions_Boolean& src)
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
                   const Union_WebController_CustomObject& src)
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
                   const Union_Number_String_PlaybackSpeed& src)
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
                   const Union_Number_Array_Number& src)
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
                   const Union_String_Array_String& src)
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
                   const Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent& src)
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
                   const Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute& src)
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
                   const Union_Length_Array_Length& src)
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
                   const Union_String_Number& src)
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
                   const Union_Ark_ResourceStr_Ark_CustomBuilder& src)
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
                   const Union_Ark_CustomBuilder_SwipeActionItem& src)
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
                   const Union_String_Resource_CustomObject& src)
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
                   const Union_Number_GridRowColumnOption& src)
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
                   const Union_Length_GutterOption& src)
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
                   const Union_Number_GridColColumnOption& src)
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
                   const Union_Ark_ResourceColor_LinearGradient& src)
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
                   const Union_Ark_ResourceStr_CustomObject& src)
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
                   const Union_BorderStyle_Ark_EdgeStyles& src)
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
                   const Union_Ark_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors& src)
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
                   const Union_Length_Ark_EdgeWidths_LocalizedEdgeWidths& src)
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
                   const Union_SheetTitleOptions_Ark_CustomBuilder& src)
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
                   const Union_Boolean_Resource& src)
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
                   const Union_Boolean_Number& src)
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
                   const Union_DragPreviewMode_Array_DragPreviewMode& src)
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
                   const Union_Number_Literal_Number_span_offset& src)
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
                   const Union_Curve_String_ICurve& src)
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
                   const Union_Ark_EdgeOutlineStyles_OutlineStyle& src)
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
                   const Union_Ark_OutlineRadiuses_Length& src)
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
                   const Union_Ark_EdgeColors_Ark_ResourceColor_LocalizedEdgeColors& src)
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
                   const Union_Ark_EdgeOutlineWidths_Length& src)
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
                   const Union_String_Resource_LinearGradient& src)
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
                   const Union_Ark_EdgeWidths_CustomObject_LocalizedEdgeWidths& src)
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
                   const Union_Ark_EdgeStyles_BorderStyle& src)
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
                   const Union_Ark_BorderRadiuses_Length_LocalizedBorderRadiuses& src)
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
                   const Union_Ark_EdgeWidths_Length_LocalizedEdgeWidths& src)
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
                   const Union_RichEditorTextSpanResult_RichEditorImageSpanResult& src)
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
                   const Union_String_Number_Resource_ArrayBuffer& src)
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
                   const Union_String_ImageAttachment_CustomSpan& src)
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
                   const Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions& src)
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
                   const Union_CustomObject_Ark_ResourceStr& src)
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
                   const Union_String_Ark_Undefined& src)
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
                   const Ark_CanvasFillRule& src)
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
                   const Union_ImageBitmap_CustomObject& src)
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
                   const Union_DividerStyle_Ark_Undefined& src)
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
                   const Union_NestedScrollOptions_NestedScrollOptionsExt& src)
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
                   const Union_DividerOptions_Ark_Undefined& src)
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
                   const Union_Ark_ResourceColor_UnderlineColor_Undefined& src)
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
                   const Union_Ark_ResourceStr_Undefined& src)
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
                   const Union_TextInputStyle_TextContentStyle& src)
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
                   const Union_SubTabBarStyle_BottomTabBarStyle& src)
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
                   const Union_String_Resource_Ark_CustomBuilder_Literal_Opt_Union_String_Resource_icon_text& src)
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
                   const Union_Number_String_Ark_SwiperAutoFill& src)
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
                   const Union_ArrowStyle_Boolean& src)
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
                   const Union_DotIndicator_DigitIndicator_Boolean& src)
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
                   const Union_Opt_DividerOptions_Ark_Undefined& src)
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
                   const Union_Length_OptionWidthMode& src)
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
                   const Union_CancelButtonOptions_CancelButtonSymbolOptions& src)
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
                   const Union_IconOptions_CustomObject& src)
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
                   const Union_Color_Number_String& src)
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
                   const Union_ResponseType_RichEditorResponseType& src)
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
                   const Union_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight& src)
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
                   const Union_Length_PanelHeight& src)
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
                   const Union_Array_ToolbarItem_Ark_CustomBuilder& src)
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
                   const Union_CustomObject_Ark_CustomBuilder& src)
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
                   const Union_Array_NavigationMenuItem_Ark_CustomBuilder& src)
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
                   const Union_Ark_ResourceStr_Ark_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle& src)
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
                   const Union_String_CustomObject_Resource_CustomObject& src)
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
                   const Union_Ark_ResourceStr_CustomObject_CustomObject& src)
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
                   const Union_String_Ark_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle_Resource& src)
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
                   const Union_Boolean_Ark_ResourceStr_CustomObject& src)
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
                   const Union_MenuItemOptions_Ark_CustomBuilder& src)
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
                   const Union_DividerStyleOptions_Undefined& src)
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
                   const Union_CustomObject_Ark_ResourceStr_CustomObject_ASTCResource& src)
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
                   const Union_Position_Edges_LocalizedEdges& src)
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
                   const Union_ListDividerOptions_Ark_Undefined& src)
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
                   const Union_Boolean_EditMode& src)
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
                   const Union_Number_Ark_LengthConstrain& src)
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
                   const Union_ColorFilter_CustomObject& src)
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
                   const Union_CustomObject_Ark_ResourceStr_CustomObject& src)
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
                   const Union_CustomObject_Ark_ResourceStr_CustomObject_ImageContent& src)
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
                   const Union_Color_Number_String_Resource& src)
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
                   const Union_Ark_ResourceColor_LinearGradient_Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number& src)
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
                   const Union_ColumnSplitDividerStyle_Ark_Undefined& src)
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
                   const Union_CanvasRenderingContext2D_DrawingRenderingContext& src)
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
                   const Union_SpringMotion_FrictionMotion_ScrollMotion& src)
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
                   const Union_String_FunctionKey& src)
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
                   const Union_Array_MenuElement_Ark_CustomBuilder& src)
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
                   const Union_PopupOptions_CustomPopupOptions& src)
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
                   const Union_CustomObject_CustomObject_CustomObject_CustomObject& src)
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
                   const Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask& src)
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
                   const Union_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute& src)
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
                   const Union_BlendMode_CustomObject& src)
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
                   const Union_String_Ark_CustomBuilder_CustomObject& src)
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
                   const Union_Ark_CustomBuilder_DragItemInfo_String& src)
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
                   const Union_Array_CustomObject_Ark_Undefined& src)
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
                   const Union_ClickEffect_Ark_Undefined& src)
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
                   const Union_Position_LocalizedPosition& src)
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
                   const Union_Number_InvertOptions& src)
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
                   const Union_Color_String_Resource& src)
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
                   const Union_TransitionOptions_TransitionEffect& src)
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
                   const Union_Ark_ResourceColor_ColoringStrategy& src)
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
                   const Union_Length_Ark_OutlineRadiuses& src)
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
                   const Union_Length_Ark_EdgeOutlineWidths& src)
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
                   const Union_OutlineStyle_Ark_EdgeOutlineStyles& src)
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
                   const Union_Position_Alignment& src)
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
                   const Union_SizeOptions_ImageSize& src)
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
                   const Union_Array_Rectangle_Rectangle& src)
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
                   const Union_DrawModifier_Undefined& src)
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
                     const Literal_Ark_ResourceColor_color& src)
{
    AssignTo(dst, src.color);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_String_value_Function_action& src)
{
    AssignTo(dst, src.value);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Number_span_offset& src)
{
    AssignTo(dst, src.span);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Union_String_CustomObject_Resource_shown_hidden_Opt_Union_String_CustomObject_Resource_switching& src)
{
    AssignTo(dst, src.shown);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Union_String_Resource_icon_text& src)
{
    AssignTo(dst, src.icon);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight& src)
{
    AssignTo(dst, src.width);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius& src)
{
    AssignTo(dst, src.width);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Number_year_month_day& src)
{
    AssignTo(dst, src.year);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_String_anchor_VerticalAlign_align& src)
{
    AssignTo(dst, src.anchor);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_String_anchor_HorizontalAlign_align& src)
{
    AssignTo(dst, src.anchor);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Function_callback_CustomObject_fileSelector& src)
{
    AssignTo(dst, src.callback);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_CustomObject_detail& src)
{
    AssignTo(dst, src.detail);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Function_handler_CustomObject_error& src)
{
    AssignTo(dst, src.handler);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Union_String_WebResourceRequest_data& src)
{
    AssignTo(dst, src.data);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Number_time& src)
{
    AssignTo(dst, src.time);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Number_duration& src)
{
    AssignTo(dst, src.duration);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Boolean_fullscreen& src)
{
    AssignTo(dst, src.fullscreen);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Number_errcode_String_msg& src)
{
    AssignTo(dst, src.errcode);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Number_width_height_componentWidth_componentHeight_loadingStatus_contentWidth_contentHeight_contentOffsetX_contentOffsetY& src)
{
    AssignTo(dst, src.width);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Number_surfaceWidth_surfaceHeight& src)
{
    AssignTo(dst, src.surfaceWidth);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_CustomObject_object_String_name_Array_String_methodList& src)
{
    AssignTo(dst, src.object);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Union_String_Resource_url_Opt_Array_Header_headers& src)
{
    AssignTo(dst, src.url);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_String_data_mimeType_encoding_Opt_String_baseUrl_historyUrl& src)
{
    AssignTo(dst, src.data);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_String_script_Opt_Function_callback& src)
{
    AssignTo(dst, src.script);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Boolean_next_Opt_Axis_direction& src)
{
    AssignTo(dst, src.next);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Boolean_next& src)
{
    AssignTo(dst, src.next);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Number_fingers_distance_Opt_PanDirection_direction& src)
{
    AssignTo(dst, src.fingers);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_String_id_XComponentType_type_Opt_String_libraryname_Opt_XComponentController_controller& src)
{
    AssignTo(dst, src.id);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_String_id_type_Opt_String_libraryname_Opt_XComponentController_controller& src)
{
    AssignTo(dst, src.id);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_CancelButtonStyle_style_Opt_IconOptions_icon& src)
{
    AssignTo(dst, src.style);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Number_timeZoneOffset_Opt_TextClockController_controller& src)
{
    AssignTo(dst, src.timeZoneOffset);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_BarPosition_barPosition_Opt_Number_index_Opt_TabsController_controller& src)
{
    AssignTo(dst, src.barPosition);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Number_index& src)
{
    AssignTo(dst, src.index);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Union_Number_String_x_y_width_height& src)
{
    AssignTo(dst, src.x);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_String_value_icon_Ark_ResourceStr_placeholder_Opt_SearchController_controller& src)
{
    AssignTo(dst, src.value);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Union_String_Number_width_height& src)
{
    AssignTo(dst, src.width);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_PluginComponentTemplate_template_CustomObject_data& src)
{
    AssignTo(dst, src.template_);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Union_Number_String_width_height_Opt_String_commands& src)
{
    AssignTo(dst, src.width);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_String_target_Opt_NavigationType_type& src)
{
    AssignTo(dst, src.target);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Number_width_height& src)
{
    AssignTo(dst, src.width);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Number_value_Opt_Number_min_max& src)
{
    AssignTo(dst, src.value);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Literal_Number_year_month_day_date_MonthData_currentData_preData_nextData_Opt_CalendarController_controller& src)
{
    AssignTo(dst, src.date);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_CustomObject_want& src)
{
    AssignTo(dst, src.want);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Tuple_Length_Length_center_Union_Number_String_radius_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating& src)
{
    AssignTo(dst, src.center);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Tuple_Length_Length_center_Opt_Union_Number_String_start_end_rotation_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating& src)
{
    AssignTo(dst, src.center);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Union_Number_String_angle_Opt_GradientDirection_direction_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating& src)
{
    AssignTo(dst, src.angle);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Union_Number_Literal_Number_span_offset_xs_sm_md_lg& src)
{
    AssignTo(dst, src.xs);
}

template<typename T>
void AssignLiteralTo(std::optional<T>& dst,
                     const Literal_Opt_Alignment_align& src)
{
    AssignTo(dst, src.align);
}


#define ASSIGN_OPT(name) \
template<typename T> \
void AssignOptionalTo(std::optional<T>& dst, const name& src) { \
    if (src.tag != ARK_TAG_UNDEFINED) { \
        AssignUnionTo(dst, src.value); \
    } \
} \
template<typename T> \
void WithOptional(const name& src, T call) { \
    if (src.tag != ARK_TAG_UNDEFINED) { \
        call(src.value); \
    } \
}
ASSIGN_OPT(Opt_Int32)
ASSIGN_OPT(Opt_Array_String)
ASSIGN_OPT(Opt_String)
ASSIGN_OPT(Opt_Number)
ASSIGN_OPT(Opt_Length)
ASSIGN_OPT(Opt_Resource)
ASSIGN_OPT(Opt_ColoringStrategy)
ASSIGN_OPT(Opt_Color)
ASSIGN_OPT(Opt_Position)
ASSIGN_OPT(Opt_BorderRadiuses)
ASSIGN_OPT(Opt_Padding)
ASSIGN_OPT(Opt_Tuple_Length_Length)
ASSIGN_OPT(Opt_CustomObject)
ASSIGN_OPT(Opt_Boolean)
ASSIGN_OPT(Opt_Union_Number_Resource)
ASSIGN_OPT(Opt_Union_Color_String_Resource_ColoringStrategy)
ASSIGN_OPT(Opt_ShadowType)
ASSIGN_OPT(Opt_FontWeight)
ASSIGN_OPT(Opt_Area)
ASSIGN_OPT(Opt_Union_Length_BorderRadiuses)
ASSIGN_OPT(Opt_Union_Length_Padding)
ASSIGN_OPT(Opt_LeadingMarginPlaceholder)
ASSIGN_OPT(Opt_TextDecorationStyle)
ASSIGN_OPT(Opt_ResourceColor)
ASSIGN_OPT(Opt_TextDecorationType)
ASSIGN_OPT(Opt_Union_CustomObject_BorderRadiuses)
ASSIGN_OPT(Opt_Union_CustomObject_Padding)
ASSIGN_OPT(Opt_Array_ShadowOptions)
ASSIGN_OPT(Opt_ShadowOptions)
ASSIGN_OPT(Opt_ICurve)
ASSIGN_OPT(Opt_Curve)
ASSIGN_OPT(Opt_FontStyle)
ASSIGN_OPT(Opt_Union_String_Resource)
ASSIGN_OPT(Opt_Union_FontWeight_Number_String)
ASSIGN_OPT(Opt_ResourceStr)
ASSIGN_OPT(Opt_CommonMethod)
ASSIGN_OPT(Opt_TextBaseController)
ASSIGN_OPT(Opt_Undefined)
ASSIGN_OPT(Opt_Function)
ASSIGN_OPT(Opt_GridRowSizeOption)
ASSIGN_OPT(Opt_CanvasPattern)
ASSIGN_OPT(Opt_CanvasGradient)
ASSIGN_OPT(Opt_SheetSize)
ASSIGN_OPT(Opt_SourceTool)
ASSIGN_OPT(Opt_SourceType)
ASSIGN_OPT(Opt_EventTarget)
ASSIGN_OPT(Opt_RichEditorLayoutStyle)
ASSIGN_OPT(Opt_ImageFit)
ASSIGN_OPT(Opt_ImageSpanAlignment)
ASSIGN_OPT(Opt_Tuple_Number_Number)
ASSIGN_OPT(Opt_LineBreakStrategy)
ASSIGN_OPT(Opt_WordBreak)
ASSIGN_OPT(Opt_Union_Length_LeadingMarginPlaceholder)
ASSIGN_OPT(Opt_TextAlign)
ASSIGN_OPT(Opt_SymbolRenderingStrategy)
ASSIGN_OPT(Opt_SymbolEffectStrategy)
ASSIGN_OPT(Opt_Union_Number_FontWeight_String)
ASSIGN_OPT(Opt_Array_ResourceColor)
ASSIGN_OPT(Opt_Union_Number_String_Resource)
ASSIGN_OPT(Opt_DecorationStyleResult)
ASSIGN_OPT(Opt_TextBackgroundStyle)
ASSIGN_OPT(Opt_Union_Number_LeadingMarginPlaceholder)
ASSIGN_OPT(Opt_TextOverflow)
ASSIGN_OPT(Opt_ImageAttachmentLayoutStyle)
ASSIGN_OPT(Opt_SizeOptions)
ASSIGN_OPT(Opt_RichEditorRange)
ASSIGN_OPT(Opt_Union_Number_String)
ASSIGN_OPT(Opt_Union_ShadowOptions_Array_ShadowOptions)
ASSIGN_OPT(Opt_DecorationStyleInterface)
ASSIGN_OPT(Opt_Union_Length_Number)
ASSIGN_OPT(Opt_Union_Curve_ICurve)
ASSIGN_OPT(Opt_LocalizedPadding)
ASSIGN_OPT(Opt_Font)
ASSIGN_OPT(Opt_TextHeightAdaptivePolicy)
ASSIGN_OPT(Opt_Union_Number_ResourceStr)
ASSIGN_OPT(Opt_CommonShapeMethod)
ASSIGN_OPT(Opt_TextEditControllerEx)
ASSIGN_OPT(Opt_Array_CustomObject)
ASSIGN_OPT(Opt_TitleHeight)
ASSIGN_OPT(Opt_CustomBuilder)
ASSIGN_OPT(Opt_Union_Length_GridRowSizeOption)
ASSIGN_OPT(Opt_Array_Tuple_ResourceColor_Number)
ASSIGN_OPT(Opt_GradientDirection)
ASSIGN_OPT(Opt_CanvasTextBaseline)
ASSIGN_OPT(Opt_CanvasTextAlign)
ASSIGN_OPT(Opt_CanvasDirection)
ASSIGN_OPT(Opt_CanvasLineJoin)
ASSIGN_OPT(Opt_CanvasLineCap)
ASSIGN_OPT(Opt_ImageSmoothingQuality)
ASSIGN_OPT(Opt_Union_String_Number_CanvasGradient_CanvasPattern)
ASSIGN_OPT(Opt_CanvasPath)
ASSIGN_OPT(Opt_BadgePosition)
ASSIGN_OPT(Opt_BorderStyle)
ASSIGN_OPT(Opt_Union_SheetSize_Length)
ASSIGN_OPT(Opt_TransitionEffect)
ASSIGN_OPT(Opt_LocalizedBorderRadiuses)
ASSIGN_OPT(Opt_MenuPreviewMode)
ASSIGN_OPT(Opt_ShadowStyle)
ASSIGN_OPT(Opt_Literal_ResourceColor_color)
ASSIGN_OPT(Opt_OutlineStyle)
ASSIGN_OPT(Opt_Array_TouchObject)
ASSIGN_OPT(Opt_TouchType)
ASSIGN_OPT(Opt_BaseEvent)
ASSIGN_OPT(Opt_Map_String_String)
ASSIGN_OPT(Opt_WebResourceRequest)
ASSIGN_OPT(Opt_RichEditorImageSpanStyleResult)
ASSIGN_OPT(Opt_RichEditorSpanPosition)
ASSIGN_OPT(Opt_RichEditorParagraphStyle)
ASSIGN_OPT(Opt_RichEditorSymbolSpanStyle)
ASSIGN_OPT(Opt_RichEditorTextStyleResult)
ASSIGN_OPT(Opt_BackgroundColorStyle)
ASSIGN_OPT(Opt_UserDataSpan)
ASSIGN_OPT(Opt_CustomSpan)
ASSIGN_OPT(Opt_UrlStyle)
ASSIGN_OPT(Opt_LineHeightStyle)
ASSIGN_OPT(Opt_ParagraphStyle)
ASSIGN_OPT(Opt_ImageAttachment)
ASSIGN_OPT(Opt_GestureStyle)
ASSIGN_OPT(Opt_TextShadowStyle)
ASSIGN_OPT(Opt_LetterSpacingStyle)
ASSIGN_OPT(Opt_BaselineOffsetStyle)
ASSIGN_OPT(Opt_DecorationStyle)
ASSIGN_OPT(Opt_TextStyle)
ASSIGN_OPT(Opt_RichEditorSpanStyleOptions)
ASSIGN_OPT(Opt_RichEditorImageSpanStyle)
ASSIGN_OPT(Opt_RichEditorTextStyle)
ASSIGN_OPT(Opt_ScrollAnimationOptions)
ASSIGN_OPT(Opt_RelativeIndexable)
ASSIGN_OPT(Opt_Union_String_CustomObject_Resource)
ASSIGN_OPT(Opt_ImageAnalyzerController)
ASSIGN_OPT(Opt_Array_ImageAnalyzerType)
ASSIGN_OPT(Opt_NestedScrollMode)
ASSIGN_OPT(Opt_WebController)
ASSIGN_OPT(Opt_PlaybackSpeed)
ASSIGN_OPT(Opt_Array_Number)
ASSIGN_OPT(Opt_Array_TextCascadePickerRangeContent)
ASSIGN_OPT(Opt_Array_TextPickerRangeContent)
ASSIGN_OPT(Opt_Array_Array_String)
ASSIGN_OPT(Opt_Union_ResourceColor_Undefined)
ASSIGN_OPT(Opt_TextContentControllerBase)
ASSIGN_OPT(Opt_TabBarIconStyle)
ASSIGN_OPT(Opt_VerticalAlign)
ASSIGN_OPT(Opt_LayoutMode)
ASSIGN_OPT(Opt_Union_Padding_Length_LocalizedPadding)
ASSIGN_OPT(Opt_LabelStyle)
ASSIGN_OPT(Opt_Union_Padding_Length)
ASSIGN_OPT(Opt_BoardStyle)
ASSIGN_OPT(Opt_SelectedMode)
ASSIGN_OPT(Opt_IndicatorStyle)
ASSIGN_OPT(Opt_VP)
ASSIGN_OPT(Opt_Indicator)
ASSIGN_OPT(Opt_RectAttribute)
ASSIGN_OPT(Opt_PathAttribute)
ASSIGN_OPT(Opt_EllipseAttribute)
ASSIGN_OPT(Opt_CircleAttribute)
ASSIGN_OPT(Opt_DividerOptions)
ASSIGN_OPT(Opt_CancelButtonStyle)
ASSIGN_OPT(Opt_IconOptions)
ASSIGN_OPT(Opt_Array_Length)
ASSIGN_OPT(Opt_StyledStringController)
ASSIGN_OPT(Opt_RichEditorBaseController)
ASSIGN_OPT(Opt_Union_Number_String_Array_CustomObject)
ASSIGN_OPT(Opt_Union_TitleHeight_Length)
ASSIGN_OPT(Opt_SwipeActionItem)
ASSIGN_OPT(Opt_BreakpointsReference)
ASSIGN_OPT(Opt_GridRowColumnOption)
ASSIGN_OPT(Opt_GutterOption)
ASSIGN_OPT(Opt_GridColColumnOption)
ASSIGN_OPT(Opt_LinearGradient)
ASSIGN_OPT(Opt_CanvasRenderer)
ASSIGN_OPT(Opt_Array_CalendarDay)
ASSIGN_OPT(Opt_BadgeStyle)
ASSIGN_OPT(Opt_Union_BadgePosition_Position)
ASSIGN_OPT(Opt_EdgeStyles)
ASSIGN_OPT(Opt_LocalizedEdgeColors)
ASSIGN_OPT(Opt_EdgeColors)
ASSIGN_OPT(Opt_LocalizedEdgeWidths)
ASSIGN_OPT(Opt_EdgeWidths)
ASSIGN_OPT(Opt_SheetTitleOptions)
ASSIGN_OPT(Opt_BlurStyle)
ASSIGN_OPT(Opt_ContextMenuAnimationOptions)
ASSIGN_OPT(Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses)
ASSIGN_OPT(Opt_Union_MenuPreviewMode_CustomBuilder)
ASSIGN_OPT(Opt_Placement)
ASSIGN_OPT(Opt_Union_Boolean_Function)
ASSIGN_OPT(Opt_Union_ShadowOptions_ShadowStyle)
ASSIGN_OPT(Opt_ArrowPointPosition)
ASSIGN_OPT(Opt_Union_Boolean_Literal_ResourceColor_color)
ASSIGN_OPT(Opt_Union_Color_String_Resource_Number)
ASSIGN_OPT(Opt_PopupMessageOptions)
ASSIGN_OPT(Opt_Literal_String_value_Function_action)
ASSIGN_OPT(Opt_Array_DragPreviewMode)
ASSIGN_OPT(Opt_DragPreviewMode)
ASSIGN_OPT(Opt_ClickEffectLevel)
ASSIGN_OPT(Opt_HorizontalAlign)
ASSIGN_OPT(Opt_Literal_Number_span_offset)
ASSIGN_OPT(Opt_GestureInterface)
ASSIGN_OPT(Opt_RotateOptions)
ASSIGN_OPT(Opt_ScaleOptions)
ASSIGN_OPT(Opt_TranslateOptions)
ASSIGN_OPT(Opt_TransitionType)
ASSIGN_OPT(Opt_EdgeOutlineStyles)
ASSIGN_OPT(Opt_OutlineRadiuses)
ASSIGN_OPT(Opt_EdgeOutlineWidths)
ASSIGN_OPT(Opt_BlurOptions)
ASSIGN_OPT(Opt_AdaptiveColor)
ASSIGN_OPT(Opt_ThemeColorMode)
ASSIGN_OPT(Opt_WebKeyboardController)
ASSIGN_OPT(Opt_RenderProcessNotRespondingReason)
ASSIGN_OPT(Opt_EventResult)
ASSIGN_OPT(Opt_TouchEvent)
ASSIGN_OPT(Opt_NativeEmbedInfo)
ASSIGN_OPT(Opt_NativeEmbedStatus)
ASSIGN_OPT(Opt_WebNavigationType)
ASSIGN_OPT(Opt_DataResubmissionHandler)
ASSIGN_OPT(Opt_ControllerHandler)
ASSIGN_OPT(Opt_ClientAuthenticationHandler)
ASSIGN_OPT(Opt_SslError)
ASSIGN_OPT(Opt_SslErrorHandler)
ASSIGN_OPT(Opt_WebContextMenuResult)
ASSIGN_OPT(Opt_WebContextMenuParam)
ASSIGN_OPT(Opt_ScreenCaptureHandler)
ASSIGN_OPT(Opt_PermissionRequest)
ASSIGN_OPT(Opt_HttpAuthHandler)
ASSIGN_OPT(Opt_FullScreenExitHandler)
ASSIGN_OPT(Opt_FileSelectorParam)
ASSIGN_OPT(Opt_FileSelectorResult)
ASSIGN_OPT(Opt_RenderExitReason)
ASSIGN_OPT(Opt_Union_String_WebResourceRequest)
ASSIGN_OPT(Opt_WebResourceResponse)
ASSIGN_OPT(Opt_WebResourceError)
ASSIGN_OPT(Opt_ConsoleMessage)
ASSIGN_OPT(Opt_JsResult)
ASSIGN_OPT(Opt_JsGeolocation)
ASSIGN_OPT(Opt_TextDeleteDirection)
ASSIGN_OPT(Opt_Array_RichEditorTextSpanResult)
ASSIGN_OPT(Opt_Array_RichEditorImageSpanResult)
ASSIGN_OPT(Opt_TextRange)
ASSIGN_OPT(Opt_RichEditorImageSpanResult)
ASSIGN_OPT(Opt_RichEditorTextSpanResult)
ASSIGN_OPT(Opt_Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult)
ASSIGN_OPT(Opt_RichEditorDeleteDirection)
ASSIGN_OPT(Opt_Object)
ASSIGN_OPT(Opt_NavDestinationMode)
ASSIGN_OPT(Opt_ListItemGroupArea)
ASSIGN_OPT(Opt_AppRotation)
ASSIGN_OPT(Opt_FoldStatus)
ASSIGN_OPT(Opt_Array_FingerInfo)
ASSIGN_OPT(Opt_GestureControl_GestureType)
ASSIGN_OPT(Opt_DragBehavior)
ASSIGN_OPT(Opt_KeySource)
ASSIGN_OPT(Opt_KeyType)
ASSIGN_OPT(Opt_MouseAction)
ASSIGN_OPT(Opt_MouseButton)
ASSIGN_OPT(Opt_AccessibilityHoverType)
ASSIGN_OPT(Opt_RectResult)
ASSIGN_OPT(Opt_SelectStatus)
ASSIGN_OPT(Opt_WebCaptureMode)
ASSIGN_OPT(Opt_ArrayBuffer)
ASSIGN_OPT(Opt_Array_Header)
ASSIGN_OPT(Opt_StyledStringValue)
ASSIGN_OPT(Opt_StyledStringKey)
ASSIGN_OPT(Opt_MenuPolicy)
ASSIGN_OPT(Opt_RichEditorUpdateSymbolSpanStyleOptions)
ASSIGN_OPT(Opt_RichEditorUpdateImageSpanStyleOptions)
ASSIGN_OPT(Opt_RichEditorUpdateTextSpanStyleOptions)
ASSIGN_OPT(Opt_RichEditorGesture)
ASSIGN_OPT(Opt_TextMenuItemId)
ASSIGN_OPT(Opt_LaunchMode)
ASSIGN_OPT(Opt_Axis)
ASSIGN_OPT(Opt_Union_ScrollAnimationOptions_Boolean)
ASSIGN_OPT(Opt_Uint8ClampedArray)
ASSIGN_OPT(Opt_ImageBitmap)
ASSIGN_OPT(Opt_PanDirection)
ASSIGN_OPT(Opt_LinearIndicatorStyle)
ASSIGN_OPT(Opt_DpiFollowStrategy)
ASSIGN_OPT(Opt_WaterFlowLayoutMode)
ASSIGN_OPT(Opt_WaterFlowSections)
ASSIGN_OPT(Opt_Scroller)
ASSIGN_OPT(Opt_RRect)
ASSIGN_OPT(Opt_DividerStyle)
ASSIGN_OPT(Opt_Literal_Union_String_CustomObject_Resource_shown_hidden_Opt_Union_String_CustomObject_Resource_switching)
ASSIGN_OPT(Opt_ImageAIOptions)
ASSIGN_OPT(Opt_XComponentController)
ASSIGN_OPT(Opt_XComponentType)
ASSIGN_OPT(Opt_NestedScrollOptionsExt)
ASSIGN_OPT(Opt_NestedScrollOptions)
ASSIGN_OPT(Opt_Union_WebController_CustomObject)
ASSIGN_OPT(Opt_RenderMode)
ASSIGN_OPT(Opt_VideoController)
ASSIGN_OPT(Opt_Union_Number_String_PlaybackSpeed)
ASSIGN_OPT(Opt_ToggleType)
ASSIGN_OPT(Opt_TimePickerFormat)
ASSIGN_OPT(Opt_TextTimerController)
ASSIGN_OPT(Opt_Union_Number_Array_Number)
ASSIGN_OPT(Opt_Union_String_Array_String)
ASSIGN_OPT(Opt_Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent)
ASSIGN_OPT(Opt_UnderlineColor)
ASSIGN_OPT(Opt_TextContentStyle)
ASSIGN_OPT(Opt_TextInputStyle)
ASSIGN_OPT(Opt_TextInputController)
ASSIGN_OPT(Opt_TextClockController)
ASSIGN_OPT(Opt_TextAreaController)
ASSIGN_OPT(Opt_TextController)
ASSIGN_OPT(Opt_BottomTabBarStyle)
ASSIGN_OPT(Opt_SubTabBarStyle)
ASSIGN_OPT(Opt_Literal_Opt_Union_String_Resource_icon_text)
ASSIGN_OPT(Opt_EdgeEffect)
ASSIGN_OPT(Opt_AnimationMode)
ASSIGN_OPT(Opt_LayoutStyle)
ASSIGN_OPT(Opt_TabsController)
ASSIGN_OPT(Opt_BarPosition)
ASSIGN_OPT(Opt_SwiperAutoFill)
ASSIGN_OPT(Opt_ArrowStyle)
ASSIGN_OPT(Opt_DigitIndicator)
ASSIGN_OPT(Opt_DotIndicator)
ASSIGN_OPT(Opt_Alignment)
ASSIGN_OPT(Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute)
ASSIGN_OPT(Opt_SliderBlockType)
ASSIGN_OPT(Opt_SliderStyle)
ASSIGN_OPT(Opt_OptionWidthMode)
ASSIGN_OPT(Opt_CancelButtonSymbolOptions)
ASSIGN_OPT(Opt_CancelButtonOptions)
ASSIGN_OPT(Opt_SearchController)
ASSIGN_OPT(Opt_BarState)
ASSIGN_OPT(Opt_ScrollBarDirection)
ASSIGN_OPT(Opt_Union_Length_Array_Length)
ASSIGN_OPT(Opt_ScrollSnapAlign)
ASSIGN_OPT(Opt_ButtonType)
ASSIGN_OPT(Opt_SaveDescription)
ASSIGN_OPT(Opt_SaveIconStyle)
ASSIGN_OPT(Opt_Union_String_Number)
ASSIGN_OPT(Opt_Array_TextDataDetectorType)
ASSIGN_OPT(Opt_MenuType)
ASSIGN_OPT(Opt_RichEditorResponseType)
ASSIGN_OPT(Opt_ResponseType)
ASSIGN_OPT(Opt_RichEditorStyledStringController)
ASSIGN_OPT(Opt_RichEditorController)
ASSIGN_OPT(Opt_LocalizedBarrierDirection)
ASSIGN_OPT(Opt_BarrierDirection)
ASSIGN_OPT(Opt_GuideLinePosition)
ASSIGN_OPT(Opt_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight)
ASSIGN_OPT(Opt_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius)
ASSIGN_OPT(Opt_RadioIndicatorType)
ASSIGN_OPT(Opt_PluginComponentTemplate)
ASSIGN_OPT(Opt_CircleStyleOptions)
ASSIGN_OPT(Opt_PasteDescription)
ASSIGN_OPT(Opt_PasteIconStyle)
ASSIGN_OPT(Opt_PanelHeight)
ASSIGN_OPT(Opt_NavigationType)
ASSIGN_OPT(Opt_ToolbarItemStatus)
ASSIGN_OPT(Opt_Array_ToolbarItem)
ASSIGN_OPT(Opt_Array_NavigationMenuItem)
ASSIGN_OPT(Opt_NavigationCustomTitle)
ASSIGN_OPT(Opt_NavigationCommonTitle)
ASSIGN_OPT(Opt_BarStyle)
ASSIGN_OPT(Opt_NavDestinationCustomTitle)
ASSIGN_OPT(Opt_NavDestinationCommonTitle)
ASSIGN_OPT(Opt_Union_ResourceStr_Ark_CustomBuilder)
ASSIGN_OPT(Opt_MenuItemOptions)
ASSIGN_OPT(Opt_DividerStyleOptions)
ASSIGN_OPT(Opt_ASTCResource)
ASSIGN_OPT(Opt_LocationDescription)
ASSIGN_OPT(Opt_LocationIconStyle)
ASSIGN_OPT(Opt_LocalizedEdges)
ASSIGN_OPT(Opt_Edges)
ASSIGN_OPT(Opt_ListDividerOptions)
ASSIGN_OPT(Opt_ListItemGroupStyle)
ASSIGN_OPT(Opt_SwipeEdgeEffect)
ASSIGN_OPT(Opt_Union_CustomBuilder_SwipeActionItem)
ASSIGN_OPT(Opt_EditMode)
ASSIGN_OPT(Opt_ListItemStyle)
ASSIGN_OPT(Opt_ChainEdgeEffect)
ASSIGN_OPT(Opt_LengthConstrain)
ASSIGN_OPT(Opt_ColorFilter)
ASSIGN_OPT(Opt_Union_String_Resource_CustomObject)
ASSIGN_OPT(Opt_ImageContent)
ASSIGN_OPT(Opt_GridRowDirection)
ASSIGN_OPT(Opt_BreakPoints)
ASSIGN_OPT(Opt_Union_Number_GridRowColumnOption)
ASSIGN_OPT(Opt_Union_Length_GutterOption)
ASSIGN_OPT(Opt_SizeType)
ASSIGN_OPT(Opt_Union_Number_GridColColumnOption)
ASSIGN_OPT(Opt_GridItemStyle)
ASSIGN_OPT(Opt_GridItemAlignment)
ASSIGN_OPT(Opt_MultiShadowOptions)
ASSIGN_OPT(Opt_Union_ResourceColor_LinearGradient)
ASSIGN_OPT(Opt_Array_Tuple_Union_ResourceColor_LinearGradient_Number)
ASSIGN_OPT(Opt_FormShape)
ASSIGN_OPT(Opt_FormRenderingMode)
ASSIGN_OPT(Opt_FormDimension)
ASSIGN_OPT(Opt_FlexSpaceOptions)
ASSIGN_OPT(Opt_FlexAlign)
ASSIGN_OPT(Opt_ItemAlign)
ASSIGN_OPT(Opt_FlexWrap)
ASSIGN_OPT(Opt_FlexDirection)
ASSIGN_OPT(Opt_Array_Union_ResourceColor_LinearGradient)
ASSIGN_OPT(Opt_DataPanelType)
ASSIGN_OPT(Opt_ModelType)
ASSIGN_OPT(Opt_Union_ResourceStr_CustomObject)
ASSIGN_OPT(Opt_ColumnSplitDividerStyle)
ASSIGN_OPT(Opt_IlluminatedType)
ASSIGN_OPT(Opt_LightSource)
ASSIGN_OPT(Opt_DrawingRenderingContext)
ASSIGN_OPT(Opt_CanvasRenderingContext2D)
ASSIGN_OPT(Opt_CalendarController)
ASSIGN_OPT(Opt_MonthData)
ASSIGN_OPT(Opt_Literal_Number_year_month_day)
ASSIGN_OPT(Opt_ButtonRole)
ASSIGN_OPT(Opt_ControlSize)
ASSIGN_OPT(Opt_ButtonStyleMode)
ASSIGN_OPT(Opt_BadgeParam)
ASSIGN_OPT(Opt_ScrollMotion)
ASSIGN_OPT(Opt_FrictionMotion)
ASSIGN_OPT(Opt_SpringMotion)
ASSIGN_OPT(Opt_FunctionKey)
ASSIGN_OPT(Opt_ScrollSizeMode)
ASSIGN_OPT(Opt_SheetMode)
ASSIGN_OPT(Opt_Union_BorderStyle_EdgeStyles)
ASSIGN_OPT(Opt_Union_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors)
ASSIGN_OPT(Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths)
ASSIGN_OPT(Opt_Union_SheetTitleOptions_CustomBuilder)
ASSIGN_OPT(Opt_SheetType)
ASSIGN_OPT(Opt_Union_Boolean_Resource)
ASSIGN_OPT(Opt_Tuple_Union_SheetSize_Length_Opt_Union_SheetSize_Length_Opt_Union_SheetSize_Length)
ASSIGN_OPT(Opt_BindOptions)
ASSIGN_OPT(Opt_ModalTransition)
ASSIGN_OPT(Opt_Array_MenuElement)
ASSIGN_OPT(Opt_ContextMenuOptions)
ASSIGN_OPT(Opt_CustomPopupOptions)
ASSIGN_OPT(Opt_PopupOptions)
ASSIGN_OPT(Opt_TransitionHierarchyStrategy)
ASSIGN_OPT(Opt_ProgressMask)
ASSIGN_OPT(Opt_BlendMode)
ASSIGN_OPT(Opt_OverlayOffset)
ASSIGN_OPT(Opt_Union_Boolean_Number)
ASSIGN_OPT(Opt_Union_DragPreviewMode_Array_DragPreviewMode)
ASSIGN_OPT(Opt_DragItemInfo)
ASSIGN_OPT(Opt_ClickEffect)
ASSIGN_OPT(Opt_Bias)
ASSIGN_OPT(Opt_LocalizedVerticalAlignParam)
ASSIGN_OPT(Opt_LocalizedHorizontalAlignParam)
ASSIGN_OPT(Opt_Literal_String_anchor_VerticalAlign_align)
ASSIGN_OPT(Opt_Literal_String_anchor_HorizontalAlign_align)
ASSIGN_OPT(Opt_Union_Number_Literal_Number_span_offset)
ASSIGN_OPT(Opt_LocalizedPosition)
ASSIGN_OPT(Opt_SharedTransitionEffectType)
ASSIGN_OPT(Opt_MotionPathOptions)
ASSIGN_OPT(Opt_Union_Curve_String_ICurve)
ASSIGN_OPT(Opt_InvertOptions)
ASSIGN_OPT(Opt_MotionBlurAnchor)
ASSIGN_OPT(Opt_Array_Tuple_Number_Number)
ASSIGN_OPT(Opt_GestureGroupInterface)
ASSIGN_OPT(Opt_RotationGestureInterface)
ASSIGN_OPT(Opt_SwipeGestureInterface)
ASSIGN_OPT(Opt_PinchGestureInterface)
ASSIGN_OPT(Opt_PanGestureInterface)
ASSIGN_OPT(Opt_LongPressGestureInterface)
ASSIGN_OPT(Opt_TapGestureInterface)
ASSIGN_OPT(Opt_TransitionOptions)
ASSIGN_OPT(Opt_ExpectedFrameRateRange)
ASSIGN_OPT(Opt_FinishCallbackType)
ASSIGN_OPT(Opt_PlayMode)
ASSIGN_OPT(Opt_Union_EdgeOutlineStyles_OutlineStyle)
ASSIGN_OPT(Opt_Union_OutlineRadiuses_Length)
ASSIGN_OPT(Opt_Union_EdgeColors_Ark_ResourceColor_LocalizedEdgeColors)
ASSIGN_OPT(Opt_Union_EdgeOutlineWidths_Length)
ASSIGN_OPT(Opt_Union_String_Resource_LinearGradient)
ASSIGN_OPT(Opt_RepeatMode)
ASSIGN_OPT(Opt_Union_EdgeWidths_CustomObject_LocalizedEdgeWidths)
ASSIGN_OPT(Opt_Union_EdgeStyles_BorderStyle)
ASSIGN_OPT(Opt_Union_BorderRadiuses_Length_LocalizedBorderRadiuses)
ASSIGN_OPT(Opt_Union_EdgeWidths_Length_LocalizedEdgeWidths)
ASSIGN_OPT(Opt_BlurStyleOptions)
ASSIGN_OPT(Opt_BlurType)
ASSIGN_OPT(Opt_BlurStyleActivePolicy)
ASSIGN_OPT(Opt_ImageSize)
ASSIGN_OPT(Opt_PixelRoundCalcPolicy)
ASSIGN_OPT(Opt_Rectangle)
ASSIGN_OPT(Opt_Array_Rectangle)
ASSIGN_OPT(Opt_DrawModifier)
ASSIGN_OPT(Opt_TerminationInfo)
ASSIGN_OPT(Opt_AdsBlockedDetails)
ASSIGN_OPT(Opt_WebKeyboardCallbackInfo)
ASSIGN_OPT(Opt_ViewportFit)
ASSIGN_OPT(Opt_RenderProcessNotRespondingData)
ASSIGN_OPT(Opt_NativeEmbedTouchInfo)
ASSIGN_OPT(Opt_NativeEmbedVisibilityInfo)
ASSIGN_OPT(Opt_NativeEmbedDataInfo)
ASSIGN_OPT(Opt_IntelligentTrackingPreventionDetails)
ASSIGN_OPT(Opt_LoadCommittedDetails)
ASSIGN_OPT(Opt_ThreatType)
ASSIGN_OPT(Opt_OnOverScrollEvent)
ASSIGN_OPT(Opt_OnLoadInterceptEvent)
ASSIGN_OPT(Opt_LargestContentfulPaint)
ASSIGN_OPT(Opt_FirstMeaningfulPaint)
ASSIGN_OPT(Opt_OnFirstContentfulPaintEvent)
ASSIGN_OPT(Opt_OnAudioStateChangedEvent)
ASSIGN_OPT(Opt_OnDataResubmittedEvent)
ASSIGN_OPT(Opt_OnPageVisibleEvent)
ASSIGN_OPT(Opt_OnFaviconReceivedEvent)
ASSIGN_OPT(Opt_OnTouchIconUrlReceivedEvent)
ASSIGN_OPT(Opt_OnWindowNewEvent)
ASSIGN_OPT(Opt_OnClientAuthenticationEvent)
ASSIGN_OPT(Opt_SslErrorEvent)
ASSIGN_OPT(Opt_OnSslErrorEventReceiveEvent)
ASSIGN_OPT(Opt_OnScrollEvent)
ASSIGN_OPT(Opt_OnSearchResultReceiveEvent)
ASSIGN_OPT(Opt_OnContextMenuShowEvent)
ASSIGN_OPT(Opt_OnScreenCaptureRequestEvent)
ASSIGN_OPT(Opt_OnPermissionRequestEvent)
ASSIGN_OPT(Opt_OnInterceptRequestEvent)
ASSIGN_OPT(Opt_OnHttpAuthRequestEvent)
ASSIGN_OPT(Opt_OnScaleChangeEvent)
ASSIGN_OPT(Opt_FullScreenEnterEvent)
ASSIGN_OPT(Opt_OnResourceLoadEvent)
ASSIGN_OPT(Opt_Literal_Function_callback_CustomObject_fileSelector)
ASSIGN_OPT(Opt_Literal_CustomObject_detail)
ASSIGN_OPT(Opt_OnShowFileSelectorEvent)
ASSIGN_OPT(Opt_OnRenderExitedEvent)
ASSIGN_OPT(Opt_Literal_Function_handler_CustomObject_error)
ASSIGN_OPT(Opt_Literal_Union_String_WebResourceRequest_data)
ASSIGN_OPT(Opt_OnRefreshAccessedHistoryEvent)
ASSIGN_OPT(Opt_OnDownloadStartEvent)
ASSIGN_OPT(Opt_OnHttpErrorReceiveEvent)
ASSIGN_OPT(Opt_OnErrorReceiveEvent)
ASSIGN_OPT(Opt_OnConsoleEvent)
ASSIGN_OPT(Opt_OnPromptEvent)
ASSIGN_OPT(Opt_OnConfirmEvent)
ASSIGN_OPT(Opt_OnBeforeUnloadEvent)
ASSIGN_OPT(Opt_OnAlertEvent)
ASSIGN_OPT(Opt_OnGeolocationShowEvent)
ASSIGN_OPT(Opt_OnTitleReceiveEvent)
ASSIGN_OPT(Opt_OnProgressChangeEvent)
ASSIGN_OPT(Opt_OnPageBeginEvent)
ASSIGN_OPT(Opt_OnPageEndEvent)
ASSIGN_OPT(Opt_Literal_Number_time)
ASSIGN_OPT(Opt_Literal_Number_duration)
ASSIGN_OPT(Opt_Literal_Boolean_fullscreen)
ASSIGN_OPT(Opt_TimePickerResult)
ASSIGN_OPT(Opt_TabsAnimationEvent)
ASSIGN_OPT(Opt_SwiperAnimationEvent)
ASSIGN_OPT(Opt_SliderChangeMode)
ASSIGN_OPT(Opt_DeleteValue)
ASSIGN_OPT(Opt_InsertValue)
ASSIGN_OPT(Opt_PreviewText)
ASSIGN_OPT(Opt_SaveButtonOnClickResult)
ASSIGN_OPT(Opt_CopyEvent)
ASSIGN_OPT(Opt_CutEvent)
ASSIGN_OPT(Opt_RichEditorChangeValue)
ASSIGN_OPT(Opt_SubmitEvent)
ASSIGN_OPT(Opt_PasteEvent)
ASSIGN_OPT(Opt_Union_RichEditorTextSpanResult_RichEditorImageSpanResult)
ASSIGN_OPT(Opt_RichEditorDeleteValue)
ASSIGN_OPT(Opt_RichEditorInsertValue)
ASSIGN_OPT(Opt_RichEditorSelection)
ASSIGN_OPT(Opt_RefreshStatus)
ASSIGN_OPT(Opt_Literal_Number_errcode_String_msg)
ASSIGN_OPT(Opt_PasteButtonOnClickResult)
ASSIGN_OPT(Opt_NavigationOperation)
ASSIGN_OPT(Opt_NavContentInfo)
ASSIGN_OPT(Opt_LocationButtonOnClickResult)
ASSIGN_OPT(Opt_VisibleListContentInfo)
ASSIGN_OPT(Opt_ImageLoadResult)
ASSIGN_OPT(Opt_ImageError)
ASSIGN_OPT(Opt_Literal_Number_width_height_componentWidth_componentHeight_loadingStatus_contentWidth_contentHeight_contentOffsetX_contentOffsetY)
ASSIGN_OPT(Opt_ItemDragInfo)
ASSIGN_OPT(Opt_FormCallbackInfo)
ASSIGN_OPT(Opt_HoverEventParam)
ASSIGN_OPT(Opt_OnFoldStatusChangeInfo)
ASSIGN_OPT(Opt_DatePickerResult)
ASSIGN_OPT(Opt_ScrollState)
ASSIGN_OPT(Opt_Array_GestureRecognizer)
ASSIGN_OPT(Opt_GestureRecognizer)
ASSIGN_OPT(Opt_FingerInfo)
ASSIGN_OPT(Opt_BaseGestureEvent)
ASSIGN_OPT(Opt_GestureInfo)
ASSIGN_OPT(Opt_PreDragStatus)
ASSIGN_OPT(Opt_DragEvent)
ASSIGN_OPT(Opt_KeyEvent)
ASSIGN_OPT(Opt_TouchObject)
ASSIGN_OPT(Opt_MouseEvent)
ASSIGN_OPT(Opt_AccessibilityHoverEvent)
ASSIGN_OPT(Opt_HoverEvent)
ASSIGN_OPT(Opt_ClickEvent)
ASSIGN_OPT(Opt_TouchTestInfo)
ASSIGN_OPT(Opt_Array_TouchTestInfo)
ASSIGN_OPT(Opt_CheckboxGroupResult)
ASSIGN_OPT(Opt_CalendarRequestedData)
ASSIGN_OPT(Opt_CalendarSelectedDate)
ASSIGN_OPT(Opt_LinearIndicatorStartOptions)
ASSIGN_OPT(Opt_SectionOptions)
ASSIGN_OPT(Opt_Array_SectionOptions)
ASSIGN_OPT(Opt_SurfaceRotationOptions)
ASSIGN_OPT(Opt_SurfaceRect)
ASSIGN_OPT(Opt_Literal_Number_surfaceWidth_surfaceHeight)
ASSIGN_OPT(Opt_ScreenCaptureConfig)
ASSIGN_OPT(Opt_Union_String_Number_Resource_ArrayBuffer)
ASSIGN_OPT(Opt_MessageLevel)
ASSIGN_OPT(Opt_Literal_CustomObject_object_String_name_Array_String_methodList)
ASSIGN_OPT(Opt_Header)
ASSIGN_OPT(Opt_Literal_Union_String_Resource_url_Opt_Array_Header_headers)
ASSIGN_OPT(Opt_Literal_String_data_mimeType_encoding_Opt_String_baseUrl_historyUrl)
ASSIGN_OPT(Opt_Literal_String_script_Opt_Function_callback)
ASSIGN_OPT(Opt_SeekMode)
ASSIGN_OPT(Opt_SpanStyle)
ASSIGN_OPT(Opt_StyledStringChangedListener)
ASSIGN_OPT(Opt_CustomSpanDrawInfo)
ASSIGN_OPT(Opt_CustomSpanMeasureInfo)
ASSIGN_OPT(Opt_StyleOptions)
ASSIGN_OPT(Opt_Array_StyleOptions)
ASSIGN_OPT(Opt_Union_String_ImageAttachment_CustomSpan)
ASSIGN_OPT(Opt_SelectionOptions)
ASSIGN_OPT(Opt_StyledString)
ASSIGN_OPT(Opt_RichEditorParagraphStyleOptions)
ASSIGN_OPT(Opt_Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions)
ASSIGN_OPT(Opt_RichEditorSymbolSpanOptions)
ASSIGN_OPT(Opt_RichEditorBuilderSpanOptions)
ASSIGN_OPT(Opt_RichEditorImageSpanOptions)
ASSIGN_OPT(Opt_Union_CustomObject_ResourceStr)
ASSIGN_OPT(Opt_RichEditorTextSpanOptions)
ASSIGN_OPT(Opt_TextMenuItem)
ASSIGN_OPT(Opt_Array_TextMenuItem)
ASSIGN_OPT(Opt_PatternLockChallengeResult)
ASSIGN_OPT(Opt_NavigationInterception)
ASSIGN_OPT(Opt_NavigationOptions)
ASSIGN_OPT(Opt_NavPathInfo)
ASSIGN_OPT(Opt_ScrollToIndexOptions)
ASSIGN_OPT(Opt_ScrollAlign)
ASSIGN_OPT(Opt_Literal_Boolean_next_Opt_Axis_direction)
ASSIGN_OPT(Opt_Literal_Boolean_next)
ASSIGN_OPT(Opt_ScrollEdgeOptions)
ASSIGN_OPT(Opt_Edge)
ASSIGN_OPT(Opt_ScrollOptions)
ASSIGN_OPT(Opt_Matrix2D)
ASSIGN_OPT(Opt_ImageData)
ASSIGN_OPT(Opt_Union_String_Undefined)
ASSIGN_OPT(Opt_Path2D)
ASSIGN_OPT(Opt_CanvasFillRule)
ASSIGN_OPT(Opt_Union_ImageBitmap_CustomObject)
ASSIGN_OPT(Opt_RenderingContextSettings)
ASSIGN_OPT(Opt_UIGestureEvent)
ASSIGN_OPT(Opt_Literal_Opt_Number_fingers_distance_Opt_PanDirection_direction)
ASSIGN_OPT(Opt_LinearIndicatorController)
ASSIGN_OPT(Opt_UIExtensionOptions)
ASSIGN_OPT(Opt_WaterFlowOptions)
ASSIGN_OPT(Opt_WindowAnimationTarget)
ASSIGN_OPT(Opt_Union_DividerStyle_Undefined)
ASSIGN_OPT(Opt_SideBarPosition)
ASSIGN_OPT(Opt_ButtonStyle)
ASSIGN_OPT(Opt_SideBarContainerType)
ASSIGN_OPT(Opt_XComponentOptions)
ASSIGN_OPT(Opt_Literal_String_id_XComponentType_type_Opt_String_libraryname_Opt_XComponentController_controller)
ASSIGN_OPT(Opt_Literal_String_id_type_Opt_String_libraryname_Opt_XComponentController_controller)
ASSIGN_OPT(Opt_WebKeyboardAvoidMode)
ASSIGN_OPT(Opt_ExpandedMenuItemOptions)
ASSIGN_OPT(Opt_Array_ExpandedMenuItemOptions)
ASSIGN_OPT(Opt_NativeMediaPlayerConfig)
ASSIGN_OPT(Opt_Union_NestedScrollOptions_NestedScrollOptionsExt)
ASSIGN_OPT(Opt_WebLayoutMode)
ASSIGN_OPT(Opt_Array_ScriptItem)
ASSIGN_OPT(Opt_ScriptItem)
ASSIGN_OPT(Opt_OverScrollMode)
ASSIGN_OPT(Opt_WebMediaOptions)
ASSIGN_OPT(Opt_WebDarkMode)
ASSIGN_OPT(Opt_CacheMode)
ASSIGN_OPT(Opt_JavaScriptProxy)
ASSIGN_OPT(Opt_MixedMode)
ASSIGN_OPT(Opt_WebOptions)
ASSIGN_OPT(Opt_VideoOptions)
ASSIGN_OPT(Opt_SwitchStyle)
ASSIGN_OPT(Opt_ToggleOptions)
ASSIGN_OPT(Opt_TimePickerOptions)
ASSIGN_OPT(Opt_TextTimerOptions)
ASSIGN_OPT(Opt_Union_DividerOptions_Undefined)
ASSIGN_OPT(Opt_TextCascadePickerRangeContent)
ASSIGN_OPT(Opt_TextPickerRangeContent)
ASSIGN_OPT(Opt_TextPickerOptions)
ASSIGN_OPT(Opt_Literal_Opt_CancelButtonStyle_style_Opt_IconOptions_icon)
ASSIGN_OPT(Opt_Union_ResourceColor_UnderlineColor_Undefined)
ASSIGN_OPT(Opt_Union_ResourceStr_Undefined)
ASSIGN_OPT(Opt_PasswordIcon)
ASSIGN_OPT(Opt_Union_TextInputStyle_TextContentStyle)
ASSIGN_OPT(Opt_InputType)
ASSIGN_OPT(Opt_TextInputOptions)
ASSIGN_OPT(Opt_Literal_Opt_Number_timeZoneOffset_Opt_TextClockController_controller)
ASSIGN_OPT(Opt_ContentType)
ASSIGN_OPT(Opt_TextAreaType)
ASSIGN_OPT(Opt_InputCounterOptions)
ASSIGN_OPT(Opt_TextAreaOptions)
ASSIGN_OPT(Opt_TextSelectableMode)
ASSIGN_OPT(Opt_TextResponseType)
ASSIGN_OPT(Opt_TextSpanType)
ASSIGN_OPT(Opt_EllipsisMode)
ASSIGN_OPT(Opt_TextOverflowOptions)
ASSIGN_OPT(Opt_FontSettingOptions)
ASSIGN_OPT(Opt_TextOptions)
ASSIGN_OPT(Opt_Union_SubTabBarStyle_BottomTabBarStyle)
ASSIGN_OPT(Opt_Union_String_Resource_CustomBuilder_Literal_Opt_Union_String_Resource_icon_text)
ASSIGN_OPT(Opt_BarGridColumnOptions)
ASSIGN_OPT(Opt_ScrollableBarModeOptions)
ASSIGN_OPT(Opt_BarMode)
ASSIGN_OPT(Opt_Literal_Opt_BarPosition_barPosition_Opt_Number_index_Opt_TabsController_controller)
ASSIGN_OPT(Opt_SymbolEffect)
ASSIGN_OPT(Opt_SwiperContentAnimatedTransition)
ASSIGN_OPT(Opt_SwiperNestedScrollMode)
ASSIGN_OPT(Opt_Union_Number_String_SwiperAutoFill)
ASSIGN_OPT(Opt_SwiperDisplayMode)
ASSIGN_OPT(Opt_Union_ArrowStyle_Boolean)
ASSIGN_OPT(Opt_Union_DotIndicator_DigitIndicator_Boolean)
ASSIGN_OPT(Opt_SwiperController)
ASSIGN_OPT(Opt_ItemState)
ASSIGN_OPT(Opt_Literal_Opt_Number_index)
ASSIGN_OPT(Opt_StackOptions)
ASSIGN_OPT(Opt_TextCase)
ASSIGN_OPT(Opt_SlideRange)
ASSIGN_OPT(Opt_SliderInteraction)
ASSIGN_OPT(Opt_SliderBlockStyle)
ASSIGN_OPT(Opt_SliderOptions)
ASSIGN_OPT(Opt_Literal_Opt_Union_Number_String_x_y_width_height)
ASSIGN_OPT(Opt_Union_Opt_DividerOptions_Undefined)
ASSIGN_OPT(Opt_Union_Length_OptionWidthMode)
ASSIGN_OPT(Opt_MenuAlignType)
ASSIGN_OPT(Opt_ArrowPosition)
ASSIGN_OPT(Opt_SelectOption)
ASSIGN_OPT(Opt_Array_SelectOption)
ASSIGN_OPT(Opt_SearchType)
ASSIGN_OPT(Opt_TextDecorationOptions)
ASSIGN_OPT(Opt_CaretStyle)
ASSIGN_OPT(Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions)
ASSIGN_OPT(Opt_Union_IconOptions_CustomObject)
ASSIGN_OPT(Opt_SearchButtonOptions)
ASSIGN_OPT(Opt_Literal_Opt_String_value_icon_ResourceStr_placeholder_Opt_SearchController_controller)
ASSIGN_OPT(Opt_ScrollBarOptions)
ASSIGN_OPT(Opt_OffsetOptions)
ASSIGN_OPT(Opt_ScrollSnapOptions)
ASSIGN_OPT(Opt_Union_Color_Number_String)
ASSIGN_OPT(Opt_ScrollDirection)
ASSIGN_OPT(Opt_SaveButtonOptions)
ASSIGN_OPT(Opt_RowOptions)
ASSIGN_OPT(Opt_RootSceneSession)
ASSIGN_OPT(Opt_EditMenuOptions)
ASSIGN_OPT(Opt_EnterKeyType)
ASSIGN_OPT(Opt_PlaceholderStyle)
ASSIGN_OPT(Opt_TextDataDetectorType)
ASSIGN_OPT(Opt_TextDataDetectorConfig)
ASSIGN_OPT(Opt_KeyboardOptions)
ASSIGN_OPT(Opt_SelectionMenuOptions)
ASSIGN_OPT(Opt_Union_ResponseType_RichEditorResponseType)
ASSIGN_OPT(Opt_RichEditorSpanType)
ASSIGN_OPT(Opt_RichEditorStyledStringOptions)
ASSIGN_OPT(Opt_RichEditorOptions)
ASSIGN_OPT(Opt_LocalizedBarrierStyle)
ASSIGN_OPT(Opt_Array_LocalizedBarrierStyle)
ASSIGN_OPT(Opt_BarrierStyle)
ASSIGN_OPT(Opt_Array_BarrierStyle)
ASSIGN_OPT(Opt_GuideLineStyle)
ASSIGN_OPT(Opt_Array_GuideLineStyle)
ASSIGN_OPT(Opt_RefreshOptions)
ASSIGN_OPT(Opt_Union_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight)
ASSIGN_OPT(Opt_StarStyleOptions)
ASSIGN_OPT(Opt_RatingOptions)
ASSIGN_OPT(Opt_RadioStyle)
ASSIGN_OPT(Opt_RadioOptions)
ASSIGN_OPT(Opt_Literal_Opt_Union_String_Number_width_height)
ASSIGN_OPT(Opt_Literal_PluginComponentTemplate_template_CustomObject_data)
ASSIGN_OPT(Opt_PatternLockController)
ASSIGN_OPT(Opt_Literal_Opt_Union_Number_String_width_height_Opt_String_commands)
ASSIGN_OPT(Opt_PasteButtonOptions)
ASSIGN_OPT(Opt_Union_Length_PanelHeight)
ASSIGN_OPT(Opt_PanelType)
ASSIGN_OPT(Opt_PanelMode)
ASSIGN_OPT(Opt_Literal_String_target_Opt_NavigationType_type)
ASSIGN_OPT(Opt_Array_LayoutSafeAreaEdge)
ASSIGN_OPT(Opt_Array_LayoutSafeAreaType)
ASSIGN_OPT(Opt_NavigationToolbarOptions)
ASSIGN_OPT(Opt_ToolbarItem)
ASSIGN_OPT(Opt_Union_Array_ToolbarItem_CustomBuilder)
ASSIGN_OPT(Opt_Union_CustomObject_CustomBuilder)
ASSIGN_OPT(Opt_Union_Array_NavigationMenuItem_CustomBuilder)
ASSIGN_OPT(Opt_NavigationTitleMode)
ASSIGN_OPT(Opt_Union_ResourceStr_Ark_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle)
ASSIGN_OPT(Opt_Union_String_CustomObject_Resource_CustomObject)
ASSIGN_OPT(Opt_NavigationMode)
ASSIGN_OPT(Opt_NavBarPosition)
ASSIGN_OPT(Opt_NavPathStack)
ASSIGN_OPT(Opt_NavRouteMode)
ASSIGN_OPT(Opt_RouteInfo)
ASSIGN_OPT(Opt_NavigationSystemTransitionType)
ASSIGN_OPT(Opt_LayoutSafeAreaEdge)
ASSIGN_OPT(Opt_LayoutSafeAreaType)
ASSIGN_OPT(Opt_NavigationMenuItem)
ASSIGN_OPT(Opt_Union_ResourceStr_CustomObject_CustomObject)
ASSIGN_OPT(Opt_NavigationTitleOptions)
ASSIGN_OPT(Opt_Union_String_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle_Resource)
ASSIGN_OPT(Opt_MenuItemGroupOptions)
ASSIGN_OPT(Opt_Union_Boolean_ResourceStr_CustomObject)
ASSIGN_OPT(Opt_Union_MenuItemOptions_CustomBuilder)
ASSIGN_OPT(Opt_SubMenuExpandingMode)
ASSIGN_OPT(Opt_Union_DividerStyleOptions_Undefined)
ASSIGN_OPT(Opt_Union_CustomObject_ResourceStr_CustomObject_ASTCResource)
ASSIGN_OPT(Opt_MarqueeUpdateStrategy)
ASSIGN_OPT(Opt_MarqueeOptions)
ASSIGN_OPT(Opt_LocationButtonOptions)
ASSIGN_OPT(Opt_Union_Position_Edges_LocalizedEdges)
ASSIGN_OPT(Opt_SecurityComponentLayoutDirection)
ASSIGN_OPT(Opt_Union_ListDividerOptions_Undefined)
ASSIGN_OPT(Opt_ListItemGroupOptions)
ASSIGN_OPT(Opt_SwipeActionOptions)
ASSIGN_OPT(Opt_Union_Boolean_EditMode)
ASSIGN_OPT(Opt_Sticky)
ASSIGN_OPT(Opt_ListItemOptions)
ASSIGN_OPT(Opt_ChildrenMainSize)
ASSIGN_OPT(Opt_StickyStyle)
ASSIGN_OPT(Opt_ChainAnimationOptions)
ASSIGN_OPT(Opt_ListItemAlign)
ASSIGN_OPT(Opt_Union_Number_LengthConstrain)
ASSIGN_OPT(Opt_ListOptions)
ASSIGN_OPT(Opt_Union_ColorFilter_CustomObject)
ASSIGN_OPT(Opt_ImageFrameInfo)
ASSIGN_OPT(Opt_Array_ImageFrameInfo)
ASSIGN_OPT(Opt_ImageAnalyzerConfig)
ASSIGN_OPT(Opt_CopyOptions)
ASSIGN_OPT(Opt_Literal_Number_width_height)
ASSIGN_OPT(Opt_ImageInterpolation)
ASSIGN_OPT(Opt_DynamicRangeMode)
ASSIGN_OPT(Opt_ImageRenderMode)
ASSIGN_OPT(Opt_Union_CustomObject_ResourceStr_CustomObject)
ASSIGN_OPT(Opt_Union_CustomObject_ResourceStr_CustomObject_ImageContent)
ASSIGN_OPT(Opt_Union_Color_Number_String_Resource)
ASSIGN_OPT(Opt_GridRowOptions)
ASSIGN_OPT(Opt_GridContainerOptions)
ASSIGN_OPT(Opt_GridColOptions)
ASSIGN_OPT(Opt_GridItemOptions)
ASSIGN_OPT(Opt_GridDirection)
ASSIGN_OPT(Opt_GridLayoutOptions)
ASSIGN_OPT(Opt_FadingEdgeOptions)
ASSIGN_OPT(Opt_EdgeEffectOptions)
ASSIGN_OPT(Opt_GaugeIndicatorOptions)
ASSIGN_OPT(Opt_GaugeShadowOptions)
ASSIGN_OPT(Opt_Tuple_Union_ResourceColor_LinearGradient_Number)
ASSIGN_OPT(Opt_Union_ResourceColor_LinearGradient_Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number)
ASSIGN_OPT(Opt_Literal_Number_value_Opt_Number_min_max)
ASSIGN_OPT(Opt_FormLinkOptions)
ASSIGN_OPT(Opt_FormInfo)
ASSIGN_OPT(Opt_FolderStackOptions)
ASSIGN_OPT(Opt_FlexOptions)
ASSIGN_OPT(Opt_EmbeddedType)
ASSIGN_OPT(Opt_DatePickerOptions)
ASSIGN_OPT(Opt_DataPanelShadowOptions)
ASSIGN_OPT(Opt_DataPanelOptions)
ASSIGN_OPT(Opt_SceneOptions)
ASSIGN_OPT(Opt_Union_ColumnSplitDividerStyle_Undefined)
ASSIGN_OPT(Opt_PointLightStyle)
ASSIGN_OPT(Opt_ColumnOptions)
ASSIGN_OPT(Opt_CircleOptions)
ASSIGN_OPT(Opt_LineJoinStyle)
ASSIGN_OPT(Opt_LineCapStyle)
ASSIGN_OPT(Opt_CheckboxGroupOptions)
ASSIGN_OPT(Opt_MarkStyle)
ASSIGN_OPT(Opt_CheckBoxShape)
ASSIGN_OPT(Opt_CheckboxOptions)
ASSIGN_OPT(Opt_ImageAnalyzerType)
ASSIGN_OPT(Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext)
ASSIGN_OPT(Opt_PickerTextStyle)
ASSIGN_OPT(Opt_Offset)
ASSIGN_OPT(Opt_CalendarAlign)
ASSIGN_OPT(Opt_CalendarOptions)
ASSIGN_OPT(Opt_WorkStateStyle)
ASSIGN_OPT(Opt_WeekStyle)
ASSIGN_OPT(Opt_TodayStyle)
ASSIGN_OPT(Opt_NonCurrentDayStyle)
ASSIGN_OPT(Opt_CurrentDayStyle)
ASSIGN_OPT(Opt_CalendarDay)
ASSIGN_OPT(Opt_Literal_Literal_Number_year_month_day_date_MonthData_currentData_preData_nextData_Opt_CalendarController_controller)
ASSIGN_OPT(Opt_ButtonOptions)
ASSIGN_OPT(Opt_BadgeParamWithString)
ASSIGN_OPT(Opt_BadgeParamWithNumber)
ASSIGN_OPT(Opt_Union_SpringMotion_FrictionMotion_ScrollMotion)
ASSIGN_OPT(Opt_FillMode)
ASSIGN_OPT(Opt_AnimationStatus)
ASSIGN_OPT(Opt_IndexerAlign)
ASSIGN_OPT(Opt_AlphabetIndexerOptions)
ASSIGN_OPT(Opt_Literal_CustomObject_want)
ASSIGN_OPT(Opt_BackgroundBrightnessOptions)
ASSIGN_OPT(Opt_GestureModifier)
ASSIGN_OPT(Opt_RenderFit)
ASSIGN_OPT(Opt_ObscuredReasons)
ASSIGN_OPT(Opt_Array_ObscuredReasons)
ASSIGN_OPT(Opt_ModifierKey)
ASSIGN_OPT(Opt_Array_ModifierKey)
ASSIGN_OPT(Opt_Union_String_FunctionKey)
ASSIGN_OPT(Opt_PixelStretchEffectOptions)
ASSIGN_OPT(Opt_StateStyles)
ASSIGN_OPT(Opt_SheetOptions)
ASSIGN_OPT(Opt_ContentCoverOptions)
ASSIGN_OPT(Opt_Union_Array_MenuElement_CustomBuilder)
ASSIGN_OPT(Opt_MenuOptions)
ASSIGN_OPT(Opt_MenuElement)
ASSIGN_OPT(Opt_Union_PopupOptions_CustomPopupOptions)
ASSIGN_OPT(Opt_GeometryTransitionOptions)
ASSIGN_OPT(Opt_Union_CustomObject_CustomObject_CustomObject_CustomObject)
ASSIGN_OPT(Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask)
ASSIGN_OPT(Opt_Union_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute)
ASSIGN_OPT(Opt_Union_BlendMode_CustomObject)
ASSIGN_OPT(Opt_BlendApplyType)
ASSIGN_OPT(Opt_Tuple_ResourceColor_Number)
ASSIGN_OPT(Opt_Literal_Tuple_Length_Length_center_Union_Number_String_radius_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating)
ASSIGN_OPT(Opt_Literal_Tuple_Length_Length_center_Opt_Union_Number_String_start_end_rotation_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating)
ASSIGN_OPT(Opt_Literal_Opt_Union_Number_String_angle_Opt_GradientDirection_direction_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating)
ASSIGN_OPT(Opt_OverlayOptions)
ASSIGN_OPT(Opt_Union_String_CustomBuilder_CustomObject)
ASSIGN_OPT(Opt_DragInteractionOptions)
ASSIGN_OPT(Opt_DragPreviewOptions)
ASSIGN_OPT(Opt_Union_CustomBuilder_DragItemInfo_String)
ASSIGN_OPT(Opt_Union_Array_CustomObject_Undefined)
ASSIGN_OPT(Opt_Union_ClickEffect_Undefined)
ASSIGN_OPT(Opt_ChainStyle)
ASSIGN_OPT(Opt_LocalizedAlignRuleOptions)
ASSIGN_OPT(Opt_AlignRuleOption)
ASSIGN_OPT(Opt_Literal_Opt_Union_Number_Literal_Number_span_offset_xs_sm_md_lg)
ASSIGN_OPT(Opt_Union_Position_LocalizedPosition)
ASSIGN_OPT(Opt_Direction)
ASSIGN_OPT(Opt_sharedTransitionOptions)
ASSIGN_OPT(Opt_Visibility)
ASSIGN_OPT(Opt_Union_Number_InvertOptions)
ASSIGN_OPT(Opt_Union_Color_String_Resource)
ASSIGN_OPT(Opt_MotionBlurOptions)
ASSIGN_OPT(Opt_LinearGradientBlurOptions)
ASSIGN_OPT(Opt_GestureMask)
ASSIGN_OPT(Opt_GestureType)
ASSIGN_OPT(Opt_Union_TransitionOptions_TransitionEffect)
ASSIGN_OPT(Opt_AnimateParam)
ASSIGN_OPT(Opt_FocusPriority)
ASSIGN_OPT(Opt_FocusBoxStyle)
ASSIGN_OPT(Opt_HoverEffect)
ASSIGN_OPT(Opt_Union_ResourceColor_ColoringStrategy)
ASSIGN_OPT(Opt_Union_Length_OutlineRadiuses)
ASSIGN_OPT(Opt_Union_Length_EdgeOutlineWidths)
ASSIGN_OPT(Opt_Union_OutlineStyle_EdgeOutlineStyles)
ASSIGN_OPT(Opt_OutlineOptions)
ASSIGN_OPT(Opt_BorderImageOption)
ASSIGN_OPT(Opt_BorderOptions)
ASSIGN_OPT(Opt_ForegroundBlurStyleOptions)
ASSIGN_OPT(Opt_ForegroundEffectOptions)
ASSIGN_OPT(Opt_ResizableOptions)
ASSIGN_OPT(Opt_BackgroundEffectOptions)
ASSIGN_OPT(Opt_BackgroundBlurStyleOptions)
ASSIGN_OPT(Opt_Union_Position_Alignment)
ASSIGN_OPT(Opt_Union_SizeOptions_ImageSize)
ASSIGN_OPT(Opt_ImageRepeat)
ASSIGN_OPT(Opt_PixelRoundPolicy)
ASSIGN_OPT(Opt_Literal_Opt_Alignment_align)
ASSIGN_OPT(Opt_HitTestMode)
ASSIGN_OPT(Opt_ConstraintSizeOptions)
ASSIGN_OPT(Opt_Union_Array_Rectangle_Rectangle)
ASSIGN_OPT(Opt_SafeAreaEdge)
ASSIGN_OPT(Opt_Array_SafeAreaEdge)
ASSIGN_OPT(Opt_SafeAreaType)
ASSIGN_OPT(Opt_Array_SafeAreaType)
ASSIGN_OPT(Opt_Union_DrawModifier_Undefined)
#undef ASSIGN_OPT
}

#endif // CONVERTER_GENERATED_H
