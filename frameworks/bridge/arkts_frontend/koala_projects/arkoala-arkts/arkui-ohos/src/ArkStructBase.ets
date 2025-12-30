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

import { NodeAttach, remember } from "@koalaui/runtime"
import { ArkCustomComponent } from "./ArkCustomComponent"
import { SyntaxItemPeer } from './base/SyntaxNodeBase'
import { ArkComponentRoot } from "./ArkComponentRoot"
import { ArkColumnPeer } from "#generated";
import { ObserveSingleton } from "./stateManagement/base/observeSingleton";
import { OBSERVE } from "./stateManagement";
import { PeerNode } from "./PeerNode"
import { RecordData } from "@ohos.base"
import { ArkCommonMethodComponent, ArkCommonPeer, CommonMethod } from 'arkui/component/common';
import { memo_skip } from '@koalaui/runtime/annotations';
import { int32 } from '@koalaui/common';
import { IExtendableComponent } from "./component/extendableComponent";

/** base class for user's structs */
export abstract class ArkStructBase<T, T_Options> implements ArkCustomComponent {
    private peer?: PeerNode
    public _initializers?: () => T_Options
    reuseForceAddRefFlag: boolean = false;
    private themeScopeId?: int32

    setPeer(peer: PeerNode): void {
        this.peer = peer
    }
    getPeer(): PeerNode | undefined {
        return this. peer
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

    aboutToReuse(param: RecordData, initializers?: T_Options): void { }
    aboutToRecycle(): void {}
    __aboutToReuse_Internal(param?: RecordData): void { }
    __aboutToRecycle_Internal(): void { }

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
            instance.__initializeStruct(content, initializers?.());
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
                this.reuseForceAddRefFlag = !this.reuseForceAddRefFlag;
                if (this.reuseForceAddRefFlag) {
                    // switch branch to force update dependency
                    this.updateStructWithMemoParameter(initializers);
                } else {
                    this.updateStructWithMemoParameter(initializers);
                }
            } else {
                this.updateStructWithMemoParameter(initializers);
            }
            const savedRenderingComponent = OBSERVE.renderingComponent
            OBSERVE.renderingComponent = 
            this.isV2()
                ? ObserveSingleton.RenderingComponentV2
                : ObserveSingleton.RenderingComponentV1;
            this.build();
            OBSERVE.renderingComponent = savedRenderingComponent
            remember(() => {
                ObserveSingleton.instance.applyTaskDelayMutableStateChange(() => {
                    this.onDidBuild();
                })
            });
            node.setOnRecycle(() =>
                this.__aboutToRecycle_Internal()
            )
            node.setOnReuse(
                (param?: RecordData) => {
                    this.__aboutToReuse_Internal(param)
                }
            )
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
        /* need to wrap both states and build() of @Component */
        NodeAttach(() => SyntaxItemPeer.create(), (node: SyntaxItemPeer) => {
            const component = remember(() => {
                const instance = factory()
                instance.__initializeStruct(content, initializers?.());
                node.setOnRecycle(() =>
                    instance.__aboutToRecycle_Internal()
                )
                node.component = instance as IExtendableComponent
                node.isCustomComponent = true
                return instance
            });
            node.setOnReuse(
                (param?: RecordData) => {
                    component.__aboutToReuse_Internal(param)
                }
            )
            component.setInitializers(initializers);
            component._buildWrapper(content, initializers, true);
        }, reuseId + '@Component')
    }

    isV2(): boolean {
        return true;
    }
}
