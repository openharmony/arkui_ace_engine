/**
    given parameters for calling a @Builder function
    this function wraps the Object of type T inside a ES6 Proxy.
    Each param, i.e. Object property is either a function or a value.
    If it is a function the function can either return a value of expected 
    parameter type or an ObservedPropertyabstract<T> where T is the exected 
    parameter type. The latter is the case when passing a state variable by 
    reference.

    Two purposes:
    1 - @Builder function boxy accesses params a '$$.paramA'
        However paramA can be a function, so to obtain the value the 
        access would need to be '$$.param()' The proxy executes 
        the function and return s the result
    2 - said function returns to ObservedPropertyAbstract backing store of 
        a calling @Component state variable (whenever the state var is 
        provided to the @Builder function). For this case the proxy can provide
        - the value by executing paramA() to return the ObservedPropertyAbstract 
          and further (monitored!) get() to read its value
        - when requested to return '__param1' it returns the ObservedPropertyAbstract
          object. The scenario is to use to init a @Link source.
  */
function makeBuilderParameterProxy(builderName: string, source: Object): Object {
    return new Proxy(source, {
        set(target, prop, val) {
            throw Error(`@Builder '${builderName}': Invalid attempt to set(write to) parameter '${prop.toString()}' error!`);
        },
        get(target, prop) {
            const prop1 = prop.toString().trim().startsWith("__")
                ? prop.toString().trim().substring(2)
                : prop.toString().trim();
            stateMgmtConsole.debug(`get - prop ${prop.toString()} prop1 ${prop1}`);
            if (!(typeof target === "object") && (prop1 in target)) {
                throw Error(`@Builder '${builderName}': '${prop1}' used but not a function parameter error!`);
            }
            const value = target[prop1];
            if (typeof value !== "function") {
                stateMgmtConsole.debug(`      - no fun`);
                return value;
            }
            const funcRet = value();
            if ((typeof funcRet === "object") && ('get' in funcRet)) {
                if (prop1 !== prop) {
                    stateMgmtConsole.debug(`      - func - is ObservedPropertybstract - ret ObservedPropertyObject`);
                    return funcRet;
                } else {
                    stateMgmtConsole.debug(`      - func - is ObservedPropertybstract - ret get()`);
                    const result = funcRet.get();
                    stateMgmtConsole.debug(`                                          - returns ${result}`);
                    return result;
                }
            }

            stateMgmtConsole.debug(`      - func - no ObservedPropertybstract - ret value ${funcRet}`);
            return funcRet;
        } // get
    }); // new Proxy
}
