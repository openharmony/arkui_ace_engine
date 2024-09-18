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

export default async function layoutWeightTest() {
  /*
   * Search组件 LayoutWeight通用属性
   * 找到画面id为searchLayoutWeight的组件
   * 找到画面text为ButtonLayoutWeight的button组件
   * 获取searchLayoutWeight的LayoutWeight属性与期待值 1 比较
   * 点击button，变更searchLayoutWeight的LayoutWeight属性为 2
   * 获取searchLayoutWeight的LayoutWeight属性与期待值 2 比较
   */
  defineTest('layoutWeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('layoutWeightTestDemo running')
    let driver: Tester = Tester.create()
    let searchLayoutWeight: Component =
      await driver.findComponent(Matcher.create().id('searchLayoutWeight').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonLayoutWeight').enabled(true))
    let layoutWeight1: string = await searchLayoutWeight.getInspectorInfo()
    assertEqual(JSON.parse(layoutWeight1).$attrs.layoutWeight, 1)

    await button.tap()
    let layoutWeight2: string = await searchLayoutWeight.getInspectorInfo()
    assertEqual(JSON.parse(layoutWeight2).$attrs.layoutWeight, 2)
  }, 0)
}