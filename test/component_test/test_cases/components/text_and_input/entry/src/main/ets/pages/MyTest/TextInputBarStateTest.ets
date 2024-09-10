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

export default async function textInputBarStateTest() {
  /*
* TextInput组件 BarState属性
* 找到画面id为textInputBarState1,textInputBarState2的TextInput组件
* 找到画面文本为TextInputBarState的Button组件
* 获取textInput1的BarState属性与期待值'BarState.Off'比对
* 获取textInput2的BarState属性与期待值'BarState.On'比对
* 点击button，变更textInput2的BarState属性值为BarState.Auto
* 获取textInput2的BarState属性与期待值'BarState.Auto'比对
*/
  defineTest('textInputBarStateTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputBarStateTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component = await driver.findComponent(Matcher.create().id('textInputBarState1').enabled(true))
    let textInput2: Component = await driver.findComponent(Matcher.create().id('textInputBarState2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextInputBarState').enabled(true))

    let barState1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(barState1).$attrs.barState, 'BarState.OFF')
    let barState2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(barState2).$attrs.barState, 'BarState.ON')

    await button.tap()
    let barState3: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(barState3).$attrs.barState, 'BarState.AUTO')
  }, 0)
}