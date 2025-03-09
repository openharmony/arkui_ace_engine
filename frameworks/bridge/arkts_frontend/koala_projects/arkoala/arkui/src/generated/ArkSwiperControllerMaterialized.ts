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

import { VoidCallback } from "./ArkUnitsInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class SwiperControllerInternal {
    public static fromPtr(ptr: KPointer): SwiperController {
        const obj: SwiperController = new SwiperController()
        obj.peer = new Finalizable(ptr, SwiperController.getFinalizer())
        return obj
    }
}
export class SwiperController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_swipercontroller(): KPointer {
        const retval = ArkUIGeneratedNativeModule._SwiperController_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = SwiperController.ctor_swipercontroller()
        this.peer = new Finalizable(ctorPtr, SwiperController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwiperController_getFinalizer()
    }
    public showNext(): undefined {
        return this.showNext_serialize()
    }
    public showPrevious(): undefined {
        return this.showPrevious_serialize()
    }
    public changeIndex(index: number, useAnimation?: boolean): undefined {
        const index_casted = index as (number)
        const useAnimation_casted = useAnimation as (boolean | undefined)
        return this.changeIndex_serialize(index_casted, useAnimation_casted)
    }
    public finishAnimation(callback_?: VoidCallback): undefined {
        const callback__casted = callback_ as (VoidCallback | undefined)
        return this.finishAnimation_serialize(callback__casted)
    }
    private showNext_serialize(): undefined {
        const retval = ArkUIGeneratedNativeModule._SwiperController_showNext(this.peer!.ptr)
        return retval
    }
    private showPrevious_serialize(): undefined {
        const retval = ArkUIGeneratedNativeModule._SwiperController_showPrevious(this.peer!.ptr)
        return retval
    }
    private changeIndex_serialize(index: number, useAnimation?: boolean): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        let useAnimation_type: int32 = RuntimeType.UNDEFINED
        useAnimation_type = runtimeType(useAnimation)
        thisSerializer.writeInt8(useAnimation_type)
        if ((RuntimeType.UNDEFINED) != (useAnimation_type)) {
            const useAnimation_value = useAnimation!
            thisSerializer.writeBoolean(useAnimation_value)
        }
        const retval = ArkUIGeneratedNativeModule._SwiperController_changeIndex(this.peer!.ptr, index, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private finishAnimation_serialize(callback_?: VoidCallback): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        let callback__type: int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        const retval = ArkUIGeneratedNativeModule._SwiperController_finishAnimation(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
