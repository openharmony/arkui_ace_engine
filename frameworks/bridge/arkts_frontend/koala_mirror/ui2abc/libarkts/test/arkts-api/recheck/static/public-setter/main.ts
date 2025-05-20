import { AnimatedState, one } from "./library"

let x: AnimatedState<number>|undefined
if (x) x!.paused = true
class AnimatedStateImpl<Value> implements AnimatedState<Value> {
    get paused(): boolean {
        throw new Error("")
    }
    set paused(paused: boolean) {
        throw new Error("")
    }
}
