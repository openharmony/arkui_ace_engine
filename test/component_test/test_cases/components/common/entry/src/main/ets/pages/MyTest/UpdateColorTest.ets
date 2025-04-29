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
import { assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function updateColorTest() {
  /*
  * Image组件 updateColor属性
  * 找到画面id为progressUpdateColor1的Image组件
  * 找到画面文本为UpdateColor1、UpdateColor2、UpdateColor3的Button组件
  * 获取progressUpdateColor1的updateColor属性与期待值#FF808080比对
  * 点击button1，变更progressUpdateColor1的updateColor属性值为#9FFF0000
  * 获取progressUpdateColor1的updateColor属性与期待值#9FFF0000比对
  * 点击button2，变更progressUpdateColor1的updateColor属性值为'#99182431'
  * 获取progressUpdateColor1的updateColor属性与期待值'#99182431'比对
  * *点击button3，变更progressUpdateColor1的updateColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
  * 获取progressUpdateColor1的updateColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
  */
  defineTest('updateColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("updateColorTestDemo running")
    let driver: Tester = Tester.create()
    let progressUpdateColor1: Component =
      await driver.findComponent(Matcher.create().id('progressUpdateColor1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonUpdateColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonUpdateColor2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonUpdateColor3').enabled(true))
    let updateColor1: string = await progressUpdateColor1.getInspectorInfo()
    assertEqual(JSON.parse(updateColor1).$attrs.updateColor, '#FF808080')

    await button1.tap()
    let updateColor2: string = await progressUpdateColor1.getInspectorInfo()
    assertEqual(JSON.parse(updateColor2).$attrs.updateColor, '#9FFF0000')

    await button2.tap()
    let updateColor3: string = await progressUpdateColor1.getInspectorInfo()
    assertEqual(JSON.parse(updateColor3).$attrs.updateColor, '#99182431')

    await button3.tap()
    let updateColor4: string = await progressUpdateColor1.getInspectorInfo()
    assertEqual(JSON.parse(updateColor4).$attrs.updateColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}