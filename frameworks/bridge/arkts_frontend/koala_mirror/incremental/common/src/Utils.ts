/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

export class Utils {
    static begin_: (str:string) => void = (str: string)=> {
    }
    static end_: () => void = () =>{
    }

    static Init(begin:(str:string) => void, end:() => void) {
        Utils.begin_ = begin
        Utils.end_ = end
    }

    static traceBegin(str:string):void {
        Utils.begin_(str)
    }
    static traceEnd(): void {
        Utils.end_()
    }
}
