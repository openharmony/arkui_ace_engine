/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Component
struct MyAsyncEventPage {
    @State myAngle:number = 0
    build() {
        Column() {
            Row()
                .rotate({
                    x: 0,
                    y: 0,
                    z: 1,
                    centerX: '50%',
                    centerY: '50%',
                    angle: this.myAngle
                })
                .width(100).height(100).backgroundColor(0xAFEEEE)
                .onAppear(()=> {
                    console.log("MyPage onAppear")
                })
            Button("My page")
                .onClick(()=>{
                    this.myAngle += 50
                    console.log("click change angle to:" + this.myAngle)
                })
        }
    }
}
