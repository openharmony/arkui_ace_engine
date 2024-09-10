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

export default async function checkboxGroupUnSelectedColorTest() {
  /*
   * CheckboxGroup组件 UnSelectedColor属性
   * 找到画面id为checkboxGroupUnSelectedColor1，checkboxGroupUnSelectedColor2，checkboxGroupUnSelectedColor3的CheckboxGroup组件
   * 找到画面文本为CheckboxGroupUnSelectedColor的Button组件
   * 获取checkboxGroupUnSelectedColor1的UnSelectedColor属性与期待值Color.Black比对
   * 获取checkboxGroupUnSelectedColor2的UnSelectedColor属性与期待值'#FFA52A2A'比对
   * 获取checkboxGroupUnSelectedColor3的UnSelectedColor属性与期待值'#FF8EFF65'比对
   * 点击button，变更checkboxGroupUnSelectedColor3的UnSelectedColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取checkboxGroupUnSelectedColor3的UnSelectedColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('checkboxGroupUnSelectedColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('checkboxGroupUnSelectedColorTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxGroupUnSelectedColor1: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupUnSelectedColor1').enabled(true))
    let checkboxGroupUnSelectedColor2: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupUnSelectedColor2').enabled(true))
    let checkboxGroupUnSelectedColor3: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupUnSelectedColor3').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('CheckboxGroupUnSelectedColor').enabled(true))

    let unselectedColor1: string = await checkboxGroupUnSelectedColor1.getInspectorInfo()
    assertEqual(JSON.parse(unselectedColor1).$attrs.unselectedColor.toLowerCase(), Color.Black)

    let unselectedColor2: string = await checkboxGroupUnSelectedColor2.getInspectorInfo()
    assertEqual(JSON.parse(unselectedColor2).$attrs.unselectedColor, '#FFA52A2A')

    let unselectedColor3: string = await checkboxGroupUnSelectedColor3.getInspectorInfo()
    assertEqual(JSON.parse(unselectedColor3).$attrs.unselectedColor, '#FF8EFF65')

    await button.tap()
    let unselectedColor4: string = await checkboxGroupUnSelectedColor3.getInspectorInfo()
    assertEqual(JSON.parse(unselectedColor4).$attrs.unselectedColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}