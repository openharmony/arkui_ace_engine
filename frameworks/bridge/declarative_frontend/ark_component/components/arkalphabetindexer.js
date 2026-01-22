/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

/// <reference path='./import.ts' />
class ArkAlphabetIndexerComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onSelected(callback) {
    modifierWithKey(this._modifiersWithKeys, OnSelectedModifier.identity, OnSelectedModifier, callback);
    return this;
  }
  color(value) {
    modifierWithKey(this._modifiersWithKeys, ColorModifier.identity, ColorModifier, value);
    return this;
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedColorModifier.identity, SelectedColorModifier, value);
    return this;
  }
  popupColor(value) {
    modifierWithKey(this._modifiersWithKeys, PopupColorModifier.identity, PopupColorModifier, value);
    return this;
  }
  selectedBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedBackgroundColorModifier.identity, SelectedBackgroundColorModifier, value);
    return this;
  }
  popupBackground(value) {
    modifierWithKey(this._modifiersWithKeys, PopupBackgroundModifier.identity, PopupBackgroundModifier, value);
    return this;
  }
  popupSelectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, PopupSelectedColorModifier.identity, PopupSelectedColorModifier, value);
    return this;
  }
  popupUnselectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, PopupUnselectedColorModifier.identity, PopupUnselectedColorModifier, value);
    return this;
  }
  popupItemBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, PopupItemBackgroundColorModifier.identity, PopupItemBackgroundColorModifier, value);
    return this;
  }
  usingPopup(value) {
    modifierWithKey(this._modifiersWithKeys, UsingPopupModifier.identity, UsingPopupModifier, value);
    return this;
  }
  selectedFont(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedFontModifier.identity, SelectedFontModifier, value);
    return this;
  }
  popupFont(value) {
    modifierWithKey(this._modifiersWithKeys, PopupFontModifier.identity, PopupFontModifier, value);
    return this;
  }
  popupItemFont(value) {
    modifierWithKey(this._modifiersWithKeys, PopupItemFontModifier.identity, PopupItemFontModifier, value);
    return this;
  }
  itemSize(value) {
    modifierWithKey(this._modifiersWithKeys, ItemSizeModifier.identity, ItemSizeModifier, value);
    return this;
  }
  font(value) {
    modifierWithKey(this._modifiersWithKeys, AlphabetIndexerFontModifier.identity, AlphabetIndexerFontModifier, value);
    return this;
  }
  alignStyle(value, offset) {
    let alignStyle = new ArkAlignStyle;
    alignStyle.indexerAlign = value;
    alignStyle.offset = offset;
    modifierWithKey(this._modifiersWithKeys, AlignStyleModifier.identity, AlignStyleModifier, alignStyle);
    return this;
  }
  onSelect(callback) {
    modifierWithKey(this._modifiersWithKeys, OnSelectModifier.identity, OnSelectModifier, callback);
    return this;
  }
  onRequestPopupData(callback) {
    modifierWithKey(this._modifiersWithKeys, OnRequestPopupDataModifier.identity, OnRequestPopupDataModifier, callback);
    return this;
  }
  onPopupSelect(callback) {
    modifierWithKey(this._modifiersWithKeys, OnPopupSelectModifier.identity, OnPopupSelectModifier, callback);
    return this;
  }
  selected(index) {
    modifierWithKey(this._modifiersWithKeys, AlphabetIndexerSelectedModifier.identity, AlphabetIndexerSelectedModifier, index);
    return this;
  }
  popupPosition(value) {
    modifierWithKey(this._modifiersWithKeys, PopupPositionModifier.identity, PopupPositionModifier, value);
    return this;
  }
  popupItemBorderRadius(value) {
    modifierWithKey(this._modifiersWithKeys, PopupItemBorderRadiusModifier.identity, PopupItemBorderRadiusModifier, value);
    return this;
  }
  itemBorderRadius(value) {
    modifierWithKey(this._modifiersWithKeys, ItemBorderRadiusModifier.identity, ItemBorderRadiusModifier, value);
    return this;
  }
  popupBackgroundBlurStyle(value) {
    modifierWithKey(this._modifiersWithKeys, PopupBackgroundBlurStyleModifier.identity, PopupBackgroundBlurStyleModifier, value);
    return this;
  }
  popupTitleBackground(value) {
    modifierWithKey(this._modifiersWithKeys, PopupTitleBackgroundModifier.identity, PopupTitleBackgroundModifier, value);
    return this;
  }
  width(value) {
    modifierWithKey(this._modifiersWithKeys, AdaptiveWidthModifier.identity, AdaptiveWidthModifier, value);
    return this;
  }
  autoCollapse(value) {
    modifierWithKey(this._modifiersWithKeys, AutoCollapseModifier.identity, AutoCollapseModifier, value);
    return this;
  }
  enableHapticFeedback(value) {
    modifierWithKey(this._modifiersWithKeys, EnableHapticFeedbackModifier.identity, EnableHapticFeedbackModifier, value);
    return this;
  }
}

class PopupItemFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupItemFont(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupItemFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
PopupItemFontModifier.identity = Symbol('popupItemFont');
class SelectedFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelectedFont(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setSelectedFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
SelectedFontModifier.identity = Symbol('alphaBetIndexerSelectedFont');
class PopupFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupFont(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
PopupFontModifier.identity = Symbol('popupFont');
class AlphabetIndexerFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetFont(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
AlphabetIndexerFontModifier.identity = Symbol('alphaBetIndexerFont');
class PopupItemBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupItemBackgroundColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupItemBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PopupItemBackgroundColorModifier.identity = Symbol('popupItemBackgroundColor');
class OnSelectedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetOnSelected(node);
    } else {
      getUINativeModule().alphabetIndexer.setOnSelected(node, this.value);
    }
  }
}
OnSelectedModifier.identity = Symbol('onSelected');
class OnSelectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetOnSelect(node);
    } else {
      getUINativeModule().alphabetIndexer.setOnSelect(node, this.value);
    }
  }
}
OnSelectModifier.identity = Symbol('onSelect');
class OnRequestPopupDataModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetOnRequestPopupData(node);
    } else {
      getUINativeModule().alphabetIndexer.setOnRequestPopupData(node, this.value);
    }
  }
}
OnRequestPopupDataModifier.identity = Symbol('onRequestPopupData');
class OnPopupSelectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetOnPopupSelect(node);
    } else {
      getUINativeModule().alphabetIndexer.setOnPopupSelect(node, this.value);
    }
  }
}
OnPopupSelectModifier.identity = Symbol('onPopupSelect');
class ColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ColorModifier.identity = Symbol('alphabetColor');
class PopupColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PopupColorModifier.identity = Symbol('popupColor');
class SelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelectedColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectedColorModifier.identity = Symbol('selectedColor');
class PopupBackgroundModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupBackground(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupBackground(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PopupBackgroundModifier.identity = Symbol('popupBackground');
class SelectedBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelectedBackgroundColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setSelectedBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectedBackgroundColorModifier.identity = Symbol('selectedBackgroundColor');
class PopupUnselectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupUnselectedColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupUnselectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PopupUnselectedColorModifier.identity = Symbol('popupUnselectedColor');
class PopupSelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupSelectedColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PopupSelectedColorModifier.identity = Symbol('popupSelectedColor');
class AlignStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetAlignStyle(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setAlignStyle(node, this.value.indexerAlign, this.value.offset);
    }
  }
  checkObjectDiff() {
    let indexerAlignEQ = isBaseOrResourceEqual(this.stageValue.indexerAlign, this.value.indexerAlign);
    let offsetEQ = isBaseOrResourceEqual(this.stageValue.offset, this.value.offset);
    return !indexerAlignEQ || !offsetEQ;
  }
}
AlignStyleModifier.identity = Symbol('alignStyle');
class UsingPopupModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetUsingPopup(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setUsingPopup(node, this.value);
    }
  }
}
UsingPopupModifier.identity = Symbol('usingPopup');
class AlphabetIndexerSelectedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelected(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setSelected(node, this.value);
    }
  }
}
AlphabetIndexerSelectedModifier.identity = Symbol('alphabetIndexerSelected');
class ItemSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetItemSize(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setItemSize(node, this.value);
    }
  }
}
ItemSizeModifier.identity = Symbol('itemSize');
class PopupPositionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupPosition(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupPosition(node, this.value.x, this.value.y);
    }
  }
  checkObjectDiff() {
    let xEQ = isBaseOrResourceEqual(this.stageValue.x, this.value.x);
    let yEQ = isBaseOrResourceEqual(this.stageValue.y, this.value.y);
    return !xEQ || !yEQ;
  }
}
PopupPositionModifier.identity = Symbol('popupPosition');
class PopupItemBorderRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupItemBorderRadius(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupItemBorderRadius(node, this.value);
    }
  }
}
PopupItemBorderRadiusModifier.identity = Symbol('popupItemBorderRadius');
class ItemBorderRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetItemBorderRadius(node);
    } else {
      getUINativeModule().alphabetIndexer.setItemBorderRadius(node, this.value);
    }
  }
}
ItemBorderRadiusModifier.identity = Symbol('itemBorderRadius');
class PopupBackgroundBlurStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupBackgroundBlurStyle(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupBackgroundBlurStyle(node, this.value);
    }
  }
}
ItemBorderRadiusModifier.identity = Symbol('popupBackgroundBlurStyle');

class PopupTitleBackgroundModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupTitleBackground(node);
    } else {
      getUINativeModule().alphabetIndexer.setPopupTitleBackground(node, this.value);
    }
  }
}
PopupTitleBackgroundModifier.identity = Symbol('popupTitleBackground');
class AdaptiveWidthModifier extends ModifierWithKey {
  constructor(value) {
      super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
        getUINativeModule().alphabetIndexer.resetAdaptiveWidth(node);
    } else {
        getUINativeModule().alphabetIndexer.setAdaptiveWidth(node, this.value);
    }
  }
}
AdaptiveWidthModifier.identity = Symbol('adaptiveWidth');
class AutoCollapseModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetAutoCollapse(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setAutoCollapse(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
AutoCollapseModifier.identity = Symbol('autoCollapse');
class EnableHapticFeedbackModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetEnableHapticFeedback(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setEnableHapticFeedback(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
EnableHapticFeedbackModifier.identity = Symbol('enableHapticFeedback');

 class JSAlphabetIndexer extends JSViewAbstract {
   static create(params) {
     getUINativeModule().alphabetIndexer.create(params, false);
     return this;
   }
   static createArc(params) {
     getUINativeModule().alphabetIndexer.create(params, true);
     return this;
   }
   static onSelected(value) {
     getUINativeModule().alphabetIndexer.setOnSelected(true, value);
   }
 
   static color(value) {
     getUINativeModule().alphabetIndexer.setColor(true, value);
   }
 
   static selectedColor(value) {
     getUINativeModule().alphabetIndexer.setSelectedColor(true, value);
   }
   static popupColor(value) {
     getUINativeModule().alphabetIndexer.setPopupColor(true, value);
   }
 
   static selectedBackgroundColor(value) {
     getUINativeModule().alphabetIndexer.setSelectedBackgroundColor(true, value);
   }
 
   static popupBackground(value) {
     getUINativeModule().alphabetIndexer.setPopupBackground(true, value);
   }
 
   static popupSelectedColor(value) {
     getUINativeModule().alphabetIndexer.setPopupSelectedColor(true, value);
   }
 
   static popupUnselectedColor(value) {
     getUINativeModule().alphabetIndexer.setPopupUnselectedColor(true, value);
   }
 
   static popupItemBackgroundColor(value) {
     getUINativeModule().alphabetIndexer.setPopupItemBackgroundColor(true, value);
   }
 
   static usingPopup(value) {
     getUINativeModule().alphabetIndexer.setUsingPopup(true, value);
   }
 
   static selectedFont(value) {
     getUINativeModule().alphabetIndexer.setSelectedFont(true, value);
   }
 
   static popupFont(value) {
     getUINativeModule().alphabetIndexer.setPopupFont(true, value);
   }
 
   static popupItemFont(value) {
     getUINativeModule().alphabetIndexer.setPopupItemFont(true, value);
   }
 
   static itemSize(value) {
     getUINativeModule().alphabetIndexer.setItemSize(true, value);
   }
 
   static font(value) {
     getUINativeModule().alphabetIndexer.setFont(true, value);
   }
 
   static alignStyle(value, offset) {
     getUINativeModule().alphabetIndexer.setAlignStyle(true, value, offset);
   }
   static onSelect(value) {
     getUINativeModule().alphabetIndexer.setOnSelect(true, value);
   }
 
   static onRequestPopupData(value) {
     getUINativeModule().alphabetIndexer.setOnRequestPopupData(true, value);
   }
 
   static onPopupSelect(value) {
     getUINativeModule().alphabetIndexer.setOnPopupSelect(true, value);
   }
   static selected(value, callback) {
     getUINativeModule().alphabetIndexer.setSelected(true, value, callback);
   }
   static popupPosition(value) {
     getUINativeModule().alphabetIndexer.setPopupPosition(true, value);
   }
   static popupItemBorderRadius(value) {
     getUINativeModule().alphabetIndexer.setPopupItemBorderRadius(true, value);
   }
   static itemBorderRadius(value) {
     getUINativeModule().alphabetIndexer.setItemBorderRadius(true, value);
   }
   static popupBackgroundBlurStyle(value) {
     getUINativeModule().alphabetIndexer.setPopupBackgroundBlurStyle(true, value);
   }
   static popupTitleBackground(value) {
     getUINativeModule().alphabetIndexer.setPopupTitleBackground(true, value);
   }
   static width(value) {
     getUINativeModule().alphabetIndexer.setAdaptiveWidth(true, value);
   }
   static autoCollapse(value) {
     getUINativeModule().alphabetIndexer.setAutoCollapse(true, value);
   }
   static enableHapticFeedback(value) {
     getUINativeModule().alphabetIndexer.setEnableHapticFeedback(true, value);
   }
 
   static attributeModifier(modifier) {
     attributeModifierFunc.call(this, modifier, (nativePtr) => {
       return new ArkAlphabetIndexerComponent(nativePtr);
     }, (nativePtr, classType, modifierJS) => {
       return new modifierJS.AlphabetIndexerModifier(nativePtr, classType);
     });
   }
 
   static onAttach(value) {
     __Common__.onAttach(value);
   }
   static onAppear(value) {
     __Common__.onAppear(value);
   }
   static onDetach(value) {
     __Common__.onDetach(value);
   }
   static onDisAppear(value) {
     __Common__.onDisAppear(value);
   }
   static onTouch(value) {
     __Common__.onTouch(value);
   }
 }
 
 function createComponent(nativePtr, classType) {
   return new ArkAlphabetIndexerComponent(nativePtr, classType);
 }
 function exportComponent() {
   globalThis.ArkAlphabetIndexerComponent = ArkAlphabetIndexerComponent;
 }
 
 function exportView() {
   globalThis.AlphabetIndexer = JSAlphabetIndexer;
 }
 
export default { ArkAlphabetIndexerComponent, JSAlphabetIndexer, createComponent, exportComponent, exportView };