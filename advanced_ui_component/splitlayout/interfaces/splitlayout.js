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

export class splitlayout extends ViewPU {
  constructor(e, t, o, r = -1) {
    super(e, o, r);
    this.container = void 0;
    this.__sizeValue = new ObservedPropertySimplePU("", this, "sizeValue");
    this.__areaWidth = new ObservedPropertySimplePU(0, this, "areaWidth");
    this.__imageBackgroundColor = new ObservedPropertySimplePU("#19000000", this, "imageBackgroundColor");
    this.__mainImage = new SynchedPropertyObjectOneWayPU(t.mainImage, this, "mainImage");
    this.__primaryText = new SynchedPropertySimpleOneWayPU(t.primaryText, this, "primaryText");
    this.secondaryText = "私人订制新歌精选站，为你推荐专属优质新歌;为你推荐专属优质新歌";
    this.tertiaryText = "每日更新";
    this.setInitiallyProvidedValue(t)
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.container && (this.container = e.container);
    void 0 !== e.sizeValue && (this.sizeValue = e.sizeValue);
    void 0 !== e.areaWidth && (this.areaWidth = e.areaWidth);
    void 0 !== e.imageBackgroundColor && (this.imageBackgroundColor = e.imageBackgroundColor);
    void 0 !== e.primaryText ? this.__primaryText.set(e.primaryText) : this.__primaryText.set("新歌推荐");
    void 0 !== e.secondaryText && (this.secondaryText = e.secondaryText);
    void 0 !== e.tertiaryText && (this.tertiaryText = e.tertiaryText)
  }

  updateStateVars(e) {
    this.__mainImage.reset(e.mainImage);
    this.__primaryText.reset(e.primaryText)
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__sizeValue.purgeDependencyOnElmtId(e);
    this.__areaWidth.purgeDependencyOnElmtId(e);
    this.__imageBackgroundColor.purgeDependencyOnElmtId(e);
    this.__mainImage.purgeDependencyOnElmtId(e);
    this.__primaryText.purgeDependencyOnElmtId(e)
  }

  aboutToBeDeleted() {
    this.__sizeValue.aboutToBeDeleted();
    this.__areaWidth.aboutToBeDeleted();
    this.__imageBackgroundColor.aboutToBeDeleted();
    this.__mainImage.aboutToBeDeleted();
    this.__primaryText.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  get sizeValue() {
    return this.__sizeValue.get()
  }

  set sizeValue(e) {
    this.__sizeValue.set(e)
  }

  get areaWidth() {
    return this.__areaWidth.get()
  }

  set areaWidth(e) {
    this.__areaWidth.set(e)
  }

  get imageBackgroundColor() {
    return this.__imageBackgroundColor.get()
  }

  set imageBackgroundColor(e) {
    this.__imageBackgroundColor.set(e)
  }

  get mainImage() {
    return this.__mainImage.get()
  }

  set mainImage(e) {
    this.__mainImage.set(e)
  }

  get primaryText() {
    return this.__primaryText.get()
  }

  set primaryText(e) {
    this.__primaryText.set(e)
  }

  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.onAreaChange(((e, t) => {
        console.info(`Ace: on area change, oldValue is ${JSON.stringify(e)} value is ${JSON.stringify(t)}`);
        this.sizeValue = JSON.stringify(t);
        this.areaWidth = parseInt(t.width.toString(), 0);
        console.info("pingAce: on area change, oldValue is" + this.areaWidth);
        console.info("pingAce: on area change, oldValue is" + parseInt(t.height.toString(), 0))
      }));
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.areaWidth < 600 ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          GridRow.create({
            columns: 4,
            breakpoints: { reference: BreakpointsReference.WindowSize },
            direction: GridRowDirection.Row
          });
          t || GridRow.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          GridCol.create({ span: { xs: 4, sm: 4, md: 4, lg: 4 } });
          t || GridCol.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Column.create();
          t || Column.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Stack.create({ alignContent: Alignment.Bottom });
          t || Stack.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Image.create(this.mainImage);
          Stack.height("34%");
          Stack.width("100%");
          t || Image.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Column.create();
          Column.alignItems(HorizontalAlign.Center);
          Column.margin({
            left: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_max_padding_start"],
              bundleName: "",
              moduleName: ""
            },
            right: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_max_padding_end"],
              bundleName: "",
              moduleName: ""
            }
          });
          t || Column.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.primaryText);
		  Text.fontWeight(FontWeight.Medium);
          Text.textAlign(TextAlign.Center);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_headline7"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_primary"],
            bundleName: "",
            moduleName: ""
          });
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.secondaryText);
          Text.textAlign(TextAlign.Center);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body2"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_primary"],
            bundleName: "",
            moduleName: ""
          });
          Text.margin({ top: 4, bottom: 8 });
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.tertiaryText);
          Text.textAlign(TextAlign.Center);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_caption"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_secondary"],
            bundleName: "",
            moduleName: ""
          });
          Text.margin({ bottom: 24 });
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        Column.pop();
        Stack.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Column.create();
          Column.height("66%");
          Column.width("100%");
          t || Column.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.container.bind(this)();
        Column.pop();
        Column.pop();
        GridCol.pop();
        GridRow.pop()
      })) : 600 < this.areaWidth && this.areaWidth < 840 ? this.ifElseBranchUpdateFunction(1, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          GridRow.create({
            columns: 8,
            breakpoints: { reference: BreakpointsReference.WindowSize },
            direction: GridRowDirection.Row
          });
          t || GridRow.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          GridCol.create({ span: { xs: 8, sm: 8, md: 8, lg: 8 } });
          t || GridCol.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Column.create();
          t || Column.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.backgroundColor(this.imageBackgroundColor);
          Row.height("34%");
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Image.create(this.mainImage);
          Image.margin({ left: 96, right: 36 });
          Image.height("60%");
          Image.width("20%");
          t || Image.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Column.create();
		  Column.width("42%");
          Column.alignItems(HorizontalAlign.Start);
          Column.margin({ right: 96 });
          t || Column.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.primaryText);
		  Text.fontWeight(FontWeight.Medium);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_headline7"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_primary"],
            bundleName: "",
            moduleName: ""
          });
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.secondaryText);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body2"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_primary"],
            bundleName: "",
            moduleName: ""
          });
          Text.margin({ top: 4, bottom: 8 });
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.tertiaryText);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_caption"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_secondary"],
            bundleName: "",
            moduleName: ""
          });
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        Column.pop();
        Row.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Column.create();
          Column.height("66%");
          t || Column.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.container.bind(this)();
        Column.pop();
        Column.pop();
        GridCol.pop();
        GridRow.pop()
      })) : this.areaWidth > 840 && this.ifElseBranchUpdateFunction(2, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          GridRow.create({
            columns: 12,
            breakpoints: { reference: BreakpointsReference.WindowSize },
            direction: GridRowDirection.Row
          });
          t || GridRow.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          GridCol.create({ span: { xs: 4, sm: 4, md: 4, lg: 4 } });
          GridCol.height("100%");
          t || GridCol.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Column.create();
          Column.height("100%");
          Column.backgroundColor(this.imageBackgroundColor);
          Column.justifyContent(FlexAlign.Center);
          Column.alignItems(HorizontalAlign.Center);
          t || Column.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Image.create(this.mainImage);
          Image.height("17%");
          Image.width("34%");
          Image.margin({ bottom: 36 });
          t || Image.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.primaryText);
          Text.textAlign(TextAlign.Center);
		  Text.fontWeight(FontWeight.Medium);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_headline7"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_primary"],
            bundleName: "",
            moduleName: ""
          });
          Text.margin({ left: 48, right: 48 });
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.secondaryText);
          Text.textAlign(TextAlign.Center);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body2"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_primary"],
            bundleName: "",
            moduleName: ""
          });
          Text.margin({ top: 4, bottom: 8, left: 48, right: 48 });
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.tertiaryText);
          Text.textAlign(TextAlign.Center);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_caption"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_secondary"],
            bundleName: "",
            moduleName: ""
          });
          Text.margin({ left: 48, right: 48 });
          t || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        Column.pop();
        GridCol.pop();
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          GridCol.create({ span: { xs: 8, sm: 8, md: 8, lg: 8 } });
          t || GridCol.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.container.bind(this)();
        GridCol.pop();
        GridRow.pop()
      }));
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    Column.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}