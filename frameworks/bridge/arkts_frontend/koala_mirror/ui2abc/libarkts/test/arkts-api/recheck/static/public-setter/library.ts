export interface AnimatedState<Value> {
    paused: boolean
}

class AnimatedStateImpl<Value> implements AnimatedState<Value> {
    get paused(): boolean {
        throw new Error("")
    }
    set paused(paused: boolean) {
        throw new Error("")
    }
}

export function one() {

}
