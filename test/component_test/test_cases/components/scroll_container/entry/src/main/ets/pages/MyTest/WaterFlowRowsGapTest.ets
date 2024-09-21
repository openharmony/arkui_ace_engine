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

export default async function waterFlowRowsGapTest() {
  /*
* WaterFlow组件 rowsGap属性
* 找到画面id为waterFlowRowsGap1,waterFlowRowsGap2的waterFlow组件
* 找到画面文本为WaterFlowRowsGap的button组件
* 获取waterFlow1的rowsGap属性与期待值$r('app.string.length')比对
* 获取waterFlow2的rowsGap属性与期待值10比对
* 点击button，变更waterFlow2的rowsGap属性值为'80.00px'
* 获取waterFlow2的rowsGap属性与期待值'80.00px'比对
*/
  defineTest('waterFlowRowsGapTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowRowsGapTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow1: Component = await driver.findComponent(Matcher.create().id('waterFlowRowsGap1').enabled(true))
    let waterFlow2: Component = await driver.findComponent(Matcher.create().id('waterFlowRowsGap2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('WaterFlowRowsGap').enabled(true))

    let rowsGap1: string = await waterFlow1.getInspectorInfo()
    assertEqual(JSON.parse(rowsGap1).$attrs.rowsGap, $r('app.string.length'))
    let rowsGap2: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(rowsGap2).$attrs.rowsGap, '10.00vp')
    await button.tap()
    let rowsGap3: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(rowsGap3).$attrs.rowsGap, '80.00px')
  }, 0)
}