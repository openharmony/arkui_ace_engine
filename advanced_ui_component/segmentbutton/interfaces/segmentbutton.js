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

var __decorate = this && this.__decorate || function (t, e, o, s) {
    var i, n = arguments.length, r = n < 3 ? e : null === s ? s = Object.getOwnPropertyDescriptor(e, o) : s;
    if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) r = Reflect.decorate(t, e, o, s); else for (var d = t.length - 1;d >= 0; d--) (i = t[d]) && (r = (n < 3 ? i(r) : n > 3 ? i(e, o, r) : i(e, o)) || r);
    return n > 3 && r && Object.defineProperty(e, o, r), r
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
const curves = globalThis.requireNativeModule("ohos.curves");
const KeyCode = globalThis.requireNapi("multimodalInput.keyCode").KeyCode;
const MIN_ITEM_COUNT = 2;
const MAX_ITEM_COUNT = 5;
let SegmentButtonItemOptions = class {
    constructor(t) {
        this.icon = t.icon;
        this.selectedIcon = t.selectedIcon;
        this.text = t.text
    }
};
SegmentButtonItemOptions = __decorate([Observed], SegmentButtonItemOptions);
let SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = class extends Array {
    constructor(t) {
        super();
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        if (t.length < 2) throw new RangeError("Below the minimum number of elements (2).");
        if (t.length > 5) throw new RangeError("Exceeded the maximum number of elements (5).");
        super.push(...t.map((t => new SegmentButtonItemOptions(t))))
    }

    push(...t) {
        if (this.length + t.length > 5) throw new RangeError("Exceeded the maximum number of elements (5).");
        this.changeStartIndex = this.length - 1;
        this.deleteCount = 0;
        this.addLength = t.length;
        return super.push(...t.map((t => new SegmentButtonItemOptions(t))))
    }

    pop() {
        if (this.length <= 2) throw new RangeError("Below the minimum number of elements (2).");
        this.changeStartIndex = this.length - 1;
        this.deleteCount = 1;
        this.addLength = 0;
        return super.pop()
    }

    shift() {
        if (this.length <= 2) throw new RangeError("Below the minimum number of elements (2).");
        this.changeStartIndex = 0;
        this.deleteCount = 1;
        this.addLength = 0;
        return super.shift()
    }

    unshift(...t) {
        if (this.length + t.length > 5) throw new RangeError("Exceeded the maximum number of elements (5).");
        this.changeStartIndex = 0;
        this.deleteCount = 0;
        this.addLength = 1;
        return super.unshift(...t.map((t => new SegmentButtonItemOptions(t))))
    }

    splice(t, e, ...o) {
        if (e > 5 || this.length - e + o.length < 2) throw new RangeError("Below the minimum number of elements (2).");
        if (this.length - e + o.length > 5) throw new RangeError("Exceeded the maximum number of elements (5).");
        this.changeStartIndex = t;
        this.deleteCount = e;
        this.addLength = o.length;
        return super.splice(t, e, ...o)
    }

    static create(t) {
        return new SegmentButtonItemOptionsArray_1(t)
    }
};
SegmentButtonItemOptionsArray = SegmentButtonItemOptionsArray_1 = __decorate([Observed], SegmentButtonItemOptionsArray);

let SegmentButtonOptions = SegmentButtonOptions_1 = class {
    constructor(t) {
        var e, o, s, i, n, r, d, a, h, c, p, u, l, m, _;
        this.multiply = !1;
        this.showText = !1;
        this.showIcon = !1;
        this.fontColor = null !== (e = t.fontColor) && void 0 !== e ? e : {
                                                                              id: -1,
                                                                              type: 10001,
                                                                              params: ["sys.color.ohos_id_color_text_secondary"],
                                                                              bundleName: "",
                                                                              moduleName: ""
                                                                          };
        this.selectedFontColor = null !== (o = t.selectedFontColor) && void 0 !== o ? o : {
                                                                                              id: -1,
                                                                                              type: 10001,
                                                                                              params: ["sys.color.ohos_id_color_text_primary"],
                                                                                              bundleName: "",
                                                                                              moduleName: ""
                                                                                          };
        this.fontSize = null !== (s = t.fontSize) && void 0 !== s ? s : {
                                                                            id: -1,
                                                                            type: 10002,
                                                                            params: ["sys.float.ohos_id_text_size_body2"],
                                                                            bundleName: "",
                                                                            moduleName: ""
                                                                        };
        this.selectedFontSize = null !== (i = t.selectedFontSize) && void 0 !== i ? i : {
                                                                                            id: -1,
                                                                                            type: 10002,
                                                                                            params: ["sys.float.ohos_id_text_size_body2"],
                                                                                            bundleName: "",
                                                                                            moduleName: ""
                                                                                        };
        this.fontWeight = null !== (n = t.fontWeight) && void 0 !== n ? n : FontWeight.Regular;
        this.selectedFontWeight = null !== (r = t.selectedFontWeight) && void 0 !== r ? r : FontWeight.Medium;
        this.backgroundColor = null !== (d = t.backgroundColor) && void 0 !== d ? d : {
                                                                                          id: -1,
                                                                                          type: 10001,
                                                                                          params: ["sys.color.ohos_id_color_button_normal"],
                                                                                          bundleName: "",
                                                                                          moduleName: ""
                                                                                      };
        this.selectedBackgroundColor = null !== (a = t.selectedBackgroundColor) && void 0 !== a ? a : {
                                                                                                          id: -1,
                                                                                                          type: 10001,
                                                                                                          params: ["sys.color.ohos_id_color_foreground_contrary"],
                                                                                                          bundleName: "",
                                                                                                          moduleName: ""
                                                                                                      };
        this.imageSize = null !== (h = t.imageSize) && void 0 !== h ? h : { width: 24, height: 24 };
        this.buttonMargin = null !== (c = t.buttonMargin) && void 0 !== c ? c : {
                                                                                    top: 4,
                                                                                    right: 8,
                                                                                    bottom: 4,
                                                                                    left: 8
                                                                                };
        this.textMargin = null !== (p = t.textMargin) && void 0 !== p ? p : 0;
        this.type = t.type;
        this.buttons = new SegmentButtonItemOptionsArray(t.buttons);
        if ("capsule" === this.type) {
            this.multiply = null !== (u = t.multiply) && void 0 !== u && u;
            this.buttons.forEach((t => {
                this.showText || (this.showText = void 0 !== t.text);
                this.showIcon || (this.showIcon = void 0 !== t.icon || void 0 !== t.selectedIcon)
            }));
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.buttonMargin = null !== (l = t.buttonMargin) && void 0 !== l ? l : {
                                                                                            top: 6,
                                                                                            right: 8,
                                                                                            bottom: 6,
                                                                                            left: 8
                                                                                        };
                this.iconTextBackgroundRadius = 14
            }
            this.selectedFontColor = null !== (m = t.selectedFontColor) && void 0 !== m ? m : {
                                                                                                  id: -1,
                                                                                                  type: 10001,
                                                                                                  params: ["sys.color.ohos_id_color_foreground_contrary"],
                                                                                                  bundleName: "",
                                                                                                  moduleName: ""
                                                                                              };
            this.selectedBackgroundColor = null !== (_ = t.selectedBackgroundColor) && void 0 !== _ ? _ : {
                                                                                                              id: -1,
                                                                                                              type: 10001,
                                                                                                              params: ["sys.color.ohos_id_color_emphasize"],
                                                                                                              bundleName: "",
                                                                                                              moduleName: ""
                                                                                                          }
        } else this.showText = !0;
        this.componentPadding = this.multiply ? 0 : 2
    }

    static tab(t) {
        return new SegmentButtonOptions_1(Object.assign({ type: "tab" }, t))
    }

    static capsule(t) {
        return new SegmentButtonOptions_1(Object.assign({ type: "capsule" }, t))
    }
};
SegmentButtonOptions = SegmentButtonOptions_1 = __decorate([Observed], SegmentButtonOptions);

class MultiSelectBackground extends ViewPU {
    constructor(t, e, o, s = -1, i = void 0) {
        super(t, o, s);
        "function" == typeof i && (this.paramsGenerator_ = i);
        this.__optionsArray = new SynchedPropertyNesedObjectPU(e.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(e.options, this, "options");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.setInitiallyProvidedValue(e)
    }

    setInitiallyProvidedValue(t) {
        this.__optionsArray.set(t.optionsArray);
        this.__options.set(t.options)
    }

    updateStateVars(t) {
        this.__optionsArray.set(t.optionsArray);
        this.__options.set(t.options)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__optionsArray.purgeDependencyOnElmtId(t);
        this.__options.purgeDependencyOnElmtId(t);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(t);
        this.__buttonItemsSize.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__optionsArray.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get optionsArray() {
        return this.__optionsArray.get()
    }

    get options() {
        return this.__options.get()
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get()
    }

    set buttonBorderRadius(t) {
        this.__buttonBorderRadius.set(t)
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get()
    }

    set buttonItemsSize(t) {
        this.__buttonItemsSize.set(t)
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Row.create({ space: 1 });
            Row.padding(this.options.componentPadding);
            e || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            ForEach.create();
            this.forEachUpdateFunction(t, this.optionsArray, ((t, e) => {
                this.observeComponentCreation(((t, o) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    If.create();
                        e < 5 ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((t, o) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            Stack.create();
                            Stack.layoutWeight(1);
                            Stack.height(this.buttonItemsSize[e].height);
                            Stack.backgroundColor(this.options.backgroundColor);
                            Stack.borderRadius(this.buttonBorderRadius[e]);
                            o || Stack.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Stack.pop()
                    })) : this.ifElseBranchUpdateFunction(1, (() => {
                    }));
                    o || If.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                If.pop()
            }), void 0,!0,!1);
            e || ForEach.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        ForEach.pop();
        Row.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

class SelectItem extends ViewPU {
    constructor(t, e, o, s = -1, i = void 0) {
        super(t, o, s);
        "function" == typeof i && (this.paramsGenerator_ = i);
        this.__optionsArray = new SynchedPropertyNesedObjectPU(e.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(e.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(e.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__selectedItemPosition = this.initializeConsume("selectedItemPosition", "selectedItemPosition");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.setInitiallyProvidedValue(e)
    }

    setInitiallyProvidedValue(t) {
        this.__optionsArray.set(t.optionsArray);
        this.__options.set(t.options)
    }

    updateStateVars(t) {
        this.__optionsArray.set(t.optionsArray);
        this.__options.set(t.options)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__optionsArray.purgeDependencyOnElmtId(t);
        this.__options.purgeDependencyOnElmtId(t);
        this.__selectedIndexes.purgeDependencyOnElmtId(t);
        this.__buttonItemsSize.purgeDependencyOnElmtId(t);
        this.__selectedItemPosition.purgeDependencyOnElmtId(t);
        this.__zoomScaleArray.purgeDependencyOnElmtId(t);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__optionsArray.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__selectedItemPosition.aboutToBeDeleted();
        this.__zoomScaleArray.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get optionsArray() {
        return this.__optionsArray.get()
    }

    get options() {
        return this.__options.get()
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get()
    }

    set selectedIndexes(t) {
        this.__selectedIndexes.set(t)
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get()
    }

    set buttonItemsSize(t) {
        this.__buttonItemsSize.set(t)
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get()
    }

    set selectedItemPosition(t) {
        this.__selectedItemPosition.set(t)
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get()
    }

    set zoomScaleArray(t) {
        this.__zoomScaleArray.set(t)
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get()
    }

    set buttonBorderRadius(t) {
        this.__buttonBorderRadius.set(t)
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
                0 !== this.selectedIndexes.length ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]]);
                    Stack.size(this.buttonItemsSize[this.selectedIndexes[0]]);
                    Stack.backgroundColor(this.options.selectedBackgroundColor);
                    Stack.position(ObservedObject.GetRawObject(this.selectedItemPosition));
                    Stack.scale({
                        x: this.zoomScaleArray[this.selectedIndexes[0]],
                        y: this.zoomScaleArray[this.selectedIndexes[0]]
                    });
                    Stack.shadow(ShadowStyle.OUTER_DEFAULT_MD);
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Stack.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

class MultiSelectItemArray extends ViewPU {
    constructor(t, e, o, s = -1, i = void 0) {
        super(t, o, s);
        "function" == typeof i && (this.paramsGenerator_ = i);
        this.__optionsArray = new SynchedPropertyNesedObjectPU(e.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(e.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(e.selectedIndexes, this, "selectedIndexes");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__multiColor = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, (() => Color.Transparent)), this, "multiColor");
        this.setInitiallyProvidedValue(e);
        this.declareWatch("selectedIndexes", this.selectedChange)
    }

    setInitiallyProvidedValue(t) {
        this.__optionsArray.set(t.optionsArray);
        this.__options.set(t.options);
        void 0 !== t.multiColor && (this.multiColor = t.multiColor)
    }

    updateStateVars(t) {
        this.__optionsArray.set(t.optionsArray);
        this.__options.set(t.options)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__optionsArray.purgeDependencyOnElmtId(t);
        this.__options.purgeDependencyOnElmtId(t);
        this.__selectedIndexes.purgeDependencyOnElmtId(t);
        this.__buttonItemsSize.purgeDependencyOnElmtId(t);
        this.__zoomScaleArray.purgeDependencyOnElmtId(t);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(t);
        this.__multiColor.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__optionsArray.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__zoomScaleArray.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__multiColor.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get optionsArray() {
        return this.__optionsArray.get()
    }

    get options() {
        return this.__options.get()
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get()
    }

    set selectedIndexes(t) {
        this.__selectedIndexes.set(t)
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get()
    }

    set buttonItemsSize(t) {
        this.__buttonItemsSize.set(t)
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get()
    }

    set zoomScaleArray(t) {
        this.__zoomScaleArray.set(t)
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get()
    }

    set buttonBorderRadius(t) {
        this.__buttonBorderRadius.set(t)
    }

    get multiColor() {
        return this.__multiColor.get()
    }

    set multiColor(t) {
        this.__multiColor.set(t)
    }

    selectedChange() {
        for (let t = 0;t < 5; t++) this.multiColor[t] = Color.Transparent;
        for (let t = 0;t < this.selectedIndexes.length; t++) this.multiColor[this.selectedIndexes[t]] = this.options.selectedBackgroundColor
    }

    aboutToAppear() {
        for (let t = 0;t < this.selectedIndexes.length; t++) this.multiColor[this.selectedIndexes[t]] = this.options.selectedBackgroundColor
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Row.create({ space: 1 });
            Row.padding(this.options.componentPadding);
            e || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            ForEach.create();
            this.forEachUpdateFunction(t, this.optionsArray, ((t, e) => {
                this.observeComponentCreation(((t, o) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    If.create();
                        e < 5 ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((t, o) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            Stack.create();
                            Stack.width(this.buttonItemsSize[e].width);
                            Stack.height(this.buttonItemsSize[e].height);
                            Stack.backgroundColor(this.multiColor[e]);
                            Stack.scale({ x: this.zoomScaleArray[e], y: this.zoomScaleArray[e] });
                            Stack.borderRadius(this.buttonBorderRadius[e]);
                            o || Stack.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        Stack.pop()
                    })) : this.ifElseBranchUpdateFunction(1, (() => {
                    }));
                    o || If.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                If.pop()
            }), void 0,!0,!1);
            e || ForEach.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        ForEach.pop();
        Row.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

class SegmentButtonItem extends ViewPU {
    constructor(t, e, o, s = -1, i = void 0) {
        super(t, o, s);
        "function" == typeof i && (this.paramsGenerator_ = i);
        this.__itemOptions = new SynchedPropertyNesedObjectPU(e.itemOptions, this, "itemOptions");
        this.__options = new SynchedPropertyNesedObjectPU(e.options, this, "options");
        this.__property = new SynchedPropertyNesedObjectPU(e.property, this, "property");
        this.index = void 0;
        this.setInitiallyProvidedValue(e)
    }

    setInitiallyProvidedValue(t) {
        this.__itemOptions.set(t.itemOptions);
        this.__options.set(t.options);
        this.__property.set(t.property);
        void 0 !== t.index && (this.index = t.index)
    }

    updateStateVars(t) {
        this.__itemOptions.set(t.itemOptions);
        this.__options.set(t.options);
        this.__property.set(t.property)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__itemOptions.purgeDependencyOnElmtId(t);
        this.__options.purgeDependencyOnElmtId(t);
        this.__property.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__itemOptions.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__property.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get itemOptions() {
        return this.__itemOptions.get()
    }

    get options() {
        return this.__options.get()
    }

    get property() {
        return this.__property.get()
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Column.create({ space: 2 });
            Column.justifyContent(FlexAlign.Center);
            Column.padding(this.options.buttonMargin);
            Column.constraintSize({ minHeight: 28 });
            e || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
            this.options.showIcon ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                    Image.size(this.options.imageSize);
                    Image.focusable(0 == this.index);
                    Image.draggable(!1);
                    e || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }))
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
            this.options.showText ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Text.create(this.itemOptions.text);
                    Text.fontColor(this.property.fontColor);
                    Text.fontWeight(this.property.fontWeight);
                    Text.fontSize(this.property.fontSize);
                    Text.minFontSize(9);
                    Text.maxFontSize(this.property.fontSize);
                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    Text.maxLines(1);
                    Text.textAlign(TextAlign.Center);
                    Text.focusable(0 == this.index && !this.options.showIcon);
                    Text.padding(this.options.textMargin);
                    e || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Column.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

let HoverColorProperty = class {
    constructor() {
        this.hoverColor = Color.Transparent
    }
};
HoverColorProperty = __decorate([Observed], HoverColorProperty);

class PressAndHoverEffect extends ViewPU {
    constructor(t, e, o, s = -1, i = void 0) {
        super(t, o, s);
        "function" == typeof i && (this.paramsGenerator_ = i);
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__press = new SynchedPropertySimpleOneWayPU(e.press, this, "press");
        this.__colorProperty = new SynchedPropertyNesedObjectPU(e.colorProperty, this, "colorProperty");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.pressIndex = 0;
        this.pressColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
        };
        this.setInitiallyProvidedValue(e)
    }

    setInitiallyProvidedValue(t) {
        this.__colorProperty.set(t.colorProperty);
        void 0 !== t.pressIndex && (this.pressIndex = t.pressIndex);
        void 0 !== t.pressColor && (this.pressColor = t.pressColor)
    }

    updateStateVars(t) {
        this.__press.reset(t.press);
        this.__colorProperty.set(t.colorProperty)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__buttonItemsSize.purgeDependencyOnElmtId(t);
        this.__press.purgeDependencyOnElmtId(t);
        this.__colorProperty.purgeDependencyOnElmtId(t);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__press.aboutToBeDeleted();
        this.__colorProperty.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get()
    }

    set buttonItemsSize(t) {
        this.__buttonItemsSize.set(t)
    }

    get press() {
        return this.__press.get()
    }

    set press(t) {
        this.__press.set(t)
    }

    get colorProperty() {
        return this.__colorProperty.get()
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get()
    }

    set buttonBorderRadius(t) {
        this.__buttonBorderRadius.set(t)
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Stack.create();
            Stack.size(this.buttonItemsSize[this.pressIndex]);
            Stack.backgroundColor(this.press ? this.pressColor : this.colorProperty.hoverColor);
            Stack.borderRadius(this.buttonBorderRadius[this.pressIndex]);
            e || Stack.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Stack.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

class SegmentButtonItemArrayComponent extends ViewPU {
    constructor(t, e, o, s = -1, i = void 0) {
        super(t, o, s);
        "function" == typeof i && (this.paramsGenerator_ = i);
        this.__optionsArray = new SynchedPropertyNesedObjectPU(e.optionsArray, this, "optionsArray");
        this.__options = new SynchedPropertyNesedObjectPU(e.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(e.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = this.initializeConsume("componentSize", "componentSize");
        this.__buttonBorderRadius = this.initializeConsume("buttonBorderRadius", "buttonBorderRadius");
        this.__buttonItemsSize = this.initializeConsume("buttonItemsSize", "buttonItemsSize");
        this.__buttonItemsPosition = this.initializeConsume("buttonItemsPosition", "buttonItemsPosition");
        this.__focusIndex = this.initializeConsume("focusIndex", "focusIndex");
        this.__zoomScaleArray = this.initializeConsume("zoomScaleArray", "zoomScaleArray");
        this.__buttonItemProperty = this.initializeConsume("buttonItemProperty", "buttonItemProperty");
        this.__buttonItemsSelected = this.initializeConsume("buttonItemsSelected", "buttonItemsSelected");
        this.__pressArray = new ObservedPropertyObjectPU(Array.from({ length: 5 }, (() =>!1)), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, (() => new HoverColorProperty)), this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({ length: 5 }, (() => 0)), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({ length: 5 }, (() => 0)), this, "buttonHeight");
        this.buttonItemsRealHeight = Array.from({ length: 5 }, (() => 0));
        this.setInitiallyProvidedValue(e);
        this.declareWatch("optionsArray", this.optionsArrayChange);
        this.declareWatch("buttonItemsSize", this.buttonItemsSizeChange)
    }

    setInitiallyProvidedValue(t) {
        this.__optionsArray.set(t.optionsArray);
        this.__options.set(t.options);
        void 0 !== t.pressArray && (this.pressArray = t.pressArray);
        void 0 !== t.hoverColorArray && (this.hoverColorArray = t.hoverColorArray);
        void 0 !== t.buttonWidth && (this.buttonWidth = t.buttonWidth);
        void 0 !== t.buttonHeight && (this.buttonHeight = t.buttonHeight);
        void 0 !== t.buttonItemsRealHeight && (this.buttonItemsRealHeight = t.buttonItemsRealHeight)
    }

    updateStateVars(t) {
        this.__optionsArray.set(t.optionsArray);
        this.__options.set(t.options)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__optionsArray.purgeDependencyOnElmtId(t);
        this.__options.purgeDependencyOnElmtId(t);
        this.__selectedIndexes.purgeDependencyOnElmtId(t);
        this.__componentSize.purgeDependencyOnElmtId(t);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(t);
        this.__buttonItemsSize.purgeDependencyOnElmtId(t);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(t);
        this.__focusIndex.purgeDependencyOnElmtId(t);
        this.__zoomScaleArray.purgeDependencyOnElmtId(t);
        this.__buttonItemProperty.purgeDependencyOnElmtId(t);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(t);
        this.__pressArray.purgeDependencyOnElmtId(t);
        this.__hoverColorArray.purgeDependencyOnElmtId(t);
        this.__buttonWidth.purgeDependencyOnElmtId(t);
        this.__buttonHeight.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__optionsArray.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__componentSize.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__buttonItemsPosition.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
        this.__zoomScaleArray.aboutToBeDeleted();
        this.__buttonItemProperty.aboutToBeDeleted();
        this.__buttonItemsSelected.aboutToBeDeleted();
        this.__pressArray.aboutToBeDeleted();
        this.__hoverColorArray.aboutToBeDeleted();
        this.__buttonWidth.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get optionsArray() {
        return this.__optionsArray.get()
    }

    get options() {
        return this.__options.get()
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get()
    }

    set selectedIndexes(t) {
        this.__selectedIndexes.set(t)
    }

    get componentSize() {
        return this.__componentSize.get()
    }

    set componentSize(t) {
        this.__componentSize.set(t)
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get()
    }

    set buttonBorderRadius(t) {
        this.__buttonBorderRadius.set(t)
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get()
    }

    set buttonItemsSize(t) {
        this.__buttonItemsSize.set(t)
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get()
    }

    set buttonItemsPosition(t) {
        this.__buttonItemsPosition.set(t)
    }

    get focusIndex() {
        return this.__focusIndex.get()
    }

    set focusIndex(t) {
        this.__focusIndex.set(t)
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get()
    }

    set zoomScaleArray(t) {
        this.__zoomScaleArray.set(t)
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get()
    }

    set buttonItemProperty(t) {
        this.__buttonItemProperty.set(t)
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get()
    }

    set buttonItemsSelected(t) {
        this.__buttonItemsSelected.set(t)
    }

    get pressArray() {
        return this.__pressArray.get()
    }

    set pressArray(t) {
        this.__pressArray.set(t)
    }

    get hoverColorArray() {
        return this.__hoverColorArray.get()
    }

    set hoverColorArray(t) {
        this.__hoverColorArray.set(t)
    }

    get buttonWidth() {
        return this.__buttonWidth.get()
    }

    set buttonWidth(t) {
        this.__buttonWidth.set(t)
    }

    get buttonHeight() {
        return this.__buttonHeight.get()
    }

    set buttonHeight(t) {
        this.__buttonHeight.set(t)
    }

    buttonItemsSizeChange() {
        this.buttonItemsSize.forEach(((t, e) => {
            this.buttonWidth[e] = t.width;
            this.buttonHeight[e] = t.height
        }))
    }

    changeSelectedIndexes(t) {
        if (this.options.multiply) {
            let t = this.selectedIndexes;
            for (let e = 0;e < this.optionsArray.deleteCount; e++) {
                let e = t.indexOf(this.optionsArray.changeStartIndex);
                let o = t.map((t => t > this.optionsArray.changeStartIndex ? t - 1 : t));
                -1 !== e && o.splice(e, 1);
                t = o
            }
            for (let e = 0;e < this.optionsArray.addLength; e++) {
                let e = t.map((t => t >= this.optionsArray.changeStartIndex ? t + 1 : t));
                t = e
            }
            this.selectedIndexes = t
        } else {
            if (void 0 === this.selectedIndexes[0]) return;
            if (this.selectedIndexes[0] < this.optionsArray.changeStartIndex) return;
            if (this.selectedIndexes[0] === this.optionsArray.changeStartIndex && this.optionsArray.changeStartIndex + this.optionsArray.deleteCount - this.optionsArray.addLength === this.optionsArray.length) {
                this.selectedIndexes[0] = this.optionsArray.changeStartIndex - 1;
                return
            }
                this.optionsArray.changeStartIndex + this.optionsArray.deleteCount > this.selectedIndexes[0] ? this.selectedIndexes[0] = this.optionsArray.changeStartIndex : this.selectedIndexes[0] = this.selectedIndexes[0] - this.optionsArray.deleteCount + this.optionsArray.addLength;
            this.selectedIndexes[0] > t - 1 && (this.selectedIndexes[0] = t - 1)
        }
    }

    changeFocusIndex(t) {
        if (-1 !== this.focusIndex && !(this.focusIndex < this.optionsArray.changeStartIndex)) if (this.focusIndex !== this.optionsArray.changeStartIndex || this.optionsArray.changeStartIndex + this.optionsArray.deleteCount - this.optionsArray.addLength !== this.optionsArray.length) {
                this.optionsArray.changeStartIndex + this.optionsArray.deleteCount > this.focusIndex ? this.focusIndex = this.optionsArray.changeStartIndex : this.focusIndex = this.focusIndex - this.optionsArray.deleteCount + this.optionsArray.addLength;
            this.focusIndex > t - 1 && (this.focusIndex = t - 1)
        } else this.focusIndex = this.optionsArray.changeStartIndex - 1
    }

    optionsArrayChange() {
        let t = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (void 0 !== this.optionsArray.changeStartIndex && void 0 !== this.optionsArray.deleteCount && void 0 !== this.optionsArray.addLength) {
            this.changeSelectedIndexes(t);
            this.changeFocusIndex(t);
            this.optionsArray.changeStartIndex = void 0;
            this.optionsArray.deleteCount = void 0;
            this.optionsArray.addLength = void 0
        }
    }

    aboutToAppear() {
        for (let t = 0;t < this.buttonItemsRealHeight.length; t++) this.buttonItemsRealHeight[t] = 0
    }

    focusStack(t, e = null) {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Stack.create();
            Stack.size({ width: 1, height: 1 });
            Stack.align(Alignment.Center);
            e || Stack.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, o) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
                t === this.focusIndex ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, o) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Stack.create();
                    Stack.borderRadius({
                        topLeft: "capsule" === this.options.type && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[t].topLeft + 4 : this.buttonBorderRadius[t].topLeft,
                        topRight: "capsule" === this.options.type && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[t].topRight + 4 : this.buttonBorderRadius[t].topRight,
                        bottomLeft: "capsule" === this.options.type && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[t].bottomLeft + 4 : this.buttonBorderRadius[t].bottomLeft,
                        bottomRight: "capsule" === this.options.type && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[t].bottomRight + 4 : this.buttonBorderRadius[t].bottomRight
                    });
                    Stack.size({
                        width: "capsule" === this.options.type && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[t] + 8 : this.buttonWidth[t],
                        height: "capsule" === this.options.type && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[t] + 8 : this.buttonHeight[t]
                    });
                    Stack.borderColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_focused_outline"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Stack.borderWidth(2);
                    o || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Stack.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }));
            o || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Stack.pop()
    }

    calculateBorderRadius() {
        var t, e, o, s, i, n, r, d;
        let a = Array.from({ length: 5 }, (() => ({ topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 })));
        for (let h = 0;h < this.buttonBorderRadius.length; h++) {
            let c = this.buttonItemsSize[h].height / 2;
            if (this.options.multiply) if (0 === h) {
                a[h].topLeft = null !== (i = this.options.iconTextRadius) && void 0 !== i ? i : c;
                a[h].topRight = 0;
                a[h].bottomLeft = null !== (n = this.options.iconTextRadius) && void 0 !== n ? n : c;
                a[h].bottomRight = 0
            } else if (h === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                a[h].topLeft = 0;
                a[h].topRight = null !== (r = this.options.iconTextRadius) && void 0 !== r ? r : c;
                a[h].bottomLeft = 0;
                a[h].bottomRight = null !== (d = this.options.iconTextRadius) && void 0 !== d ? d : c
            } else {
                a[h].topLeft = 0;
                a[h].topRight = 0;
                a[h].bottomLeft = 0;
                a[h].bottomRight = 0
            } else {
                a[h].topLeft = null !== (t = this.options.iconTextRadius) && void 0 !== t ? t : c;
                a[h].topRight = null !== (e = this.options.iconTextRadius) && void 0 !== e ? e : c;
                a[h].bottomLeft = null !== (o = this.options.iconTextRadius) && void 0 !== o ? o : c;
                a[h].bottomRight = null !== (s = this.options.iconTextRadius) && void 0 !== s ? s : c
            }
        }
        this.buttonBorderRadius = a
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
                this.optionsArray.length > 1 ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Row.create({ space: 1 });
                    Row.padding(this.options.componentPadding);
                    Row.onAreaChange(((t, e) => {
                        this.componentSize = { width: e.width, height: e.height }
                    }));
                    e || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    ForEach.create();
                    this.forEachUpdateFunction(t, this.optionsArray, ((t, e) => {
                        const o = t;
                        this.observeComponentCreation(((t, s) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            If.create();
                                e < 5 ? this.ifElseBranchUpdateFunction(0, (() => {
                                this.observeComponentCreation(((t, o) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                                    Stack.create();
                                    Stack.borderRadius(this.buttonBorderRadius[e]);
                                    Stack.scale({ x: this.zoomScaleArray[e], y: this.zoomScaleArray[e] });
                                    Stack.layoutWeight(1);
                                    Stack.onAreaChange(((t, o) => {
                                        this.buttonItemsSize[e] = {
                                            width: o.width,
                                            height: this.buttonItemsSize[e].height
                                        };
                                        this.buttonItemsPosition[e] = o.position
                                    }));
                                    Stack.overlay({ builder: () => {
                                        this.focusStack.call(this, e)
                                    } }, { align: Alignment.Center });
                                    Stack.onTouch((t => {
                                        t.source === SourceType.TouchScreen && (t.type === TouchType.Down ? Context.animateTo({
                                            curve: curves.interpolatingSpring(10, 1, 410, 38)
                                        }, (() => {
                                            this.zoomScaleArray[e] = .95
                                        })) : t.type === TouchType.Up && Context.animateTo({
                                            curve: curves.interpolatingSpring(10, 1, 410, 38)
                                        }, (() => {
                                            this.zoomScaleArray[e] = 1
                                        })))
                                    }));
                                    Stack.onHover((t => {
                                        if (t) {
                                            this.hoverColorArray[e].hoverColor = {
                                                id: -1,
                                                type: 10001,
                                                params: ["sys.color.ohos_id_color_hover"],
                                                bundleName: "",
                                                moduleName: ""
                                            };
                                            Context.animateTo({ duration: 250, curve: Curve.Friction }, (() => {
                                                this.zoomScaleArray[e] = 1.05
                                            }))
                                        } else {
                                            this.hoverColorArray[e].hoverColor = Color.Transparent;
                                            Context.animateTo({ duration: 250, curve: Curve.Friction }, (() => {
                                                this.zoomScaleArray[e] = 1
                                            }))
                                        }
                                    }));
                                    Stack.onMouse((t => {
                                        switch (t.action) {
                                            case MouseAction.Press:
                                                Context.animateTo({ duration: 250, curve: Curve.Friction }, (() => {
                                                    this.zoomScaleArray[e] = 1
                                                }));
                                                Context.animateTo({ duration: 100, curve: Curve.Sharp }, (() => {
                                                    this.pressArray[e] = !0
                                                }));
                                                break;
                                            case MouseAction.Release:
                                                Context.animateTo({ duration: 250, curve: Curve.Friction }, (() => {
                                                    this.zoomScaleArray[e] = 1.05
                                                }));
                                                Context.animateTo({ duration: 100, curve: Curve.Sharp }, (() => {
                                                    this.pressArray[e] = !1
                                                }))
                                        }
                                    }));
                                    o || Stack.pop();
                                    ViewStackProcessor.StopGetAccessRecording()
                                }));
                                this.observeComponentCreation(((t, o) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                                    if (o) {
                                        let o = () => ({
                                            pressIndex: e,
                                            colorProperty: this.hoverColorArray[e],
                                            press: this.pressArray[e]
                                        });
                                        ViewPU.create(new PressAndHoverEffect(this, {
                                            pressIndex: e,
                                            colorProperty: this.hoverColorArray[e],
                                            press: this.pressArray[e]
                                        }, void 0, t, o))
                                    } else this.updateStateVarsOfChildByElmtId(t, {
                                        colorProperty: this.hoverColorArray[e],
                                        press: this.pressArray[e]
                                    });
                                    ViewStackProcessor.StopGetAccessRecording()
                                }));
                                this.observeComponentCreation(((t, o) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                                    __Common__.create();
                                    __Common__.onAreaChange(((t, o) => {
                                        this.buttonItemsRealHeight[e] = o.height;
                                        let s = Math.max(...this.buttonItemsRealHeight);
                                        for (let t = 0;t < this.buttonItemsSize.length; t++) this.buttonItemsSize[t] = {
                                            width: this.buttonItemsSize[t].width,
                                            height: s
                                        };
                                        this.calculateBorderRadius()
                                    }));
                                    o || __Common__.pop();
                                    ViewStackProcessor.StopGetAccessRecording()
                                }));
                                this.observeComponentCreation(((t, s) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                                    if (s) {
                                        let s = () => ({
                                            index: e,
                                            itemOptions: o,
                                            options: this.options,
                                            property: this.buttonItemProperty[e]
                                        });
                                        ViewPU.create(new SegmentButtonItem(this, {
                                            index: e,
                                            itemOptions: o,
                                            options: this.options,
                                            property: this.buttonItemProperty[e]
                                        }, void 0, t, s))
                                    } else this.updateStateVarsOfChildByElmtId(t, {
                                        itemOptions: o,
                                        options: this.options,
                                        property: this.buttonItemProperty[e]
                                    });
                                    ViewStackProcessor.StopGetAccessRecording()
                                }));
                                __Common__.pop();
                                Stack.pop()
                            })) : this.ifElseBranchUpdateFunction(1, (() => {
                            }));
                            s || If.pop();
                            ViewStackProcessor.StopGetAccessRecording()
                        }));
                        If.pop()
                    }), void 0,!0,!1);
                    e || ForEach.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                ForEach.pop();
                Row.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

let ItemProperty = class {
    constructor() {
        this.fontColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_secondary"],
            bundleName: "",
            moduleName: ""
        };
        this.fontSize = {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body2"],
            bundleName: "",
            moduleName: ""
        };
        this.fontWeight = FontWeight.Regular;
        this.isSelected = !1
    }
};
ItemProperty = __decorate([Observed], ItemProperty);

class SegmentButton extends ViewPU {
    constructor(t, e, o, s = -1, i = void 0) {
        super(t, o, s);
        "function" == typeof i && (this.paramsGenerator_ = i);
        this.__options = new SynchedPropertyNesedObjectPU(e.options, this, "options");
        this.__selectedIndexes = new SynchedPropertyObjectTwoWayPU(e.selectedIndexes, this, "selectedIndexes");
        this.__componentSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, "componentSize");
        this.addProvidedVar("componentSize", this.__componentSize);
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({ length: 5 }, (() => ({
            topLeft: 0,
            topRight: 0,
            bottomLeft: 0,
            bottomRight: 0
        }))), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: 5 }, (() => ({
        }))), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({ length: 5 }, (() => ({
        }))), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, (() =>!1)), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, (() => new ItemProperty)), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, (() => 1)), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray);
        this.doSelectedChangeAnimate = !1;
        this.isCurrentPositionSelected = !1;
        this.setInitiallyProvidedValue(e);
        this.declareWatch("options", this.optionsChange);
        this.declareWatch("selectedIndexes", this.selectedChange);
        this.declareWatch("buttonItemsPosition", this.itemsPositionChange)
    }

    setInitiallyProvidedValue(t) {
        this.__options.set(t.options);
        void 0 !== t.componentSize && (this.componentSize = t.componentSize);
        void 0 !== t.buttonBorderRadius && (this.buttonBorderRadius = t.buttonBorderRadius);
        void 0 !== t.buttonItemsSize && (this.buttonItemsSize = t.buttonItemsSize);
        void 0 !== t.buttonItemsPosition && (this.buttonItemsPosition = t.buttonItemsPosition);
        void 0 !== t.buttonItemsSelected && (this.buttonItemsSelected = t.buttonItemsSelected);
        void 0 !== t.buttonItemProperty && (this.buttonItemProperty = t.buttonItemProperty);
        void 0 !== t.focusIndex && (this.focusIndex = t.focusIndex);
        void 0 !== t.selectedItemPosition && (this.selectedItemPosition = t.selectedItemPosition);
        void 0 !== t.zoomScaleArray && (this.zoomScaleArray = t.zoomScaleArray);
        void 0 !== t.doSelectedChangeAnimate && (this.doSelectedChangeAnimate = t.doSelectedChangeAnimate);
        void 0 !== t.isCurrentPositionSelected && (this.isCurrentPositionSelected = t.isCurrentPositionSelected)
    }

    updateStateVars(t) {
        this.__options.set(t.options)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__options.purgeDependencyOnElmtId(t);
        this.__selectedIndexes.purgeDependencyOnElmtId(t);
        this.__componentSize.purgeDependencyOnElmtId(t);
        this.__buttonBorderRadius.purgeDependencyOnElmtId(t);
        this.__buttonItemsSize.purgeDependencyOnElmtId(t);
        this.__buttonItemsPosition.purgeDependencyOnElmtId(t);
        this.__buttonItemsSelected.purgeDependencyOnElmtId(t);
        this.__buttonItemProperty.purgeDependencyOnElmtId(t);
        this.__focusIndex.purgeDependencyOnElmtId(t);
        this.__selectedItemPosition.purgeDependencyOnElmtId(t);
        this.__zoomScaleArray.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__componentSize.aboutToBeDeleted();
        this.__buttonBorderRadius.aboutToBeDeleted();
        this.__buttonItemsSize.aboutToBeDeleted();
        this.__buttonItemsPosition.aboutToBeDeleted();
        this.__buttonItemsSelected.aboutToBeDeleted();
        this.__buttonItemProperty.aboutToBeDeleted();
        this.__focusIndex.aboutToBeDeleted();
        this.__selectedItemPosition.aboutToBeDeleted();
        this.__zoomScaleArray.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get options() {
        return this.__options.get()
    }

    get selectedIndexes() {
        return this.__selectedIndexes.get()
    }

    set selectedIndexes(t) {
        this.__selectedIndexes.set(t)
    }

    get componentSize() {
        return this.__componentSize.get()
    }

    set componentSize(t) {
        this.__componentSize.set(t)
    }

    get buttonBorderRadius() {
        return this.__buttonBorderRadius.get()
    }

    set buttonBorderRadius(t) {
        this.__buttonBorderRadius.set(t)
    }

    get buttonItemsSize() {
        return this.__buttonItemsSize.get()
    }

    set buttonItemsSize(t) {
        this.__buttonItemsSize.set(t)
    }

    get buttonItemsPosition() {
        return this.__buttonItemsPosition.get()
    }

    set buttonItemsPosition(t) {
        this.__buttonItemsPosition.set(t)
    }

    get buttonItemsSelected() {
        return this.__buttonItemsSelected.get()
    }

    set buttonItemsSelected(t) {
        this.__buttonItemsSelected.set(t)
    }

    get buttonItemProperty() {
        return this.__buttonItemProperty.get()
    }

    set buttonItemProperty(t) {
        this.__buttonItemProperty.set(t)
    }

    get focusIndex() {
        return this.__focusIndex.get()
    }

    set focusIndex(t) {
        this.__focusIndex.set(t)
    }

    get selectedItemPosition() {
        return this.__selectedItemPosition.get()
    }

    set selectedItemPosition(t) {
        this.__selectedItemPosition.set(t)
    }

    get zoomScaleArray() {
        return this.__zoomScaleArray.get()
    }

    set zoomScaleArray(t) {
        this.__zoomScaleArray.set(t)
    }

    itemsPositionChange() {
        this.doSelectedChangeAnimate ? this.updateAnimatedProperty(this.getSelectedChangeCurve()) : this.updateAnimatedProperty(null)
    }

    setItemsSelected() {
        let t = Array.from({ length: 5 }, (() =>!1));
        this.options.multiply ? this.selectedIndexes.forEach((e => t[e] = !0)) : void 0 !== this.selectedIndexes[0] && (t[this.selectedIndexes[0]] = !0);
        this.buttonItemsSelected = t
    }

    optionsChange() {
        this.updateAnimatedProperty(null)
    }

    selectedChange() {
        this.setItemsSelected();
        this.doSelectedChangeAnimate ? this.updateAnimatedProperty(this.getSelectedChangeCurve()) : this.updateAnimatedProperty(null)
    }

    aboutToAppear() {
        if ("tab" === this.options.type && 0 === this.selectedIndexes.length) {
            this.selectedIndexes[0] = 0;
            this.buttonItemsSelected[0] = !0
        }
        this.setItemsSelected();
        this.updateAnimatedProperty(null)
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Stack.create();
            Stack.onFocus((() => {
                    0 !== this.selectedIndexes.length ? this.options.multiply ? this.focusIndex = Math.min(...this.selectedIndexes) : this.focusIndex = this.selectedIndexes[0] : this.focusIndex = 0
            }));
            Stack.onBlur((() => {
                this.focusIndex = -1
            }));
            Stack.onKeyEvent((t => {
                if (t.type === KeyType.Down) {
                    (t.keyCode === KeyCode.KEYCODE_DPAD_DOWN || t.keyCode === KeyCode.KEYCODE_DPAD_RIGHT) && this.focusIndex < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1 && (this.focusIndex = this.focusIndex + 1);
                    (t.keyCode === KeyCode.KEYCODE_DPAD_UP || t.keyCode === KeyCode.KEYCODE_DPAD_LEFT) && this.focusIndex > 0 && (this.focusIndex = this.focusIndex - 1);
                    t.keyCode === KeyCode.KEYCODE_SPACE && (this.options.multiply ? -1 === this.selectedIndexes.indexOf(this.focusIndex) ? this.selectedIndexes.push(this.focusIndex) : this.selectedIndexes.splice(this.selectedIndexes.indexOf(this.focusIndex), 1) : this.selectedIndexes[0] = this.focusIndex)
                }
            }));
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Parallel);
            TapGesture.create();
            TapGesture.onAction((t => {
                let e = t.fingerList.find((t => null !== t));
                if (void 0 === e) return;
                let o = e.localX;
                for (let t = 0;t < Math.min(this.options.buttons.length, this.buttonItemsSize.length); t++) {
                    o -= this.buttonItemsSize[t].width;
                    if (!(o >= 0)) {
                        this.doSelectedChangeAnimate = !0;
                            "capsule" === this.options.type && this.options.multiply ? -1 === this.selectedIndexes.indexOf(t) ? this.selectedIndexes.push(t) : this.selectedIndexes.splice(this.selectedIndexes.indexOf(t), 1) : this.selectedIndexes[0] = t;
                        this.doSelectedChangeAnimate = !1;
                        break
                    }
                }
            }));
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((t => {
                if (!("capsule" === this.options.type && this.options.multiply || this.isCurrentPositionSelected)) if (t.angle > 0 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                    this.doSelectedChangeAnimate = !0;
                    this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
                    this.doSelectedChangeAnimate = !1
                } else if (t.angle < 0 && 0 !== this.selectedIndexes[0]) {
                    this.doSelectedChangeAnimate = !0;
                    this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
                    this.doSelectedChangeAnimate = !1
                }
            }));
            SwipeGesture.pop();
            PanGesture.create();
            PanGesture.onActionStart((t => {
                let e = t.fingerList.find((t => null !== t));
                if (void 0 === e) return;
                let o = e.localX;
                for (let t = 0;t < Math.min(this.options.buttons.length, this.buttonItemsSize.length); t++) {
                    o -= this.buttonItemsSize[t].width;
                    if (o < 0) {
                        this.isCurrentPositionSelected = t === this.selectedIndexes[0];
                        break
                    }
                }
            }));
            PanGesture.onActionUpdate((t => {
                if ("capsule" === this.options.type && this.options.multiply) return;
                if (!this.isCurrentPositionSelected) return;
                let e = t.fingerList.find((t => null !== t));
                if (void 0 === e) return;
                let o = e.localX;
                for (let t = 0;t < Math.min(this.options.buttons.length, this.buttonItemsSize.length); t++) {
                    o -= this.buttonItemsSize[t].width;
                    if (o < 0) {
                        this.doSelectedChangeAnimate = !0;
                        this.selectedIndexes[0] = t;
                        this.doSelectedChangeAnimate = !1;
                        break
                    }
                }
            }));
            PanGesture.onActionEnd((t => {
                this.isCurrentPositionSelected = !1
            }));
            PanGesture.pop();
            GestureGroup.pop();
            Gesture.pop();
            e || Stack.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
                "capsule" === this.options.type && this.options.multiply ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    if (e) {
                        let e = () => ({ optionsArray: this.options.buttons, options: this.options });
                        ViewPU.create(new MultiSelectBackground(this, {
                            optionsArray: this.options.buttons,
                            options: this.options
                        }, void 0, t, e))
                    } else this.updateStateVarsOfChildByElmtId(t, {
                        optionsArray: this.options.buttons,
                        options: this.options
                    });
                    ViewStackProcessor.StopGetAccessRecording()
                }))
            })) : this.ifElseBranchUpdateFunction(1, (() => {
                this.observeComponentCreation(((t, e) => {
                    var o;
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.size(ObservedObject.GetRawObject(this.componentSize));
                    Stack.backgroundColor(this.options.backgroundColor);
                    Stack.borderRadius(null !== (o = this.options.iconTextBackgroundRadius) && void 0 !== o ? o : this.componentSize.height / 2);
                    Stack.foregroundBlurStyle(BlurStyle.BACKGROUND_THICK, { colorMode: ThemeColorMode.LIGHT });
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Stack.pop()
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Stack.create();
            Stack.size(ObservedObject.GetRawObject(this.componentSize));
            e || Stack.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
                "capsule" === this.options.type && this.options.multiply ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    if (e) {
                        let e = () => ({
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: $selectedIndexes
                        });
                        ViewPU.create(new MultiSelectItemArray(this, {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.__selectedIndexes
                        }, void 0, t, e))
                    } else this.updateStateVarsOfChildByElmtId(t, {
                        optionsArray: this.options.buttons,
                        options: this.options
                    });
                    ViewStackProcessor.StopGetAccessRecording()
                }))
            })) : this.ifElseBranchUpdateFunction(1, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    if (e) {
                        let e = () => ({
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: $selectedIndexes
                        });
                        ViewPU.create(new SelectItem(this, {
                            optionsArray: this.options.buttons,
                            options: this.options,
                            selectedIndexes: this.__selectedIndexes
                        }, void 0, t, e))
                    } else this.updateStateVarsOfChildByElmtId(t, {
                        optionsArray: this.options.buttons,
                        options: this.options
                    });
                    ViewStackProcessor.StopGetAccessRecording()
                }))
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Stack.pop();
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            if (e) {
                let e = () => ({
                    optionsArray: this.options.buttons,
                    options: this.options,
                    selectedIndexes: $selectedIndexes
                });
                ViewPU.create(new SegmentButtonItemArrayComponent(this, {
                    optionsArray: this.options.buttons,
                    options: this.options,
                    selectedIndexes: this.__selectedIndexes
                }, void 0, t, e))
            } else this.updateStateVarsOfChildByElmtId(t, {
                optionsArray: this.options.buttons,
                options: this.options
            });
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Stack.pop()
    }

    getSelectedChangeCurve() {
        return "capsule" === this.options.type && this.options.multiply ? null : curves.springMotion(.347, .99)
    }

    updateAnimatedProperty(t) {
        let e = () => {
            this.selectedItemPosition = 0 === this.selectedIndexes.length ? {
                                                                            } : this.buttonItemsPosition[this.selectedIndexes[0]];
            this.buttonItemsSelected.forEach(((t, e) => {
                this.buttonItemProperty[e].fontColor = t ? this.options.selectedFontColor : this.options.fontColor
            }))
        };
            t ? Context.animateTo({ curve: t }, e) : e();
        this.buttonItemsSelected.forEach(((t, e) => {
            this.buttonItemProperty[e].fontSize = t ? this.options.selectedFontSize : this.options.fontSize;
            this.buttonItemProperty[e].fontWeight = t ? this.options.selectedFontWeight : this.options.fontWeight;
            this.buttonItemProperty[e].isSelected = t
        }))
    }

    rerender() {
        this.updateDirtyElements()
    }
}

export default { SegmentButton, SegmentButtonOptions, SegmentButtonItemOptionsArray };