/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkTabContentComponent extends globalThis.__ArkComponent__ implements TabContentAttribute {
      constructor(nativePtr: KNode, classType?: ModifierType) {
        super(nativePtr, classType);
      }
      tabBar(value: SubTabBarStyle | BottomTabBarStyle | ComponentContent): this {
        modifierWithKey(this._modifiersWithKeys, TabContentTabBarModifier.identity, TabContentTabBarModifier, value);
        return this;
      }
      size(value: SizeOptions): this {
        modifierWithKey(this._modifiersWithKeys, TabContentSizeModifier.identity, TabContentSizeModifier, value);
        return this;
      }
      width(value: Length): this {
        modifierWithKey(this._modifiersWithKeys, TabContentWidthModifier.identity, TabContentWidthModifier, value);
        return this;
      }
      height(value: Length): this {
        modifierWithKey(this._modifiersWithKeys, TabContentHeightModifier.identity, TabContentHeightModifier, value);
        return this;
      }
      onWillShow(event: VoidCallback): TabContent {
        modifierWithKey(this._modifiersWithKeys, TabContentOnWillShowModifier.identity, TabContentOnWillShowModifier, event);
        return this;
      }
      onWillHide(event: VoidCallback): TabContent {
        modifierWithKey(this._modifiersWithKeys, TabContentOnWillHideModifier.identity, TabContentOnWillHideModifier, event);
        return this;
      }
    }
    
    class TabContentTabBarModifier extends ModifierWithKey<SubTabBarStyle | BottomTabBarStyle> {
      constructor(value: SubTabBarStyle | BottomTabBarStyle) {
        super(value);
      }
      static identity: Symbol = Symbol('tabContentTabBar');
      applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
          getUINativeModule().tabContent.resetTabBar(node);
        } else {
          getUINativeModule().tabContent.setTabBar(node, this.value);
        }
      }
    
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    
    class TabContentWidthModifier extends ModifierWithKey<Length> {
      constructor(value: Length) {
        super(value);
      }
      static identity: Symbol = Symbol('tabcontentwidth');
      applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
          getUINativeModule().tabContent.resetTabContentWidth(node);
        } else {
          getUINativeModule().tabContent.setTabContentWidth(node, this.value);
        }
      }
    
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    
    class TabContentHeightModifier extends ModifierWithKey<Length> {
      constructor(value: Length) {
        super(value);
      }
      static identity: Symbol = Symbol('tabcontentheight');
      applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
          getUINativeModule().tabContent.resetTabContentHeight(node);
        } else {
          getUINativeModule().tabContent.setTabContentHeight(node, this.value);
        }
      }
    
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    
    class TabContentSizeModifier extends ModifierWithKey<SizeOptions> {
      constructor(value: SizeOptions) {
        super(value);
      }
      static identity: Symbol = Symbol('tabcontentsize');
      applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
          getUINativeModule().tabContent.resetTabContentSize(node);
        } else {
          getUINativeModule().tabContent.setTabContentSize(node, this.value.width, this.value.height);
        }
      }
    
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
          !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
      }
    }
    
    class TabContentOnWillShowModifier extends ModifierWithKey<VoidCallback> {
      constructor(value: VoidCallback) {
        super(value);
      }
      static identity: Symbol = Symbol('contentonwillshow');
      applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
          getUINativeModule().tabContent.resetTabContentOnWillShow(node);
        } else {
          getUINativeModule().tabContent.setTabContentOnWillShow(node, this.value);
        }
      }
    
      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    
    class TabContentOnWillHideModifier extends ModifierWithKey<VoidCallback> {
      constructor(value: VoidCallback) {
        super(value);
      }
      static identity: Symbol = Symbol('contentonwillhide');
      applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
          getUINativeModule().tabContent.resetTabContentOnWillHide(node);
        } else {
          getUINativeModule().tabContent.setTabContentOnWillHide(node, this.value);
        }
      }

      checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
      }
    }
    
    loadComponent.componentObj = { 'component': ArkTabContentComponent };
  }
  return loadComponent.componentObj;
}

function getTabContentComponent(): any {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  const nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  return JSTabContent.createOrGetNode(elmtId, () => {
    return createComponent(nativeNode, 'tabContent');
  });
}

// @ts-ignore
globalThis.TabContent.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return createComponent(nativePtr, 'tabContent');
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.TabContentModifier(nativePtr, classType);
  });
};

class JSTabContent extends JSContainerBase {
  static create(value: any): void {
    getUINativeModule().tabContent.create(value);
  }

  static pop(value: any): void {
    getUINativeModule().tabContent.pop(value);
  }

  static tabBar(value: any): void {
    getUINativeModule().tabContent.setTabBar(true, value);
  }

  static size(value: any): void {
    getUINativeModule().tabContent.setTabContentSize(true, value);
  }

  static width(value: any): void {
    getUINativeModule().tabContent.setTabContentWidth(true, value);
  }

  static height(value: any): void {
    getUINativeModule().tabContent.setTabContentHeight(true, value);
  }

  static onWillShow(value: any): void {
    getUINativeModule().tabContent.setTabContentOnWillShow(true, value);
  }

  static onWillHide(value: any): void {
    getUINativeModule().tabContent.setTabContentOnWillHide(true, value);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
      return createComponent(nativePtr, 'tabContent');
    }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
      return new modifierJS.TabContentModifier(nativePtr, classType);
    });
  }

  static onAttach(value: any): void {
    __Common__.onAttach(value);
  }

  static onAppear(value: any): void {
    __Common__.onAppear(value);
  }

  static onDetach(value: any): void {
    __Common__.onDetach(value);
  }

  static onDisAppear(value: any): void {
    __Common__.onDisAppear(value);
  }

  static onTouch(value: any): void {
    __Common__.onTouch(value);
  }

  static onHover(value: any): void {
    __Common__.onHover(value);
  }

  static onClick(value: any): void {
    __Common__.onClick(value);
  }

  static onKeyEvent(value: any): void {
    __Common__.onKeyEvent(value);
  }

  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
  }

  static remoteMessage(value: any): void {
    __Common__.remoteMessage(value);
  }
}

function createComponent(nativePtr: any, classType: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkTabContentComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.TabContent = JSTabContent;
}

export default { loadComponent, createComponent, exportComponent, exportView };
