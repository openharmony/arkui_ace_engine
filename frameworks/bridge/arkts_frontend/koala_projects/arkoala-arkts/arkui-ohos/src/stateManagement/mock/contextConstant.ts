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

namespace contextConstant {

  /**
   * File area mode
   *
   * @enum { number }
   * @syscap SystemCapability.Ability.AbilityRuntime.Core
   * @StageModelOnly
   * @since 20
   */
  export enum AreaMode {

      /**
       * System level device encryption area
       *
       * @syscap SystemCapability.Ability.AbilityRuntime.Core
       * @StageModelOnly
       * @since 20
       */
      EL1 = 0,

      /**
       * User credential encryption area
       *
       * @syscap SystemCapability.Ability.AbilityRuntime.Core
       * @StageModelOnly
       * @since 20
       */
      EL2 = 1,
      /**
       * User credential encryption area
       * when screen locked, can read/write, and create file
       *
       * @syscap SystemCapability.Ability.AbilityRuntime.Core
       * @stagemodelonly
       * @since 20
       */
      EL3 = 2,
      /**
       * User credential encryption area
       * when screen locked, FEB2.0 can read/write, FEB3.0 can't
       * read/write, and all can't create file
       *
       * @syscap SystemCapability.Ability.AbilityRuntime.Core
       * @stagemodelonly
       * @since 20
       */
      EL4 = 3,
      /**
       * User privacy sensitive encryption area
       * when the screen locked, a closed file cannot be opened, read, or written,
       * a file can be created and then opened, read, or written.
       *
       * @syscap SystemCapability.Ability.AbilityRuntime.Core
       * @stagemodelonly
       * @since 20
       */
      EL5 = 4
  }
}

export default contextConstant;