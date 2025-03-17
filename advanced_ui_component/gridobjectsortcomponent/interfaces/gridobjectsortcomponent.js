/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
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
const accessibility = requireNapi('accessibility');

const COL_IMAGE_TEXT = 3;
const COL_TEXT = 4;
const GRID_COL_3 = '1fr 1fr 1fr';
const GRID_COL_4 = '1fr 1fr 1fr 1fr';
const ICON_SIZE = 24;
const SYMBOL_SIZE_24VP = '24vp';
const SYMBOL_SIZE_12FP = 12;
const IMAGE_DEFAULT = 56;
const SYMBOL_DEFAULT = '56vp';
const SYMBOL_WEIGHT = 400;
const TEXT_PADDING_LEFT_RIGHT = 12;
const PADDING_EIGHT = 4;
const GRID_ITEM_HEIGHT_TEXT = 28;
const MARGIN_EIGHT = 8;
const ROW_GAP = 16;
const SUBTITLE_HEIGHT = 56;
const TEXT_MAX_LINES = 1;
const MIN_FONT_SCALE = 1;
const MAX_FONT_SCALE = 2;
const MIN_SYMBOL_FONT_SCALE = 1.15;
const DEFAULT_TEXT_SIZE = 12;
const DEFAULT_FONT_SIZE_SCALE = 1;
const DEFAULT_FONT_WEIGHT_SCALE = 1;
const DEFAULT_BLOCK_TEXT_ITEM_SAFE_MARGIN = 8;
const EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN = 16;
const ENTER_EXIT_ICON_DURATION = 200;
const SEND_EVENT_DURATION = 10;
const COMMON_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1);
const DRAG_SPRING = curves.interpolatingSpring(0, 1, 400, 38);
const REMOVE_ADD_SPRING = curves.interpolatingSpring(0, 1, 150, 24);
const LONG_TOUCH_SCALE = curves.cubicBezierCurve(0.2, 0, 0.2, 1);
const ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE = 'gridobjectsortcomponent_accessibility_item_long_press_gesture';
const ACCESSIBILITY_ILLEGAL_AREA = 'gridobjectsortcomponent_accessibility_illegal_area';
const ACCESSIBILITY_SELECTED_ITEM_DRAG_START = 'gridobjectsortcomponent_accessibility_selected_item_drag_start';
const ACCESSIBILITY_DOUBLE_CLICK = 'gridobjectsortcomponent_accessibility_single_finger_double_click';
const ACCESSIBILITY_RESIDENT_AREA = 'gridobjectsortcomponent_accessibility_resident_area_edit_state';
const ACCESSIBILITY_SELECTED_ITEM_DESC = 'gridobjectsortcomponent_accessibility_selected_item_desc';
const ACCESSIBILITY_SELECTED_ITEM = 'gridobjectsortcomponent_accessibility_selected_item';
const ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP = 'gridobjectsortcomponent_accessibility_selected_item_drag_stop';
const ACCESSIBILITY_UNSELECTED_ITEM_ADD = 'gridobjectsortcomponent_accessibility_unselected_item_add';
const ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC = 'gridobjectsortcomponent_accessibility_unselected_image_item_desc';
const ACCESSIBILITY_UNSELECTED_TEXT_ITEM_DESC = 'gridobjectsortcomponent_accessibility_unselected_text_item_desc';
const ACCESSIBILITY_UNSELECTED_ITEM = 'gridobjectsortcomponent_accessibility_unselected_item';
const ACCESSIBILITY_SELECTED_ITEM_DELETE = 'gridobjectsortcomponent_accessibility_selected_item_delete';
const ACCESSIBILITY_SELECTED_ITEM_DRAG_MOVING = 'gridobjectsortcomponent_accessibility_selected_item_drag_moving';
const ACCESSIBILITY_DELETED = 'gridobjectsortcomponent_accessibility_deleted';
const ACCESSIBILITY_UNSELECTED_BUTTON = 'gridobjectsortcomponent_accessibility_unselected_button';
const EDIT_TITLE_BAR_ID = 'EditTitleBar';
const ADD_TITLE_BAR_ID = 'AddTitleBar';
const ADD_GRID_FIRST_ITEM_ID = 'add_grid_item_0';
const YES = 'yes';
const NO = 'no';
const ADD = 'add';
const EDIT = 'edit';
const DELETE = 'delete';
export var GridObjectSortComponentType;
(function (l94) {
    l94['IMAGE_TEXT'] = 'image_text';
    l94['TEXT'] = 'text';
})(GridObjectSortComponentType || (GridObjectSortComponentType = {}));
export class GridObjectSortComponent extends ViewPU {
    constructor(c94, d94, e94, f94 = -1, g94 = undefined, h94) {
        super(c94, e94, f94, h94);
        if (typeof g94 === 'function') {
            this.paramsGenerator_ = g94;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(d94.options, this, 'options');
        this.dataList = [];
        this.__selected = new ObservedPropertyObjectPU([], this, 'selected');
        this.__unSelected = new ObservedPropertyObjectPU([], this, 'unSelected');
        this.__copySelected = new ObservedPropertyObjectPU([], this, 'copySelected');
        this.__copyUnSelected = new ObservedPropertyObjectPU([], this, 'copyUnSelected');
        this.__content = new ObservedPropertyObjectPU({
            id: '',
            text: '',
            selected: false,
            order: 0
        }, this, 'content');
        this.__dragContent = new ObservedPropertyObjectPU({
            id: '',
            text: '',
            selected: false,
            order: 0
        }, this, 'dragContent');
        this.__dragContentIndex = new ObservedPropertySimplePU(-1, this, 'dragContentIndex');
        this.__hoverId = new ObservedPropertySimplePU('', this, 'hoverId');
        this.__gridComState = new ObservedPropertySimplePU(false, this, 'gridComState');
        this.__menuSwitch = new ObservedPropertySimplePU(false, this, 'menuSwitch');
        this.__areaWidth = new ObservedPropertySimplePU(0, this, 'areaWidth');
        this.__blockWidth = new ObservedPropertySimplePU(0, this, 'blockWidth');
        this.__blockHeight = new ObservedPropertySimplePU(0, this, 'blockHeight');
        this.__longScaleOnePointTwo = new ObservedPropertySimplePU(1, this, 'longScaleOnePointTwo');
        this.__scaleGridItemNinetyPercent = new ObservedPropertySimplePU(1, this, 'scaleGridItemNinetyPercent');
        this.__reboundSize = new ObservedPropertySimplePU(1, this, 'reboundSize');
        this.__scaleIcon = new ObservedPropertySimplePU(1, this, 'scaleIcon');
        this.__addIconShow = new ObservedPropertySimplePU(false, this, 'addIconShow');
        this.__scaleAddIcon = new ObservedPropertySimplePU(0, this, 'scaleAddIcon');
        this.__isStartDrag = new ObservedPropertySimplePU(false, this, 'isStartDrag');
        this.__insertIndex = new ObservedPropertySimplePU(-1, this, 'insertIndex');
        this.__itemIndex = new ObservedPropertySimplePU(0, this, 'itemIndex');
        this.__editGridDataLength = new ObservedPropertySimplePU(-1, this, 'editGridDataLength');
        this.__isTouchDown = new ObservedPropertySimplePU(false, this, 'isTouchDown');
        this.__addItemMoveX = new ObservedPropertySimplePU(0, this, 'addItemMoveX');
        this.__addItemMoveY = new ObservedPropertySimplePU(0, this, 'addItemMoveY');
        this.__editItemMoveX = new ObservedPropertySimplePU(0, this, 'editItemMoveX');
        this.__editItemMoveY = new ObservedPropertySimplePU(0, this, 'editItemMoveY');
        this.__unSelectedIndex = new ObservedPropertySimplePU(0, this, 'unSelectedIndex');
        this.__clickAddBtn = new ObservedPropertySimplePU(false, this, 'clickAddBtn');
        this.__selectedIndex = new ObservedPropertySimplePU(-1, this, 'selectedIndex');
        this.__clickRemoveBtn = new ObservedPropertySimplePU(false, this, 'clickRemoveBtn');
        this.__addAreaLongPressGesture = new ObservedPropertySimplePU(false, this, 'addAreaLongPressGesture');
        this.__arraySelectIsChange = new ObservedPropertySimplePU(0, this, 'arraySelectIsChange');
        this.__arrayUnSelectIsChange = new ObservedPropertySimplePU(0, this, 'arrayUnSelectIsChange');
        this.__textItemEditWidth = new ObservedPropertySimplePU(0, this, 'textItemEditWidth');
        this.__textItemEditHeight = new ObservedPropertySimplePU(0, this, 'textItemEditHeight');
        this.__imageItemWidth = new ObservedPropertySimplePU(0, this, 'imageItemWidth');
        this.__saveClick = new ObservedPropertySimplePU(false, this, 'saveClick');
        this.__imageTextAddIconShow = new ObservedPropertySimplePU(false, this, 'imageTextAddIconShow');
        this.__imageTextRemoveIconShow = new ObservedPropertySimplePU(false, this, 'imageTextRemoveIconShow');
        this.__firstIn = new ObservedPropertySimplePU(true, this, 'firstIn');
        this.__fontSizeScale = new ObservedPropertyObjectPU(1, this, 'fontSizeScale');
        this.__fontWeightScale = new ObservedPropertyObjectPU(1, this, 'fontWeightScale');
        this.__customColumns = new ObservedPropertySimplePU('1fr 1fr 1fr 1fr', this, 'customColumns');
        this.__editGridHeight = new ObservedPropertySimplePU(0, this, 'editGridHeight');
        this.__addGridHeight = new ObservedPropertySimplePU(0, this, 'addGridHeight');
        this.__subTitleHeight = new ObservedPropertySimplePU(0, this, 'subTitleHeight');
        this.__isOpenAccessibility = new ObservedPropertySimplePU(accessibility.isScreenReaderOpenSync(), this, 'isOpenAccessibility');
        this.callbackId = undefined;
        this.colNum = COL_IMAGE_TEXT;
        this.vibrationDone = false;
        this.touchDown = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.touchBorderRadius = { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.hoverBackgroundColor = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.imageText = false;
        this.onSave = undefined;
        this.onCancel = undefined;
        this.isFollowingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.bundleName = '';
        this.__readFlag = new ObservedPropertySimplePU(true, this, 'readFlag');
        this.__readIndex4AddArea = new ObservedPropertySimplePU(-1, this, 'readIndex4AddArea');
        this.__readIndex4EditArea = new ObservedPropertySimplePU(-1, this, 'readIndex4EditArea');
        this.__isPointToAddTitleBarEditButton = new ObservedPropertySimplePU(false, this, 'isPointToAddTitleBarEditButton');
        this.__isPointToEditTitleBarSaveButton = new ObservedPropertySimplePU(false, this, 'isPointToEditTitleBarSaveButton');
        this.preTextAnnouncedForAccessibility = '';
        this.textAnnouncedForAccessibility = '';
        this.envCallback = {
            onConfigurationUpdated: (f1) => {
                let g1 = this.getUIContext();
                this.fontSizeScale = this.decideFontScale(g1);
                this.fontWeightScale = f1.fontWeightScale;
            },
            onMemoryLevel: (e1) => { }
        };
        this.setInitiallyProvidedValue(d94);
        this.declareWatch('gridComState', this.onGridComStateChange);
        this.declareWatch('fontSizeScale', this.calcAreaInfo);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b94) {
        if (b94.options === undefined) {
            this.__options.set({});
        }
        if (b94.dataList !== undefined) {
            this.dataList = b94.dataList;
        }
        if (b94.selected !== undefined) {
            this.selected = b94.selected;
        }
        if (b94.unSelected !== undefined) {
            this.unSelected = b94.unSelected;
        }
        if (b94.copySelected !== undefined) {
            this.copySelected = b94.copySelected;
        }
        if (b94.copyUnSelected !== undefined) {
            this.copyUnSelected = b94.copyUnSelected;
        }
        if (b94.content !== undefined) {
            this.content = b94.content;
        }
        if (b94.dragContent !== undefined) {
            this.dragContent = b94.dragContent;
        }
        if (b94.dragContentIndex !== undefined) {
            this.dragContentIndex = b94.dragContentIndex;
        }
        if (b94.hoverId !== undefined) {
            this.hoverId = b94.hoverId;
        }
        if (b94.gridComState !== undefined) {
            this.gridComState = b94.gridComState;
        }
        if (b94.menuSwitch !== undefined) {
            this.menuSwitch = b94.menuSwitch;
        }
        if (b94.areaWidth !== undefined) {
            this.areaWidth = b94.areaWidth;
        }
        if (b94.blockWidth !== undefined) {
            this.blockWidth = b94.blockWidth;
        }
        if (b94.blockHeight !== undefined) {
            this.blockHeight = b94.blockHeight;
        }
        if (b94.longScaleOnePointTwo !== undefined) {
            this.longScaleOnePointTwo = b94.longScaleOnePointTwo;
        }
        if (b94.scaleGridItemNinetyPercent !== undefined) {
            this.scaleGridItemNinetyPercent = b94.scaleGridItemNinetyPercent;
        }
        if (b94.reboundSize !== undefined) {
            this.reboundSize = b94.reboundSize;
        }
        if (b94.scaleIcon !== undefined) {
            this.scaleIcon = b94.scaleIcon;
        }
        if (b94.addIconShow !== undefined) {
            this.addIconShow = b94.addIconShow;
        }
        if (b94.scaleAddIcon !== undefined) {
            this.scaleAddIcon = b94.scaleAddIcon;
        }
        if (b94.isStartDrag !== undefined) {
            this.isStartDrag = b94.isStartDrag;
        }
        if (b94.insertIndex !== undefined) {
            this.insertIndex = b94.insertIndex;
        }
        if (b94.itemIndex !== undefined) {
            this.itemIndex = b94.itemIndex;
        }
        if (b94.editGridDataLength !== undefined) {
            this.editGridDataLength = b94.editGridDataLength;
        }
        if (b94.isTouchDown !== undefined) {
            this.isTouchDown = b94.isTouchDown;
        }
        if (b94.addItemMoveX !== undefined) {
            this.addItemMoveX = b94.addItemMoveX;
        }
        if (b94.addItemMoveY !== undefined) {
            this.addItemMoveY = b94.addItemMoveY;
        }
        if (b94.editItemMoveX !== undefined) {
            this.editItemMoveX = b94.editItemMoveX;
        }
        if (b94.editItemMoveY !== undefined) {
            this.editItemMoveY = b94.editItemMoveY;
        }
        if (b94.unSelectedIndex !== undefined) {
            this.unSelectedIndex = b94.unSelectedIndex;
        }
        if (b94.clickAddBtn !== undefined) {
            this.clickAddBtn = b94.clickAddBtn;
        }
        if (b94.selectedIndex !== undefined) {
            this.selectedIndex = b94.selectedIndex;
        }
        if (b94.clickRemoveBtn !== undefined) {
            this.clickRemoveBtn = b94.clickRemoveBtn;
        }
        if (b94.addAreaLongPressGesture !== undefined) {
            this.addAreaLongPressGesture = b94.addAreaLongPressGesture;
        }
        if (b94.arraySelectIsChange !== undefined) {
            this.arraySelectIsChange = b94.arraySelectIsChange;
        }
        if (b94.arrayUnSelectIsChange !== undefined) {
            this.arrayUnSelectIsChange = b94.arrayUnSelectIsChange;
        }
        if (b94.textItemEditWidth !== undefined) {
            this.textItemEditWidth = b94.textItemEditWidth;
        }
        if (b94.textItemEditHeight !== undefined) {
            this.textItemEditHeight = b94.textItemEditHeight;
        }
        if (b94.imageItemWidth !== undefined) {
            this.imageItemWidth = b94.imageItemWidth;
        }
        if (b94.saveClick !== undefined) {
            this.saveClick = b94.saveClick;
        }
        if (b94.imageTextAddIconShow !== undefined) {
            this.imageTextAddIconShow = b94.imageTextAddIconShow;
        }
        if (b94.imageTextRemoveIconShow !== undefined) {
            this.imageTextRemoveIconShow = b94.imageTextRemoveIconShow;
        }
        if (b94.firstIn !== undefined) {
            this.firstIn = b94.firstIn;
        }
        if (b94.fontSizeScale !== undefined) {
            this.fontSizeScale = b94.fontSizeScale;
        }
        if (b94.fontWeightScale !== undefined) {
            this.fontWeightScale = b94.fontWeightScale;
        }
        if (b94.customColumns !== undefined) {
            this.customColumns = b94.customColumns;
        }
        if (b94.editGridHeight !== undefined) {
            this.editGridHeight = b94.editGridHeight;
        }
        if (b94.addGridHeight !== undefined) {
            this.addGridHeight = b94.addGridHeight;
        }
        if (b94.subTitleHeight !== undefined) {
            this.subTitleHeight = b94.subTitleHeight;
        }
        if (b94.isOpenAccessibility !== undefined) {
            this.isOpenAccessibility = b94.isOpenAccessibility;
        }
        if (b94.callbackId !== undefined) {
            this.callbackId = b94.callbackId;
        }
        if (b94.colNum !== undefined) {
            this.colNum = b94.colNum;
        }
        if (b94.vibrationDone !== undefined) {
            this.vibrationDone = b94.vibrationDone;
        }
        if (b94.touchDown !== undefined) {
            this.touchDown = b94.touchDown;
        }
        if (b94.touchBorderRadius !== undefined) {
            this.touchBorderRadius = b94.touchBorderRadius;
        }
        if (b94.hoverBackgroundColor !== undefined) {
            this.hoverBackgroundColor = b94.hoverBackgroundColor;
        }
        if (b94.imageText !== undefined) {
            this.imageText = b94.imageText;
        }
        if (b94.onSave !== undefined) {
            this.onSave = b94.onSave;
        }
        if (b94.onCancel !== undefined) {
            this.onCancel = b94.onCancel;
        }
        if (b94.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = b94.isFollowingSystemFontScale;
        }
        if (b94.maxAppFontScale !== undefined) {
            this.maxAppFontScale = b94.maxAppFontScale;
        }
        if (b94.bundleName !== undefined) {
            this.bundleName = b94.bundleName;
        }
        if (b94.readFlag !== undefined) {
            this.readFlag = b94.readFlag;
        }
        if (b94.readIndex4AddArea !== undefined) {
            this.readIndex4AddArea = b94.readIndex4AddArea;
        }
        if (b94.readIndex4EditArea !== undefined) {
            this.readIndex4EditArea = b94.readIndex4EditArea;
        }
        if (b94.isPointToAddTitleBarEditButton !== undefined) {
            this.isPointToAddTitleBarEditButton = b94.isPointToAddTitleBarEditButton;
        }
        if (b94.isPointToEditTitleBarSaveButton !== undefined) {
            this.isPointToEditTitleBarSaveButton = b94.isPointToEditTitleBarSaveButton;
        }
        if (b94.preTextAnnouncedForAccessibility !== undefined) {
            this.preTextAnnouncedForAccessibility = b94.preTextAnnouncedForAccessibility;
        }
        if (b94.textAnnouncedForAccessibility !== undefined) {
            this.textAnnouncedForAccessibility = b94.textAnnouncedForAccessibility;
        }
        if (b94.envCallback !== undefined) {
            this.envCallback = b94.envCallback;
        }
    }
    updateStateVars(a94) {
        this.__options.reset(a94.options);
    }
    purgeVariableDependenciesOnElmtId(z93) {
        this.__options.purgeDependencyOnElmtId(z93);
        this.__selected.purgeDependencyOnElmtId(z93);
        this.__unSelected.purgeDependencyOnElmtId(z93);
        this.__copySelected.purgeDependencyOnElmtId(z93);
        this.__copyUnSelected.purgeDependencyOnElmtId(z93);
        this.__content.purgeDependencyOnElmtId(z93);
        this.__dragContent.purgeDependencyOnElmtId(z93);
        this.__dragContentIndex.purgeDependencyOnElmtId(z93);
        this.__hoverId.purgeDependencyOnElmtId(z93);
        this.__gridComState.purgeDependencyOnElmtId(z93);
        this.__menuSwitch.purgeDependencyOnElmtId(z93);
        this.__areaWidth.purgeDependencyOnElmtId(z93);
        this.__blockWidth.purgeDependencyOnElmtId(z93);
        this.__blockHeight.purgeDependencyOnElmtId(z93);
        this.__longScaleOnePointTwo.purgeDependencyOnElmtId(z93);
        this.__scaleGridItemNinetyPercent.purgeDependencyOnElmtId(z93);
        this.__reboundSize.purgeDependencyOnElmtId(z93);
        this.__scaleIcon.purgeDependencyOnElmtId(z93);
        this.__addIconShow.purgeDependencyOnElmtId(z93);
        this.__scaleAddIcon.purgeDependencyOnElmtId(z93);
        this.__isStartDrag.purgeDependencyOnElmtId(z93);
        this.__insertIndex.purgeDependencyOnElmtId(z93);
        this.__itemIndex.purgeDependencyOnElmtId(z93);
        this.__editGridDataLength.purgeDependencyOnElmtId(z93);
        this.__isTouchDown.purgeDependencyOnElmtId(z93);
        this.__addItemMoveX.purgeDependencyOnElmtId(z93);
        this.__addItemMoveY.purgeDependencyOnElmtId(z93);
        this.__editItemMoveX.purgeDependencyOnElmtId(z93);
        this.__editItemMoveY.purgeDependencyOnElmtId(z93);
        this.__unSelectedIndex.purgeDependencyOnElmtId(z93);
        this.__clickAddBtn.purgeDependencyOnElmtId(z93);
        this.__selectedIndex.purgeDependencyOnElmtId(z93);
        this.__clickRemoveBtn.purgeDependencyOnElmtId(z93);
        this.__addAreaLongPressGesture.purgeDependencyOnElmtId(z93);
        this.__arraySelectIsChange.purgeDependencyOnElmtId(z93);
        this.__arrayUnSelectIsChange.purgeDependencyOnElmtId(z93);
        this.__textItemEditWidth.purgeDependencyOnElmtId(z93);
        this.__textItemEditHeight.purgeDependencyOnElmtId(z93);
        this.__imageItemWidth.purgeDependencyOnElmtId(z93);
        this.__saveClick.purgeDependencyOnElmtId(z93);
        this.__imageTextAddIconShow.purgeDependencyOnElmtId(z93);
        this.__imageTextRemoveIconShow.purgeDependencyOnElmtId(z93);
        this.__firstIn.purgeDependencyOnElmtId(z93);
        this.__fontSizeScale.purgeDependencyOnElmtId(z93);
        this.__fontWeightScale.purgeDependencyOnElmtId(z93);
        this.__customColumns.purgeDependencyOnElmtId(z93);
        this.__editGridHeight.purgeDependencyOnElmtId(z93);
        this.__addGridHeight.purgeDependencyOnElmtId(z93);
        this.__subTitleHeight.purgeDependencyOnElmtId(z93);
        this.__isOpenAccessibility.purgeDependencyOnElmtId(z93);
        this.__readFlag.purgeDependencyOnElmtId(z93);
        this.__readIndex4AddArea.purgeDependencyOnElmtId(z93);
        this.__readIndex4EditArea.purgeDependencyOnElmtId(z93);
        this.__isPointToAddTitleBarEditButton.purgeDependencyOnElmtId(z93);
        this.__isPointToEditTitleBarSaveButton.purgeDependencyOnElmtId(z93);
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
        this.__isOpenAccessibility.aboutToBeDeleted();
        this.__readFlag.aboutToBeDeleted();
        this.__readIndex4AddArea.aboutToBeDeleted();
        this.__readIndex4EditArea.aboutToBeDeleted();
        this.__isPointToAddTitleBarEditButton.aboutToBeDeleted();
        this.__isPointToEditTitleBarSaveButton.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get options() {
        return this.__options.get();
    }
    set options(y93) {
        this.__options.set(y93);
    }
    get selected() {
        return this.__selected.get();
    }
    set selected(x93) {
        this.__selected.set(x93);
    }
    get unSelected() {
        return this.__unSelected.get();
    }
    set unSelected(w93) {
        this.__unSelected.set(w93);
    }
    get copySelected() {
        return this.__copySelected.get();
    }
    set copySelected(v93) {
        this.__copySelected.set(v93);
    }
    get copyUnSelected() {
        return this.__copyUnSelected.get();
    }
    set copyUnSelected(u93) {
        this.__copyUnSelected.set(u93);
    }
    get content() {
        return this.__content.get();
    }
    set content(t93) {
        this.__content.set(t93);
    }
    get dragContent() {
        return this.__dragContent.get();
    }
    set dragContent(s93) {
        this.__dragContent.set(s93);
    }
    get dragContentIndex() {
        return this.__dragContentIndex.get();
    }
    set dragContentIndex(r93) {
        this.__dragContentIndex.set(r93);
    }
    get hoverId() {
        return this.__hoverId.get();
    }
    set hoverId(q93) {
        this.__hoverId.set(q93);
    }
    get gridComState() {
        return this.__gridComState.get();
    }
    set gridComState(p93) {
        this.__gridComState.set(p93);
    }
    get menuSwitch() {
        return this.__menuSwitch.get();
    }
    set menuSwitch(o93) {
        this.__menuSwitch.set(o93);
    }
    get areaWidth() {
        return this.__areaWidth.get();
    }
    set areaWidth(n93) {
        this.__areaWidth.set(n93);
    }
    get blockWidth() {
        return this.__blockWidth.get();
    }
    set blockWidth(m93) {
        this.__blockWidth.set(m93);
    }
    get blockHeight() {
        return this.__blockHeight.get();
    }
    set blockHeight(l93) {
        this.__blockHeight.set(l93);
    }
    get longScaleOnePointTwo() {
        return this.__longScaleOnePointTwo.get();
    }
    set longScaleOnePointTwo(k93) {
        this.__longScaleOnePointTwo.set(k93);
    }
    get scaleGridItemNinetyPercent() {
        return this.__scaleGridItemNinetyPercent.get();
    }
    set scaleGridItemNinetyPercent(j93) {
        this.__scaleGridItemNinetyPercent.set(j93);
    }
    get reboundSize() {
        return this.__reboundSize.get();
    }
    set reboundSize(i93) {
        this.__reboundSize.set(i93);
    }
    get scaleIcon() {
        return this.__scaleIcon.get();
    }
    set scaleIcon(h93) {
        this.__scaleIcon.set(h93);
    }
    get addIconShow() {
        return this.__addIconShow.get();
    }
    set addIconShow(g93) {
        this.__addIconShow.set(g93);
    }
    get scaleAddIcon() {
        return this.__scaleAddIcon.get();
    }
    set scaleAddIcon(f93) {
        this.__scaleAddIcon.set(f93);
    }
    get isStartDrag() {
        return this.__isStartDrag.get();
    }
    set isStartDrag(e93) {
        this.__isStartDrag.set(e93);
    }
    get insertIndex() {
        return this.__insertIndex.get();
    }
    set insertIndex(d93) {
        this.__insertIndex.set(d93);
    }
    get itemIndex() {
        return this.__itemIndex.get();
    }
    set itemIndex(c93) {
        this.__itemIndex.set(c93);
    }
    get editGridDataLength() {
        return this.__editGridDataLength.get();
    }
    set editGridDataLength(b93) {
        this.__editGridDataLength.set(b93);
    }
    get isTouchDown() {
        return this.__isTouchDown.get();
    }
    set isTouchDown(a93) {
        this.__isTouchDown.set(a93);
    }
    get addItemMoveX() {
        return this.__addItemMoveX.get();
    }
    set addItemMoveX(z92) {
        this.__addItemMoveX.set(z92);
    }
    get addItemMoveY() {
        return this.__addItemMoveY.get();
    }
    set addItemMoveY(y92) {
        this.__addItemMoveY.set(y92);
    }
    get editItemMoveX() {
        return this.__editItemMoveX.get();
    }
    set editItemMoveX(x92) {
        this.__editItemMoveX.set(x92);
    }
    get editItemMoveY() {
        return this.__editItemMoveY.get();
    }
    set editItemMoveY(w92) {
        this.__editItemMoveY.set(w92);
    }
    get unSelectedIndex() {
        return this.__unSelectedIndex.get();
    }
    set unSelectedIndex(v92) {
        this.__unSelectedIndex.set(v92);
    }
    get clickAddBtn() {
        return this.__clickAddBtn.get();
    }
    set clickAddBtn(u92) {
        this.__clickAddBtn.set(u92);
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(t92) {
        this.__selectedIndex.set(t92);
    }
    get clickRemoveBtn() {
        return this.__clickRemoveBtn.get();
    }
    set clickRemoveBtn(s92) {
        this.__clickRemoveBtn.set(s92);
    }
    get addAreaLongPressGesture() {
        return this.__addAreaLongPressGesture.get();
    }
    set addAreaLongPressGesture(r92) {
        this.__addAreaLongPressGesture.set(r92);
    }
    get arraySelectIsChange() {
        return this.__arraySelectIsChange.get();
    }
    set arraySelectIsChange(q92) {
        this.__arraySelectIsChange.set(q92);
    }
    get arrayUnSelectIsChange() {
        return this.__arrayUnSelectIsChange.get();
    }
    set arrayUnSelectIsChange(p92) {
        this.__arrayUnSelectIsChange.set(p92);
    }
    get textItemEditWidth() {
        return this.__textItemEditWidth.get();
    }
    set textItemEditWidth(o92) {
        this.__textItemEditWidth.set(o92);
    }
    get textItemEditHeight() {
        return this.__textItemEditHeight.get();
    }
    set textItemEditHeight(n92) {
        this.__textItemEditHeight.set(n92);
    }
    get imageItemWidth() {
        return this.__imageItemWidth.get();
    }
    set imageItemWidth(m92) {
        this.__imageItemWidth.set(m92);
    }
    get saveClick() {
        return this.__saveClick.get();
    }
    set saveClick(l92) {
        this.__saveClick.set(l92);
    }
    get imageTextAddIconShow() {
        return this.__imageTextAddIconShow.get();
    }
    set imageTextAddIconShow(k92) {
        this.__imageTextAddIconShow.set(k92);
    }
    get imageTextRemoveIconShow() {
        return this.__imageTextRemoveIconShow.get();
    }
    set imageTextRemoveIconShow(j92) {
        this.__imageTextRemoveIconShow.set(j92);
    }
    get firstIn() {
        return this.__firstIn.get();
    }
    set firstIn(i92) {
        this.__firstIn.set(i92);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(h92) {
        this.__fontSizeScale.set(h92);
    }
    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }
    set fontWeightScale(g92) {
        this.__fontWeightScale.set(g92);
    }
    get customColumns() {
        return this.__customColumns.get();
    }
    set customColumns(f92) {
        this.__customColumns.set(f92);
    }
    get editGridHeight() {
        return this.__editGridHeight.get();
    }
    set editGridHeight(e92) {
        this.__editGridHeight.set(e92);
    }
    get addGridHeight() {
        return this.__addGridHeight.get();
    }
    set addGridHeight(d92) {
        this.__addGridHeight.set(d92);
    }
    get subTitleHeight() {
        return this.__subTitleHeight.get();
    }
    set subTitleHeight(c92) {
        this.__subTitleHeight.set(c92);
    }
    get isOpenAccessibility() {
        return this.__isOpenAccessibility.get();
    }
    set isOpenAccessibility(b92) {
        this.__isOpenAccessibility.set(b92);
    }
    get readFlag() {
        return this.__readFlag.get();
    }
    set readFlag(a92) {
        this.__readFlag.set(a92);
    }
    get readIndex4AddArea() {
        return this.__readIndex4AddArea.get();
    }
    set readIndex4AddArea(z91) {
        this.__readIndex4AddArea.set(z91);
    }
    get readIndex4EditArea() {
        return this.__readIndex4EditArea.get();
    }
    set readIndex4EditArea(y91) {
        this.__readIndex4EditArea.set(y91);
    }
    get isPointToAddTitleBarEditButton() {
        return this.__isPointToAddTitleBarEditButton.get();
    }
    set isPointToAddTitleBarEditButton(x91) {
        this.__isPointToAddTitleBarEditButton.set(x91);
    }
    get isPointToEditTitleBarSaveButton() {
        return this.__isPointToEditTitleBarSaveButton.get();
    }
    set isPointToEditTitleBarSaveButton(w91) {
        this.__isPointToEditTitleBarSaveButton.set(w91);
    }
    aboutToAppear() {
        this.dataList.length = 50;
        this.selected = this.dataList && this.deduplicate(this.dataList).filter(v91 => v91.selected).sort(this.sortBy());
        this.unSelected = this.dataList && this.deduplicate(this.dataList).filter(u91 => !u91.selected).sort(this.sortBy());
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
        try {
            let t91 = this.getUIContext();
            this.isFollowingSystemFontScale = t91.isFollowingSystemFontScale();
            this.maxAppFontScale = t91.getMaxFontScale();
            this.fontSizeScale = this.decideFontScale(t91);
            this.fontWeightScale =
                t91.getHostContext()?.config?.fontWeightScale ?? DEFAULT_FONT_WEIGHT_SCALE;
        }
        catch (q91) {
            let r91 = q91.code;
            let s91 = q91.message;
            hilog.error(0x3900, 'Ace', `GridObjectSortComponent Faild to init fontsizescale info, code:${r91}, message: ${s91}`);
        }
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        }
        catch (n91) {
            let o91 = n91.code;
            let p91 = n91.message;
            hilog.error(0x3900, 'Ace', `GridObjectSortComponent Faild to get environment param error: ${o91}, ${p91}`);
        }
        this.calcGridHeight();
        setTimeout(() => {
            this.firstIn = false;
        }, 500);
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
        accessibility.on('screenReaderStateChange', (m91) => {
            this.isOpenAccessibility = m91;
        });
    }
    getAdaptiveSymbolFontSize() {
        let l91 = this.fontSizeScale;
        if (!this.isFollowingSystemFontScale || l91 === undefined) {
            l91 = MIN_FONT_SCALE;
        }
        l91 = Math.min(MIN_SYMBOL_FONT_SCALE, l91);
        l91 = Math.max(l91, MIN_FONT_SCALE);
        return (l91 * SYMBOL_SIZE_12FP).toString() + 'vp';
    }
    getSymbolFontSizeFrom(k91) {
        if (k91 === undefined) {
            return SYMBOL_DEFAULT;
        }
        if (typeof k91 === 'number') {
            return k91.toString() + 'vp';
        }
        return k91;
    }
    calcTextItemEditHeight() {
        let j91 = MeasureText.measureTextSize({
            textContent: this.dataList[0]?.text ?? '',
            fontSize: `${(LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })?.value ??
                DEFAULT_TEXT_SIZE) * (this.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE)}vp`,
            overflow: TextOverflow.Ellipsis,
            maxLines: TEXT_MAX_LINES
        });
        this.textItemEditHeight = this.fontSizeScale === DEFAULT_FONT_SIZE_SCALE ?
            GRID_ITEM_HEIGHT_TEXT : px2vp(j91.height);
        this.textItemEditHeight = this.textItemEditHeight + PADDING_EIGHT * 2;
    }
    decideFontScale(h91) {
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        let i91 = h91.getHostContext()?.config?.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE;
        return Math.min(i91, this.maxAppFontScale, MAX_FONT_SCALE);
    }
    calcColNum() {
        if (this.imageText || (this.fontSizeScale && this.fontSizeScale > DEFAULT_FONT_SIZE_SCALE)) {
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
    deduplicate(d91) {
        const e91 = [];
        d91.forEach(f91 => {
            if (!e91.some(g91 => g91.id === f91.id)) {
                e91.push(f91);
            }
        });
        return e91;
    }
    onGridComStateChange() {
        this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
        if (!this.imageText) {
            this.blockHeight = this.gridComState ?
                this.textItemEditHeight + EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN :
                this.textItemEditHeight + DEFAULT_BLOCK_TEXT_ITEM_SAFE_MARGIN;
        }
    }
    sortBy() {
        return (b91, c91) => {
            return b91.order - c91.order;
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
        this.isPointToAddTitleBarEditButton = true;
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
        this.isPointToEditTitleBarSaveButton = true;
        this.calcGridHeight();
    }
    pointToEditTitleBarSaveButton() {
        if (this.isPointToEditTitleBarSaveButton) {
            let z90 = this.getUIContext().getFrameNodeById(EDIT_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
            let a91 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `ImageMenuItem_${z90}_0`
            });
            accessibility.sendAccessibilityEvent(a91).then(() => {
                setTimeout(() => {
                    this.isPointToEditTitleBarSaveButton = false;
                }, ENTER_EXIT_ICON_DURATION);
            });
        }
    }
    onSaveEdit() {
        if (this.isStartDrag) {
            return;
        }
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
            const x90 = this.getNewData(this.selected, true, 0);
            const y90 = this.getNewData(this.unSelected, false, this.selected.length);
            this.selected = x90;
            this.unSelected = y90;
            this.calcGridHeight();
            this.onSave && this.onSave(x90, y90);
        });
        setTimeout(() => {
            this.saveClick = false;
        }, ENTER_EXIT_ICON_DURATION);
        this.menuSwitch = false;
        this.isPointToAddTitleBarEditButton = true;
    }
    pointToAddTitleBarEditButton() {
        if (this.isPointToAddTitleBarEditButton) {
            let v90 = this.getUIContext()?.getFrameNodeById(ADD_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
            let w90 = ({
                type: 'requestFocusForAccessibilityNotInterrupt',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `ComposeTitleBar_ImageMenuItem_${v90}_0`
            });
            setTimeout(() => {
                accessibility.sendAccessibilityEvent(w90).then(() => {
                    setTimeout(() => {
                        this.isPointToAddTitleBarEditButton = false;
                    }, ENTER_EXIT_ICON_DURATION);
                });
            }, SEND_EVENT_DURATION);
        }
    }
    onDragMoveEvent(r90, s90, t90) {
        if (!this.gridComState || (r90.x < this.blockWidth / 3 && r90.y < this.blockHeight / 3)) {
            return;
        }
        let u90 = t90;
        if (u90 < 0) {
            u90 = this.selected.length - 1;
        }
        else {
            this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_MOVING, Math.floor(t90 / this.colNum) + 1, t90 % this.colNum + 1);
        }
        if (this.dragContent.visibility !== Visibility.Hidden) {
            this.dragContent.visibility = Visibility.Hidden;
        }
        if (this.insertIndex !== t90 || s90 !== t90) {
            this.sendAccessibility();
        }
        this.insertIndex = t90;
    }
    sendAccessibility() {
        if (this.preTextAnnouncedForAccessibility !== this.textAnnouncedForAccessibility) {
            let q90 = ({
                type: 'announceForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                textAnnouncedForAccessibility: this.textAnnouncedForAccessibility
            });
            accessibility.sendAccessibilityEvent(q90);
            this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
        }
    }
    handleDeleteClick(m90) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.clickRemoveBtn = true;
        this.scaleIcon = 0;
        this.arraySelectIsChange = 1;
        let n90 = this.selected.findIndex(p90 => p90.id === m90.id);
        this.content = m90;
        this.selectedIndex = n90;
        this.calcGridHeight();
        Context.animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
            this.scaleIcon = 1;
            this.selected.splice(n90, 1);
            this.unSelected.unshift(m90);
            this.calcGridHeight();
            this.editGridDataLength = this.editGridDataLength - 1;
            this.editItemMoveX = 0;
            this.editItemMoveY = 0;
            this.arraySelectIsChange = 2;
            this.clickRemoveBtn = false;
            this.readFlag = false;
            this.readIndex4AddArea = 0;
            this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_DELETED, this.getAccessibilityText(this.content?.text ?? ' '));
        } }, () => {
            let o90 = this.getAddItemGridPosition();
            this.editItemMoveX = o90.x;
            this.editItemMoveY = o90.y;
        });
    }
    pointToAddArea() {
        let l90 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: ADD_GRID_FIRST_ITEM_ID
        });
        accessibility.sendAccessibilityEvent(l90).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4AddArea = -1;
            }, ENTER_EXIT_ICON_DURATION);
        });
    }
    getNewData(g90, h90, i90) {
        return g90.map((j90, k90) => {
            j90.selected = h90;
            j90.order = i90 + k90;
            j90.visibility = Visibility.Visible;
            return j90;
        });
    }
    getBlockWidth() {
        const f90 = (this.areaWidth - 32) / this.colNum;
        return f90;
    }
    calcGridHeight() {
        this.editGridHeight = this.getGridHeight(this.selected, EDIT);
        this.addGridHeight = this.getGridHeight(this.unSelected);
    }
    getGridHeight(x89, y89) {
        let z89 = 0;
        let a90 = x89.length;
        x89.forEach(e90 => {
            if (e90.visibility === Visibility.Hidden) {
                a90 = a90 - 1;
            }
        });
        let b90 = 0;
        let c90 = a90 % this.colNum === 0;
        if (this.clickAddBtn && c90) {
            b90 = 1;
        }
        else if (this.isStartDrag && c90 && y89) {
            b90 = 1;
        }
        else if (this.clickRemoveBtn && c90 && !y89) {
            b90 = 1;
        }
        else {
            b90 = 0;
        }
        let d90 = Math.ceil(a90 / this.colNum) + b90;
        z89 = this.blockHeight * d90;
        if (a90 === 0) {
            z89 = 0;
        }
        return z89;
    }
    imageTextRemoveIcon(u89) {
        const v89 = this.clickRemoveBtn && this.content.id === u89.id;
        const w89 = v89 ? { 'id': -1, 'type': 40000, params: ['sys.symbol.plus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        return w89;
    }
    imageTextAddIcon(r89) {
        const s89 = this.clickAddBtn && this.content.id === r89.id && this.gridComState;
        const t89 = s89 ? { 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 40000, params: ['sys.symbol.plus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        return t89;
    }
    imageTextAddIconVisible(o89) {
        const p89 = this.clickAddBtn && this.content.id === o89.id && !this.gridComState;
        const q89 = p89 ? Visibility.Hidden : Visibility.Visible;
        return q89;
    }
    getCoodXY(j89) {
        let k89 = 0;
        let l89 = 0;
        const m89 = this.colNum;
        const n89 = Math.trunc(j89 % m89);
        if (j89 >= this.dragContentIndex) {
            if (j89 <= this.insertIndex && j89 !== this.dragContentIndex) {
                if (n89 === 0) {
                    k89 = k89 + this.blockWidth * (m89 - 1);
                    l89 = l89 - this.blockHeight;
                }
                else {
                    k89 = k89 - this.blockWidth;
                }
            }
        }
        else {
            if (j89 >= this.insertIndex) {
                if (n89 === m89 - 1) {
                    k89 = k89 - this.blockWidth * (m89 - 1);
                    l89 = l89 + this.blockHeight;
                }
                else {
                    k89 = k89 + this.blockWidth;
                }
            }
        }
        if (!this.isStartDrag) {
            k89 = 0;
            l89 = 0;
        }
        return { x: k89, y: l89 };
    }
    getAddItemGridPosition() {
        const x88 = this.selected.length;
        const y88 = this.colNum;
        const z88 = (this.selectedIndex + 1) % y88;
        const a89 = Math.ceil((this.selectedIndex + 1) / y88);
        const b89 = Math.ceil(x88 / y88);
        const c89 = this.imageText;
        let d89 = 0;
        if (z88 === 0) {
            d89 = c89 || (this.fontSizeScale && this.fontSizeScale > 1) ? -this.blockWidth * 2 : -this.blockWidth * 3;
        }
        else {
            d89 = -this.blockWidth * (z88 - 1);
        }
        let e89 = SUBTITLE_HEIGHT;
        let f89 = 0;
        const g89 = b89 - a89;
        const h89 = x88 % y88;
        const i89 = h89 === 1 ? g89 : g89 + 1;
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            e89 = this.subTitleHeight;
        }
        f89 = i89 * this.blockHeight + e89;
        return {
            x: d89,
            y: f89
        };
    }
    getCoveringGridPosition(u88) {
        let v88 = 0;
        let w88 = 0;
        if (u88 > this.selectedIndex && this.arraySelectIsChange !== 2) {
            v88 = u88 % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            w88 = u88 % this.colNum === 0 ? -this.blockHeight : 0;
        }
        return {
            x: v88,
            y: w88
        };
    }
    getEditItemGridPosition(i88, j88) {
        const k88 = i88.length;
        const l88 = this.colNum;
        const m88 = Math.trunc(k88 % l88);
        const n88 = Math.trunc(j88 % l88);
        let o88 = Math.abs(m88 - n88) * this.blockWidth;
        if (m88 < n88) {
            o88 = -o88;
        }
        else if (m88 > n88) {
            o88 = o88;
        }
        else {
            o88 = 0;
        }
        let p88 = 0;
        let q88 = 0;
        let r88 = Math.trunc(j88 / this.colNum);
        let s88 = SUBTITLE_HEIGHT;
        const t88 = !this.imageText && this.gridComState && j88 > 3;
        if (t88) {
            q88 = (r88 + 1) * (this.blockHeight - 8) + 8;
        }
        else {
            q88 = (r88 + 1) * this.blockHeight;
        }
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            s88 = this.subTitleHeight;
        }
        p88 = q88 + s88;
        return {
            x: o88,
            y: p88
        };
    }
    getCoveringGridPositionBottom(d88) {
        let e88 = 0;
        let f88 = 0;
        const g88 = d88 % this.colNum === 0;
        const h88 = this.gridComState && !this.imageText ? -this.blockHeight + 8 : -this.blockHeight;
        if (d88 > this.unSelectedIndex && this.arrayUnSelectIsChange !== 2) {
            e88 = g88 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            f88 = g88 ? h88 : 0;
        }
        return {
            x: e88,
            y: f88
        };
    }
    getAddItemRightMove(z87) {
        let a88 = this.blockWidth;
        let b88 = 0;
        let c88 = (z87 + 1) % this.colNum === 0;
        if (c88) {
            a88 = -this.blockWidth * (this.colNum - 1);
            b88 = this.imageText ? this.blockHeight : this.blockHeight - 8;
        }
        return { x: a88, y: b88 };
    }
    getShowAreaItemTranslate(w87) {
        if (this.isStartDrag) {
            let y87 = this.getCoodXY(w87);
            return {
                x: y87.x,
                y: y87.y
            };
        }
        if (!this.isStartDrag && w87 === this.selectedIndex) {
            return {
                x: this.editItemMoveX,
                y: this.editItemMoveY
            };
        }
        if (!this.isStartDrag && w87 !== this.selectedIndex && this.clickRemoveBtn) {
            let x87 = this.getCoveringGridPosition(w87);
            return {
                x: x87.x,
                y: x87.y
            };
        }
        return { x: 0, y: 0 };
    }
    getAddAreaItemTranslate(t87) {
        if (this.clickRemoveBtn) {
            let v87 = this.getAddItemRightMove(t87);
            return {
                x: v87.x,
                y: v87.y
            };
        }
        if (!this.clickRemoveBtn && t87 === this.unSelectedIndex) {
            return {
                x: this.addItemMoveX,
                y: -this.addItemMoveY
            };
        }
        if (!this.clickRemoveBtn && t87 !== this.unSelectedIndex && this.clickAddBtn) {
            let u87 = this.getCoveringGridPositionBottom(t87);
            return {
                x: u87.x,
                y: u87.y
            };
        }
        return { x: 0, y: 0 };
    }
    PixelMapBuilder(s86, t86, u86 = null) {
        this.observeComponentCreation2((r87, s87) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.clip(false);
            Stack.height(this.blockHeight * 1.5);
            Stack.width(this.blockWidth * 1.2);
        }, Stack);
        this.observeComponentCreation2((v86, w86) => {
            If.create();
            if (this.imageText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p87, q87) => {
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
                    this.observeComponentCreation2((h87, i87) => {
                        If.create();
                        if (s86 === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((n87, o87) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.width(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                }, SymbolGlyph);
                            });
                        }
                        else if (s86 instanceof SymbolGlyphModifier) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((l87, m87) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.width(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.attributeModifier.bind(this)(s86);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                                this.observeComponentCreation2((j87, k87) => {
                                    Image.create(s86);
                                    Image.draggable(false);
                                    Image.height(this.options.imageSize || IMAGE_DEFAULT);
                                    Image.width(this.options.imageSize || IMAGE_DEFAULT);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((f87, g87) => {
                        Text.create(t86);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.margin({ top: 2 });
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((d87, e87) => {
                        SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.width(ICON_SIZE);
                        SymbolGlyph.height(ICON_SIZE);
                        SymbolGlyph.position({
                            x: this.blockWidth - 40,
                            y: -MARGIN_EIGHT
                        });
                    }, SymbolGlyph);
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((b87, c87) => {
                        Row.create();
                        Row.borderRadius(50);
                        Row.padding({
                            left: TEXT_PADDING_LEFT_RIGHT,
                            right: TEXT_PADDING_LEFT_RIGHT,
                        });
                        Row.scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo });
                        Row.alignItems(VerticalAlign.Center);
                        Row.justifyContent(FlexAlign.Center);
                        Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Row.width(this.textItemEditWidth);
                        Row.height(this.textItemEditHeight);
                    }, Row);
                    this.observeComponentCreation2((z86, a87) => {
                        Text.create(t86);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.textAlign(TextAlign.Center);
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((x86, y86) => {
                        SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.width(ICON_SIZE);
                        SymbolGlyph.height(ICON_SIZE);
                        SymbolGlyph.position({
                            x: this.blockWidth - 52,
                            y: -MARGIN_EIGHT
                        });
                    }, SymbolGlyph);
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }
    HeaderTitleBuilder(a86 = null) {
        this.observeComponentCreation2((n86, o86) => {
            __Common__.create();
            __Common__.id(ADD_TITLE_BAR_ID);
            __Common__.visibility(!this.menuSwitch ? Visibility.Visible : Visibility.None);
            __Common__.onVisibleAreaChange([0.0, 1.0], (p86, q86) => {
                if (p86) {
                    this.pointToAddTitleBarEditButton();
                }
                else {
                    if (this.isPointToEditTitleBarSaveButton) {
                        let r86 = ({
                            type: 'announceForAccessibility',
                            bundleName: this.bundleName,
                            triggerAction: 'common',
                            textAnnouncedForAccessibility: getContext().resourceManager
                                .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE)
                        });
                        accessibility.sendAccessibilityEvent(r86);
                    }
                }
            });
        }, __Common__);
        {
            this.observeComponentCreation2((j86, k86) => {
                if (k86) {
                    let l86 = new ComposeTitleBar(this, {
                        title: this.options.normalTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        menuItems: [{
                            value: { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_edit'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            symbolStyle: (new SymbolGlyphModifier({ 'id': -1, 'type': 40000, params: ['sys.symbol.square_and_pencil'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })),
                            isEnabled: true,
                            label: { 'id': -1, 'type': 10003, params: ['sys.string.gridobjectsortcomponent_accessibility_header_edit_button'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            accessibilityText: { 'id': -1, 'type': 10003, params: ['sys.string.gridobjectsortcomponent_accessibility_header_edit_button'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            action: () => {
                                this.goEdit();
                            }
                        }]
                    }, undefined, j86, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 948, col: 5 });
                    ViewPU.create(l86);
                    let j = () => {
                        return {
                            title: this.options.normalTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_chanel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            menuItems: [{
                                value: { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_edit'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                symbolStyle: (new SymbolGlyphModifier({ 'id': -1, 'type': 40000, params: ['sys.symbol.square_and_pencil'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })),
                                isEnabled: true,
                                label: { 'id': -1, 'type': 10003, params: ['sys.string.gridobjectsortcomponent_accessibility_header_edit_button'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                accessibilityText: { 'id': -1, 'type': 10003, params: ['sys.string.gridobjectsortcomponent_accessibility_header_edit_button'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                action: () => {
                                    this.goEdit();
                                }
                            }]
                        };
                    };
                    l86.paramsGenerator_ = j;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(j86, {});
                }
            }, { name: 'ComposeTitleBar' });
        }
        __Common__.pop();
        this.observeComponentCreation2((f86, g86) => {
            __Common__.create();
            __Common__.id(EDIT_TITLE_BAR_ID);
            __Common__.visibility(this.menuSwitch ? Visibility.Visible : Visibility.None);
            __Common__.onVisibleAreaChange([0.0, 1.0], (h86, i86) => {
                if (h86) {
                    this.pointToEditTitleBarSaveButton();
                }
            });
        }, __Common__);
        {
            this.observeComponentCreation2((b86, c86) => {
                if (c86) {
                    let d86 = new EditableTitleBar(this, {
                        leftIconStyle: EditableLeftIconType.Cancel,
                        isSaveIconRequired: false,
                        menuItems: [{
                            value: { 'id': -1, 'type': 40000, params: ['sys.symbol.checkmark'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            label: { 'id': -1, 'type': 10003, params: ['sys.string.gridobjectsortcomponent_accessibility_complete_button'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            accessibilityText: { 'id': -1, 'type': 10003, params: ['sys.string.gridobjectsortcomponent_accessibility_complete_button'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            action: () => {
                                this.saveClick = true;
                                this.onSaveEdit();
                            }
                        }],
                        title: this.options.editTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_edit'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        onCancel: () => {
                            this.cancelEdit();
                        },
                    }, undefined, b86, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 979, col: 5 });
                    ViewPU.create(d86);
                    let i = () => {
                        return {
                            leftIconStyle: EditableLeftIconType.Cancel,
                            isSaveIconRequired: false,
                            menuItems: [{
                                value: { 'id': -1, 'type': 40000, params: ['sys.symbol.checkmark'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                label: { 'id': -1, 'type': 10003, params: ['sys.string.gridobjectsortcomponent_accessibility_complete_button'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                accessibilityText: { 'id': -1, 'type': 10003, params: ['sys.string.gridobjectsortcomponent_accessibility_complete_button'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                action: () => {
                                    this.saveClick = true;
                                    this.onSaveEdit();
                                }
                            }],
                            title: this.options.editTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_title_edit'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            onCancel: () => {
                                this.cancelEdit();
                            }
                        };
                    };
                    d86.paramsGenerator_ = i;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(b86, {});
                }
            }, { name: 'EditableTitleBar' });
        }
        __Common__.pop();
    }
    ImageTextBuilder(d85, e85, f85 = null) {
        this.observeComponentCreation2((y85, z85) => {
            Column.create();
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((w85, x85) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Center);
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.height(this.imageItemWidth);
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.borderRadius((this.isTouchDown && d85.id === this.content.id) ||
                d85.id === this.hoverId ? this.touchBorderRadius : 0);
            Column.backgroundColor(this.isTouchDown && d85.id === this.content.id
                ? this.touchDown : d85.id === this.hoverId ? this.hoverBackgroundColor : '');
            Column.scale(d85.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
        }, Column);
        this.observeComponentCreation2((m85, n85) => {
            If.create();
            if (d85.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u85, v85) => {
                        SymbolGlyph.create();
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.attributeModifier.bind(this)(d85.symbolStyle);
                        SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((o85, p85) => {
                        If.create();
                        if (d85.url === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((s85, t85) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((q85, r85) => {
                                    Image.create(d85.url);
                                    Image.draggable(false);
                                    Image.height(this.options.imageSize || IMAGE_DEFAULT);
                                    Image.width((this.options.imageSize || IMAGE_DEFAULT));
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((k85, l85) => {
            Text.create(d85.text);
            Text.textAlign(TextAlign.Center);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.margin({ top: 2 });
            Text.maxLines(TEXT_MAX_LINES);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
            Text.padding({
                top: PADDING_EIGHT,
                bottom: PADDING_EIGHT
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((i85, j85) => {
            SymbolGlyph.create(this.imageTextAddIcon(d85));
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.visibility(e85 === 'add' ? this.imageTextAddIconVisible(d85) : Visibility.Hidden);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.height(ICON_SIZE);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            SymbolGlyph.onClick(() => this.handleAddIconClick(d85));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_BUTTON, this.getAccessibilityText(d85.text)));
        }, SymbolGlyph);
        this.observeComponentCreation2((g85, h85) => {
            SymbolGlyph.create(this.imageTextRemoveIcon(d85));
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.visibility(e85 === 'delete' && this.gridComState ? Visibility.Visible :
            Visibility.Hidden);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.height(ICON_SIZE);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            SymbolGlyph.onClick(() => this.handleDeleteClick(d85));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DELETE, this.getAccessibilityText(d85.text)));
        }, SymbolGlyph);
        Column.pop();
        Column.pop();
    }
    handleAddIconClick(y84) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.scaleIcon = 0;
        this.content = y84;
        const z84 = this.unSelected.findIndex(c85 => c85.id === y84.id);
        this.editGridDataLength = this.selected.length + 1;
        const a85 = this.getEditItemGridPosition(this.selected, z84);
        this.unSelectedIndex = z84;
        this.arrayUnSelectIsChange = 1;
        this.clickAddBtn = true;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING,
            onFinish: () => {
                if (!this.selected.some(b85 => b85.id === y84.id)) {
                    this.arrayUnSelectIsChange = 2;
                    this.scaleIcon = 1;
                    this.selected.push(y84);
                    this.unSelected.splice(z84, 1);
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
            this.addItemMoveX = a85.x;
            this.addItemMoveY = a85.y;
        });
        this.readFlag = false;
        this.readIndex4EditArea = this.editGridDataLength - 1;
        this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM_ADD, this.getAccessibilityText(this.content?.text ?? ''), Math.floor(this.readIndex4EditArea / this.colNum) + 1, this.readIndex4EditArea % this.colNum + 1);
    }
    TextBlockBuilder(k84, l84 = null) {
        this.observeComponentCreation2((w84, x84) => {
            Stack.create();
            Stack.scale(k84.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((u84, v84) => {
            Row.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
            } : { duration: 0 });
            Row.borderRadius(50);
            Row.width(this.clickRemoveBtn && k84.id === this.content.id ?
                this.textItemEditWidth + 8 : this.textItemEditWidth);
            Row.translate(this.gridComState ? this.clickRemoveBtn &&
                k84.id === this.content.id ? { x: 0 } : { x: -4 } : { x: 0 });
            Row.height('100%');
            Context.animation(null);
            Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((s84, t84) => {
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
            Flex.backgroundColor(this.isTouchDown && k84.id === this.content.id ? this.touchDown
                : k84.id === this.hoverId ? this.hoverBackgroundColor
                    : '');
            Flex.width(this.clickRemoveBtn && k84.id === this.content.id ?
                this.textItemEditWidth + 8 : this.textItemEditWidth);
            Flex.translate(this.gridComState ? this.clickRemoveBtn && k84.id === this.content.id ?
                { x: 0 } : { x: -4 } : { x: 0 });
            Flex.height('100%');
            Context.animation(null);
        }, Flex);
        this.observeComponentCreation2((q84, r84) => {
            SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.plus'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            SymbolGlyph.fontSize(this.getAdaptiveSymbolFontSize());
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.visibility(this.clickRemoveBtn && k84.id === this.content.id ? Visibility.Visible : Visibility.None);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((o84, p84) => {
            Text.create(k84.text);
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((m84, n84) => {
            SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER,
            });
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, centerX: '50%' } });
            SymbolGlyph.scale(k84.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {});
            SymbolGlyph.visibility(this.gridComState ? 0 : 1);
            SymbolGlyph.position({
                x: this.blockWidth - 52,
                y: -MARGIN_EIGHT
            });
            Context.animation(null);
            SymbolGlyph.onClick(() => this.handleDeleteClick(k84));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DELETE, this.getAccessibilityText(k84.text)));
        }, SymbolGlyph);
        Flex.pop();
        Stack.pop();
    }
    TextBlockAddItemBuilder(u83, v83 = null) {
        this.observeComponentCreation2((i84, j84) => {
            Stack.create();
            Stack.scale(u83.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } : {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((g84, h84) => {
            Row.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Row.borderRadius(50);
            Row.height('100%');
            Row.width(this.addIconShow && u83.id === this.content.id ? this.textItemEditWidth : '100%');
            Row.translate(this.addIconShow && u83.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Row.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((e84, f84) => {
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
            Flex.backgroundColor(this.isTouchDown && u83.id === this.content.id ? this.touchDown
                : u83.id === this.hoverId ? this.hoverBackgroundColor : '');
            Flex.width(this.addIconShow && u83.id === this.content.id ? this.textItemEditWidth : '100%');
            Flex.translate(this.addIconShow && u83.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Flex.height('100%');
        }, Flex);
        this.observeComponentCreation2((c84, d84) => {
            SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.plus'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            SymbolGlyph.fontSize(this.getAdaptiveSymbolFontSize());
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
            SymbolGlyph.visibility(this.addIconShow && u83.id === this.content.id ? Visibility.None : Visibility.Visible);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((a84, b84) => {
            Text.create(u83.text);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Start);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((w83, x83) => {
            If.create();
            if (this.gridComState && this.addIconShow && u83.id === this.content.id) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y83, z83) => {
                        SymbolGlyph.create({ 'id': -1, 'type': 40000, params: ['sys.symbol.minus_circle_fill'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.width(ICON_SIZE);
                        SymbolGlyph.translate(this.gridComState ? { x: -MARGIN_EIGHT } : {});
                        SymbolGlyph.position({
                            x: this.blockWidth - 44,
                            y: -MARGIN_EIGHT
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
            duration: ENTER_EXIT_ICON_DURATION,
            curve: LONG_TOUCH_SCALE
        }, () => {
            this.longScaleOnePointTwo = 1;
        });
    }
    AddTagBuilder(z82 = null) {
        this.observeComponentCreation2((s83, t83) => {
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
            Grid.accessibilityLevel(NO);
        }, Grid);
        this.observeComponentCreation2((a83, b83) => {
            ForEach.create();
            const f = (e83, f83) => {
                const g83 = e83;
                {
                    const g = (q83, r83) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.clickRemoveBtn ? DRAG_SPRING : f83 === this.unSelectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getAddAreaItemTranslate(f83));
                        Context.animation(null);
                    };
                    const h = () => {
                        this.observeComponentCreation2(g, GridItem);
                        this.observeComponentCreation2((l83, m83) => {
                            Stack.create();
                            Stack.onHover((p83) => {
                                if (p83) {
                                    this.hoverId = g83.id;
                                }
                                else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.onTouch(this.isOpenAccessibility ? undefined : (o83) => {
                                this.handleAddItemTouch(o83, g83);
                            });
                            Stack.onClick(this.isOpenAccessibility ? () => this.handleAddItemClick(g83) : undefined);
                            Gesture.create(GesturePriority.Low);
                            LongPressGesture.create({ repeat: true });
                            LongPressGesture.onAction((n83) => {
                                if (!this.gridComState) {
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: COMMON_BEZIER,
                                    }, () => {
                                        this.addAreaLongPressGesture = true;
                                        this.gridComState = true;
                                    });
                                    this.menuSwitch = true;
                                    setTimeout(() => {
                                        this.pointToRepeat(ADD);
                                    }, ENTER_EXIT_ICON_DURATION);
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
                                this.onAddTagLongPressEnd();
                            });
                            LongPressGesture.onActionCancel(() => {
                                this.onAddTagLongPressEnd();
                            });
                            LongPressGesture.pop();
                            Gesture.pop();
                            Stack.id(`add_grid_item_${f83}`);
                            Stack.onAppear(() => {
                                if (!this.readFlag && f83 === this.readIndex4AddArea) {
                                    this.pointToAddArea();
                                }
                            });
                            Stack.accessibilityGroup(true);
                            Stack.accessibilityLevel(YES);
                            Stack.accessibilityText(this.readFlag ?
                            this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM, this.getAccessibilityText(g83.text ?? '')) :
                            this.textAnnouncedForAccessibility);
                            Stack.accessibilityDescription(this.readFlag ? this.getAddTagGridItemAccessibilityDesc() : ' ');
                        }, Stack);
                        this.observeComponentCreation2((j83, k83) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(g83, ADD);
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockAddItemBuilder.bind(this)(g83);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    h();
                }
            };
            this.forEachUpdateFunction(a83, this.unSelected, f, (d83) => d83.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
    }
    getAddTagGridItemAccessibilityDesc() {
        return this.options?.type === GridObjectSortComponentType.IMAGE_TEXT ?
            this.menuSwitch ? ' ' : this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC) :
            this.menuSwitch ? this.getStringByResourceToken(ACCESSIBILITY_DOUBLE_CLICK) :
            this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_TEXT_ITEM_DESC);
    }
    handleAddItemTouch(t82, u82) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        if (t82.type === TouchType.Down) {
            this.content = u82;
            this.isTouchDown = true;
        }
        if (t82.type === TouchType.Cancel) {
            this.isTouchDown = false;
            return;
        }
        if (t82.type === TouchType.Up) {
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
            const v82 = this.unSelected.findIndex(y82 => y82.id === u82.id);
            this.editGridDataLength = this.selected.length + 1;
            const w82 = this.getEditItemGridPosition(this.selected, v82);
            this.content = u82;
            this.unSelectedIndex = v82;
            this.clickAddBtn = true;
            this.arrayUnSelectIsChange = 1;
            this.calcGridHeight();
            Context.animateTo({ curve: REMOVE_ADD_SPRING, onFinish: () => {
                if (!this.selected.some(x82 => x82.id === u82.id)) {
                    this.scaleIcon = 1;
                    this.scaleAddIcon = 0;
                    this.selected.push(u82);
                    this.unSelected.splice(v82, 1);
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
                this.addItemMoveX = w82.x;
                this.addItemMoveY = w82.y;
            });
            this.readFlag = false;
            this.readIndex4EditArea = this.editGridDataLength - 1;
            this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM_ADD, this.getAccessibilityText(this.content?.text ?? ''), Math.floor(this.readIndex4EditArea / this.colNum) + 1, this.readIndex4EditArea % this.colNum + 1);
        }
    }
    handleAddItemClick(o82) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.content = o82;
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
        const p82 = this.unSelected.findIndex(s82 => s82.id === o82.id);
        this.editGridDataLength = this.selected.length + 1;
        const q82 = this.getEditItemGridPosition(this.selected, p82);
        this.content = o82;
        this.unSelectedIndex = p82;
        this.clickAddBtn = true;
        this.arrayUnSelectIsChange = 1;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING,
            onFinish: () => {
                if (!this.selected.some(r82 => r82.id === o82.id)) {
                    this.scaleIcon = 1;
                    this.scaleAddIcon = 0;
                    this.selected.push(o82);
                    this.unSelected.splice(p82, 1);
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
            }
        }, () => {
            this.addItemMoveX = q82.x;
            this.addItemMoveY = q82.y;
        });
        this.readFlag = false;
        this.readIndex4EditArea = this.editGridDataLength - 1;
        this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM_ADD, this.getAccessibilityText(this.content?.text ?? ''), Math.floor(this.readIndex4EditArea / this.colNum) + 1, this.readIndex4EditArea % this.colNum + 1);
    }
    EditTagBuilder(d81 = null) {
        this.observeComponentCreation2((l82, m82) => {
            Column.create();
            Column.accessibilityLevel((this.selected.length === 0) ? YES : NO);
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction(() => {
                this.menuSwitch = true;
            });
            LongPressGesture.onActionEnd(() => {
                let n82 = ({
                    type: 'announceForAccessibility',
                    bundleName: this.bundleName,
                    triggerAction: 'common',
                    textAnnouncedForAccessibility: getContext().resourceManager
                        .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE)
                });
                accessibility.sendAccessibilityEvent(n82);
            });
            LongPressGesture.pop();
            Gesture.pop();
            Column.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_RESIDENT_AREA));
            Column.accessibilityDescription(this.menuSwitch ? ' ' :
            this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC));
        }, Column);
        this.observeComponentCreation2((x81, y81) => {
            Grid.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            } : { duration: 0 });
            Grid.accessibilityLevel(NO);
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((k82) => {
                if (!this.gridComState) {
                    Context.animateTo({
                        duration: ENTER_EXIT_ICON_DURATION,
                        curve: COMMON_BEZIER
                    }, () => {
                        this.gridComState = true;
                    });
                    this.menuSwitch = true;
                    setTimeout(() => {
                        this.pointToRepeat(EDIT);
                    }, ENTER_EXIT_ICON_DURATION);
                }
                else {
                    Context.animateTo({
                        duration: ENTER_EXIT_ICON_DURATION,
                        curve: LONG_TOUCH_SCALE
                    }, () => {
                        this.longScaleOnePointTwo = 1.05;
                    });
                    if (k82.repeat && !this.vibrationDone) {
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
                left: ROW_GAP,
                right: ROW_GAP
            });
            Grid.height(this.editGridHeight);
            Context.animation(null);
            Grid.onItemDragStart((i82, j82) => {
                this.itemIndex = j82;
                this.selectedIndex = -1;
                if (!this.gridComState) {
                    return;
                }
                this.isStartDrag = true;
                this.insertIndex = j82;
                this.dragContent = this.selected[j82];
                this.dragContentIndex = j82;
                this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_START, this.getAccessibilityText(this.dragContent?.text ?? ''));
                this.sendAccessibility();
                return { builder: () => {
                    this.PixelMapBuilder.call(this, this.dragContent?.symbolStyle || this.dragContent?.url, this.dragContent?.text);
                } };
            });
            Grid.onItemDrop((e82, f82, g82, h82) => {
                this.insertItem(f82, g82);
            });
            Grid.onItemDragMove((b82, c82, d82) => this.onDragMoveEvent(b82, c82, d82));
            Grid.onItemDragLeave((z81, a82) => {
                this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_ILLEGAL_AREA);
                this.sendAccessibility();
            });
        }, Grid);
        this.observeComponentCreation2((e81, f81) => {
            ForEach.create();
            const c = (i81, j81) => {
                const k81 = i81;
                {
                    const d = (v81, w81) => {
                        GridItem.create(() => { }, false);
                        Context.animation({
                            curve: this.isStartDrag ? DRAG_SPRING : j81 === this.selectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING,
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getShowAreaItemTranslate(j81));
                        Context.animation(null);
                        GridItem.visibility(k81.visibility);
                    };
                    const e = () => {
                        this.observeComponentCreation2(d, GridItem);
                        this.observeComponentCreation2((p81, q81) => {
                            Stack.create();
                            Stack.onHover((u81) => {
                                if (u81) {
                                    this.hoverId = k81.id;
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
                            Stack.onTouch((t81) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (t81.type === TouchType.Down) {
                                    this.content = k81;
                                    this.isTouchDown = true;
                                }
                                if (t81.type === TouchType.Up || t81.type === TouchType.Cancel) {
                                    this.isTouchDown = false;
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: LONG_TOUCH_SCALE
                                    }, () => {
                                        this.longScaleOnePointTwo = 1;
                                    });
                                }
                            });
                            Stack.id(`edit_grid_item_${j81}`);
                            Stack.onVisibleAreaChange([0.0, 1.0], (r81, s81) => {
                                if (r81) {
                                    if (!this.readFlag && j81 === this.readIndex4EditArea) {
                                        this.pointToNextOne();
                                    }
                                }
                            });
                            Stack.accessibilityGroup(true);
                            Stack.accessibilityLevel(YES);
                            Stack.accessibilityText(this.readFlag ?
                            this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM, this.getAccessibilityText(k81.text)) :
                            this.textAnnouncedForAccessibility);
                            Stack.accessibilityDescription(this.readFlag ?
                            this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DESC) : '');
                        }, Stack);
                        this.observeComponentCreation2((n81, o81) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(k81, DELETE);
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockBuilder.bind(this)(k81);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    e();
                }
            };
            this.forEachUpdateFunction(e81, this.selected, c, (h81) => h81.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
        Column.pop();
    }
    pointToRepeat(x80) {
        this.readFlag = false;
        let y80 = '';
        let z80 = -1;
        if (x80 === ADD) {
            z80 = this.unSelected.findIndex(c81 => c81.id === this.content.id);
            this.readIndex4AddArea = z80;
            y80 = `add_grid_item_${z80}`;
        }
        else {
            z80 = this.selected.findIndex(b81 => b81.id === this.content.id);
            this.readIndex4EditArea = z80;
            y80 = `edit_grid_item_${z80}`;
        }
        this.textAnnouncedForAccessibility = getContext().resourceManager
            .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE);
        let a81 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: y80
        });
        accessibility.sendAccessibilityEvent(a81).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4EditArea = -1;
                this.readIndex4AddArea = -1;
                this.textAnnouncedForAccessibility = '';
            }, ENTER_EXIT_ICON_DURATION);
        });
    }
    insertItem(v80, w80) {
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
        if (w80 !== -1) {
            this.selected.splice(v80, 1);
            this.selected.splice(w80, 0, this.dragContent);
            this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP, Math.floor(w80 / this.colNum) + 1, w80 % this.colNum + 1);
        }
        else {
            this.insertIndex = v80;
            this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP, Math.floor(v80 / this.colNum) + 1, v80 % this.colNum + 1);
        }
        this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
        this.dragContent.visibility = Visibility.Visible;
        this.calcGridHeight();
        this.readFlag = false;
        this.readIndex4EditArea = this.insertIndex;
    }
    pointToNextOne() {
        let u80 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: `edit_grid_item_${this.readIndex4EditArea}`
        });
        accessibility.sendAccessibilityEvent(u80).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4EditArea = -1;
                this.readIndex4AddArea = -1;
                this.textAnnouncedForAccessibility = '';
            }, ENTER_EXIT_ICON_DURATION);
        });
    }
    calcAreaInfo() {
        this.calcColNum();
        this.blockWidth = this.getBlockWidth();
        this.textItemEditWidth = this.gridComState ? this.blockWidth - 24 : this.blockWidth - 16;
        this.imageItemWidth = this.blockWidth - 16;
        this.calcTextItemEditHeight();
        this.blockHeight = this.imageText ? this.imageItemWidth + EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN : this.gridComState ?
            this.textItemEditHeight + EDIT_BLOCK_TEXT_ITEM_SAFE_MARGIN :
            this.textItemEditHeight + DEFAULT_BLOCK_TEXT_ITEM_SAFE_MARGIN;
        this.calcGridHeight();
    }
    initialRender() {
        this.observeComponentCreation2((s80, t80) => {
            Column.create();
            Column.width('100%');
            Column.height('90%');
        }, Column);
        this.HeaderTitleBuilder.bind(this)();
        this.observeComponentCreation2((q80, r80) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((m80, n80) => {
            Column.create();
            Column.onAreaChange((o80, p80) => {
                this.areaWidth = Number(p80.width);
                this.calcAreaInfo();
            });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((k80, l80) => {
            __Common__.create();
            __Common__.margin({ bottom: MARGIN_EIGHT });
        }, __Common__);
        {
            this.observeComponentCreation2((g80, h80) => {
                if (h80) {
                    let i80 = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, g80, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 1846, col: 11 });
                    ViewPU.create(i80);
                    let b = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.showAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    i80.paramsGenerator_ = b;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(g80, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_sort'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        icon: '',
                        operationType: OperationType.BUTTON
                    });
                }
            }, { name: 'SubHeader' });
        }
        __Common__.pop();
        this.EditTagBuilder.bind(this)();
        this.observeComponentCreation2((c80, d80) => {
            __Common__.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            __Common__.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } : {});
            Context.animation(null);
            __Common__.margin({ bottom: MARGIN_EIGHT });
            __Common__.onAreaChange((e80, f80) => {
                this.subTitleHeight = Number(f80.height);
            });
        }, __Common__);
        {
            this.observeComponentCreation2((y79, z79) => {
                if (z79) {
                    let a80 = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, y79, () => { }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 1855, col: 11 });
                    ViewPU.create(a80);
                    let a = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.addAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    a80.paramsGenerator_ = a;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(y79, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || { 'id': -1, 'type': 10003, params: ['sys.string.ohos_grid_edit_subtitle_add'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        icon: '',
                        operationType: OperationType.BUTTON
                    });
                }
            }, { name: 'SubHeader' });
        }
        __Common__.pop();
        this.AddTagBuilder.bind(this)();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }
    getStringByResourceToken(v79, ...w79) {
        if (v79) {
            try {
                return getContext(this).resourceManager.getStringByNameSync(v79, ...w79);
            }
            catch (x79) {
                hilog.error(0x3900, 'Ace', `GridObjectSortComponent getStringByResourceToken, error: ${x79.toString()}`);
            }
        }
        return '';
    }
    getAccessibilityText(q79) {
        try {
            let u79 = '';
            if (typeof q79 === 'string') {
                u79 = q79;
            }
            else {
                if (q79.id === -1) {
                    u79 = getContext()?.resourceManager?.getStringByNameSync(q79.params?.[0].split('.').pop());
                }
                else {
                    u79 = getContext()?.resourceManager?.getStringSync(q79);
                }
            }
            return u79;
        }
        catch (r79) {
            let s79 = r79.code;
            let t79 = r79.message;
            hilog.error(0x3900, 'Ace', `GridObjectSortComponent getAccessibilityText error, code: ${s79}, message: ${t79}`);
            return '';
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    GridObjectSortComponent, GridObjectSortComponentType
}
