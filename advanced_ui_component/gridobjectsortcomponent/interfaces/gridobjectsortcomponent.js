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

const vibrator = requireNativeModule('ohos.vibrator');
const curves = requireNativeModule('ohos.curves');
const composetitlebar = requireNapi('arkui.advanced.ComposeTitleBar');
const editabletitlebar = requireNapi('arkui.advanced.EditableTitleBar');
const subheader = requireNapi('arkui.advanced.SubHeader');

const ComposeTitleBar = composetitlebar.ComposeTitleBar;
const EditableTitleBar = editabletitlebar.EditableTitleBar;
const EditableLeftIconType = editabletitlebar.EditableLeftIconType;
const SubHeader = subheader.SubHeader;
const OperationType = subheader.OperationType;

const COL_IMAGE_TEXT = 3;
const COL_TEXT = 4;
const BLOCK_TEXT_HEIGHT = 36;
const ICON_SIZE = 24;
const IMAGE_DEFAULT = 56;
const TEXT_PADDING_LEFT_RIGHT = 12;
const MARGIN_EIGHT = 8;
const ROW_GAP = 16;
const SUBTITLE_HEIGHT = 56;
const ENTER_EXIT_ICON_DURATION = 200;
const COMMON_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1);
const DRAG_SPRING = curves.interpolatingSpring(0, 1, 400, 38);
const REMOVE_ADD_SPRING = curves.interpolatingSpring(0, 1, 150, 24);
const LONG_TOUCH_SCALE = curves.cubicBezierCurve(0.2, 0, 0.2, 1);
export var GridObjectSortComponentType;
(function (x15) {
    x15["IMAGE_TEXT"] = "image_text";
    x15["TEXT"] = "text";
})(GridObjectSortComponentType || (GridObjectSortComponentType = {}));
class MenuItem {
    constructor(u15, v15, w15) {
        this.value = u15;
        this.isEnabled = v15;
        this.action = w15;
    }
}
export class GridObjectSortComponent extends ViewPU {
    constructor(n15, o15, p15, q15 = -1, r15 = undefined, s15) {
        super(n15, p15, q15, s15);
        if (typeof r15 === "function") {
            this.paramsGenerator_ = r15;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(o15.options, this, "options");
        this.dataList = [];
        this.__selected = new ObservedPropertyObjectPU([], this, "selected");
        this.__unSelected = new ObservedPropertyObjectPU([], this, "unSelected");
        this.__copySelected = new ObservedPropertyObjectPU([], this, "copySelected");
        this.__copyUnSelected = new ObservedPropertyObjectPU([], this, "copyUnSelected");
        this.__content = new ObservedPropertyObjectPU({ id: '', text: '', selected: false, order: 0 }, this, "content");
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
        this.setInitiallyProvidedValue(o15);
        this.declareWatch("gridComState", this.onGridComStateChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(m15) {
        if (m15.options === undefined) {
            this.__options.set({});
        }
        if (m15.dataList !== undefined) {
            this.dataList = m15.dataList;
        }
        if (m15.selected !== undefined) {
            this.selected = m15.selected;
        }
        if (m15.unSelected !== undefined) {
            this.unSelected = m15.unSelected;
        }
        if (m15.copySelected !== undefined) {
            this.copySelected = m15.copySelected;
        }
        if (m15.copyUnSelected !== undefined) {
            this.copyUnSelected = m15.copyUnSelected;
        }
        if (m15.content !== undefined) {
            this.content = m15.content;
        }
        if (m15.hoverId !== undefined) {
            this.hoverId = m15.hoverId;
        }
        if (m15.gridComState !== undefined) {
            this.gridComState = m15.gridComState;
        }
        if (m15.menuSwitch !== undefined) {
            this.menuSwitch = m15.menuSwitch;
        }
        if (m15.areaWidth !== undefined) {
            this.areaWidth = m15.areaWidth;
        }
        if (m15.blockWidth !== undefined) {
            this.blockWidth = m15.blockWidth;
        }
        if (m15.blockHeight !== undefined) {
            this.blockHeight = m15.blockHeight;
        }
        if (m15.longScaleOnePointTwo !== undefined) {
            this.longScaleOnePointTwo = m15.longScaleOnePointTwo;
        }
        if (m15.scaleGridItemNinetyPercent !== undefined) {
            this.scaleGridItemNinetyPercent = m15.scaleGridItemNinetyPercent;
        }
        if (m15.reboundSize !== undefined) {
            this.reboundSize = m15.reboundSize;
        }
        if (m15.scaleIcon !== undefined) {
            this.scaleIcon = m15.scaleIcon;
        }
        if (m15.addIconShow !== undefined) {
            this.addIconShow = m15.addIconShow;
        }
        if (m15.scaleAddIcon !== undefined) {
            this.scaleAddIcon = m15.scaleAddIcon;
        }
        if (m15.isStartDrag !== undefined) {
            this.isStartDrag = m15.isStartDrag;
        }
        if (m15.insertIndex !== undefined) {
            this.insertIndex = m15.insertIndex;
        }
        if (m15.editGridDataLength !== undefined) {
            this.editGridDataLength = m15.editGridDataLength;
        }
        if (m15.isTouchDown !== undefined) {
            this.isTouchDown = m15.isTouchDown;
        }
        if (m15.addItemMoveX !== undefined) {
            this.addItemMoveX = m15.addItemMoveX;
        }
        if (m15.addItemMoveY !== undefined) {
            this.addItemMoveY = m15.addItemMoveY;
        }
        if (m15.editItemMoveX !== undefined) {
            this.editItemMoveX = m15.editItemMoveX;
        }
        if (m15.editItemMoveY !== undefined) {
            this.editItemMoveY = m15.editItemMoveY;
        }
        if (m15.unSelectedIndex !== undefined) {
            this.unSelectedIndex = m15.unSelectedIndex;
        }
        if (m15.clickAddBtn !== undefined) {
            this.clickAddBtn = m15.clickAddBtn;
        }
        if (m15.selectedIndex !== undefined) {
            this.selectedIndex = m15.selectedIndex;
        }
        if (m15.clickRemoveBtn !== undefined) {
            this.clickRemoveBtn = m15.clickRemoveBtn;
        }
        if (m15.addAreaLongPressGesture !== undefined) {
            this.addAreaLongPressGesture = m15.addAreaLongPressGesture;
        }
        if (m15.arraySelectIsChange !== undefined) {
            this.arraySelectIsChange = m15.arraySelectIsChange;
        }
        if (m15.arrayUnSelectIsChange !== undefined) {
            this.arrayUnSelectIsChange = m15.arrayUnSelectIsChange;
        }
        if (m15.textItemEditWidth !== undefined) {
            this.textItemEditWidth = m15.textItemEditWidth;
        }
        if (m15.imageItemWidth !== undefined) {
            this.imageItemWidth = m15.imageItemWidth;
        }
        if (m15.saveClick !== undefined) {
            this.saveClick = m15.saveClick;
        }
        if (m15.imageTextAddIconShow !== undefined) {
            this.imageTextAddIconShow = m15.imageTextAddIconShow;
        }
        if (m15.imageTextRemoveIconShow !== undefined) {
            this.imageTextRemoveIconShow = m15.imageTextRemoveIconShow;
        }
        if (m15.firstIn !== undefined) {
            this.firstIn = m15.firstIn;
        }
        if (m15.colNum !== undefined) {
            this.colNum = m15.colNum;
        }
        if (m15.vibrationDone !== undefined) {
            this.vibrationDone = m15.vibrationDone;
        }
        if (m15.touchDown !== undefined) {
            this.touchDown = m15.touchDown;
        }
        if (m15.touchBorderRadius !== undefined) {
            this.touchBorderRadius = m15.touchBorderRadius;
        }
        if (m15.hoverBackgroundColor !== undefined) {
            this.hoverBackgroundColor = m15.hoverBackgroundColor;
        }
        if (m15.focusBorder !== undefined) {
            this.focusBorder = m15.focusBorder;
        }
        if (m15.imageText !== undefined) {
            this.imageText = m15.imageText;
        }
        if (m15.menuItems !== undefined) {
            this.menuItems = m15.menuItems;
        }
        if (m15.onSave !== undefined) {
            this.onSave = m15.onSave;
        }
        if (m15.onCancel !== undefined) {
            this.onCancel = m15.onCancel;
        }
    }
    updateStateVars(l15) {
        this.__options.reset(l15.options);
    }
    purgeVariableDependenciesOnElmtId(k15) {
        this.__options.purgeDependencyOnElmtId(k15);
        this.__selected.purgeDependencyOnElmtId(k15);
        this.__unSelected.purgeDependencyOnElmtId(k15);
        this.__copySelected.purgeDependencyOnElmtId(k15);
        this.__copyUnSelected.purgeDependencyOnElmtId(k15);
        this.__content.purgeDependencyOnElmtId(k15);
        this.__hoverId.purgeDependencyOnElmtId(k15);
        this.__gridComState.purgeDependencyOnElmtId(k15);
        this.__menuSwitch.purgeDependencyOnElmtId(k15);
        this.__areaWidth.purgeDependencyOnElmtId(k15);
        this.__blockWidth.purgeDependencyOnElmtId(k15);
        this.__blockHeight.purgeDependencyOnElmtId(k15);
        this.__longScaleOnePointTwo.purgeDependencyOnElmtId(k15);
        this.__scaleGridItemNinetyPercent.purgeDependencyOnElmtId(k15);
        this.__reboundSize.purgeDependencyOnElmtId(k15);
        this.__scaleIcon.purgeDependencyOnElmtId(k15);
        this.__addIconShow.purgeDependencyOnElmtId(k15);
        this.__scaleAddIcon.purgeDependencyOnElmtId(k15);
        this.__isStartDrag.purgeDependencyOnElmtId(k15);
        this.__insertIndex.purgeDependencyOnElmtId(k15);
        this.__editGridDataLength.purgeDependencyOnElmtId(k15);
        this.__isTouchDown.purgeDependencyOnElmtId(k15);
        this.__addItemMoveX.purgeDependencyOnElmtId(k15);
        this.__addItemMoveY.purgeDependencyOnElmtId(k15);
        this.__editItemMoveX.purgeDependencyOnElmtId(k15);
        this.__editItemMoveY.purgeDependencyOnElmtId(k15);
        this.__unSelectedIndex.purgeDependencyOnElmtId(k15);
        this.__clickAddBtn.purgeDependencyOnElmtId(k15);
        this.__selectedIndex.purgeDependencyOnElmtId(k15);
        this.__clickRemoveBtn.purgeDependencyOnElmtId(k15);
        this.__addAreaLongPressGesture.purgeDependencyOnElmtId(k15);
        this.__arraySelectIsChange.purgeDependencyOnElmtId(k15);
        this.__arrayUnSelectIsChange.purgeDependencyOnElmtId(k15);
        this.__textItemEditWidth.purgeDependencyOnElmtId(k15);
        this.__imageItemWidth.purgeDependencyOnElmtId(k15);
        this.__saveClick.purgeDependencyOnElmtId(k15);
        this.__imageTextAddIconShow.purgeDependencyOnElmtId(k15);
        this.__imageTextRemoveIconShow.purgeDependencyOnElmtId(k15);
        this.__firstIn.purgeDependencyOnElmtId(k15);
    }
    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__selected.aboutToBeDeleted();
        this.__unSelected.aboutToBeDeleted();
        this.__copySelected.aboutToBeDeleted();
        this.__copyUnSelected.aboutToBeDeleted();
        this.__content.aboutToBeDeleted();
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get options() {
        return this.__options.get();
    }
    set options(j15) {
        this.__options.set(j15);
    }
    get selected() {
        return this.__selected.get();
    }
    set selected(i15) {
        this.__selected.set(i15);
    }
    get unSelected() {
        return this.__unSelected.get();
    }
    set unSelected(h15) {
        this.__unSelected.set(h15);
    }
    get copySelected() {
        return this.__copySelected.get();
    }
    set copySelected(g15) {
        this.__copySelected.set(g15);
    }
    get copyUnSelected() {
        return this.__copyUnSelected.get();
    }
    set copyUnSelected(f15) {
        this.__copyUnSelected.set(f15);
    }
    get content() {
        return this.__content.get();
    }
    set content(e15) {
        this.__content.set(e15);
    }
    get hoverId() {
        return this.__hoverId.get();
    }
    set hoverId(d15) {
        this.__hoverId.set(d15);
    }
    get gridComState() {
        return this.__gridComState.get();
    }
    set gridComState(c15) {
        this.__gridComState.set(c15);
    }
    get menuSwitch() {
        return this.__menuSwitch.get();
    }
    set menuSwitch(b15) {
        this.__menuSwitch.set(b15);
    }
    get areaWidth() {
        return this.__areaWidth.get();
    }
    set areaWidth(a15) {
        this.__areaWidth.set(a15);
    }
    get blockWidth() {
        return this.__blockWidth.get();
    }
    set blockWidth(z14) {
        this.__blockWidth.set(z14);
    }
    get blockHeight() {
        return this.__blockHeight.get();
    }
    set blockHeight(y14) {
        this.__blockHeight.set(y14);
    }
    get longScaleOnePointTwo() {
        return this.__longScaleOnePointTwo.get();
    }
    set longScaleOnePointTwo(x14) {
        this.__longScaleOnePointTwo.set(x14);
    }
    get scaleGridItemNinetyPercent() {
        return this.__scaleGridItemNinetyPercent.get();
    }
    set scaleGridItemNinetyPercent(w14) {
        this.__scaleGridItemNinetyPercent.set(w14);
    }
    get reboundSize() {
        return this.__reboundSize.get();
    }
    set reboundSize(v14) {
        this.__reboundSize.set(v14);
    }
    get scaleIcon() {
        return this.__scaleIcon.get();
    }
    set scaleIcon(u14) {
        this.__scaleIcon.set(u14);
    }
    get addIconShow() {
        return this.__addIconShow.get();
    }
    set addIconShow(t14) {
        this.__addIconShow.set(t14);
    }
    get scaleAddIcon() {
        return this.__scaleAddIcon.get();
    }
    set scaleAddIcon(s14) {
        this.__scaleAddIcon.set(s14);
    }
    get isStartDrag() {
        return this.__isStartDrag.get();
    }
    set isStartDrag(r14) {
        this.__isStartDrag.set(r14);
    }
    get insertIndex() {
        return this.__insertIndex.get();
    }
    set insertIndex(q14) {
        this.__insertIndex.set(q14);
    }
    get editGridDataLength() {
        return this.__editGridDataLength.get();
    }
    set editGridDataLength(p14) {
        this.__editGridDataLength.set(p14);
    }
    get isTouchDown() {
        return this.__isTouchDown.get();
    }
    set isTouchDown(o14) {
        this.__isTouchDown.set(o14);
    }
    get addItemMoveX() {
        return this.__addItemMoveX.get();
    }
    set addItemMoveX(n14) {
        this.__addItemMoveX.set(n14);
    }
    get addItemMoveY() {
        return this.__addItemMoveY.get();
    }
    set addItemMoveY(m14) {
        this.__addItemMoveY.set(m14);
    }
    get editItemMoveX() {
        return this.__editItemMoveX.get();
    }
    set editItemMoveX(l14) {
        this.__editItemMoveX.set(l14);
    }
    get editItemMoveY() {
        return this.__editItemMoveY.get();
    }
    set editItemMoveY(k14) {
        this.__editItemMoveY.set(k14);
    }
    get unSelectedIndex() {
        return this.__unSelectedIndex.get();
    }
    set unSelectedIndex(j14) {
        this.__unSelectedIndex.set(j14);
    }
    get clickAddBtn() {
        return this.__clickAddBtn.get();
    }
    set clickAddBtn(i14) {
        this.__clickAddBtn.set(i14);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(h14) {
        this.__selectedIndex.set(h14);
    }
    get clickRemoveBtn() {
        return this.__clickRemoveBtn.get();
    }
    set clickRemoveBtn(g14) {
        this.__clickRemoveBtn.set(g14);
    }
    get addAreaLongPressGesture() {
        return this.__addAreaLongPressGesture.get();
    }
    set addAreaLongPressGesture(f14) {
        this.__addAreaLongPressGesture.set(f14);
    }
    get arraySelectIsChange() {
        return this.__arraySelectIsChange.get();
    }
    set arraySelectIsChange(e14) {
        this.__arraySelectIsChange.set(e14);
    }
    get arrayUnSelectIsChange() {
        return this.__arrayUnSelectIsChange.get();
    }
    set arrayUnSelectIsChange(d14) {
        this.__arrayUnSelectIsChange.set(d14);
    }
    get textItemEditWidth() {
        return this.__textItemEditWidth.get();
    }
    set textItemEditWidth(c14) {
        this.__textItemEditWidth.set(c14);
    }
    get imageItemWidth() {
        return this.__imageItemWidth.get();
    }
    set imageItemWidth(b14) {
        this.__imageItemWidth.set(b14);
    }
    get saveClick() {
        return this.__saveClick.get();
    }
    set saveClick(a14) {
        this.__saveClick.set(a14);
    }
    get imageTextAddIconShow() {
        return this.__imageTextAddIconShow.get();
    }
    set imageTextAddIconShow(z13) {
        this.__imageTextAddIconShow.set(z13);
    }
    get imageTextRemoveIconShow() {
        return this.__imageTextRemoveIconShow.get();
    }
    set imageTextRemoveIconShow(y13) {
        this.__imageTextRemoveIconShow.set(y13);
    }
    get firstIn() {
        return this.__firstIn.get();
    }
    set firstIn(x13) {
        this.__firstIn.set(x13);
    }
    aboutToAppear() {
        this.dataList.length = 50;
        this.selected = this.dataList && this.deduplicate(this.dataList).filter(w13 => w13.selected).sort(this.sortBy());
        this.unSelected = this.dataList && this.deduplicate(this.dataList).filter(v13 => !v13.selected).sort(this.sortBy());
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
        this.colNum = this.imageText ? COL_IMAGE_TEXT : COL_TEXT;
        setTimeout(() => {
            this.firstIn = false;
        }, 500);
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
    }
    deduplicate(l13) {
        const m13 = [];
        l13.forEach(o13 => {
            if (!m13.some(q13 => q13.id === o13.id)) {
                m13.push(o13);
            }
        });
        return m13;
    }
    onGridComStateChange() {
        this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
        if (!this.imageText) {
            this.blockHeight = this.gridComState ? 44 : BLOCK_TEXT_HEIGHT;
        }
    }
    sortBy() {
        return (j13, k13) => {
            return j13.order - k13.order;
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
            const d13 = this.getNewData(this.selected, true, 0);
            const e13 = this.getNewData(this.unSelected, false, this.selected.length);
            this.selected = d13;
            this.unSelected = e13;
            this.onSave && this.onSave(d13, e13);
        });
        setTimeout(() => {
            this.saveClick = false;
        }, ENTER_EXIT_ICON_DURATION);
        this.menuSwitch = false;
    }
    onDragMoveEvent(w12, x12, y12) {
        if (!this.gridComState || (w12.x < this.blockWidth / 3 && w12.y < this.blockHeight / 3)) {
            return;
        }
        let z12 = y12;
        if (z12 < 0) {
            z12 = this.selected.length - 1;
        }
        this.insertIndex = y12;
    }
    handleDeleteClick(r12) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.clickRemoveBtn = true;
        this.scaleIcon = 0;
        this.arraySelectIsChange = 1;
        let s12 = this.selected.findIndex(v12 => v12.id === r12.id);
        this.content = r12;
        this.selectedIndex = s12;
        Context.animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
            this.scaleIcon = 1;
            this.selected.splice(s12, 1);
            this.unSelected.unshift(r12);
            this.editGridDataLength = this.editGridDataLength - 1;
            this.editItemMoveX = 0;
            this.editItemMoveY = 0;
            this.arraySelectIsChange = 2;
            this.clickRemoveBtn = false;
        } }, () => {
            this.editItemMoveX = this.getAddItemGridPosition().x;
            this.editItemMoveY = this.getAddItemGridPosition().y;
        });
    }
    customColumnsTemplate() {
        let q12 = '1fr 1fr 1fr 1fr';
        if (this.imageText) {
            q12 = '1fr 1fr 1fr';
        }
        return q12;
    }
    getNewData(k12, l12, m12) {
        return k12.map((o12, p12) => {
            o12.selected = l12;
            o12.order = m12 + p12;
            return o12;
        });
    }
    getBlockWidth() {
        const j12 = (this.areaWidth - 32) / this.colNum;
        return j12;
    }
    getGridHeight(c12, d12) {
        let e12 = 0;
        let f12 = c12.length;
        let g12 = 0;
        let h12 = f12 % this.colNum === 0;
        if (this.clickAddBtn && h12) {
            g12 = 1;
        }
        else if (this.isStartDrag && h12 && d12) {
            g12 = 1;
        }
        else if (this.clickRemoveBtn && h12 && !d12) {
            g12 = 1;
        }
        else {
            g12 = 0;
        }
        let i12 = Math.ceil(f12 / this.colNum) + g12;
        e12 = this.blockHeight * i12;
        if (f12 === 0) {
            e12 = 0;
        }
        return e12;
    }
    imageTextRemoveIcon(z11) {
        const a12 = this.clickRemoveBtn && this.content.id === z11.id;
        const b12 = a12 ? { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_add_norm_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_remove_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        return b12;
    }
    imageTextAddIcon(w11) {
        const x11 = this.clickAddBtn && this.content.id === w11.id && this.gridComState;
        const y11 = x11 ? { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_remove_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_add_norm_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        return y11;
    }
    imageTextAddIconVisible(t11) {
        const u11 = this.clickAddBtn && this.content.id === t11.id && !this.gridComState;
        const v11 = u11 ? Visibility.Hidden : Visibility.Visible;
        return v11;
    }
    getCoodXY(o11) {
        let p11 = 0;
        let q11 = 0;
        const r11 = this.colNum;
        const s11 = Math.trunc(o11 % r11);
        if (o11 >= this.insertIndex) {
            if (s11 === r11 - 1) {
                p11 = p11 - this.blockWidth * (r11 - 1);
                q11 = q11 + this.blockHeight;
            }
            else {
                p11 = p11 + this.blockWidth;
            }
        }
        if (!this.isStartDrag) {
            p11 = 0;
            q11 = 0;
        }
        return { x: p11, y: q11 };
    }
    getAddItemGridPosition() {
        const c11 = this.selected.length;
        const d11 = this.colNum;
        const e11 = (this.selectedIndex + 1) % d11;
        const f11 = Math.ceil((this.selectedIndex + 1) / d11);
        const g11 = Math.ceil(c11 / d11);
        const h11 = this.imageText;
        let i11 = 0;
        if (e11 === 0) {
            i11 = h11 ? -this.blockWidth * 2 : -this.blockWidth * 3;
        }
        else {
            i11 = -this.blockWidth * (e11 - 1);
        }
        const j11 = SUBTITLE_HEIGHT;
        let k11 = 0;
        const l11 = g11 - f11;
        const m11 = c11 % d11;
        const n11 = m11 === 1 ? l11 : l11 + 1;
        k11 = n11 * this.blockHeight + j11;
        return {
            x: i11,
            y: k11
        };
    }
    getCoveringGridPosition(z10) {
        let a11 = 0;
        let b11 = 0;
        if (z10 > this.selectedIndex && this.arraySelectIsChange !== 2) {
            a11 = z10 % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            b11 = z10 % this.colNum === 0 ? -this.blockHeight : 0;
        }
        return {
            x: a11,
            y: b11
        };
    }
    getEditItemGridPosition(n10, o10) {
        const p10 = n10.length;
        const q10 = this.colNum;
        const r10 = Math.trunc(p10 % q10);
        const s10 = Math.trunc(o10 % q10);
        let t10 = Math.abs(r10 - s10) * this.blockWidth;
        if (r10 < s10) {
            t10 = -t10;
        }
        else if (r10 > s10) {
            t10 = t10;
        }
        else {
            t10 = 0;
        }
        let u10 = 0;
        let v10 = 0;
        let w10 = Math.trunc(o10 / this.colNum);
        const x10 = SUBTITLE_HEIGHT;
        const y10 = !this.imageText && this.gridComState && o10 > 3;
        if (y10) {
            v10 = (w10 + 1) * (this.blockHeight - 8) + 8;
        }
        else {
            v10 = (w10 + 1) * this.blockHeight;
        }
        u10 = v10 + x10;
        return {
            x: t10,
            y: u10
        };
    }
    getCoveringGridPositionBottom(i10) {
        let j10 = 0;
        let k10 = 0;
        const l10 = i10 % this.colNum === 0;
        const m10 = this.gridComState && !this.imageText ? -this.blockHeight + 8 : -this.blockHeight;
        if (i10 > this.unSelectedIndex && this.arrayUnSelectIsChange !== 2) {
            j10 = l10 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            k10 = l10 ? m10 : 0;
        }
        return {
            x: j10,
            y: k10
        };
    }
    getAddItemRightMove(e10) {
        let f10 = this.blockWidth;
        let g10 = 0;
        let h10 = (e10 + 1) % this.colNum === 0;
        if (h10) {
            f10 = -this.blockWidth * (this.colNum - 1);
            g10 = this.imageText ? this.blockHeight : this.blockHeight - 8;
        }
        return { x: f10, y: g10 };
    }
    getShowAreaItemTranslate(d10) {
        if (this.isStartDrag) {
            return {
                x: this.getCoodXY(d10).x,
                y: this.getCoodXY(d10).y
            };
        }
        if (!this.isStartDrag && d10 === this.selectedIndex) {
            return {
                x: this.editItemMoveX,
                y: this.editItemMoveY
            };
        }
        if (!this.isStartDrag && d10 !== this.selectedIndex && this.clickRemoveBtn) {
            return {
                x: this.getCoveringGridPosition(d10).x,
                y: this.getCoveringGridPosition(d10).y
            };
        }
        return { x: 0, y: 0 };
    }
    getAddAreaItemTranslate(c10) {
        if (this.clickRemoveBtn) {
            return {
                x: this.getAddItemRightMove(c10).x,
                y: this.getAddItemRightMove(c10).y
            };
        }
        if (!this.clickRemoveBtn && c10 === this.unSelectedIndex) {
            return {
                x: this.addItemMoveX,
                y: -this.addItemMoveY
            };
        }
        if (!this.clickRemoveBtn && c10 !== this.unSelectedIndex && this.clickAddBtn) {
            return {
                x: this.getCoveringGridPositionBottom(c10).x,
                y: this.getCoveringGridPositionBottom(c10).y
            };
        }
        return { x: 0, y: 0 };
    }
    PixelMapBuilder(y8 = null) {
        this.observeComponentCreation2((a10, b10) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.clip(false);
            Stack.height(this.blockHeight * 1.5);
            Stack.width(this.blockWidth * 1.2);
        }, Stack);
        this.observeComponentCreation2((b9, c9) => {
            If.create();
            if (this.imageText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y9, z9) => {
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
                    this.observeComponentCreation2((w9, x9) => {
                        Image.create(this.content.url);
                        Image.draggable(false);
                        Image.height(this.options.imageSize || IMAGE_DEFAULT);
                        Image.width((this.options.imageSize || IMAGE_DEFAULT));
                    }, Image);
                    this.observeComponentCreation2((u9, v9) => {
                        Text.create(this.content.text);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({ top: 2 });
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.textAlign(TextAlign.Center);
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((s9, t9) => {
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
                    this.observeComponentCreation2((l9, m9) => {
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
                    this.observeComponentCreation2((j9, k9) => {
                        Text.create(this.content.text);
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.textAlign(TextAlign.Center);
                        Text.maxLines(1);
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((h9, i9) => {
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
    HeaderTitleBuilder(d8 = null) {
        this.observeComponentCreation2((w8, x8) => {
            __Common__.create();
            __Common__.visibility(!this.menuSwitch ? Visibility.Visible : Visibility.None);
        }, __Common__);
        {
            this.observeComponentCreation2((q8, r8) => {
                if (r8) {
                    let s8 = new ComposeTitleBar(typeof PUV2ViewBase !== "undefined" && d8 instanceof PUV2ViewBase ? d8 : this, {
                        title: this.options.normalTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        menuItems: this.menuItems,
                    }, undefined, q8, () => { }, { page: "library/src/main/ets/components/mainpage/GridObjectSortComponent.ets", line: 625, col: 5 });
                    ViewPU.create(s8);
                    let t8 = () => {
                        return {
                            title: this.options.normalTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            menuItems: this.menuItems
                        };
                    };
                    s8.paramsGenerator_ = t8;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(q8, {});
                }
            }, { name: "ComposeTitleBar" });
        }
        __Common__.pop();
        this.observeComponentCreation2((n8, o8) => {
            __Common__.create();
            __Common__.visibility(this.menuSwitch ? Visibility.Visible : Visibility.None);
        }, __Common__);
        {
            this.observeComponentCreation2((h8, i8) => {
                if (i8) {
                    let j8 = new EditableTitleBar(typeof PUV2ViewBase !== "undefined" && d8 instanceof PUV2ViewBase ? d8 : this, {
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
                    }, undefined, h8, () => { }, { page: "library/src/main/ets/components/mainpage/GridObjectSortComponent.ets", line: 630, col: 5 });
                    ViewPU.create(j8);
                    let k8 = () => {
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
                    j8.paramsGenerator_ = k8;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(h8, {});
                }
            }, { name: "EditableTitleBar" });
        }
        __Common__.pop();
    }
    ImageTextBuilder(z6, a7, b7 = null) {
        this.observeComponentCreation2((b8, c8) => {
            Column.create();
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((z7, a8) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Center);
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.height(this.imageItemWidth);
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.borderRadius((this.isTouchDown && z6.id === this.content.id) ||
                z6.id === this.hoverId ? this.touchBorderRadius : 0);
            Column.backgroundColor(this.isTouchDown && z6.id === this.content.id
                ? this.touchDown : z6.id === this.hoverId ? this.hoverBackgroundColor : '');
            Column.scale(z6.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
        }, Column);
        this.observeComponentCreation2((x7, y7) => {
            Image.create(z6.url);
            Image.draggable(false);
            Image.height(this.options.imageSize || IMAGE_DEFAULT);
            Image.width((this.options.imageSize || IMAGE_DEFAULT));
        }, Image);
        this.observeComponentCreation2((v7, w7) => {
            Text.create(z6.text);
            Text.textAlign(TextAlign.Center);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.margin({ top: 2 });
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((l7, m7) => {
            Image.create(this.imageTextAddIcon(z6));
            Image.draggable(false);
            Image.visibility(a7 === "add" ? this.imageTextAddIconVisible(z6) : Visibility.Hidden);
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
                this.content = z6;
                const o7 = this.unSelected.findIndex(u7 => u7.id === z6.id);
                this.editGridDataLength = this.selected.length + 1;
                const p7 = this.getEditItemGridPosition(ObservedObject.GetRawObject(this.selected), o7);
                this.unSelectedIndex = o7;
                this.arrayUnSelectIsChange = 1;
                this.clickAddBtn = true;
                Context.animateTo({
                    curve: REMOVE_ADD_SPRING,
                    onFinish: () => {
                        if (!this.selected.some(t7 => t7.id === z6.id)) {
                            this.arrayUnSelectIsChange = 2;
                            this.scaleIcon = 1;
                            this.selected.push(z6);
                            this.unSelected.splice(o7, 1);
                            this.addItemMoveX = 0;
                            this.addItemMoveY = 0;
                            if (!this.gridComState) {
                                this.onSaveEdit();
                            }
                            this.clickAddBtn = false;
                        }
                    }
                }, () => {
                    this.addItemMoveX = p7.x;
                    this.addItemMoveY = p7.y;
                });
            });
        }, Image);
        this.observeComponentCreation2((i7, j7) => {
            Image.create(this.imageTextRemoveIcon(z6));
            Image.draggable(false);
            Image.fillColor({ "id": -1, "type": 10001, params: ["sys.color.ohos_id_color_secondary"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.visibility(a7 === "delete" && this.gridComState ? Visibility.Visible : Visibility.Hidden);
            Image.width(ICON_SIZE);
            Image.height(ICON_SIZE);
            Image.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            Image.onClick(() => this.handleDeleteClick(z6));
        }, Image);
        Column.pop();
        Column.pop();
    }
    TextBlockBuilder(e6, f6 = null) {
        this.observeComponentCreation2((x6, y6) => {
            Stack.create();
            Stack.scale(e6.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(28);
        }, Stack);
        this.observeComponentCreation2((v6, w6) => {
            Row.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
            } : { duration: 0 });
            Row.borderRadius(50);
            Row.width(this.clickRemoveBtn && e6.id === this.content.id ? this.textItemEditWidth + 8 : this.textItemEditWidth);
            Row.translate(this.gridComState ? this.clickRemoveBtn &&
                e6.id === this.content.id ? { x: 0 } : { x: -4 } : { x: 0 });
            Row.height('100%');
            Context.animation(null);
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((t6, u6) => {
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
            Flex.backgroundColor(this.isTouchDown && e6.id === this.content.id ? this.touchDown
                : e6.id === this.hoverId ? this.hoverBackgroundColor
                    : '');
            Flex.width(this.clickRemoveBtn && e6.id === this.content.id ? this.textItemEditWidth + 8 : this.textItemEditWidth);
            Flex.translate(this.gridComState ? this.clickRemoveBtn && e6.id === this.content.id ? { x: 0 } : { x: -4 } : {
                x: 0
            });
            Flex.height('100%');
            Context.animation(null);
        }, Flex);
        this.observeComponentCreation2((r6, s6) => {
            Image.create({ "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_add"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Image.width(12);
            Image.height(12);
            Image.draggable(false);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.visibility(this.clickRemoveBtn && e6.id === this.content.id ? Visibility.Visible : Visibility.None);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0, } });
            Image.margin({ right: 4 });
            Context.animation(null);
        }, Image);
        this.observeComponentCreation2((p6, q6) => {
            Text.create(e6.text);
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(1);
            Text.constraintSize(this.clickRemoveBtn && e6.id === this.content.id ? { maxWidth: 26 } : {});
        }, Text);
        Text.pop();
        this.observeComponentCreation2((m6, n6) => {
            Image.create({ "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_remove_filled"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER,
            });
            Image.draggable(false);
            Image.fillColor({ "id": -1, "type": 10001, params: ["sys.color.ohos_id_color_secondary"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(ICON_SIZE);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0, centerX: '50%' } });
            Image.scale(e6.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {});
            Image.visibility(this.gridComState ? 0 : 1);
            Image.position({
                x: this.blockWidth - 52,
                y: -MARGIN_EIGHT
            });
            Context.animation(null);
            Image.onClick(() => this.handleDeleteClick(e6));
        }, Image);
        Flex.pop();
        Stack.pop();
    }
    TextBlockAddItemBuilder(f5, g5 = null) {
        this.observeComponentCreation2((c6, d6) => {
            Stack.create();
            Stack.scale(f5.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(28);
        }, Stack);
        this.observeComponentCreation2((a6, b6) => {
            Row.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Row.borderRadius(50);
            Row.height('100%');
            Row.width(this.addIconShow && f5.id === this.content.id ? this.textItemEditWidth : '100%');
            Row.translate(this.addIconShow && f5.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Row.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((y5, z5) => {
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
            Flex.backgroundColor(this.isTouchDown && f5.id === this.content.id ? this.touchDown
                : f5.id === this.hoverId ? this.hoverBackgroundColor : '');
            Flex.width(this.addIconShow && f5.id === this.content.id ? this.textItemEditWidth : '100%');
            Flex.translate(this.addIconShow && f5.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Flex.height('100%');
        }, Flex);
        this.observeComponentCreation2((w5, x5) => {
            Image.create({ "id": -1, "type": 20000, params: ["sys.media.ohos_ic_public_add"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Image.draggable(false);
            Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(12);
            Image.height(12);
            Image.visibility(this.addIconShow && f5.id === this.content.id ? Visibility.None : Visibility.Visible);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            Image.margin({ right: 4 });
            Context.animation(null);
        }, Image);
        this.observeComponentCreation2((u5, v5) => {
            Text.create(f5.text);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Start);
            Text.maxLines(1);
            Text.constraintSize({
                maxWidth: 26
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((n5, o5) => {
            If.create();
            if (this.gridComState && this.addIconShow && f5.id === this.content.id) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s5, t5) => {
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
    AddTagBuilder(j3 = null) {
        this.observeComponentCreation2((d5, e5) => {
            Grid.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            Grid.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {});
            Context.animation(null);
            Grid.columnsTemplate(this.customColumnsTemplate());
            Grid.padding({
                left: ROW_GAP,
                right: ROW_GAP,
            });
            Grid.clip(false);
            Grid.height(this.getGridHeight(ObservedObject.GetRawObject(this.unSelected)));
        }, Grid);
        this.observeComponentCreation2((m3, n3) => {
            ForEach.create();
            const o3 = (s3, t3) => {
                const u3 = s3;
                {
                    const v3 = (a5, b5) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.clickRemoveBtn ? DRAG_SPRING : t3 === this.unSelectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getAddAreaItemTranslate(t3));
                        Context.animation(null);
                    };
                    const w3 = () => {
                        this.observeComponentCreation2(v3, GridItem);
                        this.observeComponentCreation2((f4, g4) => {
                            Stack.create();
                            Stack.onHover((z4) => {
                                if (z4) {
                                    this.hoverId = u3.id;
                                }
                                else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.onTouch((p4) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (p4.type === TouchType.Down) {
                                    this.content = u3;
                                    this.isTouchDown = true;
                                }
                                if (p4.type === TouchType.Up) {
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
                                    const q4 = this.unSelected.findIndex(y4 => y4.id === u3.id);
                                    this.editGridDataLength = this.selected.length + 1;
                                    const r4 = this.getEditItemGridPosition(ObservedObject.GetRawObject(this.selected), q4);
                                    this.content = u3;
                                    this.unSelectedIndex = q4;
                                    this.clickAddBtn = true;
                                    this.arrayUnSelectIsChange = 1;
                                    Context.animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
                                        if (!this.selected.some(x4 => x4.id === u3.id)) {
                                            this.scaleIcon = 1;
                                            this.scaleAddIcon = 0;
                                            this.selected.push(u3);
                                            this.unSelected.splice(q4, 1);
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
                                        this.addItemMoveX = r4.x;
                                        this.addItemMoveY = r4.y;
                                    });
                                }
                            });
                            Gesture.create(GesturePriority.Low);
                            LongPressGesture.create({ repeat: true });
                            LongPressGesture.onAction((m4) => {
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
                        this.observeComponentCreation2((b4, c4) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(u3, "add", j3 ? j3 : this);
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockAddItemBuilder.bind(this)(u3, j3 ? j3 : this);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    w3();
                }
            };
            this.forEachUpdateFunction(m3, this.unSelected, o3, (r3) => r3.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
    }
    EditTagBuilder(g1 = null) {
        this.observeComponentCreation2((h3, i3) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((n2, o2) => {
            Grid.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            } : { duration: 0 });
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((d3) => {
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
                    if (d3.repeat && !this.vibrationDone) {
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
            });
            LongPressGesture.pop();
            Gesture.pop();
            Grid.clip(false);
            Grid.editMode(this.gridComState);
            Grid.columnsTemplate(this.customColumnsTemplate());
            Grid.padding({
                left: ROW_GAP,
                right: ROW_GAP
            });
            Grid.height(this.getGridHeight(ObservedObject.GetRawObject(this.selected), 'edit'));
            Context.animation(null);
            Grid.onItemDragStart((b3, c3) => {
                this.selectedIndex = -1;
                if (!this.gridComState) {
                    return;
                }
                this.isStartDrag = true;
                this.editGridDataLength = this.selected.length + 1;
                this.selected.splice(c3, 1);
                return { builder: () => {
                    this.PixelMapBuilder.call(this);
                } };
            });
            Grid.onItemDrop((w2, x2, y2, z2) => {
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
                this.selected.splice(y2 === -1 ? x2 : y2, 0, ObservedObject.GetRawObject(this.content));
            });
            Grid.onItemDragMove((t2, u2, v2) => this.onDragMoveEvent(t2, u2, v2));
        }, Grid);
        this.observeComponentCreation2((k1, l1) => {
            ForEach.create();
            const m1 = (q1, r1) => {
                const s1 = q1;
                {
                    const t1 = (k2, l2) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.isStartDrag ? DRAG_SPRING : r1 === this.selectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING,
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getShowAreaItemTranslate(r1));
                        Context.animation(null);
                    };
                    const u1 = () => {
                        this.observeComponentCreation2(t1, GridItem);
                        this.observeComponentCreation2((d2, e2) => {
                            Stack.create();
                            Stack.onHover((j2) => {
                                if (j2) {
                                    this.hoverId = s1.id;
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
                            Stack.onTouch((h2) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (h2.type === TouchType.Down) {
                                    this.content = s1;
                                    this.isTouchDown = true;
                                }
                                if (h2.type === TouchType.Up) {
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
                        this.observeComponentCreation2((z1, a2) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(s1, 'delete', g1 ? g1 : this);
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockBuilder.bind(this)(s1, g1 ? g1 : this);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    u1();
                }
            };
            this.forEachUpdateFunction(k1, this.selected, m1, (p1) => p1.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
        Column.pop();
    }
    initialRender() {
        this.observeComponentCreation2((e1, f1) => {
            Column.create();
            Column.width('100%');
            Column.height('90%');
        }, Column);
        this.HeaderTitleBuilder.bind(this)(this);
        this.observeComponentCreation2((c1, d1) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((x, y) => {
            Column.create();
            Column.onAreaChange((a1, b1) => {
                this.areaWidth = Number(b1.width);
                this.blockWidth = this.getBlockWidth();
                this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
                this.imageItemWidth = this.blockWidth - 16;
                this.blockHeight = this.imageText ? this.imageItemWidth + 16 : this.gridComState ? 44 : BLOCK_TEXT_HEIGHT;
            });
            Column.width("100%");
        }, Column);
        this.observeComponentCreation2((v, w) => {
            __Common__.create();
            __Common__.margin({ bottom: MARGIN_EIGHT });
        }, __Common__);
        {
            this.observeComponentCreation2((p, q) => {
                if (q) {
                    let r = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, p, () => { }, { page: "library/src/main/ets/components/mainpage/GridObjectSortComponent.ets", line: 1163, col: 11 });
                    ViewPU.create(r);
                    let s = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.showAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    r.paramsGenerator_ = s;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(p, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        icon: '',
                        operationType: OperationType.BUTTON
                    });
                }
            }, { name: "SubHeader" });
        }
        __Common__.pop();
        this.EditTagBuilder.bind(this)(this);
        this.observeComponentCreation2((m, n) => {
            __Common__.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            __Common__.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {});
            Context.animation(null);
            __Common__.margin({ bottom: MARGIN_EIGHT });
        }, __Common__);
        {
            this.observeComponentCreation2((g, h) => {
                if (h) {
                    let i = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || { "id": -1, "type": 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, g, () => { }, { page: "library/src/main/ets/components/mainpage/GridObjectSortComponent.ets", line: 1172, col: 11 });
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
        this.AddTagBuilder.bind(this)(this);
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