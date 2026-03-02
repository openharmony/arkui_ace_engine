/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import i18n from '@ohos.i18n';

export class LanguageUtil {
  public static getLanguageCode(): string {
    let systemLanguage: string = i18n.System.getAppPreferredLanguage() || i18n.System.getSystemLanguage()
    const lang = systemLanguage.toLowerCase()
    switch (true) {
      case lang.startsWith('en'):
        return LanguageUtil.getENSimplifiedLanguage(systemLanguage)
      case lang.startsWith('zh-hant'):
        let region: string =i18n.System.getSystemRegion()
        return region === 'HK' || region === 'MO' ? 'zh-hk' : 'zh-tw'

      case lang.startsWith('ug'):
        return 'ug-cn'

      case lang.startsWith('bo'):
        return 'bo-cn'

      case lang.startsWith('zh-hans'):
        return 'zh-cn'

      case lang.startsWith('ko'):
        return 'ko-kr'

      case lang.startsWith('ja'):
        return 'ja-jp'

      case lang.startsWith('ru'):
        return 'ru-ru'

      case lang.startsWith('ar'):
        return 'ar-ep'

      case lang.startsWith('es'):
        return 'es-es'

      case lang.startsWith('vi'):
        return 'vi-vn'

      case lang.startsWith('fr'):
        return 'fr-fr'

      case lang.startsWith('de'):
        return 'de-de'
      case lang.startsWith('id'):
        return 'in-id'
      case lang.startsWith('it'):
        return 'it-it'
      case lang.startsWith('lo'):
        return 'lo-la'
      case lang.startsWith('ms'):
        return 'ms-my'
      case lang.startsWith('my'):
        return 'my-mm'
      case lang.startsWith('pl'):
        return 'pl-pl'
      case lang.startsWith('pt-pt'):
        return 'pt-pt'
      case lang.startsWith('th'):
        return 'th-th'
      case lang.startsWith('tr'):
        return 'tr-tr'
      default:
        return systemLanguage
    }
  }
  private static getENSimplifiedLanguage(language: string): string {
    try {
      return i18n.System.getSimplifiedLanguage(language).toLowerCase()
    } catch (e) {
      return 'en-us'
    }
  }
  static readonly LANGUAGE_MAP = new Map([['zh', 'zh-cn'], ['en', 'en-us']])

  public static convert(language: string): string {
    let result = LanguageUtil.LANGUAGE_MAP.get(language.toLowerCase())
    if (result) {
      return result
    } else {
      return language
    }
  }
}