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
import { KPointer } from "@koalaui/interop/InteropTypes";
import { runtimeType, RuntimeType } from "@koalaui/interop";
import { int32, int8 } from "@koalaui/common";
import { Serializer } from "../component/peers/Serializer";

export class RouterExtender {
    public static routerPush(options: router.RouterOptions, ptr: KPointer, finishCallback: (node: KPointer) => void): KPointer {
        const thisSerializer : Serializer = Serializer.hold();
        const url = options.url as (string);
        thisSerializer.writeString(url);

        let recover_type: int32 = RuntimeType.UNDEFINED;
        recover_type = runtimeType(options.recoverable);
        thisSerializer.writeInt8(recover_type as int32);
        if ((RuntimeType.UNDEFINED) != (recover_type)) {
            const recover_value = options.recoverable! as boolean;
            thisSerializer.writeBoolean(recover_value);
        }

        const jsView = ptr as KPointer;
        thisSerializer.writePointer(jsView);

        let callback_type : int32 = RuntimeType.UNDEFINED;
        callback_type = runtimeType(finishCallback);
        thisSerializer.writeInt8(callback_type as int32);
        if ((RuntimeType.UNDEFINED) != (callback_type)) {
            const value_value  = finishCallback! as ((node: KPointer) => void);
            thisSerializer.holdAndWriteCallback(value_value);
        }
        const retVal = ArkUIGeneratedNativeModule._RouterExtender_RouterPush1attribute(thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
        return retVal;
    }

    public static routerReplace(options: router.RouterOptions, ptr: KPointer, enterFinishCallback: (node: KPointer) => void): KPointer {
        const thisSerializer : Serializer = Serializer.hold();
        const url = options.url as (string);
        thisSerializer.writeString(url);

        let recover_type: int32 = RuntimeType.UNDEFINED;
        recover_type = runtimeType(options.recoverable);
        thisSerializer.writeInt8(recover_type as int32);
        if ((RuntimeType.UNDEFINED) != (recover_type)) {
            const recover_value = options.recoverable! as boolean;
            thisSerializer.writeBoolean(recover_value);
        }

        const jsView = ptr as KPointer;
        thisSerializer.writePointer(jsView);

        let callback_type : int32 = RuntimeType.UNDEFINED;
        callback_type = runtimeType(enterFinishCallback);
        thisSerializer.writeInt8(callback_type as int32);
        if ((RuntimeType.UNDEFINED) != (callback_type)) {
            const value_value  = enterFinishCallback! as ((node: KPointer) => void);
            thisSerializer.holdAndWriteCallback(value_value);
        }

        const retVal = ArkUIGeneratedNativeModule._RouterExtender_RouterReplace1attribute(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retVal
    }

    public static routerPushUrl(options: router.RouterOptions): Promise<void> {
        return new Promise<void>(() => {})
    }

    public static routerBack(options?: router.RouterOptions): void {
        if (options !== undefined) {
            const thisSerializer : Serializer = Serializer.hold()
            const url = options.url as (string)
            const url_value  = url!
            thisSerializer.writeString(url_value)

            const param = options.params as (Object | undefined)
            let param_type: int32 = RuntimeType.UNDEFINED
            param_type = runtimeType(param)
            thisSerializer.writeInt8(param_type as int32)
            if ((RuntimeType.UNDEFINED) != (param_type)) {
                const param_value  = param!
                thisSerializer.holdAndWriteObject(param_value)
            }
            ArkUIGeneratedNativeModule._RouterExtender_RouterBack1attribute(thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        } else {
            ArkUIGeneratedNativeModule._RouterExtender_RouterBack0attribute()
        }
    }

    public static routerClear(): void {
        ArkUIGeneratedNativeModule._RouterExtender_RouterClear()
    }

    public static routerRunPage(options: router.RouterOptions, ptr: KPointer, finishCallback: (node: KPointer) => void): KPointer {
        const thisSerializer : Serializer = Serializer.hold();
        const url = options.url as (string);
        thisSerializer.writeString(url);

        let recover_type: int32 = RuntimeType.UNDEFINED;
        recover_type = runtimeType(options.recoverable);
        thisSerializer.writeInt8(recover_type as int32);
        if ((RuntimeType.UNDEFINED) != (recover_type)) {
            const recover_value = options.recoverable! as boolean;
            thisSerializer.writeBoolean(recover_value);
        }

        const jsView = ptr as KPointer;
        thisSerializer.writePointer(jsView);

        let callback_type : int32 = RuntimeType.UNDEFINED;
        callback_type = runtimeType(finishCallback);
        thisSerializer.writeInt8(callback_type as int32);
        if ((RuntimeType.UNDEFINED) != (callback_type)) {
            const value_value  = finishCallback! as ((node: KPointer) => void);
            thisSerializer.holdAndWriteCallback(value_value);
        }
        const retVal = ArkUIGeneratedNativeModule._RouterExtender_RouterRunPage(thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
        return retVal;
    }

    public static moveCommonUnderPageNode(commonNode: KPointer, pageNode: KPointer): void {
        ArkUIGeneratedNativeModule._RouterExtender_MoveCommonUnderPageNode(commonNode, pageNode)
    }

    public static routerShowAlertBeforeBackPage(options: router.EnableAlertOptions): void {
        const message = options.message as string;
        ArkUIGeneratedNativeModule._RouterExtender_ShowAlertBeforeBackPage(message);
    }

    public static routerHideAlertBeforeBackPage(): void {
        ArkUIGeneratedNativeModule._RouterExtender_HideAlertBeforeBackPage();
    }
}