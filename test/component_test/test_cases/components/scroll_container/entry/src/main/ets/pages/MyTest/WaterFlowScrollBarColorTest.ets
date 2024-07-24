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

export default async function waterFlowScrollBarColorTest() {
  /*
* WaterFlow组件 nestedScroll属性
* 找到画面id为waterFlowScrollBarColor1,waterFlowScrollBarColor2的waterFlow组件
* 找到画面文本为WaterFlowScrollBarColor的button组件
* 获取waterFlow1的scrollBarColor属性与期待值'#FF008000'比对
* 获取waterFlow2的scrollBarColor属性与期待值'#FFFFFF00'比对
* 点击button，变更waterFlow2的scrollBarColor属性值为'#FFFFA500'
* 获取waterFlow2的scrollBarColor属性与期待值'#FFFFA500'比对
*/
  defineTest('waterFlowScrollBarColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowScrollBarColorTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow1: Component =
      await driver.findComponent(Matcher.create().id('waterFlowScrollBarColor1').enabled(true))
    let waterFlow2: Component =
      await driver.findComponent(Matcher.create().id('waterFlowScrollBarColor2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('WaterFlowScrollBarColor').enabled(true))

    let scrollBarColor1: string = await waterFlow1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor1).$attrs.scrollBarColor, '#FF008000')
    let scrollBarColor2: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor2).$attrs.scrollBarColor, '#FFFFFF00')
    await button.tap()
    let scrollBarColor3: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor3).$attrs.scrollBarColor, '#FFFFA500')
  }, 0)
}

