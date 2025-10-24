'use static'
/**
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
import { UIUtils } from '@kit.ArkUI';
import {
  DataReloadOperation,
  DataOperationType,
  Entry,
  Text,
  TextAttribute,
  Column,
  Component,
  Stack,
  WaterFlow,
  LazyForEach,
  FlowItem,
  DataOperation,
  Color,
  TextAlign,
  DataChangeListener,
  IDataSource,
  Button,
  ButtonAttribute,
  ClickEvent,

  Image,
  Search,
  Row,
  Column,
  SearchController,ComponentV2,ForEach,
  ColumnOptions,WaterFlowSections,Scroller,SectionOptions
} from '@ohos.arkui.component'
import { State, Link, Prop,Local } from '@ohos.arkui.stateManagement'
import { AppStorage } from '@ohos.arkui.stateManagement';
import { UIContext, Router } from '@ohos.arkui.UIContext';
import common from '@ohos.app.ability.common';

@Entry
@ComponentV2
struct makeObserved0140 {
  colors: Array<string> = ['#FFC0CB', '#DA70D6', '#6B8E23', '#6A5ACD', '#00FFFF', '#00FF7F'] as Array<string>
  sections: WaterFlowSections = UIUtils.makeObserved(new WaterFlowSections())
  scroller: Scroller = new Scroller()
  @Local private arr: Array<number> = new Array<number>(8).fill(0)
  oneColumnSection: SectionOptions = {
    itemsCount: 3,
    crossCount: 1,
  } as SectionOptions
  twoColumnSection: SectionOptions = {
    itemsCount: 2,
    crossCount: 2,
  } as SectionOptions
  lastSection: SectionOptions = {
    itemsCount: 3,
    crossCount: 3
  } as SectionOptions

  aboutToAppear(): void {
    let sectionOptions: Array<SectionOptions> = [this.oneColumnSection, this.twoColumnSection, this.lastSection] as Array<SectionOptions>
    this.sections.splice(0, 0, sectionOptions)
  }

  build() {
    Column() {
      Text(`${this.arr.length}`).height('5%')
      Button('push option').height('5%').onClick(():void => {
        this.arr.push(100)
        this.arr.push(101)
        this.arr.push(102)
        this.arr.push(103)
        let section: SectionOptions = { itemsCount: 4, crossCount: 2 } as SectionOptions
        this.sections.push(section)
      }).id('buttonPush')
      Button('splice option').height('5%').onClick(():void => {
        let section: SectionOptions = { itemsCount: 12, crossCount: 3 } as SectionOptions
        this.sections.splice(0, this.arr.length, [section])
      }).id('buttonSplice')
      Button('update option').height('5%').onClick(():void => {
        let section: SectionOptions = { itemsCount: 12, crossCount: 4 } as SectionOptions
        this.sections.update(0, section)
      }).id('buttonUpdate')
      WaterFlow({ scroller: this.scroller, sections: this.sections }) {
        ForEach(this.arr, (item: number, index: int) => {
          FlowItem() {
            Text(`${item}`)
              .border({ width: 1 })
              .backgroundColor(this.colors[(index % 6) as int ])
              .height('5%')
              .id(`flowItem${index}`)
          }
        })
      }.id('waterFlowTest')
    }
  }
}