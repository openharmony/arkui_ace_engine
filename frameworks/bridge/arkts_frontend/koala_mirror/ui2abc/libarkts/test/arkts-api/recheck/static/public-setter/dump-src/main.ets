
import { AnimatedState as AnimatedState, one as one } from "./library";

let x: (AnimatedState<number> | undefined);

function main(): void {}

if (x) {
  x!.paused = true
}

class AnimatedStateImpl<Value>  implements AnimatedState<Value> {
  set paused(paused: boolean) {
    throw new Error("");
  }
  
  public get paused(): boolean {
    throw new Error("");
  }
  
  public constructor() {}
  
}

