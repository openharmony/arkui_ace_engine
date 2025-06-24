export interface State<Value> {
    /**
     * If state was modified since last UI computations.
     */
    readonly modified: boolean
    /**
     * Current value of the state.
     * State value doesn't change during memo code execution.
     */
    readonly value: Value
}

export interface MutableState<Value> extends State<Value> {
    /**
     * Current value of the state as a mutable value.
     * You should not change state value from a memo code.
     * State value doesn't change during memo code execution.
     * In the event handlers and other non-memo code
     * a changed value is immediately visible.
     */
    value: Value
}

export function mutableState<T>(value: T): MutableState<T> {
    return { value, modified: false }
}


interface I {
    s: string
}

class Impl {
    s = " asd"
}

export function provideI(): I {
    return new Impl()
}