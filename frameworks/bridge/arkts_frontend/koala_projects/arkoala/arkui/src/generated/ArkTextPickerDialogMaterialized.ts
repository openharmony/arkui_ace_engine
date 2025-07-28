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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class TextPickerDialog {
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
