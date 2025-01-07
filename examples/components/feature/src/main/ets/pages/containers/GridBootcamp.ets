/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';
import { Drawer, RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';

@Component
export struct GridBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableFadingEdge: boolean = false;
  @State fadingEdge: boolean = false;
  @State enableFadingEdgeLengthValue: boolean = false;
  @State fadingEdgeLengthValue: number = 32;
  @State enableFadingEdgeLengthUnit: boolean = false;
  @State fadingEdgeLengthUnit: LengthUnit = LengthUnit.VP;
  @State enableFrCount: boolean = false;
  @State frCount: number = 2;
  @State enableColumnsGap: boolean = false;
  @State columnsGap: Length	= 0;
  @State enableRowsGap: boolean = false;
  @State rowsGap: Length	= 0;
  @State enableScrollBar: boolean = false;
  @State scrollBar: BarState = BarState.Auto;
  @State enableScrollBarColor: boolean = false;
  @State scrollBarColor: Color | number | string = '#182431';
  @State enableScrollBarWidth: boolean = false;
  @State scrollBarWidth: number | string = 4;
  @State enableCachedCount: boolean = false;
  @State cachedCount: number = 1;
  @State enableEditMode: boolean = false;
  @State editMode: boolean = false;
  @State enableLayoutDirection: boolean = false;
  @State layoutDirection: GridDirection = GridDirection.Row;
  @State enableMaxCount: boolean = false;
  @State maxCount: number = Infinity;
  @State enableMinCount: boolean = false;
  @State minCount: number = 1;
  @State enableCellLength: boolean = false;
  @State cellLength: number = 0;
  @State enableMultiSelectable: boolean = false;
  @State multiSelectable: boolean = false;
  @State enableSupportAnimation: boolean = false;
  @State supportAnimation: boolean = false;
  @State enableEdgeEffect: boolean = false;
  @State edgeEffect: EdgeEffect = EdgeEffect.None;
  @State enableEdgeEffectOptionsAlwaysEnabled: boolean = false;
  @State edgeEffectOptionsAlwaysEnabled: boolean = false;
  @State enableEnableScrollInteraction: boolean = false;
  @State enableScrollInteraction: boolean = true;
  @State enableNestedScrollScrollForward: boolean = false;
  @State nestedScrollScrollForward: NestedScrollMode = NestedScrollMode.SELF_ONLY;
  @State enableNestedScrollScrollBackward: boolean = false;
  @State nestedScrollScrollBackward: NestedScrollMode = NestedScrollMode.SELF_ONLY;
  @State enableFriction: boolean = false;
  @State friction: number = 0.75;
  @State enableAlignItems: boolean = false;
  @State alignItems: Optional<GridItemAlignment> = GridItemAlignment.DEFAULT;
  @State enableCompWidth: boolean = false;
  @State compWidth: Length = 'auto';
  @State enableCompHeight: boolean = false;
  @State compHeight: Length = 'auto';
  @State enableCompPadding: boolean = false;
  @State compPadding: number = 0;
  @State enableCompMargin: boolean = false;
  @State compMargin: number = 0;
  @State enableCompBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor = '#ff000000';
  @State enableCompBorderWidth: boolean = false;
  @State compBorderWidth: number = 0;
  @State enableCompBorderColor: boolean = false;
  @State compBorderColor: ResourceColor = Color.Black;
  @State enableCompBorderRadius: boolean = false;
  @State compBorderRadius: number = 0;
  @State enableCompBorderStyle: boolean = false;
  @State compBorderStyle: BorderStyle = BorderStyle.Solid;
  @State enableCompOpacity: boolean = false;
  @State compOpacity: number = 1;
  @State enableCompVisibility: boolean = false;
  @State compVisibility: Visibility = Visibility.Visible;
  @State enableCompDirection: boolean = false;
  @State compDirection: Direction = Direction.Auto;
  @State enableCompClip: boolean = false;
  @State compClip: boolean = false;

  @State totalCount: number = 30;
  scrollerForV: Scroller = new Scroller();
  scrollerForH: Scroller = new Scroller();
  @State currentIndex: number = 0
  @State enableDragGray: boolean = false;
  @State dragGray: DragPreviewMode = DragPreviewMode.AUTO;
  private controller: TabsController = new TabsController()
  private listScrollerForV: ListScroller = new ListScroller()
  private listScrollerForH: ListScroller = new ListScroller()
  @State dragText: string = 'drag'

  @Builder pixelMapBuilder() { //拖拽过程样式
    Column() {
      Text(this.dragText)
        .fontSize(16)
        .backgroundColor(0xF9CF93)
        .width(80)
        .height(80)
        .textAlign(TextAlign.Center)
    }
  }

  @Builder
  tabBuilder(index: number, name: string) {
    Column() {
      Text(name)
      Divider()
        .strokeWidth(2)
        .color('#007DFF')
        .opacity(this.currentIndex === index ? 1 : 0)
    }.width('100%')
  }

  getElements() {
    return Array.from({ length: this.totalCount }, (_: ESObject, index: number) => `${index}`);
  }

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex, controller: this.controller }) {
        TabContent() {
          List({scroller: this.listScrollerForV}) {
            ListItem() {
              Text('1').width('90%').textAlign(TextAlign.Center)
            }
            .height(200).backgroundColor(Color.Green).margin(10)

            ListItem() {
              Text('2').width('90%').textAlign(TextAlign.Center)
            }
            .height(200).backgroundColor(Color.Green).margin(10)

            ListItem() {
              Grid(this.scrollerForV) {
                ForEach(this.getElements(), (row: string) => {
                  GridItem() {
                  }
                  .height(80)
                  .backgroundColor('#510A59F7')
                  .borderRadius(12)
                }, (row: string) => row)
              }
              .columnsTemplate(Array(this.frCount).fill('1fr').join(' '))
              .columnsGap(useEnabled(this.enableColumnsGap, this.columnsGap))
              .rowsGap(useEnabled(this.enableRowsGap, this.rowsGap))
              .scrollBar(useEnabled(this.enableScrollBar, this.scrollBar))
              .scrollBarColor(useEnabled(this.enableScrollBarColor, this.scrollBarColor))
              .scrollBarWidth(useEnabled(this.enableScrollBarWidth, this.scrollBarWidth))
              .cachedCount(useEnabled(this.enableCachedCount, this.cachedCount))
              .editMode(useEnabled(this.enableEditMode, this.editMode))
              .layoutDirection(useEnabled(this.enableLayoutDirection, this.layoutDirection))
              .maxCount(useEnabled(this.enableMaxCount, this.maxCount))
              .minCount(useEnabled(this.enableMinCount, this.minCount))
              .cellLength(useEnabled(this.enableCellLength, this.cellLength))
              .multiSelectable(useEnabled(this.enableMultiSelectable, this.multiSelectable))
              .supportAnimation(useEnabled(this.enableSupportAnimation, this.supportAnimation))
              .edgeEffect(
                useEnabled(this.enableEdgeEffect, this.edgeEffect),
                {
                  alwaysEnabled: useEnabled(
                    this.enableEdgeEffectOptionsAlwaysEnabled,
                    this.edgeEffectOptionsAlwaysEnabled
                  )
                }
              )
              .enableScrollInteraction(useEnabled(this.enableEnableScrollInteraction, this.enableScrollInteraction))
              .nestedScroll({
                scrollForward: useEnabled(this.enableNestedScrollScrollForward, this.nestedScrollScrollForward),
                scrollBackward: useEnabled(this.enableNestedScrollScrollBackward, this.nestedScrollScrollBackward)
              })
              .friction(useEnabled(this.enableFriction, this.friction))
              .alignItems(useEnabled(this.enableAlignItems, this.alignItems))
              .width(useEnabled(this.enableCompWidth, this.compWidth))
              .height(useEnabled(this.enableCompHeight, this.compHeight))
              .padding(useEnabled(this.enableCompPadding, this.compPadding))
              .margin(useEnabled(this.enableCompMargin, this.compMargin))
              .backgroundColor(useEnabled(this.enableCompBackgroundColor, this.compBackgroundColor))
              .borderWidth(useEnabled(this.enableCompBorderWidth, this.compBorderWidth))
              .borderColor(useEnabled(this.enableCompBorderColor, this.compBorderColor))
              .borderRadius(useEnabled(this.enableCompBorderRadius, this.compBorderRadius))
              .borderStyle(useEnabled(this.enableCompBorderStyle, this.compBorderStyle))
              .opacity(useEnabled(this.enableCompOpacity, this.compOpacity))
              .visibility(useEnabled(this.enableCompVisibility, this.compVisibility))
              .direction(useEnabled(this.enableCompDirection, this.compDirection))
              .clip(useEnabled(this.enableCompClip, this.compClip))
              .fadingEdge(
                useEnabled(this.enableFadingEdge, this.fadingEdge),
                useEnabled<FadingEdgeOptions>(this.fadingEdge, {
                  fadingEdgeLength: new LengthMetrics(this.fadingEdgeLengthValue, this.fadingEdgeLengthUnit)
                })
              )
              .onDragStart(() => {})
              .dragPreviewOptions({ mode: useEnabled(this.enableDragGray, this.dragGray)})
              .onItemDragStart((event: ItemDragInfo, itemIndex: number) => { //第一次拖拽此事件绑定的组件时，触发回调。
                this.dragText = this.getElements()[itemIndex]
                return this.pixelMapBuilder() //设置拖拽过程中显示的图片。
              })
              .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
                //绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
                console.info('onItemDrop event triggered')
              })
            }
            .height(400)

            ListItem() {
              Text('4').width('90%').textAlign(TextAlign.Center)
            }
            .height(200).backgroundColor(Color.Green).margin(10)

            ListItem() {
              Text('5').width('90%').textAlign(TextAlign.Center)
            }
            .height(200).backgroundColor(Color.Green).margin(10)
          }
          .height('100%')
        }.tabBar(this.tabBuilder(0, '竖直布局'))

        TabContent() {
          List({scroller: this.listScrollerForH}) {
            ListItem() {
              Text('1').height('90%').textAlign(TextAlign.Center)
            }
            .width(150).backgroundColor(Color.Green).margin(10)

            ListItem() {
              Text('2').height('90%').textAlign(TextAlign.Center)
            }
            .width(150).backgroundColor(Color.Green).margin(10)

            ListItem() {
              Grid(this.scrollerForH) {
                ForEach(this.getElements(), (row: string) => {
                  GridItem() {
                  }
                  .width(80)
                  .backgroundColor('#510A59F7')
                  .borderRadius(12)
                }, (row: string) => row)
              }
              .rowsTemplate(Array(this.frCount).fill('1fr').join(' '))
              .columnsGap(useEnabled(this.enableColumnsGap, this.columnsGap))
              .rowsGap(useEnabled(this.enableRowsGap, this.rowsGap))
              .scrollBar(useEnabled(this.enableScrollBar, this.scrollBar))
              .scrollBarColor(useEnabled(this.enableScrollBarColor, this.scrollBarColor))
              .scrollBarWidth(useEnabled(this.enableScrollBarWidth, this.scrollBarWidth))
              .cachedCount(useEnabled(this.enableCachedCount, this.cachedCount))
              .editMode(useEnabled(this.enableEditMode, this.editMode))
              .layoutDirection(useEnabled(this.enableLayoutDirection, this.layoutDirection))
              .maxCount(useEnabled(this.enableMaxCount, this.maxCount))
              .minCount(useEnabled(this.enableMinCount, this.minCount))
              .cellLength(useEnabled(this.enableCellLength, this.cellLength))
              .multiSelectable(useEnabled(this.enableMultiSelectable, this.multiSelectable))
              .supportAnimation(useEnabled(this.enableSupportAnimation, this.supportAnimation))
              .edgeEffect(
                useEnabled(this.enableEdgeEffect, this.edgeEffect),
                {
                  alwaysEnabled: useEnabled(
                    this.enableEdgeEffectOptionsAlwaysEnabled,
                    this.edgeEffectOptionsAlwaysEnabled
                  )
                }
              )
              .enableScrollInteraction(useEnabled(this.enableEnableScrollInteraction, this.enableScrollInteraction))
              .nestedScroll({
                scrollForward: useEnabled(this.enableNestedScrollScrollForward, this.nestedScrollScrollForward),
                scrollBackward: useEnabled(this.enableNestedScrollScrollBackward, this.nestedScrollScrollBackward)
              })
              .friction(useEnabled(this.enableFriction, this.friction))
              .alignItems(useEnabled(this.enableAlignItems, this.alignItems))
              .width(useEnabled(this.enableCompWidth, this.compWidth))
              .height(useEnabled(this.enableCompHeight, this.compHeight))
              .padding(useEnabled(this.enableCompPadding, this.compPadding))
              .margin(useEnabled(this.enableCompMargin, this.compMargin))
              .backgroundColor(useEnabled(this.enableCompBackgroundColor, this.compBackgroundColor))
              .borderWidth(useEnabled(this.enableCompBorderWidth, this.compBorderWidth))
              .borderColor(useEnabled(this.enableCompBorderColor, this.compBorderColor))
              .borderRadius(useEnabled(this.enableCompBorderRadius, this.compBorderRadius))
              .borderStyle(useEnabled(this.enableCompBorderStyle, this.compBorderStyle))
              .opacity(useEnabled(this.enableCompOpacity, this.compOpacity))
              .visibility(useEnabled(this.enableCompVisibility, this.compVisibility))
              .direction(useEnabled(this.enableCompDirection, this.compDirection))
              .clip(useEnabled(this.enableCompClip, this.compClip))
              .fadingEdge(
                useEnabled(this.enableFadingEdge, this.fadingEdge),
                useEnabled<FadingEdgeOptions>(this.fadingEdge, {
                  fadingEdgeLength: new LengthMetrics(this.fadingEdgeLengthValue, this.fadingEdgeLengthUnit)
                })
              )
              .onDragStart(() => {})
              .dragPreviewOptions({ mode: useEnabled(this.enableDragGray, this.dragGray)})
              .onItemDragStart((event: ItemDragInfo, itemIndex: number) => { //第一次拖拽此事件绑定的组件时，触发回调。
                this.dragText = this.getElements()[itemIndex]
                return this.pixelMapBuilder() //设置拖拽过程中显示的图片。
              })
              .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
                //绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
                console.info('onItemDrop event triggered')
              })
            }
            .width(300)

            ListItem() {
              Text('4').height('90%').textAlign(TextAlign.Center)
            }
            .width(150).backgroundColor(Color.Green).margin(10)

            ListItem() {
              Text('5').height('90%').textAlign(TextAlign.Center)
            }
            .width(150).backgroundColor(Color.Green).margin(10)
          }
          .listDirection(Axis.Horizontal)
          .width('100%')
        }.tabBar(this.tabBuilder(1, '水平布局'))

        TabContent() {
          Grid() {
            ForEach(this.getElements(), (idx: string) => {
              GridItem() {
                Text(idx)
              }
              .height(100)
              .width(100)
              .backgroundColor('#FFFA59F7')
              .borderRadius(12)
            }, (idx: string) => idx)
          }
          .layoutDirection(useEnabled(this.enableLayoutDirection, this.layoutDirection))
          .columnsGap(useEnabled(this.enableColumnsGap, this.columnsGap))
          .rowsGap(useEnabled(this.enableRowsGap, this.rowsGap))
          .maxCount(useEnabled(this.enableMaxCount, this.maxCount))
          .minCount(useEnabled(this.enableMinCount, this.minCount))
          .cellLength(useEnabled(this.enableCellLength, this.cellLength))
          .editMode(useEnabled(this.enableEditMode, this.editMode))
          .onItemDragStart((event: ItemDragInfo, itemIndex: number) => { //第一次拖拽此事件绑定的组件时，触发回调。
            this.dragText = this.getElements()[itemIndex]
            return this.pixelMapBuilder() //设置拖拽过程中显示的图片。
          })
          .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
            //绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
            console.info('onItemDrop event triggered')
          })
          .width(useEnabled(this.enableCompWidth, this.compWidth))
          .height(useEnabled(this.enableCompHeight, this.compHeight))
        }.tabBar(this.tabBuilder(2, '可变布局'))
      }
      .onChange((index: number) => {
        this.currentIndex = index
      })
    }
    .height('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        SliderBlock({
          title: 'columnsGap',
          isEnabled: $enableColumnsGap,
          value: $columnsGap,
          min: -5,
          max: 20
        })

        SliderBlock({
          title: 'rowsGap',
          isEnabled: $enableRowsGap,
          value: $rowsGap,
          min: -5,
          max: 20
        })

        RadioBlock({
          title: 'scrollBar',
          isEnabled: $enableScrollBar,
          value: $scrollBar,
          dataSource: [
            { label: 'Off', value: BarState.Off },
            { label: 'On', value: BarState.On },
            { label: 'Auto', value: BarState.Auto }
          ]
        })

        ColorBlock({
          title: 'scrollBarColor',
          isEnabled: $enableScrollBarColor,
          color: $scrollBarColor
        })

        SliderBlock({
          title: 'scrollBarWidth',
          isEnabled: $enableScrollBarWidth,
          value: $scrollBarWidth,
          min: 1,
          max: 8
        })

        SliderBlock({
          title: 'cachedCount',
          isEnabled: $enableCachedCount,
          value: $cachedCount,
          min: 0,
          max: 50
        })

        RadioBlock({
          title: 'editMode',
          isEnabled: $enableEditMode,
          value: $editMode,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'layoutDirection',
          isEnabled: $enableLayoutDirection,
          value: $layoutDirection,
          dataSource: [
            { label: 'Row', value: GridDirection.Row },
            { label: 'Column', value: GridDirection.Column },
            { label: 'RowReverse', value: GridDirection.RowReverse },
            { label: 'ColumnReverse', value: GridDirection.ColumnReverse }
          ]
        })

        SliderBlock({
          title: 'maxCount',
          isEnabled: $enableMaxCount,
          value: $maxCount,
          min: 0,
          max: 20
        })

        SliderBlock({
          title: 'minCount',
          isEnabled: $enableMinCount,
          value: $minCount,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'cellLength',
          isEnabled: $enableCellLength,
          value: $cellLength,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'multiSelectable',
          isEnabled: $enableMultiSelectable,
          value: $multiSelectable,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'supportAnimation',
          isEnabled: $enableSupportAnimation,
          value: $supportAnimation,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'edgeEffect',
          isEnabled: $enableEdgeEffect,
          value: $edgeEffect,
          dataSource: [
            { label: 'Spring', value: EdgeEffect.Spring },
            { label: 'Fade', value: EdgeEffect.Fade },
            { label: 'None', value: EdgeEffect.None }
          ]
        })

        RadioBlock({
          title: 'edgeEffect.options.alwaysEnabled',
          isEnabled: $enableEdgeEffectOptionsAlwaysEnabled,
          value: $edgeEffectOptionsAlwaysEnabled,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'enableScrollInteraction',
          isEnabled: $enableEnableScrollInteraction,
          value: $enableScrollInteraction,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'nestedScroll.scrollForward',
          isEnabled: $enableNestedScrollScrollForward,
          value: $nestedScrollScrollForward,
          dataSource: [
            { label: 'SELF_ONLY', value: NestedScrollMode.SELF_ONLY },
            { label: 'SELF_FIRST', value: NestedScrollMode.SELF_FIRST },
            { label: 'PARENT_FIRST', value: NestedScrollMode.PARENT_FIRST },
            { label: 'PARALLEL', value: NestedScrollMode.PARALLEL }
          ]
        })

        RadioBlock({
          title: 'nestedScroll.scrollBackward',
          isEnabled: $enableNestedScrollScrollBackward,
          value: $nestedScrollScrollBackward,
          dataSource: [
            { label: 'SELF_ONLY', value: NestedScrollMode.SELF_ONLY },
            { label: 'SELF_FIRST', value: NestedScrollMode.SELF_FIRST },
            { label: 'PARENT_FIRST', value: NestedScrollMode.PARENT_FIRST },
            { label: 'PARALLEL', value: NestedScrollMode.PARALLEL }
          ]
        })

        SliderBlock({
          title: 'friction',
          isEnabled: $enableFriction,
          value: $friction,
          min: 0,
          max: 1,
          step: 0.05
        })

        RadioBlock({
          title: 'alignItems',
          isEnabled: $enableAlignItems,
          value: $alignItems,
          dataSource: [
            { label: 'DEFAULT', value: GridItemAlignment.DEFAULT },
            { label: 'STRETCH', value: GridItemAlignment.STRETCH }
          ]
        })

        RadioBlock({
          title: 'fadingEdge',
          isEnabled: $enableFadingEdge,
          value: $fadingEdge,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        if (this.fadingEdge) {
          SliderBlock({
            title: 'fadingEdge.length',
            isEnabled: $enableFadingEdgeLengthValue,
            value: $fadingEdgeLengthValue,
            min: 0,
            max: 500
          })
          RadioBlock({
            title: 'fadingEdge.length.unit',
            isEnabled: $enableFadingEdgeLengthUnit,
            value: $fadingEdgeLengthUnit,
            dataSource: [
              { label: 'px', value: LengthUnit.PX },
              { label: 'vp', value: LengthUnit.VP },
              { label: 'fp', value: LengthUnit.FP },
              { label: 'percent', value: LengthUnit.PERCENT },
              { label: 'lpx', value: LengthUnit.LPX }
            ]
          })
        }

        SliderBlock({
          title: 'frCount',
          isEnabled: $enableFrCount,
          value: $frCount,
          min: 1,
          max: 6
        })

        RadioBlock({
          title: '拖拽背板图样式',
          isEnabled: $enableDragGray,
          value: $dragGray,
          dataSource: [
            { label: '默认', value: DragPreviewMode.AUTO },
            { label: '灰显', value: DragPreviewMode.ENABLE_DRAG_ITEM_GRAY_EFFECT }
          ]
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableCompWidth,
          value: $compWidth,
          min: 100,
          max: 600
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableCompHeight,
          value: $compHeight,
          min: 50,
          max: 400
        })

        SliderBlock({
          title: 'padding',
          isEnabled: $enableCompPadding,
          value: $compPadding,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'margin',
          isEnabled: $enableCompMargin,
          value: $compMargin,
          min: 0,
          max: 100
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableCompBackgroundColor,
          color: $compBackgroundColor
        })

        SliderBlock({
          title: 'borderWidth',
          isEnabled: $enableCompBorderWidth,
          value: $compBorderWidth,
          min: 0,
          max: 20
        })

        ColorBlock({
          title: 'borderColor',
          isEnabled: $enableCompBorderColor,
          color: $compBorderColor
        })

        SliderBlock({
          title: 'borderRadius',
          isEnabled: $enableCompBorderRadius,
          value: $compBorderRadius,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'borderStyle',
          isEnabled: $enableCompBorderStyle,
          value: $compBorderStyle,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        SliderBlock({
          title: 'opacity',
          isEnabled: $enableCompOpacity,
          value: $compOpacity,
          min: 0,
          max: 1,
          step: 0.1
        })

        RadioBlock({
          title: 'visibility',
          isEnabled: $enableCompVisibility,
          value: $compVisibility,
          dataSource: [
            { label: 'None', value: Visibility.None },
            { label: 'Hidden', value: Visibility.Hidden },
            { label: 'Visible', value: Visibility.Visible }
          ]
        })

        RadioBlock({
          title: 'direction',
          isEnabled: $enableCompDirection,
          value: $compDirection,
          dataSource: [
            { label: 'Auto', value: Direction.Auto },
            { label: 'Ltr', value: Direction.Ltr },
            { label: 'Rtl', value: Direction.Rtl }
          ]
        })

        RadioBlock({
          title: 'clip',
          isEnabled: $enableCompClip,
          value: $compClip,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
      }
      .width('100%')
    }
    .align(Alignment.Top)
    .height('50%')
  }
}

@Preview
@Component
struct GridBootcampPreviewer {
  build() {
    GridBootcamp({
      title: '网格/Grid'
    })
  }
}