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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { CustomTheme } from "@ohos.arkui.theme"
import { ThemeColorMode } from "./common"
import { hookWithThemeAttributeModifier, AttributeModifier, AttributeUpdater, hookWithThemeOptions } from "#handwritten"
import { WithThemeModifier } from "./../WithThemeModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { CustomTheme_serializer } from "./../framework/ohos.arkui.theme"
import { ArkThemeScopeManager } from 'arkui/theme/ArkThemeScopeManager';
import { GlobalStateManager } from '@koalaui/runtime';
import { ModifierStateManager } from '../CommonModifier';
export class ArkWithThemePeer extends PeerNode {
    attributeSet?: WithThemeModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWithThemePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._WithTheme_construct(peerId, flags)
        const _peer  = new ArkWithThemePeer(_peerPtr, peerId, 'WithTheme', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWithThemeOptionsAttribute(options: WithThemeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        WithThemeOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._WithThemeInterface_setWithThemeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface WithThemeOptions {
    theme?: CustomTheme;
    colorMode?: ThemeColorMode;
}
export interface WithThemeAttribute {
    setWithThemeOptions(options: WithThemeOptions | undefined): this {
        throw new Error("Unimplemented method setWithThemeOptions")
    }
    attributeModifier(value: AttributeModifier<WithThemeAttribute> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkWithThemeStyle implements WithThemeAttribute {
    setWithThemeOptions(options: WithThemeOptions | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<WithThemeAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkWithThemeComponent extends ComponentBase implements WithThemeAttribute {
    getPeer(): ArkWithThemePeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkWithThemePeer)
    }
    public setWithThemeOptions(options: WithThemeOptions | undefined): this {
        if (this.checkPriority("setWithThemeOptions")) {
            hookWithThemeOptions(this, options);
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WithThemeAttribute> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookWithThemeAttributeModifier(this, value);
        })
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
export function WithThemeImpl(
    @memo
    style: ((attributes: WithThemeAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkWithThemeComponent>((): ArkWithThemeComponent => {
        return new ArkWithThemeComponent()
    })
    NodeAttach<ArkWithThemePeer>((): ArkWithThemePeer => ArkWithThemePeer.create(receiver), (peer: ArkWithThemePeer): void => {
        receiver.setPeer(peer)

        const withThemeId = receiver.getPeer()?.getId() ?? 0;
        ArkThemeScopeManager.getInstance().onComponentCreateEnter("WithTheme", receiver.getPeer()?.getId(), receiver.isFirstRender)
        style?.(receiver)
        ArkThemeScopeManager.getInstance().onComponentCreateExit(receiver.getPeer()?.getId())
        receiver.setPeer(undefined)

        GlobalStateManager.instance.namedState<int32>("themeScopeId", () => withThemeId);
        const themeOptions = ArkThemeScopeManager.getInstance().getThemeOptionsById(withThemeId);
        ArkThemeScopeManager.getInstance().updateColorMode(themeOptions?.colorMode ?? ThemeColorMode.SYSTEM);

        content_?.()

        ArkThemeScopeManager.getInstance().restoreColorMode();
        ArkThemeScopeManager.getInstance().onScopeExit();

        receiver.isFirstRender = false;
    })
}

export class WithThemeOptions_serializer {
    public static write(buffer: SerializerBase, value: WithThemeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTheme  = value.theme
        if (valueHolderForTheme !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForThemeTmpValue  = valueHolderForTheme!
            CustomTheme_serializer.write(valueSerializer, valueHolderForThemeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColorMode  = value.colorMode
        if (valueHolderForColorMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorModeTmpValue  = (valueHolderForColorMode as ThemeColorMode)
            valueSerializer.writeInt32(valueHolderForColorModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): WithThemeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const themeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let themeTmpBuf : CustomTheme | undefined = undefined
        if ((themeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            themeTmpBuf = CustomTheme_serializer.read(valueDeserializer)
        }
        const themeTmpResult : CustomTheme | undefined = themeTmpBuf
        const colorModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorModeTmpBuf : ThemeColorMode | undefined = undefined
        if ((colorModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            colorModeTmpBuf = ThemeColorMode.fromValue(valueDeserializer.readInt32())
        }
        const colorModeTmpResult : ThemeColorMode | undefined = colorModeTmpBuf
        let value : WithThemeOptions = ({theme: themeTmpResult, colorMode: colorModeTmpResult} as WithThemeOptions)
        return value
    }
}
