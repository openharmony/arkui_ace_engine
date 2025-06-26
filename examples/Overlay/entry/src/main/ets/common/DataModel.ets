/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

export class Model1 {
  public message?: string | Resource | number = undefined //message是必填项
  public duration?: string | Resource | number = undefined
  public bottom?: string | Resource | number = undefined

  constructor(message?: string | Resource, duration?: string | Resource, bottom?: string | Resource) {
    this.message = message
    this.duration = duration
    this.bottom = bottom
  }
}

//showDialog---title|message|buttons测试参数且无必填项
export class Model2 {
  public title?: string | Resource | number = undefined
  public message?: string | Resource | number = undefined
  public buttonText1?: string | Resource | number = undefined
  public buttonColor1?: string | Resource | number = undefined
  public buttonText2?: string | Resource = undefined
  public buttonColor2?: string | Resource = undefined
  public buttonText3?: string | Resource = undefined
  public buttonColor3?: string | Resource = undefined

  constructor(title?: string | Resource, message?: string | Resource, buttonText1?: string | Resource,
    buttonColor1?: string | Resource, buttonText2?: string | Resource, buttonColor2?: string | Resource,
    buttonText3?: string | Resource, buttonColor3?: string | Resource) {
    this.title = title
    this.message = message
    this.buttonText1 = buttonText1
    this.buttonColor1 = buttonColor1
    this.buttonText2 = buttonText2
    this.buttonColor2 = buttonColor2
    this.buttonText3 = buttonText3
    this.buttonColor3 = buttonColor3
  }
}

//showActionMenu---title|buttons测试参数且buttons为必填项
export class Model3 {
  public title?: Resource | string | number = undefined
  public buttonText?: string | Resource | number = undefined
  public buttonColor?: string | Resource | number = undefined

  constructor(title?: string | Resource, buttonText?: string | Resource, buttonColor?: string | Resource) {
    this.title = title
    this.buttonText = buttonText
    this.buttonColor = buttonColor
  }
}

export class TestListOption {
  public title?: string = undefined
  public url?: string = undefined
  public key?: string = undefined
}

export class Stack<T> {
  private items: T[];

  constructor() {
    this.items = [];
  }

  push(element: T) {
    this.items.push(element);
  }

  pop(): T | undefined {
    return this.items.pop();
  }

  top(): T | undefined {
    return this.items[this.items.length - 1];
  }

  isEmpty(): boolean {
    return this.items.length === 0;
  }
}

export class SystemWindowOptions {
  public decorVisible: boolean = true
  public decorHeight: number = 48
}
