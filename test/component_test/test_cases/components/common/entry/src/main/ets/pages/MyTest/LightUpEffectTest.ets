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

export default async function lightUpEffectTest() {
  /*
   * Counter组件 LightUpEffect通用属性
   * 找到画面id为counterLightUpEffect的组件
   * 找到画面text为 ButtonLightUpEffect 的button组件
   * 获取counterLightUpEffect的LightUpEffect属性与期待值-1比较
   * 点击button，变更counterLightUpEffect的LightUpEffect属性为 0
   * 获取counterLightUpEffect的LightUpEffect属性中与期待值 0 比较
   * 点击button，变更counterLightUpEffect的LightUpEffect属性为 0.5
   * 获取counterLightUpEffect的LightUpEffect属性中与期待值 0.5 比较
   * 点击button，变更counterLightUpEffect的LightUpEffect属性为 1
   * 获取counterLightUpEffect的LightUpEffect属性中与期待值 1 比较
   * 点击button，变更counterLightUpEffect的LightUpEffect属性为 1.1
   * 获取counterLightUpEffect的LightUpEffect属性中与期待值 1 比较
   */
  defineTest('lightUpEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('lightUpEffectTestDemo running')
    let driver: Tester = Tester.create()
    let counterLightUpEffect: Component =
      await driver.findComponent(Matcher.create().id('counterLightUpEffect').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonLightUpEffect').enabled(true))

    let lightUpEffect1: string = await counterLightUpEffect.getInspectorInfo()
    assertEqual(JSON.parse(lightUpEffect1).$attrs.lightUpEffect, 0)

    await button.tap()
    let lightUpEffect2: string = await counterLightUpEffect.getInspectorInfo()
    assertEqual(JSON.parse(lightUpEffect2).$attrs.lightUpEffect, 0)

    await button.tap()
    let lightUpEffect3: string = await counterLightUpEffect.getInspectorInfo()
    assertEqual(JSON.parse(lightUpEffect3).$attrs.lightUpEffect, 0.5)

    await button.tap()
    let lightUpEffect4: string = await counterLightUpEffect.getInspectorInfo()
    assertEqual(JSON.parse(lightUpEffect4).$attrs.lightUpEffect, 1)

    await button.tap()
    let lightUpEffect5: string = await counterLightUpEffect.getInspectorInfo()
    assertEqual(JSON.parse(lightUpEffect5).$attrs.lightUpEffect, 1)
  }, 0)
}