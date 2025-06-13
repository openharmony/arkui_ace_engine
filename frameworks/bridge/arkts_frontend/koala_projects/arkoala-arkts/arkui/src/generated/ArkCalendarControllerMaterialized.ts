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

import { Literal_Number_day_month_year } from "./SyntheticDeclarations"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class CalendarControllerInternal {
    public static fromPtr(ptr: KPointer): CalendarController {
        const obj : CalendarController = new CalendarController()
        obj.peer = new Finalizable(ptr, CalendarController.getFinalizer())
        return obj
    }
}
export class CalendarController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_calendarcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CalendarController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = CalendarController.ctor_calendarcontroller()
        this.peer = new Finalizable(ctorPtr, CalendarController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CalendarController_getFinalizer()
    }
    public backToToday(): undefined {
        return this.backToToday_serialize()
    }
    public goTo(value: Literal_Number_day_month_year): undefined {
        const value_casted = value as (Literal_Number_day_month_year)
        return this.goTo_serialize(value_casted)
    }
    private backToToday_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._CalendarController_backToToday(this.peer!.ptr)
        return retval
    }
    private goTo_serialize(value: Literal_Number_day_month_year): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        const value_year  = value.year
        thisSerializer.writeNumber(value_year)
        const value_month  = value.month
        thisSerializer.writeNumber(value_month)
        const value_day  = value.day
        thisSerializer.writeNumber(value_day)
        const retval  = ArkUIGeneratedNativeModule._CalendarController_goTo(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
