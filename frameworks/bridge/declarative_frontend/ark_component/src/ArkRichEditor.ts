/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path="./import.ts" />

class RichEditorCopyOptionsModifier extends ModifierWithKey<CopyOptions> {
  constructor(value: CopyOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('richEditorCopyOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().richEditor.resetCopyOptions(node);
    } else {
      GetUINativeModule().richEditor.setCopyOptions(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ArkRichEditorComponent extends ArkComponent implements CommonMethod<RichEditorAttribute> {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  enableDataDetector(enable: boolean): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }

  dataDetectorConfig(config: any): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }

  copyOptions(value: CopyOptions): RichEditorAttribute {
    modifierWithKey(this._modifiersWithKeys, RichEditorCopyOptionsModifier.identity, RichEditorCopyOptionsModifier, value);
    return this;
  }
  onPaste(callback: (event?: PasteEvent) => void): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  onReady(callback: () => void): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  onSelect(callback: (value: RichEditorSelection) => void): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  aboutToIMEInput(callback: (value: RichEditorInsertValue) => boolean): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  onIMEInputComplete(callback: (value: RichEditorTextSpanResult) => void): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  aboutToDelete(callback: (value: RichEditorDeleteValue) => boolean): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  onDeleteComplete(callback: () => void): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  bindSelectionMenu(spanType: RichEditorSpanType, content: CustomBuilder, responseType: ResponseType, options?: SelectionMenuOptions): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
  customKeyboard(value: CustomBuilder): RichEditorAttribute {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.RichEditor.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRichEditorComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
