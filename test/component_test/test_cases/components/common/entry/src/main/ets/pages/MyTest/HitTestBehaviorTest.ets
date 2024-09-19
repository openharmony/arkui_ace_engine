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
import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function hitTestBehaviorTest() {
  /*
   * Text组件 HitTestBehavior通用属性
   * 找到画面id为textHitTestBehavior组件
   * 找到画面text为ButtonHitTestBehavior的button组件
   * 获取textHitTestBehavior组件的hitTestBehavior属性与HitTestMode.Default比较
   * 点击button，改变textHitTestBehavior组件的hitTestBehavior属性为HitTestMode.Block
   * 获取textHitTestBehavior组件的hitTestBehavior属性与HitTestMode.Block比较
   * 点击button，改变textHitTestBehavior组件的hitTestBehavior属性为HitTestMode.Transparent
   * 获取textHitTestBehavior组件的hitTestBehavior属性与HitTestMode.Transparent 比较
   * 点击button，改变textHitTestBehavior组件的hitTestBehavior属性为HitTestMode.None
   * 获取textHitTestBehavior组件的hitTestBehavior属性与HitTestMode.None 比较
   */
  defineTest('hitTestBehaviorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('hitTestBehaviorTestDemo running')
    let driver: Tester = Tester.create()
    let textHitTestBehavior: Component =
      await driver.findComponent(Matcher.create().id('textHitTestBehavior').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonHitTestBehavior').enabled(true))
    let hitTestBehavior1: string = await textHitTestBehavior.getInspectorInfo()
    assertEqual(JSON.parse(hitTestBehavior1).$attrs.hitTestBehavior, 'HitTestMode.Default')

    await button.tap()
    let hitTestBehavior2: string = await textHitTestBehavior.getInspectorInfo()
    assertEqual(JSON.parse(hitTestBehavior2).$attrs.hitTestBehavior, 'HitTestMode.Block')

    await button.tap()
    let hitTestBehavior3: string = await textHitTestBehavior.getInspectorInfo()
    assertEqual(JSON.parse(hitTestBehavior3).$attrs.hitTestBehavior, 'HitTestMode.Transparent')

    await button.tap()
    let hitTestBehavior4: string = await textHitTestBehavior.getInspectorInfo()
    assertEqual(JSON.parse(hitTestBehavior4).$attrs.hitTestBehavior, 'HitTestMode.None')
  }, 0)
}