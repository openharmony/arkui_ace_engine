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
import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function waterFlowLayoutDirectionTest() {
  /*
* WaterFlow组件  layoutDirection属性
* 找到画面id为waterFlowLayoutDirection1,waterFlowLayoutDirection2的waterFlow组件
* 找到画面文本为WaterFlowLayoutDirection1,WaterFlowLayoutDirection2的button组件
* 获取waterFlow1的layoutDirection属性与期待值FlexDirection.Column比对
* 获取waterFlow2的layoutDirection属性与期待值FlexDirection.Row比对
* 点击button1，变更waterFlow2的layoutDirection属性值为FlexDirection.ColumnReverse
* 获取waterFlow2的layoutDirection属性与期待值FlexDirection.ColumnReverse比对
* 点击button2，变更waterFlow2的layoutDirection属性值为FlexDirection.RowReverse
* 获取waterFlow2的layoutDirection属性与期待值FlexDirection.RowReverse比对
*/
  defineTest('waterFlowLayoutDirectionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowLayoutDirectionTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow1: Component =
      await driver.findComponent(Matcher.create().id('waterFlowLayoutDirection1').enabled(true))
    let waterFlow2: Component =
      await driver.findComponent(Matcher.create().id('waterFlowLayoutDirection2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('WaterFlowLayoutDirection1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('WaterFlowLayoutDirection2').enabled(true))

    let itemConstraintSize1: string = await waterFlow1.getInspectorInfo()
    assertFalse(JSON.parse(itemConstraintSize1).$attrs.layoutDirection == undefined)
    assertEqual(JSON.parse(itemConstraintSize1).$attrs.layoutDirection, 'FlexDirection.Column')
    let itemConstraintSize2: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(itemConstraintSize2).$attrs.layoutDirection, 'FlexDirection.Row')
    await button1.tap()
    let itemConstraintSize3: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(itemConstraintSize3).$attrs.layoutDirection, 'FlexDirection.ColumnReverse')
    await button2.tap()
    let itemConstraintSize4: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(itemConstraintSize4).$attrs.layoutDirection, 'FlexDirection.RowReverse')
  }, 0)
}