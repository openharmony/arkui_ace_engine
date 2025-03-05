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

import { PerfMonitorActionType, PerfMonitorSourceType } from "./ArkArkuiExternalInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class GlobalScope_ohos_arkui_performanceMonitorInternal {
    public static fromPtr(ptr: KPointer): GlobalScope_ohos_arkui_performanceMonitor {
        const obj : GlobalScope_ohos_arkui_performanceMonitor = new GlobalScope_ohos_arkui_performanceMonitor()
        obj.peer = new Finalizable(ptr, GlobalScope_ohos_arkui_performanceMonitor.getFinalizer())
        return obj
    }
}
export class GlobalScope_ohos_arkui_performanceMonitor implements MaterializedBase {
    peer?: Finalizable | undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_globalscope_ohos_arkui_performancemonitor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_ctor()
        return retval
    }
     constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = GlobalScope_ohos_arkui_performanceMonitor.ctor_globalscope_ohos_arkui_performancemonitor()
        this.peer = new Finalizable(ctorPtr, GlobalScope_ohos_arkui_performanceMonitor.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_getFinalizer()
    }
    public static begin(scene: string, startInputType: PerfMonitorActionType, note?: string): void {
        const scene_casted = scene as (string)
        const startInputType_casted = startInputType as (PerfMonitorActionType)
        const note_casted = note as (string | undefined)
        GlobalScope_ohos_arkui_performanceMonitor.begin_serialize(scene_casted, startInputType_casted, note_casted)
        return
    }
    public static end(scene: string): void {
        const scene_casted = scene as (string)
        GlobalScope_ohos_arkui_performanceMonitor.end_serialize(scene_casted)
        return
    }
    public static recordInputEventTime(actionType: PerfMonitorActionType, sourceType: PerfMonitorSourceType, time: number): void {
        const actionType_casted = actionType as (PerfMonitorActionType)
        const sourceType_casted = sourceType as (PerfMonitorSourceType)
        const time_casted = time as (number)
        GlobalScope_ohos_arkui_performanceMonitor.recordInputEventTime_serialize(actionType_casted, sourceType_casted, time_casted)
        return
    }
    private static begin_serialize(scene: string, startInputType: PerfMonitorActionType, note?: string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let note_type : int32 = RuntimeType.UNDEFINED
        note_type = runtimeType(note)
        thisSerializer.writeInt8(note_type as int32)
        if ((RuntimeType.UNDEFINED) != (note_type)) {
            const note_value  = note!
            thisSerializer.writeString(note_value)
        }
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_begin(scene, (startInputType.valueOf() as int32), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private static end_serialize(scene: string): void {
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_end(scene)
    }
    private static recordInputEventTime_serialize(actionType: PerfMonitorActionType, sourceType: PerfMonitorSourceType, time: number): void {
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime((actionType.valueOf() as int32), (sourceType.valueOf() as int32), time)
    }
}
