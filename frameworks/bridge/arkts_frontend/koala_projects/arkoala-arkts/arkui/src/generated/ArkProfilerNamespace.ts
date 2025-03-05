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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export namespace Profiler {
    export class GlobalScope_Profiler_inspector {
        public static registerVsyncCallback(callback_: ((info: string) => void)): void {
            const callback__casted = callback_ as (((info: string) => void))
            GlobalScope_Profiler_inspector.registerVsyncCallback_serialize(callback__casted)
            return
        }
        public static unregisterVsyncCallback(): void {
            GlobalScope_Profiler_inspector.unregisterVsyncCallback_serialize()
            return
        }
        private static registerVsyncCallback_serialize(callback_: ((info: string) => void)): void {
            const thisSerializer : Serializer = Serializer.hold()
            thisSerializer.holdAndWriteCallback(callback_)
            ArkUIGeneratedNativeModule._GlobalScope_Profiler_inspector_registerVsyncCallback(thisSerializer.asArray(), thisSerializer.length())
            thisSerializer.release()
        }
        private static unregisterVsyncCallback_serialize(): void {
            ArkUIGeneratedNativeModule._GlobalScope_Profiler_inspector_unregisterVsyncCallback()
        }
    }
}
export namespace Profiler {
    export function registerVsyncCallback(callback_: ((info: string) => void)): void {
        GlobalScope_Profiler_inspector.registerVsyncCallback(callback_)
    }
    export function unregisterVsyncCallback(): void {
        GlobalScope_Profiler_inspector.unregisterVsyncCallback()
    }
}
