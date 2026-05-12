/*
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
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

import { BusinessError } from '@ohos.base';
import hilog from '@ohos.hilog';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import resourceManager from '@ohos.resourceManager';
import { Theme } from '@ohos.arkui.theme';
import { LengthMetrics } from '@ohos.arkui.node';
import common from '@ohos.app.ability.common';
import window from '@ohos.window';
import { Context } from '@ohos.arkui.UIContext';
import { SymbolGlyphModifier } from '@kit.ArkUI';
import { EnvironmentCallback } from '@kit.AbilityKit';
import emitter from '@ohos.events.emitter';
import { promptAction } from '@kit.ArkUI';

export enum EditableLeftIconTypeV2 {
  Back,
  Cancel,
}

export interface EditableTitleBarMenuItem {
  value: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
  isEnabled: boolean;
  label?: ResourceStr;
  action?: () => void;
  accessibilityLevel?: string;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  defaultFocus?: boolean;
}

export type EditableTitleBarItem = EditableTitleBarMenuItem;

export declare interface EditableTitleBarOptions {
  backgroundColor?: ResourceColor;
  backgroundBlurStyle?: BlurStyle;
  safeAreaTypes?: Array<SafeAreaType>;
  safeAreaEdges?: Array<SafeAreaEdge>;
}

enum ItemType {
  Image,
  Icon,
  LeftIcon,
}

const PUBLIC_CANCEL = $r('sys.symbol.xmark');

const PUBLIC_OK = $r('sys.symbol.checkmark');

const PUBLIC_BACK = $r('sys.symbol.chevron_backward');

const PUBLIC_IMAGE_BACK = $r('sys.media.ohos_ic_compnent_titlebar_back');

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
const TITLE_VP: number = 20;
const SUBTITLE_VP: number = 14;

const TITLE_F: number = getNumberByResource(125831095, TITLE_VP);
const SUBTITLE_F: number = getNumberByResource(125831097, SUBTITLE_VP);

const TITLE_F_VP: string = (TITLE_F > 0 ? TITLE_F : TITLE_VP) + 'vp';
const SUBTITLE_F_VP: string = (SUBTITLE_F > 0 ? SUBTITLE_F : SUBTITLE_VP) + 'vp';

const EVENT_FONT_SIZE_CHANGE = 20001;

@ObservedV2
class EditableTitleBarTheme {
  @Trace public iconColor: ResourceColor = $r('sys.color.titlebar_icon_color');
  @Trace public iconBackgroundColor: ResourceColor = $r('sys.color.titlebar_icon_background_color');
  @Trace public iconBackgroundPressedColor: ResourceColor = $r('sys.color.titlebar_icon_background_pressed_color');
  @Trace public iconBackgroundHoverColor: ResourceColor = $r('sys.color.titlebar_icon_background_hover_color');
  @Trace public iconBackgroundFocusOutlineColor: ResourceColor = $r('sys.color.titlebar_icon_background_focus_outline_color');
  @Trace public titleColor: ResourceColor = $r('sys.color.titlebar_title_tertiary_color');
  @Trace public subTitleColor: ResourceColor = $r('sys.color.titlebar_subheader_color');
}

class ButtonGestureModifier implements GestureModifier {
  public static readonly longPressTime: number = 500;
  public static readonly minFontSize: number = 1.75;
  public fontSize: number = 1;
  public maxFontSize: number = 3.2;
  public dialogId: number | null = null;
  public builder: () => void = () => {};

  constructor(dialogId: number | null, builder: () => void) {
    this.dialogId = dialogId;
    this.builder = builder;
  }

  applyGesture(event: UIGestureEvent): void {
    if (this.fontSize >= ButtonGestureModifier.minFontSize) {
      event.addGesture(
        new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
          .onAction(() => {
            if (event) {
              promptAction.openCustomDialog({
                builder: this.builder,
                maskColor: Color.Transparent,
                isModal: true,
                backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
                backgroundColor: Color.Transparent,
                shadow: ShadowStyle.OUTER_DEFAULT_LG,
                cornerRadius: $r('sys.float.corner_radius_level10'),
                width: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG,
              }).then((dialogId: number) => {
                this.dialogId = dialogId;
              }).catch((err: BusinessError) => {
                hilog.error(0x3900, 'EditableTitleBarV2', `Failed to open dialog, error: ${err.message}`);
              });
            }
          })
          .onActionEnd(() => {
            if (this.dialogId !== null) {
              promptAction.closeCustomDialog(this.dialogId);
              this.dialogId = null;
            }
          })
      )
    } else {
      event.clearGestures();
    }
  }
}

@ComponentV2
export struct EditableTitleBarV2 {
  @Param leftIconStyle: EditableLeftIconTypeV2 = EditableLeftIconTypeV2.Back;
  @Param title: ResourceStr = '';
  @Param subtitle?: ResourceStr = '';
  @Param isSaveIconRequired: boolean = true;
  @Param imageItem?: EditableTitleBarItem = undefined;
  @Param menuItems: Array<EditableTitleBarMenuItem> | undefined = undefined;
  @Param options: EditableTitleBarOptions = {};
  @Param onSave?: () => void = undefined;
  @Param onCancel?: () => void = undefined;
  @Param constraintWidth: number = 0;
  @Param leftIconDefaultFocus?: boolean = false;
  @Param saveIconDefaultFocus?: boolean = false;
  public static readonly maxCountOfExtraItems = 3;
  public static readonly maxOtherCountOfExtraItems = 2;
  public static readonly commonZero = 0;
  public static readonly noneColor = '#00000000';
  public static readonly defaultHeight: number = getNumberByResource(125831115, DEFAULT_TITLE_BAR_HEIGHT);
  public static readonly defaultTitlePadding: number = getNumberByResource(125830920, DEFAULT_TITLE_PADDING);
  public static readonly totalHeight: number =
    EditableTitleBarV2.defaultHeight === EditableTitleBarV2.commonZero ? DEFAULT_TITLE_BAR_HEIGHT :
      EditableTitleBarV2.defaultHeight;
  static readonly titlePadding: number =
    EditableTitleBarV2.defaultTitlePadding === EditableTitleBarV2.commonZero ?
      DEFAULT_TITLE_PADDING : EditableTitleBarV2.defaultTitlePadding;
  private static readonly maxMainTitleHeight =
    (EditableTitleBarV2.totalHeight - EditableTitleBarV2.titlePadding) * MAX_MAIN_TITLE_PERCENT;
  private static readonly maxSubTitleHeight =
    (EditableTitleBarV2.totalHeight - EditableTitleBarV2.titlePadding) * MAX_SUB_TITLE_PERCENT;
  private isFollowingSystemFontScale: boolean = false;
  private maxFontScale: number = 1;
  private systemFontScale?: number = 1;
  @Local editableTitleBarTheme: EditableTitleBarTheme = new EditableTitleBarTheme();
  @Param contentMargin?: LocalizedMargin = undefined;
  @Local titleBarMargin: LocalizedMargin = {
    start: LengthMetrics.resource($r('sys.float.margin_left')),
    end: LengthMetrics.resource($r('sys.float.margin_right')),
  }
  @Local fontSize: number = 1;
  private callbackId: number | undefined = undefined;

  onWillApplyTheme(theme: Theme): void {
    this.editableTitleBarTheme.iconColor = theme.colors.iconPrimary;
    this.editableTitleBarTheme.titleColor = theme.colors.fontPrimary;
    this.editableTitleBarTheme.subTitleColor = theme.colors.fontSecondary;
    this.editableTitleBarTheme.iconBackgroundPressedColor = theme.colors.interactivePressed;
    this.editableTitleBarTheme.iconBackgroundHoverColor = theme.colors.interactiveHover;
    this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = theme.colors.interactiveFocus;
  }

  aboutToAppear(): void {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (exception) {
      let code: number = (exception as BusinessError)?.code;
      let message: string = (exception as BusinessError)?.message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
    }
    emitter.on({ eventId: EVENT_FONT_SIZE_CHANGE }, (eventData: emitter.EventData) => {
      if (eventData.data && eventData.data.fontSize !== undefined) {
        this.fontSize = eventData.data.fontSize;
      }
    });
  }

  aboutToDisappear(): void {
    emitter.off(EVENT_FONT_SIZE_CHANGE);
    if (this.callbackId) {
      this.getUIContext()?.getHostContext()?.getApplicationContext()?.off('environment', this.callbackId);
    }
  }

  decideFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale, this.maxFontScale);
  }

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch,
    }) {
      Row() {
        Row() {
          this.leftIconLayout();
        }
        .flexShrink(0)

        Row() {
          if (this.imageItem) {
            Row() {
              this.imageItemLayout();
            }
            .flexShrink(0)
          }

          Row() {
            this.titleLayout();
          }
          .width('100%')
          .flexShrink(1)
        }
        .width('100%')
        .flexShrink(1)
        .accessibilityGroup(true)
        .accessibilityDescription($r('sys.string.subheader_accessibility_title'))

        Row() {
          this.rightMenuItemsLayout();
        }
        .flexShrink(0)
      }
      .width('100%')
      .margin(this.contentMargin ?? this.titleBarMargin)
      .height(EditableTitleBarV2.totalHeight)
    }
    .backgroundColor(this.options.backgroundColor ?? EditableTitleBarV2.noneColor)
    .backgroundBlurStyle(
      this.options.backgroundBlurStyle ?? BlurStyle.NONE, undefined, { disableSystemAdaptation: true })
    .expandSafeArea(
      this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM],
      this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP],
    )
  }

  @Builder
  imageItemLayout(): void {
    ImageMenuItem({
      item: this.imageItem,
      attribute: ItemType.Image,
      editableTitleBarTheme: this.editableTitleBarTheme,
    })
  }

  @Builder
  leftIconLayout(): void {
    if (this.leftIconStyle === EditableLeftIconTypeV2.Back) {
      ImageMenuItem({
        item: {
          value: PUBLIC_BACK,
          isEnabled: true,
          action: () => this.onCancel ? this.onCancel() : this.getUIContext()?.getRouter()?.back(),
          defaultFocus: this.leftIconDefaultFocus
        },
        fontSize: this.fontSize,
        attribute: ItemType.LeftIcon,
        imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`,
        editableTitleBarTheme: this.editableTitleBarTheme,
      })
    } else {
      ImageMenuItem({
        item: {
          value: PUBLIC_CANCEL,
          isEnabled: true,
          action: () => this.onCancel && this.onCancel(),
          defaultFocus: this.leftIconDefaultFocus
        },
        fontSize: this.fontSize,
        attribute: ItemType.LeftIcon,
        imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`,
        editableTitleBarTheme: this.editableTitleBarTheme,
      })
    }
  }

  @Builder
  titleLayout(): void {
    Column() {
      Row() {
        Text(this.title)
          .maxFontSize(TITLE_F_VP)
          .minFontSize(SUBTITLE_F_VP)
          .fontColor(this.editableTitleBarTheme.titleColor)
          .maxLines(this.subtitle ? MAX_LINE_ONE : MAX_LINES_TWO)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Start)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .heightAdaptivePolicy(this.subtitle ?
            TextHeightAdaptivePolicy.MAX_LINES_FIRST : TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
          .constraintSize({
            maxHeight: this.subtitle ? EditableTitleBarV2.maxMainTitleHeight : EditableTitleBarV2.totalHeight,
          })
      }
      .justifyContent(FlexAlign.Start)

      if (this.subtitle) {
        Row() {
          Text(this.subtitle)
            .maxFontSize(SUBTITLE_F_VP)
            .minFontSize(MIN_SUBTITLE_SIZE)
            .fontColor(this.editableTitleBarTheme.subTitleColor)
            .maxLines(MAX_LINE_ONE)
            .fontWeight(FontWeight.Regular)
            .textAlign(TextAlign.Start)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
            .constraintSize({
              maxHeight: this.title ? EditableTitleBarV2.maxSubTitleHeight : EditableTitleBarV2.totalHeight,
            })
        }
        .margin({
          top: $r('sys.float.padding_level1'),
        })
        .justifyContent(FlexAlign.Start)
      }
    }
    .height(EditableTitleBarV2.totalHeight)
    .justifyContent(FlexAlign.Center)
    .margin({
      start: LengthMetrics.resource($r('sys.float.titlebar_icon_background_space_horizontal')),
    })
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  rightMenuItemsLayout(): void {
    EditableTitleBarMenuSection({
      menuItems: this.menuItems,
      onSave: this.onSave,
      isSaveEnabled: this.isSaveIconRequired,
      fontSize: this.fontSize,
      parentUniqueId: this.getUniqueId(),
      saveIconDefaultFocus: this.saveIconDefaultFocus,
      editableTitleBarTheme: this.editableTitleBarTheme,
    })
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void {
    children.forEach((child) => {
      child.layout({ x: 0, y: 0 });
    })
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    let result: SizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    this.fontSize = this.decideFontScale();
    emitter.emit({ eventId: EVENT_FONT_SIZE_CHANGE }, { data: { fontSize: this.fontSize } });
    children.forEach((child) => {
      result.height = child.measure(constraint).height;
      result.width = Number(constraint.maxWidth);
    })
    return result;
  }
}

@ComponentV2
struct EditableTitleBarMenuSection {
  @Param menuItems: Array<EditableTitleBarMenuItem> | undefined = undefined;
  @Param onSave?: () => void = undefined;
  @Param isSaveEnabled: boolean = true;
  @Param saveIconDefaultFocus?: boolean = false;
  @Param fontSize: number = 1;
  @Param parentUniqueId?: number = undefined;
  @Param editableTitleBarTheme: EditableTitleBarTheme = new EditableTitleBarTheme();

  build() {
    Column() {
      Row() {
        if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBarV2.commonZero) {
          ForEach(this.menuItems.slice(EditableTitleBarV2.commonZero,
            this.isSaveEnabled ?
              EditableTitleBarV2.maxOtherCountOfExtraItems : EditableTitleBarV2.maxCountOfExtraItems),
            (item: EditableTitleBarMenuItem, index: number) => {
              ImageMenuItem({
                item: item,
                attribute: ItemType.Icon,
                imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${index}`,
                editableTitleBarTheme: this.editableTitleBarTheme,
              })
            })
        }
        if (this.isSaveEnabled) {
          ImageMenuItem({
            item: {
              value: PUBLIC_OK,
              isEnabled: true,
              action: () => this.onSave && this.onSave(),
              defaultFocus: this.saveIconDefaultFocus
            },
            fontSize: this.fontSize,
            attribute: ItemType.Icon,
            imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`,
            editableTitleBarTheme: this.editableTitleBarTheme,
          })
        }
      }
    }
    .justifyContent(FlexAlign.Center)
  }
}

@ComponentV2
struct ImageMenuItem {
  @Param item: EditableTitleBarMenuItem = {
    value: '',
    isEnabled: true,
    label: '',
    accessibilityLevel: 'auto',
    accessibilityText: '',
    accessibilityDescription: '',
  };
  @Param attribute: ItemType = ItemType.Image;
  callbackId: number | undefined = undefined;
  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  longPressTime: number = 500;
  systemFontScale?: number = 1;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  @Param fontSize: number = 1;
  @Local innerFontSize: number = 1;
  @Local isOnFocus: boolean = false;
  @Local isOnHover: boolean = false;
  @Local isOnClick: boolean = false;
  @Param imageMenuItemId?: string = undefined;
  @Param editableTitleBarTheme: EditableTitleBarTheme = new EditableTitleBarTheme();
  dialogId: number | null = null;
  @Local buttonGestureModifier: ButtonGestureModifier | null = null;

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (exception) {
      let code: number = (exception as BusinessError)?.code;
      let message: string = (exception as BusinessError)?.message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
    }

    this.buttonGestureModifier = new ButtonGestureModifier(this.dialogId, () => {
      this.EditableTitleBarDialogBuilder();
    });

    try {
      this.callbackId =
        this.getUIContext()?.getHostContext()?.getApplicationContext()?.on('environment', this.envCallback);
    } catch (paramError) {
      let code = (paramError as BusinessError)?.code;
      let message = (paramError as BusinessError)?.message;
      hilog.error(0x3900, 'EditableTitleBarV2',
        `Failed to get environment param error: ${code}, ${message}`);
    }
    this.innerFontSize = this.decideFontScale();
    if (this.buttonGestureModifier) {
      this.buttonGestureModifier.fontSize = this.innerFontSize;
      this.buttonGestureModifier.maxFontSize = this.maxFontSize;
    }
  }

  aboutToDisappear(): void {
    if (this.callbackId) {
      this.getUIContext()?.getHostContext()?.getApplicationContext()?.off('environment', this.callbackId);
      this.callbackId = undefined;
    }
  }

  private textDialog(): ResourceStr {
    if (this.item.value === PUBLIC_OK) {
      return $r('sys.string.icon_save');
    } else if (this.item.value === PUBLIC_CANCEL) {
      return $r('sys.string.icon_cancel');
    } else if (this.item.value === PUBLIC_BACK) {
      return $r('sys.string.icon_back');
    } else {
      return this.item.label ? this.item.label : '';
    }
  }

  private envCallback: EnvironmentCallback = {
    onConfigurationUpdated: (config) => {
      if (config === undefined || !this.isFollowingSystemFontScale) {
        this.innerFontSize = 1;
        return;
      }
      try {
        this.innerFontSize = Math.min(
          this.maxFontScale, config?.fontSizeScale ?? 1);
        if (this.buttonGestureModifier) {
          this.buttonGestureModifier.fontSize = this.innerFontSize;
        }
      } catch (paramError) {
        let code = (paramError as BusinessError)?.code;
        let message = (paramError as BusinessError)?.message;
        hilog.error(0x3900, 'EditableTitleBarV2',
          `EnvironmentCallback error: ${code}, ${message}`);
      }
    },
    onMemoryLevel: (level) => {
    }
  }

  decideFontScale(): number {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.systemFontScale = (uiContent?.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
    } catch (exception) {
      let code: number = (exception as BusinessError)?.code;
      let message: string = (exception as BusinessError)?.message;
      hilog.error(0x3900, 'EditableTitleBarV2', `Failed to decideFontScale,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  @Styles
  buttonStateStyles() {
    .stateStyles({
      focused: this.focusedStyle,
      normal: this.notInFocusedStyle,
      pressed: this.notInFocusedStyle,
    })
  }

  @Styles
  focusedStyle() {
    .border({
      radius: $r('sys.float.titlebar_icon_background_shape'),
      width: $r('sys.float.titlebar_icon_background_focus_outline_weight'),
      color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
      style: BorderStyle.Solid,
    })
  }

  @Styles
  notInFocusedStyle() {
    .border({
      radius: $r('sys.float.titlebar_icon_background_shape'),
      width: EditableTitleBarV2.commonZero,
    })
  }

  private touchEventAction(event: TouchEvent): void {
    if (!this.item.isEnabled) {
      return;
    }
    if (event.type === TouchType.Down) {
      this.isOnClick = true;
    }
    if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
      if (this.innerFontSize >= this.minFontSize && this.dialogId !== null) {
        promptAction.closeCustomDialog(this.dialogId);
        this.dialogId = null;
      }
      this.isOnClick = false;
    }
  }

  private keyEventAction(event: KeyEvent): void {
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

  @Styles
  buttonEventStyle() {
    .onFocus(() => {
      if (!this.item.isEnabled) {
        return;
      }
      this.isOnFocus = true;
    })
    .onBlur(() => this.isOnFocus = false)
    .onHover((isOn) => {
      if (!this.item.isEnabled) {
        return;
      }
      this.isOnHover = isOn;
    })
    .onKeyEvent((event) => {
      this.keyEventAction(event);
    })
    .onTouch((event) => {
      this.touchEventAction(event);
    })
    .onClick(() => {
      if (this.item.isEnabled === undefined) {
        this.item.isEnabled = true;
      }
      this.item.isEnabled && this.item.action && this.item.action()
    })
  }

  @Styles
  backgroundButtonStyle() {
    .width($r('sys.float.titlebar_icon_background_width'))
    .height($r('sys.float.titlebar_icon_background_height'))
    .focusable(this.item.isEnabled)
    .enabled(this.item.isEnabled)
  }

  getBgColor(): ResourceColor {
    if (this.isOnClick) {
      return this.editableTitleBarTheme.iconBackgroundPressedColor;
    } else if (this.isOnHover) {
      return this.editableTitleBarTheme.iconBackgroundHoverColor;
    } else {
      return this.editableTitleBarTheme.iconBackgroundColor;
    }
  }

  getFgColor(): ResourceStr {
    if (this.isOnClick) {
      return $r('sys.color.titlebar_icon_background_pressed_color');
    } else if (this.isOnHover) {
      return $r('sys.color.titlebar_icon_background_hover_color');
    } else {
      return EditableTitleBarV2.noneColor;
    }
  }

  getStringByNameSync(contextName: string): string {
    let uiContext: string = '';
    try {
      uiContext = getContext()?.resourceManager?.getStringByNameSync(contextName);
    } catch (exception) {
      let code: number = (exception as BusinessError)?.code;
      let message: string = (exception as BusinessError)?.message;
      hilog.error(0x3900, 'Ace', `Faild to getStringByNameSync,cause, code: ${code}, message: ${message}`);
    }
    return uiContext;
  }

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return resource;
    } else {
      let resourceString: string = '';
      try {
        if (resource.id === -1) {
          resourceString = getContext()?.resourceManager?.getStringByNameSync(resource.params?.[0]?.split('.').pop() ?? '');
        } else {
          resourceString = getContext()?.resourceManager?.getStringSync(resource);
        }
      } catch (err) {
        let code: number = (err as BusinessError)?.code;
        let message: string = (err as BusinessError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to EditableTitleBarV2 toStringFormat, code: ${code}, message: ${message}`)
      }
      return resourceString;
    }
  }

  private getAccessibilityReadText(): string | undefined {
    if (this.item.value === PUBLIC_OK) {
      return this.getStringByNameSync('icon_save');
    } else if (this.item.value === PUBLIC_CANCEL) {
      return this.getStringByNameSync('icon_cancel');
    } else if (this.item.value === PUBLIC_BACK) {
      return this.getStringByNameSync('icon_back');
    } else if (this.item.accessibilityText) {
      return this.item.accessibilityText as string;
    } else if (this.item.label) {
      return this.item.label as string;
    }
    return ' ';
  }

  private getRightIconAccessibilityLevel(): string {
    if (this.item.accessibilityLevel && this.item.accessibilityLevel !== '') {
      return this.item.accessibilityLevel;
    }
    return 'auto';
  }

  private getAccessibilityDescription(): string | undefined {
    if (this.item.accessibilityDescription && this.item.accessibilityDescription !== '') {
      return this.item.accessibilityDescription as string;
    }
    return '';
  }

  @Builder
  EditableTitleBarDialogBuilder(): void {
    EditableTitleBarDialogContent({
      itemEditableDialog: this.item,
      textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
      fontSize: this.fontSize,
    })
  }

  @Builder
  IconBuilder(): void {
    Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled }) {
      if (this.item.symbolStyle !== undefined) {
        SymbolGlyph()
          .fontColor([this.editableTitleBarTheme.iconColor])
          .attributeModifier(this.item.symbolStyle)
          .focusable(this.item.isEnabled)
          .enabled(this.item.isEnabled)
          .draggable(false)
          .accessibilityText(this.getAccessibilityReadText())
          .effectStrategy(SymbolEffectStrategy.NONE)
          .symbolEffect(new SymbolEffect(), false)
          .fontSize(SYMBOL_SIZE)
      } else {
        if (Util.isSymbolResource(this.item.value)) {
          SymbolGlyph(this.item.value as Resource)
            .fontSize(SYMBOL_SIZE)
            .fontColor([this.editableTitleBarTheme.iconColor])
            .focusable(this.item.isEnabled)
            .enabled(this.item.isEnabled)
            .draggable(false)
            .accessibilityText(this.getAccessibilityReadText())
        } else {
          Image(this.item.value)
            .fillColor(this.editableTitleBarTheme.iconColor)
            .matchTextDirection(this.item.value === PUBLIC_IMAGE_BACK ? true : false)
            .width($r('sys.float.titlebar_icon_width'))
            .height($r('sys.float.titlebar_icon_height'))
            .focusable(this.item.isEnabled)
            .enabled(this.item.isEnabled)
            .draggable(false)
            .accessibilityText(this.getAccessibilityReadText())
        }
      }
    }
    .id(this.imageMenuItemId)
    .backgroundButtonStyle()
    .borderRadius($r('sys.float.titlebar_icon_background_shape'))
    .margin({
      start: this.attribute === ItemType.LeftIcon ? LengthMetrics.vp(EditableTitleBarV2.commonZero) :
        LengthMetrics.resource($r('sys.float.titlebar_icon_background_space_horizontal')),
    })
    .focusOnTouch(true)
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
    .buttonStateStyles()
    .buttonEventStyle()
    .gestureModifier(this.buttonGestureModifier!)
    .accessibilityLevel(this.getRightIconAccessibilityLevel())
    .accessibilityDescription(this.getAccessibilityDescription())
    .defaultFocus(this.item.defaultFocus)
  }

  @Builder
  ImageBuilder() {
    Stack({ alignContent: Alignment.Center }) {
      Image(this.item.value)
        .width($r('sys.float.titlebar_icon_background_width'))
        .height($r('sys.float.titlebar_icon_background_height'))
        .borderRadius($r('sys.float.corner_radius_level10'))
        .focusable(false)
        .enabled(this.item.isEnabled)
        .objectFit(ImageFit.Cover)
      Button({ type: ButtonType.Circle })
        .backgroundButtonStyle()
        .foregroundColor(this.getFgColor())
        .backgroundColor(EditableTitleBarV2.noneColor)
        .buttonStateStyles()
        .buttonEventStyle()
        .gestureModifier(this.buttonGestureModifier!)
        .defaultFocus(this.item.defaultFocus)
    }
    .margin({
      start: LengthMetrics.resource($r('sys.float.titlebar_icon_background_space_horizontal')),
    })
  }

  build() {
    if (this.attribute === ItemType.Icon || this.attribute === ItemType.LeftIcon) {
      this.IconBuilder();
    } else {
      this.ImageBuilder();
    }
  }
}

@ComponentV2
struct EditableTitleBarDialogContent {
  @Param itemEditableDialog: EditableTitleBarMenuItem = {
    value: '',
    isEnabled: true,
  };
  callbackId: number | undefined = undefined;
  @Param textEditableTitleBarDialog?: ResourceStr = '';
  mainWindowStage: window.Window | undefined = undefined;
  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  screenWidth: number = 640;
  verticalScreenLines: number = 6;
  horizontalsScreenLines: number = 1;
  mainWindow: window.Window | undefined = undefined;
  @Param fontSize: number = 1;
  @Local maxLines: number = 1;
  windowStandardHeight: number = 0;

  build() {
    if (this.textEditableTitleBarDialog) {
      Column() {
        if (this.itemEditableDialog.symbolStyle !== undefined) {
          SymbolGlyph()
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(this.itemEditableDialog.symbolStyle)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            })
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
            .fontSize(SYMBOL_TITLE_SIZE)
            .direction(Direction.Ltr)
        } else {
          if (Util.isSymbolResource(this.itemEditableDialog.value)) {
            SymbolGlyph(this.itemEditableDialog.value as Resource)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              })
              .fontColor([$r('sys.color.icon_primary')])
              .fontSize(SYMBOL_TITLE_SIZE)
              .direction(Direction.Ltr)
          } else {
            Image(this.itemEditableDialog.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              })
              .fillColor($r('sys.color.icon_primary'))
              .direction(Direction.Ltr)
          }
        }
        Column() {
          Text(this.textEditableTitleBarDialog)
            .fontSize(TEXT_EDITABLE_DIALOG)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .maxLines(this.maxLines)
            .width('100%')
            .textAlign(TextAlign.Center)
            .fontColor($r('sys.color.font_primary'))
        }
        .width('100%')
        .padding({
          left: $r('sys.float.padding_level4'),
          right: $r('sys.float.padding_level4'),
          bottom: $r('sys.float.padding_level12'),
        })
      }
      .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
      .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius(($r('sys.float.corner_radius_level10')))
    } else {
      Column() {
        if (this.itemEditableDialog.symbolStyle !== undefined) {
          SymbolGlyph()
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(this.itemEditableDialog.symbolStyle)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
            .fontSize(SYMBOL_TITLE_SIZE)
        } else {
          if (Util.isSymbolResource(this.itemEditableDialog.value)) {
            SymbolGlyph(this.itemEditableDialog.value as Resource)
              .fontColor([$r('sys.color.icon_primary')])
              .fontSize(SYMBOL_TITLE_SIZE)
          } else {
            Image(this.itemEditableDialog.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
      .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius(($r('sys.float.corner_radius_level10')))
      .justifyContent(FlexAlign.Center)
      .direction(Direction.Ltr)
    }
  }

  async aboutToAppear(): Promise<void> {
    try {
      let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
      this.mainWindowStage = context.windowStage.getMainWindowSync();
    } catch (error) {
      let code: number = (error as BusinessError)?.code;
      let message: string = (error as BusinessError)?.message;
      hilog.error(0x3900, 'Ace', `EditableTitleBarV2 getMainWindowStage error, code: ${code},message:${message}`);
      return;
    }
    if (this.mainWindowStage) {
      let properties: window.WindowProperties = this.mainWindowStage.getWindowProperties();
      let rect = properties.windowRect;
      if (px2vp(rect.height) > this.screenWidth) {
        this.maxLines = this.verticalScreenLines;
      } else {
        this.maxLines = this.horizontalsScreenLines;
      }
    }
  }
}

function getNumberByResource(resourceId: number, defaultNumber: number): number {
  try {
    let resourceNumber: number = resourceManager.getSystemResourceManager().getNumber(resourceId);
    if (resourceNumber === 0) {
      return defaultNumber;
    } else {
      return resourceNumber;
    }
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `EditableTitleBarV2 getNumberByResource error, code: ${code},message:${message}`);
    return 0;
  }
}

class Util {
  private static RESOURCE_TYPE_SYMBOL = 40000;

  public static isSymbolResource(resourceStr: ResourceStr | undefined): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
    return resource.type === Util.RESOURCE_TYPE_SYMBOL;
  }

  public static isResourceType(resource: ResourceStr | Resource | undefined): boolean {
    if (!resource) {
      return false;
    }
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return false;
    }
    return true;
  }
}