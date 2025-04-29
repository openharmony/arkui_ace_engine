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

export default async function patternLockRegularColorTest() {
  /*
   * PatternLock组件 RegularColor属性
   * 找到画面id为patternLockRegularColor1，patternLockRegularColor2的PatternLock组件
   * 找到画面文本为PatternLockRegularColor1,PatternLockRegularColor2的Button组件
   * 获取patternLock1的RegularColor属性与期待值Color.Grey比对
   * 获取patternLock2的RegularColor属性与期待值#ffff0000比对
   * 点击button1，变更patternLock2的RegularColor属性值为'#008000'
   * 获取patternLock2的RegularColor属性与期待值'#FF008000'比对
   * 点击button2，变更patternLock2的RegularColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取patternLock2的RegularColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('patternLockRegularColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("patternLockRegularColorTestDemo running")
    let driver: Tester = Tester.create()
    let patternLock1: Component =
      await driver.findComponent(Matcher.create().id('patternLockRegularColor1').enabled(true))
    let patternLock2: Component =
      await driver.findComponent(Matcher.create().id('patternLockRegularColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PatternLockRegularColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PatternLockRegularColor2').enabled(true))

    let regularColor1: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(regularColor1).$attrs.regularColor.toLowerCase(), Color.Grey)
    let regularColor2: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(regularColor2).$attrs.regularColor.toLowerCase(), '#ffff0000')

    await button1.tap()
    let regularColor3: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(regularColor3).$attrs.regularColor, '#FF008000')
    await button2.tap()
    let regularColor4: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(regularColor4).$attrs.regularColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}