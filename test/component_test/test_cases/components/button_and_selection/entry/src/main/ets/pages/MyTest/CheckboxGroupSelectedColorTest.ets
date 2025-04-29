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

export default async function checkboxGroupSelectedColorTest() {
  /*
   * CheckboxGroup组件 SelectedColor属性
   * 找到画面id为checkboxGroupSelectedColor1，checkboxGroupSelectedColor2，checkboxGroupSelectedColor3的CheckboxGroup组件
   * 找到画面文本为CheckboxGroupSelectedColor的Button组件
   * 获取checkboxGroupSelectedColor1的SelectedColor属性与期待值Color.Black比对
   * 获取checkboxGroupSelectedColor2的SelectedColor属性与期待值'#FFA52A2A'比对
   * 获取checkboxGroupSelectedColor3的SelectedColor属性与期待值'#FF8EFF65'比对
   * 点击button，变更checkboxGroupSelectedColor3的SelectedColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取checkboxGroupSelectedColor3的SelectedColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('checkboxGroupSelectedColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('checkboxGroupSelectedColorTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxGroupSelectedColor1: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupSelectedColor1').enabled(true))
    let checkboxGroupSelectedColor2: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupSelectedColor2').enabled(true))
    let checkboxGroupSelectedColor3: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupSelectedColor3').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('CheckboxGroupSelectedColor').enabled(true))

    let selectedColor1: string = await checkboxGroupSelectedColor1.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor1).$attrs.selectedColor.toLowerCase(), Color.Black)

    let selectedColor2: string = await checkboxGroupSelectedColor2.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor2).$attrs.selectedColor, '#FFA52A2A')

    let selectedColor3: string = await checkboxGroupSelectedColor3.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor3).$attrs.selectedColor, '#FF8EFF65')

    await button.tap()
    let selectedColor4: string = await checkboxGroupSelectedColor3.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor4).$attrs.selectedColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}