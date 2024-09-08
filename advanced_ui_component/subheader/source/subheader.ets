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

import { TextModifier } from '@ohos.arkui.modifier'
import { Theme } from '@ohos.arkui.theme';
import { LengthMetrics } from '@ohos.arkui.node';
import resourceManager from '@ohos.resourceManager';
import { BusinessError } from '@ohos.base';
import hilog from '@ohos.hilog';
import common from '@ohos.app.ability.common';

const INDEX_TWO: number = 2;
// 行数及整体高度
const SINGLE_LINE_NUM: number = 1;
const DOUBLE_LINE_NUM: number = 2;
const SINGLE_LINE_HEIGHT: number = 56;
const DOUBLE_LINE_HEIGHT: number = 72;
// 资源数值
const RESOURCE_TYPE_SYMBOL: number = 40000;
// 左边尺寸常量
const LEFT_ICON_SIZE: ResourceStr = '16vp';
const LEFT_ICON_SIZE_NUMBER: number = 16;
const LEFT_TEXT_NUMBER: number = 8;
// 右边尺寸常量
const OPERATE_ITEM_LENGTH: number = 24;
const ARROW_ICON_WIDTH: number = 12;
const SINGLE_ICON_ZONE_SIZE: number = 28;
const RIGHT_SINGLE_ICON_SIZE: ResourceStr = '24vp';
const PADDING_LEVEL_2: number = 4;
const MAX_RIGHT_WIDTH: Length = '34%';
const MIN_FONT_SIZE: number = 1.75;
const MIN_HOT_AREA_LENGTH: number = 40;
const MULTI_ICON_REGION_WIDTH: number = 37;
const ICON_REGION_X: number = -9;
const ICON_REGION_Y: number = -6;
const SINGLE_ICON_REGION_X: number = -12;
const SINGLE_ICON_NUMBER: number = 1;

export enum OperationType {
  TEXT_ARROW = 0,
  BUTTON = 1,
  ICON_GROUP = 2,
  LOADING = 3,
}

export declare class OperationOption {
  public value: ResourceStr;
  public action?: () => void;
}

export declare class SelectOptions {
  public options: Array<SelectOption>;
  public selected?: number;
  public value?: string;
  public onSelect?: (index: number, value?: string) => void;
}

export declare class SymbolOptions {
  public fontSize?: Length;
  public fontColor?: Array<ResourceColor>;
  public fontWeight?: number | FontWeight | string;
  public effectStrategy?: SymbolEffectStrategy;
  public renderingStrategy?: SymbolRenderingStrategy;
}

class IconOptions {
  public icon?: Resource;
  public symbolicIconOption?: SymbolOptions | null;
}

class ContentIconOption {
  public content?: ResourceStr;
  public subContent?: ResourceStr;
  public iconOptions?: IconOptions;
  public action?: () => void;
}

class FontStyle {
  public maxLines: number = 0;
  public fontWeight: number = 0;
  public fontColor?: ResourceColor;
  public alignment?: Alignment;
}

class SubHeaderTheme {
  public fontPrimaryColor: ResourceColor = $r('sys.color.font_primary');
  public fontSecondaryColor: ResourceColor = $r('sys.color.font_secondary');
  public fontButtonColor: ResourceColor = $r('sys.color.font_emphasize');
  public iconArrowColor: ResourceColor = $r('sys.color.icon_tertiary');
  public textArrowHoverBgColor: ResourceColor = $r('sys.color.interactive_hover');
  public borderFocusColor: ResourceColor = $r('sys.color.interactive_focus');
  public leftIconColor: ResourceColor = $r('sys.color.icon_secondary');
  public rightIconColor: ResourceColor = $r('sys.color.icon_primary');
}

@Extend(Text)
function secondaryTitleStyles(fontStyle: FontStyle) {
  .fontSize($r('sys.float.Subtitle_S'))
  .fontColor(fontStyle?.fontColor ?? $r('sys.color.font_secondary'))
  .fontWeight(fontStyle?.fontWeight)
  .maxLines(fontStyle?.maxLines)
  .textOverflow({ overflow: TextOverflow.Ellipsis })
  .align(fontStyle?.alignment)
}

@Extend(Text)
function primaryTitleStyles(fontStyle: FontStyle) {
  .fontSize($r('sys.float.Subtitle_L'))
  .fontColor(fontStyle?.fontColor ?? $r('sys.color.font_primary'))
  .fontWeight(fontStyle?.fontWeight)
  .maxLines(fontStyle?.maxLines)
  .textOverflow({ overflow: TextOverflow.Ellipsis })
  .align(fontStyle?.alignment)
}

@Styles
function pressedStyle() {
  .backgroundColor($r('sys.color.interactive_pressed'))
}

@Styles
function disabledStyle() {
  .opacity($r('sys.float.interactive_disable'))
}

class SubHeaderModifier implements AttributeModifier<RowAttribute> {
  public isAgeing: boolean = false

  applyNormalAttribute(instance: RowAttribute): void {
    if (this.isAgeing) {
      instance.width('100%')
    } else {
    }
  }
}

@Component
export struct SubHeader {
  @Prop icon: Resource | null = null;
  iconSymbolOptions?: SymbolOptions | null = null;
  @Prop primaryTitle: string | null = null;
  @State primaryTitleModifier: TextModifier = new TextModifier();
  @Prop secondaryTitle: string | null = null;
  @State secondaryTitleModifier: TextModifier = new TextModifier();
  @State subHeaderModifier: SubHeaderModifier = new SubHeaderModifier();
  select: SelectOptions | null = null;
  @Prop operationType: OperationType = OperationType.BUTTON;
  operationItem: Array<OperationOption> | null = null;
  operationSymbolOptions?: Array<SymbolOptions> | null = null;
  callbackId: number | undefined = undefined;
  @State fontSize: number = 1;
  @State ageing: boolean = true;
  // 内部变量
  @State textArrowBgColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background_transparent');
  @State buttonBgColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background_transparent');
  @State buttonStyleWidth: number = 0;
  @State buttonStyleHeight: number = 0;
  @State textArrowStyleWidth: number = 0;
  @State textArrowStyleHeight: number = 0;
  @State iconWidth: number = 0;
  @State selectedIndex: number | Resource | undefined = -1;
  @State selectValue: ResourceStr | undefined = '';
  @State flexAlign: FlexAlign = FlexAlign.SpaceBetween;
  @BuilderParam titleBuilder?: () => void;
  @Prop contentMargin: LocalizedMargin;
  @Prop contentPadding: LocalizedPadding;
  @State subHeaderMargin: LocalizedMargin = {
    start: LengthMetrics.resource($r('sys.float.margin_left')),
    end: LengthMetrics.resource($r('sys.float.margin_right')),
  };
  @Provide subHeaderTheme: SubHeaderTheme = new SubHeaderTheme();
  isFollowingSystemFontScale: boolean = false;
  appMaxFontScale: number = 3.2;
  constraintWidth: number = 0;
  paddingLeft: number = 2;

  onWillApplyTheme(theme: Theme) {
    this.subHeaderTheme.fontPrimaryColor = theme.colors.fontPrimary;
    this.subHeaderTheme.fontSecondaryColor = theme.colors.fontSecondary;
    this.subHeaderTheme.fontButtonColor = theme.colors.fontEmphasize;
    this.subHeaderTheme.iconArrowColor = theme.colors.iconTertiary;
    this.subHeaderTheme.textArrowHoverBgColor = theme.colors.interactiveHover;
    this.subHeaderTheme.borderFocusColor = theme.colors.interactiveFocus;
    this.subHeaderTheme.leftIconColor = theme.colors.iconSecondary;
    this.subHeaderTheme.rightIconColor = theme.colors.iconPrimary;
  }

  @Styles
  private commonContentPadding() {
    .padding({
      end: LengthMetrics.resource($r('sys.float.padding_level0')),
      top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.resource($r('sys.float.padding_level0'))
        : LengthMetrics.resource($r('sys.float.padding_level4')),
      bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.resource($r('sys.float.padding_level0'))
        : LengthMetrics.resource($r('sys.float.padding_level4')),
    })
  }

  @Styles
  private commonListPadding() {
    .padding({
      end: LengthMetrics.resource($r('sys.float.padding_level6')),
      top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.resource($r('sys.float.padding_level0'))
        : LengthMetrics.resource($r('sys.float.padding_level4')),
      bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.resource($r('sys.float.padding_level0'))
        : LengthMetrics.resource($r('sys.float.padding_level4')),
    })
  }

  @Styles
  private rightAreaClickEvent() {
    .onClick(() => {
      if ((this.operationType === OperationType.TEXT_ARROW || this.operationType === OperationType.BUTTON) &&
      this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
        this.operationItem[0].action();
      }
    })
    .onTouch((event) => {
      if (event.type === TouchType.Down) {
        if (this.operationType === OperationType.TEXT_ARROW) {
          this.textArrowBgColor = $r('sys.color.interactive_pressed');
        }
        if (this.operationType === OperationType.BUTTON) {
          this.buttonBgColor = $r('sys.color.interactive_pressed');
        }
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        if (this.operationType === OperationType.TEXT_ARROW) {
          this.textArrowBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
        if (this.operationType === OperationType.BUTTON) {
          this.buttonBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      }
    })
  }

  updateFontScale(): number {
    try {
      let uiContext: UIContext = this.getUIContext();
      let systemFontScale = (uiContext.getHostContext() as common.UIAbilityContext)?.config.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(systemFontScale, this.appMaxFontScale);
    } catch (exception) {
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  async aboutToAppear(): Promise<void> {
    let uiContext: UIContext = this.getUIContext();
    this.isFollowingSystemFontScale = uiContext.isFollowingSystemFontScale();
    this.appMaxFontScale = uiContext.getMaxFontScale();
    this.fontSize = this.updateFontScale();
    if (this.isSuitableAging()) {
      this.ageing = true;
      this.subHeaderModifier.isAgeing = this.ageing;
    } else {
      this.ageing = false;
      this.subHeaderModifier.isAgeing = this.ageing;
    }
    if (this.select) {
      this.selectedIndex = this.select.selected;
      this.selectValue = this.select.value;
    }
  }

  private isSuitableAging(): boolean | null {
    return (this.fontSize >= MIN_FONT_SIZE) && ((this.operationType === OperationType.TEXT_ARROW) ||
      this.operationType === OperationType.BUTTON) && this.operationItem &&
      (this.operationItem?.length > 0) && this.operationItem[0].value !== '';
  }

  build() {
    if (this.isSuitableAging()) {
      Column() {
        Row() {
          this.leftArea();
        }
        .margin({
          top: LengthMetrics.resource($r('sys.float.padding_level8')),
          bottom: LengthMetrics.resource($r('sys.float.padding_level1')),
        })
        .padding({
          start: this.contentMargin ? this.contentMargin.start : LengthMetrics.resource($r('sys.float.margin_left')),
          end: this.contentMargin ? this.contentMargin.end : LengthMetrics.resource($r('sys.float.margin_right')),
        })
        .width('100%')

        Row() {
          this.rightArea();
        }
        .margin({
          bottom: $r('sys.float.padding_level4'),
        })
        .padding({
          // 'sys.float.margin_left' id,value: 16vp
          start: LengthMetrics.vp((this.contentMargin ? 
          (this.contentMargin.start ? this.contentMargin.start.value : 0) :
          Util.getNumberByResource(125830936, LEFT_ICON_SIZE_NUMBER)) - this.paddingLeft),
          // 'sys.float.margin_right' id,value: 16vp
          end: this.contentMargin ? this.contentMargin.end : LengthMetrics.vp(Util.getNumberByResource(125830937,
            LEFT_ICON_SIZE_NUMBER)),
        })
        .justifyContent(FlexAlign.Start)
        .width('100%')
        .rightAreaClickEvent()
      }
      .constraintSize({ minHeight: this.getMinHeight() })
      .padding(this.getAreaPadding())
    } else {
      Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.End }) {
        Row() {
          this.leftArea();
        }
        .margin({
          top: this.fontSize >= MIN_FONT_SIZE ? $r('sys.float.padding_level8') : ''
        })
        .width('100%')
        .flexShrink(1)

        Row() {
          this.rightArea();
        }
        .justifyContent(FlexAlign.End)
        .alignItems(VerticalAlign.Bottom)
        .constraintSize({
          maxWidth: this.getRightAreaMaxWidth(),
          minWidth: this.getRightAreaMinWidth(),
          minHeight: MIN_HOT_AREA_LENGTH,
        })
        .flexShrink(0)
        .rightAreaClickEvent()
      }
      .constraintSize({ minHeight: this.getMinHeight() })
      .margin(this.contentMargin ?? this.subHeaderMargin)
      .padding(this.getAreaPadding())
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    let result: SizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
    this.fontSize = this.updateFontScale();
    if (this.isSuitableAging()) {
      this.ageing = true;
      this.subHeaderModifier.isAgeing = this.ageing;
    } else {
      this.ageing = false;
      this.subHeaderModifier.isAgeing = this.ageing;
    }
    children.forEach((child) => {
      constraint.minHeight = Math.min(Number(this.getMinHeight()), Number(constraint.maxHeight));
      result.height = child.measure(constraint).height;
      result.width = Number(constraint.maxWidth);
    })
    return result;
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void {
    children.forEach((child) => {
      child.layout({ x: 0, y: 0 });
    })
  }

  private getRightAreaMaxWidth(): Length {
    if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
      return '100%';
    }
    return MAX_RIGHT_WIDTH;
  }

  private getRightAreaMinWidth(): Length {
    if (this.operationItem && this.operationItem.length > 0) {
      return MIN_HOT_AREA_LENGTH;
    }
    return 0;
  }

  private getMinHeight(): Length {
    if (this.secondaryTitle && this.icon) {
      return SINGLE_LINE_HEIGHT;
    } else if (this.secondaryTitle && this.primaryTitle) {
      return DOUBLE_LINE_HEIGHT;
    }
    return SINGLE_LINE_HEIGHT;
  }

  private getTextArrowPaddingLeft(): LengthMetrics {
    if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
      return LengthMetrics.resource($r('sys.float.padding_level1'));
    }
    return LengthMetrics.resource($r('sys.float.padding_level0'));
  }

  private getTextArrowMarginRight(): LengthMetrics {
    if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
      return LengthMetrics.vp(PADDING_LEVEL_2 + ARROW_ICON_WIDTH);
    }
    return LengthMetrics.vp(ARROW_ICON_WIDTH);
  }

  private getAreaPadding(): LocalizedPadding {
    if (this.contentPadding) {
      return this.contentPadding;
    }
    let padding: LocalizedPadding = {};
    if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
      (!this.primaryTitle && this.secondaryTitle))) {
      padding = {
        start: LengthMetrics.resource($r('sys.float.padding_level6')),
        end: LengthMetrics.resource($r('sys.float.padding_level6')),
      }
    }
    return padding;
  }

  @Builder
  leftArea(): void {
    if (this.titleBuilder) {
      this.titleBuilder();
    } else if (this.secondaryTitle && this.icon) {
      this.IconSecondaryTitleStyle({
        content: this.secondaryTitle,
        iconOptions: {
          icon: this.icon,
          symbolicIconOption: this.iconSymbolOptions,
        },
      });
    } else if (this.secondaryTitle && this.primaryTitle) {
      this.SubTitleStyle({ content: this.primaryTitle, subContent: this.secondaryTitle });
    } else if (this.secondaryTitle) {
      this.SecondTitleStyle({ content: this.secondaryTitle });
    } else if (this.select) {
      this.SelectStyle(this.select);
    } else if (this.primaryTitle) {
      this.PrimaryTitleStyle({ content: this.primaryTitle });
    } else {
      // 其他不支持场景
      this.dummyFunction();
    }
  }

  @Builder
  rightArea(): void {
    if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
      this.ButtonStyle(this.operationItem[0]);
    }
    if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
      this.TextArrowStyle(this.operationItem[0]);
    }
    if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
      this.IconGroupStyle(this.operationItem);
    }
    if (this.operationType === OperationType.LOADING) {
      this.LoadingProcessStyle();
    }
  }

  @Builder
  IconSecondaryTitleStyle($$: ContentIconOption): void {
    Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
      if (Util.isSymbolResource($$.iconOptions?.icon)) {
        SymbolGlyph($$.iconOptions?.icon)
          .fontSize($$.iconOptions?.symbolicIconOption?.fontSize ?
          Util.symbolFontSize($$.iconOptions?.symbolicIconOption?.fontSize) : LEFT_ICON_SIZE)
          .fontColor($$.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor])
          .fontWeight($$.iconOptions?.symbolicIconOption?.fontWeight)
          .renderingStrategy($$.iconOptions?.symbolicIconOption?.renderingStrategy)
          .effectStrategy($$.iconOptions?.symbolicIconOption?.effectStrategy)
          .margin({ end: LengthMetrics.resource($r('sys.float.padding_level4')) })
          .flexShrink(0)
      } else {
        Image($$.iconOptions?.icon)
          .fillColor(this.subHeaderTheme.leftIconColor)
          .width(LEFT_ICON_SIZE)
          .height(LEFT_ICON_SIZE)
          .margin({ end: LengthMetrics.resource($r('sys.float.padding_level4')) })
          .draggable(false)
          .flexShrink(0)
      }
      Text($$.content)
        .secondaryTitleStyles({
          maxLines: DOUBLE_LINE_NUM,
          fontWeight: FontWeight.Medium,
          alignment: Alignment.Start,
          fontColor: this.subHeaderTheme.fontSecondaryColor,
        })
        .attributeModifier(this.secondaryTitleModifier)
        .flexShrink(1)
    }
    .commonListPadding()
    .onAppear(() => {
      this.changeFlexAlign(FlexAlign.SpaceBetween);
    })
  }

  @Builder
  SubTitleStyle($$: ContentIconOption): void {
    Column() {
      Text($$.content)
        .primaryTitleStyles({
          fontWeight: FontWeight.Bold,
          maxLines: DOUBLE_LINE_NUM,
          alignment: Alignment.Start,
          fontColor: this.subHeaderTheme.fontPrimaryColor,
        })
        .attributeModifier(this.primaryTitleModifier)
        .accessibilityLevel('yes')
        .width('100%')
      Text($$.subContent)
        .secondaryTitleStyles({
          maxLines: DOUBLE_LINE_NUM,
          fontWeight: FontWeight.Regular,
          alignment: Alignment.Start,
          fontColor: this.subHeaderTheme.fontSecondaryColor,
        })
        .width('100%')
        .margin({
          top: $r('sys.float.padding_level1'),
        })
        .attributeModifier(this.secondaryTitleModifier)
        .accessibilityLevel('yes')
    }
    .commonContentPadding()
    .alignItems(HorizontalAlign.Start)
    .onAppear(() => {
      this.changeFlexAlign(FlexAlign.SpaceBetween);
    })
  }

  @Builder
  SecondTitleStyle($$: ContentIconOption): void {
    Column() {
      Text($$.content)
        .secondaryTitleStyles({
          maxLines: DOUBLE_LINE_NUM,
          fontWeight: FontWeight.Medium,
          alignment: Alignment.Start,
          fontColor: this.subHeaderTheme.fontSecondaryColor,
        })
        .width('100%')
        .onAppear(() => {
          this.changeFlexAlign(FlexAlign.SpaceBetween);
        })
        .attributeModifier(this.secondaryTitleModifier)
        .accessibilityLevel('yes')
    }
    .alignItems(HorizontalAlign.Start)
    .commonListPadding()
  }

  @Builder
  SelectStyle(selectParam: SelectOptions): void {
    Column() {
      Select(selectParam.options)
        .height('auto')
        .width('auto')
        .selected(this.selectedIndex)
        .value(this.selectValue)
        .onSelect((index: number, value?: string) => {
          this.selectedIndex = index;
          if (value) {
            this.selectValue = value;
          }
          if (selectParam.onSelect) {
            selectParam.onSelect(index, value);
          }
        })
        .font({
          size: $r('sys.float.Body_L'),
          weight: FontWeight.Medium,
        })
    }
    .alignItems(HorizontalAlign.Start)
    .onAppear(() => {
      this.changeFlexAlign(FlexAlign.SpaceBetween);
    })
  }

  @Builder
  PrimaryTitleStyle($$: ContentIconOption): void {
    Column() {
      Text($$.content)
        .primaryTitleStyles({
          fontWeight: FontWeight.Bold,
          maxLines: DOUBLE_LINE_NUM,
          alignment: Alignment.Start,
          fontColor: this.subHeaderTheme.fontPrimaryColor,
        })
        .width('100%')
        .onAppear(() => {
          this.changeFlexAlign(FlexAlign.SpaceBetween);
        })
        .attributeModifier(this.primaryTitleModifier)
        .accessibilityLevel('yes')
    }
    .alignItems(HorizontalAlign.Start)
    .commonContentPadding()
  }

  @Builder
  ButtonStyle(button: OperationOption): void {
    Row() {
      Stack() {
        if (button) {
          Row() {
            Text(button.value)
              .secondaryTitleStyles({
                fontWeight: FontWeight.Medium,
                maxLines: DOUBLE_LINE_NUM,
                fontColor: this.subHeaderTheme.fontButtonColor,
              })
          }
          .padding({
            start: LengthMetrics.resource($r('sys.float.padding_level1')),
            end: LengthMetrics.resource($r('sys.float.padding_level1')),
            top: LengthMetrics.resource($r('sys.float.padding_level2')),
            bottom: LengthMetrics.resource($r('sys.float.padding_level2')),
          })
          .margin({
            start: this.leftIconMargin(),
            bottom: $r('sys.float.padding_level2'),
          })
          .backgroundColor(this.buttonBgColor)
          .focusable(true)
          .constraintSize({ minHeight: OPERATE_ITEM_LENGTH })
          .justifyContent(FlexAlign.End)
          .borderRadius($r('sys.float.corner_radius_level4'))
          .onHover((isHover: boolean) => {
            if (isHover) {
              this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
            } else {
              this.buttonBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
            }
          })
          .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
            this.buttonStyleWidth = Number(newValue.width);
            this.buttonStyleHeight = Number(newValue.height);
          })

          Text()
            .focusable(true)
            .width(this.buttonStyleWidth)
            .height(this.buttonStyleHeight)
            .hitTestBehavior(HitTestMode.None)
            .stateStyles({
              focused: {
                .border({
                  radius: $r('sys.float.corner_radius_level4'),
                  width: $r('sys.float.outline_extra_larger'),
                  color: this.subHeaderTheme.borderFocusColor,
                })
              },
              pressed: pressedStyle,
              disabled: disabledStyle,
              normal: {
                .border({
                  radius: $r('sys.float.corner_radius_level4'),
                  width: $r('sys.float.border_none'),
                  color: $r('sys.color.ohos_id_color_focused_outline_transparent'),
                })
              }
            })
        }
      }
      .focusable(true)
    }
    .margin({
      start: LengthMetrics.resource(this.ageing ? $r('sys.float.padding_level0') : $r('sys.float.padding_level4')),
      bottom: LengthMetrics.resource(this.ageing ? $r('sys.float.padding_level0') : $r('sys.float.padding_level2')),
    })
    .justifyContent(FlexAlign.End)
  }

  private leftIconMargin(): LengthMetrics {
    if (this.titleBuilder) {
      return LengthMetrics.vp(0);
    }
    if (this.icon && Util.isSymbolResource(this.icon)) {
      return this.ageing ? LengthMetrics.vp((this.iconSymbolOptions?.fontSize ?
      Util.numberToSize(this.iconSymbolOptions?.fontSize) : LEFT_ICON_SIZE_NUMBER) +
        LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
    } else {
      return (this.ageing && this.icon) ? LengthMetrics.vp(LEFT_ICON_SIZE_NUMBER +
        LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
    }
  }

  @Builder
  TextArrowStyle(textArrow: OperationOption): void {
    Row() {
      Stack() {
        Row() {
          if (textArrow) {
            Text(textArrow.value)
              .secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Regular,
                alignment: Alignment.End,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
              })
              .margin({
                end: this.getTextArrowMarginRight(),
              })
          }
        }
        .attributeModifier(this.subHeaderModifier)
        .alignItems(VerticalAlign.Center)
        .borderRadius($r('sys.float.corner_radius_level4'))
        .focusable(true)
        .backgroundColor(this.textArrowBgColor)
        .constraintSize({ minHeight: OPERATE_ITEM_LENGTH })
        .padding({
          start: this.getTextArrowPaddingLeft(),
          top: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.resource($r('sys.float.padding_level2')),
          bottom: this.ageing ? LengthMetrics.vp(0) : LengthMetrics.resource($r('sys.float.padding_level2')),
        })
        .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
          this.textArrowStyleWidth = Number(newValue.width);
          this.textArrowStyleHeight = Number(newValue.height);
        })

        Row() {
          Image($r('sys.media.ohos_ic_public_arrow_right'))
            .fillColor(this.subHeaderTheme.iconArrowColor)
            .width(ARROW_ICON_WIDTH)
            .height(OPERATE_ITEM_LENGTH)
            .focusable(true)
            .draggable(false)
            .matchTextDirection(true)
        }
        .justifyContent(FlexAlign.End)
        .height(this.textArrowStyleHeight)
        .width(this.textArrowStyleWidth)
        .hitTestBehavior(HitTestMode.None)
        .stateStyles({
          focused: {
            .border({
              radius: $r('sys.float.corner_radius_level4'),
              width: $r('sys.float.outline_extra_larger'),
              color: this.subHeaderTheme.borderFocusColor,
            })
          },
          pressed: pressedStyle,
          disabled: disabledStyle,
          normal: {
            .border({
              radius: $r('sys.float.corner_radius_level4'),
              width: $r('sys.float.border_none'),
              color: $r('sys.color.ohos_id_color_focused_outline_transparent'),
            })
          }
        })
      }
      .margin({
        start: this.leftIconMargin(),
      })
      .onHover((isHover: boolean) => {
        if (isHover) {
          this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
        } else {
          this.textArrowBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      })
    }
    .attributeModifier(this.subHeaderModifier)
    .focusable(true)
    .justifyContent(this.ageing ? FlexAlign.SpaceBetween : FlexAlign.End)
    .margin({
      start: LengthMetrics.resource(this.ageing ? $r('sys.float.padding_level0') : $r('sys.float.padding_level4')),
      bottom: LengthMetrics.resource(this.ageing ? $r('sys.float.padding_level0') : $r('sys.float.padding_level2')),
    })
  }

  @Builder
  IconGroupStyle(operationItem: Array<OperationOption>): void {
    Row() {
      ForEach(operationItem, (item: OperationOption, index: number) => {
        if (Util.isResourceType(item.value)) {
          if (index <= INDEX_TWO) {
            SingleIconStyle({
              item: {
                iconOptions: {
                  icon: item.value as Resource,
                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > index ?
                  this.operationSymbolOptions[index] : null,
                },
                action: item.action,
              },
              isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
            })
              .margin({
                start: LengthMetrics.resource($r('sys.float.padding_level4')),
                bottom: LengthMetrics.resource($r('sys.float.padding_level3')),
              })
          } else {
            // 最大支持3个ICON,此场景不支持
          }
        }
      })
    }
    .justifyContent(FlexAlign.End)
    .focusable(true)
  }

  @Builder
  LoadingProcessStyle(): void {
    Row() {
      LoadingProgress()
        .width(OPERATE_ITEM_LENGTH)
        .height(OPERATE_ITEM_LENGTH)
        .color($r('sys.color.icon_secondary'))
    }
    .justifyContent(FlexAlign.End)
    .padding({
      top: $r('sys.float.padding_level2'),
      bottom: $r('sys.float.padding_level2'),
    })
    .margin({
      start: LengthMetrics.resource($r('sys.float.padding_level4')),
    })
  }

  @Builder
  dummyFunction(): void {
    Row() {
    }.onAppear(() => {
      this.changeFlexAlign(FlexAlign.End);
    });
  }

  private changeFlexAlign(flex: FlexAlign): void {
    if (this.flexAlign === flex) {
      return;
    }
    this.flexAlign = flex;
  }
}

@Component
struct SingleIconStyle {
  @State bgColor: Resource = $r('sys.color.ohos_id_color_sub_background_transparent');
  @State isFocus: boolean = false;
  item: ContentIconOption | null = null;
  @Consume subHeaderTheme: SubHeaderTheme;
  isSingleIcon: boolean = true;

  build() {
    if (this.item && this.item.iconOptions) {
      Row() {
        this.IconZone();
      }
      .focusable(true)
      .width(SINGLE_ICON_ZONE_SIZE)
      .height(SINGLE_ICON_ZONE_SIZE)
      .justifyContent(FlexAlign.Center)
      .backgroundColor(this.bgColor)
      .stateStyles({
        normal: {
          .border({
            radius: $r('sys.float.corner_radius_level4'),
            width: $r('sys.float.border_none'),
            color: $r('sys.color.ohos_id_color_sub_background_transparent'),
          })
        },
        focused: {
          .border({
            radius: $r('sys.float.corner_radius_level4'),
            width: $r('sys.float.outline_extra_larger'),
            color: this.subHeaderTheme.borderFocusColor,
            style: BorderStyle.Solid,
          })
        },
        pressed: pressedStyle,
        disabled: disabledStyle,
      })
      .onTouch((event) => {
        if (event.type === TouchType.Down || TouchType.Cancel) {
          this.bgColor = $r('sys.color.interactive_pressed');
        }
        if (event.type === TouchType.Up) {
          this.bgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      })
      .onHover((isHover: boolean) => {
        if (isHover) {
          this.bgColor = $r('sys.color.interactive_hover');
        } else {
          this.bgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
        }
      })
      .responseRegion(this.iconResponseRegion())
      .onClick((event) => {
        if (this.item?.action) {
          this.item?.action();
        }
      })
    }
  }

  private iconResponseRegion(): Rectangle {
    if (this.isSingleIcon) {
      return { x: SINGLE_ICON_REGION_X, y: ICON_REGION_Y, width: MIN_HOT_AREA_LENGTH, height: MIN_HOT_AREA_LENGTH };
    }
    return { x: ICON_REGION_X, y: ICON_REGION_Y, width: MULTI_ICON_REGION_WIDTH, height: MIN_HOT_AREA_LENGTH };
  }

  private fontSizeValue(item: ContentIconOption): Length {
    return item.iconOptions?.symbolicIconOption?.fontSize ?
    Util.symbolFontSize(item.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE
  }

  @Builder
  IconZone(): void {
    if (this.item && this.item.iconOptions) {
      if (Util.isSymbolResource(this.item.iconOptions.icon)) {
        SymbolGlyph(this.item.iconOptions?.icon)
          .focusable(true)
          .fontSize(this.fontSizeValue(this.item))
          .fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.rightIconColor])
          .fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight)
          .renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy)
          .effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy)
      } else {
        Image(this.item?.iconOptions?.icon)
          .fillColor(this.subHeaderTheme.rightIconColor)
          .width(RIGHT_SINGLE_ICON_SIZE)
          .height(RIGHT_SINGLE_ICON_SIZE)
          .focusable(true)
          .draggable(false)
      }
    }
  }
}

class Util {
  /**
   * 是否symbol资源
   * @param resourceStr  资源
   * @returns true：symbol资源；false:非symbol资源
   */
  public static isSymbolResource(resourceStr: ResourceStr | undefined): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
    return resource.type === RESOURCE_TYPE_SYMBOL;
  }

  /**
   * 是否Resource类型
   * @param resource 资源
   * @returns true：Resource类型；false:非Resource类型
   */
  public static isResourceType(resource: ResourceStr | Resource | undefined): boolean {
    if (!resource) {
      return false;
    }
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return false;
    }
    return true;
  }

  /**
   * get resource size
   *
   * @param resourceName resource id
   * @returns resource size
   */
  public static getNumberByResource(resourceId: number, defaultNumber: number): number {
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
      hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${code}, message: ${message}`);
      return 0;
    }
  }

  public static numberToSize(fontSize: Length): number {
    if (typeof fontSize === 'string') {
      const fontSizeNumber: number = parseInt(fontSize);
      return fontSizeNumber;
    } else if (typeof fontSize === 'number') {
      return fontSize;
    } else {
      return getContext().resourceManager.getNumber(fontSize);
    }
  }

  public static symbolFontSize(fontSize: Length): Length {
    return Util.numberToSize(fontSize) + 'vp';
  }
}