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

import { CalendarDialogOptions, CalendarOptions } from "./ArkCalendarPickerInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { VoidCallback, ResourceColor, Length, BorderRadiuses } from "./ArkUnitsInterfaces"
import { BlurStyle, PickerDialogButtonStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, ShadowType } from "./ArkCommonInterfaces"
import { ButtonType, ButtonStyleMode, ButtonRole } from "./ArkButtonInterfaces"
import { FontWeight, FontStyle, Color, ColoringStrategy } from "./ArkEnumsInterfaces"
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class CalendarPickerDialogInternal {
    public static fromPtr(ptr: KPointer): CalendarPickerDialog {
        const obj: CalendarPickerDialog = new CalendarPickerDialog()
        obj.peer = new Finalizable(ptr, CalendarPickerDialog.getFinalizer())
        return obj
    }
}
export class CalendarPickerDialog implements MaterializedBase {
    peer?: Finalizable | undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_calendarpickerdialog(): KPointer {
        const retval = ArkUIGeneratedNativeModule._CalendarPickerDialog_ctor()
        return retval
    }
     constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr: KPointer = CalendarPickerDialog.ctor_calendarpickerdialog()
        this.peer = new Finalizable(ctorPtr, CalendarPickerDialog.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CalendarPickerDialog_getFinalizer()
    }
    public static show(options?: CalendarDialogOptions): void {
        const options_casted = options as (CalendarDialogOptions | undefined)
        CalendarPickerDialog.show_serialize(options_casted)
        return
    }
    private static show_serialize(options?: CalendarDialogOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeCalendarDialogOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CalendarPickerDialog_show(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
