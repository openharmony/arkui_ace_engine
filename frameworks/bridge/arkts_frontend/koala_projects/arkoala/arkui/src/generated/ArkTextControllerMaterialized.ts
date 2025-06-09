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
import { LayoutManager, LayoutManagerInternal } from "./ArkLayoutManagerMaterialized"
import { ImageAttachment, ImageAttachmentInternal } from "./ArkImageAttachmentMaterialized"
import { CustomSpan, CustomSpanInternal } from "./ArkCustomSpanMaterialized"
import { StyleOptions, StyledStringKey, SpanStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledStringValue } from "./ArkStyledStringInterfaces"
import { PositionWithAffinity, LineMetrics, TextRange, TextBox, Affinity } from "./ArkTextCommonInterfaces"
import { RectWidthStyle, RectHeightStyle, LengthUnit } from "./ArkArkuiExternalInterfaces"
import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { SizeOptions, Length, Margin, Padding, BorderRadiuses } from "./ArkUnitsInterfaces"
import { ImageSpanAlignment, ImageFit } from "./ArkEnumsInterfaces"
import { DrawContext } from "./ArkCommonInterfaces"
import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class TextControllerInternal {
    public static fromPtr(ptr: KPointer): TextController {
        const obj: TextController = new TextController()
        obj.peer = new Finalizable(ptr, TextController.getFinalizer())
        return obj
    }
}
export class TextController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textcontroller(): KPointer {
        const retval = ArkUIGeneratedNativeModule._TextController_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = TextController.ctor_textcontroller()
        this.peer = new Finalizable(ctorPtr, TextController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextController_getFinalizer()
    }
    public closeSelectionMenu(): void {
        this?.closeSelectionMenu_serialize()
        return
    }
    public setStyledString(value: StyledString): void {
        const value_casted = value as (StyledString)
        this?.setStyledString_serialize(value_casted)
        return
    }
    public getLayoutManager(): LayoutManager {
        return this.getLayoutManager_serialize()
    }
    private closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._TextController_closeSelectionMenu(this.peer!.ptr)
    }
    private setStyledString_serialize(value: StyledString): void {
        ArkUIGeneratedNativeModule._TextController_setStyledString(this.peer!.ptr, toPeerPtr(value))
    }
    private getLayoutManager_serialize(): LayoutManager {
        const retval = ArkUIGeneratedNativeModule._TextController_getLayoutManager(this.peer!.ptr)
        const obj: LayoutManager = LayoutManagerInternal.fromPtr(retval)
        return obj
    }
}
