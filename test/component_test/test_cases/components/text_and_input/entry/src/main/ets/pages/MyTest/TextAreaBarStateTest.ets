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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function textAreaBarStateTest() {
  /*
   * TextArea组件 BarState属性
   * 找到画面id为textAreaBarState1,textAreaBarState2的TextArea组件
   * 找到画面文本为TextAreaBarState的Button组件
   * 获取textArea1的BarState属性与期待值BarState.Off比对
   * 获取textArea2的BarState属性与期待值BarState.On比对
   * 点击button，变更textArea2的BarState属性值为BarState.Auto
   * 获取textArea2的BarState属性与期待值BarState.Auto比对
   */
  defineTest('textAreaBarStateTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaBarStateTestDemo running")
    let driver: Tester = Tester.create()
    let textArea1: Component = await driver.findComponent(Matcher.create().id('textAreaBarState1').enabled(true))
    let textArea2: Component = await driver.findComponent(Matcher.create().id('textAreaBarState2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextAreaBarState').enabled(true))

    let barState1: string = await textArea1.getInspectorInfo()
    assertEqual(JSON.parse(barState1).$attrs.barState, 'BarState.OFF')
    let barState2: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(barState2).$attrs.barState, 'BarState.ON')

    await button.tap()
    let barState3: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(barState3).$attrs.barState, 'BarState.AUTO')
  }, 0)
}