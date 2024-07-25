/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

/**
 * Environment
 * 
 * Injects device properties ("environment") into AppStorage 
 * 
 */

class Environment {
  private static instance_: Environment = undefined;
  private static envBackend_: IEnvironmentBackend;
  private props_: Map<string, SubscribedAbstractProperty<any>>;

  private static getOrCreate(): Environment {
    if (Environment.instance_) {
      // already initialized
      return Environment.instance_;
    }

    Environment.instance_ = new Environment();
    return Environment.instance_;
  }

  public static configureBackend(envBackend: IEnvironmentBackend): void {
    Environment.envBackend_ = envBackend;
  }

  /**
   * @see configureBackend
   * @deprecated
   */
  public static ConfigureBackend(envBackend: IEnvironmentBackend): void {
    Environment.envBackend_ = envBackend;
  }


  public static aboutToBeDeleted(): void {
    if (!Environment.instance_) {
      return;
    }

    Environment.getOrCreate().aboutToBeDeleted();
    Environment.instance_ = undefined;
  }

  /**
   * @see aboutToBeDeleted
   * @deprecated
   */
  public static AboutToBeDeleted(): void {
    Environment.aboutToBeDeleted();
  }

  public static envProp<S>(key: string, value: S): boolean {
    return Environment.getOrCreate().envProp<S>(key, value);
  }

  /**
   * @see envProp
   * @deprecated
   */
  public static EnvProp<S>(key: string, value: S): boolean {
    return Environment.getOrCreate().envProp<S>(key, value);
  }

  public static envProps(props: {
    key: string,
    defaultValue: any
  }[]
  ): void {
    Environment.getOrCreate().envProps(props);
  }

  /**
   * @see envProps
   * @deprecated
   */
  public static EnvProps(props: {
    key: string,
    defaultValue: any
  }[]
  ): void {
    Environment.getOrCreate().envProps(props);
  }

  static keys(): Array<string> {
    return Environment.getOrCreate().keys();
  }

  /**
   * @see keys
   * @deprecated
   */
  static Keys(): Array<string> {
    return Environment.getOrCreate().keys();
  }

  private constructor() {
    this.props_ = new Map<string, ObservedPropertyAbstract<any>>();

    Environment.envBackend_.onValueChanged(this.onValueChanged.bind(this));
  }

  private envProp<S>(key: string, value: S): boolean {
    let prop = AppStorage.prop(key);
    if (prop) {
      stateMgmtConsole.warn(`Environment: envProp '${key}': Property already exists in AppStorage. Not using environment property.`);
      return false;
    }
    let tmp;
    switch (key) {
      case 'accessibilityEnabled':
        tmp = Environment.envBackend_ .getAccessibilityEnabled();
        break;
      case 'colorMode':
        tmp = Environment.envBackend_ .getColorMode();
        break;
      case 'fontScale':
        tmp = Environment.envBackend_ .getFontScale();
        break;
      case 'fontWeightScale':
        tmp = Environment.envBackend_ .getFontWeightScale().toFixed(2);
        break;
      case 'layoutDirection':
        tmp = Environment.envBackend_ .getLayoutDirection();
        break;
      case 'languageCode':
        tmp = Environment.envBackend_ .getLanguageCode();
        break;
      default:
        tmp = value;
    }
    if (!tmp && tmp !== 0) {
      tmp = value;
    }
    prop = AppStorage.setAndProp(key, tmp);
    if (!prop) {
      stateMgmtConsole.warn(`Environment: envProp '${key}': AppStorage setAndProp failed.`);
      return false;
    }
    this.props_.set(key, prop);
    stateMgmtConsole.debug(`Environment: envProp for '${key}' done.`);
    return true;
  }

  private envProps(properties: {
    key: string,
    defaultValue: any
  }[]): void {
    properties.forEach(property => {
      this.envProp(property.key, property.defaultValue);
      stateMgmtConsole.debug(`Environment: envProps for '${property.key}' done.`);
    });
  }

  keys(): Array<string> {
    let result = [];
    const it = this.props_.keys();
    let val = it.next();

    while (!val.done) {
      result.push(val.value);
      val = it.next();
    }

    return result;
  }

  onValueChanged(key: string, value: any): void {
    let ok = AppStorage.set(key, value);
    if (ok) {
      stateMgmtConsole.debug(`Environment: onValueChanged: ${key} changed to ${value}`);
    } else {
      stateMgmtConsole.warn(`Environment: onValueChanged: error changing ${key}! See results above.`);
    }
  }

  aboutToBeDeleted() {
    this.props_.forEach((val, key, map) => {
      val.aboutToBeDeleted();
      AppStorage.delete(key);
    });
  }
}
