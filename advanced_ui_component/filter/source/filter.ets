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

import measure from '@ohos.measure'
import curves from '@ohos.curves'
import { LengthMetrics } from '@ohos.arkui.node';
import { common, EnvironmentCallback } from '@kit.AbilityKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { JSON } from '@kit.ArkTS';
import { accessibility } from '@kit.AccessibilityKit';

const TEXT_HOT_AREA_WIDTH: number = 8
const LIST_ROW_HEIGHT: number = 40
const ARROW_IMG_SIZE: number = 24
const MULTI_LINE_PADDING: number = 24
const BAR_ANIMATION_DURATION: number = 150
const ARROW_ANIMATION_DURATION: number = 200
const ANIMATION_DURATION_250: number = 250
const ANIMATION_DURATION_100: number = 100
const FILTER_TOP_PADDING: number = 8
const FILTER_BAR_MARGIN: number = 8
const SEPARATOR_HEIGHT: number = 16
const SEPARATOR_WIDTH: number = 1
const FLOAT_OPACITY: number = 0.95
const FILTER_FONT_SIZE = 12
const FOCUS_BORDER_WIDTH = 2
const ARROW_SHOW_DELAY = 300
const PERCENT_100: Length = '100%'
const SHARP_CUBIC_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1)
const INTER_POLATING_SPRING = curves.interpolatingSpring(0, 1, 328, 34)
const FRICTION_CUBIC_BEZIER = curves.cubicBezierCurve(0.2, 0, 0.2, 1)
const TRANS_COLOR: string = '#00FFFFFF'
const GRADIENT_WIDTH: number = 16
const MAX_FONT_SCALE: number = 2;
const ERROR_CODE: number = 0x3900;
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
  index: number;
  value: ResourceStr;
}

@Observed
class FontWeightArray extends Array<FontWeight> {
}

@Observed
class ResourceArray extends Array<Resource> {
}

@Observed
class BooleanArray extends Array<boolean> {
}

@Observed
export class ObservedBoolean {
  public value: boolean

  constructor(value: boolean) {
    this.value = value
  }
}

@Observed
class ObservedNumber {
  public value: number

  constructor(value: number) {
    this.value = value
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
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context2D: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

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
        })
    }
    .blendMode(BlendMode.DST_OUT)
    .width(GRADIENT_WIDTH)
    .height(LIST_ROW_HEIGHT)
  }
}

@Component
struct ListFilterRow {
  @ObjectLink colorRow: ResourceArray
  @ObjectLink fontWeightRow: FontWeightArray
  @ObjectLink backgroundColorRow: ResourceArray
  @ObjectLink isBackgroundHoverRow: BooleanArray
  @ObjectLink isSelectedRow: BooleanArray;
  @ObjectLink filterAccessibilityText: FilterAccessibilityText;
  filterRow: FilterParams = { name: '', options: [] };
  onItemClick: (colIndex: number) => void = () => {}
  rowIndex: number = 0
  maxAppFontScale: number = 1;
  isFollowingSystemFontScale: boolean = false;
  bundleName: string = '';

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxAppFontScale = uiContent.getMaxFontScale();
    } catch (err) {
      let code: number = (err as BusinessError).code;
      let message: string = (err as BusinessError).message;
      hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    this.bundleName = (getContext(this) as common.UIAbilityContext)?.abilityInfo?.bundleName;
  }

  updateFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    let systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(systemFontScale, this.maxAppFontScale);
  }

  getAccessibilityText(resource: ResourceStr | undefined, selected: boolean, type: FilterAccessibilityType): string {
    let accessibilityText: string = '';
    try {
      let resourceString: string = '';
      if (typeof resource === 'string') {
        resourceString = resource;
      } else {
        resourceString = getContext()?.resourceManager?.getStringSync(resource?.id);
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
      let code: number = (error as BusinessError).code;
      let message: string = (error as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
    }
    return accessibilityText;
  }

  sendAccessibility(resource: ResourceStr | undefined, selected: boolean): void {
    let eventInfo: accessibility.EventInfo = ({
      type: 'announceForAccessibility',
      bundleName: this.bundleName,
      triggerAction: 'common',
      textAnnouncedForAccessibility: this.getAccessibilityText(resource, selected,
        FilterAccessibilityType.SEND_ACCESSIBILITY),
    });
    accessibility.sendAccessibilityEvent(eventInfo).then(() => {
      hilog.info(0x3900, 'Ace', `ListFilter sendAccessibility send event, event info is ${JSON.stringify(eventInfo)}`);
    })
  }

  build() {
    Stack({ alignContent: Alignment.End }) {
      Stack({ alignContent: Alignment.Start }) {
        List() {
          ForEach(this.filterRow.options, (option: ResourceStr, colIndex: number) => {
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
                .fontColor(this.colorRow[colIndex])
                .fontWeight(this.fontWeightRow[colIndex])
                .focusable(true)
            }
            .accessibilityText(this.getAccessibilityText(option,
              this.isSelectedRow[colIndex], FilterAccessibilityType.ACCESSIBILITY_TEXT))
            .accessibilityDescription(this.getAccessibilityText(option,
              this.isSelectedRow[colIndex], FilterAccessibilityType.ACCESSIBILITY_DESC))
            .height(PERCENT_100)
            .onClick(() => {
              this.onItemClick(colIndex)
              this.sendAccessibility(option, true);
            })
            .focusable(true)
            .stateStyles({
              focused: {
                .border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: FOCUS_BORDER_WIDTH,
                  color: $r('sys.color.ohos_id_color_focused_outline'),
                  style: BorderStyle.Solid
                })
                .padding({
                  start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                  end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                })
              },
              normal: {
                .border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: 0 })
                .padding({ start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH), end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH) })
              }
            })
            .backgroundColor(this.isBackgroundHoverRow[colIndex] ? this.backgroundColorRow[colIndex] : TRANS_COLOR)
            .onHover((isHover: boolean) => {
              animateTo({
                curve: FRICTION_CUBIC_BEZIER,
                duration: ANIMATION_DURATION_250
              }, () => {
                if (isHover) {
                  this.backgroundColorRow[colIndex] = $r('sys.color.ohos_id_color_hover')
                  this.isBackgroundHoverRow[colIndex] = true
                } else {
                  this.isBackgroundHoverRow[colIndex] = false
                }
              })
            })
            .onTouch((event) => {
              if (event.type === TouchType.Down) {
                animateTo({
                  curve: SHARP_CUBIC_BEZIER,
                  duration: ANIMATION_DURATION_100
                }, () => {
                  this.backgroundColorRow[colIndex] = $r('sys.color.ohos_id_color_click_effect')
                  this.isBackgroundHoverRow[colIndex] = true
                })
              } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                animateTo({
                  curve: SHARP_CUBIC_BEZIER,
                  duration: ANIMATION_DURATION_100
                }, () => {
                  this.isBackgroundHoverRow[colIndex] = false
                })
              }
            })
            .margin({ start: LengthMetrics.vp(colIndex === 0 ? -TEXT_HOT_AREA_WIDTH : 0) })
            .tabIndex(colIndex === 0 ? this.rowIndex : -1)
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
  @ObjectLink colorRow: ResourceArray
  @ObjectLink fontWeightRow: FontWeightArray
  @ObjectLink backgroundColorRow: ResourceArray
  @ObjectLink isBackgroundHoverRow: BooleanArray
  @ObjectLink twoLineModeItemNumRow: ObservedNumber
  @ObjectLink twoLineModeItemNumRecordRow: ObservedNumber
  @ObjectLink arrowShowStateRow: ObservedBoolean
  @ObjectLink isArrowIconDown: ObservedBoolean
  @ObjectLink isSelectedRow: BooleanArray;
  @ObjectLink filterAccessibilityText: FilterAccessibilityText;
  filterRow: FilterParams | null = null
  onItemClick: (colIndex: number) => void = () => {}
  @State arrowBgColorRow: Resource = $r('sys.color.ohos_id_color_hover')
  @State isArrowBgHoverRow: boolean = false
  @Prop fontSizeScale: number | undefined;
  @State replaceEffect: number = 0;
  @State isSendArrowAccessibility: boolean = false;
  private filterColumnWidth: number = 0
  private lastFilterColumnWidth: number = 0
  private rowIndex: number = 0
  maxAppFontScale: number = 1;
  isFollowingSystemFontScale: boolean = false;
  bundleName: string = '';
  filterId: number = this.getUniqueId();

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxAppFontScale = uiContent.getMaxFontScale();
    } catch (err) {
      let code: number = (err as BusinessError).code;
      let message: string = (err as BusinessError).message;
      hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    this.bundleName = (getContext(this) as common.UIAbilityContext)?.abilityInfo?.bundleName;
  }

  updateFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    let systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(systemFontScale, this.maxAppFontScale);
  }

  private calcMultiFilterRowItemNum() {
    let curLineRetainWidth = this.filterColumnWidth;
    let curLineSum = 0
    let curLine = 1
    if (this.filterRow) {
      for (let i = 0; i < this.filterRow.options.length; i++) {
        let option = this.filterRow.options[i]
        let itemWidth = measure.measureText({
          textContent: option,
          fontSize: `${FILTER_FONT_SIZE * Math.min(this.updateFontScale(), MAX_FONT_SCALE)}vp`,
        })
        if (i === 0) {
          continue
        } else {
          itemWidth += vp2px(TEXT_HOT_AREA_WIDTH * 2)
        }
        if (curLineRetainWidth - itemWidth >= 0) {
          curLineRetainWidth -= itemWidth
          curLineSum += 1
        } else {
          if (curLineSum === 0) {
            curLineSum++
            curLineRetainWidth = 0
          }
          if (curLine === 1) {
            curLine += 1
            curLineRetainWidth =
              this.filterColumnWidth - vp2px(ARROW_IMG_SIZE * (this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE));
            i--
          } else {
            break
          }
        }
      }
    }
    return curLineSum
  }

  getAccessibilityText(resource: ResourceStr | undefined, selected: boolean, type: FilterAccessibilityType): string {
    let accessibilityText: string = '';
    try {
      let resourceString: string = '';
      if (typeof resource === 'string') {
        resourceString = resource;
      } else {
        resourceString = getContext()?.resourceManager?.getStringSync(resource?.id);
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
      let code: number = (error as BusinessError).code;
      let message: string = (error as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
    }
    return accessibilityText;
  }

  private sendAccessibility(resource: ResourceStr | undefined, selected: boolean): void {
    let eventInfo: accessibility.EventInfo = ({
      type: 'announceForAccessibility',
      bundleName: this.bundleName,
      triggerAction: 'common',
      textAnnouncedForAccessibility: this.getAccessibilityText(resource, selected,
        FilterAccessibilityType.SEND_ACCESSIBILITY),
    });
    accessibility.sendAccessibilityEvent(eventInfo);
  }

  private sendArrowAccessibility(id: string): void {
    if (this.isSendArrowAccessibility) {
      let eventInfo: accessibility.EventInfo = ({
        type: 'requestFocusForAccessibility',
        bundleName: this.bundleName,
        triggerAction: 'common',
        customId: id,
      });
      accessibility.sendAccessibilityEvent(eventInfo).then(() => {
        setTimeout(() => {
          this.isSendArrowAccessibility = false;
        }, 200);
      });
    }
  }

  @Builder
  DownAndUpArrow() {
    Row() {
      Button({ stateEffect: false, type: ButtonType.Normal }) {
        SymbolGlyph(this.isArrowIconDown.value ? $r('sys.symbol.chevron_down') : $r('sys.symbol.chevron_up'))
          .fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`)
          .height(LIST_ROW_HEIGHT)
          .fontColor([$r('sys.color.ohos_id_color_tertiary')])
          .symbolEffect(new ReplaceSymbolEffect(EffectScope.WHOLE), this.replaceEffect)
          .focusable(true)
          .draggable(false)
          .stateStyles({
            focused: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: FOCUS_BORDER_WIDTH,
                color: $r('sys.color.ohos_id_color_focused_outline'),
                style: BorderStyle.Solid
              })
              .offset({ x: -FOCUS_BORDER_WIDTH })
            },
            normal: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: 0 })
              .offset({ x: 0 })
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
      .id(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`)
      .visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden)
      .onHover((isHover: boolean) => {
        animateTo({
          curve: FRICTION_CUBIC_BEZIER,
          duration: ANIMATION_DURATION_250
        }, () => {
          if (isHover) {
            this.arrowBgColorRow = $r('sys.color.ohos_id_color_hover')
            this.isArrowBgHoverRow = true
          } else {
            this.isArrowBgHoverRow = false
          }
        })
      })
      .onTouch((event) => {
        if (event.type === TouchType.Down) {
          animateTo({
            curve: SHARP_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_100
          }, () => {
            this.arrowBgColorRow = $r('sys.color.ohos_id_color_click_effect')
            this.isArrowBgHoverRow = true
          })
        } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
          animateTo({
            curve: SHARP_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_100
          }, () => {
            this.isArrowBgHoverRow = false
          })
        }
      })
      .onClick(() => {
        this.isSendArrowAccessibility = true;
        this.replaceEffect += 1
        if (this.isArrowIconDown.value) {
          this.isArrowIconDown.value = false
          this.arrowShowStateRow.value = false
          animateTo({
            curve: INTER_POLATING_SPRING,
          }, () => {
            this.twoLineModeItemNumRow.value = this.filterRow?.options.length as number
          })

          animateTo({
            delay: 300,
            duration: ARROW_ANIMATION_DURATION,
            curve: SHARP_CUBIC_BEZIER
          }, () => {
            this.arrowShowStateRow.value = true
          })
        } else {
          this.isArrowIconDown.value = true
          this.arrowShowStateRow.value = false

          animateTo({
            curve: INTER_POLATING_SPRING,
          }, () => {
            this.twoLineModeItemNumRow.value = this.twoLineModeItemNumRecordRow.value
          })
          animateTo({
            delay: ARROW_SHOW_DELAY,
            duration: ARROW_ANIMATION_DURATION,
            curve: SHARP_CUBIC_BEZIER
          }, () => {
            this.arrowShowStateRow.value = true
          })
        }
        this.sendArrowAccessibility(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`);
      })
    }
    .height(LIST_ROW_HEIGHT)
  }

  build() {
    Flex() {
      if (this.filterRow?.options && this.filterRow?.options.length > 0) {
        Text(this.filterRow?.options[0])
          .height(LIST_ROW_HEIGHT)
          .margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) })
          .fontSize($r('sys.float.ohos_id_text_size_body3'))
          .minFontScale(1)
          .maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE))
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .fontColor(this.colorRow[0])
          .fontWeight(this.fontWeightRow[0])
          .backgroundColor(this.isBackgroundHoverRow[0] ? this.backgroundColorRow[0] : TRANS_COLOR)
          .accessibilityText(this.getAccessibilityText(this.filterRow?.options[0],
            this.isSelectedRow[0], FilterAccessibilityType.ACCESSIBILITY_TEXT))
          .accessibilityDescription(this.getAccessibilityText(this.filterRow?.options[0],
            this.isSelectedRow[0], FilterAccessibilityType.ACCESSIBILITY_DESC))
          .onClick(() => {
            this.onItemClick(0);
            this.sendAccessibility(this.filterRow?.options[0], true);
          })
          .id(`filterMultiFilterRow_${this.filterId}_${this.rowIndex}`)
          .focusable(true)
          .onHover((isHover: boolean) => {
            animateTo({
              curve: FRICTION_CUBIC_BEZIER,
              duration: ANIMATION_DURATION_250
            }, () => {
              if (isHover) {
                this.backgroundColorRow[0] = $r('sys.color.ohos_id_color_hover')
                this.isBackgroundHoverRow[0] = true
              } else {
                this.isBackgroundHoverRow[0] = false
              }
            })
          })
          .onTouch((event) => {
            if (event.type === TouchType.Down) {
              animateTo({
                curve: SHARP_CUBIC_BEZIER,
                duration: ANIMATION_DURATION_100
              }, () => {
                this.backgroundColorRow[0] = $r('sys.color.ohos_id_color_click_effect')
                this.isBackgroundHoverRow[0] = true
              })
            } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
              animateTo({
                curve: SHARP_CUBIC_BEZIER,
                duration: ANIMATION_DURATION_100
              }, () => {
                this.isBackgroundHoverRow[0] = false
              })
            }
          })
          .stateStyles({
            focused: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: FOCUS_BORDER_WIDTH,
                color: $r('sys.color.ohos_id_color_focused_outline'),
                style: BorderStyle.Solid
              })
              .padding({
                start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
              })
            },
            normal: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: 0 })
              .padding({ start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH), end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH) })
            }
          })
          .constraintSize({ maxWidth: '50%' })
          .flexShrink(0)
          .tabIndex(this.rowIndex)
      }
      Row() {
        Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
          ForEach(this.filterRow?.options.slice(0, this.twoLineModeItemNumRow.value + 1),
            (option: ResourceStr, colIndex: number) => {
              if (colIndex > 0) {
                Text(option)
                  .transition(TransitionEffect.OPACITY)
                  .fontSize($r('sys.float.ohos_id_text_size_body3'))
                  .minFontScale(1)
                  .maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE))
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .height(LIST_ROW_HEIGHT)
                  .fontColor(this.colorRow[colIndex])
                  .fontWeight(this.fontWeightRow[colIndex])
                  .accessibilityText(this.getAccessibilityText(option,
                    this.isSelectedRow[colIndex], FilterAccessibilityType.ACCESSIBILITY_TEXT))
                  .accessibilityDescription(this.getAccessibilityText(option,
                    this.isSelectedRow[colIndex], FilterAccessibilityType.ACCESSIBILITY_DESC))
                  .backgroundColor(this.isBackgroundHoverRow[colIndex] ?
                  this.backgroundColorRow[colIndex] : TRANS_COLOR)
                  .onClick(() => {
                    this.onItemClick(colIndex)
                    this.sendAccessibility(option, true);
                  })
                  .onHover((isHover: boolean) => {
                    animateTo({
                      curve: FRICTION_CUBIC_BEZIER,
                      duration: ANIMATION_DURATION_250
                    }, () => {
                      if (isHover) {
                        this.backgroundColorRow[colIndex] = $r('sys.color.ohos_id_color_hover')
                        this.isBackgroundHoverRow[colIndex] = true
                      } else {
                        this.isBackgroundHoverRow[colIndex] = false
                      }
                    })
                  })
                  .onTouch((event) => {
                    if (event.type === TouchType.Down) {
                      animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                      }, () => {
                        this.backgroundColorRow[colIndex] = $r('sys.color.ohos_id_color_click_effect')
                        this.isBackgroundHoverRow[colIndex] = true
                      })
                    } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                      animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                      }, () => {
                        this.isBackgroundHoverRow[colIndex] = false
                      })
                    }
                  })
                  .focusable(true)
                  .stateStyles({
                    focused: {
                      .border({
                        radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                        width: FOCUS_BORDER_WIDTH,
                        color: $r('sys.color.ohos_id_color_focused_outline'),
                        style: BorderStyle.Solid
                      })
                      .padding({
                        start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                        end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                      })
                    },
                    normal: {
                      .border({
                        radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                        width: 0 })
                      .padding({
                        start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                        end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                      })
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
        this.filterColumnWidth = vp2px(parseInt(newValue.width.toString(), 0))
        if (this.twoLineModeItemNumRow.value === 0) {
          let curLineSum = this.calcMultiFilterRowItemNum()
          this.twoLineModeItemNumRow.value = curLineSum
          this.twoLineModeItemNumRecordRow.value = curLineSum
          if (this.filterRow && curLineSum < this.filterRow.options.length - 1) {
            this.arrowShowStateRow.value = true
          } else {
            this.arrowShowStateRow.value = false
          }
        } else if (this.filterColumnWidth !== this.lastFilterColumnWidth) {
          let curLineSum = this.calcMultiFilterRowItemNum()
          if (this.filterRow && curLineSum < this.filterRow.options.length - 1) {
            if (!this.arrowShowStateRow.value || this.isArrowIconDown.value) {
              this.arrowShowStateRow.value = true
              this.isArrowIconDown.value = true
              this.twoLineModeItemNumRow.value = curLineSum
            }
          } else {
            this.arrowShowStateRow.value = false
            this.isArrowIconDown.value = false
            this.twoLineModeItemNumRow.value = curLineSum
          }
          this.twoLineModeItemNumRecordRow.value = curLineSum
        }
        this.lastFilterColumnWidth = this.filterColumnWidth
      })

    }.width(PERCENT_100)
    .padding({
      start: LengthMetrics.resource($r('sys.float.ohos_id_max_padding_start')),
      end: LengthMetrics.resource($r('sys.float.ohos_id_max_padding_end'))
    })
  }
}


@Component
export struct Filter {
  @BuilderParam container: () => void
  @Prop multiFilters: Array<FilterParams> = []
  @Prop additionFilters: FilterParams | null = null
  onFilterChanged: ((filterResults: Array<FilterResult>) => void) | null = null
  @Prop filterType: FilterType = FilterType.LIST_FILTER
  private selectedFilters: Array<FilterResult> | null = null
  @State private colorArr: Array<ResourceArray> | null = null
  @State private fontWeightArr: Array<FontWeightArray> | null = null
  @State private backgroundColorArr: Array<ResourceArray> | null = null
  @State private isBackgroundHover: Array<BooleanArray> | null = null
  @State private floatArrowBgColor: Resource | null = null
  @State private isFloatArrowBgHover: boolean = false
  @State private isArrowIconDownArr: Array<ObservedBoolean> | null = null
  @State private additionColorArr: Array<Resource> | null = null
  @State private additionFontWeightArr: Array<FontWeight> | null = null
  @State private additionBackgroundColorArr: Array<Resource> | null = null
  @State private isAdditionBackgroundHover: Array<boolean> | null = null
  @State private isSelectedArr: Array<BooleanArray> | null = null;
  @State colorRefresh: boolean = false
  @State @Watch('updateFocusForAccessibility') isFloatBarShow: boolean = false;
  isFloatBarShowWithoutAnimation: boolean = false
  @State isFloatShowAllFilter: boolean = false
  isFloatShowAllFilterWithoutAnimation: boolean = false
  @State floatFilterPosition: number = 0
  @State floatFilterBarHeight: number = 0
  @State floatFilterBarPosition: number = 0
  filterDynamicHeight: number = 0
  @State twoLineModeItemNum: Array<ObservedNumber> | null = null
  @State twoLineModeItemNumRecord: Array<ObservedNumber> | null = null
  @State downArrowShowState: Array<ObservedBoolean> | null = null
  @State floatFilterBarText: string = ''
  maxAppFontScale: number = 1;
  isFollowingSystemFontScale: boolean = false;
  @State fontSizeScale: number | undefined = undefined;
  private callbackId: number | undefined = undefined;
  private callbacks: EnvironmentCallback = {
    onConfigurationUpdated: (config) => {
      this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
      this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
      this.initAccessibilityResource();
    }, onMemoryLevel() {
    }
  };
  @State additionFiltersSelectedIndex?: number = -1;
  @State floatFilterBarAccessibilityText: string = '';
  @State filterAccessibilityText: FilterAccessibilityText = new FilterAccessibilityText();
  bundleName: string = '';
  private filterId: number = this.getUniqueId();

  textColor(rowIndex: number, colIndex: number) {
    if (this.selectedFilters && this.selectedFilters.length > rowIndex &&
      this.selectedFilters[rowIndex].index === colIndex) {
      return $r('sys.color.ohos_id_color_text_primary_activated')
    }
    return $r('sys.color.ohos_id_color_text_primary')
  }

  aboutToAppear() {
    this.initParams();
    this.initAccessibilityResource();
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxAppFontScale = uiContent.getMaxFontScale();
      this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
      this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
      this.callbackId = uiContent.getHostContext()?.getApplicationContext()?.on('environment', this.callbacks);
    } catch (err) {
      let code: number = (err as BusinessError).code;
      let message: string = (err as BusinessError).message;
      hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
  }

  aboutToDisappear(): void {
    if (this.callbackId) {
      this.getUIContext()
        .getHostContext()
      ?.getApplicationContext()
      ?.off('environment', this.callbackId);
      this.callbackId = void (0);
    }
  }

  private initAccessibilityResource(): void {
    try {
      this.bundleName = (getContext(this) as common.UIAbilityContext)?.abilityInfo?.bundleName;
      let resourceManager = getContext()?.resourceManager;
      this.filterAccessibilityText.accessibilitySelectedText =
        resourceManager?.getStringByNameSync('filter_accessibility_selected');
      this.filterAccessibilityText.accessibilityUnselectedText =
        resourceManager?.getStringByNameSync('filter_accessibility_unselected');
      this.filterAccessibilityText.accessibilityFilters =
        resourceManager?.getStringByNameSync('filter_accessibility_filters');
      this.filterAccessibilityText.accessibilitySelectedDesc =
        resourceManager?.getStringByNameSync('filter_accessibility_select_desc');
      this.filterAccessibilityText.accessibilityUnselectedDesc =
        resourceManager?.getStringByNameSync('filter_accessibility_unselect_desc');
      this.filterAccessibilityText.accessibilityExpandDesc =
        resourceManager?.getStringByNameSync('filter_accessibility_expand_desc');
      this.filterAccessibilityText.accessibilityExpanded =
        resourceManager?.getStringByNameSync('filter_accessibility_expanded');
      this.filterAccessibilityText.accessibilityCollapsed =
        resourceManager?.getStringByNameSync('filter_accessibility_collapsed');
      this.filterAccessibilityText.accessibilityExpand =
        resourceManager?.getStringByNameSync('filter_accessibility_expand');
      this.filterAccessibilityText.accessibilityCollapse =
        resourceManager?.getStringByNameSync('filter_accessibility_collapse');
    } catch (err) {
      let code: number = (err as BusinessError).code;
      let message: string = (err as BusinessError).message;
      hilog.error(ERROR_CODE, 'Ace', `Filter failed to initAccessibilityResource, code: ${code}, message: ${message}`);
    }
  }

  updateFocusForAccessibility(): void {
    if (this.isFloatBarShow) {
      let eventInfo: accessibility.EventInfo = ({
        type: 'requestFocusForAccessibility',
        bundleName: this.bundleName,
        triggerAction: 'common',
        customId: `FiliterFloatFilterBar_${this.getUniqueId()}`,
      });
      accessibility.sendAccessibilityEvent(eventInfo);
    }
  }

  updateFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    let systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(systemFontScale, this.maxAppFontScale);
  }

  getAccessibilityText(resource: ResourceStr | undefined, selected: boolean, type: FilterAccessibilityType): string {
    let accessibilityText: string = '';
    try {
      let resourceString: string = '';
      if (typeof resource === 'string') {
        resourceString = resource;
      } else {
        resourceString = getContext().resourceManager.getStringSync(resource?.id);
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
      let code: number = (error as BusinessError).code;
      let message: string = (error as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
    }
    return accessibilityText;
  }

  private sendAccessibility(resource: ResourceStr | undefined, selected: boolean): void {
    let eventInfo: accessibility.EventInfo = ({
      type: 'announceForAccessibility',
      bundleName: this.bundleName,
      triggerAction: 'common',
      textAnnouncedForAccessibility: this.getAccessibilityText(resource, selected,
        FilterAccessibilityType.SEND_ACCESSIBILITY),
    });
    accessibility.sendAccessibilityEvent(eventInfo).then(() => {
      hilog.info(0x3900, 'Ace', `ListFilter sendAccessibility send event, event info is ${JSON.stringify(eventInfo)}`);
    })
  }

  private filterItemClick(rowIndex: number, colIndex: number): void {
    let selectedFilterValue = this.multiFilters[rowIndex].options[colIndex]
    if (this.selectedFilters && colIndex !== this.selectedFilters[rowIndex].index) {
      if (this.colorArr) {
        this.colorArr[rowIndex][colIndex] = $r('sys.color.ohos_id_color_text_primary_activated')
        this.colorArr[rowIndex][this.selectedFilters[rowIndex].index] = $r('sys.color.ohos_id_color_text_primary')
      }
      if (this.fontWeightArr) {
        this.fontWeightArr[rowIndex][colIndex] = FontWeight.Medium
        this.fontWeightArr[rowIndex][this.selectedFilters[rowIndex].index] = FontWeight.Regular
      }
      if (this.isSelectedArr) {
        this.isSelectedArr[rowIndex][colIndex] = true;
        this.isSelectedArr[rowIndex][this.selectedFilters[rowIndex].index] = false;
      }
      this.colorRefresh = !this.colorRefresh
      this.selectedFilters[rowIndex].value = selectedFilterValue
      this.selectedFilters[rowIndex].index = colIndex
      let filterChanged = this.onFilterChanged
      filterChanged && filterChanged(this.selectedFilters)
    }
    this.refreshFloatFilterBarText()
  }

  private refreshFloatFilterBarText(): void {
    this.floatFilterBarText = '';
    this.floatFilterBarAccessibilityText = '';
    if (this.selectedFilters) {
      const selectedValueFilters = this.selectedFilters?.filter(item => item?.value).map((item) => {
        if (typeof item.value !== 'string') {
          return getContext()?.resourceManager?.getStringSync((item.value as Resource)?.id);
        } else {
          return item.value;
        }
      });
      this.floatFilterBarText = selectedValueFilters.join('/');
      this.floatFilterBarAccessibilityText = selectedValueFilters.join(' ');
    }
  }

  private getFloatAccessibilityText(resource: ResourceStr | undefined, type: FilterAccessibilityType): string {
    let accessibilityText: string = '';
    let accessibilityFilters: string = this.filterAccessibilityText.accessibilityFilters;
    let accessibilityCollapsed: string = this.filterAccessibilityText.accessibilityCollapsed;
    try {
      let resourceString: string = '';
      if (typeof resource === 'string') {
        resourceString = resource;
      } else {
        resourceString = getContext()?.resourceManager?.getStringSync(resource?.id);
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
      let code: number = (error as BusinessError).code;
      let message: string = (error as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
    }
    return accessibilityText;
  }

  private sendFloatAccessibility(resource: ResourceStr | undefined): void {
    let eventInfo: accessibility.EventInfo = ({
      type: 'announceForAccessibility',
      bundleName: this.bundleName,
      triggerAction: 'common',
      textAnnouncedForAccessibility: this.getFloatAccessibilityText(resource,
        FilterAccessibilityType.SEND_ACCESSIBILITY),
    });
    accessibility.sendAccessibilityEvent(eventInfo);
    if (this.multiFilters && this.multiFilters.length > 0) {
      let requestFocusEventInfo: accessibility.EventInfo = ({
        type: 'requestFocusForAccessibility',
        bundleName: this.bundleName,
        triggerAction: 'common',
        customId: `filterMultiFilterRow_${this.filterId}_0`,
      });
      accessibility.sendAccessibilityEvent(requestFocusEventInfo);
    } else if (this.additionFilters && this.additionFilters.name) {
      let requestFocusEventInfo: accessibility.EventInfo = ({
        type: 'requestFocusForAccessibility',
        bundleName: this.bundleName,
        triggerAction: 'common',
        customId: `filterAdditionFiltersName_${this.filterId}`,
      });
      accessibility.sendAccessibilityEvent(requestFocusEventInfo);
    }
  }

  private initParams(): void {
    if (!this.selectedFilters) {
      this.selectedFilters = []
      for (let filter of this.multiFilters) {
        let result: FilterResult = { name: filter.name, index: -1, value: '' }
        if (filter.options.length > 0) {
          result.index = 0
          result.value = filter.options[0]
        }
        this.selectedFilters.push(result)
      }
      if (this.additionFilters && this.additionFilters.name) {
        let result: FilterResult = { name: this.additionFilters.name, index: -1, value: '' }
        this.selectedFilters.push(result)
      }
      this.refreshFloatFilterBarText();
    }
    if (!this.colorArr) {
      this.colorArr = []
      this.backgroundColorArr = []
      this.isBackgroundHover = []
      this.fontWeightArr = []
      this.isArrowIconDownArr = []
      this.isSelectedArr = [];
      this.floatArrowBgColor = $r('sys.color.ohos_id_color_background')
      for (let filter of this.multiFilters) {
        let colorRow = new ResourceArray()
        let fontWeightRow = new FontWeightArray()
        let backgroundColorRow = new ResourceArray()
        let isBackgroundHoverRow = new BooleanArray()
        let isSelectedRow = new BooleanArray();
        for (let index of filter.options.keys()) {
          if (index === 0) {
            colorRow.push($r('sys.color.ohos_id_color_text_primary_activated'))
            fontWeightRow.push(FontWeight.Medium)
            isSelectedRow.push(true);
          } else {
            colorRow.push($r('sys.color.ohos_id_color_text_primary'))
            fontWeightRow.push(FontWeight.Regular)
            isSelectedRow.push(false);
          }
          backgroundColorRow.push($r('sys.color.ohos_id_color_hover'))
        }
        this.colorArr.push(colorRow)
        this.fontWeightArr.push(fontWeightRow)
        this.backgroundColorArr.push(backgroundColorRow)
        this.isBackgroundHover.push(isBackgroundHoverRow)
        this.isArrowIconDownArr.push(new ObservedBoolean(true))
        this.isSelectedArr.push(isSelectedRow);
      }
    }
    if (this.additionFilters && this.additionFilters.options) {
      this.additionColorArr = []
      this.additionFontWeightArr = []
      this.additionBackgroundColorArr = []
      this.isAdditionBackgroundHover = []
      for (let i = 0; i < this.additionFilters.options.length; i++) {
        this.additionColorArr.push($r('sys.color.ohos_id_color_text_primary'))
        this.additionFontWeightArr.push(FontWeight.Regular)
        this.additionBackgroundColorArr.push($r('sys.color.ohos_id_color_hover'))
        this.isAdditionBackgroundHover.push(false)
      }
    }
    if (!this.twoLineModeItemNum) {
      this.twoLineModeItemNum = []
      this.twoLineModeItemNumRecord = []
      this.downArrowShowState = []
      for (let i = 0; i < this.multiFilters.length; i++) {
        this.twoLineModeItemNum.push(new ObservedNumber(this.multiFilters[i].options.length))
        this.twoLineModeItemNumRecord.push(new ObservedNumber(this.multiFilters[i].options.length))
        this.downArrowShowState.push(new ObservedBoolean(false))
      }
    }
  }

  @Builder
  ListFilter() {
    Column() {
      ForEach(this.multiFilters, (filter: FilterParams, rowIndex: number) => {
        ListFilterRow({
          colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
          fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
          backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
          isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
          isSelectedRow: this.isSelectedArr ? this.isSelectedArr[rowIndex] : [],
          filterRow: filter,
          onItemClick: (colIndex: number) => {
            this.filterItemClick(rowIndex, colIndex);
          },
          rowIndex: rowIndex,
          filterAccessibilityText: this.filterAccessibilityText,
        })
      })
    }.width(PERCENT_100)
    .align(Alignment.Start)
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
        if (this.additionFilters !== null) {
          this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING
        } else {
          this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + FILTER_TOP_PADDING
        }
        this.floatFilterPosition = -this.filterDynamicHeight
      }
    })
  }

  @Builder
  MultiLineFilter() {
    Column() {
      ForEach(this.multiFilters, (filterItem: FilterParams, rowIndex: number) => {
        MultiFilterRow({
          colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
          fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
          backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
          isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
          arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[rowIndex] : new ObservedBoolean(false),
          twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[rowIndex] : new ObservedNumber(0),
          isSelectedRow: this.isSelectedArr ? this.isSelectedArr[rowIndex] : [],
          twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ? this.twoLineModeItemNumRecord[rowIndex] :
            new ObservedNumber(0),
          isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[rowIndex] : new ObservedBoolean(false),
          filterRow: filterItem,
          onItemClick: (colIndex: number) => {
            this.filterItemClick(rowIndex, colIndex);
          },
          rowIndex: rowIndex,
          fontSizeScale: this.fontSizeScale,
          filterId: this.filterId,
          filterAccessibilityText: this.filterAccessibilityText,
        })
      })
    }.width(PERCENT_100)
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      if (this.additionFilters !== null) {
        this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING
      } else {
        this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + FILTER_TOP_PADDING
      }
      if (!this.isFloatBarShowWithoutAnimation && !this.isFloatShowAllFilterWithoutAnimation) {
        this.floatFilterPosition = -this.filterDynamicHeight
      }
    })
  }

  private additionItemClick(index: number): void {
    let additionRowIndex = this.multiFilters.length
    if (this.selectedFilters && this.selectedFilters[additionRowIndex].index !== index) {
      if (this.selectedFilters[additionRowIndex].index === -1) {
        this.additionColorArr && (this.additionColorArr[index] = $r('sys.color.ohos_id_color_text_primary_activated'))
        this.additionFontWeightArr && (this.additionFontWeightArr[index] = FontWeight.Medium)
        this.selectedFilters[additionRowIndex].value = this.additionFilters ? this.additionFilters.options[index] : ''
        this.selectedFilters[additionRowIndex].index = index
        this.additionFiltersSelectedIndex = index;
      } else {
        let lastIndex = this.selectedFilters[additionRowIndex].index
        this.additionColorArr && (this.additionColorArr[lastIndex] = $r('sys.color.ohos_id_color_text_primary'))
        this.additionColorArr && (this.additionColorArr[index] = $r('sys.color.ohos_id_color_text_primary_activated'))
        this.additionFontWeightArr && (this.additionFontWeightArr[lastIndex] = FontWeight.Regular)
        this.additionFontWeightArr && (this.additionFontWeightArr[index] = FontWeight.Medium)
        this.selectedFilters && (this.selectedFilters[additionRowIndex].value = this.additionFilters ?
        this.additionFilters.options[index] : '')
        this.selectedFilters && (this.selectedFilters[additionRowIndex].index = index)
        this.additionFiltersSelectedIndex = index;
      }
    } else {
      this.additionColorArr && (this.additionColorArr[index] = $r('sys.color.ohos_id_color_text_primary'))
      this.additionFontWeightArr && (this.additionFontWeightArr[index] = FontWeight.Regular)
      this.selectedFilters && (this.selectedFilters[additionRowIndex].value = '')
      this.selectedFilters && (this.selectedFilters[additionRowIndex].index = -1)
      this.additionFiltersSelectedIndex = -1;
    }
    if (this.selectedFilters) {
      this.onFilterChanged && this.onFilterChanged(this.selectedFilters)
    }
    this.colorRefresh = !this.colorRefresh
    this.refreshFloatFilterBarText()
  }

  private getSelected(index: number): boolean {
    let additionRowIndex = this.multiFilters.length;
    if (this.selectedFilters && this.selectedFilters[additionRowIndex].index !== index) {
      return false;
    } else {
      return true;
    }
  }

  @Builder
  AdditionFilterList() {
    if (this.additionFilters && this.additionFilters.name && this.additionFilters.options &&
      this.additionFilters.options.length !== 0) {
      Stack({ alignContent: Alignment.End }) {
        Stack({ alignContent: Alignment.Start }) {
          List() {
            ListItem() {
              Row() {
                Text(this.additionFilters.name)
                  .fontSize($r('sys.float.ohos_id_text_size_body3'))
                  .minFontScale(1)
                  .maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE))
                  .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                  .margin({ start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH), end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH) })
                  .padding({ start: LengthMetrics.resource($r('sys.float.ohos_id_max_padding_start')) })
                  .id(`filterAdditionFiltersName_${this.filterId}`)
                Row()
                  .width(SEPARATOR_WIDTH)
                  .height(SEPARATOR_HEIGHT)
                  .backgroundColor($r('sys.color.ohos_id_color_list_separator'))
              }
            }.height(PERCENT_100)
            .margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) })

            ForEach(this.additionFilters.options, (option: ResourceStr, index: number) => {
              ListItem() {
                Text(option)
                  .fontSize($r('sys.float.ohos_id_text_size_body3'))
                  .minFontScale(1)
                  .maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE))
                  .fontColor(this.additionColorArr ? this.additionColorArr[index] : '')
                  .fontWeight(this.additionFontWeightArr ? this.additionFontWeightArr[index] : '')
                  .focusable(true)
              }
              .accessibilityText(this.getAccessibilityText(option,
                this.additionFiltersSelectedIndex === index, FilterAccessibilityType.ACCESSIBILITY_TEXT))
              .accessibilityDescription(this.getAccessibilityText(option,
                this.additionFiltersSelectedIndex === index, FilterAccessibilityType.ACCESSIBILITY_DESC))
              .height(PERCENT_100)
              .backgroundColor(this.isAdditionBackgroundHover && this.isAdditionBackgroundHover[index] ?
                this.additionBackgroundColorArr ? this.additionBackgroundColorArr[index] : '' : TRANS_COLOR)
              .onHover((isHover: boolean) => {
                animateTo({
                  curve: FRICTION_CUBIC_BEZIER,
                  duration: ANIMATION_DURATION_250
                }, () => {
                  if (isHover) {
                    this.additionBackgroundColorArr &&
                      (this.additionBackgroundColorArr[index] = $r('sys.color.ohos_id_color_hover'))
                    this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[index] = true)
                  } else {
                    this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[index] = false)
                  }
                })
              })
              .onTouch((event) => {
                if (event.type === TouchType.Down) {
                  animateTo({
                    curve: SHARP_CUBIC_BEZIER,
                    duration: ANIMATION_DURATION_100
                  }, () => {
                    this.additionBackgroundColorArr &&
                      (this.additionBackgroundColorArr[index] = $r('sys.color.ohos_id_color_click_effect'))
                    this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[index] = true)
                  })
                } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                  animateTo({
                    curve: SHARP_CUBIC_BEZIER,
                    duration: ANIMATION_DURATION_100
                  }, () => {
                    this.isAdditionBackgroundHover && (this.isAdditionBackgroundHover[index] = false)
                  })
                }
              })
              .focusable(true)
              .stateStyles({
                focused: {
                  .border({
                    radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                    width: FOCUS_BORDER_WIDTH,
                    color: $r('sys.color.ohos_id_color_focused_outline'),
                    style: BorderStyle.Solid
                  })
                  .padding({
                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                  })
                },
                normal: {
                  .border({
                    radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                    width: 0 })
                  .padding({ start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH), end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH) })
                }
              })
              .onClick(() => {
                this.additionItemClick(index)
                this.sendAccessibility(option, this.getSelected(index));
              })
              .tabIndex(index === 0 ? this.multiFilters.length : -1)
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
    }.padding({ top: FILTER_TOP_PADDING })
    .onVisibleAreaChange([0.0, 1.0], (_isVisible: boolean, currentRatio: number) => {
      if (currentRatio > 0) {
        this.isFloatShowAllFilter = false
        this.isFloatShowAllFilterWithoutAnimation = false
        this.isFloatBarShowWithoutAnimation = false
        animateTo({
          curve: INTER_POLATING_SPRING,
          onFinish: () => {
            if (!this.isFloatBarShowWithoutAnimation) {
              this.isFloatBarShow = false
            }
          }
        }, () => {
          this.floatFilterBarHeight = 0
        })
      } else {
        this.isFloatBarShow = true
        this.isFloatBarShowWithoutAnimation = true
        animateTo({
          curve: INTER_POLATING_SPRING
        }, () => {
          this.floatFilterBarPosition = 0
          this.floatFilterBarHeight = LIST_ROW_HEIGHT + FILTER_TOP_PADDING
        })
      }
    })
  }

  @Builder
  FloatFilterHeader() {
    Column() {
      Scroll() {
        Column() {
          if (this.filterType === FilterType.LIST_FILTER) {
            this.ListFilter()
          } else {
            this.MultiLineFilter()
          }
          this.AdditionFilterList()
        }
      }
    }
    .padding({ top: FILTER_TOP_PADDING })
    .width(PERCENT_100)
    .constraintSize({ maxHeight: '80%' })
    .clip(true)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .opacity(FLOAT_OPACITY)
    .backgroundBlurStyle(BlurStyle.Thin)
    .visibility(this.isFloatShowAllFilter ? Visibility.Visible : Visibility.Hidden)
    .position({ x: 0, y: this.floatFilterPosition })
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
          .margin({ start: LengthMetrics.vp(FILTER_BAR_MARGIN) })
          .focusable(true)
        }.height(PERCENT_100)
        .alignItems(VerticalAlign.Center)
      }
      .id(`FiliterFloatFilterBar_${this.getUniqueId()}`)
      .accessibilityText(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText,
        FilterAccessibilityType.ACCESSIBILITY_TEXT))
      .accessibilityDescription(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText,
        FilterAccessibilityType.ACCESSIBILITY_DESC))
      .backgroundColor(this.isFloatArrowBgHover ? this.floatArrowBgColor : TRANS_COLOR)
      .stateStyles({
        focused: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: FOCUS_BORDER_WIDTH,
            color: $r('sys.color.ohos_id_color_focused_outline'),
            style: BorderStyle.Solid
          })
        },
        normal: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: 0 })
        }
      })
      .alignItems(HorizontalAlign.Center)
      .width(PERCENT_100)
      .height(LIST_ROW_HEIGHT)
      .onTouch((event) => {
        if (event.type === TouchType.Down) {
          animateTo({
            curve: SHARP_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_100
          }, () => {
            this.floatArrowBgColor = $r('sys.color.ohos_id_color_click_effect')
            this.isFloatArrowBgHover = true
          })
        } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
          animateTo({
            curve: SHARP_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_100
          }, () => {
            this.isFloatArrowBgHover = false
          })
        }
      })
      .onClick(() => {
        animateTo({
          duration: BAR_ANIMATION_DURATION,
          curve: SHARP_CUBIC_BEZIER
        }, () => {
          this.isFloatBarShow = false
          this.isFloatBarShowWithoutAnimation = false
        })
        this.isFloatShowAllFilter = true
        this.isFloatShowAllFilterWithoutAnimation = true
        animateTo({
          curve: INTER_POLATING_SPRING,
          onFinish: () => {
            this.floatFilterBarPosition = 0
          }
        }, () => {
          this.floatFilterPosition = 0
          this.floatFilterBarPosition = this.filterDynamicHeight
        })
        this.sendFloatAccessibility(this.floatFilterBarAccessibilityText);
      })
      .onHover((isHover: boolean) => {
        if (isHover) {
          animateTo({
            curve: FRICTION_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_250
          }, () => {
            this.floatArrowBgColor = $r('sys.color.ohos_id_color_hover')
            this.isFloatArrowBgHover = true
          })
        } else {
          animateTo({
            curve: FRICTION_CUBIC_BEZIER,
            duration: ANIMATION_DURATION_250
          }, () => {
            this.isFloatArrowBgHover = false
          })
        }
      })
    }
    .width(PERCENT_100)
    .height(this.floatFilterBarHeight)
    .padding({ start: LengthMetrics.vp(FOCUS_BORDER_WIDTH), end: LengthMetrics.vp(FOCUS_BORDER_WIDTH) })
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .opacity(FLOAT_OPACITY)
    .clip(true)
    .backgroundBlurStyle(BlurStyle.Thin)
    .visibility(this.isFloatBarShow ? Visibility.Visible : Visibility.Hidden)
    .alignItems(VerticalAlign.Bottom)
    .position({ x: 0, y: this.floatFilterBarPosition })
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
        .onScroll((_scrollOffset: number, scrollState: ScrollState) => {
          if (this.isFloatShowAllFilterWithoutAnimation && scrollState === ScrollState.Scroll) {
            this.isFloatBarShowWithoutAnimation = true
            this.isFloatShowAllFilterWithoutAnimation = false
            animateTo({
              duration: BAR_ANIMATION_DURATION,
              curve: SHARP_CUBIC_BEZIER
            }, () => {
              this.isFloatBarShow = true
            })

            animateTo({
              curve: INTER_POLATING_SPRING,
              onFinish: () => {
                if (!this.isFloatShowAllFilterWithoutAnimation) {
                  this.isFloatShowAllFilter = false
                }
              }
            }, () => {
              this.floatFilterPosition = -this.filterDynamicHeight
              this.floatFilterBarPosition = 0
            })
          }
        })
      }.zIndex(0)
    }.clip(true)
  }
}