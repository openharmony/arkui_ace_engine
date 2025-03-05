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

import { DatePickerDialogOptions } from "./ArkDatePickerInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class DatePickerDialogInternal {
    public static fromPtr(ptr: KPointer): DatePickerDialog {
        const obj : DatePickerDialog = new DatePickerDialog()
        obj.peer = new Finalizable(ptr, DatePickerDialog.getFinalizer())
        return obj
    }
}
export class DatePickerDialog implements MaterializedBase {
    peer?: Finalizable | undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_datepickerdialog(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DatePickerDialog_ctor()
        return retval
    }
     constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = DatePickerDialog.ctor_datepickerdialog()
        this.peer = new Finalizable(ctorPtr, DatePickerDialog.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DatePickerDialog_getFinalizer()
    }
    public static show(options?: DatePickerDialogOptions): undefined {
        const options_casted = options as (DatePickerDialogOptions | undefined)
        return DatePickerDialog.show_serialize(options_casted)
    }
    private static show_serialize(options?: DatePickerDialogOptions): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeDatePickerDialogOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._DatePickerDialog_show(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
