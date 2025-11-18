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
  Resource, ResourceStr, GestureModifier, UIGestureEvent, LongPressGestureHandler, ResourceColor, AttributeModifier,
  ColumnAttribute, Builder, Button, ButtonType, Column, SymbolGlyph, Text, FontWeight, TextOverflow, TextAlign,
  FlexAlign, Placement, Color, SymbolEffect, Image, ImageFit, PX, FP, LPX, VP, GeometryInfo, Measurable, SizeResult,
  ConstraintSizeOptions, MeasureResult, Divider, Row, ForEach, BlurStyle, ColorMetrics, ShadowStyle, $r,
  LocalizedPadding, Margin, Padding, SymbolGlyphModifier, ButtonOptions, ClickEvent, CommonMethod, MenuElement,
  ComponentV2, CustomLayout, MenuOptions, Position, Layoutable, ClassCastError
} from '@ohos.arkui.component'
import { ObservedV2, Trace, Computed, Require, Param, Local, Monitor, IMonitor } from '@ohos.arkui.stateManagement';
import { Theme } from '@ohos.arkui.theme';
import { LengthMetrics, LengthUnit, ColorMetrics } from '@ohos.arkui.node';
import { DividerModifier } from '@ohos.arkui.modifier';
import hilog from '@ohos.hilog';
import window from '@ohos.window';
import common from '@ohos.app.ability.common';
import promptAction from '@ohos.promptAction';

export enum ToolBarV2ItemState {
  ENABLE = 1,
  DISABLE = 2,
  ACTIVATE = 3,
}

// “更多”栏图标
const PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
const IMAGE_SIZE: VP = '24vp';
const DEFAULT_TOOLBAR_HEIGHT: number = 56;
const TOOLBAR_MAX_LENGTH: number = 5;
const MAX_FONT_SIZE: number = 3.2;
const DIALOG_IMAGE_SIZE: VP = '64vp';
const MAX_DIALOG: VP = '256vp';
const MIN_DIALOG: VP = '216vp';
const TEXT_TOOLBAR_DIALOG: FP = '18.3fp';
const SCREEN_WIDTH_BREAK_POINT: number = 640;
const VERTICAL_SCREEN_TEXT_MAX_LINES: int = 6;
const HORIZONTAL_SCREEN_TEXT_MAX_LINES: int = 1;
const FOCUS_BOX_MARGIN: number = -2;
const FOCUS_BOX_BORDER_WIDTH: number = 2;
const RESOURCE_TYPE_SYMBOL: number = 40000;

class Util {
  public static isSymbolResource(resourceStr: ResourceStr | undefined | null): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource: Resource = resourceStr as Resource;
    return resource.type === RESOURCE_TYPE_SYMBOL;
  }

  public static isResourceType(resource: ResourceStr | Resource | undefined | null): boolean {
    if (!resource) {
      return false;
    }
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return false;
    }
    return true;
  }
}

@ObservedV2
export class ToolBarV2SymbolGlyph {
  @Trace
  public normal: SymbolGlyphModifier;
  @Trace
  public activated?: SymbolGlyphModifier;

  constructor(options: ToolBarV2SymbolGlyphOptions) {
    this.normal = options.normal;
    this.activated = options.activated;
  }
}

export interface ToolBarV2SymbolGlyphOptions {
  normal: SymbolGlyphModifier;
  activated?: SymbolGlyphModifier;
}

class ButtonGestureModifier implements GestureModifier {
  public static readonly longPressTime: number = 500;
  public static readonly minFontSize: number = 1.75;
  public gestureCallBack?: (event: UIGestureEvent) => void = undefined;

  applyGesture(event: UIGestureEvent): void {
    this.gestureCallBack?.(event);
  }
}

@ObservedV2
export class ToolBarV2ItemText {
  @Trace
  public text: ResourceStr;
  @Trace
  public color?: ColorMetrics = ColorMetrics.resourceColor($r('sys.color.font_primary'));
  @Trace
  public activatedColor?: ColorMetrics = ColorMetrics.resourceColor($r('sys.color.font_emphasize'));

  constructor(options: ToolBarV2ItemTextOptions) {
    this.text = options.text;
    this.color = options.color;
    this.activatedColor = options.activatedColor;
  }
}

export interface ToolBarV2ItemTextOptions {
  text: ResourceStr;
  color?: ColorMetrics;
  activatedColor?: ColorMetrics;
}

@ObservedV2
export class ToolBarV2ItemImage {
  @Trace
  public src: ResourceStr;
  @Trace
  public color?: ColorMetrics = undefined;
  @Trace
  public activatedColor?: ColorMetrics = undefined;

  constructor(options: ToolBarV2ItemImageOptions) {
    this.src = options.src;
    this.color = options.color;
    this.activatedColor = options.activatedColor;
  }
}

export declare type ToolBarV2ItemIconType = ToolBarV2ItemImage | ToolBarV2SymbolGlyph;

export interface ToolBarV2ItemImageOptions {
  src: ResourceStr;
  color?: ColorMetrics;
  activatedColor?: ColorMetrics;
}

export type ToolBarV2ItemAction = (index: int) => void;

@ObservedV2
export class ToolBarV2Item {
  @Trace
  public content: ToolBarV2ItemText = new ToolBarV2ItemText({ text: '' });
  @Trace
  public action?: (index: int) => void = undefined;
  @Trace
  public icon?: ToolBarV2ItemIconType = undefined;
  @Trace
  public state?: ToolBarV2ItemState = 1 as ToolBarV2ItemState;
  @Trace
  public accessibilityText?: ResourceStr = '';
  @Trace
  public accessibilityDescription?: ResourceStr = '';
  @Trace
  public accessibilityLevel?: string = 'auto';
  // item background, not exported
  @Trace
  public backgroundColor: ResourceColor = Color.Transparent;

  constructor(options: ToolBarV2ItemOptions) {
    this.content = options.content;
    this.action = options.action;
    this.icon = options.icon;
    this.state = options.state;
    this.accessibilityText = options.accessibilityText;
    this.accessibilityDescription = options.accessibilityDescription;
    this.accessibilityLevel = options.accessibilityLevel;
  }

  @Computed
  get symbol(): ToolBarV2SymbolGlyph | undefined {
    if (this.icon instanceof ToolBarV2SymbolGlyph) {
      return this.icon as ToolBarV2SymbolGlyph;
    }
    return undefined;
  }

  @Computed
  get image(): ToolBarV2ItemImage | undefined {
    if (!(this.icon instanceof ToolBarV2SymbolGlyph)) {
      return this.icon as ToolBarV2ItemImage;
    }
    return undefined;
  }
}

export interface ToolBarV2ItemOptions {
  content: ToolBarV2ItemText;
  action?: (index: int) => void;
  icon?: ToolBarV2ItemIconType;
  state?: ToolBarV2ItemState;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

@ObservedV2
export class ToolBarV2Modifier implements AttributeModifier<ColumnAttribute> {
  @Trace
  public backgroundColorValue?: ResourceColor = $r('sys.color.ohos_id_color_toolbar_bg');
  @Trace
  public heightValue?: LengthMetrics = LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT);
  @Trace
  public stateEffectValue?: boolean = true;
  @Trace
  public paddingValue?: LengthMetrics = LengthMetrics.resource($r('sys.float.padding_level12'));

  applyNormalAttribute(instance: ColumnAttribute): void {
    instance.backgroundColor(this.backgroundColorValue);
  }

  public backgroundColor(backgroundColor: ColorMetrics): ToolBarV2Modifier {
    this.backgroundColorValue = backgroundColor.color;
    return this;
  }

  public height(height: LengthMetrics): ToolBarV2Modifier {
    this.heightValue = height;
    return this;
  }

  public stateEffect(stateEffect: boolean): ToolBarV2Modifier {
    this.stateEffectValue = stateEffect;
    return this;
  }

  public padding(padding: LengthMetrics): ToolBarV2Modifier {
    this.paddingValue = padding;
    return this;
  }
}

@ObservedV2
class ToolBarV2Theme {
  @Trace
  public iconPrimaryColor: ResourceColor = $r('sys.color.icon_primary');
  @Trace
  public iconActivePrimaryColor: ResourceColor = $r('sys.color.icon_emphasize');
  @Trace
  public fontPrimaryColor: ResourceColor = $r('sys.color.font_primary');
  @Trace
  public fontActivatedPrimaryColor: ResourceColor = $r('sys.color.font_emphasize');
}

@CustomLayout
@ComponentV2
export struct ToolBarV2 {
  @Require @Param
  toolBarList: ToolBarV2Item[] = [] as ToolBarV2Item[];
  @Param
  activatedIndex?: int = -1;
  @Param
  dividerModifier?: DividerModifier = new DividerModifier();
  @Param
  toolBarModifier?: ToolBarV2Modifier =
    new ToolBarV2Modifier()
      .padding(LengthMetrics.resource($r('sys.float.padding_level12')))
      .stateEffect(true)
      .height(LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT))
      .backgroundColor(ColorMetrics.resourceColor($r('sys.color.ohos_id_color_toolbar_bg')));
  @Local
  localActivatedIndex: int = -1;
  @Local
  fontSize: number = 1;
  @Local
  theme: ToolBarV2Theme = new ToolBarV2Theme();

  gestureItem: ToolBarV2Item =
    new ToolBarV2Item({
      content: new ToolBarV2ItemText({
        text: '',
      }),
      icon: new ToolBarV2ItemImage({
        src: ''
      })
    });
  gestureIndex: int = -1;

  @Monitor(['activatedIndex'])
  onActivateIndexChange(monitor: IMonitor) {
    this.localActivatedIndex = monitor.value<int>('activatedIndex')?.now ?? -1;
  }

  @Computed
  get getMenus(): MenuElement[] {
    let menuContent: MenuElement[] = [] as MenuElement[];
    this.toolBarList.forEach((value: ToolBarV2Item, index: number) => {
      if (index >= TOOLBAR_MAX_LENGTH - 1) {
        menuContent.push({
          value: this.toolBarList[Double.toInt(index)].content.text,
          action: () => {
            let callback: ToolBarV2ItemAction | undefined = this.toolBarList[Double.toInt(index)].action;
            if (callback) {
              callback(Double.toInt(index));
            }
          },
          enabled: this.toolBarList[Double.toInt(index)].state !== ToolBarV2ItemState.DISABLE,
        });
      }
    })
    return menuContent;
  }

  private itemCardTextMaxLine: int = 1;
  private itemDialogId?: int = undefined;
  private isFollowSystem?: boolean = false;
  private maxFontSizeScale?: number = 3.2;
  private moreItem: ToolBarV2Item = new ToolBarV2Item({
    content: new ToolBarV2ItemText({
      text: $r('sys.string.ohos_toolbar_more'),
    }),
    icon: new ToolBarV2ItemImage({
      src: PUBLIC_MORE
    })
  })
  private moreText: Resource = $r('sys.string.ohos_toolbar_more');

  aboutToAppear(): void {
    this.localActivatedIndex = this.activatedIndex ?? -1;
    try {
      this.isFollowSystem = this.getUIContext()?.isFollowingSystemFontScale();
      this.maxFontSizeScale = this.getUIContext()?.getMaxFontScale();
    } catch (err) {
      let code: undefined|int = (err as ClassCastError)?.code;
      let message: undefined|string = (err as ClassCastError)?.message;
      hilog.error(0x3900, 'Ace',
        `Faild to toolBarV2 getMaxFontScale, code: ${code}, message: ${message}`);
    }
  }

  onWillApplyTheme(theme: Theme): void {
    this.theme.iconPrimaryColor = theme.colors.iconPrimary;
    this.theme.iconActivePrimaryColor = theme.colors.iconEmphasize;
    this.theme.fontPrimaryColor = theme.colors.fontPrimary;
    this.theme.fontActivatedPrimaryColor = theme.colors.fontEmphasize;
  }

  @Builder
  MoreTabBuilder(index: number): void {
    Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
      Column() {
        SymbolGlyph(PUBLIC_MORE)
          .fontSize(IMAGE_SIZE)
          .fontColor([this.theme.iconPrimaryColor])
          .draggable(false)
          .margin({ bottom: $r('sys.float.padding_level1') } as Margin)
        Text(this.moreText)
          .fontColor(this.theme.fontPrimaryColor)
          .fontSize($r('sys.float.ohos_id_text_size_caption'))
          .fontWeight(FontWeight.Medium)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .textAlign(TextAlign.Center)
          .focusable(true)
          .focusOnTouch(true)
      }
      .width('100%')
      .height('100%')
      .justifyContent(FlexAlign.Center)
      .padding({
        start: LengthMetrics.resource($r('sys.float.padding_level2')),
        end: LengthMetrics.resource($r('sys.float.padding_level2')),
      } as LocalizedPadding)
      .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    }
    .accessibilityGroup(true)
    .focusable(true)
    .focusOnTouch(true)
    .focusBox({
      margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
      strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
      strokeColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_focused_outline'))
    })
    .width('100%')
    .height('100%')
    .bindMenu(this.getMenus, { placement: Placement.TopRight, offset: { x: -12, y: -10 } as Position } as MenuOptions)
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .backgroundColor(this.toolBarList[Double.toInt(index)].backgroundColor)
    .onHover((isHover: boolean): void => {
      if (isHover) {
        this.toolBarList[Double.toInt(index)].backgroundColor = $r('sys.color.ohos_id_color_hover');
      } else {
        this.toolBarList[Double.toInt(index)].backgroundColor = Color.Transparent;
      }
    })
    .stateStyles({
      pressed: (instance: CommonMethod) => {
        instance.backgroundColor((!this.toolBarModifier?.stateEffectValue) ?
          this.toolBarList[Double.toInt(index)].backgroundColor : $r('sys.color.ohos_id_color_click_effect'))
      }
    })
    .gestureModifier(this.getItemGestureModifier(this.moreItem, Double.toInt(index)))
  }

  @Builder
  TabBuilder(index: int): void {
    Button({ type: ButtonType.Normal, stateEffect: false } as ButtonOptions) {
      Column() {
        if (this.toolBarList[index]?.symbol) {
          SymbolGlyph()
            .fontSize(IMAGE_SIZE)
            .symbolEffect(new SymbolEffect(), false)
            .attributeModifier(this.getToolBarSymbolModifier(index))
            .margin({ bottom: $r('sys.float.padding_level1') } as Margin)
        } else if (Util.isSymbolResource(this.toolBarList[index]?.image?.src)) {
          SymbolGlyph(this.toolBarList[index]?.image?.src as Resource)
            .fontSize(IMAGE_SIZE)
            .fontColor([this.getIconColor(index)])
            .margin({ bottom: $r('sys.float.padding_level1') } as Margin)
        } else {
          Image(this.toolBarList[index]?.image?.src as ResourceStr)
            .width(IMAGE_SIZE)
            .height(IMAGE_SIZE)
            .fillColor(this.getIconColor(index))
            .margin({ bottom: $r('sys.float.padding_level1') } as Margin)
            .objectFit(ImageFit.Contain)
            .draggable(false)
        }
        Text(this.toolBarList[index]?.content.text)
          .fontColor(this.getTextColor(index))
          .fontSize($r('sys.float.ohos_id_text_size_caption'))
          .maxFontSize($r('sys.float.ohos_id_text_size_caption'))
          .minFontSize(9)
          .fontWeight(FontWeight.Medium)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .textAlign(TextAlign.Center)
          .focusable(!(this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE))
          .focusOnTouch(!(this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE))
      }
      .justifyContent(FlexAlign.Center)
      .width('100%')
      .height('100%')
      .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
      .padding({
        start: LengthMetrics.resource($r('sys.float.padding_level2')),
        end: LengthMetrics.resource($r('sys.float.padding_level2')),
      } as LocalizedPadding)
    }
    .accessibilityGroup(true)
    .accessibilityText(
      this.toAccessibilityText(this.toolBarList[index]?.accessibilityText, index))
    .accessibilityDescription(
      this.toStringFormat(this.toolBarList[index]?.accessibilityDescription))
    .accessibilityLevel(this.toolBarList[index]?.accessibilityLevel ?? 'auto')
    .enabled(this.toolBarList[index]?.state !== ToolBarV2ItemState.DISABLE)
    .width('100%')
    .height('100%')
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .focusable(!(this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE))
    .focusOnTouch(!(this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE))
    .focusBox({
      margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
      strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
      strokeColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_focused_outline'))
    })
    .backgroundColor(this.toolBarList[index].backgroundColor)
    .onHover((isHover: boolean): void => {
      if (isHover && this.toolBarList[index]?.state !== ToolBarV2ItemState.DISABLE) {
        this.toolBarList[index].backgroundColor = $r('sys.color.ohos_id_color_hover');
      } else {
        this.toolBarList[index].backgroundColor = Color.Transparent;
      }
    })
    .stateStyles({
      pressed: (instance: CommonMethod): void => {
        instance.backgroundColor((this.toolBarList[index]?.state === ToolBarV2ItemState.DISABLE) ||
          (!this.toolBarModifier?.stateEffectValue) ?
          this.toolBarList[index].backgroundColor : $r('sys.color.ohos_id_color_click_effect'))
      }
    })
    .onClick((event: ClickEvent) => {
      this.clickEventAction(index);
    })
    .gestureModifier(this.getItemGestureModifier(this.toolBarList[index], index))
  }

  @Builder
  itemCardDialogBuilder() {
    if (this.gestureItem.content && this.gestureItem.content.text) {
      Column() {
        if (this.gestureItem.symbol) {
          SymbolGlyph()
            .attributeModifier(this.getToolBarSymbolModifier(this.gestureIndex))
            .symbolEffect(new SymbolEffect(), false)
            .fontColor([$r('sys.color.icon_primary')])
            .fontSize(DIALOG_IMAGE_SIZE)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
        } else if (Util.isSymbolResource(this.gestureItem.image?.src)) {
          SymbolGlyph(this.gestureItem.image?.src as Resource)
            .fontColor([$r('sys.color.icon_primary')])
            .fontSize(DIALOG_IMAGE_SIZE)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
        } else {
          Image(this.gestureItem.image?.src as ResourceStr)
            .width(DIALOG_IMAGE_SIZE)
            .height(DIALOG_IMAGE_SIZE)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
            .fillColor($r('sys.color.icon_primary'))
        }
        Column() {
          Text(this.gestureItem.content.text)
            .fontSize(TEXT_TOOLBAR_DIALOG)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .maxLines(this.itemCardTextMaxLine)
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
      .constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG })
    } else {
      Column() {
        if (this.gestureItem.symbol) {
          SymbolGlyph()
            .attributeModifier(this.getToolBarSymbolModifier(this.gestureIndex))
            .symbolEffect(new SymbolEffect(), false)
            .fontColor([$r('sys.color.icon_primary')])
            .fontSize(DIALOG_IMAGE_SIZE)
        } else if (Util.isSymbolResource(this.gestureItem.image?.src)) {
          SymbolGlyph(this.gestureItem.image?.src as Resource)
            .fontColor([$r('sys.color.icon_primary')])
            .fontSize(DIALOG_IMAGE_SIZE)
        } else {
          Image(this.gestureItem.image?.src as ResourceStr)
            .width(DIALOG_IMAGE_SIZE)
            .height(DIALOG_IMAGE_SIZE)
            .fillColor($r('sys.color.icon_primary'))
        }
      }
      .constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG })
      .justifyContent(FlexAlign.Center)
    }
  }

  private toAccessibilityText(resource: ResourceStr | undefined, index: int): string {
    if (typeof resource === 'string') {
      return resource as string;
    } else if (typeof resource === 'undefined') {
      return this.toStringFormat(this.toolBarList[index]?.content?.text);
    } else {
      let str = (this.getUIContext().getHostContext() as common.UIAbilityContext)?.resourceManager?.
      getStringSync((resource as Resource).id)
      return str as string;
    }
  }

  private toStringFormat(resource: ResourceStr | undefined): string {
    if (typeof resource === 'string') {
      return resource as string;
    } else if (typeof resource === 'undefined') {
      return '' as string;
    } else {
      let str = (this.getUIContext().getHostContext() as common.UIAbilityContext)?.resourceManager?.
      getStringSync((resource as Resource).id)
      return str as string;
    }
  }

  private getFontSizeScale(): number {
    let context = this.getUIContext();
    let fontScaleSystem: number = 1;
    if (context.getHostContext()) {
      fontScaleSystem = (context.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    }
    if (!this.isFollowSystem) {
      return 1;
    } else {
      return Math.min(fontScaleSystem, this.maxFontSizeScale as Double);
    }
  }

  private isItemActivating(index: int): boolean {
    return this.localActivatedIndex === index &&
      (this.toolBarList[index]?.state === ToolBarV2ItemState.ACTIVATE);
  }

  private getToolBarSymbolModifier(index: int): SymbolGlyphModifier | undefined {
    if (this.isItemActivating(index)) {
      return this.toolBarList[index]?.symbol?.activated;
    }
    return this.toolBarList[index]?.symbol?.normal;
  }

  private getIconColor(index: int): ResourceColor {
    if (this.isItemActivating(index)) {
      return this.toolBarList[index]?.image?.activatedColor?.color ?? this.theme.iconActivePrimaryColor;
    }
    return this.toolBarList[index]?.image?.color?.color ?? this.theme.iconPrimaryColor;
  }

  private getTextColor(index: int): ResourceColor {
    if (this.isItemActivating(index)) {
      return this.toolBarList[index]?.content.activatedColor?.color ??
      this.theme.fontActivatedPrimaryColor;
    }
    return this.toolBarList[index]?.content.color?.color ?? this.theme.fontPrimaryColor;
  }

  private toLengthString(value?: LengthMetrics): string {
    if (value === undefined) {
      return '';
    }
    const length: number = value.value;
    let lengthString: string = '';
    switch (value.unit) {
      case LengthUnit.PX:
        lengthString = `${length}px`;
        break;
      case LengthUnit.FP:
        lengthString = `${length}fp`;
        break;
      case LengthUnit.LPX:
        lengthString = `${length}lpx`;
        break;
      case LengthUnit.PERCENT:
        lengthString = `${length * 100}%`;
        break;
      case LengthUnit.VP:
        lengthString = `${length}vp`;
        break;
      default:
        lengthString = `${length}vp`;
        break;
    }
    return lengthString;
  }

  private clickEventAction(index: int): void {
    let toolbar = this.toolBarList[index];
    if (toolbar.state === ToolBarV2ItemState.ACTIVATE) {
      if (this.localActivatedIndex === index) {
        this.localActivatedIndex = -1;
      } else {
        this.localActivatedIndex = index;
      }
    }
    if (toolbar.state !== ToolBarV2ItemState.DISABLE) {
      if (typeof toolbar.action === 'function') {
        toolbar.action?.(index);
      }
    }
  }

  private getItemGestureModifier(item: ToolBarV2Item, index: int): ButtonGestureModifier | undefined {
    if (!item?.icon) {
      return undefined;
    }
    let buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier();
    buttonGestureModifier.gestureCallBack = (event: UIGestureEvent) => {
      if (this.fontSize >= ButtonGestureModifier.minFontSize) {
        this.gestureItem = item;
        this.gestureIndex = index;
        event.addGesture(
          new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime as int })
            .onAction(() => {
              try {
                this.getUIContext().getPromptAction().openCustomDialog({
                  builder: this.itemCardDialogBuilder,
                  onWillAppear: () => {
                    try {
                      let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
                      if (context) {
                        let mainWindowStage = context.windowStage.getMainWindowSync();
                        let properties: window.WindowProperties =
                          mainWindowStage?.getWindowProperties() as window.WindowProperties;
                        if (this.getUIContext().px2vp(properties.windowRect.height) > SCREEN_WIDTH_BREAK_POINT) {
                          this.itemCardTextMaxLine = VERTICAL_SCREEN_TEXT_MAX_LINES;
                        } else {
                          this.itemCardTextMaxLine = HORIZONTAL_SCREEN_TEXT_MAX_LINES;
                        }
                      }
                    } catch (err) {
                      let code = (err as ClassCastError)?.code;
                      let message = (err as ClassCastError)?.message;
                      hilog.error(0x3900, 'Ace',
                        `ToolBarV2 get window height failed, code: ${code}, message: ${message}`);
                    }
                  },
                  maskColor: Color.Transparent,
                  isModal: true,
                  backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
                  backgroundColor: Color.Transparent,
                  shadow: ShadowStyle.OUTER_DEFAULT_LG,
                  cornerRadius: $r('sys.float.corner_radius_level10'),
                  width: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG
                } as promptAction.CustomDialogOptions
                ).then((dialogId: int) => {
                  this.itemDialogId = dialogId;
                });
              } catch (error: ClassCastError) {
                let code = (error as ClassCastError)?.code;
                let message = (error as ClassCastError)?.message;
                hilog.error(0x3900, 'Ace',
                  `ToolBarV2 get window height failed, code: ${code}, message: ${message}`);
              }
            })
            .onActionEnd(() => {
              if (this.itemDialogId) {
                try {
                  this.getUIContext().getPromptAction().closeCustomDialog(this.itemDialogId as int)
                } catch (error: ClassCastError) {
                  let message = (error as ClassCastError).message;
                  let code = (error as ClassCastError).code;
                  console.error(`closeCustomDialog error code is ${code}, message is ${message}`);
                }
              }
            })
            .onActionCancel(() => {
              if (this.itemDialogId) {
                try {
                  this.getUIContext().getPromptAction().closeCustomDialog(this.itemDialogId as int)
                } catch (error: ClassCastError) {
                  let message = (error as ClassCastError).message;
                  let code = (error as ClassCastError).code;
                  console.error(`closeCustomDialog error code is ${code}, message is ${message}`);
                }
              }
            })
        )
        return;
      }
      event.clearGestures();
    }
    return buttonGestureModifier;
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions) {
    children.forEach((child) => {
      child.layout({ x: 0, y: 0 })
    })
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    this.fontSize = this.getFontSizeScale();
    let sizeResult: SizeResult = { height: 0, width: 0 };
    if (Double.toInt(children.length) > 0) {
      children.forEach((child) => {
        let childMeasureResult: MeasureResult | undefined = child.measure(constraint);
        if (childMeasureResult) {
          sizeResult.width = childMeasureResult.width;
          sizeResult.height = childMeasureResult.height;
        }
      });
    }
    return sizeResult;
  }

  build() {
    Column() {
      Divider()
        .width('100%')
        .height(1)
        .attributeModifier(this.dividerModifier)
      Row() {
        ForEach(this.toolBarList, (item: ToolBarV2Item, index: int) => {
          if (this.toolBarList.length <= TOOLBAR_MAX_LENGTH || index < TOOLBAR_MAX_LENGTH - 1) {
            Row() {
              this.TabBuilder(index);
            }
            .height('100%')
            .flexShrink(1)
          }
        }, (item: ToolBarV2Item, index: int) => {
          return `${this.getUniqueId}__${index}}`;
        })
        if (this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
          Row() {
            this.MoreTabBuilder(TOOLBAR_MAX_LENGTH - 1);
          }
          .height('100%')
          .flexShrink(1)
        }
      }
      .justifyContent(FlexAlign.Center)
      .constraintSize({
        minHeight: this.toLengthString(this.toolBarModifier?.heightValue),
        maxHeight: this.toLengthString(this.toolBarModifier?.heightValue),
      })
      .width('100%')
      .height(this.toLengthString(this.toolBarModifier?.heightValue))
      .padding({
        start: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
          this.toolBarModifier?.paddingValue : LengthMetrics.resource($r('sys.float.padding_level0')),
        end: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
          this.toolBarModifier?.paddingValue : LengthMetrics.resource($r('sys.float.padding_level0')),
      } as LocalizedPadding)
    }
    .attributeModifier(this.toolBarModifier)
  }
}
