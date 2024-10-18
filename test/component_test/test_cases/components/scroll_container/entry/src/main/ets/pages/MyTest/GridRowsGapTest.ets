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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function gridRowsGapTest() {
  /*
  * Grid组件 RowsGap属性
  * 找到画面id为gridRowsGap1，gridRowsGap2，gridRowsGap3的Grid组件
  * 找到画面文本为GridRowsGap的Button组件
  * 获取gridRowsGap1的RowsGap属性与期待值2.00vp比对
  * 获取gridRowsGap2的RowsGap属性与期待值'0.00vp'比对
  * 获取gridRowsGap3的RowsGap属性与期待值'15.00px'比对
  * 点击button，变更gridRowsGap3的RowsGap属性值为$r('app.string.length')
  * 获取gridRowsGap3的RowsGap属性与期待值$r('app.string.length')比对
  */
  defineTest('gridRowsGapTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridRowsGapTestDemo running')
    let driver: Tester = Tester.create()
    let gridRowsGap1: Component = await driver.findComponent(Matcher.create().id('gridRowsGap1').enabled(true))
    let gridRowsGap2: Component = await driver.findComponent(Matcher.create().id('gridRowsGap2').enabled(true))
    let gridRowsGap3: Component = await driver.findComponent(Matcher.create().id('gridRowsGap3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridRowsGap').enabled(true))
    let rowsGap1: string = await gridRowsGap1.getInspectorInfo()
    assertEqual(JSON.parse(rowsGap1).$attrs.rowsGap, '2.00vp')
    let rowsGap2: string = await gridRowsGap2.getInspectorInfo()
    assertEqual(JSON.parse(rowsGap2).$attrs.rowsGap, '0.00vp')
    let rowsGap3: string = await gridRowsGap3.getInspectorInfo()
    assertEqual(JSON.parse(rowsGap3).$attrs.rowsGap, '15.00px')
    await button.tap()
    let rowsGap4: string = await gridRowsGap3.getInspectorInfo()
    assertEqual(JSON.parse(rowsGap4).$attrs.rowsGap, $r('app.string.length'))
  }, 0)
}