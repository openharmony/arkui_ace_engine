/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
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
const hilog = requireNapi('ohos.hilog');
const PUBLIC_MORE = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
class ComposeTitleBar extends ViewPU {
  constructor(k10, l10, m10, n10 = -1, o10 = undefined, p10) {
    super(k10, m10, n10, p10);
    if (typeof o10 === 'function') {
      this.paramsGenerator_ = o10;
    }
    this.item = undefined;
    this.title = '';
    this.subtitle = '';
    this.menuItems = [];
    this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, 'titleMaxWidth');
    this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
    this.setInitiallyProvidedValue(l10);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(j10) {
    if (j10.item !== undefined) {
      this.item = j10.item;
    }
    if (j10.title !== undefined) {
      this.title = j10.title;
    }
    if (j10.subtitle !== undefined) {
      this.subtitle = j10.subtitle;
    }
    if (j10.menuItems !== undefined) {
      this.menuItems = j10.menuItems;
    }
    if (j10.titleMaxWidth !== undefined) {
      this.titleMaxWidth = j10.titleMaxWidth;
    }
    if (j10.fontSize !== undefined) {
      this.fontSize = j10.fontSize;
    }
  }
  updateStateVars(i10) {
  }
  purgeVariableDependenciesOnElmtId(h10) {
    this.__titleMaxWidth.purgeDependencyOnElmtId(h10);
    this.__fontSize.purgeDependencyOnElmtId(h10);
  }
  aboutToBeDeleted() {
    this.__titleMaxWidth.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get titleMaxWidth() {
    return this.__titleMaxWidth.get();
  }
  set titleMaxWidth(g10) {
    this.__titleMaxWidth.set(g10);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(f10) {
    this.__fontSize.set(f10);
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation((y9, z9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y9);
      Flex.create({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      });
      Flex.width('100%');
      Flex.height(ComposeTitleBar.totalHeight);
      Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Flex.onAreaChange((b10, c10) => {
        let d10 = Number(c10.width);
        if (this.menuItems !== undefined) {
          let e10 = this.menuItems.length;
          if (e10 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
            d10 = d10 - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
          }
          else if (e10 > 0) {
            d10 = d10 - ImageMenuItem.imageHotZoneWidth * e10;
          }
        }
        this.titleMaxWidth = d10;
        this.titleMaxWidth -= ComposeTitleBar.leftPadding;
        this.titleMaxWidth -= ImageMenuItem.imageHotZoneWidth;
        if (this.item !== undefined) {
          this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding +
          ComposeTitleBar.portraitImageSize +
          ComposeTitleBar.portraitImageRightPadding;
        }
        this.titleMaxWidth -= ComposeTitleBar.rightPadding;
      });
      if (!z9) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((w9, x9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w9);
      Row.create();
      Row.margin({ left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
      if (!x9) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    {
      this.observeComponentCreation((q9, r9) => {
        ViewStackProcessor.StartGetAccessRecordingFor(q9);
        if (r9) {
          let s9 = new ImageMenuItem(this, { item: {
            value: PUBLIC_BACK,
            isEnabled: true,
            action: () => this.getUIContext()?.getRouter()?.back()
          }, index: -1 }, undefined, q9, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 60, col: 9 });
          ViewPU.create(s9);
          let t9 = () => {
            return {
              item: {
                value: PUBLIC_BACK,
                isEnabled: true,
                action: () => this.getUIContext()?.getRouter()?.back()
              },
              index: -1
            };
          };
          s9.paramsGenerator_ = t9;
        }
        else {
          this.updateStateVarsOfChildByElmtId(q9, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
    this.observeComponentCreation((i9, j9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i9);
      If.create();
      if (this.item !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((n9, o9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n9);
            Image.create(this.item.value);
            Image.width(ComposeTitleBar.portraitImageSize);
            Image.height(ComposeTitleBar.portraitImageSize);
            Image.margin({
              left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
            });
            Image.focusable(false);
            Image.borderRadius(ImageMenuItem.buttonBorderRadius);
            if (!o9) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!j9) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((g9, h9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g9);
      Column.create();
      Column.justifyContent(FlexAlign.Start);
      Column.alignItems(HorizontalAlign.Start);
      Column.constraintSize({ maxWidth: this.titleMaxWidth });
      if (!h9) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((w8, x8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w8);
      If.create();
      if (this.title !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((e9, f9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e9);
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            if (!f9) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((c9, d9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c9);
            Text.create(this.title);
            Text.fontWeight(FontWeight.Medium);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.maxLines(this.subtitle !== undefined ? 1 : 2);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ maxWidth: this.titleMaxWidth });
            if (!d9) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!x8) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((m8, n8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(m8);
      If.create();
      if (this.subtitle !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((u8, v8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u8);
            Row.create();
            Row.justifyContent(FlexAlign.Start);
            if (!v8) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((s8, t8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s8);
            Text.create(this.subtitle);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_over_line'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.constraintSize({ maxWidth: this.titleMaxWidth });
            if (!t8) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!n8) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
    Row.pop();
    this.observeComponentCreation((b8, c8) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b8);
      If.create();
      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          {
            this.observeComponentCreation((g8, h8) => {
              ViewStackProcessor.StartGetAccessRecordingFor(g8);
              if (h8) {
                let i8 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ }, undefined, g8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 110, col: 9 });
                ViewPU.create(i8);
                let j8 = () => {
                  return {
                    menuItems: this.menuItems,
                    index: 1 + ComposeTitleBar.instanceCount++
                  };
                };
                i8.paramsGenerator_ = j8;
              }
              else {
                this.updateStateVarsOfChildByElmtId(g8, {});
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
          }
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c8) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
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
ComposeTitleBar.totalHeight = 56;
ComposeTitleBar.leftPadding = 12;
ComposeTitleBar.rightPadding = 12;
ComposeTitleBar.portraitImageSize = 40;
ComposeTitleBar.portraitImageLeftPadding = 4;
ComposeTitleBar.portraitImageRightPadding = 16;
ComposeTitleBar.instanceCount = 0;
class CollapsibleMenuSection extends ViewPU {
  constructor(k7, l7, m7, n7 = -1, o7 = undefined, p7) {
    super(k7, m7, n7, p7);
    if (typeof o7 === 'function') {
      this.paramsGenerator_ = o7;
    }
    this.menuItems = [];
    this.item = {
      value: PUBLIC_MORE,
      label: { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
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
        let q7 = new ComposeTitleBarDialog(this, {
          cancel: () => {
          },
          confirm: () => {
          },
          itemComposeTitleDialog: this.item,
          composeTitleBarDialog: this.item.label ? this.item.label : '',
          fontSize: this.fontSize,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 166, col: 14 });
        q7.setController(this.dialogController);
        ViewPU.create(q7);
        let r7 = () => {
          return {
            cancel: () => {
            },
            confirm: () => {
            },
            itemComposeTitleDialog: this.item,
            composeTitleBarDialog: this.item.label ? this.item.label : '',
            fontSize: this.fontSize
          };
        };
        q7.paramsGenerator_ = r7;
      },
      maskColor: Color.Transparent,
      isModal: true,
      customStyle: true
    }, this);
    this.setInitiallyProvidedValue(l7);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(j7) {
    if (j7.menuItems !== undefined) {
      this.menuItems = j7.menuItems;
    }
    if (j7.item !== undefined) {
      this.item = j7.item;
    }
    if (j7.index !== undefined) {
      this.index = j7.index;
    }
    if (j7.longPressTime !== undefined) {
      this.longPressTime = j7.longPressTime;
    }
    if (j7.minFontSize !== undefined) {
      this.minFontSize = j7.minFontSize;
    }
    if (j7.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = j7.isFollowingSystemFontScale;
    }
    if (j7.maxFontScale !== undefined) {
      this.maxFontScale = j7.maxFontScale;
    }
    if (j7.systemFontScale !== undefined) {
      this.systemFontScale = j7.systemFontScale;
    }
    if (j7.firstFocusableIndex !== undefined) {
      this.firstFocusableIndex = j7.firstFocusableIndex;
    }
    if (j7.isPopupShown !== undefined) {
      this.isPopupShown = j7.isPopupShown;
    }
    if (j7.isMoreIconOnFocus !== undefined) {
      this.isMoreIconOnFocus = j7.isMoreIconOnFocus;
    }
    if (j7.isMoreIconOnHover !== undefined) {
      this.isMoreIconOnHover = j7.isMoreIconOnHover;
    }
    if (j7.isMoreIconOnClick !== undefined) {
      this.isMoreIconOnClick = j7.isMoreIconOnClick;
    }
    if (j7.fontSize !== undefined) {
      this.fontSize = j7.fontSize;
    }
    if (j7.dialogController !== undefined) {
      this.dialogController = j7.dialogController;
    }
  }
  updateStateVars(i7) {
  }
  purgeVariableDependenciesOnElmtId(h7) {
    this.__isPopupShown.purgeDependencyOnElmtId(h7);
    this.__isMoreIconOnFocus.purgeDependencyOnElmtId(h7);
    this.__isMoreIconOnHover.purgeDependencyOnElmtId(h7);
    this.__isMoreIconOnClick.purgeDependencyOnElmtId(h7);
    this.__fontSize.purgeDependencyOnElmtId(h7);
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
  set isPopupShown(g7) {
    this.__isPopupShown.set(g7);
  }
  get isMoreIconOnFocus() {
    return this.__isMoreIconOnFocus.get();
  }
  set isMoreIconOnFocus(f7) {
    this.__isMoreIconOnFocus.set(f7);
  }
  get isMoreIconOnHover() {
    return this.__isMoreIconOnHover.get();
  }
  set isMoreIconOnHover(e7) {
    this.__isMoreIconOnHover.set(e7);
  }
  get isMoreIconOnClick() {
    return this.__isMoreIconOnClick.get();
  }
  set isMoreIconOnClick(d7) {
    this.__isMoreIconOnClick.set(d7);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(c7) {
    this.__fontSize.set(c7);
  }
  getMoreIconFgColor() {
    return this.isMoreIconOnClick ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
  }
  getMoreIconBgColor() {
    if (this.isMoreIconOnClick) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    else if (this.isMoreIconOnHover) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    else {
      return Color.Transparent;
    }
  }
  aboutToAppear() {
    try {
      let b7 = this.getUIContext();
      this.isFollowingSystemFontScale = b7.isFollowingSystemFontScale();
      this.maxFontScale = b7.getMaxFontScale();
    }
    catch (y6) {
      let z6 = y6.code;
      let a7 = y6.message;
      hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${z6}, message: ${a7}`);
    }
    if (this.menuItems) {
      this.menuItems.forEach((w6, x6) => {
        if (w6.isEnabled && this.firstFocusableIndex == -1 &&
          x6 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
          this.firstFocusableIndex = this.index * 1000 + x6 + 1;
        }
      });
    }
  }
  decideFontScale() {
    try {
      let u6 = this.getUIContext();
      this.systemFontScale = u6.getHostContext()?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
    }
    catch (r6) {
      let s6 = r6.code;
      let t6 = r6.message;
      hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${s6}, message: ${t6}`);
      return 1;
    }
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation((p6, q6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(p6);
      Column.create();
      Column.height('100%');
      Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
      Column.justifyContent(FlexAlign.Center);
      if (!q6) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((n6, o6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n6);
      Row.create();
      if (!o6) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((i4, j4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i4);
      If.create();
      if (this.menuItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((n4, o4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n4);
            If.create();
            if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((z5, a6) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(z5);
                  ForEach.create();
                  const b6 = (d6, e6) => {
                    const f6 = d6;
                    {
                      this.observeComponentCreation((h6, i6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(h6);
                        if (i6) {
                          let j6 = new ImageMenuItem(this, { item: f6, index: this.index * 1000 + e6 + 1 }, undefined, h6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 239, col: 15 });
                          ViewPU.create(j6);
                          let k6 = () => {
                            return {
                              item: f6,
                              index: this.index * 1000 + e6 + 1
                            };
                          };
                          j6.paramsGenerator_ = k6;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(h6, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                      });
                    }
                  };
                  this.forEachUpdateFunction(z5, this.menuItems, b6, undefined, true, false);
                  if (!a6) {
                    ForEach.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                ForEach.pop();
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation((j5, k5) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(j5);
                  ForEach.create();
                  const l5 = (n5, o5) => {
                    const p5 = n5;
                    {
                      this.observeComponentCreation((r5, s5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(r5);
                        if (s5) {
                          let t5 = new ImageMenuItem(this, { item: p5, index: this.index * 1000 + o5 + 1 }, undefined, r5, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 244, col: 17 });
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
                        ViewStackProcessor.StopGetAccessRecording();
                      });
                    }
                  };
                  this.forEachUpdateFunction(j5, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), l5, undefined, true, false);
                  if (!k5) {
                    ForEach.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                ForEach.pop();
                this.observeComponentCreation((v4, w4) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(v4);
                  Row.create();
                  Row.width(ImageMenuItem.imageHotZoneWidth);
                  Row.height(ImageMenuItem.imageHotZoneWidth);
                  Row.borderRadius(ImageMenuItem.buttonBorderRadius);
                  Row.foregroundColor(this.getMoreIconFgColor());
                  Row.backgroundColor(this.getMoreIconBgColor());
                  Row.justifyContent(FlexAlign.Center);
                  ViewStackProcessor.visualState('focused');
                  Row.border({
                    radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                    width: ImageMenuItem.focusBorderWidth,
                    color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                    style: BorderStyle.Solid
                  });
                  ViewStackProcessor.visualState('normal');
                  Row.border({
                    radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                    width: 0
                  });
                  ViewStackProcessor.visualState();
                  Row.onFocus(() => this.isMoreIconOnFocus = true);
                  Row.onBlur(() => this.isMoreIconOnFocus = false);
                  Row.onHover((i5) => this.isMoreIconOnHover = i5);
                  Row.onKeyEvent((h5) => {
                    if (h5.keyCode !== KeyCode.KEYCODE_ENTER &&
                      h5.keyCode !== KeyCode.KEYCODE_SPACE) {
                      return;
                    }
                    if (h5.type === KeyType.Down) {
                      this.isMoreIconOnClick = true;
                    }
                    if (h5.type === KeyType.Up) {
                      this.isMoreIconOnClick = false;
                    }
                  });
                  Row.onTouch((g5) => {
                    if (g5.type === TouchType.Down) {
                      this.isMoreIconOnClick = true;
                    }
                    if (g5.type === TouchType.Up || g5.type === TouchType.Cancel) {
                      this.isMoreIconOnClick = false;
                      if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.close();
                      }
                    }
                  });
                  Row.onClick(() => this.isPopupShown = true);
                  Gesture.create(GesturePriority.Low);
                  LongPressGesture.create({ repeat: false, duration: this.longPressTime });
                  LongPressGesture.onAction((f5) => {
                    this.fontSize = this.decideFontScale();
                    if (f5) {
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
                    onStateChange: (e5) => {
                      this.isPopupShown = e5.isVisible;
                      if (!e5.isVisible) {
                        this.isMoreIconOnClick = false;
                      }
                    }
                  });
                  if (!w4) {
                    Row.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                this.observeComponentCreation((t4, u4) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(t4);
                  Image.create(PUBLIC_MORE);
                  Image.width(ImageMenuItem.imageSize);
                  Image.draggable(false);
                  Image.height(ImageMenuItem.imageSize);
                  Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                  Image.focusable(true);
                  if (!u4) {
                    Image.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                Row.pop();
              });
            }
            if (!o4) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!j4) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Row.pop();
    Column.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  popupBuilder(g3 = null) {
    this.observeComponentCreation((c4, d4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c4);
      Column.create();
      Column.width(ImageMenuItem.imageHotZoneWidth +
        CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
      Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
      Column.onAppear(() => {
        focusControl.requestFocus(ImageMenuItem.focusablePrefix +
        this.firstFocusableIndex);
      });
      if (!d4) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j3, k3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j3);
      If.create();
      if (this.menuItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((o3, p3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o3);
            ForEach.create();
            const q3 = (s3, t3) => {
              const u3 = s3;
              {
                this.observeComponentCreation((w3, x3) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(w3);
                  if (x3) {
                    let y3 = new ImageMenuItem(this, { item: u3, index: this.index * 1000 +
                    CollapsibleMenuSection.maxCountOfVisibleItems + t3, isPopup: true }, undefined, w3, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 342, col: 13 });
                    ViewPU.create(y3);
                    let z3 = () => {
                      return {
                        item: u3,
                        index: this.index * 1000 +
                        CollapsibleMenuSection.maxCountOfVisibleItems + t3,
                        isPopup: true
                      };
                    };
                    y3.paramsGenerator_ = z3;
                  }
                  else {
                    this.updateStateVarsOfChildByElmtId(w3, {});
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              }
            };
            this.forEachUpdateFunction(o3, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), q3, undefined, true, false);
            if (!p3) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!k3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
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
  constructor(w2, x2, y2, z2 = -1, a3 = undefined, b3) {
    super(w2, y2, z2, b3);
    if (typeof a3 === 'function') {
      this.paramsGenerator_ = a3;
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
    this.__fontSize = new SynchedPropertySimpleOneWayPU(x2.fontSize, this, 'fontSize');
    this.dialogController = new CustomDialogController({
      builder: () => {
        let c3 = new ComposeTitleBarDialog(this, {
          cancel: () => {
          },
          confirm: () => {
          },
          itemComposeTitleDialog: this.item,
          composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
          fontSize: this.fontSize,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 381, col: 14 });
        c3.setController(this.dialogController);
        ViewPU.create(c3);
        let d3 = () => {
          return {
            cancel: () => {
            },
            confirm: () => {
            },
            itemComposeTitleDialog: this.item,
            composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
            fontSize: this.fontSize
          };
        };
        c3.paramsGenerator_ = d3;
      },
      maskColor: Color.Transparent,
      isModal: true,
      customStyle: true
    }, this);
    this.setInitiallyProvidedValue(x2);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(v2) {
    if (v2.item !== undefined) {
      this.item = v2.item;
    }
    if (v2.index !== undefined) {
      this.index = v2.index;
    }
    if (v2.longPressTime !== undefined) {
      this.longPressTime = v2.longPressTime;
    }
    if (v2.minFontSize !== undefined) {
      this.minFontSize = v2.minFontSize;
    }
    if (v2.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = v2.isFollowingSystemFontScale;
    }
    if (v2.maxFontScale !== undefined) {
      this.maxFontScale = v2.maxFontScale;
    }
    if (v2.systemFontScale !== undefined) {
      this.systemFontScale = v2.systemFontScale;
    }
    if (v2.isPopup !== undefined) {
      this.isPopup = v2.isPopup;
    }
    if (v2.isOnFocus !== undefined) {
      this.isOnFocus = v2.isOnFocus;
    }
    if (v2.isOnHover !== undefined) {
      this.isOnHover = v2.isOnHover;
    }
    if (v2.isOnClick !== undefined) {
      this.isOnClick = v2.isOnClick;
    }
    if (v2.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (v2.dialogController !== undefined) {
      this.dialogController = v2.dialogController;
    }
  }
  updateStateVars(u2) {
    this.__fontSize.reset(u2.fontSize);
  }
  purgeVariableDependenciesOnElmtId(t2) {
    this.__isOnFocus.purgeDependencyOnElmtId(t2);
    this.__isOnHover.purgeDependencyOnElmtId(t2);
    this.__isOnClick.purgeDependencyOnElmtId(t2);
    this.__fontSize.purgeDependencyOnElmtId(t2);
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
  set isOnFocus(s2) {
    this.__isOnFocus.set(s2);
  }
  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(r2) {
    this.__isOnHover.set(r2);
  }
  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(q2) {
    this.__isOnClick.set(q2);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(p2) {
    this.__fontSize.set(p2);
  }
  textDialog() {
    if (this.item.value === PUBLIC_MORE) {
      return { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    else if (this.item.value === PUBLIC_BACK) {
      return { 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    else {
      return this.item.label ? this.item.label : '';
    }
  }
  getFgColor() {
    return this.isOnClick
      ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
  }
  getBgColor() {
    if (this.isOnClick) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    else if (this.isOnHover) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    else {
      return Color.Transparent;
    }
  }
  aboutToAppear() {
    try {
      let o2 = this.getUIContext();
      this.isFollowingSystemFontScale = o2.isFollowingSystemFontScale();
      this.maxFontScale = o2.getMaxFontScale();
    }
    catch (l2) {
      let m2 = l2.code;
      let n2 = l2.message;
      hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${m2}, message: ${n2}`);
    }
  }
  decideFontScale() {
    try {
      let k2 = this.getUIContext();
      this.systemFontScale = k2.getHostContext()?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
    }
    catch (h2) {
      let i2 = h2.code;
      let j2 = h2.message;
      hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${i2}, message: ${j2}`);
      return 1;
    }
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation((u1, v1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u1);
      Row.create();
      Row.enabled(this.item.isEnabled);
      Row.width(ImageMenuItem.imageHotZoneWidth);
      Row.height(ImageMenuItem.imageHotZoneWidth);
      Row.borderRadius(ImageMenuItem.buttonBorderRadius);
      Row.foregroundColor(this.getFgColor());
      Row.backgroundColor(this.getBgColor());
      Row.justifyContent(FlexAlign.Center);
      Row.opacity(this.item?.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity);
      ViewStackProcessor.visualState('focused');
      Row.border({
        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        width: ImageMenuItem.focusBorderWidth,
        color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        style: BorderStyle.Solid
      });
      ViewStackProcessor.visualState('normal');
      Row.border({
        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        width: 0
      });
      ViewStackProcessor.visualState();
      Row.onFocus(() => {
        if (!this.item?.isEnabled) {
          return;
        }
        this.isOnFocus = true;
      });
      Row.onBlur(() => this.isOnFocus = false);
      Row.onHover((g2) => {
        if (!this.item?.isEnabled) {
          return;
        }
        this.isOnHover = g2;
      });
      Row.onKeyEvent((f2) => {
        if (!this.item?.isEnabled) {
          return;
        }
        if (f2.keyCode !== KeyCode.KEYCODE_ENTER &&
          f2.keyCode !== KeyCode.KEYCODE_SPACE) {
          return;
        }
        if (f2.type === KeyType.Down) {
          this.isOnClick = true;
        }
        if (f2.type === KeyType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onTouch((e2) => {
        if (!this.item?.isEnabled) {
          return;
        }
        if (e2.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (e2.type === TouchType.Up || e2.type === TouchType.Cancel) {
          this.isOnClick = false;
          if (this.fontSize >= this.minFontSize && this.isPopup === false) {
            this.dialogController?.close();
          }
        }
      });
      Row.onClick(() => {
        if (this.item) {
          return this.item.isEnabled && this.item.action?.();
        }
      });
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
      if (!v1) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((s1, t1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(s1);
      Image.create(this.item?.value);
      Image.matchTextDirection(this.item?.value === PUBLIC_BACK ? true : false);
      Image.width(ImageMenuItem.imageSize);
      Image.draggable(false);
      Image.height(ImageMenuItem.imageSize);
      Image.focusable(this.item?.isEnabled);
      Image.key(ImageMenuItem.focusablePrefix + this.index);
      Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      if (!t1) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
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
ImageMenuItem.focusablePrefix = 'Id-ComposeTitleBar-ImageMenuItem-';
class ComposeTitleBarDialog extends ViewPU {
  constructor(i1, j1, k1, l1 = -1, m1 = undefined, n1) {
    super(i1, k1, l1, n1);
    if (typeof m1 === 'function') {
      this.paramsGenerator_ = m1;
    }
    this.itemComposeTitleDialog = {};
    this.callbackId = undefined;
    this.composeTitleBarDialog = '';
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
    if (h1.itemComposeTitleDialog !== undefined) {
      this.itemComposeTitleDialog = h1.itemComposeTitleDialog;
    }
    if (h1.callbackId !== undefined) {
      this.callbackId = h1.callbackId;
    }
    if (h1.composeTitleBarDialog !== undefined) {
      this.composeTitleBarDialog = h1.composeTitleBarDialog;
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
    this.observeComponentCreation((e, f) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      if (this.composeTitleBarDialog) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((y, z) => {
            ViewStackProcessor.StartGetAccessRecordingFor(y);
            Column.create();
            Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!z) {
              Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((w, x) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w);
            Image.create(this.itemComposeTitleDialog.value);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.margin({
              top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!x) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((u, v) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u);
            Column.create();
            Column.width('100%');
            Column.padding({
              left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            if (!v) {
              Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((s, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s);
            Text.create(this.composeTitleBarDialog);
            Text.fontSize(TEXT_EDITABLE_DIALOG);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(this.maxLines);
            Text.width('100%');
            Text.textAlign(TextAlign.Center);
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!t) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Column.pop();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation((l, m) => {
            ViewStackProcessor.StartGetAccessRecordingFor(l);
            Column.create();
            Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Column.justifyContent(FlexAlign.Center);
            if (!m) {
              Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((j, k) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j);
            Image.create(this.itemComposeTitleDialog.value);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!k) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Column.pop();
        });
      }
      if (!f) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
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
  ComposeTitleBar: ComposeTitleBar
};
