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

const vibrator = requireNativeModule('ohos.vibrator');
const curves = requireNativeModule('ohos.curves');
const composetitlebar = requireNapi('arkui.advanced.ComposeTitleBar');
const editabletitlebar = requireNapi('arkui.advanced.EditableTitleBar');
const subheader = requireNapi('arkui.advanced.SubHeader');
const hilog = requireNapi('hilog');

const ComposeTitleBar = composetitlebar.ComposeTitleBar;
const EditableTitleBar = editabletitlebar.EditableTitleBar;
const EditableLeftIconType = editabletitlebar.EditableLeftIconType;
const SubHeader = subheader.SubHeader;
const OperationType = subheader.OperationType;

const COL_IMAGE_TEXT = 3;
const COL_TEXT = 4;
const GRID_COL_3 = '1fr 1fr 1fr';
const GRID_COL_4 = '1fr 1fr 1fr 1fr';
const BLOCK_TEXT_HEIGHT = 36;
const ICON_SIZE = 24;
const IMAGE_DEFAULT = 56;
const TEXT_PADDING_LEFT_RIGHT = 12;
const MARGIN_EIGHT = 8;
const ROW_GAP = 16;
const SUBTITLE_HEIGHT = 56;
const TEXT_MAX_LINES = 1;
const MIN_FONT_SCALE = 1;
const MAX_FONT_SCALE = 2;
const ENTER_EXIT_ICON_DURATION = 200;
const COMMON_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1);
const DRAG_SPRING = curves.interpolatingSpring(0, 1, 400, 38);
const REMOVE_ADD_SPRING = curves.interpolatingSpring(0, 1, 150, 24);
const LONG_TOUCH_SCALE = curves.cubicBezierCurve(0.2, 0, 0.2, 1);
export var GridObjectSortComponentType;
(function (b17) {
    b17["IMAGE_TEXT"] = "image_text";
    b17["TEXT"] = "text";
})(GridObjectSortComponentType || (GridObjectSortComponentType = {}));
class MenuItem {
    constructor(y16, z16, a17) {
        this.value = y16;
        this.isEnabled = z16;
        this.action = a17;
    }
}
export class GridObjectSortComponent extends ViewPU {
    constructor(o16, p16, q16, r16 = -1, s16 = undefined, t16) {
        super(o16, q16, r16, t16);
        if (typeof s16 === "function") {
            this.paramsGenerator_ = s16;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(p16.options, this, "options");
        this.dataList = [];
        this.__selected = new ObservedPropertyObjectPU([], this, "selected");
        this.__unSelected = new ObservedPropertyObjectPU([], this, "unSelected");
        this.__copySelected = new ObservedPropertyObjectPU([], this, "copySelected");
        this.__copyUnSelected = new ObservedPropertyObjectPU([], this, "copyUnSelected");
        this.__content = new ObservedPropertyObjectPU({ id: '', text: '', selected: false, order: 0 }, this, "content");
        this.__dragContent = new ObservedPropertyObjectPU({ id: '', text: '', selected: false, order: 0 }, this, "dragContent");
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
        this.__imageItemWidth = new ObservedPropertySimplePU(0, this, "imageItemWidth");
        this.__saveClick = new ObservedPropertySimplePU(false, this, "saveClick");
        this.__imageTextAddIconShow = new ObservedPropertySimplePU(false, this, "imageTextAddIconShow");
        this.__imageTextRemoveIconShow = new ObservedPropertySimplePU(false, this, "imageTextRemoveIconShow");
        this.__firstIn = new ObservedPropertySimplePU(true, this, "firstIn");
        this.__fontSizeScale = new ObservedPropertyObjectPU(1, this, "fontSizeScale");
        this.__customColumns = new ObservedPropertySimplePU('1fr 1fr 1fr 1fr', this, "customColumns");
        this.__editGridHeight = new ObservedPropertySimplePU(0, this, "editGridHeight");
        this.__addGridHeight = new ObservedPropertySimplePU(0, this, "addGridHeight");
        this.__subTitleHeight = new ObservedPropertySimplePU(0, this, "subTitleHeight");
        this.callbackId = undefined;
        this.colNum = COL_IMAGE_TEXT;
        this.vibrationDone = false;
        this.touchDown = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.touchBorderRadius = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.hoverBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.focusBorder = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.imageText = false;
        this.menuItems = [
            new MenuItem({ "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_edit'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, true, () => {
                this.goEdit();
            }),
        ];
        this.onSave = undefined;
        this.onCancel = undefined;
        this.isFollowingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.envCallback = {
            onConfigurationUpdated: (w16) => {
                let x16 = this.getUIContext();
                this.fontSizeScale = this.decideFontScale(x16);
            },
            onMemoryLevel: (v16) => { }
        };
        this.setInitiallyProvidedValue(p16);
        this.declareWatch("gridComState", this.onGridComStateChange);
        this.declareWatch("fontSizeScale", this.calcAreaInfo);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(n16) {
        if (n16.options === undefined) {
            this.__options.set({});
        }
        if (n16.dataList !== undefined) {
            this.dataList = n16.dataList;
        }
        if (n16.selected !== undefined) {
            this.selected = n16.selected;
        }
        if (n16.unSelected !== undefined) {
            this.unSelected = n16.unSelected;
        }
        if (n16.copySelected !== undefined) {
            this.copySelected = n16.copySelected;
        }
        if (n16.copyUnSelected !== undefined) {
            this.copyUnSelected = n16.copyUnSelected;
        }
        if (n16.content !== undefined) {
            this.content = n16.content;
        }
        if (n16.dragContent !== undefined) {
            this.dragContent = n16.dragContent;
        }
        if (n16.dragContentIndex !== undefined) {
            this.dragContentIndex = n16.dragContentIndex;
        }
        if (n16.hoverId !== undefined) {
            this.hoverId = n16.hoverId;
        }
        if (n16.gridComState !== undefined) {
            this.gridComState = n16.gridComState;
        }
        if (n16.menuSwitch !== undefined) {
            this.menuSwitch = n16.menuSwitch;
        }
        if (n16.areaWidth !== undefined) {
            this.areaWidth = n16.areaWidth;
        }
        if (n16.blockWidth !== undefined) {
            this.blockWidth = n16.blockWidth;
        }
        if (n16.blockHeight !== undefined) {
            this.blockHeight = n16.blockHeight;
        }
        if (n16.longScaleOnePointTwo !== undefined) {
            this.longScaleOnePointTwo = n16.longScaleOnePointTwo;
        }
        if (n16.scaleGridItemNinetyPercent !== undefined) {
            this.scaleGridItemNinetyPercent = n16.scaleGridItemNinetyPercent;
        }
        if (n16.reboundSize !== undefined) {
            this.reboundSize = n16.reboundSize;
        }
        if (n16.scaleIcon !== undefined) {
            this.scaleIcon = n16.scaleIcon;
        }
        if (n16.addIconShow !== undefined) {
            this.addIconShow = n16.addIconShow;
        }
        if (n16.scaleAddIcon !== undefined) {
            this.scaleAddIcon = n16.scaleAddIcon;
        }
        if (n16.isStartDrag !== undefined) {
            this.isStartDrag = n16.isStartDrag;
        }
        if (n16.insertIndex !== undefined) {
            this.insertIndex = n16.insertIndex;
        }
        if (n16.itemIndex !== undefined) {
            this.itemIndex = n16.itemIndex;
        }
        if (n16.editGridDataLength !== undefined) {
            this.editGridDataLength = n16.editGridDataLength;
        }
        if (n16.isTouchDown !== undefined) {
            this.isTouchDown = n16.isTouchDown;
        }
        if (n16.addItemMoveX !== undefined) {
            this.addItemMoveX = n16.addItemMoveX;
        }
        if (n16.addItemMoveY !== undefined) {
            this.addItemMoveY = n16.addItemMoveY;
        }
        if (n16.editItemMoveX !== undefined) {
            this.editItemMoveX = n16.editItemMoveX;
        }
        if (n16.editItemMoveY !== undefined) {
            this.editItemMoveY = n16.editItemMoveY;
        }
        if (n16.unSelectedIndex !== undefined) {
            this.unSelectedIndex = n16.unSelectedIndex;
        }
        if (n16.clickAddBtn !== undefined) {
            this.clickAddBtn = n16.clickAddBtn;
        }
        if (n16.selectedIndex !== undefined) {
            this.selectedIndex = n16.selectedIndex;
        }
        if (n16.clickRemoveBtn !== undefined) {
            this.clickRemoveBtn = n16.clickRemoveBtn;
        }
        if (n16.addAreaLongPressGesture !== undefined) {
            this.addAreaLongPressGesture = n16.addAreaLongPressGesture;
        }
        if (n16.arraySelectIsChange !== undefined) {
            this.arraySelectIsChange = n16.arraySelectIsChange;
        }
        if (n16.arrayUnSelectIsChange !== undefined) {
            this.arrayUnSelectIsChange = n16.arrayUnSelectIsChange;
        }
        if (n16.textItemEditWidth !== undefined) {
            this.textItemEditWidth = n16.textItemEditWidth;
        }
        if (n16.imageItemWidth !== undefined) {
            this.imageItemWidth = n16.imageItemWidth;
        }
        if (n16.saveClick !== undefined) {
            this.saveClick = n16.saveClick;
        }
        if (n16.imageTextAddIconShow !== undefined) {
            this.imageTextAddIconShow = n16.imageTextAddIconShow;
        }
        if (n16.imageTextRemoveIconShow !== undefined) {
            this.imageTextRemoveIconShow = n16.imageTextRemoveIconShow;
        }
        if (n16.firstIn !== undefined) {
            this.firstIn = n16.firstIn;
        }
        if (n16.fontSizeScale !== undefined) {
            this.fontSizeScale = n16.fontSizeScale;
        }
        if (n16.customColumns !== undefined) {
            this.customColumns = n16.customColumns;
        }
        if (n16.editGridHeight !== undefined) {
            this.editGridHeight = n16.editGridHeight;
        }
        if (n16.addGridHeight !== undefined) {
            this.addGridHeight = n16.addGridHeight;
        }
        if (n16.subTitleHeight !== undefined) {
            this.subTitleHeight = n16.subTitleHeight;
        }
        if (n16.callbackId !== undefined) {
            this.callbackId = n16.callbackId;
        }
        if (n16.colNum !== undefined) {
            this.colNum = n16.colNum;
        }
        if (n16.vibrationDone !== undefined) {
            this.vibrationDone = n16.vibrationDone;
        }
        if (n16.touchDown !== undefined) {
            this.touchDown = n16.touchDown;
        }
        if (n16.touchBorderRadius !== undefined) {
            this.touchBorderRadius = n16.touchBorderRadius;
        }
        if (n16.hoverBackgroundColor !== undefined) {
            this.hoverBackgroundColor = n16.hoverBackgroundColor;
        }
        if (n16.focusBorder !== undefined) {
            this.focusBorder = n16.focusBorder;
        }
        if (n16.imageText !== undefined) {
            this.imageText = n16.imageText;
        }
        if (n16.menuItems !== undefined) {
            this.menuItems = n16.menuItems;
        }
        if (n16.onSave !== undefined) {
            this.onSave = n16.onSave;
        }
        if (n16.onCancel !== undefined) {
            this.onCancel = n16.onCancel;
        }
        if (n16.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = n16.isFollowingSystemFontScale;
        }
        if (n16.maxAppFontScale !== undefined) {
            this.maxAppFontScale = n16.maxAppFontScale;
        }
        if (n16.envCallback !== undefined) {
            this.envCallback = n16.envCallback;
        }
    }
    updateStateVars(m16) {
        this.__options.reset(m16.options);
    }
    purgeVariableDependenciesOnElmtId(l16) {
        this.__options.purgeDependencyOnElmtId(l16);
        this.__selected.purgeDependencyOnElmtId(l16);
        this.__unSelected.purgeDependencyOnElmtId(l16);
        this.__copySelected.purgeDependencyOnElmtId(l16);
        this.__copyUnSelected.purgeDependencyOnElmtId(l16);
        this.__content.purgeDependencyOnElmtId(l16);
        this.__dragContent.purgeDependencyOnElmtId(l16);
        this.__dragContentIndex.purgeDependencyOnElmtId(l16);
        this.__hoverId.purgeDependencyOnElmtId(l16);
        this.__gridComState.purgeDependencyOnElmtId(l16);
        this.__menuSwitch.purgeDependencyOnElmtId(l16);
        this.__areaWidth.purgeDependencyOnElmtId(l16);
        this.__blockWidth.purgeDependencyOnElmtId(l16);
        this.__blockHeight.purgeDependencyOnElmtId(l16);
        this.__longScaleOnePointTwo.purgeDependencyOnElmtId(l16);
        this.__scaleGridItemNinetyPercent.purgeDependencyOnElmtId(l16);
        this.__reboundSize.purgeDependencyOnElmtId(l16);
        this.__scaleIcon.purgeDependencyOnElmtId(l16);
        this.__addIconShow.purgeDependencyOnElmtId(l16);
        this.__scaleAddIcon.purgeDependencyOnElmtId(l16);
        this.__isStartDrag.purgeDependencyOnElmtId(l16);
        this.__insertIndex.purgeDependencyOnElmtId(l16);
        this.__itemIndex.purgeDependencyOnElmtId(l16);
        this.__editGridDataLength.purgeDependencyOnElmtId(l16);
        this.__isTouchDown.purgeDependencyOnElmtId(l16);
        this.__addItemMoveX.purgeDependencyOnElmtId(l16);
        this.__addItemMoveY.purgeDependencyOnElmtId(l16);
        this.__editItemMoveX.purgeDependencyOnElmtId(l16);
        this.__editItemMoveY.purgeDependencyOnElmtId(l16);
        this.__unSelectedIndex.purgeDependencyOnElmtId(l16);
        this.__clickAddBtn.purgeDependencyOnElmtId(l16);
        this.__selectedIndex.purgeDependencyOnElmtId(l16);
        this.__clickRemoveBtn.purgeDependencyOnElmtId(l16);
        this.__addAreaLongPressGesture.purgeDependencyOnElmtId(l16);
        this.__arraySelectIsChange.purgeDependencyOnElmtId(l16);
        this.__arrayUnSelectIsChange.purgeDependencyOnElmtId(l16);
        this.__textItemEditWidth.purgeDependencyOnElmtId(l16);
        this.__imageItemWidth.purgeDependencyOnElmtId(l16);
        this.__saveClick.purgeDependencyOnElmtId(l16);
        this.__imageTextAddIconShow.purgeDependencyOnElmtId(l16);
        this.__imageTextRemoveIconShow.purgeDependencyOnElmtId(l16);
        this.__firstIn.purgeDependencyOnElmtId(l16);
        this.__fontSizeScale.purgeDependencyOnElmtId(l16);
        this.__customColumns.purgeDependencyOnElmtId(l16);
        this.__editGridHeight.purgeDependencyOnElmtId(l16);
        this.__addGridHeight.purgeDependencyOnElmtId(l16);
        this.__subTitleHeight.purgeDependencyOnElmtId(l16);
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
        this.__imageItemWidth.aboutToBeDeleted();
        this.__saveClick.aboutToBeDeleted();
        this.__imageTextAddIconShow.aboutToBeDeleted();
        this.__imageTextRemoveIconShow.aboutToBeDeleted();
        this.__firstIn.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
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
    set options(k16) {
        this.__options.set(k16);
    }
    get selected() {
        return this.__selected.get();
    }
    set selected(j16) {
        this.__selected.set(j16);
    }
    get unSelected() {
        return this.__unSelected.get();
    }
    set unSelected(i16) {
        this.__unSelected.set(i16);
    }
    get copySelected() {
        return this.__copySelected.get();
    }
    set copySelected(h16) {
        this.__copySelected.set(h16);
    }
    get copyUnSelected() {
        return this.__copyUnSelected.get();
    }
    set copyUnSelected(g16) {
        this.__copyUnSelected.set(g16);
    }
    get content() {
        return this.__content.get();
    }
    set content(f16) {
        this.__content.set(f16);
    }
    get dragContent() {
        return this.__dragContent.get();
    }
    set dragContent(e16) {
        this.__dragContent.set(e16);
    }
    get dragContentIndex() {
        return this.__dragContentIndex.get();
    }
    set dragContentIndex(d16) {
        this.__dragContentIndex.set(d16);
    }
    get hoverId() {
        return this.__hoverId.get();
    }
    set hoverId(c16) {
        this.__hoverId.set(c16);
    }
    get gridComState() {
        return this.__gridComState.get();
    }
    set gridComState(b16) {
        this.__gridComState.set(b16);
    }
    get menuSwitch() {
        return this.__menuSwitch.get();
    }
    set menuSwitch(a16) {
        this.__menuSwitch.set(a16);
    }
    get areaWidth() {
        return this.__areaWidth.get();
    }
    set areaWidth(z15) {
        this.__areaWidth.set(z15);
    }
    get blockWidth() {
        return this.__blockWidth.get();
    }
    set blockWidth(y15) {
        this.__blockWidth.set(y15);
    }
    get blockHeight() {
        return this.__blockHeight.get();
    }
    set blockHeight(x15) {
        this.__blockHeight.set(x15);
    }
    get longScaleOnePointTwo() {
        return this.__longScaleOnePointTwo.get();
    }
    set longScaleOnePointTwo(w15) {
        this.__longScaleOnePointTwo.set(w15);
    }
    get scaleGridItemNinetyPercent() {
        return this.__scaleGridItemNinetyPercent.get();
    }
    set scaleGridItemNinetyPercent(v15) {
        this.__scaleGridItemNinetyPercent.set(v15);
    }
    get reboundSize() {
        return this.__reboundSize.get();
    }
    set reboundSize(u15) {
        this.__reboundSize.set(u15);
    }
    get scaleIcon() {
        return this.__scaleIcon.get();
    }
    set scaleIcon(t15) {
        this.__scaleIcon.set(t15);
    }
    get addIconShow() {
        return this.__addIconShow.get();
    }
    set addIconShow(s15) {
        this.__addIconShow.set(s15);
    }
    get scaleAddIcon() {
        return this.__scaleAddIcon.get();
    }
    set scaleAddIcon(r15) {
        this.__scaleAddIcon.set(r15);
    }
    get isStartDrag() {
        return this.__isStartDrag.get();
    }
    set isStartDrag(q15) {
        this.__isStartDrag.set(q15);
    }
    get insertIndex() {
        return this.__insertIndex.get();
    }
    set insertIndex(p15) {
        this.__insertIndex.set(p15);
    }
    get itemIndex() {
        return this.__itemIndex.get();
    }
    set itemIndex(o15) {
        this.__itemIndex.set(o15);
    }
    get editGridDataLength() {
        return this.__editGridDataLength.get();
    }
    set editGridDataLength(n15) {
        this.__editGridDataLength.set(n15);
    }
    get isTouchDown() {
        return this.__isTouchDown.get();
    }
    set isTouchDown(m15) {
        this.__isTouchDown.set(m15);
    }
    get addItemMoveX() {
        return this.__addItemMoveX.get();
    }
    set addItemMoveX(l15) {
        this.__addItemMoveX.set(l15);
    }
    get addItemMoveY() {
        return this.__addItemMoveY.get();
    }
    set addItemMoveY(k15) {
        this.__addItemMoveY.set(k15);
    }
    get editItemMoveX() {
        return this.__editItemMoveX.get();
    }
    set editItemMoveX(j15) {
        this.__editItemMoveX.set(j15);
    }
    get editItemMoveY() {
        return this.__editItemMoveY.get();
    }
    set editItemMoveY(i15) {
        this.__editItemMoveY.set(i15);
    }
    get unSelectedIndex() {
        return this.__unSelectedIndex.get();
    }
    set unSelectedIndex(h15) {
        this.__unSelectedIndex.set(h15);
    }
    get clickAddBtn() {
        return this.__clickAddBtn.get();
    }
    set clickAddBtn(g15) {
        this.__clickAddBtn.set(g15);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(f15) {
        this.__selectedIndex.set(f15);
    }
    get clickRemoveBtn() {
        return this.__clickRemoveBtn.get();
    }
    set clickRemoveBtn(e15) {
        this.__clickRemoveBtn.set(e15);
    }
    get addAreaLongPressGesture() {
        return this.__addAreaLongPressGesture.get();
    }
    set addAreaLongPressGesture(d15) {
        this.__addAreaLongPressGesture.set(d15);
    }
    get arraySelectIsChange() {
        return this.__arraySelectIsChange.get();
    }
    set arraySelectIsChange(c15) {
        this.__arraySelectIsChange.set(c15);
    }
    get arrayUnSelectIsChange() {
        return this.__arrayUnSelectIsChange.get();
    }
    set arrayUnSelectIsChange(b15) {
        this.__arrayUnSelectIsChange.set(b15);
    }
    get textItemEditWidth() {
        return this.__textItemEditWidth.get();
    }
    set textItemEditWidth(a15) {
        this.__textItemEditWidth.set(a15);
    }
    get imageItemWidth() {
        return this.__imageItemWidth.get();
    }
    set imageItemWidth(z14) {
        this.__imageItemWidth.set(z14);
    }
    get saveClick() {
        return this.__saveClick.get();
    }
    set saveClick(y14) {
        this.__saveClick.set(y14);
    }
    get imageTextAddIconShow() {
        return this.__imageTextAddIconShow.get();
    }
    set imageTextAddIconShow(x14) {
        this.__imageTextAddIconShow.set(x14);
    }
    get imageTextRemoveIconShow() {
        return this.__imageTextRemoveIconShow.get();
    }
    set imageTextRemoveIconShow(w14) {
        this.__imageTextRemoveIconShow.set(w14);
    }
    get firstIn() {
        return this.__firstIn.get();
    }
    set firstIn(v14) {
        this.__firstIn.set(v14);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(u14) {
        this.__fontSizeScale.set(u14);
    }
    get customColumns() {
        return this.__customColumns.get();
    }
    set customColumns(t14) {
        this.__customColumns.set(t14);
    }
    get editGridHeight() {
        return this.__editGridHeight.get();
    }
    set editGridHeight(s14) {
        this.__editGridHeight.set(s14);
    }
    get addGridHeight() {
        return this.__addGridHeight.get();
    }
    set addGridHeight(r14) {
        this.__addGridHeight.set(r14);
    }
    get subTitleHeight() {
        return this.__subTitleHeight.get();
    }
    set subTitleHeight(q14) {
        this.__subTitleHeight.set(q14);
    }
    aboutToAppear() {
        this.dataList.length = 50;
        this.selected = this.dataList && this.deduplicate(this.dataList).filter(p14 => p14.selected).sort(this.sortBy());
        this.unSelected = this.dataList && this.deduplicate(this.dataList).filter(o14 => !o14.selected).sort(this.sortBy());
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
        try {
            let d2 = this.getUIContext();
            this.isFollowingSystemFontScale = d2.isFollowingSystemFontScale();
            this.maxAppFontScale = d2.getMaxFontScale();
            this.fontSizeScale = this.decideFontScale(d2);
        }
        catch (z1) {
            let a2 = z1.code;
            let b2 = z1.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code:${a2}, message: ${b2}`);
        }
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        }
        catch (t1) {
            console.error(`error: ${t1.code}, ${t1.message}`);
        }
        this.calcGridHeight();
        setTimeout(() => {
            this.firstIn = false;
        }, 500);
    }
    decideFontScale(f14) {
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        let i14 = f14.getHostContext()?.config.fontSizeScale ?? 1;
        return Math.min(i14, this.maxAppFontScale, MAX_FONT_SCALE);
    }
    calcColNum() {
        if (this.imageText || (this.fontSizeScale && this.fontSizeScale > 1)) {
            this.customColumns = GRID_COL_3;
            this.colNum = COL_IMAGE_TEXT;
        }
        else {
            this.customColumns = GRID_COL_4;
            this.colNum = COL_TEXT;
        }
    }
    aboutToDisappear() {
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER,
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
    deduplicate(y13) {
        const z13 = [];
        y13.forEach(b14 => {
            if (!z13.some(d14 => d14.id === b14.id)) {
                z13.push(b14);
            }
        });
        return z13;
    }
    onGridComStateChange() {
        this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
        if (!this.imageText) {
            this.blockHeight = this.gridComState ? 44 : BLOCK_TEXT_HEIGHT;
        }
    }
    sortBy() {
        return (w13, x13) => {
            return w13.order - x13.order;
        };
    }
    cancelEdit() {
        if (this.isStartDrag || this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: LONG_TOUCH_SCALE
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER,
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
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER,
        }, () => {
            this.gridComState = true;
        });
        this.menuSwitch = true;
        this.calcGridHeight();
    }
    onSaveEdit() {
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: LONG_TOUCH_SCALE
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
        this.editGridDataLength = this.selected.length;
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: COMMON_BEZIER,
        }, () => {
            this.gridComState = false;
            this.copySelected = this.selected.slice();
            this.copyUnSelected = this.unSelected.slice();
            const q13 = this.getNewData(this.selected, true, 0);
            const r13 = this.getNewData(this.unSelected, false, this.selected.length);
            this.selected = q13;
            this.unSelected = r13;
            this.calcGridHeight();
            this.onSave && this.onSave(q13, r13);
        });
        setTimeout(() => {
            this.saveClick = false;
        }, ENTER_EXIT_ICON_DURATION);
        this.menuSwitch = false;
    }
    onDragMoveEvent(j13, k13, l13) {
        if (!this.gridComState || (j13.x < this.blockWidth / 3 && j13.y < this.blockHeight / 3)) {
            return;
        }
        let m13 = l13;
        if (m13 < 0) {
            m13 = this.selected.length - 1;
        }
        if (this.dragContent.visibility !== Visibility.Hidden) {
            this.dragContent.visibility = Visibility.Hidden;
        }
        this.insertIndex = l13;
    }
    handleDeleteClick(d13) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.clickRemoveBtn = true;
        this.scaleIcon = 0;
        this.arraySelectIsChange = 1;
        let e13 = this.selected.findIndex(i13 => i13.id === d13.id);
        this.content = d13;
        this.selectedIndex = e13;
        this.calcGridHeight();
        Context.animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
            this.scaleIcon = 1;
            this.selected.splice(e13, 1);
            this.unSelected.unshift(d13);
            this.calcGridHeight();
            this.editGridDataLength = this.editGridDataLength - 1;
            this.editItemMoveX = 0;
            this.editItemMoveY = 0;
            this.arraySelectIsChange = 2;
            this.clickRemoveBtn = false;
        } }, () => {
            let h13 = this.getAddItemGridPosition();
            this.editItemMoveX = h13.x;
            this.editItemMoveY = h13.y;
        });
    }
    getNewData(x12, y12, z12) {
        return x12.map((b13, c13) => {
            b13.selected = y12;
            b13.order = z12 + c13;
            b13.visibility = Visibility.Visible;
            return b13;
        });
    }
    getBlockWidth() {
        const w12 = (this.areaWidth - 32) / this.colNum;
        return w12;
    }
    calcGridHeight() {
        this.editGridHeight = this.getGridHeight(this.selected, 'edit');
        this.addGridHeight = this.getGridHeight(this.unSelected);
    }
    getGridHeight(n12, o12) {
        let p12 = 0;
        let q12 = n12.length;
        n12.forEach(v12 => {
            if (v12.visibility === Visibility.Hidden) {
                q12 = q12 - 1;
            }
        });
        let r12 = 0;
        let s12 = q12 % this.colNum === 0;
        if (this.clickAddBtn && s12) {
            r12 = 1;
        }
        else if (this.isStartDrag && s12 && o12) {
            r12 = 1;
        }
        else if (this.clickRemoveBtn && s12 && !o12) {
            r12 = 1;
        }
        else {
            r12 = 0;
        }
        let t12 = Math.ceil(q12 / this.colNum) + r12;
        p12 = this.blockHeight * t12;
        if (q12 === 0) {
            p12 = 0;
        }
        return p12;
    }
    imageTextRemoveIcon(k12) {
        const l12 = this.clickRemoveBtn && this.content.id === k12.id;
        const m12 = l12 ? { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_add_norm_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_remove_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        return m12;
    }
    imageTextAddIcon(h12) {
        const i12 = this.clickAddBtn && this.content.id === h12.id && this.gridComState;
        const j12 = i12 ? { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_remove_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_add_norm_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        return j12;
    }
    imageTextAddIconVisible(e12) {
        const f12 = this.clickAddBtn && this.content.id === e12.id && !this.gridComState;
        const g12 = f12 ? Visibility.Hidden : Visibility.Visible;
        return g12;
    }
    getCoodXY(z11) {
        let a12 = 0;
        let b12 = 0;
        const c12 = this.colNum;
        const d12 = Math.trunc(z11 % c12);
        if (z11 >= this.dragContentIndex) {
            if (z11 <= this.insertIndex && z11 !== this.dragContentIndex) {
                if (d12 === 0) {
                    a12 = a12 + this.blockWidth * (c12 - 1);
                    b12 = b12 - this.blockHeight;
                }
                else {
                    a12 = a12 - this.blockWidth;
                }
            }
        }
        else {
            if (z11 >= this.insertIndex) {
                if (d12 === c12 - 1) {
                    a12 = a12 - this.blockWidth * (c12 - 1);
                    b12 = b12 + this.blockHeight;
                }
                else {
                    a12 = a12 + this.blockWidth;
                }
            }
        }
        if (!this.isStartDrag) {
            a12 = 0;
            b12 = 0;
        }
        return { x: a12, y: b12 };
    }
    getAddItemGridPosition() {
        const n11 = this.selected.length;
        const o11 = this.colNum;
        const p11 = (this.selectedIndex + 1) % o11;
        const q11 = Math.ceil((this.selectedIndex + 1) / o11);
        const r11 = Math.ceil(n11 / o11);
        const s11 = this.imageText;
        let t11 = 0;
        if (p11 === 0) {
            t11 = s11 || (this.fontSizeScale && this.fontSizeScale > 1) ? -this.blockWidth * 2 : -this.blockWidth * 3;
        }
        else {
            t11 = -this.blockWidth * (p11 - 1);
        }
        let u11 = SUBTITLE_HEIGHT;
        let v11 = 0;
        const w11 = r11 - q11;
        const x11 = n11 % o11;
        const y11 = x11 === 1 ? w11 : w11 + 1;
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            u11 = this.subTitleHeight;
        }
        v11 = y11 * this.blockHeight + u11;
        return {
            x: t11,
            y: v11
        };
    }
    getCoveringGridPosition(k11) {
        let l11 = 0;
        let m11 = 0;
        if (k11 > this.selectedIndex && this.arraySelectIsChange !== 2) {
            l11 = k11 % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            m11 = k11 % this.colNum === 0 ? -this.blockHeight : 0;
        }
        return {
            x: l11,
            y: m11
        };
    }
    getEditItemGridPosition(y10, z10) {
        const a11 = y10.length;
        const b11 = this.colNum;
        const c11 = Math.trunc(a11 % b11);
        const d11 = Math.trunc(z10 % b11);
        let e11 = Math.abs(c11 - d11) * this.blockWidth;
        if (c11 < d11) {
            e11 = -e11;
        }
        else if (c11 > d11) {
            e11 = e11;
        }
        else {
            e11 = 0;
        }
        let f11 = 0;
        let g11 = 0;
        let h11 = Math.trunc(z10 / this.colNum);
        let i11 = SUBTITLE_HEIGHT;
        const j11 = !this.imageText && this.gridComState && z10 > 3;
        if (j11) {
            g11 = (h11 + 1) * (this.blockHeight - 8) + 8;
        }
        else {
            g11 = (h11 + 1) * this.blockHeight;
        }
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            i11 = this.subTitleHeight;
        }
        f11 = g11 + i11;
        return {
            x: e11,
            y: f11
        };
    }
    getCoveringGridPositionBottom(t10) {
        let u10 = 0;
        let v10 = 0;
        const w10 = t10 % this.colNum === 0;
        const x10 = this.gridComState && !this.imageText ? -this.blockHeight + 8 : -this.blockHeight;
        if (t10 > this.unSelectedIndex && this.arrayUnSelectIsChange !== 2) {
            u10 = w10 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            v10 = w10 ? x10 : 0;
        }
        return {
            x: u10,
            y: v10
        };
    }
    getAddItemRightMove(p10) {
        let q10 = this.blockWidth;
        let r10 = 0;
        let s10 = (p10 + 1) % this.colNum === 0;
        if (s10) {
            q10 = -this.blockWidth * (this.colNum - 1);
            r10 = this.imageText ? this.blockHeight : this.blockHeight - 8;
        }
        return { x: q10, y: r10 };
    }
    getShowAreaItemTranslate(m10) {
        if (this.isStartDrag) {
            let o10 = this.getCoodXY(m10);
            return {
                x: o10.x,
                y: o10.y
            };
        }
        if (!this.isStartDrag && m10 === this.selectedIndex) {
            return {
                x: this.editItemMoveX,
                y: this.editItemMoveY
            };
        }
        if (!this.isStartDrag && m10 !== this.selectedIndex && this.clickRemoveBtn) {
            let n10 = this.getCoveringGridPosition(m10);
            return {
                x: n10.x,
                y: n10.y
            };
        }
        return { x: 0, y: 0 };
    }
    getAddAreaItemTranslate(j10) {
        if (this.clickRemoveBtn) {
            let l10 = this.getAddItemRightMove(j10);
            return {
                x: l10.x,
                y: l10.y
            };
        }
        if (!this.clickRemoveBtn && j10 === this.unSelectedIndex) {
            return {
                x: this.addItemMoveX,
                y: -this.addItemMoveY
            };
        }
        if (!this.clickRemoveBtn && j10 !== this.unSelectedIndex && this.clickAddBtn) {
            let k10 = this.getCoveringGridPositionBottom(j10);
            return {
                x: k10.x,
                y: k10.y
            };
        }
        return { x: 0, y: 0 };
    }
    PixelMapBuilder(d9, e9, f9 = null) {
        this.observeComponentCreation2((h10, i10) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.clip(false);
            Stack.height(this.blockHeight * 1.5);
            Stack.width(this.blockWidth * 1.2);
        }, Stack);
        this.observeComponentCreation2((i9, j9) => {
            If.create();
            if (this.imageText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f10, g10) => {
                        Column.create();
                        Column.alignItems(HorizontalAlign.Center);
                        Column.justifyContent(FlexAlign.Center);
                        Column.width(this.imageItemWidth);
                        Column.height(this.imageItemWidth);
                        Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
                        Column.backgroundColor(this.touchDown);
                        Column.borderRadius(this.touchBorderRadius);
                        Column.scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo });
                    }, Column);
                    this.observeComponentCreation2((d10, e10) => {
                        Image.create(d9);
                        Image.draggable(false);
                        Image.height(this.options.imageSize || IMAGE_DEFAULT);
                        Image.width((this.options.imageSize || IMAGE_DEFAULT));
                    }, Image);
                    this.observeComponentCreation2((b10, c10) => {
                        Text.create(e9);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({ top: 2 });
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((z9, a10) => {
                        Image.create({ "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_remove_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Image.draggable(false);
                        Image.fillColor({ "id": -1, "type": 10001, params: ["sys.color.ohos_id_color_secondary"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Image.width(ICON_SIZE);
                        Image.height(ICON_SIZE);
                        Image.position({
                            x: this.blockWidth - 40,
                            y: -MARGIN_EIGHT
                        });
                    }, Image);
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((s9, t9) => {
                        Row.create();
                        Row.borderRadius(50);
                        Row.padding({
                            left: TEXT_PADDING_LEFT_RIGHT,
                            right: TEXT_PADDING_LEFT_RIGHT,
                        });
                        Row.scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo });
                        Row.alignItems(VerticalAlign.Center);
                        Row.justifyContent(FlexAlign.Center);
                        Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Row.width(this.textItemEditWidth);
                        Row.height(28);
                    }, Row);
                    this.observeComponentCreation2((q9, r9) => {
                        Text.create(e9);
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.textAlign(TextAlign.Center);
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((o9, p9) => {
                        Image.create({ "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_remove_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Image.draggable(false);
                        Image.fillColor({ "id": -1, "type": 10001, params: ["sys.color.ohos_id_color_secondary"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Image.width(ICON_SIZE);
                        Image.height(ICON_SIZE);
                        Image.position({
                            x: this.blockWidth - 52,
                            y: -MARGIN_EIGHT
                        });
                    }, Image);
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }
    HeaderTitleBuilder(i8 = null) {
        this.observeComponentCreation2((b9, c9) => {
            __Common__.create();
            __Common__.visibility(!this.menuSwitch ? Visibility.Visible : Visibility.None);
        }, __Common__);
        {
            this.observeComponentCreation2((v8, w8) => {
                if (w8) {
                    let x8 = new ComposeTitleBar(this, {
                        title: this.options.normalTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        menuItems: this.menuItems,
                    }, undefined, v8, () => { }, { page: "librarys/gridobjectsortcomponent0805/src/main/ets/components/GridObjectSortComponent.ets", line: 723, col: 5 });
                    ViewPU.create(x8);
                    let y8 = () => {
                        return {
                            title: this.options.normalTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            menuItems: this.menuItems
                        };
                    };
                    x8.paramsGenerator_ = y8;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(v8, {});
                }
            }, { name: "ComposeTitleBar" });
        }
        __Common__.pop();
        this.observeComponentCreation2((s8, t8) => {
            __Common__.create();
            __Common__.visibility(this.menuSwitch ? Visibility.Visible : Visibility.None);
        }, __Common__);
        {
            this.observeComponentCreation2((m8, n8) => {
                if (n8) {
                    let o8 = new EditableTitleBar(this, {
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
                    }, undefined, m8, () => { }, { page: "librarys/gridobjectsortcomponent0805/src/main/ets/components/GridObjectSortComponent.ets", line: 728, col: 5 });
                    ViewPU.create(o8);
                    let p8 = () => {
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
                    o8.paramsGenerator_ = p8;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(m8, {});
                }
            }, { name: "EditableTitleBar" });
        }
        __Common__.pop();
    }
    ImageTextBuilder(e7, f7, g7 = null) {
        this.observeComponentCreation2((g8, h8) => {
            Column.create();
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((e8, f8) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Center);
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.height(this.imageItemWidth);
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.borderRadius((this.isTouchDown && e7.id === this.content.id) ||
                e7.id === this.hoverId ? this.touchBorderRadius : 0);
            Column.backgroundColor(this.isTouchDown && e7.id === this.content.id
                ? this.touchDown : e7.id === this.hoverId ? this.hoverBackgroundColor : '');
            Column.scale(e7.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
        }, Column);
        this.observeComponentCreation2((c8, d8) => {
            Image.create(e7.url);
            Image.draggable(false);
            Image.height(this.options.imageSize || IMAGE_DEFAULT);
            Image.width((this.options.imageSize || IMAGE_DEFAULT));
        }, Image);
        this.observeComponentCreation2((a8, b8) => {
            Text.create(e7.text);
            Text.textAlign(TextAlign.Center);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.margin({ top: 2 });
            Text.maxLines(TEXT_MAX_LINES);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((q7, r7) => {
            Image.create(this.imageTextAddIcon(e7));
            Image.draggable(false);
            Image.visibility(f7 === "add" ? this.imageTextAddIconVisible(e7) : Visibility.Hidden);
            Image.fillColor({ "id": -1, "type": 10001, params: ["sys.color.ohos_id_color_secondary"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(ICON_SIZE);
            Image.height(ICON_SIZE);
            Image.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            Image.onClick(() => {
                if (this.clickAddBtn || this.clickRemoveBtn) {
                    return;
                }
                this.scaleIcon = 0;
                this.content = e7;
                const t7 = this.unSelected.findIndex(z7 => z7.id === e7.id);
                this.editGridDataLength = this.selected.length + 1;
                const u7 = this.getEditItemGridPosition(ObservedObject.GetRawObject(this.selected), t7);
                this.unSelectedIndex = t7;
                this.arrayUnSelectIsChange = 1;
                this.clickAddBtn = true;
                this.calcGridHeight();
                Context.animateTo({
                    curve: REMOVE_ADD_SPRING,
                    onFinish: () => {
                        if (!this.selected.some(y7 => y7.id === e7.id)) {
                            this.arrayUnSelectIsChange = 2;
                            this.scaleIcon = 1;
                            this.selected.push(e7);
                            this.unSelected.splice(t7, 1);
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
                    this.addItemMoveX = u7.x;
                    this.addItemMoveY = u7.y;
                });
            });
        }, Image);
        this.observeComponentCreation2((n7, o7) => {
            Image.create(this.imageTextRemoveIcon(e7));
            Image.draggable(false);
            Image.fillColor({ "id": -1, "type": 10001, params: ["sys.color.ohos_id_color_secondary"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.visibility(f7 === "delete" && this.gridComState ? Visibility.Visible : Visibility.Hidden);
            Image.width(ICON_SIZE);
            Image.height(ICON_SIZE);
            Image.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            Image.onClick(() => this.handleDeleteClick(e7));
        }, Image);
        Column.pop();
        Column.pop();
    }
    TextBlockBuilder(j6, k6 = null) {
        this.observeComponentCreation2((c7, d7) => {
            Stack.create();
            Stack.scale(j6.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(28);
        }, Stack);
        this.observeComponentCreation2((a7, b7) => {
            Row.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
            } : { duration: 0 });
            Row.borderRadius(50);
            Row.width(this.clickRemoveBtn && j6.id === this.content.id ? this.textItemEditWidth + 8 : this.textItemEditWidth);
            Row.translate(this.gridComState ? this.clickRemoveBtn &&
                j6.id === this.content.id ? { x: 0 } : { x: -4 } : { x: 0 });
            Row.height('100%');
            Context.animation(null);
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((y6, z6) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
            } : { duration: 0 });
            Flex.borderRadius(50);
            Flex.padding({
                left: TEXT_PADDING_LEFT_RIGHT,
                right: TEXT_PADDING_LEFT_RIGHT,
            });
            Flex.backgroundColor(this.isTouchDown && j6.id === this.content.id ? this.touchDown
                : j6.id === this.hoverId ? this.hoverBackgroundColor
                    : '');
            Flex.width(this.clickRemoveBtn && j6.id === this.content.id ? this.textItemEditWidth + 8 : this.textItemEditWidth);
            Flex.translate(this.gridComState ? this.clickRemoveBtn && j6.id === this.content.id ? { x: 0 } : { x: -4 } : {
                x: 0
            });
            Flex.height('100%');
            Context.animation(null);
        }, Flex);
        this.observeComponentCreation2((w6, x6) => {
            Image.create({ "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_add"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Image.width(12);
            Image.height(12);
            Image.draggable(false);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.visibility(this.clickRemoveBtn && j6.id === this.content.id ? Visibility.Visible : Visibility.None);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0, } });
            Image.margin({ right: 4 });
            Context.animation(null);
        }, Image);
        this.observeComponentCreation2((u6, v6) => {
            Text.create(j6.text);
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((r6, s6) => {
            Image.create({ "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_remove_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER,
            });
            Image.draggable(false);
            Image.fillColor({ "id": -1, "type": 10001, params: ["sys.color.ohos_id_color_secondary"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(ICON_SIZE);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0, centerX: '50%' } });
            Image.scale(j6.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {});
            Image.visibility(this.gridComState ? 0 : 1);
            Image.position({
                x: this.blockWidth - 52,
                y: -MARGIN_EIGHT
            });
            Context.animation(null);
            Image.onClick(() => this.handleDeleteClick(j6));
        }, Image);
        Flex.pop();
        Stack.pop();
    }
    TextBlockAddItemBuilder(k5, l5 = null) {
        this.observeComponentCreation2((h6, i6) => {
            Stack.create();
            Stack.scale(k5.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(28);
        }, Stack);
        this.observeComponentCreation2((f6, g6) => {
            Row.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Row.borderRadius(50);
            Row.height('100%');
            Row.width(this.addIconShow && k5.id === this.content.id ? this.textItemEditWidth : '100%');
            Row.translate(this.addIconShow && k5.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((d6, e6) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Flex.borderRadius(50);
            Flex.padding({
                left: TEXT_PADDING_LEFT_RIGHT,
                right: TEXT_PADDING_LEFT_RIGHT,
            });
            Flex.backgroundColor(this.isTouchDown && k5.id === this.content.id ? this.touchDown
                : k5.id === this.hoverId ? this.hoverBackgroundColor : '');
            Flex.width(this.addIconShow && k5.id === this.content.id ? this.textItemEditWidth : '100%');
            Flex.translate(this.addIconShow && k5.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Flex.height('100%');
        }, Flex);
        this.observeComponentCreation2((b6, c6) => {
            Image.create({ "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_add"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Image.draggable(false);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(12);
            Image.height(12);
            Image.visibility(this.addIconShow && k5.id === this.content.id ? Visibility.None : Visibility.Visible);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            Image.margin({ right: 4 });
            Context.animation(null);
        }, Image);
        this.observeComponentCreation2((z5, a6) => {
            Text.create(k5.text);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Start);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((s5, t5) => {
            If.create();
            if (this.gridComState && this.addIconShow && k5.id === this.content.id) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x5, y5) => {
                        Image.create({ "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_remove_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Image.draggable(false);
                        Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
                        Image.fillColor({ "id": -1, "type": 10001, params: ["sys.color.ohos_id_color_secondary"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Image.width(ICON_SIZE);
                        Image.translate(this.gridComState ? { x: -MARGIN_EIGHT } : {});
                        Image.position({
                            x: this.blockWidth - 44,
                            y: -MARGIN_EIGHT
                        });
                    }, Image);
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
    AddTagBuilder(o3 = null) {
        this.observeComponentCreation2((i5, j5) => {
            Grid.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            Grid.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {});
            Context.animation(null);
            Grid.columnsTemplate(this.customColumns);
            Grid.padding({
                left: ROW_GAP,
                right: ROW_GAP,
            });
            Grid.clip(false);
            Grid.height(this.addGridHeight);
        }, Grid);
        this.observeComponentCreation2((r3, s3) => {
            ForEach.create();
            const t3 = (x3, y3) => {
                const z3 = x3;
                {
                    const a4 = (f5, g5) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.clickRemoveBtn ? DRAG_SPRING : y3 === this.unSelectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getAddAreaItemTranslate(y3));
                        Context.animation(null);
                    };
                    const b4 = () => {
                        this.observeComponentCreation2(a4, GridItem);
                        this.observeComponentCreation2((k4, l4) => {
                            Stack.create();
                            Stack.onHover((e5) => {
                                if (e5) {
                                    this.hoverId = z3.id;
                                }
                                else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.onTouch((u4) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (u4.type === TouchType.Down) {
                                    this.content = z3;
                                    this.isTouchDown = true;
                                }
                                if (u4.type === TouchType.Up) {
                                    this.isTouchDown = false;
                                    if (this.addAreaLongPressGesture || this.longScaleOnePointTwo === 1.05 || this.imageText) {
                                        return;
                                    }
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: COMMON_BEZIER
                                    }, () => {
                                        this.addIconShow = true;
                                    });
                                    if (this.options.type === GridObjectSortComponentType.TEXT) {
                                        this.scaleAddIcon = 1;
                                    }
                                    this.scaleIcon = 0;
                                    const v4 = this.unSelected.findIndex(d5 => d5.id === z3.id);
                                    this.editGridDataLength = this.selected.length + 1;
                                    const w4 = this.getEditItemGridPosition(ObservedObject.GetRawObject(this.selected), v4);
                                    this.content = z3;
                                    this.unSelectedIndex = v4;
                                    this.clickAddBtn = true;
                                    this.arrayUnSelectIsChange = 1;
                                    this.calcGridHeight();
                                    Context.animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
                                        if (!this.selected.some(c5 => c5.id === z3.id)) {
                                            this.scaleIcon = 1;
                                            this.scaleAddIcon = 0;
                                            this.selected.push(z3);
                                            this.unSelected.splice(v4, 1);
                                            this.calcGridHeight();
                                            this.arrayUnSelectIsChange = 2;
                                            this.addItemMoveX = 0;
                                            this.addItemMoveY = 0;
                                            if (!this.gridComState) {
                                                this.onSaveEdit();
                                            }
                                            Context.animateTo({
                                                duration: ENTER_EXIT_ICON_DURATION,
                                                curve: COMMON_BEZIER
                                            }, () => {
                                                this.addIconShow = false;
                                            });
                                            this.clickAddBtn = false;
                                        }
                                    } }, () => {
                                        this.addItemMoveX = w4.x;
                                        this.addItemMoveY = w4.y;
                                    });
                                }
                            });
                            Gesture.create(GesturePriority.Low);
                            LongPressGesture.create({ repeat: true });
                            LongPressGesture.onAction((r4) => {
                                if (!this.gridComState) {
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: COMMON_BEZIER,
                                    }, () => {
                                        this.addAreaLongPressGesture = true;
                                        this.gridComState = true;
                                    });
                                    this.menuSwitch = true;
                                }
                                else {
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: LONG_TOUCH_SCALE
                                    }, () => {
                                        this.longScaleOnePointTwo = 1.05;
                                    });
                                }
                                this.calcGridHeight();
                            });
                            LongPressGesture.onActionEnd(() => {
                                this.addAreaLongPressGesture = false;
                                Context.animateTo({
                                    duration: ENTER_EXIT_ICON_DURATION,
                                    curve: LONG_TOUCH_SCALE
                                }, () => {
                                    this.longScaleOnePointTwo = 1;
                                });
                            });
                            LongPressGesture.pop();
                            Gesture.pop();
                        }, Stack);
                        this.observeComponentCreation2((g4, h4) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(z3, "add");
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockAddItemBuilder.bind(this)(z3);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    b4();
                }
            };
            this.forEachUpdateFunction(r3, this.unSelected, t3, (w3) => w3.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
    }
    EditTagBuilder(m1 = null) {
        this.observeComponentCreation2((m3, n3) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((t2, u2) => {
            Grid.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            } : { duration: 0 });
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((i3) => {
                if (!this.gridComState) {
                    Context.animateTo({
                        duration: ENTER_EXIT_ICON_DURATION,
                        curve: COMMON_BEZIER
                    }, () => {
                        this.gridComState = true;
                    });
                    this.menuSwitch = true;
                }
                else {
                    Context.animateTo({
                        duration: ENTER_EXIT_ICON_DURATION,
                        curve: LONG_TOUCH_SCALE
                    }, () => {
                        this.longScaleOnePointTwo = 1.05;
                    });
                    if (i3.repeat && !this.vibrationDone) {
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
            LongPressGesture.pop();
            Gesture.pop();
            Grid.clip(false);
            Grid.editMode(this.gridComState);
            Grid.columnsTemplate(this.customColumns);
            Grid.padding({
                left: ROW_GAP,
                right: ROW_GAP
            });
            Grid.height(this.editGridHeight);
            Context.animation(null);
            Grid.onItemDragStart((g3, h3) => {
                this.itemIndex = h3;
                this.selectedIndex = -1;
                if (!this.gridComState) {
                    return;
                }
                this.isStartDrag = true;
                this.insertIndex = h3;
                this.dragContent = this.selected[h3];
                this.dragContentIndex = h3;
                return { builder: () => {
                    this.PixelMapBuilder.call(this, this.dragContent?.url, this.dragContent?.text);
                } };
            });
            Grid.onItemDrop((c3, d3, e3, f3) => {
                this.insertItem(d3, e3);
            });
            Grid.onItemDragMove((z2, a3, b3) => this.onDragMoveEvent(z2, a3, b3));
        }, Grid);
        this.observeComponentCreation2((q1, r1) => {
            ForEach.create();
            const s1 = (w1, x1) => {
                const y1 = w1;
                {
                    const z1 = (q2, r2) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.isStartDrag ? DRAG_SPRING : x1 === this.selectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING,
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getShowAreaItemTranslate(x1));
                        Context.animation(null);
                        GridItem.visibility(y1.visibility);
                    };
                    const a2 = () => {
                        this.observeComponentCreation2(z1, GridItem);
                        this.observeComponentCreation2((j2, k2) => {
                            Stack.create();
                            Stack.onHover((p2) => {
                                if (p2) {
                                    this.hoverId = y1.id;
                                }
                                else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.clip(false);
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : this.gridComState ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.onTouch((n2) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (n2.type === TouchType.Down) {
                                    this.content = y1;
                                    this.isTouchDown = true;
                                }
                                if (n2.type === TouchType.Up) {
                                    this.isTouchDown = false;
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: LONG_TOUCH_SCALE
                                    }, () => {
                                        this.longScaleOnePointTwo = 1;
                                    });
                                }
                            });
                        }, Stack);
                        this.observeComponentCreation2((f2, g2) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(y1, 'delete');
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockBuilder.bind(this)(y1);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    a2();
                }
            };
            this.forEachUpdateFunction(q1, this.selected, s1, (v1) => v1.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
        Column.pop();
    }
    insertItem(j1, k1) {
        if (!this.gridComState) {
            return;
        }
        this.vibrationDone = false;
        Context.animateTo({
            duration: ENTER_EXIT_ICON_DURATION,
            curve: LONG_TOUCH_SCALE
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
        this.isStartDrag = false;
        if (k1 !== -1) {
            this.selected.splice(j1, 1);
            this.selected.splice(k1, 0, this.dragContent);
        }
        this.dragContent.visibility = Visibility.Visible;
        this.calcGridHeight();
    }
    calcAreaInfo() {
        this.calcColNum();
        this.blockWidth = this.getBlockWidth();
        this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
        this.imageItemWidth = this.blockWidth - 16;
        this.blockHeight = this.imageText ? this.imageItemWidth + 16 : this.gridComState ? 44 : BLOCK_TEXT_HEIGHT;
        this.calcGridHeight();
    }
    initialRender() {
        this.observeComponentCreation2((h1, i1) => {
            Column.create();
            Column.width('100%');
            Column.height('90%');
        }, Column);
        this.HeaderTitleBuilder.bind(this)();
        this.observeComponentCreation2((f1, g1) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((a1, b1) => {
            Column.create();
            Column.onAreaChange((d1, e1) => {
                this.areaWidth = Number(e1.width);
                this.calcAreaInfo();
            });
            Column.width("100%");
        }, Column);
        this.observeComponentCreation2((y, z) => {
            __Common__.create();
            __Common__.margin({ bottom: MARGIN_EIGHT });
        }, __Common__);
        {
            this.observeComponentCreation2((s, t) => {
                if (t) {
                    let u = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, s, () => { }, { page: "librarys/gridobjectsortcomponent0805/src/main/ets/components/GridObjectSortComponent.ets", line: 1288, col: 11 });
                    ViewPU.create(u);
                    let v = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.showAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    u.paramsGenerator_ = v;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(s, {
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
        this.observeComponentCreation2((m, n) => {
            __Common__.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            __Common__.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {});
            Context.animation(null);
            __Common__.margin({ bottom: MARGIN_EIGHT });
            __Common__.onAreaChange((p, q) => {
                this.subTitleHeight = Number(q.height);
            });
        }, __Common__);
        {
            this.observeComponentCreation2((g, h) => {
                if (h) {
                    let i = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, g, () => { }, { page: "librarys/gridobjectsortcomponent0805/src/main/ets/components/GridObjectSortComponent.ets", line: 1297, col: 11 });
                    ViewPU.create(i);
                    let j = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.addAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    i.paramsGenerator_ = j;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(g, {
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