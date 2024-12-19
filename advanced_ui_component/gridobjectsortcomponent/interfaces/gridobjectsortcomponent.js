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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const vibrator = requireNativeModule('ohos.vibrator');
const curves = requireNativeModule('ohos.curves');
const composetitlebar = requireNapi('arkui.advanced.ComposeTitleBar');
const editabletitlebar = requireNapi('arkui.advanced.EditableTitleBar');
const subheader = requireNapi('arkui.advanced.SubHeader');
const hilog = requireNapi('hilog');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const MeasureText = requireNapi('measure');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;

const ComposeTitleBar = composetitlebar.ComposeTitleBar;
const EditableTitleBar = editabletitlebar.EditableTitleBar;
const EditableLeftIconType = editabletitlebar.EditableLeftIconType;
const SubHeader = subheader.SubHeader;
const OperationType = subheader.OperationType;

const i = 3;
const j = 4;
const m = '1fr 1fr 1fr';
const o = '1fr 1fr 1fr 1fr';
const t = 24;
const j4 = '24vp';
const l4 = 12;
const b1 = 56;
const c1 = '56vp';
const d1 = 400;
const e1 = 12;
const f1 = 4;
const g1 = 28;
const h1 = 8;
const i1 = 16;
const j1 = 56;
const l1 = 1;
const m1 = 1;
const n1 = 2;
const m4 = 1.15;
const o1 = 12;
const q1 = 1;
const s1 = 1;
const t1 = 8;
const u1 = 16;
const v1 = 200;
const w1 = curves.cubicBezierCurve(0.33, 0, 0.67, 1);
const z1 = curves.interpolatingSpring(0, 1, 400, 38);
const a2 = curves.interpolatingSpring(0, 1, 150, 24);
const b2 = curves.cubicBezierCurve(0.2, 0, 0.2, 1);
export var GridObjectSortComponentType;
(function (GridObjectSortComponentType) {
    GridObjectSortComponentType["IMAGE_TEXT"] = "image_text";
    GridObjectSortComponentType["TEXT"] = "text";
})(GridObjectSortComponentType || (GridObjectSortComponentType = {}));
class MenuItem {
    constructor(value, symbolStyle, enabled, action) {
        this.value = value;
        this.symbolStyle = symbolStyle;
        this.isEnabled = enabled;
        this.action = action;
    }
}
export class GridObjectSortComponent extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(params.options, this, "options");
        this.dataList = [];
        this.__selected = new ObservedPropertyObjectPU([], this, "selected");
        this.__unSelected = new ObservedPropertyObjectPU([], this, "unSelected");
        this.__copySelected = new ObservedPropertyObjectPU([], this, "copySelected");
        this.__copyUnSelected = new ObservedPropertyObjectPU([], this, "copyUnSelected");
        this.__content = new ObservedPropertyObjectPU({
            id: '',
            text: '',
            selected: false,
            order: 0
        }, this, "content");
        this.__dragContent = new ObservedPropertyObjectPU({
            id: '',
            text: '',
            selected: false,
            order: 0
        }, this, "dragContent");
        this.__dragContentIndex = new ObservedPropertySimplePU(-1, this, "dragContentIndex");
        this.__hoverId = new ObservedPropertySimplePU('', this, "hoverId");
        this.__gridComState = new ObservedPropertySimplePU(false, this, "gridComState");
        this.__menuSwitch = new ObservedPropertySimplePU(false, this, "menuSwitch");
        this.__areaWidth = new ObservedPropertySimplePU(0, this, "areaWidth");
        this.__blockWidth = new ObservedPropertySimplePU(0, this, "blockWidth");
        this.__blockHeight = new ObservedPropertySimplePU(0, this, "blockHeight");
        this.__longScaleOnePointTwo = new ObservedPropertySimplePU(1, this, "longScaleOnePointTwo");
        this.__scaleGridItemNinetyPercent = new ObservedPropertySimplePU(1, this, "scaleGridItemNinetyPercent");
        this.__reboundSize = new ObservedPropertySimplePU(1, this, "reboundSize");
        this.__scaleIcon = new ObservedPropertySimplePU(1, this, "scaleIcon");
        this.__addIconShow = new ObservedPropertySimplePU(false, this, "addIconShow");
        this.__scaleAddIcon = new ObservedPropertySimplePU(0, this, "scaleAddIcon");
        this.__isStartDrag = new ObservedPropertySimplePU(false, this, "isStartDrag");
        this.__insertIndex = new ObservedPropertySimplePU(-1, this, "insertIndex");
        this.__itemIndex = new ObservedPropertySimplePU(0, this, "itemIndex");
        this.__editGridDataLength = new ObservedPropertySimplePU(-1, this, "editGridDataLength");
        this.__isTouchDown = new ObservedPropertySimplePU(false, this, "isTouchDown");
        this.__addItemMoveX = new ObservedPropertySimplePU(0, this, "addItemMoveX");
        this.__addItemMoveY = new ObservedPropertySimplePU(0, this, "addItemMoveY");
        this.__editItemMoveX = new ObservedPropertySimplePU(0, this, "editItemMoveX");
        this.__editItemMoveY = new ObservedPropertySimplePU(0, this, "editItemMoveY");
        this.__unSelectedIndex = new ObservedPropertySimplePU(0, this, "unSelectedIndex");
        this.__clickAddBtn = new ObservedPropertySimplePU(false, this, "clickAddBtn");
        this.__selectedIndex = new ObservedPropertySimplePU(-1, this, "selectedIndex");
        this.__clickRemoveBtn = new ObservedPropertySimplePU(false, this, "clickRemoveBtn");
        this.__addAreaLongPressGesture = new ObservedPropertySimplePU(false, this, "addAreaLongPressGesture");
        this.__arraySelectIsChange = new ObservedPropertySimplePU(0, this, "arraySelectIsChange");
        this.__arrayUnSelectIsChange = new ObservedPropertySimplePU(0, this, "arrayUnSelectIsChange");
        this.__textItemEditWidth = new ObservedPropertySimplePU(0, this, "textItemEditWidth");
        this.__textItemEditHeight = new ObservedPropertySimplePU(0, this, "textItemEditHeight");
        this.__imageItemWidth = new ObservedPropertySimplePU(0, this, "imageItemWidth");
        this.__saveClick = new ObservedPropertySimplePU(false, this, "saveClick");
        this.__imageTextAddIconShow = new ObservedPropertySimplePU(false, this, "imageTextAddIconShow");
        this.__imageTextRemoveIconShow = new ObservedPropertySimplePU(false, this, "imageTextRemoveIconShow");
        this.__firstIn = new ObservedPropertySimplePU(true, this, "firstIn");
        this.__fontSizeScale = new ObservedPropertyObjectPU(1, this, "fontSizeScale");
        this.__fontWeightScale = new ObservedPropertyObjectPU(1, this, "fontWeightScale");
        this.__customColumns = new ObservedPropertySimplePU('1fr 1fr 1fr 1fr', this, "customColumns");
        this.__editGridHeight = new ObservedPropertySimplePU(0, this, "editGridHeight");
        this.__addGridHeight = new ObservedPropertySimplePU(0, this, "addGridHeight");
        this.__subTitleHeight = new ObservedPropertySimplePU(0, this, "subTitleHeight");
        this.callbackId = undefined;
        this.colNum = i;
        this.vibrationDone = false;
        this.touchDown = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.touchBorderRadius = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.hoverBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.focusBorder = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.imageText = false;
        this.menuItems = [
            new MenuItem({ "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_edit'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, (new SymbolGlyphModifier({ "id": -1, "type": 40000, params: ['sys.symbol.square_and_pencil'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })), true, () => {
                this.goEdit();
            }),
        ];
        this.onSave = undefined;
        this.onCancel = undefined;
        this.isFollowingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.envCallback = {
            onConfigurationUpdated: (config) => {
                let g4 = this.getUIContext();
                this.fontSizeScale = this.decideFontScale(g4);
                this.fontWeightScale = config.fontWeightScale;
            },
            onMemoryLevel: (level) => { }
        };
        this.setInitiallyProvidedValue(params);
        this.declareWatch("gridComState", this.onGridComStateChange);
        this.declareWatch("fontSizeScale", this.calcAreaInfo);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.options === undefined) {
            this.__options.set({});
        }
        if (params.dataList !== undefined) {
            this.dataList = params.dataList;
        }
        if (params.selected !== undefined) {
            this.selected = params.selected;
        }
        if (params.unSelected !== undefined) {
            this.unSelected = params.unSelected;
        }
        if (params.copySelected !== undefined) {
            this.copySelected = params.copySelected;
        }
        if (params.copyUnSelected !== undefined) {
            this.copyUnSelected = params.copyUnSelected;
        }
        if (params.content !== undefined) {
            this.content = params.content;
        }
        if (params.dragContent !== undefined) {
            this.dragContent = params.dragContent;
        }
        if (params.dragContentIndex !== undefined) {
            this.dragContentIndex = params.dragContentIndex;
        }
        if (params.hoverId !== undefined) {
            this.hoverId = params.hoverId;
        }
        if (params.gridComState !== undefined) {
            this.gridComState = params.gridComState;
        }
        if (params.menuSwitch !== undefined) {
            this.menuSwitch = params.menuSwitch;
        }
        if (params.areaWidth !== undefined) {
            this.areaWidth = params.areaWidth;
        }
        if (params.blockWidth !== undefined) {
            this.blockWidth = params.blockWidth;
        }
        if (params.blockHeight !== undefined) {
            this.blockHeight = params.blockHeight;
        }
        if (params.longScaleOnePointTwo !== undefined) {
            this.longScaleOnePointTwo = params.longScaleOnePointTwo;
        }
        if (params.scaleGridItemNinetyPercent !== undefined) {
            this.scaleGridItemNinetyPercent = params.scaleGridItemNinetyPercent;
        }
        if (params.reboundSize !== undefined) {
            this.reboundSize = params.reboundSize;
        }
        if (params.scaleIcon !== undefined) {
            this.scaleIcon = params.scaleIcon;
        }
        if (params.addIconShow !== undefined) {
            this.addIconShow = params.addIconShow;
        }
        if (params.scaleAddIcon !== undefined) {
            this.scaleAddIcon = params.scaleAddIcon;
        }
        if (params.isStartDrag !== undefined) {
            this.isStartDrag = params.isStartDrag;
        }
        if (params.insertIndex !== undefined) {
            this.insertIndex = params.insertIndex;
        }
        if (params.itemIndex !== undefined) {
            this.itemIndex = params.itemIndex;
        }
        if (params.editGridDataLength !== undefined) {
            this.editGridDataLength = params.editGridDataLength;
        }
        if (params.isTouchDown !== undefined) {
            this.isTouchDown = params.isTouchDown;
        }
        if (params.addItemMoveX !== undefined) {
            this.addItemMoveX = params.addItemMoveX;
        }
        if (params.addItemMoveY !== undefined) {
            this.addItemMoveY = params.addItemMoveY;
        }
        if (params.editItemMoveX !== undefined) {
            this.editItemMoveX = params.editItemMoveX;
        }
        if (params.editItemMoveY !== undefined) {
            this.editItemMoveY = params.editItemMoveY;
        }
        if (params.unSelectedIndex !== undefined) {
            this.unSelectedIndex = params.unSelectedIndex;
        }
        if (params.clickAddBtn !== undefined) {
            this.clickAddBtn = params.clickAddBtn;
        }
        if (params.selectedIndex !== undefined) {
            this.selectedIndex = params.selectedIndex;
        }
        if (params.clickRemoveBtn !== undefined) {
            this.clickRemoveBtn = params.clickRemoveBtn;
        }
        if (params.addAreaLongPressGesture !== undefined) {
            this.addAreaLongPressGesture = params.addAreaLongPressGesture;
        }
        if (params.arraySelectIsChange !== undefined) {
            this.arraySelectIsChange = params.arraySelectIsChange;
        }
        if (params.arrayUnSelectIsChange !== undefined) {
            this.arrayUnSelectIsChange = params.arrayUnSelectIsChange;
        }
        if (params.textItemEditWidth !== undefined) {
            this.textItemEditWidth = params.textItemEditWidth;
        }
        if (params.textItemEditHeight !== undefined) {
            this.textItemEditHeight = params.textItemEditHeight;
        }
        if (params.imageItemWidth !== undefined) {
            this.imageItemWidth = params.imageItemWidth;
        }
        if (params.saveClick !== undefined) {
            this.saveClick = params.saveClick;
        }
        if (params.imageTextAddIconShow !== undefined) {
            this.imageTextAddIconShow = params.imageTextAddIconShow;
        }
        if (params.imageTextRemoveIconShow !== undefined) {
            this.imageTextRemoveIconShow = params.imageTextRemoveIconShow;
        }
        if (params.firstIn !== undefined) {
            this.firstIn = params.firstIn;
        }
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.fontWeightScale !== undefined) {
            this.fontWeightScale = params.fontWeightScale;
        }
        if (params.customColumns !== undefined) {
            this.customColumns = params.customColumns;
        }
        if (params.editGridHeight !== undefined) {
            this.editGridHeight = params.editGridHeight;
        }
        if (params.addGridHeight !== undefined) {
            this.addGridHeight = params.addGridHeight;
        }
        if (params.subTitleHeight !== undefined) {
            this.subTitleHeight = params.subTitleHeight;
        }
        if (params.callbackId !== undefined) {
            this.callbackId = params.callbackId;
        }
        if (params.colNum !== undefined) {
            this.colNum = params.colNum;
        }
        if (params.vibrationDone !== undefined) {
            this.vibrationDone = params.vibrationDone;
        }
        if (params.touchDown !== undefined) {
            this.touchDown = params.touchDown;
        }
        if (params.touchBorderRadius !== undefined) {
            this.touchBorderRadius = params.touchBorderRadius;
        }
        if (params.hoverBackgroundColor !== undefined) {
            this.hoverBackgroundColor = params.hoverBackgroundColor;
        }
        if (params.focusBorder !== undefined) {
            this.focusBorder = params.focusBorder;
        }
        if (params.imageText !== undefined) {
            this.imageText = params.imageText;
        }
        if (params.menuItems !== undefined) {
            this.menuItems = params.menuItems;
        }
        if (params.onSave !== undefined) {
            this.onSave = params.onSave;
        }
        if (params.onCancel !== undefined) {
            this.onCancel = params.onCancel;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
        if (params.maxAppFontScale !== undefined) {
            this.maxAppFontScale = params.maxAppFontScale;
        }
        if (params.envCallback !== undefined) {
            this.envCallback = params.envCallback;
        }
    }
    updateStateVars(params) {
        this.__options.reset(params.options);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__selected.purgeDependencyOnElmtId(rmElmtId);
        this.__unSelected.purgeDependencyOnElmtId(rmElmtId);
        this.__copySelected.purgeDependencyOnElmtId(rmElmtId);
        this.__copyUnSelected.purgeDependencyOnElmtId(rmElmtId);
        this.__content.purgeDependencyOnElmtId(rmElmtId);
        this.__dragContent.purgeDependencyOnElmtId(rmElmtId);
        this.__dragContentIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__hoverId.purgeDependencyOnElmtId(rmElmtId);
        this.__gridComState.purgeDependencyOnElmtId(rmElmtId);
        this.__menuSwitch.purgeDependencyOnElmtId(rmElmtId);
        this.__areaWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__blockWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__blockHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__longScaleOnePointTwo.purgeDependencyOnElmtId(rmElmtId);
        this.__scaleGridItemNinetyPercent.purgeDependencyOnElmtId(rmElmtId);
        this.__reboundSize.purgeDependencyOnElmtId(rmElmtId);
        this.__scaleIcon.purgeDependencyOnElmtId(rmElmtId);
        this.__addIconShow.purgeDependencyOnElmtId(rmElmtId);
        this.__scaleAddIcon.purgeDependencyOnElmtId(rmElmtId);
        this.__isStartDrag.purgeDependencyOnElmtId(rmElmtId);
        this.__insertIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__itemIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__editGridDataLength.purgeDependencyOnElmtId(rmElmtId);
        this.__isTouchDown.purgeDependencyOnElmtId(rmElmtId);
        this.__addItemMoveX.purgeDependencyOnElmtId(rmElmtId);
        this.__addItemMoveY.purgeDependencyOnElmtId(rmElmtId);
        this.__editItemMoveX.purgeDependencyOnElmtId(rmElmtId);
        this.__editItemMoveY.purgeDependencyOnElmtId(rmElmtId);
        this.__unSelectedIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__clickAddBtn.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__clickRemoveBtn.purgeDependencyOnElmtId(rmElmtId);
        this.__addAreaLongPressGesture.purgeDependencyOnElmtId(rmElmtId);
        this.__arraySelectIsChange.purgeDependencyOnElmtId(rmElmtId);
        this.__arrayUnSelectIsChange.purgeDependencyOnElmtId(rmElmtId);
        this.__textItemEditWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__textItemEditHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__imageItemWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__saveClick.purgeDependencyOnElmtId(rmElmtId);
        this.__imageTextAddIconShow.purgeDependencyOnElmtId(rmElmtId);
        this.__imageTextRemoveIconShow.purgeDependencyOnElmtId(rmElmtId);
        this.__firstIn.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__fontWeightScale.purgeDependencyOnElmtId(rmElmtId);
        this.__customColumns.purgeDependencyOnElmtId(rmElmtId);
        this.__editGridHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__addGridHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__subTitleHeight.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__selected.aboutToBeDeleted();
        this.__unSelected.aboutToBeDeleted();
        this.__copySelected.aboutToBeDeleted();
        this.__copyUnSelected.aboutToBeDeleted();
        this.__content.aboutToBeDeleted();
        this.__dragContent.aboutToBeDeleted();
        this.__dragContentIndex.aboutToBeDeleted();
        this.__hoverId.aboutToBeDeleted();
        this.__gridComState.aboutToBeDeleted();
        this.__menuSwitch.aboutToBeDeleted();
        this.__areaWidth.aboutToBeDeleted();
        this.__blockWidth.aboutToBeDeleted();
        this.__blockHeight.aboutToBeDeleted();
        this.__longScaleOnePointTwo.aboutToBeDeleted();
        this.__scaleGridItemNinetyPercent.aboutToBeDeleted();
        this.__reboundSize.aboutToBeDeleted();
        this.__scaleIcon.aboutToBeDeleted();
        this.__addIconShow.aboutToBeDeleted();
        this.__scaleAddIcon.aboutToBeDeleted();
        this.__isStartDrag.aboutToBeDeleted();
        this.__insertIndex.aboutToBeDeleted();
        this.__itemIndex.aboutToBeDeleted();
        this.__editGridDataLength.aboutToBeDeleted();
        this.__isTouchDown.aboutToBeDeleted();
        this.__addItemMoveX.aboutToBeDeleted();
        this.__addItemMoveY.aboutToBeDeleted();
        this.__editItemMoveX.aboutToBeDeleted();
        this.__editItemMoveY.aboutToBeDeleted();
        this.__unSelectedIndex.aboutToBeDeleted();
        this.__clickAddBtn.aboutToBeDeleted();
        this.__selectedIndex.aboutToBeDeleted();
        this.__clickRemoveBtn.aboutToBeDeleted();
        this.__addAreaLongPressGesture.aboutToBeDeleted();
        this.__arraySelectIsChange.aboutToBeDeleted();
        this.__arrayUnSelectIsChange.aboutToBeDeleted();
        this.__textItemEditWidth.aboutToBeDeleted();
        this.__textItemEditHeight.aboutToBeDeleted();
        this.__imageItemWidth.aboutToBeDeleted();
        this.__saveClick.aboutToBeDeleted();
        this.__imageTextAddIconShow.aboutToBeDeleted();
        this.__imageTextRemoveIconShow.aboutToBeDeleted();
        this.__firstIn.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__fontWeightScale.aboutToBeDeleted();
        this.__customColumns.aboutToBeDeleted();
        this.__editGridHeight.aboutToBeDeleted();
        this.__addGridHeight.aboutToBeDeleted();
        this.__subTitleHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get options() {
        return this.__options.get();
    }
    set options(newValue) {
        this.__options.set(newValue);
    }
    get selected() {
        return this.__selected.get();
    }
    set selected(newValue) {
        this.__selected.set(newValue);
    }
    get unSelected() {
        return this.__unSelected.get();
    }
    set unSelected(newValue) {
        this.__unSelected.set(newValue);
    }
    get copySelected() {
        return this.__copySelected.get();
    }
    set copySelected(newValue) {
        this.__copySelected.set(newValue);
    }
    get copyUnSelected() {
        return this.__copyUnSelected.get();
    }
    set copyUnSelected(newValue) {
        this.__copyUnSelected.set(newValue);
    }
    get content() {
        return this.__content.get();
    }
    set content(newValue) {
        this.__content.set(newValue);
    }
    get dragContent() {
        return this.__dragContent.get();
    }
    set dragContent(newValue) {
        this.__dragContent.set(newValue);
    }
    get dragContentIndex() {
        return this.__dragContentIndex.get();
    }
    set dragContentIndex(newValue) {
        this.__dragContentIndex.set(newValue);
    }
    get hoverId() {
        return this.__hoverId.get();
    }
    set hoverId(newValue) {
        this.__hoverId.set(newValue);
    }
    get gridComState() {
        return this.__gridComState.get();
    }
    set gridComState(newValue) {
        this.__gridComState.set(newValue);
    }
    get menuSwitch() {
        return this.__menuSwitch.get();
    }
    set menuSwitch(newValue) {
        this.__menuSwitch.set(newValue);
    }
    get areaWidth() {
        return this.__areaWidth.get();
    }
    set areaWidth(newValue) {
        this.__areaWidth.set(newValue);
    }
    get blockWidth() {
        return this.__blockWidth.get();
    }
    set blockWidth(newValue) {
        this.__blockWidth.set(newValue);
    }
    get blockHeight() {
        return this.__blockHeight.get();
    }
    set blockHeight(newValue) {
        this.__blockHeight.set(newValue);
    }
    get longScaleOnePointTwo() {
        return this.__longScaleOnePointTwo.get();
    }
    set longScaleOnePointTwo(newValue) {
        this.__longScaleOnePointTwo.set(newValue);
    }
    get scaleGridItemNinetyPercent() {
        return this.__scaleGridItemNinetyPercent.get();
    }
    set scaleGridItemNinetyPercent(newValue) {
        this.__scaleGridItemNinetyPercent.set(newValue);
    }
    get reboundSize() {
        return this.__reboundSize.get();
    }
    set reboundSize(newValue) {
        this.__reboundSize.set(newValue);
    }
    get scaleIcon() {
        return this.__scaleIcon.get();
    }
    set scaleIcon(newValue) {
        this.__scaleIcon.set(newValue);
    }
    get addIconShow() {
        return this.__addIconShow.get();
    }
    set addIconShow(newValue) {
        this.__addIconShow.set(newValue);
    }
    get scaleAddIcon() {
        return this.__scaleAddIcon.get();
    }
    set scaleAddIcon(newValue) {
        this.__scaleAddIcon.set(newValue);
    }
    get isStartDrag() {
        return this.__isStartDrag.get();
    }
    set isStartDrag(newValue) {
        this.__isStartDrag.set(newValue);
    }
    get insertIndex() {
        return this.__insertIndex.get();
    }
    set insertIndex(newValue) {
        this.__insertIndex.set(newValue);
    }
    get itemIndex() {
        return this.__itemIndex.get();
    }
    set itemIndex(newValue) {
        this.__itemIndex.set(newValue);
    }
    get editGridDataLength() {
        return this.__editGridDataLength.get();
    }
    set editGridDataLength(newValue) {
        this.__editGridDataLength.set(newValue);
    }
    get isTouchDown() {
        return this.__isTouchDown.get();
    }
    set isTouchDown(newValue) {
        this.__isTouchDown.set(newValue);
    }
    get addItemMoveX() {
        return this.__addItemMoveX.get();
    }
    set addItemMoveX(newValue) {
        this.__addItemMoveX.set(newValue);
    }
    get addItemMoveY() {
        return this.__addItemMoveY.get();
    }
    set addItemMoveY(newValue) {
        this.__addItemMoveY.set(newValue);
    }
    get editItemMoveX() {
        return this.__editItemMoveX.get();
    }
    set editItemMoveX(newValue) {
        this.__editItemMoveX.set(newValue);
    }
    get editItemMoveY() {
        return this.__editItemMoveY.get();
    }
    set editItemMoveY(newValue) {
        this.__editItemMoveY.set(newValue);
    }
    get unSelectedIndex() {
        return this.__unSelectedIndex.get();
    }
    set unSelectedIndex(newValue) {
        this.__unSelectedIndex.set(newValue);
    }
    get clickAddBtn() {
        return this.__clickAddBtn.get();
    }
    set clickAddBtn(newValue) {
        this.__clickAddBtn.set(newValue);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(newValue) {
        this.__selectedIndex.set(newValue);
    }
    get clickRemoveBtn() {
        return this.__clickRemoveBtn.get();
    }
    set clickRemoveBtn(newValue) {
        this.__clickRemoveBtn.set(newValue);
    }
    get addAreaLongPressGesture() {
        return this.__addAreaLongPressGesture.get();
    }
    set addAreaLongPressGesture(newValue) {
        this.__addAreaLongPressGesture.set(newValue);
    }
    get arraySelectIsChange() {
        return this.__arraySelectIsChange.get();
    }
    set arraySelectIsChange(newValue) {
        this.__arraySelectIsChange.set(newValue);
    }
    get arrayUnSelectIsChange() {
        return this.__arrayUnSelectIsChange.get();
    }
    set arrayUnSelectIsChange(newValue) {
        this.__arrayUnSelectIsChange.set(newValue);
    }
    get textItemEditWidth() {
        return this.__textItemEditWidth.get();
    }
    set textItemEditWidth(newValue) {
        this.__textItemEditWidth.set(newValue);
    }
    get textItemEditHeight() {
        return this.__textItemEditHeight.get();
    }
    set textItemEditHeight(newValue) {
        this.__textItemEditHeight.set(newValue);
    }
    get imageItemWidth() {
        return this.__imageItemWidth.get();
    }
    set imageItemWidth(newValue) {
        this.__imageItemWidth.set(newValue);
    }
    get saveClick() {
        return this.__saveClick.get();
    }
    set saveClick(newValue) {
        this.__saveClick.set(newValue);
    }
    get imageTextAddIconShow() {
        return this.__imageTextAddIconShow.get();
    }
    set imageTextAddIconShow(newValue) {
        this.__imageTextAddIconShow.set(newValue);
    }
    get imageTextRemoveIconShow() {
        return this.__imageTextRemoveIconShow.get();
    }
    set imageTextRemoveIconShow(newValue) {
        this.__imageTextRemoveIconShow.set(newValue);
    }
    get firstIn() {
        return this.__firstIn.get();
    }
    set firstIn(newValue) {
        this.__firstIn.set(newValue);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }
    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }
    set fontWeightScale(newValue) {
        this.__fontWeightScale.set(newValue);
    }
    get customColumns() {
        return this.__customColumns.get();
    }
    set customColumns(newValue) {
        this.__customColumns.set(newValue);
    }
    get editGridHeight() {
        return this.__editGridHeight.get();
    }
    set editGridHeight(newValue) {
        this.__editGridHeight.set(newValue);
    }
    get addGridHeight() {
        return this.__addGridHeight.get();
    }
    set addGridHeight(newValue) {
        this.__addGridHeight.set(newValue);
    }
    get subTitleHeight() {
        return this.__subTitleHeight.get();
    }
    set subTitleHeight(newValue) {
        this.__subTitleHeight.set(newValue);
    }
    aboutToAppear() {
        this.dataList.length = 50;
        this.selected = this.dataList && this.deduplicate(this.dataList).filter(val => val.selected).sort(this.sortBy());
        this.unSelected = this.dataList && this.deduplicate(this.dataList).filter(val => !val.selected).sort(this.sortBy());
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
        try {
            let f4 = this.getUIContext();
            this.isFollowingSystemFontScale = f4.isFollowingSystemFontScale();
            this.maxAppFontScale = f4.getMaxFontScale();
            this.fontSizeScale = this.decideFontScale(f4);
            this.fontWeightScale =
                f4.getHostContext()?.config.fontWeightScale ?? s1;
        }
        catch (e4) {
            let code = e4.code;
            let message = e4.message;
            hilog.error(0x3900, 'Ace', `GridObjectSortComponent Faild to init fontsizescale info, code:${code}, message: ${message}`);
        }
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        }
        catch (d4) {
            let code = d4.code;
            let message = d4.message;
            hilog.error(0x3900, 'Ace', `GridObjectSortComponent Faild to get environment param error: ${code}, ${message}`);
        }
        this.calcGridHeight();
        setTimeout(() => {
            this.firstIn = false;
        }, 500);
    }
    getAdaptiveSymbolFontSize() {
        let fontScale = this.fontSizeScale;
        if (!this.isFollowingSystemFontScale || fontScale === undefined) {
            fontScale = m1;
        }
        fontScale = Math.min(m4, fontScale);
        fontScale = Math.max(fontScale, m1);
        return (fontScale * l4).toString() + 'vp';
    }
    getSymbolFontSizeFrom(imageSize) {
        if (imageSize === undefined) {
            return c1;
        }
        if (typeof imageSize === 'number') {
            return imageSize.toString() + 'vp';
        }
        return imageSize;
    }
    calcTextItemEditHeight() {
        let c4 = MeasureText.measureTextSize({
            textContent: this.dataList[0]?.text ?? '',
            fontSize: `${(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })?.value ?? o1) * (this.fontSizeScale ?? q1)}vp`,
            overflow: TextOverflow.Ellipsis,
            maxLines: l1
        });
        this.textItemEditHeight = this.fontSizeScale === q1 ? g1 : px2vp(c4.height);
        this.textItemEditHeight = this.textItemEditHeight + f1 * 2;
    }
    decideFontScale(a4) {
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        let b4 = a4.getHostContext()?.config.fontSizeScale ?? q1;
        return Math.min(b4, this.maxAppFontScale, n1);
    }
    calcColNum() {
        if (this.imageText || (this.fontSizeScale && this.fontSizeScale > q1)) {
            this.customColumns = m;
            this.colNum = i;
        }
        else {
            this.customColumns = o;
            this.colNum = j;
        }
    }
    aboutToDisappear() {
        Context.animateTo({
            duration: v1,
            curve: w1,
        }, () => {
            this.gridComState = false;
        });
        this.menuSwitch = false;
        this.selected = this.copySelected;
        this.unSelected = this.copyUnSelected;
        if (this.callbackId) {
            this.getUIContext()
                .getHostContext()
                ?.getApplicationContext()
                ?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }
    deduplicate(arr) {
        const result = [];
        arr.forEach(item => {
            if (!result.some(x => x.id === item.id)) {
                result.push(item);
            }
        });
        return result;
    }
    onGridComStateChange() {
        this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
        if (!this.imageText) {
            this.blockHeight = this.gridComState ?
                this.textItemEditHeight + u1 :
                this.textItemEditHeight + t1;
        }
    }
    sortBy() {
        return (a, b) => {
            return a.order - b.order;
        };
    }
    cancelEdit() {
        if (this.isStartDrag || this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        Context.animateTo({
            duration: v1,
            curve: b2
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
        Context.animateTo({
            duration: v1,
            curve: w1,
        }, () => {
            this.gridComState = false;
        });
        this.menuSwitch = false;
        this.selected = this.copySelected.slice();
        this.unSelected = this.copyUnSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.calcGridHeight();
        this.onCancel && this.onCancel();
    }
    goEdit() {
        Context.animateTo({
            duration: v1,
            curve: w1,
        }, () => {
            this.gridComState = true;
        });
        this.menuSwitch = true;
        this.calcGridHeight();
    }
    onSaveEdit() {
        if (this.isStartDrag) {
            return;
        }
        Context.animateTo({
            duration: v1,
            curve: b2
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
        this.editGridDataLength = this.selected.length;
        Context.animateTo({
            duration: v1,
            curve: w1,
        }, () => {
            this.gridComState = false;
            this.copySelected = this.selected.slice();
            this.copyUnSelected = this.unSelected.slice();
            const selected = this.getNewData(this.selected, true, 0);
            const z3 = this.getNewData(this.unSelected, false, this.selected.length);
            this.selected = selected;
            this.unSelected = z3;
            this.calcGridHeight();
            this.onSave && this.onSave(selected, z3);
        });
        setTimeout(() => {
            this.saveClick = false;
        }, v1);
        this.menuSwitch = false;
    }
    onDragMoveEvent(event, itemIndex, insertIndex) {
        if (!this.gridComState || (event.x < this.blockWidth / 3 && event.y < this.blockHeight / 3)) {
            return;
        }
        let targetIndex = insertIndex;
        if (targetIndex < 0) {
            targetIndex = this.selected.length - 1;
        }
        if (this.dragContent.visibility !== Visibility.Hidden) {
            this.dragContent.visibility = Visibility.Hidden;
        }
        this.insertIndex = insertIndex;
    }
    handleDeleteClick(content) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.clickRemoveBtn = true;
        this.scaleIcon = 0;
        this.arraySelectIsChange = 1;
        let currentIndex = this.selected.findIndex(val => val.id === content.id);
        this.content = content;
        this.selectedIndex = currentIndex;
        this.calcGridHeight();
        Context.animateTo({ curve: a2, onFinish: () => {
                this.scaleIcon = 1;
                this.selected.splice(currentIndex, 1);
                this.unSelected.unshift(content);
                this.calcGridHeight();
                this.editGridDataLength = this.editGridDataLength - 1;
                this.editItemMoveX = 0;
                this.editItemMoveY = 0;
                this.arraySelectIsChange = 2;
                this.clickRemoveBtn = false;
            }
        }, () => {
            let y3 = this.getAddItemGridPosition();
            this.editItemMoveX = y3.x;
            this.editItemMoveY = y3.y;
        });
    }
    getNewData(data, state, startIndex) {
        return data.map((val, index) => {
            val.selected = state;
            val.order = startIndex + index;
            val.visibility = Visibility.Visible;
            return val;
        });
    }
    getBlockWidth() {
        const x3 = (this.areaWidth - 32) / this.colNum;
        return x3;
    }
    calcGridHeight() {
        this.editGridHeight = this.getGridHeight(this.selected, 'edit');
        this.addGridHeight = this.getGridHeight(this.unSelected);
    }
    getGridHeight(data, state) {
        let height = 0;
        let t3 = data.length;
        data.forEach(item => {
            if (item.visibility === Visibility.Hidden) {
                t3 = t3 - 1;
            }
        });
        let u3 = 0;
        let v3 = t3 % this.colNum === 0;
        if (this.clickAddBtn && v3) {
            u3 = 1;
        }
        else if (this.isStartDrag && v3 && state) {
            u3 = 1;
        }
        else if (this.clickRemoveBtn && v3 && !state) {
            u3 = 1;
        }
        else {
            u3 = 0;
        }
        let w3 = Math.ceil(t3 / this.colNum) + u3;
        height = this.blockHeight * w3;
        if (t3 === 0) {
            height = 0;
        }
        return height;
    }
    imageTextRemoveIcon(select) {
        const s3 = this.clickRemoveBtn && this.content.id === select.id;
        const icon = s3 ? { "id": -1, "type": 40000, params: ['sys.symbol.plus_circle_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 40000, params: ['sys.symbol.minus_circle_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        return icon;
    }
    imageTextAddIcon(select) {
        const r3 = this.clickAddBtn && this.content.id === select.id && this.gridComState;
        const icon = r3 ? { "id": -1, "type": 40000, params: ['sys.symbol.minus_circle_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 40000, params: ['sys.symbol.plus_circle_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        return icon;
    }
    imageTextAddIconVisible(select) {
        const q3 = this.clickAddBtn && this.content.id === select.id && !this.gridComState;
        const visible = q3 ? Visibility.Hidden : Visibility.Visible;
        return visible;
    }
    getCoodXY(index) {
        let x = 0;
        let y = 0;
        const n3 = this.colNum;
        const p3 = Math.trunc(index % n3);
        if (index >= this.dragContentIndex) {
            if (index <= this.insertIndex && index !== this.dragContentIndex) {
                if (p3 === 0) {
                    x = x + this.blockWidth * (n3 - 1);
                    y = y - this.blockHeight;
                }
                else {
                    x = x - this.blockWidth;
                }
            }
        }
        else {
            if (index >= this.insertIndex) {
                if (p3 === n3 - 1) {
                    x = x - this.blockWidth * (n3 - 1);
                    y = y + this.blockHeight;
                }
                else {
                    x = x + this.blockWidth;
                }
            }
        }
        if (!this.isStartDrag) {
            x = 0;
            y = 0;
        }
        return { x: x, y: y };
    }
    getAddItemGridPosition() {
        const len = this.selected.length;
        const d3 = this.colNum;
        const e3 = (this.selectedIndex + 1) % d3;
        const f3 = Math.ceil((this.selectedIndex + 1) / d3);
        const g3 = Math.ceil(len / d3);
        const h3 = this.imageText;
        let i3 = 0;
        if (e3 === 0) {
            i3 = h3 || (this.fontSizeScale && this.fontSizeScale > 1) ? -this.blockWidth * 2 : -this.blockWidth * 3;
        }
        else {
            i3 = -this.blockWidth * (e3 - 1);
        }
        let j3 = j1;
        let k3 = 0;
        const l3 = g3 - f3;
        const m3 = len % d3;
        const line = m3 === 1 ? l3 : l3 + 1;
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            j3 = this.subTitleHeight;
        }
        k3 = line * this.blockHeight + j3;
        return {
            x: i3,
            y: k3
        };
    }
    getCoveringGridPosition(index) {
        let b3 = 0;
        let c3 = 0;
        if (index > this.selectedIndex && this.arraySelectIsChange !== 2) {
            b3 = index % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            c3 = index % this.colNum === 0 ? -this.blockHeight : 0;
        }
        return {
            x: b3,
            y: c3
        };
    }
    getEditItemGridPosition(data, q2) {
        const len = data.length;
        const r2 = this.colNum;
        const s2 = Math.trunc(len % r2);
        const t2 = Math.trunc(q2 % r2);
        let u2 = Math.abs(s2 - t2) * this.blockWidth;
        if (s2 < t2) {
            u2 = -u2;
        }
        else if (s2 > t2) {
            u2 = u2;
        }
        else {
            u2 = 0;
        }
        let v2 = 0;
        let itemHeight = 0;
        let w2 = Math.trunc(q2 / this.colNum);
        let z2 = j1;
        const a3 = !this.imageText && this.gridComState && q2 > 3;
        if (a3) {
            itemHeight = (w2 + 1) * (this.blockHeight - 8) + 8;
        }
        else {
            itemHeight = (w2 + 1) * this.blockHeight;
        }
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            z2 = this.subTitleHeight;
        }
        v2 = itemHeight + z2;
        return {
            x: u2,
            y: v2
        };
    }
    getCoveringGridPositionBottom(index) {
        let l2 = 0;
        let m2 = 0;
        const n2 = index % this.colNum === 0;
        const o2 = this.gridComState && !this.imageText ? -this.blockHeight + 8 : -this.blockHeight;
        if (index > this.unSelectedIndex && this.arrayUnSelectIsChange !== 2) {
            l2 = n2 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            m2 = n2 ? o2 : 0;
        }
        return {
            x: l2,
            y: m2
        };
    }
    getAddItemRightMove(index) {
        let x = this.blockWidth;
        let y = 0;
        let k2 = (index + 1) % this.colNum === 0;
        if (k2) {
            x = -this.blockWidth * (this.colNum - 1);
            y = this.imageText ? this.blockHeight : this.blockHeight - 8;
        }
        return { x: x, y: y };
    }
    getShowAreaItemTranslate(index) {
        if (this.isStartDrag) {
            let j2 = this.getCoodXY(index);
            return {
                x: j2.x,
                y: j2.y
            };
        }
        if (!this.isStartDrag && index === this.selectedIndex) {
            return {
                x: this.editItemMoveX,
                y: this.editItemMoveY
            };
        }
        if (!this.isStartDrag && index !== this.selectedIndex && this.clickRemoveBtn) {
            let i2 = this.getCoveringGridPosition(index);
            return {
                x: i2.x,
                y: i2.y
            };
        }
        return { x: 0, y: 0 };
    }
    getAddAreaItemTranslate(index) {
        if (this.clickRemoveBtn) {
            let h2 = this.getAddItemRightMove(index);
            return {
                x: h2.x,
                y: h2.y
            };
        }
        if (!this.clickRemoveBtn && index === this.unSelectedIndex) {
            return {
                x: this.addItemMoveX,
                y: -this.addItemMoveY
            };
        }
        if (!this.clickRemoveBtn && index !== this.unSelectedIndex && this.clickAddBtn) {
            let g2 = this.getCoveringGridPositionBottom(index);
            return {
                x: g2.x,
                y: g2.y
            };
        }
        return { x: 0, y: 0 };
    }
    PixelMapBuilder(url, text, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.clip(false);
            Stack.height(this.blockHeight * 1.5);
            Stack.width(this.blockWidth * 1.2);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.imageText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.alignItems(HorizontalAlign.Center);
                        Column.justifyContent(FlexAlign.Center);
                        Column.width(this.imageItemWidth);
                        Column.height(this.imageItemWidth);
                        Column.padding({ left: h1, right: h1 });
                        Column.backgroundColor(this.touchDown);
                        Column.borderRadius(this.touchBorderRadius);
                        Column.scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (url === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || c1);
                                    SymbolGlyph.width((this.options.imageSize || c1));
                                    SymbolGlyph.fontSize(this.options.imageSize || c1);
                                }, SymbolGlyph);
                            });
                        }
                        else if (url instanceof SymbolGlyphModifier) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || c1);
                                    SymbolGlyph.width((this.options.imageSize || c1));
                                    SymbolGlyph.attributeModifier.bind(this)(url);
                                    SymbolGlyph.fontSize(this.options.imageSize || c1);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Image.create(url);
                                    Image.draggable(false);
                                    Image.height(this.options.imageSize || b1);
                                    Image.width((this.options.imageSize || b1));
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(text);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({ top: 2 });
                        Text.maxLines(l1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.minFontScale(m1);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.minus_circle_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        SymbolGlyph.fontSize(j4);
                        SymbolGlyph.fontWeight(d1);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                        SymbolGlyph.width(t);
                        SymbolGlyph.height(t);
                        SymbolGlyph.position({
                            x: this.blockWidth - 40,
                            y: -h1
                        });
                    }, SymbolGlyph);
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.borderRadius(50);
                        Row.padding({
                            left: e1,
                            right: e1,
                        });
                        Row.scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo });
                        Row.alignItems(VerticalAlign.Center);
                        Row.justifyContent(FlexAlign.Center);
                        Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Row.width(this.textItemEditWidth);
                        Row.height(this.textItemEditHeight);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(text);
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.textAlign(TextAlign.Center);
                        Text.maxLines(l1);
                        Text.minFontScale(m1);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.minus_circle_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        SymbolGlyph.fontSize(j4);
                        SymbolGlyph.fontWeight(d1);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                        SymbolGlyph.width(t);
                        SymbolGlyph.height(t);
                        SymbolGlyph.position({
                            x: this.blockWidth - 52,
                            y: -h1
                        });
                    }, SymbolGlyph);
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }
    HeaderTitleBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.visibility(!this.menuSwitch ? Visibility.Visible : Visibility.None);
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new ComposeTitleBar(this, {
                        title: this.options.normalTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        menuItems: this.menuItems,
                    }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/GridObjectSortComponent.ets", line: 832, c2: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            title: this.options.normalTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            menuItems: this.menuItems
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: "ComposeTitleBar" });
        }
        __Common__.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.visibility(this.menuSwitch ? Visibility.Visible : Visibility.None);
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new EditableTitleBar(this, {
                        leftIconStyle: EditableLeftIconType.Cancel,
                        menuItems: [],
                        title: this.options.editTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_title_edit'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        onCancel: () => {
                            this.cancelEdit();
                        },
                        onSave: () => {
                            this.saveClick = true;
                            this.onSaveEdit();
                        }
                    }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/GridObjectSortComponent.ets", line: 837, c2: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            leftIconStyle: EditableLeftIconType.Cancel,
                            menuItems: [],
                            title: this.options.editTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_title_edit'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            onCancel: () => {
                                this.cancelEdit();
                            },
                            onSave: () => {
                                this.saveClick = true;
                                this.onSaveEdit();
                            }
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: "EditableTitleBar" });
        }
        __Common__.pop();
    }
    ImageTextBuilder(select, type, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.padding({ left: h1, right: h1 });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Center);
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.height(this.imageItemWidth);
            Column.padding({ left: h1, right: h1 });
            Column.borderRadius((this.isTouchDown && select.id === this.content.id) ||
                select.id === this.hoverId ? this.touchBorderRadius : 0);
            Column.backgroundColor(this.isTouchDown && select.id === this.content.id
                ? this.touchDown : select.id === this.hoverId ? this.hoverBackgroundColor : '');
            Column.scale(select.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (select.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create();
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.attributeModifier.bind(this)(select.symbolStyle);
                        SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (select.url === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Image.create(select.url);
                                    Image.draggable(false);
                                    Image.height(this.options.imageSize || b1);
                                    Image.width((this.options.imageSize || b1));
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(select.text);
            Text.textAlign(TextAlign.Center);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.margin({ top: 2 });
            Text.maxLines(l1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.minFontScale(m1);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
            Text.padding({
                top: f1,
                bottom: f1
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create(this.imageTextAddIcon(select));
            SymbolGlyph.fontSize(j4);
            SymbolGlyph.fontWeight(d1);
            SymbolGlyph.draggable(false);
            SymbolGlyph.visibility(type === 'add' ? this.imageTextAddIconVisible(select) : Visibility.Hidden);
            SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
            SymbolGlyph.width(t);
            SymbolGlyph.height(t);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -h1
            });
            SymbolGlyph.onClick(() => {
                if (this.clickAddBtn || this.clickRemoveBtn) {
                    return;
                }
                this.scaleIcon = 0;
                this.content = select;
                const index = this.unSelected.findIndex(f2 => f2.id === select.id);
                this.editGridDataLength = this.selected.length + 1;
                const e2 = this.getEditItemGridPosition(ObservedObject.GetRawObject(this.selected), index);
                this.unSelectedIndex = index;
                this.arrayUnSelectIsChange = 1;
                this.clickAddBtn = true;
                this.calcGridHeight();
                Context.animateTo({ curve: a2, onFinish: () => {
                        if (!this.selected.some(val => val.id === select.id)) {
                            this.arrayUnSelectIsChange = 2;
                            this.scaleIcon = 1;
                            this.selected.push(select);
                            this.unSelected.splice(index, 1);
                            this.calcGridHeight();
                            this.addItemMoveX = 0;
                            this.addItemMoveY = 0;
                            if (!this.gridComState) {
                                this.onSaveEdit();
                            }
                            this.clickAddBtn = false;
                        }
                    }
                }, () => {
                    this.addItemMoveX = e2.x;
                    this.addItemMoveY = e2.y;
                });
            });
        }, SymbolGlyph);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create(this.imageTextRemoveIcon(select));
            SymbolGlyph.fontSize(j4);
            SymbolGlyph.fontWeight(d1);
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
            SymbolGlyph.visibility(type === 'delete' && this.gridComState ? Visibility.Visible :
                Visibility.Hidden);
            SymbolGlyph.width(t);
            SymbolGlyph.height(t);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -h1
            });
            SymbolGlyph.onClick(() => this.handleDeleteClick(select));
        }, SymbolGlyph);
        Column.pop();
        Column.pop();
    }
    TextBlockBuilder(select, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.scale(select.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: h1,
                right: h1
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Context.animation(!this.firstIn ? {
                duration: v1,
                curve: this.gridComState ? z1 : w1
            } : { duration: 0 });
            Row.borderRadius(50);
            Row.width(this.clickRemoveBtn && select.id === this.content.id ? this.textItemEditWidth + 8 : this.textItemEditWidth);
            Row.translate(this.gridComState ? this.clickRemoveBtn &&
                select.id === this.content.id ? { x: 0 } : { x: -4 } : { x: 0 });
            Row.height('100%');
            Context.animation(null);
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Context.animation(!this.firstIn ? {
                duration: v1,
                curve: this.gridComState ? z1 : w1
            } : { duration: 0 });
            Flex.borderRadius(50);
            Flex.padding({
                left: e1,
                right: e1,
            });
            Flex.backgroundColor(this.isTouchDown && select.id === this.content.id ? this.touchDown
                : select.id === this.hoverId ? this.hoverBackgroundColor
                    : '');
            Flex.width(this.clickRemoveBtn && select.id === this.content.id ? this.textItemEditWidth + 8 : this.textItemEditWidth);
            Flex.translate(this.gridComState ? this.clickRemoveBtn && select.id === this.content.id ? { x: 0 } : { x: -4 } : {
                x: 0
            });
            Flex.height('100%');
            Context.animation(null);
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.plus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Context.animation({
                duration: v1,
                curve: w1
            });
            SymbolGlyph.fontSize(this.getAdaptiveSymbolFontSize());
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
            SymbolGlyph.visibility(this.clickRemoveBtn && select.id === this.content.id ? Visibility.Visible : Visibility.None);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(select.text);
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(l1);
            Text.minFontScale(m1);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.minus_circle_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Context.animation({
                duration: v1,
                curve: w1,
            });
            SymbolGlyph.fontSize(j4);
            SymbolGlyph.fontWeight(d1);
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
            SymbolGlyph.width(t);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, centerX: '50%' } });
            SymbolGlyph.scale(select.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {});
            SymbolGlyph.visibility(this.gridComState ? 0 : 1);
            SymbolGlyph.position({
                x: this.blockWidth - 52,
                y: -h1
            });
            Context.animation(null);
            SymbolGlyph.onClick(() => this.handleDeleteClick(select));
        }, SymbolGlyph);
        Flex.pop();
        Stack.pop();
    }
    TextBlockAddItemBuilder(select, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.scale(select.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: h1,
                right: h1
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Context.animation({
                duration: v1,
                curve: w1
            });
            Row.borderRadius(50);
            Row.height('100%');
            Row.width(this.addIconShow && select.id === this.content.id ? this.textItemEditWidth : '100%');
            Row.translate(this.addIconShow && select.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Context.animation({
                duration: v1,
                curve: w1
            });
            Flex.borderRadius(50);
            Flex.padding({
                left: e1,
                right: e1,
            });
            Flex.backgroundColor(this.isTouchDown && select.id === this.content.id ? this.touchDown
                : select.id === this.hoverId ? this.hoverBackgroundColor : '');
            Flex.width(this.addIconShow && select.id === this.content.id ? this.textItemEditWidth : '100%');
            Flex.translate(this.addIconShow && select.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Flex.height('100%');
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.plus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Context.animation({
                duration: v1,
                curve: w1
            });
            SymbolGlyph.fontSize(this.getAdaptiveSymbolFontSize());
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
            SymbolGlyph.visibility(this.addIconShow && select.id === this.content.id ? Visibility.None : Visibility.Visible);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(select.text);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Start);
            Text.maxLines(l1);
            Text.minFontScale(m1);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.gridComState && this.addIconShow && select.id === this.content.id) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.minus_circle_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        SymbolGlyph.fontSize(j4);
                        SymbolGlyph.fontWeight(d1);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
                        SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                        SymbolGlyph.width(t);
                        SymbolGlyph.translate(this.gridComState ? { x: -h1 } : {});
                        SymbolGlyph.position({
                            x: this.blockWidth - 44,
                            y: -h1
                        });
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        Stack.pop();
    }
    onAddTagLongPressEnd() {
        this.addAreaLongPressGesture = false;
        Context.animateTo({
            duration: v1,
            curve: b2
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
    }
    AddTagBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Grid.create();
            Context.animation({
                duration: v1,
                curve: this.imageText ? a2 : w1,
            });
            Grid.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {});
            Context.animation(null);
            Grid.columnsTemplate(this.customColumns);
            Grid.padding({
                left: i1,
                right: i1,
            });
            Grid.clip(false);
            Grid.height(this.addGridHeight);
        }, Grid);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const item = _item;
                {
                    const itemCreation2 = (elmtId, isInitialRender) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.clickRemoveBtn ? z1 : index === this.unSelectedIndex ? a2 : z1
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getAddAreaItemTranslate(index));
                        Context.animation(null);
                    };
                    const observedDeepRender = () => {
                        this.observeComponentCreation2(itemCreation2, GridItem);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Stack.create();
                            Stack.onHover((isHover) => {
                                if (isHover) {
                                    this.hoverId = item.id;
                                }
                                else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.margin({
                                bottom: this.imageText ? i1 : h1
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.onTouch((event) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (event.type === TouchType.Down) {
                                    this.content = item;
                                    this.isTouchDown = true;
                                }
                                if (event.type === TouchType.Cancel) {
                                    this.isTouchDown = false;
                                    return;
                                }
                                if (event.type === TouchType.Up) {
                                    this.isTouchDown = false;
                                    if (this.addAreaLongPressGesture || this.longScaleOnePointTwo === 1.05 || this.imageText) {
                                        return;
                                    }
                                    Context.animateTo({
                                        duration: v1,
                                        curve: w1
                                    }, () => {
                                        this.addIconShow = true;
                                    });
                                    if (this.options.type === GridObjectSortComponentType.TEXT) {
                                        this.scaleAddIcon = 1;
                                    }
                                    this.scaleIcon = 0;
                                    const index = this.unSelected.findIndex(d2 => d2.id === item.id);
                                    this.editGridDataLength = this.selected.length + 1;
                                    const c2 = this.getEditItemGridPosition(ObservedObject.GetRawObject(this.selected), index);
                                    this.content = item;
                                    this.unSelectedIndex = index;
                                    this.clickAddBtn = true;
                                    this.arrayUnSelectIsChange = 1;
                                    this.calcGridHeight();
                                    Context.animateTo({
                                        curve: a2, onFinish: () => {
                                            if (!this.selected.some(val => val.id === item.id)) {
                                                this.scaleIcon = 1;
                                                this.scaleAddIcon = 0;
                                                this.selected.push(item);
                                                this.unSelected.splice(index, 1);
                                                this.calcGridHeight();
                                                this.arrayUnSelectIsChange = 2;
                                                this.addItemMoveX = 0;
                                                this.addItemMoveY = 0;
                                                if (!this.gridComState) {
                                                    this.onSaveEdit();
                                                }
                                                Context.animateTo({
                                                    duration: v1,
                                                    curve: w1
                                                }, () => {
                                                    this.addIconShow = false;
                                                });
                                                this.clickAddBtn = false;
                                            }
                                        }
                                    }, () => {
                                        this.addItemMoveX = c2.x;
                                        this.addItemMoveY = c2.y;
                                    });
                                }
                            });
                            Gesture.create(GesturePriority.Low);
                            LongPressGesture.create({ repeat: true });
                            LongPressGesture.onAction((event) => {
                                if (!this.gridComState) {
                                    Context.animateTo({
                                        duration: v1,
                                        curve: w1,
                                    }, () => {
                                        this.addAreaLongPressGesture = true;
                                        this.gridComState = true;
                                    });
                                    this.menuSwitch = true;
                                }
                                else {
                                    Context.animateTo({
                                        duration: v1,
                                        curve: b2
                                    }, () => {
                                        this.longScaleOnePointTwo = 1.05;
                                    });
                                }
                                this.calcGridHeight();
                            });
                            LongPressGesture.onActionEnd(() => {
                                this.onAddTagLongPressEnd();
                            });
                            LongPressGesture.onActionCancel(() => {
                                this.onAddTagLongPressEnd();
                            });
                            LongPressGesture.pop();
                            Gesture.pop();
                        }, Stack);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(item, 'add');
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockAddItemBuilder.bind(this)(item);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    observedDeepRender();
                }
            };
            this.forEachUpdateFunction(elmtId, this.unSelected, forEachItemGenFunction, (item) => item.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
    }
    EditTagBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Grid.create();
            Context.animation(!this.firstIn ? {
                duration: v1,
                curve: this.imageText ? a2 : w1,
            } : { duration: 0 });
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((event) => {
                if (!this.gridComState) {
                    Context.animateTo({
                        duration: v1,
                        curve: w1
                    }, () => {
                        this.gridComState = true;
                    });
                    this.menuSwitch = true;
                }
                else {
                    Context.animateTo({
                        duration: v1,
                        curve: b2
                    }, () => {
                        this.longScaleOnePointTwo = 1.05;
                    });
                    if (event.repeat && !this.vibrationDone) {
                        try {
                            vibrator.startVibration({
                                type: 'time',
                                duration: 1000
                            }, {
                                id: 0,
                                usage: 'alarm'
                            }).then(() => {
                                this.vibrationDone = true;
                            });
                        }
                        catch {
                            this.vibrationDone = false;
                        }
                    }
                }
                this.calcGridHeight();
            });
            LongPressGesture.onActionCancel(() => {
                if (this.isStartDrag) {
                    this.insertItem(this.itemIndex, this.itemIndex);
                }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Grid.clip(false);
            Grid.editMode(this.gridComState);
            Grid.columnsTemplate(this.customColumns);
            Grid.padding({
                left: i1,
                right: i1
            });
            Grid.height(this.editGridHeight);
            Context.animation(null);
            Grid.onItemDragStart((event, itemIndex) => {
                this.itemIndex = itemIndex;
                this.selectedIndex = -1;
                if (!this.gridComState) {
                    return;
                }
                this.isStartDrag = true;
                this.insertIndex = itemIndex;
                this.dragContent = this.selected[itemIndex];
                this.dragContentIndex = itemIndex;
                return { builder: () => {
                        this.PixelMapBuilder.call(this, this.dragContent?.symbolStyle || this.dragContent?.url, this.dragContent?.text);
                    } };
            });
            Grid.onItemDrop((event, itemIndex, insertIndex, isSuccess) => {
                this.insertItem(itemIndex, insertIndex);
            });
            Grid.onItemDragMove((event, itemIndex, insertIndex) => this.onDragMoveEvent(event, itemIndex, insertIndex));
        }, Grid);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const select = _item;
                {
                    const itemCreation2 = (elmtId, isInitialRender) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.isStartDrag ? z1 : index === this.selectedIndex ? a2 : z1,
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getShowAreaItemTranslate(index));
                        Context.animation(null);
                        GridItem.visibility(select.visibility);
                    };
                    const observedDeepRender = () => {
                        this.observeComponentCreation2(itemCreation2, GridItem);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Stack.create();
                            Stack.onHover((isHover) => {
                                if (isHover) {
                                    this.hoverId = select.id;
                                }
                                else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.clip(false);
                            Stack.margin({
                                bottom: this.imageText ? i1 : this.gridComState ? i1 : h1
                            });
                            Stack.onTouch((event) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (event.type === TouchType.Down) {
                                    this.content = select;
                                    this.isTouchDown = true;
                                }
                                if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                                    this.isTouchDown = false;
                                    Context.animateTo({
                                        duration: v1,
                                        curve: b2
                                    }, () => {
                                        this.longScaleOnePointTwo = 1;
                                    });
                                }
                            });
                        }, Stack);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(select, 'delete');
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockBuilder.bind(this)(select);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    observedDeepRender();
                }
            };
            this.forEachUpdateFunction(elmtId, this.selected, forEachItemGenFunction, (item) => item.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
        Column.pop();
    }
    insertItem(itemIndex, insertIndex) {
        if (!this.gridComState) {
            return;
        }
        this.vibrationDone = false;
        Context.animateTo({
            duration: v1,
            curve: b2
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
        this.isStartDrag = false;
        if (insertIndex !== -1) {
            this.selected.splice(itemIndex, 1);
            this.selected.splice(insertIndex, 0, this.dragContent);
        }
        this.dragContent.visibility = Visibility.Visible;
        this.calcGridHeight();
    }
    calcAreaInfo() {
        this.calcColNum();
        this.blockWidth = this.getBlockWidth();
        this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
        this.imageItemWidth = this.blockWidth - 16;
        this.calcTextItemEditHeight();
        this.blockHeight = this.imageText ? this.imageItemWidth + u1 : this.gridComState ?
            this.textItemEditHeight + u1 :
            this.textItemEditHeight + t1;
        this.calcGridHeight();
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
            Column.height('90%');
        }, Column);
        this.HeaderTitleBuilder.bind(this)();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.onAreaChange((oldValue, newValue) => {
                this.areaWidth = Number(newValue.width);
                this.calcAreaInfo();
            });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.margin({ bottom: h1 });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/GridObjectSortComponent.ets", line: 1441, c2: 11 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.showAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        icon: '',
                        operationType: OperationType.BUTTON
                    });
                }
            }, { name: "SubHeader" });
        }
        __Common__.pop();
        this.EditTagBuilder.bind(this)();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            Context.animation({
                duration: v1,
                curve: this.imageText ? a2 : w1,
            });
            __Common__.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {});
            Context.animation(null);
            __Common__.margin({ bottom: h1 });
            __Common__.onAreaChange((oldValue, newValue) => {
                this.subTitleHeight = Number(newValue.height);
            });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/GridObjectSortComponent.ets", line: 1450, c2: 11 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.addAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        icon: '',
                        operationType: OperationType.BUTTON
                    });
                }
            }, { name: "SubHeader" });
        }
        __Common__.pop();
        this.AddTagBuilder.bind(this)();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    GridObjectSortComponent, GridObjectSortComponentType
}