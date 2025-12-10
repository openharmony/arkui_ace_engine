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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkRichEditorPeer, RichEditorSelection, RichEditorRange, RichEditorInsertValue, RichEditorTextSpanResult, RichEditorDeleteValue, PasteEventCallback, PasteEvent, SubmitCallback, RichEditorChangeValue, CutEvent, CopyEvent, RichEditorAttribute, RichEditorSpanType, RichEditorResponseType, SelectionMenuOptions, KeyboardOptions, PlaceholderStyle } from './component/richEditor'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback as arkui_component_common_Callback } from './component/common'
import { VoidCallback, ResourceColor, Resource as arkui_component_units_Resource, ResourceStr as arkui_component_units_ResourceStr } from './component/units'
import { TextRange, TextDataDetectorConfig, OnDidChangeCallback, EditMenuOptions, KeyboardAppearance } from './component/textCommon'
import { CopyOptions, Color as arkui_component_enums_Color, BarState, ResponseType } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { EnterKeyType, SubmitEvent } from './component/textInput'
import { CustomBuilder } from './component/builder'
export class RichEditorModifier extends CommonMethodModifier implements RichEditorAttribute,AttributeModifier<RichEditorAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: RichEditorAttribute): void { }
    applyPressedAttribute(instance: RichEditorAttribute): void { }
    applyFocusedAttribute(instance: RichEditorAttribute): void { }
    applyDisabledAttribute(instance: RichEditorAttribute): void { }
    applySelectedAttribute(instance: RichEditorAttribute): void { }
    public _onReady_0_0value?: VoidCallback | undefined
    public _onSelect_0_0value?: arkui_component_common_Callback<RichEditorSelection, void> | undefined
    public _onSelectionChange_0_0value?: arkui_component_common_Callback<RichEditorRange, void> | undefined
    public _aboutToIMEInput_0_0value?: arkui_component_common_Callback<RichEditorInsertValue, boolean> | undefined
    public _onIMEInputComplete_0_0value?: arkui_component_common_Callback<RichEditorTextSpanResult, void> | undefined
    public _onDidIMEInput_0_0value?: arkui_component_common_Callback<TextRange, void> | undefined
    public _aboutToDelete_0_0value?: arkui_component_common_Callback<RichEditorDeleteValue, boolean> | undefined
    public _onDeleteComplete_0_0value?: VoidCallback | undefined
    public _copyOptions_0_0value?: CopyOptions | undefined
    public _onPaste_0_0value?: PasteEventCallback | undefined
    public _enableDataDetector_0_0value?: boolean | undefined
    public _enablePreviewText_0_0value?: boolean | undefined
    public _dataDetectorConfig_0_0value?: TextDataDetectorConfig | undefined
    public _caretColor_0_0value?: ResourceColor | undefined
    public _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    public _onEditingChange_0_0value?: arkui_component_common_Callback<boolean, void> | undefined
    public _enterKeyType_0_0value?: EnterKeyType | undefined
    public _onSubmit_0_0value?: SubmitCallback | undefined
    public _onWillChange_0_0value?: arkui_component_common_Callback<RichEditorChangeValue, boolean> | undefined
    public _onDidChange_0_0value?: OnDidChangeCallback | undefined
    public _onCut_0_0value?: arkui_component_common_Callback<CutEvent, void> | undefined
    public _onCopy_0_0value?: arkui_component_common_Callback<CopyEvent, void> | undefined
    public _editMenuOptions_0_0value?: EditMenuOptions | undefined
    public _enableKeyboardOnFocus_0_0value?: boolean | undefined
    public _enableHapticFeedback_0_0value?: boolean | undefined
    public _barState_0_0value?: BarState | undefined
    public _maxLength_0_0value?: int32 | undefined
    public _maxLines_0_0value?: int32 | undefined
    public _keyboardAppearance_0_0value?: KeyboardAppearance | undefined
    public _stopBackPress_0_0value?: boolean | undefined
    public _bindSelectionMenu_0_0value?: RichEditorSpanType | undefined
    public _bindSelectionMenu_0_1value?: CustomBuilder | undefined
    public _bindSelectionMenu_0_2value?: ResponseType | RichEditorResponseType | undefined
    public _bindSelectionMenu_0_3value?: SelectionMenuOptions | undefined
    public _customKeyboard_0_0value?: CustomBuilder | undefined
    public _customKeyboard_0_1value?: KeyboardOptions | undefined
    public _placeholder_0_0value?: arkui_component_units_ResourceStr | undefined
    public _placeholder_0_1value?: PlaceholderStyle | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkRichEditorPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkRichEditorPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnReadyAttribute((this._onReady_0_0value as VoidCallback | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnReadyAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnSelectAttribute((this._onSelect_0_0value as arkui_component_common_Callback<RichEditorSelection, void> | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnSelectAttribute((undefined as arkui_component_common_Callback<RichEditorSelection, void> | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setOnSelectionChangeAttribute((this._onSelectionChange_0_0value as arkui_component_common_Callback<RichEditorRange, void> | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setOnSelectionChangeAttribute((undefined as arkui_component_common_Callback<RichEditorRange, void> | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setAboutToIMEInputAttribute((this._aboutToIMEInput_0_0value as arkui_component_common_Callback<RichEditorInsertValue, boolean> | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setAboutToIMEInputAttribute((undefined as arkui_component_common_Callback<RichEditorInsertValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setOnIMEInputCompleteAttribute((this._onIMEInputComplete_0_0value as arkui_component_common_Callback<RichEditorTextSpanResult, void> | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setOnIMEInputCompleteAttribute((undefined as arkui_component_common_Callback<RichEditorTextSpanResult, void> | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setOnDidIMEInputAttribute((this._onDidIMEInput_0_0value as arkui_component_common_Callback<TextRange, void> | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setOnDidIMEInputAttribute((undefined as arkui_component_common_Callback<TextRange, void> | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setAboutToDeleteAttribute((this._aboutToDelete_0_0value as arkui_component_common_Callback<RichEditorDeleteValue, boolean> | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setAboutToDeleteAttribute((undefined as arkui_component_common_Callback<RichEditorDeleteValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOnDeleteCompleteAttribute((this._onDeleteComplete_0_0value as VoidCallback | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setOnDeleteCompleteAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setCopyOptionsAttribute((this._copyOptions_0_0value as CopyOptions | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setCopyOptionsAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setOnPasteAttribute((this._onPaste_0_0value as PasteEventCallback | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setOnPasteAttribute((undefined as PasteEventCallback | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setEnableDataDetectorAttribute((this._enableDataDetector_0_0value as boolean | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setEnableDataDetectorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setEnablePreviewTextAttribute((this._enablePreviewText_0_0value as boolean | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setEnablePreviewTextAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setDataDetectorConfigAttribute((this._dataDetectorConfig_0_0value as TextDataDetectorConfig | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setDataDetectorConfigAttribute((undefined as TextDataDetectorConfig | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1: {
                    peer.setCaretColorAttribute((this._caretColor_0_0value as ResourceColor | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setCaretColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1: {
                    peer.setSelectedBackgroundColorAttribute((this._selectedBackgroundColor_0_0value as ResourceColor | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setSelectedBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1: {
                    peer.setOnEditingChangeAttribute((this._onEditingChange_0_0value as arkui_component_common_Callback<boolean, void> | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setOnEditingChangeAttribute((undefined as arkui_component_common_Callback<boolean, void> | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1: {
                    peer.setEnterKeyTypeAttribute((this._enterKeyType_0_0value as EnterKeyType | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setEnterKeyTypeAttribute((undefined as EnterKeyType | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1: {
                    peer.setOnSubmitAttribute((this._onSubmit_0_0value as SubmitCallback | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setOnSubmitAttribute((undefined as SubmitCallback | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1: {
                    peer.setOnWillChangeAttribute((this._onWillChange_0_0value as arkui_component_common_Callback<RichEditorChangeValue, boolean> | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setOnWillChangeAttribute((undefined as arkui_component_common_Callback<RichEditorChangeValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1: {
                    peer.setOnDidChangeAttribute((this._onDidChange_0_0value as OnDidChangeCallback | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setOnDidChangeAttribute((undefined as OnDidChangeCallback | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkRichEditorPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1: {
                    peer.setOnCutAttribute((this._onCut_0_0value as arkui_component_common_Callback<CutEvent, void> | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setOnCutAttribute((undefined as arkui_component_common_Callback<CutEvent, void> | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1: {
                    peer.setOnCopyAttribute((this._onCopy_0_0value as arkui_component_common_Callback<CopyEvent, void> | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setOnCopyAttribute((undefined as arkui_component_common_Callback<CopyEvent, void> | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1: {
                    peer.setEditMenuOptionsAttribute((this._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setEditMenuOptionsAttribute((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1: {
                    peer.setEnableKeyboardOnFocusAttribute((this._enableKeyboardOnFocus_0_0value as boolean | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setEnableKeyboardOnFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1: {
                    peer.setBarStateAttribute((this._barState_0_0value as BarState | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setBarStateAttribute((undefined as BarState | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1: {
                    peer.setMaxLengthAttribute((this._maxLength_0_0value as int32 | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setMaxLengthAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1: {
                    peer.setMaxLinesAttribute((this._maxLines_0_0value as int32 | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setMaxLinesAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1: {
                    peer.setKeyboardAppearanceAttribute((this._keyboardAppearance_0_0value as KeyboardAppearance | undefined));
                    flagArray[28] = 2;
                    break;
                }
                case 3: {
                    flagArray[28] = 2;
                    break;
                }
                default: {
                    flagArray[28] = 0;
                    peer.setKeyboardAppearanceAttribute((undefined as KeyboardAppearance | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1: {
                    peer.setStopBackPressAttribute((this._stopBackPress_0_0value as boolean | undefined));
                    flagArray[29] = 2;
                    break;
                }
                case 3: {
                    flagArray[29] = 2;
                    break;
                }
                default: {
                    flagArray[29] = 0;
                    peer.setStopBackPressAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1: {
                    peer.setBindSelectionMenuAttribute((this._bindSelectionMenu_0_0value as RichEditorSpanType | undefined), (this._bindSelectionMenu_0_1value as CustomBuilder | undefined), (this._bindSelectionMenu_0_2value as ResponseType | RichEditorResponseType | undefined), (this._bindSelectionMenu_0_3value as SelectionMenuOptions | undefined | undefined));
                    flagArray[30] = 2;
                    break;
                }
                case 3: {
                    flagArray[30] = 2;
                    break;
                }
                default: {
                    flagArray[30] = 0;
                    peer.setBindSelectionMenuAttribute((undefined as RichEditorSpanType | undefined), (undefined as CustomBuilder | undefined), (undefined as ResponseType | RichEditorResponseType | undefined), (undefined as SelectionMenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1: {
                    peer.setCustomKeyboardAttribute((this._customKeyboard_0_0value as CustomBuilder | undefined), (this._customKeyboard_0_1value as KeyboardOptions | undefined | undefined));
                    flagArray[31] = 2;
                    break;
                }
                case 3: {
                    flagArray[31] = 2;
                    break;
                }
                default: {
                    flagArray[31] = 0;
                    peer.setCustomKeyboardAttribute((undefined as CustomBuilder | undefined), (undefined as KeyboardOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1: {
                    peer.setPlaceholderAttribute((this._placeholder_0_0value as arkui_component_units_ResourceStr | undefined), (this._placeholder_0_1value as PlaceholderStyle | undefined | undefined));
                    flagArray[32] = 2;
                    break;
                }
                case 3: {
                    flagArray[32] = 2;
                    break;
                }
                default: {
                    flagArray[32] = 0;
                    peer.setPlaceholderAttribute((undefined as arkui_component_units_ResourceStr | undefined), (undefined as PlaceholderStyle | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RichEditorModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
    }
    mergeModifier0(modifier: RichEditorModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onReady(modifier._onReady_0_0value);
                    break;
                }
                default: {
                    this.onReady((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onSelect(modifier._onSelect_0_0value);
                    break;
                }
                default: {
                    this.onSelect((undefined as arkui_component_common_Callback<RichEditorSelection, void> | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.onSelectionChange(modifier._onSelectionChange_0_0value);
                    break;
                }
                default: {
                    this.onSelectionChange((undefined as arkui_component_common_Callback<RichEditorRange, void> | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.aboutToIMEInput(modifier._aboutToIMEInput_0_0value);
                    break;
                }
                default: {
                    this.aboutToIMEInput((undefined as arkui_component_common_Callback<RichEditorInsertValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.onIMEInputComplete(modifier._onIMEInputComplete_0_0value);
                    break;
                }
                default: {
                    this.onIMEInputComplete((undefined as arkui_component_common_Callback<RichEditorTextSpanResult, void> | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.onDidIMEInput(modifier._onDidIMEInput_0_0value);
                    break;
                }
                default: {
                    this.onDidIMEInput((undefined as arkui_component_common_Callback<TextRange, void> | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.aboutToDelete(modifier._aboutToDelete_0_0value);
                    break;
                }
                default: {
                    this.aboutToDelete((undefined as arkui_component_common_Callback<RichEditorDeleteValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.onDeleteComplete(modifier._onDeleteComplete_0_0value);
                    break;
                }
                default: {
                    this.onDeleteComplete((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.copyOptions(modifier._copyOptions_0_0value);
                    break;
                }
                default: {
                    this.copyOptions((undefined as CopyOptions | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.onPaste(modifier._onPaste_0_0value);
                    break;
                }
                default: {
                    this.onPaste((undefined as PasteEventCallback | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.enableDataDetector(modifier._enableDataDetector_0_0value);
                    break;
                }
                default: {
                    this.enableDataDetector((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.enablePreviewText(modifier._enablePreviewText_0_0value);
                    break;
                }
                default: {
                    this.enablePreviewText((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.dataDetectorConfig(modifier._dataDetectorConfig_0_0value);
                    break;
                }
                default: {
                    this.dataDetectorConfig((undefined as TextDataDetectorConfig | undefined));
                }
            }
        }
        if (flagArray[13] != 0) {
            switch (flagArray[13]) {
                case 1:
                case 3: {
                    this.caretColor(modifier._caretColor_0_0value);
                    break;
                }
                default: {
                    this.caretColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[14] != 0) {
            switch (flagArray[14]) {
                case 1:
                case 3: {
                    this.selectedBackgroundColor(modifier._selectedBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.selectedBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[15] != 0) {
            switch (flagArray[15]) {
                case 1:
                case 3: {
                    this.onEditingChange(modifier._onEditingChange_0_0value);
                    break;
                }
                default: {
                    this.onEditingChange((undefined as arkui_component_common_Callback<boolean, void> | undefined));
                }
            }
        }
        if (flagArray[16] != 0) {
            switch (flagArray[16]) {
                case 1:
                case 3: {
                    this.enterKeyType(modifier._enterKeyType_0_0value);
                    break;
                }
                default: {
                    this.enterKeyType((undefined as EnterKeyType | undefined));
                }
            }
        }
        if (flagArray[17] != 0) {
            switch (flagArray[17]) {
                case 1:
                case 3: {
                    this.onSubmit(modifier._onSubmit_0_0value);
                    break;
                }
                default: {
                    this.onSubmit((undefined as SubmitCallback | undefined));
                }
            }
        }
        if (flagArray[18] != 0) {
            switch (flagArray[18]) {
                case 1:
                case 3: {
                    this.onWillChange(modifier._onWillChange_0_0value);
                    break;
                }
                default: {
                    this.onWillChange((undefined as arkui_component_common_Callback<RichEditorChangeValue, boolean> | undefined));
                }
            }
        }
        if (flagArray[19] != 0) {
            switch (flagArray[19]) {
                case 1:
                case 3: {
                    this.onDidChange(modifier._onDidChange_0_0value);
                    break;
                }
                default: {
                    this.onDidChange((undefined as OnDidChangeCallback | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: RichEditorModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0) {
            switch (flagArray[20]) {
                case 1:
                case 3: {
                    this.onCut(modifier._onCut_0_0value);
                    break;
                }
                default: {
                    this.onCut((undefined as arkui_component_common_Callback<CutEvent, void> | undefined));
                }
            }
        }
        if (flagArray[21] != 0) {
            switch (flagArray[21]) {
                case 1:
                case 3: {
                    this.onCopy(modifier._onCopy_0_0value);
                    break;
                }
                default: {
                    this.onCopy((undefined as arkui_component_common_Callback<CopyEvent, void> | undefined));
                }
            }
        }
        if (flagArray[22] != 0) {
            switch (flagArray[22]) {
                case 1:
                case 3: {
                    this.editMenuOptions(modifier._editMenuOptions_0_0value);
                    break;
                }
                default: {
                    this.editMenuOptions((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (flagArray[23] != 0) {
            switch (flagArray[23]) {
                case 1:
                case 3: {
                    this.enableKeyboardOnFocus(modifier._enableKeyboardOnFocus_0_0value);
                    break;
                }
                default: {
                    this.enableKeyboardOnFocus((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[24] != 0) {
            switch (flagArray[24]) {
                case 1:
                case 3: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[25] != 0) {
            switch (flagArray[25]) {
                case 1:
                case 3: {
                    this.barState(modifier._barState_0_0value);
                    break;
                }
                default: {
                    this.barState((undefined as BarState | undefined));
                }
            }
        }
        if (flagArray[26] != 0) {
            switch (flagArray[26]) {
                case 1:
                case 3: {
                    this.maxLength(modifier._maxLength_0_0value);
                    break;
                }
                default: {
                    this.maxLength((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[27] != 0) {
            switch (flagArray[27]) {
                case 1:
                case 3: {
                    this.maxLines(modifier._maxLines_0_0value);
                    break;
                }
                default: {
                    this.maxLines((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[28] != 0) {
            switch (flagArray[28]) {
                case 1:
                case 3: {
                    this.keyboardAppearance(modifier._keyboardAppearance_0_0value);
                    break;
                }
                default: {
                    this.keyboardAppearance((undefined as KeyboardAppearance | undefined));
                }
            }
        }
        if (flagArray[29] != 0) {
            switch (flagArray[29]) {
                case 1:
                case 3: {
                    this.stopBackPress(modifier._stopBackPress_0_0value);
                    break;
                }
                default: {
                    this.stopBackPress((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[30] != 0) {
            switch (flagArray[30]) {
                case 1:
                case 3: {
                    this.bindSelectionMenu(modifier._bindSelectionMenu_0_0value, modifier._bindSelectionMenu_0_1value, modifier._bindSelectionMenu_0_2value, modifier._bindSelectionMenu_0_3value);
                    break;
                }
                default: {
                    this.bindSelectionMenu((undefined as RichEditorSpanType | undefined), (undefined as CustomBuilder | undefined), (undefined as ResponseType | RichEditorResponseType | undefined), (undefined as SelectionMenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[31] != 0) {
            switch (flagArray[31]) {
                case 1:
                case 3: {
                    this.customKeyboard(modifier._customKeyboard_0_0value, modifier._customKeyboard_0_1value);
                    break;
                }
                default: {
                    this.customKeyboard((undefined as CustomBuilder | undefined), (undefined as KeyboardOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[32] != 0) {
            switch (flagArray[32]) {
                case 1:
                case 3: {
                    this.placeholder(modifier._placeholder_0_0value, modifier._placeholder_0_1value);
                    break;
                }
                default: {
                    this.placeholder((undefined as arkui_component_units_ResourceStr | undefined), (undefined as PlaceholderStyle | undefined | undefined));
                }
            }
        }
    }
    onReady(value: VoidCallback | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onReady_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    onSelect(value: arkui_component_common_Callback<RichEditorSelection, void> | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._onSelect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    onSelectionChange(value: arkui_component_common_Callback<RichEditorRange, void> | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._onSelectionChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    aboutToIMEInput(value: arkui_component_common_Callback<RichEditorInsertValue, boolean> | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._aboutToIMEInput_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    onIMEInputComplete(value: arkui_component_common_Callback<RichEditorTextSpanResult, void> | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._onIMEInputComplete_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    onDidIMEInput(value: arkui_component_common_Callback<TextRange, void> | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._onDidIMEInput_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    aboutToDelete(value: arkui_component_common_Callback<RichEditorDeleteValue, boolean> | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._aboutToDelete_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    onDeleteComplete(value: VoidCallback | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._onDeleteComplete_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    copyOptions(value: CopyOptions | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._copyOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    onPaste(value: PasteEventCallback | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._onPaste_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    enableDataDetector(value: boolean | undefined): this {
        if (((this._flagArray[10]) == (0)) || ((this._enableDataDetector_0_0value) !== (value))) {
            this._flagArray[10] = 1
            this._enableDataDetector_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    enablePreviewText(value: boolean | undefined): this {
        if (((this._flagArray[11]) == (0)) || ((this._enablePreviewText_0_0value) !== (value))) {
            this._flagArray[11] = 1
            this._enablePreviewText_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._dataDetectorConfig_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    caretColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true)) {
            this._flagArray[13] = 1
            this._caretColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[13] = 3
        }
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true)) {
            this._flagArray[14] = 1
            this._selectedBackgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[14] = 3
        }
        return this
    }
    onEditingChange(value: arkui_component_common_Callback<boolean, void> | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true)) {
            this._flagArray[15] = 1
            this._onEditingChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[15] = 3
        }
        return this
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true)) {
            this._flagArray[16] = 1
            this._enterKeyType_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[16] = 3
        }
        return this
    }
    onSubmit(value: SubmitCallback | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true)) {
            this._flagArray[17] = 1
            this._onSubmit_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[17] = 3
        }
        return this
    }
    onWillChange(value: arkui_component_common_Callback<RichEditorChangeValue, boolean> | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true)) {
            this._flagArray[18] = 1
            this._onWillChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[18] = 3
        }
        return this
    }
    onDidChange(value: OnDidChangeCallback | undefined): this {
        if (((this._flagArray[19]) == (0)) || (true)) {
            this._flagArray[19] = 1
            this._onDidChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[19] = 3
        }
        return this
    }
    onCut(value: arkui_component_common_Callback<CutEvent, void> | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true)) {
            this._flagArray[20] = 1
            this._onCut_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[20] = 3
        }
        return this
    }
    onCopy(value: arkui_component_common_Callback<CopyEvent, void> | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true)) {
            this._flagArray[21] = 1
            this._onCopy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[21] = 3
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true)) {
            this._flagArray[22] = 1
            this._editMenuOptions_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[22] = 3
        }
        return this
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        if (((this._flagArray[23]) == (0)) || ((this._enableKeyboardOnFocus_0_0value) !== (value))) {
            this._flagArray[23] = 1
            this._enableKeyboardOnFocus_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[23] = 3
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._flagArray[24]) == (0)) || ((this._enableHapticFeedback_0_0value) !== (value))) {
            this._flagArray[24] = 1
            this._enableHapticFeedback_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[24] = 3
        }
        return this
    }
    barState(value: BarState | undefined): this {
        if (((this._flagArray[25]) == (0)) || (true)) {
            this._flagArray[25] = 1
            this._barState_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[25] = 3
        }
        return this
    }
    maxLength(value: int32 | undefined): this {
        if (((this._flagArray[26]) == (0)) || ((this._maxLength_0_0value) !== (value))) {
            this._flagArray[26] = 1
            this._maxLength_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[26] = 3
        }
        return this
    }
    maxLines(value: int32 | undefined): this {
        if (((this._flagArray[27]) == (0)) || ((this._maxLines_0_0value) !== (value))) {
            this._flagArray[27] = 1
            this._maxLines_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[27] = 3
        }
        return this
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (((this._flagArray[28]) == (0)) || (true)) {
            this._flagArray[28] = 1
            this._keyboardAppearance_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[28] = 3
        }
        return this
    }
    stopBackPress(value: boolean | undefined): this {
        if (((this._flagArray[29]) == (0)) || ((this._stopBackPress_0_0value) !== (value))) {
            this._flagArray[29] = 1
            this._stopBackPress_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[29] = 3
        }
        return this
    }
    bindSelectionMenu(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: ResponseType | RichEditorResponseType | undefined, options?: SelectionMenuOptions): this {
        if (((this._flagArray[30]) == (0)) || (true) || (true) || (true) || (true)) {
            this._flagArray[30] = 1
            this._bindSelectionMenu_0_0value = spanType
            this._bindSelectionMenu_0_1value = content
            this._bindSelectionMenu_0_2value = responseType
            this._bindSelectionMenu_0_3value = options
            this._state.fireChange()
        } else {
            this._flagArray[30] = 3
        }
        return this
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (((this._flagArray[31]) == (0)) || (true) || (true)) {
            this._flagArray[31] = 1
            this._customKeyboard_0_0value = value
            this._customKeyboard_0_1value = options
            this._state.fireChange()
        } else {
            this._flagArray[31] = 3
        }
        return this
    }
    placeholder(value: arkui_component_units_ResourceStr | undefined, style?: PlaceholderStyle): this {
        if (((this._flagArray[32]) == (0)) || (true) || (true)) {
            this._flagArray[32] = 1
            this._placeholder_0_0value = value
            this._placeholder_0_1value = style
            this._state.fireChange()
        } else {
            this._flagArray[32] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RichEditorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
