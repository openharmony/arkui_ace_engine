/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

import { ArkThemeScopeManager } from "#arktheme"
import { ArkUIAniUIExtensionOptions } from "arkui.ani"
import { ComponentContent } from "arkui.ComponentContent"
import { KLong } from "@koalaui/interop"
import { KPointer, InteropNativeModule } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { CommonMethod, TerminationInfo, ArkCommonMethodComponent } from "./common"
import { ErrorCallback, BusinessError } from "@ohos.base"
import { AttributeModifier, hookEmbeddedComponentAttributeModifier } from "#handwritten"
import { default as Want } from "@ohos.app.ability.Want"
import { EmbeddedType } from "./enums"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { EmbeddedComponentModifier } from "./../EmbeddedComponentModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ArkUIExtensionComponentPeerBase } from "./uiExtensionComponent"
import { ArkUIAniUiextensionModal, UiextensionType } from "arkui.ani"

export enum EmbeddedDpiFollowStrategy {
    FOLLOW_HOST_DPI = 0,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1
}

export enum EmbeddedWindowModeFollowStrategy {
    FOLLOW_HOST_WINDOW_MODE = 0,
    FOLLOW_UI_EXTENSION_ABILITY_WINDOW_MODE = 1
}

export interface EmbeddedOptions {
    placeholder?: ComponentContent;
    dpiFollowStrategy?: EmbeddedDpiFollowStrategy;
    windowModeFollowStrategy?: EmbeddedWindowModeFollowStrategy;
    areaChangePlaceholder?: Array<[string, ComponentContent]>;
}

export class ArkEmbeddedComponentPeer extends ArkUIExtensionComponentPeerBase {
    embeddedComponentAttributeSet?: EmbeddedComponentModifier;
    public setEmbeddedComponentOptionsAttribute(loader: Want, type?: EmbeddedType, options?: EmbeddedOptions): void {
    InteropNativeModule._NativeLog("[AceEmbeddedComponent] setEmbeddedComponentOptionsAttribute entry");
    if (options !== undefined) {
        let innerOption : ArkUIAniUIExtensionOptions = new ArkUIAniUIExtensionOptions()
        if (options.dpiFollowStrategy !== undefined) {
            innerOption.dpiFollowStrategy = (options.dpiFollowStrategy as EmbeddedDpiFollowStrategy).valueOf();
        }
        if (options.windowModeFollowStrategy !== undefined) {
            innerOption.isWindowModeFollowHost =
                options.windowModeFollowStrategy === EmbeddedWindowModeFollowStrategy.FOLLOW_HOST_WINDOW_MODE;
        }
        if (options.placeholder !== undefined) {
            if (options.placeholder!.getNodePtr() !== null && options.placeholder!.getNodePtr() !== undefined) {
                innerOption.initPlaceholder = options.placeholder!.getNodePtr() as KLong;
            }
        }
        if (options?.areaChangePlaceholder) {
            const value_areaChangePlaceholder_value = options.areaChangePlaceholder!
            for (const pairValue of value_areaChangePlaceholder_value) {
                const placeholderNode = pairValue[1]!
                if (pairValue[0] === 'ROTATION') {
                    innerOption.rotationPlaceholder = (placeholderNode!.getNodePtr()) as KLong;
                } else if (pairValue[0] === 'FOLD_TO_EXPAND') {
                    innerOption.flodPlaceholder = (placeholderNode!.getNodePtr()) as KLong;
                } else if (pairValue[0] === 'UNDEFINED') {
                    innerOption.undefinedPlaceholder = (placeholderNode!.getNodePtr()) as KLong;
                }
            }
        }
        ArkUIAniUiextensionModal._Uiextension_Set_Option(this.peer.ptr, innerOption); 
        } 
        ArkUIAniUiextensionModal._Uiextension_Set_Want(this.peer.ptr, loader); 
    }

    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkEmbeddedComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIAniUiextensionModal._Uiextension_Construct(peerId, flags, UiextensionType.EmbeddedComponent)
        const _peer  = new ArkEmbeddedComponentPeer(_peerPtr, peerId, 'EmbeddedComponent', flags)
        component?.setPeer(_peer)
        InteropNativeModule._NativeLog("[AceUiextensionComponent] ArkEmbeddedComponentPeer Create");
        return _peer
    }
}
export interface EmbeddedComponentAttribute extends CommonMethod {
    setEmbeddedComponentOptions(loader: Want, type?: EmbeddedType, options?: EmbeddedOptions): this {
        throw new Error("Unimplemented method setEmbeddedComponentOptions")
    }
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onTerminated")
    }
    onError(value: ErrorCallback<BusinessError> | undefined): this {
        throw new Error("Unimplemented method onError")
    }
    attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
    onDrawReady(value: (() => void) | undefined): this { 
        throw new Error("Unimplemented method onDrawReady") 
    }
}
export class ArkEmbeddedComponentComponent extends ArkCommonMethodComponent implements EmbeddedComponentAttribute {
    getPeer(): ArkEmbeddedComponentPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkEmbeddedComponentPeer)
    }
    public setEmbeddedComponentOptions(loader: Want, type?: EmbeddedType, options?: EmbeddedOptions): this {
        if (this.checkPriority("setEmbeddedComponentOptions")) {
            const loader_casted = loader as (Want)
            const type_casted = type as (EmbeddedType | undefined)
            const options_casted = options as (EmbeddedOptions | undefined)
            this.getPeer()?.setEmbeddedComponentOptionsAttribute(loader_casted, type_casted, options_casted)
            this.applyOptionsFinish('EmbeddedComponentAttribute');
            return this
        }
        return this
    }
    public onTerminated(value: ((value0: TerminationInfo) => void) | undefined): this {
        if (this.checkPriority("onTerminated")) {
            const value_casted = value as (((value0: TerminationInfo) => void) | undefined)
            this.getPeer()?.setOnTerminatedAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ErrorCallback<BusinessError> | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback<BusinessError> | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookEmbeddedComponentAttributeModifier(this, value);
        return this
    }
    public onDrawReady(value: (() => void) | undefined): this {
        if (this.checkPriority("onDrawReady")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnDrawReadyAttribute(value_casted)
            return this
        } 
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function EmbeddedComponentImpl(
    @memo
    style: ((attributes: EmbeddedComponentAttribute) => void) | undefined,
): void {
    const receiver = remember<ArkEmbeddedComponentComponent>((): ArkEmbeddedComponentComponent => {
        return new ArkEmbeddedComponentComponent()
    })
    NodeAttach<ArkEmbeddedComponentPeer>((): ArkEmbeddedComponentPeer => ArkEmbeddedComponentPeer.create(receiver), (peer: ArkEmbeddedComponentPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
    })
}

@memo
export function EmbeddedComponent(
    @memo @memo_skip
    style: ((attributes: EmbeddedComponentAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkEmbeddedComponentComponent>((): ArkEmbeddedComponentComponent => {
        return new ArkEmbeddedComponentComponent()
    })
    NodeAttach<ArkEmbeddedComponentPeer>((): ArkEmbeddedComponentPeer => ArkEmbeddedComponentPeer.create(receiver), (_: ArkEmbeddedComponentPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

