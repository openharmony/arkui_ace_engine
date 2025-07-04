/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { ArkUIGeneratedNativeModule } from "#components"
import { runtimeType, RuntimeType, KPointer } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { StepperOptions, Bindable } from "../component"
import { Serializer } from "../component/peers/Serializer"
import { StepperOpsHandWritten } from "./"

export class StepperHandWrittenImpl {
    static SetStepperOptionsImpl(node: KPointer, value: StepperOptions | undefined) {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            const value_value_index  = value_value.index
            let value_value_index_type : int32 = RuntimeType.UNDEFINED
            value_value_index_type = runtimeType(value_value_index)
            thisSerializer.writeInt8(value_value_index_type as int32)
            if ((RuntimeType.OBJECT) == (value_value_index_type)) {
                StepperOpsHandWritten.hookStepperAttributeStepperIndexImpl(node,
                    (value_value_index as Bindable<number>));
                thisSerializer.release()
                return
            } else if ((RuntimeType.NUMBER) == (value_value_index_type)) {
                const value_value_index_value  = value_value_index! as number
                thisSerializer.writeNumber(value_value_index_value)
            }
        }
        ArkUIGeneratedNativeModule._StepperInterface_setStepperOptions(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}