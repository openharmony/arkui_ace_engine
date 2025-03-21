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

import { AlertDialogParamWithConfirm, AlertDialogParamWithButtons, AlertDialogParamWithOptions } from "./ArkAlertDialogInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class AlertDialog {
    public static show(value: AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions): undefined {
        const value_casted = value as (AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions)
        return AlertDialog.show_serialize(value_casted)
    }
    private static show_serialize(value: AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isAlertDialogParamWithConfirm(value, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as AlertDialogParamWithConfirm
            thisSerializer.writeAlertDialogParamWithConfirm(value_0)
        }
        else if (TypeChecker.isAlertDialogParamWithButtons(value, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as AlertDialogParamWithButtons
            thisSerializer.writeAlertDialogParamWithButtons(value_1)
        }
        else if (TypeChecker.isAlertDialogParamWithOptions(value, false, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as AlertDialogParamWithOptions
            thisSerializer.writeAlertDialogParamWithOptions(value_2)
        }
        const retval  = ArkUIGeneratedNativeModule._AlertDialog_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
