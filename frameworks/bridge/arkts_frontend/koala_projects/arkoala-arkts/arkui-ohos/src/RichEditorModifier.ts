/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { AttributeModifier, CustomBuilder } from './component/common'
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier';
import { VoidCallback, ResourceColor, ResourceStr } from "./component/units"
import { RichEditorSelection, RichEditorRange, RichEditorInsertValue, RichEditorTextSpanResult, RichEditorDeleteValue,
    PasteEventCallback, PasteEvent, SubmitCallback, RichEditorChangeValue, CutEvent, CopyEvent, RichEditorAttribute,
    RichEditorSpanType, RichEditorResponseType, SelectionMenuOptions, KeyboardOptions, PlaceholderStyle,
    ArkRichEditorPeer } from "./component/richEditor"
import { TextRange, TextDataDetectorConfig, OnDidChangeCallback, EditMenuOptions, KeyboardAppearance } from "./component/textCommon"
import { CopyOptions, Color, BarState, ResponseType } from "./component/enums"
import { EnterKeyType, SubmitEvent } from "./component/textInput"
import { PeerNode } from "./PeerNode";


export class RichEditorModifier extends CommonMethodModifier implements RichEditorAttribute,AttributeModifier<RichEditorAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: RichEditorAttribute): void { }
    applyPressedAttribute(instance: RichEditorAttribute): void { }
    applyFocusedAttribute(instance: RichEditorAttribute): void { }
    applyDisabledAttribute(instance: RichEditorAttribute): void { }
    applySelectedAttribute(instance: RichEditorAttribute): void { }
    _onReady_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReady_0_0value?: VoidCallback | undefined
    _onSelect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelect_0_0value?: ((value0: RichEditorSelection) => void) | undefined
    _onSelectionChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelectionChange_0_0value?: ((value0: RichEditorRange) => void) | undefined
    _aboutToIMEInput_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _aboutToIMEInput_0_0value?: ((value0: RichEditorInsertValue) => boolean) | undefined
    _onIMEInputComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onIMEInputComplete_0_0value?: ((value0: RichEditorTextSpanResult) => void) | undefined
    _onDidIMEInput_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidIMEInput_0_0value?: ((value0: TextRange) => void) | undefined
    _aboutToDelete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _aboutToDelete_0_0value?: ((value0: RichEditorDeleteValue) => boolean) | undefined
    _onDeleteComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDeleteComplete_0_0value?: VoidCallback | undefined
    _copyOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _copyOptions_0_0value?: CopyOptions | undefined
    _onPaste_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPaste_0_0value?: PasteEventCallback | undefined
    _enableDataDetector_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableDataDetector_0_0value?: boolean | undefined
    _enablePreviewText_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enablePreviewText_0_0value?: boolean | undefined
    _dataDetectorConfig_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dataDetectorConfig_0_0value?: TextDataDetectorConfig | undefined
    _caretColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _caretColor_0_0value?: ResourceColor | undefined
    _selectedBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    _onEditingChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onEditingChange_0_0value?: ((value0: boolean) => void) | undefined
    _enterKeyType_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enterKeyType_0_0value?: EnterKeyType | undefined
    _onSubmit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSubmit_0_0value?: SubmitCallback | undefined
    _onWillChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillChange_0_0value?: ((value0: RichEditorChangeValue) => boolean) | undefined
    _onDidChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidChange_0_0value?: OnDidChangeCallback | undefined
    _onCut_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCut_0_0value?: ((value0: CutEvent) => void) | undefined
    _onCopy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCopy_0_0value?: ((value0: CopyEvent) => void) | undefined
    _editMenuOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _editMenuOptions_0_0value?: EditMenuOptions | undefined
    _enableKeyboardOnFocus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableKeyboardOnFocus_0_0value?: boolean | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _barState_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barState_0_0value?: BarState | undefined
    _maxLength_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxLength_0_0value?: number | undefined
    _maxLines_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxLines_0_0value?: number | undefined
    _keyboardAppearance_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _keyboardAppearance_0_0value?: KeyboardAppearance | undefined
    _stopBackPress_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stopBackPress_0_0value?: boolean | undefined
    _bindSelectionMenu_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindSelectionMenu_0_0value?: RichEditorSpanType | undefined
    _bindSelectionMenu_0_1value?: CustomBuilder | undefined
    _bindSelectionMenu_0_2value?: ResponseType | RichEditorResponseType | undefined
    _bindSelectionMenu_0_3value?: SelectionMenuOptions | undefined
    _customKeyboard_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customKeyboard_0_0value?: CustomBuilder | undefined
    _customKeyboard_0_1value?: KeyboardOptions | undefined
    _placeholder_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _placeholder_0_0value?: ResourceStr | undefined
    _placeholder_0_1value?: PlaceholderStyle | undefined
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peer: ArkRichEditorPeer = value as ArkRichEditorPeer
        if (this._onReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onReadyAttribute((this._onReady_0_0value as VoidCallback | undefined));
                    this._onReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReady_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onReadyAttribute(undefined);
                }
            }
        }
        if (this._onSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onSelectAttribute((this._onSelect_0_0value as ((value0: RichEditorSelection) => void) | undefined));
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onSelectAttribute(undefined);
                }
            }
        }
        if (this._onSelectionChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSelectionChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onSelectionChangeAttribute((this._onSelectionChange_0_0value as ((value0: RichEditorRange) => void) | undefined));
                    this._onSelectionChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelectionChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelectionChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onSelectionChangeAttribute(undefined);
                }
            }
        }
        if (this._aboutToIMEInput_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._aboutToIMEInput_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.aboutToIMEInputAttribute((this._aboutToIMEInput_0_0value as ((value0: RichEditorInsertValue) => boolean) | undefined));
                    this._aboutToIMEInput_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._aboutToIMEInput_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._aboutToIMEInput_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.aboutToIMEInputAttribute(undefined);
                }
            }
        }
        if (this._onIMEInputComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onIMEInputComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onIMEInputCompleteAttribute((this._onIMEInputComplete_0_0value as ((value0: RichEditorTextSpanResult) => void) | undefined));
                    this._onIMEInputComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onIMEInputComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onIMEInputComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onIMEInputCompleteAttribute(undefined);
                }
            }
        }
        if (this._onDidIMEInput_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidIMEInput_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onDidIMEInputAttribute((this._onDidIMEInput_0_0value as ((value0: TextRange) => void) | undefined));
                    this._onDidIMEInput_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidIMEInput_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidIMEInput_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onDidIMEInputAttribute(undefined);
                }
            }
        }
        if (this._aboutToDelete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._aboutToDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.aboutToDeleteAttribute((this._aboutToDelete_0_0value as ((value0: RichEditorDeleteValue) => boolean) | undefined));
                    this._aboutToDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._aboutToDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._aboutToDelete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.aboutToDeleteAttribute(undefined);
                }
            }
        }
        if (this._onDeleteComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDeleteComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onDeleteCompleteAttribute((this._onDeleteComplete_0_0value as VoidCallback | undefined));
                    this._onDeleteComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDeleteComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDeleteComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onDeleteCompleteAttribute(undefined);
                }
            }
        }
        if (this._copyOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._copyOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.copyOptionsAttribute((this._copyOptions_0_0value as CopyOptions | undefined));
                    this._copyOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._copyOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._copyOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.copyOptionsAttribute(undefined);
                }
            }
        }
        if (this._onPaste_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPaste_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onPasteAttribute((this._onPaste_0_0value as PasteEventCallback | undefined));
                    this._onPaste_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPaste_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPaste_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onPasteAttribute(undefined);
                }
            }
        }
        if (this._enableDataDetector_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableDataDetector_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableDataDetectorAttribute((this._enableDataDetector_0_0value as boolean | undefined));
                    this._enableDataDetector_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableDataDetector_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableDataDetector_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableDataDetectorAttribute(undefined);
                }
            }
        }
        if (this._enablePreviewText_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enablePreviewText_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enablePreviewTextAttribute((this._enablePreviewText_0_0value as boolean | undefined));
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enablePreviewTextAttribute(undefined);
                }
            }
        }
        if (this._dataDetectorConfig_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dataDetectorConfig_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.dataDetectorConfigAttribute((this._dataDetectorConfig_0_0value as TextDataDetectorConfig | undefined));
                    this._dataDetectorConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dataDetectorConfig_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dataDetectorConfig_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.dataDetectorConfigAttribute(undefined);
                }
            }
        }
        if (this._caretColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._caretColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.caretColorAttribute((this._caretColor_0_0value as ResourceColor | undefined));
                    this._caretColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._caretColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._caretColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.caretColorAttribute(undefined);
                }
            }
        }
        if (this._selectedBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.selectedBackgroundColorAttribute((this._selectedBackgroundColor_0_0value as ResourceColor | undefined));
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.selectedBackgroundColorAttribute(undefined);
                }
            }
        }
        if (this._onEditingChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onEditingChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onEditingChangeAttribute((this._onEditingChange_0_0value as ((value0: boolean) => void) | undefined));
                    this._onEditingChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onEditingChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onEditingChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onEditingChangeAttribute(undefined);
                }
            }
        }
        if (this._enterKeyType_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enterKeyType_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enterKeyTypeAttribute((this._enterKeyType_0_0value as EnterKeyType | undefined));
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enterKeyTypeAttribute(undefined);
                }
            }
        }
        if (this._onSubmit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSubmit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onSubmitAttribute((this._onSubmit_0_0value as SubmitCallback | undefined));
                    this._onSubmit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSubmit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSubmit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onSubmitAttribute(undefined);
                }
            }
        }
        if (this._onWillChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onWillChangeAttribute((this._onWillChange_0_0value as ((value0: RichEditorChangeValue) => boolean) | undefined));
                    this._onWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onWillChangeAttribute(undefined);
                }
            }
        }
        if (this._onDidChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onDidChangeAttribute((this._onDidChange_0_0value as OnDidChangeCallback | undefined));
                    this._onDidChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onDidChangeAttribute(undefined);
                }
            }
        }
        if (this._onCut_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onCut_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onCutAttribute((this._onCut_0_0value as ((value0: CutEvent) => void) | undefined));
                    this._onCut_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCut_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCut_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onCutAttribute(undefined);
                }
            }
        }
        if (this._onCopy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onCopy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onCopyAttribute((this._onCopy_0_0value as ((value0: CopyEvent) => void) | undefined));
                    this._onCopy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCopy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCopy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onCopyAttribute(undefined);
                }
            }
        }
        if (this._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.editMenuOptionsAttribute((this._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.editMenuOptionsAttribute(undefined);
                }
            }
        }
        if (this._enableKeyboardOnFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableKeyboardOnFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableKeyboardOnFocusAttribute((this._enableKeyboardOnFocus_0_0value as boolean | undefined));
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableKeyboardOnFocusAttribute(undefined);
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableHapticFeedbackAttribute(undefined);
                }
            }
        }
        if (this._barState_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barState_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.barStateAttribute((this._barState_0_0value as BarState | undefined));
                    this._barState_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barState_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barState_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.barStateAttribute(undefined);
                }
            }
        }
        if (this._maxLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxLengthAttribute((this._maxLength_0_0value as number | undefined));
                    this._maxLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxLength_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxLengthAttribute(undefined);
                }
            }
        }
        if (this._maxLines_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxLines_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.maxLinesAttribute((this._maxLines_0_0value as number | undefined));
                    this._maxLines_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxLines_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxLines_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.maxLinesAttribute(undefined);
                }
            }
        }
        if (this._keyboardAppearance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._keyboardAppearance_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.keyboardAppearanceAttribute((this._keyboardAppearance_0_0value as KeyboardAppearance | undefined));
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.keyboardAppearanceAttribute(undefined);
                }
            }
        }
        if (this._stopBackPress_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stopBackPress_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.stopBackPressAttribute((this._stopBackPress_0_0value as boolean | undefined));
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.stopBackPressAttribute(undefined);
                }
            }
        }
        if (this._bindSelectionMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindSelectionMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.bindSelectionMenuAttribute((this._bindSelectionMenu_0_0value as RichEditorSpanType | undefined), (this._bindSelectionMenu_0_1value as CustomBuilder | undefined), (this._bindSelectionMenu_0_2value as ResponseType | RichEditorResponseType | undefined), (this._bindSelectionMenu_0_3value as SelectionMenuOptions | undefined));
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.bindSelectionMenuAttribute(undefined, undefined, undefined, undefined);
                }
            }
        }
        if (this._customKeyboard_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customKeyboard_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.customKeyboardAttribute((this._customKeyboard_0_0value as CustomBuilder | undefined), (this._customKeyboard_0_1value as KeyboardOptions | undefined));
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.customKeyboardAttribute(undefined, undefined);
                }
            }
        }
        if (this._placeholder_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._placeholder_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.placeholderAttribute((this._placeholder_0_0value as ResourceStr | undefined), (this._placeholder_0_1value as PlaceholderStyle | undefined));
                    this._placeholder_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._placeholder_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._placeholder_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.placeholderAttribute(undefined, undefined);
                }
            }
        }
    }
    mergeModifier(modifier: RichEditorModifier): void {
        super.mergeModifier(modifier)
        if (modifier._onReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReady(modifier._onReady_0_0value);
                    break;
                }
                default: {
                    this.onReady((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelect(modifier._onSelect_0_0value);
                    break;
                }
                default: {
                    this.onSelect((undefined as ((value0: RichEditorSelection) => void) | undefined));
                }
            }
        }
        if (modifier._onSelectionChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSelectionChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelectionChange(modifier._onSelectionChange_0_0value);
                    break;
                }
                default: {
                    this.onSelectionChange((undefined as ((value0: RichEditorRange) => void) | undefined));
                }
            }
        }
        if (modifier._aboutToIMEInput_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._aboutToIMEInput_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.aboutToIMEInput(modifier._aboutToIMEInput_0_0value);
                    break;
                }
                default: {
                    this.aboutToIMEInput((undefined as ((value0: RichEditorInsertValue) => boolean) | undefined));
                }
            }
        }
        if (modifier._onIMEInputComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onIMEInputComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onIMEInputComplete(modifier._onIMEInputComplete_0_0value);
                    break;
                }
                default: {
                    this.onIMEInputComplete((undefined as ((value0: RichEditorTextSpanResult) => void) | undefined));
                }
            }
        }
        if (modifier._onDidIMEInput_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidIMEInput_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidIMEInput(modifier._onDidIMEInput_0_0value);
                    break;
                }
                default: {
                    this.onDidIMEInput((undefined as ((value0: TextRange) => void) | undefined));
                }
            }
        }
        if (modifier._aboutToDelete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._aboutToDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.aboutToDelete(modifier._aboutToDelete_0_0value);
                    break;
                }
                default: {
                    this.aboutToDelete((undefined as ((value0: RichEditorDeleteValue) => boolean) | undefined));
                }
            }
        }
        if (modifier._onDeleteComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDeleteComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDeleteComplete(modifier._onDeleteComplete_0_0value);
                    break;
                }
                default: {
                    this.onDeleteComplete((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._copyOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._copyOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.copyOptions(modifier._copyOptions_0_0value);
                    break;
                }
                default: {
                    this.copyOptions((undefined as CopyOptions | undefined));
                }
            }
        }
        if (modifier._onPaste_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPaste_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPaste(modifier._onPaste_0_0value);
                    break;
                }
                default: {
                    this.onPaste((undefined as PasteEventCallback | undefined));
                }
            }
        }
        if (modifier._enableDataDetector_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableDataDetector_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableDataDetector(modifier._enableDataDetector_0_0value);
                    break;
                }
                default: {
                    this.enableDataDetector((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enablePreviewText_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enablePreviewText_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enablePreviewText(modifier._enablePreviewText_0_0value);
                    break;
                }
                default: {
                    this.enablePreviewText((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._dataDetectorConfig_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dataDetectorConfig_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dataDetectorConfig(modifier._dataDetectorConfig_0_0value);
                    break;
                }
                default: {
                    this.dataDetectorConfig((undefined as TextDataDetectorConfig | undefined));
                }
            }
        }
        if (modifier._caretColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._caretColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.caretColor(modifier._caretColor_0_0value);
                    break;
                }
                default: {
                    this.caretColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._selectedBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedBackgroundColor(modifier._selectedBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.selectedBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._onEditingChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onEditingChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onEditingChange(modifier._onEditingChange_0_0value);
                    break;
                }
                default: {
                    this.onEditingChange((undefined as ((value0: boolean) => void) | undefined));
                }
            }
        }
        if (modifier._enterKeyType_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enterKeyType_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enterKeyType(modifier._enterKeyType_0_0value);
                    break;
                }
                default: {
                    this.enterKeyType((undefined as EnterKeyType | undefined));
                }
            }
        }
        if (modifier._onSubmit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSubmit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSubmit(modifier._onSubmit_0_0value);
                    break;
                }
                default: {
                    this.onSubmit((undefined as SubmitCallback | undefined));
                }
            }
        }
        if (modifier._onWillChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillChange(modifier._onWillChange_0_0value);
                    break;
                }
                default: {
                    this.onWillChange((undefined as ((value0: RichEditorChangeValue) => boolean) | undefined));
                }
            }
        }
        if (modifier._onDidChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidChange(modifier._onDidChange_0_0value);
                    break;
                }
                default: {
                    this.onDidChange((undefined as OnDidChangeCallback | undefined));
                }
            }
        }
        if (modifier._onCut_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onCut_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCut(modifier._onCut_0_0value);
                    break;
                }
                default: {
                    this.onCut((undefined as ((value0: CutEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onCopy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onCopy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCopy(modifier._onCopy_0_0value);
                    break;
                }
                default: {
                    this.onCopy((undefined as ((value0: CopyEvent) => void) | undefined));
                }
            }
        }
        if (modifier._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.editMenuOptions(modifier._editMenuOptions_0_0value);
                    break;
                }
                default: {
                    this.editMenuOptions((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (modifier._enableKeyboardOnFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableKeyboardOnFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableKeyboardOnFocus(modifier._enableKeyboardOnFocus_0_0value);
                    break;
                }
                default: {
                    this.enableKeyboardOnFocus((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._barState_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barState_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barState(modifier._barState_0_0value);
                    break;
                }
                default: {
                    this.barState((undefined as BarState | undefined));
                }
            }
        }
        if (modifier._maxLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxLength(modifier._maxLength_0_0value);
                    break;
                }
                default: {
                    this.maxLength((undefined as number | undefined));
                }
            }
        }
        if (modifier._maxLines_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxLines_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxLines(modifier._maxLines_0_0value);
                    break;
                }
                default: {
                    this.maxLines((undefined as number | undefined));
                }
            }
        }
        if (modifier._keyboardAppearance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._keyboardAppearance_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.keyboardAppearance(modifier._keyboardAppearance_0_0value);
                    break;
                }
                default: {
                    this.keyboardAppearance((undefined as KeyboardAppearance | undefined));
                }
            }
        }
        if (modifier._stopBackPress_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stopBackPress_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stopBackPress(modifier._stopBackPress_0_0value);
                    break;
                }
                default: {
                    this.stopBackPress((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._bindSelectionMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindSelectionMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindSelectionMenu(modifier._bindSelectionMenu_0_0value, modifier._bindSelectionMenu_0_1value, modifier._bindSelectionMenu_0_2value, modifier._bindSelectionMenu_0_3value);
                    break;
                }
                default: {
                    this.bindSelectionMenu((undefined as RichEditorSpanType | undefined), (undefined as CustomBuilder | undefined), (undefined as ResponseType | RichEditorResponseType | undefined), (undefined as SelectionMenuOptions | undefined | undefined));
                }
            }
        }
        if (modifier._customKeyboard_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._customKeyboard_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customKeyboard(modifier._customKeyboard_0_0value, modifier._customKeyboard_0_1value);
                    break;
                }
                default: {
                    this.customKeyboard((undefined as CustomBuilder | undefined), (undefined as KeyboardOptions | undefined | undefined));
                }
            }
        }
        if (modifier._placeholder_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._placeholder_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.placeholder(modifier._placeholder_0_0value, modifier._placeholder_0_1value);
                    break;
                }
                default: {
                    this.placeholder((undefined as ResourceStr | undefined), (undefined as PlaceholderStyle | undefined | undefined));
                }
            }
        }
    }
    onReady(value: VoidCallback | undefined): this {
        if (((this._onReady_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReady_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReady_0_0value = value
        } else
        {
            this._onReady_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSelect(value: ((value0: RichEditorSelection) => void) | undefined): this {
        if (((this._onSelect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSelect_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelect_0_0value = value
        } else
        {
            this._onSelect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSelectionChange(value: ((value0: RichEditorRange) => void) | undefined): this {
        if (((this._onSelectionChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSelectionChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelectionChange_0_0value = value
        } else
        {
            this._onSelectionChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    aboutToIMEInput(value: ((value0: RichEditorInsertValue) => boolean) | undefined): this {
        if (((this._aboutToIMEInput_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._aboutToIMEInput_0_flag = AttributeUpdaterFlag.UPDATE
            this._aboutToIMEInput_0_0value = value
        } else
        {
            this._aboutToIMEInput_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onIMEInputComplete(value: ((value0: RichEditorTextSpanResult) => void) | undefined): this {
        if (((this._onIMEInputComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onIMEInputComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onIMEInputComplete_0_0value = value
        } else
        {
            this._onIMEInputComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidIMEInput(value: ((value0: TextRange) => void) | undefined): this {
        if (((this._onDidIMEInput_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidIMEInput_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidIMEInput_0_0value = value
        } else
        {
            this._onDidIMEInput_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    aboutToDelete(value: ((value0: RichEditorDeleteValue) => boolean) | undefined): this {
        if (((this._aboutToDelete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._aboutToDelete_0_flag = AttributeUpdaterFlag.UPDATE
            this._aboutToDelete_0_0value = value
        } else
        {
            this._aboutToDelete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDeleteComplete(value: VoidCallback | undefined): this {
        if (((this._onDeleteComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDeleteComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDeleteComplete_0_0value = value
        } else
        {
            this._onDeleteComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    copyOptions(value: CopyOptions | undefined): this {
        if (((this._copyOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._copyOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._copyOptions_0_0value = value
        } else
        {
            this._copyOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPaste(value: PasteEventCallback | undefined): this {
        if (((this._onPaste_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPaste_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPaste_0_0value = value
        } else
        {
            this._onPaste_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableDataDetector(value: boolean | undefined): this {
        if (((this._enableDataDetector_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableDataDetector_0_0value) !== (value)))
        {
            this._enableDataDetector_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableDataDetector_0_0value = value
        } else
        {
            this._enableDataDetector_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enablePreviewText(value: boolean | undefined): this {
        if (((this._enablePreviewText_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enablePreviewText_0_0value) !== (value)))
        {
            this._enablePreviewText_0_flag = AttributeUpdaterFlag.UPDATE
            this._enablePreviewText_0_0value = value
        } else
        {
            this._enablePreviewText_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (((this._dataDetectorConfig_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._dataDetectorConfig_0_flag = AttributeUpdaterFlag.UPDATE
            this._dataDetectorConfig_0_0value = value
        } else
        {
            this._dataDetectorConfig_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    caretColor(value: ResourceColor | undefined): this {
        if (((this._caretColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._caretColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._caretColor_0_0value = value
        } else
        {
            this._caretColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._selectedBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedBackgroundColor_0_0value = value
        } else
        {
            this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onEditingChange(value: ((value0: boolean) => void) | undefined): this {
        if (((this._onEditingChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onEditingChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onEditingChange_0_0value = value
        } else
        {
            this._onEditingChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        if (((this._enterKeyType_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._enterKeyType_0_flag = AttributeUpdaterFlag.UPDATE
            this._enterKeyType_0_0value = value
        } else
        {
            this._enterKeyType_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSubmit(value: SubmitCallback | undefined): this {
        if (((this._onSubmit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSubmit_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSubmit_0_0value = value
        } else
        {
            this._onSubmit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillChange(value: ((value0: RichEditorChangeValue) => boolean) | undefined): this {
        if (((this._onWillChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillChange_0_0value = value
        } else
        {
            this._onWillChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidChange(value: OnDidChangeCallback | undefined): this {
        if (((this._onDidChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidChange_0_0value = value
        } else
        {
            this._onDidChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onCut(value: ((value0: CutEvent) => void) | undefined): this {
        if (((this._onCut_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onCut_0_flag = AttributeUpdaterFlag.UPDATE
            this._onCut_0_0value = value
        } else
        {
            this._onCut_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onCopy(value: ((value0: CopyEvent) => void) | undefined): this {
        if (((this._onCopy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onCopy_0_flag = AttributeUpdaterFlag.UPDATE
            this._onCopy_0_0value = value
        } else
        {
            this._onCopy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._editMenuOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._editMenuOptions_0_0value = value
        } else
        {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        if (((this._enableKeyboardOnFocus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableKeyboardOnFocus_0_0value) !== (value)))
        {
            this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableKeyboardOnFocus_0_0value = value
        } else
        {
            this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barState(value: BarState | undefined): this {
        if (((this._barState_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barState_0_flag = AttributeUpdaterFlag.UPDATE
            this._barState_0_0value = value
        } else
        {
            this._barState_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxLength(value: number | undefined): this {
        if (((this._maxLength_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maxLength_0_0value) !== (value)))
        {
            this._maxLength_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxLength_0_0value = value
        } else
        {
            this._maxLength_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxLines(value: number | undefined): this {
        if (((this._maxLines_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maxLines_0_0value) !== (value)))
        {
            this._maxLines_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxLines_0_0value = value
        } else
        {
            this._maxLines_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (((this._keyboardAppearance_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._keyboardAppearance_0_flag = AttributeUpdaterFlag.UPDATE
            this._keyboardAppearance_0_0value = value
        } else
        {
            this._keyboardAppearance_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stopBackPress(value: boolean | undefined): this {
        if (((this._stopBackPress_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stopBackPress_0_0value) !== (value)))
        {
            this._stopBackPress_0_flag = AttributeUpdaterFlag.UPDATE
            this._stopBackPress_0_0value = value
        } else
        {
            this._stopBackPress_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindSelectionMenu(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: ResponseType | RichEditorResponseType | undefined, options?: SelectionMenuOptions): this {
        if (((this._bindSelectionMenu_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true) || (true))
        {
            this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindSelectionMenu_0_0value = spanType
            this._bindSelectionMenu_0_1value = content
            this._bindSelectionMenu_0_2value = responseType
            this._bindSelectionMenu_0_3value = options
        } else
        {
            this._bindSelectionMenu_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (((this._customKeyboard_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._customKeyboard_0_flag = AttributeUpdaterFlag.UPDATE
            this._customKeyboard_0_0value = value
            this._customKeyboard_0_1value = options
        } else
        {
            this._customKeyboard_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    placeholder(value: ResourceStr | undefined, style?: PlaceholderStyle): this {
        if (((this._placeholder_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._placeholder_0_flag = AttributeUpdaterFlag.UPDATE
            this._placeholder_0_0value = value
            this._placeholder_0_1value = style
        } else
        {
            this._placeholder_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}