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

const vibrator = requireNativeModule('ohos.vibrator')
const curves = requireNativeModule('ohos.curves')

const composetitlebar = requireNapi('arkui.advanced.composetitlebar');
const editabletitlebar = requireNapi('arkui.advanced.editabletitlebar');
const subheader = requireNapi('arkui.advanced.subheader');
const ComposeTitleBar = composetitlebar.ComposeTitleBar
const EditableTitleBar = editabletitlebar.EditableTitleBar
const EditableLeftIconType = editabletitlebar.EditableLeftIconType
const SubHeader = subheader.SubHeader

const COL_IMAGE_TEXT = 3;
const COL_TEXT = 4;
const BLOCK_TEXT_HEIGHT = 46;
const BLOCK_IMAGE_TEXT_HEIGHT = 124;
const ROW_GAP = 16;
const DURATION = 300;
const ICON_SIZE = 24;
const IMAGE_DEFAULT = 56;
const TEXT_PADDING_LEFT_RIGHT = 12;
const COMMON_BEZIER = curves.cubicBezierCurve(.33, 0, .67, 1);

export var GridObjectSortComponentType;
!function(e){
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

function __Text__blockTextStyle(e = 65) {
    Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_primary"],
        bundleName: "",
        moduleName: ""
    });
    Text.backgroundColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_button_normal"],
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
    Text.maxLines(1);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.height(28);
    Text.width(e);
    Text.textAlign(TextAlign.Center);
    Text.borderRadius(50);
    Text.padding({ left: 12, right: 12 })
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
        this.__gridComState = new ObservedPropertySimplePU(!1, this, "gridComState");
        this.__areaWidth = new ObservedPropertySimplePU(0, this, "areaWidth");
        this.__blockWidth = new ObservedPropertySimplePU(0, this, "blockWidth");
        this.__blockHeight = new ObservedPropertySimplePU(this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? 124 : 46, this, "blockHeight");
        this.__longScaleOnePointTwo = new ObservedPropertySimplePU(1, this, "longScaleOnePointTwo");
        this.__scaleGridItemNinetyPercent = new ObservedPropertySimplePU(1, this, "scaleGridItemNinetyPercent");
        this.__scaleAddItemNinetyPercent = new ObservedPropertySimplePU(1, this, "scaleAddItemNinetyPercent");
        this.__scaleIcon = new ObservedPropertySimplePU(1, this, "scaleIcon");
        this.__addIconShow = new ObservedPropertySimplePU(!1, this, "addIconShow");
        this.__scaleAddIcon = new ObservedPropertySimplePU(0, this, "scaleAddIcon");
        this.__isStartDrag = new ObservedPropertySimplePU(!1, this, "isStartDrag");
        this.__dragNextID = new ObservedPropertySimplePU(0, this, "dragNextID");
        this.__insertIndex = new ObservedPropertySimplePU(-1, this, "insertIndex");
        this.__editGridDataLength = new ObservedPropertySimplePU(-1, this, "editGridDataLength");
        this.__isTouchDown = new ObservedPropertySimplePU(!1, this, "isTouchDown");
        this.__endX = new ObservedPropertySimplePU(0, this, "endX");
        this.__endY = new ObservedPropertySimplePU(0, this, "endY");
        this.__unSelectedIndex = new ObservedPropertySimplePU(0, this, "unSelectedIndex");
        this.__selectedIndex = new ObservedPropertySimplePU(-1, this, "selectedIndex");
        this.__clickAddBtn = new ObservedPropertySimplePU(!1, this, "clickAddBtn");
        this.__gridHeight = new ObservedPropertySimplePU(0, this, "gridHeight");
        this.__clickRemoveBtn = new ObservedPropertySimplePU(!1, this, "clickRemoveBtn");
        this.__addAreaLongPressGesture = new ObservedPropertySimplePU(!1, this, "addAreaLongPressGesture");
        this.colNum = this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? 3 : 4;
        this.arraySelectIsChange = 0;
        this.arrayUnSelectIsChange = 0;
        this.vibrationDone=!1;
        this.touchDown = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
        };
        this.touchDownBg = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_hover"],
            bundleName: "",
            moduleName: ""
        };
        this.scroller = new Scroller;
        this.onSave = void 0;
        this.onCancel = void 0;
        this.menuItems = [new MenuItem({
            id: -1,
            type: 2e4,
            params: ["sys.media.ohos_ic_public_edit"],
            bundleName: "",
            moduleName: ""
        },!0, (() => {
            this.goEdit()
        }))];
        this.setInitiallyProvidedValue(t)
    }

    setInitiallyProvidedValue(e) {
        void 0 === e.options && this.__options.set({});
        void 0 !== e.dataList && (this.dataList = e.dataList);
        void 0 !== e.selected && (this.selected = e.selected);
        void 0 !== e.unSelected && (this.unSelected = e.unSelected);
        void 0 !== e.copySelected && (this.copySelected = e.copySelected);
        void 0 !== e.copyUnSelected && (this.copyUnSelected = e.copyUnSelected);
        void 0 !== e.content && (this.content = e.content);
        void 0 !== e.gridComState && (this.gridComState = e.gridComState);
        void 0 !== e.areaWidth && (this.areaWidth = e.areaWidth);
        void 0 !== e.blockWidth && (this.blockWidth = e.blockWidth);
        void 0 !== e.blockHeight && (this.blockHeight = e.blockHeight);
        void 0 !== e.longScaleOnePointTwo && (this.longScaleOnePointTwo = e.longScaleOnePointTwo);
        void 0 !== e.scaleGridItemNinetyPercent && (this.scaleGridItemNinetyPercent = e.scaleGridItemNinetyPercent);
        void 0 !== e.scaleAddItemNinetyPercent && (this.scaleAddItemNinetyPercent = e.scaleAddItemNinetyPercent);
        void 0 !== e.scaleIcon && (this.scaleIcon = e.scaleIcon);
        void 0 !== e.addIconShow && (this.addIconShow = e.addIconShow);
        void 0 !== e.scaleAddIcon && (this.scaleAddIcon = e.scaleAddIcon);
        void 0 !== e.isStartDrag && (this.isStartDrag = e.isStartDrag);
        void 0 !== e.dragNextID && (this.dragNextID = e.dragNextID);
        void 0 !== e.insertIndex && (this.insertIndex = e.insertIndex);
        void 0 !== e.editGridDataLength && (this.editGridDataLength = e.editGridDataLength);
        void 0 !== e.isTouchDown && (this.isTouchDown = e.isTouchDown);
        void 0 !== e.endX && (this.endX = e.endX);
        void 0 !== e.endY && (this.endY = e.endY);
        void 0 !== e.unSelectedIndex && (this.unSelectedIndex = e.unSelectedIndex);
        void 0 !== e.selectedIndex && (this.selectedIndex = e.selectedIndex);
        void 0 !== e.clickAddBtn && (this.clickAddBtn = e.clickAddBtn);
        void 0 !== e.gridHeight && (this.gridHeight = e.gridHeight);
        void 0 !== e.clickRemoveBtn && (this.clickRemoveBtn = e.clickRemoveBtn);
        void 0 !== e.addAreaLongPressGesture && (this.addAreaLongPressGesture = e.addAreaLongPressGesture);
        void 0 !== e.colNum && (this.colNum = e.colNum);
        void 0 !== e.arraySelectIsChange && (this.arraySelectIsChange = e.arraySelectIsChange);
        void 0 !== e.arrayUnSelectIsChange && (this.arrayUnSelectIsChange = e.arrayUnSelectIsChange);
        void 0 !== e.vibrationDone && (this.vibrationDone = e.vibrationDone);
        void 0 !== e.touchDown && (this.touchDown = e.touchDown);
        void 0 !== e.touchDownBg && (this.touchDownBg = e.touchDownBg);
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
        this.__gridComState.purgeDependencyOnElmtId(e);
        this.__areaWidth.purgeDependencyOnElmtId(e);
        this.__blockWidth.purgeDependencyOnElmtId(e);
        this.__blockHeight.purgeDependencyOnElmtId(e);
        this.__longScaleOnePointTwo.purgeDependencyOnElmtId(e);
        this.__scaleGridItemNinetyPercent.purgeDependencyOnElmtId(e);
        this.__scaleAddItemNinetyPercent.purgeDependencyOnElmtId(e);
        this.__scaleIcon.purgeDependencyOnElmtId(e);
        this.__addIconShow.purgeDependencyOnElmtId(e);
        this.__scaleAddIcon.purgeDependencyOnElmtId(e);
        this.__isStartDrag.purgeDependencyOnElmtId(e);
        this.__dragNextID.purgeDependencyOnElmtId(e);
        this.__insertIndex.purgeDependencyOnElmtId(e);
        this.__editGridDataLength.purgeDependencyOnElmtId(e);
        this.__isTouchDown.purgeDependencyOnElmtId(e);
        this.__endX.purgeDependencyOnElmtId(e);
        this.__endY.purgeDependencyOnElmtId(e);
        this.__unSelectedIndex.purgeDependencyOnElmtId(e);
        this.__selectedIndex.purgeDependencyOnElmtId(e);
        this.__clickAddBtn.purgeDependencyOnElmtId(e);
        this.__gridHeight.purgeDependencyOnElmtId(e);
        this.__clickRemoveBtn.purgeDependencyOnElmtId(e);
        this.__addAreaLongPressGesture.purgeDependencyOnElmtId(e);
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__selected.aboutToBeDeleted();
        this.__unSelected.aboutToBeDeleted();
        this.__copySelected.aboutToBeDeleted();
        this.__copyUnSelected.aboutToBeDeleted();
        this.__content.aboutToBeDeleted();
        this.__gridComState.aboutToBeDeleted();
        this.__areaWidth.aboutToBeDeleted();
        this.__blockWidth.aboutToBeDeleted();
        this.__blockHeight.aboutToBeDeleted();
        this.__longScaleOnePointTwo.aboutToBeDeleted();
        this.__scaleGridItemNinetyPercent.aboutToBeDeleted();
        this.__scaleAddItemNinetyPercent.aboutToBeDeleted();
        this.__scaleIcon.aboutToBeDeleted();
        this.__addIconShow.aboutToBeDeleted();
        this.__scaleAddIcon.aboutToBeDeleted();
        this.__isStartDrag.aboutToBeDeleted();
        this.__dragNextID.aboutToBeDeleted();
        this.__insertIndex.aboutToBeDeleted();
        this.__editGridDataLength.aboutToBeDeleted();
        this.__isTouchDown.aboutToBeDeleted();
        this.__endX.aboutToBeDeleted();
        this.__endY.aboutToBeDeleted();
        this.__unSelectedIndex.aboutToBeDeleted();
        this.__selectedIndex.aboutToBeDeleted();
        this.__clickAddBtn.aboutToBeDeleted();
        this.__gridHeight.aboutToBeDeleted();
        this.__clickRemoveBtn.aboutToBeDeleted();
        this.__addAreaLongPressGesture.aboutToBeDeleted();
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

    get gridComState() {
        return this.__gridComState.get()
    }

    set gridComState(e) {
        this.__gridComState.set(e)
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

    get scaleAddItemNinetyPercent() {
        return this.__scaleAddItemNinetyPercent.get()
    }

    set scaleAddItemNinetyPercent(e) {
        this.__scaleAddItemNinetyPercent.set(e)
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

    get dragNextID() {
        return this.__dragNextID.get()
    }

    set dragNextID(e) {
        this.__dragNextID.set(e)
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

    get selectedIndex() {
        return this.__selectedIndex.get()
    }

    set selectedIndex(e) {
        this.__selectedIndex.set(e)
    }

    get clickAddBtn() {
        return this.__clickAddBtn.get()
    }

    set clickAddBtn(e) {
        this.__clickAddBtn.set(e)
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

    sortBy() {
        return (e, t) => e.order - t.order
    }

    aboutToAppear() {
        this.dataList.length = 50;
        this.selected = this.dataList && this.dataList.filter((e => e.selected)).sort(this.sortBy());
        this.unSelected = this.dataList && this.dataList.filter((e =>!e.selected)).sort(this.sortBy());
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        this.editGridDataLength = this.selected.length;
    }

    cancelEdit() {
        this.longScaleOnePointTwo = 1;
        this.scaleGridItemNinetyPercent = 1;
        Context.animateTo({ duration: 300 }, (() => {
            this.gridComState = !1
        }));
        this.selected = this.copySelected.slice();
        this.unSelected = this.copyUnSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.onCancel && this.onCancel()
    }

    goEdit() {
        this.scaleGridItemNinetyPercent = .9;
        Context.animateTo({ duration: 300 }, (() => {
            this.gridComState = !0
        }))
    }

    onSaveEdit() {
        this.longScaleOnePointTwo = 1;
        this.scaleGridItemNinetyPercent = 1;
        this.editGridDataLength = this.selected.length;
        Context.animateTo({ duration: 300 }, (() => {
            this.gridComState = !1
        }));
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        const e = this.getNewData(this.selected,!0, 0);
        const t = this.getNewData(this.unSelected,!1, this.selected.length);
        this.selected = e;
        this.unSelected = t;
        this.onSave && this.onSave(e, t)
    }

    aboutToDisappear() {
        Context.animateTo({ duration: 300 }, (() => {
            this.gridComState = !1
        }));
        this.selected = this.copySelected;
        this.unSelected = this.copyUnSelected
    }

    customColumnsTemplate() {
        let e = "1fr 1fr 1fr 1fr";
        this.options.type === GridObjectSortComponentType.IMAGE_TEXT && (e = "1fr 1fr 1fr");
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
        return (this.areaWidth - 36 - 48) / 4
    }

    getImageBlockWidth() {
        const e = (this.areaWidth - 36 - 32) / 3;
        return Math.trunc(e)
    }

    getEditItemGridPosition(e, t) {
        const i = e.length;
        const o = this.colNum;
        const s = Math.trunc(i % o);
        const n = Math.trunc(t % o);
        const d = s;
        let r = Math.abs(d - n) * (this.blockWidth + 14);
        d < n ? r = -r : d > n || (r = 0);
        let a = 0;
        a = (Math.trunc(t / this.colNum) + 1) * this.blockHeight + 57;
        return { x: r, y: a }
    }

    getAddItemGridPosition(e, t) {
        const i = e.length;
        const o = this.colNum;
        const s = Math.trunc(i % o);
        const n = Math.trunc(t % o);
        const d = s;
        let r = Math.abs(d - n) * (this.blockWidth + 14);
        d < n ? r = -r : d > n || (r = 0);
        let a = 0;
        let l = Math.trunc(t / this.colNum);
        const c = i % o == 0 ? 0 : 1;
        let h = Math.trunc(i / this.colNum) + c;
        const m = this.selected.length;
        const p = m % o == 0 ? 0 : 1;
        let u = Math.trunc(m / this.colNum) + p;
        a = 0 === s ? (h + (u - l)) * this.blockHeight + 48 : (h - 1 + (u - l)) * this.blockHeight + 48;
        return { x: r, y: a }
    }

    getCoveringGridPosition(e, t, i) {
        const o = e.length;
        let s = 0;
        let n = 0;
        if (t > i) if (i === o - 1) {
            s = 0;
            n = 0
        } else if (2 !== this.arraySelectIsChange) {
            s = t % this.colNum == 0 ? (this.blockWidth + 16) * (this.colNum - 1) : -this.blockWidth - 14;
            n = t % this.colNum == 0 ? -this.blockHeight : 0
        }
        return { x: s, y: n }
    }

    onDragMoveEvent(e, t, i) {
        var o;
        if (!this.gridComState || e.x < this.blockWidth / 3 && e.y < this.blockHeight / 3) return;
        let s = i;
        i < 0 && (s = this.selected.length - 1);
        this.insertIndex = i;
        this.dragNextID = null === (o = this.selected[i]) || void 0 === o ? void 0 : o.id
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
        }), 300)
    }

    getCoodXY(e) {
        const t = this.colNum;
        let i = 0;
        let o = 0;
        if (e >= this.insertIndex) if (Math.trunc(e % t) === t - 1) {
            i = i - this.blockWidth * (t - 1) - 12 * (t - 1);
            o += this.blockHeight
        } else i = i + this.blockWidth + 12;
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
        i = this.blockHeight * n + 8;
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
            o = this.getAddItemGridPosition(this.unSelected, i).x
            s = this.getAddItemGridPosition(this.unSelected, i).y
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
            s = t % this.colNum == 0 ? (this.blockWidth + 16) * (this.colNum - 1) : -this.blockWidth - 14;
            n = t % this.colNum == 0 ? -this.blockHeight : 0;
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
            Stack.create();
            Stack.padding({ top: this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? 12 : 6, right: 6 });
            Stack.clip(!1)
        }), Stack);
        this.observeComponentCreation2(((e, t) => {
            If.create();
                this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((e, t) => {
                    Stack.create();
                    Stack.width(this.blockWidth * this.longScaleOnePointTwo + 2);
                    Stack.height(this.blockWidth * this.longScaleOnePointTwo + 2);
                    Stack.clip(!1)
                }), Stack);
                this.ImageTextBuilder.bind(this)(ObservedObject.GetRawObject(this.content), "delete", "pixe");
                Stack.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
                this.observeComponentCreation2(((e, t) => {
                    Stack.create();
                    Stack.clip(!1);
                    Stack.height(28 * this.longScaleOnePointTwo)
                }), Stack);
                this.observeComponentCreation2(((e, t) => {
                    Text.create(this.content.text);
                    __Text__blockTextStyle(this.blockWidth);
                    Text.fontSize(14);
                    Text.width(this.blockWidth);
                    Text.height(28)
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
                    Image.fillColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_secondary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.width(24);
                    Image.height(24);
                    Image.position({ x: this.blockWidth * this.longScaleOnePointTwo - 32, y: -6 })
                }), Image);
                Stack.pop()
            }))
        }), If);
        If.pop();
        Stack.pop()
    }

    HeaderTitleBuilder(e = null) {
        this.observeComponentCreation2(((e, t) => {
            Stack.create()
        }), Stack);
        this.observeComponentCreation2(((e, t) => {
            If.create();
            this.gridComState ? this.ifElseBranchUpdateFunction(1, (() => {
                this.observeComponentCreation2(((e, t) => {
                    if (t) {
                        let t = () => ({
                            leftIconStyle: EditableLeftIconType.Cancel,
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
                                this.onSaveEdit()
                            }
                        });
                        ViewPU.create(new EditableTitleBar(this, {
                            leftIconStyle: EditableLeftIconType.Cancel,
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
                                this.onSaveEdit()
                            }
                        }, void 0, e, t))
                    } else this.updateStateVarsOfChildByElmtId(e, {})
                }), null)
            })) : this.ifElseBranchUpdateFunction(0, (() => {
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
                }), null)
            }))
        }), If);
        If.pop();
        Stack.pop()
    }

    ImageTextBuilder(e, t, i, o = null) {
        this.observeComponentCreation2(((t, i) => {
            Flex.create({
                direction: FlexDirection.Column,
                justifyContent: FlexAlign.Center,
                alignItems: ItemAlign.Center
            });
            Context.animation({ duration: 500, curve: curves.springCurve(10, 1, 410, 38) });
            Flex.backgroundColor(this.isTouchDown && e.id === this.content.id ? this.touchDown : "");
            Flex.colorBlend(this.isTouchDown && e.id === this.content.id ? this.touchDownBg : "");
            Flex.scale(e.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Context.animation(null);
            Flex.clip(!1);
            Flex.width(this.blockWidth);
            Flex.height(this.blockWidth);
            Flex.zIndex(999);
            Flex.padding({ top: 12, bottom: 8 })
        }), Flex);
        this.observeComponentCreation2(((t, o) => {
            If.create();
                i || e.id === this.content.id ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((t, i) => {
                    Image.create(e.url);
                    Image.draggable(!1);
                    Image.height(56);
                    Image.width(56);
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
                    Text.textAlign(TextAlign.Center);
                    Text.width(this.blockWidth * this.longScaleOnePointTwo);
                    Text.padding({ top: 2, left: 12, right: 12 });
                    Text.maxLines(1);
                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    Text.textAlign(TextAlign.Center)
                }), Text);
                Text.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
                this.observeComponentCreation2(((t, i) => {
                    Image.create(e.url);
                    Image.draggable(!1);
                    Image.height(this.options.imageSize || 56);
                    Image.width(this.options.imageSize || 56);
                }), Image);
                this.observeComponentCreation2(((t, i) => {
                    Text.create(e.text);
                    Text.textAlign(TextAlign.Center);
                    Text.width(this.blockWidth);
                    Text.fontSize({
                        id: -1,
                        type: 10002,
                        params: ["sys.float.ohos_id_text_size_button3"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.padding({ top: 2, left: 12, right: 12 });
                    Text.maxLines(1);
                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                    Text.textAlign(TextAlign.Center)
                }), Text);
                Text.pop()
            }))
        }), If);
        If.pop();
        this.observeComponentCreation2(((i, o) => {
            If.create();
                "add" === t ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((t, i) => {
                    Image.create({
                        id: -1,
                        type: 2e4,
                        params: ["sys.media.ohos_ic_public_add_norm_filled"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Context.animation({ duration: 300, curve: Curve.Linear, iterations: 1, playMode: PlayMode.Normal });
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
                    Image.position({ x: this.blockWidth - 16, y: -18 });
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
                        }), 300)
                    }));
                }), Image)
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }))
        }), If);
        If.pop();
        this.observeComponentCreation2(((o, s) => {
            Image.create({
                id: -1,
                type: 2e4,
                params: ["sys.media.ohos_ic_public_remove_filled"],
                bundleName: "",
                moduleName: ""
            });
            Context.animation({ duration: 300, curve: Curve.Linear, iterations: 1, playMode: PlayMode.Normal });
            Image.fillColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_secondary"],
                bundleName: "",
                moduleName: ""
            });
            Image.visibility("delete" === t && this.gridComState ? 0 : 1);
            Image.width(24);
            Image.height(24);
            Image.opacity("delete" === t && this.gridComState ? 1 : 0);
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            Image.position({ x: i && e.id === this.content.id ? this.blockWidth - 17 : this.blockWidth - 16, y: -18 });
            Context.animation(null);
            Image.onClick((() => this.handleDeleteClick(e)))
        }), Image);
        Flex.pop()
    }

    TextBlockBuilder(e, t, i = null) {
        this.observeComponentCreation2(((t, i) => {
            Stack.create();
            Context.animation({
                duration: 500,
                curve: curves.springCurve(10, 1, 410, 38),
                iterations: 1,
                playMode: PlayMode.Normal
            });
            Stack.scale(e.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Context.animation(null);
            Stack.height(28)
        }), Stack);
        this.observeComponentCreation2(((t, i) => {
            Text.create(e.text);
            Context.animation({
                duration: 250,
                curve: curves.springCurve(0, 1, 400, 38),
                iterations: 1,
                playMode: PlayMode.Normal
            });
            __Text__blockTextStyle(this.blockWidth);
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.backgroundColor(this.isTouchDown && e.id === this.content.id ? this.touchDown : {
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_button_normal"],
                bundleName: "",
                moduleName: ""
            });
            Text.colorBlend(this.isTouchDown && e.id === this.content.id ? this.touchDownBg : "");
            Text.scale(this.gridComState ? { x: this.scaleGridItemNinetyPercent, centerX: 0 } : { 
                x: this.scaleGridItemNinetyPercent 
            });
            Context.animation(null);
        }), Text);
        Text.pop();
        this.observeComponentCreation2(((i, o) => {
            Image.create({
                id: -1,
                type: 2e4,
                params: ["sys.media.ohos_ic_public_remove_filled"],
                bundleName: "",
                moduleName: ""
            });
            Context.animation({ duration: 250, curve: COMMON_BEZIER, iterations: 1, playMode: PlayMode.Normal });
            Image.transition({ type: TransitionType.All, scale: { x: 0, y: 0, centerX: 10, centerY: 16 } });
            Image.scale(e.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {});
            Image.visibility("delete" === t && this.gridComState ? 0 : 1);
            Image.fillColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_secondary"],
                bundleName: "",
                moduleName: ""
            });
            Image.width(24);
            Image.position({
                x: "delete" === t && this.gridComState ? this.blockWidth * this.scaleGridItemNinetyPercent - 16 : this.blockWidth - 16,
                y: "delete" === t && this.gridComState ? -5 : -8
            });
            Context.animation(null);
            Image.onClick((() => this.handleDeleteClick(e)))
        }), Image);
        Stack.pop()
    }

    AddTagBuilder(e = null) {
        this.observeComponentCreation2(((e, t) => {
            Grid.create();
            Grid.columnsTemplate(this.customColumnsTemplate());
            Grid.padding({ top: 8, left: 16, right: 16 });
            Grid.clip(!1);
            Grid.height(this.getGridHeight(ObservedObject.GetRawObject(this.unSelected)) + 120)
        }), Grid);
        this.observeComponentCreation2(((e, t) => {
            ForEach.create();
            this.forEachUpdateFunction(e, this.unSelected, ((e, t) => {
                const i = e;
                {
                    const e = (e, i) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e);
                        GridItem.create((() => {
                        }),!1);
                        Context.animation({
                            duration: 300,
                            curve: curves.springCurve(0, 1, 150, 24),
                            iterations: 1,
                            playMode: PlayMode.Normal
                        });
                        GridItem.clip(!1);
                        GridItem.padding({ left: 8, right: 8 });
                        GridItem.translate({
                            x: this.getUnSelectXY(ObservedObject.GetRawObject(this.unSelected), t, this.unSelectedIndex).x,
                            y: this.getUnSelectXY(ObservedObject.GetRawObject(this.unSelected), t, this.unSelectedIndex).y
                        });
                        Context.animation(null);
                        i || GridItem.pop();
                        ViewStackProcessor.StopGetAccessRecording()
                    };
                    const o = () => {
                        this.observeComponentCreation(e);
                        this.observeComponentCreation2(((e, t) => {
                            Stack.create();
                            Context.animation({
                                duration: 300,
                                curve: curves.springCurve(0, 1, 150, 24),
                                iterations: 1,
                                playMode: PlayMode.Normal
                            });
                            Stack.scale(this.isTouchDown && i.id === this.content.id ? {
                                x: this.scaleAddItemNinetyPercent,
                                y: this.scaleAddItemNinetyPercent
                            } : { x: 1, y: 1 });
                            Context.animation(null);
                            Stack.margin({ top: 2, bottom: 16 });
                            Stack.onTouch((e => {
                                if (e.type === TouchType.Down) {
                                    this.content = i;
                                    this.isTouchDown = !0;
                                    this.scaleAddItemNinetyPercent = .9
                                }
                                if (e.type === TouchType.Up) {
                                    this.isTouchDown = !1;
                                    this.scaleAddItemNinetyPercent = 1;
                                    if (this.clickAddBtn || this.addAreaLongPressGesture || !this.gridComState && this.options.type === GridObjectSortComponentType.IMAGE_TEXT) return;
                                    Context.animateTo({ duration: 300, curve: COMMON_BEZIER }, (() => {
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
                                        this.clickAddBtn = !1;
                                        this.gridComState || this.onSaveEdit();
                                        Context.animateTo({ duration: 300, curve: COMMON_BEZIER }, (() => {
                                            this.addIconShow = !1
                                        }))
                                    }), 300)
                                }
                            }));
                            Gesture.create(GesturePriority.Low);
                            LongPressGesture.create({ repeat: !0 });
                            LongPressGesture.onAction((e => {
                                this.gridComState || Context.animateTo({ duration: 300 }, (() => {
                                    this.addAreaLongPressGesture = !0
                                    this.gridComState = !0
                                }))
                            }));
                            LongPressGesture.onActionEnd((()=>{
                                this.addAreaLongPressGesture = !1
                            }));
                            LongPressGesture.pop();
                            Gesture.pop()
                        }), Stack);
                        this.observeComponentCreation2(((e, t) => {
                            If.create();
                                this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? this.ifElseBranchUpdateFunction(0, (() => {
                                this.ImageTextBuilder.bind(this)(i, "add")
                            })) : this.ifElseBranchUpdateFunction(1, (() => {
                                this.observeComponentCreation2(((e, t) => {
                                    Flex.create({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center });
                                    Flex.backgroundColor(this.isTouchDown && i.id === this.content.id ? this.touchDown : {
                                        id: -1,
                                        type: 10001,
                                        params: ["sys.color.ohos_id_color_button_normal"],
                                        bundleName: "",
                                        moduleName: ""
                                    });
                                    Flex.borderRadius(50);
                                    Flex.width(this.blockWidth);
                                    Flex.height(28);
                                    Flex.padding({ left: 12, right: 12 })
                                }), Flex);
                                this.observeComponentCreation2(((e, t) => {
                                    If.create();
                                    this.addIconShow && i.id === this.content.id ? this.ifElseBranchUpdateFunction(1, (() => {
                                    })) : this.ifElseBranchUpdateFunction(0, (() => {
                                        this.observeComponentCreation2(((e, t) => {
                                            Image.create({
                                                id: -1,
                                                type: 2e4,
                                                params: ["sys.media.ohos_ic_public_add"],
                                                bundleName: "",
                                                moduleName: ""
                                            });
                                            Image.fillColor({
                                                id: -1,
                                                type: 10001,
                                                params: ["sys.color.ohos_id_color_text_secondary"],
                                                bundleName: "",
                                                moduleName: ""
                                            });
                                            Image.width(16);
                                            Image.margin({ right: 4 })
                                        }), Image)
                                    }))
                                }), If);
                                If.pop();
                                this.observeComponentCreation2(((e, t) => {
                                    Text.create(i.text);
                                    Text.fontSize({
                                        id: -1,
                                        type: 10002,
                                        params: ["sys.float.ohos_id_text_size_button3"],
                                        bundleName: "",
                                        moduleName: ""
                                    });
                                    Text.width(this.blockWidth - 24);
                                    Text.maxLines(1);
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                    Text.textAlign(TextAlign.Center);
                                    Text.height("100%")
                                }), Text);
                                Text.pop();
                                this.observeComponentCreation2(((e, t) => {
                                    If.create();
                                        this.gridComState && this.addIconShow && i.id === this.content.id ? this.ifElseBranchUpdateFunction(0, (() => {
                                        this.observeComponentCreation2(((e, t) => {
                                            Image.create({
                                                id: -1,
                                                type: 2e4,
                                                params: ["sys.media.ohos_ic_public_remove_filled"],
                                                bundleName: "",
                                                moduleName: ""
                                            });
                                            Image.transition({ scale: { x: 0, y: 0 } });
                                            Image.fillColor({
                                                id: -1,
                                                type: 10001,
                                                params: ["sys.color.ohos_id_color_secondary"],
                                                bundleName: "",
                                                moduleName: ""
                                            });
                                            Image.width(24);
                                            Image.position({ x: this.blockWidth - 32, y: -4 })
                                        }), Image)
                                    })) : this.ifElseBranchUpdateFunction(1, (() => {
                                    }))
                                }), If);
                                If.pop();
                                Flex.pop()
                            }))
                        }), If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop()
                    };
                    o()
                }
            }), void 0,!0,!1)
    }), ForEach);
        ForEach.pop();
        Grid.pop()
    }

    EditTagBuilder(e = null) {
        this.observeComponentCreation2(((e, t) => {
            Grid.create();
            Context.animation({ duration: 100, curve: Curve.Ease });
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: !0 });
            LongPressGesture.onAction((e => {
                if (this.gridComState) {
                    this.longScaleOnePointTwo = 1.2;
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
                    this.scaleGridItemNinetyPercent = .9;
                    Context.animateTo({ duration: 300 }, (() => {
                        this.gridComState = !0
                    }))
                }
            }));
            LongPressGesture.pop();
            Gesture.pop();
            Grid.clip(!1);
            Grid.editMode(this.gridComState);
            Grid.columnsTemplate(this.customColumnsTemplate());
            Grid.padding({ left: 16, right: 16, top: 8 });
            Grid.height(0 === this.selected.length && this.clickAddBtn ? this.blockHeight + 8 : this.getGridHeight(ObservedObject.GetRawObject(this.selected), "edit"));
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
                    this.longScaleOnePointTwo = 1;
                    this.isStartDrag = !1;
                    this.selected.splice(-1 !== i ? i : this.selected.length - 1, 0, ObservedObject.GetRawObject(this.content))
                }
            }));
            Grid.onItemDragMove(((e, t, i) => this.onDragMoveEvent(e, t, i)))
        }), Grid);
        this.observeComponentCreation2(((e, t) => {
            ForEach.create();
            this.forEachUpdateFunction(e, this.selected, ((e, t) => {
                const i = e;
                {
                    const e = (e, i) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e);
                        GridItem.create((() => {
                        }),!1);
                        Context.animation({
                            duration: 300,
                            curve: COMMON_BEZIER,
                            iterations: 1,
                            playMode: PlayMode.Normal
                        });
                        GridItem.clip(!1);
                        GridItem.translate({
                            x: this.getXY(ObservedObject.GetRawObject(this.selected), t, this.selectedIndex).x,
                            y: this.getXY(ObservedObject.GetRawObject(this.selected), t, this.selectedIndex).y
                        });
                        Context.animation(null);
                        i || GridItem.pop();
                        ViewStackProcessor.StopGetAccessRecording()
                    };
                    (() => {
                        this.observeComponentCreation(e);
                        this.observeComponentCreation2(((e, t) => {
                            Stack.create();
                            Stack.clip(!1);
                            Stack.margin({ top: 2, bottom: 16 });
                            Stack.onTouch((e => {
                                if (e.type === TouchType.Down) {
                                    this.content = i;
                                    this.isTouchDown = !0
                                }
                                if (e.type === TouchType.Up) {
                                    this.isTouchDown = !1;
                                    this.longScaleOnePointTwo = 1
                                }
                            }))
                        }), Stack);
                        this.observeComponentCreation2(((e, t) => {
                            If.create();
                                this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? this.ifElseBranchUpdateFunction(0, (() => {
                                this.ImageTextBuilder.bind(this)(i, "delete")
                            })) : this.ifElseBranchUpdateFunction(1, (() => {
                                this.TextBlockBuilder.bind(this)(i, "delete")
                            }))
                        }), If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop()
                    })()
                }
            }), void 0,!0,!1)
        }), ForEach);
        ForEach.pop();
        Grid.pop()
    }

    initialRender() {
        this.observeComponentCreation2(((e, t) => {
            Column.create();
            Column.width("100%");
            Column.height("90%")
        }), Column);
        this.HeaderTitleBuilder.bind(this)();
        this.observeComponentCreation2(((e, t) => {
            Scroll.create()
        }), Scroll);
        this.observeComponentCreation2(((e, t) => {
            Column.create();
            Column.onAreaChange(((e, t) => {
                this.areaWidth = Math.trunc(Number(t.width));
                this.blockWidth = this.options.type === GridObjectSortComponentType.IMAGE_TEXT ? this.getImageBlockWidth() : this.getBlockWidth()
            }));
            Column.width("100%")
        }), Column);
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
        }), null);
        this.EditTagBuilder.bind(this)();
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
        }), null);
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