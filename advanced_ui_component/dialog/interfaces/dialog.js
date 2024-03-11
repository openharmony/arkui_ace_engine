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

const hilog = requireNapi('hilog');
const resourceManager = requireNapi('resourceManager');
const measure = requireNapi('measure');
const window = requireNapi('window');

const TITLE_MAX_LINES = 2;
const HORIZON_BUTTON_MAX_COUNT = 2;
const VERTICAL_BUTTON_MAX_COUNT = 4;
const BUTTON_DEFAULT_HEIGHT = 40;
const BUTTON_LAYOUT_WEIGHT = 1;
const CHECKBOX_CONTAINER_HEIGHT = 48;
const CONTENT_MAX_LINES = 2;
const DIVIDER_CONTAINER_WIDTH = 16;
const DIVIDER_HEIGHT = 24;
const DIVIDER_WIDTH = 2;
const LOADING_PROGRESS_WIDTH = 40;
const LOADING_PROGRESS_HEIGHT = 40;
const ITEM_TEXT_SIZE = 14;
const LOADING_MAX_LINES = 10;
const LOADING_TEXT_LAYOUT_WEIGHT = 1;
const LOADING_TEXT_MARGIN_LEFT = 12;
const LOADING_MIN_HEIGHT = 48;
const LIST_MIN_HEIGHT = 48;
const CHECKBOX_CONTAINER_LENGTH = 20;

export class TipsDialog extends ViewPU {
  constructor(e, o, t, r = -1) {
    super(e, t, r);
    this.controller = void 0;
    this.imageRes = void 0;
    this.imageSize = { width: '100%', height: 180 };
    this.title = '';
    this.content = '';
    this.checkTips = '';
    this.__isChecked = new ObservedPropertySimplePU(!1, this, 'isChecked');
    this.primaryButton = { value: '' };
    this.secondaryButton = { value: '' };
    this.setInitiallyProvidedValue(o);
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.controller && (this.controller = e.controller);
    void 0 !== e.imageRes && (this.imageRes = e.imageRes);
    void 0 !== e.imageSize && (this.imageSize = e.imageSize);
    void 0 !== e.title && (this.title = e.title);
    void 0 !== e.content && (this.content = e.content);
    void 0 !== e.checkTips && (this.checkTips = e.checkTips);
    void 0 !== e.isChecked && (this.isChecked = e.isChecked);
    void 0 !== e.primaryButton && (this.primaryButton = e.primaryButton);
    void 0 !== e.secondaryButton && (this.secondaryButton = e.secondaryButton);
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__isChecked.purgeDependencyOnElmtId(e);
  }

  aboutToBeDeleted() {
    this.__isChecked.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(e) {
    this.controller = e;
  }

  get isChecked() {
    return this.__isChecked.get();
  }

  set isChecked(e) {
    this.__isChecked.set(e);
  }

  initialRender() {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.backgroundBlurStyle(BlurStyle.Thick);
      Column.borderRadius({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_corner_radius_dialog'],
        bundleName: '',
        moduleName: ''
      });
      Column.margin({
        left: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_dialog_margin_start'],
          bundleName: '',
          moduleName: ''
        },
        right: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_dialog_margin_end'],
          bundleName: '',
          moduleName: ''
        },
        bottom: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_dialog_margin_bottom'],
          bundleName: '',
          moduleName: ''
        }
      });
      Column.backgroundColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_dialog_bg'],
        bundleName: '',
        moduleName: ''
      });
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.width('100%');
      Row.padding({ left: 24, right: 24 });
      Row.margin({ top: 24 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.layoutWeight(1);
      Column.clip(!0);
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Image.create(this.imageRes);
      Image.size(this.imageSize);
      Image.objectFit(ImageFit.Fill);
      o || Image.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Column.pop();
    Row.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.padding({ left: 24, right: 24 });
      Row.margin({ top: 16 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.title);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_headline8'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_text_primary'],
        bundleName: '',
        moduleName: ''
      });
      Text.textAlign(TextAlign.Center);
      Text.maxLines(2);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.minFontSize(15);
      Text.maxFontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_headline8"],
        bundleName: "",
        moduleName: ""
      });
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    Row.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.content ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.padding({ left: 24, right: 24, top: 8, bottom: 8 });
          Row.width('100%');
          o || Row.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.content);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body1'],
            bundleName: '',
            moduleName: ''
          });
          Text.fontWeight(FontWeight.Regular);
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            bundleName: '',
            moduleName: ''
          });
          Text.textAlign(TextAlign.Center);
          Text.minFontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body3'],
            bundleName: '',
            moduleName: ''
          });
          Text.maxLines(2);
          Text.textOverflow({ overflow: TextOverflow.Ellipsis });
          o || Text.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        Text.pop();
        Row.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.height(CHECKBOX_CONTAINER_HEIGHT);
      Row.width('100%');
      Row.padding({ left: 24, right: 24, top: 8, bottom: 8 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
      Checkbox.select(this.isChecked);
      Checkbox.onChange((e => {
        this.isChecked = e;
      }));
      Checkbox.margin({ left: 0, right: 8 });
      o || Checkbox.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Checkbox.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.checkTips);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_body2'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_text_primary'],
        bundleName: '',
        moduleName: ''
      });
      Text.maxLines(CONTENT_MAX_LINES);
      Text.layoutWeight(1);
      Text.focusOnTouch(!0);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.onClick((() => {
        this.isChecked = !this.isChecked;
      }));
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    Row.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.width('100%');
      Row.padding({ left: 16, right: 16, top: 16, bottom: 16 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.primaryButton.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Button.createWithLabel(this.primaryButton.value);
          Button.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_button1'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontWeight(FontWeight.Medium);
          Button.layoutWeight(1);
          Button.backgroundColor(this.primaryButton.background ? this.primaryButton.background : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontColor(this.primaryButton.fontColor ? this.primaryButton.fontColor : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary_activated'],
            bundleName: '',
            moduleName: ''
          });
          Button.onClick((() => {
            this.primaryButton.action && this.primaryButton.action();
            this.controller.close();
          }));
          o || Button.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        Button.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.secondaryButton.value && this.primaryButton.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Column.create();
          Column.width(DIVIDER_CONTAINER_WIDTH);
          Column.alignItems(HorizontalAlign.Center);
          o || Column.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          If.create();
          this.secondaryButton.background ? If.branchId(1) : this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Divider.create();
              Divider.width(DIVIDER_WIDTH);
              Divider.height(DIVIDER_HEIGHT);
              Divider.color({
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_list_separator'],
                bundleName: '',
                moduleName: ''
              });
              Divider.vertical(!0);
              o || Divider.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
          }));
          o || If.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        If.pop();
        Column.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.secondaryButton.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Button.createWithLabel(this.secondaryButton.value);
          Button.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_button1'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontWeight(FontWeight.Medium);
          Button.layoutWeight(1);
          Button.backgroundColor(this.secondaryButton.background ? this.secondaryButton.background : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontColor(this.secondaryButton.fontColor ? this.secondaryButton.fontColor : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary_activated'],
            bundleName: '',
            moduleName: ''
          });
          Button.onClick((() => {
            this.secondaryButton.action && this.secondaryButton.action();
            this.controller.close();
          }));
          o || Button.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        Button.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    Row.pop();
    Column.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}

export class SelectDialog extends ViewPU {
  constructor(e15, f15, g15, h15 = -1, i15 = undefined, j15) {
    super(e15, g15, h15, j15);
    if (typeof i15 === 'function') {
      this.paramsGenerator_ = i15;
    }
    this.title = '';
    this.content = '';
    this.selectedIndex = -1;
    this.confirm = { value: '' };
    this.radioContent = [];
    this.contentBuilder = this.buildContent;
    this.controller = new CustomDialogController({
      builder: () => {
        let k15;
        let l15 = new CustomContentDialog(this, {
          primaryTitle: this.title,
          contentBuilder: () => {
            this.contentBuilder();
          },
          buttons: (this.confirm === undefined || ((k15 = this.confirm) === null || k15 === void 0 ? void 0 : k15.value) === '') ? [] : [this.confirm],
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 166 });
        l15.setController(this.controller);
        ViewPU.create(l15);
        let m15 = () => {
          let p15;
          return {
            primaryTitle: this.title,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: (this.confirm === undefined || ((p15 = this.confirm) === null || p15 === void 0 ? void 0 : p15.value) === '') ? [] : [this.confirm]
          };
        };
        l15.paramsGenerator_ = m15;
      }
    }, this);
    this.setInitiallyProvidedValue(f15);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(d15) {
    if (d15.title !== undefined) {
      this.title = d15.title;
    }
    if (d15.content !== undefined) {
      this.content = d15.content;
    }
    if (d15.selectedIndex !== undefined) {
      this.selectedIndex = d15.selectedIndex;
    }
    if (d15.confirm !== undefined) {
      this.confirm = d15.confirm;
    }
    if (d15.radioContent !== undefined) {
      this.radioContent = d15.radioContent;
    }
    if (d15.contentBuilder !== undefined) {
      this.contentBuilder = d15.contentBuilder;
    }
    if (d15.controller !== undefined) {
      this.controller = d15.controller;
    }
  }
  updateStateVars(c15) {
  }
  purgeVariableDependenciesOnElmtId(b15) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(a15) {
    this.controller = a15;
  }
  buildContent(p12 = null) {
    this.observeComponentCreation((y14, z14) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y14);
      Scroll.create();
      Scroll.margin({ right: -getNumberByResource('padding_level8') });
      Scroll.scrollBar(BarState.Auto);
      if (!z14) {
        Scroll.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((w14, x14) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w14);
      Column.create();
      Column.padding({ right: { id: -1, type: 10002, params: ['sys.float.padding_level8'], bundleName: '__harDefaultBundleName__', moduleName: '__harDefaultModuleName__' } });
      if (!x14) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((m14, n14) => {
      ViewStackProcessor.StartGetAccessRecordingFor(m14);
      If.create();
      if (this.content) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((u14, v14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u14);
            Row.create();
            Row.padding({ bottom: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '__harDefaultBundleName__', moduleName: '__harDefaultModuleName__' } });
            Row.width('100%');
            if (!v14) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((s14, t14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s14);
            Text.create(this.content);
            Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Body_M'], bundleName: '__harDefaultBundleName__', moduleName: '__harDefaultModuleName__' });
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '__harDefaultBundleName__', moduleName: '__harDefaultModuleName__' });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            if (!t14) {
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
      if (!n14) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((k14, l14) => {
      ViewStackProcessor.StartGetAccessRecordingFor(k14);
      List.create({ space: 1 });
      List.width('100%');
      List.clip(false);
      if (!l14) {
        List.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((v12, w12) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v12);
      ForEach.create();
      const x12 = (z12, a13) => {
        const b13 = z12;
        {
          const c13 = (i14, j14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i14);
            d13(i14, j14);
            if (!j14) {
              ListItem.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          };
          const d13 = (g14, h14) => {
            ListItem.create(e13, true);
          };
          const e13 = (i13, j13) => {
            c13(i13, j13);
            this.updateFuncByElmtId.set(i13, c13);
            this.observeComponentCreation((e14, f14) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e14);
              Column.create();
              if (!f14) {
                Column.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            this.observeComponentCreation((b14, c14) => {
              ViewStackProcessor.StartGetAccessRecordingFor(b14);
              Row.create();
              Row.constraintSize({ minHeight: LIST_MIN_HEIGHT });
              Row.clip(false);
              Row.padding({ top: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '__harDefaultBundleName__', moduleName: '__harDefaultModuleName__' }, bottom: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '__harDefaultBundleName__', moduleName: '__harDefaultModuleName__' } });
              Row.onClick(() => {
                b13.action && b13.action();
                this.controller.close();
              });
              if (!c14) {
                Row.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            this.observeComponentCreation((z13, a14) => {
              ViewStackProcessor.StartGetAccessRecordingFor(z13);
              Text.create(b13.title);
              Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '__harDefaultBundleName__', moduleName: '__harDefaultModuleName__' });
              Text.fontWeight(FontWeight.Medium);
              Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '__harDefaultBundleName__', moduleName: '__harDefaultModuleName__' });
              Text.layoutWeight(1);
              if (!a14) {
                Text.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            Text.pop();
            this.observeComponentCreation((w13, x13) => {
              ViewStackProcessor.StartGetAccessRecordingFor(w13);
              Radio.create({ value: 'item.title', group: 'radioGroup' });
              Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
              Radio.checked(this.selectedIndex === a13);
              Radio.onClick(() => {
                b13.action && b13.action();
                this.controller.close();
              });
              if (!x13) {
                Radio.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            Row.pop();
            this.observeComponentCreation((p13, q13) => {
              ViewStackProcessor.StartGetAccessRecordingFor(p13);
              If.create();
              if (a13 < this.radioContent.length - 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation((u13, v13) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(u13);
                    Divider.create();
                    Divider.color({ id: -1, type: 10001, params: ['sys.color.comp_divider'], bundleName: '__harDefaultBundleName__', moduleName: '__harDefaultModuleName__' });
                    if (!v13) {
                      Divider.pop();
                    }
                    ViewStackProcessor.StopGetAccessRecording();
                  });
                });
              }
              else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
              }
              if (!q13) {
                If.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            If.pop();
            Column.pop();
            ListItem.pop();
          };
          this.observeComponentCreation(c13);
          ListItem.pop();
        }
      };
      this.forEachUpdateFunction(v12, this.radioContent, x12, undefined, true, false);
      if (!w12) {
        ForEach.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    ForEach.pop();
    List.pop();
    Column.pop();
    Scroll.pop();
  }
  initialRender() {
    {
      this.observeComponentCreation((j12, k12) => {
        ViewStackProcessor.StartGetAccessRecordingFor(j12);
        if (k12) {
          let l12 = new CustomDialogComponent(this, {
            controller: this.controller,
            primaryTitle: this.title,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: (this.confirm === undefined || this.confirm.value === '') ? [] : [this.confirm],
          }, undefined, j12, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 225 });
          ViewPU.create(l12);
          let m12 = () => {
            return {
              controller: this.controller,
              primaryTitle: this.title,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: (this.confirm === undefined || this.confirm.value === '') ? [] : [this.confirm]
            };
          };
          l12.paramsGenerator_ = m12;
        }
        else {
          this.updateStateVarsOfChildByElmtId(j12, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export class ConfirmDialog extends ViewPU {
  constructor(e, o, t, r = -1) {
    super(e, t, r);
    this.controller = void 0;
    this.title = '';
    this.content = '';
    this.checkTips = '';
    this.__isChecked = new ObservedPropertySimplePU(!1, this, 'isChecked');
    this.primaryButton = { value: '' };
    this.secondaryButton = { value: '' };
    this.setInitiallyProvidedValue(o);
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.controller && (this.controller = e.controller);
    void 0 !== e.title && (this.title = e.title);
    void 0 !== e.content && (this.content = e.content);
    void 0 !== e.checkTips && (this.checkTips = e.checkTips);
    void 0 !== e.isChecked && (this.isChecked = e.isChecked);
    void 0 !== e.primaryButton && (this.primaryButton = e.primaryButton);
    void 0 !== e.secondaryButton && (this.secondaryButton = e.secondaryButton);
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__isChecked.purgeDependencyOnElmtId(e);
  }

  aboutToBeDeleted() {
    this.__isChecked.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(e) {
    this.controller = e;
  }

  get isChecked() {
    return this.__isChecked.get();
  }

  set isChecked(e) {
    this.__isChecked.set(e);
  }

  initialRender() {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.backgroundBlurStyle(BlurStyle.Thick);
      Column.borderRadius({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_corner_radius_dialog'],
        bundleName: '',
        moduleName: ''
      });
      Column.margin({
        left: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_dialog_margin_start'],
          bundleName: '',
          moduleName: ''
        },
        right: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_dialog_margin_end'],
          bundleName: '',
          moduleName: ''
        },
        bottom: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_dialog_margin_bottom'],
          bundleName: '',
          moduleName: ''
        }
      });
      Column.backgroundColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_dialog_bg'],
        bundleName: '',
        moduleName: ''
      });
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.padding({ left: 24, right: 24, top: 24 });
      Row.constraintSize({ minHeight: 56 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.title);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_dialog_tittle'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(CONTENT_MAX_LINES);
      Text.minFontSize(15);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_text_primary'],
        bundleName: '',
        moduleName: ''
      });
      Text.textAlign(TextAlign.Start);
      Text.width('100%');
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    Row.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.content ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.padding({ left: 24, right: 24, top: 8, bottom: 8 });
          Row.width('100%');
          Row.constraintSize({ minHeight: 36 });
          o || Row.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.content);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body1'],
            bundleName: '',
            moduleName: ''
          });
          Text.fontWeight(FontWeight.Medium);
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            bundleName: '',
            moduleName: ''
          });
          Text.maxLines(CONTENT_MAX_LINES);
          Text.textOverflow({ overflow: TextOverflow.Ellipsis });
          Text.minFontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body3'],
            bundleName: '',
            moduleName: ''
          });
          o || Text.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        Text.pop();
        Row.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.height(CHECKBOX_CONTAINER_HEIGHT);
      Row.width('100%');
      Row.padding({ left: 24, right: 24, top: 8, bottom: 8 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
      Checkbox.select(this.isChecked);
      Checkbox.onChange((e => {
        this.isChecked = e;
      }));
      Checkbox.margin({ left: 0, right: 8 });
      o || Checkbox.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Checkbox.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.checkTips);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_body2'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_text_primary'],
        bundleName: '',
        moduleName: ''
      });
      Text.maxLines(CONTENT_MAX_LINES);
      Text.layoutWeight(1);
      Text.focusOnTouch(!0);
      Text.onClick((() => {
        this.isChecked = !this.isChecked;
      }));
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    Row.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.width('100%');
      Row.padding({ left: 16, right: 16, top: 16, bottom: 16 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.primaryButton.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Button.createWithLabel(this.primaryButton.value);
          Button.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_button1'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontWeight(FontWeight.Medium);
          Button.layoutWeight(1);
          Button.backgroundColor(this.primaryButton.background ? this.primaryButton.background : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontColor(this.primaryButton.fontColor ? this.primaryButton.fontColor : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary_activated'],
            bundleName: '',
            moduleName: ''
          });
          Button.onClick((() => {
            this.primaryButton.action && this.primaryButton.action();
            this.controller.close();
          }));
          o || Button.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        Button.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.secondaryButton.value && this.primaryButton.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Column.create();
          Column.width(DIVIDER_CONTAINER_WIDTH);
          Column.alignItems(HorizontalAlign.Center);
          o || Column.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          If.create();
          this.secondaryButton.background ? If.branchId(1) : this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Divider.create();
              Divider.width(DIVIDER_WIDTH);
              Divider.height(DIVIDER_HEIGHT);
              Divider.color({
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_list_separator'],
                bundleName: '',
                moduleName: ''
              });
              Divider.vertical(!0);
              o || Divider.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
          }));
          o || If.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        If.pop();
        Column.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.secondaryButton.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Button.createWithLabel(this.secondaryButton.value);
          Button.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_button1'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontWeight(FontWeight.Medium);
          Button.layoutWeight(1);
          Button.backgroundColor(this.secondaryButton.background ? this.secondaryButton.background : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontColor(this.secondaryButton.fontColor ? this.secondaryButton.fontColor : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary_activated'],
            bundleName: '',
            moduleName: ''
          });
          Button.onClick((() => {
            this.secondaryButton.action && this.secondaryButton.action();
            this.controller.close();
          }));
          o || Button.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        Button.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    Row.pop();
    Column.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}

export class AlertDialog extends ViewPU {
  constructor(a8, b8, c8, d8 = -1, e8 = undefined, f8) {
    super(a8, c8, d8, f8);
    if (typeof e8 === 'function') {
      this.paramsGenerator_ = e8;
    }
    this.controller = undefined;
    this.content = '';
    this.primaryButton = null;
    this.secondaryButton = null;
    this.buttons = undefined;
    this.setInitiallyProvidedValue(b8);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(z7) {
    if (z7.controller !== undefined) {
      this.controller = z7.controller;
    }
    if (z7.content !== undefined) {
      this.content = z7.content;
    }
    if (z7.primaryButton !== undefined) {
      this.primaryButton = z7.primaryButton;
    }
    if (z7.secondaryButton !== undefined) {
      this.secondaryButton = z7.secondaryButton;
    }
    if (z7.buttons !== undefined) {
      this.buttons = z7.buttons;
    }
  }
  updateStateVars(y7) {
  }
  purgeVariableDependenciesOnElmtId(x7) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(w7) {
    this.controller = w7;
  }
  initialRender() {
    {
      this.observeComponentCreation((q7, r7) => {
        ViewStackProcessor.StartGetAccessRecordingFor(q7);
        if (r7) {
          let s7 = new CustomDialogComponent(this, {
            controller: this.controller,
            contentBuilder: () => {
              this.AlertDialogContentBuilder();
            },
            buttons: this.buttons,
          }, undefined, q7, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 375 });
          ViewPU.create(s7);
          let t7 = () => {
            return {
              controller: this.controller,
              contentBuilder: () => {
                this.AlertDialogContentBuilder();
              },
              buttons: this.buttons
            };
          };
          s7.paramsGenerator_ = t7;
        }
        else {
          this.updateStateVarsOfChildByElmtId(q7, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
  }
  AlertDialogContentBuilder(f7 = null) {
    this.observeComponentCreation((n7, o7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n7);
      Column.create();
      Column.margin({ right: `${this.getMargin()}vp`, });
      if (!o7) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((l7, m7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l7);
      Scroll.create();
      Scroll.width('100%');
      if (!m7) {
        Scroll.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j7, k7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j7);
      Text.create(this.content);
      Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
      Text.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level8'], bundleName: '', moduleName: '' }, });
      Text.width(`calc(100% - ${getNumberByResource('padding_level8')}vp)`);
      Text.textAlign(this.getTextAlign());
      if (!k7) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Scroll.pop();
    Column.pop();
  }
  aboutToAppear() {
    this.initButtons();
  }
  getTextAlign() {
    let d7 = measure.measureTextSize({
      textContent: this.content,
      fontSize: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
    });
    let e7 = measure.measureTextSize({
      textContent: '1',
      fontSize: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
    });
    if (this.getTextHeight(d7) <= this.getTextHeight(e7)) {
      return TextAlign.Center;
    }
    return TextAlign.Start;
  }
  getTextHeight(c7) {
    if (c7 && c7.height !== null && c7.height !== undefined) {
      return Number(c7.height);
    }
    return 0;
  }
  initButtons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return;
    }
    this.buttons = [];
    if (this.primaryButton) {
      this.buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      this.buttons.push(this.secondaryButton);
    }
  }
  getMargin() {
    return 0 - getNumberByResource('padding_level8');
  }
  rerender() {
    this.updateDirtyElements();
  }
}

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
export class CustomContentDialog extends ViewPU {
  constructor(l6, m6, n6, o6 = -1, p6 = undefined, q6) {
    super(l6, n6, o6, q6);
    if (typeof p6 === 'function') {
      this.paramsGenerator_ = p6;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = undefined;
    this.buttons = undefined;
    this.setInitiallyProvidedValue(m6);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(k6) {
    if (k6.controller !== undefined) {
      this.controller = k6.controller;
    }
    if (k6.primaryTitle !== undefined) {
      this.primaryTitle = k6.primaryTitle;
    }
    if (k6.secondaryTitle !== undefined) {
      this.secondaryTitle = k6.secondaryTitle;
    }
    if (k6.contentBuilder !== undefined) {
      this.contentBuilder = k6.contentBuilder;
    }
    if (k6.buttons !== undefined) {
      this.buttons = k6.buttons;
    }
  }
  updateStateVars(j6) {
  }
  purgeVariableDependenciesOnElmtId(i6) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(h6) {
    this.controller = h6;
  }
  initialRender() {
    {
      this.observeComponentCreation((b6, c6) => {
        ViewStackProcessor.StartGetAccessRecordingFor(b6);
        if (c6) {
          let d6 = new CustomDialogContentComponent(this, {
            controller: this.controller,
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
          }, undefined, b6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 22 });
          ViewPU.create(d6);
          let e6 = () => {
            return {
              controller: this.controller,
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons
            };
          };
          d6.paramsGenerator_ = e6;
        }
        else {
          this.updateStateVarsOfChildByElmtId(b6, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class CustomDialogContentComponent extends ViewPU {
  constructor(u5, v5, w5, x5 = -1, y5 = undefined, z5) {
    super(u5, w5, x5, z5);
    if (typeof y5 === 'function') {
      this.paramsGenerator_ = y5;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = this.defaultContentBuilder;
    this.buttons = undefined;
    this.titleHeight = 0;
    this.__contentMaxHeight = new ObservedPropertySimplePU('', this, 'contentMaxHeight');
    this.setInitiallyProvidedValue(v5);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(t5) {
    if (t5.controller !== undefined) {
      this.controller = t5.controller;
    }
    if (t5.primaryTitle !== undefined) {
      this.primaryTitle = t5.primaryTitle;
    }
    if (t5.secondaryTitle !== undefined) {
      this.secondaryTitle = t5.secondaryTitle;
    }
    if (t5.contentBuilder !== undefined) {
      this.contentBuilder = t5.contentBuilder;
    }
    if (t5.buttons !== undefined) {
      this.buttons = t5.buttons;
    }
    if (t5.titleHeight !== undefined) {
      this.titleHeight = t5.titleHeight;
    }
    if (t5.contentMaxHeight !== undefined) {
      this.contentMaxHeight = t5.contentMaxHeight;
    }
  }
  updateStateVars(s5) {
  }
  purgeVariableDependenciesOnElmtId(r5) {
    this.__contentMaxHeight.purgeDependencyOnElmtId(r5);
  }
  aboutToBeDeleted() {
    this.__contentMaxHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  defaultContentBuilder(q5 = null) {
  }
  get contentMaxHeight() {
    return this.__contentMaxHeight.get();
  }
  set contentMaxHeight(p5) {
    this.__contentMaxHeight.set(p5);
  }
  initialRender() {
    this.observeComponentCreation((n5, o5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n5);
      Column.create();
      Column.width('100%');
      if (!o5) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j5, k5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j5);
      If.create();
      if (this.primaryTitle || this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.buildTitles.bind(this)();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!k5) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((h5, i5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h5);
      Column.create();
      Column.padding(this.getContentPadding());
      Column.constraintSize({ maxHeight: this.contentMaxHeight, });
      if (!i5) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.contentBuilder.bind(this)();
    Column.pop();
    this.observeComponentCreation((d5, e5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(d5);
      If.create();
      if (this.buttons && this.buttons.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.buildButtons.bind(this)();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!e5) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
  }
  buildTitles(v3 = null) {
    this.observeComponentCreation((u4, v4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u4);
      Column.create();
      Column.constraintSize({
        minHeight: this.getTitleAreaMinHeight(),
      });
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.padding(this.getTitleAreaPadding());
      Column.onAreaChange((x4, y4) => {
        this.titleHeight = Number(y4.height);
        this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
      });
      if (!v4) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((s4, t4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(s4);
      Row.create();
      Row.width('100%');
      if (!t4) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((q4, r4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(q4);
      Text.create(this.primaryTitle);
      Text.fontWeight(FontWeight.Bold);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
      Text.textAlign(TextAlign.Start);
      Text.maxFontSize({ id: -1, type: 10002, params: ['sys.float.Title_S'], bundleName: '', moduleName: '' });
      Text.minFontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
      Text.maxLines(TITLE_MAX_LINES);
      Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      if (!r4) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
    this.observeComponentCreation((g4, h4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g4);
      If.create();
      if (this.primaryTitle && this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((o4, p4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o4);
            Row.create();
            if (!p4) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((m4, n4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(m4);
            Divider.create();
            Divider.margin({ id: -1, type: 10002, params: ['sys.float.padding_level1'], bundleName: '', moduleName: '' });
            Divider.color(Color.Transparent);
            if (!n4) {
              Divider.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!h4) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((e4, f4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e4);
      Row.create();
      Row.width('100%');
      if (!f4) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((c4, d4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c4);
      Text.create(this.secondaryTitle);
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_secondary'], bundleName: '', moduleName: '' });
      Text.textAlign(TextAlign.Start);
      Text.maxFontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_S'], bundleName: '', moduleName: '' });
      Text.minFontSize({ id: -1, type: 10002, params: ['sys.float.Body_S'], bundleName: '', moduleName: '' });
      Text.maxLines(TITLE_MAX_LINES);
      Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      if (!d4) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
    Column.pop();
  }
  buildButtons(r3 = null) {
    this.observeComponentCreation((t3, u3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t3);
      Column.create();
      Column.width('100%');
      Column.padding(this.getOperationAreaPadding());
      if (!u3) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.buildHorizontalAlignButtons.bind(this)();
    this.buildVerticalAlignButtons.bind(this)();
    Column.pop();
  }
  buildSingleButton(i3, j3 = null) {
    this.observeComponentCreation((l3, m3) => {
      let n3;
      let o3;
      ViewStackProcessor.StartGetAccessRecordingFor(l3);
      Button.createWithLabel(i3.value);
      Button.onClick(() => {
        let q3;
        if (i3.action) {
          i3.action();
        }
        (q3 = this.controller) === null || q3 === void 0 ? void 0 : q3.close();
      });
      Button.buttonStyle((n3 = i3.buttonStyle) !== null && n3 !== void 0 ? n3 : getNumberByResource('alert_button_style'));
      Button.role((o3 = i3.role) !== null && o3 !== void 0 ? o3 : ButtonRole.NORMAL);
      Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
      if (!m3) {
        Button.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Button.pop();
  }
  buildHorizontalAlignButtons(r2 = null) {
    this.observeComponentCreation((t2, u2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t2);
      If.create();
      if (this.buttons && this.buttons.length > 0 && this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((g3, h3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g3);
            Row.create();
            if (!h3) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.buildSingleButton.bind(this)(this.buttons[0]);
          this.observeComponentCreation((z2, a3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(z2);
            If.create();
            if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((e3, f3) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e3);
                  Divider.create();
                  Divider.width({ id: -1, type: 10002, params: ['sys.float.alert_divider_width'], bundleName: '', moduleName: '' });
                  Divider.height({ id: -1, type: 10002, params: ['sys.float.alert_divider_height'], bundleName: '', moduleName: '' });
                  Divider.color({ id: -1, type: 10001, params: ['sys.color.alert_divider_color'], bundleName: '', moduleName: '' });
                  Divider.vertical(true);
                  Divider.margin({
                    left: { id: -1, type: 10002, params: ['sys.float.alert_button_horizontal_space'], bundleName: '', moduleName: '' },
                    right: { id: -1, type: 10002, params: ['sys.float.alert_button_horizontal_space'], bundleName: '', moduleName: '' },
                  });
                  if (!f3) {
                    Divider.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                this.buildSingleButton.bind(this)(this.buttons[HORIZON_BUTTON_MAX_COUNT - 1]);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
            }
            if (!a3) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!u2) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  buildVerticalAlignButtons(y1 = null) {
    this.observeComponentCreation((a2, b2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(a2);
      If.create();
      if (this.buttons && this.isVerticalAlignButton()) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((p2, q2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p2);
            Column.create();
            if (!q2) {
              Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((g2, h2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g2);
            ForEach.create();
            const i2 = (m2, n2) => {
              const o2 = m2;
              this.buildButtonWithDivider.bind(this)(n2);
            };
            this.forEachUpdateFunction(g2, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), i2, (l2) => l2.value.toString(), true, false);
            if (!h2) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!b2) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  buildButtonWithDivider(g1, h1 = null) {
    this.observeComponentCreation((j1, k1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j1);
      If.create();
      if (this.buttons && this.buttons[g1]) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((w1, x1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w1);
            Row.create();
            if (!x1) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.buildSingleButton.bind(this)(this.buttons[g1]);
          Row.pop();
          this.observeComponentCreation((p1, q1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p1);
            If.create();
            if (g1 < this.buttons.length - 1) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((u1, v1) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(u1);
                  Row.create();
                  Row.height({ id: -1, type: 10002, params: ['sys.float.alert_button_vertical_space'], bundleName: '', moduleName: '' });
                  if (!v1) {
                    Row.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                Row.pop();
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
            }
            if (!q1) {
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
      if (!k1) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  aboutToAppear() {
    if (this.primaryTitle) {
      this.titleHeight = getNumberByResource('alert_title_primary_height');
    }
    if (this.secondaryTitle) {
      this.titleHeight = getNumberByResource('alert_title_secondary_height');
    }
    this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
  }
  getButtonsHeight() {
    if (!this.buttons || this.buttons.length === 0) {
      return 0;
    }
    let f1 = getNumberByResource('alert_button_top_padding');
    if (this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
      f1 += BUTTON_DEFAULT_HEIGHT +
        getNumberByResource('alert_button_bottom_padding_horizontal');
    }
    else {
      f1 += BUTTON_DEFAULT_HEIGHT * this.buttons.length +
        (this.buttons.length - 1) * getNumberByResource('alert_button_vertical_space') +
        getNumberByResource('alert_button_bottom_padding_vertical');
    }
    return f1;
  }
  getContentPadding() {
    if ((this.primaryTitle || this.secondaryTitle) && this.buttons && this.buttons.length > 0) {
      return {
        top: 0,
        right: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        bottom: 0,
        left: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
      };
    }
    else if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: 0,
        right: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        left: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
      };
    }
    else if (this.buttons && this.buttons.length > 0) {
      return {
        top: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        bottom: 0,
        left: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
      };
    }
    else {
      return {
        top: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        left: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
      };
    }
  }
  getTitleAreaMinHeight() {
    if (this.secondaryTitle) {
      return { id: -1, type: 10002, params: ['sys.float.alert_title_secondary_height'], bundleName: '', moduleName: '' };
    }
    else if (this.primaryTitle) {
      return { id: -1, type: 10002, params: ['sys.float.alert_title_primary_height'], bundleName: '', moduleName: '' };
    }
    else {
      return 0;
    }
  }
  getTitleAreaPadding() {
    if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_top'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_right'], bundleName: '', moduleName: '' },
        left: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_left'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_bottom'], bundleName: '', moduleName: '' },
      };
    }
    return {
      top: 0,
      right: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_right'], bundleName: '', moduleName: '' },
      left: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_left'], bundleName: '', moduleName: '' },
      bottom: 0,
    };
  }
  isVerticalAlignButton() {
    if (this.buttons) {
      return this.buttons.length > HORIZON_BUTTON_MAX_COUNT;
    }
    return false;
  }
  getOperationAreaPadding() {
    if (this.isVerticalAlignButton()) {
      return {
        top: { id: -1, type: 10002, params: ['sys.float.alert_button_top_padding'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.alert_right_padding_vertical'], bundleName: '', moduleName: '' },
        left: { id: -1, type: 10002, params: ['sys.float.alert_left_padding_vertical'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.alert_button_bottom_padding_vertical'], bundleName: '', moduleName: '' },
      };
    }
    return {
      top: { id: -1, type: 10002, params: ['sys.float.alert_button_top_padding'], bundleName: '', moduleName: '' },
      right: { id: -1, type: 10002, params: ['sys.float.alert_right_padding_horizontal'], bundleName: '', moduleName: '' },
      left: { id: -1, type: 10002, params: ['sys.float.alert_left_padding_horizontal'], bundleName: '', moduleName: '' },
      bottom: { id: -1, type: 10002, params: ['sys.float.alert_button_bottom_padding_horizontal'], bundleName: '', moduleName: '' },
    };
  }
  rerender() {
    this.updateDirtyElements();
  }
}
export class CustomDialogComponent extends ViewPU {
  constructor(z, a1, b1, c1 = -1, d1 = undefined, e1) {
    super(z, b1, c1, e1);
    if (typeof d1 === 'function') {
      this.paramsGenerator_ = d1;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = undefined;
    this.buttons = undefined;
    this.__dialogWidth = new ObservedPropertySimplePU('100%', this, 'dialogWidth');
    this.setInitiallyProvidedValue(a1);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(y) {
    if (y.controller !== undefined) {
      this.controller = y.controller;
    }
    if (y.primaryTitle !== undefined) {
      this.primaryTitle = y.primaryTitle;
    }
    if (y.secondaryTitle !== undefined) {
      this.secondaryTitle = y.secondaryTitle;
    }
    if (y.contentBuilder !== undefined) {
      this.contentBuilder = y.contentBuilder;
    }
    if (y.buttons !== undefined) {
      this.buttons = y.buttons;
    }
    if (y.dialogWidth !== undefined) {
      this.dialogWidth = y.dialogWidth;
    }
  }
  updateStateVars(x) {
  }
  purgeVariableDependenciesOnElmtId(w) {
    this.__dialogWidth.purgeDependencyOnElmtId(w);
  }
  aboutToBeDeleted() {
    this.__dialogWidth.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get dialogWidth() {
    return this.__dialogWidth.get();
  }
  set dialogWidth(v) {
    this.__dialogWidth.set(v);
  }
  initialRender() {
    this.observeComponentCreation((t, u) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Column.create();
      Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
      Column.borderRadius({ id: -1, type: 10002, params: ['sys.float.alert_container_shape'], bundleName: '', moduleName: '' });
      Column.backgroundColor({ id: -1, type: 10001, params: ['sys.color.comp_background_primary'], bundleName: '', moduleName: '' });
      Column.width(this.dialogWidth);
      if (!u) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    {
      this.observeComponentCreation((n, o) => {
        ViewStackProcessor.StartGetAccessRecordingFor(n);
        if (o) {
          let p = new CustomDialogContentComponent(this, {
            controller: this.controller,
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
          }, undefined, n, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 343 });
          ViewPU.create(p);
          let q = () => {
            return {
              controller: this.controller,
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons
            };
          };
          p.paramsGenerator_ = q;
        }
        else {
          this.updateStateVarsOfChildByElmtId(n, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
    Column.pop();
  }
  aboutToAppear() {
    window.getLastWindow(getContext(this)).then((h) => {
      let i = px2vp(h.getWindowProperties().windowRect.width);
      this.dialogWidth = Math.min(i - getNumberByResource('ohos_id_dialog_margin_start') -
        getNumberByResource('ohos_id_dialog_margin_end'), getNumberByResource('alert_container_max_width'));
      h.on('windowSizeChange', (k) => {
        this.dialogWidth = Math.min(px2vp(k.width) - getNumberByResource('ohos_id_dialog_margin_start') -
          getNumberByResource('ohos_id_dialog_margin_end'), getNumberByResource('alert_container_max_width'));
      });
    }).catch((g) => {
      hilog.error(0x3900, 'Ace', `Failed to obtain the top window, code: ${g.code}, message:${g.message}`);
    });
  }
  rerender() {
    this.updateDirtyElements();
  }
}
function getNumberByResource(a) {
  try {
    return resourceManager.getSystemResourceManager().getNumberByName(a);
  }
  catch (b) {
    let c = b.code;
    let d = b.message;
    hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResource error, code: ${c}, message: ${d}`);
    return 0;
  }
}

export class LoadingDialog extends ViewPU {
  constructor(b1, c1, d1, e1 = -1, f1 = undefined, g1) {
    super(b1, d1, e1, g1);
    if (typeof f1 === 'function') {
      this.paramsGenerator_ = f1;
    }
    this.controller = undefined;
    this.content = '';
    this.setInitiallyProvidedValue(c1);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(a1) {
    if (a1.controller !== undefined) {
      this.controller = a1.controller;
    }
    if (a1.content !== undefined) {
      this.content = a1.content;
    }
  }
  updateStateVars(z) {
  }
  purgeVariableDependenciesOnElmtId(y) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(x) {
    this.controller = x;
  }
  initialRender() {
    this.observeComponentCreation((v, w) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v);
      Column.create();
      if (!w) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    {
      this.observeComponentCreation((p, q) => {
        ViewStackProcessor.StartGetAccessRecordingFor(p);
        if (q) {
          let r = new CustomDialogComponent(this, {
            controller: this.controller,
            contentBuilder: () => {
              this.contentBuilder();
            },
          }, undefined, p, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 758 });
          ViewPU.create(r);
          let s = () => {
            return {
              controller: this.controller,
              contentBuilder: () => {
                this.contentBuilder();
              }
            };
          };
          r.paramsGenerator_ = s;
        }
        else {
          this.updateStateVarsOfChildByElmtId(p, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
    Column.pop();
  }
  contentBuilder(a = null) {
    this.observeComponentCreation((l, m) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l);
      Column.create();
      if (!m) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j, k) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j);
      Row.create();
      Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
      if (!k) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((h, i) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h);
      Text.create(this.content);
      Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Body_L'], 'bundleName': '', 'moduleName': '' });
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '', 'moduleName': '' });
      Text.layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT);
      Text.maxLines(LOADING_MAX_LINES);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      if (!i) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    this.observeComponentCreation((f, g) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f);
      LoadingProgress.create();
      LoadingProgress.color({ 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '', 'moduleName': '' });
      LoadingProgress.width(LOADING_PROGRESS_WIDTH);
      LoadingProgress.height(LOADING_PROGRESS_HEIGHT);
      LoadingProgress.margin({ left: LOADING_TEXT_MARGIN_LEFT });
      if (!g) {
        LoadingProgress.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
    Column.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default { TipsDialog, ConfirmDialog, SelectDialog, AlertDialog, LoadingDialog, CustomContentDialog };