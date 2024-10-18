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

export default async function stateStylesTest() {
  /*
   * stateStyles属性 Text 组件
   * 找到画面中id为TextStateStyles1 TextStateStyles2 TextStateStyles3 的Text组件
   * 点击TextStateStyles2 TextStateStyles3 Text组件使用stateStyles的接口
   * 获取TextStateStyles1组件backgroundColor值于#FF0A59F7对比
   * 获取TextStateStyles1组件backgroundColor值于#FFED6F21对比
   * 获取TextStateStyles1组件backgroundColor值于#FFE5E5E5对比
   */
  defineTest('stateStylesTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('stateStylesTestDemo running')
    let driver: Tester = Tester.create()
    let TextStateStyles1: Component = await driver.findComponent(Matcher.create().id('TextStateStyles1').enabled(true))
    let TextStateStyles2: Component = await driver.findComponent(Matcher.create().id('TextStateStyles2').enabled(true))
    let TextStateStyles3: Component = await driver.findComponent(Matcher.create().id('TextStateStyles3').enabled(true))
    await TextStateStyles3.tap()
    await TextStateStyles2.tap()
    let stateStyles1: string = await TextStateStyles1.getInspectorInfo()
    let stateStyles2: string = await TextStateStyles2.getInspectorInfo()
    let stateStyles3: string = await TextStateStyles3.getInspectorInfo()
    assertEqual(JSON.parse(stateStyles1).$attrs.backgroundColor, '#FF0A59F7')
    assertEqual(JSON.parse(stateStyles2).$attrs.backgroundColor, '#FFED6F21')
    assertEqual(JSON.parse(stateStyles3).$attrs.backgroundColor, '#FFE5E5E5')
  }, 0)
}