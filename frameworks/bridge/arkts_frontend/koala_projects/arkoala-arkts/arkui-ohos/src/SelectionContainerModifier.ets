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

import { CommonMethod, Callback } from './component/common'
import { ResourceColor as arkui_component_units_ResourceColor } from 'arkui/component/units'
import { CopyOptions } from 'arkui/component/enums'
import { CustomBuilder } from 'arkui/component/builder'
import { TextSpanType, TextResponseType } from 'arkui/component/text'
import {
    ArkSelectionContainerPeer,
    SelectionContainerAttribute,
    SelectionContainerTextJoinStyle,
    SelectionContainerMenuOptions,
    SelectionContainerEditMenuOptions,
} from '@ohos.arkui.components.SelectionContainer'
import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'

export class SelectionContainerModifier extends CommonMethodModifier implements
    SelectionContainerAttribute, AttributeModifier<SelectionContainerAttribute> {
    _SelectionContainer_addr: ArrayBuffer = new ArrayBuffer(4096)
    _SelectionContainer_flagArray: Uint8Array = new Uint8Array(this._SelectionContainer_addr)

    constructor() {
        super()
        this._SelectionContainer_flagArray.fill(0)
    }

    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SelectionContainerAttribute): void { }
    applyPressedAttribute(instance: SelectionContainerAttribute): void { }
    applyFocusedAttribute(instance: SelectionContainerAttribute): void { }
    applyDisabledAttribute(instance: SelectionContainerAttribute): void { }
    applySelectedAttribute(instance: SelectionContainerAttribute): void { }
    applyHoveredAttribute(instance: SelectionContainerAttribute): void { }

    public _SelectionContainer_copyOption_0_0value?: CopyOptions | undefined
    public _SelectionContainer_caretColor_0_0value?: arkui_component_units_ResourceColor | undefined
    public _SelectionContainer_selectedBackgroundColor_0_0value?: arkui_component_units_ResourceColor | undefined
    public _SelectionContainer_enableHapticFeedback_0_0value?: boolean | undefined
    public _SelectionContainer_textJoinStyle_0_0value?: SelectionContainerTextJoinStyle | undefined
    public _SelectionContainer_editMenuOptions_0_0value?: SelectionContainerEditMenuOptions | undefined
    public _SelectionContainer_onTextSelectionChange_0_0value?: Callback<Array<string>> | undefined
    public _SelectionContainer_onWillCopy_0_0value?: Callback<string, boolean> | undefined
    public _SelectionContainer_onCopy_0_0value?: Callback<string> | undefined
    public _SelectionContainer_bindSelectionMenu_0_0spanType?: TextSpanType | undefined
    public _SelectionContainer_bindSelectionMenu_0_0content?: CustomBuilder | undefined
    public _SelectionContainer_bindSelectionMenu_0_0responseType?: TextResponseType | undefined
    public _SelectionContainer_bindSelectionMenu_0_0options?: SelectionContainerMenuOptions | undefined

    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkSelectionContainerPeer
        const flagArray = this._SelectionContainer_flagArray
        this.applyModifierPatch0(peer, flagArray)
    }

    applyModifierPatch0(peer: ArkSelectionContainerPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setCopyOptionAttribute(this._SelectionContainer_copyOption_0_0value as CopyOptions | undefined)
                    flagArray[0] = 2
                    break
                }
                case 3: {
                    flagArray[0] = 2
                    break
                }
                default: {
                    flagArray[0] = 0
                    peer.setCopyOptionAttribute(undefined as CopyOptions | undefined)
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setCaretColorAttribute(this._SelectionContainer_caretColor_0_0value as arkui_component_units_ResourceColor | undefined)
                    flagArray[1] = 2
                    break
                }
                case 3: {
                    flagArray[1] = 2
                    break
                }
                default: {
                    flagArray[1] = 0
                    peer.setCaretColorAttribute(undefined as arkui_component_units_ResourceColor | undefined)
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setSelectedBackgroundColorAttribute(this._SelectionContainer_selectedBackgroundColor_0_0value as arkui_component_units_ResourceColor | undefined)
                    flagArray[2] = 2
                    break
                }
                case 3: {
                    flagArray[2] = 2
                    break
                }
                default: {
                    flagArray[2] = 0
                    peer.setSelectedBackgroundColorAttribute(undefined as arkui_component_units_ResourceColor | undefined)
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute(this._SelectionContainer_enableHapticFeedback_0_0value as boolean | undefined)
                    flagArray[3] = 2
                    break
                }
                case 3: {
                    flagArray[3] = 2
                    break
                }
                default: {
                    flagArray[3] = 0
                    peer.setEnableHapticFeedbackAttribute(undefined as boolean | undefined)
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setTextJoinStyleAttribute(this._SelectionContainer_textJoinStyle_0_0value as SelectionContainerTextJoinStyle | undefined)
                    flagArray[4] = 2
                    break
                }
                case 3: {
                    flagArray[4] = 2
                    break
                }
                default: {
                    flagArray[4] = 0
                    peer.setTextJoinStyleAttribute(undefined as SelectionContainerTextJoinStyle | undefined)
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setEditMenuOptionsAttribute(this._SelectionContainer_editMenuOptions_0_0value as SelectionContainerEditMenuOptions | undefined)
                    flagArray[5] = 2
                    break
                }
                case 3: {
                    flagArray[5] = 2
                    break
                }
                default: {
                    flagArray[5] = 0
                    peer.setEditMenuOptionsAttribute(undefined as SelectionContainerEditMenuOptions | undefined)
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setOnTextSelectionChangeAttribute(this._SelectionContainer_onTextSelectionChange_0_0value as Callback<Array<string>> | undefined)
                    flagArray[6] = 2
                    break
                }
                case 3: {
                    flagArray[6] = 2
                    break
                }
                default: {
                    flagArray[6] = 0
                    peer.setOnTextSelectionChangeAttribute(undefined as Callback<Array<string>> | undefined)
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOnWillCopyAttribute(this._SelectionContainer_onWillCopy_0_0value as Callback<string, boolean> | undefined)
                    flagArray[7] = 2
                    break
                }
                case 3: {
                    flagArray[7] = 2
                    break
                }
                default: {
                    flagArray[7] = 0
                    peer.setOnWillCopyAttribute(undefined as Callback<string, boolean> | undefined)
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnCopyAttribute(this._SelectionContainer_onCopy_0_0value as Callback<string> | undefined)
                    flagArray[8] = 2
                    break
                }
                case 3: {
                    flagArray[8] = 2
                    break
                }
                default: {
                    flagArray[8] = 0
                    peer.setOnCopyAttribute(undefined as Callback<string> | undefined)
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setBindSelectionMenuAttribute(
                        this._SelectionContainer_bindSelectionMenu_0_0spanType as TextSpanType | undefined,
                        this._SelectionContainer_bindSelectionMenu_0_0content as CustomBuilder | undefined,
                        this._SelectionContainer_bindSelectionMenu_0_0responseType as TextResponseType | undefined,
                        this._SelectionContainer_bindSelectionMenu_0_0options as SelectionContainerMenuOptions | undefined)
                    flagArray[9] = 2
                    break
                }
                case 3: {
                    flagArray[9] = 2
                    break
                }
                default: {
                    flagArray[9] = 0
                    peer.setBindSelectionMenuAttribute(undefined as TextSpanType | undefined,
                        undefined as CustomBuilder | undefined,
                        undefined as TextResponseType | undefined,
                        undefined as SelectionContainerMenuOptions | undefined)
                }
            }
        }
    }

    mergeModifier(modifier: SelectionContainerModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state
        const flagArray = modifier._SelectionContainer_flagArray
        this.mergeModifier0(modifier, flagArray)
    }

    mergeModifier0(modifier: SelectionContainerModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.copyOption(modifier._SelectionContainer_copyOption_0_0value as CopyOptions | undefined)
                    break
                }
                default: {
                    this.copyOption(undefined as CopyOptions | undefined)
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.caretColor(modifier._SelectionContainer_caretColor_0_0value as arkui_component_units_ResourceColor | undefined)
                    break
                }
                default: {
                    this.caretColor(undefined as arkui_component_units_ResourceColor | undefined)
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.selectedBackgroundColor(modifier._SelectionContainer_selectedBackgroundColor_0_0value as arkui_component_units_ResourceColor | undefined)
                    break
                }
                default: {
                    this.selectedBackgroundColor(undefined as arkui_component_units_ResourceColor | undefined)
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.enableHapticFeedback(modifier._SelectionContainer_enableHapticFeedback_0_0value as boolean | undefined)
                    break
                }
                default: {
                    this.enableHapticFeedback(undefined as boolean | undefined)
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.textJoinStyle(modifier._SelectionContainer_textJoinStyle_0_0value as SelectionContainerTextJoinStyle | undefined)
                    break
                }
                default: {
                    this.textJoinStyle(undefined as SelectionContainerTextJoinStyle | undefined)
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.editMenuOptions(modifier._SelectionContainer_editMenuOptions_0_0value as SelectionContainerEditMenuOptions | undefined)
                    break
                }
                default: {
                    this.editMenuOptions(undefined as SelectionContainerEditMenuOptions | undefined)
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.onTextSelectionChange(modifier._SelectionContainer_onTextSelectionChange_0_0value as Callback<Array<string>> | undefined)
                    break
                }
                default: {
                    this.onTextSelectionChange(undefined as Callback<Array<string>> | undefined)
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.onWillCopy(modifier._SelectionContainer_onWillCopy_0_0value as Callback<string, boolean> | undefined)
                    break
                }
                default: {
                    this.onWillCopy(undefined as Callback<string, boolean> | undefined)
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.onCopy(modifier._SelectionContainer_onCopy_0_0value as Callback<string> | undefined)
                    break
                }
                default: {
                    this.onCopy(undefined as Callback<string> | undefined)
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.bindSelectionMenu(
                        modifier._SelectionContainer_bindSelectionMenu_0_0spanType as TextSpanType | undefined,
                        modifier._SelectionContainer_bindSelectionMenu_0_0content as CustomBuilder | undefined,
                        modifier._SelectionContainer_bindSelectionMenu_0_0responseType as TextResponseType | undefined,
                        modifier._SelectionContainer_bindSelectionMenu_0_0options as SelectionContainerMenuOptions | undefined)
                    break
                }
                default: {
                    this.bindSelectionMenu(undefined as TextSpanType | undefined,
                        undefined as CustomBuilder | undefined,
                        undefined as TextResponseType | undefined,
                        undefined as SelectionContainerMenuOptions | undefined)
                }
            }
        }
    }

    setSelectionContainerOptions(): this {
        return this
    }

    copyOption(value: CopyOptions | undefined): this {
        if ((this._SelectionContainer_flagArray[0] == 0) || true) {
            this._SelectionContainer_flagArray[0] = 1
            this._SelectionContainer_copyOption_0_0value = value
            this._state.fireChange()
        } else {
            this._SelectionContainer_flagArray[0] = 3
        }
        return this
    }

    caretColor(color: arkui_component_units_ResourceColor | undefined): this {
        if ((this._SelectionContainer_flagArray[1] == 0) || true) {
            this._SelectionContainer_flagArray[1] = 1
            this._SelectionContainer_caretColor_0_0value = color
            this._state.fireChange()
        } else {
            this._SelectionContainer_flagArray[1] = 3
        }
        return this
    }

    selectedBackgroundColor(color: arkui_component_units_ResourceColor | undefined): this {
        if ((this._SelectionContainer_flagArray[2] == 0) || true) {
            this._SelectionContainer_flagArray[2] = 1
            this._SelectionContainer_selectedBackgroundColor_0_0value = color
            this._state.fireChange()
        } else {
            this._SelectionContainer_flagArray[2] = 3
        }
        return this
    }

    enableHapticFeedback(isEnabled: boolean | undefined): this {
        if ((this._SelectionContainer_flagArray[3] == 0) || true) {
            this._SelectionContainer_flagArray[3] = 1
            this._SelectionContainer_enableHapticFeedback_0_0value = isEnabled
            this._state.fireChange()
        } else {
            this._SelectionContainer_flagArray[3] = 3
        }
        return this
    }

    textJoinStyle(style: SelectionContainerTextJoinStyle | undefined): this {
        if ((this._SelectionContainer_flagArray[4] == 0) || true) {
            this._SelectionContainer_flagArray[4] = 1
            this._SelectionContainer_textJoinStyle_0_0value = style
            this._state.fireChange()
        } else {
            this._SelectionContainer_flagArray[4] = 3
        }
        return this
    }

    editMenuOptions(editMenu: SelectionContainerEditMenuOptions | undefined): this {
        if ((this._SelectionContainer_flagArray[5] == 0) || true) {
            this._SelectionContainer_flagArray[5] = 1
            this._SelectionContainer_editMenuOptions_0_0value = editMenu
            this._state.fireChange()
        } else {
            this._SelectionContainer_flagArray[5] = 3
        }
        return this
    }

    onTextSelectionChange(callback: Callback<Array<string>> | undefined): this {
        if ((this._SelectionContainer_flagArray[6] == 0) || true) {
            this._SelectionContainer_flagArray[6] = 1
            this._SelectionContainer_onTextSelectionChange_0_0value = callback
            this._state.fireChange()
        } else {
            this._SelectionContainer_flagArray[6] = 3
        }
        return this
    }

    onWillCopy(callback: Callback<string, boolean> | undefined): this {
        if ((this._SelectionContainer_flagArray[7] == 0) || true) {
            this._SelectionContainer_flagArray[7] = 1
            this._SelectionContainer_onWillCopy_0_0value = callback
            this._state.fireChange()
        } else {
            this._SelectionContainer_flagArray[7] = 3
        }
        return this
    }

    onCopy(callback: Callback<string> | undefined): this {
        if ((this._SelectionContainer_flagArray[8] == 0) || true) {
            this._SelectionContainer_flagArray[8] = 1
            this._SelectionContainer_onCopy_0_0value = callback
            this._state.fireChange()
        } else {
            this._SelectionContainer_flagArray[8] = 3
        }
        return this
    }

    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined,
        responseType: TextResponseType | undefined, options?: SelectionContainerMenuOptions | undefined): this {
        if ((this._SelectionContainer_flagArray[9] == 0) || true) {
            this._SelectionContainer_flagArray[9] = 1
            this._SelectionContainer_bindSelectionMenu_0_0spanType = spanType
            this._SelectionContainer_bindSelectionMenu_0_0content = content
            this._SelectionContainer_bindSelectionMenu_0_0responseType = responseType
            this._SelectionContainer_bindSelectionMenu_0_0options = options
            this._state.fireChange()
        } else {
            this._SelectionContainer_flagArray[9] = 3
        }
        return this
    }

    public attributeModifier(
        modifier: AttributeModifier<SelectionContainerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
}
