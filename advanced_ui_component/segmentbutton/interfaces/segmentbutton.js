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
    if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) r = Reflect.decorate(t, e, o, s); else for (var d = t.length - 1; d >= 0; d--) (i = t[d]) && (r = (n < 3 ? i(r) : n > 3 ? i(e, o, r) : i(e, o)) || r);
    return n > 3 && r && Object.defineProperty(e, o, r), r
};
var SegmentButtonItemOptionsArray_1, SegmentButtonOptions_1;
const curves = globalThis.requireNativeModule("ohos.curves");
const KeyCode = globalThis.requireNapi("multimodalInput.keyCode").KeyCode;
const MIN_ITEM_COUNT = 2;
const MAX_ITEM_COUNT = 5;
const SegmentButtonTheme = {
    FONT_COLOR: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_secondary"],
        bundleName: "",
        moduleName: ""
    },
    TAB_SELECTED_FONT_COLOR: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
    },
    CAPSULE_SELECTED_FONT_COLOR: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_foreground_contrary"],
        bundleName: "",
        moduleName: ""
    },
    FONT_SIZE: {
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_body2"],
        bundleName: "",
        moduleName: ""
    },
    SELECTED_FONT_SIZE: {
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_body2"],
        bundleName: "",
        moduleName: ""
    },
    BACKGROUND_COLOR: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_button_normal"],
        bundleName: "",
        moduleName: ""
    },
    TAB_SELECTED_BACKGROUND_COLOR: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_foreground_contrary"],
        bundleName: "",
        moduleName: ""
    },
    CAPSULE_SELECTED_BACKGROUND_COLOR: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_emphasize"],
        bundleName: "",
        moduleName: ""
    },
    FOCUS_BORDER_COLOR: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_focused_outline"],
        bundleName: "",
        moduleName: ""
    },
    HOVER_COlOR: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_hover"],
        bundleName: "",
        moduleName: ""
    },
    PRESS_COLOR: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_click_effect"],
        bundleName: "",
        moduleName: ""
    },
    BACKGROUND_BLUR_STYLE: BlurStyle.NONE
};

function nearEqual(t, e) {
    return Math.abs(t - e) < .001
}

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
        super("number" == typeof t ? t : 0);
        this.changeStartIndex = void 0;
        this.deleteCount = void 0;
        this.addLength = void 0;
        "number" != typeof t && void 0 !== t && super.push(...t.map((t => new SegmentButtonItemOptions(t))))
    }

    push(...t) {
        if (this.length + t.length > 5) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length
        }
        this.changeStartIndex = this.length;
        this.deleteCount = 0;
        this.addLength = t.length;
        return super.push(...t.map((t => new SegmentButtonItemOptions(t))))
    }

    pop() {
        if (!(this.length <= 2)) {
            this.changeStartIndex = this.length - 1;
            this.deleteCount = 1;
            this.addLength = 0;
            return super.pop()
        }
        console.warn("Below the minimum number of elements (2).")
    }

    shift() {
        if (!(this.length <= 2)) {
            this.changeStartIndex = 0;
            this.deleteCount = 1;
            this.addLength = 0;
            return super.shift()
        }
        console.warn("Below the minimum number of elements (2).")
    }

    unshift(...t) {
        if (this.length + t.length > 5) {
            console.warn("Exceeded the maximum number of elements (5).");
            return this.length
        }
        if (t.length > 0) {
            this.changeStartIndex = 0;
            this.deleteCount = 0;
            this.addLength = t.length
        }
        return super.unshift(...t.map((t => new SegmentButtonItemOptions(t))))
    }

    splice(t, e, ...o) {
        let s = this.length - e < 0 ? 0 : this.length - e;
        s += o.length;
        if (s < 2) {
            console.warn("Below the minimum number of elements (2).");
            return []
        }
        if (s > 5) {
            console.warn("Exceeded the maximum number of elements (5).");
            return []
        }
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
        var e, o, s, i, n, r, d, h, a, c, u, l, p, m, _, S;
        this.multiply = !1;
        this.showText = !1;
        this.showIcon = !1;
        this._buttons = void 0;
        this.fontColor = null !== (e = t.fontColor) && void 0 !== e ? e : SegmentButtonTheme.FONT_COLOR;
        this.selectedFontColor = null !== (o = t.selectedFontColor) && void 0 !== o ? o : SegmentButtonTheme.TAB_SELECTED_FONT_COLOR;
        this.fontSize = null !== (s = t.fontSize) && void 0 !== s ? s : SegmentButtonTheme.FONT_SIZE;
        this.selectedFontSize = null !== (i = t.selectedFontSize) && void 0 !== i ? i : SegmentButtonTheme.SELECTED_FONT_SIZE;
        this.fontWeight = null !== (n = t.fontWeight) && void 0 !== n ? n : FontWeight.Regular;
        this.selectedFontWeight = null !== (r = t.selectedFontWeight) && void 0 !== r ? r : FontWeight.Medium;
        this.backgroundColor = null !== (d = t.backgroundColor) && void 0 !== d ? d : SegmentButtonTheme.BACKGROUND_COLOR;
        this.selectedBackgroundColor = null !== (h = t.selectedBackgroundColor) && void 0 !== h ? h : SegmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
        this.imageSize = null !== (a = t.imageSize) && void 0 !== a ? a : { width: 24, height: 24 };
        this.buttonPadding = null !== (c = t.buttonPadding) && void 0 !== c ? c : {
            top: 4,
            right: 8,
            bottom: 4,
            left: 8
        };
        this.textPadding = null !== (u = t.textPadding) && void 0 !== u ? u : 0;
        this.type = t.type;
        this.backgroundBlurStyle = null !== (l = t.backgroundBlurStyle) && void 0 !== l ? l : SegmentButtonTheme.BACKGROUND_BLUR_STYLE;
        this.buttons = new SegmentButtonItemOptionsArray(t.buttons);
        if ("capsule" === this.type) {
            this.multiply = null !== (p = t.multiply) && void 0 !== p && p;
            this.buttons.forEach((t => {
                this.showText || (this.showText = void 0 !== t.text);
                this.showIcon || (this.showIcon = void 0 !== t.icon || void 0 !== t.selectedIcon)
            }));
            if (this.showText && this.showIcon) {
                this.iconTextRadius = 12;
                this.buttonPadding = null !== (m = t.buttonPadding) && void 0 !== m ? m : {
                    top: 6,
                    right: 8,
                    bottom: 6,
                    left: 8
                };
                this.iconTextBackgroundRadius = 14
            }
            this.selectedFontColor = null !== (_ = t.selectedFontColor) && void 0 !== _ ? _ : SegmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
            this.selectedBackgroundColor = null !== (S = t.selectedBackgroundColor) && void 0 !== S ? S : SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
        } else this.showText = !0;
        this.componentPadding = this.multiply ? 0 : 2
    }

    get buttons() {
        return this._buttons
    }

    set buttons(t) {
        var e;
        void 0 !== this._buttons && this._buttons !== t && (null === (e = this.onButtonsChange) || void 0 === e || e.call(this));
        this._buttons = t
    }

    static tab(t) {
        return new SegmentButtonOptions_1({
            type: "tab",
            buttons: t.buttons,
            fontColor: t.fontColor,
            selectedFontColor: t.selectedFontColor,
            fontSize: t.fontSize,
            selectedFontSize: t.selectedFontSize,
            fontWeight: t.fontWeight,
            selectedFontWeight: t.selectedFontWeight,
            backgroundColor: t.backgroundColor,
            selectedBackgroundColor: t.selectedBackgroundColor,
            imageSize: t.imageSize,
            buttonPadding: t.buttonPadding,
            textPadding: t.textPadding,
            backgroundBlurStyle: t.backgroundBlurStyle
        })
    }

    static capsule(t) {
        return new SegmentButtonOptions_1({
            type: "capsule",
            buttons: t.buttons,
            multiply: t.multiply,
            fontColor: t.fontColor,
            selectedFontColor: t.selectedFontColor,
            fontSize: t.fontSize,
            selectedFontSize: t.selectedFontSize,
            fontWeight: t.fontWeight,
            selectedFontWeight: t.selectedFontWeight,
            backgroundColor: t.backgroundColor,
            selectedBackgroundColor: t.selectedBackgroundColor,
            imageSize: t.imageSize,
            buttonPadding: t.buttonPadding,
            textPadding: t.textPadding,
            backgroundBlurStyle: t.backgroundBlurStyle
        })
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
                            var s;
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            Stack.create();
                            Stack.layoutWeight(1);
                            Stack.height(this.buttonItemsSize[e].height);
                            Stack.backgroundColor(null !== (s = this.options.backgroundColor) && void 0 !== s ? s : SegmentButtonTheme.BACKGROUND_COLOR);
                            Stack.borderRadius(this.buttonBorderRadius[e]);
                            Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
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
            void 0 !== this.selectedIndexes && 0 !== this.selectedIndexes.length ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    var o;
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]]);
                    Stack.size(this.buttonItemsSize[this.selectedIndexes[0]]);
                    Stack.backgroundColor(null !== (o = this.options.selectedBackgroundColor) && void 0 !== o ? o : "tab" === this.options.type ? SegmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR : SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR);
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
        }, ((t, e) => Color.Transparent)), this, "multiColor");
        this.setInitiallyProvidedValue(e);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange)
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

    onOptionsChange() {
        var t;
        for (let e = 0; e < this.selectedIndexes.length; e++) this.multiColor[this.selectedIndexes[e]] = null !== (t = this.options.selectedBackgroundColor) && void 0 !== t ? t : SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
    }

    onSelectedChange() {
        var t;
        for (let t = 0; t < 5; t++) this.multiColor[t] = Color.Transparent;
        for (let e = 0; e < this.selectedIndexes.length; e++) this.multiColor[this.selectedIndexes[e]] = null !== (t = this.options.selectedBackgroundColor) && void 0 !== t ? t : SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
    }

    aboutToAppear() {
        var t;
        for (let e = 0; e < this.selectedIndexes.length; e++) this.multiColor[this.selectedIndexes[e]] = null !== (t = this.options.selectedBackgroundColor) && void 0 !== t ? t : SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
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
        this.__index = new SynchedPropertySimpleOneWayPU(e.index, this, "index");
        this.setInitiallyProvidedValue(e)
    }

    setInitiallyProvidedValue(t) {
        this.__itemOptions.set(t.itemOptions);
        this.__options.set(t.options);
        this.__property.set(t.property)
    }

    updateStateVars(t) {
        this.__itemOptions.set(t.itemOptions);
        this.__options.set(t.options);
        this.__property.set(t.property);
        this.__index.reset(t.index)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__itemOptions.purgeDependencyOnElmtId(t);
        this.__options.purgeDependencyOnElmtId(t);
        this.__property.purgeDependencyOnElmtId(t);
        this.__index.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__itemOptions.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__property.aboutToBeDeleted();
        this.__index.aboutToBeDeleted();
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

    get index() {
        return this.__index.get()
    }

    set index(t) {
        this.__index.set(t)
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            var o;
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Column.create({ space: 2 });
            Column.justifyContent(FlexAlign.Center);
            Column.padding(null !== (o = this.options.buttonPadding) && void 0 !== o ? o : "capsule" === this.options.type && this.options.showText && this.options.showIcon ? {
                top: 6,
                right: 8,
                bottom: 6,
                left: 8
            } : { top: 4, right: 8, bottom: 4, left: 8 });
            Column.constraintSize({ minHeight: 28 });
            e || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
            this.options.showIcon ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    var o, s, i;
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon);
                    Image.size(null !== (o = this.options.imageSize) && void 0 !== o ? o : { width: 24, height: 24 });
                    Image.focusable(0 == this.index);
                    Image.draggable(!1);
                    Image.fillColor(this.property.isSelected ? null !== (s = this.options.selectedFontColor) && void 0 !== s ? s : SegmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR : null !== (i = this.options.fontColor) && void 0 !== i ? i : SegmentButtonTheme.FONT_COLOR);
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
                    var o;
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
                    Text.padding(null !== (o = this.options.textPadding) && void 0 !== o ? o : 0);
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
        this.pressColor = SegmentButtonTheme.PRESS_COLOR;
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
        this.__pressArray = new ObservedPropertyObjectPU(Array.from({ length: 5 }, ((t, e) =>!1)), this, "pressArray");
        this.__hoverColorArray = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, ((t, e) => new HoverColorProperty)), this, "hoverColorArray");
        this.__buttonWidth = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, ((t, e) => 0)), this, "buttonWidth");
        this.__buttonHeight = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, ((t, e) => 0)), this, "buttonHeight");
        this.buttonItemsRealHeight = Array.from({ length: 5 }, ((t, e) => 0));
        this.setInitiallyProvidedValue(e);
        this.declareWatch("optionsArray", this.onOptionsArrayChange);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("buttonItemsSize", this.onButtonItemsSizeChange)
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

    onButtonItemsSizeChange() {
        this.buttonItemsSize.forEach(((t, e) => {
            this.buttonWidth[e] = t.width;
            this.buttonHeight[e] = t.height
        }))
    }

    changeSelectedIndexes(t) {
        var e;
        if (void 0 !== this.optionsArray.changeStartIndex && void 0 !== this.optionsArray.deleteCount && void 0 !== this.optionsArray.addLength) if (null !== (e = this.options.multiply) && void 0 !== e && e) {
            let t = this.selectedIndexes;
            for (let e = 0; e < this.optionsArray.deleteCount; e++) {
                let e = t.indexOf(this.optionsArray.changeStartIndex);
                let o = t.map((t => this.optionsArray.changeStartIndex && t > this.optionsArray.changeStartIndex ? t - 1 : t));
                -1 !== e && o.splice(e, 1);
                t = o
            }
            for (let e = 0; e < this.optionsArray.addLength; e++) {
                let e = t.map((t => this.optionsArray.changeStartIndex && t >= this.optionsArray.changeStartIndex ? t + 1 : t));
                t = e
            }
            this.selectedIndexes = t
        } else {
            if (void 0 === this.selectedIndexes[0]) return;
            if (this.selectedIndexes[0] < this.optionsArray.changeStartIndex) return;
            this.optionsArray.changeStartIndex + this.optionsArray.deleteCount > this.selectedIndexes[0] ? "tab" === this.options.type ? this.selectedIndexes[0] = 0 : "capsule" === this.options.type && (this.selectedIndexes = []) : this.selectedIndexes[0] = this.selectedIndexes[0] - this.optionsArray.deleteCount + this.optionsArray.addLength
        }
    }

    changeFocusIndex(t) {
        void 0 !== this.optionsArray.changeStartIndex && void 0 !== this.optionsArray.deleteCount && void 0 !== this.optionsArray.addLength && -1 !== this.focusIndex && (this.focusIndex < this.optionsArray.changeStartIndex || (this.optionsArray.changeStartIndex + this.optionsArray.deleteCount > this.focusIndex ? this.focusIndex = 0 : this.focusIndex = this.focusIndex - this.optionsArray.deleteCount + this.optionsArray.addLength))
    }

    onOptionsArrayChange() {
        if (void 0 === this.options || void 0 === this.options.buttons) return;
        let t = Math.min(this.options.buttons.length, this.buttonItemsSize.length);
        if (void 0 !== this.optionsArray.changeStartIndex && void 0 !== this.optionsArray.deleteCount && void 0 !== this.optionsArray.addLength) {
            this.changeSelectedIndexes(t);
            this.changeFocusIndex(t);
            this.optionsArray.changeStartIndex = void 0;
            this.optionsArray.deleteCount = void 0;
            this.optionsArray.addLength = void 0
        }
    }

    onOptionsChange() {
        void 0 !== this.options && void 0 !== this.options.buttons && this.calculateBorderRadius()
    }

    aboutToAppear() {
        for (let t = 0; t < this.buttonItemsRealHeight.length; t++) this.buttonItemsRealHeight[t] = 0
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
                    Stack.borderColor(SegmentButtonTheme.FOCUS_BORDER_COLOR);
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
        var t, e, o, s, i, n, r, d, h;
        let a = Array.from({ length: 5 }, ((t, e) => ({ topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 })));
        for (let c = 0; c < this.buttonBorderRadius.length; c++) {
            let u = this.buttonItemsSize[c].height / 2;
            if ("tab" !== this.options.type && null !== (t = this.options.multiply) && void 0 !== t && t) if (0 === c) {
                a[c].topLeft = null !== (n = this.options.iconTextRadius) && void 0 !== n ? n : u;
                a[c].topRight = 0;
                a[c].bottomLeft = null !== (r = this.options.iconTextRadius) && void 0 !== r ? r : u;
                a[c].bottomRight = 0
            } else if (this.options.buttons && c === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                a[c].topLeft = 0;
                a[c].topRight = null !== (d = this.options.iconTextRadius) && void 0 !== d ? d : u;
                a[c].bottomLeft = 0;
                a[c].bottomRight = null !== (h = this.options.iconTextRadius) && void 0 !== h ? h : u
            } else {
                a[c].topLeft = 0;
                a[c].topRight = 0;
                a[c].bottomLeft = 0;
                a[c].bottomRight = 0
            } else {
                a[c].topLeft = null !== (e = this.options.iconTextRadius) && void 0 !== e ? e : u;
                a[c].topRight = null !== (o = this.options.iconTextRadius) && void 0 !== o ? o : u;
                a[c].bottomLeft = null !== (s = this.options.iconTextRadius) && void 0 !== s ? s : u;
                a[c].bottomRight = null !== (i = this.options.iconTextRadius) && void 0 !== i ? i : u
            }
        }
        this.buttonBorderRadius = a
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
            void 0 !== this.optionsArray && this.optionsArray.length > 1 ? this.ifElseBranchUpdateFunction(0, (() => {
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
                                    var s, i;
                                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                                    Stack.create();
                                    Stack.borderRadius(this.buttonBorderRadius[e]);
                                    Stack.scale({
                                        x: "capsule" === this.options.type && null !== (s = this.options.multiply) && void 0 !== s && s ? 1 : this.zoomScaleArray[e],
                                        y: "capsule" === this.options.type && null !== (i = this.options.multiply) && void 0 !== i && i ? 1 : this.zoomScaleArray[e]
                                    });
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
                                        t ? Context.animateTo({ duration: 250, curve: Curve.Friction }, (() => {
                                            this.hoverColorArray[e].hoverColor = SegmentButtonTheme.HOVER_COlOR
                                        })) : Context.animateTo({ duration: 250, curve: Curve.Friction }, (() => {
                                            this.hoverColorArray[e].hoverColor = Color.Transparent
                                        }))
                                    }));
                                    Stack.onMouse((t => {
                                        switch (t.action) {
                                            case MouseAction.Press:
                                                Context.animateTo({ curve: curves.springMotion(.347, .99) }, (() => {
                                                    this.zoomScaleArray[e] = .95
                                                }));
                                                Context.animateTo({ duration: 100, curve: Curve.Sharp }, (() => {
                                                    this.pressArray[e] = !0
                                                }));
                                                break;
                                            case MouseAction.Release:
                                                Context.animateTo({ curve: curves.springMotion(.347, .99) }, (() => {
                                                    this.zoomScaleArray[e] = 1
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
                                        let s = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ? this.options.buttons.length : 0));
                                        for (let t = 0; t < this.buttonItemsSize.length; t++) this.buttonItemsSize[t] = {
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
                                        index: e,
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
        this.fontColor = SegmentButtonTheme.FONT_COLOR;
        this.fontSize = SegmentButtonTheme.FONT_SIZE;
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
        this.__buttonBorderRadius = new ObservedPropertyObjectPU(Array.from({ length: 5 }, ((t, e) => ({
            topLeft: 0,
            topRight: 0,
            bottomLeft: 0,
            bottomRight: 0
        }))), this, "buttonBorderRadius");
        this.addProvidedVar("buttonBorderRadius", this.__buttonBorderRadius);
        this.__buttonItemsSize = new ObservedPropertyObjectPU(Array.from({ length: 5 }, ((t, e) => ({
        }))), this, "buttonItemsSize");
        this.addProvidedVar("buttonItemsSize", this.__buttonItemsSize);
        this.__buttonItemsPosition = new ObservedPropertyObjectPU(Array.from({ length: 5 }, ((t, e) => ({
        }))), this, "buttonItemsPosition");
        this.addProvidedVar("buttonItemsPosition", this.__buttonItemsPosition);
        this.__buttonItemsSelected = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, ((t, e) =>!1)), this, "buttonItemsSelected");
        this.addProvidedVar("buttonItemsSelected", this.__buttonItemsSelected);
        this.__buttonItemProperty = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, ((t, e) => new ItemProperty)), this, "buttonItemProperty");
        this.addProvidedVar("buttonItemProperty", this.__buttonItemProperty);
        this.__focusIndex = new ObservedPropertySimplePU(-1, this, "focusIndex");
        this.addProvidedVar("focusIndex", this.__focusIndex);
        this.__selectedItemPosition = new ObservedPropertyObjectPU({}, this, "selectedItemPosition");
        this.addProvidedVar("selectedItemPosition", this.__selectedItemPosition);
        this.__zoomScaleArray = new ObservedPropertyObjectPU(Array.from({
            length: 5
        }, ((t, e) => 1)), this, "zoomScaleArray");
        this.addProvidedVar("zoomScaleArray", this.__zoomScaleArray);
        this.doSelectedChangeAnimate = !1;
        this.isCurrentPositionSelected = !1;
        this.panGestureStartPoint = { x: 0, y: 0 };
        this.isPanGestureMoved = !1;
        this.setInitiallyProvidedValue(e);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("selectedIndexes", this.onSelectedChange);
        this.declareWatch("buttonItemsPosition", this.onItemsPositionChange)
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
        void 0 !== t.isCurrentPositionSelected && (this.isCurrentPositionSelected = t.isCurrentPositionSelected);
        void 0 !== t.panGestureStartPoint && (this.panGestureStartPoint = t.panGestureStartPoint);
        void 0 !== t.isPanGestureMoved && (this.isPanGestureMoved = t.isPanGestureMoved)
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

    onItemsPositionChange() {
        void 0 !== this.options && void 0 !== this.options.buttons && (this.doSelectedChangeAnimate ? this.updateAnimatedProperty(this.getSelectedChangeCurve()) : this.updateAnimatedProperty(null))
    }

    setItemsSelected() {
        var t;
        this.buttonItemsSelected.forEach(((t, e) => {
            this.buttonItemsSelected[e] = !1
        }));
        "capsule" === this.options.type && null !== (t = this.options.multiply) && void 0 !== t && t ? this.selectedIndexes.forEach((t => this.buttonItemsSelected[t] = !0)) : this.buttonItemsSelected[this.selectedIndexes[0]] = !0
    }

    updateSelectedIndexes() {
        var t;
        void 0 === this.selectedIndexes && (this.selectedIndexes = []);
        "tab" === this.options.type && 0 === this.selectedIndexes.length && (this.selectedIndexes[0] = 0);
        if (this.selectedIndexes.length > 1) {
            "tab" === this.options.type && (this.selectedIndexes = [0]);
            "capsule" !== this.options.type || null !== (t = this.options.multiply) && void 0 !== t && t || (this.selectedIndexes = [])
        }
        this.selectedIndexes.some((t => void 0 === t || t < 0 || this.options.buttons && t >= this.options.buttons.length)) && ("tab" === this.options.type ? this.selectedIndexes = [0] : this.selectedIndexes = [])
    }

    onOptionsChange() {
        if (void 0 !== this.options && void 0 !== this.options.buttons) {
            this.updateSelectedIndexes();
            this.setItemsSelected();
            this.updateAnimatedProperty(null)
        }
    }

    onSelectedChange() {
        if (void 0 !== this.options && void 0 !== this.options.buttons) {
            this.updateSelectedIndexes();
            this.setItemsSelected();
            this.doSelectedChangeAnimate ? this.updateAnimatedProperty(this.getSelectedChangeCurve()) : this.updateAnimatedProperty(null)
        }
    }

    aboutToAppear() {
        if (void 0 !== this.options && void 0 !== this.options.buttons) {
            this.options.onButtonsChange = () => {
                "tab" === this.options.type ? this.selectedIndexes = [0] : this.selectedIndexes = []
            };
            this.updateSelectedIndexes();
            this.setItemsSelected();
            this.updateAnimatedProperty(null)
        }
    }

    isMouseWheelScroll(t) {
        return t.source === SourceType.Mouse && !this.isPanGestureMoved
    }

    isMovedFromPanGestureStartPoint(t, e) {
        return!nearEqual(t, this.panGestureStartPoint.x) || !nearEqual(e, this.panGestureStartPoint.y)
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Stack.create();
            Stack.onFocus((() => {
                var t;
                void 0 !== this.options && (void 0 !== this.selectedIndexes && 0 !== this.selectedIndexes.length ? "tab" !== this.options.type && null !== (t = this.options.multiply) && void 0 !== t && t ? this.focusIndex = Math.min(...this.selectedIndexes) : this.focusIndex = this.selectedIndexes[0] : this.focusIndex = 0)
            }));
            Stack.onBlur((() => {
                this.focusIndex = -1
            }));
            Stack.onKeyEvent((t => {
                var e;
                if (void 0 !== this.options && void 0 !== this.options.buttons && t.type === KeyType.Down) {
                    (t.keyCode === KeyCode.KEYCODE_DPAD_DOWN || t.keyCode === KeyCode.KEYCODE_DPAD_RIGHT) && this.focusIndex < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1 && (this.focusIndex = this.focusIndex + 1);
                    (t.keyCode === KeyCode.KEYCODE_DPAD_UP || t.keyCode === KeyCode.KEYCODE_DPAD_LEFT) && this.focusIndex > 0 && (this.focusIndex = this.focusIndex - 1);
                    t.keyCode !== KeyCode.KEYCODE_SPACE && t.keyCode !== KeyCode.KEYCODE_ENTER && t.keyCode !== KeyCode.KEYCODE_NUMPAD_ENTER || ("capsule" === this.options.type && null !== (e = this.options.multiply) && void 0 !== e && e ? -1 === this.selectedIndexes.indexOf(this.focusIndex) ? this.selectedIndexes.push(this.focusIndex) : this.selectedIndexes.splice(this.selectedIndexes.indexOf(this.focusIndex), 1) : this.selectedIndexes[0] = this.focusIndex)
                }
            }));
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Parallel);
            TapGesture.create();
            TapGesture.onAction((t => {
                var e;
                let o = t.fingerList.find(Boolean);
                if (void 0 === o) return;
                if (void 0 === this.options || void 0 === this.options.buttons) return;
                let s = o.localX;
                for (let t = 0; t < Math.min(this.options.buttons.length, this.buttonItemsSize.length); t++) {
                    s -= this.buttonItemsSize[t].width;
                    if (!(s >= 0)) {
                        this.doSelectedChangeAnimate = !(this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length));
                        "capsule" === this.options.type && null !== (e = this.options.multiply) && void 0 !== e && e ? -1 === this.selectedIndexes.indexOf(t) ? this.selectedIndexes.push(t) : this.selectedIndexes.splice(this.selectedIndexes.indexOf(t), 1) : this.selectedIndexes[0] = t;
                        this.doSelectedChangeAnimate = !1;
                        break
                    }
                }
            }));
            TapGesture.pop();
            SwipeGesture.create();
            SwipeGesture.onAction((t => {
                var e;
                if (void 0 !== this.options && void 0 !== this.options.buttons && !("capsule" === this.options.type && null !== (e = this.options.multiply) && void 0 !== e && e || this.isCurrentPositionSelected)) if (t.angle > 0 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
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
                var e;
                if (void 0 === this.options || void 0 === this.options.buttons) return;
                if ("capsule" === this.options.type && null !== (e = this.options.multiply) && void 0 !== e && e) return;
                let o = t.fingerList.find(Boolean);
                if (void 0 === o) return;
                let s = o.localX;
                this.panGestureStartPoint = { x: o.globalX, y: o.globalY };
                this.isPanGestureMoved = !1;
                for (let t = 0; t < Math.min(this.options.buttons.length, this.buttonItemsSize.length); t++) {
                    s -= this.buttonItemsSize[t].width;
                    if (s < 0) {
                        this.isCurrentPositionSelected = t === this.selectedIndexes[0];
                        break
                    }
                }
            }));
            PanGesture.onActionUpdate((t => {
                var e;
                if (void 0 === this.options || void 0 === this.options.buttons) return;
                if ("capsule" === this.options.type && null !== (e = this.options.multiply) && void 0 !== e && e) return;
                if (!this.isCurrentPositionSelected) return;
                let o = t.fingerList.find(Boolean);
                if (void 0 === o) return;
                let s = o.localX;
                !this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(o.globalX, o.globalY) && (this.isPanGestureMoved = !0);
                for (let t = 0; t < Math.min(this.options.buttons.length, this.buttonItemsSize.length); t++) {
                    s -= this.buttonItemsSize[t].width;
                    if (s < 0) {
                        this.doSelectedChangeAnimate = !0;
                        this.selectedIndexes[0] = t;
                        this.doSelectedChangeAnimate = !1;
                        break
                    }
                }
                this.zoomScaleArray.forEach(((t, e) => {
                    e === this.selectedIndexes[0] ? Context.animateTo({
                        curve: curves.interpolatingSpring(10, 1, 410, 38)
                    }, (() => {
                        this.zoomScaleArray[e] = .95
                    })) : Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, (() => {
                        this.zoomScaleArray[e] = 1
                    }))
                }))
            }));
            PanGesture.onActionEnd((t => {
                var e;
                if (void 0 === this.options || void 0 === this.options.buttons) return;
                if ("capsule" === this.options.type && null !== (e = this.options.multiply) && void 0 !== e && e) return;
                let o = t.fingerList.find(Boolean);
                if (void 0 !== o) {
                    !this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(o.globalX, o.globalY) && (this.isPanGestureMoved = !0);
                    if (this.isMouseWheelScroll(t)) {
                        let e = 0 !== t.offsetX ? t.offsetX : t.offsetY;
                        this.doSelectedChangeAnimate = !0;
                        e > 0 && this.selectedIndexes[0] > 0 ? this.selectedIndexes[0] -= 1 : e < 0 && this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1 && (this.selectedIndexes[0] += 1);
                        this.doSelectedChangeAnimate = !1
                    }
                    Context.animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, (() => {
                        this.zoomScaleArray[this.selectedIndexes[0]] = 1
                    }));
                    this.isCurrentPositionSelected = !1
                }
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
            void 0 !== this.options && null != this.options.buttons ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    var o;
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    If.create();
                    "capsule" === this.options.type && null !== (o = this.options.multiply) && void 0 !== o && o ? this.ifElseBranchUpdateFunction(0, (() => {
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
                            var o, s;
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            Stack.create();
                            Stack.size(ObservedObject.GetRawObject(this.componentSize));
                            Stack.backgroundColor(null !== (o = this.options.backgroundColor) && void 0 !== o ? o : SegmentButtonTheme.BACKGROUND_COLOR);
                            Stack.borderRadius(null !== (s = this.options.iconTextBackgroundRadius) && void 0 !== s ? s : this.componentSize.height / 2);
                            Stack.backgroundBlurStyle(this.options.backgroundBlurStyle);
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
                    var o, s;
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Stack.create();
                    Stack.size(ObservedObject.GetRawObject(this.componentSize));
                    Stack.borderRadius(null !== (s = "capsule" === this.options.type && null !== (o = this.options.multiply) && void 0 !== o && o ? this.options.iconTextRadius : this.options.iconTextBackgroundRadius) && void 0 !== s ? s : this.componentSize.height / 2);
                    Stack.clip(!0);
                    e || Stack.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    var o;
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    If.create();
                    "capsule" === this.options.type && null !== (o = this.options.multiply) && void 0 !== o && o ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation(((t, e) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(t);
                            if (e) {
                                let e = () => ({
                                    optionsArray: this.options.buttons,
                                    options: this.options,
                                    selectedIndexes: this.selectedIndexes
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
                                    selectedIndexes: this.selectedIndexes
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
                            selectedIndexes: this.selectedIndexes
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
                }))
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Stack.pop()
    }

    getSelectedChangeCurve() {
        var t;
        return "capsule" === this.options.type && null !== (t = this.options.multiply) && void 0 !== t && t ? null : curves.springMotion(.347, .99)
    }

    updateAnimatedProperty(t) {
        let e = () => {
            this.selectedItemPosition = 0 === this.selectedIndexes.length ? {
            } : this.buttonItemsPosition[this.selectedIndexes[0]];
            this.buttonItemsSelected.forEach(((t, e) => {
                var o, s;
                this.buttonItemProperty[e].fontColor = t ? null !== (o = this.options.selectedFontColor) && void 0 !== o ? o : "tab" === this.options.type ? SegmentButtonTheme.TAB_SELECTED_FONT_COLOR : SegmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR : null !== (s = this.options.fontColor) && void 0 !== s ? s : SegmentButtonTheme.FONT_COLOR
            }))
        };
        t ? Context.animateTo({ curve: t }, e) : e();
        this.buttonItemsSelected.forEach(((t, e) => {
            var o, s, i, n;
            this.buttonItemProperty[e].fontSize = t ? null !== (o = this.options.selectedFontSize) && void 0 !== o ? o : SegmentButtonTheme.SELECTED_FONT_SIZE : null !== (s = this.options.fontSize) && void 0 !== s ? s : SegmentButtonTheme.FONT_SIZE;
            this.buttonItemProperty[e].fontWeight = t ? null !== (i = this.options.selectedFontWeight) && void 0 !== i ? i : FontWeight.Medium : null !== (n = this.options.fontWeight) && void 0 !== n ? n : FontWeight.Regular;
            this.buttonItemProperty[e].isSelected = t
        }))
    }

    rerender() {
        this.updateDirtyElements()
    }
}

export default { SegmentButton, SegmentButtonOptions, SegmentButtonItemOptionsArray, SegmentButtonItemOptions };