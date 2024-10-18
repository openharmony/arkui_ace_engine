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
import { assertTrue, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function useEffectTest() {
  /*
  * 使用Text组件 UseEffect属性
  * 找到画面id为textUseEffect的Text组件
  * 找到画面文本为ButtonUseEffect的Button组件
  * 获取textUseEffect的UseEffect属性与期待值false比对
  * 点击button，变更textUseEffect的UseEffect属性值为true
  * 获取textUseEffectArea的UseEffect属性与期待值true比对
  */
  defineTest('UseEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('UseEffectTestDemo running')
    let driver: Tester = Tester.create()
    let textUseEffect: Component = await driver.findComponent(Matcher.create().id('textUseEffect').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonUseEffect').enabled(true))

    let useEffect1: string = await textUseEffect.getInspectorInfo()
    assertFalse(JSON.parse(useEffect1).$attrs.useEffect == undefined)
    assertFalse(JSON.parse(useEffect1).$attrs.useEffect)
    await button.tap()

    let useEffect2: string = await textUseEffect.getInspectorInfo()
    assertTrue(JSON.parse(useEffect2).$attrs.useEffect)
  }, 0)
}