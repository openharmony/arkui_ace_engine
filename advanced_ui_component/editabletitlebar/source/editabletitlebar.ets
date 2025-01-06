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

export enum EditableLeftIconType {
  Back,
  Cancel,
}

export declare interface EditableTitleBarMenuItem {
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

// 'sys.float.titlebar_title_tertiary_size' id,value: 20vp
const TITLE_F: number = getNumberByResource(125831095, TITLE_VP);
// 'sys.float.titlebar_subheader_size' id,value: 14vp
const SUBTITLE_F: number = getNumberByResource(125831097, SUBTITLE_VP);

const TITLE_F_VP: string = (TITLE_F > 0 ? TITLE_F : TITLE_VP) + 'vp';
const SUBTITLE_F_VP: string = (SUBTITLE_F > 0 ? SUBTITLE_F : SUBTITLE_VP) + 'vp';

class EditableTitleBarTheme {
  public iconColor: ResourceColor = $r('sys.color.titlebar_icon_color');
  public iconBackgroundColor: ResourceColor = $r('sys.color.titlebar_icon_background_color');
  public iconBackgroundPressedColor: ResourceColor = $r('sys.color.titlebar_icon_background_pressed_color');
  public iconBackgroundHoverColor: ResourceColor = $r('sys.color.titlebar_icon_background_hover_color');
  public iconBackgroundFocusOutlineColor: ResourceColor = $r('sys.color.titlebar_icon_background_focus_outline_color');
  public titleColor: ResourceColor = $r('sys.color.titlebar_title_tertiary_color');
  public subTitleColor: ResourceColor = $r('sys.color.titlebar_subheader_color');
}

class ButtonGestureModifier implements GestureModifier {
  public static readonly longPressTime: number = 500;
  public static readonly minFontSize: number = 1.75;
  public fontSize: number = 1;
  public controller: CustomDialogController | null = null;

  constructor(controller: CustomDialogController | null) {
    this.controller = controller;
  }

  applyGesture(event: UIGestureEvent): void {
    if (this.fontSize >= ButtonGestureModifier.minFontSize) {
      event.addGesture(
        new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
          .onAction(() => {
            if (event) {
              this.controller?.open();
            }
          })
          .onActionEnd(() => {
            this.controller?.close();
          })
      )
    } else {
      event.clearGestures();
    }
  }
}

@Component
export struct EditableTitleBar {
  leftIconStyle: EditableLeftIconType = EditableLeftIconType.Back;
  title: ResourceStr = '';
  subtitle?: ResourceStr = '';
  isSaveIconRequired: boolean = true;
  imageItem?: EditableTitleBarItem;
  menuItems: Array<EditableTitleBarMenuItem> | undefined = undefined;
  options: EditableTitleBarOptions = {};
  onSave?: () => void;
  onCancel?: () => void;
  constraintWidth: number = 0;
  leftIconDefaultFocus?: boolean = false;
  saveIconDefaultFocus?: boolean = false;
  public static readonly maxCountOfExtraItems = 3;
  public static readonly maxOtherCountOfExtraItems = 2;
  public static readonly commonZero = 0;
  public static readonly noneColor = '#00000000';
  // 'sys.float.titlebar_default_height' id,value: 56vp
  public static readonly defaultHeight: number = getNumberByResource(125831115, DEFAULT_TITLE_BAR_HEIGHT);
  // 'sys.float.padding_level1' id,value: 2vp
  public static readonly defaultTitlePadding: number = getNumberByResource(125830920, DEFAULT_TITLE_PADDING);
  public static readonly totalHeight: number =
    EditableTitleBar.defaultHeight === EditableTitleBar.commonZero ? DEFAULT_TITLE_BAR_HEIGHT :
    EditableTitleBar.defaultHeight;
  static readonly titlePadding: number =
    EditableTitleBar.defaultTitlePadding === EditableTitleBar.commonZero ?
      DEFAULT_TITLE_PADDING : EditableTitleBar.defaultTitlePadding;
  private static readonly maxMainTitleHeight =
    (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_MAIN_TITLE_PERCENT;
  private static readonly maxSubTitleHeight =
    (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_SUB_TITLE_PERCENT;
  private isFollowingSystemFontScale: boolean = false;
  private maxFontScale: number = 1;
  private systemFontScale?: number = 1;
  @Provide editableTitleBarTheme: EditableTitleBarTheme = new EditableTitleBarTheme();
  @Prop contentMargin?: LocalizedMargin;
  @State titleBarMargin: LocalizedMargin = {
    start: LengthMetrics.resource($r('sys.float.margin_left')),
    end: LengthMetrics.resource($r('sys.float.margin_right')),
  }
  @State fontSize: number = 1;

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
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
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

        Row() {
          this.rightMenuItemsLayout();
        }
        .flexShrink(0)
      }
      .width('100%')
      .margin(this.contentMargin ?? this.titleBarMargin)
      .height(EditableTitleBar.totalHeight)
    }
    .backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor)
    .backgroundBlurStyle(
      this.options.backgroundBlurStyle ?? BlurStyle.NONE)
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
    })
  }

  @Builder
  leftIconLayout(): void {
    if (this.leftIconStyle === EditableLeftIconType.Back) {
      ImageMenuItem({
        item: {
          value: PUBLIC_BACK,
          isEnabled: true,
          action: () => this.onCancel ? this.onCancel() : this.getUIContext()?.getRouter()?.back(),
          defaultFocus: this.leftIconDefaultFocus
        },
        fontSize: this.fontSize,
        attribute: ItemType.LeftIcon,
        imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`
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
        imageMenuItemId: `CancelMenuItem_${this.getUniqueId()}`
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
            maxHeight: this.subtitle ? EditableTitleBar.maxMainTitleHeight : EditableTitleBar.totalHeight,
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
              maxHeight: this.title ? EditableTitleBar.maxSubTitleHeight : EditableTitleBar.totalHeight,
            })
        }
        .margin({
          top: $r('sys.float.padding_level1'),
        })
        .justifyContent(FlexAlign.Start)
      }
    }
    .height(EditableTitleBar.totalHeight)
    .justifyContent(FlexAlign.Center)
    .margin({
      // 'sys.float.titlebar_icon_background_space_horizontal' id,value: 8vp
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
      saveIconDefaultFocus: this.saveIconDefaultFocus
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
    children.forEach((child) => {
      result.height = child.measure(constraint).height;
      result.width = Number(constraint.maxWidth);
    })
    return result;
  }
}

@Component
struct EditableTitleBarMenuSection {
  menuItems: Array<EditableTitleBarMenuItem> | undefined = undefined;
  onSave?: () => void;
  isSaveEnabled: boolean = true;
  saveIconDefaultFocus?: boolean = false;
  @Prop fontSize: number = 1;
  @Prop parentUniqueId?: number;

  build() {
    Column() {
      Row() {
        if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
          ForEach(this.menuItems.slice(EditableTitleBar.commonZero,
            this.isSaveEnabled ?
            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems),
            (item: EditableTitleBarMenuItem, index: number) => {
              ImageMenuItem({
                item: item,
                attribute: ItemType.Icon,
                fontSize: this.fontSize,
                imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${index}`
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
            imageMenuItemId: `SaveMenuItem_${this.parentUniqueId}`
          })
        }
      }
    }
    .justifyContent(FlexAlign.Center)
  }
}

@Component
struct ImageMenuItem {
  item: EditableTitleBarMenuItem = {
    value: '',
    isEnabled: true,
    label: '',
    accessibilityLevel: 'auto',
    accessibilityText: '',
    accessibilityDescription: '',
  };
  attribute: ItemType = ItemType.Image;
  callbackId: number | undefined = undefined;
  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  longPressTime: number = 500;
  @Prop @Watch('onFontSizeUpdated') fontSize: number = 1;
  @State isOnFocus: boolean = false;
  @State isOnHover: boolean = false;
  @State isOnClick: boolean = false;
  imageMenuItemId?: string;
  @Consume editableTitleBarTheme: EditableTitleBarTheme;
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: EditableTitleBarDialog({
      cancel: () => {
      },
      confirm: () => {
      },
      itemEditableDialog: this.item,
      textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
      fontSize: this.fontSize,
    }),
    maskColor: Color.Transparent,
    isModal: true,
    customStyle: true,
  });
  @State buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier(this.dialogController);

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

  onFontSizeUpdated(): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
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
      width: EditableTitleBar.commonZero,
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
      if (this.fontSize >= this.minFontSize) {
        this.dialogController?.close()
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
      return EditableTitleBar.noneColor;
    }
  }

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return resource;
    } else {
      let resourceString: string = '';
      try {
        resourceString = getContext()?.resourceManager?.getStringSync(resource);
      } catch (err) {
        let code: number = (err as BusinessError)?.code;
        let message: string = (err as BusinessError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to subHeader toStringFormat, code: ${code}, message: ${message}`)
      }
      return resourceString;
    }
  }

  private getAccessibilityReadText(): string | undefined {
    if (this.item.value === PUBLIC_OK) {
      return getContext()?.resourceManager?.getStringByNameSync('icon_save');
    } else if (this.item.value === PUBLIC_CANCEL) {
      return getContext()?.resourceManager?.getStringByNameSync('icon_cancel');
    } else if (this.item.value === PUBLIC_BACK) {
      return getContext()?.resourceManager?.getStringByNameSync('icon_back');
    } else if (this.item.accessibilityText) {
      return this.toStringFormat(this.item.accessibilityText);
    } else if (this.item.label) {
      return this.toStringFormat(this.item.label);
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
      return this.toStringFormat(this.item.accessibilityDescription);
    }
    return '';
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
          .defaultFocus(this.item.isEnabled ? this.item.defaultFocus : false)
      } else {
        if (Util.isSymbolResource(this.item.value)) {
          SymbolGlyph(this.item.value as Resource)
            .fontSize(SYMBOL_SIZE)
            .fontColor([this.editableTitleBarTheme.iconColor])
            .focusable(this.item.isEnabled)
            .enabled(this.item.isEnabled)
            .draggable(false)
            .accessibilityText(this.getAccessibilityReadText())
            .defaultFocus(this.item.isEnabled ? this.item.defaultFocus : false)
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
            .defaultFocus(this.item.isEnabled ? this.item.defaultFocus : false)
        }
      }
    }
    .id(this.imageMenuItemId)
    .backgroundButtonStyle()
    .borderRadius($r('sys.float.titlebar_icon_background_shape'))
    .margin({
      start: this.attribute === ItemType.LeftIcon ? LengthMetrics.vp(EditableTitleBar.commonZero) :
      LengthMetrics.resource($r('sys.float.titlebar_icon_background_space_horizontal')),
    })
    .focusOnTouch(true)
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
    .buttonStateStyles()
    .buttonEventStyle()
    .gestureModifier(this.buttonGestureModifier)
    .accessibilityLevel(this.getRightIconAccessibilityLevel())
    .accessibilityDescription(this.getAccessibilityDescription())
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
        .backgroundColor(EditableTitleBar.noneColor)
        .buttonStateStyles()
        .buttonEventStyle()
        .gestureModifier(this.buttonGestureModifier)
        .defaultFocus(this.item.isEnabled ? this.item.defaultFocus : false)
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

/**
 * EditableTitleBarDialog
 *
 * @since 2024-05-28
 */
@CustomDialog
struct EditableTitleBarDialog {
  itemEditableDialog: EditableTitleBarMenuItem = {
    value: '',
    isEnabled: true,
  };
  callbackId: number | undefined = undefined;
  textEditableTitleBarDialog?: ResourceStr = '';
  mainWindowStage: window.Window | undefined = undefined;
  controller?: CustomDialogController
  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  screenWidth: number = 640;
  verticalScreenLines: number = 6;
  horizontalsScreenLines: number = 1;
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  @StorageLink('mainWindow') mainWindow: Promise<window.Window> | undefined = undefined;
  @Prop fontSize: number = 1;
  @State maxLines: number = 1;
  @StorageProp('windowStandardHeight') windowStandardHeight: number = 0;

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
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK)
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
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK)
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius(($r('sys.float.corner_radius_level10')))
      .justifyContent(FlexAlign.Center)
      .direction(Direction.Ltr)
    }
  }

  async aboutToAppear(): Promise<void> {
    let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
    this.mainWindowStage = context.windowStage.getMainWindowSync();
    let properties: window.WindowProperties = this.mainWindowStage.getWindowProperties();
    let rect = properties.windowRect;
    if (px2vp(rect.height) > this.screenWidth) {
      this.maxLines = this.verticalScreenLines;
    } else {
      this.maxLines = this.horizontalsScreenLines;
    }
  }
}

/**
 * get resource size
 *
 * @param resourceId resource id
 * @return resource size
 */
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
    hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${code},message:${message}`);
    return 0;
  }
}

class Util {
  private static RESOURCE_TYPE_SYMBOL = 40000;

  public static isSymbolResource(resourceStr: ResourceStr | undefined): boolean {
    if (resourceStr === undefined) {
      return true;
    }
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
    return resource.type === Util.RESOURCE_TYPE_SYMBOL;
  }

  public static isResourceType(resource: ResourceStr): boolean {
    if (!resource) {
      return false;
    }
    return typeof resource !== 'string';
  }
}
