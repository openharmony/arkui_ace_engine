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

export default async function waterFlowScrollBarWidthTest() {
  /*
* WaterFlow组件  scrollBarWidth属性
* 找到画面id为waterFlowScrollBarWidth1,waterFlowScrollBarWidth2的waterFlow组件
* 找到画面文本为WaterFlowScrollBarWidth的button组件
* 获取waterFlow1的scrollBarWidth属性与期待值'20.00vp'比对
* 获取waterFlow2的scrollBarWidth属性与期待值'10000000.00vp'比对
* 点击button，变更waterFlow1的scrollBarWidth属性值为'30.00vp'
* 获取waterFlow1的scrollBarWidth属性与期待值'30.00vp'比对
*/
  defineTest('waterFlowScrollBarWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowScrollBarWidthTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow1: Component =
      await driver.findComponent(Matcher.create().id('waterFlowScrollBarWidth1').enabled(true))
    let waterFlow2: Component =
      await driver.findComponent(Matcher.create().id('waterFlowScrollBarWidth2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('WaterFlowScrollBarWidth').enabled(true))

    let scrollBarWidth1: string = await waterFlow1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarWidth1).$attrs.scrollBarWidth, '20.00vp')
    let scrollBarWidth2: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarWidth2).$attrs.scrollBarWidth, '10000000.00vp')
    await button.tap()
    let scrollBarWidth3: string = await waterFlow1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarWidth3).$attrs.scrollBarWidth, '30.00vp')

  }, 0)
}