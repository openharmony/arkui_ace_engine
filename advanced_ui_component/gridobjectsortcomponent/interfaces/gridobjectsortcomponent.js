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
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
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
const SEND_EVENT_DURATION = 100;
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
(function (w107) {
    w107['IMAGE_TEXT'] = 'image_text';
    w107['TEXT'] = 'text';
})(GridObjectSortComponentType || (GridObjectSortComponentType = {}));

export class GridObjectSortComponent extends ViewPU {
    constructor(n107, o107, p107, q107 = -1, r107 = undefined, s107) {
        super(n107, p107, q107, s107);
        if (typeof r107 === 'function') {
            this.paramsGenerator_ = r107;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(o107.options, this, 'options');
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
        this.__isOpenAccessibility =
            new ObservedPropertySimplePU(accessibility.isScreenReaderOpenSync(), this, 'isOpenAccessibility');
        this.callbackId = undefined;
        this.colNum = COL_IMAGE_TEXT;
        this.vibrationDone = false;
        this.touchDown = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_click_effect'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.touchBorderRadius = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_corner_radius_clicked'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.hoverBackgroundColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.imageText = false;
        this.onSave = undefined;
        this.onCancel = undefined;
        this.isFollowingSystemFontScale = false;
        this.maxAppFontScale = 1;
        this.bundleName = '';
        this.__readFlag = new ObservedPropertySimplePU(true, this, 'readFlag');
        this.__readIndex4AddArea = new ObservedPropertySimplePU(-1, this, 'readIndex4AddArea');
        this.__readIndex4EditArea = new ObservedPropertySimplePU(-1, this, 'readIndex4EditArea');
        this.__isPointToAddTitleBarEditButton =
            new ObservedPropertySimplePU(false, this, 'isPointToAddTitleBarEditButton');
        this.__isPointToEditTitleBarSaveButton =
            new ObservedPropertySimplePU(false, this, 'isPointToEditTitleBarSaveButton');
        this.preTextAnnouncedForAccessibility = '';
        this.textAnnouncedForAccessibility = '';
        this.envCallback = {
            onConfigurationUpdated: (u107) => {
                let v107 = this.getUIContext();
                this.fontSizeScale = this.decideFontScale(v107);
                this.fontWeightScale = u107.fontWeightScale;
            },
            onMemoryLevel: (t107) => {
            }
        };
        this.setInitiallyProvidedValue(o107);
        this.declareWatch('gridComState', this.onGridComStateChange);
        this.declareWatch('fontSizeScale', this.calcAreaInfo);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(m107) {
        if (m107.options === undefined) {
            this.__options.set({});
        }
        if (m107.dataList !== undefined) {
            this.dataList = m107.dataList;
        }
        if (m107.selected !== undefined) {
            this.selected = m107.selected;
        }
        if (m107.unSelected !== undefined) {
            this.unSelected = m107.unSelected;
        }
        if (m107.copySelected !== undefined) {
            this.copySelected = m107.copySelected;
        }
        if (m107.copyUnSelected !== undefined) {
            this.copyUnSelected = m107.copyUnSelected;
        }
        if (m107.content !== undefined) {
            this.content = m107.content;
        }
        if (m107.dragContent !== undefined) {
            this.dragContent = m107.dragContent;
        }
        if (m107.dragContentIndex !== undefined) {
            this.dragContentIndex = m107.dragContentIndex;
        }
        if (m107.hoverId !== undefined) {
            this.hoverId = m107.hoverId;
        }
        if (m107.gridComState !== undefined) {
            this.gridComState = m107.gridComState;
        }
        if (m107.menuSwitch !== undefined) {
            this.menuSwitch = m107.menuSwitch;
        }
        if (m107.areaWidth !== undefined) {
            this.areaWidth = m107.areaWidth;
        }
        if (m107.blockWidth !== undefined) {
            this.blockWidth = m107.blockWidth;
        }
        if (m107.blockHeight !== undefined) {
            this.blockHeight = m107.blockHeight;
        }
        if (m107.longScaleOnePointTwo !== undefined) {
            this.longScaleOnePointTwo = m107.longScaleOnePointTwo;
        }
        if (m107.scaleGridItemNinetyPercent !== undefined) {
            this.scaleGridItemNinetyPercent = m107.scaleGridItemNinetyPercent;
        }
        if (m107.reboundSize !== undefined) {
            this.reboundSize = m107.reboundSize;
        }
        if (m107.scaleIcon !== undefined) {
            this.scaleIcon = m107.scaleIcon;
        }
        if (m107.addIconShow !== undefined) {
            this.addIconShow = m107.addIconShow;
        }
        if (m107.scaleAddIcon !== undefined) {
            this.scaleAddIcon = m107.scaleAddIcon;
        }
        if (m107.isStartDrag !== undefined) {
            this.isStartDrag = m107.isStartDrag;
        }
        if (m107.insertIndex !== undefined) {
            this.insertIndex = m107.insertIndex;
        }
        if (m107.itemIndex !== undefined) {
            this.itemIndex = m107.itemIndex;
        }
        if (m107.editGridDataLength !== undefined) {
            this.editGridDataLength = m107.editGridDataLength;
        }
        if (m107.isTouchDown !== undefined) {
            this.isTouchDown = m107.isTouchDown;
        }
        if (m107.addItemMoveX !== undefined) {
            this.addItemMoveX = m107.addItemMoveX;
        }
        if (m107.addItemMoveY !== undefined) {
            this.addItemMoveY = m107.addItemMoveY;
        }
        if (m107.editItemMoveX !== undefined) {
            this.editItemMoveX = m107.editItemMoveX;
        }
        if (m107.editItemMoveY !== undefined) {
            this.editItemMoveY = m107.editItemMoveY;
        }
        if (m107.unSelectedIndex !== undefined) {
            this.unSelectedIndex = m107.unSelectedIndex;
        }
        if (m107.clickAddBtn !== undefined) {
            this.clickAddBtn = m107.clickAddBtn;
        }
        if (m107.selectedIndex !== undefined) {
            this.selectedIndex = m107.selectedIndex;
        }
        if (m107.clickRemoveBtn !== undefined) {
            this.clickRemoveBtn = m107.clickRemoveBtn;
        }
        if (m107.addAreaLongPressGesture !== undefined) {
            this.addAreaLongPressGesture = m107.addAreaLongPressGesture;
        }
        if (m107.arraySelectIsChange !== undefined) {
            this.arraySelectIsChange = m107.arraySelectIsChange;
        }
        if (m107.arrayUnSelectIsChange !== undefined) {
            this.arrayUnSelectIsChange = m107.arrayUnSelectIsChange;
        }
        if (m107.textItemEditWidth !== undefined) {
            this.textItemEditWidth = m107.textItemEditWidth;
        }
        if (m107.textItemEditHeight !== undefined) {
            this.textItemEditHeight = m107.textItemEditHeight;
        }
        if (m107.imageItemWidth !== undefined) {
            this.imageItemWidth = m107.imageItemWidth;
        }
        if (m107.saveClick !== undefined) {
            this.saveClick = m107.saveClick;
        }
        if (m107.imageTextAddIconShow !== undefined) {
            this.imageTextAddIconShow = m107.imageTextAddIconShow;
        }
        if (m107.imageTextRemoveIconShow !== undefined) {
            this.imageTextRemoveIconShow = m107.imageTextRemoveIconShow;
        }
        if (m107.firstIn !== undefined) {
            this.firstIn = m107.firstIn;
        }
        if (m107.fontSizeScale !== undefined) {
            this.fontSizeScale = m107.fontSizeScale;
        }
        if (m107.fontWeightScale !== undefined) {
            this.fontWeightScale = m107.fontWeightScale;
        }
        if (m107.customColumns !== undefined) {
            this.customColumns = m107.customColumns;
        }
        if (m107.editGridHeight !== undefined) {
            this.editGridHeight = m107.editGridHeight;
        }
        if (m107.addGridHeight !== undefined) {
            this.addGridHeight = m107.addGridHeight;
        }
        if (m107.subTitleHeight !== undefined) {
            this.subTitleHeight = m107.subTitleHeight;
        }
        if (m107.isOpenAccessibility !== undefined) {
            this.isOpenAccessibility = m107.isOpenAccessibility;
        }
        if (m107.callbackId !== undefined) {
            this.callbackId = m107.callbackId;
        }
        if (m107.colNum !== undefined) {
            this.colNum = m107.colNum;
        }
        if (m107.vibrationDone !== undefined) {
            this.vibrationDone = m107.vibrationDone;
        }
        if (m107.touchDown !== undefined) {
            this.touchDown = m107.touchDown;
        }
        if (m107.touchBorderRadius !== undefined) {
            this.touchBorderRadius = m107.touchBorderRadius;
        }
        if (m107.hoverBackgroundColor !== undefined) {
            this.hoverBackgroundColor = m107.hoverBackgroundColor;
        }
        if (m107.imageText !== undefined) {
            this.imageText = m107.imageText;
        }
        if (m107.onSave !== undefined) {
            this.onSave = m107.onSave;
        }
        if (m107.onCancel !== undefined) {
            this.onCancel = m107.onCancel;
        }
        if (m107.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = m107.isFollowingSystemFontScale;
        }
        if (m107.maxAppFontScale !== undefined) {
            this.maxAppFontScale = m107.maxAppFontScale;
        }
        if (m107.bundleName !== undefined) {
            this.bundleName = m107.bundleName;
        }
        if (m107.readFlag !== undefined) {
            this.readFlag = m107.readFlag;
        }
        if (m107.readIndex4AddArea !== undefined) {
            this.readIndex4AddArea = m107.readIndex4AddArea;
        }
        if (m107.readIndex4EditArea !== undefined) {
            this.readIndex4EditArea = m107.readIndex4EditArea;
        }
        if (m107.isPointToAddTitleBarEditButton !== undefined) {
            this.isPointToAddTitleBarEditButton = m107.isPointToAddTitleBarEditButton;
        }
        if (m107.isPointToEditTitleBarSaveButton !== undefined) {
            this.isPointToEditTitleBarSaveButton = m107.isPointToEditTitleBarSaveButton;
        }
        if (m107.preTextAnnouncedForAccessibility !== undefined) {
            this.preTextAnnouncedForAccessibility = m107.preTextAnnouncedForAccessibility;
        }
        if (m107.textAnnouncedForAccessibility !== undefined) {
            this.textAnnouncedForAccessibility = m107.textAnnouncedForAccessibility;
        }
        if (m107.envCallback !== undefined) {
            this.envCallback = m107.envCallback;
        }
    }

    updateStateVars(l107) {
        this.__options.reset(l107.options);
    }

    purgeVariableDependenciesOnElmtId(k107) {
        this.__options.purgeDependencyOnElmtId(k107);
        this.__selected.purgeDependencyOnElmtId(k107);
        this.__unSelected.purgeDependencyOnElmtId(k107);
        this.__copySelected.purgeDependencyOnElmtId(k107);
        this.__copyUnSelected.purgeDependencyOnElmtId(k107);
        this.__content.purgeDependencyOnElmtId(k107);
        this.__dragContent.purgeDependencyOnElmtId(k107);
        this.__dragContentIndex.purgeDependencyOnElmtId(k107);
        this.__hoverId.purgeDependencyOnElmtId(k107);
        this.__gridComState.purgeDependencyOnElmtId(k107);
        this.__menuSwitch.purgeDependencyOnElmtId(k107);
        this.__areaWidth.purgeDependencyOnElmtId(k107);
        this.__blockWidth.purgeDependencyOnElmtId(k107);
        this.__blockHeight.purgeDependencyOnElmtId(k107);
        this.__longScaleOnePointTwo.purgeDependencyOnElmtId(k107);
        this.__scaleGridItemNinetyPercent.purgeDependencyOnElmtId(k107);
        this.__reboundSize.purgeDependencyOnElmtId(k107);
        this.__scaleIcon.purgeDependencyOnElmtId(k107);
        this.__addIconShow.purgeDependencyOnElmtId(k107);
        this.__scaleAddIcon.purgeDependencyOnElmtId(k107);
        this.__isStartDrag.purgeDependencyOnElmtId(k107);
        this.__insertIndex.purgeDependencyOnElmtId(k107);
        this.__itemIndex.purgeDependencyOnElmtId(k107);
        this.__editGridDataLength.purgeDependencyOnElmtId(k107);
        this.__isTouchDown.purgeDependencyOnElmtId(k107);
        this.__addItemMoveX.purgeDependencyOnElmtId(k107);
        this.__addItemMoveY.purgeDependencyOnElmtId(k107);
        this.__editItemMoveX.purgeDependencyOnElmtId(k107);
        this.__editItemMoveY.purgeDependencyOnElmtId(k107);
        this.__unSelectedIndex.purgeDependencyOnElmtId(k107);
        this.__clickAddBtn.purgeDependencyOnElmtId(k107);
        this.__selectedIndex.purgeDependencyOnElmtId(k107);
        this.__clickRemoveBtn.purgeDependencyOnElmtId(k107);
        this.__addAreaLongPressGesture.purgeDependencyOnElmtId(k107);
        this.__arraySelectIsChange.purgeDependencyOnElmtId(k107);
        this.__arrayUnSelectIsChange.purgeDependencyOnElmtId(k107);
        this.__textItemEditWidth.purgeDependencyOnElmtId(k107);
        this.__textItemEditHeight.purgeDependencyOnElmtId(k107);
        this.__imageItemWidth.purgeDependencyOnElmtId(k107);
        this.__saveClick.purgeDependencyOnElmtId(k107);
        this.__imageTextAddIconShow.purgeDependencyOnElmtId(k107);
        this.__imageTextRemoveIconShow.purgeDependencyOnElmtId(k107);
        this.__firstIn.purgeDependencyOnElmtId(k107);
        this.__fontSizeScale.purgeDependencyOnElmtId(k107);
        this.__fontWeightScale.purgeDependencyOnElmtId(k107);
        this.__customColumns.purgeDependencyOnElmtId(k107);
        this.__editGridHeight.purgeDependencyOnElmtId(k107);
        this.__addGridHeight.purgeDependencyOnElmtId(k107);
        this.__subTitleHeight.purgeDependencyOnElmtId(k107);
        this.__isOpenAccessibility.purgeDependencyOnElmtId(k107);
        this.__readFlag.purgeDependencyOnElmtId(k107);
        this.__readIndex4AddArea.purgeDependencyOnElmtId(k107);
        this.__readIndex4EditArea.purgeDependencyOnElmtId(k107);
        this.__isPointToAddTitleBarEditButton.purgeDependencyOnElmtId(k107);
        this.__isPointToEditTitleBarSaveButton.purgeDependencyOnElmtId(k107);
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

    set options(j107) {
        this.__options.set(j107);
    }

    get selected() {
        return this.__selected.get();
    }

    set selected(i107) {
        this.__selected.set(i107);
    }

    get unSelected() {
        return this.__unSelected.get();
    }

    set unSelected(h107) {
        this.__unSelected.set(h107);
    }

    get copySelected() {
        return this.__copySelected.get();
    }

    set copySelected(g107) {
        this.__copySelected.set(g107);
    }

    get copyUnSelected() {
        return this.__copyUnSelected.get();
    }

    set copyUnSelected(f107) {
        this.__copyUnSelected.set(f107);
    }

    get content() {
        return this.__content.get();
    }

    set content(e107) {
        this.__content.set(e107);
    }

    get dragContent() {
        return this.__dragContent.get();
    }

    set dragContent(d107) {
        this.__dragContent.set(d107);
    }

    get dragContentIndex() {
        return this.__dragContentIndex.get();
    }

    set dragContentIndex(c107) {
        this.__dragContentIndex.set(c107);
    }

    get hoverId() {
        return this.__hoverId.get();
    }

    set hoverId(b107) {
        this.__hoverId.set(b107);
    }

    get gridComState() {
        return this.__gridComState.get();
    }

    set gridComState(a107) {
        this.__gridComState.set(a107);
    }

    get menuSwitch() {
        return this.__menuSwitch.get();
    }

    set menuSwitch(z106) {
        this.__menuSwitch.set(z106);
    }

    get areaWidth() {
        return this.__areaWidth.get();
    }

    set areaWidth(y106) {
        this.__areaWidth.set(y106);
    }

    get blockWidth() {
        return this.__blockWidth.get();
    }

    set blockWidth(x106) {
        this.__blockWidth.set(x106);
    }

    get blockHeight() {
        return this.__blockHeight.get();
    }

    set blockHeight(w106) {
        this.__blockHeight.set(w106);
    }

    get longScaleOnePointTwo() {
        return this.__longScaleOnePointTwo.get();
    }

    set longScaleOnePointTwo(v106) {
        this.__longScaleOnePointTwo.set(v106);
    }

    get scaleGridItemNinetyPercent() {
        return this.__scaleGridItemNinetyPercent.get();
    }

    set scaleGridItemNinetyPercent(u106) {
        this.__scaleGridItemNinetyPercent.set(u106);
    }

    get reboundSize() {
        return this.__reboundSize.get();
    }

    set reboundSize(t106) {
        this.__reboundSize.set(t106);
    }

    get scaleIcon() {
        return this.__scaleIcon.get();
    }

    set scaleIcon(s106) {
        this.__scaleIcon.set(s106);
    }

    get addIconShow() {
        return this.__addIconShow.get();
    }

    set addIconShow(r106) {
        this.__addIconShow.set(r106);
    }

    get scaleAddIcon() {
        return this.__scaleAddIcon.get();
    }

    set scaleAddIcon(q106) {
        this.__scaleAddIcon.set(q106);
    }

    get isStartDrag() {
        return this.__isStartDrag.get();
    }

    set isStartDrag(p106) {
        this.__isStartDrag.set(p106);
    }

    get insertIndex() {
        return this.__insertIndex.get();
    }

    set insertIndex(o106) {
        this.__insertIndex.set(o106);
    }

    get itemIndex() {
        return this.__itemIndex.get();
    }

    set itemIndex(n106) {
        this.__itemIndex.set(n106);
    }

    get editGridDataLength() {
        return this.__editGridDataLength.get();
    }

    set editGridDataLength(m106) {
        this.__editGridDataLength.set(m106);
    }

    get isTouchDown() {
        return this.__isTouchDown.get();
    }

    set isTouchDown(l106) {
        this.__isTouchDown.set(l106);
    }

    get addItemMoveX() {
        return this.__addItemMoveX.get();
    }

    set addItemMoveX(k106) {
        this.__addItemMoveX.set(k106);
    }

    get addItemMoveY() {
        return this.__addItemMoveY.get();
    }

    set addItemMoveY(j106) {
        this.__addItemMoveY.set(j106);
    }

    get editItemMoveX() {
        return this.__editItemMoveX.get();
    }

    set editItemMoveX(i106) {
        this.__editItemMoveX.set(i106);
    }

    get editItemMoveY() {
        return this.__editItemMoveY.get();
    }

    set editItemMoveY(h106) {
        this.__editItemMoveY.set(h106);
    }

    get unSelectedIndex() {
        return this.__unSelectedIndex.get();
    }

    set unSelectedIndex(g106) {
        this.__unSelectedIndex.set(g106);
    }

    get clickAddBtn() {
        return this.__clickAddBtn.get();
    }

    set clickAddBtn(f106) {
        this.__clickAddBtn.set(f106);
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(e106) {
        this.__selectedIndex.set(e106);
    }

    get clickRemoveBtn() {
        return this.__clickRemoveBtn.get();
    }

    set clickRemoveBtn(d106) {
        this.__clickRemoveBtn.set(d106);
    }

    get addAreaLongPressGesture() {
        return this.__addAreaLongPressGesture.get();
    }

    set addAreaLongPressGesture(c106) {
        this.__addAreaLongPressGesture.set(c106);
    }

    get arraySelectIsChange() {
        return this.__arraySelectIsChange.get();
    }

    set arraySelectIsChange(b106) {
        this.__arraySelectIsChange.set(b106);
    }

    get arrayUnSelectIsChange() {
        return this.__arrayUnSelectIsChange.get();
    }

    set arrayUnSelectIsChange(a106) {
        this.__arrayUnSelectIsChange.set(a106);
    }

    get textItemEditWidth() {
        return this.__textItemEditWidth.get();
    }

    set textItemEditWidth(z105) {
        this.__textItemEditWidth.set(z105);
    }

    get textItemEditHeight() {
        return this.__textItemEditHeight.get();
    }

    set textItemEditHeight(y105) {
        this.__textItemEditHeight.set(y105);
    }

    get imageItemWidth() {
        return this.__imageItemWidth.get();
    }

    set imageItemWidth(x105) {
        this.__imageItemWidth.set(x105);
    }

    get saveClick() {
        return this.__saveClick.get();
    }

    set saveClick(w105) {
        this.__saveClick.set(w105);
    }

    get imageTextAddIconShow() {
        return this.__imageTextAddIconShow.get();
    }

    set imageTextAddIconShow(v105) {
        this.__imageTextAddIconShow.set(v105);
    }

    get imageTextRemoveIconShow() {
        return this.__imageTextRemoveIconShow.get();
    }

    set imageTextRemoveIconShow(u105) {
        this.__imageTextRemoveIconShow.set(u105);
    }

    get firstIn() {
        return this.__firstIn.get();
    }

    set firstIn(t105) {
        this.__firstIn.set(t105);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(s105) {
        this.__fontSizeScale.set(s105);
    }

    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }

    set fontWeightScale(r105) {
        this.__fontWeightScale.set(r105);
    }

    get customColumns() {
        return this.__customColumns.get();
    }

    set customColumns(q105) {
        this.__customColumns.set(q105);
    }

    get editGridHeight() {
        return this.__editGridHeight.get();
    }

    set editGridHeight(p105) {
        this.__editGridHeight.set(p105);
    }

    get addGridHeight() {
        return this.__addGridHeight.get();
    }

    set addGridHeight(o105) {
        this.__addGridHeight.set(o105);
    }

    get subTitleHeight() {
        return this.__subTitleHeight.get();
    }

    set subTitleHeight(n105) {
        this.__subTitleHeight.set(n105);
    }

    get isOpenAccessibility() {
        return this.__isOpenAccessibility.get();
    }

    set isOpenAccessibility(m105) {
        this.__isOpenAccessibility.set(m105);
    }

    get readFlag() {
        return this.__readFlag.get();
    }

    set readFlag(l105) {
        this.__readFlag.set(l105);
    }

    get readIndex4AddArea() {
        return this.__readIndex4AddArea.get();
    }

    set readIndex4AddArea(k105) {
        this.__readIndex4AddArea.set(k105);
    }

    get readIndex4EditArea() {
        return this.__readIndex4EditArea.get();
    }

    set readIndex4EditArea(j105) {
        this.__readIndex4EditArea.set(j105);
    }

    get isPointToAddTitleBarEditButton() {
        return this.__isPointToAddTitleBarEditButton.get();
    }

    set isPointToAddTitleBarEditButton(i105) {
        this.__isPointToAddTitleBarEditButton.set(i105);
    }

    get isPointToEditTitleBarSaveButton() {
        return this.__isPointToEditTitleBarSaveButton.get();
    }

    set isPointToEditTitleBarSaveButton(h105) {
        this.__isPointToEditTitleBarSaveButton.set(h105);
    }

    aboutToAppear() {
        this.dataList.length = 50;
        this.selected =
            this.dataList && this.deduplicate(this.dataList).filter(g105 => g105.selected).sort(this.sortBy());
        this.unSelected =
            this.dataList && this.deduplicate(this.dataList).filter(f105 =>!f105.selected).sort(this.sortBy());
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
        try {
            let e105 = this.getUIContext();
            this.isFollowingSystemFontScale = e105.isFollowingSystemFontScale();
            this.maxAppFontScale = e105.getMaxFontScale();
            this.fontSizeScale = this.decideFontScale(e105);
            this.fontWeightScale =
                e105.getHostContext()?.config?.fontWeightScale ?? DEFAULT_FONT_WEIGHT_SCALE;
        } catch (b105) {
            let c105 = b105.code;
            let d105 = b105.message;
            hilog.error(0x3900, 'Ace',
                `GridObjectSortComponent Faild to init fontsizescale info, code:${c105}, message: ${d105}`);
        }
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        } catch (y104) {
            let z104 = y104?.code;
            let a105 = y104?.message;
            hilog.error(0x3900, 'Ace',
                `GridObjectSortComponent Faild to get environment param error: ${z104}, ${a105}`);
        }
        this.calcGridHeight();
        setTimeout(() => {
            this.firstIn = false;
        }, 500);
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
        accessibility.on('screenReaderStateChange', (x104) => {
            this.isOpenAccessibility = x104;
        });
    }

    getAdaptiveSymbolFontSize() {
        let w104 = this.fontSizeScale;
        if (!this.isFollowingSystemFontScale || w104 === undefined) {
            w104 = MIN_FONT_SCALE;
        }
        w104 = Math.min(MIN_SYMBOL_FONT_SCALE, w104);
        w104 = Math.max(w104, MIN_FONT_SCALE);
        return (w104 * SYMBOL_SIZE_12FP).toString() + 'vp';
    }

    getSymbolFontSizeFrom(v104) {
        if (v104 === undefined) {
            return SYMBOL_DEFAULT;
        }
        if (typeof v104 === 'number') {
            return v104.toString() + 'vp';
        }
        return v104;
    }

    calcTextItemEditHeight() {
        let u104 = MeasureText.measureTextSize({
            textContent: this.dataList[0]?.text ?? '',
            fontSize: `${(LengthMetrics.resource({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_button3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            })?.value ??
                DEFAULT_TEXT_SIZE) * (this.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE)}vp`,
            overflow: TextOverflow.Ellipsis,
            maxLines: TEXT_MAX_LINES
        });
        this.textItemEditHeight = this.fontSizeScale === DEFAULT_FONT_SIZE_SCALE ?
            GRID_ITEM_HEIGHT_TEXT : px2vp(u104.height);
        this.textItemEditHeight = this.textItemEditHeight + PADDING_EIGHT * 2;
    }

    decideFontScale(s104) {
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        let t104 = s104.getHostContext()?.config?.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE;
        return Math.min(t104, this.maxAppFontScale, MAX_FONT_SCALE);
    }

    calcColNum() {
        if (this.imageText || (this.fontSizeScale && this.fontSizeScale > DEFAULT_FONT_SIZE_SCALE)) {
            this.customColumns = GRID_COL_3;
            this.colNum = COL_IMAGE_TEXT;
        } else {
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

    deduplicate(o104) {
        const p104 = [];
        o104.forEach(q104 => {
            if (!p104.some(r104 => r104.id === q104.id)) {
                p104.push(q104);
            }
        });
        return p104;
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
        return (m104, n104) => {
            return m104.order - n104.order;
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
            let k104 = this.getUIContext().getFrameNodeById(EDIT_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
            let l104 = ({
                type: 'requestFocusForAccessibilityNotInterrupt',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `ImageMenuItem_${k104}_0`
            });
            setTimeout(() => {
                accessibility.sendAccessibilityEvent(l104).then(() => {
                    setTimeout(() => {
                        this.isPointToEditTitleBarSaveButton = false;
                    }, ENTER_EXIT_ICON_DURATION);
                });
            }, SEND_EVENT_DURATION);
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
            const i104 = this.getNewData(this.selected, true, 0);
            const j104 = this.getNewData(this.unSelected, false, this.selected.length);
            this.selected = i104;
            this.unSelected = j104;
            this.calcGridHeight();
            this.onSave && this.onSave(i104, j104);
        });
        setTimeout(() => {
            this.saveClick = false;
        }, ENTER_EXIT_ICON_DURATION);
        this.menuSwitch = false;
        this.isPointToAddTitleBarEditButton = true;
    }

    pointToAddTitleBarEditButton() {
        if (this.isPointToAddTitleBarEditButton) {
            let g104 = this.getUIContext()?.getFrameNodeById(ADD_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
            let h104 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `ComposeTitleBar_ImageMenuItem_${g104}_0`
            });
            accessibility.sendAccessibilityEvent(h104).then(() => {
                setTimeout(() => {
                    this.isPointToAddTitleBarEditButton = false;
                }, ENTER_EXIT_ICON_DURATION);
            });
        }
    }

    onDragMoveEvent(c104, d104, e104) {
        if (!this.gridComState || (c104.x < this.blockWidth / 3 && c104.y < this.blockHeight / 3)) {
            return;
        }
        let f104 = e104;
        if (f104 < 0) {
            f104 = this.selected.length - 1;
        } else {
            this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_MOVING,
                Math.floor(e104 / this.colNum) + 1, e104 % this.colNum + 1);
        }
        if (this.dragContent.visibility !== Visibility.Hidden) {
            this.dragContent.visibility = Visibility.Hidden;
        }
        if (this.insertIndex !== e104 || d104 !== e104) {
            this.sendAccessibility();
        }
        this.insertIndex = e104;
    }

    sendAccessibility() {
        if (this.preTextAnnouncedForAccessibility !== this.textAnnouncedForAccessibility) {
            let b104 = ({
                type: 'announceForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                textAnnouncedForAccessibility: this.textAnnouncedForAccessibility
            });
            accessibility.sendAccessibilityEvent(b104);
            this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
        }
    }

    handleDeleteClick(x103) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.clickRemoveBtn = true;
        this.scaleIcon = 0;
        this.arraySelectIsChange = 1;
        let y103 = this.selected.findIndex(a104 => a104.id === x103.id);
        this.content = x103;
        this.selectedIndex = y103;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING, onFinish: () => {
                this.scaleIcon = 1;
                this.selected.splice(y103, 1);
                this.unSelected.unshift(x103);
                this.calcGridHeight();
                this.editGridDataLength = this.editGridDataLength - 1;
                this.editItemMoveX = 0;
                this.editItemMoveY = 0;
                this.arraySelectIsChange = 2;
                this.clickRemoveBtn = false;
                this.readFlag = false;
                this.readIndex4AddArea = 0;
                this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_DELETED,
                    this.getAccessibilityText(this.content?.text ?? ' '));
            }
        }, () => {
            let z103 = this.getAddItemGridPosition();
            this.editItemMoveX = z103.x;
            this.editItemMoveY = z103.y;
        });
    }

    pointToAddArea() {
        let w103 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: ADD_GRID_FIRST_ITEM_ID
        });
        accessibility.sendAccessibilityEvent(w103).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4AddArea = -1;
            }, ENTER_EXIT_ICON_DURATION);
        });
    }

    getNewData(r103, s103, t103) {
        return r103.map((u103, v103) => {
            u103.selected = s103;
            u103.order = t103 + v103;
            u103.visibility = Visibility.Visible;
            return u103;
        });
    }

    getBlockWidth() {
        const q103 = (this.areaWidth - 32) / this.colNum;
        return q103;
    }

    calcGridHeight() {
        this.editGridHeight = this.getGridHeight(this.selected, EDIT);
        this.addGridHeight = this.getGridHeight(this.unSelected);
    }

    getGridHeight(i103, j103) {
        let k103 = 0;
        let l103 = i103.length;
        i103.forEach(p103 => {
            if (p103.visibility === Visibility.Hidden) {
                l103 = l103 - 1;
            }
        });
        let m103 = 0;
        let n103 = l103 % this.colNum === 0;
        if (this.clickAddBtn && n103) {
            m103 = 1;
        } else if (this.isStartDrag && n103 && j103) {
            m103 = 1;
        } else if (this.clickRemoveBtn && n103 && !j103) {
            m103 = 1;
        } else {
            m103 = 0;
        }
        let o103 = Math.ceil(l103 / this.colNum) + m103;
        k103 = this.blockHeight * o103;
        if (l103 === 0) {
            k103 = 0;
        }
        return k103;
    }

    imageTextRemoveIcon(f103) {
        const g103 = this.clickRemoveBtn && this.content.id === f103.id;
        const h103 = g103 ? {
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.plus_circle_fill'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        } : {
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.minus_circle_fill'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        return h103;
    }

    imageTextAddIcon(c103) {
        const d103 = this.clickAddBtn && this.content.id === c103.id && this.gridComState;
        const e103 = d103 ? {
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.minus_circle_fill'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        } : {
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.plus_circle_fill'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        return e103;
    }

    imageTextAddIconVisible(z102) {
        const a103 = this.clickAddBtn && this.content.id === z102.id && !this.gridComState;
        const b103 = a103 ? Visibility.Hidden : Visibility.Visible;
        return b103;
    }

    getCoodXY(u102) {
        let v102 = 0;
        let w102 = 0;
        const x102 = this.colNum;
        const y102 = Math.trunc(u102 % x102);
        if (u102 >= this.dragContentIndex) {
            if (u102 <= this.insertIndex && u102 !== this.dragContentIndex) {
                if (y102 === 0) {
                    v102 = v102 + this.blockWidth * (x102 - 1);
                    w102 = w102 - this.blockHeight;
                } else {
                    v102 = v102 - this.blockWidth;
                }
            }
        } else {
            if (u102 >= this.insertIndex) {
                if (y102 === x102 - 1) {
                    v102 = v102 - this.blockWidth * (x102 - 1);
                    w102 = w102 + this.blockHeight;
                } else {
                    v102 = v102 + this.blockWidth;
                }
            }
        }
        if (!this.isStartDrag) {
            v102 = 0;
            w102 = 0;
        }
        return { x: v102, y: w102 };
    }

    getAddItemGridPosition() {
        const i102 = this.selected.length;
        const j102 = this.colNum;
        const k102 = (this.selectedIndex + 1) % j102;
        const l102 = Math.ceil((this.selectedIndex + 1) / j102);
        const m102 = Math.ceil(i102 / j102);
        const n102 = this.imageText;
        let o102 = 0;
        if (k102 === 0) {
            o102 = n102 || (this.fontSizeScale && this.fontSizeScale > 1) ? -this.blockWidth * 2 : -this.blockWidth * 3;
        } else {
            o102 = -this.blockWidth * (k102 - 1);
        }
        let p102 = SUBTITLE_HEIGHT;
        let q102 = 0;
        const r102 = m102 - l102;
        const s102 = i102 % j102;
        const t102 = s102 === 1 ? r102 : r102 + 1;
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            p102 = this.subTitleHeight;
        }
        q102 = t102 * this.blockHeight + p102;
        return {
            x: o102,
            y: q102
        };
    }

    getCoveringGridPosition(f102) {
        let g102 = 0;
        let h102 = 0;
        if (f102 > this.selectedIndex && this.arraySelectIsChange !== 2) {
            g102 = f102 % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            h102 = f102 % this.colNum === 0 ? -this.blockHeight : 0;
        }
        return {
            x: g102,
            y: h102
        };
    }

    getEditItemGridPosition(t101, u101) {
        const v101 = t101.length;
        const w101 = this.colNum;
        const x101 = Math.trunc(v101 % w101);
        const y101 = Math.trunc(u101 % w101);
        let z101 = Math.abs(x101 - y101) * this.blockWidth;
        if (x101 < y101) {
            z101 = -z101;
        } else if (x101 > y101) {
            z101 = z101;
        } else {
            z101 = 0;
        }
        let a102 = 0;
        let b102 = 0;
        let c102 = Math.trunc(u101 / this.colNum);
        let d102 = SUBTITLE_HEIGHT;
        const e102 = !this.imageText && this.gridComState && u101 > 3;
        if (e102) {
            b102 = (c102 + 1) * (this.blockHeight - 8) + 8;
        } else {
            b102 = (c102 + 1) * this.blockHeight;
        }
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            d102 = this.subTitleHeight;
        }
        a102 = b102 + d102;
        return {
            x: z101,
            y: a102
        };
    }

    getCoveringGridPositionBottom(o101) {
        let p101 = 0;
        let q101 = 0;
        const r101 = o101 % this.colNum === 0;
        const s101 = this.gridComState && !this.imageText ? -this.blockHeight + 8 : -this.blockHeight;
        if (o101 > this.unSelectedIndex && this.arrayUnSelectIsChange !== 2) {
            p101 = r101 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            q101 = r101 ? s101 : 0;
        }
        return {
            x: p101,
            y: q101
        };
    }

    getAddItemRightMove(k101) {
        let l101 = this.blockWidth;
        let m101 = 0;
        let n101 = (k101 + 1) % this.colNum === 0;
        if (n101) {
            l101 = -this.blockWidth * (this.colNum - 1);
            m101 = this.imageText ? this.blockHeight : this.blockHeight - 8;
        }
        return { x: l101, y: m101 };
    }

    getShowAreaItemTranslate(h101) {
        if (this.isStartDrag) {
            let j101 = this.getCoodXY(h101);
            return {
                x: j101.x,
                y: j101.y
            };
        }
        if (!this.isStartDrag && h101 === this.selectedIndex) {
            return {
                x: this.editItemMoveX,
                y: this.editItemMoveY
            };
        }
        if (!this.isStartDrag && h101 !== this.selectedIndex && this.clickRemoveBtn) {
            let i101 = this.getCoveringGridPosition(h101);
            return {
                x: i101.x,
                y: i101.y
            };
        }
        return { x: 0, y: 0 };
    }

    getAddAreaItemTranslate(e101) {
        if (this.clickRemoveBtn) {
            let g101 = this.getAddItemRightMove(e101);
            return {
                x: g101.x,
                y: g101.y
            };
        }
        if (!this.clickRemoveBtn && e101 === this.unSelectedIndex) {
            return {
                x: this.addItemMoveX,
                y: -this.addItemMoveY
            };
        }
        if (!this.clickRemoveBtn && e101 !== this.unSelectedIndex && this.clickAddBtn) {
            let f101 = this.getCoveringGridPositionBottom(e101);
            return {
                x: f101.x,
                y: f101.y
            };
        }
        return { x: 0, y: 0 };
    }

    PixelMapBuilder(d100, e100, f100 = null) {
        this.observeComponentCreation2((c101, d101) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.clip(false);
            Stack.height(this.blockHeight * 1.5);
            Stack.width(this.blockWidth * 1.2);
        }, Stack);
        this.observeComponentCreation2((g100, h100) => {
            If.create();
            if (this.imageText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a101, b101) => {
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
                    this.observeComponentCreation2((s100, t100) => {
                        If.create();
                        if (d100 === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((y100, z100) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.width(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                }, SymbolGlyph);
                            });
                        } else if (d100 instanceof SymbolGlyphModifier) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((w100, x100) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.width(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.attributeModifier.bind(this)(d100);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(2, () => {
                                this.observeComponentCreation2((u100, v100) => {
                                    Image.create(d100);
                                    Image.draggable(false);
                                    Image.height(this.options.imageSize || IMAGE_DEFAULT);
                                    Image.width(this.options.imageSize || IMAGE_DEFAULT);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((q100, r100) => {
                        Text.create(e100);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_button3'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        Text.margin({ top: 2 });
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((o100, p100) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.minus_circle_fill'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_secondary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        }]);
                        SymbolGlyph.width(ICON_SIZE);
                        SymbolGlyph.height(ICON_SIZE);
                        SymbolGlyph.position({
                            x: this.blockWidth - 40,
                            y: -MARGIN_EIGHT
                        });
                    }, SymbolGlyph);
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((m100, n100) => {
                        Row.create();
                        Row.borderRadius(50);
                        Row.padding({
                            left: TEXT_PADDING_LEFT_RIGHT,
                            right: TEXT_PADDING_LEFT_RIGHT,
                        });
                        Row.scale({ x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo });
                        Row.alignItems(VerticalAlign.Center);
                        Row.justifyContent(FlexAlign.Center);
                        Row.backgroundColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_button_normal'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        Row.width(this.textItemEditWidth);
                        Row.height(this.textItemEditHeight);
                    }, Row);
                    this.observeComponentCreation2((k100, l100) => {
                        Text.create(e100);
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_button3'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.textAlign(TextAlign.Center);
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((i100, j100) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.minus_circle_fill'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_secondary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        }]);
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

    HeaderTitleBuilder(l99 = null) {
        this.observeComponentCreation2((y99, z99) => {
            __Common__.create();
            __Common__.id(ADD_TITLE_BAR_ID);
            __Common__.visibility(!this.menuSwitch ? Visibility.Visible : Visibility.None);
            __Common__.onVisibleAreaChange([0.0, 1.0], (a100, b100) => {
                if (a100) {
                    this.pointToAddTitleBarEditButton();
                } else {
                    if (this.isPointToEditTitleBarSaveButton) {
                        try {
                            let c100 = ({
                                type: 'announceForAccessibility',
                                bundleName: this.bundleName,
                                triggerAction: 'common',
                                textAnnouncedForAccessibility: getContext().resourceManager
                                    .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE)
                            });
                            accessibility.sendAccessibilityEvent(c100);
                        } catch (y104) {
                            let z104 = y104?.code;
                            let a105 = y104?.message;
                            hilog.error(0x3900, 'Ace',
                                `GridObjectSortComponent Faild to get environment param error: ${z104}, ${a105}`);
                        }
                    }
                }
            });
        }, __Common__);
        {
            this.observeComponentCreation2((u99, v99) => {
                if (v99) {
                    let w99 = new ComposeTitleBar(this, {
                        title: this.options.normalTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_title_chanel'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        },
                        menuItems: [{
                            value: {
                                'id': -1,
                                'type': 20000,
                                params: ['sys.media.ohos_ic_public_edit'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            symbolStyle: (new SymbolGlyphModifier({
                                'id': -1,
                                'type': 40000,
                                params: ['sys.symbol.square_and_pencil'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            })),
                            isEnabled: true,
                            label: {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.gridobjectsortcomponent_accessibility_header_edit_button'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            accessibilityText: {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.gridobjectsortcomponent_accessibility_header_edit_button'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            action: () => {
                                this.goEdit();
                            }
                        }]
                    }, undefined, u99, () => {
                    }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 948, col: 5 });
                    ViewPU.create(w99);
                    let x99 = () => {
                        return {
                            title: this.options.normalTitle || {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.ohos_grid_edit_title_chanel'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            menuItems: [{
                                value: {
                                    'id': -1,
                                    'type': 20000,
                                    params: ['sys.media.ohos_ic_public_edit'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                },
                                symbolStyle: (new SymbolGlyphModifier({
                                    'id': -1,
                                    'type': 40000,
                                    params: ['sys.symbol.square_and_pencil'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                })),
                                isEnabled: true,
                                label: {
                                    'id': -1,
                                    'type': 10003,
                                    params: ['sys.string.gridobjectsortcomponent_accessibility_header_edit_button'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                },
                                accessibilityText: {
                                    'id': -1,
                                    'type': 10003,
                                    params: ['sys.string.gridobjectsortcomponent_accessibility_header_edit_button'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                },
                                action: () => {
                                    this.goEdit();
                                }
                            }]
                        };
                    };
                    w99.paramsGenerator_ = x99;
                } else {
                    this.updateStateVarsOfChildByElmtId(u99, {});
                }
            }, { name: 'ComposeTitleBar' });
        }
        __Common__.pop();
        this.observeComponentCreation2((q99, r99) => {
            __Common__.create();
            __Common__.id(EDIT_TITLE_BAR_ID);
            __Common__.visibility(this.menuSwitch ? Visibility.Visible : Visibility.None);
            __Common__.onVisibleAreaChange([0.0, 1.0], (s99, t99) => {
                if (s99) {
                    this.pointToEditTitleBarSaveButton();
                }
            });
        }, __Common__);
        {
            this.observeComponentCreation2((m99, n99) => {
                if (n99) {
                    let o99 = new EditableTitleBar(this, {
                        leftIconStyle: EditableLeftIconType.Cancel,
                        isSaveIconRequired: false,
                        menuItems: [{
                            value: {
                                'id': -1,
                                'type': 40000,
                                params: ['sys.symbol.checkmark'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            label: {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.gridobjectsortcomponent_accessibility_complete_button'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            accessibilityText: {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.gridobjectsortcomponent_accessibility_complete_button'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            action: () => {
                                this.saveClick = true;
                                this.onSaveEdit();
                            }
                        }],
                        title: this.options.editTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_title_edit'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        },
                        onCancel: () => {
                            this.cancelEdit();
                        },
                    }, undefined, m99, () => {
                    }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 979, col: 5 });
                    ViewPU.create(o99);
                    let p99 = () => {
                        return {
                            leftIconStyle: EditableLeftIconType.Cancel,
                            isSaveIconRequired: false,
                            menuItems: [{
                                value: {
                                    'id': -1,
                                    'type': 40000,
                                    params: ['sys.symbol.checkmark'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                },
                                label: {
                                    'id': -1,
                                    'type': 10003,
                                    params: ['sys.string.gridobjectsortcomponent_accessibility_complete_button'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                },
                                accessibilityText: {
                                    'id': -1,
                                    'type': 10003,
                                    params: ['sys.string.gridobjectsortcomponent_accessibility_complete_button'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                },
                                action: () => {
                                    this.saveClick = true;
                                    this.onSaveEdit();
                                }
                            }],
                            title: this.options.editTitle || {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.ohos_grid_edit_title_edit'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            onCancel: () => {
                                this.cancelEdit();
                            }
                        };
                    };
                    o99.paramsGenerator_ = p99;
                } else {
                    this.updateStateVarsOfChildByElmtId(m99, {});
                }
            }, { name: 'EditableTitleBar' });
        }
        __Common__.pop();
    }

    ImageTextBuilder(o98, p98, q98 = null) {
        this.observeComponentCreation2((j99, k99) => {
            Column.create();
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((h99, i99) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Center);
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.height(this.imageItemWidth);
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.borderRadius((this.isTouchDown && o98.id === this.content.id) ||
                o98.id === this.hoverId ? this.touchBorderRadius : 0);
            Column.backgroundColor(this.isTouchDown && o98.id === this.content.id
                ? this.touchDown : o98.id === this.hoverId ? this.hoverBackgroundColor : '');
            Column.scale(o98.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } :
                {});
        }, Column);
        this.observeComponentCreation2((x98, y98) => {
            If.create();
            if (o98.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f99, g99) => {
                        SymbolGlyph.create();
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.attributeModifier.bind(this)(o98.symbolStyle);
                        SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((z98, a99) => {
                        If.create();
                        if (o98.url === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((d99, e99) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((b99, c99) => {
                                    Image.create(o98.url);
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
        this.observeComponentCreation2((v98, w98) => {
            Text.create(o98.text);
            Text.textAlign(TextAlign.Center);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_button3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
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
        this.observeComponentCreation2((t98, u98) => {
            SymbolGlyph.create(this.imageTextAddIcon(o98));
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.visibility(p98 === 'add' ? this.imageTextAddIconVisible(o98) : Visibility.Hidden);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }]);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.height(ICON_SIZE);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            SymbolGlyph.onClick(() => this.handleAddIconClick(o98));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_BUTTON,
                this.getAccessibilityText(o98.text)));
        }, SymbolGlyph);
        this.observeComponentCreation2((r98, s98) => {
            SymbolGlyph.create(this.imageTextRemoveIcon(o98));
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }]);
            SymbolGlyph.visibility(p98 === 'delete' && this.gridComState ? Visibility.Visible :
            Visibility.Hidden);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.height(ICON_SIZE);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            SymbolGlyph.onClick(() => this.handleDeleteClick(o98));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DELETE,
                this.getAccessibilityText(o98.text)));
        }, SymbolGlyph);
        Column.pop();
        Column.pop();
    }

    handleAddIconClick(j98) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.scaleIcon = 0;
        this.content = j98;
        const k98 = this.unSelected.findIndex(n98 => n98.id === j98.id);
        this.editGridDataLength = this.selected.length + 1;
        const l98 = this.getEditItemGridPosition(this.selected, k98);
        this.unSelectedIndex = k98;
        this.arrayUnSelectIsChange = 1;
        this.clickAddBtn = true;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING,
            onFinish: () => {
                if (!this.selected.some(m98 => m98.id === j98.id)) {
                    this.arrayUnSelectIsChange = 2;
                    this.scaleIcon = 1;
                    this.selected.push(j98);
                    this.unSelected.splice(k98, 1);
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
            this.addItemMoveX = l98.x;
            this.addItemMoveY = l98.y;
        });
        this.readFlag = false;
        this.readIndex4EditArea = this.editGridDataLength - 1;
        this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM_ADD,
            this.getAccessibilityText(this.content?.text ?? ''), Math.floor(this.readIndex4EditArea / this.colNum) + 1,
            this.readIndex4EditArea % this.colNum + 1);
    }

    TextBlockBuilder(v97, w97 = null) {
        this.observeComponentCreation2((h98, i98) => {
            Stack.create();
            Stack.scale(v97.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } :
                {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((f98, g98) => {
            Row.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
            } : { duration: 0 });
            Row.borderRadius(50);
            Row.width(this.clickRemoveBtn && v97.id === this.content.id ?
                this.textItemEditWidth + 8 : this.textItemEditWidth);
            Row.translate(this.gridComState ? this.clickRemoveBtn &&
                v97.id === this.content.id ? { x: 0 } : { x: -4 } : { x: 0 });
            Row.height('100%');
            Context.animation(null);
            Row.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_button_normal'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((d98, e98) => {
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
            Flex.backgroundColor(this.isTouchDown && v97.id === this.content.id ? this.touchDown
                : v97.id === this.hoverId ? this.hoverBackgroundColor
                    : '');
            Flex.width(this.clickRemoveBtn && v97.id === this.content.id ?
                this.textItemEditWidth + 8 : this.textItemEditWidth);
            Flex.translate(this.gridComState ? this.clickRemoveBtn && v97.id === this.content.id ?
                { x: 0 } : { x: -4 } : { x: 0 });
            Flex.height('100%');
            Context.animation(null);
        }, Flex);
        this.observeComponentCreation2((b98, c98) => {
            SymbolGlyph.create({
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.plus'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            SymbolGlyph.fontSize(this.getAdaptiveSymbolFontSize());
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }]);
            SymbolGlyph.visibility(this.clickRemoveBtn && v97.id === this.content.id ? Visibility.Visible :
            Visibility.None);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((z97, a98) => {
            Text.create(v97.text);
            Text.fontColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_button3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((x97, y97) => {
            SymbolGlyph.create({
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.minus_circle_fill'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER,
            });
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }]);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, centerX: '50%' } });
            SymbolGlyph.scale(v97.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {});
            SymbolGlyph.visibility(this.gridComState ? 0 : 1);
            SymbolGlyph.position({
                x: this.blockWidth - 52,
                y: -MARGIN_EIGHT
            });
            Context.animation(null);
            SymbolGlyph.onClick(() => this.handleDeleteClick(v97));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DELETE,
                this.getAccessibilityText(v97.text)));
        }, SymbolGlyph);
        Flex.pop();
        Stack.pop();
    }

    TextBlockAddItemBuilder(f97, g97 = null) {
        this.observeComponentCreation2((t97, u97) => {
            Stack.create();
            Stack.scale(f97.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } :
                {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((r97, s97) => {
            Row.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Row.borderRadius(50);
            Row.height('100%');
            Row.width(this.addIconShow && f97.id === this.content.id ? this.textItemEditWidth : '100%');
            Row.translate(this.addIconShow && f97.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Row.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_button_normal'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((p97, q97) => {
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
            Flex.backgroundColor(this.isTouchDown && f97.id === this.content.id ? this.touchDown
                : f97.id === this.hoverId ? this.hoverBackgroundColor : '');
            Flex.width(this.addIconShow && f97.id === this.content.id ? this.textItemEditWidth : '100%');
            Flex.translate(this.addIconShow && f97.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Flex.height('100%');
        }, Flex);
        this.observeComponentCreation2((n97, o97) => {
            SymbolGlyph.create({
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.plus'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            SymbolGlyph.fontSize(this.getAdaptiveSymbolFontSize());
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            }]);
            SymbolGlyph.visibility(this.addIconShow && f97.id === this.content.id ? Visibility.None :
            Visibility.Visible);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((l97, m97) => {
            Text.create(f97.text);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_button3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Start);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((h97, i97) => {
            If.create();
            if (this.gridComState && this.addIconShow && f97.id === this.content.id) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j97, k97) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.minus_circle_fill'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
                        SymbolGlyph.fontColor([{
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_secondary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        }]);
                        SymbolGlyph.width(ICON_SIZE);
                        SymbolGlyph.translate(this.gridComState ? { x: -MARGIN_EIGHT } : {});
                        SymbolGlyph.position({
                            x: this.blockWidth - 44,
                            y: -MARGIN_EIGHT
                        });
                    }, SymbolGlyph);
                });
            } else {
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

    AddTagBuilder(k96 = null) {
        this.observeComponentCreation2((d97, e97) => {
            Grid.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            Grid.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ? { y: -this.blockHeight } :
                {});
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
        this.observeComponentCreation2((l96, m96) => {
            ForEach.create();
            const n96 = (p96, q96) => {
                const r96 = p96;
                {
                    const s96 = (b97, c97) => {
                        GridItem.create(() => {
                        }, false);
                        Context.animation({
                            curve: this.clickRemoveBtn ? DRAG_SPRING :
                                q96 === this.unSelectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getAddAreaItemTranslate(q96));
                        Context.animation(null);
                    };
                    const t96 = () => {
                        this.observeComponentCreation2(s96, GridItem);
                        this.observeComponentCreation2((w96, x96) => {
                            Stack.create();
                            Stack.onHover((a97) => {
                                if (a97) {
                                    this.hoverId = r96.id;
                                } else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.onTouch(this.isOpenAccessibility ? undefined : (z96) => {
                                this.handleAddItemTouch(z96, r96);
                            });
                            Stack.onClick(this.isOpenAccessibility ? () => this.handleAddItemClick(r96) : undefined);
                            Gesture.create(GesturePriority.Low);
                            LongPressGesture.create({ repeat: true });
                            LongPressGesture.onAction((y96) => {
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
                                } else {
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
                            Stack.id(`add_grid_item_${q96}`);
                            Stack.onAppear(() => {
                                if (!this.readFlag && q96 === this.readIndex4AddArea) {
                                    this.pointToAddArea();
                                }
                            });
                            Stack.accessibilityGroup(true);
                            Stack.accessibilityLevel(YES);
                            Stack.accessibilityText(this.readFlag ?
                            this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM,
                                this.getAccessibilityText(r96.text ?? '')) : this.textAnnouncedForAccessibility);
                            Stack.accessibilityDescription(this.readFlag ? this.getAddTagGridItemAccessibilityDesc() :
                                ' ');
                        }, Stack);
                        this.observeComponentCreation2((u96, v96) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(r96, ADD);
                                });
                            } else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockAddItemBuilder.bind(this)(r96);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    t96();
                }
            };
            this.forEachUpdateFunction(l96, this.unSelected, n96, (o96) => o96.id.toString(), true, false);
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

    handleAddItemTouch(e96, f96) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        if (e96.type === TouchType.Down) {
            this.content = f96;
            this.isTouchDown = true;
        }
        if (e96.type === TouchType.Cancel) {
            this.isTouchDown = false;
            return;
        }
        if (e96.type === TouchType.Up) {
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
            const g96 = this.unSelected.findIndex(j96 => j96.id === f96.id);
            this.editGridDataLength = this.selected.length + 1;
            const h96 = this.getEditItemGridPosition(this.selected, g96);
            this.content = f96;
            this.unSelectedIndex = g96;
            this.clickAddBtn = true;
            this.arrayUnSelectIsChange = 1;
            this.calcGridHeight();
            Context.animateTo({
                curve: REMOVE_ADD_SPRING, onFinish: () => {
                    if (!this.selected.some(i96 => i96.id === f96.id)) {
                        this.scaleIcon = 1;
                        this.scaleAddIcon = 0;
                        this.selected.push(f96);
                        this.unSelected.splice(g96, 1);
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
                this.addItemMoveX = h96.x;
                this.addItemMoveY = h96.y;
            });
            this.readFlag = false;
            this.readIndex4EditArea = this.editGridDataLength - 1;
            this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM_ADD,
                this.getAccessibilityText(this.content?.text ?? ''),
                Math.floor(this.readIndex4EditArea / this.colNum) + 1, this.readIndex4EditArea % this.colNum + 1);
        }
    }

    handleAddItemClick(z95) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.content = z95;
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
        const a96 = this.unSelected.findIndex(d96 => d96.id === z95.id);
        this.editGridDataLength = this.selected.length + 1;
        const b96 = this.getEditItemGridPosition(this.selected, a96);
        this.content = z95;
        this.unSelectedIndex = a96;
        this.clickAddBtn = true;
        this.arrayUnSelectIsChange = 1;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING,
            onFinish: () => {
                if (!this.selected.some(c96 => c96.id === z95.id)) {
                    this.scaleIcon = 1;
                    this.scaleAddIcon = 0;
                    this.selected.push(z95);
                    this.unSelected.splice(a96, 1);
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
            this.addItemMoveX = b96.x;
            this.addItemMoveY = b96.y;
        });
        this.readFlag = false;
        this.readIndex4EditArea = this.editGridDataLength - 1;
        this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM_ADD,
            this.getAccessibilityText(this.content?.text ?? ''), Math.floor(this.readIndex4EditArea / this.colNum) + 1,
            this.readIndex4EditArea % this.colNum + 1);
    }

    EditTagBuilder(o94 = null) {
        this.observeComponentCreation2((w95, x95) => {
            Column.create();
            Column.accessibilityLevel((this.selected.length === 0) ? YES : NO);
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction(() => {
                this.menuSwitch = true;
            });
            LongPressGesture.pop();
            Gesture.pop();
            Column.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_RESIDENT_AREA));
            Column.accessibilityDescription(this.menuSwitch ? ' ' :
            this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC));
        }, Column);
        this.observeComponentCreation2((i95, j95) => {
            Grid.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            } : { duration: 0 });
            Grid.accessibilityLevel(NO);
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((v95) => {
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
                } else {
                    Context.animateTo({
                        duration: ENTER_EXIT_ICON_DURATION,
                        curve: LONG_TOUCH_SCALE
                    }, () => {
                        this.longScaleOnePointTwo = 1.05;
                    });
                    if (v95.repeat && !this.vibrationDone) {
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
                        } catch {
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
            Grid.onItemDragStart((t95, u95) => {
                this.itemIndex = u95;
                this.selectedIndex = -1;
                if (!this.gridComState) {
                    return;
                }
                this.isStartDrag = true;
                this.insertIndex = u95;
                this.dragContent = this.selected[u95];
                this.dragContentIndex = u95;
                this.textAnnouncedForAccessibility =
                    this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_START,
                        this.getAccessibilityText(this.dragContent?.text ?? ''));
                this.sendAccessibility();
                return {
                    builder: () => {
                        this.PixelMapBuilder.call(this, this.dragContent?.symbolStyle || this.dragContent?.url,
                            this.dragContent?.text);
                    }
                };
            });
            Grid.onItemDrop((p95, q95, r95, s95) => {
                this.insertItem(q95, r95);
            });
            Grid.onItemDragMove((m95, n95, o95) => this.onDragMoveEvent(m95, n95, o95));
            Grid.onItemDragLeave((k95, l95) => {
                this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_ILLEGAL_AREA);
                this.sendAccessibility();
            });
        }, Grid);
        this.observeComponentCreation2((p94, q94) => {
            ForEach.create();
            const r94 = (t94, u94) => {
                const v94 = t94;
                {
                    const w94 = (g95, h95) => {
                        GridItem.create(() => {
                        }, false);
                        Context.animation({
                            curve: this.isStartDrag ? DRAG_SPRING :
                                u94 === this.selectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING,
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getShowAreaItemTranslate(u94));
                        Context.animation(null);
                        GridItem.visibility(v94.visibility);
                    };
                    const x94 = () => {
                        this.observeComponentCreation2(w94, GridItem);
                        this.observeComponentCreation2((a95, b95) => {
                            Stack.create();
                            Stack.onHover((f95) => {
                                if (f95) {
                                    this.hoverId = v94.id;
                                } else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.clip(false);
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : this.gridComState ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.onTouch((e95) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (e95.type === TouchType.Down) {
                                    this.content = v94;
                                    this.isTouchDown = true;
                                }
                                if (e95.type === TouchType.Up || e95.type === TouchType.Cancel) {
                                    this.isTouchDown = false;
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: LONG_TOUCH_SCALE
                                    }, () => {
                                        this.longScaleOnePointTwo = 1;
                                    });
                                }
                            });
                            Stack.id(`edit_grid_item_${u94}`);
                            Stack.onVisibleAreaChange([0.0, 1.0], (c95, d95) => {
                                if (c95) {
                                    if (!this.readFlag && u94 === this.readIndex4EditArea) {
                                        this.pointToNextOne();
                                    }
                                }
                            });
                            Stack.accessibilityGroup(true);
                            Stack.accessibilityLevel(YES);
                            Stack.accessibilityText(this.readFlag ?
                            this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM,
                                this.getAccessibilityText(v94.text)) :
                            this.textAnnouncedForAccessibility);
                            Stack.accessibilityDescription(this.readFlag ?
                            this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DESC) : '');
                        }, Stack);
                        this.observeComponentCreation2((y94, z94) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(v94, DELETE);
                                });
                            } else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockBuilder.bind(this)(v94);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    x94();
                }
            };
            this.forEachUpdateFunction(p94, this.selected, r94, (s94) => s94.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
        Column.pop();
    }

    pointToRepeat(i94) {
        this.readFlag = false;
        let j94 = '';
        let k94 = -1;
        if (i94 === ADD) {
            k94 = this.unSelected.findIndex(n94 => n94.id === this.content.id);
            this.readIndex4AddArea = k94;
            j94 = `add_grid_item_${k94}`;
        } else {
            k94 = this.selected.findIndex(m94 => m94.id === this.content.id);
            this.readIndex4EditArea = k94;
            j94 = `edit_grid_item_${k94}`;
        }
        this.textAnnouncedForAccessibility = getContext().resourceManager
            .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE);
        let l94 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: j94
        });
        accessibility.sendAccessibilityEvent(l94).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4EditArea = -1;
                this.readIndex4AddArea = -1;
                this.textAnnouncedForAccessibility = '';
            }, ENTER_EXIT_ICON_DURATION);
        });
    }

    insertItem(g94, h94) {
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
        if (h94 !== -1) {
            this.selected.splice(g94, 1);
            this.selected.splice(h94, 0, this.dragContent);
            this.textAnnouncedForAccessibility =
                this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP, Math.floor(h94 / this.colNum) + 1,
                    h94 % this.colNum + 1);
        } else {
            this.insertIndex = g94;
            this.textAnnouncedForAccessibility =
                this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP, Math.floor(g94 / this.colNum) + 1,
                    g94 % this.colNum + 1);
        }
        this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
        this.dragContent.visibility = Visibility.Visible;
        this.calcGridHeight();
        this.readFlag = false;
        this.readIndex4EditArea = this.insertIndex;
    }

    pointToNextOne() {
        let f94 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: `edit_grid_item_${this.readIndex4EditArea}`
        });
        accessibility.sendAccessibilityEvent(f94).then(() => {
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
        this.observeComponentCreation2((d94, e94) => {
            Column.create();
            Column.width('100%');
            Column.height('90%');
        }, Column);
        this.HeaderTitleBuilder.bind(this)();
        this.observeComponentCreation2((b94, c94) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((x93, y93) => {
            Column.create();
            Column.onAreaChange((z93, a94) => {
                this.areaWidth = Number(a94.width);
                this.calcAreaInfo();
            });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((v93, w93) => {
            __Common__.create();
            __Common__.margin({ bottom: MARGIN_EIGHT });
        }, __Common__);
        {
            this.observeComponentCreation2((r93, s93) => {
                if (s93) {
                    let t93 = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_subtitle_sort'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, r93, () => {
                    }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 1846, col: 11 });
                    ViewPU.create(t93);
                    let u93 = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.showAreaTitle || {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.ohos_grid_edit_subtitle_sort'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    t93.paramsGenerator_ = u93;
                } else {
                    this.updateStateVarsOfChildByElmtId(r93, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_subtitle_sort'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        },
                        icon: '',
                        operationType: OperationType.BUTTON
                    });
                }
            }, { name: 'SubHeader' });
        }
        __Common__.pop();
        this.EditTagBuilder.bind(this)();
        this.observeComponentCreation2((n93, o93) => {
            __Common__.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            __Common__.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ?
                { y: -this.blockHeight } : {});
            Context.animation(null);
            __Common__.margin({ bottom: MARGIN_EIGHT });
            __Common__.onAreaChange((p93, q93) => {
                this.subTitleHeight = Number(q93.height);
            });
        }, __Common__);
        {
            this.observeComponentCreation2((j93, k93) => {
                if (k93) {
                    let l93 = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_subtitle_add'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, j93, () => {
                    }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 1855, col: 11 });
                    ViewPU.create(l93);
                    let m93 = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.addAreaTitle || {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.ohos_grid_edit_subtitle_add'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__',
                            },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    l93.paramsGenerator_ = m93;
                } else {
                    this.updateStateVarsOfChildByElmtId(j93, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_subtitle_add'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        },
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

    getStringByResourceToken(g93, ...h93) {
        if (g93) {
            try {
                return getContext(this).resourceManager.getStringByNameSync(g93, ...h93);
            } catch (i93) {
                hilog.error(0x3900, 'Ace',
                    `GridObjectSortComponent getStringByResourceToken, error: ${i93.toString()}`);
            }
        }
        return '';
    }

    getAccessibilityText(b93) {
        try {
            let f93 = '';
            if (typeof b93 === 'string') {
                f93 = b93;
            } else {
                if (b93.id === -1) {
                    f93 = getContext()?.resourceManager?.getStringByNameSync(b93.params?.[0].split('.').pop());
                } else {
                    f93 = getContext()?.resourceManager?.getStringSync(b93);
                }
            }
            return f93;
        } catch (c93) {
            let d93 = c93.code;
            let e93 = c93.message;
            hilog.error(0x3900, 'Ace',
                `GridObjectSortComponent getAccessibilityText error, code: ${d93}, message: ${e93}`);
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
