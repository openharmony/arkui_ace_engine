/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
  ComponentV2, Flex, FlexAlign, ItemAlign, Row, Image, Column, Text, FontWeight, TextAlign, TextOverflow,
  TextHeightAdaptivePolicy, HorizontalAlign, GeometryInfo, Layoutable, ConstraintSizeOptions, Measurable,
  SizeResult, ForEach, Color, BorderStyle, TouchEvent, TouchType, KeyEvent, KeyType,
  Button, ButtonType, SymbolGlyph, SymbolEffectStrategy, SymbolEffect, ImageFit, BlurStyle, SafeAreaType,
  SafeAreaEdge, Direction, ShadowStyle, $r, Margin, Padding, ButtonOptions, HoverEvent, ClickEvent,
  UIContext, Resource, Stack, Alignment, ResourceStr,
  ResourceColor, LocalizedMargin, GestureModifier, UIGestureEvent, LongPressGestureHandler
} from '@ohos.arkui.component';
import { SymbolGlyphModifier } from '@ohos.arkui.modifier'
import { LengthMetrics } from '@ohos.arkui.node';
import { Param, Local, Monitor, IMonitor, ObservedV2, Trace } from '@ohos.arkui.stateManagement';
import { Theme } from '@ohos.arkui.theme';

import hilog from '@ohos.hilog';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import common from '@ohos.app.ability.common';
import window from '@ohos.window';
import promptAction from '@ohos.promptAction';
import EnvironmentCallback from '@ohos.app.ability.EnvironmentCallback';
import { Configuration } from '@ohos.app.ability.Configuration';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';
import { Require } from '@kit.ArkUI';

export type OnActionCallback = () => void;

export enum EditableLeftIconTypeV2 {
  Back = 0,
  Cancel = 1,
}

export interface EditableLeftIconV2Options {
  iconType?: EditableLeftIconTypeV2;
  defaultFocus?: boolean;
  onAction?: OnActionCallback;
}

@ObservedV2
export class EditableLeftIconV2 {
  @Trace public iconType: EditableLeftIconTypeV2 = EditableLeftIconTypeV2.Back;
  @Trace public defaultFocus: boolean = false;
  @Trace public onAction?: OnActionCallback;

  constructor(options?: EditableLeftIconV2Options) {
    if (options?.iconType !== undefined) {
      this.iconType = options!.iconType!;
    }
    if (options?.defaultFocus !== undefined) {
      this.defaultFocus = options!.defaultFocus!;
    }
    if (options?.onAction !== undefined) {
      this.onAction = options!.onAction;
    }
  }
}

export interface EditableTitleV2Options {
  mainTitle?: ResourceStr;
  subTitle?: ResourceStr;
}

@ObservedV2
export class EditableTitleV2 {
  @Trace public mainTitle: ResourceStr = '';
  @Trace public subTitle?: ResourceStr;

  constructor(options?: EditableTitleV2Options) {
    if (options?.mainTitle !== undefined) {
      this.mainTitle = options!.mainTitle!;
    }
    if (options?.subTitle !== undefined) {
      this.subTitle = options!.subTitle;
    }
  }
}

export interface EditableTitleBarMenuItemV2Options {
  value?: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
  isEnabled?: boolean;
  label?: ResourceStr;
  action?: OnActionCallback;
  accessibilityLevel?: string;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  defaultFocus?: boolean;
}

@ObservedV2
export class EditableTitleBarMenuItemV2 {
  @Trace public value: ResourceStr = '';
  @Trace public symbolStyle?: SymbolGlyphModifier;
  @Trace public isEnabled: boolean = true;
  @Trace public label?: ResourceStr;
  @Trace public action?: OnActionCallback;
  @Trace public accessibilityLevel: string = 'auto';
  @Trace public accessibilityText?: ResourceStr;
  @Trace public accessibilityDescription?: ResourceStr;
  @Trace public defaultFocus: boolean = false;

  constructor(options?: EditableTitleBarMenuItemV2Options) {
    if (options?.value !== undefined) {
      this.value = options!.value!;
    }
    if (options?.symbolStyle !== undefined) {
      this.symbolStyle = options!.symbolStyle;
    }
    if (options?.isEnabled !== undefined) {
      this.isEnabled = options!.isEnabled!;
    }
    if (options?.label !== undefined) {
      this.label = options!.label;
    }
    if (options?.action !== undefined) {
      this.action = options!.action;
    }
    if (options?.accessibilityLevel !== undefined) {
      this.accessibilityLevel = options!.accessibilityLevel!;
    }
    if (options?.accessibilityText !== undefined) {
      this.accessibilityText = options!.accessibilityText;
    }
    if (options?.accessibilityDescription !== undefined) {
      this.accessibilityDescription = options!.accessibilityDescription;
    }
    if (options?.defaultFocus !== undefined) {
      this.defaultFocus = options!.defaultFocus!;
    }
  }
}

export type EditableTitleBarItemV2 = EditableTitleBarMenuItemV2;
export type EditableTitleBarItemV2Options = EditableTitleBarMenuItemV2Options;

export interface EditableSaveButtonV2Options {
  isRequired?: boolean;
  defaultFocus?: boolean;
  onAction?: OnActionCallback;
}

@ObservedV2
export class EditableSaveButtonV2 {
  @Trace public isRequired: boolean = true;
  @Trace public defaultFocus: boolean = false;
  @Trace public onAction?: OnActionCallback;

  constructor(options?: EditableSaveButtonV2Options) {
    if (options?.isRequired !== undefined) {
      this.isRequired = options!.isRequired!;
    }
    if (options?.defaultFocus !== undefined) {
      this.defaultFocus = options!.defaultFocus!;
    }
    if (options?.onAction !== undefined) {
      this.onAction = options!.onAction;
    }
  }
}

export interface EditableTitleBarStyleV2Options {
  backgroundColor?: ResourceColor;
  backgroundBlurStyle?: BlurStyle;
  safeAreaTypes?: Array<SafeAreaType>;
  safeAreaEdges?: Array<SafeAreaEdge>;
  contentMargin?: LocalizedMargin;
}

@ObservedV2
export class EditableTitleBarStyleV2 {
  @Trace public backgroundColor?: ResourceColor;
  @Trace public backgroundBlurStyle?: BlurStyle;
  @Trace public safeAreaTypes?: Array<SafeAreaType>;
  @Trace public safeAreaEdges?: Array<SafeAreaEdge>;
  @Trace public contentMargin?: LocalizedMargin;

  constructor(options?: EditableTitleBarStyleV2Options) {
    if (options?.backgroundColor !== undefined) {
      this.backgroundColor = options!.backgroundColor;
    }
    if (options?.backgroundBlurStyle !== undefined) {
      this.backgroundBlurStyle = options!.backgroundBlurStyle;
    }
    if (options?.safeAreaTypes !== undefined) {
      this.safeAreaTypes = options!.safeAreaTypes;
    }
    if (options?.safeAreaEdges !== undefined) {
      this.safeAreaEdges = options!.safeAreaEdges;
    }
    if (options?.contentMargin !== undefined) {
      this.contentMargin = options!.contentMargin;
    }
  }
}

export enum ItemTypeV2 {
  Image,
  Icon,
  LeftIcon,
}

const PUBLIC_CANCEL_V2 = $r('sys.symbol.xmark');
const PUBLIC_OK_V2 = $r('sys.symbol.checkmark');
const PUBLIC_BACK_V2 = $r('sys.symbol.chevron_backward');
const PUBLIC_IMAGE_BACK_V2 = $r('sys.media.ohos_ic_compnent_titlebar_back');

const DEFAULT_TITLE_BAR_HEIGHT_V2: number = 56;
const DEFAULT_TITLE_PADDING_V2: number = 2;
const MAX_LINE_ONE_V2: int = 1;
const MAX_LINES_TWO_V2: int = 2;
const MAX_MAIN_TITLE_PERCENT_V2: number = 0.65;
const MAX_SUB_TITLE_PERCENT_V2: number = 0.35;
const MIN_SUBTITLE_SIZE_V2 = '10.0vp';
const TEXT_EDITABLE_DIALOG_V2 = '18.3fp';
const IMAGE_SIZE_V2 = '64vp';
const MAX_DIALOG_V2 = '256vp';
const MIN_DIALOG_V2 = '216vp';
const SYMBOL_SIZE_V2 = '24vp';
const SYMBOL_TITLE_SIZE_V2 = '64vp';
const TITLE_VP_V2: number = 20;
const SUBTITLE_VP_V2: number = 14;

const TITLE_F_V2: number = getNumberByResourceV2(125831095, TITLE_VP_V2);
const SUBTITLE_F_V2: number = getNumberByResourceV2(125831097, SUBTITLE_VP_V2);

const TITLE_F_VP_V2: string = (TITLE_F_V2 > 0 ? TITLE_F_V2 : TITLE_VP_V2) + 'vp';
const SUBTITLE_F_VP_V2: string = (SUBTITLE_F_V2 > 0 ? SUBTITLE_F_V2 : SUBTITLE_VP_V2) + 'vp';

@ObservedV2
export class EditableTitleBarThemeV2 {
  @Trace public iconColor: ResourceColor = $r('sys.color.titlebar_icon_color');
  @Trace public iconBackgroundColor: ResourceColor = $r('sys.color.titlebar_icon_background_color');
  @Trace public iconBackgroundPressedColor: ResourceColor = $r('sys.color.titlebar_icon_background_pressed_color');
  @Trace public iconBackgroundHoverColor: ResourceColor = $r('sys.color.titlebar_icon_background_hover_color');
  @Trace public iconBackgroundFocusOutlineColor: ResourceColor =
    $r('sys.color.titlebar_icon_background_focus_outline_color');
  @Trace public titleColor: ResourceColor = $r('sys.color.titlebar_title_tertiary_color');
  @Trace public subTitleColor: ResourceColor = $r('sys.color.titlebar_subheader_color');
}

export class ButtonGestureModifierV2 implements GestureModifier {
  public static readonly longPressTime: number = 500;
  public static readonly minFontSize: number = 1.75;
  public fontSize: number = 1;
  private onDialogOpen: () => void;
  private onDialogClose: () => void;

  constructor(onDialogOpen: () => void, onDialogClose: () => void) {
    this.onDialogOpen = onDialogOpen;
    this.onDialogClose = onDialogClose;
  }

  applyGesture(event: UIGestureEvent): void {
    if (this.fontSize >= ButtonGestureModifierV2.minFontSize) {
      event.addGesture(
        new LongPressGestureHandler({ repeat: false, duration: Double.toInt(ButtonGestureModifierV2.longPressTime)})
          .onAction(() => {
            if (event) {
              this.onDialogOpen();
            }
          })
          .onActionEnd(() => {
            this.onDialogClose();
          })
      )
    } else {
      event.clearGestures();
    }
  }
}

export class EnvironmentCallbackEntryV2 implements EnvironmentCallback {
  private imageMenuItem: ImageMenuItemV2;
  private localFontSize: number = 1;
  private localIsFollowing: boolean = false;
  private localMaxScale: number = 1;

  constructor(imageMenuItem: ImageMenuItemV2) {
    this.imageMenuItem = imageMenuItem;
    this.localFontSize = imageMenuItem.fontSizeV2;
    this.localIsFollowing = imageMenuItem.isFollowingSystemFontScaleV2;
    this.localMaxScale = imageMenuItem.maxFontScaleV2;
  }

  onConfigurationUpdated(config: Configuration): void {
    if (config === undefined || !this.localIsFollowing) {
      this.localFontSize = 1;
      this.imageMenuItem.onFontSizeUpdate(this.localFontSize);
      return;
    }
    try {
      this.localFontSize = Math.min(this.localMaxScale, config.fontSizeScale ?? 1);
      this.imageMenuItem.onFontSizeUpdate(this.localFontSize);
    } catch (paramError) {
      let code = (paramError as ClassCastError)?.code;
      let message = (paramError as ClassCastError)?.message;
      hilog.error(0x3900, 'EditableTitleBarV2',
        `EditableTitleBarV2 environmentCallback error: ${code}, ${message}`);
    }
  }

  onMemoryLevel(level: AbilityConstant.MemoryLevel): void {
  }
}

@ComponentV2
export struct EditableTitleBarV2 {
  @Param leftIcon?: EditableLeftIconV2 = undefined;
  @Param @Require title: ResourceStr | EditableTitleV2;
  @Param imageItem?: EditableTitleBarItemV2 = undefined;
  @Param menuItems?: Array<EditableTitleBarMenuItemV2> = undefined;
  @Param saveButton?: EditableSaveButtonV2 = undefined;
  @Param options?: EditableTitleBarStyleV2 = undefined;

  public static readonly maxCountOfExtraItemsV2: number = 3;
  public static readonly maxOtherCountOfExtraItemsV2: number = 2;
  public static readonly commonZeroV2: number = 0;
  public static readonly noneColorV2: string = '#00000000';
  public static readonly defaultHeightV2: number = getNumberByResourceV2(125831115, DEFAULT_TITLE_BAR_HEIGHT_V2);
  public static readonly defaultTitlePaddingV2: number = getNumberByResourceV2(125830920, DEFAULT_TITLE_PADDING_V2);
  public static readonly totalHeightV2: number =
    EditableTitleBarV2.defaultHeightV2 === EditableTitleBarV2.commonZeroV2 ? DEFAULT_TITLE_BAR_HEIGHT_V2 :
      EditableTitleBarV2.defaultHeightV2;
  static readonly titlePaddingV2: number =
    EditableTitleBarV2.defaultTitlePaddingV2 === EditableTitleBarV2.commonZeroV2 ?
      DEFAULT_TITLE_PADDING_V2 : EditableTitleBarV2.defaultTitlePaddingV2;
  private static readonly maxMainTitleHeightV2: number =
    (EditableTitleBarV2.totalHeightV2 - EditableTitleBarV2.titlePaddingV2) * MAX_MAIN_TITLE_PERCENT_V2;
  private static readonly maxSubTitleHeightV2: number =
    (EditableTitleBarV2.totalHeightV2 - EditableTitleBarV2.titlePaddingV2) * MAX_SUB_TITLE_PERCENT_V2;

  @Local private isFollowingSystemFontScaleV2: boolean = false;
  @Local private maxFontScaleV2: number = 1;
  @Local private fontSizeV2: number = 1;

  @Local editableTitleBarThemeV2: EditableTitleBarThemeV2 = new EditableTitleBarThemeV2();

  private getLeftIconType(): EditableLeftIconTypeV2 {
    return this.leftIcon?.iconType ?? EditableLeftIconTypeV2.Back;
  }

  private getLeftIconDefaultFocus(): boolean {
    return this.leftIcon?.defaultFocus ?? false;
  }

  private getLeftIconAction(): OnActionCallback | undefined {
    return this.leftIcon?.onAction;
  }

  private getTitleText(): ResourceStr {
    if (typeof this.title === 'string' || this.title instanceof Resource) {
      return this.title as ResourceStr;
    }
    return (this.title as EditableTitleV2).mainTitle ?? '';
  }

  private getSubtitleText(): ResourceStr {
    if (typeof this.title === 'string' || this.title instanceof Resource) {
      return '';
    }
    return (this.title as EditableTitleV2).subTitle ?? '';
  }

  private getSaveButtonRequired(): boolean {
    return this.saveButton?.isRequired ?? true;
  }

  private getSaveButtonDefaultFocus(): boolean {
    return this.saveButton?.defaultFocus ?? false;
  }

  private getSaveButtonAction(): OnActionCallback | undefined {
    return this.saveButton?.onAction;
  }

  private getBackgroundColor(): ResourceColor {
    return this.options?.backgroundColor ?? EditableTitleBarV2.noneColorV2;
  }

  private getBackgroundBlurStyle(): BlurStyle {
    return this.options?.backgroundBlurStyle ?? BlurStyle.NONE;
  }

  private getSafeAreaTypes(): Array<SafeAreaType> {
    return this.options?.safeAreaTypes ?? [SafeAreaType.SYSTEM];
  }

  private getSafeAreaEdges(): Array<SafeAreaEdge> {
    return this.options?.safeAreaEdges ?? [SafeAreaEdge.TOP];
  }

  private getContentMargin(): LocalizedMargin {
    if (this.options?.contentMargin) {
      return this.options?.contentMargin as LocalizedMargin;
    }
    return {
      start: LengthMetrics.resource($r('sys.float.margin_left')),
      end: LengthMetrics.resource($r('sys.float.margin_right')),
    } as LocalizedMargin;
  }

  onWillApplyTheme(theme: Theme): void {
    this.editableTitleBarThemeV2.iconColor = theme.colors.iconPrimary;
    this.editableTitleBarThemeV2.titleColor = theme.colors.fontPrimary;
    this.editableTitleBarThemeV2.subTitleColor = theme.colors.fontSecondary;
    this.editableTitleBarThemeV2.iconBackgroundPressedColor = theme.colors.interactivePressed;
    this.editableTitleBarThemeV2.iconBackgroundHoverColor = theme.colors.interactiveHover;
    this.editableTitleBarThemeV2.iconBackgroundFocusOutlineColor = theme.colors.interactiveFocus;
  }

  aboutToAppear(): void {
    try {
      let uiContent: UIContext = this.getUIContext();
      if (uiContent.getHostContext() !== undefined) {
        this.isFollowingSystemFontScaleV2 = uiContent.isFollowingSystemFontScale();
        this.maxFontScaleV2 = uiContent.getMaxFontScale();
      }
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | String = (exception as ClassCastError)?.message;
      hilog.error(0x3900, 'EditableTitleBarV2', `Failed to init fontsizescale info,cause, code: ${code}, message: ${message}`);
    }
  }

  decideFontScaleV2(): number {
    let uiContent: UIContext = this.getUIContext();
    if (uiContent.getHostContext() !== undefined) {
      let config = (uiContent.getHostContext() as common.UIAbilityContext)?.config;
      let systemFontScale = config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScaleV2) {
        return 1;
      }
      return Math.min(systemFontScale, this.maxFontScaleV2);
    }
    if (!this.isFollowingSystemFontScaleV2) {
      return 1;
    }
    return this.maxFontScaleV2;
  }

  build(): void {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch,
    }) {
      Row() {
        Row() {
          this.leftIconLayoutV2();
        }
        .flexShrink(0)

        Row() {
          if (this.imageItem) {
            Row() {
              this.imageItemLayoutV2();
            }
            .flexShrink(0)
          }

          Row() {
            this.titleLayoutV2();
          }
          .width('100%')
          .flexShrink(1)
        }
        .width('100%')
        .flexShrink(1)
        .accessibilityGroup(true)
        .accessibilityDescription($r('sys.string.subheader_accessibility_title'))

        Row() {
          this.rightMenuItemsLayoutV2();
        }
        .flexShrink(0)
      }
      .width('100%')
      .margin(this.getContentMargin())
      .height(EditableTitleBarV2.totalHeightV2)
    }
    .backgroundColor(this.getBackgroundColor())
    .backgroundBlurStyle(
      this.getBackgroundBlurStyle(), undefined, { disableSystemAdaptation: true })
    .expandSafeArea(
      this.getSafeAreaTypes(),
      this.getSafeAreaEdges(),
    )
  }

  @Builder
  imageItemLayoutV2(): void {
    ImageMenuItemV2({
      itemV2: this.imageItem as EditableTitleBarMenuItemV2,
      attributeV2: ItemTypeV2.Image,
      fontSizeV2: this.fontSizeV2,
      imageMenuItemIdV2: `ImageMenuItem_${this.getUniqueId()}`,
    })
  }

  @Builder
  leftIconLayoutV2(): void {
    if (this.getLeftIconType() === EditableLeftIconTypeV2.Back) {
      ImageMenuItemV2({
        itemV2: {
          value: PUBLIC_BACK_V2,
          isEnabled: true,
          action: () => {
            if (this.getLeftIconAction()) {
              this.getLeftIconAction()?.()
            } else {
              this.getUIContext()?.getRouter()?.back()
            }
          },
          defaultFocus: this.getLeftIconDefaultFocus()
        } as EditableTitleBarMenuItemV2,
        fontSizeV2: this.fontSizeV2,
        attributeV2: ItemTypeV2.LeftIcon,
        imageMenuItemIdV2: `BackMenuItem_${this.getUniqueId()}`,
      })
    } else {
      ImageMenuItemV2({
        itemV2: {
          value: PUBLIC_CANCEL_V2,
          isEnabled: true,
          action: () => {
            if (this.getLeftIconAction()) {
              this.getLeftIconAction()?.()
            }
          },
          defaultFocus: this.getLeftIconDefaultFocus()
        } as EditableTitleBarMenuItemV2,
        fontSizeV2: this.fontSizeV2,
        attributeV2: ItemTypeV2.LeftIcon,
        imageMenuItemIdV2: `CancelMenuItem_${this.getUniqueId()}`,
      })
    }
  }

  @Builder
  titleLayoutV2(): void {
    Column() {
      Row() {
        Text(this.getTitleText())
          .maxFontSize(TITLE_F_VP_V2)
          .minFontSize(SUBTITLE_F_VP_V2)
          .fontColor(this.editableTitleBarThemeV2.titleColor)
          .maxLines(this.getSubtitleText() ? MAX_LINE_ONE_V2 : MAX_LINES_TWO_V2)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Start)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .heightAdaptivePolicy(this.getSubtitleText() ?
            TextHeightAdaptivePolicy.MAX_LINES_FIRST : TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
          .constraintSize({
            maxHeight: this.getSubtitleText() ?
              EditableTitleBarV2.maxMainTitleHeightV2 : EditableTitleBarV2.totalHeightV2,
          })
      }
      .justifyContent(FlexAlign.Start)

      if (this.getSubtitleText()) {
        Row() {
          Text(this.getSubtitleText())
            .maxFontSize(SUBTITLE_F_VP_V2)
            .minFontSize(MIN_SUBTITLE_SIZE_V2)
            .fontColor(this.editableTitleBarThemeV2.subTitleColor)
            .maxLines(MAX_LINE_ONE_V2)
            .fontWeight(FontWeight.Regular)
            .textAlign(TextAlign.Start)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
            .constraintSize({
              maxHeight: this.getTitleText() ?
                EditableTitleBarV2.maxSubTitleHeightV2 : EditableTitleBarV2.totalHeightV2,
            })
        }
        .margin({
          top: $r('sys.float.padding_level1'),
        } as Margin)
        .justifyContent(FlexAlign.Start)
      }
    }
    .height(EditableTitleBarV2.totalHeightV2)
    .justifyContent(FlexAlign.Center)
    .margin({
      start: LengthMetrics.resource($r('sys.float.titlebar_icon_background_space_horizontal')),
    } as LocalizedMargin)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  rightMenuItemsLayoutV2(): void {
    EditableTitleBarMenuSectionV2({
      menuItemsV2: this.menuItems,
      onSaveV2: this.getSaveButtonAction(),
      isSaveEnabledV2: this.getSaveButtonRequired(),
      fontSizeV2: this.fontSizeV2,
      parentUniqueIdV2: this.getUniqueId(),
      saveIconDefaultFocusV2: this.getSaveButtonDefaultFocus(),
    })
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void {
    children.forEach((child) => {
      child.layout({ x: 0, y: 0 });
    })
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    let result: SizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    this.fontSizeV2 = this.decideFontScaleV2();
    children.forEach((child) => {
      let childMeasureResult = child.measure(constraint);
      if (childMeasureResult) {
        result.height = childMeasureResult.height;
      }
      result.width = constraint.maxWidth as number;
    })
    return result;
  }
}

@ComponentV2
struct EditableTitleBarMenuSectionV2 {
  @Param menuItemsV2: Array<EditableTitleBarMenuItemV2> | undefined = undefined;
  @Param onSaveV2?: OnActionCallback = undefined;
  @Param isSaveEnabledV2: boolean = true;
  @Param saveIconDefaultFocusV2: boolean = false;
  @Param fontSizeV2: number = 1;
  @Param parentUniqueIdV2: number = 0;
  @Param editableTitleBarThemeV2: EditableTitleBarThemeV2 = new EditableTitleBarThemeV2();

  build() {
    Column() {
      Row() {
        if (this.menuItemsV2) {
          ForEach((this.menuItemsV2 as EditableTitleBarMenuItemV2[]).slice(EditableTitleBarV2.commonZeroV2.toInt(),
            this.isSaveEnabledV2 ?
              EditableTitleBarV2.maxOtherCountOfExtraItemsV2.toInt() :
              EditableTitleBarV2.maxCountOfExtraItemsV2.toInt()),
            (item: EditableTitleBarMenuItemV2, index: int) => {
              ImageMenuItemV2({
                itemV2: item,
                attributeV2: ItemTypeV2.Icon,
                imageMenuItemIdV2: `ImageMenuItem_${this.parentUniqueIdV2}_${index}`,
                fontSizeV2: this.fontSizeV2,
                editableTitleBarThemeV2: this.editableTitleBarThemeV2,
              })
            }, (item: EditableTitleBarMenuItemV2, index: int) => {
              return JSON.stringify(item.value + '_' + index)
            })
        }
        if (this.isSaveEnabledV2) {
          ImageMenuItemV2({
            itemV2: {
              value: PUBLIC_OK_V2,
              isEnabled: true,
              action: () => {
                if (this.onSaveV2) {
                  this.onSaveV2?.()
                }
              },
              defaultFocus: this.saveIconDefaultFocusV2
            } as EditableTitleBarMenuItemV2,
            fontSizeV2: this.fontSizeV2,
            attributeV2: ItemTypeV2.Icon,
            imageMenuItemIdV2: `SaveMenuItem_${this.parentUniqueIdV2}`,
            editableTitleBarThemeV2: this.editableTitleBarThemeV2,
          })
        }
      }
    }
    .justifyContent(FlexAlign.Center)
  }
}

@ComponentV2
export struct ImageMenuItemV2 {
  @Param itemV2: EditableTitleBarMenuItemV2 = {
    value: '',
    isEnabled: true,
    label: '',
    accessibilityLevel: 'auto',
    accessibilityText: '',
    accessibilityDescription: '',
  } as EditableTitleBarMenuItemV2;
  @Param attributeV2: ItemTypeV2 = ItemTypeV2.Image;
  @Param imageMenuItemIdV2?: string = undefined;
  @Param fontSizeV2: number = 1;
  @Param editableTitleBarThemeV2: EditableTitleBarThemeV2 = new EditableTitleBarThemeV2();

  @Local private isOnFocusV2: boolean = false;
  @Local private isOnHoverV2: boolean = false;
  @Local private isOnClickV2: boolean = false;
  @Local private isInFocusedStyleV2: boolean = false;
  @Local fontSizeInternalV2: number = 1;

  private buttonGestureModifierLocal: ButtonGestureModifierV2 = new ButtonGestureModifierV2(
    (): void => this.onOpenDialogV2(),
    (): void => this.onCloseDialogV2()
  );

  aboutToAppear(): void {
    this.buttonGestureModifierLocal.fontSize = this.fontSizeInternalV2;
  }

  onFontSizeUpdate(newSize: number): void {
    this.fontSizeInternalV2 = newSize;
  }

  get isFollowingSystemFontScaleV2(): boolean {
    return false;
  }

  get maxFontScaleV2(): number {
    return 1;
  }

  private onOpenDialogV2(): void {
  }

  private onCloseDialogV2(): void {
  }

  private textDialogV2(): ResourceStr {
    if (this.itemV2.value === PUBLIC_OK_V2) {
      return $r('sys.string.icon_save');
    } else if (this.itemV2.value === PUBLIC_CANCEL_V2) {
      return $r('sys.string.icon_cancel');
    } else if (this.itemV2.value === PUBLIC_BACK_V2) {
      return $r('sys.string.icon_back');
    } else {
      return this.itemV2.label ? this.itemV2.label as ResourceStr : '' as ResourceStr;
    }
  }

  getBgColorV2(): ResourceColor {
    if (this.isOnClickV2) {
      return this.editableTitleBarThemeV2.iconBackgroundPressedColor;
    } else if (this.isOnHoverV2) {
      return this.editableTitleBarThemeV2.iconBackgroundHoverColor;
    } else {
      return this.editableTitleBarThemeV2.iconBackgroundColor;
    }
  }

  getFgColorV2(): ResourceStr {
    if (this.isOnClickV2) {
      return $r('sys.color.titlebar_icon_background_pressed_color');
    } else if (this.isOnHoverV2) {
      return $r('sys.color.titlebar_icon_background_hover_color');
    } else {
      return EditableTitleBarV2.noneColorV2;
    }
  }

  getStringByNameSyncV2(contextName: string): undefined | String {
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
      hilog.error(0x3900, 'EditableTitleBarV2', `Failed to getStringByNameSyncV2,cause, code: ${code}, message: ${message}`);
    }
    return uiContext;
  }

  private toStringFormatV2(resource: ResourceStr | undefined | Long): string | undefined {
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
        hilog.error(0x3900, 'EditableTitleBarV2', `Failed to EditableTitleBarV2 toStringFormatV2, code: ${code}, message: ${message}`)
      }
      return resourceString;
    }
    return undefined;
  }

  private getAccessibilityReadTextV2(): string | undefined {
    if (this.itemV2.value === PUBLIC_OK_V2) {
      return this.getStringByNameSyncV2('icon_save');
    } else if (this.itemV2.value === PUBLIC_CANCEL_V2) {
      return this.getStringByNameSyncV2('icon_cancel');
    } else if (this.itemV2.value === PUBLIC_BACK_V2) {
      return this.getStringByNameSyncV2('icon_back');
    } else if (this.itemV2.accessibilityText) {
      return this.toStringFormatV2(this.itemV2.accessibilityText) as string;
    } else if (this.itemV2.label) {
      return this.itemV2.label as string;
    }
    return ' ';
  }

  private getRightIconAccessibilityLevelV2(): string {
    if (this.itemV2.accessibilityLevel && this.itemV2.accessibilityLevel !== '') {
      return this.itemV2.accessibilityLevel as string;
    }
    return 'auto';
  }

  private getAccessibilityDescriptionV2(): string | undefined {
    if (UtilV2.isResourceType(this.itemV2.accessibilityDescription)) {
      return (this.getUIContext().getHostContext() as common.Context).resourceManager
        .getStringSync((this.itemV2.accessibilityDescription as Resource).id);
    } else if (this.itemV2.accessibilityDescription && this.itemV2.accessibilityDescription !== '') {
      return this.itemV2.accessibilityDescription as string;
    }
    return '';
  }

  @Builder
  IconBuilderV2(): void {
    Button({ type: ButtonType.Normal, stateEffect: this.itemV2.isEnabled } as ButtonOptions) {
      if (this.itemV2.symbolStyle !== undefined) {
        SymbolGlyph()
          .fontColor([this.editableTitleBarThemeV2.iconColor])
          .attributeModifier(this.itemV2.symbolStyle)
          .focusable(this.itemV2.isEnabled)
          .enabled(this.itemV2.isEnabled)
          .draggable(false)
          .accessibilityText(this.getAccessibilityReadTextV2())
          .effectStrategy(SymbolEffectStrategy.NONE)
          .symbolEffect(new SymbolEffect(), false)
          .fontSize(SYMBOL_SIZE_V2)
          .defaultFocus(this.itemV2.isEnabled ? this.itemV2.defaultFocus : false)
      } else {
        if (UtilV2.isSymbolResource(this.itemV2.value)) {
          SymbolGlyph(this.itemV2.value as Resource)
            .fontSize(SYMBOL_SIZE_V2)
            .fontColor([this.editableTitleBarThemeV2.iconColor])
            .focusable(this.itemV2.isEnabled)
            .enabled(this.itemV2.isEnabled)
            .draggable(false)
            .accessibilityText(this.getAccessibilityReadTextV2())
            .defaultFocus(this.itemV2.isEnabled ? this.itemV2.defaultFocus : false)
        } else {
          Image(this.itemV2.value)
            .fillColor(this.editableTitleBarThemeV2.iconColor)
            .matchTextDirection(this.itemV2.value === PUBLIC_IMAGE_BACK_V2 ? true : false)
            .width($r('sys.float.titlebar_icon_width'))
            .height($r('sys.float.titlebar_icon_height'))
            .focusable(this.itemV2.isEnabled)
            .enabled(this.itemV2.isEnabled)
            .draggable(false)
            .accessibilityText(this.getAccessibilityReadTextV2() as string)
            .defaultFocus(this.itemV2.isEnabled ? this.itemV2.defaultFocus : false)
        }
      }
    }
    .id(this.imageMenuItemIdV2)
    .width($r('sys.float.titlebar_icon_background_width'))
    .height($r('sys.float.titlebar_icon_background_height'))
    .focusable(this.itemV2.isEnabled)
    .enabled(this.itemV2.isEnabled)
    .borderRadius($r('sys.float.titlebar_icon_background_shape'))
    .margin({
      start: this.attributeV2 === ItemTypeV2.LeftIcon ? LengthMetrics.vp(EditableTitleBarV2.commonZeroV2) :
        LengthMetrics.resource($r('sys.float.titlebar_icon_background_space_horizontal')),
    } as LocalizedMargin)
    .focusOnTouch(true)
    .foregroundColor(this.getFgColorV2())
    .backgroundColor(this.getBgColorV2())
    .border({
      radius: $r('sys.float.titlebar_icon_background_shape'),
      width: this.isInFocusedStyleV2 ?
        $r('sys.float.titlebar_icon_background_focus_outline_weight') : EditableTitleBarV2.commonZeroV2,
      color: this.isInFocusedStyleV2 ?
        this.editableTitleBarThemeV2.iconBackgroundFocusOutlineColor : Color.Transparent,
      style: BorderStyle.Solid,
    })
    .onFocus(() => {
      if (!this.itemV2.isEnabled) {
        return;
      }
      this.isOnFocusV2 = true;
      this.isInFocusedStyleV2 = true;
    })
    .onBlur(() => {
      this.isOnFocusV2 = false;
      this.isInFocusedStyleV2 = false;
    })
    .onHover((isOn: boolean, event?: HoverEvent) => {
      if (!this.itemV2.isEnabled) {
        return;
      }
      this.isOnHoverV2 = isOn;
    })
    .onKeyEvent((event: KeyEvent): boolean => {
      if (!this.itemV2.isEnabled) {
        return false;
      }
      if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
        return false;
      }
      if (event.type === KeyType.Down) {
        this.isOnClickV2 = true;
      }
      if (event.type === KeyType.Up) {
        this.isOnClickV2 = false;
      }
      return true;
    })
    .onTouch((event: TouchEvent) => {
      if (!this.itemV2.isEnabled) {
        return;
      }
      if (event.type === TouchType.Down) {
        this.isOnClickV2 = true;
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        this.isOnClickV2 = false;
      }
    })
    .onClick((event?: ClickEvent) => {
      if ((this.itemV2.isEnabled as boolean | undefined) === undefined) {
        this.itemV2.isEnabled = true;
      }
      this.itemV2.isEnabled && this.itemV2.action?.()
    })
    .gestureModifier(this.buttonGestureModifierLocal)
    .accessibilityLevel(this.getRightIconAccessibilityLevelV2())
    .accessibilityDescription(this.getAccessibilityDescriptionV2() as string)
  }

  @Builder
  ImageBuilderV2(): void {
    Stack({ alignContent: Alignment.Center }) {
      Image(this.itemV2.value)
        .width($r('sys.float.titlebar_icon_background_width'))
        .height($r('sys.float.titlebar_icon_background_height'))
        .borderRadius($r('sys.float.corner_radius_level10'))
        .focusable(false)
        .enabled(this.itemV2.isEnabled)
        .objectFit(ImageFit.Cover)
      Button('', { type: ButtonType.Circle } as ButtonOptions)
        .width($r('sys.float.titlebar_icon_background_width'))
        .height($r('sys.float.titlebar_icon_background_height'))
        .focusable(this.itemV2.isEnabled)
        .enabled(this.itemV2.isEnabled)
        .foregroundColor(this.getFgColorV2())
        .backgroundColor(EditableTitleBarV2.noneColorV2)
        .border({
          radius: $r('sys.float.titlebar_icon_background_shape'),
          width: this.isInFocusedStyleV2 ?
            $r('sys.float.titlebar_icon_background_focus_outline_weight') : EditableTitleBarV2.commonZeroV2,
          color: this.isInFocusedStyleV2 ?
            this.editableTitleBarThemeV2.iconBackgroundFocusOutlineColor : Color.Transparent,
          style: BorderStyle.Solid,
        })
        .onFocus(() => {
          if (!this.itemV2.isEnabled) {
            return;
          }
          this.isOnFocusV2 = true;
          this.isInFocusedStyleV2 = true;
        })
        .onBlur(() => {
          this.isOnFocusV2 = false;
          this.isInFocusedStyleV2 = false;
        })
        .onHover((isOn: boolean, event?: HoverEvent) => {
          if (!this.itemV2.isEnabled) {
            return;
          }
          this.isOnHoverV2 = isOn;
        })
        .onKeyEvent((event: KeyEvent): boolean => {
          if (!this.itemV2.isEnabled) {
            return false;
          }
          if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
            return false;
          }
          if (event.type === KeyType.Down) {
            this.isOnClickV2 = true;
          }
          if (event.type === KeyType.Up) {
            this.isOnClickV2 = false;
          }
          return true;
        })
        .onTouch((event: TouchEvent) => {
          if (!this.itemV2.isEnabled) {
            return;
          }
          if (event.type === TouchType.Down) {
            this.isOnClickV2 = true;
          }
          if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
            this.isOnClickV2 = false;
          }
        })
        .onClick((event?: ClickEvent) => {
          if ((this.itemV2.isEnabled as boolean | undefined) === undefined) {
            this.itemV2.isEnabled = true;
          }
          this.itemV2.isEnabled && this.itemV2.action?.()
        })
        .gestureModifier(this.buttonGestureModifierLocal)
        .defaultFocus(this.itemV2.isEnabled ? this.itemV2.defaultFocus : false)
    }
    .margin({
      start: LengthMetrics.resource($r('sys.float.titlebar_icon_background_space_horizontal')),
    } as LocalizedMargin)
  }

  build(): void {
    if (this.attributeV2 === ItemTypeV2.Icon || this.attributeV2 === ItemTypeV2.LeftIcon) {
      this.IconBuilderV2();
    } else {
      this.ImageBuilderV2();
    }
  }
}

function getNumberByResourceV2(resourceId: number, defaultNumber: number): number {
  return defaultNumber
}

class UtilV2 {
  private static RESOURCE_TYPE_SYMBOL: number = 40000;

  public static isSymbolResource(resourceStr: ResourceStr | undefined): boolean {
    if (!UtilV2.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
    return resource.type === UtilV2.RESOURCE_TYPE_SYMBOL;
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