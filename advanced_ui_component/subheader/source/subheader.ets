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

import { KeyCode } from '@ohos.multimodalInput.keyCode';
import { TextModifier } from '@ohos.arkui.modifier'
import { Theme } from '@ohos.arkui.theme';

const INDEX_ZERO: number = 0;
const INDEX_ONE: number = 1;
const INDEX_TWO: number = 2;
// 行数及整体高度
const SINGLE_LINE_NUM: number = 1;
const DOUBLE_LINE_NUM: number = 2;
const SINGLE_LINE_HEIGHT: number = 56;
const DOUBLE_LINE_HEIGHT: number = 72;
// 资源数值
const BORDER_WIDTH: number = 2;
const RESOURCE_TYPE_SYMBOL: number = 40000;
// 左边尺寸常量
const LEFT_ICON_SIZE: number = 16;
// 右边尺寸常量
const BUTTON_ZONE_SIZE: number = 32;
const BUTTON_HEIGHT: number = 28;
const ARROW_ICON_WIDTH: number = 12;
const ARROW_ICON_HEIGHT: number = 24;
const SINGLE_ICON_ZONE_SIZE: number = 32;
const RIGHT_SINGLE_ICON_SIZE: number = 24;
const LOADING_SIZE: number = 24;
const PADDING_LEVEL_2: number = 4;
const MAX_RIGHT_WIDTH: Length = '34%';

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

@Styles
function commonContentPadding() {
  .padding({
    left: $r('sys.float.padding_level0'),
    right: $r('sys.float.padding_level0'),
    top: $r('sys.float.padding_level4'),
    bottom: $r('sys.float.padding_level4'),
  })
}

@Styles
function commonListPadding() {
  .padding({
    left: $r('sys.float.padding_level6'),
    right: $r('sys.float.padding_level6'),
    top: $r('sys.float.padding_level4'),
    bottom: $r('sys.float.padding_level4'),
  })
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

@Component
export struct SubHeader {
  @Prop icon: Resource | null = null;
  iconSymbolOptions?: SymbolOptions | null = null;
  @Prop primaryTitle: string | null = null;
  @State primaryTitleModifier: TextModifier = new TextModifier();
  @Prop secondaryTitle: string | null = null;
  @State secondaryTitleModifier: TextModifier = new TextModifier();
  select: SelectOptions | null = null;
  @Prop operationType: OperationType = OperationType.BUTTON;
  operationItem: Array<OperationOption> | null = null;
  operationSymbolOptions?: Array<SymbolOptions> | null = null;
  // 内部变量
  @State isDuplicateLine: boolean = false;
  @State textArrowBgColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background_transparent');
  @State buttonBgColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background_transparent');
  @State textArrowFocus: boolean = false;
  @State buttonFocus: boolean = false;
  @State textArrowStyleWidth: number = 0;
  @State textArrowStyleHeight: number = 0;
  @State buttonStyleWidth: number = 0;
  @State buttonStyleHeight: number = 0;
  @State iconWidth: number = 0;
  @State selectedIndex: number | Resource | undefined = -1;
  @State selectValue: ResourceStr | undefined = '';
  @State flexAlign: FlexAlign = FlexAlign.SpaceBetween;
  @BuilderParam titleBuilder?: () => void;
  @Prop contentMargin: Margin;
  @Provide subHeaderTheme: SubHeaderTheme = new SubHeaderTheme()

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

  build() {
    Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.End }) {
      Row() {
        this.leftArea();
      }
      .width('100%')
      .margin({
        left: this.contentMargin?.left ?? $r('sys.float.margin_left'),
        right: this.getMarginRight()
      })
      .flexShrink(1)

      Row() {
        this.rightArea();
      }
      .justifyContent(FlexAlign.End)
      .constraintSize({ maxWidth: this.getMaxWidth() })
      .flexShrink(0)
    }
    .width('100%')
    .focusable(true)
    .constraintSize({ minHeight: this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT })
  }

  private getMarginRight(): Length {
    if (this.operationType === OperationType.LOADING || (this.operationItem && this.operationItem.length > 0)) {
      return $r('sys.float.padding_level0');
    }
    return this.contentMargin?.right ?? $r('sys.float.margin_right');
  }

  private getMaxWidth(): Length {
    if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
      return '100%';
    } else {
      return MAX_RIGHT_WIDTH;
    }
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
          .focusable(true)
          .fontSize($$.iconOptions?.symbolicIconOption?.fontSize ?? LEFT_ICON_SIZE)
          .fontColor($$.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor])
          .fontWeight($$.iconOptions?.symbolicIconOption?.fontWeight)
          .renderingStrategy($$.iconOptions?.symbolicIconOption?.renderingStrategy)
          .effectStrategy($$.iconOptions?.symbolicIconOption?.effectStrategy)
          .margin({ right: $r('sys.float.padding_level4') })
          .flexShrink(0)
      } else {
        Image($$.iconOptions?.icon)
          .fillColor(this.subHeaderTheme.leftIconColor)
          .width(LEFT_ICON_SIZE)
          .height(LEFT_ICON_SIZE)
          .margin({ right: $r('sys.float.padding_level4') })
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
      this.isDuplicateLine = false;
      this.changeFlexAlign(FlexAlign.SpaceBetween);
    })
  }

  @Builder
  SubTitleStyle($$: ContentIconOption): void {
    Column() {
      Text($$.content)
        .primaryTitleStyles({
          fontWeight: FontWeight.Bold,
          maxLines: SINGLE_LINE_NUM,
          alignment: Alignment.Start,
          fontColor: this.subHeaderTheme.fontPrimaryColor,
        })
        .attributeModifier(this.primaryTitleModifier)
        .width('100%')
      Text($$.subContent)
        .secondaryTitleStyles({
          maxLines: SINGLE_LINE_NUM,
          fontWeight: FontWeight.Regular,
          alignment: Alignment.Start,
          fontColor: this.subHeaderTheme.fontSecondaryColor,
        })
        .width('100%')
        .margin({
          top: $r('sys.float.padding_level1'),
        })
        .attributeModifier(this.secondaryTitleModifier)
    }
    .commonContentPadding()
    .alignItems(HorizontalAlign.Start)
    .onAppear(() => {
      this.isDuplicateLine = true;
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
          this.isDuplicateLine = false;
          this.changeFlexAlign(FlexAlign.SpaceBetween);
        })
        .attributeModifier(this.secondaryTitleModifier)
    }
    .alignItems(HorizontalAlign.Start)
    .commonListPadding()
  }

  @Builder
  SelectStyle(selectParam: SelectOptions): void {
    Column() {
      Select(selectParam.options)
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
      this.isDuplicateLine = false;
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
          this.isDuplicateLine = false;
          this.changeFlexAlign(FlexAlign.SpaceBetween);
        })
        .attributeModifier(this.primaryTitleModifier)
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
                maxLines: SINGLE_LINE_NUM,
                fontColor: this.subHeaderTheme.fontButtonColor,
              })
              .focusable(true)
          }
          .padding({
            left: $r('sys.float.padding_level3'),
            right: $r('sys.float.padding_level3'),
          })
          .margin({
            bottom: $r('sys.float.padding_level2'),
          })
          .backgroundColor(this.buttonBgColor)
          .focusable(true)
          .constraintSize({ minHeight: BUTTON_HEIGHT })
          .justifyContent(FlexAlign.End)
          .borderRadius($r('sys.float.corner_radius_level4'))
          .onFocus(() => {
            this.buttonFocus = true;
          })
          .onBlur(() => {
            this.buttonFocus = false;
          })
          .onHover((isHover: boolean) => {
            if (isHover) {
              this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
            } else {
              this.buttonBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
            }
          })
          .onTouch((event) => {
            if (event.type === TouchType.Down) {
              this.buttonBgColor = $r('sys.color.interactive_pressed');
            }
            if (event.type === TouchType.Up) {
              this.buttonBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
            }
          })
          .onKeyEvent((event) => {
            if (event.keyCode === KeyCode.KEYCODE_ENTER || event.keyCode === KeyCode.KEYCODE_SPACE) {
              if (button.action) {
                button.action();
              }
            }
          })
          .onClick((event) => {
            if (button.action) {
              button.action();
            }
          })
          .onAreaChange((oldValue: Area, newValue: Area) => {
            this.buttonStyleWidth = Number(newValue.width);
            this.buttonStyleHeight = Number(newValue.height);
          })
        }
        if (this.buttonFocus) {
          Row()
            .height(BUTTON_HEIGHT)
            .width(this.buttonStyleWidth)
            .hitTestBehavior(HitTestMode.None)
            .border({
              width: BORDER_WIDTH,
              color: this.subHeaderTheme.borderFocusColor
            })
            .borderRadius($r('sys.float.corner_radius_level4'))
        }
      }
      .focusable(true)
    }
    .margin({
      left: $r('sys.float.padding_level1'),
      right: $r('sys.float.padding_level5'),
    })
    .justifyContent(FlexAlign.End)
    .focusable(true)
  }

  @Builder
  TextArrowStyle(textArrow: OperationOption): void {
    Row() {
      Stack() {
        Row() {
          if (textArrow) {
            Text(textArrow.value)
              .secondaryTitleStyles({
                maxLines: SINGLE_LINE_NUM,
                fontWeight: FontWeight.Regular,
                alignment: Alignment.End,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
              })
              .margin({
                right: PADDING_LEVEL_2 + ARROW_ICON_WIDTH,
                top: $r('sys.float.padding_level4'),
                bottom: $r('sys.float.padding_level4'),
              })
              .focusable(true)
          }
        }
        .alignItems(VerticalAlign.Center)
        .borderRadius($r('sys.float.corner_radius_level4'))
        .focusable(true)
        .backgroundColor(this.textArrowBgColor)
        .constraintSize({ minHeight: BUTTON_ZONE_SIZE })
        .onFocus(() => {
          this.textArrowFocus = true;
        })
        .onBlur(() => {
          this.textArrowFocus = false;
        })
        .padding({
          left: $r('sys.float.padding_level2'),
          right: $r('sys.float.padding_level4'),
        })
        .onAreaChange((oldValue: Area, newValue: Area) => {
          this.textArrowStyleWidth = Number(newValue.width);
          this.textArrowStyleHeight = Number(newValue.height);
        })

        Row() {
          Image($r('sys.media.ohos_ic_public_arrow_right'))
            .fillColor(this.subHeaderTheme.iconArrowColor)
            .width(ARROW_ICON_WIDTH)
            .height(ARROW_ICON_HEIGHT)
            .focusable(true)
            .draggable(false)
        }
        .justifyContent(FlexAlign.End)
        .height(this.textArrowStyleHeight)
        .width(this.textArrowStyleWidth)
        .hitTestBehavior(HitTestMode.None)
        .padding({ right: $r('sys.float.padding_level4') })
        .border({
          radius: $r('sys.float.corner_radius_level4'),
          width: $r('sys.float.outline_extra_larger'),
          color: $r('sys.color.interactive_focus'),
        })
        .stateStyles({
          focused: {
            .border({
              radius: $r('sys.float.corner_radius_level4'),
              width: $r('sys.float.outline_extra_larger'),
              color: this.subHeaderTheme.borderFocusColor ,
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
    .onHover((isHover: boolean) => {
      if (isHover) {
        this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
      } else {
        this.textArrowBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
      }
    })
    .onTouch((event) => {
      if (event.type === TouchType.Down) {
        this.textArrowBgColor = $r('sys.color.interactive_pressed');
      }
      if (event.type === TouchType.Up) {
        this.textArrowBgColor = $r('sys.color.ohos_id_color_sub_background_transparent');
      }
    })
    .onKeyEvent((event) => {
      if (event.keyCode === KeyCode.KEYCODE_ENTER || event.keyCode === KeyCode.KEYCODE_SPACE) {
        if (textArrow.action) {
          textArrow.action();
        }
      }
    })
    .onClick((event) => {
      if (textArrow.action) {
        textArrow.action();
      }
    })
    .focusable(true)
    .justifyContent(FlexAlign.End)
    .margin({
      left: $r('sys.float.padding_level4'),
      right: this.contentMargin?.right ?? $r('sys.float.padding_level4'),
    })
  }

  @Builder
  IconGroupStyle(operationItem: Array<OperationOption>): void {
    Row() {
      ForEach(operationItem, (item: OperationOption, index?: number) => {
        if (Util.isResourceType(item.value)) {
          if (index === INDEX_ZERO) {
            SingleIconStyle({
              item: {
                iconOptions: {
                  icon: item.value as Resource,
                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > index ?
                  this.operationSymbolOptions[index] : null,
                },
                action: item.action,
              }
            })
          } else if (index === INDEX_ONE || index === INDEX_TWO) {
            SingleIconStyle({
              item: {
                action: item.action,
                iconOptions: {
                  icon: item.value as Resource,
                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > index ?
                  this.operationSymbolOptions[index] : null,
                },
              }
            })
              .margin({
                left: $r('sys.float.padding_level4'),
              })
          } else {
            // 最大支持3个ICON,此场景不支持
          }
        }
      });
    }
    .justifyContent(FlexAlign.End)
    .focusable(true)
    .margin({
      left: $r('sys.float.padding_level2'),
      right: this.contentMargin?.right ?? $r('sys.float.padding_level6'),
    })
  }

  @Builder
  LoadingProcessStyle(): void {
    Row() {
      LoadingProgress()
        .width(LOADING_SIZE)
        .height(LOADING_SIZE)
        .color($r('sys.color.icon_secondary'))
        .focusable(true)
        .onAppear(() => {
          this.isDuplicateLine = false;
        })
    }
    .focusable(true)
    .justifyContent(FlexAlign.End)
    .padding({
      top: $r('sys.float.padding_level2'),
      bottom: $r('sys.float.padding_level2'),
    })
    .margin({
      left: $r('sys.float.padding_level4'),
      right: this.contentMargin?.right ? this.contentMargin.right : $r('sys.float.margin_right'),
    })
  }

  @Builder
  dummyFunction(): void {
    Row() {
    }.onAppear(() => {
      this.changeFlexAlign(FlexAlign.End);
    });
  }

  aboutToAppear(): void {
    if (this.select) {
      this.selectedIndex = this.select.selected;
      this.selectValue = this.select.value;
    }
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

  build() {
    if (this.item && this.item.iconOptions) {
      Row() {
        this.IconZone();
      }
      .focusable(true)
      .width(SINGLE_ICON_ZONE_SIZE)
      .height(SINGLE_ICON_ZONE_SIZE)
      .margin({
        bottom: $r('sys.float.padding_level2'),
      })
      .justifyContent(FlexAlign.Center)
      .borderRadius($r('sys.float.corner_radius_level4'))
      .backgroundColor(this.bgColor)
      .stateStyles({
        normal: {
          .border({ width: 0 })
          .backgroundColor($r('sys.color.ohos_id_color_sub_background_transparent'))
        },
        focused: {
          .border({
            radius: $r('sys.float.corner_radius_level4'),
            width: BORDER_WIDTH,
            color: this.subHeaderTheme.borderFocusColor,
            style: BorderStyle.Solid,
          })
        },
        pressed: pressedStyle,
        disabled: disabledStyle,
      })
      .onTouch((event) => {
        if (event.type === TouchType.Down) {
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
      .onKeyEvent((event) => {
        if (event.keyCode === KeyCode.KEYCODE_ENTER || event.keyCode === KeyCode.KEYCODE_SPACE) {
          if (this.item?.action) {
            this.item?.action();
          }
        }
      })
      .onClick((event) => {
        if (this.item?.action) {
          this.item?.action();
        }
      })
    }
  }

  @Builder
  IconZone(): void {
    if (this.item && this.item.iconOptions) {
      if (Util.isSymbolResource(this.item.iconOptions.icon)) {
        SymbolGlyph(this.item.iconOptions?.icon)
          .focusable(true)
          .fontSize(this.item.iconOptions?.symbolicIconOption?.fontSize ?? RIGHT_SINGLE_ICON_SIZE)
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
}
