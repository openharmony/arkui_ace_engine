/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { NodeAttach, remember, once } from '@koalaui/runtime';
import { ArkCustomComponent } from "./ArkCustomComponent"
import { SyntaxItemPeer } from './base/SyntaxNodeBase'
import { ArkComponentRoot } from "./ArkComponentRoot"
import { ArkColumnPeer } from "#generated";
import { ObserveSingleton } from "./stateManagement/base/observeSingleton";
import { IReusePool } from "./stateManagement/utils";
import { OBSERVE } from "./stateManagement";
import { PeerNode } from "./PeerNode"
import { RecordData } from "@ohos.base"
import { ArkCommonMethodComponent, ArkCommonPeer, CommonMethod } from 'arkui/component/common';
import { memo_skip } from '@koalaui/runtime/annotations';
import { int32 } from '@koalaui/common';
import { IExtendableComponent, ExtendableComponent } from './component/extendableComponent';
import { LifeCycleEvent } from './component/customComponent';
import { KPointer } from '@koalaui/interop'
import { GlobalReusePool } from './stateManagement/tools/globalReusePool';

/** base class for user's structs */
export abstract class ArkStructBase<T, T_Options> implements ArkCustomComponent {
    private peer?: PeerNode
    public _initializers?: () => T_Options
    public reuseForceAddRefFlag: boolean = false;
    private themeScopeId?: int32
    private reuseInFlight_: boolean = false;
    public canUpdateStateVars_: boolean = false;

    setPeer(peer: PeerNode): void {
        this.peer = peer
    }
    getPeer(): PeerNode | undefined {
        return this. peer
    }

 
    __setReuseInFlight_Internal(v: boolean): void {
        this.reuseInFlight_ = v;
    }

    __getReuseInFlight_Internal(): boolean {
        return this.reuseInFlight_;
    }

    setInitializers(initializers?: () => T_Options): void {
        this._initializers = initializers
    }

    setThemeScopeId(themeScopeId: int32): void {
        this.themeScopeId = themeScopeId
    }
    getThemeScopeId(): int32 | undefined {
        return this.themeScopeId
    }

    onFormRecycle(): string {
        throw new Error("Not supported yet");
    }
    onFormRecover(statusData: string): void {
        throw new Error("Not supported yet");
    }
    ClearParentReusePool(): void {}
    __getMemOpt__Internal(): int32 { return 0; }

    aboutToReuse(param: RecordData, initializers?: T_Options): void { }
    aboutToRecycle(): void {}
    __aboutToReuse_Internal(param?: RecordData): void { }
    __aboutToRecycle_Internal(): void { }
    __debugLine_Internal(ptr: KPointer): void { }
    switchHasBeenRecycle(recycle: boolean) {}
    // Can be overridden as an effect of @Prop, @Watch etc
    protected __updateStruct(initializers?: T_Options): void { }


    /** @memo */
    static _instantiate<T extends ArkStructBase<T, T_Options>, T_Options>(
        factory: () => T,
        /** @memo */
        content?: () => void,
        initializers?: () => T_Options,
        reuseKey?: string
    ): void {
        if (reuseKey) {
            ArkStructBase._instantiateReusable<T, T_Options>(reuseKey!, factory, content, initializers);
            return
        }
        const receiver = remember(() => {
            const instance = factory();
            const savedRenderingComponent = OBSERVE.renderingComponent;
            OBSERVE.renderingComponent = ObserveSingleton.RenderingPause;
            instance.__initializeStruct(content, initializers?.());
            OBSERVE.renderingComponent = savedRenderingComponent;
            instance.setInitializers(initializers);
            return instance;
        });
        receiver._buildWrapper(content, initializers);
    }

    /** @memo:intrinsic */
    callStyles(): void {}
 
    applyStyles(instance: CommonMethod): void {}
 
    get hasCommonStyles(): boolean {
        return false;
    }

    protected __initializeStruct(
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        console.log("__initializeStruct()")
    }

    /** @memo */
    updateStructWithMemoParameter(
        @memo_skip
        initializers?: () => T_Options): void {
            // ** parameter is not reliable any more in reuse scenarios.. **
            this.__updateStruct(this._initializers?.() as T_Options | undefined);
    }

    /** @memo:intrinsic */
    buildArkComponentRoot(initializers?: () => T_Options, callFromReuse: boolean = false) {
        ArkComponentRoot(this, (node: PeerNode) => {
            if (callFromReuse) {
                // reuse component should manually update dependency
                // this flag should be switched when reuse to force record again
                if (this.reuseForceAddRefFlag) {
                    // switch branch to force update dependency
                    this.updateStructWithMemoParameter(initializers);
                } else {
                    this.updateStructWithMemoParameter(initializers);
                }
            } else {
                this.updateStructWithMemoParameter(initializers);
            }
            once(() => {
                this.canUpdateStateVars_ = true;
            });
            const savedRenderingComponent = OBSERVE.renderingComponent
            OBSERVE.renderingComponent = 
            this.isV2()
                ? ObserveSingleton.RenderingComponentV2
                : ObserveSingleton.RenderingComponentV1;
            this.build();
            remember(() => {
                ObserveSingleton.instance.applyTaskDelayMutableStateChange(() => {
                    this.__getLifecycle__Internal()?.trigger(LifeCycleEvent.ON_BUILD);
                    this.onDidBuild();
                })
                if (node.peer) {
                    this.__debugLine_Internal(node.peer.ptr);
                }
            });
            node.setOnRecycle(() => {
                this.switchHasBeenRecycle(true);
                this.__aboutToRecycle_Internal()
            })
            node.setOnReuse(
                (param?: RecordData) => {
                    this.switchHasBeenRecycle(false);
                    this.__aboutToReuse_Internal(param)
                }
            )
            OBSERVE.renderingComponent = savedRenderingComponent;
        })
    }

    /** @memo */
    _buildWrapper(
        /** @memo */
        content?: () => void,
        initializers?: () => T_Options,
        callFromReuse: boolean = false
    ): void {
        this.callStyles();
        const hasCommonStyles = remember(() => this.hasCommonStyles)
 
        if (hasCommonStyles) {
            const receiver = remember(() => new ArkCommonMethodComponent());
            NodeAttach(() => ArkCommonPeer.create(receiver), (_: ArkCommonPeer) => {
                this.applyStyles(receiver);
                this.buildArkComponentRoot(initializers, callFromReuse);
            })
        } else {
            this.buildArkComponentRoot(initializers, callFromReuse);
        }
    }

    /** @memo */
    static _instantiateReusable<T extends ArkStructBase<T, T_Options>, T_Options>(
        reuseId: string,
        factory: () => T,
        /** @memo */
        content?: () => void,
        initializers?: () => T_Options,
    ): void {
        const hashIdx = reuseId.indexOf('#');
        const classKey = hashIdx >= 0 ? reuseId.substring(0, hashIdx) : reuseId;
        const userReuseId: string | undefined = hashIdx >= 0 ? reuseId.substring(hashIdx + 1) : undefined;

        const preRenderPool = GlobalReusePool.getPreRenderPool();
        if (preRenderPool !== undefined) {
            console.log(`GlobalReuse: _instantiateReusable PRE-RENDER for ${classKey} reuseId=${userReuseId ?? '<default>'}`);
            const instance = factory();
            instance.__initializeStruct(content, initializers?.());
            instance.setInitializers(initializers);
            preRenderPool!.push(classKey, instance as Object, userReuseId);
            return;
        }

        GlobalReusePool.pendingInitializersForReuse = initializers as Object | undefined;

        let preRendered: T | undefined = undefined;
        const currentObj = ExtendableComponent.current;
        if (currentObj !== undefined && currentObj instanceof ExtendableComponent) {
            let pool = (currentObj as ExtendableComponent).__getReusePoolForClass__Internal(classKey);
            if (pool !== undefined && pool!.isActive()) {
                const peeked = pool!.peek(classKey, userReuseId);
                if (peeked !== undefined && peeked instanceof ArkStructBase) {
                    const popped = pool!.pop(classKey, userReuseId);
                    preRendered = popped as T;
                } else {
                    // First pool empty — try next pool up the chain
                    const alt = (currentObj as ExtendableComponent).__getReusePoolForClass__Internal(classKey, pool);
                    if (alt !== undefined && alt!.isActive()) {
                        const peeked2 = alt!.peek(classKey, userReuseId);
                        if (peeked2 !== undefined && peeked2 instanceof ArkStructBase) {
                            const popped2 = alt!.pop(classKey, userReuseId);
                            preRendered = popped2 as T;
                        }
                    }
                }
            }
        }

        NodeAttach(() => SyntaxItemPeer.create(), (node: SyntaxItemPeer) => {
            const component = remember(() => {
                const instance = preRendered !== undefined ? preRendered! : factory();
                if (preRendered === undefined) {
                    instance.__initializeStruct(content, initializers?.());
                }

                node.setOnRecycle((): void => {
                    instance.__setReuseInFlight_Internal(false);
                    instance.switchHasBeenRecycle(true);
                    instance.__aboutToRecycle_Internal();
                });
                node.component = instance as IExtendableComponent;
                node.isCustomComponent = true;
                return instance;
            });

            node.setOnReuse((param?: RecordData) => {
                if (component.__getReuseInFlight_Internal()) return;
                component.__setReuseInFlight_Internal(true);
                component.switchHasBeenRecycle(false);
                component.__aboutToReuse_Internal(param);
                component.__setReuseInFlight_Internal(false);
            });
            component.setInitializers(initializers);
            component._buildWrapper(content, initializers, true);
        }, reuseId + '@Component');
    }

    isV2(): boolean {
        return true;
    }

    getName(): string {
        return '';
    }
}
