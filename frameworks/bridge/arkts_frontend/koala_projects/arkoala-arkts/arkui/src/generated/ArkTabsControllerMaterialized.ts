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

import { TranslateOptions } from "./ArkCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class TabsControllerInternal {
    public static fromPtr(ptr: KPointer): TabsController {
        const obj : TabsController = new TabsController()
        obj.peer = new Finalizable(ptr, TabsController.getFinalizer())
        return obj
    }
}
export class TabsController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_tabscontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabsController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TabsController.ctor_tabscontroller()
        this.peer = new Finalizable(ctorPtr, TabsController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TabsController_getFinalizer()
    }
    public changeIndex(value: number): void {
        const value_casted = value as (number)
        this.changeIndex_serialize(value_casted)
        return
    }
    public preloadItems(indices?: Array<number>): Promise<void> {
        const indices_casted = indices as (Array<number> | undefined)
        return this.preloadItems_serialize(indices_casted)
    }
    public setTabBarTranslate(translate: TranslateOptions): void {
        const translate_casted = translate as (TranslateOptions)
        this.setTabBarTranslate_serialize(translate_casted)
        return
    }
    public setTabBarOpacity(opacity: number): void {
        const opacity_casted = opacity as (number)
        this.setTabBarOpacity_serialize(opacity_casted)
        return
    }
    private changeIndex_serialize(value: number): void {
        ArkUIGeneratedNativeModule._TabsController_changeIndex(this.peer!.ptr, value)
    }
    private preloadItems_serialize(indices?: Array<number>): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        let indices_type : int32 = RuntimeType.UNDEFINED
        indices_type = runtimeType(indices)
        thisSerializer.writeInt8(indices_type as int32)
        if ((RuntimeType.UNDEFINED) != (indices_type)) {
            const indices_value  = indices!
            thisSerializer.writeInt32(indices_value.length as int32)
            for (let i = 0; i < indices_value.length; i++) {
                const indices_value_element : number = indices_value[i]
                thisSerializer.writeNumber(indices_value_element)
            }
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._TabsController_preloadItems(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private setTabBarTranslate_serialize(translate: TranslateOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTranslateOptions(translate)
        ArkUIGeneratedNativeModule._TabsController_setTabBarTranslate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setTabBarOpacity_serialize(opacity: number): void {
        ArkUIGeneratedNativeModule._TabsController_setTabBarOpacity(this.peer!.ptr, opacity)
    }
}
