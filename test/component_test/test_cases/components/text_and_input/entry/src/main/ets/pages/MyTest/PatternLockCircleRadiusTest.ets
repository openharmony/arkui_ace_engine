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

export default async function patternLockCircleRadiusTest() {
  /*
   * PatternLock组件 CircleRadius属性
   * 找到画面id为patternLockCircleRadius1，patternLockCircleRadius2的PatternLock组件
   * 找到画面文本为PatternLockCircleRadius1,PatternLockCircleRadius2的Button组件
   * 获取patternLock1的CircleRadius属性与期待值50.00vp比对
   * 点击button1，变更patternLock1的CircleRadius属性值为'20px'
   * 获取patternLock1的CircleRadius属性与期待值'20.00px'比对
   * 点击button2，变更patternLock1的CircleRadius属性值为6
   * 获取patternLock1的CircleRadius属性与期待值6.00vp比对
   * 获取patternLock2的CircleRadius属性与期待值$r('app.string.vp_length')比对
   */
  defineTest('patternLockCircleRadiusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("patternLockCircleRadiusTestDemo running")
    let driver: Tester = Tester.create()
    let patternLock1: Component =
      await driver.findComponent(Matcher.create().id('patternLockCircleRadius1').enabled(true))
    let patternLock2: Component =
      await driver.findComponent(Matcher.create().id('patternLockCircleRadius2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PatternLockCircleRadius1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PatternLockCircleRadius2').enabled(true))

    let circleRadius1: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(circleRadius1).$attrs.circleRadius, '50.00vp')
    let circleRadius2: string = await patternLock2.getInspectorInfo()
    assertEqual(JSON.parse(circleRadius2).$attrs.circleRadius, $r('app.string.vp_length'))

    await button1.tap()
    let circleRadius3: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(circleRadius3).$attrs.circleRadius, '20.00px')
    await button2.tap()
    let circleRadius4: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(circleRadius4).$attrs.circleRadius, '6.00vp')
  }, 0)
}