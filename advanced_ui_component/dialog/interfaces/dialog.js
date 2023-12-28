/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

const CHECKBOX_CONTAINER_HEIGHT = 48;
const CONTENT_MAX_LINES = 2;
const DIVIDER_CONTAINER_WIDTH = 16;
const DIVIDER_HEIGHT = 24;
const DIVIDER_WIDTH = 2;
const LOADING_PROGRESS_WIDTH = 40;
const LOADING_PROGRESS_HEIGHT = 48;
const ITEM_TEXT_SIZE = 14;

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
  constructor(e, o, t, r = -1) {
    super(e, t, r);
    this.controller = void 0;
    this.title = '';
    this.content = '';
    this.selectedIndex = -1;
    this.confirm = { value: '' };
    this.radioContent = [];
    this.setInitiallyProvidedValue(o);
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.controller && (this.controller = e.controller);
    void 0 !== e.title && (this.title = e.title);
    void 0 !== e.content && (this.content = e.content);
    void 0 !== e.selectedIndex && (this.selectedIndex = e.selectedIndex);
    void 0 !== e.confirm && (this.confirm = e.confirm);
    void 0 !== e.radioContent && (this.radioContent = e.radioContent);
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
  }

  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(e) {
    this.controller = e;
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
          o || Row.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.content);
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
      List.create({ space: 1 });
      List.width('100%');
      List.padding({ left: 24, right: 24, top: 8, bottom: 8 });
      List.clip(!1);
      o || List.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.radioContent, ((e, o) => {
        const t = e;
        {
          const e = !0;
          const r = (o, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o);
            ListItem.create(i, e);
            t || ListItem.pop();
            ViewStackProcessor.StopGetAccessRecording();
          };
          const s = () => {
            this.observeComponentCreation(r);
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Column.create();
              o || Column.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Row.create();
              Row.constraintSize({ minHeight: 48 });
              Row.clip(!1);
              Row.onClick((() => {
                t.action && t.action();
                this.controller.close();
              }));
              o || Row.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Text.create(t.title);
              Text.fontSize(ITEM_TEXT_SIZE);
              Text.fontWeight(FontWeight.Medium);
              Text.maxLines(CONTENT_MAX_LINES);
              Text.fontColor({
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_text_primary'],
                bundleName: '',
                moduleName: ''
              });
              Text.layoutWeight(1);
              o || Text.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            Text.pop();
            this.observeComponentCreation(((e, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Radio.create({ value: 'item.title', group: 'radioGroup' });
              Radio.size({ width: 20, height:20});
              Radio.checked(this.selectedIndex === o);
              Radio.onClick((() => {
                t.action && t.action();
                this.controller.close();
              }));
              r || Radio.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            Row.pop();
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              If.create();
              o < this.radioContent.length - 1 ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, o) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Divider.create();
                  Divider.color({
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_list_separator'],
                    bundleName: '',
                    moduleName: ''
                  });
                  o || Divider.pop();
                  ViewStackProcessor.StopGetAccessRecording();
                }));
              })) : If.branchId(1);
              t || If.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            If.pop();
            Column.pop();
            ListItem.pop();
          };
          const i = (e, s) => {
            r(e, s);
            this.updateFuncByElmtId.set(e, r);
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Column.create();
                o || Column.pop();
                ViewStackProcessor.StopGetAccessRecording();
            }));
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Row.create();
              Row.constraintSize({ minHeight: 48 });
              Row.clip(!1);
              Row.onClick((() => {
                t.action && t.action();
                this.controller.close();
              }));
              o || Row.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Text.create(t.title);
              Text.fontSize(ITEM_TEXT_SIZE);
              Text.fontWeight(FontWeight.Regular);
              Text.maxLines(CONTENT_MAX_LINES);
              Text.fontColor({
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_text_primary'],
                bundleName: '',
                moduleName: ''
              });
              Text.layoutWeight(1);
              o || Text.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            Text.pop();
            this.observeComponentCreation(((e, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Radio.create({ value: 'item.title', group: 'radioGroup' });
              Radio.size({ width: 20, height: 20 });
              Radio.checked(this.selectedIndex === o);
              Radio.onClick((() => {
                t.action && t.action();
                this.controller.close();
              }));
              r || Radio.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            Row.pop();
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              If.create();
              o < this.radioContent.length - 1 ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, o) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Divider.create();
                  Divider.color({
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_list_separator'],
                    bundleName: '',
                    moduleName: ''
                  });
                  o || Divider.pop();
                  ViewStackProcessor.StopGetAccessRecording();
                }));
              })) : If.branchId(1);
              t || If.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            If.pop();
            Column.pop();
            ListItem.pop();
          };
          e ? (() => {
            this.observeComponentCreation(r);
            ListItem.pop();
          })() : s();
        }
      }), void 0, !0, !1);
      o || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    ForEach.pop();
    List.pop();
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
      this.confirm.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Button.createWithLabel(this.confirm.value);
          Button.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_button1'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontWeight(FontWeight.Medium);
          Button.layoutWeight(1);
          Button.backgroundColor(this.confirm.background ? this.confirm.background : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontColor(this.confirm.fontColor ? this.confirm.fontColor : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary_activated'],
            bundleName: '',
            moduleName: ''
          });
          Button.onClick((() => {
            this.confirm.action && this.confirm.action();
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
  constructor(e, o, t, r = -1) {
    super(e, t, r);
    this.controller = void 0;
    this.content = '';
    this.primaryButton = { value: '' };
    this.secondaryButton = { value: '' };
    this.setInitiallyProvidedValue(o);
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.controller && (this.controller = e.controller);
    void 0 !== e.content && (this.content = e.content);
    void 0 !== e.primaryButton && (this.primaryButton = e.primaryButton);
    void 0 !== e.secondaryButton && (this.secondaryButton = e.secondaryButton);
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
  }

  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(e) {
    this.controller = e;
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

export class LoadingDialog extends ViewPU {
  constructor(e, o, t, r = -1) {
    super(e, t, r);
    this.controller = void 0;
    this.content = '';
    this.setInitiallyProvidedValue(o);
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.controller && (this.controller = e.controller);
    void 0 !== e.content && (this.content = e.content);
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
  }

  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(e) {
    this.controller = e;
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
      Row.margin({ left: 24, right: 24, top: 24, bottom: 24 });
      Row.constraintSize({ minHeight: 48 });
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
      Text.layoutWeight(1);
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      LoadingProgress.create();
      LoadingProgress.width(LOADING_PROGRESS_WIDTH);
      LoadingProgress.height(LOADING_PROGRESS_HEIGHT);
      LoadingProgress.margin({ left: 16 });
      o || LoadingProgress.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Row.pop();
    Column.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}
export default { TipsDialog, ConfirmDialog, SelectDialog, AlertDialog, LoadingDialog };