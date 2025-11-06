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
import { ArkComponentRoot } from "./ArkComponentRoot"
import { ArkColumnPeer } from "#generated";
import { ObserveSingleton } from "./stateManagement/base/observeSingleton";
import { OBSERVE } from "./stateManagement";
import { PeerNode } from "./PeerNode"
import { RecordData } from "@ohos.base"
import { ArkCommonMethodComponent, ArkCommonPeer, CommonMethod } from 'arkui/component/common';
import { memo_skip } from '@koalaui/runtime/annotations';
import { int32 } from '@koalaui/common';

/** base class for user's structs */
export abstract class ArkStructBase<T, T_Options> implements ArkCustomComponent {
    private peer?: PeerNode

    private themeScopeId?: int32

    setPeer(peer: PeerNode): void {
        this.peer = peer
    }
    getPeer(): PeerNode | undefined {
        return this. peer
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
            ArkStructBase._instantiateReusable(reuseKey!, factory, content, initializers);
            return
        }
        const receiver = remember(() => {
            const instance = factory();
            instance.__initializeStruct(content, initializers?.());
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
            this.__updateStruct(initializers?.());
    }

    /** @memo:intrinsic */
    buildArkComponentRoot(initializers?: () => T_Options) {
        ArkComponentRoot(this, (node: PeerNode) => {
            this.updateStructWithMemoParameter(initializers);
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
                this.aboutToRecycle()
            )
            node.setOnReuse(
                (param?: RecordData) => {
                    this.aboutToReuse(param, initializers?.())
                }
            )

        })
    }

    /** @memo */
    _buildWrapper(
        /** @memo */
        content?: () => void,
        initializers?: () => T_Options
    ): void {
        this.callStyles();
        const hasCommonStyles = remember(() => this.hasCommonStyles)
 
        if (hasCommonStyles) {
            const receiver = remember(() => new ArkCommonMethodComponent());
            NodeAttach(() => ArkCommonPeer.create(receiver), (_: ArkCommonPeer) => {
                this.applyStyles(receiver);
                this.buildArkComponentRoot(initializers);
            })
        } else {
            this.buildArkComponentRoot(initializers);
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
        NodeAttach(() => ArkColumnPeer.create(undefined), (node: ArkColumnPeer) => { // replace with Frontend Node later
            const component = remember(() => {
                const instance = factory()
                instance.__initializeStruct(content, initializers?.());
                node.setOnRecycle(() =>
                    instance.aboutToRecycle()
                )
                return instance
            });
            node.setOnReuse(
                (param?: RecordData) => {
                    component.aboutToReuse(param, initializers?.())
                }
            )
            component._buildWrapper(content, initializers);
        }, reuseId)
    }

    isV2(): boolean {
        return true;
    }
}
