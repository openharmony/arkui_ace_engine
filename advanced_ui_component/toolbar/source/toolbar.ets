/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

import { Theme } from '@ohos.arkui.theme';
import { LengthMetrics, LengthUnit, ColorMetrics } from '@ohos.arkui.node';
import { DividerModifier, SymbolGlyphModifier } from '@ohos.arkui.modifier';
import hilog from '@ohos.hilog';
import window from '@ohos.window';
import common from '@ohos.app.ability.common';
import { BusinessError } from '@ohos.base';

export enum ItemState {
  ENABLE = 1,
  DISABLE = 2,
  ACTIVATE = 3,
}

// “更多”栏图标
const PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
const IMAGE_SIZE: string = '24vp';
const DEFAULT_TOOLBAR_HEIGHT: number = 56;
const TOOLBAR_MAX_LENGTH: number = 5;
const MAX_FONT_SIZE = 3.2;
const DIALOG_IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const TEXT_TOOLBAR_DIALOG = '18.3fp';
const FOCUS_BOX_MARGIN: number = -2;
const FOCUS_BOX_BORDER_WIDTH: number = 2;
const RESOURCE_TYPE_SYMBOL: number = 40000;

interface MenuController {
  value: ResourceStr;
  action: () => void;
  enabled?: boolean;
}

export interface ToolBarSymbolGlyphOptions {
  normal?: SymbolGlyphModifier;
  activated?: SymbolGlyphModifier;
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
          .onActionCancel(() => {
            this.controller?.close();
          })
      )
    } else {
      event.clearGestures();
    }
  }
}

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

@Observed
export class ToolBarOption {
  public content: ResourceStr = '';
  public action?: () => void = undefined;
  public icon?: Resource = undefined;
  public state?: ItemState = 1;
  public iconColor?: ResourceColor = $r('sys.color.icon_primary');
  public activatedIconColor?: ResourceColor = $r('sys.color.icon_emphasize');
  public textColor?: ResourceColor = $r('sys.color.font_primary');
  public activatedTextColor?: ResourceColor = $r('sys.color.font_emphasize');
  public toolBarSymbolOptions?: ToolBarSymbolGlyphOptions = undefined;
  public accessibilityText?: ResourceStr = '';
  public accessibilityDescription?: ResourceStr = '';
  public accessibilityLevel?: string = 'auto';
}

@Observed
export class ToolBarOptions extends Array<ToolBarOption> {
}

export class ToolBarModifier implements AttributeModifier<ColumnAttribute> {
  public backgroundColorValue?: ResourceColor = $r('sys.color.ohos_id_color_toolbar_bg');
  public heightValue?: LengthMetrics = LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT);
  public stateEffectValue?: boolean = true;
  public paddingValue?: LengthMetrics = LengthMetrics.resource($r('sys.float.padding_level12'));

  applyNormalAttribute(instance: ColumnAttribute): void {
    instance.backgroundColor(this.backgroundColorValue);
  }

  public backgroundColor(backgroundColor: ResourceColor): ToolBarModifier {
    this.backgroundColorValue = backgroundColor;
    return this;
  }

  public height(height: LengthMetrics): ToolBarModifier {
    this.heightValue = height;
    return this;
  }

  public stateEffect(stateEffect: boolean): ToolBarModifier {
    this.stateEffectValue = stateEffect;
    return this;
  }

  public padding(padding: LengthMetrics): ToolBarModifier {
    this.paddingValue = padding;
    return this;
  }
}

class ToolBarTheme {
  public iconPrimaryColor: ResourceColor = $r('sys.color.icon_primary');
  public iconActivePrimaryColor: ResourceColor = $r('sys.color.icon_emphasize');
  public fontPrimaryColor: ResourceColor = $r('sys.color.font_primary');
  public fontActivatedPrimaryColor: ResourceColor = $r('sys.color.font_emphasize');
}

@Component
export struct ToolBar {
  @ObjectLink toolBarList: ToolBarOptions;
  controller: TabsController = new TabsController();
  @Prop activateIndex: number = -1;
  @Prop dividerModifier: DividerModifier;
  @Prop toolBarModifier: ToolBarModifier;
  @Prop moreText: Resource = $r('sys.string.ohos_toolbar_more');
  @State menuContent: MenuController[] = [];
  @State toolBarItemBackground: ResourceColor[] = [];
  @State toolBarTheme: ToolBarTheme = new ToolBarTheme();
  @State fontSize: number = 1;
  isFollowSystem: boolean = false;
  maxFontSizeScale: number = 3.2;
  moreIndex: number = 4;
  moreItem: ToolBarOption = {
    content: $r('sys.string.ohos_toolbar_more'),
    icon: PUBLIC_MORE,
  }

  onWillApplyTheme(theme: Theme) {
    this.toolBarTheme.iconPrimaryColor = theme.colors.iconPrimary;
    this.toolBarTheme.iconActivePrimaryColor = theme.colors.iconEmphasize;
    this.toolBarTheme.fontPrimaryColor = theme.colors.fontPrimary;
    this.toolBarTheme.fontActivatedPrimaryColor = theme.colors.fontEmphasize;
  }

  @Builder
  MoreTabBuilder(index: number) {
    Button({ type: ButtonType.Normal, stateEffect: false }) {
      Column() {
        SymbolGlyph(PUBLIC_MORE)
          .fontSize(IMAGE_SIZE)
          .fontColor([this.toolBarTheme.iconPrimaryColor])
          .draggable(false)
          .margin({ bottom: $r('sys.float.padding_level1') })
        Text(this.moreText)
          .fontColor(this.toolBarTheme.fontPrimaryColor)
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
      })
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
    .bindMenu(this.menuContent, { placement: Placement.TopRight, offset: { x: -12, y: -10 } })
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .backgroundColor(this.toolBarItemBackground[index])
    .onHover((isHover: boolean) => {
      if (isHover) {
        this.toolBarItemBackground[index] = $r('sys.color.ohos_id_color_hover');
      } else {
        this.toolBarItemBackground[index] = Color.Transparent;
      }
    })
    .stateStyles({
      pressed: {
        .backgroundColor((!this.toolBarModifier?.stateEffectValue) ?
        this.toolBarItemBackground[index] : $r('sys.color.ohos_id_color_click_effect'))
      }
    })
    .gestureModifier(this.getItemGestureModifier(this.moreItem, index))
  }

  @Builder
  TabBuilder(index: number) {
    Button({ type: ButtonType.Normal, stateEffect: false }) {
      Column() {
        if (this.toolBarList[index]?.toolBarSymbolOptions?.normal ||
          this.toolBarList[index]?.toolBarSymbolOptions?.activated) {
          SymbolGlyph()
            .fontSize(IMAGE_SIZE)
            .symbolEffect(new SymbolEffect(), false)
            .attributeModifier(this.getToolBarSymbolModifier(index))
            .margin({ bottom: $r('sys.float.padding_level1') })
        } else if (Util.isSymbolResource(this.toolBarList[index]?.icon)) {
          SymbolGlyph(this.toolBarList[index]?.icon)
            .fontSize(IMAGE_SIZE)
            .fontColor([this.getIconColor(index)])
            .margin({ bottom: $r('sys.float.padding_level1') })
        } else {
          Image(this.toolBarList[index]?.icon)
            .width(IMAGE_SIZE)
            .height(IMAGE_SIZE)
            .fillColor(this.getIconColor(index))
            .margin({ bottom: $r('sys.float.padding_level1') })
            .objectFit(ImageFit.Contain)
            .draggable(false)
        }
        Text(this.toolBarList[index]?.content)
          .fontColor(this.getTextColor(index))
          .fontSize($r('sys.float.ohos_id_text_size_caption'))
          .maxFontSize($r('sys.float.ohos_id_text_size_caption'))
          .minFontSize(9)
          .fontWeight(FontWeight.Medium)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .textAlign(TextAlign.Center)
          .focusable(!(this.toolBarList[index]?.state === ItemState.DISABLE))
          .focusOnTouch(!(this.toolBarList[index]?.state === ItemState.DISABLE))
      }
      .justifyContent(FlexAlign.Center)
      .width('100%')
      .height('100%')
      .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
      .padding({
        start: LengthMetrics.resource($r('sys.float.padding_level2')),
        end: LengthMetrics.resource($r('sys.float.padding_level2')),
      })
    }
    .accessibilityGroup(true)
    .accessibilityText(this.toolBarList[index]?.accessibilityText as Resource ??
      this.toolBarList[index]?.content as Resource)
    .accessibilityDescription(this.toolBarList[index]?.accessibilityDescription as string ?? '')
    .accessibilityLevel(this.toolBarList[index]?.accessibilityLevel ?? 'auto')
    .enabled(this.toolBarList[index]?.state !== ItemState.DISABLE)
    .width('100%')
    .height('100%')
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .focusable(!(this.toolBarList[index]?.state === ItemState.DISABLE))
    .focusOnTouch(!(this.toolBarList[index]?.state === ItemState.DISABLE))
    .focusBox({
      margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
      strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
      strokeColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_focused_outline'))
    })
    .backgroundColor(this.toolBarItemBackground[index])
    .onHover((isHover: boolean) => {
      if (isHover && this.toolBarList[index]?.state !== ItemState.DISABLE) {
        this.toolBarItemBackground[index] = $r('sys.color.ohos_id_color_hover');
      } else {
        this.toolBarItemBackground[index] = Color.Transparent;
      }
    })
    .stateStyles({
      pressed: {
        .backgroundColor((this.toolBarList[index]?.state === ItemState.DISABLE) ||
          (!this.toolBarModifier?.stateEffectValue) ?
        this.toolBarItemBackground[index] : $r('sys.color.ohos_id_color_click_effect'))
      }
    })
    .onClick(() => {
      this.clickEventAction(index);
    })
    .gestureModifier(this.getItemGestureModifier(this.toolBarList[index], index))
  }

  private getFontSizeScale(): number {
    let context = this.getUIContext();
    let fontScaleSystem = (context.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.isFollowSystem) {
      return 1;
    } else {
      return Math.min(fontScaleSystem, this.maxFontSizeScale);
    }
  }

  private getToolBarSymbolModifier(index: number): SymbolGlyphModifier | undefined {
    if ((!this.toolBarList[index]?.toolBarSymbolOptions?.activated) &&
      (!this.toolBarList[index]?.toolBarSymbolOptions?.normal)) {
      return undefined;
    }
    if (this.activateIndex === index && (this.toolBarList[index]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[index]?.toolBarSymbolOptions?.activated;
    }
    return this.toolBarList[index]?.toolBarSymbolOptions?.normal;
  }

  private getIconColor(index: number): ResourceColor {
    if (this.activateIndex === index && (this.toolBarList[index]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[index]?.activatedIconColor ?? this.toolBarTheme.iconActivePrimaryColor;
    }
    return this.toolBarList[index]?.iconColor ?? this.toolBarTheme.iconPrimaryColor;
  }

  private getTextColor(index: number): ResourceColor {
    if (this.activateIndex === index && (this.toolBarList[index]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[index]?.activatedTextColor ?? this.toolBarTheme.fontActivatedPrimaryColor;
    }
    return this.toolBarList[index]?.textColor ?? this.toolBarTheme.fontPrimaryColor;
  }

  private toLengthString(value: LengthMetrics | undefined): string {
    if (value === void (0)) {
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

  private clickEventAction(index: number): void {
    let toolbar = this.toolBarList[index];
    if (toolbar.state === ItemState.ACTIVATE) {
      if (this.activateIndex === index) {
        this.activateIndex = -1;
      } else {
        this.activateIndex = index;
      }
    }
    if (!(toolbar.state === ItemState.DISABLE)) {
      toolbar.action && toolbar.action();
    }
  }

  private getItemGestureModifier(item: ToolBarOption, index: number): ButtonGestureModifier {
    let buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier(null);
    if (item?.icon || item?.toolBarSymbolOptions?.activated || item?.toolBarSymbolOptions?.normal) {
      buttonGestureModifier = new ButtonGestureModifier(new CustomDialogController({
        builder: ToolBarDialog({
          itemDialog: item,
          fontSize: this.fontSize,
          itemSymbolModifier: this.getToolBarSymbolModifier(index),
        }),
        maskColor: Color.Transparent,
        isModal: true,
        customStyle: true,
      }))
      buttonGestureModifier.fontSize = this.fontSize;
    }
    return buttonGestureModifier;
  }

  refreshData() {
    this.dividerModifier = this.dividerModifier ? this.dividerModifier : new DividerModifier();
    this.toolBarModifier = this.toolBarModifier ? this.toolBarModifier : new ToolBarModifier()
      .padding(LengthMetrics.resource($r('sys.float.padding_level12')))
      .stateEffect(true)
      .height(LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT))
      .backgroundColor('sys.color.ohos_id_color_toolbar_bg');
    this.menuContent = [];
    for (let i = 0; i < this.toolBarList.length; i++) {
      if (i >= this.moreIndex && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.menuContent[i - this.moreIndex] = {
          value: this.toolBarList[i].content,
          action: this.toolBarList[i].action ? this.toolBarList[i].action as () => void : () => {
          },
          enabled: this.toolBarList[i].state !== ItemState.DISABLE,
        }
      } else {
        this.menuContent = [];
      }
      this.toolBarItemBackground[i] = this.toolBarItemBackground[i] ?? Color.Transparent;
    }
    return true;
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    this.fontSize = this.getFontSizeScale();
    let sizeResult: SizeResult = { height: 0, width: 0 };
    children.forEach((child) => {
      let childMeasureResult: MeasureResult = child.measure(constraint);
      sizeResult.width = childMeasureResult.width;
      sizeResult.height = childMeasureResult.height;
    });
    return sizeResult;
  }

  aboutToAppear() {
    this.refreshData();
    try {
      this.isFollowSystem = this.getUIContext()?.isFollowingSystemFontScale();
      this.maxFontSizeScale = this.getUIContext()?.getMaxFontScale();
    } catch (err) {
      let code: number = (err as BusinessError)?.code;
      let message: string = (err as BusinessError)?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBar getMaxFontScale, code: ${code}, message: ${message}`);
    }
  }

  build() {
    Column() {
      Tabs({ controller: this.controller }) {
      }
      .visibility(Visibility.None)

      Divider()
        .width('100%').height(1)
        .attributeModifier(this.dividerModifier)
      Row() {
        ForEach(this.toolBarList, (item: ToolBarOption, index: number) => {
          if (this.toolBarList.length <= TOOLBAR_MAX_LENGTH || index < this.moreIndex) {
            Row() {
              this.TabBuilder(index);
            }
            .height('100%')
            .flexShrink(1)
          }
        }, (item: ToolBarOption, index: number) => {
          return `${this.getUniqueId()}__${index}}`;
        })
        if (this.refreshData() && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
          Row() {
            this.MoreTabBuilder(this.moreIndex);
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
      })
    }
    .attributeModifier(this.toolBarModifier)
  }
}

/**
 * ToolBarDialog
 *
 * @since 2024-07-23
 */
@CustomDialog
struct ToolBarDialog {
  itemDialog: ToolBarOption = {
    icon: undefined,
    content: '',
  };
  itemSymbolModifier?: SymbolGlyphModifier;
  mainWindowStage: window.Window | undefined = undefined;
  controller?: CustomDialogController
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
  @State symbolEffect: SymbolEffect = new SymbolEffect();

  build() {
    if (this.itemDialog.content) {
      Column() {
        if (this.itemDialog.toolBarSymbolOptions?.normal ||
          this.itemDialog.toolBarSymbolOptions?.activated) {
          SymbolGlyph()
            .attributeModifier(this.itemSymbolModifier)
            .symbolEffect(this.symbolEffect, false)
            .fontColor([$r('sys.color.icon_primary')])
            .fontSize(DIALOG_IMAGE_SIZE)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            })
        } else if (Util.isSymbolResource(this.itemDialog.icon)) {
          SymbolGlyph(this.itemDialog?.icon)
            .fontColor([$r('sys.color.icon_primary')])
            .fontSize(DIALOG_IMAGE_SIZE)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            })
        } else {
          Image(this.itemDialog.icon)
            .width(DIALOG_IMAGE_SIZE)
            .height(DIALOG_IMAGE_SIZE)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            })
            .fillColor($r('sys.color.icon_primary'))
        }
        Column() {
          Text(this.itemDialog.content)
            .fontSize(TEXT_TOOLBAR_DIALOG)
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
      .width(this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG)
      .constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius(($r('sys.float.corner_radius_level10')))
    } else {
      Column() {
        if (this.itemDialog.toolBarSymbolOptions?.normal ||
          this.itemDialog.toolBarSymbolOptions?.activated) {
          SymbolGlyph()
            .attributeModifier(this.itemSymbolModifier)
            .symbolEffect(this.symbolEffect, false)
            .fontColor([$r('sys.color.icon_primary')])
            .fontSize(DIALOG_IMAGE_SIZE)
        } else if (Util.isSymbolResource(this.itemDialog.icon)) {
          SymbolGlyph(this.itemDialog?.icon)
            .fontColor([$r('sys.color.icon_primary')])
            .fontSize(DIALOG_IMAGE_SIZE)
        } else {
          Image(this.itemDialog.icon)
            .width(DIALOG_IMAGE_SIZE)
            .height(DIALOG_IMAGE_SIZE)
            .fillColor($r('sys.color.icon_primary'))
        }
      }
      .width(this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG)
      .constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius(($r('sys.float.corner_radius_level10')))
      .justifyContent(FlexAlign.Center)
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