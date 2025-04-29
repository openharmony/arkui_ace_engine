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

export default async function patternLockActiveColorTest() {
  /*
   * PatternLock组件 ActiveColor属性
   * 找到画面id为patternLockActiveColor1，patternLockActiveColor2的PatternLock组件
   * 找到画面文本为PatternLockActiveColor1,PatternLockActiveColor2的Button组件
   * 获取patternLock1属性与期待值Color.Grey比对
   * 获取patternLock2属性与期待值0xfffff比对
   * 点击button1，变更patternLock2的ActiveColor属性值为'#008000'
   * 获取patternLock2的ActiveColor属性与期待值'#008000'比对
   * 点击button2，变更patternLock2的ActiveColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取patternLock2的ActiveColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('patternLockActiveColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("patternLockActiveColorTestDemo running")
    let driver: Tester = Tester.create()
    let patternLock1: Component =
      await driver.findComponent(Matcher.create().id('patternLockActiveColor1').enabled(true))
    let patternLock2: Component =
      await driver.findComponent(Matcher.create().id('patternLockActiveColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PatternLockActiveColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PatternLockActiveColor2').enabled(true))

    let activeColor1: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(activeColor1).$attrs.activeColor.toLowerCase(), Color.Grey)
    let activeColor2: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(activeColor2).$attrs.activeColor.toLowerCase(), '#ff0fffff')

    await button1.tap()
    let activeColor3: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(activeColor3).$attrs.activeColor, '#FF008000')
    await button2.tap()
    let activeColor4: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(activeColor4).$attrs.activeColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}