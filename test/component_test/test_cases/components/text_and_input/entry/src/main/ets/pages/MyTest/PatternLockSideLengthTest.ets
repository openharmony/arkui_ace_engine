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

export default async function patternLockSideLengthTest() {
  /*
* PatternLock组件 SideLength属性
* 找到画面id为patternLockSideLength1,patternLockSideLength2的PatternLock组件
* 找到画面文本为PatternLockSideLength的Button组件
* 获取patternLock1的SideLength属性与期待值200.00vp比对
* 点击button，变更patternLock1的SideLength属性值为'100px'
* 获取patternLock1的SideLength属性与期待值'100.00px'比对
* 获取patternLock2的SideLength属性与期待值$r('app.string.vp_length')比对
*/
  defineTest('patternLockSideLengthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("patternLockSideLengthTestDemo running")
    let driver: Tester = Tester.create()
    let patternLock1: Component =
      await driver.findComponent(Matcher.create().id('patternLockSideLength1').enabled(true))
    let patternLock2: Component =
      await driver.findComponent(Matcher.create().id('patternLockSideLength2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PatternLockSideLength').enabled(true))

    let sideLength1: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(sideLength1).$attrs.sideLength, '200.00vp')
    let sideLength2: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(sideLength2).$attrs.sideLength, $r('app.string.vp_length'))

    await button.tap()
    let sideLength3: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(sideLength3).$attrs.sideLength, '100.00px')
  }, 0)
}