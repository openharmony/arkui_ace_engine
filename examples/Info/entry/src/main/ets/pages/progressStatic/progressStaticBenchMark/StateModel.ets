/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
'use static';
export enum StateConstants {
  CREATE_STATE = 0,
  READ_STATE = 1,
  WRITE_STATE = 2,
  UI_CHANGE = 3
}

export class StateModel {
  private _stateType: number = 0

  public set setStateType(value: number) {
    this._stateType = value
  }

  public get getStateType(): number {
    return this._stateType
  }

  private _isBindUI: boolean = false

  public set isBindUI(value: boolean) {
    this._isBindUI = value
  }

  public get isBindUI(): boolean {
    return this._isBindUI
  }

  constructor(stateType: number, isBindUI: boolean) {
    this._stateType = stateType
    this._isBindUI = isBindUI
  }
}


export enum LanguageEnum {
  English = 'Hello World',
  Chinese = '你好， 世界',
  French = 'Bonjour, le monde',
  German= 'Hallo Welt',
  Japanese = 'こんにちは世界',
  Thailand = 'สวัสดีชาวโลก',
  Vietnam = 'Xin chào thế giới',
  Greece = 'Γεια σας, κόσμε',
  Russian = 'Здравствуй, мир',
  Korea = 'Hello World는',
  Mongols = 'ᠲᠠ ᠰᠠᠢᠨ ᠶᠢᠷᠲᠢᠨᠴᠦ'
}

export let enumArr: LanguageEnum[] = [LanguageEnum.English, LanguageEnum.Chinese, LanguageEnum.English,
  LanguageEnum.Chinese, LanguageEnum.English, LanguageEnum.Chinese, LanguageEnum.English, LanguageEnum.Chinese,
  LanguageEnum.English, LanguageEnum.Chinese]
