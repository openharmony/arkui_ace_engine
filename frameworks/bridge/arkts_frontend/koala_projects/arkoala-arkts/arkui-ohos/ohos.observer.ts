export declare namespace observer {
    export interface UIObserver {
        on(type: string, callback: () => void): void;

        off(type: string, callback?: () => void): void;
    }
    export function createUIObserver(id: number): UIObserver;
}
