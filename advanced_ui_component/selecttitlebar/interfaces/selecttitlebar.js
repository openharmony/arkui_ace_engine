/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
if (PUV2ViewBase.contextStack === undefined) {
  Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const hilog = requireNapi('hilog');
const PUBLIC_MORE = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_more'],
  'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_back'],
  'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';

export class SelectTitleBar extends ViewPU {
  constructor(x9, y9, z9, a10 = -1, b10 = undefined, c10) {
    super(x9, z9, a10, c10);
    if (typeof b10 === 'function') {
      this.paramsGenerator_ = b10;
    }
    this.__selected = new SynchedPropertySimpleOneWayPU(y9.selected, this, 'selected');
    this.options = [];
    this.menuItems = [];
    this.subtitle = '';
    this.badgeValue = 0;
    this.hidesBackButton = false;
    this.onSelected = () => { };
    this.__selectMaxWidth = new ObservedPropertySimplePU(0, this, 'selectMaxWidth');
    this.__backActive = new ObservedPropertySimplePU(false, this, 'backActive');
    this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
    this.setInitiallyProvidedValue(y9);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(w9) {
    if (w9.selected === undefined) {
      this.__selected.set(0);
    }
    if (w9.options !== undefined) {
      this.options = w9.options;
    }
    if (w9.menuItems !== undefined) {
      this.menuItems = w9.menuItems;
    }
    if (w9.subtitle !== undefined) {
      this.subtitle = w9.subtitle;
    }
    if (w9.badgeValue !== undefined) {
      this.badgeValue = w9.badgeValue;
    }
    if (w9.hidesBackButton !== undefined) {
      this.hidesBackButton = w9.hidesBackButton;
    }
    if (w9.onSelected !== undefined) {
      this.onSelected = w9.onSelected;
    }
    if (w9.selectMaxWidth !== undefined) {
      this.selectMaxWidth = w9.selectMaxWidth;
    }
    if (w9.backActive !== undefined) {
      this.backActive = w9.backActive;
    }
    if (w9.fontSize !== undefined) {
      this.fontSize = w9.fontSize;
    }
  }

  updateStateVars(v9) {
    this.__selected.reset(v9.selected);
  }

  purgeVariableDependenciesOnElmtId(u9) {
    this.__selected.purgeDependencyOnElmtId(u9);
    this.__selectMaxWidth.purgeDependencyOnElmtId(u9);
    this.__backActive.purgeDependencyOnElmtId(u9);
    this.__fontSize.purgeDependencyOnElmtId(u9);
  }

  aboutToBeDeleted() {
    this.__selected.aboutToBeDeleted();
    this.__selectMaxWidth.aboutToBeDeleted();
    this.__backActive.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get selected() {
    return this.__selected.get();
  }

  set selected(t9) {
    this.__selected.set(t9);
  }

  get selectMaxWidth() {
    return this.__selectMaxWidth.get();
  }

  set selectMaxWidth(s9) {
    this.__selectMaxWidth.set(s9);
  }

  get backActive() {
    return this.__backActive.get();
  }

  set backActive(r9) {
    this.__backActive.set(r9);
  }

  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(q9) {
    this.__fontSize.set(q9);
  }

  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((j9, k9) => {
      Flex.create({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      });
      Flex.width('100%');
      Flex.height(SelectTitleBar.totalHeight);
      Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Flex.onAreaChange((m9, n9) => {
        let o9 = Number(n9.width);
        if (!this.hidesBackButton) {
          o9 -= ImageMenuItem.imageHotZoneWidth;
          o9 += SelectTitleBar.leftPadding;
          o9 -= SelectTitleBar.leftPaddingWithBack;
        }
        if (this.menuItems !== undefined) {
          let p9 = this.menuItems.length;
          if (p9 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
            o9 -= ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
          } else if (p9 > 0) {
            o9 -= ImageMenuItem.imageHotZoneWidth * p9;
          }
        }
        if (this.badgeValue) {
          this.selectMaxWidth = o9 - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding -
          SelectTitleBar.rightPadding - SelectTitleBar.badgePadding;
        } else {
          this.selectMaxWidth = o9 - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding;
        }
      });
    }, Flex);
    this.observeComponentCreation2((h9, i9) => {
      Row.create();
      Row.margin({ left: this.hidesBackButton ? {
        'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_start'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
        { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
      });
    }, Row);
    this.observeComponentCreation2((t8, u8) => {
      If.create();
      if (!this.hidesBackButton) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((f9, g9) => {
            Navigator.create();
            Navigator.active(this.backActive);
          }, Navigator);
          Navigator.pop();
          {
            this.observeComponentCreation2((z8, a9) => {
              if (a9) {
                let b9 = new ImageMenuItem(this, { item: {
                  value: PUBLIC_BACK,
                  isEnabled: true,
                  action: () => this.backActive = true,
                }, index: -1 }, undefined, z8, () => { },
                  { page: 'library/src/main/ets/components/MainPage.ets', line: 73, col: 11 });
                ViewPU.create(b9);
                let c9 = () => {
                  return {
                    item: {
                      value: PUBLIC_BACK,
                      isEnabled: true,
                      action: () => this.backActive = true,
                    },
                    index: -1,
                  };
                };
                b9.paramsGenerator_ = c9;
              }
              else {
                this.updateStateVarsOfChildByElmtId(z8, {});
              }
            }, { name: 'ImageMenuItem' });
          }
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((r8, s8) => {
      Column.create();
      Column.justifyContent(FlexAlign.Start);
      Column.alignItems(HorizontalAlign.Start);
      Column.constraintSize({ maxWidth: this.selectMaxWidth });
    }, Column);
    this.observeComponentCreation2((y7, z7) => {
      If.create();
      if (this.badgeValue) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((p8, q8) => {
            Badge.create({
              count: this.badgeValue,
              position: BadgePosition.Right,
              style: {
                badgeColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'],
                  'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                borderColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'],
                  'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                borderWidth: 0
              }
            });
          }, Badge);
          this.observeComponentCreation2((n8, o8) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            Row.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
          }, Row);
          this.observeComponentCreation2((l8, m8) => {
            Select.create(this.options);
            Select.selected(this.selected);
            Select.value(this.selected < this.options.length ? this.options[this.selected].value.toString() : '');
            Select.font({ size: this.hidesBackButton && !this.subtitle ?
              { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline7'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
              { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Select.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Select.backgroundColor(Color.Transparent);
            Select.onSelect(this.onSelected);
            Select.constraintSize({ maxWidth: this.selectMaxWidth });
            Select.offset({ x: -4 });
          }, Select);
          Select.pop();
          Row.pop();
          Badge.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((f8, g8) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
          }, Row);
          this.observeComponentCreation2((d8, e8) => {
            Select.create(this.options);
            Select.selected(this.selected);
            Select.value(this.selected < this.options.length ? this.options[this.selected].value.toString() : '');
            Select.font({ size: this.hidesBackButton && !this.subtitle ?
              { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline7'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
              { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Select.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Select.backgroundColor(Color.Transparent);
            Select.onSelect(this.onSelected);
            Select.constraintSize({ maxWidth: this.selectMaxWidth });
            Select.offset({ x: -4 });
          }, Select);
          Select.pop();
          Row.pop();
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((o7, p7) => {
      If.create();
      if (this.subtitle !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((w7, x7) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            Row.margin({ left: SelectTitleBar.subtitleLeftPadding });
          }, Row);
          this.observeComponentCreation2((u7, v7) => {
            Text.create(this.subtitle);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_over_line'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ maxWidth: this.selectMaxWidth });
            Text.offset({ y: -4 });
          }, Text);
          Text.pop();
          Row.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    Column.pop();
    Row.pop();
    this.observeComponentCreation2((d7, e7) => {
      If.create();
      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          {
            this.observeComponentCreation2((i7, j7) => {
              if (j7) {
                let k7 = new CollapsibleMenuSection(this, { menuItems: this.menuItems,
                  index: 1 + SelectTitleBar.instanceCount++ }, undefined, i7, () => { },
                  { page: 'library/src/main/ets/components/MainPage.ets', line: 146, col: 9 });
                ViewPU.create(k7);
                let l7 = () => {
                  return {
                    menuItems: this.menuItems,
                    index: 1 + SelectTitleBar.instanceCount++
                  };
                };
                k7.paramsGenerator_ = l7;
              }
              else {
                this.updateStateVarsOfChildByElmtId(i7, {});
              }
            }, { name: 'CollapsibleMenuSection' });
          }
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    Flex.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }

  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
SelectTitleBar.badgeSize = 16;
SelectTitleBar.totalHeight = 56;
SelectTitleBar.leftPadding = 24;
SelectTitleBar.leftPaddingWithBack = 12;
SelectTitleBar.rightPadding = 24;
SelectTitleBar.badgePadding = 16;
SelectTitleBar.subtitleLeftPadding = 4;
SelectTitleBar.instanceCount = 0;
class CollapsibleMenuSection extends ViewPU {
  constructor(m6, n6, o6, p6 = -1, q6 = undefined, r6) {
    super(m6, o6, p6, r6);
    if (typeof q6 === 'function') {
      this.paramsGenerator_ = q6;
    }
    this.menuItems = [];
    this.item = {
      value: PUBLIC_MORE,
      label: { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
    };
    this.index = 0;
    this.longPressTime = 500;
    this.minFontSize = 1.75;
    this.isFollowingSystemFontScale = false;
    this.maxFontScale = 1;
    this.systemFontScale = 1;
    this.firstFocusableIndex = -1;
    this.__isPopupShown = new ObservedPropertySimplePU(false, this, 'isPopupShown');
    this.__isMoreIconOnFocus = new ObservedPropertySimplePU(false, this, 'isMoreIconOnFocus');
    this.__isMoreIconOnHover = new ObservedPropertySimplePU(false, this, 'isMoreIconOnHover');
    this.__isMoreIconOnClick = new ObservedPropertySimplePU(false, this, 'isMoreIconOnClick');
    this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
    this.dialogController = new CustomDialogController({
      builder: () => {
        let s6 = new SelectTitleBarDialog(this, {
          cancel: () => {
          },
          confirm: () => {
          },
          SelectTitleDialog: this.item,
          SelectTitleBarDialog: this.item.label ? this.item.label : '',
          fontSize: this.fontSize,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 201, col: 14 });
        s6.setController(this.dialogController);
        ViewPU.create(s6);
        let t6 = () => {
          return {
            cancel: () => {
            },
            confirm: () => {
            },
            SelectTitleDialog: this.item,
            SelectTitleBarDialog: this.item.label ? this.item.label : '',
            fontSize: this.fontSize
          };
        };
        s6.paramsGenerator_ = t6;
      },
      maskColor: Color.Transparent,
      isModal: true,
      customStyle: true
    }, this);
    this.setInitiallyProvidedValue(n6);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(l6) {
    if (l6.menuItems !== undefined) {
      this.menuItems = l6.menuItems;
    }
    if (l6.item !== undefined) {
      this.item = l6.item;
    }
    if (l6.index !== undefined) {
      this.index = l6.index;
    }
    if (l6.longPressTime !== undefined) {
      this.longPressTime = l6.longPressTime;
    }
    if (l6.minFontSize !== undefined) {
      this.minFontSize = l6.minFontSize;
    }
    if (l6.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = l6.isFollowingSystemFontScale;
    }
    if (l6.maxFontScale !== undefined) {
      this.maxFontScale = l6.maxFontScale;
    }
    if (l6.systemFontScale !== undefined) {
      this.systemFontScale = l6.systemFontScale;
    }
    if (l6.firstFocusableIndex !== undefined) {
      this.firstFocusableIndex = l6.firstFocusableIndex;
    }
    if (l6.isPopupShown !== undefined) {
      this.isPopupShown = l6.isPopupShown;
    }
    if (l6.isMoreIconOnFocus !== undefined) {
      this.isMoreIconOnFocus = l6.isMoreIconOnFocus;
    }
    if (l6.isMoreIconOnHover !== undefined) {
      this.isMoreIconOnHover = l6.isMoreIconOnHover;
    }
    if (l6.isMoreIconOnClick !== undefined) {
      this.isMoreIconOnClick = l6.isMoreIconOnClick;
    }
    if (l6.fontSize !== undefined) {
      this.fontSize = l6.fontSize;
    }
    if (l6.dialogController !== undefined) {
      this.dialogController = l6.dialogController;
    }
  }

  updateStateVars(k6) {
  }

  purgeVariableDependenciesOnElmtId(j6) {
    this.__isPopupShown.purgeDependencyOnElmtId(j6);
    this.__isMoreIconOnFocus.purgeDependencyOnElmtId(j6);
    this.__isMoreIconOnHover.purgeDependencyOnElmtId(j6);
    this.__isMoreIconOnClick.purgeDependencyOnElmtId(j6);
    this.__fontSize.purgeDependencyOnElmtId(j6);
  }

  aboutToBeDeleted() {
    this.__isPopupShown.aboutToBeDeleted();
    this.__isMoreIconOnFocus.aboutToBeDeleted();
    this.__isMoreIconOnHover.aboutToBeDeleted();
    this.__isMoreIconOnClick.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get isPopupShown() {
    return this.__isPopupShown.get();
  }

  set isPopupShown(i6) {
    this.__isPopupShown.set(i6);
  }

  get isMoreIconOnFocus() {
    return this.__isMoreIconOnFocus.get();
  }

  set isMoreIconOnFocus(h6) {
    this.__isMoreIconOnFocus.set(h6);
  }

  get isMoreIconOnHover() {
    return this.__isMoreIconOnHover.get();
  }

  set isMoreIconOnHover(g6) {
    this.__isMoreIconOnHover.set(g6);
  }

  get isMoreIconOnClick() {
    return this.__isMoreIconOnClick.get();
  }

  set isMoreIconOnClick(f6) {
    this.__isMoreIconOnClick.set(f6);
  }

  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(e6) {
    this.__fontSize.set(e6);
  }

  getMoreIconFgColor() {
    return this.isMoreIconOnClick ?
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
  }

  getMoreIconBgColor() {
    if (this.isMoreIconOnClick) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else if (this.isMoreIconOnHover) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else {
      return Color.Transparent;
    }
  }

  aboutToAppear() {
    try {
      let h = this.getUIContext();
      this.isFollowingSystemFontScale = h.isFollowingSystemFontScale();
      this.maxFontScale = h.getMaxFontScale();
    }
    catch (j9) {
      let k9 = j9.code;
      let l9 = j9.message;
      hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${k9}, message: ${l9}`);
    }
    this.menuItems.forEach((c6, d6) => {
      if (c6.isEnabled && this.firstFocusableIndex == -1 &&
        d6 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + d6 + 1;
      }
    });
  }
  decideFontScale() {
    let m9 = this.getUIContext();
    this.systemFontScale = m9.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale, this.maxFontScale);
  }

  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((z5, a6) => {
      Column.create();
      Column.height('100%');
      Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
      Column.justifyContent(FlexAlign.Center);
    }, Column);
    this.observeComponentCreation2((x5, y5) => {
      Row.create();
    }, Row);
    this.observeComponentCreation2((w3, x3) => {
      If.create();
      if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((j5, k5) => {
            ForEach.create();
            const l5 = (n5, o5) => {
              const p5 = n5;
              {
                this.observeComponentCreation2((r5, s5) => {
                  if (s5) {
                    let t5 = new ImageMenuItem(this, { item: p5, index: this.index * 1000 + o5 + 1 }, undefined, r5,
                      () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 245, col: 13 });
                    ViewPU.create(t5);
                    let u5 = () => {
                      return {
                        item: p5,
                        index: this.index * 1000 + o5 + 1
                      };
                    };
                    t5.paramsGenerator_ = u5;
                  }
                  else {
                    this.updateStateVarsOfChildByElmtId(r5, {});
                  }
                }, { name: 'ImageMenuItem' });
              }
            };
            this.forEachUpdateFunction(j5, this.menuItems, l5, undefined, true, false);
          }, ForEach);
          ForEach.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((t4, u4) => {
            ForEach.create();
            const v4 = (x4, y4) => {
              const z4 = x4;
              {
                this.observeComponentCreation2((b5, c5) => {
                  if (c5) {
                    let d5 = new ImageMenuItem(this, { item: z4, index: this.index * 1000 + y4 + 1 }, undefined, b5,
                      () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 250, col: 15 });
                    ViewPU.create(d5);
                    let e5 = () => {
                      return {
                        item: z4,
                        index: this.index * 1000 + y4 + 1
                      };
                    };
                    d5.paramsGenerator_ = e5;
                  }
                  else {
                    this.updateStateVarsOfChildByElmtId(b5, {});
                  }
                }, { name: 'ImageMenuItem' });
              }
            };
            this.forEachUpdateFunction(t4, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1),
              v4, undefined, true, false);
          }, ForEach);
          ForEach.pop();
          this.observeComponentCreation2((e4, f4) => {
            Row.create();
            Row.width(ImageMenuItem.imageHotZoneWidth);
            Row.height(ImageMenuItem.imageHotZoneWidth);
            Row.borderRadius(ImageMenuItem.buttonBorderRadius);
            Row.foregroundColor(this.getMoreIconFgColor());
            Row.backgroundColor(this.getMoreIconBgColor());
            Row.justifyContent(FlexAlign.Center);
            ViewStackProcessor.visualState('focused');
            Row.border({
              radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              width: ImageMenuItem.focusBorderWidth,
              color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState('normal');
            Row.border({
              radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              width: 0
            });
            ViewStackProcessor.visualState();
            Row.onFocus(() => this.isMoreIconOnFocus = true);
            Row.onBlur(() => this.isMoreIconOnFocus = false);
            Row.onHover((s4) => this.isMoreIconOnHover = s4);
            Row.onKeyEvent((r4) => {
              if (r4.keyCode !== KeyCode.KEYCODE_ENTER && r4.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (r4.type === KeyType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (r4.type === KeyType.Up) {
                this.isMoreIconOnClick = false;
              }
            });
            Row.onTouch((q4) => {
              if (q4.type === TouchType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (q4.type === TouchType.Up || q4.type === TouchType.Cancel) {
                this.isMoreIconOnClick = false;
                if (this.fontSize >= this.minFontSize) {
                  this.dialogController?.close();
                }
              }
            });
            Row.onClick(() => this.isPopupShown = true);
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: false, duration: this.longPressTime });
            LongPressGesture.onAction((o4) => {
              this.fontSize = this.decideFontScale();
              if (o4) {
                if (this.fontSize >= this.minFontSize) {
                  this.dialogController?.open();
                }
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Row.bindPopup(this.isPopupShown, {
              builder: { builder: this.popupBuilder.bind(this) },
              placement: Placement.Bottom,
              popupColor: Color.White,
              enableArrow: false,
              onStateChange: (n4) => {
                this.isPopupShown = n4.isVisible;
                if (!n4.isVisible) {
                  this.isMoreIconOnClick = false;
                }
              }
            });
          }, Row);
          this.observeComponentCreation2((c4, d4) => {
            Image.create(PUBLIC_MORE);
            Image.width(ImageMenuItem.imageSize);
            Image.height(ImageMenuItem.imageSize);
            Image.focusable(true);
            Image.draggable(false);
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Image);
          Row.pop();
        });
      }
    }, If);
    If.pop();
    Row.pop();
    Column.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }

  popupBuilder(z2 = null) {
    this.observeComponentCreation2((q3, r3) => {
      Column.create();
      Column.width(
        ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum
      );
      Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
      Column.onAppear(() => {
        focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
      });
    }, Column);
    this.observeComponentCreation2((c3, d3) => {
      ForEach.create();
      const e3 = (g3, h3) => {
        const i3 = g3;
        {
          this.observeComponentCreation2((k3, l3) => {
            if (l3) {
              let m3 = new ImageMenuItem(this, { item: i3,
                index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + h3, isPopup: true },
                undefined, k3, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 345, col: 11 });
              ViewPU.create(m3);
              let n3 = () => {
                return {
                  item: i3,
                  index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + h3,
                  isPopup: true
                };
              };
              m3.paramsGenerator_ = n3;
            }
            else {
              this.updateStateVarsOfChildByElmtId(k3, {});
            }
          }, { name: 'ImageMenuItem' });
        }
      };
      this.forEachUpdateFunction(c3, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1,
        this.menuItems.length), e3, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    Column.pop();
  }

  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
CollapsibleMenuSection.maxCountOfVisibleItems = 3;
CollapsibleMenuSection.focusPadding = 4;
CollapsibleMenuSection.marginsNum = 2;
class ImageMenuItem extends ViewPU {
  constructor(p2, q2, r2, s2 = -1, t2 = undefined, u2) {
    super(p2, r2, s2, u2);
    if (typeof t2 === 'function') {
      this.paramsGenerator_ = t2;
    }
    this.item = {};
    this.index = 0;
    this.longPressTime = 500;
    this.minFontSize = 1.75;
    this.isFollowingSystemFontScale = false;
    this.maxFontScale = 1;
    this.systemFontScale = 1;
    this.isPopup = false;
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
    this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
    this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
    this.__fontSize = new SynchedPropertySimpleOneWayPU(q2.fontSize, this, 'fontSize');
    this.dialogController = new CustomDialogController({
      builder: () => {
        let v2 = new SelectTitleBarDialog(this, {
          cancel: () => {
          },
          confirm: () => {
          },
          SelectTitleDialog: this.item,
          SelectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
          fontSize: this.fontSize,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 376, col: 14 });
        v2.setController(this.dialogController);
        ViewPU.create(v2);
        let w2 = () => {
          return {
            cancel: () => {
            },
            confirm: () => {
            },
            SelectTitleDialog: this.item,
            SelectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
            fontSize: this.fontSize
          };
        };
        v2.paramsGenerator_ = w2;
      },
      maskColor: Color.Transparent,
      isModal: true,
      customStyle: true
    }, this);
    this.setInitiallyProvidedValue(q2);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(o2) {
    if (o2.item !== undefined) {
      this.item = o2.item;
    }
    if (o2.index !== undefined) {
      this.index = o2.index;
    }
    if (o2.longPressTime !== undefined) {
      this.longPressTime = o2.longPressTime;
    }
    if (o2.minFontSize !== undefined) {
      this.minFontSize = o2.minFontSize;
    }
    if (o2.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = o2.isFollowingSystemFontScale;
    }
    if (o2.maxFontScale !== undefined) {
      this.maxFontScale = o2.maxFontScale;
    }
    if (o2.systemFontScale !== undefined) {
      this.systemFontScale = o2.systemFontScale;
    }
    if (o2.isPopup !== undefined) {
      this.isPopup = o2.isPopup;
    }
    if (o2.isOnFocus !== undefined) {
      this.isOnFocus = o2.isOnFocus;
    }
    if (o2.isOnHover !== undefined) {
      this.isOnHover = o2.isOnHover;
    }
    if (o2.isOnClick !== undefined) {
      this.isOnClick = o2.isOnClick;
    }
    if (o2.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (o2.dialogController !== undefined) {
      this.dialogController = o2.dialogController;
    }
  }

  updateStateVars(n2) {
    this.__fontSize.reset(n2.fontSize);
  }

  purgeVariableDependenciesOnElmtId(m2) {
    this.__isOnFocus.purgeDependencyOnElmtId(m2);
    this.__isOnHover.purgeDependencyOnElmtId(m2);
    this.__isOnClick.purgeDependencyOnElmtId(m2);
    this.__fontSize.purgeDependencyOnElmtId(m2);
  }

  aboutToBeDeleted() {
    this.__isOnFocus.aboutToBeDeleted();
    this.__isOnHover.aboutToBeDeleted();
    this.__isOnClick.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get isOnFocus() {
    return this.__isOnFocus.get();
  }

  set isOnFocus(l2) {
    this.__isOnFocus.set(l2);
  }

  get isOnHover() {
    return this.__isOnHover.get();
  }

  set isOnHover(k2) {
    this.__isOnHover.set(k2);
  }

  get isOnClick() {
    return this.__isOnClick.get();
  }

  set isOnClick(j2) {
    this.__isOnClick.set(j2);
  }

  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(i2) {
    this.__fontSize.set(i2);
  }

  textDialog() {
    if (this.item.value === PUBLIC_MORE) {
      return { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else if (this.item.value === PUBLIC_BACK) {
      return { 'id': -1, 'type': 10003, params: ['sys.string.icon_back'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else {
      return this.item.label ? this.item.label : '';
    }
  }

  getFgColor() {
    return this.isOnClick ?
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
  }

  getBgColor() {
    if (this.isOnClick) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else if (this.isOnHover) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else {
      return Color.Transparent;
    }
  }
  aboutToAppear() {
    try {
      let h = this.getUIContext();
      this.isFollowingSystemFontScale = h.isFollowingSystemFontScale();
      this.maxFontScale = h.getMaxFontScale();
    }
    catch (h2) {
      let i2 = h2.code;
      let j2 = h2.message;
      hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${i2}, message: ${j2}`);
    }
  }
  decideFontScale() {
    let k2 = this.getUIContext();
    this.systemFontScale = k2.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale, this.maxFontScale);
  }

  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((u1, v1) => {
      Row.create();
      Row.width(ImageMenuItem.imageHotZoneWidth);
      Row.height(ImageMenuItem.imageHotZoneWidth);
      Row.borderRadius(ImageMenuItem.buttonBorderRadius);
      Row.foregroundColor(this.getFgColor());
      Row.backgroundColor(this.getBgColor());
      Row.justifyContent(FlexAlign.Center);
      Row.opacity(this.item.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity);
      ViewStackProcessor.visualState('focused');
      Row.border({
        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        width: ImageMenuItem.focusBorderWidth,
        color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        style: BorderStyle.Solid,
      });
      ViewStackProcessor.visualState('normal');
      Row.border({
        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        width: 0,
      });
      ViewStackProcessor.visualState();
      Row.onFocus(() => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnFocus = true;
      });
      Row.onBlur(() => this.isOnFocus = false);
      Row.onHover((h2) => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnHover = h2;
      });
      Row.onKeyEvent((g2) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (g2.keyCode !== KeyCode.KEYCODE_ENTER && g2.keyCode !== KeyCode.KEYCODE_SPACE) {
          return;
        }
        if (g2.type === KeyType.Down) {
          this.isOnClick = true;
        }
        if (g2.type === KeyType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onTouch((f2) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (f2.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (f2.type === TouchType.Up || f2.type === TouchType.Cancel) {
          this.isOnClick = false;
          if (this.fontSize >= this.minFontSize && this.isPopup === false) {
            this.dialogController?.close();
          }
        }
      });
      Row.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
      Gesture.create(GesturePriority.Low);
      LongPressGesture.create({ repeat: false, duration: this.longPressTime });
      LongPressGesture.onAction((d2) => {
        this.fontSize = this.decideFontScale();
        if (d2) {
          if (this.fontSize >= this.minFontSize && this.isPopup === false) {
            this.dialogController?.open();
          }
        }
      });
      LongPressGesture.pop();
      Gesture.pop();
    }, Row);
    this.observeComponentCreation2((s1, t1) => {
      Image.create(this.item.value);
      Image.draggable(false);
      Image.width(ImageMenuItem.imageSize);
      Image.height(ImageMenuItem.imageSize);
      Image.focusable(this.item.isEnabled);
      Image.key(ImageMenuItem.focusablePrefix + this.index);
      Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
    }, Image);
    Row.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }

  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
ImageMenuItem.imageSize = 24;
ImageMenuItem.imageHotZoneWidth = 48;
ImageMenuItem.buttonBorderRadius = 8;
ImageMenuItem.focusBorderWidth = 2;
ImageMenuItem.disabledImageOpacity = 0.4;
ImageMenuItem.focusablePrefix = 'Id-SelectTitleBar-ImageMenuItem-';
class SelectTitleBarDialog extends ViewPU {
  constructor(i1, j1, k1, l1 = -1, m1 = undefined, n1) {
    super(i1, k1, l1, n1);
    if (typeof m1 === 'function') {
      this.paramsGenerator_ = m1;
    }
    this.SelectTitleDialog = {};
    this.callbackId = undefined;
    this.SelectTitleBarDialog = '';
    this.mainWindowStage = undefined;
    this.controller = undefined;
    this.minFontSize = 1.75;
    this.maxFontSize = 3.2;
    this.screenWidth = 640;
    this.verticalScreenLines = 6;
    this.horizontalsScreenLines = 1;
    this.__mainWindow = this.createStorageLink('mainWindow', undefined, 'mainWindow');
    this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
    this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
    this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
    this.cancel = () => {
    };
    this.confirm = () => {
    };
    this.setInitiallyProvidedValue(j1);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(h1) {
    if (h1.SelectTitleDialog !== undefined) {
      this.SelectTitleDialog = h1.SelectTitleDialog;
    }
    if (h1.callbackId !== undefined) {
      this.callbackId = h1.callbackId;
    }
    if (h1.SelectTitleBarDialog !== undefined) {
      this.SelectTitleBarDialog = h1.SelectTitleBarDialog;
    }
    if (h1.mainWindowStage !== undefined) {
      this.mainWindowStage = h1.mainWindowStage;
    }
    if (h1.controller !== undefined) {
      this.controller = h1.controller;
    }
    if (h1.minFontSize !== undefined) {
      this.minFontSize = h1.minFontSize;
    }
    if (h1.maxFontSize !== undefined) {
      this.maxFontSize = h1.maxFontSize;
    }
    if (h1.screenWidth !== undefined) {
      this.screenWidth = h1.screenWidth;
    }
    if (h1.verticalScreenLines !== undefined) {
      this.verticalScreenLines = h1.verticalScreenLines;
    }
    if (h1.horizontalsScreenLines !== undefined) {
      this.horizontalsScreenLines = h1.horizontalsScreenLines;
    }
    if (h1.fontSize !== undefined) {
      this.fontSize = h1.fontSize;
    }
    if (h1.maxLines !== undefined) {
      this.maxLines = h1.maxLines;
    }
    if (h1.cancel !== undefined) {
      this.cancel = h1.cancel;
    }
    if (h1.confirm !== undefined) {
      this.confirm = h1.confirm;
    }
  }

  updateStateVars(g1) {
  }

  purgeVariableDependenciesOnElmtId(f1) {
    this.__mainWindow.purgeDependencyOnElmtId(f1);
    this.__fontSize.purgeDependencyOnElmtId(f1);
    this.__maxLines.purgeDependencyOnElmtId(f1);
    this.__windowStandardHeight.purgeDependencyOnElmtId(f1);
  }

  aboutToBeDeleted() {
    this.__mainWindow.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    this.__maxLines.aboutToBeDeleted();
    this.__windowStandardHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(e1) {
    this.controller = e1;
  }

  get mainWindow() {
    return this.__mainWindow.get();
  }

  set mainWindow(d1) {
    this.__mainWindow.set(d1);
  }

  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(c1) {
    this.__fontSize.set(c1);
  }

  get maxLines() {
    return this.__maxLines.get();
  }

  set maxLines(b1) {
    this.__maxLines.set(b1);
  }

  get windowStandardHeight() {
    return this.__windowStandardHeight.get();
  }

  set windowStandardHeight(a1) {
    this.__windowStandardHeight.set(a1);
  }

  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((e, f) => {
      If.create();
      if (this.SelectTitleBarDialog) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((y, z) => {
            Column.create();
            Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Column);
          this.observeComponentCreation2((w, x) => {
            Image.create(this.SelectTitleDialog.value);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.margin({
              top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Image);
          this.observeComponentCreation2((u, v) => {
            Column.create();
            Column.width('100%');
            Column.padding({
              left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
          }, Column);
          this.observeComponentCreation2((s, t) => {
            Text.create(this.SelectTitleBarDialog);
            Text.fontSize(TEXT_EDITABLE_DIALOG);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(this.maxLines);
            Text.width('100%');
            Text.textAlign(TextAlign.Center);
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Text);
          Text.pop();
          Column.pop();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((l, m) => {
            Column.create();
            Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Column.justifyContent(FlexAlign.Center);
          }, Column);
          this.observeComponentCreation2((j, k) => {
            Image.create(this.SelectTitleDialog.value);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Image);
          Column.pop();
        });
      }
    }, If);
    If.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }

  async aboutToAppear() {
    let a = this.getUIContext().getHostContext();
    this.mainWindowStage = a.windowStage.getMainWindowSync();
    let b = this.mainWindowStage.getWindowProperties();
    let c = b.windowRect;
    if (px2vp(c.height) > this.screenWidth) {
      this.maxLines = this.verticalScreenLines;
    }
    else {
      this.maxLines = this.horizontalsScreenLines;
    }
  }

  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
export default {
  SelectTitleBar: SelectTitleBar,
};
