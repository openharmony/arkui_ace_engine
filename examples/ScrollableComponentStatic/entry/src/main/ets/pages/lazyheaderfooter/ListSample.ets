'use static'

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
  Entry,
  ComponentV2,
  Builder,
  Column,
  ColumnOptions,
  Row,
  RowOptions,
  List,
  Text,
  Button,
  Color,
  FontWeight,
  TextAlign,
  EdgeEffect,
  ResourceColor,
  LazyForEach,
  StickyStyle,
  LazyVGridLayout,
  LazyVGridLayoutAttribute,
} from '@ohos.arkui.component'
import { Local } from '@ohos.arkui.stateManagement'
import { LengthMetrics } from '@ohos.arkui.node'
import { LazyColumnLayout, LazyColumnLayoutAttribute } from '@ohos.arkui.components.ArkLazyColumnLayout'
import { LazyVWaterFlowLayout, LazyVWaterFlowLayoutAttribute } from '@ohos.arkui.components.ArkLazyWaterFlowLayout'
import { LazyDataSource } from './DataSource'

@Entry
@ComponentV2
struct ListSample {
  private arr1: LazyDataSource = new LazyDataSource()
  private arr2: LazyDataSource = new LazyDataSource()
  private arr3: LazyDataSource = new LazyDataSource()

  @Local private visibleText: string = 'visible: -'
  @Local private totalText: string = 'total: 0'

  @Local private outerStickyHeader: boolean = true
  @Local private outerStickyFooter: boolean = true
  @Local private outerShowHeader: boolean = true
  @Local private outerShowFooter: boolean = true

  @Local private gridStickyHeader: boolean = true
  @Local private gridStickyFooter: boolean = true
  @Local private gridShowHeader: boolean = true
  @Local private gridShowFooter: boolean = true

  @Local private wfStickyHeader: boolean = true
  @Local private wfStickyFooter: boolean = true
  @Local private wfShowHeader: boolean = true
  @Local private wfShowFooter: boolean = true

  private computeSticky(header: boolean, footer: boolean): StickyStyle | undefined {
    if (header && footer) {
      return StickyStyle.BOTH
    }
    if (header) {
      return StickyStyle.Header
    }
    if (footer) {
      return StickyStyle.Footer
    }
    return undefined
  }

  private stickyLabel(header: boolean, footer: boolean): string {
    if (header && footer) {
      return 'BOTH'
    }
    if (header) {
      return 'Header'
    }
    if (footer) {
      return 'Footer'
    }
    return 'undefined'
  }

  aboutToAppear(): void {
    for (let i: int = 0; i < 20; i++) {
      this.arr1.pushData(i.toString())
    }
    for (let i: int = 0; i < 25; i++) {
      this.arr2.pushData(i.toString())
    }
    for (let i: int = 0; i < 15; i++) {
      this.arr3.pushData(i.toString())
    }
  }

  @Builder
  StickyPanel(title: string, label: string, headerShown: boolean, footerShown: boolean, bg: ResourceColor,
    onHeader: () => void, onFooter: () => void, onBoth: () => void, onNone: () => void,
    onToggleHeader: () => void, onToggleFooter: () => void): void {
    Column({ space: 4 } as ColumnOptions) {
      Text(title + '   sticky = ' + label)
        .fontSize(12)
        .fontWeight(FontWeight.Bold)
        .fontColor('#0B3D66')
        .width('100%')
      Row({ space: 4 } as RowOptions) {
        Button('Header').layoutWeight(1).fontSize(11).height(28).onClick(onHeader)
        Button('Footer').layoutWeight(1).fontSize(11).height(28).onClick(onFooter)
        Button('Both').layoutWeight(1).fontSize(11).height(28).onClick(onBoth)
        Button('None').layoutWeight(1).fontSize(11).height(28).onClick(onNone)
      }
      .width('100%')
      Row({ space: 4 } as RowOptions) {
        Button('Header: ' + (headerShown ? 'ON' : 'OFF'))
          .layoutWeight(1).fontSize(11).height(28)
          .backgroundColor(headerShown ? '#4A90E2' : '#999')
          .onClick(onToggleHeader)
        Button('Footer: ' + (footerShown ? 'ON' : 'OFF'))
          .layoutWeight(1).fontSize(11).height(28)
          .backgroundColor(footerShown ? '#4A90E2' : '#999')
          .onClick(onToggleFooter)
      }
      .width('100%')
    }
    .width('92%')
    .padding(6)
    .backgroundColor(bg)
    .borderRadius(6)
    .margin({ bottom: 4 })
  }

  @Builder
  HeaderBuilder(title: string, bg: ResourceColor): void {
    Column({ space: 3 } as ColumnOptions) {
      Text(title)
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#0B3D66')
      Text(this.visibleText + ', ' + this.totalText)
        .fontSize(12)
        .fontColor('#31556F')
    }
    .width('100%')
    .padding(8)
    .backgroundColor(bg)
  }

  @Builder
  FooterBuilder(label: string, bg: ResourceColor): void {
    Text(label)
      .height(44)
      .width('100%')
      .fontSize(14)
      .backgroundColor(bg)
      .textAlign(TextAlign.Center)
  }

  build(): void {
    Column(undefined) {
      this.StickyPanel(
        '[Outer] LazyColumnLayout',
        this.stickyLabel(this.outerStickyHeader, this.outerStickyFooter),
        this.outerShowHeader, this.outerShowFooter,
        '#DCEEFF',
        () => { this.outerStickyHeader = true; this.outerStickyFooter = false },
        () => { this.outerStickyHeader = false; this.outerStickyFooter = true },
        () => { this.outerStickyHeader = true; this.outerStickyFooter = true },
        () => { this.outerStickyHeader = false; this.outerStickyFooter = false },
        () => { this.outerShowHeader = !this.outerShowHeader },
        () => { this.outerShowFooter = !this.outerShowFooter }
      )
      this.StickyPanel(
        '[GridB] LazyVGridLayout',
        this.stickyLabel(this.gridStickyHeader, this.gridStickyFooter),
        this.gridShowHeader, this.gridShowFooter,
        '#FFE7C2',
        () => { this.gridStickyHeader = true; this.gridStickyFooter = false },
        () => { this.gridStickyHeader = false; this.gridStickyFooter = true },
        () => { this.gridStickyHeader = true; this.gridStickyFooter = true },
        () => { this.gridStickyHeader = false; this.gridStickyFooter = false },
        () => { this.gridShowHeader = !this.gridShowHeader },
        () => { this.gridShowFooter = !this.gridShowFooter }
      )
      this.StickyPanel(
        '[WF] LazyVWaterFlowLayout',
        this.stickyLabel(this.wfStickyHeader, this.wfStickyFooter),
        this.wfShowHeader, this.wfShowFooter,
        '#C8F1C8',
        () => { this.wfStickyHeader = true; this.wfStickyFooter = false },
        () => { this.wfStickyHeader = false; this.wfStickyFooter = true },
        () => { this.wfStickyHeader = true; this.wfStickyFooter = true },
        () => { this.wfStickyHeader = false; this.wfStickyFooter = false },
        () => { this.wfShowHeader = !this.wfShowHeader },
        () => { this.wfShowFooter = !this.wfShowFooter }
      )

      List() {
        LazyColumnLayout() {
          LazyVGridLayout() {
            LazyForEach(this.arr1, (item: string) => {
              Text('GridA item' + item)
                .height(80)
                .width('100%')
                .borderWidth(1)
                .backgroundColor(Color.Red)
                .textAlign(TextAlign.Center)
            }, (item: string): string => item)
          }

          LazyVGridLayout() {
            LazyForEach(this.arr2, (item: string) => {
              Text('GridB item' + item)
                .height(80)
                .width('100%')
                .borderWidth(1)
                .backgroundColor(Color.Orange)
                .textAlign(TextAlign.Center)
            }, (item: string): string => item)
          }
          .header(this.gridShowHeader ? ((): void => { this.HeaderBuilder('[GridB] LazyVGridLayout header', '#FFE7C2') }) : undefined)
          .footer(this.gridShowFooter ? ((): void => { this.FooterBuilder('[GridB] LazyVGridLayout footer', '#FFD699') }) : undefined)
          .sticky(this.computeSticky(this.gridStickyHeader, this.gridStickyFooter))

          LazyVWaterFlowLayout() {
            LazyForEach(this.arr3, (item: string) => {
              Text('WF item' + item)
                .height(80)
                .width('100%')
                .borderWidth(1)
                .backgroundColor(Color.Green)
                .textAlign(TextAlign.Center)
            }, (item: string): string => item)
          }
          .columnsTemplate('1fr')
          .header(this.wfShowHeader ? ((): void => { this.HeaderBuilder('[WF] LazyVWaterFlowLayout header', '#C8F1C8') }) : undefined)
          .footer(this.wfShowFooter ? ((): void => { this.FooterBuilder('[WF] LazyVWaterFlowLayout footer', '#A6E3A6') }) : undefined)
          .sticky(this.computeSticky(this.wfStickyHeader, this.wfStickyFooter))
        }
        .space(LengthMetrics.vp(20))
        .header(this.outerShowHeader ? ((): void => { this.HeaderBuilder('[Outer] LazyColumnLayout header (under List)', '#DCEEFF') }) : undefined)
        .footer(this.outerShowFooter ? ((): void => { this.FooterBuilder('[Outer] LazyColumnLayout footer (under List)', '#B7DCFF') }) : undefined)
        .sticky(this.computeSticky(this.outerStickyHeader, this.outerStickyFooter))
      }
      .width('92%')
      .layoutWeight(1)
      .borderWidth(1)
      .edgeEffect(EdgeEffect.Spring)
    }
    .width('100%')
    .height('100%')
  }
}
