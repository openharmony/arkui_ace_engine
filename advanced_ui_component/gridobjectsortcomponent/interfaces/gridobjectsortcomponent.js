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

const composetitlebar = requireNapi('arkui.advanced.composetitlebar');
const editabletitlebar = requireNapi('arkui.advanced.editabletitlebar');
const subheader = requireNapi('arkui.advanced.subheader');
const ComposeTitleBar = composetitlebar.ComposeTitleBar;
const EditableTitleBar = editabletitlebar.EditableTitleBar;
const EditableLeftIconType = editabletitlebar.EditableLeftIconType;
const SubHeader = subheader.SubHeader;

const COL_IMAGE_TEXT = 3;
const COL_TEXT = 4;
const BLOCK_TEXT_HEIGHT = 36;
const ICON_SIZE = 24;
const IMAGE_DEFAULT = 56;
const TEXT_PADDING_LEFT_RIGHT = 12;
const MARGIN_EIGHT = 8;
const ROW_GAP = 16;
const DURATION = 300;
const ENTER_EXIT_ICON_DURATION = 200;
const COMMON_BEZIER = curves.cubicBezierCurve(.33, 0, .67, 1);
const DRAG_SPRING = curves.interpolatingSpring(0, 1, 400, 38);
const REMOVE_ADD_SPRING = curves.interpolatingSpring(0, 1, 150, 24);
const LONG_TOUCH_SCALE = curves.cubicBezierCurve(.2, 0, .2, 1);

export var GridObjectSortComponentType;
!function (e) {
    e.IMAGE_TEXT = "image_text";
    e.TEXT = "text"
}(GridObjectSortComponentType || (GridObjectSortComponentType = {}));

class MenuItem {
    constructor(e, t, i) {
        this.value = e;
        this.isEnabled = t;
        this.action = i
    }
}

export class GridObjectSortComponent extends ViewPU {
    constructor(e, t, i, o = -1, s = void 0) {
        super(e, i, o);
        "function" == typeof s && (this.paramsGenerator_ = s);
        this.__options = new SynchedPropertyObjectOneWayPU(t.options, this, "options");
        this.dataList = [];
        this.__selected = new ObservedPropertyObjectPU([], this, "selected");
        this.__unSelected = new ObservedPropertyObjectPU([], this, "unSelected");
        this.__copySelected = new ObservedPropertyObjectPU([], this, "copySelected");
        this.__copyUnSelected = new ObservedPropertyObjectPU([], this, "copyUnSelected");
        this.__content = new ObservedPropertyObjectPU({ id: "", text: "", selected: !1, order: 0 }, this, "content");
        this.__hoverId = new ObservedPropertySimplePU("", this, "hoverId");
        this.__gridComState = new ObservedPropertySimplePU(!1, this, "gridComState");
        this.__menuSwitch = new ObservedPropertySimplePU(!1, this, "menuSwitch");
        this.__areaWidth = new ObservedPropertySimplePU(0, this, "areaWidth");
        this.__blockWidth = new ObservedPropertySimplePU(0, this, "blockWidth");
        this.__blockHeight = new ObservedPropertySimplePU(0, this, "blockHeight");
        this.__longScaleOnePointTwo = new ObservedPropertySimplePU(1, this, "longScaleOnePointTwo");
        this.__scaleGridItemNinetyPercent = new ObservedPropertySimplePU(1, this, "scaleGridItemNinetyPercent");
        this.__reboundSize = new ObservedPropertySimplePU(1, this, "reboundSize");
        this.__scaleIcon = new ObservedPropertySimplePU(1, this, "scaleIcon");
        this.__addIconShow = new ObservedPropertySimplePU(!1, this, "addIconShow");
        this.__scaleAddIcon = new ObservedPropertySimplePU(0, this, "scaleAddIcon");
        this.__isStartDrag = new ObservedPropertySimplePU(!1, this, "isStartDrag");
        this.__insertIndex = new ObservedPropertySimplePU(-1, this, "insertIndex");
        this.__editGridDataLength = new ObservedPropertySimplePU(-1, this, "editGridDataLength");
        this.__isTouchDown = new ObservedPropertySimplePU(!1, this, "isTouchDown");
        this.__endX = new ObservedPropertySimplePU(0, this, "endX");
        this.__endY = new ObservedPropertySimplePU(0, this, "endY");
        this.__unSelectedIndex = new ObservedPropertySimplePU(0, this, "unSelectedIndex");
        this.__clickAddBtn = new ObservedPropertySimplePU(!1, this, "clickAddBtn");
        this.__selectedIndex = new ObservedPropertySimplePU(-1, this, "selectedIndex");
        this.__gridHeight = new ObservedPropertySimplePU(0, this, "gridHeight");
        this.__clickRemoveBtn = new ObservedPropertySimplePU(!1, this, "clickRemoveBtn");
        this.__addAreaLongPressGesture = new ObservedPropertySimplePU(!1, this, "addAreaLongPressGesture");
        this.__itemMoveX = new ObservedPropertySimplePU(0, this, "itemMoveX");
        this.__itemMoveY = new ObservedPropertySimplePU(0, this, "itemMoveY");
        this.__arraySelectIsChange = new ObservedPropertySimplePU(0, this, "arraySelectIsChange");
        this.__arrayUnSelectIsChange = new ObservedPropertySimplePU(0, this, "arrayUnSelectIsChange");
        this.__textItemEditWidth = new ObservedPropertySimplePU(0, this, "textItemEditWidth");
        this.__imageItemWidth = new ObservedPropertySimplePU(0, this, "imageItemWidth");
        this.__saveClick = new ObservedPropertySimplePU(!1, this, "saveClick");
        this.colNum = 3;
        this.vibrationDone = !1;
        this.touchDown = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
        };
        this.touchBorderRadius = {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_corner_radius_clicked"],
            bundleName: "",
            moduleName: ""
        };
        this.hoverBackgroundColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_hover"],
            bundleName: "",
            moduleName: ""
        };
        this.focusBorder = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_focused_outline"],
            bundleName: "",
            moduleName: ""
        };
        this.imageText = !1;
        this.initPosition = [];
        this.scroller = new Scroller;
        this.onSave = void 0;
        this.onCancel = void 0;
        this.menuItems = [new MenuItem({
            id: -1,
            type: 2e4,
            params: ["sys.media.ohos_ic_public_edit"],
            bundleName: "",
            moduleName: ""
        }, !0, (() => {
            this.goEdit()
        }))];
        this.setInitiallyProvidedValue(t);
        this.declareWatch("gridComState", this.onGridComStateChange)
    }

    setInitiallyProvidedValue(e) {
        void 0 === e.options && this.__options.set({});
        void 0 !== e.dataList && (this.dataList = e.dataList);
        void 0 !== e.selected && (this.selected = e.selected);
        void 0 !== e.unSelected && (this.unSelected = e.unSelected);
        void 0 !== e.copySelected && (this.copySelected = e.copySelected);
        void 0 !== e.copyUnSelected && (this.copyUnSelected = e.copyUnSelected);
        void 0 !== e.content && (this.content = e.content);
        void 0 !== e.hoverId && (this.hoverId = e.hoverId);
        void 0 !== e.gridComState && (this.gridComState = e.gridComState);
        void 0 !== e.menuSwitch && (this.menuSwitch = e.menuSwitch);
        void 0 !== e.areaWidth && (this.areaWidth = e.areaWidth);
        void 0 !== e.blockWidth && (this.blockWidth = e.blockWidth);
        void 0 !== e.blockHeight && (this.blockHeight = e.blockHeight);
        void 0 !== e.longScaleOnePointTwo && (this.longScaleOnePointTwo = e.longScaleOnePointTwo);
        void 0 !== e.scaleGridItemNinetyPercent && (this.scaleGridItemNinetyPercent = e.scaleGridItemNinetyPercent);
        void 0 !== e.reboundSize && (this.reboundSize = e.reboundSize);
        void 0 !== e.scaleIcon && (this.scaleIcon = e.scaleIcon);
        void 0 !== e.addIconShow && (this.addIconShow = e.addIconShow);
        void 0 !== e.scaleAddIcon && (this.scaleAddIcon = e.scaleAddIcon);
        void 0 !== e.isStartDrag && (this.isStartDrag = e.isStartDrag);
        void 0 !== e.insertIndex && (this.insertIndex = e.insertIndex);
        void 0 !== e.editGridDataLength && (this.editGridDataLength = e.editGridDataLength);
        void 0 !== e.isTouchDown && (this.isTouchDown = e.isTouchDown);
        void 0 !== e.endX && (this.endX = e.endX);
        void 0 !== e.endY && (this.endY = e.endY);
        void 0 !== e.unSelectedIndex && (this.unSelectedIndex = e.unSelectedIndex);
        void 0 !== e.clickAddBtn && (this.clickAddBtn = e.clickAddBtn);
        void 0 !== e.selectedIndex && (this.selectedIndex = e.selectedIndex);
        void 0 !== e.gridHeight && (this.gridHeight = e.gridHeight);
        void 0 !== e.clickRemoveBtn && (this.clickRemoveBtn = e.clickRemoveBtn);
        void 0 !== e.addAreaLongPressGesture && (this.addAreaLongPressGesture = e.addAreaLongPressGesture);
        void 0 !== e.itemMoveX && (this.itemMoveX = e.itemMoveX);
        void 0 !== e.itemMoveY && (this.itemMoveY = e.itemMoveY);
        void 0 !== e.arraySelectIsChange && (this.arraySelectIsChange = e.arraySelectIsChange);
        void 0 !== e.arrayUnSelectIsChange && (this.arrayUnSelectIsChange = e.arrayUnSelectIsChange);
        void 0 !== e.textItemEditWidth && (this.textItemEditWidth = e.textItemEditWidth);
        void 0 !== e.imageItemWidth && (this.imageItemWidth = e.imageItemWidth);
        void 0 !== e.saveClick && (this.saveClick = e.saveClick);
        void 0 !== e.colNum && (this.colNum = e.colNum);
        void 0 !== e.vibrationDone && (this.vibrationDone = e.vibrationDone);
        void 0 !== e.touchDown && (this.touchDown = e.touchDown);
        void 0 !== e.touchBorderRadius && (this.touchBorderRadius = e.touchBorderRadius);
        void 0 !== e.hoverBackgroundColor && (this.hoverBackgroundColor = e.hoverBackgroundColor);
        void 0 !== e.focusBorder && (this.focusBorder = e.focusBorder);
        void 0 !== e.imageText && (this.imageText = e.imageText);
        void 0 !== e.initPosition && (this.initPosition = e.initPosition);
        void 0 !== e.scroller && (this.scroller = e.scroller);
        void 0 !== e.onSave && (this.onSave = e.onSave);
        void 0 !== e.onCancel && (this.onCancel = e.onCancel);
        void 0 !== e.menuItems && (this.menuItems = e.menuItems)
    }

    updateStateVars(e) {
        this.__options.reset(e.options)
    }

    purgeVariableDependenciesOnElmtId(e) {
        this.__options.purgeDependencyOnElmtId(e);
        this.__selected.purgeDependencyOnElmtId(e);
        this.__unSelected.purgeDependencyOnElmtId(e);
        this.__copySelected.purgeDependencyOnElmtId(e);
        this.__copyUnSelected.purgeDependencyOnElmtId(e);
        this.__content.purgeDependencyOnElmtId(e);
        this.__hoverId.purgeDependencyOnElmtId(e);
        this.__gridComState.purgeDependencyOnElmtId(e);
        this.__menuSwitch.purgeDependencyOnElmtId(e);
        this.__areaWidth.purgeDependencyOnElmtId(e);
        this.__blockWidth.purgeDependencyOnElmtId(e);
        this.__blockHeight.purgeDependencyOnElmtId(e);
        this.__longScaleOnePointTwo.purgeDependencyOnElmtId(e);
        this.__scaleGridItemNinetyPercent.purgeDependencyOnElmtId(e);
        this.__reboundSize.purgeDependencyOnElmtId(e);
        this.__scaleIcon.purgeDependencyOnElmtId(e);
        this.__addIconShow.purgeDependencyOnElmtId(e);
        this.__scaleAddIcon.purgeDependencyOnElmtId(e);
        this.__isStartDrag.purgeDependencyOnElmtId(e);
        this.__insertIndex.purgeDependencyOnElmtId(e);
        this.__editGridDataLength.purgeDependencyOnElmtId(e);
        this.__isTouchDown.purgeDependencyOnElmtId(e);
        this.__endX.purgeDependencyOnElmtId(e);
        this.__endY.purgeDependencyOnElmtId(e);
        this.__unSelectedIndex.purgeDependencyOnElmtId(e);
        this.__clickAddBtn.purgeDependencyOnElmtId(e);
        this.__selectedIndex.purgeDependencyOnElmtId(e);
        this.__gridHeight.purgeDependencyOnElmtId(e);
        this.__clickRemoveBtn.purgeDependencyOnElmtId(e);
        this.__addAreaLongPressGesture.purgeDependencyOnElmtId(e);
        this.__itemMoveX.purgeDependencyOnElmtId(e);
        this.__itemMoveY.purgeDependencyOnElmtId(e);
        this.__arraySelectIsChange.purgeDependencyOnElmtId(e);
        this.__arrayUnSelectIsChange.purgeDependencyOnElmtId(e);
        this.__textItemEditWidth.purgeDependencyOnElmtId(e);
        this.__imageItemWidth.purgeDependencyOnElmtId(e);
        this.__saveClick.purgeDependencyOnElmtId(e)
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
        this.__endX.aboutToBeDeleted();
        this.__endY.aboutToBeDeleted();
        this.__unSelectedIndex.aboutToBeDeleted();
        this.__clickAddBtn.aboutToBeDeleted();
        this.__selectedIndex.aboutToBeDeleted();
        this.__gridHeight.aboutToBeDeleted();
        this.__clickRemoveBtn.aboutToBeDeleted();
        this.__addAreaLongPressGesture.aboutToBeDeleted();
        this.__itemMoveX.aboutToBeDeleted();
        this.__itemMoveY.aboutToBeDeleted();
        this.__arraySelectIsChange.aboutToBeDeleted();
        this.__arrayUnSelectIsChange.aboutToBeDeleted();
        this.__textItemEditWidth.aboutToBeDeleted();
        this.__imageItemWidth.aboutToBeDeleted();
        this.__saveClick.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get options() {
        return this.__options.get()
    }

    set options(e) {
        this.__options.set(e)
    }

    get selected() {
        return this.__selected.get()
    }

    set selected(e) {
        this.__selected.set(e)
    }

    get unSelected() {
        return this.__unSelected.get()
    }

    set unSelected(e) {
        this.__unSelected.set(e)
    }

    get copySelected() {
        return this.__copySelected.get()
    }

    set copySelected(e) {
        this.__copySelected.set(e)
    }

    get copyUnSelected() {
        return this.__copyUnSelected.get()
    }

    set copyUnSelected(e) {
        this.__copyUnSelected.set(e)
    }

    get content() {
        return this.__content.get()
    }

    set content(e) {
        this.__content.set(e)
    }

    get hoverId() {
        return this.__hoverId.get()
    }

    set hoverId(e) {
        this.__hoverId.set(e)
    }

    get gridComState() {
        return this.__gridComState.get()
    }

    set gridComState(e) {
        this.__gridComState.set(e)
    }

    get menuSwitch() {
        return this.__menuSwitch.get()
    }

    set menuSwitch(e) {
        this.__menuSwitch.set(e)
    }

    get areaWidth() {
        return this.__areaWidth.get()
    }

    set areaWidth(e) {
        this.__areaWidth.set(e)
    }

    get blockWidth() {
        return this.__blockWidth.get()
    }

    set blockWidth(e) {
        this.__blockWidth.set(e)
    }

    get blockHeight() {
        return this.__blockHeight.get()
    }

    set blockHeight(e) {
        this.__blockHeight.set(e)
    }

    get longScaleOnePointTwo() {
        return this.__longScaleOnePointTwo.get()
    }

    set longScaleOnePointTwo(e) {
        this.__longScaleOnePointTwo.set(e)
    }

    get scaleGridItemNinetyPercent() {
        return this.__scaleGridItemNinetyPercent.get()
    }

    set scaleGridItemNinetyPercent(e) {
        this.__scaleGridItemNinetyPercent.set(e)
    }

    get reboundSize() {
        return this.__reboundSize.get()
    }

    set reboundSize(e) {
        this.__reboundSize.set(e)
    }

    get scaleIcon() {
        return this.__scaleIcon.get()
    }

    set scaleIcon(e) {
        this.__scaleIcon.set(e)
    }

    get addIconShow() {
        return this.__addIconShow.get()
    }

    set addIconShow(e) {
        this.__addIconShow.set(e)
    }

    get scaleAddIcon() {
        return this.__scaleAddIcon.get()
    }

    set scaleAddIcon(e) {
        this.__scaleAddIcon.set(e)
    }

    get isStartDrag() {
        return this.__isStartDrag.get()
    }

    set isStartDrag(e) {
        this.__isStartDrag.set(e)
    }

    get insertIndex() {
        return this.__insertIndex.get()
    }

    set insertIndex(e) {
        this.__insertIndex.set(e)
    }

    get editGridDataLength() {
        return this.__editGridDataLength.get()
    }

    set editGridDataLength(e) {
        this.__editGridDataLength.set(e)
    }

    get isTouchDown() {
        return this.__isTouchDown.get()
    }

    set isTouchDown(e) {
        this.__isTouchDown.set(e)
    }

    get endX() {
        return this.__endX.get()
    }

    set endX(e) {
        this.__endX.set(e)
    }

    get endY() {
        return this.__endY.get()
    }

    set endY(e) {
        this.__endY.set(e)
    }

    get unSelectedIndex() {
        return this.__unSelectedIndex.get()
    }

    set unSelectedIndex(e) {
        this.__unSelectedIndex.set(e)
    }

    get clickAddBtn() {
        return this.__clickAddBtn.get()
    }

    set clickAddBtn(e) {
        this.__clickAddBtn.set(e)
    }

    get selectedIndex() {
        return this.__selectedIndex.get()
    }

    set selectedIndex(e) {
        this.__selectedIndex.set(e)
    }

    get gridHeight() {
        return this.__gridHeight.get()
    }

    set gridHeight(e) {
        this.__gridHeight.set(e)
    }

    get clickRemoveBtn() {
        return this.__clickRemoveBtn.get()
    }

    set clickRemoveBtn(e) {
        this.__clickRemoveBtn.set(e)
    }

    get addAreaLongPressGesture() {
        return this.__addAreaLongPressGesture.get()
    }

    set addAreaLongPressGesture(e) {
        this.__addAreaLongPressGesture.set(e)
    }

    get itemMoveX() {
        return this.__itemMoveX.get()
    }

    set itemMoveX(e) {
        this.__itemMoveX.set(e)
    }

    get itemMoveY() {
        return this.__itemMoveY.get()
    }

    set itemMoveY(e) {
        this.__itemMoveY.set(e)
    }

    get arraySelectIsChange() {
        return this.__arraySelectIsChange.get()
    }

    set arraySelectIsChange(e) {
        this.__arraySelectIsChange.set(e)
    }

    get arrayUnSelectIsChange() {
        return this.__arrayUnSelectIsChange.get()
    }

    set arrayUnSelectIsChange(e) {
        this.__arrayUnSelectIsChange.set(e)
    }

    get textItemEditWidth() {
        return this.__textItemEditWidth.get()
    }

    set textItemEditWidth(e) {
        this.__textItemEditWidth.set(e)
    }

    get imageItemWidth() {
        return this.__imageItemWidth.get()
    }

    set imageItemWidth(e) {
        this.__imageItemWidth.set(e)
    }

    get saveClick() {
        return this.__saveClick.get()
    }

    set saveClick(e) {
        this.__saveClick.set(e)
    }

    aboutToAppear() {
        this.dataList.length = 50;
        this.selected = this.dataList && this.deduplicate(this.dataList).filter((e => e.selected)).sort(this.sortBy());
        this.unSelected = this.dataList && this.deduplicate(this.dataList).filter((e => !e.selected)).sort(this.sortBy());
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
        this.colNum = this.imageText ? 3 : 4
    }

    deduplicate(e) {
        const t = [];
        e.forEach((e => {
            t.some((t => t.id === e.id)) || t.push(e)
        }));
        return t
    }

    onGridComStateChange() {
        this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
        this.imageText || (this.blockHeight = this.gridComState ? 44 : 36)
    }

    sortBy() {
        return (e, t) => e.order - t.order
    }

    cancelEdit() {
        Context.animateTo({ duration: 200, curve: LONG_TOUCH_SCALE }, (() => {
            this.longScaleOnePointTwo = 1
        }));
        Context.animateTo({ duration: 200, curve: COMMON_BEZIER }, (() => {
            this.gridComState = !1
        }));
        this.menuSwitch = !1;
        this.selected = this.copySelected.slice();
        this.unSelected = this.copyUnSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.onCancel && this.onCancel()
    }

    goEdit() {
        Context.animateTo({ duration: 200, curve: COMMON_BEZIER }, (() => {
            this.gridComState = !0
        }));
        this.menuSwitch = !0
    }

    onSaveEdit() {
        Context.animateTo({ duration: 200, curve: LONG_TOUCH_SCALE }, (() => {
            this.longScaleOnePointTwo = 1
        }));
        this.editGridDataLength = this.selected.length;
        Context.animateTo({ duration: 200, curve: COMMON_BEZIER }, (() => {
            this.gridComState = !1;
            this.copySelected = this.selected.slice();
            this.copyUnSelected = this.unSelected.slice();
            const e = this.getNewData(this.selected, !0, 0);
            const t = this.getNewData(this.unSelected, !1, this.selected.length);
            this.selected = e;
            this.unSelected = t;
            this.onSave && this.onSave(e, t)
        }));
        setTimeout((() => {
            this.saveClick = !1
        }), 200);
        this.menuSwitch = !1
    }

    aboutToDisappear() {
        Context.animateTo({ duration: 200, curve: COMMON_BEZIER }, (() => {
            this.gridComState = !1
        }));
        this.menuSwitch = !1;
        this.selected = this.copySelected;
        this.unSelected = this.copyUnSelected
    }

    customColumnsTemplate() {
        let e = "1fr 1fr 1fr 1fr";
        this.imageText && (e = "1fr 1fr 1fr");
        return e
    }

    getNewData(e, t, i) {
        return e.map(((e, o) => {
            e.selected = t;
            e.order = i + o;
            return e
        }))
    }

    getBlockWidth() {
        const e = (this.areaWidth - 32) / this.colNum;
        return e
    }

    getEditItemGridPosition(e, t) {
        const i = e.length;
        const o = this.colNum;
        const s = Math.trunc(i % o);
        const n = Math.trunc(t % o);
        let d = Math.abs(s - n) * this.blockWidth;
        s < n ? d = -d : s > n || (d = 0);
        let a = 0;
        a = (Math.trunc(t / this.colNum) + 1) * this.blockHeight + 56;
        return { x: d, y: a }
    }

    getAddItemGridPosition(e) {
        const t = this.unSelected.length;
        const i = this.colNum;
        const o = Math.trunc(t % i);
        const s = Math.trunc(e % i);
        const n = o;
        let d = Math.abs(n - s) * this.blockWidth;
        n < s ? d = -d : n > s || (d = 0);
        let a = 0;
        let r = Math.trunc(e / this.colNum);
        const h = t % i == 0 ? 0 : 1;
        let l = Math.trunc(t / this.colNum) + h;
        const c = this.selected.length;
        const m = c % i == 0 ? 0 : 1;
        let g = Math.trunc(c / this.colNum) + m;
        a = 0 === o ? (l + (g - r)) * this.blockHeight + 56 : (l - 1 + (g - r)) * this.blockHeight + 56;
        return { x: d, y: a }
    }

    getAddItemGridFirstPosition(e) {
        const t = this.selected.length;
        const i = this.colNum;
        const o = (e + 1) % i;
        const s = Math.ceil((e + 1) / i);
        const n = Math.ceil(t / i);
        const d = this.imageText;
        let a = 0;
        a = 0 === o ? d ? 2 * -this.blockWidth : 3 * -this.blockWidth : -this.blockWidth * (o - 1);
        let r = 0;
        const h = n - s;
        r = (h + 1) * this.blockHeight + 56;
        return { x: a, y: r }
    }

    getCoveringGridPosition(e, t, i) {
        const o = e.length;
        let s = 0;
        let n = 0;
        if (t > i) if (i === o - 1) {
            s = 0;
            n = 0
        } else if (2 !== this.arraySelectIsChange) {
            s = t % this.colNum == 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            n = t % this.colNum == 0 ? -this.blockHeight : 0
        }
        return { x: s, y: n }
    }

    onDragMoveEvent(e, t, i) {
        if (!this.gridComState || e.x < this.blockWidth / 3 && e.y < this.blockHeight / 3) return;
        let o = i;
        i < 0 && (o = this.selected.length - 1);
        this.insertIndex = i
    }

    handleDeleteClick(e) {
        if (this.clickRemoveBtn) return;
        this.scaleIcon = 0;
        this.clickRemoveBtn = !0;
        this.arraySelectIsChange = 1;
        let t = 0;
        this.content = e;
        this.selected.forEach(((i, o) => {
            i.id === e.id && (t = o)
        }));
        this.selectedIndex = t;
        setTimeout((() => {
            this.scaleIcon = 1;
            this.arraySelectIsChange = 2;
            this.unSelected.push(e);
            this.selected.splice(t, 1);
            this.editGridDataLength = this.editGridDataLength - 1;
            this.clickRemoveBtn = !1
        }), 500)
    }

    getCoodXY(e) {
        const t = this.colNum;
        let i = 0;
        let o = 0;
        if (e >= this.insertIndex) if (Math.trunc(e % t) === t - 1) {
            i -= this.blockWidth * (t - 1);
            o += this.blockHeight
        } else i += this.blockWidth;
        if (!this.isStartDrag) {
            i = 0;
            o = 0
        }
        return { x: i, y: o }
    }

    getGridNum(e, t) {
        let i = e.length;
        let o = 0;
        t ? (this.isStartDrag || 0 !== Math.trunc(i % this.colNum) && this.editGridDataLength === i || this.clickAddBtn) && (o = 1) : 0 !== Math.trunc(i % this.colNum) && (o = 1);
        return o
    }

    getGridHeight(e, t) {
        let i = 0;
        let o = e.length;
        let s = e;
        const n = Math.trunc(o / this.colNum) + this.getGridNum(s, t);
        i = this.blockHeight * n;
        0 === o && (i = 0);
        t && (this.gridHeight = i);
        return i
    }

    getXY(e, t, i) {
        let o = 0;
        let s = 0;
        if (this.isStartDrag) {
            o = this.getCoodXY(t).x;
            s = this.getCoodXY(t).y
        } else if (this.clickRemoveBtn) if (t === i) {
            o = this.getAddItemGridPosition(i).x;
            s = this.getAddItemGridPosition(i).y
        } else {
            o = this.getCoveringGridPosition(e, t, i).x;
            s = this.getCoveringGridPosition(e, t, i).y
        }
        return { x: o, y: s }
    }

    getCoveringGridPositionBottom(e, t, i) {
        const o = e.length;
        let s = 0;
        let n = 0;
        if (t > i) if (i === o - 1) {
            s = 0;
            n = 0
        } else if (2 !== this.arrayUnSelectIsChange) {
            s = t % this.colNum == 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            n = t % this.colNum == 0 ? -this.blockHeight : 0
        }
        return { x: s, y: n }
    }

    getUnSelectXY(e, t, i) {
        let o = 0;
        let s = 0;
        if (this.clickAddBtn) if (t === this.unSelectedIndex) {
            o = this.endX;
            s = -this.endY
        } else {
            o = this.getCoveringGridPositionBottom(e, t, i).x;
            s = this.getCoveringGridPositionBottom(e, t, i).y
        }
        return { x: o, y: s }
    }

    PixelMapBuilder(e = null) {
        this.observeComponentCreation2(((e, t) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.clip(!1);
            Stack.height(1.5 * this.blockHeight);
            Stack.width(1.2 * this.blockWidth);
        }), Stack);
        this.observeComponentCreation2(((e, t) => {
            If.create();
            this.imageText ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((e, t) => {
                    Column.create();
                    Column.alignItems(HorizontalAlign.Center);
                    Column.justifyContent(FlexAlign.Center);
                    Column.width(this.imageItemWidth);
                    Column.height(this.imageItemWidth);
                    Column.padding({ left: 8, right: 8 });
                    Column.backgroundColor(this.touchDown);
                    Column.borderRadius(this.touchBorderRadius);
                    Column.scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo });
                }), Column);
                this.observeComponentCreation2(((e, t) => {
                    Image.create(this.content.url);
                    Image.draggable(!1);
                    Image.height(this.options.imageSize || 56);
                    Image.width(this.options.imageSize || 56);
                }), Image);
                this.observeComponentCreation2(((e, t) => {
                    Text.create(this.content.text);
                    Text.textAlign(TextAlign.Center);
                    Text.fontSize({
                        id: -1,
                        type: 10002,
                        params: ["sys.float.ohos_id_text_size_button3"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.margin({ top: 2 });
                    Text.maxLines(1);
                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    Text.textAlign(TextAlign.Center);
                }), Text);
                Text.pop();
                this.observeComponentCreation2(((e, t) => {
                    Image.create({
                        id: -1,
                        type: 2e4,
                        params: ["sys.media.ohos_ic_public_remove_filled"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.draggable(!1);
                    Image.fillColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_secondary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.width(24);
                    Image.height(24);
                    Image.position({ x: this.blockWidth - 40, y: -8 });
                }), Image);
                Column.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
                this.observeComponentCreation2(((e, t) => {
                    Row.create();
                    Row.borderRadius(50);
                    Row.padding({ left: 12, right: 12 });
                    Row.scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo });
                    Row.alignItems(VerticalAlign.Center);
                    Row.justifyContent(FlexAlign.Center);
                    Row.backgroundColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_button_normal"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Row.width(this.textItemEditWidth);
                    Row.height(28);
                }), Row);
                this.observeComponentCreation2(((e, t) => {
                    Text.create(this.content.text);
                    Text.fontColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_text_primary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.fontSize({
                        id: -1,
                        type: 10002,
                        params: ["sys.float.ohos_id_text_size_button3"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    Text.textAlign(TextAlign.Center);
                    Text.maxLines(1);
                }), Text);
                Text.pop();
                this.observeComponentCreation2(((e, t) => {
                    Image.create({
                        id: -1,
                        type: 2e4,
                        params: ["sys.media.ohos_ic_public_remove_filled"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.draggable(!1);
                    Image.fillColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_secondary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.width(24);
                    Image.height(24);
                    Image.position({ x: this.blockWidth - 52, y: -8 });
                }), Image);
                Row.pop()
            }));
        }), If);
        If.pop();
        Stack.pop()
    }


    MoveMask(e = null) {
        this.observeComponentCreation2(((e, t) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.height(this.blockHeight);
            Stack.width(this.blockWidth);
        }), Stack);
        this.observeComponentCreation2(((e, t) => {
            If.create();
            this.imageText ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((e, t) => {
                    Column.create();
                    Column.alignItems(HorizontalAlign.Center);
                    Column.justifyContent(FlexAlign.Center);
                    Column.width(this.imageItemWidth);
                    Column.height(this.imageItemWidth);
                    Column.padding({ left: 8, right: 8 });
                    Column.backgroundColor(this.touchDown);
                    Column.borderRadius(this.touchBorderRadius);
                }), Column);
                this.observeComponentCreation2(((e, t) => {
                    Image.create(this.content.url);
                    Image.draggable(!1);
                    Image.height(this.options.imageSize || 56);
                    Image.width(this.options.imageSize || 56);
                }), Image);
                this.observeComponentCreation2(((e, t) => {
                    Text.create(this.content.text);
                    Text.textAlign(TextAlign.Center);
                    Text.fontSize({
                        id: -1,
                        type: 10002,
                        params: ["sys.float.ohos_id_text_size_button3"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.margin({ top: 2 });
                    Text.maxLines(1);
                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    Text.textAlign(TextAlign.Center);
                }), Text);
                Text.pop();
                this.observeComponentCreation2(((e, t) => {
                    Image.create({
                        id: -1,
                        type: 2e4,
                        params: ["sys.media.ohos_ic_public_remove_filled"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.draggable(!1);
                    Image.fillColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_secondary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.width(24);
                    Image.height(24);
                    Image.position({ x: this.blockWidth - 40, y: -8 });
                }), Image);
                Column.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
                this.observeComponentCreation2(((e, t) => {
                    Row.create();
                    Row.borderRadius(50);
                    Row.padding({ left: 12, right: 12 });
                    Row.alignItems(VerticalAlign.Center);
                    Row.justifyContent(FlexAlign.Center);
                    Row.backgroundColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_button_normal"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Row.width(this.textItemEditWidth);
                    Row.height(28);
                }), Row);
                this.observeComponentCreation2(((e, t) => {
                    Text.create(this.content.text);
                    Text.fontColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_text_primary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.fontSize({
                        id: -1,
                        type: 10002,
                        params: ["sys.float.ohos_id_text_size_button3"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    Text.textAlign(TextAlign.Center);
                    Text.maxLines(1);
                }), Text);
                Text.pop();
                this.observeComponentCreation2(((e, t) => {
                    Image.create({
                        id: -1,
                        type: 2e4,
                        params: ["sys.media.ohos_ic_public_remove_filled"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.draggable(!1);
                    Image.fillColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_secondary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.width(24);
                    Image.height(24);
                    Image.position({ x: this.blockWidth - 52, y: -8 });
                }), Image);
                Row.pop()
            }));
        }), If);
        If.pop();
        Stack.pop()
    }

    HeaderTitleBuilder(e = null) {
        this.observeComponentCreation2(((e, t) => {
            __Common__.create();
            __Common__.visibility(this.menuSwitch ? Visibility.None : Visibility.Visible)
        }), __Common__);
        this.observeComponentCreation2(((e, t) => {
            if (t) {
                let t = () => ({
                    title: this.options.normalTitle || {
                        id: -1,
                        type: 10003,
                        params: ["sys.string.ohos_grid_edit_title_chanel"],
                        bundleName: "",
                        moduleName: ""
                    },
                    menuItems: this.menuItems
                });
                ViewPU.create(new ComposeTitleBar(this, {
                    title: this.options.normalTitle || {
                        id: -1,
                        type: 10003,
                        params: ["sys.string.ohos_grid_edit_title_chanel"],
                        bundleName: "",
                        moduleName: ""
                    },
                    menuItems: this.menuItems
                }, void 0, e, t))
            } else this.updateStateVarsOfChildByElmtId(e, {})
        }), null);
        __Common__.pop();
        this.observeComponentCreation2(((e, t) => {
            __Common__.create();
            __Common__.visibility(this.menuSwitch ? Visibility.Visible : Visibility.None)
        }), __Common__);
        this.observeComponentCreation2(((e, t) => {
            if (t) {
                let t = () => ({
                    leftIconStyle: EditableLeftIconType.Cancel,
                    menuItems: [],
                    title: this.options.editTitle || {
                        id: -1,
                        type: 10003,
                        params: ["sys.string.ohos_grid_edit_title_edit"],
                        bundleName: "",
                        moduleName: ""
                    },
                    onCancel: () => {
                        this.cancelEdit()
                    },
                    onSave: () => {
                        this.saveClick = !0;
                        this.onSaveEdit()
                    }
                });
                ViewPU.create(new EditableTitleBar(this, {
                    leftIconStyle: EditableLeftIconType.Cancel,
                    menuItems: [],
                    title: this.options.editTitle || {
                        id: -1,
                        type: 10003,
                        params: ["sys.string.ohos_grid_edit_title_edit"],
                        bundleName: "",
                        moduleName: ""
                    },
                    onCancel: () => {
                        this.cancelEdit()
                    },
                    onSave: () => {
                        this.saveClick = !0;
                        this.onSaveEdit()
                    }
                }, void 0, e, t))
            } else this.updateStateVarsOfChildByElmtId(e, {})
        }), null);
        __Common__.pop()
    }

    ImageTextBuilder(e, t, i = null) {
        this.observeComponentCreation2(((e, t) => {
            Column.create();
            Column.padding({ left: 8, right: 8 });
            Column.width("100%");
        }), Column);
        this.observeComponentCreation2(((t, i) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Center);
            Column.justifyContent(FlexAlign.Center);
            Column.width("100%");
            Column.height(this.imageItemWidth);
            Column.padding({ left: 8, right: 8 });
            Column.borderRadius(this.isTouchDown && e.id === this.content.id || e.id === this.hoverId ? this.touchBorderRadius : 0);
            Column.backgroundColor(this.isTouchDown && e.id === this.content.id ? this.touchDown : e.id === this.hoverId ? this.hoverBackgroundColor : "");
            Column.scale(e.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
        }), Column);
        this.observeComponentCreation2(((t, i) => {
            Image.create(e.url);
            Image.draggable(!1);
            Image.height(this.options.imageSize || 56);
            Image.width(this.options.imageSize || 56);
        }), Image);
        this.observeComponentCreation2(((t, i) => {
            Text.create(e.text);
            Text.textAlign(TextAlign.Center);
            Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_button3"],
                bundleName: "",
                moduleName: ""
            });
            Text.margin({ top: 2 });
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
        }), Text);
        Text.pop();
        this.observeComponentCreation2(((i, o) => {
            Image.create({
                id: -1,
                type: 2e4,
                params: ["sys.media.ohos_ic_public_add_norm_filled"],
                bundleName: "",
                moduleName: ""
            });
            Context.animation({ duration: 300, curve: Curve.Linear, iterations: 1, playMode: PlayMode.Normal });
            Image.draggable(!1);
            Image.visibility("add" === t ? Visibility.Visible : Visibility.Hidden);
            Image.fillColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_secondary"],
                bundleName: "",
                moduleName: ""
            });
            Image.width(24);
            Image.height(24);
            Context.animation(null);
            Image.position({ x: this.blockWidth - 40, y: -8 });
            Image.onClick((() => {
                if (this.clickAddBtn) return;
                this.scaleIcon = 0;
                this.content = e;
                const t = this.unSelected.findIndex((t => t.id === e.id));
                this.editGridDataLength = this.selected.length + 1;
                const i = this.getEditItemGridPosition(ObservedObject.GetRawObject(this.selected), t);
                this.unSelectedIndex = t;
                this.endX = i.x;
                this.endY = i.y;
                this.arrayUnSelectIsChange = 1;
                this.clickAddBtn = !0;
                setTimeout((() => {
                    this.arrayUnSelectIsChange = 2;
                    this.scaleIcon = 1;
                    this.selected.push(e);
                    this.unSelected.splice(t, 1);
                    this.endX = 0;
                    this.endY = 0;
                    this.gridComState || this.onSaveEdit();
                    this.clickAddBtn = !1
                }), 500)
            }));
        }), Image);
        this.observeComponentCreation2(((i, o) => {
            Image.create({
                id: -1,
                type: 2e4,
                params: ["sys.media.ohos_ic_public_remove_filled"],
                bundleName: "",
                moduleName: ""
            });
            Context.animation({ duration: 300, curve: Curve.Linear });
            Image.draggable(!1);
            Image.fillColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_secondary"],
                bundleName: "",
                moduleName: ""
            });
            Image.visibility("delete" === t && this.gridComState ? Visibility.Visible : Visibility.Hidden);
            Image.width(24);
            Image.height(24);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            Image.position({ x: this.blockWidth - 40, y: -8 });
            Context.animation(null);
            Image.onClick((() => this.handleDeleteClick(e)));
        }), Image);
        Column.pop();
        Column.pop()
    }

    TextBlockBuilder(e, t = null) {
        this.observeComponentCreation2(((t, i) => {
            Stack.create();
            Stack.scale(e.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({ left: 8, right: 8 });
            Stack.height(28);
        }), Stack);
        this.observeComponentCreation2(((t, i) => {
            Row.create();
            Context.animation({ duration: 200, curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER });
            Row.borderRadius(50);
            Row.width(this.clickRemoveBtn && e.id === this.content.id ? this.textItemEditWidth + 8 : this.textItemEditWidth);
            Row.translate(this.gridComState ? this.clickRemoveBtn && e.id === this.content.id ? { x: 0 } : { x: -4 } : {
                x: 0
            });
            Row.height("100%");
            Context.animation(null);
            Row.backgroundColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_button_normal"],
                bundleName: "",
                moduleName: ""
            });
        }), Row);
        Row.pop();
        this.observeComponentCreation2(((t, i) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Context.animation({ duration: 200, curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER });
            Flex.borderRadius(50);
            Flex.padding({ left: 12, right: 12 });
            Flex.backgroundColor(this.isTouchDown && e.id === this.content.id ? this.touchDown : e.id === this.hoverId ? this.hoverBackgroundColor : "");
            Flex.width(this.clickRemoveBtn && e.id === this.content.id ? this.textItemEditWidth + 8 : this.textItemEditWidth);
            Flex.translate(this.gridComState ? this.clickRemoveBtn && e.id === this.content.id ? { x: 0 } : {
                x: -4
            } : { x: 0 });
            Flex.height("100%");
            Context.animation(null);
        }), Flex);
        this.observeComponentCreation2(((t, i) => {
            Image.create({
                id: -1,
                type: 2e4,
                params: ["sys.media.ohos_ic_public_add"],
                bundleName: "",
                moduleName: ""
            })
            Context.animation({ duration: 200, curve: COMMON_BEZIER });
            Image.width(12);
            Image.height(12);
            Image.draggable(!1);
            Image.fillColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_text_secondary"],
                bundleName: "",
                moduleName: ""
            });
            Image.visibility(this.clickRemoveBtn && e.id === this.content.id ? Visibility.Visible : Visibility.None);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            Image.margin({ right: 4 });
            Context.animation(null)
        }), Image);
        this.observeComponentCreation2(((t, i) => {
            Text.create(e.text);
            Text.fontColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_text_primary"],
                bundleName: "",
                moduleName: ""
            });
            Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_button3"],
                bundleName: "",
                moduleName: ""
            });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(1)
        }), Text);
        Text.pop();
        this.observeComponentCreation2(((t, i) => {
            Image.create({
                id: -1,
                type: 2e4,
                params: ["sys.media.ohos_ic_public_remove_filled"],
                bundleName: "",
                moduleName: ""
            });
            Context.animation({ duration: 200, curve: COMMON_BEZIER });
            Image.draggable(!1);
            Image.fillColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_secondary"],
                bundleName: "",
                moduleName: ""
            });
            Image.width(24);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            Image.scale(e.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon, centerX: "0" } : {
                centerX: "0"
            });
            Image.visibility(this.gridComState ? 0 : 1);
            Image.position({ x: this.blockWidth - 44, y: -8 });
            Image.translate(this.gridComState ? this.clickRemoveBtn && e.id === this.content.id ? { x: 8 } : {
                x: -8
            } : { x: 0 });
            Context.animation(null);
            Image.onClick((() => this.handleDeleteClick(e)))
        }), Image);
        Flex.pop();
        Stack.pop()
    }

    TextBlockAddItemBuilder(e, t = null) {
        this.observeComponentCreation2(((t, i) => {
            Stack.create();
            Stack.scale(e.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({ left: 8, right: 8 });
            Stack.height(28)
        }), Stack);
        this.observeComponentCreation2(((t, i) => {
            Row.create();
            Context.animation({ duration: 200, curve: COMMON_BEZIER });
            Row.borderRadius(50);
            Row.height("100%");
            Row.width(this.addIconShow && e.id === this.content.id ? this.textItemEditWidth : "100%");
            Row.translate(this.addIconShow && e.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Row.backgroundColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_button_normal"],
                bundleName: "",
                moduleName: ""
            })
        }), Row);
        Row.pop();
        this.observeComponentCreation2(((t, i) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
            Context.animation({ duration: 200, curve: COMMON_BEZIER });
            Flex.borderRadius(50);
            Flex.padding({ left: 12, right: 12 });
            Flex.backgroundColor(this.isTouchDown && e.id === this.content.id ? this.touchDown : e.id === this.hoverId ? this.hoverBackgroundColor : "");
            Flex.width(this.addIconShow && e.id === this.content.id ? this.textItemEditWidth : "100%");
            Flex.translate(this.addIconShow && e.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Flex.height("100%")
        }), Flex);
        this.observeComponentCreation2(((t, i) => {
            Image.create({
                id: -1,
                type: 2e4,
                params: ["sys.media.ohos_ic_public_add"],
                bundleName: "",
                moduleName: ""
            });
            Context.animation({ duration: 200, curve: COMMON_BEZIER });
            Image.draggable(!1);
            Image.fillColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_text_secondary"],
                bundleName: "",
                moduleName: ""
            });
            Image.width(12);
            Image.height(12);
            Image.visibility(this.addIconShow && e.id === this.content.id ? Visibility.None : Visibility.Visible);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            Image.margin({ right: 4 });
            Context.animation(null)
        }), Image);
        this.observeComponentCreation2(((t, i) => {
            Text.create(e.text);
            Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_button3"],
                bundleName: "",
                moduleName: ""
            });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(1)
        }), Text);
        Text.pop();
        this.observeComponentCreation2(((t, i) => {
            If.create();
            this.gridComState && this.addIconShow && e.id === this.content.id ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((e, t) => {
                    Image.create({
                        id: -1,
                        type: 2e4,
                        params: ["sys.media.ohos_ic_public_remove_filled"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.draggable(!1);
                    Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
                    Image.fillColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_secondary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.width(24);
                    Image.translate(this.gridComState ? { x: -8 } : {});
                    Image.position({ x: this.blockWidth - 44, y: -8 })
                }), Image)
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }))
        }), If);
        If.pop();
        Flex.pop();
        Stack.pop()
    }

    AddTagBuilder(e = null) {
        this.observeComponentCreation2(((e, t) => {
            Grid.create();
            Context.animation({ duration: 100, curve: Curve.Ease });
            Grid.columnsTemplate(this.customColumnsTemplate());
            Grid.padding({ left: 16, right: 16 });
            Grid.clip(!1);
            Grid.height(this.getGridHeight(ObservedObject.GetRawObject(this.unSelected)) + 120);
            Context.animation(null);
        }), Grid);
        this.observeComponentCreation2(((e, t) => {
            ForEach.create();
            this.forEachUpdateFunction(e, this.unSelected, ((e, t) => {
                const i = e;
                {
                    const e = (e, o) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e);
                        GridItem.create((() => {
                        }), !1);
                        Context.animation({ curve: REMOVE_ADD_SPRING, onFinish: () => {
                                i.id === this.content.id && this.clickAddBtn && console.log("animationOnFinish", t, JSON.stringify(i))
                            } });
                        GridItem.clip(!1);
                        GridItem.translate({
                            x: this.getUnSelectXY(ObservedObject.GetRawObject(this.unSelected), t, this.unSelectedIndex).x,
                            y: this.getUnSelectXY(ObservedObject.GetRawObject(this.unSelected), t, this.unSelectedIndex).y
                        });
                        Context.animation(null);
                        o || GridItem.pop();
                        ViewStackProcessor.StopGetAccessRecording()
                    };
                    const o = () => {
                        this.observeComponentCreation(e);
                        this.observeComponentCreation2(((e, t) => {
                            Stack.create();
                            Stack.onHover((e => {
                                this.hoverId = e ? i.id : ""
                            }));
                            Stack.margin({ bottom: this.imageText || this.gridComState ? 16 : 8 });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.onTouch((e => {
                                if (!this.clickAddBtn) {
                                    if (e.type === TouchType.Down) {
                                        this.content = i;
                                        this.isTouchDown = !0
                                    }
                                    if (e.type === TouchType.Up) {
                                        this.isTouchDown = !1;
                                        if (this.addAreaLongPressGesture || 1.05 === this.longScaleOnePointTwo || this.imageText) return;
                                        Context.animateTo({ duration: 200, curve: COMMON_BEZIER }, (() => {
                                            this.addIconShow = !0
                                        }));
                                        this.options.type === GridObjectSortComponentType.TEXT && (this.scaleAddIcon = 1);
                                        this.scaleIcon = 0;
                                        const e = this.unSelected.findIndex((e => e.id === i.id));
                                        this.editGridDataLength = this.selected.length + 1;
                                        const t = this.getEditItemGridPosition(ObservedObject.GetRawObject(this.selected), e);
                                        this.content = i;
                                        this.unSelectedIndex = e;
                                        this.endX = t.x;
                                        this.endY = t.y;
                                        this.clickAddBtn = !0;
                                        this.arrayUnSelectIsChange = 1;
                                        setTimeout((() => {
                                            this.scaleIcon = 1;
                                            this.scaleAddIcon = 0;
                                            this.selected.push(i);
                                            this.unSelected.splice(e, 1);
                                            this.arrayUnSelectIsChange = 2;
                                            this.endX = 0;
                                            this.endY = 0;
                                            this.gridComState || this.onSaveEdit();
                                            Context.animateTo({ duration: 200, curve: COMMON_BEZIER }, (() => {
                                                this.addIconShow = !1
                                            }));
                                            this.clickAddBtn = !1
                                        }), 500)
                                    }
                                }
                            }));
                            Gesture.create(GesturePriority.Low);
                            LongPressGesture.create({ repeat: !0 });
                            LongPressGesture.onAction((e => {
                                if (this.gridComState) Context.animateTo({
                                    duration: 200,
                                    curve: LONG_TOUCH_SCALE
                                }, (() => {
                                    this.longScaleOnePointTwo = 1.05
                                })); else {
                                    Context.animateTo({ duration: 200, curve: COMMON_BEZIER }, (() => {
                                        this.addAreaLongPressGesture = !0;
                                        this.gridComState = !0
                                    }));
                                    this.menuSwitch = !0
                                }
                            }));
                            LongPressGesture.onActionEnd((() => {
                                this.addAreaLongPressGesture = !1;
                                Context.animateTo({ duration: 200, curve: LONG_TOUCH_SCALE }, (() => {
                                    this.longScaleOnePointTwo = 1
                                }))
                            }));
                            LongPressGesture.pop();
                            Gesture.pop();
                        }), Stack);
                        this.observeComponentCreation2(((e, t) => {
                            If.create();
                            this.imageText ? this.ifElseBranchUpdateFunction(0, (() => {
                                this.ImageTextBuilder.bind(this)(i, "add")
                            })) : this.ifElseBranchUpdateFunction(1, (() => {
                                this.TextBlockAddItemBuilder.bind(this)(i)
                            }));
                        }), If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop()
                    };
                    o();
                }
            }), (e => e.id.toString()), !0, !1);
        }), ForEach);
        ForEach.pop();
        Grid.pop()
    }

    EditTagBuilder(e = null) {
        this.observeComponentCreation2(((e, t) => {
            Column.create();
        }), Column);
        this.observeComponentCreation2(((e, t) => {
            Grid.create();
            Context.animation({ duration: 100, curve: Curve.Ease });
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: !0 });
            LongPressGesture.onAction((e => {
                if (this.gridComState) {
                    Context.animateTo({ duration: 200, curve: LONG_TOUCH_SCALE }, (() => {
                        this.longScaleOnePointTwo = 1.05
                    }));
                    if (e.repeat && !this.vibrationDone) try {
                        vibrator.startVibration({ type: "time", duration: 1e3 }, {
                            id: 0,
                            usage: "alarm"
                        }).then((() => {
                            this.vibrationDone = !0
                        }))
                    } catch (e) {
                        this.vibrationDone = !1
                    }
                } else {
                    Context.animateTo({ duration: 200, curve: COMMON_BEZIER }, (() => {
                        this.gridComState = !0
                    }));
                    this.menuSwitch = !0
                }
            }));
            LongPressGesture.pop();
            Gesture.pop();
            Grid.clip(!1);
            Grid.editMode(this.gridComState);
            Grid.columnsTemplate(this.customColumnsTemplate());
            Grid.padding({ left: 16, right: 16 });
            Grid.height(this.getGridHeight(ObservedObject.GetRawObject(this.selected), "edit"));
            Context.animation(null);
            Grid.onItemDragStart(((e, t) => {
                this.selectedIndex = -1;
                if (this.gridComState) {
                    this.isStartDrag = !0;
                    this.selected.splice(t, 1);
                    this.editGridDataLength = this.selected.length + 1;
                    return { builder: () => {
                            this.PixelMapBuilder.call(this)
                    } }
                }
            }));
            Grid.onItemDrop(((e, t, i, o) => {
                if (this.gridComState) {
                    this.vibrationDone = !1;
                    Context.animateTo({ duration: 200, curve: LONG_TOUCH_SCALE }, (() => {
                        this.longScaleOnePointTwo = 1
                    }));
                    this.isStartDrag = !1;
                    this.selected.splice(-1 === i ? t : i, 0, ObservedObject.GetRawObject(this.content))
                }
            }));
            Grid.onItemDragMove(((e, t, i) => this.onDragMoveEvent(e, t, i)));
        }), Grid);
        this.observeComponentCreation2(((e, t) => {
            ForEach.create();
            this.forEachUpdateFunction(e, this.selected, ((e, t) => {
                const i = e;
                {
                    const e = (e, o) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e);
                        GridItem.create((() => {
                        }), !1)
                        Context.animation({ curve: this.isStartDrag ? DRAG_SPRING : REMOVE_ADD_SPRING });
                        GridItem.clip(!1);
                        GridItem.translate({
                            x: this.getXY(ObservedObject.GetRawObject(this.selected), t, this.selectedIndex).x,
                            y: this.getXY(ObservedObject.GetRawObject(this.selected), t, this.selectedIndex).y
                        });
                        Context.animation(null);
                        GridItem.onAreaChange(((e, o) => {
                            if (!this.isStartDrag) {
                                if (this.initPosition.some((e => e.id === i.id))) {
                                    const e = this.initPosition.findIndex((e => e.id === i.id));
                                    this.initPosition[e] = {
                                        id: i.id,
                                        globalPositionX: o.position.x,
                                        globalPositionY: o.position.y
                                    }
                                } else this.initPosition.push({
                                    id: i.id,
                                    globalPositionX: o.position.x,
                                    globalPositionY: o.position.y
                                })
                            }
                        }));
                        o || GridItem.pop();
                        ViewStackProcessor.StopGetAccessRecording()
                    };
                    (() => {
                        this.observeComponentCreation(e);
                        this.observeComponentCreation2(((e, t) => {
                            Stack.create();
                            Stack.onHover((e => {
                                this.hoverId = e ? i.id : ""
                            }));
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.clip(!1);
                            Stack.margin({ bottom: this.imageText || this.gridComState ? 16 : 8 });
                            Stack.onTouch((e => {
                                if (e.type === TouchType.Down) {
                                    this.content = i;
                                    this.isTouchDown = !0
                                }
                                if (e.type === TouchType.Up) {
                                    this.isTouchDown = !1;
                                    Context.animateTo({ duration: 200, curve: LONG_TOUCH_SCALE }, (() => {
                                        this.longScaleOnePointTwo = 1
                                    }))
                                }
                            }));
                        }), Stack);
                        this.observeComponentCreation2(((e, t) => {
                            If.create();
                            this.imageText ? this.ifElseBranchUpdateFunction(0, (() => {
                                this.ImageTextBuilder.bind(this)(i, "delete")
                            })) : this.ifElseBranchUpdateFunction(1, (() => {
                                this.TextBlockBuilder.bind(this)(i)
                            }));
                        }), If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop()
                    })();
                }
            }), (e => e.id.toString()), !0, !1);
        }), ForEach);
        ForEach.pop();
        Grid.pop();
        Column.pop()
    }

    initialRender() {
        this.observeComponentCreation2(((e, t) => {
            Column.create();
            Column.width("100%");
            Column.height("90%");
        }), Column);
        this.HeaderTitleBuilder.bind(this)();
        this.observeComponentCreation2(((e, t) => {
            Scroll.create();
        }), Scroll);
        this.observeComponentCreation2(((e, t) => {
            Column.create();
            Column.onAreaChange(((e, t) => {
                this.areaWidth = Number(t.width);
                this.blockWidth = this.getBlockWidth();
                this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
                this.imageItemWidth = this.blockWidth - 16;
                this.blockHeight = this.imageText ? this.imageItemWidth + 16 : this.gridComState ? 44 : 36;
            }));
            Column.width("100%");
        }), Column);
        this.observeComponentCreation2(((e, t) => {
            __Common__.create();
            __Common__.margin({ bottom: 8 })
        }), __Common__);
        this.observeComponentCreation2(((e, t) => {
            if (t) {
                let t = () => ({
                    secondaryTitle: this.options.showAreaTitle || {
                        id: -1,
                        type: 10003,
                        params: ["sys.string.ohos_grid_edit_subtitle_sort"],
                        bundleName: "",
                        moduleName: ""
                    }
                });
                ViewPU.create(new SubHeader(this, {
                    secondaryTitle: this.options.showAreaTitle || {
                        id: -1,
                        type: 10003,
                        params: ["sys.string.ohos_grid_edit_subtitle_sort"],
                        bundleName: "",
                        moduleName: ""
                    }
                }, void 0, e, t))
            } else this.updateStateVarsOfChildByElmtId(e, {
                secondaryTitle: this.options.showAreaTitle || {
                    id: -1,
                    type: 10003,
                    params: ["sys.string.ohos_grid_edit_subtitle_sort"],
                    bundleName: "",
                    moduleName: ""
                }
            })
        }), null)
        __Common__.pop();
        this.EditTagBuilder.bind(this)();
        this.observeComponentCreation2(((e, t) => {
            __Common__.create();
            __Common__.margin({ bottom: 8 })
        }), __Common__);
        this.observeComponentCreation2(((e, t) => {
            if (t) {
                let t = () => ({
                    secondaryTitle: this.options.addAreaTitle || {
                        id: -1,
                        type: 10003,
                        params: ["sys.string.ohos_grid_edit_subtitle_add"],
                        bundleName: "",
                        moduleName: ""
                    }
                });
                ViewPU.create(new SubHeader(this, {
                    secondaryTitle: this.options.addAreaTitle || {
                        id: -1,
                        type: 10003,
                        params: ["sys.string.ohos_grid_edit_subtitle_add"],
                        bundleName: "",
                        moduleName: ""
                    }
                }, void 0, e, t))
            } else this.updateStateVarsOfChildByElmtId(e, {
                secondaryTitle: this.options.addAreaTitle || {
                    id: -1,
                    type: 10003,
                    params: ["sys.string.ohos_grid_edit_subtitle_add"],
                    bundleName: "",
                    moduleName: ""
                }
            })
        }), null)
        __Common__.pop();
        this.AddTagBuilder.bind(this)();
        Column.pop();
        Scroll.pop();
        Column.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

export default {
    GridObjectSortComponent, GridObjectSortComponentType
}