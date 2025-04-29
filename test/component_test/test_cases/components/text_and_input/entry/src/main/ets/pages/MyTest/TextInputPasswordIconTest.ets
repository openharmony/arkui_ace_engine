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

export default async function textInputPasswordIconTest() {
  /*
* TextInput组件 PasswordIcon属性
* 找到画面id为textInputPasswordIcon的TextInput组件
* 找到画面文本为TextInputPasswordIcon的Button组件
* 获取textInput的PasswordIcon属性PasswordIcon.onIconSrc与期待值$r('app.media.startIcon')比对
* 点击button，变更textInput的PasswordIcon属性PasswordIcon.offIconSrc值为$r('app.media.startIcon')
* 获取textInput的PasswordIcon属性PasswordIcon.offIconSrc与期待值$r('app.media.startIcon')比对
*/
  defineTest('textInputPasswordIconTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputPasswordIconTestDemo running")
    let driver: Tester = Tester.create()
    let textInput: Component = await driver.findComponent(Matcher.create().id('textInputPasswordIcon').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextInputPasswordIcon').enabled(true))

    let passwordIcon1: string = await textInput.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(passwordIcon1).$attrs.passwordIcon).onIconSrc, $r('app.media.startIcon'))
    await button.tap()
    let passwordIcon2: string = await textInput.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(passwordIcon2).$attrs.passwordIcon).offIconSrc, $r('app.media.startIcon'))
  }, 0)
}