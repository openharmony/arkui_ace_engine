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

import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function sphericalEffectTest() {
  /*
   * Image组件 SphericalEffect通用属性
   * 找到画面id为imageSphericalEffect的组件
   * 找到画面text为ButtonSphericalEffect的button组件
   * 获取imageSphericalEffect的SphericalEffect属性与期待值 0 比较
   * 点击button，变更imageSphericalEffect的SphericalEffect属性为 0
   * 获取imageSphericalEffect的SphericalEffect属性中与期待值 0 比较
   * 点击button，变更imageSphericalEffect的SphericalEffect属性为 0.5
   * 获取imageSphericalEffect的SphericalEffect属性中与期待值 0.5 比较
   * 点击button，变更imageSphericalEffect的SphericalEffect属性为 1
   * 获取imageSphericalEffect的SphericalEffect属性中与期待值 1 比较
   * 点击button，变更imageSphericalEffect的SphericalEffect属性为 1.1
   * 获取imageSphericalEffect的SphericalEffect属性中与期待值 1 比较
   */
  defineTest('sphericalEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sphericalEffectTestDemo running')
    let driver: Tester = Tester.create()
    let imageSphericalEffect: Component =
      await driver.findComponent(Matcher.create().id('imageSphericalEffect').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonSphericalEffect').enabled(true))

    let information1: string = await imageSphericalEffect.getInspectorInfo()
    assertEqual(JSON.parse(information1).$attrs.sphericalEffect, 0)

    await button.tap()
    let information2: string = await imageSphericalEffect.getInspectorInfo()
    assertEqual(JSON.parse(information2).$attrs.sphericalEffect, 0)

    await button.tap()
    let information3: string = await imageSphericalEffect.getInspectorInfo()
    assertEqual(JSON.parse(information3).$attrs.sphericalEffect, 0.5)

    await button.tap()
    let information4: string = await imageSphericalEffect.getInspectorInfo()
    assertEqual(JSON.parse(information4).$attrs.sphericalEffect, 1)

    await button.tap()
    let information5: string = await imageSphericalEffect.getInspectorInfo()
    assertEqual(JSON.parse(information5).$attrs.sphericalEffect, 1)
  }, 0)
}