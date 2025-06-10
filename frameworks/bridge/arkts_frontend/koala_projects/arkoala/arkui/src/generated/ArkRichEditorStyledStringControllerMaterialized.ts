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

import { RichEditorBaseController, RichEditorBaseControllerInternal } from "./ArkRichEditorBaseControllerMaterialized"
import { TextEditControllerEx, TextEditControllerExInternal } from "./ArkTextEditControllerExMaterialized"
import { TextBaseController, TextBaseControllerInternal } from "./ArkTextBaseControllerMaterialized"
import { SelectionOptions, MenuPolicy, ShadowOptions, ShadowType, DrawContext } from "./ArkCommonInterfaces"
import { LayoutManager, LayoutManagerInternal } from "./ArkLayoutManagerMaterialized"
import { PreviewText, StyledStringChangedListener, PositionWithAffinity, LineMetrics, TextRange, TextBox, Affinity, OnDidChangeCallback, StyledStringChangeValue } from "./ArkTextCommonInterfaces"
import { RichEditorTextStyle, RichEditorRange } from "./ArkRichEditorInterfaces"
import { StyledStringController, StyledStringControllerInternal } from "./ArkStyledStringControllerMaterialized"
import { StyledString, StyledStringInternal } from "./ArkStyledStringMaterialized"
import { MutableStyledString, MutableStyledStringInternal } from "./ArkMutableStyledStringMaterialized"
import { RectWidthStyle, RectHeightStyle, LengthUnit } from "./ArkArkuiExternalInterfaces"
import { ResourceColor, Length, ResourceStr, SizeOptions, Margin, Padding, BorderRadiuses } from "./ArkUnitsInterfaces"
import { FontStyle, FontWeight, TextDecorationType, TextDecorationStyle, Color, ColoringStrategy, ImageSpanAlignment, ImageFit } from "./ArkEnumsInterfaces"
import { DecorationStyleInterface, StyleOptions, StyledStringKey, SpanStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledStringValue } from "./ArkStyledStringInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { ImageAttachment, ImageAttachmentInternal } from "./ArkImageAttachmentMaterialized"
import { CustomSpan, CustomSpanInternal } from "./ArkCustomSpanMaterialized"
import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class RichEditorStyledStringControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorStyledStringController {
        const obj: RichEditorStyledStringController = new RichEditorStyledStringController()
        obj.peer = new Finalizable(ptr, RichEditorStyledStringController.getFinalizer())
        return obj
    }
}
export class RichEditorStyledStringController extends RichEditorBaseController implements MaterializedBase {
    static ctor_richeditorstyledstringcontroller(): KPointer {
        const retval = ArkUIGeneratedNativeModule._RichEditorStyledStringController_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = RichEditorStyledStringController.ctor_richeditorstyledstringcontroller()
        this.peer = new Finalizable(ctorPtr, RichEditorStyledStringController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RichEditorStyledStringController_getFinalizer()
    }
    public setStyledString(styledString: StyledString): void {
        const styledString_casted = styledString as (StyledString)
        this?.setStyledString_serialize(styledString_casted)
        return
    }
    public getStyledString(): MutableStyledString {
        return this.getStyledString_serialize()
    }
    public getSelection(): RichEditorRange {
        return this.getSelection_serialize()
    }
    public onContentChanged(listener: StyledStringChangedListener): void {
        const listener_casted = listener as (StyledStringChangedListener)
        this?.onContentChanged_serialize(listener_casted)
        return
    }
    private setStyledString_serialize(styledString: StyledString): void {
        ArkUIGeneratedNativeModule._RichEditorStyledStringController_setStyledString(this.peer!.ptr, toPeerPtr(styledString))
    }
    private getStyledString_serialize(): MutableStyledString {
        const retval = ArkUIGeneratedNativeModule._RichEditorStyledStringController_getStyledString(this.peer!.ptr)
        const obj: MutableStyledString = MutableStyledStringInternal.fromPtr(retval)
        return obj
    }
    private getSelection_serialize(): RichEditorRange {
        const retval = ArkUIGeneratedNativeModule._RichEditorStyledStringController_getSelection(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const returnResult: RichEditorRange = retvalDeserializer.readRichEditorRange()
        return returnResult
    }
    private onContentChanged_serialize(listener: StyledStringChangedListener): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeStyledStringChangedListener(listener)
        ArkUIGeneratedNativeModule._RichEditorStyledStringController_onContentChanged(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
