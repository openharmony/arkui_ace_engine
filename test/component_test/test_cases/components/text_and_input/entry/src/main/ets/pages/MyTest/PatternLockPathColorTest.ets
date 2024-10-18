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

export default async function patternLockPathColorTest() {
  /*
   * PatternLock组件 PathColor属性
   * 找到画面id为patternLockPathColor1，patternLockPathColor2的PatternLock组件
   * 找到画面文本为PatternLockPathColor1,PatternLockPathColor2的Button组件
   * 获取patternLock1的PathColor属性与期待值Color.Grey比对
   * 获取patternLock2的PathColor属性与期待值0xffffff比对
   * 点击button1，变更patternLock2的PathColor属性值为'#008000'
   * 获取patternLock2的PathColor属性与期待值'#008000'比对
   * 点击button2，变更patternLock2的PathColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取patternLock2的PathColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('patternLockPathColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("patternLockPathColorTestDemo running")
    let driver: Tester = Tester.create()
    let patternLock1: Component = await driver.findComponent(Matcher.create().id('patternLockPathColor1').enabled(true))
    let patternLock2: Component = await driver.findComponent(Matcher.create().id('patternLockPathColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PatternLockPathColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PatternLockPathColor2').enabled(true))

    let pathColor1: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(pathColor1).$attrs.pathColor.toLowerCase(), Color.Grey)
    let pathColor2: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(pathColor2).$attrs.pathColor.toLowerCase(), '#ffffffff')

    await button1.tap()
    let pathColor3: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(pathColor3).$attrs.pathColor, '#FF008000')
    await button2.tap()
    let pathColor4: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(pathColor4).$attrs.pathColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}