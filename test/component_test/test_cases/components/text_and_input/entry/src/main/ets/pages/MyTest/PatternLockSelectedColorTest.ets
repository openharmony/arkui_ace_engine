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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function patternLockSelectedColorTest() {
  /*
   * PatternLock组件 SelectedColor属性
   * 找到画面id为patternLockSelectedColor1，patternLockSelectedColor2的PatternLock组件
   * 找到画面文本为PatternLockSelectedColor1,PatternLockSelectedColor2的Button组件
   * 获取patternLock1的SelectedColor属性与期待值Color.Grey比对
   * 获取patternLock2的SelectedColor属性与期待值#ffff0000比对
   * 点击button1，变更patternLock2的SelectedColor属性值为'#008000'
   * 获取patternLock2的SelectedColor属性与期待值'#FF008000'比对
   * 点击button2，变更patternLock2的SelectedColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取patternLock1的SelectedColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('patternLockSelectedColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("patternLockSelectedColorTestDemo running")
    let driver: Tester = Tester.create()
    let patternLock1: Component =
      await driver.findComponent(Matcher.create().id('patternLockSelectedColor1').enabled(true))
    let patternLock2: Component =
      await driver.findComponent(Matcher.create().id('patternLockSelectedColor2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('PatternLockSelectedColor1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('PatternLockSelectedColor2').enabled(true))

    let selectedColor1: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor1).$attrs.selectedColor.toLowerCase(), Color.Grey)
    let selectedColor2: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor2).$attrs.selectedColor.toLowerCase(), '#ffff0000')

    await button1.tap()
    let selectedColor3: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor3).$attrs.selectedColor, '#FF008000')
    await button2.tap()
    let selectedColor4: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor4).$attrs.selectedColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}