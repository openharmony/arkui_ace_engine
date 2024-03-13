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



/**
 * @state @Component/ViewPU variable decorator
 * 
 * local init required - transpiler needs to support
 * no init or update form parent - transpiler needs to support
 * new value assignment allowed = has setter 
 *
 * part of SDK
 * @from 12
 *
 */
/*
const state = (target: Object, propertyKey: string) => {
    ObserveV3.addVariableDecoMeta(target, propertyKey, "@state");
    return trackInternal(target, propertyKey);
  }
  */
  
  /**
   * @param class property decorator 
   * 
   * local init optional - transpiler needs to support
   * init and update form parent is mandatory when no local init, otherwise optional - transpiler needs to support
   * new value assignment not allowed = has no setter. For update from parent @Component, 
   *               transpiler calls ViewPU.updateParam(paramName).
   * 
   * @param target  ViewPU class prototype object
   * @param propertyKey  class property name
   * 
   * turns given property into getter and setter functions
   * adds property target[storeProp] as the backing store
   *
   * part of SDK
   * @from 12
   *
   */
  /*
  const param = (target : Object, propertyKey : string) => {
    ObserveV3.addVariableDecoMeta(target, propertyKey, "@param");
  
    let storeProp = ObserveV3.OB_PREFIX + propertyKey
    target[storeProp] = target[propertyKey]
    Reflect.defineProperty(target, propertyKey, {
      get() {
        ObserveV3.getObserve().addRef(this, propertyKey)
        return ObserveV3.autoProxyObject(this, ObserveV3.OB_PREFIX + propertyKey)
      },
      set(_) {
        stateMgmtConsole.applicationError(`@param ${propertyKey.toString()}: can not assign a new value, application error.`)
        return;
      },
      // @param can not be assigned, no setter
      enumerable: true
    })
  } // param
  */
  
  /**
   * @event @Component/ViewPU variable decorator
   * 
   * @param target 
   * @param propertyKey 
   */
  
  /*
  const event = (target, propertyKey) => {
    ObserveV3.addVariableDecoMeta(target, propertyKey, "@event");
    target[propertyKey] = () => {};
  }
  */
 
  // The prop parameter is not carried when the component is updated.
  // FIXME what is the purpose of this ?
  /*
  let updateChild = ViewPU.prototype["updateStateVarsOfChildByElmtId"];
  ViewPU.prototype["updateStateVarsOfChildByElmtId"] = function (elmtId, params) {
    updateChild?.call(this, elmtId, params);
    let child = this.getChildById(elmtId);
    if (child) {
      let realParams = child.paramsGenerator_ ? child.paramsGenerator_() : params
      for (let k in realParams) {
        if (ObserveV3.OB_PREFIX + k in child) {
          child[k] = realParams[k];
        }
      }
    }
  }
  */
  
  