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

export default async function progressColorResourceColorTest() {
  /*
* Progress组件 Color属性
* 找到画面id为progressColorResourceColor1,progressColorResourceColor2的Progress组件
* 找到画面文本为ProgressColorResourceColor1,ProgressColorResourceColor2组件
* 获取progress1的Color.ResourceColor属性与期待值Color.Red比对
* 获取progress1的Color.ResourceColor属性与期待值$r('app.color.progress_color')比对
* 点击button1，变更progress1的Color.ResourceColor属性值为0x000000
* 获取progress1的Color.ResourceColor属性与期待值0x000000比对
* 点击button2，变更progress1的Color.ResourceColor属性值为'#0000ff'
* 获取progress2的Color.ResourceColor属性与期待值'#0000ff'比对
*/
  defineTest('progressColorResourceColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("progressColorResourceColorTestDemo running")
    let driver: Tester = Tester.create()
    let progress1: Component =
      await driver.findComponent(Matcher.create().id('progressColorResourceColor1').enabled(true))
    let progress2: Component =
      await driver.findComponent(Matcher.create().id('progressColorResourceColor2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ProgressColorResourceColor1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ProgressColorResourceColor2').enabled(true))
    let colorResourceColor1: string = await progress1.getInspectorInfo()
    assertEqual(JSON.parse(colorResourceColor1).$attrs.color.toLowerCase(), Color.Red)
    let colorResourceColor2: string = await progress2.getInspectorInfo()
    assertEqual(JSON.parse(colorResourceColor2).$attrs.color, $r("app.color.progress_color"))
    await button1.tap()
    let colorResourceColor3: string = await progress1.getInspectorInfo()
    assertEqual(JSON.parse(colorResourceColor3).$attrs.color, '#FF000000')
    await button2.tap()
    let colorResourceColor4: string = await progress1.getInspectorInfo()
    assertEqual(JSON.parse(colorResourceColor4).$attrs.color, '#FF0000FF')
  }, 0)
}