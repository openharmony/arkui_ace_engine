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
const hilog = requireNapi('hilog');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const resourceManager = requireNapi('resourceManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
export var EditableLeftIconType;

(function (EditableLeftIconType) {
    EditableLeftIconType[EditableLeftIconType['Back'] = 0] = 'Back';
    EditableLeftIconType[EditableLeftIconType['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;

(function (ItemType) {
    ItemType[ItemType['Image'] = 0] = 'Image';
    ItemType[ItemType['Icon'] = 1] = 'Icon';
    ItemType[ItemType['LeftIcon'] = 2] = 'LeftIcon';
})(ItemType || (ItemType = {}));

const PUBLIC_CANCEL = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.xmark'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const PUBLIC_OK = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.checkmark'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const PUBLIC_BACK = {
    'id': -1,
    'type': 40000,
    params: ['sys.symbol.chevron_backward'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const DEFAULT_TITLE_BAR_HEIGHT = 56;
const DEFAULT_TITLE_PADDING = 2;
const MAX_LINE_ONE = 1;
const MAX_LINES_TWO = 2;
const MAX_MAIN_TITLE_PERCENT = 0.65;
const MAX_SUB_TITLE_PERCENT = 0.35;
const MIN_SUBTITLE_SIZE = '10.0vp';
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const SYMBOL_SIZE = '24vp';
const SYMBOL_TITLE_SIZE = '64vp';
const TITLE_VP = 20;
const SUBTITLE_VP = 14;
// 'sys.float.titlebar_title_tertiary_size' id,value: 20vp
const TITLE_F = getNumberByResource(125831095, TITLE_VP);
// 'sys.float.titlebar_subheader_size' id,value: 14vp
const SUBTITLE_F = getNumberByResource(125831097, SUBTITLE_VP);
const TITLE_F_VP = (TITLE_F > 0 ? TITLE_F : TITLE_VP) + 'vp';
const SUBTITLE_F_VP = (SUBTITLE_F > 0 ? SUBTITLE_F : SUBTITLE_VP) + 'vp';
class EditableTitleBarTheme {
    constructor() {
        this.iconColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_icon_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconBackgroundColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_icon_background_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconBackgroundPressedColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_icon_background_pressed_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconBackgroundHoverColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_icon_background_hover_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconBackgroundFocusOutlineColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_icon_background_focus_outline_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.titleColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_title_tertiary_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.subTitleColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.titlebar_subheader_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
    }
}
class ButtonGestureModifier {
    constructor(controller) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = controller;
    }
    applyGesture(event) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            event.addGesture(new LongPressGestureHandler({
                repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (event) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            event.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class EditableTitleBar extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.leftIconStyle = EditableLeftIconType.Back;
        this.title = '';
        this.subtitle = '';
        this.isSaveIconRequired = true;
        this.imageItem = undefined;
        this.menuItems = undefined;
        this.options = {};
        this.onSave = undefined;
        this.onCancel = undefined;
        this.constraintWidth = 0;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(),
            this, 'editableTitleBarTheme');
        this.addProvidedVar('editableTitleBarTheme', this.__editableTitleBarTheme, false);
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(params.contentMargin, this, 'contentMargin');
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({
                'id': -1,
                'type': 10002,
                params: ['sys.float.margin_left'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }),
            end: LengthMetrics.resource({
                'id': -1,
                'type': 10002,
                params: ['sys.float.margin_left'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }),
        }, this, 'titleBarMargin');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.leftIconStyle !== undefined) {
            this.leftIconStyle = params.leftIconStyle;
        }
        if (params.title !== undefined) {
            this.title = params.title;
        }
        if (params.subtitle !== undefined) {
            this.subtitle = params.subtitle;
        }
        if (params.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = params.isSaveIconRequired;
        }
        if (params.imageItem !== undefined) {
            this.imageItem = params.imageItem;
        }
        if (params.menuItems !== undefined) {
            this.menuItems = params.menuItems;
        }
        if (params.options !== undefined) {
            this.options = params.options;
        }
        if (params.onSave !== undefined) {
            this.onSave = params.onSave;
        }
        if (params.onCancel !== undefined) {
            this.onCancel = params.onCancel;
        }
        if (params.constraintWidth !== undefined) {
            this.constraintWidth = params.constraintWidth;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
        if (params.maxFontScale !== undefined) {
            this.maxFontScale = params.maxFontScale;
        }
        if (params.systemFontScale !== undefined) {
            this.systemFontScale = params.systemFontScale;
        }
        if (params.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = params.editableTitleBarTheme;
        }
        if (params.titleBarMargin !== undefined) {
            this.titleBarMargin = params.titleBarMargin;
        }
        if (params.fontSize !== undefined) {
            this.fontSize = params.fontSize;
        }
    }
    updateStateVars(params) {
        this.__contentMargin.reset(params.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__contentMargin.purgeDependencyOnElmtId(rmElmtId);
        this.__titleBarMargin.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSize.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__editableTitleBarTheme.aboutToBeDeleted();
        this.__contentMargin.aboutToBeDeleted();
        this.__titleBarMargin.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(newValue) {
        this.__editableTitleBarTheme.set(newValue);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(newValue) {
        this.__contentMargin.set(newValue);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(newValue) {
        this.__titleBarMargin.set(newValue);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(newValue) {
        this.__fontSize.set(newValue);
    }
    onWillApplyTheme(theme) {
        this.editableTitleBarTheme.iconColor = theme.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = theme.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = theme.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = theme.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = theme.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = theme.colors.interactiveFocus;
    }
    aboutToAppear() {
        try {
            let uiContent = this.getUIContext();
            this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
            this.maxFontScale = uiContent.getMaxFontScale();
        }
        catch (exception) {
            let code = exception.code;
            let message = exception.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
        }
    }
    decideFontScale() {
        let uiContent = this.getUIContext();
        this.systemFontScale = uiContent.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM], this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.flexShrink(0);
                    }, Row);
                    this.imageItemLayout.bind(this)();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    imageItemLayout(parent = null) {
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, elmtId, () => { }, {
                        page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 237, col: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }
    leftIconLayout(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() :
                                        this.getUIContext()?.getRouter()?.back()
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    useSymbol: true,
                                }, undefined, elmtId, () => { }, {
                                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 246, col: 7 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.getUIContext()?.getRouter()?.back()
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        useSymbol: true
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                    useSymbol: true,
                                }, undefined, elmtId, () => { }, {
                                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 257, col: 7 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon,
                                        useSymbol: true
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
        }, If);
        If.pop();
    }
    titleLayout(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_space_horizontal'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.title);
            Text.maxFontSize(TITLE_F_VP);
            Text.minFontSize(SUBTITLE_F_VP);
            Text.fontColor(this.editableTitleBarTheme.titleColor);
            Text.maxLines(this.subtitle ? MAX_LINE_ONE : MAX_LINES_TWO);
            Text.fontWeight(FontWeight.Bold);
            Text.textAlign(TextAlign.Start);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.heightAdaptivePolicy(this.subtitle ?
            TextHeightAdaptivePolicy.MAX_LINES_FIRST : TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.constraintSize({
                maxHeight: this.subtitle ? EditableTitleBar.maxMainTitleHeight : EditableTitleBar.totalHeight,
            });
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.margin({
                            top: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level1'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.subtitle);
                        Text.maxFontSize(SUBTITLE_F_VP);
                        Text.minFontSize(MIN_SUBTITLE_SIZE);
                        Text.fontColor(this.editableTitleBarTheme.subTitleColor);
                        Text.maxLines(MAX_LINE_ONE);
                        Text.fontWeight(FontWeight.Regular);
                        Text.textAlign(TextAlign.Start);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST);
                        Text.constraintSize({
                            maxHeight: this.title ? EditableTitleBar.maxSubTitleHeight : EditableTitleBar.totalHeight,
                        });
                    }, Text);
                    Text.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }
    rightMenuItemsLayout(parent = null) {
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                    }, undefined, elmtId, () => { }, {
                        page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 322, col: 5 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {
                        fontSize: this.fontSize
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onPlaceChildren(selfLayoutInfo, children, constraint) {
        children.forEach((child) => {
            child.layout({ x: 0, y: 0 });
        });
    }
    onMeasureSize(selfLayoutInfo, children, constraint) {
        let result = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
        this.fontSize = this.decideFontScale();
        children.forEach((child) => {
            result.height = child.measure(constraint).height;
            result.width = Number(constraint.maxWidth);
        });
        return result;
    }
    rerender() {
        this.updateDirtyElements();
    }
}
EditableTitleBar.maxCountOfExtraItems = 3;
EditableTitleBar.maxOtherCountOfExtraItems = 2;
EditableTitleBar.commonZero = 0;
EditableTitleBar.noneColor = '#00000000';
// 'sys.float.titlebar_default_height' id,value: 56vp
EditableTitleBar.defaultHeight = getNumberByResource(125831115, DEFAULT_TITLE_BAR_HEIGHT);
// 'sys.float.padding_level1' id,value: 2vp
EditableTitleBar.defaultTitlePadding = getNumberByResource(125830920, DEFAULT_TITLE_PADDING);
EditableTitleBar.totalHeight = EditableTitleBar.defaultHeight === EditableTitleBar.commonZero ?
    DEFAULT_TITLE_BAR_HEIGHT : EditableTitleBar.defaultHeight;
EditableTitleBar.titlePadding = EditableTitleBar.defaultTitlePadding === EditableTitleBar.commonZero ?
    DEFAULT_TITLE_PADDING : EditableTitleBar.defaultTitlePadding;
EditableTitleBar.maxMainTitleHeight =
    (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_MAIN_TITLE_PERCENT;
EditableTitleBar.maxSubTitleHeight =
    (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_SUB_TITLE_PERCENT;
class EditableTitleBarMenuSection extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(params.fontSize, this, 'fontSize');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.menuItems !== undefined) {
            this.menuItems = params.menuItems;
        }
        if (params.onSave !== undefined) {
            this.onSave = params.onSave;
        }
        if (params.isSaveEnabled !== undefined) {
            this.isSaveEnabled = params.isSaveEnabled;
        }
        if (params.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(params) {
        this.__fontSize.reset(params.fontSize);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__fontSize.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(newValue) {
        this.__fontSize.set(newValue);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        ForEach.create();
                        const forEachItemGenFunction = _item => {
                            const item = _item;
                            {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    if (isInitialRender) {
                                        let componentCall = new ImageMenuItem(this, {
                                            item: item,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                        }, undefined, elmtId, () => { }, {
                                            page: 'library/src/main/ets/components/EditableTitleBar.ets',
                                            line: 362, col: 15 });
                                        ViewPU.create(componentCall);
                                        let paramsLambda = () => {
                                            return {
                                                item: item,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize
                                            };
                                        };
                                        componentCall.paramsGenerator_ = paramsLambda;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(elmtId, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(elmtId, this.menuItems.slice(EditableTitleBar.commonZero,
                            this.isSaveEnabled ? EditableTitleBar.maxOtherCountOfExtraItems :
                            EditableTitleBar.maxCountOfExtraItems), forEachItemGenFunction);
                    }, ForEach);
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                    useSymbol: true,
                                }, undefined, elmtId, () => { }, {
                                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 370, col: 11 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.Icon,
                                        useSymbol: true
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class ImageMenuItem extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.item = {
            value: '',
            isEnabled: true,
            label: '',
        };
        this.attribute = ItemType.Image;
        this.callbackId = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.longPressTime = 500;
        this.useSymbol = false;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(params.fontSize, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let jsDialog = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                    useSymbol: this.useSymbol,
                }, undefined, -1, () => { }, {
                    page: 'library/src/main/ets/components/EditableTitleBar.ets', line: 406, col: 14 });
                jsDialog.setController(this.dialogController);
                ViewPU.create(jsDialog);
                let paramsLambda = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        itemEditableDialog: this.item,
                        textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        fontSize: this.fontSize,
                        useSymbol: this.useSymbol
                    };
                };
                jsDialog.paramsGenerator_ = paramsLambda;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, "buttonGestureModifier");
        this.setInitiallyProvidedValue(params);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.item !== undefined) {
            this.item = params.item;
        }
        if (params.attribute !== undefined) {
            this.attribute = params.attribute;
        }
        if (params.callbackId !== undefined) {
            this.callbackId = params.callbackId;
        }
        if (params.minFontSize !== undefined) {
            this.minFontSize = params.minFontSize;
        }
        if (params.maxFontSize !== undefined) {
            this.maxFontSize = params.maxFontSize;
        }
        if (params.longPressTime !== undefined) {
            this.longPressTime = params.longPressTime;
        }
        if (params.useSymbol !== undefined) {
            this.useSymbol = params.useSymbol;
        }
        if (params.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (params.isOnFocus !== undefined) {
            this.isOnFocus = params.isOnFocus;
        }
        if (params.isOnHover !== undefined) {
            this.isOnHover = params.isOnHover;
        }
        if (params.isOnClick !== undefined) {
            this.isOnClick = params.isOnClick;
        }
        if (params.dialogController !== undefined) {
            this.dialogController = params.dialogController;
        }
        if (params.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = params.buttonGestureModifier;
        }
    }
    updateStateVars(params) {
        this.__fontSize.reset(params.fontSize);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__fontSize.purgeDependencyOnElmtId(rmElmtId);
        this.__isOnFocus.purgeDependencyOnElmtId(rmElmtId);
        this.__isOnHover.purgeDependencyOnElmtId(rmElmtId);
        this.__isOnClick.purgeDependencyOnElmtId(rmElmtId);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        this.__editableTitleBarTheme.aboutToBeDeleted();
        this.__buttonGestureModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(newValue) {
        this.__fontSize.set(newValue);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(newValue) {
        this.__isOnFocus.set(newValue);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(newValue) {
        this.__isOnHover.set(newValue);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(newValue) {
        this.__isOnClick.set(newValue);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(newValue) {
        this.__editableTitleBarTheme.set(newValue);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(newValue) {
        this.__buttonGestureModifier.set(newValue);
    }
    textDialog() {
        if (this.item.value === PUBLIC_OK) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_save'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.item.value === PUBLIC_CANCEL) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_cancel'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.item.value === PUBLIC_BACK) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_back'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else {
            return this.item.label ? this.item.label : '';
        }
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    touchEventAction(event) {
        if (!this.item.isEnabled) {
            return;
        }
        if (event.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }
    keyEventAction(event) {
        if (!this.item.isEnabled) {
            return;
        }
        if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (event.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (event.type === KeyType.Up) {
            this.isOnClick = false;
        }
    }
    getBgColor() {
        if (this.isOnClick) {
            return this.editableTitleBarTheme.iconBackgroundPressedColor;
        }
        else if (this.isOnHover) {
            return this.editableTitleBarTheme.iconBackgroundHoverColor;
        }
        else {
            return this.editableTitleBarTheme.iconBackgroundColor;
        }
    }
    getFgColor() {
        if (this.isOnClick) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.titlebar_icon_background_pressed_color'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.isOnHover) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.titlebar_icon_background_hover_color'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else {
            return EditableTitleBar.noneColor;
        }
    }
    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_OK) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_save'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.item.value === PUBLIC_CANCEL) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_cancel'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.item.value === PUBLIC_BACK) {
            return {
                'id': -1,
                'type': 10003,
                params: ['sys.string.icon_back'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        else if (this.item.label) {
            return this.item.label;
        }
        return undefined;
    }
    IconBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.width({
                'id': -1,
                'type': 10002,
                params: ['sys.float.titlebar_icon_background_width'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.height({
                'id': -1,
                'type': 10002,
                params: ['sys.float.titlebar_icon_background_height'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.borderRadius({
                'id': -1,
                'type': 10002,
                params: ['sys.float.titlebar_icon_background_shape'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.margin({
                start: this.attribute === ItemType.LeftIcon ? LengthMetrics.vp(EditableTitleBar.commonZero) :
                    LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.titlebar_icon_background_space_horizontal'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }),
            });
            Button.focusOnTouch(true);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(this.getBgColor());
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_focus_outline_weight'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
                style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState();
            Button.onFocus(() => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnFocus = true;
            });
            Button.onBlur(() => this.isOnFocus = false);
            Button.onHover((isOn) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = isOn;
            });
            Button.onKeyEvent((event) => {
                this.keyEventAction(event);
            });
            Button.onTouch((event) => {
                this.touchEventAction(event);
            });
            Button.onClick(() => {
                if (this.item.isEnabled === undefined) {
                    this.item.isEnabled = true;
                }
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.useSymbol) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create(this.item.value);
                        SymbolGlyph.fontColor([this.editableTitleBarTheme.iconColor]);
                        SymbolGlyph.width({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_width'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.height({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_height'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.focusable(this.item.isEnabled);
                        SymbolGlyph.enabled(this.item.isEnabled);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontSize(SYMBOL_SIZE);
                        SymbolGlyph.accessibilityText(this.getAccessibilityReadText());
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.item.value);
                        Image.fillColor(this.editableTitleBarTheme.iconColor);
                        Image.matchTextDirection(this.item.value === PUBLIC_BACK ? true : false);
                        Image.width({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_width'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.height({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_height'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.focusable(this.item.isEnabled);
                        Image.enabled(this.item.isEnabled);
                        Image.draggable(false);
                        Image.accessibilityText(this.getAccessibilityReadText());
                    }, Image);
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    ImageBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_space_horizontal'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }),
            });
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.useSymbol) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create(this.item.value);
                        SymbolGlyph.width({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_background_width'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.height({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_background_height'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.borderRadius({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.corner_radius_level10'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        SymbolGlyph.focusable(false);
                        SymbolGlyph.enabled(this.item.isEnabled);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.item.value);
                        Image.width({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_background_width'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.height({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.titlebar_icon_background_height'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.borderRadius({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.corner_radius_level10'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Image.focusable(false);
                        Image.enabled(this.item.isEnabled);
                        Image.objectFit(ImageFit.Cover);
                    }, Image);
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithLabel({ type: ButtonType.Circle });
            Button.width({
                'id': -1,
                'type': 10002,
                params: ['sys.float.titlebar_icon_background_width'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.height({
                'id': -1,
                'type': 10002,
                params: ['sys.float.titlebar_icon_background_height'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(EditableTitleBar.noneColor);
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_shape'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.titlebar_icon_background_focus_outline_weight'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
                style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState();
            Button.onFocus(() => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnFocus = true;
            });
            Button.onBlur(() => this.isOnFocus = false);
            Button.onHover((isOn) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = isOn;
            });
            Button.onKeyEvent((event) => {
                this.keyEventAction(event);
            });
            Button.onTouch((event) => {
                this.touchEventAction(event);
            });
            Button.onClick(() => {
                if (this.item.isEnabled === undefined) {
                    this.item.isEnabled = true;
                }
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
        }, Button);
        Button.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.attribute === ItemType.Icon || this.attribute === ItemType.LeftIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconBuilder.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.ImageBuilder.bind(this)();
                });
            }
        }, If);
        If.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class EditableTitleBarDialog extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.itemEditableDialog = {
            value: '',
            isEnabled: true,
        };
        this.callbackId = undefined;
        this.textEditableTitleBarDialog = '';
        this.mainWindowStage = undefined;
        this.controller = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.screenWidth = 640;
        this.verticalScreenLines = 6;
        this.horizontalsScreenLines = 1;
        this.useSymbol = false;
        this.cancel = () => {
        };
        this.confirm = () => {
        };
        this.__mainWindow = this.createStorageLink('mainWindow', undefined, 'mainWindow');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(params.fontSize, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.itemEditableDialog !== undefined) {
            this.itemEditableDialog = params.itemEditableDialog;
        }
        if (params.callbackId !== undefined) {
            this.callbackId = params.callbackId;
        }
        if (params.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = params.textEditableTitleBarDialog;
        }
        if (params.mainWindowStage !== undefined) {
            this.mainWindowStage = params.mainWindowStage;
        }
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.minFontSize !== undefined) {
            this.minFontSize = params.minFontSize;
        }
        if (params.maxFontSize !== undefined) {
            this.maxFontSize = params.maxFontSize;
        }
        if (params.screenWidth !== undefined) {
            this.screenWidth = params.screenWidth;
        }
        if (params.verticalScreenLines !== undefined) {
            this.verticalScreenLines = params.verticalScreenLines;
        }
        if (params.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = params.horizontalsScreenLines;
        }
        if (params.useSymbol !== undefined) {
            this.useSymbol = params.useSymbol;
        }
        if (params.cancel !== undefined) {
            this.cancel = params.cancel;
        }
        if (params.confirm !== undefined) {
            this.confirm = params.confirm;
        }
        if (params.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (params.maxLines !== undefined) {
            this.maxLines = params.maxLines;
        }
    }
    updateStateVars(params) {
        this.__fontSize.reset(params.fontSize);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__mainWindow.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSize.purgeDependencyOnElmtId(rmElmtId);
        this.__maxLines.purgeDependencyOnElmtId(rmElmtId);
        this.__windowStandardHeight.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(ctr) {
        this.controller = ctr;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(newValue) {
        this.__mainWindow.set(newValue);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(newValue) {
        this.__fontSize.set(newValue);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(newValue) {
        this.__maxLines.set(newValue);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(newValue) {
        this.__windowStandardHeight.set(newValue);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.corner_radius_level10'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        }));
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.useSymbol) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create(this.itemEditableDialog.value);
                                    SymbolGlyph.width(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.height(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.margin({
                                        top: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.padding_level24'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        bottom: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.padding_level8'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                    });
                                    SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Image.create(this.itemEditableDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.margin({
                                        top: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.padding_level24'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        bottom: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.padding_level8'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                    });
                                    Image.fillColor({
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level4'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level4'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            bottom: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level12'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                        });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.textEditableTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.width('100%');
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.font_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                    }, Text);
                    Text.pop();
                    Column.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.corner_radius_level10'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        }));
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.useSymbol) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create(this.itemEditableDialog.value);
                                    SymbolGlyph.width(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.height(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.fontSize(SYMBOL_TITLE_SIZE);
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Image.create(this.itemEditableDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.fillColor({
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_primary'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                    Column.pop();
                });
            }
        }, If);
        If.pop();
    }
    async aboutToAppear() {
        let context = this.getUIContext().getHostContext();
        this.mainWindowStage = context.windowStage.getMainWindowSync();
        let properties = this.mainWindowStage.getWindowProperties();
        let rect = properties.windowRect;
        if (px2vp(rect.height) > this.screenWidth) {
            this.maxLines = this.verticalScreenLines;
        }
        else {
            this.maxLines = this.horizontalsScreenLines;
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
/**
 * get resource size
 *
 * @param resourceId resource id
 * @return resource size
 */
function getNumberByResource(resourceId, defaultNumber) {
    try {
        let resourceNumber = resourceManager.getSystemResourceManager().getNumber(resourceId);
        if (resourceNumber === 0) {
            return defaultNumber;
        }
        else {
            return resourceNumber;
        }
    }
    catch (error) {
        let code = error.code;
        let message = error.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${code},message:${message}`);
        return 0;
    }
}

export default {
    EditableLeftIconType: EditableLeftIconType,
    EditableTitleBar: EditableTitleBar,
};