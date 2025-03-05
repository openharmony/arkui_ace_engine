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

import { TextPickerDialogOptions, TextPickerOptions, TextPickerRangeContent, TextCascadePickerRangeContent, TextPickerResult } from "./ArkTextPickerInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { PickerTextStyle, PickerDialogButtonStyle, Rectangle, BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, ShadowType } from "./ArkCommonInterfaces"
import { DialogAlignment } from "./ArkAlertDialogInterfaces"
import { Offset, ResourceColor, Font, Length, BorderRadiuses } from "./ArkUnitsInterfaces"
import { FontWeight, FontStyle, Color, ColoringStrategy } from "./ArkEnumsInterfaces"
import { ButtonType, ButtonStyleMode, ButtonRole } from "./ArkButtonInterfaces"
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class TextPickerDialogInternal {
    public static fromPtr(ptr: KPointer): TextPickerDialog {
        const obj: TextPickerDialog = new TextPickerDialog()
        obj.peer = new Finalizable(ptr, TextPickerDialog.getFinalizer())
        return obj
    }
}
export class TextPickerDialog implements MaterializedBase {
    peer?: Finalizable | undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textpickerdialog(): KPointer {
        const retval = ArkUIGeneratedNativeModule._TextPickerDialog_ctor()
        return retval
    }
     constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr: KPointer = TextPickerDialog.ctor_textpickerdialog()
        this.peer = new Finalizable(ctorPtr, TextPickerDialog.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextPickerDialog_getFinalizer()
    }
    public static show(options?: TextPickerDialogOptions): undefined {
        const options_casted = options as (TextPickerDialogOptions | undefined)
        return TextPickerDialog.show_serialize(options_casted)
    }
    private static show_serialize(options?: TextPickerDialogOptions): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeTextPickerDialogOptions(options_value)
        }
        const retval = ArkUIGeneratedNativeModule._TextPickerDialog_show(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
