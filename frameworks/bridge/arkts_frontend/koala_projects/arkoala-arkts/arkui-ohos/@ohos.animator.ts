export interface AnimatorOptions {
    duration: number;
    easing: string;
    delay: number;
    fill: "none" | "forwards" | "backwards" | "both";
    direction: "normal" | "reverse" | "alternate" | "alternate-reverse";
    iterations: number;
    begin: number;
    end: number;
}

export declare class SimpleAnimatorOptions {
}
export declare class Animator {
    static create(options: AnimatorOptions | SimpleAnimatorOptions): AnimatorResult;
}

export declare class AnimatorResult {
}