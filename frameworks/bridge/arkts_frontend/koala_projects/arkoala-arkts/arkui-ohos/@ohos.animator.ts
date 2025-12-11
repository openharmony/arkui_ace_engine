import { float32, int32 } from "@koalaui/compat";

export interface AnimatorOptions {
    duration: int32;
    easing: string;
    delay: int32;
    fill: "none" | "forwards" | "backwards" | "both";
    direction: "normal" | "reverse" | "alternate" | "alternate-reverse";
    iterations: int32;
    begin: double;
    end: double;
}

export declare class SimpleAnimatorOptions {
}
export declare class Animator {
    static create(options: AnimatorOptions | SimpleAnimatorOptions): AnimatorResult;
}

export declare class AnimatorResult {
}