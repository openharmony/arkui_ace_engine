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

import { KPointer, runtimeType, RuntimeType } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule } from "#components"
import { CustomTheme } from "@ohos/arkui/theme"
import { AttributeModifier, ThemeColorMode } from "./common"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Serializer } from "./peers/Serializer"
import { Deserializer } from "./peers/Deserializer";
import { ArkThemeScopeManager } from '../handwritten/theme/ArkThemeScopeManager';
import { ArkThemeBase } from '../handwritten/theme/ArkThemeBase';
import { ArkThemeNativeHelper } from '../handwritten/theme/ArkThemeNativeHelper';

export class ArkWithThemePeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWithThemePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._WithTheme_construct(peerId, flags)
        const _peer  = new ArkWithThemePeer(_peerPtr, peerId, "WithTheme", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWithThemeOptionsAttribute(options: WithThemeOptions): void {
        const elmtId: int32  = this.getId();
        const colorMode = options.colorMode ?? ThemeColorMode.SYSTEM;
        const cloneTheme = ArkThemeScopeManager.cloneCustomThemeWithExpand(options.theme);
        const theme: ArkThemeBase = ArkThemeScopeManager.getInstance().makeTheme(cloneTheme, colorMode);
        // bind theme to theme scope with elmtId
        theme.bindToScope(elmtId);

        // prepare on theme scope destroy callback
        const onThemeScopeDestroy = () => {
            ArkThemeScopeManager.getInstance().onScopeDestroy(elmtId);
        }

        // keep for backward compatibility
        ArkThemeNativeHelper.sendThemeToNative(theme, elmtId);
        // new approach to apply theme in native side
        ArkThemeNativeHelper.createInternal(elmtId, theme.id, cloneTheme, colorMode, onThemeScopeDestroy);

        ArkThemeScopeManager.getInstance().onScopeEnter(elmtId, options ?? {} as WithThemeOptions, theme);
    }
}
export interface WithThemeOptions {
    theme?: CustomTheme;
    colorMode?: ThemeColorMode;
}
export type WithThemeInterface = (options: WithThemeOptions) => WithThemeAttribute;
export interface WithThemeAttribute {
    // attributeModifier(value: AttributeModifier<WithThemeAttribute> | undefined): this
}
export class ArkWithThemeStyle implements WithThemeAttribute {
    public attributeModifier(value: AttributeModifier<WithThemeAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: WithThemeAttribute): void {
    }
}

export class ArkWithThemeComponent extends ComponentBase implements WithThemeAttribute {
    getPeer(): ArkWithThemePeer {
        return (this.peer as ArkWithThemePeer)
    }
    public setWithThemeOptions(options: WithThemeOptions): this {
        if (this.checkPriority("setWithThemeOptions")) {
            const options_casted = options as (WithThemeOptions)
            this.getPeer()?.setWithThemeOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    _modifier?: AttributeModifier<WithThemeAttribute> | undefined
    public attributeModifier(value: AttributeModifier<WithThemeAttribute> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
        ArkThemeScopeManager.getInstance().onScopeExit();
        // getUINativeModule().theme.pop();
    }
}
/** @memo */
export function WithTheme(
    /** @memo */
    style: ((attributes: WithThemeAttribute) => void) | undefined,
    options: WithThemeOptions,
    /** @memo */
    content_: (() => void) | undefined,
): void {
    const receiver = remember<ArkWithThemeComponent>((): ArkWithThemeComponent => {
        return new ArkWithThemeComponent()
    })
    NodeAttach<ArkWithThemePeer>((): ArkWithThemePeer => ArkWithThemePeer.create(receiver), (_: ArkWithThemePeer): void => {
        ArkThemeScopeManager.getInstance().onComponentCreateEnter("WithTheme", receiver.getPeer()?.getId(), receiver.isFirstBuild)
        receiver.setWithThemeOptions(options)
        style?.(receiver)
        content_?.()
        ArkThemeScopeManager.getInstance().onComponentCreateExit(receiver.getPeer()?.getId())
        receiver.applyAttributesFinish()
    })
}

export class ArkWithThemeSet implements WithThemeAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: WithThemeAttribute): void {
    }
    public attributeModifier(value: AttributeModifier<WithThemeAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class WithThemeOptions_serializer {
    public static write(buffer: Serializer, value: WithThemeOptions): void {
        let valueSerializer : Serializer = buffer
        const value_theme  = value.theme
        let value_theme_type : int32 = RuntimeType.UNDEFINED
        value_theme_type = runtimeType(value_theme)
        valueSerializer.writeInt8((value_theme_type).toChar())
        if ((RuntimeType.UNDEFINED) != (value_theme_type)) {
            const value_theme_value  = value_theme!
            // CustomTheme_serializer.write(valueSerializer, value_theme_value)
        }
        const value_colorMode  = value.colorMode
        let value_colorMode_type : int32 = RuntimeType.UNDEFINED
        value_colorMode_type = runtimeType(value_colorMode)
        valueSerializer.writeInt8((value_colorMode_type).toChar())
        if ((RuntimeType.UNDEFINED) != (value_colorMode_type)) {
            const value_colorMode_value  = (value_colorMode as ThemeColorMode)
            valueSerializer.writeInt32(value_colorMode_value.valueOf())
        }
    }
    public static read(buffer: Deserializer): WithThemeOptions {
        let valueDeserializer : Deserializer = buffer
        const theme_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let theme_buf : CustomTheme | undefined
        if ((RuntimeType.UNDEFINED) != (theme_buf_runtimeType))
        {
            // theme_buf = CustomTheme_serializer.read(valueDeserializer)
        }
        const theme_result : CustomTheme | undefined = theme_buf
        const colorMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorMode_buf : ThemeColorMode | undefined
        if ((RuntimeType.UNDEFINED) != (colorMode_buf_runtimeType))
        {
            colorMode_buf = ThemeColorMode.fromValue(valueDeserializer.readInt32())
        }
        const colorMode_result : ThemeColorMode | undefined = colorMode_buf
        let value : WithThemeOptions = ({theme: theme_result, colorMode: colorMode_result} as WithThemeOptions)
        return value
    }
}
