/// <reference path="./import.ts" />

class RichEditorCopyOptionsModifier extends Modifier<CopyOptions> {
    static identity: Symbol = Symbol('richEditorCopyOptions');
    applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
        GetUINativeModule().richEditor.resetCopyOptions(node);
      } else {
        GetUINativeModule().richEditor.setCopyOptions(node, this.value!);
      }
    }
  }
  
  class ArkRichEditorComponent extends ArkComponent implements CommonMethod<RichEditorAttribute>{
    copyOptions(value: CopyOptions): RichEditorAttribute {
      if (value) {
        modifier(this._modifiers, RichEditorCopyOptionsModifier, value);
      } else {
        modifier(this._modifiers, RichEditorCopyOptionsModifier, undefined);
      }
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
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
  
  }
  