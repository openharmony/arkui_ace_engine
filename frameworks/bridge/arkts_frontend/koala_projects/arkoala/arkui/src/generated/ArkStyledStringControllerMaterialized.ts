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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { StyledString, StyledStringInternal } from "./ArkStyledStringMaterialized"
import { MutableStyledString, MutableStyledStringInternal } from "./ArkMutableStyledStringMaterialized"
import { ImageAttachment, ImageAttachmentInternal } from "./ArkImageAttachmentMaterialized"
import { CustomSpan, CustomSpanInternal } from "./ArkCustomSpanMaterialized"
import { StyleOptions, StyledStringKey, SpanStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledStringValue, UserDataSpan, TextStyleInterface, DecorationStyleInterface, GestureStyleInterface, ParagraphStyleInterface } from "./ArkStyledStringInterfaces"
import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { SizeOptions, Length, Margin, Padding, BorderRadiuses, ResourceColor, ResourceStr, Area, Position, Dimension, PX, VP, FP, LPX, Percentage } from "./ArkUnitsInterfaces"
import { ImageSpanAlignment, ImageFit, FontStyle, TextDecorationType, TextDecorationStyle, TextAlign, TextOverflow, WordBreak, FontWeight, Color, ColoringStrategy } from "./ArkEnumsInterfaces"
import { DrawContext, ShadowOptions, ShadowType, EventTarget, SourceType, SourceTool } from "./ArkCommonInterfaces"
import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { TextStyle_styled_string, TextStyle_styled_stringInternal } from "./ArkTextStyleStyledStringMaterialized"
import { DecorationStyle, DecorationStyleInternal } from "./ArkDecorationStyleMaterialized"
import { BaselineOffsetStyle, BaselineOffsetStyleInternal } from "./ArkBaselineOffsetStyleMaterialized"
import { LetterSpacingStyle, LetterSpacingStyleInternal } from "./ArkLetterSpacingStyleMaterialized"
import { TextShadowStyle, TextShadowStyleInternal } from "./ArkTextShadowStyleMaterialized"
import { GestureStyle, GestureStyleInternal } from "./ArkGestureStyleMaterialized"
import { ParagraphStyle, ParagraphStyleInternal } from "./ArkParagraphStyleMaterialized"
import { LineHeightStyle, LineHeightStyleInternal } from "./ArkLineHeightStyleMaterialized"
import { UrlStyle, UrlStyleInternal } from "./ArkUrlStyleMaterialized"
import { BackgroundColorStyle, BackgroundColorStyleInternal } from "./ArkBackgroundColorStyleMaterialized"
import { LeadingMarginPlaceholder } from "./ArkRichEditorInterfaces"
import { TextBackgroundStyle } from "./ArkSpanInterfaces"
import { ClickEvent, ClickEventInternal } from "./ArkClickEventMaterialized"
import { BaseEvent, BaseEventInternal } from "./ArkBaseEventMaterialized"
import { GestureEvent, GestureEventInternal } from "./ArkGestureEventMaterialized"
import { FingerInfo } from "./ArkGestureInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export interface StyledStringController {
    setStyledString(styledString: StyledString): void
    getStyledString(): MutableStyledString
}
export class StyledStringControllerInternal implements MaterializedBase,StyledStringController {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_styledstringcontroller(): KPointer {
        const retval = ArkUIGeneratedNativeModule._StyledStringController_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = StyledStringControllerInternal.ctor_styledstringcontroller()
        this.peer = new Finalizable(ctorPtr, StyledStringControllerInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._StyledStringController_getFinalizer()
    }
    public setStyledString(styledString: StyledString): void {
        const styledString_casted = styledString as (StyledString)
        this?.setStyledString_serialize(styledString_casted)
        return
    }
    public getStyledString(): MutableStyledString {
        return this.getStyledString_serialize()
    }
    private setStyledString_serialize(styledString: StyledString): void {
        ArkUIGeneratedNativeModule._StyledStringController_setStyledString(this.peer!.ptr, toPeerPtr(styledString))
    }
    private getStyledString_serialize(): MutableStyledString {
        const retval = ArkUIGeneratedNativeModule._StyledStringController_getStyledString(this.peer!.ptr)
        const obj: MutableStyledString = MutableStyledStringInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): StyledStringControllerInternal {
        const obj: StyledStringControllerInternal = new StyledStringControllerInternal()
        obj.peer = new Finalizable(ptr, StyledStringControllerInternal.getFinalizer())
        return obj
    }
}
