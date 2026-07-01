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
  LazyColumnLayout,
  LazyColumnLayoutAttribute,
  LazyVWaterFlowLayout,
  LazyVWaterFlowLayoutAttribute,
  LengthMetrics
} from '@kit.ArkUI'
import { LazyDataSource } from './DataSource'

export enum LazyHeaderFooterHost {
  SCROLL,
  LIST,
  WATER_FLOW
}

@Component
export struct LazyHeaderFooterSampleView {
  @Prop host: LazyHeaderFooterHost = LazyHeaderFooterHost.SCROLL

  private arr1: LazyDataSource = new LazyDataSource()
  private arr2: LazyDataSource = new LazyDataSource()
  private arr3: LazyDataSource = new LazyDataSource()

  @State private visibleText: string = 'visible: -'
  @State private totalText: string = 'total: 0'

  @State private outerStickyHeader: boolean = true
  @State private outerStickyFooter: boolean = true
  @State private outerShowHeader: boolean = true
  @State private outerShowFooter: boolean = true

  @State private gridStickyHeader: boolean = true
  @State private gridStickyFooter: boolean = true
  @State private gridShowHeader: boolean = true
  @State private gridShowFooter: boolean = true

  @State private wfStickyHeader: boolean = true
  @State private wfStickyFooter: boolean = true
  @State private wfShowHeader: boolean = true
  @State private wfShowFooter: boolean = true

  private computeSticky(header: boolean, footer: boolean): StickyStyle {
    if (header && footer) {
      return (StickyStyle.Header | StickyStyle.Footer) as StickyStyle
    }
    if (header) {
      return StickyStyle.Header
    }
    if (footer) {
      return StickyStyle.Footer
    }
    return 0 as StickyStyle
  }

  private stickyLabel(header: boolean, footer: boolean): string {
    if (header && footer) {
      return 'Both'
    }
    if (header) {
      return 'Header'
    }
    if (footer) {
      return 'Footer'
    }
    return 'None'
  }

  aboutToAppear(): void {
    for (let i = 0; i < 20; i++) {
      this.arr1.pushData(i.toString())
    }
    for (let i = 0; i < 25; i++) {
      this.arr2.pushData(i.toString())
    }
    for (let i = 0; i < 15; i++) {
      this.arr3.pushData(i.toString())
    }
    this.totalText = 'total: ' + (this.arr1.totalCount() + this.arr2.totalCount() + this.arr3.totalCount()).toString()
  }

  @Builder
  StickyPanel(title: string, label: string, headerShown: boolean, footerShown: boolean, bg: ResourceColor,
    onHeader: () => void, onFooter: () => void, onBoth: () => void, onNone: () => void,
    onToggleHeader: () => void, onToggleFooter: () => void) {
    Column({ space: 4 }) {
      Text(title + '   sticky = ' + label)
        .fontSize(12)
        .fontWeight(FontWeight.Bold)
        .fontColor('#0B3D66')
        .width('100%')
      Row({ space: 4 }) {
        Button('Header').layoutWeight(1).fontSize(11).height(28).onClick(onHeader)
        Button('Footer').layoutWeight(1).fontSize(11).height(28).onClick(onFooter)
        Button('Both').layoutWeight(1).fontSize(11).height(28).onClick(onBoth)
        Button('None').layoutWeight(1).fontSize(11).height(28).onClick(onNone)
      }
      .width('100%')
      Row({ space: 4 }) {
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
  HeaderBuilder(title: string, bg: ResourceColor) {
    Column({ space: 3 }) {
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
  FooterBuilder(label: string, bg: ResourceColor) {
    Text(label)
      .height(44)
      .width('100%')
      .fontSize(14)
      .backgroundColor(bg)
      .textAlign(TextAlign.Center)
  }

  @Builder
  LazyContent(hostName: string) {
    LazyColumnLayout() {
      LazyVGridLayout() {
        LazyForEach(this.arr1, (item: string) => {
          Text('GridA item' + item)
            .height(80)
            .width('100%')
            .borderWidth(1)
            .backgroundColor(Color.Red)
            .textAlign(TextAlign.Center)
        })
      }

      LazyVGridLayout() {
        LazyForEach(this.arr2, (item: string) => {
          Text('GridB item' + item)
            .height(80)
            .width('100%')
            .borderWidth(1)
            .backgroundColor(Color.Orange)
            .textAlign(TextAlign.Center)
        })
      }
      .header(this.gridShowHeader ? this.HeaderBuilder('[GridB] LazyVGridLayout header', '#FFE7C2') : undefined)
      .footer(this.gridShowFooter ? this.FooterBuilder('[GridB] LazyVGridLayout footer', '#FFD699') : undefined)
      .sticky(this.computeSticky(this.gridStickyHeader, this.gridStickyFooter))

      LazyVWaterFlowLayout() {
        LazyForEach(this.arr3, (item: string) => {
          Text('WF item' + item)
            .height(80)
            .width('100%')
            .borderWidth(1)
            .backgroundColor(Color.Green)
            .textAlign(TextAlign.Center)
        })
      }
      .columnsTemplate('1fr')
      .header(this.wfShowHeader ? this.HeaderBuilder('[WF] LazyVWaterFlowLayout header', '#C8F1C8') : undefined)
      .footer(this.wfShowFooter ? this.FooterBuilder('[WF] LazyVWaterFlowLayout footer', '#A6E3A6') : undefined)
      .sticky(this.computeSticky(this.wfStickyHeader, this.wfStickyFooter))
    }
    .space(LengthMetrics.vp(20))
    .header(this.outerShowHeader ? this.HeaderBuilder('[Outer] LazyColumnLayout header (under ' + hostName + ')',
      '#DCEEFF') : undefined)
    .footer(this.outerShowFooter ? this.FooterBuilder('[Outer] LazyColumnLayout footer (under ' + hostName + ')',
      '#B7DCFF') : undefined)
    .sticky(this.computeSticky(this.outerStickyHeader, this.outerStickyFooter))
    .onVisibleIndexesChange((start: number, end: number) => {
      this.visibleText = 'visible: ' + start.toString() + '-' + end.toString()
    })
  }

  @Builder
  ScrollHost() {
    Scroll() {
      this.LazyContent('Scroll')
    }
    .width('92%')
    .layoutWeight(1)
    .borderWidth(1)
    .edgeEffect(EdgeEffect.Spring)
  }

  @Builder
  ListHost() {
    List() {
      this.LazyContent('List')
    }
    .width('92%')
    .layoutWeight(1)
    .borderWidth(1)
    .edgeEffect(EdgeEffect.Spring)
  }

  @Builder
  WaterFlowHost() {
    WaterFlow({ layoutMode: WaterFlowLayoutMode.SLIDING_WINDOW }) {
      this.LazyContent('WaterFlow')
    }
    .columnsTemplate('1fr')
    .width('92%')
    .layoutWeight(1)
    .borderWidth(1)
    .edgeEffect(EdgeEffect.Spring)
  }

  build() {
    Column() {
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

      if (this.host === LazyHeaderFooterHost.LIST) {
        this.ListHost()
      } else if (this.host === LazyHeaderFooterHost.WATER_FLOW) {
        this.WaterFlowHost()
      } else {
        this.ScrollHost()
      }
    }
    .width('100%')
    .height('100%')
  }
}
