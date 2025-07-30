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

import router from "@ohos/router";
import { ArkUIGeneratedNativeModule } from "#components"
import { InteropNativeModule } from "@koalaui/interop/InteropNativeModule";
import { KPointer } from "@koalaui/interop/InteropTypes";
import { runtimeType, RuntimeType } from "@koalaui/interop";
import { int32, int8 } from "@koalaui/common";
import { Serializer } from "../component/peers/Serializer";

export class RouterExtender {
    public static routerPush(options: router.RouterOptions): KPointer {
        const url = options.url as (string)
        const retVal = ArkUIGeneratedNativeModule._RouterExtender_RouterPush1attribute(url)
        return retVal
    }

    public static routerReplace(options: router.RouterOptions, finishCallback: () => void): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        const url = options.url as (string)
        thisSerializer.writeString(url)
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(finishCallback)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = finishCallback! as (() => void)
            thisSerializer.holdAndWriteCallback(value_value)
        }
        const retVal = ArkUIGeneratedNativeModule._RouterExtender_RouterReplace1attribute(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retVal
    }

    public static routerPushUrl(options: router.RouterOptions): Promise<void> {
        return new Promise<void>(() => {})
    }

    public static routerBack(options?: router.RouterOptions): void {
        if (options) {
            const url = options.url as (string)
        } else {
            ArkUIGeneratedNativeModule._RouterExtender_RouterBack0attribute()
        }
    }

    public static routerClear(): void {
        ArkUIGeneratedNativeModule._RouterExtender_RouterClear()
    }

    public static routerRunPage(options: router.RouterOptions): KPointer {
        const url = options.url as (string)
        const retVal = ArkUIGeneratedNativeModule._RouterExtender_RouterRunPage(url)
        return retVal
    }

    public static moveCommonUnderPageNode(commonNode: KPointer, pageNode: KPointer): void {
        ArkUIGeneratedNativeModule._RouterExtender_MoveCommonUnderPageNode(commonNode, pageNode)
    }
}