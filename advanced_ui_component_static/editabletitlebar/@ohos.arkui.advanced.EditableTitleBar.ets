/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import {
  ResourceStr, ResourceColor, BlurStyle, SafeAreaType, SafeAreaEdge, GestureModifier, CustomDialogController,
  UIGestureEvent, LongPressGestureHandler, Component, LocalizedMargin, UIContext, Flex, FlexAlign, ItemAlign,
  Row, Builder, Column, Text, FontWeight, TextAlign, TextOverflow, TextHeightAdaptivePolicy, HorizontalAlign,
  GeometryInfo, Layoutable, ConstraintSizeOptions, Measurable, SizeResult, ForEach, Color, CommonMethod, StateStyles,
  BorderStyle, TouchEvent, TouchType, KeyEvent, KeyType, Button, ButtonType, SymbolGlyph, SymbolEffectStrategy,
  SymbolEffect, Resource, Image, Stack, Alignment, ImageFit, Circle, Direction, ShadowStyle, $r, Margin,
  Padding, ButtonOptions, SymbolGlyphModifier, HoverEvent, ClickEvent, TapGestureHandler, PanGestureHandler,
  GestureEvent, applyStyles, CustomDialog, CustomDialogControllerOptions, CustomLayout, Callback, ClassCastError
} from '@ohos.arkui.component';
import display from '@ohos.display'
import hilog from '@ohos.hilog';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import resourceManager from '@ohos.resourceManager';
import { Theme } from '@ohos.arkui.theme';
import { LengthMetrics } from '@ohos.arkui.node';
import common from '@ohos.app.ability.common';
import window from '@ohos.window';
import { Context } from '@ohos.arkui.UIContext';
import EnvironmentCallback from '@ohos.app.ability.EnvironmentCallback';
import { State, Observed, Prop, PropRef, StorageProp, StorageLink, Provide, Consume } from '@ohos.arkui.stateManagement'
import { Configuration } from '@ohos.app.ability.Configuration';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';
import ApplicationContext from 'application.ApplicationContext';

export enum EditableLeftIconType {
  Back,
  Cancel,
}

export class EditableTitleBarMenuItem {
  public value: ResourceStr = '';
  public symbolStyle?: SymbolGlyphModifier;
  public isEnabled?: boolean;
  public label?: ResourceStr;
  public action?: () => void;
  public accessibilityLevel?: string;
  public accessibilityText?: ResourceStr;
  public accessibilityDescription?: ResourceStr;
  public defaultFocus?: boolean;
}

export type EditableTitleBarItem = EditableTitleBarMenuItem;

export interface EditableTitleBarOptions {
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

const DEFAULT_TITLE_BAR_HEIGHT: number = 56;
const DEFAULT_TITLE_PADDING: number = 2;
const MAX_LINE_ONE: int = 1;
const MAX_LINES_TWO: int = 2;
const MAX_MAIN_TITLE_PERCENT: number = 0.65;
const MAX_SUB_TITLE_PERCENT: number = 0.35;
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
        new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime as int})
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

class EnvironmentCallbackEntry implements EnvironmentCallback {
  private imageMenuItem: ImageMenuItem;

  constructor(imageMenuItem: ImageMenuItem) {
    this.imageMenuItem = imageMenuItem;
  }

  onConfigurationUpdated(config: Configuration) {

    if (config === undefined || !this.imageMenuItem.isFollowingSystemFontScale) {
      this.imageMenuItem.fontSize = 1;
      return;
    }
    try {
      this.imageMenuItem.fontSize = Math.min(
        this.imageMenuItem.maxFontScale, config.fontSizeScale ?? 1);
      this.imageMenuItem.buttonGestureModifier.fontSize = this.imageMenuItem.fontSize;
    } catch (paramError) {
      let code = (paramError as ClassCastError)?.code;
      let message = (paramError as ClassCastError)?.message;
      hilog.error(0x3900, 'Ace',
        `EditableTitleBar environmentCallback error: ${code}, ${message}`);
    }
  }

  onMemoryLevel(level: AbilityConstant.MemoryLevel) {
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
  options: EditableTitleBarOptions = {} as EditableTitleBarOptions;
  onSave?: () => void;
  onCancel?: () => void;
  constraintWidth: number = 0;
  leftIconDefaultFocus?: boolean = false;
  saveIconDefaultFocus?: boolean = false;
  public static readonly maxCountOfExtraItems: number = 3;
  public static readonly maxOtherCountOfExtraItems: number = 2;
  public static readonly commonZero: number = 0;
  public static readonly noneColor: string = '#00000000';
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
  private static readonly maxMainTitleHeight: number =
    (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_MAIN_TITLE_PERCENT;
  private static readonly maxSubTitleHeight: number =
    (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_SUB_TITLE_PERCENT;
  private isFollowingSystemFontScale: boolean = false;
  private maxFontScale: number = 1;
  private systemFontScale?: number = 1;
  @Provide editableTitleBarTheme: EditableTitleBarTheme = new EditableTitleBarTheme();
  @PropRef contentMargin: LocalizedMargin | undefined = undefined;
  @State titleBarMargin: LocalizedMargin = {
    start: LengthMetrics.resource($r('sys.float.margin_left')),
    end: LengthMetrics.resource($r('sys.float.margin_right')),
  } as LocalizedMargin
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
      if (uiContent.getHostContext() !== undefined) {
        this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
        this.maxFontScale = uiContent.getMaxFontScale();
      }
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | String = (exception as ClassCastError)?.message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
    }
  }

  decideFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    if (uiContent.getHostContext() !== undefined) {
      this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    }
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale as number, this.maxFontScale as number);
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
      .height(EditableTitleBar.totalHeight)
    }
    .backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor)
    .backgroundBlurStyle(
      this.options.backgroundBlurStyle ?? BlurStyle.NONE, undefined, { disableSystemAdaptation: true })
    .expandSafeArea(
      this.options.safeAreaTypes ?? [SafeAreaType.SYSTEM],
      this.options.safeAreaEdges ?? [SafeAreaEdge.TOP],
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
          action: () => {
            if (this.onCancel) {
              this.onCancel?.()
            } else {
              this.getUIContext()?.getRouter()?.back()
            }
          },
          defaultFocus: this.leftIconDefaultFocus
        } as EditableTitleBarMenuItem,
        fontSize: this.fontSize,
        attribute: ItemType.LeftIcon,
        imageMenuItemId: `BackMenuItem_${this.getUniqueId()}`
      })
    } else {
      ImageMenuItem({
        item: {
          value: PUBLIC_CANCEL,
          isEnabled: true,
          action: () => {
            if (this.onCancel) {
              this.onCancel?.()
            }
          },
          defaultFocus: this.leftIconDefaultFocus as boolean
        } as EditableTitleBarMenuItem,
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
        } as Margin)
        .justifyContent(FlexAlign.Start)
      }
    }
    .height(EditableTitleBar.totalHeight)
    .justifyContent(FlexAlign.Center)
    .margin({
      // 'sys.float.titlebar_icon_background_space_horizontal' id,value: 8vp
      start: LengthMetrics.resource($r('sys.float.titlebar_icon_background_space_horizontal')),
    } as LocalizedMargin)
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
      let childMeasureResult = child.measure(constraint);
      if (childMeasureResult) {
        result.height = childMeasureResult.height;
      }
      result.width = Number(constraint.maxWidth as number);
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
  @PropRef fontSize: number = 1;
  @PropRef parentUniqueId: number | undefined = undefined;

  build() {
    Column() {
      Row() {
        if (this.menuItems) {
          ForEach((this.menuItems as EditableTitleBarMenuItem[]).slice(EditableTitleBar.commonZero.toInt(),
            this.isSaveEnabled ?
              EditableTitleBar.maxOtherCountOfExtraItems.toInt() : EditableTitleBar.maxCountOfExtraItems.toInt()),
            (item: EditableTitleBarMenuItem, index: int) => {
              ImageMenuItem({
                item: item,
                attribute: ItemType.Icon,
                imageMenuItemId: `ImageMenuItem_${this.parentUniqueId}_${index}`
              })
            })
        }
        if (this.isSaveEnabled) {
          ImageMenuItem({
            item: {
              value: PUBLIC_OK,
              isEnabled: true,
              action: () => {
                if (this.onSave) {
                  this.onSave?.()
                }
              },
              defaultFocus: this.saveIconDefaultFocus
            } as EditableTitleBarMenuItem,
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
  } as EditableTitleBarMenuItem;
  attribute: ItemType = ItemType.Image;
  callbackId: number | undefined = undefined;
  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  longPressTime: number = 500;
  systemFontScale?: number = 1;
  isFollowingSystemFontScale: boolean = this.getUIContext().isFollowingSystemFontScale();
  maxFontScale: number = this.getUIContext().getMaxFontScale();
  applicationContext: ApplicationContext = new ApplicationContext()
  @State fontSize: number = 1;
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
  private envCallback: EnvironmentCallbackEntry = new EnvironmentCallbackEntry(this)
  @Observed
  @State buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier(this.dialogController);

  private textDialog(): ResourceStr {
    if (this.item.value === PUBLIC_OK) {
      return $r('sys.string.icon_save');
    } else if (this.item.value === PUBLIC_CANCEL) {
      return $r('sys.string.icon_cancel');
    } else if (this.item.value === PUBLIC_BACK) {
      return $r('sys.string.icon_back');
    } else {
      return this.item.label ? this.item.label as ResourceStr : '' as ResourceStr;
    }
  }

  aboutToAppear() {
    try {
      let context: UIContext = this.getUIContext();
      if (context.getHostContext() !== undefined) {
        let hostContext: common.UIAbilityContext = context.getHostContext() as common.UIAbilityContext
        this.applicationContext = hostContext.getApplicationContext();
        try {
          this.callbackId = this.applicationContext.onEnvironment(this.envCallback);
        } catch (paramError) {
          hilog.error(0x3900, 'Ace',
            `EditableTitleBar Faild to get environment param error `);
        }
      }
    } catch (paramError) {
      let code = (paramError as ClassCastError)?.code;
      let message = (paramError as ClassCastError)?.message;
      hilog.error(0x3900, 'Ace',
        `EditableTitleBar Faild to get environment param error: ${code}, ${message}`);
    }
    this.fontSize = this.decideFontScale();
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  decideFontScale(): number {
    try {
      let uiContent: UIContext = this.getUIContext();
      if (uiContent.getHostContext() != undefined) {
        this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      }
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale as number, this.maxFontScale as number);
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | String = (exception as ClassCastError)?.message;
      hilog.error(0x3900, 'EditableTitleBar', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  focusedStyle(instance: CommonMethod) {
    instance.border({
      radius: $r('sys.float.titlebar_icon_background_shape'),
      width: $r('sys.float.titlebar_icon_background_focus_outline_weight'),
      color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
      style: BorderStyle.Solid,
    })
  }

  notInFocusedStyle(instance: CommonMethod) {
    instance.border({
      radius: $r('sys.float.titlebar_icon_background_shape'),
      width: EditableTitleBar.commonZero,
    })
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

  getStringByNameSync(contextName: string): undefined | String {
    let uiContext: undefined | String = '';
    try {
      let context: UIContext = this.getUIContext();
      if (context.getHostContext() !== undefined) {
        let hostContext: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;
        uiContext = hostContext?.resourceManager?.getStringByNameSync(contextName);
      }
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | String = (exception as ClassCastError)?.message;
      hilog.error(0x3900, 'Ace', `Faild to getStringByNameSync,cause, code: ${code}, message: ${message}`);
    }
    return uiContext;
  }

  private toStringFormat(resource: ResourceStr | undefined | Long): string | undefined {
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      if (typeof resource === 'string') {
        return resource as string;
      } else if (typeof resource === 'undefined') {
        return resource as undefined;
      }
    } else {
      let resourceString: string | undefined = '';
      try {
        let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
        if ((resource as Resource).id === -1 && (resource as Resource).params?.[0] !== undefined) {
          resourceString =
            context?.resourceManager?.getStringByNameSync(((resource as Resource).params?.[0] as string).split('.')
              .pop() ?? '');
        } else {
          resourceString = context?.resourceManager?.getStringSync(resource as Long);
        }
      } catch (err) {
        let code: undefined | int = (err as ClassCastError)?.code;
        let message: undefined | String = (err as ClassCastError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to EditableTitleBar toStringFormat, code: ${code}, message: ${message}`)
      }
      return resourceString;
    }
    return undefined;
  }

  private getAccessibilityReadText(): string | undefined {
    if (this.item.value === PUBLIC_OK) {
      return this.getStringByNameSync('icon_save');
    } else if (this.item.value === PUBLIC_CANCEL) {
      return this.getStringByNameSync('icon_cancel');
    } else if (this.item.value === PUBLIC_BACK) {
      return this.getStringByNameSync('icon_back');
    } else if (this.item.accessibilityText) {
      return this.toStringFormat(this.item.accessibilityText) as string;
    } else if (this.item.label) {
      return this.item.label as string;
    }
    return ' ';
  }

  private getRightIconAccessibilityLevel(): string {
    if (this.item.accessibilityLevel && this.item.accessibilityLevel !== '') {
      return this.item.accessibilityLevel as string;
    }
    return 'auto';
  }

  private getAccessibilityDescription(): string | undefined {
    if (Util.isResourceType(this.item.accessibilityDescription)) {
      return (this.getUIContext().getHostContext() as common.Context).resourceManager
        .getStringSync((this.item.accessibilityDescription as Resource).id);
    } else if (this.item.accessibilityDescription && this.item.accessibilityDescription !== '') {
      return this.item.accessibilityDescription as string;
    }
    return '';
  }

  @Builder
  IconBuilder(): void {
    Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
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
            .accessibilityText(this.getAccessibilityReadText() as string)
            .defaultFocus(this.item.isEnabled ? this.item.defaultFocus : false)
        }
      }
    }
    .id(this.imageMenuItemId)
    .width($r('sys.float.titlebar_icon_background_width'))
    .height($r('sys.float.titlebar_icon_background_height'))
    .focusable(this.item.isEnabled)
    .enabled(this.item.isEnabled)
    .borderRadius($r('sys.float.titlebar_icon_background_shape'))
    .margin({
      start: this.attribute === ItemType.LeftIcon ? LengthMetrics.vp(EditableTitleBar.commonZero) :
        LengthMetrics.resource($r('sys.float.titlebar_icon_background_space_horizontal')),
    } as LocalizedMargin)
    .focusOnTouch(true)
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
    .stateStyles({
      focused: this.focusedStyle,
      normal: this.notInFocusedStyle,
      pressed: this.notInFocusedStyle,
    })
    .onFocus(() => {
      if (!this.item.isEnabled) {
        return;
      }
      this.isOnFocus = true;
    })
    .onBlur(() => {
      this.isOnFocus = false
    })
    .onHover((isOn: boolean, event?: HoverEvent) => {
      if (!this.item.isEnabled) {
        return;
      }
      this.isOnHover = isOn;
    })
    .onKeyEvent((event: KeyEvent): boolean => {
      if (!this.item.isEnabled) {
        return false;
      }
      if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
        return false;
      }
      if (event.type === KeyType.Down) {
        this.isOnClick = true;
      }
      if (event.type === KeyType.Up) {
        this.isOnClick = false;
      }
      return true;
    })
    .onTouch((event: TouchEvent) => {
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
    })
    .onClick((event?: ClickEvent) => {
      if ((this.item.isEnabled as boolean | undefined) === undefined) {
        this.item.isEnabled = true;
      }
      this.item.isEnabled && this.item.action?.()
    })
    .gestureModifier(this.buttonGestureModifier)
    .accessibilityLevel(this.getRightIconAccessibilityLevel())

    .accessibilityDescription(this.getAccessibilityDescription() as string)
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
      Button({ type: ButtonType.Circle } as ButtonOptions)
        .width($r('sys.float.titlebar_icon_background_width'))
        .height($r('sys.float.titlebar_icon_background_height'))
        .focusable(this.item.isEnabled)
        .enabled(this.item.isEnabled)
        .foregroundColor(this.getFgColor())
        .backgroundColor(EditableTitleBar.noneColor)
        .stateStyles({
          focused: this.focusedStyle,
          normal: this.notInFocusedStyle,
          pressed: this.notInFocusedStyle,
        })
        .onFocus(() => {
          if (!this.item.isEnabled) {
            return;
          }
          this.isOnFocus = true;
        })
        .onBlur(() => {
          this.isOnFocus = false
        })
        .onHover((isOn: boolean, event?: HoverEvent) => {
          if (!this.item.isEnabled) {
            return;
          }
          this.isOnHover = isOn;
        })
        .onKeyEvent((event: KeyEvent): boolean => {
          if (!this.item.isEnabled) {
            return false;
          }
          if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
            return false;
          }
          if (event.type === KeyType.Down) {
            this.isOnClick = true;
          }
          if (event.type === KeyType.Up) {
            this.isOnClick = false;
          }
          return true;
        })
        .onTouch((event: TouchEvent) => {
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
        })
        .onClick((event?: ClickEvent) => {
          if ((this.item.isEnabled as boolean | undefined) === undefined) {
            this.item.isEnabled = true;
          }
          this.item.isEnabled && this.item.action?.()
        })
        .gestureModifier(this.buttonGestureModifier)
        .defaultFocus(this.item.isEnabled ? this.item.defaultFocus : false)
    }
    .margin({
      start: LengthMetrics.resource($r('sys.float.titlebar_icon_background_space_horizontal')),
    } as LocalizedMargin)
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
  } as EditableTitleBarMenuItem;
  callbackId: number | undefined = undefined;
  textEditableTitleBarDialog?: ResourceStr = '';
  mainWindowStage: window.Window | undefined = undefined;
  controller?: CustomDialogController
  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  screenWidth: number = 640;
  verticalScreenLines: int = 6;
  horizontalsScreenLines: int = 1;
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  @PropRef fontSize: number = 1;
  @State maxLines: int = 1;
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
            } as Margin)
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
              } as Margin)
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
              } as Margin)
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
        } as Padding)
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

  aboutToAppear(): void {
    try {
      let context: UIContext = this.getUIContext();
      if (context.getHostContext() !== undefined) {
        let hostContext: common.UIAbilityContext = context.getHostContext() as common.UIAbilityContext
        this.mainWindowStage = hostContext?.windowStage.getMainWindowSync();
      }
    } catch (error) {
      let code: undefined | int = (error as ClassCastError)?.code;
      let message: undefined | String = (error as ClassCastError)?.message;
      hilog.error(0x3900, 'Ace', `EditableTitleBar getMainWindowStage error, code: ${code},message:${message}`);
    }
    let properties: window.WindowProperties =
      this.mainWindowStage?.getWindowProperties() as window.WindowProperties;
    let rect = properties.windowRect;
    if (this.getUIContext().px2vp(rect.height) > this.screenWidth) {
      this.maxLines = this.verticalScreenLines;
    } else {
      this.maxLines = this.horizontalsScreenLines;
    }
  }
}

const densityPixels: number = ((): number => {
  try {
    let densityPixels: number = display.getDefaultDisplaySync().densityPixels;
    return densityPixels;
  } catch (error) {
    let code = (error as ClassCastError)?.code;
    let message = (error as ClassCastError)?.message;
    return 1;
  }
})();

/**
 * get resource size
 *
 * @param resourceId resource id
 * @return resource size
 */
function getNumberByResource(resourceId: number, defaultNumber: number): number {
  try {
    let resourceNumber: number = resourceManager.getSysResourceManager().getDouble(resourceId as Long);
    if (resourceNumber === 0) {
      return defaultNumber;
    } else {
      return resourceNumber / densityPixels;
    }
  } catch (error) {
    let code: int = (error as ClassCastError).code;
    let message: string = (error as ClassCastError).message;
    hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${code},message:${message}`);
    return 0;
  }
}

class Util {
  private static RESOURCE_TYPE_SYMBOL: number = 40000;

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