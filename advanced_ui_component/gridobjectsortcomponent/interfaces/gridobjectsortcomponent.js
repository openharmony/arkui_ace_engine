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
const ACCESSIBILITY_COMPLETE_BUTTON = 'gridobjectsortcomponent_accessibility_complete_button';
const ACCESSIBILITY_RESIDENT_AREA = 'gridobjectsortcomponent_accessibility_resident_area_edit_state';
const ACCESSIBILITY_SELECTED_ITEM_DESC = 'gridobjectsortcomponent_accessibility_selected_item_desc';
const ACCESSIBILITY_SELECTED_ITEM = 'gridobjectsortcomponent_accessibility_selected_item';
const ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP = 'gridobjectsortcomponent_accessibility_selected_item_drag_stop';
const ACCESSIBILITY_UNSELECTED_ITEM_ADD = 'gridobjectsortcomponent_accessibility_unselected_item_add';
const ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC = 'gridobjectsortcomponent_accessibility_unselected_image_item_desc';
const ACCESSIBILITY_UNSELECTED_TEXT_ITEM_DESC = 'gridobjectsortcomponent_accessibility_unselected_text_item_desc';
const ACCESSIBILITY_UNSELECTED_ITEM = 'gridobjectsortcomponent_accessibility_unselected_item';
const ACCESSIBILITY_SELECTED_ITEM_DELETE = 'gridobjectsortcomponent_accessibility_selected_item_delete';
const ACCESSIBILITY_HEADER_EDIT_BUTTON = 'gridobjectsortcomponent_accessibility_header_edit_button';
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
(function (v106) {
    v106['IMAGE_TEXT'] = 'image_text';
    v106['TEXT'] = 'text';
})(GridObjectSortComponentType || (GridObjectSortComponentType = {}));

class MenuItem {
    constructor(p106, q106, r106, s106, t106, u106) {
        this.value = p106;
        this.symbolStyle = q106;
        this.isEnabled = r106;
        this.action = t106;
        this.accessibilityText = s106;
        this.label = u106;
    }
}

export class GridObjectSortComponent extends ViewPU {
    constructor(g106, h106, i106, j106 = -1, k106 = undefined, l106) {
        super(g106, i106, j106, l106);
        if (typeof k106 === 'function') {
            this.paramsGenerator_ = k106;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(h106.options, this, 'options');
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
            'moduleName': '__harDefaultModuleName__'
        };
        this.touchBorderRadius = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_corner_radius_clicked'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.hoverBackgroundColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.focusBorder = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_focused_outline'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.imageText = false;
        this.menuItems = [
            new MenuItem({
                'id': -1,
                'type': 20000,
                params: ['sys.media.ohos_ic_public_edit'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }, (new SymbolGlyphModifier({
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.square_and_pencil'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            })), true, this.getStringByResourceToken(ACCESSIBILITY_HEADER_EDIT_BUTTON), () => {
                this.goEdit();
            }, this.getStringByResourceToken(ACCESSIBILITY_HEADER_EDIT_BUTTON))
        ];
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
            onConfigurationUpdated: (n106) => {
                let o106 = this.getUIContext();
                this.fontSizeScale = this.decideFontScale(o106);
                this.fontWeightScale = n106.fontWeightScale;
            },
            onMemoryLevel: (m106) => {
            }
        };
        this.setInitiallyProvidedValue(h106);
        this.declareWatch('gridComState', this.onGridComStateChange);
        this.declareWatch('fontSizeScale', this.calcAreaInfo);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(f106) {
        if (f106.options === undefined) {
            this.__options.set({});
        }
        if (f106.dataList !== undefined) {
            this.dataList = f106.dataList;
        }
        if (f106.selected !== undefined) {
            this.selected = f106.selected;
        }
        if (f106.unSelected !== undefined) {
            this.unSelected = f106.unSelected;
        }
        if (f106.copySelected !== undefined) {
            this.copySelected = f106.copySelected;
        }
        if (f106.copyUnSelected !== undefined) {
            this.copyUnSelected = f106.copyUnSelected;
        }
        if (f106.content !== undefined) {
            this.content = f106.content;
        }
        if (f106.dragContent !== undefined) {
            this.dragContent = f106.dragContent;
        }
        if (f106.dragContentIndex !== undefined) {
            this.dragContentIndex = f106.dragContentIndex;
        }
        if (f106.hoverId !== undefined) {
            this.hoverId = f106.hoverId;
        }
        if (f106.gridComState !== undefined) {
            this.gridComState = f106.gridComState;
        }
        if (f106.menuSwitch !== undefined) {
            this.menuSwitch = f106.menuSwitch;
        }
        if (f106.areaWidth !== undefined) {
            this.areaWidth = f106.areaWidth;
        }
        if (f106.blockWidth !== undefined) {
            this.blockWidth = f106.blockWidth;
        }
        if (f106.blockHeight !== undefined) {
            this.blockHeight = f106.blockHeight;
        }
        if (f106.longScaleOnePointTwo !== undefined) {
            this.longScaleOnePointTwo = f106.longScaleOnePointTwo;
        }
        if (f106.scaleGridItemNinetyPercent !== undefined) {
            this.scaleGridItemNinetyPercent = f106.scaleGridItemNinetyPercent;
        }
        if (f106.reboundSize !== undefined) {
            this.reboundSize = f106.reboundSize;
        }
        if (f106.scaleIcon !== undefined) {
            this.scaleIcon = f106.scaleIcon;
        }
        if (f106.addIconShow !== undefined) {
            this.addIconShow = f106.addIconShow;
        }
        if (f106.scaleAddIcon !== undefined) {
            this.scaleAddIcon = f106.scaleAddIcon;
        }
        if (f106.isStartDrag !== undefined) {
            this.isStartDrag = f106.isStartDrag;
        }
        if (f106.insertIndex !== undefined) {
            this.insertIndex = f106.insertIndex;
        }
        if (f106.itemIndex !== undefined) {
            this.itemIndex = f106.itemIndex;
        }
        if (f106.editGridDataLength !== undefined) {
            this.editGridDataLength = f106.editGridDataLength;
        }
        if (f106.isTouchDown !== undefined) {
            this.isTouchDown = f106.isTouchDown;
        }
        if (f106.addItemMoveX !== undefined) {
            this.addItemMoveX = f106.addItemMoveX;
        }
        if (f106.addItemMoveY !== undefined) {
            this.addItemMoveY = f106.addItemMoveY;
        }
        if (f106.editItemMoveX !== undefined) {
            this.editItemMoveX = f106.editItemMoveX;
        }
        if (f106.editItemMoveY !== undefined) {
            this.editItemMoveY = f106.editItemMoveY;
        }
        if (f106.unSelectedIndex !== undefined) {
            this.unSelectedIndex = f106.unSelectedIndex;
        }
        if (f106.clickAddBtn !== undefined) {
            this.clickAddBtn = f106.clickAddBtn;
        }
        if (f106.selectedIndex !== undefined) {
            this.selectedIndex = f106.selectedIndex;
        }
        if (f106.clickRemoveBtn !== undefined) {
            this.clickRemoveBtn = f106.clickRemoveBtn;
        }
        if (f106.addAreaLongPressGesture !== undefined) {
            this.addAreaLongPressGesture = f106.addAreaLongPressGesture;
        }
        if (f106.arraySelectIsChange !== undefined) {
            this.arraySelectIsChange = f106.arraySelectIsChange;
        }
        if (f106.arrayUnSelectIsChange !== undefined) {
            this.arrayUnSelectIsChange = f106.arrayUnSelectIsChange;
        }
        if (f106.textItemEditWidth !== undefined) {
            this.textItemEditWidth = f106.textItemEditWidth;
        }
        if (f106.textItemEditHeight !== undefined) {
            this.textItemEditHeight = f106.textItemEditHeight;
        }
        if (f106.imageItemWidth !== undefined) {
            this.imageItemWidth = f106.imageItemWidth;
        }
        if (f106.saveClick !== undefined) {
            this.saveClick = f106.saveClick;
        }
        if (f106.imageTextAddIconShow !== undefined) {
            this.imageTextAddIconShow = f106.imageTextAddIconShow;
        }
        if (f106.imageTextRemoveIconShow !== undefined) {
            this.imageTextRemoveIconShow = f106.imageTextRemoveIconShow;
        }
        if (f106.firstIn !== undefined) {
            this.firstIn = f106.firstIn;
        }
        if (f106.fontSizeScale !== undefined) {
            this.fontSizeScale = f106.fontSizeScale;
        }
        if (f106.fontWeightScale !== undefined) {
            this.fontWeightScale = f106.fontWeightScale;
        }
        if (f106.customColumns !== undefined) {
            this.customColumns = f106.customColumns;
        }
        if (f106.editGridHeight !== undefined) {
            this.editGridHeight = f106.editGridHeight;
        }
        if (f106.addGridHeight !== undefined) {
            this.addGridHeight = f106.addGridHeight;
        }
        if (f106.subTitleHeight !== undefined) {
            this.subTitleHeight = f106.subTitleHeight;
        }
        if (f106.isOpenAccessibility !== undefined) {
            this.isOpenAccessibility = f106.isOpenAccessibility;
        }
        if (f106.callbackId !== undefined) {
            this.callbackId = f106.callbackId;
        }
        if (f106.colNum !== undefined) {
            this.colNum = f106.colNum;
        }
        if (f106.vibrationDone !== undefined) {
            this.vibrationDone = f106.vibrationDone;
        }
        if (f106.touchDown !== undefined) {
            this.touchDown = f106.touchDown;
        }
        if (f106.touchBorderRadius !== undefined) {
            this.touchBorderRadius = f106.touchBorderRadius;
        }
        if (f106.hoverBackgroundColor !== undefined) {
            this.hoverBackgroundColor = f106.hoverBackgroundColor;
        }
        if (f106.focusBorder !== undefined) {
            this.focusBorder = f106.focusBorder;
        }
        if (f106.imageText !== undefined) {
            this.imageText = f106.imageText;
        }
        if (f106.menuItems !== undefined) {
            this.menuItems = f106.menuItems;
        }
        if (f106.onSave !== undefined) {
            this.onSave = f106.onSave;
        }
        if (f106.onCancel !== undefined) {
            this.onCancel = f106.onCancel;
        }
        if (f106.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = f106.isFollowingSystemFontScale;
        }
        if (f106.maxAppFontScale !== undefined) {
            this.maxAppFontScale = f106.maxAppFontScale;
        }
        if (f106.bundleName !== undefined) {
            this.bundleName = f106.bundleName;
        }
        if (f106.readFlag !== undefined) {
            this.readFlag = f106.readFlag;
        }
        if (f106.readIndex4AddArea !== undefined) {
            this.readIndex4AddArea = f106.readIndex4AddArea;
        }
        if (f106.readIndex4EditArea !== undefined) {
            this.readIndex4EditArea = f106.readIndex4EditArea;
        }
        if (f106.isPointToAddTitleBarEditButton !== undefined) {
            this.isPointToAddTitleBarEditButton = f106.isPointToAddTitleBarEditButton;
        }
        if (f106.isPointToEditTitleBarSaveButton !== undefined) {
            this.isPointToEditTitleBarSaveButton = f106.isPointToEditTitleBarSaveButton;
        }
        if (f106.preTextAnnouncedForAccessibility !== undefined) {
            this.preTextAnnouncedForAccessibility = f106.preTextAnnouncedForAccessibility;
        }
        if (f106.textAnnouncedForAccessibility !== undefined) {
            this.textAnnouncedForAccessibility = f106.textAnnouncedForAccessibility;
        }
        if (f106.envCallback !== undefined) {
            this.envCallback = f106.envCallback;
        }
    }

    updateStateVars(e106) {
        this.__options.reset(e106.options);
    }

    purgeVariableDependenciesOnElmtId(d106) {
        this.__options.purgeDependencyOnElmtId(d106);
        this.__selected.purgeDependencyOnElmtId(d106);
        this.__unSelected.purgeDependencyOnElmtId(d106);
        this.__copySelected.purgeDependencyOnElmtId(d106);
        this.__copyUnSelected.purgeDependencyOnElmtId(d106);
        this.__content.purgeDependencyOnElmtId(d106);
        this.__dragContent.purgeDependencyOnElmtId(d106);
        this.__dragContentIndex.purgeDependencyOnElmtId(d106);
        this.__hoverId.purgeDependencyOnElmtId(d106);
        this.__gridComState.purgeDependencyOnElmtId(d106);
        this.__menuSwitch.purgeDependencyOnElmtId(d106);
        this.__areaWidth.purgeDependencyOnElmtId(d106);
        this.__blockWidth.purgeDependencyOnElmtId(d106);
        this.__blockHeight.purgeDependencyOnElmtId(d106);
        this.__longScaleOnePointTwo.purgeDependencyOnElmtId(d106);
        this.__scaleGridItemNinetyPercent.purgeDependencyOnElmtId(d106);
        this.__reboundSize.purgeDependencyOnElmtId(d106);
        this.__scaleIcon.purgeDependencyOnElmtId(d106);
        this.__addIconShow.purgeDependencyOnElmtId(d106);
        this.__scaleAddIcon.purgeDependencyOnElmtId(d106);
        this.__isStartDrag.purgeDependencyOnElmtId(d106);
        this.__insertIndex.purgeDependencyOnElmtId(d106);
        this.__itemIndex.purgeDependencyOnElmtId(d106);
        this.__editGridDataLength.purgeDependencyOnElmtId(d106);
        this.__isTouchDown.purgeDependencyOnElmtId(d106);
        this.__addItemMoveX.purgeDependencyOnElmtId(d106);
        this.__addItemMoveY.purgeDependencyOnElmtId(d106);
        this.__editItemMoveX.purgeDependencyOnElmtId(d106);
        this.__editItemMoveY.purgeDependencyOnElmtId(d106);
        this.__unSelectedIndex.purgeDependencyOnElmtId(d106);
        this.__clickAddBtn.purgeDependencyOnElmtId(d106);
        this.__selectedIndex.purgeDependencyOnElmtId(d106);
        this.__clickRemoveBtn.purgeDependencyOnElmtId(d106);
        this.__addAreaLongPressGesture.purgeDependencyOnElmtId(d106);
        this.__arraySelectIsChange.purgeDependencyOnElmtId(d106);
        this.__arrayUnSelectIsChange.purgeDependencyOnElmtId(d106);
        this.__textItemEditWidth.purgeDependencyOnElmtId(d106);
        this.__textItemEditHeight.purgeDependencyOnElmtId(d106);
        this.__imageItemWidth.purgeDependencyOnElmtId(d106);
        this.__saveClick.purgeDependencyOnElmtId(d106);
        this.__imageTextAddIconShow.purgeDependencyOnElmtId(d106);
        this.__imageTextRemoveIconShow.purgeDependencyOnElmtId(d106);
        this.__firstIn.purgeDependencyOnElmtId(d106);
        this.__fontSizeScale.purgeDependencyOnElmtId(d106);
        this.__fontWeightScale.purgeDependencyOnElmtId(d106);
        this.__customColumns.purgeDependencyOnElmtId(d106);
        this.__editGridHeight.purgeDependencyOnElmtId(d106);
        this.__addGridHeight.purgeDependencyOnElmtId(d106);
        this.__subTitleHeight.purgeDependencyOnElmtId(d106);
        this.__isOpenAccessibility.purgeDependencyOnElmtId(d106);
        this.__readFlag.purgeDependencyOnElmtId(d106);
        this.__readIndex4AddArea.purgeDependencyOnElmtId(d106);
        this.__readIndex4EditArea.purgeDependencyOnElmtId(d106);
        this.__isPointToAddTitleBarEditButton.purgeDependencyOnElmtId(d106);
        this.__isPointToEditTitleBarSaveButton.purgeDependencyOnElmtId(d106);
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

    set options(c106) {
        this.__options.set(c106);
    }

    get selected() {
        return this.__selected.get();
    }

    set selected(b106) {
        this.__selected.set(b106);
    }

    get unSelected() {
        return this.__unSelected.get();
    }

    set unSelected(a106) {
        this.__unSelected.set(a106);
    }

    get copySelected() {
        return this.__copySelected.get();
    }

    set copySelected(z105) {
        this.__copySelected.set(z105);
    }

    get copyUnSelected() {
        return this.__copyUnSelected.get();
    }

    set copyUnSelected(y105) {
        this.__copyUnSelected.set(y105);
    }

    get content() {
        return this.__content.get();
    }

    set content(x105) {
        this.__content.set(x105);
    }

    get dragContent() {
        return this.__dragContent.get();
    }

    set dragContent(w105) {
        this.__dragContent.set(w105);
    }

    get dragContentIndex() {
        return this.__dragContentIndex.get();
    }

    set dragContentIndex(v105) {
        this.__dragContentIndex.set(v105);
    }

    get hoverId() {
        return this.__hoverId.get();
    }

    set hoverId(u105) {
        this.__hoverId.set(u105);
    }

    get gridComState() {
        return this.__gridComState.get();
    }

    set gridComState(t105) {
        this.__gridComState.set(t105);
    }

    get menuSwitch() {
        return this.__menuSwitch.get();
    }

    set menuSwitch(s105) {
        this.__menuSwitch.set(s105);
    }

    get areaWidth() {
        return this.__areaWidth.get();
    }

    set areaWidth(r105) {
        this.__areaWidth.set(r105);
    }

    get blockWidth() {
        return this.__blockWidth.get();
    }

    set blockWidth(q105) {
        this.__blockWidth.set(q105);
    }

    get blockHeight() {
        return this.__blockHeight.get();
    }

    set blockHeight(p105) {
        this.__blockHeight.set(p105);
    }

    get longScaleOnePointTwo() {
        return this.__longScaleOnePointTwo.get();
    }

    set longScaleOnePointTwo(o105) {
        this.__longScaleOnePointTwo.set(o105);
    }

    get scaleGridItemNinetyPercent() {
        return this.__scaleGridItemNinetyPercent.get();
    }

    set scaleGridItemNinetyPercent(n105) {
        this.__scaleGridItemNinetyPercent.set(n105);
    }

    get reboundSize() {
        return this.__reboundSize.get();
    }

    set reboundSize(m105) {
        this.__reboundSize.set(m105);
    }

    get scaleIcon() {
        return this.__scaleIcon.get();
    }

    set scaleIcon(l105) {
        this.__scaleIcon.set(l105);
    }

    get addIconShow() {
        return this.__addIconShow.get();
    }

    set addIconShow(k105) {
        this.__addIconShow.set(k105);
    }

    get scaleAddIcon() {
        return this.__scaleAddIcon.get();
    }

    set scaleAddIcon(j105) {
        this.__scaleAddIcon.set(j105);
    }

    get isStartDrag() {
        return this.__isStartDrag.get();
    }

    set isStartDrag(i105) {
        this.__isStartDrag.set(i105);
    }

    get insertIndex() {
        return this.__insertIndex.get();
    }

    set insertIndex(h105) {
        this.__insertIndex.set(h105);
    }

    get itemIndex() {
        return this.__itemIndex.get();
    }

    set itemIndex(g105) {
        this.__itemIndex.set(g105);
    }

    get editGridDataLength() {
        return this.__editGridDataLength.get();
    }

    set editGridDataLength(f105) {
        this.__editGridDataLength.set(f105);
    }

    get isTouchDown() {
        return this.__isTouchDown.get();
    }

    set isTouchDown(e105) {
        this.__isTouchDown.set(e105);
    }

    get addItemMoveX() {
        return this.__addItemMoveX.get();
    }

    set addItemMoveX(d105) {
        this.__addItemMoveX.set(d105);
    }

    get addItemMoveY() {
        return this.__addItemMoveY.get();
    }

    set addItemMoveY(c105) {
        this.__addItemMoveY.set(c105);
    }

    get editItemMoveX() {
        return this.__editItemMoveX.get();
    }

    set editItemMoveX(b105) {
        this.__editItemMoveX.set(b105);
    }

    get editItemMoveY() {
        return this.__editItemMoveY.get();
    }

    set editItemMoveY(a105) {
        this.__editItemMoveY.set(a105);
    }

    get unSelectedIndex() {
        return this.__unSelectedIndex.get();
    }

    set unSelectedIndex(z104) {
        this.__unSelectedIndex.set(z104);
    }

    get clickAddBtn() {
        return this.__clickAddBtn.get();
    }

    set clickAddBtn(y104) {
        this.__clickAddBtn.set(y104);
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(x104) {
        this.__selectedIndex.set(x104);
    }

    get clickRemoveBtn() {
        return this.__clickRemoveBtn.get();
    }

    set clickRemoveBtn(w104) {
        this.__clickRemoveBtn.set(w104);
    }

    get addAreaLongPressGesture() {
        return this.__addAreaLongPressGesture.get();
    }

    set addAreaLongPressGesture(v104) {
        this.__addAreaLongPressGesture.set(v104);
    }

    get arraySelectIsChange() {
        return this.__arraySelectIsChange.get();
    }

    set arraySelectIsChange(u104) {
        this.__arraySelectIsChange.set(u104);
    }

    get arrayUnSelectIsChange() {
        return this.__arrayUnSelectIsChange.get();
    }

    set arrayUnSelectIsChange(t104) {
        this.__arrayUnSelectIsChange.set(t104);
    }

    get textItemEditWidth() {
        return this.__textItemEditWidth.get();
    }

    set textItemEditWidth(s104) {
        this.__textItemEditWidth.set(s104);
    }

    get textItemEditHeight() {
        return this.__textItemEditHeight.get();
    }

    set textItemEditHeight(r104) {
        this.__textItemEditHeight.set(r104);
    }

    get imageItemWidth() {
        return this.__imageItemWidth.get();
    }

    set imageItemWidth(q104) {
        this.__imageItemWidth.set(q104);
    }

    get saveClick() {
        return this.__saveClick.get();
    }

    set saveClick(p104) {
        this.__saveClick.set(p104);
    }

    get imageTextAddIconShow() {
        return this.__imageTextAddIconShow.get();
    }

    set imageTextAddIconShow(o104) {
        this.__imageTextAddIconShow.set(o104);
    }

    get imageTextRemoveIconShow() {
        return this.__imageTextRemoveIconShow.get();
    }

    set imageTextRemoveIconShow(n104) {
        this.__imageTextRemoveIconShow.set(n104);
    }

    get firstIn() {
        return this.__firstIn.get();
    }

    set firstIn(m104) {
        this.__firstIn.set(m104);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(l104) {
        this.__fontSizeScale.set(l104);
    }

    get fontWeightScale() {
        return this.__fontWeightScale.get();
    }

    set fontWeightScale(k104) {
        this.__fontWeightScale.set(k104);
    }

    get customColumns() {
        return this.__customColumns.get();
    }

    set customColumns(j104) {
        this.__customColumns.set(j104);
    }

    get editGridHeight() {
        return this.__editGridHeight.get();
    }

    set editGridHeight(i104) {
        this.__editGridHeight.set(i104);
    }

    get addGridHeight() {
        return this.__addGridHeight.get();
    }

    set addGridHeight(h104) {
        this.__addGridHeight.set(h104);
    }

    get subTitleHeight() {
        return this.__subTitleHeight.get();
    }

    set subTitleHeight(g104) {
        this.__subTitleHeight.set(g104);
    }

    get isOpenAccessibility() {
        return this.__isOpenAccessibility.get();
    }

    set isOpenAccessibility(f104) {
        this.__isOpenAccessibility.set(f104);
    }

    get readFlag() {
        return this.__readFlag.get();
    }

    set readFlag(e104) {
        this.__readFlag.set(e104);
    }

    get readIndex4AddArea() {
        return this.__readIndex4AddArea.get();
    }

    set readIndex4AddArea(d104) {
        this.__readIndex4AddArea.set(d104);
    }

    get readIndex4EditArea() {
        return this.__readIndex4EditArea.get();
    }

    set readIndex4EditArea(c104) {
        this.__readIndex4EditArea.set(c104);
    }

    get isPointToAddTitleBarEditButton() {
        return this.__isPointToAddTitleBarEditButton.get();
    }

    set isPointToAddTitleBarEditButton(b104) {
        this.__isPointToAddTitleBarEditButton.set(b104);
    }

    get isPointToEditTitleBarSaveButton() {
        return this.__isPointToEditTitleBarSaveButton.get();
    }

    set isPointToEditTitleBarSaveButton(a104) {
        this.__isPointToEditTitleBarSaveButton.set(a104);
    }

    aboutToAppear() {
        this.dataList.length = 50;
        this.selected =
            this.dataList && this.deduplicate(this.dataList).filter(z103 => z103.selected).sort(this.sortBy());
        this.unSelected =
            this.dataList && this.deduplicate(this.dataList).filter(y103 =>!y103.selected).sort(this.sortBy());
        this.copySelected = this.selected.slice();
        this.copyUnSelected = this.unSelected.slice();
        this.editGridDataLength = this.selected.length;
        this.imageText = this.options.type === GridObjectSortComponentType.IMAGE_TEXT;
        try {
            let x103 = this.getUIContext();
            this.isFollowingSystemFontScale = x103.isFollowingSystemFontScale();
            this.maxAppFontScale = x103.getMaxFontScale();
            this.fontSizeScale = this.decideFontScale(x103);
            this.fontWeightScale =
                x103.getHostContext()?.config?.fontWeightScale ?? DEFAULT_FONT_WEIGHT_SCALE;
        } catch (u103) {
            let v103 = u103.code;
            let w103 = u103.message;
            hilog.error(0x3900, 'Ace',
                `GridObjectSortComponent Faild to init fontsizescale info, code:${v103}, message: ${w103}`);
        }
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        } catch (r103) {
            let s103 = r103.code;
            let t103 = r103.message;
            hilog.error(0x3900, 'Ace',
                `GridObjectSortComponent Faild to get environment param error: ${s103}, ${t103}`);
        }
        this.calcGridHeight();
        setTimeout(() => {
            this.firstIn = false;
        }, 500);
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
        accessibility.on('screenReaderStateChange', (q103) => {
            this.isOpenAccessibility = q103;
        });
    }

    getAdaptiveSymbolFontSize() {
        let p103 = this.fontSizeScale;
        if (!this.isFollowingSystemFontScale || p103 === undefined) {
            p103 = MIN_FONT_SCALE;
        }
        p103 = Math.min(MIN_SYMBOL_FONT_SCALE, p103);
        p103 = Math.max(p103, MIN_FONT_SCALE);
        return (p103 * SYMBOL_SIZE_12FP).toString() + 'vp';
    }

    getSymbolFontSizeFrom(o103) {
        if (o103 === undefined) {
            return SYMBOL_DEFAULT;
        }
        if (typeof o103 === 'number') {
            return o103.toString() + 'vp';
        }
        return o103;
    }

    calcTextItemEditHeight() {
        let n103 = MeasureText.measureTextSize({
            textContent: this.dataList[0]?.text ?? '',
            fontSize: `${(LengthMetrics.resource({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_button3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            })?.value ??
                DEFAULT_TEXT_SIZE) * (this.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE)}vp`,
            overflow: TextOverflow.Ellipsis,
            maxLines: TEXT_MAX_LINES
        });
        this.textItemEditHeight = this.fontSizeScale === DEFAULT_FONT_SIZE_SCALE ?
            GRID_ITEM_HEIGHT_TEXT : px2vp(n103.height);
        this.textItemEditHeight = this.textItemEditHeight + PADDING_EIGHT * 2;
    }

    decideFontScale(l103) {
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        let m103 = l103.getHostContext()?.config?.fontSizeScale ?? DEFAULT_FONT_SIZE_SCALE;
        return Math.min(m103, this.maxAppFontScale, MAX_FONT_SCALE);
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

    deduplicate(h103) {
        const i103 = [];
        h103.forEach(j103 => {
            if (!i103.some(k103 => k103.id === j103.id)) {
                i103.push(j103);
            }
        });
        return i103;
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
        return (f103, g103) => {
            return f103.order - g103.order;
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
            let d103 = this.getUIContext().getFrameNodeById(EDIT_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
            let e103 = ({
                type: 'requestFocusForAccessibilityNotInterrupt',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `ImageMenuItem_${d103}_0`
            });
            setTimeout(() => {
                accessibility.sendAccessibilityEvent(e103).then(() => {
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
            const b103 = this.getNewData(this.selected, true, 0);
            const c103 = this.getNewData(this.unSelected, false, this.selected.length);
            this.selected = b103;
            this.unSelected = c103;
            this.calcGridHeight();
            this.onSave && this.onSave(b103, c103);
        });
        setTimeout(() => {
            this.saveClick = false;
        }, ENTER_EXIT_ICON_DURATION);
        this.menuSwitch = false;
        this.isPointToAddTitleBarEditButton = true;
    }

    pointToAddTitleBarEditButton() {
        if (this.isPointToAddTitleBarEditButton) {
            let z102 = this.getUIContext()?.getFrameNodeById(ADD_TITLE_BAR_ID)?.getFirstChild()?.getUniqueId();
            let a103 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `ComposeTitleBar_ImageMenuItem_${z102}_0`
            });
            accessibility.sendAccessibilityEvent(a103).then(() => {
                setTimeout(() => {
                    this.isPointToAddTitleBarEditButton = false;
                }, ENTER_EXIT_ICON_DURATION);
            });
        }
    }

    onDragMoveEvent(v102, w102, x102) {
        if (!this.gridComState || (v102.x < this.blockWidth / 3 && v102.y < this.blockHeight / 3)) {
            return;
        }
        let y102 = x102;
        if (y102 < 0) {
            y102 = this.selected.length - 1;
        } else {
            this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_MOVING,
                Math.floor(x102 / this.colNum) + 1, x102 % this.colNum + 1);
        }
        if (this.dragContent.visibility !== Visibility.Hidden) {
            this.dragContent.visibility = Visibility.Hidden;
        }
        if (this.insertIndex !== x102 || w102 !== x102) {
            this.sendAccessibility();
        }
        this.insertIndex = x102;
    }

    sendAccessibility() {
        if (this.preTextAnnouncedForAccessibility !== this.textAnnouncedForAccessibility) {
            let u102 = ({
                type: 'announceForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                textAnnouncedForAccessibility: this.textAnnouncedForAccessibility
            });
            accessibility.sendAccessibilityEvent(u102);
            this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
        }
    }

    handleDeleteClick(q102) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.clickRemoveBtn = true;
        this.scaleIcon = 0;
        this.arraySelectIsChange = 1;
        let r102 = this.selected.findIndex(t102 => t102.id === q102.id);
        this.content = q102;
        this.selectedIndex = r102;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING, onFinish: () => {
                this.scaleIcon = 1;
                this.selected.splice(r102, 1);
                this.unSelected.unshift(q102);
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
            let s102 = this.getAddItemGridPosition();
            this.editItemMoveX = s102.x;
            this.editItemMoveY = s102.y;
        });
    }

    pointToAddArea() {
        let p102 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: ADD_GRID_FIRST_ITEM_ID
        });
        accessibility.sendAccessibilityEvent(p102).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4AddArea = -1;
            }, ENTER_EXIT_ICON_DURATION);
        });
    }

    getNewData(k102, l102, m102) {
        return k102.map((n102, o102) => {
            n102.selected = l102;
            n102.order = m102 + o102;
            n102.visibility = Visibility.Visible;
            return n102;
        });
    }

    getBlockWidth() {
        const j102 = (this.areaWidth - 32) / this.colNum;
        return j102;
    }

    calcGridHeight() {
        this.editGridHeight = this.getGridHeight(this.selected, EDIT);
        this.addGridHeight = this.getGridHeight(this.unSelected);
    }

    getGridHeight(b102, c102) {
        let d102 = 0;
        let e102 = b102.length;
        b102.forEach(i102 => {
            if (i102.visibility === Visibility.Hidden) {
                e102 = e102 - 1;
            }
        });
        let f102 = 0;
        let g102 = e102 % this.colNum === 0;
        if (this.clickAddBtn && g102) {
            f102 = 1;
        } else if (this.isStartDrag && g102 && c102) {
            f102 = 1;
        } else if (this.clickRemoveBtn && g102 && !c102) {
            f102 = 1;
        } else {
            f102 = 0;
        }
        let h102 = Math.ceil(e102 / this.colNum) + f102;
        d102 = this.blockHeight * h102;
        if (e102 === 0) {
            d102 = 0;
        }
        return d102;
    }

    imageTextRemoveIcon(y101) {
        const z101 = this.clickRemoveBtn && this.content.id === y101.id;
        const a102 = z101 ? {
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.plus_circle_fill'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        } : {
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.minus_circle_fill'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        return a102;
    }

    imageTextAddIcon(v101) {
        const w101 = this.clickAddBtn && this.content.id === v101.id && this.gridComState;
        const x101 = w101 ? {
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.minus_circle_fill'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        } : {
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.plus_circle_fill'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        return x101;
    }

    imageTextAddIconVisible(s101) {
        const t101 = this.clickAddBtn && this.content.id === s101.id && !this.gridComState;
        const u101 = t101 ? Visibility.Hidden : Visibility.Visible;
        return u101;
    }

    getCoodXY(n101) {
        let o101 = 0;
        let p101 = 0;
        const q101 = this.colNum;
        const r101 = Math.trunc(n101 % q101);
        if (n101 >= this.dragContentIndex) {
            if (n101 <= this.insertIndex && n101 !== this.dragContentIndex) {
                if (r101 === 0) {
                    o101 = o101 + this.blockWidth * (q101 - 1);
                    p101 = p101 - this.blockHeight;
                } else {
                    o101 = o101 - this.blockWidth;
                }
            }
        } else {
            if (n101 >= this.insertIndex) {
                if (r101 === q101 - 1) {
                    o101 = o101 - this.blockWidth * (q101 - 1);
                    p101 = p101 + this.blockHeight;
                } else {
                    o101 = o101 + this.blockWidth;
                }
            }
        }
        if (!this.isStartDrag) {
            o101 = 0;
            p101 = 0;
        }
        return { x: o101, y: p101 };
    }

    getAddItemGridPosition() {
        const b101 = this.selected.length;
        const c101 = this.colNum;
        const d101 = (this.selectedIndex + 1) % c101;
        const e101 = Math.ceil((this.selectedIndex + 1) / c101);
        const f101 = Math.ceil(b101 / c101);
        const g101 = this.imageText;
        let h101 = 0;
        if (d101 === 0) {
            h101 = g101 || (this.fontSizeScale && this.fontSizeScale > 1) ? -this.blockWidth * 2 : -this.blockWidth * 3;
        } else {
            h101 = -this.blockWidth * (d101 - 1);
        }
        let i101 = SUBTITLE_HEIGHT;
        let j101 = 0;
        const k101 = f101 - e101;
        const l101 = b101 % c101;
        const m101 = l101 === 1 ? k101 : k101 + 1;
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            i101 = this.subTitleHeight;
        }
        j101 = m101 * this.blockHeight + i101;
        return {
            x: h101,
            y: j101
        };
    }

    getCoveringGridPosition(y100) {
        let z100 = 0;
        let a101 = 0;
        if (y100 > this.selectedIndex && this.arraySelectIsChange !== 2) {
            z100 = y100 % this.colNum === 0 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            a101 = y100 % this.colNum === 0 ? -this.blockHeight : 0;
        }
        return {
            x: z100,
            y: a101
        };
    }

    getEditItemGridPosition(m100, n100) {
        const o100 = m100.length;
        const p100 = this.colNum;
        const q100 = Math.trunc(o100 % p100);
        const r100 = Math.trunc(n100 % p100);
        let s100 = Math.abs(q100 - r100) * this.blockWidth;
        if (q100 < r100) {
            s100 = -s100;
        } else if (q100 > r100) {
            s100 = s100;
        } else {
            s100 = 0;
        }
        let t100 = 0;
        let u100 = 0;
        let v100 = Math.trunc(n100 / this.colNum);
        let w100 = SUBTITLE_HEIGHT;
        const x100 = !this.imageText && this.gridComState && n100 > 3;
        if (x100) {
            u100 = (v100 + 1) * (this.blockHeight - 8) + 8;
        } else {
            u100 = (v100 + 1) * this.blockHeight;
        }
        if (this.fontSizeScale && this.fontSizeScale > 1) {
            w100 = this.subTitleHeight;
        }
        t100 = u100 + w100;
        return {
            x: s100,
            y: t100
        };
    }

    getCoveringGridPositionBottom(h100) {
        let i100 = 0;
        let j100 = 0;
        const k100 = h100 % this.colNum === 0;
        const l100 = this.gridComState && !this.imageText ? -this.blockHeight + 8 : -this.blockHeight;
        if (h100 > this.unSelectedIndex && this.arrayUnSelectIsChange !== 2) {
            i100 = k100 ? this.blockWidth * (this.colNum - 1) : -this.blockWidth;
            j100 = k100 ? l100 : 0;
        }
        return {
            x: i100,
            y: j100
        };
    }

    getAddItemRightMove(d100) {
        let e100 = this.blockWidth;
        let f100 = 0;
        let g100 = (d100 + 1) % this.colNum === 0;
        if (g100) {
            e100 = -this.blockWidth * (this.colNum - 1);
            f100 = this.imageText ? this.blockHeight : this.blockHeight - 8;
        }
        return { x: e100, y: f100 };
    }

    getShowAreaItemTranslate(a100) {
        if (this.isStartDrag) {
            let c100 = this.getCoodXY(a100);
            return {
                x: c100.x,
                y: c100.y
            };
        }
        if (!this.isStartDrag && a100 === this.selectedIndex) {
            return {
                x: this.editItemMoveX,
                y: this.editItemMoveY
            };
        }
        if (!this.isStartDrag && a100 !== this.selectedIndex && this.clickRemoveBtn) {
            let b100 = this.getCoveringGridPosition(a100);
            return {
                x: b100.x,
                y: b100.y
            };
        }
        return { x: 0, y: 0 };
    }

    getAddAreaItemTranslate(x99) {
        if (this.clickRemoveBtn) {
            let z99 = this.getAddItemRightMove(x99);
            return {
                x: z99.x,
                y: z99.y
            };
        }
        if (!this.clickRemoveBtn && x99 === this.unSelectedIndex) {
            return {
                x: this.addItemMoveX,
                y: -this.addItemMoveY
            };
        }
        if (!this.clickRemoveBtn && x99 !== this.unSelectedIndex && this.clickAddBtn) {
            let y99 = this.getCoveringGridPositionBottom(x99);
            return {
                x: y99.x,
                y: y99.y
            };
        }
        return { x: 0, y: 0 };
    }

    PixelMapBuilder(w98, x98, y98 = null) {
        this.observeComponentCreation2((v99, w99) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.clip(false);
            Stack.height(this.blockHeight * 1.5);
            Stack.width(this.blockWidth * 1.2);
        }, Stack);
        this.observeComponentCreation2((z98, a99) => {
            If.create();
            if (this.imageText) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t99, u99) => {
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
                    this.observeComponentCreation2((l99, m99) => {
                        If.create();
                        if (w98 === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((r99, s99) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.width(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                }, SymbolGlyph);
                            });
                        } else if (w98 instanceof SymbolGlyphModifier) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((p99, q99) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.width(this.options.imageSize || SYMBOL_DEFAULT);
                                    SymbolGlyph.attributeModifier.bind(this)(w98);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(2, () => {
                                this.observeComponentCreation2((n99, o99) => {
                                    Image.create(w98);
                                    Image.draggable(false);
                                    Image.height(this.options.imageSize || IMAGE_DEFAULT);
                                    Image.width(this.options.imageSize || IMAGE_DEFAULT);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((j99, k99) => {
                        Text.create(x98);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_button3'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.margin({ top: 2 });
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((h99, i99) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.minus_circle_fill'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_secondary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
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
                    this.observeComponentCreation2((f99, g99) => {
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
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Row.width(this.textItemEditWidth);
                        Row.height(this.textItemEditHeight);
                    }, Row);
                    this.observeComponentCreation2((d99, e99) => {
                        Text.create(x98);
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_button3'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.textAlign(TextAlign.Center);
                        Text.maxLines(TEXT_MAX_LINES);
                        Text.minFontScale(MIN_FONT_SCALE);
                        Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((b99, c99) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.minus_circle_fill'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
                        SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_secondary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
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

    HeaderTitleBuilder(e98 = null) {
        this.observeComponentCreation2((r98, s98) => {
            __Common__.create();
            __Common__.id(ADD_TITLE_BAR_ID);
            __Common__.visibility(!this.menuSwitch ? Visibility.Visible : Visibility.None);
            __Common__.onVisibleAreaChange([0.0, 1.0], (t98, u98) => {
                if (t98) {
                    this.pointToAddTitleBarEditButton();
                } else {
                    if (this.isPointToEditTitleBarSaveButton) {
                        let v98 = ({
                            type: 'announceForAccessibility',
                            bundleName: this.bundleName,
                            triggerAction: 'common',
                            textAnnouncedForAccessibility: getContext().resourceManager
                                .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE)
                        });
                        accessibility.sendAccessibilityEvent(v98);
                    }
                }
            });
        }, __Common__);
        {
            this.observeComponentCreation2((n98, o98) => {
                if (o98) {
                    let p98 = new ComposeTitleBar(this, {
                        title: this.options.normalTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_title_chanel'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        },
                        menuItems: this.menuItems,
                    }, undefined, n98, () => {
                    }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 977, col: 5 });
                    ViewPU.create(p98);
                    let r = () => {
                        return {
                            title: this.options.normalTitle || {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.ohos_grid_edit_title_chanel'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            menuItems: this.menuItems
                        };
                    };
                    p98.paramsGenerator_ = r;
                } else {
                    this.updateStateVarsOfChildByElmtId(n98, {});
                }
            }, { name: 'ComposeTitleBar' });
        }
        __Common__.pop();
        this.observeComponentCreation2((j98, k98) => {
            __Common__.create();
            __Common__.id(EDIT_TITLE_BAR_ID);
            __Common__.visibility(this.menuSwitch ? Visibility.Visible : Visibility.None);
            __Common__.onVisibleAreaChange([0.0, 1.0], (l98, m98) => {
                if (l98) {
                    this.pointToEditTitleBarSaveButton();
                }
            });
        }, __Common__);
        {
            this.observeComponentCreation2((f98, g98) => {
                if (g98) {
                    let h98 = new EditableTitleBar(this, {
                        leftIconStyle: EditableLeftIconType.Cancel,
                        isSaveIconRequired: false,
                        menuItems: [{
                            value: {
                                'id': -1,
                                'type': 40000,
                                params: ['sys.symbol.checkmark'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            label: this.getStringByResourceToken(ACCESSIBILITY_COMPLETE_BUTTON),
                            accessibilityText: this.getStringByResourceToken(ACCESSIBILITY_COMPLETE_BUTTON),
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
                            'moduleName': '__harDefaultModuleName__'
                        },
                        onCancel: () => {
                            this.cancelEdit();
                        },
                    }, undefined, f98, () => {
                    }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 999, col: 5 });
                    ViewPU.create(h98);
                    let q = () => {
                        return {
                            leftIconStyle: EditableLeftIconType.Cancel,
                            isSaveIconRequired: false,
                            menuItems: [{
                                value: {
                                    'id': -1,
                                    'type': 40000,
                                    params: ['sys.symbol.checkmark'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                },
                                label: this.getStringByResourceToken(ACCESSIBILITY_COMPLETE_BUTTON),
                                accessibilityText: this.getStringByResourceToken(ACCESSIBILITY_COMPLETE_BUTTON),
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
                                'moduleName': '__harDefaultModuleName__'
                            },
                            onCancel: () => {
                                this.cancelEdit();
                            }
                        };
                    };
                    h98.paramsGenerator_ = q;
                } else {
                    this.updateStateVarsOfChildByElmtId(f98, {});
                }
            }, { name: 'EditableTitleBar' });
        }
        __Common__.pop();
    }

    ImageTextBuilder(h97, i97, j97 = null) {
        this.observeComponentCreation2((c98, d98) => {
            Column.create();
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((a98, b98) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Center);
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.height(this.imageItemWidth);
            Column.padding({ left: MARGIN_EIGHT, right: MARGIN_EIGHT });
            Column.borderRadius((this.isTouchDown && h97.id === this.content.id) ||
                h97.id === this.hoverId ? this.touchBorderRadius : 0);
            Column.backgroundColor(this.isTouchDown && h97.id === this.content.id
                ? this.touchDown : h97.id === this.hoverId ? this.hoverBackgroundColor : '');
            Column.scale(h97.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } :
                {});
        }, Column);
        this.observeComponentCreation2((q97, r97) => {
            If.create();
            if (h97.symbolStyle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y97, z97) => {
                        SymbolGlyph.create();
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.attributeModifier.bind(this)(h97.symbolStyle);
                        SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((s97, t97) => {
                        If.create();
                        if (h97.url === undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w97, x97) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.fontSize(this.getSymbolFontSizeFrom(this.options.imageSize));
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((u97, v97) => {
                                    Image.create(h97.url);
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
        this.observeComponentCreation2((o97, p97) => {
            Text.create(h97.text);
            Text.textAlign(TextAlign.Center);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_button3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
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
        this.observeComponentCreation2((m97, n97) => {
            SymbolGlyph.create(this.imageTextAddIcon(h97));
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.visibility(i97 === 'add' ? this.imageTextAddIconVisible(h97) : Visibility.Hidden);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }]);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.height(ICON_SIZE);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            SymbolGlyph.onClick(() => this.handleAddIconClick(h97));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_BUTTON,
                this.getAccessibilityText(h97.text)));
        }, SymbolGlyph);
        this.observeComponentCreation2((k97, l97) => {
            SymbolGlyph.create(this.imageTextRemoveIcon(h97));
            SymbolGlyph.fontSize(SYMBOL_SIZE_24VP);
            SymbolGlyph.fontWeight(SYMBOL_WEIGHT);
            SymbolGlyph.draggable(false);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }]);
            SymbolGlyph.visibility(i97 === 'delete' && this.gridComState ? Visibility.Visible :
            Visibility.Hidden);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.height(ICON_SIZE);
            SymbolGlyph.position({
                x: this.blockWidth - 40,
                y: -MARGIN_EIGHT
            });
            SymbolGlyph.onClick(() => this.handleDeleteClick(h97));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DELETE,
                this.getAccessibilityText(h97.text)));
        }, SymbolGlyph);
        Column.pop();
        Column.pop();
    }

    handleAddIconClick(c97) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.scaleIcon = 0;
        this.content = c97;
        const d97 = this.unSelected.findIndex(g97 => g97.id === c97.id);
        this.editGridDataLength = this.selected.length + 1;
        const e97 = this.getEditItemGridPosition(this.selected, d97);
        this.unSelectedIndex = d97;
        this.arrayUnSelectIsChange = 1;
        this.clickAddBtn = true;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING,
            onFinish: () => {
                if (!this.selected.some(f97 => f97.id === c97.id)) {
                    this.arrayUnSelectIsChange = 2;
                    this.scaleIcon = 1;
                    this.selected.push(c97);
                    this.unSelected.splice(d97, 1);
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
            this.addItemMoveX = e97.x;
            this.addItemMoveY = e97.y;
        });
        this.readFlag = false;
        this.readIndex4EditArea = this.editGridDataLength - 1;
        this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM_ADD,
            this.getAccessibilityText(this.content?.text ?? ''), Math.floor(this.readIndex4EditArea / this.colNum) + 1,
            this.readIndex4EditArea % this.colNum + 1);
    }

    TextBlockBuilder(o96, p96 = null) {
        this.observeComponentCreation2((a97, b97) => {
            Stack.create();
            Stack.scale(o96.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } :
                {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((y96, z96) => {
            Row.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.gridComState ? DRAG_SPRING : COMMON_BEZIER
            } : { duration: 0 });
            Row.borderRadius(50);
            Row.width(this.clickRemoveBtn && o96.id === this.content.id ?
                this.textItemEditWidth + 8 : this.textItemEditWidth);
            Row.translate(this.gridComState ? this.clickRemoveBtn &&
                o96.id === this.content.id ? { x: 0 } : { x: -4 } : { x: 0 });
            Row.height('100%');
            Context.animation(null);
            Row.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_button_normal'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((w96, x96) => {
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
            Flex.backgroundColor(this.isTouchDown && o96.id === this.content.id ? this.touchDown
                : o96.id === this.hoverId ? this.hoverBackgroundColor
                    : '');
            Flex.width(this.clickRemoveBtn && o96.id === this.content.id ?
                this.textItemEditWidth + 8 : this.textItemEditWidth);
            Flex.translate(this.gridComState ? this.clickRemoveBtn && o96.id === this.content.id ?
                { x: 0 } : { x: -4 } : { x: 0 });
            Flex.height('100%');
            Context.animation(null);
        }, Flex);
        this.observeComponentCreation2((u96, v96) => {
            SymbolGlyph.create({
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.plus'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
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
                'moduleName': '__harDefaultModuleName__'
            }]);
            SymbolGlyph.visibility(this.clickRemoveBtn && o96.id === this.content.id ? Visibility.Visible :
            Visibility.None);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((s96, t96) => {
            Text.create(o96.text);
            Text.fontColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_button3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((q96, r96) => {
            SymbolGlyph.create({
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.minus_circle_fill'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
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
                'moduleName': '__harDefaultModuleName__'
            }]);
            SymbolGlyph.width(ICON_SIZE);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0, centerX: '50%' } });
            SymbolGlyph.scale(o96.id === this.content.id ? { x: this.scaleIcon, y: this.scaleIcon } : {});
            SymbolGlyph.visibility(this.gridComState ? 0 : 1);
            SymbolGlyph.position({
                x: this.blockWidth - 52,
                y: -MARGIN_EIGHT
            });
            Context.animation(null);
            SymbolGlyph.onClick(() => this.handleDeleteClick(o96));
            SymbolGlyph.accessibilityLevel(YES);
            SymbolGlyph.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DELETE,
                this.getAccessibilityText(o96.text)));
        }, SymbolGlyph);
        Flex.pop();
        Stack.pop();
    }

    TextBlockAddItemBuilder(y95, z95 = null) {
        this.observeComponentCreation2((m96, n96) => {
            Stack.create();
            Stack.scale(y95.id === this.content.id ? { x: this.longScaleOnePointTwo, y: this.longScaleOnePointTwo } :
                {});
            Stack.padding({
                left: MARGIN_EIGHT,
                right: MARGIN_EIGHT
            });
            Stack.height(this.textItemEditHeight);
        }, Stack);
        this.observeComponentCreation2((k96, l96) => {
            Row.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: COMMON_BEZIER
            });
            Row.borderRadius(50);
            Row.height('100%');
            Row.width(this.addIconShow && y95.id === this.content.id ? this.textItemEditWidth : '100%');
            Row.translate(this.addIconShow && y95.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Row.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_button_normal'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
        }, Row);
        Row.pop();
        this.observeComponentCreation2((i96, j96) => {
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
            Flex.backgroundColor(this.isTouchDown && y95.id === this.content.id ? this.touchDown
                : y95.id === this.hoverId ? this.hoverBackgroundColor : '');
            Flex.width(this.addIconShow && y95.id === this.content.id ? this.textItemEditWidth : '100%');
            Flex.translate(this.addIconShow && y95.id === this.content.id && this.gridComState ? { x: -4 } : { x: 0 });
            Context.animation(null);
            Flex.height('100%');
        }, Flex);
        this.observeComponentCreation2((g96, h96) => {
            SymbolGlyph.create({
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.plus'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
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
                'moduleName': '__harDefaultModuleName__'
            }]);
            SymbolGlyph.visibility(this.addIconShow && y95.id === this.content.id ? Visibility.None :
            Visibility.Visible);
            SymbolGlyph.transition({ type: TransitionType.All, scale: { x: 0, y: 0 } });
            SymbolGlyph.margin({ right: 4 });
            Context.animation(null);
        }, SymbolGlyph);
        this.observeComponentCreation2((e96, f96) => {
            Text.create(y95.text);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_button3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.textAlign(TextAlign.Start);
            Text.maxLines(TEXT_MAX_LINES);
            Text.minFontScale(MIN_FONT_SCALE);
            Text.maxFontScale(ObservedObject.GetRawObject(this.fontSizeScale));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((a96, b96) => {
            If.create();
            if (this.gridComState && this.addIconShow && y95.id === this.content.id) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c96, d96) => {
                        SymbolGlyph.create({
                            'id': -1,
                            'type': 40000,
                            params: ['sys.symbol.minus_circle_fill'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
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
                            'moduleName': '__harDefaultModuleName__'
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

    AddTagBuilder(d95 = null) {
        this.observeComponentCreation2((w95, x95) => {
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
        this.observeComponentCreation2((e95, f95) => {
            ForEach.create();
            const n = (i95, j95) => {
                const k95 = i95;
                {
                    const o = (u95, v95) => {
                        GridItem.create(() => {
                        }, false);
                        Context.animation({
                            curve: this.clickRemoveBtn ? DRAG_SPRING :
                                j95 === this.unSelectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getAddAreaItemTranslate(j95));
                        Context.animation(null);
                    };
                    const p = () => {
                        this.observeComponentCreation2(o, GridItem);
                        this.observeComponentCreation2((p95, q95) => {
                            Stack.create();
                            Stack.onHover((t95) => {
                                if (t95) {
                                    this.hoverId = k95.id;
                                } else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.onTouch(this.isOpenAccessibility ? undefined : (s95) => {
                                this.handleAddItemTouch(s95, k95);
                            });
                            Stack.onClick(this.isOpenAccessibility ? () => this.handleAddItemClick(k95) : undefined);
                            Gesture.create(GesturePriority.Low);
                            LongPressGesture.create({ repeat: true });
                            LongPressGesture.onAction((r95) => {
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
                            Stack.id(`add_grid_item_${j95}`);
                            Stack.onAppear(() => {
                                if (!this.readFlag && j95 === this.readIndex4AddArea) {
                                    this.pointToAddArea();
                                }
                            });
                            Stack.accessibilityGroup(true);
                            Stack.accessibilityLevel(YES);
                            Stack.accessibilityText(this.readFlag ?
                            this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM,
                                this.getAccessibilityText(k95.text ?? '')) : this.textAnnouncedForAccessibility);
                            Stack.accessibilityDescription(this.readFlag ? this.getAddTagGridItemAccessibilityDesc() :
                                ' ');
                        }, Stack);
                        this.observeComponentCreation2((n95, o95) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(k95, ADD);
                                });
                            } else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockAddItemBuilder.bind(this)(k95);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    p();
                }
            };
            this.forEachUpdateFunction(e95, this.unSelected, n, (h95) => h95.id.toString(), true, false);
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

    handleAddItemTouch(x94, y94) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        if (x94.type === TouchType.Down) {
            this.content = y94;
            this.isTouchDown = true;
        }
        if (x94.type === TouchType.Cancel) {
            this.isTouchDown = false;
            return;
        }
        if (x94.type === TouchType.Up) {
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
            const z94 = this.unSelected.findIndex(c95 => c95.id === y94.id);
            this.editGridDataLength = this.selected.length + 1;
            const a95 = this.getEditItemGridPosition(this.selected, z94);
            this.content = y94;
            this.unSelectedIndex = z94;
            this.clickAddBtn = true;
            this.arrayUnSelectIsChange = 1;
            this.calcGridHeight();
            Context.animateTo({
                curve: REMOVE_ADD_SPRING, onFinish: () => {
                    if (!this.selected.some(b95 => b95.id === y94.id)) {
                        this.scaleIcon = 1;
                        this.scaleAddIcon = 0;
                        this.selected.push(y94);
                        this.unSelected.splice(z94, 1);
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
                this.addItemMoveX = a95.x;
                this.addItemMoveY = a95.y;
            });
            this.readFlag = false;
            this.readIndex4EditArea = this.editGridDataLength - 1;
            this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM_ADD,
                this.getAccessibilityText(this.content?.text ?? ''),
                Math.floor(this.readIndex4EditArea / this.colNum) + 1, this.readIndex4EditArea % this.colNum + 1);
        }
    }

    handleAddItemClick(s94) {
        if (this.clickAddBtn || this.clickRemoveBtn) {
            return;
        }
        this.content = s94;
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
        const t94 = this.unSelected.findIndex(w94 => w94.id === s94.id);
        this.editGridDataLength = this.selected.length + 1;
        const u94 = this.getEditItemGridPosition(this.selected, t94);
        this.content = s94;
        this.unSelectedIndex = t94;
        this.clickAddBtn = true;
        this.arrayUnSelectIsChange = 1;
        this.calcGridHeight();
        Context.animateTo({
            curve: REMOVE_ADD_SPRING,
            onFinish: () => {
                if (!this.selected.some(v94 => v94.id === s94.id)) {
                    this.scaleIcon = 1;
                    this.scaleAddIcon = 0;
                    this.selected.push(s94);
                    this.unSelected.splice(t94, 1);
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
            this.addItemMoveX = u94.x;
            this.addItemMoveY = u94.y;
        });
        this.readFlag = false;
        this.readIndex4EditArea = this.editGridDataLength - 1;
        this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_ITEM_ADD,
            this.getAccessibilityText(this.content?.text ?? ''), Math.floor(this.readIndex4EditArea / this.colNum) + 1,
            this.readIndex4EditArea % this.colNum + 1);
    }

    EditTagBuilder(h93 = null) {
        this.observeComponentCreation2((p94, q94) => {
            Column.create();
            Column.accessibilityLevel((this.selected.length === 0) ? YES : NO);
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction(() => {
                this.menuSwitch = true;
            });
            LongPressGesture.onActionEnd(() => {
                let r94 = ({
                    type: 'announceForAccessibility',
                    bundleName: this.bundleName,
                    triggerAction: 'common',
                    textAnnouncedForAccessibility: getContext().resourceManager
                        .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE)
                });
                accessibility.sendAccessibilityEvent(r94);
            });
            LongPressGesture.pop();
            Gesture.pop();
            Column.accessibilityText(this.getStringByResourceToken(ACCESSIBILITY_RESIDENT_AREA));
            Column.accessibilityDescription(this.menuSwitch ? ' ' :
            this.getStringByResourceToken(ACCESSIBILITY_UNSELECTED_IMAGE_ITEM_DESC));
        }, Column);
        this.observeComponentCreation2((b94, c94) => {
            Grid.create();
            Context.animation(!this.firstIn ? {
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            } : { duration: 0 });
            Grid.accessibilityLevel(NO);
            Gesture.create(GesturePriority.Parallel);
            LongPressGesture.create({ repeat: true });
            LongPressGesture.onAction((o94) => {
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
                    if (o94.repeat && !this.vibrationDone) {
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
            Grid.onItemDragStart((m94, n94) => {
                this.itemIndex = n94;
                this.selectedIndex = -1;
                if (!this.gridComState) {
                    return;
                }
                this.isStartDrag = true;
                this.insertIndex = n94;
                this.dragContent = this.selected[n94];
                this.dragContentIndex = n94;
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
            Grid.onItemDrop((i94, j94, k94, l94) => {
                this.insertItem(j94, k94);
            });
            Grid.onItemDragMove((f94, g94, h94) => this.onDragMoveEvent(f94, g94, h94));
            Grid.onItemDragLeave((d94, e94) => {
                this.textAnnouncedForAccessibility = this.getStringByResourceToken(ACCESSIBILITY_ILLEGAL_AREA);
                this.sendAccessibility();
            });
        }, Grid);
        this.observeComponentCreation2((i93, j93) => {
            ForEach.create();
            const k = (m93, n93) => {
                const o93 = m93;
                {
                    const l = (z93, a94) => {
                        GridItem.create(() => {
                        }, false);
                        Context.animation({
                            curve: this.isStartDrag ? DRAG_SPRING :
                                n93 === this.selectedIndex ? REMOVE_ADD_SPRING : DRAG_SPRING,
                        });
                        GridItem.clip(false);
                        GridItem.translate(this.getShowAreaItemTranslate(n93));
                        Context.animation(null);
                        GridItem.visibility(o93.visibility);
                    };
                    const m = () => {
                        this.observeComponentCreation2(l, GridItem);
                        this.observeComponentCreation2((t93, u93) => {
                            Stack.create();
                            Stack.onHover((y93) => {
                                if (y93) {
                                    this.hoverId = o93.id;
                                } else {
                                    this.hoverId = '';
                                }
                            });
                            Stack.clickEffect({ level: ClickEffectLevel.LIGHT });
                            Stack.clip(false);
                            Stack.margin({
                                bottom: this.imageText ? ROW_GAP : this.gridComState ? ROW_GAP : MARGIN_EIGHT
                            });
                            Stack.onTouch((x93) => {
                                if (this.clickAddBtn || this.clickRemoveBtn) {
                                    return;
                                }
                                if (x93.type === TouchType.Down) {
                                    this.content = o93;
                                    this.isTouchDown = true;
                                }
                                if (x93.type === TouchType.Up || x93.type === TouchType.Cancel) {
                                    this.isTouchDown = false;
                                    Context.animateTo({
                                        duration: ENTER_EXIT_ICON_DURATION,
                                        curve: LONG_TOUCH_SCALE
                                    }, () => {
                                        this.longScaleOnePointTwo = 1;
                                    });
                                }
                            });
                            Stack.id(`edit_grid_item_${n93}`);
                            Stack.onVisibleAreaChange([0.0, 1.0], (v93, w93) => {
                                if (v93) {
                                    if (!this.readFlag && n93 === this.readIndex4EditArea) {
                                        this.pointToNextOne();
                                    }
                                }
                            });
                            Stack.accessibilityGroup(true);
                            Stack.accessibilityLevel(YES);
                            Stack.accessibilityText(this.readFlag ?
                            this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM,
                                this.getAccessibilityText(o93.text)) :
                            this.textAnnouncedForAccessibility);
                            Stack.accessibilityDescription(this.readFlag ?
                            this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DESC) : '');
                        }, Stack);
                        this.observeComponentCreation2((r93, s93) => {
                            If.create();
                            if (this.imageText) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.ImageTextBuilder.bind(this)(o93, DELETE);
                                });
                            } else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.TextBlockBuilder.bind(this)(o93);
                                });
                            }
                        }, If);
                        If.pop();
                        Stack.pop();
                        GridItem.pop();
                    };
                    m();
                }
            };
            this.forEachUpdateFunction(i93, this.selected, k, (l93) => l93.id.toString(), true, false);
        }, ForEach);
        ForEach.pop();
        Grid.pop();
        Column.pop();
    }

    pointToRepeat(b93) {
        this.readFlag = false;
        let c93 = '';
        let d93 = -1;
        if (b93 === ADD) {
            d93 = this.unSelected.findIndex(g93 => g93.id === this.content.id);
            this.readIndex4AddArea = d93;
            c93 = `add_grid_item_${d93}`;
        } else {
            d93 = this.selected.findIndex(f93 => f93.id === this.content.id);
            this.readIndex4EditArea = d93;
            c93 = `edit_grid_item_${d93}`;
        }
        this.textAnnouncedForAccessibility = getContext().resourceManager
            .getStringByNameSync(ACCESSIBILITY_ITEM_LONG_PRESS_GESTURE);
        let e93 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: c93
        });
        accessibility.sendAccessibilityEvent(e93).then(() => {
            setTimeout(() => {
                this.readFlag = true;
                this.readIndex4EditArea = -1;
                this.readIndex4AddArea = -1;
                this.textAnnouncedForAccessibility = '';
            }, ENTER_EXIT_ICON_DURATION);
        });
    }

    insertItem(z92, a93) {
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
        if (a93 !== -1) {
            this.selected.splice(z92, 1);
            this.selected.splice(a93, 0, this.dragContent);
            this.textAnnouncedForAccessibility =
                this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP, Math.floor(a93 / this.colNum) + 1,
                    a93 % this.colNum + 1);
        } else {
            this.insertIndex = z92;
            this.textAnnouncedForAccessibility =
                this.getStringByResourceToken(ACCESSIBILITY_SELECTED_ITEM_DRAG_STOP, Math.floor(z92 / this.colNum) + 1,
                    z92 % this.colNum + 1);
        }
        this.preTextAnnouncedForAccessibility = this.textAnnouncedForAccessibility;
        this.dragContent.visibility = Visibility.Visible;
        this.calcGridHeight();
        this.readFlag = false;
        this.readIndex4EditArea = this.insertIndex;
    }

    pointToNextOne() {
        let y92 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: `edit_grid_item_${this.readIndex4EditArea}`
        });
        accessibility.sendAccessibilityEvent(y92).then(() => {
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
        this.observeComponentCreation2((w92, x92) => {
            Column.create();
            Column.width('100%');
            Column.height('90%');
        }, Column);
        this.HeaderTitleBuilder.bind(this)();
        this.observeComponentCreation2((u92, v92) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((q92, r92) => {
            Column.create();
            Column.onAreaChange((s92, t92) => {
                this.areaWidth = Number(t92.width);
                this.calcAreaInfo();
            });
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((o92, p92) => {
            __Common__.create();
            __Common__.margin({ bottom: MARGIN_EIGHT });
        }, __Common__);
        {
            this.observeComponentCreation2((k92, l92) => {
                if (l92) {
                    let m92 = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_subtitle_sort'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, k92, () => {
                    }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 1865, col: 11 });
                    ViewPU.create(m92);
                    let j = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.showAreaTitle || {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.ohos_grid_edit_subtitle_sort'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    m92.paramsGenerator_ = j;
                } else {
                    this.updateStateVarsOfChildByElmtId(k92, {
                        primaryTitle: '',
                        secondaryTitle: this.options.showAreaTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_subtitle_sort'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        },
                        icon: '',
                        operationType: OperationType.BUTTON
                    });
                }
            }, { name: 'SubHeader' });
        }
        __Common__.pop();
        this.EditTagBuilder.bind(this)();
        this.observeComponentCreation2((g92, h92) => {
            __Common__.create();
            Context.animation({
                duration: ENTER_EXIT_ICON_DURATION,
                curve: this.imageText ? REMOVE_ADD_SPRING : COMMON_BEZIER,
            });
            __Common__.translate(this.clickRemoveBtn && this.selected.length % this.colNum === 1 ?
                { y: -this.blockHeight } : {});
            Context.animation(null);
            __Common__.margin({ bottom: MARGIN_EIGHT });
            __Common__.onAreaChange((i92, j92) => {
                this.subTitleHeight = Number(j92.height);
            });
        }, __Common__);
        {
            this.observeComponentCreation2((c92, d92) => {
                if (d92) {
                    let e92 = new SubHeader(this, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_subtitle_add'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        },
                        icon: '',
                        operationType: OperationType.BUTTON
                    }, undefined, c92, () => {
                    }, { page: 'library/src/main/ets/components/GridObjectSortComponent.ets', line: 1874, col: 11 });
                    ViewPU.create(e92);
                    let i = () => {
                        return {
                            primaryTitle: '',
                            secondaryTitle: this.options.addAreaTitle || {
                                'id': -1,
                                'type': 10003,
                                params: ['sys.string.ohos_grid_edit_subtitle_add'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            icon: '',
                            operationType: OperationType.BUTTON
                        };
                    };
                    e92.paramsGenerator_ = i;
                } else {
                    this.updateStateVarsOfChildByElmtId(c92, {
                        primaryTitle: '',
                        secondaryTitle: this.options.addAreaTitle || {
                            'id': -1,
                            'type': 10003,
                            params: ['sys.string.ohos_grid_edit_subtitle_add'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
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

    getStringByResourceToken(f, ...g) {
        if (f) {
            try {
                return getContext(this).resourceManager.getStringByNameSync(f, ...g);
            } catch (h) {
                console.error(`Ace SegmentButton getAccessibilityDescription, error: ${h.toString()}`);
            }
        }
        return '';
    }

    getAccessibilityText(a) {
        try {
            let e = '';
            if (typeof a === 'string') {
                e = a;
            } else {
                e = getContext().resourceManager.getStringSync(a);
            }
            return e;
        } catch (b) {
            let c = b.code;
            let d = b.message;
            hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${c}, message: ${d}`);
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
