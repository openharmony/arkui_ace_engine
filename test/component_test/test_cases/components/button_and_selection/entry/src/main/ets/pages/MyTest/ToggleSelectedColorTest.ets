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

export default async function toggleSelectedColorTest() {
  /*
   * Toggle组件 SelectedColor属性
   * 找到画面id为toggleSelectedColor1，toggleSelectedColor2， toggleSelectedColor3的Button组件
   * 找到画面文本为ToggleSelectedColor的Button组件
   * 获取toggleSelectedColor1的SelectedColor属性与期待值Color.Black比对
   * 获取toggleSelectedColor2的SelectedColor属性与期待值'#FFA52A2A'比对
   * 获取toggleSelectedColor3的SelectedColor属性与期待值'#FF8EFF65'比对
   * 点击button，变更toggleSelectedColor3的SelectedColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取toggleSelectedColor3的SelectedColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('toggleSelectedColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('toggleSelectedColorTestDemo running')
    let driver: Tester = Tester.create()
    let toggleSelectedColor1: Component =
      await driver.findComponent(Matcher.create().id('toggleSelectedColor1').enabled(true))
    let toggleSelectedColor2: Component =
      await driver.findComponent(Matcher.create().id('toggleSelectedColor2').enabled(true))
    let toggleSelectedColor3: Component =
      await driver.findComponent(Matcher.create().id('toggleSelectedColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ToggleSelectedColor').enabled(true))

    let selectedColor1: string = await toggleSelectedColor1.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor1).$attrs.selectedColor.toLowerCase(), Color.Black)

    let selectedColor2: string = await toggleSelectedColor2.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor2).$attrs.selectedColor, '#FFA52A2A')

    let selectedColor3: string = await toggleSelectedColor3.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor3).$attrs.selectedColor, '#FF8EFF65')

    await button.tap()
    let selectedColor4: string = await toggleSelectedColor3.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor4).$attrs.selectedColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}