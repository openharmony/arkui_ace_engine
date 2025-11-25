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
import { SyntaxItemPeer } from "./base/SyntaxNodeBase"
import { ArkComponentRoot } from "./ArkComponentRoot"
import { ArkColumnPeer } from "#generated";
import { ObserveSingleton } from "./stateManagement/base/observeSingleton";
import { OBSERVE } from "./stateManagement";
import { PeerNode } from "./PeerNode"
import { RecordData } from "@ohos.base"

/** base class for user's structs */
export abstract class ArkStructBase<T, T_Options> implements ArkCustomComponent {
    private peer?: PeerNode

    setPeer(peer: PeerNode): void {
        this.peer = peer
    }
    getPeer(): PeerNode | undefined {
        return this. peer
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
        initializers?: T_Options,
        reuseKey?: string
    ): void {
        if (reuseKey) {
            ArkStructBase._instantiateReusable(reuseKey!, factory, content, initializers);
            return
        }
        const receiver = remember(() => {
            const instance = factory();
            instance.__initializeStruct(content, initializers);
            return instance;
        });
        receiver._buildWrapper(content, initializers);
    }

    protected __initializeStruct(
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        console.log("__initializeStruct()")
    }

    /** @memo */
    _buildWrapper(
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        ArkComponentRoot(this, (node: PeerNode) => {
            this.__updateStruct(initializers);
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
                    this.aboutToReuse(param, initializers)
                }
            )

        })
    }


    /** @memo */
    static _instantiateReusable<T extends ArkStructBase<T, T_Options>, T_Options>(
        reuseId: string,
        factory: () => T,
        /** @memo */
        content?: () => void,
        initializers?: T_Options,
    ): void {
        /* need to wrap both states and build() of @Component */
        NodeAttach(() => SyntaxItemPeer.create(), (node: SyntaxItemPeer) => {
            const component = remember(() => {
                const instance = factory()
                instance.__initializeStruct(content, initializers);
                node.setOnRecycle(() =>
                    instance.aboutToRecycle()
                )
                return instance
            });
            node.setOnReuse(
                (param?: RecordData) => {
                    component.aboutToReuse(param, initializers)
                }
            )
            component._buildWrapper(content, initializers);
        }, reuseId)
    }

    isV2(): boolean {
        return true;
    }
}
