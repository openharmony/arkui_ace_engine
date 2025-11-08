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

import { ExtendableComponent } from "./extendableComponent"
import { CustomDialogControllerExtender, CustomDialogControllerOptionsExtender,
    CustomDialogControllerExternalOptionsExtender, LevelOrderExtender } from '#generated'
import { LevelOrder } from "@ohos.promptAction";

export class CustomDialogController extends CustomDialogControllerExtender {
    customComponent?: ExtendableComponent | undefined = undefined
    constructor(value: CustomDialogControllerOptions) {
        super(convert(value))
        if ((value) !== (undefined) && (value.baseComponent) !== (undefined)) {
            this.customComponent = (value.baseComponent)!
        }
    }
    open(): void {
        if (this.customComponent) {
            const peerNode = this.customComponent!.getPeerNode()
            if (peerNode) {
                super.setOwnerView(peerNode!.getPeerPtr())
                super.open()
            }
        }
    }
    public getExternalOptions(): CustomDialogControllerExternalOptions {
        let options: CustomDialogControllerExternalOptionsExtender = super.getExternalOptions()
        return {customStyle: options.customStyle} as CustomDialogControllerExternalOptions
    }
}
function convert(value: CustomDialogControllerOptions): CustomDialogControllerOptionsExtender {
    let extender: CustomDialogControllerOptionsExtender = value as CustomDialogControllerOptionsExtender
    if (value.levelOrder !== undefined) {
        extender.levelOrderExtender = new LevelOrderExtender(value.levelOrder!.getPeer()!.ptr)
    }
    return extender
}
export interface CustomDialogControllerOptions extends CustomDialogControllerOptionsExtender {
    baseComponent?: ExtendableComponent,
    levelOrder?: LevelOrder,
}
export interface CustomDialogControllerExternalOptions extends CustomDialogControllerExternalOptionsExtender {}