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

export default async function checkboxSelectedColorTest() {
  /*
   * Checkbox组件 SelectedColor属性
   * 找到画面id为checkboxSelectedColor1，checkboxSelectedColor2，checkboxSelectedColor3的Checkbox组件
   * 找到画面文本为CheckboxSelectedColor的Button组件
   * 获取checkboxSelectedColor1的SelectedColor属性与期待值Color.Black比对
   * 获取checkboxSelectedColor2的SelectedColor属性与期待值'#FFA52A2A'比对
   * 获取checkboxSelectedColor3的SelectedColor属性与期待值'#FF8EFF65'比对
   * 点击button，变更checkboxSelectedColor3的SelectedColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取checkboxSelectedColor3的SelectedColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('checkboxSelectedColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('checkboxSelectedColorTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxSelectedColor1: Component =
      await driver.findComponent(Matcher.create().id('checkboxSelectedColor1').enabled(true))
    let checkboxSelectedColor2: Component =
      await driver.findComponent(Matcher.create().id('checkboxSelectedColor2').enabled(true))
    let checkboxSelectedColor3: Component =
      await driver.findComponent(Matcher.create().id('checkboxSelectedColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CheckboxSelectedColor').enabled(true))

    let selectedColor1: string = await checkboxSelectedColor1.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor1).$attrs.selectedColor.toLowerCase(), Color.Black)

    let selectedColor2: string = await checkboxSelectedColor2.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor2).$attrs.selectedColor, '#FFA52A2A')

    let selectedColor3: string = await checkboxSelectedColor3.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor3).$attrs.selectedColor, '#FF8EFF65')

    await button.tap()
    let selectedColor4: string = await checkboxSelectedColor3.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor4).$attrs.selectedColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}