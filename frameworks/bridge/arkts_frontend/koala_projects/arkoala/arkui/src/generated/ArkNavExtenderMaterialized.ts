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

import { NavPathStack, NavPathStackInternal } from "./ArkNavPathStackMaterialized"
import { NavExtender_OnUpdateStack } from "./ArkNavigationExtenderInterfaces"
import { NavPathInfo, NavPathInfoInternal } from "./ArkNavPathInfoMaterialized"
import { NavigationOptions, NavigationInterception, LaunchMode, PopInfo, InterceptionShowCallback, InterceptionModeCallback } from "./ArkNavigationInterfaces"
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class NavExtenderInternal {
    public static fromPtr(ptr: KPointer): NavExtender {
        const obj: NavExtender = new NavExtender()
        obj.peer = new Finalizable(ptr, NavExtender.getFinalizer())
        return obj
    }
}
export class NavExtender implements MaterializedBase {
    peer?: Finalizable | undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_navextender(): KPointer {
        const retval = ArkUIGeneratedNativeModule._NavExtender_ctor()
        return retval
    }
     constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr: KPointer = NavExtender.ctor_navextender()
        this.peer = new Finalizable(ctorPtr, NavExtender.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavExtender_getFinalizer()
    }
    public static setUpdateStackCallback(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void {
        const peer_casted = peer as (NavPathStack)
        const callback_casted = callback as (NavExtender_OnUpdateStack)
        NavExtender.setUpdateStackCallback_serialize(peer_casted, callback_casted)
        return
    }
    private static setUpdateStackCallback_serialize(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeNavPathStack(peer)
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._NavExtender_setUpdateStackCallback(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
