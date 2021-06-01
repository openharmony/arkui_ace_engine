/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

class Handler {
  constructor(publishedProperties1) {
    this.listeners = new Set();
    this.publishedProperties = publishedProperties1;
    console.log(`ObservableObject Published Properties: ${JSON.stringify([...this.publishedProperties])}`);

    this.register = function (v) {
      if (this.listeners.has(v.getViewId())) {
        console.error(`ObservableObject: add listener: Given View is already a listener. Number of reg. listeners: ${this.listeners.size}`);
        return false;
      } else {
        this.listeners.add(v.getViewId());
        addViewById(v.getViewId(), v);
        console.log(`Added listening View to ObservableObject. Number of reg. listeners: ${this.listeners.size}`);
        return true;
      }
    }.bind(this);

    this.unregister = function (v) {
      if (!this.listeners.has(v.getViewId())) {
        console.error(`ObservableObject: remove listener: Given View is not a listener. Number of reg. listeners: ${this.listeners.size}`);
        return false;
      } else {
        this.listeners.delete(v.getViewId());
        removeViewById(v.getViewId());
        console.log(`Removed listening View from ObservableObject. Number of reg. listeners: ${this.listeners.size}`);
        return true;
      }
    }.bind(this);

    this.notifyAllViews = function () {
      console.log(`ObservableObject.notifyAllViews(): Notifying ${this.listeners.size} listeners.`);
      this.listeners.forEach((viewId) => markViewNeedUpdateById(viewId));
    }

    this.get = function (target, property) {
      return target[property];
    }.bind(this);

    this.set = function (target, property, newValue) {

      if (this.publishedProperties.has(property) && (target[property] != newValue)) {
        console.log(`ObservableObject: Publishd property '${property}' has been changed.`);
        this.notifyAllViews();
      }
      target[property] = newValue
      return true;
    }.bind(this);

  } // constructor
}

class ExtendableProxy {
  constructor(obj, handler) {
    return new Proxy(obj, handler);
  }
}

// gloabl JS function accessible from native side.
var createObservableObject = function (jsObj) {
  return new ObservableObject(jsObj);
}


class ObservableObject extends ExtendableProxy {

  constructor(jsObject) {
    var handler = new Handler(new Set(Object.keys(jsObject)));
    super(jsObject, handler);
    this.handler = handler;

    this.registerDependentView = function (view) {
      this.handler.register(view);
    }
    this.unregisterDependentView = function (view) {
      this.handler.unregister(view);
    }

    this.__observableobject__ = {
      get() {
        console.log("Object is ObservableObject");
        return true;
      }
    }
  }
}


/*
  function to create a LinkReference, equivalent of the '$' sign pre-pended to
  an constructor parameter. A parameter to initilaize a @Link in to-be-creted
  child Component, e.g.

  @Component
  ParentView {
    @State myState : ...;
    build() {
      ChildView(boundState: $mystate)
    }
}

  @Component
  ChildView{
    @Link boundState;

    ...
  }

  sourceView is a valid View, in above example: 'ParentView'
  sourceProperty is name of the bount to property inside sourceView,
                 in above example: 'myState'
*/
var createLinkReference = function (sourceView, sourceProperty1) {
  if ((sourceView === undefined)
    || (typeof sourceView.getViewId !== "function")
    || (sourceView.getViewId() < 0)
    || (sourceProperty1 == undefined)
    || (typeof sourceProperty1 !== "string")) {
    throw new SyntaxError(`createLinkReference expects a valid View and a property name (string) parameter!`);
  }
  let sourceProperty = sourceProperty1;

  return {
    get: function () {
      console.log(`${this.constructor.name}: get bound property '${sourceProperty}'`);
      return this.hasOwnProperty(sourceProperty) ? this[sourceProperty] : /* should never happen */ undefined;
    }.bind(sourceView),
    set: function (newValue) {
      if (this.hasOwnProperty(sourceProperty)) {
        this[sourceProperty] = newValue;
        return true;
      } else {
        /* should never happen */
        return false;
      }
    }.bind(sourceView),
    ____is_link_reference____: true
  }
} // createLinkReference


class View extends NativeView {

  constructor(id, parent) {
    super(id, parent);

    if (this.____is_initialized___ &&
      (typeof this.obsPropStore === "object") &&
      (typeof this.setInitialObjectState === "function") &&
      (typeof this.updateObjectState === "function") &&
      (typeof this.createState === "function") &&
      (typeof this.createProp === "function") &&
      (typeof this.createLink === "function")) {
      console.log(`${this.constructor.name}: re-using existing instance`);
      // further initialization not needed
      return;
    }

    console.log(`${this.constructor.name}: new instance`);

    /**
     * backing store for all observed properties, this is where their values are stored
     */
    this.obsPropStore = {};

    /**
     * map of properties, indicates for each if it is used in rendering
     * map gets build during render
     */
    this.propUsedToRender = {};
    this.isRenderingInProgress = false;

    /**  this function is run just once on an instance
     *   to set variables to their initial state
     *   var c = 1  ->  setInitialObjectState({c: 1})
    */
    this.setInitialObjectState = function (initialState) {
      if (!this.____is_initialized___) {
        console.log(`${this.constructor.name}: one-time, local initialization with values: ${JSON.stringify(initialState)}`);
        Object.assign(this, initialState);
      }
    }.bind(this);

    /**  this function is run every time a component
     *   is re-initialized, use to update constructtion function parameters
     *    new CompA({C: 7})  ->  updateObjectState({c: 7})
    */
    this.updateObjectState = function (updateParams) {
      if ((updateParams != undefined) && (typeof updateParams === "object")) {
        console.log(`${this.constructor.name}: on create and re-initialization: updating with constructor params: ${JSON.stringify(updateParams)}`);
        Object.assign(this, updateParams);
      } else {
        console.warn(`${this.constructor.name}: on create and re-initialization: missing or invalid constructor params: ${JSON.stringify(updateParams)}`);
      }
    }.bind(this);

    /**
     * View.createState("property")  API function, in eDSL @State
     *
     * usage and syntax:
     * 1. step set property of View to an initial value of type  Object, ObservableObject, Bool, String, or Number,
     *    this should happen in the constructor, e.g.
     *      this["propStr"] = createObservableObject({value: 47});
     * 2. step:  call  View.createState("propStr")
     *    createState picks up the initial value from the property and turns it into an observed state property.
     *    turning into an observed state property means propStr gets added to View.addObservedProp and the property
     *    gets turned into a get/set property.
     *
     */
    this.createState = function (propStr) {

      var setStatePropToValue = function (propStr, newValue) {
        var oldValue = this.obsPropStore[propStr];
        if ((oldValue !== undefined) && (oldValue.__observableobject__)) {
          // old value is an ObservableObject, unregister this View from the ObservableObject
          oldValue.unregisterDependentView(this);
        }

        console.log(`setStatePropToValue(${propStr} - ${JSON.stringify(newValue)})`);

        switch (typeof newValue) {
          case "boolean":
          case "string":
          case "number":
            console.log(`${this.constructor.name}: set @State '${propStr}' with value ${JSON.stringify(newValue)} of type boolean/number/string.`);
            this.obsPropStore[propStr] = newValue;
            return newValue;
          case "object":
            if (newValue.__observableobject__) {
              console.log(`${this.constructor.name}: set @State '${propStr}' with value ${JSON.stringify(newValue)} is wrapped with ObserableObject already`);
              newValue.registerDependentView(this);
              this.obsPropStore[propStr] = newValue;
              return newValue;
            } else {
              console.log(`${this.constructor.name}: set @State '${propStr}' with value ${JSON.stringify(value)} needs wrapping in ObserableObject`);
              let obs = createObservableObject(newValue);
              obs.registerDependentView(this);
              this.obsPropStore[propStr] = obs;
              return obs;
            }
          default:
            throw new SyntaxError(`${this.constructor.name}: set @State '${propStr}' with value ${JSON.stringify(value)} of unsupported type.`);
        }
        // unreachable
      }.bind(this) // setStatePropToValue local function

      if (this.____is_initialized___) {
        return;
      }

      console.log(`${this.constructor.name}: createState '${propStr}' ...`);

      if (!this.hasOwnProperty(propStr)) {
        throw new SyntaxError(`${this.constructor.name}: createState('${propStr}'): View lacks property '${propStr}'`);
      }
      if (this.obsPropStore.hasOwnProperty(propStr)) {
        throw new SyntaxError(`${this.constructor.name}: createState('${propStr}'): View has observed property '${propStr}' already!`);
      }

      // replace regular property of View with get/set property
      let value = this[propStr];
      delete this[propStr];
      console.log(`${this.constructor.name}: View.createState('${propStr}', ${JSON.stringify(value)})`);


      // in case value is an object, it must be wrapped inside an ObservableObject
      this.obsPropStore[propStr] = setStatePropToValue(propStr, value);

      Object.defineProperty(this, propStr, {
        get: function () {
          if (this.isRenderingInProgress) {
            console.log(`${this.constructor.name}: set this.propUsedToRender[{$propStr}] = true`);
            this.propUsedToRender[propStr] = true;
          }
          return this.obsPropStore[propStr];
        }.bind(this),

        set: function (newValue) {
          if (this.obsPropStore[propStr] === newValue) {
            console.log(`${this.constructor.name}: View.(observed)set('${propStr}', unchanged value ${JSON.stringify(newValue)})`);
            return true;
          }
          setStatePropToValue(propStr, newValue);
          console.log(`${this.constructor.name}: View.(observed)set('${propStr}': need for update, is used in render`);
          markViewNeedUpdateById(this.getViewId())

          return true;
        }.bind(this)
      });

      // native function: add this View into the global map of Views by random Id
      // see also markViewNeedUpdateById
      addViewById(this.getViewId(), this);

    }.bind(this);

    /**
     * View.createLink(linkReference, "property") API function, in eDSL @Link
     *
     * in eDSL:
     *
     * @Component
     * ParentView {
    * @State myState = { ... };
    *   build() {
    *    ChildView(boundState: $mystate)
    *   }
    * }
    *
    * @Component
    * ChildView{
    *    @Link boundState;
    *    ...
    *  }
     *
     * in pure JS with ACE-Diff APIs:
     *
     * ParentView : View {
     *   constructor() {
     *      this.myState = { ... };
     *      this.createState("myState");
     *   }
     *
     *   render() {
     *     return new ChildView(createLinkReference(this, "myState"));
     *   }
     *
     * ChildView : View {
     *  option 1 how to write constructor
    *   constructor(linkReference) {
    *      this.createLink("boundState", linkReference)
    *   }
    *
    * *  option 2 how to write constructor
    *   constructor(linkReference) {
    *      this.boundState = linkReference;
    *      this.createLink("boundState")
    *   }
     * }
     */
    this.createLink = function (propStr, linkReference) {

      if (this.____is_initialized___) {
        return;
      }

      var ___linkReference___ = linkReference || this[propStr];  // to local closure use either 2nd parameter or previous defined value.

      if ((___linkReference___ === undefined) || (___linkReference___.get() === undefined)) {
        throw new SyntaxError(`${this.constructor.name}: createLink for '${propStr}'. linkReference is undefined or invalid!`);
      }

      console.log(`${this.constructor.name}: View.createLink('${propStr}'`);

      delete (this[propStr]);
      Object.defineProperty(this, propStr, {
        get: () => {
          console.log(`${this.constructor.name}: Getting @Link '${propStr}'}`);
          if (this.isRenderingInProgress) {
            this.propUsedToRender[propStr] = true;
          }
          return ___linkReference___.get();
        },

        set: (newValue) => {
          if (newValue.____is_link_reference____) {
            console.log(`${this.constructor.name}: set '${propStr}' with a link reference. Ignoring`);
            if (this.propUsedToRender[propStr] == true) {
              markViewNeedUpdateById(this.getViewId())
            } else {
              console.log(`${this.constructor.name}: View.(observed)set('${propStr}': no need for update, is not used in render`);
            }
            return;
          }
          console.log(`${this.constructor.name}: Setting @Link '${propStr}' `);

          let oldValue = ___linkReference___.get();
          if (oldValue === newValue) {
            console.log(`.. value unchanged, nothing to do.`);
            return true;
          }
          // update registrations of this View to ObservableObjects (any old or new one)
          if (oldValue.__observableobject__) {
            console.log(`.. unregistering from ObservableObject old link value`);
            oldValue.unregisterDependentView(this);
          }
          if (newValue.__observableobject__) {
            console.log(`.. registering to ObservableObject new link value`);
            newValue.registerDependentView(this);
          }
          if (this.propUsedToRender[propStr] == true) {
            markViewNeedUpdateById(this.getViewId())
          } else {
            console.log(`${this.constructor.name}: View.(observed)set('${propStr}': no need for update, is not used in render`);
          }
          return ___linkReference___.set(newValue);
        }
      });

      if (___linkReference___.get().__observableobject__) {
        console.log(`.. registering to ObservableObject new link value`);
        ___linkReference___.get().registerDependentView(this);
      }

      // native function: add this View into the global map of Views by random Id
      // see also markViewNeedUpdateById
      addViewById(this.getViewId(), this);

    }.bind(this);



    /**
       * View.createProp("property") API function, in eDSL @Prop
       *
       * usage and syntax:
       * 1. step set property of View to an initial value of type Bool, Number, or String/
       *    this typically happens in the constructor, and the initial value is a attr of the constructor function, e.g.
       *    constructor(simpleValueProp) {}
       *        this["propStr"] = simpleValueProp
       *        this.createLink("propStr")
       *     }
        * 2. step:  call  View.createProp("propStr")
        *    createProp picks up the initial value from the property and turns it into a observed link property.
        *    turning into an observed state property means propStr gets added to View.addObservedProp,
        *    and the property gets turned into a get/set property.
        *
        */
    this.createProp = function (propStr) {

      if (this.____is_initialized___) {
        return;
      }

      if (!this.hasOwnProperty(propStr)) {
        throw new SyntaxErro(`${this.constructor.name}: createProp('${propStr}'). View lacks property '${propStr}'. Ignoring`);
      }
      if (this.obsPropStore.hasOwnProperty(propStr)) {
        throw new SyntaxError(`${this.constructor.name}: createProp('${propStr}'): View has observed property '${propStr}' already!`);
      }

      // replace regular property of View with a get/set property
      let value = this[propStr];
      delete this[propStr];

      console.log(`${this.constructor.name}: View.createProp('${propStr}', ${JSON.stringify(value)}) by-value type value.`);

      // check and set the value type, and set value to View's obsPropStore
      if ((typeof value != "number") && (typeof value != "bool") && (typeof value != "string")) {
        throw new SyntaxError(`${this.constructor.name} Create @Prop('${propStr}'): ${value} must be a Bool, Number, or String.`);
      }
      console.log(`${this.constructor.name}: Set @Prop '${propStr}' to ${JSON.stringify(value)}.`);
      this.obsPropStore[propStr] = value;

      // define get/set property to obtain value from View's obsPropStore
      Object.defineProperty(this, propStr, {
        get: () => {
          console.log(`${this.constructor.name}: Get @Prop '${propStr}'`);
          if (this.isRenderingInProgress) {
            this.propUsedToRender[propStr] = true;
          }
          return this.obsPropStore[propStr];
        },
        set: (newValue) => {
          if (this.obsPropStore[propStr] === newValue) {
            console.log(`${this.constructor.name}: Set @Prop '${propStr}' value ${JSON.stringify(newValue)} unchanged.`);
            return true;
          }

          if ((typeof newValue != "number") && (typeof newValue != "bool") && (typeof newValue != "string")) {
            throw new SyntaxError(`${this.constructor.name} set @Prop('${propStr}'): ${newValue} must be a Bool, Number, or String.`);
          }
          console.log(`${this.constructor.name}: Set @Prop '${propStr}' to ${JSON.stringify(newValue)}.`);
          this.obsPropStore[propStr] = newValue;

          if (this.propUsedToRender[propStr] == true) {
            markViewNeedUpdateById(this.getViewId())
          } else {
            console.log(`${this.constructor.name}: View.(observed)set('${propStr}': no need for update, is not used in render`);
          }
          return true;
        }
      })

      // native function: add this View into the global map of Views by random Id
      // see also markViewNeedUpdateById
      addViewById(this.getViewId(), this);

    }.bind(this); // createProp function
  }

  aboutToRender() {
    this.isRenderingInProgress = true;
    Object.keys(this.obsPropStore).forEach((prop) => this.propUsedToRender[prop] = false);
    console.log(`${this.constructor.name}: aboutToRender: these properties to monitor get access: ${JSON.stringify(this.propUsedToRender)}.`);

  }

  onRenderDone() {
    this.isRenderingInProgress = false;
    console.log(`${this.constructor.name}: onRenderDone: render performed get access to these properties: ${JSON.stringify(this.propUsedToRender)}.`);
  }
}
