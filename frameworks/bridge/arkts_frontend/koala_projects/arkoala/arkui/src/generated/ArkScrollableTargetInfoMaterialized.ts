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

import { EventTargetInfo, EventTargetInfoInternal } from "./ArkEventTargetInfoMaterialized"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class ScrollableTargetInfoInternal {
    public static fromPtr(ptr: KPointer): ScrollableTargetInfo {
        const obj: ScrollableTargetInfo = new ScrollableTargetInfo()
        obj.peer = new Finalizable(ptr, ScrollableTargetInfo.getFinalizer())
        return obj
    }
}
export class ScrollableTargetInfo extends EventTargetInfo implements MaterializedBase {
    static ctor_scrollabletargetinfo(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ScrollableTargetInfo_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = ScrollableTargetInfo.ctor_scrollabletargetinfo()
        this.peer = new Finalizable(ctorPtr, ScrollableTargetInfo.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ScrollableTargetInfo_getFinalizer()
    }
    public isBegin(): boolean {
        return this.isBegin_serialize()
    }
    public isEnd(): boolean {
        return this.isEnd_serialize()
    }
    private isBegin_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._ScrollableTargetInfo_isBegin(this.peer!.ptr)
        return retval
    }
    private isEnd_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._ScrollableTargetInfo_isEnd(this.peer!.ptr)
        return retval
    }
}
