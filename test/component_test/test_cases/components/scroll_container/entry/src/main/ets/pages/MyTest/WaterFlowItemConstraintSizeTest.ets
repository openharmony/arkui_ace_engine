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

export default async function waterFlowItemConstraintSizeTest() {
  /*
* WaterFlow组件  friction属性
* 找到画面id为waterFlowItemConstraintSize1,waterFlowItemConstraintSize2的waterFlow组件
* 找到画面文本为WaterFlowItemConstraintSize的button组件
* 获取waterFlow1的itemConstraintSize属性与期待值$r('app.string.length'),$r('app.string.length'),$r('app.string.length'),$r('app.string.length')比对
* 获取waterFlow2的itemConstraintSize属性与期待值'0.00vp','600.00vp','0.00vp','600.00vp'比对
* 点击button，变更waterFlow1的itemConstraintSize属性值为0,600,0,600
* 获取waterFlow1的itemConstraintSize属性与期待值0.00%,100.00%,0.00%,100.00%比对
*/
  defineTest('waterFlowItemConstraintSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowItemConstraintSizeTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow1: Component =
      await driver.findComponent(Matcher.create().id('waterFlowItemConstraintSize1').enabled(true))
    let waterFlow2: Component =
      await driver.findComponent(Matcher.create().id('waterFlowItemConstraintSize2').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('WaterFlowItemConstraintSize').enabled(true))

    let itemConstraintSize1: string = await waterFlow1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize1).$attrs.itemConstraintSize).minWidth, $r('app.string.length'))
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize1).$attrs.itemConstraintSize).maxWidth, $r('app.string.length'))
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize1).$attrs.itemConstraintSize).minHeight,
      $r('app.string.length'))
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize1).$attrs.itemConstraintSize).maxHeight,
      $r('app.string.length'))
    let itemConstraintSize2: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize2).$attrs.itemConstraintSize).minWidth, '0.00vp')
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize2).$attrs.itemConstraintSize).maxWidth, '600.00vp')
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize2).$attrs.itemConstraintSize).minHeight, '0.00vp')
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize2).$attrs.itemConstraintSize).maxHeight, '600.00vp')
    await button.tap()
    let itemConstraintSize3: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize3).$attrs.itemConstraintSize).minWidth, '0.00%')
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize3).$attrs.itemConstraintSize).maxWidth, '100.00%')
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize3).$attrs.itemConstraintSize).minHeight, '0.00%')
    assertEqual(JSON.parse(JSON.parse(itemConstraintSize3).$attrs.itemConstraintSize).maxHeight, '100.00%')
  }, 0)
}