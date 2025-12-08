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
  $r, Row, Text, List, Axis, Area, Flex, Color, Stack, Length, Button, ICurve, Column, Scroll, 
  Canvas, Builder, ForEach, Padding, Resource, ListItem, BarState, Position, FlexWrap, 
  BlendMode, BlurStyle, Alignment, Component, TouchType, FontWeight, ClickEvent, HoverEvent, 
  TouchEvent, Visibility, ButtonType, EdgeEffect, SymbolGlyph, BorderStyle, ResourceStr, 
  ScrollState, EffectScope, VoidCallback, TextOverflow, CommonMethod, BuilderParam, 
  AnimateParam, ButtonOptions, LengthMetrics, FlexDirection, VerticalAlign, BlendApplyType, 
  LocalizedMargin, HorizontalAlign, TransitionEffect, LocalizedPadding, OnScrollCallback, 
  ReplaceSymbolEffect, AccessibilityRoleType, RenderingContextSettings, CanvasRenderingContext2D, 
  VisibleAreaChangeCallback, ClassCastError
} from '@ohos.arkui.component';
import { ObjectLink, Observed, State, PropRef, Watch } from '@ohos.arkui.stateManagement';
import EnvironmentCallback from '@ohos.app.ability.EnvironmentCallback';
import ApplicationContext from 'application.ApplicationContext';
import { UIContext, MeasureUtils ,Context} from "@ohos.arkui.UIContext";
import { Configuration } from '@ohos.app.ability.Configuration';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';
import resourceManager from "@ohos.resourceManager";
import accessibility from '@ohos.accessibility';
import common from "@ohos.app.ability.common";
import { BusinessError } from '@ohos.base';
import curves from '@ohos.curves';
import hilog from '@ohos.hilog';

const TEXT_HOT_AREA_WIDTH: number = 8;
const LIST_ROW_HEIGHT: number = 40;
const ARROW_IMG_SIZE: number = 24;
const MULTI_LINE_PADDING: number = 24;
const BAR_ANIMATION_DURATION: int = 150;
const ARROW_ANIMATION_DURATION: int = 200;
const ANIMATION_DURATION_250: int = 250;
const ANIMATION_DURATION_100: int = 100;
const FILTER_TOP_PADDING: number = 8;
const FILTER_BAR_MARGIN: number = 8;
const SEPARATOR_HEIGHT: number = 16;
const SEPARATOR_WIDTH: number = 1;
const FLOAT_OPACITY: number = 0.95;
const FILTER_FONT_SIZE: number = 12;
const FOCUS_BORDER_WIDTH: number = 2;
const ARROW_SHOW_DELAY: int = 300;
const PERCENT_100: Length = '100%';
const SHARP_CUBIC_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1);
const INTER_POLATING_SPRING = curves.interpolatingSpring(0, 1, 328, 34);
const FRICTION_CUBIC_BEZIER = curves.cubicBezierCurve(0.2, 0, 0.2, 1);
const TRANS_COLOR: string = '#00FFFFFF';
const GRADIENT_WIDTH: number = 16;
const MAX_FONT_SCALE: number = 2;
const ERROR_CODE: int = 0x3900;
const SYMBOL_SIZE: number = 24;
const MAX_SYMBOL_FONT_SCALE: number = 1.45;
const MIN_SYMBOL_FONT_SCALE: number = 1;
const DEFAULT_SYMBOL_FONT_SCALE: number = 1;

export enum FilterType {
  MULTI_LINE_FILTER,
  LIST_FILTER
}

enum FilterAccessibilityType {
  ACCESSIBILITY_TEXT,
  ACCESSIBILITY_DESC,
  SEND_ACCESSIBILITY,
}

export interface FilterParams {
  name: ResourceStr;
  options: Array<ResourceStr>;
}

export interface FilterResult {
  name: ResourceStr;
  index: int;
  value: ResourceStr;
}

type FontWeightArray = Array<FontWeight>;

type ResourceArray = Array<Resource>;

type BooleanArray = Array<boolean>;

@Observed
export class ObservedBoolean {
  public value: boolean;

  constructor(value: boolean) {
    this.value = value;
  }
}

@Observed
class ObservedNumber {
  public value: number;

  constructor(value: number) {
    this.value = value;
  }
}

@Observed
class FilterAccessibilityText {
  public accessibilitySelectedText: string = '';
  public accessibilityExpand: string = '';
  public accessibilityCollapse: string = '';
  public accessibilityExpanded: string = '';
  public accessibilityCollapsed: string = '';
  public accessibilityUnselectedText: string = '';
  public accessibilityFilters: string = '';
  public accessibilitySelectedDesc: string = '';
  public accessibilityUnselectedDesc: string = '';
  public accessibilityExpandDesc: string = '';
}

@Component
struct GradientMask {
  x0: number = 0;
  y0: number = 0;
  x1: number = 0;
  y1: number = 0;
  private settings: RenderingContextSettings = new RenderingContextSettings(true);
  private context2D: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings);

  build() {
    Column() {
      Canvas(this.context2D)
        .width(GRADIENT_WIDTH)
        .height(LIST_ROW_HEIGHT)
        .onReady(() => {
          let grad = this.context2D.createLinearGradient(this.x0, this.y0, this.x1, this.y1)
          grad.addColorStop(0.0, '#ffffffff')
          grad.addColorStop(1, '#00ffffff')
          this.context2D.fillStyle = grad
          this.context2D.fillRect(0, 0, GRADIENT_WIDTH, LIST_ROW_HEIGHT)
        } as VoidCallback)
    }
    .blendMode(BlendMode.DST_OUT, BlendApplyType.FAST)
    .width(GRADIENT_WIDTH)
    .height(LIST_ROW_HEIGHT)
  }
}

@Component
struct ListFilterRow {
  @PropRef colorRow: ResourceArray;
  @PropRef fontWeightRow: FontWeightArray;
  @PropRef backgroundColorRow: ResourceArray;
  @PropRef isBackgroundHoverRow: BooleanArray;
  @PropRef isSelectedRow: BooleanArray;
  @ObjectLink filterAccessibilityText: FilterAccessibilityText;
  filterRow: FilterParams = { name: '', options: [], } as FilterParams;
  onItemClick: (colIndex: number) => void = () => {
  };
  rowIndex: number = 0;
  maxAppFontScale: number = 1;
  isFollowingSystemFontScale: boolean = false;
  bundleName: string = '';
  filterId: number = this.getUniqueId().toDouble();

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxAppFontScale = uiContent.getMaxFontScale();
    } catch (err) {
      let code: number | undefined = (err as ClassCastError).code;
      let message: string | undefined = (err as ClassCastError).message;
      hilog.error(ERROR_CODE, 'Ace',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    if (this.getUIContext().getHostContext()) {
      this.bundleName = ((this.getUIContext().getHostContext()) as common.UIAbilityContext).abilityInfo.bundleName;
    }
  }

  updateFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    let systemFontScale: number = 1;
    if (uiContent.getHostContext()) {
      systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    }
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(systemFontScale, this.maxAppFontScale);
  }

  getAccessibilityText(resource: ResourceStr | undefined, selected: boolean, type: FilterAccessibilityType): string {
    let accessibilityText: string = '';
    try {
      let resourceString: string = '';
      if (resource == undefined) {
        resourceString = '';
      } else if (typeof resource === 'string') {
        resourceString = resource as string;
      } else {
        let uiContent: Context | undefined = UIContext.getFocusedUIContext()?.getHostContext();
        resourceString = (uiContent as common.UIAbilityContext).resourceManager
          .getStringSync((resource as Resource).id) as string;
      }
      switch (type) {
        case FilterAccessibilityType.ACCESSIBILITY_TEXT:
          accessibilityText = selected ? this.filterAccessibilityText.accessibilitySelectedText : resourceString;
          break;
        case FilterAccessibilityType.ACCESSIBILITY_DESC:
          accessibilityText = selected ? resourceString : '';
          break;
        case FilterAccessibilityType.SEND_ACCESSIBILITY:
          accessibilityText =
            selected ? `${this.filterAccessibilityText.accessibilitySelectedText},${resourceString}` : '';
          break;
        default:
          break;
      }
    } catch (error) {
      let code: number | undefined = (error as ClassCastError).code;
      let message: string | undefined = (error as ClassCastError).message;
      hilog.error(0x3900, 'Ace',
        `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
    }
    return accessibilityText;
  }

  sendAccessibility(resource: ResourceStr | undefined, selected: boolean): void {
    let eventInfo: accessibility.EventInfo =
      new accessibility.EventInfo('announceForAccessibility', this.bundleName, 'common');
    eventInfo.textAnnouncedForAccessibility =
      this.getAccessibilityText(resource, selected, FilterAccessibilityType.SEND_ACCESSIBILITY);
    accessibility.sendAccessibilityEvent(eventInfo).then(() => {
      hilog.info(0x3900, 'Ace',
        `ListFilter sendAccessibility send event, event info is ${JSON.stringify(eventInfo)}`);
    })
  }

  build() {
    Stack({ alignContent: Alignment.End }) {
      Stack({ alignContent: Alignment.Start }) {
        List() {
          ForEach(this.filterRow.options as Array<ResourceStr>, (option: ResourceStr, colIndex: int) => {
            if (colIndex === 0) {
              ListItem()
                .width($r('sys.float.ohos_id_max_padding_start'))
                .height(LIST_ROW_HEIGHT)
            }
            ListItem() {
              Text(option)
                .fontSize($r('sys.float.ohos_id_text_size_body3'))
                .minFontScale(1)
                .maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE))
                .fontColor(this.colorRow[colIndex.toInt()])
                .fontWeight(this.fontWeightRow[colIndex.toInt()])
                .focusable(true)
            }
            .accessibilityText(this.getAccessibilityText(option,
              this.isSelectedRow[colIndex.toInt()], FilterAccessibilityType.ACCESSIBILITY_TEXT))
            .accessibilityDescription(this.getAccessibilityText(option,
              this.isSelectedRow[colIndex.toInt()], FilterAccessibilityType.ACCESSIBILITY_DESC))
            .id(`filterListFilterRow_${this.filterId}_${this.rowIndex}`)
            .height(PERCENT_100)
            .onClick((event?: ClickEvent) => {
              this.onItemClick(colIndex as number)
              this.sendAccessibility(option, true);
            })
            .focusable(true)
            .stateStyles({
              focused: (instance: CommonMethod) => {
                instance
                  .border({
                    radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                    width: FOCUS_BORDER_WIDTH,
                    color: $r('sys.color.ohos_id_color_focused_outline'),
                    style: BorderStyle.Solid
                  })
                  .padding({
                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                  } as LocalizedPadding)
              },
              normal: (instance: CommonMethod) => {
                instance
                  .border({
                    radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                    width: 0
                  })
                  .padding({
                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                  } as LocalizedPadding)
              }
            })
            .backgroundColor(this.isBackgroundHoverRow[colIndex.toInt()] ? this.backgroundColorRow[colIndex.toInt()] :
              TRANS_COLOR)
            .onHover((isHover: boolean, event: HoverEvent) => {
              this.getUIContext()?.animateTo({
                curve: FRICTION_CUBIC_BEZIER as ICurve,
                duration: ANIMATION_DURATION_250
              } as AnimateParam, () => {
                if (isHover) {
                  this.backgroundColorRow[colIndex.toInt()] = $r('sys.color.ohos_id_color_hover')
                  this.isBackgroundHoverRow[colIndex.toInt()] = true
                } else {
                  this.isBackgroundHoverRow[colIndex.toInt()] = false
                }
              })
            })
            .onTouch((event?: TouchEvent) => {
              if (event?.type === TouchType.Down) {
                this.getUIContext()?.animateTo({
                  curve: SHARP_CUBIC_BEZIER as ICurve,
                  duration: ANIMATION_DURATION_100
                } as AnimateParam, () => {
                  this.backgroundColorRow[colIndex.toInt()] = $r('sys.color.ohos_id_color_click_effect')
                  this.isBackgroundHoverRow[colIndex.toInt()] = true
                })
              } else if (event?.type === TouchType.Up || event?.type === TouchType.Cancel) {
                this.getUIContext()?.animateTo({
                  curve: SHARP_CUBIC_BEZIER as ICurve,
                  duration: ANIMATION_DURATION_100
                } as AnimateParam, () => {
                  this.isBackgroundHoverRow[colIndex.toInt()] = false
                })
              }
            })
            .margin({ start: LengthMetrics.vp(colIndex === 0 ? -TEXT_HOT_AREA_WIDTH : 0) } as LocalizedMargin)
            .tabIndex(colIndex === 0 ? 1 : -1)
          })
        }
        .listDirection(Axis.Horizontal)
        .scrollBar(BarState.Off)
        .width(PERCENT_100)
        .height(LIST_ROW_HEIGHT)
        .align(Alignment.Start)

        GradientMask({
          x0: 0,
          y0: LIST_ROW_HEIGHT / 2,
          x1: GRADIENT_WIDTH,
          y1: LIST_ROW_HEIGHT / 2
        })
      }

      GradientMask({
        x0: GRADIENT_WIDTH,
        y0: LIST_ROW_HEIGHT / 2,
        x1: 0,
        y1: LIST_ROW_HEIGHT / 2
      })
    }.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN)
  }
}

@Component
struct MultiFilterRow {
  @PropRef colorRow: ResourceArray;
  @PropRef fontWeightRow: FontWeightArray;
  @PropRef backgroundColorRow: ResourceArray;
  @PropRef isBackgroundHoverRow: BooleanArray;
  @ObjectLink twoLineModeItemNumRow: ObservedNumber;
  @ObjectLink twoLineModeItemNumRecordRow: ObservedNumber;
  @ObjectLink arrowShowStateRow: ObservedBoolean;
  @ObjectLink isArrowIconDown: ObservedBoolean;
  @PropRef isSelectedRow: BooleanArray;
  @ObjectLink filterAccessibilityText: FilterAccessibilityText;
  filterRow: FilterParams | null = null;
  onItemClick: (colIndex: number) => void = () => {
  };
  @State arrowBgColorRow: Resource = $r('sys.color.ohos_id_color_hover');
  @State isArrowBgHoverRow: boolean = false;
  @PropRef fontSizeScale: number | undefined;
  @State replaceEffect: int = 0;
  @State isSendArrowAccessibility: boolean = false;
  private filterColumnWidth: number = 0;
  private lastFilterColumnWidth: number = 0;
  private rowIndex: number = 0;
  maxAppFontScale: number = 1;
  isFollowingSystemFontScale: boolean = false;
  bundleName: string = '';
  filterId: number = this.getUniqueId().toDouble();

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxAppFontScale = uiContent.getMaxFontScale();
    } catch (err) {
      let code: number | undefined = (err as ClassCastError).code;
      let message: string | undefined = (err as ClassCastError).message;
      hilog.error(ERROR_CODE, 'Ace',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    if (this.getUIContext().getHostContext()) {
      this.bundleName = ((this.getUIContext().getHostContext()) as common.UIAbilityContext).abilityInfo.bundleName;
    }
  }

  updateFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    let systemFontScale: number = 1;
    if (uiContent.getHostContext()) {
      systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    }
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(systemFontScale, this.maxAppFontScale);
  }

  private calcMultiFilterRowItemNum() {
    let curLineRetainWidth: number = this.filterColumnWidth;
    let curLineSum: number = 0;
    let curLine: number = 1;
    if (this.filterRow) {
      for (let i: number = 0; i < (this.filterRow?.options as Array<ResourceStr>).length; i++) {
        let option = this.filterRow?.options[i.toInt()];
        let measureUtils = this.getUIContext().getMeasureUtils();
        let itemWidth = measureUtils.measureText({
          textContent: option as ResourceStr,
          fontSize: `${FILTER_FONT_SIZE * Math.min(this.updateFontScale(), MAX_FONT_SCALE)}vp`,
        })
        if (i === 0) {
          continue;
        } else {
          itemWidth += this.getUIContext().vp2px(TEXT_HOT_AREA_WIDTH * 2);
        }
        if (curLineRetainWidth - itemWidth >= 0) {
          curLineRetainWidth -= itemWidth;
          curLineSum += 1;
        } else {
          if (curLineSum === 0) {
            curLineSum++;
            curLineRetainWidth = 0;
          }
          if (curLine === 1) {
            curLine += 1;
            curLineRetainWidth =
              this.filterColumnWidth -
              this.getUIContext().vp2px(ARROW_IMG_SIZE * (this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE));
            i--;
          } else {
            break;
          }
        }
      }
    }
    return curLineSum;
  }

  getAccessibilityText(resource: ResourceStr | undefined, selected: boolean, type: FilterAccessibilityType): string {
    let accessibilityText: string = '';
    try {
      let resourceString: string = '';
      if (resource == undefined) {
        resourceString = '';
      } else if (typeof resource === 'string') {
        resourceString = resource as string;
      } else {
        let uiContent: Context | undefined = UIContext.getFocusedUIContext()?.getHostContext();
        resourceString = (uiContent as common.UIAbilityContext).resourceManager
          .getStringSync((resource as Resource).id) as string;
      }
      switch (type) {
        case FilterAccessibilityType.ACCESSIBILITY_TEXT:
          accessibilityText = selected ? this.filterAccessibilityText.accessibilitySelectedText : resourceString;
          break;
        case FilterAccessibilityType.ACCESSIBILITY_DESC:
          accessibilityText = selected ? resourceString : '';
          break;
        case FilterAccessibilityType.SEND_ACCESSIBILITY:
          accessibilityText =
            selected ? `${this.filterAccessibilityText.accessibilitySelectedText},${resourceString}` : '';
          break;
        default:
          break;
      }
    } catch (err) {
      let code: number | undefined = (err as ClassCastError).code;
      let message: string | undefined = (err as ClassCastError).message;
      hilog.error(0x3900, 'Ace',
        `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
    }
    return accessibilityText;
  }

  private sendAccessibility(resource: ResourceStr | undefined, selected: boolean): void {
    let eventInfo: accessibility.EventInfo =
      new accessibility.EventInfo('announceForAccessibility', this.bundleName, 'common')
    eventInfo.textAnnouncedForAccessibility =
      this.getAccessibilityText(resource, selected, FilterAccessibilityType.SEND_ACCESSIBILITY)
    accessibility.sendAccessibilityEvent(eventInfo);
  }

  private sendArrowAccessibility(id: string): void {
    if (this.isSendArrowAccessibility) {
      let eventInfo: accessibility.EventInfo =
        new accessibility.EventInfo('requestFocusForAccessibility', this.bundleName, 'common')
      eventInfo.customId = id
      accessibility.sendAccessibilityEvent(eventInfo)
        .then(() => {
          setTimeout(() => {
            this.isSendArrowAccessibility = false;
          }, 200);
        });
    }
  }

  @Builder
  DownAndUpArrow() {
    Row() {
      Button({ stateEffect: false, type: ButtonType.Normal } as ButtonOptions) {
        SymbolGlyph(this.isArrowIconDown.value ? $r('sys.symbol.chevron_down') : $r('sys.symbol.chevron_up'))
          .fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`)
          .height(LIST_ROW_HEIGHT)
          .fontColor([$r('sys.color.ohos_id_color_tertiary')])
          .symbolEffect(new ReplaceSymbolEffect(EffectScope.WHOLE), this.replaceEffect)
          .focusable(true)
          .draggable(false)
          .stateStyles({
            focused: (instance: CommonMethod) => {
              instance
                .border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: FOCUS_BORDER_WIDTH,
                  color: $r('sys.color.ohos_id_color_focused_outline'),
                  style: BorderStyle.Solid
                })
                .offset({ x: -FOCUS_BORDER_WIDTH } as Position)
            },
            normal: (instance: CommonMethod) => {
              instance
                .border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: 0
                })
                .offset({ x: 0 } as Position)
            }
          })
          .tabIndex(-1)
      }
      .border({
        radius: $r('sys.float.ohos_id_corner_radius_clicked')
      })
      .height(LIST_ROW_HEIGHT)
      .backgroundColor(this.isArrowBgHoverRow ? this.arrowBgColorRow : TRANS_COLOR)
      .focusable(true)
      .accessibilityGroup(true)
      .accessibilityText(this.isSendArrowAccessibility ?
        (this.isArrowIconDown?.value ? this.filterAccessibilityText.accessibilityCollapsed :
          this.filterAccessibilityText.accessibilityExpanded) :
        (this.isArrowIconDown?.value ? this.filterAccessibilityText.accessibilityExpand :
          this.filterAccessibilityText.accessibilityCollapse))
      .accessibilityDescription(this.isSendArrowAccessibility ? ' ' : '')
      .accessibilityRole(this.isSendArrowAccessibility ? AccessibilityRoleType.ROLE_NONE : AccessibilityRoleType.BUTTON)
      .id(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`)
      .visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden)

      .onHover((isHover: boolean, event: HoverEvent) => {
        this.getUIContext()?.animateTo({
          curve: FRICTION_CUBIC_BEZIER as ICurve,
          duration: ANIMATION_DURATION_250
        } as AnimateParam, () => {
          if (isHover) {
            this.arrowBgColorRow = $r('sys.color.ohos_id_color_hover')
            this.isArrowBgHoverRow = true
          } else {
            this.isArrowBgHoverRow = false
          }
        })
      })
      .onTouch((event?: TouchEvent) => {
        if (event?.type === TouchType.Down) {
          this.getUIContext()?.animateTo({
            curve: SHARP_CUBIC_BEZIER as ICurve,
            duration: ANIMATION_DURATION_100
          } as AnimateParam, () => {
            this.arrowBgColorRow = $r('sys.color.ohos_id_color_click_effect')
            this.isArrowBgHoverRow = true
          })
        } else if (event?.type === TouchType.Up || event?.type === TouchType.Cancel) {
          this.getUIContext()?.animateTo({
            curve: SHARP_CUBIC_BEZIER as ICurve,
            duration: ANIMATION_DURATION_100
          } as AnimateParam, () => {
            this.isArrowBgHoverRow = false;
          })
        }
      })
      .onClick((event?: ClickEvent) => {
        this.isSendArrowAccessibility = true;
        this.replaceEffect += 1;
        if (this.isArrowIconDown.value) {
          this.isArrowIconDown.value = false;
          this.arrowShowStateRow.value = false;
          this.getUIContext()?.animateTo({
            curve: INTER_POLATING_SPRING as ICurve,
          } as AnimateParam, () => {
            this.twoLineModeItemNumRow.value = this.filterRow?.options.length.toDouble() as number;
          })

          this.getUIContext()?.animateTo({
            delay: 300,
            duration: ARROW_ANIMATION_DURATION,
            curve: SHARP_CUBIC_BEZIER as ICurve
          } as AnimateParam, () => {
            this.arrowShowStateRow.value = true;
          })
        } else {
          this.isArrowIconDown.value = true;
          this.arrowShowStateRow.value = false;

          this.getUIContext()?.animateTo({
            curve: INTER_POLATING_SPRING as ICurve,
          } as AnimateParam, () => {
            this.twoLineModeItemNumRow.value = this.twoLineModeItemNumRecordRow.value;
          })
          this.getUIContext()?.animateTo({
            delay: ARROW_SHOW_DELAY,
            duration: ARROW_ANIMATION_DURATION,
            curve: SHARP_CUBIC_BEZIER as ICurve
          } as AnimateParam, () => {
            this.arrowShowStateRow.value = true;
          })
        }
        this.sendArrowAccessibility(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`);
      })
    }
    .height(LIST_ROW_HEIGHT)
  }

  build() {
    Flex() {
      if (this.filterRow?.options && (this.filterRow?.options as Array<ResourceStr>).length > 0) {
        Text(this.filterRow?.options[0] as ResourceStr)
          .height(LIST_ROW_HEIGHT)
          .margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) } as LocalizedMargin)
          .fontSize($r('sys.float.ohos_id_text_size_body3'))
          .minFontScale(1)
          .maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE))
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .fontColor(this.colorRow[0])
          .fontWeight(this.fontWeightRow[0])
          .backgroundColor(this.isBackgroundHoverRow[0] ? this.backgroundColorRow[0] :
            TRANS_COLOR)
          .accessibilityText(this.getAccessibilityText(this.filterRow?.options[0],
            this.isSelectedRow[0], FilterAccessibilityType.ACCESSIBILITY_TEXT))
          .accessibilityDescription(this.getAccessibilityText(this.filterRow?.options[0],
            this.isSelectedRow[0], FilterAccessibilityType.ACCESSIBILITY_DESC))
          .onClick((event?: ClickEvent) => {
            this.onItemClick(0);
            this.sendAccessibility(this.filterRow?.options[0], true);
          })
          .id(`filterMultiFilterRow_${this.filterId}_${this.rowIndex}`)
          .focusable(true)
          .onHover((isHover: boolean, event: HoverEvent) => {
            this.getUIContext()?.animateTo({
              curve: FRICTION_CUBIC_BEZIER as ICurve,
              duration: ANIMATION_DURATION_250
            } as AnimateParam, () => {
              if (isHover) {
                this.backgroundColorRow[0] = $r('sys.color.ohos_id_color_hover');
                this.isBackgroundHoverRow[0] = true;
              } else {
                this.isBackgroundHoverRow[0] = false;
              }
            })
          })
          .onTouch((event?: TouchEvent) => {
            if (event?.type === TouchType.Down) {
              this.getUIContext()?.animateTo({
                curve: SHARP_CUBIC_BEZIER as ICurve,
                duration: ANIMATION_DURATION_100
              } as AnimateParam, () => {
                this.backgroundColorRow[0] = $r('sys.color.ohos_id_color_click_effect');
                this.isBackgroundHoverRow[0] = true;
              })
            } else if (event?.type === TouchType.Up || event?.type === TouchType.Cancel) {
              this.getUIContext()?.animateTo({
                curve: SHARP_CUBIC_BEZIER as ICurve,
                duration: ANIMATION_DURATION_100
              } as AnimateParam, () => {
                this.isBackgroundHoverRow[0] = false;
              })
            }
          })
          .stateStyles({
            focused: (instance: CommonMethod) => {
              instance
                .border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: FOCUS_BORDER_WIDTH,
                  color: $r('sys.color.ohos_id_color_focused_outline'),
                  style: BorderStyle.Solid
                })
                .padding({
                  start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                  end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                } as LocalizedPadding)
            },
            normal: (instance: CommonMethod) => {
              instance
                .border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: 0
                })
                .padding({
                  start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                  end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                } as LocalizedPadding)
            }
          })
          .constraintSize({ maxWidth: '50%' })
          .flexShrink(0)
          .tabIndex(1)
      }
      Row() {
        Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
          ForEach((this.filterRow?.options as Array<ResourceStr>)
            .slice(0, this.twoLineModeItemNumRow.value.toInt() + 1),
            (option: ResourceStr, colIndex: int) => {
              if (colIndex > 0) {
                Text(option)
                  .transition(TransitionEffect.OPACITY, (transitionIn: boolean) => {
                  })
                  .fontSize($r('sys.float.ohos_id_text_size_body3'))
                  .minFontScale(1)
                  .maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE))
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .height(LIST_ROW_HEIGHT)
                  .fontColor(this.colorRow[colIndex.toInt()])
                  .fontWeight(this.fontWeightRow[colIndex.toInt()])
                  .accessibilityText(this.getAccessibilityText(option,
                    this.isSelectedRow[colIndex.toInt()], FilterAccessibilityType.ACCESSIBILITY_TEXT))
                  .accessibilityDescription(this.getAccessibilityText(option,
                    this.isSelectedRow[colIndex.toInt()], FilterAccessibilityType.ACCESSIBILITY_DESC))
                  .backgroundColor(this.isBackgroundHoverRow[colIndex.toInt()] ?
                    this.backgroundColorRow[colIndex.toInt()] : TRANS_COLOR)
                  .onClick((event?: ClickEvent) => {
                    this.onItemClick(colIndex as number)
                    this.sendAccessibility(option, true);
                  })
                  .onHover((isHover: boolean, event: HoverEvent) => {
                    this.getUIContext()?.animateTo({
                      curve: FRICTION_CUBIC_BEZIER as ICurve,
                      duration: ANIMATION_DURATION_250
                    } as AnimateParam, () => {
                      if (isHover) {
                        this.backgroundColorRow[colIndex.toInt()] = $r('sys.color.ohos_id_color_hover');
                        this.isBackgroundHoverRow[colIndex.toInt()] = true;
                      } else {
                        this.isBackgroundHoverRow[colIndex.toInt()] = false;
                      }
                    })
                  })
                  .onTouch((event?: TouchEvent) => {
                    if (event?.type === TouchType.Down) {
                      this.getUIContext()?.animateTo({
                        curve: SHARP_CUBIC_BEZIER as ICurve,
                        duration: ANIMATION_DURATION_100
                      } as AnimateParam, () => {
                        this.backgroundColorRow[colIndex.toInt()] = $r('sys.color.ohos_id_color_click_effect')
                        this.isBackgroundHoverRow[colIndex.toInt()] = true
                      })
                    } else if (event?.type === TouchType.Up || event?.type === TouchType.Cancel) {
                      this.getUIContext()?.animateTo({
                        curve: SHARP_CUBIC_BEZIER as ICurve,
                        duration: ANIMATION_DURATION_100
                      } as AnimateParam, () => {
                        this.isBackgroundHoverRow[colIndex.toInt()] = false;
                      })
                    }
                  })
                  .focusable(true)
                  .stateStyles({
                    focused: (instance: CommonMethod) => {
                      instance
                        .border({
                          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                          width: FOCUS_BORDER_WIDTH,
                          color: $r('sys.color.ohos_id_color_focused_outline'),
                          style: BorderStyle.Solid
                        })
                        .padding({
                          start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                          end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                        } as LocalizedPadding)
                    },
                    normal: (instance: CommonMethod) => {
                      instance
                        .border({
                          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                          width: 0
                        })
                        .padding({
                          start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                          end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                        } as LocalizedPadding)
                    }
                  })
                  .tabIndex(-1)
              }
            })
          if (this.arrowShowStateRow.value) {
            this.DownAndUpArrow()
          }
        }
      }.width(PERCENT_100)
      .onAreaChange((_oldValue: Area, newValue: Area) => {
        this.filterColumnWidth = this.getUIContext().vp2px(parseInt(newValue.width.toString(), 0))
        if (this.twoLineModeItemNumRow.value === 0) {
          let curLineSum: number = this.calcMultiFilterRowItemNum();
          this.twoLineModeItemNumRow.value = curLineSum;
          this.twoLineModeItemNumRecordRow.value = curLineSum;
          if (this.filterRow && curLineSum < (this.filterRow?.options as Array<ResourceStr>).length - 1) {
            this.arrowShowStateRow.value = true;
          } else {
            this.arrowShowStateRow.value = false;
          }
        } else if (this.filterColumnWidth !== this.lastFilterColumnWidth) {
          let curLineSum: number = this.calcMultiFilterRowItemNum();
          if (this.filterRow && curLineSum < (this.filterRow?.options as Array<ResourceStr>).length - 1) {
            if (!this.arrowShowStateRow.value || this.isArrowIconDown.value) {
              this.arrowShowStateRow.value = true;
              this.isArrowIconDown.value = true;
              this.twoLineModeItemNumRow.value = curLineSum;
            }
          } else {
            this.arrowShowStateRow.value = false;
            this.isArrowIconDown.value = false;
            this.twoLineModeItemNumRow.value = curLineSum;
          }
          this.twoLineModeItemNumRecordRow.value = curLineSum;
        }
        this.lastFilterColumnWidth = this.filterColumnWidth;
      })

    }.width(PERCENT_100)
    .padding({
      start: LengthMetrics.resource($r('sys.float.ohos_id_max_padding_start')),
      end: LengthMetrics.resource($r('sys.float.ohos_id_max_padding_end'))
    } as LocalizedPadding)
  }
}

class EnvironmentCallbackEntry implements EnvironmentCallback {
  filter: Filter;

  constructor(filter: Filter) {
    this.filter = filter;
  }

  onConfigurationUpdated(config: Configuration) {
    this.filter.fontSizeScale = Math.min(this.filter.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
    this.filter.fontSizeScale = Math.max(this.filter.fontSizeScale as number, MIN_SYMBOL_FONT_SCALE);
    this.filter.initAccessibilityResource()
  }

  onMemoryLevel(level: AbilityConstant.MemoryLevel) {

  }
}

@Component
export struct Filter {
  @BuilderParam container: () => void = this.defaultContentBuilder;
  @PropRef multiFilters: Array<FilterParams> = [] as Array<FilterParams>;
  @PropRef additionFilters: FilterParams | undefined = undefined
  onFilterChanged: ((filterResults: Array<FilterResult>) => void) = () => {
  }
  @PropRef filterType: FilterType = FilterType.LIST_FILTER
  private selectedFilters: Array<FilterResult> | null = null;
  private colorArrNew: ResourceArray = new ResourceArray();
  private fontWeightArrNew: FontWeightArray = new FontWeightArray();
  private backgroundColorArrNew: ResourceArray = new ResourceArray();
  private isBackgroundHoverNew: BooleanArray = new BooleanArray();
  private downArrowShowStateNew: ObservedBoolean = new ObservedBoolean(false);
  private twoLineModeItemNumNew: ObservedNumber = new ObservedNumber(0);
  private isSelectedArrNew: BooleanArray = new BooleanArray();
  private twoLineModeItemNumRecordNew: ObservedNumber = new ObservedNumber(0);
  private isArrowIconDownArrNew: ObservedBoolean = new ObservedBoolean(false);
  @State private colorArr: Array<ResourceArray> | undefined = undefined;
  @State private fontWeightArr: Array<FontWeightArray> | undefined = undefined;
  @State private backgroundColorArr: Array<ResourceArray> | undefined = undefined;
  @State private isBackgroundHover: Array<BooleanArray> | undefined = undefined;
  @State private floatArrowBgColor: Resource | undefined = undefined;
  @State private isFloatArrowBgHover: boolean = false;
  @State private isArrowIconDownArr: Array<ObservedBoolean> | undefined = undefined;
  @State private additionColorArr: Array<Resource> | undefined = undefined;
  @State private additionFontWeightArr: Array<FontWeight> | undefined = undefined;
  @State private additionBackgroundColorArr: Array<Resource> | undefined = undefined;
  @State private isAdditionBackgroundHover: Array<boolean> | undefined = undefined;
  @State private isSelectedArr: Array<BooleanArray> | undefined = undefined;
  @State colorRefresh: boolean = false;
  @State @Watch('updateFocusForAccessibility') isFloatBarShow: boolean = false;
  isFloatBarShowWithoutAnimation: boolean = false;
  @State isFloatShowAllFilter: boolean = false;
  isFloatShowAllFilterWithoutAnimation: boolean = false;
  @State floatFilterPosition: number = 0;
  @State floatFilterBarHeight: number = 0;
  @State floatFilterBarPosition: number = 0;
  filterDynamicHeight: number = 0;
  @State twoLineModeItemNum: Array<ObservedNumber> | undefined = undefined;
  @State twoLineModeItemNumRecord: Array<ObservedNumber> | undefined = undefined;
  @State downArrowShowState: Array<ObservedBoolean> | undefined = undefined;
  @State floatFilterBarText: string = '';
  maxAppFontScale: number = 1;
  isFollowingSystemFontScale: boolean = false;
  @State fontSizeScale: number | undefined = undefined;
  private callbackId: number | undefined = undefined;
  private callbacks: EnvironmentCallbackEntry = new EnvironmentCallbackEntry(this);
  @State additionFiltersSelectedIndex?: number = -1;
  @State floatFilterBarAccessibilityText: string = '';
  @State filterAccessibilityText: FilterAccessibilityText = new FilterAccessibilityText();
  bundleName: string = '';
  private filterId: number = this.getUniqueId().toDouble();
  applicationContext: ApplicationContext = new ApplicationContext();

  @Builder
  defaultContentBuilder(): void {
  }

  textColor(rowIndex: number, colIndex: number) {
    if (this.selectedFilters && (this.selectedFilters as Array<FilterResult>).length > rowIndex &&
      ((this.selectedFilters as Array<FilterResult>)[rowIndex.toInt()].index as number) === colIndex) {
      return $r('sys.color.ohos_id_color_text_primary_activated');
    }
    return $r('sys.color.ohos_id_color_text_primary');
  }

  aboutToAppear() {
    this.initParams();
    this.initAccessibilityResource();
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxAppFontScale = uiContent.getMaxFontScale();
      this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
      this.fontSizeScale = Math.max(this.fontSizeScale as number, MIN_SYMBOL_FONT_SCALE);
      if (uiContent.getHostContext() !== undefined) {
        let hostContext: common.UIAbilityContext = uiContent.getHostContext() as common.UIAbilityContext
        this.applicationContext = hostContext.getApplicationContext();
        this.callbackId = this.applicationContext.onEnvironment(this.callbacks);
      }

    } catch (err) {
      let code: number | undefined = (err as ClassCastError).code;
      let message: string | undefined = (err as ClassCastError).message;
      hilog.error(ERROR_CODE, 'Ace',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
  }

  aboutToDisappear(): void {
    if (this.callbackId) {
      let context: UIContext = this.getUIContext();
      if (context.getHostContext() !== undefined) {
        this.applicationContext.offEnvironment(this.callbackId!.toInt(),
          (err: BusinessError<void> | null): void => {
            hilog.info(0x0000, 'testTag', `applicationContext off environment err: code ${err?.code}`);
          })
      }
      this.callbackId = undefined;
    }
  }

  initAccessibilityResource(): void {
    try {
      if (this.getUIContext().getHostContext()) {
        this.bundleName = ((this.getUIContext().getHostContext()) as common.UIAbilityContext).abilityInfo.bundleName;
      }
      let resourceMan = resourceManager.getSysResourceManager()
      this.filterAccessibilityText.accessibilitySelectedText =
        resourceMan?.getStringByNameSync('filter_accessibility_selected') as string;
      this.filterAccessibilityText.accessibilityUnselectedText =
        resourceMan?.getStringByNameSync('filter_accessibility_unselected') as string;
      this.filterAccessibilityText.accessibilityFilters =
        resourceMan?.getStringByNameSync('filter_accessibility_filters') as string;
      this.filterAccessibilityText.accessibilitySelectedDesc =
        resourceMan?.getStringByNameSync('filter_accessibility_select_desc') as string;
      this.filterAccessibilityText.accessibilityUnselectedDesc =
        resourceMan?.getStringByNameSync('filter_accessibility_unselect_desc') as string;
      this.filterAccessibilityText.accessibilityExpandDesc =
        resourceMan?.getStringByNameSync('filter_accessibility_expand_desc') as string;
      this.filterAccessibilityText.accessibilityExpanded =
        resourceMan?.getStringByNameSync('filter_accessibility_expanded') as string;
      this.filterAccessibilityText.accessibilityCollapsed =
        resourceMan?.getStringByNameSync('filter_accessibility_collapsed') as string;
      this.filterAccessibilityText.accessibilityExpand =
        resourceMan?.getStringByNameSync('filter_accessibility_expand') as string;
      this.filterAccessibilityText.accessibilityCollapse =
        resourceMan?.getStringByNameSync('filter_accessibility_collapse') as string;
    } catch (err) {
      let code: number | undefined = (err as ClassCastError).code;
      let message: string | undefined = (err as ClassCastError).message;
      hilog.error(ERROR_CODE, 'Ace',
        `Filter failed to initAccessibilityResource, code: ${code}, message: ${message}`);
    }
  }

  updateFocusForAccessibility(name: string): void {
    if (this.isFloatBarShow) {
      let eventInfo: accessibility.EventInfo =
        new accessibility.EventInfo('requestFocusForAccessibility', this.bundleName, 'common')
      eventInfo.customId = `FiliterFloatFilterBar_${this.getUniqueId()}`
      accessibility.sendAccessibilityEvent(eventInfo);
    }
  }

  updateFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    let systemFontScale: number = 1;
    if (uiContent.getHostContext()) {
      systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    }
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(systemFontScale, this.maxAppFontScale);
  }

  getAccessibilityText(resource: ResourceStr | undefined, selected: boolean, type: FilterAccessibilityType): string {
    let accessibilityText: string = '';
    try {
      let resourceString: string = '';
      if (resource == undefined) {
        resourceString = '';
      } else if (typeof resource === 'string') {
        resourceString = resource as string;
      } else {
        let uiContent: Context | undefined = UIContext.getFocusedUIContext()?.getHostContext();
        resourceString = (uiContent as common.UIAbilityContext).resourceManager
          .getStringSync((resource as Resource).id) as string;
      }
      switch (type) {
        case FilterAccessibilityType.ACCESSIBILITY_TEXT:
          accessibilityText = selected ? `${this.filterAccessibilityText.accessibilitySelectedText},${resourceString}` :
            resourceString;
          break;
        case FilterAccessibilityType.ACCESSIBILITY_DESC:
          accessibilityText = selected ? this.filterAccessibilityText.accessibilityUnselectedDesc :
            this.filterAccessibilityText.accessibilitySelectedDesc;
          break;
        case FilterAccessibilityType.SEND_ACCESSIBILITY:
          accessibilityText = selected ? `${this.filterAccessibilityText.accessibilitySelectedText},${resourceString}` :
            `${this.filterAccessibilityText.accessibilityUnselectedText},${resourceString}`;
          break;
        default:
          break;
      }
    } catch (error) {
      let code: number | undefined = (error as ClassCastError).code;
      let message: string | undefined = (error as ClassCastError).message;
      hilog.error(0x3900, 'Ace',
        `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
    }
    return accessibilityText;
  }

  private sendAccessibility(resource: ResourceStr | undefined, selected: boolean): void {
    let eventInfo: accessibility.EventInfo =
      new accessibility.EventInfo('announceForAccessibility', this.bundleName, 'common')
    eventInfo.textAnnouncedForAccessibility =
      this.getAccessibilityText(resource, selected, FilterAccessibilityType.SEND_ACCESSIBILITY)
    accessibility.sendAccessibilityEvent(eventInfo).then(() => {
      hilog.info(0x3900, 'Ace',
        `ListFilter sendAccessibility send event, event info is ${JSON.stringify(eventInfo)}`);
    })
  }

  private filterItemClick(rowIndex: number, colIndex: number): void {
    let selectedFilterValue = (this.multiFilters as Array<FilterParams>)[rowIndex.toInt()].options[colIndex.toInt()];
    if (this.selectedFilters && colIndex !== (this.selectedFilters as Array<FilterResult>)[rowIndex.toInt()].index) {
      if (this.colorArr) {
        ((this.colorArr as Array<ResourceArray>)[rowIndex.toInt()] as ResourceArray)[colIndex.toInt()] =
          $r('sys.color.ohos_id_color_text_primary_activated');
        ((this.colorArr as Array<ResourceArray>)[rowIndex.toInt()] as ResourceArray)
        [((this.selectedFilters as Array<FilterResult>)[rowIndex.toInt()].index.toInt())] =
          $r('sys.color.ohos_id_color_text_primary');
      }
      if (this.fontWeightArr) {
        (this.fontWeightArr as Array<FontWeightArray>)[rowIndex.toInt()][colIndex.toInt()] =
          FontWeight.Medium as FontWeight;
        (this.fontWeightArr as Array<FontWeightArray>)[rowIndex.toInt()]
        [(this.selectedFilters as Array<FilterResult>)[rowIndex.toInt()].index.toInt()] = FontWeight.Regular;
      }
      if (this.isSelectedArr) {
        (this.isSelectedArr as Array<BooleanArray>)[rowIndex.toInt()][colIndex.toInt()] = true;
        (this.isSelectedArr as Array<BooleanArray>)[rowIndex.toInt()]
        [(this.selectedFilters as Array<FilterResult>)[rowIndex.toInt()].index.toInt()] = false;
      }
      this.colorRefresh = (!this.colorRefresh) as boolean;
      (this.selectedFilters as Array<FilterResult>)[rowIndex.toInt()].value = selectedFilterValue as ResourceStr;
      (this.selectedFilters as Array<FilterResult>)[rowIndex.toInt()].index = colIndex.toInt();
      let filterChanged: ((filterResults: Array<FilterResult>) => void) | null = this.onFilterChanged;
      if (filterChanged) {
        filterChanged(this.selectedFilters as Array<FilterResult>);
      }
    }
    this.refreshFloatFilterBarText();
  }

  private refreshFloatFilterBarText(): void {
    this.floatFilterBarText = '';
    this.floatFilterBarAccessibilityText = '';
    if (this.selectedFilters) {
      const selectedValueFilters = this.selectedFilters?.filter(item => item?.value !== undefined)
        .map((item: FilterResult): ResourceStr => {
          if (typeof item.value !== 'string') {
            let uiContent: Context | undefined = UIContext.getFocusedUIContext()?.getHostContext();
            return (uiContent as common.UIAbilityContext).resourceManager
              .getStringSync((item.value as Resource).id as Long)
          } else {
            return item.value;
          }
        });
      this.floatFilterBarText = selectedValueFilters?.join('/') as string;
      this.floatFilterBarAccessibilityText = selectedValueFilters?.join(' ') as string;
    }
  }

  private getFloatAccessibilityText(resource: ResourceStr | undefined, type: FilterAccessibilityType): string {
    let accessibilityText: string = '';
    let accessibilityFilters: string = this.filterAccessibilityText.accessibilityFilters;
    let accessibilityCollapsed: string = this.filterAccessibilityText.accessibilityCollapsed;
    try {
      let resourceString: string = '';
      if (typeof resource === 'string') {
        resourceString = resource as string;
      } else {
        let uiContent: Context | undefined = UIContext.getFocusedUIContext()?.getHostContext();
        resourceString = (uiContent as common.UIAbilityContext).resourceManager.
        getStringSync((resource as Resource).id as Long)
      }
      switch (type) {
        case FilterAccessibilityType.ACCESSIBILITY_TEXT:
          accessibilityText =
            `${accessibilityFilters},${accessibilityCollapsed},${resourceString}`;
          break;
        case FilterAccessibilityType.ACCESSIBILITY_DESC:
          accessibilityText = this.filterAccessibilityText.accessibilityExpandDesc;
          break;
        case FilterAccessibilityType.SEND_ACCESSIBILITY:
          accessibilityText = this.filterAccessibilityText.accessibilityExpanded;
          break;
        default:
          break;
      }
    } catch (error) {
      let code: number | undefined = (error as ClassCastError).code;
      let message: string | undefined = (error as ClassCastError).message;
      hilog.error(0x3900, 'Ace',
        `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
    }
    return accessibilityText;
  }

  private sendFloatAccessibility(resource: ResourceStr | undefined): void {
    let eventInfo: accessibility.EventInfo =
      new accessibility.EventInfo('announceForAccessibility', this.bundleName, 'common')
    eventInfo.textAnnouncedForAccessibility =
      this.getFloatAccessibilityText(resource, FilterAccessibilityType.SEND_ACCESSIBILITY)
    accessibility.sendAccessibilityEvent(eventInfo);
    if (this.multiFilters && (this.multiFilters as Array<FilterParams>).length > 0) {
      if (this.filterType === FilterType.LIST_FILTER) {
        let requestFocusEventInfo: accessibility.EventInfo =
          new accessibility.EventInfo('requestFocusForAccessibility', this.bundleName, 'common')
        eventInfo.customId = `filterListFilterRow_${this.filterId}_0`
        accessibility.sendAccessibilityEvent(requestFocusEventInfo);
      } else if (this.filterType === FilterType.MULTI_LINE_FILTER) {
        let requestFocusEventInfo: accessibility.EventInfo =
          new accessibility.EventInfo('requestFocusForAccessibility', this.bundleName, 'common')
        eventInfo.customId = `filterMultiFilterRow_${this.filterId}_0`
        accessibility.sendAccessibilityEvent(requestFocusEventInfo);
      }
    } else if (this.additionFilters && this.additionFilters?.name) {
      let requestFocusEventInfo: accessibility.EventInfo =
        new accessibility.EventInfo('requestFocusForAccessibility', this.bundleName, 'common')
      eventInfo.customId = `filterAdditionFiltersName_${this.filterId}`
      accessibility.sendAccessibilityEvent(requestFocusEventInfo);
    }
  }

  private initParams(): void {
    if (!this.selectedFilters) {
      this.selectedFilters = [];
      for (let filter of (this.multiFilters as Array<FilterParams>)) {
        let result: FilterResult = { name: filter.name, index: -1, value: '' } as FilterResult;
        if (filter.options.length > 0) {
          result.index = 0;
          result.value = filter.options[0];
        }
        this.selectedFilters?.push(result);
      }
      if (this.additionFilters && this.additionFilters?.name) {
        let result: FilterResult =
          { name: this.additionFilters?.name as ResourceStr, index: -1, value: '' } as FilterResult;
        this.selectedFilters?.push(result);
      }
      this.refreshFloatFilterBarText();
    }
    if (!this.colorArr) {
      this.colorArr = [];
      this.backgroundColorArr = [];
      this.isBackgroundHover = [];
      this.fontWeightArr = [];
      this.isArrowIconDownArr = [];
      this.isSelectedArr = [];
      this.floatArrowBgColor = $r('sys.color.ohos_id_color_background');
      for (let filter of (this.multiFilters as Array<FilterParams>)) {
        let colorRow = new ResourceArray();
        let fontWeightRow = new FontWeightArray();
        let backgroundColorRow = new ResourceArray();
        let isBackgroundHoverRow = new BooleanArray();
        let isSelectedRow = new BooleanArray();
        for (let index of filter.options.keys()) {
          if (index === 0) {
            colorRow.push($r('sys.color.ohos_id_color_text_primary_activated'));
            fontWeightRow.push(FontWeight.Medium);
            isSelectedRow.push(true);
          } else {
            colorRow.push($r('sys.color.ohos_id_color_text_primary'));
            fontWeightRow.push(FontWeight.Regular);
            isSelectedRow.push(false);
          }
          backgroundColorRow.push($r('sys.color.ohos_id_color_hover'));
          isBackgroundHoverRow.push(false);
        }
        this.colorArr?.push(colorRow);
        this.fontWeightArr?.push(fontWeightRow);
        this.backgroundColorArr?.push(backgroundColorRow);
        this.isBackgroundHover?.push(isBackgroundHoverRow);
        this.isArrowIconDownArr?.push(new ObservedBoolean(true));
        this.isSelectedArr?.push(isSelectedRow);
      }
    }
    if (this.additionFilters && this.additionFilters?.options) {
      this.additionColorArr = [];
      this.additionFontWeightArr = [];
      this.additionBackgroundColorArr = [];
      this.isAdditionBackgroundHover = [];
      for (let i: number = 0; i < (this.additionFilters?.options as Array<ResourceStr>).length; i++) {
        this.additionColorArr?.push($r('sys.color.ohos_id_color_text_primary'));
        this.additionFontWeightArr?.push(FontWeight.Regular);
        this.additionBackgroundColorArr?.push($r('sys.color.ohos_id_color_hover'));
        this.isAdditionBackgroundHover?.push(false);
      }
    }
    if (!this.twoLineModeItemNum) {
      this.twoLineModeItemNum = [];
      this.twoLineModeItemNumRecord = [];
      this.downArrowShowState = [];

      for (let filter of (this.multiFilters as Array<FilterParams>)) {
        let optionsLength: number = filter.options.length;
        this.twoLineModeItemNum?.push(new ObservedNumber(optionsLength));
        this.twoLineModeItemNumRecord?.push(new ObservedNumber(optionsLength));
        this.downArrowShowState?.push(new ObservedBoolean(false));
      }
    }
  }

  @Builder
  ListFilter() {
    Column() {
      ForEach((this.multiFilters as Array<FilterParams>), (filter: FilterParams, rowIndex: int) => {
        ListFilterRow({
          colorRow: this.colorArr ? (this.colorArr as Array<ResourceArray>)[rowIndex.toInt()] : this.colorArrNew,
          fontWeightRow: this.fontWeightArr ?
            (this.fontWeightArr as Array<FontWeightArray>)[rowIndex.toInt()] : this.fontWeightArrNew,
          backgroundColorRow: this.backgroundColorArr ?
            (this.backgroundColorArr as Array<ResourceArray>)[rowIndex.toInt()] : this.backgroundColorArrNew,
          isBackgroundHoverRow: this.isBackgroundHover ?
            (this.isBackgroundHover as Array<BooleanArray>)[rowIndex.toInt()] : this.isBackgroundHoverNew,
          isSelectedRow: this.isSelectedArr ?
            (this.isSelectedArr as Array<BooleanArray>)[rowIndex.toInt()] : this.isSelectedArrNew,
          filterRow: filter,
          onItemClick: (colIndex: number) => {
            this.filterItemClick(rowIndex as number, colIndex);
          },
          rowIndex: rowIndex as number,
          filterAccessibilityText: this.filterAccessibilityText
        })
      },(filter: FilterParams)=>{return filter.name.toString()})
    }.width(PERCENT_100)
    .align(Alignment.Start)
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
        if (this.additionFilters !== null) {
          this.filterDynamicHeight =
            parseInt(newValue.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
        } else {
          this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + FILTER_TOP_PADDING;
        }
        this.floatFilterPosition = -this.filterDynamicHeight;
      }
    })
  }

  @Builder
  MultiLineFilter() {
    Column() {
      ForEach((this.multiFilters as Array<FilterParams>), (filterItem: FilterParams, rowIndex: int) => {
        MultiFilterRow({
          colorRow: this.colorArr ?
            (this.colorArr as Array<ResourceArray>)[rowIndex.toInt()] : this.colorArrNew,
          fontWeightRow: this.fontWeightArr ?
            (this.fontWeightArr as Array<FontWeightArray>)[rowIndex.toInt()] : this.fontWeightArrNew,
          backgroundColorRow: this.backgroundColorArr ?
            (this.backgroundColorArr as Array<ResourceArray>)[rowIndex.toInt()] : this.backgroundColorArrNew,
          isBackgroundHoverRow: this.isBackgroundHover ?
            (this.isBackgroundHover as Array<BooleanArray>)[rowIndex.toInt()] : this.isBackgroundHoverNew,
          arrowShowStateRow: this.downArrowShowState ?
            (this.downArrowShowState as Array<ObservedBoolean>)[rowIndex.toInt()] : this.downArrowShowStateNew,
          twoLineModeItemNumRow: this.twoLineModeItemNum ?
            (this.twoLineModeItemNum as Array<ObservedNumber>)[rowIndex.toInt()] : this.twoLineModeItemNumNew,
          isSelectedRow: this.isSelectedArr ?
            (this.isSelectedArr as Array<BooleanArray>)[rowIndex.toInt()] : this.isSelectedArrNew,
          twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ?
            (this.twoLineModeItemNumRecord as Array<ObservedNumber>)[rowIndex.toInt()] :
            this.twoLineModeItemNumRecordNew,
          isArrowIconDown: this.isArrowIconDownArr ?
            (this.isArrowIconDownArr as Array<ObservedBoolean>)[rowIndex.toInt()] : this.isArrowIconDownArrNew,
          filterRow: filterItem,
          onItemClick: (colIndex: number) => {
            this.filterItemClick(rowIndex as number, colIndex);
          },
          rowIndex: rowIndex as number,
          fontSizeScale: this.fontSizeScale,
          filterId: this.filterId,
          filterAccessibilityText: this.filterAccessibilityText
        })
      },(filterItem: FilterParams)=>{return filterItem.name.toString()})
    }.width(PERCENT_100)
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      if (this.additionFilters !== null) {
        this.filterDynamicHeight =
          parseInt(newValue.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING
      } else {
        this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + FILTER_TOP_PADDING
      }
      if (!this.isFloatBarShowWithoutAnimation && !this.isFloatShowAllFilterWithoutAnimation) {
        this.floatFilterPosition = -this.filterDynamicHeight
      }
    })
  }

  private additionItemClick(index: number): void {
    let additionRowIndex: number = (this.multiFilters as Array<FilterParams>).length
    if (this.selectedFilters &&
      (this.selectedFilters as Array<FilterResult>)[additionRowIndex.toInt()].index !== index) {
      this.additionColorArr &&
        ((this.additionColorArr as Array<Resource>)[index.toInt()] =
          $r('sys.color.ohos_id_color_text_primary_activated'));
      this.additionFontWeightArr &&
        ((this.additionFontWeightArr as Array<FontWeight>)[index.toInt()] = FontWeight.Medium);
      if ((this.selectedFilters as Array<FilterResult>)[additionRowIndex.toInt()].index === -1) {
        (this.selectedFilters as Array<FilterResult>)[additionRowIndex.toInt()].value =
          this.additionFilters ? this.additionFilters?.options[index.toInt()] as ResourceStr : '' as ResourceStr;
        (this.selectedFilters as Array<FilterResult>)[additionRowIndex.toInt()].index = index.toInt();
        this.additionFiltersSelectedIndex = index;
      } else {
        let lastIndex: number = (this.selectedFilters as Array<FilterResult>)[additionRowIndex.toInt()].index;
        this.additionColorArr && ((this.additionColorArr as Array<Resource>)[lastIndex.toInt()] =
          $r('sys.color.ohos_id_color_text_primary'));
        this.additionFontWeightArr &&
          ((this.additionFontWeightArr as Array<FontWeight>)[lastIndex.toInt()] = FontWeight.Regular);
        this.selectedFilters &&
          ((this.selectedFilters as Array<FilterResult>)[additionRowIndex.toInt()].value = this.additionFilters ?
            this.additionFilters?.options[index.toInt()] as ResourceStr : '');
        this.selectedFilters &&
          ((this.selectedFilters as Array<FilterResult>)[additionRowIndex.toInt()].index = index.toInt());
        this.additionFiltersSelectedIndex = index;
      }
    } else {
      this.additionColorArr &&
        ((this.additionColorArr as Array<Resource>)[index.toInt()] = $r('sys.color.ohos_id_color_text_primary'));
      this.additionFontWeightArr &&
        ((this.additionFontWeightArr as Array<FontWeight>)[index.toInt()] = FontWeight.Regular);
      this.selectedFilters && ((this.selectedFilters as Array<FilterResult>)[additionRowIndex.toInt()].value = '');
      this.selectedFilters && ((this.selectedFilters as Array<FilterResult>)[additionRowIndex.toInt()].index = -1);
      this.additionFiltersSelectedIndex = -1;
    }
    if (this.selectedFilters) {
      if (this.onFilterChanged) {
        (this.onFilterChanged as
        ((filterResults: Array<FilterResult>) => void))(this.selectedFilters as Array<FilterResult>);
      }
    }
    this.colorRefresh = !this.colorRefresh;
    this.refreshFloatFilterBarText();
  }

  private getSelected(index: number): boolean {
    let additionRowIndex: number = (this.multiFilters as Array<FilterParams>).length;
    if (this.selectedFilters &&
      (this.selectedFilters as Array<FilterResult>)[additionRowIndex.toInt()].index !== index) {
      return false;
    } else {
      return true;
    }
  }

  @Builder
  AdditionFilterList() {
    if (this.additionFilters && this.additionFilters?.name && this.additionFilters?.options &&
      this.additionFilters?.options.length !== 0) {
      Stack({ alignContent: Alignment.End }) {
        Stack({ alignContent: Alignment.Start }) {
          List() {
            ListItem() {
              Row() {
                Text(this.additionFilters?.name)
                  .fontSize($r('sys.float.ohos_id_text_size_body3'))
                  .minFontScale(1)
                  .maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE))
                  .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                  .margin({
                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                  } as LocalizedMargin)
                  .padding({
                    start: LengthMetrics.resource($r('sys.float.ohos_id_max_padding_start'))
                  } as LocalizedPadding)
                  .id(`filterAdditionFiltersName_${this.filterId}`)
                Row()
                  .width(SEPARATOR_WIDTH)
                  .height(SEPARATOR_HEIGHT)
                  .backgroundColor($r('sys.color.ohos_id_color_list_separator'))
              }
            }.height(PERCENT_100)
            .margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) } as LocalizedMargin)

            ForEach(this.additionFilters?.options as Array<ResourceStr>, (option: ResourceStr, index: int) => {
              ListItem() {
                Text(option)
                  .fontSize($r('sys.float.ohos_id_text_size_body3'))
                  .minFontScale(1)
                  .maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE))
                  .fontColor(this.additionColorArr ? (this.additionColorArr as Array<Resource>)[index.toInt()] :
                    '#e6182431')
                  .fontWeight(this.additionFontWeightArr ?
                    (this.additionFontWeightArr as Array<FontWeight>)[index.toInt()] : FontWeight.Normal)
                  .focusable(true)
              }
              .accessibilityText(this.getAccessibilityText(option,
                this.additionFiltersSelectedIndex === index, FilterAccessibilityType.ACCESSIBILITY_TEXT))
              .accessibilityDescription(this.getAccessibilityText(option,
                this.additionFiltersSelectedIndex === index, FilterAccessibilityType.ACCESSIBILITY_DESC))
              .height(PERCENT_100)
              .backgroundColor(this.isAdditionBackgroundHover &&
              (this.isAdditionBackgroundHover as Array<boolean>)[index.toInt()] ?
                this.additionBackgroundColorArr ? (this.additionBackgroundColorArr as Array<Resource>)[index.toInt()] :
                  '' : TRANS_COLOR)
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.getUIContext()?.animateTo({
                  curve: FRICTION_CUBIC_BEZIER as ICurve,
                  duration: ANIMATION_DURATION_250
                } as AnimateParam, () => {
                  if (isHover) {
                    this.additionBackgroundColorArr &&
                      ((this.additionBackgroundColorArr as Array<Resource>)[index.toInt()] =
                        $r('sys.color.ohos_id_color_hover'));
                    this.isAdditionBackgroundHover &&
                      ((this.isAdditionBackgroundHover as Array<boolean>)[index.toInt()] = true);
                  } else {
                    this.isAdditionBackgroundHover &&
                      ((this.isAdditionBackgroundHover as Array<boolean>)[index.toInt()] = false);
                  }
                })
              })
              .onTouch((event?: TouchEvent) => {
                if (event?.type === TouchType.Down) {
                  this.getUIContext()?.animateTo({
                    curve: SHARP_CUBIC_BEZIER as ICurve,
                    duration: ANIMATION_DURATION_100
                  } as AnimateParam, () => {
                    this.additionBackgroundColorArr &&
                      ((this.additionBackgroundColorArr as Array<Resource>)[index.toInt()] =
                        $r('sys.color.ohos_id_color_click_effect'));
                    this.isAdditionBackgroundHover &&
                      ((this.isAdditionBackgroundHover as Array<boolean>)[index.toInt()] = true);
                  })
                } else if (event?.type === TouchType.Up || event?.type === TouchType.Cancel) {
                  this.getUIContext()?.animateTo({
                    curve: SHARP_CUBIC_BEZIER as ICurve,
                    duration: ANIMATION_DURATION_100
                  } as AnimateParam, () => {
                    this.isAdditionBackgroundHover &&
                      ((this.isAdditionBackgroundHover as Array<boolean>)[index.toInt()] = false);
                  })
                }
              })
              .focusable(true)
              .stateStyles({
                focused: (instance: CommonMethod) => {
                  instance
                    .border({
                      radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                      width: FOCUS_BORDER_WIDTH,
                      color: $r('sys.color.ohos_id_color_focused_outline'),
                      style: BorderStyle.Solid
                    })
                    .padding({
                      start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                      end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                    } as LocalizedPadding)
                },
                normal: (instance: CommonMethod) => {
                  instance
                    .border({
                      radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                      width: 0
                    })
                    .padding({
                      start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                      end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                    } as LocalizedPadding)
                }
              })
              .onClick((event?: ClickEvent) => {
                this.additionItemClick(index as number)
                this.sendAccessibility(option, this.getSelected(index as number));
              })
              .tabIndex(index === 0 ? 1 : -1)
            })
          }
          .listDirection(Axis.Horizontal)
          .scrollBar(BarState.Off)
          .width(PERCENT_100)
          .height(LIST_ROW_HEIGHT)

          GradientMask({
            x0: 0,
            y0: LIST_ROW_HEIGHT / 2,
            x1: GRADIENT_WIDTH,
            y1: LIST_ROW_HEIGHT / 2
          })
        }

        GradientMask({
          x0: GRADIENT_WIDTH,
          y0: LIST_ROW_HEIGHT / 2,
          x1: 0,
          y1: LIST_ROW_HEIGHT / 2
        })
      }
      .blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN)
    }
  }

  @Builder
  FilterHeader() {
    Column() {
      if (this.filterType === FilterType.LIST_FILTER) {
        this.ListFilter()
      } else {
        this.MultiLineFilter()
      }
      this.AdditionFilterList()
    }.padding({ top: FILTER_TOP_PADDING } as Padding)

    .onVisibleAreaChange([0.0, 1.0], (_isVisible: boolean, currentRatio: number) => {
      if (currentRatio > 0) {
        this.isFloatShowAllFilter = false;
        this.isFloatShowAllFilterWithoutAnimation = false;
        this.isFloatBarShowWithoutAnimation = false;
        this.getUIContext()?.animateTo({
          curve: INTER_POLATING_SPRING as ICurve,
          onFinish: () => {
            if (!this.isFloatBarShowWithoutAnimation) {
              this.isFloatBarShow = false;
            }
          }
        } as AnimateParam, () => {
          this.floatFilterBarHeight = 0;
        })
      } else {
        this.isFloatBarShow = true;
        this.isFloatBarShowWithoutAnimation = true;
        this.getUIContext()?.animateTo({
          curve: INTER_POLATING_SPRING as ICurve
        } as AnimateParam, () => {
          this.floatFilterBarPosition = 0;
          this.floatFilterBarHeight = LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
        })
      }
    } as VisibleAreaChangeCallback)
  }

  @Builder
  FloatFilterHeader() {
    Column() {
      Scroll() {
        Column() {
          if (this.filterType === FilterType.LIST_FILTER) {
            this.ListFilter();
          } else {
            this.MultiLineFilter();
          }
          this.AdditionFilterList();
        }
      }
    }
    .padding({ top: FILTER_TOP_PADDING } as Padding)
    .width(PERCENT_100)
    .constraintSize({ maxHeight: '80%' })
    .clip(true)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .opacity(FLOAT_OPACITY)
    .backgroundBlurStyle(BlurStyle.Thin, undefined, { disableSystemAdaptation: true })
    .visibility(this.isFloatShowAllFilter ? Visibility.Visible : Visibility.Hidden)
    .position({ x: 0, y: this.floatFilterPosition } as Position)
    .zIndex(2)
  }

  @Builder
  FloatFilterBar() {
    Row() {
      Column() {
        Row() {
          Row() {
            Text(this.floatFilterBarText)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .fontColor($r('sys.color.ohos_id_color_text_primary_activated'))
              .fontSize($r('sys.float.ohos_id_text_size_body3'))
              .minFontScale(1)
              .maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE))
              .constraintSize({ maxWidth: '85%' })
              .maxLines(1)

            SymbolGlyph($r('sys.symbol.chevron_down'))
              .fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`)
              .fontColor([$r('sys.color.ohos_id_color_text_primary_activated')])
              .focusable(true)
              .draggable(false)
          }
          .height(LIST_ROW_HEIGHT)
          .margin({ start: LengthMetrics.vp(FILTER_BAR_MARGIN) } as LocalizedMargin)
          .focusable(true)
        }.height(PERCENT_100)
        .alignItems(VerticalAlign.Center)
      }
      .id(`FiliterFloatFilterBar_${this.getUniqueId()}`)
      .accessibilityText(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText,
        FilterAccessibilityType.ACCESSIBILITY_TEXT))
      .accessibilityDescription(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText,
        FilterAccessibilityType.ACCESSIBILITY_DESC))
      .backgroundColor(this.isFloatArrowBgHover ? this.floatArrowBgColor as undefined | Color | number | ResourceStr :
        TRANS_COLOR)
      .stateStyles({
        focused: (instance: CommonMethod) => {
          instance.border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: FOCUS_BORDER_WIDTH,
            color: $r('sys.color.ohos_id_color_focused_outline'),
            style: BorderStyle.Solid
          })
        },
        normal: (instance: CommonMethod) => {
          instance.border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: 0
          })
        }
      })
      .alignItems(HorizontalAlign.Center)
      .width(PERCENT_100)
      .height(LIST_ROW_HEIGHT)

      .onTouch((event?: TouchEvent) => {
        if (event?.type === TouchType.Down) {
          this.getUIContext()?.animateTo({
            curve: SHARP_CUBIC_BEZIER as ICurve,
            duration: ANIMATION_DURATION_100
          } as AnimateParam, () => {
            this.floatArrowBgColor = $r('sys.color.ohos_id_color_click_effect');
            this.isFloatArrowBgHover = true;
          })
        } else if (event?.type === TouchType.Up || event?.type === TouchType.Cancel) {
          this.getUIContext()?.animateTo({
            curve: SHARP_CUBIC_BEZIER as ICurve,
            duration: ANIMATION_DURATION_100
          } as AnimateParam, () => {
            this.isFloatArrowBgHover = false;
          })
        }
      })
      .onClick((event?: ClickEvent) => {
        this.getUIContext()?.animateTo({
          duration: BAR_ANIMATION_DURATION,
          curve: SHARP_CUBIC_BEZIER as ICurve
        } as AnimateParam, () => {
          this.isFloatBarShow = false;
          this.isFloatBarShowWithoutAnimation = false;
        })
        this.isFloatShowAllFilter = true
        this.isFloatShowAllFilterWithoutAnimation = true
        this.getUIContext()?.animateTo({
          curve: INTER_POLATING_SPRING as ICurve,
          onFinish: () => {
            this.floatFilterBarPosition = 0
          }
        } as AnimateParam, () => {
          this.floatFilterPosition = 0;
          this.floatFilterBarPosition = this.filterDynamicHeight;
        })
        this.sendFloatAccessibility(this.floatFilterBarAccessibilityText);
      })
      .onHover((isHover: boolean, event: HoverEvent) => {
        if (isHover) {
          this.getUIContext()?.animateTo({
            curve: FRICTION_CUBIC_BEZIER as ICurve,
            duration: ANIMATION_DURATION_250
          } as AnimateParam, () => {
            this.floatArrowBgColor = $r('sys.color.ohos_id_color_hover');
            this.isFloatArrowBgHover = true;
          })
        } else {
          this.getUIContext()?.animateTo({
            curve: FRICTION_CUBIC_BEZIER as ICurve,
            duration: ANIMATION_DURATION_250
          } as AnimateParam, () => {
            this.isFloatArrowBgHover = false;
          })
        }
      })
    }
    .width(PERCENT_100)
    .height(this.floatFilterBarHeight)
    .padding({
      start: LengthMetrics.vp(FOCUS_BORDER_WIDTH),
      end: LengthMetrics.vp(FOCUS_BORDER_WIDTH)
    } as LocalizedPadding)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .opacity(FLOAT_OPACITY)
    .clip(true)
    .backgroundBlurStyle(BlurStyle.Thin, undefined, { disableSystemAdaptation: true })
    .visibility(this.isFloatBarShow ? Visibility.Visible : Visibility.Hidden)
    .alignItems(VerticalAlign.Bottom)
    .position({ x: 0, y: this.floatFilterBarPosition } as Position)
    .zIndex(1)
  }

  build() {
    Stack({ alignContent: Alignment.Top }) {
      this.FloatFilterBar();
      this.FloatFilterHeader();
      Column() {
        List({ initialIndex: 0 }) {
          ListItem() {
            this.FilterHeader()
          }.focusable(true)
          ListItem() {
            this.container()
          }.focusable(true)
        }
        .listDirection(Axis.Vertical)
        .width(PERCENT_100)
        .height(PERCENT_100)
        .edgeEffect(EdgeEffect.Spring)

        .onDidScroll((scrollOffset: number, scrollState: ScrollState) => {
          if (this.isFloatShowAllFilterWithoutAnimation && scrollState === ScrollState.Scroll) {
            this.isFloatBarShowWithoutAnimation = true
            this.isFloatShowAllFilterWithoutAnimation = false
            this.getUIContext()?.animateTo({
              duration: BAR_ANIMATION_DURATION,
              curve: SHARP_CUBIC_BEZIER as ICurve
            } as AnimateParam, () => {
              this.isFloatBarShow = true;
            })

            this.getUIContext()?.animateTo({
              curve: INTER_POLATING_SPRING as ICurve,
              onFinish: () => {
                if (!this.isFloatShowAllFilterWithoutAnimation) {
                  this.isFloatShowAllFilter = false;
                }
              }
            } as AnimateParam, () => {
              this.floatFilterPosition = -this.filterDynamicHeight;
              this.floatFilterBarPosition = 0;
            })
          }
        } as OnScrollCallback)
      }.zIndex(0)
    }.clip(true)
  }
}