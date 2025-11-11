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

import { ArkUIGeneratedNativeModule } from '#components'
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KLong, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, InteropNativeModule } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ComponentBase } from '../ComponentBase'
import { PeerNode } from '../PeerNode'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { BusinessError, Callback } from '#external'
import { ErrorCallback } from '@ohos.base'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ArkUIAniUiextensionModal, ArkUIAniModule, ArkUIAniDynamicModal, ArkUIAniDynamicOptions } from 'arkui.ani'
import { EAWorker } from 'std/core'
import { CoroutineExtras } from 'std/debug/concurrency'

class ArkDynamicCallbackHelp {
    onError?: ((e: BusinessError) => void)
    constructor() {
        this.onError = undefined;
    }
}
const DcFlag : int32 = 1000000;
export class ArkDynamicComponentPeer extends ArkCommonMethodPeer {
    _callbackHelp?: ArkDynamicCallbackHelp;
    eaWorker_ : EAWorker | undefined = undefined;
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
        this.InitArkDynamicCallbackHelp();
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkDynamicComponentPeer {
        InteropNativeModule._NativeLog("[AceDynamicComponent] create ArkDynamicComponentPeer start");
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIAniDynamicModal._Dynamic_Construct(peerId, flags)
        const _peer  = new ArkDynamicComponentPeer(_peerPtr, peerId, "DynamicComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    InitArkDynamicCallbackHelp(): void {
        InteropNativeModule._NativeLog("[AceDynamicComponent] InitArkDynamicCallbackHelp entry");
        this._callbackHelp = new ArkDynamicCallbackHelp();
    }
    setDynamicComponentOptionsAttribute(options: DynamicOptions | undefined): void {
        if (options === undefined) {
            InteropNativeModule._NativeLog("[AceDynamicComponent] options is undefined");
            return;
        }
        let innerOption : ArkUIAniDynamicOptions = new ArkUIAniDynamicOptions();
        if (options.entryPoint !== undefined) {
            innerOption.entryPoint = options.entryPoint;
        }
        if (options.worker !== undefined) {
            this.eaWorker_ = options.worker;
            innerOption.workerId = -1;
            if (!this.eaWorker_?.isAlive()) {
                InteropNativeModule._NativeLog("[AceDynamicComponent] eaWorker is not alive, will start");
                this.eaWorker_?.start();
            }
            let p1 = this.eaWorker_?.run<int32>(():int32 => {
                let runId = CoroutineExtras.getWorkerId();
                InteropNativeModule._NativeLog("[AceDynamicComponent] running in eaWorker, runId: " + runId);
                return runId;
            });
            let runId = p1?.Await();
            if (runId != null) {
                innerOption.workerId = runId;
            }
        }
        if (options.backgroundTransparent !== undefined) {
            innerOption.backgroundTransparent = (options.backgroundTransparent) as boolean;
        }
        ArkUIAniDynamicModal._Dynamic_Set_Option(this.peer.ptr, innerOption);
    }
    onErrorAttribute(value: ((e: BusinessError) => void) | undefined): void {
        const help = this._callbackHelp;
        if (help !== undefined && help !== null) {
            help.onError = value;
            ArkUIAniDynamicModal._Dynamic_Set_OnErrorCallback(
                this.peer.ptr, (code1: number, name1: string, message1: string) => {
                    const onError = this._callbackHelp?.onError;
                    if (onError !== undefined && onError !== null) {
                        const param = {
                            code: code1 as int,
                            name: name1,
                            message: message1
                        } as BusinessError
                        onError(param);
                    }
                });
        }
    }
    public isReportFrameEvent(value: boolean | undefined) : void {
        if (value === undefined || value === null) {
            return;
        }
        ArkUIAniDynamicModal._Dynamic_Set_IsReportFrameEvent(this.peer.ptr, value as boolean);
    }
}
export interface DynamicOptions {
    entryPoint: string;
    worker: EAWorker | undefined;
    backgroundTransparent?: boolean;
}
export type DynamicComponentInterface = (options: DynamicOptions) => DynamicComponentAttribute;
export interface DynamicComponentAttribute extends CommonMethod {
    setDynamicComponentOptions(options: DynamicOptions): this {
        return this
    }
    onError(value: ((e: BusinessError) => void) | undefined): this
    isReportFrameEvent(value: boolean | undefined): this
}
export class ArkDynamicComponent extends ArkCommonMethodComponent implements DynamicComponentAttribute {
    getPeer(): ArkDynamicComponentPeer {
        return (this.peer as ArkDynamicComponentPeer)
    }
    public setDynamicComponentOptions(options: DynamicOptions): this {
        if (this.checkPriority("setDynamicComponentOptions")) {
            const options_casted = options as (DynamicOptions | undefined)
            this.getPeer()?.setDynamicComponentOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public onError(value: ((e: BusinessError) => void) | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (((e: BusinessError) => void) | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public isReportFrameEvent(value: boolean | undefined) : this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.isReportFrameEvent(value_casted)
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function DynamicComponentImpl(
    /** @memo */
    style: ((attributes: DynamicComponentAttribute) => void) | undefined,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkDynamicComponent()
    })
    NodeAttach<ArkDynamicComponentPeer>((): ArkDynamicComponentPeer => ArkDynamicComponentPeer.create(receiver, DcFlag), (_: ArkDynamicComponentPeer) => {
        style?.(receiver)
        content_?.()
    })
}