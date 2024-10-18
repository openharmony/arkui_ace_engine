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

export default async function gridColumnsGapTest() {
  /*
  * Grid组件 ColumnsGap属性
  * 找到画面id为gridColumnsGap1，gridColumnsGap2，gridColumnsGap3的Grid组件
  * 找到画面文本为GridColumnsGap的Button组件
  * 获取gridColumnsGap1的ColumnsGap属性与期待值'15.00px'比对
  * 获取gridColumnsGap2的ColumnsGap属性与期待值'0.00vp'比对
  * 获取gridColumnsGap3的ColumnsGap属性与期待值'10.00vp'比对
  * 点击button，变更gridColumnsGap3的ColumnsGap属性值为$r('app.float.ListLanes_float'))
  * 获取gridColumnsGap3的ColumnsGap属性与期待值$r('app.float.ListLanes_float'))比对
  */
  defineTest('gridColumnsGapTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridColumnsGapTestDemo running')
    let driver: Tester = Tester.create()
    let gridColumnsGap1: Component = await driver.findComponent(Matcher.create().id('gridColumnsGap1').enabled(true))
    let gridColumnsGap2: Component = await driver.findComponent(Matcher.create().id('gridColumnsGap2').enabled(true))
    let gridColumnsGap3: Component = await driver.findComponent(Matcher.create().id('gridColumnsGap3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridColumnsGap').enabled(true))
    let columnsGap1: string = await gridColumnsGap1.getInspectorInfo()
    assertEqual(JSON.parse(columnsGap1).$attrs.columnsGap, '15.00px')
    let columnsGap2: string = await gridColumnsGap2.getInspectorInfo()
    assertEqual(JSON.parse(columnsGap2).$attrs.columnsGap, '0.00vp')
    let columnsGap3: string = await gridColumnsGap3.getInspectorInfo()
    assertEqual(JSON.parse(columnsGap3).$attrs.columnsGap, '10.00vp')
    await button.tap()
    let columnsGap4: string = await gridColumnsGap3.getInspectorInfo()
    assertEqual(JSON.parse(columnsGap4).$attrs.columnsGap, $r('app.float.ListLanes_float'))
  }, 0)
}