/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { CommonMethod, ArkCommonMethodPeer, ArkCommonMethodComponent, AttributeModifier, Callback } from 'arkui/component/common'
import { ResourceColor } from 'arkui/component/units'
import { CopyOptions } from 'arkui/component/enums'
import { CustomBuilder } from 'arkui/component/builder'
import { TextSpanType, TextResponseType } from 'arkui/component/text'
import { TextMenuItem, OnCreateMenuCallback, OnPrepareMenuCallback } from 'arkui/component/textCommon'
import { SelectionContainerExtender } from 'arkui/component/idlize'
import { ModifierStateManager } from 'arkui/CommonModifier'
import { SelectionContainerModifier } from 'arkui/SelectionContainerModifier'
import { hookSelectionContainerAttributeModifier } from '#handwritten'
import { int32 } from '@koalaui/common'
import { KPointer } from '@koalaui/interop'
import { ComponentBase } from 'arkui/ComponentBase'
import { PeerNode } from 'arkui/PeerNode'
import { NodeAttach, remember } from '@koalaui/runtime'

export enum SelectionContainerTextJoinStyle {
    NEWLINE = 0,
    DIRECT = 1
}

export interface SelectionContainerMenuOptions {
    onAppear?: Callback<string>
    onDisappear?: Callback<void>
    onMenuShow?: Callback<string>
    onMenuHide?: Callback<string>
}

export type OnMenuItemClickWithTextCallback = (menuItem: TextMenuItem, value: string) => boolean

export interface SelectionContainerEditMenuOptions {
    onCreateMenu?: OnCreateMenuCallback
    onMenuItemClick?: OnMenuItemClickWithTextCallback
    onPrepareMenu?: OnPrepareMenuCallback
}

export class ArkSelectionContainerPeer extends ArkCommonMethodPeer {
    selectionContainerAttributeSet?: SelectionContainerModifier

    constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }

    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkSelectionContainerPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = SelectionContainerExtender.selectionContainerConstructor(peerId)
        const _peer = new ArkSelectionContainerPeer(_peerPtr, peerId, 'SelectionContainer', flags)
        component?.setPeer(_peer)
        return _peer
    }

    setSelectionContainerOptionsAttribute(): void {
        SelectionContainerExtender.setSelectionContainerOptions(this.peer.ptr)
    }
    setCopyOptionAttribute(value: CopyOptions | undefined): void {
        SelectionContainerExtender.copyOption(this.peer.ptr, value)
    }
    setCaretColorAttribute(color: ResourceColor | undefined): void {
        SelectionContainerExtender.caretColor(this.peer.ptr, color)
    }
    setSelectedBackgroundColorAttribute(color: ResourceColor | undefined): void {
        SelectionContainerExtender.selectedBackgroundColor(this.peer.ptr, color)
    }
    setEnableHapticFeedbackAttribute(isEnabled: boolean | undefined): void {
        SelectionContainerExtender.enableHapticFeedback(this.peer.ptr, isEnabled)
    }
    setTextJoinStyleAttribute(style: SelectionContainerTextJoinStyle | undefined): void {
        SelectionContainerExtender.textJoinStyle(this.peer.ptr, style)
    }
    setEditMenuOptionsAttribute(options: SelectionContainerEditMenuOptions | undefined): void {
        SelectionContainerExtender.editMenuOptions(this.peer.ptr, options)
    }
    setOnTextSelectionChangeAttribute(callback: Callback<Array<string>> | undefined): void {
        SelectionContainerExtender.onTextSelectionChange(this.peer.ptr, callback)
    }
    setOnWillCopyAttribute(callback: Callback<string, boolean> | undefined): void {
        SelectionContainerExtender.onWillCopy(this.peer.ptr, callback)
    }
    setOnCopyAttribute(callback: Callback<string> | undefined): void {
        SelectionContainerExtender.onCopy(this.peer.ptr, callback)
    }
    setBindSelectionMenuAttribute(spanType: TextSpanType | undefined, content: CustomBuilder | undefined,
        responseType: TextResponseType | undefined, options: SelectionContainerMenuOptions | undefined): void {
        SelectionContainerExtender.bindSelectionMenu(this.peer.ptr, spanType, content, responseType, options)
    }
}

export interface SelectionContainerAttribute extends CommonMethod {
    copyOption(value: CopyOptions | undefined): this
    caretColor(color: ResourceColor | undefined): this
    selectedBackgroundColor(color: ResourceColor | undefined): this
    enableHapticFeedback(isEnabled: boolean | undefined): this
    textJoinStyle(style: SelectionContainerTextJoinStyle | undefined): this
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined,
        responseType: TextResponseType | undefined, options?: SelectionContainerMenuOptions | undefined): this
    editMenuOptions(editMenu: SelectionContainerEditMenuOptions | undefined): this
    onTextSelectionChange(callback: Callback<Array<string>> | undefined): this
    onWillCopy(callback: Callback<string, boolean> | undefined): this
    onCopy(callback: Callback<string> | undefined): this
    attributeModifier(modifier: AttributeModifier<SelectionContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this
    setSelectionContainerOptions(): this
}

export class ArkSelectionContainerComponent extends ArkCommonMethodComponent implements SelectionContainerAttribute {
    getPeer(): ArkSelectionContainerPeer {
        if (!this.peer) {
            throw new Error('Attribute function should be called in memo context')
        }
        return (this.peer as ArkSelectionContainerPeer)
    }

    public setSelectionContainerOptions(): this {
        if (this.checkPriority('setSelectionContainerOptions')) {
            this.getPeer()?.setSelectionContainerOptionsAttribute()
            this.applyOptionsFinish('SelectionContainerAttribute')
            return this
        }
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        if (this.checkPriority('copyOption')) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.setCopyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    public caretColor(color: ResourceColor | undefined): this {
        if (this.checkPriority('caretColor')) {
            const color_casted = color as (ResourceColor | undefined)
            this.getPeer()?.setCaretColorAttribute(color_casted)
            return this
        }
        return this
    }
    public selectedBackgroundColor(color: ResourceColor | undefined): this {
        if (this.checkPriority('selectedBackgroundColor')) {
            const color_casted = color as (ResourceColor | undefined)
            this.getPeer()?.setSelectedBackgroundColorAttribute(color_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(isEnabled: boolean | undefined): this {
        if (this.checkPriority('enableHapticFeedback')) {
            const isEnabled_casted = isEnabled as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(isEnabled_casted)
            return this
        }
        return this
    }
    public textJoinStyle(style: SelectionContainerTextJoinStyle | undefined): this {
        if (this.checkPriority('textJoinStyle')) {
            const style_casted = style as (SelectionContainerTextJoinStyle | undefined)
            this.getPeer()?.setTextJoinStyleAttribute(style_casted)
            return this
        }
        return this
    }
    public bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined,
        responseType: TextResponseType | undefined, options?: SelectionContainerMenuOptions | undefined): this {
        if (this.checkPriority('bindSelectionMenu')) {
            this.getPeer()?.setBindSelectionMenuAttribute(spanType, content, responseType, options)
            return this
        }
        return this
    }
    public editMenuOptions(editMenu: SelectionContainerEditMenuOptions | undefined): this {
        if (this.checkPriority('editMenuOptions')) {
            const editMenu_casted = editMenu as (SelectionContainerEditMenuOptions | undefined)
            this.getPeer()?.setEditMenuOptionsAttribute(editMenu_casted)
            return this
        }
        return this
    }
    public onTextSelectionChange(callback: Callback<Array<string>> | undefined): this {
        if (this.checkPriority('onTextSelectionChange')) {
            const callback_casted = callback as (Callback<Array<string>> | undefined)
            this.getPeer()?.setOnTextSelectionChangeAttribute(callback_casted)
            return this
        }
        return this
    }
    public onWillCopy(callback: Callback<string, boolean> | undefined): this {
        if (this.checkPriority('onWillCopy')) {
            const callback_casted = callback as (Callback<string, boolean> | undefined)
            this.getPeer()?.setOnWillCopyAttribute(callback_casted)
            return this
        }
        return this
    }
    public onCopy(callback: Callback<string> | undefined): this {
        if (this.checkPriority('onCopy')) {
            const callback_casted = callback as (Callback<string> | undefined)
            this.getPeer()?.setOnCopyAttribute(callback_casted)
            return this
        }
        return this
    }
    public attributeModifier(modifier: AttributeModifier<SelectionContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookSelectionContainerAttributeModifier(this, modifier)
        })
        return this
    }
    public applyAttributesFinish(): void {
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function SelectionContainerImpl(
    @memo
    style: ((attributes: SelectionContainerAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSelectionContainerComponent>((): ArkSelectionContainerComponent => {
        return new ArkSelectionContainerComponent()
    })
    NodeAttach<ArkSelectionContainerPeer>((): ArkSelectionContainerPeer => ArkSelectionContainerPeer.create(receiver), (peer: ArkSelectionContainerPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export type SelectionContainerInterface = (content_?: () => void) => SelectionContainerAttribute
